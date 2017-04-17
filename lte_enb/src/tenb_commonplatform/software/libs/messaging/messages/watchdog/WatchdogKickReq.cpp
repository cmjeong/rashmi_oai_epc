///////////////////////////////////////////////////////////////////////////////
//
// $Id: WatchdogKickReq.cpp 15267 2009-06-26 15:37:02Z dallwright $
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "WatchdogKickReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

WatchdogKickReq::WatchdogKickReq() :
    m_id(0),
    m_timeoutSoft(0),
    m_timeoutHard(0)
{
    ENTER();
    EXIT();
}

WatchdogKickReq::WatchdogKickReq(u32 id, u16 soft, u16 hard) :
    m_id(id),
    m_timeoutSoft(soft),
    m_timeoutHard(hard)
{
    ENTER();
    EXIT();
}

s32 WatchdogKickReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= 8)
    {
        U32ToBigEndianByteArray(m_id,          &data[0]);
        U16ToBigEndianByteArray(m_timeoutSoft, &data[4]);
        U16ToBigEndianByteArray(m_timeoutHard, &data[6]);
        return 8;
    }

    RETURN(-1);
}

bool WatchdogKickReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen >= 8)
    {
        m_id          = BigEndianByteArrayToU32(&data[0]);
        m_timeoutSoft = BigEndianByteArrayToU16(&data[4]);
        m_timeoutHard = BigEndianByteArrayToU16(&data[6]);

        RETURN(true);
    }

    RETURN(false);
}

string WatchdogKickReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "WatchdogKickReq { id=" <<
    m_id << ", soft=" <<
    m_timeoutSoft << ", hard=" <<
    m_timeoutHard << " seconds }" << endl;

    RETURN(stream.str());
}

// END OF FILE
