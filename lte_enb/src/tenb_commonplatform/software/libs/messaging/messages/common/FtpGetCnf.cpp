///////////////////////////////////////////////////////////////////////////////
//
// FtpGetCnf.cpp
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

#include "FtpGetCnf.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

FtpGetCnf::FtpGetCnf(
        bool succeeded,
        const threeway::TimeWrap & startTime,
        const threeway::TimeWrap & stopTime,
        const std::string & failureString ) :
            m_succeeded(succeeded),
            m_startTime(startTime),
            m_stopTime(stopTime),
            m_failureString(failureString)
{
    ENTER();

    EXIT();
}

s32 FtpGetCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= (1 + 4 + 4 + (2 + MaxFtpGetCnfStringLength) ));

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_succeeded, serialisedData);
    SerialiseIt(m_startTime.GetUnixTime(), serialisedData);
    SerialiseIt(m_stopTime.GetUnixTime(), serialisedData);
    SerialiseIt(m_failureString, serialisedData);

    RETURN(serialisedData - data);
}

bool FtpGetCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    u32 startTime;
    u32 stopTime;

    DeSerialiseIt(m_succeeded, data );
    DeSerialiseIt(startTime, data );
    DeSerialiseIt(stopTime, data );
    DeSerialiseIt(m_failureString, data, MaxFtpGetCnfStringLength);

    m_startTime.Set(startTime,0);
    m_stopTime.Set(stopTime,0);

    RETURN(true);
}

std::string FtpGetCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "ftpget(cnf) " << (m_succeeded?"[OK]":"[NOK]") <<  "Started at " << m_startTime.ToString() << ", completed at " << m_stopTime.ToString() << ". " << m_failureString;

    RETURN(stream.str());
}
