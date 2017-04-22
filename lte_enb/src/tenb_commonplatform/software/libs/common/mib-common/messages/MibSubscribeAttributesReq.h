///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesReq.h
//
// Message for subscribing to MIB attributes.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSubscribeAttributesReq_h_
#define __MibSubscribeAttributesReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeIdsMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibSubscribeAttributesReq : public MibAttributeIdsMessage
{
public:
    /**
     * Constructor.
     * Subscribe to attributes on an MO.
     * Can add further attribute IDs with call to base class AddAttributeIds().
     *
     * \dn          First MO to get attributes from.
     * \attributes  Attribute IDs to get from first MO.
     */
    MibSubscribeAttributesReq(u32 subscriptionId);
    MibSubscribeAttributesReq(u32 subscriptionId, const MibDN& dn, const MibAttributeIds& attributeIds);

    /**
     * Default constructor to allow deserialisation.
     */
    MibSubscribeAttributesReq();

    /**
     * Destructor.
     */
    virtual ~MibSubscribeAttributesReq() {};

    /**
     * Override Serialisable virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_REQ; };

    /**
     * Accessors.
     */
    u32 GetSubscriptionId() const { return m_subscriptionId; }

private:
    u32 m_subscriptionId;
};

#endif
