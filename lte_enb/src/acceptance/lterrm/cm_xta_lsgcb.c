
/********************************************************************20**

     Name:     cm_xta_lsgcb.c 

     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     cm_xta_lsgcb.c

     Sid:      cm_xta_lsgcb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:21 2015

     Prg:      sm

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
*       File:  cm_xta_lsgcb.c
*
*/

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLsgCfgCfm
(
Pst     *pst,          /* post structure */
SgMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 cmXtaSmMiLsgCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
SgMngmt *cfm;          /* configuration */
#endif
{
   TRC2(cmXtaSmMiLsgCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLsgCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSGCFGCFM;

   cmXtaUtlLsgSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLsgCfgCfm */


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
*       File:  cm_xta_lsgcb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLsgCntrlCfm
(
Pst     *pst,          /* post structure */
SgMngmt *cfm           /* control */
)
#else
PUBLIC S16 cmXtaSmMiLsgCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
SgMngmt *cfm;          /* control */
#endif
{

   TRC2(cmXtaSmMiLsgCntrlCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLsgCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSGCNTRLCFM;

   cmXtaUtlLsgSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLsgCntrlCfm */


/*
*
*       Fun:   Status Indication
*
*       Desc:  This function is used by to present  unsolicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lsocb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLsgStaInd
(
Pst     *pst,           /* post structure */
SgMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 cmXtaSmMiLsgStaInd(pst, usta)
Pst     *pst;           /* post structure */
SgMngmt *usta;          /* unsolicited status */
#endif
{

   TRC2(cmXtaSmMiLsgStaInd)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLsgStaInd(): txnId(%ld)\n", usta->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSGSTAIND;

   cmXtaUtlLsgSendMsg(pst, usta, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLsgStaInd */



/*
*
*       Fun:   Trace Indication
*
*       Desc:  This function is used to present trace
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lsocb.c
*
*/

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLsgTrcInd
(
Pst *pst,               /* post structure */
SgMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmXtaSmMiLsgTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
SgMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(soAcSmMiLsoTrcInd)
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLsgTrcInd(): txnId(%ld)\n", trc->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSGTRCIND;

   cmXtaUtlLsgSendMsg(pst, trc, mBuf);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLsgTrcInd */


/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  This function is used to present solicited statistics 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lsocb.c
*
*/

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLsgStsCfm
(
Pst       *pst,         /* post structure */
SgMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 cmXtaSmMiLsgStsCfm(pst, sts)
Pst       *pst;         /* post structure */
SgMngmt   *sts;         /* confirmed statistics */
#endif
{
   TRC2(cmXtaSmMiLsgStsCfm)
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLsgStsCfm(): txnId(%ld)\n", sts->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSGSTSCFM;

   cmXtaUtlLsgSendMsg(pst, sts, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLsgStsCfm */


/*
*
*       Fun:   Status Confirm
*
*       Desc:  This function is used to present solicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lsocb.c
*
*/

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLsgStaCfm
(
Pst     *pst,           /* post structure */
SgMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 cmXtaSmMiLsgStaCfm(pst, sta)
Pst     *pst;           /* post structure */
SgMngmt *sta;            /* confirmed status */
#endif
{
   TRC2(cmXtaSmMiLsgStaCfm)
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLsgStaCfm(): txnId(%ld)\n", sta->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSGSTACFM;

   cmXtaUtlLsgSendMsg(pst, sta, NULLP);

   RETVALUE(ROK);
} /* end of cmXtaSmMiLsgStaCfm */


/*
*
*       Fun:   cmXtaUtlLsgSendMsg 
*
*       Desc:  This function is used to save the message to 
*              CM XTA FTHA message queue.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lsocb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLsgSendMsg
(
Pst         *pst,
SgMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 cmXtaUtlLsgSendMsg(pst, cfm, mBuf)
Pst         *pst;
SgMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CmXtaFthaMsgQElm *sgMsg;

   TRC3(cmXtaUtlLsgSendMsg)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLsgSendMsg(): txnId(%ld)\n", cfm->hdr.transId));

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
      CMXTA_DBG_INFO((_cmxtap, "cmXtaUtlLsgSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
      if (pst->event == EVTLSGTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
#if 0
   if ((tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);
#endif

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLSGTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLSGSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLSGSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLSGTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
      CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLsgSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
      /*-- Drop the message --*/
      if (pst->event == EVTLSGTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SIP memory data --*/
   sgMsg = NULLP;
   CMXTA_ALLOC(&sgMsg, sizeof (CmXtaFthaMsgQElm));
   if (sgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaUtlLsgSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLSGTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(sgMsg->u.sgMngmt), (U8 *)cfm, sizeof(SgMngmt));
   qElm.data = (Void *)sgMsg;
   qElm.msgFreeFun = cmXtaUtlLsgCb;

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
} /* End of cmXtaUtlLsgSendMsg() */

/*
*
*       Fun:   cmXtaUtlLsgCb 
*
*       Desc:  This function is used to free the message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lsgcb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLsgCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 cmXtaUtlLsgCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CmXtaFthaMsgQElm  *sgMsg;

   TRC2(cmXtaUtlLsgCb)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLsgCb(): \n"));

   sgMsg = (CmXtaFthaMsgQElm *)qElm->data;

   if (sgMsg != NULLP)
   {
      CMXTA_FREE(sgMsg, sizeof (CmXtaFthaMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of cmXtaUtlLsgCb() */


/********************************************************************30**

         End of file:     cm_xta_lsgcb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:21 2015

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
