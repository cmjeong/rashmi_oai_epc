///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNccPermit.cpp
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
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorNccPermit.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorNccPermit::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   u8 idx = 0;

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      validated = true;

      for (idx = 0; value[idx] != '\0'; idx++)
      {
         if((value[idx] != '1') && (value[idx] != '0'))
         {
            validated = false;

            ostringstream description;
            description << "Provide 8bit string value with 0 and 1 only";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());

            RETURN(validated);
         }
      }
   }
   RETURN(validated);
}
