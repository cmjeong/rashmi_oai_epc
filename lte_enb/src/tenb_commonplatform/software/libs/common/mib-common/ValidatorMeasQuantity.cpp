///////////////////////////////////////////////////////////////////////////////
//
// ValidatorMeasQuantity.cpp
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
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>
#include <string.h>

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorMeasQuantity.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorMeasQuantity::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;

    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
        if(!strcmp(value.c_str(),"CPICH-RSCP"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"CPICH-EcN0"))
	{
            validated = true;
	}
        else
        {
            ostringstream description;
            description << "Supported values are CPICH-RSCP and CPICH-EcN0";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
        }
    }

    RETURN(validated);
}
