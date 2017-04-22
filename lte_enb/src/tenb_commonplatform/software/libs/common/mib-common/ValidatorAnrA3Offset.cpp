///////////////////////////////////////////////////////////////////////////////
//
// ValidatorAnrA3Offset.cpp
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
#include "ValidatorAnrA3Offset.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorAnrA3Offset::ValidateS32(MibDN fapLteDn, s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_INTRA_HO_A3_OFFSET,HoA3Offset,fapLteDn);
    bool isValid = ValidatorS32::ValidateS32(value, min, max, failureDescriptor);

    if( (isValid) && ((HoA3Offset > 0 ) && (value > HoA3Offset )))
    {
          isValid = FALSE;
          ostringstream description;
          description << "Anr A3 Offset  (" << value << ") should be less  than" << 
                " HO A3 Offset (" << HoA3Offset << ")";
          failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
          RETURN(isValid);
    }
    if(!isValid)
    {
        ostringstream description;
        description << "supported A3Offset range -30 to 30";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
      
