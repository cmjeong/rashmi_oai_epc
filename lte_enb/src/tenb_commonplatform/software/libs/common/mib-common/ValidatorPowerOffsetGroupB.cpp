///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPowerOffsetGroupB.cpp
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

#include "ValidatorPowerOffsetGroupB.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPowerOffsetGroupB::ValidateS32Array(const std::vector<s32>& value, s32 min, s32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorS32Array::ValidateS32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch(value.at(i))
         {
            case -1:
            case 0:
            case 5:
            case 8:
            case 10:
            case 12:
            case 15:
            case 18:
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
      description << "Supported MessagePowerOffsetGroupB are (" <<
         "-1, 0, 5, 8, 10, 12, 15, 18)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
