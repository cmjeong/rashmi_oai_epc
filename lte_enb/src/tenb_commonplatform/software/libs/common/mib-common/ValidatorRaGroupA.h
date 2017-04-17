///////////////////////////////////////////////////////////////////////////////
//
// ValidatorRaGroupA.h
//
// A validator for SizeOfRaGroupA.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorRaGroupA_h_
#define __ValidatorRaGroupA_h_

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

class ValidatorRaGroupA : public ValidatorU32Array
{
public:

    ValidatorRaGroupA() {};
    virtual ~ValidatorRaGroupA() {};

    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif
