///////////////////////////////////////////////////////////////////////////////
//
// TimerEngineTest.h
//
// Unit tests for TimerEngine class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TimerEngineTest_h_
#define __TimerEngineTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <unistd.h>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/TimerEngine.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TestTimerEngine : public TimerEngine
{
    TestTimerEngine(Mutex& timersMutex, Condition& timersCondition) :
        TimerEngine(timersMutex, timersCondition),
        m_currentTickCountMs(0)
    {
    }

    virtual uint64_t GetTickCountMs() const
    {
        return m_currentTickCountMs;
    }

    void IncTickCountByMs(u32 incMs)
    {
        m_currentTickCountMs += incMs;
    }

    uint64_t m_currentTickCountMs;
};


class TimerEngineTest : public CppUnit::TestCase, public TimerNotifyInterface
{
public:
    void NotifyTimerExpiry(TimerHandle expiredTimer)
    {
        m_expiredTimer = expiredTimer;
        TRACE("Expired timer", (u32)expiredTimer);
    }

    void runTest()
    {
        cout << endl << endl
             << "*****************" << endl
             << "TimerEngine tests" << endl
             << "*****************" << endl << endl;

        //
        // Normal cases.
        //
        TimerEngineThread& timerEngineThread = TimerEngineThread::GetInstance();
        timerEngineThread.StartTimerEngine();

        TimerEngine& timerEngine = TimerEngine::GetInstance();
        //TestTimerEngine timerEngine();

        m_expiredTimer = NULL_TIMER;
        TimerHandle timerHandle = timerEngine.CreateTimer("Jon's Funky Timer", 1000, *this);
        TRACE("Timer started", (u32)timerHandle);

        sleep(2);

        CPPUNIT_ASSERT_MESSAGE("Check expired timer handle", m_expiredTimer == timerHandle);

        //
        // Wall Clock Timer
        //
        //timerEngine.CalculateWallClockExpiryTime(3600 * 1000);

        //
        // Error cases.
        //

        timerEngineThread.StopTimerEngine();

        fflush(stdout);
    }

private:
    TimerHandle m_expiredTimer;
};

#endif
