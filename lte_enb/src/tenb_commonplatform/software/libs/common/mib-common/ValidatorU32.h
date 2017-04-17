///////////////////////////////////////////////////////////////////////////////
//
// ValidatorU32.h
//
// U32 value validator.
//
// A random idea TBD: We use the Strategy pattern to
// allow different validators for a particular attribute type.  The Context
// is the attribute and the validator is the Strategy.  E.g a string
// attribute may have a length validator, a character set validator, a reg-ex
// validator etc, or some combination.  At run-time we hook up attributes and
// validators according to the configuration for the particular product.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorU32_h_
#define __ValidatorU32_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibDN.h>
#include "ValidationFailureDescriptor.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorU32
{
public:
    ValidatorU32();
    virtual ~ValidatorU32();

    /**
     * Validate a u32.
     *
     * \param value The value to validate.
     * \param min   The minimum allowed value.
     * \param max   The maximum allowed value.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);
    virtual bool ValidateU32(MibDN fapLteDn,u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);
};

#endif
