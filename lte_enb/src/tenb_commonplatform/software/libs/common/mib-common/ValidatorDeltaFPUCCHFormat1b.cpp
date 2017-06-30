///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDeltaFPUCCHFormat1b.cpp 
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

#include "ValidatorDeltaFPUCCHFormat1b.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorDeltaFPUCCHFormat1b::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        switch ( value )
        {
            case 1:
            case 3:
            case 5:
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
        description << "NotValidValue (" << value << ") supported DeltaFPUCCHFormat1b are (" <<
                "1, 3, 5)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
