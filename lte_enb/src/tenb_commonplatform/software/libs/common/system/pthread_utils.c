///////////////////////////////////////////////////////////////////////////////
//
// pthread_utils.c
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#if !defined(TARGET_rtl) && !defined(_GNU_SOURCE)
// The GNU extensions don't seem to work on rtlinux.
#define _GNU_SOURCE
#endif
#include <sys/time.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <errno.h> // eventually includes /usr/include/asm/errno.h on RH9
#include <limits.h>
#include <unistd.h>
#include <string.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "pthread_utils.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

static const char * getMutexErrorStr(int result);

int pthreadUtils_createThread(pthread_t* thread, void* (*start_routine)(void *), void* arg)
{
    ENTER();
    RETURN(pthreadUtils_createThreadWithStackSize(thread, start_routine, arg, LARGE_DEFAULT_THREAD_STACK_SIZE));
}

int pthreadUtils_createThreadWithStackSize(pthread_t* thread, void* (*start_routine)(void *), void* arg, u32 stack_size_bytes)
{
    ENTER();

    pthread_attr_t thread_attr;
    int status;
    int destroy_status;

    status = pthread_attr_init (&thread_attr);
    if (status != 0)
    {
        TRACE_PRINTF("pthreadUtils_createThreadWithStackSize: pthread_attr_init failed: %d", status);
        return status;
    }

#ifdef _POSIX_THREAD_ATTR_STACKSIZE
#ifndef PLATFORM_BRDCM
    // If supported select a stack size for the new thread.
    status = pthread_attr_setstacksize(&thread_attr, stack_size_bytes);
    if (status != 0)
    {
        TRACE_PRINTF("pthreadUtils_createThreadWithStackSize: pthread_attr_setstacksize failed: %d", status);
        return status;
    }
#endif
#endif

    status = pthread_create(thread, &thread_attr, start_routine, arg);

    if (status != 0)
    {
        TRACE_PRINTF("pthreadUtils_createThreadWithStackSize: pthread_create failed: %d", status);
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
        TRACE_PRINTF("                                        stack size set to: %" PRIu32 " bytes", stack_size_bytes);
#else
        TRACE_PRINTF("                                        stack size set to default");
#endif
    }
    else
    {
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
        TRACE_PRINTF("Created thread with stack size %" PRIu32 " bytes", stack_size_bytes);
#else
        TRACE_PRINTF("Created thread with default stack size");
#endif
    }

    destroy_status = pthread_attr_destroy (&thread_attr);
    if (destroy_status != 0)
    {
        TRACE_PRINTF("pthreadUtils_createThreadWithStackSize: pthread_attr_destroy failed: %d", destroy_status);
        return status;
    }
    RETURN(status);
}

void pthreadUtils_setThreadPriority(pthread_t thread, ThreadPolicy policy, ThreadPriority priority)
{
    struct sched_param p;
    int schedPolicy = SCHED_OTHER; // Compiler unused var fix

    switch(policy)
    {
    case THREAD_POLICY_REGULAR:
        schedPolicy = SCHED_OTHER;
        break;
    case THREAD_POLICY_ROUND_ROBIN:
        schedPolicy = SCHED_RR;
        break;
    case THREAD_POLICY_FIFO:
        schedPolicy = SCHED_FIFO;
        break;
    default:
        RSYS_ASSERT("Unsupported thread policy");
        break;
    }
    int priorityMin = sched_get_priority_min(schedPolicy);
    int priorityMax = sched_get_priority_max(schedPolicy);

    switch(priority)
    {
    case THREAD_PRIORITY_NORMAL:
        p.sched_priority = priorityMin;
        break;
    case THREAD_PRIORITY_HIGH:
        p.sched_priority = priorityMax;
        break;
    default:
        RSYS_ASSERT("Unsupported thread priority");
        break;
    }

    TRACE_PRINTF("Setting thread=%"PRIu32" to policy=%"PRIi32", priority=%"PRIi32, (u32)thread, schedPolicy, p.sched_priority);

    int result = pthread_setschedparam(thread, schedPolicy, &p);
    RSYS_ASSERT_PRINTF(result == 0, "Failed to set thread scheduling policy/priority, result=%"PRIi32, result);
}

void pthreadUtils_initialiseMutex(pthread_mutex_t* mutex)
{
    ENTER ();
#if defined(__XENO__) || defined(BUILD_arm_none_linux_gnueabi) || (BUILD_mipsel_unknown_linux_gnu)
    // Standard initialisation
    pthread_mutex_init(mutex, NULL);
#else

#if defined(BUILD_i686_pc_cygwin)
    *mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
#else
# ifdef BUILD_i686_linux
    // The bit of code below for bfin-uclinux works on RH9 but not FC5, hence
    // doing it this way (maybe this works for all of the builds, hmm, must
    // try that sometime).
#  ifdef TARGET_rtl
    // And another complication.  I can't get error checking mutex's to
    // work with rtlinux.
    const pthread_mutex_t theMutex = PTHREAD_MUTEX_INITIALIZER;
#  else
    const pthread_mutex_t theMutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
#  endif
    memcpy (mutex, &theMutex, sizeof (pthread_mutex_t));
# else
    // bfin-uclinux
    pthread_mutexattr_t mutexType;
    mutexType.__mutexkind = PTHREAD_MUTEX_ERRORCHECK_NP;
    pthread_mutex_init(mutex, &mutexType);
# endif
#endif
#endif
    EXIT ();
}

int pthreadUtils_lockMutex(pthread_mutex_t* mutex)
{
    // Intentionally no ENTER/EXIT.

    int result = 0;

    result = pthread_mutex_lock(mutex);
    if(result)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "Mutex lock failed: %s", getMutexErrorStr(result));
    }

    return result;
}

int pthreadUtils_unlockMutex(pthread_mutex_t* mutex)
{
    // Intentionally no ENTER/EXIT.

    int result = 0;

    result = pthread_mutex_unlock(mutex);
    if(result)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "Mutex unlock failed: %s", getMutexErrorStr(result));
    }

    return result;
}

void pthreadUtils_conditionInit(Condition* condition)
{
    ENTER();

    condition->fence = 0;
    pthread_cond_init(&(condition->condition), NULL); // Never returns an error code.

    EXIT();
}

int pthreadUtils_conditionDestroy(Condition* condition)
{
    ENTER();

    int result = pthread_cond_destroy(&(condition->condition));

    if(result)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "Condition var destroy failed, result=%d", result);
        if(result == EBUSY)
        {
            TRACE_PRINTF("   Threads are currently waiting on cond var");
        }
    }

    RETURN(result);
}

void pthreadUtils_conditionSignal(Condition* condition)
{
    pthread_cond_signal(&(condition->condition)); // Never returns an error code.
}

void pthreadUtils_conditionWait(Condition* condition, pthread_mutex_t* mutex)
{
    int result = pthread_cond_wait(&(condition->condition), mutex);

    if(result)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "Condition var wait failed, result=%d", result);
    }
}

int pthreadUtils_conditionTimedWait(Condition* condition, pthread_mutex_t* mutex, struct timespec * absTimeout)
{
    // The only error codes this returns are ETIMEDOUT and EINTR both
    // of which are normal so we don't bother checking.
    return pthread_cond_timedwait(&(condition->condition), mutex, absTimeout);
}

void pthreadUtils_conditionGetAbsTimeout(u32 relativeTimeoutMs, struct timespec * absTimeout)
{
    int retcode;
    struct timeval nowTime;

    retcode = gettimeofday(&nowTime, NULL);
    if(retcode == 0)
    {
        div_t relativeTimeout_sec = div(relativeTimeoutMs,1000);

        /**
         *  Add timeout to tv and store in absTimeout
         */

        /**
         * To overflow tv_sec...
         * now + timeout > 4.3billion seconds (136yrs) [since epoch (1/1/1970) i.e. AD.2106]
         * Assuming now is approx 2006, timeouts can be upto 100years,
         * which is fairly difficult to represent in a u32{milliseconds}. [0xffffffff=49days]
         */
        absTimeout->tv_sec = nowTime.tv_sec  + relativeTimeout_sec.quot;
        u32 tmp_usec       = nowTime.tv_usec + (relativeTimeout_sec.rem*1000);

        if(tmp_usec >= 1000000)
        {
            ++absTimeout->tv_sec;
            tmp_usec -= 1000000;
        }

        absTimeout->tv_nsec  = tmp_usec;
        absTimeout->tv_nsec *= 1000;
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "gettimeofday failed, result=%"PRId32, retcode);
    }
}

static const char * getMutexErrorStr(int result)
{
    // Intentionally no ENTER/EXIT.

    if(!result)
    {
        return NULL;
    }

    switch(result)
    {
        case EINVAL:
            return "Mutex has not been properly initialized";
            break;
        case EDEADLK:
            return "Deadlock would occur";
            break;
        case EPERM:
            return "Calling thread does not own the mutex";
            break;
        default:
            break;
    }

    return "Unrecognised error code";
}
