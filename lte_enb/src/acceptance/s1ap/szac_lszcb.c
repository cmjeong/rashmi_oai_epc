
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszcb.c

     Sid:      szac_lszcb.c@@/main/3 - Mon Jan 10 22:15:52 2011

     Prg:     pk 
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

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for MGCP */
#include "sct.h"           /* SB (SCTP) layer */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */

#include "cm_pasn.h"
#include "cm_xta.h" 

/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "sz.h"            /* defines and macros for MGCP */
#include "szt.h"            /* defines and macros for MGCP */
#include "szac_acc.h"        /* defines for MGCP acceptance tests */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SCTP Interface Structures */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for MGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "sb_mtu.x"
#include "lsb.x"
#include "sb.x"
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x" 
#include "sz.x"            /* typedefs for MGCP */
#include "szac_lsz.x"
#include "szac_acc.x"        /* typedefs for MGCP acceptance tests */

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
*       File:  szac_lszcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLszCfgCfm
(
Pst     *pst,          /* post structure */
SzMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLszCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
SzMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLszCfgCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLSZCFGCFM;

   SmMiLszSendMsg(pst, cfm, NULLP);
 
   RETVALUE(ROK);
} /* end of SmMiLszCfgCfm */
 
 
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
*       File:  szac_lszcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLszCntrlCfm
(
Pst     *pst,          /* post structure */
SzMngmt *cfm           /* control */
)
#else
PUBLIC S16 SmMiLszCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
SzMngmt *cfm;          /* control */
#endif
{
 
   TRC2(SmMiLszCntrlCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLSZCNTRLCFM;

   SmMiLszSendMsg(pst, cfm, NULLP);
 
   RETVALUE(ROK);
} /* end of SmMiLszCntrlCfm */
 
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
*       File:  szac_lszcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLszStaInd
(
Pst     *pst,           /* post structure */
SzMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 SmMiLszStaInd(pst, usta)
Pst     *pst;           /* post structure */
SzMngmt *usta;          /* unsolicited status */
#endif
{
 
   TRC2(SmMiLszStaInd);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszStaInd(): txnId(%d)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszStaInd(): txnId(%ld)\n", usta->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLSZSTAIND;

   SmMiLszSendMsg(pst, usta, NULLP);
 
   RETVALUE(ROK);
} /* end of SmMiLszStaInd */
 
 
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
*       File:  szac_lszcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLszTrcInd
(
Pst *pst,               /* post structure */
SzMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 SmMiLszTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
SzMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(SmMiLszTrcInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszTrcInd(): txnId(%d)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLSZTRCIND;

   SmMiLszSendMsg(pst, trc, mBuf);
 
   RETVALUE(ROK);
} /* end of SmMiLszTrcInd */
 
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
*       File:  szac_lszcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLszStsCfm
(
Pst       *pst,         /* post structure */
SzMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 SmMiLszStsCfm(pst, sts)
Pst       *pst;         /* post structure */
SzMngmt   *sts;         /* confirmed statistics */
#endif
{
   TRC2(SmMiLszStsCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszStsCfm(): txnId(%d)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLSZSTSCFM;

   SmMiLszSendMsg(pst, sts, NULLP);
 
   RETVALUE(ROK);
} /* end of SmMiLszStsCfm */
 
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
*       File:  szac_lszcb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLszStaCfm
(
Pst     *pst,           /* post structure */
SzMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 SmMiLszStaCfm(pst, sta)
Pst     *pst;           /* post structure */
SzMngmt *sta;            /* confirmed status */
#endif
{
   TRC2(SmMiLszStaCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszStaCfm(): txnId(%d)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#endif
 
   /*-- Update Event --*/
   pst->event = EVTLSZSTACFM;

   SmMiLszSendMsg(pst, sta, NULLP);
 
   RETVALUE(ROK);
} /* end of SmMiLszStaCfm */
 
 
/*
*
*       Fun:   SmMiLszSendMsg 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  szac_lszcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLszSendMsg
(
Pst         *pst,
SzMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLszSendMsg(pst, cfm, mBuf)
Pst         *pst;
SzMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
 
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   SzAccMsgQElm *szMsg;
 
   TRC3(SmMiLszSendMsg);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLszSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#endif
 
   CMXTA_ZERO(&qElm, sizeof(qElm));

   del = TRUE;

   /*This change is done so that we get sta ind*/
   /*!!! Not sure about the side effects of these changes*/
   if(!(pst->event == EVTLSZTRCIND) && !(pst->event == EVTLSZSTAIND))
   {
      /*-- Do not delete the txn cb if it is partial confirmation --*/
      if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
         del = FALSE;

      /*-- Find the associated test case using the txnId --*/
      if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
      {
         /*-- No associated test case found, spurious message, drop it --*/

#ifdef ALIGN_64BIT
         CMXTA_DBG_INFO((_cmxtap, "SmMiLszSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#else
         CMXTA_DBG_INFO((_cmxtap, "SmMiLszSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
#endif

         /*-- Drop the message --*/
         if (pst->event == EVTLSZTRCIND)
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
      if ((tcCb = szAcLszTstCbFind()) == NULLP)
      {
         /*-- No associated test case found, spurious message, drop it --*/

         /*-- szac_ENHANCE:  Update debug prints --*/
         CMXTA_DBG_INFO((_cmxtap, "Msg dropped szac_ENHANCE: may be Sts Ind etc...\n"));

         /*-- Drop the message --*/
         if (pst->event == EVTLSZTRCIND)
         {
            CMXTA_FREEMBUF(mBuf);
         }

         RETVALUE(ROK);
      }

   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((pst->event != EVTLSZTRCIND) &&
       (pst->event != EVTLSZSTAIND) && 
       (tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLSZTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLSZSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLSZSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLSZTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "SmMiLszSendMsg(): txnId(%d) dropping alarm/trace\n", cfm->hdr.transId));
#else
      CMXTA_DBG_PARAM((_cmxtap, "SmMiLszSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
#endif

      /*-- Drop the message --*/
      if (pst->event == EVTLSZTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SZ memory data --*/
   szMsg = NULLP;
   CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
   if (szMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLszSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLSZTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(szMsg->u.szMngmt), (U8 *)cfm, sizeof(SzMngmt));
   qElm.data = (Void *)szMsg;
   qElm.msgFreeFun = szAcUtlLszCb;

 
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
} /* End of SmMiLszSendMsg() */
/*
*
*       Fun:   szAcLszTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_sztcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  szAcLszTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  szAcLszTstCbFind ()
#endif
{
   TRC2(szAcLszTstCbFind);
 
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
} /* End of szAcLszTstCbFind */



/*
*
*       Fun:   szAcUtlLszCb 
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
PUBLIC S16 szAcUtlLszCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 szAcUtlLszCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   SzAccMsgQElm *szMsg;

   TRC2(szAcUtlLszCb);

   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlLszCb(): \n"));

   szMsg = (SzAccMsgQElm *)qElm->data;

   if(qElm->pst.event ==  EVTLSZSTACFM)
   {
      if( szMsg->u.szMngmt.hdr.elmId.elmnt == STSZPEER )
      {
         CMXTA_FREE((szMsg->u.szMngmt.u.ssta.s.peer.peerStaInfo), (sizeof(SzPeerStaInfo) * szMsg->u.szMngmt.u.ssta.s.peer.nmbPeer)); 
      }
   }
   if (szMsg != NULLP)
   {
      if(szMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(szMsg->mBuf);

      CMXTA_FREE(szMsg, sizeof (SzAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of szAcUtlLszCb() */

/********************************************************************30**

         End of file:     szac_lszcb.c@@/main/3 - Mon Jan 10 22:15:52 2011

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   va    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
