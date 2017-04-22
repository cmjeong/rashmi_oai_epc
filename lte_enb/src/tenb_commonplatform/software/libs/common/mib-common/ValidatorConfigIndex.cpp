///////////////////////////////////////////////////////////////////////////////
//
// ValidatorConfigIndex.cpp
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
#include "ValidatorConfigIndex.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorConfigIndex::ValidateStringArray(MibDN fapLteDn, const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_TDD_SPECIAL_SUB_FRAME_PATTERNS,SpclSfCfg,fapLteDn );

   bool isValid = false;

   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {
      isValid = true;
      if((SpclSfCfg >= 0 ) && ( SpclSfCfg <= 4))
      {
         for(u32 i = 0; i < value.size(); i++)
         {
            if((atoi(value.at(i).c_str()) >= 48) && (atoi(value.at(i).c_str()) <= 57))
            {
               isValid = FALSE;
               ostringstream description;
               description << "ConfigIndex should not be 48 - 57";
               failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
               RETURN(isValid);
            }
         }
      }
   }
   RETURN(isValid);
}
      
