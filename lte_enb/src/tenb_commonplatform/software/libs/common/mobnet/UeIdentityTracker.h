///////////////////////////////////////////////////////////////////////////////
//
// UeIdentityTracker.h
//
// Maintains lists of UE identities to allowing mapping between IMSI, TMSI and
// P-TMSI.  We only look at downlink NAS messages that contain assigned
// TMSI/P-TMSI and ignore the uplink 'confirm' messages e.g. TMSI Realloc
// Complete.  This simplification means we don't have to track two sets of
// temporary IDs and means we don't need to worry about what the confirm is
// confirming in the case of combined attach (TMSI, P-TMSI or both?).  The
// slight downside is very occassionally we will request the IMSI when we may
// not have needed to.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UeIdentityTracker_h_
#define __UeIdentityTracker_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <sstream>
#include <system/TimerInterface.h>
#include <system/TimestamperInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IMSI.h"
#include "TMSI.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class UeIdentityTracker : public TimerNotifyInterface
{
public:
    /**
     * Constructor.
     *
     * \param timerEngine Give it a concrete timer engine...
     * \param timestamper Interface for getting current time.
     */
    UeIdentityTracker(TimerEngineInterface& timerEngine, TimestamperInterface& timestamper);

    /**
     * Destructor.
     */
    ~UeIdentityTracker();

    /**
     * Implement TimerNotifyInterface
     * Note: Not thread safe, protect externally if timer thread different to UE message processing thread.
     */
    virtual void NotifyTimerExpiry(TimerHandle expiredTimer);

    /**
     * Set periodic location update duration T3212.
     * This will be used to set the inactivity timeout for garbage collecting old temporary
     * identities.  At some fraction of this period we will check for inactivity on each entry
     * in the internal mappings and delete old entries.
     *
     * \param t3212Decihours Periodic location update duration.
     */
    void SetPeriodicLocUpDurationT3212(u32 t3212Decihours);

    /**
     * Update TMSI stored for a particular UE (IMSI).
     * Any existing TMSI will be maintained until new one is confirmed.
     *
     * \param imsi    UE IMSI
     * \param newTmsi New TMSI for UE
     */
    void RecordNewTMSI(const IMSI& imsi, const TMSI& newTmsi);

    /**
     * Update P-TMSI stored for a particular UE (IMSI).
     * Any existing P-TMSI will be maintained until new one is confirmed.
     *
     * \param imsi     UE IMSI
     * \param newPTmsi New P-TMSI for UE
     */
    void RecordNewPTMSI(const IMSI& imsi, const TMSI& newPTmsi);

    /**
     * Look up IMSI from TMSI.
     *
     * \param tmsi TMSI to lookup IMSI against
     * \param imsi Filled in with IMSI if available
     * \return true if IMSI found
     */
    bool FindIMSIFromTMSI(const TMSI& tmsi, IMSI& imsi);

    /**
     * Look up IMSI from P-TMSI.
     *
     * \param ptmsi P-TMSI to lookup IMSI against
     * \param imsi Filled in with IMSI if available
     * \return true if IMSI found
     */
    bool FindIMSIFromPTMSI(const TMSI& ptmsi, IMSI& imsi);

    /**
     * Get current mappings as string for debug/trace.
     */
    std::string ToString() const;

private:

    // How long to keep unused temporary identities.
    static const u32 DEFAULT_UE_IDENTITY_INACTIVITY_TIMEOUT_SECS = 3600;

    typedef struct
    {
        u32 lastAccessTimestampSecs;
        IMSI imsi;
    } ImsiInfo;

    // Most common lookup is from TMSI/P-TMSI to IMSI.  Reverse lookup is only necessary
    // when inserting in to the map to see if IMSI already exists.
    typedef std::map<TMSI, ImsiInfo> TempUeIdToImsiMap;

    void RecordNewTempId(const threeway::IMSI& imsi, const threeway::TMSI& newTempId, TempUeIdToImsiMap& pendingTempIdMap);
    void GarbageCollectImsiMap(TempUeIdToImsiMap& imsiMap, const char * description);
    void ImsiMapToString(const TempUeIdToImsiMap& imsiMap, const char * description, std::ostringstream& stream) const;

    TimerEngineInterface& m_timerEngine;
    TimestamperInterface& m_timestamper;

    // Seconds of inactivity after which we delete entries from our UE identity maps.
    // Normally this will be linked to the periodic location update + routing area update timers.
    u32 m_inactivityTimeoutSecs;

    // Repeating timer that triggers us to check for inactive entries.
    TimerHandle m_garbageCollectTimer; // Some fraction of the inactivity timeout

    // IMSI <> TMSI mapping.
    TempUeIdToImsiMap m_tmsiToImsiMapping;

    // IMSI <> P-TMSI mapping.
    TempUeIdToImsiMap m_pTmsiToImsiMapping;
};

}

#endif
