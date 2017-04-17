///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPeriodicUploadInterval.cpp
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

#include "ValidatorPeriodicUploadInterval.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPeriodicUploadInterval::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
  
   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if ( isValid )
   {
      if((value % min) == 0)
      {
         isValid = true;
      }
      else
      {
         isValid = false;
      }
   }

   if(!isValid)
   {
      ostringstream description;
      description << "\" "<< value << "\" is NotValidValue of PeriodicUploadInterval";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
