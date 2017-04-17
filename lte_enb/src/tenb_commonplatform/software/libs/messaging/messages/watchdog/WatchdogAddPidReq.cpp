///////////////////////////////////////////////////////////////////////////////
//
// WatchdogAddPidReq.cpp
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
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "WatchdogAddPidReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

WatchdogAddPidReq::WatchdogAddPidReq(pid_t pid, const char * descriptor) :
    m_pid(pid),
    m_descriptor(descriptor)
{
    ENTER();
    EXIT();
}

s32 WatchdogAddPidReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= 4 + (2 + m_descriptor.length()));
    RSYS_ASSERT(m_descriptor.length() <= MAX_DESCRIPTOR_LEN);

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt((u32)m_pid, serialisedData);
    SerialiseIt(m_descriptor, serialisedData);

    RETURN(serialisedData - data);
}

bool WatchdogAddPidReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    RSYS_ASSERT(dataLen >= 6);

    // De-serialise all the members.
    u32 pidU32;
    DeSerialiseIt(pidU32, data);
    m_pid = (pid_t)pidU32;

    DeSerialiseIt(m_descriptor, data, MAX_DESCRIPTOR_LEN);

    RETURN(true);
}

string WatchdogAddPidReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "WatchdogAddPidReq { pid=" << m_pid << ", descriptor=" << m_descriptor << " }";

    RETURN(stream.str());
}
