///////////////////////////////////////////////////////////////////////////////
//
// AlarmEventLog.h
//
// Maintains a historical log of alarms.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AlarmEventLog_h_
#define __AlarmEventLog_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <list>

#include <system/AlarmEvent.h>
#include <system/AlarmEventList.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class AlarmEventLog : public AlarmEventList
{
public:

    AlarmEventLog(u32 maxLogNumEvents);
    virtual ~AlarmEventLog();

    /**
     * Implement AlarmEventList.
     */
    void AcceptVisitor(AlarmEventListVisitor& alarmEventListVisitor) const;
    void RegisterListener(AlarmEventListListener* alarmEventListListener);
    void Clear();
    void HandleAlarmEvent(const AlarmEvent& alarmEvent);

private:
    /**
     * Store client to callback to on new alarm events.
     */
    AlarmEventListListener* m_alarmEventListListener;

    /**
     * Maximum number of events this log can hold.
     * Old ones get discarded.
     */
    u32 m_maxLogNumEvents;

    /**
     * List of historical alarm events.
     * STL list works well as we need to be able to add to one end and delete from the other.
     */
    std::list<AlarmEvent> m_alarmEvents;

};

}

#endif
