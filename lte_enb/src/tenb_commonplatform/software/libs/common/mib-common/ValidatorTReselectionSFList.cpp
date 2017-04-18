///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTReselectionSFList.cpp
//
// See header file for documentation.
//
// 
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

#include"ValidatorTReselectionSFList.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


ValidatorTReselectionSFList::ValidatorTReselectionSFList()
{
}
ValidatorTReselectionSFList::~ValidatorTReselectionSFList()
{
}

bool ValidatorTReselectionSFList::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
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
        if(!m_validator.ValidateU32(value.at(i), minValue, maxValue, failureDescriptor))
        {
            ostringstream description;
            description << "Element " << i << ": " << failureDescriptor.GetDescription();
            failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
            return false;
        }
    }

    return true;
}


