
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_locrpt.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_MODULE_ID=32;
static int RLOG_FILE_ID=128;

#include "wr.h"
#include "wr_utils.h"
#include "wr_umm.h"
#include "wr_umm_trans.h"
#include "wr_lwr.h"
#include "wr_umm_s1ap_msg.h"
#include "wr_ifm_s1ap.h"

/** @brief This function is responsible for handling Location report Control 
 *         message
 *
 * @details
 *
 * Function:wrUmmLocReptProcessor
 *
 *   Processing steps:
 *    -Get the Request type
 *    -If the request type is 'Update whenever UE changes cell', store the
 *     request type in UE control block and return
 *    -If the request type is 'Direct', send the Location Report message
 *     to UE
 *    -If the request type is 'Cancel whenever UE changes cell', reset the
 *     same in UE control block and return
 *
 * @param[in]  transCb: pointer to transaction control block
 * @return S16
 *  -#Success : ROK
 *  -#Failure : RFAILED
 */
PUBLIC S16 wrUmmLocReptProcessor
(
 WrUmmTransCb                *transCb
)
{
   SztRqstTyp    *rqstType;
   WrUeCb        *ueCb;
   S1apPdu       *locRptFail;

   ueCb = transCb->ueCb;

   /* Check if the UE is in handover state, if yes, send out the location control 
    * failure indication to MME with appropriate cause */
   if(ueCb->mobCtrlState != WR_HO_NORMAL)
   {
      wrUmmS1apBldLocReportFail(ueCb, &locRptFail);
      wrIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, locRptFail);
      transCb->state = WR_UMM_TRANS_DONE;
      RETVALUE(ROK);
   }

   /* Get the Request Type IE from the message */
   wrSzGetIE(&(transCb->msg->u.s1Pdu->pdu->pdu), Sztid_RqstTyp,
             (TknU8**)(&rqstType));

   if(rqstType == NULLP)
   {
      transCb->state = WR_UMM_TRANS_DONE;
      RETVALUE(RFAILED);
   }

   RLOG_ARG3(L_EVENT, DBG_CRNTI,ueCb->crnti,"[S1AP]:Received LOCATION REPORTING"
             "CONTROL [MME-UE-S1AP-ID:%lu] [eNB-UE-S1AP-ID:%lu] [ReqType:%d]",
             ueCb->s1ConCb->mme_ue_s1ap_id, ueCb->s1ConCb->enb_ue_s1ap_id,rqstType->eventTyp.val);

   /* Check the Request type, if the Request type is 'chage of serve cell',
    * store the value and return. If the request type is 'stop change
    * serve cell' then make the flag as false. If the request tupe is
    * 'Direct', send the Location Report Message */
   switch(rqstType->eventTyp.val)
   {
      case SztEventTypchange_of_serve_cellEnum:
      {
         ueCb->locReportType = TRUE;
         break;
      }
      case SztEventTypstop_change_of_serve_cellEnum:
      {
         ueCb->locReportType = FALSE;
         break;
      }
      case SztEventTypdirectEnum:
      {
         /* Build and send the location report message to MME */
         wrUmmBldSndLocRept(transCb);
         break;
      }
      default:
         break;
   }

   /* End the transaction here as we have done with this trasaction */
   transCb->state = WR_UMM_TRANS_DONE;
   RETVALUE(ROK);
}

/** @brief This function is Location Report Control specific transaction release
 *         function. There is nothing held by this transaction and so a simple
 *         return function.
 *
 * @details
 *
 *     Function: wrUmmLocReptTransRel
 *
 *         Processing steps:
 *         - No Release Action Performed
 *
 * @param[in]  transCb : transaction information
 * @return  ROK
 */
PUBLIC S16 wrUmmLocReptTransRel
(
 WrUmmTransCb                 *transCb
)
{
   RETVALUE(ROK);
}

/** @brief This function is called by HO module to send the Location Report
 *         message to MME if the MME is requested to report the 'Update
 *         whenever change in cell' or if the 'Request type IE' is present
 *         in the Handover Request.
 *
 * @details
 *
 *     Function: wrUmmBldSndLocRept
 *
 *         Processing steps:
 *         - Build the Location Control Message
 *         - Send the Location control message
 *
 * @param[in]  transCb : transaction information
 * @return  ROK
 */
PUBLIC Void wrUmmBldSndLocRept
(
 WrUmmTransCb                 *transCb
)
{
   WrUeCb        *ueCb;
   S1apPdu       *locRpt;

   /* Get the UeCb from the transaction CB */
   ueCb = transCb->ueCb;

   wrUmmS1apBldLocReport(ueCb, &locRpt);
   wrIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, locRpt);

   RETVOID;
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
