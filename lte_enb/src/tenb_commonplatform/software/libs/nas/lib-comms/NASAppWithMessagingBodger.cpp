///////////////////////////////////////////////////////////////////////////////
//
// NASAppWithMessagingBodger.cpp
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
#include <messaging/transport/ApplicationWithMessaging.h>

#include <lib-system/NASTrace.h>
#include <lib-system/NASFileName.h>
#include <lib-system/NASString.h>
#include <lib-system/NASException.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASAppWithMessagingBodger.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// Class instance variable.
NASAppWithMessagingBodger *NASAppWithMessagingBodger::s_pThis = NULL;

///////////////////////////////////////////////////////////////////////////////
// Class: NASAppWithMessagingBodger
// Desc : Program entry point, storage for system wide data, etc.
//        All the usual gubbins associated with an app, basically.
///////////////////////////////////////////////////////////////////////////////
NASAppWithMessagingBodger::NASAppWithMessagingBodger (const char *appName) :
    m_appTimers(threeway::TimerEngine::GetInstance().GetTimerEngineInterface())
{
	strncpysafe (m_appName, appName, sizeof(m_appName));

	s_pThis = this;
	m_sysConfig.ReadNASTextFile ();

	u32 myPid = (u32) getpid ();
	NAS_TRACE ("Started With PID", myPid);
}

NASAppWithMessagingBodger::~NASAppWithMessagingBodger ()
{
	s_pThis = NULL;
}

NASAppWithMessagingBodger &NASAppWithMessagingBodger::GetApp ()
{
	return *s_pThis;
}

const char *NASAppWithMessagingBodger::GetAppName () const
{
	return m_appName;
}

void NASAppWithMessagingBodger::SetTitle ()
{
    // Used to have code for WIN32.
}

void NASAppWithMessagingBodger::StartBodger ()
{
	NAS_ENTER ();

	char timeStr[64];
	memset (timeStr, '\0', sizeof (timeStr));

	threeway::TimeWrap timeNow;
	timeNow.GetDateStr (timeStr, sizeof(timeStr));

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

	NAS_EXIT ();
}

void NASAppWithMessagingBodger::StopBodger ()
{
	NAS_ENTER ();

	NAS_EXIT ();
}

const char *NASAppWithMessagingBodger::GetWorkingDirectory ()
{
	NAS_ENTER ();
	NAS_RETURN (s_pThis == NULL ? NULL : s_pThis->m_sysConfig.GetInstallDir ());
}

const SystemConfiguration &NASAppWithMessagingBodger::GetSystemConfig ()
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

