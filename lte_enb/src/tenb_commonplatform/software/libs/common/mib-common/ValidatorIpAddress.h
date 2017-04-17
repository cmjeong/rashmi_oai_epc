///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIpAddress.h
//
// IPv4 address value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorIpAddress_h_
#define __ValidatorIpAddress_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorIpAddress : public ValidatorString
{
public:
    ValidatorIpAddress() {};
    virtual ~ValidatorIpAddress() {};

    /**
     * Validate an IP address.  Does string length checks then further semantic
     * checks on the contents of the IP address string.
     *
     * \param value             The IP address to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);
    bool ValidateIpv4(const std::string& value,ValidationFailureDescriptor& failureDescriptor);
    bool ValidateIpv6(const std::string& value,ValidationFailureDescriptor& failureDescriptor);
};

#endif
