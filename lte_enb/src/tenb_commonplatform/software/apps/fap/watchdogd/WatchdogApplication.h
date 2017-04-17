
#ifndef __WatchdogApplication_h_
#define __WatchdogApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <messaging/transport/ApplicationWithMessaging.h>
#include <system/TimerExpiry.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Dog.h"
#include "Guardian.h"
#include "KickGuardian.h"
#include "ProcessGuardian.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

class WatchdogApplication : public threeway::ApplicationWithMessaging
{
private:
    // Is singleton so private constructor.
    WatchdogApplication();

public:
    ~WatchdogApplication();
    static WatchdogApplication& GetInstance();

    /**
     * Implement Thread pure virtual.
     * Application main thread.
     */
    u32 ThreadProcedure();

    /** If TRUE, the watchdog app should safely exit.
     */
    bool                        m_exit;

protected:
    void HandleTimerExpiry(shared_ptr<threeway::TimerExpiry> expiredTimer);

private:

    static bool IsEngMode();

    // Singleton instance.
    static WatchdogApplication *instance;

    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

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
    TimerHandle m_tickTimer;
    u32                         m_consecutiveMissedKicks;
};

#endif
