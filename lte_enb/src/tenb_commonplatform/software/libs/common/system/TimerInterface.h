///////////////////////////////////////////////////////////////////////////////
//
// TimerInterface.h
//
// Interface to a timer module.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TimerInterface_h_
#define __TimerInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <3waytypes.h>
#include <system/UpTime.h>

namespace threeway
{


///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class Timer;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

// Create a TimerHandle type in case we change the implementation later.
typedef u32 TimerHandle;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// Zero is reserved for unallocated timers.
static const TimerHandle NULL_TIMER = 0;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Clients of the timer engine implement this interface so they can be informed
 * when their timer(s) expire.
 */
class TimerNotifyInterface
{
public:
    virtual void NotifyTimerExpiry(TimerHandle expiredTimer) = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~TimerNotifyInterface () {}
};

/**
 * Any timer engine must conform to this interface.
 */
class TimerEngineInterface
{
public:
    typedef enum
    {
        TIMER_START_NOW,    // Start a newly created timer now?
        TIMER_WAIT          // Or wait for an explicit StartTimer() call.
    } TimerStart;

    typedef enum
    {
        TIMER_SINGLE_SHOT,  // Single shot timers are deleted on expiry.
        TIMER_SINGLE_SHOT_WITHOUT_DELETE,  // These timers will not be deleted on expiry, the user *must* delete
                                           // them explicitly.  This mode allows you to create a timer and
                                           // then start/stop it at will.
        TIMER_REPEAT        // Whereas repeat timers are not: they stay in the map.
    } TimerMode;

    typedef enum
    {
        TIMER_UNALIGNED,
        TIMER_WALL_CLOCK_ALIGNED
    } TimerAlignment;

    /**
     * Create a new timer.
     *
     * \timerName               String for trace purposes.
     * \timeroutPeriodMs        Timeout period in milliseconds.
     * \timerNotifyInterface    Timeout callback.
     * \startNow                Start the timer immediately or at a later call to StartTimer()?
     * \timerMode               Single shot, with/without delete or repeating?
     */
    virtual TimerHandle CreateTimer(const std::string& timerName,
                                    u32 timeoutPeriodMs,
                                    TimerNotifyInterface& timerNotifyInterface,
                                    TimerStart startNow = TIMER_START_NOW,
                                    TimerMode timerMode = TIMER_SINGLE_SHOT,
                                    bool traceTimerEvents = true) = 0;

    /**
     * Create a new "wall clock" (time-of-day based) timer.
     * This will align the requested timeout to wall-clock such that at
     * some future timer expiry (assuming timer is repetitive) the timer
     * will expiry at midnight.
     *
     * E.g. if the time is 13:42, and a one hour timeout is requested, the timer will
     * first expire in 18 minutes at 14:00.  If a 5 minute timer is requested, the first
     * expiry will be at 13:45.
     *
     * NOTE: If time-of-day changes, the next timeout will not be modified so will not be
     * wall clock aligned.  If the timer is repeating then subsequent timeouts _will_ be
     * aligned as the timeout period is recalculated each time.
     *
     * NOTE: It is highly likely that you'll want the timeout period to be such that timeouts
     * can be aligned to midnight.  I.e. MINUTES_IN_DAY / timeoutPeriodMinutes is an integer.
     *
     * \timerName               String for trace purposes.
     * \timeroutPeriodMinutes   Timeout period in minutes.
     * \timerNotifyInterface    Timeout callback.
     * \startNow                Start the timer immediately or at a later call to StartTimer()?
     * \timerMode               Single shot, with/without delete or repeating?
     */
    virtual TimerHandle CreateWallClockTimer(const std::string& timerName,
                                             u32 timeoutPeriodMinutes,
                                             TimerNotifyInterface& timerNotifyInterface,
                                             TimerStart startNow = TIMER_START_NOW,
                                             TimerMode timerMode = TIMER_REPEAT,
                                             bool traceTimerEvents = true) = 0;

    /**
     * Modify the timeout period for a timer.
     * Only takes effect at the next StartTimer() call.
     */
    virtual void ModifyTimer(TimerHandle timerHandle, u32 timeoutPeriodMs) = 0;

    /**
     * Start a timer: if it is already running, it will be stopped and restarted.
     */
    virtual void StartTimer(TimerHandle timerHandle) = 0;

    /**
     * Stop a currently running timer.  It can be restarted with a call to StartTimer.
     */
    virtual void StopTimer(TimerHandle timerHandle) = 0;

    /**
     * Delete an existing timer from the system: if it is running, it will be stopped first.
     */
    virtual void DeleteTimer(TimerHandle timerHandle) = 0;

    /**
     * Query the current status of a registered timer.
     */
    virtual bool IsTimerRunning(TimerHandle timerHandle) const = 0;

    /**
     * Get current tick count in millisecs.
     */
    virtual uptime_t GetTickCountMs() const = 0;

    /**
     * A snapshot of the state of timers for trace/cli purposes
     */
    virtual std::string ToString() const = 0;
    
    virtual Timer* FindTimer (TimerHandle timerHandle) const = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~TimerEngineInterface () {}

    inline static u32 MillisecondsToTicks( u32 milliseconds ) { return milliseconds; };
    static u32 SecondsToTicks( u32 seconds ) ;
    static u32 MinutesToTicks( u32 minutes ) ;
    static u32 HoursToTicks( u32 hours ) ;
    static u32 DaysToTicks( u32 days ) ;
};

}

#endif
