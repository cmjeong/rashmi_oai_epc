///////////////////////////////////////////////////////////////////////////////
//
// MibValidateAttributesCnf.h
//
// Message sent by MIB in response to MibValidateAttributesReq containing
// validation failures (if any).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibValidateAttributesCnf_h_
#define __MibValidateAttributesCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mib-common/MibAttrValidationFailure.h"
#include "mib-common/MibDN.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibValidateAttributesCnf : public threeway::Serialisable
{
public:
    typedef std::map<MibDN, MibAttrValidationFailures> MibAttrValidationFailuresByDn;

    /**
     * Constructor.
     * \dn          First MO to supply failures for.
     * \failures    Attribute validation failures.
     */
    MibValidateAttributesCnf(const MibDN& dn, const MibAttrValidationFailures& failures);

    /**
     * Default constructor for deserialisation.
     */
    MibValidateAttributesCnf() {};

    /**
     * Destructor.
     */
    virtual ~MibValidateAttributesCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_VALIDATE_ATTRIBUTES_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Add failures for additional (different) DNs.
     */
    void AddFailures(const MibDN& dn, const MibAttrValidationFailures& failures);

    /**
     * Get failures.
     */
    const MibAttrValidationFailuresByDn& GetFailures() const { return m_failures; }

    /**
     * Convenience function to check for all clear.
     */
    bool AllAttributesValidateOk() const { return m_failures.size() == 0; }

private:

    MibAttrValidationFailuresByDn m_failures;
};

#endif
