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

/********************************************************************20**
  
     Name:     Stack Manager Application - SmApplication.cpp

     Type:     Cpp implementation file

     Desc:     Implements the Stack manager Application for the Mib client 

     File:     SmApplication.c

     Sid:      
  
     Prg:      ksingh
  
*********************************************************************21*/

#ifndef __SmApplication_h_
#define __SmApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <FapUserLimits.h>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/TimerInterface.h>
#include <system/Trace.h>
#include <messaging/transport/KpiMessageManager.h>
#include <system/ManagedObject.h>
#include <platform/ManagedFing.h>
#include <messaging/transport/SingleThreadedAppWithAttrCache.h>
#include <comms/IPv6Address.h>
#include <comms/IPAddress.h>
#include <system/KpiCollector.h>
#include <queue>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SmKpiCollector.h"
#include "SmTr196Validator.h"
#include "KpiCollector.h"
#include "wr_msm_common.h"

#define NUM_MAX_PLMN_DIGIT     6
#define NUM_MAX_PLMN           6
#define NUM_QOFFSET_VAL 31
#define QOFFSET_FREQ {-24,-22,-20,-18,-16,-14,-12,-10,-8,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,8,10,12,14,16,18,20,22,24}
#define MAX_NEIGHBOR_CELLS 16
#define MAX_EUTRA_NEIGHBOR_FREQ 8
#define MAX_UTRA_NEIGHBOR_FDD_FREQ 16
#define MAX_GERAN_NEIGHBOR_CELLS 16
#define MAX_GERAN_NEIGHBOR_FREQ 16
#define MAX_TDS_CDMA_UTRAN_TDD_FREQ 16
#define MAX_TDS_CDMA_UTRAN_TDD_CELL 32
#define MAX_GERAN_NEIGHBOR_CELLS_IN_USE 32
#define FAP_CAPACITY_MAX_UE_SERVED 32
#define ADMIN_CHANGE 0
#define IP_CHANGE 1
#define MAX_UMTS_OBJ 16
#define MAX_UMTS_IN_USE_OBJ 32
#define PLMN_ID_CFGD 1
#define MME_IP_CFGD 2
#define TAC_CFGD 4
#define CELL_ID_CFGD 8
#define PCI_CFGD 16
#define EARFCN_CFGD 32
#define BASIC_CFG_CFGD (PLMN_ID_CFGD | MME_IP_CFGD | TAC_CFGD | CELL_ID_CFGD | PCI_CFGD | EARFCN_CFGD)

using namespace boost;

typedef map<u32 ,pair<u32 ,u32> > subsIdRanges;

//class EmergencyCallPriorityTest;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
namespace Sm
{
   class SmApplication : public threeway::SingleThreadedAppWithAttrCache, public threeway::KpiCollector
   {
      // for unit tests

      public:
         static SmApplication& GetInstance();
         virtual ~SmApplication();

         shared_ptr<SmKpiCollector> GetSmKpiCollector() const { RSYS_ASSERT(m_smKpiCollector != NULL); return m_smKpiCollector; };
         shared_ptr<SmTr196Validator> GetSmTr196Validator() const { RSYS_ASSERT(m_smTr196Validator != NULL); return m_smTr196Validator; };

         //Alarms
         shared_ptr<threeway::Messenger> GetSmMessenger() const { RSYS_ASSERT(m_messenger != NULL); return m_messenger; };

         void sendNotification(void);
      private:

         /**
          * Implement base class hooks relating to application start-up.
          */
         virtual void InitialiseApp();
         virtual void StartApp();
         virtual void InitialiseSubsIds();
         bool IsDynamicConfig(u16 subId, bool *pushDynCfg);
         virtual std::vector<MessagingEntity> GetSupportedEntities();
         virtual void GetSubscriptions(std::vector<threeway::SubscriptionDescriptor>& subscriptions);
         threeway::TimerHandle m_logTimerHandle;
         typedef enum
         {
            SI_LTE_GERAN_NGH_PARAMETERS=1,
            SI_LTE_ADMIN_STATE_CHANGE=2,
            SI_LTE_OP_STATE_CHANGE=3,
            //SI_LTE_SON_CFG_PRES_PARAMETERS=4,
            SI_LTE_PRACH_CONFIG_COMMON_PARAMETERS=5, /* Done */
            //SI_LTE_CELL_CARRIER_PARAMETERS=6,
            SI_LTE_ENODEB_IP_PARAMETERS=7,
            SI_LTE_RACH_CONFIG_COMMON_PARAMETERS=8, /* Done */
            SI_LTE_PDSCH_CONFIG_COMMON_PARAMETERS=9,  /* Done */
            SI_LTE_UL_POWER_CONTROL_COMMON_PARAMETERS=10, /* Done */
            SI_LTE_UL_FREQUENCY_INFO_PARAMETERS=11, /* Done */
            SI_LTE_CELL_SIB3_CONFIG_GROUP_PARAMETERS=12,  /* Done */
            SI_LTE_CELL_SIB1_CONFIG_GROUP_PARAMETERS=13, /* Done */
            SI_LTE_DRX_CONFIG_PARAMETERS=14,
            SI_LTE_CELL_MEAS_CONFIG_PARAMETERS=15,
            SI_LTE_ADD_CELL_CONFIG_PARAMETERS=16,
            SI_LTE_SM_CELL_CONFIG_PARAMETERS=17,
            SI_LTE_CELL_MIB_CONFIG_PARAMETERS=18,
            SI_LTE_MAC_SCH_CONFIG_PARAMETERS=19,
            SI_LTE_ANTENNA_COMMON_CONFIG_PARAMETERS=20,
            SI_LTE_PDSCH_CONFIG_DEDICATED_PARAMETERS=21,
            SI_LTE_PUSCH_BASIC_CFG_COMMON_PARAMETERS=22, /* Done */
            SI_LTE_PUSCH_REF_SIGNAL_CFG_PARAMETERS=23,  /* Done */
            SI_LTE_PUCCH_CFG_COMMON_PARAMETERS=24,   /* Done */
            SI_LTE_SRS_CFG_COMMON_PARAMETERS=25,  /* Done */
            SI_LTE_RAB_DRB_POLICY_CFG_GRP_PARAMETERS=26,
            SI_LTE_RAB_SRB1_POLICY_CFG_GRP_PARAMETERS=27,
            SI_LTE_RAB_SRB2_POLICY_CFG_GRP_PARAMETERS=28,
            SI_LTE_UE_TIMER_CONSTANTS_PARAMETERS=29,  /* Done */
            SI_LTE_CELL_EAID_CFG_GRP_PARAMETERS=30,
            SI_LTE_CELL_SIB9_CFG_GRP_PARAMETERS=31,   /* Done */
            SI_LTE_CQI_PERIODIC_REPORT_CFG_PARAMETERS=32,
            SI_LTE_UTRA_NEIGH_FREQ_CFG_PARAMETERS=33,
            SI_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS=34,
            SI_LTE_EUTRAN_NEIGHBORLIST_PARAMETERS=35,
            SI_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS=36,
            SI_LTE_UTRA_NEIGHBORLIST_IN_USE_PARAMETERS=37,
            SI_LTE_SIB5_INTER_FREQ_CARRIER_INFO_PARAMETERS=38,
            SI_LTE_CELL_SIB6_CONFIG_GROUP_PARAMETERS=39,  /* Done */
            SI_LTE_ENB_PROTO_CFG_PARAMETERS=40,
            SI_LTE_RIM_PARAMETERS=41,
            SI_LTE_FACTORY_PARAMETERS=42,
            SI_ENB_IP_ADDRESS=43,
            SI_LTE_AC_BARRING_INFO_PARAMETERS=44, /* Done */
            SI_LTE_SELF_CONFIG_PARAMETERS=45,
            SI_LTE_REM_CONTROL_PARAMETERS=46,
            SI_LTE_REM_SCAN_PARAMETERS=47,
            SI_LTE_POWER_OFFSET_PARAMETERS=48,
            SI_LTE_CELL_SCHD_POWER_PARAMETERS=49,
            SI_LTE_FAP_CONTROL_PARAMETERS=50,
            SI_LTE_PRB_ALLOCATION_PARAMETERS=51,
            SI_LTE_SIB4_CSG_INFO_PARAMETERS=52, /* Done */
            SI_LTE_RRM_TDD_PARAMETERS=53,
            SI_LTE_TDD_PARAMETERS=54, /* Done */
            SI_LTE_X2_CONFIG_PARAMETERS=55,
            SI_LTE_SCTP_CONFIG_PARAMETERS=56,
            SI_LTE_PCCH_CONFIG_COMMON_PARAMETERS=57,  /* Done */
            SI_LTE_CELL_UL_SCHD_CONFIG_PARAMETERS=58,
            SI_LTE_CELL_DL_SCHD_CONFIG_PARAMETERS=59,
            SI_LTE_MS_CELL_CFG_REQ_PARAMETERS=60,
            SI_LTE_DBG_PARAMETERS=61,
            SI_LTE_UL_ALLOC_INFO_CB_PARAMETERS=62,
            SI_LTE_PROC_TIMER_CFG_PARAMETERS=63,
            SI_LTE_SPS_PARAMETERS=64,
            SI_LTE_NBR_CELL_SRC_PARAMETERS=65,
            SI_LTE_NBR_FREQ_SRC_PARAMETERS=66,
            SI_PM_PARAMETERS=67,
            SI_REM_UTRA_CONTROL_PARAMETERS=68,
            SI_REM_SCAN_UTRA_PARAMETERS=69,
            SI_FREQUENT_FAULT_PARAMETERS=70,
            SI_CDMA_BAND_CLASS_PARAMETERS=71,
            SI_CDMA_MOBILITY_PARAMETERS=72,
            SI_BARRING_CFG_1XRTT=73,   /* Done */
            SI_CDMA_1XRTT_NGH_CELL=74,
            SI_SIB8_PARAMETERS=75,   /* Done */
            SI_LTE_SIB7_PARAMETERS=76, /* Done */
            SI_LTE_CSFB_GERAN_PARAMETERS=77,
            SI_LTE_TD_SCDMA_NGH_PARAMETERS=78,
            SI_LTE_UTRA_NEIGH_PARAMETERS=79,
            SI_LTE_CELL_SIB1_PLMN_SRC_PARAMETERS=80,
            SI_EUTRA_NBR_FREQ_OBJ=81,
            SI_EUTRA_RSYS_NBR_FREQ_OBJ=82,
            SI_EUTRA_NBR_CELL_OBJ=83,
            SI_EUTRA_RSYS_NBR_CELL_OBJ=84,
            SI_LTE_CNM_PARAMETERS=85,
            SI_TIME_ALGMT_CFG_PARAMETERS=86,  /* Done */
            SI_LTE_DYNAMIC_CFI_PARAMETERS=87,
            SI_CSFB_CFG_PARAMETERS=88,
            SI_LTE_REM_EARFCN_RSSI_PARAMETERS=89,
            SI_LTE_ACCESS_MNGMNT_PARAMETERS=90,
            SI_LTE_TRANSMISSION_MODE_CONFIG=91,
            S1_LTE_TENB_STATS_CFG=92,
            SI_LTE_REM_SCAN_ATTRIBUTES=93,
            SI_LTE_REM_SCAN_CELL_CNT_ATTRIBUTES=94,
            SI_WCDMA_REM_SCAN_ATTRIBUTES=95,
            SI_WCDMA_REM_SCAN_CELL_CNT_ATTRIBUTES=96,
            SI_LTE_SEC_GW_PARAMETERS=97,
            SI_LOG_UPLOAD_INTERVAL=98,
            SI_LTE_LOG_LVL_PARAM=99,
            SI_LTE_FREQ_SYNC_PARAMETERS=100,
            SI_LTE_RSYS_TPM_PARAMETERS=101,
            SI_DUPLEX_MODE=102,
            SI_EUTRA_NBR_FREQ_PARAMS=103,
            SI_EUTRA_NBR_FREQ_PARAMS_END=110,
            SI_NBR_CELL_PARAMETERS=135,
            SI_NBR_CELL_PARAMETERS_END=166,
            SI_NBR_CELL_IN_USE_PARAMETERS=167,
            SI_NBR_CELL_IN_USE_PARAMETERS_END=198,
            SI_TDS_CDMA_UTRAN_TDD_FREQ_PARAMETERS=199,
            SI_TDS_CDMA_UTRAN_TDD_FREQ_PARAMETERS_END=230,
            SI_TDS_CDMA_UTRAN_TDD_CELL_PARAMETERS=231,
            SI_TDS_CDMA_UTRAN_TDD_CELL_PARAMETERS_END=262,
            SI_NBR_UTRA_FDD_START=263,
            SI_NBR_UTRA_FDD_START_END=278,
            SI_NBR_UMTS_PARAMETERS=279,
            SI_NBR_UMTS_PARAMETERS_END=294,
            SI_NBR_UMTS_IN_USE_PARAMETRERS=295,
            SI_NBR_UMTS_IN_USE_PARAMETRERS_END=326,
            SI_NBR_GERAN_FREQ_PARAMETERS=327,
            SI_NBR_GERAN_FREQ_PARAMETERS_END=342,
            SI_NBR_GERAN_X_RSYS_FREQ_PARAMETERS=343,
            SI_NBR_GERAN_X_RSYS_FREQ_PARAMETERS_END=358,
            SI_NBR_GERAN_CELL_PARAMETERS=359,
            SI_NBR_GERAN_CELL_PARAMETERS_END=374,
            SI_NBR_GERAN_X_RSYS_CELL_PARAMETERS=375,
            SI_NBR_GERAN_X_RSYS_CELL_PARAMETERS_END=390,
            SI_NBR_GERAN_CELL_IN_USE_PARAMETERS=391,
            SI_NBR_GERAN_CELL_IN_USE_PARAMETERS_END=422,
            SI_REM_LTE_CELL_PARAMETERS=423,
            SI_REM_LTE_CELL_PARAMETERS_END=438,
            SI_REM_WCDMA_CELL_PARAMETERS=439,
            SI_REM_WCDMA_CELL_PARAMETERS_END=454,
            SI_CELL_PLMN_LIST_PARAMETERS=455,
            SI_CELL_PLMN_LIST_PARAMETERS_END=461,
            SI_LTE_NBR_FREQ_NUM_INSTNCE_PARMATERS=462,
            SI_FAP_REM_SCAN_ATTRIBUTES=463,
            SI_LTE_GOST_CFG_PARAMETERS = 464,
#ifdef TIP_OAM
            SI_LTE_SIU_PARAMETERS = 400,
#endif
#ifdef LTE_ADV
            SI_LTE_CA_PARAMS=465,
            /*Should be the last enum value*/
            SI_LTE_MESSENGER_CONFIGURATION_COMPLETE=466
#else
            /*Should be the last enum value*/
            SI_LTE_MESSENGER_CONFIGURATION_COMPLETE=467
#endif
         } SmSubscriptionIds;
   
         typedef void (SmApplication:: *subHdlr)(u16 cellIdx, bool isDynCfg);
         typedef std::map<u16, subHdlr> fctnPtrMap;
         fctnPtrMap hdlrMap;

         void HandleTimerExpiry(shared_ptr<threeway::TimerExpiry> expiredTimer);

         /**
          * Default constructor.  Private as it's a singleton.
          */
         SmApplication();
         void HandleLteSubscriptions(u16 subscribs);
         void HandleLteDeleteSubscriptions(u16 subscribs, string objName);
         char * GetMibObjectInstanceNum(string objClass);
         void HandleLteAdminStateChange(u16, bool);
         void HandleLteDynamicConfiguration();
         void HandleLteGenericParameters();
         void HandleLtePrachCfgCommonParameters(u16, bool);
         void ReadLteeNodeBIPParameters(MibDN,MsmLteeNodeBIPparams *);
         void HandlerEmpty(u16, bool);
         void HandleLteeNodeBIPParameters(u16, bool);
         void HandleLteRachConfigCommonParameters(u16, bool);
         void HandleLtePdschConfigCommonParameters(u16, bool);
         void HandleLteUlPwrCtrlCommonParameters(u16, bool);
         void HandleLteULFrequencyInfoParameters(u16, bool);
         void HandleLteCellSib3CfgGroupParameters(u16, bool);
         void HandleLteCellSib1CfgGroupParameters(u16, bool);
         void ReadLteDrxCfgParameters(MibDN, MsmLteDrxCfgParams *);
         void HandleLteDrxCfgParameters(u16, bool);
         void HandleLteCellMeasCfgGrpParameters(u16, bool);
         void ReadAddCellCfgParameters(MibDN,MsmLteAddCellCfg *);
         void HandleLteAddCellCfgParameters(u16, bool);
         void ReadLteSmCfgParameters(MibDN,MsmLteSmCellCfg *);
         void HandleLteSmCfgParameters(u16, bool);
         void HandleLteFreqSyncParameters(u16, bool);
         void HandleLteCellMibCfgParameters(u16, bool);
         void ReadLteMacSchCfgParameters(MibDN,MsmLteMAC_SCH_Config *);
         void HandleLteMacSchCfgParameters(u16, bool);
         void HandleLteAntennaCommonCfgParameters(u16, bool);
         void HandleLtePdschCfgDedicatedParameters(u16, bool);
         void HandleLtePuschBasicCfgCommonParameters(u16, bool);
         void HandleLtePuschRefSignalCfgParameters(u16, bool);
         void HandleLtePucchCfgCommonParameters(u16, bool);
         void HandleLteSRSCfgCommonParameters(u16, bool);
         void HandleLteRimParameters(u16,bool);
         void HandleCellPlmnListParameters(u16, bool);
         void HandleLteRabPolicyCfgGrpParameters(u16, bool);
         void ReadLteSrb1PolicyCfgGrpParameters(MibDN,MsmLteRabPolicyCfgGrp *);
         void HandleLteSrb1PolicyCfgGrpParameters(u16, bool);
         void ReadLteSrb2PolicyCfgGrpParameters(MibDN,MsmLteRabPolicyCfgGrp *);
         void HandleLteSrb2PolicyCfgGrpParameters(u16, bool);
         void HandleLteUeTimerConstantsParameters(u16, bool);
         void HandleLteCellEAIDCfgGrpParameters(u16, bool);
         void HandleLteCellSib9CfgGrpParameters(u16, bool);
         void ReadLteCQIPeriodicReportCfgParameters(MibDN, MsmLteCQIPeriodicReportCfg *);
         void HandleLteCQIPeriodicReportCfgParameters(u16, bool);
         void HandleLteNeighFreqCfgParameters(u16 subscribs);
         void HandleLteNeighFreqMIOParams(u16 subscribs, u8 instance,bool isDynCfg,u16 cellIdx);
         void HandleLteRsysNeighFreqMIOParams(u16 subscribs, u8 instance);
         void HandleLteNeighCellCfgParameters(u16 subscribs,u8 instance,bool isDynCfg,u16 cellIdx);
         void fillLteDbgParameters(MsmLteDbgParams &lteDbgParams);
         void FillNeighCellCfgParameters();
         bool FillServCarrFreqInfo(MibDN, MsmLteNeighEutraFreq *freqInfo);
         void FillEutraNeighCellCfgParameters(u16 cellIdx);
         void FillUtraNeighCellCfgParameters(u16);
         void FillEutraCfgdCells(MsmNeighCellCfg *lteNeighCellCfg, u8 *idx, u16 cellIdx);
         void FillUtraCfgdCells(MsmNeighCellCfg *utraNeighCellCfg, u8 *idx, u8 &numUtraCfgdCells, u16 cellIdx);
         void FillTdScdmaCellCfgParameters(u16);
         void FillRemLteScannedCells(MsmNeighCellCfg *lteNeighCellCfg, u8 *idx, u8 *numRemLteScanCells);
         void FillRemWcdmaScannedCells(MsmNeighCellCfg *lteNeighCellCfg, u8 *idx, u8 *numRemWcdmaScanCells);
         void readEutraParameters(MibDN dn,MsmEUTRANeighCell *eutraNeighCel);
         void fillEutraInUseNibr(MibDN dn ,MsmEUTRANeighCell eutraNeighCel);
         void FillNeighCellInUseCells(MsmNeighCellCfg *lteNeighCellCfg);
         void HandleLteNeighCellCfgInUseParameters(u16 subscribs);
         void HandleLteNeighCellMIOParameters(u16 subscribs);
         void HandleLteRsysNeighCellMIOParameters(u16 subscribs);
         void HandleLteCellEntryParameter();
         void HandleLteCnmParameters(u16  cellIdx, bool isDynCfg);
         void HandleTenbStatsCfgParams(u16 cellIdx, bool isDynCfg);
         void HandleLteGeranCellEntryParameter();
         void FillGeranNeighFreqParameters(u16 cellIdx);
         void HandleNeighUmtsInUseMIOParameters(u32 index);
         void HandleLteNeighCellInUseParameters( u32 index);
         void HandleLteUtraFddNeighCellParameters(u32 index);
         void HandleLteGeranFreqEntryParameter();
         void HandleLteNeighGeranXRsysCellMIOParameters(u16 subscribs);
         void HandleLteGeranXRsysCellEntryParameter();
         void HandleLteNeighGeranXRsysFreqMIOParameters(u16 subscribs);
         void HandleLteGeranXRsysFreqEntryParameter();
         void HandleLteSib5InterFreqCarrierInfoParameters();
         void HandleLteCellSib6CfgGroupParameters(u16, bool);
         void HandleLteEnbProtoCfgParameters(u16,bool);
         void HandleLteRemEarfcnAndRSSIParameters(u16, bool);
         void HandleMessengerFactoryLteParameters();
         void HandleEnodebIPAddress(u16 cellIdx,bool isDynCfg);
         void HandleLteAcBarringInfoParameters(u16, bool);
         void HandleLteSelfConfigParameters(u16, bool);
         void HandleLteRemControlParameters();
         void HandleLteRemScanParameters();
         void HandleLteTunnelInfoParameters();
         void HandleLtePowerOffsetParameters(u16, bool);
         void HandleLteFapControParameters(U16,bool);
         void HandleLtePRBallocationParameters(u16,bool);
         void HandleLteSib4CsgInfoParameters(u16, bool);
         void HandleLteRrmTddParameters(u16,bool);
         void HandleLteTddParameters(u16, bool);
         void HandleLteX2ConfigParameters();
         void HandleLteSctpConfigParameters(u16,bool);
         void HandleLtePcchConfigCommonParameters(u16, bool);
         void HandleLteCellUlSchdCfgGrpParameters(u16, bool);
         void HandleLteCellDlSchdCfgGrpParameters(u16 cellIdx, bool isDynCfg);
         void HandleLteMsCellCfgReqParameters(u16 cellIdx, bool isDynCfg);
         void HandleLteDbgParameters(u16 cellIdx, bool isDynCfg);
         void HandleLteUlAllocInfoCbParameters(u16 cellIdx, bool isDynCfg);
         void HandleLteProcTimerCfgParameters(u16 cellIdx, bool isDynCfg);
         void FillTdScdmaUtranFreqParameters(u16 cellIdx);
         void HandleAccessManagementParameters(u16, bool);
         void FillNeighUmtsInUseMIOParameter();
         void HandleDynamicIPConfigChange(MsmLteeNodeBIPparams *lteeNodeBIPparams);
         void ReadA1Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadA2Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadA3Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadA4Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadA5Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadB2Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadUtraB2Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadGeranB2Event(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadCDMAMeasCfgParam(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadUTRAMeasCfgParam(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadEutraMeasCfgParam(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadSpeedMeasCfgParam(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void HandleLteEutraPlmnId(MsmNeighCellCfg *lteNeighCellCfg, u32 index);
         void HandleLteUtraPlmnId(MsmNeighCellCfg *lteNeighCellCfg, u32 index);
         void HandleLteEutraPlmnIdList(MsmNeighCellCfg *lteNeighCellCfg, u32 index, u32 numcells);
         void HandleLteUtraPlmnIdList(MsmNeighCellCfg *lteNeighCellCfg, u32 index, u32 numcells);
         void HandleTunnelPlmnId(MsmLteTunnelInfoParams *lteTunnelInfoParams);
         void HandleLtePlmnIdUpdate(MsmEUTRANeighCell *eutraCellCfg, std::vector<std::string> *plmnIdList);
         void dumpNbrMsmInfo(MsmEUTRANeighCell* eutraCell);
         void FillPlmn(MsmLtePlmnId *plmn,std::string plmnId);
         void GetPlmn(MsmLtePlmnId plmn,std::string &plmnId);
         void ReadUtraInUseParameters(MibDN dnobj,MsmUtraNeighCell *utranCell);
         void HandlePerfMgmtParameters(u16 cellIdx, bool isDynCfg);
         void HandleGostCfgParams(u16 cellIdx, bool isDynCfg);
         void HandleLteDynamicCfiParameters(u16, bool);
         void HandleRemUtraControlParameters();
         void HandleRemScanUtraParameters();
         void HandleFrequentFaultMgmtParameters(u16 cellIdx, bool isDynCfg);
         void FillCdmaBandClassParameters(u16 cellIdx);
         void HandleCdmaMobilityParameters(u16 cellIdx, bool isDynCfg);
         void HandleBarringConfig1xRTTCfg(u16, bool);
         void FillCDMA1xNeighCell(u16 cellIdx);
         void HandleSib8Parameters(u16, bool);
         void HandleCsfbCfgParameters(u16, bool);
         void HandleTimeAlgmtCfgParameters(u16, bool);
         void HandleLteSpsParameters(u16 cellIdx, bool isDynCfg);
         void HandleLteTMParameters(u16, bool);
         void HandleLteCellSchdPowerParameters(u16, bool);
         void HandleSib7CfgParameters(u16, bool);
         void HandleCsfbGeranCfgParameters(u16, bool);
         void ReadCsfbGeranCfgParameters(MibDN dn,MsmLteCsfbGeranCfg &csfbToGeranCfg);
         void ReadMeasGERANPeridRptCfg(MibDN, MsmLteCellMeasCfgGrp*);
         void ReadMeasQtyCfgParam(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void ReadMeasGapParam(MibDN, MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp);
         void HandleTdsCdmaUtranTddFreqParameters();
         void HandleTdsCdmaUtranTddCellParameters();
         void HandleLtePlmnId(MsmLtePlmnId *ltePlmnId, u32 index, string plmnIdParameter);
         void HandleLtePlmnIdList(MsmNeighCellCfg *lteNeighCellCfg, u32 index, u32 numcells, string plmnIdParameter);
         void UpdateNbrCellPlmnId(MsmEUTRANeighCell *lteNeighCellCfg, std::string plmnidvalue);
         u32 FillNeighFreqCarrByInstance(MibDN dn,u8 instance, MsmLteNeighEutraFreq *freqInfo);
         u32 FillRsysNeighFreqCarrByInstance(u8 instance, MsmLteNeighEutraFreq *freqInfo);
         void printFreqValuesFilled(MsmLteNeighEutraFreq *freqInfo);
         bool isUpdateFrmSON();
         void HandleRemScanStatus(u16, bool);
         bool isStackStart();
         s32 GetGeranInUseInstanceNbr(std::string geranPlmnId , u32 geranCi, u16 cellIdx);
         s32 getEutraInuseInstanceNbr(MibDN dn, std::string ,u32);
         void ReadUtraParameters(MibDN dnobj, MsmUtraNeighCell *utraCell);
         void readRemLteParameters(MibDN dn,MsmEUTRANeighCell *eutraNeighCel);
         void readRemUmtsParameters(MibDN dn,MsmUtraNeighCell *utraNeighCel);
         bool IsAllParametersSet(MibDN remDN);
         void fillUtraInUseNbr(MibDN , MsmUtraNeighCell );
         void fillAllNeighUmtsMIOParameters();
         void FillAllNeighLteMIOParameters();
         void FillAllRemLteMIOParameters();
         bool LteNRTUpdateCompleteAtMsm();
         bool UtraFddNRTUpdateCompleteAtMsm();
         void WaitforNRTUpdateCompleteAtMsm(u32);
         void LteNeighInuseFillDefaultVal(MsmEUTRANeighCell *ptr);
         bool EntireNRTUpdateCompleteAtMsm();
         bool UmtsNRTUpdateCompleteAtMsm();
         bool GsmNRTUpdateCompleteAtMsm();
         bool IsAllMandatoryParametersSet(MibDN);
         void ReadEutraInuseParameters(MibDN inUsednobj,MsmEUTRANeighCell *eutraCell);
         void updateGeranInUseInstance(MibDN gsmDn,MsmLteGERANNeighCell *geranCellCfg);
         void FillAllGSMNbrToInUse();
         void UpdateGSMNbrToMsm(u16 cellIdx);
         void FillAllUtraFdd(u16);
         void dumpGSMNbrMsmInfo(MsmLteGERANNeighCell* geranCell);
         void FillGSMToMsmByInstance(MibDN, u32 instance,MsmLteGERANNeighCell* geranCell, u16 cellIdx, u32& numGeranCells);
         void ReadIfPresent(MibDN , MibAttributeId ,  u32&,u32);
         void ReadIfPresent(MibDN , MibAttributeId , s32&,s32);
         void ReadIfPresent(MibDN , MibAttributeId , std::string&,std::string);
         void ReadIfPresent(MibDN , MibAttributeId , std::vector<std::string>&,std::vector<std::string>);
         void HandleEnbLogLvlParameter(u16, bool); 
         void startPeriodicRemScan();
         void PeriodicRemHandler();
         void HandleRsysTpmParam(u16, bool); 
         void HandleNumOfCellsCfgParam(u16, bool);
#ifdef TIP_OAM
         void HandleS1UCfg(u16 cellIdx,bool isDynCfg);
         void ReadS1UCfgParameters(MibDN fapDn, MsmS1UCfg &S1uCfg);
         void GetReportAmount(MibDN dn, string &s_reportAmount); 
#endif
#ifdef LTE_ADV
         void HandleCaParams(u16, bool);
#endif
         s16 getCellIdx(u16);
         void ReadLtePrachCfgCommonParameters(MibDN fapLteDn,MsmLtePrachCfgCommon &ltePrachCfgCommon);
         void ReadRachConfigParam(MibDN fapLteDn, MsmLteRachCfgCommonParams &lteRachCfgCommonParams);
         void ReadLtePdschConfigCommonParameters(MibDN fapLteDn,MsmLtePdschCfgCommon &ltePdschCfgCommon);
         void ReadUlPwrCtrlParams(MibDN fapLteDn, MsmLteULPwrCtrlCommon &lteULPwrCtrlCommon);
         void ReadLteULFrequencyInfoParameters(MibDN fapLteDn,MsmLteULFrequencyInfo &lteULFrequencyInfo);
         void ReadLteCellSib3CfgGroupParameters(MibDN dn,MsmLteCellSib3CfgGrp &lteCellSib3CfgGrp);
         void ReadLtePuschBasicCfgCommonParameters(MibDN fapLteDn,
                                        MsmLtePuschBasicCfgCommon &ltePuschBasicCfgCommon);
         void ReadLtePuschRefSignalCfgParameters(MibDN fapLteDn,MsmLtePuschRefSignalCfg &ltePuschRefSignalCfg);
         void ReadLtePucchCfgCommonParameters(MibDN fapLteDn,MsmLtePucchCfgCommon &ltePucchCfgCommon);
         void ReadLteSRSCfgCommonParameters(MibDN fapLteDn,MsmLteSRSCfgCommon &lteSRSCfgCommon);
         void ReadUeTimerConstantsParams(MibDN fapLteDn, MsmLteUeTimerConstants &lteUeTimerConstants);
         void ReadLteCellSib9CfgGrpParameters(MibDN dn,MsmLteCellSib9CfgGrp &lteCellSib9CfgGrp);
         void ReadSib7CfgParameters(MibDN dn,MsmLteCellSib7CfgGrp &sib7CfgGrp);
         void ReadLteCellSib6CfgGroupParameters(MibDN dn,MsmLteCellSib6CfgGrp &lteCellSib6CfgGrp);
         void ReadAcBarringInfoParams(MibDN fapLteDn, MsmLteAcBarringInfo &lteAcBarringInfo);
         void ReadLteSib4CsgInfoParameters(MibDN dn,MsmLteSib4CsgInfo &lteSib4CsgInfo);
         void ReadLtePcchConfigCommonParameters(MibDN fapLteDn,MsmLtePCCHCfgCommon &ltePCCHCfgCommon);
         void ReadLteTddParameters(MibDN dn,MsmLteTddParam &lteTddParam);
         void ReadBarringConfig1xRTTCfg(MibDN dn,MsmBarringConfig1xRTTCfg &barringConfig1xRTTCfg);
         void ReadSib8Parameters(MibDN dn,MsmCellSib8CfgGrp &cellSib8CfgGrp);
         void ReadCsfbCfgParameters( MibDN dn, MsmCsfbCfgGrp &csfbCfgGrp);
         void ReadAccessManagementParameters(MibDN dn, MsmLteFapAccessParams &lteFapAccessParams,
               MsmLteSmCellCfg &lteSmCellCfg,U16 cellIdx);
         void ReadTenbStatsCfgParams(MibDN dn,MsmTenbStatsCfg &tenbStatsCfg);
         void ReadeAddCellCfgParameters(MibDN dnobj,MsmLteAddCellCfg &lteAddellCfg,bool isDynCfg);
         void ReadLteRimParameters(MibDN fapLteDn, MsmLteRimParams &lteRimParams);
         void ReadLteSelfConfigParameters(MibDN,MsmLteSonGenericParams&);
         void ReadLteEnbProtoCfgParameters(MibDN, MsmLteEnbProtoCfg&);
         void ReadLtePowerOffsetParameters(MibDN,MsmLtePowerOffsetParams&);
         void ReadLteCellSchdPowerParameters(MibDN,MsmCellSchdPwrCfg&);
         void ReadLteFapControParameters(MibDN,MsmLteFapControlParams&);
         void ReadHandleLteCellUlSchdCfgGrpParameters(MibDN fapLteDn, MsmLteCellUlSchdCfgGrp &lteCellUlSchdCfgGrp);
         void ReadLtePRBallocationParameters(MibDN fapLteDn, MsmLtePRBallocation &ltePRBallocation);
         void ReadLteSctpConfigParameters(MibDN fapLteDn, MsmLteSctpCfgParams &ltesctpCfgParams);
         void ReadLteRrmTddParameters(MibDN fapLteDn, MsmLteRrmTddParam &lteRrmTddParam);
         // Implement MessageHandler interface
         virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

         // Singleton instance.
         static SmApplication* s_instance;
         static u32  s_adminFlag;
         static bool s_isN1PucchUpdateFromRRM;
         static void adminDownFlagSet();
         static bool m_PeriodicRemScanInProg;

         /**
          * Although the KPI collector is registered with the base class
          * it is convenient to keep a shared ptr to it here that we
          * can give to anything that wants to update KPIs.
          */
         shared_ptr<SmKpiCollector> m_smKpiCollector;
         shared_ptr<SmTr196Validator> m_smTr196Validator;
         threeway::KpiMessageManager m_kpiMessageManager;
         //threeway::ManagedObject::AdminState m_adminState;

         u16 m_adminState;
         u16 m_messengerInitialConfigComplete;
         u16 m_smmInitialConfigComplete;
         u16 m_oneTimeInitialisation;
         u32 m_posu32;
         u16 m_posu16;
         u8 m_posu8;
         std::vector<u8> m_posu8list;
         std::vector<u32> m_posu32list;
         std::queue<u16> m_dynupdate;
         SmTr196Validator* ptr_Tr196Validator;
         threeway::TimerHandle m_watchdogKickTimer;
         threeway::TimerHandle  m_adminFlagTimer;
         threeway::TimerHandle m_periodRemStartTimer;
         threeway::TimerHandle m_periodRemScanTimer;
         u32 m_isSONRaisedAlarmExists;
         threeway::TimerHandle m_lteNeighCfgTimer;
         u32 callBackTo;

      public:
         void HandleLogUpload(u16, bool); 
         void StartLogTimer(u32 timer_value); 
         void HandleLteStackInitialConfigComplete();
         void SetLteOperationalState(u32 opState);
         void HandleLteShutDownAck();
         void HandleLteAlarmRegister(u32 id,u8 alarmSeverity,u8 alarmCauseType, u8 alarmCauseVal, std::string info="test");
         void HandleSwVersion(const char * swver);
         void updateDynEutraInUseCellList(u8 action, u8 mioInstance, u8 nrtIndx);
         void UpdateDynEutraCellInUse(u8 action, u8 cellIdx);
         void UpdateDynEutraCell(MibDN dnobj, u8 instance);
         void UpdateCellIndexMap(u32 instance, int inUseInstance, MsmDynNeighCellCfg *lteNeighCellCfg);
         u32 FillNeighCellByInstance(MibDN dnobj,u8 instance,MsmEUTRANeighCell *lteNeighCellCfg );
         void HandleLtePlmnIdUpdate(MsmEUTRANeighCell *eutraCellCfg, std::string *plmnIdStr);
         void rollBackNbrCell(u8 instance, MsmEUTRANeighCell *nbrCell,u16 cellIdx);
         void rollBackRsysNbrCell(u8 instance, MsmEUTRANeighCell *nbrCell);
         void msmDynConfigComplete(u8 status, u8 cause, MsmDynCfmInfo cfmInfo,u16 cellIdx);
         void HandleLteNeighFreqDynCfgFailure(u8 action, u8 freqIdx,u16 cellIdx);
         void HandleLteNeighCellDynCfgFailure(u8 action, u8 cellIdx,u16 cellId);
         void rollBackInterFreqCarr(u8 instance, MsmLteNeighEutraFreq *freqInfo,u16 cellIdx);
         void rollBackRsysInterFreqCarr(u8 instance, MsmLteNeighEutraFreq *freqInfo);
         void updateSONSelectedPCIInMIB(u16);
         void updateSONSelectedEARFCNULinMIB( u32* );
         void updateSONSelectedEARFCNDLinMIB( u32* );
         void updateSONEARFCNListInMIB( MsmEarfcnListCfg* );
         void updatePRACHConfInMIB( MsmLtePrachCfgCommon* );
         void updatePDSCHConfInMIB( MsmLtePdschCfgCommon *);
         void updatePowerOffsetInMIB( MsmLtePowerOffsetParams*);
         void updatePDSCHConfDedicatedfInMIB( MsmLtePdschCfgDedicated*);
         void updateN1PucchInMIB(u16 n1Pucch);
         void startAdminFlagTimer(u32 timeOutPeriod);
         void updateLteInUseNbr(u32 action, MsmEUTRANeighCell *eutraInfo, MibDN dn);
         void updateUmtsInUseNbr(u32 action, MsmUtraNeighCell *utraInfo, u16 cellIdx);
         void updateGeranInUseNbr(MsmLteGERANNeighCell *geranCellCfg, u16 cellIdx);

         u32 FillIp(std::vector<std::string> &ipString, u32 idx,Mmeiptype *mmeIp);
         bool IsIpSet(std::string ip);
         u16 numOfCells;
         typedef enum
         {
            MIB_OBJ_INIT_DEF_VAL=0,  /* Instance created and initialised with default values*/
            MIB_OBJ_CONFIGURED,   /* Values configured through SPV */
            MIB_OBJ_DELETED          /* Instance deleted or invalid */
         }MibObjectState;
         typedef enum {
            TYPE_INVALID=0,
            TYPE_IPV4,
            TYPE_IPV6
         }IpType;

         void ResetIP( Mmeiptype *mmeIp, IpType type);
         std::map<u32 ,pair<u32 ,std::string > >  lteNeighTracceMap;
         subsIdRanges  ranges;
   };
}
#endif
