///////////////////////////////////////////////////////////////////////////////
//
// MibAttrValidationFailure.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttrValidationFailure.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

s32 MibAttrValidationFailures::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 4);

    const u8* const dataStart = data;

    // Serialise the number of failures.
    u32 numFailures = size();
    SerialiseIt(numFailures, data);

    // Loop through failures and serialise each.
    for(const_iterator iter = begin(); iter != end(); ++iter)
    {
        u32 spaceReqd = 4 + 4 + 2 + iter->GetDescription().length();
        RSYS_ASSERT(spaceReqd <= (dataMaxBytes - (data - dataStart)));

        SerialiseIt((u32)(iter->GetMibAttributeId()), data); // 4
        SerialiseIt(iter->GetDescription(), data); // Variable
        SerialiseIt((u32)iter->GetCause(), data); // 4
    }

    RETURN(data - dataStart);
}

bool MibAttrValidationFailures::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    const u8* const dataStart = data;

    // Serialise the number of failures.
    u32 numFailures = size();
    DeSerialiseIt(numFailures, data);

    // Loop through failures and serialise each.
    for(u32 i = 0; i < numFailures; i++)
    {
        u32 id;
        DeSerialiseIt(id, data); // 4

        string description;
        DeSerialiseIt(description, data, 2560); // Variable

        u32 cause;
        DeSerialiseIt(cause, data); // 4

        MibAttrValidationFailure failure;
        failure.SetMibAttributeId((MibAttributeId)id);
        failure.Set((ValidationFailureDescriptor::ValidationFailureCause)cause, description);

        push_back(failure);
    }

    RSYS_ASSERT(data == (dataStart + dataLen));

    RETURN(true);
}

std::string MibAttrValidationFailures::ToString() const
{
    ENTER();

    ostringstream stream;
    for(const_iterator iter = begin(); iter != end(); ++iter)
    {
        stream << iter->ToString() << std::endl;
    }

    RETURN(stream.str());
}
