///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesCnf.cpp
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
#include <system/SerialisationUtils.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibSubscribeAttributesCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MibSubscribeAttributesCnf::MibSubscribeAttributesCnf(u32 subscriptionId) :
    m_subscriptionId(subscriptionId)
{
    ENTER();
    EXIT();
}

MibSubscribeAttributesCnf::MibSubscribeAttributesCnf() :
    m_subscriptionId(0)
{
    ENTER();

    EXIT();
}

s32 MibSubscribeAttributesCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes > 128);

    const u8* const dataStart = data;

    SerialiseIt(m_subscriptionId, data);

    RETURN(data - dataStart);
}

bool MibSubscribeAttributesCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_subscriptionId, data);

    RETURN(true);
}

string MibSubscribeAttributesCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "subscriptionId=" << m_subscriptionId;

    RETURN(stream.str());
}
