///////////////////////////////////////////////////////////////////////////////
//
// ValidatorStringArray.cpp
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

#include "ValidatorStringArray.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

#define MAX_S32_VAL 2147483647

ValidatorStringArray::ValidatorStringArray()
{
    ENTER();

    EXIT();
}

ValidatorStringArray::~ValidatorStringArray()
{
    ENTER();

    EXIT();
}

bool ValidatorStringArray::ValidateStringArray(MibDN Dn,const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   return (ValidateStringArray(value,minLength,maxLength,minValue,maxValue,maxInstances,failureDescriptor));
}

bool ValidatorStringArray::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   if(value.size() > maxInstances)
   {
      ostringstream description;
      description << "numInstances=" << value.size() << ", maxInstances=" << maxInstances;
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
      RETURN(false);
   }

   for(u32 i = 0; i < value.size(); i++)
   {
      if(!m_validatorString.ValidateString(value.at(i), minLength, maxLength, failureDescriptor))
      {
         ostringstream description;
         description << "Element " << i << ": " << failureDescriptor.GetDescription();
         failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
         RETURN(false);
      }

      if((minValue != MAX_S32_VAL)||(maxValue != MAX_S32_VAL))
      {
         s32 min = 0,max = 0;   
         string strVal = value.at(i).c_str();
         static const char * VALID_STRING_CHARS = "0123456789.-";
         string::size_type p = strVal.find_first_not_of(VALID_STRING_CHARS);
         bool valid = false;
         if(p == string::npos)
         {
            size_t found = strVal.find('.');
            
            if((found != std::string::npos)&&(found != 0))
            {
               min = atoi(strVal.substr(0,found).c_str());
               std::size_t foundE = strVal.find_last_of(".");
               if((foundE != std::string::npos)&&(foundE == found+1))
               {
                  max = atoi(strVal.substr(foundE+1).c_str());
                  valid = true;
               }
            }
            else
            {
               if(found != 0)
               {
                  min = atoi(value.at(i).c_str());
                  max = atoi(value.at(i).c_str());
                  valid = true;
               }
            } 
         }
        
         if((!valid)||(min < minValue)||(max > maxValue))
         {
            ostringstream description;
            description << "out of range value, range is: " << minValue << "-" << maxValue;
            failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            return(false);
         }
         
     }

   }

   RETURN(true);
}
