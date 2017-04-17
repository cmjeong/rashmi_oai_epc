
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_l1_msg.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=59;


static int RLOG_MODULE_ID=32;

#include "wr.h"
#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_umm_l1_msg.h"
#include "wr_ifm_l1.h"


/**
 *  @brief This function build Ctf Ue config
 *
 *      Function: wrUmmFillPhyUeCfg
 *
 *          Processing steps:
 *          - update the structure from the UE CB
 *          - call the interfce function to send the message
 *
 *
 *  @param [in]  transId : transid of the UE config message sent to Ctf
 *  @param [in]  ueCb    : pointer to UeCb of the UE for which ueCfg 
 *                         message is sent
 *  @param [out] cfgInfo : pointer to be update with UE config Info
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */

PUBLIC S16 wrUmmPhyFillUeCfg
(
U32                          transId,
WrUeCb                       *ueCb,
CtfCfgReqInfo                *cfgInfo
)
{
   CtfDedCfgInfo             *ueCfgParam = NULLP;

   cfgInfo->cfgType = CTF_CONFIG;
   cfgInfo->u.cfg.cfgElem = CTF_UE_CFG;
   ueCfgParam = &cfgInfo->u.cfg.u.dedCfg;
   if(ueCb == NULLP)
   {
      RLOG0(L_ERROR, "Invalid UeCb");
      RETVALUE(RFAILED);
   }
   else
   {
      ueCfgParam->cellId = ueCb->cellId;
      ueCfgParam->ueId = ueCb->crnti;
   }

   /* Ue category */
   ueCfgParam->ueCatCfg.pres = TRUE;
   ueCfgParam->ueCatCfg.ueCategory = ueCb->ueCat;

   /* PDSCH Cfg */
   ueCfgParam->pdschCfg.pres = TRUE;
   ueCfgParam->pdschCfg.pA = ueCb->pdschDedCfg.p_a;

   /* PUCCH Cfg */
   ueCfgParam->pucchCfg.pres = ueCb->pucchDedCfg.pres;
   ueCfgParam->pucchCfg.dedPucchCfgType = CTF_IE_CFG_SETUP;
   ueCfgParam->pucchCfg.pucchSetup.repFact = ueCb->pucchDedCfg.repeatFactor;
   ueCfgParam->pucchCfg.pucchSetup.n1PUCCHRep = ueCb->pucchDedCfg.n1pucchAn;

   /* PUSCH Cfg */
   ueCfgParam->puschCfg.pres = TRUE;
   ueCfgParam->puschCfg.betaOffsetAckIdx = ueCb->puschDedCfg.ackIdx;
   ueCfgParam->puschCfg.betaOffsetRiIdx = ueCb->puschDedCfg.riIdx;
   ueCfgParam->puschCfg.betaOffsetCqiIdx = ueCb->puschDedCfg.cqiIdx;

/* Fix: tfu upgrade changes */
#ifndef TFU_UPGRADE
   if(ueCb->bResCfgBitMap &  WR_UE_RADIO_RES_CFG_CQI)
   {
      /* CQI Reporting */

      /*Fix for ccpu00126943- removal of platform name macro*/

      ueCfgParam->cqiRptCfg.pres = TRUE;

      ueCfgParam->cqiRptCfg.reportingMode = CTF_CQI_RPTMODE_PRDIOC;

      /* APERIODIC is not supported for now */
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiPeriodicCfgType 
         = CTF_IE_CFG_SETUP;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.cqiPUCCHRsrcIndx 
         = ueCb->cqiRptCfg.cqiPucchRsrcIdx;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.cqiPmiCfgIndx 
         = ueCb->cqiRptCfg.cqipmiCfgIdx;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.formatIndicator 
         = ueCb->cqiRptCfg.fmtInd; 
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.subbandCqi.k 
         = ueCb->cqiRptCfg.subbndCqik;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.riCfgPres
         = FALSE;
      ueCfgParam->cqiRptCfg.reportMode.periodicRpt.cqiSetup.simultaneousAckNack
         = ueCb->cqiRptCfg.simulAckNackAndCQI;
   }
   else
   {
      ueCfgParam->cqiRptCfg.pres = FALSE;
   }
   /* UL SRS Cfg */
   ueCfgParam->srsUlCfg.pres = ueCb->srsUlDedCfg.pres;
   if(ueCb->bResCfgBitMap &  WR_UE_RADIO_RES_CFG_SR)
   {
      if (ueCb->srsUlDedCfg.pres)
      {
         ueCfgParam->srsUlCfg.dedSrsUlCfgType            = CTF_IE_CFG_SETUP;
         ueCfgParam->srsUlCfg.dedSrsSetup.srsBw          = ueCb->srsUlDedCfg.srsBw;
         ueCfgParam->srsUlCfg.dedSrsSetup.srsHopngBw     = ueCb->srsUlDedCfg.srsHoppingBw;
         ueCfgParam->srsUlCfg.dedSrsSetup.freqDmnPos     = ueCb->srsUlDedCfg.freqDomPos;
         ueCfgParam->srsUlCfg.dedSrsSetup.duration       = ueCb->srsUlDedCfg.duration;
         ueCfgParam->srsUlCfg.dedSrsSetup.srsCfgIdx      = ueCb->srsUlDedCfg.srsCfgIdx;
         ueCfgParam->srsUlCfg.dedSrsSetup.txComb         = ueCb->srsUlDedCfg.transComb;
         ueCfgParam->srsUlCfg.dedSrsSetup.cyclicShift    = ueCb->srsUlDedCfg.cyclicshift;
      }
      /* Dedicated SR Cfg */
      ueCfgParam->dedSRCfg.pres = TRUE;
      ueCfgParam->dedSRCfg.dedSRCfgType = CTF_IE_CFG_SETUP;
      ueCfgParam->dedSRCfg.dedSrSetup.srPUCCHRi = ueCb->srCfg.srPUCCHResIdx;

      ueCfgParam->dedSRCfg.dedSrSetup.srCfgIdx = ueCb->srCfg.srCfgIdx;
   }
   else
   {
      ueCfgParam->dedSRCfg.pres = FALSE;
   }

#endif /* TFU_UPGRADE */

   /* Antenna Cfg */
   ueCfgParam->antInfo.pres = TRUE;
   ueCfgParam->antInfo.txMode = ueCb->antennaInfo.txmode;
   ueCfgParam->antInfo.ueTxAntSelection.cfgType = CTF_IE_CFG_SETUP; 
   ueCfgParam->antInfo.ueTxAntSelection.txAntSelect = 
              ueCb->antennaInfo.ueTxAntSel;
   RETVALUE(ROK);
} /* wrUmmPhyFillUeCfg */

/**
 *  @brief This function build and send the UE release message
 *
 *      Function: wrUmmL1SndUeRel
 *
 *          Processing steps:
 *          - Allocate memory for ue release message 
 *          - update the structure
 *          - call the interface function to send the message
 *
 *
 *  @param [in]  transId : transid of the UE config message sent to Ctf
 *  @param [in]  crnti   : crnti of the UE to be released
 *  @param [in]  cellId  : cell ID of cell from which UE is released 
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */
PUBLIC S16 wrUmmL1SndUeRel
(
U32                          transId,
U16                          crnti,
U16                          cellId
)
{
   CtfCfgReqInfo             *cfgInfo;

   WR_ALLOC(&cfgInfo, sizeof(CtfCfgReqInfo));
   if(cfgInfo == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   cfgInfo->cfgType = CTF_DELETE;
   cfgInfo->u.release.cfgElem = CTF_UE_CFG;
   cfgInfo->u.release.u.dedRel.cellId = cellId;
   cfgInfo->u.release.u.dedRel.ueId = crnti;

   if(ROK != wrIfmPhyUeCfg(cfgInfo, transId))
   {
      RLOG0(L_ERROR, "wrIfmPhyUeCfg failed.");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/********************************************************************30**

           End of file:    $SID$

*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
