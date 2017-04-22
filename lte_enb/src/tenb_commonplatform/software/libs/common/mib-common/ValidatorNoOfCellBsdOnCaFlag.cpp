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
#include "ValidatorNoOfCellBsdOnCaFlag.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorNoOfCellBsdOnCaFlag::ValidateU32(MibDN Dn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_CA_ENABLE,isCaEnable,Dn);
   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);
   if(!isValid)
   {
      RETURN(isValid);
   }

   if((1 == value) && (isCaEnable == 1))
   {
         isValid = FALSE;
         ostringstream description;
         description << "CA enable flag is set to 1 , so num of cells cannot be 1";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
         RETURN(isValid);
   }
   RETURN(isValid);
}
