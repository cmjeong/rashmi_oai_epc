
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_legcb.c

     Sid:      egac_legcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:34 2015

     Prg:     an 
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "leg.h"           /* layer management defines for MGCP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#include "cm_xta.h" 

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for MGCP */
#include "egt.h"            /* defines and macros for MGCP */
#include "egac_acc.h"        /* defines for MGCP acceptance tests */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "egt.x"           /* SCTP Interface Structures */
#include "leg.x"           /* layer management typedefs for MGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for MGCP */
#include "egac_leg.x"
#include "egac_acc.x"        /* typedefs for MGCP acceptance tests */

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
*       File:  egac_legcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcSmMiLegCfgCfm
(
Pst     *pst,          /* post structure */
EgMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 egAcSmMiLegCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
EgMngmt *cfm;          /* configuration */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLegCfgCfm);

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLEGCFGCFM;

   SmMiLegSendMsg(pst, cfm, NULLP);
 
   RETVALUE(ROK);
} /* end of egAcSmMiLegCfgCfm */
 
 
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
*       File:  egac_legcb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcSmMiLegCntrlCfm
(
Pst     *pst,          /* post structure */
EgMngmt *cfm           /* control */
)
#else
PUBLIC S16 egAcSmMiLegCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
EgMngmt *cfm;          /* control */
#endif
{
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLegCntrlCfm);

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLEGCNTRLCFM;

   SmMiLegSendMsg(pst, cfm, NULLP);
 
   RETVALUE(ROK);
} /* end of egAcSmMiLegCntrlCfm */
 
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
*       File:  egac_legcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcSmMiLegStaInd
(
Pst     *pst,           /* post structure */
EgMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 egAcSmMiLegStaInd(pst, usta)
Pst     *pst;           /* post structure */
EgMngmt *usta;          /* unsolicited status */
#endif
{
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLegStaInd);

#ifdef LMINT3 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegStaInd(): txnId(%d)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegStaInd(): txnId(%ld)\n", usta->hdr.transId));
#endif
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLEGSTAIND;

   SmMiLegSendMsg(pst, usta, NULLP);
 
   RETVALUE(ROK);
} /* end of egAcSmMiLegStaInd */
 
 
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
*       File:  egac_legcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcSmMiLegTrcInd
(
Pst *pst,               /* post structure */
EgMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 egAcSmMiLegTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
EgMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLegTrcInd);

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegTrcInd(): txnId(%d)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#endif
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLEGTRCIND;

   SmMiLegSendMsg(pst, trc, mBuf);
 
   RETVALUE(ROK);
} /* end of egAcSmMiLegTrcInd */
 
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
*       File:  egac_legcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcSmMiLegStsCfm
(
Pst       *pst,         /* post structure */
EgMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 egAcSmMiLegStsCfm(pst, sts)
Pst       *pst;         /* post structure */
EgMngmt   *sts;         /* confirmed statistics */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLegStsCfm);

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegStsCfm(): txnId(%d)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#endif
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLEGSTSCFM;

   SmMiLegSendMsg(pst, sts, NULLP);
 
   RETVALUE(ROK);
} /* end of egAcSmMiLegStsCfm */
 
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
*       File:  egac_legcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcSmMiLegStaCfm
(
Pst     *pst,           /* post structure */
EgMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 egAcSmMiLegStaCfm(pst, sta)
Pst     *pst;           /* post structure */
EgMngmt *sta;            /* confirmed status */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLegStaCfm);

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegStaCfm(): txnId(%d)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLegStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#endif
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLEGSTACFM;

   SmMiLegSendMsg(pst, sta, NULLP);
 
   RETVALUE(ROK);
} /* end of egAcSmMiLegStaCfm */
 
 
/*
*
*       Fun:   SmMiLegSendMsg 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_legcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLegSendMsg
(
Pst         *pst,
EgMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLegSendMsg(pst, cfm, mBuf)
Pst         *pst;
EgMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
 
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egMsg;
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(SmMiLegSendMsg);

#ifdef LMINT3 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLegSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLegSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#endif
#endif
 
   CMXTA_ZERO(&qElm, sizeof(qElm));

   del = TRUE;

   /*This change is done so that we get sta ind*/
   /*!!! Not sure about the side effects of these changes*/
   if(!(pst->event == EVTLEGTRCIND) && !(pst->event == EVTLEGSTAIND))
   {
      /*-- Do not delete the txn cb if it is partial confirmation --*/
      if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
         del = FALSE;

#ifdef LMINT3
      /*-- Find the associated test case using the txnId --*/
      if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
      {
         /*-- No associated test case found, spurious message, drop it --*/

#ifdef ALIGN_64BIT
         CMXTA_DBG_INFO((_cmxtap, "SmMiLegSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#else
         CMXTA_DBG_INFO((_cmxtap, "SmMiLegSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
#endif

         /*-- Drop the message --*/
         if (pst->event == EVTLEGTRCIND)
         {
            CMXTA_FREEMBUF(mBuf);
         }

         RETVALUE(CMXTA_ERR_NONE);
      }
#endif
   }
   else
   {

      /*This change is done so that we get sta ind*/
      /*!!! Not sure about the side effects of these changes*/
         /*-- Find the associated test case */
      if ((tcCb = egAcLegTstCbFind()) == NULLP)
      {
         /*-- No associated test case found, spurious message, drop it --*/

         /*-- egac_ENHANCE:  Update debug prints --*/
         CMXTA_DBG_INFO((_cmxtap, "Msg dropped egac_ENHANCE: may be Sts Ind etc...\n"));
         RETVALUE(ROK);
      }

   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((pst->event != EVTLEGTRCIND) &&
       (pst->event != EVTLEGSTAIND) &&
       (tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLEGTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLEGSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLEGSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLEGTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
#ifdef LMINT3
#ifdef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "SmMiLegSendMsg(): txnId(%d) dropping alarm/trace\n", cfm->hdr.transId));
#else
      CMXTA_DBG_PARAM((_cmxtap, "SmMiLegSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
#endif
#endif

      /*-- Drop the message --*/
      if (pst->event == EVTLEGTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SZ memory data --*/
   egMsg = NULLP;
   CMXTA_ALLOC(&egMsg, sizeof (EgAccMsgQElm));
   if (egMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLegSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLEGTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(egMsg->u.egMngmt), (U8 *)cfm, sizeof(EgMngmt));
   qElm.data = (Void *)egMsg;
   qElm.msgFreeFun = egAcUtlLegCb;

 
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
} /* End of SmMiLegSendMsg() */
/*
*
*       Fun:   egAcLegTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  egAcLegTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  egAcLegTstCbFind ()
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcLegTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of egAcLegTstCbFind */



/*
*
*       Fun:   egAcUtlLegCb 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcUtlLegCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 egAcUtlLegCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   EgAccMsgQElm *egMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlLegCb);

   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlLegCb(): \n"));

   egMsg = (EgAccMsgQElm *)qElm->data;

   if (egMsg != NULLP)
   {
      if(egMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(egMsg->mBuf);

      CMXTA_FREE(egMsg, sizeof (EgAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of egAcUtlLegCb() */

/********************************************************************30**

         End of file:     egac_legcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:34 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix
                                     TRACE5 macro related issue
/main/3     eg004.201 magnihotri  1. Header files added for eGTP-C PSF
*********************************************************************91*/
