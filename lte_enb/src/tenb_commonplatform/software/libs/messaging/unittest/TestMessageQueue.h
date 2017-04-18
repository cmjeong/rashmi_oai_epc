///////////////////////////////////////////////////////////////////////////////
//
// TestMessageQueue.h
//
// Simple message queue for to support unit tests.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TestMessageQueue_h_
#define __TestMessageQueue_h_


///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <messaging/transport/ApplicationWithMessaging.h>
#include <messaging/transport/MessagingEntity.h>
#include <messaging/transport/MessageSerialisedData.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class TestMessageQueue : public threeway::SendMessageInterface
{
public:
    TestMessageQueue();
    ~TestMessageQueue();

    /**
     * Implement SendMessageInterface.
     *
     * This can  be used instead of the ApplicationWithMessaging::SendMessage().
     * It simply puts the message on the internal queue, so that the unit test
     * can pull messages off the queue and validate their contents.
     *
     * \param messageToSend     A serialisable object to be serialised and sent.
     * \param destinationEntity Destination messaging entity.
     * \param sourceEntity      The entity this message should be sent "from", used when an app
     *                          registers multiple entities.  Default value means it will be sent
     *                          from the last registered entity.
     * \return                  true on successful send of message, false otherwise.
     */
    bool SendMessage(const threeway::Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity = ENTITY_INVALID) const;

    /**
     * Ensure the message queue is ready for the next test.
     */
    void ResetQueue(void);

    /**
     * Return the number of messages in the queue
     */
    int NumMessagesOnQueue(void) { return m_messageQueue.size(); };

    /**
     * Get a message from the message queue.
     *
     * \return Shared pointer to the next message on the queue, NULL otherwise.
     */
    boost::shared_ptr<threeway::MessageSerialisedData> GetNextMessage();

    /**
     * Serialises a message
     * @param fromEntity
     * @param toEntity
     * @param message
     * @return
     */
    static shared_ptr<threeway::MessageSerialisedData> MakeSerialisedData(MessagingEntity fromEntity, MessagingEntity toEntity, threeway::Serialisable& message)
    {
        u8 serialisedData[4096];
        s32 len = message.Serialise(serialisedData, sizeof(serialisedData));
        shared_ptr<threeway::MessageSerialisedData> serialisedDataPtr(new threeway::MessageSerialisedData(fromEntity, toEntity, message.GetSerialisationId(), serialisedData, len));;
        return serialisedDataPtr;
    }

private:

    // Note: for some reason the SendMessageInterface::SendMessage is defined as a const method,
    //       so we need to 'mutable' stuff here.

    // Message queue.
    typedef std::queue< boost::shared_ptr<threeway::MessageSerialisedData> > MessageQueue;
    mutable MessageQueue m_messageQueue;

    // Storage for building serialised data
    mutable u8 m_serialData[4096];

};


#endif
