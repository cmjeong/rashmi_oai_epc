//
// IkeTunnelDisconnectInd.h
//
// The definition of a message sent back to a tunnel requester
//  when the IPsec tunnel has terminated.
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IkeTunnelDisconnectInd_h_
#define __IkeTunnelDisconnectInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class IkeTunnelDisconnectInd : public threeway::Serialisable
{
public:
    IkeTunnelDisconnectInd(u32 id) : m_id(id) {}
    IkeTunnelDisconnectInd() : m_id(0) {}
    virtual ~IkeTunnelDisconnectInd() {}

    // Implement Serialisable
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IKE_TUNNEL_DISCONNECT_IND; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    u32 GetId() const { return m_id; }

    virtual std::string ToString() const;

private:
    u32 m_id;
};

}; // namespace

#endif
