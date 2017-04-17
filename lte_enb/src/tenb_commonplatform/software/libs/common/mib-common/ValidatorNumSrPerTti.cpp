///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNumSrPerTti.cpp
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
#include "ValidatorNumSrPerTti.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorNumSrPerTti::ValidateU32(MibDN Dn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_N1PUCCHAN,N1Pucch,Dn);
   bool isValid = TRUE;

   if( ValidatorU32::ValidateU32(value, min, max, failureDescriptor) )
   {
      for(u32 i = 0; i < N1Pucch.size(); i++)
      {
         if((value < 0 ) || (value > u32(atoi(N1Pucch.at(i).c_str()) )))
         {
            isValid = FALSE;
            ostringstream description;
            description << "NumSrPerTti  (" << value  << ") should be less  than" << 
               " N1Pucch (" << atoi(N1Pucch.at(i).c_str()) << ")";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
         }
      }
   }
   RETURN(isValid);
}

      
