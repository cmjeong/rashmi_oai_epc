///////////////////////////////////////////////////////////////////////////////
//
// pthread_utils.h
//
// Wrapper functions for pthread library functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __pthread_utils_h_
#define __pthread_utils_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <3waytypes.h>

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const u32 SMALL_DEFAULT_THREAD_STACK_SIZE = 32 * 1024;
static const u32 MEDIUM_DEFAULT_THREAD_STACK_SIZE = 128 * 1024;
#if defined(BUILD_mipsel_unknown_linux_gnu)
static const u32 LARGE_DEFAULT_THREAD_STACK_SIZE = 296 * 1024;
#else
static const u32 LARGE_DEFAULT_THREAD_STACK_SIZE = 384 * 1024;
#endif
static const u32 MAXIMUM_THREAD_STACK_SIZE = 512 * 1024;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef pthread_mutex_t Mutex;

typedef struct
{
    pthread_cond_t  condition;
    // Mike discovered that condition handling functions can overrun their
    // their allocated space by up to 3 bytes.  Until we understand this
    // better we are going to protect ourselves.
    u32             fence;
} Condition;

/**
 * Thread scheduling policies - abstract, clearer and more portable.
 */
typedef enum
{
    THREAD_POLICY_REGULAR,
    THREAD_POLICY_ROUND_ROBIN,
    THREAD_POLICY_FIFO,
} ThreadPolicy;

/**
 * Thread priorities - abstract and portable.
 */
typedef enum
{
    THREAD_PRIORITY_NORMAL,
    THREAD_PRIORITY_HIGH
} ThreadPriority;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a pthread with our default stack size.
 */
int pthreadUtils_createThread(pthread_t* thread, void* (*start_routine)(void *), void* arg);

/**
 * Create a pthread with a given stack size.
 */
int pthreadUtils_createThreadWithStackSize(pthread_t* thread, void* (*start_routine)(void *), void* arg, u32 stack_size_bytes);

/**
 * Set thread priority.
 */
void pthreadUtils_setThreadPriority(pthread_t thread, ThreadPolicy policy, ThreadPriority priority);

/**
 * Mutexes
 */
// Initialise a mutex.
void pthreadUtils_initialiseMutex(pthread_mutex_t* mutex);
// Lock mutex.
int pthreadUtils_lockMutex(pthread_mutex_t* mutex);
// Unlock mutex.
int pthreadUtils_unlockMutex(pthread_mutex_t* mutex);

/**
 * Condition Variables
 */
// Initialise a condition variable.
void pthreadUtils_conditionInit(Condition* condition);
// Destroy a condition variable.
int pthreadUtils_conditionDestroy(Condition* condition);
// Signal a condition variable.
void pthreadUtils_conditionSignal(Condition* condition);
// Wait for a condition variable.
void pthreadUtils_conditionWait(Condition* condition, pthread_mutex_t* mutex);
// Timed wait for a condition variable.
int  pthreadUtils_conditionTimedWait(Condition* condition, pthread_mutex_t* mutex, struct timespec * absTimeout);
// Get an absolute time given a relative time.
void pthreadUtils_conditionGetAbsTimeout(u32 relativeTimeoutMs, struct timespec * absTimeout);


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif

