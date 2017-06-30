///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDRXRetransmissionTimer.cpp
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

#include "ValidatorDRXRetransmissionTimer.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorDRXRetransmissionTimer::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if( ValidatorU32Array::ValidateU32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch ( value.at(i) )
         {
         case 1:
         case 2:
         case 4:
         case 6:
         case 8:
         case 16:
         case 24:
         case 33:
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
      description << "Supported DRXRetransmissionTimer are (" <<
         "1, 2, 4, 6, 8, 16, 24, 33)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
