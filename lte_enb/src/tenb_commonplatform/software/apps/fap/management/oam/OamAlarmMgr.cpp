
///////////////////////////////////////////////////////////////////////////////
//
// OamAlarmMgr.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamAlarmMgr.h"
#include "OamStuckAlarms.h"
#include "oam_env.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

OamAlarmMgr::OamAlarmMgr(SingleThreadedApplicationWithMessaging& mainApp, u32 nextAlarmEventSequenceNumber) :
    m_mainApp(mainApp),
    m_alarmEventLog(ALARM_MGR_MAX_LOG_ALARM_EVENTS),
    m_nextAlarmEventSequenceNumber(nextAlarmEventSequenceNumber)
{
    ENTER();
    string alarmLogFile;

    alarmLogFile += mainApp.GetNvLogDirectory();
    alarmLogFile += mainApp.GetName();
    alarmLogFile += ".alarms";

    m_alarmEventLogFileMgr.reset(new OamAlarmEventLogFileMgr(m_alarmEventLog, alarmLogFile.c_str(), ALARM_MGR_MAX_LOG_ALARM_EVENTS));

    EXIT();
}

OamAlarmMgr::~OamAlarmMgr()
{
    ENTER();
    EXIT();
}

void OamAlarmMgr::Start( void )
{
    m_alarmEventLogFileMgr->ReadAllObjects();
    m_nextAlarmEventSequenceNumber = m_alarmEventLogFileMgr->GetNextSequenceNumber();

    m_alarmEventLogFileMgr->StartLogging();
}


void OamAlarmMgr::ClearAlarmsLeftSetOverReboot()
{
    TRACE_PRINTF("Clearing stuck alarms");

    StuckAlarms stuckAlarms;

    AcceptAlarmEventLogVisitor(stuckAlarms);

    stuckAlarms.Clear(m_mainApp);
}

void OamAlarmMgr::HandleAlarmEvent(AlarmEvent& alarmEvent)
{
    ENTER();

    TRACE_PRINTF("AlarmEvent: %s", alarmEvent.ToString().c_str());

    // Give it a unique (within OAM at least) sequence number.
    // A particular management interface (TR069, SNMP etc) may choose to use, ignore or overwrite this.
    alarmEvent.SetSequenceNumber(m_nextAlarmEventSequenceNumber);
    // Increment ready for the next event.
    m_nextAlarmEventSequenceNumber++;

    // Add to log.
    m_alarmEventLog.HandleAlarmEvent(alarmEvent);

    // Send it on to management interfaces that are present.
    // TODO - Could still make it neater by having mgmt entities register with OAM.
    if(oamEnv_isProductHbs2Iu() || oamEnv_isProductGeneric())
    {
        if(m_mainApp.IsRouteAvailable(ENTITY_TR069))
        {
            m_mainApp.SendMessage(alarmEvent, ENTITY_TR069, ENTITY_OAM);
        }
        else
        {
            TRACE_LEV(TRACE_WARNING, "Trying to send alarm event to TR-069 but entity not yet registered", alarmEvent.ToString());
        }
    }

    else
    {
	    TRACE_PRINTF("Inside the wrong environment");
    }

    EXIT();
}

void OamAlarmMgr::AcceptAlarmEventLogVisitor(AlarmEventListVisitor& eventLogVisitor) const
{
    ENTER();

    m_alarmEventLog.AcceptVisitor(eventLogVisitor);

    EXIT();
}


