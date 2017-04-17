///////////////////////////////////////////////////////////////////////////////
//
// WatchdogRemovePidReq.h
//
// Message for requesting that the watchdog guards some PID and will reset the
// system if that process dies.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __WatchdogRemovePidReq_h_
#define __WatchdogRemovePidReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class WatchdogRemovePidReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    WatchdogRemovePidReq() { m_pid = 0; };
    WatchdogRemovePidReq(pid_t pid);
    virtual ~WatchdogRemovePidReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_WATCHDOG_REMOVE_PID_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    pid_t GetPid() const { return m_pid; };

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    pid_t m_pid;
};

#endif
