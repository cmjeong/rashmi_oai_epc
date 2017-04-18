///////////////////////////////////////////////////////////////////////////////
//
// SystemConfiguration.cpp
//
// Contents of the 3Way_SystemConfiguration.txt file.  Contains things like
// the network timers, etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <NASTrace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SystemConfiguration.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// Parameter Names.
static const char PARAM_VERSION_NUMBER [] = "VersionNumber";

///////////////////////////////////////////////////////////////////////////////
// Class: SystemConfiguration
// Desc : Read the system configuration file, and provide accessors so the
//        various application settings can be retrieved.
///////////////////////////////////////////////////////////////////////////////
SystemConfiguration::SystemConfiguration () :
    NASTextFile ("./", NAS_SYSTEM_CONFIGURATION)
{
}

SystemConfiguration::~SystemConfiguration ()
{
}

u32 SystemConfiguration::GetVersionNumber () const
{
    NAS_ENTER ();
    NAS_RETURN (GetU32Parameter (PARAM_VERSION_NUMBER));
}

bool SystemConfiguration::GenerateTraceFiles () const
{
    NAS_ENTER ();
	NAS_RETURN (strcasecmp (GetStringParameter ("GenerateTraceFiles", "Yes"), "Yes") == 0);
}

const char *SystemConfiguration::GetInstallDir () const
{
    NAS_ENTER ();
    NAS_RETURN ("./");
}

const char *SystemConfiguration::GetInstallDirNOTRACE () const
{
    return "./";
}

const char *SystemConfiguration::GetTraceDir () const
{
    return "./trace/";
}

u32 SystemConfiguration::GetTraceFileLimit () const
{
	NAS_ENTER ();
	// Returning a default of 1MB if entry not found.
	NAS_RETURN (GetU32Parameter ("TraceFileLimit", 262144));
}

bool SystemConfiguration::CaptureSubscribersIMSI () const
{
    NAS_ENTER ();
    NAS_RETURN (GetU32Parameter ("IMSICapture", 0) != 0);
}

const char *SystemConfiguration::GetUDPLoggingAddress () const
{
    NAS_ENTER ();
    NAS_RETURN (GetStringParameter ("UDP_Logging", "OFF"));
}

u16 SystemConfiguration::GetUDPLoggingPort (const char *appName) const
{
	char fileEntry [64];
	snprintf (fileEntry, 64, "%s_LoggingPort", appName);
	return (u16) GetU32Parameter (fileEntry, 0);
}

const char *SystemConfiguration::GetSipMediaDestination () const
{
	NAS_ENTER ();
	NAS_RETURN (GetStringParameter ("SipMediaDestinationAddress", ""));
}

