///////////////////////////////////////////////////////////////////////////////
//
// Tr196Alarm.h
//
// Class representing a TR069
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr196Alarm_h_
#define __Tr196Alarm_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <boost/shared_ptr.hpp>
#include <system/AlarmEvent.h>
#include <system/AlarmPerceivedSeverity.h>
#include <system/AlarmEventType.h>
#include <platform/RadisysFapAlarmId.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Tr196Alarm
{
public:
    Tr196Alarm() :
        m_eventTime("0001-01-01T00:00:00Z"),
        m_perceivedSeverity("Indeterminate")
    {

    }
    virtual ~Tr196Alarm(){}

    const string & GetAlarmIdentifier( void ) const { return m_alarmIdentifier; }
    const string & GetEventTime( void ) const { return m_eventTime; }
    const string & GetEventType( void ) const { return m_eventType; }
    const string & GetProbableCause( void ) const { return m_probableCause; }
    const string & GetSpecificProblem( void ) const { return m_specificProblem; }
    const string & GetPercievedSeverity( void ) const { return m_perceivedSeverity; }
    const string & GetAdditionalText( void ) const { return m_additionalText; }
    const string & GetAdditionalInformation( void ) const { return m_additionalInformation; }

protected:
    void SetAlarmIdentifier( const string & value ) { m_alarmIdentifier = value; }
    void SetEventTime( const string & value ) { m_eventTime = value; }
    void SetEventType( AlarmEventType value ) { m_eventType = AlarmEventTypeToString(value); }
    void SetProbableCause( const string & value ) { m_probableCause = value; }
    void SetSpecificProblem( const string & value ) { m_specificProblem = value; }
    void SetPercievedSeverity( AlarmPerceivedSeverity value ) { m_perceivedSeverity = AlarmPerceivedSeverityToString(value); }
    void SetAdditionalText( const string & value ) { m_additionalText = value; }
    void SetAdditionalInformation( const string & value ) { m_additionalInformation = value; }

private:
    string m_alarmIdentifier;
    string m_eventTime;
    string m_eventType;
    string m_probableCause;
    string m_specificProblem;
    string m_perceivedSeverity;
    string m_additionalText;
    string m_additionalInformation;
};

class Tr196RadisysAlarm : public Tr196Alarm
{
public:
    Tr196RadisysAlarm( const AlarmEvent & alarmEvent );
    ~Tr196RadisysAlarm() {};

    std::string ToString();

private:
    void SetAlarmIdentifier( u32 value )
    {
        stringstream ss;

        ss << value;
        Tr196Alarm::SetAlarmIdentifier( ss.str() );
    }

    void SetEventType( AlarmEvent::AlarmType alarmType )
    {
        stringstream ss;

        switch(alarmType)
        {
            case AlarmEvent::ALARM_TYPE_COMMUNICATIONS:
                Tr196Alarm::SetEventType(ALARM_EVENT_TYPE_COMMUNICATION_FAULURE);
                break;
            case AlarmEvent::ALARM_TYPE_QOS:
                Tr196Alarm::SetEventType(ALARM_EVENT_TYPE_QUALITY_OF_SERVICE);
                break;
            case AlarmEvent::ALARM_TYPE_PROCESSING:
                Tr196Alarm::SetEventType(ALARM_EVENT_TYPE_PROCESSING_FAILURE);
                break;
            case AlarmEvent::ALARM_TYPE_EQUIPMENT:
                Tr196Alarm::SetEventType(ALARM_EVENT_TYPE_EQUIPMENT_FAILURE);
                break;
            case AlarmEvent::ALARM_TYPE_ENVIRONMENT:
                Tr196Alarm::SetEventType(ALARM_EVENT_TYPE_ENVIRONMENT_FAILURE);
                break;
        }
    }
};


}

#endif
