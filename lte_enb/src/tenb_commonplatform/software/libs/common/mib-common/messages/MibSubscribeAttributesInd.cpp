///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesInd.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibSubscribeAttributesInd.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibSubscribeAttributesInd::MibSubscribeAttributesInd() :
    m_subscriptionId(0)
{
    ENTER();

    EXIT();
}

MibSubscribeAttributesInd::MibSubscribeAttributesInd(u32 subscriptionId) :
        m_subscriptionId(subscriptionId)
{

}

MibSubscribeAttributesInd::MibSubscribeAttributesInd(u32 subscriptionId, const MibDN& dn, const MibAttributeValues& attributes) :
    m_subscriptionId(subscriptionId)
{
    AddAttributes(dn, attributes);
}

MibSubscribeAttributesInd::MibSubscribeAttributesInd(u32 subscriptionId, const MibAttributeValuesByDn & mibAttributeValuesByDn) :
        m_subscriptionId(subscriptionId)
{
    for( MibAttributeValuesByDn::const_iterator i = mibAttributeValuesByDn.begin();
         i != mibAttributeValuesByDn.end();
         i++ )
    {
        AddAttributes( i->first, i->second );
    }
}

s32 MibSubscribeAttributesInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    RSYS_ASSERT(dataMaxBytes >= 4);

    const u8* const dataStart = data;

    SerialiseIt(m_subscriptionId, data);
    data += MibAttributesMessage::Serialise(data, dataMaxBytes - (data - dataStart));

    return (data - dataStart);
}

bool MibSubscribeAttributesInd::DeSerialise(const u8* data, u32 dataLen)
{
    RSYS_ASSERT(dataLen >= 4);

    const u8* const dataStart = data;

    DeSerialiseIt(m_subscriptionId, data);
    MibAttributesMessage::DeSerialise(data, dataLen - (data - dataStart));

    return true;
}

std::string MibSubscribeAttributesInd::ToString() const
{
    ostringstream stream;

    stream << "subscriptionId=" << m_subscriptionId
           << ", " << MibAttributesMessage::ToString();

    return stream.str();
}
