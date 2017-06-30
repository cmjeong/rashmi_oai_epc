///////////////////////////////////////////////////////////////////////////////
//
// ValidatorHexString.h
//
// HexString value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorHexString_h_
#define __ValidatorHexString_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorHexString : public ValidatorString
{
public:
    ValidatorHexString() {};
    virtual ~ValidatorHexString() {};

    /**
     * Validate a Hex string. Also does string length checks then further semantic
     * checks on the contents of the hex string.
     *
     * \param value     The hex string to validate.
     * \param minLength The minimum length allowed.
     * \param maxLength The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
