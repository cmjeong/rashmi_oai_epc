///////////////////////////////////////////////////////////////////////////////
//
// UdpMessenger.cpp
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
#include <comms/networking.h>
#include <system/SerialisedData.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UdpMessenger.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

UdpMessenger::UdpMessenger(IPv4Address remoteIpAddress, u16 remotePort) :
    Messenger(),
    m_savedMessageRxRawInterface(NULL),
    m_udpSocket(remoteIpAddress, remotePort)
{
    ENTER ();

    Initialise();

    EXIT ();
}

UdpMessenger::UdpMessenger(u16 localPort,
                           MessageRxRawInterface* messageRxRawInterface) :
    Messenger(messageRxRawInterface),
    m_savedMessageRxRawInterface(messageRxRawInterface),
    m_udpSocket(localPort, *this)
{
    ENTER ();

    Initialise();

    EXIT ();
}

UdpMessenger::UdpMessenger(u16 localPort, IPv4Address remoteIpAddress, u16 remotePort,
                           MessageRxRawInterface* messageRxRawInterface) :
    Messenger(messageRxRawInterface),
    m_savedMessageRxRawInterface(messageRxRawInterface),
    m_udpSocket(localPort, remoteIpAddress, remotePort, *this)
{
    ENTER ();

    Initialise();

    EXIT ();
}

UdpMessenger::UdpMessenger(u16 localPort, IPv4Address remoteIpAddress, u16 remotePort) :
    Messenger(NULL),
    m_savedMessageRxRawInterface(NULL),
    m_udpSocket(localPort, remoteIpAddress, remotePort, *this)
{
    ENTER ();

    Initialise();

    EXIT ();
}

UdpMessenger::~UdpMessenger()
{
    ENTER ();

    // m_udpSocket goes out of scope so the UDP receive thread is stopped and
    // the UDP socket closed.  And everybody's happy.

    EXIT ();
}

void UdpMessenger::StartReceiving()
{
    ENTER ();

    m_udpSocket.StartReceiving();

    EXIT ();
}

void UdpMessenger::SwitchToPolledMode()
{
    ENTER();

    if (m_messageRxRawInterface)
    {
        TRACE_PRINTF("Messenger switched to polled mode.")
        // Ensure the queue is cleared from any previous usage
        Thread::LockMutex(m_messageQueueMutex);
        while (!m_messageQueue.empty())
        {
            m_messageQueue.pop();
        }
        Thread::UnlockMutex(m_messageQueueMutex);

        // And switch by removing the callback
        m_messageRxRawInterface = NULL;
    }

    EXIT();
}

void UdpMessenger::RestoreCallbackMode()
{
    ENTER();

    if (m_savedMessageRxRawInterface)
    {
        TRACE_PRINTF("Messenger restored to callback mode.")
        m_messageRxRawInterface = m_savedMessageRxRawInterface;
    }

    EXIT();
}

boost::shared_ptr<SerialisedData> UdpMessenger::BlockingReceiveMessage(u32 timeoutMilliSecs,
                                                                       MessagingEntity& fromEntity,
                                                                       MessagingEntity& toEntity)
{
    // No ENTER/EXIT as this is often called in a tight loop.

    RSYS_ASSERT(m_messageRxRawInterface == NULL);

    MessageQueueItem dequeuedMessage;

    Thread::LockMutex(m_messageQueueMutex);

    struct timespec absTimeout;
    Thread::ConditionGetAbsTimeout(timeoutMilliSecs, &absTimeout);

    while (m_messageQueue.empty())
    {
        // The timed wait function may return before the timeout even if
        // there is nothing on the queue.  Hence we keep checking whether
        // the queue is empty.  The timeout is absolute so we don't need
        // to recalculate it each time.
        if (Thread::ConditionTimedWait(m_messageQueueCondition,
                m_messageQueueMutex, &absTimeout))
        {
            // Timed out
            Thread::UnlockMutex(m_messageQueueMutex);
            fromEntity = ENTITY_INVALID;
            toEntity = ENTITY_INVALID;
            return dequeuedMessage.message; // Will be NULL.
        }
    }

    // Queue is not empty so grab the message off the front.
    dequeuedMessage = m_messageQueue.front();
    // Then remove it from the queue.
    m_messageQueue.pop();

    Thread::UnlockMutex(m_messageQueueMutex);

#ifdef MESSENGER_EXTRA_DEBUG
    TRACE_PRINTF("Messenger: Dequeued received message, serialisationId=%" PRIu32,
                    dequeuedMessage.message->GetSerialisationId());
#endif

    // Return the entities and pass through values.
    fromEntity = dequeuedMessage.fromEntity;
    toEntity = dequeuedMessage.toEntity;

    return dequeuedMessage.message;
}

s32 UdpMessenger::SendPacket(const u8 * packet, u32 packetLen) const
{
    ENTER();

    RETURN(m_udpSocket.UdpSend(packet, packetLen));
}

s32 UdpMessenger::SendRoutedPacket(MessageRouteEntry& route, const u8 * packet, u32 packetLen) const
{
    ENTER();

    RETURN(m_udpSocket.UdpSendTo(route.GetIpAddress(), route.GetPort(), packet, packetLen));
}

void UdpMessenger::HandleUdpRx(s32 fd)
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
        TRACE_LEV(TRACE_WARNING, "UdpMessenger::HandleUdpRx(): packetLen", (s32)packetLen);
    }

    EXIT ();
}

void UdpMessenger::HandleUnhandledReceivedSerialisedData(MessagingEntity& fromEntity,
                                                         MessagingEntity& toEntity,
                                                         u32 serialisationId,
                                                         const u8 * serialisedData,
                                                         u32 serialisedDataLen)
{
    ENTER();

    MessageQueueItem messageQueueItem;

    // Set up structure for putting on queue.
    messageQueueItem.message.reset(new SerialisedData(serialisationId, serialisedData, serialisedDataLen));
    messageQueueItem.fromEntity = fromEntity;
    messageQueueItem.toEntity = toEntity;

    // Stick it on our queue and signal to polled ReceiveMessage method
    // in case it is waiting for one.

    Thread::LockMutex(m_messageQueueMutex);

    // Put it on the queue.
    m_messageQueue.push(messageQueueItem);

    // Signal to receive function that there is a message waiting.
    Thread::ConditionSignal(m_messageQueueCondition);

    Thread::UnlockMutex(m_messageQueueMutex);

    EXIT();
}

void UdpMessenger::Initialise()
{
    ENTER();

    Thread::InitialiseMutex(m_messageQueueMutex);
    Thread::ConditionInit(m_messageQueueCondition);
    m_udpSocket.CloseOnExec();

    EXIT();
}
