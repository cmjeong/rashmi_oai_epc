///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMFileTransferMethod.h
//
// PMFileTransferMethod value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPMFileTransferMethod_h_
#define __ValidatorPMFileTransferMethod_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorPMFileTransferMethod : public ValidatorString
{
public:
    ValidatorPMFileTransferMethod() {};
    virtual ~ValidatorPMFileTransferMethod() {};

    /**
     * Validate a PMFileTransferMethod.  Does string semantic
     * checks on the contents of the string.
     *
     * \param value             The PMFileTransferMethod to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
