///////////////////////////////////////////////////////////////////////////////
//
// SerialisingProtocolRelay.h
//
// Relay layer for connecting two ProtocolStack objects.
//
// Default functionality is to place PDUs from either stack on the internal
// queue and then pop them off in the main thread loop before where they
// will end up being pushed down the opposite stack. I.e. it simply passes
// PDUs between the stacks via a queue that avoids any threading problems.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisingProtocolRelay_h_
#define __SerialisingProtocolRelay_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <comms/ProtocolLayer.h>
#include <comms/SerialisingProtocolLayer.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class PDU;
class SerialisingProtocolRelay;
class ProtocolStack;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

// Identifiers for the two stacks.
typedef enum RelayStackIndexTag
{
    RELAY_STACK_1 = 1,
    RELAY_STACK_2 = 2
} RelayStackIndex;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * ProtocolLayerDriver
 * 
 * We need to connect the tops of the protocol stacks to something that looks
 * like a protocol layer.  We'll define a class and have two instances of it
 * within the relay class below, one for each of the two stacks connecting to
 * the relay.
 */
class ProtocolLayerDriver : public ProtocolLayer
{
public:
    ProtocolLayerDriver(SerialisingProtocolRelay& relay, RelayStackIndex stackIndex);
    virtual ~ProtocolLayerDriver();
    
    /**
     * Implement ProtocolLayer pure virtual.
     * Pass the PDU through to the layer below.
     */
    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu);

    /**
     * Implement ProtocolLayer pure virtual.
     * Receive a PDU and pass it on to the relay via the ReceiveFromLowerLayer
     * function, returning the stack index i.e. which stack is this layer
     * the top of.
     */
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu);
    
private:
    // Reference to the relay object.
    SerialisingProtocolRelay& m_relay;
    
    // Stack index - indicates which side of the relay this layer is connected to.
    RelayStackIndex m_stackIndex;
};


/**
 * SerialisingProtocolRelay
 * 
 * This class spans two protocol layers and is intended for use at the top
 * of two protocol stacks to relay messages between them.  The default
 * implementation does just that, derive from it to add some functionality
 * into the relay.
 */
class SerialisingProtocolRelay : public SerialisingProtocolLayer
{
    // Make the drivers our friends so that they, and only they,
    // can pass PDUs on to the relay. 
    friend class ProtocolLayerDriver;
    
public:
    /**
     * Construction / destruction.
     * Constructor will wire up the two protocol stacks to the two protocol
     * layer drivers which in turn will pass PDUs into this object.
     */
    SerialisingProtocolRelay(ProtocolStack& protocolStack1, ProtocolStack& protocolStack2);
    virtual ~SerialisingProtocolRelay();
 
    /**
     * Override this so we can update the names of the protocol layer drivers
     * that sit on top of each stack that the relay connects.
     */
    virtual void SetLayerName(const char * layerName);

    /**
     * Receive from one of the two stacks and put the message on this
     * object's queue. ProcessPdu() then removes this from the PDU and calls a
     * different ProcessPdu() with stack index.
     * Normally don't need to call this but can be useful to inject PDUs
     * directly rather than via layer/stack below.
     */
    void ReceiveFromLowerLayer(shared_ptr<PDU> pdu, RelayStackIndex stackIndex);

protected:
    /**
     * Default handling of PDUs is to pass them on to the other stack.
     * Override this to provide some real functionality.
     */
    virtual void ProcessPdu(shared_ptr<PDU> pdu, RelayStackIndex stackIndex);

    /**
     * Default handling of timer expiries is to ignore them.
     * Override this to provide some real functionality.
     */
    virtual void ProcessTimerExpiry(TimerHandle expiredTimer);

    /**
     * Send a PDU to one of the stacks.
     */
    virtual void SendToLowerLayer(shared_ptr<PDU> pdu, RelayStackIndex stackIndex);

private:
    /**
     * Override ProtocolLayer functions.
     * These functions are no longer required so make them private and do nothing.
     */
    bool SendToHigherLayer(shared_ptr<PDU> pdu) const;
    bool SendToLowerLayer(shared_ptr<PDU> pdu) const;

    /**
     * Implement SerialisingProtocolLayer pure virtual.
     * Receive PDUs and call ProcessPdu with stack index.
     * Derived classes should not override this function.
     */
    /* final */ void ProcessPdu(shared_ptr<PDU> pdu, PduDirection direction);
    
    // The two protocol stacks we are relaying across.
    ProtocolStack& m_protocolStack1;
    ProtocolStack& m_protocolStack2;

    // Drivers for the top two layers of the stacks we are relaying across.
    shared_ptr<ProtocolLayerDriver> m_protocolStack1Driver;
    shared_ptr<ProtocolLayerDriver> m_protocolStack2Driver;
    
};

}

#endif
