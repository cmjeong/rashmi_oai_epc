///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTmAutoCheck.h
//
//  TM Auto config validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorTmAutoCheck_h_
#define __ValidatorTmAutoCheck_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorTmAutoCheck : public ValidatorString
{
public:
    ValidatorTmAutoCheck() {};
    virtual ~ValidatorTmAutoCheck() {};

    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
