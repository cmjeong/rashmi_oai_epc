///////////////////////////////////////////////////////////////////////////////
//
// Application.h
//
// Provides a bunch of basic functionality for an application.
//
// Override and implement Main().
// Make the overridden class a singleton.  Then from main.cpp:
//
//   return MyApplication::GetInstance()->Run(argc, argv);
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Application_h_
#define __Application_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>

#include <3waytypes.h>

#include <system/ConfigurationFile.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**
 * Map of command line arguments.
 */
typedef std::map<std::string, std::string> CmdLineArgs;

/**
 * Application version information.
 */
typedef struct
{
    const char startKey[4];

    const char version[16];    char nt0;
    const char buildCount[10]; char nt1;
    const char buildDate[12];  char nt2;
    const char buildTime[10];  char nt3;

    const char endKey[4];
}
ApplicationVersion;

/**
 * External application version information.
 */
extern const ApplicationVersion appVer;

/**
 * Define to produce a version stamp.
 * This structure needs to exist in the final executable to be stamped with
 * version information at compile time; if we define it in the library then
 * the apps won't carry distinct version info.
 * This define ensures we can change the declaration at a later date without
 * touching all the apps.
 */
#define DeclareAppVersionStamp                 \
  const ApplicationVersion threeway::appVer =  \
    { {'$','S','T','T'}, "", '\0', "", '\0', "", '\0', "", '\0', {'E','N','D','$'} };

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class Application
{
protected:
    /* Singleton */
    Application(const char * appName) :
        m_appName(appName),
        m_systemConfig("nas-system-configuration", "/mnt/bank-active/config/")
    {};

private:
    /* Singleton */
    Application(const Application &);
    Application & operator= (const Application &);

public:
    /* Singleton */
    virtual ~Application() {};

    /**
     * Get application name as set at construction.
     */
    const char * GetName() const;

    /**
     * Get name and version information.
     */
    std::string GetApplicationInfo() const;

    /**
     * Get command line argument value.
     *
     * \param  argument Cmd line argument name.
     * \return Value if present or empty string if argument is just a flag.
     *         NULL if argument not present.
     */
    const char * GetCmdLineArgument(const char * argument) const;

    /**
     * Get number of command line arguments following executable.
     *
     * \return Number of command line arguments.
     */
    u32 GetNumCmdLineArgs() const;

    /**
     * Run the application.
     * Does some basic setup (e.g. cmd line parsing) then calls Main().
     *
     * \param  argc Cmd line argument count as provided to main().
     * \param  argv Cmd line argument values as provided to main().
     * \return Application exit code to return from main().
     */
    int Run(int argc, char * argv[]);

    /**
     * Get path to non-volatile log store directory.
     * Currently get this from build flags but could change to getting from config file.
     *
     * \return Path to NV log directory.
     */
    const char * GetNvLogDirectory() const;

    /**
     * Get path to non-volatile temp directory for s/w downloads etc.
     * Currently get this from build flags but could change to getting from config file.
     *
     * \return Path to NV temporary directory.
     */
    const char * GetNvTmpDirectory() const;

    /**
     * Get information about the application as a string for debug/presentation.
     */
    virtual std::string ToString() const;
protected:
    /**
     * Do the main application thread.
     * NOTE: argc/argv only provided here for legacy reasons.  Access
     *       cmd line args through GetCmdLineArgument().
     */
    virtual int Main(int argc, char * argv[]) = 0;

    /**
     * Parse the command line arguments
     */
    void ParseCmdLineArgs(int argc, char ** argv);

    /**
     * Starts up the trace engine using the application name as the log
     * file prefix (suffix is date/time.txt) and places the file in the
     * directory supplied on the command line with --trace-dir /some/path/
     */
    virtual void StartTrace() const;

    // Main system configuration file (nas-system-configuration).
    // Read at startup and then available to derived classes.
    ConfigurationFile m_systemConfig;
private:

    // Path to exe as run (i.e. application cmd line).
    std::string m_exePath;

    // Name of the application.
    std::string m_appName;

    // Map of command line arguments to value.
    // If cmd line argument is just present then the value will be an empty string.
    CmdLineArgs m_cmdLineArgs;
};

}

#endif
