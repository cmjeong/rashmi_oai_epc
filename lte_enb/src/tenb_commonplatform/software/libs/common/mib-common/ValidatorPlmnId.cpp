///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPlmnId.cpp
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
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>
#include <mobnet/PlmnId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorPlmnId.h"

using namespace std;

bool ValidatorPlmnId::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    if(!ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor))
    {
        return false;
    }

    bool valid = rsysmob::PlmnId::Validate(value);

    if(!valid)
    {
        ostringstream description;
        description << " PLMN ID is invalid.";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
        return false;
    }

    return true;
}
