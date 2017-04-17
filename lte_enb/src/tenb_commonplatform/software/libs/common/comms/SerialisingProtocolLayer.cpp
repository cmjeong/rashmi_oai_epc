///////////////////////////////////////////////////////////////////////////////
//
// SerialisingProtocolLayer.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <boost/shared_ptr.hpp>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisingProtocolLayer.h"
#include "PDU.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

class ProtocolLayerQueuedPdu : public Queueable
{
public:
    ProtocolLayerQueuedPdu(shared_ptr<PDU> pdu, PduDirection direction);
    virtual ~ProtocolLayerQueuedPdu();

    shared_ptr<PDU> m_pdu;
    PduDirection m_direction;
};

class ProtocolTimerExpiryQueuedMessage : public Queueable
{
public:
    ProtocolTimerExpiryQueuedMessage(TimerHandle expiredTimer);
    virtual ~ProtocolTimerExpiryQueuedMessage();

    TimerHandle m_expiredTimer;
};

class LmeQueuedPdu : public Queueable
{
public:
    LmeQueuedPdu(shared_ptr<PDU> pdu);
    virtual ~LmeQueuedPdu();

    shared_ptr<PDU> m_lmePdu;
};

///////////////////////////////////////////////////////////////////////////////
// ProtocolTimerExpiryQueuedMessage Class Functions
///////////////////////////////////////////////////////////////////////////////

ProtocolTimerExpiryQueuedMessage::ProtocolTimerExpiryQueuedMessage(TimerHandle expiredTimer) :
    m_expiredTimer(expiredTimer)
{
    ENTER();
    EXIT();
}

ProtocolTimerExpiryQueuedMessage::~ProtocolTimerExpiryQueuedMessage()
{
    ENTER();
    EXIT();
}

///////////////////////////////////////////////////////////////////////////////
// ProtocolLayerQueuedPdu Class Functions
///////////////////////////////////////////////////////////////////////////////

ProtocolLayerQueuedPdu::ProtocolLayerQueuedPdu(shared_ptr<PDU> pdu, PduDirection direction) :
    m_pdu(pdu),
    m_direction(direction)
{
    ENTER();
    EXIT();
}

ProtocolLayerQueuedPdu::~ProtocolLayerQueuedPdu()
{
    ENTER();
    EXIT();
}

///////////////////////////////////////////////////////////////////////////////
// LmeQueuedPdu Class Functions
///////////////////////////////////////////////////////////////////////////////

LmeQueuedPdu::LmeQueuedPdu(shared_ptr<PDU> pdu) :
    m_lmePdu(pdu)
{
    ENTER();
    EXIT();
}

LmeQueuedPdu::~LmeQueuedPdu()
{
    ENTER();
    
    // Explicitly not deleting pdu (it's done with shared pointers anyway).
    
    EXIT();
}

///////////////////////////////////////////////////////////////////////////////
// SerialisingProtocolLayer Class Functions
///////////////////////////////////////////////////////////////////////////////

SerialisingProtocolLayer::SerialisingProtocolLayer() :
    ProtocolLayer("Serialising Protocol Layer"),
    m_processingEvent(false)
{
    ENTER();
    EXIT();
}

SerialisingProtocolLayer::~SerialisingProtocolLayer()
{
    ENTER();
    EXIT();
}

void SerialisingProtocolLayer::ReceiveFromHigherLayer(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // If we are currently processing an event, enqueue this one and process later.
    
    if(m_processingEvent)
    {
        TRACE_PRINTF("%s: Enqueuing PDU from higher layer: %s", GetLayerName(), pdu->ToString().c_str());
        shared_ptr<ProtocolLayerQueuedPdu> queuedPdu(new ProtocolLayerQueuedPdu(pdu, PDU_RECEIVED_FROM_HIGHER_LAYER));
        m_queue.push(queuedPdu);
        RETURN_VOID();
    }

    m_processingEvent = true;
    ProcessPdu(pdu, PDU_RECEIVED_FROM_HIGHER_LAYER);
    m_processingEvent = false;

    ProcessQueue();
            
    EXIT();
}

void SerialisingProtocolLayer::ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // If we are currently processing an event, enqueue this one and process later.
    
    if(m_processingEvent)
    {
        TRACE_PRINTF("%s: Enqueuing PDU from lower layer: %s", GetLayerName(), pdu->ToString().c_str());
        shared_ptr<ProtocolLayerQueuedPdu> queuedPdu(new ProtocolLayerQueuedPdu(pdu, PDU_RECEIVED_FROM_LOWER_LAYER));
        m_queue.push(queuedPdu);
        RETURN_VOID();
    }

    m_processingEvent = true;
    ProcessPdu(pdu, PDU_RECEIVED_FROM_LOWER_LAYER);
    m_processingEvent = false;

    ProcessQueue();
            
    EXIT();
}

void SerialisingProtocolLayer::ReceiveFromLME(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // If we are currently processing an event, enqueue this one and process later.

    if(m_processingEvent)
    {
        TRACE_PRINTF("%s: Enqueuing PDU from LME: %s", GetLayerName(), pdu->ToString().c_str());
        shared_ptr<LmeQueuedPdu> queuedPdu(new LmeQueuedPdu(pdu));
        m_queue.push(queuedPdu);
        RETURN_VOID();
    }

    m_processingEvent = true;
    ProcessLmePdu(pdu);
    m_processingEvent = false;

    ProcessQueue();
    
    EXIT();
}

void SerialisingProtocolLayer::NotifyTimerExpiry(TimerHandle expiredTimer)
{
    ENTER();
    
    // If we are currently processing an event, enqueue this one and process later.

    if(m_processingEvent)
    {
        TRACE_PRINTF("%s: Enqueuing timer expiry: %"PRIu32, GetLayerName(), (u32)expiredTimer);
        shared_ptr<ProtocolTimerExpiryQueuedMessage> queuedTimerExpiry(new ProtocolTimerExpiryQueuedMessage(expiredTimer));
        m_queue.push(queuedTimerExpiry);
        RETURN_VOID();
    }

    m_processingEvent = true;
    ProcessTimerExpiry(expiredTimer);
    m_processingEvent = false;

    ProcessQueue();
    
    EXIT();
}

void SerialisingProtocolLayer::ProcessLmePdu(shared_ptr<PDU> pdu)
{
    ENTER();
    
    TRACE_PRINTF_LEV(TRACE_WARNING, "%s: Unhandled LME PDU: %s", GetLayerName(), pdu->ToString().c_str());
    
    EXIT();
}

bool SerialisingProtocolLayer::SendToHigherLayer(shared_ptr<PDU> pdu) const
{
    // We should only send to other layers when we have correctly indicated
    // we are processing an event, otherwise our re-entrancy checking won't
    // work.
    RSYS_ASSERT(m_processingEvent);
    return ProtocolLayer::SendToHigherLayer(pdu);
}

bool SerialisingProtocolLayer::SendToLowerLayer(shared_ptr<PDU> pdu) const
{
    // We should only send to other layers when we have correctly indicated
    // we are processing an event, otherwise our re-entrancy checking won't
    // work.
    RSYS_ASSERT(m_processingEvent);
    return ProtocolLayer::SendToLowerLayer(pdu);
}

void SerialisingProtocolLayer::ProcessQueue()
{
    ENTER();

    shared_ptr<Queueable> dequeuedMessage;

    m_processingEvent = true;
    while(!m_queue.empty())
    {

        dequeuedMessage = m_queue.front();
        m_queue.pop();
        if(dequeuedMessage != NULL)
        {
            // Check for normal inter-layer PDU.
            shared_ptr<ProtocolLayerQueuedPdu> queuedPdu = dynamic_pointer_cast<ProtocolLayerQueuedPdu>(dequeuedMessage);
            if(queuedPdu)
            {
                TRACE_PRINTF_LEV(TRACE_VERBOSE, "%s: Protocol layer PDU dequeued", GetLayerName());

                // Process dequeued PDU message.
                ProcessPdu(queuedPdu->m_pdu, queuedPdu->m_direction);
                continue;
            }

            // Check for timer expiry.
            shared_ptr<ProtocolTimerExpiryQueuedMessage> queuedTimerExpiry = dynamic_pointer_cast<ProtocolTimerExpiryQueuedMessage>(dequeuedMessage);
            if(queuedTimerExpiry)
            {
                TRACE_PRINTF_LEV(TRACE_VERBOSE, "%s: Protocol layer timer expiry dequeued", GetLayerName());

                // Process dequeued timer expiry message.
                ProcessTimerExpiry(queuedTimerExpiry->m_expiredTimer);
                continue;
            }

            // Check for LME PDU.
            shared_ptr<LmeQueuedPdu> queuedLmePdu = dynamic_pointer_cast<LmeQueuedPdu>(dequeuedMessage);
            if(queuedLmePdu)
            {
                TRACE_PRINTF_LEV(TRACE_VERBOSE, "%s: Protocol layer LME PDU dequeued", GetLayerName());

                // Process dequeued LME message.
                ProcessLmePdu(queuedLmePdu->m_lmePdu);
                continue;
            }

            RSYS_ASSERT_FAIL("Unknown queued message of type %s", typeid(dequeuedMessage).name());
        }
    }
    m_processingEvent = false;

    EXIT();
}

}
