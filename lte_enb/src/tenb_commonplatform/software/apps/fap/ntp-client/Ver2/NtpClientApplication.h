///////////////////////////////////////////////////////////////////////////////
//
// NtpClientApplication.h
//
// Main ntp-client app entry point and startup code.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NtpClientApplication_h_
#define __NtpClientApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/transport/ApplicationWithParamCache.h>
#include <messaging/transport/MessageSerialisedData.h>
#include <messaging/messages/fntp/FNTPSetSampleModeReq.h>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FreqNTP.h"
#include "StateMachine.h"
#include "Simulator.h"

using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class NtpClientApplication: public threeway::ApplicationWithParamCache
{
private:

    enum CheckAllResult
    {
        CHECK_ALL_OK,
        CHECK_ALL_NO_VALID_SERVERS,
        CHECK_ALL_NO_SERVERS_ACTIVE
    };

    enum FSEvents
    {
        EventNone,
        EventStartApp,
        EventInitialisationDone,
        EventMibSubscribeAttributesIndReceived,
        EventSubscribeMIBParamsTimeout,
        EventMibSubscribeAttributesCnfReceived,
        EventMibGetAttributesCnfReceived,
        EventGetMIBParamsTimeout,
        EventMibSetAttributesCnfReceived,
        EventRegisterEntityCnfReceived,
        EventFNTPGetFrequencyOffsetIndReceived,
        EventInitReqReceived,
        EventIpSecClearedToRun,
        EventTimeInitOK,
        EventTimeInitNoValidServers,
        EventTimeInitNoActiveServers,
        EventFrequencyOffsetReqReceived,
        EventSlotActive,
        EventAccuracyInsufficient,
        EventAccuracyOK,
        EventSlotTimerExpired,
        EventBurstIntervalTimerExpired,
        EventServerAddressesUpdated,
        EventServerRetryTimeout,
        EventFatalError,
        EventStartTest,
        EventFNTPGetFrequencyOffsetIndSent,
        EventFreqSyncAliveReceived,
        EventSendAliveRetryTimeout,
        EventipsecClearanceCheckRetryTimeout,
        EventSimulationFinished,
    };

    static const u32 SECS_PER_DAY = 86400;//1 day
    static const u32 DEFAULT_NUM_IN_BURST = 20;
    static const u32 FAST_CONVERGENCE_BURST_SIZE = 20;
    static const u32 SLOW_CONVERGENCE_BURST_SIZE = 10;
    static const u32 DEFAULT_ADD_FRACTION = 4;
    static const u32 OAM_DEFAULT_NUM_SERVERS = 4; //the number of servers stored by default in oam
    static const u32 DEFAULT_NUM_SLOTS = 100;
    static const u32 INACTIVE_SERVERS_RETRY_SECS = 300; //5 mins
    //static const u32 LONG_TERM_MULTIPLICATION_FACTOR = 4;
    static const u32 LONG_TERM_MULTIPLICATION_FACTOR = 1;
    static const u32 FNTP_ALIVE_RETRY_MS = 5000;
    static const u32 FNTP_IPSEC_CLEARANCE_RETRY_TIMEOUT = 1000;
    static const u32 FNTP_GET_MIB_PARAMS_RETRY_MS = 1000;
    static const u32 FNTP_SUBSCRIBE_MIB_PARAMS_RETRY_MS = 1000;
    static const u32 NUMBER_OF_DAYS_THAT_IS_CONSIDERED_TOO_LONG_TO_CONVERGE_IN = 2;
    // Is singleton so private constructor.
    NtpClientApplication();

public:
    ~NtpClientApplication();
    static NtpClientApplication& GetInstance();
    threeway::TimerEngineInterface& GetTimerInterface() const;

    /**
     * Implement Application::Main.
     */
    int Main(int argc, char * argv[]);

    void SubscribeNTPMibParams(void);
    void GetOAMvalues(void);
    bool SetSeverIPAddress(u32 serverNum, IPv4Address ipAdd);
    void GetOAMNTPServerAddresses(void);
    void GetOAMNTPServerAddresses(bool& validServersPresent);
    void DisplayOAMCacheValues(void);

    //Initialise
    void StateEntryInitialisation(void);
    void StateEntryTerminal(void);
    void StateExitGettingParameters(void);
    void StateEntryAwaitingFreqSync(void);
    void StateExitAwaitingFreqSync(void);
    void StateEntryWaitingAccuracyMessage(void);
    void StateEntryWaitingIPSecClearance(void);
    void StateExitWaitingIPSecClearance(void);
    void StateEntryInitializingTime(void);
    void EventResponseTimeInitOK(void);
    void StateEntryNoServersActive(void);
    void StateEntryNoServersValid(void);
    void StateEntryWaitingSlot(void);
    void StateEntryDoingCalculation(void);
    void StateEntryAwaitingIntervalTimer(void);
    void StateEntrySendingFNTPGetFrequencyOffsetIndMessage(void);
    void InitTime(void);

    void ExitConditionOfLackOfServersIfNotAlready(void);
    void EnterConditionOfLackOfServersIfNotAlready(void);
    /**
     * Implement MessageRxInterface.
     *
     if there is an OAM message for us. Act on it if there is.*/

    threeway::TimerHandle CreatePossiblySimulatedTimer(const std::string& timerName, u32 timeoutPeriod, TimerEngineInterface::TimerStart startNow =
                                                       TimerEngineInterface::TIMER_START_NOW,
                                                       TimerEngineInterface::TimerMode timerMode = TimerEngineInterface::TIMER_SINGLE_SHOT);
    // Timer handler.
    void NotifyTimerExpiry(threeway::TimerHandle expiredTimer);
    //create a callback for a method wihin this class of type callback base. Used for the state machine state entry/exit and event handlers
    CallbackBase* CreateCallback(void(NtpClientApplication::*Callback)(void));

    // Check if QOS is enabled
    bool IsQosEnabled();

    /**
     * Application main thread
     */
    u32 ThreadProcedure();

    void ForceExit() {m_exit = true;} ;

private:

    // Singleton instance.
    static NtpClientApplication* instance;
    //Initialise all the interfaces to the NTP servers. At this stage only new them
    bool InitServerInterfaces();
    //set the PARAM_ID_FREQ_SYNC_TIME_SYNCED oam param
    void SetTimeSyncedOAMFlag(bool timeSynced);
    //Inset all the states & event handlers into the state machine & connect up
    void BuildStateMachine(void);
    /**
     * FNTP related functions.
     */
    //get time expressed as an u32 integer number of seconds since 1970
    u32 GetIntTime();
    //init slotting procedure, by generating a random number that is used to place the fap on a random timeslot.
    void InitSlottingRandomness();
    //write the inputted time to flash file called /mnt/dbx/initial-ntp-time
    void SetTimeInFlash(void);
    //go through all the NTP servers syncing time, and sync in the serevr with the least latency
    bool CheckAll(CheckAllResult *Result);
    //open all the files relevant to this application
    void OpenAllFiles();
    //Cause all the active server interfaces to get bursts from their servers
    u32 DoAllBursts();
    //Process the command line args. Also deal with defaults
    bool ProcessArgs(int argc, char * argv[]);
    //print out all the command line options
    void PrintUsage();
    /**
     *
     */
    ComboResult SelectClusterAndCombine(FreqNTPServerInterface inServers[], u32 nServers);

    bool IsIpSecEnabled();
    /**
     * Check to see in the ipsec ip address is not 0.0.0.0
     */
    bool CheckIpsecGwValid();

    //Sets all servers to uninited. Used after a time sync as all the timings will be out
    void SetAllUninited();

    long double CalculateCombinedDeviations(void);

    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    u32 m_randomRandomNumber;
    //pointer to array of FreqNTPServerInterface s that interface to the servers
    FreqNTPServerInterface *m_servers;
    //number of servers we talk to
    u32 m_numServers;
    //burst interval in s. Time between consecutive bursts.
    u32 m_burstInterval;
    //number of moving average boxes
    u32 m_addFraction;
    //value that reflects the oam value freqSyncAdminState
    bool m_oamAdjustEnabled;
    //level used to filter debugging
    u32 m_debugLevel;
    //pointer to main output file
    FILE *m_mainOutFile;
    //main result of all our calculations
    ComboResult m_CResult;
    //indicates whether the app has been real time synced i.e. the absolute time has been set
    bool m_timeSynced;
    //used to indicate to the app that a stat burst needs to be got. Used for general statistics getting
    bool m_gatherStats;
    //moving combination filter used to combine estimates to provide a more accurate one.
    ComboResultFilter m_resultFilter;
    //accuracy in ppb that the FNTP algorithm attempts to keep to.
    long double m_requiredAccuracy;
    //State machine used for the control of the app. Changes states in responsew to events
    StateMachine m_stateMachine;
    //number of time slots we can transmit on. The fap will be randomly assigned a slot on which it can transmit.
    u32 m_numSlots;
    //Timer for subscribing MIB param  messages (in the case OAM is inactive at this stage)
    threeway::TimerHandle m_subscribeParamsRetry;
    //Timer for sending get parameter messages (in the case OAM is inactive at this stage)
    threeway::TimerHandle m_getParamsRetry;
    //Timer for send alive message retry
    threeway::TimerHandle m_fntpAliveRetry;
    // Timer for slot readiness.
    threeway::TimerHandle m_slotTimer;
    // Timer for the burst interval
    threeway::TimerHandle m_burstIntervalTimer;
    // Timer for the invalid server retry
    threeway::TimerHandle m_serverRetryTimer;
    // Timer for re-checking if the ipsec is valid
    threeway::TimerHandle m_ipsecClearanceCheckRetry;
    // Timer for re-writing time to flash
    threeway::TimerHandle m_flashRewriteTime;
    tSampleMode m_samplingMode;
    u32 m_timeNow;
    u32 m_numBurstsDone;

    // Work-around to avoid large system time change causing cyclic reboot
    // when IPSec tunnel fails due to rekeying problem (mantis 1115).  The
    // first change will cause a reboot but caching the date/time in flash
    // should stop it cycling.
    bool m_commitFirstGoodSystemTimeToFlash;
    //state variable. A bit horrible as the state machine should cope. Indicates that there are no servers active and or valid
    bool m_LackOfServers;

    bool m_exit;
};

}

#endif
