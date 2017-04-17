///////////////////////////////////////////////////////////////////////////////
//
// UdpSocket.cpp
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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UdpSocket.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class - UdpSocket
///////////////////////////////////////////////////////////////////////////////

UdpSocket::UdpSocket( const IPv4Address& localIpAddress, u16 localPort, const IPv4Address& remoteIpAddress,
                      u16 remotePort, UdpRxInterface& udpRxInterface, TOSVal tosValue, bool reentrantUdpSend) :
    m_localIpAddress(localIpAddress),
    m_localPort(localPort),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_tosValue(tosValue),
    m_fd(-1),
    m_reentrantUdpSend(reentrantUdpSend)
{
    ENTER ();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    Thread::InitialiseMutex(m_udpSendMutex);

    // Initialise both receive and transmit.
    InitialiseTransmit();
    // Do receive after transmit so we can re-use tx FD.
    InitialiseReceive(udpRxInterface);

    EXIT ();
}

UdpSocket::UdpSocket(u16 localPort, const IPv4Address& remoteIpAddress, u16 remotePort,
                    UdpRxInterface& udpRxInterface, bool reentrantUdpSend) :
    m_localIpAddress("0.0.0.0"),
    m_localPort(localPort),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_tosValue(QOS_NONE),
    m_fd(-1),
    m_reentrantUdpSend(reentrantUdpSend)
{
    ENTER ();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    Thread::InitialiseMutex(m_udpSendMutex);

    // Initialise both receive and transmit.
    InitialiseTransmit();
    // Do receive after transmit so we can re-use tx FD.
    InitialiseReceive(udpRxInterface);

    EXIT ();
}

UdpSocket::UdpSocket( const IPv4Address& localIpAddress, const IPv4Address& remoteIpAddress, u16 remotePort,
                      TOSVal tosValue, bool reentrantUdpSend) :
    m_localIpAddress(localIpAddress),
    m_localPort(0),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_tosValue(tosValue),
    m_fd(-1),
    m_reentrantUdpSend(reentrantUdpSend)
{
    ENTER();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    Thread::InitialiseMutex(m_udpSendMutex);

    // Transmit only.
    InitialiseTransmit();

    EXIT();
}

UdpSocket::UdpSocket( const IPv4Address& localIpAddress, u16 localPort, const IPv4Address& remoteIpAddress, u16 remotePort,
                      TOSVal tosValue, bool reentrantUdpSend) :
    m_localIpAddress(localIpAddress),
    m_localPort(localPort),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_tosValue(tosValue),
    m_fd(-1),
    m_reentrantUdpSend(reentrantUdpSend)
{
    ENTER();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    Thread::InitialiseMutex(m_udpSendMutex);

    // Transmit only.
    InitialiseTransmit();

    EXIT();
}

UdpSocket::UdpSocket(const IPv4Address& remoteIpAddress, u16 remotePort, bool reentrantUdpSend) :
    m_localIpAddress("0.0.0.0"),
    m_localPort(0),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_tosValue(QOS_NONE),
    m_fd(-1),
    m_reentrantUdpSend(reentrantUdpSend)
{
    ENTER();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    Thread::InitialiseMutex(m_udpSendMutex);

    // Transmit only.
    InitialiseTransmit();

    EXIT();
}

UdpSocket::UdpSocket(u16 localPort, UdpRxInterface& udpRxInterface) :
    m_localIpAddress("0.0.0.0"),
    m_localPort(localPort),
    m_remotePort(0),
    m_tosValue(QOS_NONE),
    m_fd(-1),
    m_reentrantUdpSend(false)
{
    ENTER();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    Thread::InitialiseMutex(m_udpSendMutex);

    // Receive only.
    InitialiseReceive(udpRxInterface);

    EXIT();
}

UdpSocket::~UdpSocket()
{
    ENTER ();

    // Clean up the receive thread.
    if(m_udpReceiveThread != NULL)
    {
        StopReceiving();
    }

    // And close the transmit socket.
    if(m_fd >= 0)
    {
        close(m_fd);
    }

    if(m_reentrantUdpSend)
    {
        Thread::DestroyMutex(m_udpSendMutex);
    }

    EXIT ();
}

void UdpSocket::StartReceiving()
{
    ENTER ();

    if(m_udpReceiveThread != NULL)
    {
        struct sockaddr_in addr;

        if(m_localPort != 0)
        {
            TRACE("  Local port", (u32)m_localPort);
        }

        if(m_fd < 0)
        {
            // No FD supplied so open and bind a socket.

            m_fd = socket(PF_INET, SOCK_DGRAM, 0);
            RSYS_ASSERT(m_fd != -1);

            bzero(&addr, sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_port = htons(m_localPort);
            addr.sin_addr.s_addr = INADDR_ANY;

            int reuse = 1;
            if ( setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0 )
            {
                TRACE_MSG_LEV(TRACE_WARNING, "Failed SO_REUSEADDR call");
            }

            if(bind(m_fd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
            {
                TRACE_MSG_LEV(TRACE_CRITICAL, "Failed to bind in UdpSocket::StartReceiving()");
                close(m_fd);
                RETURN_VOID();
            }
            else
            {
                TRACE_PRINTF("Successful UDP Rx bind(%u:%u)",ntohl(addr.sin_addr.s_addr),m_localPort);
            }
        }

        m_udpReceiveThread->StartThread(MEDIUM_DEFAULT_THREAD_STACK_SIZE);

        TRACE_MSG("Waiting for UDP receive thread to be ready");

        while(!m_udpReceiveThread->IsReadyToReceive())
        {
            /* Allow other threads to run before re-checking */
            sched_yield();
        }
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "UdpSocket::StartReceiving(): %s not configured for receiving", ToString().c_str());
    }

    EXIT ();
}


void UdpSocket::StopReceiving()
{
    ENTER ();

    if(m_udpReceiveThread != NULL)
    {
        m_udpReceiveThread->StopThread();
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "UdpSocket::StopReceiving(): %s not configured for receiving", ToString().c_str());
    }

    EXIT ();
}

void UdpSocket::CloseOnExec()
{
    ENTER ();

    if(m_fd >= 0)
    {
        if(fcntl(m_fd, F_SETFD, FD_CLOEXEC) == -1)
        {
            TRACE_PRINTF("fcntl(m_fd, F_SETFD, FD_CLOEXEC) failed: %s", strerror(errno));
        }
    }

    EXIT ();
}

s32 UdpSocket::UdpSend(const u8* packet, u32 packetLen) const
{
    ENTER ();

    RSYS_ASSERT_PRINTF(m_txSockAddr.sin_addr.s_addr != 0, "%s", ToString().c_str());

    if(m_fd >= 0)
    {
        // Documentation on sendto (that I've found) is unclear as to whether it is thread-safe
        // in linux (and I guess uClinux in particular although it shouldn't be different).
        // POSIX spec is quiet on the issue.
        // So let's give the user the option, will aid portability too.
        if(m_reentrantUdpSend)
        {
            Thread::LockMutex(m_udpSendMutex);
        }

        // Under C++ you don't get the funky transparent union for sockaddr/sockaddr_in so have to cast.
        struct sockaddr * txSockAddr = (sockaddr *) &m_txSockAddr;

        s32 result = sendto(m_fd, packet, packetLen, 0 /* flags */, txSockAddr, sizeof(m_txSockAddr));

        if(m_reentrantUdpSend)
        {
            Thread::UnlockMutex(m_udpSendMutex);
        }

        RETURN (result);
    }

    TRACE_PRINTF_LEV(TRACE_WARNING, "UdpSocket::UdpSend(): %s not configured for transmit", ToString().c_str());

    RETURN(-1);
}

s32 UdpSocket::UdpSendTo(const IPv4Address& remoteIpAddress, u16 remotePort, const u8* packet, u32 packetLen) const
{
    ENTER ();

    RSYS_ASSERT(remoteIpAddress.IsSet());
    RSYS_ASSERT(m_fd >= 0);

    u32 ipAddress;
    remoteIpAddress.Get(ipAddress);

    // Documentation on sendto (that I've found) is unclear as to whether it is thread-safe
    // in linux (and I guess uClinux in particular although it shouldn't be different).
    // POSIX spec is quiet on the issue.
    // So let's give the user the option, will aid portability too.
    if(m_reentrantUdpSend)
    {
        Thread::LockMutex(m_udpSendMutex);
    }

    // Setup destination.
    struct sockaddr_in txSockAddr;
    txSockAddr.sin_family      = AF_INET;
    txSockAddr.sin_port        = htons(remotePort);
    txSockAddr.sin_addr.s_addr = ipAddress;

    s32 result = sendto(m_fd, packet, packetLen, 0 /* flags */,
                        (sockaddr *)&txSockAddr, // Under C++ you don't get the funky transparent union for sockaddr/sockaddr_in so have to cast.
                        sizeof(txSockAddr));

    if(m_reentrantUdpSend)
    {
        Thread::UnlockMutex(m_udpSendMutex);
    }

    RETURN (result);
}

string UdpSocket::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "Tx=" << m_remoteIpAddress.ToString() << ":" << m_remotePort;
    if(m_localPort != 0)
    {
        stream << ", RxPort=" << m_localPort;
    }
    else
    {
        stream << ", No Rx";
    }

    RETURN(stream.str());
}

void UdpSocket::InitialiseTransmit()
{
    ENTER();

    if(m_reentrantUdpSend)
    {
        // Initialise the mutex for UdpSend.
        Thread::InitialiseMutex(m_udpSendMutex);
    }

    // Open transmit socket.
    m_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(m_fd < 0)
    {
        TRACE_LEV(TRACE_WARNING, "Error opening UDP socket", (s32)errno);
        RETURN_VOID();
    }
    else
    {
        TRACE("UDP socket opened", ToString().c_str());
    }

    int reuse = 1;
    if ( setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0 )
    {
        TRACE_MSG_LEV(TRACE_WARNING, "Failed SO_REUSEADDR call");
    }

#if defined(BUILD_bfin_uclinux_2006) || defined(BUILD_bfin_uclinux_2008)
    if ( m_tosValue != QOS_NONE )
    {
        // getsockopt call is need only to prevent setsockopt to fail
        int getVal = 0;
        getsockopt(m_fd, IPPROTO_IP, IP_TOS, &getVal, ((socklen_t*)sizeof(getVal)) );
        if( setsockopt(m_fd, SOL_IP, IP_TOS, &m_tosValue, sizeof(m_tosValue)) == -1)
        {
            TRACE("(UDP Socket) Error setting setsockopt for TOS", (s32)errno);
            RETURN_VOID();
        }
    }
#endif

    // Bind to local addr:port (0.0.0.0:0 allows bind to choose).
    {
        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        u32 localIpAddressU32InNetworkByteOrder = m_localIpAddress.Get();
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_localPort);
        addr.sin_addr.s_addr = localIpAddressU32InNetworkByteOrder;

        if(bind(m_fd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
        {
            TRACE_MSG_LEV(TRACE_CRITICAL, "Failed to bind in UdpSocket::InitialiseTransmit()");
            close(m_fd);
            m_fd = -1;
            RETURN_VOID();
        }
        else
        {
            TRACE_PRINTF("Successful UDP Tx bind(%u:%u)",ntohl(localIpAddressU32InNetworkByteOrder),m_localPort);
        }
    }

    // Setup destination.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));
    u32 ipAddressU32 = m_remoteIpAddress.Get();
    m_txSockAddr.sin_family = AF_INET;
    m_txSockAddr.sin_port = htons(m_remotePort);
    m_txSockAddr.sin_addr.s_addr = ipAddressU32;

    EXIT();
}

void UdpSocket::InitialiseReceive(UdpRxInterface& udpRxInterface)
{
    ENTER();

    if(m_localPort != 0)
    {
        m_udpReceiveThread.reset(new UdpReceiveThread(*this, udpRxInterface));
    }

    EXIT();
}

int UdpSocket::GetFd()
{
    ENTER();

    RETURN(m_fd);
}
