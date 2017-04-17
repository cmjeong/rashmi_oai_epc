///////////////////////////////////////////////////////////////////////////////
//
// $Id: WatchdogKickStopReq.h 15267 2009-06-26 15:37:02Z dallwright $
//
// Message for requesting that the watchdog no longer requires kicking for
// some specific context.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __WatchdogKickStopReq_h_
#define __WatchdogKickStopReq_h_

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

class WatchdogKickStopReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    WatchdogKickStopReq() { m_id = 0; };
    WatchdogKickStopReq(u32 id);
    virtual ~WatchdogKickStopReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_WATCHDOG_KICK_STOP_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    u32 GetId() const { return m_id; };

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    u32  m_id;
};

#endif
