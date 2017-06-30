///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIpv6Allias.cpp
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
#include <stdlib.h>
#include <system/Trace.h>


#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorIpv6Allias.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorIpv6Allias::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;
    ostringstream description;
    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
       std::string sub=value.substr(0,4);
       if(sub!="cpe-")
       {
          validated=false;
          description<<"IpV6 Allias should start with string \"-cpe\"";
       }
       else
       {
          validated=true;
       }
    }
    else
    {
       description<<"IpV6 allias name lengh" <<value.length()<<"not allowed \n length sould be "<<minLength<<"-"<<maxLength;
    }
     
    if(!validated)
    {
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_INVALID, description.str());
    }
    RETURN(validated);
}
