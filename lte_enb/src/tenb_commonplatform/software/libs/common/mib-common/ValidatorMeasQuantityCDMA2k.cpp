///////////////////////////////////////////////////////////////////////////////
//
// ValidatorMeasQuantityCDMA2k.cpp
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
#include "ValidatorMeasQuantityCDMA2k.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//Validator to validate LTE_MEAS_QUANTITY_CDMA2000 accepts only PilotStrength and PilotPnPhaseAndPilotStrength as values
///////////////////////////////////////////////////////////////////////////////

bool ValidatorMeasQuantityCDMA2k::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"PilotStrength"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"PilotPnPhaseAndPilotStrength"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "Allowed values are PilotStrength and PilotPnPhaseAndPilotStrength";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}

