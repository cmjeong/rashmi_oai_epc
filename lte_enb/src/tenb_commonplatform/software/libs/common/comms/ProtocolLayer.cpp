///////////////////////////////////////////////////////////////////////////////
//
// ProtocolLayer.cpp
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
#include <system/Exception.h>
#include <comms/PDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ProtocolLayer.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ProtocolLayer::ProtocolLayer() :
    m_layerName("Protocol Layer"),
    m_conditionalTraceEnabled(true),
    m_lme(NULL),
    m_lmePassThrough(0)
{
}

ProtocolLayer::ProtocolLayer(const char * layerName) :
    m_layerName(layerName),
    m_conditionalTraceEnabled(true),
    m_lme(NULL),
    m_lmePassThrough(0)
{
}

ProtocolLayer::~ProtocolLayer()
{
}

void ProtocolLayer::SetLayerName(const char * layerName)
{
    m_layerName = layerName;
}

const char * ProtocolLayer::GetLayerName() const
{
    return(m_layerName.c_str());
}

void ProtocolLayer::SetHigherLayer(shared_ptr<ProtocolLayer> layer)
{
    m_higherLayer = layer;
}

void ProtocolLayer::RemoveHigherLayer()
{
    m_higherLayer.reset();
}

shared_ptr<ProtocolLayer> ProtocolLayer::GetHigherLayer() const
{
    return(m_higherLayer);
}

void ProtocolLayer::SetLowerLayer(shared_ptr<ProtocolLayer> layer)
{
    m_lowerLayer = layer;
}

void ProtocolLayer::RemoveLowerLayer()
{
    m_lowerLayer.reset();
}

shared_ptr<ProtocolLayer> ProtocolLayer::GetLowerLayer() const
{
    return(m_lowerLayer);
}

void ProtocolLayer::SetLME(LayerManagementEntity* lme, u32 passThrough)
{
    m_lme = lme;
    m_lmePassThrough = passThrough;
}

void ProtocolLayer::SetLayerTraceEnabled(bool enabled)
{
    m_conditionalTraceEnabled = enabled;
    
    TRACE_PRINTF("%s: Tracing is now %s", GetLayerName(), (enabled?"ENABLED":"DISABLED"));
}

void ProtocolLayer::ReceiveFromLME(shared_ptr<PDU> pdu)
{
    TRACE_PRINTF_LEV(TRACE_WARNING, "%s: LME message not handled: %s", GetLayerName(), pdu->ToString().c_str());
}

void ProtocolLayer::NotifyTimerExpiry(TimerHandle expiredTimer)
{
    TRACE_PRINTF_LEV(TRACE_WARNING, "%s: Timer expiry not handled, expiredTimer=%" PRIu32, GetLayerName(), (u32)expiredTimer);
}

bool ProtocolLayer::SendToHigherLayer(shared_ptr<PDU> pdu) const
{
    if(m_higherLayer)
    {
        m_higherLayer->ReceiveFromLowerLayer(pdu);
        return(true);
    }
    
    TRACE_PRINTF_LEV(TRACE_WARNING, "%s: No higher layer to send PDU to!", GetLayerName());
    
    return(false);
}

bool ProtocolLayer::SendToLowerLayer(shared_ptr<PDU> pdu) const
{
    if(m_lowerLayer)
    {
        m_lowerLayer->ReceiveFromHigherLayer(pdu);
        return(true);
    }
    
    TRACE_PRINTF_LEV(TRACE_WARNING, "%s: No lower layer to send PDU to!", GetLayerName());

    return(false);
}

void ProtocolLayer::SendToLME(shared_ptr<PDU> pdu) const
{
    RSYS_ASSERT_PRINTF(pdu != NULL, "%s", GetLayerName());

    if(m_lme != NULL)
    {
        m_lme->HandleProtocolLayerLmePdu(m_lmePassThrough, pdu);
    }
    else
    {
        TRACE_LEV(TRACE_WARNING, "No LME to send PDU to", pdu->ToString());
    }
}

bool ProtocolLayer::SendOn(shared_ptr<PDU> pdu, PduDirection direction) const
{
    if(direction == PDU_RECEIVED_FROM_HIGHER_LAYER)
    {
        return( SendToLowerLayer(pdu) );
    }
    
    return( SendToHigherLayer(pdu) );
}

bool ProtocolLayer::SendResponse(shared_ptr<PDU> pdu, PduDirection direction) const
{
    if(direction == PDU_RECEIVED_FROM_LOWER_LAYER)
    {
        return( SendToLowerLayer(pdu) );
    }
    
    return( SendToHigherLayer(pdu) );
}

std::string ProtocolLayer::ToString() const
{
    std::ostringstream stream;
    
    stream << m_layerName;

    if(m_higherLayer)
    {
        stream << ": higherLayer=" << m_higherLayer->GetLayerName();
    }
    else
    {
        stream << ": no higher layer";
    }

    if(m_lowerLayer)
    {
        stream << ", lowerLayer=" << m_lowerLayer->GetLayerName();
    }
    else
    {
        stream << ", no lower layer";
    }
    
    if(m_lme)
    {
        stream << ", has LME";
    }
    else
    {
        stream << ", no LME";
    }
    
    return (stream.str());
}

}
