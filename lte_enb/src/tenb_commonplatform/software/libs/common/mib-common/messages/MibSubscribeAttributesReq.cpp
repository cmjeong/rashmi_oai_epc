///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesReq.cpp
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
#include <system/NumberConversions.h>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibSubscribeAttributesReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MibSubscribeAttributesReq::MibSubscribeAttributesReq(u32 subscriptionId) :
    m_subscriptionId(subscriptionId)
{
    ENTER();

    EXIT();
}

MibSubscribeAttributesReq::MibSubscribeAttributesReq(u32 subscriptionId, const MibDN& dn, const MibAttributeIds& attributeIds) :
    m_subscriptionId(subscriptionId)
{
    ENTER();

    AddAttributeIds(dn, attributeIds);

    EXIT();
}

MibSubscribeAttributesReq::MibSubscribeAttributesReq() :
    m_subscriptionId(0)
{
    ENTER();
    EXIT();
}

s32 MibSubscribeAttributesReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 128);

    const u8* const dataStart = data;

    SerialiseIt(m_subscriptionId, data);
    data += MibAttributeIdsMessage::Serialise(data, dataMaxBytes - (data - dataStart));

    RETURN(data - dataStart);
}

bool MibSubscribeAttributesReq::DeSerialise(const u8* data, u32 dataLen)
{
    RSYS_ASSERT(dataLen >= 4);

    const u8* const dataStart = data;

    DeSerialiseIt(m_subscriptionId, data);
    MibAttributeIdsMessage::DeSerialise(data, dataLen - (data - dataStart));

    RETURN(true);
}

string MibSubscribeAttributesReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "subscriptionId=" << m_subscriptionId
           << ", " << MibAttributeIdsMessage::ToString();

    RETURN(stream.str());
}
