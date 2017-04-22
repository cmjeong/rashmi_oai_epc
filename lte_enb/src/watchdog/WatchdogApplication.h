///////////////////////////////////////////////////////////////////////////////
//
// $Id: WatchdogApplication.h 22583 2010-01-28 15:43:26Z mrenwick $
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __WatchdogApplication_h_
#define __WatchdogApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <iostream>
#include <vector>
#include <map>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Dog.h"
#include "Guardian.h"
#include "KickGuardian.h"
#include "ProcessGuardian.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class WatchdogApplication
{
private:
    // Is singleton so private constructor.
    WatchdogApplication();

public:
    ~WatchdogApplication();
    static WatchdogApplication& GetInstance();

    /**
     * Application main method.
     */
    u32 ThreadProcedure();
	/**
     * Monitor for Messages
	 * from Applications.
     */
    void MonitorMsgs();
	/**
     * WatchDog periodic Timer
     */
	void startTimer();
    /** If TRUE, the watchdog app should safely exit.
     */
    bool                        m_exit;

   void HandleTimerExpiry();

private:

    // Singleton instance.
    static WatchdogApplication *instance;

    // Implement MessageHandler interface
    void MessageHandler(char *buf);

    /**
     * Helper function to find and remove guardian from m_guardians.
     */
    void RemoveGuardian(Guardian *g);

    // List of all guardians to check
    vector<Guardian *>          m_guardians;

    // Map of PIDs to process guardians
    map<pid_t, ProcessGuardian *>  m_pidguardians;

    // Map of IDs to kick guardians
    map<u32, KickGuardian *>    m_kickguardians;

    // The actual watchdog device
    Dog                        *m_dog;
    //TimerHandle m_tickTimer;
    u32                         m_consecutiveMissedKicks;
};

#endif
