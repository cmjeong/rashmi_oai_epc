
/********************************************************************20**

     Name:     cm_xta_lmrcb.c 

     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     cm_xta_lmrcb.c

     Sid:      cm_xta_lmrcb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:19 2015

     Prg:      aj

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta_app.h"
#include "cm_ftha.h"
#include "lmr.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#include "cm_xta.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta_app.x"
#include "cm_ftha.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "cm_xta.x"


/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lmrcb.c
*
*/

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLmrCfgCfm
(
Pst     *pst,          /* post structure */
MrMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 cmXtaSmMiLmrCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
MrMngmt *cfm;          /* configuration */
#endif
{
   TRC2(cmXtaSmMiLmrCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLmrCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLMRCFGCFM;

   cmXtaUtlLmrSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLmrCfgCfm */


/*
*
*       Fun:   Control Confirm
*
*       Desc:  This function is used by to present control confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lmrcb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLmrCntrlCfm
(
Pst     *pst,          /* post structure */
MrMngmt *cfm           /* control */
)
#else
PUBLIC S16 cmXtaSmMiLmrCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
MrMngmt *cfm;          /* control */
#endif
{

   TRC2(cmXtaSmMiLmrCntrlCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLmrCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLMRCNTRLCFM;

   cmXtaUtlLmrSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLmrCntrlCfm */


/*
*
*       Fun:   cmXtaUtlLmrSendMsg 
*
*       Desc:  This function is used to save the message to 
*              CM XTA FTHA message queue.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lmrcb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLmrSendMsg
(
Pst         *pst,
MrMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 cmXtaUtlLmrSendMsg(pst, cfm, mBuf)
Pst         *pst;
MrMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CmXtaFthaMsgQElm *mrMsg;

   TRC3(cmXtaUtlLmrSendMsg)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLmrSendMsg(): txnId(%ld)\n", cfm->hdr.transId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   del = TRUE;
   /*-- Do not delete the txn cb if it is partial confirmation --*/
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      del = FALSE;

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
   {
      /*-- No associated test case found, spurious 
        message, drop it --*/
      CMXTA_DBG_INFO((_cmxtap, "cmXtaUtlLmrSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
      if (pst->event == EVTLMRTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLMRTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLMRSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLMRSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLMRTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
      CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLmrSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
      /*-- Drop the message --*/
      if (pst->event == EVTLMRTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SIP memory data --*/
   mrMsg = NULLP;
   CMXTA_ALLOC(&mrMsg, sizeof (CmXtaFthaMsgQElm));
   if (mrMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaUtlLmrSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLMRTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(mrMsg->u.mrMngmt), (U8 *)cfm, sizeof(MrMngmt));
   qElm.data = (Void *)mrMsg;
   qElm.msgFreeFun = cmXtaUtlLmrCb;

   /*-- Test case found, queue the message for the tcCb --*/
   /*-- Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of cmXtaUtlLmrSendMsg() */

/*
*
*       Fun:   cmXtaUtlLmrCb 
*
*       Desc:  This function is used to free the message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lmrcb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLmrCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 cmXtaUtlLmrCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CmXtaFthaMsgQElm  *mrMsg;

   TRC2(cmXtaUtlLmrCb)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLmrCb(): \n"));

   mrMsg = (CmXtaFthaMsgQElm *)qElm->data;

   if (mrMsg != NULLP)
   {
      CMXTA_FREE(mrMsg, sizeof (CmXtaFthaMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of cmXtaUtlLsgCb() */


/********************************************************************30**

         End of file:     cm_xta_lmrcb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:19 2015

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
/main/1      ----      aj      1. main release
*********************************************************************91*/
