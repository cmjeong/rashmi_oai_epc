
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <system/SerialisationIds.h>
#include <messaging/transport/CliHandler.h>
#include <messaging/messages/watchdog/WatchdogKickStopReq.h>
#include <messaging/messages/watchdog/WatchdogKickReq.h>
#include <messaging/messages/watchdog/WatchdogAddPidReq.h>
#include <messaging/messages/watchdog/WatchdogRemovePidReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "WatchdogApplication.h"
#include "ProcessGuardian.h"
#include "KickGuardian.h"
#include "BfinDog.h"

using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

WatchdogApplication* WatchdogApplication::instance = NULL;

DeclareAppVersionStamp

extern "C" void catchTerm(int v)
{
    TRACE_PRINTF("Received signal %u", v);

    /* Indicate that we should exit */
    WatchdogApplication::GetInstance().m_exit = true;
}


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

WatchdogApplication::WatchdogApplication () :
    ApplicationWithMessaging("watchdogd"),
    m_exit(false),
    m_dog(NULL),
    m_tickTimer(0),
    m_consecutiveMissedKicks(0)
{
    ENTER ();

    RegisterMessageHandler(this, "watchdogd");

    EXIT ();
}

WatchdogApplication::~WatchdogApplication ()
{
    ENTER ();

    instance = NULL;

    EXIT();
}

WatchdogApplication &WatchdogApplication::GetInstance()
{
    ENTER ();

    if(instance == NULL)
    {
        instance = new WatchdogApplication();
    }

    RETURN (*instance);
}

bool WatchdogApplication::IsEngMode()
{
    struct stat sb;

    return stat("/mnt/config/developer", &sb) == 0 && S_ISREG(sb.st_mode);
}


void WatchdogApplication::RemoveGuardian(Guardian *g)
{
    vector<Guardian*>::iterator vi;

    // Search the vector of guardians to remove from there
    for(vi = m_guardians.begin(); vi != m_guardians.end(); vi++)
    {
        if(*vi == g)
        {
            m_guardians.erase(vi);
            break;
        }
    }
}


u32 WatchdogApplication::ThreadProcedure ()
{
    ENTER ();

    // Register CLI handler.
    shared_ptr<CliHandler> cli(new CliHandler(ENTITY_WATCHDOG, "watchdog"));
    RegisterCliHandler(ENTITY_WATCHDOG, cli); // Base class keeps a shared ptr to it.

    // Start up timer engine.
    StartTimerEngine();

    // Start up the messaging engine.
    StartMessaging();

    // Register entity - blocks until successful.
    RegisterEntity(ENTITY_WATCHDOG);

    // Create timer used to kick the dog
    m_tickTimer = CreateTimer("Tick",
                                        5000,
                                        TimerEngineInterface::TIMER_START_NOW,
                                        TimerEngineInterface::TIMER_REPEAT);

    // Promote this thread's priority to max
    //  In case a task enters an infinite loop, this allows this task to
    //  hopefully continue to be scheduled.  At the least this allows log
    //  files and warnings to be updated helping to record the failure cause.
    struct sched_param p;
    p.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &p);

    // Register handlers to catch 'normal' shutdown cases
    signal(SIGTERM, catchTerm);
    signal(SIGHUP, catchTerm);
    signal(SIGINT, catchTerm);

    // Create the watchdog if not in engineering mode
    if(GetCmdLineArgument("--eng-mode") || GetCmdLineArgument("-e") || IsEngMode())
    {
        TRACE_PRINTF("** Engineering mode, no hardware dog: system unguarded **");
    }
    else
    {
        m_dog = new BfinDog();
    }

    // Loop, processing received messages
    while(!m_exit)
    {
        shared_ptr<Queueable> event = ReceiveEvent(5000);
        DispatchEvent(event);
    }

    // Stop timer engine.
    StopTimerEngine();

    if(m_dog != NULL) delete m_dog;

    TRACE_PRINTF("Watchdog exiting\n");

    RETURN(0);
}

bool WatchdogApplication::MessageHandler (shared_ptr<threeway::MessageSerialisedData> & message)
{
    // First, pass to parent
    bool handled = ApplicationWithMessaging::MessageHandler(message);

    TRACE_PRINTF("Received: %s", message->ToString().c_str());

    if (MessageSerialisedData::CONNECTIONLESS == message->GetStatus())
    {
        // Handle the message.
        switch(message->GetSerialisationId())
        {
            case SERIALISATION_ID_WATCHDOG_ADD_PID_REQ:
            {
                shared_ptr<WatchdogAddPidReq> apr = Serialisable::DeSerialise<WatchdogAddPidReq>(message);
                map<pid_t, ProcessGuardian *>::iterator i = m_pidguardians.find(apr->GetPid());

                // Check if already in the map
                if(i == m_pidguardians.end())
                {
                    ProcessGuardian *pg = new ProcessGuardian(apr->GetPid(), apr->GetDescriptor().c_str());

                    m_guardians.push_back(pg);
                    m_pidguardians[apr->GetPid()] = pg;

                    TRACE_PRINTF("Guardian added: %s", pg->ToString().c_str());
                }
                break;
            }
            case SERIALISATION_ID_WATCHDOG_REMOVE_PID_REQ:
            {
                shared_ptr<WatchdogRemovePidReq> rpr = Serialisable::DeSerialise<WatchdogRemovePidReq>(message);
                map<pid_t, ProcessGuardian *>::iterator mi = m_pidguardians.find(rpr->GetPid());

                // Check if in the map
                if(mi != m_pidguardians.end())
                {
                    Guardian *g = mi->second;

                    // Remove from the map
                    m_pidguardians.erase(mi);
                    RemoveGuardian(g);

                    TRACE_PRINTF("Guardian removed: %s", g->ToString().c_str());
                    delete g;
                }
                else
                {
                    TRACE_PRINTF("Unknown guardian: pid=%" PRIu32, rpr->GetPid());
                }

                break;
            }
            case SERIALISATION_ID_WATCHDOG_KICK_REQ:
            {
                shared_ptr<WatchdogKickReq> kr = Serialisable::DeSerialise<WatchdogKickReq>(message);
                map<u32, KickGuardian *>::iterator i = m_kickguardians.find(kr->getId());

                // Check if already in the map
                if(i != m_kickguardians.end())
                {
                    // It is, just kick it
                    i->second->Kick();
                }
                else
                {
                    // It's new, create new object and store in list and map
                    KickGuardian *kg = new KickGuardian(kr->getId(), kr->getTimeoutSoft(), kr->getTimeoutHard());

                    m_guardians.push_back(kg);
                    m_kickguardians[kr->getId()] = kg;

                    TRACE_PRINTF("Guardian added: %s", kg->ToString().c_str());
                }
                break;
            }
            case SERIALISATION_ID_WATCHDOG_KICK_STOP_REQ:
            {
                shared_ptr<WatchdogKickStopReq> kr = Serialisable::DeSerialise<WatchdogKickStopReq>(message);
                map<u32, KickGuardian *>::iterator mi = m_kickguardians.find(kr->GetId());

                // Check if in the map
                if(mi != m_kickguardians.end())
                {
                    Guardian *g = mi->second;

                    // Remove from the map
                    m_kickguardians.erase(mi);
                    RemoveGuardian(g);

                    TRACE_PRINTF("Guardian removed: %s", g->ToString().c_str());
                    delete g;
                }
                else
                {
                    TRACE_PRINTF("Unknown guardian: id=%" PRIu32, kr->GetId());
                }

                break;
            }
            default:
                break;
        }
    }
    else
    {
        TRACE_MSG_LEV(TRACE_WARNING, "Connection oriented message received but this app doesn't use them!");
    }

    return handled;
}

void WatchdogApplication::HandleTimerExpiry(shared_ptr<threeway::TimerExpiry> expiredTimer)
{
    if(m_tickTimer == expiredTimer->GetTimerHandle())
    {
        Guardian *guardianBlamedForFailureAndReboot = NULL;
        vector<Guardian*>::iterator i;
        bool allGood = true;

        // Check each guardian in turn
        for(i = m_guardians.begin(); i != m_guardians.end(); i++)
        {
            Guardian *g = *i;

            if(!g->IsGood())
            {
                if(!guardianBlamedForFailureAndReboot)
                {
                    guardianBlamedForFailureAndReboot = g;
                }

                allGood = false;
                TRACE_PRINTF("Guardian unresponsive: %s", g->ToString().c_str());
            }
        }

        // Kick the dog if all guardians are okay
        if(m_dog)
        {
            if(allGood)
            {
                m_dog->Kick();

                m_consecutiveMissedKicks = 0;
            }
            else
            {
                m_consecutiveMissedKicks++;
                TRACE_PRINTF("Watckdog kicks missed=%d", m_consecutiveMissedKicks);
            }

            if(m_consecutiveMissedKicks == 3)
            {
                system("chmod +x /mnt/dbx/reboot-fap");
                system("/mnt/dbx/reboot-fap");
                RSYS_ASSERT_PRINTF( m_consecutiveMissedKicks < 3, "Watchdog failure, possibly due to %s.", guardianBlamedForFailureAndReboot->ToString().c_str());
            }
        }

    }
}

int main (int argc, char **argv)
{
    try
    {
        return(WatchdogApplication::GetInstance().Run(argc, argv));
    }
    catch(Exception &e)
    {
        return EXIT_FAILURE;
    }
}

// END OF FILE
