///////////////////////////////////////////////////////////////////////////////
//
// ValidatorFreqBandIndicator.cpp
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
#include "ValidatorFreqBandIndicator.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorFreqBandIndicator::ValidateU32(MibDN fapLteDn,  u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_DUPLEX_MODE,duplexMode,MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP,0));

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);
  
    if (isValid )
    {
        if ((duplexMode == "FDDMode") && (value <= 31))
	{
	  isValid = TRUE;  
	}
	else if ((duplexMode == "TDDMode")&& (value >= 33))
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
        if(duplexMode == "FDDMode")
        {
           description<<" Mode is :"<<duplexMode<<"Please enter Band Indicator value within Range(1,32)";
        }
        else if(duplexMode == "TDDMode")
        {
           description<<" Mode is :"<<duplexMode<<"Please enter Band Indicator value within Range(33,44)";
        } 
        else
        {
           description << value;
        }
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }
    RETURN(isValid);
}
