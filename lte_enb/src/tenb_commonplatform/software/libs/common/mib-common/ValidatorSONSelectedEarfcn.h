///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSONSelectedEarfcn.h
//
// Description : This class validates values allowed for LTE_SON_SELECTED_EARFCNUL and
//               LTE_SON_SELECTED_EARFCNDL parameters.
//               4294967295 is also considered valid value but not supposed to be 
//               configured from HeMS or CLI. Its the initial value(first-time bootup)
//               of above mentioned parameters.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorSONSelectedEarfcn_h_
#define __ValidatorSONSelectedEarfcn_h_

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

class ValidatorSONSelectedEarfcn : public ValidatorU32
{
public:

    ValidatorSONSelectedEarfcn() {};
    virtual ~ValidatorSONSelectedEarfcn() {};

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
