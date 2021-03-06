///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPowerRamping.h
//
// A validator for PowerRamping.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPowerRamping_h_
#define __ValidatorPowerRamping_h_

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

class ValidatorPowerRamping : public ValidatorU32Array
{
public:

    ValidatorPowerRamping() {};
    virtual ~ValidatorPowerRamping() {};

    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif
