///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteAntennaPortsCount.cpp
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

#include "ValidatorLteAntennaPortsCount.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorLteAntennaPortsCount::ValidatorLteAntennaPortsCount()
{
    ENTER();

    EXIT();
}

ValidatorLteAntennaPortsCount::~ValidatorLteAntennaPortsCount()
{
    ENTER();

    EXIT();
}

bool ValidatorLteAntennaPortsCount::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    if(value < min)
    {
        ostringstream description;
        description << "value=" << value << ", min=" << min;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_BELOW_MINIMUM, description.str());
        RETURN(false);
    }
    else if(value > max)
    {
        ostringstream description;
        description << "value=" << value << ", max=" << max;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_ABOVE_MAXIMUM, description.str());
        RETURN(false);
    }
    else if(3 == value)
    {
	ostringstream description;
        description << "value=" << value ;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
        RETURN(false);
    }

    RETURN(true);
}
