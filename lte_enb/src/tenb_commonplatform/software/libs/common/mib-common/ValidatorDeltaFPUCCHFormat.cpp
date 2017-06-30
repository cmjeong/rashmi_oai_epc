///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDeltaFPUCCHFormat.cpp 
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

#include "ValidatorDeltaFPUCCHFormat.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorDeltaFPUCCHFormat::ValidateS32(s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorS32::ValidateS32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        if((value == -2)||(value == 0)||(value == 2))
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
        description << "NotValidValue (" << value << ") supported DeltaFPUCCHFormat are (" <<
                "-2, 0, 2)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
