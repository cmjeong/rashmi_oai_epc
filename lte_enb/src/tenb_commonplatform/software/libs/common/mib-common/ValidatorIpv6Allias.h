///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIpv6Allias.h
//
// Validate Ipv6Allias .
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorIpv6Allias_h_
#define __ValidatorIpv6Allias_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorIpv6Allias : public ValidatorString
{
public:
    ValidatorIpv6Allias() {};
    virtual ~ValidatorIpv6Allias() {};

    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
