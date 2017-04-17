///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT304IRAT.cpp
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

#include "ValidatorT304IRAT.h"
#include "mib-common/ValidationReferences.h"	 	 
 	 	 
#define DELAY 100

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorT304IRAT::ValidateU32Array(MibDN Dn, const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();
   bool isPresent = ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_GERAN_T304_EXP_WAIT_TMR, t304ExpWaitTmr, Dn);
   bool isValid = false;

   if( ValidatorU32Array::ValidateU32Array(value, min, max, maxInstances, failureDescriptor) )
   {
      for(u32 i = 0; i < value.size(); i++)
      {
         switch ( value.at(i) )
         {
            case 100:
            case 200:
            case 500:
            case 1000:
            case 2000:
            case 4000:
            case 8000:
               isValid = true;
               break;
            default:
               isValid = false;
               break;
         }

         if(!isValid)
         {
            ostringstream description;
            description << "Supported T304IRAT are (" <<
               "100, 200, 500, 1000, 2000, 4000, 8000)";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         }
         else	 	 
         {
            if( isPresent)
            {    /* VENKI */       
               if( t304ExpWaitTmr < value.at(i) + DELAY )	 	 
               {	 	 
                  isValid = false;
                  ostringstream description;	 	 
                  description << "LTE_GERAN_T304_EXP_WAIT_TMR should be atleast 100 + LTE_T304IRAT "<<
                                    t304ExpWaitTmr<<"value"<<value.at(i);	 	 
                  failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());	 	 
               }
            }
         }
         if(!isValid)
         {
            break;
         }
      }
   }

   RETURN(isValid);
}
