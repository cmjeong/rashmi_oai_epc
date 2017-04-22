///////////////////////////////////////////////////////////////////////////////
//
// ValidatorReportingThreshold.cpp
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

#include "ValidatorReportingThreshold.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorReportingThreshold::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

    if ( isValid )
    {
        switch ( value )
        {
        case 8:
        case 16:
        case 32:
        case 64:
        case 128:
        case 256:
        case 512:
        case 1024:
        case 2048:
        case 3072:
        case 4096:
        case 6144:
        case 8192:
        case 12288:
        case 16384:
        case 24576:
        case 32768:
        case 49152:
        case 65536:
        case 98304:
        case 131072:
        case 196608:
        case 262144:
        case 393216:
        case 524288:
        case 786432:
                isValid = true;
                break;
            default:
                isValid = false;
                break;
        }
    }

    if(!isValid)
    {
        ostringstream description;
        description << "NotValidValue (" << value << ") supported thresholds are (" <<
                "8, 16, 32, 64, 128, 256, 512, 1024, 2048, 3072, 4096, 6144, 8192, " <<
                "12288, 16384, 24576, 32768, 49152, 65536, 98304, 131072, 196608, " <<
                "262144, 393216, 524288, 786432)";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
    }

    RETURN(isValid);
}
