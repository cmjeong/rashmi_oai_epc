///////////////////////////////////////////////////////////////////////////////
//
// TcpSocket.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h> // sleep
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <system/Trace.h>
#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TcpSocket.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class - TcpSocket
///////////////////////////////////////////////////////////////////////////////

TcpSocket::TcpSocket(TcpRxInterface *tcpRxInterface) :
    m_connected(false),
    m_sockAddr()
{
    ENTER ();

    // Create TCP socket.
    m_sockFd = socket(AF_INET, SOCK_STREAM, 0);
    RSYS_ASSERT(m_sockFd != -1);

    // Construct the receive thread.
    m_tcpReceiveThread.reset(new TcpClientReceiveThread(m_sockFd, tcpRxInterface));

    EXIT ();
}

TcpSocket::TcpSocket(u16 localPort, TcpServerRxInterface *tcpRxInterface, IPv4Address localIpAddress) :
    m_connected(false),
    m_sockAddr()
{
    ENTER ();

    // Preconditions.
    RSYS_ASSERT(localIpAddress.IsSet());

    // Create TCP socket.
    m_sockFd = socket(AF_INET, SOCK_STREAM, 0);
    RSYS_ASSERT(m_sockFd != -1);

    // Give the socket a name and bind it
    m_sockAddr.sin_family = AF_INET;
    m_sockAddr.sin_port = htons (localPort);
    m_sockAddr.sin_addr.s_addr = localIpAddress.Get();

    TRACE_PRINTF("TcpSocket::TcpSocket: Attempting to bind to local address %s", localIpAddress.ToString()) ;
    if (bind (m_sockFd, (struct sockaddr *) &m_sockAddr, sizeof (m_sockAddr)) == -1)
    {
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "TcpSocket::TcpSocket: Failed to bind socket, Errno = %d, %s", errno, strerror(errno));
    }

    // Construct the receive thread.
    m_tcpReceiveThread.reset(new TcpServerReceiveThread(m_sockFd, tcpRxInterface));

    EXIT ();
}

TcpSocket::~TcpSocket()
{
    ENTER ();

    // Clean up the receive thread.
    StopReceiving();

    // And close the socket.
    close(m_sockFd);

    EXIT ();
}

int TcpSocket::GetSocketFd() const
{
    ENTER();
    RETURN(m_sockFd);
}

bool TcpSocket::Connect(IPv4Address remoteIpAddress, u16 remotePort)
{
    ENTER ();

    struct sockaddr_in remoteSockAddr;
    // Build the sockaddr structure for sending packets.
    bzero((char *) &remoteSockAddr, sizeof(remoteSockAddr));
    u32 ipAddressU32 = remoteIpAddress.Get();
    remoteSockAddr.sin_family = AF_INET;
    remoteSockAddr.sin_port = htons(remotePort);
    remoteSockAddr.sin_addr.s_addr = ipAddressU32;

    int connectResult = connect(m_sockFd, (struct sockaddr *) &remoteSockAddr, sizeof(remoteSockAddr));

    m_connected = (connectResult == 0);

    RETURN (m_connected);
}

bool TcpSocket::Connect(IPv4Address remoteIpAddress, u16 remotePort, u32 timeoutSecs)
{
    ENTER();

    RSYS_ASSERT(timeoutSecs > 0);

    int error = 0;
    int flags;
    fd_set rset, wset;
    int connectResult;
    struct timeval tval;
    struct sockaddr_in remoteSockAddr;

    // Build the sockaddr structure for sending packets.
    bzero((char *) &remoteSockAddr, sizeof(remoteSockAddr));
    u32 ipAddressU32 = remoteIpAddress.Get();
    remoteSockAddr.sin_family = AF_INET;
    remoteSockAddr.sin_port = htons(remotePort);
    remoteSockAddr.sin_addr.s_addr = ipAddressU32;

    // Set the socket as nonblocking IO.
    flags = fcntl(m_sockFd, F_GETFL, 0);
    fcntl(m_sockFd, F_SETFL, flags | O_NONBLOCK);

    // Try to connect.
    if((connectResult = connect(m_sockFd, (struct sockaddr *) &remoteSockAddr, sizeof(remoteSockAddr))) < 0)
    {
        // connect() returned an error code, if this isn't EINPROGRESS
        // then something's gone wrong.
        if(errno != EINPROGRESS)
        {
            RETURN(false);
        }
    }

    if(connectResult != 0)
    {
        // connect() didn't complete (this is the normal case) so now wait for
        // connection or timeout.
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        FD_SET(m_sockFd, &rset);
        FD_SET(m_sockFd, &wset);
        tval.tv_sec = timeoutSecs;
        tval.tv_usec = 0;

        // Call select() until connected or we timeout.
        if( (connectResult = select(m_sockFd+1, &rset, &wset, NULL, &tval)) == 0)
        {
            TRACE_MSG("TcpSocket::Connect: Timed out");
            RETURN(false);
        }

        if(FD_ISSET(m_sockFd, &rset) || FD_ISSET(m_sockFd, &wset))
        {
            socklen_t len = sizeof(error);
            if(getsockopt(m_sockFd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
            {
                TRACE_MSG("TcpSocket::Connect: getsockopt() failed");
                RETURN(false);
            }
        }
        else
        {
            TRACE_MSG("TcpSocket::Connect: select() failed");
            RETURN(false);
        }
    }

    // Change the socket options back to what they were before.
    fcntl(m_sockFd, F_SETFL, flags);

    m_connected = true;

    RETURN(true);

}

bool TcpSocket::IsConnected()
{
    ENTER ();
    RETURN (m_connected);
}

void TcpSocket::StartReceiving()
{
    ENTER ();

    m_tcpReceiveThread->StartThread();

    EXIT ();
}

void TcpSocket::StopReceiving()
{
    ENTER ();

    m_tcpReceiveThread->StopThread();

    EXIT ();
}

s32 TcpSocket::TcpSend(const u8* packet, u32 packetLen, const int sockId)
{
    ENTER ();

    RETURN (send((sockId < 0 ? m_sockFd : sockId), packet, packetLen, 0 /* flags */));
}

std::string TcpSocket::ToString() const
{
    ENTER ();

    std::ostringstream stream;
    struct sockaddr_in remoteSockAddr;
    socklen_t size = sizeof (remoteSockAddr);

    if (getpeername (m_sockFd, (struct sockaddr *) &remoteSockAddr, &size) < 0)
        stream << "Socket error or not connected";
    else
        stream << "Socket FD " << m_sockFd << " connected to remoteAddress "
               << inet_ntoa (remoteSockAddr.sin_addr) << ", remotePort " << ntohs (remoteSockAddr.sin_port);

    RETURN (stream.str());
}
