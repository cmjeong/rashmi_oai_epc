///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPreambleInitialTargetPower.cpp
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

#include "ValidatorPreambleInitialTargetPower.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPreambleInitialTargetPower::ValidateS32Array(const std::vector<s32>& value, s32 min, s32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorS32Array::ValidateS32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch(value.at(i))
         {
            case -120:
            case -118:
            case -116:
            case -114:
            case -112:
            case -110:
            case -108:
            case -106:
            case -104:
            case -102:
            case -100:
            case -98:
            case -96:
            case -94:
            case -92:
            case -90:
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
      description << "Supported PreambleInitialTargetPower are (" <<
         "-120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90 )";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
