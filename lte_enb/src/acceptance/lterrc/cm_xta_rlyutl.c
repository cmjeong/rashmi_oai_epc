
/********************************************************************20**

     Name:    cm_xta_rlyutl.c 

     Type:    C source file

     Desc:    C code for Configuration and Control Handler of Relay.

     File:    cm_xta_rlyutl.c

     Sid:      cm_xta_rlyutl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:28 2015

     Prg:     up 

*********************************************************************21*/

#ifdef CM_XTA_RELAY
/* header include files (.h) */

/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta_app.h"
#include "cm_ftha.h"
#include "lry.h"
#include "cm_xta.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta_app.x"
#include "cm_ftha.x"
#include "lry.x"
#include "cm_xta.x"

#define CMXTA_MAX_HDR_LEN   400
#define TSTINST  0

/*
*
*       Fun:   cmXtaRlyGenCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaRlyGenCfgReq
(
ProcId   srcProcId,                       /*-- Destination low procId --*/
ProcId   dstProcId,                        /*-- Destination higher procId --*/
U16      nmbChannel
)
#else
PUBLIC S16 cmXtaRlyGenCfgReq(srcProcId, dstProcId, nmbChannel)
ProcId   srcProcId;                       /*-- Destination low procId --*/
ProcId   dstProcId;                        /*-- Destination higher procId --*/
U16      nmbChannel;
#endif
{
   RyMngmt      cfg;
   Pst          pst;

   TRC2(cmXtaRlyGenCfgReq)

   pst.dstProcId = dstProcId; 
   pst.dstEnt = ENTRY;
   pst.dstInst = TSTINST;
   pst.srcProcId = srcProcId; 
   pst.srcEnt = ENTSM;
   pst.srcInst = TSTINST;
   pst.prior = PRIOR0;
   pst.route = RTESPEC;
   /* cm_xta_rlyutl_c_001.main_1: Changed the selector value. With the new
    * relay implementation, the selector value will be always zero as it
    * works with multi-threading and there is a separate thread which sends
    * back the CFM */
   pst.selector = 0;

   pst.region = DFLT_REGION;
   pst.pool = DFLT_POOL;

   cfg.hdr.msgType = TCFG;

   cfg.hdr.elmId.elmnt = STGEN;

   cfg.hdr.response.selector = LRY_SEL_LC;
   cfg.hdr.response.prior = 0;
   cfg.hdr.response.route = 0;
   cfg.hdr.response.mem.region = DFLT_REGION;
   cfg.hdr.response.mem.pool = DFLT_POOL;
 
   /* cm_xta_rlyutl_c_001.main_1: Removed redundant code */
   cfg.t.cfg.s.ryGenCfg.nmbChan = nmbChannel;
   
   cfg.t.cfg.s.ryGenCfg.tmrRes = 1;            /* timer resolution */

#if OLD_RY
   cfg.t.cfg.s.ryGenCfg.usta = FALSE;            /* timer resolution */
#endif

   /* cm_xta_rlyutl_c_001.main_1: Changed the selector value. With the new
    * relay implementation, the selector value will be always zero as it
    * works with multi-threading and there is a separate thread which sends
    * back the CFM */
   cfg.t.cfg.s.ryGenCfg.lmPst.selector = 0;

   cfg.t.cfg.s.ryGenCfg.lmPst.srcProcId = dstProcId; 
   cfg.t.cfg.s.ryGenCfg.lmPst.srcEnt = ENTRY;
   cfg.t.cfg.s.ryGenCfg.lmPst.srcInst = TSTINST;
   cfg.t.cfg.s.ryGenCfg.lmPst.dstProcId = srcProcId; 
   cfg.t.cfg.s.ryGenCfg.lmPst.dstEnt = ENTSM;
   cfg.t.cfg.s.ryGenCfg.lmPst.dstInst = TSTINST;
   cfg.t.cfg.s.ryGenCfg.lmPst.prior = PRIOR0;
   cfg.t.cfg.s.ryGenCfg.lmPst.route = RTESPEC;

   cfg.t.cfg.s.ryGenCfg.lmPst.region = DFLT_REGION;
   cfg.t.cfg.s.ryGenCfg.lmPst.pool = DFLT_POOL;

   SmMiLryCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);

}/* soAcHdlShStaCntrlReq*/
/*
*
*       Fun:   cmXtaRlyShutDownReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  cm_xta_rlyutl.c
*
*/

/* cm_xta_rlyutl_c_001.main_1: Added function to shutdown the relay */
#ifdef ANSI
PUBLIC S16 cmXtaRlyShutDownReq
(
ProcId   srcProcId,                       /*-- Destination low procId --*/
ProcId   dstProcId                        /*-- Destination higher procId --*/
)
#else
PUBLIC S16 cmXtaRlyShutDownReq(srcProcId, dstProcId, nmbChannel)
ProcId   srcProcId;                       /*-- Destination low procId --*/
ProcId   dstProcId;                        /*-- Destination higher procId --*/
#endif
{
   RyMngmt      cfg;
   Pst          pst;

   TRC2(cmXtaRlyShutDownReq)

   pst.dstProcId = dstProcId; 
   pst.dstEnt = ENTRY;
   pst.dstInst = TSTINST;
   pst.srcProcId = srcProcId; 
   pst.srcEnt = ENTSM;
   pst.srcInst = TSTINST;
   pst.prior = PRIOR0;
   pst.route = RTESPEC;
   /* cm_xta_rlyutl_c_001.main_1: Changed the selector value. With the new
    * relay implementation, the selector value will be always zero as it
    * works with multi-threading and there is a separate thread which sends
    * back the CFM */
   pst.selector = 0;
   pst.region = DFLT_REGION;
   pst.pool = DFLT_POOL;

   cfg.hdr.msgType = TCNTRL;

   cfg.hdr.elmId.elmnt = ASHUTDOWN;
   cfg.t.cntrl.action = ASHUTDOWN;
   cfg.hdr.entId.ent = ENTRY;

   cfg.hdr.response.selector = LRY_SEL_LC;
   cfg.hdr.response.prior = 0;
   cfg.hdr.response.route = 0;
   cfg.hdr.response.mem.region = DFLT_REGION;
   cfg.hdr.response.mem.pool = DFLT_POOL;
 
   SmMiLryCntrlReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaRlyShutDownReq */

/*
*
*       Fun:   cmXtaRlyChannelGenCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaRlyChannelCfgReq
(
U16      channelId,                       /* Channel Id ----*/
ProcId   srcProcId,                   /*-- Destination low procId --*/    
ProcId   dstProcId,                    /*-- Destination higher procId --*/
U32      port,                        /*-- Destination port --*/
Txt      hostName[CMXTA_MAX_HDR_LEN], /*-- Destination IP address --*/
U32      localport,                    /*-- Local Port --*/
ProcId   localProcId                   /*-- Destination low procId --*/    
)
#else
PUBLIC S16 cmXtaRlyChannelCfgReq(channelId, srcProcId,dstProcId ,port,  hostName, localport, localProcId)
U16      channelId;                       /* Channel Id ----*/
ProcId   srcProcId;                       /*-- Destination low procId --*/
ProcId   dstProcId;                        /*-- Destination higher procId --*/
U32      port;                            /*-- Destination port --*/
Txt      hostName[CMXTA_MAX_HDR_LEN];     /*-- Destination IP address --*/
U32      localport;                       /*-- Local Port --*/
ProcId   localProcId;                   /*-- Destination low procId --*/    
#endif
{
   RyMngmt      cfg;
   Pst smPst;

   TRC2(cmXtaRlyChannelCfgReq)

      CMXTA_ZERO(&cfg, sizeof(RyMngmt));

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaRlyChannelCfgReq() ChannelId = (%d) LowProcId = (%d) HighProcId = (%d) Port = (%d) localPort = (%d) localProcId = (%d)  \n", channelId, srcProcId, dstProcId, port, localport, localProcId));

   cfg.hdr.msgType = TCFG;
   cfg.hdr.elmId.elmnt = STCHCFG;
   cfg.hdr.elmId.elmntInst1 = channelId;

   cfg.t.cfg.s.ryChanCfg.id = channelId; /* this must to be same as elmntInst1
                                            value filled inside header! */
   cfg.hdr.response.selector = LRY_SEL_LC;
   cfg.hdr.response.prior = 0;
   cfg.hdr.response.route = 0;
   cfg.hdr.response.mem.region = DFLT_REGION;
   cfg.hdr.response.mem.pool = DFLT_POOL;
   cfg.t.cfg.s.ryChanCfg.propErr = TRUE;
   cfg.t.cfg.s.ryChanCfg.low = dstProcId;
   cfg.t.cfg.s.ryChanCfg.high = dstProcId;
   cfg.t.cfg.s.ryChanCfg.strtAddr = NULLP; /* not used */
   cfg.t.cfg.s.ryChanCfg.nmbScanQ = 1;

   if (localport == 0)
      cfg.t.cfg.s.ryChanCfg.flags = LRY_FLG_INTR; /* intr mode for tx ch*/
   else
      cfg.t.cfg.s.ryChanCfg.flags = LRY_FLG_POLL; /* intr mode for listen ch*/

   cfg.t.cfg.s.ryChanCfg.congThrsh = 3;
   cfg.t.cfg.s.ryChanCfg.dropThrsh = 1;
   cfg.t.cfg.s.ryChanCfg.contThrsh = 4;
   cfg.t.cfg.s.ryChanCfg.kaTxTmr.enb = FALSE; /*for tx channel */
   cfg.t.cfg.s.ryChanCfg.kaTxTmr.val = 30;
   cfg.t.cfg.s.ryChanCfg.kaRxTmr.enb = FALSE; /*for tx channel */
   cfg.t.cfg.s.ryChanCfg.kaRxTmr.val = 150;
   if (localport == 0)
   {
      cfg.t.cfg.s.ryChanCfg.btTmr.enb = FALSE; /*for tx channel */
      cfg.t.cfg.s.ryChanCfg.btTmr.val = 600;
   }
   else
   {
      cfg.t.cfg.s.ryChanCfg.btTmr.enb = TRUE; /*for tx channel */
      cfg.t.cfg.s.ryChanCfg.btTmr.val = 600;
   }

   cfg.t.cfg.s.ryChanCfg.msInd = LRY_MS_MASTER;
#ifdef RY_SLAVE
   cfg.t.cfg.s.ryChanCfg.msInd = LRY_MS_SLAVE;
#endif /* RY_SLAVE */

   smPst.region = DFLT_REGION;             /* region */
   smPst.pool = DFLT_POOL;                 /* pool */
   smPst.prior = PRIOR0;                   /* priority */
   smPst.route = RTESPEC;                  /* route */
   smPst.dstProcId = localProcId;         /* destination processor id */
   smPst.dstEnt = ENTRY;                   /* destination entity */
   smPst.dstInst = TSTINST;                /* destination instance */
   smPst.srcProcId = localProcId;         /* source processor id */
   smPst.srcEnt = ENTSM;                   /* source entity */
   smPst.srcInst = TSTINST;                /* source instance */
   /* cm_xta_rlyutl_c_001.main_1: Changed the selector value. With the new
    * relay implementation, the selector value will be always zero as it
    * works with multi-threading and there is a separate thread which sends
    * back the CFM */
   smPst.selector = 0;                /* Selector value */

   /* now enter parameters to configure UDP socket transmit relay
      channel */
#ifdef RY_ENBUDPSOCK
   cfg.t.cfg.s.ryChanCfg.type = LRY_CT_USOCK;
   /* since tx channel is being configured, make listenportno=0 */
   cfg.t.cfg.s.ryChanCfg.listenPortNo = localport;
   cfg.t.cfg.s.ryChanCfg.transmittoPortNo = port;
   cfg.t.cfg.s.ryChanCfg.targetProcId = dstProcId;
   strcpy(&cfg.t.cfg.s.ryChanCfg.transmittoHostName[0],
         hostName);
#endif
   smPst.event = EVTLRYCFGREQ;   /* send event to config relay */
   SmMiLryCfgReq (&smPst, &cfg);          /* now send reqst to config
                                             this transmit channel */
   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaRlyChannelCfgReq*/


#ifdef OLD_RY
/*
 *
 *       Fun:    cmXtaRlyCfgCfm - configuration confirm
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
PUBLIC S16 cmXtaRlyCfgCfm
(
Pst         *pst,
RyMngmt     *cfg
)
#else
PUBLIC S16 cmXtaRlyCfgCfm (pst, cfg)
Pst         *pst;
RyMngmt     *cfg;
#endif /* ANSI */
{

   TRC3(cmXtaRlyCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaSmMiLshCfgCfm(): txnId(%ld)\n", cfg->hdr.transId));

   /*-- Update Event --*/
#if OLD_RY
   pst->event = EVTLRYCFGCFM;

   cmXtaLrySendMsg(pst, cfg, NULLP);
#endif

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaRlyCfgCfm() */


/*
 *
 *       Fun:    cmXtaLrySendMsg - trace indication
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
PUBLIC S16 cmXtaLrySendMsg
(
Pst         *pst,
RyMngmt     *cfm,
Buffer     *mBuf
)
#else
PUBLIC S16 cmXtaLrySendMsg(pst, cfm, mBuf)
Pst         *pst;
RyMngmt     *cfm;
Buffer     *mBuf;
#endif /* ANSI */
{
   Bool del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CmXtaFthaMsgQElm *ryMsg;

   TRC3(cmXtaUtlLrySendMsg)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLrySendMsg(): txnId(%ld)\n", cfm->hdr.transId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   del = TRUE;
   /*-- Do not delete the txn cb if it is partial confirmation --*/
#if OLD_RY
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      del = FALSE;
#endif

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
   {
      /*-- No associated test case found, spurious 
        message, drop it --*/
      CMXTA_DBG_INFO((_cmxtap, "cmXtaUtlLsgSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
#ifdef OLD_RY
   if ((tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);
#endif


   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLRYSTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLRYSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ( (tcCb->directives.capTrc == FALSE)))
   {
      CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLshSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
      /*-- Drop the message --*/

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate SIP memory data --*/
   ryMsg = NULLP;
   CMXTA_ALLOC(&ryMsg, sizeof (CmXtaFthaMsgQElm));
   if (ryMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaUtlLshSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }


   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
#if  0
   (Void) cmMemcpy((U8 *) &(ryMsg->u.ryMngmt), (U8 *)cfm, sizeof(RyMngmt));
   qElm.data = (Void *)ryMsg;
   qElm.msgFreeFun = cmXtaUtlLryCb;
#endif

   /*-- Test case found, queue the message for the tcCb --*/
   /*-- Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);

  
} /* end of cmXtaLrySendMsg() */
#endif

/*
*
*       Fun:   cmXtaUtlLryCb 
*
*       Desc:  This function is used to free the message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_xta_lsgcb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaUtlLryCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 cmXtaUtlLryCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CmXtaFthaMsgQElm  *ryMsg;

   TRC2(cmXtaUtlLryCb)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaUtlLsgCb(): \n"));

   ryMsg = (CmXtaFthaMsgQElm *)qElm->data;

   if (ryMsg != NULLP)
   {
      CMXTA_FREE(ryMsg, sizeof (CmXtaFthaMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of cmXtaUtlLryCb() */

#endif /*-- CM_XTA_RELAY --*/


/********************************************************************30**

         end of file:     cm_xta_rlyutl.c@@/main/1 - wed jun 27 16:21:27 2007

*********************************************************************31*/


/********************************************************************40**

        notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----      aj      1. main release
/main/2      ---      cm_xta_rlyutl_c_001.main_1 pka 1. Fix for integration testing.
*********************************************************************91*/

