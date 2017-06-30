
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    czac_lhiutil.c

     Sid:      czac_lhiutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:26 2015

     Prg:     sy
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for X2AP */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h"

#include "cz.h"            /* defines and macros for X2AP */
#include "czt.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for X2AP acceptance tests */
#include <stdlib.h>

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
#include "lcz.x"           /* LCZ types */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x"
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lhi.x"


#ifdef HI
/*
*
*       Fun:   czAcUtlLhiSendMsg 
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
PUBLIC S16 czAcUtlLhiSendMsg
(
Pst         *pst,
HiMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 czAcUtlLhiSendMsg(pst, cfm, mBuf)
Pst         *pst;
HiMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;

   TRC3(czAcUtlLhiSendMsg)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlLhiSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlLhiSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
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
      CMXTA_DBG_INFO((_cmxtap, "czAcUtlLhiSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#else
      CMXTA_DBG_INFO((_cmxtap, "czAcUtlLhiSendMsg(): msg dropped for txnId(%ld)\n",
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
   czMsg = NULLP;
   CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
   if (czMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "aqAcAquSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(czMsg->u.hiMngmt), (U8 *)cfm, sizeof(HiMngmt));
   czMsg->mBuf = mBuf;
   qElm.msgFreeFun = czAcUtlLhiCb;
   qElm.data = (Void *)czMsg;

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
} /* End of czAcUtlLhiSendMsg() */


/*
*
*       Fun:   czAcUtlLhiCb 
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
PUBLIC S16 czAcUtlLhiCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 czAcUtlLhiCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CzAccMsgQElm *czMsg;

   TRC2(czAcUtlLhiCb)

   czMsg = (CzAccMsgQElm *)qElm->data;

   if ((qElm->pst.event == EVTLHITRCIND) &&
       (czMsg->mBuf != NULLP))
   {
      CMXTA_FREEMBUF(czMsg->mBuf);
   }

   CMXTA_FREE(czMsg, sizeof (CzAccMsgQElm));


   RETVALUE(CMXTA_ERR_NONE);
} /* End of czAcUtlLhiCb() */

#endif /* ifdef HI */
/********************************************************************30**

         End of file:     czac_lhiutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:26 2015

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
/main/1      ---        sy        1. LTE-X2AP Initial Release.
/main/2      ---        pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
