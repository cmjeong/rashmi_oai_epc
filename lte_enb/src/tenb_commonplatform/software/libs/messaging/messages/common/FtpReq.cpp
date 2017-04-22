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

#include "FtpReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

FtpReq::FtpReq(
    u32 ftpRequestIdentity,
    Command command,
    const std::string & username,
    const std::string & password,
    const std::string & filename,
    const threeway::Fqdn & remoteFqdn,
    const std::string & remoteDirectory,
    const threeway::IPv4Address & localIpAddress,
    const std::string & localDirectory) :
        m_ftpRequestIdentity(ftpRequestIdentity),
        m_command(command),
        m_username(username),
        m_password(password),
        m_filename(filename),
        m_remoteFqdn(remoteFqdn),
        m_remoteDirectory(remoteDirectory),
        m_localIpAddress(localIpAddress),
        m_localDirectory(localDirectory)
{
    ENTER();

    EXIT();
}

s32 FtpReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= (MaxFtpReqStringLength * 5) + 13);

    // Serialise all the members.
    u8* serialisedData = data;
    u8  command = (u8)m_command;

    SerialiseIt(m_ftpRequestIdentity, serialisedData);
    SerialiseIt(command, serialisedData);
    SerialiseIt(m_username, serialisedData);
    SerialiseIt(m_password, serialisedData);
    SerialiseIt(m_filename, serialisedData);
    SerialiseIt(m_remoteFqdn.ToString(), serialisedData);
    SerialiseIt(m_remoteDirectory, serialisedData);
    SerialiseIt(m_localIpAddress.Get(), serialisedData);
    SerialiseIt(m_localDirectory, serialisedData);

    RETURN(serialisedData - data);
}

bool FtpReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    string fqdn;
    u32 localIpAddress;
    u8 command;

    DeSerialiseIt(m_ftpRequestIdentity, data);
    DeSerialiseIt(command, data);
    DeSerialiseIt(m_username, data, MaxFtpReqStringLength);
    DeSerialiseIt(m_password, data, MaxFtpReqStringLength);
    DeSerialiseIt(m_filename, data, MaxFtpReqStringLength);
    DeSerialiseIt(fqdn, data, MaxFtpReqStringLength);
    DeSerialiseIt(m_remoteDirectory, data, MaxFtpReqStringLength);
    DeSerialiseIt(localIpAddress, data);
    DeSerialiseIt(m_localDirectory, data, MaxFtpReqStringLength);

    m_remoteFqdn.Set(fqdn);
    m_localIpAddress.Set(localIpAddress);
    m_command = (Command)command;

    RETURN(true);
}

std::string FtpReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "FtpReq (" << m_ftpRequestIdentity << ") " << (m_command == GET? "Get":"Put" ) << m_username << ":" << m_password << "@" << m_remoteFqdn.ToString() << "/" << m_remoteDirectory << m_filename << " >> " << m_localIpAddress.ToString() << "/" << m_localDirectory;

    RETURN(stream.str());
}
