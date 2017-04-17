///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMCollectionPeriod.cpp
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
#include "ValidatorPMCollectionPeriod.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPMCollectionPeriod::ValidateU32(u32 value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorU32::ValidateU32(value, minLength, maxLength, failureDescriptor) )
   {
      if((value % minLength)==0)
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "PMCollectionPeriod value should\n"
                     <<"0 for Same as periodic upload or should be in the multiples of 5 and should not be more than 1440";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }
   RETURN(validated);
}
