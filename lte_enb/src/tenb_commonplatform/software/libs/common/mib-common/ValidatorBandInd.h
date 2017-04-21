///////////////////////////////////////////////////////////////////////////////
//
// ValidatorBandInd.h
//
// ReportQuantity validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorBandInd_h_
#define __ValidatorBandInd_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorBandInd : public ValidatorString
{
public:
    ValidatorBandInd() {};
    virtual ~ValidatorBandInd() {};

    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif