///////////////////////////////////////////////////////////////////////////////
//
// Tr069DownloadRequest.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069DownloadRequest.h"

using namespace std;
using namespace threeway;
using namespace tr069;

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
DownloadRequest::DownloadRequest(
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
        std::string localDirectory) :
    tr069::Tr069QueueableEvent( TR069_EVENT(DOWNLOAD_REQUEST), FILE_TRANSFER_FSM ),
    m_commandKey(commandKey),
    m_ftpFile(ftpFile),
    m_ftpTimeout(ftpTimeout),
    m_username(username),
    m_password(password),
    m_fileSize(fileSize),
    m_targetFilename(targetFilename),
    m_successUrl(successUrl),
    m_failureUrl(failureUrl),
    m_localDirectory(localDirectory)
{
    size_t position_of_last_slash = fileUrl.find_last_of("/");

    if(position_of_last_slash != std::string::npos)
    {
        m_remoteDirectory = fileUrl.substr( 0, position_of_last_slash + 1);
        m_filename        = fileUrl.substr( position_of_last_slash + 1, fileUrl.length() );
    }
    else
    {
        m_remoteDirectory = "";
        m_filename        = fileUrl;
    }
}

}
