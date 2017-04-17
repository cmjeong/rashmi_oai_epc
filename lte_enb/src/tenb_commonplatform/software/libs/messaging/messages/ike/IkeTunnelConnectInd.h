///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelConnectInd.h
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IkeTunnelConnectInd_h_
#define __IkeTunnelConnectInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <comms/IPv4Address.h>
#include <comms/IPAddress.h>
#include <system/Trace.h>
///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class IkeTunnelConnectInd : public threeway::Serialisable
{
public:
    IkeTunnelConnectInd(u32 id, IPAddress tunnelAddr) : m_id(id)
    { 
       m_tunnelAddr = tunnelAddr;
    }
    IkeTunnelConnectInd() : m_id(0)
    {
    }
    virtual ~IkeTunnelConnectInd() {}

    // Implement Serialisable
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IKE_TUNNEL_CONNECT_IND; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    u32                     GetId()         const { return m_id; }
    IPAddress   GetTunnelAddr() const { return m_tunnelAddr; }

    virtual std::string ToString() const;

private:
    u32                     m_id;
    IPAddress   m_tunnelAddr;
};

}; // namespace

#endif
