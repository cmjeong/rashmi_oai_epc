///////////////////////////////////////////////////////////////////////////////
//
// ProtoProfLayer.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <3waytypes.h>
#include <boost/shared_ptr.hpp>
#include <system/Trace.h>
#include <comms/PDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ProtoProfLayer.h"

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// ProtoProfLayer Class Functions
///////////////////////////////////////////////////////////////////////////////

ProtoProfLayer::ProtoProfLayer() :
    ProtocolLayer("Proto Prof Layer")
{
    ENTER();
    EXIT();
}

ProtoProfLayer::~ProtoProfLayer()
{
    ENTER();
    EXIT();
}

void ProtoProfLayer::ReceiveFromHigherLayer(shared_ptr<PDU> pdu)
{
    ENTER();

    // Get layer names and output PP string.
    string lowerLayerName;
    string higherLayerName;
    
    GetLayerNames(lowerLayerName, higherLayerName);
    
    MESSAGE_TAG_SHORT(higherLayerName.c_str(), lowerLayerName.c_str(), "-", "-", pdu->ToString().c_str());
    
    // Send it on.
    SendToLowerLayer(pdu);

    EXIT();
}

void ProtoProfLayer::ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
{
    ENTER();

    // Get layer names and output PP string.
    string lowerLayerName;
    string higherLayerName;
    
    GetLayerNames(lowerLayerName, higherLayerName);
    
    MESSAGE_TAG_SHORT(lowerLayerName.c_str(), higherLayerName.c_str(), "-", "-", pdu->ToString().c_str());

    // Send it on.
    SendToHigherLayer(pdu);

    EXIT();
}

void ProtoProfLayer::GetLayerNames(string& lowerLayerName, string& higherLayerName)
{
    ENTER();
    
    shared_ptr<ProtocolLayer> higherLayer = GetHigherLayer();
    shared_ptr<ProtocolLayer> lowerLayer = GetLowerLayer();
    higherLayerName = "top";
    lowerLayerName = "bot";
    
    if(higherLayer != NULL)
    {
        higherLayerName = higherLayer->GetLayerName();
    }

    if(lowerLayer != NULL)
    {
        lowerLayerName = lowerLayer->GetLayerName();
    }
    
    EXIT();
}

}
