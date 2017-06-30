///////////////////////////////////////////////////////////////////////////////
//
// MessagingReleaseConf.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingReleaseConf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MessagingReleaseConf::MessagingReleaseConf(MessagingConnectionIdentifier localId, MessagingConnectionIdentifier remoteId) :
    m_sourceConnId(localId),
    m_destConnId(remoteId)
{
    ENTER();

    EXIT();
}

MessagingReleaseConf::MessagingReleaseConf() :
    m_sourceConnId(ConnectionIdentifierUnused),
    m_destConnId(ConnectionIdentifierUnused)
{
    ENTER();

    EXIT();
}

MessagingReleaseConf::~MessagingReleaseConf()
{
    ENTER();
    EXIT();
}

s32 MessagingReleaseConf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise to:
    //   4 bytes - source connection Id
    //   4 bytes - destination connection Id

    if (dataMaxBytes >= 8)
    {
        U32ToBigEndianByteArray((u32)m_sourceConnId, &data[0]);
        U32ToBigEndianByteArray((u32)m_destConnId, &data[4]);
        RETURN(8);
    }

    RETURN(-1);
}

bool MessagingReleaseConf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // DeSerialise from:
    //   4 bytes - source connection Id
    //   4 bytes - destination connection Id

    if(dataLen == 8)
    {
        m_sourceConnId = (MessagingConnectionIdentifier)BigEndianByteArrayToU32(&data[0]);
        m_destConnId = (MessagingConnectionIdentifier)BigEndianByteArrayToU32(&data[4]);
        RETURN(true);
    }
    else
    {
        TRACE_PRINTF("Failed to deserialise MessagingReleaseConf - wrong data length, dataLen=%" PRIu32, dataLen);
    }

    RETURN(false);
}

string MessagingReleaseConf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "MessagingReleaseConf: ";
    stream << "sourceConnectionId=" << (u32)m_sourceConnId;
    stream << ", destConnectionId=" << (u32)m_destConnId;

    RETURN(stream.str());
}
