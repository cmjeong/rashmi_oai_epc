///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT30SeriesTimer.cpp
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

#include "ValidatorT30SeriesTimer.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorT30SeriesTimer::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        switch ( value )
        {
            case 100:
            case 200:
            case 300:
            case 400:
            case 600:
            case 1000:
            case 1500:
            case 2000:
            case 3000:
            case 4000:
            case 5000:
            case 6000:
            case 7000:
            case 8000:
            case 9000:
            case 10000:
            case 11000:
            case 12000:
            case 13000:
            case 14000:
            case 15000:
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
        description << "NotValidValue (" << value << ") supported T30SeriesTimer are (" <<
                "100, 200, 300, 400, 600, 1000, 1500, 2000)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
