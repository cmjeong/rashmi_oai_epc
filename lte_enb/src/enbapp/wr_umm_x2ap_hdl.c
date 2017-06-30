
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_x2ap_hdl.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=77;


static int RLOG_MODULE_ID=32;

#include "wr.h"        /* Common Includes */
#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_umm_trans.h"

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
PUBLIC S16 wrUmmX2GetTransIdFromMsg
(
WrUeCb                       *ueCb,
WrUmmIncMsg                  *msg,
U32                          *transId
)
{
   CztX2AP_PDU               *pdu = &msg->u.x2Pdu->pdu;
   S16                       msgType = CZT_MSG_UNKNOWN;

   msgType = wrUtlX2GetMsgIdx (pdu);
   if(CZT_MSG_HO_REQ == msgType)
   {
      *transId = WR_CREATE_NEW_TRANS;
   }
   else
   {
      *transId = ueCb->hoTransId;
   }
   RETVALUE(ROK);
}

/* ********************************************************************** */
/*                                                                        */
/* This function is responsible for identifying transaction type based    */
/* on the received message. All transactions start with initiating        */
/* messages.                                                              */
/*                                                                        */
/* ********************************************************************** */
PUBLIC S16 wrUmmGetX2TransType
(
WrUmmIncMsg                  *msg,
U32                          *transTyp
)
{
   CztX2AP_PDU               *pdu = &msg->u.x2Pdu->pdu;
   /* S16                       msgType = CZT_MSG_UNKNOWN; */
   S16                        msgType = CZT_MSG_UNKNOWN; 
   msgType = wrUtlX2GetMsgIdx(pdu);
   /*ccpu00127802*/
   RLOG1(L_DEBUG, "=====Message Type=====[%d]",msgType);
   switch(msgType)
   {
      case CZT_MSG_HO_REQ:
      case CZT_MSG_HO_CANCEL:
      case CZT_MSG_SN_STATUS_TRFR:
      {
         *transTyp = WR_UMM_X2_TGT_HO_TRANS;
         RETVALUE(ROK);
      }
      case CZT_MSG_HO_ACK:
      case CZT_MSG_HO_FAIL:
      case CZT_MSG_UE_CXT_RELEASE:
      {
         *transTyp = WR_UMM_X2_SRC_HO_TRANS;
         RETVALUE(ROK);
      }
      default:
      {
        *transTyp = CZT_MSG_UNKNOWN;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
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
