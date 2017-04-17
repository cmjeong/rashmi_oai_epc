///////////////////////////////////////////////////////////////////////////////
//
// NASApplication.h
//
// When converting NAS applictions from being derived from NASApplication to
// ApplicationWithMessaging, we still need to provide some of the old facilities
// of NASApplication. This is where this bodger comes in...
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASAppWithMessagingBodger_h_
#define __NASAppWithMessagingBodger_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/TimerEngine.h>
#include <lib-system/SystemConfiguration.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Maximum number of characters in the application name:
// _please_ don't put space characters in the name...
#define MAX_APP_NAME	64


///////////////////////////////////////////////////////////////////////////////
//
// Class: NASApplication
// Desc : Program entry point, storage for system wide data, etc.
//        All the usual gubbins associated with an app, basically.
//
///////////////////////////////////////////////////////////////////////////////
class NASAppWithMessagingBodger
{
public:
	// Construction / destruction
	NASAppWithMessagingBodger(const char *appName);
	virtual ~NASAppWithMessagingBodger ();

	// Make sure the main application class is always available.
	static NASAppWithMessagingBodger &GetApp ();

    // Initialisation + termination members.  Hey leaf classes, make sure you
	// call the base: it allows system status information to be generated
	// every time an applications starts + stops.
	virtual void StartBodger ();
	virtual void StopBodger ();

	// Accessor for the public application name & type.
	const char *GetAppName () const;

	// Windows only: put the title of the application
	// on the window title bar.  Sounds superficial, but
	// it's actually pretty handy when tabbing between
	// windows.  Does nothing on non-Windows systems.
	void SetTitle ();

	// Static accessor for the working directory so that everyone
	// that needs it has easy access to it.
	static const char *GetWorkingDirectory ();

	// Ditto for the main configuration parameters.
	static const SystemConfiguration &GetSystemConfig ();

protected:

	// The timer engine: all running timers are registered here.
	// Notification of timer expiry is picked up in RunCore() and dispatched
	// to the timer owner for processing.
    threeway::TimerEngineInterface& m_appTimers;

	// Application name; informative only.
	char m_appName[MAX_APP_NAME];

	// Application configuration information.
	SystemConfiguration m_sysConfig;

	// Single instance of this class.
	static NASAppWithMessagingBodger *s_pThis;

private:

};

#endif
