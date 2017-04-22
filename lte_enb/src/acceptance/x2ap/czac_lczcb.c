
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_lczcb.c

     Sid:      czac_lczcb.c@@/main/2 - Tue Aug 30 18:35:47 2011

     Prg:     sy 
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "lcz.h"           /* layer management defines for MGCP */
#include "sct.h"           /* SB (SCTP) layer */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 

#include "cz.h"            /* defines and macros for MGCP */
#include "czt.h"            /* defines and macros for MGCP */
#include "czac_acc.h"        /* defines for MGCP acceptance tests */

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
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* SCTP Interface Structures */
#include "lcz.x"           /* layer management typedefs for MGCP */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for MGCP */
#include "czac_lcz.x"
#include "czac_acc.x"        /* typedefs for MGCP acceptance tests */

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
*       File:  czac_lczcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLczCfgCfm
(
Pst     *pst,          /* post structure */
CzMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLczCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
CzMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLczCfgCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLCZCFGCFM;

   SmMiLczSendMsg(pst, cfm, NULLP);

   CMXTA_FREE(cfm, sizeof (CzMngmt));

   RETVALUE(ROK);
} /* end of SmMiLczCfgCfm */
 
 
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
*       File:  czac_lczcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLczCntrlCfm
(
Pst     *pst,          /* post structure */
CzMngmt *cfm           /* control */
)
#else
PUBLIC S16 SmMiLczCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
CzMngmt *cfm;          /* control */
#endif
{
 
   TRC2(SmMiLczCntrlCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLCZCNTRLCFM;

   SmMiLczSendMsg(pst, cfm, NULLP);
   CMXTA_FREE(cfm, sizeof (CzMngmt));
 
   RETVALUE(ROK);
} /* end of SmMiLczCntrlCfm */
 
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
*       File:  czac_lczcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLczStaInd
(
Pst     *pst,           /* post structure */
CzMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 SmMiLczStaInd(pst, usta)
Pst     *pst;           /* post structure */
CzMngmt *usta;          /* unsolicited status */
#endif
{
 
   TRC2(SmMiLczStaInd);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczStaInd(): txnId(%d)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczStaInd(): txnId(%ld)\n", usta->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLCZSTAIND;

   SmMiLczSendMsg(pst, usta, NULLP);

   CMXTA_FREE(usta, sizeof(CzMngmt));
 
   RETVALUE(ROK);
} /* end of SmMiLczStaInd */
 
 
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
*       File:  czac_lczcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLczTrcInd
(
Pst *pst,               /* post structure */
CzMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 SmMiLczTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
CzMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(SmMiLczTrcInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczTrcInd(): txnId(%d)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLCZTRCIND;

   SmMiLczSendMsg(pst, trc, mBuf);
   /* cz001.301 : purify fix */
   CMXTA_FREE(trc, sizeof(CzMngmt));
 
   RETVALUE(ROK);
} /* end of SmMiLczTrcInd */
 
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
*       File:  czac_lczcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLczStsCfm
(
Pst       *pst,         /* post structure */
CzMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 SmMiLczStsCfm(pst ,sts)
Pst       *pst;         /* post structure */
CzMngmt   *sts;         /* confirmed statistics */
#endif
{
   TRC2(SmMiLczStsCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczStsCfm(): txnId(%d)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLCZSTSCFM;

   SmMiLczSendMsg(pst, sts, NULLP);
   CMXTA_FREE(sts, sizeof(CzMngmt));
 
   RETVALUE(ROK);
} /* end of SmMiLczStsCfm */
 
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
*       File:  czac_lczcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLczStaCfm
(
Pst     *pst,           /* post structure */
CzMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 SmMiLczStaCfm(pst, sta)
Pst     *pst;           /* post structure */
CzMngmt *sta;            /* confirmed status */
#endif
{
   TRC2(SmMiLczStaCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczStaCfm(): txnId(%d)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLCZSTACFM;

   SmMiLczSendMsg(pst, sta, NULLP);
   
   if(sta->hdr.elmId.elmnt == STCZSID)
   {
      CMXTA_FREE(sta->t.ssta.s.sysId.ptNmb, LCZ_MAX_PT_NUM_SIZE);
   }
   CMXTA_FREE(sta, sizeof (CzMngmt));
 
   RETVALUE(ROK);
} /* end of SmMiLczStaCfm */
 
 
/*
*
*       Fun:   SmMiLczSendMsg 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  czac_lczcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLczSendMsg
(
Pst         *pst,
CzMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLczSendMsg(pst, cfm, mBuf)
Pst         *pst;
CzMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
 
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;
 
   TRC3(SmMiLczSendMsg);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLczSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#endif
 
   CMXTA_ZERO(&qElm, sizeof(qElm));

   del = TRUE;

   /*This change is done so that we get sta ind*/
   /*!!! Not sure about the side effects of these changes*/
   if(!(pst->event == EVTLCZTRCIND) && !(pst->event == EVTLCZSTAIND))
   {
      /*-- Do not delete the txn cb if it is partial confirmation --*/
      if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
         del = FALSE;

      /*-- Find the associated test case using the txnId --*/
      if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
      {
         /*-- No associated test case found, spurious message, drop it --*/

#ifdef ALIGN_64BIT
         CMXTA_DBG_INFO((_cmxtap, "SmMiLczSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#else
         CMXTA_DBG_INFO((_cmxtap, "SmMiLczSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
#endif

         /*-- Drop the message --*/
         if (pst->event == EVTLCZTRCIND)
         {
            CMXTA_FREEMBUF(mBuf);
         }

         RETVALUE(CMXTA_ERR_NONE);
      }
   }
   else
   {

      /*This change is done so that we get sta ind*/
      /*!!! Not sure about the side effects of these changes*/
         /*-- Find the associated test case */
      if ((tcCb = czAcLczTstCbFind()) == NULLP)
      {
         /*-- No associated test case found, spurious message, drop it --*/

         /*-- czac_ENHANCE:  Update debug prints --*/
         CMXTA_DBG_INFO((_cmxtap, "Msg dropped czac_ENHANCE: may be Sts Ind etc...\n"));

         /*-- Drop the message --*/
         if (pst->event == EVTLCZTRCIND)
         {
            CMXTA_FREEMBUF(mBuf);
         }

         RETVALUE(ROK);
      }

   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((pst->event != EVTLCZTRCIND) &&
       (pst->event != EVTLCZSTAIND) && 
       (tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLCZTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLCZSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLCZSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLCZTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "SmMiLczSendMsg(): txnId(%d) dropping alarm/trace\n", cfm->hdr.transId));
#else
      CMXTA_DBG_PARAM((_cmxtap, "SmMiLczSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
#endif

      /*-- Drop the message --*/
      if (pst->event == EVTLCZTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate CZ memory data --*/
   czMsg = NULLP;
   CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
   if (czMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLczSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLCZTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(czMsg->u.czMngmt), (U8 *)cfm, sizeof(CzMngmt));
   qElm.data = (Void *)czMsg;
   qElm.msgFreeFun = czAcUtlLczCb;

 
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
} /* End of SmMiLczSendMsg() */
/*
*
*       Fun:   czAcLczTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_cztcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  czAcLczTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  czAcLczTstCbFind ()
#endif
{
   TRC2(czAcLczTstCbFind);
 
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
} /* End of czAcLczTstCbFind */



/*
*
*       Fun:   czAcUtlLczCb 
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
PUBLIC S16 czAcUtlLczCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 czAcUtlLczCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CzAccMsgQElm *czMsg;

   TRC2(czAcUtlLczCb);

   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlLczCb(): \n"));

   czMsg = (CzAccMsgQElm *)qElm->data;

   if(qElm->pst.event ==  EVTLCZSTACFM)
   {
      if( czMsg->u.czMngmt.hdr.elmId.elmnt == STCZPEER )
      {
         CMXTA_FREE((czMsg->u.czMngmt.t.ssta.s.peerSta.peerStaInfo), (sizeof(CzPeerStaInfo) * czMsg->u.czMngmt.t.ssta.s.peerSta.nmbPeer)); 
      }
   }
   if (czMsg != NULLP)
   {
      if(czMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(czMsg->mBuf);

      CMXTA_FREE(czMsg, sizeof (CzAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of czAcUtlLczCb() */

/********************************************************************30**

         End of file:     czac_lczcb.c@@/main/2 - Tue Aug 30 18:35:47 2011

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
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
