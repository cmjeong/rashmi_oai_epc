///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNumAntenna.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
// Validator to validate number of antenna which should be 1,2 or 4
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorNumAntenna.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorNumAntenna::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   if(value.size() > maxInstances)
   {
      ostringstream description;
      description << "numInstances=" << value.size() << ", maxInstances=" << maxInstances;
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
      return false;
   }

   for(u32 i = 0; i < value.size(); i++)
   { 
      switch ( value.at(i) )
      {
         case 1:
         case 2:
         case 4:
            isValid = true;
            break;
         default:
            isValid = false;
            break;
      }

      if(!isValid)
      {
         ostringstream description;
         description << "NotValidValue (" << value.at(i) << ") supported Antenna count values are (" <<
            "1,2,4 )";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(isValid); 
}
