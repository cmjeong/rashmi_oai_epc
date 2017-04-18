/*********************************************************************17*/
///////////////////////////////////////////////////////////////////////////////
//
// UpdateRequests.cpp
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
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UpdateRequests.h"

///////////////////////////////////////////////////////////////////////////////
// FtpRequest Class static data.
///////////////////////////////////////////////////////////////////////////////
u32 SwUpdateOperationRequest::m_nextLocalRequestId = 0 ;

///////////////////////////////////////////////////////////////////////////////
// FtpRequest Class Functions
///////////////////////////////////////////////////////////////////////////////
FtpRequest::FtpRequest(const string& server, const string& user, const string& password,
                             string remoteDir, const string& remoteFilename,
                             const string& localIpAddress,
                             string localDir, const string& localFilename,
                             MessagingEntity requestingEntity,
                             FtpDirection direction,
                             u32 clientRequestId ) :
                                 m_username(user),
                                 m_password (password),
                                 m_server (server),
                                 m_remoteFilename(remoteFilename),
                                 m_localIpAddress (localIpAddress),
                                 m_localFilename(localFilename),
                                 m_direction(direction),
                                 m_requestingEntity(requestingEntity),
                                 m_FtpStatus(FTP_PENDING),
                                 SwUpdateOperationRequest(FTP_REQUEST, clientRequestId)
{
    ENTER();
    if (remoteDir.length())
    {
        if (remoteDir[remoteDir.length()-1] != '/')
        {
            remoteDir.append("/") ;
        }
    }
    m_remoteDir = remoteDir ;

    if (localDir.length())
    {
        if (localDir[localDir.length()-1] != '/')
        {
            localDir.append("/") ;
        }
    }
    m_localDir = localDir ;
    EXIT();
}


FtpRequest::~FtpRequest()
{
    ENTER();
    EXIT();
}


