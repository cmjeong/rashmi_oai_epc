
/********************************************************************20**
 
     Name:     TIP PHY Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for control plane primitives on TIP PHY Open Interface.

     File:     tip_ctf.c

     Sid:      tip_ctf.c@@

     Prg:      Radisys
     
*********************************************************************21*/
#if 0
static const char* RLOG_MODULE_NAME="TIP";
static int RLOG_MODULE_ID=847;
static int RLOG_FILE_ID=2;
#endif

/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm_lte.h"        /* Common LTE Defines              */
#include "ctf.h"           /* CTF interface defines           */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm_lib.x"        /* Common LTE library              */
#include "cm_lte.x"        /* Common LTE library              */
#include "ctf.x"          

#include "tip.h"
#include "tip_cmn.h"
#include "L3_L2L.h"
#include "tip_ctf.h"
#include "tip_utils.h"
#include "wr_ifm_l1.h"
#include "wr_smm_init.h"
#include "wr_smm_smallcell.h"
#include "wr_utils.h"

#ifndef LTE_ENB_PAL
EXTERN S16 YsUiCtfCfgReq ARGS(( Pst *pst, SpId spId, CtfCfgTransId transId, CtfCfgReqInfo* cfgReqInfo));
EXTERN S16 ysMsCfgPhyUp(U16  cellId);
#endif

U32 tipIsInitDone = 0;
U8  tipIsL3Ready = FALSE;
U8  isMacInitReqSent = FALSE;
U8  isRlcInitReqSent = FALSE;
U8  LL2HashLstInitDone = 0;

S16 tipCheckIsL2Ready()
{
   if(isMacInitReqSent && isRlcInitReqSent)
      RETVALUE(TRUE);
   
   RETVALUE(FALSE);
}

Bandwidth tipGetCtfBwToTipBw(CtfBandwidth bwVal)
{
   switch(bwVal)
   {
     case CTF_BW_RB_6:
        RETVALUE(BW_RB_6);
     case CTF_BW_RB_15:
        RETVALUE(BW_RB_15);
     case CTF_BW_RB_25:
        RETVALUE(BW_RB_25);
     case CTF_BW_RB_50:
        RETVALUE(BW_RB_50);
     case CTF_BW_RB_75:
        RETVALUE(BW_RB_75);
     case CTF_BW_RB_100:
        RETVALUE(BW_RB_100);
     default:
       printf("Wrong Bw %d\n", bwVal);
      break;
   }
   RETVALUE(BW_RB_100);
}

CtfBandwidth tipGetTipBwToCtfBw(Bandwidth bwVal)
{
   switch(bwVal)
   {
     case BW_RB_6:
        RETVALUE(CTF_BW_RB_6);
     case BW_RB_15:
        RETVALUE(CTF_BW_RB_15);
     case BW_RB_25:
        RETVALUE(CTF_BW_RB_25);
     case BW_RB_50:
        RETVALUE(CTF_BW_RB_50);
     case BW_RB_75:
        RETVALUE(CTF_BW_RB_75);
     case BW_RB_100:
        RETVALUE(CTF_BW_RB_100);
     default:
       printf("Wrong Bw %d\n", bwVal);
      break;
   }
   RETVALUE(CTF_BW_RB_100);
}

/***********************************************************
 *
 *     Func: tipBldCtfCellCfgReq
 *
 *
 *     Desc:   Cell Configuration Information
 *     @details This structure contains the information for setting-up
 *              of a cell and its associated resources at PHY.
 *
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipBldCtfCellCfgReq
(
PhyCellConfigReq *cellCfgInfo,
CtfCellCfgInfo *param
)
#else
PUBLIC S16 tipBldCtfCellCfgReq(cellCfgInfo, param)
PhyCellConfigReq *cellCfgInfo;
CtfCellCfgInfo *param;
#endif
{

   TRC3(cmPkCtfCellCfgInfo);

   cellCfgInfo->pci = (3 * param->cellIdGrpId) + param->physCellId;
   cellCfgInfo->pcfichPowerOffset = 6000;
   cellCfgInfo->bwConfigInfo.dlBandwidth = tipGetCtfBwToTipBw(param->bwCfg.dlBw);
   cellCfgInfo->bwConfigInfo.ulBandwidth = tipGetCtfBwToTipBw(param->bwCfg.ulBw);
   cellCfgInfo->bwConfigInfo.frequencyBand = param->bwCfg.eUtraBand;
   cellCfgInfo->bwConfigInfo.dlEarfcn = param->dlEarfcn;
   cellCfgInfo->bwConfigInfo.ulEarfcn = param->ulEarfcn;

   cellCfgInfo->txSchemeConfigInfo.duplexMode = param->txCfg.duplexMode;
   cellCfgInfo->txSchemeConfigInfo.subCarrierSpacing = param->txCfg.scSpacing;
   cellCfgInfo->txSchemeConfigInfo.cyclicPrefix = param->txCfg.cycPfx;

   cellCfgInfo->antennaConfigInfo.txAntennaPorts = param->antennaCfg.antPortsCnt;

   cellCfgInfo->prachConfigInfo.rootSeqIndex = param->prachCfg.rootSequenceIndex;
   cellCfgInfo->prachConfigInfo.configIndex = param->prachCfg.prachCfgIndex;
   cellCfgInfo->prachConfigInfo.zeroCorrZoneConfig = 
      param->prachCfg.zeroCorrelationZoneCfg;
   cellCfgInfo->prachConfigInfo.highSpeedFlag = param->prachCfg.highSpeedFlag;
   cellCfgInfo->prachConfigInfo.freqencyOffset = param->prachCfg.prachFreqOffset;

   cellCfgInfo->pdschConfigInfo.pB = param->pdschCfg.p_b;

   cellCfgInfo->puschConfigInfo.hoppingMode =
      param->puschCfg.puschBasicCfg.hoppingMode;
   cellCfgInfo->puschConfigInfo.hoppingOffset =
      param->puschCfg.puschBasicCfg.hoppingOffset;
   cellCfgInfo->puschConfigInfo.numberOfSubbands =
      param->puschCfg.puschBasicCfg.noOfsubBands;
   cellCfgInfo->puschConfigInfo.enable64Qam =
      param->puschCfg.puschBasicCfg.enable64QAM;
   cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.groupHoppingEnable =
      param->puschCfg.puschUlRS.grpHopEnabled;
   cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.sequnceHoppingEnable =
      param->puschCfg.puschUlRS.seqHopEnabled;
   cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.groupAssignment =
      param->puschCfg.puschUlRS.grpNum;
   cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.cyclicShift =
      param->puschCfg.puschUlRS.cycShift;

   cellCfgInfo->phichConfigInfo.phichDuration = param->phichCfg.duration;
   cellCfgInfo->phichConfigInfo.phichResource = param->phichCfg.resource;
   cellCfgInfo->phichConfigInfo.phichPowerOffset = 6000;/*TODO aricent asked send 0 as of now */

   cellCfgInfo->pucchConfigInfo.nRB = param->pucchCfg.nRB;
   cellCfgInfo->pucchConfigInfo.nCS = param->pucchCfg.nCS;
   cellCfgInfo->pucchConfigInfo.n1PucchAn = param->pucchCfg.n1PUCCH;
   cellCfgInfo->pucchConfigInfo.deltaPucchShift =
      param->pucchCfg.deltaShift + 1; /* +1 to cover the enum value 
                                         difference */

   cellCfgInfo->srsConfigInfo.bwConfig = param->srsUlCfg.srsSetup.srsBw;
   cellCfgInfo->srsConfigInfo.sfConfig = param->srsUlCfg.srsSetup.sfCfg;
   cellCfgInfo->srsConfigInfo.anSimultTx =
      param->srsUlCfg.srsSetup.srsANSimultTx;

   cellCfgInfo->sigConfigInfo.priSyncSignal = param->priSigPwr;
   cellCfgInfo->sigConfigInfo.secSyncSignal = param->secSigPwr;
   cellCfgInfo->sigConfigInfo.refSignalPower = param->pdschCfg.refSigPwr;

   RETVALUE(ROK);
}

/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipSendCtfCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfCfgReqInfo*  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendCtfCfgReq
(
Pst             *pst,
SpId            spId,
CtfCfgTransId   transId,
CtfCfgReqInfo   *cfgReqInfo
)
#else
PUBLIC S16 tipSendCtfCfgReq(pst, spId, transId, cfgReqInfo)
Pst             *pst;
SpId            spId;
CtfCfgTransId   transId;
CtfCfgReqInfo   *cfgReqInfo;
#endif
{
   TipPacket          *packet;
   U8                 sendBuf[MAX_BUFF_LEN_L2_L3];
   U16                len = 0;
   PhyCellConfigReq   *phyCfgInfo;
   U32                msgId;

   TRC3(cmPkCtfCfgReq);

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;

   switch(cfgReqInfo->cfgType) {
      case CTF_DELETE:
         {
            TipL3CfgDat   *cfg;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfg, sizeof(TipL3CfgDat)) != ROK)
            {           
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)ERGR052, (ErrVal)0, "Allocation failed");
#endif
               RETVALUE(RFAILED);

            }
            cmMemset((U8*)cfg, 0, sizeof(TipL3CfgDat));
            TIP_COPY_L1_TRANSID(transId, cfg->l1TransId);
            cfg->key = tipPrepareKey(cfgReqInfo->u.release.u.dedRel.cellId, cfgReqInfo->u.release.u.dedRel.ueId, 0);
            if(ROK != TipAddTransaction(cfg))
            {
               printf("\n\n *****failed to Add reconfig *****\n\n"); 
            }

         }
         break;
      case CTF_RECONFIG:
         if(CTF_TX_PWR_CFG == cfgReqInfo->u.cfg.cfgElem || 
               CTF_UE_CFG == cfgReqInfo->u.cfg.cfgElem)
         {
            WrIfmL1CfgCfm(pst, spId, transId, CTF_CFG_CFM_OK);
         }
         break;
      case CTF_CONFIG:
         if(CTF_CELL_CFG == cfgReqInfo->u.cfg.cfgElem)
         {
            msgId = PHY_CELLCONFIG_REQ;
            len = sizeof(PhyCellConfigReq);
            phyCfgInfo = (PhyCellConfigReq*)((U8*)sendBuf + TIP_HDR_LEN);
            tipBldCtfCellCfgReq(phyCfgInfo, &cfgReqInfo->u.cfg.u.cellCfg);
            #ifdef CTF_VER3
            WR_FREE(cfgReqInfo->vendorParams.paramBuffer, cfgReqInfo->vendorParams.buffLen );
            #endif
         }
         else if(CTF_UE_CFG == cfgReqInfo->u.cfg.cfgElem)
         {
            ;
         }
         break;
     default :
         printf("\nCTF Config Type not supported[%d]\n",
               cfgReqInfo->cfgType);
         break;
   }

   if(len <= 1) {
      printf("\nTIP:CTF:PACK: Error in packing\n");
      cmRelCtfCfgReq(pst, cfgReqInfo);
      RETVALUE(ROK); /* Sending ROK for App, to avoid UE del req*/
   }

   packet->srcModId = RRC_MOD_ID;
   packet->dstModId = PHY_MOD_ID;
   packet->cellId   = cfgReqInfo->u.cfg.u.cellCfg.cellId;
   packet->msgId    = msgId;
   packet->pktLen   = len + TIP_HDR_LEN;
   deriveTipTransId(transId.trans, packet);
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
               sizeof(CtfCfgReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }
   RETVALUE(tipSendToCLL2(packet->pktLen,(U8 *) &sendBuf));
}

/***********************************************************
 *
 *     Func: tipBldCtfUeCfgReq 
 *
 *
 *     Desc:   UE Configuration Information
 *     @details This structure contains the information for setting-up
 *              of a UE and its associated resources at PHY.
 *
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipBldCtfUeCfgReq(MacUeConfigReq *ueCfg, CtfDedCfgInfo  *ueCfgParam)
#else
PUBLIC S16 tipBldCtfUeCfgReq(ueCfg, ueCfgParam)
MacUeConfigReq *ueCfg;
CtfDedCfgInfo  *ueCfgParam;
#endif

{
   TRC3(tipBldCtfUeCfgReq);
   ueCfgParam->ueId = ueCfg->ueInfo.cRnti;

   /* Ue category */
   ueCfgParam->ueCatCfg.pres = TRUE;
   ueCfgParam->ueCatCfg.ueCategory = ueCfg->ueCategory;

   /* PDSCH Cfg */
   ueCfgParam->pdschCfg.pres = TRUE;
   ueCfgParam->pdschCfg.pA = ueCfg->uePdschConfigInfo.pA;

   /* PUCCH Cfg */
   /* TODO */
   ueCfgParam->pucchCfg.pres = TRUE;
   ueCfgParam->pucchCfg.dedPucchCfgType = CTF_IE_CFG_SETUP;
   ueCfgParam->pucchCfg.pucchSetup.repFact = 0;
   ueCfgParam->pucchCfg.pucchSetup.n1PUCCHRep = 0;
   /* PUSCH Cfg */
   ueCfgParam->puschCfg.pres = TRUE;
   ueCfgParam->puschCfg.betaOffsetAckIdx = ueCfg->uePuschConfigInfo.harqBetaOffset;   //TODO
   ueCfgParam->puschCfg.betaOffsetRiIdx = ueCfg->uePuschConfigInfo.riBetaOffset;
   ueCfgParam->puschCfg.betaOffsetCqiIdx = ueCfg->uePuschConfigInfo.cqiBetaOffset;

   /* Fix: tfu upgrade changes */
#ifndef TFU_UPGRADE
   //if(ueCb->bResCfgBitMap &  WR_UE_RADIO_RES_CFG_CQI)    //TODO
   {
      /* CQI Reporting */

      /*Fix for ccpu00126943- removal of platform name macro*/

      ueCfgParam->cqiRptCfg.pres = TRUE;

      ueCfgParam->cqiRptCfg.reportingMode = CTF_CQI_RPTMODE_PRDIOC;

      /* APERIODIC is not supported for now */
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiPeriodicCfgType 
         = CTF_IE_CFG_SETUP;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.cqiPUCCHRsrcIndx 
         = ueCfg->dlCqiConfigInfo.periodicCqiConfigInfo.cqiPucchResourceIndex;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.cqiPmiCfgIndx 
         = ueCfg->dlCqiConfigInfo.periodicCqiConfigInfo.cqiPmiConfigurationIndex;
      //ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.formatIndicator 
      // = ueCb->cqiRptCfg.fmtInd; 
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.subbandCqi.k 
         = ueCfg->dlCqiConfigInfo.periodicCqiConfigInfo.k;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.riCfgPres
         = FALSE;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.simultaneousAckNack
         = ueCfg->dlCqiConfigInfo.periodicCqiConfigInfo.simultaneousAckNackAndCqi;
   }
   else
   {
      ueCfgParam->cqiRptCfg.pres = FALSE;
   }
   /* UL SRS Cfg */
   ueCfgParam->srsUlCfg.pres = FALSE; //TODO 
   //if(ueCb->bResCfgBitMap &  WR_UE_RADIO_RES_CFG_SR)  //TODO
   {
      if (ueCb->srsUlDedCfg.pres)
      {
         ueCfgParam->srsUlCfg.dedSrsUlCfgType            = CTF_IE_CFG_SETUP;
         ueCfgParam->srsUlCfg.dedSrsSetup.srsBw          = ueCfg->srsUeConfigInfo.srsBandwidth;
         ueCfgParam->srsUlCfg.dedSrsSetup.srsHopngBw     = ueCfg->srsUeConfigInfo.srsHoppingBandwidth;
         ueCfgParam->srsUlCfg.dedSrsSetup.freqDmnPos     = ueCfg->srsUeConfigInfo.frequencyDomainPosition;
         ueCfgParam->srsUlCfg.dedSrsSetup.duration       = ueCfg->srsUeConfigInfo.duration;
         ueCfgParam->srsUlCfg.dedSrsSetup.srsCfgIdx      = ueCfg->srsUeConfigInfo.srsConfigIndex;
         ueCfgParam->srsUlCfg.dedSrsSetup.txComb         = ueCfg->srsUeConfigInfo.transmissionComb;
         ueCfgParam->srsUlCfg.dedSrsSetup.cyclicShift    = ueCfg->srsUeConfigInfo.srsCyclicShift;
      }
      /* Dedicated SR Cfg */
      ueCfgParam->dedSRCfg.pres = TRUE;
      ueCfgParam->dedSRCfg.dedSRCfgType = CTF_IE_CFG_SETUP;
      ueCfgParam->dedSRCfg.dedSrSetup.srPUCCHRi = ueCfg->srConfigInfo.srResourceIndex;

      ueCfgParam->dedSRCfg.dedSrSetup.srCfgIdx = ueCfg->srConfigInfo.srConfigIndex;
   }
   else
   {
      ueCfgParam->dedSRCfg.pres = FALSE;
   }

#endif /* TFU_UPGRADE */

   /* Antenna Cfg */
   ueCfgParam->antInfo.pres = TRUE;
   ueCfgParam->antInfo.txMode = ueCfg->transmissionModeConfigInfo.transmissionMode;
   ueCfgParam->antInfo.ueTxAntSelection.cfgType = CTF_IE_CFG_SETUP; 
   ueCfgParam->antInfo.ueTxAntSelection.txAntSelect = 0;

    RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func:   tipBldCtfUeReCfgReq 
 *
 *
 *     Desc:   UE Reconfiguration Information
 *     @details This structure contains the information for setting-up
 *              of a UE and its associated resources at PHY for UE 
 *              reconfiguration.
 *
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipBldCtfUeReCfgReq(MacUeReconfigReq  *ueReCfg, CtfDedRecfgInfo *ueReCfgParam)
#else
PUBLIC S16 tipBldCtfUeReCfgReq(ueReCfg, ueReCfgParam)
MacUeReconfigReq  *ueReCfg;
CtfDedRecfgInfo   *ueReCfgParam;
#endif

{
   TRC3(tipBldCtfUeReCfgReq);
   ueReCfgParam->ueId          = ueReCfg->oldCRnti;
   ueReCfgParam->newUeId       = ueReCfg->newCRnti;
   ueReCfgParam->ueCatCfg.ueCategory = ueReCfg->ueCategory;
   ueReCfgParam->ueCatCfg.pres = TRUE;
   RETVALUE(ROK);
}

/**
* @brief Send CTF UE Config request 
*
* @details
*
*     Function: tipSendCtfUeCfgReq 
*
*  @param[in]   TipPacket*    hdr
*  @param[in]   Pst*       nPst 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendCtfUeCfgReq(TipPacket   *hdr, Pst *nPst)
#else
PUBLIC S16 tipSendCtfUeCfgReq(hdr, nPst)
TipPacket   *hdr;
Pst         *nPst;
#endif
{
   S16              ret = ROK;
   Pst              *pst; 
   SpId             spId = 0;
   CtfCfgTransId    transId;
   U64              tipTransId;
   CtfCfgReqInfo    *cfgReqInfo = NULLP;


   TRC3(tipSendCtfUeCfgReq);

   if(SGetSBuf(nPst->region, nPst->pool, (Data **)&pst, sizeof(Pst)) != ROK)
   {
      RETVALUE(RFAILED);
   } 

   TIP_CREATE_CTF_PST(pst);  //TODO

   if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
            sizeof(CtfCfgReqInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   cmMemset((U8*)cfgReqInfo, 0, sizeof(CtfCfgReqInfo));

   switch(hdr->msgId)
   {
      case MAC_UECONFIG_REQ : 
         {   
            MacUeConfigReq *ueCfg = (MacUeConfigReq*)&hdr->message; 

            CtfDedCfgInfo             *ueCfgParam = NULLP;

            cfgReqInfo->cfgType = CTF_CONFIG;
            cfgReqInfo->u.cfg.cfgElem = CTF_UE_CFG;
            ueCfgParam = &cfgReqInfo->u.cfg.u.dedCfg;
            ueCfgParam->cellId = hdr->cellId;

            tipBldCtfUeCfgReq(ueCfg, ueCfgParam);
            tipTransId = tipPrepareLL2Key(hdr); 
            deriveLL2TransId((U8 *)&transId, tipTransId, CTF_CONFIG, CTF_UE_CFG, CTF_CFG_TRANSID_SIZE);
         }
         break;
      case MAC_UERECONFIG_REQ :
         {  
            MacUeReconfigReq  *ueReCfg = (MacUeReconfigReq*)&hdr->message; 

            CtfDedRecfgInfo   *ueReCfgParam = NULLP;

            cfgReqInfo->cfgType = CTF_RECONFIG;
            cfgReqInfo->u.reCfg.cfgElem = CTF_UE_CFG;
            ueReCfgParam = &cfgReqInfo->u.reCfg.u.dedRecfg;
            ueReCfgParam->cellId = hdr->cellId;

            tipBldCtfUeReCfgReq(ueReCfg, ueReCfgParam);
            tipTransId = tipPrepareLL2Key(hdr); 
            deriveLL2TransId((U8 *)&transId, tipTransId, CTF_RECONFIG, CTF_UE_CFG, CTF_CFG_TRANSID_SIZE);
         }
         break;

      case MAC_UEDELETE_REQ:
         {
            MacUeDeleteReq  *ueDelReq = (MacUeDeleteReq*)&hdr->message; 

            CtfDedReleaseInfo  *ueReleaseInfo = NULLP;

            cfgReqInfo->cfgType = CTF_DELETE;
            cfgReqInfo->u.release.cfgElem = CTF_UE_CFG;
            ueReleaseInfo = &cfgReqInfo->u.release.u.dedRel;
            ueReleaseInfo->cellId = hdr->cellId;
            ueReleaseInfo->ueId = ueDelReq->ueInfo.cRnti;

            tipTransId = tipPrepareLL2Key(hdr); 
            deriveLL2TransId((U8 *)&transId, tipTransId, CTF_DELETE, CTF_UE_CFG, CTF_CFG_TRANSID_SIZE);

         }
         break;

      default:
         /* Free allocated memory */
         SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
               sizeof(CtfCfgReqInfo));

         SPutSBuf (nPst->region, nPst->pool, (Data *)pst, sizeof(Pst));
         printf("Invalid message %d is received at PHY !! ", hdr->msgId);
         RETVALUE(RFAILED);
   }
#ifdef LTE_ENB_PAL
   ret = TfUiCtfCfgReq(pst, spId, transId, cfgReqInfo);
#else
   ret = YsUiCtfCfgReq(pst, spId, transId, cfgReqInfo);
#endif
   SPutSBuf (nPst->region, nPst->pool, (Data *)pst, sizeof(Pst));
   RETVALUE(ret);
}

/***********************************************************
*
*     Func: tipFillCtfCellCfgReq
*
*
*     Desc:   Cell Configuration Information
 * @details This structure contains the information for setting-up
 *          of a cell and its associated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 tipFillCtfCellCfgReq
(
PhyCellConfigReq *cellCfgInfo,
CtfCellCfgInfo *param
)
#else
PUBLIC S16 tipFillCtfCellCfgReq(cellCfgInfo, param)
PhyCellConfigReq *cellCfgInfo;
CtfCellCfgInfo *param;
#endif
{
   TRC3(tipFillCtfCellCfgReq);

   param->schSapId = 1; /*LYS_TFU_SCH_SAP*/
   param->macSapId = 0; /*LYS_TFU_USR_SAP*/
   param->cellIdGrpId = (cellCfgInfo->pci / 3);
   param->physCellId = (cellCfgInfo->pci % 3);

   param->bwCfg.dlBw = tipGetTipBwToCtfBw(cellCfgInfo->bwConfigInfo.dlBandwidth);
   param->bwCfg.ulBw = tipGetTipBwToCtfBw(cellCfgInfo->bwConfigInfo.ulBandwidth);
   param->bwCfg.eUtraBand = cellCfgInfo->bwConfigInfo.frequencyBand;
   param->dlEarfcn = cellCfgInfo->bwConfigInfo.dlEarfcn;
   param->ulEarfcn = cellCfgInfo->bwConfigInfo.ulEarfcn;

   param->txCfg.duplexMode = cellCfgInfo->txSchemeConfigInfo.duplexMode;
   param->txCfg.scSpacing = cellCfgInfo->txSchemeConfigInfo.subCarrierSpacing;
   param->txCfg.cycPfx = cellCfgInfo->txSchemeConfigInfo.cyclicPrefix;

   param->antennaCfg.antPortsCnt = cellCfgInfo->antennaConfigInfo.txAntennaPorts;

   param->prachCfg.rootSequenceIndex = cellCfgInfo->prachConfigInfo.rootSeqIndex;
   param->prachCfg.prachCfgIndex = cellCfgInfo->prachConfigInfo.configIndex;
   param->prachCfg.zeroCorrelationZoneCfg =
      cellCfgInfo->prachConfigInfo.zeroCorrZoneConfig;
   param->prachCfg.highSpeedFlag = cellCfgInfo->prachConfigInfo.highSpeedFlag;
   param->prachCfg.prachFreqOffset = cellCfgInfo->prachConfigInfo.freqencyOffset;

   param->pdschCfg.p_b = cellCfgInfo->pdschConfigInfo.pB;

   param->puschCfg.puschBasicCfg.hoppingMode = 
      cellCfgInfo->puschConfigInfo.hoppingMode;
   param->puschCfg.puschBasicCfg.hoppingOffset =
      cellCfgInfo->puschConfigInfo.hoppingOffset;
   param->puschCfg.puschBasicCfg.noOfsubBands =
      cellCfgInfo->puschConfigInfo.numberOfSubbands;
   param->puschCfg.puschBasicCfg.enable64QAM =
      cellCfgInfo->puschConfigInfo.enable64Qam;
   param->puschCfg.puschUlRS.grpHopEnabled =
      cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.groupHoppingEnable;
   param->puschCfg.puschUlRS.seqHopEnabled =
      cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.sequnceHoppingEnable;
   param->puschCfg.puschUlRS.grpNum =
      cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.groupAssignment;
   param->puschCfg.puschUlRS.cycShift =
      cellCfgInfo->puschConfigInfo.ulRefSigCfgInfo.cyclicShift;

   param->phichCfg.duration = cellCfgInfo->phichConfigInfo.phichDuration;
   param->phichCfg.resource = cellCfgInfo->phichConfigInfo.phichResource;

   param->pucchCfg.nRB = cellCfgInfo->pucchConfigInfo.nRB;
   param->pucchCfg.nCS = cellCfgInfo->pucchConfigInfo.nCS;
   param->pucchCfg.n1PUCCH = cellCfgInfo->pucchConfigInfo.n1PucchAn;
   param->pucchCfg.deltaShift = 
      cellCfgInfo->pucchConfigInfo.deltaPucchShift - 1; /* -1 to cover the enum
                                                          value difference */

   param->srsUlCfg.srsSetup.srsBw = cellCfgInfo->srsConfigInfo.bwConfig;
   param->srsUlCfg.srsSetup.sfCfg = cellCfgInfo->srsConfigInfo.sfConfig;
   param->srsUlCfg.srsSetup.srsANSimultTx = 
      cellCfgInfo->srsConfigInfo.anSimultTx;
   param->srsUlCfg.srsCfgType = 1; //SOUNDINGRS_UL_CONFIGCMN_SETUP;

   param->priSigPwr = cellCfgInfo->sigConfigInfo.priSyncSignal;
   param->secSigPwr = cellCfgInfo->sigConfigInfo.secSyncSignal;
   param->pilotSigPwr = cellCfgInfo->sigConfigInfo.refSignalPower;
   param->pdschCfg.refSigPwr = cellCfgInfo->sigConfigInfo.refSignalPower;
   param->opMode = lteeNodeBparams[0].lteMsCellCfgReq.opMode;
   param->period = lteeNodeBparams[0].lteMsCellCfgReq.period;

   RETVALUE(ROK);
}

/**
* @brief Configuration Confirm from PHY to RRC.
*
* @details
*
*     Function: tipSendCtfCfgRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendCtfCfgRsp
(
Pst* pst,
SuId suId,
CtfCfgTransId transId,
U8 status
)
#else
PUBLIC S16 tipSendCtfCfgRsp(pst, suId, transId, status)
Pst* pst;
SuId suId;
CtfCfgTransId transId;
U8 status;
#endif
{
   TipPacket *packet;
   U8 sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   PhyCellConfigRsp *phyCfgCfm;
   TipLL2RgDat      *cfg;
   U64              key = 0;
   U16              cellId = 0;

   TRC3(tipSendCtfCfgRsp);

   key |= (U64)transId.trans[2];
   key = key << 8;
   key |= (U64)transId.trans[3];
   key = key << 8;
   key |= (U64)transId.trans[4];
   key = key << 8;
   key |= (U64)transId.trans[5];
   key = key << 8;
   key |= (U64)transId.trans[6];
   key = key << 8;
   key |= (U64)transId.trans[7];

   cellId = (U16)(((U16)transId.trans[4] << 8) | (U16)transId.trans[5]);
   if(ROK != TipFindLL2Trans(key, &cfg))
   {
      RETVALUE(RFAILED);
   }
   TipDelLL2Trans(cfg);

   switch( transId.trans[0])
   {
      case CTF_CONFIG :
         {
            switch(transId.trans[1] )
            {
               case CTF_CELL_CFG :
                  {
                     packet = (TipPacket*)sendBuf;

                     packet->srcModId = PHY_MOD_ID;
                     packet->dstModId = RRC_MOD_ID;
                     packet->cellId = cellId;
                     packet->msgId = PHY_CELLCONFIG_RSP;
                     packet->pktLen = TIP_HDR_LEN + sizeof(PhyCellConfigRsp);

                     phyCfgCfm = (PhyCellConfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);
                     if(status  == CTF_CFG_CFM_OK)
                     {
                        phyCfgCfm->status = 0; 
                     }
                     else
                     {
                        phyCfgCfm->status = 1; 
                     }
                     packet->transId = cfg->upperLyrTrans;
                     SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(TipLL2RgDat));
                     RETVALUE(tipSendToL3(packet->pktLen,(U8 *)&sendBuf));
                  }
                  break;
               case CTF_UE_CFG :
                  {
                     cfg->isPhyUeCfgDone = TRUE;
                     printf(" tipSendCtfCfgRsp UE Config Done successfully !!! \n");
                     TipAddLL2Trans(cfg);
                  }
                  break;
               default :
                  printf(" tipSendCtfCfgRsp received for invalid cfgType %d \n", transId.trans[1]);
            }
         }
         break;
         case CTF_RECONFIG :
         {
            switch(transId.trans[1] )
            {
               case CTF_UE_CFG:
                  {
                     cfg->isPhyUeReCfgDone = TRUE;
                     printf(" tipSendCtfCfgRsp UE ReConfig Done successfully !!! \n");
                     TipAddLL2Trans(cfg);
                  }
                  break;
               case CTF_CELL_CFG:
                  printf("Cell start IND processed successfully\n");
                  break;
               default :
                  printf(" tipSendCtfCfgRsp received for invalid cfgType %d \n", transId.trans[1]);
            }
         }
         break;
         case CTF_DELETE :
         {
            switch(transId.trans[1] )
            {
               case CTF_UE_CFG :
                  {
                     cfg->isPhyUeDeleteDone = TRUE;
                     printf(" tipSendCtfCfgRsp UE Delete Done successfully !!! \n");
                     TipAddLL2Trans(cfg);
                  }
                  break;
               default :
                  printf(" tipSendCtfCfgRsp received for invalid cfgType %d \n", transId.trans[1]);
            }
         }
         break;
         default:
              printf(" tipSendCtfCfgRsp received for invalid action %d \n", transId.trans[0]);
   }
   RETVALUE(ROK);
}

/**
* @brief unpack all L1 massages received from L3
*
* @details
*
*     Function: tipUnpkL1AppMsg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkL1AppMsg
(
Pst*    pst,
Buffer* mBuf
)
{
  U8             rcvBuf[MAX_BUFF_LEN_L2_L3];
  TipPacket      *hdr = NULLP;
  MsgLen         msgLen;
  CtfCfgTransId  transId;
  U32            suId = 0;
  S16            ret;
  MsgLen         bufLen;
   
  ret = SFndLenMsg(mBuf, &bufLen); 
  ret = SCpyMsgFix(mBuf, 0, bufLen, rcvBuf, &msgLen);

  hdr = (TipPacket*)&rcvBuf;

  switch(hdr->msgId)
  {
     case PHY_CELLCONFIG_RSP:
     {
        PhyCellConfigRsp *cellCfgCfm;
        cellCfgCfm = (PhyCellConfigRsp*)&hdr->message;
        deriveTransId( (U8*)&transId, hdr->transId, CTF_CONFIG, CTF_CELL_CFG, CTF_CFG_TRANSID_SIZE);
        if(cellCfgCfm->status == 0)
        {
            cellCfgCfm->status = CTF_CFG_CFM_OK; 
        }
        else
        {
            cellCfgCfm->status = CTF_CFG_CFM_NOK; 
        }
        WrIfmL1CfgCfm(pst, suId, transId, cellCfgCfm->status);
     }
     break;
     case PHY_CELLDELETE_RSP:
     {
       printf("Need to handle PHY_CELLDELETE_RSP:");
     }
     break;
#if 0
     case MAC_INIT_IND:
     {
#ifdef TIP_L3
        if(isMacInitReqSent == FALSE)
        {
           tipBldSendInitReq(hdr->srcModId);
           printf("MAC INIT Indication received (%d)\n", hdr->msgId);
           isMacInitReqSent = TRUE;
        }
        else
        {
           printf("Already ongoing INIT procedure. Dropping INIT Indication "
                 "[msgId(%d)]\n", hdr->msgId);
        }
#endif
     }
     break;
     case RLC_INIT_IND:
     {
#ifdef TIP_L3
        if(isRlcInitReqSent == FALSE)
        {
           tipBldSendInitReq(hdr->srcModId);
           printf("RLC INIT Indication received (%d)\n", hdr->msgId);
           isRlcInitReqSent = TRUE;
        }
        else
        {
           printf("Already ongoing INIT procedure. Dropping INIT Indication "
                 "[msgId(%d)]\n", hdr->msgId);
        }
#endif
     }
     break;
     case MAC_INIT_RSP:
     {
#ifdef TIP_L3
        tipIsInitDone |= TIP_MAC_INIT_DONE;
        if(tipIsInitDone == TIP_INIT_DONE)
        {
           tipIsInitDone = 0xffffff;
           if(tipIsL3Ready)
               smWrConfigCell(1);
               smWrConfigCell(2);
        }
#endif
         printf("INIT Response received from MAC \n");
     }
     break;
     case RLC_INIT_RSP:
     {
#ifdef TIP_L3
        tipIsInitDone |= TIP_RLC_INIT_DONE;
        if(tipIsInitDone == TIP_INIT_DONE)
        {
           tipIsInitDone = 0xffffff;
           if(tipIsL3Ready)
               smWrConfigCell(1);
               sleep(1);
               smWrConfigCell(2);
        }
#endif
         printf("INIT Response received from RLC \n");
     }
     break;
#endif
    default:
     {
        printf("L1 Message(%d) is not handled \n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ROK);
} /*end of tipUnpkL1AppMsg */

/**
 *  @brief This function build and send the cell re-Configuration           message
 *
 *      Function: tipCellTxPwrReCfg 
 *
 *          Processing steps:
 *          - Allocate memory for cell reCfg message 
 *          - update the structure
 *          - call the interface function to send the message to               CL over CTF interface
 *
 *
 *  @param [in]  transId : transid
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */
PRIVATE S16 tipCellTxPwrReCfg 
(
   U16                       cellId,
   CtfCfgReqInfo             *reCfgInfo
)
{
   CtfCellRecfgInfo          *reCellCfgParam = NULLP;

   reCfgInfo->cfgType 	       = CTF_RECONFIG;

   reCfgInfo->u.reCfg.cfgElem  = CTF_TX_PWR_CFG; 

   reCellCfgParam = &reCfgInfo->u.reCfg.u.cellRecfg;

   reCellCfgParam->cellId        = cellId;

   /* One S1 connection is available now so setting defalut tx power */
   reCellCfgParam->pdschCfg.refSigPwr =  wrSmDfltRefSigPwr; 
   reCellCfgParam->pilotSigPwr        =  wrSmDfltPilotSigPwr;
   reCellCfgParam->priSigPwr          =  wrSmDfltPriSigPwr;
   reCellCfgParam->secSigPwr          =  wrSmDfltSecSigPwr;
   reCellCfgParam->ctfCellStatus      = CTF_CELL_UP;

   RETVALUE(ROK);
}/* end of wrEmmCellTxPwrReCfg*/


/**
* @brief unpack all L3 massages received from L1
*
* @details
*
*     Function: tipUnpkAppL1Msg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkAppL1Msg
(
Pst*    pst,
Buffer* mBuf
)
{
  U8             rcvBuf[MAX_BUFF_LEN_L2_L3];
  MsgLen         msgLen;
  TipPacket      *hdr = NULLP;
  CtfCfgReqInfo  *cfgReqInfo = NULLP;
  SpId           spId = 0;
  CtfCfgTransId  transId;
  U64            tipTransId;
  MsgLen         bufLen;
  S16            ret;
  TipLL2RgDat    *cfg;

  ret = SFndLenMsg(mBuf, &bufLen);
  ret = SCpyMsgFix(mBuf, 0, bufLen, rcvBuf, &msgLen);
  hdr = (TipPacket*)&rcvBuf;

  switch(hdr->msgId)
  {
     case PHY_CELLCONFIG_REQ:
     {
#ifndef LTE_ENB_PAL
        WrMsCellCfgReq    *msCellCfgReq;
#endif
        PhyCellConfigReq  *cellCfgReq;

        if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
               sizeof(CtfCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            /* ctf_c_001.main_3 Compilation warning fix with g++ */
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ECTF024, (ErrVal)0, (Txt*)&"Memory Allocation failed");
#endif
           SPutMsg(mBuf);
           RETVALUE(RFAILED);
        }
        cmMemset((U8 *)cfgReqInfo, 0, sizeof(CtfCfgReqInfo));

#ifdef TIP_LOWER_L2
        /* Initializing LL2 Hash List */
        if(!LL2HashLstInitDone)
        {
           tipLL2HashListInit();
           LL2HashLstInitDone = TRUE;
        }
#endif
        cfgReqInfo->cfgType = CTF_CONFIG;
        if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg,
               sizeof(TipLL2RgDat))) != ROK) 
        {
           printf("\nMemory allocation failed\n"); 
           RETVALUE(RFAILED);
        }
        cmMemset((U8 *)cfg, 0, sizeof(TipLL2RgDat));

        cfgReqInfo->u.cfg.cfgElem = CTF_CELL_CFG;

#ifndef LTE_ENB_PAL
        WR_ALLOC(&cfgReqInfo->vendorParams.paramBuffer, sizeof(WrMsCellCfgReq));
        if(cfgReqInfo->vendorParams.paramBuffer == NULLP)
        {
           RETVALUE(RFAILED);
        } /* end of if statement */

        msCellCfgReq = (WrMsCellCfgReq *)cfgReqInfo->vendorParams.paramBuffer;
        /*changed from sizeof(msCellCfgReq) to
         * sizeof(WrMsCellCfgReq) */
        cfgReqInfo->vendorParams.buffLen = sizeof(WrMsCellCfgReq);
        msCellCfgReq->opMode  = lteeNodeBparams[0].lteMsCellCfgReq.opMode;
        msCellCfgReq->counter = 0;
        msCellCfgReq->period  = lteeNodeBparams[0].lteMsCellCfgReq.period;
#endif

        cellCfgReq = (PhyCellConfigReq*)&hdr->message;
        tipFillCtfCellCfgReq(cellCfgReq, &cfgReqInfo->u.cfg.u.cellCfg);
        cfgReqInfo->u.cfg.u.cellCfg.cellId = hdr->cellId;
        cfg->key = tipPrepareLL2Key(hdr);
        cfg->upperLyrTrans = hdr->transId;
        tipTransId = cfg->key;
        deriveLL2TransId((U8 *)&transId, tipTransId, CTF_CONFIG, CTF_CELL_CFG, CTF_CFG_TRANSID_SIZE);
        TipAddLL2Trans(cfg);
#ifdef LTE_ENB_PAL
        ret = TfUiCtfCfgReq(pst, spId, transId, cfgReqInfo);
#else
        ret = YsUiCtfCfgReq(pst, spId, transId, cfgReqInfo);
#endif
     }
     break;
     case PHY_CELLDELETE_REQ:
     {
       printf("Need to handle PHY_CELLDELETE_REQ:");
     }
     break;
     case MAC_CELLSTART_IND:
     {
#ifdef TIP_LOWER_L2
#ifdef LTE_ENB_PAL
       tipStartCell(hdr->cellId);
#else
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
               sizeof(CtfCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            /* ctf_c_001.main_3 Compilation warning fix with g++ */
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ECTF024, (ErrVal)0, (Txt*)&"Packing failed");
#endif
           SPutMsg(mBuf);
           RETVALUE(RFAILED);
       }
       cmMemset((U8 *)cfgReqInfo, 0, sizeof(CtfCfgReqInfo));

       ysMsCfgPhyUp(hdr->cellId);
       tipCellTxPwrReCfg(hdr->cellId, cfgReqInfo);
#if 0
       tipTransId = hdr->transId; 
       deriveTransId((U8 *)&transId, tipTransId, CTF_RECONFIG, CTF_CELL_CFG, CTF_CFG_TRANSID_SIZE);
#else
        if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg,
               sizeof(TipLL2RgDat))) != ROK) 
        {
           printf("\nMemory allocation failed\n"); 
           RETVALUE(RFAILED);
        }
        cmMemset((U8 *)cfg, 0, sizeof(TipLL2RgDat));
        cfg->key = tipPrepareLL2Key(hdr);
        printf("\n*** Key stored %lu ****\n", cfg->key);
        cfg->upperLyrTrans = hdr->transId;
        tipTransId = cfg->key;
        deriveLL2TransId((U8 *)&transId, tipTransId, CTF_RECONFIG, CTF_CELL_CFG, CTF_CFG_TRANSID_SIZE);
        TipAddLL2Trans(cfg); 
#endif
       YsUiCtfCfgReq(pst, spId, transId, cfgReqInfo);
#endif
#endif
     }
     break;
     case MAC_INIT_REQ:
     case RLC_INIT_REQ:
     {
        tipHdlInitReq(hdr);
     }
     break;
     default:
     {
        printf("L1 Message(%d) is not handled \n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ROK);
} /*end of tipUnpkL1AppMsg */


/********************************************************************30**

         End of file:     tip_ctf.c@@

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
