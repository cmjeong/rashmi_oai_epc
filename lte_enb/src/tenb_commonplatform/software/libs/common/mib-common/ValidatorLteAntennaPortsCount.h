///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteAntennaPortsCount.h
//
// LteAntennaPortsCount value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorLteAntennaPortsCount_h_
#define __ValidatorLteAntennaPortsCount_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidationFailureDescriptor.h"
#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorLteAntennaPortsCount : public ValidatorU32
{
public:
    ValidatorLteAntennaPortsCount();
    virtual ~ValidatorLteAntennaPortsCount();

    /**
     * Validate a LteAntennaPortsCount.
     *
     * \param value The value to validate.
     * \param min   The minimum allowed value.
     * \param max   The maximum allowed value.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);

};

#endif
