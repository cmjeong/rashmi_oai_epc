///////////////////////////////////////////////////////////////////////////////
//
// DeviceMessenger.h
//
// Send and receive messages over devices e.g. over RT FIFOs, for talking
// to another application.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DeviceMessenger_h_
#define __DeviceMessenger_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <comms/DeviceTxRx.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Messenger.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class Serialisable;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class for sending and receiving messages over devices e.g. RT FIFOs.
 */
class DeviceMessenger : public Messenger,
                        public DeviceRxInterface
{
    friend class DeviceTxRx; // For receive callback.

public:
    /**
     * Constructor.
     *
     * \param rxDevice           Device to receive messages on.
     * \param txDevice           Device to send messages on.
     * \param messageRxRawInterface Callback for received messages
     */
    DeviceMessenger(const char * rxDevice, const char * txDevice,
                    MessageRxRawInterface* messageRxRawInterface);

    virtual ~DeviceMessenger();

    /**
     * Start receiving messages (starts up the device receive thread).
     */
    void StartReceiving();

protected:

    /**
     * Implement Messenger pure virtuals.
     */
    virtual s32 SendPacket(const u8 * packet, u32 packetLen) const;
    virtual s32 SendRoutedPacket(MessageRouteEntry& route, const u8 * packet, u32 packetLen) const;

    /**
     * Implement DeviceRxInterface.
     */
    virtual void HandleDeviceRx(s32 fd);

private:
    // The class to use for sending/receiving packets.
    DeviceTxRx          m_deviceTxRx;

};

}

#endif
