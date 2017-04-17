///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSRSBandwidthCfg.cpp
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
#include "ValidatorSRSBandwidthCfg.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorSRSBandwidthCfg::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         if(!strcmp(value.at(i).c_str(),"bw0"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw1"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw2"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw3"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw4"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw5"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw6"))
         {
            validated = true;
         }
         else if(!strcmp(value.at(i).c_str(),"bw7"))
         {
            validated = true;
         }
         else
         {
            validated = false;
            ostringstream description;
            description << "SRSBandwidthCfg is invalid";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         }
      }
   }

   RETURN(validated);
}
