///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMCollectionPeriod.h
//
// PMCollectionPeriod value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPMCompressMethod_h_
#define __ValidatorPMCompressMethod_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorPMCompressMethod : public ValidatorString
{
public:
    ValidatorPMCompressMethod() {};
    virtual ~ValidatorPMCompressMethod() {};

    /**
     * Validate an ValidatorPMCompressMethod.  Does string semantic
     * checks on the contents of the string.
     *
     * \param value             The ValidatorPMCompressMethod to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
