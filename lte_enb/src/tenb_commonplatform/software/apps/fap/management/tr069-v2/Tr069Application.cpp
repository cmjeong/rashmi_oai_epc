///////////////////////////////////////////////////////////////////////////////
//
// Tr069Application.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <signal.h>
#include <system/pthread_utils.h>
#include <system/Trace.h>
#include <system/TimerEngine.h>
#include <system/AlarmEvent.h>
#include <system/KpiGroup.h>
#include <system/SoftwareRelease.h>
#include <system/FapHardwareConfig.h>
#include <system/SerialisationIds.h>
#include <system/WatchDogDereg.h>
#include <mobnet/RemScanStatusId.h>
#include <mobnet/PlmnId.h>
#include <platform/FapAlarmId.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/common/KpiConfigureReq.h>
#include <messaging/messages/common/KpiCollectionReq.h>
#include <messaging/messages/common/KpiReadCnf.h>
#include <messaging/messages/common/RemScanReq.h>
#include <messaging/messages/common/AutonomousTransferComp.h>
#include <messaging/messages/common/UploadLogReq.h>
#ifdef LTE_REM
#include <messaging/messages/rem/rem_msgs.h>
#endif
#include <nanohttp/nanohttp-socket.h>
#include <nanohttp/nanohttp-client.h>
#include <nanohttp/nanohttp-logging.h>
#include <libcsoap/soap-client.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069Events.h"
#include "Tr069FgwQuery.h"
#include "Tr069Md5.hpp"
#include "Tr069Cli.h"
#include "Tr069AlarmManager.h"
#include "Tr069SetParameterValueManager.h"
#include "Tr069ParameterValueChangeNotificationManager.h"
#include "Tr069MultiInstanceMibObjectManager.h"
#include "Tr069DataModelManager.h"
#include "Tr069AddObjectManager.h"
#include "Tr069DeleteObjectManager.h"
#include "NsnPerformanceMeasurement.h"
#include "MibHelper.h"
#include <fstream>
#include "Tr069UdpServer.h"

using namespace std;
using namespace threeway;
using namespace tr069;

bool Tr069Application::isWatchdogDereg =false;
string Tr069Application::authMethod = "PKI";
static int stunSockFd;
StunAddress4 StunServerAddr;
///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

Tr069Application* Tr069Application::s_instance = NULL;
#define MAX_DIR_LEN 50

DeclareAppVersionStamp

static int my_argc;
static char** my_argv;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Tr069Application::Tr069Application() :
    ApplicationWithParamCache("tr069"),
    m_StartMsgReceived(false),
    m_notifyReadyGuardTimer(0),
    m_startDelayTimer(0),
    m_cliCommands(*this),
    m_perodicUploadInterval(0),
    m_collectionPeriodInSecs(0),
    m_perodicUploadPhaseAllignInMin(0),
    m_currentPmFilenameIdx(0),
    m_max_pmFiles(MAX_PM_FILES)
{
    ENTER();

    RegisterMessageHandler(this, "Tr069");

    EXIT();
}

Tr069Application::~Tr069Application()
{
   ENTER ();

   EXIT ();
}

Tr069Application& Tr069Application::GetInstance()
{
   ENTER ();

   if (s_instance == NULL)
   {
      s_instance = new Tr069Application();

      RSYS_ASSERT(s_instance);
   }

   RETURN (*s_instance);
}

void Tr069SignalSigtermHandler(int sig)
{
   Tr069Application::isWatchdogDereg = true;
   DeregisterWithWatchDog(ENTITY_TR069, ENTITY_WATCHDOG);
   exit(0);
}

u32 Tr069Application::ThreadProcedure()
{
   ENTER();

   TRACE_PRINTF("TR069Application::ThreadProcedure()\n");

   signal(SIGTERM,Tr069SignalSigtermHandler);
   m_cliCommands.Register();

   StartTimerEngine();
   StartMessaging();
   StartAttributeCache();

   RegisterEntity(ENTITY_TR069);
   string val = getConfigParam("OAM_CONFIG_FILES_DIR", "");
   string nvStorePath = val.c_str();
   nvStorePath = nvStorePath + "/config/";
   nvStorePath = nvStorePath + "param-attribute.nv"; 
   m_paramAttNvStore.reset(new Tr069ParamAttributeNvStore());
   m_paramAttNvStore->SetParamAttStoreFileName(nvStorePath);
   m_paramAttNvStore->InitialiseParamAttributeNvStore();

   SubscribeToMibParams();

   m_alarmManager.reset( new AlarmManager(GetMibCache(), *this) );
   m_alarmManager->Start();

   Filename paramAttrFilename( GetNvLogDirectory(), GetName(), ".paramAttr");
   m_parameterAttributeManager.reset( new ParameterAttributeManager(paramAttrFilename.c_str()));

   //GenerateHwVersionString();
   GenerateSwVersionString();
   //GenerateFapTr069ServerUrl();
   InitialisePMParms();

   NotifyReady(ENTITY_OAM, ENTITY_TR069, false);
   m_notifyReadyGuardTimer = CreateTimer("notifyReadyGuardTimer", 10000 );

   while(1)
   {
      shared_ptr<Queueable> event = ReceiveEvent( TimerEngineInterface::HoursToTicks(1) );
      DispatchEvent(event);
   }

   RETURN(0);
}

typedef enum Tr069Subscriptions_eTag
{
   SubsPerfMgmt,
   SubsVendor,
   SubsHMS,
   SubsCrypto,
   SubsWcdma,
   SubsStunEnable,
   SubsLogUpload,
   SubsTr69ConnReq,
   SubsPeriodicInform,
   SubsFapLteAdminState,
   SubsRemScanStatus,
   SubsPm,
   SubsFapLte,
   SubsFapParameters,
   SubsIpInterface
} Tr069Subscriptions_e;

/*
 * Each line starts with a Class, and then lists a variable number of
 * attributes, terminated by PARAM_ID_INVALID.
 * The line is converted in to a Mibubscription.
 */

static const u16 mibParamsSubsciptions[] =
{
   SubsVendor, MIB_OBJECT_CLASS_COMMISSIONING, PARAM_ID_GATEWAY_VENDOR, PARAM_ID_INVALID,

   // Normal stuff...
   SubsFapParameters,  MIB_OBJECT_CLASS_FAP, 
   PARAM_ID_PM_MAX_INSTANCES,
   PARAM_ID_IP_FIREWALL_ENABLE,    
   PARAM_ID_ENABLE_TR069,
   PARAM_ID_ALARM_SUPPORTED_ENTRIES,
   PARAM_ID_LTE_MAX_PM_FILES,
   PARAM_ID_TLS_CERT_PATH,
   PARAM_ID_TLS_CERT_CA,
   PARAM_ID_TLS_KEY_PATH,
   PARAM_ID_HMS_BOOTSTRAP_COMPLETED,
   PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE,
   PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE,
   PARAM_ID_LTE_REBOOT_STATUS,
   PARAM_ID_LOCAL_TIMEZONE_OFFSET_TO_GMT,
   PARAM_ID_LTE_COMMAND_KEY,
   PARAM_ID_LTE_TR069_CONN_WITH_URL_IN_USE,
   PARAM_ID_IU_CORE_NET_ADDRESS,
   PARAM_ID_ENB_IP_ADDR_IPV4,
   PARAM_ID_ENB_IP_ADDR_IPV6,
   PARAM_ID_IKE_SEND_INTERMEDIATE_CERTS,
   PARAM_ID_IKE_SA_LIFETIME,
   PARAM_ID_IKE_DPD_TRIES,
   PARAM_ID_IPSEC_NAT_T_PORT,
   PARAM_ID_IPSEC_ENCRYPTION_3DES_ENABLE,
   PARAM_ID_IPSEC_ENCRYPTION_AES_ENABLE,
   PARAM_ID_IPSEC_ENCRYPTION_AES128_ENABLE,
   PARAM_ID_IPSEC_ENCRYPTION_NULL_ENABLE,
   PARAM_ID_IPSEC_SA_LIFETIME,
   PARAM_ID_IUH_ENABLE,
   PARAM_ID_IU_SCTP_LOCAL_PORT,
   PARAM_ID_IU_SCTP_REMOTE_PORT,
   PARAM_ID_IU_CORE_NET_CS_POINT_CODE,
   PARAM_ID_IU_CORE_NET_PS_POINT_CODE,
   PARAM_ID_IU_STATIC_CN_IP_ADDRESS,
   PARAM_ID_STATIC_IP_CONFIG_NET_MASK,
   PARAM_ID_STATIC_IP_CONFIG_GATEWAY,
   PARAM_ID_STATIC_IP_CONFIG_IP_ADDRESS,
   PARAM_ID_SERVING_SECGW,
   PARAM_ID_MANAGEMENT_SERVER_IN_USE,
   PARAM_ID_SERVING_FGW_OAM_INNER_IP_ADDRESS,
   PARAM_ID_TR069_ACTION_RECONNECT,
   PARAM_ID_SCTP_LOCAL_PORT_1ST,
   PARAM_ID_SCTP_LOCAL_PORT_2ND,
   PARAM_ID_SCTP_REMOTE_PORT_1ST,
   PARAM_ID_SCTP_REMOTE_PORT_2ND,
   PARAM_ID_RPC_REBOOT_OFF_COUNT,
   PARAM_ID_RPC_REBOOT_ON_COUNT,
   PARAM_ID_RPC_REBOOT_COMMAND_KEY,
   PARAM_ID_RPC_SW_LOAD_DOWNLOAD,
   PARAM_ID_RPC_SW_LOAD_DOWNLOAD_COMMAND_KEY,
   PARAM_ID_RPC_SW_LOAD_DOWNLOAD_START_TIME,
   PARAM_ID_RPC_SW_LOAD_DOWNLOAD_COMPLETE_TIME,
   PARAM_ID_TR069_CONFIG_PLAN_MD5_CHECKSUM,
   PARAM_ID_DEVICESUMMARY,
   PARAM_ID_SPECVERSION,
   PARAM_ID_PROVISIONINGCODE,
   PARAM_ID_TR069_RECONNECT_SECGW_ENABLE,
   PARAM_ID_QOS_ENABLE,
   PARAM_ID_REQUIRE_FREQ_SYNC,
   PARAM_ID_FAP_ALARM_ID,
   PARAM_ID_ALARM_CHANGED_TIME,
   PARAM_ID_NEIGHBORLIST_CONFIG,
   PARAM_ID_GPS_SYNC_ENABLE,
   PARAM_ID_MACRO_SYNC_ENABLE,
   PARAM_ID_FNTP_SYNC_ENABLE,
   PARAM_ID_GSM_SCAN_TIMEOUT,
   PARAM_ID_RAB_STATUS_REQUEST,
   PARAM_ID_RAB_STATUS_REPORT,
   PARAM_ID_LTE_SOFTWARE_VERSION,
   PARAM_ID_LTE_SOAP_SESS_TIMEOUT,
   PARAM_ID_LTE_SOAP_SESS_TIMEOUT_ENABLE,
   PARAM_ID_REM_SCAN_ENABLE,
   PARAM_ID_LTE_REM_SCANNED_CSG_INDICATOR,
   PARAM_ID_LTE_REM_SCANNED_CSG_ID,
   PARAM_ID_DEFAULT_NTP_SERVER,
   PARAM_ID_X_RADISYS_NTP_SYNC_INTERVAL,
   PARAM_ID_DL_UARFCN,
   PARAM_ID_SW_UPDATE_PACKAGE_NAME_A,
   PARAM_ID_SW_UPDATE_PACKAGE_NAME_B,
   PARAM_ID_SW_PACKAGE_ACTIVE,
   PARAM_ID_SW_PACKAGE_SELECTED,
   PARAM_ID_FAP_ID,
   PARAM_ID_UNIT_IP_ADDRESS,
   PARAM_ID_UNIT_IP_NET_MASK,
   PARAM_ID_UNIT_IP_GATEWAY,
   PARAM_ID_WCDMA_FREQ_SYNC_PSC,
   PARAM_ID_WCDMA_FREQ_SYNC_UARFCN,
   PARAM_ID_WCDMA_FREQ_SYNC_ENABLE,
   PARAM_ID_TRACE_FT_SERVER_NAME,
   PARAM_ID_TRACE_FT_USER_NAME,
   PARAM_ID_TRACE_FT_PASSWORD,
   PARAM_ID_TRACE_FT_METHOD,
   PARAM_ID_TRACE_FT_REMOTE_LOCATION,
   PARAM_ID_LTE_DOWNLOAD_START_TIME,
   PARAM_ID_LTE_ENBLOG_MASK,
   PARAM_ID_LTE_ENBLOG_REMOTE_LOGGING,
   PARAM_ID_LTE_FACTORY_RESET_ON_TR069_CONN_FAIL,
   PARAM_ID_LTE_IN_SERVICE_HANDLING,
   PARAM_ID_LTE_MESSENGER_CONFIG_COMPLETE,
   PARAM_ID_REM_SCAN_RESULT,
   PARAM_ID_KPI_REPORT_DURATION,
#ifdef TIP_OAM
   PARAM_ID_GTPU_ECHO_INTERVAL,
#endif
   PARAM_ID_INVALID,

   SubsFapLte,      MIB_OBJECT_CLASS_FAP_LTE,
   PARAM_ID_LTE_OAM_Q_OFFSET_RANGE,
   PARAM_ID_LTE_CDMA2K_CELL_BAND_CLASS,
   PARAM_ID_LTE_CDMA2K_ARFCN,
   PARAM_ID_LTE_CDMA2K_BAND_PN_OFFSET,
   PARAM_ID_LTE_CDMA2K_CELL_TYPE,
   PARAM_ID_LTE_CDMA2K_CID_CDMA2K,
   PARAM_ID_LTE_CDMA2K_MAX_CDMA1X_NEIGH_CELL_ENTRIES,
   PARAM_ID_LTE_GERAN_FREQ_SRC,
   PARAM_ID_LTE_GERAN_CELL_SRC,
   PARAM_ID_LTE_TDS_CDMA_FREQ_SRC,
   PARAM_ID_LTE_TDS_CDMA_CELL_SRC,
   PARAM_ID_LTE_CELL_PLMN_SRC,
   PARAM_ID_LTE_UMTS_NEIGHBOUR_LIST_SRC,
   PARAM_ID_LTE_TM_AUTO_CONFIG,
   PARAM_ID_LTE_FREQ_SYNC_PCI,
   PARAM_ID_LTE_FREQ_SYNC_EARFCN,
   PARAM_ID_LTE_FREQ_SYNC_ENABLE,
   PARAM_ID_LTE_CONFIG_INDEX,
   PARAM_ID_LTE_ZERO_CORRELATION_ZONE_CFG,
   PARAM_ID_LTE_FREQ_OFFSET,
   PARAM_ID_LTE_PRD_REPORT_AMOUNT,
   PARAM_ID_LTE_REM_NUM_EARFCN,
   PARAM_ID_LTE_REM_RSSI,
   PARAM_ID_LTE_REM_EARFCNDL,
   PARAM_ID_LTE_SON_CONF_PRESENCE,
   PARAM_ID_LTE_IN_USE_MAX_LTE_CELL,
   PARAM_ID_LTE_NUM_EUTRA_NEIGH_CELLS_IN_USE_ENTRIES,
   PARAM_ID_LTE_NUM_EUTRA_NEIGH_CELLS_ENTRIES,
   PARAM_ID_LTE_UMTS_NUMBER_OF_ENTRIES,
   PARAM_ID_LTE_RNCID,
   PARAM_ID_LTE_CID_IRAT,
   PARAM_ID_LTE_LAC,
   PARAM_ID_LTE_RAC,
   PARAM_ID_LTE_URA,
   PARAM_ID_LTE_UARFCNUL,
   PARAM_ID_LTE_UARFCNDL,
   PARAM_ID_LTE_PCPICH_SCRAMBLING_CODE,
   PARAM_ID_LTE_RSRP,
   PARAM_ID_LTE_RSRQ,
   PARAM_ID_LTE_RSSI,
   PARAM_ID_LTE_NEIGH_IN_USE_CSG_INDICATOR,
   PARAM_ID_LTE_NEIGH_IN_USE_CSG_ID,
   PARAM_ID_LTE_NEIGH_IN_USE_CSG_ACCESS_MODE,
   PARAM_ID_LTE_CARRIER_ARFCNDL,
   PARAM_ID_LTE_CARRIER_WIDTH,
   PARAM_ID_LTE_CARRIER_RSSI,
   PARAM_ID_LTE_T_RESELECTION_EUTRA,
   PARAM_ID_LTE_THRESH_XLOW,
   PARAM_ID_LTE_THRESH_XHIGH,
   PARAM_ID_LTE_UTRA_FREQ_NEIGH_SRC,
   PARAM_ID_LTE_ENABLE_IRAT,
   PARAM_ID_LTE_UTRA_CARRIER_ARFCN,
   PARAM_ID_LTE_Q_RX_LEV_MIN_IRAT,
   PARAM_ID_LTE_Q_QUAL_MIN_IRAT,
   PARAM_ID_LTE_CELL_RESELECT_PRIORITY_IRAT,
   PARAM_ID_LTE_THRESH_XHIGH_IRAT,
   PARAM_ID_LTE_THRESH_XLOW_IRAT,
   PARAM_ID_LTE_PMAX_UTRA,
   PARAM_ID_LTE_ANR_TRICE_PERIOD,
   PARAM_ID_LTE_ANR_CELL_VALID_AGE,
   PARAM_ID_LTE_ANR_DRX_ON_DURATION_TMR,
   PARAM_ID_LTE_PCI_RANGE2_OFFSET,
   PARAM_ID_LTE_X2SIG_LINK_PORT,
   PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC,
   PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MODATA,
   PARAM_ID_LTE_TDD_MAX_SFCONFIG_LIST_ENTRIES,
   PARAM_ID_LTE_TDD_SFCONFIG_LIST_NUMBER_OF_ENTRIES,
   PARAM_ID_LTE_TDD_SYNC_STRATUM_ID,
   PARAM_ID_LTE_OAM_NEIGHBOUR_DL_BANDWIDTH_SIB3,
#ifdef TIP_OAM
   PARAM_ID_LTE_A3_OFFSET,
#endif
   PARAM_ID_INVALID,

   SubsHMS,           MIB_OBJECT_CLASS_FAP,
   PARAM_ID_MANAGEMENT_SERVER,
   PARAM_ID_MANAGEMENT_SERVER_IN_USE,
   PARAM_ID_MANAGEMENT_USERNAME,
   PARAM_ID_MANAGEMENT_PASSWORD,
   PARAM_ID_INVALID,

   SubsPm,            MIB_OBJECT_CLASS_FAP, 
   PARAM_ID_PM_COMMON_COLLECTION_PERIOD, 
   PARAM_ID_PM_ENABLE_FILE_COMPRESS,
   PARAM_ID_PM_COMPRESSION_METHOD,
   PARAM_ID_PM_CONFIG_NUMBER_OF_ENTRIES,
   PARAM_ID_INVALID,

   SubsRemScanStatus, MIB_OBJECT_CLASS_REM_LTE,
   PARAM_ID_LTE_REM_SCAN_STATUS,
   PARAM_ID_INVALID,

   SubsFapLteAdminState, MIB_OBJECT_CLASS_FAP,
   PARAM_ID_LTE_FAP_ADMIN_STATE, 
   PARAM_ID_INVALID,

   SubsPeriodicInform,      MIB_OBJECT_CLASS_FAP, 
   PARAM_ID_PERIODIC_INFORM_ENABLED,
   PARAM_ID_PERIODIC_INFORM_INTERVAL,
   PARAM_ID_INVALID,

   SubsTr69ConnReq, MIB_OBJECT_CLASS_FAP,
   PARAM_ID_TR069_CONNECTION_REQUEST_USERNAME,
   PARAM_ID_TR069_CONNECTION_REQUEST_PASSWORD,
   PARAM_ID_INVALID,

   SubsLogUpload,       MIB_OBJECT_CLASS_FAP, 
   PARAM_ID_LOG_UPLOAD_INTERVAL,
   PARAM_ID_INVALID,

   SubsStunEnable,      MIB_OBJECT_CLASS_FAP, 
   PARAM_ID_STUN_ENABLE,
   PARAM_ID_INVALID,

   SubsWcdma, MIB_OBJECT_CLASS_REM_UMTS_WCDMA,
   PARAM_ID_WCDMA_REM_SCAN_STATUS,
   PARAM_ID_INVALID,

   SubsCrypto, MIB_OBJECT_CLASS_CRYPTO_PROFILES,
   PARAM_ID_CRYPTO_PROFILE_ENABLED,
   PARAM_ID_CRYPTO_PATH,
   PARAM_ID_INVALID,

   SubsPerfMgmt, MIB_OBJECT_CLASS_PERF_MGMT,
   PARAM_ID_PM_UPLOAD_ENABLE,
   PARAM_ID_PM_URL,
   PARAM_ID_PM_USERNAME,
   PARAM_ID_PM_PASSWORD,
   PARAM_ID_PM_PERIODIC_UPLOAD_INTERVAL,
   PARAM_ID_PM_PERIODIC_UPLOAD_TIME,
   PARAM_ID_INVALID,

   SubsIpInterface, MIB_OBJECT_CLASS_IP_INTERFACE,
   PARAM_ID_IP_MAX_IPV6_ENTRIES,
   PARAM_ID_INVALID,
};

void Tr069Application::SubscribeToMibParams(void)
{
   enum { Subs, Class, Params } state = Subs;

   u32 subsId = 0;
   MibObjectClass moClass = MIB_OBJECT_CLASS_INVALID;
   MibAttributeIds subscription;
   u16 numCell = 1;
   string numCellStr = getConfigParam("OAM_NUM_CELL_ENTRIES", "");
   if(NULL != numCellStr.c_str())
   {
      numCell = (u16)atoi(numCellStr.c_str());
   }

   for( size_t s = 0; s <  sizeof(mibParamsSubsciptions)/sizeof(mibParamsSubsciptions[0]); s++)
   {
      u16 v = mibParamsSubsciptions[s];

      switch (state)
      {
         case Subs:
            subsId = u32(v);
            state = Class;
            break;

         case Class:
            moClass = MibObjectClass(v);
            state = Params;
            break;

         case Params:
            MibAttributeId attribute = MibAttributeId(mibParamsSubsciptions[s]);

            if(PARAM_ID_INVALID != attribute)
            {
               subscription.insert(attribute);
            }
            else
            {
               if(moClass == MIB_OBJECT_CLASS_FAP_LTE)
               {
                  for(u16 cellIdx = 0; cellIdx < numCell; cellIdx++)
                  {
                     GetMibCache().SubscribeMibAttributes(subsId, ENTITY_TR069, MibDN::GenerateMibDN(moClass,cellIdx), subscription, true);
                  }
                  subscription.clear();
                  state = Subs;
               }
               else
               {
                  GetMibCache().SubscribeMibAttributes(subsId, ENTITY_TR069, MibDN::GenerateMibDN(moClass), subscription, true);
                  subscription.clear();
                  state = Subs;
               }

            }
      }
   }

   RSYS_ASSERT(state == Subs);

   MibAttributeIdsByDn dataModelAttributesByDn;
   DataModelManager::GetInstance().AddMibAttributesForDataModelParameters(dataModelAttributesByDn);
   MibAttributeIdsByDn::iterator dnIter = dataModelAttributesByDn.begin();
   while(dnIter != dataModelAttributesByDn.end())
   {
      MibDN dn = dnIter->first;
      subscription.clear();
      subscription = dnIter->second;
      GetMibCache().SubscribeMibAttributes( ++subsId, ENTITY_TR069, dn, subscription, true);
      dnIter++; 
   }
   // Object subscriptions
   MultiInstanceMibObjectManager::GetInstance().PerformMibSubscriptions(subsId);
}

void Tr069Application::ImportCommissioningAttributes(void)
{
   MibAttributeValues attrs;

   MibAttributeId url = { PARAM_ID_MANAGEMENT_SERVER };

   bool serverUrlPresent = GetMibCache().IsMibAttributePresent( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), url);
   bool serverUrlNullValue = true;

   if(serverUrlPresent)
   {
      Url serverUrl;
      GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), url, serverUrl);

      TRACE_PRINTF("Fap.0.%s=%s", MibAttributeIdToString(url), serverUrl.Get().c_str() );

      serverUrlNullValue = serverUrl.IsNull();
   }

   if( !serverUrlPresent || serverUrlNullValue )
   {
      TRACE_PRINTF("Copying COMMISSIONING.0.%s server URLs to FAP.0",  MibAttributeIdToString(url));

      if( GetMibCache().IsMibAttributePresent( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), url) )
      {
         Url serverUrl;
         GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), url, serverUrl);
         attrs.AddAttribute(url, serverUrl.Get() );
      }
   }

   if( attrs.GetAttributeCount() > 0 )
   {
      GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);
   }

   /**
    * If not present, initial SecGw
    */
   if( !Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(PARAM_ID_SERVING_SECGW) )
   {
      MibAttributeValues attrs;
      attrs.AddAttribute( PARAM_ID_SERVING_SECGW, 1);
      Tr069Application::GetInstance().GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);
   }
}

void Tr069Application::HandleOtherEvent(shared_ptr<Queueable> otherEvent)
{
   shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(otherEvent);

   if (tr069Event)
   {
      switch( tr069Event->GetDst() )
      {
         case Tr069QueueableEvent::SECGW_CONNECTION_FSM:
         case Tr069QueueableEvent::CWMP_CONNECTION_FSM:
         case Tr069QueueableEvent::SPV_FSM:
         case Tr069QueueableEvent::ADD_OBJECT_FSM:
         case Tr069QueueableEvent::DELETE_OBJECT_FSM:
         case Tr069QueueableEvent::SOCKET_INTERFACE_FSM:
         case Tr069QueueableEvent::TRANSACTION_SESSION_FSM:
            Tr069ServerConnection::GetInstance().HandleEvent(tr069Event);
            break;

         case Tr069QueueableEvent::FILE_TRANSFER_FSM:
            {
               Tr069FileTransfer::GetInstance().HandleEvent(tr069Event);
            }
            break;

         case Tr069QueueableEvent::REBOOT_FSM:
            Tr069Reboot::GetInstance().HandleEvent(tr069Event);
            break;

         case Tr069QueueableEvent::ANONYMOUS:
         case Tr069QueueableEvent::TR069_APPLICATION:
            TRACE_PRINTF("ReceiveEvent(unhandled) %s.\n", tr069Event->ToString() );
            break;
      }
   }
}

void Tr069Application::UpdatePMParams(u32 inst)
{
   ENTER ();

   MibAccessInterface& m_mib = Tr069Application::GetInstance().GetMibCache();

   MibDN dnObj = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_PERF_MGMT, inst);

   TRACE_PRINTF("Mibdn generated: %s", dnObj.ToString().c_str());

   if(m_mib.IsMibObjectPresent(dnObj))
   {

      m_mib.GetMibAttribute(dnObj, PARAM_ID_PM_UPLOAD_ENABLE, m_perodicUploadEnable);

      if(m_perodicUploadEnable)
      {
         TimeWrap perodicUploadPhaseAllign;
         TimeStructure tm;

         m_mib.GetMibAttribute(dnObj, PARAM_ID_PM_PERIODIC_UPLOAD_TIME, perodicUploadPhaseAllign);
         tm = perodicUploadPhaseAllign.GetTimeStructure();
         m_perodicUploadPhaseAllignInMin = tm.theMinutes + tm.theHour * 60;

         m_mib.GetMibAttribute(dnObj, PARAM_ID_PM_USERNAME, m_UserName);
         m_mib.GetMibAttribute(dnObj, PARAM_ID_PM_PASSWORD, m_Passwd);
         m_mib.GetMibAttribute(dnObj, PARAM_ID_PM_PERIODIC_UPLOAD_INTERVAL, m_perodicUploadInterval);
         m_mib.GetMibAttribute(PARAM_ID_PM_ENABLE_FILE_COMPRESS, m_enableFileCompress);
         m_mib.GetMibAttribute(PARAM_ID_PM_COMPRESSION_METHOD, m_compressMethod);
         m_mib.GetMibAttribute(PARAM_ID_LTE_MAX_PM_FILES, m_max_pmFiles);
      }
   }

   EXIT();
}

void Tr069Application::InitialisePMParms()
{
   ENTER ();

   u32 inst = 0;
   u32 collectionPeriod;
   m_perodicUploadInterval = DFLT_UPLOAD_INTERVAL;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_MAX_PM_FILES, m_max_pmFiles);
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_PM_COMMON_COLLECTION_PERIOD, collectionPeriod);
   TRACE_PRINTF("\n %s Common collection value set %d",__FUNCTION__,collectionPeriod);
   if (collectionPeriod == 0)
   {
      m_collectionPeriodInSecs = m_perodicUploadInterval;
   }
   else
   {
      m_collectionPeriodInSecs = collectionPeriod;
   }

   for(inst = 0; inst < MAX_PERF_MGMT_ENTRY; inst++)
   {
      UpdatePMParams(inst);
   }

   EXIT ();
}

void Tr069Application::HandleTimerExpiry(shared_ptr<TimerExpiry> expiredTimer)
{
   ENTER();
   static int ipAddAvbl = 0;

   if (expiredTimer->GetTimerHandle() == m_watchdogKickTimer)
   {
      if(Tr069Application::isWatchdogDereg == false)
      {
         WatchdogKick (getpid(),5,15);
      }
   }
   else if(expiredTimer->GetTimerHandle() == m_logTimerHandle)
   {
      string logFileName[3];
      int numClosedFiles = Trace::GetInstance().GetLogFilesToUpload(logFileName);
      for(int n_uploadfile = 0;n_uploadfile < numClosedFiles;n_uploadfile++)
      {
         UploadLogReq upLogReq(logFileName[n_uploadfile]);
         SendMessage(upLogReq,ENTITY_FTP,ENTITY_TR069);
      }
      HandleLogUpload();
   }
   else if(expiredTimer->GetTimerHandle() == m_stunTimerHandle)
   {
      SendBindingRequest(stunSockFd,StunServerAddr);
   }
   if(expiredTimer->GetTimerHandle() == m_notifyReadyGuardTimer)
   {
      if(!m_StartMsgReceived)
      {
         NotifyReady(ENTITY_OAM, ENTITY_TR069, false);
         m_notifyReadyGuardTimer = CreateTimer("notifyReadyGuardTimer", 10000 );
      }
   }
   else if(expiredTimer->GetTimerHandle() == m_startDelayTimer)
   {
      string val;

      val = getConfigParam("OAM_ETHERNET_INTERFACE", "");
      IPv4Address addr, mask;
      char * pethinterface=NULL;
      pethinterface = (char *)val.c_str();
      GetIPV6Address(); 
      if(!GetIPAddress(pethinterface, addr, mask))
      {
         u32 startDelay = TimerEngine::MillisecondsToTicks(300);
         m_startDelayTimer = CreateTimer("StartDelayTimer", startDelay );
      }
      else
      {
         ipAddAvbl++;
         TRACE_PRINTF(" Found IP Address from Interface, ipAddAvbl is %d",ipAddAvbl);
         //Start the same timer for additional grace period for the routing also to be established
         if (ipAddAvbl == ONE)
         {
            // Start timer for 10 seconds
            TRACE_PRINTF("Starting timer for 10 seconds for route to be established");
            u32 startDelay = TimerEngine::MillisecondsToTicks(10000);
            m_startDelayTimer = CreateTimer("StartDelayTimer", startDelay );
            // Let us set the IP interface attributes here
            {
               MibDN ipDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE);
               MibAttributeValues attrs;
               attrs.AddAttribute(PARAM_ID_IP_INTERFACE_NAME, pethinterface);
               attrs.AddAttribute(PARAM_ID_IP_INTERFACE_ENABLED, (u32)1);
               attrs.AddAttribute(PARAM_ID_IP_INTERFACE_STATUS, "Up");
               attrs.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ENABLED, (u32)1);
               Tr069Application::GetInstance().GetMibCache().SetMibAttributes(ipDn, attrs, ENTITY_TR069);

               //Update the DN to point to first instnace of IPv4 address
               MibDN ipv4Dn = MibDN::GenerateMibDN(ipDn, MIB_OBJECT_CLASS_IP_INTERFACE_IPV4_ADDRESS);
               MibAttributeValues ipAddressAttrs;
               ipAddressAttrs.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS, addr.ToString());
               ipAddressAttrs.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_SUBNET_MASK, mask.ToString());
               ipAddressAttrs.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS_ENABLED, (u32)1);
               ipAddressAttrs.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS_STATUS, "Enabled");
               Tr069Application::GetInstance().GetMibCache().SetMibAttributes(ipv4Dn, ipAddressAttrs, ENTITY_TR069);
            }
         }
         else
         {
            Tr069ServerConnection::GetInstance().StartFsm();
            m_startDelayTimer = 0;
            HandleLogUpload();
         }
      }
   }
   else
   {
      bool timerTriggeredDelayedProcedure = timerDelayedProcedures.Trigger(expiredTimer->GetTimerHandle());

      if( !timerTriggeredDelayedProcedure )
      {
         if( Tr069ServerConnection::GetInstance().HandleTimerExpiry(expiredTimer->GetTimerHandle()) ||
               Tr069FileTransfer::GetInstance().HandleTimerExpiry(expiredTimer->GetTimerHandle()) ||
               Tr069ParameterValueChangeNotificationManager::GetInstance().HandleTimerExpiry(expiredTimer->GetTimerHandle())
           )
         {

         }
      }
   }

   EXIT();
}

bool Tr069Application::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
   ENTER();

   // First, pass to parent
   bool handled = ApplicationWithParamCache::MessageHandler(message);

   RSYS_ASSERT(message != NULL);

   switch (message->GetSerialisationId())
   {
      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
         {
            // The local parameter cache has already been updated...

            shared_ptr<MibSubscribeAttributesInd> subscribeAttributesInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);
            RSYS_ASSERT(subscribeAttributesInd != NULL);

            switch(subscribeAttributesInd->GetSubscriptionId())
            {
               case SubsCrypto:
                  {
                     authMethod = "PKI";
                     string cPath;
                     bool enabled;
                     u32  inst = subscribeAttributesInd->GetSubscriptionId() - SubsCrypto;
                     GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_CRYPTO_PROFILES, inst), PARAM_ID_CRYPTO_PROFILE_ENABLED, enabled );
                     GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_CRYPTO_PROFILES, inst), PARAM_ID_CRYPTO_PATH, cPath );

                     if (enabled == true)
                     {
                        // Set the auth method to PKI if the path does not 
                        if (cPath.find("Certificate") == string::npos)
                        {
                           authMethod = "PSK";
                        }
                     }
                  }
                  break;
               case SubsPm:
                  {
                     InitialisePMParms();
                  }
                  break;
               case SubsFapLteAdminState:
                  {
                     u16 lteAdminState;
                     GetMibCache().GetMibAttribute(PARAM_ID_LTE_FAP_ADMIN_STATE, lteAdminState);

                     TRACE_PRINTF("LTE AdminState is modified, current value is set to %s", (true==lteAdminState)? "true" : "false");

                     if((true == lteAdminState) && (true == m_StartMsgReceived)) 
                     {
                        KpiConfigure();
                     }

                     Tr069ServerConnection::GetInstance().HandleSecGwSubsciptionInd();
                  }
                  break;
               case SubsPerfMgmt:
                  {
                     u32 inst = subscribeAttributesInd->GetSubscriptionId() - SubsPerfMgmt;
                     UpdatePMParams(inst);
                     TRACE_PRINTF("Received dynamic update on PM related parameters");
                  }
                  break;
               case SubsPeriodicInform:
                  {
                     TRACE_PRINTF("Received dynamic update on periodic inform configuration");
                     Tr069ServerConnection::GetInstance().HandlePeriodicInformSubscriptionInd();
                  }
                  break;
               case SubsTr69ConnReq:
                  {
                     TRACE_PRINTF("Change to connection request username and password");
                     Tr069ServerConnection::GetInstance().HandleConnectionRequestParameterUpdate();
                  }
                  break;
               case SubsLogUpload:
                  {
                     TRACE_PRINTF("LOGUP:IN subs");
                     HandleLogUpload();
                  }
                  break;
               case SubsWcdma:
                  {
                     TRACE_PRINTF("Received wcdma scan state change.");

                     Tr069ServerConnection::GetInstance().InitializeCwmp();
                  }
                  break;
               case SubsRemScanStatus:
                  {
                     TRACE_PRINTF("Received lte scan state change.");

                     Tr069ServerConnection::GetInstance().InitializeCwmp();
                  }
                  break;
               case SubsStunEnable:
                  {
                     TRACE_PRINTF("Received Stun Enable change from HeMS.");
                     bool stunEnable;
                     GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_STUN_ENABLE,stunEnable) ;
                     if(stunEnable)
                     {
                         IPv4Address fgwIp;
                         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_ENB_IP_ADDR_IPV6, fgwIp);
                         Tr069UdpServer & startUdpServer = Tr069UdpServer::GetInstance(fgwIp);
                         RSYS_ASSERT(&startUdpServer);
                         startUdpServer.StartThread();
                     }
                  }
                  break;
               default:
                  {
                     MultiInstanceMibObjectManager::GetInstance().HandleMibSubscribeAttributesInd(subscribeAttributesInd->GetSubscriptionId());
                  }
                  break;
            }
         }
         break;

      case SERIALISATION_ID_ALARM_EVENT:
         {
            // Can't use the funky template here, we have special deserialisation requirements
            // as we have to get the correct alarm ID object into AlarmEvent first.
            shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::INVALID));

            RSYS_ASSERT(alarmId);

            AlarmEvent alarmEvent;
            alarmEvent.SetAlarmId(alarmId);

            // Should always deserialise successfully.
            bool deserialiseSuccess = alarmEvent.DeSerialise(message->GetSerialData(), message->GetSerialDataLength());
            RSYS_ASSERT(deserialiseSuccess);

            //MESSAGE_TAG_SHORT("OAM", "TR069", "OAM", "ALARM_EVENT", alarmEvent.ToString().c_str());

            m_alarmManager->HandleAlarmEvent(alarmEvent);
         }
         break;

      case SERIALISATION_ID_KPI_READ_CNF:
         {
            RSYS_ASSERT(m_kpiLogFileMgr);

            KpiReadCnf kpiReadCnf;

            bool deserialiseSuccess = kpiReadCnf.DeSerialise(message->GetSerialData(), message->GetSerialDataLength());
            RSYS_ASSERT(deserialiseSuccess);

            //MESSAGE_TAG_SHORT("OAM", "TR069", "OAM", "KPI_READ_CNF", kpiReadCnf.ToString().c_str());

            m_kpiLogFileMgr->WriteObject(kpiReadCnf.GetKpiGroup());
         }
         break;

      case SERIALISATION_ID_FTP_COMPLETE_IND:
      case SERIALISATION_ID_FTP_CNF:
      case SERIALISATION_ID_SW_INSTALL_CNF:
      case SERIALISATION_ID_SW_ACTIVATE_CNF:
      case SERIALISATION_ID_SW_UPDATE_CNF:
         {
            Tr069FileTransfer::GetInstance().HandleEvent(message);
         }
         break;

      case SERIALISATION_ID_MIB_VALIDATE_ATTRIBUTES_CNF:
         {
            Tr069FileTransfer::GetInstance().HandleEvent(message);
            Tr069ServerConnection::GetInstance().HandleEvent(message);
         }
         break;

      case SERIALISATION_ID_MIB_CREATE_OBJECT_CNF:
      case SERIALISATION_ID_MIB_DELETE_OBJECT_CNF:
      case SERIALISATION_ID_IKE_TUNNEL_CREATE_CNF:
      case SERIALISATION_ID_IKE_TUNNEL_DELETE_CNF:
      case SERIALISATION_ID_IKE_TUNNEL_DISCONNECT_IND:
      case SERIALISATION_ID_IKE_TUNNEL_CONNECT_IND:
         {
            Tr069ServerConnection::GetInstance().HandleEvent(message);
         }
         break;

      case SERIALISATION_ID_REM_SCAN_CNF:
         {
            MibAttributeValues selectedValues;

            Tr069ServerConnection::GetInstance().HandleEvent(message);

            static bool scanStatusComplete = false;
            if(!scanStatusComplete)
            {
               selectedValues.AddAttribute(PARAM_ID_LTE_REM_SCAN_STATUS, REM_STATUS_SUCCESS);
               scanStatusComplete = true;
            }

            if(selectedValues.GetAttributeCount() > 0)
            {
               GetMibCache().SetMibAttributes(selectedValues, ENTITY_TR069);
            }

         }
         break;

      case SERIALISATION_ID_REQUEST_START_RSP:
         {
            if (!m_StartMsgReceived)
            {
               TRACE_PRINTF("TR-069 START received...");

               m_StartMsgReceived = true;

               bool enableTr069 = true;
               GetMibCache().GetMibAttribute(PARAM_ID_ENABLE_TR069, enableTr069);
               TRACE_PRINTF("TR069 %s", enableTr069 ? "ENABLED" : "*DISABLED*");

               // Inform OAM that TR069 "Operational"
               MfOpStateInformInd opStateInform(MF_TR069, ManagedObject::OP_STATE_ENABLED, 0,
                     "TR069 App exiting, as not Tr069Enabled");
               SendMessage(opStateInform, ENTITY_OAM);

               if(!enableTr069)
               {
                  // Deregister our PID with the watchdog.
                  WatchdogRemovePid();

                  TRACE_PRINTF_LEV(TRACE_CRITICAL,"TR069 not enabled, exiting.");
                  exit(0);
               }

               ImportCommissioningAttributes();

               StartKeyPerformanceIndicationLogging();
               Tr069ParameterValueChangeNotificationManager::GetInstance().ClearPendingValueChanges();

               u32 startDelay = TimerEngine::MillisecondsToTicks(10);
               m_startDelayTimer = CreateTimer("StartDelayTimer", startDelay );
            }
            else
            {
               TRACE_PRINTF("TR-069 already started");
            }
         }
         break;

      case SERIALISATION_ID_MIB_SET_ATTRIBUTES_CNF:
      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_DELETE_IND:
      case SERIALISATION_ID_OAM_ACTION_CNF:
         // Ignore.
         break;
      case SERIALISATION_ID_KPI_COLL_REQ:
         {
            TRACE_PRINTF("Received KPI COLLECTION REQ %s.\n", message->ToString().c_str() );    
            std::string fileName;

            Tr069Application::GetInstance().GeneratePmFileName(fileName);
            RemoveOldPmFile(fileName);

            KpiCollectionReq kpiCollectionReq;
            bool deserialiseSuccess = kpiCollectionReq.DeSerialise(message->GetSerialData(), message->GetSerialDataLength());
            RSYS_ASSERT(deserialiseSuccess);

            if (Tr069Application::GetInstance().GeneratePmDataFile(fileName, kpiCollectionReq.IsReqAfterReboot()))
            {
               //if (std::system("pidof ftp-func >/dev/null 2>&1") == 0)
               if (std::system("pidof fileTransMgr >/dev/null 2>&1") == 0)
               {
                  if(m_perodicUploadEnable)
                  { 
                     Tr069Application::GetInstance().UploadPmDataFile(fileName);
                  }
                  else
                  {
                     TRACE_PRINTF("Att!! UploadPmDataFile is not performed as perodicUploadEnable is false");
                  }
               }      
               else
               {
                  TRACE_PRINTF("Att!! UploadPmDataFile is not performed as Application ftp-func is not running");
               }
            }
            else
            {
               TRACE_PRINTF("Att!! UploadPmDataFile is not performed as file is not generated");
            }
         }     
         break; 
      case SERIALISATION_ID_AUTONOMOUS_TRANSFER_COMP:
         {
            //Tr069ServerConnection  serverCon;
            shared_ptr<AutonomousTransferComp> autonomousTransferComp = Serialisable::DeSerialise<AutonomousTransferComp>(message);
            Tr069ServerConnection::GetInstance().HandleAutoTransferCompReq(autonomousTransferComp->GetFileName(),
                  autonomousTransferComp->GetStartTime(),
                  autonomousTransferComp->GetCompleteTime(),
                  autonomousTransferComp->GetUploadStatus());
         }
         break;
      default:
         {
            TRACE_PRINTF("Unhandled Receive %s.\n", message->ToString().c_str() );
         }
         break;
   }

   RETURN (handled);
}


void Tr069Application::StartKeyPerformanceIndicationLogging()
{
   RSYS_ASSERT(m_kpiLogFileMgr == NULL);

   string kpiLogFilename(Application::GetNvLogDirectory());
   kpiLogFilename += "tr069_kpi_log";

   // Build up a list of KPI groups that we want to log.
   for( size_t i = 0; i < sizeof(kpiGroupDefinitions)/sizeof(kpiGroupDefinitions[0]); ++i)
   {
      m_kpiGroupList.insert(kpiGroupDefinitions[i].kpiGroupId);
   }

   // We normally poll hourly so 48 gives us 2 days so we can always get KPIs for midnight-to-midnight yesterday.
   // Not forgetting to multiply by the number of KPI groups we expect to record.
   u32 numKpiGroups = (u32)m_kpiGroupList.size();
   TRACE_PRINTF("Collecting %" PRIu32 " KPI groups.", numKpiGroups);
   m_kpiLogFileMgr = shared_ptr<KpiLogFileMgr>(new  KpiLogFileMgr(kpiLogFilename.c_str(), numKpiGroups * 48));

   m_kpiLogFileMgr->StartLogging();

   u16 lteAdminState;
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_FAP_ADMIN_STATE, lteAdminState);

   if(true == lteAdminState)
   {
      TRACE_PRINTF("lteAdminState is true, so configuring the KPI's");
      KpiConfigure();
   }
   else
   {
      TRACE_PRINTF("lteAdminState is false, skipping configuring KPI's");
   }
}

void Tr069Application::KpiConfigure()
{
   KpiConfigureReq  kpiConfigureReq( m_kpiGroupList, m_collectionPeriodInSecs, m_perodicUploadInterval, m_perodicUploadPhaseAllignInMin );
   SendMessage(kpiConfigureReq, ENTITY_OAM);
}

void Tr069Application::HandleLogUpload() 
{ 
   TRACE_PRINTF("%s\n",__FUNCTION__); 
   u32 timer_value=0; 
   GetMibCache().GetMibAttribute((MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP)), PARAM_ID_LOG_UPLOAD_INTERVAL,timer_value); 
   if(IsTimerRunning(m_logTimerHandle)) 
   { 
      DeleteTimer(m_logTimerHandle); 
   } 
   if(timer_value > 0) 
   { 
      Tr069Application::GetInstance().StartLogTimer(timer_value*60000); 
   } 
   else 
   { 
      TRACE_PRINTF("\nLOG UPLOAD FUNCTIONALITY IS DISABLED"); 
   } 
} 

void Tr069Application::StartLogTimer(u32 timer_value) 
{ 
   m_logTimerHandle = CreateTimer((const std::string&)"LOG expiration timeout", timer_value ,TimerEngineInterface::TIMER_START_NOW, 
         TimerEngineInterface::TIMER_SINGLE_SHOT); 
} 

void Tr069Application::RebootFapViaOam()
{
   shared_ptr<RebootReq> rebootReq( new RebootReq() );
   Tr069Reboot::GetInstance().HandleEvent(rebootReq);
}

bool Tr069Application::GeneratePmDataFile( const Filename & filename, bool IsReqAfterReboot )
{
   u32 numKpiGroupsAggregated;
   bool IfFileGenerated = true;

   NsnPm nsnPm(m_kpiLogFileMgr,m_perodicUploadInterval,m_perodicUploadPhaseAllignInMin,m_collectionPeriodInSecs);
   m_kpiLogFileMgr->StopLogging();

   numKpiGroupsAggregated = nsnPm.CollateResults(IsReqAfterReboot);

   m_kpiLogFileMgr->StartLogging();

   if(1)
   {
      nsnPm.GenerateFile(filename); 
   }
   else
   {
      TRACE_PRINTF("Attn!! File is not generated, numKpiGroupsAggregated are %d",numKpiGroupsAggregated);
      IfFileGenerated = false;
   }

   return IfFileGenerated;          
}

void Tr069Application::UploadPmDataFile ( std::string fileName )
{
   ENTER();

   std::string commandKey = "command_key";
   std::string fileUrl;
   std::string username = m_UserName;
   std::string password = m_Passwd;
   std::string targetFilename = "";
   std::string successUrl = "";
   std::string failureUrl = "";

   ostringstream command;

   if ( m_enableFileCompress && (0 == m_compressMethod.compare("gzip") ) )
   {
      command << "gzip -fv "<<fileName.c_str();
      if(system(command.str().c_str()) == oam_ret_zero )
      {
         command.str(""); 
         fileUrl = fileName.append(".gz");  
      }else 
      {
         TRACE_MSG("Tr069Application::UploadPmDataFile, Failed to gzip file");
         EXIT();
      }
   }
   else
   {
      fileUrl = fileName;
   }

  shared_ptr<UploadRequest> uploadRequest(new UploadRequest(
          commandKey,
          shared_ptr<FtpFile>(new FtpFile()),
          0,
          fileUrl,
          username,
          password ) );

   shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( uploadRequest ));
   Tr069Application::GetInstance().Enqueue(fsc);

   EXIT();
}

void Tr069Application::GeneratePmFileName( std::string &fileName )
{
   ENTER();

   TimeWrap now;
   string timezoneOffsetToGmt;
   GetMibCache().GetMibAttribute(PARAM_ID_LOCAL_TIMEZONE_OFFSET_TO_GMT, timezoneOffsetToGmt );

   time_t secondsInReportDuration = m_perodicUploadInterval;
   time_t nowInUnixTime = now.GetUnixTime();
   time_t endOfLastReportDurationInUnixTime = ((nowInUnixTime / secondsInReportDuration) * secondsInReportDuration);
   time_t startOfLastReportDurationInUnixTime = (endOfLastReportDurationInUnixTime - secondsInReportDuration);

   TimeWrap startDateTime, endDateTime;
   endDateTime.Set(endOfLastReportDurationInUnixTime,0);
   startDateTime.Set(startOfLastReportDurationInUnixTime,0);
   fileName.append(getConfigFilePath().c_str());
   fileName.append("/");
   fileName.append("A");
   fileName.append(startDateTime.ToString(timezoneOffsetToGmt.c_str()).c_str());
   fileName.append("-");
   fileName.append(endDateTime.ToString(timezoneOffsetToGmt.c_str()).c_str()); 
   fileName.append(".xml");

   EXIT();   
}

void Tr069Application::GenerateSwVersionString()
{
}

std::string & Tr069Application::GetFormattedUtcTime ( std::string & timeString, const TimeWrap & timeWrap, u8 subSecondDecimalPlaces ) const
{
   u32 ntpSynchronised;
   GetMibCache().GetMibAttribute(PARAM_ID_NTP_STATUS,  ntpSynchronised );

   if(ntpSynchronised)
   {
      timeString  = timeWrap.ToString( subSecondDecimalPlaces );
      timeString += "Z";
   }
   else
   {
      timeString = "0001-01-01T00:00:00Z";
   }

   return timeString;
}


// This is contensious, but it's actually what we've always done...
static bool inTheAbsenceOfNtpSynchronisationUseOurBestGuessForLocalTime = true;

std::string & Tr069Application::GetFormattedLocalTime ( std::string & timeString, const TimeWrap & timeWrap, u8 subSecondDecimalPlaces ) const
{
   string ntpSynchronised;
   GetMibCache().GetMibAttribute(PARAM_ID_NTP_STATUS,  ntpSynchronised );

   if(!strcmp(ntpSynchronised.c_str(),"synchronised") || inTheAbsenceOfNtpSynchronisationUseOurBestGuessForLocalTime)
   {
      string timezoneOffsetToGmt;
      GetMibCache().GetMibAttribute(PARAM_ID_LOCAL_TIMEZONE_OFFSET_TO_GMT, timezoneOffsetToGmt );

      timeString  = timeWrap.ToString(timezoneOffsetToGmt.c_str(), subSecondDecimalPlaces );
   }
   else
   {
      timeString = "0001-01-01T00:00:00-00:00";
   }

   return timeString;
}


std::string & Tr069Application::GetFormattedCurrentTime ( std::string & timeString, u8 subSecondDecimalPlaces ) const
{
   TimeWrap now;

   return GetFormattedLocalTime( timeString, now, subSecondDecimalPlaces );
}

void Tr069Application::MibAttributesUpdated(u32 subscriptionId, const MibAttributeIdsByDn& mibAttributeValuesByDn)
{
   if(m_StartMsgReceived)
   {
      TRACE_PRINTF("MibAttributesUpdated %s", mibAttributeValuesByDn.ToString().c_str() );

      for( MibAttributeIdsByDn::const_iterator i = mibAttributeValuesByDn.begin();
            i != mibAttributeValuesByDn.end();
            ++i)
      {
         const MibDN & dn = i->first;
         const MibAttributeIds & attrIds = i->second;

         for( MibAttributeIds::const_iterator j = attrIds.begin();
               j != attrIds.end();
               ++j)
         {
            MibAttributeId mibAttributeId = *j;

            if( dn.ToString() == "FAP.0" )
            {
               switch(mibAttributeId)
               {
                  case PARAM_ID_KPI_REPORT_DURATION:
                     {
                        KpiConfigure();
                     }
                     break;

                  case PARAM_ID_PRIM_SC:
                     {
                        DataModelManager::GetInstance().MibAttributeUpdatedNotification( MibDN::GenerateMibDN("FAP.0"), mibAttributeId);
                     }
                     break;

                  case PARAM_ID_DL_UARFCN:
                     {
                        DataModelManager::GetInstance().MibAttributeUpdatedNotification( MibDN::GenerateMibDN("FAP.0"), mibAttributeId);
                     }
                     break;

#ifdef LTE_REM	
                  case PARAM_ID_ABORT_REM_SCAN:
                     {
                        TRACE_PRINTF("%s:RemScan Abort Request recevied from HeMS",__FUNCTION__);
                        CRemOamAbortScanCmd oamAbortScanCmd;
                        SendMessage(oamAbortScanCmd, ENTITY_OAM);
                     }
                     break;
#endif

                  default:
                     break;
               }
            }
         }
      }
   }
}

void Tr069Application::MibAttributesUpdated(u32 subscriptionId, const MibAttributeValuesByDn &oldValues, const MibAttributeValuesByDn &newValues)
{
   // Go through all the Domain's one by one (currently one subscriberID only supports one Domain, but this will change
   // to multiple domain support in future, so we may as well just write the code anyway.
   for(MibAttributeValuesByDn::const_iterator changedAttrsByDnIter = newValues.begin();
         changedAttrsByDnIter != newValues.end();
         ++changedAttrsByDnIter)
   {
      const MibDN& dn = changedAttrsByDnIter->first;
      const MibAttributeValues& changedAttrValues = changedAttrsByDnIter->second;

      // Now let's go through each parameter that has changed, updating the group info as we go.
      for(MibAttributeValues::MibAttributeValuesById::const_iterator iter = changedAttrValues.GetAttributeValues().begin();
            iter != changedAttrValues.GetAttributeValues().end();
            ++iter)
      {
         MibAttributeId mibAttributeId = iter->first;

         DataModelManager::GetInstance().MibAttributeUpdatedNotification( dn, mibAttributeId);

         if( dn.ToString() == "FAP.0" )
         {

            switch(mibAttributeId)
            {
               case PARAM_ID_LTE_SEC_GW_SERVER_1:
               case PARAM_ID_LTE_SEC_GW_SERVER_2:
               case PARAM_ID_LTE_SEC_GW_SERVER_3:
                  {
                     Tr069ServerConnection::GetInstance().UpdatedSecGwUrl( mibAttributeId );
                  }
                  break;

               default:
                  {
                  }

            }
         }

      }
   }
}

#define IFRSIZE   ((int)(size * sizeof (struct ifreq)))
bool Tr069Application::GetIPV6Address()
{
   struct ifaddrs *ifaddr, *ifa;
   int family, s, n;
   char host[NI_MAXHOST];
   //size_t pos;
   string hostipv6;//,hostipv6addr; 
   MibAttributeValues attrsIpAddr;

   if (getifaddrs(&ifaddr) == -1) 
   {
      TRACE_PRINTF("getifaddrs failed");
      return false;
   }

   for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) 
   {
      if (ifa->ifa_addr == NULL)
         continue;

      family = ifa->ifa_addr->sa_family;



      if ((family == AF_INET6) && (strcmp(ifa->ifa_name,"lo")!=0)) 
      {
         s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in6),host,NI_MAXHOST,
               NULL, 0, NI_NUMERICHOST);
         if (s != 0) 
         {
            RSYS_ASSERT_FAIL("getnameinfo() failed: %s\n", gai_strerror(s));
         }
         struct sockaddr_in6 *current_addr = (struct sockaddr_in6 *) ifa->ifa_addr;

         if (IN6_IS_ADDR_LINKLOCAL(&(current_addr->sin6_addr))) 
         continue;
         hostipv6= host;   
        // pos = hostipv6.find("%");      
        // hostipv6addr = hostipv6.substr (0,pos);    
        // TRACE_PRINTF("\n*** host: %s\n", host);
        // TRACE_PRINTF("\n*** hostipv6 %s hostipv6addr %s",hostipv6.c_str(),hostipv6addr.c_str());
         TRACE_PRINTF("\n*** host: %s\n", host);
         TRACE_PRINTF("\n*** hostipv6 %s",hostipv6.c_str());

         // attrsIpAddr.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV6, address.ToString()); // PROVIDED EXTRA
         attrsIpAddr.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV6, hostipv6); // PROVIDED EXTRA
         GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrsIpAddr, ENTITY_TR069);
         MibAttributeValues ipv6MioAttr;
         ipv6MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV6_ADDRESS,hostipv6);
         ipv6MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV6_ENABLE,(u32)true);
         MibDN ipInterfaceDn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
         MibDN::GenerateMibDN(ipInterfaceDn,MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS,0);
         GetMibCache().SetMibAttributes(ipInterfaceDn,ipv6MioAttr,ENTITY_OAM);

      }
   }
   freeifaddrs(ifaddr);

   return true;
}
bool Tr069Application::GetIPAddress(const char * interfaceName, IPv4Address &addr, IPv4Address &mask)
{
   TRACE("Getting IP address for interface", interfaceName);

   // do the IP address getty type stuff here
   int                sockfd, size  = 1;
   struct ifreq       *ifr;
   struct ifconf      ifc;
   struct sockaddr_in ipaddr;

   if (0 > (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)))
   {
      TRACE_PRINTF("Failed to open socket.");
      return false;
   }

   ifc.ifc_len = IFRSIZE;
   ifc.ifc_req = NULL;

   do
   {
      ++size;
      /* realloc buffer size until no overflow occurs  */
      if (NULL == (ifc.ifc_req = (ifreq *)realloc(ifc.ifc_req, IFRSIZE)))
      {
         RSYS_ASSERT_FAIL("realloc(): Out of memory.");
      }

      ifc.ifc_len = IFRSIZE;
      if (ioctl(sockfd, SIOCGIFCONF, &ifc))
      {
         RSYS_ASSERT_FAIL("ioctl(SIOCFIFCONF): %s", strerror(errno));
      }
   } while  (IFRSIZE <= ifc.ifc_len);


   for (ifr = ifc.ifc_req;(char *) ifr < (char *) ifc.ifc_req + ifc.ifc_len; ++ifr)
   {

      if (ifr->ifr_addr.sa_data == (ifr+1)->ifr_addr.sa_data)
      {
         continue;  /* duplicate, skip it */
      }

      if (ioctl(sockfd, SIOCGIFFLAGS, ifr))
      {
         continue;  /* failed to get flags, skip it */
      }

      // Copy to overcome accessing restricted pointer of different types
      memcpy(&ipaddr, &ifr->ifr_addr, sizeof(struct sockaddr_in));

      IPv4Address address(inet_ntoa(ipaddr.sin_addr));
      if(!strcmp(interfaceName, ifr->ifr_name))
      {

         MibAttributeValues attrsIpAddr;
         attrsIpAddr.AddAttribute(PARAM_ID_UNIT_IP_ADDRESS, address.ToString());
         GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrsIpAddr, ENTITY_TR069);
         if (ioctl(sockfd, SIOCGIFNETMASK, ifr))
         {
            RSYS_ASSERT_FAIL("Failed to open socket.");
            RSYS_ASSERT_FAIL("realloc(): Out of memory.");
            RSYS_ASSERT_FAIL("ioctl(SIOCFIFCONF): %s", strerror(errno));
            continue;  /* failed to get flags, skip it */
         }

         // Copy to overcome accessing restricted pointer of different types
         memcpy(&ipaddr, &ifr->ifr_netmask, sizeof(struct sockaddr_in));

         IPv4Address netmask(inet_ntoa(ipaddr.sin_addr));
         if(!strcmp(interfaceName, ifr->ifr_name))
         {
            MibAttributeValues attrsNetmask;
            attrsNetmask.AddAttribute(PARAM_ID_UNIT_IP_NET_MASK, netmask.ToString());
            GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrsNetmask, ENTITY_TR069);
         }


         TRACE(" Interface NAME=", interfaceName);
         char sysCmd[200];
         snprintf( sysCmd, sizeof(sysCmd), "route | grep %s | grep default | awk '{print $2}' > /tmp/gateway.txt", interfaceName);
         TRACE_PRINTF("Tr069Application: value of system command at OAM user app= %s",sysCmd);
         if(system(sysCmd) != oam_ret_zero)
         {
            TRACE_MSG("Tr069Application::GetIpAddress, Failed to execute system command");
         }	

         ifstream gatewayFileStream( "/tmp/gateway.txt") ;
         if (gatewayFileStream)
         {
            char oneLineFromFile[128] = "";
            gatewayFileStream.getline(oneLineFromFile, sizeof(oneLineFromFile));
            gatewayFileStream.close();

            TRACE_PRINTF("Gateway(%s) = %s", interfaceName, oneLineFromFile);
            IPv4Address gateway( oneLineFromFile);

            MibAttributeValues attrsIpAddr;
            attrsIpAddr.AddAttribute(PARAM_ID_UNIT_IP_GATEWAY, gateway.ToString());
            GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrsIpAddr, ENTITY_TR069);			

         }
         unlink("/tmp/gateway.txt");

         addr = address;
         mask = netmask;

         fprintf(stderr, "%s: address %s mask %s\n", ifr->ifr_name, address.ToString(), netmask.ToString());
         TRACE_PRINTF("Ip Address of %s as read via ioctl %s netmask %s", ifr->ifr_name, address.ToString(), netmask.ToString() );
         // Register our PID with the watchdog.
         Tr069Application::isWatchdogDereg =false;
         WatchdogRegisterPid();
         m_watchdogKickTimer = CreateTimer ("Tr069WatchdogKick",5000, TimerEngineInterface::TIMER_START_NOW,TimerEngineInterface::TIMER_REPEAT);
         WatchdogKick(getpid(),5,15);
         close(sockfd);
         return true;
      }
   }

   TRACE_MSG("No Ip Address found via ioctl");

   close(sockfd);
   return false;
}

// Function to retrieve the soap timeout value if configured, to be sent in 
// response messages to ACS
std::string Tr069Application::GetSoapTimeout()
{
   u32 timeoutEnable, timeout = 40;
   string soapTimeout="";
   ostringstream timeoutStr;
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOAP_SESS_TIMEOUT_ENABLE, timeoutEnable);
   if(timeoutEnable)
   {
      GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOAP_SESS_TIMEOUT, timeout );		
      timeoutStr << timeout;
      soapTimeout = timeoutStr.str();
   }
   return soapTimeout;
}

std::string Tr069Application::GetAuthMethod()
{
   return m_auth;
}

std::string Tr069Application::GetDigestAttribute(std::string attribute)
{
   TRACE_PRINTF("%s",__func__);

   string val="";
   map<std::string,std::string>::iterator it;

   for(it=m_digestMap.begin();it!=m_digestMap.end();++it)
   {
      if(0 == strcmp(attribute.c_str(), (it->first).c_str()))
      {
         val = it->second;
         break;
      }
   }
   return val;
}

void Tr069Application::StartStunTimer(u32 timer_value)
{
    m_stunTimerHandle = CreateTimer("Stun Timer",timer_value, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_REPEAT);
}

void Tr069Application::SendBindingRequest(int fd,StunAddress4 stunServerAddr)
{
   TRACE_PRINTF("%s",__func__);
   initNetwork();
   stunSockFd = fd;
   StunServerAddr = stunServerAddr;
   StunEncodeRequest(fd,stunServerAddr);
}

/**
 * Application entry point.
 */
int main(int argc, char* argv[])
{
   my_argc = argc;
   my_argv = argv;

   int result = Tr069Application::GetInstance().Run(argc, argv);
   return result;
}

string tr069::XmlSafeString( const string & input )
{
   string output(input);

   size_t position = output.find_first_of("&<>\'\"");
   while (position != string::npos)
   {
      switch(output.at(position))
      {
         case '&': output.replace(position, 1, "&amp;"); break;
         case '<': output.replace(position, 1, "&lt;"); break;
         case '>': output.replace(position, 1, "&gt;"); break;
                   case '\"': output.replace(position, 1, "&quot;"); break;
         case '\'': output.replace(position, 1, "&apos;"); break;

      }
      position = output.find_first_of("&<>\'\"",position+1);
   }

   return output;
}

void Tr069Application::RemoveOldPmFile(std::string FileName)
{
   if (m_PmFileNames.size() < m_max_pmFiles)
   {
      m_currentPmFilenameIdx = (m_currentPmFilenameIdx+1)%m_max_pmFiles;
      m_PmFileNames.push_back(FileName);
      TRACE_PRINTF("m_PmFileNames.size() =%d",m_PmFileNames.size());
   }
   else
   {
      std::string fileToDetele = m_PmFileNames.at(m_currentPmFilenameIdx);
      m_PmFileNames[m_currentPmFilenameIdx] = FileName;
      m_currentPmFilenameIdx = (m_currentPmFilenameIdx+1)%m_max_pmFiles;
      if(m_perodicUploadEnable)
      {
         //fileToDetele = threeway::getConfigFilePath()+"\\"+fileToDetele;

      }
      if(!remove(fileToDetele.c_str()))
      {
         TRACE_PRINTF("%s : Old PM file %s have removed ",__FUNCTION__,FileName.c_str());
      }
      else
      {
         std::string rm_cmd = "pwd && rm -rf "+fileToDetele;
         if(!system(rm_cmd .c_str()))
         {
            TRACE_PRINTF("%s : Failed to remove Old PM file %s cmd %s ",__FUNCTION__,FileName.c_str(),rm_cmd.c_str());
         }
         else
         {
            TRACE_PRINTF("%s :Removed old  Old PM file :%s ",__FUNCTION__,FileName.c_str());
         }
      }
      
   }
   m_currentPmFilenameIdx = (m_currentPmFilenameIdx+1) % m_max_pmFiles;
}
