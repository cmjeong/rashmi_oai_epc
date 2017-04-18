///////////////////////////////////////////////////////////////////////////////
//
// ProtocolLayer.h
//
// Protocol layer base class to allow abstract handling of layers in a
// protocol stack.
//
// See also: ProtocolStack.h 
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ProtocolLayer_h_
#define __ProtocolLayer_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <system/TimerInterface.h>
#include <system/ManagedObject.h>
#include <comms/PDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef enum PduDirectionTag
{
    PDU_RECEIVED_FROM_HIGHER_LAYER,
    PDU_RECEIVED_FROM_LOWER_LAYER
} PduDirection;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * LME PDU for sending to a protocol layer to control its admin state.
 */
class LmeSetAdminStateReqPdu : public threeway::PDU
{
public:
    LmeSetAdminStateReqPdu(ManagedObject::AdminState adminState) :
        m_adminState(adminState) {}
    virtual ~LmeSetAdminStateReqPdu() {}

    ManagedObject::AdminState m_adminState;
};

/**
 * LME PDU for sending from a protocol layer to report its operational state.
 */
class LmeOpStateInformIndPdu : public threeway::PDU
{
public:
    LmeOpStateInformIndPdu(ManagedObject::OpState opState) :
        m_opState(opState),
        m_additionalInfoVal(0) {}
    LmeOpStateInformIndPdu(ManagedObject::OpState opState, u32 additionInfoVal, const char * additionalInfo) :
        m_opState(opState),
        m_additionalInfoVal(additionInfoVal),
        m_additionalInfo(additionalInfo) {}
    virtual ~LmeOpStateInformIndPdu() {}

    ManagedObject::OpState m_opState;
    u32 m_additionalInfoVal;
    std::string m_additionalInfo;
};

/**
 * Interface for receiving LME PDUs from the protocol layer.
 */
class LayerManagementEntity
{
public:
    virtual ~LayerManagementEntity() {};

    /**
     * Handle a LME PDU from the protocol layer.
     *
     * \param passThrough Used by client to disambiguate different protocol layers.
     *                    Is set when registering LME.
     */
    virtual void HandleProtocolLayerLmePdu(u32 passThrough, shared_ptr<PDU> lmePdu) = 0;
};

class ProtocolLayer : public TimerNotifyInterface
{
public:
    /**
     * Construction / destruction.
     */
    ProtocolLayer();
    ProtocolLayer(const char * layerName);
    virtual ~ProtocolLayer();
 
    /**
     * Set/get the name of the layer for debug.
     */
    virtual void SetLayerName(const char * layerName);
    const char * GetLayerName() const;
    
    /**
     * Setters and getters for layer above, layer below and LME.
     */
    void SetHigherLayer(shared_ptr<ProtocolLayer> layer);
    void RemoveHigherLayer();
    shared_ptr<ProtocolLayer> GetHigherLayer() const;
    
    void SetLowerLayer(shared_ptr<ProtocolLayer> layer);
    void RemoveLowerLayer();
    shared_ptr<ProtocolLayer> GetLowerLayer() const;

    void SetLME(LayerManagementEntity* lme, u32 passThrough);

    /**
     * Set/get conditional tracing enabled/disabled.
     */
    void SetLayerTraceEnabled(bool enabled);
    bool IsLayerTraceEnabled() const { return m_conditionalTraceEnabled; };
    
    /**
     * Receive packet from the layer above.
     */
    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu) = 0;

    /**
     * Receive packet from the layer below.
     */
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu) = 0;
 
    /**
     * Receive packet from layer management entity.
     * Not pure virtual as often not required.  Default implementation
     * just outputs an 'unhandled message' warning.
     */
    virtual void ReceiveFromLME(shared_ptr<PDU> pdu);
 
    /**
     * Implement TimerNotifyInterface pure virtual.
     * 
     * Handle timer expiry.  Does nothing but show a warning
     * about unhandled timer.  Override to really handle timers.
     * 
     * \param expiredTimer
     */
    virtual void NotifyTimerExpiry(TimerHandle expiredTimer);

    /**
     * Get as string for debug.
     */
    virtual std::string ToString() const;
    
protected:
    /**
     * Send packets up/down the stack.
     */
    virtual bool SendToHigherLayer(shared_ptr<PDU> pdu) const;
    virtual bool SendToLowerLayer(shared_ptr<PDU> pdu) const;

    /**
     * Send packets to LME.
     */
    void SendToLME(shared_ptr<PDU> pdu) const;
    
    /**
     * Send packet in opposite direction to the layer indicated by
     * 'direction'.  I.e. if direction says 'received from lower layer'
     * then send this PDU to the higher layer and v.v.
     */
    bool SendOn(shared_ptr<PDU> pdu, PduDirection direction) const;
    
    /**
     * Send packet back to layer that 'direction' indicates original
     * PDU was from.  I.e. if direction says 'received from lower layer'
     * then send this PDU to the lower layer and v.v.
     */
    bool SendResponse(shared_ptr<PDU> pdu, PduDirection direction) const;
    
private:
    std::string                 m_layerName;
    shared_ptr<ProtocolLayer>   m_lowerLayer;
    shared_ptr<ProtocolLayer>   m_higherLayer;
    LayerManagementEntity*      m_lme;
    u32                         m_lmePassThrough;

    // Is conditional tracing enabled for this layer?
    bool                        m_conditionalTraceEnabled;

};

}

#endif
