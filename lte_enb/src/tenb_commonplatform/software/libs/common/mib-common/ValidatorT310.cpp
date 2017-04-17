///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT310.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorT310.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorT310::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorU32Array::ValidateU32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch ( value.at(i) )
         {
         case 0:
         case 50:
         case 100:
         case 200:
         case 500:
         case 1000:
         case 2000:
               isValid = true;
               break;
         default:
               isValid = false;
               break;
         }
      }
   }

   if(!isValid)
   {
      ostringstream description;
      description << "Supported T310 are (" <<
         "0, 50, 100, 200, 500, 1000, 2000)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}