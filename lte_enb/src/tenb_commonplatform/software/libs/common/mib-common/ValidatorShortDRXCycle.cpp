///////////////////////////////////////////////////////////////////////////////
//
// ValidatorShortDRXCycle.cpp
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

#include "ValidatorShortDRXCycle.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorShortDRXCycle::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        switch ( value )
        {
            case 2:
            case 5:
            case 8:
            case 10:
            case 16:
            case 20:
            case 32:
            case 40:
            case 64:
            case 80:
            case 128:
            case 160:
            case 256:
            case 320:
            case 512:
            case 640:
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
        description << "NotValidValue (" << value << ") supported ShortDRXCycle are (" <<
                "2, 5, 8, 10, 16, 20, 32, 40, 64, 80, 128, 160, 256, 320, 512, 640)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
