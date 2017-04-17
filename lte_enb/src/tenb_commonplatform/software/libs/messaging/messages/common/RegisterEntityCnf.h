///////////////////////////////////////////////////////////////////////////////
//
// RegisterEntityCnf.h
//
// Message for registering an entity with a post office application that can
// keep track of entities and distribute configuration to them.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RegisterEntityCnf_h_
#define __RegisterEntityCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "RegisterEntity.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class RegisterEntityCnf : public threeway::Serialisable
{
public:
    RegisterEntityCnf(MessagingEntities entities) : m_entities(entities) {};
    RegisterEntityCnf(MessagingEntity entity) { m_entities.push_back(entity); };
    RegisterEntityCnf() {};
    virtual ~RegisterEntityCnf() {};

    // Implement Serialisable

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REGISTER_ENTITY_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    MessagingEntity GetEntity() const { return m_entities[0]; }

    MessagingEntities m_entities;
};

#endif
