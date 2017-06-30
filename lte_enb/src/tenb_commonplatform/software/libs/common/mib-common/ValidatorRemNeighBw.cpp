///////////////////////////////////////////////////////////////////////////////
//
// ValidatorRemNeighBw.cpp
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
#include "ValidatorRemNeighBw.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorRemNeighBw::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"n7"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"n15"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"n25"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"n50"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"n100"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "possible values are n7,n15,n25,n50,n100 ";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}

