///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSerialNumber.h
//
// SerialNumber value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorSerialNumber_h_
#define __ValidatorSerialNumber_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorSerialNumber : public ValidatorString
{
public:
    ValidatorSerialNumber() {};
    virtual ~ValidatorSerialNumber() {};

    /**
     * Validate a serial number.  Does string length checks then further semantic
     * checks on the contents of the serial number string.
     *
     * \param value     The serial number to validate.
     * \param minLength The minimum length allowed.
     * \param maxLength The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
