///////////////////////////////////////////////////////////////////////////////
//
// Tr069CurrentAlarmManager
//
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069CurrentAlarmManager_h_
#define __Tr069CurrentAlarmManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <messaging/transport/MibAccessInterface.h>
#include <messaging/transport/Messenger.h>
#include <system/AlarmEvent.h>
#include <system/AlarmPerceivedSeverity.h>
#include <MibAttributeId.h>
#include <mib-common/MibDN.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr196Alarm.h"
#include "Tr069ParameterList.h"
#include "Tr069SupportedAlarm.h"

using namespace std;

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

class CurrentAlarm
{
public:
    CurrentAlarm( shared_ptr<Tr196Alarm> tr196Alarm ) :
        m_tr196Alarm(tr196Alarm),
        m_riseTime(tr196Alarm->GetEventTime()),
        m_notificationType("NewAlarm")
    {

    }

    bool CompareAlarmIdentifier( shared_ptr<Tr196Alarm> tr196Alarm )
    {
        bool sameAlarm = (m_tr196Alarm->GetAlarmIdentifier() == tr196Alarm->GetAlarmIdentifier() );

        return sameAlarm;
    }

    void Update( shared_ptr<Tr196Alarm> tr196Alarm )
    {
        if(CompareAlarmIdentifier(tr196Alarm))
        {
            if( tr196Alarm->GetPercievedSeverity() == AlarmPerceivedSeverityToString(ALARM_PERCEIVED_SEVERITY_CLEARED) )
            {
                m_notificationType = "ClearedAlarm";
            }
            else
            {
                m_notificationType = "ChangedAlarm";
            }
        }
        else
        {
            TRACE_PRINTF("CurrentAlarm::Update wrong alarm.");
        }
    }

    shared_ptr<Tr196Alarm> GetAlarm() { return m_tr196Alarm;}
    string GetNotificationType() { return m_notificationType;}
private:
    shared_ptr<Tr196Alarm> m_tr196Alarm;
    string m_riseTime;
    string m_notificationType;
};

typedef u32 CurrentAlarmIdx;

typedef map<CurrentAlarmIdx, shared_ptr<CurrentAlarm> > CurrentAlarms;

class CurrentAlarmManager
{
public:
typedef enum m_notificationType
    {
        NewAlarm,
	ChangedAlarm,
        ClearedAlarm
    } M_notificationType;

    CurrentAlarmManager( MibAccessInterface& mib, SendMessageInterface &messenger ) :
        m_mib(mib),
        m_messenger(messenger),
        m_nextSequentialAlarmIdentifier(0)
    {}

    virtual ~CurrentAlarmManager(){};

    void SupportedAlarmEvent( const SupportedAlarm & supportedAlarm, const AlarmEvent & alarmEvent );

private:
    MibAccessInterface& m_mib;
    SendMessageInterface &m_messenger;

    typedef u32 AlarmIdentifier;
    map<string /* ProbableCause */, MibDN > m_raisedCurrentAlarms;
    map<string /* ProbableCause */, MibDN > m_raisedHistoryAlarms;
    map<string /* ProbableCause */, MibDN > m_raisedExpeditedAlarms;
    map<string /* ProbableCause */, MibDN > m_raisedQueuedAlarms;
    AlarmIdentifier m_nextSequentialAlarmIdentifier;
    //CurrentAlarms m_currentAlarms;
    std::string m_toString;
    set<CurrentAlarmIdx> m_pendingExpedite;

    void RaiseAlarm( const SupportedAlarm & supportedAlarm, const AlarmEvent & alarmEvent );
    void ClearAlarm( const SupportedAlarm & supportedAlarm, const AlarmEvent & alarmEvent );
    void AddExpeditedAlarmsToParameterList( ParameterList & parameterList );

    void UpdateHighestSeverityAlarmStatus();

};


}

#endif
