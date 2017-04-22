///////////////////////////////////////////////////////////////////////////////
//
// FreqSyncEntity.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <sys/time.h>
#include <time.h>
#include <system/Trace.h>
#include <system/SerialisationIds.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <mib-common/messages/MibGetAttributesCnf.h>
#include <mib-common/messages/MibSetAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <messaging/messages/fntp/FNTPGetFrequencyOffsetReq.h>
#include <messaging/messages/fntp/FNTPGetFrequencyOffsetInd.h>
#include <messaging/messages/fntp/FNTPInitReq.h>
#include <messaging/messages/fntp/FNTPInitCnf.h>
#include <messaging/messages/fntp/FreqSyncIsAliveInd.h>
#include <messaging/messages/fntp/FNTPSetSampleModeReq.h>
#include <messaging/messages/fntp/FNTPSetSampleModeCnf.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/common/RemGsmRemDACEstimateInd.h>
#include <messaging/messages/cphy/CPhyRemWcdmaCoarseFreqLockReq.h>
#include <messaging/messages/cphy/CPhyRemWcdmaCoarseFreqLockCnf.h>
#include <messaging/messages/fntp/FreqSyncSetFakeDac.h>
#include <messaging/messages/fntp/FNTPIsAliveInd.h>
#include <system/TimerEngine.h>
#include <platform/FapAlarmId.h>

// Messages for COSC
#include <messaging/messages/common/NlmCoscReq.h>
#include <messaging/messages/common/NlmCoscCnf.h>
#include <messaging/messages/cphy/CPhyNlmErrInd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FreqSyncEntity.h"
#include "OamUserApplication.h"
#include "MibHelper.h"


using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
XtalDac::XtalDac():
    m_vecIndex(0),
    m_pptPerBit(0),
    m_initialDACVal(0),
    m_currentDacVal(0),
    m_adjust(true),
    m_longTermAverage(0.0),
    m_lastlongTermAverage(0.0),
    m_timeLastDriftCalc(0),
    m_driftNotCalced(true),
    m_numInited(0),
    m_movAvgSize(0),
    m_unstable(false)
{
    ENTER();

    EXIT();
}

bool XtalDac::Init(u32 initialDACVal,s32 pptPerBit,bool adjust,u32 movAvgSize)
{
    ENTER();

    TRACE_PRINTF("XtalDac::Init initialDacValue=%"PRIu32" pptPerBit=%"PRId32" adjust=%d movAvgSize=%"PRIu32,
                 initialDACVal, pptPerBit, adjust ? 1:0, movAvgSize);
    m_currentDacVal = m_initialDACVal = initialDACVal;
    m_pptPerBit = pptPerBit;
    m_adjust = adjust;
    m_movAvgSize = movAvgSize;

    m_movAvgFilter.resize(m_movAvgSize);
    m_movAvgFilter.clear();


    RETURN(true);
}

void XtalDac::AddFreqEstimate(s32 freqEstppb)
{
    s32 requiredDacOffset;
    s32 requiredDacValue;
    u32 movAvgSum;



    if(m_pptPerBit == 0)
    {
        TRACE_PRINTF("m_pptPerBit = 0");
        RSYS_ASSERT(0);
    }

    if (((u32)(abs(freqEstppb))) > (FreqSyncEntity::DEFAULT_REQUIRED_ACCURACY_PPB * m_movAvgSize))
    {
        m_unstable = true;
    }
    else
    {
        m_unstable = false;
    }

    requiredDacOffset = ((freqEstppb * 1000) / m_pptPerBit);

    TRACE_PRINTF("XtalDac::Update freqEst=%"PRId32"ppb  pptPerBit=%"PRId32" unstable=%d currentDacValue=%"PRIu32" requiredDacOffset=%"PRId32,
                 freqEstppb, m_pptPerBit, m_unstable ? 1:0, m_currentDacVal, requiredDacOffset);

    if(abs(freqEstppb) > FreqSyncEntity::FREQ_OFFSET_LIMIT_PPB)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "NTP frequency offset estimate unreliable. Measurement discarded");
        return;
    }
    requiredDacValue = ((s32)m_currentDacVal) + requiredDacOffset;
    TRACE_PRINTF("requiredDacValue = %"PRId32, requiredDacValue);

    if(requiredDacValue > DAC_MAX)
    {
        requiredDacValue = DAC_MAX;
    }
    else if(requiredDacValue < 0)
    {
        requiredDacValue = 0;
    }
    TRACE_PRINTF("requiredDacValue(saturated) = %"PRId32, requiredDacValue);
    TRACE_PRINTF("movAvgSize=%"PRIu32"  vecIndex=%"PRIu32"  numInited=%"PRIu32,
                 m_movAvgSize, m_vecIndex, m_numInited);


    m_movAvgFilter[m_vecIndex++] = requiredDacValue;

    if(m_vecIndex >= m_movAvgSize)
    {
        m_vecIndex = 0;
    }

    if(m_numInited < m_movAvgSize)
    {
        m_numInited++;
    }

    movAvgSum = 0;
    for(u32 i = 0; i < m_numInited; i++)
    {
        movAvgSum += m_movAvgFilter[i];
        TRACE_PRINTF("Filter element %"PRIu32" = %"PRIu32, i, m_movAvgFilter[i]);
    }

    /* Compute the average over m_numInited number of samples, rounding the
     * result to the nearest integer.
     */
    m_currentDacVal = (movAvgSum + (m_numInited >> 1)) / m_numInited;
    TRACE_PRINTF("movAvgSum=%"PRIu32"  filteredDacValue=%"PRIu32, movAvgSum, m_currentDacVal);
}


FreqSyncEntity::FreqSyncEntity() :
m_oamAdjustEnabled(false),
m_factoryOscDac(0),
m_liveOscDac(0),
m_oamDACCalSlope(0),
m_remScanResult(REM_SCAN_RESULT_NOT_YET_PERFORMED),
m_simulatorActive(false),
m_dacAdjustFile(false),
m_recordDACAdjustments(false),
m_currentDACOffsetppb(0),
m_LackOfMethodForFrequencySync(false),
m_timeSyncResult(TIME_SYNC_NOT_RECEIVED_MESSAGE)
#ifdef QC_TFCS
,
m_tfcsHandle(TFCS_CLIENT_HANDLE_INVALID),
m_tfcsSysStateFlag(TFCS_SYS_NONE),
m_tfcsAcqConfig(SYNC_SRC_GPS), /* Setting default sync source to GPS */
m_coscArfcn(0),
m_retryCnt(0),
m_timerRunning(FALSE),
m_coscReqSentCntr(0)
#endif /* QC_TFCS */
{
    ENTER();

    EXIT();
}

FreqSyncEntity::~FreqSyncEntity()
{
    ENTER();
    if(m_dacAdjustFile != NULL)
    {
        fclose(m_dacAdjustFile);
    }

    /* Release the TFCS client handle */
#ifdef QC_TFCS
    releaseTFCSClient();
#endif /* QC_TFCS */

    EXIT();
}

void FreqSyncEntity::Startup(u32 factoryOscDac,u32 liveOscDac,s32 pptPerBit,bool adminStateU32,eRemScanResult remScanResult)
{
    ENTER();
    m_factoryOscDac = factoryOscDac;
    m_liveOscDac = liveOscDac;
    m_oamDACCalSlope = pptPerBit;
    m_oamAdjustEnabled = adminStateU32;
    m_remScanResult = remScanResult;
    m_timeSyncResult = TIME_SYNC_NOT_RECEIVED_MESSAGE;

    if(m_recordDACAdjustments)
    {
        if ((m_dacAdjustFile = fopen("/mnt/dbx/DacAdjustfile", "w")) == NULL)
        {
            TRACE_PRINTF("Error opening DAC adjust file");
        }
    }
    //very first startup where liveOscDac will be 0. Set to factoryOscDac. This will work if ntp-client is not running TODO get best startup mechanism
    if(m_liveOscDac == 0)
    {
        m_liveOscDac = m_factoryOscDac;
        TRACE_PRINTF("FreqSyncEntity::Startup very first set. m_liveOscDac set to %d",m_factoryOscDac);
    }

    m_XtalDac.Init(m_liveOscDac,m_oamDACCalSlope,true,4);

    SetDacValue(m_liveOscDac);

    BuildStateMachine();

    /* Set the state machine as constructed */
    m_stateMachine.SetConstructed();

    TRACE_PRINTF("FreqSyncEntity:: freq-sync StateMachine built successfully.");
    m_stateMachine.EventHappened(EventStartApp);
    EXIT();
}

void FreqSyncEntity::BuildStateMachine(void)
{
    TRACE_PRINTF("FreqSyncEntity:: Building freq-sync StateMachine");

    m_stateMachine.Reset();

    m_stateMachine.SetStateMachineName("Frequecy Sync Entity");
    m_stateMachine.InsertSimpleState("Initial",NULL,NULL);
    m_stateMachine.InsertSimpleState("Initializing",CreateCallback(&FreqSyncEntity::StateEntryInitializing),NULL);

#ifdef QC_TFCS
    m_stateMachine.InsertSimpleState("Getting GPS sync",CreateCallback(&FreqSyncEntity::StateEntryGettingGPSSync),NULL);
    m_stateMachine.InsertSimpleState("Cosc request",CreateCallback(&FreqSyncEntity::StateEntryCoscReq),NULL);
    m_stateMachine.InsertSimpleState("Acquire and sync GPS",CreateCallback(&FreqSyncEntity::StateEntryAcqAndSync),NULL);
    m_stateMachine.InsertSimpleState("Acquire and sync macro",CreateCallback(&FreqSyncEntity::StateEntryAcqAndSync),NULL);
#endif /* QC_TFCS */

    m_stateMachine.InsertSimpleState("Waiting FNTP alive",CreateCallback(&FreqSyncEntity::StateEntryWaitingFNTPAlive), CreateCallback(&FreqSyncEntity::StateExitWaitingFNTPAlive));
    m_stateMachine.InsertSimpleState("Sending FNTP accuracy",CreateCallback(&FreqSyncEntity::StateEntrySendingFNTPAccuracy),NULL);
    m_stateMachine.InsertSimpleState("Getting REM sync",CreateCallback(&FreqSyncEntity::StateEntryGettingREMScan),CreateCallback(&FreqSyncEntity::StateExitGettingREMScan));
    m_stateMachine.InsertSimpleState("REM inactive Getting FNTP time sync",CreateCallback(&FreqSyncEntity::StateEntryRemInactiveGettingFNTPTimeSync),NULL);
    m_stateMachine.InsertSimpleState("REM disable Getting FNTP sync",CreateCallback(&FreqSyncEntity::StateEntryRemDisableGettingFNTPSync),NULL);//may30
    m_stateMachine.InsertSimpleState("REM active Getting FNTP time sync",CreateCallback(&FreqSyncEntity::StateEntryGettingREMactiveGettingFNTPSync),CreateCallback(&FreqSyncEntity::StateExitGettingREMactiveGettingFNTPSync));
    m_stateMachine.InsertSimpleState("No FNTP or REM",CreateCallback(&FreqSyncEntity::StateEntryNoFNTPorREM),NULL);
    m_stateMachine.InsertSimpleState("FNTP getting first offset measurement",CreateCallback(&FreqSyncEntity::StateEntryGettingFirstFoff),CreateCallback(&FreqSyncEntity::StateExitGettingFirstFoff));
    m_stateMachine.InsertSimpleState("Long term FNTP",CreateCallback(&FreqSyncEntity::StateEntryLongTermFNTP),NULL);
    m_stateMachine.InsertSimpleState("Long Term REM mode no FNTP",CreateCallback(&FreqSyncEntity::StateEntryLongTermREMMode),NULL);
    m_stateMachine.InsertSimpleState("Getting Start Temperature",CreateCallback(&FreqSyncEntity::StateEntryGettingStartTemperature),NULL);
    m_stateMachine.InsertSimpleState("Idle State",NULL,NULL);


    m_stateMachine.InsertEventHandler(EventStartApp,"Initial",NULL,"Initializing");

    /* TFCS changes */
#ifdef QC_TFCS
    m_stateMachine.InsertEventHandler(EventInitialisationDone,"Initializing",NULL,"Getting GPS sync");
    m_stateMachine.InsertEventHandler(EventGPSSyncFailed,"Getting GPS sync",NULL,"Getting REM sync");
    m_stateMachine.InsertEventHandler(EventGPSSyncPassed,"Getting GPS sync",NULL,"Acquire and sync GPS");
    m_stateMachine.InsertEventHandler(EventREMSyncFailed,"Getting REM sync",NULL,"Waiting FNTP alive");
    m_stateMachine.InsertEventHandler(EventREMSyncPassed,"Getting REM sync",NULL,"Cosc request");
    m_stateMachine.InsertEventHandler(EventRemSyncDisabled,"Getting REM sync",NULL,"REM disable Getting FNTP sync");//may30
    m_stateMachine.InsertEventHandler(EventFNTPAlive,"REM disable Getting FNTP sync",NULL,"Waiting FNTP alive");//may30
    m_stateMachine.InsertEventHandler(EventFNTPSyncFailed,"Waiting FNTP alive",CreateCallback(&FreqSyncEntity::StateEntryFNTPSyncFailed),"Getting GPS sync");
    m_stateMachine.InsertEventHandler(EventCoscCnf,"Cosc request",NULL,"Acquire and sync macro");
/* new-changes: If coscCnf successful to same arfcn, sync with same source again */
    m_stateMachine.InsertEventHandler(EventCoscCnf,"Acquire and sync macro", CreateCallback(&FreqSyncEntity::StateEntryAcqAndSync), "Acquire and sync macro");
    m_stateMachine.InsertEventHandler(EventCoscFailed,"Cosc request",NULL,"Waiting FNTP alive");
    m_stateMachine.InsertEventHandler(EventFreqSyncCallbackTimeoutHappened,"Acquire and sync GPS",NULL,"Getting REM sync");
    m_stateMachine.InsertEventHandler(EventFreqSyncCallbackTimeoutHappened,"Acquire and sync macro",NULL,"Waiting FNTP alive");
    m_stateMachine.InsertEventHandler(EventFreqSyncCallbackTimeoutHappened,"Getting REM sync",NULL,"Waiting FNTP alive");//may30
    m_stateMachine.InsertEventHandler(EventFNTPDisabled,"Waiting FNTP alive",NULL,"Getting GPS sync");
    m_stateMachine.InsertEventHandler(EventFreqSyncCallbackTimeoutHappened,"Waiting FNTP alive",NULL,"Getting GPS sync");
#else
    m_stateMachine.InsertEventHandler(EventInitialisationDone,"Initializing",NULL,"Waiting FNTP alive");
    m_stateMachine.InsertEventHandler(EventREMSyncPassed,"Getting REM sync",NULL,"REM active Getting FNTP time sync");
    m_stateMachine.InsertEventHandler(EventREMSyncFailed,"Getting REM sync",NULL,"REM inactive Getting FNTP time sync");
#endif /* QC_TFCS */

    m_stateMachine.InsertEventHandler(EventFNTPAlive,"Waiting FNTP alive",NULL,"Sending FNTP accuracy");

#ifdef QC_TFCS
    m_stateMachine.InsertEventHandler(EventFNTPAccuracySent,"Sending FNTP accuracy",NULL,"REM inactive Getting FNTP time sync");
#else
    m_stateMachine.InsertEventHandler(EventFNTPAccuracySent,"Sending FNTP accuracy",NULL,"Getting REM sync");
#endif /* QC_TFCS */


#ifdef QC_TFCS
    m_stateMachine.InsertEventHandler(EventCallbackTimerExpired,"Getting GPS sync",NULL,"Getting REM sync");
    m_stateMachine.InsertEventHandler(EventCallbackTimerExpired,"Getting REM sync",NULL,"Waiting FNTP alive");
/* new-changes: If High uncertainity persists for some time, try to latch on to same cell first */
    m_stateMachine.InsertEventHandler(EventCallbackTimerExpired,"Acquire and sync macro", CreateCallback(&FreqSyncEntity::HandleAcqLostAndHighUncert), "Acquire and sync macro");
    m_stateMachine.InsertEventHandler(EventRetryTimerExpired,"No FNTP or REM",NULL,"Getting GPS sync");
#else /* QC_TFCS */
    m_stateMachine.InsertEventHandler(EventRetryTimerExpired,"No FNTP or REM",NULL,"Getting REM sync");
#endif /* QC_TFCS */

    m_stateMachine.InsertEventHandler(EventFNTPInitCnfReceivedFailed,"REM inactive Getting FNTP time sync",NULL,"No FNTP or REM");
    m_stateMachine.InsertEventHandler(EventFNTPInitCnfReceivedPassed,"No FNTP or REM",NULL,"Getting Start Temperature");
    m_stateMachine.InsertEventHandler(EventFNTPInitCnfReceivedPassed,"REM inactive Getting FNTP time sync",NULL,"Getting Start Temperature");
    m_stateMachine.InsertEventHandler(EventFNTPInitCnfReceivedFailed,"REM active Getting FNTP time sync",NULL,"Long Term REM mode no FNTP");
    m_stateMachine.InsertEventHandler(EventFNTPInitCnfReceivedPassed,"Long Term REM mode no FNTP",NULL,"Long term FNTP");
    m_stateMachine.InsertEventHandler(EventFNTPInitCnfReceivedPassed,"REM active Getting FNTP time sync",NULL,"Long term FNTP");
    m_stateMachine.InsertEventHandler(EventWarmStart,"Getting Start Temperature",NULL,"FNTP getting first offset measurement");
    m_stateMachine.InsertEventHandler(EventColdStart,"Getting Start Temperature",NULL,"FNTP getting first offset measurement");

    m_stateMachine.InsertEventHandler(EventFNTPGetFrequencyOffsetIndReceived,"FNTP getting first offset measurement",CreateCallback(&FreqSyncEntity::EventResponseFirstFrequencyOffsetIndReceived),"Long term FNTP");
    m_stateMachine.InsertEventHandler(EventFNTPSyncFailed,"FNTP getting first offset measurement",CreateCallback(&FreqSyncEntity::StateEntryFNTPSyncFailed),"Getting GPS sync");
    m_stateMachine.InsertEventHandler(EventFNTPGetFrequencyOffsetIndReceived,"Long term FNTP",CreateCallback(&FreqSyncEntity::EventResponseGetFrequencyOffsetIndReceived),"Long term FNTP");

#if 0
    StateMachine* syncStateOrthogonalsm = m_stateMachine.InsertOrthogonalStateMachine("Sync State orthogonal sm");

    syncStateOrthogonalsm->InsertSimpleState("Initial",NULL,NULL);
    syncStateOrthogonalsm->InsertSimpleState("Not recently synchronised",CreateCallback(&FreqSyncEntity::StateEntryNotRecentlySynchronised),CreateCallback(&FreqSyncEntity::StateExitNotRecentlySynchronised));
    syncStateOrthogonalsm->InsertSimpleState("Recently synchronised",CreateCallback(&FreqSyncEntity::StateEntryRecentlySynchronised),NULL);

    syncStateOrthogonalsm->InsertEventHandler(EventStartApp,"Initial",NULL,"Not recently synchronised");
    syncStateOrthogonalsm->InsertEventHandler(EventFNTPGetFrequencyOffsetIndReceived,"Not recently synchronised",NULL,"Recently synchronised");

#ifdef QC_TFCS
    syncStateOrthogonalsm->InsertEventHandler(EventSyncSuccessful,"Not recently synchronised",CreateCallback(&FreqSyncEntity::EventResponseRemSyncPassed),"Recently synchronised");
#else /* QC_TFCS */
    syncStateOrthogonalsm->InsertEventHandler(EventREMSyncPassed,"Not recently synchronised",CreateCallback(&FreqSyncEntity::EventResponseRemSyncPassed),"Recently synchronised");
#endif /* QC_TFCS */

    syncStateOrthogonalsm->InsertEventHandler(EventWarmStart,"Not recently synchronised",NULL,"Recently synchronised");
    syncStateOrthogonalsm->InsertEventHandler(EventFNTPGetFrequencyOffsetIndReceived,"Recently synchronised",NULL,"Recently synchronised");

#ifdef QC_TFCS
    syncStateOrthogonalsm->InsertEventHandler(EventSyncSuccessful,"Recently synchronised",CreateCallback(&FreqSyncEntity::EventResponseRemSyncPassed),"Recently synchronised");
#else /* QC_TFCS */
    syncStateOrthogonalsm->InsertEventHandler(EventREMSyncPassed,"Recently synchronised",CreateCallback(&FreqSyncEntity::EventResponseRemSyncPassed),"Recently synchronised");
#endif /* QC_TFCS */

#ifdef QC_TFCS
    syncStateOrthogonalsm->InsertEventHandler(EventSynchronisationExpired,"Recently synchronised",NULL,"Not recently synchronised");
#else /* QC_TFCS */
    syncStateOrthogonalsm->InsertEventHandler(EventSynchronisationExpired,"Recently synchronised",NULL,"Not recently synchronised");
#endif /* QC_TFCS */

    //NB the below is an internal event handler so does not cross the state boundary (NULL final state)
    syncStateOrthogonalsm->InsertEventHandler(EventFreqSyncActivityNotificationTimeoutHappened,"Recently synchronised",CreateCallback(&FreqSyncEntity::EventResponseFreqSyncActivityNotificationTimeoutHappened),NULL);
    syncStateOrthogonalsm->SetConstructed();
#endif /* if 0 */
}

void FreqSyncEntity::StateEntryInitializing(void)
{
#ifdef QC_TFCS
    if( !InitializeTFCS() )
    {
       TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS Initialization failure. Can not sync using GPS or Macro, moving to NTP");
       m_stateMachine.EventHappened(EventREMSyncFailed);
    }
#endif /* QC_TFCS */
    m_stateMachine.EventHappened(EventInitialisationDone);
}

#ifdef QC_TFCS
void FreqSyncEntity::StateEntryGettingGPSSync(void)
{  
    bool bGPSSyncEnable;
    MibHelper::GetMibAttributeDirect(PARAM_ID_GPS_SYNC_ENABLE, bGPSSyncEnable);

    if(bGPSSyncEnable)
    {
        if( !SetSyncSrcTFCS(SYNC_SRC_GPS) )
        {
            TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS GPS sync failed, moving to Macro based sync");
            m_stateMachine.EventHappened(EventGPSSyncFailed);
        }
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS GPS sync DISABLED in MIB, moving to Macro based sync");
        m_stateMachine.EventHappened(EventGPSSyncFailed);
    }
    /* Set the event to GPS sync passed */
    m_stateMachine.EventHappened(EventGPSSyncPassed);
} 

void FreqSyncEntity::StateEntryCoscReq(void)
{  
    /* Set GSM macro cell as sync source */
    if( !SetSyncSrcTFCS(SYNC_SRC_GSM) )
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS Macro sync failed, moving to FNTP based sync");
        m_stateMachine.EventHappened(EventREMSyncFailed);
    }
  
    /* Send message to NLM for doing COSC on a cell */
    SendNlmCoscReq();
}  

void FreqSyncEntity::SendNlmCoscReq(void)
{  
   CoscArfcnList list;
   u16           arfcn = 0;
   u8            idx = 0;
   u8            numArfcnsInMib = 0;

   /* Initialize the numArfcns to zero */
   list.numArfcns = 0;
   /* new-changes */
   m_coscArfcn = 0;
   m_retryCnt = 0;

   TRACE_PRINTF_LEV(TRACE_INFO, "FreqSyncEntity:: Getting the ARFCNs from MIB");

   MibHelper::GetMibAttributeDirect((MibAttributeId)((u32)PARAM_ID_NUM_GSM_INTERRAT_NCELLS), numArfcnsInMib);

   /* new-changes */
   for(idx = m_coscReqSentCntr; idx < numArfcnsInMib; idx++) 
   {                                         
      /* Put the arfcn in list, if it is valid */
      if(arfcn != 0)
      {
         list.arfcn[list.numArfcns++] = arfcn;
         TRACE_PRINTF_LEV(TRACE_INFO, "FreqSyncEntity:: Arfcn%hhu = %hu,", list.numArfcns-1, list.arfcn[list.numArfcns-1]);
      }

      /* If the arfcn list array is filled completely, send the msg */
      if( list.numArfcns >= (sizeof(list.arfcn)/sizeof(list.arfcn[0])) )
      {
         break;
      }
   }

   TRACE_PRINTF_LEV(TRACE_INFO, "FreqSyncEntity:: Number of GSM ARFCNs found in MIB = %hhu", list.numArfcns);

   /* Send message to REM for acquiring a cell */
   if(list.numArfcns > 0)
   {
      /* new-changes */
      m_coscReqSentCntr += list.numArfcns;
      TRACE_PRINTF("FreqSyncEntity:: Send the cosc msg to GSM_REM");

      NlmCoscReq NlmCoscReq(list);
      OamUserApplication::GetInstance().SendMessage(NlmCoscReq, ENTITY_GSM_REM, ENTITY_FREQ_SYNC); 
   }
   else
   {
      TRACE_PRINTF_LEV(TRACE_WARNING, "COSC failed for Macro sync, moving to FNTP based sync");
      m_stateMachine.EventHappened(EventCoscFailed);
   }
}

#endif /* QC_TFCS */

void FreqSyncEntity::StateEntryWaitingFNTPAlive(void)
{ 
    u32 timeoutvalue;
    OamUserApplication::GetInstance().GetTimeoutValue(timeoutvalue);
    if(timeoutvalue < FREQ_SYNC_CALLBACK_TIMEOUT_MS)
    {
        timeoutvalue = FREQ_SYNC_CALLBACK_TIMEOUT_MS;
    }

    bool bFNTPSyncEnable;
    MibHelper::GetMibAttributeDirect(PARAM_ID_FNTP_SYNC_ENABLE, bFNTPSyncEnable);

    if(bFNTPSyncEnable)
    {
        TRACE_PRINTF("FreqSyncEntity:: NTP Sync is enabled");
	#ifdef QC_TFCS
	if( !SetSyncSrcTFCS(SYNC_SRC_EXTERNAL) )
        {
            TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS NTP sync failed");
            m_stateMachine.EventHappened(EventFNTPSyncFailed);
        }
        else
        {
	#endif
        /* Start the callback timer */
        OamUserApplication::GetInstance().StartFreqSyncCallbackTimer(FREQ_SYNC_CALLBACK_TIMEOUT_MS);
	#ifdef QC_TFCS
        }
	#endif
    }
    else
    {
        TRACE_PRINTF("FreqSyncEntity:: NTP Sync is disabled");
        m_stateMachine.EventHappened(EventFNTPDisabled);
    }
}

void FreqSyncEntity::StateExitWaitingFNTPAlive(void)
{
    FreqSyncIsAliveInd msg(true);
    OamUserApplication::GetInstance().SendMessage(msg, ENTITY_NTP_CLIENT, ENTITY_FREQ_SYNC);
}
void FreqSyncEntity::StateEntrySendingFNTPAccuracy(void)
{
     OamUserApplication::GetInstance().StopFreqSyncCallbackTimer();//may30
     FNTPGetFrequencyOffsetReq msg(DEFAULT_REQUIRED_ACCURACY_PPB);
     OamUserApplication::GetInstance().SendMessage(msg, ENTITY_NTP_CLIENT, ENTITY_FREQ_SYNC);
     m_stateMachine.EventHappened(EventFNTPAccuracySent);
}

void FreqSyncEntity::StateEntryGettingREMScan(void)
{
    u32 chosenDac;
    bool bMacroSyncEnable;
    u32 timeoutvalue;
    OamUserApplication::GetInstance().GetTimeoutValue(timeoutvalue);
    MibHelper::GetMibAttributeDirect(PARAM_ID_MACRO_SYNC_ENABLE, bMacroSyncEnable);

    if(bMacroSyncEnable)
    {
                TRACE_PRINTF("FreqSyncEntity:: Macro Sync is enabled");
    if(m_remScanResult == REM_SCAN_RESULT_PASSED)
    	{       
	        chosenDac = m_liveOscDac;
        	TRACE_PRINTF_LEV(TRACE_INFO, "FreqSyncEntity: chosenDac is chosenDac = %d m_liveOscDac = %d", chosenDac, (int)m_liveOscDac);
        	m_stateMachine.EventHappened(EventREMSyncPassed);
    	}
    else if(m_remScanResult == REM_SCAN_RESULT_FAILED)
    	{
        	TRACE_PRINTF_LEV(TRACE_WARNING, "FreqSyncEntity: rem scan failed, moving to FNTP");
        	m_stateMachine.EventHappened(EventREMSyncFailed);
    	}
    else
    	{
        	/* Wait for Rem scan to happen */
        	TRACE_PRINTF_LEV(TRACE_WARNING, "FreqSyncEntity: rem scan not yet happened");
        	/* Start the callback timer */
        	TRACE_PRINTF_LEV(TRACE_INFO, "FreqSyncEntity: Timeout value is %dms",timeoutvalue);
        	OamUserApplication::GetInstance().StartFreqSyncCallbackTimer(timeoutvalue);
    	}
    }
    //may30
    else
    {
                TRACE_PRINTF("FreqSyncEntity:: Macro Sync is disabled");
                m_stateMachine.EventHappened(EventRemSyncDisabled);
    }
    //may30
}


void FreqSyncEntity::StateExitGettingREMScan(void)
{
    FNTPInitReq msg;
    OamUserApplication::GetInstance().SendMessage(msg, ENTITY_NTP_CLIENT, ENTITY_FREQ_SYNC);
}

void FreqSyncEntity::StateEntryNoFNTPorREM(void)
{
    shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::NTP_FREQUENCY_SYNCHRONISATION_FAILURE));

    AlarmEvent alarmEvent(
            alarmId,
            AlarmEvent::ALARM_EVENT_NONTRANSIENT,
            AlarmEvent::ALARM_SEVERITY_MAJOR,
            "NTP Frequency Synchronization Failure",
            AlarmEvent::ALARM_TYPE_PROCESSING);

    OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);

    m_stateMachine.EventHappened(EventSynchronisationExpired);

}

void FreqSyncEntity::StateEntryGettingREMactiveGettingFNTPSync(void)
{
    m_stateMachine.EventHappened(EventREMSyncPassed);
    if(m_timeSyncResult == TIME_SYNC_OK)
    {
        m_stateMachine.EventHappened(EventFNTPInitCnfReceivedPassed);
        TRACE_PRINTF("FreqSyncEntity::StateEntryGettingREMactiveGettingFNTPSync  time sync OK");
    }
    else if(m_timeSyncResult == TIME_SYNC_NOT_OK)
    {
        TRACE_PRINTF("FreqSyncEntity::StateEntryGettingREMactiveGettingFNTPSync  time sync NOT OK");
        m_stateMachine.EventHappened(EventFNTPInitCnfReceivedFailed);
    }
    else
    {
        TRACE_PRINTF("FreqSyncEntity::StateEntryGettingREMactiveGettingFNTPSync as yet no time sync");
    }
}

void FreqSyncEntity::StateExitGettingREMactiveGettingFNTPSync(void)
{
    FNTPSetSampleModeReq msg(LONG_TERM);
     OamUserApplication::GetInstance().SendMessage(msg, ENTITY_NTP_CLIENT, ENTITY_FREQ_SYNC);
}

//may30
void FreqSyncEntity::StateEntryRemDisableGettingFNTPSync(void)
{
        TRACE_PRINTF("FreqSyncEntity::StateEntryRemDisabledGettingFNTPSync - wait for FNTP alive ind");
}
//may30

void FreqSyncEntity::StateEntryRemInactiveGettingFNTPTimeSync(void)
{
    shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::OTA_FREQUENCY_SYNCHRONISATION_FAILURE));

            AlarmEvent alarmEvent(
                    alarmId,
                    AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                    AlarmEvent::ALARM_SEVERITY_MAJOR,
                    "OTA Frequency Synchronization Failure",
                    AlarmEvent::ALARM_TYPE_PROCESSING);

            OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);

            if(m_timeSyncResult == TIME_SYNC_OK)
            {
                m_stateMachine.EventHappened(EventFNTPInitCnfReceivedPassed);
            }
            else if(m_timeSyncResult == TIME_SYNC_NOT_OK)
            {
                m_stateMachine.EventHappened(EventFNTPInitCnfReceivedFailed);
            }
}

void FreqSyncEntity::StateEntryGettingStartTemperature(void)
{
    struct timeval tv;
    u32 tinSecsOfLastSync;
    u32 dacVal;
    gettimeofday(&tv, NULL);
    MibHelper::GetMibAttributeDirect(PARAM_ID_FREQ_SYNC_ACTIVITY_TIMESTAMP,tinSecsOfLastSync);
    TRACE_PRINTF("last sync = %d time (s) = %d",tinSecsOfLastSync,((u32)(tv.tv_sec)));

    if((((u32)(tv.tv_sec)) - tinSecsOfLastSync) <= NUM_SECS_BEFORE_SYNC_WARM_START)
    {
        MibHelper::GetMibAttributeDirect(PARAM_ID_LIVE_OSC_DAC,dacVal);
        m_liveOscDac = dacVal;
        TRACE_PRINTF("#########################################SYNC WARM START..")
        m_stateMachine.EventHappened(EventWarmStart);
    }
    else
    {
        TRACE_PRINTF("#########################################SYNC COLD START..")
        m_liveOscDac = m_factoryOscDac;
        SetDacValue(m_liveOscDac);
        m_stateMachine.EventHappened(EventColdStart);
    }
}

void FreqSyncEntity::StateEntryGettingFirstFoff(void)
{

}

void FreqSyncEntity::StateExitGettingFirstFoff(void)
{
    SetXtalSyncedOAMFlag(true);
    FNTPSetSampleModeReq msg(LONG_TERM);
    OamUserApplication::GetInstance().SendMessage(msg, ENTITY_NTP_CLIENT, ENTITY_FREQ_SYNC);
}


void FreqSyncEntity::StateEntryNotRecentlySynchronised(void)
{
    shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::NO_FREQUENCY_DISCIPLINE));

    TRACE_PRINTF("FreqSyncEntity::StateEntryNotRecentlySynchronised setting alarm");

     AlarmEvent alarmEvent(
             alarmId,
             AlarmEvent::ALARM_EVENT_NONTRANSIENT,
             AlarmEvent::ALARM_SEVERITY_MAJOR,
             "No FrequencyDiscipline",
             AlarmEvent::ALARM_TYPE_PROCESSING);

     OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);

     InformOAMThatFrequencySynchronisationHasBeenLost();
}

void FreqSyncEntity::StateExitNotRecentlySynchronised(void)
{
    //Cancel NO_FREQUENCY_DISCIPLINE alarm
     shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::NO_FREQUENCY_DISCIPLINE));

     TRACE_PRINTF("FreqSyncEntity::StateExitNotRecentlySynchronised clearing alarm");

      AlarmEvent alarmEvent(
              alarmId,
              AlarmEvent::ALARM_EVENT_NONTRANSIENT,
              AlarmEvent::ALARM_SEVERITY_CLEARED,
              "Cleared No Frequency Discipline alarm",
              AlarmEvent::ALARM_TYPE_PROCESSING);

      OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);

}


void FreqSyncEntity::StateEntryRecentlySynchronised(void)
{
    OamUserApplication::GetInstance().StartFreqSyncExpiryTimer(FREQ_SYNC_EXPIRY_TIMEOUT_MS);

    SetDacValue(m_liveOscDac);

    SetXtalSyncedOAMFlag(true);

    RecordFreqSyncActivity();

    OamUserApplication::GetInstance().StartFreqSyncActivityNotificationTimer(FREQ_SYNC_ACTIVITY_TIMEOUT_MS);

    InformOAMThatFrequencySynchronisationHasBeenAchieved();
}

void FreqSyncEntity::SetTimeOfLastSyncToNow(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_TIME_OF_LAST_SYNC, ((u32)(tv.tv_sec)));
    OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_FREQ_SYNC);
}

void FreqSyncEntity::EventResponseRemSyncPassed(void)
{
    SetTimeOfLastSyncToNow();
}

void FreqSyncEntity::EventResponseGetFrequencyOffsetIndReceived(void)
{

    PerformSoftSync();

    SetTimeOfLastSyncToNow();

    if(m_XtalDac.GetUnstable())
    {
        shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::OSCILLATOR_STABILITY_PROBLEM));

                AlarmEvent alarmEvent(
                        alarmId,
                        AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                        AlarmEvent::ALARM_SEVERITY_MAJOR,
                        "Oscillator Stability Problem",
                        AlarmEvent::ALARM_TYPE_PROCESSING);

                OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);
    }
}

void FreqSyncEntity::EventResponseFirstFrequencyOffsetIndReceived(void)
{
	PerformSoftSync();
}

void FreqSyncEntity::StateEntryLongTermFNTP(void)
{
    TRACE_PRINTF("Found NTP Est State  entry");
}

void FreqSyncEntity::StateEntryLongTermREMMode(void)
{
    shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::NTP_FREQUENCY_SYNCHRONISATION_FAILURE));

    AlarmEvent alarmEvent(
            alarmId,
            AlarmEvent::ALARM_EVENT_NONTRANSIENT,
            AlarmEvent::ALARM_SEVERITY_MAJOR,
            "NTP Frequency Synchronization Failure",
            AlarmEvent::ALARM_TYPE_PROCESSING);

    OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);
}

void FreqSyncEntity::StateEntryFNTPSyncFailed(void)
{
    shared_ptr<FapAlarmId> alarmId(new FapAlarmId( FapAlarmId::NTP_FREQUENCY_SYNCHRONISATION_FAILURE));

    AlarmEvent alarmEvent(
            alarmId,
            AlarmEvent::ALARM_EVENT_NONTRANSIENT,
            AlarmEvent::ALARM_SEVERITY_MAJOR,
            "NTP Frequency Synchronization Failure",
            AlarmEvent::ALARM_TYPE_PROCESSING);

    OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);
}

void FreqSyncEntity::PerformSoftSync(void)
{
	#ifdef QC_TFCS	
	s32    retVal;
	#endif
        float  clkFreqError;
        clkFreqError = (float)m_liveOscDac;
        //TODO - Check is required here

         /* Do soft sync with time and frequency corrections */
	#ifdef QC_TFCS	
        retVal = tfcs_sync(m_tfcsHandle, SYNC_TYPE_SOFT_SYNC, 0 , clkFreqError);
        if (retVal != TFCS_API_SUCCESS)
        {
           TRACE_PRINTF_LEV(TRACE_WARNING, "ERR: Soft Sync failed...");
           return;
        }
	#endif
        /* Got the Sync Report from TFCS */
        m_stateMachine.EventHappened(EventSyncSuccessful);

        /* Stop the callback timer */
        OamUserApplication::GetInstance().StopFreqSyncCallbackTimer();

	#ifdef QC_TFCS	
        m_tfcsSysStateFlag = TFCS_SYS_OUT_OF_SYNC;
	#endif
        TRACE_PRINTF("TCXO Status: Out of sync\n");
        TRACE_PRINTF("Action: Soft Sync (%f (ppb))\n", clkFreqError);

}

void FreqSyncEntity::SetXtalSyncedOAMFlag(bool xtalSynced)
{
    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_XTAL_SYNCED, xtalSynced);
    OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_FREQ_SYNC);
}

void FreqSyncEntity::HandleMessage(shared_ptr<MessageSerialisedData> message)
{

    if(message)
    {
        SerialisationId serialisationId = (SerialisationId)message->GetSerialisationId();
        switch(serialisationId)
        {
            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
            {

            }
            break;

            case SERIALISATION_ID_REGISTER_ENTITY_CNF:
            {
                shared_ptr<RegisterEntityCnf> registerEntityCnf = Serialisable::DeSerialise<RegisterEntityCnf>(message);
                RSYS_ASSERT(registerEntityCnf != NULL);

                TRACE("FreqSyncEntity: RegisterEntityCnf received", registerEntityCnf->ToString());
            }
            break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF:
            {
                shared_ptr<MibSubscribeAttributesCnf> mibSubscribeAttributesCnf = Serialisable::DeSerialise<MibSubscribeAttributesCnf>(message);
                RSYS_ASSERT(mibSubscribeAttributesCnf != NULL);

                TRACE("FreqSyncEntity: MibSubscribeAttributesCnf received", mibSubscribeAttributesCnf->ToString());
            }
            break;

            case SERIALISATION_ID_MIB_GET_ATTRIBUTES_CNF:
            {
                shared_ptr<MibGetAttributesCnf> mibGetAttributesCnf = Serialisable::DeSerialise<MibGetAttributesCnf>(message);
                RSYS_ASSERT(mibGetAttributesCnf != NULL);

                TRACE("FreqSyncEntity: MibGetAttributesCnf received", mibGetAttributesCnf->ToString());
            }
            break;

            case SERIALISATION_ID_MIB_SET_ATTRIBUTES_CNF:
            {
                shared_ptr<MibSetAttributesCnf> mibSetAttributesCnf = Serialisable::DeSerialise<MibSetAttributesCnf>(message);
                RSYS_ASSERT(mibSetAttributesCnf);

                TRACE("FreqSyncEntity: MibSetAttributesCnf received", mibSetAttributesCnf->ToString());
            }
            break;

            case SERIALISATION_ID_FNTP_GET_FREQUENCY_OFFSET_IND:
            {
                TRACE_PRINTF("Received SERIALISATION_ID_FNTP_GET_FREQUENCY_OFFSET_IND");
                shared_ptr<FNTPGetFrequencyOffsetInd> FrequencyOffsetInd = Serialisable::DeSerialise<FNTPGetFrequencyOffsetInd>(message);
                m_currentDACOffsetppb = FrequencyOffsetInd->GetFrequencyOffsetppb();
                TRACE_PRINTF("FrequencyOffsetppb = %" PRId32, m_currentDACOffsetppb);
                TRACE_PRINTF("Msg  = %s",(FrequencyOffsetInd->ToString().c_str()));
                m_XtalDac.AddFreqEstimate(m_currentDACOffsetppb);
                m_liveOscDac = m_XtalDac.GetDacValue();
		#ifdef QC_TFCS
 		if( !SyncUsingTFCSWithoutAcquire() )
    		{
        		TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS sync using FNTP failed, moving to long term FNTP based sync");
        		m_stateMachine.EventHappened(EventFNTPSyncFailed);
    		}		
		#endif
                m_stateMachine.EventHappened(EventFNTPGetFrequencyOffsetIndReceived);
            }
            break;

            case SERIALISATION_ID_FNTP_INIT_CNF:
            {
                TRACE_PRINTF("Received SERIALISATION_ID_FNTP_INIT_CNF");
                shared_ptr<FNTPInitCnf> InitCnf = Serialisable::DeSerialise<FNTPInitCnf>(message);
                if( InitCnf->GetSuccess())
                {
                    m_stateMachine.EventHappened(EventFNTPInitCnfReceivedPassed);
                    m_timeSyncResult = TIME_SYNC_OK;
                }
                else
                {
                    m_stateMachine.EventHappened(EventFNTPInitCnfReceivedFailed);
                    m_timeSyncResult = TIME_SYNC_NOT_OK;
                }
            }
            break;

            case SERIALISATION_ID_FNTP_SET_SAMPLE_MODE_CNF:
            {
                TRACE_PRINTF("Received SERIALISATION_ID_FNTP_SET_SAMPLE_MODE_CNF");
                m_stateMachine.EventHappened(EventFNTPSetSampleModeCnfReceived);
            }
            break;

            case SERIALISATION_ID_FNTP_IS_ALIVE_IND:
            {
                shared_ptr<FNTPIsAliveInd> isAliveInd = Serialisable::DeSerialise<FNTPIsAliveInd>(message);
                m_simulatorActive = isAliveInd->GetSimulatorActive();
                TRACE_PRINTF("Received SERIALISATION_ID_FNTP_IS_ALIVE_IND with simulator active = %d",m_simulatorActive);
                TRACE_PRINTF("Alive msg = %s",(isAliveInd->ToString()).c_str());
                m_stateMachine.EventHappened(EventFNTPAlive);
            }
            break;

            case SERIALISATION_ID_REM_GSM_REM_DAC_ESTIMATE_IND:
            {
    /* new-changes */
                /* Stop the callback timer */
                OamUserApplication::GetInstance().StopFreqSyncCallbackTimer();

                TRACE_PRINTF("FreqSyncEntity:: DAC estimate ind received");
                shared_ptr<RemGsmRemDACEstimateInd> req = Serialisable::DeSerialise<RemGsmRemDACEstimateInd>(message);


                m_liveOscDac = req->GetDACEstimate();
                if(req->GetremGsmRemScanWasOK())
                {
                    TRACE_PRINTF("FreqSyncEntity:: EventREMSyncPassed, GSM Scan OK");
                    m_stateMachine.EventHappened(EventREMSyncPassed);
                }
                else
                {
                    TRACE_PRINTF("FreqSyncEntity:: EventREMSyncFailed, GSM Scan NOT OK");
                    m_stateMachine.EventHappened(EventREMSyncFailed);
                }

            }
            break;

            case SERIALISATION_ID_NLM_COSC_CNF:
            {
                shared_ptr<NlmCoscCnf> cnf = Serialisable::DeSerialise<NlmCoscCnf>(message);

                RSYS_ASSERT(cnf != NULL);
                if(cnf->GetNlmCoscResult() == NLM_COSC_SUCCESSFUL)
                {
                   /* new-changes */
		   #ifdef QC_TFCS
                   m_coscArfcn = cnf->GetNlmCoscArfcn();
                   TRACE_PRINTF("Received COSC confirm from NLM on ARFCN = (%"PRId16")", m_coscArfcn);
		   #endif
                   m_stateMachine.EventHappened(EventCoscCnf);
                }
                else
                {
                   TRACE_PRINTF_LEV(TRACE_WARNING, "COSC failed for Macro sync, moving to FNTP based sync");
                   m_stateMachine.EventHappened(EventCoscFailed);
		   #ifdef QC_TFCS
                   SendNlmCoscReq();
		   #endif
                }
            }
            break;

            case SERIALISATION_ID_CPHY_NLM_ERR_IND:
            {
                shared_ptr<CPhyNlmErrInd> ind = Serialisable::DeSerialise<CPhyNlmErrInd>(message);

                RSYS_ASSERT(ind != NULL);
                if(ind->GetErrCode() == NLM_COSC_LOST)
                {
                   /* Handle the acquire lost scenario */
		   #ifdef QC_TFCS
                   FreqSyncEntity::HandleAcqLostAndHighUncert();
		   #endif
                }
                else
                {
                   TRACE_PRINTF_LEV(TRACE_WARNING, "Unknown error received from NLM");
                   m_stateMachine.EventHappened(EventCoscFailed);
                }
            }
            break;

            default:
                TRACE("FreqSyncEntity: Unhandled message", message->ToString());
                break;
        }
    }
}


bool FreqSyncEntity::SetDacValue(u32 dacVal)
{
    ENTER();

    bool retVal = true;

    TRACE_PRINTF("Updating DAC value with %" PRIu32, dacVal);
    if(!m_simulatorActive)
    {
        MibAttributeValues attrs;
        attrs.AddAttribute(PARAM_ID_LIVE_OSC_DAC, dacVal);
        OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_FREQ_SYNC);
    }
    else
    {
        FreqSyncSetFakeDAC FreqSyncSetFakeDACmsg(dacVal);
        OamUserApplication::GetInstance().SendMessage(FreqSyncSetFakeDACmsg, ENTITY_NTP_CLIENT, ENTITY_FREQ_SYNC);
        retVal = true;
    }

    if(m_recordDACAdjustments)
    {
       /* vineet: compilation error */
/*        TRACE_PRINTF(m_dacAdjustFile,"%d\n",(int)dacVal); */
    }

    RETURN(retVal);
}

void  FreqSyncEntity::InformOAMThatFrequencySynchronisationHasBeenAchieved()
{
    MfOpStateInformInd opStateInform(MF_FREQUENCY_OFFSET, ManagedObject::OP_STATE_ENABLED, 0, "Frequency Offset Found");
    OamUserApplication::GetInstance().SendMessage(opStateInform, ENTITY_OAM, ENTITY_FREQ_SYNC);
}

void  FreqSyncEntity::InformOAMThatFrequencySynchronisationHasBeenLost()
{
    TRACE_PRINTF("FreqSyncEntity::InformOAMThatFrequencySynchronisationHasBeenLost. Sync has been lost. Telling OAM to turn off FAP.")
    MfOpStateInformInd opStateInform(MF_FREQUENCY_OFFSET, ManagedObject::OP_STATE_DISABLED, 0, "Frequency Offset Lost");
    OamUserApplication::GetInstance().SendMessage(opStateInform, ENTITY_OAM, ENTITY_FREQ_SYNC);
}


void FreqSyncEntity::FreqSyncExpiryTimeoutHappened()
{
    m_stateMachine.EventHappened(EventSynchronisationExpired);
}

void FreqSyncEntity::FreqSyncActivityNotificationTimeoutHappened()
{
    m_stateMachine.EventHappened(EventFreqSyncActivityNotificationTimeoutHappened);
}

/* Callback from TFCS or NTP not received */
#ifdef QC_TFCS
void FreqSyncEntity::FreqSyncCallbackTimeoutHappened()
{
    m_stateMachine.EventHappened(EventFreqSyncCallbackTimeoutHappened);
}
#endif

void FreqSyncEntity::RecordFreqSyncActivity(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_FREQ_SYNC_ACTIVITY_TIMESTAMP, ((u32)(tv.tv_sec)));
    OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_FREQ_SYNC);
}

void FreqSyncEntity::EventResponseFreqSyncActivityNotificationTimeoutHappened(void)
{
    RecordFreqSyncActivity();
}

CallbackBase*  FreqSyncEntity::CreateCallback(void (FreqSyncEntity::*Callback)(void))
{
ENTER();
FNTPcallback<FreqSyncEntity>* retVal = new(FNTPcallback<FreqSyncEntity>);

    retVal->SetInstance(this);
    retVal->SetMethod(Callback);

RETURN(retVal);
}

#ifdef QC_TFCS

void  FreqSyncEntity::InformOAMThatNbrCellNotFound()
{
    TRACE_PRINTF("FreqSyncEntity::InformOAMThatNbrCellNotFound. No nbr cells found in MIB to do COSC. Telling OAM to trigger REM SCAN.")
    MfOpStateInformInd opStateInform(MF_FREQUENCY_OFFSET, ManagedObject::OP_STATE_DISABLED, 0, "GSM Cell not found");
    OamUserApplication::GetInstance().SendMessage(opStateInform, ENTITY_OAM, ENTITY_FREQ_SYNC);
}

bool  FreqSyncEntity::InitializeTFCS()
{
    tfcs_event_mask_type eventRegMask = 0xffffffff;

    TRACE_PRINTF("FreqSyncEntity::InitializeTFCS, Initializing TFCS client")

    /* Call QC-API for initializing tfcs module */
    if( !tfcs_init() )
    {
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "tfcs_init() API failed ...");
        RETURN(FALSE);
    }
    else
    {  
        TRACE_PRINTF("TFCS Initialized successfully");

        /* Set event mask to event and sync reports */
        eventRegMask = TFCS_EVENT_CONFIG_REPORT | TFCS_EVENT_SYNCHRONIZATION_REPORT;

        /* Call QC-API for registering tfcs handler */
        m_tfcsHandle = tfcs_open (eventRegMask, hdlTfcsEvtCallback);

        if(m_tfcsHandle == TFCS_CLIENT_HANDLE_INVALID)
        {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "tfcs_open API returned Error: TFCS_CLIENT_HANDLE_INVALID. tfcsHandler = %d", m_tfcsHandle);
            /* If tfcs_open does not return valid clientId return error */
            RETURN(FALSE);
        }
        else if(m_tfcsHandle == TFCS_API_RPC_FAILURE)
        {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "tfcs_open API returned Error: TFCS_API_RPC_FAILURE.");
            /* If tfcs_open does not return valid clientId return error */
            RETURN(FALSE);
        }
        else
        {
            TRACE_PRINTF("\n tfcs_open API Successful. \n  Client Id = (%"PRId32") \n\n", m_tfcsHandle);
            RETURN(TRUE); 
        } 
    } 
    RETURN(TRUE); 
}

bool  FreqSyncEntity::SetSyncSrcTFCS(tfcs_configuration_e_type syncSrc)
{ 
    int ret = 0;
    tfcs_synchronization_criteria_s_type  configData;

    /* Set the Configuration parameters */
    configData.sync_config = syncSrc;
    configData.enable_pp2s = 1;
    configData.valid_mask = 0xFF;

    /* Call the API to set the cofig params */
    ret = tfcs_set_config(m_tfcsHandle, &configData);

    if(ret == TFCS_API_INVALID_HANDLE)
    {
        TRACE_PRINTF("tfcs_set_config API returned Error: TFCS_API_INVALID_HANDLE. tfcsHandler = %d", m_tfcsHandle);
        /* If tfcs_set_config does not return valid clientId return error */
        RETURN(FALSE);
    }
    else
    {
        TRACE_PRINTF("tfcs_set_config API Successful.");
        /* Set the source for tfcs_acquire */
        m_tfcsAcqConfig = syncSrc;
    } 

    RETURN(TRUE);
}

bool FreqSyncEntity::SyncUsingTFCSWithoutAcquire()
{
    s32 ret = 0;

    /* Call the API to get the cofig params */
    ret = tfcs_get_config(m_tfcsHandle);

    if(ret == TFCS_API_INVALID_HANDLE)
    {
        TRACE_PRINTF("\n tfcs_get_config API returned Error: TFCS_API_INVALID_HANDLE. tfcsHandler = %d \n\n", m_tfcsHandle);
        RETURN(FALSE);
    }
    else
    {
        TRACE_PRINTF("\n tfcs_get_config API Successful. \n\n");
    }
RETURN(TRUE);
}

/*********************************************
 * Acquire and Sync state entry function 
 *********************************************/
void FreqSyncEntity::StateEntryAcqAndSync()
{
    if( !SyncUsingTFCS() )
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS sync using GPS/Macro failed, moving to FNTP based sync");
        m_stateMachine.EventHappened(EventREMSyncFailed);
    }
}

bool FreqSyncEntity::SyncUsingTFCS()
{
    s32 ret = 0;

    /* Call the API to get the cofig params */
    ret = tfcs_get_config(m_tfcsHandle);

    if(ret == TFCS_API_INVALID_HANDLE)
    {
        TRACE_PRINTF("\n tfcs_get_config API returned Error: TFCS_API_INVALID_HANDLE. tfcsHandler = %d \n\n", m_tfcsHandle);
        RETURN(FALSE);
    }
    else
    {
        TRACE_PRINTF("\n tfcs_get_config API Successful. \n\n");
    } 

    /* Call the API to Get the sync report */ 
    ret = tfcs_acquire(m_tfcsHandle, m_tfcsAcqConfig);

    if(ret == TFCS_API_INVALID_HANDLE)
    {
        TRACE_PRINTF("tfcs_acquire API returned Error: TFCS_API_INVALID_HANDLE.");
        /* If tfcs_acquire does not return valid clientId return error */
        RETURN(FALSE);
    }
    else
    {
       TRACE_PRINTF("tfcs_acquire API Successful. Waiting for callBack.");
       /* Update the TFCS system state to acquire done */
       m_tfcsSysStateFlag = TFCS_SYS_ACQ_DONE;

       /* Start the callback timer */
       OamUserApplication::GetInstance().StartFreqSyncCallbackTimer(FREQ_SYNC_CALLBACK_TIMEOUT_MS);
    } 

    RETURN(TRUE);
}



#ifdef __cplusplus
extern "C" {
#endif

      
 /*********************************************
 * Event CallBack Handler Function
 *********************************************/
int hdlTfcsEvtCallback ( 
      tfcs_client_handle_type tfcs_handle, 
      tfcs_event_mask_type tfcs_event, 
      const tfcs_event_payload_u_type *tfcs_event_payload )  
{
   /* Store the sync report */
   OamUserApplication::GetInstance().m_freqSyncEntity.StoreSyncReportTFCS(tfcs_event_payload);

   if(tfcs_event == TFCS_EVENT_SYNCHRONIZATION_REPORT)
   { 

      TRACE_PRINTF_LEV(TRACE_VERBOSE, "\n*******************SYNC REPORT*******************");
      if( tfcs_event_payload->sync_report.sync_status & TFCS_SYNC_STATUS_MASK_SYNC)
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nPP2S TRIGGER                 : ENABLED" );
      }
      else
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nPP2S TRIGGER                 : DISABLED");
      }

      switch((tfcs_event_payload->sync_report.sync_status & TFCS_SYNC_STATUS_MASK_SYNC_SOURCE) >> 1)
      {
         /*as this call back is only for Macro disciplining,the source can be UMTS(primarly)*/
         /*it can also be GPS if the signal is available.hence print only these values*/
         case 0:
            TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nTime Source                  : GPS" );
            break;

         case 4:
            TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nTime Source                  : UMTS");
            break;

         default:
            TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nTime Source                  : Non UMTS");
            break;
      }

      if( tfcs_event_payload->sync_report.sync_status & TFCS_SYNC_STATUS_MASK_VCTCXO_ACCESS )
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nVCTCXO access                : Failed");
      }
      else
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nVCTCXO access                : Success ");
      }

      if( tfcs_event_payload->sync_report.sync_status & TFCS_SYNC_STATUS_MASK_FTM_ACCESS)
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nTiming hardware access       : Failed");
      }
      else
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nTiming hardware access       : Success ");
      }

      TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nGPS Millisecond              : %ld", tfcs_event_payload->sync_report.tfcs_time.gps_msec);
      TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nGPS Week Number              : %d", tfcs_event_payload->sync_report.tfcs_time.gps_week);
      TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nClock Time Bias (us)         : %f", tfcs_event_payload->sync_report.tfcs_time.clk_time_error);
      TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nClock Time Uncertainty (us)  : %f", tfcs_event_payload->sync_report.tfcs_time.clk_time_uncertainty);
      TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nClock Freq Bias (ppb)        : %f", tfcs_event_payload->sync_report.tfcs_freq.clk_freq_error);
      TRACE_PRINTF_LEV(TRACE_VERBOSE, " \nClock Freq Uncertainity (ppb): %f\n", tfcs_event_payload->sync_report.tfcs_freq.clk_freq_uncertainty);

      /* Continously monitor for the Freq errors from a Macro*/
      /* Apply Soft Sync when the Freq error/uncertainty values exceed the i/p values */
      OamUserApplication::GetInstance().m_freqSyncEntity.MonitorFreqBiasTFCS();
   }

   else if (tfcs_event == TFCS_EVENT_CONFIG_REPORT)
   {
      if(tfcs_event_payload->config_report.status == 0x0)
      {
         TRACE_PRINTF("\n------------CONFIG REPORT------------\n");
         TRACE_PRINTF(" \ntfcs status      : TFCS_API_SUCCESS");

         /*as the source can be either UMTS/GPS,handle only these 2 sources*/
         if (tfcs_event_payload->config_report.type == SYNC_SRC_GPS)
         {
            TRACE_PRINTF(" \ntfcs sync source : GPS");
         }
         else if (tfcs_event_payload->config_report.type == SYNC_SRC_UMTS)
         {
            TRACE_PRINTF(" \ntfcs sync source : UMTS");
         }
         else if (tfcs_event_payload->config_report.type == SYNC_SRC_EXTERNAL)
         {
            TRACE_PRINTF(" \ntfcs sync source : NTP");
         }
         else
         {
            TRACE_PRINTF(" \ntfcs sync source : NON-UMTS source");
         }
         TRACE_PRINTF(" \ntfcs sync config : %d", tfcs_event_payload->config_report.data.sync_criteria.sync_config);
         TRACE_PRINTF(" \ntfcs enable pp2s : %d", tfcs_event_payload->config_report.data.sync_criteria.enable_pp2s);
         TRACE_PRINTF("\n-------------------------------------\n");
      }
      else
      {
         TRACE_PRINTF_LEV(TRACE_WARNING, " \ntfcs status      : TFCS_API_INVALID_HANDLE");
      }
   }
   else
   {
      TRACE_PRINTF_LEV(TRACE_WARNING, "\n Invalid TFCS event in callback \n");
   }

   RETURN(0);
} 

#ifdef __cplusplus
}
#endif /* __cplusplus */
 
/*********************************************
 * Funtion to store the sync report 
 *********************************************/
void FreqSyncEntity::StoreSyncReportTFCS(const tfcs_event_payload_u_type *tfcs_event_payload)
{

   m_syncReport.sync_status = tfcs_event_payload->sync_report.sync_status;
   m_syncReport.tfcs_freq.clk_freq_error = tfcs_event_payload->sync_report.tfcs_freq.clk_freq_error;
   m_syncReport.tfcs_freq.clk_freq_uncertainty = tfcs_event_payload->sync_report.tfcs_freq.clk_freq_uncertainty;
   m_syncReport.tfcs_time.gps_msec = tfcs_event_payload->sync_report.tfcs_time.gps_msec;
   m_syncReport.tfcs_time.gps_week = tfcs_event_payload->sync_report.tfcs_time.gps_week;
   m_syncReport.tfcs_time.clk_time_error = tfcs_event_payload->sync_report.tfcs_time.clk_time_error;
   m_syncReport.tfcs_time.clk_time_uncertainty = tfcs_event_payload->sync_report.tfcs_time.clk_time_uncertainty;

   return;
}

 
/*********************************************
 * Funtion to monitor freq bias
 *********************************************/
void FreqSyncEntity::MonitorFreqBiasTFCS(void)
{
    bool   pp2sState;
    float  clkFreqError = 0.0;
    float  clkFreqUncertainty = 0.0;
    float  clkTimeError = 0.0 ;
    float  clkTimeUncertainty = 0.0;
    s32    retVal;

    pp2sState = m_syncReport.sync_status;
    clkFreqError = m_syncReport.tfcs_freq.clk_freq_error;
    clkFreqUncertainty = m_syncReport.tfcs_freq.clk_freq_uncertainty;
    clkTimeError = m_syncReport.tfcs_time.clk_time_error;
    clkTimeUncertainty = m_syncReport.tfcs_time.clk_time_uncertainty;

    /* Perform action based on the current system state */
    switch (m_tfcsSysStateFlag)
    {
        case TFCS_SYS_NONE:
            break;
        case TFCS_SYS_ACQ_IN_PROGRESS:
            break;
        case TFCS_SYS_ACQ_DONE:
        {
            /*Dont apply Hard sync if the freq uncertainty is a huge value*/
            /*Do Hard Sync if the freq uncertainty is within MACRO_FREQ_UNCERT_MAXVALUE*/
            if (fabs(clkFreqUncertainty) <= TFCS_FREQ_UNCERT_MAXVALUE)
            {
               /* If acquisition is done, do a hard sync */
               TRACE_PRINTF("***************************\n");
               TRACE_PRINTF("TCXO Status: None \n");
               TRACE_PRINTF("Action: Hard sync issued\n");
               m_tfcsSysStateFlag = TFCS_SYS_HARD_SYNC_IN_PROGRESS;

               retVal =  tfcs_sync(m_tfcsHandle, SYNC_TYPE_HARD_SYNC, 0, clkFreqError);

               if (retVal != TFCS_API_SUCCESS)
               {
                  TRACE_PRINTF_LEV(TRACE_WARNING, "ERR: Hard Sync is failed...");
                  return;  
               }

               /* Got the Sync Report from TFCS */
               m_stateMachine.EventHappened(EventSyncSuccessful);
            }
         }
         break;

         case TFCS_SYS_HARD_SYNC_IN_PROGRESS:
         {
            /* If PP2S is enabled, change state to hard sync done */
            if (pp2sState & TFCS_SYNC_STATUS_MASK_SYNC)
            {
                TRACE_PRINTF("***************************\n");
                TRACE_PRINTF("TCXO Status: None\n");
                TRACE_PRINTF("Action: Hard sync done\n");
                m_tfcsSysStateFlag = TFCS_SYS_HARD_SYNC_DONE;
            }
         }
         break;

         case TFCS_SYS_HARD_SYNC_DONE:
         case TFCS_SYS_IN_SYNC:
         case TFCS_SYS_OUT_OF_SYNC:
         {
            TRACE_PRINTF("\n#### Sync status (as per user defined thresholds) ####\n");

            /* Do soft sync if freq error limits are crossed */
            if (fabs(clkFreqError) > TFCS_FREQ_BIAS_ERROR &&
                fabs(clkFreqUncertainty) < TFCS_FREQ_UNCERTAINTY_LIMIT_PPB)
            {
               /* Do soft sync with time and frequency corrections */
               retVal = tfcs_sync(m_tfcsHandle, SYNC_TYPE_SOFT_SYNC, clkTimeError, clkFreqError);
               if (retVal != TFCS_API_SUCCESS)
               {
                  TRACE_PRINTF_LEV(TRACE_WARNING, "ERR: Soft Sync failed...");
                  return;
               }
               /* Got the Sync Report from TFCS */
               m_stateMachine.EventHappened(EventSyncSuccessful);

               /* Stop the callback timer */
               OamUserApplication::GetInstance().StopFreqSyncCallbackTimer();
               m_timerRunning = FALSE;

               m_tfcsSysStateFlag = TFCS_SYS_OUT_OF_SYNC;
               TRACE_PRINTF("TCXO Status: Out of sync\n");
               TRACE_PRINTF("Action: Soft Sync (%f (ppb))\n", clkFreqError);
            }
            else if (fabs(clkFreqUncertainty) > TFCS_FREQ_UNCERTAINTY_LIMIT_PPB)
            {
               TRACE_PRINTF("TCXO Status: Out of sync\n");
               TRACE_PRINTF("Action: None (High uncertainty) \n");
    /* new-changes */
               /* Start the callback timer */
               if(!m_timerRunning)
               {
                  OamUserApplication::GetInstance().StartFreqSyncCallbackTimer(FREQ_SYNC_CALLBACK_TIMEOUT_MS);
                  m_timerRunning = TRUE;
               }

               m_tfcsSysStateFlag = TFCS_SYS_OUT_OF_SYNC;
            }
            else
            {
               TRACE_PRINTF("\nTCXO Status: In Sync\n");
               m_tfcsSysStateFlag = TFCS_SYS_IN_SYNC;
            }

            TRACE_PRINTF("\n*************************************************\n\n");
         }
         break;

         default:
            TRACE_PRINTF("Incorrect state %d in MonitorFreqBiasTFCS()\n", m_tfcsSysStateFlag);
            break;
     }
     return;
}  

/*********************************************
 * Funtion to handle acquire lost scenario 
 *********************************************/
void FreqSyncEntity::HandleAcqLostAndHighUncert(void)
{
    s32    retVal;

    /* Do not sync as acquired cell has been lost */
    retVal = tfcs_sync(m_tfcsHandle, SYNC_TYPE_DO_NOT_SYNC, 0, 0);
    if (retVal != TFCS_API_SUCCESS)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "ERR: Do not Sync TFCS API call failed...");
        return;
    }

    /* new-changes */
    m_retryCnt++;
    if( (m_coscArfcn != 0) && (m_retryCnt < TFCS_MAX_COSC_RETRY) )
    {
       CoscArfcnList list;

       list.arfcn[0] = m_coscArfcn;
       list.numArfcns = 1;

       TRACE_LEV(TRACE_INFO, "FreqSyncEntity:: Retrying COSC on same Arfcn = %hu,", list.arfcn[0]);

       TRACE_PRINTF("FreqSyncEntity:: Send the cosc msg to GSM_REM");

       NlmCoscReq NlmCoscReq(list);
       OamUserApplication::GetInstance().SendMessage(NlmCoscReq, ENTITY_GSM_REM, ENTITY_FREQ_SYNC); 

    }
    else
    {
    /* new-changes */
       /* Do COSC again */
       SendNlmCoscReq();
    }
}

/*********************************************
 * Release the TFCS client
 *********************************************/ 
void FreqSyncEntity::releaseTFCSClient(void)
{ 
    s32 ret = 0;

    if( m_tfcsHandle != TFCS_CLIENT_HANDLE_INVALID )
    {
       ret = tfcs_close(m_tfcsHandle);

       if(ret == TFCS_API_INVALID_HANDLE)
       {
       TRACE_PRINTF_LEV(TRACE_WARNING, "TFCS Initialization failure. Can not sync using GPS or Macro, moving to NTP");
          TRACE_PRINTF_LEV(TRACE_WARNING, "tfcs_close API returned Error: TFCS_API_INVALID_HANDLE. tfcsHandler = %d \n", m_tfcsHandle);
       }
       else
       {
          TRACE_PRINTF_LEV(TRACE_INFO, "tfcs_close API Successful. tfcsHandler = %d \n", m_tfcsHandle);
          m_tfcsHandle = TFCS_CLIENT_HANDLE_INVALID;
       }  
    } 
}

#endif /* QC_TFCS */
 
