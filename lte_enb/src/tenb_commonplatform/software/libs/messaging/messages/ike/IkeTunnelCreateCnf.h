///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelCreateCnf.h
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IkeTunnelCreateCnf_h_
#define __IkeTunnelCreateCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include "comms/IPv4Address.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class IkeTunnelCreateCnf : public threeway::Serialisable
{
public:
    IkeTunnelCreateCnf(u32 id) : m_id(id) {}
    IkeTunnelCreateCnf() : m_id(0) {}
    virtual ~IkeTunnelCreateCnf() {}

    // Implement Serialisable
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IKE_TUNNEL_CREATE_CNF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    u32 GetId() const { return m_id; }

    virtual std::string ToString() const;

private:
    u32 m_id;
};

}; // namespace

#endif
