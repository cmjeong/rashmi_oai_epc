
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:59:31 2015

     Prg:     up 

*********************************************************************21*/
#ifndef __CMXTA_X__
#define __CMXTA_X__

#ifdef __cplusplus
extern "C" {
#endif
#include "ss_err.h"        /* errors --*/
#include "ss_dep.h"        /* implementation-specific --*/
#include "ss_queue.h"      /* queues --*/
#include "ss_task.h"       /* tasking --*/
#include "ss_msg.h"        /* messaging --*/
#include "ss_mem.h"        /* memory management interface --*/
#include "ss_gen.h"        /* general --*/

#ifdef CMXTA_FTHA_INTEGRATED
#include "cm_ftha.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#include "lry.h"
/* cm_xta_x_001.main_16 - Updated for Psf-Diameter 1.1 release */
#include "lhi.h"
#include "ry.h"

#endif
#include "ss_dep.x"        /* implementation-specific --*/
#include "ss_queue.x"      /* queues --*/
#include "ss_task.x"       /* tasking --*/
#include "ss_timer.x"      /* timers --*/
#include "ss_strm.x"       /* STREAMS --*/
#include "ss_msg.x"        /* messaging --*/
#include "ss_mem.x"        /* memory management interface --*/
#include "ss_drvr.x"       /* driver tasks --*/
#include "ss_gen.x"

/*Updated for FTHA Integration*/ 
#ifdef CMXTA_FTHA_INTEGRATED
#include "cm_ftha.x"
#include "cm_inet.h"
#include "cm_inet.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "lry.x"
/* cm_xta_x_001.main_16 - Updated for Psf-Diameter 1.1 release */
#include "lhi.x"
#include "ry.x"
#endif

/*----------------------------------------------------------------------
             TA: Forward declarations
-----------------------------------------------------------------------*/
EXTERN Txt cmXtaFlagStr[][50];
EXTERN Bool cmXtaFlag[];

/*----------------------------------------------------------------------
             TA: System Topology data structures
-----------------------------------------------------------------------*/
typedef struct cmXtaEntReg
{
   Bool         valid;

   SSTskId      sTskId;

   ProcId       proc;                   /* task processor ID */

   Ent          ent;                    /* task entity ID */
   Inst         inst;                   /* task instance ID */

   Ttype        tskType;                /* normal/permanent/driver */
   Prior        tskPrior;               /* priority of task */

   PAIFS16      initTsk;                /* initialization function */
   ActvTsk      actvTsk;                /* activation function */
}CmXtaEntReg;

typedef struct cmXtaEntInst
{
   Bool         valid;

   ProcId       dstProc;
   Ent          dstEnt;                    /* destination entity   --*/
   Inst         dstInst;                  /* destination instance --*/

   ProcId       srcProc;
   Ent          srcEnt;                    /* source entity        --*/
   Inst         srcInst;                  /* source instance      --*/

   Selector     toSel;             /* selector             --*/
   Selector     fromSel;             /* selector             --*/
}CmXtaEntInst;

#ifdef CMXTA_FTHA_INTEGRATED
/*-- This structure defines a processors make up --*/
typedef struct cmXtaProcs
{
   Bool             isUp;         /* True if the node is up and working */
   Txt              descr[20];    /* Description                  */
   Txt              ipAddr[20];   /* IP address where this processor is running */
   U16              port;         /* Port at which the driver task is listening */
   ProcId           lowProcId;    /* Lower procId in the range of ProcIds on this node */
   ProcId           hiProcId;     /* Higher procId in the range of ProcIds on this node */
}CmXtaProcs;
#endif

typedef struct cmXtaTopology

{
   Bool             valid;
   Txt              descr[100];   /* Description                  */

   U8               sTasks;       /* Number of system tasks       */

   U16              procCnt;
   ProcId           procId[20];

   CmXtaEntReg         entReg[SS_MAX_TTSKS];

   CmXtaEntInst        sel[CMXTA_MAX_INTERFACE];
}CmXtaTopology;

EXTERN CmXtaTopology cmXtaTop[20];

#ifdef CMXTA_FTHA_INTEGRATED
EXTERN CmXtaProcs    cmXtaProc[CMXTA_NODES];
#endif

EXTERN U16 topCount;

/*----------------------------------------------------------------------
             TA: Global flags
-----------------------------------------------------------------------*/
typedef struct cmXtaDirectives
{
   Bool  logAlarm;
   Bool  logTrc;

   Bool  capAlarm;
   Bool  capTrc;

   Bool ignoreMsg;

   Bool delayTest;
   Bool delayShutDown;

   Bool             memCalculate;
   Bool             ignoreDelay;

   Bool        xmlOutput;
   Bool        ignoreSot;
   Bool        partialCfm;
   U32  maxLoad;
   Bool             memFlag;
/* Updated for FTHA */
#ifdef CM_XTA_PSF
   U8             piMode;        /* Peer interface mode */
   U8             fthaInstances; /* Number of Instances i.e. Single or two*/
#endif
}CmXtaDirectives;

/*----------------------------------------------------------------------
             TA: Load data structures
-----------------------------------------------------------------------*/
typedef struct cmXtaLoadDir
{
   Bool loadMode;
   Bool syncLoadSteps;
   Bool loadStarted;
   Bool loadState;
   Bool loadSts;
   Bool clearOnErr;

   U32  maxLoad;
}CmXtaLoadDir;

typedef struct cmXtaLoadStepSts
{
   U32      passCnt;
   U32      failCnt;
   U32      retransCnt;
}CmXtaLoadStepSts;

typedef struct cmXtaLoadSts
{
   U32       rcvdMsg;
   U32       sentMsg;

   U32       dropMsg;

   U32       totalCalls; /* Total number of calls initiated      --*/

   U32       passCalls; /* Total number of calls successful   */ 
   U32       failCalls; /* Total number of calls Failed       */ 
   U32       incompCalls; /* Total number of calls Not completed       */ 

#ifdef CM_XTA_ENHANCE
   CmXtaSoLoadSts sts;
#endif

   U32       ldStartTimeSec;
   U32       ldStartTimeUSec;

}CmXtaLoadSts;

typedef struct cmXtaLoadCb
{
   Bool    inUse;
   Bool    fail;

   U8      curStep;

   Void    *load;
}CmXtaLoadCb;

typedef struct cmXtaLoadStep
{
   U8        cmdType;
   U8        subType;

   U16       seqCnt;
   U16       minSeqCnt;
   U16       maxSeqCnt;

   Bool      expOptMsg;

   Bool      retract;
   Bool      retrans;

   Void     *loadStep;

   CmXtaLoadStepSts sts;
}CmXtaLoadStep;

/*----------------------------------------------------------------------
             TA: XML data structures
-----------------------------------------------------------------------*/
typedef struct cmXtaTCCb   CmXtaTCCb;
typedef struct cmXtaXmlCb  CmXtaXmlCb;
typedef struct cmXtaSpCb   CmXtaSpCb;
typedef S16   (* CmXtaHdl) ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));

typedef struct cmXtaXmlTG
{
   Void      *doc;
   Void      *pre;
   Void      *cfg;
   Void      *shutdown;
}CmXtaXmlTG;

typedef struct cmXtaXmlCmd
{
   Void      *doc;
   Void      *steps;
}CmXtaXmlCmd;

typedef struct cmXtaXmlTC
{
   Void      *doc;
   Void      *pre;
   Void      *cfg;
   Void      *test;
   Void      *clean;
   Void      *shutdown;

   Void      *tg;
}CmXtaXmlTC;

struct cmXtaXmlCb
{
   CmHashListEnt     tstHlEnt;      /* Hashlist entry for termId Key */
   U8                cmdType;
   U8                subType;
   Txt               cmd[50];
   Txt               *doc;
   Bool      parsed;

   /*-- Simple commands --*/
   CmXtaHdl     func;

   Void      *xmlDocNode;
   Void      *tcNode;

   union
   {
      CmXtaXmlTC   xmlTC;
      CmXtaXmlTG   xmlTG;
      CmXtaXmlCmd  xmlCmd;
   }t;
};

struct cmXtaSpCb
{
   Void      *firstStep;
   Void      *curStep;
   U8        rest;                /* test result              */
   U8        state;                 /* test state               */

   Void      *childStep;
   CmXtaXmlCb *xmlCb;

   U16       stepCnt;                 /* step count               */
   /*-- cm_xta_x_001.main_7 loop changes starts--*/
   Void      *reStartStep;  /* Used to store the current step in case of repeat */
   U32       repeatCount;   /* Number of times to repeat the steps */
   U16       repeatStepCnt; /* Used to store the current step count in case of repeat */
   /*--loop changes ends--*/
};

typedef struct cmXtaCmd
{
   Txt            *cmd;
   U8             cmdType;
   U8             subType;
   CmXtaHdl          func;
   Txt            *tc;
   Txt            *doc;
}CmXtaCmd;

/*----------------------------------------------------------------------
             TA: Queue data structures
-----------------------------------------------------------------------*/
typedef struct cmXtaMsgQElm CmXtaMsgQElm;

/* Message queue control block */
typedef S16  (*PMSGFREEFS16) ARGS((CmXtaMsgQElm *qElm));

/* Message queue element for FTHA */
typedef struct cmXtaFthaMsgQElm
{
   Pst           pst;                          /* pst structure         */
   Buffer        *mBuf;
#ifdef CMXTA_FTHA_INTEGRATED
   union
   {
      ShMngmt     shMngmt;
      SgMngmt     sgMngmt;
      MrMngmt     mrMngmt;
      RyMngmt     ryMngmt;
      /* cm_xta_x_001.main_16 - Updated for Psf-Diameter 1.1 release */
      HiMngmt     hiMngmt;
   }u;
#endif

   PMSGFREEFS16      msgFreeFun;       /* Function to free the msg */
}CmXtaFthaMsgQElm;


/* Message queue element */
struct cmXtaMsgQElm
{
   Pst           pst;                          /* pst structure         */

   Void          *data;

   PMSGFREEFS16      msgFreeFun;       /* Function to free the msg */
};

typedef struct cmXtaMsgQ
{
   SLockId           qLock;                   /* locking semaphore           */
   CmXtaMsgQElm      qElm[CMXTA_MSGQ_SIZE];  /* Message Queue               */
   U16               rdPtr;                   /* Next queue loc to read from */
   U16               wrPtr;                   /* Next queue loc to write to  */
} CmXtaMsgQ;

/*----------------------------------------------------------------------
             TA: TC, TG data structures
-----------------------------------------------------------------------*/
/* Test Case Cb */
typedef struct cmXtaTstCb
{
   U8        tcSet;                 /* TC configured            */
   U8        result;                /* test result              */
   U8        memResult;             /* test result              */
   U8        state;                 /* test state               */

   Txt       flag[100];             /* Flag dependency          */
   CmXtaXmlCb   *tc;
} CmXtaTstCb;

/* Test group control structure                 */
typedef struct cmXtaTstGroup
{
   Txt           name[100];                          /* test group name      */
   U8            state;                          /* test group state     */
   U8        memResult;             /* test result              */
   S16           curTest;                        /* current test number  */
   S16           startTest;                      /* current test number  */
   S16           endTest;                        /* last test number     */
   U16           testsDone;                      /* number of tests done */
   U8            result;                         /* test group result    */
   U16           numTests;                       /* # tests in list      */
   U8            tstGrpType;                     /* Unit/Integration     */
   CmXtaTstCb    tstList[CMXTA_MAX_TST];                       /* # tests in group     */
   CmXtaXmlCb       *tg;
}CmXtaTstGrp;

/*----------------------------------------------------------------------
             TA: TC, data structure
-----------------------------------------------------------------------*/
/* Test Case Cb */
struct cmXtaTCCb
{

   U16             tstGrpId;
   U16             tstId;
   CmXtaDirectives    directives;

   SsMemDbgInfo   memPreCfg;
   SsMemDbgInfo   memPreTest;
   SsMemDbgInfo   memPostClean;
   SsMemDbgInfo   memPostShutdown;
   U8        tcSet;                 /* TC configured            */
   U8        result;                /* test result              */
   U8        state;                 /* test state               */
   U8        user;                 /* test state               */

   Bool      busy;
   Bool      guardTmr;
   Bool      suspendTC;
   Bool      noGuardTmr;
   Bool      delayTestTmr;
   Bool      delayShutDownTmr;
   Bool      delayTmr;
   Bool      dropMsg;

   CmXtaXmlCb    *xmlCb;
   CmXtaXmlCb       *ext;

   CmXtaSpCb stack[CMXTA_STACK_DEPTH]; /* the stack             */
   S16        sp;                             /* current stack-pointer */

   U8        err;

   CmTimer         timers[CMXTA_MAX_TMR];

   CmXtaMsgQ        msgQ[CMXTA_MAX_QUEUES];    /* message queues       */
   U32      tcId;

   /*-- Data for internal commands --*/
   U8       timeOutState;

   Void     *data;

   Void     *tcCb;


   U16       minSeqCnt;
   U16       maxSeqCnt;
   U16       seqCnt;
   CmXtaXmlCb   *seqXmlCb;

   U16       setCnt;
   U16       setRcvdCnt;
   Bool      expSet[CMXTA_MAX_EXP_SET_MSG];

   Bool      expSeq;
   Bool      expOptTmr;

   Bool      expOptMsg;
   Bool      lcStep;
#ifdef CM_XTA_PSF
   Queue        piMsgQ;                    /* message queue  */
   U16          shTxnId;
#endif

   /*-- cm_xta_x_001.main_2 : Added mbuf for uncomplete compress stream --*/
   Buffer   *mBuf;
};

/*----------------------------------------------------------------------
             TA: Txn data structure
-----------------------------------------------------------------------*/
typedef struct cmXtaTxnCb
{
   CmHashListEnt  txnHlEnt;     /* Node in SoEntCb->bptransCbLst hash list --*/
   U32            txnId;      /* Local Unique ID (per SSAP)              --*/
   Ptr            cb;
   U32            tcId;
}CmXtaTxnCb;

/*----------------------------------------------------------------------
             TA: Global Access Point
-----------------------------------------------------------------------*/
typedef struct cmXtaCb
{
   /*--------------------- Timer Resoultion --------------------------*/

   /*-- Timer resolution defines the minimum granularity of Timer. --*
    *--                                                            --*
    *-- Possible values of "timerUnit"                             --*
    *-- (1) SS_100MS  = 100 mili second resolution                 --*
    *-- (2) SS_10MS   = 10  mili second resolution                 --*
    *-- (3) SS_1MS    = 1   mili second resolution                 --*
    *--                                                            --*
    *-- "timerPeriod" defines actual value of resolution           --*
    *-- (in combination "timerUnit")                               --*
    *-- Possible values of "timerPeriod"                           --*
    *-- (1) "timerUnit"   = SS_100MS (100 mili second resolution)  --*
    *--       timerPeriod = 1  implies  100 mili second resolution --*     
    *--       timerPeriod = 2  implies  200 mili second resolution --*     
    *--       timerPeriod = 10 implies  1 second resolution        --*     
    *--       and so on                                            --*
    *--                                                            --*
    *-- (2) "timerUnit"   =  SS_10MS  (10 mili second resolution)  --*
    *--       timerPeriod = 1   implies  10 mili second resolution --*     
    *--       timerPeriod = 2   implies  20 mili second resolution --*     
    *--       timerPeriod = 100 implies  1 second resolution       --*     
    *--       and so on                                            --*
    *--                                                            --*
    *-- (3) "timerUnit"   = SS_1MS (1 mili second resolution)      --*
    *--       timerPeriod = 1  implies   1 mili second resolution  --*     
    *--       timerPeriod = 2  implies   2 mili second resolution  --*     
    *--       timerPeriod = 1000 implies 1 second resolution       --*     
    *--       and so on                                            --*
    *--                                                            --*
    *-- IMP: Please note that any timer value configured is in     --*
    *--      units of "timePeriod" cofigured. So if "timePeriod" = --*
    *--      10 ms, in order to confure timer with value 500ms, we --*
    *--      provide its value as 50.                              --*
    *--                                                            --*
    *-- IMP: The value of "timerUnit" is dependent on compile time --*
    *--      flag SS_TICKS_SEC. SS_TICKS_SEC defines the minimum   --*
    *--      granularity available with SSI for timer.The value of --*
    *--      "timerUnit" cannot be less than SS_TICKS_SEC. For     --*
    *--      example, if SS_TICK_SEC is SS_10MS,"timerUnit" cannot --*
    *--      be "SS_1MS". Its always a GOOD idea to keep the value --*
    *--      of "timerUnit" same as SS_TICKS_SEC                   --*/
   Ticks        timerUnit;       /* Timer resolution unit           */
   Ticks        timerPeriod;     /* Timer resolution period         */


   SSTskId          tskId[CMXTA_MAX_TASK];   /* Test Layer Task Id          */
   Pst              pst[CMXTA_MAX_INTERFACE];/*  SIP's VG Pst              */

   TskInit          init;                    /* task initialization info     */

   U8               curTopId;                 /* Current Thread Toploogy Id  */
   U8               curNode;                     /* Current node we are running on index into CmXtaProcs */
   U8               mode;                     /* Test Arch Mode              */
   U8               loopCnt;                  /* Current Count for loop mode */
   U8               maxLoopCnt;               /* Max Count for loop mode     */

   U8        state;                 /* test state               */
   U8        grpState;                 /* test state               */
   U8        err;                 /* test state               */
   U8        result;                 /* test state               */
   U8        TGErr;                 /* test state               */

   Txt              apb[10000];               /* print buf         */
   U32 dbgMask;
   Bool             exitFlag;
   CmHashListCp     xmlLstCp;

   S16               curTstGroup;             /* Current test group           */
   CmXtaTCCb           *curTCCb;             /* Current test group           */
   CmXtaXmlCb          *curTGCb;             /* Current test group           */
   U8        tstGrpCnt;                 /* test state               */
   CmXtaTstGrp       tstGrp[CMXTA_MAX_GRP];

   CmTqCp         tqCp;
   CmTqType       tq[CMXTA_TQ_SIZE];

   U32            txnCounter;
   U32            tcCounter;
   CmHashListCp     txnLstCp;             /* Hashlist of terminations */

   CmXtaDirectives    directives;
   CmXtaLoadDir    loadDir;
   U16       delayTstVal;                 /* test state               */
   U16       delayTstShutDownVal;                 /* test state               */

   CmXtaLoadStep      loadSteps[100];

   U16           nxtLoadIndx;
   U16           basePort;

   CmXtaLoadCb    call[100000];

   CmXtaLoadSts   loadSts;
   U8          masterMode;

   S16         xmlIndent;


   U32         ipcPort;
   U32         portBase;
   U32         localIpcIpAddr;
   U32         remoteIpcIpAddr;
   U8          rel;
}CmXtaCb;

EXTERN CmXtaCb cmXtaCb;


/*Updated for FTHA Integration*/ 
/*----------------------------------------------------------------------
             TA: LSG LSH LMR related declarations
-----------------------------------------------------------------------*/
#ifdef CMXTA_FTHA_INTEGRATED
EXTERN S16 cmXtaLshSendMsg ARGS((Pst   *pst, ShMngmt     *cfm, Buffer   *mBuf));

EXTERN S16 cmXtaUtlLsgSendMsg ARGS(( Pst         *pst, SgMngmt     *cfm, Buffer      *mBuf));
EXTERN S16 cmXtaSmMiLsgCfgCfm ARGS(( Pst         *pst, SgMngmt     *cfm));
EXTERN S16 cmXtaUtlLsgCb ARGS(( CmXtaMsgQElm *qElm));
EXTERN S16 cmXtaHdlSgGenCfgReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgEntCfgReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgCfgCfm ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgEnableNode ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgDisableNode ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgSwapNode ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
/* cm_xta_x_001.main_12: control switch over is implemented for psf-sip load run. */
EXTERN S16 cmXtaControlSwitch ARGS((Void));
EXTERN S16 cmXtaHdlSgAbort ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgUstaCntrlReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgTrcInd ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgDebugCntrlReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgCntrlCfm ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgEntityStsReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgNodeStsReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgStsCfm ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgEntityStaReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgNodeStaReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgSidStaReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgStaCfm ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgStaInd ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlSgTrcInd ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));

EXTERN S16 cmXtaHdlSgTrcCntrlReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));

EXTERN S16 cmXtaSmMiLshCfgCfm ARGS(( Pst         *pst, ShMngmt     *cfm));
EXTERN S16 cmXtaSmMiLshCntrlCfm ARGS(( Pst         *pst, ShMngmt     *cfm));
EXTERN S16 cmXtaSmMiLshStaInd ARGS(( Pst         *pst, ShMngmt     *cfm));
EXTERN S16 cmXtaSmMiLshStsCfm ARGS(( Pst         *pst, ShMngmt     *cfm));
EXTERN S16 cmXtaSmMiLshStaCfm ARGS(( Pst         *pst, ShMngmt     *cfm));
EXTERN S16 cmXtaSmMiLshTrcInd ARGS(( Pst         *pst, ShMngmt     *cfm));
EXTERN Void cmXtaUtlLshSendMsg ARGS(( Pst         *pst, SgMngmt     *cfm, Buffer      *mBuf));
EXTERN S16 cmXtaHdlLshCfgReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlLshCfgCfm ARGS(( CmXtaTCCb         *tcCb, CmXtaSpCb     *spCb));
EXTERN S16 cmXtaHdlLshTrcCntrlReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlLshCntrlCfm ARGS(( CmXtaTCCb         *tcCb, CmXtaSpCb     *spCb));
EXTERN S16 cmXtaHdlLshStsReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlLshStsCfm ARGS((Pst  *pst, ShMngmt *sts));
EXTERN S16 cmXtaUtlLmrSendMsg ARGS(( Pst         *pst, MrMngmt     *cfm, Buffer      *mBuf));
EXTERN S16 cmXtaHdlMrGenCfgReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlMrCfgCfm ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlMrShutDownCntrlReq ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaHdlMrCntrlCfm ARGS(( CmXtaTCCb    *tcCb,   CmXtaSpCb  *spCb));
EXTERN S16 cmXtaSmMiLmrCntrlCfm ARGS((Pst *pst, MrMngmt *cfm));
EXTERN S16 cmXtaUtlLmrCb ARGS(( CmXtaMsgQElm *qElm));
EXTERN S16 cmXtaHdlLshTrcInd ARGS((Pst         *pst, ShMngmt   *trc ));
EXTERN S16 cmXtaUtlLshCb ARGS(( CmXtaMsgQElm *qElm));
#ifdef CM_XTA_RELAY
EXTERN S16 cmXtaRlyGenCfgReq ARGS((  ProcId srcProcId,  ProcId dstProcId ,
                                     U16 nmbChannel));
EXTERN S16 cmXtaRlyChannelCfgReq ARGS(( U16  channelId, ProcId srcProcId,
                                        ProcId dstProcId ,
                                        U32 port,  
                                        Txt *hostName, 
                                        U32 localport,
                                        ProcId localProcId ));
EXTERN S16 cmXtaRlyCfgCfm ARGS(( Pst         *pst, RyMngmt     *cfg));
EXTERN S16 cmXtaUtlLryCb ARGS(( CmXtaMsgQElm *qElm));
EXTERN S16 cmXtaLrySendMsg ARGS(( Pst         *pst, RyMngmt     *cfm, Buffer      *mBuf));
#endif
#ifndef SS_MULTIPLE_PROCS
EXTERN S16   cmXtaFmActvTmr              ARGS((Void));
#else
EXTERN S16   cmXtaFmActvTmr              ARGS((
ProcId proc,
Ent    ent,
Inst   inst));
#endif
EXTERN Void cmXtaFmProcTmr ARGS(( Ptr              cb,          S16              tmrEvnt      ));

#ifndef SS_MULTIPLE_PROCS
EXTERN S16   cmXtaFmActvInit ARGS((Ent entity, Inst inst, Region region, Reason reason));
#else /* SS_MULTIPLE_PROCS */
EXTERN S16 cmXtaFmActvInit ARGS((ProcId proc, 
                            Ent ent, 
                            Inst inst, 
                            Region region, 
                            Reason reason,
                            Void **xxCb));
#endif
EXTERN S16   cmXtaFmActvTsk  ARGS((Pst *pst, Buffer *mBuf));

#ifdef CM_XTA_RELAY
EXTERN S16   cmXtaRelayInit  ARGS((Void));
/*cm_xta_x_001.main_12: relay GenCfgCfm is handeled in XTA */
EXTERN S16   rycmXtaGenCfgCfm ARGS((Pst *pst,RyMngmt *cfg));

#ifndef SS_MULTIPLE_PROCS
EXTERN S16   cmXtaDsmActvInit ARGS((Ent entity, Inst inst, Region region, Reason reason));
#else /* SS_MULTIPLE_PROCS */
EXTERN S16 cmXtaDsmActvInit ARGS((ProcId proc, 
                            Ent ent, 
                            Inst inst, 
                            Region region, 
                            Reason reason,
                            Void **xxCb));
#endif
EXTERN S16   cmXtaDsmActvTsk  ARGS((Pst *pst, Buffer *mBuf));


#endif

#endif
/*----------------------------------------------------------------------
             TA: Result Utility Functions
-----------------------------------------------------------------------*/
EXTERN Void  cmXtaEndTst            ARGS((CmXtaTCCb *tcCb));
EXTERN S16   cmXtaFailTest          ARGS((Void));
EXTERN S16   cmXtaPassTest          ARGS((Void));
EXTERN S16   cmXtaIgnoreTest        ARGS((Void));
PUBLIC Void cmXtaResults ARGS (( Void));
PUBLIC Void cmXtaXmlResults ARGS (( Void));

/*----------------------------------------------------------------------
             Queue Primitives Functions
-----------------------------------------------------------------------*/
EXTERN S16  cmXtaInitQ           ARGS((CmXtaMsgQ *msgQ));
EXTERN Void cmXtaFlushQ          ARGS((CmXtaMsgQ *msgQ));
EXTERN Void cmXtaDispNFlushQ     ARGS((CmXtaMsgQ *msgQ));
EXTERN S16  cmXtaPushMsg         ARGS((CmXtaMsgQ *msgQ, CmXtaMsgQElm *msg));
EXTERN S16  cmXtaPopMsg          ARGS((CmXtaMsgQ *msgQ, CmXtaMsgQElm **msg));
EXTERN S16  cmXtaPeekMsg         ARGS((CmXtaMsgQ *msgQ, CmXtaMsgQElm **msg));
EXTERN S16  cmXtaFlushMsg        ARGS((CmXtaMsgQ *msgQ, CmXtaMsgQElm *msg));
EXTERN S16  cmXtaLenMsgQ         ARGS((CmXtaMsgQ *msgQ));

/*----------------------------------------------------------------------
             Activation and Init funtions
-----------------------------------------------------------------------*/
EXTERN S16   cmXtaActvInit ARGS((Ent entity, Inst inst, Region region, Reason reason));
EXTERN S16   cmXtaActvTsk  ARGS((Pst *pst, Buffer *mBuf));

/* cm_xta_x_001.main_13: Removed the redundant function declarations */

/*----------------------------------------------------------------------
             Internal Module Init/DeInit/Handler functions
-----------------------------------------------------------------------*/
EXTERN S16   cmXtaIntInit  ARGS((Void));
EXTERN S16   cmXtaDirectiveInit  ARGS((Void));
EXTERN S16   cmXtaAppDirectiveInit  ARGS((Void));
EXTERN S16   cmXtaIntDeInit  ARGS((Void));

EXTERN S16   cmXtaHdlIntSend  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntExpect  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntExpSeq  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntExpOpt  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntExpSet  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntTimeout  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntDelay    ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntSuspend  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntInvalid  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntDirective    ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntGlobalDirective    ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntDummy        ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
/*--cm_xta_x_001.main_7 loop changes starts--*/
/*--New handler functions are intorduced to repeat the test steps
    between repeat start and repeat end--*/
EXTERN S16   cmXtaHdlIntRepeatStart  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntRepeatEnd  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntRepeatStartLchCfg  ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
/*--loop changes ends--*/

/* -- new functions for memory utilization and leak detection */
EXTERN S16   cmXtaHdlIntSRegInfoShow ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16   cmXtaHdlIntSLogMemLk    ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));

/*----------------------------------------------------------------------
             Flag Module Init/DeInit/Handler functions
-----------------------------------------------------------------------*/
EXTERN S16   cmXtaFlInit  ARGS((Void));
EXTERN Bool  cmXtaFlIsSet  ARGS((U16 flag));

/*----------------------------------------------------------------------
             XML Module functions
-----------------------------------------------------------------------*/
EXTERN CmXtaXmlCb* cmXtaXmlFind              ARGS((U8 tstGrpId, U8 tstId, Txt *cmd, Bool parse));
EXTERN CmXtaXmlCb* cmXtaXmlFindFromXml    ARGS((Void *curStep));
EXTERN CmXtaXmlCb* cmXtaXmlCreate            ARGS((Txt *cmd, U8 cmdType, U8 subType, CmXtaHdl func, Txt *doc, Txt *tc, Bool parse));
EXTERN S16 cmXtaXmlDelete            ARGS((CmXtaXmlCb *tcCb));
EXTERN S16 cmXtaXmlParse            ARGS((CmXtaXmlCb *tcCb));
EXTERN S16   cmXtaXmlDeInit             ARGS((Void));
EXTERN S16   cmXtaXmlInit               ARGS((Void));
EXTERN S16   cmXtaXmlValidate           ARGS((U8 type));
EXTERN S16   cmXtaXmlGetDocTC           ARGS((CmXtaTCCb  *tcCb, Void *curStep, U16 sp));
EXTERN S16   cmXtaXmlGetDoc             ARGS((CmXtaXmlCb *xmlCb, Void *doc, Void *pre));
EXTERN S16   cmXtaXmlGetVal             ARGS((CmXtaTCCb *tcCb, Void *curStep, U8 type, Txt *attrib, Void *val));
EXTERN Void * cmXtaXmlFirstChildOfType  ARGS((Void *curStep, U16   elmType));
EXTERN Void * cmXtaXmlGetNextOfType     ARGS((Void *curStep, Void *nextStep, U16   elmType));
EXTERN Void * cmXtaXmlNextSiblingOfType     ARGS((Void *curStep, U16   elmType));
EXTERN S16   cmXtaXmlGetValList  ARGS((CmXtaTCCb  *tcCb, Void *curStep, U8 type, U8 sep, Txt *attrib, Void *valList, U8 *length));
EXTERN S16   cmXtaXmlValidateRe  ARGS((CmXtaTCCb  *tcCb, Void *curStep, Txt *msg));

EXTERN S16   cmXtaXmlDumpSimpleCmd           ARGS((Void));
EXTERN S16   cmXtaXmlLoadSimpleCmd           ARGS((U16 cmdCnt, CmXtaCmd *cmdLst));
PUBLIC S16 cmXtaXmlLoadTestGroups ARGS (( Bool        parse));
EXTERN S16   cmXtaXmlLoadTestCases           ARGS((Bool parse));
EXTERN S16   cmXtaXmlLoadCommands           ARGS((Bool parse));

/* cm_xta_x_001.main_13: Removed the redundant function declarations */
EXTERN S16   cmXtaXmlLoadFiles  ARGS((Bool parse));

/*----------------------------------------------------------------------
             Timer Module functions
-----------------------------------------------------------------------*/
#ifndef SS_MULTIPLE_PROCS
#ifndef MT_TMR_CHANGES
EXTERN S16   cmXtaActvTmr              ARGS((Void));
#else
EXTERN S16   cmXtaActvTmr              ARGS((
Ent    ent,
Inst   inst));
#endif
#else
EXTERN S16   cmXtaActvTmr              ARGS((
ProcId proc,
Ent    ent,
Inst   inst));
#endif

EXTERN S16   cmXtaTmrInitQ             ARGS((Void));
EXTERN S16   cmXtaStopTmr              ARGS((S16 timer, Ptr cp));
EXTERN S16   cmXtaStartTmr             ARGS((S16 timer, Ptr cp, U16 timerVal));
EXTERN S16   cmXtaTmrDeInitQ           ARGS((Void));

EXTERN Void   cmXtaProcTmr  ARGS((PTR cb, S16 event));
PUBLIC S16 cmXtaIntPrcTimerExp  ARGS (( CmXtaTCCb *tcCb, S16    event));
/*----------------------------------------------------------------------
             Txn module functions
-----------------------------------------------------------------------*/
EXTERN CmXtaTxnCb*  cmXtaTxnFind               ARGS((U32 txnId));
EXTERN CmXtaTCCb*  cmXtaTxnTstCbFind               ARGS((U32 txnId, Bool del));
EXTERN CmXtaTxnCb*  cmXtaTxnCreate             ARGS((U32 txnId, Ptr cb));
EXTERN S16  cmXtaTxnDelete                    ARGS((CmXtaTxnCb *txnCb));
EXTERN S16 cmXtaTxnInit                       ARGS((Void));
EXTERN S16 cmXtaTxnDeInit                     ARGS((Void));

/*----------------------------------------------------------------------
             Utility functions
-----------------------------------------------------------------------*/
EXTERN Void cmXtaInitHdr               ARGS((Header *hdr, U32 txnId, Ent ent, Inst inst, Elmnt elem, Selector selector));
/*Updated for FTHA Integration*/ 
EXTERN Void cmXtaGetPst                         ARGS((
                                                   Pst *pst, 
                                                   Ent srcEnt, 
                                                   Inst srcInst, 
                                                   Ent dstEnt, 
                                                   Inst dstInst, 
                                                   ProcId srcProcId, 
                                                   ProcId dstProcId,
                                                   Bool   matchProc));

EXTERN S16   cmXtaMasterParseCmdLine      ARGS((Void));
EXTERN S16   cmXtaSlaveParseCmdLine      ARGS((Void));
EXTERN S16   cmXtaLogXml      ARGS((CmXtaTCCb *tcCb, U8 logType));
EXTERN S16   cmXtaRegInfoShow   ARGS((CmXtaTCCb *tcCb, U8 logType, SsMemDbgInfo *memInfo));
EXTERN S16   cmXtaCheckMemory   ARGS((CmXtaTCCb *tcCb));
EXTERN S16 cmXtaFndLenDmndQ ARGS(( QLen  *qLen));

EXTERN S16   cmXtaSlaveParseRdConQ      ARGS((Data data));
EXTERN S16   cmXtaMasterParseRdConQ      ARGS((Data data));
EXTERN S16   cmXtaMasterParseDebug ARGS((Void));
EXTERN Void  cmXtaMasterUsage             ARGS((Void));
EXTERN Void  cmXtaMasterUsageDebug        ARGS((Void));
EXTERN Void  cmXtaSlaveUsage             ARGS((Void));
EXTERN Void cmXtaGetStatus ARGS((Void *curStep, CmStatus *status));
/* cm_xta_x_001.main_15: Changed the product specific flag to common */
#ifdef CM_XTA_PSF
EXTERN Void cmXtaGetState ARGS((Void *curStep, State *state));
#endif /* CM_XTA_PSF */
EXTERN S16 cmXtaValidateStatus ARGS((CmStatus *status, CmStatus *incStatus));
EXTERN S16 cmXtaValidateState ARGS((State *state, State *incState));
EXTERN S16 cmXtaValidatePst ARGS((Pst *pst, Pst *srcPst));

EXTERN S16 cmXtaMasterInitPst            ARGS((Void));

/*----------------------------------------------------------------------
             TA FSM functions
-----------------------------------------------------------------------*/
EXTERN S16  cmXtaTAPstSelfMsg            ARGS((Void *ptr, U8 event));
EXTERN S16 cmXtaTAReq    ARGS((S16 ret));

typedef S16   (* CmXtaTAFsm)        ARGS((S16 ret));

EXTERN S16 cmXtaTAFsmS0    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS1    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS2    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS3    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS4    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS5    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS6    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS7    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS8    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS9    ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS10   ARGS((S16 ret));
EXTERN S16 cmXtaTAFsmS11   ARGS((S16 ret));


/*----------------------------------------------------------------------
             TG FSM functions
-----------------------------------------------------------------------*/
EXTERN S16  cmXtaTGInit      ARGS((Void));
EXTERN S16  cmXtaTGGetNxt      ARGS((Void));
EXTERN S16 cmXtaTGReq    ARGS((S16 ret));

typedef S16   (* CmXtaTGFsm)        ARGS((S16 ret));

EXTERN S16 cmXtaTGFsmS0    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS1    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS2    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS3    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS4    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS5    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS6    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS7    ARGS((S16 ret));
EXTERN S16 cmXtaTGFsmS8    ARGS((S16 ret));


/*----------------------------------------------------------------------
             TC FSM functions
-----------------------------------------------------------------------*/
typedef S16   (* CmXtaTCFsm)        ARGS((CmXtaTCCb *tstCb, S16 ret));

EXTERN S16 cmXtaTCReq    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCEngine    ARGS((CmXtaTCCb *tstCb));
EXTERN S16 cmXtaTCEngineInt    ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb));
EXTERN S16 cmXtaTCSpReset    ARGS((CmXtaTCCb *tstCb));
EXTERN S16 cmXtaTCSpInit    ARGS((CmXtaTCCb *tstCb, CmXtaSpCb *spCb, Void *cmd));
EXTERN S16 cmXtaTCSpResetStepCnt    ARGS((CmXtaTCCb *tstCb));
EXTERN S16 cmXtaTCGetNxtStep    ARGS((CmXtaSpCb *spCb));
EXTERN S16 cmXtaTCGetFirstStep    ARGS((CmXtaSpCb *spCb));
EXTERN S16  cmXtaTCGetNxt      ARGS((Void));

EXTERN S16 cmXtaTCFsmS0    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS1    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS2    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS3    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS4    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS5    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS6    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS7    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS8    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS9    ARGS((CmXtaTCCb *tstCb, S16 ret));
EXTERN S16 cmXtaTCFsmS10   ARGS((CmXtaTCCb *tstCb, S16 ret));

EXTERN S16   cmXtaTCLoadTestCases  ARGS((Bool parse));
EXTERN S16   cmXtaTCLoadCommands  ARGS((Bool parse));

EXTERN S16   cmXtaTCLoadCmd            ARGS((Bool parse));
EXTERN S16   cmXtaTCLoadTC             ARGS((Bool parse));

EXTERN S16   cmXtaTCDelete  ARGS((CmXtaTCCb *tcCb));
EXTERN CmXtaTCCb*   cmXtaTCCreate  ARGS((U8 ctxt, U16 tstGrpId, U16 tstId, Void *ptr));
EXTERN S16   cmXtaTCValidatePre  ARGS((CmXtaTCCb *tcCb, Void *pre));
EXTERN Bool  cmXtaTCValidateStep  ARGS((Void *curStep));
EXTERN S16   cmXtaTCGenCount  ARGS((CmXtaTCCb *tcCb, Txt *str));
EXTERN S16   cmXtaTCSpIncrStepCnt  ARGS((CmXtaTCCb *tcCb));
/* cm_xta_x_001.main_13: Removed the redundant function declarations */

EXTERN S16   cmXtaTCAddTC           ARGS((U16 tstGrpId, U16 tstId));
EXTERN S16   cmXtaTCAddTG           ARGS((U16 tstGrpId, Txt *doc));
/*----------------------------------------------------------------------
             System Init functions
-----------------------------------------------------------------------*/
EXTERN S16   cmXtaRegister  ARGS((Void));
EXTERN S16   cmXtaDeRegister  ARGS((Bool finalShutdown));

EXTERN S16  cmXtaPreInit      ARGS((Void));
EXTERN S16  cmXtaParseDebug   ARGS((Void));

EXTERN S16  cmXtaSlaveInit         ARGS((Void));
EXTERN S16  cmXtaSlavePreInit      ARGS((Void));
EXTERN S16  cmXtaSlaveDeInit       ARGS((Void));

EXTERN S16  cmXtaMasterInit         ARGS((Void));
EXTERN S16  cmXtaMasterPreInit      ARGS((Void));
EXTERN S16  cmXtaMasterDeInit       ARGS((Void));


EXTERN S16  cmXtaMasterTst          ARGS((Void));
EXTERN S16  cmXtaSlaveTst           ARGS((Void));
/*----------------------------------------------------------------------
             Load specific functions 
-----------------------------------------------------------------------*/
EXTERN S16 cmXtaLoadEngine ARGS((Void *msg));
EXTERN Void cmXtaLoadDisplay ARGS((Void));

/* cm_xta_x_001.main_9: MT_SIP changes */
#ifdef SO_MT_SIP
#ifdef SO_MT_SIP_INTDBG

EXTERN S16 cmXtaAppPrintInfo ARGS((Void));
EXTERN S16 cmXtaTuclPrintInfo  ARGS((Void));

#endif
#endif

/* cm_xta_x_001.main_11: IU_UP changes */
#ifdef LX_ACC
EXTERN S16 cmXtaAppPrintInfo ARGS((Void));
EXTERN Void  lxCmPrintSts  ARGS((Void));
#endif


/*----------------------------------------------------------------------
             Application specific functions 
-----------------------------------------------------------------------*/
EXTERN S16 cmXtaAppTst ARGS((Void));
EXTERN S16 cmXtaAppIpcInit ARGS((Void));
EXTERN S16 cmXtaAppIpcDeInit ARGS((Void));

EXTERN S16 cmXtaAppMasterInit ARGS((Void));
EXTERN S16 cmXtaAppMasterDeInit ARGS((Void));
EXTERN S16 cmXtaAppMasterParseCmdLine ARGS((Void));

EXTERN S16 cmXtaAppSlaveInit ARGS((Void));
EXTERN S16 cmXtaAppSlaveDeInit ARGS((Void));
EXTERN S16 cmXtaAppSlaveParseCmdLine ARGS((Void));

EXTERN S16 cmXtaAppDeInit ARGS((Void));
EXTERN Void cmXtaAppMasterUsage ARGS((Void));
EXTERN Void cmXtaAppSlaveUsage ARGS((Void));
EXTERN S16 cmXtaAppTCCreate ARGS((CmXtaTCCb *tcCb));
EXTERN S16 cmXtaAppTCDelete ARGS((CmXtaTCCb *tcCb));
EXTERN S16 cmXtaAppInitQ ARGS((CmXtaMsgQ *msgQ));
EXTERN Void cmXtaAppFlushQ ARGS((CmXtaMsgQ *msgQ));

EXTERN S16 cmXtaAppPyInit ARGS((Void));
EXTERN S16 cmXtaAppPyDeInit ARGS((Void));

/* cm_xta_x_001.main_14 - Fix for compilation warnings */
EXTERN S16 cmXtaAppInit ARGS((Void));
EXTERN S16 cmXtaAppParseCmdLine ARGS((Void));
EXTERN Void cmXtaAppUsage ARGS((Void));
/*----------------------------------------------------------------------
             Load specific functions : to be implemented by App
-----------------------------------------------------------------------*/
EXTERN S16 cmXtaAppLoadEngine ARGS((CmXtaLoadCb *loadCb, Void *loadMsg, Bool retrans, U16 curLoadIndx, U16 retransLoadIndx));
EXTERN S16 cmXtaAppLoadFindnCreate ARGS((Void *msg, Bool  *newCall, CmXtaLoadCb  **loadCb));
EXTERN S16 cmXtaAppLoadDelete ARGS((CmXtaLoadCb  *loadCb, Bool fail));
EXTERN S16 cmXtaAppLoadInit ARGS((Void));
EXTERN S16 cmXtaAppLoadDeInit ARGS((Void));
EXTERN S16 cmXtaAppLoadGetCurStep ARGS((Void *msg, CmXtaLoadCb  *loadCb, U16   *curLoadIndx, U16   *retransLoadIndx));
EXTERN S16 cmXtaAppLoadFreeMsg ARGS((Void *loadMsg));

#ifdef SW_ACC
EXTERN S16 cmXtaAppLoadFreeSwSessions ARGS((void *loadMsg, U16 loadIndex));
#endif

/*----------------------------------------------------------------------
             IPC Data structures
-----------------------------------------------------------------------*/
EXTERN S16  cmXtaAppIpcUdpInit   ARGS((Void));
EXTERN Void cmXtaAppIpcUdpDeInit ARGS((Void));
EXTERN S16  cmXtaAppIpcUdpPstTsk ARGS((Pst *pst, Buffer *mBuf));
#ifdef ENB_RELAY
EXTERN Void cmXtaAppIpcUdpIsTsk  ARGS((UProc *uProc));
EXTERN S16  cmXtaAppIpcUdpGetTsk ARGS((UProc *uProc));
#endif
/*----------------------------------------------------------------------
             C Library Declaration
-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /* __CMXTA_X__ */
/********************************************************************30**

         End of file:     cm_xta.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:59:31 2015

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
/main/2      ----     up  1. Main release
/main/3      ---      ss  1. Added mbuf for uncomplete compress stream
/main/4      ---      sk  1. Updated for FTHA
/main/5      ---      st  1. Added rel(Release Version) field. 
/main/6      ---      aj  1. Updated for FTHA Integration 
/main/7      ----     sy   GCP 2.1 release
/main/8      ---      cm_xta_x_001.main_7  mn 1. Loop changes
/main/9      ---      st  1. Added support for newly introduced
                             timer activation changes under 
                             MT_TMR_CHANGES flag.
/main/10     ---  cm_xta_x_001.main_9    ve  1. MT_SIP changes
/main/12     ---  cm_xta_x_001.main_11   rss 1. IU_UP changes
/main/13     ---  cm_xta_x_001.main_12   ve  1. control switch over is implemented for psf-sip load run.
                                             2. relay GenCfgCfm is handeled in XTA.
/main/14     ---      cm_xta_x_001.main_13  pkaX  1. Removed the redundant function 
                                         declarations
/main/15 cm_xta_x_001.main_14 spoovalingam 1. Fix for compilation warnings
/main/16     ---      cm_xta_x_001.main_15 pka 1. Changed the product specific flag to common.
/main/17     ---      cm_xta_x_001.main_16 nh  1. Updated for Psf-Diameter 1.1 release 
*********************************************************************91*/
