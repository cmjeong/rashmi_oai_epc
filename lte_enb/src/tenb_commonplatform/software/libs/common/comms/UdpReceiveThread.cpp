///////////////////////////////////////////////////////////////////////////////
//
// UdpReceiveThread.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef HARDWARE_hbs2_4
#include <sys/prctl.h>
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <fcntl.h>

#include <system/Trace.h>
#include <system/Thread.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UdpReceiveThread.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class - UdpReceiveThread
///////////////////////////////////////////////////////////////////////////////

UdpReceiveThread::UdpReceiveThread(GetFdInterface& associatedSocket, UdpRxInterface& udpRxInterface) :
    Thread("Udp Receive Thread"),
    m_associatedSocket(associatedSocket),
    m_udpRxInterface(udpRxInterface),
    m_readyToReceive(false)
{
    ENTER ();

    int r = pipe(m_stopPipe);
    RSYS_ASSERT(r == 0);

    // Close on exec
    fcntl(m_stopPipe[0], F_SETFD, FD_CLOEXEC);
    fcntl(m_stopPipe[1], F_SETFD, FD_CLOEXEC);

    EXIT ();
}

void UdpReceiveThread::StopThread()
{
    if (m_threadHandle != 0)
    {
        char c = 's';
	int w_ret = -1;

        TRACE("UdpReceiveThread stopping", GetThreadName());

        // Setting this bool to true should cause the main thread procedure
        //  exit...
        m_threadStopRequest = true;

        // Unblock select
        w_ret = write(m_stopPipe[1], &c, sizeof(c));
	if(w_ret < 1)
        {
                TRACE_MSG("Error while writing to stop Pipe");
        }
	

        // In which case the join() call below shouldn't take too long.
        pthread_join (m_threadHandle, NULL);
        m_threadHandle = 0;

        // No longer needed
        close(m_stopPipe[0]);
        close(m_stopPipe[1]);
    }//end if
}

u32 UdpReceiveThread::ThreadProcedure()
{
    ENTER ();

    TRACE_PRINTF("Running %s: pid=%d", GetThreadName(), getpid());

#ifdef HARDWARE_hbs2_4
    char name[17];

    /* Get the name and ensure it is null terminated */
    prctl(PR_GET_NAME, name, 0, 0, 0);
    name[16] = '\0';

    /* Add extension to name if there is space */
    /* Kloc work fix for ABV.GENERAL */
    if(strlen(name) <= 12)
    {
      strncat(name, "-urt", 4);
    }
   
    /* Set the new name */
    prctl(PR_SET_NAME, name, 0, 0, 0);
#endif

    m_readyToReceive = true;

    // Create the read FD set.
    fd_set rxSet;
    FD_ZERO(&rxSet);

    int nfds = m_stopPipe[0] > m_associatedSocket.GetFd() ? m_stopPipe[0] + 1 : m_associatedSocket.GetFd() + 1;

    while(!ThreadStopped())
    {
        // Use select to wait for new packets.
        FD_SET(m_associatedSocket.GetFd(), &rxSet);
        FD_SET(m_stopPipe[0], &rxSet);

        // Wait for something
        select(nfds, &rxSet, NULL, NULL, NULL);

        // If it's a packet for us, pass it on.
        if(FD_ISSET(m_associatedSocket.GetFd(), &rxSet))
        {
            m_udpRxInterface.HandleUdpRx(m_associatedSocket.GetFd());
        }
    }

    TRACE("UdpReceiveThread stopped", GetThreadName());

    RETURN (0);
}
