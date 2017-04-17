///////////////////////////////////////////////////////////////////////////////
//
// ValidatorCdmaUtraTddMode.h
//
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorCdmaUtraTddMode_h_
#define __ValidatorCdmaUtraTddMode_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorCdmaUtraTddMode : public ValidatorString
{
public:
    ValidatorCdmaUtraTddMode() {};
    virtual ~ValidatorCdmaUtraTddMode() {};

    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
