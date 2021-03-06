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

#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <arpa/inet.h>

#include <ctype.h>
#include <system/Trace.h>
#include <system/SerialisationIds.h>
#include <system/TimerEngine.h>
#include <system/ThreadWithQueue.h>
#include <system/Filename.h>
#include <system/StringUtils.h>
#include <messaging/transport/CliHandler.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <messaging/messages/cli/CliExecuteCmdReq.h>
#include <messaging/messages/cli/CliExecuteCmdCnf.h>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/cli/CliExecuteCmdProgressInd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliEvents.h"
#include "CliApplication.h"
#include "CliCmdFileMgr.h"

#include "CliFsm.h"
#include "CliFsmInterfaceAte.h"
#include "CliFsmInterfaceStandard.h"
#include "CliFsmInterfaceCanonical.h"
#include "CliUserInput.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

CliApplication* CliApplication::s_instance = NULL;

DeclareAppVersionStamp

bool CliApplication::static_PreventTerminationOnIdle = false;


int main (int argc, char **argv)
{
    Trace::GetInstance().AppendTraceToExistingFile();

    int result = CliApplication::GetInstance().Run(argc, argv);
    return result;
}


///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

CliApplication::CliApplication () :
    SingleThreadedApplicationWithMessaging("cli"),
    m_detectedAnotherCliRunning(false),
    m_terminated(false)
{
    ENTER();

    RegisterMessageHandler(this, "Cli");

    EXIT();
}

CliApplication::~CliApplication ()
{
    ENTER();

    EXIT();
}

CliApplication& CliApplication::GetInstance()
{
    ENTER ();

    if(s_instance == NULL)
    {
        s_instance = new CliApplication();
    }

    RETURN (*s_instance);
}

int CliApplication::AppMain()
{
    ENTER ();

    ExitIfAnotherCliDetected();

    Init();

    // Loop, processing received events.
    while( !m_terminated )
    {
        HandleEventCallbacksAndQueues( GetSelectTimeout() );

        if(m_terminated)
        {
            m_fsm->Stop("\n^C");
        }

        if(m_interactive)
        {
            m_interactive->HandleInteractiveInput();
        }
    }

    RETURN(0);
}

u32 CliApplication::GetSelectTimeout()
{
    u32 timeoutMs = 5000;

    if(m_interactive)
    {
        timeoutMs = m_interactive->GetPollRepeatTimeout();
    }

    return timeoutMs;
}

void CliApplication::ParseCommandLineArguments()
{
    const char *ateMode = GetCmdLineArgument("-a");
    const char *ateDevMode = GetCmdLineArgument("-d");
    const char *canonicalMode = GetCmdLineArgument("-c");
    const char *localIpAddress = GetCmdLineArgument("-i") ;
    const char *configFile = GetCmdLineArgument("-f") ;

    if(ateMode && canonicalMode)
    {
        // can't specify both!;
    }
    else if(ateMode)
    {
        NewCommandGroup("ate");
        if(ateDevMode)
        {
            NewCommandGroup("dev");
        }
        shared_ptr<CliInput> cliInput(new CliInputStdin ( GetSelectorRegisterInterface() ));
        shared_ptr<CliFsmInterface> fsmInterface(new CliFsmInterfaceAte(cliInput));

        m_fsm = shared_ptr<CliFsm>(new CliFsm( fsmInterface, "CliFsm(ATE)"));
    }
    else if(canonicalMode)
    {
        NewCommandGroup("ate");
        NewCommandGroup("dev");

        CliInput *cliInput_p = NULL;

        string argv(canonicalMode);

        bool readCommandsFromStdin = (argv == "");

        if(readCommandsFromStdin)
        {
            TRACE_PRINTF("CliInputStdin");
            cliInput_p = new CliInputStdin( GetSelectorRegisterInterface() );
        }
        else
        {
            TRACE_PRINTF("CliInputApplicationArgument(%s)",argv.c_str());
            cliInput_p = new CliInputApplicationArgument( argv );
        }

        shared_ptr<CliInput> cliInput(cliInput_p);
        shared_ptr<CliFsmInterface> fsmInterface(new CliFsmInterfaceCanonical(cliInput));

        m_fsm = shared_ptr<CliFsm>(new CliFsm( fsmInterface, "CliFsm(-c)"));

    }
    else
    {
        NewCommandGroup("ate");
        NewCommandGroup("dev");

        m_interactive.reset(new CliInputStdinInteractive());

        shared_ptr<CliInput> cliInput = m_interactive;
        shared_ptr<CliFsmInterface> fsmInterface(new CliFsmInterfaceStandard(cliInput));

        m_fsm = shared_ptr<CliFsm>(new CliFsm( fsmInterface, "CliFsm"));
    }

    if(localIpAddress)
    {
        cerr << "Option -i ignored.\n";
    }

    bool argumentsParserFailed = (m_fsm == NULL);

    if(argumentsParserFailed)
    {
        cerr << "Invalid option.\nSee relevant documentation for more information.\nBye.\n";
        exit(-1);
    }

	if( configFile )
		ReadConfigFile(configFile);
}

void CliApplication::ReadConfigFile(const char* configFile)
{
	ifstream cfgFile;
	string line, cmd, args;

	cfgFile.open(configFile);

	if( cfgFile.is_open() == false ) {
		cerr << "Failed to open file " << configFile << endl;
		return;
	}

	cerr << "Please wait..reading configuration file and configuring parameters ... ";

   while( getline(cfgFile, line) )
   {
      std::istringstream iss(line);

      if( !(iss >> cmd >> args) ) {
			cerr << "done." << endl;
         break;
      }

		if(line.find("tr69.") == string::npos )
		{
			cmd = "oam.set" ;
      	ProcessCommand( cmd, line);
		}
		else {
      	ProcessCommand( cmd, args);
		}
   }

	cfgFile.close();
}

void CliApplication::Init()
{
    // Register CLI handler to provide generic commands (tracelev etc).
    shared_ptr<CliHandler> cliHandler(new CliHandler(ENTITY_CLI, "cli"));
    RegisterCliHandler(ENTITY_CLI, cliHandler); // Base class keeps a shared ptr to it.

    CppCliPair cppCliPairs[] =
    {
        {
            {
                "help", 0, 3,  // min/max arguments
                "dev",
                "help [all|command|namespace] <command_id> <namespace_id>",
                "Get help on CLI commands & usage."
            },
            &CliCmdHelp,

        },
        {
            {
                "no-kick", 0, 0,
                "dev",
                "no-kick",
                "Turn off auto shutdown after inactivity."
            },
            &CliCmdNoKick
        }
    } ;

    for (u32 i = 0; i < sizeof(cppCliPairs) / sizeof(cppCliPairs[0]); i++)
    {
        cliHandler->RegisterCliCmd(cppCliPairs[i].descriptor, cppCliPairs[i].cppFuncPtr);
    }

    // Start up application services
    StartMessaging();

    // Register the application with post office.
    RegisterEntity(ENTITY_CLI);
}


void CliApplication::HandleTerminationSignal(void)
{
    m_terminated = true;
}

void CliApplication::HandleTimerExpiry(shared_ptr<TimerExpiry> timer)
{
    ENTER();

    TimerHandle expiredTimer = timer->GetTimerHandle();

    if ( m_fsm->HandleTimerExpiry(expiredTimer))
    {
        // handled
    }

    EXIT();
}

bool CliApplication::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
    ENTER();

    // First, pass to parent
    bool handled = SingleThreadedApplicationWithMessaging::MessageHandler(message);

    RSYS_ASSERT(message != NULL);

    switch (message->GetSerialisationId())
    {
        case SERIALISATION_ID_REGISTER_ENTITY_CNF:
        {
            if(!m_fsm)
            {
                shared_ptr<RegisterEntityCnf> registerEntityCnf = Serialisable::DeSerialise<RegisterEntityCnf>(message);
                RSYS_ASSERT(registerEntityCnf != NULL);

                TRACE("RegisterEntityCnf received", registerEntityCnf->ToString().c_str());
                ParseCommandLineArguments();
            }
        }
        break;

        case SERIALISATION_ID_CLI_EXECUTE_CMD_IND:
        case SERIALISATION_ID_CLI_EXECUTE_CMD_PROGRESS_IND:
        case SERIALISATION_ID_CLI_EXECUTE_CMD_CNF:
        {
            m_fsm->HandleMessage(message);
        }
        break;

        default:
            break;
    }

    RETURN (handled);
}


void CliApplication::HandleOtherEvent(shared_ptr<Queueable> event)
{
    shared_ptr<CliAppEvent> cliEvent = dynamic_pointer_cast<CliAppEvent>(event);
    if (cliEvent)
    {

        if (CliAppEvent::CLI_EVENT_WHOLE_CMD == cliEvent->GetCliAppEventType())
        {
            shared_ptr<CliAppWholeCmdEvent> wholeCmdEvent = dynamic_pointer_cast<CliAppWholeCmdEvent>(event);
            shared_ptr<CliCommand> cliCommand(new CliCommand(wholeCmdEvent->GetWholeCmd()));

            HandleUserInputLine(cliCommand);
        }

    }
}


void CliApplication::HandleUserInputLine(shared_ptr<CliCommand> command)
{
    ENTER();

    RSYS_ASSERT(m_fsm);

    m_fsm->HandleCommandLine(command);

    EXIT();
}

shared_ptr<CliResponse> CliApplication::CliCmdHelp(const CliArguments& argsIn)
{
    int argc = argsIn.size();

    ostringstream response;
    s32 cmdStatus = CLI_ERROR_NONE;
    CliArguments args = argsIn;

    TRACE_PRINTF("CliApplication::CliCmdHelp") ;
    for (int n=0;n < argc; n++)
    {
        TRACE_PRINTF("Arg %" PRIu32 " = %s", n, args[n].c_str());
    }

    if( argc == 1 &&
        ( args[0].CaselessEquals("namespaces") ||
          args[0].CaselessEquals("names") ||
          args[0].CaselessEquals("n")
        )
      )
    {
        set<string> namespaces;
        CliCmdFileMgr::GetInstance().ListAllNamespaces(namespaces);

        set<string>::iterator i = namespaces.begin();

        while( i != namespaces.end() )
        {
            response << *i++ << "\n";
        }
    }
    else
    if( argc == 1 &&
        ( args[0].CaselessEquals("all") ||
          args[0].CaselessEquals("a")
        )
      )
    {
        set<string> allCommands;
        CliCmdFileMgr::GetInstance().ListAllMatchingCommands(allCommands, "");

        set<string>::iterator i = allCommands.begin();

        while( i != allCommands.end() )
        {
            response << *i++ << "\n";
        }
    }
    else
    if( (argc == 1 || argc == 2) &&
        ( args[0].CaselessEquals("commands") ||
          args[0].CaselessEquals("cmd") ||
          args[0].CaselessEquals("c") )
        )
    {
        string partialcommand("");

        if(argc == 2)
        {
            partialcommand = args[1];
        }

        set<string> allCommands;
        CliCmdFileMgr::GetInstance().ListAllMatchingCommands(allCommands, partialcommand);

        set<string>::iterator i = allCommands.begin();

        while( i != allCommands.end() )
        {
            CliCmdFile cmd(i->c_str());

            response << *i++ << "\t" << cmd.GetHelp() << "\n";
        }

        if( response.str().empty() )
        {
            response << "No commands matching \"" << partialcommand << "\" found.\n";
        }
    }

    if( response.str().empty() )
    {
        response <<
                "help - Show this text\n"
                "help [namespaces | names | n] - List available namespaces\n"
                "help [all | a] - List all available commands\n"
                "help [commands | cmd | c] <partial-command-name> - Describe commands matching <partial-command-name>\n"
                "     e.g.  help c tr69\n"
                "           help c tpm.show\n"
                "           help c oam.netwo\n";
    }

    shared_ptr<CliResponse> cliResponsePtr (new CliResponse(response.str(), cmdStatus)) ;
    RETURN (cliResponsePtr);
}

shared_ptr<CliResponse> CliApplication::CliCmdNoKick(const CliArguments& argsIn)
{
    TRACE_PRINTF("CliApplication::CliCmdNoKick");
    static_PreventTerminationOnIdle = true;
    shared_ptr<CliResponse> cliResponsePtr (new CliResponse("Done"));
    RETURN (cliResponsePtr);
}

void CliApplication::ProcessCommand(const string& cmd, const string& args)
{
    ENTER();
    shared_ptr<CliCommand> cliCommand(new CliCommand( cmd,  args ));
    m_fsm->HandleCommandLine(cliCommand);
}

void CliApplication::ExitIfAnotherCliDetected()
{

    const char *killMode = GetCmdLineArgument("-k");

    while(killMode)
    {
        sleep(2);

        TRACE_PRINTF_CONSOLE("In Kill mode: Current buddy info, and starting another CLI:\n");
        if(system("cat /proc/buddyinfo && /mnt/dbx/cli -k") != oam_ret_zero )
	{
	  TRACE_MSG("CliApplication::ExitIfAnotherCliDetected, Unable to start another CLI");
	}

        sleep(1000);
    }

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(fd >= 0)
    {
        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));

        u16 port = CliApplication::GetInstance().GetLocalPort();

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if( bind(fd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
        {
            TRACE_PRINTF_CONSOLE("Detected that CLI is already running.\n");
            exit(-1);
        }

        close(fd);
    }
    else
    {
        TRACE_PRINTF_CONSOLE("Detection of another already running CLI has fatally failed - so exiting.\n");
        exit(-1);
    }
}


bool CliApplication::ValidateCommand(const string& cmd,
                                     const string& args)
{
    ENTER();

    bool result = false;

    CliCmdFile cliCmdFile( cmd.c_str() );

    if( cliCmdFile.found() )
    {
        if( QueryCommandGroupActive(cliCmdFile.GetGroup()) )
        {
            // Command found in namespace - check args.
            // See what we've got in the way of arguments.
            StringVector argVector ;
            int argc = StringUtils::tokenise(args,argVector);

            if( (argc >= cliCmdFile.GetMinArgs() ) && (argc <= cliCmdFile.GetMaxArgs() ))
            {
                result = true;
            }
            else
            {
                TRACE_PRINTF("Command %s arg (%s) error %u <= %u <= %u", cmd.c_str(), args.c_str(), cliCmdFile.GetMinArgs(), argc, cliCmdFile.GetMaxArgs() );
            }
        }
        else
        {
            TRACE_PRINTF("Command %s found in inactive group %s.", cmd.c_str(), cliCmdFile.GetGroup().c_str() );
        }
    }
    else
    {
        TRACE_PRINTF("Command %s not found", cmd.c_str() );
    }

    RETURN(result);
}


string & removeLeadingAndTrailingWhitespace( string & s )
{
    while(!s.empty() && (0 == isgraph(s.at(0))))
    {
        s.erase(0, 1);
    }

    while(!s.empty() && (0 == isgraph( s.at(s.length()- 1) )))
    {
        s.erase(s.length() - 1);
    }

    return s;
}

