///////////////////////////////////////////////////////////////////////////////
//
// CliApplication.h
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliApplication.h"
#include "CliFsmInterfaceAte.h"

using namespace std;



void CliFsmInterfaceAte::FeedbackCompletionResult(shared_ptr<CliExecuteCmdCnf> event)
{
    string title;
    string cliResponseStr;
    s16 resultCode = event->GetStatus();
    s32 stringLength;
    if (resultCode > 0)
    {
        title= "RESULT";
    }
    else if (resultCode < 0)
    {
        title= "ERROR";
    }
    else
    {
        title= "OK";
    }

    string result(event->GetResult());
    removeLeadingAndTrailingWhitespace(result);

    ostringstream ossResponse;
    ossResponse << event->GetNamespace() << "." << event->GetCommand() << " " << title << " " << resultCode << " " << result;
    stringLength= ossResponse.str().length();
    cliResponseStr= ossResponse.str();
    TRACE_PRINTF_CONSOLE("%d   %s",stringLength,cliResponseStr.c_str());
}



void CliFsmInterfaceAte::FeedbackCommandRejected(shared_ptr<CliCommand> command)
{
    string title("ERROR");
    string cliResponse;
    string result();
    s32 cliResponseStrLen;
    ostringstream response;
    response << command->GetCommand() << " ERROR -1 Invalid command";
    cliResponseStrLen= response.str().length();
    cliResponse= response.str();
    TRACE_PRINTF_CONSOLE("%d   %s",cliResponseStrLen,cliResponse.c_str());
}




