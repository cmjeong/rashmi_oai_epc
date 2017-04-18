///////////////////////////////////////////////////////////////////////////////
//
// TcpReceiveThread.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <algorithm> // min,max
#include <cstring> // strerror
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#include <system/Trace.h>
#include <system/Thread.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TcpReceiveThread.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class - TcpReceiveThread
///////////////////////////////////////////////////////////////////////////////

TcpReceiveThread::TcpReceiveThread(int sockFd, const char * threadName ) :
    Thread(threadName),
    m_localSockFd(sockFd)
{
    ENTER ();

    int r = pipe(m_stopPipe);
    RSYS_ASSERT(r == 0);

    EXIT ();
}

void TcpReceiveThread::StopThread()
{
    if (m_threadHandle != 0)
    {
        char c = 's';
	int w_ret = -1;

        TRACE("TcpReceiveThread stopping", GetThreadName());

        // Setting this bool to true should cause the main thread procedure
        //  exit...
        m_threadStopRequest = true;

        // Unblock select
        w_ret = write(m_stopPipe[1], &c, sizeof(c));
	if(w_ret < 1)
        {
		TRACE_MSG("Error while writing to stop Pipe");
	}

        // In which case the join() call below shouldn't take too long.
        pthread_join (m_threadHandle, NULL);
        m_threadHandle = 0;

        // No longer needed
        close(m_stopPipe[0]);
        close(m_stopPipe[1]);
    }//end if
}

///////////////////////////////////////////////////////////////////////////////
// Class - TcpClientReceiveThread
///////////////////////////////////////////////////////////////////////////////

TcpClientReceiveThread::TcpClientReceiveThread(int sockFd, TcpRxInterface *tcpRxInterface ) :
    TcpReceiveThread(sockFd, "TCP Client Receive Thread"),
    m_tcpRxInterface(tcpRxInterface)
{
    ENTER ();
    EXIT ();
}


u32 TcpClientReceiveThread::ThreadProcedure()
{
    ENTER ();

    // Read FD set.
    fd_set rxSet, activeSet;

    TRACE("Running ", GetThreadName());

    FD_ZERO(&activeSet);
    FD_SET(m_localSockFd, &activeSet);
    FD_SET(m_stopPipe[0], &activeSet);

    int nfds = std::max<int>(m_stopPipe[0],m_localSockFd) + 1;

    while(!ThreadStopped())
    {
        rxSet = activeSet;
        // Use select to wait for new packets.
        select(nfds, &rxSet, NULL, NULL, NULL);

        if(FD_ISSET(m_localSockFd, &rxSet))
        {
            // It's for us, pass it on.
            m_tcpRxInterface->HandleTcpRx(m_localSockFd);
        }

        // Check stack usage for this thread.
        //CheckStackUsage();
    }

    // Make sure disconnect is handled as the thing that stopped
    // this thread might not be the thing that needs to know about
    // disconnections.
    m_tcpRxInterface->HandleTcpDisconnect(m_localSockFd);

    // Clean up.
    close(m_localSockFd);

    TRACE("TcpClientReceiveThread stopped", GetThreadName());

    RETURN (0);
}

///////////////////////////////////////////////////////////////////////////////
// Class - TcpServerReceiveThread
///////////////////////////////////////////////////////////////////////////////

TcpServerReceiveThread::TcpServerReceiveThread(int sockFd, TcpServerRxInterface *tcpRxInterface ) :
    TcpReceiveThread(sockFd, "TCP Server Receive Thread"),
    m_tcpRxInterface(tcpRxInterface)
{
    ENTER ();
    EXIT ();
}


u32 TcpServerReceiveThread::ThreadProcedure()
{
    ENTER ();

    // Read FD set.
    fd_set activeSet, rxSet;

    TRACE("Running ", GetThreadName());

    if (listen (m_localSockFd, 1) < 0)
    {
        TRACE_MSG("TcpSocket::Listen: Error");
    }

    FD_ZERO(&activeSet);
    FD_SET(m_localSockFd, &activeSet);
    FD_SET(m_stopPipe[0], &activeSet);

    int nfds = std::max<int>(m_stopPipe[0], m_localSockFd) + 1;

    // Signal here to the thread handler that we're as ready as we'll ever be.

    int selectResult = 0;
    while(!ThreadStopped())
    {
        // Use select to wait for new packets.

        rxSet = activeSet;
        selectResult = select(nfds, &rxSet, NULL, NULL, NULL);
        if (selectResult < 0)
        {
            TRACE_PRINTF("TcpSocket::Select: Error %s",strerror(errno));

        }
        if (selectResult == 0)
        {
            TRACE_MSG("Select timed out");
            continue;
        }

        // Serving the pending sockets
        for (int i = 0; i < nfds; ++i)
        {
            if(FD_ISSET(i, &rxSet))
            {
                if (i == m_localSockFd)
                {
                    // Connection request on original socket.
                    int newSockFd;
                    struct sockaddr_in newSockAddr;
                    socklen_t size = sizeof (newSockAddr);

                    newSockFd = accept (m_localSockFd, (struct sockaddr *) &newSockAddr, &size);
                    if (newSockFd < 0)
                    {
                        TRACE_MSG("TcpSocket::Accept: Error");
                    }
                    else
                    {
                        TRACE_PRINTF ("Server: connect from host %s, port %"PRIu16".\n",
                                inet_ntoa (newSockAddr.sin_addr),
                                ntohs (newSockAddr.sin_port));

                        // Add this socket to the active set
                        FD_SET (newSockFd, &activeSet);
                        nfds = std::max<int>(nfds, newSockFd + 1);
                        //Inform the external interface which is the new sock fd
                        m_tcpRxInterface->HandleNewTcpSock(newSockFd);
                    }

                } // local socket
                else if (i != m_stopPipe[0])
                {
                    // It's for us, pass it on.
                    if (m_tcpRxInterface->HandleTcpRx(i) < 0)
                    {
                        //0 bytes were read; so the other end has closed
                        // We close as well
                        TRACE("Server close socket: ", (u32)i);
                        close (i);
                        FD_CLR (i, &activeSet);
                    }
                }
            } // if FD_ISSET
        } // for

        // Check stack usage for this thread.
        //CheckStackUsage();
    } // while

    // Make sure disconnect is handled as the thing that stopped
    // this thread might not be the thing that needs to know about
    // disconnections.
    m_tcpRxInterface->HandleTcpDisconnect(m_localSockFd);

    // Clean up.
    close(m_localSockFd);

    TRACE("TcpServerReceiveThread stopped", GetThreadName());

    RETURN (0);
}
