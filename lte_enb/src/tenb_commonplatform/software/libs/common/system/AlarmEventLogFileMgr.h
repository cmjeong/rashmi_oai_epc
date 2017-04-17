///////////////////////////////////////////////////////////////////////////////
//
// AlarmEventLogFileMgr.h
//
// Manage a file for storing and retrieving historical alarm events.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AlarmEventLogFileMgr_h_
#define __AlarmEventLogFileMgr_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/AlarmEventLog.h>
#include <system/FiniteSerialisableFileStore.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class AlarmEventLogFileMgr : public FiniteSerialisableFileStore,
                             public AlarmEventListListener // so we can receive new events to write to file
{
public:

    /**
     * Constructor.
     *
     * \param alarmEventList    Reference to object maintaining the alarm event list.
     * \param logFileName       Path and file name to log file.
     * \param minNumAlarmEvents Minimum number of alarm events to be stored.
     */
    AlarmEventLogFileMgr(AlarmEventList& alarmEventList, const char * logFileNameStem, u32 minNumAlarmEvents);

    virtual ~AlarmEventLogFileMgr();

    /**
     * Implement AlarmEventListListener.
     */
    virtual void ListenAlarmEvent(const AlarmEvent& alarmEvent);

    /**
     * Implement SerialisableFactory.  Used when we read
     * objects from the alarm log file(s).
     */
    virtual boost::shared_ptr<Serialisable> GetSerialisable(u32 serialisationId,
                                                            const u8* serialisedData,
                                                            u32 serialisedDataLen);

    /**
     * Get a new AlarmId object for this particular alarm event store.
     *
     * AlarmId is just an interface.  Any particular system has to define
     * a concrete alarm ID for that system - typically an enum of alarm IDs.
     * Therefore this file store class, on reading alarm events from file, has
     * to be able to get a concrete alarm ID in order to deserialise the alarm
     * event properly.  This is the only thing a derived class *has* to implement.
     */
    virtual boost::shared_ptr<AlarmId> GetNewAlarmId() = 0;

    /**
     * Open log file, read any existing alarm events so we know how many
     * there are and register a listener for new events.
     */
    virtual void StartLogging();

    /**
     * Drop our event listener and close the file.
     */
    virtual void StopLogging();

    /**
     * After a call to ReadAllObjects() you can query the next sequence number
     * to use in subsequent alarm events.
     *
     * \return Next sequence number to be used in alarm events.
     *         Be careful to respect this as this class relies on
     *         sequence numbers being continually increasing.
     */
    u32 GetNextSequenceNumber() { return m_nextSeqNum; };

    /**
     * Override base class hooks.
     */
    virtual void HandleObjectRead(const shared_ptr<Serialisable> object);

private:

    /**
     * Reference to the list of alarm events that we are going to store to file
     * and populate on reading the file.
     */
    AlarmEventList& m_alarmEventList;

    /**
     * Set true when we are reading from file and updating the event list
     * so that we can stop listening to new events through AlarmEventListListener.
     */
    bool m_updatingEventListFromFile;

    /**
     * Next sequence number to use in the files.  Updated when we first read out
     * of the log files and when we subsequently write to them.
     */
    u32 m_nextSeqNum;

};

}

#endif
