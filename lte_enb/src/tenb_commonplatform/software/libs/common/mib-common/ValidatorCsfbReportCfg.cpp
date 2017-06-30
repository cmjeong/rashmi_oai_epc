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
#include "ValidatorCsfbReportCfg.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Validator to Ensure values of LTE_CSFB_REPORT_CFG_VAL accepts only CSFB_WITHOUT_MEAS and CSFB_WITH_MEAS
///////////////////////////////////////////////////////////////////////////////

bool ValidatorCsfbReportCfg::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"CSFB_WITHOUT_MEAS"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"CSFB_WITH_MEAS"))
      {
         validated = true;
      }
      else
      {
         ostringstream description;
         description << "CSFB_REPORT_CFG_VAL, value : " <<value << 
            "The allowed values are CSFB_WITHOUT_MEAS and CSFB_WITH_MEAS";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}
