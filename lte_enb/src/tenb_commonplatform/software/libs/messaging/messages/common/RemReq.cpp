///////////////////////////////////////////////////////////////////////////////
//
// RemReq.cpp
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "RemReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

RemReq::RemReq(const RemReqParams& params) :
    m_remReqParams(params)
{
    ENTER();
    EXIT();
}

RemReq::RemReq()
{
    ENTER();
    EXIT();
}
RemReq::~RemReq()
{
    ENTER();
    EXIT();
}

s32 RemReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= sizeof(RemReqParams));

    const u8 * const dataStart = data;
    m_remReqParams.Serialise(data);
    RETURN(data - dataStart);
}

bool RemReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    m_remReqParams.DeSerialise(data);
    RETURN(true);
}

string RemReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "RemReq:\n\n" << m_remReqParams.ToString();

    RETURN(stream.str());
}
