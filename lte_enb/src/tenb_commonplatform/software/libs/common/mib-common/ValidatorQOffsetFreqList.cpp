///////////////////////////////////////////////////////////////////////////////
//
// ValidatorQOffsetFreqList.cpp
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

#include "ValidatorQOffsetFreqList.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorQOffsetFreqList::ValidatorQOffsetFreqList()
{
}

ValidatorQOffsetFreqList::~ValidatorQOffsetFreqList()
{
}

bool ValidatorQOffsetFreqList::ValidateS32Array(const std::vector<s32>& value, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
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
        if(!m_validator.ValidateS32(value.at(i), minValue, maxValue, failureDescriptor))
        {
            ostringstream description;
            description << "Element " << i << ": " << failureDescriptor.GetDescription();
            failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            return false;
        }
    }

    return true;
}
