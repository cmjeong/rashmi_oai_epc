///////////////////////////////////////////////////////////////////////////////
//
// ProtocolStack.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <3waytypes.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ProtocolStack.h"
#include "ProtocolLayer.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ProtocolStack::ProtocolStack() :
    m_stackName("Protocol Stack")
{
    ENTER();
    EXIT();
}

ProtocolStack::~ProtocolStack()
{
    ENTER();
    EXIT();
}

void ProtocolStack::SetStackName(const char * stackName)
{
    ENTER();
    
    m_stackName = stackName;
    
    EXIT();
}

const char * ProtocolStack::GetStackName() const
{
    ENTER();
    RETURN(m_stackName.c_str());
}

bool ProtocolStack::Transmit(shared_ptr<PDU> pdu) const
{
    ENTER();
    
    if(m_highestLayer != NULL)
    {
        m_highestLayer->ReceiveFromHigherLayer(pdu);
        RETURN(true);
    }
    
    RETURN(false);
}

bool ProtocolStack::Receive(shared_ptr<PDU> pdu) const
{
    ENTER();
    
    if(m_lowestLayer != NULL)
    {
        m_lowestLayer->ReceiveFromLowerLayer(pdu);
        RETURN(true);
    }
    
    RETURN(false);
}

void ProtocolStack::AddLayer(shared_ptr<ProtocolLayer> layer,
                             Placement placement)
{
    ENTER();
    
    shared_ptr<ProtocolLayer> nullProtocolLayer;
    AddLayer(layer, placement, nullProtocolLayer);
    
    EXIT();
}

void ProtocolStack::AddLayer(shared_ptr<ProtocolLayer> layer,
                             Placement placement, 
                             shared_ptr<ProtocolLayer> existingLayer)
{
    ENTER();
    
    // Initialise the higher and lower protocol layers to NULL in the new
    // protocol layer.  They will be set at the point of insertion into the
    // stack.
    layer->RemoveLowerLayer();
    layer->RemoveHigherLayer();

    if(m_highestLayer != NULL)
    {
        // This is not the first layer so we need to work out where to place it.
        switch (placement)
        {
            case TOP_OF_STACK:
                // Place at the top of the stack.
                m_highestLayer->SetHigherLayer(layer);
                layer->SetLowerLayer(m_highestLayer);
                m_highestLayer = layer;
                break;
    
            case ABOVE_LAYER:
                {
                // Place the layer above an existing layer.
                shared_ptr<ProtocolLayer> previousHigherLayer;
    
                // Linking up the new layer above the existing layer
                previousHigherLayer = existingLayer->GetHigherLayer();
                layer->SetHigherLayer(previousHigherLayer);
                layer->SetLowerLayer(existingLayer);
                existingLayer->SetHigherLayer(layer);
    
                // Check if the existing layer was the highest layer.
                if (existingLayer == m_highestLayer)
                {
                    // If it was, make the new layer the highest layer.
                    m_highestLayer = layer;
                }
                else
                {
                    // Change the pointer of the existing layer's upper layer
                    // to point to the newly inserted layer.
                    previousHigherLayer->SetLowerLayer(layer);
                }
                }
                break;
    
            case BELOW_LAYER:
                {
                // Place the layer below the existing layer.
                shared_ptr<ProtocolLayer> previousLowerLayer;
    
                // Linking up the new layer below the existing layer.
                previousLowerLayer = existingLayer->GetLowerLayer();
                layer->SetHigherLayer(existingLayer);
                layer->SetLowerLayer(previousLowerLayer);
                existingLayer->SetLowerLayer(layer);
    
                // Check if the existing layer was the lowest layer.
                if(existingLayer == m_lowestLayer)
                {
                    // If it was, make the new layer the lowest layer.
                    m_lowestLayer = layer;
                }
                else
                {
                    // Change the pointer of the existing layer's lower layer
                    // to point to the newly inserted layer.
                    previousLowerLayer->SetHigherLayer(layer);
                }
                }
                break;
                
            case BOTTOM_OF_STACK:
                // Place at the bottom of the stack.
                m_lowestLayer->SetLowerLayer(layer);
                layer->SetHigherLayer(m_lowestLayer);
                m_lowestLayer = layer;
                break;
        }
    }
    else
    {
        // This is the first layer in the protocol stack.
        m_highestLayer = layer;
        m_lowestLayer = layer;
    }
    
    EXIT();
}

void ProtocolStack::RemoveLayer(shared_ptr<ProtocolLayer> layer)
{
    ENTER();
    
    // Check if the layer to be removed is the highest layer.
    if(layer == m_highestLayer)
    {
        // Yes it is, so set the removed layer's lower layer as the highest layer
        // in the protocol stack.
        m_highestLayer = layer->GetLowerLayer();

        // If this was not the only layer in the stack, set the
        // upper layer of this layer as NULL.
        if(m_highestLayer != NULL)
        {
            m_highestLayer->RemoveHigherLayer();
        }
    }
    else
    {
        // Not the highest layer.
        // Stitch the upper layer to lower layer link after the layer is removed.
        (layer->GetHigherLayer())->SetLowerLayer(layer->GetLowerLayer());
    }

    // Check if the layer to be removed is the lowest layer.
    if(layer == m_lowestLayer)
    {
        // Yes it is, so set the removed layer's upper layer as the lowest layer
        // in the protocol stack.
        m_lowestLayer = layer->GetHigherLayer();

        // If this was not the only layer in the stack, set the
        // lower layer of this layer as NULL.
        if(m_lowestLayer != NULL)
        {
            m_lowestLayer->RemoveLowerLayer();
        }
    }
    else
    {
        // Stitch the lower layer to upper layer link after the layer is removed.
        (layer->GetLowerLayer())->SetHigherLayer(layer->GetHigherLayer());
    }

    // Set the upper and lower layer pointers of the removed layer as NULL.
    // This is a safety measure.
    layer->RemoveLowerLayer();
    layer->RemoveHigherLayer();
    
    EXIT();
}

std::string ProtocolStack::ToString() const
{
    ENTER();
    
    std::ostringstream stream;
    
    stream << "ProtocolStack: " << m_stackName << std::endl;

    if(m_highestLayer != NULL)
    {
        shared_ptr<ProtocolLayer> layer = m_highestLayer;
        while(layer)
        {
            stream << "  " << layer->GetLayerName() << std::endl;
            layer = layer->GetLowerLayer();
        }
    }
    else
    {
        stream << "  No protocol layers present" << std::endl;
    }
    
    RETURN(stream.str());
}

}
