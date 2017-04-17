///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteBandsSupported.cpp
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

#include "ValidatorLteBandsSupported.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorLteBandsSupported::ValidatorLteBandsSupported()
{
}

ValidatorLteBandsSupported::~ValidatorLteBandsSupported()
{
}

bool ValidatorLteBandsSupported::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
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
	else
	{
		if((value.at(i) > 21)&&(value.at(i) < 33)) 
		{
            		ostringstream description;
            		description << "Element " << i << ": " << failureDescriptor.GetDescription();
            		failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            		return false;
		}
	}
    }

    return true;
}
