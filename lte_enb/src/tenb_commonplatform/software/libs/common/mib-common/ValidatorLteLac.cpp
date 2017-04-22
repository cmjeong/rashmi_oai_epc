///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteLac.cpp
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

#include "ValidatorLteLac.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorLteLac::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if (!isValid)
   {
      RETURN(isValid);
   }
   else
   {
      switch ( value )
      {
         case 0:
         case 65534:
            isValid = false;
            break;
         default:
            isValid = true;
            break;
      }
   }

   if(!isValid)
   {
      ostringstream description;
      description << "NotValidValue (" << value << ") Inter-RAT GSM does not support (" <<
         "0 and 65534)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
