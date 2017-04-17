///////////////////////////////////////////////////////////////////////////////
//
// $Id: WatchdogKickStopReq.cpp 15267 2009-06-26 15:37:02Z dallwright $
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

#include "WatchdogKickStopReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

WatchdogKickStopReq::WatchdogKickStopReq(u32 id) :
    m_id(id)
{
    ENTER();
    EXIT();
}

s32 WatchdogKickStopReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= 4)
    {
        U32ToBigEndianByteArray(m_id, &data[0]);
        return 4;
    }

    RETURN(-1);
}

bool WatchdogKickStopReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen >= 4)
    {
        m_id = BigEndianByteArrayToU32(&data[0]);

        RETURN(true);
    }

    RETURN(false);
}

string WatchdogKickStopReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "WatchdogKickStopReq { id=" << m_id << " }";

    RETURN(stream.str());
}

// END OF FILE
