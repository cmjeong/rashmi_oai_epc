///////////////////////////////////////////////////////////////////////////////
//
// ThreadlessUdpMessenger.h
//
// Send and receive messages over UDP e.g. for talking to another application.
// Registers its FD with a Selector class to aid reducing threads.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ThreadlessUdpMessenger_h_
#define __ThreadlessUdpMessenger_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <comms/UdpSocketWithSelect.h>

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
 * Class for sending and receiving UDP messages.
 */
class ThreadlessUdpMessenger : public Messenger,
                               public UdpRxInterface
{
    friend class UdpSocket; // For receive callback.
    
public:

    /**
     * Constructor for raw callbacks.
     * 
     * \param localPort          Port to listen on.
     * \param remoteIpAddress    IP address to send messages to.
     * \param remotePort         Port to send messages to.
     * \param messageRxRawInterface Callback for raw received messages.
     */
    ThreadlessUdpMessenger(SelectorRegisterInterface& selector,
                           u16 localPort, IPv4Address remoteIpAddress, u16 remotePort,
                           MessageRxRawInterface* messageRxRawInterface );

    virtual ~ThreadlessUdpMessenger();
    
    /**
     * Implement Messenger.
     */
    virtual void StartReceiving();
    virtual void SwitchToPolledMode();
    virtual void RestoreCallbackMode();
    virtual shared_ptr<SerialisedData> BlockingReceiveMessage(u32 timeoutMilliSecs,
                                                              MessagingEntity& fromEntity,
                                                              MessagingEntity& toEntity);

protected:
    /**
     * Implement Messenger.
     */
    virtual s32 SendPacket(const u8 * packet, u32 packetLen) const;
    virtual s32 SendRoutedPacket(MessageRouteEntry& route, const u8 * packet, u32 packetLen) const;
    virtual void HandleUnhandledReceivedSerialisedData(MessagingEntity& fromEntity,
                                                       MessagingEntity& toEntity,
                                                       u32 serialisationId,
                                                       const u8 * serialisedData,
                                                       u32 serialisedDataLen);

    /**
     * Implement UdpRxInterface.
     */
    virtual void HandleUdpRx(s32 fd);

private:

    // The socket to use for sending/receiving messages.
    UdpSocketWithSelect m_udpSocket;
};

}

#endif
