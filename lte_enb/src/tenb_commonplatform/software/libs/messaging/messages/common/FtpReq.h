///////////////////////////////////////////////////////////////////////////////
//
// FtpReq.h
//
// Send this to OAM to request an FTP Get.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FtpReq_h_
#define __FtpReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/Fqdn.h>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FtpReq : public threeway::Serialisable
{
public:
    typedef enum Command_tag
    {
        PUT,
        GET
    } Command;

    static const unsigned short MaxFtpReqStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    FtpReq() :
        m_ftpRequestIdentity(0),
        m_command(PUT),
        m_username(""),
        m_password(""),
        m_filename(""),
        m_remoteFqdn(),
        m_remoteDirectory(""),
        m_localIpAddress("0.0.0.0"),
        m_localDirectory("")
    {};

    /**
     * Construct a FTP Get request message.
     */
    FtpReq(
        u32 ftpRequestIdentity,
        Command command,
        const std::string & username,
        const std::string & password,
        const std::string & filename,
        const threeway::Fqdn & remoteFqdn,
        const std::string & remoteDirectory, // with trailing "/"
        const threeway::IPv4Address & localIpAddress,
        const std::string & localDirectory // with trailing "/"
        );

    virtual ~FtpReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_FTP_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    u32 GetFtpRequestIdentity() const { return m_ftpRequestIdentity; }
    Command GetCommand() const { return m_command; }
    const std::string & GetUsername() const { return m_username; }
    const std::string & GetPassword() const { return m_password; }
    const std::string & GetFilename() const { return m_filename; }
    const threeway::Fqdn & GetRemoteFqdn() const { return m_remoteFqdn; }
    const std::string & GetRemoteDirectory() const { return m_remoteDirectory; }
    const threeway::IPv4Address & GetLocalIpAddress() const { return m_localIpAddress; }
    const std::string & GetLocalDirectory() const { return m_localDirectory; }

private:

    u32 m_ftpRequestIdentity;
    Command m_command;
    std::string m_username;
    std::string m_password;
    std::string m_filename;
    threeway::Fqdn m_remoteFqdn;
    std::string m_remoteDirectory;
    threeway::IPv4Address m_localIpAddress;
    std::string m_localDirectory;
};

#endif
