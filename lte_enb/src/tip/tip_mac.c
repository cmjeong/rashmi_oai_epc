
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     tip_mac.c

     Sid:      $SID$ 

     Prg:      Radisys 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="TIP";
static int RLOG_MODULE_ID=847;
static int RLOG_FILE_ID=4;

/* header include files (.h) */
#include "tip_cmn.h"
#include "L3_L2L.h"
#include "tip.h"
#include "crg.h"
#include "crg.x"
#include "tip_mac.h"
#include "tip_utils.h"

#include "wr.h"
#include "wr_cmn.h"
#include "wr_emm.h"
#include "wr_smm_smallcell.h"
#include "rgr.x"
#include "wr_emm_mme.h"
#include "wr_emm_pbm.h"
#include "wr_utils.h"
#include "wr_umm_meas_fun.h"
#include "wr_emm_s1_flex.h"
#include "wr_emm_rim.h"
#include "wr_emm_rim_app.h"
#include "wr_kpi.h"
#include "wr_ifm_l1.h"

#ifdef TIP_L3
extern LwrSchedEnbCfg *wrGetSchedEnbCfg();
#endif
#define TIP_DBG

TipCellTransInfo tipCellInfoList[TIP_MAX_CELLS];
U8 tipNumActvCells = 0;
U32 pfsQciWgt[RGR_MAX_NUM_QCI] = {8,6,7,5,9,4,3,2,1};
static int sendOneStatus = 0;

#ifdef TIP_DBG
void printMsg(U16 len, U8 *msg)
{
   U16 idx = 0;
   printf("Starting DATA Len(%d)\n", len);
   for(idx = 0; idx < len; idx++)
   {
      printf(" %x", msg[idx]);
   }
   printf("\nEND of DATA\n");
}
#endif

CmHashListCp  LL2HashLstCp;

/**
 * @brief 
 *    Handler for Init
 *
 * @param[in] gCb      RLC Instance Control Block  
 * @param[in] cfgTmpData  Configuration stored in Transaction Block  
 * @param[in] cfg      Configuration block
 *
 * @return  S16
 *    -# ROK 
 *    -# RFAILED
 */
#ifdef ANSI
PUBLIC Void tipLL2HashListInit
(
)
#else
PUBLIC Void tipLL2HashListInit(Void)
#endif
{
   if(ROK != cmHashListInit(&(LL2HashLstCp), 
                            (U16) 64,
                            (U16) 0, 
                            (Bool) FALSE, 
                            (U16) CM_HASH_KEYTYPE_STR,
                            0, 
                            0))
   {
      //RLOG0(L_ERROR, "transIdLstCp Initialization Failed");
      printf("\n\n*****transIdLstCp Initialization Failed****\n\n");
   }
   RETVOID;
}

/**
 * @brief Handler to add a transaction 
 *
 * @details
 *    This function adds a transaction. 
 *
 * @param[in] cRnti
 * @param[in] Ue-Index
 * 
 * @return  S16
 *    -# ROK 
 *    -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 TipAddLL2Trans
(
TipLL2RgDat   *cfg
)
#else
PUBLIC S16 TipAddLL2Trans(cfg)
TipLL2RgDat   *cfg;
#endif
{
   TRC3(TipAddLL2Trans)
   if(ROK != (cmHashListInsert(&(LL2HashLstCp), 
                             (PTR)(cfg), 
                             (U8 *)&(cfg->key), 
                             (U16) sizeof(cfg->key))))
   {
     printf("\n\n**** Failed addition to hashList ****\n\n");
     RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} 

/**
 * @brief Handler to find a transaction 
 *       
 * @details
 *    This function find transaction using transaction Id 
 *
 *
 * @param[in] gCb       RLC Instance Control Block
 * @param[in] transId   Transaction Id 
 * @param[out] cfg      Configuration information attached to this transaction
 *
 * @return  S16
 *    -# ROK 
 *    -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 TipFindLL2Trans
(
U64          key,
TipLL2RgDat  **cfg
)
#else
PUBLIC S16 TipFindLL2Trans(key, cfg)
U64          key;
TipLL2RgDat  **cfg;
#endif
{
   TRC3(TipFindLL2Trans)

   *cfg = NULLP;

   if(ROK != cmHashListFind(&(LL2HashLstCp),
                            (U8 *) &(key), 
                            sizeof (key), 
                            0, (PTR *) cfg))
   {
      printf("\n\n **** Find failed **** [key: %lx] \n\n", key);
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/**
 *
 * @brief Handler to delete a transaction 
 *
 * @details
 *    This function deletes a transaction 
 *
 *
 *  @param[in] gCb     RLC Instance Control Block
 *  @param[in] cfg     Configuration information
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 TipDelLL2Trans
(
TipLL2RgDat   *cfg
)
#else
PUBLIC S16 TipDelLL2Trans(cfg)
TipLL2RgDat   *cfg;      
#endif
{
   TRC3(TipDelLL2Trans)

   if(NULLP == cfg)
   {
      RETVALUE(RFAILED);
   }

   if(cmHashListDelete(&(LL2HashLstCp),(PTR) (cfg)) != ROK) 
   {
      RLOG0(L_ERROR,"HashList Deletion failed");
      printf("\n\n****HashList Deletion failed*****[key: %lx]\n\n", cfg->key);
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}
/**
 *
 * @brief Handler to Get TA timer value as per TIP interface  
 *
 * @details
 *    This function to Get TA value  
 *
 *
 *  @param[in] taTimer  TA timer as per RSYS Interface
 *
 *  @return  S16
 *      -# Timer Value as per TIP interface
 *
 */
#ifdef ANSI
PUBLIC U32 tipGetTipTaVal
(
 U32  taTmrVal
)
#else
PUBLIC U32 tipGetTipTaVal(taTmrVal)
 U32  taTmrVal
#endif
{
  switch(taTmrVal)
  {
    case 500:
    {
       RETVALUE(0);
    }
    case 750:
    {
      RETVALUE(1);
    }
    case 1280:
    {
      RETVALUE(2);
    }
    case 1920:
    {
      RETVALUE(3);
    }
    case 2560:
    {
      RETVALUE(4);
    }
    case 5120:
    {
      RETVALUE(5);
    }
    case 10240:
    {
      RETVALUE(6);
    }
    default:
    {
      RETVALUE(7);
    }
  }
}

/**
 *
 * @brief Handler to Get TA timer value as per RSYS interface  
 *
 * @details
 *    This function to Get TA value  
 *
 *
 *  @param[in] taTimer  TA timer as per TIP Interface
 *
 *  @return  S16
 *      -# Timer Value as per RSYS interface
 *
 */
#ifdef ANSI
PUBLIC U32 tipGetRsysTaVal
(
 U32  taTmrVal
)
#else
PUBLIC S16 tipGetRsysTaVal(taTmrVal)
 U32  taTmrVal
#endif
{

  switch(taTmrVal)
  {
     case 0:
     {
        RETVALUE(500);
     }
     case 1:
     {
       RETVALUE(750);
     }
     case 2:
     {
       RETVALUE(1280);
     }
     case 3:
     {
       RETVALUE(1920);
     }
     case 4:
     {
       RETVALUE(2560);
     }
     case 5:
     {
       RETVALUE(5120);
     }
     case 6:
     {
       RETVALUE(10240);
     }
     default:
     {
       RETVALUE(0);
     }
  }
}

/***********************************************************
*
*     Func : tipFillMacLcUeRecfg
*
*
*     Desc : Fill MAC Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipFillMacLcUeRecfg
(
LcConfigInfo       *lchUeReCfg,
RgrLchCfg          *rgrLchUeReCfg,
TipL3RgDat         *rgCfgDat
)
#else
PUBLIC S16 tipFillMacLcUeRecfg(lchUeReCfg, lchUeReCfg, rgCfgDat)
LcConfigInfo       *lchUeReCfg;
RgrLchCfg          *rgrLchUeReCfg;
TipL3CfgDat        *rgCfgDat;
#endif
{
   
   TRC3(tipFillMacLcUeRecfg);

   lchUeReCfg->lcConfigType = 1;/*0= Create LC */
   lchUeReCfg->lchId = rgrLchUeReCfg->lcId;
   rgCfgDat->lchId[rgCfgDat->lchIdCnt] = lchUeReCfg->lchId;  
   rgCfgDat->lchIdCnt++;  
   lchUeReCfg->dirInfo = 3;/* Bi-direciton*/
   lchUeReCfg->ulLcInfo.lcgId = rgrLchUeReCfg->ulLchQciInfo.lcgId;
   /* Not supported in RGR interface */
   lchUeReCfg->dlLcInfo.lchPriority = 1; /* Currently Hardcoded to 1 */
   lchUeReCfg->qosConfigInfo.qci = rgrLchUeReCfg->dlInfo.dlQos.qci;
   lchUeReCfg->qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateDl = rgrLchUeReCfg->dlInfo.dlQos.mbr;
   lchUeReCfg->qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateUl = 1;/* Currently hardcoded to 1*/
   lchUeReCfg->qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateDl = rgrLchUeReCfg->dlInfo.dlQos.gbr;
   lchUeReCfg->qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateUl = 1; /* Currently hardcoded to 1*/
 
   RETVALUE(ROK);
}/*tipFillMacLcUeRecfg*/


/***********************************************************
*
*     Func : tipFillMacUeRecfg
*
*
*     Desc : Fill MAC Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipFillMacUeRecfg
(
MacUeReconfigReq   *ueReCfgReq,
RgrUeRecfg         *rgrUeReCfg
)
#else
PUBLIC S16 tipFillMacUeRecfg(ueReCfgReq, rgrUeReCfg)
MacUeReconfigReq   *ueReCfgReq,
RgrUeRecfg         *rgrUeReCfg
#endif
{
   TRC3(tipFillMacUeRecfg);

   tipGetUeIndex(rgrUeReCfg->cellId, rgrUeReCfg->newCrnti, &ueReCfgReq->ueIndex);
   ueReCfgReq->oldCRnti = rgrUeReCfg->oldCrnti;          
   ueReCfgReq->newCRnti = rgrUeReCfg->newCrnti;          

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_TXMODE_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 0);
      ueReCfgReq->transmissionModeConfigInfo.transmissionModePresent = rgrUeReCfg->txMode.pres;
      ueReCfgReq->transmissionModeConfigInfo.transmissionMode = rgrUeReCfg->txMode.txModeEnum;

      ueReCfgReq->bitMask |= (1 << 8);
      ueReCfgReq->cbSubsetRestrictionConfigInfo.cbSubsetRestrictionflag = rgrUeReCfg->ueCodeBookRstRecfg.pres;
      ueReCfgReq->cbSubsetRestrictionConfigInfo.cbBitmap[0] = rgrUeReCfg->ueCodeBookRstRecfg.pmiBitMap[0];
      ueReCfgReq->cbSubsetRestrictionConfigInfo.cbBitmap[1] = rgrUeReCfg->ueCodeBookRstRecfg.pmiBitMap[1];
   }
   else
   {
      ueReCfgReq->transmissionModeConfigInfo.transmissionModePresent = FALSE;
   }

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_APRD_DLCQI_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 1);
      ueReCfgReq->dlCqiConfigInfo.aperiodicCqiConfigInfo.present = rgrUeReCfg->aprdDlCqiRecfg.pres;
      ueReCfgReq->dlCqiConfigInfo.aperiodicCqiConfigInfo.aperiodicCqiMode = rgrUeReCfg->aprdDlCqiRecfg.aprdModeEnum;
   }
   else
   {
      ueReCfgReq->dlCqiConfigInfo.aperiodicCqiConfigInfo.present = FALSE;
   }

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_PCQI_RECFG)
   {
      if(rgrUeReCfg->cqiCfg.type == 1)/*1== SETUP*/
      {
         ueReCfgReq->bitMask |= (1 << 10);
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.present = TRUE;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.cqiPucchResourceIndex = rgrUeReCfg->cqiCfg.cqiSetup.cqiPResIdx;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.cqiPmiConfigurationIndex = rgrUeReCfg->cqiCfg.cqiSetup.cqiPCfgIdx;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.k = rgrUeReCfg->cqiCfg.cqiSetup.k;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.periodicCqiMode = rgrUeReCfg->cqiCfg.cqiSetup.prdModeEnum;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.simultaneousAckNackAndCqi = rgrUeReCfg->cqiCfg.cqiSetup.sANCQI;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.riEnableFlag = rgrUeReCfg->cqiCfg.cqiSetup.riEna;
         ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.riConfigIndex = rgrUeReCfg->cqiCfg.cqiSetup.riCfgIdx;
         //      U8   cqiRepType;  /*!< Wideband CQI = 1  Subband CQI =2 */
      }
   }
   else
   {
      ueReCfgReq->dlCqiConfigInfo.periodicCqiConfigInfo.present = FALSE;
   }

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_PCQI_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 2);
      ueReCfgReq->ulHarqConfigInfo.maxUlHarqTransmissions = rgrUeReCfg->ueUlHqRecfg.maxUlHqTx;

      ueReCfgReq->bitMask |= (1 << 3);
      ueReCfgReq->ueQosConfigInfo.ambrPresent = rgrUeReCfg->ueQosRecfg.ambrPres;
      ueReCfgReq->ueQosConfigInfo.dlAmbrValue = rgrUeReCfg->ueQosRecfg.dlAmbr;
      ueReCfgReq->ueQosConfigInfo.ulByteRate = rgrUeReCfg->ueQosRecfg.ueBr;
   }

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_PCQI_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 4);
      ueReCfgReq->ueTaTimerConfigInfo.present = rgrUeReCfg->ueTaTmrRecfg.pres;
      ueReCfgReq->ueTaTimerConfigInfo.taTimer = tipGetTipTaVal(rgrUeReCfg->ueTaTmrRecfg.taTmr);
   }
   else
   {
      ueReCfgReq->ueTaTimerConfigInfo.present = FALSE;
   }

   if(rgrUeReCfg->ueUlPwrRecfg.uePuschPwr.pres && rgrUeReCfg->ueUlPwrRecfg.uePucchPwr.pres)
   {
      ueReCfgReq->bitMask |= (1 << 5);
      ueReCfgReq->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.present = rgrUeReCfg->ueUlPwrRecfg.uePuschPwr.pres;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.index = rgrUeReCfg->ueUlPwrRecfg.uePuschPwr.idx;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.tpcRnti = rgrUeReCfg->ueUlPwrRecfg.uePuschPwr.tpcRnti;

      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.present = rgrUeReCfg->ueUlPwrRecfg.uePucchPwr.pres;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.index = rgrUeReCfg->ueUlPwrRecfg.uePucchPwr.idx;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.tpcRnti = rgrUeReCfg->ueUlPwrRecfg.uePucchPwr.tpcRnti;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.accumulatedFlag = rgrUeReCfg->ueUlPwrRecfg.isAccumulated;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.deltaMcsFlag = rgrUeReCfg->ueUlPwrRecfg.isDeltaMCSEnabled;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.p0UePusch = rgrUeReCfg->ueUlPwrRecfg.p0UePusch;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.p0UePucch = rgrUeReCfg->ueUlPwrRecfg.p0UePucch;
   }
   else
   {
      ueReCfgReq->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.present = FALSE;
      ueReCfgReq->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.present = FALSE;
   }

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_PCQI_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 6);
      ueReCfgReq->ueMeasurementGapConfigInfo.ueMeasurementGapFlag = rgrUeReCfg->ueMeasGapRecfg.isMesGapEnabled;
      ueReCfgReq->ueMeasurementGapConfigInfo.gapPeriod = rgrUeReCfg->ueMeasGapRecfg.gapPrd;
      ueReCfgReq->ueMeasurementGapConfigInfo.gapOffset = rgrUeReCfg->ueMeasGapRecfg.gapOffst;
   }
   else
   {
      ueReCfgReq->ueMeasurementGapConfigInfo.ueMeasurementGapFlag = FALSE;
   }

   //ueReCfgReq->bitMask |= (1 << 7);

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_UECAT_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 9);
      ueReCfgReq->ueCategory = rgrUeReCfg->ueCatEnum;
   }

   if(rgrUeReCfg->srsCfg.type == 1)
   {
      ueReCfgReq->bitMask |= (1 << 11);
      ueReCfgReq->srsUeConfigInfo.srsConfigFlag = TRUE;
      ueReCfgReq->srsUeConfigInfo.srsConfigIndex = rgrUeReCfg->srsCfg.srsSetup.srsCfgIdx;
      ueReCfgReq->srsUeConfigInfo.srsBandwidth = rgrUeReCfg->srsCfg.srsSetup.srsBw;
      ueReCfgReq->srsUeConfigInfo.srsHoppingBandwidth = rgrUeReCfg->srsCfg.srsSetup.srsHopBw;
      ueReCfgReq->srsUeConfigInfo.srsCyclicShift = rgrUeReCfg->srsCfg.srsSetup.cycShift;
      ueReCfgReq->srsUeConfigInfo.duration = rgrUeReCfg->srsCfg.srsSetup.duration;
      ueReCfgReq->srsUeConfigInfo.transmissionComb = rgrUeReCfg->srsCfg.srsSetup.txComb;
      ueReCfgReq->srsUeConfigInfo.frequencyDomainPosition = rgrUeReCfg->srsCfg.srsSetup.fDomPosi;
   }

   if(rgrUeReCfg->srCfg.type == 1)
   {
      ueReCfgReq->bitMask |= (1 << 12);
      ueReCfgReq->srConfigInfo.srConfigFlag = TRUE;
      ueReCfgReq->srConfigInfo.srConfigIndex = rgrUeReCfg->srCfg.srSetup.srCfgIdx;
      ueReCfgReq->srConfigInfo.srResourceIndex = rgrUeReCfg->srCfg.srSetup.srResIdx;
   }

   if(rgrUeReCfg->ueRecfgTypes & RGR_UE_UECAT_RECFG)
   {
      ueReCfgReq->bitMask |= (1 << 13);
      ueReCfgReq->ueDrxConfigInfo.drxEnabledFlag = rgrUeReCfg->ueDrxRecfg.isDrxEnabled;
#ifdef LTEMAC_R9
      ueReCfgReq->ueDrxConfigInfo.cqiMask = rgrUeReCfg->ueDrxRecfg.cqiMask;
#endif
      ueReCfgReq->ueDrxConfigInfo.drxInactivitytimer = rgrUeReCfg->ueDrxRecfg.drxInactvTmr;
      ueReCfgReq->ueDrxConfigInfo.drxOnDurationTimer = rgrUeReCfg->ueDrxRecfg.drxOnDurTmr;
      ueReCfgReq->ueDrxConfigInfo.drxRetransmissionTimer = rgrUeReCfg->ueDrxRecfg.drxRetxTmr;
      ueReCfgReq->ueDrxConfigInfo.longDrxCycle = rgrUeReCfg->ueDrxRecfg.drxLongCycleOffst.longDrxCycle;
      ueReCfgReq->ueDrxConfigInfo.longDrxCycleStartOffset = rgrUeReCfg->ueDrxRecfg.drxLongCycleOffst.drxStartOffst;
      ueReCfgReq->ueDrxConfigInfo.shortDrxPresent = rgrUeReCfg->ueDrxRecfg.drxShortDrx.pres;
      ueReCfgReq->ueDrxConfigInfo.shortDrxCycle = rgrUeReCfg->ueDrxRecfg.drxShortDrx.shortDrxCycle;
      ueReCfgReq->ueDrxConfigInfo.shortDrxCycleTimer = rgrUeReCfg->ueDrxRecfg.drxShortDrx.drxShortCycleTmr;
   }
   else
   {
      ueReCfgReq->ueDrxConfigInfo.drxEnabledFlag = FALSE;
   }


   //ueReCfgReq->bitMask |= (1 << 14);
   if(rgrUeReCfg->uePdschDedCfg.uepACfg.pAPrsnt)
   {
      ueReCfgReq->bitMask |= (1 << 15);
      ueReCfgReq->uePdschConfigInfo.uePdschPAConfigFlag = rgrUeReCfg->uePdschDedCfg.uepACfg.pAPrsnt;
      ueReCfgReq->uePdschConfigInfo.pA = rgrUeReCfg->uePdschDedCfg.uepACfg.pA;
   }
   else
   {
      ueReCfgReq->uePdschConfigInfo.uePdschPAConfigFlag = FALSE;
   }

   if(rgrUeReCfg->puschDedCfg.pres)
   {
      ueReCfgReq->bitMask |= (1 << 16);
      ueReCfgReq->uePuschConfigInfo.uePuschConfigSupport = rgrUeReCfg->puschDedCfg.pres;
      ueReCfgReq->uePuschConfigInfo.harqBetaOffset = rgrUeReCfg->puschDedCfg.bACKIdx;
      ueReCfgReq->uePuschConfigInfo.riBetaOffset = rgrUeReCfg->puschDedCfg.bRIIdx;
      ueReCfgReq->uePuschConfigInfo.cqiBetaOffset = rgrUeReCfg->puschDedCfg.bCQIIdx;
   }
   else
   {
      ueReCfgReq->uePuschConfigInfo.uePuschConfigSupport = FALSE;
   }

   ueReCfgReq->ttiBundlingEnable = rgrUeReCfg->isTtiBundlEnabled;
 
   RETVALUE(ROK);
}/*tipFillMacUeRecfg*/

/***********************************************************
*
*     Func : tipFillMacCellCfg
*
*
*     Desc : Fill MAC Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipFillMacCellCfg
(
MacCellConfigReq   *cellCfgReq,
RgrCellCfg         *rgrCellCfg
)
#else
PUBLIC S16 tipFillMacCellCfg(cellCfgReq, cfgReqInfo)
MacCellConfigReq   *cellCfgReq;
RgrCellCfg         *rgrCellCfg;
#endif
{
   WrSib2Params       *sib2Parms = NULLP;
   WrCellCb           *cellCb = NULLP;
   #ifdef TIP_L3
   LwrSchedEnbCfg     *schEnbCfg = NULLP;
   #endif

   TRC3(tipFillMacCellCfg);

   cellCfgReq->cyclicPrefix = rgrCellCfg->isCpUlExtend;
   cellCfgReq->enable64Qam  = rgrCellCfg->cellModSchm;
   cellCfgReq->cfiValue = rgrCellCfg->cfiCfg.cfi;
   cellCfgReq->dynamicCfiEnable = rgrCellCfg->isDynCfiEnb;
   cellCfgReq->harqConfigInfo.maxDlHarqTransmissions = rgrCellCfg->dlHqCfg.maxDlHqTx;
   cellCfgReq->harqConfigInfo.maxMsg4HarqTransmissions = rgrCellCfg->dlHqCfg.maxMsg4HqTx;
   cellCfgReq->rntiConfigInfo.startRnti = rgrCellCfg->macRnti.startRnti;
   cellCfgReq->rntiConfigInfo.endRnti = (rgrCellCfg->macRnti.startRnti + rgrCellCfg->macRnti.size );
   cellCfgReq->pMax = rgrCellCfg->pMax;
   cellCfgReq->bwInfo.dlBandwidth = rgrCellCfg->bwCfg.dlTotalBw;
   cellCfgReq->bwInfo.ulBandwidth = rgrCellCfg->bwCfg.ulTotalBw;
   cellCfgReq->phichConfigInfo.phichResource = rgrCellCfg->phichCfg.ngEnum;
   cellCfgReq->phichConfigInfo.phichDuration = rgrCellCfg->phichCfg.isDurExtend;
   cellCfgReq->pucchConfigInfo.resourceSize = rgrCellCfg->pucchCfg.resourceSize;
   cellCfgReq->pucchConfigInfo.deltaShift = rgrCellCfg->pucchCfg.deltaShift;
   cellCfgReq->pucchConfigInfo.n1PucchAckNack = rgrCellCfg->pucchCfg.n1PucchAn;
   cellCfgReq->pucchConfigInfo.cyclicShift = rgrCellCfg->pucchCfg.cyclicShift;
   cellCfgReq->srsConfigInfo.cellSpecificSrsEnable  = rgrCellCfg->srsCfg.isSrsCfgSetup;
   cellCfgReq->srsConfigInfo.srsSubframeConfiguration = rgrCellCfg->srsCfg.srsSubFrameCfg;
   cellCfgReq->srsConfigInfo.srsBwConfigInfo = rgrCellCfg->srsCfg.srsBwEnum;
   cellCfgReq->rachConfigInfo.raWindowSize = rgrCellCfg->rachCfg.raWinSize;
   cellCfgReq->rachConfigInfo.maxMsg3HarqTransmissions = rgrCellCfg->rachCfg.maxMsg3Tx;
   cellCfgReq->rachConfigInfo.numberOfRAPreambles = rgrCellCfg->rachCfg.numRaPreamble;
   cellCfgReq->rachConfigInfo.sizeOfRAPreambleinGroupA = rgrCellCfg->rachCfg.sizeRaPreambleGrpA;
   cellCfgReq->rachConfigInfo.messageSizeGroupA = rgrCellCfg->rachCfg.msgSizeGrpA;
   cellCfgReq->rachConfigInfo.contentionResolutionTimer = rgrCellCfg->rachCfg.contResTmr;
   cellCfgReq->numOfUsersPerTTI.numberOfDlUsersPerTTI= rgrCellCfg->maxDlUeNewTxPerTti;
   cellCfgReq->numOfUsersPerTTI.numberOfUlUsersPerTTI= rgrCellCfg->maxUlUeNewTxPerTti;
   cellCfgReq->dlPowerControlConfigInfo.phichPowerOffset = 6000;// L3 is not filling this parameter rgrCellCfg->phichTxPwrOffset;
   cellCfgReq->l3SfPeriodicity = rgrCellCfg->rrmTtiIndPrd * 10;

#ifdef TIP_L3
   schEnbCfg = wrGetSchedEnbCfg();
   cellCfgReq->bwInfo.duplexingMode = FDD;
   cellCfgReq->schedulerSpecificConfigInfo.dlSchedulingType= schEnbCfg->dlSchType;
   cellCfgReq->schedulerSpecificConfigInfo.ulSchedulingType= schEnbCfg->ulSchType;
   cellCfgReq->numOfTxAntennas = schEnbCfg->numAntPorts;
#endif
   /* Get WR CELLCB to fill below parameter */ 
   WR_EMM_GET_CELLCB(cellCb, rgrCellCfg->cellId);
   if(NULLP == cellCb)
   {
      printf("Invalid CellId received while getting SIB2 parames\n");
      RETVALUE(RFAILED);
   }

   sib2Parms = &cellCb->sib2;
   cellCfgReq->defaultPagingCycle = 2 << (4 + sib2Parms->pcchCfg.defaultPagingCycle);//Aricent Requested change
   cellCfgReq->nB = sib2Parms->pcchCfg.nB;
   cellCfgReq->rachConfigInfo.prachConfigurationIndex = sib2Parms->prachCfg.prachCfgIdx;
   cellCfgReq->rachConfigInfo.prachFrequencyOffset = sib2Parms->prachCfg.prachFreqOffset;
   cellCfgReq->srsConfigInfo.simultaneousAckNackAndSrs = sib2Parms->srsCfg.ackNackSrsSimulTx;
   cellCfgReq->dlfsEnable = 0;//cellCb->schCfg.dlfsSchdType;
   cellCfgReq->ulfsEnable = 0;//cellCb->schCfg.dlfsSchdType;

   cellCfgReq->ulPowerControlConfigInfo.p0NominalPusch = sib2Parms->ulPwrCtrlCfg.p0NominalPusch;
   cellCfgReq->ulPowerControlConfigInfo.alpha = sib2Parms->ulPwrCtrlCfg.alpha;
   cellCfgReq->ulPowerControlConfigInfo.p0NominalPucch = sib2Parms->ulPwrCtrlCfg.p0NominlPucch;
   cellCfgReq->ulPowerControlConfigInfo.deltaPreambleMessage3 = sib2Parms->ulPwrCtrlCfg.deltaPeambleMsg3;
   cellCfgReq->ulPowerControlConfigInfo.format3PucchStartTpcRnti = rgrCellCfg->pwrCfg.pucchPwrFmt3.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3PucchEndRnti = rgrCellCfg->pwrCfg.pucchPwrFmt3.size + 
                                                                  rgrCellCfg->pwrCfg.pucchPwrFmt3.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3APucchStartTpcRnti = rgrCellCfg->pwrCfg.pucchPwrFmt3a.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3APucchEndRnti = rgrCellCfg->pwrCfg.pucchPwrFmt3a.size +
                                                                rgrCellCfg->pwrCfg.pucchPwrFmt3a.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3PuschStartTpcRnti = rgrCellCfg->pwrCfg.puschPwrFmt3.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3PuschEndRnti = rgrCellCfg->pwrCfg.puschPwrFmt3.size +
                                                                     rgrCellCfg->pwrCfg.puschPwrFmt3.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3APuschStartTpcRnti = rgrCellCfg->pwrCfg.puschPwrFmt3a.startTpcRnti;
   cellCfgReq->ulPowerControlConfigInfo.format3APuschEndRnti = rgrCellCfg->pwrCfg.puschPwrFmt3a.size +
                                                                  rgrCellCfg->pwrCfg.puschPwrFmt3a.startTpcRnti;
   cellCfgReq->puschConfigInfo.numberOfSubBands = sib2Parms->puschCfg.nSB;
   cellCfgReq->puschConfigInfo.hoppingMode = (sib2Parms->puschCfg.hoppingMode == WR_INTRA_SUBFRAME_HOPPING)?TRUE:FALSE;
   cellCfgReq->puschConfigInfo.hopOffset = 0;

#if 1 /*manjappa TODO hardcoded values */
   cellCfgReq->dlPowerControlConfigInfo.pcfichPowerOffset = 6000;
   cellCfgReq->dlPowerControlConfigInfo.pdcchPowerOffset = 6000;
   cellCfgReq->dlPowerControlConfigInfo.pbchTransmissionPower = 6000;
   cellCfgReq->dlPowerControlConfigInfo.pchTransmissionPower = 6000;
#endif
 RETVALUE(ROK);
}/*tipFillMacCellCfg*/

/***********************************************************
*
*     Func : tipFillMacLcgCfg
*
*
*     Desc : Fill MAC LCG Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipFillMacLcgCfg
(
LcConfigInfo     *lcgInfo,
RgrLcgCfg        *lcgCfg
)
#else
PUBLIC S16 tipFillMacLcgCfg(lcgInfo, lcgCfg)
LcConfigInfo     *lchInfo;
RgrLcgCfg        *lcgCfg;
#endif
{
   TRC3(tipFillMacLcgCfg);
   
   lcgInfo->ulLcInfo.lcgId = lcgCfg->ulInfo.lcgId; 
   lcgInfo->qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateUl = lcgCfg->ulInfo.mbr; //1
   lcgInfo->qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateUl = lcgCfg->ulInfo.gbr; //1

 RETVALUE(ROK);
}/*tipFillMacLcgCfg*/

/***********************************************************
*
*     Func : tipFillMacLchCfg
*
*
*     Desc : Fill MAC LCH Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipFillMacLchCfg
(
LcConfigInfo     *lchInfo,
RgrLchCfg        *lchCfg
)
#else
PUBLIC S16 tipFillMacLchCfg(lchInfo, lchCfg)
LcConfigInfo     *lchInfo;
RgrLchCfg        *lchCfg;
#endif
{
   TRC3(tipFillMacLchCfg);
   
   lchInfo->lcConfigType = 0; // 1 - setup
   lchInfo->lchId = lchCfg->lcId; //WR_PDCP_ID_SRB1
   lchInfo->dirInfo = BOTH;
   lchInfo->dlLcInfo.lchPriority = 1; //TODO- What needs to be sent?
   lchInfo->qosConfigInfo.qci = lchCfg->dlInfo.dlQos.qci; //5
   lchInfo->qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateDl = lchCfg->dlInfo.dlQos.mbr; //1
   lchInfo->qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateDl = lchCfg->dlInfo.dlQos.gbr; //1

 RETVALUE(ROK);
}/*tipFillMacLchCfg*/

/***********************************************************
*
*     Func : tipFillMacUeCfg
*
*
*     Desc : Fill MAC UE Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipFillMacUeCfg
(
MacUeConfigReq   *rcvUeCfg,
RgrUeCfg         *rgrUeCfg
)
#else
PUBLIC S16 tipFillMacUeCfg(rcvUeCfg, cfgReqInfo)
MacUeConfigReq   *rcvUeCfg;
RgrUeCfg         *rgrUeCfg;
#endif
{
   AperiodicCqiConfig *aCqiCfg;
   PeriodicCqiConfig  *pCqiCfg;
   RgrUeDlPCqiSetup   *pcqiSetup;
   UePuschGroupPowerControlConfig *uePuschGrpPcInfo;
   UePucchGroupPowerControlConfig *uePucchGrpPcInfo;
   UeDrxConfiguration *ueDrxCfg;

   TRC3(tipFillMacUeCfg);

   rcvUeCfg->ueInfo.cRnti = rgrUeCfg->crnti;
   tipGetUeIndex(rgrUeCfg->cellId, rgrUeCfg->crnti, &rcvUeCfg->ueInfo.ueIndex);
   rcvUeCfg->ueConfigPresent = TRUE; 
   rcvUeCfg->ueCategory = (U8)rgrUeCfg->ueCatEnum;
   rcvUeCfg->ttiBundlingEnable = rgrUeCfg->isTtiBundlEnabled;
   rcvUeCfg->transmissionModeConfigInfo.transmissionModePresent = 
                              rgrUeCfg->txMode.pres;   
   rcvUeCfg->transmissionModeConfigInfo.transmissionMode =
                    (U8)rgrUeCfg->txMode.txModeEnum;  
   aCqiCfg = &rcvUeCfg->dlCqiConfigInfo.aperiodicCqiConfigInfo;
   aCqiCfg->present = rgrUeCfg->ueDlCqiCfg.aprdCqiCfg.pres;
   aCqiCfg->aperiodicCqiMode = rgrUeCfg->ueDlCqiCfg.aprdCqiCfg.aprdModeEnum;
   pCqiCfg = &rcvUeCfg->dlCqiConfigInfo.periodicCqiConfigInfo;
   pCqiCfg->present = rgrUeCfg->ueDlCqiCfg.prdCqiCfg.type;
   pcqiSetup = &rgrUeCfg->ueDlCqiCfg.prdCqiCfg.cqiSetup;
   pCqiCfg->cqiPucchResourceIndex = pcqiSetup->cqiPResIdx;
   pCqiCfg->cqiPmiConfigurationIndex = pcqiSetup->cqiPCfgIdx;
   pCqiCfg->k = pcqiSetup->k;
   pCqiCfg->periodicCqiMode = pcqiSetup->prdModeEnum;
   pCqiCfg->simultaneousAckNackAndCqi = pcqiSetup->sANCQI;
   pCqiCfg->riEnableFlag = pcqiSetup->riEna;
   pCqiCfg->riConfigIndex = pcqiSetup->riCfgIdx;
   rcvUeCfg->ulHarqConfigInfo.maxUlHarqTransmissions = rgrUeCfg->ueUlHqCfg.maxUlHqTx;
   uePuschGrpPcInfo = 
     &rcvUeCfg->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo;
   uePucchGrpPcInfo = 
     &rcvUeCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo;
   uePuschGrpPcInfo->present = rgrUeCfg->ueUlPwrCfg.uePuschPwr.pres;
   uePuschGrpPcInfo->index = rgrUeCfg->ueUlPwrCfg.uePuschPwr.idx; 
   uePuschGrpPcInfo->tpcRnti = rgrUeCfg->ueUlPwrCfg.uePuschPwr.tpcRnti;
   uePucchGrpPcInfo->present = rgrUeCfg->ueUlPwrCfg.uePucchPwr.pres;
   uePucchGrpPcInfo->index = rgrUeCfg->ueUlPwrCfg.uePucchPwr.idx; 
   uePucchGrpPcInfo->tpcRnti = rgrUeCfg->ueUlPwrCfg.uePucchPwr.tpcRnti;
   uePucchGrpPcInfo->accumulatedFlag = rgrUeCfg->ueUlPwrCfg.isAccumulated;
   uePucchGrpPcInfo->deltaMcsFlag = rgrUeCfg->ueUlPwrCfg.isDeltaMCSEnabled;
   uePucchGrpPcInfo->p0UePusch = rgrUeCfg->ueUlPwrCfg.p0UePusch;
   uePucchGrpPcInfo->p0UePucch = rgrUeCfg->ueUlPwrCfg.p0UePucch;
   rcvUeCfg->ueQosConfigInfo.ambrPresent = rgrUeCfg->ueQosCfg.ambrPres;
   rcvUeCfg->ueQosConfigInfo.dlAmbrValue = rgrUeCfg->ueQosCfg.dlAmbr;
   rcvUeCfg->ueQosConfigInfo.ulByteRate = rgrUeCfg->ueQosCfg.ueBr;
   rcvUeCfg->ueTaTimerConfigInfo.present = TRUE;//rgrUeCfg->ueTaTmrCfg.pres; 
   /*Aricent LL2 expect always TA value even though its infinet value configured*/
   rcvUeCfg->ueTaTimerConfigInfo.taTimer = tipGetTipTaVal(rgrUeCfg->ueTaTmrCfg.taTmr);
   ueDrxCfg = &rcvUeCfg->ueDrxConfigInfo;
   ueDrxCfg->drxEnabledFlag = rgrUeCfg->ueDrxCfg.isDrxEnabled;
   ueDrxCfg->cqiMask = 0;
   ueDrxCfg->drxInactivitytimer = rgrUeCfg->ueDrxCfg.drxInactvTmr;
   ueDrxCfg->drxOnDurationTimer = rgrUeCfg->ueDrxCfg.drxOnDurTmr;
   ueDrxCfg->drxRetransmissionTimer = rgrUeCfg->ueDrxCfg.drxRetxTmr;
   ueDrxCfg->longDrxCycle = rgrUeCfg->ueDrxCfg.drxLongCycleOffst.longDrxCycle;
   ueDrxCfg->longDrxCycleStartOffset = rgrUeCfg->ueDrxCfg.drxLongCycleOffst.drxStartOffst;
   ueDrxCfg->shortDrxPresent = rgrUeCfg->ueDrxCfg.drxShortDrx.pres;
   ueDrxCfg->shortDrxCycle = rgrUeCfg->ueDrxCfg.drxShortDrx.shortDrxCycle;
   ueDrxCfg->shortDrxCycleTimer = rgrUeCfg->ueDrxCfg.drxShortDrx.drxShortCycleTmr;
   rcvUeCfg->ueMeasurementGapConfigInfo.ueMeasurementGapFlag =
                  rgrUeCfg->ueMesGapCfg.isMesGapEnabled;
   rcvUeCfg->ueMeasurementGapConfigInfo.gapPeriod =
                 rgrUeCfg->ueMesGapCfg.gapPrd;
   rcvUeCfg->ueMeasurementGapConfigInfo.gapOffset =
                 rgrUeCfg->ueMesGapCfg.gapOffst;
   rcvUeCfg->cbSubsetRestrictionConfigInfo.cbSubsetRestrictionflag =
                 rgrUeCfg->ueCodeBookRstCfg.pres;
   rcvUeCfg->cbSubsetRestrictionConfigInfo.cbBitmap[0] =
                 rgrUeCfg->ueCodeBookRstCfg.pmiBitMap[0];
   rcvUeCfg->cbSubsetRestrictionConfigInfo.cbBitmap[1] =
                 rgrUeCfg->ueCodeBookRstCfg.pmiBitMap[1];
   rcvUeCfg->srsUeConfigInfo.srsConfigFlag = rgrUeCfg->srsCfg.type;
   rcvUeCfg->srsUeConfigInfo.srsConfigIndex = rgrUeCfg->srsCfg.srsSetup.srsCfgIdx;
   rcvUeCfg->srsUeConfigInfo.srsBandwidth = (U8)rgrUeCfg->srsCfg.srsSetup.srsBw;
   rcvUeCfg->srsUeConfigInfo.srsHoppingBandwidth = (U8)rgrUeCfg->srsCfg.srsSetup.srsHopBw;
   rcvUeCfg->srsUeConfigInfo.srsCyclicShift = (U8)rgrUeCfg->srsCfg.srsSetup.cycShift;
   rcvUeCfg->srsUeConfigInfo.duration = rgrUeCfg->srsCfg.srsSetup.duration;
   rcvUeCfg->srsUeConfigInfo.transmissionComb = rgrUeCfg->srsCfg.srsSetup.txComb;
   rcvUeCfg->srsUeConfigInfo.frequencyDomainPosition = rgrUeCfg->srsCfg.srsSetup.fDomPosi;
   rcvUeCfg->srConfigInfo.srConfigFlag = rgrUeCfg->srCfg.type;
   rcvUeCfg->srConfigInfo.srConfigIndex = rgrUeCfg->srCfg.srSetup.srCfgIdx;
   rcvUeCfg->srConfigInfo.srResourceIndex = rgrUeCfg->srCfg.srSetup.srResIdx;
   rcvUeCfg->uePuschConfigInfo.uePuschConfigSupport = rgrUeCfg->puschDedCfg.pres;
   rcvUeCfg->uePuschConfigInfo.harqBetaOffset = rgrUeCfg->puschDedCfg.bACKIdx;
   rcvUeCfg->uePuschConfigInfo.riBetaOffset = rgrUeCfg->puschDedCfg.bRIIdx;
   rcvUeCfg->uePuschConfigInfo.cqiBetaOffset = rgrUeCfg->puschDedCfg.bCQIIdx;
   rcvUeCfg->uePdschConfigInfo.uePdschPAConfigFlag = rgrUeCfg->uePdschDedCfg.uepACfg.pAPrsnt;
   rcvUeCfg->uePdschConfigInfo.pA = (U8)rgrUeCfg->uePdschDedCfg.uepACfg.pA;
   rcvUeCfg->ueRel = rgrUeCfg->accessStratumRls;
   rcvUeCfg->numberOfLcs = 1; 

 RETVALUE(ROK);
}/*tipFillMacUeCfg*/

PRIVATE void tipMacFillReestCfg
(
MacUeReconfigReq *ueRecfg,
RgrUeRecfg       *rgrUeReCfg
)
{
   //tipGetUeIndex(rgrUeReCfg->cellId, rgrUeReCfg->newCrnti, &ueRecfg->ueIndex);
   tipGetUeIndex(rgrUeReCfg->cellId, rgrUeReCfg->oldCrnti, &ueRecfg->ueIndex);

   ueRecfg->bitMask |= MAC_UEIDCHANGE_RECONFIGURATION;
   ueRecfg->oldCRnti = rgrUeReCfg->oldCrnti;
   ueRecfg->newCRnti = rgrUeReCfg->newCrnti;

   ueRecfg->bitMask |= MAC_UL_HARQ_RECONFIGURATION;
   ueRecfg->ulHarqConfigInfo.maxUlHarqTransmissions =
      rgrUeReCfg->ueUlHqRecfg.maxUlHqTx;

   RETVOID;
}

/***********************************************************
*
*     Func : tipSendMacCfgReq
*
*
*     Desc : Configuration Request from RRM to MAC for 
*            configuring Cell
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendMacCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 tipSendMacCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrCfgReqInfo * cfgReqInfo;
#endif
{
   MacCellConfigReq   *cellCfgReq;
   MacUeConfigReq     *rcvUeCfg;
   MacUeReconfigReq   *ueReCfg;
   MacUeDeleteReq     *ueDelReq;
   U8                 sendBuf[MAX_BUFF_LEN_L2_L3];
   U32                cellId = 0;
   TipPacket          *hdr = NULLP;
   U32                msgLen = 0; 
   U32                lcLen; 
   U32                msgId = 0;
   LcConfigInfo       lcCfgInfo[10] = {{0},{0},{0}};
   U8                 lcCnt = 0;
   S16                suId = 0;
   U64                key = 0LL;
   U8                 freeCfgReq = TRUE;
   U8                 sendpacket  = TRUE;
   U8                 hashLstTransId = FALSE;
   TipL3RgDat         *rgCfgDat = NULLP;

   TRC3(tipSendMacCfgReq);
   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   hdr = (TipPacket*)sendBuf;

   switch(cfgReqInfo->action)
   {
      case RGR_CONFIG:
      {
         if(cfgReqInfo->u.cfgInfo.cfgType == RGR_CELL_CFG) 
         {
            TipCellTransInfo *tipCellInfo = NULLP;
            cellId = cfgReqInfo->u.cfgInfo.u.cellCfg.cellId;
            TIP_GET_NEW_CELLCB(tipCellInfo);
            if(NULLP == tipCellInfo)
            {
               RLOG_ARG0(L_FATAL, DBG_CELLID, cellId,
                     "New Cell CB not found. Reconfigure number of cells");
            }
            cellCfgReq = (MacCellConfigReq*)((U8*)sendBuf + TIP_HDR_LEN);
            msgId = MAC_CELLCONFIG_REQ; 
            msgLen = sizeof(MacCellConfigReq) + TIP_HDR_LEN;
            tipFillMacCellCfg(cellCfgReq, &cfgReqInfo->u.cfgInfo.u.cellCfg);
            tipCellInfo->cellId = cellId;
            cmMemcpy((U8*)&(tipCellInfo->siInfo.siCfgInfo),
                  (U8*)&(cfgReqInfo->u.cfgInfo.u.cellCfg.siCfg),
                  sizeof(RgrSiCfg));
         }
         else if(cfgReqInfo->u.cfgInfo.cfgType == RGR_UE_CFG)
         {
            rcvUeCfg = (MacUeConfigReq*)((U8*)sendBuf + TIP_HDR_LEN);
            tipFillMacUeCfg(rcvUeCfg, &cfgReqInfo->u.cfgInfo.u.ueCfg);
            TipUtlPrepKeyAndStoreMacTrans(pst, TIP_MAC_CFG, 
                  cfgReqInfo->u.cfgInfo.u.ueCfg.cellId,
                  cfgReqInfo->u.cfgInfo.u.ueCfg.crnti, TIP_LCL_KEY, 0,
                  &rgCfgDat, &key);
            if(NULLP != rgCfgDat)
            {
               cmMemcpy((U8*)&(rgCfgDat->mapperUeCfg),(U8*)(rcvUeCfg),sizeof(MacUeConfigReq));
            }
            NxLiRgrCfgCfm(pst, suId, transId, 0);
            sendpacket = FALSE;
         }
         /* connection setup - SRB1 */
         else if(cfgReqInfo->u.cfgInfo.cfgType == RGR_LCH_CFG &&
               (cfgReqInfo->u.cfgInfo.u.lchCfg.lcId == 1))
         {
            rgCfgDat = TipUtlGetStoredL3MacData(
                  cfgReqInfo->u.cfgInfo.u.lchCfg.cellId,
                  cfgReqInfo->u.cfgInfo.u.lchCfg.crnti, TIP_LCL_KEY);
            if(NULLP != rgCfgDat)
            {
               tipFillMacLchCfg(rgCfgDat->mapperUeCfg.lcInfo, &cfgReqInfo->u.cfgInfo.u.lchCfg);
            }
            NxLiRgrCfgCfm(pst, suId, transId, 0); 
            sendpacket = FALSE;
         }
         /* connection setup - SRB1 */
         else if(cfgReqInfo->u.cfgInfo.cfgType == RGR_LCG_CFG &&
               (cfgReqInfo->u.cfgInfo.u.lcgCfg.ulInfo.lcgId == 0))
         {
            rcvUeCfg = (MacUeConfigReq*)((U8*)sendBuf + TIP_HDR_LEN);
            msgId = MAC_UECONFIG_REQ; 
            msgLen = sizeof(MacUeConfigReq) + TIP_HDR_LEN;
            cellId = cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId;

            rgCfgDat = TipUtlGetStoredL3MacData(
                  cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                  cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti, TIP_LCL_KEY);
            if(NULLP != rgCfgDat)
            {
               tipFillMacLcgCfg(rgCfgDat->mapperUeCfg.lcInfo,
                     &cfgReqInfo->u.cfgInfo.u.lcgCfg);
               cmMemcpy((U8*)(rcvUeCfg),(U8*)&(rgCfgDat->mapperUeCfg),
                     sizeof(MacUeConfigReq));

               /* RGR cfgInfo pointer is not stored for UE CFG and 
                * LCH CFG. Hence delete the node and free the data */
               TipUtlFreeL3Trans(pst, cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                     cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti, TIP_LCL_KEY);
            }
         }
         /* reconfiguration - ICS/ERAB */
         else if(cfgReqInfo->u.cfgInfo.cfgType == RGR_LCH_CFG)
         {
            freeCfgReq = FALSE;
            sendpacket = FALSE;
            rgCfgDat = TipUtlGetStoredL3MacData(
                  cfgReqInfo->u.cfgInfo.u.lchCfg.cellId,
                  cfgReqInfo->u.cfgInfo.u.lchCfg.crnti, TIP_LCL_KEY);
            if(NULLP != rgCfgDat)
            {
               rgCfgDat->schdUeRecfgReq[(rgCfgDat->msgCnt)++] = cfgReqInfo;
            }
         }
         /* reconfiguration - ICS/ERAB */
         else if(cfgReqInfo->u.cfgInfo.cfgType == RGR_LCG_CFG)
         {
            TipL3CfgDat *recfg = NULLP;
            rgCfgDat = TipUtlGetStoredL3MacData(
                  cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                  cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti, TIP_LCL_KEY);
            if(NULLP != rgCfgDat)
            {
               freeCfgReq = FALSE;
               rgCfgDat->schdUeRecfgReq[(rgCfgDat->msgCnt)++] = cfgReqInfo;
               rgCfgDat->lcgCnt++;
               if(rgCfgDat->lcgCnt == 3)
               {
                  ueReCfg = (MacUeReconfigReq*)hdr->message;
                  msgId = MAC_UERECONFIG_REQ; 
                  msgLen = sizeof(MacUeReconfigReq) + TIP_HDR_LEN;
                  /* Currently cell Id updation happending in last message*/
                  cellId = cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId;
                  for(U8 idx = 0; idx < rgCfgDat->msgCnt; idx++)
                  {
                     RgrCfgReqInfo *rgrUeRecfgReq = rgCfgDat->schdUeRecfgReq[idx];
                     if(rgrUeRecfgReq->action == RGR_RECONFIG)
                     {
                        tipFillMacUeRecfg(ueReCfg,
                              &rgrUeRecfgReq->u.recfgInfo.u.ueRecfg);
                     }
                     else
                     {
                        if((rgrUeRecfgReq->u.cfgInfo.cfgType == RGR_LCH_CFG) && 
                              (rgrUeRecfgReq->action == RGR_CONFIG))
                        { 
                           tipFillMacLcUeRecfg(&lcCfgInfo[lcCnt++],
                                 &rgrUeRecfgReq->u.cfgInfo.u.lchCfg, rgCfgDat);
                        }
                        else
                        { 
                           for(U8 idx1 = 0; idx1 < lcCnt; idx1++)
                           {
                              if(rgrUeRecfgReq->u.cfgInfo.u.lcgCfg.ulInfo.lcgId == lcCfgInfo[idx1].ulLcInfo.lcgId)
                              {
                                 lcCfgInfo[idx1].qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateUl = rgrUeRecfgReq->u.cfgInfo.u.lcgCfg.ulInfo.mbr;
                                 lcCfgInfo[idx1].qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateUl = rgrUeRecfgReq->u.cfgInfo.u.lcgCfg.ulInfo.gbr;
                              }
                           }
                        }
                     }
                  }
                  /* freeing the stored cfgreqs */
                  for(U8 idx = 0; idx < rgCfgDat->msgCnt; idx++)
                  {
                     if (ROK != SPutSBuf(pst->region, pst->pool,
                              (Data *)rgCfgDat->schdUeRecfgReq[idx], sizeof(RgrCfgReqInfo)))
                     {
#if (ERRCLASS & ERRCLS_ADD_RES)
                        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                              __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                              (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
                        RETVALUE(RFAILED);
                     }
                  }
                  rgCfgDat->msgCnt = rgCfgDat->lcgCnt = 0;
                  lcLen = sizeof(LcConfigInfo) * lcCnt;
                  msgLen = msgLen + lcLen - sizeof(LcConfigInfo);
                  ueReCfg->numberOfLcs = lcCnt;
                  cmMemcpy((U8*)&(ueReCfg->LcInfo), (U8*)&(lcCfgInfo), lcLen);

                  recfg = TipUtlDelL3TransFrmLst(pst, cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                        (U16)cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti, (U8)TIP_LCL_KEY);

                  deriveTipTransId(transId.trans, hdr);
                  if(NULLP != recfg)
                  {
                     TipUtlStoreTrans(cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                           cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti, (U8)TIP_INTF_KEY,
                           hdr->transId, recfg, &key);
                  }
                  hashLstTransId = TRUE;
                  TIP_EVENT_LOG(cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                        cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti, TIP_MOD_RRC,
                        TIP_MOD_MAC, TIP_MSG_MAC_UERECONFIG_REQ, hdr->transId);
               }
               else
               {
                  sendpacket = FALSE;
               }
            }
            else
            {
               sendpacket = FALSE;
               printf("\nFailed to get L3 MAC transInfo not found for "
                     "[CellId: %d | UEID: %d]\n",
                     cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId,
                     cfgReqInfo->u.cfgInfo.u.lcgCfg.crnti);
            }
         }
         else
         {
            printf("currently this type is not handled (%d)\n", cfgReqInfo->u.cfgInfo.cfgType );
            RETVALUE(ROK);
         }

      }
      break;
      case RGR_RECONFIG:
      {
         if(cfgReqInfo->u.recfgInfo.recfgType == RGR_UE_CFG) 
         {
            if(cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti ==
                  cfgReqInfo->u.recfgInfo.u.ueRecfg.newCrnti)
            {
               TipUtlPrepKeyAndStoreMacTrans(pst, TIP_MAC_CFG,
                     cfgReqInfo->u.recfgInfo.u.ueRecfg.cellId,
                     cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti, TIP_LCL_KEY,
                     0, &rgCfgDat, &key);
               if(NULLP != rgCfgDat)
               {
                  rgCfgDat->schdUeRecfgReq[(rgCfgDat->msgCnt)++] = cfgReqInfo;
                  freeCfgReq = FALSE;
               }
               sendpacket = FALSE;
            }
            else
            {
               /* UE ID Change */
               ueReCfg = (MacUeReconfigReq*)hdr->message;
               msgId = MAC_UERECONFIG_REQ; 
               msgLen = sizeof(MacUeReconfigReq) + TIP_HDR_LEN;
               cellId = cfgReqInfo->u.cfgInfo.u.lcgCfg.cellId;
               tipMacFillReestCfg(ueReCfg, &cfgReqInfo->u.recfgInfo.u.ueRecfg);

               deriveTipTransId(transId.trans, hdr);
               TipUtlPrepKeyAndStoreMacTrans(pst, TIP_MAC_CFG,
                     cfgReqInfo->u.recfgInfo.u.ueRecfg.cellId,
                     cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti, TIP_INTF_KEY,
                     //cfgReqInfo->u.recfgInfo.u.ueRecfg.newCrnti, TIP_INTF_KEY,
                     hdr->transId, &rgCfgDat, &key);
               if(NULLP != rgCfgDat)
               {
                  rgCfgDat->schdUeRecfgReq[(rgCfgDat->msgCnt)++] = cfgReqInfo;
               }
               hashLstTransId = TRUE;
               TIP_EVENT_LOG(cfgReqInfo->u.recfgInfo.u.ueRecfg.cellId,
                     cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti, TIP_MOD_RRC,
                     TIP_MOD_MAC, TIP_MSG_MAC_UERECONFIG_REQ, hdr->transId);
               freeCfgReq = FALSE;
            }
         }
         else if(cfgReqInfo->u.recfgInfo.recfgType == RGR_CELL_CFG)
         {
            TipCellTransInfo *tipCellInfo;
            TIP_GET_CELL_INFO(cfgReqInfo->u.recfgInfo.u.cellRecfg.cellId,
                  tipCellInfo);
            if(NULLP == tipCellInfo)
            {
               RLOG_ARG0(L_FATAL, DBG_CELLID,
                     cfgReqInfo->u.recfgInfo.u.cellRecfg.cellId,
                     "Cell Info not found. Do CellConfig before Reconfig");
            }
            else
            {
               /* update SiCfg */
               cmMemset((U8 *)&tipCellInfo->siInfo, 0, sizeof(TipSiInfo));
               cmMemcpy((U8*)&(tipCellInfo->siInfo.siCfgInfo),
                     (U8*)&(cfgReqInfo->u.recfgInfo.u.cellRecfg.siReCfg),
                     sizeof(RgrSiCfg));
            }
            sendpacket = FALSE;
         }
         else
         {
            printf("currently this type is not handled (%d)\n",
                  cfgReqInfo->u.recfgInfo.recfgType);
            sendpacket = FALSE;
         }
      }
      break;
      case RGR_DELETE:
      {
         if(cfgReqInfo->u.delInfo.delType == RGR_UE_CFG)
         {
            cellId = cfgReqInfo->u.delInfo.u.ueDel.cellId;
            msgId = MAC_UEDELETE_REQ;
            msgLen = sizeof(MacUeDeleteReq) + TIP_HDR_LEN;
            ueDelReq = (MacUeDeleteReq*)((U8*)sendBuf + TIP_HDR_LEN);
            ueDelReq->ueInfo.cRnti = cfgReqInfo->u.delInfo.u.ueDel.crnti;
            tipGetUeIndex(cellId, ueDelReq->ueInfo.cRnti, &ueDelReq->ueInfo.ueIndex);
         }
         else
         {
            printf("currently this type is not handled (%d)\n", cfgReqInfo->u.delInfo.delType );
            RETVALUE(ROK);
         }
      }
      break;
      case RGR_RESET:
      {
         /* send success response assuming UE ID change will follow */
         NxLiRgrCfgCfm(pst, suId, transId, 0);
         sendpacket = FALSE;
      }
      break;
      case RGR_SON_CFG:
      default:
      {
         printf("even is not handled action(%d)\n", cfgReqInfo->action);
         RETVALUE(RFAILED);
      }
      break;
   }

   if(freeCfgReq == TRUE)
   {
      if (SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
               sizeof(RgrCfgReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
         RETVALUE(RFAILED);
      }
   }

   if(sendpacket == TRUE)
   {
      tipFillHdr(pst, cellId, msgId, 0, msgLen, hdr);
      if(hashLstTransId)
      {
         hdr->transId = (U32)(((key >> 16) & 0x0ffff0000) | (key & 0x0ffff));
      }
      else
      {
         deriveTipTransId(transId.trans, hdr);
      }
      RETVALUE(tipSendToCLL2(msgLen , (U8 *)&sendBuf));
   }

   RETVALUE(ROK);
}/*end of tipSendMacCfgReq*/

/***********************************************************
*
*     Func : tipUnpkUeLcgCfg
*
*
*     Desc : unpack MAC Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkUeLcgCfg
(
LcConfigInfo       *tipUeLchCfg,
RgrLcgCfg          *ueLcgCfg,
U64                tipTransId
)
#else
PUBLIC S16 tipUnpkUeLcgCfg(tipUeLchCfg, ueLcgCfg, tipTransId)
LcConfigInfo       *tipUeLchCfg;
RgrLcgCfg          *ueLcgCfg;
U64                tipTransId;
#endif
{
   U64           key;
   TipLL2RgDat   *cfg;

   TRC3(tipUnpkUeLcgCfg)

   key = tipTransId;
   TipFindLL2Trans(key, &cfg);

   if(NULLP == cfg)
   {
      RETVALUE(ROK);
   }

   TipDelLL2Trans(cfg);

   if(tipUeLchCfg->lcConfigType == 1)
   {
      if(cfg->lcg1 || cfg->lcg2 || cfg->lcg3)
      {
         ueLcgCfg->ulInfo.lcgId = tipUeLchCfg->ulLcInfo.lcgId;
         ueLcgCfg->ulInfo.mbr = tipUeLchCfg->qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateUl;
         ueLcgCfg->ulInfo.gbr = tipUeLchCfg->qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateUl;
      }
      if(ueLcgCfg->ulInfo.lcgId == 1)
      {
         cfg->lcg1 = TRUE;
      }
      if(ueLcgCfg->ulInfo.lcgId == 2)
      {
         cfg->lcg2 = TRUE;
      }
      if(ueLcgCfg->ulInfo.lcgId == 3)
      {
         cfg->lcg3 = TRUE;
      }
   }
   TipAddLL2Trans(cfg);
  RETVALUE(ROK);
}
/***********************************************************
*
*     Func : tipUnpkUeLcCfg
*
*
*     Desc : unpack MAC Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkUeLcCfg
(
LcConfigInfo       *tipUeLchCfg,
RgrLchCfg          *ueLchCfg,
U64                tipTransId
)
#else
PUBLIC S16 tipUnpkUeLcCfg(tipUeLchCfg, ueLchCfg, tipTransId)
LcConfigInfo       *tipUeLchCfg;
RgrLchCfg          *ueLchCfg;
U64                tipTransId;
#endif
{
   U64          key;
   TipLL2RgDat  *cfg;

   TRC3(tipUnpkUeLcCfg)

   //key = tipPrepareKey(ueLchCfg->cellId, ueLchCfg->crnti,0);
   key = tipTransId;
   TipFindLL2Trans(key, &cfg);

   if(NULLP == cfg)
   {
      RETVALUE(ROK);
   }

   TipDelLL2Trans(cfg);

   if(tipUeLchCfg->lcConfigType == 1)
   {
      ueLchCfg->lcId   = tipUeLchCfg->lchId;
      cfg->ll2LchId[cfg->ll2LchIdCnt] = ueLchCfg->lcId; 
      cfg->ll2LchIdCnt++;
      if(ueLchCfg->lcId == 2)
      {
         ueLchCfg->lcType = CM_LTE_LCH_DCCH;
         ueLchCfg->dlInfo.dlTrchType = CM_LTE_TRCH_DL_SCH;
      }
      else
      {
         ueLchCfg->lcType = CM_LTE_LCH_DTCH;
         ueLchCfg->dlInfo.dlTrchType = CM_LTE_TRCH_DL_SCH;
      }
      ueLchCfg->dlInfo.dlQos.qci = tipUeLchCfg->qosConfigInfo.qci;
      ueLchCfg->ulLchQciInfo.lcId = tipUeLchCfg->lchId;
      ueLchCfg->ulLchQciInfo.qci = tipUeLchCfg->qosConfigInfo.qci;
      ueLchCfg->ulLchQciInfo.lcgId = tipUeLchCfg->ulLcInfo.lcgId;
      ueLchCfg->lcgId = tipUeLchCfg->ulLcInfo.lcgId;
   
      ueLchCfg->dlInfo.dlQos.mbr = tipUeLchCfg->qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateDl;
      ueLchCfg->dlInfo.dlQos.gbr = tipUeLchCfg->qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateDl ;
   }
   TipAddLL2Trans(cfg);
  RETVALUE(ROK);
}
/***********************************************************
*
*     Func : tipUnpkUeReCfg
*
*
*     Desc : unpack MAC Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkUeReCfg
(
MacUeReconfigReq   *tipUeReCfg,
RgrUeRecfg         *ueReCfg
)
#else
PUBLIC S16 tipUnpkUeReCfg(tipUeReCfg, ueReCfg)
MacUeReconfigReq   *tipUeReCfg;
RgrUeRecfg         *ueReCfg;
#endif
{
   TRC3(tipUnpkUeReCfg);
   if(tipUeReCfg->bitMask & (1 << 10))
   {
      if(tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.present == TRUE)
      {
         ueReCfg->ueRecfgTypes |= RGR_UE_PCQI_RECFG; 
         ueReCfg->cqiCfg.type = 1;
         ueReCfg->cqiCfg.cqiSetup.cqiPResIdx = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.cqiPucchResourceIndex;
         ueReCfg->cqiCfg.cqiSetup.cqiPCfgIdx = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.cqiPmiConfigurationIndex;
         ueReCfg->cqiCfg.cqiSetup.cqiRepType = RGR_UE_PCQI_WB_REP;
         ueReCfg->cqiCfg.cqiSetup.k = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.k;
         ueReCfg->cqiCfg.cqiSetup.prdModeEnum = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.periodicCqiMode;
         ueReCfg->cqiCfg.cqiSetup.sANCQI = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.simultaneousAckNackAndCqi;
         ueReCfg->cqiCfg.cqiSetup.riEna = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.riEnableFlag;
         ueReCfg->cqiCfg.cqiSetup.riCfgIdx = tipUeReCfg->dlCqiConfigInfo.periodicCqiConfigInfo.riConfigIndex;
      }
   }
   if(tipUeReCfg->bitMask & (1 << 1))
   {
      if(tipUeReCfg->dlCqiConfigInfo.aperiodicCqiConfigInfo.present == TRUE)
      {
         ueReCfg->ueRecfgTypes |= RGR_UE_APRD_DLCQI_RECFG; 

         ueReCfg->aprdDlCqiRecfg.pres = tipUeReCfg->dlCqiConfigInfo.aperiodicCqiConfigInfo.present;
         ueReCfg->aprdDlCqiRecfg.aprdModeEnum = tipUeReCfg->dlCqiConfigInfo.aperiodicCqiConfigInfo.aperiodicCqiMode;
      }
   }
   if(tipUeReCfg->bitMask & (1 << 12))
   {
      if(tipUeReCfg->srConfigInfo.srConfigFlag == TRUE)
      {
         ueReCfg->srCfg.type = RGR_SCH_SR_SETUP;

         ueReCfg->srCfg.srSetup.srCfgIdx = tipUeReCfg->srConfigInfo.srConfigIndex;
         ueReCfg->srCfg.srSetup.srResIdx = tipUeReCfg->srConfigInfo.srResourceIndex;
      }
   }

   if(tipUeReCfg->bitMask & (1 << 0))
   {
      if(tipUeReCfg->transmissionModeConfigInfo.transmissionModePresent == TRUE)
      {
         ueReCfg->ueRecfgTypes |= RGR_UE_TXMODE_RECFG; 

         ueReCfg->txMode.tmTrnstnState = RGR_TXMODE_RECFG_CMPLT;;
         ueReCfg->txMode.pres = tipUeReCfg->transmissionModeConfigInfo.transmissionModePresent;
         ueReCfg->txMode.txModeEnum = tipUeReCfg->transmissionModeConfigInfo.transmissionMode;
      }
   }
   if(tipUeReCfg->bitMask & (1 << 8))
   {
      if(tipUeReCfg->cbSubsetRestrictionConfigInfo.cbSubsetRestrictionflag == TRUE)
      {
         ueReCfg->ueCodeBookRstRecfg.pres = tipUeReCfg->cbSubsetRestrictionConfigInfo.cbSubsetRestrictionflag;
         ueReCfg->ueCodeBookRstRecfg.pmiBitMap[0] = tipUeReCfg->cbSubsetRestrictionConfigInfo.cbBitmap[0];
         ueReCfg->ueCodeBookRstRecfg.pmiBitMap[1] = tipUeReCfg->cbSubsetRestrictionConfigInfo.cbBitmap[1];
      }
   }

   if(tipUeReCfg->bitMask & (1 << 9))
   {
      ueReCfg->ueCatEnum = tipUeReCfg->ueCategory;
   }

   if(tipUeReCfg->bitMask & (1 << 2))
   {
      ueReCfg->ueUlHqRecfg.maxUlHqTx = tipUeReCfg->ulHarqConfigInfo.maxUlHarqTransmissions;
   }

   if(tipUeReCfg->bitMask & (1 << 3))
   {
      ueReCfg->ueQosRecfg.ambrPres = tipUeReCfg->ueQosConfigInfo.ambrPresent;
      ueReCfg->ueQosRecfg.dlAmbr = tipUeReCfg->ueQosConfigInfo.dlAmbrValue;
      ueReCfg->ueQosRecfg.ueBr = tipUeReCfg->ueQosConfigInfo.ulByteRate;
   }

   if(tipUeReCfg->bitMask & (1 << 4))
   {
      ueReCfg->ueTaTmrRecfg.pres = tipUeReCfg->ueTaTimerConfigInfo.present;
         ueReCfg->ueTaTmrRecfg.taTmr = tipGetRsysTaVal(tipUeReCfg->ueTaTimerConfigInfo.taTimer);
   }

   if(tipUeReCfg->bitMask & (1 << 5))
   {
      ueReCfg->ueUlPwrRecfg.uePuschPwr.pres = tipUeReCfg->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.present;
      ueReCfg->ueUlPwrRecfg.uePuschPwr.idx = tipUeReCfg->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.index;
      ueReCfg->ueUlPwrRecfg.uePuschPwr.tpcRnti = tipUeReCfg->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo.tpcRnti;

      ueReCfg->ueUlPwrRecfg.uePucchPwr.pres = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.present;
      ueReCfg->ueUlPwrRecfg.uePucchPwr.idx = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.index;
      ueReCfg->ueUlPwrRecfg.uePucchPwr.tpcRnti = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.tpcRnti;
      ueReCfg->ueUlPwrRecfg.isAccumulated = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.accumulatedFlag;
      ueReCfg->ueUlPwrRecfg.isDeltaMCSEnabled = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.deltaMcsFlag;
      ueReCfg->ueUlPwrRecfg.p0UePusch = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.p0UePusch;
      ueReCfg->ueUlPwrRecfg.p0UePucch = tipUeReCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo.p0UePucch;
   }

   if(tipUeReCfg->bitMask & (1 << 6))
   {
      ueReCfg->ueMeasGapRecfg.isMesGapEnabled = tipUeReCfg->ueMeasurementGapConfigInfo.ueMeasurementGapFlag;
      ueReCfg->ueMeasGapRecfg.gapPrd = tipUeReCfg->ueMeasurementGapConfigInfo.gapPeriod;
      ueReCfg->ueMeasGapRecfg.gapOffst = tipUeReCfg->ueMeasurementGapConfigInfo.gapOffset;
   }

   if(tipUeReCfg->bitMask & (1 << 11))
   {
      ueReCfg->srsCfg.type = tipUeReCfg->srsUeConfigInfo.srsConfigFlag;
      ueReCfg->srsCfg.srsSetup.srsCfgIdx = tipUeReCfg->srsUeConfigInfo.srsConfigIndex;
      ueReCfg->srsCfg.srsSetup.srsBw = tipUeReCfg->srsUeConfigInfo.srsBandwidth;
      ueReCfg->srsCfg.srsSetup.srsHopBw = tipUeReCfg->srsUeConfigInfo.srsHoppingBandwidth;
      ueReCfg->srsCfg.srsSetup.cycShift = tipUeReCfg->srsUeConfigInfo.srsCyclicShift;
      ueReCfg->srsCfg.srsSetup.duration = tipUeReCfg->srsUeConfigInfo.duration;
      ueReCfg->srsCfg.srsSetup.txComb = tipUeReCfg->srsUeConfigInfo.transmissionComb;
      ueReCfg->srsCfg.srsSetup.fDomPosi = tipUeReCfg->srsUeConfigInfo.frequencyDomainPosition;
   }
   if(tipUeReCfg->bitMask & (1 << 13))
   {
      ueReCfg->ueDrxRecfg.isDrxEnabled = tipUeReCfg->ueDrxConfigInfo.drxEnabledFlag;
#ifdef LTEMAC_R9
      ueReCfg->ueDrxRecfg.cqiMask = tipUeReCfg->ueDrxConfigInfo.cqiMask;
#endif
      ueReCfg->ueDrxRecfg.drxInactvTmr = tipUeReCfg->ueDrxConfigInfo.drxInactivitytimer;
      ueReCfg->ueDrxRecfg.drxOnDurTmr = tipUeReCfg->ueDrxConfigInfo.drxOnDurationTimer;
      ueReCfg->ueDrxRecfg.drxRetxTmr = tipUeReCfg->ueDrxConfigInfo.drxRetransmissionTimer;
      ueReCfg->ueDrxRecfg.drxLongCycleOffst.longDrxCycle = tipUeReCfg->ueDrxConfigInfo.longDrxCycle;
      ueReCfg->ueDrxRecfg.drxLongCycleOffst.drxStartOffst = tipUeReCfg->ueDrxConfigInfo.longDrxCycleStartOffset;
      ueReCfg->ueDrxRecfg.drxShortDrx.pres = tipUeReCfg->ueDrxConfigInfo.shortDrxPresent;
      ueReCfg->ueDrxRecfg.drxShortDrx.shortDrxCycle = tipUeReCfg->ueDrxConfigInfo.shortDrxCycle;
      ueReCfg->ueDrxRecfg.drxShortDrx.drxShortCycleTmr = tipUeReCfg->ueDrxConfigInfo.shortDrxCycleTimer;
   }

   if(tipUeReCfg->bitMask & MAC_PDSCH_RECONFIGURATION)
   {
      ueReCfg->uePdschDedCfg.uepACfg.pAPrsnt = tipUeReCfg->uePdschConfigInfo.uePdschPAConfigFlag;
      ueReCfg->uePdschDedCfg.uepACfg.pA = tipUeReCfg->uePdschConfigInfo.pA;
   }

   if(tipUeReCfg->bitMask & MAC_PUSCH_RECONFIGURATION)
   {
      ueReCfg->puschDedCfg.pres = tipUeReCfg->uePuschConfigInfo.uePuschConfigSupport;
      ueReCfg->puschDedCfg.bACKIdx = tipUeReCfg->uePuschConfigInfo.harqBetaOffset;
      ueReCfg->puschDedCfg.bRIIdx = tipUeReCfg->uePuschConfigInfo.riBetaOffset;
      ueReCfg->puschDedCfg.bCQIIdx = tipUeReCfg->uePuschConfigInfo.cqiBetaOffset;
   }
   ueReCfg->isTtiBundlEnabled = tipUeReCfg->ttiBundlingEnable;

   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : tipUnpkCellCfg
*
*
*     Desc : unpack MAC Cell Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkCellCfg
(
MacCellConfigReq   *rcvCellCfg,
RgrCellCfg         *cellCfg
)
#else
PUBLIC S16 tipUnpkCellCfg(rcvCellCfg, cfgReqInfo)
MacCellConfigReq   *rcvCellCfg;
RgrCellCfg         *cellCfg;
#endif
{
   TRC3(tipUnpkCellCfg);

   cellCfg->isCpUlExtend  = rcvCellCfg->cyclicPrefix;
   cellCfg->isCpDlExtend = rcvCellCfg->cyclicPrefix;
   cellCfg->cellModSchm  = rcvCellCfg->enable64Qam;
   cellCfg->pMax  = rcvCellCfg->pMax;
   cellCfg->dlHqCfg.maxDlHqTx  = rcvCellCfg->harqConfigInfo.maxDlHarqTransmissions;
   cellCfg->dlHqCfg.maxMsg4HqTx  = rcvCellCfg->harqConfigInfo.maxMsg4HarqTransmissions;
   cellCfg->macRnti.startRnti  = rcvCellCfg->rntiConfigInfo.startRnti;
   cellCfg->macRnti.size  = (rcvCellCfg->rntiConfigInfo.endRnti - rcvCellCfg->rntiConfigInfo.startRnti); 
   cellCfg->cfiCfg.cfi  = rcvCellCfg->cfiValue;

   cellCfg->bwCfg.dlTotalBw  = rcvCellCfg->bwInfo.dlBandwidth;
   cellCfg->bwCfg.ulTotalBw  = rcvCellCfg->bwInfo.ulBandwidth;

   cellCfg->phichCfg.ngEnum  = rcvCellCfg->phichConfigInfo.phichResource;
   cellCfg->phichCfg.isDurExtend  = rcvCellCfg->phichConfigInfo.phichDuration;

   cellCfg->pucchCfg.resourceSize  = rcvCellCfg->pucchConfigInfo.resourceSize ;
   cellCfg->pucchCfg.n1PucchAn  = rcvCellCfg->pucchConfigInfo.n1PucchAckNack;
   cellCfg->pucchCfg.deltaShift  = rcvCellCfg->pucchConfigInfo.deltaShift;
   cellCfg->pucchCfg.cyclicShift  = rcvCellCfg->pucchConfigInfo.cyclicShift;

   cellCfg->srsCfg.isSrsCfgSetup  = rcvCellCfg->srsConfigInfo.cellSpecificSrsEnable;
   cellCfg->srsCfg.srsBwEnum  = rcvCellCfg->srsConfigInfo.srsBwConfigInfo;
   cellCfg->srsCfg.srsSubFrameCfg = rcvCellCfg->srsConfigInfo.srsSubframeConfiguration;

   cellCfg->rachCfg.raWinSize  = rcvCellCfg->rachConfigInfo.raWindowSize;
   cellCfg->rachCfg.maxMsg3Tx  = rcvCellCfg->rachConfigInfo.maxMsg3HarqTransmissions;
   cellCfg->rachCfg.numRaPreamble  = rcvCellCfg->rachConfigInfo.numberOfRAPreambles;
   cellCfg->rachCfg.sizeRaPreambleGrpA  = rcvCellCfg->rachConfigInfo.sizeOfRAPreambleinGroupA;
   cellCfg->rachCfg.msgSizeGrpA  = rcvCellCfg->rachConfigInfo.messageSizeGroupA;
   cellCfg->rachCfg.prachResource = rcvCellCfg->rachConfigInfo.prachFrequencyOffset;/*TODO manjappa*/
   cellCfg->rachCfg.contResTmr = rcvCellCfg->rachConfigInfo.contentionResolutionTimer;

   cellCfg->pwrCfg.p0NominalPusch  = rcvCellCfg->ulPowerControlConfigInfo.p0NominalPusch;
   cellCfg->pwrCfg.alpha = rcvCellCfg->ulPowerControlConfigInfo.alpha;
   cellCfg->pwrCfg.p0NominalPucch = rcvCellCfg->ulPowerControlConfigInfo.p0NominalPucch;
   cellCfg->pwrCfg.deltaPreambleMsg3 = rcvCellCfg->ulPowerControlConfigInfo.deltaPreambleMessage3;

   cellCfg->pwrCfg.pucchPwrFmt3.startTpcRnti = rcvCellCfg->ulPowerControlConfigInfo.format3PucchStartTpcRnti;
   cellCfg->pwrCfg.pucchPwrFmt3.size = (rcvCellCfg->ulPowerControlConfigInfo.format3PucchEndRnti -
                                        rcvCellCfg->ulPowerControlConfigInfo.format3PucchStartTpcRnti);

   cellCfg->pwrCfg.pucchPwrFmt3a.startTpcRnti = rcvCellCfg->ulPowerControlConfigInfo.format3APucchStartTpcRnti;
   cellCfg->pwrCfg.pucchPwrFmt3a.size = (rcvCellCfg->ulPowerControlConfigInfo.format3APucchEndRnti -
                                          rcvCellCfg->ulPowerControlConfigInfo.format3APucchStartTpcRnti);

   cellCfg->pwrCfg.puschPwrFmt3.startTpcRnti = rcvCellCfg->ulPowerControlConfigInfo.format3PuschStartTpcRnti;
   cellCfg->pwrCfg.puschPwrFmt3.size = (rcvCellCfg->ulPowerControlConfigInfo.format3PuschEndRnti -
                                        rcvCellCfg->ulPowerControlConfigInfo.format3PuschStartTpcRnti);

   cellCfg->pwrCfg.puschPwrFmt3a.startTpcRnti = rcvCellCfg->ulPowerControlConfigInfo.format3APuschStartTpcRnti;
   cellCfg->pwrCfg.puschPwrFmt3a.size  = (rcvCellCfg->ulPowerControlConfigInfo.format3APuschEndRnti -
                                          rcvCellCfg->ulPowerControlConfigInfo.format3APuschStartTpcRnti);

   cellCfg->puschCfg.numSubBands  = rcvCellCfg->puschConfigInfo.numberOfSubBands ;
   cellCfg->puschCfg.isIntraHop  = rcvCellCfg->puschConfigInfo.hoppingMode;
   cellCfg->puschCfg.hopOffst  = rcvCellCfg->puschConfigInfo.hopOffset;

   cellCfg->bcchTxPwrOffset = rcvCellCfg->dlPowerControlConfigInfo.pbchTransmissionPower;
   cellCfg->pcchTxPwrOffset =  rcvCellCfg->dlPowerControlConfigInfo.pbchTransmissionPower;
   cellCfg->phichTxPwrOffset = rcvCellCfg->dlPowerControlConfigInfo.phichPowerOffset;
   cellCfg->isDynCfiEnb = rcvCellCfg->dynamicCfiEnable;
   cellCfg->rrmTtiIndPrd = rcvCellCfg->l3SfPeriodicity;
#if 1
   /*TODO manjappa hardcoded values */
   cellCfg->maxUlBwPerUe  = rcvCellCfg->bwInfo.ulBandwidth;
   cellCfg->maxDlBwPerUe = rcvCellCfg->bwInfo.dlBandwidth;
#ifdef RGR_V1
   cellCfg->rarTxPwrOffset = 0; /*This parameter is not filled from app currently*/;
   cellCfg->maxMsg3PerUlSf = 0;
#endif
   cellCfg->maxUePerUlSf = rcvCellCfg->numOfUsersPerTTI.numberOfDlUsersPerTTI;/*currently value is read from wr_Cfg.txt file */
   cellCfg->maxUePerDlSf = rcvCellCfg->numOfUsersPerTTI.numberOfDlUsersPerTTI;/*wr_Cfg.txt paramer */
   cellCfg->maxCcchPerDlSf = 0;/*not configuresd*/
   cellCfg->maxDlRetxBw  = rcvCellCfg->bwInfo.dlBandwidth;
   cellCfg->maxDlUeNewTxPerTti = rcvCellCfg->numOfUsersPerTTI.numberOfDlUsersPerTTI;
   cellCfg->maxUlUeNewTxPerTti = rcvCellCfg->numOfUsersPerTTI.numberOfDlUsersPerTTI;
   cellCfg->dlfsSchdType  = rcvCellCfg->dlfsEnable;;
   cellCfg->trgUlCqi.trgCqi  = 11;
   cellCfg->dlCmnCodeRate.bcchPchRaCodeRate  = 0;
   cellCfg->dlCmnCodeRate.pdcchCodeRate  = 0;
   cellCfg->dlCmnCodeRate.ccchCqi  = 6;
   cellCfg->puschSubBand.subbandStart  = 1;
   cellCfg->puschSubBand.numSubbands  = 32;//rcvCellCfg->puschConfigInfo.numberOfSubBands;
   cellCfg->puschSubBand.size  = 3;
#if 0
   for(idx = 0; idx <RGR_MAX_SUBBANDS; idx++)
   {
      cellCfg->puschSubBand.dmrs[idx]  = ;
   }
#endif
   cellCfg->ulCmnCodeRate.ccchCqi  = 6;
   cellCfg->dlfsCfg.isDlFreqSel  = 0;
   cellCfg->dlfsCfg.thresholdCqi  = TRUE;
   cellCfg->pucchCfg.maxPucchRb = 10;/*TODO manjappa*/
   cellCfg->srsCfg.srsCfgPrdEnum  = 0;/*TODO manjappa*/
   cellCfg->rachCfg.preambleFormat  = 0x01;/*TODO manjappa*/
   cellCfg->rachCfg.raOccasion.size  = 0x01;
   cellCfg->rachCfg.raOccasion.sfnEnum  = RGR_SFN_ANY;
   cellCfg->rachCfg.raOccasion.subFrameNum[0]  = 0x01;
   cellCfg->siCfg.siWinSize  = 5;/*WR_SI_WINDOWLEN_5*/
   cellCfg->siCfg.retxCnt  = 1;
   cellCfg->siCfg.modPrd  = RGR_MOD_PERD_64;/*RGR_MOD_PERD_64*/
   cellCfg->macPreambleSet.pres  = TRUE;
   if(cellCfg->macPreambleSet.pres == TRUE)
   {
      cellCfg->macPreambleSet.start  = 47 ;
      cellCfg->macPreambleSet.size  = 4;
   }
   cellCfg->numCmnLcs  = RGR_MAX_CMN_LC_PER_CELL;/*WR_DFLT_NUM_CMN_LCS*/

   {
      cellCfg->cmnLcCfg[0].lcId = WR_BCCH_SIB1_ID;
      cellCfg->cmnLcCfg[0].lcType = CM_LTE_LCH_BCCH;
      cellCfg->cmnLcCfg[0].dir = RGR_DIR_TX;
      cellCfg->cmnLcCfg[0].dlTrchType = CM_LTE_TRCH_DL_SCH;
      cellCfg->cmnLcCfg[0].ulTrchType = WR_VAL_ZERO;
   }
   {
      cellCfg->cmnLcCfg[1].lcId = WR_PCCH_ID;
      cellCfg->cmnLcCfg[1].lcType = CM_LTE_LCH_PCCH;
      cellCfg->cmnLcCfg[1].dir = RGR_DIR_TX;
      cellCfg->cmnLcCfg[1].dlTrchType = WR_VAL_ZERO;
      cellCfg->cmnLcCfg[1].ulTrchType = WR_VAL_ZERO;
   }
   {
      cellCfg->cmnLcCfg[2].lcId = WR_BCCH_BCH_ID;
      cellCfg->cmnLcCfg[2].lcType = CM_LTE_LCH_BCCH;
      cellCfg->cmnLcCfg[2].dir = RGR_DIR_TX;
      cellCfg->cmnLcCfg[2].dlTrchType = CM_LTE_TRCH_BCH;
      cellCfg->cmnLcCfg[2].ulTrchType = WR_VAL_ZERO;
   }

   {
      cellCfg->cmnLcCfg[3].lcId = WR_CCCH_UL_ID;
      cellCfg->cmnLcCfg[3].lcType = CM_LTE_LCH_CCCH;
      cellCfg->cmnLcCfg[3].dir = RGR_DIR_RX;
      cellCfg->cmnLcCfg[3].dlTrchType = CM_LTE_TRCH_DL_SCH;
      cellCfg->cmnLcCfg[3].ulTrchType = CM_LTE_TRCH_UL_SCH;
   }

   {
      cellCfg->cmnLcCfg[4].lcId = WR_CCCH_DL_ID;
      cellCfg->cmnLcCfg[4].lcType = CM_LTE_LCH_CCCH;
      cellCfg->cmnLcCfg[4].dir = RGR_DIR_TX;
      cellCfg->cmnLcCfg[4].dlTrchType = CM_LTE_TRCH_DL_SCH;
      cellCfg->cmnLcCfg[4].ulTrchType = CM_LTE_TRCH_UL_SCH;
   }

   {
      cellCfg->cmnLcCfg[5].lcId = WR_BCCH_SIB_OTHERS_ID;
      cellCfg->cmnLcCfg[5].lcType = CM_LTE_LCH_BCCH;
      cellCfg->cmnLcCfg[5].dir = RGR_DIR_TX;
      cellCfg->cmnLcCfg[5].dlTrchType = CM_LTE_TRCH_DL_SCH;
      cellCfg->cmnLcCfg[5].ulTrchType = WR_VAL_ZERO;
   }

  /*parameter values are taken from wr_cfg.txt*/
   cellCfg->csgParamCfg.minDlResNonCsg = 0;
   cellCfg->csgParamCfg.minUlResNonCsg = 0;
   cellCfg->spsCfg.maxSpsDlBw = 10;
   cellCfg->spsCfg.maxSpsUePerDlSf = 1;
   cellCfg->spsCfg.maxSpsUePerUlSf = 1;
   cellCfg->rgrLteAdvCfg.pres = FALSE;
   cellCfg->t300TmrVal = 0x04;

#if 1 /*SI configuration will be received as part of broadcost cell command */
   cellCfg->siCfg.siPeriodicity[0]  = RGR_SI_PERD_16;
   cellCfg->siCfg.siPeriodicity[1]  = RGR_SI_PERD_32;
   cellCfg->siCfg.siPeriodicity[2]  = RGR_SI_PERD_64;
   cellCfg->siCfg.siPeriodicity[3]  = RGR_SI_PERD_512;
   cellCfg->siCfg.siPeriodicity[4]  = RGR_SI_PERD_256;
   cellCfg->siCfg.siPeriodicity[5]  = RGR_SI_PERD_128;
   cellCfg->siCfg.siPeriodicity[6]  = 0;
   cellCfg->siCfg.siPeriodicity[7]  = 0;
   cellCfg->siCfg.minPeriodicity  = 0;
   cellCfg->siCfg.numSi           = 6;
#endif
   cellCfg->isAutoCfgModeEnb = 0;
   cellCfg->msg4pAVal = RGRUE_DLPWRCNTRL_PA_DB_6;
   cellCfg->lteUCfg.isLaaCell = 0;
#endif

  RETVALUE(ROK);
}

/***********************************************************
*
*     Func : tipUnpkUeCfg
*
*
*     Desc : unpack MAC UE Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkUeCfg
(
MacUeConfigReq   *rcvUeCfg,
RgrUeCfg         *rgrUeCfg
)
#else
PUBLIC S16 tipUnpkUeCfg(rcvUeCfg, ueCfg)
MacUeConfigReq   *rcvUeCfg;
RgrUeCfg         *rgrUeCfg;
#endif
{

   AperiodicCqiConfig *aCqiCfg;
   PeriodicCqiConfig  *pCqiCfg;
   RgrUeDlPCqiSetup   *pcqiSetup;
   UePuschGroupPowerControlConfig *uePuschGrpPcInfo;
   UePucchGroupPowerControlConfig *uePucchGrpPcInfo;
   UeDrxConfiguration *ueDrxCfg;
   TRC3(tipUnpkUeCfg);

   rgrUeCfg->crnti = rcvUeCfg->ueInfo.cRnti;
   rgrUeCfg->txMode.pres = rcvUeCfg->transmissionModeConfigInfo.transmissionModePresent;
   rgrUeCfg->txMode.txModeEnum = rcvUeCfg->transmissionModeConfigInfo.transmissionMode;
   aCqiCfg = &rcvUeCfg->dlCqiConfigInfo.aperiodicCqiConfigInfo;
   rgrUeCfg->ueDlCqiCfg.aprdCqiCfg.pres = aCqiCfg->present;
   rgrUeCfg->ueDlCqiCfg.aprdCqiCfg.aprdModeEnum = aCqiCfg->aperiodicCqiMode; 
   pCqiCfg = &rcvUeCfg->dlCqiConfigInfo.periodicCqiConfigInfo;
   rgrUeCfg->ueDlCqiCfg.prdCqiCfg.type = pCqiCfg->present; 
   pcqiSetup = &rgrUeCfg->ueDlCqiCfg.prdCqiCfg.cqiSetup;
   pcqiSetup->cqiPResIdx = pCqiCfg->cqiPucchResourceIndex; 
   pcqiSetup->cqiPCfgIdx = pCqiCfg->cqiPmiConfigurationIndex; 
   pcqiSetup->k = pCqiCfg->k; 
   pcqiSetup->prdModeEnum = pCqiCfg->periodicCqiMode; 
   pcqiSetup->sANCQI = pCqiCfg->simultaneousAckNackAndCqi; 
   pcqiSetup->riEna = pCqiCfg->riEnableFlag; 
   pcqiSetup->riCfgIdx = pCqiCfg->riConfigIndex;
   if(pCqiCfg->periodicCqiMode == 0 || pCqiCfg->periodicCqiMode == 1)
   {
      pcqiSetup->cqiRepType = 1; /*WideBand CQI*/
   }
   else
   {
      pcqiSetup->cqiRepType = 2; /*SubBand CQI*/
   }
   rgrUeCfg->ueUlHqCfg.maxUlHqTx = rcvUeCfg->ulHarqConfigInfo.maxUlHarqTransmissions; 
   rgrUeCfg->ueUlHqCfg.deltaHqOffst = 0; /*Unset Parameter*/
   uePuschGrpPcInfo = 
     &rcvUeCfg->ueUlPowerControlConfigInfo.uePuschGroupPowerControlConfigInfo;
   uePucchGrpPcInfo = 
     &rcvUeCfg->ueUlPowerControlConfigInfo.uePucchGroupPowerControlConfigInfo;
   rgrUeCfg->ueUlPwrCfg.uePuschPwr.pres = uePuschGrpPcInfo->present; 
   rgrUeCfg->ueUlPwrCfg.uePuschPwr.idx = uePuschGrpPcInfo->index;  
   rgrUeCfg->ueUlPwrCfg.uePuschPwr.tpcRnti = uePuschGrpPcInfo->tpcRnti; 
   rgrUeCfg->ueUlPwrCfg.uePucchPwr.pres = uePucchGrpPcInfo->present; 
   rgrUeCfg->ueUlPwrCfg.uePucchPwr.idx = uePucchGrpPcInfo->index; 
   rgrUeCfg->ueUlPwrCfg.uePucchPwr.tpcRnti= uePucchGrpPcInfo->tpcRnti; 
   rgrUeCfg->ueUlPwrCfg.isAccumulated = uePucchGrpPcInfo->accumulatedFlag; 
   rgrUeCfg->ueUlPwrCfg.isDeltaMCSEnabled = uePucchGrpPcInfo->deltaMcsFlag; 
   rgrUeCfg->ueUlPwrCfg.p0UePusch = uePucchGrpPcInfo->p0UePusch; 
   rgrUeCfg->ueUlPwrCfg.p0UePucch = uePucchGrpPcInfo->p0UePucch; 
   rgrUeCfg->ueQosCfg.ambrPres = rcvUeCfg->ueQosConfigInfo.ambrPresent; 
   rgrUeCfg->ueQosCfg.dlAmbr = rcvUeCfg->ueQosConfigInfo.dlAmbrValue; 
   rgrUeCfg->ueQosCfg.ueBr = rcvUeCfg->ueQosConfigInfo.ulByteRate; 
   rgrUeCfg->ueTaTmrCfg.pres = rcvUeCfg->ueTaTimerConfigInfo.present; 
   rgrUeCfg->ueTaTmrCfg.taTmr = tipGetRsysTaVal(rcvUeCfg->ueTaTimerConfigInfo.taTimer); 
   if(rgrUeCfg->ueTaTmrCfg.taTmr == 0)
   {
      rgrUeCfg->ueTaTmrCfg.pres = FALSE; 
      /*as we are filling pres falg as TRUE in UE Config need to check 
       * if its configured as infinet need to disable pres falg*/
   }

   ueDrxCfg = &rcvUeCfg->ueDrxConfigInfo;
   rgrUeCfg->ueDrxCfg.isDrxEnabled = ueDrxCfg->drxEnabledFlag;
#if 0
   if (ueDrxCfg->cqiMask == RGR_DRX_SETUP) //TODO - LTEMAC_R9 is not enabled 
   rgrUeCfg->ueDrxCfg.cqiMask.pres = TRUE;
   rgrUeCfg->ueDrxCfg.cqiMask.val = 0;
#endif
   rgrUeCfg->ueDrxCfg.drxInactvTmr = ueDrxCfg->drxInactivitytimer; 
   rgrUeCfg->ueDrxCfg.drxOnDurTmr = ueDrxCfg->drxOnDurationTimer; 
   rgrUeCfg->ueDrxCfg.drxRetxTmr = ueDrxCfg->drxRetransmissionTimer; 
   rgrUeCfg->ueDrxCfg.drxLongCycleOffst.longDrxCycle = ueDrxCfg->longDrxCycle; 
   rgrUeCfg->ueDrxCfg.drxLongCycleOffst.drxStartOffst = ueDrxCfg->longDrxCycleStartOffset;  
   rgrUeCfg->ueDrxCfg.drxShortDrx.pres = ueDrxCfg->shortDrxPresent; 
   rgrUeCfg->ueDrxCfg.drxShortDrx.shortDrxCycle = ueDrxCfg->shortDrxCycle; 
   rgrUeCfg->ueDrxCfg.drxShortDrx.drxShortCycleTmr= ueDrxCfg->shortDrxCycleTimer; 
   rgrUeCfg->ueBsrTmrCfg.isPrdBsrTmrPres = TRUE;
   rgrUeCfg->ueBsrTmrCfg.prdBsrTmr = 5; /*Proprietary*/
   rgrUeCfg->ueBsrTmrCfg.retxBsrTmr = 320; /*Proprietary */
   rgrUeCfg->ueCatEnum = rcvUeCfg->ueCategory;
   rgrUeCfg->isTtiBundlEnabled = rcvUeCfg->ttiBundlingEnable;
   rgrUeCfg->ueAckNackCfg.isAckNackEnabled = FALSE;
   rgrUeCfg->ueAckNackCfg.pucchAckNackRep = 10;
   rgrUeCfg->ueAckNackCfg.ackNackRepFactor = 2;
   rgrUeCfg->ueCapCfg.pwrClass = 0;
   rgrUeCfg->ueCapCfg.intraSfFeqHop = FALSE;
   rgrUeCfg->ueCapCfg.resAloocType1 = FALSE;
   rgrUeCfg->ueCapCfg.simCqiAckNack = FALSE;
   rgrUeCfg->ueCapCfg.txAntSel = 0; 
   rgrUeCfg->ueMesGapCfg.isMesGapEnabled =
   rcvUeCfg->ueMeasurementGapConfigInfo.ueMeasurementGapFlag;
   rgrUeCfg->ueMesGapCfg.gapPrd =
   rcvUeCfg->ueMeasurementGapConfigInfo.gapPeriod;
   rgrUeCfg->ueMesGapCfg.gapOffst = 
   rcvUeCfg->ueMeasurementGapConfigInfo.gapOffset;
   rgrUeCfg->ueCodeBookRstCfg.pres =
   rcvUeCfg->cbSubsetRestrictionConfigInfo.cbSubsetRestrictionflag;
   rgrUeCfg->ueCodeBookRstCfg.pmiBitMap[0] =
   rcvUeCfg->cbSubsetRestrictionConfigInfo.cbBitmap[0];
   rgrUeCfg->ueCodeBookRstCfg.pmiBitMap[1] =
   rcvUeCfg->cbSubsetRestrictionConfigInfo.cbBitmap[1];
   rgrUeCfg->dedPreambleId.pres = NOTPRSNT;
   /*Memsetting to zero for unused parameters*/
   cmMemset((U8*)&(rgrUeCfg->ueSpsCfg), 0, sizeof(RgrUeSpsCfg));
   cmMemset((U8*)&(rgrUeCfg->ulTxAntSel), 0, sizeof(RgrUeTxAntSelCfg));
   cmMemset((U8*)&(rgrUeCfg->ueCqiReptCfg), 0, sizeof(RgrUeCqiReptCfg));
   cmMemset((U8*)&(rgrUeCfg->ueLteAdvCfg), 0, sizeof(RgrLteAdvancedUeConfig));
   //rgrUeCfg->isHdFddEnbld = 0;
   rgrUeCfg->csgMmbrSta = 0;
   rgrUeCfg->srsCfg.type = rcvUeCfg->srsUeConfigInfo.srsConfigFlag; 
   rgrUeCfg->srsCfg.srsSetup.srsCfgIdx= rcvUeCfg->srsUeConfigInfo.srsConfigIndex; 
   rgrUeCfg->srsCfg.srsSetup.srsBw = rcvUeCfg->srsUeConfigInfo.srsBandwidth; 
   rgrUeCfg->srsCfg.srsSetup.srsHopBw = rcvUeCfg->srsUeConfigInfo.srsHoppingBandwidth;
   rgrUeCfg->srsCfg.srsSetup.cycShift = rcvUeCfg->srsUeConfigInfo.srsCyclicShift;
   rgrUeCfg->srsCfg.srsSetup.duration = rcvUeCfg->srsUeConfigInfo.duration; 
   rgrUeCfg->srsCfg.srsSetup.txComb = rcvUeCfg->srsUeConfigInfo.transmissionComb;
   rgrUeCfg->srsCfg.srsSetup.fDomPosi = rcvUeCfg->srsUeConfigInfo.frequencyDomainPosition; 
   rgrUeCfg->srCfg.type = rcvUeCfg->srConfigInfo.srConfigFlag; 
   rgrUeCfg->srCfg.srSetup.srCfgIdx = rcvUeCfg->srConfigInfo.srConfigIndex; 
   rgrUeCfg->srCfg.srSetup.srResIdx = rcvUeCfg->srConfigInfo.srResourceIndex; 
   rgrUeCfg->puschDedCfg.pres = rcvUeCfg->uePuschConfigInfo.uePuschConfigSupport; 
   rgrUeCfg->puschDedCfg.bACKIdx = rcvUeCfg->uePuschConfigInfo.harqBetaOffset; 
   rgrUeCfg->puschDedCfg.bRIIdx = rcvUeCfg->uePuschConfigInfo.riBetaOffset; 
   rgrUeCfg->puschDedCfg.bCQIIdx = rcvUeCfg->uePuschConfigInfo.cqiBetaOffset; 
   rgrUeCfg->uePdschDedCfg.uepACfg.pAPrsnt = rcvUeCfg->uePdschConfigInfo.uePdschPAConfigFlag; 
   rgrUeCfg->uePdschDedCfg.uepACfg.pA = rcvUeCfg->uePdschConfigInfo.pA;
   rgrUeCfg->accessStratumRls = rcvUeCfg->ueRel; 
  RETVALUE(ROK);
}

#ifdef TIP_LOWER_L2
/**
* @brief Send UE release request to L3.
*
* @details
*
*     Function: tipSendUeRlsInd
*
*  @param[in]   RgSchUeCb    *ueCb
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendUeRlsInd
(
U16        ueId,
U16        cellId,
U32        cause
)
#else
PUBLIC S16 tipSendUeRlsInd(ueId, cellId, event)
U16        ueId;
U16        cellId;
U32        cause;
#endif
{
   Pst             nPst;
   TipPacket       *packet;
   U8              sendBuf[MAX_BUFF_LEN_L2_L3];
   L2UeRelInd      *rlfInd;
   U8              inst = 0;

   TRC3(tipSendUeRlsInd)

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;

   rlfInd = (L2UeRelInd *)((U8*)sendBuf + TIP_HDR_LEN);
   inst = 0; /* In CA codebase sch instance 0 is for primary cell and 1 is for secondary cell */
   tipLL2GetUeIndex(cellId, inst, ueId, &(rlfInd->ueInfo.ueIndex));
   rlfInd->ueInfo.cRnti = ueId;
   rlfInd->cause = cause;

   /* nPst is used to fill src modId and dst modId in TIP interface */
   if(cause == L2_UEREL_CAUSE_ULSYNC_LOSS)
   {
      nPst.srcEnt = ENTRG;
   }
   else
   {
      nPst.srcEnt = ENTKW;
   }
   nPst.dstEnt = ENTNH;
   tipFillHdr(&nPst, cellId, L2_UERELEASE_IND, 0, (sizeof(L2UeRelInd) + TIP_HDR_LEN), packet);

   //RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
   RETVALUE(ROK);
}
#endif

/**
* @brief Send TTI Indication from MAC/SCH to APP.
*
* @details
*
*     Function: tipSendMacAppTtiInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgrTtiIndInfo *ttiInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendMacAppTtiInd
(
Pst* pst,
SuId suId,
RgrTtiIndInfo *ttiInd
)
#else
PUBLIC S16 tipSendMacAppTtiInd(pst, suId, transId, status)
Pst* pst;
SuId suId;
RgrTtiIndInfo *ttiInd;
#endif
{
   TipPacket *packet;
   U8 sendBuf[MAX_BUFF_LEN_L2_L3];
   L3TtiInd *l3TtiInd;
   U16 msgLen;
   U32 cellId,msgId;

   TRC3(tipSendMacAppTtiInd);

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;

   cellId = ttiInd->cellId;
   msgId = L3_TTI_IND;
   msgLen = sizeof(L3TtiInd);

   l3TtiInd = (L3TtiInd*)((U8*)sendBuf + TIP_HDR_LEN);
   l3TtiInd->timingInfo.sfn = ttiInd->sfn;
   l3TtiInd->timingInfo.sf = 0; /* MAC->APP API doesn't have SF as of now*/

   tipFillHdr(pst, cellId, msgId, 0, (msgLen + TIP_HDR_LEN), packet);
   SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(RgrTtiIndInfo));
   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

/**
* @brief Configuration Confirm from MAC/SCH to APP.
*
* @details
*
*     Function: tipSendMacCfgRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   U8  status
*  @param[in]   U8  action
*  @param[in]   U8  cfgType
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendMacCfgRsp
(
Pst* pst,
SuId suId,
RgrCfgTransId transId,
U8 status,
U8 action,
U8 cfgType
)
#else
PUBLIC S16 tipSendMacCfgRsp(pst, suId, transId, status, U8 action, U8 cfgType)
Pst* pst;
SuId suId;
RgrCfgTransId transId;
U8 status;
U8 action;
U8 cfgType;
#endif
{
   TipPacket     *packet;
   U8            sendBuf[MAX_BUFF_LEN_L2_L3];
   U16           msgLen = 0;
   U32           cellId,msgId = 0;
   U64           key = 0;
   TipLL2RgDat   *cfg;


   TRC3(tipSendMacCfgRsp)

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;
   
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
   TipFindLL2Trans(key, &cfg);

   if(NULLP == cfg)
   {
      RETVALUE(ROK);
   }

   TipDelLL2Trans(cfg);

   switch (action)
   {
      case RGR_CONFIG:
      {
         switch (cfgType)
         {
            case RGR_CELL_CFG:
            {
               msgId = MAC_CELLCONFIG_RSP;
               msgLen = sizeof(MacCellConfigRsp);
               MacCellConfigRsp *cellCfgCfm;

               cellCfgCfm = (MacCellConfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);
               cellCfgCfm->status = status;
            }
            break;
            case RGR_UE_CFG:
            {
               if(RGR_CFG_CFM_OK == status)
               {
                  cfg->isSchUeCfgSuccess = TRUE;
               }
               else
               {
                  cfg->isSchUeCfgSuccess = FALSE;
               }
               TipAddLL2Trans(cfg);
               RETVALUE(ROK);
            }
            break;
            case RGR_LCH_CFG:
            {
               if(0 == cfg->recvdRgrCfgCfm)
               {
                  cfg->isSchLcCfgSuccess = TRUE; /* initializing to success only
                                               for the first time */
               }
               if(RGR_CFG_CFM_NOK == status)
               {
                  printf("SCH UE LCH Config failed[NumCfg: %d,NumFail: %d]\n",
                        cfg->expctdNumLcCfm, cfg->recvdNumLcCfm);
                  cfg->isSchUeCfgSuccess = FALSE;
               }
               cfg->recvdRgrCfgCfm++;
               if(cfg->exptdRgrCfgCfm == cfg->recvdRgrCfgCfm)
               {
                  msgId = MAC_UECONFIG_RSP;
                  msgLen = sizeof(MacUeConfigRsp);
                  MacUeConfigRsp  *ueCfgRsp;
                  ueCfgRsp = (MacUeConfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);

                  ueCfgRsp->ueInfo.ueIndex = cfg->ueId.ueIndex;
                  ueCfgRsp->ueInfo.cRnti = cfg->ueId.cRnti;

                  if(cfg->isSchUeCfgSuccess && cfg->isSchLcCfgSuccess &&
                        cfg->isMacUeCfgSuccess && cfg->isMacLchCfgSuccess && 
                        cfg->isPhyUeCfgDone)
                  {
                     ueCfgRsp->status = 0;
                  }
                  else
                  {
                     ueCfgRsp->status = 1;
                  }
               }
               else
               {
                 TipAddLL2Trans(cfg);
                 RETVALUE(ROK);
               }
            }
            break;   
            case RGR_LCG_CFG:
            {
               cfg->ll2RcvLchIdCnt++;
               cfg->recvdRgrCfgCfm++;
#if 0
               if(cfg->exptdRgrCfgCfm == cfg->recvdRgrCfgCfm)
               {
                  msgId = MAC_UERECONFIG_RSP;
                  msgLen = sizeof(MacUeReconfigRsp);
                  MacUeReconfigRsp    *ueRecfgRsp;
                  ueRecfgRsp = (MacUeReconfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);

                  ueRecfgRsp->ueInfo.ueIndex = cfg->ueId.ueIndex;
                  ueRecfgRsp->ueInfo.cRnti = cfg->ueId.cRnti;

                  if(cfg->isMacUeReCfgSuccess && cfg->isPhyUeReCfgDone)
                  {
                     ueRecfgRsp->status = 0;
                  }
                  else
                  {
                     ueRecfgRsp->status = 1;
                  }
               }
               else
#endif
               {
                 TipAddLL2Trans(cfg);
                 RETVALUE(ROK);
               }

            }
            break;  
            default:
            {
               printf("Config: CfgType should not reach here %d\n",cfgType); 
               TipAddLL2Trans(cfg);
               RETVALUE(ROK);
            }
         }
      }
      break;
      case RGR_RECONFIG:
      {
         switch (cfgType)
         {
            case RGR_CELL_CFG:
            {
            }
            break;
            case RGR_UE_CFG:
            {
               msgId = MAC_UERECONFIG_RSP;
               msgLen = sizeof(MacUeReconfigRsp);
               MacUeReconfigRsp    *ueRecfgRsp;
               ueRecfgRsp = (MacUeReconfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);
               
               ueRecfgRsp->ueInfo.ueIndex = cfg->ueId.ueIndex;
               ueRecfgRsp->ueInfo.cRnti = cfg->ueId.cRnti;

               if(cfg->isMacUeReCfgSuccess && cfg->isPhyUeReCfgDone)
               {
                  ueRecfgRsp->status = 0;
               }
               else
               {
                  ueRecfgRsp->status = 1;
               }
            }
            break;   
            case RGR_LCH_CFG:
            {
               MacUeReconfigRsp    *ueRecfgRsp; 

               cfg->ll2RcvLchIdCnt++;                             
               cfg->recvdRgrCfgCfm++;                             
               printf(" LC exptdRgrCfgCfm %d ll2RcvLchIdCnt %d\n", cfg->exptdRgrCfgCfm, cfg->ll2RcvLchIdCnt);
               ueRecfgRsp = (MacUeReconfigRsp*)((U8*)cfg->ueRecfgsendBuf + TIP_HDR_LEN);
               if(status == RGR_CFG_CFM_NOK) 
               { 
                  ueRecfgRsp->lc[ueRecfgRsp->numberOfFailedLcs].lcConfigType = 1; 
                  ueRecfgRsp->lc[ueRecfgRsp->numberOfFailedLcs].lchId = cfg->ll2LchId[cfg->ll2RcvLchIdCnt-1];//LL2 
                  ueRecfgRsp->numberOfFailedLcs++; 
               } 
               if(cfg->exptdRgrCfgCfm != cfg->ll2RcvLchIdCnt)
               {
                  TipAddLL2Trans(cfg);
                  RETVALUE(ROK);
               }
            }
            break;   
            case RGR_LCG_CFG:
            {
               MacUeReconfigRsp    *ueRecfgRsp; 

               cfg->ll2RcvLchIdCnt++;                             
               cfg->recvdRgrCfgCfm++;
               printf(" LCG exptdRgrCfgCfm %d ll2RcvLchIdCnt %d\n", cfg->exptdRgrCfgCfm, cfg->ll2RcvLchIdCnt);
               ueRecfgRsp = (MacUeReconfigRsp*)((U8*)cfg->ueRecfgsendBuf + TIP_HDR_LEN);
               if(status == RGR_CFG_CFM_NOK) 
               { 
                  ueRecfgRsp->lc[ueRecfgRsp->numberOfFailedLcs].lcConfigType = 1; 
                  ueRecfgRsp->lc[ueRecfgRsp->numberOfFailedLcs].lchId = cfg->ll2LchId[cfg->ll2RcvLchIdCnt-1];//LL2 
                  ueRecfgRsp->numberOfFailedLcs++; 
               }
               if(cfg->exptdRgrCfgCfm != cfg->ll2RcvLchIdCnt)
               {
                  TipAddLL2Trans(cfg);
                  RETVALUE(ROK);
               }
            }
            break;   
            default:
            printf("Reconfig: CfgType should not reach here \n"); 
         }
      }
      break;
      case RGR_DELETE:
      {
         switch (cfgType)
         {
            case RGR_CELL_CFG:
            {
            }
            break;
            case RGR_UE_CFG:
            {
               msgId = MAC_UEDELETE_RSP;
               msgLen = sizeof(MacUeDeleteRsp);
               MacUeDeleteRsp    *ueDeleteRsp;
               ueDeleteRsp = (MacUeDeleteRsp*)((U8*)sendBuf + TIP_HDR_LEN);

               ueDeleteRsp->ueInfo.ueIndex = cfg->ueId.ueIndex;
               ueDeleteRsp->ueInfo.cRnti = cfg->ueId.cRnti;

               if(cfg->isMacUeDeleteSuccess && cfg->isPhyUeDeleteDone)
               {
                  ueDeleteRsp->status = 0;
               }
               else
               {
                  ueDeleteRsp->status = 1;
               }

            }
            break;   
            case RGR_LCH_CFG:
            {
            }
            break;   
            case RGR_LCG_CFG:
            {
            }
            break;   
            default:
            printf("Delete: CfgType should not reach here \n"); 
         }
      }
      break;
      case RGR_RESET:
      {
         TipAddLL2Trans(cfg);
         RETVALUE(ROK);
      }
      break;
      default:
         printf("Action should not reach here: %d \n", action); 
   }
   tipFillHdr(pst, cellId, msgId, cfg->upperLyrTrans, (msgLen + TIP_HDR_LEN), packet);
   SPutSBuf(0, 0, (Data *)cfg, sizeof(TipLL2RgDat));
   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

#ifdef ANSI
PRIVATE S16 tipStoreSiMsg
(
RgrSiCfgReqInfo *siCfgReq,
TipSiInfo       *macSiInfo
)
#else
PRIVATE S16 tipStoreSiMsg(siCfgReq, macSiInfo)
RgrSiCfgReqInfo *siCfgReq;
TipSiInfo       *macSiInfo;
#endif
{
   MsgLen bufLen;
   MsgLen msgLen;
   S16 ret1;

   /* update this param only for the first time a PDU is written to MAC
    * Broadcast Info. Need this to address SI modification scenario */
   MacBroadcastMsgReq  temp;
   U16 idxToUseForFirstCfg = TIP_HDR_LEN + sizeof(MacBroadcastMsgReq) -
      sizeof(temp.mibPdu) - sizeof(temp.sib1Pdu) - sizeof(temp.siConfigInfo);

   switch(siCfgReq->cfgType)
   {
      case RGR_SI_CFG_TYPE_MIB:
      {
         U8                  *mibPdu;

         SFndLenMsg(siCfgReq->pdu, &bufLen);
         macSiInfo->macBrdcstInfo->mibPduLen = bufLen;
         macSiInfo->nextIdxToUse = idxToUseForFirstCfg;
         mibPdu  = (U8*)(macSiInfo->macBrdcstPdu +  macSiInfo->nextIdxToUse);

         ret1 = SCpyMsgFix(siCfgReq->pdu, 0, bufLen, mibPdu, &msgLen);
         if((-1 == ret1) || (bufLen != msgLen))
         {
            printf("\n%s: failed to convert to char buffer\n", __func__);
            RETVALUE(ret1);
         }

         macSiInfo->nextIdxToUse +=  bufLen;
         macSiInfo->macBrdcstInfo->siCfgBitMask = MAC_MIB_PDU;
      }
      break;

      case RGR_SI_CFG_TYPE_SIB1:
      {
         U8 *sib1Pdu;
         SFndLenMsg(siCfgReq->pdu, &bufLen);
         macSiInfo->macBrdcstInfo->sib1PduLen = bufLen;

         if(!macSiInfo->nextIdxToUse)
            macSiInfo->nextIdxToUse = idxToUseForFirstCfg;

         sib1Pdu = (U8*)(macSiInfo->macBrdcstPdu +  macSiInfo->nextIdxToUse);
         ret1 = SCpyMsgFix(siCfgReq->pdu, 0, bufLen, sib1Pdu, &msgLen);
         if((-1 == ret1) || (bufLen != msgLen))
         {
            printf("\n%s: failed to convert to mBuf\n", __func__);
         }

         macSiInfo->nextIdxToUse += bufLen;
         macSiInfo->macBrdcstInfo->siCfgBitMask |= MAC_SIB1_PDU;
      }
      break;

      case RGR_SI_CFG_TYPE_SI:
      {
         SiPduInfo *siPduList;
         /* pointer to the index will be changing for every SI config */
         /* since complete SI config is received per SI config req, storing
          * address per SI is not needed will work */
         SiConfiguration *siCfg = (SiConfiguration*)(U8*)(macSiInfo->macBrdcstPdu +
               macSiInfo->nextIdxToUse);
         siCfg->siId = siCfgReq->siId;
         siCfg->numSegments = TIP_DEFAULT_SI_SEGMENTS;
         siCfg->siPeriodicity = 
            macSiInfo->siCfgInfo.siPeriodicity[siCfgReq->siId-1];

         macSiInfo->nextIdxToUse += sizeof(SiConfiguration) - sizeof(siCfg->siPduList);

         siPduList = (SiPduInfo*)(U8*)(macSiInfo->macBrdcstPdu + 
               macSiInfo->nextIdxToUse);
         SFndLenMsg(siCfgReq->pdu, &bufLen);
         siPduList->pduLength = bufLen;
         ret1 = SCpyMsgFix(siCfgReq->pdu, 0, bufLen,
                                          siPduList->siPdu, &msgLen);
         if((-1 == ret1) || (bufLen != msgLen))
         {
            printf("\n%s: failed to convert to mBuf\n", __func__);
         }
         macSiInfo->macBrdcstInfo->numSiPdus +=1;
         macSiInfo->nextIdxToUse += bufLen + sizeof(SiPduInfo) - sizeof(siPduList->siPdu);
         macSiInfo->macBrdcstInfo->siCfgBitMask |= MAC_SI_PDU;
      }
      break;

      default:
         break;
   }
   (Void)SPutMsg((siCfgReq->pdu));
   siCfgReq->pdu = NULL;
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : tipSendMacCellStartReq
*
*
*     Desc : Configuration Request from RRM to MAC for 
*            configuring Cell
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendMacCellStartReq
(
Pst* pst,
U16  cellId
)
#else
PUBLIC S16 tipSendMacCellStartReq(pst, cellId)
Pst* pst;
U16  cellId;
#endif
{
   U8                 sendBuf[MAX_BUFF_LEN_L2_L3];
   TipPacket          *hdr = NULLP;

   TRC3(tipSendMacCellStartReq);
   memset(sendBuf,0,MAX_BUFF_LEN_L2_L3);
   hdr = (TipPacket*)sendBuf;
   tipFillHdr(pst, cellId, MAC_CELLSTART_IND, 0,TIP_HDR_LEN, hdr);

   TIP_EVENT_LOG(cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
         TIP_MSG_MAC_CELLSTART_IND, 0);
   RETVALUE(tipSendToCLL2(TIP_HDR_LEN, (U8*)&sendBuf));
}/*end of tipSendMacCellStartReq */
/***********************************************************
*
*     Func : tipSendSiCfgReq
*
*
*     Desc : SI Configuration Request from RRM to MAC for 
*            configuring SI
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrSiCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 tipSendSiCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrSiCfgReqInfo * cfgReqInfo;
#endif
{
   TipPacket *hdr = NULLP;
   U32 msgId = MAC_BROADCASTMSG_REQ;
   U8 sendPacket = FALSE;
   TipCellTransInfo *tipCellInfo;

   TRC3(tipSendSiCfgReq);

   TIP_GET_CELL_INFO(cfgReqInfo->cellId, tipCellInfo);
   if(NULLP == tipCellInfo)
   {
      RLOG_ARG0(L_FATAL, DBG_CELLID, cfgReqInfo->cellId,
            "Cell Info not found. Do CellConfig first");
      RETVALUE(RFAILED);
   }

   if(tipCellInfo->siInfo.isFirstCfgDone == FALSE)
   {
      tipCellInfo->siInfo.macBrdcstInfo = 
         (MacBroadcastMsgReq*)(tipCellInfo->siInfo.macBrdcstPdu + TIP_HDR_LEN);
      /* update common broadcast config info */
      tipCellInfo->siInfo.macBrdcstInfo->siWindowLen =
         tipCellInfo->siInfo.siCfgInfo.siWinSize;
      tipCellInfo->siInfo.macBrdcstInfo->modfnPeriod =
         tipCellInfo->siInfo.siCfgInfo.modPrd;
      tipCellInfo->siInfo.macBrdcstInfo->siBrdcstChngTim = SI_CHANGE_NORMAL;
      tipCellInfo->siInfo.macBrdcstInfo->siRetxCnt = SI_CHANGE_NORMAL;

      /* store the SI PDU */
      tipStoreSiMsg(cfgReqInfo, &tipCellInfo->siInfo);
      tipCellInfo->siInfo.isFirstCfgDone = TRUE;
   }
   else if(tipCellInfo->siInfo.numSiCfgRecv == tipCellInfo->siInfo.siCfgInfo.numSi)
   {
      hdr = (TipPacket*)tipCellInfo->siInfo.macBrdcstPdu;

      tipStoreSiMsg(cfgReqInfo, &tipCellInfo->siInfo);
      tipFillHdr(pst, cfgReqInfo->cellId, msgId, 0, 
            tipCellInfo->siInfo.nextIdxToUse, hdr);;
 
      deriveTipTransId(transId.trans, hdr);
      sendPacket = TRUE;
   }
   else
   {
      /* store the SI PDU */
      tipStoreSiMsg(cfgReqInfo, &tipCellInfo->siInfo);
   }
   tipCellInfo->siInfo.numSiCfgRecv++;

   if (SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
               sizeof(RgrSiCfgReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }

   /* send the PDU only when all the SI's are collated */
   if(sendPacket)
   {
      TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
            TIP_MSG_MAC_BROADCASTMSG_REQ, hdr->transId);
      RETVALUE(tipSendToCLL2(tipCellInfo->siInfo.nextIdxToUse, tipCellInfo->siInfo.macBrdcstPdu));
   }

   RETVALUE(ROK);
}

/**
* @brief Configuration Confirm from PHY to RRC.
*
* @details
*
*     Function: tipSendMacSiCfgRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendMacSiCfgRsp
(
Pst* pst,
SuId suId,
RgrCfgTransId transId,
U8 status
)
#else
PUBLIC S16 tipSendMacSiCfgRsp(pst, suId, transId, status)
Pst* pst;
SuId suId;
RgrCfgTransId transId;
U8 status;
#endif
{
   TipPacket *packet;
   U8 sendBuf[MAX_BUFF_LEN_L2_L3];
   MacCellConfigRsp *siCfgCfm;
   U32 msgId, cellId;
   U16 msgLen;

   TRC3(tipSendMacSiCfgRsp);
   if(sendOneStatus != 0)
      RETVALUE(ROK);
   sendOneStatus = 1;
   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;

   cellId = 1;
   msgId = MAC_BROADCASTMSG_RSP;
   msgLen = sizeof(MacCellConfigRsp);

   siCfgCfm = (MacCellConfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);
   siCfgCfm->status = status;

   tipFillHdr(pst, cellId, msgId, 0, (msgLen + TIP_HDR_LEN), packet);
   deriveTipTransId(transId.trans, packet);
   TIP_EVENT_LOG(packet->cellId, 0, TIP_MOD_MAC, TIP_MOD_RRC,
         TIP_MSG_MAC_BROADCASTMSG_RSP, packet->transId);
   RETVALUE(tipSendToL3(packet->pktLen,(U8 *) &sendBuf));
} /*endif of tipSendMacSiCfgRsp*/

/**
* @brief Get SI config and fill PDU
*
* @details
*
*     Function: tipGetSiCfgReqInf
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipGetSiCfgReqInf 
(
 Pst              *pst,
 RgrSiCfgReqInfo  **siCfgReqInfo,
 U8               *pdu,
 MsgLen           pduLen
)
{
   if ((SGetSBuf(pst->region, pst->pool, (Data **)siCfgReqInfo,
            sizeof(RgrSiCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR052, (ErrVal)0, "Memory Allocation failed");
#endif
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)*siCfgReqInfo, 0, sizeof(RgrSiCfgReqInfo));

   if (SGetMsg(pst->region, pst->pool, &(*siCfgReqInfo)->pdu) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR045, (ErrVal)0, "Memory Allocation failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)siCfgReqInfo, 
            sizeof(RgrSiCfgReqInfo));
      RETVALUE(RFAILED);
   }
   if(SAddPstMsgMult(pdu, (MsgLen)pduLen, (*siCfgReqInfo)->pdu) != ROK)
   {
      printf("failed to  pack cellCfg\n");
      RETVALUE(RFAILED);
   }
#ifdef TIP_DBG
   printMsg(pduLen, pdu);
#endif
 RETVALUE(ROK);
}/*end of tipGetSiCfgReqInf*/


/**
* @brief unpack all L2-Mac massages received from L3
*
* @details
*
*     Function: tipSendCrgCfgCfm 
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendCrgCfgCfm(CrgCfgTransId transId, U8 status)
#else
PUBLIC S16 tipSendCrgCfgCfm(transId, status)
CrgCfgTransId transId;
U8   status;
#endif
{
   S16         ret = ROK;
   U64         key = 0;
   TipLL2RgDat *cfg;

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

   TipFindLL2Trans(key, &cfg);

   if(NULLP == cfg)
   {
      RETVALUE(ROK);
   }

   TipDelLL2Trans(cfg);

   switch(transId.trans[0])
   {
      case CRG_CONFIG:
      {
         switch (transId.trans[1])
         {
            case CRG_CELL_CFG:
               cfg->isMacCellCfgSuccess = TRUE;
               if(status == CRG_CFG_CFM_NOK)
               {
                  printf("MAC Cell Config failed\n");
                  cfg->isMacCellCfgSuccess = FALSE;
               }
               break;
            case CRG_UE_CFG:
               cfg->isMacUeCfgSuccess = TRUE;
               if(status == CRG_CFG_CFM_NOK)
               {
                  printf("MAC UE Config failed\n");
                  cfg->isMacUeCfgSuccess = FALSE;
               }
               break;
            case CRG_LCH_CFG:
               if(0 == cfg->recvdNumLcCfm)
               {
                  cfg->isMacLchCfgSuccess = TRUE; /* initializing to success only
                                                for the first time */
               }
               if(status == CRG_CFG_CFM_NOK)
               {
                  printf("MAC UE LCH Config failed[NumCfg: %d,NumFail: %d]\n",
                        cfg->expctdNumLcCfm, cfg->recvdNumLcCfm);
                  cfg->isMacLchCfgSuccess = FALSE;
               }
               cfg->recvdNumLcCfm++;
               break;
         }
      }
      break;
      case CRG_RECONFIG:
      {
         switch (transId.trans[1])
         {
               case CRG_UE_CFG:
               cfg->isMacUeReCfgSuccess = TRUE;
               if(status == CRG_CFG_CFM_NOK)
               {
                  printf("MAC UE Re Config failed\n");
                  cfg->isMacUeReCfgSuccess = FALSE;
               }
               break;
         }
      }
         break;
      case CRG_RESET:
         break;
      case CRG_DELETE:
      {
         switch (transId.trans[1])
         {
            case CRG_UE_CFG:
               cfg->isMacUeDeleteSuccess = TRUE;
               if(status == CRG_CFG_CFM_NOK)
               {
                  printf("MAC UE Delete failed\n");
                  cfg->isMacUeDeleteSuccess = FALSE;
               }
               break;
            default:
               printf("type not handled yet\n");
         }

      }
         break;
   }
   TipAddLL2Trans(cfg);
   RETVALUE(ret);
}

/**
* @brief unpack all L2-Mac massages received from L3
*
* @details
*
*     Function: tipUnpkMacMsg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendCrgCfgReq(TipPacket   *hdr, Pst *nPst, U64 tipTransId)
#else
PUBLIC S16 tipSendCrgCfgReq(hdr, nPst, tipTransId)
TipPacket   *hdr;
Pst         *nPst;
U64         tipTransId;
#endif
{
   S16             ret = ROK;
   Pst             *pst; 
   SpId            spId = 0;
   CrgCfgTransId   transId;
   CrgCfgReqInfo   *cfgReqInfo;
   U8              idx;
   
   if(SGetSBuf(nPst->region, nPst->pool, (Data **)&pst, sizeof(Pst)) != ROK)
   {
      RETVALUE(RFAILED);
   } 

   TIP_CREATE_MAC_PST(pst);

   cfgReqInfo = NULLP;
   if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
            sizeof(CrgCfgReqInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   
   switch( hdr->msgId )
   {
      case MAC_CELLCONFIG_REQ : 
         {   
            MacCellConfigReq *rcvCellCfg = (MacCellConfigReq*)&hdr->message; 
            transId.trans[0] = 1;
            transId.trans[1] = 0;
            transId.trans[2] = (tipTransId) >> 40; 
            transId.trans[3] = (tipTransId) >> 32;
            transId.trans[4] = (tipTransId) >> 24; 
            transId.trans[5] = (tipTransId) >> 16;
            transId.trans[6] = (tipTransId) >> 8;
            transId.trans[7] = (tipTransId) & 0x0ffff;

            /* Cell Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_CELL_CFG; 
            cfgReqInfo->u.cfgInfo.u.cellCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.cellCfg.rachCfg.maxMsg3Tx = rcvCellCfg->rachConfigInfo.maxMsg3HarqTransmissions;
            cfgReqInfo->u.cfgInfo.u.cellCfg.bwCfg.dlTotalBw = rcvCellCfg->bwInfo.dlBandwidth;
            cfgReqInfo->u.cfgInfo.u.cellCfg.bwCfg.ulTotalBw = rcvCellCfg->bwInfo.ulBandwidth;


            transId.trans[8] = 2;
            transId.trans[9] = 1;
            transId.trans[10] = 0;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            cfgReqInfo = NULLP;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK)
            {
               RETVALUE(RFAILED);
            }

            /* LCH Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = 0; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = WR_BCCH_SIB1_ID;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_BCCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dir = RGR_DIR_TX;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType = CM_LTE_TRCH_DL_SCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType = WR_VAL_ZERO;

            transId.trans[8] = 1;
            transId.trans[9] = 1;
            transId.trans[10] = 2;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            cfgReqInfo = NULLP;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK)
            {
               RETVALUE(RFAILED);
            }

            /* LCH Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = 0; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = WR_PCCH_ID;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_PCCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dir = RGR_DIR_TX;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType = CM_LTE_TRCH_PCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType = WR_VAL_ZERO;

            transId.trans[8] = 1;
            transId.trans[9] = 1;
            transId.trans[10] = 6;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            cfgReqInfo = NULLP;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK)
            {
               RETVALUE(RFAILED);
            }

            /* LCH Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = 0; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = WR_BCCH_BCH_ID;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_BCCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dir = RGR_DIR_TX;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType = CM_LTE_TRCH_BCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType = WR_VAL_ZERO;

            transId.trans[8] = 1;
            transId.trans[9] = 1;
            transId.trans[10] = 1;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            cfgReqInfo = NULLP;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK)
            {
               RETVALUE(RFAILED);
            }

            /* LCH Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = 0;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = WR_CCCH_UL_ID;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_CCCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dir = RGR_DIR_RX;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType = WR_VAL_ZERO;
            cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType = CM_LTE_TRCH_UL_SCH;

            transId.trans[8] = 1;
            transId.trans[9] = 1;
            transId.trans[10] = 5;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            cfgReqInfo = NULLP;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK)
            {
               RETVALUE(RFAILED);
            }

            /* LCH Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = 0;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = WR_CCCH_DL_ID;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_CCCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dir = RGR_DIR_TX;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType = CM_LTE_TRCH_DL_SCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType =  WR_VAL_ZERO;

            transId.trans[8] = 1;
            transId.trans[9] = 1;
            transId.trans[10] = 4;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            cfgReqInfo = NULLP;
            if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK)
            {
               RETVALUE(RFAILED);
            }

            /* LCH Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = 0; 
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = WR_BCCH_SIB_OTHERS_ID;
            cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_BCCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dir = RGR_DIR_TX;
            cfgReqInfo->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType = CM_LTE_TRCH_DL_SCH;
            cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType =  WR_VAL_ZERO;

            transId.trans[8] = 1;
            transId.trans[9] = 1;
            transId.trans[10] = 3;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);
         }
         break;
      case MAC_UECONFIG_REQ:
         {
            MacUeConfigReq *ueCfg = (MacUeConfigReq*)&hdr->message;
            TipLL2RgDat    *cfg;
            U64            key;

            deriveLL2TransId((U8 *)&transId, tipTransId, CRG_CONFIG, CRG_UE_CFG,
                  CRG_CFG_TRANSID_SIZE);

            /* UE Config */
            cfgReqInfo->action = CRG_CONFIG;
            cfgReqInfo->u.cfgInfo.cfgType = CRG_UE_CFG; 
            cfgReqInfo->u.cfgInfo.u.ueCfg.cellId = hdr->cellId;
            cfgReqInfo->u.cfgInfo.u.ueCfg.crnti = ueCfg->ueInfo.cRnti;

            cfgReqInfo->u.cfgInfo.u.ueCfg.ueUlHqCfg.maxUlHqTx = ueCfg->ulHarqConfigInfo.maxUlHarqTransmissions;
            cfgReqInfo->u.cfgInfo.u.ueCfg.txMode.pres = ueCfg->transmissionModeConfigInfo.transmissionModePresent;
            cfgReqInfo->u.cfgInfo.u.ueCfg.txMode.tm = ueCfg->transmissionModeConfigInfo.transmissionMode;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            /* LCH Config */
            deriveLL2TransId((U8 *)&transId, tipTransId, CRG_CONFIG, CRG_LCH_CFG,
                  CRG_CFG_TRANSID_SIZE);
            LcConfigInfo *lcInfo;// = ueCfg->lcInfo;
            key = tipTransId;
            TipFindLL2Trans(key, &cfg);

            if(NULLP == cfg)
            {
               RETVALUE(ROK);
            }

            TipDelLL2Trans(cfg);

            cfg->expctdNumLcCfm = ueCfg->numberOfLcs;
            TipAddLL2Trans(cfg);
            for(idx = 0; idx < ueCfg->numberOfLcs; idx++)
            {
               cfgReqInfo = NULLP;
               lcInfo = (LcConfigInfo *)&ueCfg->lcInfo[idx];
               if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
                        sizeof(CrgCfgReqInfo)) != ROK)
               {
                  printf("\nMemory Alloc failed for MAC LC config.\n"
                        "Number of LCs already cofigured = %d out of %d\n", idx,
                        ueCfg->numberOfLcs);
                  RETVALUE(RFAILED);
               }
               cfgReqInfo->action = CRG_CONFIG;
               cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
               cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
               cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = ueCfg->ueInfo.cRnti;
               cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = lcInfo->lchId;
               /* SRBs */
               if(lcInfo->lchId <= 2)
               {
                  cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_DCCH;
               }
               else /* DRBs */
               {
                  cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_DTCH;
               }
               cfgReqInfo->u.cfgInfo.u.lchCfg.dir = lcInfo->dirInfo;
#ifdef LTE_L2_MEAS
               cfgReqInfo->u.cfgInfo.u.lchCfg.qci = lcInfo->qosConfigInfo.qci;
#endif
               /* irrespective of direction, only UL info is needed at 
                * CRG configration. */
               cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.lcgId = lcInfo->ulLcInfo.lcgId;
               cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.lcgId = lcInfo->ulLcInfo.lcgId;

               /* CRG interface only piggy backs the TRANSID, hence not changing it for 
                * LCH CFG */
               ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);
            }
         }
         break;
      case MAC_UERECONFIG_REQ :
         {
            MacUeReconfigReq  *ueReCfg = (MacUeReconfigReq*)&hdr->message; 
            deriveLL2TransId((U8 *)&transId, tipTransId, CRG_RESET, CRG_UE_CFG,
                  CRG_CFG_TRANSID_SIZE);

            if(ueReCfg->oldCRnti != ueReCfg->newCRnti)
            {
               CrgCfgReqInfo   *cfgReqResetInfo;
               if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqResetInfo,
                        sizeof(CrgCfgReqInfo)) != ROK)
               {
                  printf("\nMemory Alloc failed for MAC LC config.\n"
                        "Number of LCs already cofigured = %d out of %d\n", idx,
                        ueReCfg->numberOfLcs);
                  RETVALUE(RFAILED);
               }
               cfgReqResetInfo->action = CRG_RESET;
               RgUiCrgCfgReq(pst, spId, transId, cfgReqResetInfo);
            }

            deriveLL2TransId((U8 *)&transId, tipTransId, CRG_RECONFIG, CRG_UE_CFG,
                  CRG_CFG_TRANSID_SIZE);
            /* UE ReConfig */
            cfgReqInfo->action = CRG_RECONFIG;
            cfgReqInfo->u.recfgInfo.recfgType = CRG_UE_CFG; 
            cfgReqInfo->u.recfgInfo.u.ueRecfg.cellId = hdr->cellId;
            /* UE ID change for MAC will be controlled by SCH */
            cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti = ueReCfg->oldCRnti;
            cfgReqInfo->u.recfgInfo.u.ueRecfg.newCrnti = ueReCfg->oldCRnti;

            //cfgReqInfo->u.recfgInfo.u.ueRecfg.newCrnti = ueReCfg->newCRnti;
            cfgReqInfo->u.recfgInfo.u.ueRecfg.ueUlHqRecfg.maxUlHqTx = ueReCfg->ulHarqConfigInfo.maxUlHarqTransmissions;
            if ( ueReCfg->transmissionModeConfigInfo.transmissionModePresent  == TRUE)
            {
               cfgReqInfo->u.recfgInfo.u.ueRecfg.txMode.pres = ueReCfg->transmissionModeConfigInfo.transmissionModePresent;
               cfgReqInfo->u.recfgInfo.u.ueRecfg.txMode.tm = ueReCfg->transmissionModeConfigInfo.transmissionMode;
            }
            else
            {
               cfgReqInfo->u.recfgInfo.u.ueRecfg.txMode.pres = FALSE;
            }

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);

            /* LCH Config */
            deriveLL2TransId((U8 *)&transId, tipTransId, CRG_CONFIG, CRG_LCH_CFG,
                  CRG_CFG_TRANSID_SIZE);
            LcConfigInfo *lcInfo;// = ueReCfg->lcInfo[0];

         /*   key = tipTransId;
            TipFindLL2Trans(key, &cfg);
            TipDelLL2Trans(cfg);
            cfg->expctdNumLcCfm = ueCfg->numberOfLcs;
                 printf("manjappa : 8 key %x\n", cfg->key);
            TipAddLL2Trans(cfg);*/


            for(idx = 0; idx < ueReCfg->numberOfLcs; idx++)
            {
               lcInfo = (LcConfigInfo *)&(ueReCfg->LcInfo[idx]);
               cfgReqInfo = NULLP;
               if(SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
                        sizeof(CrgCfgReqInfo)) != ROK)
               {
                  printf("\nMemory Alloc failed for MAC LC config.\n"
                        "Number of LCs already cofigured = %d out of %d\n", idx,
                        ueReCfg->numberOfLcs);
                  RETVALUE(RFAILED);
               }
               cfgReqInfo->action = CRG_CONFIG;
               cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
               cfgReqInfo->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
               cfgReqInfo->u.cfgInfo.u.lchCfg.crnti = ueReCfg->oldCRnti;
               cfgReqInfo->u.cfgInfo.u.lchCfg.lcId = lcInfo->lchId;
               /* SRBs */
               if(lcInfo->lchId <= 2)
               {
                  cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_DCCH;
               }
               else /* DRBs */
               {
                  cfgReqInfo->u.cfgInfo.u.lchCfg.lcType = CM_LTE_LCH_DTCH;
               }
               cfgReqInfo->u.cfgInfo.u.lchCfg.dir = lcInfo->dirInfo;
#ifdef LTE_L2_MEAS
               cfgReqInfo->u.cfgInfo.u.lchCfg.qci = lcInfo->qosConfigInfo.qci;
#endif
               /* irrespective of direction, only UL info is needed at 
                * CRG configration. */
               cfgReqInfo->u.cfgInfo.u.lchCfg.ulInfo.lcgId = lcInfo->ulLcInfo.lcgId;

               /* CRG interface only piggy backs the TRANSID, hence not changing it for 
                * LCH CFG */
               ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);
            }
         }
         break;
      case MAC_UEDELETE_REQ:
         {
            MacUeDeleteReq  *ueDelReq = (MacUeDeleteReq*)&hdr->message; 
            deriveLL2TransId((U8 *)&transId, tipTransId, CRG_DELETE, CRG_UE_CFG,
                  CRG_CFG_TRANSID_SIZE);

            /* UE Delete */
            cfgReqInfo->action = CRG_DELETE;
            cfgReqInfo->u.delInfo.delType = CRG_UE_CFG; 
            cfgReqInfo->u.delInfo.u.ueDel.cellId = hdr->cellId;
            cfgReqInfo->u.delInfo.u.ueDel.crnti = ueDelReq->ueInfo.cRnti;

            ret = RgUiCrgCfgReq(pst, spId, transId, cfgReqInfo);
         } 
         break;
      default:
         /* Free allocated memory */
         SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
               sizeof(CrgCfgReqInfo));

         SPutSBuf (nPst->region, nPst->pool, (Data *)pst, sizeof(Pst));
         printf("Invalid message %d is received at CRG !! ", hdr->msgId);
         RETVALUE(RFAILED); 
         break;
   }
   SPutSBuf (nPst->region, nPst->pool, (Data *)pst, sizeof(Pst));
   RETVALUE(ret);
}


/**
* @brief unpack all L2-Mac massages received from L3
*
* @details
*
*     Function: tipUnpkAppMacMsg 
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkAppMacMsg
(
Pst*    pst,
Buffer* mBuf
)
{
  U8               rcvBuf[MAX_BUFF_LEN_L2_L3];
  TipPacket        *hdr = NULLP;
  RgrCfgReqInfo    *cfgReqInfo;
  RgrCfgTransId    transId;
  U32              spId = 0;
  U64              tipTransId = 0;
  MsgLen           bufLen;
  S16              ret, ret1;
  MsgLen            msgLen;
  TipLL2RgDat      *cfg;
   
  ret = SFndLenMsg(mBuf, &bufLen); 
  ret1 = SCpyMsgFix(mBuf, 0, bufLen, rcvBuf, &msgLen);
   
  if(ROK != SGetSBuf(pst->region, pst->pool, (Data **)&cfg, sizeof(TipLL2RgDat)))
  {
     printf("Failed while memory allocation \n\n");
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
  }
  cmMemset((U8 *)cfg, 0, sizeof(TipLL2RgDat));

  hdr = (TipPacket*)&rcvBuf;
  if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
              sizeof(RgrCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
     SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
           __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
           (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
  }
  cmMemset((U8 *)cfgReqInfo, 0, sizeof(RgrCfgReqInfo));
 
  switch(hdr->msgId)
  {
     case MAC_CELLCONFIG_REQ:
     {
        cfg->key = tipPrepareLL2Key(hdr);
        cfg->upperLyrTrans = hdr->transId;
        tipTransId = cfg->key; 
        TipAddLL2Trans(cfg);
        
        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
              TIP_MSG_MAC_CELLCONFIG_REQ, hdr->transId);

        /* Sending Mac Config before Sch */
        ret = tipSendCrgCfgReq(hdr, pst, tipTransId);

        /* send SCH ENB CFG */
        RgrSchedEnbCfg *enbCfg = &cfgReqInfo->u.cfgInfo.u.schedEnbCfg;
        MacCellConfigReq *macCellCfg = (MacCellConfigReq*)&hdr->message;
        cfgReqInfo->action = RGR_CONFIG;
        cfgReqInfo->u.cfgInfo.cfgType = RGR_ENB_CFG;
        cfgReqInfo->u.cfgInfo.u.cellCfg.cellId = hdr->cellId;
        cfgReqInfo->u.cfgInfo.u.cellCfg.macInst = 0;
        enbCfg->numTxAntPorts = macCellCfg->numOfTxAntennas;
        enbCfg->dlSchdType = macCellCfg->schedulerSpecificConfigInfo.dlSchedulingType;
        enbCfg->dlSchInfo.dlPfs.tptCoeffi = 0;
        enbCfg->dlSchInfo.dlPfs.fairCoeffi = 0;
        cmMemcpy((U8*)&enbCfg->dlSchInfo.dlPfs.qciWgt, 
              (U8*)&pfsQciWgt, RGR_MAX_NUM_QCI);
        enbCfg->ulSchdType = macCellCfg->schedulerSpecificConfigInfo.ulSchedulingType;
        enbCfg->ulSchInfo.ulPfs.tptCoeffi = 0;
        enbCfg->ulSchInfo.ulPfs.fairCoeffi = 0;
        cmMemcpy((U8*)&enbCfg->ulSchInfo.ulPfs.qciWgt, 
              (U8*)&pfsQciWgt, RGR_MAX_NUM_QCI);
        enbCfg->accsMode = RGR_CELL_ACCS_OPEN;
        deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_ENB_CFG,
              RGR_CFG_TRANSID_SIZE);
        RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo);

        /* Send SCH Cell CFG */
        RgrCellCfg         *cellCfg;
        if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
                    sizeof(RgrCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
           SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
           SPutMsg(mBuf);
           RETVALUE(RFAILED);
        }
        cmMemset((U8 *)cfgReqInfo, 0, sizeof(RgrCfgReqInfo));
        cfgReqInfo->action = RGR_CONFIG;
        cfgReqInfo->u.cfgInfo.cfgType = RGR_CELL_CFG; 
        cellCfg = &cfgReqInfo->u.cfgInfo.u.cellCfg;
        cfgReqInfo->u.cfgInfo.u.cellCfg.cellId = hdr->cellId;
        cfgReqInfo->u.cfgInfo.u.cellCfg.macInst = 0;
        tipUnpkCellCfg((MacCellConfigReq*)&hdr->message, &cfgReqInfo->u.cfgInfo.u.cellCfg);
        deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_CELL_CFG, RGR_CFG_TRANSID_SIZE);
        RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo);
     }
     break;
     case MAC_CELLRECONFIG_REQ:
     {
        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
              TIP_MSG_MAC_CELLRECONFIG_REQ, hdr->transId);
     }
     break;
     case MAC_CELLDELETE_REQ:
     {
        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
              TIP_MSG_MAC_CELLDELETE_REQ, hdr->transId);
     }
     break;
     case MAC_BROADCASTMSG_REQ:
     {
        MacBroadcastMsgReq *macBrdcstReq;
        RgrSiCfgReqInfo    *siCfgReqInfo;
        U16                 nxtIndx = 0;
        U16                 idx = 0;

        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
              TIP_MSG_MAC_BROADCASTMSG_REQ, hdr->transId);

        /* reset response handler */
        sendOneStatus = 0;

        cfg->key = tipPrepareLL2Key(hdr);
        cfg->upperLyrTrans = hdr->transId;
        macBrdcstReq = (MacBroadcastMsgReq*)hdr->message;
        nxtIndx += TIP_HDR_LEN;
        nxtIndx += sizeof(MacBroadcastMsgReq) - sizeof(macBrdcstReq->mibPdu)- \
                   sizeof(macBrdcstReq->sib1Pdu) - sizeof(macBrdcstReq->siConfigInfo);
        /* MIB processing start */
        if((macBrdcstReq->siCfgBitMask & MAC_MIB_PDU) &&
              (macBrdcstReq->mibPduLen > 0))
        {
           if(nxtIndx > MAX_BUFF_LEN_L2_L3)
           {
              printf("index greater than max buffer size\n");
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
           ret = tipGetSiCfgReqInf(pst, (RgrSiCfgReqInfo **)&siCfgReqInfo, (U8*)(rcvBuf + nxtIndx), macBrdcstReq->mibPduLen);
           if(ret != ROK)
           {
              printf("failed to  process MIB Message \n");
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
           nxtIndx += macBrdcstReq->mibPduLen;

           siCfgReqInfo->cellId = hdr->cellId;
           siCfgReqInfo->cfgType = RGR_SI_CFG_TYPE_MIB;
           tipTransId = cfg->key; 
           deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_SI_CFG_TYPE_MIB, RGR_CFG_TRANSID_SIZE);
           RgUiRgrSiCfgReq(pst, spId, transId, siCfgReqInfo);
        }
        else
        {
           RLOG_ARG0(L_DEBUG, DBG_CELLID, hdr->cellId, "MIB PDU not received");
        }
        /* MIB processing end */

        /* SIB1 processing start */
        if((macBrdcstReq->siCfgBitMask & MAC_SIB1_PDU) &&
              (macBrdcstReq->sib1PduLen > 0))
        {
           if(nxtIndx > MAX_BUFF_LEN_L2_L3)
           {
              printf("index greater than max buffer size\n");
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
           ret = tipGetSiCfgReqInf(pst, (RgrSiCfgReqInfo **)&siCfgReqInfo,(U8*)(rcvBuf + nxtIndx), macBrdcstReq->sib1PduLen);
           if(ret != ROK)
           {
              printf("failed to  process MIB Message \n");
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
           nxtIndx += macBrdcstReq->sib1PduLen;

           siCfgReqInfo->cellId = hdr->cellId;
           siCfgReqInfo->cfgType = RGR_SI_CFG_TYPE_SIB1;
           deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_SI_CFG_TYPE_SIB1, RGR_CFG_TRANSID_SIZE);
           RgUiRgrSiCfgReq(pst, spId, transId, siCfgReqInfo);
        }
        else
        {
           RLOG_ARG0(L_DEBUG, DBG_CELLID, hdr->cellId, "SIB PDU not received");
        }
        /* SIB1 processing end */

        /* SI Message processing start */
        if(macBrdcstReq->siCfgBitMask & MAC_SI_PDU)
        {
           SiConfiguration  *siConfigInfo;
           SiPduInfo        *siPduList;     /*!< List of segments for the SI */
           for(idx = 0; idx < macBrdcstReq->numSiPdus; idx++) 
           {
              if(nxtIndx >= MAX_BUFF_LEN_L2_L3)
              {
                 printf("index greater than max buffer size\n");
                 SPutMsg(mBuf);
                 RETVALUE(RFAILED);
              }
              siConfigInfo = (SiConfiguration*)(rcvBuf + nxtIndx);
              siPduList = &siConfigInfo->siPduList[0];
              ret = tipGetSiCfgReqInf(pst, (RgrSiCfgReqInfo **)&siCfgReqInfo, siPduList->siPdu, siPduList->pduLength);
              if(ret != ROK)
              {
                 printf("failed to  process MIB Message \n");
                 SPutMsg(mBuf);
                 RETVALUE(RFAILED);
              }
              siCfgReqInfo->cellId = hdr->cellId;
              siCfgReqInfo->cfgType = RGR_SI_CFG_TYPE_SI;
              siCfgReqInfo->siId = siConfigInfo->siId;
              deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_SI_CFG_TYPE_SI, RGR_CFG_TRANSID_SIZE);
              RgUiRgrSiCfgReq(pst, spId, transId, siCfgReqInfo);
              nxtIndx += sizeof(SiConfiguration) + siPduList->pduLength - sizeof(siPduList->siPdu);  
           }
        }
        /* SI Message processing end */
     }
     break;
     case MAC_UECONFIG_REQ:
     {
        U8               idx;
        RgrUeCfg         *ueCfg;
        RgrLchCfg        *lchCfg;
        MacUeConfigReq   *tipMacUeCfg = (MacUeConfigReq*)&hdr->message;

        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
              TIP_MSG_MAC_UECONFIG_REQ, hdr->transId);

        cfg->key = tipPrepareLL2Key(hdr);
        cfg->upperLyrTrans = hdr->transId;
        cfg->exptdRgrCfgCfm = tipMacUeCfg->numberOfLcs;
        cfgReqInfo->action = RGR_CONFIG;
        cfgReqInfo->u.cfgInfo.cfgType = RGR_UE_CFG; 
        ueCfg = &cfgReqInfo->u.cfgInfo.u.ueCfg;
        cfgReqInfo->u.cfgInfo.u.ueCfg.cellId = hdr->cellId;
        tipUnpkUeCfg((MacUeConfigReq*)&hdr->message, &cfgReqInfo->u.cfgInfo.u.ueCfg);
        tipTransId = cfg->key;

        deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_UE_CFG, RGR_CFG_TRANSID_SIZE);
        cfg->ueId.ueIndex = tipMacUeCfg->ueInfo.ueIndex;
        cfg->ueId.cRnti = tipMacUeCfg->ueInfo.cRnti;

        TipAddLL2Trans(cfg);
        /* Sending MAC Config before SCH */
        ret = tipSendCrgCfgReq(hdr, pst, tipTransId);
        /* Sending PHY config Req */
        ret = tipSendCtfUeCfgReq(hdr, pst);
        /* Sending SCH Config Req */
        RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo);
        /* send RGR LC CFG */
        /* same transId for all LC CFGs */
        deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_LCH_CFG,
              RGR_CFG_TRANSID_SIZE);
        for(idx = 0; idx < tipMacUeCfg->numberOfLcs; idx++)
        {
           cfgReqInfo = NULLP;
           if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
                       sizeof(RgrCfgReqInfo))) != ROK)
           {
              printf("\nMemory Alloc failed for RGR LC config.\n"
                    "Number of LCs already cofigured = %d out of %d\n", idx,
                    tipMacUeCfg->numberOfLcs);
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
           cmMemset((U8 *)cfgReqInfo, 0, sizeof(RgrCfgReqInfo));
           cfgReqInfo->action = CRG_CONFIG;
           cfgReqInfo->u.cfgInfo.cfgType = CRG_LCH_CFG; 
           lchCfg         = &cfgReqInfo->u.cfgInfo.u.lchCfg;
           lchCfg->cellId = hdr->cellId;
           lchCfg->crnti  = tipMacUeCfg->ueInfo.cRnti;
           lchCfg->lcId   = tipMacUeCfg->lcInfo[idx].lchId;
           if(lchCfg->lcId > 2)
           {
              lchCfg->lcType = CM_LTE_LCH_DTCH;
           }
           else
           {
              lchCfg->lcType = CM_LTE_LCH_DCCH;
           }
           lchCfg->dlInfo.dlTrchType = CM_LTE_TRCH_DL_SCH;
           lchCfg->dlInfo.dlQos.qci = tipMacUeCfg->lcInfo[idx].qosConfigInfo.qci;

           lchCfg->dlInfo.dlQos.gbr = tipMacUeCfg->lcInfo[idx].qosConfigInfo.gbrQosConfigInfo.erabGuaranteedBitRateDl;
           lchCfg->dlInfo.dlQos.mbr = tipMacUeCfg->lcInfo[idx].qosConfigInfo.gbrQosConfigInfo.erabMaxBitRateDl;
           lchCfg->lcgId            = tipMacUeCfg->lcInfo[idx].ulLcInfo.lcgId;

           lchCfg->ulLchQciInfo.lcId = tipMacUeCfg->lcInfo[idx].lchId;
           lchCfg->ulLchQciInfo.qci = tipMacUeCfg->lcInfo[idx].qosConfigInfo.qci;
           lchCfg->ulLchQciInfo.lcgId = tipMacUeCfg->lcInfo[idx].ulLcInfo.lcgId;
           RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo);
        }
     }
     break;
     case MAC_UERECONFIG_REQ:
     {
        RgrCfgReqInfo      *cfgLchReqInfo[12];
        U8                 lchCnt = 0;
        U8                 idx = 0;
        U8                 idx1 = 0;
#ifdef TIP_LOWER_L2
        U8                 inst;
#endif
        MacUeReconfigReq   *tipUeReCfg = (MacUeReconfigReq*)&hdr->message;
        LcConfigInfo       *tipLchCfg = (LcConfigInfo*)&tipUeReCfg->LcInfo;

        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_RRC, TIP_MOD_MAC,
              TIP_MSG_MAC_UECONFIG_REQ, hdr->transId);

        cfg->key = tipPrepareLL2Key(hdr); 
        cfg->upperLyrTrans = hdr->transId;
        cfg->ueId.ueIndex = tipUeReCfg->ueIndex;
        cfg->ueId.cRnti = tipUeReCfg->newCRnti;
        cfgReqInfo->action = RGR_RECONFIG;
        cfgReqInfo->u.recfgInfo.recfgType = RGR_UE_CFG;
        cfgReqInfo->u.recfgInfo.u.ueRecfg.cellId = hdr->cellId;
        /* no spl handling UE ID change. SCH automatically detects the old and
         * new crnti change. */
        cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti = tipUeReCfg->oldCRnti;
        cfgReqInfo->u.recfgInfo.u.ueRecfg.newCrnti = tipUeReCfg->newCRnti;
        tipUnpkUeReCfg((MacUeReconfigReq*)&hdr->message,
              &cfgReqInfo->u.recfgInfo.u.ueRecfg);
        tipTransId = cfg->key; 
#ifdef TIP_LOWER_L2
        inst = 0; /* In CA codebase sch instance 0 is for primary cell and
                     1 is for secondary cell */
        tipLL2SaveUeIndex(hdr->cellId, inst, tipUeReCfg->newCRnti,
              tipUeReCfg->ueIndex);
#endif
        TipAddLL2Trans(cfg);

        /* Sending MAC Config before Sch */
        /* Send UE Reconfig to CRG */
        ret = tipSendCrgCfgReq(hdr, pst, tipTransId); 

        /* Send UE Reconfig to CTF */
        ret = tipSendCtfUeCfgReq(hdr, pst);

        /* send SCH reset before UE ID change is detected */
        if(((MacUeReconfigReq*)&hdr->message)->bitMask &
              MAC_UEIDCHANGE_RECONFIGURATION)
        {
           RgrCfgReqInfo    *cfgReqInfo1;
           //RgrCfgTransId    transId1;
           if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo1,
                       sizeof(RgrCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                    (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
           cmMemset((U8 *)cfgReqInfo1, 0, sizeof(RgrCfgReqInfo));
           cfgReqInfo1->action = RGR_RESET;
           cfgReqInfo1->u.rstInfo.cellId = hdr->cellId;
           cfgReqInfo1->u.rstInfo.crnti  = tipUeReCfg->oldCRnti;
           deriveLL2TransId((U8 *)&transId, tipTransId, RGR_RESET,
                 RGR_UE_CFG, RGR_CFG_TRANSID_SIZE);
           RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo1);
        }

        /* Sending UE Reconfig before LC/LCG config */
        deriveLL2TransId((U8 *)&transId, tipTransId, RGR_RECONFIG,
              RGR_UE_CFG, RGR_CFG_TRANSID_SIZE);
        RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo);
        
        lchCnt = tipUeReCfg->numberOfLcs;
        cfg->exptdRgrCfgCfm = tipUeReCfg->numberOfLcs * 2;
        for(; idx < lchCnt; idx++)
        {
           if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgLchReqInfo[idx],
                       sizeof(RgrCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
           }
           cmMemset((U8 *)cfgLchReqInfo[idx], 0, sizeof(RgrCfgReqInfo));

          /*Send LCH config */
           cfgLchReqInfo[idx]->action = RGR_CONFIG;
           cfgLchReqInfo[idx]->u.cfgInfo.cfgType = RGR_LCH_CFG;
           cfgLchReqInfo[idx]->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
           cfgLchReqInfo[idx]->u.cfgInfo.u.lchCfg.crnti = tipUeReCfg->oldCRnti;
           tipUnpkUeLcCfg((LcConfigInfo*)tipLchCfg, &cfgLchReqInfo[idx]->u.cfgInfo.u.lchCfg, tipTransId);
           deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_LCH_CFG, RGR_CFG_TRANSID_SIZE);
           /* Sending Mac Config before Sch */
           RgUiRgrCfgReq(pst, spId, transId, cfgLchReqInfo[idx]);
           idx1 = idx + 1;
           tipLchCfg++;
        }
        tipLchCfg = (LcConfigInfo*)&tipUeReCfg->LcInfo;
        for(idx = 0; idx < lchCnt; idx++)
        {
           if(cfg->lcg1 && cfg->lcg2 && cfg->lcg3)
           {
              break;
           }
           if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgLchReqInfo[idx1],sizeof(RgrCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
           }
           cmMemset((U8 *)cfgLchReqInfo[idx1], 0, sizeof(RgrCfgReqInfo));

          /*Send LCH config */
           cfgLchReqInfo[idx]->action = RGR_CONFIG;
           cfgLchReqInfo[idx]->u.cfgInfo.cfgType = RGR_LCG_CFG;
           cfgLchReqInfo[idx]->u.cfgInfo.u.lchCfg.cellId = hdr->cellId;
           cfgLchReqInfo[idx]->u.cfgInfo.u.lchCfg.crnti = tipUeReCfg->oldCRnti;
           tipUnpkUeLcgCfg((LcConfigInfo*)tipLchCfg, &cfgLchReqInfo[idx1]->u.cfgInfo.u.lcgCfg, tipTransId);
           deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_LCG_CFG, RGR_CFG_TRANSID_SIZE);
           /* Sending Mac Config before Sch */
           RgUiRgrCfgReq(pst, spId, transId, cfgLchReqInfo[idx1]);
           tipLchCfg++;
        }
     }
     break;
     case MAC_UEDELETE_REQ:
     {
        MacUeDeleteReq   *tipUeDelReq = (MacUeDeleteReq*)&hdr->message;
        cfg->key = tipPrepareLL2Key(hdr);
        cfg->upperLyrTrans = hdr->transId;
        cfg->ueId.ueIndex = tipUeDelReq->ueInfo.ueIndex;
        cfg->ueId.cRnti = tipUeDelReq->ueInfo.cRnti;
        TipAddLL2Trans(cfg);
        cfgReqInfo->action = RGR_DELETE;
        cfgReqInfo->u.delInfo.delType = RGR_UE_CFG; 
        tipTransId = cfg->key; 
        deriveLL2TransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_UE_CFG, RGR_CFG_TRANSID_SIZE);
        cfgReqInfo->u.delInfo.u.ueDel.cellId = hdr->cellId; 
        cfgReqInfo->u.delInfo.u.ueDel.crnti = tipUeDelReq->ueInfo.cRnti;
        /* Sending MAC Config before SCH */
        ret = tipSendCrgCfgReq(hdr, pst, tipTransId);
        /* Sending CTF Config before SCH */
        ret = tipSendCtfUeCfgReq(hdr, pst);
        RgUiRgrCfgReq(pst, spId, transId, cfgReqInfo);
     }
     break;
     case MAC_CELLSTART_IND:
     {
     }
     break;
     case MAC_INIT_REQ:
     {
         tipHdlInitReq(hdr);
     }
     break;
     default:
     {
        printf("MAC Tip Message(%d) unhandled\n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ROK);
}/*end of tipUnpkAppMacMsg*/


/**
* @brief unpack all L3-Mac massages received from L2
*
* @details
*
*     Function: tipUnpkMacAppMsg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkMacAppMsg
(
Pst*    pst,
Buffer* mBuf
)
{
  U8             rcvBuf[MAX_BUFF_LEN_L2_L3];
  RgrCfgTransId  transId;
  TipPacket      *hdr = NULLP;
  S16            suId = 0;
  U32            tipTransId;
  S16            ret, ret1;
  MsgLen         msgLen,bufLen;
   
  ret = SFndLenMsg(mBuf, &bufLen);
  ret1 = SCpyMsgFix(mBuf, 0, bufLen, rcvBuf, &msgLen);
   
  hdr = (TipPacket*)&rcvBuf;
  switch(hdr->msgId)
  {
     case MAC_CELLCONFIG_RSP:
     {
        MacCellConfigRsp *cellCfgCfm;
        cellCfgCfm = (MacCellConfigRsp*)&hdr->message;

        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_MAC, TIP_MOD_RRC,
              TIP_MSG_MAC_CELLCONFIG_RSP, hdr->transId);

        tipTransId = hdr->transId; 
        deriveTransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_CELL_CFG, RGR_CFG_TRANSID_SIZE);
        NxLiRgrCfgCfm(pst, suId, transId, cellCfgCfm->status);
     }
     break;
     case MAC_CELLRECONFIG_RSP:
     {
     }
     break;
     case MAC_CELLDELETE_RSP:
     {
     }
     break;
     case MAC_BROADCASTMSG_RSP:
     {
        MacBroadcastMsgRsp *siCfgCfm;
        siCfgCfm = (MacBroadcastMsgRsp*)&hdr->message;

        TIP_EVENT_LOG(hdr->cellId, 0, TIP_MOD_MAC, TIP_MOD_RRC,
              TIP_MSG_MAC_BROADCASTMSG_RSP, hdr->transId);

        tipTransId = hdr->transId; 
        deriveTransId((U8 *)&transId, tipTransId, RGR_CONFIG, RGR_SI_CFG_TYPE_MIB, RGR_CFG_TRANSID_SIZE);
        NxLiRgrSiCfgCfm(pst, suId, transId, siCfgCfm->status);
     }
     break;
     case MAC_UECONFIG_RSP:
     {
        MacUeConfigRsp *ueCfgCfm;
        CtfCfgTransId  L1transId;
        U32            *transIdPtr = 0;
        ueCfgCfm = (MacUeConfigRsp*)&hdr->message;

        TIP_EVENT_LOG(hdr->cellId, ueCfgCfm->ueInfo.cRnti, TIP_MOD_MAC,
              TIP_MOD_RRC, TIP_MSG_MAC_UECONFIG_RSP, hdr->transId);

        tipTransId = hdr->transId; 
        deriveTransId((U8 *)&transId, tipTransId, RGR_UE_CFG, RGR_CONFIG,RGR_CFG_TRANSID_SIZE);
        NxLiRgrCfgCfm(pst, suId, transId, ueCfgCfm->status);
        deriveTransId((U8 *)&L1transId, tipTransId, 0/*WR_CTF_UE_CFG*/,CTF_CONFIG,CTF_CFG_TRANSID_SIZE);
        transIdPtr = (U32 *)&L1transId.trans[7];
        *transIdPtr = 0;
        *transIdPtr  |=  hdr->cellId << 20;
        *transIdPtr  |= ueCfgCfm->ueInfo.ueIndex << 12;
        WrIfmL1CfgCfm(pst, suId, L1transId, 1);
     }
     break;
     case MAC_UERECONFIG_RSP:
     {
        MacUeReconfigRsp *ueRecfgCfm;
        TipL3CfgDat      *recfg;
        U64              key;
        ueRecfgCfm = (MacUeReconfigRsp*)&hdr->message;

        TIP_EVENT_LOG(hdr->cellId, ueRecfgCfm->ueInfo.cRnti, TIP_MOD_MAC,
              TIP_MOD_RRC, TIP_MSG_MAC_UERECONFIG_RSP, hdr->transId);

        key = tipDeriveKey(hdr);
        if(ROK != TipFindTransaction(key, &recfg))
        { 
           printf("\n\n ****** Finding key failed [key: %lld]*******\n\n", key);
        }
        else
        {
           if(ROK != TipDelTransaction(recfg))
           {
              printf("\n\n ****** Delete transaction failed *******\n\n");
           }

           hdr->transId = recfg->upperLyrTrans;
           tipTransId = hdr->transId;

           if(recfg->rgCfgDat.msgCnt > 0)
           {
              U8 idx;
              RgrCfgReqInfo *cfgReqInfo;
              for(idx = 0; idx < recfg->rgCfgDat.msgCnt; idx++)
              {
                 cfgReqInfo = recfg->rgCfgDat.schdUeRecfgReq[idx];
                 if(cfgReqInfo->u.recfgInfo.recfgType == RGR_UE_CFG)
                 {
                    if(cfgReqInfo->u.recfgInfo.u.ueRecfg.oldCrnti != 
                          cfgReqInfo->u.recfgInfo.u.ueRecfg.newCrnti)
                    {
                       /* response for UE ID change */
                       deriveTransId((U8 *)&transId, tipTransId, RGR_UE_CFG,
                             RGR_RECONFIG, RGR_CFG_TRANSID_SIZE);
                       NxLiRgrCfgCfm(pst, suId, transId, ueRecfgCfm->status);
                       SPutSBuf(pst->region, pst->pool,
                             (Data *)recfg->rgCfgDat.schdUeRecfgReq[idx],
                             sizeof(RgrCfgReqInfo));
                    }
                 }
              }
              recfg->rgCfgDat.msgCnt = 0;
           }
           else /* TODO: to move all cases inside the above for loop */
           {
              /* UE RECONFIG CFM - reset last 4 bits and then set to the 
               * appropriate config mask */
              tipTransId = (hdr->transId & 0xfffffff0) | 0x0f;
              deriveTransId((U8 *)&transId, tipTransId, RGR_UE_CFG, RGR_RECONFIG, RGR_CFG_TRANSID_SIZE);
              NxLiRgrCfgCfm(pst, suId, transId, ueRecfgCfm->status);
              /* SRB2 LCH CONFIG CFM */
              tipTransId = (hdr->transId & 0xfffffff0) | 0x0a;
              deriveTransId((U8 *)&transId, tipTransId, RGR_LCH_CFG, RGR_CONFIG, RGR_CFG_TRANSID_SIZE);
              NxLiRgrCfgCfm(pst, suId, transId, ueRecfgCfm->status);
              /* DRB LCH(s) CONFIG CFM */
              for(U8 idx = 0,idx1 = 0; idx < recfg->rgCfgDat.lchIdCnt; idx++)
              {
                 tipTransId = (hdr->transId & 0xfffffff0) | idx;
                 if(recfg->rgCfgDat.lchId[idx] != ueRecfgCfm->lc[idx1].lchId)
                 {
                    deriveTransId((U8 *)&transId, tipTransId, RGR_LCH_CFG, RGR_CONFIG, RGR_CFG_TRANSID_SIZE);
                    NxLiRgrCfgCfm(pst, suId, transId, 0);
                 }
                 else
                 {
                    deriveTransId((U8 *)&transId, tipTransId, RGR_LCH_CFG, RGR_CONFIG, RGR_CFG_TRANSID_SIZE);
                    NxLiRgrCfgCfm(pst, suId, transId, 1);
                    idx1++;
                 }
                 recfg->rgCfgDat.lchId[idx] = 0; 
              }
              recfg->rgCfgDat.lchIdCnt = 0;

              if(ROK != SPutSBuf(pst->region, pst->pool, (Data *)recfg, sizeof(TipL3CfgDat)))
              {
#if (ERRCLASS & ERRCLS_ADD_RES)
                 SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                       __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                       (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
              }

              for(U8 idx = 0; idx < 3; idx++)
              {
                 tipTransId = (hdr->transId & 0xfffffff0) | (0x0000000b + idx);
                 deriveTransId((U8 *)&transId, tipTransId, RGR_LCG_CFG, RGR_CONFIG, RGR_CFG_TRANSID_SIZE);
                 NxLiRgrCfgCfm(pst, suId, transId, ueRecfgCfm->status);
              }
           }
        }
     }
     break;
     case MAC_UEDELETE_RSP:
     {
        MacUeDeleteRsp *ueDelCfm;
        CtfCfgTransId  L1transId;
        TipL3CfgDat    *cfg;
        U64            key;
        ueDelCfm = (MacUeDeleteRsp*)&hdr->message;

        TIP_EVENT_LOG(hdr->cellId, ueDelCfm->ueInfo.cRnti, TIP_MOD_MAC,
              TIP_MOD_RRC, TIP_MSG_MAC_UEDELETE_RSP, hdr->transId);

        tipTransId = hdr->transId;
        deriveTransId((U8 *)&transId, tipTransId, RGR_UE_CFG, RGR_DELETE,RGR_CFG_TRANSID_SIZE);
        NxLiRgrCfgCfm(pst, suId, transId, ueDelCfm->status);
#if 0
        U32            *transIdPtr = 0;
        deriveTransId((U8 *)&L1transId, tipTransId, 0/*WR_CTF_UE_CFG*/,0/*WR_CTF_UE_CFG*/,CTF_CFG_TRANSID_SIZE);
        transIdPtr = &L1transId.trans[4];
        *transIdPtr = 0;
        *transIdPtr  |=  hdr->cellId << 20;
        deriveTransId((U8 *)&L1transId, tipTransId, CTF_UE_CFG,CTF_DELETE,CTF_CFG_TRANSID_SIZE);
#else
        key = tipPrepareKey(hdr->cellId, ueDelCfm->ueInfo.cRnti, 0);
        if(ROK != TipFindTransaction(key, &cfg))
        { 
           printf("\n\n ****** Finding key failed *******\n\n");
           SPutMsg(mBuf);
           RETVALUE(RFAILED);
        }
        if(ROK != TipDelTransaction(cfg))
        {
           printf("\n\n ****** Delete transaction failed *******\n\n");
        }
#endif
        
        TIP_COPY_L1_TRANSID(cfg->l1TransId, L1transId);
        WrIfmL1CfgCfm(pst, suId, L1transId, 1);
     }
     break;
     case L2_UERELEASE_IND:
     {
        L2UeRelInd     *rlfInd;

        rlfInd = (L2UeRelInd *)hdr->message;

        TIP_EVENT_LOG(hdr->cellId, rlfInd->ueInfo.cRnti, TIP_MOD_MAC,
              TIP_MOD_RRC, TIP_MSG_L2_UERELEASE_IND, hdr->transId);

        if(rlfInd->cause != L2_UEREL_CAUSE_MAXRETX)
        {
           if (wrUmmSndCtxtRelReq(rlfInd->ueInfo.cRnti, hdr->cellId,
               WR_UMM_UE_LOST) != ROK)
           {
              /* Log error */
              printf("\n****wrUmmSndCtxtRelReq Failed****\n");
              SPutMsg(mBuf);
              RETVALUE(RFAILED);
           }
       }
       else
       {
          /* L2_UEREL_CAUSE_MAXRETX not handled */
       }
     }
     break;
     case L3_TTI_IND:
     {
        L3TtiInd *l3TtiInd;
        l3TtiInd = (L3TtiInd*)&hdr->message;
        RgrTtiIndInfo *ttiInd; 
        if ((SGetSBuf(pst->region, pst->pool, (Data **)&ttiInd, sizeof(RgrTtiIndInfo))) != ROK) 
        {
#if (ERRCLASS & ERRCLS_ADD_RES)      
           SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ERGR029, (ErrVal)0, "Memory Allocation failed");
#endif      
           SPutMsg(mBuf);
           RETVALUE(RFAILED);
        }
        ttiInd->cellId = hdr->cellId;  
        ttiInd->sfn = l3TtiInd->timingInfo.sfn;
        NxLiRgrTtiInd(pst, suId, ttiInd); 
     }
     break;  
     default:
     {
        printf("L3-MAC Tip Message(%d) unhandled\n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ROK);
}/*end of tipUnpkAppMacMsg*/
