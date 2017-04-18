
///////////////////////////////////////////////////////////////////////////////
//
// OamtuckAlarms.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <system/Trace.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamStuckAlarms.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

StuckAlarms::StuckAlarms()
{
}

StuckAlarms::~StuckAlarms()
{
    m_stuckAlarms.clear();
}

void StuckAlarms::VisitAlarmEvent(const AlarmEvent& alarmEvent)
{
    shared_ptr<FapAlarmId> airAlarmId = dynamic_pointer_cast<FapAlarmId>(alarmEvent.GetAlarmId());

    u32 numericalAlarmId = airAlarmId->GetNumericAlarmId();

    m_stuckAlarms.erase( numericalAlarmId );

    if(alarmEvent.GetSeverity() != AlarmEvent::ALARM_SEVERITY_CLEARED && alarmEvent.GetLifetime() == AlarmEvent::ALARM_EVENT_NONTRANSIENT)
    {
        m_stuckAlarms[numericalAlarmId] = alarmEvent;
    }
}

void StuckAlarms::Clear(SingleThreadedApplicationWithMessaging & app)
{
    map<u32,AlarmEvent>::iterator i;

    for( i = m_stuckAlarms.begin(); i != m_stuckAlarms.end(); ++i )
    {
        AlarmEvent stuckAlarmEvent = i->second;
        ostringstream oss;

        string additionalText("Clear stuck alarm. ");
        additionalText += stuckAlarmEvent.GetAdditionalInfo();

        AlarmEvent alarmEvent(stuckAlarmEvent.GetAlarmId(),
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_CLEARED,
                              additionalText,
                              stuckAlarmEvent.GetAlarmType());

        app.SendMessage(alarmEvent, ENTITY_OAM);
    }
}
