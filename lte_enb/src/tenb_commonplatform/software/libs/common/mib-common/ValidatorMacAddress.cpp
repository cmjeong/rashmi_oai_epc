///////////////////////////////////////////////////////////////////////////////
//
// ValidatorMacAddress.cpp
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

#include "ValidatorMacAddress.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorMacAddress::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   if(ValidatorString::ValidateString(value, 17, 17, failureDescriptor))
   {
      // TODO: Could use boost regex once we add library.

      static const char * VALID_MAC_ADDRESS_CHARS = "0123456789ABCDEF:";
      string::size_type p = value.find_first_not_of(VALID_MAC_ADDRESS_CHARS);
      if(p == string::npos)
      {
         // Didn't find anything except valid chars so looking good.
         RETURN(true);
      }

      ostringstream description;
      description << "must contain only chars from \"" << VALID_MAC_ADDRESS_CHARS << "\"";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());

      RETURN(false);
   }

   RETURN(false);
}
