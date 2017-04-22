///////////////////////////////////////////////////////////////////////////////
//
// UdpMessenger.h
//
// Send and receive messages over UDP e.g. for talking to another application.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpMessenger_h_
#define __UdpMessenger_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <comms/UdpSocket.h>

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

class MessageQueueItem
{
public:

    shared_ptr<SerialisedData> message;
    MessagingEntity fromEntity;
    MessagingEntity toEntity;

    MessageQueueItem& operator=(const MessageQueueItem& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        message = rhs.message;
        fromEntity = rhs.fromEntity;
        toEntity = rhs.toEntity;

        return *this;
    }
};

typedef std::queue<MessageQueueItem> MessageQueue;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class for sending and receiving UDP messages.
 */
class UdpMessenger : public Messenger,
                     public UdpRxInterface
{
    friend class UdpSocket; // For receive callback.
    
public:

    /**
     * Constructor for send only.
     * 
     * \param remoteIpAddress    IP address to send messages to.
     * \param remotePort         Port to send messages to.
     */
    UdpMessenger(IPv4Address remoteIpAddress, u16 remotePort);

    /**
     * Constructor for receive only raw callbacks.
     * 
     * \param localPort          Port to listen on.
     * \param messageRxRawInterface Callback for raw received messages.
     */
    UdpMessenger(u16 localPort,
                 MessageRxRawInterface* messageRxRawInterface);

    /**
     * Constructor for raw callbacks.
     * 
     * \param localPort          Port to listen on.
     * \param remoteIpAddress    IP address to send messages to.
     * \param remotePort         Port to send messages to.
     * \param messageRxRawInterface Callback for raw received messages.
     */
    UdpMessenger(u16 localPort, IPv4Address remoteIpAddress, u16 remotePort,
                 MessageRxRawInterface* messageRxRawInterface);

    /**
     * Constructor for polled mode deserialised messages.
     * 
     * \param localPort          Port to listen on.
     * \param remoteIpAddress    IP address to send messages to.
     * \param remotePort         Port to send messages to.
     * \param serialisableFactory Factory to build an object from received
     *                            serialisation data.
     */
    UdpMessenger(u16 localPort, IPv4Address remoteIpAddress, u16 remotePort);

    virtual ~UdpMessenger();
    
    /**
     * Implement Messenger.
     */
    void StartReceiving();
    void SwitchToPolledMode();
    void RestoreCallbackMode();
    shared_ptr<SerialisedData> BlockingReceiveMessage(u32 timeoutMilliSecs,
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
    /**
     * Common initialise function for all constructors.
     */
    void Initialise();

    // Saved receive callback for raw message receive.
    MessageRxRawInterface* m_savedMessageRxRawInterface;

    // The socket to use for sending/receiving messages.
    UdpSocket m_udpSocket;
    
    // Received message queue for polled mode.
    // Message is deserialised using the supplied factory before being
    // placed on the queue.
    MessageQueue    m_messageQueue;
    Mutex           m_messageQueueMutex;
    Condition       m_messageQueueCondition;

};

}

#endif
