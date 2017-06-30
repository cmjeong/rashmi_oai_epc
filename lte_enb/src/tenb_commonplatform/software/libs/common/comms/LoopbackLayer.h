///////////////////////////////////////////////////////////////////////////////
//
// LoopbackLayer.h
//
// Loopback layer to join the bottom of two protocol stacks.
// Simply passes PDUs between the lower edges of the two protocol stacks.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LoopbackLayer_h_
#define __LoopbackLayer_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <comms/ProtocolLayer.h>

using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class PDU;
class LoopbackLayer;
class ProtocolStack;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

// Identifiers for the two stacks.
typedef enum LoopbackStackIndexTag
{
    LOOPBACK_STACK_1 = 1,
    LOOPBACK_STACK_2 = 2
} LoopbackStackIndex;
    
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * LoopbackProtoLayerDriver
 * 
 * We need to connect the bottoms of the protocol stacks to something that looks
 * like a protocol layer.  We'll define a class and have two instances of it
 * within the loopback class below, one for each of the two stacks connecting to
 * the loopback layer.
 */
class LoopbackProtoLayerDriver : public ProtocolLayer
{
public:
    LoopbackProtoLayerDriver(LoopbackLayer& loopbackLayer, LoopbackStackIndex stackIndex);
    virtual ~LoopbackProtoLayerDriver();
    
    /**
     * Implement ProtocolLayer pure virtual.
     * Pass the PDU on to the loopback layer.
     */
    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu);

    /**
     * Implement ProtocolLayer pure virtual.
     * Receive from relay layer and send it on up the stack.
     */
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu);

private:
    // Reference to the relay object.
    LoopbackLayer& m_loopbackLayer;
    
    // Stack index - indicates which side of the relay this layer is connected to.
    LoopbackStackIndex m_stackIndex;
};


/**
 * LoopbackLayer
 * 
 * This class spans the bottoms of two protocol layers and is intended for use
 * at the bottom of two protocol stacks to loopback messages between them.
 */
class LoopbackLayer
{
    // Make the drivers our friends so that they, and only they,
    // can pass PDUs on to the loopback layer. 
    friend class LoopbackProtoLayerDriver;
    
public:
    /**
     * Construction / destruction.
     * Constructor will wire up the two protocol stacks to the two protocol
     * layer drivers which in turn will pass PDUs into this object.
     */
    LoopbackLayer(ProtocolStack& protocolStack1, ProtocolStack& protocolStack2);
    virtual ~LoopbackLayer();
 
    /**
     * Override this so we can update the names of the protocol layer drivers
     * that sit on top of each stack that the relay connects.
     */
    virtual void SetLayerName(const char * layerName);

protected:

private:
    /**
     * Receive from one of the two stacks and send on to the other stack.
     */
    void ReceiveFromHigherLayer(shared_ptr<PDU> pdu, LoopbackStackIndex stackIndex);

    // The two protocol stacks we are loopbacking across.
    ProtocolStack& m_protocolStack1;
    ProtocolStack& m_protocolStack2;

    // Drivers for the bottomw two layers of the stacks we are relaying across.
    shared_ptr<LoopbackProtoLayerDriver> m_protocolStack1Driver;
    shared_ptr<LoopbackProtoLayerDriver> m_protocolStack2Driver;
    
};

}

#endif
