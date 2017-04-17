///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIratCidList.cpp
//
// See header file for documentation.
//
//
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "mib-common/ValidationReferences.h"
#include "ValidatorIratCidList.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorIratCidList::ValidateU32Array(MibDN fapLteDn, const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RNCID,RncId,fapLteDn);
   bool isValid = false;
   if(value.size() > maxInstances)
   {
      ostringstream description;
      description << "numInstances=" << value.size() << ", maxInstances=" << maxInstances;
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
      return false;
   }

   if(RncId.empty())
   {
      isValid = true;
   }
   else
   {
      if(RncId.size() == value.size())
      {
         for(u32 i = 0; i < value.size(); i++)
         {
            isValid = ValidatorU32::ValidateU32(value.at(i), minValue, maxValue, failureDescriptor);

            if (isValid )
            {
               if((RncId.at(i) < 4096) || (RncId.at(i) >= 4096 && value.at(i) < 4096))
               {
                  isValid = true;
               }
               else
               {
                  ostringstream description;
                  description << "NotValidValue : Cid value (" << value.at(i) << 
                     ") When RncId is greater than 4096, Cid has to be lesser than 4096";
                  failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str()); 
                  isValid = false;
                  break;
               } 
            }
         }
      }
      else
      {
         ostringstream description;
         description << "Number of Instances of RncId and Cid do not match"<<
            "RncId Size= " << RncId.size() << " Value Size = " << value.size();
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str()); 
         isValid = false;
      } 
   }

   return isValid;
}

