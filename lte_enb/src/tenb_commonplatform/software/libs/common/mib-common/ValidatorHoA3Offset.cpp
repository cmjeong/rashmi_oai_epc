///////////////////////////////////////////////////////////////////////////////
//
// ValidatorHoA3Offset.cpp
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
#include "ValidatorHoA3Offset.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorHoA3Offset::ValidateS32(MibDN fapLteDn, s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    bool isValid = ValidatorS32::ValidateS32(value, min, max, failureDescriptor);
    
    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_INTRA_ANR_A3_OFFSET,AnrA3Offset,fapLteDn);
    if( (isValid) && (value < AnrA3Offset))
    {
          isValid = FALSE;
          ostringstream description;
          description << "HO A3 Offset  (" << value << ") should be greater  than" << 
                " ANR A3 Offset (" << AnrA3Offset << ")";
          failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
          RETURN(isValid);
    }
    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported A3Offset range(" <<
                " -30 t0 30 )";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
      
