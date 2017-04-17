///////////////////////////////////////////////////////////////////////////////
//
// SwUpdateCli.cpp
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
#include <string>
#include <set>
#include <stdio.h>

#include <boost/shared_ptr.hpp>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/common/FtpGetReq.h>
#include <messaging/messages/common/FtpPutReq.h>
#include <messaging/messages/common/FtpReq.h>
#include <messaging/messages/common/FtpAbort.h>
#include <messaging/messages/common/ApplyUpdateReq.h>
#include <messaging/messages/common/RevertUpdateReq.h>
#include <messaging/messages/common/InstallUpdateReq.h>
#include <messaging/messages/common/InstallUpdateCnf.h>
#include <messaging/messages/common/ActivateUpdateReq.h>
#include <messaging/messages/common/ActivateUpdateCnf.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SwUpdateApplication.h"
#include "SwUpdateCli.h"
#ifdef PRODUCT_generic
extern "C" void __gcov_flush(void);
#endif


using namespace std;
using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Structs
///////////////////////////////////////////////////////////////////////////////

struct NamePair
{
    std::string left;
    std::string right;
};

void FtpCli::RegisterFtpCliCmds(shared_ptr<CliHandler> ftpCliHandler)
{
    ENTER();

    CppCliPair cppFtpCliPairs[] =
    {
#ifdef PRODUCT_generic
        {
            {
                "coverage", 0, 0, // min/max arguments
                "ate",
                "coverage",
                "Get coverage."
            },
            &CliCmdFtpGetCoverage,
        },
#endif
	{
            {
                "req", 9, 9,
                "ate",
                "req [Get|Put] <remoteIpAddress> <remoteDirectory> <filename> <localIpAddress> <localDirectory> <username> <password> <Request ID (u32)",
                "Send an FTP request message."
            },
            &CliCmdFtpReq,
        },
        {
            {
                "getupdate", 2, 4,
                "dev",
                "getupdate <remoteIpAddress> <update file pathname> [<username> <password>]",
                "FTP an update image to the default update location."
            },
            &CliCmdFtpGetUpdate,
        },
        {
            {
                "abort", 2, 2,
                "ate",
                "abort <Client Request ID (u32)> <Update Request ID (u32)> ",
                "Send an FTP abort message."
            },
            &CliCmdFtpAbort,
        },
        {
            {
                "status", 0, 1,
                "ate",
                "status [extended]",
                "Check status of FTP requests."
            },
            &CliCmdFtpStatus,
        }
    } ;

    for (u32 i = 0; i < sizeof(cppFtpCliPairs) / sizeof(cppFtpCliPairs[0]); i++)
    {
    	ftpCliHandler->RegisterCliCmd(cppFtpCliPairs[i].descriptor, cppFtpCliPairs[i].cppFuncPtr);
    }

    EXIT();
}

shared_ptr<CliResponse> FtpCli::CliCmdFtpReq(const CliArguments& args)
{
    /*************************************************************************
     * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
     * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
     *************************************************************************/

    ostringstream responseString;
    s32 result = CLI_ERROR_NONE ;

    FtpRequest::FtpDirection command (FtpRequest::FTP_DIRECTION_INVALID);

    if (args[0].CaselessEquals("Get"))
    {
        command = FtpRequest::FTP_DIRECTION_GET ;
    }
    else if (args[0].CaselessEquals("Put"))
    {
        command = FtpRequest::FTP_DIRECTION_PUT ;
    }

    shared_ptr<FtpRequest> ftpRequest ( new FtpRequest ( args[1], // Remote IP address
                                                               args[6], // Username
                                                               args[7], // Password
                                                               args[2], // Remote Directory
                                                               args[3], // Filename
                                                               args[4], // Local IP address,
                                                               args[5], // Local Directory
                                                               args[3], // Filename
                                                               ENTITY_SW_UPDATE,
                                                               command,
                                                               args[8].GetU32() // Request ID
    ));

    SwUpdateApplication::GetInstance().GetSwUpdateEngine().Enqueue(ftpRequest);
    responseString << "Sent FTP request to UPDATE: FtpReq " << ftpRequest->GetLocalRequestId();
    shared_ptr<CliResponse> response (new CliResponse (responseString.str(), result)) ;
    return response ;
}

shared_ptr<CliResponse> FtpCli::CliCmdFtpGetUpdate(const CliArguments& args)
{
    s32 result = CLI_ERROR_NONE ;
    ostringstream responseString;
    string remotedir("") ;
    string filename("") ;
    string username("anonymous") ;
    string password("fap-update-download@Radisys.com") ;

    size_t filenameSepIndex = args[1].find_last_of ('/') ;
	if (filenameSepIndex == string::npos)
	{
		filename = args[1] ;
	}
	else
	{
		filename = args[1].substr(filenameSepIndex+1) ;
		remotedir = args[1].substr(0, filenameSepIndex) ;
    }

	if (args.size() > 2)
	{
		username = args[2];
		if (args.size() > 3)
    	{
    		password = args[3];
    	}
	}

    shared_ptr<FtpRequest> ftpRequest ( new FtpRequest ( args[0], // Remote IP address
                                                               username, // Username
                                                               password, // Password
                                                               remotedir, // Remote Directory
                                                               filename, // Filename
                                                               "0.0.0.0", // Local IP address,
                                                               "/tmp/updates", // Local Directory
                                                               filename, // Filename
                                                               ENTITY_SW_UPDATE,
                                                               FtpRequest::FTP_DIRECTION_GET,
                                                               0 // Request ID
    ));

    SwUpdateApplication::GetInstance().GetSwUpdateEngine().Enqueue(ftpRequest);
    responseString << "Sent FTP request to update engine: FtpReq " << ftpRequest->GetLocalRequestId();
    shared_ptr<CliResponse> response (new CliResponse (responseString.str(), result)) ;

    return response ;
}

shared_ptr<CliResponse> FtpCli::CliCmdFtpAbort(const CliArguments& args)
{
    /*************************************************************************
     * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
     * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
     *************************************************************************/

    s32 result = CLI_ERROR_NONE ;
    ostringstream responseString;
    shared_ptr<FtpAbort> abortReq (new FtpAbort(args[0].GetU32(), // Client Request ID
                                                args[1].GetU32() // Server Request ID
                                               ));
    SwUpdateApplication::GetInstance().SendMessage(*abortReq, ENTITY_SW_UPDATE, ENTITY_SW_UPDATE);
    responseString << "Sent FTP Abort request to UPDATE: " << abortReq->ToString();
    shared_ptr<CliResponse> response (new CliResponse (responseString.str(), result)) ;

    return response ;
}

shared_ptr<CliResponse> FtpCli::CliCmdFtpStatus(const CliArguments& args)
{
    /*************************************************************************
     * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
     * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
     *************************************************************************/

    s32 result = CLI_ERROR_NONE ;

    bool extended = false ;

    if ((args.size()) && (args[0].CaselessEquals("extended")))
    {
        extended = true ;
    }

    string responseString = SwUpdateApplication::GetInstance().GetFtpStatusString(extended);
    shared_ptr<CliResponse> response (new CliResponse (responseString, result)) ;

    return response ;
}

#ifdef PRODUCT_generic
shared_ptr<CliResponse> FtpCli::CliCmdFtpGetCoverage(const CliArguments& args)
{
    s32 result = CLI_ERROR_NONE;
    ostringstream responseStream ;
    
    responseStream << "Generating coverage for Ftp";
    __gcov_flush();
    shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;
    
    return response;
}
#endif 
