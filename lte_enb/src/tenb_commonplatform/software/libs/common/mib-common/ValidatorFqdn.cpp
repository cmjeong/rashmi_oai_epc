///////////////////////////////////////////////////////////////////////////////
//
// ValidatorFqdn.cpp
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
#include <system/Url.h>


#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorFqdn.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorFqdn::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;

    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
        if(threeway::Fqdn::FromString(value))
        {
            validated = true;
        }
        else
        {
            ostringstream description;
            description << "Fqdn is invalid.";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
        }
    }

    RETURN(validated);
}
