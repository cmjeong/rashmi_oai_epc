///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPlmnIds.cpp
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
#include <mobnet/PlmnId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorPlmnIds.h"

using namespace std;

bool ValidatorPlmnIds::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   minLength = 5;
   maxLength = 6;

   if(!ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor))
   {
      return false;
   }

   if(!(value.size()))
   {
      TRACE_PRINTF("PLMNList is NULL\n");
      return true;
   }

   for(u32 i = 0; i < value.size(); i++)
   {
      bool valid = rsysmob::PlmnId::Validate(value.at(i));

      if(!valid)
      {
         ostringstream description;
         description << "Element " << i << ": " << value.at(i) << " invalid PLMN ID.";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         return false;
      }
   }

   return true;
}
