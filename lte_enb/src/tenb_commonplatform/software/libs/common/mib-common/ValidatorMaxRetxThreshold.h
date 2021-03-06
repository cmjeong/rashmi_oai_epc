///////////////////////////////////////////////////////////////////////////////
//
// ValidatorMaxRetxThreshold.h
//
// A validator for MaxRetxThreshold.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorMaxRetxThreshold_h_
#define __ValidatorMaxRetxThreshold_h_

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

class ValidatorMaxRetxThreshold: public ValidatorU32Array
{
public:

    ValidatorMaxRetxThreshold() {};
    virtual ~ValidatorMaxRetxThreshold() {};

    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif
