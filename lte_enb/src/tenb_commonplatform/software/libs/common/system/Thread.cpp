///////////////////////////////////////////////////////////////////////////////
//
// Thread.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <errno.h>

#include <system/Thread.h>
#include <system/Exception.h>
#include <system/Trace.h>
#include <system/threadstack.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Thread.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

void *capeCanaveral (void *threadArg)
{
    ENTER ();
    bool bExceptionRaised = false;

    // Thread owners should always catch their own exceptions, but since they
    // sometimes (!) forget lets do a last resort catch here so at least something
    // gets logged...
    try
    {
        // You can inspect the return value from the thread proc if you want >:-)
        Thread *thread = (Thread *)threadArg;
        /* u32 retVal = */ thread->ThreadProcedure();

        // ThreadProcedure() returned... may be because StopThread()
        // was called or maybe it had just finished doing its stuff.
        // In the second case, we should record that it has exited so that
        // other threads can check to see if it is running or not.
        thread->SetThreadExited();
    }
    catch (Exception& e)
    {
        TRACE_MSG ("Thread: Caught threeway::Exception:");
        TRACE_MSG (e.what());
        bExceptionRaised = true;
    }
    catch (std::exception& e)
    {
        TRACE_MSG ("Thread: Caught std::exception:");
        TRACE_MSG (e.what());
        bExceptionRaised = true;
    }
    catch (int e)
    {
        TRACE ("Thread: Caught int exception", (s32)e);
        bExceptionRaised = true;
    }
    catch (...)
    {
        TRACE_MSG ("Thread: Uh oh, unknown exception!");
        bExceptionRaised = true;
    }

    // If an exception was caught at this level, it means that the application
    // threw an exception, but failed to handle it gracefully
    // the 'not so graceful' handling at this level is to exit the process (abort)
    // and let watchdog do what it does best...reboot!!!
    if (bExceptionRaised)
    {
        TRACE_MSG_LEV(TRACE_FATAL, "Thread: Aborting the process due to unhandled exception!");
        abort();
    }

    RETURN (NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Static Class Functions
///////////////////////////////////////////////////////////////////////////////

void Thread::InitialiseMutex(Mutex& mutex)
{
    pthreadUtils_initialiseMutex((pthread_mutex_t*)&mutex);
}

void Thread::DestroyMutex(Mutex& mutex)
{
    pthread_mutex_destroy((pthread_mutex_t*)&mutex);
}

void Thread::LockMutex(Mutex& mutex)
{
    pthreadUtils_lockMutex((pthread_mutex_t*)&mutex);
}

void Thread::LockMutex(Mutex& mutex, const char * functionName)
{
    pthreadUtils_lockMutex((pthread_mutex_t*)&mutex);
}

void Thread::UnlockMutex(Mutex& mutex)
{
    pthreadUtils_unlockMutex((pthread_mutex_t*)&mutex);
}

void Thread::UnlockMutex(Mutex& mutex, const char * functionName)
{
    pthreadUtils_unlockMutex((pthread_mutex_t*)&mutex);
}

void Thread::ConditionInit(Condition& condition)
{
    pthreadUtils_conditionInit(&condition);
}

void Thread::ConditionDestroy(Condition& condition)
{
    pthreadUtils_conditionDestroy(&condition);
}

void Thread::ConditionSignal(Condition& condition)
{
    pthreadUtils_conditionSignal(&condition);
}

void Thread::ConditionWait(Condition& condition, Mutex& mutex)
{
    pthreadUtils_conditionWait(&condition, (pthread_mutex_t*)&mutex);
}

bool Thread::ConditionTimedWait(Condition& condition, Mutex& mutex, struct timespec * absTimeout)
{
    if(pthreadUtils_conditionTimedWait(&condition,
                                     (pthread_mutex_t*)&mutex,
                                     absTimeout) == ETIMEDOUT)
    {
        return true;
    }

    return false;
}

void Thread::ConditionGetAbsTimeout(u32 relativeTimeoutMs, struct timespec * absTimeout)
{
    pthreadUtils_conditionGetAbsTimeout(relativeTimeoutMs, absTimeout);
}


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Thread::Thread(const char * threadName) :
    m_threadHandle(0),
    m_threadStopRequest(false),
    m_threadName(threadName),
    m_threadStackSize(LARGE_DEFAULT_THREAD_STACK_SIZE),
    m_threadExited(false)
{}

Thread::~Thread()
{
    // TODO - should we stop the thread here?
    // StopThread();
}

void Thread::StartThread(u32 threadStackSize)
{
    ENTER ();

    m_threadStopRequest = false;
    m_threadStackSize = threadStackSize;

    int createResult = pthreadUtils_createThreadWithStackSize (&m_threadHandle, capeCanaveral, (void *) this, m_threadStackSize);
    if (createResult != 0)
    {
        m_threadHandle = 0;

        EXIT ();
        throw Exception (
            __FILE__,
            __LINE__,
            "Failed To Create Worker Thread [%ul]",
            createResult);
    }//end if

    EXIT ();
}

void Thread::WaitForThreadToExit()
{
    ENTER();

    if (m_threadHandle != 0)
    {
        // Sit and wait for the thread to exit
        pthread_join (m_threadHandle, NULL);
        m_threadHandle = 0;
    }//end if

    EXIT();
}

void Thread::StopThread()
{
    ENTER();

    if (m_threadHandle != 0)
    {
        // Setting this bool to true should cause the main thread procedure
        // derived in a leaf implementation to exit...
        m_threadStopRequest = true;

        // In which case the join() call below shouldn't take too long.
        pthread_join (m_threadHandle, NULL);
        m_threadHandle = 0;
    }//end if

    EXIT();
}

bool Thread::ThreadStopped () const
{
    return m_threadStopRequest;
}

void Thread::CheckStackUsage() const
{
#if defined(BUILD_bfin_uclinux_2006) || defined(BUILD_bfin_uclinux_2008)
    pthread_t thread = pthread_self();
    u32 stackUsage;

    stackUsage = threadstack_used(&thread);
    TRACE("  Thread name", m_threadName.c_str());
    TRACE("  Peak stack usage", stackUsage);
    TRACE("  Allocated stack", m_threadStackSize);
    // Warn if blown or close to blowing.
    if(stackUsage >= m_threadStackSize - 1024) {
        TRACE("THREAD STACK WARNING!  Thread ID", (u32)thread);
    }
#endif
}

pthread_t Thread::GetThreadHandle() const
{
    ENTER();
    RETURN(m_threadHandle);
}

}
