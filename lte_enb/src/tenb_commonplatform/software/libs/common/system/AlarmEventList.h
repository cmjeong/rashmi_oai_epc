///////////////////////////////////////////////////////////////////////////////
//
// AlarmEventList.h
//
// Abstract class for encapsulating a list of alarm events.  E.g. to provide a
// historical log or to capture current active alarms.
//
// Also provides visitor class for inspecting the list of alarm events.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AlarmEventList_h_
#define __AlarmEventList_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/AlarmEvent.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * A client of AlarmEventList can implement (or have a helper class that
 * implements) AlarmEventListVisitor.  That class is then passed by ref to
 * AcceptVisitor() on AlarmEventList.
 *
 * This is used to get access to all the alarm events in a decoupled and
 * memory efficient way.
 */
class AlarmEventListVisitor
{
public:

    virtual ~AlarmEventListVisitor () {}

    /**
     * Visitor for an AlarmEvent.
     *
     * Provides generic mechanism for calling back to a client with each
     * alarm contained within an AlarmList, regardless of how they are
     * stored internally.
     *
     * \param alarmEvent Each of the alarm events passed back to client.
     */
    virtual void VisitAlarmEvent(const AlarmEvent& alarmEvent) = 0;

};

/**
 * A client of AlarmEventList can implement (or have a helper class that
 * implements) AlarmEventListListener.  That class is then passed by ref to
 * RegisterSubscriber() on AlarmEventList.
 *
 * This is used to implement a callback when a new event occurs e.g. to
 * allow writing events to a file as in AlarmEventLogFileMgr.
 */
class AlarmEventListListener
{
public:

    virtual ~AlarmEventListListener () {}

    /**
     * Listener for an AlarmEvent.
     *
     * Callback into client object on each new alarm event.
     *
     * \param alarmEvent The alarm event that has just occurred.
     */
    virtual void ListenAlarmEvent(const AlarmEvent& alarmEvent) = 0;

};

class AlarmEventList
{
public:

    virtual ~AlarmEventList() {};

    /**
     * Accept a visitor, iterate over all alarm events and callback into client.
     */
    virtual void AcceptVisitor(AlarmEventListVisitor& alarmEventListVisitor) const = 0;

    /**
     * Register a listener to be informed when a new event occurs.
     * Can be used e.g. to write events to a file.
     */
    virtual void RegisterListener(AlarmEventListListener* alarmEventListListener) = 0;

    /**
     * Clear the current list of alarms / alarm events.
     */
    virtual void Clear() = 0;

    /**
     * Handle an alarm event and do something sensible as far as the derived
     * class is concerned.  This will vary e.g. it might get filtered out,
     * it might get munged, it might be stored regardless or used to record
     * 'active' alarms...
     */
    virtual void HandleAlarmEvent(const AlarmEvent& alarmEvent) = 0;

private:

};

}

#endif
