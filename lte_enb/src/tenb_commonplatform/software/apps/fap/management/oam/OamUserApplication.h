
///////////////////////////////////////////////////////////////////////////////
//
// OamUserApplication.h
//
// Main application class for OAM app.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OamUserApplication_h_
#define __OamUserApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <algorithm> 
#include <sstream>
#include <mib-core/MibManager.h>
#include <messaging/transport/SingleThreadedAppWithAttrCache.h>
#include <messaging/messages/cphy/CPhyNodeBStatInd.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <mobnet/MobnetTypes.h>
#include <system/Utilities.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#if 0
#include "freq-sync/FreqSyncEntity.h"
#endif
#include "TemperatureMonitor.h"
#include "OamAlarmMgr.h"
#include "OamCli.h" 
#include "KpiManager.h"
#include "Oam_fsm.h"
#include "Oam_fsm_interface.h"
#include "MfManager.h"

#define EQUIVALENT_PLMN_LIMIT 99999
#define NMM_SUPPORTED_RAT_LTE   0x01
#define NMM_SUPPORTED_RAT_WCDMA 0x02
#define NMM_SUPPORTED_RAT_FREQ_SYNC  0x10
#define ONE 1
#define OAM_SET_GERAN_TRESEL_SF_MED  1
#define OAM_SET_GERAN_TRESEL_SF_HIGH 2
#define OAM_SET_GERAN_SPEED_SCALE    3
#define NTP_SERVER1 0
#define NTP_SERVER2 1
#define NTP_SERVER3 2
#define NTP_SERVER4 3
#define NTP_SERVER5 4
#define NTP_STATUS1 "Synchronized"
#define NTP_STATUS2 "UnSynchronized"
#define NTP_STATUS3 "Disabled"
#define INVALID_INSTANCE_NBR -1
static const int oam_ret_zero = 0;
///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
using namespace threeway;

class OamUserApplication : public threeway::SingleThreadedAppWithAttrCache,
                           public OamFsmInterface,
                           public MibSubscriptionNotifyInterface
{
   private:
      // Is singleton so private constructor.
      OamUserApplication();

   public:
      typedef enum
      {
         SUBSCRIPTION_ID_ADMIN_STATE = 0,
         SUBSCRIPTION_ID_RRC_STATE,
         SUBSCRIPTION_ID_LOG_UPLOAD_INTERVAL,
         SUBSCRIPTION_ID_NEW_UARFCN,
         SUBSCRIPTION_ID_FAP_SECURITY,
         SUBSCRIPTION_ID_REQUIRE_FREQ_SYNC,
         SUBSCRIPTION_ID_IUH_CONFIG,
         SUBSCRIPTION_ID_REM_SCAN_NEIGHBOUR_RESET,
         SUBSCRIPTION_ID_MAC_ADDRESS,
         SUBSCRIPTION_ID_OP_STATE,
         SUBSCRIPTION_ID_RAB_STATUS_REPORT,
         SUBSCRIPTION_ID_DL_EARFCN_FOR_REM,
         SUBSCRIPTION_ID_NTP_CFG_PARAMETERS,
         SUBSCRIPTION_ID_DEFAULT_NTP_CFG,
         SUBSCRIPTION_ID_TRACE_FT_PARAMETERS,
         SUBSCRIPTION_ID_IPV6_0,
         SUBSCRIPTION_ID_IPV6_1,
         SUBSCRIPTION_ID_LTE_FREQ = 20,
         SUBSCRIPTION_ID_LTE_CELL = 28 ,
         SUBSCRIPTION_ID_UTRA_FREQ = 44,
         SUBSCRIPTION_ID_UTRA_CELL = 60,
         SUBSCRIPTION_ID_GERAN_FREQ = 76,
         SUBSCRIPTION_ID_GERAN_CELL = 92,
         SUBSCRIPTION_ID_TDS_UTRA_FREQ = 118,
         SUBSCRIPTION_ID_TDS_UTRA_CELL = 134 ,
         SUBSCRIPTION_ID_MAX = 166
      } OamSubscriptionId;


      typedef enum
      {
         SCAN_INDETERMINATE =0,
         SCAN_INPROGRESS,
         SCAN_SUCCESS,
         SCAN_ERROR,
         SCAN_TIMEOUT
      }RemScanStatus;

      typedef enum
      {
         RAT_LTE = 0,
         RAT_WCDMA,
         RAT_GERAN,
         RAT_CDMA,
         MAX_SUPPORTED_RATS
      } RemScannedRAT;


      /**
       * Construction / destruction.
       */
      virtual ~OamUserApplication ();
      static OamUserApplication& GetInstance();

      /** Get the SVN build version string.
      */
      static const char *GetSvnVersion() { return appVer.version; }

      /**
       * Implement MibSubscriptionNotifyInterface.
       */

      virtual void SendSubscriptionNotification(
            u32 subscriberId,
            u32 subscriptionId,
            const MibAttributeValuesByDn & objects);

      virtual void SendSubscriptionDeleteNotification(u32 subscriberId,
            u32 subscriptionId,
            const MibAttributeIdsByDn& deletedAttributeIdsByDn);

      /**
       * Implement SingleThreadedAppWithAttrCache
       */
      virtual std::vector<MessagingEntity> GetSupportedEntities();
      virtual void GetSubscriptions(std::vector<SubscriptionDescriptor>& subscriptions);
      virtual void InitialiseApp();
      virtual void StartApp();

      /**
       * Override base class SendMessage to add tracing.
       */
      virtual bool SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity = ENTITY_INVALID) const;

      //void InitFreqSyncEntity();

      /**
       * Get MibManager, may be null.  Don't hold on to a copy of the returned pointer...
       */
      shared_ptr<MibManager> GetMibManager() { return m_mibManager; }

      /**
       * Get the alarm manager.
       * We're exposing a private member here.  That's OK, it's only a member here
       * rather than a singleton to associate its lifespan with the main application class.
       */
      OamAlarmMgr& GetAlarmMgr() { return m_alarmMgr; }

      /**
       * Get the KPI manager.
       * We're exposing a private member here.  That's OK, it's only a member here
       * rather than a singleton to associate its lifespan with the main application class.
       */
      KpiManager& GetKpiMgr() { RSYS_ASSERT(m_kpiMgr != NULL); return *m_kpiMgr; }

      /**
       * Get the Managed Fings manager.
       * We're exposing a private member here.  That's OK, it's only a member here
       * rather than a singleton to associate its lifespan with the main application class.
       */
      MfManager& GetMfManager() { return m_mfManager; }

      void DnsServerAdd(u32 id, IPv4Address& dnsServer);
      void TftpOpenPinhole(IPAddress& tftpServer);
      void TftpClosePinhole(void);

      /**
       * Implement TriggerPacketManagerInterface.
       */
      void TriggerPacketPinholeOpened(void);
      void TriggerPacketReceived(const IPv4Address& hostIpAddress);
      void StartNtpTimer(u32 timeoutPeriod); 

#if 0
      /**
       * Update the periodic REM timer whenever the parameters change.
       */
      void UpdateRemTimer(u32 perScanInterval, u32 periodicRemScanEnabled, u32 perScanTimeWindowDur, u32 perScanTimeWindowStart, u32 freqSyncSynced);

      /**
       * Start a timer that goes off timeoutPeriod after a Frequency Synchronisation occurs to indicate that the time sychronisation has expired
       */
      void StartFreqSyncExpiryTimer(u32 timeoutPeriod);
      /**
       * Start a timer that tells freq-sync to record its activity (used with warm start)
       */
      void StartFreqSyncActivityNotificationTimer(u32 timeoutPeriod);

      /**
       * Start a timer that tells freq-sync to check if callback is received or not.
       */
      void StartFreqSyncCallbackTimer(u32 timeoutPeriod);
      void StopFreqSyncCallbackTimer();
#endif
      /**
       * Kick off a full REM scan.
       */
      void TriggerFullRemScan();
      void HandleNtpParams(); 
      void HandleNtpCurrentTime();
      /**
       * REM scan is disabled.
       */
      void RemScanDisabled(shared_ptr<threeway::MessageSerialisedData> message);
      /**
       * GetMinMaxValue from the Range
       */
      void GetTimeoutValue(u32 &timeoutvalue);
      /**
       * Frequency sync sub entity.
       */
      //FreqSyncEntity m_freqSyncEntity;
      /**
       * Signal handler initialization.
       */
      void OamInitSignals(void);
      /**
       * Send Request to Rem to start the scan.
       */
      void SendRemScanReq();
      /**
       * Send Request to Rem to abort the scan.
       */
      void SendAbortRemScanReq();

      /**
       * Send Request to Oam to factory reset.
       */
      void SendFactoryResetReq();
      static bool isWatchdogDereg;

      /**
       * Checks if the SON feature related parameters are configured
       * and sets LTE_SON_CONF_PRESENCE accordingly. 
       */
      void checkForSONParameters(const MibAttributeValues&);

      /**
       * Function to retrieve instance number from DN
       */
      char * GetMibObjectInstanceNum(string dn) const;

      /**
       * If PMax for GERAN parameter is updated then flag that this
       * parameter is set by user need to be set internally
       */
      void HandleGERANPmaxParam(string csgParam);

      /**
       * If tReselectionGERANSFMedium & tReselectionGERANSFHigh
       * for GERAN parameter is updated then flag that this
       * parameter is set by user need to be set internally
       */
      void HandleGERANSpeedScaleParam(string tReselParams);

      /**
       * Upadate the array correspoding to the MIO to identify if instance
       * was added, modified or deleted
       */
      void HandleLogUpload();                          
      void StartLogTimer(u32 timer_value);
      void HandleMIOdn(MibDN dn);
      void HandleNetCntrlOrdrParam(string);
      void modifyField(FILE *fptr,std::string fieldName,std::string newValue);
   protected:

      void HandleTimerExpiry(shared_ptr<TimerExpiry> timer);

   private:
      static u32 accFrameCount;
      static u32 accBlockErrorCount[NUM_CPHY_STAT_CHAN_DCH];
      static u32 accBlockCount[NUM_CPHY_STAT_CHAN_DCH];
      static u32 accBitErrors;
      static u32 accBitCount;
      static bool countErrors;
      string logFileName;
      string logFileDir;
      // Singleton
      static shared_ptr<OamUserApplication> s_instance;

      void StartIu();
      void StopIu();
      void SendRequestStartRsp(MessagingEntity entity);

      /**
       * Implement OAM FSM.
       */
      OamInterfaceDefinition();
      void HandleOamMessage(shared_ptr<threeway::MessageSerialisedData> message);
      void HandleOpStateInformMessage(shared_ptr<threeway::MessageSerialisedData> message);
      void HandleMibMessage(shared_ptr<threeway::MessageSerialisedData> message);

      /**
       * Handle an OAM_ACTION_REQ message.
       */
      void HandleOamActionReq(shared_ptr<MessageSerialisedData> message);

      /**
       * Send the CphyHwConfigReq to L1
       */
      void SendCPhyHwConfigReq();

      /**
       * Fill in the details of a RemScanReq and send it.
       */

      void ProcessEntityReadyStatesAndFireEmUpIfAllStarted();
      void StartTr069();
      void UpdateReadyFlag(bool& flag);
      void InjectOpStateIntoFsm();

      void FillNeighborlistInfo();

      // Implement MessageHandler interface
      virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

      /**
       * Read software release from file and apply to MIB.
       */
      void SetSoftwareReleaseAndBuildDesc() const;

      /**
       * Read hardware type/revision to determine our frequency band.
       * Set band in D/L UARFCN validator.
       * Check current DL_UARFCN value - if none or invalid then set to default.
       */
      void SetFrequencyBandAndCheckDlUArfcn() const;
      string GetStatusAsString(int status);
      void SetLogDirPath(string path);
      void SetAppLogFileName(string name);
      string GetAppLogFileName(){ return logFileName; }
      string GetLogDirPath(){ return logFileDir; }

      /**
       * Update LEDs based on op states.
       */

      // a load of flags to decouple app startup from the main state machine.
      bool m_l1l2Started;
      bool m_iuReady;
      bool m_oamReady;
      bool m_swUpdateReady;
      bool m_tr069Ready;
      bool m_rrcReady;
      bool m_rrmReady;
      bool m_cphyReady; // note this is l1rem
      bool m_psUserPlaneReady;
      bool m_csUserPlaneReady;
      bool m_ggsnReady;
      bool m_tenpinReady;
      bool m_sapiReady;
      bool m_smReady;
      u32 speedScaleCount;

      // temporary workaround for FAP_SECURITY until mib subscription informs us with a reason
      bool m_fapSecurityInitialised;

      /**
       * MIB
       */
      boost::shared_ptr<MibManager> m_mibManager;


      /**
       * KPI manager.
       */
      shared_ptr<KpiManager> m_kpiMgr;

      /**
       * Trigger packet manager plus related vars.
       */
      TimerHandle m_triggerPacketTimerHandle;
      TimerHandle m_ateIpSecTimerHandle;
      threeway::TimerHandle m_watchdogKickTimer;
      IPv4Address m_ateHostIpAddress;

      /**
       * Temperature monitor and associated timer.
       */
      TemperatureMonitor m_tempMonitor;
      TimerHandle m_tempReadingTimerHandle;
      TimerHandle m_freqSyncExpiredTimerHandle;
      TimerHandle m_freqSyncActivityNotificationTimerHandle;
      /* Timer for waiting for TFCS callback */
      TimerHandle m_freqSyncCallbackTimerHandle;
      TimerHandle m_ntpTimerHandle; 

      /**
       * Alarm manager.  Collates all alarm events raised on the FAP.
       */
      OamAlarmMgr m_alarmMgr;

      bool m_stuckAlarmCleared;

      threeway::TimerHandle m_periodicRescanTimer;

      std::vector<MessagingEntity> m_otherEntitiesToStart;

      // Below is commented for ccpu integration
      //FirewallHandles m_handles;

      // Some specials builds need to send a heartbeat.
      // Keep track of MFs that have sent op state inform inds.
      // Can use this info in FSMs and CLI commands.
      MfManager m_mfManager;

      // LED Management

      /**
       * OAM State Machine.
       * Put this last in case initial state uses other member data.
       */
      OamFsm m_fsm;
      OamCli m_OamCli;
    TimerHandle m_logTimerHandle;
};

#endif
