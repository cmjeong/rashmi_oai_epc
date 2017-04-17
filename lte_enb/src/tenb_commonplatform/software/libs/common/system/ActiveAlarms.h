///////////////////////////////////////////////////////////////////////////////
//
// ActiveAlarms.h
//
// Maintains a list of current alarms.
//
// Current alarms are those that have been raised but not cleared and are
// non-transient.  Transient alarms are ignored as they don't have a life
// cycle - it doesn't make sense to talk of active transient alarms.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ActiveAlarms_h_
#define __ActiveAlarms_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>

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

class ActiveAlarms : public AlarmEventList
{
public:

    ActiveAlarms();
    virtual ~ActiveAlarms();

    /**
     * Implement AlarmEventList.
     */
    void AcceptVisitor(AlarmEventListVisitor& alarmEventListVisitor) const;
    void RegisterListener(AlarmEventListListener* alarmEventListListener);
    void Clear();
    void HandleAlarmEvent(const AlarmEvent& alarmEvent);

    /**
     * Get the highest (worst) severity of all active alarms.
     *
     * \return Highest active alarm severity.
     */
    AlarmEvent::AlarmSeverity GetHighestActiveSeverity() const;

private:
    /**
     * Store client to callback to on new alarm events.
     */
    AlarmEventListListener* m_alarmEventListListener;

    // Typedefs

    typedef std::map<u32 /* alarm id */, AlarmEvent> ActiveAlarmsList;

    /**
     * List of active alarm events.
     * STL map gives us easy access to specific alarms.
     */
    ActiveAlarmsList m_activeAlarms;

};

}

#endif
