///////////////////////////////////////////////////////////////////////////////
//
// MibDeleteAttributesReq.h
//
// Message for deleting (unsetting) attributes in the MIB.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibDeleteAttributesReq_h_
#define __MibDeleteAttributesReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeIdsMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibDeleteAttributesReq : public MibAttributeIdsMessage
{
public:
    /**
     * Constructor.
     * Delete attributes on an MO..
     * Can add further attribute IDs with call to base class AddAttributeIds().
     *
     * \dn          First MO to get attributes from.
     * \attributes  Attribute IDs to get from first MO.
     */
    MibDeleteAttributesReq(const MibDN& dn, const MibAttributeIds& attributeIds)
    {
        AddAttributeIds(dn, attributeIds);
    }

    /**
     * Default constructor to allow deserialisation.
     */
    MibDeleteAttributesReq() {};

    /**
     * Destructor.
     */
    virtual ~MibDeleteAttributesReq() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_DELETE_ATTRIBUTES_REQ; };
};

#endif
