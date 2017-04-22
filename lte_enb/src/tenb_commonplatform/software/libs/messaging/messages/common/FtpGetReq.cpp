///////////////////////////////////////////////////////////////////////////////
//
// FtpGetReq.cpp
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

#include "FtpGetReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

FtpGetReq::FtpGetReq(
    const std::string & username,
    const std::string & password,
    const std::string & filename,
    const threeway::IPv4Address & remoteIpAddress,
    const std::string & remoteDirectory,
    const threeway::IPv4Address & localIpAddress,
    const std::string & localDirectory) :
        m_username(username),
        m_password(password),
        m_filename(filename),
        m_remoteIpAddress(remoteIpAddress),
        m_remoteDirectory(remoteDirectory),
        m_localIpAddress(localIpAddress),
        m_localDirectory(localDirectory)
{
    ENTER();

    EXIT();
}

s32 FtpGetReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= (MaxFtpGetStringLength * 5) + 8); // measurementIntervalSecs + num group ids + at least one group id

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_username, serialisedData);
    SerialiseIt(m_password, serialisedData);
    SerialiseIt(m_filename, serialisedData);
    SerialiseIt(m_remoteIpAddress.Get(), serialisedData);
    SerialiseIt(m_remoteDirectory, serialisedData);
    SerialiseIt(m_localIpAddress.Get(), serialisedData);
    SerialiseIt(m_localDirectory, serialisedData);

    RETURN(serialisedData - data);
}

bool FtpGetReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    u32 remoteIpAddress;
    u32 localIpAddress;

    DeSerialiseIt(m_username, data, MaxFtpGetStringLength);
    DeSerialiseIt(m_password, data, MaxFtpGetStringLength);
    DeSerialiseIt(m_filename, data, MaxFtpGetStringLength);
    DeSerialiseIt(remoteIpAddress, data);
    DeSerialiseIt(m_remoteDirectory, data, MaxFtpGetStringLength);
    DeSerialiseIt(localIpAddress, data);
    DeSerialiseIt(m_localDirectory, data, MaxFtpGetStringLength);

    m_remoteIpAddress.Set(remoteIpAddress);
    m_localIpAddress.Set(localIpAddress);

    RETURN(true);
}

std::string FtpGetReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "ftpget " << m_username << ":" << m_password << "@" << m_remoteIpAddress.ToString() << "/" << m_remoteDirectory << m_filename << " >> " << m_localIpAddress.ToString() << "/" << m_localDirectory;

    RETURN(stream.str());
}
