///////////////////////////////////////////////////////////////////////////////
//
// MibValidateAttributesReq.h
//
// Message for validating attributes on one or more (existing) MOs.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibValidateAttributesReq_h_
#define __MibValidateAttributesReq_h_

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

class MibValidateAttributesReq : public MibAttributesMessage
{
public:
    /**
     * Set attributes on one or more MOs.  Can add further attributes with
     * call to base class AddAttributes().
     *
     * \dn          First MO to set attributes on.
     * \attributes  Attributes to set on first MO.
     */
    MibValidateAttributesReq(const MibDN& dn, const MibAttributeValues& attributes)
    {
        AddAttributes(dn, attributes);
    };

    /**
     * Default constructor to allow deserialisation.
     */
    MibValidateAttributesReq() {};

    /**
     * Destructor.
     */
    virtual ~MibValidateAttributesReq() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_VALIDATE_ATTRIBUTES_REQ; };

private:

};

#endif
