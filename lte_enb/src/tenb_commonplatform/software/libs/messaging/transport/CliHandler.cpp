///////////////////////////////////////////////////////////////////////////////
//
// CliHandler.h
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <fstream>
#include <string>

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <system/StlToString.h>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/TimerEngine.h>
#include <system/Filename.h>
#include <system/Utilities.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliHandler.h"
#include "ApplicationWithMessaging.h"

#define MAX_DIR_LEN 50

using namespace std;
using namespace threeway;

TimerEngineInterface* CliHandler::m_pTimerEngineInterface = 0;

///////////////////////////////////////////////////////////////////////////////
// CliCmdInfo Class Functions
///////////////////////////////////////////////////////////////////////////////

string CliCmdInfo::GetShortHelpText(void)
{
    ostringstream helpText;

    helpText << "\t" << m_shortDescription << endl;

    return(helpText.str());
}

string CliCmdInfo::GetFullHelpText(void)
{
    ostringstream helpText;

    helpText << m_cmdName << endl;
    helpText << "\t" << m_shortDescription << endl;
    helpText << "\t" << m_helpText << endl;

    return(helpText.str());
}

///////////////////////////////////////////////////////////////////////////////
// CliResponse Class Functions
///////////////////////////////////////////////////////////////////////////////

CliResponse::CliResponse () :
m_status(0)
{
}

CliResponse::CliResponse (const string& responseText, s32 status) :
    m_status(status),
    m_responseText(responseText)
{
}

CliResponse::~CliResponse ()
{
}

string CliResponse::GetResponseText(void) const
{
	return(m_responseText);
}

void CliResponse::SetResponseText (const string& newResponseText)
{
	m_responseText = newResponseText;
}

void CliResponse::SetResponseText (const char * newResponseText)
{
	// Preconditions.
	RSYS_ASSERT(newResponseText != NULL);

	m_responseText = newResponseText ;
}

s32 CliResponse::CliResponse::GetStatus (void) const
{
	return(m_status);
}

void CliResponse::SetStatus (s32 newStatus)
{
	m_status = newStatus ;
}

u32 CliResponse::GetResponseLength ()
{
    return m_responseText.length() + sizeof (m_status);
}

///////////////////////////////////////////////////////////////////////////////
// CliHandler Class Functions
///////////////////////////////////////////////////////////////////////////////


CliHandler::CliHandler(const MessagingEntity entity, const char* entityNamespace, const bool includeCommonCmds)
{
    // Preconditions.
    RSYS_ASSERT(entityNamespace != NULL);

    m_namespace = entityNamespace ;
    m_entity = entity ;

    if (includeCommonCmds)
    {
        // iu.trace cmd.
        CliCmdDescriptor cmdDescTraceLev = {
                "tracelev", 0, 2,
                "dev",
                "tracelev [<level> <on|off>]",
                "Set/get trace criticality levels."};

        CliCmdDescriptor cmdDescTraceCat = {
                "tracecat", 0, 2,
                "dev",
                "tracecat [<category> <on|off>]",
                "Set/get trace categories."};

        CliCmdDescriptor cmdDescTraceUdp = {
                "traceudp", 0, 2,
                "dev",
                "traceudp [<dest-ip-address> <dest-port>]",
                "Turn UDP trace logging on/off.  Use 0.0.0.0 to turn off."};

        CliCmdDescriptor cmdDescShowMem = {
                "showmem", 0, 0,
                "dev",
                "showmem",
                "Display the memory usage by this process."};

        CliCmdDescriptor cmdDescShowTimers = {
                "showtimers", 0, 0,
                "dev",
                "showtimers",
                "Display the timer usage by this process."};

        CliCmdDescriptor cmdDescAssert = {
                "assert", 0, 1,
                "dev",
                "assert [<assert-text>]",
                "Force an assert in the code for testing assert mechanisms e.g. logging and watchdog.\n"
                "If <assert-text> is provided this is used in the assert instead of default text."};

        // Function to call with args to execute command.
        RegisterCliCmd(cmdDescTraceLev, &CliHandler::CliCmdTraceLev);
        RegisterCliCmd(cmdDescTraceCat, &CliHandler::CliCmdTraceCat);
        RegisterCliCmd(cmdDescTraceUdp, &CliHandler::CliCmdTraceUdp);
        RegisterCliCmd(cmdDescShowMem, &CliHandler::CliCmdShowMem);
        RegisterCliCmd(cmdDescShowTimers, &CliHandler::CliCmdShowTimers);
        RegisterCliCmd(cmdDescAssert, &CliHandler::CliCmdAssert);
    }
}

CliHandler::~CliHandler()
{
}

void CliHandler::WriteCliCmdFile(const CliCmdDescriptor& cmdDesc)
{
   string val;
   std::string CliFiledDir = "";

   val = getConfigParam("OAM_CONFIG_FILES_DIR", "");
   CliFiledDir = (char *)val.c_str();
   CliFiledDir = CliFiledDir + "/.cli";

   mkdir(CliFiledDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

   Filename cliFilename(CliFiledDir.c_str(), m_namespace, cmdDesc.cmdName);

   ofstream commandFile;
   commandFile.open( cliFilename.c_str(), ios::trunc );

   commandFile << "entity " << (u16)GetEntity() << "\n"
      << "group " << cmdDesc.group << "\n"
      << "min-args " << (u16)cmdDesc.minArgs << "\n"
      << "max-args " << (u16)cmdDesc.maxArgs << "\n"
      << "help " << cmdDesc.help << "\n"
      << "short-description " << cmdDesc.shortDesc << endl;

   commandFile.close();
}

void CliHandler::RegisterCliCmd(const CliCmdDescriptor& cmdDesc,
                                CliCmdCppFunctionPtr cliCmdCppFunctionPtr)
{
    RSYS_ASSERT(cmdDesc.cmdName != NULL);
    RSYS_ASSERT_PRINTF(cmdDesc.group != NULL, "No group for command name %s", cmdDesc.cmdName);
    RSYS_ASSERT_PRINTF(cmdDesc.help != NULL, "No help for command name %s", cmdDesc.cmdName);
    RSYS_ASSERT_PRINTF(cmdDesc.shortDesc != NULL, "No short desc for command name %s", cmdDesc.cmdName);
    RSYS_ASSERT_PRINTF(cliCmdCppFunctionPtr != NULL, "No call back function for command name %s", cmdDesc.cmdName);

    RegisteredCliCmds::const_iterator iter = m_registeredCliCmds.find(cmdDesc.cmdName);

    if(iter != m_registeredCliCmds.end())
    {
        TRACE_MSG_LEV(TRACE_WARNING, "C++ CLI command already registered");
    }

    RegisteredCliCmd registeredCliCmd;

    registeredCliCmd.callback.cliCmdCppFunctionPtr = cliCmdCppFunctionPtr;
    registeredCliCmd.isCppCallback = true;
    registeredCliCmd.cmdDesc = cmdDesc;

    m_registeredCliCmds[cmdDesc.cmdName] = registeredCliCmd;

    WriteCliCmdFile(cmdDesc);
}

void CliHandler::RegisterCliCmd(const CliCmdDescriptor& cmdDesc,
                                CliCmdCFunctionPtr cliCmdCFunctionPtr)
{
    RSYS_ASSERT(cmdDesc.cmdName != NULL);
    RSYS_ASSERT_PRINTF(cmdDesc.group != NULL, "No group for command name %s", cmdDesc.cmdName);
    RSYS_ASSERT_PRINTF(cmdDesc.help != NULL, "No help for command name %s", cmdDesc.cmdName);
    RSYS_ASSERT_PRINTF(cmdDesc.shortDesc != NULL, "No short desc for command name %s", cmdDesc.cmdName);
    RSYS_ASSERT_PRINTF(cliCmdCFunctionPtr != NULL, "No call back function for command name %s", cmdDesc.cmdName);

    RegisteredCliCmds::const_iterator iter = m_registeredCliCmds.find(cmdDesc.cmdName);

    if(iter != m_registeredCliCmds.end())
    {
        TRACE_MSG_LEV(TRACE_WARNING, "C CLI command already registered");
    }

    RegisteredCliCmd registeredCliCmd;

    registeredCliCmd.callback.cliCmdCFunctionPtr = cliCmdCFunctionPtr;
    registeredCliCmd.isCppCallback = false;
    registeredCliCmd.cmdDesc = cmdDesc;

    m_registeredCliCmds[cmdDesc.cmdName] = registeredCliCmd;
}

shared_ptr<CliResponse> CliHandler::ExecuteCliCmd(const string& cmdName, const string& args)
{
    shared_ptr<CliResponse> result (new CliResponse);
    string cmdOutput;

    // Locate cmd in registered commands.
    RegisteredCliCmds::const_iterator iter = m_registeredCliCmds.find(cmdName);
    if(iter != m_registeredCliCmds.end())
    {
        // Command found.
        TRACE("Executing CLI command", cmdName.c_str());
        if(iter->second.isCppCallback)
        {
            vector<string> callbackArgs;
            StringUtils::tokenise(args, callbackArgs);
            string::size_type numArgs = callbackArgs.size();
            if(numArgs < iter->second.cmdDesc.minArgs)
            {
                cmdOutput = "Not enough arguments: ";
                cmdOutput += iter->second.cmdDesc.shortDesc;
                result->SetStatus(CLI_ERROR_TOO_FEW_ARGUMENTS) ;
                result->SetResponseText(cmdOutput) ;
            }
            else if (numArgs > iter->second.cmdDesc.maxArgs)
            {
                cmdOutput = "Too many arguments: ";
                cmdOutput += iter->second.cmdDesc.shortDesc;
                result->SetStatus(CLI_ERROR_TOO_MANY_ARGUMENTS) ;
                result->SetResponseText(cmdOutput) ;
            }
            else
            {
                CliArguments cliArguments;
                for(vector<string>::const_iterator argsIter = callbackArgs.begin(); argsIter != callbackArgs.end(); ++argsIter)
                {
                    CliArgument cliArgument(*argsIter);
                    cliArguments.push_back(cliArgument);
                }
                result = iter->second.callback.cliCmdCppFunctionPtr(cliArguments);
            }
        }
        else
        {
            char cmdOutputTemp[1024];
            s32 status = iter->second.callback.cliCmdCFunctionPtr(args.c_str(), cmdOutputTemp, sizeof(cmdOutputTemp));
            result->SetStatus(status) ;
            result->SetResponseText(cmdOutputTemp) ;
        }
    }
    else
    {
    	result->SetStatus(CLI_ERROR_COMMAND_NOT_FOUND) ;
        result->SetResponseText("*** CLI command not found.") ;
        TRACE_MSG(result->GetResponseText().c_str());
    }

    return(result);
}

void CliHandler::GenerateCliCmdInfo(vector<CliCmdInfo>& cmdInfo) const
{
    cmdInfo.clear();

    if (m_registeredCliCmds.size())
    {
        RegisteredCliCmds::const_iterator iter;
        for (iter = m_registeredCliCmds.begin(); iter != m_registeredCliCmds.end(); iter++)
        {
            CliCmdInfo newCliCmdInfoStruct(iter->second.cmdDesc);

            cmdInfo.push_back(newCliCmdInfoStruct);
        }
    }
}

void CliHandler::SetTimerEngineInterface(TimerEngineInterface* pInterface)
{
    m_pTimerEngineInterface = pInterface;
}

///////////////////////////////////////////////////////////////////////////////
// Static Class Functions
///////////////////////////////////////////////////////////////////////////////

shared_ptr<CliResponse> CliHandler::CliCmdTraceLev(const CliArguments& args)
{
	ostringstream responseString;
	s32 result = CLI_ERROR_NONE ;

	if (args.size() == 0)
	{
	    string availableCat = Trace::GetInstance().GetRegisteredTraceCategoriesString();

        // Show current levels and current and available categories.
        responseString << endl << Trace::GetInstance().ToString();
	}
	else if(args.size() == 2)
	{
		u32 level = 0;
		if(args.at(0).CaselessEquals("verbose"))
		{
			level = TRACE_VERBOSE;
		}
		else if(args.at(0).CaselessEquals("info"))
		{
			level = TRACE_INFO;
		}
        else if(args.at(0).CaselessEquals("stack"))
        {
            level = TRACE_CALL_STACK;
        }

		if(level)
		{
			if(args.at(1).GetBool())
			{
				// Turn this level on.
				Trace::GetInstance().SetTraceLevelOn(level);
			}
			else
			{
				// Turn this level off.
				Trace::GetInstance().SetTraceLevelOff(level);
			}

			// Show new level.
			responseString << Trace::GetInstance().ToString();
		}
		else
		{
			responseString << "<level> argument not recognised.  Requires one of: verbose, info, stack" << endl;
			result = CLI_ERROR_INVALID_ARGUMENT ;
		}
	}
	else if(args.size() > 2)
	{
		responseString << "Too many parameters" << endl;
		result = CLI_ERROR_TOO_MANY_ARGUMENTS ;
	}
	else
	{
		responseString << "Too few parameters" << endl;
		result = CLI_ERROR_TOO_FEW_ARGUMENTS ;
	}

	shared_ptr <CliResponse> response (new CliResponse(responseString.str(), result)) ;
	return response ;
}

shared_ptr<CliResponse> CliHandler::CliCmdTraceCat(const CliArguments& args)
{
    ostringstream responseString;
    s32 result = CLI_ERROR_NONE ;

    if (args.size() == 0)
    {
        // Show current levels and current and available categories.
        responseString << endl << Trace::GetInstance().ToString();
    }
    else if(args.size() == 2)
    {
        // First argument is the category.
        // Look this up against registered categories.
        u32 category = Trace::GetInstance().GetTraceCategoryFromString(args.at(0).c_str());
        if(category)
        {
            if(args.at(1).GetBool())
            {
                Trace::GetInstance().SetTraceCategoriesOn(category);
            }
            else
            {
                Trace::GetInstance().SetTraceCategoriesOff(category);
            }

            // Show new categories.
            responseString << Trace::GetInstance().ToString();
        }
        else
        {
            responseString << "Unknown category: " << args.at(0).c_str();
            result = CLI_ERROR_INVALID_ARGUMENT;
        }
    }
    else if(args.size() > 2)
    {
        responseString << "Too many parameters" << endl;
        result = CLI_ERROR_TOO_MANY_ARGUMENTS ;
    }
    else
    {
        responseString << "Too few parameters" << endl;
        result = CLI_ERROR_TOO_FEW_ARGUMENTS ;
    }

    shared_ptr <CliResponse> response (new CliResponse(responseString.str(), result)) ;
    return response ;
}


shared_ptr<CliResponse> CliHandler::CliCmdTraceUdp(const CliArguments& args)
{
    ostringstream responseString;
    s32 result = CLI_ERROR_NONE ;

    if (args.size() == 0)
    {
        // Show current levels and current and available categories.
        if(Trace::GetInstance().LoggingToUdp())
        {
            u32 ipAddrU32 = Trace::GetInstance().GetUdpLoggingDestAddr();
            IPv4Address ipAddr(ipAddrU32);
            responseString << "UDP logging enabled to " << ipAddr.ToString() << "(" << ipAddrU32 << ") port " << Trace::GetInstance().GetUdpLoggingDestPort();
        }
        else
        {
            responseString << "UDP logging disabled";
        }
    }
    else if(args.size() == 1)
    {
        if((args.at(0).compare("0.0.0.0") == 0) ||
           (args.at(0).compare("0") == 0))
        {
            // Disable UDP logging.
            Trace::GetInstance().DisableUDPLogging();
            responseString << "UDP logging disabled";
        }
        else
        {
            responseString << "IP address and port required";
            result = CLI_ERROR_TOO_FEW_ARGUMENTS;
        }
    }
    else
    {
        if((args.at(0).compare("0.0.0.0") == 0) ||
           (args.at(0).compare("0") == 0) ||
           (args.at(1).GetU32() == 0))
        {
            // Disable UDP logging.
            Trace::GetInstance().DisableUDPLogging();
            responseString << "UDP logging disabled";
        }
        else
        {
            // Enable UDP logging.
            IPv4Address ipAddr(args.at(0).c_str());
            Trace::GetInstance().EnableUDPLogging((u16)args.at(1).GetU32(), ipAddr.Get());

            u32 ipAddrU32 = Trace::GetInstance().GetUdpLoggingDestAddr();
            responseString << "UDP logging enabled to " << ipAddr.ToString() << "(" << ipAddrU32 << ") port " << Trace::GetInstance().GetUdpLoggingDestPort();
        }
    }

    shared_ptr <CliResponse> response (new CliResponse(responseString.str(), result)) ;
    return response ;
}


shared_ptr<CliResponse> CliHandler::CliCmdShowMem(const CliArguments& args)
{
    ostringstream responseString;
    s32 result = CLI_ERROR_NONE ;

    if (args.size() == 0)
    {
        responseString << Trace_GetMemoryUsageStr();
    }
    else if(args.size() > 1)
    {
        responseString << "Too many parameters" << endl;
        result = CLI_ERROR_TOO_MANY_ARGUMENTS ;
    }

    shared_ptr <CliResponse> response (new CliResponse(responseString.str(), result)) ;
    return response ;
}

shared_ptr<CliResponse> CliHandler::CliCmdShowTimers(const CliArguments& args)
{
    ostringstream responseString;
    s32 result = CLI_ERROR_NONE ;

    if (args.size() == 0)
    {
        if (m_pTimerEngineInterface)
        {
            responseString << m_pTimerEngineInterface->ToString();
        }
        else
        {
            responseString << "No timers for this application" << endl;
        }
    }
    else if(args.size() > 1)
    {
        responseString << "Too many parameters" << endl;
        result = CLI_ERROR_TOO_MANY_ARGUMENTS ;
    }

    shared_ptr <CliResponse> response (new CliResponse(responseString.str(), result)) ;
    return response ;
}

shared_ptr<CliResponse> CliHandler::CliCmdAssert(const CliArguments& args)
{
    if (args.size() == 0)
    {
        RSYS_ASSERT_FAIL("Assert forced through CLI");
    }
    else
    {
        RSYS_ASSERT_FAIL("%s", args.at(0).c_str());
    }

    shared_ptr <CliResponse> response (new CliResponse("", CLI_ERROR_NONE)) ;
    return response ;
}

