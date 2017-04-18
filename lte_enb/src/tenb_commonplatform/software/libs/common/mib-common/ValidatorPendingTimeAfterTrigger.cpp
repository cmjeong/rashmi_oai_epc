///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPendingTimeAfterTrigger.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorPendingTimeAfterTrigger.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPendingTimeAfterTrigger::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        switch ( value )
        {
            case 250:
            case 500:
            case 1000:
            case 2000:
            case 4000:
            case 8000:
            case 16000:
                isValid = true;
                break;
            default:
                isValid = false;
                break;
        }
    }

    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported thresholds are (" <<
                "250, 500, 1000, 2000, 4000, 8000, 16000)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
