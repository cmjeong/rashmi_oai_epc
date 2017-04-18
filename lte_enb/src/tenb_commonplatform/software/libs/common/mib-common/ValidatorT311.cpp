///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT311.cpp
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

#include "ValidatorT311.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorT311::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorU32Array::ValidateU32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch ( value.at(i) )
         {
         case 1000:
         case 3000:
         case 5000:
         case 10000:
         case 15000:
         case 20000:
         case 30000:
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
      description << "Supported T311 are (" <<
         "1000, 3000, 5000, 10000, 15000, 20000, 30000)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
