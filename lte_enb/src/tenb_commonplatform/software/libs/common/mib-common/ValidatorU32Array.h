///////////////////////////////////////////////////////////////////////////////
//
// ValidatorU32Array.h
//
// U32 value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorU32Array_h_
#define __ValidatorU32Array_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibDN.h>
#include "ValidationFailureDescriptor.h"
#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorU32Array
{
public:
    ValidatorU32Array();
    virtual ~ValidatorU32Array();

    /**
     * Validate a u32 array.
     *
     * \param value        The value(s) to validate.
     * \param min          The minimum allowed value.
     * \param max          The maximum allowed value.
     * \param maxInstances The maximum number of elements.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

    virtual bool ValidateU32Array(MibDN Dn,const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
private:
    ValidatorU32 m_validatorU32;

};

#endif
