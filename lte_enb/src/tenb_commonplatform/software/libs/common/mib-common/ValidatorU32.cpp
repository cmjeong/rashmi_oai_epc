///////////////////////////////////////////////////////////////////////////////
//
// ValidatorU32.cpp
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

#include "ValidatorU32.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorU32::ValidatorU32()
{
    ENTER();

    EXIT();
}

ValidatorU32::~ValidatorU32()
{
    ENTER();

    EXIT();
}

bool ValidatorU32::ValidateU32(MibDN fapLteDn,u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    return (ValidateU32(value,min,max,failureDescriptor));
}
bool ValidatorU32::ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    if(value < min)
    {
        ostringstream description;
        description << "NotValidValue " << value << ", Supported value should be within " << min << " to "<< max << " range." <<endl;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_BELOW_MINIMUM, description.str());
        RETURN(false);
    }

    if(value > max)
    {
        ostringstream description;
        description << "NotValidValue " << value << ", Supported value should be within " << min << " to "<< max << " range." <<endl;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_ABOVE_MAXIMUM, description.str());
        RETURN(false);
    }

    RETURN(true);
}
