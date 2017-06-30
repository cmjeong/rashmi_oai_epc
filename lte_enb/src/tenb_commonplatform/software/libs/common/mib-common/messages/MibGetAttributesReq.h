///////////////////////////////////////////////////////////////////////////////
//
// MibGetAttributesReq.h
//
// Contains subscribed attribute id/value pairs by DN.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibGetAttributesReq_h_
#define __MibGetAttributesReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeIdsMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibGetAttributesReq : public MibAttributeIdsMessage
{
public:
    /**
     * Constructor.
     * Get attributes from one or more MOs.  Can add further attribute IDs with
     * call to base class AddAttributeIds().
     *
     * \dn          First MO to get attributes from.
     * \attributes  Attribute IDs to get from first MO.
     */
    MibGetAttributesReq(const MibDN& dn, const MibAttributeIds& attributeIds)
    {
        AddAttributeIds(dn, attributeIds);
    }

    /**
     * Default constructor to allow deserialisation.
     */
    MibGetAttributesReq() {};

    /**
     * Destructor.
     */
    virtual ~MibGetAttributesReq() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_GET_ATTRIBUTES_REQ; };

protected:

private:


};

#endif
