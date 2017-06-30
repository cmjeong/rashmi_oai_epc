///////////////////////////////////////////////////////////////////////////////
//
// OamActionCnf.h
//
// Message for serialising/deserialising an OAM action cnf.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OamActionCnf_h_
#define __OamActionCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <messaging/transport/MessagingEntity.h>
#include <system/OamAction.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class OamActionCnf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    OamActionCnf(MessagingEntity entity, OamAction action, u32 param) : m_entity(entity), m_action(action), m_val(param) {}
    OamActionCnf() : m_entity(ENTITY_INVALID), m_action(OAM_ACTION_NOACTION), m_val(0) {}
    virtual ~OamActionCnf() {}

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_OAM_ACTION_CNF; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

    /**
     * Accessors.
     */
    MessagingEntity GetEntity() const { return m_entity; }
    OamAction GetAction() const { return m_action; }
    u32 GetValue() const { return m_val; }

protected:

    // The entity to respond to.
    MessagingEntity m_entity;
    OamAction m_action;
    u32 m_val;
};

typedef shared_ptr<OamActionCnf> OamActionCnfPtr;

#endif // __OamActionCnf_h_
