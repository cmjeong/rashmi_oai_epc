///////////////////////////////////////////////////////////////////////////////
//
// DeviceReceiveThread.h
//
// Thread for receiving packets from a device.  Actual reading from the device
// is done by callback function (class implementing DeviceRxInterface) so as
// to avoid multiple data copies.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DeviceReceiveThread_h_
#define __DeviceReceiveThread_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>

#include <system/Thread.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Callback for received packets.
 */
class DeviceRxInterface
{
public:
    /**
     * Handle a packet received from a device.
     * To read the data, use:
     *   u8 data[SOME_SIZE];
     *   s32 packetLen = read(fd, data, sizeof(data));
     * 
     * \param fd File descriptor to read from
     */
    virtual void HandleDeviceRx(s32 fd) = 0;
    
    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~DeviceRxInterface () {}
};

/**
 * Thread for listening for data to receive from a device.
 */
class DeviceReceiveThread : public Thread
{
public:
    /**
     * Constructor.
     * 
     * \param localPort Port to listen on
     * \param udpRxInterface Callback for received packets
     */
    DeviceReceiveThread(const char * rxDevice, DeviceRxInterface& deviceRxInterface);
    
    /**
     * Override Thread method.
     * Listen to device, call DeviceRxInterface::HandleDeviceRx on interface
     * supplied at construction for each packet.
     */
    virtual u32 ThreadProcedure();
    
    /**
     * After calling StartThread() you can poll to see if the thread is
     * ready to receive packets i.e. has bound to socket.
     */
    bool IsReadyToReceive() const { return m_readyToReceive; };
    
private:
    // Device for receiving packets.
    const char *        m_rxDevice;
    
    // Interface to call on received packets.
    DeviceRxInterface&  m_deviceRxInterface;
    
    // Stores "ready to receive" state of device.  Set true after successfully
    // opening the device.
    bool                m_readyToReceive;
};

}

#endif
