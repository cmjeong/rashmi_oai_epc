///////////////////////////////////////////////////////////////////////////////
//
// ValidatorS32.h
//
// S32 value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorS32_h_
#define __ValidatorS32_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibDN.h>
#include "ValidationFailureDescriptor.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorS32
{
public:
    ValidatorS32();
    virtual ~ValidatorS32();

    /**
     * Validate a s32.
     *
     * \param value The value to validate.
     * \param min   The minimum allowed value.
     * \param max   The maximum allowed value.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateS32(s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor);
    virtual bool ValidateS32(MibDN Dn,s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor);

};

#endif
