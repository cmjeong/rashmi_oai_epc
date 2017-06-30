///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// ValidatorPhyCellId.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
// //////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// System Incudes
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <set>
#include <vector>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Local Includes
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#include"ValidatorPhyCellId.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


ValidatorPhyCellId::ValidatorPhyCellId()
{
}
ValidatorPhyCellId::~ValidatorPhyCellId()
{
}

bool ValidatorPhyCellId::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor) 
{
   u32 count = 0;
   ostringstream description;
         
   std::set<u32> phyCellId;
   stringstream ss;

  if(value.size() == 0 )
   {
      description << "numInstances="<< value.size() << " , minimum 1 value required"<< endl;
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_BELOW_MINIMUM, description.str());
      return false;
   }

   if( ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor) )
   {   
   for(u32 i = 0; i < value.size(); i++)
   {
         s32 min = 0;
         s32 max = 0;
         bool isNegative = false;
         char digit[1];
         string str = value.at(i).c_str();
         u32 pos = 0;

         for(u32 dotPos = 0; dotPos < strlen(str.c_str()); dotPos++)
         {
            if((str[dotPos] == '.') && (str[dotPos+1] == '.'))
            {
               pos = dotPos;
               break;
            }
         }

         if(pos > 0)
         {
            for(u32 idx = 0; idx < pos; idx++)
            {
               digit[0] = str[idx];
               if(digit[0]  == '-')
               {
                  isNegative = true;
               }

               min = min*10 + atoi(digit);
            }

            if(isNegative)
            {
               min = min * (-1);
               isNegative = false;
            }
            for(u32 idx = pos+2; idx < strlen(value.at(i).c_str()); idx++)
            {
               digit[0] = str[idx];
               if(digit[0]  == '-')
               {
                  isNegative = true;
               }
               max = max*10 + atoi(digit);
            }

            if(isNegative)
            {
               max = max * (-1);
               isNegative = false;
            }
            s32 index = 0;

            for(index = min; index <= max; index++)
            {
               count++;
               phyCellId.insert(index);
            }
         }
         else
         {
            count++;
         phyCellId.insert(atoi(value.at(i).c_str()));
         }
      ss<<value.at(i);
   }  
   }  
   else
   {
      return false;
   }
   string phyCellIdString(ss.str());
   if((phyCellIdString.length()+value.size())> (512))
   {
       description << "Maximum size of input string : "<< (phyCellIdString.length()+value.size()) << ", Allowed length is " << maxInstances << endl;
       failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
       return false;
   }
   if(count != phyCellId.size())
   {
    description << "Physical Cell Id can not contain duplicate entries";
    failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str()); 
    return false;  
   }   

   return true;
}
