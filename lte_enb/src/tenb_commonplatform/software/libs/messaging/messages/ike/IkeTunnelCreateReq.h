///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelCreateReq.h
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IkeTunnelCreateReq_h_
#define __IkeTunnelCreateReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/Fqdn.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class IkeTunnelCreateReq : public threeway::Serialisable
{
public:
    IkeTunnelCreateReq( const threeway::Fqdn & destAddr) : m_destAddr(destAddr), m_authMethod("PKI"){}
    IkeTunnelCreateReq( const threeway::Fqdn & destAddr, const string & auth) : m_destAddr(destAddr), m_authMethod(auth){}
    IkeTunnelCreateReq() : m_destAddr() {}
    virtual ~IkeTunnelCreateReq() {}

    // Implement Serialisable
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IKE_TUNNEL_CREATE_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    threeway::Fqdn GetDestAddr() const { return m_destAddr; }
    string& GetAuthMethod() { return m_authMethod; }

    virtual std::string ToString() const;

private:
    threeway::Fqdn m_destAddr;
    string m_authMethod;
};

}; // namespace

#endif
