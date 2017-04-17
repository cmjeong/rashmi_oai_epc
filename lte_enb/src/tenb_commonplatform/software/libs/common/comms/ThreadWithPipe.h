///////////////////////////////////////////////////////////////////////////////
//
// ThreadWithPipe
//
// Derives from Thread to create a thread with a pipe intended 
// for serialising messages into the thread from multiple other threads.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ThreadWithPipe_h_
#define __ThreadWithPipe_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Thread.h>
#include <comms/Pipe.h>

namespace threeway
{
    
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

template <class T>
class ThreadWithPipe : public Thread
{
public:

    /**
     * Construction/destruction.
     */
    ThreadWithPipe() {};
    virtual ~ThreadWithPipe() {};
    
    // Delegate to Pipe::Write 
    void Write(T& messageToQueue)
    {
        m_pipe.Write(messageToQueue); 
    }
    
protected:

    // Delegate to Pipe::Read 
    bool Read(T& dequeuedMessage, u32 timeoutMillisecs = 1000)
    {
        ENTER()
        RETURN ( m_pipe.Read(dequeuedMessage, timeoutMillisecs) );
    } 

private:

    // The pipe used to serialise messages into this thread.
    Pipe<T> m_pipe;
    
};

}

#endif
