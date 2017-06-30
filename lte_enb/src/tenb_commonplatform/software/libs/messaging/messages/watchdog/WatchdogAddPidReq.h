///////////////////////////////////////////////////////////////////////////////
//
// WatchdogAddPidReq.h
//
// Message for requesting that the watchdog guards some PID and will reset the
// system if that process dies.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __WatchdogAddPidReq_h_
#define __WatchdogAddPidReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class WatchdogAddPidReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    WatchdogAddPidReq() { m_pid = 0; };
    WatchdogAddPidReq(pid_t pid, const char * descriptor);
    virtual ~WatchdogAddPidReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_WATCHDOG_ADD_PID_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    pid_t GetPid() const { return m_pid; };
    std::string GetDescriptor() const { return m_descriptor; };

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    static const u16 MAX_DESCRIPTOR_LEN = 50;

    pid_t m_pid;
    std::string m_descriptor;
};

#endif
