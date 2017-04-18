///////////////////////////////////////////////////////////////////////////////
//
// $Id: WatchdogKickReq.h 15983 2009-07-22 15:30:41Z dsansom $
//
// Message for requesting that the watchdog guards some context that needs
//  periodically kicking to prevent the system resetting.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __WatchdogKickReq_h_
#define __WatchdogKickReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Manifest Constants
///////////////////////////////////////////////////////////////////////////////

#define WATCHDOG_KICK_FRINT  0
#define WATCHDOG_KICK_CS_UP  1

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class WatchdogKickReq : public threeway::Serialisable
{
public:
    /*
     * Construction / destruction.
     */
    WatchdogKickReq();
    WatchdogKickReq(u32 id, u16 soft, u16 hard);
    virtual ~WatchdogKickReq() {};

    /*
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_WATCHDOG_KICK_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /*
     * Accessors.
     */
    u32 getId()          const { return m_id; };
    u16 getTimeoutSoft() const { return m_timeoutSoft; };
    u16 getTimeoutHard() const { return m_timeoutHard; };

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    u32  m_id;
    u16  m_timeoutSoft;
    u16  m_timeoutHard;
};

#endif
