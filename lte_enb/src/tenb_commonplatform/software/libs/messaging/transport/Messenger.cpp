///////////////////////////////////////////////////////////////////////////////
//
// Messenger.cpp
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

// Uncomment this to turn on extra message tracing
// #define MESSENGER_EXTRA_DEBUG

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string.h>
#include <system/Trace.h>
#include <system/Serialisable.h>
#include <system/NumberConversions.h>
#include <system/HexString.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Messenger.h"
#include "clog.h"

using namespace std;
using namespace boost;
using namespace threeway;

// Make the CLogger API functions weak
//  Any apps not linked/dynamically linked against libRadisys-clog will end
//  up with these functions being NULL and clogging will be skipped.
__attribute__((__weak__)) void ClogInit(void);
__attribute__((__weak__)) bool ClogAlloc(const clog_msg_type_t type, uint16_t len, union clog_msg_data **buf);
__attribute__((__weak__)) bool ClogZalloc(const clog_msg_type_t type, uint16_t len, union clog_msg_data **buf);
__attribute__((__weak__)) void ClogFree(union clog_msg_data *buf);

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Messenger::Messenger() :
    m_messageRxRawInterface(NULL)
{
    ENTER();

    if(ClogInit != NULL)
    {
        ClogInit();
    }

    EXIT();
}

Messenger::Messenger(MessageRxRawInterface* messageRxRawInterface) :
    m_messageRxRawInterface(messageRxRawInterface)
{
    ENTER();

    if(ClogInit != NULL)
    {
        ClogInit();
    }

    EXIT();
}

Messenger::~Messenger()
{
    ENTER();

    EXIT();
}

bool Messenger::SendMessage(const Serialisable& message, MessagingEntity fromEntity,
        MessagingEntity toEntity) const
{
    ENTER();

    u8 messagePacket[MESSENGER_MAX_SERIALISED_PACKET_LEN];
    u32 pktLen = 0;

    // Add the from entity.
    U32ToBigEndianByteArray(fromEntity, &(messagePacket[pktLen]));
    pktLen += 4;

    // Add the to entity.
    U32ToBigEndianByteArray(toEntity, &(messagePacket[pktLen]));
    pktLen += 4;

    // And a u32 to say what sort of serialised data.
    u32 serialisationId = message.GetSerialisationId();
    U32ToBigEndianByteArray(serialisationId, &(messagePacket[pktLen]));
    pktLen += 4;

    // Check that header length (and hence available payload space) hasn't changed
    RSYS_ASSERT (pktLen == MESSENGER_SERIALISED_PACKET_HEADER_LEN) ;

    // Add the serialisation data.
    s32 serialiseDataLen = message.Serialise(&(messagePacket[pktLen]),
            sizeof(messagePacket) - pktLen);
    if (serialiseDataLen < 0)
    {
        TRACE_MSG_LEV(TRACE_WARNING, "Messenger: Failed to serialise message.");
        RETURN(false);
    }

    // Update packet length.
    pktLen += (u32)serialiseDataLen;

    RSYS_ASSERT(pktLen <= MESSENGER_MAX_SERIALISED_PACKET_LEN);

    // Do we have a route for the destination entity?
    s32 sendResult;
    MessageRouteEntry route;
    if (m_routingTable.GetRoute(toEntity, route))
    {
#ifdef MESSENGER_EXTRA_DEBUG
        TRACE_PRINTF("Routing msg id=%" PRIu32 " len=%" PRIu32 " to %s", serialisationId, pktLen, route.ToString().c_str());
#endif
        sendResult = SendRoutedPacket(route, messagePacket, pktLen);
    }
    else
    {
        // Send via the default route in the derived class
        sendResult = SendPacket(messagePacket, pktLen);
    }

    RSYS_ASSERT_PRINTF(sendResult == (s32)pktLen, "Messenger: Failed to send message, send packet function returned %" PRId32 ", expected %" PRIu32, sendResult, pktLen);

#ifdef MESSENGER_EXTRA_DEBUG
    TRACE_PRINTF("Messenger: Sent message, serialisationId=%" PRIu32 ", len=%" PRIu32 ", fromEntity=%" PRIu32 ", toEntity=%" PRIu32, message.GetSerialisationId(), pktLen, fromEntity, toEntity);
#endif

    RETURN(true);
}

bool Messenger::IsRouteAvailable(const MessagingEntity& entity)
{
    ENTER();

    RETURN(m_routingTable.IsEntityPresent(entity));
}

void Messenger::HandleReceivedPacket(const u8 * packet, u32 packetLen)
{
    ENTER();

    if (packetLen > 0)
    {
#ifdef MESSENGER_EXTRA_DEBUG
        TRACE_PRINTF("Message received, len=%" PRIu32, packetLen);
#endif

        if (packetLen >= 12 /* 4 bytes fromEntity, 4 bytes toEntity, 4 bytes serialisationId */)
        {
            u32 packetPos = 0;

            MessagingEntity fromEntity = (MessagingEntity)BigEndianByteArrayToU32(&(packet[packetPos]));
            packetPos += 4;

            MessagingEntity toEntity = (MessagingEntity)BigEndianByteArrayToU32(&(packet[packetPos]));
            packetPos += 4;

            u32 serialisationId = BigEndianByteArrayToU32(&(packet[packetPos]));
            packetPos += 4;

            u32 serialisedDataLen = packetLen - packetPos;

            // Pass to clogger
            union clog_msg_data *clog;
            if(ClogAlloc != NULL && ClogAlloc(CLOG_MSG_MESSENGER, packetLen, &clog))
            {
                memcpy(clog, packet, packetLen);
                ClogFree(clog);
            }

            // Intercept the message routing table update here
            if (SERIALISATION_ID_MESSAGING_ROUTE_IND == serialisationId)
            {
                shared_ptr<MessagingRouteInd> msgRouteInd;
                msgRouteInd = Serialisable::DeSerialise<MessagingRouteInd>(&(packet[packetPos]), serialisedDataLen);
                if (msgRouteInd != NULL)
                {
                    HandleReceivedRoutingTableUpdate(*msgRouteInd);
                }
            }
            else if (m_messageRxRawInterface)
            {
                m_messageRxRawInterface->ReceiveMessage(
                        fromEntity, toEntity, serialisationId,
                        &(packet[packetPos]), serialisedDataLen);
            }
            else
            {
                HandleUnhandledReceivedSerialisedData(fromEntity, toEntity, serialisationId, &(packet[packetPos]), serialisedDataLen);
            }
        }
        else
        {
            RSYS_ASSERT_FAIL("Messenger: Received message too short %"PRIu32, (u32)packetLen);
        }
    }

    EXIT();
}

void Messenger::HandleReceivedRoutingTableUpdate(MessagingRouteInd& msgRouteInd)
{
#ifdef MESSENGER_EXTRA_DEBUG
    TRACE_MSG(msgRouteInd.GetRoutingTable().ToString().c_str());
#else
    TRACE_MSG("Received message routing table update");
#endif
    m_routingTable = msgRouteInd.GetRoutingTable();
}
