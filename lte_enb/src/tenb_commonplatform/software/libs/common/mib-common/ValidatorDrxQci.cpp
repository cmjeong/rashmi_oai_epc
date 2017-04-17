///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDrxQci.cpp
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
#include "ValidatorDrxQci.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorDrxQci::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_DRX_ENABLE,DrxEnable,fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_ANR_REPORT_CFG_VAL,AnrRptCfgVal,fapLteDn);
   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if(value > 0)
   {
      if((0 == AnrRptCfgVal) && (0 == DrxEnable))
      {
         isValid = FALSE;
         ostringstream description;
         description << "DrxQci can not be enabled as both LTE_ANR_REPORT_CFG_VAL and LTE_DRX_ENABLE are disabled";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         RETURN(isValid);
      }
   }
   if(!isValid)
   {
      ostringstream description;
      description << "NotValidValue (" << value << ") its bool";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }
   RETURN(isValid);
}
