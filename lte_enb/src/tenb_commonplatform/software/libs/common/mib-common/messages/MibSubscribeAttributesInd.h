///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesInd.h
//
// Contains subscribed attribute id/value pairs by DN.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSubscribeAttributesInd_h_
#define __MibSubscribeAttributesInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributesMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibSubscribeAttributesInd : public MibAttributesMessage
{
public:
    /**
     * Choice of constructor.
     */
    MibSubscribeAttributesInd(u32 subscriptionId);
    MibSubscribeAttributesInd(u32 subscriptionId, const MibDN& dn, const MibAttributeValues& attributes);
    MibSubscribeAttributesInd(u32 subscriptionId, const MibAttributeValuesByDn & mibAttributeValuesByDn);

    /**
     * Default constructor to allow deserialisation.
     */
    MibSubscribeAttributesInd();

    /**
     * Destructor.
     */
    virtual ~MibSubscribeAttributesInd() {};

    /**
     * Override Serialisable virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND; };

    /**
     * Get subscription ID to allow clients to track their subscriptions.
     */
    u32 GetSubscriptionId() const { return m_subscriptionId; };

private:
    u32 m_subscriptionId;
};

#endif
