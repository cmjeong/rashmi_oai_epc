///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT304ExpWaitTmr.cpp
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

#include "ValidatorT304ExpWaitTmr.h"
#include "mib-common/ValidationReferences.h"

#define DELAY 100

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorT304ExpWaitTmr::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_T304IRAT, t304Irat, fapLteDn);

   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if( isValid )
   {
      if( value < t304Irat.at(0) + DELAY )
      {
	 isValid = false;
         ostringstream description;
         description << "LTE_GERAN_T304_EXP_WAIT_TMR should be atleast 100 + LTE_T304IRAT ";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
      }
   }

   RETURN(isValid);
}

