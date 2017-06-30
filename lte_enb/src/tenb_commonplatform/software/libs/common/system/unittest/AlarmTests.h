///////////////////////////////////////////////////////////////////////////////
//
// AlarmTests.h
//
// Unit tests for various classes relating to alarms.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AlarmEventTest_h_
#define __AlarmEventTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <unistd.h>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/AlarmId.h>
#include <system/AlarmEvent.h>
#include <system/AlarmEventLog.h>
#include <system/AlarmEventLogFileMgr.h>
#include <system/ActiveAlarms.h>

using namespace threeway;
using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TestAlarmId : public AlarmId
{
public:

    // Typedefs
    typedef enum
    {
        TEST_ALARM_1 = 0,
        TEST_ALARM_2,
        TEST_ALARM_3,
        TEST_ALARM_4
    } Id;

    /**
     * Construct with an alarm ID.
     */
    TestAlarmId(Id id) : m_testAlarmId(id) {};
    virtual ~TestAlarmId() {};

    /**
     * Implement AlarmId.
     */
    virtual void SetNumericAlarmId(u32 id) { m_testAlarmId = (Id)id; };
    virtual u32 GetNumericAlarmId() const { return (u32)m_testAlarmId; };
    virtual std::string ToString() const { return "Can't be arsed"; };

    /**
     * Get alarm ID as enum.
     */
    Id GetTestAlarmId() const { return m_testAlarmId; };

private:

    // Alarm ID.
    Id m_testAlarmId;

};

class TestAlarmEventLogFileMgr : public AlarmEventLogFileMgr
{
public:
    TestAlarmEventLogFileMgr(AlarmEventList& alarmEventList, const char * logFileName, u32 minNumAlarmEvents) :
        AlarmEventLogFileMgr(alarmEventList, logFileName, minNumAlarmEvents) {};
    virtual ~TestAlarmEventLogFileMgr() {};

    virtual shared_ptr<AlarmId> GetNewAlarmId()
    {
        shared_ptr<AlarmId> alarmId(new TestAlarmId(TestAlarmId::TEST_ALARM_1));
        return alarmId;
    }

};

class AlarmEventTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "****************" << endl
             << "AlarmEvent tests" << endl
             << "****************" << endl << endl;

        TRACE_MSG("Constructing alarmEvent.");

        shared_ptr<TestAlarmId> alarmId(new TestAlarmId(TestAlarmId::TEST_ALARM_1));
        AlarmEvent alarmEvent(alarmId,
                              AlarmEvent::ALARM_EVENT_TRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_MAJOR,
                              "This is the additional info",
                              AlarmEvent::ALARM_TYPE_EQUIPMENT);

        TRACE_MSG("Serialising alarmEvent.");
        u8 serialisedBuffer[1024];
        s32 serialisedLen = alarmEvent.Serialise(serialisedBuffer, sizeof(serialisedBuffer));

        TRACE_MSG("Check serialisation length.");
        CPPUNIT_ASSERT_MESSAGE("Check serialisation length", serialisedLen == 49);

        TRACE_MSG("Constructing alarmEvent2.");
        shared_ptr<TestAlarmId> alarmId2(new TestAlarmId(TestAlarmId::TEST_ALARM_1)); // Actual alarm ID doesn't matter
        AlarmEvent alarmEvent2;
        alarmEvent2.SetAlarmId(alarmId2); // Set alarm ID object before deserialising.

        TRACE_MSG("Deserialising alarmEvent data into alarmEvent2.");
        alarmEvent2.DeSerialise(serialisedBuffer, serialisedLen);

        TRACE_MSG("Checking serialise/deserialise all worked.");
        shared_ptr<TestAlarmId> checkAlarmId = dynamic_pointer_cast<TestAlarmId>(alarmEvent2.GetAlarmId());
        CPPUNIT_ASSERT_MESSAGE("Check alarm ID matches", checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_1);
        CPPUNIT_ASSERT_MESSAGE("Check alarm lifetime matches", alarmEvent2.GetLifetime() == AlarmEvent::ALARM_EVENT_TRANSIENT);
        CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent2.GetSeverity() == AlarmEvent::ALARM_SEVERITY_MAJOR);
        CPPUNIT_ASSERT_MESSAGE("Check additional info matches", alarmEvent2.GetAdditionalInfo() == "This is the additional info");
        CPPUNIT_ASSERT_MESSAGE("Check alarm type matches", alarmEvent2.GetAlarmType() == AlarmEvent::ALARM_TYPE_EQUIPMENT);

        TRACE_MSG("Checking sequence number.");
        alarmEvent2.SetSequenceNumber(23);
        CPPUNIT_ASSERT_MESSAGE("Check sequence number", alarmEvent2.GetSequenceNumber() == 23);

        fflush(stdout);
    }

private:
};

class AlarmEventLogTest : public CppUnit::TestCase, public AlarmEventListVisitor
{
public:
    AlarmEventLogTest() :
        m_alarmEventCount(0)
    {
    }

    void VisitAlarmEvent(const AlarmEvent& alarmEvent)
    {
        TRACE_PRINTF("AlarmEvent visitor got event %" PRIu32 " and it was %s", m_alarmEventCount, alarmEvent.ToString().c_str());

        shared_ptr<TestAlarmId> checkAlarmId = dynamic_pointer_cast<TestAlarmId>(alarmEvent.GetAlarmId());
        switch(m_alarmEventCount)
        {
        case 0:
        case 6:
            CPPUNIT_ASSERT_MESSAGE("Check alarm ID matches", checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_1);
            CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_MAJOR);
            break;
        case 1:
        case 3:
        case 7:
            CPPUNIT_ASSERT_MESSAGE("Check alarm ID matches", checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_2);
            CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_CRITICAL);
            break;
        case 2:
        case 4:
        case 8:
            CPPUNIT_ASSERT_MESSAGE("Check alarm ID matches", checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_2);
            CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_CLEARED);
            break;
        case 5:
        case 9:
            CPPUNIT_ASSERT_MESSAGE("Check alarm ID matches", checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_3);
            CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_MINOR);
            break;
        }

        m_alarmEventCount++;
    }

    void runTest()
    {
        cout << endl << endl
             << "*******************" << endl
             << "AlarmEventLog tests" << endl
             << "*******************" << endl << endl;

        // Delete any existing alarm event log file.
        BinaryFile alarmEventFile0("./alarmeventlogfile-0");
        alarmEventFile0.Delete();
        BinaryFile alarmEventFile1("./alarmeventlogfile-1");
        alarmEventFile1.Delete();

        TRACE_MSG("Constructing AlarmEventLog.");
        shared_ptr<AlarmEventLog> alarmEventLog(new AlarmEventLog(3));

        TRACE_MSG("Constructing TestAlarmEventLogFileMgr");

        shared_ptr<TestAlarmEventLogFileMgr> logFileMgr(new TestAlarmEventLogFileMgr(*alarmEventLog, "./alarmeventlogfile", 3));
        logFileMgr->ReadAllObjects();
        u32 nextSeqNum = logFileMgr->GetNextSequenceNumber();
        logFileMgr->StartLogging();

        CPPUNIT_ASSERT_MESSAGE("Check latest sequence number is 0 - we have empty log files.", nextSeqNum == 0);

        TRACE_MSG("Let's go visit that log... should be empty.");
        alarmEventLog->AcceptVisitor(*this);

        TRACE_MSG("Adding 3 alarm events to the log.");
        shared_ptr<TestAlarmId> alarmId1(new TestAlarmId(TestAlarmId::TEST_ALARM_1));
        AlarmEvent alarmEvent1(alarmId1,
                              AlarmEvent::ALARM_EVENT_TRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_MAJOR,
                              "This is the first alarm event - transient",
                              AlarmEvent::ALARM_TYPE_EQUIPMENT);
        alarmEvent1.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent1);

        shared_ptr<TestAlarmId> alarmId2(new TestAlarmId(TestAlarmId::TEST_ALARM_2));
        AlarmEvent alarmEvent2(alarmId2,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_CRITICAL,
                              "This is the second alarm event - raise an alarm",
                              AlarmEvent::ALARM_TYPE_QOS);
        alarmEvent2.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent2);

        AlarmEvent alarmEvent3(alarmId2,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_CLEARED,
                              "This is the third alarm event - clear the previous alarm",
                              AlarmEvent::ALARM_TYPE_QOS);
        alarmEvent3.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent3);

        TRACE_MSG("Let's go visit that log...");
        alarmEventLog->AcceptVisitor(*this);

        CPPUNIT_ASSERT_MESSAGE("Check correct number of events", m_alarmEventCount == 3);

        TRACE_MSG("There were 3 in the bed and the little one said... adding 4th event which should push oldest one out.");
        shared_ptr<TestAlarmId> alarmId3(new TestAlarmId(TestAlarmId::TEST_ALARM_3));
        AlarmEvent alarmEvent4(alarmId3,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_MINOR,
                              "This is the 4th alarm event - should displace first",
                              AlarmEvent::ALARM_TYPE_QOS);
        alarmEvent4.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent4);

        TRACE_MSG("Let's go visit that log again...");
        alarmEventLog->AcceptVisitor(*this);

        // We've visited it twice and both times it should have had 3 events in it, total 6.
        CPPUNIT_ASSERT_MESSAGE("Check correct number of events after adding 4th", m_alarmEventCount == 6);

        // Add 3 more in to make sure we rotate through our log files.
        TRACE_MSG("Add 3 more to make sure we rotate log files...");
        alarmEvent1.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent1);
        alarmEvent2.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent2);
        alarmEvent3.SetSequenceNumber(nextSeqNum++);
        alarmEventLog->HandleAlarmEvent(alarmEvent3);

        // Stop logging and remove our memory resident objects.
        logFileMgr->StopLogging();
        logFileMgr.reset();
        alarmEventLog.reset();

        TRACE_MSG("Constructing AlarmEventLog again.");
        alarmEventLog.reset(new AlarmEventLog(3));

        TRACE_MSG("Constructing TestAlarmEventLogFileMgr again.");

        logFileMgr.reset(new TestAlarmEventLogFileMgr(*alarmEventLog, "./alarmeventlogfile", 3));
        logFileMgr->ReadAllObjects();
        logFileMgr->StartLogging();

        TRACE("Next sequence number to use", nextSeqNum);

        CPPUNIT_ASSERT_MESSAGE("Check next sequence number is 7 - we've already used 0-6.", nextSeqNum == 7);

        TRACE_MSG("Let's go visit that log again...");
        alarmEventLog->AcceptVisitor(*this);

        // TODO... more tests...
        //    - add more events and check ok
        //    - make sure oldest seq num stuff works


        fflush(stdout);
    }

private:
    u32 m_alarmEventCount;
};


class ActiveAlarmsTest : public CppUnit::TestCase, public AlarmEventListVisitor
{
public:
    ActiveAlarmsTest() :
        m_gotAlarm1(false),
        m_gotAlarm2(false)
    {
    }

    void VisitAlarmEvent(const AlarmEvent& alarmEvent)
    {
        TRACE_PRINTF("AlarmEvent visitor got event %s", alarmEvent.ToString().c_str());

        CPPUNIT_ASSERT_MESSAGE("Check alarm lifetime is non-transient", alarmEvent.GetLifetime() == AlarmEvent::ALARM_EVENT_NONTRANSIENT);

        shared_ptr<TestAlarmId> checkAlarmId = dynamic_pointer_cast<TestAlarmId>(alarmEvent.GetAlarmId());
        if(checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_1)
        {
            CPPUNIT_ASSERT_MESSAGE("Check we haven't already had this alarm", m_gotAlarm1 == false);
            CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_CRITICAL);
            m_gotAlarm1 = true;
        }
        else if(checkAlarmId->GetTestAlarmId() == TestAlarmId::TEST_ALARM_2)
        {
            CPPUNIT_ASSERT_MESSAGE("Check we haven't already had this alarm", m_gotAlarm2 == false);
            CPPUNIT_ASSERT_MESSAGE("Check alarm severity matches", alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_MAJOR);
            m_gotAlarm2 = true;
        }
        else
        {
            CPPUNIT_FAIL("Wrong alarm ID");
        }
    }

    void runTest()
    {
        cout << endl << endl
             << "******************" << endl
             << "ActiveAlarms tests" << endl
             << "******************" << endl << endl;

        TRACE_MSG("Constructing activeAlarms.");
        ActiveAlarms activeAlarms;

        CPPUNIT_ASSERT_MESSAGE("Check highest severity", activeAlarms.GetHighestActiveSeverity() == AlarmEvent::ALARM_SEVERITY_CLEARED);

        TRACE_MSG("Adding 3 alarm events to the log.  1 non-transient+critical, 1 non-transient+major, 1 transient+major");
        shared_ptr<TestAlarmId> alarmId1(new TestAlarmId(TestAlarmId::TEST_ALARM_1));
        AlarmEvent alarmEvent1(alarmId1,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_CRITICAL,
                              "Raise 1st alarm",
                              AlarmEvent::ALARM_TYPE_EQUIPMENT);
        activeAlarms.HandleAlarmEvent(alarmEvent1);

        CPPUNIT_ASSERT_MESSAGE("Check highest severity", activeAlarms.GetHighestActiveSeverity() == AlarmEvent::ALARM_SEVERITY_CRITICAL);

        shared_ptr<TestAlarmId> alarmId2(new TestAlarmId(TestAlarmId::TEST_ALARM_2));
        AlarmEvent alarmEvent2(alarmId2,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_MAJOR,
                              "Raise 2nd alarm",
                              AlarmEvent::ALARM_TYPE_QOS);
        activeAlarms.HandleAlarmEvent(alarmEvent2);

        CPPUNIT_ASSERT_MESSAGE("Check highest severity", activeAlarms.GetHighestActiveSeverity() == AlarmEvent::ALARM_SEVERITY_CRITICAL);

        shared_ptr<TestAlarmId> alarmId3(new TestAlarmId(TestAlarmId::TEST_ALARM_3));
        AlarmEvent alarmEvent3(alarmId3,
                              AlarmEvent::ALARM_EVENT_TRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_MAJOR,
                              "Raise 3rd alarm (transient)",
                              AlarmEvent::ALARM_TYPE_QOS);
        activeAlarms.HandleAlarmEvent(alarmEvent3);

        TRACE_MSG("Let's go visit those active alarms...");
        activeAlarms.AcceptVisitor(*this);

        TRACE_MSG("Clear active alarms...");
        AlarmEvent alarmEvent4(alarmId1,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_CLEARED,
                              "Clear 1st alarm",
                              AlarmEvent::ALARM_TYPE_EQUIPMENT);
        activeAlarms.HandleAlarmEvent(alarmEvent4);

        CPPUNIT_ASSERT_MESSAGE("Check highest severity", activeAlarms.GetHighestActiveSeverity() == AlarmEvent::ALARM_SEVERITY_MAJOR);

        AlarmEvent alarmEvent5(alarmId2,
                              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                              AlarmEvent::ALARM_SEVERITY_CLEARED,
                              "Clear 2nd alarm",
                              AlarmEvent::ALARM_TYPE_QOS);
        activeAlarms.HandleAlarmEvent(alarmEvent5);

        CPPUNIT_ASSERT_MESSAGE("Check highest severity", activeAlarms.GetHighestActiveSeverity() == AlarmEvent::ALARM_SEVERITY_CLEARED);

        TRACE_MSG("Let's go visit those active alarms again... should be none there...");
        activeAlarms.AcceptVisitor(*this);

        fflush(stdout);
    }

private:
    bool m_gotAlarm1;
    bool m_gotAlarm2;
};

#endif
