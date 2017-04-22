/********************************************************************16**

            (c) Copyright 2012 by RadiSys Corporation. All rights reserved.

     This software is confidential and proprietary to RadiSys Corporation.
     No part of this software may be reproduced, stored, transmitted, 
     disclosed or used in any form or by any means other than as expressly
     provided by the written Software License Agreement between Radisys 
     and its licensee.

     Radisys warrants that for a period, as provided by the written
     Software License Agreement between Radisys and its licensee, this
     software will perform substantially to Radisys specifications as
  published at the time of shipment, exclusive of any updates or 
  upgrades, and the media used for delivery of this software will be 
     free from defects in materials and workmanship.  Radisys also warrants 
  that has the corporate authority to enter into and perform under the   
  Software License Agreement and it is the copyright owner of the software 
  as originally delivered to its licensee.

     RADISYS MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
  WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
  A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
  MATERIALS.

     IN NO EVENT SHALL RADISYS BE LIABLE FOR ANY INDIRECT, SPECIAL,
  CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
  OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
  ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
  LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.

                       Restricted Rights Legend:

  This software and all related materials licensed hereby are
  classified as "restricted computer software" as defined in clause
  52.227-19 of the Federal Acquisition Regulation ("FAR") and were
  developed entirely at private expense for nongovernmental purposes,
  are commercial in nature and have been regularly used for
  nongovernmental purposes, and, to the extent not published and
  copyrighted, are trade secrets and confidential and are provided
  with all rights reserved under the copyright laws of the United
  States.  The government's rights to the software and related
  materials are limited and restricted as provided in clause
  52.227-19 of the FAR.

  IMPORTANT LIMITATION(S) ON USE

  The use of this software is limited to the use set
     forth in the written Software License Agreement between Radisys and
  its Licensee. Among other things, the use of this software
  may be limited to a particular type of Designated Equipment, as 
  defined in such Software License Agreement.
  Before any installation, use or transfer of this software, please
     consult the written Software License Agreement or contact Radisys at
  the location set forth below in order to confirm that you are
  engaging in a permissible use of the software.

                    RadiSys Corporation
Tel: +1 (858) 882 8800
Fax: +1 (858) 777 3388
Email: support@trillium.com
                    Web: http://www.radisys.com 

 *********************************************************************17*/

/*********************************************************************17*/
/**********************************************************************

Name:     Stack Manager Application - SmApplication.cpp

Type:     Cpp implementation file

Desc:     Implements the Oam-messenger functionality and serves as an 
	  interface between the Oam and the stack

File:     SmApplication.cpp

***********************************************************************/
#include <stdlib.h>
#include<string>
#include <system/Trace.h>
#include <Exception.h>
#include <time.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <mib-common/messages/MibSubscribeAttributesDeleteInd.h>
#include <mib-common/messages/MibCreateObjectCnf.h>
#include <messaging/messages/common/KpiRegisterReq.h>
#include <messaging/messages/common/MfSetAdminStateReq.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/common/InitConfigComplete.h>
#include <messaging/messages/common/AlarmRegister.h>
#include <messaging/messages/common/EventNotify.h>
#include <messaging/messages/common/L2TimerNotify.h>
#include <messaging/messages/common/UpdateInUseEutraCellList.h>
#include <messaging/messages/common/UpdateInUseUtraCellList.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/common/UploadLogReq.h>
#include <messaging/messages/common/OamActionReq.h>
#include <system/KpiGroup.h>
#include <system/KpiCollector.h>
#include <system/Utilities.h>
#include <string.h>
#include <sstream>
#include <fstream>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "SmApplication.h"
#include "SmAlarmHandler.h"
#include "SmMultiInstanceObjectManager.h"
#include "wr_kpi.h"
#define ROK 0
#define RFAILURE 1
#define TR_196_OBJ 0
#define RSYS_OBJ 1
#define ANR_OBJ 2
#define SELF_CFGD_CELL 100 /* Cell that is detected through REM scan or ANR */
#define CELLSUBID (cellIdx*SI_LTE_MESSENGER_CONFIGURATION_COMPLETE)
#define INVALID 0xff
extern "C" 
{
   int SmAppTst();
   s16 MsmEnodeBinitialCfgComplete();
   void MsmStartStopStackReq(unsigned int isPremReq,unsigned int isStkSt,
         unsigned int isImd);
   void MsmConfigComplete();
   void MsmOperationalState(u32 opstate);
   void MsmShutDownAck();
   S16 MsmSmmDynCfgReq(void *cfg, unsigned int cfgType,unsigned char priority);
   S16 wrSendKpisInfo(void);
   S16 wrKpiStartKpiCollecPrc(Bool l2CollecEna); /*start Kpi Collection*/
   S16 wrKpiStopKpiCollecPrc(void); /*stop Kpi Collection*/
   void FapAlarmInd(u32 alarmId, u8 severity, u8 causeType, u8 causeVal,u16 cellId = 0);
   void FapAlarmIndWithAddInfo(MsmUpdateAlarms *smUpdateAlarms);
   void SmUpdateMibParms(u32 msgType, u32 action, void* Cfg, u16 cellIdx);
   void SmUpdateSwVersion(const char * swver);
   void SmUpdateN1pucch(u16 n1Pucch);
   void smUpdateSONParams(u32 msgType, void* params);
   void msmDynConfigComplete(u8 status, u8 cause, MsmDynCfmInfo cfmInfo,
         u16 cellIdx);
}

/* source for neighbor cell update is ANR or not */
bool m_smmWaitForDynCfgRsp = FALSE;
bool neighFreqRollBack = FALSE; 
bool neighCellRollBack = FALSE; 
bool dynNbrCellUpdate = FALSE;
u32 attrPresent = FALSE;
std::vector<u32> sonUpdatedPCIList;
bool firstTimeConfig = true;
bool remScanDone = true;
bool ipPresent = false;
bool globalInitCfgComp = false;
extern MsmFapParameters   fapParameters;

typedef struct
{
   bool inUse;        /* Indicates whether the element is free */
   u8   instanceNumb; /* Instance number of the object */
   u8   mioObjInstance;
}indxMap;
indxMap freqIndxMap[8]; /* Maps Neighbour frequency MO instance and freqIndx
                           sent to SM */
indxMap cellIndxMap[32]; /* Maps Neighbour cell MO instance and cellindex at NRT
                            sent to SM */

using namespace std;
using namespace boost;
using namespace threeway;
using namespace Sm;

extern "C" { void IncFapKpiByIntVal(unsigned  int Id,u32 cellIdx, unsigned int  incVal);}
extern "C" { void IncFapKpiByRealVal(unsigned  int Id,u32 cellIdx,float incVal);}
extern "C" { void KpisInfoSentNotification(void);}
extern "C" { void IncFapKpiByIntValMInst(unsigned  int Id, unsigned int  incVal, KpiInstInfo mInfoVal);}
extern "C" { void IncFapKpiByRealValMInst(unsigned  int Id, float incVal, KpiInstInfo mInfoVal);}
//QyMapSmSpvSubs        SpvStatus;

#define CONVERT_SECONDS_TO_MILLISEC(seconds) seconds*1000

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

SmApplication* SmApplication::s_instance = NULL;
u32 SmApplication::s_adminFlag=MSM_FALSE;
bool SmApplication::s_isN1PucchUpdateFromRRM=false;
bool SmApplication::m_PeriodicRemScanInProg = false;
//DeclareAppVersionStamp

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SmApplication::SmApplication() : \
      SingleThreadedAppWithAttrCache("oam-sm"),
      m_kpiMessageManager(ENTITY_SM,*this),m_adminState(0),
      m_isSONRaisedAlarmExists(0), numOfCells(2)
{
   ENTER();

   string fileName = (const char *)fapParameters.configFilePath;
   ifstream in(fileName.c_str());
   string numCellStr, param;
   bool found = false;
   if (in.is_open())
   {
      while (!in.eof() && !found)
      {
         in >> param >> numCellStr;
         if (!param.compare("OAM_NUM_CELL_ENTRIES"))
            found = true;
      }
   }
   else
   {
      TRACE_PRINTF("Failed to open %s. Using defaults.", fileName.c_str());
   }
   if(NULL != numCellStr.c_str())
   {
      numOfCells = atoi(numCellStr.c_str());
   }
   EXIT();
}

SmApplication::~SmApplication()
{
   ENTER();

   EXIT();
}

SmApplication& SmApplication::GetInstance()
{
   ENTER ();

   if(s_instance == NULL)
   {
      s_instance = new SmApplication();
   }

   RETURN (*s_instance);
}

void SmApplication::InitialiseSubsIds()
{
   int idx, startRange, endRange, endVal, startVal=1;

   endVal = SI_LTE_MESSENGER_CONFIGURATION_COMPLETE;

   for (idx=0; idx < numOfCells; idx++)
   {
      startRange = startVal + (idx * endVal);
      endRange = endVal + (idx * endVal);
      ranges[idx] = std::make_pair(startRange, endRange);
   }
}

void SmApplication::InitialiseApp()
{
   RegisterMessageHandler(&m_kpiMessageManager, "SmKpi");
   RegisterMessageHandler(this, "oam-sm");
   m_smKpiCollector.reset(new SmKpiCollector());
   m_smTr196Validator.reset(new SmTr196Validator());
   m_kpiMessageManager.RegisterKpiCollector(ENTITY_SM, m_smKpiCollector);
   InitialiseSubsIds();
}

void SmApplication::StartApp()
{
   TRACE_MSG("Start Registering KPIs...");
   set<KpiGroupId> kpiGroupIds;

   //LTE KPI begins from here
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RRC_ESTAB);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RRC_REESTAB);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RRC_CONN_NUM);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RRC_SETUP_TIME);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_UE_CTXT_RELEASE);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_ESTAB);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_ESTAB_ADD);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_SETUP_TIME_MEAN);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_SETUP_TIME_MAX);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_RELEASE_ENB);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_RELEASE);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_MOD);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_SESSION);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ERAB_NUM);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_HO_INTRA_LTE);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_HO_INTER_RAT);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_HO_INTRA_LTE_INTER_ENB);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_HO_INTRA_FREQ);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_HO_INTER_FREQ);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_HO_DRX);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_DL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_UL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_CONTROL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_DL_DLY);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_DL_DROP);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_DL_LOSS);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PDCP_SDU_UL_LOSS);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_Throughput_DL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_Throughput_UL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_DL_PRB_Usage);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_UL_PRB_Usage);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RACH_Usage);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CELL_Unavailable_Time);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_S1_SIG);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_PAGING);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CSG);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_EQUIP_RES);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_S1AP_RadioNetworkCause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_S1AP_TransportCause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_S1AP_NasCause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_S1AP_ProtocolCause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_S1AP_MiscCause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RRC_RreCause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RRC_Cause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RLC_Cause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RLC_Cause);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_TB_DL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_TB_UL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ACT_UE_DL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_ACT_UE_UL);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CSG_UE);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CSFB_CDMA);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CSFB_GERAN);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CSFB_UTRA);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_RIM);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_CSFB_IRAT);
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_L2_CPU_PERCORE);           
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_L3_CPU_PERCORE);           
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_L3_MEM_PERPOOL);           
   kpiGroupIds.insert( KPI_GROUP_ID_LTE_L2_MEM_PERPOOL);           
   KpiRegisterReq kpiRegisterReq(kpiGroupIds);
   SendMessage(kpiRegisterReq, ENTITY_OAM, ENTITY_SM);
   TRACE_MSG("End Registering KPIs...");
}

std::vector<MessagingEntity> SmApplication::GetSupportedEntities()
{
   vector<MessagingEntity> entities;

   entities.push_back(ENTITY_SM);

   return entities;
}

void SmApplication::GetSubscriptions
(
 std::vector<SubscriptionDescriptor>& subscriptions
 )
{
   u16   cellIdx = 0;
   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   /* eNodeB level parameter subscriptions */
   MibAttributeIds mibLteSctpCfgParameters;
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_HRTBEAT_INTERVAL);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_RTO_INITIAL);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_RTO_MIN);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_RTO_MAX);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_MAX_ASSOC_RETX);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_MAX_INIT_RETX);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_MAX_PATH_RETX);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_SCTP_COOKIE_LIFE);
   mibLteSctpCfgParameters.insert(PARAM_ID_LTE_X_RADISYS_LOCAL_PORT);
   AddSubscription(subscriptions, SI_LTE_SCTP_CONFIG_PARAMETERS,
         ENTITY_SM, fapDn, mibLteSctpCfgParameters);
   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_SCTP_CONFIG_PARAMETERS,
          &SmApplication::HandleLteSctpConfigParameters));

   MibAttributeIds mibFapDuplexMode;
   mibFapDuplexMode.insert(PARAM_ID_DUPLEX_MODE);
   AddSubscription(subscriptions,SI_DUPLEX_MODE,
         ENTITY_SM,fapDn,mibFapDuplexMode);
   hdlrMap.insert(std::make_pair
         ((u16)SI_DUPLEX_MODE,
          &SmApplication::HandlerEmpty));

   MibAttributeIds mibLteTotaleNodeBStats;
   mibLteTotaleNodeBStats.insert(PARAM_ID_LTE_TENB_STATS_SOCKET_ENABLE);
   mibLteTotaleNodeBStats.insert(PARAM_ID_LTE_TENB_FILE_STATS_ENABLE);
   mibLteTotaleNodeBStats.insert(PARAM_ID_LTE_TENB_CONSOLE_STATS_ENABLE);
   mibLteTotaleNodeBStats.insert(PARAM_ID_LTE_TENB_STATS_PERIODICITY);
   mibLteTotaleNodeBStats.insert(PARAM_ID_LTE_TENB_STATS_SCOKET_PORT);
   AddSubscription(subscriptions,S1_LTE_TENB_STATS_CFG, ENTITY_SM, fapDn,
         mibLteTotaleNodeBStats);
   hdlrMap.insert(std::make_pair
         ((u16)S1_LTE_TENB_STATS_CFG,
          &SmApplication::HandleTenbStatsCfgParams));

   MibAttributeIds mibFapLogUpload;
   mibFapLogUpload.insert(PARAM_ID_LOG_UPLOAD_INTERVAL);
   AddSubscription(subscriptions,SI_LOG_UPLOAD_INTERVAL,
         ENTITY_SM,fapDn,mibFapLogUpload);
   hdlrMap.insert(std::make_pair
         ((u16)SI_LOG_UPLOAD_INTERVAL,
          &SmApplication::HandleLogUpload));

   MibAttributeIds mibLogLvlCfgParam;
   mibLogLvlCfgParam.insert(PARAM_ID_LTE_ENB_L3LOG_LEVEL);
   mibLogLvlCfgParam.insert(PARAM_ID_LTE_ENB_L2LOG_LEVEL);
   mibLogLvlCfgParam.insert(PARAM_ID_LTE_ENBLOG_MASK);
   mibLogLvlCfgParam.insert(PARAM_ID_LTE_ENBLOG_REMOTE_LOGGING);
   AddSubscription(subscriptions,SI_LTE_LOG_LVL_PARAM,
         ENTITY_SM,fapDn,mibLogLvlCfgParam);
   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_LOG_LVL_PARAM,
          &SmApplication::HandleEnbLogLvlParameter));

   MibAttributeIds mibAdminState;
   mibAdminState.insert(PARAM_ID_LTE_FAP_ADMIN_STATE);

   AddSubscription(subscriptions, SI_LTE_ADMIN_STATE_CHANGE, ENTITY_SM,
         fapDn, mibAdminState);

   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_ADMIN_STATE_CHANGE,
          &SmApplication::HandleLteAdminStateChange));

   MibAttributeIds mibOPState;
   mibOPState.insert(PARAM_ID_LTE_RFTX_OP_STATE);

   AddSubscription(subscriptions, SI_LTE_OP_STATE_CHANGE, ENTITY_SM,
         fapDn, mibOPState);

   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_OP_STATE_CHANGE,
          &SmApplication::HandlerEmpty));

#ifdef TIP_OAM
   MibAttributeIds mibS1UParameters;
   mibS1UParameters.insert(PARAM_ID_GTPU_ECHO_INTERVAL);
   AddSubscription(subscriptions, SI_LTE_SIU_PARAMETERS,
         ENTITY_SM, fapDn, mibS1UParameters);
   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_SIU_PARAMETERS,
          &SmApplication::HandleS1UCfg));
#endif

   MibAttributeIds mibLteeNodeBIPParameters;
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_S1CON_MODE);
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_SIGLINK_SERVER_LIST);
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_S1SIG_LINK_PORT);
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_OAM_SECONDARY_IP_1);
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_OAM_SECONDARY_IP_2);
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_OAM_SECONDARY_IP_3);
   mibLteeNodeBIPParameters.insert(PARAM_ID_LTE_OAM_SECONDARY_IP_4);

   AddSubscription(subscriptions, SI_LTE_ENODEB_IP_PARAMETERS,
         ENTITY_SM, fapDn, mibLteeNodeBIPParameters);

   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_ENODEB_IP_PARAMETERS,
          &SmApplication::HandleLteeNodeBIPParameters));

   MibAttributeIds mibLteDbgParameters;
   mibLteDbgParameters.insert(PARAM_ID_LTE_TUCL_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_SCTP_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_S1AP_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_EGTP_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_RRC_APP_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_RRC_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_RLC_PDCP_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_MAC_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_CL_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_SM_DBG);
   mibLteDbgParameters.insert(PARAM_ID_LTE_X2AP_DBG);

   AddSubscription(subscriptions, SI_LTE_DBG_PARAMETERS, ENTITY_SM, fapDn,
         mibLteDbgParameters);

   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_DBG_PARAMETERS,
          &SmApplication::HandleLteDbgParameters));

   MibAttributeIds mibMessengerPerfMgmt;
   mibMessengerPerfMgmt.insert(PARAM_ID_PM_COLLECTION_METHOD);
   mibMessengerPerfMgmt.insert(PARAM_ID_PM_L2_COLLECTION_ENA);

   AddSubscription(subscriptions, SI_PM_PARAMETERS, ENTITY_SM, fapDn,
         mibMessengerPerfMgmt);

   hdlrMap.insert(std::make_pair
         ((u16)SI_PM_PARAMETERS,
          &SmApplication::HandlePerfMgmtParameters));

   MibAttributeIds mibFrequentFaultMgmtParameters;
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MAX_S1ERROR_IND_COUNT);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MIN_S1ERROR_IND_TIME);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MAX_S1RESET_COUNT);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MIN_S1RESET_TIME);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MAX_X2ERROR_IND_COUNT);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MIN_X2ERROR_IND_TIME);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MAX_X2RESET_COUNT);
   mibFrequentFaultMgmtParameters.insert(PARAM_ID_MIN_X2RESET_TIME);

   AddSubscription(subscriptions, SI_FREQUENT_FAULT_PARAMETERS, ENTITY_SM,
         fapDn, mibFrequentFaultMgmtParameters);

   hdlrMap.insert(std::make_pair
         ((u16)SI_FREQUENT_FAULT_PARAMETERS,
          &SmApplication::HandleFrequentFaultMgmtParameters));

   MibAttributeIds mibEnbIp;
   mibEnbIp.insert(PARAM_ID_ENB_IP_ADDR_IPV4);
   mibEnbIp.insert(PARAM_ID_ENB_IP_ADDR_IPV6);
   AddSubscription(subscriptions, SI_ENB_IP_ADDRESS, ENTITY_SM,fapDn, mibEnbIp);
   hdlrMap.insert(std::make_pair
         ((u16)SI_ENB_IP_ADDRESS,
          &SmApplication::HandleEnodebIPAddress));

   MibAttributeIds mibGostCfgParams;
   mibGostCfgParams.insert(PARAM_ID_LTE_RRC_LOG_ENABLE);
   mibGostCfgParams.insert(PARAM_ID_LTE_GOST_IP);
   mibGostCfgParams.insert(PARAM_ID_LTE_GOST_IP_PORT);
  AddSubscription(subscriptions,SI_LTE_GOST_CFG_PARAMETERS,ENTITY_SM,fapDn,mibGostCfgParams);
  hdlrMap.insert(std::make_pair
        ((u16)SI_LTE_GOST_CFG_PARAMETERS,
         &SmApplication::HandleGostCfgParams));

   MibAttributeIds mibLteRemScanAttributes;
   mibLteRemScanAttributes.insert(PARAM_ID_LTE_REM_SCAN_STATUS);
   mibLteRemScanAttributes.insert(PARAM_ID_LTE_REM_SCAN_ON_BOOT);
   mibLteRemScanAttributes.insert(PARAM_ID_LTE_IN_SERVICE_HANDLING);
   mibLteRemScanAttributes.insert(PARAM_ID_LTE_PERIODIC_SCAN_MODE);
   mibLteRemScanAttributes.insert(PARAM_ID_LTE_PERIODIC_INTERVAL);
   mibLteRemScanAttributes.insert(PARAM_ID_LTE_PERIODIC_TIME);

   MibDN remDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE);

   AddSubscription(subscriptions, SI_LTE_REM_SCAN_ATTRIBUTES,
         ENTITY_SM, remDn, mibLteRemScanAttributes);

   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_REM_SCAN_ATTRIBUTES,
          &SmApplication::HandleRemScanStatus));

   MibAttributeIds mibFapRemAttributes;
   mibFapRemAttributes.insert(PARAM_ID_LTE_MAX_REM_ENTRIES);
   mibFapRemAttributes.insert(PARAM_ID_LTE_NUM_REM_ENTRIES);
   AddSubscription(subscriptions, SI_FAP_REM_SCAN_ATTRIBUTES,
         ENTITY_SM, fapDn, mibFapRemAttributes);

   u16 subId = SI_REM_LTE_CELL_PARAMETERS;
   for(u32 rem_lte=0;rem_lte < MAX_NEIGHBOR_CELLS ; rem_lte++)
   {
      MibAttributeIds remLteCellParameters;
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_EARFCN);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_PCI);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_RSRP);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_RSRQ);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_RSSI);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_DL_BANDWIDTH);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_UL_BANDWIDTH);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_RS_TX_POWER);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_TAC);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_CELL_IDENTITY);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_CELL_BARRED);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_CSG_INDICATOR);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_CSG_ID);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_NUM_OF_PLMN_ENTRIES);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_PLMNID);
      remLteCellParameters.insert(
            PARAM_ID_LTE_REM_SCANNED_CELL_RESERVE_FOR_OPERATOR);
      remLteCellParameters.insert(PARAM_ID_LTE_REM_SCANNED_CSG_ID);
      remLteCellParameters.insert(PARAM_ID_LTE_X_RADISYS_REM_SCANNED_QOFFSET);
      remLteCellParameters.insert(PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CIO);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_BLACKLISTED);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CSG_ACCESS_MODE);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_NUM_ANTENNA);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_ULDL_SUB_FRAME_CFG);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_SPL_SF_CFG);
      remLteCellParameters.insert(PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CP_DL);
      remLteCellParameters.insert(PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CP_UL);
      remLteCellParameters.insert(PARAM_ID_LTE_X_RADISYS_REM_SCANNED_UL_EARFCN);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_IS_PRACH_CFG_PRESENT);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_ROOT_SEQ_INDEX);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_ZERO_CORRELATIONZONE_CONFIG);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_CONFIG_INDEX);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_HIGH_SPEED_FLAG);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_FREQ_OFFSET);
      remLteCellParameters.insert(
            PARAM_ID_LTE_X_RADISYS_REM_SCANNED_INTRA_FREQ_NEIGH_PCI);

      MibDN remLteMO = MibDN::GenerateMibDN(
            MIB_OBJECT_CLASS_LTE_REM_SCANNED_CELL,rem_lte);
      AddSubscription(subscriptions, subId, ENTITY_SM,remLteMO,
            remLteCellParameters);
      subId++;
   }

   MibAttributeIds mibWcdmaRemNumOfCellsAttributes;
   mibWcdmaRemNumOfCellsAttributes.insert(PARAM_ID_NUM_CELL_ENTRIES);

   AddSubscription(subscriptions,SI_WCDMA_REM_SCAN_CELL_CNT_ATTRIBUTES,
         ENTITY_SM,fapDn,mibWcdmaRemNumOfCellsAttributes);

   MibAttributeIds mibSecGwServerParameters;
   mibSecGwServerParameters.insert(PARAM_ID_LTE_SEC_GW_SERVER_1);
   mibSecGwServerParameters.insert(PARAM_ID_LTE_SEC_GW_SERVER_2);
   mibSecGwServerParameters.insert(PARAM_ID_LTE_SEC_GW_SERVER_3);

   AddSubscription(subscriptions,SI_LTE_SEC_GW_PARAMETERS,
         ENTITY_SM,fapDn,mibSecGwServerParameters);

#ifdef LTE_ADV
   MibAttributeIds mibCaParams;
   mibCaParams.insert(PARAM_ID_LTE_X_RADISYS_CA_ENABLE);
   mibCaParams.insert(PARAM_ID_LTE_X_RADISYS_CA_FREQ_CONTG);
   AddSubscription(subscriptions, SI_LTE_CA_PARAMS, ENTITY_SM,
         fapDn,mibCaParams);
   TRACE_PRINTF("%s:%d calling HandleCaParam func",__FUNCTION__,__LINE__);	

   hdlrMap.insert(std::make_pair
         ((u16)SI_LTE_CA_PARAMS,
          &SmApplication::HandleCaParams));
#endif
   /* Cell specificd parameter subscriptions */
   for (cellIdx=0; cellIdx < numOfCells; cellIdx++)
   {
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

      MibAttributeIds mibTdsCdmaNghParam;
      mibTdsCdmaNghParam.insert(PARAM_ID_LTE_TDS_CDMA_MAX_UMTSTDD_ENTRIES);
      mibTdsCdmaNghParam.insert(PARAM_ID_LTE_TDS_CDMA_CELL_SRC);
      mibTdsCdmaNghParam.insert(
            PARAM_ID_LTE_TDS_CDMA_MAX_UTRANTDD_FREQ_ENTRIES);
      mibTdsCdmaNghParam.insert(PARAM_ID_LTE_TDS_CDMA_FREQ_SRC);

      AddSubscription(subscriptions, SI_LTE_TD_SCDMA_NGH_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibTdsCdmaNghParam);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_TD_SCDMA_NGH_PARAMETERS,
             &SmApplication::HandlerEmpty));

      MibAttributeIds mibCdmaBandClassParameters;
      mibCdmaBandClassParameters.insert(PARAM_ID_LTE_CDMA2K_MAX_CDMA2K_BAND);
      mibCdmaBandClassParameters.insert(PARAM_ID_LTE_CDMA2K_NUM_CDMA2K_BAND);
      mibCdmaBandClassParameters.insert(PARAM_ID_LTE_CDMA2K_BAND_CLASS);
      mibCdmaBandClassParameters.insert(PARAM_ID_LTE_CDMA2K_CELL_RESEL_PRIOR);
      mibCdmaBandClassParameters.insert(PARAM_ID_LTE_CDMA2K_THRESH_X_HIGH);
      mibCdmaBandClassParameters.insert(PARAM_ID_LTE_CDMA2K_THRESH_X_LOW);
      AddSubscription(subscriptions, SI_CDMA_BAND_CLASS_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibCdmaBandClassParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_CDMA_BAND_CLASS_PARAMETERS,
             &SmApplication::HandlerEmpty));

      MibAttributeIds mibNbrFreqSrcParameters;
      mibNbrFreqSrcParameters.insert(PARAM_ID_LTE_MAX_CARRIER_ENTRIES_IDLE);
      mibNbrFreqSrcParameters.insert(PARAM_ID_LTE_X_RADISYS_NEIGH_FREQ_SRC);
      AddSubscription(subscriptions, SI_LTE_NBR_FREQ_SRC_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibNbrFreqSrcParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_NBR_FREQ_SRC_PARAMETERS,
             &SmApplication::HandlerEmpty));

      MibAttributeIds mibGeranNghParam;
      mibGeranNghParam.insert(PARAM_ID_LTE_GERAN_MAX_FREQ_ENTRIES);
      mibGeranNghParam.insert(PARAM_ID_LTE_GERAN_MAX_CELL_ENTRIES);
      mibGeranNghParam.insert(PARAM_ID_LTE_GERAN_MAX_CELL_IN_USE_ENTRIES);
      mibGeranNghParam.insert(PARAM_ID_LTE_GERAN_NUM_CELL_IN_USE_ENTRIES);
      mibGeranNghParam.insert(PARAM_ID_LTE_GERAN_CELL_SRC);
      mibGeranNghParam.insert(PARAM_ID_LTE_GERAN_FREQ_SRC);
      AddSubscription(subscriptions, SI_LTE_GERAN_NGH_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibGeranNghParam);

      MibAttributeIds mibNghNumParam;
      mibNghNumParam.insert(PARAM_ID_LTE_NUM_UTRA_NEIGH_CELLS_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_MAX_UMTS_IN_USE_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_UMTS_IN_USE_NUMBER_OF_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_MAX_UMTS_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_MAX_UTRANFDD_FREQ_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_NUM_UTRA_NEIGH_FREQ_ENTRIES); 
      mibNghNumParam.insert(PARAM_ID_LTE_UMTS_NUMBER_OF_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_CELL_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC);
      mibNghNumParam.insert(PARAM_ID_LTE_MAX_LTE_CELL);
      mibNghNumParam.insert(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_ENTRIES);
      mibNghNumParam.insert(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_MAX_LTE_CELL);

      AddSubscription(subscriptions, SI_LTE_NBR_FREQ_NUM_INSTNCE_PARMATERS +
            CELLSUBID, ENTITY_SM, fapLteDn,mibNghNumParam);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_NBR_FREQ_NUM_INSTNCE_PARMATERS,
             &SmApplication::HandlerEmpty));

      MibAttributeIds mibLteCellSib1CfgGrpParameters;
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_PMAX);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_FREQ_BAND_INDICATOR);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_QRX_LEVEL_MIN_SIB1);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_QRX_LEVEL_MIN_OFFSET);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_TAC);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_CELL_IDENTITY);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_CELL_BARRED);
      mibLteCellSib1CfgGrpParameters.insert(PARAM_ID_LTE_CSG_ID);

      AddSubscription(subscriptions, SI_LTE_CELL_SIB1_CONFIG_GROUP_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellSib1CfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_SIB1_CONFIG_GROUP_PARAMETERS,
             &SmApplication::HandleLteCellSib1CfgGroupParameters));

      MibAttributeIds mibLteAddCellCfgParameters;
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_PHY_CELLID_LIST);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_SMALLCELL_START_PCI);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_SMALLCELL_PCI_RANGE);
      mibLteAddCellCfgParameters.insert(
            PARAM_ID_LTE_EMERGENCY_SERVICE_PRIORITY_LEVEL);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_CELL_SIZE_TYPE);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_EARFCNDL_LIST);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_EARFCNUL_LIST);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_MIN_DL_RES_NONCSGUSER);
      mibLteAddCellCfgParameters.insert(PARAM_ID_LTE_MIN_UL_RES_NONCSGUSER);

      AddSubscription(subscriptions, SI_LTE_ADD_CELL_CONFIG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteAddCellCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_ADD_CELL_CONFIG_PARAMETERS,
             &SmApplication::HandleLteAddCellCfgParameters));

      MibAttributeIds mibfreqSyncParams;
      mibfreqSyncParams.insert(PARAM_ID_LTE_FREQ_SYNC_PCI);
      mibfreqSyncParams.insert(PARAM_ID_LTE_FREQ_SYNC_EARFCN);
      AddSubscription(subscriptions,SI_LTE_FREQ_SYNC_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibfreqSyncParams);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_FREQ_SYNC_PARAMETERS,
             &SmApplication::HandleLteFreqSyncParameters));

      MibAttributeIds mibRsysTpmCfgParam;
      mibRsysTpmCfgParam.insert(PARAM_ID_LTE_ENB_RSYS_TPM_TGT_RSRP);
      mibRsysTpmCfgParam.insert(PARAM_ID_LTE_ENB_RSYS_TPM_RSRP_ATTN_CONST);
      mibRsysTpmCfgParam.insert(PARAM_ID_LTE_ENB_RSYS_TPM_MIN_RSRP);
      mibRsysTpmCfgParam.insert(PARAM_ID_LTE_ENB_RSYS_TPM_MAX_RSRP);

      AddSubscription(subscriptions,SI_LTE_RSYS_TPM_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibRsysTpmCfgParam);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RSYS_TPM_PARAMETERS,
             &SmApplication::HandleRsysTpmParam));

      MibAttributeIds mibLtePrachCfgCommonParameters;
      mibLtePrachCfgCommonParameters.insert(PARAM_ID_LTE_HIGH_SPEED_FLAG);
      mibLtePrachCfgCommonParameters.insert(
            PARAM_ID_LTE_PRACH_ROOT_SEQUENCE_INDEX_LIST);
      mibLtePrachCfgCommonParameters.insert(
            PARAM_ID_LTE_PRACH_CONFIG_INDEX_LIST);
      mibLtePrachCfgCommonParameters.insert(
            PARAM_ID_LTE_PRACH_ZERO_CORRELATIONZONE_CONFIG_LIST);
      mibLtePrachCfgCommonParameters.insert(
            PARAM_ID_LTE_PRACH_FREQ_OFFSET_LIST);

      AddSubscription(subscriptions,(SI_LTE_PRACH_CONFIG_COMMON_PARAMETERS +
               CELLSUBID),
            ENTITY_SM, fapLteDn, mibLtePrachCfgCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PRACH_CONFIG_COMMON_PARAMETERS,
             &SmApplication::HandleLtePrachCfgCommonParameters));

      MibAttributeIds mibLteRachConfigCommonParameters;
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_NUM_OF_RAPREAMBLES);
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_SIZE_OF_RAGROUP_A);
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_MSG_SIZE_GROUP_A);
      mibLteRachConfigCommonParameters.insert(
            PARAM_ID_LTE_POWER_OFFSET_GROUP_B);
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_POWER_RAMPING);
      mibLteRachConfigCommonParameters.insert(
            PARAM_ID_LTE_PREAMBLE_INIT_TARGET_POWER);
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_PREAMBLE_TRANS_MAX);
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_RSP_WINDOW_SIZE);
      mibLteRachConfigCommonParameters.insert(
            PARAM_ID_LTE_CONTENTION_RESOLUTION_TMR);
      mibLteRachConfigCommonParameters.insert(PARAM_ID_LTE_MAX_HARQ_MSG3_TX);

      AddSubscription(subscriptions, SI_LTE_RACH_CONFIG_COMMON_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteRachConfigCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RACH_CONFIG_COMMON_PARAMETERS,
             &SmApplication::HandleLteRachConfigCommonParameters));

      MibAttributeIds mibLtePdschCfgCommonParameters;
      mibLtePdschCfgCommonParameters.insert(PARAM_ID_LTE_REFERNCE_SIG_POWER);
      mibLtePdschCfgCommonParameters.insert(PARAM_ID_LTE_PB);

      AddSubscription(subscriptions, SI_LTE_PDSCH_CONFIG_COMMON_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLtePdschCfgCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PDSCH_CONFIG_COMMON_PARAMETERS,
             &SmApplication::HandleLtePdschConfigCommonParameters));

      MibAttributeIds mibLteUlPwrCtrlCommonParameters;
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_PO_NOMINAL_PUSCH);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_ALPHA);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_PO_NOMINAL_PUCCH);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_DELTAF_PUCCH_FRMT1);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_DELTAF_PUCCH_FRMT1B);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_DELTAF_PUCCH_FRMT2);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_DELTAF_PUCCH_FRMT2A);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_DELTAF_PUCCH_FRMT2B);
      mibLteUlPwrCtrlCommonParameters.insert(PARAM_ID_LTE_DELTA_PREAMBLE_MSG3);

      AddSubscription(subscriptions, SI_LTE_UL_POWER_CONTROL_COMMON_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteUlPwrCtrlCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_UL_POWER_CONTROL_COMMON_PARAMETERS,
             &SmApplication::HandleLteUlPwrCtrlCommonParameters));

      MibAttributeIds mibLteUlFrequencyInfoParameters;
      mibLteUlFrequencyInfoParameters.insert(PARAM_ID_LTE_UL_BANDWIDTH);
      mibLteUlFrequencyInfoParameters.insert(PARAM_ID_LTE_EARFCNUL_LIST);

      AddSubscription(subscriptions, SI_LTE_UL_FREQUENCY_INFO_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteUlFrequencyInfoParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_UL_FREQUENCY_INFO_PARAMETERS,
             &SmApplication::HandleLteULFrequencyInfoParameters));

      MibAttributeIds mibLteCellSib3CfgGrpParameters;
      mibLteCellSib3CfgGrpParameters.insert(PARAM_ID_LTE_QHYST);
      mibLteCellSib3CfgGrpParameters.insert(PARAM_ID_LTE_QHYST_SF_MEDIUM);
      mibLteCellSib3CfgGrpParameters.insert(PARAM_ID_LTE_QHYST_SF_HIGH);
      mibLteCellSib3CfgGrpParameters.insert(PARAM_ID_LTE_T_EVALUATION);
      mibLteCellSib3CfgGrpParameters.insert(PARAM_ID_LTE_THYST_NORMAL);
      mibLteCellSib3CfgGrpParameters.insert(
            PARAM_ID_LTE_NUM_CELL_CHANGE_MEDIUM);
      mibLteCellSib3CfgGrpParameters.insert(PARAM_ID_LTE_NUM_CELL_CHANGE_HIGH);

      AddSubscription(subscriptions, SI_LTE_CELL_SIB3_CONFIG_GROUP_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellSib3CfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_SIB3_CONFIG_GROUP_PARAMETERS,
             &SmApplication::HandleLteCellSib3CfgGroupParameters));

      MibAttributeIds mibLtePuschBasicCfgCommonParameters;
      mibLtePuschBasicCfgCommonParameters.insert(PARAM_ID_LTE_NSB);
      mibLtePuschBasicCfgCommonParameters.insert(PARAM_ID_LTE_HOPPING_MODE);
      mibLtePuschBasicCfgCommonParameters.insert(PARAM_ID_LTE_HOPPING_OFFSET);
      mibLtePuschBasicCfgCommonParameters.insert(PARAM_ID_LTE_ENA_64QAM);

      AddSubscription(subscriptions, SI_LTE_PUSCH_BASIC_CFG_COMMON_PARAMETERS +
            CELLSUBID,ENTITY_SM, fapLteDn, mibLtePuschBasicCfgCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PUSCH_BASIC_CFG_COMMON_PARAMETERS,
             &SmApplication::HandleLtePuschBasicCfgCommonParameters));

      MibAttributeIds mibLtePuschRefSignalCfgParameters;
      mibLtePuschRefSignalCfgParameters.insert(PARAM_ID_LTE_GROUP_HOPPING_ENA);
      mibLtePuschRefSignalCfgParameters.insert(
            PARAM_ID_LTE_GROUP_ASSIGNMENT_PUSCH);
      mibLtePuschRefSignalCfgParameters.insert(PARAM_ID_LTE_SEQ_HOPPING_ENA);
      mibLtePuschRefSignalCfgParameters.insert(PARAM_ID_LTE_CYCLIC_SHIFT);

      AddSubscription(subscriptions, SI_LTE_PUSCH_REF_SIGNAL_CFG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLtePuschRefSignalCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PUSCH_REF_SIGNAL_CFG_PARAMETERS,
             &SmApplication::HandleLtePuschRefSignalCfgParameters));

      MibAttributeIds mibLtePucchCfgCommonParameters;
      mibLtePucchCfgCommonParameters.insert(PARAM_ID_LTE_DELTA_PUCCH_SHIFT);
      mibLtePucchCfgCommonParameters.insert(PARAM_ID_LTE_NRBCQI);
      mibLtePucchCfgCommonParameters.insert(PARAM_ID_LTE_NCSAN);
      mibLtePucchCfgCommonParameters.insert(PARAM_ID_LTE_N1PUCCHAN);

      AddSubscription(subscriptions, SI_LTE_PUCCH_CFG_COMMON_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLtePucchCfgCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PUCCH_CFG_COMMON_PARAMETERS,
             &SmApplication::HandleLtePucchCfgCommonParameters));

      MibAttributeIds mibLteSRSCfgCommonParameters;
      mibLteSRSCfgCommonParameters.insert(PARAM_ID_LTE_SRS_ENA);
      mibLteSRSCfgCommonParameters.insert(PARAM_ID_LTE_SRS_BANDWIDTH_CFG);
      mibLteSRSCfgCommonParameters.insert(
            PARAM_ID_LTE_ACK_NACK_SRS_TRNASMISSION);
      mibLteSRSCfgCommonParameters.insert(PARAM_ID_LTE_SRS_MAX_UP_PTS);

      AddSubscription(subscriptions, SI_LTE_SRS_CFG_COMMON_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteSRSCfgCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_SRS_CFG_COMMON_PARAMETERS,
             &SmApplication::HandleLteSRSCfgCommonParameters));

      MibAttributeIds mibLteUeTimerConstantsParameters;
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T300);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T301);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T302);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T304EUTRA);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T304IRAT);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T310);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T311);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_T320);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_N310);
      mibLteUeTimerConstantsParameters.insert(PARAM_ID_LTE_N311);

      AddSubscription(subscriptions, SI_LTE_UE_TIMER_CONSTANTS_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteUeTimerConstantsParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_UE_TIMER_CONSTANTS_PARAMETERS,
             &SmApplication::HandleLteUeTimerConstantsParameters));

      MibAttributeIds mibLteCellSib9CfgGrpParameters;
      mibLteCellSib9CfgGrpParameters.insert(PARAM_ID_LTE_HOME_NODEB_NAME);

      AddSubscription(subscriptions, SI_LTE_CELL_SIB9_CFG_GRP_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellSib9CfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_SIB9_CFG_GRP_PARAMETERS,
             &SmApplication::HandleLteCellSib9CfgGrpParameters));

      MibAttributeIds mibLteCellSib6CfgGrpParameters;
      mibLteCellSib6CfgGrpParameters.insert(PARAM_ID_LTE_T_RESELECTION_UTRA);
      mibLteCellSib6CfgGrpParameters.insert(
            PARAM_ID_LTE_T_RESELECTION_UTRA_SF_MED);
      mibLteCellSib6CfgGrpParameters.insert(
            PARAM_ID_LTE_T_RESELECTION_UTRA_SF_HIGH);

      AddSubscription(subscriptions, SI_LTE_CELL_SIB6_CONFIG_GROUP_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellSib6CfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_SIB6_CONFIG_GROUP_PARAMETERS,
             &SmApplication::HandleLteCellSib6CfgGroupParameters));

      MibAttributeIds mibLteAcBarringInfoParameters;
      mibLteAcBarringInfoParameters.insert(PARAM_ID_LTE_BARRING_FOR_EMERGENCY);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_TIME_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_ENABLE_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_ENABLE_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MOSIG);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_TIME_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MODATA);
      mibLteAcBarringInfoParameters.insert(
            PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MODATA);

      AddSubscription(subscriptions,SI_LTE_AC_BARRING_INFO_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteAcBarringInfoParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_AC_BARRING_INFO_PARAMETERS,
             &SmApplication::HandleLteAcBarringInfoParameters));

      MibAttributeIds mibLteSib4CsgInfoParameters;
      mibLteSib4CsgInfoParameters.insert(PARAM_ID_LTE_CSG_START_PCI);
      mibLteSib4CsgInfoParameters.insert(PARAM_ID_LTE_CSG_PCI_RANGE);
      mibLteSib4CsgInfoParameters.insert(PARAM_ID_LTE_PCI_RANGE2_OFFSET);

      AddSubscription(subscriptions, SI_LTE_SIB4_CSG_INFO_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteSib4CsgInfoParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_SIB4_CSG_INFO_PARAMETERS,
             &SmApplication::HandleLteSib4CsgInfoParameters));

      MibAttributeIds mibLteTddParameters;
      mibLteTddParameters.insert(PARAM_ID_LTE_TDD_MAX_SFCONFIG_LIST_ENTRIES);
      mibLteTddParameters.insert(
            PARAM_ID_LTE_TDD_SFCONFIG_LIST_NUMBER_OF_ENTRIES);
      mibLteTddParameters.insert(PARAM_ID_LTE_TDD_SYNC_STRATUM_ID);
      mibLteTddParameters.insert(PARAM_ID_LTE_TDD_SUBFRAME_ASSIGNMENT);
      mibLteTddParameters.insert(PARAM_ID_LTE_TDD_SPECIAL_SUB_FRAME_PATTERNS);

      AddSubscription(subscriptions, SI_LTE_TDD_PARAMETERS+CELLSUBID, ENTITY_SM,
            fapLteDn, mibLteTddParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_TDD_PARAMETERS,
             &SmApplication::HandleLteTddParameters));

      MibAttributeIds mibLtePCCHCfgCommonParameters;
      mibLtePCCHCfgCommonParameters.insert(PARAM_ID_LTE_DEFAULT_PAGING_CYCLE);
      mibLtePCCHCfgCommonParameters.insert(PARAM_ID_LTE_DEFAULT_PCCH_CFG_NB);

      AddSubscription(subscriptions, SI_LTE_PCCH_CONFIG_COMMON_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLtePCCHCfgCommonParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PCCH_CONFIG_COMMON_PARAMETERS,
             &SmApplication::HandleLtePcchConfigCommonParameters));

      MibAttributeIds mibBarringConfig1xRTTCfg;
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_0TO9_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_10_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_11_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_12_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_13_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_14_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_15_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_MSG_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_REG_R9);
      mibBarringConfig1xRTTCfg.insert(PARAM_ID_LTE_CDMA2K_AC_BRNG_EMG_R9);

      AddSubscription(subscriptions, SI_BARRING_CFG_1XRTT+CELLSUBID, ENTITY_SM,
            fapLteDn, mibBarringConfig1xRTTCfg);

      hdlrMap.insert(std::make_pair
            ((u16)SI_BARRING_CFG_1XRTT,
             &SmApplication::HandleBarringConfig1xRTTCfg));

      MibAttributeIds mibSib8Parameters;
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SPEED_STATE_PRES);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_CDMA_EUTRA_TIME_SYNC);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_SID);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_NID);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_MUL_SID);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_MUL_NID);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_HOME_REG);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_FOREIGN_SID_REG);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_FOREIGN_NID_REG);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_PARAM_REG);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_PWR_UP_REG);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_REG_PERIOD);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_REG_ZONE);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_TOTAL_ZONE);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_ZONE_TIMER);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_SIB8_PWR_DOWN_REG);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_T_RESEL_CDMA2K);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_T_RESEL_CDMA2K_SF_MED);
      mibSib8Parameters.insert(PARAM_ID_LTE_CDMA2K_T_RESEL_CDMA2K_SF_HIGH);

      AddSubscription(subscriptions, SI_SIB8_PARAMETERS+CELLSUBID, ENTITY_SM,
            fapLteDn, mibSib8Parameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_SIB8_PARAMETERS,
             &SmApplication::HandleSib8Parameters));

      MibAttributeIds mibSib7CfgParameters;
      mibSib7CfgParameters.insert(PARAM_ID_LTE_GERAN_T_RESEL);
      mibSib7CfgParameters.insert(PARAM_ID_LTE_GERAN_PRES_SPEED_SCALE);
      mibSib7CfgParameters.insert(PARAM_ID_LTE_GERAN_T_RESEL_SF_MED);
      mibSib7CfgParameters.insert(PARAM_ID_LTE_GERAN_T_RESEL_SF_HIGH);

      AddSubscription(subscriptions, SI_LTE_SIB7_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibSib7CfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_SIB7_PARAMETERS,
             &SmApplication::HandleSib7CfgParameters));

      MibAttributeIds mibTimeAlignmentCfgParameters;
      mibTimeAlignmentCfgParameters.insert(
            PARAM_ID_LTE_TIME_ALIGNMENT_TIMER_COMMON);
      mibTimeAlignmentCfgParameters.insert(
            PARAM_ID_LTE_TIME_ALIGNMENT_TIMER_DEDICATED);

      AddSubscription(subscriptions, SI_TIME_ALGMT_CFG_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, mibTimeAlignmentCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_TIME_ALGMT_CFG_PARAMETERS,
             &SmApplication::HandleTimeAlgmtCfgParameters));

      MibAttributeIds mibLteEnbProtoCfgParameters;
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_X2SIG_LINK_PORT);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_HOME_NODEB_NAME);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_MAX_PLMN_ENTRIES);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_NUM_OF_PLMN_ENTRIES);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_CELL_PLMN_SRC);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_UE_INACTIVITY_TIMER_VAL);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_UE_END_MARKER_TIMER_VAL);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_MAX_EXPIRY_COUNT);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_ETWS_CMAS_ENABLE);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_CSFB_PLMN_RAT_PRIOR);
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_X_RADISYS_NUM_OF_CELLS);
#ifdef TIP_OAM
      mibLteEnbProtoCfgParameters.insert(PARAM_ID_LTE_X_TIP_NUM_OF_CELLS);
#endif

      AddSubscription(subscriptions, SI_LTE_ENB_PROTO_CFG_PARAMETERS+CELLSUBID, ENTITY_SM, fapLteDn, mibLteEnbProtoCfgParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_ENB_PROTO_CFG_PARAMETERS,
             &SmApplication::HandleLteEnbProtoCfgParameters));

      MibAttributeIds mibLteRimParameters;
      mibLteRimParameters.insert(PARAM_ID_LTE_RIM_TIMER_RIR_VALUE);
      mibLteRimParameters.insert(PARAM_ID_LTE_RIM_TIMER_RI_VALUE);
      mibLteRimParameters.insert(PARAM_ID_LTE_RIM_RAE_VALUE);
      mibLteRimParameters.insert(PARAM_ID_LTE_RIM_MAX_RETRY_COUNT);
      mibLteRimParameters.insert(PARAM_ID_LTE_RIM_OVERALL_TIMER_VALUE);
      AddSubscription(subscriptions, SI_LTE_RIM_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteRimParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RIM_PARAMETERS,
             &SmApplication::HandleLteRimParameters));

      MibAttributeIds mibLteSelfConfigParameters;
      mibLteSelfConfigParameters.insert(
            PARAM_ID_LTE_SELFCONFIG_PHY_CELLID_ENABLE);
      mibLteSelfConfigParameters.insert(PARAM_ID_LTE_SON_TX_POWER_ENABLE);
      mibLteSelfConfigParameters.insert(PARAM_ID_LTE_SELFCONFIG_PRACH_ENABLE);
      mibLteSelfConfigParameters.insert(PARAM_ID_LTE_SELFCONFIG_EARFCN_ENABLE);
      mibLteSelfConfigParameters.insert(PARAM_ID_LTE_SON_VENDOR);
      AddSubscription(subscriptions, SI_LTE_SELF_CONFIG_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteSelfConfigParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_SELF_CONFIG_PARAMETERS,
             &SmApplication::HandleLteSelfConfigParameters));

      MibAttributeIds mibLtePowerOffsetParameters;
      mibLtePowerOffsetParameters.insert(PARAM_ID_LTE_PSCH_POWER_OFFSET);
      mibLtePowerOffsetParameters.insert(PARAM_ID_LTE_SSCH_POWER_OFFSET);
      mibLtePowerOffsetParameters.insert(PARAM_ID_LTE_PBCH_POWER_OFFSET);

      AddSubscription(subscriptions, SI_LTE_POWER_OFFSET_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibLtePowerOffsetParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_POWER_OFFSET_PARAMETERS,
             &SmApplication::HandleLtePowerOffsetParameters));

      MibAttributeIds mibLteCellSchdPowerParameters;
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUCCH_POWER_FORMAT_3_RNTI);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUCCH_POWER_FORMAT_3_SIZE);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUCCH_POWER_FORMAT_3A_RNTI);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUCCH_POWER_FORMAT_3A_SIZE);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUSCH_POWER_FORMAT_3_RNTI);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUSCH_POWER_FORMAT_3_SIZE);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUSCH_POWER_FORMAT_3A_RNTI);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_PUSCH_POWER_FORMAT_3A_SIZE);
      mibLteCellSchdPowerParameters.insert(PARAM_ID_LTE_PUCCH_PWR_FMT3A_ENABLE);
      mibLteCellSchdPowerParameters.insert(PARAM_ID_LTE_PUSCH_PWR_FMT3A_ENABLE);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_IS_UL_GRP_PWR_CONTROL_PUCCH_ENABLE);
      mibLteCellSchdPowerParameters.insert(
            PARAM_ID_LTE_IS_UL_GRP_PWR_CONTROL_PUSCH_ENABLE);

      AddSubscription(subscriptions, SI_LTE_CELL_SCHD_POWER_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellSchdPowerParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_SCHD_POWER_PARAMETERS,
             &SmApplication::HandleLteCellSchdPowerParameters));

      MibAttributeIds mibLteFapControParameters;
      mibLteFapControParameters.insert(
            PARAM_ID_LTE_CONNECTION_IN_SERVICE_HANDLING);
      mibLteFapControParameters.insert(PARAM_ID_LTE_MAX_CAPACITY_USER_ACCOUNT);
      mibLteFapControParameters.insert(PARAM_ID_LTE_MAX_CAPACITY_RATE);
      mibLteFapControParameters.insert(PARAM_ID_LTE_HANDOVER_ON_EMERGENCY);
      mibLteFapControParameters.insert(PARAM_ID_LTE_FAP_COVERAGE_TARGET);
      mibLteFapControParameters.insert(
            PARAM_ID_LTE_SERVICE_HANDLING_DEFERRED_TIMER);
      mibLteFapControParameters.insert(PARAM_ID_LTE_MIN_RB_ALLOCATION_USER);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ENABLE_X2);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ANR_EPOCH_PERIOD);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ANR_TRICE_PERIOD);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ANR_CELL_VALID_AGE);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ANR_DRX_LONG_CYCLE);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ANR_DRX_ON_DURATION_TMR);
      mibLteFapControParameters.insert(PARAM_ID_LTE_ANR_DRX_INACTIVITY_TMR);
      mibLteFapControParameters.insert(PARAM_ID_LTE_SPECIAL_ACCESS_CLASS);

      AddSubscription(subscriptions, SI_LTE_FAP_CONTROL_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteFapControParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_FAP_CONTROL_PARAMETERS,
             &SmApplication::HandleLteFapControParameters));

      int subId = SI_CELL_PLMN_LIST_PARAMETERS + CELLSUBID;
      for(int cellPlmnList=0; cellPlmnList < NUM_MAX_PLMN; cellPlmnList++)
      {
         MibAttributeIds mibCellPlmnParameters;
         mibCellPlmnParameters.insert(PARAM_ID_LTE_OAM_PLMNID);
         mibCellPlmnParameters.insert(
               PARAM_ID_LTE_OAM_CELL_RESERVE_FOR_OPERATOR);
         mibCellPlmnParameters.insert(PARAM_ID_LTE_OAM_PRIMARY_PLMN);
         mibCellPlmnParameters.insert(PARAM_ID_LTE_EPC_PLMN_ENABLE);
         mibCellPlmnParameters.insert(PARAM_ID_LTE_REDIRECTION_SUPPORT);
         MibDN plmnMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_CELL_PLMN_LIST, cellPlmnList);
         AddSubscription(subscriptions, subId, ENTITY_SM, plmnMO,
               mibCellPlmnParameters);
         subId++;
      }
      hdlrMap.insert(std::make_pair
            ((u16)SI_CELL_PLMN_LIST_PARAMETERS,
             &SmApplication::HandleCellPlmnListParameters));

      MibAttributeIds mibLteDrxCfgParameters;
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_DRX_ENABLE);
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_DRX_QCI_ENABLE);
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_ON_DURATION_TIMER);
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_DRX_INACTIVITY_TIMER);
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_DRX_RETRANSMISSION_TIMER);
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_LONG_DRX_CYCLE_GBR);
      mibLteDrxCfgParameters.insert(PARAM_ID_LTE_LONG_DRX_CYCLE_NON_GBR);

      AddSubscription(subscriptions, SI_LTE_DRX_CONFIG_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteDrxCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_DRX_CONFIG_PARAMETERS,
             &SmApplication::HandleLteDrxCfgParameters));

      MibAttributeIds mibLteCellMeasCfgGrpParameters;
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_HYSTERESIS);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_TIME_TO_TRIGGER);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_TRIGGER_QUANTITY);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_QUANTITY);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_MAX_REPORT_CELLS);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_INTERVAL);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_AMOUNT);
      /* A1 Event parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A1_THRESHOLD_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A1_THRESHOLD_RSRQ);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A1_REPORT_AMOUNT);
      /* A2 Event parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A2_THRESHOLD_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A2_THRESHOLD_RSRQ);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A2_REPORT_AMOUNT);
      /* A3 Event parameters */
#ifdef TIP_OAM
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A3_OFFSET);
#endif
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_INTRA_HO_A3_OFFSET);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_INTRA_ANR_A3_OFFSET);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A3_REPORT_AMOUNT);
      /* A4 Event parameters */
#ifdef LTE_ADV
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A4_THRESHOLD_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_X_RADISYS_MEAS_SCELL_ADD_REL);
#endif /*LTE_ADV*/
      /* A5 Event parameters */
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_INTRA_A5_THRESHOLD_1_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_INTRA_A5_THRESHOLD_2_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_INTER_A5_THRESHOLD_1_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_INTER_A5_THRESHOLD_2_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_1_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_2_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A5_REPORT_AMOUNT);
      /* B2 Event parameters */
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD2_UTRA_RSCP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD2_UTRA_ECNO);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_B2_THRESHOLD2_GERAN);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_HYSTERESIS_IRAT);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_TIME_TO_TRIGGER_IRAT);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_MAX_REPORT_CELLS_IRAT);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_INTERVAL_IRAT);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_AMOUNT_IRAT);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD1_UTRA_RSRP_HO);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD1_UTRA_RSRQ_HO);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_TDS_CDMA_B2_THRSH2_UTRATDD_RSCP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRP_REDIR);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRQ_REDIR);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD2_GERAN_RSSI_HO);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRP_HO);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRQ_HO);
      /* CDMA periodic report parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_MAX_REPORT_CELLS_CDMA);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_INTERVAL_CDMA);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_REPORT_AMOUNT_CDMA);
      /* EUTRAN periodic report parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_PRD_REPORT_AMOUNT);
      /* Speed configuration */
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_TIME_TO_TRIGGER_SF_HIGH);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_TIME_TO_TRIGGER_SF_MEDIUM);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_S_MEASURE);
      /* Quality configuration measurement parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_FILTER_COEFFICIENT);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_FILTER_COEFFICIENT_RSRP);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_FILTER_COEFFICIENT_RSRQ);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_FILTER_COEFFICIENT_UTRA);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_MEAS_QUANTITY_UTRA_FDD);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_MEAS_QUANTITY_CDMA2000);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_GERAN_FILTER_COEFF);
      mibLteCellMeasCfgGrpParameters.insert(
            PARAM_ID_LTE_TDS_CDMA_MEAS_QTY_UTRATDD);
      /* Measurement gap parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_INTER_FREQ_MEAS_GAP);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_ANR_MEAS_GAP_CONFIG);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_INTER_RAT_MEAS_GAP);
      /* Other measurement parameters */
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_A3_SUPPORT_ENABLE);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_HO_REPORT_CFG_VAL);
      mibLteCellMeasCfgGrpParameters.insert(PARAM_ID_LTE_ANR_REPORT_CFG_VAL);

      AddSubscription(subscriptions, SI_LTE_CELL_MEAS_CONFIG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellMeasCfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_MEAS_CONFIG_PARAMETERS,
             &SmApplication::HandleLteCellMeasCfgGrpParameters));

      MibAttributeIds miblteSmCellCfgParameters;
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_INTEGRITY_ALGO_LIST);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_CIPHERING_ALGO_LIST);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_RRM_RNTI_START);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_MAX_RRM_RNTIS);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_RRM_DED_PREMBL_STRT);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_RRM_NO_OF_DED_PREMBL);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_MAC_RNTI_STRT);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_MAX_MAC_RNTIS);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_MAC_NO_OF_PREMBL);
      miblteSmCellCfgParameters.insert(
            PARAM_ID_LTE_X_RADISYS_RRM_MAX_AVG_GBRPRB_USAGE); 
      miblteSmCellCfgParameters.insert(
            PARAM_ID_LTE_X_RADISYS_RRM_QCI_1_TIMING_REQ);
      miblteSmCellCfgParameters.insert(
            PARAM_ID_LTE_X_RADISYS_RRM_NUM_OF_PRB_RPTS); 
      miblteSmCellCfgParameters.insert(
            PARAM_ID_LTE_X_RADISYS_RRM_PRB_RPT_INTERVAL);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_DEFAULT_CFI_CFG);
      miblteSmCellCfgParameters.insert(PARAM_ID_LTE_MAX_X2_PEERS);

      AddSubscription(subscriptions, SI_LTE_SM_CELL_CONFIG_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, miblteSmCellCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_SM_CELL_CONFIG_PARAMETERS,
             &SmApplication::HandleLteSmCfgParameters));

      MibAttributeIds miblteCellMibCfgParameters;
      miblteCellMibCfgParameters.insert(PARAM_ID_LTE_DL_BANDWIDTH);

      AddSubscription(subscriptions, SI_LTE_CELL_MIB_CONFIG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, miblteCellMibCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_MIB_CONFIG_PARAMETERS,
             &SmApplication::HandleLteCellMibCfgParameters));

      MibAttributeIds miblteMacSchCfgParameters;
      miblteMacSchCfgParameters.insert(PARAM_ID_LTE_MAX_HARQ_TX);
      miblteMacSchCfgParameters.insert(PARAM_ID_LTE_PERIODIC_BSR_TIMER);
      miblteMacSchCfgParameters.insert(PARAM_ID_LTE_RETX_BSR_TIMER);
      miblteMacSchCfgParameters.insert(PARAM_ID_LTE_TTI_BUNDLING);

      AddSubscription(subscriptions, SI_LTE_MAC_SCH_CONFIG_PARAMETERS+CELLSUBID,
            ENTITY_SM, fapLteDn, miblteMacSchCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_MAC_SCH_CONFIG_PARAMETERS,
             &SmApplication::HandleLteMacSchCfgParameters));

      MibAttributeIds miblteAntennaCommonCfgParameters;
      miblteAntennaCommonCfgParameters.insert(PARAM_ID_LTE_ANTENNA_PORTS_COUNT);

      AddSubscription(subscriptions, SI_LTE_ANTENNA_COMMON_CONFIG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, miblteAntennaCommonCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_ANTENNA_COMMON_CONFIG_PARAMETERS,
             &SmApplication::HandleLteAntennaCommonCfgParameters));

      MibAttributeIds mibltePdschCfgDedicatedParameters;
      mibltePdschCfgDedicatedParameters.insert(PARAM_ID_LTE_PA);

      AddSubscription(subscriptions, SI_LTE_PDSCH_CONFIG_DEDICATED_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibltePdschCfgDedicatedParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PDSCH_CONFIG_DEDICATED_PARAMETERS,
             &SmApplication::HandleLtePdschCfgDedicatedParameters));

      MibAttributeIds mibLteRabDrbPolicyCfgGrpParameters;
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_IS_DSCP_ENABLE);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI1_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI2_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI3_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI4_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI5_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI6_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI7_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI8_DSCP_MAP);
      mibLteRabDrbPolicyCfgGrpParameters.insert(PARAM_ID_LTE_QCI9_DSCP_MAP);

      AddSubscription(subscriptions, SI_LTE_RAB_DRB_POLICY_CFG_GRP_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteRabDrbPolicyCfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RAB_DRB_POLICY_CFG_GRP_PARAMETERS,
             &SmApplication::HandleLteRabPolicyCfgGrpParameters));

      MibAttributeIds mibLteRabSrb1PolicyCfgGrpParameters;
      mibLteRabSrb1PolicyCfgGrpParameters.insert(PARAM_ID_LTE_DEFAULT_CFG_SRB1);
      mibLteRabSrb1PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_TPOLL_RE_TRANSMIT_SRB1);
      mibLteRabSrb1PolicyCfgGrpParameters.insert(PARAM_ID_LTE_POLL_PDU_SRB1);
      mibLteRabSrb1PolicyCfgGrpParameters.insert(PARAM_ID_LTE_POLL_BYTE_SRB1);
      mibLteRabSrb1PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_MAX_RE_TX_THRESHOLD_SRB1);
      mibLteRabSrb1PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_T_REORDERING_SRB1);
      mibLteRabSrb1PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_TSTATUS_PROHIBIT_SRB1);

      AddSubscription(subscriptions, SI_LTE_RAB_SRB1_POLICY_CFG_GRP_PARAMETERS +
            CELLSUBID,ENTITY_SM, fapLteDn, mibLteRabSrb1PolicyCfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RAB_SRB1_POLICY_CFG_GRP_PARAMETERS,
             &SmApplication::HandleLteSrb1PolicyCfgGrpParameters));

      MibAttributeIds mibLteRabSrb2PolicyCfgGrpParameters;
      mibLteRabSrb2PolicyCfgGrpParameters.insert(PARAM_ID_LTE_DEFAULT_CFG_SRB2);
      mibLteRabSrb2PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_TPOLL_RE_TRANSMIT_SRB2);
      mibLteRabSrb2PolicyCfgGrpParameters.insert(PARAM_ID_LTE_POLL_PDU_SRB2);
      mibLteRabSrb2PolicyCfgGrpParameters.insert(PARAM_ID_LTE_POLL_BYTE_SRB2);
      mibLteRabSrb2PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_MAX_RE_TX_THRESHOLD_SRB2);
      mibLteRabSrb2PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_T_REORDERING_SRB2);
      mibLteRabSrb2PolicyCfgGrpParameters.insert(
            PARAM_ID_LTE_TSTATUS_PROHIBIT_SRB2);

      AddSubscription(subscriptions, SI_LTE_RAB_SRB2_POLICY_CFG_GRP_PARAMETERS +
            CELLSUBID,ENTITY_SM, fapLteDn, mibLteRabSrb2PolicyCfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RAB_SRB2_POLICY_CFG_GRP_PARAMETERS,
             &SmApplication::HandleLteSrb2PolicyCfgGrpParameters));

      MibAttributeIds mibLteCellEAIDCfgGrpParameters;
      mibLteCellEAIDCfgGrpParameters.insert(PARAM_ID_LTE_EAID);

      AddSubscription(subscriptions, SI_LTE_CELL_EAID_CFG_GRP_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellEAIDCfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_EAID_CFG_GRP_PARAMETERS,
             &SmApplication::HandleLteCellEAIDCfgGrpParameters));

      MibAttributeIds mibLteCQIPeriodicReportCfgParameters;
      mibLteCQIPeriodicReportCfgParameters.insert(
            PARAM_ID_LTE_CQI_PUCCH_RESOURCE_IDX);
      mibLteCQIPeriodicReportCfgParameters.insert(PARAM_ID_LTE_K);

      AddSubscription(subscriptions, SI_LTE_CQI_PERIODIC_REPORT_CFG_PARAMETERS +
            CELLSUBID,ENTITY_SM, fapLteDn,mibLteCQIPeriodicReportCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CQI_PERIODIC_REPORT_CFG_PARAMETERS,
             &SmApplication::HandleLteCQIPeriodicReportCfgParameters));

      MibAttributeIds mibCsfbGeranCfgParameters;
      mibCsfbGeranCfgParameters.insert(PARAM_ID_LTE_GERAN_MEAS_WAIT_TMR);
      mibCsfbGeranCfgParameters.insert(PARAM_ID_LTE_GERAN_T304_EXP_WAIT_TMR);
      mibCsfbGeranCfgParameters.insert(PARAM_ID_LTE_GERAN_RRC_DAT_CFM_TMR);
      mibCsfbGeranCfgParameters.insert(PARAM_ID_LTE_GERAN_MEAS_ALLOW_CCO );
      mibCsfbGeranCfgParameters.insert(PARAM_ID_LTE_GERAN_CCO_ALLOW );

      AddSubscription(subscriptions,SI_LTE_CSFB_GERAN_PARAMETERS+
            CELLSUBID,ENTITY_SM, fapLteDn,mibCsfbGeranCfgParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CSFB_GERAN_PARAMETERS,
             &SmApplication::HandleCsfbGeranCfgParameters));

      subId = (SI_NBR_UMTS_PARAMETERS + CELLSUBID);
      for(int umtsNbr  =0;umtsNbr<MAX_UMTS_OBJ;umtsNbr++)
      {
         MibAttributeIds mibUmtsParameters;

         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PCPICH_TX_POWER);
         mibUmtsParameters.insert(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_ENABLE);
         mibUmtsParameters.insert(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RNCID);
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_CID_IRAT);
         mibUmtsParameters.insert(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_LAC);
         mibUmtsParameters.insert(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RAC);
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PCPICH_SC);
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_UARFCNUL);
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_UARFCNDL);
         mibUmtsParameters.insert(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID);
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RIM_SUPPORT);
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_IS_VOIP_CAPABLE);	
         mibUmtsParameters.insert(
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_IS_PS_HO_CAPABLE);	
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR, umtsNbr);
         AddSubscription(subscriptions,subId,ENTITY_SM,nbrMO,mibUmtsParameters);
         subId++;
      }

      u32 utrafddfreq=(SI_NBR_UTRA_FDD_START + CELLSUBID);
      for (u32 idx=0; idx< MAX_UTRA_NEIGHBOR_FDD_FREQ; idx++)
      {
         MibAttributeIds utraFddFreqCarrParams;
         MibDN utraFddFreqCarrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_UTRA_UTRAN_FDD_FREQ, idx);

         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_FDD_ENABLE_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_FDD_CARRIER_ARFCN);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_Q_RX_LEV_MIN_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_Q_QUAL_MIN_IRAT);
         utraFddFreqCarrParams.insert(
               PARAM_ID_LTE_UTRA_CELL_RESELECT_PRIORITY_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_THRESH_XLOW_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_THRESH_XHIGH_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_PMAX);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_FDD_CARRIER_UL_ARFCN);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_QOFFSET_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_DUPLEXMODE_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_THRESHX_HIGHQ_R9_IRAT);
         utraFddFreqCarrParams.insert(PARAM_ID_LTE_UTRA_THRESHX_LOWQ_R9_IRAT);
         AddSubscription(subscriptions, utrafddfreq, ENTITY_SM,
               utraFddFreqCarrMO, utraFddFreqCarrParams);
         utrafddfreq++;
      }

      int geranFreq;
      int geranFreqSubId = SI_NBR_GERAN_FREQ_PARAMETERS + CELLSUBID;
      for(geranFreq=0; geranFreq < MAX_GERAN_NEIGHBOR_FREQ; geranFreq++)
      {
         MibAttributeIds mibNbrGERANFreqParameters;
         mibNbrGERANFreqParameters.insert(PARAM_ID_LTE_GERAN_FREQ_ENABLE);
         mibNbrGERANFreqParameters.insert(
               PARAM_ID_LTE_GERAN_FREQ_BAND_INDICATOR);
         mibNbrGERANFreqParameters.insert(PARAM_ID_LTE_GERAN_FREQ_BCCH_ARFCN);
         mibNbrGERANFreqParameters.insert(PARAM_ID_LTE_GERAN_FREQ_QRX_LEV_MIN);
         mibNbrGERANFreqParameters.insert(
               PARAM_ID_LTE_GERAN_FREQ_CELL_RESEL_PRIOR);
         mibNbrGERANFreqParameters.insert(PARAM_ID_LTE_GERAN_FREQ_THRESHX_HIGH);
         mibNbrGERANFreqParameters.insert(PARAM_ID_LTE_GERAN_FREQ_THRESHX_LOW);
         mibNbrGERANFreqParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_FREQ_NCC_PERMIT);
         mibNbrGERANFreqParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_FREQ_PRES_PMAX);
         mibNbrGERANFreqParameters.insert(PARAM_ID_LTE_GERAN_X_RSYS_FREQ_PMAX);
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST,
               geranFreq);
         AddSubscription(subscriptions, geranFreqSubId, ENTITY_SM, nbrMO,
               mibNbrGERANFreqParameters);
         geranFreqSubId++;
      }

      int geranCell;
      u32 geranCellSubId = SI_NBR_GERAN_CELL_PARAMETERS + CELLSUBID;
      for(geranCell=0; geranCell < MAX_GERAN_NEIGHBOR_CELLS; geranCell++)
      {
         MibAttributeIds mibNbrGERANCellParameters;
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_CELL_ENABLE);
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_CELL_PLMNID);
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_CELL_LAC);
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_CELL_BSIC);
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_CELL_CI);
         mibNbrGERANCellParameters.insert(
               PARAM_ID_LTE_GERAN_CELL_BAND_INDICATOR);
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_CELL_BCCH_ARFCN);
         mibNbrGERANCellParameters.insert(PARAM_ID_LTE_GERAN_X_RSYS_CELL_RAC);
         mibNbrGERANCellParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_CELL_NCC_PERMIT);
         mibNbrGERANCellParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_CELL_DTM_CAPABLE);
         mibNbrGERANCellParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_CELL_NET_CNTRL_ORDER);
         mibNbrGERANCellParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_CELL_NET_CNTRL_ORDER_PRES);
         mibNbrGERANCellParameters.insert(
               PARAM_ID_LTE_GERAN_X_RSYS_CELL_RIM_SUPPORTED);
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST,
               geranCell);
         AddSubscription(subscriptions, geranCellSubId, ENTITY_SM, nbrMO,
               mibNbrGERANCellParameters);
         geranCellSubId++;
      }

      int geranInUseCell;
      u32 geranIuUseCellSubId = SI_NBR_GERAN_CELL_IN_USE_PARAMETERS + CELLSUBID;
      for(geranInUseCell=0; geranInUseCell < MAX_GERAN_NEIGHBOR_CELLS_IN_USE; geranInUseCell++)
      {
         MibAttributeIds mibNbrGERANCellInUseParameters;
         mibNbrGERANCellInUseParameters.insert(PARAM_ID_LTE_GERAN_CELL_IN_USE_CI);
         mibNbrGERANCellInUseParameters.insert(PARAM_ID_LTE_GERAN_CELL_IN_USE_PLMNID);
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn, 
               MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST,
               geranInUseCell);
         AddSubscription(subscriptions, geranIuUseCellSubId, ENTITY_SM, nbrMO,
               mibNbrGERANCellInUseParameters);
         geranIuUseCellSubId++;
      }

      int tdsCdmaUtranTddFreq;
      u32 tdScdmaFreqSubId = SI_TDS_CDMA_UTRAN_TDD_FREQ_PARAMETERS + CELLSUBID;
      for(tdsCdmaUtranTddFreq=0;
            tdsCdmaUtranTddFreq < MAX_TDS_CDMA_UTRAN_TDD_FREQ;
            tdsCdmaUtranTddFreq++)
      {
         MibAttributeIds mibTdsCdmaUtranTddFreqParameters;
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_FREQ_ENABLE);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_UTRA_ARFCN);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_QRX_LEV_MIN);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_CELL_RESEL_PRIOR);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_THRESH_X_HIGH);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_THRESH_X_LOW);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_PMAX_UTRA);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_UTRATDD_MODE);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_UTRATDD_BAND_INDICATOR);
         mibTdsCdmaUtranTddFreqParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_QOFFSET_UTRATDD);
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_FREQ_LIST,
               tdsCdmaUtranTddFreq);
         AddSubscription(subscriptions, tdScdmaFreqSubId, ENTITY_SM, nbrMO,
               mibTdsCdmaUtranTddFreqParameters);
         tdScdmaFreqSubId++;
      }

      int tdsCdmaUtranTddCell;
      u32 tdScdmaCellSubId = SI_TDS_CDMA_UTRAN_TDD_CELL_PARAMETERS + CELLSUBID;
      for(tdsCdmaUtranTddCell=0;
            tdsCdmaUtranTddCell < MAX_TDS_CDMA_UTRAN_TDD_CELL;
            tdsCdmaUtranTddCell++)
      {
         MibAttributeIds mibTdsCdmaUtranTddCellParameters;
         mibTdsCdmaUtranTddCellParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_CELL_ENABLE);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_PLMNID);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_RNCID);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_CID);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_LAC);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_RAC);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_URA);
         mibTdsCdmaUtranTddCellParameters.insert(PARAM_ID_LTE_TDS_CDMA_UARFCN);
         mibTdsCdmaUtranTddCellParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_CELL_PARAM_ID);
         mibTdsCdmaUtranTddCellParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_PRI_CCPCH_PWR);
         mibTdsCdmaUtranTddCellParameters.insert(
               PARAM_ID_LTE_TDS_CDMA_CELL_RIM_SUPPORT);
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_CELL_LIST,
               tdsCdmaUtranTddCell);
         AddSubscription(subscriptions, tdScdmaCellSubId, ENTITY_SM, nbrMO,
               mibTdsCdmaUtranTddCellParameters);
         tdScdmaCellSubId++;
      }

      MibAttributeIds mibCDMA1xNeighCell;
      mibCDMA1xNeighCell.insert(
            PARAM_ID_LTE_CDMA2K_MAX_CDMA1X_NEIGH_CELL_ENTRIES);
      mibCDMA1xNeighCell.insert(
            PARAM_ID_LTE_CDMA2K_NUM_CDMA1X_NEIGH_CELL_ENTRIES);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_CELL_BAND_CLASS);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_ARFCN);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_BAND_PN_OFFSET);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_CELL_TYPE);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_CID_CDMA2K);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_CUR_RANK);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_SYSTEM_TYPE);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_CHANNEL_NUM);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_NBR_MARKET_ID);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_NBR_SWITCH_NUM);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_NBR_SECTOR_NUM);
      mibCDMA1xNeighCell.insert(PARAM_ID_LTE_CDMA2K_NBR_CELL_IDENTITY);
      AddSubscription(subscriptions, SI_CDMA_1XRTT_NGH_CELL + CELLSUBID,
            ENTITY_SM, fapLteDn, mibCDMA1xNeighCell);

      MibAttributeIds mibCdmaMobilityParameters;
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SID);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_NID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_NID);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MULT_SID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MULT_SID);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MULT_NID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MULT_NID);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_REG_ZONE_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_REG_ZONE);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_TOTAL_ZONE_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_TOTAL_ZONE);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ZONE_TIMER_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ZONE_TIMER);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PKT_ZONE_ID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PKT_ZONE_ID);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_PZ_ID_HYS_PARAM_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PZ_HYST_ENABLE);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PZ_HYST_INFO_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PZ_HYST_LIST_LEN);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PZ_HYST_ACT_TIMER);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PZ_HYST_TIMER_MUL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PZ_HYST_TIMER_EXP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PREV_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PREV);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MIN_PREV_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MIN_PREV);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_NEG_SLOT_CYC_IDX_SUP_INCL);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_NEG_SLOT_CYC_IDX_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ENC_MOD_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ENC_MODE);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ENC_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ENC_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SIG_ENC_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SIG_ENC_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MSG_INT_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MSG_INT_SUP);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_SIG_INT_SUP_IND_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SIG_INT_SUP_IND);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SIG_INT_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SIG_INT_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_AUTH_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_AUTH);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_MAX_NUM_ALT_SER_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MAX_NUM_ALT_SER);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_USE_SYNC_ID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_USE_SYNC_ID);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_MS_INIT_POS_LOC_SUP_IND_INCL);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_MS_INIT_POS_LOC_SUP_IND);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MOB_QOS_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MOB_QOS);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_BAND_CLS_INFO_REQ_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_BAND_CLS_INFO_REQ);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_BAND_CLS_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_BAND_CLS);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_BY_PASS_REG_IND_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_BY_PASS_REG_IND);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ALT_BND_CLS_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_ALT_BND_CLS);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_MAX_ADD_SERV_INST_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MAX_ADD_SERV_INST);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_HOME_REG_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_HOME_REG);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SID_REG_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SID_REG);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_NID_REG_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_NID_REG);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PWR_UP_REG_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PWR_UP_REG);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PWR_DOWN_REG_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PWR_DOWN_REG);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PARAM_REG_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PARAM_REG);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_REG_PRD_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_REG_PRD);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_REG_DIST_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_REG_DIST);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PREF_MSID_TYPE_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PREF_MSID_TYPE);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_EXT_PREF_MSID_TYPE_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_EXT_PREF_MSID_TYPE);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MEID_REQD_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MEID_REQD);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MRCC_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_MCC);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_IMSI_11_12_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_IMSI_11_12);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_IMSI_TSUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_IMSI_TSUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_RE_CON_MSG_IND_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_RE_CON_MSG_IND);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_RER_MOD_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_RER_MOD_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_TZK_MOD_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_TKZ_MOD_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_TZK_ID_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_TKZ_ID);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PIL_REP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PIL_REP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SDB_SUP_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SDB_SUP);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_AUTO_FCSO_ALL_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_AUTO_FCSO_ALL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SDB_IN_RCNM_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_SDB_IN_RCNM);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_FPC_FCH_INCL);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC3);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC4);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC5);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC11);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC12);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_T_ADD_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_T_ADD);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PILOT_INC_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_PILOT_INC);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_RAND_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_RAND);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_LP_SEC_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_LP_SEC);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_LTM_OFF_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_LTM_OFF);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_DAY_LIGHT_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_DAY_LIGHT);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_GCSNA_L2_ACT_TIMER_INCL);
      mibCdmaMobilityParameters.insert(PARAM_ID_LTE_CDMA2K_GCSNA_L2_ACT_TIMER);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_GCSNA_SEQ_CTXT_TIMER_INCL);
      mibCdmaMobilityParameters.insert(
            PARAM_ID_LTE_CDMA2K_GCSNA_SEQ_CTXT_TIMER);

      AddSubscription(subscriptions, SI_CDMA_MOBILITY_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibCdmaMobilityParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_CDMA_MOBILITY_PARAMETERS,
             &SmApplication::HandleCdmaMobilityParameters));

      MibAttributeIds mibLteCellDlSchdCfgGrpParameters;
      mibLteCellDlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_MAX_DL_TX_RX_UE_PER_TTI);
      mibLteCellDlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_MAX_DL_TX_UE_PER_TTI);
      mibLteCellDlSchdCfgGrpParameters.insert(PARAM_ID_LTE_DL_SCHD_TYPE);
      mibLteCellDlSchdCfgGrpParameters.insert(PARAM_ID_LTE_DLFSS_ENABLE);
      mibLteCellDlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_PFS_DL_TPT_COEFFICIENT);
      mibLteCellDlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_PFS_DL_FAIRNESS_COEFFICIENT);
      mibLteCellDlSchdCfgGrpParameters.insert(PARAM_ID_LTE_DL_QCI_SCHD_WGT);

      AddSubscription(subscriptions, SI_LTE_CELL_DL_SCHD_CONFIG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellDlSchdCfgGrpParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_DL_SCHD_CONFIG_PARAMETERS,
             &SmApplication::HandleLteCellDlSchdCfgGrpParameters));

      MibAttributeIds mibLteMsCellCfgReqParameters;
      mibLteMsCellCfgReqParameters.insert(PARAM_ID_LTE_OP_MODE);
      mibLteMsCellCfgReqParameters.insert(PARAM_ID_LTE_PERIOD);

      AddSubscription(subscriptions, SI_LTE_MS_CELL_CFG_REQ_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteMsCellCfgReqParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_MS_CELL_CFG_REQ_PARAMETERS,
             &SmApplication::HandleLteMsCellCfgReqParameters));

      MibAttributeIds mibLteUlAllocInfoCbParameters;
      mibLteUlAllocInfoCbParameters.insert(PARAM_ID_LTE_UL_MCS_VAL);
      mibLteUlAllocInfoCbParameters.insert(PARAM_ID_LTE_UL_NUM_RB_VAL);
      mibLteUlAllocInfoCbParameters.insert(PARAM_ID_LTE_UL_RB_START_VAL);
      mibLteUlAllocInfoCbParameters.insert(PARAM_ID_LTE_UL_ENABLE_TIME);
      AddSubscription(subscriptions, SI_LTE_UL_ALLOC_INFO_CB_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteUlAllocInfoCbParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_UL_ALLOC_INFO_CB_PARAMETERS,
             &SmApplication::HandleLteUlAllocInfoCbParameters));

      MibAttributeIds mibLteProcTimerCfgParameters;
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_S1RESET_TIME);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_X2RESET_TIME);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_S1_PREP_TMR);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_S1_OVRALL_TMR);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_X2_PREP_TMR);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_X2_OVRALL_TMR);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_IRAT_TS1_RELOC_PREP_TMR);
      mibLteProcTimerCfgParameters.insert(
            PARAM_ID_LTE_IRAT_TS1_RELOC_OVRALL_TMR);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_HO_CANCEL_ACK_TMR);
      mibLteProcTimerCfgParameters.insert(PARAM_ID_LTE_X2_TIME_TO_WAIT);

      AddSubscription(subscriptions, SI_LTE_PROC_TIMER_CFG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteProcTimerCfgParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PROC_TIMER_CFG_PARAMETERS,
             &SmApplication::HandleLteProcTimerCfgParameters));

      MibAttributeIds mibSpsCfgParameters;
      mibSpsCfgParameters.insert(PARAM_ID_LTE_IS_SPS_ENABLE);
      mibSpsCfgParameters.insert(PARAM_ID_LTE_MAX_DL_SPS_UE_PER_TTI);
      mibSpsCfgParameters.insert(PARAM_ID_LTE_MAX_UL_SPS_UE_PER_TTI);
      mibSpsCfgParameters.insert(PARAM_ID_LTE_MAX_SPS_RB);

      AddSubscription(subscriptions, SI_LTE_SPS_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibSpsCfgParameters); 

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_SPS_PARAMETERS,
             &SmApplication::HandleLteSpsParameters));

      {  
         MibAttributeIdsByDn neighCellObj;
         MibObjectClassesByDn objectClassesByDn;

         MibDN parentDn = fapLteDn;
         objectClassesByDn.clear();

         objectClassesByDn[parentDn].insert(
               MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL);
         MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
         m_mib.SubscribeMibAttributes((u32)SI_EUTRA_NBR_CELL_OBJ + CELLSUBID,
               ENTITY_SM,neighCellObj,objectClassesByDn,false);
      }
      subId = SI_NBR_CELL_PARAMETERS + CELLSUBID;
      for(int cell=0;cell < MAX_NEIGHBOR_CELLS ; cell++)
      {
         MibAttributeIds mibNbrCellParameters;
         mibNbrCellParameters.insert(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_MUST_INCLUDE);
         mibNbrCellParameters.insert(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PLMNID);
         mibNbrCellParameters.insert(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CID);
         mibNbrCellParameters.insert(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_EARFCN);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PHY_CELLID);
         mibNbrCellParameters.insert(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_QOFFSET);
         mibNbrCellParameters.insert(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CIO);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_RS_TX_POWER);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_ULEARFCN);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_TAC);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CSG_INDICATOR);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CSG_ACCESS_MODE);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CSG_ID);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_NUM_ANTENNA);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_ULDL_SUB_FRAME_CFG);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_SPL_SF_CFG);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CP_DL);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CP_UL);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_RSRP);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_RSSI);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_DL_BW);
         mibNbrCellParameters.insert(
               PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_UL_BW);
         MibDN nbrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,cell);
         AddSubscription(subscriptions, subId, ENTITY_SM, nbrMO,
               mibNbrCellParameters);
         subId++;
      }

      MibAttributeIds mibLteEutranNeighFreqCfgParameters;
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_CELL_RESELECTION_PRIORITY);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_QRX_LEVEL_MIN_SIB3);
      mibLteEutranNeighFreqCfgParameters.insert(PARAM_ID_LTE_PMAX);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_T_RESELECTION_EUTRA);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_TRESELECTION_EUTRAS_MED);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_TRESELECTION_EUTRAS_HIGH);
      mibLteEutranNeighFreqCfgParameters.insert(PARAM_ID_LTE_SINTRA_SEARCH);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_S_NON_INTRA_SEARCH);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_THRESH_SERVING_LOW);
      mibLteEutranNeighFreqCfgParameters.insert(PARAM_ID_LTE_THRESH_XHIGH);
      mibLteEutranNeighFreqCfgParameters.insert(PARAM_ID_LTE_THRESH_XLOW);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_INTER_FREQ_QOFFSET);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_OAM_NEIGHBOUR_DL_BANDWIDTH_SIB3);
      mibLteEutranNeighFreqCfgParameters.insert(
            PARAM_ID_LTE_OAM_Q_OFFSET_RANGE);
      AddSubscription(subscriptions,
            SI_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS+CELLSUBID,
            ENTITY_SM,
            fapLteDn,
            mibLteEutranNeighFreqCfgParameters);

      { 
         MibAttributeIdsByDn interFreqCarrObj;
         MibObjectClassesByDn objectClassesByDn;

         MibDN parentDn = fapLteDn;
         objectClassesByDn.clear();

         objectClassesByDn[parentDn].insert(
               MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER);
         MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
         m_mib.SubscribeMibAttributes((u32)SI_EUTRA_NBR_FREQ_OBJ + CELLSUBID,
               ENTITY_SM,interFreqCarrObj,objectClassesByDn,false);
      }
      u32 interFreqCarrSubId = SI_EUTRA_NBR_FREQ_PARAMS + CELLSUBID;
      for (u8 idx=0; idx<MAX_EUTRA_NEIGHBOR_FREQ; idx++)
      {
         MibAttributeIds interFreqCarrParams;
         MibDN interFreqCarrMO = MibDN::GenerateMibDN(fapLteDn,
               MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER, idx);

         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_ENABLE);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_DL_EARFCN);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_QRX_LEVEL_MIN);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_QOFFSETFREQ);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_INTER_FREQ_CELL_RESELECT_PRIORITY);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XHIGH);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XLOW);
         interFreqCarrParams.insert(PARAM_ID_LTE_INTER_FREQ_PMAX);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_MED);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_HIGH);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_ALLOWD_MEAS_BW);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_PRES_ANTENNA_PORT1);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_QQUALMIN_R9);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_THRESHX_HIGHQ_R9);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_THRESHX_LOWQ_R9);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_NEIGH_CELL_CONFIG);
         interFreqCarrParams.insert(
               PARAM_ID_LTE_X_RADISYS_INTER_FREQ_UL_EARFCN);
         AddSubscription(subscriptions, interFreqCarrSubId, ENTITY_SM,
               interFreqCarrMO, interFreqCarrParams);
         interFreqCarrSubId++;
      }

      MibAttributeIds mibLtePRBallocationParameters;
      mibLtePRBallocationParameters.insert(PARAM_ID_LTE_PRB_ALLOCATION_PLMN);
      AddSubscription(subscriptions, SI_LTE_PRB_ALLOCATION_PARAMETERS 
            + CELLSUBID, ENTITY_SM, fapLteDn, mibLtePRBallocationParameters);

      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_PRB_ALLOCATION_PARAMETERS,
             &SmApplication::HandleLtePRBallocationParameters));

      MibAttributeIds mibLteRrmTddParameters;
      mibLteRrmTddParameters.insert(PARAM_ID_LTE_RRM_SR_PRDCTY);
      mibLteRrmTddParameters.insert(PARAM_ID_LTE_RRM_CQI_PRDCTY);
      mibLteRrmTddParameters.insert(PARAM_ID_LTE_RRM_NUM_SR_PER_TTI);
      mibLteRrmTddParameters.insert(PARAM_ID_LTE_RRM_NUM_CQI_PER_TTI);
      mibLteRrmTddParameters.insert(PARAM_ID_LTE_RRM_SIMUL_ACK_NACK_ENB);
      AddSubscription(subscriptions, SI_LTE_RRM_TDD_PARAMETERS + CELLSUBID,
            ENTITY_SM, fapLteDn, mibLteRrmTddParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_RRM_TDD_PARAMETERS,
             &SmApplication::HandleLteRrmTddParameters));


      MibAttributeIds mibLteCellUlSchdCfgGrpParameters;
      mibLteCellUlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_MAX_UL_TX_RX_UE_PER_TTI);
      mibLteCellUlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_MAX_UL_TX_UE_PER_TTI);
      mibLteCellUlSchdCfgGrpParameters.insert(PARAM_ID_LTE_UL_SCHD_TYPE);
      mibLteCellUlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_PFS_UL_TPT_COEFFICIENT);
      mibLteCellUlSchdCfgGrpParameters.insert(
            PARAM_ID_LTE_PFS_UL_FAIRNESS_COEFFICIENT);
      mibLteCellUlSchdCfgGrpParameters.insert(PARAM_ID_LTE_UL_QCI_SCHD_WGT);
      AddSubscription(subscriptions, SI_LTE_CELL_UL_SCHD_CONFIG_PARAMETERS +
            CELLSUBID, ENTITY_SM, fapLteDn, mibLteCellUlSchdCfgGrpParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CELL_UL_SCHD_CONFIG_PARAMETERS,
             &SmApplication::HandleLteCellUlSchdCfgGrpParameters));
      MibAttributeIds mibLteCnmParameters;
      mibLteCnmParameters.insert(PARAM_ID_LTE_CNM_ENABLE);
      AddSubscription(subscriptions,SI_LTE_CNM_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibLteCnmParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_CNM_PARAMETERS,
             &SmApplication::HandleLteCnmParameters));

      MibAttributeIds mibLteDynamicCfiParameters;
      mibLteDynamicCfiParameters.insert(PARAM_ID_LTE_IS_DYNAMIC_CFI_ENABLE);
      AddSubscription(subscriptions,SI_LTE_DYNAMIC_CFI_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibLteDynamicCfiParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_DYNAMIC_CFI_PARAMETERS,
             &SmApplication::HandleLteDynamicCfiParameters));

      MibAttributeIds mibCsfbCfgParameters;
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_ECSFB_REPORT_CFG_VAL);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_CSFB_REPORT_CFG_VAL);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_DUAL_RX_SUP);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_IS_DUAL_RXTX_ALLOWED);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_MARKET_ID);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_SWITCH_NUM);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_SECTOR_NUM);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CDMA2K_SEARCH_WINDOW_SIZE);
      mibCsfbCfgParameters.insert(PARAM_ID_LTE_CSFB_TO_UTRA_MEAS_ENABLE);

      AddSubscription(subscriptions,SI_CSFB_CFG_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibCsfbCfgParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_CSFB_CFG_PARAMETERS,
             &SmApplication::HandleCsfbCfgParameters));

      MibAttributeIds mibLteRemNeighEarfcnDlAndRssi;
      mibLteRemNeighEarfcnDlAndRssi.insert(PARAM_ID_LTE_REM_NUM_EARFCN);
      mibLteRemNeighEarfcnDlAndRssi.insert(PARAM_ID_LTE_REM_RSSI);
      mibLteRemNeighEarfcnDlAndRssi.insert(PARAM_ID_LTE_REM_EARFCNDL);
      AddSubscription(subscriptions,SI_LTE_REM_EARFCN_RSSI_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibLteRemNeighEarfcnDlAndRssi);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_REM_EARFCN_RSSI_PARAMETERS,
             &SmApplication::HandleLteRemEarfcnAndRSSIParameters));

      MibAttributeIds mibMessengerAccessMngmntParanmeters;
      mibMessengerAccessMngmntParanmeters.insert(PARAM_ID_LTE_ACCESS_MODE);
      mibMessengerAccessMngmntParanmeters.insert(PARAM_ID_LTE_MAX_UE_SERVED);
      mibMessengerAccessMngmntParanmeters.insert(PARAM_ID_LTE_MAX_CSG_MEMBERS);
      mibMessengerAccessMngmntParanmeters.insert(
            PARAM_ID_LTE_MAX_NON_CSG_MEMBERS);
      mibMessengerAccessMngmntParanmeters.insert(
            PARAM_ID_LTE_MAX_NON_CSG_RESOURCE);
      AddSubscription(subscriptions,SI_LTE_ACCESS_MNGMNT_PARAMETERS+CELLSUBID,
            ENTITY_SM,fapLteDn,mibMessengerAccessMngmntParanmeters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_ACCESS_MNGMNT_PARAMETERS,
             &SmApplication::HandleAccessManagementParameters));

      MibAttributeIds mibTMCfgParameters;
      mibTMCfgParameters.insert(PARAM_ID_LTE_TM_AUTO_CONFIG);
      mibTMCfgParameters.insert(PARAM_ID_LTE_PREFERRED_TRANSMISSION_MODE);
      AddSubscription(subscriptions,SI_LTE_TRANSMISSION_MODE_CONFIG+CELLSUBID,
            ENTITY_SM,fapLteDn,mibTMCfgParameters);
      hdlrMap.insert(std::make_pair
            ((u16)SI_LTE_TRANSMISSION_MODE_CONFIG,
             &SmApplication::HandleLteTMParameters));
   }
   m_oneTimeInitialisation = MSM_TRUE;
}

void SmApplication::startPeriodicRemScan()
{
   TRACE_PRINTF("Starting Periodic REM scan\n");

   m_PeriodicRemScanInProg = true;
   /* Send Scan REQ to OAM */
   OamActionReq oamActionReq(OAM_ACTION_REM_SCAN);
   SendMessage(oamActionReq, ENTITY_OAM, ENTITY_SM);
   return;
}

void SmApplication::HandleTimerExpiry
(
 shared_ptr<threeway::TimerExpiry> expiredTimer
 )
{
   TRACE_PRINTF("%s",__func__);

   if( expiredTimer->GetTimerHandle() == m_adminFlagTimer)
   {
      TRACE_PRINTF("Admin State Flag Timer Expired");
      if (ADMIN_CHANGE==callBackTo)
      {
         SmApplication::GetInstance().HandleLteAdminStateChange(INVALID,INVALID);
      }
      else if(IP_CHANGE==callBackTo)
      {
         SmApplication::GetInstance().HandleEnodebIPAddress(INVALID,INVALID);
      }
   }
   else if( expiredTimer->GetTimerHandle() == m_lteNeighCfgTimer)
   {
      if(IsTimerRunning(m_lteNeighCfgTimer))
      {
         DeleteTimer(m_lteNeighCfgTimer);
      }
      TRACE_PRINTF("LteNeighCfg Timer Expired");
      HandleLteAdminStateChange(INVALID,INVALID);
   }
   else if(expiredTimer->GetTimerHandle() == m_logTimerHandle) 
   { 
      string logFileName[3]; 
      int numClosedFiles = Trace::GetInstance().GetLogFilesToUpload(logFileName);
      for(int n_uploadfile = 0;n_uploadfile < numClosedFiles;n_uploadfile++) 
      { 
         UploadLogReq upLogReq(logFileName[n_uploadfile]); 
         SendMessage(upLogReq,ENTITY_FTP,ENTITY_SM); 
      } 
      HandleLogUpload(INVALID,INVALID); 
   } 
   else if( expiredTimer->GetTimerHandle() == m_periodRemStartTimer)
   {
      TRACE_PRINTF("m_periodRemStartTimer Expired");
      u32 lteRemPerScanIntvl;
      MibDN remDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

      MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

      /* Get the LTE REM Periodic interval */
      m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_PERIODIC_INTERVAL, lteRemPerScanIntvl);
      TRACE_PRINTF("Starting m_periodRemScanTimer\n");
      m_periodRemScanTimer = CreateTimer((const std::string&)"Starting Periodic REM scan timer",
            u32(lteRemPerScanIntvl*1000), TimerEngineInterface::TIMER_START_NOW,
            TimerEngineInterface::TIMER_REPEAT);
   }
   else if( expiredTimer->GetTimerHandle() == m_periodRemScanTimer)
   {
      TRACE_PRINTF("m_periodRemScanTimer Expired");

      TRACE_PRINTF("m_PeriodicRemScanInProg is %d",m_PeriodicRemScanInProg);
      if (m_PeriodicRemScanInProg == false)
      {
         bool perLteRem = false, perWcdmaRem = false;
         u16 inSrvcHandling = MSM_FALSE;
         string lteInSrvHandl = "", wcdmaInSrvHandl = "";

         MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

         MibDN remDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);
         m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_PERIODIC_SCAN_MODE,perLteRem);
         TRACE_PRINTF("perLteRem is  = %d",perLteRem);

         MibDN remWcdmaDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA);
         m_mib.GetMibAttribute(remWcdmaDn, PARAM_ID_PERIODIC_SCAN_MODE,perWcdmaRem);
         TRACE_PRINTF("perWcdmaRem is  = %d",perWcdmaRem);

         if (perLteRem == true)
         {
            m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_IN_SERVICE_HANDLING, lteInSrvHandl);
            TRACE_PRINTF("lteInSrvHandl is  = %s",lteInSrvHandl.c_str());
         }

         if (perWcdmaRem == true)
         {
            m_mib.GetMibAttribute(remWcdmaDn, PARAM_ID_IN_SERVICE_HANDLING,wcdmaInSrvHandl);
            TRACE_PRINTF("wcdmaInSrvHandl is  = %s",wcdmaInSrvHandl.c_str());
         }

         if ((lteInSrvHandl == "Immediate") || (wcdmaInSrvHandl == "Immediate"))
         {
            inSrvcHandling = MSM_TRUE;
         }

         TRACE_PRINTF("Sending MsmStartStopStackReq");

         MsmStartStopStackReq(MSM_TRUE,MSM_FALSE,inSrvcHandling);
      }
   }
   if (true)
   {
      SingleThreadedAppWithAttrCache::HandleTimerExpiry(expiredTimer);
   }
}

bool SmApplication::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
   TRACE_PRINTF("%s",__func__);

   // First, pass to parent
   bool handled = SingleThreadedAppWithAttrCache::MessageHandler(message);

   try
   {
      switch (message->GetSerialisationId())
      {
         case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
            {
               shared_ptr<MibSubscribeAttributesInd> subscribeMibParamsInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);
               if (subscribeMibParamsInd)
               {
                  TRACE("MibSubscribeAttributesInd received", subscribeMibParamsInd->ToString().c_str());

                  HandleLteSubscriptions(subscribeMibParamsInd->GetSubscriptionId());
               }
            }
            break;
         case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_DELETE_IND:
            {
               shared_ptr<MibSubscribeAttributesDeleteInd> subscribeMibParamsDeleteInd = Serialisable::DeSerialise<MibSubscribeAttributesDeleteInd>(message);
               if (subscribeMibParamsDeleteInd)
               {
                  TRACE("MibSubscribeAttributesDeleteInd received", subscribeMibParamsDeleteInd->ToString().c_str());
                  HandleLteDeleteSubscriptions(subscribeMibParamsDeleteInd->GetSubscriptionId(),
                        subscribeMibParamsDeleteInd->ToString()); 
               }
            }
            break;
         case SERIALISATION_ID_MIB_CREATE_OBJECT_CNF:
            {
               shared_ptr<MibCreateObjectCnf> mibCreateObjectCnf = Serialisable::DeSerialise<MibCreateObjectCnf>(message);
               if (mibCreateObjectCnf)
               {
                  TRACE("Mib Create Object Confirmation received", mibCreateObjectCnf->ToString().c_str());
               }
            }
            break;
         case SERIALISATION_ID_REGISTER_ENTITY_CNF:
            {
               shared_ptr<RegisterEntityCnf> registerEntityCnf = Serialisable::DeSerialise<RegisterEntityCnf>(message);
               if (registerEntityCnf)
               {
                  TRACE("RegisterEntityCnf received", registerEntityCnf->ToString().c_str());
               }
            }
            break;
         case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF:
            {
               shared_ptr<MibSubscribeAttributesCnf> mibSubscribeAttributesCnf = Serialisable::DeSerialise<MibSubscribeAttributesCnf>(message);
               RSYS_ASSERT(mibSubscribeAttributesCnf != NULL);

               TRACE("MibSubscribeAttributesCnf received", mibSubscribeAttributesCnf->ToString().c_str());
            }
            break;
         case SERIALISATION_ID_MIB_SET_ATTRIBUTES_CNF:
         case SERIALISATION_ID_REQUEST_START_RSP:
            // Intentionally ignore.
            break; 
         case SERIALISATION_ID_MF_SET_ADMIN_STATE_REQ:
            {
               shared_ptr<MfSetAdminStateReq> setAdminStateReq = Serialisable::DeSerialise<MfSetAdminStateReq>(message);
               RSYS_ASSERT(setAdminStateReq != NULL);

               TRACE("MfSetAdminStateReq received", setAdminStateReq->ToString());
               TRACE_PRINTF("Admin State is modified \n");

               switch(setAdminStateReq->GetManagedFing())
               {
                  case MF_SM:
                     {
                        if(setAdminStateReq->GetAdminState()==0)
                        {
                           //deleteCell();
                           //SpvStatus.adminStatus = 0;
                        }
                        else if(setAdminStateReq->GetAdminState()==1)
                        {
                           //createCell();
                           //SpvStatus.adminStatus = 1;
                        }
                     }
                     break;
                  default:
                     RSYS_ASSERT_FAIL("Unexpected Managed Fing %s(%"PRIu32")", ManagedFingToString(setAdminStateReq->GetManagedFing()), (u32)setAdminStateReq->GetManagedFing());
                     break;
               } 
            }
            break;
         case SERIALISATION_ID_ENODEB_INIT_CONFIG_COMPLETE:
            {
               HandleLteDynamicConfiguration();
            }
            break;
         case SERIALISATION_ID_ALARM_EVENT:
            {
               u8 alarmSeverity;
               u32 id;
               string info,addinfo;
               shared_ptr<AlarmRegister> alarmRegister = Serialisable::DeSerialise<AlarmRegister>(message);
               RSYS_ASSERT(alarmRegister != NULL);

               id = alarmRegister->GetAlarmId();
               alarmSeverity = alarmRegister->GetAlarmSeverity();
               info = alarmRegister->GetAdditionalInfo();
               addinfo = alarmRegister->GetAddtnlInfo();
               if(addinfo != "")
               {
                  info = info + "," + addinfo;
               }
               SmAlarmHandler::GetInstance().UpdateAlarmEvent(id,alarmSeverity,info);
               u32 alrmId = id%MAX_ALARMS;
               if( alrmId == CFG_FAIL_FROM_SON || alrmId == PCI_COLLISION || alrmId == PCI_CONFUSION )
               {
                  if(alarmSeverity != SM_ALARM_SEVERITY_CLEARED )
                  {
                     m_isSONRaisedAlarmExists++;
                     TRACE_PRINTF("Alarm raised by SON. Current number of SON alarms = %d \n", m_isSONRaisedAlarmExists);
                  }
                  else
                  {
                     m_isSONRaisedAlarmExists--;
                     TRACE_PRINTF("Alarm raised by SON is cleared.Current number of SON alarms = %d \n",m_isSONRaisedAlarmExists);
                  }
               }
            }
            break;
         case SERIALISATION_ID_EVENT_NOTIFY:
            {
               u32 opState;
               TRACE_PRINTF("EVENT_NOTIFY Received to SM");
               GetMibCache().GetMibAttribute(PARAM_ID_LTE_RFTX_OP_STATE, opState);
               if(MSM_TRUE == opState )
               {
                  wrSendKpisInfo();
               }
            }
            break;
         case SERIALISATION_ID_L2TIMER_NOTIFY: /* bipin*/
            {
               u32 opState;
               TRACE_PRINTF("EVENT_NOTIFY Received to SM");
               GetMibCache().GetMibAttribute(PARAM_ID_LTE_RFTX_OP_STATE, opState);
               if(MSM_TRUE == opState )
               {
                  MsmPerfMgmtParameters perfMgmtParameters;
                  msmGetPmParameters(&perfMgmtParameters);
                  TRACE_PRINTF("L2 TimerNotify Received to SM with L2PMEnable(%d)", perfMgmtParameters.l2PMCollectionEnable);
                  shared_ptr<L2TimerNotify> l2TimerNotify = Serialisable::DeSerialise<L2TimerNotify>(message);
                  if (l2TimerNotify)
                  {
                     TRACE("Event ", l2TimerNotify->ToString().c_str());
                  }
                  /*starts or restarts KPIs Collection */
                  wrKpiStartKpiCollecPrc(true);
                  /*wrKpiStartKpiCollecPrc(60000,TRUE);*/
               }
            }
            break;       
         default:
            TRACE_LEV(TRACE_WARNING, "Unhandled message", message->ToString());
            break;
      }
   }
   catch (threeway::Exception& e)
   {
      TRACE_EXCEPTION(e);
   }
   return handled;
}

void SmApplication::HandleLteDeleteSubscriptions(u16 subscribs, string objName)
{
   TRACE_PRINTF("%s",__func__);

   char *instance = GetMibObjectInstanceNum(objName);
   u8   inst = 0;
   char *cellIdx =  GetMibObjectInstanceNum(objName.substr(0,16));
   int  lteCellIdx = 0;

   if(NULL == instance)
   {
      TRACE_PRINTF("Invalid Instance objName %s\n",objName.c_str());
   }
   else
   {
      inst = atoi(instance);
      if(NULL != cellIdx)
      {
         lteCellIdx = atoi(cellIdx);
      }
      if((MAX_EUTRA_NEIGHBOR_FREQ >= inst) && (numOfCells >= lteCellIdx))
      {
         switch (subscribs)
         {
            case SI_EUTRA_NBR_FREQ_OBJ:
               {
                  TRACE_PRINTF("Instance number is %d\n",inst);
                  HandleLteNeighFreqMIOParams(subscribs, inst, true,
                        lteCellIdx);
               }
               break;
            case SI_EUTRA_NBR_CELL_OBJ:
               HandleLteNeighCellCfgParameters(subscribs, inst, true,
                     lteCellIdx);
               break;
            default:
               {
                  TRACE_PRINTF("Unhandled parameter in Messenger");
               }
               break;
         }
      }
   }
}

char * SmApplication::GetMibObjectInstanceNum(string objClass)
{
   TRACE_PRINTF("%s",__func__);

   char* dnchar = const_cast<char*>(objClass.c_str());
   char * token = strtok(dnchar,".");
   char * lasttoken = NULL;
   while(token != NULL)
   {
      lasttoken = token;
      token = strtok(NULL,".");
   }
   return lasttoken;
}

s16 SmApplication::getCellIdx(u16 subscribs)
{
   s16 cellIdx = -1;

   TRACE_PRINTF("%s",__func__);

   for (subsIdRanges::iterator it = ranges.begin(); it != ranges.end(); ++it)
   {
      if ((subscribs >= it->second.first) && (subscribs <= it->second.second))
      {
         cellIdx = it->first;
         break;
      }
   }

   return cellIdx;

}

bool SmApplication::IsDynamicConfig(u16 subId, bool *pushDynCfg)
{
   if (m_messengerInitialConfigComplete == MSM_FALSE)
   {
      return false;
   }

#ifdef DYNUPDATE
   if(!((MSM_TRUE == m_smmInitialConfigComplete) && 
            (m_smmWaitForDynCfgRsp == FALSE)))
   {
      m_dynupdate.push(subId);
      *pushDynCfg = true;
   }
   return true;
#endif
}

void SmApplication::HandleLteSubscriptions(u16 subId)
{
   TRACE_PRINTF("%s\n",__func__);

   s16   cellIdx;
   bool  pushDynCfg = false, isDynCfg = false;
   fctnPtrMap::const_iterator iter;

   cellIdx = getCellIdx(subId);
   TRACE_PRINTF("Parameter change notification received for cellIdx: %d",
         cellIdx);

   if (cellIdx == -1)
   {
      TRACE_PRINTF("Invalid cellIdx, cellIdx is %d, subId is %d\n",
            cellIdx,subId);

      return;
   }

   /* Check if static or dynamic config */
   isDynCfg = IsDynamicConfig(subId, &pushDynCfg);

   /* If dynamic config & pushed to queue, no need to call handler */
   if ((isDynCfg == true) && (pushDynCfg == true))
   {
      TRACE_PRINTF("Received dynamic config and pushed to queue\n");
      return;
   }

   subId = subId % SI_LTE_MESSENGER_CONFIGURATION_COMPLETE;
   if ( (subId >= SI_NBR_CELL_PARAMETERS) && (subId < SI_NBR_CELL_PARAMETERS+
            MAX_NEIGHBOR_CELLS))
   {
      HandleLteNeighCellCfgParameters(SI_NBR_CELL_PARAMETERS,
            subId-SI_NBR_CELL_PARAMETERS,isDynCfg,cellIdx);
      return;
   }

   if ((subId >= SI_EUTRA_NBR_FREQ_PARAMS) && (subId <=
            SI_EUTRA_NBR_FREQ_PARAMS_END))
   {
      HandleLteNeighFreqMIOParams(SI_EUTRA_NBR_FREQ_PARAMS,
            subId-SI_EUTRA_NBR_FREQ_PARAMS,isDynCfg,cellIdx);
      return;
   }
   if(subId == SI_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS)
   {
      HandleLteNeighFreqMIOParams(subId,0,isDynCfg,cellIdx);
   }
   iter = hdlrMap.find(subId);
   if(iter != hdlrMap.end())
   {
      (this->*(iter->second))(cellIdx, isDynCfg);
   }

   return;
}

void SmApplication::adminDownFlagSet()
{
   TRACE_PRINTF("%s",__func__);

   SmApplication::s_adminFlag=1;
}

void SmApplication::ReadLtePrachCfgCommonParameters(MibDN fapLteDn,MsmLtePrachCfgCommon &ltePrachCfgCommon)
{
   std::vector<std::string> rootSequenceIndx, prachCfgIdx, zeroCorrelationZoneCfg, prachFreqOffset;
   std::vector<string> PRACHCfgList;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_HIGH_SPEED_FLAG,ltePrachCfgCommon.prachCfgInfo.highSpeedFlag);
   printf("PARAM_ID_LTE_HIGH_SPEED_FLAG:%d\n", ltePrachCfgCommon.prachCfgInfo.highSpeedFlag);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PRACH_ROOT_SEQUENCE_INDEX_LIST, PRACHCfgList);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(PRACHCfgList);

   u32 RootSeqIdxlistSize = PRACHCfgList.size();
   ltePrachCfgCommon.prachParamLst.numRootSeqIndex = RootSeqIdxlistSize;
   for( size_t idx = 0; idx < RootSeqIdxlistSize; idx++ )
   {
      ltePrachCfgCommon.prachParamLst.rootSequenceIndxLst[idx] = atoi(PRACHCfgList.at(idx).c_str());
   }
   PRACHCfgList.clear();

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PRACH_CONFIG_INDEX_LIST, PRACHCfgList);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(PRACHCfgList);
   u32 PrachCfgIdxListSize = PRACHCfgList.size();
   ltePrachCfgCommon.prachParamLst.numPrachCfgIdx = PrachCfgIdxListSize;
   for( size_t idx = 0; idx < PrachCfgIdxListSize; idx++ )
   {
      ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[idx] = atoi(PRACHCfgList.at(idx).c_str());
   }
   PRACHCfgList.clear();

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PRACH_ZERO_CORRELATIONZONE_CONFIG_LIST, PRACHCfgList);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(PRACHCfgList);
   u32 zeroCorrZoneCfgListSize = PRACHCfgList.size();
   ltePrachCfgCommon.prachParamLst.numZeroCorrZoneCfg = zeroCorrZoneCfgListSize;
   for( size_t idx = 0; idx < zeroCorrZoneCfgListSize; idx++ )
   {
      ltePrachCfgCommon.prachParamLst.zeroCorrelationZoneCfgLst[idx] = atoi(PRACHCfgList.at(idx).c_str());
   }
   PRACHCfgList.clear();

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PRACH_FREQ_OFFSET_LIST, PRACHCfgList);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(PRACHCfgList);
   u32 FreqOffsetListSize = PRACHCfgList.size();
   ltePrachCfgCommon.prachParamLst.numPrachFreqOffset = FreqOffsetListSize;
   for( size_t idx = 0; idx < FreqOffsetListSize; idx++ )
   {
      ltePrachCfgCommon.prachParamLst.prachFreqOffsetLst[idx] = atoi(PRACHCfgList.at(idx).c_str());
   }
   PRACHCfgList.clear();
}

void SmApplication::HandleLtePrachCfgCommonParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLtePrachCfgCommon     ltePrachCfgCommon;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   if(!isDynCfg)
   {
      ltePrachCfgCommon.actType = MSM_ACT_ADD;
      ReadLtePrachCfgCommonParameters(fapLteDn,ltePrachCfgCommon);
      msmSetPrachConfigCommonParameters(&ltePrachCfgCommon, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void SmApplication::ReadRachConfigParam(MibDN fapLteDn, MsmLteRachCfgCommonParams &lteRachCfgCommonParams)
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> preambleTransMax, rarWindowSize, maxHARQMsg3;
   vector<u32> numOfRAPreambles, groupASize, msgSizeGroupA, powerRampingstep, macContResTimer;
   vector<s32> pwrOffstGrpB, initRcvdTrgtPwr;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_NUM_OF_RAPREAMBLES,numOfRAPreambles);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrRaPreamblesInfo, numOfRAPreambles.at(0), m_posu8);
   lteRachCfgCommonParams.ltePreambleCfg.numOfRAPreambles = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SIZE_OF_RAGROUP_A, groupASize);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrgroupASize, groupASize.at(0), m_posu8);
   lteRachCfgCommonParams.ltePreambleCfg.groupASize = m_posu8;	

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_MSG_SIZE_GROUP_A, msgSizeGroupA);
   printf("PARAM_ID_LTE_MSG_SIZE_GROUP_A:%d\n", msgSizeGroupA.at(0));
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrmsgSizeGroupA, msgSizeGroupA.at(0), m_posu16);
   lteRachCfgCommonParams.ltePreambleCfg.msgSizeGroupA = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_POWER_OFFSET_GROUP_B,pwrOffstGrpB);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrpwrOffstGrpB, pwrOffstGrpB.at(0), m_posu8);
   lteRachCfgCommonParams.ltePreambleCfg.pwrOffstGrpB = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_POWER_RAMPING,powerRampingstep);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrpowerRampingstep, powerRampingstep.at(0), m_posu8);
   lteRachCfgCommonParams.ltePowerRamping.powerRampingstep = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PREAMBLE_INIT_TARGET_POWER,initRcvdTrgtPwr);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrinitRcvdTrgtPwr, initRcvdTrgtPwr.at(0), m_posu16);
   lteRachCfgCommonParams.ltePowerRamping.initRcvdTrgtPwr = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PREAMBLE_TRANS_MAX, preambleTransMax);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(preambleTransMax);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrpreambleTransMax, atoi(preambleTransMax.at(0).c_str()), m_posu8);
   lteRachCfgCommonParams.lteRaSupervisionCfg.preambleTransMax = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_RSP_WINDOW_SIZE, rarWindowSize);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(rarWindowSize);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrrarWindowSize, atoi(rarWindowSize.at(0).c_str()), m_posu8);
   lteRachCfgCommonParams.lteRaSupervisionCfg.rarWindowSize = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CONTENTION_RESOLUTION_TMR,macContResTimer);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrmacContResTimer, macContResTimer.at(0), m_posu8);
   lteRachCfgCommonParams.lteRaSupervisionCfg.macContResTimer = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_MAX_HARQ_MSG3_TX, maxHARQMsg3);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(maxHARQMsg3);
   lteRachCfgCommonParams.maxHARQMsg3 = atoi(maxHARQMsg3.at(0).c_str());
}

void SmApplication::HandleLteRachConfigCommonParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteRachCfgCommonParams lteRachCfgCommonParams;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   ReadRachConfigParam(fapLteDn, lteRachCfgCommonParams);

   if(!isDynCfg)
   {
      lteRachCfgCommonParams.ltePreambleCfg.actType = MSM_ACT_ADD;
      lteRachCfgCommonParams.ltePowerRamping.actType = MSM_ACT_ADD;
      lteRachCfgCommonParams.lteRaSupervisionCfg.actType = MSM_ACT_ADD;

      msmSetRachConfigCommonParameters(&lteRachCfgCommonParams, cellIdx);
   }
   else
   {
      lteRachCfgCommonParams.ltePreambleCfg.actType = MSM_ACT_MOD;
      lteRachCfgCommonParams.ltePowerRamping.actType = MSM_ACT_MOD;
      lteRachCfgCommonParams.lteRaSupervisionCfg.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteRachCfgCommonParams, MSM_LTE_RACH_CONFIG_COMMON_PARAMETERS, cellIdx);
   }


   return;
}

void SmApplication::ReadLtePdschConfigCommonParameters(MibDN fapLteDn,MsmLtePdschCfgCommon &ltePdschCfgCommon)
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> refSigPwr, ltePb;
   size_t i;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_REFERNCE_SIG_POWER, refSigPwr);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(refSigPwr);
   ltePdschCfgCommon.refSignalPwrCnt= refSigPwr.size();
   for(  i=0; i< ltePdschCfgCommon.refSignalPwrCnt;i++)
   {
      ltePdschCfgCommon.referenceSignalPwr[i] = atoi(refSigPwr.at(i).c_str());
   }

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PB, ltePb);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(ltePb);
   ltePdschCfgCommon.pBCnt=ltePb.size();
   for( i=0;i<ltePdschCfgCommon.pBCnt;i++)
   {
      ltePdschCfgCommon.pB[i] = (u8)atoi(ltePb.at(i).c_str());
   }
}

void SmApplication::HandleLtePdschConfigCommonParameters
(
 u16   cellIdx,
 bool  isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLtePdschCfgCommon ltePdschCfgCommon;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   ReadLtePdschConfigCommonParameters(fapLteDn,ltePdschCfgCommon);   

   if(!isDynCfg)
   {
      ltePdschCfgCommon.actType = MSM_ACT_ADD;
      msmSetPdschConfigCommonParameters(&ltePdschCfgCommon, cellIdx);
   }
   else
   {
      ltePdschCfgCommon.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&ltePdschCfgCommon, MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS,cellIdx);
   }

   return;
}

void SmApplication::ReadUlPwrCtrlParams(MibDN fapLteDn, MsmLteULPwrCtrlCommon &lteULPwrCtrlCommon)
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> pNomialPusch, pNomialPucch, alphaValue;
   u32 deltaPucchFormat1b;
   s32 deltaPucchFormat;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PO_NOMINAL_PUSCH, pNomialPusch);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(pNomialPusch);
   lteULPwrCtrlCommon.pNomialPusch = atoi(pNomialPusch.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PO_NOMINAL_PUCCH, pNomialPucch);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(pNomialPucch);
   lteULPwrCtrlCommon.pNomialPucch = atoi(pNomialPucch.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_ALPHA, alphaValue);
   printf("alpha:%s\n", alphaValue.at(0).c_str());
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(alphaValue);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrAlphaInfo, atoi(alphaValue.at(0).c_str()), m_posu8);
   lteULPwrCtrlCommon.alpha = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTAF_PUCCH_FRMT1,deltaPucchFormat);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrdeltaPucchFormatInfo, deltaPucchFormat, m_posu8);
   lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat1 = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTAF_PUCCH_FRMT1B,deltaPucchFormat1b);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrdeltaPucchFormat1bInfo, deltaPucchFormat1b, m_posu8);
   lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat1b = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTAF_PUCCH_FRMT2,deltaPucchFormat);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrdeltaPucchFormat2Info, deltaPucchFormat, m_posu8);
   lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat2 = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTAF_PUCCH_FRMT2A,deltaPucchFormat);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrdeltaPucchFormatInfo, deltaPucchFormat, m_posu8);
   lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat2a = m_posu8;		

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTAF_PUCCH_FRMT2B,deltaPucchFormat);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrdeltaPucchFormatInfo, deltaPucchFormat, m_posu8);
   lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat2b = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTA_PREAMBLE_MSG3,lteULPwrCtrlCommon.deltaMsg3);
}

void SmApplication::HandleLteUlPwrCtrlCommonParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteULPwrCtrlCommon lteULPwrCtrlCommon;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   ReadUlPwrCtrlParams(fapLteDn, lteULPwrCtrlCommon);

   if(!isDynCfg)
   {
      lteULPwrCtrlCommon.actType = MSM_ACT_ADD;
      msmSetUlPowerControlCommonParameters(&lteULPwrCtrlCommon, cellIdx);
   }
   else
   {
      lteULPwrCtrlCommon.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteULPwrCtrlCommon, MSM_LTE_UL_POWER_CONTROL_COMMON_PARAMETERS,cellIdx);
   }

   return;
}

void SmApplication::ReadLteULFrequencyInfoParameters(MibDN fapLteDn,MsmLteULFrequencyInfo &lteULFrequencyInfo)
{
   std::vector<u32> s_ulBandwidth, s_dlBandwidth;
   std::vector<u32> EarfcnULList;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_EARFCNUL_LIST, EarfcnULList);
   if(EarfcnULList.size() > 0)
   {
      lteULFrequencyInfo.eARFCN = EarfcnULList.at(0);
   }
   if(GetMibCache().IsMibAttributePresent(fapLteDn,PARAM_ID_LTE_UL_BANDWIDTH))
   {
      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_UL_BANDWIDTH,s_ulBandwidth);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, s_ulBandwidth[0], m_posu8);
      lteULFrequencyInfo.ulBandwidth= (MsmLteBandwidth)m_posu8;
   }
}

void SmApplication::HandleLteULFrequencyInfoParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   std::vector<u32> s_ulBandwidth, s_dlBandwidth;
   MsmLteULFrequencyInfo lteULFrequencyInfo;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      lteULFrequencyInfo.actType = MSM_ACT_ADD;
      ReadLteULFrequencyInfoParameters(fapLteDn,lteULFrequencyInfo);
      msmSetUlFrequencyInfoParameters(&lteULFrequencyInfo,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadLteCellSib3CfgGroupParameters(MibDN dn,MsmLteCellSib3CfgGrp &lteCellSib3CfgGrp)
{
   std::vector<std::string> qHyst;
   u32 tEvalulation,tHystNormal;
   s32 sfMedium, sfHigh;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_QHYST, qHyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qHyst);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqHystInfo, atoi(qHyst.at(0).c_str()), m_posu8);
   lteCellSib3CfgGrp.qHyst = m_posu8;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_QHYST_SF_MEDIUM, sfMedium);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrsfInfo, sfMedium, m_posu8);
   lteCellSib3CfgGrp.sfMedium = m_posu8;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_QHYST_SF_HIGH, sfHigh);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrsfInfo, sfHigh, m_posu8);
   lteCellSib3CfgGrp.sfHigh = m_posu8;

   lteCellSib3CfgGrp.mobStateParams.actType = MSM_ACT_ADD;
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_T_EVALUATION, tEvalulation);
   printf("tEvaluation:%d\n", PARAM_ID_LTE_T_EVALUATION);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtEvalulationInfo, tEvalulation, m_posu16);
   lteCellSib3CfgGrp.mobStateParams.tEvalulation = m_posu16;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_THYST_NORMAL, tHystNormal);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtHystNormalInfo, tHystNormal, m_posu16);
   lteCellSib3CfgGrp.mobStateParams.tHystNormal = m_posu16;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NUM_CELL_CHANGE_MEDIUM, lteCellSib3CfgGrp.mobStateParams.nCellChangeMedium);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NUM_CELL_CHANGE_HIGH,lteCellSib3CfgGrp.mobStateParams.nCellChangeHigh);
} 

void SmApplication::HandleLteCellSib3CfgGroupParameters
(
 u16   cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteCellSib3CfgGrp lteCellSib3CfgGrp;
   MibDN faplteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   ReadLteCellSib3CfgGroupParameters(faplteDn,lteCellSib3CfgGrp);

   if(!isDynCfg)
   {
      /*For Initial configuration*/
      lteCellSib3CfgGrp.actType = MSM_ACT_ADD;

      msmSetCell_Sib3ConfigGroupParameters(&lteCellSib3CfgGrp,cellIdx);
   }
   else
   { 
      /*For Dynamic update of Parameters*/
      lteCellSib3CfgGrp.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteCellSib3CfgGrp, MSM_LTE_CELL_SIB3_CONFIG_GROUP_PARAMETERS,cellIdx);
   }

   return;
}

void SmApplication::HandleLteCellSib1CfgGroupParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   u32 valueu32;
   std::vector<std::string> qRxLevMin;
   MsmLteCellSib1CfgGrp lteCellSib1CfgGrp;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(isDynCfg && msmGetCellSib1ConfigGroupParameters(&lteCellSib1CfgGrp,cellIdx) != ROK)
   {
      return;
   }

   /*Filling common parameters */
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PMAX,lteCellSib1CfgGrp.pMax);
   printf("PARAM_ID_LTE_PMAX:%d\n", lteCellSib1CfgGrp.pMax);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_QRX_LEVEL_MIN_SIB1, qRxLevMin);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qRxLevMin);
   lteCellSib1CfgGrp.cellSelectInfo.qRxLevMin = atoi(qRxLevMin.at(0).c_str());

   if(!isDynCfg)
   {
      /*For Initial configuration*/
      lteCellSib1CfgGrp.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_FREQ_BAND_INDICATOR,lteCellSib1CfgGrp.freqBandInd);
      printf("bandInd:%d\n", lteCellSib1CfgGrp.freqBandInd);
      lteCellSib1CfgGrp.cellSelectInfo.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_QRX_LEVEL_MIN_OFFSET,lteCellSib1CfgGrp.cellSelectInfo.qRxLevMinOffset);

      lteCellSib1CfgGrp.cellAccessInfo.actType = MSM_ACT_ADD;

      if( GetMibCache().IsMibAttributePresent(fapLteDn, PARAM_ID_LTE_CELL_IDENTITY))
      {
         GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CELL_IDENTITY, valueu32);
         lteCellSib1CfgGrp.cellAccessInfo.cellId = (unsigned long)valueu32;
         attrPresent |= CELL_ID_CFGD;
         TRACE_PRINTF("%s: VALUE OF LTE_CELL_IDENTITY IS SET",__func__);
         printf("cellIdentity:%d\n", lteCellSib1CfgGrp.cellAccessInfo.cellId);
      }
      else
      {
         TRACE_PRINTF("%s: VALUE OF LTE_CELL_IDENTITY IS NOT SET",__func__);
      }

      if( GetMibCache().IsMibAttributePresent(fapLteDn, PARAM_ID_LTE_TAC))
      {
         GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_TAC, lteCellSib1CfgGrp.cellAccessInfo.tac);
         attrPresent |= TAC_CFGD;
         TRACE_PRINTF("%s: VALUE OF LTE_TAC IS SET",__func__);
      }
      else
      {
         TRACE_PRINTF("%s: VALUE OF LTE_TAC IS NOT SET",__func__);
      }

      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CELL_BARRED,lteCellSib1CfgGrp.cellAccessInfo.cellBarred);

      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CSG_ID,valueu32);
      lteCellSib1CfgGrp.cellAccessInfo.csgIdentity = (unsigned long)valueu32;
      msmSetCellSib1ConfigGroupParameters(&lteCellSib1CfgGrp, false,cellIdx);
   }
   else
   {
      lteCellSib1CfgGrp.actType = MSM_ACT_MOD;
      lteCellSib1CfgGrp.cellSelectInfo.actType = MSM_ACT_MOD;

      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteCellSib1CfgGrp, MSM_LTE_CELL_SIB1_CONFIG_GROUP_PARAMETERS,cellIdx);
   }
   return;
}

void SmApplication::ReadLtePuschBasicCfgCommonParameters(MibDN fapLteDn,
      MsmLtePuschBasicCfgCommon &ltePuschBasicCfgCommon)
{
   std::vector<std::string> hoppingOffset;
   string s_hoppingMode;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_NSB,ltePuschBasicCfgCommon.nSb);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_HOPPING_MODE, s_hoppingMode);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrhoppingModeInfo, s_hoppingMode, m_posu8, 2);
   ltePuschBasicCfgCommon.hoppingMode = m_posu8;
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_HOPPING_OFFSET, hoppingOffset);
   printf("PARAM_ID_LTE_HOPPING_OFFSET:%s\n", hoppingOffset.at(0).c_str());
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hoppingOffset);
   ltePuschBasicCfgCommon.hoppingOffset = atoi(hoppingOffset.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_ENA_64QAM,ltePuschBasicCfgCommon.enable64QAM); 
}


void SmApplication::HandleLtePuschBasicCfgCommonParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLtePuschBasicCfgCommon ltePuschBasicCfgCommon;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   ReadLtePuschBasicCfgCommonParameters(fapLteDn,ltePuschBasicCfgCommon);

   if(!isDynCfg)
   {
      ltePuschBasicCfgCommon.actType = MSM_ACT_ADD;

      msmSetPuschBasicCfgCommonParameters(&ltePuschBasicCfgCommon, cellIdx);
   }
   else
   {
      ltePuschBasicCfgCommon.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&ltePuschBasicCfgCommon, MSM_LTE_PUSCH_BASIC_CFG_COMMON_PARAMETERS, cellIdx);
   }

   return;
}

void SmApplication::ReadLtePuschRefSignalCfgParameters(MibDN fapLteDn,MsmLtePuschRefSignalCfg &ltePuschRefSignalCfg)
{
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_GROUP_HOPPING_ENA,ltePuschRefSignalCfg.grpHopEnabled);
   printf("PARAM_ID_LTE_GROUP_HOPPING_ENA:%d\n", ltePuschRefSignalCfg.grpHopEnabled);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_GROUP_ASSIGNMENT_PUSCH,ltePuschRefSignalCfg.grpAsgnPusch);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SEQ_HOPPING_ENA,ltePuschRefSignalCfg.seqHopEnabled);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CYCLIC_SHIFT,ltePuschRefSignalCfg.cyclicShift);
}

void SmApplication::HandleLtePuschRefSignalCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLtePuschRefSignalCfg ltePuschRefSignalCfg;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   if(!isDynCfg)
   {
      ltePuschRefSignalCfg.actType = MSM_ACT_ADD;
      ReadLtePuschRefSignalCfgParameters(fapLteDn,ltePuschRefSignalCfg);

      msmSetPuschRefSignalCfgParameters(&ltePuschRefSignalCfg, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::ReadLtePucchCfgCommonParameters(MibDN fapLteDn,MsmLtePucchCfgCommon &ltePucchCfgCommon)
{
   std::vector<std::string> nRBCqi, n1PucchAn;
   string s_deltaShift;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DELTA_PUCCH_SHIFT,s_deltaShift);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrdeltaShiftInfo, s_deltaShift, m_posu8, 3);
   ltePucchCfgCommon.deltaShift=(MsmLteDeltaPucchShift)m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_NRBCQI, nRBCqi);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(nRBCqi);
   ltePucchCfgCommon.nRBCqi = atoi(nRBCqi.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_NCSAN, ltePucchCfgCommon.nCSAN);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_N1PUCCHAN, n1PucchAn);
   printf("PARAM_ID_LTE_N1PUCCHAN:%s\n", n1PucchAn.at(0).c_str());
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(n1PucchAn);
   ltePucchCfgCommon.n1PucchAn = atoi(n1PucchAn.at(0).c_str()); 
}

void SmApplication::HandleLtePucchCfgCommonParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLtePucchCfgCommon ltePucchCfgCommon;		
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   ReadLtePucchCfgCommonParameters(fapLteDn,ltePucchCfgCommon);
   if(s_isN1PucchUpdateFromRRM)
   {
      s_isN1PucchUpdateFromRRM=false;
      return;
   }

   if(!isDynCfg)
   {
      ltePucchCfgCommon.actType = MSM_ACT_ADD;
      msmSetPucchCfgCommonParameters(&ltePucchCfgCommon,cellIdx);
   }
   else
   {
      ltePucchCfgCommon.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&ltePucchCfgCommon,MSM_LTE_PUCCH_CFG_COMMON_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::ReadLteSRSCfgCommonParameters(MibDN fapLteDn,MsmLteSRSCfgCommon &lteSRSCfgCommon)
{
   std::vector<std::string> s_cSrs;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SRS_ENA,lteSRSCfgCommon.enable);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SRS_BANDWIDTH_CFG, s_cSrs);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrcSrsInfo, s_cSrs.at(0), m_posu8, 8);
   lteSRSCfgCommon.cSrs=m_posu8;
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_ACK_NACK_SRS_TRNASMISSION,lteSRSCfgCommon.simulAckNackSrs);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SRS_MAX_UP_PTS,lteSRSCfgCommon.srsMaxUpts); 
   printf("PARAM_ID_LTE_SRS_MAX_UP_PTS:%d\n", lteSRSCfgCommon.srsMaxUpts);
}

void SmApplication::HandleLteSRSCfgCommonParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteSRSCfgCommon lteSRSCfgCommon;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);


   if(!isDynCfg)
   {
      lteSRSCfgCommon.actType = MSM_ACT_ADD;
      ReadLteSRSCfgCommonParameters(fapLteDn,lteSRSCfgCommon);
      msmSetSrsCfgCommonParameters(&lteSRSCfgCommon,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadUeTimerConstantsParams(MibDN fapLteDn, MsmLteUeTimerConstants &lteUeTimerConstants)
{
   TRACE_PRINTF("%s\n",__func__);

   vector<u32> t300, t301, t304, t310, t311, ccoT304;
   u32 t302, n310, n311, t320;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T300, t300);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrt300Info, t300.at(0), m_posu16);
   lteUeTimerConstants.t300 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T301, t301);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrt301Info, t301.at(0), m_posu16);
   lteUeTimerConstants.t301 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T302, t302);
   lteUeTimerConstants.t302 = t302;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T304EUTRA, t304);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrt304Info, t304.at(0), m_posu16);
   lteUeTimerConstants.t304 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T304IRAT, ccoT304);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrccoT304Info, ccoT304.at(0), m_posu16);
   lteUeTimerConstants.ccoT304 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T310, t310);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrt310Info, t310.at(0), m_posu16);
   lteUeTimerConstants.t310 = m_posu16;
   printf("t310:%d\n", lteUeTimerConstants.t310);

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_N310, n310);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrn310Info, n310, m_posu16);
   lteUeTimerConstants.n310 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T311, t311);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrt311Info, t311.at(0), m_posu16);
   lteUeTimerConstants.t311 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_N311, n311);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrn311Info, n311, m_posu16);
   lteUeTimerConstants.n311 = m_posu16;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_T320, t320);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrt320Info, t320, m_posu16);
   lteUeTimerConstants.t320 = m_posu16; 
}

void SmApplication::HandleLteUeTimerConstantsParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteUeTimerConstants lteUeTimerConstants;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   ReadUeTimerConstantsParams(fapLteDn, lteUeTimerConstants);

   if(!isDynCfg)
   {
      lteUeTimerConstants.actType = MSM_ACT_ADD;
      msmSetUeTimerConstantsParameters(&lteUeTimerConstants,cellIdx);
   }
   else
   {
      lteUeTimerConstants.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteUeTimerConstants, MSM_LTE_UE_TIMER_CONSTANTS_PARAMETERS, cellIdx);
   }

   return;
}

void SmApplication::ReadLteCellSib9CfgGrpParameters(MibDN dn,MsmLteCellSib9CfgGrp &lteCellSib9CfgGrp)
{
   string henbNameString;
   u16 idx; 

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_HOME_NODEB_NAME, henbNameString);

   for(idx=0;idx < henbNameString.length();idx++)
   {
      lteCellSib9CfgGrp.henbName[idx] =henbNameString[idx];
   }	
   TRACE_PRINTF("HeNB Name is %s",lteCellSib9CfgGrp.henbName);
}

void SmApplication::HandleLteCellSib9CfgGrpParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteCellSib9CfgGrp lteCellSib9CfgGrp;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadLteCellSib9CfgGrpParameters(dn,lteCellSib9CfgGrp);
      lteCellSib9CfgGrp.actType = MSM_ACT_ADD;

      msmSetCellSib9CfgGrpParameters(&lteCellSib9CfgGrp,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadLteCellSib6CfgGroupParameters(MibDN dn,MsmLteCellSib6CfgGrp &lteCellSib6CfgGrp)
{
   std::vector<std::string> tReselection;
   u32 tReselectionSfMedium,tReselectionSfHigh;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_T_RESELECTION_UTRA, tReselection);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tReselection);
   lteCellSib6CfgGrp.tReselection = atoi(tReselection.at(0).c_str());
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_T_RESELECTION_UTRA_SF_MED, tReselectionSfMedium);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo, tReselectionSfMedium, m_posu8);
   lteCellSib6CfgGrp.tReselectionSfMedium = m_posu8;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_T_RESELECTION_UTRA_SF_HIGH, tReselectionSfHigh);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo, tReselectionSfHigh, m_posu8);
   lteCellSib6CfgGrp.tReselectionSfHigh = m_posu8;
}

void SmApplication::HandleLteCellSib6CfgGroupParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s",__func__);
   MsmLteCellSib6CfgGrp lteCellSib6CfgGrp;	

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadLteCellSib6CfgGroupParameters(dn,lteCellSib6CfgGrp);
      lteCellSib6CfgGrp.actType = MSM_ACT_ADD;
      msmSetCellSib6ConfigGroupParameters(&lteCellSib6CfgGrp,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadAcBarringInfoParams(MibDN fapLteDn, MsmLteAcBarringInfo &lteAcBarringInfo)
{
   TRACE_PRINTF("%s\n",__func__);

   string s_acBarringFactorMoData;
   string s_acBarringTimeMoData;
   string s_acBarringFactorMoSig;
   string s_acBarringTimeMoSig;

   lteAcBarringInfo.actType = MSM_ACT_ADD;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_BARRING_FOR_EMERGENCY,lteAcBarringInfo.acBarringForEmergency);
   GetMibCache().GetMibAttributeAsString(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MOSIG,s_acBarringFactorMoSig);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessBarringFactor, s_acBarringFactorMoSig, m_posu8,16);
   lteAcBarringInfo.acBarringForMOSignal.acBarringFactor = m_posu8;
   GetMibCache().GetMibAttributeAsString(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_TIME_FOR_MOSIG,s_acBarringTimeMoSig);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessBarringTime, s_acBarringTimeMoSig, m_posu8,8);
   lteAcBarringInfo.acBarringForMOSignal.acBarringTime = m_posu8;
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MOSIG,lteAcBarringInfo.acBarringForMOSignal.acBarringAC11);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MOSIG,lteAcBarringInfo.acBarringForMOSignal.acBarringAC12);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MOSIG,lteAcBarringInfo.acBarringForMOSignal.acBarringAC13);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MOSIG,lteAcBarringInfo.acBarringForMOSignal.acBarringAC14);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MOSIG,lteAcBarringInfo.acBarringForMOSignal.acBarringAC15);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_ENABLE_FOR_MOSIG, lteAcBarringInfo.barringSignalUsage);
   GetMibCache().GetMibAttributeAsString(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MODATA,s_acBarringFactorMoData);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessBarringFactor, s_acBarringFactorMoData, m_posu8,16);
   lteAcBarringInfo.acBarringForMOData.acBarringFactor = m_posu8;
   GetMibCache().GetMibAttributeAsString(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_TIME_FOR_MODATA,s_acBarringTimeMoData);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessBarringTime, s_acBarringTimeMoData, m_posu8,8);
   lteAcBarringInfo.acBarringForMOData.acBarringTime = m_posu8;
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MODATA,lteAcBarringInfo.acBarringForMOData.acBarringAC11);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MODATA,lteAcBarringInfo.acBarringForMOData.acBarringAC12);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MODATA,lteAcBarringInfo.acBarringForMOData.acBarringAC13);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MODATA,lteAcBarringInfo.acBarringForMOData.acBarringAC14);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MODATA,lteAcBarringInfo.acBarringForMOData.acBarringAC15);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_AC_BARRING_ENABLE_FOR_MODATA, lteAcBarringInfo.barringDataUsage); 
}

void SmApplication::HandleLteAcBarringInfoParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s",__func__);
   MsmLteAcBarringInfo lteAcBarringInfo;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   ReadAcBarringInfoParams(fapLteDn, lteAcBarringInfo);

   if(!isDynCfg)
   {
      msmSetAcBarringInfoParameters(&lteAcBarringInfo, cellIdx);
   }
   else
   {
      lteAcBarringInfo.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteAcBarringInfo, MSM_LTE_AC_BARRING_INFO_PARAMETERS,cellIdx);
   }

   return;
}

void SmApplication::ReadLteSib4CsgInfoParameters(MibDN dn,MsmLteSib4CsgInfo &lteSib4CsgInfo)
{
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CSG_START_PCI,lteSib4CsgInfo.csgStartPhyCellId); 
   lteSib4CsgInfo.isCsgPciCfgd = MSM_TRUE;
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CSG_PCI_RANGE,lteSib4CsgInfo.csgPciRange); 
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_PCI_RANGE2_OFFSET,lteSib4CsgInfo.csgRange2Offset); 
}

void SmApplication::HandleLteSib4CsgInfoParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s",__func__);
   MsmLteSib4CsgInfo lteSib4CsgInfo;

   if(!isDynCfg)
   { 
      MibDN faplteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadLteSib4CsgInfoParameters(faplteDn,lteSib4CsgInfo);
      lteSib4CsgInfo.actType = MSM_ACT_ADD;
      msmSetSib4CsgInfoParameters(&lteSib4CsgInfo,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadLteTddParameters(MibDN dn,MsmLteTddParam &lteTddParam)
{
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_TDD_MAX_SFCONFIG_LIST_ENTRIES,lteTddParam.sfconfigMaxEntries);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_TDD_SFCONFIG_LIST_NUMBER_OF_ENTRIES,lteTddParam.sfconfigNumEntries);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_TDD_SYNC_STRATUM_ID,lteTddParam.syncStratumId);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_TDD_SUBFRAME_ASSIGNMENT,lteTddParam.subframeAssignment); 
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_TDD_SPECIAL_SUB_FRAME_PATTERNS,lteTddParam.specialSubFramePattern);
}

void SmApplication::HandleLteTddParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteTddParam lteTddParam;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      lteTddParam.actType = MSM_ACT_ADD;
      ReadLteTddParameters(fapLteDn,lteTddParam);

      msmSetTddParameters(&lteTddParam,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadLtePcchConfigCommonParameters(MibDN fapLteDn,MsmLtePCCHCfgCommon &ltePCCHCfgCommon)
{
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DEFAULT_PAGING_CYCLE,ltePCCHCfgCommon.defaultPagingCycle); 
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DEFAULT_PCCH_CFG_NB,ltePCCHCfgCommon.nB);
}

void SmApplication::HandleLtePcchConfigCommonParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s",__func__);
   MsmLtePCCHCfgCommon ltePCCHCfgCommon;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   ReadLtePcchConfigCommonParameters(fapLteDn,ltePCCHCfgCommon);

   if(!isDynCfg)
   {
      ltePCCHCfgCommon.actType = MSM_ACT_ADD;
      msmSetPcchConfigCommonParameters(&ltePCCHCfgCommon,cellIdx);
   }
   else
   {
      ltePCCHCfgCommon.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&ltePCCHCfgCommon, MSM_LTE_PCCH_CONFIG_COMMON_PARAMETERS, cellIdx);
   }

   return;
}

void SmApplication::ReadBarringConfig1xRTTCfg(MibDN dn,MsmBarringConfig1xRTTCfg &barringConfig1xRTTCfg)
{
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_0TO9_R9,barringConfig1xRTTCfg.ac_Barring0to9_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_10_R9,barringConfig1xRTTCfg.ac_Barring10_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_11_R9,barringConfig1xRTTCfg.ac_Barring11_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_12_R9,barringConfig1xRTTCfg.ac_Barring12_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_13_R9,barringConfig1xRTTCfg.ac_Barring13_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_14_R9,barringConfig1xRTTCfg.ac_Barring14_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_15_R9,barringConfig1xRTTCfg.ac_Barring15_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_MSG_R9,barringConfig1xRTTCfg.ac_BarringMsg_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_REG_R9,barringConfig1xRTTCfg.ac_BarringReg_r9);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_AC_BRNG_EMG_R9,barringConfig1xRTTCfg.ac_BarringEmg_r9);
}

void SmApplication::HandleBarringConfig1xRTTCfg
(
 u16   cellIdx,
 bool  isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmBarringConfig1xRTTCfg barringConfig1xRTTCfg;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadBarringConfig1xRTTCfg(dn,barringConfig1xRTTCfg);
      barringConfig1xRTTCfg.actType = MSM_ACT_MOD;

      msmSetBarringCfg1xRtt(&barringConfig1xRTTCfg,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadSib8Parameters(MibDN dn,MsmCellSib8CfgGrp &cellSib8CfgGrp)
{
   std::vector<std::string> tReselection;
   string longCodeState;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_CDMA_EUTRA_TIME_SYNC,cellSib8CfgGrp.cdmaEutraTimeSync);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_T_RESEL_CDMA2K, tReselection);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tReselection);
   cellSib8CfgGrp.tReselection = atoi(tReselection.at(0).c_str());
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SPEED_STATE_PRES,cellSib8CfgGrp.speedStatePres);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_T_RESEL_CDMA2K_SF_MED, cellSib8CfgGrp.sfMedium);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo, cellSib8CfgGrp.sfMedium, cellSib8CfgGrp.sfMedium);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_T_RESEL_CDMA2K_SF_HIGH, cellSib8CfgGrp.sfHigh);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo, cellSib8CfgGrp.sfHigh, cellSib8CfgGrp.sfHigh);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_SID, cellSib8CfgGrp.cdma1xrttRegParams.sid);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_NID, cellSib8CfgGrp.cdma1xrttRegParams.nid);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_MUL_SID,cellSib8CfgGrp.cdma1xrttRegParams.mulSID);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_MUL_NID,cellSib8CfgGrp.cdma1xrttRegParams.mulNID);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_HOME_REG,cellSib8CfgGrp.cdma1xrttRegParams.homeReg);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_FOREIGN_SID_REG,cellSib8CfgGrp.cdma1xrttRegParams.foreignSIDReg);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_FOREIGN_NID_REG,cellSib8CfgGrp.cdma1xrttRegParams.foreignNIDReg);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_PARAM_REG,cellSib8CfgGrp.cdma1xrttRegParams.paramReg);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_PWR_UP_REG,cellSib8CfgGrp.cdma1xrttRegParams.powerUpReg);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_REG_PERIOD,cellSib8CfgGrp.cdma1xrttRegParams.regPeriod);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_REG_ZONE, cellSib8CfgGrp.cdma1xrttRegParams.regZone);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_TOTAL_ZONE,cellSib8CfgGrp.cdma1xrttRegParams.totalZone);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_ZONE_TIMER, cellSib8CfgGrp.cdma1xrttRegParams.zoneTimer);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SIB8_PWR_DOWN_REG, cellSib8CfgGrp.cdma1xrttRegParams.powerDownReg);
}

void SmApplication::HandleSib8Parameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmCellSib8CfgGrp cellSib8CfgGrp;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadSib8Parameters(dn,cellSib8CfgGrp);
      cellSib8CfgGrp.actType = MSM_ACT_ADD;

      msmSetSib8Parameters(&cellSib8CfgGrp,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::ReadSib7CfgParameters(MibDN dn,MsmLteCellSib7CfgGrp &sib7CfgGrp)
{
   std::vector<std::string> tReselectionGERAN;
   u32 tResetEutraSFMedium,tResetEutraSFHigh;
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_T_RESEL, tReselectionGERAN);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tReselectionGERAN);
   sib7CfgGrp.tReselectionGERAN = atoi(tReselectionGERAN.at(0).c_str());
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_PRES_SPEED_SCALE, sib7CfgGrp.pres_SpeedStateScaleFactors);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_T_RESEL_SF_MED, tResetEutraSFMedium);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtResetEutraSFInfo, tResetEutraSFMedium, m_posu8);
   sib7CfgGrp.tReselectionGERANSFMedium = m_posu8;
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_T_RESEL_SF_HIGH, tResetEutraSFHigh);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtResetEutraSFInfo, tResetEutraSFHigh, m_posu8);
   sib7CfgGrp.tReselectionGERANSFHigh = m_posu8;
}

void SmApplication::HandleSib7CfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s",__func__);
   MsmLteCellSib7CfgGrp sib7CfgGrp;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadSib7CfgParameters(dn,sib7CfgGrp);

      msmSetsib7CfgGrpParameters(&sib7CfgGrp,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::HandleTimeAlgmtCfgParameters
(
 u16   cellIdx,
 bool  isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmSib2Cfg               sib2Cfg;
   MsmMacMainConifg         macMainConfig;

   if(!isDynCfg)
   {
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      sib2Cfg.actType = MSM_ACT_ADD; 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_TIME_ALIGNMENT_TIMER_COMMON, sib2Cfg.timeAlignmentCommon);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_TIME_ALIGNMENT_TIMER_DEDICATED, macMainConfig.timeAlignmentTimerDedicated);

      msmSetSib2Cfg(&sib2Cfg, cellIdx);
      msmSetMacMainConfig(&macMainConfig, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }

   return;
}


void SmApplication::HandlerEmpty(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   return;
}

void SmApplication::HandleLteAdminStateChange(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_FAP_ADMIN_STATE,m_adminState);

   if((m_adminState)&&(MSM_TRUE==SmApplication::s_adminFlag))
   {
      SmApplication::GetInstance().startAdminFlagTimer(100);
      callBackTo=ADMIN_CHANGE;
      return;
   }

   if(MSM_FALSE == m_adminState)
   {
      /*Admin state is LOCKED i.e 0*/
      if(MSM_FALSE == m_smmInitialConfigComplete)
      {
         TRACE_PRINTF("\nWaiting for Admin state from HeMS");
      }
      else
      {
         SmMultiInstanceObjectManager::GetInstance().resetMIO(MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR_IN_USE);
         SmMultiInstanceObjectManager::GetInstance().resetMIO(MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE);
         SmMultiInstanceObjectManager::GetInstance().resetMIO(MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST);
         /*Service affecting parameter update from HeMS,hence locked again*/	
         TRACE_PRINTF("\nAdmin state LOCKED by HeMS");
         adminDownFlagSet();
         SetLteOperationalState(0);

         MsmStartStopStackReq(MSM_FALSE,m_adminState,MSM_FALSE);
      }
   }
   else
   {
      /*Admin state is UNLOCKED i.e m_adminState == 1*/
      if(MSM_FALSE == m_smmInitialConfigComplete)
      {
         /*eNodeB stack configuartion is still pending*/
         if(MSM_TRUE == m_oneTimeInitialisation)
         {
            if(BASIC_CFG_CFGD == attrPresent)
            {
               TRACE_PRINTF("%s: Initialisation of eNodeB triggered",__func__);

               string secGwIpStr[3];
               IPv4Address secGwIpAddr[3];
               u32 secGwIp[3];

               GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SEC_GW_SERVER_1, secGwIpStr[0]);
               GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SEC_GW_SERVER_2, secGwIpStr[1]);
               GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SEC_GW_SERVER_3, secGwIpStr[2]);

               secGwIpAddr[0] = IPv4Address(secGwIpStr[0].c_str());
               secGwIpAddr[1] = IPv4Address(secGwIpStr[1].c_str());
               secGwIpAddr[2] = IPv4Address(secGwIpStr[2].c_str());

               secGwIp[0] = htonl(secGwIpAddr[0].Get());
               secGwIp[1] = htonl(secGwIpAddr[1].Get());
               secGwIp[2] = htonl(secGwIpAddr[2].Get());

               if((!IsIpSet(secGwIpStr[0])) && (!IsIpSet(secGwIpStr[1])) && (!IsIpSet(secGwIpStr[2])))
               {
                  if ((isStackStart() == true))
                  {
                     m_messengerInitialConfigComplete = MSM_TRUE;
                     FillNeighCellCfgParameters();
                     MsmEnodeBinitialCfgComplete();
                  }
               }
            }
            else     
            {     
               TRACE_PRINTF("%s: INCOMPLETE CONFIGURATIONS FOR ADMIN STATE UP attrPresent : %d",__func__, attrPresent);
            } 

            /*This condition is required to avoid sending initial configuration twice*/
            /*Here is the scenerio that may cause problem, to avoid which this check was added
              -> Admin state is 0
              -> Initial configuration of the oam-sm(messenger) is complete
              -> Waiting for Admin state to be set
              -> Admin state is set to 1(Non-volatile parameter)
              -> smm(stack) Intialisation begins
              -> smm(stack) Initialisation completes
              -> Cell-Up happens
              -> Now, kill enodeB binary and execute again.
              -> Since Admin state is already 1 and subscribed at the beginning, the handle
              will come to this part. If this condition is missing initialisation will 
              be triggered even before parameters are filled. 
              After parameters are filled, Initialsation is triggered again which is wrong.
              -> Also, we cannot move the Admin state subscription to the end as it will affect the 				   Dynamic handling of parameters, HENCE THIS CHECK. 
              */
         }
      }
      else
      {
         TRACE_PRINTF("%s: Admin state UNLOCKiED by HeMS",__func__);
         FillNeighCellCfgParameters();
         MsmStartStopStackReq(MSM_FALSE,m_adminState,MSM_FALSE);
      }
   }
   return;
}

void HandleMmeIp(std::vector<std::string> ipString, u32 idx, u32 *dstIp)
{
   TRACE_PRINTF("%s",__func__);

   IPv4Address ipv4;
   u32         ip;

   if(ipString.size() > idx)
   {
      ipv4 = IPv4Address(ipString.at(idx).c_str());
      TRACE_PRINTF("secondary MME IP(%d)=%s",idx,ipv4.ToString()); 
      ip = htonl(ipv4.Get());
      if (ip<0)
      {
         ip = ip*(-1);
      }
      *dstIp = ip;
   } 
}

void SmApplication::ReadLteRimParameters
(
 MibDN fapLteDn,
 MsmLteRimParams &lteRimParams
 )
{
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_RIM_TIMER_RIR_VALUE,
         lteRimParams.rimRirTmr);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_RIM_TIMER_RI_VALUE,
         lteRimParams.rimRiTmr);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_RIM_RAE_VALUE,
         lteRimParams.rimRiaeTmr);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_RIM_MAX_RETRY_COUNT,
         lteRimParams.rimMaxRetryCnt);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_RIM_OVERALL_TIMER_VALUE,
         lteRimParams.rimOvrlTmrVal);

}

void SmApplication::HandleLteRimParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteRimParams lteRimParams;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   if(!isDynCfg)
   {
      ReadLteRimParameters(fapLteDn,lteRimParams);
      msmSetRimParameters(&lteRimParams,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation\
            will occur after reboot.");
   }
}

void SmApplication::ReadLteeNodeBIPParameters
(
 MibDN                  dn,
 MsmLteeNodeBIPparams   *lteeNodeBIPparams
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> siglinkserverlist;
   std::vector<std::string> secIp1list;
   std::vector<std::string> secIp2list;
   std::vector<std::string> secIp3list;
   std::vector<std::string> secIp4list;
   std::string initStr = "";
   std::vector<std::string> vctrInit;
   vctrInit.push_back(initStr);
   IPv4Address siglinkip;
   IPv6Address mmeIpv6;
   u8 no_of_IPs = 0;
   string s_s1connmode;
   u32 sigip = 0;
   u8 sigipv6[16] ={ 0};
   u16 idx;
   char ipbuf[150];
   IPAddress checkip;

   for(idx = 0; idx < MAX_NUM_OF_IP; idx++)
   {
      ResetIP(&lteeNodeBIPparams->lteSiglinkserverlist[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp1[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp2[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp3[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp4[idx],TYPE_INVALID);
   }
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_S1CON_MODE,s_s1connmode);
   TRACE_PRINTF("s1conn mode is %s",s_s1connmode.c_str());

   if(GetMibCache().IsMibAttributePresent(dn,PARAM_ID_LTE_SIGLINK_SERVER_LIST))
   {
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SIGLINK_SERVER_LIST,
            siglinkserverlist);
      printf("mme ip:%s\n",siglinkserverlist.at(0).c_str());
      attrPresent |= MME_IP_CFGD;
      TRACE_PRINTF("%s: VALUE OF LTE_SIGLINK_SERVER_LIST IS SET",__func__);

      ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_1, secIp1list, vctrInit);
      ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_2, secIp2list, vctrInit);
      ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_3, secIp3list, vctrInit);
      ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_4, secIp4list, vctrInit);

      checkip.Set(siglinkserverlist.at(0).c_str());
      if(!checkip.CheckIfIPv6())
      {
         HandleMmeIp(siglinkserverlist, 0, &sigip);
      }
      else
      {
         TRACE_PRINTF("%s: MME IPV6 ADDRESS =  %s",__func__, 
               siglinkserverlist.at(0).c_str());
         mmeIpv6 = IPv6Address(siglinkserverlist.at(0).c_str());
         if(! mmeIpv6.Get(sigipv6))
         {
            TRACE_PRINTF("%s: Retrieval of MME IPV6 Failed",__func__);
            return;
         }
         else
         {
            sprintf(ipbuf,"%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x%x",\
                  sigipv6[0],sigipv6[1],sigipv6[2],sigipv6[3],sigipv6[4],
                  sigipv6[5],sigipv6[6],sigipv6[7],sigipv6[8],sigipv6[9],
                  sigipv6[10],sigipv6[11],sigipv6[12],sigipv6[13],sigipv6[14],
                  sigipv6[15]);

            TRACE_PRINTF("%s: **** MME IPV6 %s\n",__func__, ipbuf);
         }
         /* this code will be used when IPV6 code will be availabe */
         memcpy(&lteeNodeBIPparams->lteSiglinkserverlist[0].mmeipv6,&sigipv6,
               sizeof(sigipv6));
         lteeNodeBIPparams->lteSiglinkserverlist[0].ipv6pres = TRUE;
      }
      if(IsIpSet(siglinkserverlist.at(0)))
      {
         FillIp(siglinkserverlist,no_of_IPs,
               &lteeNodeBIPparams->lteSiglinkserverlist[no_of_IPs]);
         FillIp(secIp1list,no_of_IPs,
               &lteeNodeBIPparams->lteSecIp1[no_of_IPs]);
         FillIp(secIp2list,no_of_IPs,
               &lteeNodeBIPparams->lteSecIp2[no_of_IPs]);
         FillIp(secIp3list,no_of_IPs,
               &lteeNodeBIPparams->lteSecIp3[no_of_IPs]);
         FillIp(secIp4list,no_of_IPs,
               &lteeNodeBIPparams->lteSecIp4[no_of_IPs]);
         ++no_of_IPs;
      }
      else
      {
         lteeNodeBIPparams->lteS1connmode = 0;
         TRACE_PRINTF("%s:%d MME IP(0)=%s NOT passed onto to the stack",
               __func__,__LINE__,siglinkip.ToString());
      }
      if(!strcmp("All",s_s1connmode.c_str()))
      {
         for(idx = 1; idx < siglinkserverlist.size(); idx++)
         {
            if(IsIpSet(siglinkserverlist.at(idx)))
            {
               FillIp(siglinkserverlist,no_of_IPs,
                     &lteeNodeBIPparams->lteSiglinkserverlist[no_of_IPs]);
               FillIp(secIp1list,no_of_IPs,
                     &lteeNodeBIPparams->lteSecIp1[no_of_IPs]);
               FillIp(secIp2list,no_of_IPs,
                     &lteeNodeBIPparams->lteSecIp2[no_of_IPs]);
               FillIp(secIp3list,no_of_IPs,
                     &lteeNodeBIPparams->lteSecIp3[no_of_IPs]);
               FillIp(secIp4list,no_of_IPs,
                     &lteeNodeBIPparams->lteSecIp4[no_of_IPs]);
               ++no_of_IPs;
            }
         }
      }
      else
      {
         /*Data already filled for one MME*/
      }
      lteeNodeBIPparams->lteS1connmode = no_of_IPs;
   }
   else
   {
      TRACE_PRINTF("%s: VALUE OF LTE_SIGLINK_SERVER_LIST IS NOT SET",__func__);
   }
   TRACE_PRINTF("%s:%d lteS1connmode = %d",__func__,__LINE__,
         lteeNodeBIPparams->lteS1connmode);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_S1SIG_LINK_PORT,
         lteeNodeBIPparams->sctpPortNumS1);

   return;
}

void SmApplication::HandleLteeNodeBIPParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> siglinkserverlist;
   std::vector<std::string> secIp1list;
   std::vector<std::string> secIp2list;
   std::vector<std::string> secIp3list;
   std::vector<std::string> secIp4list;
   IPv4Address siglinkip;
   IPv6Address mmeIpv6;
   string s_s1connmode;
   MsmLteeNodeBIPparams lteeNodeBIPparams;
   IPAddress checkip;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);
   ReadLteeNodeBIPParameters(dn, &lteeNodeBIPparams);

   if(!isDynCfg)
   {
      lteeNodeBIPparams.actType = MSM_ACT_ADD;
      msmSetEnodebIpParameters(&lteeNodeBIPparams);
   }
   else
   {
      lteeNodeBIPparams.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteeNodeBIPparams,
            MSM_LTE_ENODEB_IP_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::HandleLogUpload(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__); 

   u32 timer_value=0;

   if(IsTimerRunning(m_logTimerHandle)) 
   { 
      DeleteTimer(m_logTimerHandle); 
   } 
   GetMibCache().GetMibAttribute((MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP)),
         PARAM_ID_LOG_UPLOAD_INTERVAL,timer_value); 
   if(timer_value > 0) 
   { 
      SmApplication::GetInstance().StartLogTimer(timer_value*60000); 
   } 
   else 
   { 
      TRACE_PRINTF("\nLOG UPLOAD FUNCTIONALITY IS DISABLED"); 
   } 
} 

void SmApplication::StartLogTimer(u32 timer_value) 
{ 
   TRACE_PRINTF("%s",__func__);

   m_logTimerHandle = CreateTimer((const std::string&)"LOG expiration timeout",
         timer_value ,TimerEngineInterface::TIMER_START_NOW, 
         TimerEngineInterface::TIMER_SINGLE_SHOT); 
}

void SmApplication::HandleDynamicIPConfigChange
(
 MsmLteeNodeBIPparams *lteeNodeBIPparams
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> siglinkserverlist;
   std::vector<std::string> secIp1list;
   std::vector<std::string> secIp2list;
   std::vector<std::string> secIp3list;
   std::vector<std::string> secIp4list;
   std::string initStr = "";
   std::vector<std::string> vctrInit;
   vctrInit.push_back(initStr);
   IPv4Address siglinkip;
   IPv6Address enbIpv6;
   u8 no_of_IPs = 0;
   string s_s1connmode;
   u16 idx;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   for(idx = 0; idx < MAX_NUM_OF_IP; idx++)
   {
      ResetIP(&lteeNodeBIPparams->lteSiglinkserverlist[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp1[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp2[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp3[idx],TYPE_INVALID);
      ResetIP(&lteeNodeBIPparams->lteSecIp4[idx],TYPE_INVALID);
   }
   lteeNodeBIPparams->actType = MSM_ACT_ADD;
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_S1CON_MODE,s_s1connmode);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SIGLINK_SERVER_LIST,
         siglinkserverlist);
   ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_1,secIp1list, vctrInit);
   ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_2,secIp2list, vctrInit);
   ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_3,secIp3list, vctrInit);
   ReadIfPresent(dn, PARAM_ID_LTE_OAM_SECONDARY_IP_4,secIp4list, vctrInit);
   if(IsIpSet(siglinkserverlist.at(0)))
   {
      FillIp(siglinkserverlist,0,
            &lteeNodeBIPparams->lteSiglinkserverlist[no_of_IPs]);
      FillIp(secIp1list,0,&lteeNodeBIPparams->lteSecIp1[no_of_IPs]);
      FillIp(secIp2list,0,&lteeNodeBIPparams->lteSecIp2[no_of_IPs]);
      FillIp(secIp3list,0,&lteeNodeBIPparams->lteSecIp3[no_of_IPs]);
      FillIp(secIp4list,0,&lteeNodeBIPparams->lteSecIp4[no_of_IPs]);
      ++no_of_IPs;
   }
   if(!strcmp("All",s_s1connmode.c_str()))
   {
      for(idx = 1; idx < siglinkserverlist.size(); idx++)
      {
         if(IsIpSet(siglinkserverlist.at(0)))
         {
            FillIp(siglinkserverlist,idx,
                  &lteeNodeBIPparams->lteSiglinkserverlist[no_of_IPs]);
            FillIp(secIp1list,idx,&lteeNodeBIPparams->lteSecIp1[no_of_IPs]);
            FillIp(secIp2list,idx,&lteeNodeBIPparams->lteSecIp2[no_of_IPs]);
            FillIp(secIp3list,idx,&lteeNodeBIPparams->lteSecIp3[no_of_IPs]);
            FillIp(secIp4list,idx,&lteeNodeBIPparams->lteSecIp4[no_of_IPs]);
            ++no_of_IPs;
         }
      }
   }
   else
   {
      /*Data already filled for one MME*/
   }
   lteeNodeBIPparams->lteS1connmode = no_of_IPs;
   TRACE_PRINTF("lteS1connmode = %d",lteeNodeBIPparams->lteS1connmode);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_S1SIG_LINK_PORT,
         lteeNodeBIPparams->sctpPortNumS1);

   return;
}

void SmApplication::ReadLteCQIPeriodicReportCfgParameters
(
 MibDN                      dn,
 MsmLteCQIPeriodicReportCfg *lteCQIPeriodicReportCfg
 )
{
   std::vector<std::string> cqiPucchResourceIdx;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CQI_PUCCH_RESOURCE_IDX, 
         cqiPucchResourceIdx);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(cqiPucchResourceIdx);
   lteCQIPeriodicReportCfg->cqi_PUCCH_ResourceIdx = 
      atoi(cqiPucchResourceIdx.at(0).c_str());

   lteCQIPeriodicReportCfg->subBandCQI.actType = MSM_ACT_ADD;
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_K,
         lteCQIPeriodicReportCfg->subBandCQI.k);

   return;
}

void SmApplication::HandleLteCQIPeriodicReportCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteCQIPeriodicReportCfg lteCQIPeriodicReportCfg;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
      ReadLteCQIPeriodicReportCfgParameters(dn,&lteCQIPeriodicReportCfg);

      lteCQIPeriodicReportCfg.actType = MSM_ACT_ADD;
      msmSetCqiPeriodicReportCfgParameters(&lteCQIPeriodicReportCfg,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }

   return;
}

void SmApplication::HandleLteCellEAIDCfgGrpParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   u32 valueu32; 
   MsmLteCellEAIDCfgGrp lteCellEAIDCfgGrp;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

      lteCellEAIDCfgGrp.actType = MSM_ACT_ADD;

      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_EAID, valueu32);
      lteCellEAIDCfgGrp.eaid[0] = (unsigned long)valueu32;
      msmSetCellEaidCfgGrpParameters(&lteCellEAIDCfgGrp, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::HandleLteRabPolicyCfgGrpParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteRabPolicyCfgGrp lteRabPolicyCfgGrp;

   if(!isDynCfg)
   {
      MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

      lteRabPolicyCfgGrp.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_IS_DSCP_ENABLE,
            lteRabPolicyCfgGrp.isDscpEnable);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI1_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[0].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI2_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[1].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI3_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[2].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI4_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[3].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI5_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[4].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI6_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[5].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI7_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[6].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI8_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[7].dscpInfo.dscp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_QCI9_DSCP_MAP,
            lteRabPolicyCfgGrp.drbPolicy[8].dscpInfo.dscp);

      msmSetRabPolicyCfgGrpDrbParameters(&lteRabPolicyCfgGrp,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::ReadLteSrb1PolicyCfgGrpParameters
(
 MibDN                  dn,
 MsmLteRabPolicyCfgGrp  *lteRabPolicyCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> tpRetransmit, timerReordering, timerStatusProhibit;
   vector<u32> pollPdu, pollByte, maxRetransThresh;
   MsmLteSrbRlcInfo   *rlcInfo;
   rlcInfo = &lteRabPolicyCfgGrp->srbPolicy[MSM_SRB1].rlcInfo;

   lteRabPolicyCfgGrp->srbPolicy[MSM_SRB1].srbId = MSM_SRB_ID_1;

   rlcInfo->srbId = MSM_SRB_ID_1;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DEFAULT_CFG_SRB1, 
         rlcInfo->srbDefaultCfg);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TPOLL_RE_TRANSMIT_SRB1,
         tpRetransmit);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tpRetransmit);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtpRetransmitInfo,
         atoi(tpRetransmit.at(0).c_str()), m_posu8);

   rlcInfo->tpRetransmit = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_POLL_PDU_SRB1, pollPdu);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrpollPduInfo, pollPdu.at(0),
         m_posu8);
   rlcInfo->pollPdu = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_POLL_BYTE_SRB1, pollByte);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrpollByteInfo, pollByte.at(0),
         m_posu8);
   rlcInfo->pollByte = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_RE_TX_THRESHOLD_SRB1,
         maxRetransThresh);
   printf("PARAM_ID_LTE_MAX_RE_TX_THRESHOLD_SRB1:%d\n", maxRetransThresh.at(0));
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrmaxRetransThreshInfo, 
         maxRetransThresh.at(0), m_posu8);
   rlcInfo->maxRetransThresh = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_T_REORDERING_SRB1,
         timerReordering);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(timerReordering);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimerReorderingInfo,
         atoi(timerReordering.at(0).c_str()), m_posu8);
   rlcInfo->timerReordering = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TSTATUS_PROHIBIT_SRB1,
         timerStatusProhibit);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(timerStatusProhibit);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimerStatusProhibitInfo,
         atoi(timerStatusProhibit.at(0).c_str()), m_posu8);
   rlcInfo->timerStatusProhibit = m_posu8;

   return;
}

void SmApplication::HandleLteSrb1PolicyCfgGrpParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteRabPolicyCfgGrp lteRabPolicyCfgGrp;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   ReadLteSrb1PolicyCfgGrpParameters(dn, &lteRabPolicyCfgGrp);

   if(!isDynCfg)
   {
      lteRabPolicyCfgGrp.actType = MSM_ACT_ADD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB1].actType = MSM_ACT_ADD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB1].rlcInfo.actType = MSM_ACT_ADD;
      msmSetRabPolicyCfgGrpSrb1Parameters(&lteRabPolicyCfgGrp, cellIdx);
   }
   else
   {
      lteRabPolicyCfgGrp.actType = MSM_ACT_MOD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB1].actType = MSM_ACT_MOD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB1].rlcInfo.actType = MSM_ACT_MOD;

      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteRabPolicyCfgGrp, 
            MSM_LTE_RAB_SRB1_POLICY_CFG_GRP_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::ReadLteSrb2PolicyCfgGrpParameters
(
 MibDN                  dn,
 MsmLteRabPolicyCfgGrp  *lteRabPolicyCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> tpRetransmit, timerReordering, timerStatusProhibit;
   vector<u32> pollPdu, pollByte, maxRetransThresh;
   MsmLteSrbRlcInfo   *rlcInfo;
   rlcInfo = &lteRabPolicyCfgGrp->srbPolicy[MSM_SRB2].rlcInfo;

   lteRabPolicyCfgGrp->srbPolicy[MSM_SRB2].srbId = MSM_SRB_ID_2;

   rlcInfo->srbId = MSM_SRB_ID_1;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DEFAULT_CFG_SRB2, 
         rlcInfo->srbDefaultCfg);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TPOLL_RE_TRANSMIT_SRB2,
         tpRetransmit);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tpRetransmit);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtpRetransmitInfo,
         atoi(tpRetransmit.at(0).c_str()), m_posu8);

   rlcInfo->tpRetransmit = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_POLL_PDU_SRB2, pollPdu);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrpollPduInfo, pollPdu.at(0),
         m_posu8);
   rlcInfo->pollPdu = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_POLL_BYTE_SRB2, pollByte);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrpollByteInfo, pollByte.at(0),
         m_posu8);
   rlcInfo->pollByte = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_RE_TX_THRESHOLD_SRB2,
         maxRetransThresh);
   printf("PARAM_ID_LTE_MAX_RE_TX_THRESHOLD_SRB2:%d\n", maxRetransThresh.at(0));
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrmaxRetransThreshInfo, 
         maxRetransThresh.at(0), m_posu8);
   rlcInfo->maxRetransThresh = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_T_REORDERING_SRB2,
         timerReordering);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(timerReordering);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimerReorderingInfo,
         atoi(timerReordering.at(0).c_str()), m_posu8);
   rlcInfo->timerReordering = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TSTATUS_PROHIBIT_SRB2,
         timerStatusProhibit);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(timerStatusProhibit);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimerStatusProhibitInfo,
         atoi(timerStatusProhibit.at(0).c_str()), m_posu8);
   rlcInfo->timerStatusProhibit = m_posu8;

   return;
}

void SmApplication::HandleLteSrb2PolicyCfgGrpParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteRabPolicyCfgGrp lteRabPolicyCfgGrp;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   ReadLteSrb2PolicyCfgGrpParameters(dn, &lteRabPolicyCfgGrp);

   if(!isDynCfg)
   {
      lteRabPolicyCfgGrp.actType = MSM_ACT_ADD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB2].actType = MSM_ACT_ADD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB2].rlcInfo.actType = MSM_ACT_ADD;
      msmSetRabPolicyCfgGrpSrb2Parameters(&lteRabPolicyCfgGrp, cellIdx);
   }
   else
   {
      lteRabPolicyCfgGrp.actType = MSM_ACT_MOD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB2].actType = MSM_ACT_MOD;
      lteRabPolicyCfgGrp.srbPolicy[MSM_SRB2].rlcInfo.actType = MSM_ACT_MOD;

      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteRabPolicyCfgGrp, 
            MSM_LTE_RAB_SRB2_POLICY_CFG_GRP_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::HandleLtePdschCfgDedicatedParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLtePdschCfgDedicated ltePdschCfgDedicated;
   std::vector<s32>        pAvalue;
   size_t                  i;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      ltePdschCfgDedicated.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_PA, pAvalue);
      ltePdschCfgDedicated.pACnt=pAvalue.size();
      for( i=0;i<ltePdschCfgDedicated.pACnt;i++)
      {
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(
               SmApplication::GetInstance().GetSmTr196Validator()->arrPaInfo, pAvalue.at(i), m_posu8);
         ltePdschCfgDedicated.pA[i] = m_posu8;
      }
      msmSetPdschConfigDedicatedParameters(&ltePdschCfgDedicated, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::HandleLteAntennaCommonCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteAntenna_Common_Config   lteAntennaCommonConfig;
   u32                           numPorts;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      lteAntennaCommonConfig.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ANTENNA_PORTS_COUNT,numPorts);
      lteAntennaCommonConfig.numAntPorts = numPorts;	
      printf("PARAM_ID_LTE_ANTENNA_PORTS_COUNT:%d\n", lteAntennaCommonConfig.numAntPorts);
      msmSetAntennaCommonConfigParameters(&lteAntennaCommonConfig, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::ReadLteMacSchCfgParameters
(
 MibDN                  dn,
 MsmLteMAC_SCH_Config   *lteMACSCHConfig
 )
{
   TRACE_PRINTF("%s\n",__func__);

   u32  maxHARQ_Tx,periodicBSR_Timer,retxBSR_Timer;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_HARQ_TX, maxHARQ_Tx);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrmaxHARQ_TxInfo,
         maxHARQ_Tx, m_posu32);
   lteMACSCHConfig->maxHARQ_Tx = (unsigned long)m_posu32;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_PERIODIC_BSR_TIMER,
         periodicBSR_Timer);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrperiodicBSR_TimerInfo,
         periodicBSR_Timer, m_posu32);
   lteMACSCHConfig->periodicBSR_Timer = (unsigned long)m_posu32;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_RETX_BSR_TIMER, retxBSR_Timer);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrretxBSR_TimerInfo,
         retxBSR_Timer, m_posu32);
   lteMACSCHConfig->retxBSR_Timer = (unsigned long)m_posu32;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TTI_BUNDLING, 
         lteMACSCHConfig->ttiBundling);
   printf("PARAM_ID_LTE_TTI_BUNDLING:%d\n", lteMACSCHConfig->ttiBundling);
}

void SmApplication::HandleLteMacSchCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMAC_SCH_Config   lteMACSCHConfig;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);


   if(!isDynCfg)
   {
      lteMACSCHConfig.actType = MSM_ACT_ADD;
      ReadLteMacSchCfgParameters(dn, &lteMACSCHConfig);
      msmSetMacSchConfigParameters(&lteMACSCHConfig, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::HandleLteCellMibCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteCellMibCfgGrp   lteCellMibCfgGrp;
   std::vector<u32>      s_dlBandwidth;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DL_BANDWIDTH,s_dlBandwidth);
   printf("DLbandwidth:%d\n", s_dlBandwidth.at(0));
   lteCellMibCfgGrp.dlBwCnt=s_dlBandwidth.size();

   for(size_t i=0;i<lteCellMibCfgGrp.dlBwCnt;i++)
   {
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
            SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth,
            s_dlBandwidth[0], m_posu8);
      lteCellMibCfgGrp.dlBw[i] = (MsmLteBandwidth)m_posu8;
   }

   if(!isDynCfg)
   {
      lteCellMibCfgGrp.actType = MSM_ACT_ADD;
      msmSetCellMibConfigParameters(&lteCellMibCfgGrp, cellIdx);
   }
   else
   {
      lteCellMibCfgGrp.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteCellMibCfgGrp, 
            MSM_LTE_CELL_MIB_CONFIG_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::ReadLteSmCfgParameters
(
 MibDN             dn,
 MsmLteSmCellCfg   *lteSmCellCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   string s_duplexMode;
   u32 idx;
   std::vector<std::string> s_intgAlgo;    
   std::vector<std::string> s_ciphAlgo;

   if(GetMibCache().IsMibObjectPresent(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP)))
   { 
      GetMibCache().GetMibAttributeAsString(
            MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_DUPLEX_MODE,
            s_duplexMode);
      printf("duplex mode:%s\n",s_duplexMode.c_str());
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
            SmApplication::GetInstance().GetSmTr196Validator()->arrduplexModeInfo,
            s_duplexMode, m_posu8,2);
      lteSmCellCfg->duplexMode = m_posu8 + 1;
   }

   for (idx = 0; idx < MSM_MAX_AS_SEC_ALGOS; idx++)
   {          
      lteSmCellCfg->genUeCfg.intgAlgo[idx] = -1;
      lteSmCellCfg->genUeCfg.ciphAlgo[idx] = -1;
   }

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTEGRITY_ALGO_LIST, s_intgAlgo);

   m_posu8list.clear();

   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringArrayenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrintgAlgoInfo, 
         s_intgAlgo, m_posu8list, MSM_MAX_AS_SEC_ALGOS);
   for (idx = 0; idx < s_intgAlgo.size(); idx++)
   {
      lteSmCellCfg->genUeCfg.intgAlgo[idx] = m_posu8list[idx];
   }

   m_posu8list.clear();
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_CIPHERING_ALGO_LIST, s_ciphAlgo);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringArrayenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrciphAlgoInfo,
         s_ciphAlgo, m_posu8list, MSM_MAX_AS_SEC_ALGOS);

   for (idx = 0; idx < s_ciphAlgo.size(); idx++)
   {
      lteSmCellCfg->genUeCfg.ciphAlgo[idx] = m_posu8list[idx];
   }

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_RRM_RNTI_START,
         lteSmCellCfg->rrmRntiStart);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_RRM_RNTIS,
         lteSmCellCfg->maxRrmRntis);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_RRM_DED_PREMBL_STRT,
         lteSmCellCfg->rrmPrmblStart);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_RRM_NO_OF_DED_PREMBL,
         lteSmCellCfg->maxRrmPrmbls);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAC_RNTI_STRT,
         lteSmCellCfg->macRntiStart);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_MAC_RNTIS,
         lteSmCellCfg->maxMacRntis);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAC_NO_OF_PREMBL,
         lteSmCellCfg->numOfMacPrm);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_RRM_MAX_AVG_GBRPRB_USAGE,
         lteSmCellCfg->maxAvgGbrPrbUsage);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_RRM_QCI_1_TIMING_REQ,
         lteSmCellCfg->rrmQci1TmngReq);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_RRM_NUM_OF_PRB_RPTS,
         lteSmCellCfg->numOfPrbRpts);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_RRM_PRB_RPT_INTERVAL,
         lteSmCellCfg->prbRptIntvl);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DEFAULT_CFI_CFG,
         lteSmCellCfg->dfltCfiCfg);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_X2_PEERS,
         lteSmCellCfg->maxX2Peers);

   return;
}

void SmApplication::ReadAddCellCfgParameters
(
 MibDN             dn,
 MsmLteAddCellCfg  *lteAddCellCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   string s_duplexMode;
   std::vector<std::string> pcilist;
   std::vector<u32> EarfcnDLList;
   std::vector<u32> EarfcnULList;
   u32 EarfcnDLListSize = 0;
   u32 PCIListSize = 0;
   u32 EarfcnULListSize = 0;

   if(GetMibCache().IsMibObjectPresent(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP)))
   {
      GetMibCache().GetMibAttributeAsString(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),
            PARAM_ID_DUPLEX_MODE,s_duplexMode);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
            SmApplication::GetInstance().GetSmTr196Validator()->arrduplexModeInfo,
            s_duplexMode, m_posu8,2);
      lteAddCellCfg->duplexMode = m_posu8 + 1;
   }

   lteAddCellCfg->isSmallCellPciCfgd = MSM_TRUE;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SMALLCELL_START_PCI,
         lteAddCellCfg->startPci);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_SMALLCELL_PCI_RANGE,
         lteAddCellCfg->pciRange);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_CELL_SIZE_TYPE, 
         lteAddCellCfg->cellSizeType);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_EMERGENCY_SERVICE_PRIORITY_LEVEL,
         lteAddCellCfg->emergencyServicePriorityLevel);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MIN_DL_RES_NONCSGUSER,
         lteAddCellCfg->minDlResNonCsg);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MIN_UL_RES_NONCSGUSER,
         lteAddCellCfg->minUlResNonCsg);

   if( GetMibCache().IsMibAttributePresent(dn,PARAM_ID_LTE_EARFCNDL_LIST))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_EARFCNDL_LIST,EarfcnDLList);
      EarfcnDLListSize = EarfcnDLList.size();
      attrPresent |= EARFCN_CFGD;
      TRACE_PRINTF("%s: VALUE OF LTE_SON_EARFCNDL_LIST IS SET",__func__);
   }
   else
   {
      TRACE_PRINTF("%s: VALUE OF LTE_SON_EARFCNDL_LIST IS NOT SET",__func__);
   }


   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_EARFCNUL_LIST, EarfcnULList);

   if( GetMibCache().IsMibAttributePresent(dn,PARAM_ID_LTE_PHY_CELLID_LIST))
   {
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_PHY_CELLID_LIST, pcilist);
      SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(pcilist);
      PCIListSize = pcilist.size();
      attrPresent |= PCI_CFGD;
      TRACE_PRINTF("%s: VALUE OF LTE_PHY_CELLID_LIST IS SET",__func__);
   }
   else
   {
      TRACE_PRINTF("%s: VALUE OF LTE_PHY_CELLID_LIST IS NOT SET",__func__);
   }

   EarfcnULListSize = EarfcnULList.size();

   lteAddCellCfg->pciListCfg.numPci = PCIListSize;
   lteAddCellCfg->earfcnListCfg.numEarfcnUl = EarfcnULListSize;
   lteAddCellCfg->earfcnListCfg.numEarfcnDl = EarfcnDLListSize;

   for( size_t idx = 0; idx < PCIListSize; idx++ )
   {
      lteAddCellCfg->pciListCfg.pciLst[idx] = (u16)atoi(pcilist[idx].c_str());
   }

   for(size_t idx = 0; idx < EarfcnDLListSize; idx++)
   {
      lteAddCellCfg->earfcnListCfg.earfcnDlLst[idx] = EarfcnDLList[idx];
   }

   for( size_t idx = 0; idx < EarfcnULListSize; idx++ )
   {
      lteAddCellCfg->earfcnListCfg.earfcnUlLst[idx] = EarfcnULList[idx];
   }

   return;
}

void SmApplication::HandleLteAddCellCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteAddCellCfg lteAddCellCfg;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   ReadAddCellCfgParameters(dn, &lteAddCellCfg);

   if(!isDynCfg)
   {
      lteAddCellCfg.actType = MSM_ACT_ADD;
      msmSetAddCellConfigParameters(&lteAddCellCfg, cellIdx);
   }
   else
   {
      lteAddCellCfg.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteAddCellCfg, 
            MSM_LTE_ADD_CELL_CONFIG_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::HandleLteSmCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteSmCellCfg lteSmCellCfg;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   ReadLteSmCfgParameters(dn, &lteSmCellCfg);

   if(!isDynCfg)
   {
      lteSmCellCfg.actType = MSM_ACT_ADD;
      msmSetSmCellConfigParameters(&lteSmCellCfg, cellIdx);
   }
   else
   {
      lteSmCellCfg.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteSmCellCfg, 
            MSM_LTE_SM_CELL_CONFIG_PARAMETERS, cellIdx);
   }
   return;
}

void SmApplication::ReadLteDrxCfgParameters
(
 MibDN                dn,
 MsmLteDrxCfgParams   *lteDrxCfgParams
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> drxInactvTmr;
   std::vector<std::string> drxOnDurTmr;
   vector<u32> drxRetxTmr;
   u32 longDrxCycleGbr,longDrxCycleNonGbr;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DRX_ENABLE,
         lteDrxCfgParams->isDrxEnabled);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DRX_QCI_ENABLE,
         lteDrxCfgParams->isDRXQCIEnabled);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ON_DURATION_TIMER,
         drxOnDurTmr);
   //SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(drxOnDurTmr);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DRX_INACTIVITY_TIMER,
         drxInactvTmr);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(drxInactvTmr);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrdrxInactvTmrInfo,
         atoi(drxInactvTmr.at(0).c_str()), m_posu16);
   lteDrxCfgParams->drxInactvTmr = m_posu16;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_DRX_RETRANSMISSION_TIMER,
         drxRetxTmr);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrdrxRetxTmrInfo,
         drxRetxTmr.at(0), m_posu8);
   lteDrxCfgParams->drxRetxTmr = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_LONG_DRX_CYCLE_GBR,
         longDrxCycleGbr);
   printf("PARAM_ID_LTE_LONG_DRX_CYCLE_GBR:%d\n", longDrxCycleGbr);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrlongDrxCycleInfo,
         longDrxCycleGbr, m_posu16);
   lteDrxCfgParams->drxLongCycleOffst.longDrxCycleGbr = m_posu16;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_LONG_DRX_CYCLE_NON_GBR,
         longDrxCycleNonGbr);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrlongDrxCycleInfo,
         longDrxCycleNonGbr, m_posu16);
   lteDrxCfgParams->drxLongCycleOffst.longDrxCycleNonGbr = m_posu16;

   return;
}

void SmApplication::HandleLteDrxCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteDrxCfgParams lteDrxCfgParams;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      lteDrxCfgParams.actType = MSM_ACT_ADD;
      ReadLteDrxCfgParameters(dn, &lteDrxCfgParams);
      msmSetDrxConfigParameters(&lteDrxCfgParams, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

#ifdef TIP_OAM
void SmApplication::GetReportAmount
(
 MibDN                  dn,
 string                 &s_reportAmount
)
{
   TRACE_PRINTF("%s\n",__func__);
   U8 rptAmt;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_AMOUNT, rptAmt);
   switch(rptAmt)
   {
      case 0: s_reportAmount = "infinity";
              break;
      case 1: s_reportAmount = "r1";
              break;
      case 2: s_reportAmount = "r2";
              break;
      case 4: s_reportAmount = "r4";
              break;
      case 8: s_reportAmount = "r8";
              break;
      case 16: s_reportAmount = "r16";
              break;
      case 32: s_reportAmount = "r32"; 
              break;
      case 64: s_reportAmount = "r64"; 
              break;
      default: s_reportAmount = "r8"; 
   }
}
#endif

void SmApplication::ReadA1Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasEvntRptCfg    *a1EvntRptCfg;
   std::vector<std::string> hyst;
   u16                      idx;
   vector<u32>              timeToTrigger;
   u32                      rsrp, rsrq, reportInterval, reportInt;
   string                   s_triggerQty,s_reportQty,s_reportAmount;
   u8                       triggerQty, reportQty,maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A1_THRESHOLD_RSRP, rsrp);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A1_THRESHOLD_RSRQ, rsrq);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER, timeToTrigger);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TRIGGER_QUANTITY, s_triggerQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtriggerQtyInfo, 
         s_triggerQty, triggerQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_QUANTITY, s_reportQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportQtyInfo,
         s_reportQty, reportQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

#ifdef TIP_OAM
   GetReportAmount(dn, s_reportAmount);
#else
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A1_REPORT_AMOUNT,
         s_reportAmount);
#endif
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_EVENT_A1_CFG; idx++)
   {
      a1EvntRptCfg = &lteCellMeasCfgGrp->measA1EvtRptCfg[idx];

      a1EvntRptCfg->actType = MSM_ACT_ADD;
      a1EvntRptCfg->threshold_RSRP = (unsigned long)rsrp;
      a1EvntRptCfg->threshold_RSRQ = (unsigned long)rsrq;
      a1EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      a1EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
      a1EvntRptCfg->triggerQty = triggerQty;
      a1EvntRptCfg->reportQty = reportQty;
      a1EvntRptCfg->maxRptCells = maxRptCells;
      a1EvntRptCfg->reportInterval = (unsigned long)reportInt;
      a1EvntRptCfg->reportAmount = m_posu8;
   }

   return;
}

void SmApplication::ReadA2Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasEvntRptCfg   *a2EvntRptCfg;
   std::vector<std::string> hyst;
   u16                      idx;
   vector<u32>              timeToTrigger;
   u32                      rsrp, rsrq, reportInterval, reportInt;
   string                   s_triggerQty,s_reportQty,s_reportAmount;
   u8                       triggerQty, reportQty,maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A2_THRESHOLD_RSRP, rsrp);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A2_THRESHOLD_RSRQ, rsrq);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER, timeToTrigger);

   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TRIGGER_QUANTITY, s_triggerQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtriggerQtyInfo, 
         s_triggerQty, triggerQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_QUANTITY, s_reportQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportQtyInfo,
         s_reportQty, reportQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

#ifdef TIP_OAM
   GetReportAmount(dn, s_reportAmount);
#else
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A2_REPORT_AMOUNT,
         s_reportAmount);
#endif
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_EVENT_A2_CFG; idx++)
   {
      a2EvntRptCfg = &lteCellMeasCfgGrp->measA2EvtRptCfg[idx];

      a2EvntRptCfg->actType = MSM_ACT_ADD;
      a2EvntRptCfg->threshold_RSRP = (unsigned long)rsrp;
      a2EvntRptCfg->threshold_RSRQ = (unsigned long)rsrq;
      a2EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      a2EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
      a2EvntRptCfg->triggerQty = triggerQty;
      a2EvntRptCfg->reportQty = reportQty;
      a2EvntRptCfg->maxRptCells = maxRptCells;
      a2EvntRptCfg->reportInterval = (unsigned long)reportInt;
      a2EvntRptCfg->reportAmount = m_posu8;
   }

   return;
}

void SmApplication::ReadA3Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasEvntA3RptCfg   *a3EvntRptCfg;
   std::vector<std::string> hyst;
#ifdef TIP_OAM
   std::vector<std::string> a3Offset;
#endif
   u16                      idx;
   vector<u32>              timeToTrigger;
   u32                      reportInterval, reportInt;
   string                   s_triggerQty,s_reportQty,s_reportAmount;
   u8                       triggerQty, reportQty,maxRptCells;
   s32                      offset;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTRA_HO_A3_OFFSET, offset);
   lteCellMeasCfgGrp->measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].offset = offset;
   lteCellMeasCfgGrp->measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].offset = offset;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTRA_ANR_A3_OFFSET, 
         lteCellMeasCfgGrp->measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].offset);
#ifdef TIP_OAM
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A3_OFFSET, a3Offset);
   printf("a3offset:%s\n", a3Offset.at(0).c_str());
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(a3Offset);
   lteCellMeasCfgGrp->measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].offset = \
      atoi(a3Offset.at(0).c_str());
   lteCellMeasCfgGrp->measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].offset = \
      atoi(a3Offset.at(0).c_str());
#endif

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER, timeToTrigger);

   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TRIGGER_QUANTITY, s_triggerQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtriggerQtyInfo, 
         s_triggerQty, triggerQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_QUANTITY, s_reportQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportQtyInfo,
         s_reportQty, reportQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

#ifdef TIP_OAM
   GetReportAmount(dn, s_reportAmount);
#else
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A3_REPORT_AMOUNT,
         s_reportAmount);
#endif
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_EVENT_A3_CFG; idx++)
   {
      a3EvntRptCfg = &lteCellMeasCfgGrp->measEvtA3Cfg[idx];

      a3EvntRptCfg->triggerQty = triggerQty;
      a3EvntRptCfg->reportQty = reportQty;
      a3EvntRptCfg->maxRptCells = maxRptCells;
      a3EvntRptCfg->reportInterval = (unsigned long)reportInt;
      a3EvntRptCfg->reportAmount = m_posu8;
      a3EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      a3EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
   }
   return;
}
#ifdef LTE_ADV
void SmApplication::ReadA4Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);
   MsmLteMeasEvntRptCfg *a4EvntRptCfg; 
   std::vector<std::string> hyst;
   u16                      idx;
   vector<u32>              timeToTrigger;
   u32                      rsrp, rsrq, reportInterval, reportInt;
   string                   s_triggerQty,s_reportQty,s_reportAmount;
   u8                       triggerQty, reportQty,maxRptCells;
   u32                      valueu32;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_MEAS_SCELL_ADD_REL, valueu32);
   lteCellMeasCfgGrp->isMeasReqForSCellAdd = (unsigned long)valueu32;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A4_THRESHOLD_RSRP, rsrp);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A1_THRESHOLD_RSRQ, rsrq);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER, timeToTrigger);

   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TRIGGER_QUANTITY, s_triggerQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtriggerQtyInfo, 
         s_triggerQty, triggerQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_QUANTITY, s_reportQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportQtyInfo,
         s_reportQty, reportQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

#ifdef TIP_OAM
   GetReportAmount(dn, s_reportAmount);
#else
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A3_REPORT_AMOUNT,
         s_reportAmount);
#endif
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_EVENT_A4_CFG; idx++)
   {
      a4EvntRptCfg = &lteCellMeasCfgGrp->measA4EvtRptCfg[idx];

      a4EvntRptCfg->actType = MSM_ACT_ADD;
      a4EvntRptCfg->threshold_RSRP = (unsigned long)rsrp;
      a4EvntRptCfg->threshold_RSRQ = (unsigned long)rsrq;
      a4EvntRptCfg->triggerQty = triggerQty;
      a4EvntRptCfg->reportQty = reportQty;
      a4EvntRptCfg->maxRptCells = maxRptCells;
      a4EvntRptCfg->reportInterval = (unsigned long)reportInt;
      a4EvntRptCfg->reportAmount = m_posu8;
      a4EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      a4EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
   }
   return;
}

#endif

void SmApplication::ReadA5Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasEvntA5RptCfg   *a5EvntRptCfg;
   std::vector<std::string> hyst;
   u16                      idx;
   vector<u32>              timeToTrigger;
   u32                      rsrp, reportInterval, reportInt;
   string                   s_triggerQty,s_reportQty,s_reportAmount;
   u8                       triggerQty, reportQty,maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTRA_A5_THRESHOLD_1_RSRP, 
         rsrp);
   lteCellMeasCfgGrp->measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].threshold1_RSRP = 
      (unsigned long)rsrp;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTRA_A5_THRESHOLD_2_RSRP,
         rsrp);
   lteCellMeasCfgGrp->measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].threshold2_RSRP = 
      (unsigned long)rsrp;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTER_A5_THRESHOLD_1_RSRP,
         rsrp);
   lteCellMeasCfgGrp->measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].threshold1_RSRP = 
      (unsigned long)rsrp;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTER_A5_THRESHOLD_2_RSRP,
         rsrp);
   lteCellMeasCfgGrp->measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].threshold2_RSRP = 
      (unsigned long)rsrp;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_1_RSRP,
         rsrp);
   lteCellMeasCfgGrp->measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].threshold1_RSRP = 
      (unsigned long)rsrp;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_2_RSRP,
         rsrp);
   lteCellMeasCfgGrp->measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].threshold2_RSRP = 
      (unsigned long)rsrp;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER, timeToTrigger);

   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TRIGGER_QUANTITY, s_triggerQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtriggerQtyInfo, 
         s_triggerQty, triggerQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_QUANTITY, s_reportQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportQtyInfo,
         s_reportQty, reportQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

#ifdef TIP_OAM
   GetReportAmount(dn, s_reportAmount);
#else
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A5_REPORT_AMOUNT,
         s_reportAmount);
#endif
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_EVENT_A5_CFG; idx++)
   {
      a5EvntRptCfg = &lteCellMeasCfgGrp->measEvtA5Cfg[idx];

      a5EvntRptCfg->actType = MSM_ACT_ADD;
      a5EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      a5EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
      a5EvntRptCfg->triggerQty = triggerQty;
      a5EvntRptCfg->reportQty = reportQty;
      a5EvntRptCfg->maxRptCells = maxRptCells;
      a5EvntRptCfg->reportInterval = (unsigned long)reportInt;
      a5EvntRptCfg->reportAmount = m_posu8;
   }
   return;
}

void SmApplication::ReadUtraB2Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasUtraEvntB2RptCfg  *b2EvntRptCfg;
   std::vector<std::string>    hyst;
   u16                         idx;
   vector<u32>                 timeToTrigger;
   u32                         reportInterval, reportInt;
   string                      s_triggerQty,s_reportQty,s_reportAmount;
   u8                          maxRptCells;
   u8                          b2Threshold1RSRP, b2Threshold1RSRQ;
   s8                          b2Threshold2UtraRSCP;
   u8                          b2Threshold2UtraEcNo;
   s32                         b2Threshold2UtraTddRSRP;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD1_UTRA_RSRP_HO,
         b2Threshold1RSRP);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD1_UTRA_RSRQ_HO,
         b2Threshold1RSRQ);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD2_UTRA_RSCP,
         b2Threshold2UtraRSCP);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD2_UTRA_ECNO,
         b2Threshold2UtraEcNo);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS_IRAT, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER_IRAT, 
         timeToTrigger);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS_IRAT, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL_IRAT, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_AMOUNT_IRAT,
         s_reportAmount);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TDS_CDMA_B2_THRSH2_UTRATDD_RSCP,
         b2Threshold2UtraTddRSRP);

   for(idx=0; idx<MSM_MEAS_MAX_UTRA_PERD_CFG; idx++)
   {
      b2EvntRptCfg = &lteCellMeasCfgGrp->measUtraEventB2RptCfg[idx];

      b2EvntRptCfg->actType = MSM_ACT_ADD;
      b2EvntRptCfg->b2Threshold1RSRP = b2Threshold1RSRP;
      b2EvntRptCfg->b2Threshold1RSRQ = b2Threshold1RSRQ;
      b2EvntRptCfg->b2Threshold2UtraRSCP = b2Threshold2UtraRSCP;
      b2EvntRptCfg->b2Threshold2UtraEcNo = b2Threshold2UtraEcNo;
      b2EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      b2EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
      b2EvntRptCfg->maxReportCell = maxRptCells;
      b2EvntRptCfg->reportInterval = (unsigned long)reportInt;
      b2EvntRptCfg->reportAmount = m_posu8;
      b2EvntRptCfg->b2Threshold2UtraTddRSRP = b2Threshold2UtraTddRSRP;
   }
   return;
}

void SmApplication::ReadGeranB2Event
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasGeranEvntB2RptCfg  *b2EvntRptCfg;
   std::vector<std::string>    hyst;
   u16                         idx;
   vector<u32>                 timeToTrigger;
   u32                         reportInterval, reportInt;
   string                      s_triggerQty,s_reportQty,s_reportAmount;
   u8                          maxRptCells;
   s32                         b2Threshold2UtraTddRSRP;


   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRP_REDIR,
         lteCellMeasCfgGrp->measGeranEventB2RptCfg[0].b2Threshold1RSRP);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRP_HO,
         lteCellMeasCfgGrp->measGeranEventB2RptCfg[1].b2Threshold1RSRP);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRQ_REDIR,
         lteCellMeasCfgGrp->measGeranEventB2RptCfg[0].b2Threshold1RSRQ);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD1_GERAN_RSRQ_HO,
         lteCellMeasCfgGrp->measGeranEventB2RptCfg[1].b2Threshold1RSRQ);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD2_GERAN,
         lteCellMeasCfgGrp->measGeranEventB2RptCfg[0].b2Threshold2Geran);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_B2_THRESHOLD2_GERAN_RSSI_HO,
         lteCellMeasCfgGrp->measGeranEventB2RptCfg[1].b2Threshold2Geran);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HYSTERESIS_IRAT, hyst);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(hyst);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER_IRAT, 
         timeToTrigger);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtimeToTriggerInfo,
         timeToTrigger.at(0), m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS_IRAT, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL_IRAT, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_AMOUNT_IRAT,
         s_reportAmount);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TDS_CDMA_B2_THRSH2_UTRATDD_RSCP,
         b2Threshold2UtraTddRSRP);
   for(idx=0; idx<MSM_MEAS_MAX_GERAN_EVNT_B2_CFG; idx++)
   {
      b2EvntRptCfg = &lteCellMeasCfgGrp->measGeranEventB2RptCfg[idx];

      b2EvntRptCfg->actType = MSM_ACT_ADD;
      b2EvntRptCfg->hysteresis = atoi(hyst.at(0).c_str());
      b2EvntRptCfg->timeToTrigger = (unsigned long)m_posu32;
      b2EvntRptCfg->maxReportCell = maxRptCells;
      b2EvntRptCfg->reportInterval = (unsigned long)reportInt;
      b2EvntRptCfg->reportAmount = m_posu8;
   }
   return;
}

void SmApplication::HandleLteFreqSyncParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s",__func__);

   MsmLteFreqSyncParams lteFreqSyncParameters;
   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_FREQ_SYNC_PCI, 
         lteFreqSyncParameters.freqSyncPci);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_FREQ_SYNC_EARFCN,
         lteFreqSyncParameters.freqSyncEarfcn);
   if (!isDynCfg)
   {
      msmSetFreqSyncParameters(&lteFreqSyncParameters,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
}

void SmApplication::ReadCDMAMeasCfgParam
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s",__func__);

   MsmMeasCDMAPeridRptCfg     *cdmaMeasCfg;
   std::vector<std::string>    hyst;
   u16                         idx;
   u32                         reportInterval, reportInt;
   string                      s_triggerQty,s_reportQty,s_reportAmount;
   u8                          maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS_CDMA, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL_CDMA, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_AMOUNT_CDMA,
         s_reportAmount);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_CDMA_PERD_CFG; idx++)
   {
      cdmaMeasCfg = &lteCellMeasCfgGrp->measCDMA1xPeridRptCfg[idx];

      cdmaMeasCfg->maxReportCell = maxRptCells;
      cdmaMeasCfg->reportInterval = (unsigned long)reportInt;
      cdmaMeasCfg->reportAmount = m_posu8;
   }
   return;
}

void SmApplication::ReadEutraMeasCfgParam
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmMeasEutraPeridRptCfg    *eutraMeasCfg;
   std::vector<std::string>    hyst;
   u16                         idx;
   u32                         reportInterval, reportInt;
   string                      s_triggerQty,s_reportQty,s_reportAmount;
   u8                          triggerQty, reportQty,maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TRIGGER_QUANTITY, s_triggerQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtriggerQtyInfo, 
         s_triggerQty, triggerQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_QUANTITY, s_reportQty);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportQtyInfo,
         s_reportQty, reportQty, 2);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL, 
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, reportInt);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_PRD_REPORT_AMOUNT,
         s_reportAmount);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo, 
         s_reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_EUTRA_PERD_CFG; idx++)
   {
      eutraMeasCfg = &lteCellMeasCfgGrp->measEutraPeridRptCfg[idx];
      eutraMeasCfg->triggerQty = triggerQty;
      eutraMeasCfg->reportQty = reportQty;
      eutraMeasCfg->maxRptCells = maxRptCells;
      eutraMeasCfg->reportInterval = reportInt;
      eutraMeasCfg->reportAmount = m_posu8;
   }
   return;
}

void SmApplication::ReadUTRAMeasCfgParam
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmMeasUtraPeriodRptCfg    *utraMeasCfg;
   u16                         idx;
   u32                         reportInterval;
   string                      reportAmount;
   u8                          maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS_IRAT, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL_IRAT,
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_AMOUNT_IRAT,
         reportAmount);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo,
         reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_UTRA_PERD_CFG; idx++)
   {
      utraMeasCfg = &lteCellMeasCfgGrp->measUtraPeriodRptCfg[idx];
      utraMeasCfg->maxReportCell = maxRptCells;
      utraMeasCfg->reportInterval = m_posu32;
      utraMeasCfg->reportAmount = m_posu8;
   }
   return;
}

void SmApplication::ReadSpeedMeasCfgParam
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmMeasSpdStateScaleFact  *measSpeedCfg;
   u32 sMeasure,timeToTriggerSf;

   measSpeedCfg = &lteCellMeasCfgGrp->measSpeedCfg;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER_SF_HIGH,
         timeToTriggerSf);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
         timeToTriggerSf, m_posu8);
   measSpeedCfg->timeToTriggerSfHigh = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TIME_TO_TRIGGER_SF_MEDIUM,
         timeToTriggerSf);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
         timeToTriggerSf, m_posu8);
   measSpeedCfg->timeToTriggerSfMedium = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_S_MEASURE, sMeasure);
   measSpeedCfg->sMeasure = sMeasure;

   return;
}

void SmApplication::ReadMeasGERANPeridRptCfg
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasGERANPeridRptCfg  *measGERANPeridRptCfg;
   u16                         idx;
   u32                         reportInterval;
   string                      reportAmount;
   u8                          maxRptCells;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_REPORT_CELLS_IRAT, 
         maxRptCells);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_INTERVAL_IRAT,
         reportInterval);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportIntervalInfo,
         reportInterval, m_posu32);

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_REPORT_AMOUNT_IRAT,
         reportAmount);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrreportAmountInfo,
         reportAmount, m_posu8, 8);

   for(idx=0; idx<MSM_MEAS_MAX_GERAN_PERD_CFG; idx++)
   {
      measGERANPeridRptCfg = &lteCellMeasCfgGrp->measGERANPeridRptCfg[idx];

      measGERANPeridRptCfg->maxRptCells = maxRptCells;
      measGERANPeridRptCfg->reportInterval = m_posu32;
      measGERANPeridRptCfg->reportAmount = m_posu8;
   }
   return;
}

void SmApplication::ReadMeasQtyCfgParam
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasQtyCfgParams  *qtyCfg;
   std::vector<std::string> rsrpFltrCoeff, rsrqFltrCoeff, ecnoFltrCoeff, fltrCoeffGeran;
   u32 filterCoefficient2FDDr10;
   string s_measQtyUtraFdd;
   string s_measQtyCdma2k;
   string s_measQtyUtraTdd;


   qtyCfg = &lteCellMeasCfgGrp->qtyCfg;

   qtyCfg->actType = MSM_ACT_ADD;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_FILTER_COEFFICIENT_RSRP,
         rsrpFltrCoeff);
   printf("rsrpFltrCoeff:%s\n",rsrpFltrCoeff.at(0).c_str());
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(rsrpFltrCoeff);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrrsrpFltrCoeffInfo,
         atoi(rsrpFltrCoeff.at(0).c_str()), m_posu8);
   qtyCfg->rsrpFltrCoeff = m_posu8;


   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_FILTER_COEFFICIENT, 
         filterCoefficient2FDDr10);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrrsrpFltrCoeffInfo,
         filterCoefficient2FDDr10, m_posu8);
   qtyCfg->filterCoefficient2FDDr10 = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_FILTER_COEFFICIENT_RSRQ,
         rsrqFltrCoeff);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(rsrqFltrCoeff);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrrsrqFltrCoeffInfo,
         atoi(rsrqFltrCoeff.at(0).c_str()), m_posu8);
   qtyCfg->rsrqFltrCoeff = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_FILTER_COEFFICIENT_UTRA,
         ecnoFltrCoeff);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(ecnoFltrCoeff);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrrsrqFltrCoeffInfo,
         atoi(ecnoFltrCoeff.at(0).c_str()), m_posu8);
   qtyCfg->ecnoFltrCoeff = m_posu8;


   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_GERAN_FILTER_COEFF, 
         fltrCoeffGeran);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(fltrCoeffGeran);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrrsrqFltrCoeffInfo,
         atoi(fltrCoeffGeran.at(0).c_str()), m_posu8);
   qtyCfg->fltrCoeffGERAN = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MEAS_QUANTITY_UTRA_FDD,
         s_measQtyUtraFdd);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrmeasQtyUtraFddInfo,
         s_measQtyUtraFdd, m_posu8, 2);
   qtyCfg->measQtyUtraFdd = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MEAS_QUANTITY_CDMA2000,
         s_measQtyCdma2k);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrmeasQtyCdma2k,
         s_measQtyCdma2k, m_posu8, 2);
   qtyCfg->measQtyCDMA2k = m_posu8;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TDS_CDMA_MEAS_QTY_UTRATDD,
         s_measQtyUtraTdd);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrMeasQtyUtraTdd, s_measQtyUtraTdd, m_posu8, 2);
   qtyCfg->measQtyUtraTdd = m_posu8;


   return;
}

void SmApplication::ReadMeasGapParam
(
 MibDN                  dn,
 MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteMeasGapConfig  *measGap;

   measGap = &lteCellMeasCfgGrp->measGap;

   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTER_FREQ_MEAS_GAP,
         measGap->gapPatternForInterFA);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ANR_MEAS_GAP_CONFIG,
         measGap->gapPatternForANR);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_INTER_RAT_MEAS_GAP,
         measGap->gapPatternForInterRAT);

   return;
}

void SmApplication::HandleLteCellMeasCfgGrpParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteCellMeasCfgGrp lteCellMeasCfgGrp;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      lteCellMeasCfgGrp.actType = MSM_ACT_ADD;

      ReadA1Event(dn, &lteCellMeasCfgGrp);
      ReadA2Event(dn, &lteCellMeasCfgGrp);
      ReadA3Event(dn, &lteCellMeasCfgGrp);
#ifdef LTE_ADV
      ReadA4Event(dn, &lteCellMeasCfgGrp);
#endif
      ReadA5Event(dn, &lteCellMeasCfgGrp);
      ReadUtraB2Event(dn, &lteCellMeasCfgGrp);
      ReadGeranB2Event(dn, &lteCellMeasCfgGrp);
      ReadCDMAMeasCfgParam(dn, &lteCellMeasCfgGrp);
      ReadEutraMeasCfgParam(dn, &lteCellMeasCfgGrp);
      ReadUTRAMeasCfgParam(dn, &lteCellMeasCfgGrp);
      ReadSpeedMeasCfgParam(dn, &lteCellMeasCfgGrp);
      ReadMeasGERANPeridRptCfg(dn, &lteCellMeasCfgGrp);
      ReadMeasQtyCfgParam(dn, &lteCellMeasCfgGrp);
      ReadMeasGapParam(dn, &lteCellMeasCfgGrp);

      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_A3_SUPPORT_ENABLE, 
            lteCellMeasCfgGrp.isA3SupportReq);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_HO_REPORT_CFG_VAL,
            lteCellMeasCfgGrp.hoRptCfg);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ANR_REPORT_CFG_VAL,
            lteCellMeasCfgGrp.anrRptCfg);

      msmSetCellMeasConfigParameters(&lteCellMeasCfgGrp, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, \
            parameter updation will occur after reboot.");
   }
   return;
}

void SmApplication::HandleCellPlmnListParameters
(
 u16 cellIdx,
 bool isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      u32 index, idx;
      string plmnidvalue,mccvalue,mncvalue;
      u32 plmnidlength = 0;
      vector<u32> cellPlmnSrc;
      u32 cellEnable = 0;
      std::vector<std::string> plmnRatPriorList;
      MsmLteCellSib1CfgGrp lteCellSib1CfgGrp;

      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_PLMN_ENTRIES,lteCellSib1CfgGrp.cellAccessInfo.maxNumOfPlmns);
      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_NUM_OF_PLMN_ENTRIES,lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns);
      printf("PARAM_ID_LTE_NUM_OF_PLMN_E:%d\n", lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns);
      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CELL_PLMN_SRC, cellPlmnSrc);
      MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
      u32 numplmn = 0;

      for(index=0; index< lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns && lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns<=MSM_MAX_PLMN; index++)
      {
         MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,MIB_OBJECT_CLASS_LTE_CELL_PLMN_LIST, index);

         if(m_mib.IsMibObjectPresent(dnobj))
         {
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_EPC_PLMN_ENABLE, cellEnable);
            if((MIB_OBJ_CONFIGURED == cellPlmnSrc.at(index)) && (TRUE == cellEnable))
            {
               numplmn++;
               GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_OAM_PRIMARY_PLMN, lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].isPrimary);
               GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_OAM_CELL_RESERVE_FOR_OPERATOR, lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].rsrvdFrOperUse);

               if(GetMibCache().IsMibAttributePresent(dnobj,PARAM_ID_LTE_OAM_PLMNID ))
               {
                  GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_OAM_PLMNID, plmnidvalue);
                  printf("plmn:%s\n",plmnidvalue.c_str());
                  plmnidlength = plmnidvalue.length(); 
                  attrPresent |= PLMN_ID_CFGD;
                  TRACE_PRINTF("%s: VALUE OF LTE_OAM_PLMNID IS SET",__func__);
               }
               else
               {
                  TRACE_PRINTF("%s: VALUE OF LTE_OAM_PLMNID IS NOT SET",__func__);
               }

               for(idx = 0; idx < plmnidlength; idx++)
               {
                  if(idx < MSM_MAX_MCC_DIGITS)
                  {
                     mccvalue = plmnidvalue.substr(idx,1);
                     lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].plmnId.mcc[idx] = u8(atoi(mccvalue.c_str()));
                  }
                  else
                  {
                     mncvalue = plmnidvalue.substr(idx,1);
                     lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].plmnId.mnc[idx-3] = u8(atoi(mncvalue.c_str()));
                  }
               }
               lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].plmnId.numMncDigits = (plmnidlength - 3);
               if(  lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].plmnId.numMncDigits == 2)	 	 
               {	 	 
                  lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[index].plmnId.mnc[2]=u8(0);	 	 
               }

            }
         }
      }
      /* updating the correct number of PLMN instead of using the
       * LTE_NUM_OF_PLMN_ENTRIES- We may insert the tr069 object but the
       * LTE_EPC_PLMN_ENABLE is not enable by user,so pass the correct numplmn */
      lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns = numplmn;
      if(msmSetCellSib1ConfigGroupParameters(&lteCellSib1CfgGrp, true,cellIdx)!=ROK)
      {
         TRACE_PRINTF("%s:%d Failed to set SIB1 configuration",__func__,__LINE__);
      }
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }
}

void SmApplication::HandleLteNeighFreqMIOParams(u16 subscribs, u8 instance,bool isDynCfg,u16 cellIdx)
{
   TRACE_PRINTF("%s\n",__func__);

   u8 idx, maxInterFreqCarrs;
   std::vector<u32> interFreqCarrSrcLst;
   MsmLteNeighFreqCfg  lteNeighFreqCfg;
   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   memset(&lteNeighFreqCfg,0,sizeof(MsmLteNeighFreqCfg));

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_CARRIER_ENTRIES_IDLE, maxInterFreqCarrs);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_X_RADISYS_NEIGH_FREQ_SRC, interFreqCarrSrcLst);

   if(isDynCfg)
   {
      if (subscribs == SI_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS)
      {
         lteNeighFreqCfg.actType = MSM_ACT_MOD;
         lteNeighFreqCfg.numEutraFreq = 1;
         //lteNeighFreqCfg.t.dynNeighFreq.eutranFreq.freqIndex = 255;
         if(FillServCarrFreqInfo(fapLteDn,&lteNeighFreqCfg.t.dynNeighFreq.eutranFreq))
         {
            m_smmWaitForDynCfgRsp = TRUE;
            MsmSmmDynCfgReq((void*)&lteNeighFreqCfg, MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS, cellIdx);
         }
         else
         {
            TRACE_PRINTF("%s: Value Of LTE_EARFCNDL_LIST Is Not Set",__func__);
         }
         return;
      } /* SI_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS */
      else if((subscribs == SI_EUTRA_NBR_FREQ_PARAMS) ||
            (subscribs == SI_EUTRA_NBR_FREQ_OBJ))
      {
         MibDN neighFreqDn = MibDN::GenerateMibDN(fapLteDn,MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER,instance);
         if (neighFreqRollBack == TRUE)
         {
            /* Notification received due to rollback, ignore and return */
            neighFreqRollBack = FALSE;
            return;
         }
         if ((m_mib.IsMibObjectPresent(neighFreqDn)) && 
               (interFreqCarrSrcLst[instance] == MIB_OBJ_CONFIGURED))
         {
            if (FillNeighFreqCarrByInstance(fapLteDn,instance,&lteNeighFreqCfg.t.dynNeighFreq.eutranFreq)
                  == ROK)
            {
               /* Check the freqIndxMap if an entry exists already for this instance for TR-196 object */
               for (idx=0; idx<maxInterFreqCarrs; idx++)
               {
                  if ((freqIndxMap[idx].inUse == TRUE) && 
                        (freqIndxMap[idx].instanceNumb == instance))
                  {
                     lteNeighFreqCfg.actType = MSM_ACT_MOD;
                     break;
                  }
               }
               /* Instance not existing for this TR-196 object */
               if (idx == maxInterFreqCarrs)
               {
                  lteNeighFreqCfg.actType = MSM_DYN_ADD;
                  /* Get the next free entry */
                  for (idx=0; idx<maxInterFreqCarrs; idx++)
                  {
                     if (freqIndxMap[idx].inUse == FALSE)
                     {
                        freqIndxMap[idx].inUse = TRUE;
                        freqIndxMap[idx].instanceNumb = instance;
                        break;
                     } 
                  }
               }
               lteNeighFreqCfg.numEutraFreq = 1;
               lteNeighFreqCfg.t.dynNeighFreq.eutranFreq.freqIndex = instance;
               TRACE_PRINTF("\n####################################################################\n");
               TRACE_PRINTF(" Neighbour frequency at instance %d\n",instance);
               TRACE_PRINTF("####################################################################\n");
               printFreqValuesFilled(&lteNeighFreqCfg.t.dynNeighFreq.eutranFreq);
               m_smmWaitForDynCfgRsp = TRUE;
               MsmSmmDynCfgReq((void*)&lteNeighFreqCfg, MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS, cellIdx);
            }
         }
         else if (interFreqCarrSrcLst[instance] == MIB_OBJ_DELETED)
         {
            lteNeighFreqCfg.actType = MSM_ACT_DEL;
            lteNeighFreqCfg.numEutraFreq = 1;
            lteNeighFreqCfg.t.delNeighFreq.eutranFreq.freqIndex = instance;
            TRACE_PRINTF("\n####################################################################\n");
            TRACE_PRINTF(" Neighbour frequency deleted at instance %d\n",instance);
            TRACE_PRINTF("####################################################################\n");
            m_smmWaitForDynCfgRsp = TRUE;
            MsmSmmDynCfgReq((void*)&lteNeighFreqCfg, MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS, cellIdx);
         }
         else
         {
            TRACE_PRINTF("MIB object added but not configured\n");
         }
      }/* SI_EUTRA_NBR_FREQ_PARAMS */
   }
   /* Static configuration */
   else
   {  
      MsmLteNeighEutraFreq   *freqInfo;
      u32 fillIdx = 1; 
      lteNeighFreqCfg.actType = MSM_ACT_ADD;
      /* serving cell at index 0 */
      lteNeighFreqCfg.numEutraFreq = 1;

      /* Filling serving cell params */
      freqInfo = &lteNeighFreqCfg.t.addNeighFreq[0].eutranFreq;
      freqInfo->freqIndex = 255; /* SERV_FREQ_IDX */
      if(MSM_FALSE == FillServCarrFreqInfo(fapLteDn,freqInfo))
      {
         TRACE_PRINTF("%s: LTE_EARFCNDL_LIST Is Not Configured ",__func__);
      }

      /* Fill neighbour cell params */
      for (idx=0; idx<maxInterFreqCarrs; idx++)
      {
         freqInfo = &lteNeighFreqCfg.t.addNeighFreq[fillIdx].eutranFreq;
         if (FillNeighFreqCarrByInstance(fapLteDn,idx,freqInfo) == ROK)
         {
            fillIdx++;
            freqIndxMap[idx].inUse = TRUE;
            freqIndxMap[idx].instanceNumb = idx;
            freqInfo->freqIndex = idx;
            lteNeighFreqCfg.numEutraFreq++;
            TRACE_PRINTF("\n##################################################\n");
            TRACE_PRINTF(" Static : Neighbour frequency at index %d\n",idx);
            TRACE_PRINTF("\n##################################################\n");
            printFreqValuesFilled(freqInfo);
         }
      }
      TRACE_PRINTF("Action type is : %d\n",lteNeighFreqCfg.actType);
      TRACE_PRINTF("Number of frequencies filled are : %d\n",lteNeighFreqCfg.numEutraFreq);
      msmSetNeighFreqEutraCfgParameters(&lteNeighFreqCfg,cellIdx);
   }
   return;
}

bool SmApplication::FillServCarrFreqInfo(MibDN fapLteDn ,MsmLteNeighEutraFreq *freqInfo)
{
   TRACE_PRINTF("%s\n",__FUNCTION__);

   std::vector<std::string> qRxLevMin, sIntraSearch, tReselection, sNonIntraSearch;
   s32 qOffsetFreq;
   string s_dlBandwidth;
   std::vector<u32> EarfcnDLList;
   std::vector<u32> EarfcnULList;

   /*Fix for TDD Attach Iusse*/
   memset(freqInfo,0,sizeof(MsmLteNeighEutraFreq));

   /* Filling serving cell params */
   if( MSM_FALSE == GetMibCache().IsMibAttributePresent(fapLteDn,PARAM_ID_LTE_EARFCNDL_LIST ))
   {
      TRACE_PRINTF("%s: VALUE OF LTE_EARFCNDL_LIST IS NOT SET",__func__);
      return MSM_FALSE;
   }
   if( MSM_FALSE == GetMibCache().IsMibAttributePresent(fapLteDn,PARAM_ID_LTE_EARFCNUL_LIST ))
   {
      TRACE_PRINTF("%s: VALUE OF LTE_EARFCNUL_LIST IS NOT SET",__func__);
      return MSM_FALSE;
   }
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_EARFCNDL_LIST, EarfcnDLList);
   freqInfo->earfcnDl = EarfcnDLList.at(0);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_EARFCNUL_LIST, EarfcnULList);
   freqInfo->earfcnUl = EarfcnULList.at(0);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CELL_RESELECTION_PRIORITY,freqInfo->priority);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_QRX_LEVEL_MIN_SIB3, qRxLevMin);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qRxLevMin);
   freqInfo->qRxLevMin = atoi(qRxLevMin.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PMAX,freqInfo->pMax);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_T_RESELECTION_EUTRA, tReselection);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tReselection);
   freqInfo->tReselection = atoi(tReselection.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_TRESELECTION_EUTRAS_MED, freqInfo->tReselectionSFMed);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
         freqInfo->tReselectionSFMed, m_posu8);
   freqInfo->tReselectionSFMed = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_TRESELECTION_EUTRAS_HIGH, freqInfo->tReselectionSFHigh);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
         freqInfo->tReselectionSFHigh, m_posu8);
   freqInfo->tReselectionSFHigh = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_SINTRA_SEARCH, sIntraSearch);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(sIntraSearch);
   freqInfo->sIntraSearch = atoi(sIntraSearch.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_S_NON_INTRA_SEARCH, sNonIntraSearch);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(sNonIntraSearch);
   freqInfo->sNonIntraSearch = atoi(sNonIntraSearch.at(0).c_str());
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_THRESH_SERVING_LOW,freqInfo->servThresholdLow);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_THRESH_XHIGH, freqInfo->threshXHigh);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_THRESH_XLOW, freqInfo->threshXLow);

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_INTER_FREQ_QOFFSET, qOffsetFreq);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo,
         qOffsetFreq, m_posu8);
   freqInfo->qOffsetFreq = m_posu8;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_OAM_NEIGHBOUR_DL_BANDWIDTH_SIB3,s_dlBandwidth);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrdlBandwidthInfo,
         s_dlBandwidth, m_posu8, 6);
   freqInfo->measBandwidth = m_posu8;

   TRACE_PRINTF("\n##################################################\n");
   TRACE_PRINTF("Serving frequency details: \n");
   TRACE_PRINTF("\n##################################################\n");
   TRACE_PRINTF("earfcnDl : %d\n",freqInfo->earfcnDl);
   TRACE_PRINTF("earfcnUl : %d\n",freqInfo->earfcnUl);
   TRACE_PRINTF("priority : %d\n",freqInfo->priority);
   TRACE_PRINTF("qRxLevMin : %d\n",freqInfo->qRxLevMin);
   TRACE_PRINTF("pMax : %d\n",freqInfo->pMax);
   TRACE_PRINTF("tReselection : %d\n",freqInfo->tReselection);
   TRACE_PRINTF("tReselectionSFMed : %d\n",freqInfo->tReselectionSFMed);
   TRACE_PRINTF("tReselectionSFHigh : %d\n",freqInfo->tReselectionSFHigh);
   TRACE_PRINTF("sIntraSearch : %d\n",freqInfo->sIntraSearch);
   TRACE_PRINTF("sNonIntraSearch : %d\n",freqInfo->sNonIntraSearch);
   TRACE_PRINTF("servThresholdLow : %d\n",freqInfo->servThresholdLow);
   TRACE_PRINTF("threshXHigh : %d\n",freqInfo->threshXHigh);
   TRACE_PRINTF("threshXLow : %d\n",freqInfo->threshXLow);
   TRACE_PRINTF("qOffsetFreq : %d\n",freqInfo->qOffsetFreq);
   TRACE_PRINTF("measBandwidth : %d\n",freqInfo->measBandwidth);
   TRACE_PRINTF("\n##################################################\n");

   return MSM_TRUE;
}

u32 SmApplication::FillNeighFreqCarrByInstance(MibDN fapLteDn,u8 instance, MsmLteNeighEutraFreq *freqInfo)
{
   TRACE_PRINTF("%s\n",__func__);

   bool enable;
   std::vector<u32> interFreqCarrSrcLst;
   std::string measBandwidth, neighCellCfg;
   std::vector<std::string> qOffsetFreq, tReselection, qRxLevMin;

   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN neighFreqDn = MibDN::GenerateMibDN(fapLteDn,MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER,instance);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_X_RADISYS_NEIGH_FREQ_SRC, interFreqCarrSrcLst);

   if ((m_mib.IsMibObjectPresent(neighFreqDn)) && (interFreqCarrSrcLst[instance] == MIB_OBJ_CONFIGURED))
   {
      GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_INTER_FREQ_ENABLE,enable);
      if (enable == TRUE)
      {
         /* TR-196 Neighbour frequency parameters */
         /* DL EARFCN */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_DL_EARFCN, freqInfo->earfcnDl);
         /* QRxLevMinSIB5 */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_QRX_LEVEL_MIN, qRxLevMin);
         SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qRxLevMin);
         freqInfo->qRxLevMin = atoi(qRxLevMin.at(0).c_str());
         /* QOffsetFreq */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_QOFFSETFREQ, qOffsetFreq);
         SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qOffsetFreq);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, atoi(qOffsetFreq.at(0).c_str()), m_posu8);
         freqInfo->qOffsetFreq = m_posu8;
         freqInfo->offsetFreq = m_posu8;
         /* TReselectionEUTRA */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA, tReselection);
         SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tReselection);
         freqInfo->tReselection = atoi(tReselection.at(0).c_str());
         /* CellReselectionPriority */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_CELL_RESELECT_PRIORITY,
               freqInfo->priority);
         /* ThreshXHigh */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XHIGH,
               freqInfo->threshXHigh);
         /* ThreshXLow */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XLOW,
               freqInfo->threshXLow);
         /* PMax */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_PMAX,
               freqInfo->pMax);
         /* TReselectionEUTRASFMedium */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_MED,
               freqInfo->tReselectionSFMed);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
               freqInfo->tReselectionSFMed, m_posu8);
         freqInfo->tReselectionSFMed = m_posu8;
         /* TReselectionEUTRASFHigh */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_HIGH,
               freqInfo->tReselectionSFHigh);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
               freqInfo->tReselectionSFHigh, m_posu8);
         freqInfo->tReselectionSFHigh = m_posu8;
         /* Allowed measBandwidth */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_ALLOWD_MEAS_BW, measBandwidth);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().
               GetSmTr196Validator()->arrAllowedMeasBandwidthInfo, measBandwidth, m_posu8,6);
         freqInfo->measBandwidth = m_posu8;
         /* Presence antenna port 1 */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_PRES_ANTENNA_PORT1, freqInfo->presAntennaPort1);
         /* Qqualminr9 */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_QQUALMIN_R9,freqInfo->qQualMinRel9);
         /* threshX-HighQ-r9 */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_THRESHX_HIGHQ_R9,freqInfo->threshXHighQR9);
         /* threshX-LowQ-r9 */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_THRESHX_LOWQ_R9,freqInfo->threshXLowQR9);
         /* neighCellCfg */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_NEIGH_CELL_CONFIG, neighCellCfg);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteBitStringVals(SmApplication::GetInstance().
               GetSmTr196Validator()->arrNeighCellConfigInfo, neighCellCfg, m_posu8,4);
         freqInfo->neighCellCfg = m_posu8;
         /* UL EARFCN */
         GetMibCache().GetMibAttribute(neighFreqDn,PARAM_ID_LTE_X_RADISYS_INTER_FREQ_UL_EARFCN,freqInfo->earfcnUl);
      }
      else
      {
         TRACE_PRINTF("Enable field for instance %d is not TRUE\n",instance);
         return RFAILURE;
      }
   }
   else
   {
      if ((m_mib.IsMibObjectPresent(neighFreqDn)) && (interFreqCarrSrcLst[instance] == MIB_OBJ_INIT_DEF_VAL))
      {
         MsmLteNeighEutraFreq  defFreqInfo;

         /* TR-196 Neighbour frequency parameters */
         /* DL EARFCN */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_DL_EARFCN,
               defFreqInfo.earfcnDl);
         /* QRxLevMinSIB5 */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_QRX_LEVEL_MIN, qRxLevMin);
         SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qRxLevMin);
         defFreqInfo.qRxLevMin = atoi(qRxLevMin.at(0).c_str());
         /* QOffsetFreq */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_QOFFSETFREQ, qOffsetFreq);
         SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qOffsetFreq);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, atoi(qOffsetFreq.at(0).c_str()), m_posu8);
         defFreqInfo.qOffsetFreq = m_posu8;
         defFreqInfo.offsetFreq = m_posu8;
         /* TReselectionEUTRA */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA, tReselection);
         SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(tReselection);
         defFreqInfo.tReselection = atoi(tReselection.at(0).c_str());
         /* CellReselectionPriority */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_CELL_RESELECT_PRIORITY,
               defFreqInfo.priority);
         /* ThreshXHigh */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XHIGH,
               defFreqInfo.threshXHigh);
         /* ThreshXLow */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XLOW,
               defFreqInfo.threshXLow);
         /* PMax */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_PMAX,
               defFreqInfo.pMax);
         /* TReselectionEUTRASFMedium */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_MED,
               defFreqInfo.tReselectionSFMed);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
               defFreqInfo.tReselectionSFMed, m_posu8);
         defFreqInfo.tReselectionSFMed = m_posu8;
         /* TReselectionEUTRASFHigh */
         GetMibCache().GetMibAttribute(neighFreqDn, PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_HIGH,
               defFreqInfo.tReselectionSFHigh);
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrtReselectionSfInfo,
               defFreqInfo.tReselectionSFHigh, m_posu8);
         defFreqInfo.tReselectionSFHigh = m_posu8;
         TRACE_PRINTF("\n##################################################\n");
         TRACE_PRINTF("Object created and initialised with default values for the instance %d\n",instance);
         TRACE_PRINTF("\n##################################################\n");
         printFreqValuesFilled(&defFreqInfo);
      }
      else
      {
         TRACE_PRINTF("Object not present for the instance %d\n",instance);
      }
      return RFAILURE;
   }
   return ROK;
}

void SmApplication::printFreqValuesFilled(MsmLteNeighEutraFreq *freqInfo)
{
   TRACE_PRINTF("earfcnDl : %d\n",freqInfo->earfcnDl);
   TRACE_PRINTF("qRxLevMin : %d\n",freqInfo->qRxLevMin);
   TRACE_PRINTF("qOffsetFreq : %d\n",freqInfo->qOffsetFreq);
   TRACE_PRINTF("offsetFreq : %d\n",freqInfo->offsetFreq);
   TRACE_PRINTF("tReselection : %d\n",freqInfo->tReselection);
   TRACE_PRINTF("priority : %d\n",freqInfo->priority);
   TRACE_PRINTF("threshXHigh : %d\n",freqInfo->threshXHigh);
   TRACE_PRINTF("threshXLow : %d\n",freqInfo->threshXLow);
   TRACE_PRINTF("pMax : %d\n",freqInfo->pMax);
   TRACE_PRINTF("tReselectionSFMed : %d\n",freqInfo->tReselectionSFMed);
   TRACE_PRINTF("tReselectionSFHigh : %d\n",freqInfo->tReselectionSFHigh);
   TRACE_PRINTF("measBandwidth : %d\n",freqInfo->measBandwidth);
   TRACE_PRINTF("presAntennaPort1 : %d\n",freqInfo->presAntennaPort1);
   TRACE_PRINTF("qQualMinRel9 : %d\n",freqInfo->qQualMinRel9);
   TRACE_PRINTF("threshXHighQR9 : %d\n",freqInfo->threshXHighQR9);
   TRACE_PRINTF("threshXLowQR9 : %d\n",freqInfo->threshXLowQR9);
   TRACE_PRINTF("neighCellCfg : %d\n",freqInfo->neighCellCfg);
   TRACE_PRINTF("earfcnUl : %d\n",freqInfo->earfcnUl);

   return;
}

void SmApplication::FillEutraNeighCellCfgParameters(u16 cellIdx)
{
   TRACE_PRINTF("%s",__func__);

   MsmNeighCellCfg lteNeighCellCfg;
   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   u8 idx =0;
   u8 numRemLteScanCells = 0;
   u8 numEutraCfgdCells = 0;

   memset(&lteNeighCellCfg, 0, sizeof(MsmNeighCellCfg));

   lteNeighCellCfg.actType = MSM_ACT_ADD;

   MibDN remDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE);
   if(m_mib.IsMibAttributePresent(fapDn,PARAM_ID_LTE_NUM_REM_ENTRIES))
   {
      m_mib.GetMibAttribute(fapDn, PARAM_ID_LTE_NUM_REM_ENTRIES,
            numRemLteScanCells);
   }
   m_mib.GetMibAttribute(fapLteDn, PARAM_ID_LTE_CELL_ENTRIES,numEutraCfgdCells);
   lteNeighCellCfg.numEutraCells = numRemLteScanCells + numEutraCfgdCells;

   TRACE_PRINTF("numRemLteScanCells is %d, numEutraCfgdCells is %d",
         numRemLteScanCells,numEutraCfgdCells);

   if (numRemLteScanCells !=0)
   {
      FillRemLteScannedCells(&lteNeighCellCfg, &idx, &numRemLteScanCells);
   }

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_ENABLE_X2,
         lteNeighCellCfg.isX2Enabled);

   if (numEutraCfgdCells != 0)
   {
      FillEutraCfgdCells(&lteNeighCellCfg, &idx,cellIdx);
   }

   msmSetNeighborListInUseEutraParameters(&lteNeighCellCfg,cellIdx);
   return;
}

void SmApplication::FillUtraNeighCellCfgParameters(u16 cellIdx)
{
   TRACE_PRINTF("%s",__func__);

   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();

   MsmNeighCellCfg utraNeighCellCfg;
   u8 idx =0;
   u8 numRemWcdmaScanCells = 0;
   u8 numUtraCfgdCells = 0;
   MibDN remWcdmaDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA);

   memset(&utraNeighCellCfg, 0, sizeof(MsmNeighCellCfg));

   utraNeighCellCfg.actType = MSM_ACT_ADD;

   if(m_mib.IsMibAttributePresent(remWcdmaDn, PARAM_ID_NUM_CELL_ENTRIES))
   {
      m_mib.GetMibAttribute(remWcdmaDn, PARAM_ID_NUM_CELL_ENTRIES,
            numRemWcdmaScanCells);
   }
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   m_mib.GetMibAttribute(fapLteDn, PARAM_ID_LTE_NUM_UTRA_NEIGH_CELLS_ENTRIES,
         numUtraCfgdCells);

   TRACE_PRINTF("numRemWcdmaScanCells is %d, numUtraCfgdCells is %d",
         numRemWcdmaScanCells, numUtraCfgdCells);

   if (numRemWcdmaScanCells != 0)
   {
      FillRemWcdmaScannedCells(&utraNeighCellCfg, &idx, &numRemWcdmaScanCells);
   }

   if (numUtraCfgdCells != 0)
   {
      FillUtraCfgdCells(&utraNeighCellCfg, &idx, numUtraCfgdCells, cellIdx);
   }
   utraNeighCellCfg.numUtraCells = numRemWcdmaScanCells + numUtraCfgdCells;

   msmSetNeighborListInUseUtraParameters(&utraNeighCellCfg, cellIdx);
   return;
}

void SmApplication::FillRemLteScannedCells
(
 MsmNeighCellCfg *lteNeighCellCfg,
 u8 *idx,
 u8 *numRemLteScanCells
 )
{
   TRACE_PRINTF("%s",__func__);

   u8 instance;
   MsmEUTRANeighCell *cellInfo;
   MsmLteEarfcnRssiCfg msmLteEarfcnRssiCfg;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   TRACE_PRINTF("REM scanned LTE cell entries %d", *numRemLteScanCells);

   for (instance=0; instance < *numRemLteScanCells; instance++)
   {
      MibDN dnobj = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_LTE_REM_SCANNED_CELL,
            instance);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());

      cellInfo = &lteNeighCellCfg->t.neighAddCfg[*idx].eutraCell;

      if (m_mib.IsMibObjectPresent(dnobj))
      {
         TRACE_PRINTF("LTE REM object present at instance %d\n",instance);
         if (IsAllMandatoryParametersSet(dnobj))
         {
            SmApplication::GetInstance().readRemLteParameters(dnobj,cellInfo);
            msmLteEarfcnRssiCfg.remScanEarfcn[*idx].earfcnDl =
               cellInfo->earfcnDl;
            msmLteEarfcnRssiCfg.remScanEarfcn[*idx].rssi = (s32)cellInfo->rssi;
            (*idx)++;
         }
      }
      else
      {
         TRACE_PRINTF("LTE REM object not present at instance %d\n",instance);
      }
   }
   msmLteEarfcnRssiCfg.numEarfcn = *idx;
   msmSetEarfcnRssiParameters(&msmLteEarfcnRssiCfg, 0);
   return;
}

void SmApplication::FillRemWcdmaScannedCells
(
 MsmNeighCellCfg *utraNeighCellCfg,
 u8 *idx,
 u8 *numRemWcdmaScanCells
 )
{
   TRACE_PRINTF("%s",__func__);

   u8 instance;
   MsmUtraNeighCell *cellInfo;
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   TRACE_PRINTF("REM scanned UMTS LTE cell entries %d", *numRemWcdmaScanCells);

   for (instance=0; instance < *numRemWcdmaScanCells; instance++)
   {
      MibDN dnobj = MibDN::GenerateMibDN
         (MIB_OBJECT_CLASS_REM_SCANNED_WCDMA_CELL,instance);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());

      cellInfo = &utraNeighCellCfg->t.neighAddCfg[*idx].utranCell;

      if (m_mib.IsMibObjectPresent(dnobj))
      {
         TRACE_PRINTF("UMTS REM object present at instance %d\n",instance);
         if (IsAllMandatoryParametersSet(dnobj))
         {
            SmApplication::GetInstance().readRemUmtsParameters(dnobj,cellInfo);
            (*idx)++;
         }
      }
      else
      {
         TRACE_PRINTF("UMTS REM object not present at instance %d\n",instance);
      }
   }

   return;
}

void SmApplication::FillEutraCfgdCells(MsmNeighCellCfg *lteNeighCellCfg, u8 *idx,u16 cellIdx)
{
   TRACE_PRINTF("%s",__func__);

   u8 instance, maxEutraCfgdCells = 0;
   MsmEUTRANeighCell *cellInfo;
   bool cellEnable;
   std::vector<u32> neighborLteCellSrc;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   m_mib.GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_LTE_CELL, maxEutraCfgdCells);
   m_mib.GetMibAttribute(fapLteDn,PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC , neighborLteCellSrc);

   TRACE_PRINTF("oam-sm printing EUTRA configured cells ");

   for (instance=0; instance < maxEutraCfgdCells; instance++)
   {
      cellInfo = &lteNeighCellCfg->t.neighAddCfg[*idx].eutraCell;

      MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,instance);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());

      if((m_mib.IsMibObjectPresent(dnobj)) && 
            (neighborLteCellSrc[instance] == MIB_OBJ_CONFIGURED))
      {
         m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE, cellEnable);
         if (cellEnable)
         {
            SmApplication::GetInstance().readEutraParameters(dnobj,cellInfo);
            cellInfo->enable = cellEnable;
            dumpNbrMsmInfo(cellInfo);
            cellInfo->isHeMsCell = TRUE;

            TRACE_PRINTF("Pushed HeMS configured EUTRA cell at index %d\n",*idx);
            (*idx)++;
         }
         else
         {
            TRACE_PRINTF("Enable field for instance %d is not TRUE\n",instance);
         }
      }
   }
   return;
}

void SmApplication::FillUtraCfgdCells
(
 MsmNeighCellCfg *utraNeighCellCfg,
 u8 *idx,
 u8 &utraCfgdCells,
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s",__func__);

   u8               instance = 0;
   u8               maxUtraCfgdCells = 0;
   MsmUtraNeighCell *cellInfo;
   bool             cellEnable;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   m_mib.GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_UMTS_ENTRIES,
         maxUtraCfgdCells);

   utraCfgdCells = 0;
   TRACE_PRINTF("oam-sm printing UTRA configured cells ");

   for (instance = 0; instance < MAX_UMTS_OBJ; instance++)
   {
      cellInfo = &utraNeighCellCfg->t.neighAddCfg[*idx].utranCell;

      MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,
            MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR, instance);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());

      if(m_mib.IsMibObjectPresent(dnobj))
      {
         m_mib.GetMibAttribute(dnobj,
               PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_ENABLE, cellEnable);
         if (cellEnable)
         {
            utraCfgdCells ++;
            SmApplication::GetInstance().ReadUtraParameters(dnobj, cellInfo);

            TRACE_PRINTF("Pushed HeMS configured UTRA cell at index %d\n",*idx);
            (*idx)++;
         }
         else
         {
            TRACE_PRINTF("Enable field for instance %d is not TRUE\n",instance);
         }
      }
   }
   return;
}

void SmApplication::FillNeighCellCfgParameters()
{
   TRACE_PRINTF("%s",__func__);

   for (u16 cellIdx=0; cellIdx < numOfCells; cellIdx++)
   {
      FillAllUtraFdd(cellIdx);
      FillGeranNeighFreqParameters(cellIdx);
      FillTdScdmaUtranFreqParameters(cellIdx);
      FillCdmaBandClassParameters(cellIdx);
      FillCDMA1xNeighCell(cellIdx);
      FillEutraNeighCellCfgParameters(cellIdx);
      FillUtraNeighCellCfgParameters(cellIdx);
      UpdateGSMNbrToMsm(cellIdx);
      FillTdScdmaCellCfgParameters(cellIdx);
   }
   return;
}

void SmApplication::HandleLteNeighCellCfgParameters
(
 u16 subscribs,
 u8 instance,
 bool isDynCfg,
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<u32> neighborLteCellSrc;
   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN neighCellDn;
   u32 neighborEnable, cid;
   std::string plmnId;
   s32 inuseInstanceNbr;
   MsmDynNeighCellCfg lteNeighCellCfg;

   memset(&lteNeighCellCfg,0,sizeof(MsmDynNeighCellCfg));
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   switch (subscribs)
   {
      case SI_NBR_CELL_PARAMETERS:
      case SI_EUTRA_NBR_CELL_OBJ:
         {
            if (isDynCfg || ( m_isSONRaisedAlarmExists > 0 ) )
            {/*For Dynamic update of Parameters*/
               GetMibCache().GetMibAttribute(fapLteDn,
                     PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC , neighborLteCellSrc);
               neighCellDn = MibDN::GenerateMibDN(fapLteDn,
                     MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,instance);

               if (((m_mib.IsMibObjectPresent(neighCellDn)) &&
                        (neighborLteCellSrc[instance] == MIB_OBJ_CONFIGURED)))
               {
                  GetMibCache().GetMibAttribute(neighCellDn,
                        PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE,neighborEnable);
                  if (neighborEnable)
                  {
                     SmApplication::GetInstance().readEutraParameters(
                           neighCellDn,
                           &lteNeighCellCfg.t.addModCfg.t.eutraCell);
                     GetMibCache().GetMibAttribute(neighCellDn,
                           PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PLMNID, plmnId);
                     GetMibCache().GetMibAttribute(neighCellDn,
                           PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CID, cid);

                     inuseInstanceNbr = getEutraInuseInstanceNbr(fapLteDn,
                           plmnId, cid);
                     /* If in IN_USE list, already existing so action will be
                      * modify */
                     if (inuseInstanceNbr != -1)
                     {
                        lteNeighCellCfg.actType = MSM_ACT_MOD;

                        lteNeighCellCfg.t.addModCfg.t.eutraCell.nrIndex =
                           instance;
                     }
                     else
                     {
                        lteNeighCellCfg.actType = MSM_DYN_ADD;
                        lteNeighCellCfg.t.addModCfg.t.eutraCell.isHeMsCell =
                           TRUE;
                        lteNeighCellCfg.t.addModCfg.t.eutraCell.nrIndex =
                           instance;
                     }
                     MsmSmmDynCfgReq((void*)&lteNeighCellCfg,
                           MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS,cellIdx);
                  }
               }
               else if (neighborLteCellSrc[instance] == MIB_OBJ_DELETED)
               {
                  lteNeighCellCfg.actType = MSM_ACT_DEL;
                  lteNeighCellCfg.t.delCfg.t.eutranCell.nrIndex = instance;
                  MsmSmmDynCfgReq((void*)&lteNeighCellCfg,
                        MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS, cellIdx);
               }
            }
         }
         break;
      default:
         {
            TRACE_PRINTF("Unhandled parameter of \
                  HandleLteNeighCellCfgParameters ");
         }
         break;
   }
   return;
} 

void SmApplication::HandleLteCnmParameters(
      u16    cellIdx,
      bool   isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmCnmCfg lteCnmCfg;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   if(!isDynCfg)
   {
      lteCnmCfg.actType = MSM_ACT_ADD;

      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CNM_ENABLE,lteCnmCfg.cnmEnable);

      msmSetCellCnmCfgGrpParameters(&lteCnmCfg,cellIdx);
   }
   else
   {

      TRACE_PRINTF("Dynamic update for CNM not allowed");
   }
   return;
}

void SmApplication::dumpNbrMsmInfo(MsmEUTRANeighCell* eutraCell)
{
   TRACE_PRINTF("nrIndex: %d", eutraCell->nrIndex);
   TRACE_PRINTF("enable: %d", eutraCell->enable);
   TRACE_PRINTF("pci: %d", eutraCell->pci);
   TRACE_PRINTF("earfcndl: %d", eutraCell->earfcnDl);
   TRACE_PRINTF("earfcnul: %d", eutraCell->earfcnUl);
   TRACE_PRINTF("cid: %d", eutraCell->cid);
   TRACE_PRINTF("tac: %d", eutraCell->tac);
   TRACE_PRINTF("numplmn: %d", eutraCell->numPlmn);
   TRACE_PRINTF("numMncDigits : %d",eutraCell->plmnId[0].numMncDigits);
   TRACE_PRINTF("mcc : %d%d%d",eutraCell->plmnId[0].mcc[0],eutraCell->plmnId[0].mcc[1],eutraCell->plmnId[0].mcc[2]);
   TRACE_PRINTF("mnc : %d%d%d",eutraCell->plmnId[0].mnc[0],eutraCell->plmnId[0].mnc[1],eutraCell->plmnId[0].mnc[2]);
   TRACE_PRINTF("qoffset: %d", eutraCell->qoffset);
   TRACE_PRINTF("cio: %d", eutraCell->cio);
   TRACE_PRINTF("RSTxPower: %d", eutraCell->RSTxPower);
   TRACE_PRINTF("BlackListed: %d", eutraCell->BlackListed);
   TRACE_PRINTF("csgAccessMode: %d", eutraCell->csgAccessMode);
   TRACE_PRINTF("csgId: %d", eutraCell->csgId);
   TRACE_PRINTF("numAntenna: %d", eutraCell->numAntenna);
   TRACE_PRINTF("ulDlSubFrameCfg: %d", eutraCell->ulDlSubFrameCfg);
   TRACE_PRINTF("splSfCfg: %d", eutraCell->splSfCfg);
   TRACE_PRINTF("cpDl: %d", eutraCell->cpDl);
   TRACE_PRINTF("cpUl: %d", eutraCell->cpUl);
   TRACE_PRINTF("rsrp: %u", eutraCell->rsrp);
   TRACE_PRINTF("rssi: %u", eutraCell->rssi);
   TRACE_PRINTF("dlBw: %u", eutraCell->dlBw);
   TRACE_PRINTF("ulBw: %u", eutraCell->ulBw);
}

void SmApplication::HandleCsfbGeranCfgParameters(
      u16    cellIdx,
      bool   isDynCfg
      )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteCsfbGeranCfg       csfbToGeranCfg;
   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   ReadCsfbGeranCfgParameters(dn,csfbToGeranCfg);

   if (!isDynCfg)
   {
      msmSetcsfbGeranCfgParameters(&csfbToGeranCfg,cellIdx);
   }
   else
   {
      TRACE_PRINTF("CsfbGeranCfg parameters are dynamically not supported.");
   }
}

void SmApplication::ReadCsfbGeranCfgParameters( 
      MibDN dn,
      MsmLteCsfbGeranCfg &csfbToGeranCfg
      )
{
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_MEAS_ALLOW_CCO, csfbToGeranCfg.isGERANMeasAllowedForCCO);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_CCO_ALLOW, csfbToGeranCfg.isCCOAllowed);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_MEAS_WAIT_TMR, csfbToGeranCfg.GERANMeasWaitTmr);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_T304_EXP_WAIT_TMR, csfbToGeranCfg.T304expWaitTmrVal);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_GERAN_RRC_DAT_CFM_TMR, csfbToGeranCfg.rrcDatCfmWaitTmr);
}

void SmApplication::FillGeranNeighFreqParameters
(
 u16  cellIdx
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> qRxLevMin;
   U8                   geranFreqEntries;
   string               nccPermit;
   U32                  freqEnable = 0,nccPermitted = 0,idx,numEnabledObj=0;
   vector<u32>          geranFreqSrc;
   string               bandInd;
   MibAttributeValues   attrs;
   MsmLteNeighFreqCfg   lteNeighFreqCfg;
   MsmLteNeighGERANFreq *geranFreq;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_GERAN_MAX_FREQ_ENTRIES, geranFreqEntries);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_GERAN_FREQ_SRC,
         geranFreqSrc);
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   for(U32 geranFreqIdx=0; geranFreqIdx < geranFreqEntries; geranFreqIdx++)
   {
      MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST,
            geranFreqIdx);
      TRACE_PRINTF("GERAN Mibdn generated: %s", dnobj.ToString().c_str());
      if(m_mib.IsMibObjectPresent(dnobj))
      {
         GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_FREQ_ENABLE,
               freqEnable);
         if((MIB_OBJ_CONFIGURED == geranFreqSrc.at(geranFreqIdx))
               && (TRUE == freqEnable))
         {
            geranFreq =
               &(lteNeighFreqCfg.t.addNeighFreq[numEnabledObj].geranFreq);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_FREQ_BAND_INDICATOR, bandInd);
            SmApplication::GetInstance().GetSmTr196Validator()->
               GetLteStringenums(SmApplication::GetInstance().
                     GetSmTr196Validator()->arrGeranBandInd, bandInd,
                     m_posu8, 4);
            geranFreq->bandIndicator = m_posu8;
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_FREQ_BCCH_ARFCN,geranFreq->bcchArfcn);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_FREQ_QRX_LEV_MIN, qRxLevMin);
            SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(qRxLevMin);
            geranFreq->qRxLevMin = atoi(qRxLevMin.at(0).c_str());
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_FREQ_CELL_RESEL_PRIOR,
                  geranFreq->cellReselectionPriority);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_FREQ_THRESHX_HIGH,
                  geranFreq->threshXHigh);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_FREQ_THRESHX_LOW,geranFreq->threshXLow);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_X_RSYS_FREQ_NCC_PERMIT,nccPermit);
            for (idx = 0; nccPermit[idx] != '\0'; idx++)
            {
               nccPermitted = (nccPermitted << 1) + nccPermit[idx] - '0';
            }
            geranFreq->ncc_Permitted = nccPermitted;
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_X_RSYS_FREQ_PRES_PMAX,
                  geranFreq->pMaxPres);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_GERAN_X_RSYS_FREQ_PMAX,geranFreq->pMax);

            numEnabledObj++;
         }
      }
   }
   lteNeighFreqCfg.numGeranFreq = numEnabledObj;
   msmSetNeighFreqCfgGeranParameters(&lteNeighFreqCfg, cellIdx);
   return;
}

void SmApplication::dumpGSMNbrMsmInfo(MsmLteGERANNeighCell* geranCell)
{
   TRACE_PRINTF("lac: %d", geranCell->lac);
   TRACE_PRINTF("rac: %d", geranCell->rac);
   TRACE_PRINTF("bsic: %d", geranCell->bsic);
   TRACE_PRINTF("ci: %d", geranCell->ci);
   TRACE_PRINTF("bandIndicator: %d", geranCell->bandIndicator);
   TRACE_PRINTF("bcchArfcn: %d", geranCell->bcchArfcn);
   TRACE_PRINTF("ncc_PermittedMeas: %d", geranCell->ncc_PermittedMeas);
   TRACE_PRINTF("isDTMCapable : %d",geranCell->isDTMCapable);
   TRACE_PRINTF("networkControlOrder : %d",geranCell->networkControlOrder);
   TRACE_PRINTF("networkControlOrderPres: %d",
         geranCell->networkControlOrderPres);
   TRACE_PRINTF("rimSupportForGeranNgh: %d", geranCell->rimSupportForGeranNgh);
   TRACE_PRINTF("numMncDigits : %d",geranCell->plmnId.numMncDigits);
   TRACE_PRINTF("mcc : %d%d%d",geranCell->plmnId.mcc[0],geranCell->plmnId.mcc[1]
         ,geranCell->plmnId.mcc[2]);
   TRACE_PRINTF("mnc : %d%d%d",geranCell->plmnId.mnc[0],geranCell->plmnId.mnc[1]
         ,geranCell->plmnId.mnc[2]);
}

s32 SmApplication::GetGeranInUseInstanceNbr
(
 std::string geranPlmnId,
 u32 geranCi,
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s",__func__);

   std::string plmnId;
   s32 instanceNbr = -1;
   u32 ci;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   for (u32 inst = 0; inst < MAX_GERAN_NEIGHBOR_CELLS_IN_USE; inst++)
   {
      MibDN dnobj = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
      MibDN inUseDn = MibDN::GenerateMibDN(dnobj,
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST,
            inst);
      if(m_mib.IsMibObjectPresent(inUseDn))
      {
         m_mib.GetMibAttribute(inUseDn,PARAM_ID_LTE_GERAN_CELL_IN_USE_CI,ci);
         if(ci == geranCi)
         {
            m_mib.GetMibAttribute(inUseDn, PARAM_ID_LTE_GERAN_CELL_IN_USE_PLMNID,
                  plmnId);
            if(strstr(plmnId.c_str(),geranPlmnId.c_str()))
            {
               instanceNbr = (s32)inst;
            }
         }
      }
   }
   return instanceNbr;
}

void SmApplication::updateGeranInUseNbr
(
 MsmLteGERANNeighCell *updatedGeranCell,
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s",__func__);

   s32 inUseInstNum;
   std::string plmnId;

   SmApplication::GetInstance().GetPlmn(updatedGeranCell->plmnId, plmnId);
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   inUseInstNum = SmApplication::GetInstance().GetGeranInUseInstanceNbr(plmnId,
         updatedGeranCell->ci, cellIdx);
   if(-1 == inUseInstNum)
   {
      TRACE_PRINTF("GERAN neighbour with PLMN ID : %s, CI : %d not yet added,\
            adding to GERAN IN USE",plmnId.c_str(), updatedGeranCell->ci);
      inUseInstNum = SmMultiInstanceObjectManager:: GetInstance().addMIO(
            fapLteDn,
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST);
   }
   else
   {
      TRACE_PRINTF("GERAN neighbour with PLMN ID : %s, CI : %d already exist in\
            GERAN IN USE",plmnId.c_str(), updatedGeranCell->ci);
      return;
   }
   MibDN gsmDn = MibDN::GenerateMibDN(fapLteDn,
         MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST,
         inUseInstNum);
   updateGeranInUseInstance(gsmDn, updatedGeranCell);
}

void SmApplication::updateGeranInUseInstance
(
 MibDN gsmDn,
 MsmLteGERANNeighCell *geranCellCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   string bandInd, plmn, nccPermit = "00000000";;
   MibAttributeValues attrs;
   int cnt = 0;

   attrs.AddAttribute(PARAM_ID_LTE_GERAN_CELL_IN_USE_LAC,
         (u32)geranCellCfg->lac);
   SmApplication::GetInstance().GetPlmn(geranCellCfg->plmnId,plmn);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_CELL_IN_USE_PLMNID,plmn.c_str());
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_CELL_IN_USE_CI,(u32)geranCellCfg->ci);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_CELL_IN_USE_BSIC,
         (u32)geranCellCfg->bsic);
   bandInd = SmTr196Validator::arrGeranBandInd[geranCellCfg->bandIndicator];
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_CELL_IN_USE_BAND_INDICATOR,bandInd);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_CELL_IN_USE_BCCH_ARFCN,
         (u32)geranCellCfg->bcchArfcn);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_IN_USE_RAC,
         (u32)geranCellCfg->rac);
   for(cnt = nccPermit.size(); geranCellCfg->ncc_PermittedMeas > 0 && cnt > 0;
         cnt--)
   {
      nccPermit[cnt-1] = geranCellCfg->ncc_PermittedMeas % 2 + 48;
   }
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_IN_USE_NCC_PERMIT,
         nccPermit.c_str());
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_IN_USE_DTM_CAPABLE,
         (u32)geranCellCfg->isDTMCapable);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_IN_USE_NET_CNTRL_ORDER,
         (u32)geranCellCfg->networkControlOrder);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_IN_USE_NET_CNTRL_ORDER_PRES
         ,(u32)geranCellCfg->networkControlOrderPres);
   attrs.AddAttribute(PARAM_ID_LTE_GERAN_X_RSYS_CELL_IN_USE_RIM_SUPPORTED,
         (u32)geranCellCfg->rimSupportForGeranNgh);
   GetMibCache().SetMibAttributesByDn(gsmDn, attrs, ENTITY_OAM);
   TRACE_PRINTF("Set IN USE Values");
}

void SmApplication::UpdateGSMNbrToMsm(u16 cellIdx)
{
   TRACE_PRINTF("%s\n",__func__);

   u32             maxCells;
   MsmNeighCellCfg gsmNeighCellCfg;
   u32             numGeranCells = 0;

   memset(&gsmNeighCellCfg,0,sizeof(MsmDynNeighCellCfg));
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_GERAN_MAX_CELL_ENTRIES, maxCells);

   for (u32 inst=0; inst<maxCells; inst++)
   {
      FillGSMToMsmByInstance(fapLteDn, inst,
            &gsmNeighCellCfg.t.neighAddCfg[numGeranCells].geranCell, cellIdx,
            numGeranCells);
   }
   gsmNeighCellCfg.numGeranCells = numGeranCells;

   msmSetNeighCellCfgGeranParameters(&gsmNeighCellCfg, cellIdx);
}

void SmApplication::FillGSMToMsmByInstance
(
 MibDN fapLteDn,
 u32 instance,
 MsmLteGERANNeighCell* geranCell,
 u16 cellIdx,
 u32& numGeranCells
 )
{
   TRACE_PRINTF("%s",__func__);

   string      bandInd, plmnId, nccPermit;
   vector<u32> geranCellSrc;
   U32         nccPermitted = 0, idx;
   U16         cellEnable = 0;

   MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,
         MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST,instance);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_GERAN_CELL_SRC,
         geranCellSrc);
   if(!GetMibCache().IsMibObjectPresent(dnobj))
   {
      return;
   }
   GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_CELL_ENABLE,
         cellEnable);
   if ((TRUE == cellEnable) && (MIB_OBJ_CONFIGURED ==
            geranCellSrc.at(numGeranCells)))
   {
      GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_CELL_LAC,
            geranCell->lac);
      GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_CELL_BSIC,
            geranCell->bsic);
      GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_CELL_CI,
            geranCell->ci);
      GetMibCache().GetMibAttribute(dnobj,
            PARAM_ID_LTE_GERAN_CELL_BAND_INDICATOR, bandInd);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums
         (SmApplication::GetInstance().GetSmTr196Validator()->arrGeranBandInd,
          bandInd, m_posu8, 4);
      geranCell->bandIndicator = m_posu8;
      GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_CELL_BCCH_ARFCN,
            geranCell->bcchArfcn);
      GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_CELL_PLMNID,
            plmnId);
      SmApplication::GetInstance().FillPlmn(&geranCell->plmnId,plmnId);
      GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_GERAN_X_RSYS_CELL_RAC,
            geranCell->rac);
      GetMibCache().GetMibAttribute(dnobj,
            PARAM_ID_LTE_GERAN_X_RSYS_CELL_DTM_CAPABLE,geranCell->isDTMCapable);
      GetMibCache().GetMibAttribute(dnobj,
            PARAM_ID_LTE_GERAN_X_RSYS_CELL_NET_CNTRL_ORDER_PRES,
            geranCell->networkControlOrderPres);
      GetMibCache().GetMibAttribute(dnobj,
            PARAM_ID_LTE_GERAN_X_RSYS_CELL_NET_CNTRL_ORDER,
            geranCell->networkControlOrder);
      GetMibCache().GetMibAttribute(dnobj,
            PARAM_ID_LTE_GERAN_X_RSYS_CELL_RIM_SUPPORTED,
            geranCell->rimSupportForGeranNgh);
      GetMibCache().GetMibAttribute(dnobj,
            PARAM_ID_LTE_GERAN_X_RSYS_CELL_NCC_PERMIT, nccPermit);
      for (idx = 0; nccPermit[idx] != '\0'; idx++)
      {
         nccPermitted = (nccPermitted << 1) + nccPermit[idx] - '0';
      }
      geranCell->ncc_PermittedMeas = nccPermitted;
      dumpGSMNbrMsmInfo(geranCell);
      numGeranCells++;
   }
}

void SmApplication::FillTdScdmaUtranFreqParameters
(
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s\n",__func__);

   U8                     tdsCdmaFreq;
   U8                     tdsCdmaFreqEntries;
   U32                    freqEnable = 0;
   vector<u32>            tdsCdmaFreqSrc;
   string                 utraTddMode;
   u16                    numTdsCdmaFreq = 0;
   MsmLteNeighFreqCfg     lteNeighFreqCfg;
   MsmLteNeighUtraTddFreq *utranTddFreq;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_TDS_CDMA_MAX_UTRANTDD_FREQ_ENTRIES,tdsCdmaFreqEntries);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_TDS_CDMA_FREQ_SRC, tdsCdmaFreqSrc);
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   for(tdsCdmaFreq=0; tdsCdmaFreq <= tdsCdmaFreqEntries; tdsCdmaFreq++)
   {
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
      MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,
            MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_FREQ_LIST, tdsCdmaFreq);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());
      if(m_mib.IsMibObjectPresent(dnobj))
      {
         GetMibCache().GetMibAttribute(dnobj,
               PARAM_ID_LTE_TDS_CDMA_FREQ_ENABLE, freqEnable);
         if((MIB_OBJ_CONFIGURED == tdsCdmaFreqSrc.at(tdsCdmaFreq)) &&
               (TRUE == freqEnable))
         {
            TRACE_PRINTF("%s is Enabled and Configured ",
                  dnobj.ToString().c_str());
            utranTddFreq = &(lteNeighFreqCfg.t.addNeighFreq[numTdsCdmaFreq].
                  utranTddFreq);
            utranTddFreq->freqIndex = numTdsCdmaFreq + 1;
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_UTRA_ARFCN, utranTddFreq->arfcn);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_QRX_LEV_MIN,utranTddFreq->qRxLevMin);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_CELL_RESEL_PRIOR,
                  utranTddFreq->priority);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_THRESH_X_HIGH,
                  utranTddFreq->threshXhigh);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_THRESH_X_LOW,
                  utranTddFreq->threshXlow);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_PMAX_UTRA, utranTddFreq->pMaxUtra);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_QOFFSET_UTRATDD,
                  utranTddFreq->offsetFreq);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_UTRATDD_MODE, utraTddMode);
            SmApplication::GetInstance().GetSmTr196Validator()->
               GetLteStringenums(SmApplication::GetInstance().
                     GetSmTr196Validator()->arrUtraTddMode, utraTddMode,
                     m_posu8, 3);
            utranTddFreq->tddMode = m_posu8;

            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_UTRATDD_BAND_INDICATOR,
                  utranTddFreq->bandIndicator);
            numTdsCdmaFreq++;
         }
      }
   }
   lteNeighFreqCfg.numUtraTddFreq = numTdsCdmaFreq;
   msmSetTdsCdmaUtranTddFreqParameters(&lteNeighFreqCfg, cellIdx);
}

void SmApplication::FillTdScdmaCellCfgParameters(u16 cellIdx)
{
   TRACE_PRINTF("%s\n",__func__);

   u32                 plmnidlength = 0;
   U32                 cellEnable = 0;
   string              plmnidvalue,mccvalue,mncvalue;
   vector<u32>         tdsCdmaCellSrc;
   u8                  idx = 0;
   u16                 numTdsCdmaCell = 0;
   u32                 tdsCdmaCell;
   u32                 tdsCdmaCellEntries;
   MsmNeighCellCfg     lteNeighCellCfg;
   MsmUtraTddNeighCell *utranTddCell;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_TDS_CDMA_MAX_UMTSTDD_ENTRIES, tdsCdmaCellEntries);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_TDS_CDMA_CELL_SRC,
         tdsCdmaCellSrc);
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   for(tdsCdmaCell=0; tdsCdmaCell <= tdsCdmaCellEntries; tdsCdmaCell++)
   {
      MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,
            MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_CELL_LIST, tdsCdmaCell);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());
      if(m_mib.IsMibObjectPresent(dnobj))
      {
         GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_CELL_ENABLE,
               cellEnable);
         if((MIB_OBJ_CONFIGURED == tdsCdmaCellSrc.at(tdsCdmaCell)) &&
               (TRUE == cellEnable))
         {
            utranTddCell = &(lteNeighCellCfg.t.neighAddCfg[numTdsCdmaCell].
                  utranTddCell);
            utranTddCell->nrIndex = numTdsCdmaCell + 1;
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_RNCID,
                  utranTddCell->rncId);
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_CID,
                  utranTddCell->cId);
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_LAC,
                  utranTddCell->lac);
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_RAC,
                  utranTddCell->rac);
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_URA,
                  utranTddCell->ura);
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_UARFCN,
                  utranTddCell->arfcn);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_CELL_PARAM_ID,
                  utranTddCell->cellParamId);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_PRI_CCPCH_PWR, utranTddCell->pccpch);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_TDS_CDMA_CELL_RIM_SUPPORT,
                  utranTddCell->isRimSupported);
            GetMibCache().GetMibAttribute(dnobj, PARAM_ID_LTE_TDS_CDMA_PLMNID,
                  plmnidvalue);
            plmnidlength = plmnidvalue.length(); 

            utranTddCell->numPlmn = 1;

            for(idx = 0; idx < plmnidlength; idx++)
            {
               if(idx < MSM_MAX_MCC_DIGITS)
               {
                  mccvalue = plmnidvalue.substr(idx,1);
                  utranTddCell->plmnId[0].mcc[idx] = u8(atoi(mccvalue.c_str()));
               }
               else
               {
                  mncvalue = plmnidvalue.substr(idx,1);
                  utranTddCell->plmnId[0].mnc[idx-3] =
                     u8(atoi(mncvalue.c_str()));
               }

               utranTddCell->plmnId[0].numMncDigits = (plmnidlength - 3); 
            }
            numTdsCdmaCell++;
         }
      }
   }
   lteNeighCellCfg.numUtraTddCells = numTdsCdmaCell;
   msmSetTdsCdmaUtranTddCellParameters(&lteNeighCellCfg, cellIdx);
}

void SmApplication::HandleTenbStatsCfgParams
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmTenbStatsCfg tenbStatsCfg={0}; 
   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);
   ReadTenbStatsCfgParams(dn,tenbStatsCfg);
   if(!isDynCfg)
   {
      msmSetTenbStatsCfgGrpParameters(&tenbStatsCfg);
   }
   else
   {
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&tenbStatsCfg, MSM_TENB_STATS_CFG, cellIdx);
   }
}

void SmApplication::ReadTenbStatsCfgParams
(
 MibDN dn,
 MsmTenbStatsCfg &tenbStatsCfg
 )
{
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TENB_STATS_SOCKET_ENABLE,
         tenbStatsCfg.tenbSocketStats);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TENB_FILE_STATS_ENABLE,
         tenbStatsCfg.tenbFileStats);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TENB_CONSOLE_STATS_ENABLE,
         tenbStatsCfg.tenbConsoleStats);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TENB_STATS_PERIODICITY,
         tenbStatsCfg.tenbStatsPeriodicity);
   GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_TENB_STATS_SCOKET_PORT,
         tenbStatsCfg.tendStatsSocketPort);
   return;
}

void SmApplication::HandleLteRemEarfcnAndRSSIParameters(
      u16    cellIdx,
      bool   isDynCfg
      )
{
   TRACE_PRINTF("%s\n",__func__);

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   if(!isDynCfg)
   {

      MsmLteEarfcnRssiCfg lteEarFCNRssi;
      u32 numEarfcnRssi;
      std::vector<u32> earfcnDLList;
      std::vector<s32> rssiList;
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_NUM_EARFCN,
            numEarfcnRssi);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_RSSI, rssiList);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_EARFCNDL, earfcnDLList);

      lteEarFCNRssi.numEarfcn = numEarfcnRssi;
      for( size_t idx = 0; idx < numEarfcnRssi; idx++ )
      {
         lteEarFCNRssi.remScanEarfcn[idx].earfcnDl = earfcnDLList[idx];
         lteEarFCNRssi.remScanEarfcn[idx].rssi = rssiList[idx]; 
      }

      msmSetEarfcnRssiParameters(&lteEarFCNRssi,cellIdx);
   }
   else
   {
      TRACE_PRINTF("REM Earfcn And RSSI parameters are not dynamically\
            supported");
   }
}

void SmApplication::ReadLteEnbProtoCfgParameters
(
 MibDN fapLteDn,
 MsmLteEnbProtoCfg &lteEnbProtoCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   IPv4Address siglinkip;
   string siglinkserver;
   string henbNameString;
   string ratPrior, ratPriorVal; 
   u32 ratPriorLen = 0;
   std::vector<std::string> plmnRatPriorList;
   u32 valueu32; 
   u16 idx = 0, index = 0, numRats = 0; 

   memset(&lteEnbProtoCfg,0,sizeof(MsmLteEnbProtoCfg));

   GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),
         PARAM_ID_LTE_S1SIG_LINK_PORT,lteEnbProtoCfg.sctpPortNumS1);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_X2SIG_LINK_PORT,
         lteEnbProtoCfg.sctpPortNumX2);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_HOME_NODEB_NAME,
         henbNameString);

   for(idx=0;idx < henbNameString.length();idx++)
   {
      lteEnbProtoCfg.henbName[idx] =henbNameString[idx];
   }	
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_NUM_OF_PLMN_ENTRIES,
         valueu32);
   lteEnbProtoCfg.numPlmns = (unsigned long)valueu32;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_UE_INACTIVITY_TIMER_VAL,
         valueu32);
   lteEnbProtoCfg.inactvTmrVal = CONVERT_SECONDS_TO_MILLISEC(valueu32);

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_UE_END_MARKER_TIMER_VAL,
         valueu32);
   lteEnbProtoCfg.endMrkTmrVal = (unsigned long)valueu32;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_EXPIRY_COUNT,
         valueu32);
   lteEnbProtoCfg.maxExpires = (unsigned long)valueu32;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ETWS_CMAS_ENABLE,
         valueu32);
   lteEnbProtoCfg.pwsEtwsCmas = (u8)valueu32;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CSFB_PLMN_RAT_PRIOR,
         plmnRatPriorList);
   for(index=0; index< plmnRatPriorList.size(); index++)
   {
      ratPrior = plmnRatPriorList[index];
      ratPriorLen = ratPrior.length();
      numRats = 0;
      for(idx = 0; idx < ratPriorLen; idx++)
      {
         ratPriorVal = ratPrior.substr(idx, 1);
         lteEnbProtoCfg.plmnRatPriority[index].rat[numRats] =
            u8(atoi(ratPriorVal.c_str()));
         idx += 1;
         numRats++;
      } 
      lteEnbProtoCfg.plmnRatPriority[index].numberOfRats = numRats;
   }
#ifndef TIP_OAM
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_X_RADISYS_NUM_OF_CELLS,
         numOfCells);
   lteEnbProtoCfg.numOfCells = numOfCells;
#endif
}

void SmApplication::HandleLteEnbProtoCfgParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   string ratPrior, ratPriorVal; 
   u32 valueu32;
#ifdef TIP_OAM
   static U32 numCells; 
#endif
   MsmLteEnbProtoCfg lteEnbProtoCfg;
   memset(&lteEnbProtoCfg,0,sizeof(MsmLteEnbProtoCfg));
   std::vector<std::string> plmnRatPriorList;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   ReadLteEnbProtoCfgParameters(fapLteDn,lteEnbProtoCfg);
#ifdef TIP_OAM
   if(0 == cellIdx)
   {
      GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_X_TIP_NUM_OF_CELLS,
         numCells);
   }
   numOfCells = numCells;
   lteEnbProtoCfg.numOfCells = numOfCells;
#endif
   if(!isDynCfg)
   {
      lteEnbProtoCfg.actType = MSM_ACT_ADD;
      msmSetEnbProtoCfgParameters(&lteEnbProtoCfg,cellIdx);
   }
   else
   {/*For Dynamic update of Parameters*/
      lteEnbProtoCfg.actType = MSM_ACT_MOD;

      GetMibCache().GetMibAttribute(PARAM_ID_LTE_ETWS_CMAS_ENABLE, valueu32);
      lteEnbProtoCfg.pwsEtwsCmas = (u8)valueu32;
      GetMibCache().GetMibAttribute(PARAM_ID_LTE_CSFB_PLMN_RAT_PRIOR,
            plmnRatPriorList);
      for(u32 index=0; index< plmnRatPriorList.size(); index++)
      {
         u32 ratPriorLen = 0;
         ratPrior = plmnRatPriorList[index];
         ratPriorLen = ratPrior.length();
         u32 numRats = 0;
         for(u32 idx = 0; idx < ratPriorLen; idx++)
         {
            ratPriorVal = ratPrior.substr(idx, 1);
            lteEnbProtoCfg.plmnRatPriority[index].rat[numRats] =
               u8(atoi(ratPriorVal.c_str()));
            idx += 1;
            numRats++;
         } 
         lteEnbProtoCfg.plmnRatPriority[index].numberOfRats = numRats;
      }
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteEnbProtoCfg, MSM_LTE_ENB_PROTO_CFG_PARAMETERS,
            cellIdx);
   }
}

void SmApplication::ReadLteSelfConfigParameters
(
 MibDN fapLteDn,
 MsmLteSonGenericParams &lteSelfConfigParams
 )
{
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_SELFCONFIG_PHY_CELLID_ENABLE,
         lteSelfConfigParams.isPciSelEnabled);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SON_TX_POWER_ENABLE,
         lteSelfConfigParams.isTxPowerSelEnabled);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_SELFCONFIG_EARFCN_ENABLE,
         lteSelfConfigParams.isEarfcnSelEnabled);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SELFCONFIG_PRACH_ENABLE,
         lteSelfConfigParams.isPrachSelEnabled);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SON_VENDOR,
         lteSelfConfigParams.sonSrvrVendor);
}

void SmApplication::HandleLteSelfConfigParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteSonGenericParams lteSelfConfigParams;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      ReadLteSelfConfigParameters(fapLteDn,lteSelfConfigParams);
      lteSelfConfigParams.actType = MSM_ACT_ADD;
      msmSetSelfConfigParameters(&lteSelfConfigParams,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation\
            will occur after reboot.");
   }
}

void SmApplication::HandleRemScanStatus
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   u32 lteRemScanOnBoot = 0, wcdmaRemScanOnBoot = 0;
   string wcdmaRemScanStatus = "", lteRemScanStatus = "";
   u32 ltePerRemScan = 0, wcdmaPerRemScan = 0;

   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();
   MibDN fapRemUmtsDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA);
   MibDN remDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE);

   if(m_mib.IsMibAttributePresent(remDn,PARAM_ID_LTE_REM_SCAN_ON_BOOT))
   {
      m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_REM_SCAN_ON_BOOT,
            lteRemScanOnBoot);
      TRACE_PRINTF("LTE REM Scan Boot val = %d",lteRemScanOnBoot);
   }
   else
   {
      return;
   }

   if(m_mib.IsMibAttributePresent(fapRemUmtsDn,PARAM_ID_WCDMA_REM_SCAN_ON_BOOT))
   {
      m_mib.GetMibAttribute(fapRemUmtsDn, PARAM_ID_WCDMA_REM_SCAN_ON_BOOT,
            wcdmaRemScanOnBoot);
      TRACE_PRINTF("Wcdma REM Scan on Boot val = %d",wcdmaRemScanOnBoot);
   }
   else
   {
      return;
   }

   if(m_mib.IsMibAttributePresent(remDn,PARAM_ID_LTE_PERIODIC_SCAN_MODE))
   {
      m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_PERIODIC_SCAN_MODE,
            ltePerRemScan);
      TRACE_PRINTF("LTE Periodic REM Scan val = %d",ltePerRemScan);
   }
   else
   {
      return;
   }

   if(m_mib.IsMibAttributePresent(fapRemUmtsDn, PARAM_ID_PERIODIC_SCAN_MODE))
   {
      m_mib.GetMibAttribute(fapRemUmtsDn, PARAM_ID_PERIODIC_SCAN_MODE,
            wcdmaPerRemScan);
      TRACE_PRINTF("Wcdma Periodic REM Scan val = %d",wcdmaPerRemScan);
   }
   else
   {
      return;
   }

   if(m_mib.IsMibAttributePresent(remDn, PARAM_ID_LTE_REM_SCAN_STATUS))
   {
      m_mib.GetMibAttribute(remDn,PARAM_ID_LTE_REM_SCAN_STATUS,
            lteRemScanStatus);
      TRACE_PRINTF("LTE REM Scan Status val = %s",lteRemScanStatus.c_str());
   }
   else 
   {
      return;
   }

   if(m_mib.IsMibAttributePresent(fapRemUmtsDn, PARAM_ID_WCDMA_REM_SCAN_STATUS))
   {
      m_mib.GetMibAttribute(fapRemUmtsDn, PARAM_ID_WCDMA_REM_SCAN_STATUS,
            wcdmaRemScanStatus);
      TRACE_PRINTF("WCDMA REM Scan Status val = %s",wcdmaRemScanStatus.c_str());
   }
   else
   {
      return;
   }

   if (firstTimeConfig == true)
   {
      if(lteRemScanOnBoot) 
      {
         if(lteRemScanStatus == "InProgress" || lteRemScanStatus ==
               "Indeterminate" )
         {
            remScanDone = false;
            TRACE_PRINTF("Initial LTE REM SCAN is either not started or has not\
                  completed");
         }
         else
         {
            remScanDone = true;
            TRACE_PRINTF("Initial LTE REM SCAN is completed");
         }
      }
      if(wcdmaRemScanOnBoot)
      {
         if(wcdmaRemScanStatus == "InProgress" || wcdmaRemScanStatus ==
               "Indeterminate")
         {
            remScanDone = false;
            TRACE_PRINTF("Initial WCDMA REM SCAN is either not started or has\
                  not completed");
         }
         else
         {
            remScanDone = true;
            TRACE_PRINTF("Initial WCDMA REM SCAN is completed");
         }
      }
   }
   else
   {
      if(ltePerRemScan) 
      {
         if(lteRemScanStatus == "InProgress"|| lteRemScanStatus ==
               "Indeterminate")
         {
            remScanDone = false;
            TRACE_PRINTF("Periodic LTE REM SCAN is either not started or has\
                  not completed");
         }
         else
         {
            remScanDone = true;
            TRACE_PRINTF("Periodic LTE REM SCAN is completed");
         }
      }

      if(wcdmaPerRemScan)
      {
         if(wcdmaRemScanStatus == "InProgress"|| wcdmaRemScanStatus ==
               "Indeterminate" )
         {
            remScanDone = false;
            TRACE_PRINTF("Periodic WCDMA REM SCAN is either not started or has\
                  not completed");
         }
         else
         {
            remScanDone = true;
            TRACE_PRINTF("Periodic WCDMA REM SCAN is completed");
         }
      }
   }

   if (isStackStart() == true)
   {
      m_messengerInitialConfigComplete = MSM_TRUE;
      FillNeighCellCfgParameters();
      MsmEnodeBinitialCfgComplete();
   }

   return;
}

bool SmApplication::isStackStart()
{
   u32 adminState = 0;

   GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), 
         PARAM_ID_LTE_FAP_ADMIN_STATE, adminState);

   TRACE_PRINTF("adminState : %d, attrPresent : %d, ipPresent : %d, remScanDone : %d",
         adminState, attrPresent, ipPresent, remScanDone);

   if ((adminState == MSM_TRUE) && (attrPresent == BASIC_CFG_CFGD) && 
         (ipPresent == true) && (remScanDone == true))
   {
      return true;
   }

   return false;
}

void SmApplication::HandleTunnelPlmnId(MsmLteTunnelInfoParams *lteTunnelInfoParams)
{
   TRACE_PRINTF("%s\n",__func__);

   string plmnidvalue,mccvalue,mncvalue;
   u32 plmnidlength = 0;
   u32 idx;

   if ((MSM_TRUE == m_messengerInitialConfigComplete) && (MSM_TRUE == m_smmInitialConfigComplete))/*Oam-Messenger configuration complete and Initial Configuartion Complete*/
   {/*For Dynamic update of Parameters*/
#ifdef DYNUPDATE 
      GetMibCache().GetMibAttributeAsString(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), (MibAttributeId)(PARAM_ID_LTE_TUNNEL_PLMNID), plmnidvalue);
      plmnidlength = plmnidvalue.length(); 

      for(idx = 0; idx < plmnidlength; idx++)
      {
         if(idx < MSM_MAX_MCC_DIGITS)
         {
            mccvalue = plmnidvalue.substr(idx,1);
            lteTunnelInfoParams->tunnelPlmnId.mcc[idx] = u8(atoi(mccvalue.c_str()));
         }
         else
         {
            mncvalue = plmnidvalue.substr(idx,1);
            lteTunnelInfoParams->tunnelPlmnId.mnc[idx-3] = u8(atoi(mncvalue.c_str()));
         }
      }
      lteTunnelInfoParams->tunnelPlmnId.numMncDigits = (plmnidlength - 3);
#endif
   }
   else
   {/*For Initial configuration*/
      GetMibCache().GetMibAttributeAsString(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), (MibAttributeId)(PARAM_ID_LTE_TUNNEL_PLMNID), plmnidvalue);
      plmnidlength = plmnidvalue.length(); 
      for(idx = 0; idx < plmnidlength; idx++)
      {
         if(idx < MSM_MAX_MCC_DIGITS)
         {
            mccvalue = plmnidvalue.substr(idx,1);
            lteTunnelInfoParams->tunnelPlmnId.mcc[idx] = u8(atoi(mccvalue.c_str()));
         }
         else
         {
            mncvalue = plmnidvalue.substr(idx,1);
            lteTunnelInfoParams->tunnelPlmnId.mnc[idx-3] = u8(atoi(mncvalue.c_str()));
         }
      }
      lteTunnelInfoParams->tunnelPlmnId.numMncDigits = (plmnidlength - 3);
   }
   return;
}

void SmApplication::ReadLtePowerOffsetParameters(MibDN fapLteDn,MsmLtePowerOffsetParams &ltePowerOffsetParams)
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> pschPowerOffset, sschPowerOffset, pbchPowerOffset;
   size_t i;

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PSCH_POWER_OFFSET, pschPowerOffset);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(pschPowerOffset);
   ltePowerOffsetParams.pschPowerOffCnt=pschPowerOffset.size();
   for(  i=0;i<ltePowerOffsetParams.pschPowerOffCnt;i++)
   {
      ltePowerOffsetParams.pschPowerOffset[i] = atoi(pschPowerOffset.at(i).c_str());
   }
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_SSCH_POWER_OFFSET, sschPowerOffset);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(sschPowerOffset);
   ltePowerOffsetParams.sschPowerOffCnt=sschPowerOffset.size();
   for( i=0;i<ltePowerOffsetParams.sschPowerOffCnt;i++)
   {
      ltePowerOffsetParams.sschPowerOffset[i] = atoi(sschPowerOffset.at(i).c_str());
   }

   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PBCH_POWER_OFFSET, pbchPowerOffset);
   printf("PARAM_ID_LTE_PB:%s\n", pbchPowerOffset.at(0).c_str());
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(pbchPowerOffset);
   ltePowerOffsetParams.pbchPowerOffCnt=pbchPowerOffset.size();
   for(  i=0;i<ltePowerOffsetParams.pbchPowerOffCnt;i++)
   {
      ltePowerOffsetParams.pbchPowerOffset[i] = atoi(pbchPowerOffset.at(i).c_str());
   }
}

void SmApplication::HandleLtePowerOffsetParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLtePowerOffsetParams ltePowerOffsetParams;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   ReadLtePowerOffsetParameters(fapLteDn,ltePowerOffsetParams);

   if(!isDynCfg)
   {
      ltePowerOffsetParams.actType = MSM_ACT_ADD;
      msmSetPowerOffsetParameters(&ltePowerOffsetParams,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }
}

void SmApplication::HandleLteDynamicCfiParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteDynCfiGrp       lteDynCfiParams;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   if(!isDynCfg)
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_IS_DYNAMIC_CFI_ENABLE, lteDynCfiParams.isDynCfiEnb);
      msmSetDynCfiParameters(&lteDynCfiParams,cellIdx);
   }
   else
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_IS_DYNAMIC_CFI_ENABLE, lteDynCfiParams.isDynCfiEnb);

      MsmSmmDynCfgReq((void*)&lteDynCfiParams, MSM_LTE_DYNAMIC_CFI_PARAMETERS,cellIdx);
   }
   return;
}


void SmApplication::ReadLteCellSchdPowerParameters(MibDN fapLteDn,MsmCellSchdPwrCfg &ltecellSchdPwrCfg)
{
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUCCH_POWER_FORMAT_3_RNTI, ltecellSchdPwrCfg.pucchPwrFmt3Rnti);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUCCH_POWER_FORMAT_3_SIZE, ltecellSchdPwrCfg.pucchPwrFmt3Siz);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUCCH_POWER_FORMAT_3A_RNTI, ltecellSchdPwrCfg.pucchPwrFmt3aRnti);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUCCH_POWER_FORMAT_3A_SIZE, ltecellSchdPwrCfg.pucchPwrFmt3aSiz);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUSCH_POWER_FORMAT_3_RNTI, ltecellSchdPwrCfg.puschPwrFmt3Rnti);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUSCH_POWER_FORMAT_3_SIZE, ltecellSchdPwrCfg.puschPwrFmt3Siz);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUSCH_POWER_FORMAT_3A_RNTI, ltecellSchdPwrCfg.puschPwrFmt3aRnti);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUSCH_POWER_FORMAT_3A_SIZE, ltecellSchdPwrCfg.puschPwrFmt3aSiz);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUCCH_PWR_FMT3A_ENABLE, ltecellSchdPwrCfg.pucchPwrFmt3aEnable);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_PUSCH_PWR_FMT3A_ENABLE, ltecellSchdPwrCfg.puschPwrFmt3aEnable);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_IS_UL_GRP_PWR_CONTROL_PUCCH_ENABLE, ltecellSchdPwrCfg.isUlGrpPwrCntrlPucchEnable);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_IS_UL_GRP_PWR_CONTROL_PUSCH_ENABLE, ltecellSchdPwrCfg.isUlGrpPwrCntrlPuschEnable);

}

void SmApplication::HandleLteCellSchdPowerParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmCellSchdPwrCfg        ltecellSchdPwrCfg;

   MibDN fapLteDn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      ReadLteCellSchdPowerParameters(fapLteDn,ltecellSchdPwrCfg);
      msmSetSchdPwrCfgParameters(&ltecellSchdPwrCfg,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot.");
   }
}

void SmApplication::ReadLteFapControParameters(MibDN fapLteDn,MsmLteFapControlParams &lteFapControlParams)
{
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_CONNECTION_IN_SERVICE_HANDLING,lteFapControlParams.connHandling);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_CAPACITY_USER_ACCOUNT,lteFapControlParams.maxUserCount);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_MAX_CAPACITY_RATE,lteFapControlParams.maxCapacityRate);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_HANDOVER_ON_EMERGENCY,lteFapControlParams.handOverEmergencyAllowed);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_FAP_COVERAGE_TARGET,lteFapControlParams.fapCoverageTarget);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_SERVICE_HANDLING_DEFERRED_TIMER,lteFapControlParams.inServiceDeferredTimer);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_MIN_RB_ALLOCATION_USER,lteFapControlParams.minRBAllocationPerUser);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ENABLE_X2,lteFapControlParams.enableX2);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ANR_EPOCH_PERIOD,lteFapControlParams.anrEpochPeriod);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ANR_TRICE_PERIOD,lteFapControlParams.anrTricePeriod);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ANR_CELL_VALID_AGE, lteFapControlParams.anrCellValidAge);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ANR_DRX_LONG_CYCLE ,lteFapControlParams.anrDrxLongCycle);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ANR_DRX_ON_DURATION_TMR,lteFapControlParams.anrDrxOnDurTmr);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_ANR_DRX_INACTIVITY_TMR,lteFapControlParams.anrDrxInactvTmr);
   GetMibCache().GetMibAttribute(fapLteDn,PARAM_ID_LTE_SPECIAL_ACCESS_CLASS,lteFapControlParams.specialAccessClass);

}

void SmApplication::HandleLteFapControParameters(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteFapControlParams lteFapControlParams;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   if(!isDynCfg)
   {
      lteFapControlParams.actType = MSM_ACT_ADD;
      ReadLteFapControParameters(fapLteDn,lteFapControlParams);

      msmSetFapControlParameters(&lteFapControlParams,cellIdx);
   }
   else
   {
      TRACE_PRINTF("%s:%d Failed to set FAP control configuration",__func__,__LINE__);
   }
}

void SmApplication::ReadLteSctpConfigParameters
(
 MibDN fapLteDn,
 MsmLteSctpCfgParams &lteSctpCfgParams
 )
{
   u32 valueu32; 
   std::vector<std::string> sctpLocalPort;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_HRTBEAT_INTERVAL,
         valueu32);
   lteSctpCfgParams.heartBeatInterval = (unsigned long)valueu32 * 1000;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_RTO_INITIAL,
         valueu32);
   lteSctpCfgParams.rtoInitial = (unsigned long)valueu32;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_RTO_MIN, valueu32);
   lteSctpCfgParams.rtoMin = (unsigned long)valueu32;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_RTO_MAX, valueu32);
   lteSctpCfgParams.rtoMax = (unsigned long)valueu32;
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_MAX_ASSOC_RETX,
         lteSctpCfgParams.maxAssocRetx);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_MAX_INIT_RETX,
         lteSctpCfgParams.maxInitRetx);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_MAX_PATH_RETX,
         lteSctpCfgParams.maxPathRetx);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_SCTP_COOKIE_LIFE,
         lteSctpCfgParams.cookieLife);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X_RADISYS_LOCAL_PORT,
         sctpLocalPort);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(
         sctpLocalPort);

   u32 numPorts = sctpLocalPort.size();
   if(1 == numPorts)
   {
      lteSctpCfgParams.localPort = atoi(sctpLocalPort.at(0).c_str());
   }
   else
   {
      lteSctpCfgParams.localPort = (getRandomVal() % (atoi(sctpLocalPort.
                  at(numPorts - 1).c_str()) - atoi(sctpLocalPort.at(0).c_str())
               + 1) + atoi(sctpLocalPort.at(0).c_str()));
   }

}

void SmApplication::HandleLteSctpConfigParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteSctpCfgParams lteSctpCfgParams;

   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   if(!isDynCfg) 
   {
      lteSctpCfgParams.actType = MSM_ACT_ADD;
      ReadLteSctpConfigParameters(fapDn, lteSctpCfgParams);
      msmSetSctpConfigParameters(&lteSctpCfgParams, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation \
            will occur after reboot\n");
   }

   return;
}
void SmApplication::ReadHandleLteCellUlSchdCfgGrpParameters
(
 MibDN fapLteDn,
 MsmLteCellUlSchdCfgGrp &lteCellUlSchdCfgGrp
 )
{
   u32 valueu32; 
   std::vector<u32>       lteUlQciWgtList;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_MAX_UL_TX_RX_UE_PER_TTI,
         lteCellUlSchdCfgGrp.maxUePerUlSf); 
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_MAX_UL_TX_UE_PER_TTI,
         lteCellUlSchdCfgGrp.maxUlUeNewTxPerTti); 
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PFS_UL_TPT_COEFFICIENT,
         lteCellUlSchdCfgGrp.pfsUlTptCoefficient); 
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_PFS_UL_FAIRNESS_COEFFICIENT,
         lteCellUlSchdCfgGrp.pfsUlFairCoefficient); 
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_UL_SCHD_TYPE, valueu32);
   lteCellUlSchdCfgGrp.ulSchedulingAlg = (unsigned long)valueu32;

   u32 lteUlQciWgtListSize= 0;

   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_UL_QCI_SCHD_WGT,
         lteUlQciWgtList);
   lteUlQciWgtListSize = lteUlQciWgtList.size();

   for(size_t idx = 0; idx < lteUlQciWgtListSize; idx++)
   {
      lteCellUlSchdCfgGrp.ulQciWgtList[idx] = lteUlQciWgtList[idx];
   }
}

void SmApplication::HandleLteCellUlSchdCfgGrpParameters
(
 u16 cellIdx,
 bool isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteCellUlSchdCfgGrp lteCellUlSchdCfgGrp;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   if(!isDynCfg)
   {
      lteCellUlSchdCfgGrp.actType = MSM_ACT_ADD;
      ReadHandleLteCellUlSchdCfgGrpParameters(fapLteDn, lteCellUlSchdCfgGrp);
      msmSetCellUlSchdConfigParameters(&lteCellUlSchdCfgGrp, cellIdx);
   }
   else 
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot\n");
   }
   return;
}

void SmApplication::HandleLtePRBallocationParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> plmnidList;
   string plmnidvalue,mccvalue,mncvalue;
   u32 plmnidlength = 0;
   u32 index;
   u32 idx;
   MsmLtePRBallocation ltePRBallocation;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   if(!isDynCfg)
   {
      ltePRBallocation.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PRB_ALLOCATION_PLMN, 
            plmnidList);
      for(index = 0; index < plmnidList.size(); index++)
      {
         plmnidvalue = plmnidList.at(index).c_str();
         plmnidlength = plmnidvalue.length(); 

         for(idx = 0; idx < plmnidlength; idx++)
         {
            if(idx < MSM_MAX_MCC_DIGITS)
            {
               mccvalue = plmnidvalue.substr(idx,1);
               ltePRBallocation.plmns[index].mcc[idx] = u8(atoi(mccvalue.c_str()));
            }
            else
            {
               mncvalue = plmnidvalue.substr(idx,1);
               ltePRBallocation.plmns[index].mnc[idx-3] = u8(atoi(mncvalue.c_str()));
            }

            ltePRBallocation.plmns[index].numMncDigits = (plmnidlength - 3);
         }
      }
      msmSetPrbAllocationParameters(&ltePRBallocation, cellIdx);
   }
   else 
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameter updation will occur after reboot\n");
   }
   return;
}

void SmApplication::HandleLteCellDlSchdCfgGrpParameters
(
 u16 cellIdx,
 bool isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      MsmLteCellDlSchdCfgGrp lteCellDlSchdCfgGrp;
      std::vector<u32> lteDlQciWgtList;
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      lteCellDlSchdCfgGrp.actType = MSM_ACT_ADD;

      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_MAX_DL_TX_RX_UE_PER_TTI,
            lteCellDlSchdCfgGrp.maxUePerDlSf); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_MAX_DL_TX_UE_PER_TTI,
            lteCellDlSchdCfgGrp.maxDlUeNewTxPerTti); 
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_PFS_DL_TPT_COEFFICIENT,
            lteCellDlSchdCfgGrp.pfsDlTptCoefficient); 
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_PFS_DL_FAIRNESS_COEFFICIENT,
            lteCellDlSchdCfgGrp.pfsDlFairCoefficient); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DLFSS_ENABLE,
            lteCellDlSchdCfgGrp.dlfsSchd);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DL_SCHD_TYPE,
            lteCellDlSchdCfgGrp.dlSchedulingAlg);

      u32 lteDlQciWgtListSize = 0;

      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_DL_QCI_SCHD_WGT,
            lteDlQciWgtList);
      lteDlQciWgtListSize = lteDlQciWgtList.size();

      for(size_t idx = 0; idx < lteDlQciWgtListSize; idx++)
      {
         lteCellDlSchdCfgGrp.dlQciWgtList[idx] = lteDlQciWgtList[idx];
      }

      msmSetCellDlSchdConfigParameters(&lteCellDlSchdCfgGrp, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }

   return;
}

void SmApplication::HandleLteMsCellCfgReqParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      u32 valueu32; 
      MsmLteMsCellCfgReq lteMsCellCfgReq;
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      lteMsCellCfgReq.actType = MSM_ACT_ADD;

      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_OP_MODE,
            lteMsCellCfgReq.opMode); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_PERIOD, valueu32);
      lteMsCellCfgReq.period = (unsigned long)valueu32;
      msmSetMsCellCfgReqParameters(&lteMsCellCfgReq, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void  SmApplication::ReadLteRrmTddParameters(MibDN fapLteDn, MsmLteRrmTddParam &lteRrmTddParam)
{
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_RRM_SR_PRDCTY, lteRrmTddParam.srPrdcty);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_RRM_CQI_PRDCTY, lteRrmTddParam.cqiPrdcty);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_RRM_NUM_SR_PER_TTI, lteRrmTddParam.numSrPerTti);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_RRM_NUM_CQI_PER_TTI, lteRrmTddParam.numCqiPerTti); 
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_RRM_SIMUL_ACK_NACK_ENB, lteRrmTddParam.simulAckNackEnb);
}

void SmApplication::HandleLteRrmTddParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteRrmTddParam lteRrmTddParam;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   if(!isDynCfg)
   {
      lteRrmTddParam.actType = MSM_ACT_ADD;
      ReadLteRrmTddParameters(fapLteDn, lteRrmTddParam);

      msmSetRrmTddParameters(&lteRrmTddParam, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
}

void SmApplication::fillLteDbgParameters(MsmLteDbgParams &lteDbgParams)
{
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_TUCL_DBG, lteDbgParams.hiDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_SCTP_DBG, lteDbgParams.sbDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_S1AP_DBG, lteDbgParams.szDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_EGTP_DBG, lteDbgParams.egDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_RRC_APP_DBG, lteDbgParams.wrDbg);
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_RRC_DBG, lteDbgParams.nhDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_RLC_PDCP_DBG,lteDbgParams.kwDbg);
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_MAC_DBG, lteDbgParams.rgDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_CL_DBG, lteDbgParams.ysDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_SM_DBG, lteDbgParams.smDbg); 
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_X2AP_DBG, lteDbgParams.czDbg);  
}
void SmApplication::HandleLteDbgParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteDbgParams lteDbgParams;

   fillLteDbgParameters(lteDbgParams);

   if(!isDynCfg)
   {
      lteDbgParams.actType = MSM_ACT_ADD;
      msmSetDbgParameters(&lteDbgParams);
   }
   else
   {
      lteDbgParams.actType = MSM_ACT_MOD;

      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteDbgParams, MSM_LTE_DBG_PARAMETERS, 0);
   }
   return;
}

void SmApplication::HandleLteUlAllocInfoCbParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      MsmLteUlAllocInfoCbParams lteUlAllocInfoCbParams;
      lteUlAllocInfoCbParams.actType = MSM_ACT_ADD;
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_UL_MCS_VAL,
            lteUlAllocInfoCbParams.mcs); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_UL_NUM_RB_VAL,
            lteUlAllocInfoCbParams.numOfRb); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_UL_RB_START_VAL,
            lteUlAllocInfoCbParams.rbStart); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_UL_ENABLE_TIME,
            lteUlAllocInfoCbParams.logTime);

      msmSetUlAllocInfoCbParameters(&lteUlAllocInfoCbParams, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void SmApplication::HandleLteProcTimerCfgParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      u32 valueu32; 
      MsmLteProcTimerCfg lteProcTimerCfg;
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      lteProcTimerCfg.actType = MSM_ACT_ADD;

      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_S1RESET_TIME,
            lteProcTimerCfg.s1ResetTmr); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X2RESET_TIME,
            lteProcTimerCfg.x2ResetTmr); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_S1_PREP_TMR,
            lteProcTimerCfg.s1PrepTimerVal); 
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_S1_OVRALL_TMR,
            lteProcTimerCfg.s1OvrAllTimerVal);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X2_PREP_TMR,
            lteProcTimerCfg.x2PrepTimerVal);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X2_OVRALL_TMR,
            lteProcTimerCfg.x2OvrAllTimerVal);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_IRAT_TS1_RELOC_PREP_TMR,
            lteProcTimerCfg.s1RATPrepTimerVal);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_IRAT_TS1_RELOC_OVRALL_TMR,
            lteProcTimerCfg.s1RATOvrAllTimerVal);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_HO_CANCEL_ACK_TMR,
            lteProcTimerCfg.s1HandoverCancelTmr);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_X2_TIME_TO_WAIT,
            valueu32);
      lteProcTimerCfg.x2TimeToWaitTimerVal = (unsigned long)valueu32;

      msmSetProcTimerCfgParameters(&lteProcTimerCfg, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void SmApplication::HandleLtePlmnId(MsmLtePlmnId *plmnId, u32 index, string plmnIdParameter)
{
   TRACE_PRINTF("index=%d,%s\n",index,__func__);

   std::vector<std::string> plmnidList;
   string plmnidvalue,mccvalue,mncvalue;
   u32 plmnidlength = 0;
   u32 idx;

   if ((MSM_TRUE == m_messengerInitialConfigComplete) && (MSM_TRUE == m_smmInitialConfigComplete))/*Oam-Messenger configuration complete and Initial Configuartion Complete*/
   {/*For Dynamic update of Parameters*/
#ifdef DYNUPDATE 
      if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
      {
         GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID, plmnidList);
      }else
      {
         GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID, plmnidList);		
      }
      plmnidvalue = plmnidList.at(index).c_str();
      plmnidlength = plmnidvalue.length(); 

      for(idx = 0; idx < plmnidlength; idx++)
      {
         if(idx < MSM_MAX_MCC_DIGITS)
         {
            mccvalue = plmnidvalue.substr(idx,1);
            plmnId->mcc[idx] = u8(atoi(mccvalue.c_str()));
         }
         else
         {
            mncvalue = plmnidvalue.substr(idx,1);
            plmnId->mnc[idx-3] = u8(atoi(mncvalue.c_str()));
         }
      }
      plmnId->numMncDigits = (plmnidlength - 3);
#endif
   }
   else
   {/*For Initial configuration*/
      if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
      {
         GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID, plmnidList);
      }else
      {
         GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID, plmnidList);
      }
      plmnidvalue = plmnidList.at(index).c_str();
      plmnidlength = plmnidvalue.length(); 
      for(idx = 0; idx < plmnidlength; idx++)
      {
         if(idx < MSM_MAX_MCC_DIGITS)
         {
            mccvalue = plmnidvalue.substr(idx,1);
            plmnId->mcc[idx] = u8(atoi(mccvalue.c_str()));
         }
         else
         {
            mncvalue = plmnidvalue.substr(idx,1);
            plmnId->mnc[idx-3] = u8(atoi(mncvalue.c_str()));
         }
      }
      plmnId->numMncDigits = (plmnidlength - 3);
   }
   return;
}

void SmApplication::HandleLtePlmnIdList(MsmNeighCellCfg *lteNeighCellCfg, u32 index, u32 numcells, string plmnIdParameter)
{
   TRACE_PRINTF("%s\n",__func__);

   string plmnidvalue,mccvalue,mncvalue;
   u32 plmnidlength = 0;
   std::vector<std::string> plmnidList;
   u32 idx, idxlist;


   if ((MSM_TRUE == m_messengerInitialConfigComplete) && (MSM_TRUE == m_smmInitialConfigComplete))/*Oam-Messenger configuration complete and Initial Configuartion Complete*/
   {
#ifdef DYNUPDATE 
      for(idxlist = 0; idxlist < numcells; idxlist++)
      {
         if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
         {
            GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID, plmnidList);
         }else
         {
            GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID, plmnidList);		
         }
         plmnidvalue = plmnidList.at(idxlist).c_str();
         plmnidlength = plmnidvalue.length();

         for(idx = 0; idx < plmnidlength; idx++)
         {
            if(idx < MSM_MAX_MCC_DIGITS)
            {
               mccvalue = plmnidvalue.substr(idx,1);
               if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
               {
                  lteNeighCellCfg->t.neighAddCfg[index].eutraCell.plmnId[idxlist].mcc[idx] = u8(atoi(mccvalue.c_str()));
               }else
               {
                  lteNeighCellCfg->t.neighAddCfg[index].utranCell.plmnId[idxlist].mcc[idx] = u8(atoi(mccvalue.c_str()));
               }
            }
            else
            {
               mncvalue = plmnidvalue.substr(idx,1);
               if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
               {
                  lteNeighCellCfg->t.neighAddCfg[index].eutraCell.plmnId[idxlist].mnc[idx-3] = u8(atoi(mncvalue.c_str()));
               }else
               {
                  lteNeighCellCfg->t.neighAddCfg[index].utranCell.plmnId[idxlist].mnc[idx-3] = u8(atoi(mncvalue.c_str()));			
               }
            }
         }
         if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
         {
            lteNeighCellCfg->t.neighAddCfg[index].eutraCell.plmnId[idxlist].numMncDigits = (plmnidlength - 3);
         }else
         {
            lteNeighCellCfg->t.neighAddCfg[index].utranCell.plmnId[idxlist].numMncDigits = (plmnidlength - 3);						
         }
         lteNeighCellCfg->t.neighAddCfg[index].utranCell.numPlmn = 1;
      }
#endif
   }
   else
   {/*For Initial configuration*/
      for(idxlist = 0; idxlist < numcells; idxlist++)
      {
         if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
         {
            GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID, plmnidList);
         }else
         {
            GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID, plmnidList);
         }
         plmnidvalue = plmnidList.at(idxlist).c_str();
         plmnidlength = plmnidvalue.length();

         for(idx = 0; idx < plmnidlength; idx++)
         {
            if(idx < MSM_MAX_MCC_DIGITS)
            {
               mccvalue = plmnidvalue.substr(idx,1);
               if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
               {
                  lteNeighCellCfg->t.neighAddCfg[index].eutraCell.plmnId[idxlist].mcc[idx] = u8(atoi(mccvalue.c_str()));
               }else
               {
                  lteNeighCellCfg->t.neighAddCfg[index].utranCell.plmnId[idxlist].mcc[idx] = u8(atoi(mccvalue.c_str()));
               }
            }
            else
            {
               mncvalue = plmnidvalue.substr(idx,1);
               if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
               {
                  lteNeighCellCfg->t.neighAddCfg[index].eutraCell.plmnId[idxlist].mnc[idx-3] = u8(atoi(mncvalue.c_str()));
               }else
               {
                  lteNeighCellCfg->t.neighAddCfg[index].utranCell.plmnId[idxlist].mnc[idx-3] = u8(atoi(mncvalue.c_str()));
               }
            }
         }
         if(strcmp(plmnIdParameter.c_str(),"PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID") == 0)
         {
            lteNeighCellCfg->t.neighAddCfg[index].eutraCell.plmnId[idxlist].numMncDigits = (plmnidlength - 3);
         }else
         {
            lteNeighCellCfg->t.neighAddCfg[index].utranCell.plmnId[idxlist].numMncDigits = (plmnidlength - 3);
         }
         lteNeighCellCfg->t.neighAddCfg[index].utranCell.numPlmn = 1;
      }
   }
   return;
}

void SmApplication::HandleEnodebIPAddress(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   string siglinkserver,enbipv6addr;
   IPv4Address enbIp;
   IPv6Address enbIpv6;
   u32 sigip =0;
   u8 sigipv6[16]={0};
   char ipbuf[150]; 
   MsmEnodebIpAddr lteEnodebIpAddr;
   static bool changeDueToIPSec = FALSE;

   if(MSM_TRUE == SmApplication::s_adminFlag)
   {
      SmApplication::GetInstance().startAdminFlagTimer(100);
      TRACE_PRINTF("%s waiting for Ack",__func__);
      callBackTo=IP_CHANGE;
      return;
   }

   TRACE_PRINTF("%s Proceeding ",__func__);
   GetMibCache().GetMibAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, siglinkserver);
   GetMibCache().GetMibAttribute(PARAM_ID_ENB_IP_ADDR_IPV6, enbipv6addr);
   if((siglinkserver.c_str() != NULL) && (strcmp(siglinkserver.c_str(),"0.0.0.0")))
   {
      ipPresent = true;
      enbIp = IPv4Address(siglinkserver.c_str());
      sigip = htonl(enbIp.Get());
      lteEnodebIpAddr.enbIpAddr = sigip;
      lteEnodebIpAddr.ipv4pres = TRUE;
   }
   if(IsIpSet(enbipv6addr))
   {
      TRACE_PRINTF("ENB IPV6 ADDRESS =  %s",enbipv6addr.c_str());
      enbIpv6.Set(enbipv6addr.c_str());
      if(! enbIpv6.Get(sigipv6))
      {
         TRACE_PRINTF("Retrieval of IPV6 Failed");
         return;
      }
      else
      {
         sprintf(ipbuf,"%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x",sigipv6[0],sigipv6[1],sigipv6[2],sigipv6[3],sigipv6[4],sigipv6[5],sigipv6[6],sigipv6[7],sigipv6[8],sigipv6[9],sigipv6[10],sigipv6[11],sigipv6[12],sigipv6[13],sigipv6[14],sigipv6[15]);
         TRACE_PRINTF("**** eNodeB IPV6 %s\n",ipbuf);
      }
      memcpy(&lteEnodebIpAddr.enbIpv6Addr,&sigipv6,sizeof(sigipv6));
      lteEnodebIpAddr.ipv6pres = TRUE;
      ipPresent = true;
   }
   else
   {
      lteEnodebIpAddr.ipv6pres = FALSE;
   }

   if ((0xffffffff == sigip) || (0x7f000001 == sigip))
   {
      SmApplication::adminDownFlagSet();
      changeDueToIPSec = TRUE;
      if(MSM_TRUE == m_adminState)
      {
         m_adminState = MSM_FALSE;
         MsmStartStopStackReq(MSM_FALSE,MSM_FALSE,MSM_FALSE);
      }
      return;
   }

   if (MSM_TRUE == m_messengerInitialConfigComplete)/*Oam-Messenger configuration complete*/
   {
#ifdef DYNUPDATE 
      if ((MSM_TRUE == m_smmInitialConfigComplete) && (m_smmWaitForDynCfgRsp == FALSE))
      {
         lteEnodebIpAddr.enbIpAddr = (unsigned long)sigip;
         m_smmWaitForDynCfgRsp = TRUE;
         MsmSmmDynCfgReq((void*)&lteEnodebIpAddr, MSM_ENB_IP_ADDRESS, 0);
         if (changeDueToIPSec == TRUE)
         {
            changeDueToIPSec = FALSE;
            MsmStartStopStackReq(MSM_FALSE,MSM_TRUE,MSM_FALSE);
         }
      }		
      else
      {
         m_dynupdate.push(MSM_ENB_IP_ADDRESS);
      }
#endif
   }
   else
   {
      msmSetEnodebIpAddr(&lteEnodebIpAddr);

      if ((isStackStart() == true) && (!m_messengerInitialConfigComplete))
      {
         m_messengerInitialConfigComplete = MSM_TRUE;
         TRACE_PRINTF("TRACE m_messengerInitialConfigComplete calling from %s",__func__);
         FillNeighCellCfgParameters();
         MsmEnodeBinitialCfgComplete();
      }
   }
   return;
}

void SmApplication::HandleGostCfgParams(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {

      MsmGostLog lteGostLog;
      u8 idx;
     string ipAddress;
    GetMibCache().GetMibAttribute(PARAM_ID_LTE_RRC_LOG_ENABLE, lteGostLog.rrcLogEnable);
    GetMibCache().GetMibAttribute(PARAM_ID_LTE_GOST_IP_PORT, lteGostLog.portNumber);
    GetMibCache().GetMibAttribute(PARAM_ID_LTE_GOST_IP,ipAddress);
    for(idx=0;idx<ipAddress.length();idx++)
    {
       lteGostLog.ipAddress[idx]=ipAddress.at(idx);
    }
    lteGostLog.ipAddress[idx]='\0';
    printf("\n in OAM ipAddress =%s\n",lteGostLog.ipAddress);
    printf("\n in OAM ipAddress =%d\n",lteGostLog.portNumber);
    /*shivani*/
#if 0
    strcpy(lteGostLog.ipAddress,ipAddress.c_str());
    printf("\n in OAM ipAddress =%s\n",lteGostLog.ipAddress);
#endif
    msmSetGostLog(&lteGostLog);
   }


}


void SmApplication::startAdminFlagTimer(u32 timeOutPeriod)
{
   if(IsTimerRunning(m_adminFlagTimer))
   {
      DeleteTimer(m_adminFlagTimer);
   }
   m_adminFlagTimer = CreateTimer((const std::string&)"Admin state flag timer timeout", u32(10), TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void SmApplication::HandlePerfMgmtParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      u32 idx;
      string collectionMethod;
      MsmPerfMgmtParameters perfMgmtParameters;

      perfMgmtParameters.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(PARAM_ID_PM_COLLECTION_METHOD, collectionMethod);
      for(idx=0;idx < collectionMethod.length();idx++)
      {
         perfMgmtParameters.collectionMethodForPM[idx] = collectionMethod[idx];
      }	
      GetMibCache().GetMibAttribute(PARAM_ID_PM_L2_COLLECTION_ENA, perfMgmtParameters.l2PMCollectionEnable);
      msmSetPmParameters(&perfMgmtParameters);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }

   return;
}

void SmApplication::HandleFrequentFaultMgmtParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      MsmFrequentFaultMgmtParameters frequentFaultMgmtParameters;

      frequentFaultMgmtParameters.actType = MSM_ACT_ADD;
      GetMibCache().GetMibAttribute(PARAM_ID_MAX_S1ERROR_IND_COUNT, frequentFaultMgmtParameters.maxS1ErrIndCnt);
      GetMibCache().GetMibAttribute(PARAM_ID_MIN_S1ERROR_IND_TIME, frequentFaultMgmtParameters.minS1ErrIndTime);
      GetMibCache().GetMibAttribute(PARAM_ID_MAX_S1RESET_COUNT, frequentFaultMgmtParameters.maxS1ResetCnt);
      GetMibCache().GetMibAttribute(PARAM_ID_MIN_S1RESET_TIME, frequentFaultMgmtParameters.minS1ResetTime);
      GetMibCache().GetMibAttribute(PARAM_ID_MAX_X2ERROR_IND_COUNT, frequentFaultMgmtParameters.maxX2ErrIndCnt);
      GetMibCache().GetMibAttribute(PARAM_ID_MIN_X2ERROR_IND_TIME, frequentFaultMgmtParameters.minX2ErrIndTime);
      GetMibCache().GetMibAttribute(PARAM_ID_MAX_X2RESET_COUNT, frequentFaultMgmtParameters.maxX2ResetCnt);
      GetMibCache().GetMibAttribute(PARAM_ID_MIN_X2RESET_TIME, frequentFaultMgmtParameters.minX2ResetTime);
      msmSetFrequentFaultParameters(&frequentFaultMgmtParameters);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void SmApplication::HandleLteDynamicConfiguration()
{
   TRACE_PRINTF("%s\n",__func__);

   u16 dynupdatevalue;/*This flag is used during dynamic updates*/

   if (firstTimeConfig == true)
   {
      firstTimeConfig = false;
      PeriodicRemHandler();
   }

   m_PeriodicRemScanInProg = false;

   while(!m_dynupdate.empty())
   {
      dynupdatevalue = m_dynupdate.front();
      m_dynupdate.pop();
      HandleLteSubscriptions(dynupdatevalue); 
   }
   return;
}

void SmApplication::FillCdmaBandClassParameters(u16 cellIdx)
{
   TRACE_PRINTF("%s\n",__func__);

   u16 idx;
   std::vector<u32> bandClass;
   std::vector<u32> cellReselectPrior;
   std::vector<u32> threshXHigh;
   std::vector<u32> threshXLow;
   std::vector<s32> cdmaType;
   MsmCdmaBandClass cdmaBandClass;
   cdmaBandClass.actType = MSM_ACT_ADD;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_MAX_CDMA2K_BAND, cdmaBandClass.maxBandClass); 
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_NUM_CDMA2K_BAND, cdmaBandClass.numBandClass);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_BAND_CLASS, bandClass);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_CELL_RESEL_PRIOR, cellReselectPrior);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_THRESH_X_LOW, threshXHigh);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_THRESH_X_HIGH, threshXLow);

   for(idx = 0; idx < cdmaBandClass.numBandClass &&
         cdmaBandClass.numBandClass <= cdmaBandClass.maxBandClass; idx++)
   {
      cdmaBandClass.t.bandClassAddCfg[idx].t.bandClass1XRtt.bandClass
         = bandClass[idx];
      cdmaBandClass.t.bandClassAddCfg[idx].t.bandClass1XRtt.cellReselectPrior
         = cellReselectPrior[idx];
      cdmaBandClass.t.bandClassAddCfg[idx].t.bandClass1XRtt.threshXHigh
         = threshXHigh[idx];
      cdmaBandClass.t.bandClassAddCfg[idx].t.bandClass1XRtt.threshXLow
         = threshXLow[idx];
   }
   msmSetCdmaBandClassParameters(&cdmaBandClass, cellIdx);
   return; 
}

void SmApplication::HandleCdmaMobilityParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   if(!isDynCfg)
   {
      MsmCdmaMobilityParam cdmaMobilityParam;
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
      cdmaMobilityParam.actType = MSM_ACT_ADD;

      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SID_INCL,
            cdmaMobilityParam.sidIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SID,
            cdmaMobilityParam.sid);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NID_INCL,
            cdmaMobilityParam.nidIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NID,
            cdmaMobilityParam.nid);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MULT_SID_INCL,
            cdmaMobilityParam.multSidsIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MULT_SID,
            cdmaMobilityParam.multSids);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MULT_NID_INCL,
            cdmaMobilityParam.multNidsIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MULT_NID,
            cdmaMobilityParam.multNids);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_REG_ZONE_INCL,
            cdmaMobilityParam.regZoneIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_REG_ZONE,
            cdmaMobilityParam.regZone);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_TOTAL_ZONE_INCL,
            cdmaMobilityParam.totalZonesIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_TOTAL_ZONE,
            cdmaMobilityParam.totalZones);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_ZONE_TIMER_INCL,
            cdmaMobilityParam.zoneTimerIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ZONE_TIMER,
            cdmaMobilityParam.zoneTimer);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PKT_ZONE_ID_INCL,
            cdmaMobilityParam.pktZoneIdIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PKT_ZONE_ID,
            cdmaMobilityParam.pktZoneId);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_ID_HYS_PARAM_INCL,
            cdmaMobilityParam.pzIdHysParamIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_HYST_ENABLE,
            cdmaMobilityParam.pzHystEnabled);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_HYST_INFO_INCL,
            cdmaMobilityParam.pzHystInfoIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_HYST_LIST_LEN,
            cdmaMobilityParam.pzHystListLen);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_HYST_ACT_TIMER,
            cdmaMobilityParam.pzHystActTimer);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_HYST_TIMER_MUL,
            cdmaMobilityParam.pzHystTimerMul);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PZ_HYST_TIMER_EXP,
            cdmaMobilityParam.pzHystTimerExp);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PREV_INCL,
            cdmaMobilityParam.pRevIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PREV,
            cdmaMobilityParam.pRev);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MIN_PREV_INCL,
            cdmaMobilityParam.minPRevIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MIN_PREV,
            cdmaMobilityParam.minPRev);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_NEG_SLOT_CYC_IDX_SUP_INCL,
            cdmaMobilityParam.negSlotCycIndxSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_NEG_SLOT_CYC_IDX_SUP,
            cdmaMobilityParam.negSlotCycIndxSup);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ENC_MOD_INCL,
            cdmaMobilityParam.encModeIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ENC_MODE,
            cdmaMobilityParam.encMode);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ENC_SUP_INCL,
            cdmaMobilityParam.encSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ENC_SUP,
            cdmaMobilityParam.encSup);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_SIG_ENC_SUP_INCL,
            cdmaMobilityParam.sigEncSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SIG_ENC_SUP,
            cdmaMobilityParam.sigEncSup);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MSG_INT_SUP_INCL,
            cdmaMobilityParam.msgIntSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MSG_INT_SUP,
            cdmaMobilityParam.msgIntSup);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_SIG_INT_SUP_IND_INCL,
            cdmaMobilityParam.sigIntSupINCLIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_SIG_INT_SUP_IND,
            cdmaMobilityParam.sigIntSupINCLIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_SIG_INT_SUP_INCL,
            cdmaMobilityParam.sigIntSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SIG_INT_SUP,
            cdmaMobilityParam.sigIntSup);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_AUTH_INCL,
            cdmaMobilityParam.authIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_AUTH,
            cdmaMobilityParam.auth);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MAX_NUM_ALT_SER_INCL,
            cdmaMobilityParam.maxNumAltoSoIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MAX_NUM_ALT_SER,
            cdmaMobilityParam.maxNumAltoSo);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_USE_SYNC_ID_INCL,
            cdmaMobilityParam.useSyncIdIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_USE_SYNC_ID,
            cdmaMobilityParam.useSyncId);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MS_INIT_POS_LOC_SUP_IND_INCL,
            cdmaMobilityParam.msInitPosLocSupIndIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MS_INIT_POS_LOC_SUP_IND,
            cdmaMobilityParam.msInitPosLocSupInd);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MOB_QOS_INCL,
            cdmaMobilityParam.mobQosIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MOB_QOS,
            cdmaMobilityParam.mobQos);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_BAND_CLS_INFO_REQ_INCL,
            cdmaMobilityParam.bandClsInfoReqIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_BAND_CLS_INFO_REQ,
            cdmaMobilityParam.bandClsInfoReq);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_BAND_CLS_INCL,
            cdmaMobilityParam.bandClsIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_BAND_CLS,
            cdmaMobilityParam.bandCls);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_BY_PASS_REG_IND_INCL,
            cdmaMobilityParam.bypassRegIndIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_BY_PASS_REG_IND,
            cdmaMobilityParam.bypassRegInd);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_ALT_BND_CLS_INCL,
            cdmaMobilityParam.altBandClsIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ALT_BND_CLS,
            cdmaMobilityParam.altBandCls);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MAX_ADD_SERV_INST_INCL,
            cdmaMobilityParam.maxAddServInstIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MAX_ADD_SERV_INST,
            cdmaMobilityParam.maxAddServInst);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_HOME_REG_INCL,
            cdmaMobilityParam.homeRegIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_HOME_REG,
            cdmaMobilityParam.homeReg);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SID_REG_INCL,
            cdmaMobilityParam.forSidRegIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SID_REG,
            cdmaMobilityParam.forSidReg);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NID_REG_INCL,
            cdmaMobilityParam.forNidRegIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NID_REG,
            cdmaMobilityParam.forNidReg);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PWR_UP_REG_INCL,
            cdmaMobilityParam.powerUpRegIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PWR_UP_REG,
            cdmaMobilityParam.powerUpReg);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PWR_DOWN_REG_INCL,
            cdmaMobilityParam.powerDownRegIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PWR_DOWN_REG,
            cdmaMobilityParam.powerDownReg);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PARAM_REG_INCL,
            cdmaMobilityParam.parmRegIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PARAM_REG,
            cdmaMobilityParam.parmReg);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_REG_PRD_INCL,
            cdmaMobilityParam.regPrdIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_REG_PRD,
            cdmaMobilityParam.regPrd);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_REG_DIST_INCL,
            cdmaMobilityParam.regDistIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_REG_DIST,
            cdmaMobilityParam.regDist);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PREF_MSID_TYPE_INCL,
            cdmaMobilityParam.prefMsIdTypeIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PREF_MSID_TYPE,
            cdmaMobilityParam.prefMsIdType);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_EXT_PREF_MSID_TYPE_INCL,
            cdmaMobilityParam.extPrefMsIdTypeIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_EXT_PREF_MSID_TYPE,
            cdmaMobilityParam.extPrefMsIdType);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_MEID_REQD_INCL,
            cdmaMobilityParam.meIdReqdIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MEID_REQD,
            cdmaMobilityParam.meIdReqd);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MRCC_INCL,
            cdmaMobilityParam.mccIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_MCC,
            cdmaMobilityParam.mcc);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_IMSI_11_12_INCL,
            cdmaMobilityParam.imsi1112Incl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_IMSI_11_12,
            cdmaMobilityParam.imsi1112);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_IMSI_TSUP_INCL,
            cdmaMobilityParam.imsiTSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_IMSI_TSUP,
            cdmaMobilityParam.imsiTSup);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_RE_CON_MSG_IND_INCL,
            cdmaMobilityParam.recntMsgIndIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_RE_CON_MSG_IND,
            cdmaMobilityParam.recntMsgInd);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_RER_MOD_SUP_INCL,
            cdmaMobilityParam.rerModeSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_RER_MOD_SUP,
            cdmaMobilityParam.rerModeSup);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_TZK_MOD_SUP_INCL,
            cdmaMobilityParam.tzkModeSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_TKZ_MOD_SUP,
            cdmaMobilityParam.tzkModeSup);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_TZK_ID_INCL,
            cdmaMobilityParam.tzkIdIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_TKZ_ID,
            cdmaMobilityParam.tzkId);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PIL_REP_INCL,
            cdmaMobilityParam.pilRepIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PIL_REP,
            cdmaMobilityParam.pilRep);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SDB_SUP_INCL,
            cdmaMobilityParam.sdbSupIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SDB_SUP,
            cdmaMobilityParam.sdbSup);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_AUTO_FCSO_ALL_INCL,
            cdmaMobilityParam.autoFcsoAllIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_AUTO_FCSO_ALL,
            cdmaMobilityParam.autoFcsoAll);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_SDB_IN_RCNM_INCL,
            cdmaMobilityParam.sdbInRcnmIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SDB_IN_RCNM,
            cdmaMobilityParam.sdbInRcnm);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_FPC_FCH_INCL,
            cdmaMobilityParam.fpcFchIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC3,
            cdmaMobilityParam.fpcFchInitSetptRC3);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC4,
            cdmaMobilityParam.fpcFchInitSetptRC4);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC5,
            cdmaMobilityParam.fpcFchInitSetptRC5);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC11,
            cdmaMobilityParam.fpcFchInitSetptRC11);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_FPC_FCH_INIT_SETPT_RC12,
            cdmaMobilityParam.fpcFchInitSetptRC12);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_T_ADD_INCL,
            cdmaMobilityParam.tAddIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_T_ADD,
            cdmaMobilityParam.tAdd);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_PILOT_INC_INCL,
            cdmaMobilityParam.pilotIncIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_PILOT_INC,
            cdmaMobilityParam.pilotInc);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_RAND_INCL,
            cdmaMobilityParam.randIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_RAND,
            cdmaMobilityParam.rand);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_LP_SEC_INCL,
            cdmaMobilityParam.lpSecIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_LP_SEC,
            cdmaMobilityParam.lpSec);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_LTM_OFF_INCL,
            cdmaMobilityParam.ltmOffIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_LTM_OFF,
            cdmaMobilityParam.ltmOff);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_DAY_LIGHT_INCL,
            cdmaMobilityParam.dayltIncl);
      GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_DAY_LIGHT,
            cdmaMobilityParam.daylt);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_GCSNA_L2_ACT_TIMER_INCL,
            cdmaMobilityParam.gcsnaL2ActTimerIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_GCSNA_L2_ACT_TIMER,
            cdmaMobilityParam.gcsnaL2ActTimer);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_GCSNA_SEQ_CTXT_TIMER_INCL,
            cdmaMobilityParam.gcsnaSeqCtxtTimerIncl);
      GetMibCache().GetMibAttribute(fapLteDn,
            PARAM_ID_LTE_CDMA2K_GCSNA_SEQ_CTXT_TIMER,
            cdmaMobilityParam.gcsnaSeqCtxtTimer);
      msmSetCdmaMobilityParameters(&cdmaMobilityParam, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported for these parameters");
   }
   return;  
}

void SmApplication::FillCDMA1xNeighCell(u16 cellIdx)
{
   TRACE_PRINTF("%s\n",__func__);

   u16 idx;
   std::vector<std::string> cellType;
   std::vector<std::string> CID;
   std::vector<u32>   bandClass;
   std::vector<u32>   arfcn;
   std::vector<u32>   pnOffset;
   std::vector<u32>   curRank;
   std::vector<u32>   systemType;
   std::vector<u32>   channelNum;
   std::vector<u32>   marketId;
   std::vector<u32>   switchNum;
   std::vector<u32>   sectorNum;
   std::vector<u32>   cellId;
   MsmNeighCellCfg    lteNeighCellCfg;
   MsmCDMA1xNeighCell *cdma1xCell;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   lteNeighCellCfg.actType = MSM_ACT_ADD;

   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_MAX_CDMA1X_NEIGH_CELL_ENTRIES,
         lteNeighCellCfg.maxCellEntries);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_NUM_CDMA1X_NEIGH_CELL_ENTRIES,
         lteNeighCellCfg.numCdma1xCells);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_CELL_BAND_CLASS,
         bandClass);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_ARFCN, arfcn);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_BAND_PN_OFFSET,
         pnOffset);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_CELL_TYPE,
         cellType);
   m_posu8list.clear();
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringArrayenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrCdmaCellType,
         cellType, m_posu8list, 2);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_CID_CDMA2K, CID);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_CUR_RANK,
         curRank);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_SYSTEM_TYPE,
         systemType);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_CHANNEL_NUM,
         channelNum);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NBR_MARKET_ID,
         marketId);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NBR_SWITCH_NUM,
         switchNum);
   GetMibCache().GetMibAttribute(fapLteDn, PARAM_ID_LTE_CDMA2K_NBR_SECTOR_NUM,
         sectorNum);
   GetMibCache().GetMibAttribute(fapLteDn,
         PARAM_ID_LTE_CDMA2K_NBR_CELL_IDENTITY, cellId);

   for(idx = 0; idx<lteNeighCellCfg.numCdma1xCells &&
         lteNeighCellCfg.numCdma1xCells <= lteNeighCellCfg.maxCellEntries;idx++)
   {
      cdma1xCell = &(lteNeighCellCfg.t.neighAddCfg[idx].cdma1xCell);
      cdma1xCell->cellType = m_posu8list[idx];
      cdma1xCell->CID = (s8*)&CID[idx];
      cdma1xCell->bandClass = bandClass[idx];
      cdma1xCell->arfcn = arfcn[idx];
      cdma1xCell->pnOffset = pnOffset[idx];
      cdma1xCell->curRank = curRank[idx];
      cdma1xCell->systemType = systemType[idx];
      cdma1xCell->channelNum = channelNum[idx];
      cdma1xCell->tgtCell.marketId = marketId[idx];
      cdma1xCell->tgtCell.switchNum = switchNum[idx];
      cdma1xCell->tgtCell.sectorNum = sectorNum[idx];
      cdma1xCell->tgtCell.cellId = cellId[idx];
      msmSetCdma1XRttNghCell(&lteNeighCellCfg, cellIdx);
   }
   return;   
}

void SmApplication::HandleCsfbCfgParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<std::string> searchRate;
   string s_ecsfbRptCfg,s_csfbRptCfg;
   MsmCsfbCfgGrp csfbCfgGrp;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      csfbCfgGrp.actType = MSM_ACT_ADD;
      ReadCsfbCfgParameters(dn,csfbCfgGrp);
      msmSetCsfbCfgParameters(&csfbCfgGrp,cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void SmApplication::ReadCsfbCfgParameters( MibDN dn, MsmCsfbCfgGrp &csfbCfgGrp)
{
   string s_ecsfbRptCfg,s_csfbRptCfg;
   std::vector<std::string> searchRate;

   GetMibCache().GetMibAttributeAsString(dn,PARAM_ID_LTE_CDMA2K_ECSFB_REPORT_CFG_VAL,s_ecsfbRptCfg);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->ecsfbReportCfgVal, s_ecsfbRptCfg, m_posu8,3);
   csfbCfgGrp.ecsfbSupport = m_posu8;
   GetMibCache().GetMibAttributeAsString(dn,PARAM_ID_LTE_CDMA2K_CSFB_REPORT_CFG_VAL,s_csfbRptCfg);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->csfbReportCfgVal, s_csfbRptCfg, m_posu8,2);
   csfbCfgGrp.csfbSupport = m_posu8;
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_DUAL_RX_SUP, csfbCfgGrp.dualRxSup);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_IS_DUAL_RXTX_ALLOWED, csfbCfgGrp.dualRxTxSup);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_MARKET_ID, csfbCfgGrp.marketId);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SWITCH_NUM, csfbCfgGrp.switchNum);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SECTOR_NUM, csfbCfgGrp.sectorNum);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CDMA2K_SEARCH_WINDOW_SIZE, searchRate);
   SmApplication::GetInstance().GetSmTr196Validator()->ExpandString(searchRate);
   csfbCfgGrp.searchRate = atoi(searchRate.at(0).c_str());
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_CSFB_TO_UTRA_MEAS_ENABLE, csfbCfgGrp.csfbToUtranWithMeasEnabled);
}

void SmApplication::HandleLteSpsParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmSpsCellConfigData stSpsCellCfg;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   if(!isDynCfg)
   {
      stSpsCellCfg.actType = MSM_ACT_ADD; 
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_IS_SPS_ENABLE,
            stSpsCellCfg.bIsSpsEnabled);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_DL_SPS_UE_PER_TTI,
            stSpsCellCfg.maxDlSpsUePerTti);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_UL_SPS_UE_PER_TTI,
            stSpsCellCfg.maxUlSpsUePerTti);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_MAX_SPS_RB,
            stSpsCellCfg.maxDlBwInRbs);
      msmSetSpsParameters(&stSpsCellCfg, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

void SmApplication::HandleAccessManagementParameters(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmLteFapAccessParams lteFapAccessParams;
   MsmLteSmCellCfg lteSmCellCfg;
   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   ReadAccessManagementParameters(dn,lteFapAccessParams,lteSmCellCfg,cellIdx);

   if(!isDynCfg)
   {
      lteFapAccessParams.actType = MSM_ACT_ADD;
      msmSetFapAccessParameters(&lteFapAccessParams,cellIdx);
      msmSetSmCellConfigParameters(&lteSmCellCfg,cellIdx);
   }
   else
   {
      lteFapAccessParams.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteFapAccessParams, MSM_LTE_FAP_ACCESS_PARAMETERS,
            cellIdx);
   }
}

void SmApplication::ReadAccessManagementParameters
(
 MibDN dn,
 MsmLteFapAccessParams &lteFapAccessParams,
 MsmLteSmCellCfg &lteSmCellCfg,
 u16 cellIdx
 )
{
   s32 maxCSGMembers,maxNonCSGMembers,maxUeSupported;
   string s_lteAccessMode;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_MAX_UE_SERVED,maxUeSupported);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_ACCESS_MODE,s_lteAccessMode);
   if(!(SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessModeInfo, s_lteAccessMode, m_posu8, 4)))
   {
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessMode, s_lteAccessMode, m_posu8, 4);
   }
   lteFapAccessParams.accessMode = m_posu8;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_MAX_CSG_MEMBERS,maxCSGMembers);
   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_MAX_NON_CSG_MEMBERS,maxNonCSGMembers);
   if( maxCSGMembers == -1)
   {
      if(maxUeSupported == -1)
      {
         lteFapAccessParams.maxCSGMembers=(u8)FAP_CAPACITY_MAX_UE_SERVED;
      }
      else
      {
         lteFapAccessParams.maxCSGMembers = (u8) maxUeSupported;
      }
   }
   else
   {
      lteFapAccessParams.maxCSGMembers=(u8)maxCSGMembers;
   }
   if( maxNonCSGMembers == -1)
   {
      if(maxUeSupported == -1)
      {
         lteFapAccessParams.maxNonCSGMembers=(u8)FAP_CAPACITY_MAX_UE_SERVED;
      }
      else
      {
         lteFapAccessParams.maxNonCSGMembers = (u8)maxUeSupported;
      }
   }
   else
   {
      lteFapAccessParams.maxNonCSGMembers=(u8)maxNonCSGMembers;
   }

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_MAX_NON_CSG_RESOURCE,lteFapAccessParams.maxResourceNonCSGMembers);
   lteSmCellCfg.actType = MSM_ACT_ADD;

   msmGetSmCellConfigParameters(&lteSmCellCfg,cellIdx);

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_MAX_UE_SERVED,lteSmCellCfg.maxUeSupp);
   if( lteSmCellCfg.maxUeSupp == -1)
   {
      lteSmCellCfg.maxUeSupp=FAP_CAPACITY_MAX_UE_SERVED;
   }
   lteSmCellCfg.actType = MSM_ACT_ADD;

}




void SmApplication::HandleLteStackInitialConfigComplete()
{ 
   TRACE_PRINTF("%s\n",__func__);

   m_smmInitialConfigComplete = MSM_TRUE;
   TRACE_PRINTF("%s SMM Configuration COMPLETE(%d)\n",__func__,m_smmInitialConfigComplete);

   TRACE_PRINTF ("Operational State is up");
   SetLteOperationalState(1);
   InitConfigComplete eNodeBStackInitConfigComplete;
   SendMessage(eNodeBStackInitConfigComplete, ENTITY_SM, ENTITY_SM);          
   return;
}

void MsmConfigComplete()
{
   TRACE_PRINTF("Received MsmConfigComplete\n");

   if(globalInitCfgComp == false)
   {
      SmApplication::GetInstance().HandleLteStackInitialConfigComplete(); 
      globalInitCfgComp = true;
   }
   return;
}

void SmApplication::HandleLteAlarmRegister(u32 id,u8 alarmSeverity,u8 alarmCauseType, u8 alarmCauseVal, std::string info)
{ 
   TRACE_PRINTF("%s",__func__);

   AlarmRegister alarmRegister(id,alarmSeverity,alarmCauseType,alarmCauseVal,const_cast<char*>(info.c_str()));
   SendMessage(alarmRegister, ENTITY_SM, ENTITY_SM);          
}

void FapAlarmInd(u32 alarmId, u8 severity, u8 causeType, u8 causeVal,u16 cellId)
{
   TRACE_PRINTF("%s\n",__func__);
   alarmId = alarmId + cellId*MAX_ALARMS;
   SmApplication::GetInstance().HandleLteAlarmRegister(alarmId,severity,causeType,causeVal);
   return;
}

/* Function called from SM if Alarm is to be raised with Additional Information*/
void FapAlarmIndWithAddInfo(MsmUpdateAlarms *smUpdateAlarms)
{
   TRACE_PRINTF("%s\n",__func__);

   u16 pci = smUpdateAlarms->t.info.pci;
   u8 actionType = smUpdateAlarms->t.info.actionType;
   u32 cellId = smUpdateAlarms->t.info.cellId;
   std::string info;
   if(smUpdateAlarms->isAdditionalInfo)
   {
      std::stringstream ss;
      ss<<pci<<","<<cellId<<","<<(int)actionType;
      info = ss.str();
   }
   else
   {
      info = "test";
   }
   u32 alarmId = (smUpdateAlarms->alarmId) + (smUpdateAlarms->cellId)*MAX_ALARMS;
   TRACE_PRINTF("Value of info at FapAlarmIndWithAddInfo = %s", info.c_str());
   SmApplication::GetInstance().HandleLteAlarmRegister(alarmId, smUpdateAlarms->severity,
         smUpdateAlarms->causeType, smUpdateAlarms->causeValue, info);
   return;
}

void SmApplication::PeriodicRemHandler()
{
   TRACE_PRINTF("PeriodicRemHandler");

   bool lteRemPerScanMode = false, wcdmaRemPerScanMode = false;
   string lteRemPerScanTime = "", wcdmaRemPerScanTime = "", perRemScanTime = "";

   struct tm remScanTime;
   time_t perRemScan, curTime;
   u32 curTimeOfTodayInSecs, perRemTimeOfTodayInSecs, diffTimeOfTodayInSecs;

   MibAccessInterface &m_mib = SmApplication::GetInstance().GetMibCache();

   MibDN remDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE);
   if(m_mib.IsMibAttributePresent(remDn,PARAM_ID_LTE_PERIODIC_SCAN_MODE))
   {
      m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_PERIODIC_SCAN_MODE, lteRemPerScanMode);
   }

   MibDN remWcdmaDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA);
   if(m_mib.IsMibAttributePresent(remWcdmaDn,PARAM_ID_PERIODIC_SCAN_MODE))
   {
      m_mib.GetMibAttribute(remWcdmaDn, PARAM_ID_PERIODIC_SCAN_MODE, wcdmaRemPerScanMode);
   }

   TRACE_PRINTF("lteRemPerScanMode is :%d, wcdmaRemPerScanMode is %d",
         lteRemPerScanMode, wcdmaRemPerScanMode);

   /* If LTE periodic scan mode is true, read the periodic REM start time */
   if (lteRemPerScanMode)
   {
      /* Get the LTE Periodic REM start time */
      m_mib.GetMibAttribute(remDn, PARAM_ID_LTE_PERIODIC_TIME, lteRemPerScanTime);
   }

   /* If WCDMA periodic scan mode is true, read the periodic REM start time */
   if (wcdmaRemPerScanMode)
   {
      /* Get the WCDMA Periodic REM start time */
      m_mib.GetMibAttribute(remWcdmaDn, PARAM_ID_PERIODIC_TIME, wcdmaRemPerScanTime);
   }
   /* If LTE periodic REM is enabled, take the LTE value */
   if (lteRemPerScanMode == true)
   {
      perRemScanTime = lteRemPerScanTime;
   }
   else if (wcdmaRemPerScanMode == true)
   {
      perRemScanTime = wcdmaRemPerScanTime;
   }
   else
   {
      TRACE_PRINTF("Neither LTE periodic REM nor UMTS periodic REM is set");
      return;
   }

   /* Get the current time */
   time(&curTime);
   curTimeOfTodayInSecs = (curTime % (24*60*60));

   TRACE_PRINTF("Current time is %s\n",ctime(&curTime));
   TRACE_PRINTF("curTimeOfTodayInSecs is %d\n",curTimeOfTodayInSecs);

   TRACE_PRINTF("perRemScanTime is %s\n",perRemScanTime.c_str());

   memset(&remScanTime, 0 , sizeof(remScanTime));

   remScanTime.tm_year = atoi((perRemScanTime.substr(1,4)).c_str());
   remScanTime.tm_mon = atoi((perRemScanTime.substr(6,2)).c_str());
   remScanTime.tm_mday = atoi((perRemScanTime.substr(9,2)).c_str());
   remScanTime.tm_hour = atoi((perRemScanTime.substr(12,2)).c_str());
   remScanTime.tm_min = atoi((perRemScanTime.substr(15,2)).c_str());
   remScanTime.tm_sec = atoi((perRemScanTime.substr(18,2)).c_str());

   TRACE_PRINTF("year: %d; month: %d; day: %d;\n", remScanTime.tm_year, 
         remScanTime.tm_mon, remScanTime.tm_mday);
   TRACE_PRINTF("hour: %d; minute: %d; second: %d\n", remScanTime.tm_hour,
         remScanTime.tm_min, remScanTime.tm_sec);

   remScanTime.tm_isdst = -1;
   remScanTime.tm_year = remScanTime.tm_year - 1900;
   remScanTime.tm_mon = remScanTime.tm_mon - 1;

   perRemScan = mktime(&remScanTime);
   TRACE_PRINTF("perRemScan configured is %s\n",ctime(&perRemScan));

   perRemTimeOfTodayInSecs = (perRemScan % (24*60*60));
   TRACE_PRINTF("perRemTimeOfTodayInSecs is %d\n",perRemTimeOfTodayInSecs);

   diffTimeOfTodayInSecs = perRemTimeOfTodayInSecs - curTimeOfTodayInSecs;
   TRACE_PRINTF("diffTimeOfTodayInSecs is %d\n",diffTimeOfTodayInSecs);

   m_periodRemStartTimer = CreateTimer((const std::string&)"Starting timer to reach the Periodic Time", 
         u32(diffTimeOfTodayInSecs*1000), TimerEngineInterface::TIMER_START_NOW,
         TimerEngineInterface::TIMER_SINGLE_SHOT);

   return;
}

/*Operational state changes*/
void SmApplication::SetLteOperationalState(u32 opState)
{
   TRACE_PRINTF ("Setting OPstate to %d",opState);

   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_LTE_RFTX_OP_STATE, opState);
   GetMibCache().SetMibAttributesByDn(fapDn, attrs, ENTITY_OAM);

   /* ccpu00143063 */
   if (opState == 1)
   {
      m_messengerInitialConfigComplete = MSM_TRUE;
      TRACE_PRINTF("%s Messenger Initial Configuration COMPLETE(%d)\n",__func__,m_messengerInitialConfigComplete);
   }
   return;
}

void MsmOperationalState(u32 opstate)
{
   SmApplication::GetInstance().SetLteOperationalState(opstate);

   TRACE_PRINTF ("OPstate changed to %d",opstate);

   return; 
}

void SmApplication::HandleLteShutDownAck()
{
   TRACE_PRINTF ("Setting admin state to down");
   SmApplication::s_adminFlag=MSM_FALSE;
   /* ccpu00143063 */
   m_messengerInitialConfigComplete = MSM_FALSE;
   TRACE_PRINTF("Setting m_messengerInitialConfigComplete to FALSE\n");

   MfOpStateInformInd opStateInform(MF_SM, ManagedObject::OP_STATE_DISABLED, 0, "");
   SendMessage(opStateInform, ENTITY_OAM, ENTITY_SM);
   TRACE_PRINTF("SmApplication::HandleLteShutDownAck Setting LTE_ADMIN_DOWN_ACK to TRUE");

   startPeriodicRemScan();
   return;
}

void MsmShutDownAck()
{
   TRACE_PRINTF("Received ShutDownACK from APP\n");
   SmApplication::GetInstance().HandleLteShutDownAck();
   return;
}


/*This function calls when value type of KPI is integer*/
void IncFapKpiByIntVal(unsigned int Id,u32 cellIdx,unsigned int  incVal)
{
   TRACE_PRINTF("KPI ID = %d && incval = %d",Id,incVal);
   KpiId kpiId;
   kpiId = static_cast<KpiId>(Id);
   KpiGroupId kpiGroupId;

   bool kpiGroupFound = KpiGroup::GetKpiGroupId(kpiId, kpiGroupId);
   if(false == kpiGroupFound)
   {
      TRACE_PRINTF("\nInvalid GroupId, cannot update Kpi");
      return;
   }

         SmApplication::GetInstance().GetSmKpiCollector()->IncKpiByIntVal((
                  KpiId)Id, cellIdx, incVal);
}

/*This Function calls when value type of KPI is Real*/
void IncFapKpiByRealVal(unsigned int Id,u32 cellIdx,float incVal)
{
   TRACE_PRINTF("KPI ID = %d incval = %f \n",Id,incVal);
   KpiId kpiId;
   kpiId = static_cast<KpiId>(Id);
   KpiGroupId kpiGroupId;

   bool kpiGroupFound = KpiGroup::GetKpiGroupId(kpiId, kpiGroupId);
   if(false == kpiGroupFound)
   {
      TRACE_PRINTF("\nInvalid GroupId, cannot update Kpi");
      return;
   }
   SmApplication::GetInstance().GetSmKpiCollector()->IncKpiByRealVal((KpiId)Id,cellIdx,incVal);
}

/* This function calls when value type of KPI is integer Mutil val */
void  IncFapKpiByIntValMInst(unsigned  int Id, unsigned int  incVal, KpiInstInfo mInfoVal)
{
   TRACE_PRINTF( "\n\n IncFapKpiByIntValMInst\n\n" );
}

void IncFapKpiByRealValMInst(unsigned  int Id, float incVal, KpiInstInfo mInfoVal)
{
   TRACE_PRINTF( "\n\n IncFapKpiByRealValMInst \n\n" );
}

/*This fuction is called by ENB App to notify all KPI info is sent*/
void KpisInfoSentNotification(void)
{
   TRACE_PRINTF( "\n\n ############## KpisInfoSentNotification ##############\n\n" );
   SmApplication::GetInstance().sendNotification();
}

/*This function sends notifcation( like a ping) to OAM from OAM-SM*/
void SmApplication::sendNotification(void)
{
   EventNotify evntNotfy;
   SendMessage(evntNotfy, ENTITY_OAM, ENTITY_SM);
}

void SmApplication::updateN1PucchInMIB(u16 n1Pucch)
{
   TRACE_PRINTF("%s Updating N1pucchan",__func__);
   MibAttributeValues attrs;
   std::vector<std::string> n1pucchAray;
   stringstream convert;
   convert<<n1Pucch;

   n1pucchAray.push_back(convert.str());
   attrs.AddAttribute(PARAM_ID_LTE_N1PUCCHAN, n1pucchAray);
   s_isN1PucchUpdateFromRRM=true;
   GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM );
}

int SmAppTst()
{
   static const char* argv[]={"OAM"};
   TRACE_PRINTF("\nWaiting for Admin state to be unlocked....\n") ;
   int result = 1; // default to error
   result = SmApplication::GetInstance().Run(1, (char**)argv);

   return result;
}

void SmUpdateN1pucch(U16 n1Pucch)
{
   SmApplication::GetInstance().updateN1PucchInMIB(n1Pucch);
}

void SmApplication::updateUmtsInUseNbr
(
 u32 action,
 MsmUtraNeighCell *utraInfo,
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s\n",__func__);

   s32 inUseInstNum;
   std::string plmnId;

   SmApplication::GetInstance().GetPlmn(utraInfo->plmnId[0], plmnId);

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
   switch (action)
   {
      case MSM_ACT_ADD:
         {
            inUseInstNum = SmMultiInstanceObjectManager:: GetInstance().
               addMIO(fapLteDn, MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR_IN_USE);

            MibDN inUseUtraDnObj = MibDN::GenerateMibDN(fapLteDn,
                  MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR_IN_USE, inUseInstNum);
            SmApplication::GetInstance().fillUtraInUseNbr(inUseUtraDnObj,
                  *utraInfo);
         }
         break;

      default:
         {
            TRACE_PRINTF("UMTS_IN_USE does not support Modify or Delete\n");
         }
         break;
   }

   return;
}

void SmApplication::updateLteInUseNbr
(
 u32 action,
 MsmEUTRANeighCell *eutraInfo,
 MibDN fapLteDn
 )
{
   TRACE_PRINTF("%s\n",__func__);

   s32 inUseInstNum;
   std::string plmnId;

   SmApplication::GetInstance().GetPlmn(eutraInfo->plmnId[0], plmnId);

   inUseInstNum = getEutraInuseInstanceNbr(fapLteDn,plmnId,eutraInfo->cid);
   switch (action)
   {
      case MSM_ACT_ADD:
         {
            if (inUseInstNum == -1)
            {
               TRACE_PRINTF("EUTRA neighbour with PLMN ID : %s, CID : %d not yet \
                     added, adding to EUTRA IN USE\n",
                     plmnId.c_str(),eutraInfo->cid);
               inUseInstNum = SmMultiInstanceObjectManager::GetInstance().
                  addMIO(fapLteDn,MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE);
            }
            else
            {
               TRACE_PRINTF("EUTRA neighbour with PLMN ID : %s, CID : %d already \
                     existing in EUTRA IN USE\n", 
                     plmnId.c_str(),eutraInfo->cid);
               return;
            }

            MibDN inUseEutraDnObj = MibDN::GenerateMibDN(fapLteDn,
                  MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE,inUseInstNum);
            LteNeighInuseFillDefaultVal(eutraInfo);
            SmApplication::GetInstance().fillEutraInUseNibr(inUseEutraDnObj,
                  *eutraInfo);
         }
         break;

      case MSM_ACT_MOD:
         {
            if (inUseInstNum == -1)
            {
               TRACE_PRINTF("EUTRA neighbour with PLMN ID : %s, CID : %d not \
                     found in EUTRA IN USE\n", plmnId.c_str(),eutraInfo->cid);
               return;
            }

            MibDN inUseEutraDnObj = MibDN::GenerateMibDN(fapLteDn,
                  MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE,inUseInstNum);
            SmApplication::GetInstance().fillEutraInUseNibr(inUseEutraDnObj,
                  *eutraInfo);
         }
         break;

      case MSM_ACT_DEL:
         {
            if (inUseInstNum == -1)
            {
               TRACE_PRINTF("EUTRA neighbour with PLMN ID : %s, CID : %d not \
                     found in EUTRA IN USE\n", plmnId.c_str(),eutraInfo->cid);
               return;
            }

            MibDN InuseDnForDelete = MibDN::GenerateMibDN(fapLteDn,
                  MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE,inUseInstNum);
            SmMultiInstanceObjectManager:: GetInstance().deleteMIO(fapLteDn,
                  InuseDnForDelete);
         }
         break;

      default:
         {
            TRACE_PRINTF("Invalid action\n");
         }
         break;
   }

   return;
}

void SmUpdateMibParms(u32 msgType, u32 action, void* Cfg, u16 cellIdx)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmUtraNeighCell  *updatedUmtsCell;
   MsmEUTRANeighCell *updatedLteCell;
   MsmLteGERANNeighCell *updatedGeranCell;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx); 

   switch(msgType)
   {
      case MSM_LTE_UTRA_NEIGHBORLIST_IN_USE_PARAMETERS:
         {
            updatedUmtsCell = (MsmUtraNeighCell*)Cfg;
            SmApplication::GetInstance().updateUmtsInUseNbr(action,
                  updatedUmtsCell, cellIdx);
         }
         break;
      case MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS:
         {
            updatedLteCell = (MsmEUTRANeighCell*)Cfg;
            SmApplication::GetInstance().updateLteInUseNbr(action, updatedLteCell,fapLteDn);
         }
         break;
      case MSM_GERAN_NEIGHBOR_CELL_IN_USE_PARAMETERS:
         {
            updatedGeranCell = (MsmLteGERANNeighCell*)Cfg;
            SmApplication::GetInstance().updateGeranInUseNbr(updatedGeranCell,
                  cellIdx);
         }
         break;
      default:
         {
            TRACE_PRINTF("Message updated is not handled for MessageType\
                  = %d\n", msgType);
         }
         break;
   }
   return;
}

void SmUpdateSwVersion(const char *swver)
{
   SmApplication::GetInstance().HandleSwVersion(swver);
   return; 
}

void SmApplication::HandleLteTMParameters
(
 u16    cellIdx,
 bool   isDynCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MsmTMCellConfig lteTransModeCellCfg;
   string autoConfig,preferredTransMode;
   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_TM_AUTO_CONFIG,autoConfig);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrAutoConfigTM,
         autoConfig, m_posu8,2);
   lteTransModeCellCfg.bIsAutoConfigEnabled=m_posu8;

   GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_PREFERRED_TRANSMISSION_MODE,
         preferredTransMode);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(
         SmApplication::GetInstance().GetSmTr196Validator()->arrPreferredTransMode,
         preferredTransMode, m_posu8,3);
   lteTransModeCellCfg.preferredTransMode = m_posu8+2;

   if(1 == lteTransModeCellCfg.bIsAutoConfigEnabled)
   {
      lteTransModeCellCfg.transModeUse = 4;
   }
   else
   {
      lteTransModeCellCfg.transModeUse = lteTransModeCellCfg.preferredTransMode;
   }

   if(!isDynCfg)
   {
      lteTransModeCellCfg.actType = MSM_ACT_ADD; 
      msmSetTMParameters(&lteTransModeCellCfg,cellIdx);
   }
   else
   {
      lteTransModeCellCfg.actType = MSM_ACT_MOD;
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteTransModeCellCfg, MSM_LTE_TM_PARAMETERS, cellIdx);
   }

   return;
}

void smUpdateSONParams(u32 msgType, void* params)
{
   TRACE_PRINTF("%s\n",__func__);
#if 0
   switch(msgType)
   {
      case MSM_LTE_UPDATE_SON_SELECTED_PCI:
         {
            u32* pciPtr = (u32*)params;
            u32 pci = (u32)*pciPtr;
            SmApplication::GetInstance().updateSONSelectedPCIInMIB( pci );
         }
         break;

      case MSM_LTE_UPDATE_SON_SELECTED_EARFCNUL:
         SmApplication::GetInstance().updateSONSelectedEARFCNULinMIB( (u32*)params );
         break;

      case MSM_LTE_UPDATE_SON_SELECTED_EARFCNDL:
         SmApplication::GetInstance().updateSONSelectedEARFCNDLinMIB( (u32*)params );
         break;


      case MSM_LTE_UPDATE_PRACH_CONFIG:
         SmApplication::GetInstance().updatePRACHConfInMIB( (MsmLtePrachCfgCommon*)params );
         break;

      case MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS:
         SmApplication::GetInstance().updatePDSCHConfInMIB( (MsmLtePdschCfgCommon *)params );
         break;

      case MSM_LTE_POWER_OFFSET_PARAMETERS:
         SmApplication::GetInstance().updatePowerOffsetInMIB( (MsmLtePowerOffsetParams*)params );
         break;


      default:
         break;
         // Invalid update
   }
#endif
}

void SmApplication::updateSONSelectedPCIInMIB( u16 paramVal )
{
   TRACE_PRINTF("%s\n",__func__);
#if 0
   u32  newPci;
   newPci = (u32)paramVal;
   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_PCI, newPci);
   GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM );
#endif
}

void SmApplication::updateSONSelectedEARFCNULinMIB( u32* paramVal )
{
   TRACE_PRINTF("%s\n",__func__);
#if 0
   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_EARFCNUL, *paramVal );
   GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM );
#endif
}

void SmApplication::updateSONSelectedEARFCNDLinMIB( u32* paramVal )
{
   TRACE_PRINTF("%s\n",__func__);
#if 0
   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_EARFCNDL, *paramVal );
   GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM );
#endif
}


void SmApplication::updatePDSCHConfInMIB( MsmLtePdschCfgCommon* pdschConfig)
{
   TRACE_PRINTF("%s\n",__func__);
#if 0
   stringstream toString;

   toString.str("");
   s32 txPwr = pdschConfig->referenceSignalPwr[0];
   toString << txPwr;

   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_TX_PWR, toString.str());

   GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM );
#endif
}

void SmApplication::updatePowerOffsetInMIB(MsmLtePowerOffsetParams* powerOffset )
{
   TRACE_PRINTF("%s\n",__func__);
}

void SmApplication::updatePRACHConfInMIB( MsmLtePrachCfgCommon* prachConf )
{
   TRACE_PRINTF("%s\n",__func__);
#if 0
   MibAttributeValues attrs;

   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_PRACH_ROOT_SEQUENCE_INDEX, (u32)prachConf->rootSequenceIndx);
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_PRACH_CONFIG_INDEX, (u32)prachConf->prachParamLst.prachCfgIdxLst[0]);
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_PRACH_ZERO_CORRELATIONZONE_CONFIG, (u32)prachConf->prachCfgInfo.zeroCorrelationZoneCfg );
   attrs.AddAttribute(PARAM_ID_LTE_SON_SELECTED_PRACH_FREQ_OFFSET,  (u32)prachConf->prachCfgInfo.prachFreqOffset );   
   GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM );
#endif
}

void SmApplication::HandleSwVersion(const char* swver)
{
   TRACE_PRINTF("%s\n",__func__);

   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_LTE_SOFTWARE_VERSION, swver);
   GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
   return;
}

void SmApplication::HandleLtePlmnIdUpdate(MsmEUTRANeighCell *eutraCellCfg, std::vector<std::string> *plmnIdList)
{
   TRACE_PRINTF("%s\n",__func__);

   MibAttributeValues attrs;
   char               plmnId[NUM_MAX_PLMN_DIGIT + 1] = {};
   u8                 mccDigits = 0, mncDigits = 0;

   for(mccDigits = 0; mccDigits < MSM_MAX_MCC_DIGITS; mccDigits++)
   {
      plmnId[mccDigits] = eutraCellCfg->plmnId[0].mcc[mccDigits] + '0';
   }

   for(mncDigits = 0; mncDigits < eutraCellCfg->plmnId[0].numMncDigits; mncDigits++)
   {
      plmnId[mccDigits+mncDigits] = eutraCellCfg->plmnId[0].mnc[mncDigits] + '0';
   }
   plmnId[mccDigits+mncDigits] = '\0';

   GetMibCache().GetMibAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID, *plmnIdList);
   plmnIdList->push_back(plmnId);

   return;
}

void SmApplication::UpdateNbrCellPlmnId(MsmEUTRANeighCell *lteNeighCellCfg, std::string plmnidvalue)
{
   TRACE_PRINTF("%s\n",__func__);

   string mccvalue,mncvalue;
   u32 plmnidlength = 0;
   u32 idx;
   plmnidlength = plmnidvalue.length(); 
   for(idx = 0; idx < plmnidlength; idx++)
   {
      if(idx < MSM_MAX_MCC_DIGITS)
      {
         mccvalue = plmnidvalue.substr(idx,1);
         lteNeighCellCfg->plmnId[0].mcc[idx] = u8(atoi(mccvalue.c_str()));
      }
      else
      {
         mncvalue = plmnidvalue.substr(idx,1);
         lteNeighCellCfg->plmnId[0].mnc[idx-3] = u8(atoi(mncvalue.c_str()));
      }
   }
   lteNeighCellCfg->plmnId[0].numMncDigits = (plmnidlength - 3);
}

void SmApplication::HandleLtePlmnIdUpdate
(
 MsmEUTRANeighCell *eutraCellCfg,
 std::string *plmnIdStr
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MibAttributeValues attrs;
   char               plmnId[NUM_MAX_PLMN_DIGIT + 1] = {};
   u8                 mccDigits = 0, mncDigits = 0;

   for(mccDigits = 0; mccDigits < MSM_MAX_MCC_DIGITS; mccDigits++)
   {
      plmnId[mccDigits] = eutraCellCfg->plmnId[0].mcc[mccDigits] + '0';
   }

   for(mncDigits = 0; mncDigits < eutraCellCfg->plmnId[0].numMncDigits;
         mncDigits++)
   {
      plmnId[mccDigits+mncDigits] = eutraCellCfg->plmnId[0].mnc[mncDigits] +
         '0';
   }
   std::string plmnIdstring(plmnId);
   *plmnIdStr = plmnIdstring;
   return;
}

s32 SmApplication::getEutraInuseInstanceNbr
(
 MibDN fapLteDn,
 std::string plmnId,
 u32 cid
 )
{
   TRACE_PRINTF("%s",__func__);

   u32 inuseCid;
   s32 instanceNbr = -1;
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   for(u32 idx=0; idx< 32; idx++)
   {
      MibDN inuseDn=MibDN::GenerateMibDN(fapLteDn,
            MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE,idx);

      std::string inusePlmnId;
      if(m_mib.IsMibObjectPresent(inuseDn))
      {
         m_mib.GetMibAttribute(inuseDn,
               PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_CID,inuseCid);

         if(cid == inuseCid)
         {
            m_mib.GetMibAttribute(inuseDn,
                  PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID,inusePlmnId);
            if(strstr(inusePlmnId.c_str(),plmnId.c_str()))
            {
               instanceNbr=(s32)idx;
               break;
            }
         }
      }
   }
   return instanceNbr;
}

bool SmApplication::IsAllMandatoryParametersSet(MibDN  remDN)
{
   TRACE_PRINTF("%s",__func__);

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
   if (
         (m_mib.IsMibAttributePresent(remDN, PARAM_ID_LTE_REM_SCANNED_EARFCN))&&
         (m_mib.IsMibAttributePresent(remDN, PARAM_ID_LTE_REM_SCANNED_PCI))&&
         (m_mib.IsMibAttributePresent(remDN,
                                      PARAM_ID_LTE_REM_SCANNED_NUM_OF_PLMN_ENTRIES))&&
         (m_mib.IsMibAttributePresent(remDN,
                                      PARAM_ID_LTE_REM_SCANNED_CELL_IDENTITY))&&
         (m_mib.IsMibAttributePresent(remDN, PARAM_ID_LTE_REM_SCANNED_PLMNID))
      )
   {
      return true;
   }
   else
   {
      TRACE_PRINTF("mendatory parameers (NUM_PLMN,PLMNID, PCI,CID,EARFCN)are\
            not set for %s",remDN.ToString().c_str());
      return false;
   }
}

void SmApplication::readEutraParameters
(
 MibDN dn,
 MsmEUTRANeighCell *eutraNeighCel
 )
{
   TRACE_PRINTF("%s",__func__);

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
   u32 cid,earfcnDl,pci,BlackListed,tac,csgId,numAntenna;
   u32 ulDlSubFrameCfg,splSfCfg,cpDl,cpUl,dlBw,ulBw;
   s32 RSTxPower,rsrp,qoffset,cio;
   s32 s32_val, rssi;
   u32 u32_val;

   std::string csgAccessMode,plmnId;
   if(m_mib.IsMibObjectPresent(dn))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CID,cid );
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_EARFCN,earfcnDl);
      printf("neigh earfcndl:%d\n", earfcnDl);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PLMNID,plmnId);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PHY_CELLID,pci);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_QOFFSET,s32_val);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, s32_val, m_posu8);
      qoffset = m_posu8;

      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CIO,s32_val);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, s32_val, m_posu8);
      cio = m_posu8;

      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_RS_TX_POWER,RSTxPower);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED,BlackListed);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_TAC,tac);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CSG_ID,csgId);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_NUM_ANTENNA,numAntenna);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_ULDL_SUB_FRAME_CFG,ulDlSubFrameCfg);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_SPL_SF_CFG,splSfCfg);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CP_DL,cpDl);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_CP_UL,cpUl);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_RSRP,rsrp);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_RSSI, rssi);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_DL_BW,u32_val);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, u32_val, m_posu8);
      dlBw = m_posu8;

      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CELL_UL_BW,u32_val);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, u32_val, m_posu8);
      ulBw = m_posu8;

      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_X_RADISYS_NEIGH_LIST_LTE_CSG_ACCESS_MODE,csgAccessMode);

      eutraNeighCel->cid=cid;
      eutraNeighCel->earfcnDl=(U16)earfcnDl;
      eutraNeighCel->pci=(U16)pci;
      eutraNeighCel->qoffset=(U8)qoffset;
      eutraNeighCel->cio=(U8)cio;
      eutraNeighCel->RSTxPower=(S8)RSTxPower;
      eutraNeighCel->BlackListed=(U8)BlackListed;
      eutraNeighCel->tac=tac;
      eutraNeighCel->csgId=csgId;
      eutraNeighCel->numAntenna=(u8)numAntenna;
      eutraNeighCel->ulDlSubFrameCfg=(u8)ulDlSubFrameCfg;
      eutraNeighCel->splSfCfg=(u8)splSfCfg;
      eutraNeighCel->cpDl=(u8)cpDl;
      eutraNeighCel->cpUl=(u8)cpUl;
      eutraNeighCel->rsrp=(s16)rsrp;
      eutraNeighCel->rssi=rssi;
      eutraNeighCel->dlBw=(u8)dlBw;
      eutraNeighCel->ulBw=(u8)ulBw;

      LteNeighInuseFillDefaultVal(eutraNeighCel);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums
         (SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessModeInfo,
          csgAccessMode, m_posu8, 4);
      eutraNeighCel->csgAccessMode = m_posu8;
      SmApplication::GetInstance().FillPlmn(&eutraNeighCel->plmnId[0],plmnId);
   }
}

void SmApplication::readRemLteParameters(MibDN dn,MsmEUTRANeighCell *eutraNeighCel)
{
   TRACE_PRINTF("%s",__func__);

   u32 numPci = 0;
   u32 intraPciIdx;
   s32 s32_val;
   u32 u32_val;
   u32 cid =0;
   u32 earfcnDl=0;
   u32 earfcnUl=0;
   u32 pci=0;
   u32 BlackListed=0;
   u32 tac=0;
   u32 csgId=0;
   u32 numAntenna=0;;
   u32 ulDlSubFrameCfg=0;
   u32 splSfCfg=0;
   u32 cpDl=0;
   u32 cpUl=0;
   u32 dlBw=0;
   u32 ulBw=0;
   u32 isCellBarred=0;
   u32 highSpeedFlag=0;
   u32 prachFreqOffset=0;
   u32 prachCfgIdx=0;
   u32 zeroCorrelationZoneCfg=0;
   u32 rootSeqIndex=0;
   u32 isPrachConfig=0;
   s32 RSTxPower,rsrp,qoffset,cio;
   s32 rssi;
   u32 intraFreqListIdx = 0;
   std::string csgAccessMode,plmnId;
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
   std::vector<u32> neighborInUseIntraFreqNeighPci;

   if(m_mib.IsMibObjectPresent(dn))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_SCANNED_CELL_IDENTITY,cid );
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_SCANNED_EARFCN,earfcnDl);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_SCANNED_PLMNID,plmnId);
      GetMibCache().GetMibAttribute(dn,PARAM_ID_LTE_REM_SCANNED_PCI ,pci);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_UL_EARFCN,earfcnUl,25600);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_QOFFSET,s32_val,0);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, s32_val, m_posu8);
      qoffset = m_posu8;

      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CIO,s32_val,0);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, s32_val, m_posu8);
      cio = m_posu8;
      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_RS_TX_POWER,RSTxPower,13);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_BLACKLISTED,BlackListed,0);
      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_TAC,tac,0);
      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_CSG_ID,csgId,0);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_NUM_ANTENNA,numAntenna,2);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_ULDL_SUB_FRAME_CFG,ulDlSubFrameCfg,2);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_SPL_SF_CFG,splSfCfg,7);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CP_DL,cpDl,0);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CP_UL,cpUl,0);
      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_RSRP,rsrp,-128);
      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_RSSI, rssi,0);

      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_DL_BANDWIDTH,u32_val,(u32)20);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, u32_val, m_posu8);
      dlBw = m_posu8;

      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_UL_BANDWIDTH,u32_val,(u32)20);
      SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, u32_val, m_posu8);
      ulBw = m_posu8;

      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_CSG_ACCESS_MODE,csgAccessMode,"");
      ReadIfPresent(dn,PARAM_ID_LTE_REM_SCANNED_CELL_BARRED,isCellBarred,0);
      eutraNeighCel->cid=cid;
      eutraNeighCel->earfcnDl=(U16)earfcnDl;
      eutraNeighCel->earfcnUl=(U16)earfcnUl;
      eutraNeighCel->pci=(U16)pci;
      eutraNeighCel->qoffset=(U8)qoffset;
      eutraNeighCel->cio=(U8)cio;
      eutraNeighCel->RSTxPower=(S8)RSTxPower;
      eutraNeighCel->BlackListed=(U8)BlackListed;
      eutraNeighCel->tac=tac;
      eutraNeighCel->csgId=csgId;
      eutraNeighCel->numAntenna=(u8)numAntenna;
      eutraNeighCel->ulDlSubFrameCfg=(u8)ulDlSubFrameCfg;
      eutraNeighCel->splSfCfg=(u8)splSfCfg;
      eutraNeighCel->cpDl=(u8)cpDl;
      eutraNeighCel->cpUl=(u8)cpUl;
      eutraNeighCel->rsrp=(s16)rsrp;
      eutraNeighCel->rssi=rssi;
      eutraNeighCel->dlBw=(u8)dlBw;
      eutraNeighCel->ulBw=(u8)ulBw;
      eutraNeighCel->isCellBarred=(u8)isCellBarred;

      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_HIGH_SPEED_FLAG,highSpeedFlag,0);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_FREQ_OFFSET,prachFreqOffset,43);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_CONFIG_INDEX,prachCfgIdx,22);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_ZERO_CORRELATIONZONE_CONFIG,
            zeroCorrelationZoneCfg,5);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_PRACH_ROOT_SEQ_INDEX,rootSeqIndex,22);
      ReadIfPresent(dn,PARAM_ID_LTE_X_RADISYS_REM_SCANNED_IS_PRACH_CFG_PRESENT,isPrachConfig,0);

      eutraNeighCel->isPrachConfig = (u8) isPrachConfig;
      eutraNeighCel->prachCfgInfo.rootSeqIndex = (u16)rootSeqIndex;
      eutraNeighCel->prachCfgInfo.zeroCorrelationZoneCfg = (u8)zeroCorrelationZoneCfg;
      eutraNeighCel->prachCfgInfo.highSpeedFlag =(u8)highSpeedFlag;
      eutraNeighCel->prachCfgInfo.prachFreqOffset =(u8) prachFreqOffset;
      eutraNeighCel->prachCfgInfo.prachCfgIdx = (u8)prachCfgIdx;
      for (u32 idx=0;idx<MSM_MAX_NUM_NEIGH_CELLS;idx++)
      {
         eutraNeighCel->intraFreqNghPci[idx]=0;
      }
      if (strcmp(csgAccessMode.c_str(), "") != 0)
      {
         SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums
            (SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessModeInfo,
             csgAccessMode, m_posu8, 4);
         eutraNeighCel->csgAccessMode = m_posu8;
      }
      SmApplication::GetInstance().FillPlmn(&eutraNeighCel->plmnId[0],plmnId);

      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_REM_SCANNED_INTRA_FREQ_NEIGH_PCI, neighborInUseIntraFreqNeighPci);
      eutraNeighCel->numIntraFreqNeighbors = neighborInUseIntraFreqNeighPci[intraFreqListIdx];
      numPci = neighborInUseIntraFreqNeighPci[intraFreqListIdx];
      for(intraPciIdx = 0; intraPciIdx< numPci; intraPciIdx++ )
      {
         intraFreqListIdx++;
         eutraNeighCel->intraFreqNghPci[intraPciIdx] = (u16)neighborInUseIntraFreqNeighPci[intraFreqListIdx];
      }
      intraFreqListIdx++;
   }
}

void SmApplication::readRemUmtsParameters(MibDN dn, MsmUtraNeighCell *cellInfo)
{
   TRACE_PRINTF("%s",__func__);

   std::string plmnId;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   if(m_mib.IsMibObjectPresent(dn))
   {
      GetMibCache().GetMibAttribute(dn, PARAM_ID_UARFCN_DL, cellInfo->arfcnDl);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_PRIM_SC,   cellInfo->psc);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LAC,       cellInfo->lac);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_RAC, cellInfo->rac);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_CELL_IDENTITY, cellInfo->cId);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_PCPICH_TXPOWER, cellInfo->pcpichTxPower);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_PLMN_ID, plmnId);
      SmApplication::GetInstance().FillPlmn(&cellInfo->plmnId[0], plmnId);
      cellInfo->numPlmn = 1;
   }

   return;
}

void SmApplication::fillEutraInUseNibr(MibDN dn ,MsmEUTRANeighCell eutraNeighCel)
{
   TRACE_PRINTF("%s",__func__);

   MibAttributeValues attrVal;
   std::string csgAccessMode,plmnId;
   std::vector<u32> neighPCI;
   LteNeighInuseFillDefaultVal(&eutraNeighCel);

   neighPCI.push_back((u32)eutraNeighCel.numIntraFreqNeighbors);
   for (u32 idx=0;idx<MSM_MAX_NUM_NEIGH_CELLS;idx++)
   {
      neighPCI.push_back((u32)eutraNeighCel.intraFreqNghPci[idx]);
   }

   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_CID,eutraNeighCel.cid );
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_DL_EARFCN,(u32)eutraNeighCel.earfcnDl);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PCI,(u32)eutraNeighCel.pci);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_QOFFSET,eutraNeighCel.qoffset);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_CIO, eutraNeighCel.cio);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_RS_TX_POWER,(s32)eutraNeighCel.RSTxPower);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_BLACKLISTED,(u32)eutraNeighCel.BlackListed);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_TAC,(u32)eutraNeighCel.tac);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CSG_ID,(u32)eutraNeighCel.csgId);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_NUM_ANTENNA,(u32)eutraNeighCel.numAntenna);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_ULDL_SUB_FRAME_CFG,(u32)eutraNeighCel.ulDlSubFrameCfg);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_SPL_SF_CFG,(u32)eutraNeighCel.splSfCfg);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CP_DL,(u32)eutraNeighCel.cpDl);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CP_UL,(u32)eutraNeighCel.cpUl);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_RSRP,(s32)eutraNeighCel.rsrp);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_RSSI,(s32)eutraNeighCel.rssi);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_DL_BW,(u32)eutraNeighCel.dlBw);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_UL_BW,(u32)eutraNeighCel.ulBw);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_IS_PRACH_CFG_PRESENT,(u32)eutraNeighCel.isPrachConfig);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_ROOT_SEQ_INDEX,(u32)eutraNeighCel.prachCfgInfo.rootSeqIndex);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_ZERO_CORRELATIONZONE_CONFIG,(u32)eutraNeighCel.prachCfgInfo.zeroCorrelationZoneCfg);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_HIGH_SPEED_FLAG,(u32)eutraNeighCel.prachCfgInfo.highSpeedFlag);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_FREQ_OFFSET,(u32)eutraNeighCel.prachCfgInfo.prachFreqOffset);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_CONFIG_INDEX,(u32)eutraNeighCel.prachCfgInfo.prachCfgIdx);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_INTRA_FREQ_NEIGH_PCI,neighPCI);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_UL_EARFCN,(u32)eutraNeighCel.earfcnUl);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_LTE_BAND,(u32)eutraNeighCel.lteBand);
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_ISBARRED,(u32)eutraNeighCel.isCellBarred);
   csgAccessMode=SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessModeInfo[eutraNeighCel.csgAccessMode];
   attrVal.AddAttribute(PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CSG_ACCESS_MODE,csgAccessMode);

   SmApplication::GetInstance().GetPlmn(eutraNeighCel.plmnId[0],plmnId);
   TRACE_PRINTF("Filling IN USE with PLMN ID : %s\n", plmnId.c_str());
   attrVal.AddAttribute( PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID,plmnId.c_str());
   SmApplication::GetInstance().GetMibCache().SetMibAttributesByDn(dn,attrVal,ENTITY_OAM);
}

void SmApplication::ReadEutraInuseParameters(MibDN inUsednobj,MsmEUTRANeighCell *eutraCell)
{
   TRACE_PRINTF("%s",__func__);

   s32 qOffset, cio, rsrp,rssi;
   std::string plmnId,csgAccessMode;
   std::vector<u32> neighPCI;
   u32 bandWidth = 0;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   if(!m_mib.IsMibObjectPresent(inUsednobj))
   {
      return;
   }
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_CID, eutraCell->cid );
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_DL_EARFCN, eutraCell->earfcnDl);
   m_mib.GetMibAttribute (inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PCI, eutraCell->pci);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_QOFFSET, qOffset);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, qOffset, m_posu8);
   eutraCell->qoffset = m_posu8;
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_CIO, cio);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteS32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrqOffsetFreqInfo, cio, m_posu8);
   eutraCell->cio = m_posu8;
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_RS_TX_POWER, eutraCell->RSTxPower);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_BLACKLISTED, eutraCell->BlackListed);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_TAC, eutraCell->tac);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CSG_ID, eutraCell->csgId);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_NUM_ANTENNA, eutraCell->numAntenna);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_ULDL_SUB_FRAME_CFG, eutraCell->ulDlSubFrameCfg);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_SPL_SF_CFG, eutraCell->splSfCfg);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CP_DL, eutraCell->cpDl);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CP_UL, eutraCell->cpUl);
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_RSRP, rsrp);
   eutraCell->rsrp = (s8)rsrp;
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_RSSI, rssi);
   eutraCell->rssi = (s8)rssi;
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_DL_BW, bandWidth);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, bandWidth, m_posu8);
   eutraCell->dlBw = m_posu8;
   m_mib.GetMibAttribute(inUsednobj,PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_UL_BW, bandWidth);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteU32enums(SmApplication::GetInstance().GetSmTr196Validator()->arrNeighBandwidth, bandWidth, m_posu8);
   eutraCell->ulBw = m_posu8;
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_IS_PRACH_CFG_PRESENT,eutraCell->isPrachConfig);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_ROOT_SEQ_INDEX,eutraCell->prachCfgInfo.rootSeqIndex);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_ZERO_CORRELATIONZONE_CONFIG,eutraCell->prachCfgInfo.zeroCorrelationZoneCfg);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_HIGH_SPEED_FLAG,eutraCell->prachCfgInfo.highSpeedFlag);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_FREQ_OFFSET,eutraCell->prachCfgInfo.prachFreqOffset);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_PRACH_CONFIG_INDEX,eutraCell->prachCfgInfo.prachCfgIdx);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_INTRA_FREQ_NEIGH_PCI,neighPCI);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_UL_EARFCN,eutraCell->earfcnUl);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_LTE_BAND,eutraCell->lteBand);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_ISBARRED,eutraCell->isCellBarred);
   eutraCell->isCellBarred = !(eutraCell->isCellBarred);
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_X_RADISYS_OAM_NEIGH_EUTRA_IN_USE_CELL_CSG_ACCESS_MODE, csgAccessMode);
   SmApplication::GetInstance().GetSmTr196Validator()->GetLteStringenums(SmApplication::GetInstance().GetSmTr196Validator()->arrlteAccessModeInfo, csgAccessMode, m_posu8, 4);
   eutraCell->csgAccessMode = m_posu8;

   for(u32 idx=0;idx< neighPCI.size();idx++)
   {
      eutraCell->intraFreqNghPci[idx]=(u16)neighPCI.at(idx);
   }
   m_mib.GetMibAttribute(inUsednobj, PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_PLMNID,plmnId);
   SmApplication::GetInstance().FillPlmn(&eutraCell->plmnId[0],plmnId);

   LteNeighInuseFillDefaultVal(eutraCell);
}

void SmApplication::LteNeighInuseFillDefaultVal(MsmEUTRANeighCell *eutraCell)
{
   TRACE_PRINTF("%s",__func__);

   eutraCell->numAntenna=2;
   eutraCell->isPrachConfig=0;
   eutraCell->prachCfgInfo.rootSeqIndex = (u16)65535;
   eutraCell->prachCfgInfo.zeroCorrelationZoneCfg = (u8)65535;
   eutraCell->prachCfgInfo.highSpeedFlag =(u8) 0;
   eutraCell->prachCfgInfo.prachFreqOffset =(u8) 255;
   eutraCell->prachCfgInfo.prachCfgIdx = (u8)255;
   eutraCell->isCellBarred=0;
   for (u32 idx=0;idx<MSM_MAX_NUM_NEIGH_CELLS;idx++)
   {
      eutraCell->intraFreqNghPci[idx]=0;
   }
}

void SmApplication::ReadUtraParameters(MibDN dnobj, MsmUtraNeighCell *utranCell)
{
   TRACE_PRINTF("%s",__func__);

   std::string plmnId;
   string plmnidvalue,mccvalue,mncvalue;

   U32                          rncId;
   U32                          cId;
   U32                          lac;
   U32                          rac;
   U32                          psc;
   S32                          pcpichTxPower=5;
   U32                          arfcnUl;
   U32                          arfcnDl;
   U32                          isRimSupported;
   U32                          isVoipCapable;
   U32                          isPsHoCapable;

   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   m_mib.GetMibAttribute(dnobj,
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PCPICH_TX_POWER, pcpichTxPower);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RNCID,
         rncId);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_CID_IRAT,
         cId);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_LAC,lac);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RAC,rac);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PCPICH_SC,
         psc);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_UARFCNUL,
         arfcnUl);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_UARFCNDL,
         arfcnDl);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RIM_SUPPORT,
         isRimSupported);
   m_mib.GetMibAttribute(dnobj,PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID,
         plmnId);
   m_mib.GetMibAttribute(dnobj,
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_IS_VOIP_CAPABLE, isVoipCapable);
   m_mib.GetMibAttribute(dnobj,
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_IS_PS_HO_CAPABLE, isPsHoCapable);

   utranCell->pcpichTxPower = (s8)pcpichTxPower;
   utranCell->rncId=(u16)rncId;
   utranCell->cId=(u16)cId;
   utranCell->lac =(u16)lac;
   utranCell->rac  =(u8)rac;
   utranCell->psc=(u16)psc;
   utranCell->arfcnUl=(u16)arfcnUl;
   utranCell->arfcnDl=(u16)arfcnDl;
   utranCell->isRimSupported=(u8)isRimSupported;
   utranCell->isVoipCapable = isVoipCapable;
   utranCell->isPsHOCapable = isPsHoCapable;
   utranCell->numPlmn = 1;
   SmApplication::GetInstance().FillPlmn(&utranCell->plmnId[0],plmnId);
}

void SmApplication::fillUtraInUseNbr(MibDN dnobj, MsmUtraNeighCell utranCell)
{
   TRACE_PRINTF("%s",__func__);

   MibAttributeValues attrVal;
   std::string plmn;

   attrVal.AddAttribute(
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_PCPICH_IN_USE_TX_POWER,
         (S32)utranCell.pcpichTxPower);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_RNCID,
         (U32)utranCell.rncId );
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_CID_IRAT,
         (U32)utranCell.cId);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_LAC,
         (U32)utranCell.lac);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_RAC,
         (U32)utranCell.rac);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_PCPICH_SC,
         (U32)utranCell.psc);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_UARFCNUL,
         (U32)utranCell.arfcnUl);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_UARFCNDL,
         (U32)utranCell.arfcnDl);

   SmApplication::GetInstance().GetPlmn(utranCell.plmnId[0],plmn);
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_PLMNID,
         plmn.c_str());
   attrVal.AddAttribute(PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_RIM_SUPPORT,
         (U32)utranCell.isRimSupported );
   attrVal.AddAttribute(
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_IS_VOIP_CAPABLE,
         (U32)utranCell.isVoipCapable);
   attrVal.AddAttribute(
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_IN_USE_CELL_IS_PS_HO_CAPABLE,
         (U32)utranCell.isPsHOCapable);

   SmApplication::GetInstance().GetMibCache().SetMibAttributesByDn(dnobj,
         attrVal, ENTITY_OAM);
}

void SmApplication::FillPlmn(MsmLtePlmnId *plmn,std::string plmnId)
{
   TRACE_PRINTF("%s",__func__);

   std::string mncvalue,mccvalue;
   u32 plmnidlength = plmnId.length();

   for(u32 idx = 0; idx < plmnidlength; idx++)
   {
      if(idx < MSM_MAX_MCC_DIGITS)
      {
         mccvalue = plmnId.substr(idx,1);
         plmn->mcc[idx] = u8(atoi(mccvalue.c_str()));
      }
      else
      {
         mncvalue = plmnId.substr(idx,1);
         plmn->mnc[idx-3] = u8(atoi(mncvalue.c_str()));
      }
   }
   plmn->numMncDigits = (plmnidlength - 3);
}

void SmApplication::GetPlmn(MsmLtePlmnId plmn,std::string &plmnId)
{
   TRACE_PRINTF("%s",__func__);

   u32 idx;
   for(idx=0;idx<(plmn.numMncDigits+(u32)3);idx++)
   {
      if(idx < MSM_MAX_MCC_DIGITS)
      {
         plmnId[idx]=plmn.mcc[idx]+48;
      }
      else
      {
         plmnId[idx]=plmn.mnc[idx-3]+48;
      }
   }
   plmnId[idx]='\0';
}

void msmDynConfigComplete(u8 status, u8 cause, MsmDynCfmInfo cfmInfo,U16 cellIdx)
{
   TRACE_PRINTF("%s",__func__);

   /* Received response, so set the flag to FALSE */
   m_smmWaitForDynCfgRsp = FALSE;

   /* Failure due to timer expiry during configuration */
   if ((status == MSM_CFM_FAILURE) && (cause == MSM_CAUSE_TIMER_EXPIRY))
   {
      TRACE_PRINTF("\nFailure received for Dynamic configuration due to Timer expiry\n");
      /* Reboot the system */
      if(-1 == system("chmod +x config/reboot-fap"))
      {
         TRACE_PRINTF("chmod +x config/reboot-fap fail %s\n",__func__);
      }
      if(-1 == system("config/reboot-fap"))
      {
         TRACE_PRINTF("config/reboot-fap fail %s\n",__func__);
      }
   }

   /* Failure during applying configuration */
   if ((status == MSM_CFM_FAILURE) && (cause == MSM_CAUSE_CFG_FAIL))
   {
      TRACE_PRINTF("Failure received for Dynamic configuration due to Configuration failure\n");
      if (cfmInfo.cfgType == MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS)
      {
         SmApplication::GetInstance().HandleLteNeighFreqDynCfgFailure(cfmInfo.action, cfmInfo.u.neighFreqIndx,cellIdx);
      }
      if (cfmInfo.cfgType == MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS)
      {
         SmApplication::GetInstance().HandleLteNeighCellDynCfgFailure(cfmInfo.action, cfmInfo.u.neighCellIndex,cellIdx);
      }
   }
   if(status == MSM_CFM_SUCCESS) 
   {
      TRACE_PRINTF("Success received for Dynamic configuration\n");
   }
   return;
}

void SmApplication::HandleLteNeighFreqDynCfgFailure(u8 action, u8 freqIdx, u16 cellIdx)
{
   TRACE_PRINTF("%s",__func__);

   MsmLteNeighFreqCfg    freqCfg;
   MsmLteNeighEutraFreq  *freqInfo = NULL;
   bool instanceFound = FALSE;
   u8 idx;

   msmGetNeighFreqEutraCfgParameters(&freqCfg,cellIdx);
   /* Get the freqCarrier from MSM global data structure */
   for (idx=1; idx<MAX_NUM_FREQ_CFG; idx++)
   {
      if (freqCfg.t.addNeighFreq[idx].eutranFreq.freqIndex == freqIdx)
      {
         freqInfo = &freqCfg.t.addNeighFreq[idx].eutranFreq;
         break;
      }
   }

   if ((action == MSM_DYN_ADD) || (action == MSM_ACT_MOD))
   {
      for (idx=0; idx<8; idx++)
      {
         if ((freqIdx == freqIndxMap[idx].instanceNumb) && (freqIndxMap[idx].inUse == TRUE))
         {
            instanceFound = TRUE;
            break;
         }
      }
      if (instanceFound == TRUE)
      {
         if (action == MSM_ACT_MOD)
         {
            neighFreqRollBack = TRUE;
            if(freqInfo != NULL)
            {
               rollBackInterFreqCarr(freqIdx,freqInfo,cellIdx);
            }
         }
      }
   }
   return;
}

void SmApplication::HandleLteNeighCellDynCfgFailure(u8 action, u8 cellIdx,u16 cellId)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmNeighCellCfg    cellCfg;
   MsmEUTRANeighCell  *eutraNbrCell = NULL;
   bool instanceFound = FALSE;
   u8 idx;

   msmGetNeighborListInUseEutraParameters(&cellCfg,cellId);
   /* Get the Nbrcell from MSM global data structure */
   for (idx=0; idx<MSM_MAX_NUM_NEIGH_CELLS; idx++)
   {
      if (cellCfg.t.neighAddCfg[idx].eutraCell.nrIndex == cellIdx)
      {
         eutraNbrCell = &cellCfg.t.neighAddCfg[idx].eutraCell;
         break;
      }
   }

   if ((action == MSM_DYN_ADD) || (action == MSM_ACT_MOD))
   {
      for (idx=0; idx<32; idx++)
      {
         if ((cellIdx == cellIndxMap[idx].instanceNumb) && (cellIndxMap[idx].inUse == TRUE))
         {
            instanceFound = TRUE;
            break;
         }
      }
      if (instanceFound == TRUE)
      {
         if(eutraNbrCell != NULL)
         {
            rollBackNbrCell(cellIndxMap[idx].mioObjInstance,eutraNbrCell,cellId);
            neighCellRollBack = TRUE;
         }
      }
   }
   return;
}

void SmApplication::rollBackInterFreqCarr
(
 u8 instance,
 MsmLteNeighEutraFreq *freqInfo,
 U16 cellIdx
 )
{
   TRACE_PRINTF("%s",__func__);

   MibAttributeValues attrs;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   MibDN neighFreqDn = MibDN::GenerateMibDN(fapLteDn,
         MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER,instance);
   stringstream qRxLevMinstr,tReselectionStr,toString;
   vector<string> qRxLevMin,tReselection,toString1;
   TRACE_PRINTF("\n##################################################\n");
   TRACE_PRINTF(" Values rolled back for neighbour frequency \n");
   TRACE_PRINTF("\n##################################################\n");
   printFreqValuesFilled(freqInfo) ;

   /* TR-196 Neighbour frequency parameters */
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_DL_EARFCN,
         (u32)freqInfo->earfcnDl);
   qRxLevMinstr << (s32)freqInfo->qRxLevMin;
   qRxLevMin.push_back(qRxLevMinstr.str());
   tReselectionStr << (u32)freqInfo->tReselection;
   tReselection.push_back(tReselectionStr.str());
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_QRX_LEVEL_MIN,qRxLevMin);
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA,tReselection);
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_CELL_RESELECT_PRIORITY,
         (u32)freqInfo->priority);
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XHIGH,
         (u32)freqInfo->threshXHigh);
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_THRESHOLD_XLOW,
         (u32)freqInfo->threshXLow);
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_PMAX,(s32)freqInfo->pMax);

   if(3 >= freqInfo->tReselectionSFMed)
   {
      attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_TRESELECTION_EUTRA_SF_MED,
            (u32)SmApplication::GetInstance().GetSmTr196Validator()->
            arrtReselectionSfInfo[freqInfo->tReselectionSFMed+1]);
   }
   if(30 >= freqInfo->qOffsetFreq)
   {
      attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_QOFFSETFREQ,
            (s32)SmApplication::GetInstance().GetSmTr196Validator()->
            arrqOffsetFreqInfo[freqInfo->qOffsetFreq+1]);
      toString << SmApplication::GetInstance().GetSmTr196Validator()->
         arrqOffsetFreqInfo[freqInfo->qOffsetFreq+1];
   }
   toString1.push_back(toString.str());
   attrs.AddAttribute(PARAM_ID_LTE_INTER_FREQ_QOFFSETFREQ,toString1);

   /* Propreitary parameters */
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_ALLOWD_MEAS_BW,
         (char *)SmApplication::GetInstance().GetSmTr196Validator()->
         arrAllowedMeasBandwidthInfo[freqInfo->measBandwidth])      ;
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_PRES_ANTENNA_PORT1,
         (u32)freqInfo->presAntennaPort1);
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_UL_EARFCN,
         (u32)freqInfo->earfcnUl);
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_QQUALMIN_R9,
         (s32)freqInfo->qQualMinRel9);
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_THRESHX_HIGHQ_R9,
         (u32)freqInfo->threshXHighQR9);
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_THRESHX_LOWQ_R9,
         (u32)freqInfo->threshXLowQR9);
   attrs.AddAttribute(PARAM_ID_LTE_X_RADISYS_INTER_FREQ_NEIGH_CELL_CONFIG,
         (char *)SmApplication::GetInstance().GetSmTr196Validator()->
         arrNeighCellConfigInfo[freqInfo->neighCellCfg]);
   GetMibCache().SetMibAttributesByDn(neighFreqDn,attrs, ENTITY_OAM);

   return ;
}

void SmApplication::rollBackNbrCell
(
 u8 instance,
 MsmEUTRANeighCell *nbrCell,
 u16 cellIdx
 )
{
   TRACE_PRINTF("%s\n",__func__);

   MibAttributeValues attrs;
   s32 qoffset,cio;
   std::string plmnId;
   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE,cellIdx);
   MibDN neighCellDn = MibDN::GenerateMibDN(fapLteDn,
         MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,instance);

   HandleLtePlmnIdUpdate(nbrCell, &plmnId);
   attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PLMNID,plmnId);
   attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CID,(u32)nbrCell->cid);
   attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_EARFCN,
         (u32)nbrCell->earfcnDl);
   attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PHY_CELLID,
         (u32)nbrCell->pci);
   if(30 >= nbrCell->qoffset)
   {
      qoffset = SmApplication::GetInstance().GetSmTr196Validator()->
         arrqOffsetFreqInfo[(nbrCell->qoffset)+1];
      attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_QOFFSET,qoffset);
   }
   if(30 >= nbrCell->cio)
   {
      cio = SmApplication::GetInstance().GetSmTr196Validator()->
         arrqOffsetFreqInfo[(nbrCell->cio)+1];
      attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CIO,cio);
   }
   attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_RS_TX_POWER,
         (s32)nbrCell->RSTxPower);
   attrs.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED,
         (u32)nbrCell->BlackListed);

   GetMibCache().SetMibAttributesByDn(neighCellDn,attrs, ENTITY_OAM);

   return;
}

void SmApplication::UpdateCellIndexMap
(
 u32 instance,
 int inUseInstance,
 MsmDynNeighCellCfg *lteNeighCellCfg
 )
{
   TRACE_PRINTF("%s\n",__func__);

   std::vector<u32> neighborLteCellSrc;
   u32 idx, maxCellEntries;
   MibDN neighCellDn;

   GetMibCache().GetMibAttribute(PARAM_ID_LTE_IN_USE_MAX_LTE_CELL,
         maxCellEntries);

   neighCellDn = MibDN::GenerateMibDN(
         MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,instance);
   GetMibCache().GetMibAttribute(PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC,
         neighborLteCellSrc);

   if (neighborLteCellSrc[instance] == MIB_OBJ_DELETED)
   {
      lteNeighCellCfg->actType = MSM_ACT_DEL;
      lteNeighCellCfg->t.delCfg.t.eutranCell.nrIndex = inUseInstance;
      TRACE_PRINTF("Deleting object at instance for TR-196 Neigh Cell %d\n",
            inUseInstance);
   }
   else
   {
      // Check the cellIndxMap if an entry exists already for this instance for
      // TR-196 or proprietary object 
      for (idx=0; idx<maxCellEntries; idx++)
      {
         if ((cellIndxMap[idx].inUse == TRUE) && (cellIndxMap[idx].instanceNumb
                  == inUseInstance))
         {
            lteNeighCellCfg->actType = MSM_ACT_MOD;
            TRACE_PRINTF("MSM ACT MOD");
            break;
         }
      }
      if (idx == maxCellEntries)
      {
         lteNeighCellCfg->actType = MSM_DYN_ADD;
         for (idx=0; idx<maxCellEntries; idx++)
         {
            if (cellIndxMap[idx].inUse == FALSE)
            {
               cellIndxMap[idx].inUse = TRUE;
               cellIndxMap[idx].instanceNumb = inUseInstance;
               cellIndxMap[idx].mioObjInstance = instance;
               break;
            } 
         }
      }
      lteNeighCellCfg->t.addModCfg.t.eutraCell.nrIndex = inUseInstance;
   }
}


void SmApplication::WaitforNRTUpdateCompleteAtMsm( u32 timeoutPeriod)
{
   TRACE_PRINTF("%s",__func__);

   if(IsTimerRunning(m_lteNeighCfgTimer))
   {
      DeleteTimer(m_lteNeighCfgTimer);
   }
   m_lteNeighCfgTimer = CreateTimer((const std::string&)"LteNeighCfg flag timer\
         timeout", u32(10), TimerEngineInterface::TIMER_START_NOW,
         TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void SmApplication::ReadIfPresent
(
 MibDN dn,
 MibAttributeId PARAM_ID,
 u32& value,
 u32 defaultValue
 )
{
   TRACE_PRINTF("%s",__func__);

   if(SmApplication::GetInstance().GetMibCache().IsMibAttributePresent(dn,
            PARAM_ID))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID,value);
   }
   else
   {
      value=defaultValue;
   }
}

void SmApplication::ReadIfPresent
(MibDN dn,
 MibAttributeId PARAM_ID,
 s32& value,
 s32 defaultValue
 )
{
   TRACE_PRINTF("%s",__func__);

   if(SmApplication::GetInstance().GetMibCache().IsMibAttributePresent(dn,
            PARAM_ID))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID,value);
   }
   else
   {
      value=defaultValue;
   }
}

void SmApplication::ReadIfPresent
(
 MibDN dn,
 MibAttributeId PARAM_ID,
 std::string& value,
 std::string defaultValue
 )
{
   TRACE_PRINTF("%s",__func__);

   if(SmApplication::GetInstance().GetMibCache().IsMibAttributePresent(dn,
            PARAM_ID))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID,value);
   }
   else
   {
      value=defaultValue;
   }
}

void SmApplication::ReadIfPresent
(
 MibDN dn,
 MibAttributeId PARAM_ID,
 std::vector<std::string>& value,
 std::vector<std::string> defaultValue
 )
{
   TRACE_PRINTF("%s",__func__);

   if(SmApplication::GetInstance().GetMibCache().IsMibAttributePresent(dn,
            PARAM_ID))
   {
      GetMibCache().GetMibAttribute(dn,PARAM_ID,value);
   }
   else
   {
      value = defaultValue;
   }
}

void SmApplication::HandleEnbLogLvlParameter(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmEnbLogLvlData lteLogLvlCfg;

   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);

   GetMibCache().GetMibAttribute(fapDn, PARAM_ID_LTE_ENB_L3LOG_LEVEL,
         lteLogLvlCfg.enbL3LogLvl);
   GetMibCache().GetMibAttribute(fapDn, PARAM_ID_LTE_ENB_L2LOG_LEVEL,
         lteLogLvlCfg.enbL2LogLvl);
   GetMibCache().GetMibAttribute(fapDn,PARAM_ID_LTE_ENBLOG_MASK,
         lteLogLvlCfg.enbLog_mask);
   GetMibCache().GetMibAttribute(fapDn, PARAM_ID_LTE_ENBLOG_REMOTE_LOGGING,
         lteLogLvlCfg.remoteLogin);

   if(!isDynCfg)
   {
      msmSetLogLvlParameter(&lteLogLvlCfg);
   }
   else
   {
      m_smmWaitForDynCfgRsp = TRUE;
      MsmSmmDynCfgReq((void*)&lteLogLvlCfg, MSM_LTE_LOG_LVL_PARAMETERS,cellIdx);
   }
   return;
}

void SmApplication::HandleRsysTpmParam(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);

   MsmRsysTpmCfg rsysTpmCfg;

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   if(!isDynCfg)
   {
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ENB_RSYS_TPM_TGT_RSRP,
            rsysTpmCfg.tgtRsrp);
      GetMibCache().GetMibAttribute(dn,
            PARAM_ID_LTE_ENB_RSYS_TPM_RSRP_ATTN_CONST, rsysTpmCfg.attnConstIdx);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ENB_RSYS_TPM_MIN_RSRP,
            rsysTpmCfg.minRsrp);
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_ENB_RSYS_TPM_MAX_RSRP,
            rsysTpmCfg.maxRsrp);
      msmSetRsysTpmCfgParameters(&rsysTpmCfg, cellIdx);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   return;
}

u32  SmApplication::FillIp
(
 std::vector<std::string> &ipString,
 u32 idx,
 Mmeiptype *mmeIp
 )
{
   TRACE_PRINTF("%s",__func__);

   IPAddress checkip;
   u32 ip;
   u8 ipv6[16] ={ 0};
   if(ipString.size() > idx)
   {
      checkip.Set(ipString.at(idx).c_str());
      if(checkip.CheckIfIPv6())
      {
         TRACE_PRINTF("IPV6Address readed %s",ipString.at(idx).c_str());
         mmeIp->ipv4pres=FALSE;

         if(checkip.ipv6.Get(ipv6))
         {
            memcpy(&mmeIp->mmeipv6,&ipv6,sizeof(ipv6));
            mmeIp->ipv6pres=TRUE;
            TRACE_PRINTF("%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x%x",ipv6[0],ipv6[1],ipv6[2],ipv6[3],ipv6[4],ipv6[5],ipv6[6],ipv6[7],ipv6[8],ipv6[9],ipv6[10],ipv6[11],ipv6[12],ipv6[13],ipv6[14],ipv6[15]);
            return TYPE_IPV6;
         }
      }
      else // in case of ipv4
      {
         mmeIp->ipv6pres=FALSE;
         ip = htonl(checkip.ipv4.Get());
         mmeIp->mmeipv4=ip;
         mmeIp->ipv4pres=TRUE;
         return TYPE_IPV4;
      }
   }
   return TYPE_INVALID;
}

void SmApplication::ResetIP( Mmeiptype *mmeIp, IpType type)
{
   if (TYPE_IPV4 == type)
   {
      mmeIp->mmeipv4=0;
      mmeIp->ipv4pres=FALSE;
   }
   else if (TYPE_IPV6 == type)
   {
      u8 ipv6[16]={0};
      memcpy(mmeIp->mmeipv6,&ipv6,sizeof(ipv6));
      mmeIp->ipv6pres=FALSE;
   }
   else if (TYPE_INVALID == type)
   {
      ResetIP(mmeIp,TYPE_IPV6);
      ResetIP(mmeIp,TYPE_IPV4);
   }
}

bool SmApplication::IsIpSet(std::string ip)
{
   std::string Ipv4Default("0.0.0.0");
   std::string Ipv6Default("0:0:0:0:0:0:0:0");
   return !((!ip.compare(Ipv4Default)) || (!ip.compare(Ipv6Default)));
}

void SmApplication::FillAllUtraFdd(u16 cellIdx)
{
   TRACE_PRINTF("%s %d",__func__,__LINE__);

   u32                 neighborEnable = 0;
   string              s_duplexMode;
   MsmLteNeighFreqCfg  lteNeighFreqCfg;
   MsmLteNeighUtraFreq *utranFreq;
   std::vector<string> UtraFddCfgList;
   u32                 numUtraFddFreq = 0;

   MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   for(u32 idx=0 ; idx < MAX_UTRA_NEIGHBOR_FDD_FREQ ; idx++)
   {
      MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();
      MibDN dnobj = MibDN::GenerateMibDN(fapLteDn,
            MIB_OBJECT_CLASS_UTRA_UTRAN_FDD_FREQ, idx);

      if(m_mib.IsMibObjectPresent(dnobj))
      {
         GetMibCache().GetMibAttribute(dnobj,PARAM_ID_LTE_UTRA_FDD_ENABLE_IRAT,
               neighborEnable);
         if( neighborEnable )
         {
            utranFreq = &(lteNeighFreqCfg.t.addNeighFreq[idx].utranFreq);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_FDD_ENABLE_IRAT, utranFreq->enable );
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_FDD_CARRIER_ARFCN, utranFreq->arfcnDl);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_Q_RX_LEV_MIN_IRAT, UtraFddCfgList);
            SmApplication::GetInstance().GetSmTr196Validator()->ExpandString
               (UtraFddCfgList);
            utranFreq->qRxLevMin = atoi(UtraFddCfgList.at(0).c_str());
            UtraFddCfgList.clear();

            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_Q_QUAL_MIN_IRAT, UtraFddCfgList);
            SmApplication::GetInstance().GetSmTr196Validator()->ExpandString
               (UtraFddCfgList);
            utranFreq->pQualMin = atoi(UtraFddCfgList.at(0).c_str());
            UtraFddCfgList.clear();

            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_CELL_RESELECT_PRIORITY_IRAT,
                  utranFreq->priority);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_THRESH_XLOW_IRAT, utranFreq->threshXlow );
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_THRESH_XHIGH_IRAT, utranFreq->threshXhigh);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_PMAX, utranFreq->pMaxUtra);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_FDD_CARRIER_UL_ARFCN, utranFreq->arfcnUl);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_QOFFSET_IRAT, utranFreq->offsetFreq);
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_DUPLEXMODE_IRAT, s_duplexMode);
            SmApplication::GetInstance().GetSmTr196Validator()->
               GetLteStringenums(SmApplication::GetInstance().
                     GetSmTr196Validator()->arrduplexModeInfo, s_duplexMode,
                     m_posu8,2);
            utranFreq->duplexModeUtra = m_posu8;
            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_THRESHX_HIGHQ_R9_IRAT,
                  utranFreq->threshXHighQR9);

            GetMibCache().GetMibAttribute(dnobj,
                  PARAM_ID_LTE_UTRA_THRESHX_LOWQ_R9_IRAT,
                  utranFreq->threshXLowQR9);
            numUtraFddFreq++;
         }
      }
   }
   lteNeighFreqCfg.numUtraFreq = numUtraFddFreq;
   lteNeighFreqCfg.maxUtraFreqEntries = MAX_UTRA_NEIGHBOR_FDD_FREQ;
   msmSetNeighFreqUtraCfgParameters(&lteNeighFreqCfg,cellIdx);
}

#ifdef TIP_OAM
void SmApplication::ReadS1UCfgParameters(MibDN fapDn, MsmS1UCfg &s1uCfg)
{
   GetMibCache().GetMibAttribute(fapDn, PARAM_ID_GTPU_ECHO_INTERVAL, s1uCfg.gtpuEchoIntvl);
   printf("gtpuEchoIntvl:%d\n", s1uCfg.gtpuEchoIntvl);
}

void SmApplication::HandleS1UCfg(u16 cellIdx,bool isDynCfg)
{
   TRACE_PRINTF("%s\n",__func__);
   MsmS1UCfg s1uCfg;

   MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, cellIdx);

   if(!isDynCfg)
   {
      ReadS1UCfgParameters(fapDn, s1uCfg);
      msmSetS1UParameters(&s1uCfg);
   }
   else
   {
      TRACE_PRINTF("Dynamic configuration not supported, parameters updation \
            will occur after reboot");
   }
   printf("\n\necho tmr:%d\n\n", s1uCfg.gtpuEchoIntvl);
   return;
}
#endif

#ifdef LTE_ADV
void SmApplication::HandleCaParams(u16 cellIdx, bool isDynCfg)
{
   TRACE_PRINTF("%s",__func__);

   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP,cellIdx);

   MsmCAGenCfg caGenCfg;

   /*For Initial configuration*/
   if(!isDynCfg)
   {
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_CA_ENABLE,caGenCfg.isCaEnabled);
#ifdef LTE_ADV_UECAP
      GetMibCache().GetMibAttribute(dn, PARAM_ID_LTE_X_RADISYS_CA_FREQ_CONTG,caGenCfg.isCellFreqCont);
#endif

      if(msmSetCAParameters(&caGenCfg,cellIdx)!= ROK)
      {
         TRACE_PRINTF("%s:%d Failed to set CA enable flag",__FUNCTION__,__LINE__);	
      }
      printf("\n FROM OAM ca flag = %d\n, ca_freq_cont = %d\n",caGenCfg.isCaEnabled,caGenCfg.isCellFreqCont);
   }
   else
   {
      TRACE_PRINTF("Dynamic update of CA ENABLE flag configuration");
   }
   return;
}
#endif
