///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIntegrityProtectionAlgo.cpp
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
#include "ValidatorIntegrityProtectionAlgo.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorIntegrityProtectionAlgo::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         if(!strcmp(value.at(i).c_str(),"128-EIA1"))
         {
            validated = true;
            continue;
         }
         else if(!strcmp(value.at(i).c_str(),"128-EIA2"))
         {
            validated = true;
            continue;
         }
         else if(!strcmp(value.at(i).c_str(),"128-EIA3"))
         {
            validated = true;
            continue;
         }
         else
         {
            ostringstream description;
            description << "Element " << i << ": " << failureDescriptor.GetDescription();
            failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            RETURN(false);
         }
      }
   }

   RETURN(validated);
}
