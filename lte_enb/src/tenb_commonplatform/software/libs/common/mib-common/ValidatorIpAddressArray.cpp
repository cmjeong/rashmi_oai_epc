///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIpAddressArray.cpp
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
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorIpAddressArray.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorIpAddressArray::ValidatorIpAddressArray()
{

}


bool ValidatorIpAddressArray::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   if(value.size() > maxInstances)
   {
      ostringstream description;
      description << "numInstances=" << value.size() << ", maxInstances=" << maxInstances;
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
      return false;
   }

   for(u32 i = 0; i < value.size(); i++)
   {
      if(!m_validatorIpAddress.ValidateString(value.at(i), minLength, maxLength, failureDescriptor))
      {
         ostringstream description;
         description << "Element " << i << ": " << failureDescriptor.GetDescription();
         failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
         RETURN(false);
      }
   }
   return true;
}
