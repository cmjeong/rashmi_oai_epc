///////////////////////////////////////////////////////////////////////////////
//
// NASApplication.h
//
// Main application class: the applications should derive from this and
// implement the virtuals.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASApplication_h_
#define __NASApplication_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <System3Way.h>
#include <system/TimerEngine.h>
#include <lib-system/SystemConfiguration.h>

#include "NASPolishMaid.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Maximum number of characters in the application name:
// _please_ don't put space characters in the name...
#define MAX_APP_NAME	64

// Enumeration allowing some very limited application status information.
// We can always add to this later if we need it.
enum NASAppState
{
	NAS_APP_STARTING,
	NAS_APP_STARTED,
	NAS_APP_RUNNING,
	NAS_APP_STOPPING,
	NAS_APP_STOPPED
};

///////////////////////////////////////////////////////////////////////////////
//
// Class: NASApplication
// Desc : Program entry point, storage for system wide data, etc.
//        All the usual gubbins associated with an app, basically.
//
///////////////////////////////////////////////////////////////////////////////
class NASApplication : public threeway::TimerNotifyInterface
{
public:
	// Construction / destruction
	NASApplication (NASApp nasApp, const char *appName);
	virtual ~NASApplication ();

	// Make sure the main applciation class is always available.
	static NASApplication &GetApp ();

	void NotifyTimerExpiry(threeway::TimerHandle expiredTimer);

	// Initialisation + termination members.  Hey leaf classes, make sure you
	// call the base: it allows system status information to be generated
	// every time an applications starts + stops.
	virtual void StartApp ();
	virtual void StopApp ();

	// Main program loop, currently running on the main thread.
	virtual u32 RunApp () = 0;

	// Accessor for the public application name & type.
	const char *GetAppName () const;
	NASApp GetAppType () const;

	// Keep the app state up-to-date!
	void SetAppState (NASAppState appState);
	NASAppState GetAppState () const;

	// If anyone is uncomfortable using the CLITransport directly, they can
	// use this instead to send messages >:-)
	void SendToCLI (const char *cliMessage, u16 transmitPort);

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

	// Invoked from the NASPolishMaid thread, to perform periodic cleanup
	// operations.  Leaf classes can call the base implementation, something
	// *** WHICH THEY WOULD BE FOOLISH NOT TO DO ***
	virtual void HouseKeeper ();

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
	static NASApplication *s_pThis;

private:

	// Which application are 'we', if you get what I mean!
	NASApp m_nasApp;

	// What is our current application state?  Primarly we use this
	// when (trying) to cleanly terminate.
	NASAppState m_appState;

	// Minimum wage, zero flexibility basic housekeeping.
	NASPolishMaid m_houseKeeper;
};

#endif
