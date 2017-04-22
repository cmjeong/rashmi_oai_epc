
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    szac_lhiutil.c

     Sid:      szac_lhiutl.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:24 2013

     Prg:     mn
*********************************************************************21*/


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

#include "sct.h"           /* SB (SCTP) layer */
#include "lsb.h"           /* layer management defines for SCTP */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for S1AP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h"

#include "cm_pasn.h"
#include "sz.h"            /* defines and macros for S1AP */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
#include "szt.h"            /* defines and macros for S1AP */
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for S1AP acceptance tests */
#include <stdlib.h>
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

#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
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
#include "lsz.x"           /* LSZ types */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x"
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */
#include "szac_lhi.x"


/*
*
*       Fun:   szAcUtlLhiSendMsg 
*
*       Desc:  This function is used to Send Message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqAc_lhiutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlLhiSendMsg
(
Pst         *pst,
HiMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 szAcUtlLhiSendMsg(pst, cfm, mBuf)
Pst         *pst;
HiMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   SzAccMsgQElm *szMsg;

   TRC3(szAcUtlLhiSendMsg)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlLhiSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlLhiSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#endif

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
#ifdef ALIGN_64BIT
      CMXTA_DBG_INFO((_cmxtap, "szAcUtlLhiSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#else
      CMXTA_DBG_INFO((_cmxtap, "szAcUtlLhiSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
#endif

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
   szMsg = NULLP;
   CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
   if (szMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "aqAcAquSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(szMsg->u.hiMngmt), (U8 *)cfm, sizeof(HiMngmt));
   szMsg->mBuf = mBuf;
   qElm.msgFreeFun = szAcUtlLhiCb;
   qElm.data = (Void *)szMsg;

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
} /* End of szAcUtlLhiSendMsg() */


/*
*
*       Fun:   szAcUtlLhiCb 
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqAc_lhiutl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcUtlLhiCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 szAcUtlLhiCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   SzAccMsgQElm *szMsg;

   TRC2(szAcUtlLhiCb)

   szMsg = (SzAccMsgQElm *)qElm->data;

   if ((qElm->pst.event == EVTLHITRCIND) &&
       (szMsg->mBuf != NULLP))
   {
      CMXTA_FREEMBUF(szMsg->mBuf);
   }

   CMXTA_FREE(szMsg, sizeof (SzAccMsgQElm));


   RETVALUE(CMXTA_ERR_NONE);
} /* End of szAcUtlLhiCb() */

/* sz003.301: Updted for PSF-S1AP 3.1 release */

/*
*
*       Fun:   Activate Task - initialize
*
*       Desc:  Invoked by system services to initialize a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  szac_lhiutl.c
*
*/
  
#ifdef ANSI
PUBLIC S16 smHiActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smHiActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smHiActvInit);

   UNUSED(region);
   UNUSED(reason);
   UNUSED(ent);
   UNUSED(inst);

   RETVALUE(ROK);
} /* end of smHiActvInit */
 

/********************************************************************30**

         End of file:     szac_lhiutl.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:24 2013

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
/main/3      ---      vvashishth  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
