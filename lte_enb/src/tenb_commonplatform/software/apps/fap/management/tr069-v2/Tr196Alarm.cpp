///////////////////////////////////////////////////////////////////////////////
//
// Tr196Alarm
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/Trace.h>
#include <platform/RadisysFapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr196Alarm.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

Tr196RadisysAlarm::Tr196RadisysAlarm( const threeway::AlarmEvent & alarmEvent ) :
    Tr196Alarm()
{

    shared_ptr<RadisysFapAlarmId> m_radisysFapAlarmId = dynamic_pointer_cast<RadisysFapAlarmId>(alarmEvent.GetAlarmId());
    m_radisysFapAlarmId = dynamic_pointer_cast<RadisysFapAlarmId>(alarmEvent.GetAlarmId());

   // RSYS_ASSERT(m_radisysFapAlarmId);
    RSYS_ASSERT(m_radisysFapAlarmId);

  //  SetAlarmIdentifier( m_radisysFapAlarmId->GetAlarmNumber() );
    SetAlarmIdentifier( m_radisysFapAlarmId->GetAlarmNumber() );
   /* SetPercievedSeverity(
            AlarmEvent::ALARM_SEVERITY_CLEARED == alarmEvent.GetSeverity() ?
                    ALARM_PERCEIVED_SEVERITY_CLEARED
                    : PerceivedSeverityId( m_nsnFapAlarmId->GetAlarmSeverity() ) );
   */
    SetPercievedSeverity(
            AlarmEvent::ALARM_SEVERITY_CLEARED == alarmEvent.GetSeverity() ?
                    ALARM_PERCEIVED_SEVERITY_CLEARED : AlarmPerceivedSeverity( m_radisysFapAlarmId->GetAlarmSeverity() ) );
    SetProbableCause(m_radisysFapAlarmId->GetAlarmText());

    SetEventType( alarmEvent.GetAlarmType() );

    string newAlarmSpecificProblem = alarmEvent.GetAdditionalInfo();
    if( newAlarmSpecificProblem.empty() )
    {
        newAlarmSpecificProblem = m_radisysFapAlarmId->GetAlarmAdditionInfo();
    }
    SetSpecificProblem(newAlarmSpecificProblem);

	string newAlarmAdditionalInfo = alarmEvent.GetAddtnlInfo();
    if( newAlarmAdditionalInfo.empty() )
    {
        newAlarmAdditionalInfo = m_radisysFapAlarmId->GetAlarmAdditionInfo();
    }
    SetAdditionalInformation(newAlarmAdditionalInfo);

    string localTimezoneOffsetToGmt;
    Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LOCAL_TIMEZONE_OFFSET_TO_GMT,localTimezoneOffsetToGmt);
    SetEventTime( alarmEvent.GetObservationTime().ToString(localTimezoneOffsetToGmt.c_str()) );

    //m_sequenceNumber = alarmEvent.GetSequenceNumber();


}

std::string Tr196RadisysAlarm::ToString()
{
    stringstream ss;

    ss << "todo: Tr196RadisysAlarm::ToString()";
    //oss << m_sequenceNumber << " " << m_alarmRiseTime << " " << (m_alarmActivity==NsnFapAlarmId::CLEARED?'x': char('0' + u32(m_alarmPerceivedSeverity))) << " " << m_alarmProbableCause << " " << m_alarmSpecificProblem;

    return ss.str();
}

}

