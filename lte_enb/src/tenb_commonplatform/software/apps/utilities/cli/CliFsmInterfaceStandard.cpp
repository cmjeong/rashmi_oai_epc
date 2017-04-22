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
#include "CliFsmInterfaceStandard.h"

using namespace std;



void CliFsmInterfaceStandard::FeedbackCompletionResult(shared_ptr<CliExecuteCmdCnf> event)
{
   const char * resultString = event->GetResult();

   if(resultString && strlen(resultString) )
   {
      TRACE_PRINTF_CONSOLE("%s",event->GetResult());
   }
   else
   {
      int cmdStatus = event->GetStatus();

      if (cmdStatus > 0)
      {
         TRACE_PRINTF_CONSOLE("RESULT %d",cmdStatus);
      }
      else if (cmdStatus < 0)
      {
         TRACE_PRINTF_CONSOLE("ERROR %d",cmdStatus);
      }
      else
      {
         TRACE_PRINTF_CONSOLE("OK");
      }
   }

   cout.flush();
}

