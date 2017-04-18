///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdProgressInd.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sstream>

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliExecuteCmdProgressInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CliExecuteCmdProgressInd::CliExecuteCmdProgressInd(const char * progressInfo) :
    m_progressInfo(progressInfo)
{
    ENTER();
    EXIT();
}

s32 CliExecuteCmdProgressInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes > m_progressInfo.size() + 4);

    u8 * serialisedData = data;
    SerialiseIt(m_progressInfo, serialisedData);

    RETURN(serialisedData - data);
}

bool CliExecuteCmdProgressInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_progressInfo, data, 1024 /* fairly arbitrary max string len */);

    RETURN(true);
}

string CliExecuteCmdProgressInd::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "CliExecuteCmdProgressInd: progressInfo=" << m_progressInfo;

    RETURN(stream.str());
}
