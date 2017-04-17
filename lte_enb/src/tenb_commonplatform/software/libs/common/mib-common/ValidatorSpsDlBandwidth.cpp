///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSpsDlBandwidth.cpp
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
#include <string.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "mib-common/ValidationReferences.h"
#include "ValidatorSpsDlBandwidth.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorSpsDlBandwidth::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_DL_BANDWIDTH,LteBandwidth,fapLteDn );
   bool validated = FALSE;

   if( ValidatorU32::ValidateU32(value, min, max, failureDescriptor) )
   {
      for(u32 i = 0; i < LteBandwidth.size(); i++)
      {
         if((LteBandwidth.at(i) == 6) && (value <= 6))
         {
            validated = true;
         }
         else if((LteBandwidth.at(i) == 15) && (value <= 15))
         {
            validated = true;
         }
         else if((LteBandwidth.at(i) == 25) && (value <= 25))
         {
            validated = true;
         }
         else if((LteBandwidth.at(i) == 50) && (value <= 50))
         {
            validated = true;
         }
         else if((LteBandwidth.at(i) == 75) && (value <= 75))
         {
            validated = true;
         }
         else if((LteBandwidth.at(i) == 100) && (value <= 100))
         {
            validated = true;
         }
         else
         {
            ostringstream description;
            description << "LTE_MAX_SPS_RB  (" << value  << ") should be less  than" << 
               " LTE_DL_BANDWIDTH (" << LteBandwidth.at(i) << ")";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
         }
      }
   }
   RETURN(validated);
}
      
