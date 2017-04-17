///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeIdsMessage.cpp
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

#include "MibAttributeIdsMessage.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibAttributeIdsMessage::MibAttributeIdsMessage()
{
    ENTER();

    EXIT();
}

MibAttributeIdsMessage::~MibAttributeIdsMessage()
{
    ENTER();

    EXIT();
}

s32 MibAttributeIdsMessage::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Loop through attribute IDs and serialise each DN + MibAttributeIds.
    u8* dataStart = data;

    u16 attrDnCount = m_attributeIdsByDn.size();
    SerialiseIt(attrDnCount, data);

    for(MibAttributeIdsByDn::const_iterator iter = m_attributeIdsByDn.begin();
        iter != m_attributeIdsByDn.end();
        ++iter)
    {
        RSYS_ASSERT( attrDnCount-- > 0 );

        // For each pair, need to put lengths in too.
        // So we have:
        //   DN length in bytes (u16)
        //   DN serialised bytes
        //   Attribute IDs length in bytes (u16)
        //   Attribute IDs serialised bytes
        u8* pDnLen = data; // Record where we'll write length.
        data += 2; // Skip over length field to be filled in later.
        s32 dnLen = iter->first.Serialise(data, dataMaxBytes - (data - dataStart));
        data += dnLen; // Account for DN data just added.
        U16ToBigEndianByteArray((u16)dnLen, pDnLen); // Store length.

        // Length of IDs.
        u16 numIds = (u16)iter->second.size();
        SerialiseIt(numIds, data);
        // IDs
        for(MibAttributeIds::const_iterator idsIter = iter->second.begin();
            idsIter != iter->second.end();
            ++idsIter)
        {
            SerialiseIt((u32)(*idsIter), data);
        }
    }

    RSYS_ASSERT( attrDnCount == 0 );

    u16 objDnCount = m_objectClassesByDn.size();
    SerialiseIt(objDnCount, data);

    for(MibObjectClassesByDn::const_iterator iter = m_objectClassesByDn.begin();
        iter != m_objectClassesByDn.end();
        ++iter)
    {
        RSYS_ASSERT( objDnCount-- > 0 );

        // For each pair, need to put lengths in too.
        // So we have:
        //   DN length in bytes (u16)
        //   DN serialised bytes
        //   Object classes length in bytes (u16)
        //   Attribute IDs serialised bytes
        u8* pDnLen = data; // Record where we'll write length.
        data += 2; // Skip over length field to be filled in later.
        s32 dnLen = iter->first.Serialise(data, dataMaxBytes - (data - dataStart));
        data += dnLen; // Account for DN data just added.
        U16ToBigEndianByteArray((u16)dnLen, pDnLen); // Store length.

        // Length of IDs.
        u16 numClassess = (u16)iter->second.size();
        SerialiseIt(numClassess, data);
        // IDs
        for(MibObjectClasses::const_iterator classesIter = iter->second.begin();
                classesIter != iter->second.end();
            ++classesIter)
        {
            SerialiseIt((u32)(*classesIter), data);
        }
    }

    RSYS_ASSERT( objDnCount == 0 );

    RETURN(data - dataStart);
}

bool MibAttributeIdsMessage::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    const u8* dataStart = data;

    m_attributeIdsByDn.clear();
    m_objectClassesByDn.clear();

    u16 dnCount;

    for( DeSerialiseIt(dnCount, data);
         dnCount > 0;
         --dnCount )
    {
        MibDN mibDn;
        MibAttributeIds mibAttributeIds;

        // Get DN len and deserialise DN.
        u16 dnLen;
        DeSerialiseIt(dnLen, data);
        mibDn.DeSerialise(data, dnLen);
        data += dnLen;

        RSYS_ASSERT(m_attributeIdsByDn.find(mibDn) == m_attributeIdsByDn.end() );
        MibAttributeIds emptyMibAttributeIds;
        m_attributeIdsByDn[mibDn] = emptyMibAttributeIds;

        // Get attributes length and deserialise.
        u16 numIds;
        DeSerialiseIt(numIds, data);
        for(u16 i = 0; i < numIds; i++)
        {
            u32 id;
            DeSerialiseIt(id, data);
            m_attributeIdsByDn[mibDn].insert(static_cast<MibAttributeId>(id));
        }
    }

    for( DeSerialiseIt(dnCount, data);
         dnCount > 0;
         --dnCount)
    {
        MibDN mibDn;
        MibObjectClassesByDn mibObjectClasses;

        // Get DN len and deserialise DN.
        u16 dnLen;
        DeSerialiseIt(dnLen, data);
        mibDn.DeSerialise(data, dnLen);
        data += dnLen;

        RSYS_ASSERT(m_objectClassesByDn.find(mibDn) == m_objectClassesByDn.end() );
        MibObjectClasses emptyMibObjectClasses;
        m_objectClassesByDn[mibDn] = emptyMibObjectClasses;

        // Get object length and deserialise.
        u16 numObjectClasses;
        DeSerialiseIt(numObjectClasses, data);
        for(u16 i = 0; i < numObjectClasses; i++)
        {
            u32 id;
            DeSerialiseIt(id, data);
            m_objectClassesByDn[mibDn].insert(static_cast<MibObjectClass>(id));
        }
    }

    RSYS_ASSERT(data == (dataStart + dataLen));

    RETURN(true);
}

std::string MibAttributeIdsMessage::ToString() const
{
    ENTER();

    RETURN(m_attributeIdsByDn.ToString());
}

void MibAttributeIdsMessage::AddAttributeIds(const MibDN& dn, const MibAttributeIds& attributeIds)
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_attributeIdsByDn.find(dn) == m_attributeIdsByDn.end(), "Trying to add DN=%s but already exists", dn.ToString().c_str());

    m_attributeIdsByDn[dn] = attributeIds;

    EXIT();
}

void MibAttributeIdsMessage::AddObjectClasses(const MibDN& dn, const MibObjectClasses& objectClasses)
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_objectClassesByDn.find(dn) == m_objectClassesByDn.end(), "Trying to add DN=%s but already exists", dn.ToString().c_str());

    m_objectClassesByDn[dn] = objectClasses;

    EXIT();
}

const MibAttributeIds& MibAttributeIdsMessage::GetMibAttributeIds(const MibDN& dn) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_attributeIdsByDn.find(dn) != m_attributeIdsByDn.end(), "DN: %s", dn.ToString().c_str());

    RETURN(m_attributeIdsByDn.at(dn));
}
