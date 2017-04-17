///////////////////////////////////////////////////////////////////////////////
//
// ActiveAlarms.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ActiveAlarms.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ActiveAlarms::ActiveAlarms() :
    m_alarmEventListListener(NULL)
{
    ENTER();
    EXIT();
}

ActiveAlarms::~ActiveAlarms()
{
    ENTER();
    EXIT();
}

void ActiveAlarms::AcceptVisitor(AlarmEventListVisitor& alarmEventListVisitor) const
{
    ENTER();

    ActiveAlarmsList::const_iterator iter = m_activeAlarms.begin();

    while(iter != m_activeAlarms.end())
    {
        alarmEventListVisitor.VisitAlarmEvent(iter->second);
        ++iter;
    }

    EXIT();
}

void ActiveAlarms::Clear()
{
    ENTER();

    TRACE_MSG("Clearing all active alarms");
    m_activeAlarms.clear();

    EXIT();
}

void ActiveAlarms::RegisterListener(AlarmEventListListener* alarmEventListListener)
{
    ENTER();

    // Preconditions.
    // Force client into explicitly setting listener to null first if they want to change it.
    // Avoids accidental attempts to have multiple listeners.
    RSYS_ASSERT((m_alarmEventListListener == NULL) || (alarmEventListListener == NULL));

    m_alarmEventListListener = alarmEventListListener;

    EXIT();
}

void ActiveAlarms::HandleAlarmEvent(const AlarmEvent& alarmEvent)
{
    ENTER();

    bool alarmListModified = false;

    ActiveAlarmsList::iterator iter = m_activeAlarms.find(alarmEvent.GetAlarmId()->GetNumericAlarmId());

    if(alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_CLEARED)
    {
        if(iter == m_activeAlarms.end())
        {
            TRACE("UpdateAlarmEvent(): Cleared alarm not found in active alarms list", alarmEvent.ToString().c_str());
        }
        else
        {
            alarmListModified = true;

            TRACE("UpdateAlarmEvent(): Clearing active alarm", alarmEvent.ToString().c_str());
            m_activeAlarms.erase(iter);
        }
    }
    else
    {
        alarmListModified = true;

        if(iter == m_activeAlarms.end())
        {
            TRACE("UpdateAlarmEvent(): Raising alarm", alarmEvent.ToString().c_str());
        }
        else
        {
            TRACE("UpdateAlarmEvent(): Updating already raised alarm", alarmEvent.ToString().c_str());
        }
        m_activeAlarms[alarmEvent.GetAlarmId()->GetNumericAlarmId()] = alarmEvent;
    }

    // Callback to listener if we have one.
    if( alarmListModified && m_alarmEventListListener != NULL)
    {
        m_alarmEventListListener->ListenAlarmEvent(alarmEvent);
    }

    EXIT();
}

AlarmEvent::AlarmSeverity ActiveAlarms::GetHighestActiveSeverity() const
{
    ENTER();

    AlarmEvent::AlarmSeverity highestActiveSeverity = AlarmEvent::ALARM_SEVERITY_CLEARED;

    ActiveAlarmsList::const_iterator iter = m_activeAlarms.begin();
    while(iter != m_activeAlarms.end())
    {
        if(iter->second.GetSeverity() > highestActiveSeverity)
        {
            highestActiveSeverity = iter->second.GetSeverity();
        }
        ++iter;
    }

    RETURN(highestActiveSeverity);
}

}
