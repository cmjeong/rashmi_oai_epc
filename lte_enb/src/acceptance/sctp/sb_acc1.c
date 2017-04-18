
/********************************************************************20**

     Name:     sb_acc1.c - Acceptance Tests  for the SCTP layer

     Type:     C source file

     Desc:     C code for controlling acceptance tests execution

     File:     sb_acc1.c

     Sid:      sb_acc1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:05 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_acc1.c - Acceptance Tests Controller for the SCTP layer

Following functions are provided in this file:
         tst                  - main test function

*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000163                      SCTP layer */

/* header include files (.h) */

#include <stdio.h>

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS defines */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb_mtu.h"        /* mtu defines */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#include "sb_acc.h"        /* defines for SCTP layer */


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"        /* mtu typedefs  */
#include "sb_acc.x"        /* defines for SCTP layer */
#include "sb.x"            /* SCTP internal typedefs */

/* local typedefs */
typedef S8 sbErrMsg[PRNTSZE];

/* public routines */
PUBLIC S16 permActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));


/* local defines */
PRIVATE sbErrMsg sbAccPrimitiveType[] =    /* Incoming primitives to test case */
{
      "BndCfm:",
      "EndpOpenCfm:",
      "EndpCloseCfm:",
      "AssocInd:",
      "AssocCfm:",
      "SetPriCfm:",
      "HBeatCfm:",
      "DatInd:",
      "TermInd:",
      "TermCfm:",
      "StaInd:",
      "StaCfm:",
      "FlcInd:",
      "BndReq:",
      "UBndReq:",
      "ServOpenReq:",
      "DiscReq:",
      "UDatReq:",
      "CfgCfm:",
      "CntrlCfm:",
      "TrcInd:",
      "StsCfm:",
      "CfgReq:",
      "CntrlReq:",
      "StsReq:",
      "StaReq:",
      "No response expected:",
      "Unknown:",
      "\n"
};  /* end sbAccPrimitiveType */

PRIVATE sbErrMsg sbAccStatusErrType[] =
{
      "Primitive  failed:",
      "Primitive not received",
      "Timeout:",
      "Incorrect TransId:",
      "Incorrect message type:",
      "Incorrect primitive type:",
      "Incorrect element Id:",
      "Incorrect SuId:",
      "Incorrect SAP ConId:",
      "Incorrect status:",
      "Incorrect reason:",
      "Incorrect alarm event:",
      "Incorrect alarm cause:",
      "Incorrect type:",
      "Incorrect data:",
      "Incorrect data/packet len:",
      "Incorrect Adler checksum:",
      "Incorrect number of packets received:",
      "No FlcInd received:",
      "Invalid chunk type received:",
      "Invalid buildPar:",
      "Stats counters not zero:",
      "Stats - number of packets sent incorrect:",
      "Invalid protocol:",
      "Invalid state:",
      "Invalid version:",
      "Invalid part number:",
      "Incorrect result:",
      "Incorrect endpoint:",
      "Incorrect SAP:",
      "Incorrect SpId:",
      "Primitive succeeds:",
      "Incorrect Timerstate:",
      "Invalid cookie:",
      "Invalid verification tag:",
      "Invalid port:",
      "Invalid cause code:",
      "Invalid segmentation:",
      "Incorrect address:",
      "Incorrect indication type:",
      "Incorrect Association Id:",
      "No test in the loosely coupled mode:",
      "No test with this number currently listed:",
      "No subtest with this number listed :",
      "The Buffer is empty :",
      "Incorrect retrieval information :",
      "Incorrect advertised Rwnd :",
      "Incorrect number of streams :",
      "Incorrect tsn number :",
      "Incorrect sack fragment start/end :",
      "Incorrect statistics: ",
      "\n"
};  /* end sbAccStatusErrType */

/* public variable declarations */
PUBLIC SbAccCb sbAccCb;
PUBLIC U32 delayMax;


/* public variable definitions */

/* private variable definitions */

PRIVATE U32 delayCntr;
PRIVATE U32 holdTst;

/* public routines */
/*
*
*       Fun:   rdConQ
*
*       Desc:  This function is used to read the console queue.
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  sb_acc.c
*
*/

#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   TRC2(rdConQ)
#ifdef DOS
   /* check if control-c */
   if (data == 0x03)
      exit(0);
#else
#ifdef UNIX
   /* check if control-c */
   if (data == 0x03)
      exit(0);
#else
#ifdef MVME162_1
   /* check if control-c */
   if (data == 0x03)
      exit(1);
#else
#ifdef WIN32
   /* check if control-c */
   if (data == 0x03)
      exit(1);
#else
#endif /* WIN32 */
#endif /* MVME162_1 */
#endif
#endif
   sbAccCb.snoozeFlg = FALSE;
   RETVALUE(OK);
}/* end of  rdConQ()*/

/*
*
*       Fun:   sbAccDispErrTstRslt
*
*       Desc: Displays the test result in the case of an error.
*
*       Ret:   void
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  Void sbAccDispErrTstRslt
(
 S8                *testNr,                /* test number */
U8                 subTest,     /* subtest number */
Event              evnt,        /* primitive */
SctStatus          status,      /* status */
U16                reason       /* reason */
)
#else
PUBLIC  Void sbAccDispErrTstRslt(testNr, subTest, evnt, status, reason)
S8     *testNr;        /* test number */
U8      subTest;                /* subtest number */
Event   evnt;                   /* primitive */
SctStatus  status;              /* status */
U16     reason;                 /* reason */
#endif
{
   Txt  prntBuf[SB_PRNTBUF_SIZE];
   char buf[MSG_SIZE];

   TRC2(sbAccDispErrTstRslt)

   sprintf(prntBuf, "Error: %s nr %d:  %s %s (reason = ",
                    testNr, subTest,
                    sbAccPrimitiveType[evnt],
                    sbAccStatusErrType[status]);

   switch (reason)
   {
        case LCM_REASON_NOT_APPL:
            strcat(prntBuf, "Reason not applicable\n");
            break;
        case LCM_REASON_INVALID_ENTITY:
            strcat(prntBuf, "Invalid entity in request\n");
            break;
        case LCM_REASON_INVALID_INSTANCE:
            strcat(prntBuf, "Invalid instance in request\n");
            break;
        case LCM_REASON_INVALID_MSGTYPE:
            strcat(prntBuf, "Invalid message type in request\n");
            break;
        case LCM_REASON_MEM_NOAVAIL:
            strcat(prntBuf, "Memory not available \n");
            break;
        case LCM_REASON_INVALID_ELMNT:
            strcat(prntBuf, "Invalid element in header\n");
            break;
        case LCM_REASON_RECONFIG_FAIL:
            strcat(prntBuf, "Reconfiguration fails\n");
            break;
        case LCM_REASON_REGTMR_FAIL:
            strcat(prntBuf, "Timer registration failed\n");
            break;
        case LCM_REASON_GENCFG_NOT_DONE:
            strcat(prntBuf, "General configuration not done\n");
            break;
        case LCM_REASON_INVALID_ACTION:
            strcat(prntBuf, "Invalid action in control request\n");
            break;
        case LCM_REASON_INVALID_SUBACTION:
            strcat(prntBuf, "Invalid subaction in control request\n");
            break;
        case LCM_REASON_INVALID_STATE:
            strcat(prntBuf, "Invalid state\n");
            break;
        case LCM_REASON_INVALID_SAP:
            strcat(prntBuf, "Invalid SAP\n");
            break;
        case LCM_REASON_INVALID_PAR_VAL:
            strcat(prntBuf, "Invalid parameter value\n");
            break;
        case LCM_REASON_QINIT_FAIL:
            strcat(prntBuf, "Queue initialization fail\n");
            break;
        case LCM_REASON_NEG_CFM:
            strcat(prntBuf, "Negative confirmation\n");
            break;
        case LCM_REASON_UPDTMR_EXPIRED:
            strcat(prntBuf, "Update timer expired\n");
            break;
        case LCM_REASON_MISC_FAILURE:
            strcat(prntBuf, "Miscellaneous failure \n");
            break;
        case LCM_REASON_EXCEED_CONF_VAL:
            strcat(prntBuf, "Exceeds configured values \n");
            break;
        case LCM_REASON_HASHING_FAILED:
            strcat(prntBuf, "Hashing failed.\n");
            break;
        case LCM_REASON_PEERCFG_NOT_DONE:
            strcat(prntBuf, "Peer Sap not configured\n");
            break;
        case LCM_REASON_PRTLYRCFG_NOT_DONE:
            strcat(prntBuf, "portable Lyr not configured \n");
            break;
/*
        case LCM_REASON_HIT_FAIL:
            strcat(prntBuf, "Failure at the HIT interface\n");
            break;
        case LCM_REASON_MAX_BND_TRY:
            strcat(prntBuf, "Maximum number of bind retries have been performed\n");
            break;
        case LCM_REASON_INVALID_TMRRES:
            strcat(prntBuf, "Invalid timer resolution Id\n");
            break;
        case LCM_REASON_INVALID_PAR_VAL:
            strcat(prntBuf, "Invalid configuration parameter Id\n");
            break;*/

       default:
            sprintf(buf, "Unknown reason-%d\n", reason);
            strcat(prntBuf, buf);
            break;
   };

   SPrint(prntBuf);
   RETVOID;

} /* end sbAccDispErrTstRslt */

/*
*
*       Fun:   sbGetLmPst
*
*       Desc:  Fills the lmPst structure. For alarms addressed to the layer manager.
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  Void  sbGetLmPst
(
Pst *lmPst
)
#else
PUBLIC  Void sbGetLmPst(lmPst)
Pst  *lmPst;          /* pointer to lmPst structure */
#endif
{
   TRC2(sbGetLmPst)

#ifdef LCSBMILSB
   lmPst->selector     = (U8)(sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC);
#else
   lmPst->selector     = SEL_TC;     /* tightly coupled */
#endif
   lmPst->dstProcId = SFndProcId();  /* dst proc id */
   lmPst->srcProcId = SFndProcId();  /* src proc id */
   lmPst->dstEnt    = ENTSM;         /* dst entity */
   lmPst->dstInst   = TSTINST_0;     /* dst inst */
   lmPst->srcEnt    = ENTSB;         /* src entity */
   lmPst->srcInst   = TSTINST_0;     /* src inst */

   lmPst->region    = TSTREG;        /* region */
   lmPst->pool      = TSTPOOL;       /* pool */
   lmPst->prior     = PRIOR0;        /* priority */
   lmPst->route     = RTESPEC;       /* route */

#ifdef LCSMSBMILSB
   lmPst->selector     = sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC;
#else
   lmPst->selector     = SEL_TC;     /* tightly coupled */
#endif


   RETVOID;

} /* sbGetLmPst */

/*
*
*       Fun:   sbAccPushMsg
*
*       Desc:  Inserts a message at the back of the message queue
*
*       Ret:   ROK     - operation was successful
*              RFAILED - queue is full
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAccPushMsg
(
SbAccMsgQElm  *msg            /* Message to be inserted in the queue */
)
#else
PUBLIC S16 sbAccPushMsg(msg)
SbAccMsgQElm  *msg;           /* Message to be inserted in the queue */
#endif
{
   Txt   prntBuf[SB_PRNTBUF_SIZE];
   U16   oldPtr;          /* saved pointer value */

   TRC2(sbAccPushMsg)

   /* get sema */
   /*(Void)sbGetSema();*/
   (Void)SLock(&sbAccCb.qlock);

   /* save the old pointer */
   oldPtr = sbAccCb.msgQ.wrPtr;

   /* increment the write pointer */
   sbAccCb.msgQ.wrPtr++;

   /* if write-ptr has reached end of the queue,roll it to the head of the queue */
   if (sbAccCb.msgQ.wrPtr == (U16) SB_ACC_MSG_QSIZE)
   {
      sbAccCb.msgQ.wrPtr = 0;
   }

      /* Check if the queue if FULL */
   if (sbAccCb.msgQ.wrPtr == sbAccCb.msgQ.rdPtr)
   {
      sbAccCb.msgQ.wrPtr = oldPtr;

      SBACCPRNERROR((prntBuf, "sbAccPushMsg(): Queue is full.\n"));
      /* release sema */
      /*(Void)sbFreeSema();*/
      (Void)SUnlock(&sbAccCb.qlock);

      RETVALUE(RFAILED);
   }

   /* queue the passed element */
   sbAccCb.msgQ.q[oldPtr] = *msg;

   /* release sema */
   /*(Void)sbFreeSema();*/
   (Void)SUnlock(&sbAccCb.qlock);

   RETVALUE(ROK);
} /* sbAccPushMsg */

/*
*
*       Fun:   sbAccPeekMsg
*
*       Desc:  Looks at the next message in the message queue
*              The message is NOT popped from the queue.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  it_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbAccPeekMsg
(
SbAccMsgQElm  **msg
)
#else
PUBLIC  S16 sbAccPeekMsg(msg)
SbAccMsgQElm  **msg;
#endif
{

   TRC2(sbAccPeekMsg)

   (Void)SLock(&sbAccCb.qlock);

   /* Check If queue is EMPTY */
   if (sbAccCb.msgQ.rdPtr == sbAccCb.msgQ.wrPtr)
   {
      *msg = NULLP;
      (Void)SUnlock(&sbAccCb.qlock);

      RETVALUE(RFAILED);
   }

   *msg = &sbAccCb.msgQ.q[sbAccCb.msgQ.rdPtr];

   (Void)SUnlock(&sbAccCb.qlock);

   RETVALUE(ROK);
}



/*
*
*       Fun:   sbAccPopMsg
*
*       Desc:  Remove a message from the queue
*
*       Ret:   ROK     - operation was successful
*              RFAILED - queue is empty
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbAccPopMsg
(
SbAccMsgQElm  **msg           /* queue message to be returned */
)
#else
PUBLIC  S16 sbAccPopMsg(msg)
SbAccMsgQElm  **msg;          /* queue message to be returned */
#endif
{
   TRC2(sbAccPopMsg)

   /*sbGetSema();*/
   (Void)SLock(&sbAccCb.qlock);

   /* Check If queue is EMPTY */
   if (sbAccCb.msgQ.rdPtr == sbAccCb.msgQ.wrPtr)
   {
      *msg = NULLP;
      /*sbFreeSema();*/
      (Void)SUnlock(&sbAccCb.qlock);

      RETVALUE(RFAILED);
   }

   *msg = &sbAccCb.msgQ.q[sbAccCb.msgQ.rdPtr];

   /* Increment the read pointer to the next location */
   sbAccCb.msgQ.rdPtr++;

   /* if read-ptr has reached end of the queue,
      roll it to the head of the queue */
   if (sbAccCb.msgQ.rdPtr == (U16) SB_ACC_MSG_QSIZE)
      sbAccCb.msgQ.rdPtr = 0;

   /*sbFreeSema();*/
   (Void)SUnlock(&sbAccCb.qlock);


   RETVALUE(ROK);
} /* sbAccPopMsg */

/*
*
*       Fun:   sbSetTimeoutCntr
*
*       Desc:  Set the timeout counter
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC Void sbSetTimeoutCntr
(
U32 timeout
)
#else
PUBLIC Void sbSetTimeoutCntr(timeout)
U32 timeout;
#endif
{
   /* Set a new value for dalay max */
   delayMax = timeout;
} /* sbSetTimeoutCntr */

/*
*
*       Fun:   sbAccVfyMsg
*
*       Desc:  This function verifies if the queue is empty and manages the delayCntr.
*              If the queue is empty and delayCntr != DELAY_CNTR_MAX it increments the
*              delayCntr and returns status = WAIT to the test handler.
*              If delayCntr < DELAY_CNTR_MAX and queue is not empty it returns status
*              = NO_MSG to the test handler
*              If delayCntr == DELAY_CNTR_MAX, it returns status = NO_MSG to the test
*              handler.
*
*       Ret:    RETVOID
*
*       Notes:  the delayCntr is set DELAY_CNTR_INIT if there is a message in the queue.
*
*       File:   sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC Void sbAccVfyMsg
(
SctStatus *status
)
#else
PUBLIC Void sbAccVfyMsg(status)
SctStatus *status;
#endif
{
   if (sbAccCb.curTst.delay!=0)
   {
      delayMax = sbAccCb.curTst.delay;
   }
   else
   {
      delayMax = DELAY_CNTR_MAX;
   }

   if (delayCntr < delayMax)
   {
      /* acquire sema */
      /*sbGetSema();*/
      (Void)SLock(&sbAccCb.qlock);

      /* Check If queue is EMPTY */
      if (sbAccCb.msgQ.rdPtr == sbAccCb.msgQ.wrPtr)
      {
         /* delay counter is incremented every 1 sec by sbAccActvTmr */
           *status = WAIT;

      }
      else
      {
         delayCntr = DELAY_CNTR_INIT;   /* Message received before time has run out*/
         *status = DONT_WAIT;
      }
      /* free sema */
      /*sbFreeSema();*/
      (Void)SUnlock(&sbAccCb.qlock);

   }
   else
   /* time has run out and expected message not received */
   {
      delayCntr = DELAY_CNTR_INIT;
      *status = TIMEOUT;

   }
   RETVOID;
} /* end sbAccVfyMsg */

/*
*
*       Fun:    activate test timer
*
*       Desc:   increments the delay counter
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sb_acc1.c
*
*/

#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 sbAccActvTmr
(
ProcId proc,
Ent    ent,
Inst   inst
)
#else
PUBLIC S16 sbAccActvTmr(proc, ent, inst)
ProcId proc;
Ent    ent;
Inst   inst;
#endif
#else  /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 sbAccActvTmr
(
void
)
#else
PUBLIC S16 sbAccActvTmr()
#endif
#endif  /* SS_MULTIPLE_PROCS */
{
   TRC3(sbAccActvTmr)

#ifdef SS_MULTIPLE_PROCS
   UNUSED(proc);
   UNUSED(ent);
   UNUSED(inst);
#endif /* SS_MULTIPLE_PROCS */

   if (sbAccCb.snoozeFlg == FALSE)
   {
      delayCntr++;
   }

   RETVALUE(ROK);
} /* end of sbAccActvTmr */


/*
*
*       Fun:    activate permanent task
*
*       Desc:   Processes received primitives from the SCTP layer.
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbPermTsk
(
Pst       *pst,         /* post */
Buffer    *mBuf         /* message buffer */
)
#else
PUBLIC S16 sbPermTsk(pst, mBuf)
Pst       *pst;         /* post */
Buffer    *mBuf;        /* message buffer */
#endif
{
   Txt    prntBuf[SB_PRNTBUF_SIZE];

   TRC3(sbPermTsk);
   UNUSED(pst);

   /* wait for some time before starting next cycle */

   /* free the message buffer if we have one */
   if (mBuf)
   {
      SPutMsg(mBuf);
      mBuf = NULLP;
   }

   /* If Acceptance test run is over then return from here */
   if (sbAccCb.testFlg == FALSE)
   {
#ifdef SS_MULTIPLE_PROCS
      if (SDeregTmr(PROC_MP_ID0,(Ent)ENTPRM, (Inst)TSTINST_0, \
                    SB_ACC_1_SECOND, (PAIFTMRS16)sbAccActvTmr) != ROK)
#else
      if (SDeregTmr((Ent)ENTPRM, (Inst)TSTINST_0, \
                    SB_ACC_1_SECOND, sbAccActvTmr) != ROK)
#endif /* SS_MULTIPLE_PROCS */
      {
         SBACCPRNERROR((prntBuf, "tst:SDeregTmr() for PermTsk failed.\n"));
         RETVALUE(RFAILED);
      }
      if (sbAccCb.tcFlg == FALSE)
      {
         SDestroySTsk(sbAccCb.sbTskId);
      }

      /* Destroy the other system task if created */
      if (sbAccCb.sbTskId != sbAccCb.tstTskId)
      {
         SDestroySTsk(sbAccCb.tstTskId);
      }

      sprintf(prntBuf, "Total tests run    : %d\n"
                 "Total tests passed : %d\n"
                 "Total tests failed : %d\n",
                 (U16)sbAccCb.testsRun,
                 (U16)sbAccCb.testsPass,
                 (U16)sbAccCb.testsFail);
      SPrint(prntBuf);
      sprintf(prntBuf,"\n******* FIN *******\n");
      SPrint(prntBuf);

      exit(0);
   }

   /* Debugging aid: hold back until a key is pressed */
   if (sbAccCb.snoozeFlg == TRUE)
   {
      RETVALUE(ROK);
   }

   (Void)(*(sbAccCb.tstLst.list[sbAccCb.tstLst.index]->testFunc))();

   /* Print the result of the last test */
   /* If the last test is completed then start the new test */
   if (sbAccCb.curTst.bCompleted == TRUE)
   {
#ifdef SS_LINUX
      SBACCPRNERROR((prntBuf, "\nTest Case %s: %d [%sPASSED%s], %d [%sFAILED%s]\n\n",
                               sbAccCb.tstLst.index<sbAccCb.tstLst.length?
                               (S8 *)(sbAccCb.tstLst.list[sbAccCb.tstLst.index]->testId) :
                               "Invalid test sequence number",
                               sbAccCb.curTst.subTestsPass,
                               sbAccCb.curTst.subTestsPass?
                               "\033[00m\033[01;32m" :
                               "\033[00m",
                               "\033[00m",
                               sbAccCb.curTst.subTestsFail,
                               sbAccCb.curTst.subTestsFail?
                               "\033[00m\033[01;31m" :
                               "\033[00m", "\033[00m"));
#else
      SBACCPRNERROR((prntBuf, "\nTest Case %s: %d PASSED, %d FAILED\n\n",
                               sbAccCb.tstLst.index<sbAccCb.tstLst.length?
                               (S8 *)(sbAccCb.tstLst.list[sbAccCb.tstLst.index]->testId) :
                               "Invalid test sequence number",
                               sbAccCb.curTst.subTestsPass,
                               sbAccCb.curTst.subTestsFail));
#endif

      sbAccCb.testsRun++;
      if ((sbAccCb.curTst.subTestsFail == 0) &&
          (sbAccCb.curTst.subTestsPass != 0))
      {
         sbAccCb.testsPass++;
      }
      else
      {
         sbAccCb.testsFail++;
      }

      /* Initialize the current test context */
      sbAccCb.curTst.addrType = CM_NETADDR_IPV4; /* default type for IPV6 test*/
      sbAccCb.curTst.state = 0;
      sbAccCb.curTst.subTest = 1;
      sbAccCb.curTst.subTestsPass = 0;
      sbAccCb.curTst.subTestsFail = 0;
      sbAccCb.curTst.bBusyPreTestConf = TRUE;
      sbAccCb.curTst.bBusySubtest = FALSE;
      sbAccCb.curTst.bConfigDeleted = FALSE;
      sbAccCb.curTst.bBusyCleanup = FALSE;
      sbAccCb.curTst.bConfigMask = 0;
      sbAccCb.curTst.bSctSapCfgMask = 0;
      sbAccCb.curTst.bTSapCfgMask   = 0;
      sbAccCb.curTst.bSapMask    = 0;
      sbAccCb.curTst.bAssocMask  = 0;;
      sbAccCb.curTst.bTSapMask = 0;
      sbAccCb.curTst.bEndpMask = 0;
      sbAccCb.curTst.bAssocMask = 0;
      sbAccCb.curTst.bAssocSetupMask = 0;
      sbAccCb.curTst.bSapMask = 0;
      sbAccCb.curTst.bTraceMask = FALSE;
      sbAccCb.curTst.bDebugPMask = FALSE;
      sbAccCb.curTst.bTickMask = 0;
      sbAccCb.curTst.tickLstDoneFlg = TRUE;
      sbAccCb.useDnsFlag = FALSE;

      sbAccCb.curTst.bCompleted = FALSE;
      sbAccCb.curTst.bTestsCompleted = FALSE;

      sbAccCb.curTst.delay = 0;
      SB_RLSMEM(sbAccCb.curTst.gmBuf)  /*  release memory */
      SB_ZERO(&sbAccCb.curTst.datRcv, (S32)sizeof(sbAccCb.curTst.datRcv));
      sbAccCb.curTst.datRcvLen = 0;

      /* initialize delayCntr at the beginning of each test */
      delayCntr = DELAY_CNTR_INIT;
      delayMax = DELAY_CNTR_MAX;

      /* By default enable the prints, can be disabled inside the test case */
      sbAccCb.curTst.prntFlag = TRUE;

      /* execute next test in sequence list or end cycle */

      if ((sbAccCb.tstLst.index+1)<sbAccCb.tstLst.length) /* next index is legal */
      {
          sbAccCb.tstLst.index++;
          /* Invoke a test */
      }
      else /* all tests completed */
      {
         /* Acceptance test run is over */
         sbAccCb.testFlg = FALSE;

         /* set holdTst = HOLD_TEST_INIT so that the next cycle
          * does not begin immdiately. This will allow some time to
          * initialize the layer before the next test cycle begins.
          */
      } /* if (index<length) */

      /* Initialize the Queue */
      (Void)sbAccFlushQ();

   } /* if (bCompleted) */



   RETVALUE(ROK);
} /* End of sbPermTsk */


/*
*
*       Fun:   permActvInit
*
*       Desc:  Initializes variables for permanent task
*              Layer
*
*       Ret:   ROK     - ok
*              RFAILED - failed
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/

#ifdef ANSI
PUBLIC S16 permActvInit
(
Ent ent,                   /* entity */
Inst inst,                 /* instance */
Region region,             /* region */
Reason reason              /* reason */
)
#else
PUBLIC S16 permActvInit(ent, inst, region, reason)
Ent ent;                   /* entity */
Inst inst;                 /* instance */
Region region;             /* region */
Reason reason;             /* reason */
#endif
{
   TRC2(permActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   RETVALUE(ROK);
} /* end of permActvInit */


/*
*
*       Fun:   sbAccFlushQ
*
*       Desc:  Flush the Queue
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC Void sbAccFlushQ
(
Void
)
#else
PUBLIC Void sbAccFlushQ(Void)
#endif
{
   TRC2(sbAccFlushQ)

   /*sbGetSema();*/
   (Void)SLock(&sbAccCb.qlock);

   sbAccCb.msgQ.wrPtr = 0;
   sbAccCb.msgQ.rdPtr = 0;

   /*sbFreeSema();*/
   (Void)SUnlock(&sbAccCb.qlock);

   delayCntr = DELAY_CNTR_INIT;

   RETVOID;
} /* sbAccFlushQ */


/*
*
*       Fun:   tst
*
*       Desc:  This routine is called by MOS to configure the layers
*              and run the acceptance test.
*
*       Ret:   ROK       - ok
*
*       Notes: This function name is required by MOS, and is invoked
*              just before the main scheduling loop, in order to
*              register tasks, configure and bind.
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
void
)
#else
PUBLIC S16 tst()
#endif
{
   S16       ret;
   Txt       prntBuf[PRNTSZE]; /* character string for printing */
/* sb061.102 - remove compiler warnings */
#ifdef SS_MULTIPLE_PROCS
  ProcId procIds[] = {PROC_MP_ID0};
  SAddProcIdLst((U16)1, procIds);
#endif  /* SS_MULTIPLE_PROCS */

   TRC1(tst)

   sbAccCb.testFlg = TRUE;

   /* Get command-line options */
   sbAccCb.snoozeFlg = FALSE;
   sbAccCb.tcFlg = FALSE;

#ifdef SBACC_CMD_LINE    /* WINNT doesn't seem to like run time arguments */
   msOptInd = 1;

   while ((ret = SGetOpt(msArgc, msArgv, "zc")) != EOF)
   {
      switch (ret)
      {
         case 'c':
            sbAccCb.tcFlg = TRUE;
            break;
         case 'z':
            sbAccCb.snoozeFlg = TRUE;
            break;
         case '?':
            /* fall through */
         default:
            break;
      }
   }
#else /* SBACC_CMD_LINE */
   ret = ROK;
#endif /* SBACC_CMD_LINE */

   /* Initialize the parameters of the control tests */
   if (sbInitAccCb() != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Initialise Semaphore */
   if (SInitLock(&sbAccCb.qlock, SS_LOCK_MUTEX) != ROK)
   {
      RETVALUE(LCM_REASON_MISC_FAILURE);
   }

   /* Initialize the task Ids */
   sbAccCb.sbTskId = 0;
   sbAccCb.tstTskId = 0;

   /* Register layer tasks */
   /* Create SCTP System Task */
   if (SCreateSTsk((SSTskPrior)PRIOR0, &(sbAccCb.sbTskId)) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SCreateSTsk() for SCTP failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Register SCTP TAPA Task */
   if (SRegTTsk((Ent)ENTSB, (Inst)TSTINST_0, (Ttype)TTNORM, (Prior)PRIOR0,
                sbActvInit, sbActvTsk) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTTsk() for SCTP failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Attach SCTP TAPA Task */
   if (SAttachTTsk((Ent)ENTSB, (Inst)TSTINST_0, sbAccCb.sbTskId)!= ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SAttachTTsk() for SCTP failed.\n"));
      RETVALUE(RFAILED);
   }

#ifdef SB_FTHA
   /* Register IWF TAPA Task */
   if (SRegTTsk((Ent)ENTSH, (Inst)TSTINST_0, TTNORM, PRIOR0, NULLP, smShtActvTsk) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTTsk() for SHT failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Attach IWF TAPA Task */
   if (SAttachTTsk((Ent)ENTSH, (Inst)TSTINST_0, sbAccCb.tstTskId)!= ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SAttachTTsk() for SHT failed.\n"));
      RETVALUE(RFAILED);
   }
#endif /* SB_FTHA */
   

   if ( sbAccCb.tcFlg == TRUE )
   {
      /* we are thus tightly coupled */
      /* create only a SINGLE system task */
      sbAccCb.tstTskId = sbAccCb.sbTskId;
   }
   else
   {
      /* we are thus loosely coupled */
      /* Create Test Code System Task */
      if (SCreateSTsk((SSTskPrior)PRIOR0, &(sbAccCb.tstTskId)) != ROK)
      {
         SBACCPRNERROR((prntBuf, "tst:SCreateSTsk() for test code failed.\n"));
         RETVALUE(RFAILED);
      }
   }

   /* Register IT Task */
   if (SRegTTsk((Ent)ENTIT, (Inst)TSTINST_0, (Ttype)TTNORM, (Prior)PRIOR0,
                 itSbActvInit, itSbActvTsk) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTTsk() for M3UA failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Attach IT TAPA Task */
   if (SAttachTTsk((Ent)ENTIT, (Inst)TSTINST_0, sbAccCb.tstTskId)!= ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SAttachTTsk() for M3UA failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Register HI TAPA Task */
   if (SRegTTsk((Ent)ENTHI, (Inst)TSTINST_0, (Ttype)TTNORM, (Prior)PRIOR0,
       hiSbActvInit, hiSbActvTsk) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTTsk() for TUCL failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Attach HI TAPA Task */
   if (SAttachTTsk((Ent)ENTHI, (Inst)TSTINST_0, sbAccCb.tstTskId)!= ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SAttachTTsk() for TUCL failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Register SM TAPA Task */
   if (SRegTTsk((Ent)ENTSM, (Inst)TSTINST_0, (Ttype)TTNORM, (Prior)PRIOR0, smSbActvInit, smSbActvTsk) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTTsk() for SM failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Attach SM TAPA Task */
   if (SAttachTTsk((Ent)ENTSM, (Inst)TSTINST_0, sbAccCb.tstTskId)!= ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SAttachTTsk() for SM failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Register Permanent TAPA Task */
   if (SRegTTsk((Ent)ENTPRM, (Inst)TSTINST_0, (Ttype)TTPERM, (Prior)PRIOR0, permActvInit, sbPermTsk) != ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTTsk() for PermTsk failed.\n"));
      RETVALUE(RFAILED);
   }

   /* Attach Permanent TAPA Task */
   if (SAttachTTsk((Ent)ENTPRM, (Inst)TSTINST_0, sbAccCb.tstTskId)!= ROK)
   {
      SBACCPRNERROR((prntBuf, "tst:SAttachTTsk() for PermTsk failed.\n"));
      RETVALUE(RFAILED);
   }

#ifdef SS_MULTIPLE_PROCS
   if (SRegTmr(PROC_MP_ID0,(Ent)ENTPRM, (Inst)TSTINST_0, SB_ACC_1_SECOND, 
                                        (PAIFTMRS16)sbAccActvTmr) != ROK)
#else
   if (SRegTmr((Ent)ENTPRM, (Inst)TSTINST_0, SB_ACC_1_SECOND, sbAccActvTmr)
                                                                    != ROK)
#endif
   {
      SBACCPRNERROR((prntBuf, "tst:SRegTmr() for timer failed.\n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* tst */


/* Static memory versions of test matrix and sequence table functions */
/*
*
*       Fun:   sbTblAddTestIndex
*
*       Desc:  Initialize the Acceptance test table
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  Void sbTblAddTestIndex
(
 SbTestCbTbl *tstTbl
)
#else
PUBLIC  Void sbTblAddTestIndex(tstTbl)
SbTestCbTbl *tstTbl;
#endif
{
   Txt   prntBuf[SB_PRNTBUF_SIZE];

   TRC2(sbTblAddTestIndex)

   if (tstTbl->numrows<ACC_TSTTBLROWS) /* next row is valid */
   {
    tstTbl->rowlength[tstTbl->numrows]=0;
    tstTbl->numrows++;
   }
   else /* error */
   {
    SBACCPRNERROR((prntBuf,"sbTblAddTestIndex: Test Table's MAXROWS exceeded."))
   }
} /* End of sbTblAddTestIndex */


/*
*
*       Fun:   sbTblAddTestSubIndex
*
*       Desc:  Initialize the Acceptance test table
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  Void sbTblAddTestSubIndex
(
 SbTestCbTbl *tstTbl,
 SbTestCb    *tstCb
)
#else
PUBLIC  Void sbTblAddTestSubIndex(tstTbl, tstCb)
SbTestCbTbl *tstTbl;
SbTestCb *tstCb;
#endif
{
   Txt   prntBuf[SB_PRNTBUF_SIZE];

   U32 curr_row;

   TRC2(sbTblAddTestSubIndex)

   if (tstTbl->numrows==0 || tstTbl->numrows>=ACC_TSTTBLROWS) return;

   curr_row = tstTbl->numrows-1;

   if (tstTbl->rowlength[curr_row]<ACC_TSTTBLROWSIZE) /* next entry valid */
   {
      /* assign new entry */
      tstTbl->tstMatrix[curr_row][tstTbl->rowlength[curr_row]] = *tstCb;
      /* indicate new row length */
      tstTbl->rowlength[curr_row]++;
   }
   else /* error */
   {
    SBACCPRNERROR((prntBuf,"sbTblAddTestSubIndex: Test Table's MAXROWSIZE exceeded."));
   }
} /* End of sbTblAddTestSubIndex */

/*
*
*       Fun:   sbLstAddTest
*
*       Desc:  Add a test to the sequence list
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  Void sbLstAddTest
(
 SbTestCb *tstCb
)
#else
PUBLIC  Void sbLstAddTest(tstCb)
SbTestCb *tstCb;
#endif
{
   Txt   prntBuf[SB_PRNTBUF_SIZE];

   TRC2(sbLstAddTest)

   if (sbAccCb.tstLst.length<ACC_TSTSEQLEN)
   {
      /* Assign test control block pointer to list and increment length */
      sbAccCb.tstLst.list[sbAccCb.tstLst.length] = tstCb;
      sbAccCb.tstLst.length++;
   }
   else /* error */
   {
    SBACCPRNERROR((prntBuf,"sbLstAddTest: Sequence list's MAXLENGTH exceeded."));
   }
} /* End of sbLstAddTest */



/*
*
*       Fun:   sbInitTstTbl
*
*       Desc:  Initialize the Acceptance test table
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  Void sbInitTstTbl
(
 Void
)
#else
PUBLIC  Void sbInitTstTbl(Void)
#endif
{
   SbTestCb tstCb;

   TRC2(sbInitTstTbl)

   sbAccCb.C100tstTbl.numrows=0;
   sbAccCb.O100tstTbl.numrows=0;
   sbAccCb.O200tstTbl.numrows=0;
   sbAccCb.O300tstTbl.numrows=0;
   sbAccCb.O400tstTbl.numrows=0;
   sbAccCb.M100tstTbl.numrows=0;
   sbAccCb.M200tstTbl.numrows=0;
   sbAccCb.M300tstTbl.numrows=0;
   sbAccCb.M400tstTbl.numrows=0;

   /* C1xx tests */
   sbTblAddTestIndex(&sbAccCb.C100tstTbl); /*index C100 */

   /*Since the test functions are defined in sb_act1/2/3.c (not included
    *in this make) the references were removed
    */

   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_01, "C.100.01")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_02, "C.100.02")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_03, "C.100.03")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_04, "C.100.04")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_05, "C.100.05")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_06, "C.100.06")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_07, "C.100.07")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_08, "C.100.08")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_09, "C.100.09")
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC100_10, "C.100.10")
#endif

   sbTblAddTestIndex(&sbAccCb.C100tstTbl); /* index C101 */

   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_01, "C.101.01")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_02, "C.101.02")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_03, "C.101.03")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_04, "C.101.04")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_05, "C.101.05")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_06, "C.101.06")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_07, "C.101.07")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_08, "C.101.08")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_09, "C.101.09")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_10, "C.101.10")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_11, "C.101.11")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_12, "C.101.12")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC101_13, "C.101.13")

   sbTblAddTestIndex(&sbAccCb.C100tstTbl); /*index C102 */

   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_01, "C.102.01")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_02, "C.102.02")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_03, "C.102.03")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_04, "C.102.04")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_05, "C.102.05")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_06, "C.102.06")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_07, "C.102.07")
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC102_08, "C.102.08")
#endif

/* sb003.103 - addition - new test cases for path profile configuration */
/* SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE   
   sbTblAddTestIndex(&sbAccCb.C100tstTbl); /*index C103 */

   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_01, "C.103.01")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_02, "C.103.02")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_03, "C.103.03")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_04, "C.103.04")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_05, "C.103.05")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_06, "C.103.06")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_07, "C.103.07")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_08, "C.103.08")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_09, "C.103.09")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_10, "C.103.10")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_11, "C.103.11")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_12, "C.103.12")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_13, "C.103.13")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_14, "C.103.14")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_15, "C.103.15")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC103_16, "C.103.16")

   sbTblAddTestIndex(&sbAccCb.C100tstTbl); /*index C104 */

   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC104_01, "C.104.01")
   SBACCADDTEST(&sbAccCb.C100tstTbl, sbC104_02, "C.104.02")
#endif /* SB_SATELLITE */   

   sbTblAddTestIndex(&sbAccCb.O100tstTbl); /*index O100 */

   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_01, "O.100.01");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_02, "O.100.02");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_03, "O.100.03");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_04, "O.100.04");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_05, "O.100.05");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_06, "O.100.06");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO100_07, "O.100.07");


   sbTblAddTestIndex(&sbAccCb.O100tstTbl); /*index O101 */

   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_01, "O.101.01");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_02, "O.101.02");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_03, "O.101.03");
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_04, "O.101.04");
#endif
/* sb042.102 - Added change for SHT interface and Rolling Up Grade */
#ifdef SB_FTHA 
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_05, "O.101.05");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_05, "O.101.11");
#endif /* SB_FTHA */
#ifdef SB_RUG
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_06, "O.101.06");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_07, "O.101.07");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_08, "O.101.08");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_09, "O.101.09");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO101_10, "O.101.10");
#endif /* SB_RUG #if 0 */


   sbTblAddTestIndex(&sbAccCb.O100tstTbl); /*index O102 */

   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_01, "O.102.01");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_02, "O.102.02");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_03, "O.102.03");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_04, "O.102.04");
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_05, "O.102.05");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_06, "O.102.06");
#endif
#ifdef SB_FTHA
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_07, "O.102.07");
   SBACCADDTEST(&sbAccCb.O100tstTbl, sbO102_07, "O.102.08");
#endif /* SB_FTHA */

   sbTblAddTestIndex(&sbAccCb.O200tstTbl); /* index O200 */

   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_01, "O.200.01");
#if (ERRCLASS & ERRCLS_INT_PAR)/* RFC 4460 -- RTR */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_02, "O.200.02");
#endif
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_03, "O.200.03");
#if (ERRCLASS & ERRCLS_INT_PAR)/* RFC 4460 -- RTR */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_04, "O.200.04");
#endif
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_05, "O.200.05");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_06, "O.200.06");
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_07, "O.200.07");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_08, "O.200.08");
#endif
   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_09, "O.200.09");
#endif /* SCT_ENDP_MULTI_IPADDR */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO200_10, "O.200.10");

   sbTblAddTestIndex(&sbAccCb.O200tstTbl); /* index O201 */

   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_01, "O.201.01");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_02, "O.201.02");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_03, "O.201.03");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_04, "O.201.04");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_05, "O.201.05");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_06, "O.201.06");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_07, "O.201.07");
#if (ERRCLASS & ERRCLS_INT_PAR)/* RFC 4460 -- RTR */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_08, "O.201.08");
#endif
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_09, "O.201.09");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_10, "O.201.10");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_11, "O.201.11");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_12, "O.201.12");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_13, "O.201.13");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_14, "O.201.14");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_15, "O.201.15");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_16, "O.201.16");
#if !defined(SB_ETSI) /* RFC 4460 -- RTR fix */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_17, "O.201.17"); /* SB_VER13 - Added */
#endif
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_18, "O.201.18"); /* SB_VER13 - Added */
 /*sb033.103: These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_19, "O.201.19");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_20, "O.201.20");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_21, "O.201.21");
#endif
#endif
   /* sb035.102 */
   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_22, "O.201.22");
#endif /* SCT_ENDP_MULTI_IPADDR */
   /* sb028.103: Added new test case for multiple TermInd issue */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_23, "O.201.23");
   /* sb029.103: Added test case O.201.24. */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_24, "O.201.24");
   /* sb030.103: Added test case O.201.25. */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_25, "O.201.25");
   /* sb035.103: Added testcases O.201.26, O.201.27 and O.201.28*/
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_26, "O.201.26");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_27, "O.201.27");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO201_28, "O.201.28");

   sbTblAddTestIndex(&sbAccCb.O200tstTbl); /* index O202 */

   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_01, "O.202.01");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_02, "O.202.02");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_03, "O.202.03");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_04, "O.202.04");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_05, "O.202.05");
#if !defined(SB_ETSI) /* RFC 4460 -- RTR fix */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_06, "O.202.06"); /* SB_VER13 - Added */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_07, "O.202.07"); /* SB_VER13 - Added */
#endif 
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_08, "0.202.08");
#endif 
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_09, "O.202.09");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_10, "O.202.10");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_11, "O.202.11");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_12, "O.202.12");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_13, "O.202.13");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_14, "O.202.14");
/* RFC 4460 -- SB_ETSI_1 */
#ifdef SB_ETSI
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_15, "O.202.15");
#endif
/* sb028.103 : Added new test cases to process the data chunk
               bundled with Cookie */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_16, "O.202.16");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_17, "O.202.17");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_18, "O.202.18");
   /* sb029.103: Added test case O.202.19  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_19, "O.202.19");
   /* sb030.103: Added test case O.202.20  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_20, "O.202.20");
   /* sb035.103: Added test case O.202.21  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO202_21, "O.202.21");


   sbTblAddTestIndex(&sbAccCb.O200tstTbl); /* index O203 */
/* sb011.103: Placing Timer Related test cases under seperate flag */
/* sb012.103: Replaced SB_TMR_TST flag with LSB12 */
#ifdef LSB12
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO203_01, "O.203.01");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO203_02, "O.203.02");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO203_03, "O.203.03");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO203_04, "O.203.04");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO203_05, "O.203.05");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO203_06, "O.203.06");
#endif /* LSB12 */

   sbTblAddTestIndex(&sbAccCb.O200tstTbl); /* index O204 */

   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_01, "O.204.01");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_02, "O.204.02");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_03, "O.204.03");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_04, "O.204.04");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_05, "O.204.05");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_06, "O.204.06");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_07, "O.204.07");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_08, "O.204.08");
/* RFC 4460 -- SB_RFC_2, SB_RFC_10 */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO204_09, "O.204.09");

   sbTblAddTestIndex(&sbAccCb.O200tstTbl); /* index O205 */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_01, "O.205.01");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_02, "O.205.02");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_03, "O.205.03");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_04, "O.205.04");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_05, "O.205.05");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_06, "O.205.06");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_07, "O.205.07");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_08, "O.205.08");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_09, "O.205.09");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_10, "O.205.10");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_11, "O.205.11");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_12, "O.205.12");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_13, "O.205.13");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_14, "O.205.14");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_15, "O.205.15");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_16, "O.205.16");
#if !(ERRCLASS & ERRCLS_INT_PAR)/* RFC 4460 -- RTR */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_17, "O.205.17");
#endif
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_18, "O.205.18");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_19, "O.205.19");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_20, "O.205.20");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_21, "O.205.21");
#if !defined(SB_ETSI) /* RFC 4460 -- RTR fix */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_22, "O.205.22");
#endif
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_23, "O.205.23");
/* sb012.103: Added test cases for non-unicast address issue fix */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_25, "O.205.25");
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_26, "O.205.26");
/* sb029.103: Added test case O.205.27  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_27, "O.205.27");
   /* sb030.103: Added test case O.205.28.  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_28, "O.205.28");
   /* sb030.103: Added test case O.205.29  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_29, "O.205.29");
   /* sb030.103: Added test case O.205.30  */
   SBACCADDTEST(&sbAccCb.O200tstTbl, sbO205_30, "O.205.30");


   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O300*/

   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_01, "O.300.01");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_02, "O.300.02");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_03, "O.300.03");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_04, "O.300.04");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_05, "O.300.05");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_06, "O.300.06");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_07, "O.300.07");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_08, "O.300.08");
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_09, "O.300.09");
#endif 
#endif 
/* RFC 4460 -- SB_ETSI_2 */
#ifdef SB_ETSI
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO300_10, "O.300.10");
#endif

   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O301*/
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO301_01, "O.301.01");
/*sb033.103: These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO301_02, "O.301.02");
#endif
#endif

   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O302*/
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO302_01, "O.302.01");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO302_02, "O.302.02");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO302_03, "O.302.03");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO302_04, "O.302.04");
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO302_05, "O.302.05");
#endif
#endif

   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O303*/

   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO303_01, "O.303.01");
/* sb011.103: Placing Timer Related test cases under seperate flag */
/* sb012.103: Replaced SB_TMR_TST flag with LSB12 */
#ifdef LSB12
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO303_02, "O.303.02");
#endif /* LSB12 */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO303_03, "O.303.03");
/* sb011.103: Placing Timer Related test cases under seperate flag */
/* sb012.103: Replaced SB_TMR_TST flag with LSB12 */
#ifdef LSB12
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO303_04, "O.303.04");
#endif /* LSB12 */
   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O304*/

   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO304_01, "O.304.01");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO304_02, "O.304.02");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO304_03, "O.304.03");

   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O305*/

   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_01, "O.305.01");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_02, "O.305.02");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_03, "O.305.03");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_04, "O.305.04");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_05, "O.305.05");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_06, "O.305.06");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_07, "O.305.07");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_08, "O.305.08");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_09, "O.305.09");
/* RFC 4460 -- SB_RFC_2 */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_10, "O.305.10");
  /* sb018.103: Added new test case */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO305_11, "O.305.11");

   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O306*/

   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO306_01, "O.306.01");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO306_02, "O.306.02");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO306_03, "O.306.03");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO306_04, "O.306.04");

/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_ECN
   sbTblAddTestIndex(&sbAccCb.O300tstTbl); /* index O307*/

   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_01, "O.307.01");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_02, "O.307.02");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_03, "O.307.03");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_04, "O.307.04");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_05, "O.307.05");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_06, "O.307.06");
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_07, "O.307.07");
   /* sb014.103: New test case added for ECNE chunk */
   SBACCADDTEST(&sbAccCb.O300tstTbl, sbO307_08, "O.307.08");
#endif /* SB_ECN */   

   sbTblAddTestIndex(&sbAccCb.O400tstTbl); /* index O400*/

   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO400_01, "O.400.01");
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO400_02, "O.400.02");
#if (ERRCLASS & ERRCLS_INT_PAR)/* RFC 4460 -- RTR */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO400_03, "O.400.03");
#endif
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO400_04, "O.400.04");
#endif
#endif

   sbTblAddTestIndex(&sbAccCb.O400tstTbl); /* index O401*/

   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_01, "O.401.01");
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_02, "O.401.02");
#if (ERRCLASS & ERRCLS_INT_PAR)/* RFC 4460 -- RTR */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_03, "O.401.03");
#endif
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_04, "O.401.04");
/* sb011.103: Placing Timer Related test cases under seperate flag */
/* sb012.103: Replaced SB_TMR_TST flag with LSB12 */
#ifdef LSB12
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_05, "O.401.05");
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_06, "O.401.06");
#endif /* LSB12 */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_07, "O.401.07");
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_08, "O.401.08");
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_09, "O.401.09");
#ifdef SB_IPV6_SUPPORTED    /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_10, "O.401.10");
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_11, "O.401.11");
#endif
/* RFC 4460 -- SB_RFC_3 */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_10, "O.401.10");
/* RFC 4460 -- SB_RFC_4 */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_11, "O.401.11");
/* RFC 4460 -- SB_RFC_5 */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_12, "O.401.12");
   /* sb021.103: Added new testcase */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO401_13, "O.401.13");

   sbTblAddTestIndex(&sbAccCb.O400tstTbl); /* index O402*/

   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO402_01, "O.402.01");
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.O400tstTbl, sbO402_02, "O.402.02");
#endif
#endif

/* Still to include - rest of the tests */


   sbTblAddTestIndex(&sbAccCb.M100tstTbl); /*index M100*/

   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM100_01, "M.100.01");
   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM100_02, "M.100.02");

   sbTblAddTestIndex(&sbAccCb.M100tstTbl); /*index M101*/

   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM101_01, "M.101.01");
   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM101_02, "M.101.02");
   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM101_03, "M.101.03");

   sbTblAddTestIndex(&sbAccCb.M100tstTbl); /*index M102*/

   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM102_01, "M.102.01");
   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM102_02, "M.102.02");
   SBACCADDTEST(&sbAccCb.M100tstTbl, sbM102_03, "M.102.03");


   sbTblAddTestIndex(&sbAccCb.M200tstTbl); /*index M200*/

   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM200_01, "M.200.01");
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM200_02, "M.200.02");
#endif
#endif

   sbTblAddTestIndex(&sbAccCb.M200tstTbl); /*index M201*/

   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM201_01, "M.201.01");
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM201_02, "M.201.02");
#endif
#endif

   sbTblAddTestIndex(&sbAccCb.M200tstTbl); /*index M202*/
   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM202_01, "M.202.01");
/*sb033.103 : These test cases will be executed if SCT3 flag is not defined */
#ifndef SCT3
#ifdef SB_IPV6_SUPPORTED   /*  sb032.102 : IPV6 Support Added */
   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM202_02, "M.202.02");
#endif
#endif

   sbTblAddTestIndex(&sbAccCb.M200tstTbl); /*index M203*/

   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM203_01, "M.203.01");
   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM203_02, "M.203.02");

   sbTblAddTestIndex(&sbAccCb.M200tstTbl); /*index M204*/

   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM204_01, "M.204.01");
   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM204_02, "M.204.02");

   sbTblAddTestIndex(&sbAccCb.M200tstTbl); /*index M205*/

   SBACCADDTEST(&sbAccCb.M200tstTbl, sbM205_01, "M.205.01");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /*index M300*/

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM300_01, "M.300.01");
   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM300_02, "M.300.02");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /*index M301*/

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM301_01, "M.301.01");
   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM301_02, "M.301.02");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /*index M302*/

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM302_01, "M.302.01");
   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM302_02, "M.302.02");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /*index M303*/

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM303_01, "M.303.01");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /*index M304*/

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM304_01, "M.304.01");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /*index M305*/

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM305_01, "M.305.01");

/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE   
   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /* index M309 */

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM306_01, "M.306.01");

   sbTblAddTestIndex(&sbAccCb.M300tstTbl); /* index M310 */

   SBACCADDTEST(&sbAccCb.M300tstTbl, sbM307_01, "M.307.01");
#endif /* SB_SATELLITE */   

   sbTblAddTestIndex(&sbAccCb.M400tstTbl); /*index M400*/

   SBACCADDTEST(&sbAccCb.M400tstTbl, sbM400_01, "M.400.01");
   SBACCADDTEST(&sbAccCb.M400tstTbl, sbM400_02, "M.400.02");

} /* End of sbInitTstTbl */


/*
*
*       Fun:   sbParseLine
*
*       Desc:  Parse a line of the config file
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbParseLine
(
 S8 *line
)
#else
PUBLIC  S16 sbParseLine(line)
S8 *line;
#endif
{
   U32 i;
   U8 majorindex;     /* 1=100, 2=200, 3=300, ..., 900 */
   U32 range_min;
   U32 range_max;
   U32 row;
   SbTestCbTbl *tstTbl;
   Txt   prntBuf[SB_PRNTBUF_SIZE];

   majorindex = (U8) (line[2]-(U8)'0');

   switch (line[0])
   {
      case 'C':
         switch (majorindex)
         {
            case 1 :
               tstTbl = &sbAccCb.C100tstTbl;
               break;
            default :
               tstTbl = (SbTestCbTbl *)NULLP;
         }
         break;
      case 'O':
         switch (majorindex)
         {
            case 1 :
               tstTbl = &sbAccCb.O100tstTbl;
               break;
            case 2 :
               tstTbl = &sbAccCb.O200tstTbl;
               break;
            case 3 :
               tstTbl = &sbAccCb.O300tstTbl;
               break;
            case 4:
               tstTbl = &sbAccCb.O400tstTbl;
               break;
            default :
               tstTbl = (SbTestCbTbl *)NULLP;
         }
         break;
      case 'M':
         switch (majorindex)
         {
            case 1 :
               tstTbl = &sbAccCb.M100tstTbl;
               break;
            case 2 :
               tstTbl = &sbAccCb.M200tstTbl;
               break;
            case 3 :
               tstTbl = &sbAccCb.M300tstTbl;
               break;
            case 4 :
               tstTbl = &sbAccCb.M400tstTbl;
               break;
            default :
               tstTbl = (SbTestCbTbl *)NULLP;
         }
         break;
      default:
         tstTbl = (SbTestCbTbl *)NULLP;
   }

   /* Check for valid table */
   if (tstTbl==(SbTestCbTbl *)NULLP)
      RETVALUE(RFAILED);

   row = (line[3]-(U8)'0')*10+(line[4]-(U8)'0');
   if (row>=tstTbl->numrows)
      RETVALUE(RFAILED);

   if (line[6]=='*') /* all subtests */
   {
      range_min = 1;
      if (tstTbl->rowlength[row]==0)
        RETVALUE(RFAILED);

      range_max = tstTbl->rowlength[row];
   }
   else if (line[8]=='-') /* specified range e.g. M100.01-10 */
   {
      range_min = (line[6]-(U8)'0')*10+(line[7]-(U8)'0');
      range_max = (line[9]-(U8)'0')*10+(line[10]-(U8)'0');
   }
   else /* single entry */
   {
      range_min = range_max = (line[6]-(U8)'0')*10+(line[7]-(U8)'0');
   }


   if (range_min>range_max || range_max>tstTbl->rowlength[row])
      RETVALUE(RFAILED);


   /* Add test(s) to sequence list */
   for (i=range_min; i<=range_max; ++i)
   {
      sbLstAddTest(&(tstTbl->tstMatrix[row][i-1]));
      sprintf(prntBuf, "%s\n",tstTbl->tstMatrix[row][i-1].testId);
      SPrint(prntBuf);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   sbAddAllTst
*
*       Desc:  This function will add all possible test in the 
*       Test table.
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbAddAllTst
(
Void
)
#else
PUBLIC  S16 sbAddAllTst(Void)
#endif
{
   U32 i = 1,idx=1;
   U32 range_min;
   U32 range_max;
   U32 row;
   SbTestCbTbl *tstTbl;
   Txt   prntBuf[SB_PRNTBUF_SIZE];

 
  for(idx=1;idx<10;idx++)
  {
    switch (idx)
    {
    case  1:
       tstTbl = &sbAccCb.C100tstTbl;
       break;
    case  2:
       tstTbl = &sbAccCb.O100tstTbl;
       break;
    case  3:
       tstTbl = &sbAccCb.O200tstTbl;
       break;
    case  4:
       tstTbl = &sbAccCb.O300tstTbl;
       break;
    case  5:
       tstTbl = &sbAccCb.O400tstTbl;
       break;
    case  6:
       tstTbl = &sbAccCb.M100tstTbl;
       break;
    case  7:
       tstTbl = &sbAccCb.M200tstTbl;
       break;
    case  8:
       tstTbl = &sbAccCb.M300tstTbl;
       break;
    case  9:
       tstTbl = &sbAccCb.M400tstTbl;
       break;
    default :
    /* sb058.102 : Added to remove compilation warning. */
       RETVALUE(RFAILED);
       break;
    }
 
    for(row=0;row<tstTbl->numrows;row++)
    {
       range_min = 1;
       range_max = tstTbl->rowlength[row];
      /* Add test(s) to sequence list */
      for (i=range_min; i<=range_max; ++i)
      {
         sbLstAddTest(&(tstTbl->tstMatrix[row][i-1]));
         sprintf(prntBuf, "%s\n",tstTbl->tstMatrix[row][i-1].testId);
         SPrint(prntBuf);
      }
    }
   
  }

   RETVALUE(ROK);
}


/*
*
*       Fun:   sbParseCfg
*
*       Desc:  Initialize the Acceptance test table
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbParseCfg
(
 Void
)
#else
PUBLIC S16 sbParseCfg(Void)
#endif
{
   U32 i;
   FILE *fil;
   S8 line[255];
   U32 length;


   sbAccCb.tstLst.length = 0; /* Initialise sequence list */
   sbAccCb.tstLst.index  = 0;

   if ((fil=fopen(CFG_FILE,"r"))==NULL)
   {
      RETVALUE(RFAILED); /* no config file found */
   }

   /* clear buffer */
   for (i=0; i<255; ++i)
   {
      line[i]=0;
   }
   fgets(line, 255, fil);
   length=0;
   while(line[length++]!=0); /* calculate length of ASCIIZ string */
   while (length>=7)
   {
      (Void) sbParseLine(line);

      /* clear buffer */
      for (i=0; i<255; ++i)
      {
         line[i]=0;
      }
      fgets(line, 255, fil);
      length=0;
      while(line[length++]!=0); /* calculate length of ASCIIZ string */
   } /* while not end of file */

   fclose(fil);

  RETVALUE(ROK);

} /* End of sbParseCfg */

/*
*
*       Fun:   sbInitAccCb
*
*       Desc:  Initialize the Acceptance test control block
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbInitAccCb
(
Void
)
#else
PUBLIC S16 sbInitAccCb(Void)
#endif
{
   Txt       prntBuf[PRNTSZE]; /* character string for printing */

   TRC2(sbInitAccCb)

   /* to begin with start the test immediately */
   holdTst = HOLD_TEST_MAX;

   /* Initialize the queue */
   sbAccCb.msgQ.rdPtr = 0;
   sbAccCb.msgQ.wrPtr = 0;

   /* Initialize delay max. The test routines can change this value
    * calling sbSetTimeoutCntr
    */
   delayMax = DELAY_CNTR_MAX;

   /* Install all the Test Handlers in the Test Table */
   sbInitTstTbl();

#ifdef SB_NOCFG_FILE
  /* This option is added for Vxwork environment where file i/o is not available - sb */
   sbAddAllTst();

#else
   /* Read config file and build a sequence list of tests to run */
   if (sbParseCfg() != ROK)   /* requires configuration text file */
   {
      SBACCPRNERROR((prntBuf, "tst: Test Configuration file (%s) not present\n", CFG_FILE));
      RETVALUE(RFAILED);
   }
#endif

   /* Initialize the current test context */
   /*  sb032.102 : IPV6 Support Added */ 
   sbAccCb.curTst.addrType         = CM_NETADDR_IPV4;/*default type forIPV6 */
   sbAccCb.curTst.state            = 0;
   sbAccCb.curTst.subTest          = 1;
   sbAccCb.curTst.subTestsPass     = 0;
   sbAccCb.curTst.subTestsFail     = 0;
   sbAccCb.curTst.bBusyPreTestConf = TRUE;
   sbAccCb.curTst.bBusySubtest     = FALSE;
   sbAccCb.curTst.bConfigDeleted   = FALSE;
   sbAccCb.curTst.bBusyCleanup     = FALSE;
   sbAccCb.curTst.bConfigMask      = 0;
   sbAccCb.curTst.bSapMask         = 0;
   sbAccCb.curTst.bCompleted       = FALSE; /* next (1st) test can start */
   sbAccCb.curTst.bTestsCompleted  = FALSE;
   sbAccCb.cycleCntr               = 1;
   sbAccCb.curTst.gmBuf            = 0;

   /* Initialize the post structure for sending requests from sm to sb */
#ifdef LCSMSBMILSB
   sbAccCb.smPst.selector  = sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC;
#else
   sbAccCb.smPst.selector  = SEL_TC;
#endif

   sbAccCb.smPst.dstProcId = SFndProcId();
   sbAccCb.smPst.srcProcId = SFndProcId();
   sbAccCb.smPst.dstEnt    = ENTSB;
   sbAccCb.smPst.dstInst   = TSTINST_0;
   sbAccCb.smPst.srcEnt    = ENTSM;
   sbAccCb.smPst.srcInst   = TSTINST_0;
   sbAccCb.smPst.prior     = PRIOR0;
   sbAccCb.smPst.route     = RTESPEC;
   sbAccCb.smPst.region    = TSTREG;
   sbAccCb.smPst.pool      = TSTPOOL;

#ifdef SB_FTHA
   sbAccCb.shtPst.dstProcId = SFndProcId();
   sbAccCb.shtPst.srcProcId = SFndProcId();
   sbAccCb.shtPst.dstEnt    = ENTSB;
   sbAccCb.shtPst.dstInst   = TSTINST_0;
   sbAccCb.shtPst.srcEnt    = ENTSH;
   sbAccCb.shtPst.srcInst   = TSTINST_0;
   sbAccCb.shtPst.prior     = PRIOR0;
   sbAccCb.shtPst.route     = RTESPEC;
   sbAccCb.shtPst.region    = TSTREG;
   sbAccCb.shtPst.pool      = TSTPOOL;
   sbAccCb.shtPst.selector  = 0;
#endif /* SB_FTHA */


   /* Initialize the post structure for sending requests from it to sb */
#ifdef LCITLISCT
   sbAccCb.itPst.selector  = sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC;
#else
   sbAccCb.itPst.selector  = SEL_TC;
#endif
   sbAccCb.itPst.dstProcId = SFndProcId();
   sbAccCb.itPst.srcProcId = SFndProcId();
   sbAccCb.itPst.dstEnt    = ENTSB;
   sbAccCb.itPst.dstInst   = TSTINST_0;
   sbAccCb.itPst.srcEnt    = ENTIT;
   sbAccCb.itPst.srcInst   = TSTINST_0;
   sbAccCb.itPst.prior     = PRIOR0;
   sbAccCb.itPst.route     = RTESPEC;
   sbAccCb.itPst.region    = TSTREG;
   sbAccCb.itPst.pool      = TSTPOOL;

  /* Initialize the post structure for sending requests from hi to sb */
#ifdef LCHIUIHIT
   sbAccCb.hiPst.selector  = sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC;
#else
   sbAccCb.hiPst.selector  = SEL_TC;
#endif

   sbAccCb.hiPst.dstProcId = SFndProcId();
   sbAccCb.hiPst.srcProcId = SFndProcId();
   sbAccCb.hiPst.dstEnt    = ENTSB;
   sbAccCb.hiPst.dstInst   = TSTINST_0;
   sbAccCb.hiPst.srcEnt    = ENTHI;
   sbAccCb.hiPst.srcInst   = TSTINST_0;
   sbAccCb.hiPst.prior     = PRIOR0;
   sbAccCb.hiPst.route     = RTESPEC;
   sbAccCb.hiPst.region    = TSTREG;
   sbAccCb.hiPst.pool      = TSTPOOL;

   /* Mark the Acceptance Test is ON */
   sbAccCb.testFlg = TRUE;

   RETVALUE(ROK);
} /* End of sbInitAccCb */

#ifdef SB_FTHA
/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from IUA layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sb_acc1.c
*
*/

#ifdef ANSI
PUBLIC S16 smShtActvTsk
(
Pst     *pst,            /* post */
Buffer  *mBuf            /* message buffer */
)
#else
PUBLIC S16 smShtActvTsk(pst, mBuf)
Pst     *pst;           /* post */
Buffer  *mBuf;          /* message buffer */
#endif
{
   S16 ret;

   TRC3(smShtActvTsk)

   switch (pst->event)
   {
      case EVTSHTCNTRLCFM:             /* Config confirm */
         ret = cmUnpkMiShtCntrlCfm(ShMiShtCntrlCfm, pst, mBuf);
         break;
      default:
         (Void)SPutMsg(mBuf);
         ret = RFAILED;
         break;
   }
   SExitTsk();
   RETVALUE(ret);
} /* end of smShtActvTsk */

#endif /* SB_FTHA */


/********************************************************************30**

         End of file:     sb_acc1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:05 2015

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
/main/3      ---      nct  1.Initial version
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
         sb042.102    hl   1. Added change for SHT interface and Rolling
                              Up Grade
         sb046.102    hl   1. Multiple IP address per endpoint support
         sb057.102    pr   1. Multiple proc ids support added.
         sb058.102    pr   1. Remove compilation warning. 
         sb061.102    pr   1. Remove compiler warnings.
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
         sb003.103    ag   1. Satellite SCTP feature (under compile-time
                              flags SB_ECN & SB_SATELLITE). Added test
                              cases: C.103.*, C.104.*, O.307.*,
                              M.306.*, M.307.*
         sb011.103    nuX  1. Placed timer related test cases under SB_TMR_TST flag.
	 sb012.103    pkaX 1. Non-Unicast Address Fix: Added New test cases.
                           2. Replaced SB_TMR_TST flag with LSB12.
         sb014.103    pkaX 1. Memory leak Fix: Added New test case.
         sb018.103    pkaX 1. BytesOut issue: Added new test case.
/main/4  sb021.103    krkX 1. Added testcase for hBeat timer.
/main/4  sb028.103  ajainx 1. Added new test case for multiple TermInd issue.  
                           2. Added new test cases to process the data chunk
                              bundled with Cookie.
/main/4  sb029.103    krkX 1. Added new testcases O.205.27,O.201.24,O.202.19. 
/main/4  sb030.103    krkX 1. Added new testcases O.201.25,O.202.20,O.205.28,
                              O.205.29 and O.205.30.
/main/4  sb033.103    sdey 1. Modified code based to pass some IPV6 related test 
                              cases while SCT3 flag is defined.
/main/4  sb035.103    vsk  1. Added new testcases O.201.26, O.201.27, O.201.28
                              and O.202.21.                               
*********************************************************************91*/
