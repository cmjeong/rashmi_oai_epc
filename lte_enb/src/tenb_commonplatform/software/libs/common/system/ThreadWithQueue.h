///////////////////////////////////////////////////////////////////////////////
//
// ThreadWithQueue
//
// Derives from Thread to create a thread with a queue intended
// for serialising objects into the thread from multiple other threads.
//
// Access to the queue is protected so calls to Enqueue/Dequeue()
// are thread-safe.
//
// Example usage:
//
// Create your own type of queued object by deriving from Queueable
// of use Queueable if all you need to convey is a u32.
//
// Derive from ThreadWithQueue and implement ThreadProcedure() with the
// following loop:
//
//    shared_ptr<Queueable> dequeuedObject;
//    while(!ThreadStopped())
//    {
//        dequeuedObject = Dequeue();
//        if(dequeuedObject != NULL)
//        {
//            ... do something with object ...
//            e.g. dynamic_pointer_cast it to your object type
//        }
//    }
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ThreadWithQueue_h_
#define __ThreadWithQueue_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <queue>

#include <boost/shared_ptr.hpp>
#include <system/Thread.h>
#include <system/Queueable.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef shared_ptr<Queueable> QueueablePtr;
typedef std::queue<QueueablePtr> QueueableQueue;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Derived message class for backwards compatibility with earlier version
 */
class ThreadQueuedMessage : public Queueable
{
public:
    ThreadQueuedMessage() : Queueable(Queueable::THREAD_QUEUED_MESSAGE) {};
    virtual ~ThreadQueuedMessage() {};

private:
};

/**
 * Wrap up a queue with thread safe enqueue/dequeue methods.
 */
class ThreadQueue
{
public:

    /**
     * Construction/destruction.
     */
    ThreadQueue();
    virtual ~ThreadQueue();

    /**
     * Add an object to the end of the queue.  Don't hang on to a
     * pointer to the object if you don't need to.
     * Use of smart pointers ensures object will be deleted
     * once removed from queue and finished with.
     *
     * \param objectToQueue The object to queue
     */
    void Enqueue(shared_ptr<Queueable> objectToQueue);

    /**
     * Add an object to the end of the priority queue.  Don't hang on to a
     * pointer to the object if you don't need to.
     * Use of smart pointers ensures object will be deleted
     * once removed from queue and finished with.
     *
     * \param objectToQueue The object to queue
     */
    void PriorityEnqueue(shared_ptr<Queueable> objectToQueue);

    /**
     * Remove oldest object from the queue.
     * The function will return as soon as there is an object available
     * or after the specified timeout if no objects are queued.
     *
     * \param   timeoutMilliSecs Timeout to wait for a queued object
     * \return  The dequeued object, NULL ptr if no object available
     */
    shared_ptr<Queueable> Dequeue(u32 timeoutMilliSecs = 1000);

private:
    QueueableQueue    m_queue;
    QueueableQueue    m_priorityQueue;

    // Mutex and Condition applies to both queues
    Mutex          m_queueMutex;
    Condition      m_queueCondition;
};

/**
 * Thread supporting a queue.
 */
class ThreadWithQueue : public threeway::Thread
{
public:

    /**
     * Construction/destruction.
     */
    ThreadWithQueue(const char * threadName = "Thread With Queue");
    virtual ~ThreadWithQueue();

    /**
     * Delegate this lot to ThreadQueue methods.
     */
    void Enqueue(shared_ptr<Queueable> objectToQueue);
    void PriorityEnqueue(shared_ptr<Queueable> objectToQueue);
    shared_ptr<Queueable> Dequeue(u32 timeoutMilliSecs = 1000);

private:
    ThreadQueue    m_threadQueue;
};

}

#endif
