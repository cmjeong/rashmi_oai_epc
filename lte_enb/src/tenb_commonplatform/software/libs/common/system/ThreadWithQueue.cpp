///////////////////////////////////////////////////////////////////////////////
//
// ThreadWithQueue.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ThreadWithQueue.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ThreadQueue::ThreadQueue()
{
    ENTER ();

    Thread::InitialiseMutex(m_queueMutex);
    Thread::ConditionInit(m_queueCondition);

    EXIT ();
}

ThreadQueue::~ThreadQueue()
{
    ENTER ();

    Thread::LockMutex(m_queueMutex);

    // Delete everything left on the queue.
    // Queue contains smart pointers so this won't leave any dangling objects.
    while(!m_priorityQueue.empty())
    {
        m_priorityQueue.pop();
    }
    while(!m_queue.empty())
    {
        m_queue.pop();
    }

    Thread::UnlockMutex(m_queueMutex);

    Thread::ConditionDestroy(m_queueCondition);

    EXIT ();
}

void ThreadQueue::Enqueue(shared_ptr<Queueable> objectToQueue)
{
    ENTER ();

    Thread::LockMutex(m_queueMutex);

    m_queue.push(objectToQueue);

    // Signal to dequeue function that there is a message waiting.
    Thread::ConditionSignal(m_queueCondition);

    Thread::UnlockMutex(m_queueMutex);

    EXIT ();
}

void ThreadQueue::PriorityEnqueue(shared_ptr<Queueable> objectToQueue)
{
    ENTER ();

    Thread::LockMutex(m_queueMutex);

    m_priorityQueue.push(objectToQueue);

    // Signal to dequeue function that there is a message waiting.
    Thread::ConditionSignal(m_queueCondition);

    Thread::UnlockMutex(m_queueMutex);

    EXIT ();
}

shared_ptr<Queueable> ThreadQueue::Dequeue(u32 timeoutMilliSecs)
{
    // No ENTER/EXIT as this is often called in a tight loop.
    shared_ptr<Queueable> dequeuedObject;

    Thread::LockMutex(m_queueMutex);

    struct timespec absTimeout;
    Thread::ConditionGetAbsTimeout(timeoutMilliSecs, &absTimeout);

    // If there's nothing on either queue, wait for a while...
    while(m_queue.empty() && m_priorityQueue.empty())
    {
        // The timed wait function may return before the timeout even if
        // there is nothing on the queue.  Hence we keep checking whether
        // the queue is empty.  The timeout is absolute so we don't need
        // to recalculate it each time.
        if(Thread::ConditionTimedWait(m_queueCondition, m_queueMutex, &absTimeout))
        {
            // Timed out - return empty message
            Thread::UnlockMutex(m_queueMutex);
            return dequeuedObject;
        }
    }

    // There must be at least one object on one of the queues - check the priority queue first.
    if (!m_priorityQueue.empty())
    {
        // Queue is not empty so grab the object off the front.
        dequeuedObject = m_priorityQueue.front();
        // Then remove it from the queue.
        m_priorityQueue.pop();
    }
    else if (!m_queue.empty())
    {
        dequeuedObject = m_queue.front();
        m_queue.pop();
    }

    Thread::UnlockMutex(m_queueMutex);

    return dequeuedObject;
}

ThreadWithQueue::ThreadWithQueue(const char * threadName) :
    Thread(threadName)
{
    ENTER ();

    EXIT ();
}

ThreadWithQueue::~ThreadWithQueue()
{
    ENTER ();

    EXIT ();
}

void ThreadWithQueue::Enqueue(shared_ptr<Queueable> objectToQueue)
{
    ENTER ();

    m_threadQueue.Enqueue(objectToQueue);

    EXIT ();
}

void ThreadWithQueue::PriorityEnqueue(shared_ptr<Queueable> objectToQueue)
{
    ENTER ();

    m_threadQueue.PriorityEnqueue(objectToQueue);

    EXIT ();
}

shared_ptr<Queueable> ThreadWithQueue::Dequeue(u32 timeoutMilliSecs)
{
    return m_threadQueue.Dequeue(timeoutMilliSecs);
}
