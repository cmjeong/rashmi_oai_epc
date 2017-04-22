///////////////////////////////////////////////////////////////////////////////
//
// NtpClientApplication.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <signal.h>
#include <system/Trace.h>
#include <system/TimerEngine.h>
#include <system/SerialisationIds.h>
#include <system/NumberConversions.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <messaging/messages/common/OamActionCnf.h>
#include <messaging/messages/fntp/FNTPGetFrequencyOffsetReq.h>
#include <messaging/messages/fntp/FNTPGetFrequencyOffsetCnf.h>
#include <messaging/messages/fntp/FNTPGetFrequencyOffsetInd.h>
#include <messaging/messages/fntp/FNTPInitReq.h>
#include <messaging/messages/fntp/FNTPInitCnf.h>
#include <messaging/messages/fntp/FNTPSetSampleModeReq.h>
#include <messaging/messages/fntp/FNTPSetSampleModeCnf.h>
#include <messaging/messages/fntp/FNTPIsAliveInd.h>
#include <messaging/messages/fntp/FreqSyncIsAliveInd.h>
#include <messaging/messages/fntp/FreqSyncSetFakeDac.h>
#include <platform/RsysFapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NtpClientApplication.h"
#include "FNTPTime.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

NtpClientApplication* NtpClientApplication::instance = NULL;

extern "C" void catchTerm(int v)
{
    TRACE_PRINTF("Received signal %u", v);

    /* Indicate that we should exit */
    NtpClientApplication::GetInstance().ForceExit();
}

DeclareAppVersionStamp

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

NtpClientApplication::NtpClientApplication() :
    ApplicationWithParamCache("ntp-client"),
    m_mainOutFile(NULL),
    m_oamAdjustEnabled(true),
    m_timeSynced(false),
    m_numBurstsDone(0),
    m_servers(NULL),
    m_commitFirstGoodSystemTimeToFlash(true),
    m_LackOfServers(false),
    m_exit(false)
{
    ENTER ();

    //m_servers = new FreqNTPServerInterface[OAM_DEFAULT_NUM_SERVERS]; //new m_servers. Will be deleted if we choose to get the servers from file
    m_resultFilter.Init(DEFAULT_ADD_FRACTION);

    InitSlottingRandomness();
    TimeMachine::GetFakeTimerEngine().SetAppCallback(this);

    RegisterMessageHandler(this, "NtpC");

    EXIT ();
}

NtpClientApplication::~NtpClientApplication()
{
    ENTER ();

    instance = NULL;

    if (m_servers != NULL)
    {
        delete[] m_servers;
    }

    if (m_mainOutFile != NULL)
    {
        fclose(m_mainOutFile);
    }

    EXIT ();
}

bool NtpClientApplication::InitServerInterfaces()
{
    ENTER();

    bool retVal;

    if ((m_servers = new FreqNTPServerInterface[OAM_DEFAULT_NUM_SERVERS]) == NULL) //new m_servers. Will be deleted if we choose to get the servers from file
    {
        retVal = false;
    }
    else
    {
        retVal = true;
    }

    RSYS_ASSERT(retVal);

    RETURN(retVal);
}

NtpClientApplication& NtpClientApplication::GetInstance()
{
    ENTER ();

    if (instance == NULL)
    {
        instance = new NtpClientApplication();
    }

    RETURN (*instance);
}

void NtpClientApplication::SetTimeSyncedOAMFlag(bool timeSynced)
{
    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_FREQ_SYNC_TIME_SYNCED, timeSynced);
    GetMibCache().SetMibAttributes(attrs, ENTITY_NTP_CLIENT);
}

bool NtpClientApplication::IsIpSecEnabled()
{
    return (1);
}

bool NtpClientApplication::IsQosEnabled()
{
    u32 qosEnable = 0;
    GetMibCache().GetMibAttribute(PARAM_ID_QOS_ENABLE, qosEnable);
    return (qosEnable == 1);
}

bool NtpClientApplication::CheckIpsecGwValid()
{
    IPv4Address ipAddr;
    IPv4Address nullIpAddr(0, 0, 0, 0);
    GetMibCache().GetMibAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, ipAddr);
    TRACE_PRINTF("NtpClientApplication::CheckIpsecGwValid PARAM_ID_ENB_IP_ADDR_IPV4 = %s", ipAddr.ToString());

    return (!(ipAddr == nullIpAddr));
}

void NtpClientApplication::BuildStateMachine(void)
{
    m_stateMachine.Reset();
    m_stateMachine.SetStateMachineName("FNTP client application");
    m_stateMachine.InsertSimpleState("Initial", NULL, NULL);
    m_stateMachine.InsertSimpleState("Initialising", CreateCallback(&NtpClientApplication::StateEntryInitialisation), NULL);
    m_stateMachine.InsertSimpleState("Waiting Freq Sync Alive", CreateCallback(&NtpClientApplication::StateEntryAwaitingFreqSync),CreateCallback(&NtpClientApplication::StateExitAwaitingFreqSync));
    m_stateMachine.InsertSimpleState("State Waiting Accuracy Message", CreateCallback(&NtpClientApplication::StateEntryWaitingAccuracyMessage), NULL);
    m_stateMachine.InsertSimpleState("Waiting IPSec clearance", CreateCallback(&NtpClientApplication::StateEntryWaitingIPSecClearance),CreateCallback(&NtpClientApplication::StateExitWaitingIPSecClearance));
    m_stateMachine.InsertSimpleState("Awaiting Timer Init Message", NULL, NULL);
    m_stateMachine.InsertSimpleState("Initializing Time", CreateCallback(&NtpClientApplication::StateEntryInitializingTime), NULL);
    m_stateMachine.InsertSimpleState("No servers valid", CreateCallback(&NtpClientApplication::StateEntryNoServersValid), NULL);
    m_stateMachine.InsertSimpleState("No servers active", CreateCallback(&NtpClientApplication::StateEntryNoServersActive), NULL);
    m_stateMachine.InsertSimpleState("Waiting Slot", CreateCallback(&NtpClientApplication::StateEntryWaitingSlot), NULL);
    m_stateMachine.InsertSimpleState("Doing Calculation", CreateCallback(&NtpClientApplication::StateEntryDoingCalculation), NULL);
    m_stateMachine.InsertSimpleState("Sending Sync message", CreateCallback(&NtpClientApplication::StateEntrySendingFNTPGetFrequencyOffsetIndMessage), NULL);
    m_stateMachine.InsertSimpleState("Awaiting interval timer", CreateCallback(&NtpClientApplication::StateEntryAwaitingIntervalTimer), NULL);
    m_stateMachine.InsertSimpleState("Terminal", CreateCallback(&NtpClientApplication::StateEntryTerminal), NULL);

    m_stateMachine.InsertEventHandler(EventStartApp, "Initial", NULL, "Initialising");
    m_stateMachine.InsertEventHandler(EventRegisterEntityCnfReceived, "Initialising", NULL, "Waiting Freq Sync Alive");
    m_stateMachine.InsertEventHandler(EventSendAliveRetryTimeout, "Waiting Freq Sync Alive", NULL, "Waiting Freq Sync Alive");
    m_stateMachine.InsertEventHandler(EventFreqSyncAliveReceived, "Waiting Freq Sync Alive", NULL, "State Waiting Accuracy Message");
    m_stateMachine.InsertEventHandler(EventFrequencyOffsetReqReceived, "State Waiting Accuracy Message", NULL, "Waiting IPSec clearance");
    m_stateMachine.InsertEventHandler(EventipsecClearanceCheckRetryTimeout, "Waiting IPSec clearance", NULL, "Waiting IPSec clearance");
    m_stateMachine.InsertEventHandler(EventIpSecClearedToRun, "Waiting IPSec clearance", NULL, "Initializing Time");
    m_stateMachine.InsertEventHandler(EventTimeInitOK, "Initializing Time", CreateCallback(&NtpClientApplication::EventResponseTimeInitOK), "Waiting Slot");
    m_stateMachine.InsertEventHandler(EventFatalError, "Initialising", NULL, "Terminal");
    m_stateMachine.InsertEventHandler(EventTimeInitNoValidServers, "Initializing Time", NULL, "No servers valid");
    m_stateMachine.InsertEventHandler(EventTimeInitNoActiveServers, "Initializing Time", NULL, "No servers active");
    m_stateMachine.InsertEventHandler(EventServerAddressesUpdated, "No servers valid", NULL, "Initializing Time");
    m_stateMachine.InsertEventHandler(EventServerRetryTimeout, "No servers active", NULL, "Initializing Time");
    m_stateMachine.InsertEventHandler(EventSlotTimerExpired, "Waiting Slot", NULL, "Doing Calculation");
    m_stateMachine.InsertEventHandler(EventAccuracyInsufficient, "Doing Calculation", NULL, "Awaiting interval timer");
    m_stateMachine.InsertEventHandler(EventSlotTimerExpired, "Awaiting interval timer", NULL, "Sending Sync message");//suhas
    m_stateMachine.InsertEventHandler(EventAccuracyOK, "Doing Calculation", NULL, "Sending Sync message");
    m_stateMachine.InsertEventHandler(EventSimulationFinished, "Doing Calculation", NULL, "Terminal");
    m_stateMachine.InsertEventHandler(EventFNTPGetFrequencyOffsetIndSent, "Sending Sync message", NULL, "Awaiting interval timer");
    m_stateMachine.InsertEventHandler(EventBurstIntervalTimerExpired, "Awaiting interval timer", NULL, "Waiting Slot");

    m_stateMachine.SetConstructed();
}

void NtpClientApplication::StateEntryInitialisation(void)
{
    if (InitServerInterfaces() == false)
    {
        m_stateMachine.EventHappened(EventFatalError);
    }
    else
    {

        // Start up the messaging engine.
        StartMessaging();
        StartAttributeCache();
        RegisterEntity(ENTITY_NTP_CLIENT, true);

        // Register our PID with the watchdog.
        WatchdogRegisterPid();

        SubscribeNTPMibParams();
        GetOAMvalues();
        m_stateMachine.EventHappened(EventRegisterEntityCnfReceived);
    }
}

void NtpClientApplication::StateEntryTerminal(void)
{
    TRACE_PRINTF("State entry terminal in FNTP.");
}

void NtpClientApplication::SubscribeNTPMibParams(void)
{
    TRACE_PRINTF("FNTP Subscribing mib params");
    MibAttributeIds ntpClientMibParams;
    ntpClientMibParams.insert(PARAM_ID_ENB_IP_ADDR_IPV4);
    ntpClientMibParams.insert(PARAM_ID_QOS_ENABLE);
    ntpClientMibParams.insert(PARAM_ID_FREQ_SYNC_ADMIN_STATE);
    ntpClientMibParams.insert(PARAM_ID_FREQ_SYNC_NTP_SERVER_1);
    ntpClientMibParams.insert(PARAM_ID_FREQ_SYNC_NTP_SERVER_2);
    ntpClientMibParams.insert(PARAM_ID_FREQ_SYNC_NTP_SERVER_3);
    ntpClientMibParams.insert(PARAM_ID_FREQ_SYNC_NTP_SERVER_4);

    NtpClientApplication::GetInstance().GetMibCache().SubscribeMibAttributes(0, ENTITY_NTP_CLIENT, ntpClientMibParams, true);
    TRACE_PRINTF("Exited GetMibCache().SubscribeMibAttributes call in StateEntrySubscribeNTPMibParams");
}

void NtpClientApplication::GetOAMvalues(void)
{
    ENTER();

    TRACE_PRINTF("GetInitialOAMvalues");
    u32 value;
    NtpClientApplication::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_ADMIN_STATE, value);
    if (value == 0)
    {
        m_oamAdjustEnabled = false;
    }
    else if (value == 1)
    {
        m_oamAdjustEnabled = true;
    }

    GetOAMNTPServerAddresses();

    m_numServers = OAM_DEFAULT_NUM_SERVERS; //if getting from OAM we always have 4 servers. If they have an inactive ip addr (0.0.0.0) they are not used

    m_stateMachine.EventHappened(EventServerAddressesUpdated);

    EXIT();
}

bool NtpClientApplication::SetSeverIPAddress(u32 serverNum, IPv4Address ipAdd)
{
bool noDuplication = true;
    RSYS_ASSERT(serverNum < OAM_DEFAULT_NUM_SERVERS);

    if(ipAdd != "0.0.0.0")
    {
        for(u32 serverIndex = 0;serverIndex < OAM_DEFAULT_NUM_SERVERS;serverIndex++)
        {
            if(serverIndex != serverNum)
            {
                    if(ipAdd == (m_servers[serverIndex].GetIPAddr()))
                    {
                        TRACE_PRINTF("WARNING FNTP Server %d is being set to the same as that of server %d = %s",(serverNum + 1),(serverIndex + 1),ipAdd.ToString());
                        noDuplication = false;
                    }
            }
        }
    }

    if(noDuplication)
    {
        m_servers[serverNum].SetIPAddr(ipAdd);
    }

    return noDuplication;
}

void NtpClientApplication::GetOAMNTPServerAddresses(bool& validServersPresent)
{
    ENTER();

    TRACE_PRINTF("NtpClientApplication::GetOAMNTPServerAddresses");
    validServersPresent = false;

    IPv4Address ipAddr;
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_1, ipAddr);
    SetSeverIPAddress(0,ipAddr);
    if(ipAddr != "0.0.0.0")
    {
        validServersPresent = true;
    }
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_2, ipAddr);
    SetSeverIPAddress(1,ipAddr);
    if(ipAddr != "0.0.0.0")
    {
        validServersPresent = true;
    }
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_3, ipAddr);
    SetSeverIPAddress(2,ipAddr);
    if(ipAddr != "0.0.0.0")
    {
        validServersPresent = true;
    }
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_4, ipAddr);
    SetSeverIPAddress(3,ipAddr);
    if(ipAddr != "0.0.0.0")
    {
        validServersPresent = true;
    }
    m_numServers = OAM_DEFAULT_NUM_SERVERS; //if getting from OAM we always have 4 servers. If they have an inactive ip addr (0.0.0.0) they are not used

    EXIT();
}

void NtpClientApplication::GetOAMNTPServerAddresses(void)
{
    ENTER();

    TRACE_PRINTF("NtpClientApplication::GetOAMNTPServerAddresses");

    IPv4Address ipAddr;
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_1, ipAddr);
    SetSeverIPAddress(0,ipAddr);
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_2, ipAddr);
    SetSeverIPAddress(1,ipAddr);
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_3, ipAddr);
    SetSeverIPAddress(2,ipAddr);
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_4, ipAddr);
    SetSeverIPAddress(3,ipAddr);
    m_numServers = OAM_DEFAULT_NUM_SERVERS; //if getting from OAM we always have 4 servers. If they have an inactive ip addr (0.0.0.0) they are not used

    EXIT();
}

void NtpClientApplication::DisplayOAMCacheValues(void)
{
    ENTER();

    TRACE_PRINTF("NtpClientApplication::DisplayOAMCacheValues  Displaying cached OAM values");
    u32 value;
    NtpClientApplication::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_ADMIN_STATE, value);
    IPv4Address ipAddr;
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_1, ipAddr);
    TRACE_PRINTF("PARAM_ID_FREQ_SYNC_NTP_SERVER_1 = %s",ipAddr.ToString());
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_2, ipAddr);
    TRACE_PRINTF("PARAM_ID_FREQ_SYNC_NTP_SERVER_2 = %s",ipAddr.ToString());
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_3, ipAddr);
    TRACE_PRINTF("PARAM_ID_FREQ_SYNC_NTP_SERVER_3 = %s",ipAddr.ToString());
    GetMibCache().GetMibAttribute(PARAM_ID_FREQ_SYNC_NTP_SERVER_4, ipAddr);
    TRACE_PRINTF("PARAM_ID_FREQ_SYNC_NTP_SERVER_4 = %s",ipAddr.ToString());
    GetMibCache().GetMibAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, ipAddr);
    TRACE_PRINTF("PARAM_ID_ENB_IP_ADDR_IPV4 = %s",ipAddr.ToString());

    EXIT();
}

void NtpClientApplication::StateExitGettingParameters(void)
{
    ENTER();

    EXIT();
}

void NtpClientApplication::StateEntryAwaitingFreqSync(void)
{
    ENTER();

    FNTPIsAliveInd msg(true, (TimeMachine::GetSimulatorActive()));
    TRACE_PRINTF("Alive msg =  sa = %u al = %" PRId32, msg.GetSimulatorActive()?1:0, msg.GetIsAlive());
    SendMessage(msg, ENTITY_FREQ_SYNC);
    //do not allow the following timer to be simulatable ergo use CreateTimer
    m_fntpAliveRetry = CreateTimer("FNTP retry send alive message", FNTP_ALIVE_RETRY_MS, TimerEngineInterface::TIMER_START_NOW,
                                   TimerEngineInterface::TIMER_SINGLE_SHOT);

    EXIT();
}

void NtpClientApplication::StateExitAwaitingFreqSync(void)
{
    DeleteTimer(m_fntpAliveRetry);
}

void NtpClientApplication::StateEntryWaitingAccuracyMessage(void)
{
    //m_stateMachine.EventHappened(EventFrequencyOffsetReqReceived);
}

void NtpClientApplication::StateEntryWaitingIPSecClearance(void)
{
    IPv4Address ipAddr;
    IPv4Address nullIpAddr(0, 0, 0, 0);
    bool        validServersPresent;
    if (!(IsIpSecEnabled()))
    {
        GetOAMNTPServerAddresses(validServersPresent);
        FreqNTPServerInterface::SetLocalIPAddress(nullIpAddr);
        if(validServersPresent)
        {
            m_stateMachine.EventHappened(EventIpSecClearedToRun);
        }
        else
        {
            TRACE_PRINTF("Waiting for Valid NTP Server Configuration in State EntryWaitingIPSecClearance");
        }
    }
    else
    {
        GetMibCache().GetMibAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, ipAddr);
        TRACE_PRINTF("NtpClientApplication::CheckIpsecGwValid PARAM_ID_ENB_IP_ADDR_IPV4 = %s", ipAddr.ToString());

        if (ipAddr != nullIpAddr)
        {
            GetOAMNTPServerAddresses(validServersPresent);
            FreqNTPServerInterface::SetLocalIPAddress(ipAddr);
            if(validServersPresent)
            {
                m_stateMachine.EventHappened(EventIpSecClearedToRun);
            }
            else
            {
                TRACE_PRINTF("Waiting for Valid NTP Server Configuration in State EntryWaitingIPSecClearance");
            }
        }
    }
    m_ipsecClearanceCheckRetry = CreateTimer("IPSEC clearance retry", FNTP_IPSEC_CLEARANCE_RETRY_TIMEOUT, TimerEngineInterface::TIMER_START_NOW,
                                             TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void NtpClientApplication::StateExitWaitingIPSecClearance(void)
{
    if (TimerEngine::GetInstance().IsTimerRunning(m_ipsecClearanceCheckRetry))
    {
        TimerEngine::GetInstance().DeleteTimer(m_ipsecClearanceCheckRetry);
    }
}

void NtpClientApplication::EnterConditionOfLackOfServersIfNotAlready(void)
{
    if (m_LackOfServers == false)
    {
        //set alarm No NTP Server Responding
        shared_ptr<RsysvFapAlarmId> rsysAlarmId(new RsysFapAlarmId(RsysFapAlarmId::NTP_SERVER_NOT_RESPONDING));

        TRACE_PRINTF("NtpClientApplication::EnterConditionOfLackOfServersIfNotAlready setting alarm");

        AlarmEvent alarmEvent(
                rsysAlarmId,
                AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                AlarmEvent::ALARM_SEVERITY_MAJOR,
                "NTP Server Not Responding",
                AlarmEvent::ALARM_TYPE_PROCESSING);

        SendMessage(alarmEvent, ENTITY_OAM);
        m_LackOfServers = true;
    }
}

void NtpClientApplication::ExitConditionOfLackOfServersIfNotAlready(void)
{
    if (m_LackOfServers == true)
    {
        TRACE_PRINTF("NtpClientApplication::ExitConditionOfLackOfServersIfNotAlready clearing alarm");
        //set alarm No NTP Server Responding
        shared_ptr<RsysFapAlarmId> rsysAlarmId(new RsysFapAlarmId(RsysFapAlarmId::NTP_SERVER_NOT_RESPONDING));

        AlarmEvent alarmEvent(
                rsysAlarmId,
                AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                AlarmEvent::ALARM_SEVERITY_CLEARED,
                "Cleared NTP Server Not Responding alarm",
                AlarmEvent::ALARM_TYPE_PROCESSING);

        SendMessage(alarmEvent, ENTITY_OAM);
        m_LackOfServers = false;
    }
}

void NtpClientApplication::StateEntryInitializingTime(void)
{
    bool InitTimeResult;
    CheckAllResult Result;
    if (TimeMachine::GetSimulatorActive())
    {
        TRACE_MSG ("TimeMachine::InitStatic(0.0,(TimeMachine::GetSimDuration()))");
        if (!TimeMachine::InitStatic(0.0, (TimeMachine::GetSimDuration())))
        {
            m_stateMachine.EventHappened(EventFatalError);
        }
    }

    InitTimeResult = CheckAll(&Result);

    if (Result == CHECK_ALL_OK)
    {
        m_stateMachine.EventHappened(EventTimeInitOK);
    }
    else if (Result == CHECK_ALL_NO_VALID_SERVERS)
    {
        m_stateMachine.EventHappened(EventTimeInitNoValidServers);
    }
    else if (Result == CHECK_ALL_NO_SERVERS_ACTIVE)
    {
        m_stateMachine.EventHappened(EventTimeInitNoActiveServers);
    }
    else
    {
        m_stateMachine.EventHappened(EventFatalError);
    }

    FNTPInitCnf msg(InitTimeResult);
    SendMessage(msg, ENTITY_FREQ_SYNC);

}

void NtpClientApplication::EventResponseTimeInitOK(void)
{
    u32 uSecSleep;
    u32 slotNumber;

    SetTimeSyncedOAMFlag(true);
    m_flashRewriteTime = CreatePossiblySimulatedTimer("FNTP flash rewrite time", (SECS_PER_DAY * 1000), TimerEngineInterface::TIMER_START_NOW,
                                                      TimerEngineInterface::TIMER_REPEAT);
    ExitConditionOfLackOfServersIfNotAlready();
    //get a random slot between 0 and m_numSlots
    slotNumber = m_randomRandomNumber % m_numSlots;
    //calculate a random time interval to spread out over the slot
    uSecSleep = m_randomRandomNumber % 1000000;
    TRACE_PRINTF("numSlots = %d, slotNumber = %d, uSleep = %d now sleeping",(int)m_numSlots,(int)slotNumber,(int)uSecSleep);
    //sleep until the slot comes up
    FNTPSleep(slotNumber);
    //sleep between 0 and 1 s so that we are spread out over the slot
    usleep(uSecSleep);
    //start the slot time which will then go off when we should start any NTP sending/receiving
    m_slotTimer = CreatePossiblySimulatedTimer("FNTP slot timer", (m_numSlots * 1000), TimerEngineInterface::TIMER_START_NOW,
                                               TimerEngineInterface::TIMER_REPEAT);

    FreqNTPServerInterface::InitTime();

    InitSlottingRandomness(); //again, post sync so that randomness in the DL time can be used as seed so that true randomness will ensue

    OpenAllFiles();

    if (m_gatherStats)
    {
        DoAllBursts();
        exit(0);
    }

    //print header to results file
    if ((tAppLevelVars::GetDebugLevel()) > 0)
    {
        fprintf(m_mainOutFile, "t\tm_ppm\tUncertainty\n");
        fflush(m_mainOutFile);
    }
}

void NtpClientApplication::StateEntryNoServersValid(void)
{
    EnterConditionOfLackOfServersIfNotAlready();
}

void NtpClientApplication::StateEntryNoServersActive(void)
{
    //do not allow the following timer to be simulatable ergo use CreateTimer
    m_serverRetryTimer = CreateTimer("FNTP inactive servers timer", (INACTIVE_SERVERS_RETRY_SECS * 1000), TimerEngineInterface::TIMER_START_NOW,
                                     TimerEngineInterface::TIMER_SINGLE_SHOT);
    TRACE_PRINTF("server retry timer = %" PRIu32, m_serverRetryTimer);
    EnterConditionOfLackOfServersIfNotAlready();
}

void NtpClientApplication::StateEntryWaitingSlot(void)
{

}

ComboResult NtpClientApplication::SelectClusterAndCombine(FreqNTPServerInterface inServers[], u32 nServers)
{
    ComboResult bestCluster;
    ComboResult ouriResult, ourjResult;
    ComboResult clusterLimit;
    u32 i, j;
    u32 nClusters = 0;
    bool expansionHappened;

    //loop around all the servers
    for (i = 0; i < nServers; i++)
    {
        ouriResult = (inServers[i].GetCResult());
        clusterLimit = ouriResult;
        expansionHappened = true;
        if (((ouriResult.m_valid) && (!(ouriResult.m_clustered)))) //if the servers result is m_valid and the servers result has not already been included in a cluster
        {
            while (expansionHappened) //keep looking for more results to include in the cluster if the cluster limits have been expanded
            {
                expansionHappened = false;
                for (j = 0; j < nServers; j++) //iterate over the list of servers
                {
                    ourjResult = (inServers[j].GetCResult());

                    if (((ourjResult.m_valid) && (!(ourjResult.m_clustered)) && (i != j))) //if the servers result in valid, not clustered, or not the result we are comparing it to.
                    {
                        if (clusterLimit.InRange(ourjResult)) //if the jth server's result is in range of the current cluster
                        {
                            clusterLimit.CombineMaxMin(ourjResult); //expand the cluster's limits to engulf the jth servers result
                            ouriResult.combine(ourjResult); //combine the result
                            expansionHappened = true; //note that our cluster range has expanded so we must search again for results are within the cluster
                            (inServers[j].GetCResult()).m_clustered = true; //note that our servers' result has been clustered
                            TRACE_PRINTF("Clustering %d with %d\n Cluster limit:",(int)i,(int)j);
                            clusterLimit.Display();
                            ouriResult.Display();
                        }
                        else
                        {
                            //TRACE_PRINTF("Server %d out of range of server %d",(int)i,(int)j);
                        }
                    }
                    else
                    {
                        //TRACE_PRINTF("Server %d m_valid = %d, m_clustered  = %d i = j",j,ourjResult.m_valid,ourjResult.m_clustered);
                    }
                }
            }
            (inServers[i].GetCResult()).m_clustered = true; //note that this server has been included in the cluster so that it is not included in any more

            if (((ouriResult.m_uncertainty) < (bestCluster.m_uncertainty)) || (nClusters == 0)) //if we have found a better cluster than the previous best or this if the first cluster looked at
            {
                bestCluster = ouriResult;
            }

            nClusters++;
        }
    }

    TRACE_PRINTF("Best cluster out of %d = ",(int)nClusters);
    bestCluster.Display();

    return bestCluster;
}

void NtpClientApplication::StateEntryDoingCalculation(void)
{
    bool resultToSpec = false;
    tEvent retEvent;
    unsigned long long int timeNow;

    if (TimeMachine::GetSimulationFinished())
    {
        TimeMachine::RewindSim();
        retEvent = EventSimulationFinished;
    }
    else
    {
        if (DoAllBursts() > 0) //get bursts from all servers. If none valid/active, continue hoping a server becomes valid until we are no longer in our slot
        {
            //combine the results from all the servers
            m_CResult = SelectClusterAndCombine(m_servers, m_numServers);
            //m_CResult.SelectClusterAndCombine(m_servers, m_numServers);
            //show them
            m_CResult.Display();

            m_resultFilter.Add(m_CResult);

            timeNow = (unsigned long long int) GetLDTime();

            if (m_oamAdjustEnabled) //if adjust disabled, do not take any action but continue to monitor long term average and drift
            {
                if ((tAppLevelVars::GetDebugLevel()) > 0)
                {
                    fprintf(m_mainOutFile, "%d\t%0.10Lf\t%0.10Lf\n", (int) (timeNow - (FreqNTPServerInterface::m_TimeStart)), m_CResult.m_ppm,
                            m_CResult.m_uncertainty);
                    fflush(m_mainOutFile);
                }

                if ((m_resultFilter.m_uncertainty) < m_requiredAccuracy)
                {
		    
                    //if we have a result to the required accuracy then set flag, else continue to poll & filter until we have a valid result     
                    TRACE_PRINTF("Result is as per spec");
                    resultToSpec = true;
                }
            }
            else
            {
                TRACE_PRINTF("Admin state is OFF. Frequency will NOT be adjusted");
                m_CResult.m_ppm = 0.0;
                m_CResult.m_uncertainty = 0.0;
            }
        }

        if (resultToSpec)
        {
            retEvent = EventAccuracyOK;
        }
        else
        {
            retEvent = EventAccuracyInsufficient;
        }
    }

    m_stateMachine.EventHappened(retEvent);
}

long double NtpClientApplication::CalculateCombinedDeviations(void)
{
    u32 i;
    long double finalCombinedDeviation = 0;

    long double bestDeviation = 1000000.0;
    long double deviation;
    long double sdSum = 0.0;
    u32 numCombined = 0;

    for (i = 0; i < m_numServers; i++)
    {
       //if((m_servers[i].GetServerValid()) && (!m_servers[i].GetServerInactive()) && (!m_servers[i].GetResultValid()))
        if((m_servers[i].GetServerValid()) && (!m_servers[i].GetServerInactive()))
        {
            deviation = m_servers[i].GetULandDLCombinedDeviation();
            if(deviation < bestDeviation)
            {
                bestDeviation = deviation;
                TRACE_PRINTF("bestDeviation in CalculateCombinedDeviations = %0.20Lf", bestDeviation);
            }
        }
    }

    for (i = 0; i < m_numServers; i++)
    {
        if((m_servers[i].GetServerValid()) && (!m_servers[i].GetServerInactive()))
        {
            if ((m_servers[i].GetULandDLCombinedDeviation()) < ((tAppLevelVars::GetUncertaintyInvalidFactor()) * bestDeviation))
            {
                sdSum += ldSquare(m_servers[i].GetULandDLCombinedDeviation());
                numCombined++;
                TRACE_PRINTF("combining server %" PRIu32 " value = %0.10LfCalculateCombinedDeviations",
                        i, (m_servers[i].GetULandDLCombinedDeviation()));
            }
            else
            {
                TRACE_PRINTF("server %" PRIu32 " invalidated in CalculateCombinedDeviations value = %0.10Lf",
                        i, (m_servers[i].GetULandDLCombinedDeviation()));
            }
        }
    }

    if (numCombined > 0)
    {
        finalCombinedDeviation = sqrt(sdSum / numCombined);
    }
    else
    {
        TRACE_PRINTF("No results combined for CalculateCombinedDeviations");
    }

    return (finalCombinedDeviation);
}

void NtpClientApplication::StateEntryAwaitingIntervalTimer(void)
{
    //long double SDSum = FreqNTPServerInterface::GetCombinedSds();
    long double SDSum = CalculateCombinedDeviations();
    //long double SDSum = FreqNTPServerInterface::GetCombinedInverseSumSds();
    m_burstInterval = (u32) (2 * (SDSum / m_requiredAccuracy)); //2 x the sd / required accuracy 2x as we assume that the next measurement will have the same characteristics as the first

    //check to see if our convergence time is too long and raise an alarm if it is
    if (m_burstInterval > (NUMBER_OF_DAYS_THAT_IS_CONSIDERED_TOO_LONG_TO_CONVERGE_IN * SECS_PER_DAY))
    {
        //set alarm NETWORK_JITTER
        shared_ptr<RsysFapAlarmId> rsysAlarmId(new RsysFapAlarmId(RsysFapAlarmId::NETWORK_JITTER));

        TRACE_PRINTF("NtpClientApplication NETWORK_JITTER setting alarm");

        AlarmEvent alarmEvent(
                       rsysAlarmId,
                       AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                       AlarmEvent::ALARM_SEVERITY_MAJOR,
                       "Network Jitter",
                       AlarmEvent::ALARM_TYPE_QOS);

        SendMessage(alarmEvent, ENTITY_OAM);
    }

    if (m_samplingMode == FAST_CONVERGENCE)
    {
        TRACE_PRINTF("FAST_CONVERGENCE");
    }
    else
    {
        TRACE_PRINTF("SLOW_CONVERGENCE");
        m_burstInterval *= LONG_TERM_MULTIPLICATION_FACTOR;
    }

    m_burstIntervalTimer = CreatePossiblySimulatedTimer("FNTP burst Interval timer", (m_burstInterval * 1000), TimerEngineInterface::TIMER_START_NOW,
                                                        TimerEngineInterface::TIMER_SINGLE_SHOT);
    TRACE_PRINTF("SDSum = %0.10Lf, m_burstInterval  = %" PRIu32, SDSum, m_burstInterval);

}

void NtpClientApplication::StateEntrySendingFNTPGetFrequencyOffsetIndMessage(void)
{
    TRACE_PRINTF("Sending Sync Message - Result found to spec ");
    m_resultFilter.Display();
    FNTPGetFrequencyOffsetInd msg((m_resultFilter.GetResultppb()));
    m_resultFilter.Reset();
    SendMessage(msg, ENTITY_FREQ_SYNC);
    m_stateMachine.EventHappened(EventFNTPGetFrequencyOffsetIndSent);
}

u32 NtpClientApplication::GetIntTime()
{
    ENTER();

    struct timeval tv;

    gettimeofday(&tv, NULL);

    RETURN(((u32)(tv.tv_sec)));
}

void NtpClientApplication::InitSlottingRandomness()
{
    ENTER();

    struct timeval tv;

    gettimeofday(&tv, NULL);
    srandom((unsigned long) (tv.tv_usec));
    m_randomRandomNumber = random();

    EXIT();
}

void NtpClientApplication::SetTimeInFlash(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    TRACE_PRINTF("FreqNTPServerInterface::SyncTime: Commiting system time to flash: %d.%d", (int)tv.tv_sec, (int)tv.tv_usec);
    time_t ntpTime = tv.tv_sec;
    struct tm* ntpTimeTm = gmtime(&ntpTime);
    char timeStr[64];
    if (strftime(timeStr, 64, "%m%d%HNtpClientApplication.cppY.%S", ntpTimeTm) > 0)
    {
        char commandStr[128];
        snprintf(commandStr, 128, "echo \"date %s\" > /mnt/dbx/initial-ntp-time", timeStr);
        system(commandStr);
    }
}

bool NtpClientApplication::CheckAll(CheckAllResult *Result)
{
    ENTER();

    u32 i;
    u32 besti = 0;
    long double delay = 0.0;
    long double bestdelay = 1000000.0;
    bool retVal = false;
    bool atLeastOneServerIsValid = false;

    //find which server has the lowest round trip delay (and works)
    for (i = 0; i < m_numServers; i++)
    {
        if (m_servers[i].GetServerValid())
        {
            atLeastOneServerIsValid = true;
            if ((m_timeSynced = m_servers[i].SyncTime(&delay))) //the single = is there for a purpose!
            {
                m_commitFirstGoodSystemTimeToFlash = false;
                if (delay < bestdelay)
                {
                    bestdelay = delay;
                    besti = i;
                    retVal = true;
                }
            }
            else
            {
                TRACE_PRINTF("Time not synced server %" PRIu32, i);
            }
        }
        else
        {
            TRACE_PRINTF("Server %" PRIu32 " invalid", i);
        }
    }

    if (retVal) //if we have at least one sensibly acting server
    {
        m_servers[besti].SyncTime(&delay); //sync on server with best round trip delay
        SetTimeInFlash();
        SetAllUninited(); //time has changed so all servers are now uninitialised
        TRACE_PRINTF("Best sync on server %d", (int)besti);
        *Result = CHECK_ALL_OK;
    }
    else if (!atLeastOneServerIsValid)
    {
        *Result = CHECK_ALL_NO_VALID_SERVERS;
    }
    else if (!m_timeSynced)
    {
        *Result = CHECK_ALL_NO_SERVERS_ACTIVE;
    }

    RETURN(retVal);
}

void NtpClientApplication::SetAllUninited()
{
    ENTER();

    u32 i;

    for (i = 0; i < m_numServers; i++)
    {
        m_servers[i].SetServerUnInited();
    }

    EXIT();
}

//Open all the files for the debug
void NtpClientApplication::OpenAllFiles()
{
    ENTER();

    if ((tAppLevelVars::GetDebugLevel()) > 0)
    {
        char burstFileStr[100];
        char outFileStr[100];
        u32 i;

        for (i = 0; i < m_numServers; i++)
        {
            snprintf(burstFileStr, sizeof(burstFileStr), "/mnt/dbx/BurstFile%d", (int) i);
            snprintf(outFileStr, sizeof(outFileStr), "/mnt/dbx/OutFile%d", (int) i);
            m_servers[i].OpenFiles(burstFileStr, outFileStr);
        }

        if ((m_mainOutFile = fopen("/mnt/dbx/MainOutfile", "w")) == NULL)
        {
            TRACE_PRINTF("Error opening Main Out file");
        }
    }

    EXIT();
}

//Go through all the servers and get a burst.
u32 NtpClientApplication::DoAllBursts()
{
    ENTER();

    u32 i;
    u32 numValidBurstsGot = 0;

    for (i = 0; i < m_numServers; i++)
    {
        m_servers[i].SetResultValid(false);
        if (m_servers[i].GetServerValid()) //if the server doesn't have an address of 0.0.0.0
        {
            if (m_servers[i].GetServerInactive() == false) //if the server is responding to NTP packets
            {
                /*                if(m_timeSynced == false)
                 {
                 m_timeSynced = servers[i].SyncTime();
                 }*/
                TRACE_PRINTF("Burst on Server %d",(int)i);

                if (m_gatherStats)
                {
                    //m_servers[i].GetStatBurst();
                }
                else
                {
                    m_servers[i].DoABurst();
                }
                if (m_servers[i].GetResultValid()) //if the result is valid i.e the delay is not too variable and the measurement is initialised
                {
                    numValidBurstsGot++;
                }
                else
                {
                    TRACE_PRINTF("Server %" PRIu32 " result invalid or uninitialised", i);
                }
            }
            else
            {
                TRACE_PRINTF("Server %" PRIu32 " inactive", i);
            }
        }
        else
        {
            TRACE_PRINTF("Server %" PRIu32 " invalid", i);
        }
    }

    RETURN(numValidBurstsGot);
}


bool NtpClientApplication::ProcessArgs(int argc, char * argv[])
{
    ENTER();

    bool retVal = true;
    u32 argCount;
    char *argptr;

    m_addFraction = DEFAULT_ADD_FRACTION;
    tAppLevelVars::SetNumInBurst(DEFAULT_NUM_IN_BURST);
    tAppLevelVars::InitVars();
    m_gatherStats = false;
    m_requiredAccuracy = 0.0;
    m_samplingMode = FAST_CONVERGENCE;
    m_numSlots = DEFAULT_NUM_SLOTS;

    for (argCount = 1; argCount < (u32) argc; argCount++)
    {
        argptr = argv[argCount];
        if (argptr[0] != '-')
        {
            retVal = false;
            break;
        }
        else
        {
            switch (argptr[1])
            {
            case 'N':
                tAppLevelVars::SetNumInBurst((atol(&(argptr[2]))));
                TRACE_PRINTF("Setting Number in burst to %" PRIu32, tAppLevelVars::GetNumInBurst());
                break;
            case 'F':
                m_addFraction = atol(&(argptr[2]));
                TRACE_PRINTF("Setting m_addFraction to %" PRIu32, m_addFraction);
                break;
            case 'd':
                tAppLevelVars::SetDebugLevel((atol(&(argptr[2]))));
                TRACE_PRINTF("Setting DebugLevel to %" PRIu32, tAppLevelVars::GetDebugLevel());
                break;
            case 'W':
                tAppLevelVars::SetdelayIgnoreThreshold(atof(&(argptr[2])));
                TRACE_PRINTF("Setting delay threshold to %0.10Lf", (tAppLevelVars::GetdelayIgnoreThreshold()));
                break;
            case 'V':
                TRACE_PRINTF("Date = %s, Time = %s",__DATE__,__TIME__);
                RETURN(false);
                break;
            case 'm':
                tAppLevelVars::SetMassiveStep(atof(&(argptr[2])));
                TRACE_PRINTF("Setting massive step to %0.10Lf", (tAppLevelVars::GetMassiveStep()));
                break;
            case 'C':
                tAppLevelVars::SetCorrectStepChangeResult((bool) (atol(&(argptr[2]))));
                TRACE_PRINTF("Setting CorrectStepChangeResult step to %d", (tAppLevelVars::GetCorrectStepChangeResult()));
                break;
            case '?':
                PrintUsage();
                RETURN(false);
                break;
            case 's':
                TimeMachine::SetSimulatorActive(true);
                TimeMachine::SetSimDuration(atol(&(argptr[2])));
                TimeMachine::SetAdjustDAC((bool) (atol(argv[++argCount])));
                TimeMachine::SetcmdLineInitialDAC(atol(argv[++argCount]));
                TRACE_PRINTF("Setting FNTP simulator active");
                TRACE_PRINTF("Setting simulator duration to %" PRIu32, (TimeMachine::GetSimDuration()));
                TRACE_PRINTF("Setting m_adjustDAC to %d", TimeMachine::GetAdjustDAC());
                TRACE_PRINTF("Setting simulated initial DAC to %" PRIu32, TimeMachine::GetcmdLineInitialDAC());
                RETURN(true); //no more args
                break;
            case 'S':
                TRACE_PRINTF("Setting State machine debug to ON");
                m_stateMachine.SetDebugOn(true);
                break;
            case 'g':
                m_gatherStats = true;
                break;
            case 'L':
                tAppLevelVars::SetsdCalcLength(atol(&(argptr[2])));
                TRACE_PRINTF("Setting standard deviation calculation length to %" PRIu32,tAppLevelVars::GetsdCalcLength());
                break;
            default:
                TRACE_PRINTF("Incorrect command line argument %s",argptr);
                PrintUsage();
                RETURN(false); //exceptional case must return
                break;
            }
        }
    }

    RETURN(retVal);
}

void NtpClientApplication::PrintUsage()
{
    TRACE_PRINTF("\n\nntp-client usage: ntp-client -D -N -F -X -d -W -V -m -C -s -S");
    TRACE_PRINTF("D       Initial DAC (if different from MIB)");
    TRACE_PRINTF("N       Number of samples in burst (default 20)");
    TRACE_PRINTF("F       filter add fraction (default 4)");
    TRACE_PRINTF("X       Do not adjust DAC (measurement mode) default false");
    TRACE_PRINTF("d       Select debug level (default 2)");
    TRACE_PRINTF("W       round trip average packet delay (s), above which burst will be ignored (default 0.1s)");
    TRACE_PRINTF("V       print out date and time of compilation, and exit");
    TRACE_PRINTF("m       sets the value of change in freq offset above which the result will be ignored");
    TRACE_PRINTF("C       attempt to correct a result that is subject to a step change in delay, or simply remove said");
    TRACE_PRINTF("s       set FNTP simulator to active, with duration of n secs");
    TRACE_PRINTF("S       set state machine debugging to ON");
    //    TRACE_PRINTF("c       execute DAC cal routine around zero point n");
    TRACE_PRINTF("Exiting....\n");
}

threeway::TimerHandle NtpClientApplication::CreatePossiblySimulatedTimer(const std::string& timerName, u32 timeoutPeriod,
                                                                         TimerEngineInterface::TimerStart startNow, TimerEngineInterface::TimerMode timerMode)
{
    threeway::TimerHandle retTimerHandle;

    if (TimeMachine::GetSimulatorActive())
    {
        bool repeatTrue = (timerMode == TimerEngineInterface::TIMER_REPEAT);
        retTimerHandle = TimeMachine::GetFakeTimerEngine().InsertTimer((timeoutPeriod / 1000), repeatTrue);
        TimeMachine::GetFakeTimerEngine().DisplayTimers();
    }
    else
    {
        retTimerHandle = CreateTimer(timerName, timeoutPeriod, startNow, timerMode);
    }

    return retTimerHandle;
}

bool NtpClientApplication::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
    // First, pass to parent
    bool handled = ApplicationWithParamCache::MessageHandler(message);

    TRACE("NtpClientApplication::HandleConnectionlessMessage message received", message->ToString().c_str());
    switch (message->GetSerialisationId())
    {
    case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
    {
        shared_ptr<MibSubscribeAttributesInd> subscribeMibParamsInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);
        TRACE("NtpClientApplication::HandleMessage MibSubscribeAttributesInd received", subscribeMibParamsInd->ToString().c_str());
        GetOAMvalues();
        DisplayOAMCacheValues(); //leave in for now TODO remove once behaviour is fully tested
        m_stateMachine.EventHappened(EventMibSubscribeAttributesIndReceived);
    }
        break;

    case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF:
    {
        shared_ptr<MibSubscribeAttributesCnf> mibSubscribeAttributesCnf = Serialisable::DeSerialise<MibSubscribeAttributesCnf>(message);
        RSYS_ASSERT(mibSubscribeAttributesCnf != NULL);

        TRACE("MibSubscribeAttributesCnf received", mibSubscribeAttributesCnf->ToString().c_str());

        m_stateMachine.EventHappened(EventMibSubscribeAttributesCnfReceived);
    }
        break;

    case SERIALISATION_ID_MIB_GET_ATTRIBUTES_CNF:
    {
        TRACE_PRINTF("Received SERIALISATION_ID_MIB_GET_ATTRIBUTES_CNF");
    }
        break;

    case SERIALISATION_ID_REGISTER_ENTITY_CNF:
    {
        TRACE_PRINTF("Received SERIALISATION_ID_REGISTER_ENTITY_CNF");
        m_stateMachine.EventHappened(EventRegisterEntityCnfReceived);
    }
        break;

    case SERIALISATION_ID_FNTP_GET_FREQUENCY_OFFSET_REQ:
    {
        TRACE_PRINTF("Received SERIALISATION_ID_FNTP_GET_FREQUENCY_OFFSET_REQ");
        shared_ptr<FNTPGetFrequencyOffsetReq> FrequencyOffsetReq = Serialisable::DeSerialise<FNTPGetFrequencyOffsetReq>(message);
        m_requiredAccuracy = ((long double) (FrequencyOffsetReq->GetRequiredAccuracy())) * 0.000000001; //convert from PPB to PPU
        TRACE_PRINTF("Received accuracy = %0.10Lf", m_requiredAccuracy);
        m_stateMachine.EventHappened(EventFrequencyOffsetReqReceived);
    }
        break;

    case SERIALISATION_ID_MIB_SET_ATTRIBUTES_CNF:
        //TODO: we should really check that this was set correctly
        break;

    case SERIALISATION_ID_OAM_ACTION_CNF:
    {
        shared_ptr<OamActionCnf> oamActionCnf = Serialisable::DeSerialise<OamActionCnf>(message);
        TRACE_PRINTF("Received SERIALISATION_ID_OAM_ACTION_CNF");
    }
        break;

    case SERIALISATION_ID_FREQ_SYNC_IS_ALIVE_IND:
    {
        TRACE_PRINTF("Received SERIALISATION_ID_FREQ_SYNC_IS_ALIVE_IND");
        m_stateMachine.EventHappened(EventFreqSyncAliveReceived);
    }
        break;

    case SERIALISATION_ID_FNTP_INIT_REQ:
    {
        TRACE_PRINTF("Received SERIALISATION_ID_FNTP_INIT_REQ");
        m_stateMachine.EventHappened(EventInitReqReceived);
    }
        break;

    case SERIALISATION_ID_FNTP_SET_SAMPLE_MODE_REQ:
    {
        shared_ptr<FNTPSetSampleModeReq> sampleModeReq = Serialisable::DeSerialise<FNTPSetSampleModeReq>(message);
        m_samplingMode = sampleModeReq->GetSampleMode();
        TRACE_PRINTF("Received SERIALISATION_ID_FNTP_SET_SAMPLE_MODE_REQ");
        if (m_samplingMode == FAST_CONVERGENCE)
        {
            tAppLevelVars::SetNumInBurst(FAST_CONVERGENCE_BURST_SIZE);
        }
        else if (m_samplingMode == LONG_TERM)
        {
            tAppLevelVars::SetNumInBurst(SLOW_CONVERGENCE_BURST_SIZE);
        }
        else
        {
            TRACE_PRINTF("Bum value for m_samplingMode (%d)",m_samplingMode);
        }

        FNTPSetSampleModeCnf sampleModeCnf(true);
        SendMessage(sampleModeCnf, ENTITY_FREQ_SYNC);
    }
        break;

    case SERIALISATION_ID_FREQ_SYNC_SET_FAKE_DAC:
    {
        shared_ptr<FreqSyncSetFakeDAC> setFakeDACmsg = Serialisable::DeSerialise<FreqSyncSetFakeDAC>(message);
        TimeMachine::SetFakeDac(setFakeDACmsg->GetFakeDACValue());
        TRACE_PRINTF("Set fake DAC message set to  %" PRIu32,(setFakeDACmsg->GetFakeDACValue()));
    }
        break;

    default:
        TRACE_LEV(TRACE_WARNING, "Unhandled message", message->ToString());
        break;
    }

    return handled;
}

void NtpClientApplication::NotifyTimerExpiry(TimerHandle expiredTimer)
{
    ENTER();

    if (m_slotTimer == expiredTimer)
    {
        m_stateMachine.EventHappened(EventSlotTimerExpired);
    }
    if (m_burstIntervalTimer == expiredTimer)
    {
        m_stateMachine.EventHappened(EventBurstIntervalTimerExpired);
    }
    if (m_serverRetryTimer == expiredTimer)
    {
        m_stateMachine.EventHappened(EventServerRetryTimeout);
    }
    if (m_fntpAliveRetry == expiredTimer)
    {
        m_stateMachine.EventHappened(EventSendAliveRetryTimeout);
    }
    if (m_getParamsRetry == expiredTimer)
    {
        m_stateMachine.EventHappened(EventGetMIBParamsTimeout);
    }
    if (m_subscribeParamsRetry == expiredTimer)
    {
        m_stateMachine.EventHappened(EventSubscribeMIBParamsTimeout);
    }
    if (m_ipsecClearanceCheckRetry == expiredTimer)
    {
        m_stateMachine.EventHappened(EventipsecClearanceCheckRetryTimeout);
    }
    if (m_flashRewriteTime == expiredTimer)
    {
        SetTimeInFlash();
    }

    EXIT();
}

threeway::TimerEngineInterface& NtpClientApplication::GetTimerInterface() const
{
    ENTER();
    RETURN(threeway::TimerEngine::GetInstance().GetTimerEngineInterface());
}

int NtpClientApplication::Main(int argc, char * argv[] /* Use of these is deprecated, use GetCmdLineArgument() */)
{
    ENTER();

    if (ProcessArgs(argc, argv) == false)
    {
        RETURN(1);
    }

    //TimeMachine TestSimulator;
    //TestSimulator.SpewDistributions(10000,10,2);

    // Now hand control back to ApplicationWithMessaging
    RETURN(ApplicationWithMessaging::Main(argc, argv));
}

u32 NtpClientApplication::ThreadProcedure()
{
    ENTER ();

    StartTimerEngine();

    // Following includes starting messaging, registering messaging entity,
    // registering with watchdog and subscribing for MIB params.
    BuildStateMachine();

    // Register handlers to catch 'normal' shutdown cases
    signal(SIGTERM, catchTerm);
    signal(SIGHUP, catchTerm);
    signal(SIGINT, catchTerm);

    m_stateMachine.EventHappened(EventStartApp);
    TRACE_PRINTF("NtpClientApplication::ThreadProcedure post m_stateMachine.EventHappened(EventStartApp)");
    //m_stateMachine.EventHappened(EventStartTest);
    while(!m_exit)
    {
        if (TimeMachine::GetSimulatorActive())
        {
            if (TimeMachine::GetFakeTimerEngine().RunFakeTimer() == false)
            {
                TRACE_PRINTF("FNTP simulator exited correctly after simulation complete");
                RETURN(1);
            }
        }
        else
        {
            while(!m_exit)
            {
                shared_ptr<Queueable> event = ReceiveEvent(5000);
                DispatchEvent(event);
            }
            TRACE_MSG ("Stopping timer engines");
            StopTimerEngine();
        }
    }
    TRACE_PRINTF ("NtpClientApplication::ThreadProcedure: Exiting!") ;
    WatchdogRemovePid();

    RETURN(0);
}

CallbackBase* NtpClientApplication::CreateCallback(void(NtpClientApplication::*Callback)(void))
{
    ENTER ();

    FNTPcallback<NtpClientApplication>* retVal = new (FNTPcallback<NtpClientApplication> );

    retVal->SetInstance(this);
    retVal->SetMethod(Callback);

    RETURN(retVal);
}

int main(int argc, char **argv)
{
    return (NtpClientApplication::GetInstance().Run(argc, argv));
}
