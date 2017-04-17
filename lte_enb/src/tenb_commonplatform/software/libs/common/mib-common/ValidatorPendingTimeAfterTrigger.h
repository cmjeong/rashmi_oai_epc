///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPendingTimeAfterTrigger.h
//
// A validator for Pending Time After Trigger.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPendingTimeAfterTrigger_h_
#define __ValidatorPendingTimeAfterTrigger_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorPendingTimeAfterTrigger : public ValidatorU32
{
public:

    ValidatorPendingTimeAfterTrigger() {};
    virtual ~ValidatorPendingTimeAfterTrigger() {};

    /**
     * Validate a Pending Time After Trigger (as u32).
     *
     * \param value The value to validate.
     * \param min   The minimum allowed value.
     * \param max   The maximum allowed value.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);

protected:

private:

};

#endif
