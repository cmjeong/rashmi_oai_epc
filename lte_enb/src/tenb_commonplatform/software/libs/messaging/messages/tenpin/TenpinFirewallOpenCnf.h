///////////////////////////////////////////////////////////////////////////////
//
// TenpinFirewallOpenCnf.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinFirewallOpenCnf_h_
#define __TenpinFirewallOpenCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinFirewall.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TenpinFirewallOpenCnf : public threeway::Serialisable
{
public:
    TenpinFirewallOpenCnf() : m_token(0) {};
    TenpinFirewallOpenCnf(u32 token) : m_token(token) {};
    virtual ~TenpinFirewallOpenCnf() {};

    // Implement Serialisable

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_TENPIN_FIREWALL_OPEN_CNF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    // Handles

    FirewallHandles m_handles;

    void SetToken(u32 token) { m_token = token; }
    u32 GetToken(void) const { return m_token; }

private:
    u32 m_token;
};

#endif
