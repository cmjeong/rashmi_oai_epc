///////////////////////////////////////////////////////////////////////////////
//
// OamActionReq.h
//
// Message for serialising/deserialising an OAM action req.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OamActionReq_h_
#define __OamActionReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/OamAction.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class OamActionReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    OamActionReq(OamAction action, u32 Data = 0) : m_action(action), m_data(Data) {}
    OamActionReq() : m_action(OAM_ACTION_NOACTION), m_data(0) {}
    virtual ~OamActionReq() {}

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_OAM_ACTION_REQ; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

    /**
     * Accessors.
     */
    OamAction GetAction() const { return m_action; }
    u32 GetData() const { return m_data; }

protected:

    // The entity to respond to.
    OamAction m_action;
    u32 m_data;
};

typedef shared_ptr<OamActionReq> OamActionReqPtr;

#endif // __OamActionReq_h_
