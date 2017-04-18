///////////////////////////////////////////////////////////////////////////////
//
// WatchdogRemovePidReq.cpp
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

#include "WatchdogRemovePidReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

WatchdogRemovePidReq::WatchdogRemovePidReq(pid_t pid) :
    m_pid(pid)
{
    ENTER();
    EXIT();
}

s32 WatchdogRemovePidReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= 4)
    {
        U32ToBigEndianByteArray(m_pid, &data[0]);
        return 4;
    }

    RETURN(-1);
}

bool WatchdogRemovePidReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen >= 4)
    {
        m_pid = BigEndianByteArrayToU32(data);

        RETURN(true);
    }

    RETURN(false);
}

string WatchdogRemovePidReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "WatchdogRemovePidReq { pid=" << m_pid << " }";

    RETURN(stream.str());
}
