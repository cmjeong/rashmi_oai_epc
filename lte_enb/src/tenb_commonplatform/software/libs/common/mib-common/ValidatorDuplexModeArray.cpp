///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDuplexModeArray.cpp
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
#include <string.h>

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorDuplexModeArray.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorDuplexModeArray::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {
      for(u32 dupModeElem = 0; dupModeElem < value.size(); dupModeElem++)
      {
         if(!strcmp(value.at(dupModeElem).c_str(),"FDDMode"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(dupModeElem).c_str(),"TDDMode"))
         {
            validated = true;
         }
         else
         {
            validated = false;
            ostringstream description;
            description << "for DuplexMode ";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
            RETURN(validated);
         }
      }
   }

   RETURN(validated);
}
