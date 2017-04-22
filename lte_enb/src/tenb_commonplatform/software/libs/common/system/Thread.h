///////////////////////////////////////////////////////////////////////////////
//
// Thread.h
//
// Generic thread stuff.  Wraps up Posix or other thread library.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Thread_h_
#define __Thread_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <pthread.h>

#include <system/pthread_utils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Thread
{
public:
    /**
     * Static functions for dealing with Mutex's
     * TODO - Maybe move into a Mutex class?
     */
    static void InitialiseMutex(Mutex& mutex);
    static void DestroyMutex(Mutex& mutex);

    static void LockMutex(Mutex& mutex);
    static void LockMutex(Mutex& mutex, const char * functionName);
    static void UnlockMutex(Mutex& mutex);
    static void UnlockMutex(Mutex& mutex, const char * functionName);

    /**
     * Helper class for Mutexes, the Guard class locks the Mutex
     * in the constructor and unlocks in the destructor.
     *
     * Create a Guard on the stack in the scope you want to protect
     * with the mutex and you don't have to worry about which code
     * path is taken, when the scope is left, the mutex is unlocked.
     */
    class Guard
    {
    public:
        Guard(Mutex& mutex) : m_mutex(mutex)
        {
            LockMutex(m_mutex);
        }
        ~Guard()
        {
            UnlockMutex(m_mutex);
        }
    private:
        Mutex& m_mutex;
    };

    /**
     * Static functions for dealing with Condition's
     * TODO - Maybe move into a Condition class?
     */
    static void ConditionInit(Condition& condition);
    static void ConditionDestroy(Condition& condition);

    static void ConditionSignal(Condition& condition);
    static void ConditionWait(Condition& condition, Mutex& mutex);
    // Timed wait - returns true if timeout occurred.
    static void ConditionGetAbsTimeout(u32 relativeTimeoutMs, struct timespec * absTimeout);
    static bool ConditionTimedWait(Condition& condition, Mutex& mutex, struct timespec * absTimeout);

    /**
     * Construction / destruction.
     */
    Thread(const char * threadName = "Unnamed Thread");
    virtual ~Thread();

    /**
     * Set the thread name - its use may change over time so naming at construction
     * may not be enough.
     */
    void SetThreadName(const char * threadName) { m_threadName = threadName; };

    /**
     * Get the thread name for debug.
     */
    const char * GetThreadName() { return m_threadName.c_str(); };

    /**
     * Virtual method which starts a new instance of a worker thread; if custom startup behaviour is
     * required then base classes can override this, however the base implementation MUST be called
     * in order to start the thread.
     */
    virtual void StartThread(u32 threadStackSize = LARGE_DEFAULT_THREAD_STACK_SIZE);

    /**
     * Called in order to terminate a worker thread.  Sets the m_stopThreadEvent and waits to see if the
     * thread stops; if it does not it will be forcibly terminated.
     */
    virtual void StopThread();

    /**
     * This method waits for the worker thread to exit. Its primary role is for when a thread
     * is launched and there is nothing else to do, e.g. in an application main().
     */
    virtual void WaitForThreadToExit();

    /**
     * Abstract method implemented by base classes to provide a worker thread procedure.
     */
    virtual u32 ThreadProcedure() = 0;

    /**
     * The leaf implementation should call this periodically to check whether or not
     * it needs to stop running and exit.
     */
    bool ThreadStopped() const;

    /**
     * Get the thread handle - uniquely identifies the thread.
     */
    pthread_t GetThreadHandle() const;

    /**
     * Check if thread has exited ThreadProcedure().
     * If so, call StopThread() so it joins correctly.
     */
    bool GetThreadExited() const { return m_threadExited; }

    /**
     * Only to be called by capeCanaveral to indicate that ThreadProcedure()
     * exited - allows other threads to check state of this thread using
     * GetThreadExited().
     */
    void SetThreadExited() { m_threadExited = true; }

protected:

    /**
     * Check stack usage for this thread.
     */
    void CheckStackUsage() const;

    /**
     * Thread instance handle; we keep a copy in order to
     * ensure we can terminate worker threads cleanly.
     */
    pthread_t m_threadHandle;

    /**
     * Set this to TRUE to cause a running thread to shutdown.  It will be done
     * automatically in the StopThread() call.
     */
    bool m_threadStopRequest;

private:

    /**
     * Thread name for debug.
     */
    std::string m_threadName;

    /**
     * Stack size that was used to create thread in bfin-uclinux-* builds.
     */
    u32 m_threadStackSize;

    /**
     * Record when the thread exited.
     * Allows another thread chance to check state of this thread.
     */
    bool m_threadExited;
};

}

#endif
