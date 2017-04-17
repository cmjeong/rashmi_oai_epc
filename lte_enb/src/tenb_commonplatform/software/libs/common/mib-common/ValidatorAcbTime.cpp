///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAcbTime.cpp
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
#include "ValidatorAcbTime.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAcbTime::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;
/* This validator validate the set of string s4, s8, s16, s32, s64, s128, s256, s512. */
    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
        if(!strcmp(value.c_str(),"s4"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"s8"))
	{
            validated = true;
	}
        else if(!strcmp(value.c_str(),"s16"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"s32"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"s64"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"s128"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"s256"))
        {
            validated = true;
        }
        else if(!strcmp(value.c_str(),"s512"))
        {
            validated = true;
        }
        else
        {
            ostringstream description;
            description << "Access Barring Time, Value :" << value <<endl
                         <<"Access Barring Time Value Range {s4,s8,s16,s32,s64,s128,s256,s512}";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
        }
    }

    RETURN(validated);
}

