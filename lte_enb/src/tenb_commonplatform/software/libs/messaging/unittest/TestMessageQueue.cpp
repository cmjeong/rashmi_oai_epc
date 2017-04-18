///////////////////////////////////////////////////////////////////////////////
//
// TestMessageQueue.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TestMessageQueue.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
TestMessageQueue::TestMessageQueue()
{
    ENTER();

    EXIT();
}

TestMessageQueue::~TestMessageQueue()
{
    ENTER();

    EXIT();
}

bool TestMessageQueue::SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity) const
{
    ENTER();

    // Serialise the data so that we can test that part of the message class works, plus we get to
    // store the source+destination that the unit test can then check.

    u32 serialiseDataLen = messageToSend.Serialise(m_serialData, sizeof(m_serialData));
    if (serialiseDataLen < 0)
    {
        RSYS_ASSERT_PRINTF(false, "TestMessageQueue: Failed to serialise message.");
        RETURN(false);
    }

    RSYS_ASSERT(serialiseDataLen <= sizeof(m_serialData));

    // And now build the MessageSerialisedData
    shared_ptr<MessageSerialisedData> messageSerialisedData(new MessageSerialisedData(sourceEntity, destinationEntity,
            messageToSend.GetSerialisationId(), m_serialData, serialiseDataLen));

    m_messageQueue.push(messageSerialisedData);

    RETURN(true);
}

void TestMessageQueue::ResetQueue(void)
{
    while (!m_messageQueue.empty())
    {
        m_messageQueue.pop();
    }
}

shared_ptr<threeway::MessageSerialisedData> TestMessageQueue::GetNextMessage()
{
    shared_ptr<MessageSerialisedData> dequeuedMessage;

    if(!m_messageQueue.empty())
    {
        // Queue is not empty so grab the message off the front.
        dequeuedMessage = m_messageQueue.front();
        // Then remove it from the queue.
        m_messageQueue.pop();
    }

    return dequeuedMessage;
}

