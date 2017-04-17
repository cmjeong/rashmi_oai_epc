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
#include "ValidatorCaEnbDis.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorCaEnbDis::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_NUM_OF_CELLS,numOfCells,fapLteDn);
   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);
   if(!isValid)
   {
      RETURN(isValid);
   }

   if(1 == value)
   {
      if(1 == numOfCells)
      {
         isValid = FALSE;
         ostringstream description;
         description << "Number of cells is 1, which means CA Flag cannot be enabled";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
         RETURN(isValid);
      }
   }
   RETURN(isValid);
}
