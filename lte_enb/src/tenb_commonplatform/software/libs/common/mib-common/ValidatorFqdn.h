///////////////////////////////////////////////////////////////////////////////
//
// ValidatorFqdn.h
//
// FQDN value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorFqdn_h_
#define __ValidatorFqdn_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorFqdn : public ValidatorString
{
public:
    ValidatorFqdn() {};
    virtual ~ValidatorFqdn() {};

    /**
     * Validate an FQDN.  Does string semantic
     * checks on the contents of the URL string.
     *
     * \param value             The IP address to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
