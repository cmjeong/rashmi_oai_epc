///////////////////////////////////////////////////////////////////////////////
//
// ValidatorEcsfbReportCfg.cpp
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
#include "ValidatorEcsfbReportCfg.h"
#include "mib-common/ValidationReferences.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Validator to Ensure values of LTE_ECSFB_REPORT_CFG_VAL accepts only ECSFB_NOT_SUPPORTED ,ECSFB_WITHOUT_MEAS and ECSFB_WITH_MEAS
///////////////////////////////////////////////////////////////////////////////

bool ValidatorEcsfbReportCfg::ValidateString(MibDN fapLteDn, const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_IS_DUAL_RXTX_ALLOWED,DualRxTxValue,fapLteDn);
   bool validated = false;


   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"ECSFB_NOT_SUPPORTED"))
      {

         if ( DualRxTxValue == 1)
         {
            validated=false;
            ostringstream description;
            description << "For setting CDMA2K_ECSFB_REPORT_CFG_VAL as ECSFB_NOT_SUPPORTED  .  LTE_IS_DUAL_RXTX_ALLOWED should not be 1";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         }
         else
         {
            validated = true;
         }
      }
      else if(!strcmp(value.c_str(),"ECSFB_WITHOUT_MEAS"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"ECSFB_WITH_MEAS"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description <<"The allowed values are ECSFB_NOT_SUPPORTED, ECSFB_WITHOUT_MEAS, ECSFB_WITH_MEAS";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }
   RETURN(validated);
}


