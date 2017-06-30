///////////////////////////////////////////////////////////////////////////////
//
// InstallUpdateReq.cpp
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

#include "InstallUpdateReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

InstallUpdateReq::InstallUpdateReq(
        const std::string & updateDir,
        const std::string & updateFilename) :
            m_updateDir(updateDir),
            m_updateFilename(updateFilename)
{
    ENTER();

    EXIT();
}

s32 InstallUpdateReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >=  m_updateDir.length() +
                                 m_updateFilename.length());

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_updateDir, serialisedData);
    SerialiseIt(m_updateFilename, serialisedData);

    RETURN(serialisedData - data);
}

bool InstallUpdateReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_updateDir, data, MaxUpdateReqStringLength);
    DeSerialiseIt(m_updateFilename, data, MaxUpdateReqStringLength);

    RETURN(true);
}

std::string InstallUpdateReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "InstallUpdate " << m_updateDir << " : " << m_updateFilename ;

    RETURN(stream.str());
}
