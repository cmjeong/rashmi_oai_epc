///////////////////////////////////////////////////////////////////////////////
//
// MibCreateObjectReq.cpp
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

#include "MibCreateObjectReq.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibCreateObjectReq::MibCreateObjectReq(const MibDN& parentDn, const MibRDN& childRdn)
{
    MibDN objectDn = parentDn;
    objectDn.push_back(childRdn);

    // Base class can store DN/attribute pairs so let's take advantage of that and store the DN there
    // along with an empty set of attributes.
    MibAttributeValues attributes;
    AddAttributes(parentDn, attributes);
}

MibCreateObjectReq::MibCreateObjectReq(const MibDN& parentDn, const MibRDN& childRdn, const MibAttributeValues& attributes)
{
    MibDN objectDn = parentDn;
    objectDn.push_back(childRdn);

    // Base class can store DN/attribute pairs so let's take advantage of that and store the DN there
    // along with the attributes supplied for the new child.
    AddAttributes(objectDn, attributes);
}

s32 MibCreateObjectReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    RSYS_ASSERT(GetDnList().size() == 1);

    const u8 * const dataStart = data;

    // Use base class to serialise.
    s32 baseLen = MibAttributesMessage::Serialise(data, dataMaxBytes - (data - dataStart));
    RSYS_ASSERT(baseLen >= 0);
    data += baseLen;

    return (data - dataStart);
}

bool MibCreateObjectReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // Use base class to deserialise.
    bool baseSuccess = MibAttributesMessage::DeSerialise(data, dataLen);
    RSYS_ASSERT(baseSuccess);

    RSYS_ASSERT(GetDnList().size() == 1);

    RETURN(true);
}

std::string MibCreateObjectReq::ToString() const
{
    ENTER();

    RSYS_ASSERT(GetDnList().size() == 1);

    ostringstream str;

    str << "DN & attributes: " << GetMibAttributeValuesByDn().ToString();

    RETURN(str.str());
}

MibDN MibCreateObjectReq::GetParentDn() const
{
    ENTER();

    RSYS_ASSERT(GetDnList().size() == 1);

    MibDN parent = GetMibAttributeValuesByDn().begin()->first;
    parent.pop_back();

    RETURN(parent);
}

MibRDN MibCreateObjectReq::GetChildRdn() const
{
    ENTER();

    RSYS_ASSERT(GetDnList().size() == 1);

    RETURN(GetMibAttributeValuesByDn().begin()->first.back());
}

const MibAttributeValues& MibCreateObjectReq::GetChildMibAttributeValues() const
{
    ENTER();

    RSYS_ASSERT(GetDnList().size() == 1);

    RETURN(GetMibAttributeValuesByDn().begin()->second);
}
