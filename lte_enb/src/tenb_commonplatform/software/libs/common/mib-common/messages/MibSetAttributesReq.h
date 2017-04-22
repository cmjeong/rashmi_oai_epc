///////////////////////////////////////////////////////////////////////////////
//
// MibSetAttributesReq.h
//
// Message for setting attributes on one or more (existing) MOs.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSetAttributesReq_h_
#define __MibSetAttributesReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributesMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibSetAttributesReq : public MibAttributesMessage
{
public:
    /**
     * Set attributes on one or more MOs.  Can add further attributes with
     * call to base class AddAttributes().
     *
     * \dn          First MO to set attributes on.
     * \attributes  Attributes to set on first MO.
     */
    MibSetAttributesReq(const MibDN& dn, const MibAttributeValues& attributes)
    {
        AddAttributes(dn, attributes);
    };

    /**
     * Default constructor to allow deserialisation.
     */
    MibSetAttributesReq() {};

    /**
     * Destructor.
     */
    virtual ~MibSetAttributesReq() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_SET_ATTRIBUTES_REQ; };

private:

};

#endif
