///////////////////////////////////////////////////////////////////////////////
//
// ValidatorUtraTddBandIndicator.cpp
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
#include <iostream>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "mib-common/ValidationReferences.h"
#include "ValidatorUtraTddBandIndicator.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorUtraTddBandIndicator::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_TDS_CDMA_UTRATDD_MODE,utraTddMode,fapLteDn);

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);
  
    if (isValid )
    {
      // if(((0 == strcmp(utraTddMode.c_str(),"UTRA_TDD_128")) && (value <= 6)))
       if((utraTddMode == "UTRA_TDD_128") && (value <= 6))
       {
          isValid = TRUE;  
       }
       else if((utraTddMode == "UTRA_TDD_384") && (value <= 4))
       {
          isValid = TRUE;
       }
       else if((utraTddMode == "UTRA_TDD_768") && (value <= 4))
       {
          isValid = TRUE;
       }
       else
       {
          isValid = FALSE;
       }
    }
    if(!isValid)
    {
        ostringstream description;
        if(utraTddMode == "UTRA_TDD_128")
        {
           description<<"NotValidValue (" <<value <<")"<<" Mode is :"<<utraTddMode<<"Please enter Band Indicator value within Range(1,6)";
        }
        else if((utraTddMode == "UTRA_TDD_384") || (utraTddMode == "UTRA_TDD_768"))
        {
           description<<"NotValidValue (" <<value <<")"<<" Mode is :"<<utraTddMode<<"Please enter Band Indicator value within Range(1,4)";
        } 
        else
        {
           description<<"NotValidValue ("<<value<<")"<<" Please enter utra tdd mode, then set the Band Indicator";
        }
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }
    RETURN(isValid);
}
