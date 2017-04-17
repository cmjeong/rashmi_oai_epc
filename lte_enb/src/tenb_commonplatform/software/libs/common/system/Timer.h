///////////////////////////////////////////////////////////////////////////////
//
// Timer.h
//
// Represents a particular timer.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __threeway_Timer_h_
#define __threeway_Timer_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/TimerInterface.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class Timer
{
public:
    /**
     * Construction / destruction
     */
    Timer(u32 timeoutPeriodMs, TimerEngineInterface::TimerMode timerMode, const std::string& timerName,
          TimerNotifyInterface& timerNotifyInterface, TimerEngineInterface::TimerAlignment timerAlignment,
          bool traceTimerEvents = true);
    virtual ~Timer();

    /**
     * Accessors.
     */
    TimerHandle             GetHandle() const;
    u32                     GetTimerPeriodMs() const;
    bool                    IsDeleteOnExpiry() const;
    const char *            GetTimerName() const;
    TimerEngineInterface::TimerMode GetTimerMode() const;
    TimerNotifyInterface&   GetTimerNotifyInterface() const;
    TimerEngineInterface::TimerAlignment GetTimerAlignment() const;
    bool                    GetTraceTimerEvents() const;

    /**
     * Allows modification of timer period without delete + recreate.
     */
    void                    SetTimerPeriodMs(u32 timerPeriodMs);

    virtual std::string ToString() const;

private:

    // Unique handle identifying this timer.
    TimerHandle    m_timerHandle;

    // Duration (in milliseconds) of this timer.
    u32            m_timerPeriodMs;

    // When this timer expires should it be deleted, kept or restarted?
    TimerEngineInterface::TimerMode      m_timerMode;

    // Name for debug.
    std::string    m_timerName;

    // Expiry callback.
    TimerNotifyInterface& m_timerNotifyInterface;

    // Timer alignment
    TimerEngineInterface::TimerAlignment m_timerAlignment;

    // Trace this timer?
    bool m_traceTimerEvents;

    // Seeding used when creating new timers.
    static TimerHandle s_nextTimerHandle;
};



}

#endif

