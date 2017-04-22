///////////////////////////////////////////////////////////////////////////////
//
// MibAttributesMessage.cpp
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

#include "MibAttributesMessage.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibAttributesMessage::MibAttributesMessage()
{
    ENTER();

    EXIT();
}

MibAttributesMessage::~MibAttributesMessage()
{
    ENTER();

    EXIT();
}

s32 MibAttributesMessage::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    const u8* const dataStart = data;

    // Loop through attributes and serialise each DN + MibAttributeValues.
    for(MibAttributeValuesByDn::const_iterator iter = m_attributes.begin();
        iter != m_attributes.end();
        ++iter)
    {
        // For each pair, need to put lengths in too.
        // So we have:
        //   DN length in bytes (u16)
        //   DN serialised bytes
        //   Attribute values length in bytes (u16)
        //   Attribute values serialised bytes
        u8* pDnLen = data; // Record where we'll write length.
        data += 2; // Skip over length field to be filled in later.
        s32 dnLen = iter->first.Serialise(data, dataMaxBytes - (data - dataStart));
        data += dnLen; // Account for DN data just added.
        U16ToBigEndianByteArray((u16)dnLen, pDnLen); // Store length.

        u8* pAttrsLen = data; // Record where we'll write length.
        data += 2; // Skip over length field to be filled in later.
        s32 attrsLen = iter->second.Serialise(data, dataMaxBytes - (data - dataStart));
        data += attrsLen; // Account for attribute data just added.
        U16ToBigEndianByteArray((u16)attrsLen, pAttrsLen); // Store length.
    }

    RSYS_ASSERT_PRINTF(data <= (dataStart + dataMaxBytes), "Failed to serialise MibAttributesMessage %s", ToString().c_str());
    RETURN(data - dataStart);
}

bool MibAttributesMessage::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    const u8* const dataStart = data;

    m_attributes.clear();
    while(data < (dataStart + dataLen))
    {
        MibDN mibDn;
        MibAttributeValues mibAttributeValues;

        // Get DN len and deserialise DN.
        u16 dnLen;
        DeSerialiseIt(dnLen, data);
        mibDn.DeSerialise(data, dnLen);
        data += dnLen;

        // Get attributes length and deserialise.
        u16 attrsLen;
        DeSerialiseIt(attrsLen, data);
        mibAttributeValues.DeSerialise(data, attrsLen);
        data += attrsLen;

        m_attributes[mibDn] = mibAttributeValues;
    }

    RSYS_ASSERT(data == (dataStart + dataLen));

    RETURN(true);
}

std::string MibAttributesMessage::ToString() const
{
    ENTER();

    RETURN(m_attributes.ToString());
}

void MibAttributesMessage::AddAttributes(const MibDN& dn, const MibAttributeValues& attributes)
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_attributes.find(dn) == m_attributes.end(), "Trying to add DN=%s but already exists", dn.ToString().c_str());

    m_attributes[dn] = attributes;

    EXIT();
}

vector<MibDN> MibAttributesMessage::GetDnList() const
{
    ENTER();

    vector<MibDN> dnList;

    for(MibAttributeValuesByDn::const_iterator iter = m_attributes.begin();
        iter != m_attributes.end();
        ++iter)
    {
        dnList.push_back(iter->first);
    }

    RETURN(dnList);
}

const MibAttributeValues& MibAttributesMessage::GetMibAttributeValues(const MibDN& dn) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_attributes.find(dn) != m_attributes.end(), "DN: %s", dn.ToString().c_str());

    RETURN(m_attributes.at(dn));
}
