///////////////////////////////////////////////////////////////////////////////
//
// TimerEngine.h
//
// Timer engine for managing timers and informing clients of their expiry.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __threeway_TimerEngine_h_
#define __threeway_TimerEngine_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <list>
#include <stdio.h>

#include <boost/shared_ptr.hpp>
#include <system/Thread.h>
#include <system/TimerInterface.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class Timer;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
typedef std::map <TimerHandle, Timer *> TimerMap;
typedef std::multimap <uptime_t, TimerHandle> TimerExpiryMap;
typedef std::list <TimerHandle> TimerList;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Timer engine without a thread.  Client is responsible for providing the
 * timeout required.
 */
class TimerEngine : public TimerEngineInterface
{
protected:
    // Is singleton so protected constructor.
    TimerEngine(Mutex& timersMutex, Condition& timersCondition);

public:
    virtual ~TimerEngine();
    // Must call this one first to construct singleton.
    static TimerEngine& GetInstance(Mutex& timersMutex, Condition& timersCondition);
    static TimerEngine& GetInstance();
    // Bit weird this... it's to support unittests so we can ensure each test
    // creates its own timer engine instance.
    static void Destroy();

    /**
     * Get timer engine interface.
     */
    TimerEngineInterface& GetTimerEngineInterface() const;

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
     * Get current tick count in millisecs.
     */
    virtual inline uptime_t GetTickCountMs() const;

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

    // Singleton instance.
    static TimerEngine* s_instance;

    static const u32 MAX_TIMERS = 0xffff; // Lots of timers :-)

    // Map holding all of the registered (although possibly not running) timers.
    TimerMap       m_theTimers;

    // This map is ordered using the timer expiry time: the first item
    // is the next timer to expire.
    TimerExpiryMap m_runningTimers;

    // Mutex to protect access to timers.
    Mutex&         m_timersMutex;
    Condition&     m_timersCondition;

    // To determine uptime.
    UpTime         m_uptime;

    // Very simple Stl container holding the handles of expired timers along
    // with their notify function. We cache this to avoid needing to use FindTimer
    // after expiry, which avoids a race.
    std::list < CachedTimerInfo > m_expiredTimers;

};

/**
 * Timer engine with own thread to keep it simple for clients.
 */
class TimerEngineThread : public Thread
{
protected:
    // Is singleton so protected constructor.
    TimerEngineThread();

public:
    virtual ~TimerEngineThread();
    static TimerEngineThread& GetInstance();

    // Initialisation + termination are separate as we want to hold off creating
    // threads at program startup.
    void StartTimerEngine ();
    void StopTimerEngine ();

protected:
    // Actual thread implementation.
    virtual u32 ThreadProcedure ();

private:
    // Singleton instance.
    static TimerEngineThread* s_instance;

    // Mutex to protect access to timers.
    mutable Mutex  m_timersMutex;
    Condition      m_timersCondition;
};

}

#endif

