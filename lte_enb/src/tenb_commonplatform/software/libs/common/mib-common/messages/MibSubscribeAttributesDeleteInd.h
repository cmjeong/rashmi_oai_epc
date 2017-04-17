///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesDeleteInd.h
//
// Contains subscribed attribute id/value pairs by DN that have been deleted
// from MIB.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSubscribeAttributesDeleteInd_h_
#define __MibSubscribeAttributesDeleteInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeIdsMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibSubscribeAttributesDeleteInd : public MibAttributeIdsMessage
{
public:
    /**
     * Default constructor.
     */
    MibSubscribeAttributesDeleteInd(u32 subscriptionId, const MibAttributeIdsByDn& deletedAttributeIdsByDn);

    /**
     * Default constructor to allow deserialisation.
     */
    MibSubscribeAttributesDeleteInd();

    /**
     * Destructor.
     */
    virtual ~MibSubscribeAttributesDeleteInd() {};

    /**
     * Override Serialisable virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_DELETE_IND; };

    /**
     * Get subscription ID to allow clients to track their subscriptions.
     */
    u32 GetSubscriptionId() const { return m_subscriptionId; };

private:
    u32 m_subscriptionId;
};

#endif
