///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteQOffsetRange.cpp
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
#include "ValidatorLteQOffsetRange.h"

using namespace std;

const char* ValidatorLteQOffsetRange::arrQOffsetRange[] = {"dB-24","dB-22","dB-20","dB-18","dB-16","dB-14",
                                 "dB-12","dB-10","dB-8","dB-6","dB-5","dB-4","dB-3",
                                 "dB-2","dB-1","dB0","dB1","dB2","dB3","dB4","dB5",
                                 "dB6","dB8","dB10","dB12","dB14","dB16","dB18",
                                 "dB20","dB22","dB24"};
///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorLteQOffsetRange::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;
   u32  idx = 0;
   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         for(idx = 0; idx < 31; idx++)
         {
            if(!strcmp(value.at(i).c_str(),arrQOffsetRange[idx]))
            {
               validated = true;
               break;
            }
         }
         if(!validated || idx == 31)	    
         {
            ostringstream description;
            description << "Element " << i << ": " << failureDescriptor.GetDescription();
            failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            RETURN(false);
         }
      }
   }

   RETURN(validated);
}
