///////////////////////////////////////////////////////////////////////////////
//
// ThreadlessTimerEngine.cpp
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
#include <time.h>
#include <sys/time.h>

#include <sstream>
#include <iomanip>

#include <system/Trace.h>
#include <system/Exception.h>
#include <system/Timer.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ThreadlessTimerEngine.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ThreadlessTimerEngine::ThreadlessTimerEngine(SelectorRegisterInterface& sri):
    m_headTimer(NULL_TIMER),
    m_SelectorRegisterInterface(sri),
    m_uptime(true)
{
}

ThreadlessTimerEngine::~ThreadlessTimerEngine ()
{
    // Safe to manipulate (i.e. empty) all of the maps.
    TimerMap::iterator timerIter = m_theTimers.begin ();
    while(timerIter != m_theTimers.end ())
    {
        delete timerIter->second;
        ++timerIter;
    } //end while

    m_theTimers.clear ();
    m_runningTimers.clear ();
}

TimerHandle ThreadlessTimerEngine::CreateTimer(const std::string& timerName, u32 timeoutPeriod,
                                               TimerNotifyInterface& timerNotifyInterface,
                                               TimerStart startNow,
                                               TimerMode timerMode,
                                               bool traceTimerEvents)
{
    ENTER();

    TimerHandle timerHandle = CreateAnyTimer(timerName,
                                             timeoutPeriod,
                                             timerNotifyInterface,
                                             startNow,
                                             timerMode,
                                             TIMER_UNALIGNED,
                                             traceTimerEvents);

    RETURN(timerHandle);
}

TimerHandle ThreadlessTimerEngine::CreateWallClockTimer(const std::string& timerName,
                                                        u32 timeoutPeriodMinutes,
                                                        TimerNotifyInterface& timerNotifyInterface,
                                                        TimerStart startNow,
                                                        TimerMode timerMode,
                                                        bool traceTimerEvents)
{
    ENTER();

    RSYS_ASSERT(timeoutPeriodMinutes > 0);
    RSYS_ASSERT(timeoutPeriodMinutes <= (24 * 60));

    if( ((24 * 60) % timeoutPeriodMinutes) != 0 )
    {
        TRACE_PRINTF_LEV(TRACE_WARNING,
                         "Creating wall clock timer (%s, %"PRIu32" minutes) that will not always be aligned to midnight",
                         timerName.c_str(), timeoutPeriodMinutes);
    }

    TimerHandle timerHandle = CreateAnyTimer(timerName,
                                             timeoutPeriodMinutes * 60 * 1000 /* ms */,
                                             timerNotifyInterface,
                                             startNow,
                                             timerMode,
                                             TIMER_WALL_CLOCK_ALIGNED,
                                             traceTimerEvents);

    RETURN(timerHandle);
}

void ThreadlessTimerEngine::ModifyTimer(TimerHandle timerHandle, u32 timeoutPeriodMs)
{
    ENTER();

    Timer* foundTimer = NULL;
    // Scope for Guard
    {
        foundTimer = FindTimer(timerHandle);

        if(foundTimer)
        {
            foundTimer->SetTimerPeriodMs(timeoutPeriodMs);
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_WARNING, "ModifyTimer: Handle not found: timerHandle=%" PRIu32 ", timeoutPeriodMs=%" PRIu32, timerHandle, timeoutPeriodMs);
        }
    }

    EXIT();
}

void ThreadlessTimerEngine::StartTimer (TimerHandle timerHandle)
{
    ENTER ();

    // If the timer is currently running, we stop it.  In effect, producing
    // the Re-Start logic.
    StopTimer (timerHandle);

    Timer* foundTimer = NULL;
    // Scope for Guard
    {
        // We're going to iterate the timers so let's protect ourselves.
        foundTimer = FindTimer(timerHandle);
    }

    if (foundTimer)
    {
        // Now register the timer in the running timers map, using
        // its expiry time as the primary index.
        u32 expiryDelta = 0;
        switch(foundTimer->GetTimerAlignment())
        {
        case TimerEngineInterface::TIMER_UNALIGNED:
            expiryDelta = foundTimer->GetTimerPeriodMs();
            break;
        case TimerEngineInterface::TIMER_WALL_CLOCK_ALIGNED:
            // Recalculate wall clock timers each time so we don't drift.
            expiryDelta = CalculateWallClockExpiryTime(foundTimer->GetTimerPeriodMs());
            break;
        // No default, let compile tell us about missing enum elements.
        }

        uptime_t expiryTime = GetTickCountMs() + expiryDelta;

        TRACE_PRINTF_LEV(foundTimer->GetTraceTimerEvents() ? TRACE_INFO : TRACE_VERBOSE,
                         "Starting Timer %" PRIu32 " (%s) expires in %" PRIu32 " ms",
                         (u32)foundTimer->GetHandle(),
                         foundTimer->GetTimerName(),
                         expiryDelta);

        // We're going to modify the timers so let's protect ourselves.
        m_runningTimers.insert (std::make_pair (expiryTime, timerHandle));
        // Signal to timer thread that the list of timers has changed
        CheckHeadTimer();
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "Starting Timer %" PRIu32 " failed - Timer does not exist!",(u32)timerHandle);
    }

    EXIT ();
}

void ThreadlessTimerEngine::StopTimer (TimerHandle timerHandle)
{
    ENTER();

    TimerExpiryMap::iterator timerIter = m_runningTimers.begin ();
    while (timerIter != m_runningTimers.end ())
    {
        if (timerIter->second == timerHandle)
        {
            // Found it: simply remove from the map and it is no
            // longer running.
            Timer* foundTimer = FindTimer(timerHandle);
            if(foundTimer)
            {
                TRACE_PRINTF_LEV(foundTimer->GetTraceTimerEvents() ? TRACE_INFO : TRACE_VERBOSE,
                                 "Stopping Timer %" PRIu32 " (%s)",
                                 (u32)timerHandle, foundTimer->GetTimerName());
            }

            m_runningTimers.erase (timerIter);
            // Signal to timer thread that the list of timers has changed
            CheckHeadTimer();
            break;
        }

        timerIter++;
    }

    EXIT();
}

void ThreadlessTimerEngine::DeleteTimer (TimerHandle timerHandle)
{
    ENTER ();

    // Make sure it's a valid timer handle before we proceed.
    if (timerHandle != NULL_TIMER)
    {
        // It might be running, so stop it first.
        StopTimer (timerHandle);

        Timer* foundTimer = FindTimer (timerHandle);

        // Sanity check the result.
        if (foundTimer)
        {
            TRACE_PRINTF_LEV(TRACE_VERBOSE, "Deleting Timer %" PRIu32 " (%s)",
                             (u32)timerHandle, foundTimer->GetTimerName());

            if(timerHandle == foundTimer->GetHandle())
            {
                // Knock out of the map...
                m_theTimers.erase (timerHandle);

                // And free the allocated memory: we are done.
                delete foundTimer;
            }
            else
            {
                // Bad code alert!  some error logging mechanism here.
                TRACE_MSG_LEV(TRACE_WARNING, "TimerHandle returned doesn't match search handle!");
            }
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_VERBOSE, "Deleting Timer %" PRIu32 " failed - Timer does not exist!", (u32)timerHandle);
        }
    }
    else
    {
        TRACE_MSG_LEV(TRACE_WARNING, "Deleting Timer NULL failed - No timer to delete");
    }

    EXIT();
}

bool ThreadlessTimerEngine::IsTimerRunning (TimerHandle timerHandle) const
{
    ENTER ();

    if (timerHandle != NULL_TIMER)
    {
        TimerExpiryMap::const_iterator timerIter = m_runningTimers.begin ();
        while (timerIter != m_runningTimers.end ())
        {
            if (timerIter++->second == timerHandle)
            {
                RETURN (true);
            }
        }//end while
    }//end if

    RETURN (false);
}

uptime_t ThreadlessTimerEngine::GetTickCountMs() const
{
    return m_uptime.GetMillisecs();
}

u32 ThreadlessTimerEngine::GetMillisecsToNextTimerExpiry() const
{
    ENTER();

    u32 timeoutMilliSecs = 5000;

    TimerExpiryMap::const_iterator timerIter = m_runningTimers.begin ();
    if (timerIter != m_runningTimers.end ())
    {
        // NB this is the absolute timeout in ms, so convert to relative
        uptime_t timeNow = GetTickCountMs ();

        if( timerIter->first > timeNow )
        {
            timeoutMilliSecs = timerIter->first - timeNow;
        }
        else
        {
            u32 arbitraryShortTime = 1000;

            /* Except for rare race-conditions due to kernel task switching etc, we
             * should never be within this condition.
             * The trace is there to detect coding errors.
             */
            if( (timerIter->first + arbitraryShortTime) <= timeNow)
            {
                TRACE_PRINTF("*** Stale Timer %"PRIu32" detected %"PRIu64"ms overdue.", timerIter->second, timeNow - timerIter->first );
                fprintf( stderr, "VERY-BAD!!! Stale Timer %"PRIu32" detected %"PRIu64"ms overdue.", timerIter->second, timeNow - timerIter->first );
            }

            timeoutMilliSecs = arbitraryShortTime;
        }
    }

    RETURN(timeoutMilliSecs);
}

void ThreadlessTimerEngine::CheckTimers()
{
    ENTER();

    // Clear out any previously expired timers
    m_expiredTimers.clear();

    // Record immediately the current system time, then check the
    // running timers map to see of any have expired.
    uptime_t timeNow = GetTickCountMs ();

    TimerExpiryMap::iterator timerIter = m_runningTimers.begin ();
    while (timerIter != m_runningTimers.end())
    {
        if (timeNow >= timerIter->first)
        {
            // This one has gone off: notify the owner.

            // Hold off the notification until we are out of this loop.  If
            // the result of the notify starts or stops a timer it will effect
            // the containers of timers
            Timer* expiredTimer = FindTimer(timerIter->second);

            // Above should always find a timer.
            RSYS_ASSERT(expiredTimer != NULL);

            m_expiredTimers.push_back(CachedTimerInfo(timerIter->second,
                                                      expiredTimer->GetTimerNotifyInterface(),
                                                      expiredTimer->GetTimerMode(),
                                                      expiredTimer->GetTraceTimerEvents()));
                                                      
            TRACE_PRINTF_LEV(expiredTimer->GetTraceTimerEvents() ? TRACE_INFO : TRACE_VERBOSE,
                             "Timer %" PRIu32 " Expired! (%s)",
                             (u32)expiredTimer->GetHandle(),expiredTimer->GetTimerName());
        }
        else
        {
            // We can safely short circuit out here: we order the map
            // using expire-time, so all subsequent timers will implicitly
            // expire later than this one.  So if it's not due, none of them
            // will be.
            // The expire-time is a 64bit type, in milliseconds, giving us
            // more than 136 years of up-time before wrapping!
            break;
        }//end if

        timerIter++;
    }//end while

    EXIT();
}

void ThreadlessTimerEngine::DeleteOrRestartExpiredTimers()
{
    std::list < CachedTimerInfo >::iterator expiredTimerIter;

    // Safely out of the iteration of running timer container,
    // now we can delete the expired timer or restart it...
    for (expiredTimerIter = m_expiredTimers.begin(); expiredTimerIter != m_expiredTimers.end(); expiredTimerIter++)
    {
        if (expiredTimerIter->m_mode == TimerEngineInterface::TIMER_SINGLE_SHOT)
        {
            DeleteTimer(expiredTimerIter->m_handle);
        }
        else if (expiredTimerIter->m_mode == TimerEngineInterface::TIMER_REPEAT)
        {
            TRACE_PRINTF_LEV(TRACE_VERBOSE, "Restarting Timer %" PRIu32, expiredTimerIter->m_handle);
            StartTimer(expiredTimerIter->m_handle);
        }
        else
        {
            StopTimer(expiredTimerIter->m_handle);
        }
    }

    // Notify the clients once all the expired timers have been noted.
    for (expiredTimerIter = m_expiredTimers.begin(); expiredTimerIter != m_expiredTimers.end(); expiredTimerIter++)
    {
        expiredTimerIter->m_notifyInterface.NotifyTimerExpiry(expiredTimerIter->m_handle);
    }
}

std::string ThreadlessTimerEngine::ToString() const
{
    std::ostringstream stream;


    uptime_t nowMs = GetTickCountMs();
    time_t now = (nowMs / 1000);
    struct tm* atTime = gmtime(&now);

    stream << "At: " << std::setfill('0') << std::setw(2) << atTime->tm_hour << ":" << std::setw(2)
        << atTime->tm_min << ":" << std::setw(2) << atTime->tm_sec << ".";
    stream << std::setw(3) << (nowMs%1000) << std::endl;

    stream << "Registered timers:" << std::endl;

    TimerMap::const_iterator timerIter;
    for (timerIter = m_theTimers.begin(); timerIter != m_theTimers.end(); timerIter++)
    {
        if (timerIter->second != NULL)
        {
            Timer* timer = timerIter->second;
            stream << timer->ToString() << std::endl;
        }
    }
    stream << "Total Registered timers: " << m_theTimers.size() << std::endl;

    stream << std::endl << "Running timers:" << std::endl;
    TimerExpiryMap::const_iterator timerExpIter;
    for (timerExpIter = m_runningTimers.begin(); timerExpIter != m_runningTimers.end(); timerExpIter++)
    {
        time_t when = timerExpIter->first/1000;
        atTime = gmtime(&when);

        stream << "At: " << std::setfill('0') << std::setw(2) << atTime->tm_hour << ":" << std::setw(2) << atTime->tm_min << ":" << std::setw(2) << atTime->tm_sec << ".";
        stream << std::setw(3) << (timerExpIter->first%1000);

        stream << " Handle: " << timerExpIter->second << " Time to run: "<< (timerExpIter->first - nowMs) << " ms" << std::endl;
    }
    stream << "Total Running timers: " << m_runningTimers.size() << std::endl;

    return stream.str();
}

TimerHandle ThreadlessTimerEngine::CreateAnyTimer(const std::string& timerName,
                                                  u32 timeoutPeriodMs,
                                                  TimerNotifyInterface& timerNotifyInterface,
                                                  TimerStart startNow,
                                                  TimerMode timerMode,
                                                  TimerAlignment timerAlignment,
                                                  bool traceTimerEvents)
{
    ENTER();

    if (m_theTimers.size() != MAX_TIMERS)
    {
        Timer *timer = NULL;

        // Scope for Guard
        {
            Timer* foundTimer = NULL;
            u32 numberOfAttempts = 0;

            /*
             * The timer handle generated by the Timer ctor, is done by an
             * ever-incrementing u32.  This will eventually wrap, so it will
             * sooner-or-later try to reuse handles.  This must be trapped
             * as the handles *must* be unique.  If the handle is not unique
             * the insert into the map will simply discard the new timer.
             */
            do
            {
                // just to make sure we don't loop forever...
                RSYS_ASSERT_PRINTF(numberOfAttempts < MAX_TIMERS,
                                   "Maximum number of active timers has been exceeded trying to create %s",
                                   timerName.c_str());
                numberOfAttempts++;

                // Instantiate new timer object...
                timer = new Timer(timeoutPeriodMs,
                                  timerMode,
                                  timerName,
                                  timerNotifyInterface,
                                  timerAlignment,
                                  traceTimerEvents);

                foundTimer = FindTimer(timer->GetHandle());

                if (foundTimer != NULL)
                {
                    delete timer;
                    timer = NULL;
                }

            } while (foundTimer != NULL);

            // Register it internally in our map of all timers...
            std::pair<TimerMap::iterator,bool> result =
                    m_theTimers.insert(std::make_pair(timer->GetHandle(), timer));

            // belt & braces, we should be guarded by the check above...
            RSYS_ASSERT_PRINTF(result.second == true, "Timer for %s (%" PRIu32 "ms) was discarded due to duplicate handle.",
                               timerName.c_str(), timeoutPeriodMs);

            TRACE_PRINTF_LEV(TRACE_VERBOSE,
                             "Creating Timer %" PRIu32 " (%s) timeout %" PRIu32 " ms",
                             (u32)timer->GetHandle(),
                             timer->GetTimerName(),
                             timer->GetTimerPeriodMs());
        }

        // Do we need to start it immediately?
        if (startNow == TIMER_START_NOW)
        {
            StartTimer(timer->GetHandle());
        }

        // and return the handle for the user to (hopefully) not lose...
        RETURN (timer->GetHandle ());
    }
    else
    {
        TRACE_MSG ("TimerEngineWithSelect is in OVERLOAD - too many registered timers");
        RETURN (NULL_TIMER);
    }//end if
}

Timer* ThreadlessTimerEngine::FindTimer (TimerHandle timerHandle) const
{
    ENTER();

    // NB this function is for "internal" use only, must not attempt to lock the
    // mutex protecting timer maps as it will be locked by the caller.

    TimerMap::const_iterator timerIter = m_theTimers.find (timerHandle);
    if (timerIter != m_theTimers.end ())
    {
        RETURN (timerIter->second);
    }

    RETURN(NULL);
}

u32 ThreadlessTimerEngine::CalculateWallClockExpiryTime(u32 timerPeriodMillisecs)
{
    ENTER();

    RSYS_ASSERT(timerPeriodMillisecs <= (24 * 60 * 60 * 1000));

    struct timeval timeVal;
    struct timezone timeZone;

    gettimeofday (&timeVal, &timeZone);
    struct tm *tmVal = gmtime (&(timeVal.tv_sec));  // gmtime works in UTC.

    TRACE_PRINTF_LEV(TRACE_VERBOSE,
                     "CalculateWallClockExpiryTime: timerPeriodMillisecs=%"PRIu32", time=%"PRIu32":%"PRIu32":%"PRIu32".%"PRIu32,
                     timerPeriodMillisecs, (u32)tmVal->tm_hour, (u32)tmVal->tm_min, (u32)tmVal->tm_sec, (u32)timeVal.tv_usec);

    u32 millisecsSinceMidnight = (tmVal->tm_hour * 60 * 60 * 1000) +
                                 (tmVal->tm_min * 60 * 1000) +
                                 (tmVal->tm_sec * 1000) +
                                 (timeVal.tv_usec / 1000);
    u32 millisecsToMidnight = (24 * 60 * 60 * 1000) - millisecsSinceMidnight;

    // Get the remainder of dividing the remaining time until midnight
    // by the timer period.  This is when the next timer should expire.
    u32 timeout = millisecsToMidnight % timerPeriodMillisecs;

    TRACE_PRINTF_LEV(TRACE_VERBOSE, "CalculateWallClockExpiryTime: timeout=%"PRIu32, timeout);

    RETURN(timeout);
}


void ThreadlessTimerEngine::CheckHeadTimer()
{
    TimerHandle newHeadTimer = NULL_TIMER;

    if (m_runningTimers.size() > 0)
    {
        newHeadTimer = (*m_runningTimers.begin()).second;
    }

    if ( newHeadTimer != m_headTimer )
    {
        m_headTimer = newHeadTimer;

        if (m_headTimer != NULL_TIMER)
        {
            uptime_t now = GetTickCountMs();
            uptime_t timeout = max(now, (*m_runningTimers.begin()).first);
            u32 relativeTimeout = timeout - now;
            m_SelectorRegisterInterface.RegisterTimeout(relativeTimeout, *this);
        }
    }
}


void ThreadlessTimerEngine::SelectCallBack()
{
    //TODO: ,,,
    CheckTimers();

    DeleteOrRestartExpiredTimers();
}

}
