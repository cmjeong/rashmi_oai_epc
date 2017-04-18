///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTEvaluation.cpp
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

#include "ValidatorTEvaluation.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorTEvaluation::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        switch ( value )
        {
            case 30:
            case 60:
            case 120:
            case 180:
            case 240:
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
        description << "NotValidValue (" << value << ") supported TEvaluation and THystNormal are (" <<
                "30, 60, 120, 180, 240)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
