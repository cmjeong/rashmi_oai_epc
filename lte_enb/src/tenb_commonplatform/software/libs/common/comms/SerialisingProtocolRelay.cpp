///////////////////////////////////////////////////////////////////////////////
//
// SerialisingProtocolRelay.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/Exception.h>
#include <comms/ProtocolStack.h>
#include <comms/PDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisingProtocolRelay.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// ProtocolLayerDriver Class Functions
///////////////////////////////////////////////////////////////////////////////

ProtocolLayerDriver::ProtocolLayerDriver(SerialisingProtocolRelay& relay, RelayStackIndex stackIndex) :
    ProtocolLayer("Protocol Layer Driver"),
    m_relay(relay),
    m_stackIndex(stackIndex)
{
    ENTER();
    EXIT();
}

ProtocolLayerDriver::~ProtocolLayerDriver()
{
    ENTER();
    EXIT();
}
    
void ProtocolLayerDriver::ReceiveFromHigherLayer(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // This will be from the relay, just send it on down the stack.
    if(!SendToLowerLayer(pdu))
    {
        TRACE("ProtocolLayerDriver: Failed to send PDU to lower layer", pdu->ToString().c_str());
    }
    EXIT();
}

void ProtocolLayerDriver::ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // Pass it on to our friend, the relay object.
    m_relay.ReceiveFromLowerLayer(pdu, m_stackIndex);
    
    EXIT();
}


///////////////////////////////////////////////////////////////////////////////
// SerialisingProtocolRelay Class Functions
///////////////////////////////////////////////////////////////////////////////

SerialisingProtocolRelay::SerialisingProtocolRelay(ProtocolStack& protocolStack1,
                                                   ProtocolStack& protocolStack2) :
    m_protocolStack1(protocolStack1),
    m_protocolStack2(protocolStack2)
{
    ENTER();
    
    // Create the driver layers.
    m_protocolStack1Driver.reset(new ProtocolLayerDriver(*this, RELAY_STACK_1));
    m_protocolStack2Driver.reset(new ProtocolLayerDriver(*this, RELAY_STACK_2));

    // Set name *after* creating the layers!
    SetLayerName("Serialising Protocol Relay");

    // Add our driver layers to the top of the two stacks.
    m_protocolStack1.AddLayer(m_protocolStack1Driver, ProtocolStack::TOP_OF_STACK);
    m_protocolStack2.AddLayer(m_protocolStack2Driver, ProtocolStack::TOP_OF_STACK);
    
    EXIT();
}

SerialisingProtocolRelay::~SerialisingProtocolRelay()
{
    ENTER();
    
    // Remove our driver layers from the top of the two stacks.
    m_protocolStack1.RemoveLayer(m_protocolStack1Driver);
    m_protocolStack2.RemoveLayer(m_protocolStack2Driver);
    
    EXIT();
}

void SerialisingProtocolRelay::SetLayerName(const char * layerName)
{
    ENTER();
    
    SerialisingProtocolLayer::SetLayerName(layerName);
    m_protocolStack1Driver->SetLayerName(layerName);
    m_protocolStack2Driver->SetLayerName(layerName);
    
    EXIT();
}

void SerialisingProtocolRelay::ReceiveFromLowerLayer(shared_ptr<PDU> pdu, RelayStackIndex stackIndex)
{
    ENTER();
    
    // We are going to use the source ID to store the stack index.
    // When ProcessPdu() gets called we can recover the stack index
    // and pass it on to the ProcessPdu() function that takes a stack index.
    u32 stackIndexU32 = (u32)stackIndex;
    pdu->SetSourceId(stackIndexU32);

    // Now do the normal receive function i.e. stick it on the queue.
    SerialisingProtocolLayer::ReceiveFromLowerLayer(pdu);
    
    EXIT();
}

void SerialisingProtocolRelay::ProcessPdu(shared_ptr<PDU> pdu, RelayStackIndex stackIndex)
{
    ENTER();

    // Default behaviour is to just pass this PDU on to the opposite stack.
    if(stackIndex == RELAY_STACK_1)
    {
        SendToLowerLayer(pdu, RELAY_STACK_2);
    }
    else
    {
        SendToLowerLayer(pdu, RELAY_STACK_1);
    }
    
    EXIT();
}

void SerialisingProtocolRelay::ProcessTimerExpiry(TimerHandle expiredTimer)
{
    ENTER();
    
    // Override this function if you want to handle timers.
    
    EXIT();
}

void SerialisingProtocolRelay::SendToLowerLayer(shared_ptr<PDU> pdu, RelayStackIndex stackIndex)
{
    ENTER();
    
    if(stackIndex == RELAY_STACK_1)
    {
        // Send to stack 1.
        m_protocolStack1Driver->ReceiveFromHigherLayer(pdu);
    }
    else
    {
        // Send to stack 2.
        m_protocolStack2Driver->ReceiveFromHigherLayer(pdu);
    }
    
    EXIT();
}

bool SerialisingProtocolRelay::SendToHigherLayer(shared_ptr<PDU> pdu) const
{
    TRACE("SerialisingProtocolRelay::SendToHigherLayer: Should not be called!  PDU", pdu->ToString().c_str());
    return false;
}

bool SerialisingProtocolRelay::SendToLowerLayer(shared_ptr<PDU> pdu) const
{
    TRACE("SerialisingProtocolRelay::SendToLowerLayer: Should not be called!  PDU", pdu->ToString().c_str());
    return false;
}

void SerialisingProtocolRelay::ProcessPdu(shared_ptr<PDU> pdu, PduDirection direction)
{
    ENTER();
    
    // Recover the stack index from the PDU.
    u32 stackIndex = pdu->GetSourceId();
    
    // Now call the stack index version of ProcessPdu(). 
    switch(stackIndex)
    {
        case 1:
            ProcessPdu(pdu, RELAY_STACK_1);
            break;
        case 2:
            ProcessPdu(pdu, RELAY_STACK_2);
            break;
        default:
            throw Exception(__FILE__, __LINE__, 
                                "SerialisingProtocolRelay(%s): PDU has invalid stack index (%" PRIu32 ")",
                                GetLayerName(), (u32)stackIndex);
            break;
    }

    EXIT();
}


}
