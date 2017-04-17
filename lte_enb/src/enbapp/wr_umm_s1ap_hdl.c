
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_s1ap_hdl.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=69;


static int RLOG_MODULE_ID=32;

#include "wr.h"        /* Common Includes */
#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_ifm_s1ap.h"
#include "wr_umm_trans.h"


PRIVATE Bool wrUmmCheckIsHoStsIEPresDlCdma
(
S1apPdu              *pdu
)
{
   Bool     result    = FALSE;
   U8       idx = 0;

   SztDlnkS1cdma2000tunneling  *dlCdma;
   SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *ie = NULLP;

   if(pdu->pdu.val.initiatingMsg.procedureCode.val == Sztid_DlnkS1cdma2000tunneling)
   {
      dlCdma = &pdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling;
      /* now fill the protocol field member */
      /* if in dlCDMA tunneling msg contains HOStaus ID 
       * is present then return TRUE else FALSE */

      for(idx = 0; idx < dlCdma->protocolIEs.noComp.val; idx++)
      {
         ie = &dlCdma->protocolIEs.member[idx];

         if(ie->id.val == Sztid_cdma2000HOStatus)
         {
            result = TRUE;
            break;
         }
      }
   }
   RETVALUE(result);
}


/**
 *  @brief This function determines the tansaction Id for a message 
 *
 *  @details Transaction ID determination from the message is needed only
 *           for successful response or a failure. If it is an initiating 
 *           PDU, a new transaction should be allocated for such procedures.
 *           This function returns ROK to suggest successful processing. It
 *           returns FAILED if the message ID is invalid to indicate failure.
 *           
 *
 *      Function: wrUmmS1GetTransIdFromMsg
 *
 *          Processing steps:
 *          - switch to the message type
 *          - fetch the message ID or assign new message ID for an initiating
 *            PDU
 *
 *  @param[in]  ueCb    : pointer to UE control block
 *  @param[in]  msg     : pointer to the incoming message
 *  @param[out] transId : pointer to return the transId
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */


/* ********************************************************************** */
/*                                                                        */
/* Transaction ID determination from the message is needed only for       */
/* successful response or a failure. If it is an initiating PDU, a new    */
/* transaction should be allocated for such procedures                    */
/*                                                                        */
/* This function returns ROK to suggest successful processing. It returns */
/* RFAILED to indicate failure.                                           */
/*                                                                        */
/* transId is populated with transaction identifier if a match is found.  */
/* If the PDU includes an initiating procedure, it returns 0 to suggest   */
/* that a new transaction needs to be allocated                           */
/*                                                                        */
/* ********************************************************************** */
PUBLIC S16 wrUmmS1GetTransIdFromMsg
(
WrUeCb                       *ueCb,
WrUmmIncMsg                  *msg,
U32                          *transId
)
{
   S1apPdu                   *pdu = msg->u.s1Pdu->pdu;
   SztInitiatingMsg          *initiatingMsg = &pdu->pdu.val.initiatingMsg;

   switch(pdu->pdu.choice.val)
   {
      case S1AP_PDU_INITIATINGMSG:
      {
            /* Check whether HOStatus is present in DL CDMA
             * tunnelling message or not. If return TRUE,
             * then find the existing eCSFB trnsaction Id
             * else create a new transaction id for DL CDMA msg */
            if(TRUE == wrUmmCheckIsHoStsIEPresDlCdma(pdu))
            {
               /* Get the existing transId of eCSFB transaction */
               if(wrUmmGetExistingTransId(WR_UMM_ECSFB_TRANS, &ueCb->transLst, transId) != ROK)
               {
                  RETVALUE(RFAILED);
               }
            }
            else if(ueCb->hoTransId != 0)
            {
               /*Check for the Message Type Received and proceed weather to create
                * new Transaction of use exitsting transaction */
               switch(initiatingMsg->procedureCode.val)
               {
                  case Sztid_UECntxtModification:
                  case Sztid_E_RABSetup:
                  case Sztid_E_RABMdfy:
                  case Sztid_E_RABRls:
                  case Sztid_downlinkNASTport:
                     {
                        *transId = WR_CREATE_NEW_TRANS;
                     }
                     break;
                  default:
                     {
                        *transId = ueCb->hoTransId;
                     }
                     break;

                     RETVALUE(ROK);
               }
            }
         else
         {
            *transId = WR_CREATE_NEW_TRANS;
         }
         RETVALUE(ROK);
      }
      case S1AP_PDU_SUCCESSFULOUTCOME:
      {
         if(ueCb->hoTransId != 0)
         {
            *transId = ueCb->hoTransId;
         }
         else
         {
            *transId = WR_CREATE_NEW_TRANS;
         }
         RETVALUE(ROK);
      }
      case S1AP_PDU_UNSUCCESSFULOUTCOME:
      {
         if(ueCb->hoTransId != 0)
         {
            *transId = ueCb->hoTransId;
         }
         else
         {
            *transId = WR_CREATE_NEW_TRANS;
         }
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
} /* end of wrUmmS1GetTransIdFromMsg */ 

/**
 *  @brief This function is responsible for identifying transaction type 
 *         based on the received message. All transactions start with 
 *         initiating messages
 *
 *      Function: wrUmmGetS1TransType
 *
 *          Processing steps:
 *          - switch to the message type
 *             - assign the transaction type to the pointer provided
 *             - return ROK
 *          - return RFAILED if invalid message type is received
 *
 *  @param[in]  msg      : pointer to the incomimng geessa
 *  @param[out] transTyp : pointer to return the transaction type
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */


/* ********************************************************************** */
/*                                                                        */
/* This function is responsible for identifying transaction type based    */
/* on the received message. All transactions start with initiating        */
/* messages.                                                              */
/*                                                                        */
/* ********************************************************************** */
PUBLIC S16 wrUmmGetS1TransType
(
S1apPdu                      *pdu,
U32                          *transTyp
)
{
   U8                        msgType;

   wrSztUtilsGetMsgIdx(&msgType, pdu);
   switch(msgType)
   {
      case SZT_MSG_ID_HO_REQ:
      {
         *transTyp = WR_UMM_S1_TGT_HO_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_HO_CANCEL_ACK:
      {
         RLOG0(L_ERROR, "HO_CANCEL_ACK received."
                        "No New Transaction will be created"); 
         RETVALUE(RFAILED);
      }
      case SZT_MSG_ID_HO_PREP_FAIL:
      case SZT_MSG_ID_HO_CMD:
      {
          ALARM("%s: Not handling S1AP Msg Type:%d, since HO Trans does not exist",__func__,msgType); 
          *transTyp = WR_UMM_TRANS_UKNW;
         RETVALUE(RFAILED);
      }
      case SZT_MSG_ID_DL_NAS_TPT:
      {
         /* Need to implement for initial context setup message here */
         *transTyp = WR_UMM_DL_NAS_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_E_RAB_BRR_SETUP_REQ:
      {
         /* Need to implement for initial context setup message here */
         *transTyp = WR_UMM_ERAB_SETUP_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_E_RAB_BRR_MOD_REQ:
      {
         /* Need to implement for ERAB modify setup message here */
         *transTyp = WR_UMM_ERAB_MOD_TRANS;
         RETVALUE(ROK);
      }
      /*In case of error indication release UE */
      case SZT_MSG_ID_UE_CXT_REL_CMD:
      case SZT_MSG_ID_ERR_IND:
      {
         *transTyp = WR_UMM_CTXT_REL_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_E_RAB_BRR_REL_CMD:
      {
         *transTyp = WR_UMM_RAB_REL_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_UE_CXT_MOD_REQ:
      {
         *transTyp = WR_UMM_UE_CTXT_MOD_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_CXT_SETUP_REQ:
      {
         *transTyp = WR_UMM_INIT_CTXT_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_LOC_REPORT_CNTRL:
      {
         *transTyp = WR_UMM_LOCATION_REPORT_TRANS;
         RETVALUE(ROK);
      }
      case SZT_MSG_ID_DNLNK_CDMA_TUNNL:
      {
         *transTyp = WR_UMM_DL_CDMA_TRANS; 
         RETVALUE(ROK);
      }
      default:
      {
          RLOG1(L_ERROR, "Not handling S1AP Msg Type[%d]",msgType); 
          *transTyp = WR_UMM_TRANS_UKNW;
          RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
} /* end of wrUmmGetS1TransType */ 



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
