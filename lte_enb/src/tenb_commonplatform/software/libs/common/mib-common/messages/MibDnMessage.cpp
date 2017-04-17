///////////////////////////////////////////////////////////////////////////////
//
// MibDnMessage.cpp
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

#include "MibDnMessage.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibDnMessage::MibDnMessage(const MibDN& dn) :
    m_dn(dn)
{
    ENTER();

    EXIT();
}

s32 MibDnMessage::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    const u8 * const dataStart = data;

    // Store DN
    u32 dnLen = m_dn.Serialise(data, dataMaxBytes);
    RSYS_ASSERT(dnLen > 0);
    data += dnLen;

    RETURN(data - dataStart);
}

bool MibDnMessage::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // Deserialise DN.
    bool success = m_dn.DeSerialise(data, dataLen);
    RSYS_ASSERT(success);

    RETURN(true);
}

std::string MibDnMessage::ToString() const
{
    ENTER();

    ostringstream str;

    str << "dn=" << m_dn.ToString();

    RETURN(str.str());
}
