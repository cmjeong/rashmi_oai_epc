///////////////////////////////////////////////////////////////////////////////
//
// AlarmManager.cpp
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
#include <platform/FapAlarmId.h>
#include <platform/RadisysFapAlarmId.h>

#include <system/AlarmEventType.h>
#include <system/AlarmPerceivedSeverity.h>
#include <system/AlarmReportingMechanism.h>
#include <mib-common/messages/MibCreateObjectReq.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069AlarmManager.h"
#include "Tr069SupportedAlarmManager.h"
#include "Tr069TransactionSessionCommand.h"
#include "Tr069Parameters.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

namespace tr069
{

AlarmManager::AlarmManager(MibAccessInterface& mib, SendMessageInterface &messenger) :
        m_mib(mib),
        m_messenger(messenger),
        m_alarmEventLog(ALARM_MGR_MAX_LOG_ALARM_EVENTS)
{
    ENTER();
    string alarmLogFile;

    alarmLogFile += "tr069_alarms";

    m_alarmEventLogFile.reset(new Tr069AlarmEventLogFileMgr(m_alarmEventLog, alarmLogFile.c_str(), ALARM_MGR_MAX_LOG_ALARM_EVENTS));

    EXIT();
}

AlarmManager::~AlarmManager()
{
}

void AlarmManager::Start( void )
{
    if(!m_alarmDespatch)
    {
        m_alarmDespatch.reset(new SupportedAlarmManager(m_mib, m_messenger));

        m_tr069ActiveAlarms.RegisterListener( m_alarmDespatch.get() );
    }
    m_alarmEventLogFile->ReadAllObjects();
    m_nextAlarmEventSequenceNumber = m_alarmEventLogFile->GetNextSequenceNumber();

    m_alarmEventLogFile->StartLogging();

}

void AlarmManager::HandleAlarmEvent(AlarmEvent& alarmEvent)
{
    // Update active alarms.
    m_tr069ActiveAlarms.HandleAlarmEvent(alarmEvent);
    m_alarmEventLog.HandleAlarmEvent(alarmEvent);
}
void AlarmManager::AcceptAlarmEventLogVisitor(AlarmEventListVisitor& eventLogVisitor) const
{
    ENTER();

    m_alarmEventLog.AcceptVisitor(eventLogVisitor);

    EXIT();

}
}
