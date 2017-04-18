///////////////////////////////////////////////////////////////////////////////
//
// ValidatorS32.cpp
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

#include "ValidatorS32.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorS32::ValidatorS32()
{
    ENTER();

    EXIT();
}

ValidatorS32::~ValidatorS32()
{
    ENTER();

    EXIT();
}

bool ValidatorS32::ValidateS32(MibDN dn,s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    return (ValidateS32(value, min, max, failureDescriptor));
}

bool ValidatorS32::ValidateS32(s32 value, s32 min, s32 max, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    if(value < min)
    {
        ostringstream description;
        description << "value=" << value << ", min=" << min;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_BELOW_MINIMUM, description.str());
        RETURN(false);
    }

    if(value > max)
    {
        ostringstream description;
        description << "value=" << value << ", max=" << max;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_ABOVE_MAXIMUM, description.str());
        RETURN(false);
    }

    RETURN(true);
}
