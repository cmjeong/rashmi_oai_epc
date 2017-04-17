
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_dlcdma.c

     Sid:      fc_umm_dlcdma.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/12 - Mon Feb 15 12:50:59 2016

     Prg:      Sriky 

*********************************************************************21*/

/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_MODULE_ID=32;
static int RLOG_FILE_ID=118;

#include "wr.h"
#include "wr_utils.h"
#include "wr_umm.h"
#include "wr_umm_ecsfb_utils.h"
#include "wr_umm_trans.h"
#include "wr_umm_rrc_msg.h"
#include "wr_umm_s1ap_msg.h"
#include "wr_ifm_rrc.h"
#include "wr_ifm_s1ap.h"
#include "wr_kpi.h"


/**
 *  @brief This function processes the DL S1 cdma tunneling message
 *
 *      Function: wrUmmDlCdmaPrcPdu
 *
 *          Processing steps:
 *          - obtain the cdma pdu and cdma type from message
 *          - cell the function to send the tunnelig message to UE
 *          - Buffer the cdma PDU for re-transmission purpose
 *
 *  @param [in]  transCb       : pointer to transCb
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */
PRIVATE S16 wrUmmDlCdmaPrcPdu
(
WrUmmTransCb                 *transCb
)
{
   S1apPdu                      *pdu;
   SztInitiatingMsg             *initMsg;
   SztDlnkS1cdma2000tunneling   *dlCdma;
   SztCdma2000PDU               *cdmaPdu = NULLP;
/*   SztCdma2000RATTyp             ratTyp; */
   U32                          ratTyp = 0xff;
   SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *ie;
   U32                           idx;

   RLOG_ARG2(L_EVENT, DBG_CRNTI, transCb->ueCb->crnti,"[S1AP]:Received DOWNLINK "
             "S1 CDMA2000 TUNNELING [MME-UE-S1AP-ID:%lu] [eNB-UE-S1AP-ID:%lu]",
             transCb->ueCb->s1ConCb->mme_ue_s1ap_id,
             transCb->ueCb->s1ConCb->enb_ue_s1ap_id);
   /* Init the DL CDMA transaction */
   transCb->u.dlCdmaTrans.msg    = NULLP;
   transCb->u.dlCdmaTrans.cdmaPdu = NULLP;

   pdu = transCb->msg->u.s1Pdu->pdu;
   initMsg = &pdu->pdu.val.initiatingMsg;
   dlCdma   = &initMsg->value.u.sztDlnkS1cdma2000tunneling;

   for(idx = 0; idx < dlCdma->protocolIEs.noComp.val; idx++)
   {
      ie = &dlCdma->protocolIEs.member[idx];
      switch(ie->id.val)
      {
         case Sztid_cdma2000PDU:
            {
               cdmaPdu = &ie->value.u.sztCdma2000PDU;
            }
            break;
         case Sztid_cdma2000RATTyp:
            {
               ratTyp = ie->value.u.sztCdma2000RATTyp.val;
            }
            break;
         default:
            break;
      }
   }

   if (cdmaPdu != NULLP)
   {
      if( RFAILED != wrUmmBuildAndSndCdmaDlInfTfr(transCb, cdmaPdu, ratTyp))
      {
         transCb->u.dlCdmaTrans.cdmaPdu = cdmaPdu;
         transCb->u.dlCdmaTrans.ratTyp = ratTyp;
         transCb->u.dlCdmaTrans.msg    = transCb->msg;
         transCb->u.dlCdmaTrans.numOfDlTxCnt++;
         transCb->u.dlCdmaTrans.datCfmState = WR_UMM_DAT_CFM_WAIT_DL_CDMA_INFO;
         transCb->msg->refCnt++;
      }
   }

   RETVALUE(ROK);
}

/* ********************************************************************** */
/*                                                                        */
/* Name: wrUmmDlCdmaProcessor                                             */
/*                                                                        */
/* This function is called when a DL DOWNLINK S1 CDMA2000 TUNNELING       */
/* message is received from MME.The included S1 CDMA2000 pdu is then      */
/* tranmitted to UE in DL information transfer RRC message.               */
/*                                                                        */
/* ********************************************************************** */
PUBLIC S16 wrUmmDlCdmaProcessor
(
WrUmmTransCb                 *transCb
)
{
   WrUmmIncMsg               *msg = transCb->msg;
   WrUmmDlCdmaTransCb        *dlTrans = &(transCb->u.dlCdmaTrans);

   switch(msg->msgTyp)
   {
      case WR_UMM_S1_DAT_IND:
      {
         wrUmmDlCdmaPrcPdu(transCb);
         break;
      }
      case WR_UMM_TMR_EXPIRY:
      {
         if(transCb->msg->u.tmrExpiry.timerEvnt == WR_TMR_RRC_DAT_CFM)
         {
            if(transCb->u.dlCdmaTrans.numOfDlTxCnt < WR_UMM_ECSFB_MAX_NUM_RETX)
            {
               wrUmmBuildAndSndCdmaDlInfTfr(transCb, transCb->u.dlCdmaTrans.cdmaPdu, transCb->u.dlCdmaTrans.ratTyp);
               transCb->u.dlCdmaTrans.numOfDlTxCnt++;
               break;
            }
            else
            {
               /* need to decide, whether we will free dlInfTfr or not
                * in case of maximum Retry */
              /* WR_FREE_EVNT(dlInfTfr);*/
               dlTrans->state = WR_UMM_DL_CDMA_ERROR;
               break;
            }
         }
      }
      case WR_UMM_RRC_DAT_CFM:
      {
            wrStopTransTmr(transCb, WR_TMR_RRC_DAT_CFM);
            dlTrans->numOfDlTxCnt  = 0;
            wrUmmTransComplete(transCb);
      }
      break;
      default:
      {
         RETVALUE(RFAILED);
      }
   }

   if (dlTrans->state == WR_UMM_DL_CDMA_ERROR)

   {
         wrUmmTransComplete(transCb);
   }
   RETVALUE(ROK);
}

/** @brief This function is DL CDMA transaction specific release function. 
 *
 * @details
 *
 *     Function: wrUmmDlCdmaTransRel
 *
 *         Processing steps:
 *
 * @param[in] transCb: Transaction Cb
 * @return S16
 *        -# Success : ROK
 */
PUBLIC S16 wrUmmDlCdmaTransRel
(
WrUmmTransCb                 *transCb
)
{
   if (transCb->u.dlCdmaTrans.msg != NULLP)
   {
      /*validate whether inetrnal pdu is getting free here or not */
     wrUmmRlsIncMsg(&transCb->u.dlCdmaTrans.msg);
   }
   RETVALUE(ROK);
}

/** @brief This function is called when a new Transaction is created for any
 * other procedure. The new transaction is passed to this function and this
 * function determines the next course of action based on the new transaction
 *
 * @details
 *
 *     Function: wrUmmDlCdmaNewTransProcessor
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

PUBLIC S16 wrUmmDlCdmaNewTransProcessor
(
 WrUmmTransCb                *transCb,
 WrUmmTransCb                *incTrans
 )
{
   TRC2(wrUmmDlCdmaNewTransProcessor)
      switch(incTrans->transTyp)
      {
         case WR_UMM_RRC_REESTAB_TRANS:
            {
               /* stop the Dat Cfm Timer and also store the address of cdma Pdu  along with Rat Type*/
               wrStopTransTmr(transCb, WR_TMR_RRC_DAT_CFM);
               RETVALUE(WR_UMM_TRANS_DEFER_ONGOING);
            }
         default:
            {
               break;
            }
      }

   RETVALUE(WR_UMM_TRANS_OK);
}
/* @details
 *
 *Function: wrUmmDlCdmaPrcDeferTrans
 *
 *Description:
 *   This function is called from the main transaction to invoke its 
 *   deferred trnsaction. Dl CDMA transaction will be in the deferred queue
 *   of re-establishment transaction. On the reception of RRC Re-Configurtion 
 *   complete message DL CDMA transaction will in invoked.
 *
 * @param[in]  transCb    : pointer to transaction control block
 * @param[in]  defTransCb : pointer to Deferred transaction control block
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16 wrUmmDlCdmaPrcDeferTrans
(
  WrUmmTransCb                *transCb,
  WrUmmTransCb                *defTransCb
)
{
   NhuUL_DCCH_Msg            *ulDcchPdu = NULLP;
   U8                        messageType = 0;
   WrUmmDlCdmaTransCb        *dlCdmaTransCb = &defTransCb->u.dlCdmaTrans;

   TRC2(wrUmmDlCdmaPrcDeferTrans)

   if(transCb->msg->msgTyp != WR_UMM_UU_IND_PDU)
   {
      RETVALUE(ROK);
   }
   ulDcchPdu = &(transCb->msg->u.uuIndPdu->sdu.m.ulDcchMsg.dcchMsg);
   messageType = ulDcchPdu->message.val.c1.choice.val;
   switch(messageType)
   {
      case C1_RRCCONRECFGNCOMPL:
         {
            /* Need to check the count here, it may increase every time during 
             *  re-establishment, so checking will control sending the same PDU not more the the MAX COUNT defined 
             */
            if(WR_UMM_ECSFB_MAX_NUM_RETX <= dlCdmaTransCb->numOfDlTxCnt)
            {
               RETVALUE(WR_UMM_STOP_OLD_TRANSACTION);
            }

            if(WR_UMM_DAT_CFM_WAIT_DL_CDMA_INFO == dlCdmaTransCb->datCfmState)
            {
               /*This function will build the message and send it to RRC
                * it will start the DTA CFM timer also
                */
               if(RFAILED != wrUmmBuildAndSndCdmaDlInfTfr(defTransCb, 
                        dlCdmaTransCb->cdmaPdu, dlCdmaTransCb->ratTyp))
               {
                  dlCdmaTransCb->datCfmState = WR_UMM_DAT_CFM_WAIT_DL_CDMA_INFO;
                  dlCdmaTransCb->numOfDlTxCnt++;
                  RETVALUE(WR_UMM_RESUME_DEF_TRANSACTION);
               }
               else
               {
                  RLOG0(L_ERROR, " Sending Failed, closing dlCdma transaction ");
                  RETVALUE(WR_UMM_STOP_OLD_TRANSACTION);
               }
            } 
            RETVALUE(WR_UMM_STOP_OLD_TRANSACTION);
         }
   }
   RETVALUE(WR_UMM_TRANS_OK);
} /* wrUmmDlCdmaPrcDeferTrans */

/********************************************************************30**

           End of file:     fc_umm_dlcdma.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/12 - Mon Feb 15 12:50:59 2016

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
/main/1        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/

