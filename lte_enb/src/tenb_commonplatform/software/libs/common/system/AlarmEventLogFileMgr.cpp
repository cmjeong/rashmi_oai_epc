///////////////////////////////////////////////////////////////////////////////
//
// AlarmEventLogFileMgr.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AlarmEventLogFileMgr.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

AlarmEventLogFileMgr::AlarmEventLogFileMgr(AlarmEventList& alarmEventList, const char * logFileNameStem, u32 minNumAlarmEvents) :
    FiniteSerialisableFileStore(logFileNameStem, minNumAlarmEvents),
    m_alarmEventList(alarmEventList),
    m_updatingEventListFromFile(false),
    m_nextSeqNum(0)
{
    ENTER();

    EXIT();
}

AlarmEventLogFileMgr::~AlarmEventLogFileMgr()
{
    ENTER();

    EXIT();
}

void AlarmEventLogFileMgr::ListenAlarmEvent(const AlarmEvent& alarmEvent)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT_PRINTF(alarmEvent.GetSequenceNumber() >= m_nextSeqNum,
                       "alarmEvent.GetSequenceNumber()=%"PRIu32" m_nextSeqNum=%"PRIu32,
                       (u32)alarmEvent.GetSequenceNumber(), (u32)m_nextSeqNum);

    // Update latest seq num - only for the above test next time this function is called.
    m_nextSeqNum = alarmEvent.GetSequenceNumber() + 1;

    if(!m_updatingEventListFromFile)
    {
        // Write to current event store.
        WriteObject(alarmEvent);
    }

    EXIT();
}

shared_ptr<Serialisable> AlarmEventLogFileMgr::GetSerialisable(u32 serialisationId,
                                                               const u8* serialisedData,
                                                               u32 serialisedDataLen)
{
    ENTER();

    shared_ptr<AlarmEvent> object;

    if(serialisationId == SERIALISATION_ID_ALARM_EVENT)
    {
        object.reset(new AlarmEvent);
        // Use some concrete implementation of GetNewAlarmId() that is
        // specific to the current system/module.
        object->SetAlarmId(GetNewAlarmId());
        object->DeSerialise(serialisedData, serialisedDataLen);
    }

    RETURN(object);
}

void AlarmEventLogFileMgr::StartLogging()
{
    ENTER();

    TRACE_MSG("Starting AlarmEvent logging.");

    FiniteSerialisableFileStore::StartLogging();

    // Register our alarm event listener.
    m_alarmEventList.RegisterListener(this);

    EXIT();
}

void AlarmEventLogFileMgr::StopLogging()
{
    ENTER();

    TRACE_MSG("Stopping AlarmEvent logging.");

    // Stop listening to new events.
    m_alarmEventList.RegisterListener(NULL);

    FiniteSerialisableFileStore::StopLogging();

    EXIT();
}

void AlarmEventLogFileMgr::HandleObjectRead(const shared_ptr<Serialisable> object)
{
    ENTER();

    const shared_ptr<AlarmEvent> alarmEvent = dynamic_pointer_cast<AlarmEvent>(object);

    if(alarmEvent != NULL)
    {
        // Update latest sequence number if this one is greater.
        if(alarmEvent->GetSequenceNumber() >= m_nextSeqNum)
        {
            m_nextSeqNum = alarmEvent->GetSequenceNumber() + 1;
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_CRITICAL,
                             "AlarmEventLogFileMgr::HandleObjectRead(): Hmmm, we just got a sequence number that went backwards... m_nextSeqNum=%u, event=%s",
                              m_nextSeqNum, alarmEvent->ToString().c_str());
        }

        m_updatingEventListFromFile = true;
        m_alarmEventList.HandleAlarmEvent(*alarmEvent);
        m_updatingEventListFromFile = false;
    }

    EXIT();
}

}
