
/********************************************************************20**

     Name:    TCP/UDP Convergence Layer (TUCL)

     Type:    C source file

     Desc:    Upper and Management Interface primitives.

     File:    hi_bdy1.c

     Sid:      tl_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Tue Feb  9 11:15:40 2016

     Prg:     asa

*********************************************************************21*/


/* 
Upper Layer functions interface to the HI Layer user.

The following functions are provided in this file:

Upper layer functions

    HiUiHitBndReq        Bind Request
    HiUiHitUbndReq       Unbind Request
    HiUiHitServOpenReq   Server Open Request
    HiUiHitConReq        Connect Request
    HiUiHitConRsp        Connect Response
    HiUiHitDatReq        Data Request(TCP)
    HiUiHitUDatReq       Unit Data Request(UDP)
    HiUiHitDiscReq       Disconnect Request
    HiUiHitTlsEstReq     TLS Establishment Request

Lower layer functions

    socket calls to common socket library

Layer Management functions

    HiMiLhiCfgReq        Configuration Request
    HiMiLhiStsReq        Statistics Request
    HiMiLhiCntrlReq      Control Request
    HiMiLhiStaReq        Solicited Status Request

System Services

    hiActvInit           Activate task - initialize

The following function are expected from the interface providers:

Upper Interface (hi_ptui.c)
    HiUiHitConInd        Connect Indication
    HiUiHitConCfm        Connect Confirm 
    HiUiHitBndCfm        Bind Confirm
    HiUiHitDatInd        Data Indication
    HiUiHitUDatInd       Unit Data Indication
    HiUiHitDiscInd       Disconnect Indication
    HiUiHitDiscCfm       Disconnect Confirm
    HiUiHitFlcInd        Flow Control Indication 
    HiUiHitTlsEstCfm     Flow Control Indication 

Lower Interface (hi_ptli.c)
    dummy file

Layer Management (hi_ptmi.c)
    HiMiLhiCfgCfm        Configuration Confirm
    HiMiLhiStsCfm        Statistics Confirm 
    HiMiLhiCntrlCfm      Control Confirm
    HiMiLhiStaCfm        Status Confirm 
    HiMiLhiTrcind        Trace Indication

System Services
    SRegTmr        Register timer activation function 
    SDeregTTsk     Deregister tapa task
    SDetachTTsk    Detach tapa task 

    SInitQueue     Initialize Queue
    SQueueFirst    Queue to First Place
    SQueueLast     Queue to Last Place
    SDequeueFirst  Dequeue from First Place
    SFndLenQueue   Find Length of Queue

    SPutMsg        Put Message
    SFndLenMsg     Find Length of Message

    SAddPreMsg     Add Pre Message
    SAddPstMsg     Add Post Message
    SRemPreMsg     Remove Pre Message
    SRemPstMsg     Remove Post Message

    SAddPreMsgMult Add multiple bytes to head of the Message
    SAddPstMsgMult Add multiple bytes from tail of the Message
    SRemPreMsgMult Remove multiple bytes to head of the Message
    SRemPstMsgMult Remove multiple bytes from tail of the Message

    SGetSBuf       Get Static Buffer
    SPutSBuf       Put Static Buffer
    SCatMsg        Concatenate two messages
    SSegMsg        Segments a message buffer
    SInitMsg       Initialize a message buffer pointer

    SChkRes        Check Resources
    SGetDateTime   Get Date and Time
    SGetSysTime    Get System Time

NOTE: For a complete list, please refer to the TUCL Service
      Definition Document.

*/


/* header include files (.h) */

#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general layer */
#include "ssi.h"                /* system services interface */

/* external headers */
#ifdef HI_TLS
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#endif

#include "cm_hash.h"            /* common hash list */
#include "cm_llist.h"           /* common linked list */
#include "cm5.h"                /* common timer */
#include "cm_inet.h"            /* common sockets */
#include "cm_tpt.h"             /* common transport defines */

#ifdef FTHA
#include "sht.h"                /* SHT interface */
#endif

#include "lhi.h"                /* layer management, TUCL  */
#include "hit.h"                /* HIT interface */
#ifdef HI_LKSCTP
#include "sct.h"                /* HIT interface */
#endif

#include "hi.h"                 /* TUCL internal defines */
#include "hi_err.h"             /* TUCL errors */

#ifdef H323_PERF
#include "hc_prf.h"             /* performance measurement */
#endif


/* header/extern include files (.x) */

#include "gen.x"                /* general layer */
#include "ssi.x"                /* system services interface */

#include "cm_hash.x"            /* common hashing */
#include "cm_llist.x"           /* common linked list */
#include "cm_lib.x"             /* common library */
#include "cm5.x"                /* common timer */
#include "cm_inet.x"            /* common sockets */
#include "cm_tpt.x"             /* common transport typedefs */

#ifdef FTHA
#include "sht.x"                /* SHT interface */
#endif

#ifdef HI_LKSCTP
#include <netinet/sctp.h>
#include "sct.x"                /* HIT interface */
#endif
#include "lhi.x"                /* layer management, TUCL */
#include "hit.x"                /* HIT interface */
#include "hi.x"                 /* TUCL internal typedefs */

#ifdef H323_PERF
#include "hc_prf.x"             /* performance measurement */
#endif



/* public variable declarations */

/* hi002.105 (hi025.104) : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS 
PUBLIC HiCb hiCbLst[HI_MAX_INSTANCES];     /* TUCL control block */
PUBLIC HiCb *hiCbPtr;
#else /*  SS_MULTIPLE_PROCS */ 
PUBLIC HiCb  hiCb;         /* TUCL control block */
#endif /*  SS_MULTIPLE_PROCS */ 


/* interface function to system service */


/*  hi004.105 Moved hiActvInit function to hi_bdy1.c for  
*             code reorganization.
*/
/*
*
*       Fun:    hiActvInit
*
*       Desc:   Called from SSI to initialize TUCL.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_ex_ms.c
*
*/
/* hi002.105 (hi025.105) */
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 hiActvInit
(
ProcId procId,         /* procId */
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void **xxCb           /* Protocol Control Block */
)
#else
PUBLIC S16 hiActvInit(procId,entity, inst, region, reason, xxCb)
ProcId procId;         /* procId */
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void **xxCb;           /* Protocol Control Block */
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 hiActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 hiActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#endif /* SS_MULTIPLE_PROCS */
{
#ifdef SS_MULTIPLE_PROCS
   PRIVATE U16 i = 0;
   PRIVATE U16 hiNumCallsToInit = 0;
#endif /* SS_MULTIPLE_PROCS */

   TRC2(hiActvInit);


#ifdef SS_MULTIPLE_PROCS
if(reason != SHUTDOWN)
{
   if(!hiNumCallsToInit)
   {
      for(i = 0; i < HI_MAX_INSTANCES; i++)
         HI_ZERO(&hiCbLst[i],sizeof(HiCb));
   }   
   if(hiNumCallsToInit >= HI_MAX_INSTANCES)
      RETVALUE(FALSE);
   hiCbLst[hiNumCallsToInit].used = TRUE;
   hiCbPtr = &hiCbLst[hiNumCallsToInit];
   *xxCb = (Void *)&hiCbLst[hiNumCallsToInit];
   hiNumCallsToInit++;
}   
#endif /* SS_MULTIPLE_PROCS */
#ifdef SS_MULTIPLE_PROCS
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "hiActvInit(ProcId(%d), Ent(%d), Inst(%d), Region(%d), Reason(%d))\n",
           procId, entity, inst, region, reason));
#else /* SS_MULTIPLE_PROCS */ 
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "hiActvInit(Ent(%d), Inst(%d), Region(%d), Reason(%d))\n",
           entity, inst, region, reason));
   HI_ZERO(&hiCb, sizeof(HiCb));
#endif /* SS_MULTIPLE_PROCS */
 
   /* initialize hiCb */


   hiCb.init.ent        = entity;
   hiCb.init.inst       = inst;
   hiCb.init.region     = region;
   hiCb.init.reason     = reason;
   hiCb.init.cfgDone    = FALSE;
   hiCb.init.pool       = 0;
#ifdef SS_MULTIPLE_PROCS
   hiCb.init.procId = procId;
#else /* SS_MULTIPLE_PROCS */
   hiCb.init.procId = SFndProcId();
#endif /* SS_MULTIPLE_PROCS */
   hiCb.init.acnt       = FALSE;
   hiCb.init.usta       = TRUE;
   hiCb.init.trc        = FALSE;

   /* hi028.201: Added dbgMask and protected under HI_DEBUG flag*/
#ifdef DEBUGP
   hiCb.init.dbgMask    = 0;
#ifdef HI_DEBUG
   hiCb.init.dbgMask = 0xFFFFFFFF; 
#endif
#endif
#ifdef SS_DIAG
   hiCb.init.logMask = 0x0;
#endif
   RETVALUE(ROK);
} /* end of hiActvInit */


/*
*     layer management interface (LHI) primitives
*/


/*
*
*       Fun:    HiMiLhiCfgReq
*
*       Desc:   Configure the layer. Responds with a HiMiLhiCfgCfm
*               primitive.
*
*       Ret:    ROK     - ok
*
*       Notes:  Configuration must be performed in the following 
*               sequence:
*               1) general configuration (STGEN)
*               2) transport sap configuration (STTSAP)
*               3) TLS context configuration (STCTX)
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiCfgReq
(
Pst             *pst,           /* post structure */
HiMngmt         *cfg            /* configuration structure */
)
#else
PUBLIC S16 HiMiLhiCfgReq(pst, cfg)
Pst             *pst;           /* post structure */
HiMngmt         *cfg;           /* configuration structure */
#endif
{
   HiMngmt      cfmMsg;
   S16          ret;
 

   TRC3(HiMiLhiCfgReq);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI012,(ErrVal)0,pst->dstInst,
            "HiMiLhiCfgReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiCfgReq(pst, elmnt(%d))\n",
           cfg->hdr.elmId.elmnt));

   HI_ZERO(&cfmMsg, sizeof (HiMngmt));


   /* hi032.201: Removed locking and unloacking of lmpst lock */
#ifdef HI_RUG
   /* hi028:201: Locking mechanism is used before using lmPst*/
   /* store interface version */
   if (!hiCb.init.cfgDone)
      hiCb.init.lmPst.intfVer = pst->intfVer;
#endif


   switch (cfg->hdr.elmId.elmnt)
   {
      case STGEN:            /* general configuration */
         ret = hiCfgGen(&cfg->t.cfg.s.hiGen);
         break;
 
      case STTSAP:           /* sap configuration */
         ret = hiCfgSap(&cfg->t.cfg.s.hiSap);
         break;

#ifdef HI_TLS
      case STCTX:            /* TLS context configuration */
         ret = hiCfgCtx(&cfg->t.cfg.s.hiCtx);
         break;
#endif

      default:               /* invalid */
         ret = LCM_REASON_INVALID_ELMNT;
         break;
   }


   /* issue configuration confirm */
   hiSendLmCfm(pst, TCFG, &cfg->hdr, (U16)(ret == LCM_REASON_NOT_APPL ?
               LCM_PRIM_OK : LCM_PRIM_NOK), (U16)ret, &cfmMsg);


   RETVALUE(ROK);
} /* HiMiLhiCfgReq() */


/*
*
*       Fun:    HiMiLhiStsReq
*
*       Desc:   Get statistics information. Statistics are
*               returned by a HiMiLhiStsCfm primitive. The
*               statistics counters can be reset using the action
*               parameter:
*                  ZEROSTS      - zero statistics counters
*                  NOZEROSTS    - do not zero statistics counters
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStsReq
(
Pst             *pst,           /* post structure */
Action          action,         /* action to be done */
HiMngmt         *sts            /* statistics structure */
)
#else
PUBLIC S16 HiMiLhiStsReq(pst, action, sts)
Pst             *pst;           /* post structure */
Action          action;         /* action to be done */
HiMngmt         *sts;           /* statistics structure */
#endif
{
   SpId         spId;
   HiMngmt      cfmMsg;
   HiSap        *sap;
   HiAlarmInfo  alInfo;


   TRC3(HiMiLhiStsReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt, EHI013,(ErrVal)0,pst->dstInst,
            "HiMiLhiStsReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiStsReq(pst, action(%d), elmnt(%d))\n",
           action, sts->hdr.elmId.elmnt));
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "SGetDateTime(DateTime(%p))\n", (Ptr)&cfmMsg.t.sts.dt));

   cmMemset((U8*)&alInfo, 0, sizeof(HiAlarmInfo));

   /* initialize the confirm structure */
   HI_ZERO(&cfmMsg, sizeof (HiMngmt));
   SGetDateTime(&cfmMsg.t.sts.dt);

  /*hi002.105 - Check if Stack is Configured */
   if(!hiCb.init.cfgDone)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiMiLhiStsReq(): general configuration not done\n"));
      /* hi003.105 issue a statistics confirm if genCfg not done*/
      hiSendLmCfm(pst, TSTS, &sts->hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
               &cfmMsg);
 
      RETVALUE(ROK); 
   }



   switch (sts->hdr.elmId.elmnt)
   {
      case STGEN:            /* general statistics */
         hiGetGenSts(&cfmMsg.t.sts.s.genSts);
         if (action == ZEROSTS)
            hiZeroGenSts();
         break;


      case STTSAP:           /* SAP statistics */
         /* get the SAP */
         spId = sts->t.sts.s.sapSts.sapId;
         HI_CHK_SPID(spId, LHI_EVENT_STSREQ, alInfo, sap);

         /* get the statistics and optionally reset them */
         hiGetSapSts(&cfmMsg.t.sts.s.sapSts, sap);
         if (action == ZEROSTS)
            hiZeroSapSts(sap);

         break;

/*hi014.105  1. modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
      case STHITHR:            /* Thread statistics */
         hiGetThrSts(pst, &cfmMsg.t.sts.s.thrSts);
         if (action == ZEROSTS)
            hiZeroThrSts();
         break;
#endif /*LHI_THR_STS */

      default:
         hiSendLmCfm(pst, TSTS, &sts->hdr, LCM_PRIM_NOK, 
                     LCM_REASON_INVALID_ELMNT, &cfmMsg);
         RETVALUE(ROK);
   }


   /* issue a statistics confirm */
   hiSendLmCfm(pst, TSTS, &sts->hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL,
               &cfmMsg);


   RETVALUE(ROK);
} /* HiMiLhiStsReq() */


/*
*
*       Fun:    HiMiLhiCntrlReq
*
*       Desc:   Control the specified element: enable or diable
*               trace and alarm (unsolicited status) generation,
*               delete or disable a SAP or a group of SAPs, enable
*               or disable debug printing.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiCntrlReq
(
Pst             *pst,           /* post structure */              
HiMngmt         *ctl            /* pointer to control structure */
)
#else
PUBLIC S16 HiMiLhiCntrlReq(pst, ctl)
Pst             *pst;           /* post structure */              
HiMngmt         *ctl;           /* pointer to control structure */
#endif
{
   Header       *hdr;
   HiMngmt      cfmMsg;
   S16          ret;


   TRC3(HiMiLhiCntrlReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI014,(ErrVal)0,pst->dstInst,
            "HiMiLhiCntrlReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiCntrlReq(pst, elmnt(%d))\n", ctl->hdr.elmId.elmnt));
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "SGetDateTime(DateTime(%p))\n", (Ptr)&ctl->t.cntrl.dt));

   hdr = &ctl->hdr;
   HI_ZERO(&cfmMsg, sizeof (HiMngmt));
   SGetDateTime(&(ctl->t.cntrl.dt));

  /*hi002.105 - Check if Stack is Configured */
   if((!hiCb.init.cfgDone) && (hdr->elmId.elmnt != STGEN))
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiMiLhiCntrlReq(): general configuration not done\n"));
      /* issue a control confirm */
      /* hi003.105 to send cntrl cfm if gen cfg not done */ 
      hiSendLmCfm(pst, TCNTRL, hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
               &cfmMsg);

      RETVALUE(ROK); 
   }

   switch (hdr->elmId.elmnt)
   {
      case STGEN:
         ret = hiCntrlGen(pst, ctl, hdr);
         break;

      case STTSAP: 
         ret = hiCntrlSap(pst, ctl, hdr);
         break;

      case STGRTSAP:
         ret = hiCntrlSapGrp(pst, ctl, hdr);
         break;

      default:
         HILOGERROR_INT_PAR(EHI015, hdr->elmId.elmnt, 0,
            "HiMiLhiCntrlReq(): bad element in control request");
         ret = LCM_REASON_INVALID_ELMNT;
         break;
   }

   /* hi003.105 HI_MULTI_THREADED flag removed for shutdown cfm*/
   if (ret == LHI_REASON_OPINPROG)
   {
      hiSendLmCfm(pst, TCNTRL, hdr, LCM_PRIM_OK_NDONE,
                  LCM_REASON_NOT_APPL, &cfmMsg);
      RETVALUE(ROK);
   }


   /* issue a control confirm primitive */
   hiSendLmCfm(pst, TCNTRL, hdr, (U16)(ret == LCM_REASON_NOT_APPL ?
               LCM_PRIM_OK : LCM_PRIM_NOK), (U16)ret, &cfmMsg);


   RETVALUE(ROK); 
} /* HiMiLhiCntrlReq() */


/*
*
*       Fun:    HiMiLhiStaReq
*
*       Desc:   Get status information. Responds with a
*               HiMiLhiStaCfm primitive.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStaReq
(
Pst             *pst,           /* post structure */
HiMngmt         *sta            /* management structure */
)
#else
PUBLIC S16 HiMiLhiStaReq(pst, sta)
Pst             *pst;           /* post structure */
HiMngmt         *sta;           /* management structure */
#endif
{
   Header       *hdr;
   HiMngmt      cfmMsg;


   TRC3(HiMiLhiStaReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI016,(ErrVal)0,pst->dstInst,
            "HiMiLhiStaReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf, "HiMiLhiStaReq(pst, elmnt(%d))\n",
           sta->hdr.elmId.elmnt));

   hdr = &(sta->hdr);
   HI_ZERO(&cfmMsg, sizeof (HiMngmt));

   /* hi002.105 - fill the date and time */
   SGetDateTime(&cfmMsg.t.ssta.dt);

  /*hi002.105 - Check if Stack is Configured */

   if(!hiCb.init.cfgDone && hdr->elmId.elmnt == STTSAP)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiMiLhiStaReq(): general configuration not done\n"));
      hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, 
                  LCM_REASON_GENCFG_NOT_DONE, &cfmMsg);
 
      RETVALUE(ROK); 
   }


      

   switch (hdr->elmId.elmnt)
   {
      case STSID:               /* system ID */
         hiGetSid(&cfmMsg.t.ssta.s.sysId);
         break;


      case STTSAP:              /* SAP status */
      {
         SpId   spId;
         HiSap  *sap;

         spId = sta->t.ssta.s.sapSta.spId;

#if (ERRCLASS & ERRCLS_INT_PAR)
         /* validate the SAP Id */
         if (spId >= (SpId)hiCb.cfg.numSaps  ||  spId < 0
               ||  !(sap = hiCb.saps[spId]))
         {
            HILOGERROR_INT_PAR(EHI017, spId, 0,
               "HiMiLhiStaReq(): spId out of range");
            hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, 
                        LHI_REASON_INV_SPID, &cfmMsg);
            RETVALUE(ROK);
         }
#else
         /* get the SAP */
         sap = hiCb.saps[spId];
#endif

#ifdef HI_RUG
         /* fill up interface version information */
         cfmMsg.t.ssta.s.sapSta.remIntfValid    = sap->remIntfValid;
         cfmMsg.t.ssta.s.sapSta.selfIfVer       = HITIFVER;
         cfmMsg.t.ssta.s.sapSta.remIfVer        = sap->uiPst.intfVer;
#endif

         /* get the status of the transport sap */
         cfmMsg.t.ssta.s.sapSta.spId    = sap->spId;
         cfmMsg.t.ssta.s.sapSta.state   = sap->state;
         break;
      }


      default:
         HILOGERROR_INT_PAR(EHI018, hdr->elmId.elmnt, 0,
            "HiMiLhiStaReq(): invalid element in status request");
         hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, 
                     LCM_REASON_INVALID_ELMNT, &cfmMsg);
         RETVALUE(ROK);
   }




   /* issue a status confirm primitive */
   hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL, 
               &cfmMsg);
 

   RETVALUE(ROK);
} /* HiMiLhiStaReq() */


#ifdef FTHA
/*
*
*       Fun:    HiMiShtCntrlReq
*
*       Desc:   Used by the system agent.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiShtCntrlReq
(
Pst             *pst,           /* post structure */
ShtCntrlReqEvnt *reqInfo        /* control request event */
)
#else
PUBLIC S16 HiMiShtCntrlReq(pst, reqInfo)
Pst             *pst;           /* post structure */
ShtCntrlReqEvnt *reqInfo;       /* control request event */
#endif
{
   S32                  i, j;
   Bool                 found;
   HiSap                *sap;
   Pst                  repPst;
   HiThrMsg             tMsg;
   ShtCntrlCfmEvnt      cfmInfo;


   TRC3(HiMiShtCntrlReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI019,(ErrVal)0,pst->dstInst,
            "HiMiShtCntrlReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */

   HI_ZERO(&repPst, sizeof (Pst));
   HI_ZERO(&cfmInfo, sizeof (ShtCntrlCfmEvnt));


   /* fill reply pst structure */
   repPst.dstProcId = pst->srcProcId;
   repPst.dstEnt    = pst->srcEnt;
   repPst.dstInst   = pst->srcInst;
   repPst.prior     = reqInfo->hdr.response.prior;
   repPst.route     = reqInfo->hdr.response.route;
   repPst.selector  = reqInfo->hdr.response.selector;
   repPst.region    = reqInfo->hdr.response.mem.region;
   repPst.pool      = reqInfo->hdr.response.mem.pool;
   repPst.event     = EVTSHTCNTRLCFM;
   repPst.srcProcId = pst->dstProcId;
   repPst.srcEnt    = ENTHI;
   repPst.srcInst   = pst->dstInst;

   /* fill reply transaction Id */
   cfmInfo.transId  = reqInfo->hdr.transId;

#ifdef HI_RUG
   /* fill request type */
   cfmInfo.reqType  = reqInfo->reqType;
#endif


   /* check if general configuration done */
   if (!hiCb.init.cfgDone)
   {
      cfmInfo.status.status = LCM_PRIM_NOK;
      cfmInfo.status.reason = LCM_REASON_GENCFG_NOT_DONE;
      HiMiShtCntrlCfm(&repPst, &cfmInfo);

      RETVALUE(ROK);
   }


   /* fill status value */
   cfmInfo.status.reason = LCM_REASON_NOT_APPL;

   switch (reqInfo->reqType)
   {
      case SHT_REQTYPE_BND_ENA:   /* SH control bind enable */
         /* TUCL does not have bind enable */
         cfmInfo.status.reason = LCM_REASON_LYR_SPECIFIC;
         break;


      case SHT_REQTYPE_UBND_DIS:  /* SH control unbind disable */
         found = FALSE;
         for (i = 0;  i < (S32)hiCb.cfg.numSaps;  i++)
         {
            sap = hiCb.saps[i];
            if (!sap)
               continue;

            switch (reqInfo->s.ubndDis.grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((sap->uiPst.dstProcId == reqInfo->s.ubndDis.dstProcId) && 
                      (sap->uiPst.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
                      (sap->uiPst.dstInst == reqInfo->s.ubndDis.dstEnt.inst) &&
                      (sap->contEnt != ENTSM))
                     found = TRUE;
                  break;

               case SHT_GRPTYPE_ENT:
                  if ((sap->uiPst.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
                      (sap->uiPst.dstInst == reqInfo->s.ubndDis.dstEnt.inst) &&
                      (sap->contEnt != ENTSM))
                     found = TRUE;
                  break;

               default:
                  cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                  break;
            }

            if (found)
            {
               found = FALSE;

               if (!sap->pendOp.flag  &&  !hiCb.pendOp.flag)
               {
                  tMsg.type = HI_THR_DISSAP;
                  tMsg.spId = sap->spId;
                  for (j = 0;  j < hiCb.numFdGrps;  j++)
                     hiSendThrMsg((U16)j, &tMsg);
               }

#ifdef HI_RUG
               if (sap->verContEnt != ENTSM)
                  sap->remIntfValid = FALSE;
#endif
            }
         }

#ifdef HI_RUG
         /* delete stored version info */
         for (i = (S32)(hiCb.numIntfInfo - 1);  i >= 0;  i--)
         {
            if ((hiCb.intfInfo[i].grpType == reqInfo->s.ubndDis.grpType) &&
                (hiCb.intfInfo[i].dstProcId ==
                                              reqInfo->s.ubndDis.dstProcId) &&
                (hiCb.intfInfo[i].dstEnt.ent ==
                                              reqInfo->s.ubndDis.dstEnt.ent) &&
                (hiCb.intfInfo[i].dstEnt.inst ==
                                              reqInfo->s.ubndDis.dstEnt.inst))
            {
               /* Delete verson info by copying the last version
                * info into current location.
                */
               cmMemcpy((U8 *)&hiCb.intfInfo[i],
                        (U8 *)&hiCb.intfInfo[hiCb.numIntfInfo - 1],
                        sizeof (ShtVerInfo));
               hiCb.numIntfInfo--;
            }
         }
#endif /* HI_RUG */

         break;


#ifdef HI_RUG
      case SHT_REQTYPE_GETVER:  /* SH control get interface version */
         hiGetVer(&cfmInfo.t.gvCfm);
         break;


      case SHT_REQTYPE_SETVER:  /* SH control set interface version */
         hiSetVer(&reqInfo->s.svReq, &cfmInfo.status);
         break;
#endif /* HI_RUG */          


      default:
         cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
         break;
   }


   /* response is sent without waiting for bind or unbind to complete */
   cfmInfo.status.status =
      (cfmInfo.status.reason == LCM_REASON_NOT_APPL ?
       LCM_PRIM_OK : LCM_PRIM_NOK);
   HiMiShtCntrlCfm(&repPst, &cfmInfo);


   RETVALUE(ROK);
} /* HiMiShtCntrlReq() */
#endif /* FTHA */


/*
*     upper interface (HIT) primitives
*/


/*
*
*       Fun:    HiUiHitBndReq
*
*       Desc:   Binds a service user to TUCL. A TSAP is assigned
*               for this bind and the identity of the service user
*               is recorded. A bind confirm primitive is then
*               issued.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitBndReq
(
Pst            *pst,            /* post structure */
SuId            suId,           /* service user id */
SpId            spId            /* service provider id */
)
#else
PUBLIC S16 HiUiHitBndReq(pst, suId, spId)
Pst            *pst;            /* post structure */
SuId            suId;           /* service user id */
SpId            spId;           /* service provider id */
#endif
{
   HiSap        *sap;
   HiAlarmInfo  alInfo;
#ifdef HI_RUG
   U16          i;
   Bool         found;
#endif


   TRC3(HiUiHitBndReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI020,(ErrVal)0,pst->dstInst,
            "HiUiHitBndReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   


   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitBndReq(pst, suId(%d), spId(%d))\n",
          suId, spId));
 
   cmMemset((U8*)&alInfo, 0, sizeof(HiAlarmInfo));

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_BNDREQ, alInfo, sap);


   /* If the SAP is already bound, nothing happens here and a bind
    * confirm is issued.
    */
   if (sap->state == HI_ST_BND)
   {
      HiUiHitBndCfm(&sap->uiPst, suId, CM_BND_OK);
      RETVALUE(ROK);
   }


   /* copy bind configuration parameters */
   sap->suId            = suId;
   sap->uiPst.dstProcId = pst->srcProcId;
   sap->uiPst.dstEnt    = pst->srcEnt;
   sap->uiPst.dstInst   = pst->srcInst;
   sap->uiPst.srcProcId = pst->dstProcId;
   sap->uiPst.srcInst   = pst->dstInst;

   /* duplicate Psts for multi-threaded case */
   HI_DUPLICATE_SAP_PST(sap, sap->uiPst);


#ifdef HI_RUG
   /* find interface version from stored info */
   if (!sap->remIntfValid)
   {
      found = FALSE;
      for (i = 0; i < hiCb.numIntfInfo && !found; i++)
      {
         if (hiCb.intfInfo[i].intf.intfId == HITIF)
         {
            switch (hiCb.intfInfo[i].grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((hiCb.intfInfo[i].dstProcId == pst->srcProcId) &&
                      (hiCb.intfInfo[i].dstEnt.ent == pst->srcEnt) &&
                      (hiCb.intfInfo[i].dstEnt.inst == pst->srcInst))
                     found = TRUE;
                     break;

               case SHT_GRPTYPE_ENT:
                  if ((hiCb.intfInfo[i].dstEnt.ent ==pst->srcEnt) &&
                      (hiCb.intfInfo[i].dstEnt.inst == pst->srcInst))
                     found = TRUE;
                     break;

               default:
                  break;
            }
         }
      }

      if (!found)
      {
         HILOGERROR_INT_PAR(EHI021, spId, pst->dstInst,
              "HiUiHitBndReq(): remIntfver not available");

         /* generate alarm to layer manager */
         alInfo.spId = spId;
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_BNDREQ,
                     LCM_CAUSE_SWVER_NAVAIL, &alInfo);

         /* send NOK to service user layer */
         HiUiHitBndCfm(&sap->uiPst, suId, CM_BND_NOK);

         RETVALUE(ROK);
      } 

      sap->uiPst.intfVer = hiCb.intfInfo[i-1].intf.intfVer;
      sap->remIntfValid = TRUE;          
   }
#endif /* HI_RUG */


   /* SAP state is now bound and enabled */
   sap->state = HI_ST_BND;


   /* issue a bind confirm */
   HiUiHitBndCfm(&sap->uiPst, suId, CM_BND_OK);


   RETVALUE(ROK);
} /* HiUiHitBndReq() */


/*
*
*       Fun:    HiUiHitUbndReq
*
*       Desc:   Unbind a service user from TUCL. All connections
*               are closed and the TSAP is unassigned.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitUbndReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
Reason          reason          /* cause for unbind operation */
)
#else
PUBLIC S16 HiUiHitUbndReq(pst, spId, reason)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
Reason          reason;         /* cause for unbind operation */
#endif
{
   S16          ret;
   U16          i;
   HiSap        *sap;
   HiThrMsg     tMsg;
   HiAlarmInfo  alInfo;


   TRC3(HiUiHitUbndReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI022,(ErrVal)0,pst->dstInst,
            "HiUiHitUBndReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitUbndReq(pst, spId(%d), reason(%d))\n",
          spId, reason));
 
   cmMemset((U8*)&alInfo, 0, sizeof(HiAlarmInfo));

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_BNDREQ, alInfo, sap);


   /* return if SAP is unbound */
   if (sap->state == HI_ST_UBND)
      RETVALUE(ROK);


   /* change SAP state to configured but not bound */
   sap->state = HI_ST_UBND;


   /* Send a disable SAP message to each group. The group
    * threads will close all connections associated with the
    * SAP.
    */
   tMsg.type = HI_THR_DISSAP;
   tMsg.spId = sap->spId;
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      ret = hiSendThrMsg(i, &tMsg);
      if (ret != ROK)
      {
         /* we're left in an unstable state! */
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiHitUbndReq(): send message to group thread failed\n"));
         RETVALUE(RFAILED);
      }
   }


   RETVALUE(ROK);
} /* HiUiHitUbndReq() */


/*
*
*       Fun:    HiUiHitServOpenReq
*
*       Desc:   Open a server on the address provided. TUCL
*               creates a new non-blocking socket and binds it to
*               the specified local address. Any socket options
*               specified in tPar are set. A connection control
*               block is created and assigned to an fd group. The
*               group thread issues a HiUiHitConCfm primitive on
*               success; a disconnect indication is sent in case
*               of any error.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
* 
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitServOpenReq 
(
Pst             *pst,           /* post stucture */
SpId            spId,           /* service provider SAP Id */
UConnId         servConId,      /* service user's connection Id */
CmTptAddr       *servTAddr,     /* transport address of the server */
CmTptParam      *tPar,          /* transport options */
CmIcmpFilter    *icmpFilter,    /* filter parameters */
U8              srvcType        /* service type */
)
#else
PUBLIC S16 HiUiHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst             *pst;           /* post stucture */
SpId            spId;           /* service provider SAP Id */
UConnId         servConId;      /* service user's connection Id */
CmTptAddr       *servTAddr;     /* transport address of the server */
CmTptParam      *tPar;          /* transport options */
CmIcmpFilter    *icmpFilter;    /* filter parameters */
U8              srvcType;       /* service type */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   U8           type;
   S16          backLog = 0;
 /* hi005.105(hi023.104) - Store the IP TOS*/
   U8             i;         /* loop counter */


   TRC3(HiUiHitServOpenReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI023,(ErrVal)0,pst->dstInst,
            "HiUiHitServOpenReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitServOpenReq(pst, spId(%d), servConId(%ld), "
          "servTAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, servConId, (Ptr)servTAddr, (Ptr)tPar, srvcType));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitServOpenReq(pst, spId(%d), servConId(%d), "
          "servTAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, servConId, (Ptr)servTAddr, (Ptr)tPar, srvcType));
#endif

   

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_SERVOPENREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_SERVOPENREQ, alInfo);


   /* must have sufficient resources to establish a connection */
	/* hi025.201 Gaurd the check resource implementation under the 
	 * flag HI_NO_CHK_RES */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongStrt)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_OUTOF_RES);
      RETVALUE(ROK);
   }
#endif /* HI_NO_CHK_RES */


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check server transport address */
   if (!HI_CHK_ADDR(servTAddr))
   {
      HILOGERROR_INT_PAR(EHI024, 0, 0,
         "HiUiHitServOpenReq(): invalid server address");
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_SERVOPENREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* for ICMP, filter must be provided */
   if (((srvcType & 0x0F) == HI_SRVC_RAW_ICMP
            &&  !HI_CHK_ICMPFILTER(icmpFilter)))
   {
      HILOGERROR_INT_PAR(EHI025, 0, 0,
         "HiUiHitServOpenReq(): invalid filter parameter");
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_FILTER_TYPE_COMB;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_SERVOPENREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

#ifdef HI_TLS
   /* for TLS, a valid context Id must be provided */
   if ((srvcType & 0x0F) == HI_SRVC_TLS
       &&  (!tPar  ||  tPar->type != CM_TPTPARAM_TLS
            ||  tPar->u.tlsParam.ctxId < 0
            ||  tPar->u.tlsParam.ctxId >= hiCb.cfg.numContexts
            ||  hiCb.tlsContexts[tPar->u.tlsParam.ctxId].cfg.ctxId
                  == HI_INVALID_OSSL_CTX))
   {
      HILOGERROR_INT_PAR(EHI026, 0, 0,
         "HiUiHitServOpenReq(): invalid TLS context");
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_PARAM;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_SERVOPENREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }
#endif /* HI_TLS */
#endif /* ERRCLS_INT_PAR */


   /* allocate and initialize a conCb for this server */
   ret = hiAllocConCb(sap, servConId, srvcType, &type, &conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_SMEM_ALLOC_ERR);
      RETVALUE(RFAILED);
   }


   /* Open and set up the server socket. ICMP is handled
    * separately, later.
    */
   if (conCb->protocol != CM_PROTOCOL_ICMP)
   {
      ret = hiCreateSock(TRUE, type, servTAddr, tPar, conCb);

      if (ret != ROK)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, conCb->suConId, ret);
         HI_FREECONCB(conCb);
         RETVALUE(RFAILED);
      }

      /* need to listen for stream type connections */
      if (type == CM_INET_STREAM) 
      {
         if (tPar  &&  tPar->type == CM_TPTPARAM_SOCK)
            backLog = tPar->u.sockParam.listenQSize;

#ifdef HI_TLS
         if (tPar->type == CM_TPTPARAM_TLS)
            backLog = tPar->u.tlsParam.listenQSize;
#endif

         ret = HI_LISTEN(&conCb->conFd, backLog);
         if (ret != ROK)
         {
            HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_SOCK_LSTN_ERR);
            HI_CLOSE_SOCKET(&conCb->conFd);
            HI_FREECONCB(conCb);
            HI_INC_ERRSTS(hiCb.errSts.sockLstnErr);
            RETVALUE(RFAILED);
         }
      }

#ifdef HI_TLS
      /* store the context Id for TLS connections */
      if (tPar->type == CM_TPTPARAM_TLS)
         conCb->tlsConCb.ctxId = tPar->u.tlsParam.ctxId;
#endif
   }


#ifdef IPV6_SUPPORTED 
   /* for IPv6 addresses, set some connection flags */
   if (servTAddr->type == CM_TPTADDR_IPV6)
   {
      if (conCb->flag & HI_FL_RAW)
         conCb->flag |= HI_FL_RAW_IPV6;
#ifdef IPV6_OPTS_SUPPORTED
      if (conCb->protocol == CM_PROTOCOL_RSVP)
         conCb->ipv6OptsReq = TRUE;
#endif
   }
#endif /* IPV6_SUPPORTED */


   /* set connection state */
   conCb->state = (type == CM_INET_STREAM
                     ? HI_ST_SRV_LISTEN
                     : HI_ST_CONNECTED);


   /* Complete the connection control block: get an spConId and
    * put it in the SAP's connections hash list.
    */
   ret = hiCompleteConCb(conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_CONID_NOT_AVAIL);
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_SERVOPENREQ,
                  LHI_CAUSE_CONID_NOT_AVAIL, &alInfo);
      if (conCb->protocol != CM_PROTOCOL_ICMP)
         HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* ICMP filters specified? */
   if (HI_CHK_ICMPFILTER(icmpFilter))
   {
      /* Process the specified filters and store them in the
       * connection.
       */
      ret = hiProcessIcmpReq(conCb, icmpFilter);
      if (ret != ROK)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INTERNAL_ERR);
         HI_FREECONCB(conCb);
         RETVALUE(RFAILED);
      }
   }
   /* hi002.105 (hi023.104) - Store the IP TOS*/
   conCb->ipTos= 0xff;
   /* hi018.201: Added tPar Null check */
   for (i = 0; ((tPar != NULLP) && (i < tPar->u.sockParam.numOpts && tPar->type != CM_TPTPARAM_NOTPRSNT)); i++)
   {
           CmSockOpts *sOpts = &(tPar->u.sockParam.sockOpts[i]);
           if (sOpts->option == CM_SOCKOPT_OPT_TOS )
           {
               conCb->ipTos= (U8)sOpts->optVal.value;
               break;
           }
   }



   /* assign the connection to an fd group */
   ret = hiAssignConCb(conCb, HI_THR_ADDCON_CONCFM);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INTERNAL_ERR);
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_SERVOPENREQ,
                  LHI_CAUSE_INTPRIM_ERR, &alInfo);
      if (conCb->protocol != CM_PROTOCOL_ICMP)
         HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* update number of connections stat */
   HI_INC_TXSTS(sap, sap->txSts.numCons);


   /* connect confirm is issued from the thread */


   RETVALUE(ROK);
} /* HiUiHitServOpenReq() */


/*
*
*       Fun:    HiUiHitConReq
*
*       Desc:   Open a new client connection. TUCL binds a new
*               non-blocking socket to the local address specified
*               and connects to the remote address specified. A
*               new connection control block is created and
*               assigned to an fd group. The group thread issues a
*               HiUiHitConCfm primitive on success; a
*               disconnect indication is issued to the service
*               user in case of any failure.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitConReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider id */
UConnId         suConId,        /* service user's connection id */
CmTptAddr       *remAddr,       /* remote address */
CmTptAddr       *localAddr,     /* local address */
CmTptParam      *tPar,          /* transport parameters */
U8              srvcType        /* service type */
)
#else
PUBLIC S16 HiUiHitConReq(pst, spId, suConId, remAddr, localAddr,
                         tPar, srvcType)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider id */
UConnId         suConId;        /* service user's connection id */
CmTptAddr       *remAddr;       /* remote address */
CmTptAddr       *localAddr;     /* local address */
CmTptParam      *tPar;          /* transport parameters */
U8              srvcType;       /* service type */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   U8           type;
   U8           srvc;


   TRC3(HiUiHitConReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI027,(ErrVal)0,pst->dstInst,
            "HiUiHitConReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS   
#ifndef DEBUGP   
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T ConReq HC->HI, in HI");
#endif

 
   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConReq(pst, spId(%d), suConId(%ld), remAddr(%p), "
          "localAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, suConId, (Ptr)remAddr, (Ptr)localAddr, (Ptr)tPar, srvcType));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConReq(pst, spId(%d), suConId(%d), remAddr(%p), "
          "localAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, suConId, (Ptr)remAddr, (Ptr)localAddr, (Ptr)tPar, srvcType));
#endif


   /* get the predefined service type being requested */
   srvc = srvcType & 0x0F;


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_CONREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_CONREQ, alInfo);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate the service type requested */
   if (srvc != HI_SRVC_UDP
         &&  srvc != HI_SRVC_UDP_TPKT_HDR
#ifdef HI_TLS
         &&  srvc != HI_SRVC_TLS
#endif
         &&  srvc != HI_SRVC_TCP_TPKT_HDR
         &&  srvc != HI_SRVC_TCP_NO_HDR)
   {
      HILOGERROR_INT_PAR(EHI028, srvcType, 0,
         "HiUiHitConReq(): invalid service type");
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_CONREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   } 
#endif /* ERRCLS_INT_PAR */


   /* must have sufficient resources to establish a connection */

#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongStrt)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_OUTOF_RES);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */

   /* allocate and initialize a conCb for this client */
   ret = hiAllocConCb(sap, suConId, srvcType, &type, &conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_SMEM_ALLOC_ERR);
      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check remote address for TCP clients */
   if (type == CM_INET_STREAM  &&  !HI_CHK_ADDR(remAddr))
   {
      HILOGERROR_INT_PAR(EHI029, 0, 0,
         "HiUiHitConReq(): invalid remote address");
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_CONREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }

#ifdef HI_TLS
   /* for TLS, make sure there's a valid context */
   if (srvc == HI_SRVC_TLS
       &&  (!tPar  ||  tPar->type != CM_TPTPARAM_TLS
            ||  tPar->u.tlsParam.ctxId < 0
            ||  tPar->u.tlsParam.ctxId >= hiCb.cfg.numContexts
            ||  hiCb.tlsContexts[tPar->u.tlsParam.ctxId].cfg.ctxId
                  == HI_INVALID_OSSL_CTX))
   {
      HILOGERROR_INT_PAR(EHI030, 0, 0,
         "HiUiHitConReq(): invalid TLS context");
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_PARAM;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_CONREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }
#endif /* HI_TLS */
#endif /* ERRCLS_INT_PAR */


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T cmInet-calls strt, in HI");
#endif


   /* open a new socket */
   ret = hiCreateSock(FALSE, type, localAddr, tPar, conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, conCb->suConId, ret);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* Issue a connect for stream type connections or if a remote
    * address has been specified for datagram connections.
    */
   conCb->state = HI_ST_CONNECTED;
   if (HI_CHK_ADDR(remAddr))
   {
      ret = HI_CONNECT(&conCb->conFd, remAddr);
      if (ret == RFAILED  ||  ret == RCLOSED)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, conCb->suConId,
                    (ret == RFAILED
                     ? HI_SOCK_CONN_ERR
                     : HI_CON_CLOSED_BY_PEER));
         HI_CLOSE_SOCKET(&conCb->conFd);
         HI_FREECONCB(conCb);
         HI_INC_ERRSTS(hiCb.errSts.sockCnctErr);
         RETVALUE(RFAILED);
      }
      else if (ret == RINPROGRESS  ||  ret == ROKDNA
               ||  ret == RWOULDBLOCK)
         conCb->state = HI_ST_CLT_CONNECTING;

      /* this a proper UDP client? */
      if (conCb->flag & HI_FL_UDP)
         conCb->flag |= HI_FL_UDP_CLT;
   }


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T cmInet-calls end, in HI");
#endif


   /* store remote address */
   cmMemcpy((U8 *)&conCb->peerAddr, (U8 *)remAddr, sizeof (CmTptAddr));


   /* Complete the connection control block: get an spConId and
    * put it in the SAP's connections hash list.
    */
   ret = hiCompleteConCb(conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_CONID_NOT_AVAIL);
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONREQ,
                  LHI_CAUSE_CONID_NOT_AVAIL, &alInfo);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


#ifdef HI_TLS
   /* For TLS, set up the connection and issue a connect if the
    * underlying TCP connection completed. Otherwise, this TLS
    * connect is issued later, when the thread completes this
    * connection.
    */
   if (srvc == HI_SRVC_TLS)
   {
      conCb->tlsConCb.ctxId = tPar->u.tlsParam.ctxId;
      ret = hiPrepareTLSCon(conCb, FALSE);
      if (ret == ROK  &&  conCb->state == HI_ST_CONNECTED)
      {
         ret = hiConnectTLS(conCb);
         if (ret == ROKDNA)
            conCb->state = HI_ST_CLT_CONNECTING;
      }

      if (ret != ROK  &&  ret != ROKDNA)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_SOCK_CONN_ERR);
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONREQ,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         HI_CLOSE_SOCKET(&conCb->conFd);
         HI_FREECONCB(conCb);
         RETVALUE(RFAILED);
      }
   }
#endif /* HI_TLS */


   /* assign the connection to an fd group */
   ret = hiAssignConCb(conCb, HI_THR_ADDCON_CONCFM);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INTERNAL_ERR);
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONREQ,
                  LHI_CAUSE_INTPRIM_ERR, &alInfo);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* update number of connections stat */
   HI_INC_TXSTS(sap, sap->txSts.numCons);


   /* connect confirm is issued from the thread */


   RETVALUE(ROK);
} /* HiUiHitConReq() */


/*
*
*       Fun:    HiUiHitConRsp
*
*       Desc:   Accept the new client connection indicated by a
*               connection indication primitive. The specified
*               suConId is stored in the connection block and data
*               transfer can be initiated.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If the connection control block corresponding to
*               spConId is not found, TUCL returns silently. This
*               can happen if a disconnect indication has been
*               issued for the connection and the block has been
*               released.
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitConRsp
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider id */
UConnId         suConId,        /* service user's connection Id */
UConnId         spConId         /* service provider's connection Id */
)
#else
PUBLIC S16 HiUiHitConRsp(pst, spId, suConId, spConId)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider id */
UConnId         suConId;        /* service user's connection Id */
UConnId         spConId;        /* service provider's connection Id */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;


   TRC3(HiUiHitConRsp);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI031,(ErrVal)0,pst->dstInst,
            "HiUiHitConRsp() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T ConRsp HC->HI, in HI");
#endif


   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConRsp(pst, spId(%d), suConId(%ld), spConId(%ld))\n",
          spId, suConId, spConId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConRsp(pst, spId(%d), suConId(%d), spConId(%d))\n",
          spId, suConId, spConId));
#endif


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_CONRSP, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_CONRSP, alInfo);


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* find the connection block */
   ret = hiFindConCb(sap, spConId, &conCb);
   if (ret != ROK)
   {
      /* not found, issue a disconnect indication */
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_DEBUG)
   /* check the connection state */
   if (conCb->state != HI_ST_AW_CON_RSP)
   {
      alInfo.type = LHI_ALARMINFO_CON_STATE;
      alInfo.inf.conState = conCb->state;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONRSP,
                  LHI_CAUSE_INV_CON_STATE, &alInfo);
      conCb->state = HI_ST_DISCONNECTING;
      hiDoneWithConCb(conCb);
      tMsg.type = HI_THR_DELCON_DISCIND;
      tMsg.spId = sap->spId;
      tMsg.spConId = conCb->spConId;
      tMsg.disc.reason = HI_INV_CON_STATE;
      hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      RETVALUE(RFAILED);
   }
#endif


   /* Store the provided suConId, shift state, and tell the
    * group thread to start processing this connection.
    */
   conCb->suConId = suConId;
   conCb->state = HI_ST_CONNECTED;
   tMsg.type = HI_THR_RSPCON;
   tMsg.spId = sap->spId;
   tMsg.spConId = conCb->spConId;
   hiSendThrMsg(conCb->fdGrpNum, &tMsg);
   hiDoneWithConCb(conCb);


   /* data transfer is now possible on this connection */


   RETVALUE(ROK);
} /* HiUiHitConRsp() */


/*
*
*       Fun:    HiUiHitDatReq
*
*       Desc:   Transmit data on a stream connection. If the SAP
*               is under flow control, the primitive is dropped.
*               Otherwise, TUCL marks the message boundaries in
*               accordance with RFC 1006 if required for this
*               connection and sends the message. If the entire
*               message cannot be sent, the untransmitted portion
*               is queued. If the total untransmitted data exceeds
*               the threshold specified in the SAP configuration,
*               a flow control indication is issued and the data
*               is dropped.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If an invalid spConId is specified, the data is
*               dropped silently. In other error cases, a
*               disconnect indication is issued.
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDatReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
UConnId         spConId,        /* service provider's connection Id */
Buffer          *mBuf           /* message buffer */
)
#else
PUBLIC S16 HiUiHitDatReq(pst, spId, spConId, mBuf)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
UConnId         spConId;        /* service provider's connection Id */
Buffer          *mBuf;          /* message buffer */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   MsgLen       mLen, txLen;
   QLen         qLen;
   Buffer       *qBuf;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;


   TRC3(HiUiHitDatReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI032,(ErrVal)0,pst->dstInst,
            "HiUiHitDatReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP 
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T DatReq HC->HI, in HI");
#endif


   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDatReq(pst, spId(%d), spConId(%ld), mBuf(%p)))\n",
          spId, spConId, (Ptr)mBuf));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDatReq(pst, spId(%d), spConId(%d), mBuf(%p)))\n",
          spId, spConId, (Ptr)mBuf));
#endif


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_DATREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_DATREQ, alInfo);


   /* hi018.201: mLen is initialized to zero */
   mLen = 0;
   /* get length of data payload */
   ret = SFndLenMsg(mBuf, &mLen);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate message */
   if (ret != ROK  ||  mLen < 1)
   {
      HILOGERROR_INT_PAR(EHI033, spId, 0,
         "HiUiHitDatReq(): invalid buffer");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_MBUF;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }
#endif


   /* find the connection control block */
   ret = hiFindConCb(sap, spConId, &conCb);
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      HI_DISCIND(sap, HI_PROVIDER_CON_ID, spConId, HI_DATREQ_INVALID_CONID);
      RETVALUE(RFAILED);
   }


   /* must have sufficient resources to send this message */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongDrop  ||  conCb->flc)
   {
      /* Drop the message silently. In case of resource
       * congestion, an alarm would have already been issued. In
       * case of flow control, an indication would have already
       * been issued.
       */
      HI_FREE_BUF(mBuf);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
#else 
   if (conCb->flc)
   {
      /* Drop the message silently. In case of resource
       * congestion, an alarm would have already been issued. In
       * case of flow control, an indication would have already
       * been issued.
       */
      HI_FREE_BUF(mBuf);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */


   /* check connection state */
   if (conCb->state != HI_ST_CONNECTED
       &&  conCb->state != HI_ST_CONNECTED_NORD)
   {
      HI_FREE_BUF(mBuf);
      alInfo.type = LHI_ALARMINFO_CON_STATE;
      alInfo.inf.conState = conCb->state;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LHI_CAUSE_INV_CON_STATE, &alInfo);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* cannot be a UDP connection */
   if (conCb->flag & HI_FL_UDP)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_INT_PAR(EHI034, spId, 0,
         "HiUiHitDatReq(): invalid connection type for data request");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_SRVC_TYPE;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
#endif


   /* add in a TPKT header if required for this connection */
   if ((conCb->srvcType & 0x0F) == HI_SRVC_TCP_TPKT_HDR)
   {
      ret = hiAddTPKTHdr(mBuf, &mLen);

#if (ERRCLASS & ERRCLS_ADD_RES)
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_ADD_RES(EHI035, spId, 0,
            "HiUiHitDatReq(): could not add TPKT header");
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
#endif
   }

   /* hi018.201 : qLen is initialized to zero */
   qLen = 0;
   /* If there is nothing in the transmit queue, send the message.
    * This could succeed partially, in which case we have to queue
    * the untransmitted portion. If there is something in the
    * transmit queue, we just queue the whole message.
    */
   HI_GET_TXQLEN(conCb, &qLen);
   if (qLen == 0)
      ret = hiTxMsg(conCb, mBuf, &txLen, &qBuf, &tMsg);
   else
   {
      ret = RWOULDBLOCK;
      qBuf = mBuf;
      txLen = 0;
   }


   /* Here, we have to enqueue the untransmitted part of the
    * message in qBuf (could be the whole message).
    */
   if (ret == RWOULDBLOCK)
   {
      ret = hiEnqueueForTx(conCb, qBuf);
      if (ret == ROK)
         /* hi006.105 : corrected the flow control check */ 
         hiChkFlc(conCb, 0, 0);
      else
      {
         HI_FREE_BUF(qBuf);
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = sap->uiPst.region;
         alInfo.inf.mem.pool = sap->uiPst.pool;
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         tMsg.type = HI_THR_DELCON_DISCIND;
         tMsg.spId = sap->spId;
         tMsg.spConId = conCb->spConId;
         tMsg.disc.reason = HI_OUTOF_RES;
      }
   }


   /* We have a failure here. The terminate message should have
    * been prepared, so we just send it to the group's thread.
    */
   if (ret != ROK  &&  ret != RWOULDBLOCK)
   {
      conCb->state = HI_ST_DISCONNECTING;
      hiSendThrMsg(conCb->fdGrpNum, &tMsg);
   }


   /* finished with the connection */
   hiDoneWithConCb(conCb);


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T DatReq - End of HiUiHitDatReq, in HI");
#endif


   RETVALUE(ROK);
} /* HiUiHitDatReq() */


/*
*
*       Fun:    HiUiHitUDatReq
*
*       Desc:   Transmit data on a datagram connection.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If an error occurs, no indication is given to the
*               service user, but an alarm is issued to the layer
*               manager.
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitUDatReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
UConnId         spConId,        /* HI connection Id */
CmTptAddr       *remAddr,       /* remote address */
CmTptAddr       *srcAddr,       /* source address */
CmIpHdrParm     *hdrParm,       /* header parameters */
CmTptParam      *tPar,          /* transport parameters */
Buffer          *mBuf           /* message buffer to be sent */
)
#else
PUBLIC S16 HiUiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, 
                          hdrParm, tPar, mBuf)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
UConnId         spConId;        /* HI connection Id */
CmTptAddr       *remAddr;       /* remote address */
CmTptAddr       *srcAddr;       /* source address */
CmIpHdrParm     *hdrParm;       /* header parameters */
CmTptParam      *tPar;          /* transport parameters */
Buffer          *mBuf;          /* message buffer to be sent */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiAlarmInfo  alInfo;
   MsgLen       mLen, txLen;
   CmInetFd     *sendFd;
   CmTptParam   lclTPar;
   HiConCb      *conCb, con;
   Bool         udpClt, resetTtl;
   HiThrMsg     tMsg;


   TRC3(HiUiHitUDatReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI036,(ErrVal)0,pst->dstInst,
            "HiUiHitUDatReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP   
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T UDatReq HC->HI, in HI");
#endif


   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitUDatReq(pst, spId(%d), remAddr(%p), mBuf(%p))\n",
          spId, (Ptr)remAddr, (Ptr)mBuf));


   /* initialize locals */
   alInfo.spId  = spId;
   alInfo.type  = LHI_ALARMINFO_TYPE_NTPRSNT;

   conCb        = NULLP;
   udpClt       = FALSE;
   resetTtl     = FALSE;

   
   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_UDATREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_UDATREQ, alInfo);

   /* hi018.201 : mLen is initialized to zero */
   mLen = 0;
   /* get length of data payload */
   ret = SFndLenMsg(mBuf, &mLen);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate message */
   if (ret != ROK  ||  mLen < 1)
   {
      HILOGERROR_INT_PAR(EHI037, spId, 0,
         "HiUiHitDatReq(): invalid Buffer");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_MBUF;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* verify the source address */
   if (!HI_CHK_ADDR(srcAddr)  &&  srcAddr->type != CM_TPTADDR_NOTPRSNT)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_INT_PAR(EHI038, 0, 0,
         "HiUiHitUDatReq(): invalid source address");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* check header parameters */
   if (!HI_CHK_HDRPARM(hdrParm)
       &&  hdrParm->type != CM_HDRPARM_NOTPRSNT)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_INT_PAR(EHI039, 0, 0,
         "HiUiHitUDatReq(): invalid protocol type in header parameters");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* check IPv4 options */
   if (hdrParm->type == CM_HDRPARM_IPV4)
   {
#ifdef IPV4_OPTS_SUPPORTED
      if (hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres
          &&  hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len > CM_IPV4_OPTS_MAXLEN)
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_INT_PAR(EHI040, hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len, 0,
            "HiUiHitUDatReq(): invalid IPv4 options length");
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_HDR_PARAM;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         RETVALUE(RFAILED);
      }
#endif
   }
#endif /* ERRCLS_INT_PAR */


   /* must have sufficient resources to send this message */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongDrop)
   {
      /* Drop the message silently. An alarm has already been
       * issued for resource congestion.
       */
      HI_FREE_BUF(mBuf);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */


   /* If spConId is zero, we use the generic socket to send this
    * message.
    */
   sendFd = NULLP;

   if (spConId == 0)
/* hi002.105 (hi030.104) - If Generic Socket Supported */
#ifndef HI_DISABLE_GENSOCKET
   {
#ifdef IPV6_SUPPORTED
      if (remAddr->type == CM_INET_IPV6ADDR_TYPE)
         sendFd = &hiCb.resv6ConFd;

      else /* assignment below */
#endif

      sendFd = &hiCb.resvConFd;

      /* Copy the fd into a temporary connection block for calling
       * hiSetSockOpt().
       */
      cmMemcpy((U8 *)&con.conFd, (U8 *)sendFd, sizeof (CmInetFd));
   }
#else
   {
      if(mBuf)
         HI_FREE_BUF(mBuf);
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
               LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }
#endif /*HI_DISABLE_GENSOCKET */

   /* spConId has been specified. Find the correct connection to
    * use for this transmission.
    */
   else
   {
      ret = hiFindConCb(sap, spConId, &conCb);
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         RETVALUE(RFAILED);
      }


      /* check connection state */
      if (conCb->state != HI_ST_CONNECTED
          &&  conCb->state != HI_ST_CONNECTED_NORD)
      {
         HI_FREE_BUF(mBuf);
         alInfo.type = LHI_ALARMINFO_CON_STATE;
         alInfo.inf.conState = conCb->state;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LHI_CAUSE_INV_CON_STATE, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }


      /* get the fd to use */
      sendFd = &conCb->conFd;


      /* is this a true UDP client? */
      if (conCb->flag & HI_FL_UDP_CLT)
         udpClt = TRUE;


#if (ERRCLASS & ERRCLS_INT_PAR)
      /* validate header parameter type against connection type */
#ifdef IPV6_SUPPORTED
      if ((hdrParm->type == CM_HDRPARM_IPV4
           ||  hdrParm->type == CM_HDRPARM_IPV6)
          &&  conCb->flag & HI_FL_TCP)
#else
      if (hdrParm->type == CM_HDRPARM_IPV4
          &&  !(conCb->flag & HI_FL_RAW))
#endif
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_INT_PAR(EHI041, (ErrVal)hdrParm->type, 0,
            "HiUiHitUDatReq(): invalid header parameter/protocol combination");
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_TPT_ADDR;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
#endif /* ERRCLS_INT_PAR */


      /* add in a TPKT header if required for this connection */
      if ((conCb->srvcType & 0x0F) == HI_SRVC_UDP_TPKT_HDR)
      {
         ret = hiAddTPKTHdr(mBuf, &mLen);

#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ret != ROK)
         {
            HI_FREE_BUF(mBuf);
            HILOGERROR_ADD_RES(EHI042, spId, 0,
               "HiUiHitUDatReq(): could not add TPKT header");
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LCM_CAUSE_UNKNOWN, &alInfo);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }
#endif
      }

      /* now, process the header parameters */
      ret = hiProcHdrParm(conCb, srcAddr, remAddr, hdrParm, mBuf, mLen);
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_ADD_RES(EHI043, spId, 0,
            "HiUiHitUDatReq(): could not process header parameters");
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_UDATREQ,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
   }


   /* Handle multicast TTL or hop count */
   if (tPar->type == CM_TPTPARAM_SOCK
       &&  tPar->u.sockParam.numOpts > 0
       &&  HI_CHK_MCASTOPT(tPar->u.sockParam.sockOpts[0].option))
   {
      if (conCb)
      {
         if (conCb->mCastTtl != tPar->u.sockParam.sockOpts[0].optVal.value)
         {
            ret = hiSetSockOpt(conCb, tPar);
            if (ret == RNA  ||  ret == RFAILED)
            {
               HI_FREE_BUF(mBuf);
               hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_UDATREQ,
                           LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
               hiDoneWithConCb(conCb);
               RETVALUE(RFAILED);
            }

            conCb->mCastTtl = tPar->u.sockParam.sockOpts[0].optVal.value;
         }
      }
      else
      {
         resetTtl = TRUE;
         lclTPar.u.sockParam.numOpts = 1;
         lclTPar.u.sockParam.sockOpts[0].option
            = tPar->u.sockParam.sockOpts[0].option;
         lclTPar.u.sockParam.sockOpts[0].level
            = tPar->u.sockParam.sockOpts[0].level;
         lclTPar.u.sockParam.sockOpts[0].optVal.value = 1;

         ret = hiSetSockOpt(&con, tPar);
         if (ret == RNA  ||  ret == RFAILED)
         {
            HI_FREE_BUF(mBuf);
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_UDATREQ,
                        LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
            /* Klock work fix ccpu00147991 */
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }
      }
   }


#ifdef IPV6_OPTS_SUPPORTED                                
   /* Copy the source address to hdrParm so that it is available
    * in cmInetSendMsg() to set on the outgoing packet.
    */
   if (srcAddr->type == CM_TPTADDR_IPV6)
   {
      hdrParm->u.hdrParmIpv6.srcAddr6.type = srcAddr->type;
      cmMemcpy((U8 *)&hdrParm->u.hdrParmIpv6.srcAddr6.u.ipv6NetAddr,
               (U8 *)&srcAddr->u.ipv6TptAddr.ipv6NetAddr, 16);
   }
#endif


#ifdef H323_PERF
   TAKE_TIMESTAMP("Before UDatReq/cmInetSendMsg(), in HI");
#endif


   /* Send the message. If the UDP socket is already connected
    * then do not pass a remote address.
    */
   HI_SENDMSG(sendFd, (udpClt ? NULLP : remAddr), mBuf,
              &txLen, (udpClt ? NULLP : hdrParm), ret);


#ifdef IPV6_OPTS_SUPPORTED
   /* free IPv6 header parameters */
   /* hi001.105 - Fixed compiler warning */
   if (hdrParm->type == CM_HDRPARM_IPV6)
      CM_INET_FREE_IPV6_HDRPARM(hiCb.init.region, hiCb.init.pool,
         ((CmInetIpv6HdrParm*)&(hdrParm->u.hdrParmIpv6)));
#endif


#ifdef H323_PERF
   TAKE_TIMESTAMP("After UDatReq/cmInetSendMsg(), in HI");
#endif


   /* check for send errors */
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);

      tMsg.type = HI_THR_DELCON_DISCIND;
      tMsg.spId = sap->spId;

      /* hi011.201 handling NETWORK failure sending error */
      /* no disconnect for ROUTRES , RWOULDBLOCK and RNETFAILED */
      if (ret == ROUTRES  ||  ret == RWOULDBLOCK || ret == RNETFAILED)
      {
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = hiCb.init.region;
         alInfo.inf.mem.pool = hiCb.init.pool;
			/* hi005.201  Free the lock in case of error */
         hiDoneWithConCb(conCb);
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         RETVALUE(RFAILED);
      }

      /* hi005.201 Don't close the non connected UDP in case of Sending error.
		             Insted give alarm Indication to Layer manager and return 
		 *           RFAILED.
		 */
      else if (!udpClt)
		{
          HI_INC_ERRSTS(hiCb.errSts.sockTxErr);
          hiDoneWithConCb(conCb);
			 hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
			             LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
			 RETVALUE(RFAILED);
      }

      /* We get RCLOSED when an ICMP message is received on a UDP
       * socket. This will only happen with a connected socket,
       * where spConId is valid. We disconnect it.
       */
      else if (ret == RCLOSED)
         tMsg.disc.reason = HI_CON_CLOSED_BY_PEER;

      /* all other errors get an alarm and are disconnected */
      else
      {
         HI_INC_ERRSTS(hiCb.errSts.sockTxErr);
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         tMsg.disc.reason = HI_SOCK_SEND_ERR;
      }

      /* send the delete connection message to the group thread */
      if (conCb)
      {
		   /* hi005.201 */
         tMsg.spConId = conCb->spConId;
         conCb->state = HI_ST_DISCONNECTING;
         hiDoneWithConCb(conCb);
         hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      }


      RETVALUE(RFAILED);
   }


   /* reset IP multicast TTL if necessary */
   if (resetTtl)
      hiSetSockOpt(&con, &lclTPar);


   /* update statistics and we're done with the connection */
   HI_ADD_TXSTS(sap, sap->txSts.numTxBytes, txLen);
   if (conCb)
   {
      HI_INC_TXSTSMSG(sap, conCb);
      hiDoneWithConCb(conCb);
   }


   /* trace the message if needed and release it; we're done! */
   if (sap->trc)
      hiTrcBuf(sap, LHI_UDP_TXED, mBuf);
   HI_FREE_BUF(mBuf);


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T DatReq - End of HiUiHitUDatReq, in HC");
#endif


   RETVALUE(ROK);
} /* HiUiHitUDatReq() */


/*
*
*       Fun:    HiUiHitDiscReq
*
*       Desc:   Shut down or close the socket identified by conId.
*               TUCL responds with a disconnect confirm on
*               success. This primitive is also used to leave
*               membership of a multicast group for UDP sockets.
*               The action parameter specifies whether the socket
*               should be closed, shut down, or if this is a
*               request to leave a multicast group.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  The connection block is released only if the
*               action parameter indicates that the socket should
*               be closed. If the connection block cannot be
*               found, TUCL returns silently (a disconnect
*               indication may have already been sent).
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDiscReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
U8              choice,         /* choice of user or provider Id */
UConnId         conId,          /* connection Id */
Action          action,         /* action to be performed */
CmTptParam      *tPar           /* transport parameters */
)
#else
PUBLIC S16 HiUiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
U8              choice;         /* choice of user or provider Id */
UConnId         conId;          /* connection Id */
Action          action;         /* action to be performed */
CmTptParam      *tPar;          /* transport parameters */
#endif
{
   S16          ret;
   HiSap        *sap;
   /* KW fixes for acc compilation  */
   HiConCb      *conCb = NULLP;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;


   TRC3(HiUiHitDiscReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt, EHI044,(ErrVal)0,pst->dstInst,
            "HiUiHitDiscReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifdef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscReq(pst, spId(%d), choice(%d), conId(%ld), \
          action(%d))\n", spId, choice, conId, action));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscReq(pst, spId(%d), choice(%d), conId(%d), \
          action(%d))\n", spId, choice, conId, action));
#endif


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_DISCREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_DISCREQ, alInfo);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (action == HI_LEAVE_MCAST_GROUP)
   {
      if (tPar->type != CM_TPTPARAM_SOCK
          ||  !HI_CHK_MCASTDRPOPT(tPar->u.sockParam.sockOpts[0].option))
      {
         HILOGERROR_INT_PAR(EHI045, 0, 0,
            "HiUiHitDiscReq(): invalid transport parameters");
         HI_DISCCFM(sap, choice, conId, action);
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_TPT_PARAM;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DISCREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         RETVALUE(RFAILED);
      }
   }
#endif


   /* find the connection */
   if (choice == HI_PROVIDER_CON_ID)
      ret = hiFindConCb(sap, conId, &conCb);
   else
      ret = hiFindConCbSuConId(sap, conId, &conCb);

   /* KW fixes for acc compilation  */
   if ((ret != ROK)||(conCb == NULLP))
   {
      HI_DISCCFM(sap, choice, conId, action);
      RETVALUE(ROK);
   }


   /* check connection state */
   if (NULLP == conCb)
   {
      HILOGERROR_INT_PAR(EHI045, 0, 0,
         "HiUiHitDiscReq(): conCb is NULL");
      RETVALUE(RFAILED);
   }
   if (conCb->state == HI_ST_DISCONNECTING)
   {
      HI_DISCCFM(sap, choice, conId, action);

      /** hi016.105  1. Given a check for NULLP before
       *                accessing conCb to avoid FMR/W  
       */
		/* hi005.201  1. If conCb is not NULL then 
		 *               free the conCb lock */
      if(conCb)
         hiDoneWithConCb(conCb);

      RETVALUE(ROK);
   }


#ifdef HI_TLS
   /* For TLS connections, we shut down the TLS part before
    * closing the socket.
    */
   if ((conCb->srvcType & 0x0F) == HI_SRVC_TLS)
   {

#if (ERRCLASS & ERRCLS_INT_PAR)
      /* the only legal action for TLS connections is close */
      if (action != HI_CLOSE)
      {
         HILOGERROR_INT_PAR(EHI046, (ErrVal)spId, 0,
            "HiUiHitDiscReq(): invalid action");

         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_ACTION;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DISCREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
#endif

      hiDisconnectTLS(conCb);
   }
#endif /* HI_TLS */


   /* We deal with multicast group leaves here; other actions are
    * handled by the group thread.
    */
   if (action == HI_LEAVE_MCAST_GROUP)
   {
      ret = hiSetSockOpt(conCb, tPar);
      if (ret != ROK)
      {
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_DISCREQ,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }

      /* issue disconnect confirm */
      HI_DISCCFM(sap, choice, conId, action);

      /* done with the connection */
      hiDoneWithConCb(conCb);

      RETVALUE(ROK);
   }


   /* set the connection to disconnecting state */
   conCb->state = HI_ST_DISCONNECTING;

   /* prepare and send a message to the group thread */
   tMsg.type        = HI_THR_DELCON_DISCCFM;
   tMsg.spId        = sap->spId;
   tMsg.spConId     = conCb->spConId;
   tMsg.disc.action = action;
   hiSendThrMsg(conCb->fdGrpNum, &tMsg);


   /* done with the connection */
   hiDoneWithConCb(conCb);


   RETVALUE(ROK);
} /* HiUiHitDiscReq() */

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/*
*
*       Fun:    HiUiHitTlsEstReq
*
*       Desc:   Establish TLS channel on top of the existing
*               TCP connection. Service user has to provide 
*               the connection ID on which it nees to start
*               TLS negotiation. A context should be created in 
*               advance and its Id should be given though this primitive
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
* 
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitTlsEstReq 
(
Pst             *pst,           /* post stucture */
SpId            spId,           /* service provider SAP Id */
UConnId         spConId,        /* service provider connection Id */
S16             ctxId,          /* Valid Context Id */
U8              nodeType        /* server or client */
)
#else
PUBLIC S16 HiUiHitTlsEstReq(pst, spId, spConId, ctxId, nodeType)
Pst             *pst;           /* post stucture */
SpId            spId;           /* service provider SAP Id */
UConnId         spConId;        /* service provider connection Id */
S16             ctxId;          /* Valid Context Id */
U8              nodeType;       /* server or client */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;

   TRC3(HiUiHitTlsEstReq);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI047,(ErrVal)0,pst->dstInst,
            "HiUiHitTlsEstReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitTlsEstReq(pst, spId(%d), spConId(%ld),"
          "contexId(%d), nodeType(%d))\n",
          spId, spConId,ctxId, nodeType));
   
   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_TLS_ESTREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_TLS_ESTREQ, alInfo);

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;

#ifdef ERRCLS_INT_PAR
   /* for TLS, a valid context Id must be provided */
   if (ctxId < 0 ||  ctxId >= hiCb.cfg.numContexts
       ||  hiCb.tlsContexts[ctxId].cfg.ctxId == HI_INVALID_OSSL_CTX)
   {
      HILOGERROR_INT_PAR(EHI048, 0, 0,
         "HiUiHitTlsEstReq(): invalid TLS context id");

      HI_DISCIND(sap, HI_PROVIDER_CON_ID, spConId, HI_INV_PAR_VAL);

      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_PARAM;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_TLS_ESTREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   if ((nodeType != HI_TLS_SERVER) && (nodeType != HI_TLS_CLIENT))
   {
      HILOGERROR_INT_PAR(EHI049, 0, 0,
         "HiUiHitTlsEstReq(): invalid node type");
      HI_DISCIND(sap, HI_PROVIDER_CON_ID, spConId, HI_INV_PAR_VAL);

      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_PARAM;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_TLS_ESTREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
            
      RETVALUE(RFAILED);
   }


#endif /* ERRCLS_INT_PAR */

   /* find the connection control block */
   ret = hiFindConCb(sap, spConId, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
       "HiUiHitTlsEstReq(): unable to find Connection control block for the given spConnId\n"));

      HI_DISCIND(sap, HI_PROVIDER_CON_ID, spConId, HI_INV_PAR_VAL);

      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_PARAM;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_TLS_ESTREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
            
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   /* check connection state */
   if (conCb->state != HI_ST_CONNECTED)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiHitTlsEstReq(): The given connection, spConId is not in connected state\n"));

      alInfo.type = LHI_ALARMINFO_CON_STATE;
      alInfo.inf.conState = conCb->state;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_TLS_ESTREQ,
                  LHI_CAUSE_INV_CON_STATE, &alInfo);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
   
   /* Change the TUCL operational mode to TCP_TLS */
   conCb->mode = HI_MODE_TCP_TLS;
  
   /* Change the service type to HI_SRVC_TLS for this connection */
   conCb->srvcType = HI_SRVC_TLS;

   if(nodeType == HI_TLS_SERVER)
   {
      /* Change the state to TCP-TLS mode */
      conCb->state = HI_ST_SRV_LISTEN;

      conCb->tlsConCb.ctxId = ctxId;

      /* If this is TLS, since the underlying TCP connection has
       * been established we can prepare the TLS part.
       */
      ret = hiPrepareTLSCon(conCb, TRUE);
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiHitTlsEstReq(): unable to prepare TLS (Create BIO and SSL object) \
            on the connection given as spConnId\n"));
         HI_TLSEST_CFM(conCb, HI_TCP_TLS_NOK, HI_TCP_TLS_REASON_UNABLE_PREPARE_TLS);

         /* issue an alarm */
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                       LCM_CAUSE_UNKNOWN, &alInfo);
      }

      hiDoneWithConCb(conCb);
   }/*if(nodeType == HI_TLS_SERVER) */
   else /*if(nodeType == HI_TLS_CLIENT)*/
   {
      conCb->tlsConCb.ctxId = ctxId;
      
      /* If this is TLS, since the underlying TCP connection has
       * been established we can prepare the TLS part.
       */
      ret = hiPrepareTLSCon(conCb, FALSE);
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiHitTlsEstReq(): unable to prepare TLS (Create BIO and SSL object) \
            on the connection given as spConnId\n"));
         HI_TLSEST_CFM(conCb, HI_TCP_TLS_NOK, HI_TCP_TLS_REASON_UNABLE_PREPARE_TLS);
         /* issue an alarm */
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                       LCM_CAUSE_UNKNOWN, &alInfo);
         RETVALUE(RFAILED);
      }

      if (ret == ROK  &&  conCb->state == HI_ST_CONNECTED)
      {
         ret = hiConnectTLS(conCb);
         if (ret == ROKDNA)
         {
            conCb->state = HI_ST_CLT_CONNECTING;

         }else if (ret == ROK) 
         {
            HI_TLSEST_CFM(conCb, (U8)HI_TCP_TLS_OK, (Reason)HI_TCP_TLS_REASON_NOT_APPL);
            hiDoneWithConCb(conCb);
            RETVALUE(ROK);
         }
      }

      if (ret != ROK  &&  ret != ROKDNA)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiHitTlsEstReq(): unable to make TLS connect\n"));
         HI_TLSEST_CFM(conCb, HI_TCP_TLS_NOK, HI_TCP_TLS_REASON_TLS_CONNECT_ERR);
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONREQ,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         RETVALUE(RFAILED);
      }

      /* prepare and send a message to the group thread */
      tMsg.type = HI_THR_ADDCON;
      tMsg.spId = conCb->sap->spId;
      tMsg.spConId = conCb->spConId;
      ret = hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      hiDoneWithConCb(conCb);
      if (ret != ROK)
      {
         /* we're left in an unstable state! */
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiHitTlsEstReq(): send message to group thread failed\n"));
         RETVALUE(RFAILED);
      }

      hiDoneWithConCb(conCb);

   }/* elseif(nodeType == HI_TLS_CLIENT)*/

   RETVALUE(ROK);

}/* endof HiUiHitTlsEstReq */

#endif /*HI_TCP_TLS*/
#endif /*HI_TLS*/
#endif /*HITV2*/

#ifdef HI_LKSCTP


/****************************************************************************/
/* SCT upper interface primitives                                           */
/****************************************************************************/

/*
*
*       Fun:   HiUiSctBndReq
*
*       Desc:  Bind Request Primitive
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function binds a User to the SCTP Layer.
*              The SCTP Layer allocates a service access point for this
*              bind and records the identity of the service user. If the
*              SAP is already bound then it is first unbound and then rebound.
*              It also issues a HiUiSctBndCfm to the service user
*              after completing a successful bind.
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctBndReq
(
Pst        *pst,              /* Post structure */
SuId        suId,             /* service user id */
SpId        spId              /* service provider id */
)
#else
PUBLIC S16 HiUiSctBndReq(pst, suId, spId)
Pst        *pst;              /* Post Structure */
SuId        suId;             /* service user id */
SpId        spId;             /* service provider id */
#endif
{
   HiSap        *sap;
   HiAlarmInfo  alInfo;
#ifdef HI_RUG
   U16          i;
   Bool         found;
#endif


   TRC3(HiUiSctBndReq);

   if (pst == NULLP)
      RETVALUE(RFAILED);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI050,(ErrVal)0,pst->dstInst,
            "HiUiSctBndReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   


   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctBndReq(pst, suId(%d), spId(%d))\n",
          suId, spId));
 

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_BNDREQ, alInfo, sap);


   /* If the SAP is already bound, nothing happens here and a bind
    * confirm is issued.
    */
   if (sap->state == HI_ST_BND)
   {
      HiUiSctBndCfm(&sap->uiPst, suId, CM_BND_OK);
      RETVALUE(ROK);
   }

   if(sap->type != HI_SCT_SAP)

   {
      HILOGERROR_INT_PAR(EHI051, spId, pst->dstInst,
            "HiUiSctBndReq(): Incorrect SAP type");

      /* generate alarm to layer manager */
      alInfo.spId = spId;
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_BNDREQ,
            LCM_CAUSE_INV_SAP, &alInfo);

      /* send NOK to service user layer */
      HiUiSctBndCfm(&sap->uiPst, suId, CM_BND_NOK);

      RETVALUE(ROK);
   } 

   /* copy bind configuration parameters */
   sap->suId            = suId;
   sap->uiPst.dstProcId = pst->srcProcId;
   sap->uiPst.dstEnt    = pst->srcEnt;
   sap->uiPst.dstInst   = pst->srcInst;
   sap->uiPst.srcProcId = pst->dstProcId;
   sap->uiPst.srcInst   = pst->dstInst;

   /* duplicate Psts for multi-threaded case */
   HI_DUPLICATE_SAP_PST(sap, sap->uiPst);


#ifdef HI_RUG
   /* find interface version from stored info */
   if (!sap->remIntfValid)
   {
      found = FALSE;
      for (i = 0; i < hiCb.numIntfInfo && !found; i++)
      {
         /* hi028.201: Changed the interface version */
         if (hiCb.intfInfo[i].intf.intfId == SCTIF)
         {
            switch (hiCb.intfInfo[i].grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((hiCb.intfInfo[i].dstProcId == pst->srcProcId) &&
                      (hiCb.intfInfo[i].dstEnt.ent == pst->srcEnt) &&
                      (hiCb.intfInfo[i].dstEnt.inst == pst->srcInst))
                     found = TRUE;
                     break;

               case SHT_GRPTYPE_ENT:
                  if ((hiCb.intfInfo[i].dstEnt.ent ==pst->srcEnt) &&
                      (hiCb.intfInfo[i].dstEnt.inst == pst->srcInst))
                     found = TRUE;
                     break;

               default:
                  break;
            }
         }
      }

      if (!found)
      {
         HILOGERROR_INT_PAR(EHI052, spId, pst->dstInst,
              "HiUiSctBndReq(): remIntfver not available");

         /* generate alarm to layer manager */
         alInfo.spId = spId;
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_BNDREQ,
                     LCM_CAUSE_SWVER_NAVAIL, &alInfo);

         /* send NOK to service user layer */
         HiUiSctBndCfm(&sap->uiPst, suId, CM_BND_NOK);

         RETVALUE(ROK);
      } 

      sap->uiPst.intfVer = hiCb.intfInfo[i-1].intf.intfVer;
      sap->remIntfValid  = TRUE;          
   }
#endif /* HI_RUG */


   /* SAP state is now bound and enabled */
   sap->state = HI_ST_BND;

   /* issue a bind confirm */
   HiUiSctBndCfm(&sap->uiPst, suId, CM_BND_OK);

   RETVALUE(ROK);
}/* end of HiUiSctBndReq() */

/*
*
*       Fun:   HiUiSctEndpOpenReq
*
*       Desc:  Primitive to Open an Endpoint Server.
*
*       Ret:   ROK
*              ROKDUP
*              RFAILED
*
*       Notes: This function opens an endpoint on the SCTP Layer. An unused
*              spEndpId is found and the necessary structures are created
*              and initialised.
*
*       File:  hi_bdy1.c
*
*/

#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PUBLIC S16 HiUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
SctNetAddrLst *intfNAddrLst      /* Interface IP address list */
)
#else
PUBLIC S16 HiUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddrLst)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
SctNetAddrLst *intfNAddrLst;     /* Interface IP address list */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PUBLIC S16 HiUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
CmNetAddr     *intfNAddr         /* Interface IP address */
)
#else
PUBLIC S16 HiUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
CmNetAddr     *intfNAddr;        /* Interface IP address */
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   /* local parameters */
   HiSap        *sap;
   HiAlarmInfo   alInfo;
   S16           ret;
   U8            type;
   HiConCb      *conCb;
   S16           backLog = 1;
#ifndef SCT_ENDP_MULTI_IPADDR
   SctNetAddrLst addrLst;
#endif

   TRC3(HiUiSctEndpOpenReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI053,(ErrVal)0,pst->dstInst,
            "HiUiSctEndpOpenReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

#ifdef SCT_ENDP_MULTI_IPADDR
   if(intfNAddrLst == NULLP)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: Null interface address list\n"));
      RETVALUE(RFAILED);
   }

   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "HiUiSctEndpOpenReq(pst, spId(%d), suEndpId(%ld), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddrLst->nAddr[0].type));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "HiUiSctEndpOpenReq(pst, spId(%d), suEndpId(%d), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddrLst->nAddr[0].type));
#endif

#else /* SCT_ENDP_MULTI_IPADDR */

   if(intfNAddr == NULLP)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: Null interface address\n"));
      RETVALUE(RFAILED);
   }

   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "HiUiSctEndpOpenReq(pst, spId(%d), suEndpId(%ld), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddr->type));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "HiUiSctEndpOpenReq(pst, spId(%d), suEndpId(%d), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddr->type));
#endif

   addrLst.nmb      = 1;
   addrLst.nAddr[0] = *intfNAddr;
#endif /* SCT_ENDP_MULTI_IPADDR */

   UNUSED(pst);

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_ENDPOPENREQ, alInfo, sap);

   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_ENDPOPENREQ, alInfo);

   /* must have sufficient resources to establish a connection */

#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongStrt)
   {
      HiUiSctEndpOpenCfm( &(sap->uiPst), sap->suId, suEndpId,
            0, SCT_NOK, SCT_CAUSE_OUTRES);
      RETVALUE(ROK);
   }
#endif /* HI_NO_CHK_RES */

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* allocate and initialize a conCb for this server */
   ret = hiAllocConCb(sap, suEndpId, HI_SRVC_LKSCTP, &type, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: Failed to allocate connection control block\n"));
      HiUiSctEndpOpenCfm( &(sap->uiPst), sap->suId, suEndpId,
            0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }

#ifdef SCT_ENDP_MULTI_IPADDR
   ret = hiCreateSctpSock(conCb, intfNAddrLst, port);
#else
   ret = hiCreateSctpSock(conCb, &addrLst, port);
#endif
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: Failed to create SCTP socket\n"));
      HiUiSctEndpOpenCfm( &(sap->uiPst), sap->suId, suEndpId,
            0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }

   ret = HI_LISTEN(&conCb->conFd, backLog);

   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: Failed to listen on SCTP socket\n"));
      HiUiSctEndpOpenCfm( &(sap->uiPst), sap->suId, suEndpId,
            0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      HI_INC_ERRSTS(hiCb.errSts.sockLstnErr);
      RETVALUE(RFAILED);
   }

   /* set connection state */
   conCb->state =  HI_ST_SRV_LISTEN;
   /* set connection type */
   conCb->type  =  HI_SCTP_ENDP;


   /* Complete the connection control block: get an spConId and
    * put it in the SAP's connections hash list.
    */
   ret = hiCompleteConCb(conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctEndpOpenReq: failed to complete connection control block\n"));
      HiUiSctEndpOpenCfm( &(sap->uiPst), sap->suId, suEndpId,
            0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* assign the connection to an fd group */
   ret = hiAssignConCb(conCb, HI_THR_ADDCON_CONCFM);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: failed to assign connection to fd group\n"));
      HiUiSctEndpOpenCfm( &(sap->uiPst), sap->suId, suEndpId,
            0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* update number of connections stat */
   HI_INC_TXSTS(sap, sap->txSts.numCons);

   HiUiSctEndpOpenCfm(&(sap->uiPst), sap->suId, suEndpId,
            conCb->spConId, SCT_OK, SCT_CAUSE_NOT_APPL);

   /* connect confirm is issued from the thread */

   RETVALUE(ROK);
}/* HiUiSctEndpOpenReq() */

/*
*
*       Fun:   HiUiSctEndpCloseReq
*
*       Desc:  Primitive to Close an Endpoint Server.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function closes an endpoint on the SCTP Layer.
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctEndpCloseReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        endpId,           /* endpoint ID */
U8             endpIdType        /* service user/provider */
)
#else
PUBLIC S16 HiUiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        endpId;           /* endpoint ID */
U8             endpIdType;       /* service user/provider */
#endif
{
   HiSap        *sap;
   HiAlarmInfo   alInfo;
   S16           ret;
   HiConCb      *endpConCb;
   HiConCb      *assocConCb;
   Bool          found;
   UConnId       i;
   HiThrMsg      tMsg;


   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctEndpCloseReq(pst, spId(%d), endpId(%ld), endpIdType(%d))\n",
          spId, endpId, endpIdType));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctEndpCloseReq(pst, spId(%d), endpId(%d), endpIdType(%d))\n",
          spId, endpId, endpIdType));
#endif

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_ENDPCLOSEREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_ENDPCLOSEREQ, alInfo);

   if (endpIdType != SCT_ENDPID_SP && endpIdType != SCT_ENDPID_SU)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctEndpCloseReq: Invalid end point id type\n"));
      RETVALUE(RFAILED);
   }


   if(endpIdType == SCT_ENDPID_SP)
   {
      ret = hiFindConCb(sap, endpId, &endpConCb);
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctEndpCloseReq: Failed to find the connection control block\n"));
         RETVALUE(RFAILED);
      }

      if(endpConCb->type != HI_SCTP_ENDP)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctEndpCloseReq: Failed to find the connection control block\n"));
         hiDoneWithConCb(endpConCb);
         RETVALUE(RFAILED);
      }
   }
   else if(endpIdType == SCT_ENDPID_SU)
   {
#ifdef HI_MULTI_THREADED
      HI_LOCK(&sap->conCbHlLock);
#endif

      found = FALSE;
      for (i = 0; i < hiCb.cfg.numCons; i++)
      {
         if (cmHashListFind(&sap->conCbHlCp, (U8 *)&i, sizeof (UConnId),
             0, (PTR *)&endpConCb) != RFAILED)
         {
#ifdef HI_MULTI_THREADED
            HI_LOCK(&endpConCb->lock);
#endif
            if((endpConCb->type == HI_SCTP_ENDP)&&(endpConCb->suConId == endpId))
            {
               endpId = endpConCb->spConId;
               found  = TRUE;
               break;
            }
#ifdef HI_MULTI_THREADED
            HI_UNLOCK(&endpConCb->lock);
#endif
         }
      }

#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&sap->conCbHlLock);
#endif

      if(found == FALSE)
      {
         HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
            "HiUiSctEndpCloseReq: Failed to find the connection control block\n"));
         RETVALUE(RFAILED);
      }
   }

   /* check connection state */
   if (endpConCb->state == HI_ST_DISCONNECTING)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiUiSctEndpCloseReq: end point already in disconnecting state\n"));
      HiUiSctEndpCloseCfm(&sap->uiPst, sap->suId, endpId, SCT_OK, SCT_CAUSE_NOT_APPL);

      hiDoneWithConCb(endpConCb);
      RETVALUE(ROK);
   }

#ifdef HI_MULTI_THREADED
   HI_LOCK(&sap->conCbHlLock);
#endif

   /* abort and remove all associations at this endpoint */
   for (i = 0; i < hiCb.cfg.numCons; i++)
   {
      if (i == endpId)
         continue;

      if (cmHashListFind(&sap->conCbHlCp, (U8 *)&i, sizeof (UConnId),
               0, (PTR *)&assocConCb) != RFAILED)
      {
#ifdef HI_MULTI_THREADED
         HI_LOCK(&assocConCb->lock);
#endif
         if ((assocConCb->type == HI_SCTP_ASSOC) && 
             (assocConCb->assocSpEndpId == endpId))
         {
            if (assocConCb->state == HI_ST_AW_CON_RSP)
            {
               /* remove all assoc maps for this association */
               ret = hiSctpRemAssocMap(endpConCb, assocConCb);
               if (ret != ROK)
               {
                  HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                     "HiUiSctEndpCloseReq: Failed to delete the assoc maps\n"));
                  /* Not returning from the func, on failure */
               }
             }

            if (assocConCb->state != HI_ST_DISCONNECTING)
            {
               /* set the connection to disconnecting state */
               assocConCb->state = HI_ST_DISCONNECTING;

               /* prepare and send a message to the group thread */
               tMsg.type                = HI_THR_DELCON_DISCIND;
               tMsg.spId                = assocConCb->sap->spId;
               tMsg.spConId             = assocConCb->spConId;
               tMsg.sctDiscInd.status   = SCT_STATUS_ABRT;
               tMsg.sctDiscInd.cause    = SCT_CAUSE_NOT_APPL;
               HI_ZERO(&tMsg.sctDiscInd.rtrvInfo, sizeof(SctRtrvInfo));

               hiSendThrMsg(assocConCb->fdGrpNum, &tMsg);
            }
         }
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&assocConCb->lock);
#endif
      }
   }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->conCbHlLock);
#endif

   /* set the connection to disconnecting state */
   endpConCb->state = HI_ST_DISCONNECTING;

   /* prepare and send a message to the group thread */
   tMsg.type        = HI_THR_DELCON_DISCCFM;
   tMsg.spId        = sap->spId;
   tMsg.spConId     = endpConCb->spConId;
   tMsg.disc.action = HI_CLOSE;

   hiSendThrMsg(endpConCb->fdGrpNum, &tMsg);

   hiDoneWithConCb(endpConCb);

   RETVALUE(ROK);
} /* HiUiSctEndpCloseReq() */

/*
*
*       Fun:   HiUiSctAssocReq
*
*       Desc:  Primitive to Open an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to establish an association with a peer.
*              Termination indications are sent if something goes wrong.
*
*       File:  hi_bdy1.c
*
*/

/* sb021.102: Modification for TOS parameter */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 HiUiSctAssocReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        spEndpId,         /* Service provider Endpoint ID */
UConnId        suAssocId,        /* Service user Association ID */
CmNetAddr     *priDstNAddr,      /* Primary destination network address */
SctPort        dstPort,          /* Destination port number */
SctStrmId      outStrms,         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst,      /* destination network address list */
SctNetAddrLst *srcNAddrLst,      /* source network address list */
SctTos         tos,              /* TOS Parameter */
Buffer        *vsInfo            /* VsInfo - not used anymore */
)
#else
PUBLIC S16 HiUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
                           dstPort, outStrms, dstNAddrLst, srcNAddrLst, 
                           tos, vsInfo)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        spEndpId;         /* Service provider Endpoint ID */
UConnId        suAssocId;        /* Service user Association ID */
CmNetAddr     *priDstNAddr;      /* Primary destination network address */
SctPort        dstPort;          /* Destination port number */
SctStrmId      outStrms;         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst;      /* destination network address list */
SctNetAddrLst *srcNAddrLst;      /* source network address list */
SctTos         tos;              /* TOS Parameter */
Buffer        *vsInfo;           /* VsInfo - not used anymore */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 HiUiSctAssocReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        spEndpId,         /* Service provider Endpoint ID */
UConnId        suAssocId,        /* Service user Association ID */
CmNetAddr     *priDstNAddr,      /* Primary destination network address */
SctPort        dstPort,          /* Destination port number */
SctStrmId      outStrms,         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst,      /* destination network address list */
SctNetAddrLst *srcNAddrLst,      /* source network address list */
Buffer        *vsInfo            /* VsInfo - not used anymore */
)
#else
PUBLIC S16 HiUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
                           dstPort, outStrms, dstNAddrLst, srcNAddrLst, 
                           vsInfo)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        spEndpId;         /* Service provider Endpoint ID */
UConnId        suAssocId;        /* Service user Association ID */
CmNetAddr     *priDstNAddr;      /* Primary destination network address */
SctPort        dstPort;          /* Destination port number */
SctStrmId      outStrms;         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst;      /* destination network address list */
SctNetAddrLst *srcNAddrLst;      /* source network address list */
Buffer        *vsInfo;           /* VsInfo - not used anymore */
#endif /* ANSI */
#endif /* SCT3 */
{
   HiSap        *sap;
   HiAlarmInfo   alInfo;
   S16           ret;
   U8            type;
   HiConCb      *conCb;
   HiConCb      *assocConCb;
   SctRtrvInfo   rtrv;
   U32            idx;
   HiAssocMapCb  *assocMapCb;
   CmInetSctpInitMsg sockOpt;


   TRC3(HiUiSctAssocReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI054, (ErrVal)0, pst->dstInst,
            "HiUiSctAssocReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d), entt(%d), inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocReq(pst, spId(%d), spEndpId(%ld), suAssocId(%ld), \
          dstPort(%d), outStrms(%d))\n",
          spId, spEndpId, suAssocId, dstPort, outStrms));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocReq(pst, spId(%d), spEndpId(%d), suAssocId(%d), \
          dstPort(%d), outStrms(%d))\n",
          spId, spEndpId, suAssocId, dstPort, outStrms));
#endif

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_ASSOCREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_ASSOCREQ, alInfo);

   if(priDstNAddr == NULLP)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctEndpOpenReq: Null primary destination address\n"));
      RETVALUE(RFAILED);
   }

   HI_ZERO(&rtrv, sizeof(SctRtrvInfo));

   /* must have sufficient resources to establish a connection */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongStrt)
   {
      HiUiSctTermInd( &(sap->uiPst), sap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                      &rtrv);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */

   if ((dstNAddrLst != NULLP) && (dstNAddrLst->nmb >= SCT_MAX_NET_ADDRS))
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: destination addresses limit exceed\n"));

      HiUiSctTermInd( &(sap->uiPst), sap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      RETVALUE(RFAILED);
   }

   /* allocate and initialize a conCb for this client */
   ret = hiFindConCb(sap, spEndpId, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Failed to find the connection control block\n"));

      HiUiSctTermInd( &(sap->uiPst), sap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      RETVALUE(RFAILED);
   }

   if(conCb->type != HI_SCTP_ENDP)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Invalid connection control block type\n"));

      HiUiSctTermInd( &(sap->uiPst), sap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   /* hi012.201: Set outstream socket option */
   sockOpt.maxInitReTx = 0;
   sockOpt.maxInitTimeout = 0;
   sockOpt.maxInstreams = 0;
   sockOpt.numOstreams = outStrms;

   ret = cmInetSetOpt(&conCb->conFd, CM_SOCKOPT_LEVEL_SCTP, 
                      CM_INET_OPT_SCTP_INIT_MSG,
                      (Ptr) &sockOpt);
  
   if(ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Failed to set soctket options for outstream\n"));
      HiUiSctTermInd( &(sap->uiPst), sap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   ret = hiAllocConCb(conCb->sap, suAssocId, HI_SRVC_LKSCTP, &type, &assocConCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Failed to allocate the connection control block\n"));
      HiUiSctTermInd(&(sap->uiPst), sap->suId, suAssocId, SCT_ASSOCID_SU, 
                     SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   /* set connection type */
   assocConCb->type          =  HI_SCTP_ASSOC;
   assocConCb->assocSpEndpId =  spEndpId;
     
   assocConCb->state         = HI_ST_AW_CON_RSP;

   /*
    * save the destination address list in assocCb and 
    * insert the destination address list into the hash table
    */
   /* Primary addr shall be stored seprately in assocCb */
   assocConCb->dstPort         = dstPort;
   assocConCb->dstNAddrLst.nmb = 0;

   if (dstNAddrLst != NULLP)
   {
      for (idx = 0; idx < dstNAddrLst->nmb; idx++)
      {
         /* Destination Address list should not contain primary address */
         if (hiSctpCmpCmNetAddr(priDstNAddr, &dstNAddrLst->nAddr[idx]) == ROK)
         continue;

         HI_ALLOC(sizeof(HiAssocMapCb), assocMapCb);
         if (NULLP == assocMapCb)
         {
            HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
                  "HiUiSctAssocReq: Failed to allocate the assoc map control block\n"));
            HiUiSctTermInd(&(sap->uiPst), sap->suId, suAssocId, SCT_ASSOCID_SU, 
                  SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);
            hiSctpRemAssocMap(conCb, assocConCb);
            HI_FREECONCB(assocConCb);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }

         HI_ZERO(assocMapCb, sizeof(HiAssocMapCb));

         assocMapCb->assocMapEntry.port = dstPort;
         HI_CPY_NADDR(&(assocMapCb->assocMapEntry.peerAddr), &dstNAddrLst->nAddr[idx]);
         assocMapCb->assocConCbPtr = assocConCb;

         ret = cmHashListInsert(&(conCb->assocMapHlCp), (PTR)(assocMapCb),
               (U8 *)&(assocMapCb->assocMapEntry), sizeof(HiAssocMapEntry));

         if (ret != ROK)
         {
            HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
                  "HiUiSctAssocReq: Failed to insert in assoc map hash list\n"));
            HiUiSctTermInd(&(sap->uiPst), sap->suId, suAssocId, SCT_ASSOCID_SU, 
                  SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL, &rtrv);
            hiSctpRemAssocMap(conCb, assocConCb);
            HI_FREECONCB(assocConCb);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
}

         assocConCb->dstNAddrLst.nAddr[assocConCb->dstNAddrLst.nmb] = dstNAddrLst->nAddr[idx];
         assocConCb->dstNAddrLst.nmb++;
       }
   }

   /* 
    * insert the primary address into the hash table
    */
   HI_ALLOC(sizeof(HiAssocMapCb), assocMapCb);
   if (NULLP == assocMapCb)
   {
      HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Failed to allocate the assoc map control block\n"));
      HiUiSctTermInd(&(sap->uiPst), sap->suId, suAssocId, SCT_ASSOCID_SU, 
            SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);
      hiSctpRemAssocMap(conCb, assocConCb);
      HI_FREECONCB(assocConCb);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   HI_ZERO(assocMapCb, sizeof(HiAssocMapCb));

   assocMapCb->assocMapEntry.port = dstPort;
   HI_CPY_NADDR(&(assocMapCb->assocMapEntry.peerAddr), priDstNAddr);
   assocMapCb->assocConCbPtr = assocConCb;

   ret = cmHashListInsert(&(conCb->assocMapHlCp), (PTR)(assocMapCb),
                          (U8 *)&(assocMapCb->assocMapEntry), sizeof(HiAssocMapEntry));

   if (ret != ROK)
   {
      HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Failed to insert in assoc map hash list\n"));
      HiUiSctTermInd(&(sap->uiPst), sap->suId, suAssocId, SCT_ASSOCID_SU, 
                     SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL, &rtrv);
      hiSctpRemAssocMap(conCb, assocConCb);
      HI_FREECONCB(assocConCb);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   assocConCb->dstNAddrLst.nAddr[assocConCb->dstNAddrLst.nmb] = *priDstNAddr;
   assocConCb->dstNAddrLst.nmb++;

/* hi024.201 : ntfyCnt added. This is 1 for LINUX and is equal to no. of 
               addresses in the dstAddrLst for SOLARIS. This is reset when
               CommUp is received for the association */
#ifdef SUN_KSCTP
   assocConCb->ntfyCnt = assocConCb->dstNAddrLst.nmb;
#else
   assocConCb->ntfyCnt = 1;
#endif

   ret = hiSctpConnect(conCb, priDstNAddr, dstPort, dstNAddrLst);

   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocReq: Failed to perform sctp connect\n"));
      /* hi024.201 : Remove assocMap and delete assocCb for internal failures.
                     For Connect failure, its deleted when failure notification
                     is received */
      if(ret == RFAILED)
      {
         HiUiSctTermInd(&(sap->uiPst), sap->suId, suAssocId, SCT_ASSOCID_SU,
                        SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL, &rtrv);
         hiSctpRemAssocMap(conCb, assocConCb);
         HI_FREECONCB(assocConCb);
      }
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   /* connect confirm is issued from the thread */

   hiDoneWithConCb(conCb);

   RETVALUE(ROK);
}/* HiUiSctAssocReq() */

/*
*
*       Fun:   HiUiSctAssocRsp
*
*       Desc:  Primitive to Respond to an Open an Association Indication
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to establish an association with a peer.
*              Termination indications are sent if something goes wrong.
*
*       File:  hi_bdy1.c
*
*/

/* sb021.102: Modification for TOS parameter */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 HiUiSctAssocRsp
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spEndpId,         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams,   /* interface specific params */
SctTos                tos,              /* TOS parameter */
SctResult             result,          /* result */
Buffer               *vsInfo           /* VsInfo - not used any more */
)
#else 
PUBLIC S16 HiUiSctAssocRsp(pst, spId, spEndpId, assocIndParams, 
                           tos, result, vsInfo)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spEndpId;         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams;   /* interface specific params */
SctTos                tos;              /* TOS parameter */
SctResult             result;           /* result */
Buffer               *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 HiUiSctAssocRsp
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spEndpId,         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams,   /* interface specific params */
SctResult             result,           /* result */
Buffer               *vsInfo           /* VsInfo - not used any more */
)
#else
PUBLIC S16 HiUiSctAssocRsp(pst, spId, spEndpId, assocIndParams, 
                           result, vsInfo)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spEndpId;         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams;   /* interface specific params */
SctResult             result;           /* result */
Buffer               *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
#endif /* SCT3 */
{
   HiSap        *sap;
   HiAlarmInfo  alInfo;
   S16          ret;
   HiConCb      *conCb;
   SctRtrvInfo   rtrv;
   SctStaInfo    staInfo;
/* hi023.201: added compile time flag for tPar */
#ifdef HI_LKSCTP_USER_CONFIG
   CmTptParam   tPar;
#endif

   TRC3(HiUiSctAssocRsp)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI055, (ErrVal)0, pst->dstInst,
            "HiUiSctAssocRsp() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "-------TUCL------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HIUiSctAssocRsp(pst, spId(%d), spEndpId(%ld))\n",
          spId, spEndpId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HIUiSctAssocRsp(pst, spId(%d), spEndpId(%d))\n",
          spId, spEndpId));
#endif

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_ASSOCRSP, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_ASSOCRSP, alInfo);

   if(assocIndParams == NULLP)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctAssocRsp: Null association indication parameter\n"));
      RETVALUE(RFAILED);
   }

   if (result != SCT_OK && result != SCT_NOK)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
            "HiUiSctAssocRsp: Invalid result value\n"));
      RETVALUE(RFAILED);
   } 


   HI_ZERO(&rtrv, sizeof(SctRtrvInfo));

   if (assocIndParams->type == SCT_ASSOC_IND_INIT)               /* INIT */
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
            "HiUiSctAssocRsp: Invalid assocIndParams type\n"));

      RETVALUE(RFAILED);
   }
   else 
   {
      ret = hiFindConCb(sap, assocIndParams->t.cookieParams.spAssocId, &conCb);
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocRsp: failed to find connection control block\n"));
         HiUiSctTermInd( &(sap->uiPst), sap->suId, assocIndParams->t.cookieParams.suAssocId,
            SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
            &rtrv);
         RETVALUE(RFAILED);
      }

      if(conCb->type != HI_SCTP_ASSOC)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctAssocRsp: invalid connection control block\n"));
         HiUiSctTermInd( &(sap->uiPst), sap->suId, assocIndParams->t.cookieParams.suAssocId,
            SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
            &rtrv);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }

      if (result != SCT_OK)
      {
         hiSctpTermAssoc(conCb, SCT_STATUS_ABRT);
      }
      else
      {
         /* save the suAssocId and mark assoc as connected */
         conCb->suConId = assocIndParams->t.cookieParams.suAssocId;
         /*hi028.201: Initialized the suAssocId */
         conCb->suAssocId = assocIndParams->t.cookieParams.suAssocId;
         conCb->state =  HI_ST_CONNECTED;

         HI_ZERO(&staInfo, sizeof(staInfo));

         staInfo.staType = SCT_GET_ASSOC_INFO;
         ret = hiSctpGetAssocInfo(conCb, &staInfo);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "HiUiSctAssocRsp: failed to get assoc info\n"));
            HiUiSctTermInd(&(sap->uiPst), sap->suId, assocIndParams->t.cookieParams.suAssocId,
               SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
               &rtrv);
            /* hi006.201 Freeing conCb incase of failure in Association Response */
            HI_CLOSE_SOCKET(&conCb->conFd);
            HI_FREECONCB(conCb);
            RETVALUE(RFAILED);
         }

         /* hi006.201 assigning of assocConCb for incoming assoc is moved in assocRsp */
         ret = hiAssignConCb(conCb, HI_THR_ADDCON_CONCFM);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                     "HiUiSctAssocRsp: failed to assign assoc control block\n"));
            HiUiSctTermInd(&(sap->uiPst), sap->suId, assocIndParams->t.cookieParams.suAssocId,
                  SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                  &rtrv);
            HI_CLOSE_SOCKET(&conCb->conFd);
            HI_FREECONCB(conCb);
            RETVALUE(RFAILED);
         }

         /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
         HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId, 
               conCb->suConId, conCb->spConId, &staInfo.u.assocInfo.priDstAddr, 
               SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL, SCT_PROTID_NONE, (Buffer *)NULLP);
#else
         HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId, 
               conCb->suConId, conCb->spConId, &staInfo.u.assocInfo.priDstAddr, 
               SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL, (Buffer *)NULLP);
#endif
      }
   }

/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP_USER_CONFIG

   tPar.type = CM_TPTPARAM_SCTP;
   tPar.u.sctpParam.numOpts = 3;

   tPar.u.sctpParam.sockOpts[0].level  = CM_SOCKOPT_LEVEL_SCTP;
   tPar.u.sctpParam.sockOpts[0].option = CM_SOCKOPT_OPT_SCTP_PEERADDR_PARAMS;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.assocId       = 0;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.s.addrPres    = FALSE;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.pathMaxRxt    = hiCb.cfg.maxPathReTx;
   if (conCb->sap->cfg.hBeatEnable == TRUE)
   {
      tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.hbEnblFlag = CM_INET_OPT_ENABLE;
      tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.hbInterval = conCb->sap->cfg.intervalTm;
   }
   else if (conCb->sap->cfg.hBeatEnable == FALSE)
      tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.hbEnblFlag = CM_INET_OPT_DISABLE;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.sackDelayFlag = CM_INET_OPT_DEFAULT;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.sackDelay     = 0;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.pmtudFlag     = CM_INET_OPT_DEFAULT;
   tPar.u.sctpParam.sockOpts[0].optVal.sctpPeerAddrParams.pathMtu       = 0;

   tPar.u.sctpParam.sockOpts[1].level  = CM_SOCKOPT_LEVEL_SCTP;
   tPar.u.sctpParam.sockOpts[1].option = CM_SOCKOPT_OPT_SCTP_ASSOC_PARAMS;
   tPar.u.sctpParam.sockOpts[1].optVal.sctpPeerAssocParams.assocId          = 0;
   tPar.u.sctpParam.sockOpts[1].optVal.sctpPeerAssocParams.cookieLife       = conCb->sap->cfg.cookieLife;
   tPar.u.sctpParam.sockOpts[1].optVal.sctpPeerAssocParams.assocMaxReTx     = hiCb.cfg.maxAssocReTx;
   tPar.u.sctpParam.sockOpts[1].optVal.sctpPeerAssocParams.numberOfPeerDest = 0;
   tPar.u.sctpParam.sockOpts[1].optVal.sctpPeerAssocParams.peerRwnd         = 0;
   tPar.u.sctpParam.sockOpts[1].optVal.sctpPeerAssocParams.localRwnd        = 0;

   tPar.u.sctpParam.sockOpts[2].level  = CM_SOCKOPT_LEVEL_SCTP;
   tPar.u.sctpParam.sockOpts[2].option = CM_SOCKOPT_OPT_SCTP_RTO_INFO;
   tPar.u.sctpParam.sockOpts[2].optVal.sctpRtoInfo.assocId    = 0;
   tPar.u.sctpParam.sockOpts[2].optVal.sctpRtoInfo.rtoInitial = conCb->sap->cfg.rtoInitial;
   tPar.u.sctpParam.sockOpts[2].optVal.sctpRtoInfo.rtoMax     = conCb->sap->cfg.rtoMax;
   tPar.u.sctpParam.sockOpts[2].optVal.sctpRtoInfo.rtoMin     = conCb->sap->cfg.rtoMin;

   ret = hiSetSockOpt(conCb, &tPar);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf, "HiUiSctAssocRsp : failed to set socket options\n"));
      /* hi023.201: changed RETVOID to RETVALUE as this function 
                    returns S16 type */
      RETVALUE(RFAILED);
   }

#endif /* HI_LKSCTP_USER_CONFIG */

   hiDoneWithConCb(conCb);

   RETVALUE(ROK);

}/* HiUiSctAssocRsp() */

/*
*
*       Fun:   HiUiSctTermReq
*
*       Desc:  Primitive to Request Termination of an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to terminate an association with a peer.
*              Termination confirmation is sent on successful completion with
*              positive status, and with negative status if something went
*              wrong. The termination procedure can be graceful or ungraceful.
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctTermReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               assocId,          /* Association ID */
U8                    assocIdType,      /* Association ID type */
Bool                  abortFlg          /* Termination type */
)
#else
PUBLIC S16 HiUiSctTermReq(pst, spId, assocId, assocIdType, abortFlg)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               assocId;          /* Association ID */
U8                    assocIdType;      /* Association ID type */
Bool                  abortFlg;         /* Termination type */
#endif
{
   /* local parameters */
   HiSap        *sap;
   HiAlarmInfo  alInfo;
   S16          ret;
   UConnId      id;
   HiConCb      *conCb;
   HiThrMsg     tMsg;
   HiConCb      *endpConCb;

   TRC3(HiUiSctTermReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);
       
   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI056, (ErrVal)0, pst->dstInst,
            "HiUiSctTermReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "-------TUCL------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctTermReq(pst, spId(%d), assocId(%ld), assocIdType(%d), \
       abortFlg(%d))\n",
       spId, assocId, assocIdType, abortFlg));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctTermReq(pst, spId(%d), assocId(%d), assocIdType(%d), \
       abortFlg(%d))\n",
       spId, assocId, assocIdType, abortFlg));
#endif

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_ASSOCREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_ASSOCREQ, alInfo);

   if (assocIdType != SCT_ASSOCID_SP && assocIdType != SCT_ASSOCID_SU)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctTermReq: invalid association id type\n"));
      RETVALUE(RFAILED);
   }

   if(abortFlg != TRUE && abortFlg != FALSE)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctTermReq: invalid abortFlg value\n"));
      RETVALUE(RFAILED);
   }


   if(assocIdType == SCT_ASSOCID_SP)
   {
      ret = hiFindConCb(sap, assocId, &conCb);
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctTermReq: failed to find connection control block\n"));
            RETVALUE(RFAILED);
      }

      if(conCb->type != HI_SCTP_ASSOC)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctTermReq: invalid connection control block\n"));
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }

   }
   else if(assocIdType == SCT_ASSOCID_SU)
   {
#ifdef HI_MULTI_THREADED
      HI_LOCK(&sap->conCbHlLock);
#endif

      /* Search for an unused spConId, assign it to this connection,
       * and put the connection in the SAP's connection hash list.
       */
      for (id = 1;  id <= hiCb.cfg.numCons;  id++)
      {
         if (cmHashListFind(&sap->conCbHlCp, (U8 *)&id, sizeof (UConnId),
               0, (PTR *)&conCb) != RFAILED)
         {
#ifdef HI_MULTI_THREADED
            HI_LOCK(&conCb->lock); 
#endif
            if((conCb->type == HI_SCTP_ASSOC) && (assocId == conCb->suConId))
                /* done, either way */
                break;
            else
            {
#ifdef HI_MULTI_THREADED
                HI_UNLOCK(&conCb->lock);
#endif
            }
         }
      }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->conCbHlLock);
#endif

      if (id > hiCb.cfg.numCons)
      {
         HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
            "HiUiSctTermReq: failed to find connection control block\n"));
         RETVALUE(RFAILED);
      }
   }


   /* check connection state */
   if (conCb->state != HI_ST_CONNECTED)
   {
      if (conCb->state == HI_ST_AW_CON_RSP)
      {
         ret = hiFindConCb(sap, conCb->assocSpEndpId, &endpConCb);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "HiUiSctTermReq: failed to find endp control block\n"));
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }

         /* remove all assoc maps for this association */
         ret = hiSctpRemAssocMap(endpConCb, conCb);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "HiUiSctTermReq: failed to delete assoc maps\n"));
            /* Not returning from the func, on failure */
         }

         hiDoneWithConCb(endpConCb);
      }

      HiUiSctTermCfm(&sap->uiPst, sap->suId, assocId, SCT_OK, SCT_CAUSE_NOT_APPL);

      hiDoneWithConCb(conCb);

      RETVALUE(ROK);
   }

   /* set the connection to disconnecting state */
   conCb->state = HI_ST_DISCONNECTING;

   /* hi028.201: Shutdown gracefully incase if abrtFlag is FALSE*/
   if(abortFlg == TRUE)
   {
      /* prepare and send a message to the group thread */
      tMsg.type        = HI_THR_DELCON_DISCCFM;
      tMsg.spId        = sap->spId;
      tMsg.spConId     = conCb->spConId;
      tMsg.disc.action = HI_ABORT;

      hiSendThrMsg(conCb->fdGrpNum, &tMsg);
   }
   else
   {
      cmInetShutDownSctp(&conCb->conFd);
   }

   hiDoneWithConCb(conCb);

   RETVALUE(ROK);
}/* HiUiSctTermReq() */

/*
*
*       Fun:   HiUiSctSetPriReq
*
*       Desc:  Primitive to Set a New Primary Address on an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctSetPriReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr          /* New primary network address */
)
#else
PUBLIC S16 HiUiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
#endif
{
   HiSap        *sap;
   HiAlarmInfo   alInfo;
   S16           ret;
   HiConCb      *conCb;

   TRC3(HiUiSctSetPriReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI057, (ErrVal)0, pst->dstInst,
            "HiUiSctSetPriReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }
 
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "-------TUCL------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctSetPriReq(pst, spId(%d), spAssocId(%ld), dstNAddr)\n",
       spId, spAssocId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctSetPriReq(pst, spId(%d), spAssocId(%d), dstNAddr)\n",
       spId, spAssocId));
#endif

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */
   ret = ROK;

   /* Sanity checks */

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_SETPRIREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_SETPRIREQ, alInfo);

   if (dstNAddr == NULLP)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
        "HiUiSctSetPriReq: invalid parameter dstNAddr\n"));
      RETVALUE(RFAILED);
   }


   ret = hiFindConCb(sap, spAssocId, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctSetPriReq: failed to find connection control block\n"));
      RETVALUE(RFAILED);
   }

   if(conCb->type != HI_SCTP_ASSOC)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctSetPriReq: invalid connection control block\n"));
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   ret = hiSctpSetPriReq(conCb, dstNAddr);

   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctSetPriReq: failed to set primary addr\n"));
      HiUiSctSetPriCfm(&(sap->uiPst), sap->suId, conCb->suConId,
                    SCT_NOK, SCT_CAUSE_SOCK_ERR);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   HiUiSctSetPriCfm(&(sap->uiPst), sap->suId, conCb->suConId,
                    SCT_OK, SCT_CAUSE_NOT_APPL);

   hiDoneWithConCb(conCb);

   RETVALUE(ROK);
}/* HiUiSctSetPriReq() */

/*
*
*       Fun:   HiUiSctHBeatReq
*
*       Desc:  Primitive to Request enable/disable Heartbeat Information.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Heartbeat can be enabled/disabled per association or per
*              destination address.
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctHBeatReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* peer address */
U16                   intervalTime,     /* heartbeat periodicity value in milliseconds */
SctStatus             status            /* Type of request to process */
)
#else
PUBLIC S16 HiUiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* peer address */
U16                   intervalTime;     /* heartbeat periodicity value in milliseconds */
SctStatus             status;           /* Type of request to process */
#endif
{
   HiSap        *sap;
   HiAlarmInfo   alInfo;
   S16           ret;
   HiConCb      *conCb;
   /* local parameters */

   TRC3(HiUiSctHBeatReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI058, (ErrVal)0, pst->dstInst,
            "HiUiSctHBeatReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "-------TUCL------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctHBeatReq(pst, spId(%d), spAssocId(%ld), dstNAddr, \
          intervalTime(%d), status(%d))\n",
          spId, spAssocId, intervalTime, status));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctHBeatReq(pst, spId(%d), spAssocId(%d), dstNAddr, \
          intervalTime(%d), status(%d))\n",
          spId, spAssocId, intervalTime, status));
#endif


#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif /* SS_MULTIPLE_PROCS */

   ret = ROK;

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_HBEATREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_HBEATREQ, alInfo);

   if(status != SCT_HBEAT_ENB_DTA &&  status != SCT_HBEAT_DIS_DTA && 
      status != SCT_HBEAT_ENB_ASSOC &&  status != SCT_HBEAT_DIS_ASSOC)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
        "HiUiSctHBeatReq: invalid Status\n"));
      RETVALUE(RFAILED);
   }


   ret = hiFindConCb(sap, spAssocId, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctHBeatReq: failed to find connection control block\n"));
      RETVALUE(RFAILED);
   }

   if(conCb->type != HI_SCTP_ASSOC)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctHBeatReq: invalid connection control block\n"));
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
  
   ret = hiSctpHbeatReq(conCb, dstNAddr, intervalTime, status);

   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctHBeatReq: failed to handle hbeat req\n"));
      HiUiSctHBeatCfm(&(sap->uiPst), sap->suId, conCb->suConId, dstNAddr, 
                      status, SCT_NOK, SCT_CAUSE_SOCK_ERR);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   HiUiSctHBeatCfm(&(sap->uiPst), sap->suId, conCb->suConId, dstNAddr, 
                   status, SCT_OK, SCT_CAUSE_NOT_APPL);

   hiDoneWithConCb(conCb);

   RETVALUE(ROK);
}/* HiUiSctHBeatReq() */

/*
*
*       Fun:   HiUiSctDatReq
*
*       Desc:  Primitive Request to send Data to a peer.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctDatReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
SctStrmId             strmId,           /* Stream ID */
Bool                  unorderFlg,       /* unordered delivery */
Bool                  nobundleFlg,      /* no bundling  */
U16                   lifeTime,         /* datagram lifetime value */
U32                   protId,           /* Protocol ID */
Buffer               *mBuf              /* message buffer */
)
#else
PUBLIC S16 HiUiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
                         nobundleFlg, lifeTime, protId, mBuf)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
SctStrmId             strmId;           /* Stream ID */
Bool                  unorderFlg;       /* unordered delivery */
Bool                  nobundleFlg;      /* no bundling  */
U16                   lifeTime;         /* datagram lifetime value */
U32                   protId;           /* Protocol ID */
Buffer               *mBuf;             /* message buffer */
#endif
{
   /* local parameters */
   HiSap        *sap;
   HiAlarmInfo   alInfo;
   S16           ret;
   HiConCb      *conCb;
   MsgLen        bufLen;

   TRC3(HiUiSctDatReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI059, (ErrVal)0, pst->dstInst,
            "HiUiSctDatReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "-------TUCL------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctDatReq(pst, spId(%d), spAssocId(%ld), dstNAddr, strmId(%d), \
       unorderFlg(%d), nobundleFlg(%d), lifeTime(%d), protId(%ld), mBuf)\n",
       spId, spAssocId, strmId, unorderFlg, nobundleFlg, lifeTime, protId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctDatReq(pst, spId(%d), spAssocId(%d), dstNAddr, strmId(%d), \
       unorderFlg(%d), nobundleFlg(%d), lifeTime(%d), protId(%d), mBuf)\n",
       spId, spAssocId, strmId, unorderFlg, nobundleFlg, lifeTime, protId));
#endif

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* Sanity checks */

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   if (mBuf == NULLP)
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctDatReq: null data buffer\n"));
      RETVALUE(RFAILED);
   } 

   /* get the SAP */
   if (spId >= (SpId)hiCb.cfg.numSaps || spId < 0 || !(sap = hiCb.saps[spId]))
   {
      HILOGERROR_INT_PAR(EHI060, spId, 0,
         "Invalid SAP Id");
      SPutMsg(mBuf);

      alInfo.spId = spId;
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_SPID, &alInfo);
      RETVALUE(RFAILED);
   }

   /* check SAP state */
   {
      if (sap->state != HI_ST_BND)
      {
         HILOGERROR_INT_PAR(EHI061, sap->state, 0,
               "SAP not bound");
         SPutMsg(mBuf);

         alInfo.type = LHI_ALARMINFO_SAP_STATE;
         alInfo.inf.state = sap->state;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
               LCM_CAUSE_INV_STATE, &alInfo);
         RETVALUE(RFAILED);
      }
      if (sap->pendOp.flag || hiCb.pendOp.flag)
      {
         HILOGERROR_INT_PAR(EHI062, 0, 0,
               "SAP/layer is under management control request");
         SPutMsg(mBuf);

         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
               LCM_CAUSE_INV_STATE, &alInfo);
         RETVALUE(RFAILED); 
      }
   }

   if ((unorderFlg != TRUE && unorderFlg != FALSE) || 
       (nobundleFlg != TRUE && nobundleFlg != FALSE))
   {
      HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiSctDatReq: invalid flag value(s)\n"));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   } 

   ret = hiFindConCb(sap, spAssocId, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctDatReq: failed to find connection control block\n"));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* must have sufficient resources to establish a connection */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongDrop)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctDatReq: resource unsufficient to send the data\n"));

      /* hi019.201: give status indication to user with mbuf */
#ifdef SCT7
      HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId,
               conCb->suAssocId, spAssocId, dstNAddr,
               SCT_STATUS_SND_FAIL, SCT_CAUSE_OUTRES, protId, mBuf);
#else
      HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId,
               conCb->suAssocId, spAssocId, dstNAddr,
               SCT_STATUS_SND_FAIL, SCT_CAUSE_OUTRES, mBuf);
#endif

      /*hi028.201: Release a connection control block in failure cases. */
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

#endif /* HI_NO_CHK_RES */

   ret = SFndLenMsg(mBuf, &bufLen);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctDatReq: failed to find the msg len\n"));

      /* hi019.201: give status indication to user with mbuf */
#ifdef SCT7
      HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId,
               conCb->suAssocId, spAssocId, dstNAddr,
               SCT_STATUS_SND_FAIL, SCT_CAUSE_UNKNOWN, protId, mBuf);
#else
      HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId,
               conCb->suAssocId, spAssocId, dstNAddr,
               SCT_STATUS_SND_FAIL, SCT_CAUSE_UNKNOWN, mBuf);
#endif
      /* hi028.201: Release a connection block in failure cases. */
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   if ((conCb->type != HI_SCTP_ASSOC) || (conCb->state != HI_ST_CONNECTED))
   {  
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctDatReq: invalid connection control block\n"));

      /* hi019.201: give status indication to user with mbuf */
#ifdef SCT7
      HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId,
               conCb->suAssocId, spAssocId, dstNAddr,
               SCT_STATUS_SND_FAIL, SCT_CAUSE_INV_STATE, protId, mBuf);
#else
      HiUiSctStaInd(&conCb->sap->uiPst, conCb->sap->suId,
               conCb->suAssocId, spAssocId, dstNAddr,
               SCT_STATUS_SND_FAIL, SCT_CAUSE_INV_STATE, mBuf);
#endif
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }


   ret = hiSctpSndMsg(conCb, dstNAddr, strmId, unorderFlg,
                      nobundleFlg, lifeTime, protId, mBuf);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctDatReq: failed to send sctp message\n"));
      hiDoneWithConCb(conCb);
      /* mBuf is already released in hiSctpSndMsg() */
      RETVALUE(RFAILED);
   }

   hiDoneWithConCb(conCb);

   /* no confirm */
   RETVALUE(ROK);
}/* HiUiSctDatReq() */

/*
*
*       Fun:   HiUiSctStaReq
*
*       Desc:  Primitive Request for Status Information.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiSctStaReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
U8                    staType           /* Status type */
)
#else
PUBLIC S16 HiUiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
U8                    staType;          /* Status type */
#endif
{
   /* local parameters */
   HiSap        *sap;
   HiAlarmInfo  alInfo;
   S16          ret;
   HiConCb      *conCb;
   SctStaInfo    staInfo;

   TRC3(HiUiSctStaReq)

#ifdef SS_MULTIPLE_PROCS

   if(pst == NULLP)
      RETVALUE(RFAILED);

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&hiCbPtr) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI063, (ErrVal)0, pst->dstInst,
            "HiUiSctStaReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "-------TUCL------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctStaReq(pst, spId(%d), spAssocId(%lu), dstNAddr, staType(%d))\n",
       spId, spAssocId, staType));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
       "HiUiSctStaReq(pst, spId(%d), spAssocId(%u), dstNAddr, staType(%d))\n",
       spId, spAssocId, staType));
#endif

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   ret = ROK;

   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_DATREQ, alInfo, sap);

   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_DATREQ, alInfo);

   ret = hiFindConCb(sap, spAssocId, &conCb);
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctStaReq: failed to find connection control block\n"));
      RETVALUE(RFAILED);
   }

   if (conCb->type != HI_SCTP_ASSOC)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
        "HiUiSctStaReq: invalid connection control block\n"));
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }

   HI_ZERO(&staInfo, sizeof(staInfo));

   staInfo.staType = staType;


   switch ( staType )
   {
      case SCT_GET_ASSOC_INFO:
      {
         ret = hiSctpGetAssocInfo(conCb, &staInfo);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "HiUiSctStaReq: failed to get assoc info\n"));
            HiUiSctStaCfm(&(sap->uiPst), sap->suId, conCb->suConId,
                          dstNAddr, SCT_NOK, SCT_CAUSE_SOCK_ERR, &staInfo);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }

         HiUiSctStaCfm(&(sap->uiPst), sap->suId, conCb->suConId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL, &staInfo);

         break;
      }

      case SCT_GET_ADDR_INFO:
      {
         if (dstNAddr == NULLP)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "HiUiSctStaReq: null dstNAddr parameter\n"));
            HiUiSctStaCfm(&(sap->uiPst), sap->suId, conCb->suConId,
               dstNAddr, SCT_NOK, SCT_CAUSE_INV_PAR_VAL, &staInfo);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }

         ret = hiSctpGetAddrInfo(conCb, dstNAddr, &staInfo);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "HiUiSctStaReq: failed to get addr info\n"));
            HiUiSctStaCfm(&(sap->uiPst), sap->suId, conCb->suConId,
               dstNAddr, SCT_NOK, SCT_CAUSE_SOCK_ERR, &staInfo);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }

         HiUiSctStaCfm(&(sap->uiPst), sap->suId, conCb->suConId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL, &staInfo);

         break;
      }

      case SCT_GET_FLC_INFO:
         if (conCb->flc == 0)
         {
            HiUiSctFlcInd(&conCb->sap->uiPst, conCb->sap->suId, 
                          conCb->suConId, SCT_FLC_INACTIVE); 
         }
         else
         {
            HiUiSctFlcInd(&conCb->sap->uiPst, conCb->sap->suId, 
                          conCb->suConId, SCT_FLC_ACTIVE); 
         }
         break;

      default:
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiSctStaReq: invalid status type\n"));
         HiUiSctStaCfm(&(sap->uiPst), sap->suId, conCb->suConId,
                       dstNAddr, SCT_NOK, SCT_CAUSE_INV_PAR_VAL, &staInfo);
         break;
   }

   hiDoneWithConCb(conCb);

   /* All the confirms have been sent by now */
   RETVALUE(ROK);
}/* HiUiSctStaReq() */


#endif


/********************************************************************30**

         End of file:     tl_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Tue Feb  9 11:15:40 2016

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
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
1.1+        hi002.11 asa  1. changes for loopback mode.
                          2. added spConId in HitUDatReq.
                          3. added HitConReq procedure for UDP clients.
                          4. added processing for TCP application 
                             specific header.
                          5. miscellaneous bug fixes.
1.1+        hi003.11 asa  1. removed an error check from HitBndReq
                          2. initialized "type" in HitConReq
1.1+        hi005.11 cvp  1. corrected confirm type in the LhiStaReq 
                             primitive.
/main/2     ---      cvp  1. added support for multiple file descriptor 
                             sets.
                          2. added support for CM_INADDR_ANY server for 
                             loopback mode.
                          3. added check for ROUTRES return value from 
                             cmInetRecvMsg and cmInetSendMsg functions.
                          4. changed the copyright header.
/main/4     ---      sb   1. Changes for Raw Socket Support in TUCL.
                          2. Application also listen to Raw ICMP messages 
                             depending on the filtering parameter provided 
                             in ServOpenReq primitive.
                          3. Ip header parameters like tos, ttl, dfBit can
                             be modified for any Raw outgoing packet. 
/main/4     hi002.13 cvp  1. Check for RCLOSED from cmInetSendMsg.
/main/4     hi003.13 cvp  1. Added support for new service type.
                          2. Incrementing queues sizes if message was not 
                             sent fully.
/main/4     hi005.13 cvp  1.  Added a check for RCLOSED from 
                             cmInetConnect function to check for 
                             connection refused errors.
                          2. Removed compiler warnings in LPBK mode.
/main/4     hi007.13 zmc  1. Fix the compilation failure due to hi005.13 
                             patch.
                          2. Add the checking for the common UDP socket.
                     cvp  3. Removing the host to network conversion of
                             the source address. This is done in the
                             hiPkIpv4Hdr function.
/main/4     ---      cvp  1. Multi-threaded related changes.
                          2. Changes to support IPV6.
                          3. changed the copyright header.
/main/4     hi001.104 mmh 1. Fixed a bug (!mBuf) to (mBuf) in HiUiHitUDatReq()
                             and HiUiHitDatReq(). 
                          2. Added check for return value from cmInetSendMsg()
                             in function HiUiHitUDatReq(). The value RCLOSED
                             will be returned when an ICMP message is 
                             received on connected UDP socket.
                      cvp 3. Zeroing out only the cfg structure and not the 
                             whole hiCb in shutdown.
            hi004.104 mmh 1. TOS value initialized.
            hi009.104 mmh 1. added new service type in HiUiHitServOpenReq()
                          2. call cmInetSendMsg & cmInetRecvMsg with different
                             new arguments.
                          3. added check for invalid IPv4 options length.
                          4. added to set/reset IPv4 IP_OPTIONS
                          5. update the header length and total length
                             when IP_OPTIONS are inserted manually.
                          6. insert IP_OPTION router alert by socket option
                             or manually if not supported.
                          7. rolling upgrade changes, under the compile flag
                              HI_RUG, as per tcr0020.txt:
                           -  during general configuration, memory allocation
                              for storing interface version information and 
                              configuration and re-configuration of LM 
                              interface version number within lmPst. 
                           -  lmPst made reconfigurable.
                           -  reconfigure version info in already configured
                              snap or copy version info to new sap.
                           -  during shutdown free memory allocated for version
                              information.
                           -  fill up self and remote interface version info 
                              in status struct in function HiMiLhiStaReq
                           -  in the system agent control request, handling for 
                              request type SHT_REQTYPE_GETVER and
                              SHT_REQTYPE_SETVER.
                           -  in HiMiShtCntrlReq() added the missing assignment
/main/4     hi013.104 bdu 1. setting the interface in the outgoing packet in 
                             UDatReq if IPV6_OPTS_SUPPORTED is enabled. 
/main/4     hi014.104 bdu 1. Fix one problem in HiUiHitDatReq.
/main/4     hi015.104 zmc 1. reset the counter
/main/4     hi017.104 zmc 1. Needs to first check the resource 
                             before checking the flag
/main/4     hi018.104 zmc 1. If socket not available free mBuf and 
                             return failure
/main/4     hi019.104 zmc 1. Fix the memory leak when spConnId is not
                             present in HiUiHitUDatReq.
/main/4     hi022.104 rs  1. Fix for sending disconnect indication.
/main/5      ---       kp  1. Updated for release 1.5.
/main/5     hi001.105 sg   1. Fixed compilation warning 
/main/5     hi002.105 jc   1. Added Check for cfgDone for LM Primitives
                      ss   2. Fix for setting IP TOS for accepted connections
                           3. Fix for initializing tPar->u.sockParam.numOpts
                           4. SS_NULTIPLE_PROC flag added.
                           5. HI_DISABLE_GENSOCKET - compile out TUCL Generic 
                              UDP Socket
/main/5     hi003.105 ss   1. HI_MULTI_THREADED flag removed for cntrl cfm.
                           2. send cntrl cfm if gen cfg not done.
/main/5+    hi004.105 ss   1. Moved hiActvInit function to hi_bdy1.c for 
                              code reorganization. 
/main/5+    hi006.105 ss   1. Corrected the flow control check. 
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi014.105 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/5+    hi016.105 svp  1. Given a check for NULLP before accessing conCb
                              in HiUiHitDescReq() to avoid FMR/W 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6     hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6+    hi005.201  rss  1. Don't close non connected udp in case of send failure.,
/main/6+    hi006.201  hsingh   1. Freeing conCb incase of failure in Association Response 
                                2. assigning of assocConCb for incoming assoc is moved in assocRsp 
/main/6+    hi011.201  cp  1. handling Network failure sending error 
/main/6+    hi012.201  rcs 1. Handling outstream socket option in AssocReq.
/main/6+    hi018.201  rcs 1. Klockwork error fix.
/main/6+    hi019.201  rcs 1. Included protId parameter in status indication. 
                           2. Added SctStaInd in SctDatReq in case of TUCL internal errors.
/main/6+    hi023.201  rcs 1. GCC warning fix for KSCTP. 
/main/6+    hi024.201  rshekar 1.In AssocReq function, during connect, removal of  assocMap 
                                 and deletion of assocCb is only for internal failures.
                                 For Connect failure, its deleted when failure notification
                                 is received. 
/main/6+    hi025.201 rss  1. Gaurd the check resource implementation under the flag 
                              HI_NO_CHK_RES
/main/6+    hi028.201 ragrawal 1. Initialized the suAssocId in HiUiSctAssocRsp().
                               2. Shutdown connection gracefully incase if 
                                  abrtFlag is FALSE in HiUiSctTermReq().
                               3. Release a connection block in failure cases
                                  in HiUiSctDatReq().
                               4. Changed the interface version in function 
                                  HiUiSctBndReq().
                               5. Added dbgMask and protected under HI_DEBUG  
                                  flag in hiActvInit().
                               6. Locking mechanism is used before using lmPst
                                  in HiMiLhiCfgReq() function.
/main/6+   hi029.201  ragrawal 1. Fix for 64 bit compilation warnings.
/main/6+   hi032.201  ragrawal 1. Removed locking and unloacking of lmpst lock
                                  in HiMiLhiCfgReq().
*********************************************************************91*/
