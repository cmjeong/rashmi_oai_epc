///////////////////////////////////////////////////////////////////////////////
//
// MessagingConnectionRef.cpp
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

#include "MessagingConnectionRef.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MessagingConnectionRef::MessagingConnectionRef(MessagingConnectionIdentifier remoteId) :
    m_destConnId(remoteId)
{
    ENTER();

    EXIT();
}

MessagingConnectionRef::MessagingConnectionRef() :
    m_destConnId(ConnectionIdentifierUnused)
{
    ENTER();

    EXIT();
}

MessagingConnectionRef::~MessagingConnectionRef()
{
    ENTER();
    EXIT();
}

s32 MessagingConnectionRef::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise to:
    //   4 bytes - destination connection Id

    if (dataMaxBytes >= 4)
    {
        U32ToBigEndianByteArray((u32)m_destConnId, &data[0]);
        RETURN(4);
    }

    RETURN(-1);
}

bool MessagingConnectionRef::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // DeSerialise from:
    //   4 bytes - destination connection Id

    if(dataLen == 4)
    {
        m_destConnId = (MessagingConnectionIdentifier)BigEndianByteArrayToU32(&data[0]);
        RETURN(true);
    }
    else
    {
        TRACE_PRINTF("Failed to deserialise MessagingConnectionRef - wrong data length, dataLen=%" PRIu32, dataLen);
    }

    RETURN(false);
}

string MessagingConnectionRef::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "MessagingConnectionRef: ";
    stream << "destConnectionId=" << (u32)m_destConnId;

    RETURN(stream.str());
}
