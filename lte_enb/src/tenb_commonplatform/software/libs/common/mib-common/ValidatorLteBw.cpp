///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteBw.cpp
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

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorLteBw.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorLteBw::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   for(u32 i = 0; i < value.size(); i++)
   {
      switch(value.at(i))
      {
         case 6:
         case 15:
         case 25:
         case 50:
         case 75:
         case 100:
            {
               validated = true;
            }
            break;
         default:
            {
               validated = false;
            }
            break;
      }
   }

   if(!validated)
   {
      ostringstream description;
      description << "Supported values are 6, 15, 25, 50, 100 ";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(validated);
}
