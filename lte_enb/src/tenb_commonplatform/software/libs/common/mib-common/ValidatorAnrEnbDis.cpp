///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAnrEnbDis.cpp
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
#include "ValidatorAnrEnbDis.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAnrEnbDis::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_DRX_QCI_ENABLE,DrxQci,fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_DRX_ENABLE,DrxEnable ,fapLteDn);
   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if(!isValid)
   {
      ostringstream description;
      description << "NotValidValue (" << value << ") its bool";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   if(0 == value)
   {
      if((1 == DrxQci) && (0 == DrxEnable))
      {
         isValid = FALSE;
         ostringstream description;
         description << "ANR can not be disabled as DRX_QCI is enabled and LTE_DRX_ENABLE is disabled";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         RETURN(isValid);
      }
   }
   RETURN(isValid);
}
