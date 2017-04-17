///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesDeleteInd.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibSubscribeAttributesDeleteInd.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibSubscribeAttributesDeleteInd::MibSubscribeAttributesDeleteInd(u32 subscriptionId, const MibAttributeIdsByDn& deletedAttributeIdsByDn) :
    m_subscriptionId(subscriptionId)
{
    ENTER();

    for( MibAttributeIdsByDn::const_iterator i = deletedAttributeIdsByDn.begin();
         i != deletedAttributeIdsByDn.end();
         ++i)
    {
        const MibDN & dn = i->first;
        const MibAttributeIds & deletedAttributeIds = i->second;

        AddAttributeIds(dn, deletedAttributeIds);

    }

    EXIT();
}

MibSubscribeAttributesDeleteInd::MibSubscribeAttributesDeleteInd() :
    m_subscriptionId(0)
{
    ENTER();

    EXIT();
}

s32 MibSubscribeAttributesDeleteInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 4);

    const u8* const dataStart = data;

    SerialiseIt(m_subscriptionId, data);
    data += MibAttributeIdsMessage::Serialise(data, dataMaxBytes - (data - dataStart));

    RETURN(data - dataStart);
}

bool MibSubscribeAttributesDeleteInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    RSYS_ASSERT(dataLen >= 4);

    const u8* const dataStart = data;

    DeSerialiseIt(m_subscriptionId, data);
    MibAttributeIdsMessage::DeSerialise(data, dataLen - (data - dataStart));

    RETURN(true);
}

std::string MibSubscribeAttributesDeleteInd::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "subscriptionId=" << m_subscriptionId
           << ", " << MibAttributeIdsMessage::ToString();

    RETURN(stream.str());
}
