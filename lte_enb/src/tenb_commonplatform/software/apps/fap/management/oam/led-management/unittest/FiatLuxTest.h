///////////////////////////////////////////////////////////////////////////////
//
// FiatLuxTest.h
//
// This unit test performs some test of FiatLux by giving it a pattern and
// keeping a counter of LEDs that are supposed to change.
// Performs tests for 3.5 and 4.0 HW
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FiatLuxTest_h_
#define __FiatLuxTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

#include <system/TimerEngine.h>
#include <messaging/messages/oam/LedInfo.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SetLedInterface.h"
#include "FiatLux.h"
#include "LedBehaviour_v3_5.h"
#include "LedBehaviour_v4.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class SetLed_unitTest : public SetLedInterface
{
public:
    SetLed_unitTest():
        m_ledMap()
    {};

    ~SetLed_unitTest() {};

    void SetLed(u32 id, LedColour c, LedPattern p)
    {
        TRACE_PRINTF("SetLed unitest: led id %" PRIu32 ", led colour %s, led pattern %s", id, ledColourToString(c), ledPatternToString(p) );
        m_ledMap[id].colour = c;
        m_ledMap[id].pattern = p;
    };

    LedMapEntry GetLedState(u32 ledId) { return m_ledMap[ledId]; }

    void ResetMap()
    {
        for (int i=0; i<4; ++i)
        {
            m_ledMap[i].colour = LED_NONE;
            m_ledMap[i].pattern = LED_SET_OFF;
        }
        TRACE_PRINTF("Local Map reset");
    }

private:
   /* Keep current state of LEDs */
   LedMapEntry    m_ledMap[4];
};


class TestTimerEngine : public TimerEngineInterface
{
public:
    TestTimerEngine() {}

    virtual TimerHandle CreateTimer(const std::string& timerName,
                                    u32 timeoutPeriodMs,
                                    TimerNotifyInterface& timerNotifyInterface,
                                    TimerStart startNow = TIMER_START_NOW,
                                    TimerMode timerMode = TIMER_SINGLE_SHOT,
                                    bool traceTimerEvents = true) { return 1; }

    virtual TimerHandle CreateWallClockTimer(const std::string& timerName,
                                             u32 timeoutPeriodMinutes,
                                             TimerNotifyInterface& timerNotifyInterface,
                                             TimerStart startNow = TIMER_START_NOW,
                                             TimerMode timerMode = TIMER_REPEAT,
                                             bool traceTimerEvents = true) { return NULL_TIMER; };

    virtual void ModifyTimer(TimerHandle timerHandle, u32 timeoutPeriodMs) { TRACE_MSG("ModifyTimer\n"); }
    virtual void StartTimer(TimerHandle timerHandle) { TRACE_MSG("StartTimer\n"); }
    virtual void StopTimer(TimerHandle timerHandle) { TRACE_MSG("StopTimer\n"); }
    virtual void DeleteTimer(TimerHandle timerHandle) { TRACE_MSG("DeleteTimer\n"); }
    virtual bool IsTimerRunning(TimerHandle timerHandle) const { TRACE_MSG("IsTimerRunning\n"); return true; }
    virtual uptime_t GetTickCountMs() const { TRACE_MSG("GetTicksCount\n"); return 0; };
    virtual std::string ToString() const { TRACE_MSG("ToString\n");; return ""; };

};


class TimerNotifier : public TimerNotifyInterface
{
public:

    void NotifyTimerExpiry(TimerHandle expiredTimer)
    {
        TRACE_PRINTF("Notification of Timer Expiry (timer %"PRId16")", expiredTimer );
    }
};


class FiatLuxTest : public CppUnit::TestCase
{
    void runTest()
    {
        cout << endl << endl
             << "***********" << endl
             << "FiatLux tests" << endl
             << "***********" << endl << endl;

        TRACE_MSG("Constructing objects...");

        SetLed_unitTest     setLed;
        LedBehaviour_v3_5   ledBehaviour_3_5;
        LedBehaviour_v4     ledBehaviour_4;
        TestTimerEngine     testTimerEngine;
        TimerNotifier       testTimerNotifier;


        TRACE_PRINTF("Creating FiatLux instance with HW 3.5 behaviour");

        FiatLux  fiatLux(setLed,
                         ledBehaviour_3_5,
                         testTimerEngine, //TimerEngine::GetInstance(),
                         testTimerNotifier, // TimerNotifyInterface
                         60000,        // 1 minute for No Connection TimeOut
                         30000 );   // 30 s for Not Operational TimeOut

        TRACE_PRINTF("Testing POWER ON pattern for HW 3.5");
        LedEvent ev = POWER_ON;
        fiatLux.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("POWER ON status",
                (setLed.GetLedState(LED_ALARM).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_ACCESS).pattern == LED_SET_OFF) );

        TRACE_PRINTF("Testing CONNECT TO SERVER pattern for HW 3.5");
        ev = CONNECT_TO_SERVER;
        fiatLux.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("CONNECT TO SERVER status",
                (setLed.GetLedState(LED_ALARM).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_ACCESS).pattern == LED_SET_OFF) );

        TRACE_PRINTF("Testing OPERATIONAL pattern for HW 3.5");
        ev = OPERATIONAL;
        fiatLux.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("OPERATIONAL status",
                (setLed.GetLedState(LED_ALARM).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_ACCESS).pattern == LED_SET_ON) );

        TRACE_PRINTF("Testing NOT OPERATIONAL pattern for HW 3.5");
        ev = NOT_OPERATIONAL;
        fiatLux.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("NOT OPERATIONAL status",
                (setLed.GetLedState(LED_ALARM).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_ACCESS).pattern == LED_SET_FLASHING) );

        TRACE_PRINTF("Testing TEMPERATURE OUT OF RANGE pattern for HW 3.5");
        ev = TEMPERATURE_OUT_OF_RANGE;
        fiatLux.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("TEMPERATURE OUT OF RANGE status",
                (setLed.GetLedState(LED_ALARM).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_ACCESS).pattern == LED_SET_OFF) );

        TRACE_PRINTF("Testing FAP ERROR pattern for HW 3.5");
        ev = FAP_ERROR;
        fiatLux.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("FAP ERROR status",
                (setLed.GetLedState(LED_ALARM).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_ACCESS).pattern == LED_SET_OFF) );

        // Test 4.0 HW
        setLed.ResetMap();
        TRACE_PRINTF("Creating FiatLux instance with HW 4.0 behaviour");

        FiatLux  fiatLux4(setLed,
                         ledBehaviour_4,
                         testTimerEngine, //TimerEngine::GetInstance(),
                         testTimerNotifier, // TimerNotifyInterface
                         60000,        // 1 minute for No Connection TimeOut
                         30000 );   // 30 s for Not Operational TimeOut

        TRACE_PRINTF("Testing POWER ON pattern for HW 4.0");
        ev = POWER_ON;
        fiatLux4.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("POWER ON status",
                (setLed.GetLedState(LED_POWER).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_POWER).colour == LED_YELLOW
                 && setLed.GetLedState(LED_INTERNET).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_INTERNET).colour == LED_NONE
                 && setLed.GetLedState(LED_LOCATION).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_LOCATION).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).pattern == LED_SET_OFF) );

        TRACE_PRINTF("Testing CONNECT TO SERVER pattern for HW 4.0");
        ev = CONNECT_TO_SERVER;
        fiatLux4.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("CONNECT TO SERVER status",
                (setLed.GetLedState(LED_POWER).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_POWER).colour == LED_GREEN
                 && setLed.GetLedState(LED_INTERNET).pattern == LED_SET_FLASHING
                 && setLed.GetLedState(LED_INTERNET).colour == LED_GREEN
                 && setLed.GetLedState(LED_LOCATION).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_LOCATION).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).pattern == LED_SET_OFF) );

        TRACE_PRINTF("Testing OPERATIONAL pattern for HW 4.0");
        ev = OPERATIONAL;
        fiatLux4.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("OPERATIONAL status",
                (setLed.GetLedState(LED_POWER).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_POWER).colour == LED_GREEN
                 && setLed.GetLedState(LED_INTERNET).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_INTERNET).colour == LED_GREEN
                 && setLed.GetLedState(LED_LOCATION).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_LOCATION).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).colour == LED_GREEN
                 && setLed.GetLedState(LED_SERVICE).pattern == LED_SET_ON) );

        TRACE_PRINTF("Testing NOT OPERATIONAL pattern for HW 4.0");
        ev = NOT_OPERATIONAL;
        fiatLux4.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("NOT OPERATIONAL status",
                (setLed.GetLedState(LED_POWER).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_POWER).colour == LED_GREEN
                 && setLed.GetLedState(LED_INTERNET).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_INTERNET).colour == LED_GREEN
                 && setLed.GetLedState(LED_LOCATION).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_LOCATION).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).colour == LED_GREEN
                 && setLed.GetLedState(LED_SERVICE).pattern == LED_SET_FLASHING) );


        TRACE_PRINTF("Testing TEMPERATURE OUT OF RANGE pattern for HW 4.0");
        ev = TEMPERATURE_OUT_OF_RANGE;
        fiatLux4.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("TEMPERATURE OUT OF RANGE status",
                (setLed.GetLedState(LED_POWER).pattern == LED_SET_FLASHING
                 && setLed.GetLedState(LED_POWER).colour == LED_RED
                 && setLed.GetLedState(LED_INTERNET).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_INTERNET).colour == LED_NONE
                 && setLed.GetLedState(LED_LOCATION).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_LOCATION).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).pattern == LED_SET_OFF) );

        TRACE_PRINTF("Testing FAP ERROR pattern for HW 4.0");
        ev = FAP_ERROR;
        fiatLux4.TriggerLedBehaviour( ev );
        CPPUNIT_ASSERT_MESSAGE("FAP ERROR status",
                (setLed.GetLedState(LED_POWER).pattern == LED_SET_ON
                 && setLed.GetLedState(LED_POWER).colour == LED_RED
                 && setLed.GetLedState(LED_INTERNET).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_INTERNET).colour == LED_NONE
                 && setLed.GetLedState(LED_LOCATION).pattern == LED_SET_OFF
                 && setLed.GetLedState(LED_LOCATION).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).colour == LED_NONE
                 && setLed.GetLedState(LED_SERVICE).pattern == LED_SET_OFF) );

        fflush(stdout);
    }

protected:

private:

};

#endif
