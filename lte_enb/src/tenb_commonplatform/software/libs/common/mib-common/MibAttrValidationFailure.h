///////////////////////////////////////////////////////////////////////////////
//
// MibAttrValidationFailure.h
//
// Describes the validation failure of a MIB attribute.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttrValidationFailure_h_
#define __MibAttrValidationFailure_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <MibAttributeId.h>
#include <mib-common/MibAttributeDescriptors.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidationFailureDescriptor.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class describing a single failure.
 */
class MibAttrValidationFailure : public ValidationFailureDescriptor
{
public:
    /**
     * Constructors.
     */
    MibAttrValidationFailure() : m_mibAttributeId(PARAM_ID_INVALID) {};
    MibAttrValidationFailure(MibAttributeId id) : m_mibAttributeId(id) {};
    MibAttrValidationFailure(MibAttributeId id, ValidationFailureDescriptor validationFailureDescriptor) :
        ValidationFailureDescriptor(validationFailureDescriptor),
        m_mibAttributeId(id) {};

    /**
     * Destructor.
     */
    virtual ~MibAttrValidationFailure() {};

    /**
     * Set/get attribute ID that this failure applies to.
     */
    void SetMibAttributeId(MibAttributeId mibAttributeId) { m_mibAttributeId = mibAttributeId; };
    MibAttributeId GetMibAttributeId() const { return m_mibAttributeId; };

    /**
     * Add ID to string provided by base class.
     */
    virtual std::string ToString() const
    {
        std::ostringstream stream;

        if(m_mibAttributeId != PARAM_ID_INVALID)
        {
            stream << getMibAttributeName(m_mibAttributeId) << ":";
        }

        stream << ValidationFailureDescriptor::ToString();

        return stream.str();
    };

private:

    MibAttributeId m_mibAttributeId;
};

/**
 * Class for a list of failures so we can provide a ToString().
 * NOTE: Don't add member vars to this as STL classes don't have virtual destructors.
 */
class MibAttrValidationFailures : public std::vector<MibAttrValidationFailure>, public threeway::Serialisable
{
public:
    MibAttrValidationFailures() {};
    virtual ~MibAttrValidationFailures() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTR_VALIDATION_FAILURES; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;
};


#endif
