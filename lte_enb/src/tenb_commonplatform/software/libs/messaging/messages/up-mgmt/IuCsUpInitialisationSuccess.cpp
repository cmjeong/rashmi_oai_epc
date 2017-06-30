///////////////////////////////////////////////////////////////////////////////
//
// IuCsUpInitialisationSuccess.cpp
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

#include "IuCsUpInitialisationSuccess.h"

using namespace threeway;

IuCsUpInitialisationSuccess::IuCsUpInitialisationSuccess (u8 successDchNumber) :
    m_successDchNumber (successDchNumber)
{
    ENTER();
    EXIT();
}

IuCsUpInitialisationSuccess::~IuCsUpInitialisationSuccess()
{
    ENTER();
    EXIT();
}

s32 IuCsUpInitialisationSuccess::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= SERIALISATION_NUM_BYTES)
    {
        data[0] = m_successDchNumber;
        RETURN (SERIALISATION_NUM_BYTES);
    }

    RETURN(-1);
}

bool IuCsUpInitialisationSuccess::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen == SERIALISATION_NUM_BYTES)
    {
        m_successDchNumber = data[0];
        RETURN(true);
    }

    RETURN(false);
}

std::string IuCsUpInitialisationSuccess::ToString() const
{
    ENTER();

    std::ostringstream stream;
    stream << "IuCsUpInitialisationSuccess: Dch " << (u32) m_successDchNumber;
    RETURN(stream.str());
}
