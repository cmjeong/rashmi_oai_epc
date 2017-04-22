///////////////////////////////////////////////////////////////////////////////
//
// ValidatorStringArray.h
//
// String value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorStringArray_h_
#define __ValidatorStringArray_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibDN.h>
#include "ValidationFailureDescriptor.h"
#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorStringArray
{
public:
    ValidatorStringArray();
    virtual ~ValidatorStringArray();

    /**
     * Validate a string array.
     *
     * \param value     The value to validate.
     * \param minLength The minimum length allowed per element.
     * \param maxLength The maximum length allowed per element.
     * \param maxInstances The maximum number of elements.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
    virtual bool ValidateStringArray(MibDN Dn,const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
    
private:
    ValidatorString m_validatorString;
};

#endif
