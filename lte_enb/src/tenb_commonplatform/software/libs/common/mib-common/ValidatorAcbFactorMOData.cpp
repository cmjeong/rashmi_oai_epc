///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAcbFactorMOData.cpp
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
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>
#include <string.h>

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorAcbFactorMOData.h"
#include "mib-common/ValidationReferences.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAcbFactorMOData::ValidateString(MibDN fapLteDn, const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MODATA, acBarringAC11, fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MODATA, acBarringAC12,  fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MODATA, acBarringAC13, fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MODATA, acBarringAC14, fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MODATA, acBarringAC15, fapLteDn);

   bool validated = false;
   bool isValid = true;
   /*  This validator validate the set of string. */ 
   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"p00"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p05"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p10"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p15"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p20"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p25"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p30"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p40"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p50"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p60"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p70"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p75"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p80"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p85"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p90"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"p95"))
      {
         validated = true;
      }

      else
      {
         ostringstream description;
         description << "Access Barring Factor, Value :" << value <<endl
            <<"Access Barring Factor Value Range {p00,p05,p10,p15,p20,p25,p30,p40,p50,p60,p70,p75,p80,p85,p90,p95}";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   if(TRUE == validated) 
   {
      if(acBarringAC11 || acBarringAC12 || acBarringAC13 || acBarringAC14 || acBarringAC15)
      {
         if(!strcmp(value.c_str(),"p00"))
         {
            TRACE_PRINTF("ValidatorAcbFactorMOData::corrected acBarring Factor\n");
            isValid = true;
         }
         else
         {
            ostringstream description;
            description << "LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MODATA value (" << value.c_str() << ") Not allowed when ac-BarringForSpecialAC are set to non-zero value ";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str()); 
            isValid = false;
         }
      }
   }
   else
   {
      RETURN(validated);
   }
   RETURN(isValid);
}
