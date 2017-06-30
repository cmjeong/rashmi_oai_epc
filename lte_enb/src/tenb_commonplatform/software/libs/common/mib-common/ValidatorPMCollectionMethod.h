///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMCollectionMethod.h
//
// PMCollectionPeriod value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPMCollectionMethod_h_
#define __ValidatorPMCollectionMethod_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorPMCollectionMethod : public ValidatorString
{
public:
    ValidatorPMCollectionMethod() {};
    virtual ~ValidatorPMCollectionMethod() {};

    /**
     * Validate an PMCollectionPeriod.  Does string semantic
     * checks on the contents of the string.
     *
     * \param value             The PMCollectionPeriod to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
