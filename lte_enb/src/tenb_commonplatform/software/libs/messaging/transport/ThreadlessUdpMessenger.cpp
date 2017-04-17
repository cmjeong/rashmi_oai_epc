///////////////////////////////////////////////////////////////////////////////
//
// ThreadlessUdpMessenger.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <system/SerialisedData.h>
#include <comms/networking.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ThreadlessUdpMessenger.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ThreadlessUdpMessenger::ThreadlessUdpMessenger(SelectorRegisterInterface& selector,
                                               u16 localPort,
                                               IPv4Address remoteIpAddress,
                                               u16 remotePort,
                                               MessageRxRawInterface* messageRxRawInterface ) :
    Messenger(messageRxRawInterface),
    m_udpSocket(selector, *this, localPort, remoteIpAddress, remotePort)
{
    ENTER ();

    EXIT ();
}


ThreadlessUdpMessenger::~ThreadlessUdpMessenger()
{
    ENTER ();

    EXIT ();
}

void ThreadlessUdpMessenger::StartReceiving()
{
    ENTER ();

    m_udpSocket.StartReceiving();

    EXIT ();
}

void ThreadlessUdpMessenger::SwitchToPolledMode()
{
    ENTER();
    EXIT();
}

void ThreadlessUdpMessenger::RestoreCallbackMode()
{
    ENTER();
    EXIT();
}

shared_ptr<SerialisedData> ThreadlessUdpMessenger::BlockingReceiveMessage(
        u32 timeoutMilliSecs,
        MessagingEntity& fromEntity,
        MessagingEntity& toEntity)
{
    u8 packet[MESSENGER_MAX_SERIALISED_PACKET_LEN];

    shared_ptr<SerialisedData> msg;
    fromEntity = ENTITY_INVALID;
    toEntity = ENTITY_INVALID;

    TRACE_PRINTF("Blocking receive - no timeout in ThreadlessUdpMessenger");

    // Receive the UDP packet.
    int packetLen = recvfrom(m_udpSocket.GetFd(), packet, sizeof(packet), 0, NULL, NULL);

    if (packetLen > 0)
    {

        if (packetLen >= 12 /* 4 bytes fromEntity, 4 bytes toEntity, 4 bytes serialisationId */)
        {
            u32 packetPos = 0;

            fromEntity = (MessagingEntity)BigEndianByteArrayToU32(&(packet[packetPos]));
            packetPos += 4;

            toEntity = (MessagingEntity)BigEndianByteArrayToU32(&(packet[packetPos]));
            packetPos += 4;

            u32 serialisationId = BigEndianByteArrayToU32(&(packet[packetPos]));
            packetPos += 4;

            u32 serialisedDataLen = packetLen - packetPos;

            msg.reset(new SerialisedData(serialisationId, &(packet[packetPos]), serialisedDataLen));
        }
        else
        {
            RSYS_ASSERT_FAIL("Received message too short %"PRIu32, (u32)packetLen);
        }
    }

    return msg;
}


s32 ThreadlessUdpMessenger::SendPacket(const u8 * packet, u32 packetLen) const
{
    ENTER();

    RETURN(m_udpSocket.UdpSend(packet, packetLen));
}

s32 ThreadlessUdpMessenger::SendRoutedPacket(MessageRouteEntry& route, const u8 * packet, u32 packetLen) const
{
    ENTER();

    RETURN(m_udpSocket.UdpSendTo(route.GetIpAddress(), route.GetPort(), packet, packetLen));
}

void ThreadlessUdpMessenger::HandleUnhandledReceivedSerialisedData(MessagingEntity& fromEntity,
                                                                   MessagingEntity& toEntity,
                                                                   u32 serialisationId,
                                                                   const u8 * serialisedData,
                                                                   u32 serialisedDataLen)
{
    SerialisedData serialisedDataObj(serialisationId, serialisedData, serialisedDataLen);

    RSYS_ASSERT_FAIL("Threadless messenger should always have messages handled in base class! %s", serialisedDataObj.ToString().c_str());
}

void ThreadlessUdpMessenger::HandleUdpRx(s32 fd)
{
    ENTER ();

    u8 packet[MESSENGER_MAX_SERIALISED_PACKET_LEN];

    // Receive the UDP packet.
    int packetLen = recvfrom(fd, packet, sizeof(packet), 0, NULL, NULL);

    if(packetLen > 0)
    {
        // Get the base class to handle it and call the client with the message.
        HandleReceivedPacket(packet, packetLen);
    }
    else
    {
        TRACE_LEV(TRACE_WARNING, "UdpMessengerWithSelect::HandleUdpRx(): packetLen", (s32)packetLen);
    }

    EXIT ();
}
