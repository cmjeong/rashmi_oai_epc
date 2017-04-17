///////////////////////////////////////////////////////////////////////////////
//
// MibUnsubscribeCnf.h
//
// Message to unsubscribe from MIB attributes.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibUnsubscribeCnf_h_
#define __MibUnsubscribeCnf_h_

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

class MibUnsubscribeCnf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MibUnsubscribeCnf(u32 subscriptionId);
    MibUnsubscribeCnf();
    virtual ~MibUnsubscribeCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_UNSUBSCRIBE_CNF; };
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
