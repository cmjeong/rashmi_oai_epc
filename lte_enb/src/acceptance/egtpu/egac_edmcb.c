
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_egtreg.c

     Sid:      egac_edmcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:24 2015

     Prg:     pc

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */

#include "eg_util.h"       /* Edmpeter Utility library */
#include "egt.h"           /* Edmpeter Upper Interface */
#include "eg_edm.h"           /* Edmpeter Upper Interface */
#include "eg.h"           /* Edmpeter Upper Interface */
#include "egac_edm.h"           /* Edmpeter Upper Interface */
#include "leg.h"           /* Edmpeter Layer Manager   */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.h"
#include "cm_dns.x"

#include "egt.x"           /* Eg Upper Interface */
#include "leg.x"           /* Eg layer manager  */

#include "cm_xta.h"
#include "egac_acc.h"
#include "eg.x"
#include "cm_xta.x"
#include "egac_acc.x"
#include "egac_edm.x"
#include "eg_edm.x"
#include "eg_util.x"       /* Eg Utility library */

/*
*
*       Fun:   EuLiEdmLmCfm
*
*       Desc:  Call handler for eGTP Message Cfg
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEdmLmCfm
(
CmStatus   status
)
#else
PUBLIC S16 EuLiEdmLmCfm( status)
CmStatus   status;
#endif
{
   EgErrEvnt errEvnt;
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(EuLiEdmLmCfm)

   cmMemset((U8 *) &errEvnt, 0, sizeof(EgErrEvnt));

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEdmLmCfm():\n"));

   egAcEdmSaveMsg(EVTEDMCFGCFM, NULLP,errEvnt, status);

   RETVALUE(ROK);
}

/*
*
*       Fun:   EuLiEdmGmSigInd
*
*       Desc:  Call handler for eGTP Message Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEdmGmSigInd
(
EgMsg *egMsg
)
#else
PUBLIC S16 EuLiEdmGmSigInd( egMsg)
EgMsg *egMsg;
#endif
{
   CmStatus   status;
   EgErrEvnt errEvnt;
   cmMemset((U8 *) &status, 0, sizeof(CmStatus));
   cmMemset((U8 *) &errEvnt, 0, sizeof(EgErrEvnt));

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(EuLiEdmGmSigInd)

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEdmGmSigInd():\n"));

   egAcEdmSaveMsg(EVTEDMSIGIND, egMsg,errEvnt, status);

   RETVALUE(ROK);
}

/*
*
*       Fun:   EuLiEdmErrInd
*
*       Desc:  Call handler for eGTP Error message Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEdmErrInd
(
EgErrEvnt errEvnt
)
#else
PUBLIC S16 EuLiEdmErrInd    ( errEvnt)
EgErrEvnt errEvnt;
#endif
{

   CmStatus   status;
   cmMemset((U8 *) &status, 0, sizeof(CmStatus));

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(EuLiEdmErrInd)
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEdmErrInd():\n"));

   egAcEdmSaveMsg(EVTEDMERRIND, NULLP, errEvnt, status);

   RETVALUE(ROK);
}


/*
*
*       Fun:   EuLiEdmGmSigCfm
*
*       Desc:  Call handler for eGTP Message Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEdmGmSigCfm
(
EgMsg *egMsg
)
#else
PUBLIC S16 EuLiEdmGmSigCfm    (egMsg)
EgMsg *egMsg;
#endif
{
   CmStatus   status;
   EgErrEvnt errEvnt;
   cmMemset((U8 *) &status, 0, sizeof(CmStatus));
   cmMemset((U8 *) &errEvnt, 0, sizeof(EgErrEvnt));
   
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(EuLiEdmGmSigCfm)

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEdmGmSigCfm():\n"));

   egAcEdmSaveMsg(EVTEDMSIGCFM, egMsg,errEvnt, status);

   RETVALUE(ROK);
}

/*
*
*       Fun:   EuLiEdmTptMsg
*
*       Desc:  Call handler for rcvd message buffer
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEdmTptMsg
(
U8   intfType,
Buffer *mBuf
)
#else
PUBLIC S16 EuLiEdmTptMsg( intfType, mBuf)
U8   intfType;
Buffer *mBuf;
#endif
{


   CmXtaTCCb *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg = NULLP;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(EuLiEdmTptMsg)

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   /*-- Allocate EGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEdmSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }


   /* Check if Load mode --*/
   if (cmXtaCb.loadDir.loadMode == FALSE)
   {
      /*-- Usual mode --*/
      CMXTA_ZERO(&qElm, sizeof(qElm));

      /*-- Find the associated test case using the txnId --*/
      if ((tcCb = egAcEdmTstCbFind()) == NULLP)
      {
         /*-- No associated test case found, spurious 
           message, drop it --*/

         if (mBuf)
         {
            SPutMsg(mBuf);
         } /* end of if mBuf is valid */

         CMXTA_DBG_ERR((_cmxtap, "egAcEdmSaveMsg(): tcCb not found, msg dropped\n"));
         RETVALUE(ROK);
      }


      /*-- Fill the message in the queue structure --*/

      egtpMsg->u.edmInfo.choice = EVTEDMENCREQ;

      /* Store SuId and EgMsg for Bind Indication*/
      egtpMsg->u.edmInfo.mBuf = mBuf;
      egtpMsg->u.edmInfo.intfType = intfType;
  
      qElm.data = (EgAccMsgQElm *)egtpMsg;
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will SOAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   }

   RETVALUE(ROK);

}


/*
*
*       Fun:   egAcEdmSaveMsg
*
*       Desc:  Function to push the message on queue 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcEdmSaveMsg
(
U8   event,
EgMsg *egMsg,
EgErrEvnt errEvnt,
CmStatus  status
)
#else
PUBLIC S16 egAcEdmSaveMsg( event,egMsg,errEvnt, status)
U8   event;
EgMsg *egMsg;
EgErrEvnt errEvnt;
CmStatus  status;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg = NULLP;
   U8  suId = 0;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcEdmSaveMsg)

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   CMXTA_DBG_PARAM((_cmxtap, "egAcEdmSaveMsg(): suId (%d))", suId));

   /*-- Allocate EGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEdmSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Check if Load mode --*/
   if (cmXtaCb.loadDir.loadMode == FALSE)
   {
      /*-- Usual mode --*/
      CMXTA_ZERO(&qElm, sizeof(qElm));

      /*-- Find the associated test case using the txnId --*/
      if ((tcCb = egAcEdmTstCbFind()) == NULLP)
      {
         /*-- No associated test case found, spurious 
           message, drop it --*/

         if (egMsg)
         {
            EgUtilDeAllocGmMsg(&egMsg);
         } /* end of if egMessage is valid */

         CMXTA_DBG_ERR((_cmxtap, "egAcEdmSaveMsg(): tcCb not found, msg dropped\n"));
         RETVALUE(ROK);
      }

      /*-- Fill the message in the queue structure --*/

      switch(event)
      {
         case EVTEDMSIGIND:
         {
            egtpMsg->u.egtInfo.choice = EVTEDMSIGIND;

            /* Store SuId and EgMsg for Bind Indication*/
            egtpMsg->u.egtInfo.u.egSigIndEvt.egMsg =  egMsg;
            break;
         }
         case EVTEDMSIGCFM:
         {
            egtpMsg->u.egtInfo.choice = EVTEDMSIGCFM;

            /* Store SuId and EgMsg for GM Message Confirmation*/
            egtpMsg->u.egtInfo.u.egSigCfmEvt.egMsg =  egMsg;
            break;
         }
         case EVTEDMCFGCFM:
         {
            egtpMsg->u.egtInfo.choice = EVTEDMCFGCFM;
            egtpMsg->u.egtInfo.u.egMngmt.cfm.reason = status.reason;
            egtpMsg->u.egtInfo.u.egMngmt.cfm.status = status.status;
            /* Store SuId and EgMsg for GM Message Confirmation*/
            break;
         }
         case EVTEDMERRIND:
         {
            egtpMsg->u.egtInfo.choice = EVTEDMERRIND;

            cmMemcpy((U8 *)&egtpMsg->u.egtInfo.u.errEvt.errInd,(U8 *)&errEvnt,
                    sizeof(EgErrEvnt));
            break;
         }
         default:
         {
            CMXTA_DBG_ERR((_cmxtap,"egAcEdmSaveMsg() Invalid Message Received\n"));

            break;
         }
      }/* End of switch statement   */
  
      qElm.data = (Void *)egtpMsg;
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will SOAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   }

   RETVALUE(ROK);
} /* end of egAcEdmSaveMsg() */


/*
*
*       Fun:   egAcEdmTstCbFind
*
*       Desc:  Call handler for finding the Test Case Control Block
*
*       Ret:   Test Case Control Block
*
*       Notes: None
*              
*       File:  egac_egucb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  egAcEdmTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  egAcEdmTstCbFind ()
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcEdmTstCbFind)

#ifdef CMXTA_EXTENSION
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else 
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
}

/********************************************************************30**

         End of file:     egac_edmcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:24 2015

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
----------- -------- ---- -----------------------------------------------
/main/1      ---      pc                1. Created for Initial Release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3    eg003.201  psingh            1. Fixed TRACE5 macro from eg006.102 
*********************************************************************91*/
