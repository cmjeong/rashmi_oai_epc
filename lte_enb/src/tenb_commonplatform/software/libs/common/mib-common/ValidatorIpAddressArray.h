///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIpAddressArray.h
//
// IP address array value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorIpAddressArray_h_
#define __ValidatorIpAddressArray_h_

#include <boost/shared_ptr.hpp>
#include <system/Regex.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorStringArray.h"
#include "ValidatorIpAddress.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorIpAddressArray : public ValidatorStringArray
{
public:
    ValidatorIpAddressArray();
    virtual ~ValidatorIpAddressArray() {};

    virtual bool ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

private:
    ValidatorIpAddress m_validatorIpAddress;
};

#endif
