///////////////////////////////////////////////////////////////////////////////
//
// ValidatorString.h
//
// String value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorString_h_
#define __ValidatorString_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibDN.h>
#include "ValidationFailureDescriptor.h"
#include "string.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorString
{
public:
    ValidatorString();
    virtual ~ValidatorString();

    /**
     * Validate a string.
     *
     * \param value     The value to validate.
     * \param minLength The minimum length allowed.
     * \param maxLength The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);
    virtual bool ValidateString(MibDN Dn, const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);
    virtual bool ValidateString(MibDN Dn, const std::string& value, u32 minLength, u32 maxLength, const char* allowedValues[], u32 length, ValidationFailureDescriptor& failureDescriptor);
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, const char* allowedValues[], u32 length, ValidationFailureDescriptor& failureDescriptor);



};

#endif
