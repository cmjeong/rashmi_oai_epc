
///////////////////////////////////////////////////////////////////////////////
//
// OamAlarmMgr.h
//
// Manage all alarm events and active alarms in the system.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OamAlarmMgr_h_
#define __OamAlarmMgr_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/AlarmEventLog.h>
#include <system/ActiveAlarms.h>
#include <system/AlarmEventLogFileMgr.h>
#include <messaging/transport/SingleThreadedApplicationWithMessaging.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class OamAlarmEventLogFileMgr : public AlarmEventLogFileMgr
{
public:
    OamAlarmEventLogFileMgr(AlarmEventList& alarmEventList, const char * logFileName, u32 minNumAlarmEvents) :
        AlarmEventLogFileMgr(alarmEventList, logFileName, minNumAlarmEvents) {};
    virtual ~OamAlarmEventLogFileMgr() {};

    virtual shared_ptr<AlarmId> GetNewAlarmId()
    {
        shared_ptr<AlarmId> alarmId(new FapAlarmId());

        RSYS_ASSERT(alarmId);

        return alarmId;
    }

};


class OamAlarmMgr
{
public:

    OamAlarmMgr(SingleThreadedApplicationWithMessaging& mainApp, u32 nextAlarmEventSequenceNumber);
    virtual ~OamAlarmMgr();

    /**
     * Handle an alarm event.  This will include adding it to the alarm
     * event log and adding/removing to/from the list of active alarms.
     *
     * \param alarmEvent The alarm event to handle.
     */
    void HandleAlarmEvent(AlarmEvent& alarmEvent);
    void AcceptAlarmEventLogVisitor(AlarmEventListVisitor& eventLogVisitor) const;
    void Start( void );

    void ClearAlarmsLeftSetOverReboot();

private:

    /**
     * Maximum number of alarm events in the historical log.
     */
    static const u32 ALARM_MGR_MAX_LOG_ALARM_EVENTS = 1400;

    /**
     * The main app for sending messages.
     */
    SingleThreadedApplicationWithMessaging& m_mainApp;

    /**
     * Alarm event log.
     */
    AlarmEventLog m_alarmEventLog;

    shared_ptr<OamAlarmEventLogFileMgr> m_alarmEventLogFileMgr;

    /**
     * Next sequence number.
     * TODO - Will be initialised from some NV at some point.
     */
    u32 m_nextAlarmEventSequenceNumber;

};

#endif
