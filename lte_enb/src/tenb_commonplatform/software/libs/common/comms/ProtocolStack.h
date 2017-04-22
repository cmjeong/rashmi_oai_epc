///////////////////////////////////////////////////////////////////////////////
//
// ProtocolStack.h
//
// Manages a set of linked ProtocolLayer's.
//
// See also: ProtocolLayer.h 
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ProtocolStack_h_
#define __ProtocolStack_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <system/TimerInterface.h>
#include <comms/ProtocolLayer.h>

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

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ProtocolStack
{
public:
    enum Placement
    {
        TOP_OF_STACK,  
        ABOVE_LAYER,
        BELOW_LAYER,
        BOTTOM_OF_STACK
    };

    /**
     * Construction / destruction.
     * Virtual destructor as can easily imagine stacks derived from this.
     */
    ProtocolStack();
    virtual ~ProtocolStack();
    
    /**
     * Set/get the stack name.
     */
    void SetStackName(const char * stackName);
    const char * GetStackName() const;
    
    /**
     * Stick a PDU into the top of the stack.
     */
    bool Transmit(shared_ptr<PDU> pdu) const;
    
    /**
     * Stick a PDU into the bottom of the stack.
     */
    bool Receive(shared_ptr<PDU> pdu) const;

    /**
     * Add a new layer to the stack, wiring it up to the
     * existing layers depending on the 'placement' parameter. 
     */
    // For first layer or where placement is TOP/BOTTOM.
    void AddLayer(shared_ptr<ProtocolLayer> layer,
                  Placement placement);
    // Version for when we want to place relative to another layer.
    void AddLayer(shared_ptr<ProtocolLayer> layer,
                  Placement placement, 
                  shared_ptr<ProtocolLayer> existingLayer);
    
    /**
     * Remove a layer from the stack and wire up the existing
     * layers to fill the gap accordingly.
     */
    void RemoveLayer(shared_ptr<ProtocolLayer> layer);

    /**
     * Get as string for debug.
     */
    virtual std::string ToString() const;

private:
    std::string                 m_stackName;
    shared_ptr<ProtocolLayer>   m_highestLayer;
    shared_ptr<ProtocolLayer>   m_lowestLayer;

};

}

#endif
