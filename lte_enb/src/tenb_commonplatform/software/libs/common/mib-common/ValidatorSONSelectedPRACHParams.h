///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSONSelectedPRACHParams.h
//
// Description : This class validates values allowed for LTE_SON_SELECTED_PRACH_CONFIG_INDEX,
//               LTE_SON_SELECTED_PRACH_ZERO_CORRELATIONZONE_CONFIG and LTE_SON_SELECTED_PRACH_FREQ_OFFSET
//               parameters.
//               255 is also considered valid value but not supposed to be
//               configured from HeMS or CLI. Its the initial value(first-time bootup)
//               of above mentioned parameters.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorSONSelectedPRACHParams_h_
#define __ValidatorSONSelectedPRACHParams_h_

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

class ValidatorSONSelectedPRACHParams : public ValidatorU32
{
public:

    ValidatorSONSelectedPRACHParams() {};
    virtual ~ValidatorSONSelectedPRACHParams() {};

    /**
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
