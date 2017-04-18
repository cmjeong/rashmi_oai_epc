///////////////////////////////////////////////////////////////////////////////
//
// FreqSyncEntity.h
//
// Frequency sync  application.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FreqSyncEntity_h_
#define __FreqSyncEntity_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <boost/shared_ptr.hpp>

#include <system/ConfigurationFile.h>
#include <messaging/transport/ApplicationWithMessaging.h>
#include <messaging/transport/MessageSerialisedData.h>
#include <messaging/messages/common/GsmRemScanReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ntp-client/Ver2/FNTPcallback.h"
#include "ntp-client/Ver2/StateMachine.h"
#include "ntp-client/Ver2/Simulator.h"

///////////////////////////////////////////////////////////////////////////////
// Qualcomm TFCS Includes
///////////////////////////////////////////////////////////////////////////////
#ifdef QC_TFCS
#include "comdef.h"
#include "tfcs_api.h"
#include "loc_api.h"
#endif

#define TFCS_SYNC_STATUS_MASK_SYNC          0x0001
#define TFCS_SYNC_STATUS_MASK_SYNC_SOURCE   0x000E
#define TFCS_SYNC_STATUS_MASK_VCTCXO_ACCESS 0x0010
#define TFCS_SYNC_STATUS_MASK_FTM_ACCESS    0x0020 

using namespace boost;
using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class TimeMachine;

class XtalDac
{
static const s32 DAC_MAX = 4095;

public:
    XtalDac();
    ~XtalDac() {};

    bool Init(u32 initialDACVal,s32 pptPerBit,bool adjust,u32 movAvgSize);
    bool GetUnstable(void){return(m_unstable);}
    void AddFreqEstimate(s32 freqEstppb);
    u32  GetDacValue(void){return(m_currentDacVal);}

private:

    s32 m_pptPerBit;
    u32 m_initialDACVal;
    u32 m_currentDacVal;
    bool m_adjust;
    long double m_longTermAverage;
    long double m_lastlongTermAverage;
    unsigned long long int m_timeLastDriftCalc;
    bool m_driftNotCalced;
    std::vector<u32> m_movAvgFilter;
    u32 m_movAvgSize;
    u32 m_vecIndex;
    u32 m_numInited;
    bool m_unstable;
};


/* New parameters for TFCS */
#ifdef QC_TFCS

/*
 * TFCS subsystem state
 */ 
typedef enum TfcsSysState
{
   TFCS_SYS_NONE                   = 0,
   TFCS_SYS_ACQ_IN_PROGRESS        = 1,
   TFCS_SYS_ACQ_DONE               = 2,
   TFCS_SYS_HARD_SYNC_IN_PROGRESS  = 3,
   TFCS_SYS_HARD_SYNC_DONE         = 4,
   TFCS_SYS_IN_SYNC                = 5,
   TFCS_SYS_OUT_OF_SYNC            = 6,
} tfcs_sys_state;
 

/* TFCS callback handler function */
#ifdef __cplusplus
extern "C" {
#endif 

extern int hdlTfcsEvtCallback (
             tfcs_client_handle_type tfcs_handle,
             tfcs_event_mask_type tfcs_event,
             const tfcs_event_payload_u_type *tfcs_event_payload );

#ifdef __cplusplus
}
#endif /* __cplusplus */
  
#endif /* QC_TFCS */
 
class FreqSyncEntity
{
public:
    //static const u32 DEFAULT_REQUIRED_ACCURACY_PPB = 250;
    static const u32 DEFAULT_REQUIRED_ACCURACY_PPB = 250000;
    static const s32 FREQ_OFFSET_LIMIT_PPB = 15000;
    //static const s32 FREQ_OFFSET_LIMIT_PPB = 3000;
    static const u32 FREQ_SYNC_EXPIRY_TIMEOUT_MS = 86400000; //1 day in ms
    static const u32 NUM_SECS_BEFORE_SYNC_WARM_START = 7200;
    static const u32 FREQ_SYNC_ACTIVITY_TIMEOUT_MS = 3600000;
    static const u32 FREQ_SYNC_CALLBACK_TIMEOUT_MS = 150000; // 150 secs in ms
#ifdef QC_TFCS
    static const u32 TFCS_FREQ_UNCERTAINTY_LIMIT_PPB = 100;
    static const u32 TFCS_FREQ_BIAS_ERROR = 20;
    static const u32 TFCS_FREQ_UNCERT_MAXVALUE = 110;
    static const u8 TFCS_MAX_COSC_RETRY = 5;

    void StoreSyncReportTFCS(const tfcs_event_payload_u_type *tfcs_event_payload);
    void MonitorFreqBiasTFCS();
#endif /* QC_TFCS */
 
private:
    enum FSEvents
    {
        EventStartApp,
        EventInitialisationDone,
        EventFNTPAlive,
        EventRetryTimerExpired,
        EventFNTPAccuracySent,
        EventREMSyncPassed,
        EventREMSyncFailed,
        EventFNTPInitCnfReceivedPassed,
        EventFNTPInitCnfReceivedFailed,
        EventFNTPGetFrequencyOffsetIndReceived,
        EventFNTPSetSampleModeCnfReceived,
        EventSynchronisationAchieved,
        EventSynchronisationExpired,
        EventFreqSyncActivityNotificationTimeoutHappened,
        EventFreqSyncCallbackTimeoutHappened,
        EventWarmStart,
        EventColdStart,
        EventGPSSyncFailed,
        EventGPSSyncPassed,
        EventCoscCnf,
        EventCoscFailed,
        EventNlmAcqLostInd,
        EventFNTPDisabled,
 	EventRemSyncDisabled,
        EventFNTPSyncFailed,
        EventCallbackTimerExpired,
        EventSyncSuccessful
    };

    enum TimeSyncResult
    {
        TIME_SYNC_NOT_RECEIVED_MESSAGE,
        TIME_SYNC_NOT_OK,
        TIME_SYNC_OK
    };

public:
    FreqSyncEntity();
    ~FreqSyncEntity();

    void Startup(u32 factoryOscDac,u32 liveOscDacu32,s32 pptPerBit,bool adminStateU32,eRemScanResult remScanResult);

    void HandleMessage(shared_ptr<MessageSerialisedData> message);
    void FreqSyncExpiryTimeoutHappened();
    void FreqSyncActivityNotificationTimeoutHappened(void);
#ifdef QC_TFCS
    void FreqSyncCallbackTimeoutHappened(void);
    void releaseTFCSClient();
#endif /* QC_TFCS */
private:
    CallbackBase*  CreateCallback(void (FreqSyncEntity::*Callback)(void));
    void BuildStateMachine(void);
    void StateEntryInitializing(void);
#ifdef QC_TFCS
    void StateEntryGettingGPSSync(void);
    void StateEntrySyncFromGPS(void);
    void StateEntryCoscReq(void);
    void StateEntryAcqAndSync(void);
#endif /* QC_TFCS */
    void StateEntryFNTPSyncFailed(void);
    void StateEntryWaitingFNTPAlive(void);
    void StateExitWaitingFNTPAlive(void);
    void StateEntrySendingFNTPAccuracy(void);
    void StateEntryGettingREMScan(void);
    void StateExitGettingREMScan(void);
    void StateEntryNoFNTPorREM(void);
    void StateEntryGettingREMactiveGettingFNTPSync(void);
    void StateExitGettingREMactiveGettingFNTPSync(void);
    void StateEntryRemInactiveGettingFNTPTimeSync(void);
    void StateEntryRemDisableGettingFNTPSync(void);
    void StateEntryGettingFirstFoff(void);
    void StateExitGettingFirstFoff(void);
    void StateEntryFoundFNTPEst(void);
    void StateExitGettingParameters(void);
    void StateEntryLongTermFNTP(void);
    void StateEntryGettingStartTemperature(void);
    void StateEntryNotRecentlySynchronised(void);
    void StateExitNotRecentlySynchronised(void);
    void StateEntryRecentlySynchronised(void);
    void SetTimeOfLastSyncToNow(void);
    void EventResponseRemSyncPassed(void);
    void EventResponseFirstFrequencyOffsetIndReceived(void);
    void PerformSoftSync(void);
    void GetTimeOutValue(void);
    void EventResponseGetFrequencyOffsetIndReceived(void);
    void StateEntryLongTermREMMode(void);
    void SetXtalSyncedOAMFlag(bool xtalSynced);
    bool SetDacValue(u32 dacVal);
    void SetrecordDACAdjustments(bool recordDACAdjustments) {m_recordDACAdjustments = recordDACAdjustments;}
    void InformOAMThatFrequencySynchronisationHasBeenAchieved();
    void InformOAMThatFrequencySynchronisationHasBeenLost();
    /* New message added for indicating OAM that no neighbor cell 
     * was found for macro based sync */
#ifdef QC_TFCS
    void InformOAMThatNbrCellNotFound();
#endif /* QC_TFCS */
    void RecordFreqSyncActivity(void);
    void EventResponseFreqSyncActivityNotificationTimeoutHappened(void);

    /* Functions added for TFCS */
#ifdef QC_TFCS
    bool InitializeTFCS();
    bool SetSyncSrcTFCS(tfcs_configuration_e_type);
    bool SyncUsingTFCS();
    bool SyncUsingTFCSWithoutAcquire();
    void SendNlmCoscReq();
    void HandleAcqLostAndHighUncert();
#endif /* QC_TFCS */

    u32 m_scantimeout;
    StateMachine m_stateMachine;
    s32 m_oamDACCalSlope;
    u32 m_factoryOscDac;
    u32 m_liveOscDac;
    s32 m_currentDACOffsetppb;
    bool m_oamAdjustEnabled;
    eRemScanResult m_remScanResult;
    bool m_simulatorActive;
    XtalDac m_XtalDac;
    //pointer to file recording DAC adjustments
    FILE *m_dacAdjustFile;
    bool m_recordDACAdjustments;
    bool m_LackOfMethodForFrequencySync;
    TimeSyncResult m_timeSyncResult;

#ifdef QC_TFCS
    tfcs_client_handle_type m_tfcsHandle;
    tfcs_sys_state m_tfcsSysStateFlag;
    tfcs_configuration_e_type m_tfcsAcqConfig;
    /* TFCS synchronization report */
    tfcs_synchronization_report_s_type m_syncReport; 

    u16 m_coscArfcn;
    u8  m_retryCnt;
    u8  m_timerRunning;
    u32 m_coscReqSentCntr;
#endif /* QC_TFCS */

};


#endif
