///////////////////////////////////////////////////////////////////////////////
//
// DeviceReceiveThread.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <system/Trace.h>
#include <system/Thread.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "DeviceReceiveThread.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class - DeviceReceiveThread
///////////////////////////////////////////////////////////////////////////////

DeviceReceiveThread::DeviceReceiveThread(const char * rxDevice, DeviceRxInterface& deviceRxInterface) :
    Thread("Device Receive Thread"),
    m_rxDevice(rxDevice),
    m_deviceRxInterface(deviceRxInterface),
    m_readyToReceive(false)
{
    ENTER ();
    EXIT ();
}

u32 DeviceReceiveThread::ThreadProcedure()
{
    ENTER ();

    TRACE("Running DeviceReceiveThread", GetThreadName());
    TRACE("  Receive device", (u32)m_rxDevice);

    int fd = open(m_rxDevice, O_RDONLY);
    RSYS_ASSERT(fd != -1);

    m_readyToReceive = true;

    // Read FD set.
    fd_set rxSet;

    // We'll timeout the select every second so we can check for thread shutdown.
    struct timeval timeout;

    while(!ThreadStopped())
    {
        // Use select to wait for new packets.
        FD_ZERO(&rxSet);
        FD_SET(fd, &rxSet);

        // Set the timeout again as select may change it.
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Wait for a packet or timeout.
        select(fd+1, &rxSet, NULL, NULL, &timeout);

        if(FD_ISSET(fd, &rxSet))
        {
            // It's for us, pass it on.
            m_deviceRxInterface.HandleDeviceRx(fd);
        }

        // Check stack usage for this thread.
        //CheckStackUsage();
    }

    close(fd);

    TRACE("DeviceReceiveThread stopped", GetThreadName());

    RETURN (0);
}
