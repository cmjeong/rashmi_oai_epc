///////////////////////////////////////////////////////////////////////////////
//
// ValidatorHoppingMode.cpp
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
#include "ValidatorHoppingMode.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorHoppingMode::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"InterSubFrame"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"IntraAndInterSubFrame"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "HoppingMode is invalid";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}
