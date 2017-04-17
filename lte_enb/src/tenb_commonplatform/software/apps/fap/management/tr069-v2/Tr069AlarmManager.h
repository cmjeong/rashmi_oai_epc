///////////////////////////////////////////////////////////////////////////////
//
// AlarmManager.h
//
// Manage all alarm events and active alarms to be reported via TR069.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069AlarmMgr_h_
#define __Tr069AlarmMgr_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/AlarmEventLog.h>
#include <system/ActiveAlarms.h>
#include <system/AlarmEventLogFileMgr.h>
#include <messaging/transport/ApplicationWithMessaging.h>
#include <platform/RadisysFapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

#include "Tr069SupportedAlarmManager.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

class Tr069AlarmEventLogFileMgr : public AlarmEventLogFileMgr
{
public:
    Tr069AlarmEventLogFileMgr(AlarmEventList& alarmEventList, const char * logFileName, u32 minNumAlarmEvents) :
        AlarmEventLogFileMgr(alarmEventList, logFileName, minNumAlarmEvents) {};
    virtual ~Tr069AlarmEventLogFileMgr() {};

    virtual shared_ptr<AlarmId> GetNewAlarmId()
    {
	 shared_ptr<AlarmId> alarmId(new RadisysFapAlarmId());

        RSYS_ASSERT(alarmId);

        return alarmId;
    }

};

class AlarmManager
{
public:

    AlarmManager(MibAccessInterface& mib, SendMessageInterface &messenger);
    virtual ~AlarmManager();

    /**
     * Handle an alarm event.  This will include filtering/converting
     * for vendor specific purposes, adding it to the alarm
     * event log and adding/removing to/from the list of active alarms.
     *
     * \param alarmEvent The alarm event to handle.
     */
    void AcceptAlarmEventLogVisitor(AlarmEventListVisitor& eventLogVisitor) const; 
    void HandleAlarmEvent(AlarmEvent& alarmEvent);

    void Start( void );

private:
    MibAccessInterface& m_mib;
    SendMessageInterface &m_messenger;

    static const u32 ALARM_MGR_MAX_LOG_ALARM_EVENTS = 1400;
    AlarmEventLog m_alarmEventLog;
    shared_ptr<Tr069AlarmEventLogFileMgr> m_alarmEventLogFile;
    u32 m_nextAlarmEventSequenceNumber;

    /**
     * List of active alarm events.
     */
    ActiveAlarms m_tr069ActiveAlarms;
    shared_ptr<SupportedAlarmManager> m_alarmDespatch;
};

}

#endif
