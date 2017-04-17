
/********************************************************************20**

     Name:     cm_xta_lshcb.c 
     Type:     C source file

     Desc:     
               
     File:     cm_xta_lshcb.c

     Sid:      cm_xta_lshcb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:23 2015

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
 *       Fun:    cmXtaSmMiLshCfgCfm - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLshCfgCfm
(
Pst         *pst,
ShMngmt     *cfg
)
#else
PUBLIC S16 cmXtaSmMiLshCfgCfm (pst, cfg)
Pst         *pst;
ShMngmt     *cfg;
#endif /* ANSI */
{

   TRC3(cmXtaSmMiLshCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshCfgCfm(): txnId(%ld)\n", cfg->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSHCFGCFM;

   cmXtaLshSendMsg(pst, cfg, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLshCfgCfm() */

/*
 *
 *       Fun:    cmXtaSmMiLshStsCfm - statistics confirm
 *
 *       Desc:   prints the statistics confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLshStsCfm
(
Pst                  *pst,
ShMngmt               *sts
)
#else
PUBLIC S16 cmXtaSmMiLshStsCfm(pst, sts)
Pst                  *pst;
ShMngmt               *sts;
#endif /* ANSI */
{
   TRC3(cmXtaSmMiLshStsCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshStsCfm(): txnId(%ld)\n", sts->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSHSTSCFM;

   /*cmXtaLshSendMsg(pst, sts, NULLP);*/

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLshStsCfm() */

/*
 *
 *       Fun:    cmXtaSmMiLshStaCfm - status confirm
 *
 *       Desc:   prints the status confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLshStaCfm
(
Pst                  *pst,
ShMngmt               *ssta
)
#else
PUBLIC S16 cmXtaSmMiLshStaCfm(pst, ssta)
Pst                  *pst;
ShMngmt               *ssta;
#endif /* ANSI */
{

   TRC3(cmXtaSmMiLshStaCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshStaCfm(): txnId(%ld)\n", ssta->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSHSTACFM;

   cmXtaLshSendMsg(pst, ssta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLshStaCfm() */

/*
 *
 *       Fun:    cmXtaSmMiLshCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLshCntrlCfm
(
Pst         *pst,
ShMngmt     *cntrl
)
#else
PUBLIC S16 cmXtaSmMiLshCntrlCfm(pst, cntrl)
Pst         *pst;
ShMngmt     *cntrl;
#endif /* ANSI */
{
   TRC3(cmXtaSmMiLshCntrlCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshCntrlCfm(): txnId(%ld)\n", cntrl->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSHCNTRLCFM;

   cmXtaLshSendMsg(pst, cntrl, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLshCntrlCfm() */

/*
 *
 *       Fun:    cmXtaSmMiLshStaInd - status indication
 *
 *       Desc:   prints the status indication (alarm)
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLshStaInd
(
Pst         *pst,
ShMngmt     *usta
)
#else
PUBLIC S16 cmXtaSmMiLshStaInd(pst, usta)
Pst         *pst;
ShMngmt     *usta;
#endif /* ANSI */
{
   TRC3(cmXtaSmMiLshStaInd)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshStaInd(): txnId(%ld)\n", usta->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSHSTAIND;

   cmXtaLshSendMsg(pst, usta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLshStaInd() */

/*
 *
 *       Fun:    cmXtaSmMiLshTrcInd - trace indication
 *
 *       Desc:   prints the trace indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaSmMiLshTrcInd
(
Pst                  *pst,
ShMngmt               *trc
)
#else
PUBLIC S16 cmXtaSmMiLshTrcInd(pst, trc)
Pst                  *pst;
ShMngmt               *trc;
#endif /* ANSI */
{
   TRC3(cmXtaSmMiLshTrcInd)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshTrcInd(): txnId(%ld)\n", trc->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLSHTRCIND;


   cmXtaLshSendMsg(pst, trc, NULLP);
   RETVALUE(CMXTA_ERR_NONE);

} /* end of cmXtaSmMiLshTrcInd() */

/*
 *
 *       Fun:    cmXtaLshSendMsg - trace indication
 *
 *       Desc:   prints the trace indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmXtaLshSendMsg
(
Pst         *pst,
ShMngmt     *cfm,
Buffer     *mBuf
)
#else
PUBLIC S16 cmXtaLshSendMsg(pst, cfm, mBuf)
Pst         *pst;
ShMngmt     *cfm;
Buffer     *mBuf;
#endif /* ANSI */
{
   Bool del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CmXtaFthaMsgQElm *shMsg;

   TRC3(cmXtaUtlLshSendMsg)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLshSendMsg(): txnId(%ld)\n", cfm->hdr.transId));

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
      if (pst->event == EVTLSHTRCIND)
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
       (pst->event == EVTLSHTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLSHSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLSHSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLSHTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
      CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLshSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
      /*-- Drop the message --*/
      if (pst->event == EVTLSHTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SIP memory data --*/
   shMsg = NULLP;
   CMXTA_ALLOC(&shMsg, sizeof (CmXtaFthaMsgQElm));
   if (shMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaUtlLshSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLSHTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(shMsg->u.shMngmt), (U8 *)cfm, sizeof(ShMngmt));
   qElm.data = (Void *)shMsg;
   qElm.msgFreeFun = cmXtaUtlLshCb;

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

  
} /* end of cmXtaLshSendMsg() */

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
PUBLIC S16 cmXtaUtlLshCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 cmXtaUtlLshCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CmXtaFthaMsgQElm  *shMsg;

   TRC2(cmXtaUtlLsgCb)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLsgCb(): \n"));

   shMsg = (CmXtaFthaMsgQElm *)qElm->data;

   if (shMsg != NULLP)
   {
      CMXTA_FREE(shMsg, sizeof (CmXtaFthaMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of cmXtaUtlLsgCb() */

/********************************************************************30**

         End of file:     cm_xta_lshcb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:23 2015

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
------------ -------- ---- ----------------------------------------------
/main/1      ----      aj      1. main release
/main/2      ----      sy      2. GCP 2.1 release
*********************************************************************91*/
