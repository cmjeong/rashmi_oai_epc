///////////////////////////////////////////////////////////////////////////////
//
// ValidatorMacAddress.h
//
// MAC address value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorMacAddress_h_
#define __ValidatorMacAddress_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorMacAddress : public ValidatorString
{
public:
    ValidatorMacAddress() {};
    virtual ~ValidatorMacAddress() {};

    /**
     * Validate a MAC address.  Does string length checks then further semantic
     * checks on the contents of the MAC address string.
     *
     * \param value             The MAC address to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
