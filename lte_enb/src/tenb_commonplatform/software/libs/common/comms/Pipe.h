///////////////////////////////////////////////////////////////////////////////
//
// Pipe.h
//
// Wrapper for linux pipe to provide timeouts on read etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Pipe_h_
#define __Pipe_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

template <class T>
class Pipe
{
public:

    /**
     * Construction/destruction.
     */
    Pipe()
    {
        int pipeFds[2];

        // Create pipe.
        pipe(pipeFds);
        
        // Get FDs.
        m_pipeReadFd = pipeFds[0];
        m_pipeWriteFd = pipeFds[1];
        
        // Open as streams so can use fprintf etc.
        m_readStream = fdopen (m_pipeReadFd, "r");
        m_writeStream = fdopen (m_pipeWriteFd, "w");
    }
    
    virtual ~Pipe()
    {
        // Close pipe FDs.
        close(m_pipeReadFd);
        close(m_pipeWriteFd);
    }

    /**
     * Get the write FD for passing on to things that want to write to it.
     * NOTE: This is not the best way but is here to support old way of doing it.
     *       Just pass around a reference to Pipe and use Write for new designs.
     */    
    int GetWriteFd()
    {
        ENTER();
        RETURN (m_pipeWriteFd);
    }
    
    /**
     * Get the write stream for the pipe.
     * This allows use of e.g. fprintf.
     * Don't forget to call Flush() if you want it to go immediately.
     */
    FILE* GetWriteStream()
    {
        ENTER();
        RETURN (m_writeStream);
    }
    
    /**
     * Write a message to the pipe.
     * This will be copied in to the pipe so the caller is free
     * to destroy the message.
     * 
     * \param messageToQueue The message to queue
     */ 
    void Write(T& messageToQueue)
    {
        ENTER();
        
        write (m_pipeWriteFd, &messageToQueue, sizeof(T));
        
        EXIT();
    }
    
    /**
     * Call this if you've written to the pipe using the stream
     * file descriptor e.g. after doing a fprintf() to it.
     */
    void Flush()
    {
        ENTER();
        
        fflush(m_writeStream);
        
        ENTER();
    }
    
    /**
     * Read oldest message from the thread pipe.
     * 
     * \param   dequeuedMessage The message read from the pipe.
     * \param   timeoutMillisecs Pipe read timeout in ms.
     * \return true if there was a message, false if timed out.
     */
    bool Read(T& dequeuedMessage, u32 timeoutMillisecs)
    {
        ENTER();
        
        fd_set readFdSet;
        struct timeval timeout;

        timeout.tv_sec = timeoutMillisecs / 1000;
        timeout.tv_usec = 1000 * (timeoutMillisecs % 1000);
        
        // Clear the FD set.    
        FD_ZERO(&readFdSet);
        // Add read FD to the select FD set.
        FD_SET(m_pipeReadFd, &readFdSet);

        int numFds = select(FD_SETSIZE, &readFdSet, NULL, NULL, &timeout);

        if(numFds < 0)
        {
            TRACE("Pipe: select error", (s32)numFds);
            RETURN (false);
        }

        if(FD_ISSET(m_pipeReadFd, &readFdSet))
        {
            int readResult = read (m_pipeReadFd, &dequeuedMessage, sizeof(T));
            if(readResult == sizeof(T))
            {
                RETURN (true);
            }
            
            TRACE("Pipe: read error", (s32)readResult);
        }
        
        RETURN (false);
    } 

private:
    int m_pipeReadFd;
    int m_pipeWriteFd;
    FILE* m_writeStream;
    FILE* m_readStream;
};

}

#endif
