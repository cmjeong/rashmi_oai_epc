///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAccessMode.cpp
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
#include "ValidatorAccessMode.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAccessMode::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"Open_Access"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"Closed_Access"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"Hybrid_Access"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"Open Access"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"Closed Access"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"Hybrid Access"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "AccessMode, value : " << value;
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}
