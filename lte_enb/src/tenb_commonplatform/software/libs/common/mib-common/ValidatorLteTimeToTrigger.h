///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteTimeToTrigger.h
//
// A validator for LTE Time To Trigger.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorLteTimeToTrigger_h_
#define __ValidatorLteTimeToTrigger_h_

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

class ValidatorLteTimeToTrigger : public ValidatorU32Array
{
public:

    ValidatorLteTimeToTrigger() {};
    virtual ~ValidatorLteTimeToTrigger() {};

    /**
     * Validate a Time To Trigger (as u32).
     *
     * \param value The value to validate.
     * \param min   The minimum allowed value.
     * \param max   The maximum allowed value.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif
