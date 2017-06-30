///////////////////////////////////////////////////////////////////////////////
//
// ValidatorHexString.cpp
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
//#include <boost/regex.hpp>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorHexString.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorHexString::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   if(ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor))
   {
      static const char * VALID_SERIAL_NUM_CHARS = "0123456789ABCDEFabcdef";
      if(value.length()>0)
      {
         string::size_type p = value.find_first_not_of(VALID_SERIAL_NUM_CHARS);
         if(p == string::npos)
         {
            // Didn't find anything except valid chars so looking good.
            RETURN(true);
         }
         ostringstream description;
         description << "Must contain only chars from \"" << VALID_SERIAL_NUM_CHARS << "\"";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());

         RETURN(false);
      }
      else
      {
         RETURN(true);
      }
   }

   RETURN(false);
}
