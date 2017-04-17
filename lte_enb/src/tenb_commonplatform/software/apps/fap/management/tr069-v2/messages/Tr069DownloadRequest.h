///////////////////////////////////////////////////////////////////////////////
//
// Tr069DownloadRequest.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069DownloadRequest_h_
#define __Tr069DownloadRequest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Tr069FtpFile.h"

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////



class DownloadRequest : public tr069::Tr069QueueableEvent
{
public:

    DownloadRequest(
            std::string & commandKey,
            shared_ptr<FtpFile> ftpFile,
            u32 ftpTimeout,
            std::string & fileUrl,
            std::string & username,
            std::string & password,
            u32 fileSize,
            std::string & targetFilename,
            std::string & successUrl,
            std::string & failureUrl,
            std::string localDirectory = "/mnt/tmp/");
    virtual ~DownloadRequest(){}

    const std::string & GetCommandKey() const { return m_commandKey; }
    shared_ptr<FtpFile> GetFtpFile() const { return m_ftpFile; }
    u32 GetFtpTimeout() const { return m_ftpTimeout; }
    const std::string & GetUsername() const { return m_username; }
    const std::string & GetPassword() const { return m_password; }
    u32 GetFileSize() const { return m_fileSize; }
    const std::string & GetTargetFilename() const { return m_targetFilename; }
    const std::string & GetSuccessUrl() const { return m_successUrl; }
    const std::string & GetFailureUrl() const { return m_failureUrl; }
    const std::string & GetLocalDirectory() const { return m_localDirectory; }
    const std::string & GetRemoteDirectory() const { return m_remoteDirectory; }
    const std::string & GetFilename() const { return m_filename; }

private:
    std::string m_commandKey;
    shared_ptr<FtpFile> m_ftpFile;
    u32 m_ftpTimeout;
    std::string m_username;
    std::string m_password;
    u32 m_fileSize;
    std::string m_targetFilename;
    std::string m_successUrl;
    std::string m_failureUrl;
    std::string m_localDirectory;
    std::string m_remoteDirectory;
    std::string m_filename;
};

}

#endif
