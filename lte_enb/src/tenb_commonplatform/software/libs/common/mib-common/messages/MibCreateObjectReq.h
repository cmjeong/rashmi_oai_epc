///////////////////////////////////////////////////////////////////////////////
//
// MibCreateObjectReq.h
//
// Message for creating a new object in the MIB.
// Currently this has to succeed.
// Core MIB will assert if creation is not possible - it's a coding bug!
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibCreateObjectReq_h_
#define __MibCreateObjectReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributesMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibCreateObjectReq : public MibAttributesMessage
{
public:
    /**
     * Create new MO without attributes.
     *
     * \parentDn    Parent to create MO on, will be ROOT for first MO.
     * \childRdn    RDN of child to create.
     */
    MibCreateObjectReq(const MibDN& parentDn, const MibRDN& childRdn);

    /**
     * Create new MO with attributes.
     *
     * \parentDn    Parent to create MO on, will be ROOT for first MO.
     * \childRdn    RDN of child to create.
     * \attributes  Attribute ID/Value pairs.
     */
    MibCreateObjectReq(const MibDN& parentDn, const MibRDN& childRdn, const MibAttributeValues& attributes);

    /**
     * Default constructor to allow deserialisation.
     */
    MibCreateObjectReq() {};

    /**
     * Destructor.
     */
    virtual ~MibCreateObjectReq() {};

    /**
     * Implement Serialisable virtuals.
     */
    u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_CREATE_OBJECT_REQ; };
    s32 Serialise(u8* data, u32 dataMaxBytes) const;
    bool DeSerialise(const u8* data, u32 dataLen);
    std::string ToString() const;

    /**
     * Accessors
     */
    MibDN GetParentDn() const;
    MibRDN GetChildRdn() const;
    const MibAttributeValues& GetChildMibAttributeValues() const;

private:


};

#endif
