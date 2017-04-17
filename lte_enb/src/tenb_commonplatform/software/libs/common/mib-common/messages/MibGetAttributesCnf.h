///////////////////////////////////////////////////////////////////////////////
//
// MibGetAttributesCnf.h
//
// Message for setting attributes on one or more (existing) MOs.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibGetAttributesCnf_h_
#define __MibGetAttributesCnf_h_

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

class MibGetAttributesCnf : public MibAttributesMessage
{
public:
    /**
     * Set attributes on one or more MOs.  Can add further attributes with
     * call to base class AddAttributes().
     *
     * \dn          First MO to set attributes on.
     * \attributes  Attributes to set on first MO.
     */
    MibGetAttributesCnf(const MibDN& dn, const MibAttributeValues& attributes)
    {
        AddAttributes(dn, attributes);
    };

    /**
     * Default constructor to allow deserialisation.
     */
    MibGetAttributesCnf() {};

    /**
     * Destructor.
     */
    virtual ~MibGetAttributesCnf() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_GET_ATTRIBUTES_CNF; };

private:

};

#endif
