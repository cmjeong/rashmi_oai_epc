///////////////////////////////////////////////////////////////////////////////
//
// SetTraceMasksReq.cpp
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
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SetTraceMasksReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SetTraceMasksReq::SetTraceMasksReq() :
    m_traceCriticalityMask(0),
    m_traceCategoriesMask(0)
{
    ENTER();
    EXIT();
}

SetTraceMasksReq::SetTraceMasksReq(u32 criticalityMask, u32 categoriesMask) :
    m_traceCriticalityMask(criticalityMask),
    m_traceCategoriesMask(categoriesMask)
{
    ENTER();
    EXIT();
}

s32 SetTraceMasksReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 8);

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_traceCriticalityMask, serialisedData);
    SerialiseIt(m_traceCategoriesMask, serialisedData);

    RETURN(serialisedData - data);
}

bool SetTraceMasksReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    RSYS_ASSERT(dataLen == 8);

    DeSerialiseIt(m_traceCriticalityMask, data);
    DeSerialiseIt(m_traceCategoriesMask, data);

    RETURN(true);
}

std::string SetTraceMasksReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "criticalityMask=" << m_traceCriticalityMask << ", categoriesMask=" << m_traceCategoriesMask;

    RETURN(stream.str());
}
