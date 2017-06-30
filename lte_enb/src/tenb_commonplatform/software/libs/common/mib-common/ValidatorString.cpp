///////////////////////////////////////////////////////////////////////////////
//
// ValidatorString.cpp
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
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorString.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorString::ValidatorString()
{
    ENTER();

    EXIT();
}

ValidatorString::~ValidatorString()
{
    ENTER();

    EXIT();
}

bool ValidatorString::ValidateString(MibDN Dn, const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    return (ValidateString(value, minLength, maxLength, failureDescriptor));
}
bool ValidatorString::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    u32 len = value.length();
    if(len < minLength)
    {
        ostringstream description;
        description << "length=" << len << ", minLength=" << minLength;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_SHORT, description.str());
        RETURN(false);
    }

    if(len > maxLength)
    {
        ostringstream description;
        description << "length=" << len << ", maxLength=" << maxLength;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_LONG, description.str());
        RETURN(false);
    }

    RETURN(true);
}

/*******************************************************************************************
* Function : ValidateString
* @args : 
*  value : Input value that is to be validated.
*  minLength : valid minimum length of "value".
*  maxLength : valid maximum length of "value".
*  allowedValues : array of char pointers pointing to list of allowed values for the parameter.
*  length : Number of elements in allowedValues array.
*  failureDescriptor : Object that holds validation failure cause, if any.
*
* Description: This function validates minimum and maximum length requirement
*              of input string. And also validates whether input string is 
*              one of the allowed values that are pointed by the array allowedValues[].
********************************************************************************************/
bool ValidatorString::ValidateString(MibDN Dn, const std::string& value, u32 minLength, u32 maxLength, const char* allowedValues[], u32 length, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    ValidateString(value, minLength, maxLength, allowedValues, length, failureDescriptor);
    return true;
}

bool ValidatorString::ValidateString(const std::string& value, u32 minLength, u32 maxLength, const char* allowedValues[], u32 length, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;
    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
        for(u32 index = 0; index < length; index++)
        {
            if( !strcmp(allowedValues[index], value.c_str()) )
            {
                validated = true;
                break;
            }
        }

        if(!validated)  // Set the appropriate failure cause when validation fails
        {
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_INVALID);
        }
    }

    RETURN(validated);
}
