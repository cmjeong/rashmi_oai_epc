///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLtePa.cpp 
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

#include "ValidatorLtePa.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorLtePa::ValidateS32Array(const std::vector<s32>& value, s32 min, s32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorS32Array::ValidateS32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch(value.at(i))
         {
            case -600:
            case -477:
            case -300:
            case -117:
            case 0:
            case 100:
            case 200:
            case 300:
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
      }
   }

   if(!isValid)
   {
      ostringstream description;
      description << "Supported PA are (" <<
         "-600, -477, -300, -177, 0, 100, 200, 300)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
