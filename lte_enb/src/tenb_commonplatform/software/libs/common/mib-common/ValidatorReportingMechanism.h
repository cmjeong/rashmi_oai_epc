///////////////////////////////////////////////////////////////////////////////
//
// ValidatorReportingMechanism.h
//
// A validator for ReportingMechanism of AlarmEvents.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorReportingMechanism_h_
#define __ValidatorReportingMechanism_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorReportingMechanism : public ValidatorU32
{
public:

    ValidatorReportingMechanism() {};
    virtual ~ValidatorReportingMechanism() {};

    virtual bool ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);

protected:

private:

};

#endif