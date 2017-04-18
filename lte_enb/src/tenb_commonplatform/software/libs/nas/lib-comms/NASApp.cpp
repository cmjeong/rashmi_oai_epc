///////////////////////////////////////////////////////////////////////////////
//
// NASApplication.cpp
//
// Main application class: the applications should derive from this and
// implement the virtuals.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include <system/TimeWrap.h>
#include <system/StringUtils.h>
#include <comms/networking.h>

#include <lib-system/NASFileName.h>
#include <lib-system/NASString.h>
#include <lib-system/NASException.h>
#include <lib-system/NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "lib-comms/NASApp.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// Class instance variable.
NASApplication *NASApplication::s_pThis = NULL;

///////////////////////////////////////////////////////////////////////////////
// Class: NASApplication
// Desc : Program entry point, storage for system wide data, etc.
//        All the usual gubbins associated with an app, basically.
///////////////////////////////////////////////////////////////////////////////
NASApplication::NASApplication (NASApp nasApp, const char *appName) :
    m_appTimers(threeway::TimerEngine::GetInstance().GetTimerEngineInterface()),
	m_nasApp (nasApp),
	m_houseKeeper (*this, 3600)
{
	strncpysafe (m_appName, appName, sizeof(m_appName));

	s_pThis = this;
	m_sysConfig.ReadNASTextFile ();

	u32 myPid = (u32) getpid ();
	NAS_TRACE ("Started With PID", myPid);

	NASString pidFileName;
	snprintf ((char *) pidFileName, pidFileName.GetSize(), "%s.%s.pid", m_sysConfig.GetInstallDir (), m_appName);

	NAS_TRACE ("Generating Pid File", (const char *) pidFileName);
	FILE *pidFile = fopen ((const char *) pidFileName, "wt");
	if (pidFile != NULL)
	{
		fprintf (pidFile, "%" PRIu32, myPid);
		fclose (pidFile);
	}//end if
}

NASApplication::~NASApplication ()
{
	s_pThis = NULL;
}

NASApplication &NASApplication::GetApp ()
{
	return *s_pThis;
}

const char *NASApplication::GetAppName () const
{
	return m_appName;
}

NASApp NASApplication::GetAppType () const
{
	return m_nasApp;
}

void NASApplication::SetAppState (NASAppState appState)
{
	m_appState = appState;
}

NASAppState NASApplication::GetAppState () const
{
	return m_appState;
}

void NASApplication::SetTitle ()
{
    // Used to have code for WIN32.
}

void NASApplication::NotifyTimerExpiry(threeway::TimerHandle expiredTimer)
{

}


void NASApplication::StartApp ()
{
	NAS_ENTER ();

	char timeStr[64];
	memset (timeStr, '\0', sizeof (timeStr));

	threeway::TimeWrap timeNow;
	timeNow.GetDateStr (timeStr, sizeof(timeStr));

	const char *traceDir = m_sysConfig.GetTraceDir ();
	NASFileName fileName (
		"%s%s",
		traceDir == NULL ? CURRENT_DIRECTORY : traceDir,
		NAS_STATUS_LOG);

	FILE *statusFile = fopen (fileName.GetFileName (), "at");

	// Check file opened.
	RSYS_ASSERT(statusFile != NULL);

	fprintf (statusFile, "%s  Application Started: %s \n", timeStr, m_appName);
	fclose (statusFile);

	try
	{
		const char *remoteLoggingAddress = m_sysConfig.GetUDPLoggingAddress ();
		if (strcasecmp (remoteLoggingAddress, "OFF") != 0)
			NASTrace::GetInstance().EnableUDPLogging (m_sysConfig.GetUDPLoggingPort (m_appName), inet_addr (remoteLoggingAddress));
	}
	catch (const NASException &e)
	{
		NAS_MSG ("Error Trying To Turn On UDP Logging: It's Not Available");
		NAS_EXCEPTION (e);
	}//end catch

	m_houseKeeper.StartThread (MEDIUM_DEFAULT_THREAD_STACK_SIZE);

	NAS_EXIT ();
}

void NASApplication::StopApp ()
{
	NAS_ENTER ();

	m_houseKeeper.StopThread ();

	// Of course, should an application GPF or otherwise abnormally
	// exit, this probably won't be called >:-)
	char timeStr[64];
	memset (timeStr, '\0', sizeof (timeStr));

	threeway::TimeWrap timeNow;
	timeNow.GetTimeStr (timeStr, sizeof(timeStr));

	NASFileName fileName ("%s%s", GetWorkingDirectory (), NAS_STATUS_LOG);

	FILE *statusFile = fopen (fileName.GetFileName (), "at");

	// Check file opened.
    RSYS_ASSERT(statusFile != NULL);

	fprintf (statusFile, "Application: %s Stopped At %s\n", m_appName, timeStr);
	fclose (statusFile);

	NAS_EXIT ();
}

const char *NASApplication::GetWorkingDirectory ()
{
	NAS_ENTER ();
	NAS_RETURN (s_pThis == NULL ? NULL : s_pThis->m_sysConfig.GetInstallDir ());
}

const SystemConfiguration &NASApplication::GetSystemConfig ()
{
	NAS_ENTER ();

	if (s_pThis != NULL)
	{
		NAS_RETURN (s_pThis->m_sysConfig);
	}//end if

	// Informative NAS_EXIT only.
	NAS_EXIT ();
	throw NASException (
		__FILE__,
		__LINE__,
		"Too Early Accessing SystemConfiguration: App Does NOT Exist");
}

void NASApplication::HouseKeeper ()
{
	NAS_ENTER ();
	// TODO Anything?  Possibly not, maybe we should sack the house keeper...
	NAS_MSG ("House Keeper Has Nothing To Do");
	NAS_EXIT ();
}
