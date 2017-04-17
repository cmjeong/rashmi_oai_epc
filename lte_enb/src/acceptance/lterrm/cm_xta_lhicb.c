
/********************************************************************20**

     Name:     TCP UDP Convergence Layer Sample Stack Manager

     Type:     C source file

     Desc:     Sample code for Management Interface primitives supplied
               by TRILLIUM

     File:     cm_xta_lhicb.c

     Sid:      cm_xta_lhicb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:19 2015

     Prg:      ve

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

#include "cm_ftha.h"
#include "lhi.h"
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

#include "cm_ftha.x"
#include "lhi.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "cm_xta.x"


EXTERN S16 cmXtaUtlLhiSendMsg ARGS((Pst *pst, HiMngmt *cfm, Buffer *mBuf));
EXTERN S16 cmXtaUtlLhiCb ARGS((CmXtaMsgQElm *qElm));
/*
*     interface functions to layer management service user
*/
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
*       File:  cm_xta_lhicb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLhiCfgCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 cmXtaSmMiLhiCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
   TRC2(cmXtaSmMiLhiCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLhiCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLHICFGCFM;

   cmXtaUtlLhiSendMsg(pst, cfm, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLhiCfgCfm */


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
*       File:  cm_xta_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLhiCntrlCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* control */
)
#else
PUBLIC S16 cmXtaSmMiLhiCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* control */
#endif
{
   TRC2(cmXtaSmMiLhiCntrlCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLhiCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLHICNTRLCFM;

   cmXtaUtlLhiSendMsg(pst, cfm, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLhiCntrlCfm */

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
*       File:  cm_xta_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLhiStaInd
(
Pst     *pst,           /* post structure */
HiMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 cmXtaSmMiLhiStaInd(pst, usta)
Pst     *pst;           /* post structure */
HiMngmt *usta;          /* unsolicited status */
#endif
{
   TRC2(cmXtaSmMiLhiStaInd)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLhiStaInd(): txnId(%ld)\n", usta->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLHISTAIND;

   cmXtaUtlLhiSendMsg(pst, usta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLhiStaInd */


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
*       File:  cm_xta_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLhiTrcInd
(
Pst *pst,               /* post structure */
HiMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmXtaSmMiLhiTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
HiMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmXtaSmMiLhiTrcInd)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLhiTrcInd(): txnId(%ld)\n", trc->hdr.transId));

   /*-- Update Event ----*/
   pst->event = EVTLHITRCIND;

   cmXtaUtlLhiSendMsg(pst, trc, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLhiTrcInd */

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
*       File:  cm_xta_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLhiStsCfm
(
Pst       *pst,         /* post structure */
HiMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 cmXtaSmMiLhiStsCfm(pst, sts)
Pst       *pst;         /* post structure */
HiMngmt   *sts;         /* confirmed statistics */
#endif
{
   TRC2(cmXtaSmMiLhiStsCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLhiStsCfm(): txnId(%ld)\n", sts->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLHISTSCFM;

   cmXtaUtlLhiSendMsg(pst, sts, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLhiStsCfm */

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
*       File:  cm_xta_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmXtaSmMiLhiStaCfm
(
Pst     *pst,           /* post structure */
HiMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 cmXtaSmMiLhiStaCfm(pst, sta)
Pst     *pst;           /* post structure */
HiMngmt *sta;            /* confirmed status */
#endif
{
   TRC2(cmXtaSmMiLhiStaCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLhiStaCfm(): txnId(%ld)\n", sta->hdr.transId));

   /*-- Update Event --*/
   pst->event = EVTLHISTACFM;

   cmXtaUtlLhiSendMsg(pst, sta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaSmMiLhiStaCfm */

/*
*
*       Fun:   cmXtaUtlLhiSendMsg 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLhiSendMsg
(
Pst         *pst,
HiMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 cmXtaUtlLhiSendMsg(pst, cfm, mBuf)
Pst         *pst;
HiMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CmXtaFthaMsgQElm *hiMsg;

   TRC3(cmXtaUtlLhiSendMsg)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLhiSendMsg(): txnId(%ld)\n", cfm->hdr.transId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Check if we are in slave mode --*/
   if (cmXtaCb.masterMode == FALSE)
   {
      CMXTA_FREEMBUF(mBuf);
      RETVALUE(CMXTA_ERR_NONE);
   }

   del = TRUE;
   /*-- Do not delete the txn cb if it is partial confirmation --*/
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      del = FALSE;

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
   {
      /*-- No associated test case found, spurious 
        message, drop it --*/
      CMXTA_DBG_INFO((_cmxtap, "cmXtaUtlLhiSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));

      /*-- Drop the message --*/
      if (pst->event == EVTLHITRCIND)
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
       (pst->event == EVTLHITRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLHISTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLHISTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLHITRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
      /*-- Drop the message --*/
      if (pst->event == EVTLHITRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SIP memory data --*/
   hiMsg = NULLP;
   CMXTA_ALLOC(&hiMsg, sizeof (CmXtaFthaMsgQElm));
   if (hiMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaUtlLhiSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(hiMsg->u.hiMngmt), (U8 *)cfm, sizeof(HiMngmt));
   hiMsg->mBuf = mBuf;
   qElm.msgFreeFun = cmXtaUtlLhiCb;
   qElm.data = (Void *)hiMsg;

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(ROK);
} /* End of cmXtaUtlLhiSendMsg() */


/*
*
*       Fun:   cmXtaUtlLhiCb
*
*       Desc:  This function is used to free the message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLhiCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 cmXtaUtlLhiCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CmXtaFthaMsgQElm  *hiMsg;

   TRC2(cmXtaUtlLhiCb);

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlhirCb(): \n"));

   hiMsg = (CmXtaFthaMsgQElm *)qElm->data;

   if (hiMsg != NULLP)
   {
      CMXTA_FREE(hiMsg, sizeof (CmXtaFthaMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of cmXtaUtlLhiCb() */



/********************************************************************30**

           End of file:     cm_xta_lhicb.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:19 2015

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
/main/1      ---      ve         1. initial release PSF-Diam 1.1
*********************************************************************91*/
