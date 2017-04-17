///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTdsCdmaMeasQty.cpp
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
#include "ValidatorTdsCdmaMeasQty.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorTdsCdmaMeasQty::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   if(!(ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) ))
   {
      ostringstream description;
      description << failureDescriptor.GetDescription();
      failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
      RETURN(false);
   }
   else
   {
      if(!strcmp(value.c_str(), "PCCPCH-RSCP"))
      {
         RETURN(true);
      }
      else if(!strcmp(value.c_str(), "RSCP"))
      {
         RETURN(true);
      }
      else
      {
         ostringstream description;
         description << " Value should be PCCPCH-RSCP/RSCP";
         failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
         RETURN(false);
      }
   }

   RETURN(false);
}
