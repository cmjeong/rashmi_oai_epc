///////////////////////////////////////////////////////////////////////////////
//
// MibUnsubscribeReq.cpp
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
#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibUnsubscribeReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MibUnsubscribeReq::MibUnsubscribeReq(u32 subscriptionId) :
    m_subscriptionId(subscriptionId)
{
    ENTER();
    EXIT();
}

MibUnsubscribeReq::MibUnsubscribeReq() :
    m_subscriptionId(0)
{
    ENTER();

    EXIT();
}

s32 MibUnsubscribeReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes > 128);

    const u8* const dataStart = data;

    SerialiseIt(m_subscriptionId, data);

    RETURN(data - dataStart);
}

bool MibUnsubscribeReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_subscriptionId, data);

    RETURN(true);
}

string MibUnsubscribeReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "subscriptionId=" << m_subscriptionId;

    RETURN(stream.str());
}
