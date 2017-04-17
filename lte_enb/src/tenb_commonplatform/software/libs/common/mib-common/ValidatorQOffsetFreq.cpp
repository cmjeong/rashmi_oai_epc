///////////////////////////////////////////////////////////////////////////////
//
// ValidatorQOffsetFreq.cpp 
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

#include "ValidatorQOffsetFreq.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorQOffsetFreq::ValidateS32(s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorS32::ValidateS32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        if((value == -24)||(value == -22)||(value == -20)||(value == -18) || (value == -16) || (value == -14) || (value == -12) || (value == -10) || (value == -8) || (value == -6) || (value == -5) || (value == -4) || (value == -3) || (value == -2) || (value == -1) || (value == 0) || (value == 1)|| (value == 2) || (value == 3) || (value == 4) || (value == 5) || (value == 6) || (value == 8) || (value == 10) || (value == 12) || (value == 14) || (value == 16) || (value == 18) || (value == 20) || (value == 22) || (value == 24))
	{
            isValid = true;
        }
	else
	{        
	isValid = false;
        }
    }

    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported QOffsetFreq are (" <<
                "-24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
