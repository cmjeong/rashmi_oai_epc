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
#include <string.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliApplication.h"
#include "CliFsmInterfaceCanonical.h"

using namespace std;


void CliFsmInterfaceCanonical::QuittingEntry()
{
    exit(0);
}

void CliFsmInterfaceCanonical::FeedbackCompletionResult(shared_ptr<CliExecuteCmdCnf> event)
{
    const char * resultString = event->GetResult();

    if(resultString && strlen(resultString) )
    {
        // Send result to stdout, rest to stderr.
        TRACE_PRINTF_CONSOLE_WITHOUT_NEWLINE("%s",event->GetResult());
    }

    int cmdStatus = event->GetStatus();

    if (cmdStatus > 0)
    {
        cerr << "RESULT " << cmdStatus << endl;
    }
    else if (cmdStatus < 0)
    {
        cerr << "ERROR " << cmdStatus << endl;
    }
    else
    {
        cerr << "OK" << endl;
    }
}
