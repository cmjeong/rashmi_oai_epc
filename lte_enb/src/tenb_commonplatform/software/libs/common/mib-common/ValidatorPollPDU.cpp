///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPollPDU.cpp
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

#include "ValidatorPollPDU.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPollPDU::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
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
         case 4:
         case 8:
         case 16:
         case 32:
         case 64:
         case 128:
         case 256:
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
      description << "Supported PollPDU are (" <<
         "0, 4, 8, 16, 32, 64, 128, 256)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
