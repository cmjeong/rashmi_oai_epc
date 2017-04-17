///////////////////////////////////////////////////////////////////////////////
//
// ThreadlessTimerEngine.h
//
// Timer engine without a thread for managing timers and informing clients
// of their expiry.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __threeway_ThreadlessTimerEngine_h_
#define __threeway_ThreadlessTimerEngine_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <list>
#include <stdio.h>

#include <boost/shared_ptr.hpp>
#include <system/Thread.h>
#include <system/TimerInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SelectorInterfaces.h"
#include "TimerEngine.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class ThreadlessTimerEngine : public TimerEngineInterface, SelectorCallBackInterface
{
public:
    ThreadlessTimerEngine(SelectorRegisterInterface&);
    virtual ~ThreadlessTimerEngine();

    /**
     * TimerEngineInterface implementation.
     */
    virtual TimerHandle CreateTimer(const std::string& timerName,
                                    u32 timeoutPeriodMs,
                                    TimerNotifyInterface& timerNotifyInterface,
                                    TimerStart startNow = TIMER_START_NOW,
                                    TimerMode timerMode = TIMER_SINGLE_SHOT,
                                    bool traceTimerEvents = true);
    virtual TimerHandle CreateWallClockTimer(const std::string& timerName,
                                             u32 timeoutPeriodMinutes,
                                             TimerNotifyInterface& timerNotifyInterface,
                                             TimerStart startNow = TIMER_START_NOW,
                                             TimerMode timerMode = TIMER_REPEAT,
                                             bool traceTimerEvents = true);
    virtual void ModifyTimer(TimerHandle timerHandle, u32 timeoutPeriodMs);
    virtual void StartTimer(TimerHandle timerHandle);
    virtual void StopTimer(TimerHandle timerHandle);
    virtual void DeleteTimer(TimerHandle timerHandle);
    virtual bool IsTimerRunning(TimerHandle timerHandle) const;
    virtual inline uptime_t GetTickCountMs() const ;

    /**
     * Request time to next timeout.
     */
    u32 GetMillisecsToNextTimerExpiry() const;

    /**
     * Check all timers and notify clients if necessary.
     */
    void CheckTimers();

    /**
     */
    void DeleteOrRestartExpiredTimers();

    /**
     * A snapshot of the state of timers for trace/cli purposes
     */
    virtual std::string ToString() const;

protected:
    /**
     * Internal function for creating aligned or unaligned timers.
     * The client API is cleaner, making it explicit when a wall clock timer is requested.
     */
    TimerHandle CreateAnyTimer(const std::string& timerName,
                               u32 timeoutPeriodMs,
                               TimerNotifyInterface& timerNotifyInterface,
                               TimerStart startNow,
                               TimerMode timerMode,
                               TimerAlignment timerAlignment,
                               bool traceTimerEvents);

    /**
     * Find a timer by timer handle.
     *
     * \return  Timer or NULL if not found.
     */
    Timer* FindTimer (TimerHandle timerHandle) const;

    /**
     * Calculate timeout period for a wall clock aligned timer.
     *
     * E.g. if the time is 13:42, and a one hour timeout is requested, the timer will
     * first expire in 18 minutes at 14:00.  If a 5 minute timer is requested, the first
     * expiry will be at 13:45.
     *
     * \param timerPeriodMillisecs  Nominal timer period, 0->24hrs
     * \return                      Millisecs to next timer expiry.
     */
    u32 CalculateWallClockExpiryTime(u32 timerPeriodMillisecs);

private:
    class CachedTimerInfo
    {
    public:
        TimerHandle m_handle;
        TimerNotifyInterface& m_notifyInterface;
        TimerEngineInterface::TimerMode m_mode;
        bool m_traceTimerEvents;

        CachedTimerInfo(TimerHandle h, TimerNotifyInterface& i, TimerEngineInterface::TimerMode m, bool traceTimerEvents) :
            m_handle(h), m_notifyInterface(i), m_mode(m), m_traceTimerEvents(traceTimerEvents) { }
        CachedTimerInfo(const CachedTimerInfo& cachedRef) :
            m_handle(cachedRef.m_handle), m_notifyInterface(cachedRef.m_notifyInterface), m_mode(cachedRef.m_mode), m_traceTimerEvents(cachedRef.m_traceTimerEvents) { }
    };

    SelectorRegisterInterface&  m_SelectorRegisterInterface;

    static const u32 MAX_TIMERS = 0xffff; // Lots of timers :-)

    // Map holding all of the registered (although possibly not running) timers.
    TimerMap       m_theTimers;

    // To determine uptime.
    UpTime         m_uptime;

    // This map is ordered using the timer expiry time: the first item
    // is the next timer to expire.
    TimerExpiryMap m_runningTimers;

    // Next timer to expire
    TimerHandle m_headTimer;

    void CheckHeadTimer();

    void SelectCallBack();

    // Very simple Stl container holding the handles of expired timers along
    // with their notify function. We cache this to avoid needing to use FindTimer
    // after expiry, which avoids a race.
    std::list < CachedTimerInfo > m_expiredTimers;

};


}

#endif

