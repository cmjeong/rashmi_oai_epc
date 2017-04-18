///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAlpha.cpp 
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

#include "ValidatorAlpha.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAlpha::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch ( atoi(value.at(i).c_str()) )
         {
            case 0:
            case 40:
            case 50:
            case 60:
            case 70:
            case 80:
            case 90:
            case 100:
               isValid = true;
               break;
            default:
               isValid = false;
               break;
         }
         if(!isValid)
            break;
      }
   }

   if(!isValid)
   {
      ostringstream description;
      description << "supported Alpha values are (" <<
         "0, 40, 50, 60, 70, 80, 90, 100)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
