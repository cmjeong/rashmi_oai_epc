///////////////////////////////////////////////////////////////////////////////
//
// Tr069UploadRequest.cpp
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
#include "Tr069UploadRequest.h"

using namespace std;
using namespace threeway;
using namespace tr069;

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
UploadRequest::UploadRequest(
        const std::string & commandKey,
        shared_ptr<FtpFile> ftpFile,
        u32 ftpTimeout,
        const std::string & fileUrl,
        const std::string & username,
        const std::string & password,
        const std::string & localDirectory) :
    tr069::Tr069QueueableEvent( TR069_EVENT(UPLOAD_REQUEST), FILE_TRANSFER_FSM ),
    m_commandKey(commandKey),
    m_ftpFile(ftpFile),
    m_ftpTimeout(ftpTimeout),
    m_username(username),
    m_password(password),
    m_localDirectory(localDirectory)
{
    size_t position_of_last_slash = fileUrl.find_last_of("/");

    if(position_of_last_slash != std::string::npos)
    {
        m_remoteDirectory = fileUrl.substr( 0, position_of_last_slash + 1);
        m_filename        = fileUrl.substr( position_of_last_slash + 1 );
    }
    else
    {
        m_remoteDirectory = "./";
        m_filename        = fileUrl;
    }
}

}
