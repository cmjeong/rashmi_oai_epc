
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_scell.c

     Sid:      $SID$ 

     Prg:      Amit 

*********************************************************************21*/

/* header include files (.h) */

#include "wr.h"            /* Common headers and Data Structures */
#include "wr_utils.h"
#include "wr_umm.h"        /* UMM Specific files */
#include "wr_umm_rrc_msg.h"
#include "wr_umm_msg.h"
#include "wr_umm_trans.h"
#include "wr_umm_scell.h"        /* UMM Specific files */
#include "wr_ifm_rrc.h"
#include "wr_ifm_schd.h"
#include "wr_ifm_l1.h"
#include "wr_ifm_rrm.h"
#include "wr_umm_sch_msg.h"

#ifdef LTE_ADV
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=144;
static int RLOG_MODULE_ID=32;

EXTERN U16      wrCliPCellId;
EXTERN U16      wrCliSCellId;
PRIVATE Void wrUmmSCellFillAperCsiTgr
(
 WrUeCb                   *ueCb,
 U8                       *triggerSet1,
 U8                       *triggerSet2
 );

EXTERN PUBLIC S16 wrUmmFillN1PucchRes
(
 WrUeCb                          *ueCb, 
 NhuDatReqSdus                   *recfgMsg,
 NhuRadioResourceConfigDedicated *rrcCfgDed
 );
/** @brief This function frees on SCELL from Trans CB
 *
 * @details
 *
 *     Function: wrUmmFreeSCellInfoFrmUeCb
 *
 *         Processing steps:
 *         - Free the Scell allocation 
 *         - Mark the sCell index in UECB as NULL
 *
 * @param[in]   ueCb         : UE Control Block Pointer
 * @param[in]  sCellTransCb : Pointer to sCell info in trans CB
 * @param[in]  idxInTransCb : Index of sCell in trans CB
 *
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 wrUmmFreeSCellInfoFrmUeCb
(
 WrUeCb *ueCb,
 WrUmmSCellTransCb     *sCellTransCb,
 U8     idxInTransCb
)
{
   if(NULLP != sCellTransCb->sCellTransInfo[idxInTransCb].sCellInfo) 
   {
      ueCb->sCellInfo[sCellTransCb->sCellTransInfo[idxInTransCb].sCellInfo->sCellIdx - 1] = NULLP; 
      WR_FREE(sCellTransCb->sCellTransInfo[idxInTransCb].sCellInfo, sizeof(WrSCellInfo));
   } 
   RETVALUE(ROK);
} /* End of wrUmmFreeSCellInfoFrmUeCb */



/** @brief This function frees on SCELL from Trans CB
 *
 * @details
 *
 *     Function: wrUmmSCellTransInfoFree
 *
 *         Processing steps:
 *         - Free the Scell allocation 
 *         - Mark the sCell index in UECB as NULL
 *
 * @param[in]   ueCb         : UE Control Block Pointer
 * @param[in]  sCellTransCb : Pointer to sCell info in trans CB
 * @param[in]  idxInTransCb : Index of sCell in trans CB
 *
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 wrUmmSCellTransInfoFree
(
 WrUeCb *ueCb,
 WrUmmSCellTransCb     *sCellTransCb,
 U8     numSCells
)
{
   U32 indx; 
   for(indx = 0; indx < numSCells; indx++) 
   { 
      wrUmmFreeSCellInfoFrmUeCb(ueCb, sCellTransCb, indx);
   }  

   RETVALUE(ROK);
} /* End of wrUmmSCellTransInfoFree */


/** @brief This function finds and return the SCell Index
 *
 * @details
 *
 *     Function: wrUmmGetSCellFreeIndex
 *
 *         Processing steps:
 *         - Traverse ueCb SCell list and return the index coresponding to first NULL found
 *
 * @param[in]   ueCb     : UE Control Block Pointer
 * @param[in]   sCellId  : Secondary Cell Id
 * @param[out]  sCellIdx : sCellIdx pointer
 *
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 wrUmmGetSCellFreeIndex
(
 WrUeCb *ueCb,
 U8     *sCellIdx,
 U16    sCellId
)
{
   U8      idx;
   for (idx = 0; idx < WR_MAX_SCELL_PER_UE; idx++)
   {
      /*To Check if this sCell has never been allocated an sCellIdx*/
      if(NULLP != ueCb->sCellInfo[idx])
      {
         if(sCellId == ueCb->sCellInfo[idx]->sCellId)
         {
            RETVALUE(RFAILED);
         }
      }
   }
   for (idx = 0; idx < WR_MAX_SCELL_PER_UE; idx++)
   {
      if (ueCb->sCellInfo[idx] == NULLP)
      {
         /* Since SCell index range is 1-7. 0 value is not valid */
         *sCellIdx = idx + 1;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
} /* End of wrUmmGetSCellFreeIndex */


/** @brief This function finds sets sCellInfo at a sCellIdx in the UECB
 *
 * @details
 *
 *     Function: wrUmmSetSCellInfoAtIdx
 *
 *         Processing steps:
 *         - Set the sCellInfo in the UECB and set it state to not active.
 *
 * @param[in]   ueCb     : UE Control Block Pointer
 * @param[out]  sCellInfo : SCell info pointer
 *
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 wrUmmSetSCellInfoAtIdx
(
 WrUeCb *ueCb,
 WrSCellInfo *sCellInfo
)
{
   U32 idx = 0;
   if (sCellInfo->sCellIdx)
   {
      idx = ((sCellInfo->sCellIdx) - 1);/*kw_fix*/
      ueCb->sCellInfo[idx] = sCellInfo;
      /* Setting the state of SCell to inactive. This will be set
       * to TRUE in case if this SCell is successfully activted */
      ueCb->sCellInfo[idx]->isScellAdded = FALSE;
      RETVALUE(ROK);
   }

   RETVALUE(RFAILED);
} /* End of wrUmmSetSCellInfoAtIdx */


/** @brief This function will commit transCb information to UeCb 
 *
 * @details
 *
 *     Function: wrUmmSCellCommitTransInfoToUeCb
 *
 *         Processing steps:
 *         - Store the Received information in UECb after 
 *           Reconfig Complete From UE
 *
 * @param[transCb]  transCb : 
 *
 * @return S16
 *    -#return : RETVOID 
 */
PRIVATE Void wrUmmSCellCommitTransInfoToUeCb
(
 WrUmmTransCb *transCb
)
{
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   WrSCellInfo               *sCellInfo;
   U32                        idx;
   
   for(idx = 0; idx < sCellTransCb->numSCells; idx++)
   {
      sCellInfo   = sCellTransCb->sCellTransInfo[idx].sCellInfo;
      if((transCb->ueCb != NULLP) && (NULLP != sCellInfo))
      {
         sCellInfo->isScellAdded = TRUE;
         transCb->ueCb->numSCells = transCb->u.sCellTransCb.numSCells;
         transCb->ueCb->sCellInfo[idx] = sCellInfo;
      }
   }
   RETVOID;
}/* End of wrUmmSCellCommitTransInfoToUeCb */


/** @brief This function indicates the Schedular that SCELLS are ready for activation.
 *
 * @details
 *     Function: wrUmmSendSCellSchActReady
 *
 *         Processing steps:
 *         - Builds the multiple SCell Activation Ready Cfg for a UE.
 *         - Delivers the PDU towards Scheduler through IFM module.
 *
 *
 * @param WrUmmTransCb *transCb
 * @return ROK/RFAILED
 */

PUBLIC S16 wrUmmSendSCellSchActReady
(
 WrUmmTransCb      *transCb
)
{
   WrUeCb                    *ueCb = transCb->ueCb;
   RgrCfgReqInfo             *cfgReq;
   RgrSCellActDeactEvnt      *sCellActDeactEvnt;
   WrSCellInfo               *sCellInfo;
   U8                         idx;
   U32                        transId;
   U8                         numSCells = 0;

   WR_ALLOC(&cfgReq, sizeof(RgrCfgReqInfo));
   if (NULLP == cfgReq)
   {
      RETVALUE(RFAILED);
   }
   sCellActDeactEvnt              = &cfgReq->u.sCellActDeactEvnt;
   cfgReq->action                 = RGR_SCELL_READY;
   sCellActDeactEvnt->crnti       = ueCb->crnti;

   for(idx = 0; idx < WR_MAX_SCELL_PER_UE; idx++)
   {
      sCellInfo   = ueCb->sCellInfo[idx];
      if(NULLP != sCellInfo)
      {
         /*Added isRest case: when Re-est occurs during SCell Add
          * then we need to Verify if SCell Is Added then add those 
          * cells during Re-establishment */
         if(WR_UMM_RRC_REESTAB_TRANS == transCb->transTyp) 
         {
            if(TRUE == sCellInfo->isScellAdded)
            {
               sCellActDeactEvnt->sCellActDeactInfo[idx].sCellIdx = sCellInfo->sCellIdx;
               numSCells++;

            }
            else
            {
               /* Dont add the SCells for thouse did not had Reconfig Complete 
                * during the SCell Add Transaction when Re-est Occured*/
               continue;
            }
         }
         else
         {
            /* Normal SCellAdd Case */
            sCellActDeactEvnt->sCellActDeactInfo[idx].sCellIdx = sCellInfo->sCellIdx;
            numSCells++;
         }
      }
   }
   sCellActDeactEvnt->numOfSCells = numSCells;
   transId = transCb->transId | WR_UMM_SCH_TRANS_SCELL_READY;

   /* Dispatch the prepared message to scheduler */
   WrIfmSchdCfgUe(cfgReq, transId, ueCb->cellId);

   RETVALUE(ROK);
} /* End of wrUmmSendSCellSchActReady */

/** @brief This function performs the SCell Activation
 *         towards Scheduler.
 *
 * @details
 *     Function: wrUmmCliSendSCellSchActDeact
 *
 *         Processing steps:
 *         - Builds the multiple SCell Activation/Deactivation Cfg for a UE.
 *         - Delivers the PDU towards Scheduler through
 *           IFM module.
 *
 *
 * @param WrUeCb       *ueCb
 * @param U32          transCbtransId
 * @param U8           action
 * @return ROK/RFAILED
 */

PRIVATE S16 wrUmmCliSendSCellSchActDeact
(
 WrUeCb       *ueCb,
 U32          transCbtransId,
 U8           action
)
{
   RgrCfgReqInfo             *cfgReq;
   RgrSCellActDeactEvnt      *sCellActDeactEvnt;
   WrSCellInfo               *sCellInfo;
   U8                         idx;
   U32                        transId;

#ifdef CA_DBG 
   printf("Scell event action =%d \n", action);
#endif   
   WR_ALLOC(&cfgReq, sizeof(RgrCfgReqInfo));
   if (NULLP == cfgReq)
   {
      RETVALUE(RFAILED);
   }
   if(RGR_SCELL_ACT == action)
   {
      cfgReq->action    = RGR_SCELL_ACT;
      transId = transCbtransId | WR_UMM_SCH_TRANS_SCELL_ACT;
   }
   else
   {
      cfgReq->action    = RGR_SCELL_DEACT;
      transId = transCbtransId | WR_UMM_SCH_TRANS_SCELL_DEACT;
   }
   sCellActDeactEvnt      = &cfgReq->u.sCellActDeactEvnt;
   sCellActDeactEvnt->numOfSCells = ueCb->numSCells;
   sCellActDeactEvnt->crnti       = ueCb->crnti;

   for(idx = 0; idx < ueCb->numSCells; idx++)
   {
	   sCellInfo   = ueCb->sCellInfo[idx];
	   if(NULLP != sCellInfo)
	   {
		   sCellActDeactEvnt->sCellActDeactInfo[idx].sCellIdx = sCellInfo->sCellIdx;
#ifdef CA_DBG
         printf("sCellInfo->sCellIdx = %d, cfgReq->action =%d \n", sCellInfo->sCellIdx, cfgReq->action);
#endif         
	   }
   }
   /*Moved transaction id setting above*/
   /* Dispatch the prepared message to scheduler */
   WrIfmSchdCfgUe(cfgReq, transId, ueCb->cellId);

   RETVALUE(ROK);
} /* End of wrUmmCliSendSCellSchActDeact */

/** @brief This function will handle RRC Re-cfg complete message for Secondary
 * cell   
 * @details
 *
 *     Function: wrUmmSCellPrcRrcMsg
 *
 *         Processing steps:
 *         1.Commit Transaction Information in UeCb
 *
 * @param [in] ueCb
 * @param [in] cellId 
 * @return S16
    -# Success : ROK
    -# Failure : RFAILED 
 */ 
PRIVATE S16 wrUmmSCellPrcRrcMsg
(
 WrUmmTransCb                *transCb
)
{  
   NhuUlDcchMsg                    *ulDcch;
   NhuUL_DCCH_MsgTypc1             *c1;
   S16                             ret = ROK;
   WrUeCb                         *ueCb = NULLP;
   ueCb                           = transCb->ueCb;
   U32                            rrc_TransId = 0;
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;

   TRC2(wrUmmSCellPrcRrcMsg)

      ulDcch = &transCb->msg->u.uuIndPdu->sdu.m.ulDcchMsg;
   c1     = &ulDcch->dcchMsg.message.val.c1;
   switch(c1->choice.val)
   {
      case C1_RRCCONRECFGNCOMPL:
         {
            printf("\nSCell: RRC Reconfig Complete Received");
            RLOG0(L_ALWAYS, "SCell: RRC Reconfig Complete Received");
            /* Stop the RRC Reconfiguration Timer */
            wrStopTransTmr(transCb, WR_TMR_RECONFIGURE);
            /* Since Handling of SCell has been sucessfully added/modified in
             * all layers , so commit transCb info in UeCb now */
            rrc_TransId = c1->val.rnRecfgnCompl_r10.rrc_TrnsxnId.val;
            if (wrUmmRelRrcTransId(transCb->ueCb, C1_RRCCONRECFGN, rrc_TransId) != ROK)
            {
               RLOG0(L_ERROR, "Release of transaction ID failed ");
            }
            /* Send SCell Activation to SCH */
            if(WR_UMM_SCELL_ADD == sCellTransCb->triggerTyp)
            {
               wrUmmSCellCommitTransInfoToUeCb(transCb);
#ifdef CA_DBG
               printf("SCell Added REconfig Complete Receoived and SCell ready for activation");
#endif               
               RLOG0(L_ALWAYS, "Trigger to SCHD that all the SCELLS added are ready for activation");
               wrUmmSendSCellSchActReady(transCb);
               wrUmmTransComplete(transCb);
            }
            else if(WR_UMM_SCELL_RELEASE == sCellTransCb->triggerTyp)
            {
               wrUmmSCellTransInfoFree(transCb->ueCb, sCellTransCb, sCellTransCb->numSCells);
               wrUmmTransComplete(transCb);
            }
            else
            {
               RLOG0(L_ALWAYS, "wrUmmSCellPrcRrcMsg:Invalid TransId");
               RETVALUE(RFAILED);
            }  
            break;
         }
      default:
         {
            RLOG0(L_EVENT, "Currently there is no handling for dcchMsg"
                  "message received as part of a UU_IND_PDU");
            RETVALUE(RFAILED);
         }
   }
   RETVALUE(ret);
}

/** @brief This function is responsible for filling the RRC structure for
 *         configuring the lower layers.
 *
 * @details
 *
 *     Function: wrUmmSCellFillRrcCfg
 *
 *         Processing steps:
 *         - Fill SCellInfo, to fill the MAC Instance Config
 *
 * @param[in] transCb : transaction information 
 * @param[in, out]     evnt    : RRC configuration
 * @return S16
 *    -#Success : ROK
 */
PRIVATE S16 wrUmmSCellFillRrcCfg
(
WrUmmTransCb                 *transCb,
NhuDatReqSdus                *evnt
)
{
   WrUmmSCellTransCb         *sCellTransCb= &transCb->u.sCellTransCb;
   NhuUeCfgInfo              *ueCfg;
   U32                       idx;
   U16                       cellId = transCb->ueCb->cellId;
   WrCellCb                  *emmCellCb = NULLP;
      
   RLOG0(L_ALWAYS, "Filling of SCell ueReconfig Message");
   evnt->sdu.isUeCfgPres = TRUE;
   ueCfg = &(evnt->sdu.ueCfg);

   /* CHECK in RRC for Proper UE CFG to Skip RLC/PDCP*/
   ueCfg->ueCfgBitMsk = NHU_EXP_CFG_UESEC_CFG;

   ueCfg->ueSCellCfgInfo.numSCells = sCellTransCb->numSCells;
   for(idx = 0; idx < sCellTransCb->numSCells; idx++)
   {
      ueCfg->ueSCellCfgInfo.ueSCellCfg[idx].sCellId = 
           sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellId;
      WR_EMM_GET_CELLCB(emmCellCb, ueCfg->ueSCellCfgInfo.ueSCellCfg[idx].sCellId);
      if (emmCellCb == NULLP)
      {
         RLOG_ARG0(L_ERROR,DBG_CELLID,cellId,"Cell Cb Not found");
         RETVALUE(RFAILED);
      }
      ueCfg->ueSCellCfgInfo.ueSCellCfg[idx].macInst = 
                                  emmCellCb->schdCfg.genCfg.macInst;
      /* Fill the SAP IDs for MAC to RLC */
      wrFillRlcMacSaps(&ueCfg->ueSCellCfgInfo.ueSCellCfg[idx], 
              sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellId);
      RLOG2(L_ALWAYS, "Filling Secondary CellId[%d] for UeId[%d] to Configure at MAC", 
                                   sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellId, 
                                   transCb->ueCb->ueIdx);
   }
   
   RETVALUE(ROK);
}/* wrUmmSCellFillRrcCfg */

/** @brief This function is responsible for preparing the sending the RRC
 *         reconfiguration message. The lower layer configurations are also 
 *         filled here.
 *
 * @details
 *
 *     Function: wrUmmSCellUpdPrepRrcMsgAndCfg
 *
 *         Processing steps:
 *         - allocate a new RRC data request event,
 *         - fill the RRC interface header
 *         - get a new free tranaction for the reconfiguration message
 *         - invoke wrUmmRrcCreateRrcReconfigMsg, to create a new 
 *           reconfiguration message
 *         - invoke wrUmmRrcPrepRadioResourceDed, to prepare the Radio
 *           Resource Dedicated IE
 *         - invoke wrUmmInitCtxtRrcReconfigAddSrb, to fill the DRB
 *           information to the ASN IE
 *         - for every RAB that is admitted,
 *           - invoke wrUmmInitCtxtRrcReconfigAddDrb, to fill the DRB 
 *             information to the ASN IE
 *         - for every RAB that is admitted,
 *           - copy the dedicated NAS information to the ASN IE
 *         - invoke wrUmmInitCtxtFillRrcCfg to fill the lower layer 
 *           configuration for the DRB(s)
 *         - send the event to RRC
 *
 * @param[in, out] transCb : transaction information 
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 wrUmmSCellUpdPrepRrcMsgAndCfg
(
WrUmmTransCb                 *transCb
)
{
   NhuDatReqSdus                   *recfgMsg;
   WrUeCb                          *ueCb = transCb->ueCb;
   NhuDL_DCCH_Msg                  *dcchMsg;
   NhuRRCConRecfgn                 *rrcConReCfg;
   NhuRRCConRecfgn_r8_IEs          *recfgIEs;
   U8                              transId;
   WrUmmSCellTransCb               *sCellTransCb = &(transCb->u.sCellTransCb);
   U16                             addSCells = 0;
   U16                             relSCells = 0;
   U16                             tempAddCells = 0;
   U16                             tempRelCells = 0;
   NhuSCellToRlsLst_r10            *sCellToRlsLst_r10 = NULLP;
   NhuSCellToAddModLst_r10         *sCellToAddModLst_r10 = NULLP;
   U32                             idx =0;
   NhuRadioResourceConfigDedicated           *rrcCfgDed;
	NhuCQI_ReportConfig_r10         *cqiReportConfigR10 = NULLP;
   WrCqiRptCfg                     *cqiRptCfg = &(ueCb->cqiRptCfg);
   S16                             ret = ROK;

   TRC2(wrUmmSCellUpdPrepRrcMsgAndCfg)
   WR_ALLOCEVNT(&recfgMsg, sizeof(NhuDatReqSdus));
   if (recfgMsg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   recfgMsg->hdr.cellId  = ueCb->cellId;
   recfgMsg->hdr.ueId    = ueCb->crnti;
   recfgMsg->hdr.transId = transCb->transId | C1_RRCCONRECFGN;

   /* Fix for ccpu00126824:if wrUmmGetRrcTransId fails, recfgMsg is freed*/
   /* Fetch an RRC transaction id for this procedure.                     */
   /* Create the reconfiguration message which is constructued excluding  */
   /* the actual procedure related details which will be added further    */
   if ((wrUmmGetRrcTransId(ueCb, C1_RRCCONRECFGN, 
               WR_GET_TRANS_FRM_TRANSID(transCb->transId), 
               &transId) != ROK) ||
         ((0 == sCellTransCb->numSCells)) ||
         (wrUmmRrcCreateRrcReconfigMsg(recfgMsg, transId) != ROK) )
   {

      RLOG_ARG0(L_ERROR, DBG_CRNTI,ueCb->crnti,
            "wrUmmRrcCreateRrcReconfigMsg failed");
      RETVALUE(RFAILED);
   }

   /* Prepare the radio resources to exclude all the IEs present in the   */
   /* the IE. Those IEs are filled subsequently                           */
   dcchMsg     = &(recfgMsg->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);
   rrcConReCfg = &(dcchMsg->message.val.c1.val.rrcConRecfgn);
   recfgIEs    = &(rrcConReCfg->criticalExtns.val.c1.val.rrcConRecfgn_r8);
   recfgIEs->pres.pres                                 = PRSNT_NODEF;

   rrcCfgDed   = &(recfgIEs->radioResourceConfigDedicated);

   WR_FILL_TKN_UINT(rrcCfgDed->pres,PRSNT_NODEF);


   wrFillTknU8(&rrcCfgDed->mac_MainConfig.choice, MAC_MAINCONFIG_EXPLICITVALUE);
   wrFillTknU8(&(rrcCfgDed->mac_MainConfig.val.explicitValue.pres), PRSNT_NODEF);
   wrFillTknU32(&(rrcCfgDed->mac_MainConfig.val.explicitValue.timeAlignmentTimerDedicated),7 );

   wrFillTknU8(&(rrcCfgDed->mac_MainConfig.val.explicitValue.extaddgrp_2.pres),PRSNT_NODEF);
   wrFillTknU8(&(rrcCfgDed->mac_MainConfig.val.explicitValue.extaddgrp_2.mac_MainConfig_v1020.pres),PRSNT_NODEF);


   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.pres,PRSNT_NODEF);

   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pres,PRSNT_NODEF);

   cqiReportConfigR10 = &(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10);


   WR_FILL_TKN_UINT(cqiReportConfigR10->pres, PRSNT_NODEF);

   WR_FILL_TKN_UINT(cqiReportConfigR10->nomPDSCH_RS_EPRE_Offset, \
         cqiRptCfg->nomPdschRsEpreOff);

   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.choice, \
         CQI_REPORTPERIODIC_SETUP);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.pres, PRSNT_NODEF);
   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.cqi_PUCCH_ResourceIdx_r10, \
         cqiRptCfg->cqiPucchRsrcIdx);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.cqi_pmi_ConfigIdx, \
         cqiRptCfg->cqipmiCfgIdx);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup. \
         cqi_FormatIndicatorPeriodic_r10.choice, 
         CQI_FORMATINDICATORPERIODIC_WIDEBANDCQI);

   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup. \
         cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.pres, 
         PRSNT_NODEF);					

   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.simultaneousAckNackAndCQI, \
         cqiRptCfg->simulAckNackAndCQI);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.ri_ConfigIdx, \
         cqiRptCfg->riCfgIdx);

   if(ueCb->pucchCfgDedPres == TRUE)
   {
   //NAVEEN : removal of duplicate filling by adding New Fun
      wrUmmFillN1PucchRes(ueCb, recfgMsg, rrcCfgDed);
   }

   recfgIEs->nonCriticalExtn.pres.pres                 = PRSNT_NODEF;
   recfgIEs->nonCriticalExtn.nonCriticalExtn.pres.pres = PRSNT_NODEF;
   recfgIEs->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres.pres = PRSNT_NODEF;
   recfgIEs->nonCriticalExtn.nonCriticalExtn.otherConfig_r9.pres.pres  = NOTPRSNT;
   recfgIEs->nonCriticalExtn.nonCriticalExtn.fullConfig_r9.pres        = NOTPRSNT;
   recfgIEs->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres.pres = PRSNT_NODEF;
   sCellToRlsLst_r10 = &(recfgIEs->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.sCellToRlsLst_r10);
   sCellToAddModLst_r10 = &(recfgIEs->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.sCellToAddModLst_r10);

   for (idx = 0; idx< sCellTransCb->numSCells; idx++)
   {
      if ((sCellTransCb->sCellTransInfo[idx].action == WR_UMM_SCELL_ADD) ||
            (sCellTransCb->sCellTransInfo[idx].action == WR_UMM_SCELL_MOD_DEDICATED))
      {
         addSCells++;
      }
      else
      {
         relSCells++;
      }
   }

   if (relSCells > 0)
   {
      WR_GET_MEM((&recfgMsg->memCp), (sizeof(NhuSCellIdx_r10) * relSCells), 
            &(sCellToRlsLst_r10->member));	
      wrFillTknU16(&sCellToRlsLst_r10->noComp, relSCells);
   }

   if (addSCells > 0)
   {
      WR_GET_MEM((&recfgMsg->memCp), (sizeof(NhuSCellToAddMod_r10) * addSCells),
            &(sCellToAddModLst_r10->member));	
      wrFillTknU16(&sCellToAddModLst_r10->noComp, addSCells);
   }

   for (idx = 0; idx< sCellTransCb->numSCells; idx++)
   {
      if ((sCellTransCb->sCellTransInfo[idx].action == WR_UMM_SCELL_ADD) ||
            (sCellTransCb->sCellTransInfo[idx].action == WR_UMM_SCELL_MOD_DEDICATED))
      {			
         NhuSCellToAddMod_r10 *member = &sCellToAddModLst_r10->member[tempAddCells];
         if (ROK != wrUtlFillAddModSCell(member, 
                  sCellTransCb->sCellTransInfo[idx].sCellInfo, ueCb, recfgMsg))
         {	
            /*To-do FREE memory created in case of failure*/
            RLOG0(L_ERROR, "wrUtlFillAddModSCell failed");
            RETVALUE(RFAILED);
         }
         tempAddCells++;
      }
      else
      {
         wrFillTknU32(&sCellToRlsLst_r10->member[tempRelCells], 
               (U32)sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellIdx);
         tempRelCells++;
      }
   }
   if(ueCb->cqiRptCfg.aperCqiEnbld)
   {
      /*When you uncommnet here, also uncomment wrAcValAperCSITgr in wrac_nhuhdl.c*/
      if(tempAddCells > 0)
      {
         recfgIEs->radioResourceConfigDedicated.pres.pres = PRSNT_NODEF;
         recfgIEs->radioResourceConfigDedicated.physicalConfigDedicated.pres.pres = PRSNT_NODEF;
         recfgIEs->radioResourceConfigDedicated.physicalConfigDedicated.extaddgrp_2.pres.pres = PRSNT_NODEF;
         recfgIEs->radioResourceConfigDedicated.physicalConfigDedicated.extaddgrp_2. \
            cqi_ReportConfig_r10.pres.pres = PRSNT_NODEF;

         NhuCQI_ReportAperiodic_r10 *cqi_RptAper_r10 = &recfgIEs->radioResourceConfigDedicated. \
                                                       physicalConfigDedicated.extaddgrp_2. \
                                                       cqi_ReportConfig_r10.cqi_ReportAperiodic_r10;
         wrFillTknU8 (&(cqi_RptAper_r10->choice),CQI_REPORTAPERIODIC_R10_SETUP);
         wrFillTknU8(&(cqi_RptAper_r10->val.setup.pres),PRSNT_NODEF);
         wrFillTknU32(&(cqi_RptAper_r10->val.setup.cqi_ReportModeAperiodic_r10), \
               ueCb->cqiRptCfg.cqiAperiodicMode); 
         wrFillTknU8(&(cqi_RptAper_r10->val.setup.aperiodicCSI_Trigger_r10.pres),PRSNT_NODEF);
         TknStrBSXL *trigger1_10 = &cqi_RptAper_r10->val.setup.aperiodicCSI_Trigger_r10.trigger1_r10;
         TknStrBSXL *trigger2_10 = &cqi_RptAper_r10->val.setup.aperiodicCSI_Trigger_r10.trigger2_r10;
         wrFillTknStrBSXL(trigger1_10,8,(Data *)&ueCb->apcsiTrigSet1,(&recfgMsg->memCp));
         wrFillTknStrBSXL(trigger2_10,8,(Data *)&ueCb->apcsiTrigSet2,(&recfgMsg->memCp));
         wrFillTknS32(&(recfgIEs->radioResourceConfigDedicated.physicalConfigDedicated. \
                  extaddgrp_2.cqi_ReportConfig_r10.nomPDSCH_RS_EPRE_Offset),ueCb->cqiRptCfg.nomPdschRsEpreOff);
      }
   }
   /* Build the configuration towards RRC                                 */
   if(WR_UMM_SCELL_ADD == sCellTransCb->triggerTyp)
   {
      if(ROK != wrUmmSCellFillRrcCfg(transCb, recfgMsg))
      {
         RLOG0(L_ERROR, "wrUmmSCellFillRrcCfg failed.");
         RETVALUE(RFAILED);
      }
   }
   if (RFAILED == wrIfmRrcSndReqToUe(recfgMsg))
   {
      RLOG0(L_ERROR, "wrIfmRrcSndReqToUe failed.");
      RETVALUE(RFAILED);
   }
   if(RFAILED == ret)
   {
      WR_FREEEVNT(recfgMsg);
   }
   RETVALUE(ret);
}
/*CA_DEV*/

/** @brief This function performs the SCell Release configuration
 *         towards MAC Scheduler.
 *
 * @details
 * Invoked by - wrUmmSendSCellRelToSch
 *     Function:
 *
 *         Processing steps:
 *         - Builds the SCell Release configuration for a UE.
 *         - Delivers the PDU towards MAC Scheduler through
 *           IFM module.
 *
 * @param WgrCfgReqInfo *cfgReq,
 * @param WrUmmTransCb  *transCb
 * @return ROK/RFAILED
 */

PRIVATE S16 wrUmmSendSCellRelToSch
(
   RgrCfgReqInfo             *cfgReq,
   WrUmmTransCb              *transCb
)
{
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   WrUeCb                    *ueCb = transCb->ueCb;
   WrSCellInfo               *sCellInfo;
   U8                        idx = 0;
   
   struct rgrUeScellRel *ueScellRelCfg = NULLP;
   cfgReq->action = RGR_DELETE;
   cfgReq->u.delInfo.delType = RGR_SCELL_UE_CFG;
   ueScellRelCfg = &cfgReq->u.delInfo.u.ueScellRel;
   ueScellRelCfg->cellId = ueCb->cellId;
   ueScellRelCfg->crnti = ueCb->crnti;
   ueScellRelCfg->ueDelTypes        = RGR_UE_SCELL_DEL_RECFG; 
   ueScellRelCfg->ueSCellRelCfgInfo.numSCells = sCellTransCb->numSCells;

   for(idx = 0; idx < sCellTransCb->numSCells; idx++)
   {
      sCellInfo   = sCellTransCb->sCellTransInfo[idx].sCellInfo;

      ueScellRelCfg->ueSCellRelCfgInfo.ueSCellRelDedCfg[idx].sCellIdx = \
                                                                        sCellInfo->sCellIdx;
      ueScellRelCfg->ueSCellRelCfgInfo.ueSCellRelDedCfg[idx].sCellId = \
                                                                       sCellInfo->sCellId;
   }
   RLOG0(L_ALWAYS, "Send SCell Delete to SCH");
   RETVALUE(ROK);
}

/** @brief This function will start the rollback functionality
 *  in case of failure during SCellAdd
 * @details
 *
 *     Function: wrUmmSCellInfoRollBack
 *
 *         Processing steps:
 *         Build RRM msg with action as SCell Release
 *
 * @param [in] WrUmmTransCb                *transCb
 * @param [in] WrUmmRollBackState           nextState
 * @return S16
 -# Success : ROK
 -# Failure : RFAILED 
 */ 
PRIVATE S16 wrUmmSCellInfoRollBack
(
 WrUmmTransCb                *transCb,
 WrUmmRollBackState          nextState
 )
{  
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   WrUeCb                    *ueCb = transCb->ueCb;
   S16                       ret = RFAILED;

      RmuUeRecfgReq         *rmuUeReCfg;
      RmuUeScellInfoReq     *rmuSCellInfoReq;
      U32                   idx;

      switch(sCellTransCb->rollBackState)
      {
         case WR_UMM_SCELL_ROLLBACK_INVALID:
            {
               if(WR_UMM_SCELL_ADD == sCellTransCb->triggerTyp)
               {
                  for(idx=0; idx < sCellTransCb->numSCells; idx++)
                  {
                     /*Validate the internal message. If it fails then return from here and 
                      * close the transaction */
                     if(transCb->ueCb->sCellInfo[sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellIdx -1] == NULLP)
                     {
                        RLOG1(L_ERROR, " Invalid SCell(%d) received in Release request",
                              sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellIdx);
                        RETVALUE(RFAILED);
                     }
                  }
                  WR_ALLOC(&rmuUeReCfg, sizeof(RmuCommonMsg));

                  RLOG0(L_ALWAYS, "wrUmmSCellPrcIntMsg ");

                  if(NULLP == rmuUeReCfg)
                  {
                     RLOG0(L_FATAL, "Failed to allocate Memory.");
                     RETVALUE(RFAILED);
                  }
                  rmuSCellInfoReq = &rmuUeReCfg->stSCellInfoReq;

                  rmuUeReCfg->bCellId = ueCb->cellId;
                  rmuUeReCfg->usCrnti = ueCb->crnti;
                  rmuUeReCfg->uiTransId = transCb->transId;
                  rmuUeReCfg->bRecfgBitMap |= RMU_RECFG_REQ_SCELL_CONFIG;

                  for(idx=0; idx< sCellTransCb->numSCells; idx++)
                  {
                     WrSCellTransInfo      *sCellTransInfo = &sCellTransCb->sCellTransInfo[idx];

                     WR_ALLOC(&sCellTransInfo->sCellInfo, sizeof(WrSCellInfo));
                     if(NULLP == sCellTransInfo->sCellInfo)
                     {
                        /*Free all pre-allocated memory for SCell */
                        wrUmmSCellTransInfoFree(ueCb, sCellTransCb, idx);
                        RLOG0(L_FATAL, "Failed to allocate Memory.");
                        RETVALUE(RFAILED);
                     }
                     sCellTransInfo->action                   = WR_UMM_SCELL_RELEASE;
                     rmuSCellInfoReq->sCellIInfo[idx].action  = WR_UMM_SCELL_RELEASE;
                     rmuSCellInfoReq->sCellIInfo[idx].sCellId = sCellTransInfo->sCellInfo->sCellId;
                     rmuSCellInfoReq->sCellIInfo[idx].sCellIdx= sCellTransInfo->sCellInfo->sCellIdx;
                  }
                  sCellTransCb->triggerTyp = WR_UMM_SCELL_RELEASE;
                  sCellTransCb->rollBackState = nextState;
                  if (idx)
                  {
                     RLOG1(L_ALWAYS, "Sending RRM UE Recfg for [%d] Of SCells", idx);
                     rmuSCellInfoReq->numOfScell = idx;
                     sCellTransCb->numSCells = idx;
                     ret = wrIfmRrmSndUeRecfgReq(rmuUeReCfg);
                  }
               }
            }
            break;
         case WR_UMM_SCELL_ROLLBACK_RRM_INFO: 
         case WR_UMM_SCELL_ROLLBACK_RRM_CTF_INFO: 
         case WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO:
            {
               wrUmmSCellTransInfoFree(ueCb, sCellTransCb, sCellTransCb->numSCells);
               ret = RFAILED;
            }
            break;
      }
   RETVALUE(ret);
}
/** @brief This function is called to handle Scheduler
 *         config confirmation for secondary cells.
 *
 * @details
 *     Function:  wrUmmSCellPrcSchCfgCfm
 *
 *         Processing steps:
 *         - Performs the validation of Scheduler config
 *           confirm whether it is success or failure.
 *
 *
 * @param WrUmmTransCb *transCb
 * @return ROK/RFAILED
 */

PRIVATE S16 wrUmmSCellPrcSchCfgCfm
(
WrUmmTransCb                 *transCb
)
{
   WrUeCb                    *ueCb = transCb->ueCb;
   WrUmmSchdCfgCfm           *schdCfm;
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   S16                       ret       = ROK;
   U16                       bitMask   = 0;

   TRC2(wrUmmSCellPrcSchCfgCfm)

   schdCfm       = &transCb->msg->u.schdCfm;
   
   if (schdCfm->status == RGR_CFG_CFM_OK)
   {
      if(WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO == sCellTransCb->rollBackState)
      {
         /* Reaching here means:
          * RRM,CTF and SCH info had to be reverted, which is successfull now
          * */
         ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO);
      }
      else
      {
         bitMask = ((schdCfm->transId) & 0x0f);
         if(bitMask == WR_UMM_SCH_TRANS_SCELL_READY)
         {
            RLOG2(L_ALWAYS, "SCELL [%u] is ready for Activation for UeId [%u]", 
                  transCb->ueCb->cellId, transCb->ueCb->ueIdx);
            /*NOTE: please check TransComplete if handling for Further Actions*/
            wrUmmTransComplete(transCb);
         }
         else if((bitMask == WR_UMM_SCH_TRANS_SCELL_ADD)||
               (bitMask == WR_UMM_SCH_TRANS_SCELL_RELEASE))
         {
            /*ELSE part is for sending RRC Reconfig for SCELL Add */
            ret = wrUmmSCellUpdPrepRrcMsgAndCfg(transCb);
            if(ret == ROK)
            {
               wrStartTransTmr(transCb,WR_TMR_RECONFIGURE, 
                     wrEmmGetRrcReCfgTmrVal(ueCb->cellId));
            }
            else
            {
               RLOG0(L_ERROR, "SCell Re-Cfg message sending Failure");
               ret = RFAILED;
            }
         }
         else
         {
            RLOG0(L_ERROR, "Scheduler Config Confirm received for Invalid transId");
            ret = RFAILED;
         }
      }
   }
   else
   {
      RLOG0(L_ERROR, "SCell Configuration failure received from Scheduler");
      if (WR_UMM_SCELL_RELEASE == sCellTransCb->triggerTyp) 
      {
         ret = wrUmmSCellUpdPrepRrcMsgAndCfg(transCb);
         if(ret == ROK)
         {
            wrStartTransTmr(transCb,WR_TMR_RECONFIGURE, 
                  wrEmmGetRrcReCfgTmrVal(ueCb->cellId));
         }
         else
         {
            RLOG0(L_ERROR, "SCell Re-Cfg message sending Failure");
            ret = RFAILED;
         }
      }
      else
      {
         /* Reaching here means:
          * RRM and CTF info has to be reverted in SCell Add case 
          * */
         ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_CTF_INFO);                           
      }
   }
   RETVALUE(ret);
}

/** @brief This function performs the SCell ADD configuration
 *         towards MAC Scheduler.
 *
 * @details
 * Invoked by - wrUmmSendSCellAddToSch
 *     Function:
 *
 *         Processing steps:
 *         - Builds the SCell Add configuration for a UE.
 *         - Delivers the PDU towards MAC Scheduler through
 *           IFM module.
 *
 *
 * @param RgrCfgReqInfo *cfgReq,
 * @param WrUmmTransCb  *transCb
 * @return ROK/RFAILED
 */

PRIVATE S16 wrUmmSendSCellAddToSch
(
   RgrCfgReqInfo             *cfgReq,
   WrUmmTransCb              *transCb
)
{
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   WrUeCb                    *ueCb = transCb->ueCb;
   WrSCellInfo               *sCellInfo;
   RgrUeDlCqiCfg             *dlCqiCfg;
   WrCellCb                  *emmCellCb = NULLP;
   RgrUeRecfg                *ueRecfg;
   U8                        idx = 0;
   U32                       actTmr = 0;
   RgrUeSecCellCfg        *ueSCellDedCfg = NULLP;
   U8                        triggerSet1 = 0;
   U8                        triggerSet2 = 0;

   cfgReq->action                = RGR_RECONFIG;
   cfgReq->u.recfgInfo.recfgType = RGR_UE_CFG;

   ueRecfg                       = &cfgReq->u.recfgInfo.u.ueRecfg;
   ueRecfg->cellId               = ueCb->cellId;
   ueRecfg->oldCrnti             = ueCb->crnti;
   ueRecfg->newCrnti             = ueCb->crnti;

   ueRecfg->ueRecfgTypes        = RGR_UE_SCELL_ADD_RECFG; 
   ueRecfg->ueSCellCfgInfo.numSCells = sCellTransCb->numSCells;
   
   wrUmmSCellFillAperCsiTgr(ueCb,&triggerSet1,&triggerSet2);
   ueRecfg->aprdDlCqiRecfg.triggerSet1 = triggerSet1;
   ueRecfg->aprdDlCqiRecfg.triggerSet2 = triggerSet2;

   ueCb->apcsiTrigSet1 = triggerSet1;
   ueCb->apcsiTrigSet2 = triggerSet2;

   for(idx = 0; idx < sCellTransCb->numSCells; idx++)
   {
      sCellInfo   = sCellTransCb->sCellTransInfo[idx].sCellInfo;
   
      sCellInfo->cqiRptCfg.aCqiTriggerSet1 = triggerSet1;
      sCellInfo->cqiRptCfg.aCqiTriggerSet2 = triggerSet2;

      ueRecfg->ueSCellCfgInfo.ueSCellDedCfg[idx].sCellIdx = sCellInfo->sCellIdx;
      ueRecfg->ueSCellCfgInfo.ueSCellDedCfg[idx].sCellId = sCellInfo->sCellId;
      WR_EMM_GET_CELLCB(emmCellCb, sCellInfo->sCellId);
      if(NULLP == emmCellCb)
      {
         RLOG_ARG0(L_ERROR,DBG_CELLID, sCellInfo->sCellId, "Cell Cb Not found");
         RETVALUE(RFAILED);
      }
      if(PRSNT_NODEF == emmCellCb->sCellDeActTmr.pres)
      {
         if(wrUtlGetSCellDeActTmrVal(emmCellCb->sCellDeActTmr.val, &actTmr))
         {
            wrFillTknU32(&ueRecfg->ueSCellCfgInfo.ueSCellDedCfg[idx].sCellDeActTmr, actTmr);
         }
      }

      dlCqiCfg    = &ueRecfg->ueSCellCfgInfo.ueSCellDedCfg[idx].ueSCellDlCqiCfg;

      ueSCellDedCfg = &ueRecfg->ueSCellCfgInfo.ueSCellDedCfg[idx];
#ifdef TFU_UPGRADE
      /* PDSCH related dedicated configuration */
      ueSCellDedCfg->uePdschDedCfg.uepACfg.pA = ueCb->pdschDedCfg.p_a;
      ueSCellDedCfg->uePdschDedCfg.uepACfg.pAPrsnt = 1;
#endif
      /* Fill TX mode for each secondary cell configured */
      wrUmmFillSchdUeTxMode(ueCb, ueRecfg, ueSCellDedCfg, sCellInfo->sCellId);
      wrUmmSchFillRgrUeDlCqiCfg(dlCqiCfg,&sCellInfo->cqiRptCfg, 0, WR_UE_RADIO_RES_CFG_CQI);
   }

   ueRecfg->ueSCellCfgInfo.useExtBSRSizes = FALSE;
   
   RETVALUE(ROK);
}


/** @brief This function performs the SCell configuration
 *         towards MAC Scheduler.
 *
 * @details
 * Invoked by - wrUmmSCellSchdCfg
 *     Function:
 *
 *         Processing steps:
 *         - Builds the SCell configuration for a UE.
 *         - Delivers the PDU towards MAC Scheduler through
 *           IFM module.
 *
 *
 * @param WrUmmTransCb  *transCb
 * @return ROK/RFAILED
 */

PRIVATE S16 wrUmmSCellPrcPhyCfgCfm
(
WrUmmTransCb                 *transCb
)
{
   WrUeCb                    *ueCb = transCb->ueCb;
   RgrCfgReqInfo             *cfgReq = NULLP;
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   WrUmmPhyCfgCfm            *phyCfm;
   U32                       transId = 0;
   S16                       ret = RFAILED;

   /*Get the PHY CFM Message*/
   phyCfm = &transCb->msg->u.phyCfm;
   if (phyCfm->status == CTF_CFG_CFM_OK)
   {
      if(WR_UMM_SCELL_ROLLBACK_RRM_CTF_INFO == sCellTransCb->rollBackState)
      {
         /* Reaching here means:
          * Both RRM and CTF info had to be reverted, which is successfull now
          * */
         ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_CTF_INFO);
      }
      else
      {
         WR_ALLOC(&cfgReq, sizeof(RgrCfgReqInfo));
         if (cfgReq == NULLP)
         {
            RETVALUE(ret);
         }
         if(WR_UMM_SCELL_ADD == sCellTransCb->triggerTyp)
         {
            if(ROK != wrUmmSendSCellAddToSch(cfgReq,transCb))
            {
                  RETVALUE(ret);
            }
            RLOG0(L_ALWAYS, "Send SCell Config to SCH");
            /* Dispatch the prepared message to scheduler */
            transId = transCb->transId | WR_UMM_SCH_TRANS_SCELL_ADD;
         }
         else if(WR_UMM_SCELL_RELEASE == sCellTransCb->triggerTyp)
         {
            if(ROK != wrUmmSendSCellRelToSch(cfgReq,transCb))
            {
               RETVALUE(ret);
            }
            transId = transCb->transId | WR_UMM_SCH_TRANS_SCELL_RELEASE;
         }
         else
         {
            RLOG0(L_ERROR, "wrUmmSCellPrcPhyCfgCfm:INVALID TRIGGER type\n");
         }
         WrIfmSchdCfgUe(cfgReq, transId , ueCb->cellId);
         ret = ROK;
      }
   }
   else
   {
      RLOG0(L_ERROR, "SCell Configuration failure at CL");
      /*Reaching here means: 
       * 1. RRM Roll back was successfull but CTF rollback failed
       *    during SCell Add, but since rollback at SCH is also required, 
       *    we forcefully trigger it
       *    rollBackState = WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO
       * 2. Failure at CTF during Normal SCell Release, 
       *    yet trigger SCell Release at SCH
       *    rollBackState = WR_UMM_SCELL_ROLLBACK_INVALID
       *    OR
       * 3. Failure at CTF during Normal SCell Add,
       *    trigger RRM Cleanup
       *    rollBackState = WR_UMM_SCELL_ROLLBACK_INVALID
       *    OR
       *    */
      if((WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO == sCellTransCb->rollBackState)
         || ((WR_UMM_SCELL_ROLLBACK_INVALID == sCellTransCb->rollBackState) 
            && (WR_UMM_SCELL_RELEASE == sCellTransCb->triggerTyp)))
      {
         WR_ALLOC(&cfgReq, sizeof(RgrCfgReqInfo));
         if (cfgReq == NULLP)
         {
            RETVALUE(RFAILED);
         }
         if(ROK != wrUmmSendSCellRelToSch(cfgReq,transCb))
         {
            RETVALUE(RFAILED);
         }
         transId = transCb->transId | WR_UMM_SCH_TRANS_SCELL_RELEASE;
         WrIfmSchdCfgUe(cfgReq, transId , ueCb->cellId);
         ret = ROK;
      }
      else
      {
         ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_INFO);
      }
   }
   RETVALUE(ret);
} /* End of wrUmmSCellPrcPhyCfgCfm */

/** @brief This function performs UE Configuration
 *         towards convergence Layer.
 *
 * @details
 *     Function: wrUmmSCellPhyUeCfg
 *
 *         Processing steps:
 *
 *         - Fills SCell configuration parameters for PHY layer.
 *         - Sends the Config parameters to interface module
 *           of Phyisical layer.
 *
 *
 * @param WrUmmTransCb  *transCb
 *
 * @return ROK/RFAILED
 */

PRIVATE S16 wrUmmSCellPhyUeCfg
(
 WrUmmTransCb                 *transCb
 )
{
   CtfCfgReqInfo             *cfgInfo;
   WrUmmSCellTransCb         *sCellTransCb = &transCb->u.sCellTransCb;
   U32                       idx;


   WR_ALLOC(&cfgInfo, sizeof(CtfCfgReqInfo));
   if (cfgInfo == NULLP)
   {
      RLOG0(L_FATAL, "Failed to allocate memory.");
      RETVALUE(RFAILED);
   }
   if(WR_UMM_SCELL_ADD == sCellTransCb->triggerTyp)
   {
      CtfDedRecfgInfo           *ueReCfgParam = NULLP;
      cfgInfo->cfgType = CTF_RECONFIG;
      cfgInfo->u.reCfg.cfgElem = CTF_UE_CFG;
      ueReCfgParam = &cfgInfo->u.reCfg.u.dedRecfg;
      ueReCfgParam->cellId = transCb->ueCb->cellId;
      ueReCfgParam->ueId = transCb->ueCb->crnti;
      ueReCfgParam->newUeId = transCb->ueCb->crnti;
#ifdef CA_DBG
      printf("SCEll Addition Trigger crnti =%d, cellId = %d numScells =%d\n", transCb->ueCb->crnti, transCb->ueCb->cellId, sCellTransCb->numSCells);
#endif      
      ueReCfgParam->sCellInfo.sCellAction = CTF_SCELL_ADD;
      for(idx=0; idx < sCellTransCb->numSCells; idx++)
      {
         if(sCellTransCb->sCellTransInfo[idx].sCellInfo != NULLP)
         {
            ueReCfgParam->sCellInfo.ueSCellDedCfg[idx].sCellId = \
                                   sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellId;
            ueReCfgParam->sCellInfo.ueSCellDedCfg[idx].sCellIdx = \
                                   sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellIdx;
         }
      }
      ueReCfgParam->sCellInfo.numSCells = sCellTransCb->numSCells;
      RLOG0(L_ALWAYS, "Sending Scell Phy UE Cfg");
   }
   else if (WR_UMM_SCELL_RELEASE == sCellTransCb->triggerTyp)
   {
      CtfDedReleaseInfo         *ueRelParam = NULLP;
      cfgInfo->cfgType = CTF_DELETE;
      cfgInfo->u.release.cfgElem = CTF_UE_CFG;
      ueRelParam = &cfgInfo->u.release.u.dedRel; 
      ueRelParam->cellId = transCb->ueCb->cellId;
      ueRelParam->ueId = transCb->ueCb->crnti;
#ifdef CA_DBG
      printf("SCell RElease transCb->ueCb->crnti =%d, ransCb->ueCb->cellId = %d \n", transCb->ueCb->crnti, transCb->ueCb->cellId);
#endif      
      ueRelParam->sCellInfo.sCellAction = CTF_SCELL_RELEASE;
      for(idx=0; idx < sCellTransCb->numSCells; idx++)
      {
         ueRelParam->sCellInfo.ueSCellDedCfg[idx].sCellId = \
                           sCellTransCb->sCellTransInfo[idx].sCellInfo->sCellId;
      }
      ueRelParam->sCellInfo.numSCells = sCellTransCb->numSCells;
      RLOG0(L_ALWAYS, "Sending Scell Phy UE Rel Cfg");
   }
   else
   {
      RLOG0(L_ERROR, "wrUmmSCellPhyUeCfg:INVALID TRIGGER Type");
   }
   if (wrIfmPhyUeCfg(cfgInfo, transCb->transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPhyUeCfg failed.");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of wrUmmSCellPhyUeCfg */ 

/**
 *  @brief This function updates the SCell PHY dedicated info to trans Cb
 *
 *      Function: wrUmmCpySCellDedInfo
 *
 *          Processing steps:
 *          - For all the resource types
 *          - check the resource type is reconfigured
 *          - update the SCell transCb with resource info
 *
 *
 *  @param [in] sCellInfo        : pointer to SCell info in the transCb
 *  @param [in] stPhyCfgDed      : pointer to SCell phy config dedicated info
 *                                 configured by RRM
 *  @return Void
 */
PRIVATE Void wrUmmCpySCellDedInfo
(
 WrSCellInfo       *sCellInfo,
 RmuUeCqiReportCfg	 *stCqiRepCfg
)
{
   TRC2(wrUmmCpySCellDedInfo)
   
   wrUmmCommitUeCqiCfgInfo(&(sCellInfo->cqiRptCfg), stCqiRepCfg, sCellInfo->sCellId);
   sCellInfo->bResCfgBitMap |=WR_UE_RADIO_RES_CFG_CQI;
   RETVOID;
} /* end of wrUmmCpySCellDedInfo */


/**
 *  @brief This function handles confirmation from RRM
 *
 *      Function: wrUmmSCellPrcRrmCfgCfm
 *
 *          Processing steps:
 *          Check for success/Failure from RRM response:
 *             If Success send phy config
 *
 *
 *  @param [in] transCb        : pointer to scell addition transaction CB
 *  @return Void
 */
PRIVATE S16 wrUmmSCellPrcRrmCfgCfm
(
 WrUmmTransCb            *transCb
 )
{
   RmuUeSCellInfoRsp     *rmuSCellRspCfg;
   WrUmmSCellTransCb     *sCellTransCb = &transCb->u.sCellTransCb;
   WrSCellTransInfo      *sCellTransInfo;
   S16                   ret = RFAILED;
   U32                   idx;

   TRC2(wrUmmSCellPrcRrmCfgCfm)

   rmuSCellRspCfg = &transCb->msg->u.rrmUeRecfgResp->stUeSCellResCfg;
   RLOG1(L_ALWAYS, "No Of SCell from RRMCfgCfm = %d", 
                                 rmuSCellRspCfg->numSCells);

   if(transCb->msg->u.rrmUeRecfgResp->stStatusInfo.enStatus 
         == RMU_SUCCESS) 
   {
      if(WR_UMM_SCELL_ROLLBACK_RRM_INFO == (sCellTransCb->rollBackState))
      {
         /* Reaching here means:
          * Only RRM info had to be reverted, which is successfull now
          * */
         ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_INFO);
      }
      else if((WR_UMM_SCELL_ROLLBACK_RRM_CTF_INFO == (sCellTransCb->rollBackState))
            || (WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO == (sCellTransCb->rollBackState)))
      {      
         RLOG0(L_ALWAYS, "Cleanup will happen after Scell Release in CTF/SCH");
         ret = ROK;
      }
      else 
      {
         /* For succesfull response store dedicated information in transCb */
         for(idx=0; idx< rmuSCellRspCfg->numSCells; idx++)
         { 
            sCellTransInfo = &sCellTransCb->sCellTransInfo[idx];
            if((rmuSCellRspCfg->sCellDedInfo[idx].stStatusInfo.enStatus == RMU_SUCCESS) &&
                  (rmuSCellRspCfg->sCellDedInfo[idx].sCellIdx <= WR_MAX_SCELL_PER_UE ))
            {
               wrUmmCpySCellDedInfo(sCellTransInfo->sCellInfo, &rmuSCellRspCfg->sCellDedInfo[idx].stCqiRepCfg);
            }
            else
            {
               /* Since this particular SCell response is FAILED so delete the entry
                * from transCb */
               wrUmmFreeSCellInfoFrmUeCb(transCb->ueCb, sCellTransCb, idx);
            }  

         }
         ret = ROK;
      }
   } 
   else
   {
      /* Reaching here means:
       * 1.RRM Cfg failed during SCell Addition, hence need to notify 
       *   RRM about the same. 
       *   rollBackState = WR_UMM_SCELL_ROLLBACK_INVALID
       * 2.Only RRM Cfg had to be reverted but that too failed
       *   rollBackState = WR_UMM_SCELL_ROLLBACK_RRM_INFO
       * */
      ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_INFO);
      RETVALUE(ret);
      /*Note: For SCell Release there is no direct msg to RRM*/
   }
   /* configure CTF interface with secondary cellId for which RRM has sent
    * positive response */
   if(ROK == ret)
   {
      ret = wrUmmSCellPhyUeCfg(transCb);
   }
   RETVALUE(ret);
}/* End of wrUmmSCellCtfCfg */

/**
 *  @brief This function handles the internal message that triggers Scell
 *  addition transaction
 *
 *      Function: wrUmmSCellPrcIntMsg
 *
 *          Processing steps:
 *          Fetch the list of SCells that can be configured for this UE
 *          Send UE RECFG REQ to RRM
 *
 *
 *  @param [in] ueCb           : pointer to UE control Block
 *  @param [in] transCb        : pointer to scell addition transaction CB
 *  @param [in] sCellIntInfo      : List of SCells that need to be added for this
 *  UE
 *  @return Void
 */
PRIVATE S16 wrUmmSCellPrcIntMsg
(
 WrUeCb                  *ueCb, 
 WrUmmTransCb            *transCb, 
 WrUmmIntSCellTransMsg   *sCellIntInfo
 )
{

   RmuUeRecfgReq         *rmuUeReCfg;
   RmuUeScellInfoReq     *rmuSCellInfoReq;
   WrUmmSCellTransCb     *sCellTransCb = &transCb->u.sCellTransCb;
   S16                   ret = RFAILED;
   U32                   idx;
   U8                    sCellIdx = 0;
   U16                   sCellId = 0; 

   WR_ALLOC(&rmuUeReCfg, sizeof(RmuCommonMsg));

   RLOG0(L_ALWAYS, "wrUmmSCellPrcIntMsg ");

   if(NULLP == rmuUeReCfg)
   {
      RLOG0(L_FATAL, "Failed to allocate Memory.");
      RETVALUE(ret);
   }
   rmuSCellInfoReq = &rmuUeReCfg->stSCellInfoReq;

   rmuUeReCfg->bCellId = ueCb->cellId;
   rmuUeReCfg->usCrnti = ueCb->crnti;
   rmuUeReCfg->uiTransId = transCb->transId;
   rmuUeReCfg->bRecfgBitMap |= RMU_RECFG_REQ_SCELL_CONFIG;


   for(idx=0; idx< sCellIntInfo->numSCells; idx++)
   {
      WrSCellTransInfo      *sCellTransInfo = &sCellTransCb->sCellTransInfo[idx];
      sCellId = sCellIntInfo->sCellUpdtReq[idx].sCellId; 

      /* This function will return first available SCellIdx from UeCb->sCellInfo
       * List */
      ret =  wrUmmGetSCellFreeIndex(ueCb, &sCellIdx, sCellId);
      if(ret == ROK)
      {
         WR_ALLOC(&sCellTransInfo->sCellInfo, sizeof(WrSCellInfo));
         if(NULLP == sCellTransInfo->sCellInfo)
         {
            /*Free all pre-allocated memory for SCell */
            wrUmmSCellTransInfoFree(ueCb, sCellTransCb, idx);
            RLOG0(L_FATAL, "Failed to allocate Memory.");
            RETVALUE(ret);
         }
         sCellTransInfo->sCellInfo->sCellIdx = sCellIdx;
         sCellIntInfo->sCellUpdtReq[idx].sCellIdx = sCellIdx;
         rmuSCellInfoReq->sCellIInfo[idx].action   = sCellIntInfo->sCellUpdtReq[idx].action;
         rmuSCellInfoReq->sCellIInfo[idx].sCellId  = sCellIntInfo->sCellUpdtReq[idx].sCellId;
         rmuSCellInfoReq->sCellIInfo[idx].sCellIdx = sCellTransInfo->sCellInfo->sCellIdx;
         wrUmmSetSCellInfoAtIdx(ueCb, sCellTransInfo->sCellInfo);
      }
      else
      {
         WR_FREE(rmuUeReCfg, sizeof(RmuUeRecfgReq));
         wrUmmSCellTransInfoFree(ueCb, sCellTransCb, idx);
         RLOG0(L_FATAL, "Failed to get Free SCellIdx");
         RETVALUE(ret);
      }
      /* Storing Required data in TransCb */
      sCellTransInfo->action                   = sCellIntInfo->sCellUpdtReq[idx].action;
      sCellTransInfo->sCellInfo->sCellId       = sCellIntInfo->sCellUpdtReq[idx].sCellId;
   }

   if (idx)
   {
      RLOG1(L_ALWAYS, "Sending RRM UE Recfg for [%d] Of SCells", idx);
      rmuSCellInfoReq->numOfScell = idx;
      sCellTransCb->numSCells = idx;
      ret = wrIfmRrmSndUeRecfgReq(rmuUeReCfg);
      RETVALUE(ROK);
   }
   RETVALUE(RFAILED);
}/* End of wrUmmSCellPrcIntMsg */

/**
 *  @brief This function handles the internal message that triggers Scell
 *  Release transaction
 *
 *      Function: wrUmmSCellPrcRelUeCfg
 *
 *          Processing steps:
 *          Fetch the list of SCells that can be configured for this UE
 *          Send UE RECFG REQ to RRM
 *
 *
 *  @param [in] transCb        : pointer to scell addition transaction CB
 *  @param [in] sCellInfo      : List of SCells that need to be added for this
 *  UE
 *  @return Void
 */
PRIVATE S16 wrUmmSCellPrcRelUeCfg
(
 WrUmmTransCb            *transCb, 
 WrUmmIntSCellTransMsg   *sCellInfo
 )
{

   WrUmmSCellTransCb     *sCellTransCb = &transCb->u.sCellTransCb;
   S16                   ret = RFAILED;
   U32                   idx;
   WrSCellTransInfo      *sCellTransInfo = NULLP;


   RLOG0(L_ALWAYS, "wrUmmSCellPrcRelUeCfg");

   for(idx=0; idx < sCellInfo->numSCells; idx++)
   {
      /*Validate the internal message. If it fails then return from here and 
       * close the transaction */
      if(transCb->ueCb->sCellInfo[sCellInfo->sCellUpdtReq[idx].sCellIdx -1] == NULLP)
      {
         RLOG1(L_ERROR, " Invalid SCell(%d) received in DEL request",
               sCellInfo->sCellUpdtReq[idx].sCellIdx);
         RETVALUE(ret);
      }
   }

   for(idx=0; idx < sCellInfo->numSCells; idx++)
   {
         sCellTransInfo = &sCellTransCb->sCellTransInfo[idx];
         WR_ALLOC(&sCellTransInfo->sCellInfo, sizeof(WrSCellInfo));
         if(NULLP == sCellTransInfo->sCellInfo)
         {
            /*Free all pre-allocated memory for SCell */
            RLOG0(L_FATAL, "Failed to allocate Memory.");
            RETVALUE(ret);
         }
         sCellTransInfo->action              = sCellInfo->sCellUpdtReq[idx].action;
         sCellTransInfo->sCellInfo->sCellIdx = sCellInfo->sCellUpdtReq[idx].sCellIdx;
         sCellTransInfo->sCellInfo->sCellId  =  sCellInfo->sCellUpdtReq[idx].sCellId;
   }
   
   if (idx)
   {
      sCellTransCb->numSCells = idx;
      ret = wrUmmSCellPhyUeCfg(transCb);
      RETVALUE(ROK);
   }
   RETVALUE(RFAILED);
}/* End of wrUmmSCellPrcRelUeCfg */

/** @brief This function(transaction) handles all CA related messages.
 *        
 * @details
 *
 * Function:wrUmmSCellProcessor
 *
 *   Processing steps:
 *    List of Messages handled in this transaction
 *         1. WR_UMM_INTERNAL_MSG:
 *         2. WR_UMM_RRM_UERECFG_RESP 
 *         3. WR_UMM_PHY_CFG
 *         4. WR_UMM_SCHD_CFG
 *         5. WR_UMM_UU_IND_PDU
 *         6.    
 *    -Check the message type
 *    
 * @param[in]  transCb: pointer to transaction control block
 * @return S16
 *  -#Success : ROK
 *  -#Failure : RFAILED
 */
PUBLIC S16 wrUmmSCellProcessor
(
 WrUmmTransCb                *transCb
 )
{
   WrUmmIncMsg               *msg          = transCb->msg;
   WrUeCb                    *ueCb         = transCb->ueCb;
   S16                       ret           = RFAILED; 
   WrUmmIntSCellTransMsg     *sCellInfo    = NULLP;

   switch(msg->msgTyp)
   {
      case WR_UMM_INTERNAL_MSG:
         {
            /* Handle Internal message which can come from RRM, PBM or any other
             * blind function */
            /* This function will call RRM to get the dedicated information for
             * all required secondary cells */
            sCellInfo    = msg->u.internalMsg->u.sCellInfo;
            transCb->u.sCellTransCb.triggerTyp = sCellInfo->triggerTyp;
            transCb->u.sCellTransCb.rollBackState = WR_UMM_SCELL_ROLLBACK_INVALID;
            if(WR_UMM_SCELL_ADD == transCb->u.sCellTransCb.triggerTyp)
            {
               ret = wrUmmSCellPrcIntMsg(ueCb, transCb, sCellInfo);
            }
            else
            {
               /*For Scell Release - Sending message to RRM is NOT required*/
               ret = wrUmmSCellPrcRelUeCfg(transCb, sCellInfo);
            }
         }
         break;
      case WR_UMM_RRM_UERECFG_RESP: 
         {
            /* Handle UE Re-cfg response and do following
             * 1. store dedicated information for each secondary cell 
             * 2. Trigger Secondar cell configuration(i.e Only SCellId) towards
             * CL */
            ret = wrUmmSCellPrcRrmCfgCfm(transCb);
         }
         break;
      case WR_UMM_PHY_CFG:
         {
            /*After getting succesful response from CL for all secondary cells, configure
             * Scheduler with each SCells dedicated information */
            ret =  wrUmmSCellPrcPhyCfgCfm(transCb);
         }
         break;
      case WR_UMM_SCHD_CFG:
         {
            /* If success, fill and send RRC Reconfiguration */
            /* In case of failure ROLLBACK */
            ret =  wrUmmSCellPrcSchCfgCfm(transCb);
         }
         break;
      case WR_UMM_UU_IND_PDU:
         {
            /* Handle RRC Re-cfg Complete message here. After this transaction
             * should be closed */
            /* Send the SCell Activation after RRC Reconfig Complt */
            ret = wrUmmSCellPrcRrcMsg(transCb); 
         }
         break;
      case WR_UMM_TMR_EXPIRY:
         {
            RLOG0(L_ALWAYS, "SCell: REconfiguration Timer Expiry\n");
#ifdef UE_REL_DBG
       printf("\n SCell: REconfiguration Timer Expiry \n");
#endif

            transCb->state = WR_UMM_TRANS_RELEASE_CALL;
            ret = ROK;
         }
         break;
      case WR_UMM_RRC_CFG:
         {
            NhuCfgCfmSdus   *nhuCfgCfmSdus = NULLP;
            nhuCfgCfmSdus = transCb->msg->u.rrcCfm;

            RLOG0(L_ALWAYS, "RRC Config Confirm Received");

            if (nhuCfgCfmSdus->sdu.isCfgSuccess == TRUE)
            {
               ret = ROK;
            }
            else
            {
               ret = wrUmmSCellInfoRollBack(transCb,WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO);
            }
         }
         break;
      case WR_UMM_RRC_DAT_CFM:
      {
         /* This does not require any special action. Just ignore it      */
         printf("\n******DAT CFM Received for SCELL Transaction \n"); 
         ret = ROK;
         break;
      }
      default :
         RLOG1(L_ERROR, " Invalid msgType(%d) ", msg->msgTyp);
   }
   if(ret == RFAILED)
   {
      transCb->state = WR_UMM_TRANS_DONE;
   }
   RETVALUE(ROK);
} /* End of wrUmmSCellProcessor */ 

/* Transaction release function to handle default release part */
PUBLIC S16 wrUmmSCellTransRel
(
 WrUmmTransCb                *transCb
)
{
   TRC2(wrUmmSCellTransRel)
   RLOG0(L_INFO," SCell Transaction Released");
   RETVALUE(ROK);
}

/** @brief This function is called when a new Transaction is created for any
 * other procedure. The new transaction is passed to this function and this
 * function determines the next course of action based on the new transaction
 *
 * @details
 *
 *     Function: wrUmmSCellNewTransProcessor
 *
 *         Description:
 *         This function is called when a new Transaction is
 *         created for any other procedure. The new transaction is passed to
 *         this function and this function determines the next course of action
 *         based on the new transaction
 *
 * @param[in]  transCb    : transaction information
 * @param[in]  incTrans   : incoming transaction information
 * @return S16
 *  -#Success : ROK
 *  -#Failure : RFAILED
 */

PUBLIC S16 wrUmmSCellNewTransProcessor
(
 WrUmmTransCb                *transCb,
 WrUmmTransCb                *incTrans
 )
{
   TRC2(wrUmmSCellNewTransProcessor)
      switch(incTrans->transTyp)
      {
         case WR_UMM_RRC_REESTAB_TRANS:
            {
               RETVALUE(WR_UMM_TRANS_DEFER_ONGOING);
            }
         default:
            {
               break;
            }
      }

   RETVALUE(WR_UMM_TRANS_OK);
}

PUBLIC S16 wrUmmCliTriggerScellAction
(
 U8 action
)
{
   WrUeCb      *ueCb = NULLP;
   WrCellId    cellId;
   WrCrnti     crnti;
   WrCellId    sCellId;
   cellId      = wrCliPCellId;
   crnti       = wrCliUeCrnti;
   sCellId     = wrCliSCellId;
   wrUmmGetUeFrmUeCrnti(&ueCb,cellId,crnti);
   WrCellId                  sCellIdLst[WR_MAX_SCELL_PER_UE];
   U8 numOfSCells = 0;
   if(NULLP != ueCb)
   {
      switch(action)
      {
         case WR_UMM_SCH_TRANS_SCELL_RELEASE:
            {
               sCellIdLst[numOfSCells] = sCellId;   
               numOfSCells++;
               wrUmmSCellTrans(ueCb, WR_UMM_SCELL_RELEASE, numOfSCells, sCellIdLst);
            }
            break;
         case WR_UMM_SCH_TRANS_SCELL_ADD:
            {
               wrUmmSCellIntTrans(ueCb,WR_UMM_SCELL_ADD);
            }
            break;
         case WR_UMM_SCH_TRANS_SCELL_ACT:
            {
               wrUmmCliSendSCellSchActDeact(ueCb,0,RGR_SCELL_ACT);
            }
            break;
         case WR_UMM_SCH_TRANS_SCELL_DEACT:
            {
               wrUmmCliSendSCellSchActDeact(ueCb,0,RGR_SCELL_DEACT);
            }
            break;
         default:
            break;
      }
      RETVALUE(ROK);
   }
   RETVALUE(RFAILED);
}
 
/**     Function: wrUmmSCellFillAperCsiTgr
 *     
 *     Description: This function prepares the value of bit strings trigger1 and
 *                  trigger2 based on the which scell has been added. 
 *                  (i.e based on sCellIdx)
 * 
 * @param[in]:  WrUeCb *ueCb        : ue control block
 * @param[out]: U8     *triggerSet1 : parameter to hold the triggerSet1
 *              U8     *triggerSet2 : parameter to hold the triggerSet2
 * @return void
 */
PRIVATE Void wrUmmSCellFillAperCsiTgr
(
 WrUeCb                   *ueCb,
 U8                       *triggerSet1,
 U8                       *triggerSet2
)
{
   U8 idx=0;
   U8 offset=0;

   for(idx = 0 ; idx < WR_MAX_SCELL_PER_UE ; idx++)
   {
      if(ueCb->sCellInfo[idx] != NULLP)
      {
         if(ueCb->sCellInfo[idx]->sCellIdx % 2  == 0)
         {
            offset =  *triggerSet2;
            /* 
             * 36.331:The leftmost bit, bit 0 in the bit string corresponds
             * to the cell with ServCellIndex=0 and bit 1 in the
             * bit string corresponds to the cell with ServCellIndex=1 etc.
             * */

            *triggerSet2 = (WR_UMM_APER_CSI_TGR_MASK << (7 - ueCb->sCellInfo[idx]->sCellIdx)) | offset; 
         }
         else
         {
            offset =  *triggerSet1;
            *triggerSet1 = (WR_UMM_APER_CSI_TGR_MASK << ( 7 - ueCb->sCellInfo[idx]->sCellIdx)) | offset; 
         }
      }
   }
   RETVOID;
}
#endif
