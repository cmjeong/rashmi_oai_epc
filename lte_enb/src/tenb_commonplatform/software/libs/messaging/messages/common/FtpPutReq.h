///////////////////////////////////////////////////////////////////////////////
//
// FtpPutReq.h
//
// Send this to OAM to request an FTP Get.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FtpPutReq_h_
#define __FtpPutReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FtpPutReq : public threeway::Serialisable
{
public:
    static const unsigned short MaxFtpPutStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    FtpPutReq() {};

    /**
     * Construct a Ftp Put request message.
     */
    FtpPutReq(
        const std::string & username,
        const std::string & password,
        const std::string & filename,
        const threeway::IPv4Address & remoteIpAddress,
        const std::string & remoteDirectory,
        const threeway::IPv4Address & localIpAddress,
        const std::string & localDirectory);

    virtual ~FtpPutReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_FTP_PUT_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    const std::string & GetUsername() const { return m_username; }
    const std::string & GetPassword() const { return m_password; }
    const std::string & GetFilename() const { return m_filename; }
    const threeway::IPv4Address & GetRemoteIpAddress() const { return m_remoteIpAddress; }
    const std::string & GetRemoteDirectory() const { return m_remoteDirectory; }
    const threeway::IPv4Address & GetLocalIpAddress() const { return m_localIpAddress; }
    const std::string & GetLocalDirectory() const { return m_localDirectory; }

private:

    std::string m_username;
    std::string m_password;
    std::string m_filename;
    threeway::IPv4Address m_remoteIpAddress;
    std::string m_remoteDirectory;
    threeway::IPv4Address m_localIpAddress;
    std::string m_localDirectory;
};

#endif
