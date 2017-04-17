///////////////////////////////////////////////////////////////////////////////
//
// LoopbackLayer.cpp
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

#include "LoopbackLayer.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// ProtocolLayerDriver Class Functions
///////////////////////////////////////////////////////////////////////////////

LoopbackProtoLayerDriver::LoopbackProtoLayerDriver(LoopbackLayer& loopbackLayer, LoopbackStackIndex stackIndex) :
    ProtocolLayer("Loopback Layer Driver"),
    m_loopbackLayer(loopbackLayer),
    m_stackIndex(stackIndex)
{
    ENTER();
    EXIT();
}

LoopbackProtoLayerDriver::~LoopbackProtoLayerDriver()
{
    ENTER();
    EXIT();
}
    
void LoopbackProtoLayerDriver::ReceiveFromHigherLayer(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // Pass it on to our friend, the LoopbackLayer object for it to
    // send it up the other stack.
    m_loopbackLayer.ReceiveFromHigherLayer(pdu, m_stackIndex);
    
    EXIT();
}

void LoopbackProtoLayerDriver::ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
{
    ENTER();
    
    // Send it on up the stack.
    SendToHigherLayer(pdu);
    
    EXIT();
}


///////////////////////////////////////////////////////////////////////////////
// LoopbackLayer Class Functions
///////////////////////////////////////////////////////////////////////////////

LoopbackLayer::LoopbackLayer(ProtocolStack& protocolStack1,
                             ProtocolStack& protocolStack2) :
    m_protocolStack1(protocolStack1),
    m_protocolStack2(protocolStack2)
{
    ENTER();
    
    // Create the driver layers.
    m_protocolStack1Driver.reset(new LoopbackProtoLayerDriver(*this, LOOPBACK_STACK_1));
    m_protocolStack2Driver.reset(new LoopbackProtoLayerDriver(*this, LOOPBACK_STACK_2));

    // Add our driver layers to the bottoms of the two stacks.
    m_protocolStack1.AddLayer(m_protocolStack1Driver, ProtocolStack::BOTTOM_OF_STACK);
    m_protocolStack2.AddLayer(m_protocolStack2Driver, ProtocolStack::BOTTOM_OF_STACK);

    EXIT();
}

LoopbackLayer::~LoopbackLayer()
{
    ENTER();
    
    // Remove our driver layers from the top of the two stacks.
    m_protocolStack1.RemoveLayer(m_protocolStack1Driver);
    m_protocolStack2.RemoveLayer(m_protocolStack2Driver);
    
    EXIT();
}

void LoopbackLayer::SetLayerName(const char * layerName)
{
    ENTER();
    
    m_protocolStack1Driver->SetLayerName(layerName);
    m_protocolStack2Driver->SetLayerName(layerName);
    
    EXIT();
}

void LoopbackLayer::ReceiveFromHigherLayer(shared_ptr<PDU> pdu, LoopbackStackIndex stackIndex)
{
    ENTER();

    // Default behaviour is to just pass this PDU on to the opposite stack.
    if(stackIndex == LOOPBACK_STACK_1)
    {
        m_protocolStack2Driver->ReceiveFromLowerLayer(pdu);
    }
    else
    {
        m_protocolStack1Driver->ReceiveFromLowerLayer(pdu);
    }
    
    EXIT();
}

}
