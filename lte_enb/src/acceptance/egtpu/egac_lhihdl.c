
/********************************************************************20**

     Name:    eGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_lhihdl.c

     Sid:      egac_lhihdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:37 2015

     Prg:     an 

*********************************************************************21*/

/* header include files (.h) */
#include "cm_xta.h"
#include "egac_acc.x"
/*-- eg003.201 : changes from eg006.102: added "egac_lhi.x" --*/
#include "egac_lhi.x"
#include "cm_xta.x"

/* --------- Design -------------------------- */
/*  Request :-
    Step 1 :- Get the Post structure.
    Step 2 :- Fill the Data.
    Step 3 :- Get the Data from Test Case if required.
    Step 4 :- Create the transaction.
    Step 5 :- Call the API. 
*/
/*  Confirmation :-
    Step 1 :- Peek the message from Queue.
    Step 2 :- Get the Post structure.
    Step 3 :- Validate if the message is meant for test case.
    Step 4 :- If it is not for us, retrun with No Match. 
    Step 5 :- Else Validate the status.
*/



/*
*
*       Fun:   egAcHdlHiGenCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cfg;
   Pst      pst;
   Pst      lmPst;

   CmXtaTxnCb* txnCb; 
  
#if (defined(HI_TLS)  &&  !defined(HI_ACC_TLS_PRNG_FILE))
   S16          i;
   Random       rnd;
#endif
   ProcId         srcProcId;
   ProcId         dstProcId;


   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiGenCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.selector=1;/*temp change*/

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /* prepare the rest */
   cfg.t.cfg.s.hiGen.numSaps      = CMXTA_TUCL_MAX_TSAP;
   cfg.t.cfg.s.hiGen.numCons      = CMXTA_TUCL_MAX_CON;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numCons",  &(cfg.t.cfg.s.hiGen.numCons));

   #ifdef HI_REL_1_2
   cfg.t.cfg.s.hiGen.numFdsPerSet = CMXTA_TUCL_FDS;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numFdsPerSet",  &(cfg.t.cfg.s.hiGen.numFdsPerSet));
   cfg.t.cfg.s.hiGen.numFdBins    = CMXTA_TUCL_FDBINS;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numFdBins",  &(cfg.t.cfg.s.hiGen.numFdBins));
   #endif /* HI_REL_1_2 */

   #ifdef HI006_12
   cfg.t.cfg.s.hiGen.selTimeout = CMXTA_TUCL_SELTIMEOUT;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "selTimeout ",  &(cfg.t.cfg.s.hiGen.selTimeout));
   #ifdef HI_REL_1_3
   cfg.t.cfg.s.hiGen.numRawMsgsToRead = 0;
   #endif /* HI_REL_1_3 */

   cfg.t.cfg.s.hiGen.numUdpMsgsToRead = CMXTA_TUCL_UDP_MSGS_TOREAD;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numUdpMsgsToRead",  &(cfg.t.cfg.s.hiGen.numUdpMsgsToRead));

   cfg.t.cfg.s.hiGen.numClToAccept = CMXTA_TUCL_NUMCL_TOACCEPT;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numClToAccept",  &(cfg.t.cfg.s.hiGen.numClToAccept));
   #endif /* HI006_12 */

   /* If flag HI_MULTI_THREADED is used then permTsk has no significance*/
   cfg.t.cfg.s.hiGen.permTsk      = FALSE;
   cfg.t.cfg.s.hiGen.schdTmrVal   = 1;
   cfg.t.cfg.s.hiGen.poolStrtThr  = CMXTA_TUCL_STRT_THRESH;
   cfg.t.cfg.s.hiGen.poolDropThr  = CMXTA_TUCL_DRP_THRESH;
   cfg.t.cfg.s.hiGen.poolStopThr  = CMXTA_TUCL_STP_THRESH;
   /* timer resolution unused */
   cfg.t.cfg.s.hiGen.timeRes      = 0;

#ifdef HI_TLS
   cfg.t.cfg.s.hiGen.initOpenSSL = TRUE;
   cfg.t.cfg.s.hiGen.numContexts = 2;
#ifdef HI_ACC_TLS_PRNG_FILE
   cfg.t.cfg.s.hiGen.prng.option = LHI_OSSL_PRNG_FILE;
   cmMemcpy((U8 *)cfg.t.cfg.s.hiGen.prng.u.file, (U8 *)"/dev/urandom", 13);
#else
   cfg.t.cfg.s.hiGen.prng.option =  LHI_OSSL_PRNG_SEED;
   for (i = 0;  i < LHI_OSSL_PRNG_SEED_LEN;  i++)
   {
      SRandom(&rnd);
      cfg.t.cfg.s.hiGen.prng.u.seed[i] = (U8)rnd;
   }
#endif /* HI_ACC_TLS_PRNG_FILE */
#endif

   /*Get the LmPst*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
    cmXtaGetPst(&lmPst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID , srcProcId, dstProcId, FALSE);

   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(cfg.t.cfg.s.hiGen.lmPst),
            (U8 *) &(lmPst),
            (PTR) sizeof(Pst));

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL General Configuration request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiGenCfgReq */


/*
*
*       Fun:   egAcHdlHiTSapCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiTSapCfgReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiTSapCfgReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cfg;
   Pst      pst;
   Pst      entPst;
   S16      tmpUiSel;
   ProcId   srcProcId;
   ProcId   dstProcId;

   CmXtaTxnCb* txnCb; 

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiTSapCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /* set the rest of the parameters */
   cfg.t.cfg.s.hiSap.flcEnb          = FALSE;
   cfg.t.cfg.s.hiSap.txqCongStrtLim  = CMXTA_TUCL_CONG_STRT;
   cfg.t.cfg.s.hiSap.txqCongDropLim  = CMXTA_TUCL_CONG_DRP;
   cfg.t.cfg.s.hiSap.txqCongStopLim  = CMXTA_TUCL_CONG_STP;
   cfg.t.cfg.s.hiSap.numBins         = CMXTA_TUCL_NMB_HLBINS;

   /*-- Get the Entity from Test Case --*/
   tmpUiSel = ENTEG;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "entity",  &(tmpUiSel));
   switch(tmpUiSel)
   {
      case ENTEG:
         /*-- Get the Pst information here --*/
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
         cmXtaGetPst(&entPst, ENTHI, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
         break;
      case ENTSB:
         /*-- Get the Pst information here --*/
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
         cmXtaGetPst(&entPst, ENTHI, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
         break;
      case ENTEU:
         /*-- Get the Pst information here --*/
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
         cmXtaGetPst(&entPst, ENTHI, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
         break;
      default:
         /*-- Get the Pst information here --*/
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
         cmXtaGetPst(&entPst, ENTHI, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
         break;
   }

   /*Get the proper value for this.*/
   cfg.t.cfg.s.hiSap.uiSel  = entPst.selector;

   cfg.t.cfg.s.hiSap.uiMemId.region = CMXTA_TSTREG;     /* region */
   cfg.t.cfg.s.hiSap.uiMemId.pool   = CMXTA_TSTPOOL;    /* pool */
   cfg.t.cfg.s.hiSap.uiPrior        = PRIOR0;            /* default priority */
   cfg.t.cfg.s.hiSap.uiRoute        = RTESPEC;           /* default route */

   if(tmpUiSel == ENTSB)
      cfg.t.cfg.s.hiSap.uiRoute        = RTESPEC;           /* default route */
   cfg.t.cfg.s.hiSap.hdrInf[0].hdrLen = 20;
   cfg.t.cfg.s.hiSap.hdrInf[0].offLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].lenLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].flag   = 0;

   /* profile_2 : srvcType value = 4 (LDP header format) */
   cfg.t.cfg.s.hiSap.hdrInf[1].hdrLen = 10;
   cfg.t.cfg.s.hiSap.hdrInf[1].offLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[1].lenLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[1].flag   = 0;

   /* these parameters are dependant on the TSAP being configured */
   cfg.t.cfg.s.hiSap.spId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
     using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "tSapId",  &(cfg.t.cfg.s.hiSap.spId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the TUCL */
   /* give configuration request to layer */
#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,"Sending TUCL TSAP CfgReq for spid(%d) transId(%u)\n",
                cfg.t.cfg.s.hiSap.spId, cfg.hdr.transId));
#else
   CMXTA_DBG_INFO((_cmxtap,"Sending TUCL TSAP CfgReq for spid(%d) transId(%lu)\n",
                cfg.t.cfg.s.hiSap.spId, cfg.hdr.transId));
#endif
#endif

   (Void) SmMiLhiCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiTSapCfgReq */


/*
*
*       Fun:   egAcHdlHiCtxtCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiCtxtCfgReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiCtxtCfgReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
#ifdef HI_TLS   
   HiMngmt     cfg;
   HiCtxCfg    *cc;
   ProcId      srcProcId;
   ProcId      dstProcId;
   
   Pst      pst;
   CmXtaTxnCb* txnCb;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiCtxtCfgReq)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiCtxtCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiCtxtCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cc = &cfg.t.cfg.s.hiCtx;
   cc->ctxId = 0;
   cc->caPath[0] = '\0';
   cmMemcpy((U8 *)cc->caFile, (U8 *)CMXTA_HI_ACC_TLSSERVER_CAFILE, 37);
   cmMemcpy((U8 *)cc->certFile, (U8 *)CMXTA_HI_ACC_TLSSERVER_CERTFILE, 35);
   cmMemcpy((U8 *)cc->privKeyFile, (U8 *)CMXTA_HI_ACC_TLSSERVER_PRIVKEYFILE, 35);
   cc->privKeyFileType = SSL_FILETYPE_PEM;
   cc->verifyMode = SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
   cmMemcpy((U8 *)cc->ciphers, (U8 *)"ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH", 34);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STCTX, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the TUCL */
   (Void) SmMiLhiCfgReq(&pst, &cfg);
#else
   CMXTA_DBG_ERR((_cmxtap, " Enable the Flag HI_TLS before using this command\n"));
   CMXTA_DBG_CALLIND((_cmxtap, "Failed : Enable Flag HI_TLS\n"), 3);
   RETVALUE(CMXTA_ERR_INT);
#endif /* HI_TLS*/

#ifdef HI_TLS   
   RETVALUE(CMXTA_ERR_NONE);
#endif
}/* egAcHdlHiCtxtCfgReq */

/*
*
*       Fun:   egAcHdlHiCfgCfm
*
*       Desc:  Call handler for configuration confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm  *egtpMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   ProcId   srcProcId;
   ProcId   dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiCfgCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiCfgCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = EVTLHICFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlHiCfgCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   if (ROK!=cmXtaPopMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egtpMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHiCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiCfgCfm*/


/*
*
*       Fun:   egAcHdlHiUstaCntrlReq
*
*       Desc:  Call handler for Control Request for Unsolicited Status  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiUstaCntrlReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiUstaCntrlReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiUstaCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiUstaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiUstaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ADISIMM;
   cntrl.t.cntrl.subAction = SAUSTA;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask > CMXTA_DBGLEVEL_HI)
   {
      cntrl.t.cntrl.action = AENA;
   }
#endif /*-- DEBUGP --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the TUCL */
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL Usta Control request\n"));

   (Void) SmMiLhiCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiUstaCntrlReq */


/*
*
*       Fun:   egAcHdlHiTrcCntrlReq
*
*       Desc:  Call handler for Control Request for Unsolicited Trace  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiTrcCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiTrcCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = AUBND_DIS;
   cntrl.t.cntrl.subAction = SATRC;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask > CMXTA_DBGLEVEL_HI)
   {
      cntrl.t.cntrl.action = AENA;
   }
#endif /*-- DEBUGP --*/

   /* Fill the Trace Data*/
   cntrl.t.cntrl.ctlType.trcDat.trcLen = (S16)-1; /* Complete PDU is copied in Trace Buffer*/
   cntrl.t.cntrl.ctlType.trcDat.sapId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "tSapId",  &(cntrl.t.cntrl.ctlType.trcDat.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL Trace Control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiTrcCntrlReq */


/*
*
*       Fun:   egAcHdlHiDbgCntrlReq
*
*       Desc:  Call handler for Control Request for Unsolicited Trace  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiDbgCntrlReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiDbgCntrlReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiDbgCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiDbgCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiDbgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ADISIMM;
   cntrl.t.cntrl.subAction = SADBG;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask > CMXTA_DBGLEVEL_HI)
   {
      cntrl.t.cntrl.action = AENA;
   }

   /* Fill the Debug Data*/
   cntrl.t.cntrl.ctlType.hiDbg.dbgMask = (U32)(DBGMASK_SI|DBGMASK_MI|DBGMASK_UI);

#endif /*-- DEBUGP --*/
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL Debug Control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiDbgCntrlReq */

/*
*
*       Fun:   egAcHdlHiShutDownCntrlReq
*
*       Desc:  Call handler for Control Request for Shutdown 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiShutDownCntrlReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiShutDownCntrlReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiShutDownCntrlReq)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiShutDownCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiShutDownCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ASHUTDOWN;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the TUCL */
   (Void) SmMiLhiCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiShutDownCntrlReq */


/*
*
*       Fun:   egAcHdlHiTsapCntrlReq
*
*       Desc:  Call handler for Control Request for Shutdown 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiTsapCntrlReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiTsapCntrlReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
   ProcId      srcProcId;
   ProcId      dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiTsapCntrlReq)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTsapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTsapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ADEL;
   cntrl.t.cntrl.subAction = SAELMNT;

   /* Get the proper value for SAPID*/
   cntrl.t.cntrl.ctlType.sapId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "tSapId",  &(cntrl.t.cntrl.ctlType.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the TUCL */
   (Void) SmMiLhiCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiTsapCntrlReq */


/*
*
*       Fun:   egAcHdlHiCntrlCfm
*
*       Desc:  Call handler for configuration confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiCntrlCfm
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiCntrlCfm(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm  *egtpMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   ProcId         srcProcId;
   ProcId         dstProcId;
   
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiCntrlCfm)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   pst.event = EVTLHICNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlHiCntrlCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   if (ROK!=cmXtaPopMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
  
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egtpMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHiCntrlCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiCntrlCfm*/

/*
*
*       Fun:   egAcHdlHiTrcInd
*
*       Desc:  Call handler for Trace Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiTrcInd
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiTrcInd(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst      pst;
   S16      ret;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiTrcInd)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTrcInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTrcInd(): tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = EVTLHITRCIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTrcInd(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   if (ROK!=cmXtaPopMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/* egAcHdlHiTrcInd()*/


/*
*
*       Fun:   egAcHdlHiStaInd
*
*       Desc:  Call handler for Status Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst      pst;
   S16      ret;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiStaInd)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiStaInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = EVTLHISTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlHiStaInd(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   if (ROK!=cmXtaPopMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/* egAcHdlHiStaInd()*/

/*
*
*       Fun:   egAcHdlHiSysStaReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiSysStaReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiSysStaReq(tcCb,spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  ssta;
   Pst      pst;

   ProcId         srcProcId;
   ProcId         dstProcId;
   CmXtaTxnCb* txnCb; 

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiSysStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiSysStaReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiSysStaReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*   Design:- Here no data is needed to be filled*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHiSysStaReq() : Failed to create transaction\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STSID, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL System Status Request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiSysStaReq */

/*
*
*       Fun:   egAcHdlHiTsapStaReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiTsapStaReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiTsapStaReq(tcCb,spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  ssta;
   Pst      pst;
   CmXtaTxnCb* txnCb; 
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiTsapStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTsapStaReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTsapStaReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ssta.t.ssta.s.sapSta.spId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "tSapId",  &(ssta.t.ssta.s.sapSta.spId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHiTsapStaReq() : Failed to create transaction\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL TSAP Status Request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiTsapStaReq */

/*
*
*       Fun:   egAcHdlHiStaCfm
*
*       Desc:  Call handler for configuration confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm  *egtpMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiStaCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiStaCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiStaCfm(): tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   pst.event = EVTLHISTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlHiStaCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   if (ROK!=cmXtaPopMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egtpMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHiStaCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiStaCfm*/


/*
*
*       Fun:   egAcHdlHiGenStsReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiGenStsReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiGenStsReq(tcCb,spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  sts;
   Pst      pst;
   Action action;
   ProcId         srcProcId;
   ProcId         dstProcId;

   CmXtaTxnCb* txnCb; 

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiGenStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiGenStsReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiGenStsReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL General Statistics Request\n"));

   action = 0;
   /* Send the request to the TUCL */
   (Void) SmMiLhiStsReq(&pst, action, &sts);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiGenStsReq */

/*
*
*       Fun:   egAcHdlHiTsapStsReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiTsapStsReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiTsapStsReq(tcCb,spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  sts;
   Pst      pst;
   Action action;
   ProcId   srcProcId;
   ProcId   dstProcId;

   CmXtaTxnCb* txnCb; 

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiTsapStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTsapStsReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiTsapStsReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    sts.t.sts.s.sapSts.sapId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "tSapId",  &(sts.t.sts.s.sapSts.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL TSAP Statistics Request\n"));

   action = 0;
   /* Send the request to the TUCL */
   (Void) SmMiLhiStsReq(&pst, action, &sts);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiTsapStsReq */

/*
*
*       Fun:   egAcHdlHiStsCfm
*
*       Desc:  Call handler for configuration confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHiStsCfm
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlHiStsCfm(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm  *egtpMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlHiStsCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiStsCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHiStsCfm(): tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = EVTLHISTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlHiStsCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   if (ROK!=cmXtaPopMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egtpMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHiStsCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlHiStsCfm*/


/********************************************************************30**

         End of file:     egac_lhihdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:37 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3    eg003.201  psingh      1. Merged code from eg006.102 to Fix TRACE5
                                     macro related issue
                                  2. Fixed warnings
*********************************************************************91*/
