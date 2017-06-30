
///////////////////////////////////////////////////////////////////////////////
//
// OamUserApplication.cpp
//
// Entry point for OAM app.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <fstream>
/* 0.9_patch3: signal handling */
#include <signal.h>
#include <dirent.h>

#include <system/pthread_utils.h>
#include <system/Trace.h>
#include <system/TimerEngine.h>
#include <system/SerialisationIds.h>
#include <system/SoftwareRelease.h>
#include <system/Utilities.h>
#include <MibAttributes.h>
#include <MibAttributeId.h>
#include <mib-common/ValidationReferences.h>
#include <mib-common/ValidatorDownlinkUArfcn.h>
#include <mib-common/ValidatorDownlinkUArfcnRem.h>
#include <mib-common/ValidatorDownlinkArfcn.h>
#include <mib-common/messages/MibCreateObjectReq.h>
#include <mib-common/messages/MibCreateObjectCnf.h>
#include <mib-common/messages/MibDeleteObjectReq.h>
#include <mib-common/messages/MibDeleteObjectCnf.h>
#include <mib-common/messages/MibSubscribeAttributesDeleteInd.h>
#include <mib-common/messages/MibValidateAttributesReq.h>
#include <mib-common/messages/MibValidateAttributesCnf.h>
#include <mib-common/messages/MibSetAttributesReq.h>
#include <mib-common/messages/MibSetAttributesCnf.h>
#include <mib-common/messages/MibGetAttributesReq.h>
#include <mib-common/messages/MibGetAttributesCnf.h>
#include <mib-common/messages/MibDeleteAttributesReq.h>
#include <mib-common/messages/MibDeleteAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <mib-common/messages/MibUnsubscribeReq.h>
#include <mib-common/messages/MibUnsubscribeCnf.h>
#include <system/StringUtils.h>
#include <system/WatchDogDereg.h>
#include <messaging/messages/cphy/CPhyHwConfigReq.h>
#include <messaging/messages/cphy/CPhyHwConfigCnf.h>
#include <messaging/messages/cphy/CPhyModeChangeReq.h>
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/common/OamActionCnf.h>
#include <messaging/messages/common/MfSetAdminStateReq.h>
#include <messaging/messages/common/RequestStartInd.h>
#include <messaging/messages/common/RequestStartRsp.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/cphy/CPhyNodeBTxEnableCnf.h>
#include <messaging/messages/ike/IkeTunnelCreateCnf.h>
#include <messaging/messages/ike/IkeTunnelConnectInd.h>
#include <messaging/transport/MessageSerialisedData.h>
#if 0
#include <messaging/messages/carb/CarbTemperatureReq.h>
#include <messaging/messages/carb/CarbTemperatureCnf.h>
#endif
#include <messaging/messages/cphy/CPhyNodeBStatInd.h>
#include <messaging/messages/cphy/CPhyNodeBConfigCnf.h>
#include <messaging/messages/cphy/CPhyModeChangeCnf.h>
#include <messaging/messages/common/RemScanReq.h>
#include <messaging/messages/common/RemScanCnf.h>
#include <messaging/messages/common/UploadLogReq.h>
#include <messaging/messages/common/KpiConfigureReq.h>
#include <messaging/messages/common/KpiRegisterReq.h>
#include <messaging/messages/common/KpiReadCnf.h>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/tenpin/TenpinDnsServerAddReq.h>
#include <messaging/messages/tenpin/TenpinDnsServerAddCnf.h>
#include <messaging/messages/tenpin/TenpinFirewallOpenReq.h>
#include <messaging/messages/tenpin/TenpinFirewallOpenCnf.h>
#include <messaging/messages/tenpin/TenpinFirewallCloseReq.h>
#include <messaging/messages/tenpin/TenpinFirewallCloseCnf.h>
#include <mobnet/NeighbourCells.h>
#include <system/FrequencyBandsSupported.h>
#include <mobnet/RemScanStatusId.h>
#include <comms/GsmRemPDUs.h>
#include <comms/IPAddress.h>
#include <nas.h>
#include <platform/FapAlarmId.h>
#include <platform/rt_fifos.h>
#include <netdb.h>
#include <mib-common/MIOAutoManage.h>
#ifdef LTE_REM
#include <messaging/messages/rem/rem_msgs.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "managed-objects/FapMO.h"
#include "OamUserApplication.h"
#include "OamCli.h"
#include "oam_env.h"

#include "OamConfigFile.h"
#include "MibHelper.h"
#define OBJECT_CONFIGURED 1

using namespace threeway;
using namespace boost;

bool OamUserApplication::isWatchdogDereg =false;
///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

extern ValidatorDownlinkUArfcn validatorDownlinkUArfcn;
extern ValidatorDownlinkUArfcnRem validatorDownlinkUArfcnRem;
extern ValidatorDownlinkArfcn validatorDownlinkArfcn;

#define MAX_DIR_LEN 50

int oam_act_reboot = FALSE;
///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<OamUserApplication> OamUserApplication::s_instance;

DeclareAppVersionStamp
string FqdnToIp(string ntpDn);
///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

OamUserApplication::OamUserApplication() :
   SingleThreadedAppWithAttrCache("oam"),
   m_l1l2Started(false),
   m_iuReady(false),
   m_oamReady(false),
   m_swUpdateReady(false),
   m_tr069Ready(false),
   m_rrcReady(false),
   m_rrmReady(false),
   m_cphyReady(false),
   m_psUserPlaneReady(false),
   m_csUserPlaneReady(false),
   m_ggsnReady(false),
   m_tenpinReady(false),
   m_sapiReady(false),
   m_smReady(false),
   m_fapSecurityInitialised(false),
   m_alarmMgr(*this, 0),
   m_periodicRescanTimer(NULL_TIMER),
   m_fsm(*this, true),
   m_triggerPacketTimerHandle(NULL_TIMER),
   m_ateIpSecTimerHandle(NULL_TIMER),
   m_tempReadingTimerHandle(NULL_TIMER),
   m_tempMonitor(*this),
   m_mfManager(*this),
   m_stuckAlarmCleared(false),
   speedScaleCount(0)
{
}

OamUserApplication::~OamUserApplication()
{
}

OamUserApplication& OamUserApplication::GetInstance()
{
   if (s_instance == NULL)
   {
      s_instance.reset(new OamUserApplication());
   }

   return *s_instance;
}

void OamUserApplication::SendSubscriptionNotification(
      u32 subscriberId,
      u32 subscriptionId,
      const MibAttributeValuesByDn & mibAttributeValuesByDn)
{
   MibSubscribeAttributesInd subscribeMibAttributesInd(subscriptionId, mibAttributeValuesByDn);
   SendMessage(subscribeMibAttributesInd, (MessagingEntity)subscriberId, ENTITY_MIB);
}

void OamUserApplication::SendSubscriptionDeleteNotification(u32 subscriberId,
      u32 subscriptionId,
      const MibAttributeIdsByDn& deletedAttributeIdsByDn)
{
   MibSubscribeAttributesDeleteInd deleteInd(subscriptionId, deletedAttributeIdsByDn);
   SendMessage(deleteInd, (MessagingEntity)subscriberId, ENTITY_MIB);
}

vector<MessagingEntity> OamUserApplication::GetSupportedEntities()
{
   vector<MessagingEntity> entities;

   entities.push_back(ENTITY_OAM);
   entities.push_back(ENTITY_MIB);
   //entities.push_back(ENTITY_FREQ_SYNC);
   entities.push_back(ENTITY_OAM_HW);
   entities.push_back(ENTITY_TRIGGER_PACKET_RECEIVER);
   entities.push_back(ENTITY_SIBS);

   return entities;
}

void OamUserApplication::GetSubscriptions(vector<SubscriptionDescriptor>& subscriptions)
{
   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
   string numCellStr = getConfigParam("OAM_NUM_CELL_ENTRIES", "");
   u16 numCell=1;
   if(NULL != numCellStr.c_str())
   {
      numCell = (u16)atoi(numCellStr.c_str());
   }

   {
      TRACE_PRINTF("Subscribing NTP parameters");

      MibAttributeIds mibntpParameters;
      mibntpParameters.insert(PARAM_ID_NTP_ENABLE);
      mibntpParameters.insert(PARAM_ID_DEFAULT_NTP_SERVER);
      mibntpParameters.insert(PARAM_ID_NTP_SERVER_1);
      mibntpParameters.insert(PARAM_ID_NTP_SERVER_2);
      mibntpParameters.insert(PARAM_ID_NTP_SERVER_3);
      mibntpParameters.insert(PARAM_ID_NTP_SERVER_4);
      mibntpParameters.insert(PARAM_ID_NTP_SERVER_5);
      mibntpParameters.insert(PARAM_ID_X_RADISYS_NTP_SYNC_INTERVAL);

      AddSubscription(subscriptions,SUBSCRIPTION_ID_NTP_CFG_PARAMETERS, ENTITY_OAM, fapDn,mibntpParameters);
   }

   {
      MibAttributeIds otherMibAttrs;
      otherMibAttrs.insert(PARAM_ID_LOG_UPLOAD_INTERVAL);
      AddSubscription(subscriptions, SUBSCRIPTION_ID_LOG_UPLOAD_INTERVAL, ENTITY_OAM, fapDn, otherMibAttrs);
   }

   {
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE);
      MibAttributeIds DlEarfcnForREMMibAttrs;
      DlEarfcnForREMMibAttrs.insert(PARAM_ID_LTE_EARFCNDL_LIST);
      AddSubscription(subscriptions, SUBSCRIPTION_ID_DL_EARFCN_FOR_REM, ENTITY_OAM, fapLteDn, DlEarfcnForREMMibAttrs);
   }
   {
      MibAttributeIds traceFTParameters;
      traceFTParameters.insert(PARAM_ID_TRACE_FT_SERVER_NAME);
      traceFTParameters.insert(PARAM_ID_TRACE_FT_USER_NAME);
      traceFTParameters.insert(PARAM_ID_TRACE_FT_PASSWORD);
      traceFTParameters.insert(PARAM_ID_TRACE_FT_METHOD);
      traceFTParameters.insert(PARAM_ID_TRACE_FT_REMOTE_LOCATION);
      AddSubscription(subscriptions,SUBSCRIPTION_ID_TRACE_FT_PARAMETERS,ENTITY_OAM,fapDn,traceFTParameters);
   }
   {
      MibAttributeIds Ipv6MIOParams;
      Ipv6MIOParams.insert(PARAM_ID_IP_INTERFACE_IPV6_ENABLE );

      MibDN ipV6Dn_0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
      MibDN::GenerateMibDN(ipV6Dn_0,MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS,0);
      AddSubscription(subscriptions,SUBSCRIPTION_ID_IPV6_0,ENTITY_OAM,ipV6Dn_0,Ipv6MIOParams);

      MibDN ipV6Dn_1= MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
      MibDN::GenerateMibDN(ipV6Dn_1,MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS,1);
      AddSubscription(subscriptions,SUBSCRIPTION_ID_IPV6_1,ENTITY_OAM,ipV6Dn_1,Ipv6MIOParams);
   }

}

void OamUserApplication:: modifyField(FILE *fptr,std::string arg_FieldName,std::string newValue)
{
   char buff[100],fieldName[100];//=arg_FieldName.c_str();
   char buff2[100];
   strcpy(fieldName,arg_FieldName.c_str());
   while(fscanf(fptr,"%s",buff)!=EOF)
   {
      strcpy(buff2,buff);
      for (u32 idx=0;idx<strlen(buff);idx++)
      {
         if(buff[idx] == '=')
         {
            u32 gobackLen = strlen(buff);
            if(!strcmp(arg_FieldName.c_str(),fieldName))
            {
               TRACE_PRINTF("Filed name %s",fieldName);
               idx++;//ignoring delemete
               /* Kloc work fix for ABV.GENERAL */
               snprintf(&buff[idx],(sizeof(char)*100),"%s #",newValue.c_str());//eraze old value
               fseek(fptr,-1*gobackLen,SEEK_CUR); // moving back
               fprintf(fptr,"%s",buff);
               return;
            }
         }
      }
   }
}

void OamSignalSigtermHandler(int sig)
{
   OamUserApplication::isWatchdogDereg = true;
   DeregisterWithWatchDog(ENTITY_OAM, ENTITY_WATCHDOG);
   exit(0);
}

void OamUserApplication::SetLogDirPath(string path)
{
   logFileDir = path;
}
void OamUserApplication::SetAppLogFileName(string name)
{
    logFileName = name;
}
void OamUserApplication::InitialiseApp()
{
   signal(SIGTERM,OamSignalSigtermHandler);

   RegisterMessageHandler(this, "Oam");

   // Instantiate the MIB object
   m_mibManager.reset(new MibManager(this));

   if(!(m_mibManager->nvStoreInitialized))
   {
      string val;

      val = getConfigParam("OAM_CONFIG_FILES_DIR", "");
      std::string sOamConfigFilesDir="";
      char* pOamConfigFilesDir=NULL;
      pOamConfigFilesDir = (char *)val.c_str();;
      sOamConfigFilesDir = pOamConfigFilesDir;
      sOamConfigFilesDir = sOamConfigFilesDir + "/config/";
      ostringstream command;
      command <<"cd " << sOamConfigFilesDir.c_str() << " && " << "rm -f *" << " && " << "reboot";
      TRACE_PRINTF("Reboot Command : %s", command.str().c_str());
      if(system(command.str().c_str()) != oam_ret_zero)
      {
         TRACE_MSG("OamUserApplication::HandleOamActionReq, Reboot command Failed");
      }
   }
   string logDirTag = getConfigParam("OAM_LOGGING_DIR", "");
   SetLogDirPath(logDirTag);
   string appLogFileName = getConfigParam("OAM_TAG_LOG_FILE_NAME", "");
   SetAppLogFileName(appLogFileName);

   // Initialise MIB - holds all (management-)configurable parameter values.
   MibHelper::BuildMoTree(GetMibManager());

   // Check for developer file and apply any matching attributes to the MIB.
   MibHelper::ApplyDeveloperMibAttributes();

   // Create all the FIFOs that are used by l1l2
   for(u32 fifoNum = MIN_FIFO_NUMBER; fifoNum <= MAX_FIFO_NUMBER; fifoNum++)
   {
      char fifoName[20];

      snprintf(fifoName, sizeof(fifoName), "%s%" PRIu32, RT_FIFO_DEV_PREFIX, fifoNum);
      mknod(fifoName, S_IFIFO|0666, 0);
   }

   // Set s/w release in MIB from config file.
   SetSoftwareReleaseAndBuildDesc(); // Of the form 0xAABBCCDD to give decimal a.b.c.d release number.  E.g. 1.0, 1.1

   // Register CLI handler.
   shared_ptr<CliHandler> cliOam(new CliHandler(ENTITY_OAM, "oam"));
   shared_ptr<CliHandler> cliMib(new CliHandler(ENTITY_MIB, "mib"));
   OamCli::RegisterOamCliCmds(cliOam);
   OamCli::RegisterMibCliCmds(cliMib);
   RegisterCliHandler(ENTITY_OAM, cliOam); // Base class keeps a shared ptr to it.
   RegisterCliHandler(ENTITY_MIB, cliMib); // Base class keeps a shared ptr to it.

   // Create object for managing KPIs.  Deals with requesting and aggregating KPI values.
   m_kpiMgr.reset(new KpiManager(m_timerEngine, *this /* timerNotifyInterface */, *this /* messageSender */));

   // Get the alarm manager up n running.
   m_alarmMgr.Start();
}

void OamUserApplication::StartApp()
{
   OamUserApplication::isWatchdogDereg =false;
   WatchdogRegisterPid();
   m_watchdogKickTimer = CreateTimer ("OAMWatchdogKick", 5000, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_REPEAT);
   WatchdogKick(getpid(),5,15);
}

bool OamUserApplication::SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity) const
{
   // Trace messages in proto prof
   MESSAGE_TAG_SHORT(MessagingEntityToString(sourceEntity),
         MessagingEntityToString(destinationEntity),
         "", SerialisationIdToString((SerialisationId)messageToSend.GetSerialisationId()), "TX");

   return SingleThreadedAppWithAttrCache::SendMessage(messageToSend, destinationEntity, sourceEntity);
}

void OamUserApplication::SendRequestStartRsp(MessagingEntity entity)
{
   RequestStartRsp requestStartRsp;
   SendMessage(requestStartRsp, entity, ENTITY_OAM);
}

#if 0
void OamUserApplication::InitFreqSyncEntity()
{
   u32 factoryOscDac;
   u32 liveOscDac;
   s32 pptPerBit;
   u32 adminStateU32;
   u32 remScanResultU32;
   MibHelper::GetMibAttributeDirect(PARAM_ID_OSC_DAC, factoryOscDac);
   MibHelper::GetMibAttributeDirect(PARAM_ID_LIVE_OSC_DAC, liveOscDac);
   MibHelper::GetMibAttributeDirect(PARAM_ID_OSC_DAC_SLOPE_PPT_PER_BIT, pptPerBit);
   MibHelper::GetMibAttributeDirect(PARAM_ID_FREQ_SYNC_ADMIN_STATE, adminStateU32);
   MibHelper::GetMibAttributeDirect(PARAM_ID_REM_SCAN_RESULT, remScanResultU32);

   TRACE_PRINTF("InitFreqSyncEntity fod = %" PRIu32 ", lod = %" PRIu32 " ppt = %" PRId32 " as = %" PRIu32 " rsok = %" PRIu32,
         factoryOscDac, liveOscDac, pptPerBit, adminStateU32,remScanResultU32);
   m_freqSyncEntity.Startup(factoryOscDac,liveOscDac,pptPerBit,(bool)adminStateU32,(eRemScanResult)remScanResultU32);
}
#endif

bool OamUserApplication::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
   // First, pass to parent
   bool handled = SingleThreadedAppWithAttrCache::MessageHandler(message);
   if(handled)
   {
      return true;
   }

   SerialisationId serialisationId = (SerialisationId)message->GetSerialisationId();

   if((serialisationId != SERIALISATION_ID_CPHY_NODEB_STAT_IND) && // We get this every couple of secs... let's not clog the trace file.
         (serialisationId != SERIALISATION_ID_KPI_READ_CNF)           // And we only get these when using CLI pollkpis and they make it hard to read the results.
     )
   {
      // Proto prof it.
      MESSAGE_TAG_SHORT(MessagingEntityToString(message->GetFromEntity()),
            MessagingEntityToString(message->GetToEntity()),
            "", SerialisationIdToString((SerialisationId)message->GetSerialisationId()),
            "RX");
   }
   else
   {
      // Put these under 'verbose' trace.
      TRACE_PRINTF_LEV(TRACE_VERBOSE, "Received: %s", message->ToString().c_str());
   }

   switch (message->GetToEntity())
   {
      case ENTITY_MIB:
         HandleMibMessage(message);
         break;

      case ENTITY_OAM:
         HandleOamMessage(message);
         break;
#if 0
      case ENTITY_FREQ_SYNC:
         m_freqSyncEntity.HandleMessage(message);
         break;
#endif
      default:
         break;

   } // end switch

   return handled;
}

void OamUserApplication::HandleOamMessage(shared_ptr<threeway::MessageSerialisedData> message)
{
   SerialisationId serialisationId = (SerialisationId)message->GetSerialisationId();

   switch(serialisationId)
   {
      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
         {
            shared_ptr<MibSubscribeAttributesInd> subscribeAttributesInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);
            RSYS_ASSERT(subscribeAttributesInd != NULL);

            switch(subscribeAttributesInd->GetSubscriptionId())
            {
               case SUBSCRIPTION_ID_LOG_UPLOAD_INTERVAL:
                  {
                     // Check if FAP ID is now set.
                     const MibAttributeValues& attributeValues = subscribeAttributesInd->GetMibAttributeValues(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP));

                     if(attributeValues.IsAttributePresent(PARAM_ID_FAP_ID))
                     {
                        string fapId;
                        attributeValues.GetAttributeValue(PARAM_ID_FAP_ID, fapId);
                     }
                     HandleLogUpload();
                  }
                  break;
               case SUBSCRIPTION_ID_NTP_CFG_PARAMETERS:
               case SUBSCRIPTION_ID_DEFAULT_NTP_CFG:
                  {
                     HandleNtpParams();
                  }
                  break;
               case SUBSCRIPTION_ID_TRACE_FT_PARAMETERS:
                  {
                     static bool TraceDirLocConfigured=false;
                     std::string ftServerName,ftUserName,ftPassword,
                        ftMethod,ftRemoteLocation;

                     MibHelper::GetMibAttributeDirect(PARAM_ID_TRACE_FT_SERVER_NAME,ftServerName);
                     MibHelper::GetMibAttributeDirect(PARAM_ID_TRACE_FT_USER_NAME,ftUserName);
                     MibHelper::GetMibAttributeDirect(PARAM_ID_TRACE_FT_PASSWORD,ftPassword);
                     MibHelper::GetMibAttributeDirect(PARAM_ID_TRACE_FT_METHOD,ftMethod);
                     MibHelper::GetMibAttributeDirect(PARAM_ID_TRACE_FT_REMOTE_LOCATION,ftRemoteLocation);

                     string ftpScript = getConfigFilePath();
                     ftpScript = ftpScript + "/ftpputLog.sh";
                     TRACE_PRINTF("%s:%d reading file %s",__func__, __LINE__, ftpScript.c_str());
                     FILE *fptr;
                     if((fptr=fopen(ftpScript.c_str(), "r+")))
                     {

                        modifyField(fptr,"FTP_SERVER",ftServerName);
                        modifyField(fptr,"FTP_USER",ftUserName);
                        modifyField(fptr,"FTP_PASSWORD",ftPassword);
                        modifyField(fptr,"FILE_TRANSFER_METHOD",ftMethod);
                        modifyField(fptr,"DESTINATION_PATH",ftRemoteLocation);
                        if(!TraceDirLocConfigured)
                        {
                           string configFileDir;
                           configFileDir = getConfigParam("OAM_LOGGING_DIR", "");
                           if(configFileDir.find("../")!=std::string::npos)
                           {
                              char pwd[1000];
                              if(getcwd(pwd,sizeof(pwd)))
                              {
                                 string pwd_string(pwd);

                                 configFileDir=pwd_string+"/"+configFileDir;

                              }
                           }
                           modifyField(fptr, "FTP_TRACE_LOCATION", configFileDir);
                           TraceDirLocConfigured=true;
                        }

                        fclose(fptr);
                     }
                  }
                  break;

               case SUBSCRIPTION_ID_IPV6_0:
               case SUBSCRIPTION_ID_IPV6_1:
                  {
                     TRACE_PRINTF("Subscription received for ipv6 mio");

                     u32 enabled;
                     u32 instance= subscribeAttributesInd->GetSubscriptionId()-SUBSCRIPTION_ID_IPV6_0;
                     std::string status;

                     MibDN ipV6Dn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
                     MibDN::GenerateMibDN(ipV6Dn,MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS,instance);
                     GetMibCache().GetMibAttribute(ipV6Dn,PARAM_ID_IP_INTERFACE_IPV6_ENABLE , enabled );
                     if(enabled)
                     {
                        status="Enabled";
                     }
                     else
                     {
                        status="Disabled";
                     }
                     MibAttributeValues attrs;
                     attrs.AddAttribute(PARAM_ID_IP_INTERFACE_IPV6_STATUS ,status);
                     GetMibCache().SetMibAttributes(ipV6Dn,attrs,ENTITY_OAM);
                  }
                  break;

               default:
                  break;
            }
         }
         break;

      case SERIALISATION_ID_MF_OP_STATE_INFORM_IND:
         {
            HandleOpStateInformMessage(message);
         }
         break;

      case SERIALISATION_ID_MF_SET_ADMIN_STATE_REQ:
         {
            shared_ptr<MfSetAdminStateReq> setAdminStateReq = Serialisable::DeSerialise<MfSetAdminStateReq>(message);
            RSYS_ASSERT(setAdminStateReq != NULL);

            TRACE("MfSetAdminStateReq received", setAdminStateReq->ToString());

            switch(setAdminStateReq->GetManagedFing())
            {
               case MF_RADIO:
                  {
                     // TODO: this is a bit too indirect, needs some refactoring.  For now if RADIO is locked/unlocked
                     // we update the op state which will feed into the OAM FSM and disable the radio.
                     // We should really be sending the MfSetAdminStateReq down to L1.
                     FapMO::GetInstance().SetServiceApiDisableRadio(setAdminStateReq->GetAdminState() == ManagedObject::ADMIN_STATE_LOCKED);
                  }
                  break;
               default:
                  RSYS_ASSERT_FAIL("Unexpected MF: %s", ManagedFingToString(setAdminStateReq->GetManagedFing()));
                  break;
            }
         }
         break;

      case SERIALISATION_ID_OAM_ACTION_REQ:
         HandleOamActionReq(message);
         break;

      case SERIALISATION_ID_REQUEST_START_IND:
         {
            shared_ptr<RequestStartInd> startMessage = Serialisable::DeSerialise<RequestStartInd>(message);
            TRACE_LEV(TRACE_VERBOSE, "  Ready signal received", MessagingEntityToString(message->GetFromEntity()));
            switch(message->GetFromEntity())
            {
               case ENTITY_TR069:
                  UpdateReadyFlag(m_tr069Ready);
                  StartTr069();
                  break;

               case ENTITY_RRC:
                  UpdateReadyFlag(m_rrcReady);
                  break;

               case ENTITY_RRM:
                  UpdateReadyFlag(m_rrmReady);
                  break;

               case ENTITY_IU:
                  UpdateReadyFlag(m_iuReady);
                  break;

               case ENTITY_OAM:
                  UpdateReadyFlag(m_oamReady);
                  SendRequestStartRsp(ENTITY_OAM);
                  break;

               case ENTITY_SW_UPDATE:
                  UpdateReadyFlag(m_swUpdateReady);
                  SendRequestStartRsp(ENTITY_SW_UPDATE);
                  break;

               case ENTITY_CPHY:
                  UpdateReadyFlag(m_cphyReady);
                  break;

               case ENTITY_PS_USER_PLANE:
                  UpdateReadyFlag(m_psUserPlaneReady);
                  break;

               case ENTITY_CS_USER_PLANE:
                  UpdateReadyFlag(m_csUserPlaneReady);
                  break;

               case ENTITY_GGSN:
                  UpdateReadyFlag(m_ggsnReady);
                  break;

               case ENTITY_TENPIN:
                  UpdateReadyFlag(m_tenpinReady);
                  SendRequestStartRsp(ENTITY_TENPIN);
                  break;

               case ENTITY_SERVICE_API:
                  UpdateReadyFlag(m_sapiReady);
                  break;

               case ENTITY_SM:
                  UpdateReadyFlag(m_smReady);
                  break;

#ifdef LTE_REM
               case ENTITY_OAM_REM:
                  SendRequestStartRsp(ENTITY_OAM_REM);
                  SendRemScanReq();
                  break;
#endif

               default:
                  TRACE_PRINTF("Entity %s notified as ready - queueing", MessagingEntityToString(message->GetFromEntity()));
                  // add to list of other entities to start when system is ready to go, check for duplicates first though
                  std::vector<MessagingEntity>:: iterator it = find(m_otherEntitiesToStart.begin(), m_otherEntitiesToStart.end(), message->GetFromEntity());
                  if (it == m_otherEntitiesToStart.end())
                  {
                     // not already in the list so add it
                     m_otherEntitiesToStart.push_back(message->GetFromEntity());
                  }
                  break;
            }
         }
         break;

      case SERIALISATION_ID_CPHY_NODEB_TX_ENABLE_CNF:
         {
            shared_ptr<CPhyNodeBTxEnableCnf> msg = Serialisable::DeSerialise<CPhyNodeBTxEnableCnf>(message);
            TRACE("OamUserApplication: CPhyNodeBTxEnableCnf received", msg->ToString());
         }
         break;

      case SERIALISATION_ID_CPHY_NODEB_STAT_IND:
         {
            shared_ptr<CPhyNodeBStatInd> msg = Serialisable::DeSerialise<CPhyNodeBStatInd>(message);
            //TRACE_MSG(msg->ToString().c_str());
            if(countErrors)
            {
               accFrameCount += msg->GetFrameCount();
               accBitErrors += msg->GetBerErr();
               accBitCount += msg->GetBerCount();
               for(u8 i = 0; i < NUM_CPHY_STAT_CHAN_DCH; i++)
               {
                  accBlockErrorCount[i] += msg->GetDchErr(i);
                  accBlockCount[i] += msg->GetDchCount(i);
               }
            }
         }
         break;

      case SERIALISATION_ID_REM_SCAN_CNF:
         {
            shared_ptr<RemScanCnf> remScanCnf = Serialisable::DeSerialise<RemScanCnf>(message);
            RSYS_ASSERT(remScanCnf != NULL);

            //received rem scan cnf, now send a request to GSM Rem subentity to commence the GSM rem scan.

            if(remScanCnf->GetRemResult() == REM_SCAN_RESULT_PASSED)
            {
               MibAttributeValues attrs;
               attrs.AddAttribute(PARAM_ID_REM_SCAN_RESULT, ((u32)REM_SCAN_RESULT_PASSED));
               GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);
               // No need to go via FSM as this is just part of the full scan sequence.
            }
            else
            {
               // Oops, REM scan failed (because configuring h/w failed, one reason being lack
               // of configuration).  This will have been reported through op state inform mechanism.
               m_fsm.InjectConfigurationComplete(NULL);
            }
         }
         break;

      case SERIALISATION_ID_GSM_REM_SCAN_CNF:
         {
            //GSM rem scan has now completed
            TRACE_MSG("Received SERIALISATION_ID_GSM_REM_SCAN_CNF");

            m_fsm.InjectConfigurationComplete(NULL);
         }
         break;

      case SERIALISATION_ID_CPHY_MODE_CHANGE_CNF:
         {
            shared_ptr<CPhyModeChangeCnf> msg = Serialisable::DeSerialise<CPhyModeChangeCnf>(message);
            TRACE("OamUserApplication: CPhyModeChangeCnf received", msg->ToString());
            if(msg->GetMode() == L1_MODE_NODEB)
            {
               TRACE_MSG("L1L2 is in NodeB State");
               FapMO::GetInstance().SetL1L2InNodeBState(true);
            }
            else
            {
               TRACE_MSG("L1L2 is NOT in NodeB State");
               FapMO::GetInstance().SetL1L2InNodeBState(false);
            }
         }
         break;

      case SERIALISATION_ID_MIB_SET_ATTRIBUTES_CNF:
         {
            shared_ptr<MibSetAttributesCnf> msg = Serialisable::DeSerialise<MibSetAttributesCnf>(message);
            TRACE("OamUserApplication: MibSetAttributesCnf received", msg->ToString());
         }
         break;

      case SERIALISATION_ID_ALARM_EVENT:
         {
            // Can't use the funky template here, we have special deserialisation requirements
            // as we have to get the correct alarm ID object into AlarmEvent first.
            shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::INVALID));
            AlarmEvent alarmEvent;
            alarmEvent.SetAlarmId(alarmId);

            // Should always deserialise successfully.
            bool deserialiseSuccess = alarmEvent.DeSerialise(message->GetSerialData(), message->GetSerialDataLength());
            RSYS_ASSERT(deserialiseSuccess);

            if(m_stuckAlarmCleared == false)
            {
               GetAlarmMgr().ClearAlarmsLeftSetOverReboot();
               m_stuckAlarmCleared = true;
            }
            GetAlarmMgr().HandleAlarmEvent(alarmEvent);
         }
         break;

      case SERIALISATION_ID_KPI_CONFIGURE_REQ:
         {
            shared_ptr<KpiConfigureReq> msg = Serialisable::DeSerialise<KpiConfigureReq>(message);
            RSYS_ASSERT(msg != NULL);
            GetKpiMgr().ConfigureMeasurements(message->GetFromEntity(), *msg);
         }
         break;

      case SERIALISATION_ID_KPI_REGISTER_REQ:
         {
            shared_ptr<KpiRegisterReq> msg = Serialisable::DeSerialise<KpiRegisterReq>(message);
            RSYS_ASSERT(msg != NULL);
            GetKpiMgr().RegisterKpiEntities(message->GetFromEntity(), msg->GetKpiGroupIds());
         }
         break;

      case SERIALISATION_ID_KPI_READ_CNF:
         {
            KpiManager& kpiManager = GetKpiMgr();
            if(kpiManager.isCollectionReqPending())
            {
               //Need not deserilalise the message as it just indicates the completion of read request processing by messaging entity.
               //So inform arrival of this message to KpiManager and return.
               kpiManager.sendUploadRequest(message->GetFromEntity());
               return;
            }

            //Read CNF is rceived because of exection of pollkpis command through CLI.So deserialise this message  and write its content to trace file.
            shared_ptr<KpiReadCnf> msg = Serialisable::DeSerialise<KpiReadCnf>(message);
            RSYS_ASSERT(msg != NULL);
            TRACE_PRINTF_LEV(TRACE_INFO, "%-13s KPIs [%s]: %s",
                  MessagingEntityToString(message->GetFromEntity()),
                  (msg->GetKpiMeasurementSet() == KpiManager::KPI_MEASUREMENT_SET_INTERVAL ? "interval" : "noreset" ),
                  msg->ToString().c_str());
         }
         break;

         //if it receives one of these, it is a bug - these should go to the MIB!
      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_REQ:
      case SERIALISATION_ID_MIB_UNSUBSCRIBE_REQ:
      case SERIALISATION_ID_MIB_SET_ATTRIBUTES_REQ:
      case SERIALISATION_ID_MIB_GET_ATTRIBUTES_REQ:
         RSYS_ASSERT_PRINTF(false, "Message of type 0x%x has been sent to OAM instead of the MIB", (u32)serialisationId);
         break;

#if 0
      case SERIALISATION_ID_CARB_TEMPERATURE_CNF:
         {
            shared_ptr<CarbTemperatureCnf> carbTemperatureCnf = Serialisable::DeSerialise<CarbTemperatureCnf>(message);
            RSYS_ASSERT(carbTemperatureCnf != NULL);
            TRACE("Measured Temperatures", carbTemperatureCnf->ToString());

            // Record this value in our temperature monitor.  Will send alarm if necessary.
            m_tempMonitor.SetNewBoardTemperature(carbTemperatureCnf->GetBoardTemp());
         }
         break;
#endif
      case SERIALISATION_ID_CPHY_HW_CONFIG_CNF:
         {
            shared_ptr<CPhyHwConfigCnf> hwConfigCnf = Serialisable::DeSerialise<CPhyHwConfigCnf>(message);
            RSYS_ASSERT(hwConfigCnf != NULL);

            if(hwConfigCnf->GetStatus() == L1_SOK)
            {
               // Hardware configured successfully, tell OAM.
               MfOpStateInformInd opStateInform(MF_HW_CONFIG, ManagedObject::OP_STATE_ENABLED, 0, "");
               SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM);
            }
            else
            {
               // Hardware configuration failed.  Oh dear.  No calibration?
               TRACE_LEV(TRACE_CRITICAL, "Hardware configuration failed.", hwConfigCnf->ToString());

               // Update op state so we don't transmit.
               MfOpStateInformInd opStateInform(MF_HW_CONFIG, ManagedObject::OP_STATE_DISABLED, 0,
                     "Hardware configuration failed.  No calibration data?");
               SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM);

               // Raise an alarm.
               shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::PHY_CONFIGURATION_FAILURE));
               string additionalInfo("Hardware (PHY) configuration failed.  No radio calibration?  Hardware incompatibility?");
               AlarmEvent phyFailureAlarm(alarmId,
                     AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                     AlarmEvent::ALARM_SEVERITY_CRITICAL,
                     additionalInfo,
                     AlarmEvent::ALARM_TYPE_EQUIPMENT);
               SendMessage(phyFailureAlarm, ENTITY_OAM, ENTITY_OAM);
            }
         }
         break;

#ifdef LTE_REM
      case SERIALISATION_ID_REM_SCAN_REQ:
         {
            u32 RemScanEnabled = 0;
            MibHelper::GetMibAttributeDirect(PARAM_ID_REM_SCAN_ENABLE, RemScanEnabled);
            TRACE_PRINTF("Value of PARAM_ID_REM_SCAN_ENABLE is %d\n",RemScanEnabled);
            if (RemScanEnabled)
               TriggerFullRemScan();
            else
               RemScanDisabled(message);
         }
         break;

      case SERIALISATION_ID_REM_OAM_ABORT_SCAN:
         {
            SendAbortRemScanReq();
         }
         break;

      case SERIALISATION_ID_REM_SCAN_STATUS:
         {
            TRACE_PRINTF("Rem Scan Status Received");
            shared_ptr<CRemScanStatus> oRemScanStatus = Serialisable::DeSerialise<CRemScanStatus>(message);
            RSYS_ASSERT(oRemScanStatus != NULL);
            MibAttributeValues attrs;
            TimeWrap now;

            if(RAT_LTE == oRemScanStatus->getScanType())
            {
               TRACE_PRINTF("Rem Scan Status for LTE_RAT");
               u32 status = (u32)oRemScanStatus->getScanStatus();
               attrs.AddAttribute(PARAM_ID_LTE_REM_SCAN_STATUS, GetStatusAsString(status));
               attrs.AddAttribute(PARAM_ID_LTE_ERROR_DETAILS, oRemScanStatus->getErrString());
               attrs.AddAttribute(PARAM_ID_LTE_LAST_REM_SCAN_TIME, now.ToString() );
               m_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE), attrs);
            }
            else
            {
               TRACE_PRINTF("Rem Scan Status for 3G_RAT");
               u32 status = (u32)oRemScanStatus->getScanStatus();
               attrs.AddAttribute(PARAM_ID_WCDMA_REM_SCAN_STATUS, GetStatusAsString(status));
               attrs.AddAttribute(PARAM_ID_ERROR_DETAILS, oRemScanStatus->getErrString());
               attrs.AddAttribute(PARAM_ID_WCDMA_LAST_REM_SCAN_TIME, now.ToString() );
               m_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA), attrs);
            }
            m_fsm.InjectConfigurationComplete(NULL);
         }
         break;
#endif

      case SERIALISATION_ID_EVENT_NOTIFY:
         {
            TRACE_PRINTF("EVENT_NOTIFY Received to OAM");
            GetKpiMgr().SendPollKpis();
         }
         break;
      default:
         TRACE_LEV(TRACE_WARNING, "ENTITY_OAM Unhandled Signal received", SerialisationIdToString(serialisationId));
         break;
   }
}

void OamUserApplication::HandleOpStateInformMessage(shared_ptr<threeway::MessageSerialisedData> message)
{
   shared_ptr<MfOpStateInformInd> opStateInform = Serialisable::DeSerialise<MfOpStateInformInd>(message);
   RSYS_ASSERT(opStateInform != NULL);

   TRACE_PRINTF("Received MfOpStateInformInd message from %s: %s",
         MessagingEntityToString(message->GetFromEntity()),
         opStateInform->ToString().c_str());

   m_mfManager.RegisterMf(opStateInform->GetManagedFing(), message->GetFromEntity()); // Later this may be done by a separate MfRegisterInf message
   if(opStateInform->IsAdminStatePresent())
   {
      m_mfManager.UpdateMfOpState(opStateInform->GetManagedFing(),
            opStateInform->GetOpState(),
            opStateInform->GetAdminState(),
            opStateInform->GetAdditionalInfoString());
   }
   else
   {
      m_mfManager.UpdateMfOpState(opStateInform->GetManagedFing(),
            opStateInform->GetOpState(),
            opStateInform->GetAdditionalInfoString());
   }

   switch (opStateInform->GetManagedFing())
   {
#if 0
      case MF_RANAP:
         {
            MibAttributeId domainAttrId = PARAM_ID_FAP_OP_STATE_CS_UP;

            // Set Iu state on the FAP MO.
            if((DomainIdent)(opStateInform->GetAdditionalInfoValue()) == CS_DOMAIN)
            {
               FapMO::GetInstance().SetIuCsEnabled(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
               domainAttrId = PARAM_ID_FAP_OP_STATE_CS_UP;
            }
            else
            {
               FapMO::GetInstance().SetIuPsEnabled(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
               domainAttrId = PARAM_ID_FAP_OP_STATE_PS_UP;
            }

            // update the domain op state params to trigger rebuilding of SIB1
            MibAttributeValues attrs;
            u32 domainOpState = 0;
            if (opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED)
            {
               domainOpState = 1;
            }
            attrs.AddAttribute(domainAttrId, domainOpState);
            GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);
         }
         break;
#endif
      case MF_TR069:
         FapMO::GetInstance().SetTr069Enabled(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
         break;

      case MF_SM:
         if(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED)
         {
            FapMO::GetInstance().SetSmEnabled(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
         }
         else
         {
            if(TRUE == oam_act_reboot)
            {
               OamActionCnf oamActionCnf(ENTITY_TR069, OAM_ACTION_REBOOT, 0);
               TRACE_MSG("Sending OamActionCnf");
               bool reply = SendMessage(oamActionCnf, ENTITY_TR069, ENTITY_OAM);
               if(!reply)
               {
                  TRACE_MSG("Sending OamActionCnf failed!");
               }

               ostringstream command;
               command <<"reboot";
               TRACE_PRINTF("Reboot Command : %s", command.str().c_str());

               MibAttributeValues attrRebootStatus;
               attrRebootStatus.AddAttribute(PARAM_ID_LTE_REBOOT_STATUS, true);
               GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),attrRebootStatus, ENTITY_OAM);
               if(system(command.str().c_str()) != oam_ret_zero)
               {
                  TRACE_MSG("OamUserApplication::HandleOamActionReq, Reboot command Failed");
               }
            }
         }
         break;

      case MF_IKE:
         FapMO::GetInstance().SetNetworkEnabled(true);
         break;

      case MF_RADIO:
         // "Radio" reports its op state through state of OAM FSM.
         // Nothing more for us to do here.  Has already been used to update LEDs.
         break;

      case MF_FREQUENCY_OFFSET:
         FapMO::GetInstance().SetFreqSyncEnabled(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
         break;

      case MF_TEMPERATURE_MONITOR:
         FapMO::GetInstance().SetFapIsOverTemperature(opStateInform->GetOpState() == ManagedObject::OP_STATE_DISABLED);
         break;

      case MF_HW_CONFIG:
         FapMO::GetInstance().SetHwConfiguredOk(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
         break;

      case MF_SCTP:
         FapMO::GetInstance().SetSctpEnabled(opStateInform->GetOpState() == ManagedObject::OP_STATE_ENABLED);
         break;

      case MF_UMTS_STACK: /* FALLTHRU */
      case MF_RRC:        /* FALLTHRU */
      case MF_RRM:        /* FALLTHRU */
         // TODO
         break;

      case MF_ETH0:
      case MF_IPSEC_TUNNEL:
      case MF_SW_UPDATE:
      case MF_REM_SCAN:
      case MF_CS_USER_PLANE:
      case MF_INVALID:
         // Nothing to do...
         break;

      default:
         break;
   }
   InjectOpStateIntoFsm();
}

void OamUserApplication::UpdateReadyFlag(bool& flag)
{
   if(!flag)
   {
      //ensure we don't start everything up twice if there are multiple ready signals (possible).
      flag = true;
      ProcessEntityReadyStatesAndFireEmUpIfAllStarted();
   }
}

void OamUserApplication::InjectOpStateIntoFsm()
{
   TRACE_PRINTF("FAP MO: %s", FapMO::GetInstance().ToString().c_str());

   if(FapMO::GetInstance().GetOpState() == ManagedObject::OP_STATE_ENABLED)
   {
   }
   else
   {
   }
}

void OamUserApplication::StartTr069()
{
   int assertNumber = 0;

   // TODO: Wrap up as a method
   FILE * assertionFailureLog = fopen(Trace::GetInstance().GetAssertionFailureLogFilename(), "r");
   if(assertionFailureLog)
   {
      char oneLineFromLog[2048 + 1];
      while( fgets( &oneLineFromLog[0], sizeof(oneLineFromLog)-1, assertionFailureLog) )
      {
         assertNumber++;

         char * p= &oneLineFromLog[0];

         while(*p)
         {
            if(*p == '\n') *p = '~';
            p++;
         }

         fprintf(stderr, "LoggedAssertionFailure(%i):\"%s\"\n", assertNumber, oneLineFromLog);
         shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::LOGGED_ASSERTION_FAILURE));
         AlarmEvent alarmEvent(alarmId,
               AlarmEvent::ALARM_EVENT_TRANSIENT,
               AlarmEvent::ALARM_SEVERITY_WARNING,
               oneLineFromLog,
               AlarmEvent::ALARM_TYPE_PROCESSING);

         GetAlarmMgr().HandleAlarmEvent(alarmEvent);
      }
      assertionFailureLog = freopen(Trace::GetInstance().GetAssertionFailureLogFilename(),"w",assertionFailureLog);
      if(assertionFailureLog)
      {
         fclose(assertionFailureLog);
      }
   }
   SendRequestStartRsp(ENTITY_TR069);

   //Check for bootStrapStatus, if set collect results and upload PM XML file
   u32 bootStrapStatus;
   MibHelper::GetMibAttributeDirect(PARAM_ID_HMS_BOOTSTRAP_COMPLETED, bootStrapStatus);
   m_kpiMgr->SendKpiCollecReqNow(bootStrapStatus);
}

void OamUserApplication::ProcessEntityReadyStatesAndFireEmUpIfAllStarted()
{
   bool go = false;
   // Now do all the start up stuff.
   std::ostringstream output;
   output << "ProcessEntityReadyStatesAndFireEmUpIfAllStarted:" <<
      " iu=" << m_iuReady <<
      " oam=" << m_oamReady <<
      " sm=" << m_smReady <<
      " sw-update=" << m_swUpdateReady <<
      " tr069=" << m_tr069Ready <<
      " rrc=" << m_rrcReady <<
      " rrm=" << m_rrmReady <<
      " cphy=" << m_cphyReady <<
      " ps-user-plane=" << m_psUserPlaneReady <<
      " cs-user-plane=" << m_csUserPlaneReady <<
      " ggsn=" << m_ggsnReady <<
      " tenpin=" << m_tenpinReady <<
      " service-api=" << m_sapiReady;
   TRACE("StartupStates", output.str());

   // First check the generic apps, then secondarily check the relevant build-specific apps
   if(  m_oamReady && m_smReady /*m_cphyReady && m_oamReady && m_swUpdateReady && m_rrcReady && m_rrmReady*/)
   {
      if(oamEnv_isProductHbs2Iu())
      {
         if(m_tenpinReady && m_tr069Ready)
         {
            go = true;
         }
         else /*This would be needed as we are doing testing without TENPIN*/
         {
            go = true;
         }

      }
      else if(oamEnv_isProductHbs2Sip())
      {
         if(m_csUserPlaneReady && m_ggsnReady)
         {
            go = true;
         }
      }
      else if(oamEnv_isProductHbs2Factory())
      {
         if(m_csUserPlaneReady && m_ggsnReady && m_tenpinReady)
         {
            go = true;
         }
      }
      else if(oamEnv_isProductHbs2Rrc())
      {
         go = true;
      }
      else
      {
         go = true;
      }

      if(go == true)
      {
         TRACE_MSG("ProcessEntityReadyStatesAndFireEmUpIfAllStarted: All Apps Started Up");
         m_fsm.InjectAppsReady(NULL);
      }
   }

   // This message is temporary until we have a proper ETH0 'Managed Fing'.
   // We can assume ETH0 is up and working by this point so just send a message to reflect this.
   MfOpStateInformInd opStateInform(MF_ETH0, ManagedObject::OP_STATE_ENABLED, 0, "IP Interface Configured");
   SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM_HW);
}

void OamUserApplication::HandleMibMessage(shared_ptr<threeway::MessageSerialisedData> message)
{
   SerialisationId serialisationId = (SerialisationId)message->GetSerialisationId();

   switch (serialisationId)
   {
      case SERIALISATION_ID_MIB_CREATE_OBJECT_REQ:
         {
            // Recover the message.
            shared_ptr<MibCreateObjectReq> mibCreateObjectReq = Serialisable::DeSerialise<MibCreateObjectReq>(message);
            RSYS_ASSERT(mibCreateObjectReq != NULL);

            m_mibManager->CreateObject(mibCreateObjectReq->GetParentDn(),
                  mibCreateObjectReq->GetChildRdn(),
                  mibCreateObjectReq->GetChildMibAttributeValues());

            // Send confirm
            MibDN newObjectDn(mibCreateObjectReq->GetParentDn());
            newObjectDn.push_back(mibCreateObjectReq->GetChildRdn());
            MibCreateObjectCnf mibCreateObjectCnf(newObjectDn);
            SendMessage(mibCreateObjectCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      case SERIALISATION_ID_MIB_DELETE_OBJECT_REQ:
         {
            // Recover the message.
            shared_ptr<MibDeleteObjectReq> mibDeleteObjectReq = Serialisable::DeSerialise<MibDeleteObjectReq>(message);
            RSYS_ASSERT(mibDeleteObjectReq != NULL);
            MibObjectDeleteResult deletionResult = MIB_OBJ_DEL_INVALID; 
            deletionResult = m_mibManager->DeleteObject(mibDeleteObjectReq->GetDn());
            if(deletionResult == MIB_OBJ_DEL_SUCCESS)
            {
               ValidationReferences::GetInstance().DeleteDnFromMap(mibDeleteObjectReq->GetDn());
            }
            if(strstr(mibDeleteObjectReq->GetDn().ToString().c_str(),"LTE_RAN_NEIGH_LIST_LTE_CELL"))
            {
               deletionResult = MIB_OBJ_DEL_SUCCESS;
            }
            MibDeleteObjectCnf mibDeleteObjectCnf(mibDeleteObjectReq->GetDn(), deletionResult);
            SendMessage(mibDeleteObjectCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_REQ:
         {
            // Recover the message.
            shared_ptr<MibSubscribeAttributesReq> mibSubscribeAttributesReq = Serialisable::DeSerialise<MibSubscribeAttributesReq>(message);
            RSYS_ASSERT(mibSubscribeAttributesReq != NULL);

            // Add subscription.  Will send a notification if MIB currently has values.
            m_mibManager->AddSubscription((u32)message->GetFromEntity(),
                  MessagingEntityToString(message->GetFromEntity()),
                  mibSubscribeAttributesReq->GetSubscriptionId(),
                  mibSubscribeAttributesReq->GetMibAttributeIdsByDn(),
                  mibSubscribeAttributesReq->GetMibObjectClassesByDn() );

            // Send confirm after the values so receiving apps know they have the current values
            MibSubscribeAttributesCnf mibSubscribeAttributesCnf(mibSubscribeAttributesReq->GetSubscriptionId());
            SendMessage(mibSubscribeAttributesCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      case SERIALISATION_ID_MIB_UNSUBSCRIBE_REQ:
         {
            // Recover the message.
            shared_ptr<MibUnsubscribeReq> mibUnsubscribeReq = Serialisable::DeSerialise<MibUnsubscribeReq>(message);
            RSYS_ASSERT(mibUnsubscribeReq != NULL);

            TRACE("Received MibUnsubscribeReq", mibUnsubscribeReq->ToString());

            // Remove subscription.
            m_mibManager->RemoveSubscription((u32)message->GetFromEntity(),
                  mibUnsubscribeReq->GetSubscriptionId());

            MibUnsubscribeCnf mibUnsubscribeCnf(mibUnsubscribeReq->GetSubscriptionId());
            SendMessage(mibUnsubscribeCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      case SERIALISATION_ID_MIB_VALIDATE_ATTRIBUTES_REQ:
         {
            // Recover the message.
            shared_ptr<MibValidateAttributesReq> mibValidateAttributesReq = Serialisable::DeSerialise<MibValidateAttributesReq>(message);
            RSYS_ASSERT(mibValidateAttributesReq != NULL);

            TRACE("Received MibValidateAttributesReq", mibValidateAttributesReq->ToString());

            MibValidateAttributesCnf mibValidateAttributesCnf;

            // Set the mib params.
            // TODO: Make this a transaction across all DNs.
            vector<MibDN> dnList = mibValidateAttributesReq->GetDnList();
            for(u32 i = 0; i < dnList.size(); i++)
            {
               const MibAttributeValues& attrValues = mibValidateAttributesReq->GetMibAttributeValues(dnList[i]);
               MibAttrValidationFailures failures = m_mibManager->ValidateAttributes(dnList[i], attrValues);
               if(failures.size() > 0)
               {
                  mibValidateAttributesCnf.AddFailures(dnList[i], failures);
               }
            }

            // Send confirm.
            SendMessage(mibValidateAttributesCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      case SERIALISATION_ID_MIB_SET_ATTRIBUTES_REQ:
         {
            // Recover the message.
            shared_ptr<MibSetAttributesReq> mibSetAttributesReq = Serialisable::DeSerialise<MibSetAttributesReq>(message);
            RSYS_ASSERT(mibSetAttributesReq != NULL);

            TRACE("Received MibSetAttributesReq", mibSetAttributesReq->ToString());

            // Set the mib params.
            // TODO: Make this a transaction across all DNs.
            vector<MibDN> dnList = mibSetAttributesReq->GetDnList();
            for(u32 i = 0; i < dnList.size(); i++)
            {
               HandleMIOdn(dnList[i]);
               const MibAttributeValues& attrValues = mibSetAttributesReq->GetMibAttributeValues(dnList[i]);
               checkForSONParameters(attrValues);
               m_mibManager->SetAttributes(dnList[i], attrValues);
            }

            // Send confirm.
            MibSetAttributesCnf mibSetAttributesCnf;
            SendMessage(mibSetAttributesCnf, message->GetFromEntity(), ENTITY_MIB);
            //HandleCsgParam(mibSetAttributesReq->ToString());
            HandleGERANPmaxParam(mibSetAttributesReq->ToString());
            HandleGERANSpeedScaleParam(mibSetAttributesReq->ToString());
            HandleNetCntrlOrdrParam(mibSetAttributesReq->ToString());
         }
         break;

      case SERIALISATION_ID_MIB_GET_ATTRIBUTES_REQ:
         {
            // Recover the message.
            shared_ptr<MibGetAttributesReq> mibGetAttributesReq = Serialisable::DeSerialise<MibGetAttributesReq>(message);
            RSYS_ASSERT(mibGetAttributesReq != NULL);

            TRACE("Received MibGetAttributesReq", mibGetAttributesReq->ToString());

            // Prepare a confirm.
            MibGetAttributesCnf mibGetAttributesCnf;

            // Work our way through the DNs in the request.
            vector<MibDN> dnList = mibGetAttributesReq->GetMibAttributeIdsByDn().GetDnList();
            for(u32 i = 0; i < dnList.size(); i++)
            {
               MibAttributeValues dnAttrValues;

               // Get the list of IDs for this DN.
               const MibAttributeIds& attrIds = mibGetAttributesReq->GetMibAttributeIds(dnList[i]);

               // Get the values for this DN.
               m_mibManager->GetAttributes(dnList[i], attrIds, dnAttrValues);

               // Add values for this DN to the confirm.
               mibGetAttributesCnf.AddAttributes(dnList[i], dnAttrValues);
            }

            // Send confirm.
            SendMessage(mibGetAttributesCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      case SERIALISATION_ID_MIB_DELETE_ATTRIBUTES_REQ:
         {
            // Recover the message.
            shared_ptr<MibDeleteAttributesReq> mibDeleteAttributesReq = Serialisable::DeSerialise<MibDeleteAttributesReq>(message);
            RSYS_ASSERT(mibDeleteAttributesReq != NULL);

            TRACE("Received MibDeleteAttributesReq", mibDeleteAttributesReq->ToString());

            // Prepare a confirm.
            MibDeleteAttributesCnf mibDeleteAttributesCnf;

            // Work our way through the DNs in the request.
            vector<MibDN> dnList = mibDeleteAttributesReq->GetMibAttributeIdsByDn().GetDnList();
            for(u32 i = 0; i < dnList.size(); i++)
            {
               // Get the list of IDs for this DN.
               const MibAttributeIds& attrIds = mibDeleteAttributesReq->GetMibAttributeIds(dnList[i]);

               // Get the values for this DN.
               m_mibManager->DeleteAttributes(dnList[i], attrIds);
            }

            // Send confirm.
            SendMessage(mibDeleteAttributesCnf, message->GetFromEntity(), ENTITY_MIB);
         }
         break;

      default:
         TRACE_LEV(TRACE_WARNING, "ENTITY_MIB Unhandled Signal received", SerialisationIdToString(serialisationId));
         break;
   }
}

/**
 * Checks if the SON feature related parameters are configured
 * and sets LTE_SON_CONF_PRESENCE accordingly.
 */
void OamUserApplication::checkForSONParameters(const MibAttributeValues& attrs)
{
   MibAttributeIds attrIds = attrs.GetAttributeIds();
   std::set<MibAttributeId>::iterator attrIdIter;
   u32 SONParamsPres;
   MibHelper::GetMibAttributeDirect(PARAM_ID_LTE_SON_CONF_PRESENCE, SONParamsPres);

   if( attrIds.find( PARAM_ID_LTE_EARFCNDL_LIST ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_EARFCNDL_LIST_CONFIGURED;
   }
   if( attrIds.find( PARAM_ID_LTE_EARFCNUL_LIST ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_EARFCNUL_LIST_CONFIGURED;
   }
   if( attrIds.find( PARAM_ID_LTE_PRACH_ROOT_SEQUENCE_INDEX_LIST ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_ROOT_SEQUENCE_INDEX_LIST_CONFIGURED;
   }
   if( attrIds.find( PARAM_ID_LTE_PRACH_CONFIG_INDEX_LIST ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_CONFIG_INDEX_LIST_CONFIGURED;
   }
   if( attrIds.find( PARAM_ID_LTE_PRACH_ZERO_CORRELATIONZONE_CONFIG_LIST ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_ZERO_CORRELATIONZONE_CONFIG_LIST_CONFIGURED;
   }
   if( attrIds.find( PARAM_ID_LTE_PRACH_FREQ_OFFSET_LIST ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_FREQ_OFFSET_LIST_CONFIGURED;
   }

   if( attrIds.find( PARAM_ID_LTE_REFERNCE_SIG_POWER ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_LTE_PDSCH_CONFIG_COMMON_CONFIGURED;
   }

   if( attrIds.find( PARAM_ID_LTE_PB ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_LTE_PDSCH_CONFIG_COMMON_CONFIGURED;
   }

   if( attrIds.find( PARAM_ID_LTE_PA ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_LTE_PDSCH_CONFIG_DEDICATED_CONFIGURED   ;
   }

   if( attrIds.find( PARAM_ID_LTE_PSCH_POWER_OFFSET) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_LTE_POWER_OFFSET_CONFIGURED;
   }
   if( attrIds.find( PARAM_ID_LTE_SSCH_POWER_OFFSET ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_LTE_POWER_OFFSET_CONFIGURED;
   }

   if( attrIds.find( PARAM_ID_LTE_PBCH_POWER_OFFSET ) != attrIds.end() )
   {
      SONParamsPres |= ManagedObject::SON_LTE_POWER_OFFSET_CONFIGURED;
   }
   MibAttributeValues attrVal;
   attrVal.AddAttribute(PARAM_ID_LTE_SON_CONF_PRESENCE, SONParamsPres);
   m_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),attrVal);
}
void OamUserApplication::StartNtpTimer(u32 timeoutPeriod)
{
   if(IsTimerRunning(m_ntpTimerHandle))
   {
      DeleteTimer(m_ntpTimerHandle);
   }
   m_ntpTimerHandle = CreateTimer((const std::string&)"NTP expiration timeout", timeoutPeriod, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_SINGLE_SHOT);
}

#if 0
void OamUserApplication::StartFreqSyncExpiryTimer(u32 timeoutPeriod)
{
   if(IsTimerRunning(m_freqSyncExpiredTimerHandle))
   {
      DeleteTimer(m_freqSyncExpiredTimerHandle);
   }

   m_freqSyncExpiredTimerHandle = CreateTimer((const std::string&)"Frequency Sync expiration timeout", timeoutPeriod, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void OamUserApplication::StartFreqSyncActivityNotificationTimer(u32 timeoutPeriod)
{
   if(IsTimerRunning(m_freqSyncActivityNotificationTimerHandle))
   {
      DeleteTimer(m_freqSyncActivityNotificationTimerHandle);
   }

   m_freqSyncActivityNotificationTimerHandle = CreateTimer((const std::string&)"Frequency Sync activity notification timeout", timeoutPeriod, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void OamUserApplication::StartFreqSyncCallbackTimer(u32 timeoutPeriod)
{
   if(IsTimerRunning(m_freqSyncCallbackTimerHandle))
   {
      DeleteTimer(m_freqSyncCallbackTimerHandle);
   }

   m_freqSyncCallbackTimerHandle = CreateTimer((const std::string&)"Frequency Sync TFCS Callback timeout", timeoutPeriod, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void OamUserApplication::StopFreqSyncCallbackTimer()
{
   if(IsTimerRunning(m_freqSyncCallbackTimerHandle))
   {
      DeleteTimer(m_freqSyncCallbackTimerHandle);
   }
}
#endif

void OamUserApplication::HandleNtpParams()
{
   TRACE_PRINTF("%s\n",__FUNCTION__);

   bool enable;
   string ntp_server[5], ntpstatus, dfltNtpServer; 
   int  ret = 0,ntpipcount=0,ntpDncount=0;
   u32 ntpTimer;
   IPv4Address ntp_ip[5], dfltNtpIp;
   u32 sigip[5] = {0};
   u32 ntpIp = 0;
   char ipbuf[100] = {0};
   string NtpDn[5];
   u32 sendNtpReq = FALSE;
   bool ntpflag = false;

   if(OamUserApplication::GetInstance().GetMibCache().IsMibAttributePresent(PARAM_ID_NTP_ENABLE))
   {
      GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_NTP_ENABLE, enable);

      if(enable)
      {
         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_NTP_SERVER_1,NtpDn[ntpDncount]);
         ntp_server[ntpipcount++] = FqdnToIp(NtpDn[ntpDncount++]);

         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_NTP_SERVER_2,NtpDn[ntpDncount]);
         ntp_server[ntpipcount++] = FqdnToIp(NtpDn[ntpDncount++]);

         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_NTP_SERVER_3,NtpDn[ntpDncount]);
         ntp_server[ntpipcount++] = FqdnToIp(NtpDn[ntpDncount++]);

         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_NTP_SERVER_4,NtpDn[ntpDncount]);
         ntp_server[ntpipcount++] = FqdnToIp(NtpDn[ntpDncount++]);

         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_NTP_SERVER_5,NtpDn[ntpDncount]);
         ntp_server[ntpipcount] = FqdnToIp(NtpDn[ntpDncount]);

         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_X_RADISYS_NTP_SYNC_INTERVAL,ntpTimer);

         GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_DEFAULT_NTP_SERVER, dfltNtpServer);
         dfltNtpIp = IPv4Address(dfltNtpServer.c_str());
         ntpIp = htonl(dfltNtpIp.Get());

         for(int count = 0 ;count <= ntpipcount;count ++)
         {
             if((ntp_server[count] != "")&&!strcmp(ntp_server[count].c_str(),"0.0.0.0"))
             {
                  ntpflag = true;
                  break;
             }
         }
         
         if(ntpflag)
         {
            ntp_ip[ntpipcount] = IPv4Address(ntp_server[ntpipcount].c_str());
            sigip[ntpipcount] = htonl(ntp_ip[ntpipcount].Get());
            ntpipcount--;
            ntp_ip[ntpipcount] = IPv4Address(ntp_server[ntpipcount].c_str());
            sigip[ntpipcount] = htonl(ntp_ip[ntpipcount].Get());
            ntpipcount--;
            ntp_ip[ntpipcount] = IPv4Address(ntp_server[ntpipcount].c_str());
            sigip[ntpipcount] = htonl(ntp_ip[ntpipcount].Get());
            ntpipcount--;
            ntp_ip[ntpipcount] = IPv4Address(ntp_server[ntpipcount].c_str());
            sigip[ntpipcount] = htonl(ntp_ip[ntpipcount].Get());
            ntpipcount--;
            ntp_ip[ntpipcount] = IPv4Address(ntp_server[ntpipcount].c_str());
            sigip[ntpipcount] = htonl(ntp_ip[ntpipcount].Get());

#ifdef PLATFORM_BRDCM
            sprintf(ipbuf,"%s %s %s %s %s %s","ntpdate -u",ntp_server[NTP_SERVER1].c_str(),ntp_server[NTP_SERVER2].c_str(),ntp_server[NTP_SERVER3].c_str(),ntp_server[NTP_SERVER4].c_str(),ntp_server[NTP_SERVER5].c_str());
#else 
            sprintf(ipbuf,"%s %s -p %s -p %s -p %s -p %s","ntpd -p",ntp_server[NTP_SERVER1].c_str(),ntp_server[NTP_SERVER1].c_str(),ntp_server[NTP_SERVER3].c_str(),ntp_server[NTP_SERVER4].c_str(),ntp_server[NTP_SERVER5].c_str());
#endif
            sendNtpReq = TRUE;
         }
         else if(ntpIp)
         {
#ifdef PLATFORM_BRDCM
            sprintf(ipbuf,"%s %s","ntpdate -u",dfltNtpServer.c_str());
#else
            sprintf(ipbuf,"%s %s","ntpd -p",dfltNtpServer.c_str());
#endif
            sendNtpReq = TRUE;
         }
         if(sendNtpReq)
         {
            TRACE_PRINTF("NTP Server IP configured:%s",ipbuf);

            ret = system(ipbuf);
            MibAttributeValues attrs;

            if(ret == 0)
            {
               ntpstatus = NTP_STATUS1;
               attrs.AddAttribute(PARAM_ID_NTP_STATUS, ntpstatus);

               TRACE_PRINTF("NTP STATUS %s",ntpstatus.c_str());

               GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
            }
            else
            {
               ntpstatus = NTP_STATUS2;
               attrs.AddAttribute(PARAM_ID_NTP_STATUS, ntpstatus);

               TRACE_PRINTF("NTP STATUS %s",ntpstatus.c_str());

               GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
            }
            OamUserApplication::GetInstance().StartNtpTimer(ntpTimer);
            HandleNtpCurrentTime();
         }
         else
         {
            TRACE_PRINTF("NTP Sever IP is not configured");
         }
      }
      else
      {
         MibAttributeValues attrs;
         ntpstatus = NTP_STATUS3;
         attrs.AddAttribute(PARAM_ID_NTP_STATUS,ntpstatus);

         TRACE_PRINTF("NTP STATUS %s",ntpstatus.c_str());

         GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
      }
   }
}

string FqdnToIp(string ntpDn)
{
     const char * hostname = ntpDn.c_str();
     string ipAddr = "";
     if (hostname)
     {
           TRACE_PRINTF("Resolving hostname '%s'", hostname);
           struct hostent * resolved = gethostbyname(hostname);
           if (resolved)
           {
                TRACE_PRINTF("...resolved to official hostname '%s'", resolved->h_name);
                if (AF_INET == resolved->h_addrtype)
                {
                      /* select the first address in the resolved list */
                      /* ditch the rest :) */
                      char first[32];
                      memset(first, 0, sizeof(first));
                      inet_ntop(AF_INET, resolved->h_addr_list[0], first, sizeof(first));
                      ipAddr = first;
                      TRACE_PRINTF("...resolved to IPv4 address '%s'", ipAddr.c_str());
                 }
                 else
                 {
                      TRACE_PRINTF("...failed, did not resolve to IPv4 address(es)");
                 }
           }
           else
           {
                 TRACE_PRINTF("...failed %s", hstrerror(h_errno));
           }
     }
     
     return ipAddr;
}

void OamUserApplication::HandleLogUpload()
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
      OamUserApplication::GetInstance().StartLogTimer(timer_value * 60000);
   }
   else
   {
      TRACE_PRINTF("\nLOG UPLOAD FUNCTIONALITY IS DISABLED");
   }
}

void OamUserApplication::StartLogTimer(u32 timer_value)
{
   m_logTimerHandle = CreateTimer((const std::string&)"LOG expiration timeout", timer_value ,TimerEngineInterface::TIMER_START_NOW,
         TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void OamUserApplication::HandleNtpCurrentTime()
{
   char dateStr[64];
   memset (dateStr, '\0', sizeof (dateStr));
   threeway::TimeWrap timeNow;
   timeNow.GetDateStr (dateStr, sizeof(dateStr));
   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_NTP_CURRENTLOCALTIME,dateStr);

   TRACE_PRINTF("UPDATED TIME AFTER NTP SYNC %s",dateStr);

   GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
}

void OamUserApplication::TriggerFullRemScan()
{
   TRACE_PRINTF("TriggerFullRemScan:Entry");

   m_fsm.InjectFullScanRequested(NULL); 

   TRACE_PRINTF("TriggerFullRemScan:Exit");
}

void OamUserApplication::RemScanDisabled(shared_ptr<threeway::MessageSerialisedData> message)
{
   TRACE_PRINTF("RemScanDisabled:Entry");
   RemScanCnf remScanCnf(REM_SCAN_RESULT_PASSED);
   SendMessage(remScanCnf, message->GetFromEntity(), ENTITY_OAM);

   MibAttributeValues attrs;

   u32 remScanStatus = REM_SCAN_STATUS_SUCCESS;
   TimeWrap now;
   attrs.AddAttribute(PARAM_ID_LTE_REM_SCAN_STATUS, remScanStatus );
   attrs.AddAttribute(PARAM_ID_LTE_LAST_REM_SCAN_TIME, now.ToString() );

   GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);
   TRACE_PRINTF("Sending Admin Unlock to StackManager");
   MfSetAdminStateReq req2sm(MF_SM, ManagedObject::ADMIN_STATE_UNLOCKED);
   SendMessage(req2sm, ENTITY_SM, ENTITY_OAM);
   TRACE_PRINTF("RemScanDisabled:Exit");
}

void OamUserApplication::HandleTimerExpiry(shared_ptr<TimerExpiry> timer)
{
   GetKpiMgr().HandleTimerExpiry(timer->GetTimerHandle());

   if (timer->GetTimerHandle() == m_watchdogKickTimer)
   {
      if(OamUserApplication::isWatchdogDereg == false)
      {
         WatchdogKick (getpid(),5,15);
      }
   }

   if(timer->GetTimerHandle() == m_triggerPacketTimerHandle)
   {
      return;
   }
   else if(timer->GetTimerHandle() == m_periodicRescanTimer)
   {
      TriggerFullRemScan();
      return;
   }
   else if(timer->GetTimerHandle() == m_ateIpSecTimerHandle)
   {
      return;
   }
#if 0
   else if(timer->GetTimerHandle() == m_tempReadingTimerHandle)
   {
      //Send a Temperature reading request to the CARB entity
      TRACE_MSG_LEV(TRACE_VERBOSE, "Temperature monitoring timer expired");
      CarbTemperatureReq req;
      SendMessage(req, ENTITY_CARB, ENTITY_OAM);
      return;
   }
   else if(timer->GetTimerHandle() == m_freqSyncExpiredTimerHandle)
   {
      m_freqSyncEntity.FreqSyncExpiryTimeoutHappened();
      return;
   }
   else if(timer->GetTimerHandle() == m_freqSyncActivityNotificationTimerHandle)
   {
      m_freqSyncEntity.FreqSyncActivityNotificationTimeoutHappened();
      return;
   }
   else if(timer->GetTimerHandle() == m_freqSyncCallbackTimerHandle)
   {
#ifdef QC_TFCS
      m_freqSyncEntity.FreqSyncCallbackTimeoutHappened();
#endif
      return;
   }
#endif
   else if(timer->GetTimerHandle() == m_ntpTimerHandle)
   {
      TRACE_PRINTF("NTP timer expired");
      HandleNtpParams();
   }
   else if(timer->GetTimerHandle() == m_logTimerHandle)
   {
      string logFileName[3];
      int numClosedFiles = Trace::GetInstance().GetLogFilesToUpload(logFileName);
      for(int n_uploadfile = 0;n_uploadfile < numClosedFiles;n_uploadfile++)
      {
         UploadLogReq upLogReq(logFileName[n_uploadfile]);
         SendMessage(upLogReq,ENTITY_FTP,ENTITY_OAM);
      }
      //UPLOAD APPLICATION LOG FILES
      string path = GetLogDirPath();
      DIR *dir;
      struct dirent *ent;
      if ((dir = opendir(path.c_str())) != NULL)
      {
         /* print all the files and directories within directory */
         while ((ent = readdir (dir)) != NULL)
         {
            if(strstr(ent->d_name, OamUserApplication::GetAppLogFileName().c_str()))
            {
               string fileName(ent->d_name);
               bool pstUpldOpr = false;
               UploadLogReq upLogReq(fileName,pstUpldOpr);
               SendMessage(upLogReq,ENTITY_FTP,ENTITY_OAM);
            }
         }
         closedir (dir);
      }
      HandleLogUpload();
   }
}

#if 0
void OamUserApplication::UpdateRemTimer(u32 perScanInterval, u32 periodicRemScanEnabled, u32 perScanTimeWindowDur, u32 perScanTimeWindowStart, u32 freqSyncSynced)
{
   TimeWrap now;
   u32 currentTimeOfDay = 0;

   if(freqSyncSynced)
   {
      //Stop the current timer if it's running, and restart it with new params.
      if (m_periodicRescanTimer != NULL_TIMER)
      {
         DeleteTimer(m_periodicRescanTimer);
         m_periodicRescanTimer = NULL_TIMER;
      }

      //only restart if the period is not 0
      if (periodicRemScanEnabled)
      {
         /* The units for all the timers below
          * are seconds.
          */
         const u32 day = 24 * 60 * 60;
         u32 timerRandomiser = 0;
         if(perScanTimeWindowDur)
         {
            timerRandomiser = getRandomVal() % (perScanTimeWindowDur * 60);
         }
         currentTimeOfDay = now.GetUnixTime() % day;

         TRACE_PRINTF("UpdateRemTimer: perScanInterval=%u perScanTimeWindowDur=%u perScanTimeWindowStart=%u", perScanInterval, perScanTimeWindowDur, perScanTimeWindowStart);

         //Calculate seconds till next window start and then add the time randomiser
         u32 timerDurationFirstDay  = ((day - currentTimeOfDay + perScanTimeWindowStart) % day) + timerRandomiser;
         u32 timerDurationExtraDays = (perScanInterval - 1) * day;
         u32 totalTimerDuration     = timerDurationFirstDay + timerDurationExtraDays;

         char remTimerName[32];
         snprintf (remTimerName, sizeof(remTimerName), "Periodic REM Timer[%" PRId32 "s]", totalTimerDuration);
         m_periodicRescanTimer = CreateTimer (remTimerName,
               TimerEngineInterface::SecondsToTicks(totalTimerDuration),
               TimerEngineInterface::TIMER_START_NOW,
               TimerEngineInterface::TIMER_SINGLE_SHOT);
      }
   }
   else
   {
      TRACE_MSG("Periodic REM timer not started as we don't yet have a stable clock!");
   }
}
#endif

void OamUserApplication::HandleOamActionReq(shared_ptr<MessageSerialisedData> message)
{
   ENTER();
   u32 returnVal = 0;
   shared_ptr<OamActionReq> oamActionReq = Serialisable::DeSerialise<OamActionReq>(message);
   RSYS_ASSERT(oamActionReq != NULL);

   TRACE("Received OamActionReq", oamActionReq->ToString());

   switch(oamActionReq->GetAction())
   {
#if 0
      case OAM_ACTION_GET_RSSI:
         {
            TRACE_MSG("Getting RSSI from hardware");
            returnVal = 0; // not implemented currently
            TRACE("Got RSSI", (u32)returnVal);
         }
         break;

      case OAM_ACTION_START_FRAME_AND_ERROR_COUNT:
         {
            TRACE_MSG("Starting Frame and Error Count");
            // now reset the values to 0
            accFrameCount = 0;
            accBitCount = 0;
            accBitErrors = 0;
            for(u8 i = 0; i < NUM_CPHY_STAT_CHAN_DCH; i++)
            {
               accBlockErrorCount[i] = 0;
               accBlockCount[i] = 0;
            }
            countErrors = true;
         }
         break;

      case OAM_ACTION_STOP_FRAME_AND_ERROR_COUNT:
         {
            char replyString[256];
            TRACE_MSG("Stopping Frame and Error Count");
            snprintf(replyString, sizeof(replyString),
                  "Frames: %u  Bits, Errors: {%"PRIu32", %"PRIu32"}  DCH Blocks, Errors: {{%"PRIu32", %"PRIu32"}, {%"PRIu32", %"PRIu32"}, {%"PRIu32", %"PRIu32"}, {%"PRIu32", %"PRIu32"}}",
                  accFrameCount,
                  accBitCount,
                  accBitErrors,
                  accBlockCount[0],
                  accBlockErrorCount[0],
                  accBlockCount[1],
                  accBlockErrorCount[1],
                  accBlockCount[2],
                  accBlockErrorCount[2],
                  accBlockCount[3],
                  accBlockErrorCount[3]);

            string replyStr(replyString);
            MibAttributeValues attrs;
            attrs.AddAttribute(PARAM_ID_FRAME_AND_ERROR_COUNT, replyStr);
            OamUserApplication::GetInstance().GetMibManager()->
               SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs);
            countErrors = false;
         }
         break;
#endif
      case OAM_ACTION_FACTORY_RESET:
         {
            TRACE_MSG("Resetting FAP to factory defaults");
            m_mibManager->ResetNvToFactoryDefaults();
         }
         //deliberate drop through, no break
      case OAM_ACTION_REBOOT:
         {
            TRACE_PRINTF_LEV(TRACE_WARNING, "Reboot requested by %s", MessagingEntityToString(message->GetFromEntity()));

            u32 adminState;
            MibHelper::GetMibAttributeDirect(PARAM_ID_LTE_FAP_ADMIN_STATE, adminState);
            if(!adminState)
            {
               ostringstream command;
               command <<"reboot";

               TRACE_PRINTF("Reboot Command : %s", command.str().c_str());

               if(system(command.str().c_str()) != oam_ret_zero)
               {
                  TRACE_MSG("OamUserApplication::HandleOamActionReq, Reboot command Failed");
               }
            }
            else
            {
               fprintf(stderr, "Reboot requested by %s\n", MessagingEntityToString(message->GetFromEntity()));

               GetKpiMgr().PollKpisSendToManagingEntity();

               MibAttributeValues attrs;
               attrs.AddAttribute(PARAM_ID_LTE_FAP_ADMIN_STATE, (u32)(ManagedObject::ADMIN_STATE_LOCKED));
               GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),attrs, ENTITY_OAM);

               oam_act_reboot = TRUE;
               TRACE_PRINTF("Sending Admin lock to StackManager");
               MfSetAdminStateReq req2sm(MF_SM, ManagedObject::ADMIN_STATE_LOCKED);
               SendMessage(req2sm, ENTITY_SM, ENTITY_OAM);
            }
         }
         break;

#if 0
      case OAM_ACTION_START_PERIODIC_REM_TIMER:
         {
            u32 perScanInterval, periodicRemScanEnabled, perScanTimeWindowDur, perScanTimeWindowStart, freqSyncSynced;

            if(MibHelper::GetMibAttributeDirect(PARAM_ID_PERIODIC_SCAN_INTERVAL_DAYS, perScanInterval) &&
                  MibHelper::GetMibAttributeDirect(PARAM_ID_PERIODIC_SCAN_ENABLED, periodicRemScanEnabled) &&
                  MibHelper::GetMibAttributeDirect(PARAM_ID_PERIODIC_SCAN_WINDOW_DUR_MINS, perScanTimeWindowDur) &&
                  MibHelper::GetMibAttributeDirect(PARAM_ID_PERIODIC_SCAN_WINDOW_START_TOD_SECS, perScanTimeWindowStart) &&
                  MibHelper::GetMibAttributeDirect(PARAM_ID_FREQ_SYNC_TIME_SYNCED, freqSyncSynced))
            {
               UpdateRemTimer(perScanInterval, periodicRemScanEnabled, perScanTimeWindowDur, perScanTimeWindowStart, freqSyncSynced);
            }
         }
         break;
#endif
      case OAM_ACTION_REM_SCAN:
      {
         CRemOamStartScanCmd oamStartScanCmd; 
         u32 periodicLteRemScan = 0, periodicWcdmaRemScan = 0;

         shared_ptr<MibAttributeValue> value;
         u8 remScanType = 0;
         value = MibHelper::GetMibAttributeDirect(
            MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE),
            PARAM_ID_LTE_PERIODIC_SCAN_MODE);
         periodicLteRemScan = value->GetValueU32();

         value = MibHelper::GetMibAttributeDirect(
            MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA),
            PARAM_ID_PERIODIC_SCAN_MODE);
         periodicWcdmaRemScan = value->GetValueU32();

         if (periodicLteRemScan)
         {
            remScanType = remScanType | NMM_SUPPORTED_RAT_LTE;
            TRACE_PRINTF("%s : LTE_Scantype is %d",__FUNCTION__,remScanType);
            oamStartScanCmd.setScanType(remScanType);
         }
         if (periodicWcdmaRemScan)
         {
            remScanType = remScanType | NMM_SUPPORTED_RAT_WCDMA;
            TRACE_PRINTF("%s : WCDMA_Scantype is %d",__FUNCTION__,remScanType);
            oamStartScanCmd.setScanType(remScanType);
         } 

         if ((periodicLteRemScan == true) || (periodicWcdmaRemScan == true))
         {
            SendMessage(oamStartScanCmd, ENTITY_OAM_REM, ENTITY_OAM);
         }
      }
      break;

      default:
         break;
   }

   // Send confirm.
   if(OAM_ACTION_REBOOT != oamActionReq->GetAction())
   {
      OamActionCnf oamActionCnf(message->GetFromEntity(), oamActionReq->GetAction(), returnVal);
      TRACE_MSG("Sending OamActionCnf");
      bool reply = SendMessage(oamActionCnf, oamActionCnf.GetEntity(), ENTITY_OAM);
      if(!reply)
      {
         TRACE_MSG("Sending OamActionCnf failed!");
      }
   }

   EXIT();
}
#if 0
void OamUserApplication::SendCPhyHwConfigReq()
{
   CphyHwConfigReq hwConfig;

   memset(&hwConfig, 0, sizeof(hwConfig));

   // TODO - need to raise alarm and sit idle with red LED on if any of these are not present.

   hwConfig.hwType = 0xff; // Invalid default value
   MibHelper::GetMibAttributeDirect(PARAM_ID_HARDWARE_TYPE, hwConfig.hwType);
   hwConfig.hwRevision = 0xff; // Invalid default value
   MibHelper::GetMibAttributeDirect(PARAM_ID_HARDWARE_REVISION, hwConfig.hwRevision);
   hwConfig.hwModLevel = 0xff; // Invalid default value
   MibHelper::GetMibAttributeDirect(PARAM_ID_HARDWARE_MOD_STATE, hwConfig.hwModLevel);
   MibHelper::GetMibAttributeDirect(PARAM_ID_OSC_DAC, hwConfig.afcDacValue);
   MibHelper::GetMibAttributeDirect(PARAM_ID_OSC_DAC_SLOPE_PPT_PER_BIT, hwConfig.afcDacSlopePpt);

   if((hwConfig.hwType == 0xff) || (hwConfig.hwRevision == 0xff) || (hwConfig.hwModLevel == 0xff))
   {
      TRACE_PRINTF_LEV(TRACE_FATAL, "Invalid Hardware Configuration: type=%"PRIu32", rev=%"PRIu32", mod=%"PRIu32,
            hwConfig.hwType, hwConfig.hwRevision, hwConfig.hwModLevel);
   }

   hwConfig.txPowerAmpGaindB = 0;

#ifdef PRODUCT_hbs2_iu
   hwConfig.allowDefaultCal = false; /* allowDefaultCal */
#else
   hwConfig.allowDefaultCal = true;
#endif

   CPhyHwConfigReq msg(&hwConfig);
   TRACE_PRINTF("Sending CPhyHwConfigReq to L1");
   SendMessage(msg, ENTITY_CPHY, ENTITY_OAM);
}
#endif

void OamUserApplication::SendRemScanReq()
{

#ifdef LTE_REM
   TRACE_PRINTF("%s : REM Scan Request Message received from HeMS",__FUNCTION__);
   CRemOamStartScanCmd oamStartScanCmd;
   bool performLteRemScanOnBoot = false;
   bool performLteRemFreqSync = false;
   U32 performWcdmaRemScanOnBoot = 0;
   shared_ptr<MibAttributeValue> value;
   u8 remScanType = 0;
   MibHelper::GetMibAttributeDirect(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE),PARAM_ID_LTE_REM_SCAN_ON_BOOT, performLteRemScanOnBoot);
   MibHelper::GetMibAttributeDirect(PARAM_ID_LTE_FREQ_SYNC_ENABLE , performLteRemFreqSync);
   value = MibHelper::GetMibAttributeDirect(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA), PARAM_ID_WCDMA_REM_SCAN_ON_BOOT);
   performWcdmaRemScanOnBoot = value->GetValueU32();
   TRACE_PRINTF("Getting WCDAM SCAN ON BOOT from mibdn performWcdmaRemScanOnBoot =%ld\n",performWcdmaRemScanOnBoot);
   if (performLteRemScanOnBoot)
   {
      remScanType = remScanType | NMM_SUPPORTED_RAT_LTE;
      TRACE_PRINTF("%s : LTE_Scantype is %d",__FUNCTION__,remScanType);
      oamStartScanCmd.setScanType(remScanType);
   }
   if (performWcdmaRemScanOnBoot)
   {
      remScanType = remScanType | NMM_SUPPORTED_RAT_WCDMA;
      TRACE_PRINTF("%s : WCDMA_Scantype is %d",__FUNCTION__,remScanType);
      oamStartScanCmd.setScanType(remScanType);
   }
   if(performLteRemFreqSync)
   {
      remScanType = remScanType | NMM_SUPPORTED_RAT_FREQ_SYNC;
      TRACE_PRINTF("%s : LTE FREQ SYNC TYPE is %d",__FUNCTION__,remScanType);
      oamStartScanCmd.setScanType(remScanType);
   }
   if(performLteRemFreqSync || performWcdmaRemScanOnBoot || performLteRemScanOnBoot)
   {
      SendMessage(oamStartScanCmd, ENTITY_OAM_REM, ENTITY_OAM);
   }

#else

   TRACE_PRINTF("%s : REM functionality disabled",__FUNCTION__);

#endif

}

void OamUserApplication::SetSoftwareReleaseAndBuildDesc() const
{
   TRACE_PRINTF("%s",__FUNCTION__);
   ConfigurationFile softwareReleaseFile("software-release", "/mnt/bank-active/config/");

   softwareReleaseFile.ReadConfigurationFile();
   const char *softwareRelease = softwareReleaseFile.GetStringParameter("SOFTWARE_RELEASE","");
   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_TR069_SW_VERSION_STRING, softwareRelease);
   m_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs);
}

void OamUserApplication::DnsServerAdd(
      u32             id,
      IPv4Address&    dnsServerAddr
      )
{
   /* synchronous exchange */
   m_messenger->SwitchToPolledMode();

   TenpinDnsServerAddReq req;
   req.SetId(id);
   req.SetAddr(dnsServerAddr.Get());

   SendMessage(req, ENTITY_TENPIN, ENTITY_OAM);

   MessagingEntity fromEntity, toEntity;

   shared_ptr<SerialisedData> rx = m_messenger->BlockingReceiveMessage(5000, fromEntity, toEntity);

   /* only expecting corresponding confirm but failure to receive it is not critical */
   if (rx && (SERIALISATION_ID_TENPIN_DNS_SERVER_ADD_CNF == rx->GetSerialisationId()))
   {
      /* synchronous exchange complete, nothing further to do */
   }

   m_messenger->RestoreCallbackMode();
}

void OamUserApplication::TftpOpenPinhole(
      IPAddress&    tftpServer
      )
{
   /* synchronous exchange */
   m_messenger->SwitchToPolledMode();

   /* temporary pinhole for all udp from this specific address */
   TenpinFirewallOpenReq req;
   req.SetPassIn();
   req.SetPassOut();
   req.SetProtocolUdp();
   req.SetRemoteAddr(tftpServer);

   SendMessage(req, ENTITY_TENPIN, ENTITY_OAM);

   MessagingEntity fromEntity, toEntity;

   shared_ptr<SerialisedData> rx;

   /* mantis issue #3376: really do wait for the cnf */
   do
   {
      rx = m_messenger->BlockingReceiveMessage(5000, fromEntity, toEntity);
      /* only expecting corresponding confirm but failure to receive it is not critical */
   }
   while (!rx || (SERIALISATION_ID_TENPIN_FIREWALL_OPEN_CNF != rx->GetSerialisationId()));

   shared_ptr<TenpinFirewallOpenCnf> cnf = Serialisable::DeSerialise<TenpinFirewallOpenCnf>(rx);

   m_messenger->RestoreCallbackMode();
}

void OamUserApplication::TftpClosePinhole(void)
{
   /* synchronous exchange */
   m_messenger->SwitchToPolledMode();

   TenpinFirewallCloseReq req;

   SendMessage(req, ENTITY_TENPIN, ENTITY_OAM);

   MessagingEntity fromEntity, toEntity;

   shared_ptr<SerialisedData> rx = m_messenger->BlockingReceiveMessage(5000, fromEntity, toEntity);

   /* only expecting corresponding confirm but failure to receive it is not critical */
   if (rx && (SERIALISATION_ID_TENPIN_FIREWALL_CLOSE_CNF == rx->GetSerialisationId()))
   {
      /* nothing to do */
   }
   m_messenger->RestoreCallbackMode();
}

void OamUserApplication::FillNeighborlistInfo()
{
   TRACE_PRINTF("OamUserApplication::FillNeighborlistInfo:Entry");

   bool NeighborlistConfig = false;
   bool NeighborlistSelfConfigEnable = false;
   MibHelper::GetMibAttributeDirect(PARAM_ID_NEIGHBORLIST_CONFIG, NeighborlistConfig);
//   MibHelper::GetMibAttributeDirect(PARAM_ID_NEIGHBORLIST_SELFCONFIG_ENABLE, NeighborlistSelfConfigEnable);

   if(NeighborlistConfig && NeighborlistSelfConfigEnable)
   {
      TRACE_PRINTF("SelfConfig:At present HNB will not support multiple values hence NeighborlistConfig is disabled by default");
   }
   else
   {
      //Fill the Values from Configured params to InUse params

      TRACE_PRINTF("SelfConfig:NeighborlistConfig is disabled");
      vector<MibDN> dnList;
      MibGetAttributesReq mibGetAttributesReq;
      MibGetAttributesCnf mibGetAttributesCnf;

      for(u32 i = 0; i < dnList.size(); i++)
      {
         MibAttributeValues dnAttrValues;

         // Get the list of IDs for this DN.
         const MibAttributeIds& attrIds = mibGetAttributesReq.GetMibAttributeIds(dnList[i]);

         // Get the values for this DN.
         m_mibManager->GetAttributes(dnList[i], attrIds, dnAttrValues);

         // Add values for this DN to the confirm.
         mibGetAttributesCnf.AddAttributes(dnList[i+3], dnAttrValues);
      }
   }
   TRACE_PRINTF("OamUserApplication::FillNeighborlistInfo:Exit");
}

void OamUserApplication::GetTimeoutValue(u32 &timeoutvalue)
{
   u32 wcdmaTimeoutValue;
   u32 gsmTimeoutValue;
   MibHelper::GetMibAttributeDirect(PARAM_ID_WCDMA_SCAN_TIMEOUT, wcdmaTimeoutValue);
   MibHelper::GetMibAttributeDirect(PARAM_ID_GSM_SCAN_TIMEOUT, gsmTimeoutValue);
   timeoutvalue = wcdmaTimeoutValue + gsmTimeoutValue;
   timeoutvalue = timeoutvalue * 1000;//converting into milli secs
   TRACE_PRINTF("%s::ScanTimeout value is %d\n",__FUNCTION__ , timeoutvalue);
}

void OamUserApplication::SendAbortRemScanReq()
{
   TRACE_PRINTF("%s:Entry",__FUNCTION__);
   CRemOamAbortScanCmd oamAbortScanCmd;
   SendMessage(oamAbortScanCmd, ENTITY_OAM_REM, ENTITY_OAM);
   TRACE_PRINTF("%s:Exit",__FUNCTION__);
}

/*
 *  Function to return the instance number of the Object if it is
 *  a Multi Instance Object
 */

/*
 * Function HandleGERANPmaxParam
 * This function checks if the setAttributeValue is for PmaxGERAN parameter
 * If yes the appropriate flags to indicate that user has set these parameters
 * are updated
 */
void OamUserApplication::HandleGERANPmaxParam(string pMaxGERANParam)
{
   TRACE_PRINTF("%s",__FUNCTION__);

   const char * isPMaxGERAN;
   const char * pMaxGERAN = "LTE_GERAN_X_RSYS_FREQ_PMAX";
   s32 lteInstanceNbr = 0,geranInstanceNbr=0;

   isPMaxGERAN = strstr(pMaxGERANParam.c_str(),pMaxGERAN);

   if (isPMaxGERAN != NULL)
   {
      std::size_t index=pMaxGERANParam.rfind(":");
      if(index != std::string::npos)
      {
         std::string dnStr = pMaxGERANParam.substr(0,index);
         geranInstanceNbr = MibDN::GetMibObjectInstanceNum(dnStr,2);
         lteInstanceNbr = MibDN::GetMibObjectInstanceNum(dnStr,1);
         if ( (INVALID_INSTANCE_NBR !=geranInstanceNbr) && ( INVALID_INSTANCE_NBR !=lteInstanceNbr) )
         {
            MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,(u32)lteInstanceNbr);
            MibAttributeValues attrVal;
            attrVal.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_FREQ_PRES_PMAX,u32(ONE));
            m_mibManager->SetAttributes(MibDN::GenerateMibDN(fapLteDn,MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST,(u32)geranInstanceNbr),attrVal);
         }
      }
   }
}

/*
 * Function HandleGERANSpeedScaleParam
 * This function checks if the setAttributeValue is for tReselectionGERANSFMedium &
 * tReselectionGERANSFHigh parameters
 * If yes the appropriate flags to indicate that user has set these parameters
 * are updated
 */
void OamUserApplication::HandleGERANSpeedScaleParam(string speedScaleGERANParam)
{
   TRACE_PRINTF("%s",__FUNCTION__);

   const char * istReselHigh = NULL;
   const char * istReselMed = NULL;
   const char * tReselSfMed = "LTE_GERAN_T_RESEL_SF_MED";
   const char * tReselSfHigh = "LTE_GERAN_T_RESEL_SF_HIGH";

   istReselMed = strstr(speedScaleGERANParam.c_str(),tReselSfMed);
   istReselHigh = strstr(speedScaleGERANParam.c_str(),tReselSfHigh);

   if (istReselMed != NULL)
   {
      speedScaleCount |= OAM_SET_GERAN_TRESEL_SF_MED;
   }
   if (istReselHigh != NULL)
   {
      speedScaleCount |= OAM_SET_GERAN_TRESEL_SF_HIGH;
   }
   if(OAM_SET_GERAN_SPEED_SCALE == speedScaleCount)
   {
      std::string dnStr = speedScaleGERANParam;
      s32 instanceNumber = MibDN::GetMibObjectInstanceNum(dnStr,1);
      if (INVALID_INSTANCE_NBR != instanceNumber)
      {
      speedScaleCount = 0;
      MibAttributeValues attrVal;
      attrVal.AddAttribute(PARAM_ID_LTE_GERAN_PRES_SPEED_SCALE,u32(ONE));
      m_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,(u32)instanceNumber),attrVal);
      }
   }
}

/*
 * Function  HandleNetCntrlOrdrParam
 * This function set  network controll order present as true if
 * network controll order is set
 */
void OamUserApplication::HandleNetCntrlOrdrParam(string NCOParam)
{
   TRACE_PRINTF("%s",__FUNCTION__);

   const char * isNCO;
   const char * NCO = "LTE_GERAN_X_RSYS_CELL_NET_CNTRL_ORDER";
   isNCO = strstr(NCOParam.c_str(),NCO);
   if (isNCO != NULL)
   {
      std::size_t index = NCOParam.rfind(":");
      if(index != std::string::npos)
      {
         std::string dnStr = NCOParam.substr(0,index);
         s32 lteInstanceNbr = MibDN::GetMibObjectInstanceNum(dnStr,1);
         s32 geranInstanceNbr = MibDN::GetMibObjectInstanceNum(dnStr,2);
         if(INVALID_INSTANCE_NBR != lteInstanceNbr)
         {
            MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,(u32)lteInstanceNbr);
            MibAttributeValues attrVal;
            if(INVALID_INSTANCE_NBR !=geranInstanceNbr)
            {
               attrVal.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_NET_CNTRL_ORDER_PRES,u32(ONE));
               m_mibManager->SetAttributes(MibDN::GenerateMibDN(fapLteDn,MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST,(u32)geranInstanceNbr),attrVal);
            }
         }
      }
   }
}

void OamUserApplication::HandleMIOdn(MibDN dn)
{
   TRACE_PRINTF("%s:Entry",__func__);

   std::vector<u32> geranSrcLst;
   std::vector<u32> tdsCdmaSrcLst;
   std::vector<u32> plmnSrcLst;
   MibAttributeValues attrs;
   s32 instanceNum = 0;
   s32 cellId = 0;

   TRACE_PRINTF("%s:Entry",__FUNCTION__);
   MibAttributeId PARAM_ID_SRC_LIST;

   if(MIOAutoManage::GetInstance().getSrcListParamName(dn,PARAM_ID_SRC_LIST))
   {
      std::vector<u32> srcLst;
      MibAttributeValues attrs;
         instanceNum=MibDN::GetMibObjectInstanceNum(dn,2);
         if((PARAM_ID_INVALID != PARAM_ID_SRC_LIST)&&
               (INVALID_INSTANCE_NBR != instanceNum))
         {
            cellId=MibDN::GetMibObjectInstanceNum(dn,1);
            MibDN faplteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,(u32)cellId);
            MibHelper::GetMibAttributeDirect(faplteDn,PARAM_ID_SRC_LIST,srcLst);
            if((u32)instanceNum < srcLst.size())
            {
              srcLst.at((u32)instanceNum) = OBJECT_CONFIGURED; /*Src is SPV */
              attrs.AddAttribute( PARAM_ID_SRC_LIST, srcLst);

              m_mibManager->SetAttributes(faplteDn,attrs);
            }
         }
   }
}

u32 OamUserApplication::accFrameCount;
u32 OamUserApplication::accBlockCount[NUM_CPHY_STAT_CHAN_DCH];
u32 OamUserApplication::accBlockErrorCount[NUM_CPHY_STAT_CHAN_DCH];
u32 OamUserApplication::accBitErrors;
u32 OamUserApplication::accBitCount;
bool OamUserApplication::countErrors;


#if 0
/* 0.9_patch3: signal_handler function */
void signal_handler(int sig)
{
   TRACE_PRINTF("\n Received the signal(%d) for process(%d) \n", sig, getpid());
   /* Release the TFCS client */
#ifdef QC_TFCS
   OamUserApplication::GetInstance().m_freqSyncEntity.releaseTFCSClient();
#endif
   exit(0);
}
#endif

string OamUserApplication::GetStatusAsString(int status)
{
   string remstat = "";
   switch (status)
   {
      case SCAN_INDETERMINATE:
         {
            remstat = "Indeterminate";
            break;
         }
      case SCAN_INPROGRESS:
         {
            remstat = "InProgress";
            break;
         }
      case SCAN_SUCCESS:
         {
            remstat = "Success";
            break;
         }
      case SCAN_ERROR:
         {
            remstat = "Error";
            break;
         }
      case SCAN_TIMEOUT:
         {
            remstat = "Error_Timeout";
            break;
         }
      default:
         break;
   }
   return remstat;
}

#if 0
void OamUserApplication::OamInitSignals(void)
{
   signal(SIGINT,signal_handler);
   signal(SIGSEGV,signal_handler);
   signal(SIGBUS,signal_handler);
   signal(SIGQUIT,signal_handler);
   signal(SIGHUP,signal_handler);
   signal(SIGKILL,signal_handler);
}
#endif

bool  OamUserApplication::Tr069Enabled(void*)
{
   return 1;
}

/**
 * Application entry point.
 */
int main(int argc, char* argv[])
{
   int result = OamUserApplication::GetInstance().Run(argc, argv);
   return result;
}
