///////////////////////////////////////////////////////////////////////////////
//
// MibAttribute.h
//
// MIB object attribute.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttribute_h_
#define __MibAttribute_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Trace.h>
#include <mib-common/MibAttributeDescriptors.h>
#include <mib-common/ValidatorU32.h>
#include <mib-common/ValidatorS32.h>
#include <mib-common/ValidatorString.h>
#include <mib-common/MibAttrValidationFailure.h>
#include <mib-common/MibAttributeValues.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibAttribute
{
public:
    static bool ValidateValue(MibDN Dn, MibAttributeId id, boost::shared_ptr<MibAttributeValue> value, MibAttrValidationFailure& failureDescriptor);

    /**
     * Default constructor.
     */
    MibAttribute(MibAttributeId mibAttributeId, boost::shared_ptr<MibAttributeValue> attributeValue);

    /**
     * Destructor.
     */
    ~MibAttribute();

    /**
     * Getters
     */
    MibAttributeId GetMibAttributeId() const { return m_mibAttributeId; }

    /**
     * Get value as a type agnostic object.
     */
    boost::shared_ptr<MibAttributeValue> GetValue() const { return m_value; };

    /**
     * Populate each of the supplied value objects with the value of this attribute.
     */
    void PopulateWithValue(MibAttributeValues& mibAttributeValues) const;

    /**
     * Compare type and value.
     */
    bool IsValueEqual(const MibAttribute& rhs) const;

    /**
     * Get as string for trace/debug.
     */
    std::string ToString() const;

protected:

    /**
     * What attribute are we then?
     * Derived classes store the value in whatever form they need to.
     */
    const MibAttributeId m_mibAttributeId;

    /**
     * And what value?
     */
    boost::shared_ptr<MibAttributeValue> m_value;

};

#endif
