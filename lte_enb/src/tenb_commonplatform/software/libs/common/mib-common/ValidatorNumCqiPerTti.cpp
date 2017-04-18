///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNumCqiPerTti.cpp
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
#include "ValidatorNumCqiPerTti.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorNumCqiPerTti::ValidateU32(MibDN Dn,u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_NRBCQI, N2Rb,Dn );
   bool isValid = TRUE;

   for(u32 i = 0; i < N2Rb.size(); i++)
   {
      if((value < 0 ) || (value > u32(atoi(N2Rb.at(i).c_str())*12 )))
      {
         isValid = FALSE;
         ostringstream description;
         description << "NumCqiPerTti  (" << value  << ") should be less  than" << 
            " n2Rb * 12(" << atoi(N2Rb.at(i).c_str()) * 12 << ")";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
      }
   }
   RETURN(isValid);
}

      
