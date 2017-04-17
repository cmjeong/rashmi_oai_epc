///////////////////////////////////////////////////////////////////////////////
//
// MessagingConnectionReq.cpp
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
#include <system/SerialisationIds.h>
#include <system/NumberConversions.h>
#include <system/Trace.h>
#include <string.h> // for memcpy
#include <StaticDecode.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingConnectionReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MessagingConnectionReq::MessagingConnectionReq(MessagingConnectionIdentifier localId, threeway::Serialisable& payloadMsg) :
    m_sourceConnId(localId),
    m_payloadMsg(&payloadMsg),
    m_payloadData(NULL),
    m_payloadDataLen(0),
    m_serialisationId(0)
{
    ENTER();

    EXIT();
}

MessagingConnectionReq::MessagingConnectionReq() :
    m_sourceConnId(ConnectionIdentifierUnused),
    m_payloadMsg(NULL),
    m_payloadData(NULL),
    m_payloadDataLen(0),
    m_serialisationId(0)
{
    ENTER();

    EXIT();
}

MessagingConnectionReq::~MessagingConnectionReq()
{
    ENTER();

    if(m_payloadData != NULL)
    {
        delete[] m_payloadData;
    }
    EXIT();
}

s32 MessagingConnectionReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise to:
    //   4 bytes - connection Id
    //   4 bytes - payload serialisation id
    //   4 bytes - payload Length
    //   n bytes - payload

    const u32 headerLen = 12; // 3 * u32 as above

    TRACE("MessagingConnectionReq::Serialise", dataMaxBytes);

    if (m_payloadMsg && (dataMaxBytes >= headerLen) &&
        (dataMaxBytes <= (MESSENGER_MAX_SERIALISED_PACKET_LEN-headerLen)))
    {
        U32ToBigEndianByteArray((u32)m_sourceConnId, &data[0]);
        U32ToBigEndianByteArray(m_payloadMsg->GetSerialisationId(), &data[4]);
        s32 payloadDataLen = m_payloadMsg->Serialise(&data[headerLen], dataMaxBytes - headerLen);
        if (payloadDataLen > 0)
        {
            // poke the payload length in once we've found it out from Serialise
            U32ToBigEndianByteArray((u32)payloadDataLen, &data[8]);
            TRACE("MessagingConnectionReq::Serialise", headerLen + (u32)payloadDataLen);
            RETURN(headerLen + (u32)payloadDataLen);
        }
    }

    RETURN(-1);
}

bool MessagingConnectionReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // DeSerialise from:
    //   4 bytes - connection Id
    //   4 bytes - payload serialisation id
    //   4 bytes - payload Length
    //   n bytes - payload

    const u32 headerLen = 12; // 3 * u32 as above

    if(dataLen >= headerLen)
    {
        m_sourceConnId = (MessagingConnectionIdentifier)BigEndianByteArrayToU32(&data[0]);
        m_serialisationId = BigEndianByteArrayToU32(&data[4]);
        m_payloadDataLen = BigEndianByteArrayToU32(&data[8]);
        m_payloadData = NULL;
        // is there an embedded message?
        if (m_payloadDataLen > 0)
        {
            // sanity check the received length
            if ((m_payloadDataLen <= (dataLen-headerLen)) &&
                (m_payloadDataLen <= (MESSENGER_MAX_SERIALISED_PACKET_LEN-headerLen)))
            {
                m_payloadData = new u8[m_payloadDataLen];
                memcpy(m_payloadData, &data[headerLen], m_payloadDataLen);
                RETURN(true);
            }
            else
            {
                TRACE_PRINTF("Failed to deserialise MessagingConnectionReq - data length too large, dataLen=%" PRIu32 ", m_payloadDataLen=%" PRIu32, dataLen, m_payloadDataLen);
            }
        }
    }
    else
    {
        TRACE_PRINTF("Failed to deserialise MessagingConnectionReq - wrong data length, dataLen=%" PRIu32, dataLen);
    }

    RETURN(false);
}

string MessagingConnectionReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "MessagingConnectionReq: ";
    stream << "connectionId=" << (u32)m_sourceConnId;
    stream << " serialisationId=" <<m_serialisationId << endl;

    if(m_payloadMsg)
    {
        stream << m_payloadMsg->ToString();
    }
    else
    {
        shared_ptr<Serialisable> msg = DeserialiseMessageBytes(m_serialisationId,
                                                               m_payloadData,
                                                               m_payloadDataLen);
        if(msg)
        {
            stream << "{" << endl << "  " << msg->ToString() << endl << "}";
        }
    }

    RETURN(stream.str());
}

string MessagingConnectionReq::ToBriefString() const
{
    ENTER();

    ostringstream stream;

    if(m_payloadMsg)
    {
        RETURN(m_payloadMsg->ToBriefString());
    }
    else
    {
        shared_ptr<Serialisable> msg = DeserialiseMessageBytes(m_serialisationId,
                                                               m_payloadData,
                                                               m_payloadDataLen);
        if(msg)
        {
            RETURN(msg->ToBriefString());
        }
    }

    RETURN(stream.str());
}

