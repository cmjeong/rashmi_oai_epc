///////////////////////////////////////////////////////////////////////////////
//
// ProtoProfLayer.h
//
// Protocol layer that generates Proto Prof trace for PDUs passing through.
// This is for use within applications whose output will be parsed by the
// ProtoProf rather than as part of the ProtoProf application itself.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ProtoProfLayer_h_
#define __ProtoProfLayer_h_

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
// Classes
///////////////////////////////////////////////////////////////////////////////

// The main class.
class ProtoProfLayer : public ProtocolLayer
{
public:
    /**
     * Construction / destruction.
     */
    ProtoProfLayer();
    virtual ~ProtoProfLayer();
 
    /**
     * Implement ProtocolLayer pure virtual.
     * Receive packet from the layer above.
     */
    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu);

    /**
     * Implement ProtocolLayer pure virtual.
     * Receive packet from the layer below.
     */
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu);
    
private:
    /**
     * Get the names of the layers above and below or use default
     * strings if the layers don't exist.
     */
    void GetLayerNames(std::string& lowerLayerName, std::string& higherLayerName);
    
};

}

#endif
