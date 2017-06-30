///////////////////////////////////////////////////////////////////////////////
//
// UeIdentityTracker.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UeIdentityTracker.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

UeIdentityTracker::UeIdentityTracker(TimerEngineInterface& timerEngine, TimestamperInterface& timestamper) :
    m_timerEngine(timerEngine),
    m_timestamper(timestamper),
    m_inactivityTimeoutSecs(DEFAULT_UE_IDENTITY_INACTIVITY_TIMEOUT_SECS)
{
    // Create and start the garbage collection timer.
    m_garbageCollectTimer = m_timerEngine.CreateTimer("UeIdentityTracker Garbage Collect",
                                                      5 * 60 * 1000, // 5 mins
                                                      *this,
                                                      TimerEngineInterface::TIMER_START_NOW,
                                                      TimerEngineInterface::TIMER_REPEAT);
}

UeIdentityTracker::~UeIdentityTracker()
{
    m_timerEngine.DeleteTimer(m_garbageCollectTimer);
}

void UeIdentityTracker::NotifyTimerExpiry(TimerHandle expiredTimer)
{
    RSYS_ASSERT(expiredTimer == m_garbageCollectTimer);

    // Look for mappings that were last touched over inactivityTimeoutSecs ago.
    // TODO - should we have separate timeout values for TMSI and P-TMSI?
    GarbageCollectImsiMap(m_tmsiToImsiMapping, "TMSI");
    GarbageCollectImsiMap(m_pTmsiToImsiMapping, "P-TMSI");
}

void UeIdentityTracker::SetPeriodicLocUpDurationT3212(u32 t3212Decihours)
{
    if(t3212Decihours > 0)
    {
        m_inactivityTimeoutSecs = t3212Decihours * 6 * 60 + 120; // T3212 + 120 secs
    }
    else
    {
        m_inactivityTimeoutSecs = 3600; // An hour :)
    }
}

void UeIdentityTracker::RecordNewTMSI(const IMSI& imsi, const TMSI& newTmsi)
{
    RecordNewTempId(imsi, newTmsi, m_tmsiToImsiMapping);
}

void UeIdentityTracker::RecordNewPTMSI(const IMSI& imsi, const TMSI& newPTmsi)
{
    RecordNewTempId(imsi, newPTmsi, m_pTmsiToImsiMapping);
}

bool UeIdentityTracker::FindIMSIFromTMSI(const TMSI& tmsi, IMSI& imsi)
{
    RSYS_ASSERT(tmsi.IsSet());

    TempUeIdToImsiMap::iterator iter = m_tmsiToImsiMapping.find(tmsi);

    if(iter != m_tmsiToImsiMapping.end())
    {
        imsi = iter->second.imsi;
        iter->second.lastAccessTimestampSecs = m_timestamper.GetTimestampSecs();
        return true;
    }

    return false;
}

bool UeIdentityTracker::FindIMSIFromPTMSI(const TMSI& ptmsi, IMSI& imsi)
{
    RSYS_ASSERT(ptmsi.IsSet());

    TempUeIdToImsiMap::iterator iter = m_pTmsiToImsiMapping.find(ptmsi);

    if(iter != m_pTmsiToImsiMapping.end())
    {
        imsi = iter->second.imsi;
        iter->second.lastAccessTimestampSecs = m_timestamper.GetTimestampSecs();
        return true;
    }

    return false;
}

std::string UeIdentityTracker::ToString() const
{
    ostringstream stream;

    ImsiMapToString(m_tmsiToImsiMapping, "TMSI", stream);
    ImsiMapToString(m_pTmsiToImsiMapping, "P-TMSI", stream);

    return stream.str();
}

void UeIdentityTracker::RecordNewTempId(const IMSI& imsi, const TMSI& newTempId, TempUeIdToImsiMap& tempIdMap)
{
    RSYS_ASSERT(imsi.IsSet());
    RSYS_ASSERT(newTempId.IsSet());

    for(TempUeIdToImsiMap::iterator iter = tempIdMap.begin();
        iter != tempIdMap.end();
        ++iter)
    {
        if(iter->second.imsi == imsi)
        {
            // Found it.  Remove it (to be replace with new temp ID below).
            tempIdMap.erase(iter);
            break; // Got break out the loop, iterator now invalid.
        }
    }

    ImsiInfo imsiInfo;
    imsiInfo.imsi = imsi;
    imsiInfo.lastAccessTimestampSecs = m_timestamper.GetTimestampSecs();
    tempIdMap[newTempId] = imsiInfo;
}

void UeIdentityTracker::GarbageCollectImsiMap(TempUeIdToImsiMap& imsiMap, const char * description)
{
    u32 now = m_timestamper.GetTimestampSecs();

    TempUeIdToImsiMap::iterator iter = imsiMap.begin();
    while(iter != imsiMap.end())
    {
        TempUeIdToImsiMap::iterator workIter = iter;
        ++iter;

        if(now > (workIter->second.lastAccessTimestampSecs + m_inactivityTimeoutSecs))
        {
            TRACE_PRINTF("UEID: Removing %s %s <> IMSI %s from %s map", description, workIter->first.ToString(), workIter->second.imsi.ToString(), description);
            imsiMap.erase(workIter);
        }
    }
}

void UeIdentityTracker::ImsiMapToString(const TempUeIdToImsiMap& imsiMap, const char * description, ostringstream& stream) const
{
    if(imsiMap.size() > 0)
    {
        stream << setw(6) << description << "      IMSI" << endl;
        for(TempUeIdToImsiMap::const_iterator iter = imsiMap.begin();
            iter != imsiMap.end();
            ++iter)
        {
            stream << iter->first.ToString() << " <> " << iter->second.imsi.ToString() << " [" << iter->second.lastAccessTimestampSecs << "s]" << endl;
        }
    }
    else
    {
        stream << "No " << description << endl;
    }

    stream << endl;
}
