///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNumAntenna.h
//
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorNumAntenna_h_
#define __ValidatorNumAntenna_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32Array.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorNumAntenna : public ValidatorU32Array
{
public:
    ValidatorNumAntenna() {};
    virtual ~ValidatorNumAntenna() {};

    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

};

#endif
