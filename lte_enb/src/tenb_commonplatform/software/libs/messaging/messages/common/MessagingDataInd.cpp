///////////////////////////////////////////////////////////////////////////////
//
// MessagingDataInd.cpp
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
#include <system/NumberConversions.h>
#include <system/Trace.h>
#include <string.h>
#include <StaticDecode.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingDataInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MessagingDataInd::MessagingDataInd(MessagingConnectionIdentifier localId,
                                   MessagingConnectionIdentifier remoteId,
                                   threeway::Serialisable& payloadMsg) :
    m_sourceConnId(localId),
    m_destConnId(remoteId),
    m_payloadMsg(&payloadMsg),
    m_payloadData(NULL),
    m_payloadDataLen(0),
    m_serialisationId(0),
    m_hasClonedData(false)
{
    ENTER();

    EXIT();
}

MessagingDataInd::MessagingDataInd() :
    m_sourceConnId(ConnectionIdentifierUnused),
    m_destConnId(ConnectionIdentifierUnused),
    m_payloadMsg(NULL),
    m_payloadData(NULL),
    m_payloadDataLen(0),
    m_serialisationId(0),
    m_hasClonedData(false)
{
    ENTER();

    EXIT();
}

MessagingDataInd::~MessagingDataInd()
{
    ENTER();

    if (m_hasClonedData)
    {
        // Delete the cloned data
        delete [] m_payloadData;
    }

    EXIT();
}

bool MessagingDataInd::Clone()
{
    ENTER();

    if (m_payloadMsg)
    {
        // If called more than once...
        if (m_hasClonedData)
        {
            delete [] m_payloadData;
        }

        m_payloadData = new u8[MESSENGER_MAX_SERIALISED_PACKET_LEN];

        s32 serialiseDataLen = m_payloadMsg->Serialise(m_payloadData, MESSENGER_MAX_SERIALISED_PACKET_LEN);
        if (serialiseDataLen > 0)
        {
            m_serialisationId = m_payloadMsg->GetSerialisationId();
            m_payloadDataLen  = serialiseDataLen;
            m_hasClonedData   = true;
        }
        else
        {
            delete [] m_payloadData;
            m_hasClonedData = false;
        }
    }

    RETURN(m_hasClonedData);
}

s32 MessagingDataInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise to:
    //   4 bytes - source connection Id
    //   4 bytes - destination connection Id
    //   4 bytes - payload serialisation Id
    //   4 bytes - payload length
    //   n bytes - payload

    const u32 headerLen = 16; // 4 * u32 as above

    if (m_payloadMsg && (dataMaxBytes >= headerLen) &&
        (dataMaxBytes >= (MESSENGER_MAX_SERIALISED_PACKET_LEN-headerLen)))
    {
        U32ToBigEndianByteArray((u32)m_sourceConnId, &data[0]);
        U32ToBigEndianByteArray((u32)m_destConnId, &data[4]);

        if (m_hasClonedData)
        {
            if (m_payloadDataLen <= (dataMaxBytes - headerLen))
            {
                // Just copy the already serialised data
                U32ToBigEndianByteArray(m_serialisationId, &data[8]);
                U32ToBigEndianByteArray(m_payloadDataLen, &data[12]);
                memcpy(&data[headerLen], m_payloadData, m_payloadDataLen);
                RETURN(headerLen + m_payloadDataLen);
            }
        }
        else
        {
            U32ToBigEndianByteArray(m_payloadMsg->GetSerialisationId(), &data[8]);
            s32 payloadDataLen = m_payloadMsg->Serialise(&data[headerLen], dataMaxBytes - headerLen);
            if (payloadDataLen > 0)
            {
                // poke the payload length in once we've found it out from Serialise
                U32ToBigEndianByteArray((u32)payloadDataLen, &data[12]);
                RETURN(headerLen + (u32)payloadDataLen);
            }
        }
    }

    RETURN(-1);
}

bool MessagingDataInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // DeSerialise from:
    //   4 bytes - source connection Id
    //   4 bytes - destination connection Id
    //   4 bytes - payload serialisation Id
    //   4 bytes - payload length
    //   n bytes - payload

    const u32 headerLen = 16; // 4 * u32 as above

    if(dataLen >= headerLen)
    {
        m_sourceConnId = (MessagingConnectionIdentifier)BigEndianByteArrayToU32(&data[0]);
        m_destConnId = (MessagingConnectionIdentifier)BigEndianByteArrayToU32(&data[4]);
        m_serialisationId = BigEndianByteArrayToU32(&data[8]);
        m_payloadDataLen = BigEndianByteArrayToU32(&data[12]);
        // is there an embedded message?
        if (m_payloadDataLen > 0)
        {
            // sanity check the received length
            if ((m_payloadDataLen <= (dataLen-headerLen)) &&
                (m_payloadDataLen <= (MESSENGER_MAX_SERIALISED_PACKET_LEN-headerLen)))
            {
                m_payloadData = new u8[m_payloadDataLen];
                memcpy(m_payloadData, &data[headerLen], m_payloadDataLen);
                m_hasClonedData = true;  // To ensure destructor cleans up
                RETURN(true);
            }
            else
            {
                TRACE_PRINTF("Failed to deserialise MessagingDataInd - data length too large, dataLen=%" PRIu32, dataLen);
            }
        }
        else
        {
            TRACE_MSG("Failed to deserialise MessagingDataInd - empty message");
        }
    }
    else
    {
        TRACE_PRINTF("Failed to deserialise MessagingDataInd - wrong data length, dataLen=%" PRIu32, dataLen);
    }

    RETURN(false);
}

string MessagingDataInd::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "MessagingDataInd: ";
    stream << "sourceConnectionId=" << (u32)m_sourceConnId;
    stream << ", destConnectionId=" << (u32)m_destConnId << endl;

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


string MessagingDataInd::ToBriefString() const
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

