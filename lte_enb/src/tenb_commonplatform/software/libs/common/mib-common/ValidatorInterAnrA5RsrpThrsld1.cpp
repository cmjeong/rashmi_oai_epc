///////////////////////////////////////////////////////////////////////////////
//
// ValidatorInterAnrA5RsrpThrsld1.cpp
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
#include "ValidatorInterAnrA5RsrpThrsld1.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorInterAnrA5RsrpThrsld1::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_INTER_A5_THRESHOLD_1_RSRP, InterA5RsrpThrsld1,fapLteDn);
    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if( (isValid) && ((InterA5RsrpThrsld1  > 0 ) && (value < InterA5RsrpThrsld1 )))
    {
          isValid = FALSE;
          ostringstream description;
          description << "Inter ANR A5 RSRP THRESHOLD1  (" << value << ") should be greater  than" << 
                " Inter A5 RSRP THRESHOLD1 (" << InterA5RsrpThrsld1 << ")";
          failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
          RETURN(isValid);
    }
    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported  Inter Anr A5 RSRP THRESHOLD1 range(" <<
                " 0 t0 97 )";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
      
