///////////////////////////////////////////////////////////////////////////////
//
// MibSubscribeAttributesCnf.h
//
// Message for subscribing to oam MIB param(s).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSubscribeAttributesCnf_h_
#define __MibSubscribeAttributesCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibSubscribeAttributesCnf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MibSubscribeAttributesCnf(u32 subscriptionId);
    MibSubscribeAttributesCnf();
    virtual ~MibSubscribeAttributesCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF; };
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
