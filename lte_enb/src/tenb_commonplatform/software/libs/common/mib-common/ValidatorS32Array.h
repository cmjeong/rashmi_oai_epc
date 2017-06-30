///////////////////////////////////////////////////////////////////////////////
//
// ValidatorS32Array.h
//
// S32 Array validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorS32Array_h_
#define __ValidatorS32Array_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibDN.h>
#include "ValidationFailureDescriptor.h"
#include "ValidatorS32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorS32Array
{
public:
    ValidatorS32Array();
    virtual ~ValidatorS32Array();

    /**
     * Validate a s32 array.
     *
     * \param value        The value(s) to validate.
     * \param min          The minimum allowed value.
     * \param max          The maximum allowed value.
     * \param maxInstances The maximum number of elements.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateS32Array(const std::vector<s32>& value, s32 min, s32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

    virtual bool ValidateS32Array(MibDN Dn, const std::vector<s32>& value, s32 min, s32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

private:
    ValidatorS32 m_validatorS32;

};

#endif
