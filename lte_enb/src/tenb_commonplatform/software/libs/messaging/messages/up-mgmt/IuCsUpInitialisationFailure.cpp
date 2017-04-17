///////////////////////////////////////////////////////////////////////////////
//
// IuCsUpInitialisationFailure.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
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

#include "IuCsUpInitialisationFailure.h"

using namespace threeway;

IuCsUpInitialisationFailure::IuCsUpInitialisationFailure (u8 failedDchNumber) :
    m_failedDchNumber (failedDchNumber)
{
    ENTER();
    EXIT();
}

IuCsUpInitialisationFailure::~IuCsUpInitialisationFailure()
{
    ENTER();
    EXIT();
}

s32 IuCsUpInitialisationFailure::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= SERIALISATION_NUM_BYTES)
    {
        data[0] = m_failedDchNumber;
        RETURN (SERIALISATION_NUM_BYTES);
    }

    RETURN(-1);
}

bool IuCsUpInitialisationFailure::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen == SERIALISATION_NUM_BYTES)
    {
        m_failedDchNumber = data[0];
        RETURN(true);
    }

    RETURN(false);
}

std::string IuCsUpInitialisationFailure::ToString() const
{
    ENTER();

    std::ostringstream stream;
    stream << "IuCsUpInitialisationFailure: Dch " << (u32) m_failedDchNumber;
    RETURN(stream.str());
}
