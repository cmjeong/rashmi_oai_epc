///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMCollectionPeriod.h
//
// PMCollectionPeriod value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPMCollectionPeriod_h_
#define __ValidatorPMCollectionPeriod_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorPMCollectionPeriod : public ValidatorU32
{
public:
    ValidatorPMCollectionPeriod() {};
    virtual ~ValidatorPMCollectionPeriod() {};

    /**
     * Validate an PMCollectionPeriod.  Does string semantic
     * checks on the contents of the string.
     *
     * \param value             The PMCollectionPeriod to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32(u32 value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
