///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT311.h
//
// A validator for T311.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorT311_h_
#define __ValidatorT311_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32Array.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorT311 : public ValidatorU32Array
{
public:

    ValidatorT311() {};
    virtual ~ValidatorT311() {};

    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif