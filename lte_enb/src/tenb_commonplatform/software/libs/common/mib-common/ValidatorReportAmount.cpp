///////////////////////////////////////////////////////////////////////////////
//
// ValidatorReportAmount.cpp
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

#include "ValidatorReportAmount.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorReportAmount::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"r1"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"r2"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"r4"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"r8"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"r16"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"r32"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"r64"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"infinity"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "valid values can be (r1, r2, r4, r8, r16, r32, r64, infinity) ";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}
