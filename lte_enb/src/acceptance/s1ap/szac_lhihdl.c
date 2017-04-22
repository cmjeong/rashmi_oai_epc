/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    szac_lhihdl.c

     Sid:      szac_lhihdl.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:23 2013

     Prg:     sn 
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
#include "sz_err.h"        /* S1AP error defines */
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
#include "lsz.x"           /* S1AP types */

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


/*  Confirmation :-
    Step 1 :- Peek the message from Queue.
    Step 2 :- Get the Post structure.
    Step 3 :- Validate if the message is meant for test case.
    Step 4 :- If it is not for us, return with No Match. 
    Step 5 :- Else Validate the status.
*/



/*
*
*       Fun:   szAcHdlHiGenCfgReq
*
*       Desc:  Call handler for Command General configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cfg;
   Pst      pst;
   Pst      lmPst;

   CmXtaTxnCb* txnCb = NULLP; 
  
#if (defined(HI_TLS)  &&  !defined(HI_ACC_TLS_PRNG_FILE))
   S16          i;
   Random       rnd;
#endif


   TRC2(szAcHdlHiGenCfgReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /* prepare the rest */
   cfg.t.cfg.s.hiGen.numSaps      = CMXTA_TUCL_MAX_TSAP;
   cfg.t.cfg.s.hiGen.numCons      = 10;

   cfg.t.cfg.s.hiGen.numFdsPerSet = CMXTA_TUCL_FDS;
   cfg.t.cfg.s.hiGen.numFdBins    = CMXTA_TUCL_FDBINS;

/* removed the flags here - vsr */
#ifdef HI006_12
   cfg.t.cfg.s.hiGen.selTimeout = CMXTA_TUCL_SELTIMEOUT;
   cfg.t.cfg.s.hiGen.numRawMsgsToRead = 0;

   cfg.t.cfg.s.hiGen.numUdpMsgsToRead = CMXTA_TUCL_UDP_MSGS_TOREAD;

   cfg.t.cfg.s.hiGen.numClToAccept = CMXTA_TUCL_NUMCL_TOACCEPT;
#endif

#if (defined(HI_LKSCTP) && defined(SZAC_LKSCTP))
   cfg.t.cfg.s.hiGen.numAssocBins   =  5;
   cfg.t.cfg.s.hiGen.maxInitReTx    =  5; 
   cfg.t.cfg.s.hiGen.maxAssocReTx   =  8;
   cfg.t.cfg.s.hiGen.maxPathReTx    =  4; 
#endif
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

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &lmPst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "selector", &lmPst.selector);

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
}/* szAcHdlHiGenCfgReq */


/*
*
*       Fun:   szAcHdlHiTSapCfgReq
*
*       Desc:  Call handler for Transport SAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiTSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiTSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cfg;
   Pst      pst;
   Pst      entPst;
   S16      tmpUiSel = 0;

   CmXtaTxnCb* txnCb = NULLP; 

   TRC2(szAcHdlHiTSapCfgReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /* set the rest of the parameters */
   cfg.t.cfg.s.hiSap.flcEnb          = FALSE;
   cfg.t.cfg.s.hiSap.txqCongStrtLim  = CMXTA_TUCL_CONG_STRT;
   cfg.t.cfg.s.hiSap.txqCongDropLim  = CMXTA_TUCL_CONG_DRP;
   cfg.t.cfg.s.hiSap.txqCongStopLim  = CMXTA_TUCL_CONG_STP;
   cfg.t.cfg.s.hiSap.numBins         = CMXTA_TUCL_NMB_HLBINS;

   tmpUiSel = ENTSB;
#ifdef SZAC_LKSCTP
   tmpUiSel =  ENTSZ;
#endif

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "entity",  &(tmpUiSel));
   switch(tmpUiSel)
   {
      case ENTSB:
      {
         /*-- Get the Pst information here --*/
         szAcGetPst(spCb, &entPst, ENTHI, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);
         break;
      }

      default:
      {
         /*-- Get the Pst information here --*/
         szAcGetPst(spCb, &entPst, ENTHI, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
         break;
      }
   }/* End of Switch  */

   /*Get the proper value for this.*/
   cfg.t.cfg.s.hiSap.uiSel  = entPst.selector;

   cfg.t.cfg.s.hiSap.uiMemId.region = CMXTA_TSTREG;     /* region */
   cfg.t.cfg.s.hiSap.uiMemId.pool   = CMXTA_TSTPOOL;    /* pool */
   cfg.t.cfg.s.hiSap.uiPrior        = PRIOR0;            /* default priority */
   cfg.t.cfg.s.hiSap.uiRoute        = RTESPEC;           /* default route */

   /* profile_1 : srvcType value = 3 (GTP header format) */
   cfg.t.cfg.s.hiSap.hdrInf[0].hdrLen = 20;
   cfg.t.cfg.s.hiSap.hdrInf[0].offLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].lenLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].flag   = 0;

   /* profile_2 : srvcType value = 4 (LDP header format) */
   cfg.t.cfg.s.hiSap.hdrInf[1].hdrLen = 10;
   cfg.t.cfg.s.hiSap.hdrInf[1].offLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[1].lenLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[1].flag   = 0;

#if (defined(HI_LKSCTP) && defined(SZAC_LKSCTP))
   cfg.t.cfg.s.hiSap.type = HI_SCT_SAP;        
#endif

   /* these parameters are dependant on the TSAP being configured */
   cfg.t.cfg.s.hiSap.spId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
     using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "tSapId",  &(cfg.t.cfg.s.hiSap.spId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8 , "selector",  &(cfg.t.cfg.s.hiSap.uiSel));

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
#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,"Sending TUCL TSAP CfgReq for spid(%d) transId(%ld)\n",
                cfg.t.cfg.s.hiSap.spId, cfg.hdr.transId));
#else
   CMXTA_DBG_INFO((_cmxtap,"Sending TUCL TSAP CfgReq for spid(%d) transId(%d)\n",
                cfg.t.cfg.s.hiSap.spId, cfg.hdr.transId));
#endif

   (Void) SmMiLhiCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiTSapCfgReq */


/*
*
*       Fun:   szAcHdlHiCtxtCfgReq
*
*       Desc:  Call handler for Context Configuration Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlHiCtxtCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiCtxtCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
#ifdef HI_TLS   
   HiMngmt     cfg;
   HiCtxCfg    *cc = NULLP;
   
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   U32      tmpU32 = 0;
   U8       modeListCnt = 0;
   U32      modeList[5] = {0};
   U32      idx = 0;
   Txt      tmpcaFile[LHI_OSSL_PATHLEN];
   Txt      tmpcaPath[LHI_OSSL_PATHLEN];
   Txt      tmpcertFile[LHI_OSSL_PATHLEN];
   Txt      tmpprivKeyFile[LHI_OSSL_PATHLEN];
   S16      ctxId = 0;
#if (defined (HI_VERIFY_DEPTH) || defined (HI_TLS_METHOD))
   U8       tmpU8 = 0;
#endif
   S16      ret = 0;

   TRC2(szAcHdlHiCtxtCfgReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiCtxtCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiCtxtCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(tmpcaFile, LHI_OSSL_PATHLEN);
   CMXTA_ZERO(tmpcaPath, LHI_OSSL_PATHLEN);
   CMXTA_ZERO(tmpcertFile, LHI_OSSL_PATHLEN);
   CMXTA_ZERO(tmpprivKeyFile, LHI_OSSL_PATHLEN);
   CMXTA_ZERO(modeList, 5);


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cc = &cfg.t.cfg.s.hiCtx;
   cc->ctxId = 0;
   cc->caPath[0] = '\0';
   cmMemcpy((U8 *)cc->caFile, (U8 *)CMXTA_HI_ACC_TLSSERVER_CAFILE, 13);
   cmMemcpy((U8 *)cc->certFile, (U8 *)CMXTA_HI_ACC_TLSSERVER_CERTFILE, 11);
   cmMemcpy((U8 *)cc->privKeyFile, (U8 *)CMXTA_HI_ACC_TLSSERVER_PRIVKEYFILE, 11);
   cc->privKeyFileType = SSL_FILETYPE_PEM;
   cc->verifyMode = SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
   cmMemcpy((U8 *)cc->ciphers, (U8 *)"ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH", 34);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "ctxId", &ctxId);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the privKeyFileType is present in the xml file */
   {
      cc->ctxId = ctxId;
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_TXT, "caFile",  tmpcaFile);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the caFile is present in the xml file */
   {
      szStrcpy( (S8 *)(cc->caFile),(S8 *)tmpcaFile); 
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_TXT, "caPath",  tmpcaPath);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the caPath is present in the xml file */
   {
      szStrcpy( (S8 *)(cc->caPath),(S8 *)tmpcaPath); 
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_TXT, "certFile",  tmpcertFile);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the certFile is present in the xml file */
   {
      szStrcpy( (S8 *)(cc->certFile),(S8 *)tmpcertFile); 
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_TXT, "privKeyFile",  tmpprivKeyFile);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the privKeyFile is present in the xml file */
   {
      aqStrcpy( (S8 *)(cc->privKeyFile),(S8 *)tmpprivKeyFile); 
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "privKeyFileType", &tmpU32);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the privKeyFileType is present in the xml file */
   {
      cc->privKeyFileType = tmpU32;
   }

   tmpU32 = 0;
   
   /* There can be multiple verify mode parameters possible  */ 
   ret = cmXtaXmlGetValList(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U32,CMXTA_SEP_COLON, "verifyMode",  modeList, &modeListCnt);
   if( ret != CMXTA_ERR_NO_VALUE) /* if the verifyMode is present in the xml file */
   {
      for(idx=0;idx<modeListCnt;idx++)
      {
         tmpU32 |= modeList[idx];
      }
      cc->verifyMode = tmpU32;
   } /* end of if statement  */

#ifdef HI_TLS_METHOD
   cc->method = HI_TLS_SSLV3_METHOD;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "method", &tmpU8);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the method is present in the xml file */
   {
      cc->method = tmpU8;
   }
#endif

#ifdef HI_VERIFY_DEPTH
   tmpU8 = 0;
   cc->verifyDepth = 5;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "verifyDepth", &tmpU8);
   
   if( ret != CMXTA_ERR_NO_VALUE) /* if the verify depth is present in the xml file */
   {
      cc->verifyDepth = tmpU8;
   }
#endif

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
   RETVALUE(CMXTA_ERR_NONE);
#else
   CMXTA_DBG_ERR((_cmxtap, " Enable the Flag HI_TLS before using this command\n"));
   RETVALUE(CMXTA_ERR_INT);
#endif /* HI_TLS*/

}/* szAcHdlHiCtxtCfgReq */

/*
*
*       Fun:   szAcHdlHiCfgCfm
*
*       Desc:  Call handler for configuration confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg = NULLP;
   SzAccMsgQElm   *szMsg = NULLP;
   CmStatus       status;
   Pst      pst;
   S16      ret = 0;

   cmMemset((U8*)&status, 0 , sizeof(CmStatus));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   
   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLHICFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlHiCfgCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlHiCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiCfgCfm*/


/*
*
*       Fun:   szAcHdlHiUstaCntrlReq
*
*       Desc:  Call handler for Control Request for Unsolicited Status  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlHiUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiUstaCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;

   TRC2(szAcHdlHiUstaCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiUstaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiUstaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ADISIMM;
   cntrl.t.cntrl.subAction = SAUSTA;

   /* Check if TA wants to enable all traces etc*/
   if ( cmXtaCb.dbgMask > SZAC_HI_DBG)
   {
      cntrl.t.cntrl.action = AENA;
   }

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));

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
}/* szAcHdlHiUstaCntrlReq */


/*
*
*       Fun:   szAcHdlHiTrcCntrlReq
*
*       Desc:  Call handler for Control Request for Unsolicited Trace  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiTrcCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;

   TRC2(szAcHdlHiTrcCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = AUBND_DIS;
   cntrl.t.cntrl.subAction = SATRC;

   /* Check if TA wants to enable all traces etc*/
   if ( cmXtaCb.dbgMask > SZAC_HI_DBG)
   {
      cntrl.t.cntrl.action = AENA;
   }

   /* Fill the Trace Data*/
   cntrl.t.cntrl.ctlType.trcDat.trcLen = (S16)-1; /* Complete PDU is copied in Trace Buffer*/
   cntrl.t.cntrl.ctlType.trcDat.sapId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "tSapId",  &(cntrl.t.cntrl.ctlType.trcDat.sapId));

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
}/* szAcHdlHiTrcCntrlReq */


/*
*
*       Fun:   szAcHdlHiDbgCntrlReq
*
*       Desc:  Call handler for Control Request for Debug 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiDbgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiDbgCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;

   TRC2(szAcHdlHiDbgCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiDbgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiDbgCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ADISIMM;
   cntrl.t.cntrl.subAction = SADBG;

   /* Check if TA wants to enable all traces etc*/
   if ( cmXtaCb.dbgMask > SZAC_HI_DBG)
   {
      cntrl.t.cntrl.action = AENA;
   }

   /* Fill the Debug Data*/
#ifdef DEBUGP
   cntrl.t.cntrl.ctlType.hiDbg.dbgMask = (U32)(DBGMASK_SI|DBGMASK_MI|DBGMASK_UI);
#endif

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));

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
}/* szAcHdlHiDbgCntrlReq */

/*
*
*       Fun:   szAcHdlHiShutDownCntrlReq
*
*       Desc:  Call handler for Control Request for Shutdown 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlHiShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiShutDownCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;

   TRC2(szAcHdlHiShutDownCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiShutDownCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiShutDownCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

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
}/* szAcHdlHiShutDownCntrlReq */


/*
*
*       Fun:   szAcHdlHiTsapCntrlReq
*
*       Desc:  Call handler for Control Request for Transport SAP 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiTsapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiTsapCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;

   TRC2(szAcHdlHiTsapCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTsapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTsapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.t.cntrl.action = ADEL;
   cntrl.t.cntrl.subAction = SAELMNT;

   /* Get the proper value for SAPID*/
   cntrl.t.cntrl.ctlType.sapId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cntrl.t.cntrl.action));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "tSapId",  &(cntrl.t.cntrl.ctlType.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the TUCL */
   (Void) SmMiLhiCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiTsapCntrlReq */


/*
*
*       Fun:   szAcHdlHiCntrlCfm
*
*       Desc:  Call handler for Control confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiCntrlCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;

   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLHICNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlHiCntrlCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
  
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlHiCntrlCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiCntrlCfm*/

/*
*
*       Fun:   szAcHdlHiTrcInd
*
*       Desc:  Call handler for Trace Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiTrcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLHITRCIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTrcInd(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/* szAcHdlHiTrcInd()*/


/*
*
*       Fun:   szAcHdlHiStaInd
*
*       Desc:  Call handler for Status Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiStaInd(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLHISTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlHiStaInd(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/* szAcHdlHiStaInd()*/

/*
*
*       Fun:   szAcHdlHiSysStaReq
*
*       Desc:  Call handler for System Status Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiSysStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiSysStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  ssta;
   Pst      pst;

   CmXtaTxnCb* txnCb; 

   TRC2(szAcHdlHiSysStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiSysStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiSysStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*   Design:- Here no data is needed to be filled*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlHiSysStaReq() : Failed to create transaction\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STSID, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL System Status Request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiSysStaReq */

/*
*
*       Fun:   szAcHdlHiTsapStaReq
*
*       Desc:  Call handler for TSap Status Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiTsapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiTsapStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  ssta;
   Pst      pst;
   CmXtaTxnCb* txnCb; 

   TRC2(szAcHdlHiTsapStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTsapStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTsapStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ssta.t.ssta.s.sapSta.spId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "tSapId",  &(ssta.t.ssta.s.sapSta.spId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlHiTsapStaReq() : Failed to create transaction\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL TSAP Status Request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiTsapStaReq */

/*
*
*       Fun:   szAcHdlHiStaCfm
*
*       Desc:  Call handler for Status confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;

   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLHISTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlHiStaCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlHiStaCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiStaCfm*/


/*
*
*       Fun:   szAcHdlHiGenStsReq
*
*       Desc:  Call handler for General Statistics Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiGenStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiGenStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  sts;
   Pst      pst;
   Action   action = 0;

   CmXtaTxnCb* txnCb; 

   TRC2(szAcHdlHiGenStsReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiGenStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiGenStsReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

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

   /* Send the request to the TUCL */
   (Void) SmMiLhiStsReq(&pst, action, &sts);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiGenStsReq */

/*
*
*       Fun:   szAcHdlHiTsapStsReq
*
*       Desc:  Call handler for Tsap Statistics Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiTsapStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiTsapStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   HiMngmt  sts;
   Pst      pst;
   Action action = 0;

   CmXtaTxnCb* txnCb; 

   TRC2(szAcHdlHiTsapStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTsapStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiTsapStsReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(HiMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
    szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    sts.t.sts.s.sapSts.sapId = 0;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "tSapId",  &(sts.t.sts.s.sapSts.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTHI, CMXTA_INST_ID, STTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TUCL TSAP Statistics Request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLhiStsReq(&pst, action, &sts);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiTsapStsReq */

/*
*
*       Fun:   szAcHdlHiStsCfm
*
*       Desc:  Call handler for Statistics confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lhihdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlHiStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlHiStsCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlHiStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTHI, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLHISTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlHiStsCfm(): No Match\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.hiMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlHiStsCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlHiStsCfm*/


/********************************************************************30**

         End of file:     szac_lhihdl.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:23 2013

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
