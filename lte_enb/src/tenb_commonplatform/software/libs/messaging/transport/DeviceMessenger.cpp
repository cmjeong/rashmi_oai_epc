///////////////////////////////////////////////////////////////////////////////
//
// DeviceMessenger.cpp
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <system/Trace.h>
#include <system/SerialisedData.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "DeviceMessenger.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

DeviceMessenger::DeviceMessenger(const char * rxDevice, const char * txDevice,
                                 MessageRxRawInterface* messageRxRawInterface) :
    Messenger(messageRxRawInterface),
    m_deviceTxRx(rxDevice, txDevice, *this)
{
    ENTER ();

    EXIT ();
}

DeviceMessenger::~DeviceMessenger()
{
    ENTER ();

    // m_deviceTxRx goes out of scope so the receive thread is stopped and
    // the devices are closed.  And everybody's happy.

    EXIT ();
}

void DeviceMessenger::StartReceiving()
{
    ENTER ();

    m_deviceTxRx.StartReceiving();

    EXIT ();
}

s32 DeviceMessenger::SendPacket(const u8 * packet, u32 packetLen) const
{
    ENTER();

    RETURN(m_deviceTxRx.DeviceSend(packet, packetLen));
}

s32 DeviceMessenger::SendRoutedPacket(MessageRouteEntry& route, const u8 * packet, u32 packetLen) const
{
    ENTER();

    // For the old device messenger, we can't support the concept of message routing,
    // so send the message over the configured default route.
    RETURN(m_deviceTxRx.DeviceSend(packet, packetLen));
}

void DeviceMessenger::HandleDeviceRx(s32 fd)
{
    ENTER ();

    u8 packet[MESSENGER_MAX_SERIALISED_PACKET_LEN];

    // Receive the device packet.
    int packetLen = read(fd, packet, sizeof(packet));

    if(packetLen > 0)
    {
        // Get the base class to handle it and call the client with the message.
        HandleReceivedPacket(packet, packetLen);
    }
    else
    {
        TRACE_LEV(TRACE_WARNING, "DeviceMessenger::HandleDeviceRx(): packetLen", (s32)packetLen);
    }

    EXIT ();
}
