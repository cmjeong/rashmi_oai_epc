///////////////////////////////////////////////////////////////////////////////
//
// TenpinDnsServerAddReq.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinDnsServerAddReq_h_
#define __TenpinDnsServerAddReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TenpinDnsServerAddReq : public threeway::Serialisable
{
public:
    TenpinDnsServerAddReq() :
        m_id(0),
        m_addr(0)
    {};
    virtual ~TenpinDnsServerAddReq() {};

    // Implement Serialisable

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_TENPIN_DNS_SERVER_ADD_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    // Rule Configuration - Basic Methods

    void SetId   (u32 id)   { m_id = id; }
    void SetAddr (u32 addr) { m_addr = addr; }

    u32 GetId   (void) const { return m_id; }
    u32 GetAddr (void) const { return m_addr; }

private:
    static const u32 serialisedLen = (2 * sizeof(u32));

    u32 m_id;
    u32 m_addr;
};

#endif
