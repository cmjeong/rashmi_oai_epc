///////////////////////////////////////////////////////////////////////////////
//
// DeviceTxRx.h
//
// Send and receive packets through a pair of devices e.g. real-time FIFOs.
// One device operates in write-only, the other in read-only.
//
// A mirror class can be used for terminating the remote end although if
// real-time FIFOs, you'll need to use RtFifoTxRx.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DeviceTxRx_h_
#define __DeviceTxRx_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>

#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "DeviceReceiveThread.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class for sending and receiving device e.g. FIFO packets.
 */
class DeviceTxRx
{
public:
    /**
     * Constructor for transmit and receive.
     * Note: Tx and Rx devices must be different.
     *
     * \param rxDevice          Device to receive packets from.
     * \param txDevice          Device to send packets to.
     * \param deviceRxInterface Callback for received packets.
     */
    DeviceTxRx(const char * rxDevice, const char * txDevice,
               DeviceRxInterface& deviceRxInterface);

    virtual ~DeviceTxRx();

    /**
     * Start/stop the device receive thread.
     */
    void StartReceiving();
    void StopReceiving();

    /**
     * Send a packet.
     *
     * \param packet    Packet to send.
     * \param packetLen Length of packet in bytes.
     */
    s32 DeviceSend(const u8* packet, u32 packetLen) const;

    /**
     * Get as string for debug.
     */
    virtual std::string ToString() const;

private:
    // Initialise the transmit section.
    void InitialiseTransmit();

    // Initialise the receive section including constructing the receive thread.
    void InitialiseReceive(DeviceRxInterface& deviceRxInterface);

    // Device for receiving packets.
    const char *        m_rxDevice;

    // Receive thread - only constructed if required.
    shared_ptr<DeviceReceiveThread> m_deviceReceiveThread;

    // Device for sending packets.
    const char *        m_txDevice;
    // File descriptor for sending packets.
    int                 m_txFd;

};

}

#endif
