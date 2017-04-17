///////////////////////////////////////////////////////////////////////////////
//
// AlarmEventLog.cpp
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

#include "AlarmEventLog.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

AlarmEventLog::AlarmEventLog(u32 maxLogNumEvents) :
    m_alarmEventListListener(NULL),
    m_maxLogNumEvents(maxLogNumEvents)
{
    ENTER();
    EXIT();
}

AlarmEventLog::~AlarmEventLog()
{
    ENTER();
    EXIT();
}

void AlarmEventLog::AcceptVisitor(AlarmEventListVisitor& alarmEventListVisitor) const
{
    ENTER();

    list<AlarmEvent>::const_iterator iter = m_alarmEvents.begin();

    while(iter != m_alarmEvents.end())
    {
        alarmEventListVisitor.VisitAlarmEvent(*iter);
        ++iter;
    }

    EXIT();
}

void AlarmEventLog::RegisterListener(AlarmEventListListener* alarmEventListListener)
{
    ENTER();

    // Preconditions.
    // Force client into explicitly setting listener to null first if they want to change it.
    // Avoids accidental attempts to have multiple listeners.
    RSYS_ASSERT((m_alarmEventListListener == NULL) || (alarmEventListListener == NULL));

    m_alarmEventListListener = alarmEventListListener;

    EXIT();
}

void AlarmEventLog::Clear()
{
    ENTER();

    TRACE_MSG("Clearing all alarm events from log");
    m_alarmEvents.clear();

    EXIT();
}

void AlarmEventLog::HandleAlarmEvent(const AlarmEvent& alarmEvent)
{
    ENTER();

    TRACE("AlarmEventLog::HandleAlarmEvent()", alarmEvent.ToString().c_str());

    if(m_alarmEvents.size() >= m_maxLogNumEvents)
    {
        m_alarmEvents.pop_front();
    }

    m_alarmEvents.push_back(alarmEvent);

    // Callback to listener if we have one.
    if(m_alarmEventListListener != NULL)
    {
        m_alarmEventListListener->ListenAlarmEvent(alarmEvent);
    }

    EXIT();
}

}
