///////////////////////////////////////////////////////////////////////////////
//
// ServerIPInterface.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <comms/UdpSocket.h>
//#include <comms/TOSValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "NTPPacket.h"
#include "ServerIPInterface.h"
#include "NtpClientApplication.h"

using namespace std;

IPv4Address ServerIPInterface::m_fgwIPSecAddress = "0.0.0.0";
bool ServerIPInterface::m_IPSecEnabled = false;

IPv4Address& ServerIPInterface::GetIPAddr(void)
{
    return m_ntpServerIpAddress;
}

void ServerIPInterface::SetIpAddress(const IPv4Address& ntpServerIpAddress)
{
    if (!(ntpServerIpAddress == m_ntpServerIpAddress))
    {
        m_ntpServerIpAddress = ntpServerIpAddress;

        if(m_ntpServerIpAddress == "0.0.0.0")
        {
            m_socketAddressValid = false;
        }
        else
        {
            m_socketAddressValid = true;
        }

        m_socketActive = false;
        m_socketChanged = true;
    }
}

bool ServerIPInterface::ReopenSocketIfChanged()
{
    if(m_socketChanged)
    {
        InitSocket();

        // OK, so let's check if the socket init has really succeeded
        // else keep the flag up like before
        if (m_ntpSocket->GetFd() <= 0)
        {
            // We don't have a good socket yet so we'll try this whole process
            // again when the next message is up for transmission
            TRACE_PRINTF("ServerIPInterface::ReopenSocketIfChanged() - tried to create an UDP socket to send, but it failed, Can't send packets at the moment\n");
            m_socketChanged = true;
            return false;
        }
        else
        {
            m_socketChanged = false;
        }
    }

    return true;
}

void ServerIPInterface::InitSocket()
{
    RSYS_ASSERT(m_socketAddressValid);

    if ( NtpClientApplication::GetInstance().IsQosEnabled() )
    {
        m_ntpSocket.reset(new UdpSocket(m_fgwIPSecAddress,  (u16) 0, m_ntpServerIpAddress, (u16) NTP_PORT, *this, QOS_CLASS_A, true));
    }
    else
    {
        m_ntpSocket.reset(new UdpSocket(m_fgwIPSecAddress,  (u16) 0, m_ntpServerIpAddress, (u16) NTP_PORT, *this, QOS_NONE, true));
    }
}

eServerIPErrors ServerIPInterface::SendGetNTPPacket(NtpPacket* NTPPacket,long double* sendTime,long double* receiveTime)
{
    RSYS_ASSERT(!(m_ntpSocket == NULL));

    u32 sentPacketBytes = 0;
    u32 receivedPacketBytes = 0;
    u32 pktSize = sizeof(NtpData);

    *sendTime = GetLDTime(); //get and note send time
    sentPacketBytes = m_ntpSocket->UdpSend(NTPPacket->GetPktBuff(), pktSize); //send NTP packet

    if (sentPacketBytes != pktSize)
    {
        TRACE_PRINTF("ServerIPInterface::SendGetNTPPacket Send failed rc = %d, errno = %02X %s",sentPacketBytes,errno,strerror(errno));
        m_socketActive = false;
        return SERVER_IP_ERROR_SEND;
    }
    else
    {
        struct timeval timeout;
        //recieve from the NTP server with a timeout
        timeout.tv_sec = 6;
        timeout.tv_usec = 0;
        if (setsockopt((m_ntpSocket->GetFd()), SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(struct timeval)) < 0)
        {
            TRACE_PRINTF("ServerIPInterface::SendGetNTPPacket: setsockopt() failed, errno = %02X %s", errno, strerror(errno));
            m_socketActive = false;
            return SERVER_IP_ERROR_SETSOCKOPT;
        }
        int txFd = m_ntpSocket->GetFd();
        receivedPacketBytes = recvfrom(txFd, (void*) NTPPacket->GetPktBuff(), (int)pktSize, 0, NULL, NULL);
        //get and record the time of reception of the packet
        *receiveTime = GetLDTime();
        if (receivedPacketBytes != pktSize)
        {
            TRACE_PRINTF("ServerIPInterface::SendGetNTPPacket Error receiving packet. rc = %d errno = %d, %s",receivedPacketBytes,errno,strerror(errno));
            m_socketActive = false;
            return SERVER_IP_ERROR_RECEIVE;
        }

        if(NTPPacket->IsItAKODPacket())
        {
            m_socketActive = false;
            return SERVER_ERROR_KOD;
        }
    }

    m_socketActive = true;
    return SERVER_IP_ERROR_NONE;
}
