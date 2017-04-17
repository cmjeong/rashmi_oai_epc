///////////////////////////////////////////////////////////////////////////////
//
// ValidatorRaPreambles.cpp 
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

#include "ValidatorRaPreambles.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorRaPreambles::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorU32Array::ValidateU32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 idx = 0; idx < value.size(); idx++)
      {
         switch ( value.at(idx) )
         {
         case 4:
         case 8:
         case 12:
         case 16:
         case 20:
         case 24:
         case 28:
         case 32:
         case 36:
         case 40:
         case 44:
         case 48:
         case 52:
         case 56:
         case 60:
         case 64:
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
      description << "Supported NumberOfRaPreambles are (" <<
         "4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
