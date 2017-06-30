///////////////////////////////////////////////////////////////////////////////
//
// FapId.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FapId.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool FapId::IsValid(const std::string& shortFapIdStr)
{
    return (shortFapIdStr.length() == SHORT_FAP_ID_LEN) || (shortFapIdStr.length() == SHORT_FAP_ID_ENGINEERING_LEN);
}

FapId::FapId() :
    m_isSet(false)
{
    ENTER();

    EXIT();
}

FapId::FapId(const std::string& shortFapId)
{
    ENTER();

    RSYS_ASSERT(IsValid(shortFapId));

    // Store the FAP ID.
    m_shortFapId = shortFapId;
    m_isSet = true;

    EXIT();
}

FapId::~FapId()
{
    ENTER();

    EXIT();
}

s32 FapId::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= (1 + 2 + m_shortFapId.length()) );

    u8* serialisedData = data;
    SerialiseIt(m_isSet, serialisedData);
    SerialiseIt(m_shortFapId, serialisedData);

    RETURN(serialisedData - data);
}

bool FapId::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_isSet, data);
    DeSerialiseIt(m_shortFapId, data, SHORT_FAP_ID_LEN);

    RETURN(true);
}

string FapId::ToString() const
{
    return "FAP ID: Full=" + GetFullFapId() + ", Short=" + GetShortFapId();
}

string FapId::GetFullFapId() const
{
    ENTER();

    RSYS_ASSERT(m_isSet);

    string fapId = m_shortFapId;
    fapId.append(".Radisys.com");

    RETURN(fapId);
}

string FapId::GetShortFapId() const
{
    ENTER();

    RSYS_ASSERT(m_isSet);

    RETURN(m_shortFapId);
}

std::string FapId::GetShortEquivFapId() const
{
    RSYS_ASSERT(m_isSet);

    if(m_shortFapId.length() == SHORT_FAP_ID_ENGINEERING_LEN)
    {
        RETURN(m_shortFapId.substr(0, 7) + m_shortFapId.substr(9, 8));
    }

    RETURN(m_shortFapId);
}

bool FapId::IsEquivalentTo(const FapId& compareFapId)
{
    ENTER();

    if(IsSet() && compareFapId.IsSet() &&
       (GetShortFapIdLength() != compareFapId.GetShortFapIdLength()))
    {
        // Compare "equivalent" FAP IDs.  This is always 15 chars and
        // may be derived from the 17 char one.
        RETURN(GetShortEquivFapId() == compareFapId.GetShortEquivFapId());
    }

    // Otherwise just do normal ==
    RETURN(operator==(compareFapId));
}

bool FapId::operator==(const FapId& rhs) const
{
    return((m_isSet == rhs.m_isSet) && (m_shortFapId == rhs.m_shortFapId));
}

bool FapId::operator!=(const FapId& rhs) const
{
    return(!operator==(rhs));
}

}
