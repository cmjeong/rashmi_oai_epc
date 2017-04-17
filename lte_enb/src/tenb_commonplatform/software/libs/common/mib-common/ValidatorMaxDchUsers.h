///////////////////////////////////////////////////////////////////////////////
//
// ValidatorMaxDchUsers
//
// TODO: Describe purpose and usage of class(es).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorMaxDchUsers_h_
#define __ValidatorMaxDchUsers_h_

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

class ValidatorMaxDchUsers : public ValidatorU32
{
public:

    ValidatorMaxDchUsers() {};
    virtual ~ValidatorMaxDchUsers() {};

    /**
     * Validate a Maximum Number of Cell DCH Users permitted (as u32).  Limited by HW platform.
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
