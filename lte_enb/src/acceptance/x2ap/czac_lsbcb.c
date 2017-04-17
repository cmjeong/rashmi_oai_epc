
/********************************************************************20**

     Name:     Dummy Stack Manager (Layer Manager) for the
               X2AP layer.
     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     cz_lsbcb.c

     Sid:      czac_lsbcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:27 2015

     Prg:      sy

*********************************************************************21*/

/*

  smsbbdy1.c - Stack Manager for the SCTP layer.

Following functions are provided in this file:
         SmMiLsbCfgCfm    - Configuration confirm
         SmMiLsbStsCfm    - Statistics confirm
         SmMiLsbStaCfm    - Status confirm
         SmMiLsbCntrlCfm  - Control confirm
         SmMiLsbStaInd    - Status indication
         SmMiLsbTrcInd    - Trace indication
         smSbActvInit     - Stack Manager initialization
*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000163                      SCTP layer
 */

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

#include "lcz.h"           /* layer management defines for X2AP */


#ifdef HI
#include "lhi.h"
#endif

#include "sct.h"           /* SB (SCTP) layer */
#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 

#include "cz.h"            /* defines and macros for X2AP */
#include "czt.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for X2AP acceptance tests */

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
#include "lcz.x"           /* layer management typedefs for X2AP */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lsb.x"

#ifdef SB
/*
 *
 *       Fun:    SmMiLsbCfgCfm - configuration confirm
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
PUBLIC S16 SmMiLsbCfgCfm
(
Pst         *pst,
SbMgmt     *cfg
)
#else
PUBLIC S16 SmMiLsbCfgCfm(pst, cfg)
Pst         *pst;
SbMgmt     *cfg;
#endif /* ANSI */
{

   TRC3(SmMiLsbCfgCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbCfgCfm(): txnId(%d)\n", cfg->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbCfgCfm(): txnId(%ld)\n", cfg->hdr.transId));
#endif

   /*-- Update Event --*/
   pst->event = LSB_EVTCFGCFM;

   czAcUtlLsbSendMsg(pst, cfg, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLsbCfgCfm() */

/*
 *
 *       Fun:    SmMiLsbStsCfm - statistics confirm
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
PUBLIC S16 SmMiLsbStsCfm
(
Pst                  *pst,
SbMgmt               *sts
)
#else
PUBLIC S16 SmMiLsbStsCfm(pst, sts)
Pst                  *pst;
SbMgmt               *sts;
#endif /* ANSI */
{
   TRC3(SmMiLsbStsCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStsCfm(): txnId(%d)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#endif

   /*-- Update Event --*/
   pst->event = LSB_EVTSTSCFM;

   czAcUtlLsbSendMsg(pst, sts, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLsbStsCfm() */

/*
 *
 *       Fun:    SmMiLsbStaCfm - status confirm
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
PUBLIC S16 SmMiLsbStaCfm
(
Pst                  *pst,
SbMgmt               *ssta
)
#else
PUBLIC S16 SmMiLsbStaCfm(pst, ssta)
Pst                  *pst;
SbMgmt               *ssta;
#endif /* ANSI */
{

   TRC3(SmMiLsbStaCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStaCfm(): txnId(%d)\n", ssta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStaCfm(): txnId(%ld)\n", ssta->hdr.transId));
#endif

   /*-- Update Event --*/
   pst->event = LSB_EVTSTACFM;

   czAcUtlLsbSendMsg(pst, ssta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLsbStaCfm() */

/*
 *
 *       Fun:    SmMiLsbCntrlCfm - control confirm
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
PUBLIC S16 SmMiLsbCntrlCfm
(
Pst         *pst,
SbMgmt     *cntrl
)
#else
PUBLIC S16 SmMiLsbCntrlCfm(pst, cntrl)
Pst         *pst;
SbMgmt     *cntrl;
#endif /* ANSI */
{
   TRC3(SmMiLsbCntrlCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbCntrlCfm(): txnId(%d)\n", cntrl->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbCntrlCfm(): txnId(%ld)\n", cntrl->hdr.transId));
#endif

   /*-- Update Event --*/
   pst->event = LSB_EVTCNTRLCFM;

   czAcUtlLsbSendMsg(pst, cntrl, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLsbCntrlCfm() */

/*
 *
 *       Fun:    SmMiLsbStaInd - status indication
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
PUBLIC S16 SmMiLsbStaInd
(
Pst         *pst,
SbMgmt     *usta
)
#else
PUBLIC S16 SmMiLsbStaInd(pst, usta)
Pst         *pst;
SbMgmt     *usta;
#endif /* ANSI */
{
   TRC3(SmMiLsbStaInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStaInd(): txnId(%d)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStaInd(): txnId(%ld)\n", usta->hdr.transId));
#endif

   /*-- Update Event --*/
   pst->event = LSB_EVTSTAIND;

   czAcUtlLsbSendMsg(pst, usta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLsbStaInd() */

/*
 *
 *       Fun:    SmMiLsbTrcInd - trace indication
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
PUBLIC S16 SmMiLsbTrcInd
(
Pst                  *pst,
SbMgmt               *trc
)
#else
PUBLIC S16 SmMiLsbTrcInd(pst, trc)
Pst                  *pst;
SbMgmt               *trc;
#endif /* ANSI */
{
   TRC3(SmMiLsbTrcInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStsCfm(): txnId(%d)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLsbStsCfm(): txnId(%ld)\n", trc->hdr.transId));
#endif

   /*-- Update Event --*/
   pst->event = LSB_EVTTRCIND;

   czAcUtlLsbSendMsg(pst, trc, NULLP);

   RETVALUE(CMXTA_ERR_NONE);

} /* end of SmMiLsbTrcInd() */

/*
 *
 *       Fun:    czAcUtlLsbSendMsg - trace indication
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
PUBLIC S16 czAcUtlLsbSendMsg
(
Pst         *pst,
SbMgmt     *cfg,
Buffer     *mBuf
)
#else
PUBLIC S16 czAcUtlLsbSendMsg(pst, cfg, mBuf)
Pst         *pst;
SbMgmt     *cfg;
Buffer     *mBuf;
#endif /* ANSI */
{
   Bool del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;

   TRC3(czAcUtlLsbSendMsg)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlLsbSendMsg(): txnId(%d)\n", cfg->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlLsbSendMsg(): txnId(%ld)\n", cfg->hdr.transId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   del = TRUE;
   /*-- Do not delete the txn cb if it is partial confirmation --*/
   if (cfg->cfm.status == LCM_PRIM_OK_NDONE)
      del = FALSE;

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = cmXtaTxnTstCbFind(cfg->hdr.transId, del)) == NULLP)
   {
      /*-- No associated test case found, spurious 
        message, drop it --*/
#ifdef ALIGN_64BIT
      CMXTA_DBG_INFO((_cmxtap, "czAcUtlLsbSendMsg(): msg dropped for txnId(%d)\n",
               cfg->hdr.transId));
#else
      CMXTA_DBG_INFO((_cmxtap, "czAcUtlLsbSendMsg(): msg dropped for txnId(%ld)\n",
               cfg->hdr.transId));
#endif

      /*-- Drop the message --*/
      if (pst->event == LSB_EVTTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((tcCb->directives.partialCfm == FALSE) &&
       (cfg->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == LSB_EVTTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == LSB_EVTSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == LSB_EVTSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == LSB_EVTTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
      /*-- Drop the message --*/
      if (pst->event == LSB_EVTTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate CZ  memory data --*/
   czMsg = NULLP;
   CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
   if (czMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcUtlLsbSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(czMsg->u.sbMgmt), (U8 *)cfg, sizeof(SbMgmt));
   czMsg->mBuf = mBuf;
   qElm.msgFreeFun = czAcUtlLsbCb;
   qElm.data = (CzAccMsgQElm *)czMsg;

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

   RETVALUE(CMXTA_ERR_NONE);
} /* end of czAcUtlLsbSendMsg() */
#endif /* ifdef SB */

/********************************************************************30**

         End of file:     czac_lsbcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:27 2015

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
/main/1      ---        sy      1. LTE-X2AP Initial Release.
/main/2      ---        pt      1. LTE-X2AP 3.1 release.
*********************************************************************91*/
