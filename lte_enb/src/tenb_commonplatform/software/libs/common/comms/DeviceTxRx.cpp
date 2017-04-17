///////////////////////////////////////////////////////////////////////////////
//
// DeviceTxRx.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "DeviceTxRx.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class - DeviceTxRx
///////////////////////////////////////////////////////////////////////////////

DeviceTxRx::DeviceTxRx(const char * rxDevice, const char * txDevice,
                       DeviceRxInterface& deviceRxInterface) :
    m_rxDevice(rxDevice),
    m_txDevice(txDevice),
    m_txFd(-1)
{
    ENTER ();

    // Initialise both receive and transmit.
    InitialiseReceive(deviceRxInterface);
    InitialiseTransmit();

    EXIT ();
}

DeviceTxRx::~DeviceTxRx()
{
    ENTER ();

    // Clean up the receive thread.
    if(m_deviceReceiveThread != NULL)
    {
        StopReceiving();
    }

    // And close the transmit socket.
    if(m_txFd >= 0)
    {
        close(m_txFd);
    }

    EXIT ();
}

void DeviceTxRx::StartReceiving()
{
    ENTER ();

    if(m_deviceReceiveThread != NULL)
    {
        m_deviceReceiveThread->StartThread();

        TRACE_MSG("Waiting for device receive thread to be ready ...");

        while(!m_deviceReceiveThread->IsReadyToReceive())
        {
            /* Allow other threads to run before re-checking */
            sched_yield();
        }

        TRACE_MSG("  ... it's ready!");
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "DeviceTxRx::StartReceiving(): %s not configured for receiving", ToString().c_str());
    }

    EXIT ();
}

void DeviceTxRx::StopReceiving()
{
    ENTER ();

    if(m_deviceReceiveThread != NULL)
    {
        m_deviceReceiveThread->StopThread();
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "DeviceTxRx::StopReceiving(): %s not configured for receiving", ToString().c_str());
    }

    EXIT ();
}

s32 DeviceTxRx::DeviceSend(const u8* packet, u32 packetLen) const
{
    ENTER ();

    if(m_txFd >= 0)
    {
        TRACE_PRINTF("DeviceTxRx: Writing packet, packetLen=%" PRIu32, packetLen);
        RETURN (write(m_txFd, packet, packetLen));
    }

    TRACE_PRINTF_LEV(TRACE_WARNING, "DeviceTxRx::DeviceSend(): %s not configured for transmit", ToString().c_str());

    RETURN(-1);
}

string DeviceTxRx::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "TxDevice=" << m_txDevice << ", RxDevice=" << m_rxDevice;

    RETURN(stream.str());
}

void DeviceTxRx::InitialiseTransmit()
{
    ENTER();

    // Open transmit socket.
    m_txFd = open(m_txDevice, O_WRONLY);
    if(m_txFd < 0)
    {
        TRACE_LEV(TRACE_WARNING, "DeviceTxRx: Error opening device", (s32)errno);
    }
    else
    {
        TRACE("DeviceTxRx: Transmit opened", m_txDevice);
    }

    EXIT();
}

void DeviceTxRx::InitialiseReceive(DeviceRxInterface& deviceRxInterface)
{
    ENTER();

    m_deviceReceiveThread.reset(new DeviceReceiveThread(m_rxDevice, deviceRxInterface));

    TRACE("DeviceTxRx: Receive thread created", m_rxDevice);

    EXIT();
}
