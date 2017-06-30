///////////////////////////////////////////////////////////////////////////////
//
// ValidatorCdmaUtraTddMode.cpp
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
#include "ValidatorCdmaUtraTddMode.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorCdmaUtraTddMode::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   if( !(ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) ))
   {
      ostringstream description;
      description << failureDescriptor.GetDescription();
      failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
      RETURN(false);
   }
   else
   {
      if(!strcmp(value.c_str(),"UTRA_TDD_128"))
      {
         RETURN(true);
      }
      else if(!strcmp(value.c_str(),"UTRA_TDD_384"))
      {
         RETURN(true);
      }
      else if(!strcmp(value.c_str(),"UTRA_TDD_768"))
      {
         RETURN(true);
      }
      else
      {
         ostringstream description;
         description << "value should be UTRA_TDD_128/UTRA_TDD_384/UTRA_TDD_768";
         failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
         RETURN(false);
      }
   }

   RETURN(false);
}
