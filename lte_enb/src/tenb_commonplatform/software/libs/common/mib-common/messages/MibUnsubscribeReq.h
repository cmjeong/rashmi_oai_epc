///////////////////////////////////////////////////////////////////////////////
//
// MibUnsubscribeReq.h
//
// Message for subscribing to oam MIB param(s).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibUnsubscribeReq_h_
#define __MibUnsubscribeReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibUnsubscribeReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MibUnsubscribeReq(u32 subscriptionId);
    MibUnsubscribeReq();
    virtual ~MibUnsubscribeReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_UNSUBSCRIBE_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Accessors.
     */
    u32 GetSubscriptionId() const { return m_subscriptionId; }

private:
    u32 m_subscriptionId;
};

#endif
