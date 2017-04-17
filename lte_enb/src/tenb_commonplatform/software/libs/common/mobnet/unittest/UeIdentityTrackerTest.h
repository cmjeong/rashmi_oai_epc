///////////////////////////////////////////////////////////////////////////////
//
// UeIdentityTrackerTest.h
//
// Unit tests for UeIdentityTracker class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UeIdentityTrackerTest_h_
#define __UeIdentityTrackerTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <mobnet/UeIdentityTracker.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

enum TimestamperState
{
    TS_INCREMENT,
    TS_GO_TO_TWO_HOURS
};

class TestTimerEngine : public TimerEngineInterface
{
    virtual TimerHandle CreateTimer(const std::string& timerName,
                                    u32 timeoutPeriodMs,
                                    TimerNotifyInterface& timerNotifyInterface,
                                    TimerStart startNow = TIMER_START_NOW,
                                    TimerMode timerMode = TIMER_SINGLE_SHOT,
                                    bool traceTimerEvents = true) { TRACE("Creating timer", timerName); CPPUNIT_ASSERT_MESSAGE("Check timer started", startNow == TIMER_START_NOW); return 0; }

    virtual TimerHandle CreateWallClockTimer(const std::string& timerName,
                                             u32 timeoutPeriodMinutes,
                                             TimerNotifyInterface& timerNotifyInterface,
                                             TimerStart startNow = TIMER_START_NOW,
                                             TimerMode timerMode = TIMER_REPEAT,
                                             bool traceTimerEvents = true) { RSYS_ASSERT_FAIL("Unused"); return 0; }

    virtual void ModifyTimer(TimerHandle timerHandle, u32 timeoutPeriodMs) { RSYS_ASSERT_FAIL("Unused"); }

    virtual void StartTimer(TimerHandle timerHandle) { TRACE("Starting timer", timerHandle); }

    virtual void StopTimer(TimerHandle timerHandle) { TRACE("Stopping timer", timerHandle); }

    virtual void DeleteTimer(TimerHandle timerHandle) { TRACE("Deleting timer", timerHandle); }

    virtual bool IsTimerRunning(TimerHandle timerHandle) const { RSYS_ASSERT_FAIL("Unused"); return false; }
    virtual uptime_t GetTickCountMs() const { RSYS_ASSERT_FAIL("Unused"); return 0; }
    virtual std::string ToString() const { RSYS_ASSERT_FAIL("Unused"); return ""; }
};

class TestTimestamper : public TimestamperInterface
{
public:
    TestTimestamper() { m_state = TS_INCREMENT; m_timestamp = 0; }

    virtual u32 GetTimestampSecs()
    {
        switch(m_state)
        {
        case TS_INCREMENT:
            m_timestamp++;
            break;
        case TS_GO_TO_TWO_HOURS:
            m_timestamp = 2 * 60 * 60;
            break;
        }

        TRACE("Timestamp", m_timestamp);
        return m_timestamp;
    }

    TimestamperState m_state;
    u32 m_timestamp;
};

class UeIdentityTrackerTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***********************" << endl
             << "UeIdentityTracker tests" << endl
             << "***********************" << endl << endl;

        TestTimerEngine timerEngine;
        TestTimestamper timestamper;

        UeIdentityTracker ueIdentityTracker(timerEngine, timestamper);

        // Try looking up TMSI without having mapping
        u8 tmsiDigits[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
        TMSI tmsi(tmsiDigits);
        IMSI imsi;
        bool foundImsi = ueIdentityTracker.FindIMSIFromTMSI(tmsi, imsi);
        CPPUNIT_ASSERT_MESSAGE("Checking didn't find IMSI from TMSI", foundImsi == false);
        foundImsi = ueIdentityTracker.FindIMSIFromPTMSI(tmsi, imsi);
        CPPUNIT_ASSERT_MESSAGE("Checking didn't find IMSI from P-TMSI", foundImsi == false);

        // Now associate TMSI with IMSI
        IMSI knownImsi("123456789abcdef");
        ueIdentityTracker.RecordNewTMSI(knownImsi, tmsi);
        foundImsi = ueIdentityTracker.FindIMSIFromTMSI(tmsi, imsi);
        TRACE("Found IMSI", imsi.ToString());
        CPPUNIT_ASSERT_MESSAGE("Checking did find IMSI from TMSI", foundImsi == true);
        foundImsi = ueIdentityTracker.FindIMSIFromPTMSI(tmsi, imsi);
        CPPUNIT_ASSERT_MESSAGE("Checking didn't find IMSI from P-TMSI", foundImsi == false);
        TRACE_PRINTF("Map:\n%s", ueIdentityTracker.ToString().c_str());

        // Now accelerate time and garbage collect.
        timestamper.m_state = TS_GO_TO_TWO_HOURS;
        ueIdentityTracker.NotifyTimerExpiry(0);
        TRACE_PRINTF("Map:\n%s", ueIdentityTracker.ToString().c_str());

        // And check no longer in map.
        foundImsi = ueIdentityTracker.FindIMSIFromTMSI(tmsi, imsi);
        CPPUNIT_ASSERT_MESSAGE("Checking didn't find IMSI from TMSI", foundImsi == false);
        foundImsi = ueIdentityTracker.FindIMSIFromPTMSI(tmsi, imsi);
        CPPUNIT_ASSERT_MESSAGE("Checking didn't find IMSI from P-TMSI", foundImsi == false);

        fflush(stdout);
    }

};

#endif
