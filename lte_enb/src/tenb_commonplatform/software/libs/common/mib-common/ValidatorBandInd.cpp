///////////////////////////////////////////////////////////////////////////////
//
// ValidatorBandInd.cpp
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
#include "ValidatorBandInd.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorBandInd::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;

    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
       if((!strcmp(value.c_str(),"GSM850")) || (!strcmp(value.c_str(),"GSM900")) || (!strcmp(value.c_str(),"DCS1800")) ||(!strcmp(value.c_str(),"PCS1900")))
       {
          validated = true;
       }
       else
       {
          ostringstream description;
          description << "Band Indicator, value : " <<value;
          failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
       }
    }

    RETURN(validated);
}
