///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelDeleteCnf.h
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IkeTunnelDeleteCnf_h_
#define __IkeTunnelDeleteCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class IkeTunnelDeleteCnf : public threeway::Serialisable
{
public:
    IkeTunnelDeleteCnf(u32 id) : m_id(id) {}
    IkeTunnelDeleteCnf() : m_id(0) {}
    virtual ~IkeTunnelDeleteCnf() {}

    // Implement Serialisable
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IKE_TUNNEL_DELETE_CNF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    u32 GetId() const { return m_id; }

    virtual std::string ToString() const;

private:
    u32 m_id;
};

}; // namespace

#endif
