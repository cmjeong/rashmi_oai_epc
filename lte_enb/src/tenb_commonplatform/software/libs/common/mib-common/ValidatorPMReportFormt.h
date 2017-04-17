///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMReportFormt.h
//
// PMCollectionPeriod value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorPMReportFormt_h_
#define __ValidatorPMReportFormt_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorPMReportFormt : public ValidatorString
{
public:
    ValidatorPMReportFormt() {};
    virtual ~ValidatorPMReportFormt() {};

    /**
     * Validate an ValidatorPMReportFormt.  Does string semantic
     * checks on the contents of the string.
     *
     * \param value             The ValidatorPMReportFormt to validate.
     * \param minLength         The minimum length allowed.
     * \param maxLength         The maximum length allowed.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor);

};

#endif
