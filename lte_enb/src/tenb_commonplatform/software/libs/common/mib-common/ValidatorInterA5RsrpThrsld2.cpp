///////////////////////////////////////////////////////////////////////////////
//
// ValidatorInterA5RsrpThrsld2.cpp
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
#include "ValidatorInterA5RsrpThrsld2.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorInterA5RsrpThrsld2::ValidateU32(MibDN Dn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_2_RSRP,InterAnrA5RsrpThrsld2,Dn);
    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if( (isValid) && ((InterAnrA5RsrpThrsld2 > 0 ) && (value < InterAnrA5RsrpThrsld2 )))
    {
          isValid = FALSE;
          ostringstream description;
          description << "Inter A5 RSRP THRESHOLD2  (" << value  << ") should be greater  than" << 
                " Inter ANR A5 RSRP THRESHOLD2 (" << InterAnrA5RsrpThrsld2 << ")";
          failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
          RETURN(isValid);
    }
    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported Inter A5 RSRP THRESHOLD2  range(" <<
                " 0 t0 97 )";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
      
