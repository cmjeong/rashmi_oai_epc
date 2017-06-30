///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTmAutoCheck.cpp
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
#include "ValidatorTmAutoCheck.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorTmAutoCheck::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;

    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
        if(!strcmp(value.c_str(),"ON")||!strcmp(value.c_str(),"OFF"))
        {
            validated = true;
        }
        else
        {
            ostringstream description;
            description << "Auto config mode value should be ON or OFF ";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
        }
    }

    RETURN(validated);
}
