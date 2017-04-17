///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDualRXTxAllowed.cpp 
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
#include<string.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorDualRXTxAllowed.h"
#include "mib-common/ValidationReferences.h"
//#include "ValidatorDualRXTxAllowed.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


bool ValidatorDualRXTxAllowed::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_CDMA2K_ECSFB_REPORT_CFG_VAL,EcsfbReportCfgValue,fapLteDn);

   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if((EcsfbReportCfgValue=="ECSFB_NOT_SUPPORTED") && (value==1 ))
   { 
       isValid=false;
       ostringstream description;
       description << "To set  DualRXTxAllowed as true ECSFB_REPORT_CFG_VAL should not be   "<<EcsfbReportCfgValue.c_str();
       failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());

   }
    
   RETURN(isValid);
}

