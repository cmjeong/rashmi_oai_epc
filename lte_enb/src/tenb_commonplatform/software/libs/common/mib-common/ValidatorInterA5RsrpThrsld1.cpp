///////////////////////////////////////////////////////////////////////////////
//
// ValidatorInterA5RsrpThrsld1.cpp
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
#include "ValidatorInterA5RsrpThrsld1.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorInterA5RsrpThrsld1::ValidateU32(MibDN Dn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_1_RSRP,InterAnrA5RsrpThrsld1,Dn);
    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if( (isValid) && ((InterAnrA5RsrpThrsld1 > 0 ) && (value > InterAnrA5RsrpThrsld1 )))
    {
          isValid = FALSE;
          ostringstream description;
          description << "Inter A5 RSRP THRESHOLD1  (" << value  << ") should be less  than" << 
                " Inter ANR A5 RSRP THRESHOLD1 (" << InterAnrA5RsrpThrsld1 << ")";
          failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
          RETURN(isValid);
    }
    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported Inter A5 RSRP THRESHOLD1  range(" <<
                " 0 t0 97 )";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
      
