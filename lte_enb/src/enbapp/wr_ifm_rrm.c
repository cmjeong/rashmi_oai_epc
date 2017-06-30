
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_ifm_rrm.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


/* header include files (.h) */
static const char* RLOG_MODULE_NAME="IFM";

static int RLOG_FILE_ID=25;

static int RLOG_MODULE_ID=4;

#include "wr.h"
#include "wr_cmn.h"
#include "wr_ifm_rrm.h"
#include "wr_emm.h"
#include "wr_emm_pbm.h"
#include "wr_emm_cfg.h"
#include "wr_umm.h"
#include "wr_umm_trans.h"
#include "wr_dam.h"
#include "cm_lte.x"
#include "cm_lte_rrm.x"
#include "rmu.x"

EXTERN Void wrDebugShowBaaringPrams(WrSib2AcBarringCfg *sib2DataCall, WrSib2AcBarringCfg *sib2Signalling);
PUBLIC S16 wrUmmReestRrmRntiUpdt(WrUmmTransCb *transCb);
PUBLIC S16 wrUmmFillAndSndRrmUeRecfgReq(WrUmmTransCb *transCb);
/* SPS changes starts */
/* SPS changes ends */

/**************************************************************
   FSM RRM  interface handler functions
***************************************************************/

#ifndef RM_INTF
/* @brief This function is used to send EnodeB configuration/reconfiguration
 * request to RRM layer.
 *
 * @details
 *
 *     Function: wrIfmRrmEnodebCfgReq
 *
 *         Processing steps:
 *         - This function is invoked by EMM module during EnodeB configuration.
 *         - This function is used to send EnodeB configuration/reconfiguration 
 *         request to RRM layer.
 *
 * @param[in] rrmWrEnbCfgReq: Pointer to enb configuration request structure
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmEnodebCfgReq 
(
RrmWrEnbCfgReqInfo            *rrmWrEnbCfgReq
)
{
   S16 ret = RFAILED;
   
   TRC3(wrIfmRrmEnodebCfgReq);
   RETVALUE(ret);
}/* wrIfmRrmEnodebCfgReq */

/** @brief This function is called from RRM to provide FSM with response to Enb
 *         Configuration.
 *
 * @details This function sends the success or failure response to FSM for the
 *          Enb configuration provided by FSM.
 *
 * @param[in] rrmWrEnbCfgResp    :The pointer to Enb configuration response 
 *                                structure.
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */

PUBLIC S16 RmWrEnodebCfgResp
(
RrmWrEnbCfgRespInfo *rrmWrEnbCfgResp
)
{
   TRC3(RmWrEnodebCfgResp);

   WR_FREE (rrmWrEnbCfgResp, sizeof(RrmWrEnbCfgRespInfo));

   RETVALUE(ROK);
}

/* @brief This function is used to send RRM cell configuration/reconfiguration
 * request to RRM layer.
 *
 * @details
 *
 *     Function: wrIfmRrmCellCfgReq
 *
 *         Processing steps:
 *         - This function is invoked by EMM module during cell configuration.
 *         - This function is used to send cell configuration request to RRM
 *           layer.
 *
 * @param[in] rrmWrCellCfgReq:   The pointer to Cell configuration request
 *                               structure
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmCellCfgReq 
(
RrmWrCellCfgReqInfo           *rrmWrCellCfgReq
)
{
   S16 ret = RFAILED;
   
   TRC3(wrIfmRrmCellCfgReq);

   /* Calling RRM function for Cell Cfg for tightly coupled */
   RETVALUE(ret);
} /* wrIfmRrmCellCfgReq */

/** @brief This function is called from RRM to provide FSM with response to Cell
 *         Configuration.
 *
 * @details This function sends the success or failure response to FSM for the
 *          cell configuration provided by FSM.
 *
 * @param[in] rrmWrCellCfgResp      :The pointer to Cell configuration response 
 *                                structure.
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */

PUBLIC S16 RmWrCellCfgResp 
(
RrmWrCellCfgRespInfo *rrmWrCellCfgResp
)
{
   TRC3(RmWrCellCfgResp);

   WR_FREE(rrmWrCellCfgResp, sizeof(RrmWrCellCfgRespInfo));

   RETVALUE(ROK);
}
   
/* @brief This function is used to send cell status indication to RRM layer.
 *
 * @details
 *
 *     Function: wrIfmRrmCellStaInd
 *
 *         Processing steps:
 *         - This function is invoked by EMM module to send cell status
 *         indication to RRM layer.
 *
 * @param[in] rrmWrCellStaInd:   The pointer to status update request 
 *                               structure.
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmCellStaInd 
(
RrmWrCellStaIndInfo           *rrmWrCellStaInd
)
{
   S16 ret = RFAILED;
   
   TRC3(wrIfmRrmCellStaInd);

   /* Calling RRM function for Cell status indication for tightly coupled */
   RETVALUE(ret);
   
} /* wrIfmRrmCellStaInd */

/* @brief This function is used to send UE status indication to RRM layer.
 *
 * @details
 *
 *     Function: wrIfmRrmUeStaInd
 *
 *         Processing steps:
 *         - This function is invoked by UMM module to send UE status
 *         indication to RRM layer.
 *
 * @param[in] rrmWrUeStaInd: The pointer to status update request structure
 * 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmUeStaInd 
(
RrmWrUeStaIndInfo             *rrmWrUeStaInd
)
{
   S16 ret = RFAILED;

   TRC3(wrIfmRrmUeStaInd);

   /* Calling RRM function for UE status indication for tightly coupled */
   RETVALUE(ret);
} /* wrIfmRrmUeStaInd */

/* @brief This function is used to send Enb status indication to RRM layer.
 *
 * @details
 *
 *     Function: wrIfmRrmEnodebStaInd
 *
 *         Processing steps:
 *         - This function is invoked by EMM module to send Enb status
 *         indication to RRM layer.
 *
 * @param[in] rrmWrEnbStaInd: The pointer to status update request structure
 *  
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmEnodebStaInd 
(
RrmWrEnbStaIndInfo            *rrmWrEnbStaInd
)
{
   S16 ret = RFAILED;
   RmuMmeOvldStartInd* rrmWrMmeStartInfo = NULLP;
   RmuMmeOvldStopInd*  rrmWrMmeStopInfo = NULLP;
   
   TRC3(wrIfmRrmEnodebStaInd);

   /* Calling RRM function for Enb status indication */
   if (rrmWrEnbStaInd->mmeStatus.mmeOvldStatus == RRM_WR_MME_OVLD_STOP)
   {
           if(ROK != SGetSBuf(wrCb.rmuSap[0]->pst.region, wrCb.rmuSap[0]->pst.pool, &rrmWrMmeStartInfo, sizeof(RmuCommonMsg)))
           {
              RLOG0(L_FATAL, "Memory allocation failed.Ovld start info");
              WR_FREE(rrmWrEnbStaInd, sizeof(RmuCommonMsg));
              RETVALUE(RFAILED);
           }
      rrmWrMmeStartInfo->enMmeOvldStatus = rrmWrEnbStaInd->mmeStatus.mmeOvldStatus;
      rrmWrMmeStartInfo->usMmeId = rrmWrEnbStaInd->mmeStatus.mmeId;
      ret = WrLiRmuMmeOverloadStartInd(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrMmeStartInfo);
   }
   else
   {
           if(ROK != SGetSBuf(wrCb.rmuSap[0]->pst.region, wrCb.rmuSap[0]->pst.pool, &rrmWrMmeStopInfo, sizeof(RmuCommonMsg)))
           {
              RLOG0(L_FATAL, "Memory allocation failed.for Ovld Stop info");
              WR_FREE(rrmWrEnbStaInd, sizeof(RmuCommonMsg));
              RETVALUE(RFAILED);
           }
      rrmWrMmeStopInfo->usMmeId = rrmWrEnbStaInd->mmeStatus.mmeId;
      ret = WrLiRmuMmeOverloadStopInd(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrMmeStopInfo);
   }
   //ret = WrRmEnodebStaInd(rrmWrEnbStaInd);

   /*WR_FREE(rrmWrEnbStaInd, sizeof(RrmWrEnbStaIndInfo));*/
   
   RETVALUE(ret);
} /* wrIfmRrmEnodebStaInd */
#endif /*RM_INTF*/

PUBLIC S16 wrIfmRrmMmeOvldStartInd
(
RmuMmeOvldStartInd* rrmWrMmeStartInfo
)
{
   S16 ret = RFAILED;
   ret = WrLiRmuMmeOverloadStartInd(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrMmeStartInfo);
   RETVALUE(ret);
}

PUBLIC S16 wrIfmRrmMmeOvldStopInd
(
RmuMmeOvldStopInd*  rrmWrMmeStopInfo
)
{
   S16 ret = RFAILED;
   ret = WrLiRmuMmeOverloadStopInd(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrMmeStopInfo);
   RETVALUE(ret);
}
/* @brief This function is used to process the Cell Reconfiguration Indication
 * recieved from RRM layer. This may change the information like SIB2 info and
 * need to be processed to reflect the changes at FSM and other layers.
 *
 * @details
 *
 *     Function: WrLiRmuCellReCfgInd
 *
 *         Processing steps:
 *
 * @param[in] rrmWrCellRecfgInd: The pointer to Cell reconfiguration structure.
 * 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 WrLiRmuCellRecfgInd
(
Pst *pst,
SuId suId,
RmuCellRecfgInd         *rrmWrCellRecfgInd
)
{
   S16 ret = RFAILED;

   TRC3 (WrLiRmuCellRecfgInd);

   ret = wrEmmProcRmCellRecfgInd (rrmWrCellRecfgInd);

   WR_FREE(rrmWrCellRecfgInd, sizeof(RmuCommonMsg));

   RETVALUE(ret);
} /* WrLiRmuCellReCfgInd */

/* @brief This function is used to process the UE Reconfiguration Indication
 * recieved from RRM layer when the Tranmission Mode change indication triggerd
 * by MAC. This will update information of TxnMode and Reporting Mode of UE by 
 * triggering RRC ReCfg to UE and SCHD.
 *
 * @details
 *
 *     Function: WrLiRmuUeReCfgInd
 *
 *         Processing steps:
 *
 * @param[in] rrmWrUeRecfgInd: The pointer to Ue reconfiguration structure.
 * 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 WrLiRmuUeRecfgInd
(
Pst *pst,
SuId suId,
RmuUeRecfgInd         *rrmWrUeRecfgInd
)
{
   S16 ret = RFAILED;

   TRC3 (WrLiRmuUeRecfgInd);

   ret = wrUmmProcRmUeRecfgInd (rrmWrUeRecfgInd);


   RETVALUE(ret);
} /* WrLiRmuUeReCfgInd */

/* @brief This function is used to process the bind confirm from the RRM 
 *
 * @details
 *
 *     Function: WrLiRmuBndCfm
 *
 *         Processing steps:
 *
 * @param[in] status: The status of the upper SAP bind request.
 * 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuBndCfm
(
Pst *pst,
SuId suId,
U8   status
)
#else
PUBLIC S16 WrLiRmuBndCfm (pst, suId, status)
Pst *pst;
SuId suId;
U8   status;
#endif
{
   TRC2(WrLiRmuBndCfm);
   
   /*Send alarm */
   if(CM_BND_OK == status)
   {
      RLOG0(L_INFO, "[ALARM] Sending RMU_SAP_BND_OK to OAM");
      wrStopTmr((PTR)wrCb.rmuSap[0],WR_TMR_RMU_SAP_BND);
      wrSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_OK, LWR_CAUSE_RMU_SAP_BOUND);
   }
   else
   {
      RLOG0(L_FATAL, "[ALARM] Sending RMU_SAP_BND_FAIL to OAM");
      wrStopTmr((PTR)wrCb.rmuSap[0],WR_TMR_RMU_SAP_BND);
      wrSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, LCM_CAUSE_UNKNOWN);
   }
 
   RETVALUE(ROK);
}

#ifdef RM_INTF
/** @brief This function is used to intimate FSM related status to
 *         RRM.
 *
 * @details  This function is used to indicate MME and ENODE B status change to 
 *           RRM.
 *          MME addition or deletion in FSM invokes the primitive.
 * @param[in] statusInd      :MME/ENODB status is sent to RRM.
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmStatusInd
(
RmuFsmStatusInd *statusInd
)
{
   S16 ret = RFAILED;

   TRC3(wrIfmRrmStatusInd);
   
   ret = WrLiRmuFsmStatusInd(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, statusInd);
   
   RETVALUE(ret);

} /* wrIfmRrmStatusInd */
#endif /*RM_INTF*/

/** @brief This function is used to reconfigure the UE context maintained in
 *         RRM.
 *
 * @details  This function is used to reconfigure the UE context maintained in
 *           RRM.
 *          the UE crnti during re-establishment procedure is initiated.
 * @param[in] ueRecfgInfo      :Ue REconfiguration parameters to be sent to RRM.
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmSndUeRecfgReq
(
RmuUeRecfgReq *ueRecfgInfo
)
{
   S16 ret = RFAILED;

   TRC3(wrIfmRrmSndUeRecfgReq);
   
   ret = WrLiRmuUeRecfgReq(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, ueRecfgInfo);
   
   RETVALUE(ret);

} /* wrIfmRrmSndUeRecfgReq */

/**
 *  @brief This function fills and sends the UE Reconfiguration request to RRM
 *         for updating the New CRTI of the UE
 *         
 *  @details This fucniton updates the UE CRNTI in UE context.
 *
 *      Function: wrUmmReestRrmRntiUpdt
 *
 *          Processing steps:
 *          - fill the Ue Reconfiguraiton Req with new CRNTI
 *          - call the RMM for UE reconfiguraiton
 *
 *  @param [in] transCb : pointer to transaction control block of intinial
 *                        context proocessor transaction 
 *  @return S16
 *
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */

PUBLIC S16 wrUmmReestRrmRntiUpdt(WrUmmTransCb *transCb)
{
   RmuUeRecfgReq             *ueRecfgInfo;

   /* Send Uerecfg req to RRM for changing UEId */
   WR_ALLOC(&ueRecfgInfo, sizeof(RmuCommonMsg));
   if (ueRecfgInfo == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   ueRecfgInfo->uiTransId = transCb->transId;
   ueRecfgInfo->bRecfgBitMap |= RMU_RECFG_REQ_NEW_CRNTI;
   ueRecfgInfo->bCellId =  transCb->ueCb->cellId;
   ueRecfgInfo->usCrnti = transCb->ueCb->crnti;
   ueRecfgInfo->usUeNewCrnti = transCb->u.rrcReEstabTransCb.newRnti;

   wrIfmRrmSndUeRecfgReq(ueRecfgInfo);

   RETVALUE(ROK);
}

/* SPS changes starts */
/**
 *  @brief This function Indicates RRM that APP is unable to 
 *  configure SPS for the UE
 *         
 *  @details This fucniton fills and sends RmuUeSpsDisableInd.
 *
 *      Function: wrUmmRrmUeSpsDisInd
 *
 *          Processing steps:
 *          - fill the SPS Disable Indication
 *          - call the RMM for SPS Disabling
 *
 *  @param [in] ueId : UE Id
 *
 *  @return S16
 *
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */

PUBLIC S16 wrUmmRrmUeSpsDisInd
(
 U8 cellId,
 U16 crnti
)
{
   RmuCommonMsg       *cmnMsg  = NULLP;
   S16                ret      = ROK;

   /* Send RRM disable Indication to Indicate SPS is disabled */
   WR_ALLOC(&cmnMsg, sizeof(RmuCommonMsg));
   if (cmnMsg == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   cmnMsg->stRmuSpsDisInd.cellId = cellId;
   cmnMsg->stRmuSpsDisInd.usCrnti = crnti;

   ret = WrLiRmuUeSpsDisInd(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, &cmnMsg->stRmuSpsDisInd);

   RETVALUE(ret);
}
/*RRM_ARP*/
/** @brief This function is used to receive and process ERAB release 
 *         indication from RRM.
 *
 * @details  This function receives ERAB release indication and calls the WR
 *           fucntion to process it.
 *           
 * @param[in] relIndinfo   :    UE ERAB release indication 
 *                               received at enbApp.
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */
PUBLIC S16 WrLiRmuUeERabRelInd
(
Pst *pst,
SuId suId,
RmuUeERabRelInd *relIndinfo
)
{
   S16 ret = RFAILED;

   TRC3(WrLiRmuUeERabRelInd);
   ret = wrUmmProcRrmUeRabRelInd(relIndinfo);
  

   RETVALUE(ret);

} /* End of WrLiRmuUeERabRelInd */

/** @brief This function is used to receive and process the response of 
 *         reconfigure request from RRM.
 *
 * @details  This function receives the reconfigure response and call the WR
 *           fucntion to process the response received. 
 *           
 * @param[in] ueRecfgRespInfo   :Ue REconfiguration response parameters 
 *                               received at enbApp.
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */
PUBLIC S16 WrLiRmuUeRecfgRsp
(
Pst *pst,
SuId suId,
RmuUeRecfgRsp *ueRecfgRespInfo
)
{
   S16 ret = RFAILED;

   TRC3(WrLiRmuUeRecfgRsp);
   
   ret = wrUmmProcRrmUeCfgRsp(ueRecfgRespInfo);
  

   RETVALUE(ret);

} /* End of WrLiRmuUeRecfgRsp */
#ifndef RM_INTF
PUBLIC S16 RmWrUeRecfgInd 
(
 RrmWrUeRecfgIndInfo *rrmWrUeRecfgInd
)
{
   S16 ret = RFAILED;

   TRC3(RmWrUeRecfgInd);
  /* TODO : Action need to take care for RBC and CQI configuration */
 
   RETVALUE(ret);

} /* End of RmWrUeRecfgInd */

#endif
/* @brief This function is used to send the UE Release Requst to RRM layer.
 *
 * @details
 *
 *     Function: wrIfmRrmSendUeRelReq 
 *
 *         Processing steps:
 *         - This function is invoked by UMM module during UE dletation.
 *         - This function is used to send UE Release request to RRM
 *           layer.
 *
 * @param [in] cellId   : Cell Identity of a cell in which UE is present
 * @param [in] crnti    : CRNTI of the UE triggering the UE Release Request.   
 * @param [in] transId  : Transaction ID of the UE Release procedure between FSM
 *                        and RRM which is same as transId of the FSM
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 WrIfmRrmSendUeRelReq
(
 CmLteCellId                cellId,
 U16                        crnti,
 U32                        transId
)
{
   RmuUeRelReq              *rrmWrUeRelReq;
   S16                       ret = ROK;

   TRC3(WrIfmRrmSendUeRelReq);
   
   WR_ALLOC(&rrmWrUeRelReq, sizeof(RmuCommonMsg));
   if(NULLP == rrmWrUeRelReq)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   rrmWrUeRelReq->bCellId = cellId;
   rrmWrUeRelReq->usCrnti = crnti;
   rrmWrUeRelReq->uiTransId = transId;

   /* Calling RRM function for UE Release Request for tightly coupled */
   ret = WrLiRmuUeRelReq(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrUeRelReq);
   if(ROK != ret)
   {
      RLOG_ARG1(L_ERROR,DBG_CRNTI, crnti, "UE Release Request is Failed TransID:[%lu]", transId);
   }
   RETVALUE(ret);
} /* end of wrIfmRrmSendUeRelReq */

/** @brief This function is used to process the UE Release response from the RRM layer.
 *
 * @details This function is invoked by RRM to provide UE Release response (Success or
 *          failure) to FSM.
 *
 *     Function: WrLiRmuUeRelRsp
 *
 * @param[in] ueRelRespPtr  : The pointer to UE Release response structure.
 *                            
 * @return S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 WrLiRmuUeRelRsp
(
Pst *pst,
SuId suId,
RmuUeRelRsp *relrspinfoPtr
)
{
   S16 ret = RFAILED;

   TRC3(WrLiRmuUeRelRsp);

   if (RMU_SUCCESS != relrspinfoPtr->stStatusInfo.enStatus)
   {
      RLOG_ARG2(L_INFO, DBG_CRNTI, relrspinfoPtr->usCrnti,  "Release Response from RRM is:"
      "status: %u, cause:%u", relrspinfoPtr->stStatusInfo.enStatus, relrspinfoPtr->stStatusInfo.enCause);
   }
   
   ret = wrUmmPrcRrmUeRelResp(relrspinfoPtr);

   RETVALUE (ret);
} /* end of WrLiRmuUeRelRsp */

/** @brief This function responds to the CAC UE admission request.
 *
 * @details This function is called from RRM to provide FSM with response 
 *          (Success or failure) of CAC admission request and other 
 *          information like preemption information etc. FSM adds or rejects 
 *          the different call based on RRM decision.
 *
 * @param[in] rrmWrUeAdmitResp  :The pointer to Call Admission Control 
 *                                   (CAC) UE admission response structure.
 *                            
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */

PUBLIC S16 WrLiRmuUeAdmitRsp
(
Pst *pst,
SuId suId,
RmuUeAdmitRsp *admitRspinfo
)
{
//   S16 ret = RFAILED;
//   WrUmmTransCb              *transCb = NULLP;
//   WrUeCb                    *ueCb = NULLP;

   TRC3(WrLiRmuUeAdmitRsp);


   RETVALUE(wrUmmPrcRrmUeAdmitResp(admitRspinfo));

#if 0 /*Moved to respective transaction handler*/
   /* UE Cfg - PHY Layer */
   wrUmmRrcConPhyUeCfg(transCb);

   /* UE Cfg - Scheduler */
   wrUmmRrcConSchUeCfg(transCb);
#endif



}/* WrLiRmuUeAdmitRsp */

/** @brief This function delete a UE based on the indication from RRM.
 *
 * @details This function is called by RRM whenever some call needs to be 
 *          deleted. RRM provides cell id, crnti and other relevant information
 *          to FSM using this primitive.
 *
 * @param[in] rrmWrUeRelInd   :The pointer to Call Admission Control (CAC) UE 
 *                             deletion request structure.
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */

PUBLIC S16 WrLiRmuUeRelInd
(
Pst *pst,
SuId suId,
RmuUeRelInd *relIndinfo
)
{
   S16 ret = RFAILED;

   TRC3(WrLiRmuUeRelInd);

   ret = wrUmmPrcRrmUeRelInd(relIndinfo);

   WR_FREE(relIndinfo, sizeof(RmuCommonMsg));
   
   RETVALUE(ret);
   
}/* WrLiRmuUeRelInd */

/** @brief This function adds a UE based on the request made.
 *
 * @details This function is called by FSM whenever a new call admission needs
 *          to be done. FSM provides cell id, crnti and other relevant 
 *          information to RRM using this primitive.
 *
 * @param[in]  cellId:           Cell ID to which the UE belongs to.
 *             crnti:            CRNTI of the UE to be added.
 *             transId:          Trans ID assigned for UE admission.
 *             establishCause:   Establishment Cause like emergency call etc. 
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRrmUeAdmitReq
(
WrCellId                     cellId, 
U16                          crnti, 
U32                          transId, 
U32                          establishCause
)
{
   RmuUeAdmitReq            *rrmWrUeAdmitReq;
   S16                       ret = RFAILED;

   TRC3(wrIfmRrmUeAdmitReq);

   WR_ALLOC(&rrmWrUeAdmitReq, sizeof(RmuCommonMsg));
   if(NULLP == rrmWrUeAdmitReq)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(ret);
   }
   rrmWrUeAdmitReq->bCellId = cellId;
   rrmWrUeAdmitReq->usCrnti = crnti;
   rrmWrUeAdmitReq->uiTransId = transId;
   rrmWrUeAdmitReq->enConEstabCause = establishCause;
   
   ret = WrLiRmuUeAdmitReq(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrUeAdmitReq);

   RETVALUE(ret);

}/* wrIfmRrmUeAdmitReq */

/*RRM_SP3*/
/** @brief Function to send UE inactivity indication to RRM.
 *
 * @details This function is used to send UE inactivity information received
 *          from DAM to RRM.
 *
 * @param[in] pst  Post information between DAM to RRM.
 * @param[in] suId service User Id. 
 * @param[in] rrmUeInactInd  UE inactivity information
 *
 * @return S16
 * -# Success : ROK
 * -# Failure : RFAILED
 */
PUBLIC S16 wrIfmRmuInactInd
(
Pst *pst,
SuId suId,
RmuUeInactInd   *rrmUeInactInd
)
{
   RETVALUE(WrLiRmuUeInactInd(pst,
                              suId,
                              rrmUeInactInd));
}

/*RRM_SP3*/
/** @brief  Function to send UE inactivity indication to RRM
 *
 * @details This function invokes the pack and send function to send 
 *          UE inactivity indication to RRM.
 *
 *     Function: wrIfmDamRmuUeInactInd
 *
 *         Processing steps:
 *            - fetch the pst for ENBAPP interface
 *            - invoke pack function
 *
 * @param[in] crnti     UE identifier
 * @param[in] cellId    Cell Identifier
 * @param[in] inactEvt  UE inactivity event
 *
 * @return  Void 
 */
PUBLIC Void wrIfmDamRmuUeInactInd 
(
U16   crnti,
U16   cellId,
U32   inactEvt 
)
{
   RmuUeInactInd   *rrmUeInactInd;
   Pst             *pst;

   TRC2(wrIfmDamRmuUeInactInd);

   pst = &wrDamCb.wrDamToRrmPst;

   /*This is being freed in RRM*/
   WR_ALLOC_SHAREBLE_BUF(&rrmUeInactInd, sizeof(RmuCommonMsg));
   if(NULLP == rrmUeInactInd)
   {
      RLOG0(L_FATAL, "Memory allocation failed for UE Inact Ind.");
      RETVOID;
   }

   rrmUeInactInd->uiCrnti    = crnti;
   rrmUeInactInd->uiCellId   = cellId;
   rrmUeInactInd->uiInactEvt = inactEvt;

   wrIfmRmuInactInd(pst,0,rrmUeInactInd);
   
   RETVOID;
}
PUBLIC S16 wrIfmRrmHoAdmitReq
(
RmuUeHoReq              *rrmWrUeHoAdmitReq
)
{
   S16                      ret = RFAILED;

   TRC3(wrIfmRrmHoAdmitReq);

   ret = WrLiRmuUeHoReq(&(wrCb.rmuSap[0]->pst), wrCb.rmuSap[0]->suId, rrmWrUeHoAdmitReq);

   RETVALUE(ret);

}/* wrIfmRrmHoAdmitReq */

PUBLIC S16 WrLiRmuUeHoRsp
(
Pst *pst,
SuId suId,
RmuUeHoRsp *hoAdmitRspinfo
)
{
//   S16 ret = RFAILED;
//   WrUmmTransCb              *transCb = NULLP;
//   WrUeCb                    *ueCb = NULLP;

   TRC3(WrLiRmuUeHoRsp);

   RETVALUE(wrUmmProcHoAdmitRsp(hoAdmitRspinfo));
}

#if 1
PUBLIC Void wrDebugShowBaaringPrams(WrSib2AcBarringCfg *sib2DataCall, WrSib2AcBarringCfg *sib2Signalling)
{
   if (sib2DataCall->pres)
   {
      /*127802*/
      RLOG2(L_INFO, "(DATA) (%d %d)", sib2DataCall->acBarringFactor, sib2DataCall->acBarringTime);
   }
   else
   {
     /*127802*/
      RLOG0(L_INFO, "(DATA) NO BARRING");
   }
   if(sib2Signalling->pres)
   {
     /*127802*/
      RLOG2(L_INFO, "(SIG) (%d %d)", sib2Signalling->acBarringFactor, sib2Signalling->acBarringTime);
   }
   else
   {
      /*127802*/
      RLOG0(L_INFO, "(SIG) NO BARRING");
   }
}
#endif



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
