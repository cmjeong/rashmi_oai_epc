///////////////////////////////////////////////////////////////////////////////
//
// MibUnsubscribeCnf.cpp
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

#include "MibUnsubscribeCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MibUnsubscribeCnf::MibUnsubscribeCnf(u32 subscriptionId) :
    m_subscriptionId(subscriptionId)
{
    ENTER();
    EXIT();
}

MibUnsubscribeCnf::MibUnsubscribeCnf() :
    m_subscriptionId(0)
{
    ENTER();

    EXIT();
}

s32 MibUnsubscribeCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes > 128);

    const u8* const dataStart = data;

    SerialiseIt(m_subscriptionId, data);

    RETURN(data - dataStart);
}

bool MibUnsubscribeCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_subscriptionId, data);

    RETURN(true);
}

string MibUnsubscribeCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "subscriptionId=" << m_subscriptionId;

    RETURN(stream.str());
}
