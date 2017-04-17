///////////////////////////////////////////////////////////////////////////////
//
// ValidatorQOffsetFrequency.cpp 
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

#include "ValidatorQOffsetFrequency.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorQOffsetFrequency::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   for(u32 i = 0; i < value.size(); i++)
   {
      switch(atoi(value.at(i).c_str()))
      {
         case -24:
         case -22:
         case -20:
         case -18:
         case -16:
         case -14:
         case -12:
         case -10:
         case -8:
         case -6:
         case -5:
         case -4:
         case -3:
         case -2:
         case -1:
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
         case 6:
         case 8:
         case 10:
         case 12:
         case 14:
         case 16:
         case 18:
         case 20:
         case 22:
         case 24:
            {
               isValid = true;
            }
            break;
         default:
            {
               isValid = false;
            }
            break;
      }
   if(!isValid)
      break;
   }

   if(!isValid)
   {
      ostringstream description;
      description << "Supported QOffsetFrequency are (" <<
         "-24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
