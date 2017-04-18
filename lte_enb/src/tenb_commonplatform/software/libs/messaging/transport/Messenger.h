///////////////////////////////////////////////////////////////////////////////
//
// Messenger.h
//
// Abstract class for sending and receiving messages.
// Derived classes implement the transport mechanism.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Messenger_h_
#define __Messenger_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <queue>

#include <boost/shared_ptr.hpp>
#include <system/SerialisedData.h>
#include <system/Thread.h>
#include <messaging/messages/common/MessagingRouteInd.h>
#include <messaging/transport/MessageRoutingTable.h>
#include <messaging/transport/MessageRouteEntry.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingEntity.h"

using namespace boost;

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
 * Interface for sending a message.
 * Allows classes that want to send messages to be decoupled from SingleThreadedApplicationWithMessaging.
 */
class SendMessageInterface
{
public:
    virtual ~SendMessageInterface() {};

    /**
     * Send a message with given from/to entity.
     */
    virtual bool SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity) const = 0;
};

/**
 * Callback for raw received messages.
 */
class MessageRxRawInterface
{
public:
    /**
     * Handle a received message.
     *
     * \param fromEntity        The unique ID for the sending entity.
     * \param toEntity          The unique ID for the receiving entity.
     * \param serialisationId   Uniquely identifies serialised class.
     * \param serialisedData    The serialised class data stream.
     * \param serialisedDataLen Length of above data in bytes.
     */
    virtual void ReceiveMessage(MessagingEntity fromEntity, MessagingEntity toEntity,
                                u32 serialisationId, const u8* serialisedData, u32 serialisedDataLen) = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~MessageRxRawInterface () {}
};

/**
 * Class for sending and receiving UDP messages.
 */
class Messenger
{
public:

    /**
     * Constructor for a polled receive messenger i.e. user must poll
     * for received messages, there is no callback mechanism.
     */
    Messenger();

    /**
     * Constructor for a callback receive messenger i.e. received messages
     * will be passed to the supplied callback interface.
     *
     * \param messageRxRawInterface Callback for received messages.
     */
    Messenger(MessageRxRawInterface* messageRxRawInterface);

    virtual ~Messenger();

    /**
     * Start receiving messages (starts up a receive thread).
     */
    virtual void StartReceiving() = 0;

    /**
     * Send a message with a tag that can be recovered at the other end.
     * The intention is that this is used for routing to some entity
     * beyond the realm of the Messenger.
     *
     * \param message    A serialisable object to be serialised and sent.
     * \param fromEntity The unique ID for the sending entity.
     * \param toEntity   The unique ID for the receiving entity.
     * \return           true on successful send of message, false otherwise.
     */
    bool SendMessage(const Serialisable& message, MessagingEntity fromEntity, MessagingEntity toEntity) const;

    /**
     * Switch to polled mode. Will save the current messageRxRawInterface
     * callback, and switch into polled mode. This is intended for temporary
     * use when implementing blocking calls e.g. entity registration.
     */
    virtual void SwitchToPolledMode() = 0;

    /**
     * Restore callback mode (if the Messenger was constructed with
     * a messageRxRawInterface callback).
     */
    virtual void RestoreCallbackMode() = 0;

    /**
     * Block until message received.
     *
     * \param timeoutMilliSecs  Time to wait for a message.  Will return sooner
     *                          if message received.
     * \param fromEntity        The unique ID for the sending entity.
     * \param toEntity          The unique ID for the receiving entity.
     * \return                  Pointer to the received and serialised data.
     *                          NULL if no message received or invalid.
     */
    virtual shared_ptr<SerialisedData> BlockingReceiveMessage(u32 timeoutMilliSecs,
                                                              MessagingEntity& fromEntity,
                                                              MessagingEntity& toEntity) = 0;
                                                      
    /**
     * Check to see if an entity is registered.
     */
    bool IsRouteAvailable(const MessagingEntity& entity);

protected:

    /**
     * Send a packet over whatever transport mechanism the derived
     * class uses, e.g. UDP socket, FIFO, ...
     *
     * The packet is sent to the default destination configured in the
     * derived class. To send on a specific route, use SendRoutedPacket()
     *
     * \param packet    Packet to send.
     * \param packetLen Packet length in bytes.
     * \return          Length of message sent or -1 on error.
     */
    virtual s32 SendPacket(const u8 * packet, u32 packetLen) const = 0;

    /**
     * Send a packet over whatever transport mechanism the derived
     * class uses, e.g. UDP socket, FIFO, ...
     *
     * \param route     The route to use to send the packet
     * \param packet    Packet to send.
     * \param packetLen Packet length in bytes.
     * \return          Length of message sent or -1 on error.
     */
    virtual s32 SendRoutedPacket(MessageRouteEntry& route, const u8 * packet, u32 packetLen) const = 0;

    /**
     * Called by derived classes when they receive a packet over their
     * chosen transport mechanism.  This results in a callback to the
     * messenger client.
     */
    void HandleReceivedPacket(const u8 * packet, u32 packetLen);

    /**
     * If the above function can't handle it for some reason it will call this function
     * so derived class can do something with it e.g. queue it for later processing.
     */
    virtual void HandleUnhandledReceivedSerialisedData(MessagingEntity& fromEntity, MessagingEntity& toEntity, u32 serialisationId, const u8 * serialisedData, u32 serialisedDataLen) = 0;

    // Receive callback for raw message receive.
    MessageRxRawInterface* m_messageRxRawInterface;

private:

    // Handle a message routing table message
    void HandleReceivedRoutingTableUpdate(MessagingRouteInd& msgRouteInd);

    // Routing table for sending messages
    mutable MessageRoutingTable m_routingTable;

};

}

#endif
