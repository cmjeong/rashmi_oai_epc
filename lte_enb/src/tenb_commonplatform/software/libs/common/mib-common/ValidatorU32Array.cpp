///////////////////////////////////////////////////////////////////////////////
//
// ValidatorU32Array.cpp
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

#include "ValidatorU32Array.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorU32Array::ValidatorU32Array()
{
}

ValidatorU32Array::~ValidatorU32Array()
{
}

bool ValidatorU32Array::ValidateU32Array(MibDN Dn,const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
     return (ValidateU32Array(value,minValue,maxValue,maxInstances,failureDescriptor));
}

bool ValidatorU32Array::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
    if(value.size() > maxInstances)
    {
        ostringstream description;
        description << "numInstances=" << value.size() << ", maxInstances=" << maxInstances;
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
        return false;
    }

    for(u32 i = 0; i < value.size(); i++)
    {
        if(!m_validatorU32.ValidateU32(value.at(i), minValue, maxValue, failureDescriptor))
        {
            ostringstream description;
            description << "Element " << i << ": " << failureDescriptor.GetDescription();
            failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            return false;
        }
    }

    return true;
}
