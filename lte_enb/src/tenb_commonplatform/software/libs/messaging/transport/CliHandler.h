///////////////////////////////////////////////////////////////////////////////
//
// CliHandler.h
//
// Simple CLI implementation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliHandler_h_
#define __CliHandler_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>
#include <string>
#include <3waytypes.h>
#include <system/SerialisedData.h>
#include <system/CliArgument.h>
#include <messaging/transport/MessagingEntity.h>
#include <system/TimerInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// Common error codes for use in CLI responses.
static const s32 CLI_ERROR_NONE = 0 ;
static const s32 CLI_ERROR_COMMAND_NOT_FOUND = -1 ;
static const s32 CLI_ERROR_INVALID_ARGUMENT = -2 ;
static const s32 CLI_ERROR_TOO_MANY_ARGUMENTS = -3 ;
static const s32 CLI_ERROR_TOO_FEW_ARGUMENTS = -4 ;
static const s32 CLI_ERROR_COMMAND_FAILED = -5 ;
static const s32 CLI_ERROR_COMMAND_TIMED_OUT = -6 ;
static const s32 CLI_ERROR_INVALID_STATE = -7 ;

// Maximum length of command response we'll put in a single packet (also fragment size used for responses
// which won't go in a single fragment)  - Maximum payload length for a packet minus an allowance for
// serialisation overhead, status value and a bit of padding in case anything else gets added to
// CliExecuteCmdCnf and/or CliExecuteCmdInd
static const u32 MAX_CLI_RESPONSE_PACKET_LENGTH = MESSENGER_MAX_SERIALISED_PACKET_PAYLOAD_LEN - 100 ;
// static const u32 MAX_CLI_RESPONSE_PACKET_LENGTH = 300 ; // Use this value for testing fragmentation of CLI messages.

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**
 * Description of a CLI command.
 */
typedef struct
{
    const char * cmdName;   // E.g. trace
    u8 minArgs;             // Minimum number of arguments this command supports.
    u8 maxArgs;             // Maximum number of arguments this command supports.
    const char * group;     // Group that command belongs, e.g. "ate", "dev" etc...
    const char * shortDesc; // One-liner for when listing available commands.
    const char * help;      // More detailed info to show on typing 'help <cmd>'
} CliCmdDescriptor;


/**
 * Types for passing command arguments to the command function.
 * CliArgument could get more complex over time to offer additional information
 * e.g. we could parse each argument and work out their type/value.
 */
typedef vector<CliArgument> CliArguments;
class CliResponse ;

/**
 * Callback prototype for C++ CLI commands.
 *
 * Easier to work with than the C version so why not use it?
 * Just make your C files CPP and you're away...
 */
typedef shared_ptr<CliResponse> (*CliCmdCppFunctionPtr) (const CliArguments& args);

/**
 * Callback prototype for C CLI commands.
 *
 * So you may still want to have a C callback.
 * Arguments are passed as a space delimited string and the output is
 * written to a string pointer - take account of cmdOutputSize when
 * writing to cmdOutput!!
 */
typedef int (*CliCmdCFunctionPtr)(const char * argsSpaceDelimited, char * cmdOutput, u16 cmdOutputSize);

/**
 * For internal use for registering commands.
 */
typedef struct
{
    CliCmdDescriptor cmdDesc;
    bool isCppCallback;
    union
    {
        CliCmdCppFunctionPtr cliCmdCppFunctionPtr;
        CliCmdCFunctionPtr   cliCmdCFunctionPtr;
    } callback;
} RegisteredCliCmd;

typedef map<string, RegisteredCliCmd> RegisteredCliCmds;

typedef struct
{
    CliCmdDescriptor descriptor;
    CliCmdCppFunctionPtr cppFuncPtr;
} CppCliPair;

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class ApplicationWithMessaging;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Self contained version of CliCmdDescriptor for use in messages etc.
 * TODO - seems like we could rationalise these two.
 */
class CliCmdInfo
{
public:
    CliCmdInfo() :
        m_minArgs(0),
        m_maxArgs(0)
    {}
    CliCmdInfo( const CliCmdDescriptor & cliCmdDescriptor ) :
        m_cmdName(cliCmdDescriptor.cmdName),
        m_minArgs(cliCmdDescriptor.minArgs),
        m_maxArgs(cliCmdDescriptor.maxArgs),
        m_group(cliCmdDescriptor.group),
        m_shortDescription(cliCmdDescriptor.shortDesc),
        m_helpText(cliCmdDescriptor.help)
    {}

    string  m_cmdName;
    u8      m_minArgs ;
    u8      m_maxArgs ;
    string  m_group;
    string  m_shortDescription;
    string  m_helpText ;

    string GetShortHelpText(void);
    string GetFullHelpText(void) ;
} ;

/**
 * Class to hold the result of a CLI handler function.
 */
class CliResponse
{
public :
    CliResponse();
    CliResponse (const string& responseText, s32 status = 0);
    virtual ~CliResponse() ;

    string GetResponseText(void) const ;
    void SetResponseText (const string& newResponseText) ;
    void SetResponseText (const char * newResponseText) ;
    s32 GetStatus (void) const ;
    void SetStatus (s32 newStatus) ;
    u32 GetResponseLength ();

private:
    string m_responseText ;
    s32 m_status ;
};

/**
 * Manages a set of CLI commands for an application.
 */
class CliHandler
{
public:
    /**
     * Constructor / destructor.
     */
    CliHandler(const MessagingEntity entity, const char* entityNamespace, const bool includeCommonCmds = true);
    virtual ~CliHandler();

    /**
     * Register a C++ CLI command with this handler.
     * The command is then available for execution by calling ExecuteCliCmd().
     *
     * \param cmdDesc Description of the command.
     * \param cmdFunction The function to call to execute this command.
     */
    void RegisterCliCmd(const CliCmdDescriptor& cmdDesc,  // Name, num args, description etc
                        CliCmdCppFunctionPtr cliCmdCppFunctionPtr); // Function to call with args to execute command.

    /**
     * Register a C CLI command with this handler.
     * The command is then available for execution by calling ExecuteCliCmd().
     *
     * \param cmdDesc Description of the command.
     * \param cmdFunction The function to call to execute this command.
     */
    void RegisterCliCmd(const CliCmdDescriptor& cmdDesc,  // Name, num args, description etc
                        CliCmdCFunctionPtr cliCmdCFunctionPtr); // Function to call with args to execute command.

    /**
     * Get the entity this CLI handler is for.
     */
    MessagingEntity GetEntity() const { return m_entity; };

    /**
     * Get the namespace this CLI handler is for.
     */
    string GetNamespace() const { return m_namespace; };

    /**
     * Execute a previously registered CLI command.
     *
     * \param cmdName The command to execute.
     * \param args List of arguments as a space delimited string.
     *             This is split and passed as a vector of arguments to the
     *             function that executes the command.
     * \return Output of the command as a string.
     */
    shared_ptr<CliResponse>  ExecuteCliCmd(const string& cmdName, const string& args);

    /**
     * Generate a vector of CliCmdInfo populated with
     * details of all CLI commands registered with this handler.
     *
     * \param Function populates this vector with details of
     *        all the CLI commands registered with this handler.
     */
    void GenerateCliCmdInfo(vector<CliCmdInfo>& cmdInfo) const;

    /**
     * Sets the interface required by the common "show-timers" cli command.
     * This is called by the parent app base class during initialisation and
     * doesn't need to be called by the concrete app class.
     * @param pInterface
     */
    static void SetTimerEngineInterface(TimerEngineInterface* pInterface);

private:
    void WriteCliCmdFile(const CliCmdDescriptor& cmdDesc);

    /**
     * Common CLI commands.
     */
    static shared_ptr <CliResponse> CliCmdTraceLev(const CliArguments& args);
    static shared_ptr <CliResponse> CliCmdTraceCat(const CliArguments& args);
    static shared_ptr <CliResponse> CliCmdTraceUdp(const CliArguments& args);
    static shared_ptr <CliResponse> CliCmdShowMem(const CliArguments& args);
    static shared_ptr <CliResponse> CliCmdShowTimers(const CliArguments& args);
    static shared_ptr <CliResponse> CliCmdAssert(const CliArguments& args);

    MessagingEntity m_entity ;
    string m_namespace ;

    // List of registered CLI commands.
    RegisteredCliCmds m_registeredCliCmds;

    // Interface to timer engine is required by common commands.
    static TimerEngineInterface* m_pTimerEngineInterface;
};

}

#endif
