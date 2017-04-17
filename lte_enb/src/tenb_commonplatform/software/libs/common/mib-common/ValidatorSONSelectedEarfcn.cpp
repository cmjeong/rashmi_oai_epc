///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSONSelectedEarfcn.cpp
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

#include "ValidatorSONSelectedEarfcn.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorSONSelectedEarfcn::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = false;
    if( value == 4294967295U )
    {
       isValid = true;
    }
    else
    {
       isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);
    } 

    RETURN(isValid);
}
