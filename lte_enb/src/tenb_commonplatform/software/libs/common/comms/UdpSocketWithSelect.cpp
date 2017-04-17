///////////////////////////////////////////////////////////////////////////////
//
// UdpSocketWithSelect.cpp
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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UdpSocketWithSelect.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

UdpSocketWithSelect::UdpSocketWithSelect(SelectorRegisterInterface& selector,
                                         UdpRxInterface& udpRxInterface,
                                         u16 localPort,
                                         const IPv4Address& remoteIpAddress,
                                         u16 remotePort) :
    m_selector(selector),
    m_udpRxInterface(udpRxInterface),
    m_localIpAddress("0.0.0.0"),
    m_localPort(localPort),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_fd(-1)
{
    ENTER ();

    // Make sure all member vars are initialised sensibly.
    memset(&m_txSockAddr, 0, sizeof (struct sockaddr_in));

    // Initialise both receive and transmit.
    InitialiseTransmit();

    CloseOnExec();

    EXIT ();
}

UdpSocketWithSelect::~UdpSocketWithSelect()
{
    ENTER ();

    // And close the transmit socket.
    if(m_fd >= 0)
    {
        close(m_fd);
    }

    EXIT ();
}

void UdpSocketWithSelect::SelectCallBack()
{
    ENTER();

    m_udpRxInterface.HandleUdpRx(m_fd);

    EXIT();
}

void UdpSocketWithSelect::StartReceiving()
{
    ENTER ();

    struct sockaddr_in addr;

    if(m_localPort != 0)
    {
        TRACE("  Local port", (u32)m_localPort);
    }

    // No FD supplied so open and bind a socket.
    if(m_fd < 0)
    {
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

        int bindResult = bind(m_fd, (struct sockaddr*)&addr, sizeof(addr));
        RSYS_ASSERT(bindResult == 0);
        TRACE_PRINTF("Successful UDP Rx bind(%u:%u)",ntohl(addr.sin_addr.s_addr),m_localPort);
    }

    m_selector.RegisterFD(m_fd, *this);

    EXIT ();
}

void UdpSocketWithSelect::StopReceiving()
{
    ENTER ();

    // TODO: what to do here?  Call m_selector.DeRegisterFd()

    EXIT ();
}

void UdpSocketWithSelect::CloseOnExec()
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

s32 UdpSocketWithSelect::UdpSend(const u8* packet, u32 packetLen) const
{
    ENTER ();

    RSYS_ASSERT_PRINTF(m_txSockAddr.sin_addr.s_addr != 0, "%s", ToString().c_str());
    RSYS_ASSERT_PRINTF(m_fd >= 0, "%s", ToString().c_str());

    // Under C++ you don't get the funky transparent union for sockaddr/sockaddr_in so have to cast.
    struct sockaddr * txSockAddr = (sockaddr *) &m_txSockAddr;

    s32 result = sendto(m_fd, packet, packetLen, 0 /* flags */, txSockAddr, sizeof(m_txSockAddr));

    RETURN (result);
}

s32 UdpSocketWithSelect::UdpSendTo(const IPv4Address& remoteIpAddress, u16 remotePort, const u8* packet, u32 packetLen) const
{
    ENTER ();

    RSYS_ASSERT_PRINTF(remoteIpAddress.IsSet(), "%s", ToString().c_str());
    RSYS_ASSERT_PRINTF(m_fd >= 0, "%s", ToString().c_str());

    u32 ipAddress;
    remoteIpAddress.Get(ipAddress);

    // Setup destination.
    struct sockaddr_in txSockAddr;
    txSockAddr.sin_family      = AF_INET;
    txSockAddr.sin_port        = htons(remotePort);
    txSockAddr.sin_addr.s_addr = ipAddress;

    s32 result = sendto(m_fd, packet, packetLen, 0 /* flags */,
                        (sockaddr *)&txSockAddr, // Under C++ you don't get the funky transparent union for sockaddr/sockaddr_in so have to cast.
                        sizeof(txSockAddr));

    RETURN (result);
}

string UdpSocketWithSelect::ToString() const
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

void UdpSocketWithSelect::InitialiseTransmit()
{
    ENTER();

    // Open transmit socket.
    m_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    RSYS_ASSERT_PRINTF(m_fd >= 0, "%s", ToString().c_str());

    TRACE("UDP socket opened", ToString().c_str());

    int reuse = 1;
    if ( setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0 )
    {
        TRACE_MSG_LEV(TRACE_WARNING, "Failed SO_REUSEADDR call");
    }

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
            TRACE_MSG_LEV(TRACE_CRITICAL, "Failed to bind in UdpSocketWithSelect::InitialiseTransmit()");
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
