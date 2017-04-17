///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTStatusProhibit.cpp
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

#include "ValidatorTStatusProhibit.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorTStatusProhibit::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
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
            case 5:
            case 10:
            case 15:
            case 20:
            case 25:
            case 30:
            case 35:
            case 40:
            case 45:
            case 50:
            case 55:
            case 60:
            case 65:
            case 70:
            case 75:
            case 80:
            case 85:
            case 90:
            case 95:
            case 100:
            case 105:
            case 110:
            case 115:
            case 120:
            case 125:
            case 130:
            case 135:
            case 140:
            case 145:
            case 150:
            case 155:
            case 160:
            case 165:
            case 170:
            case 175:
            case 180:
            case 185:
            case 190:
            case 195:
            case 200:
            case 205:
            case 210:
            case 215:
            case 220:
            case 225:
            case 230:
            case 235:
            case 240:
            case 245:
            case 250:
            case 350:
            case 400:
            case 450:
            case 500:
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
      description << "Supported TStatusProhibit are (" <<
         "0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 110, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235, 240, 245, 250, 350, 400, 450, 500)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
