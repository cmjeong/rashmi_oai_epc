///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAcBarringMOData.cpp
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
#include "ValidatorAcBarringMOData.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAcBarringMOData::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MODATA,acbFac,fapLteDn);
   bool isValid = TRUE; 

   if(value != 0)
   {
      if (0 != strcmp(acbFac.c_str(),"p00"))
      {
         ostringstream description;
         description << "To set the value of ac-BarringForSpecial as non-zero, LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MODATA value should not be(" << acbFac.c_str() << ")";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str()); 
         isValid = false;
      }
      else
      {
         TRACE_PRINTF("ValidatorAcBarringMOData:: acBarring Factor doesnot affected\n");
         isValid = true;
      }
   }
   RETURN(isValid);
}
