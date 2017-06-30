///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDrxEnbDis.cpp
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
#include "mib-common/ValidationReferences.h"
#include "ValidatorDrxEnbDis.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorDrxEnbDis::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_DRX_QCI_ENABLE,DrxQci,fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_ANR_REPORT_CFG_VAL,AnrRptCfgVal,fapLteDn);
   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);
      if(!isValid)
      {
	 RETURN(isValid);
      }

   if(0 == value)
   {
      if((0 == AnrRptCfgVal) && (1 == DrxQci))
      {
         isValid = FALSE;
         ostringstream description;
         description << "Drx can not be disabled as LTE_ANR_REPORT_CFG_VAL is disabled and LTE_DRX_QCI_ENABLE is enabled";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
         RETURN(isValid);
      }
   }
   RETURN(isValid);
}
