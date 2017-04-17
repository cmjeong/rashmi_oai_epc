
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      szac_lszhdl.c@@/main/4 - Mon Jan 10 22:15:53 2011

     Prg:     mn
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
#include "lsz.h"           /* layer management defines for SZCP */
#include "sz.h"            /* defines and macros for SZ */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "szt.h"            /* defines and macros for SZ */
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for SZ acceptance tests */

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
#include "szt.x"           /* SZT Interface Structures */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for SZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "sb.x"
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x" 
#include "sz.x"            /* typedefs for SZCP */
#include "szac_acc.x"        /* typedefs for SZCP acceptance tests */
#include "szac_lsz.x"

/*
*
*       Fun:   szAcHdlGenCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cfg;
   Pst      pst;

   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(szAcHdlGenCfgReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildGenCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZGEN, pst.selector);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "element", &(cfg.hdr.elmId.elmnt));
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));
 
 
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* szAcHdlGenCfgReq */
 
/*
*
*       Fun:   szAcHdlUSapCfgReq
*
*       Desc:  Call handler for SSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlUSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlUSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlUSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlUSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlUSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildUSapCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZSZTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending GCP SSAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* szAcHdlUSapCfgReq */
 
 
 
/*
*
*       Fun:   szAcHdlLSapCfgReq
*
*       Desc:  Call handler for TSAP Cfg Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlLSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlLSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlLSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlLSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlLSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildLSapCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZSCTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TSAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* szAcHdlLSapCfgReq */
 

/*
*
*       Fun:   szAcHdlProtCfgReq
*
*       Desc:  Call handler for Protocol Configuration Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlProtCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlProtCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   Bool tightCoupled = FALSE;
 
   TRC2(szAcHdlProtCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlProtCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlProtCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
  
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
 
   szAcUtlBuildProtCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZPROT,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending S1AP Protocol Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* szAcHdlProtCfgReq */


/*
*
*       Fun:   szAcHdlPeerCfgReq
*
*       Desc:  Call handler for Transort Server Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlPeerCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlPeerCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cfg;
   Pst      pst;
 
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlPeerCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlPeerCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlPeerCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
 
   szAcUtlBuildPeerCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZPEER,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending S1AP PEER Configuration request\n"));
 
 
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* szAcHdlPeerCfgReq */

/*
*
*       Fun:   szAcHdlCfgCfm
*
*       Desc:  Call handler for configuration conformation 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlCfgCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
 
   pst.event = EVTLSZCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.szMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlCfgCfm */

/*  
*
*       Fun:   szAcHdlStsReq
*
*       Desc:  Call handler for  Statistics Request 
*   
*       Ret:   ROK
*  
*       Notes: None
*              
*       File:  szac_lszhdl.c
*  
*/ 
#ifdef ANSI
PUBLIC S16 szAcHdlStsReq
(  
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   U8 stsType;
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(szAcHdlStsReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStsReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStsReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&sts, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
 
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   action = NOZEROSTS;
   stsType  =  STSZGEN;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &action);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "actionErr",  &action);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"stsType",&stsType);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }

   if(stsType == STSZPEER)
   {
      sts.u.sts.u.node.peerId.pres = TRUE;
      sts.u.sts.u.node.peerId.val = 0;
    
      /*-- Use Python wrapper APIs to extract the parameters which can be changed
           using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  
                                       &(sts.u.sts.u.node.peerId.val));
   } 
  /* sz001.201 Added SCT SAP level statistics */
  else if(stsType == STSZSCTSAP)
   {
      sts.u.sts.u.sctSap.suId  = 0;
    
      /*-- Use Python wrapper APIs to extract the parameters which can be changed
           using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  
                                       &(sts.u.sts.u.sctSap.suId));
   } 
    
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, stsType, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszStsReq(&pst, action, &sts);
 
   RETVALUE(ROK);
}/* szAcHdlStsReq */

/*
*
*       Fun:   szAcHdlStsCfm
*
*       Desc:  Call handler for Statistics Confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Bool     checkGenSts = FALSE;
   Bool     checkPeerSts = FALSE;
   Bool     checkErrSts = FALSE;
   /* sz001.201 Added SCT SAP level statistics */
   Bool     checkSctSapSts = FALSE;
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStsCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStsCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

 
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLSZSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.szMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkPeerSts", &checkPeerSts);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkSctSapSts", &checkSctSapSts);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkErrSts", &checkErrSts);

   if ((checkPeerSts == TRUE) || (checkSctSapSts == TRUE) || (checkErrSts == TRUE))
   {
      SzSts          sts;
      Bool           checkPduSts = FALSE;

      CMXTA_ZERO(&sts, sizeof(SzSts));

      if (checkSctSapSts == TRUE)
      {
         SzSctSapSts  *chkSts, *rcvSts;

         chkSts =  &sts.u.sctSap;
         rcvSts =  &szMsg->u.szMngmt.u.sts.u.sctSap;

         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szDedProcSts.tx", &chkSts->cfm.szDedProcSts.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szDedProcSts.rx", &chkSts->cfm.szDedProcSts.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szComProcSts.tx", &chkSts->cfm.szComProcSts.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szComProcSts.rx", &chkSts->cfm.szComProcSts.rx);

         if((rcvSts->cfm.szDedProcSts.tx   != chkSts->cfm.szDedProcSts.tx)  ||
            (rcvSts->cfm.szDedProcSts.rx   != chkSts->cfm.szDedProcSts.rx)  ||
            (rcvSts->cfm.szComProcSts.tx   != chkSts->cfm.szComProcSts.tx)  ||
            (rcvSts->cfm.szComProcSts.rx   != chkSts->cfm.szComProcSts.rx))
         {
            CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : Statistics mismatch\n"));
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      else if (checkPeerSts == TRUE)
      {
         SzPeerNodeSts  *chkSts, *rcvSts;

         chkSts =  &sts.u.node;
         rcvSts =  &szMsg->u.szMngmt.u.sts.u.node;

         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "nmbUnexpEvt", &chkSts->cfm.nmbUnexpEvt);
         /* sz002.301: Removed unused statistics variable */
#ifndef LSZV2
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "nmbTRafExp", &chkSts->cfm.nmbTRafExp);
#endif /* LSZV2 */
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szDedProcSts.tx", &chkSts->cfm.szDedProcSts.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szDedProcSts.rx", &chkSts->cfm.szDedProcSts.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szComProcSts.tx", &chkSts->cfm.szComProcSts.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "szComProcSts.rx", &chkSts->cfm.szComProcSts.rx);

         /* sz002.301: Removed unused statistics variable */
         if((rcvSts->cfm.nmbUnexpEvt       != chkSts->cfm.nmbUnexpEvt)      ||
#ifndef LSZV2
            (rcvSts->cfm.nmbTRafExp        != chkSts->cfm.nmbTRafExp)       ||
#endif /* LSZV2 */
            (rcvSts->cfm.szDedProcSts.tx   != chkSts->cfm.szDedProcSts.tx)  ||
            (rcvSts->cfm.szDedProcSts.rx   != chkSts->cfm.szDedProcSts.rx)  ||
            (rcvSts->cfm.szComProcSts.tx   != chkSts->cfm.szComProcSts.tx)  ||
            (rcvSts->cfm.szComProcSts.rx   != chkSts->cfm.szComProcSts.rx))
         {
            CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : Statistics mismatch\n"));
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "checkPduSts", &checkPduSts);
      if(checkPduSts == TRUE)
      {
         SzPduSts chkPdu;
         SzPduSts *rcvPdu =NULLP;

         CMXTA_ZERO(&chkPdu, sizeof(SzPduSts));

         if (checkSctSapSts == TRUE)
         {
            rcvPdu =  &szMsg->u.szMngmt.u.sts.u.sctSap.cfm.pdu;
         }
         else if (checkPeerSts == TRUE)
         {
            rcvPdu =  &szMsg->u.szMngmt.u.sts.u.node.cfm.pdu;
         }

         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABSetupReq.tx" ,&chkPdu.eRABSetupReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABSetupReq.rx" ,&chkPdu.eRABSetupReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABSetupResp.tx" ,&chkPdu.eRABSetupResp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABSetupResp.rx" ,&chkPdu.eRABSetupResp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABModReq.tx" ,&chkPdu.eRABModReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABModReq.rx" ,&chkPdu.eRABModReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABModResp.tx" ,&chkPdu.eRABModResp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABModResp.rx" ,&chkPdu.eRABModResp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABRelCmd.tx" ,&chkPdu.eRABRelCmd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABRelCmd.rx" ,&chkPdu.eRABRelCmd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABRelComp.tx" ,&chkPdu.eRABRelComp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABRelComp.rx" ,&chkPdu.eRABRelComp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABRelReq.tx" ,&chkPdu.eRABRelReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eRABRelReq.rx" ,&chkPdu.eRABRelReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initCxtSetup.tx" ,&chkPdu.initCxtSetup.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initCxtSetup.rx" ,&chkPdu.initCxtSetup.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initCxtSetupResp.tx" ,&chkPdu.initCxtSetupResp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initCxtSetupResp.rx" ,&chkPdu.initCxtSetupResp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initCxtSetupFail.tx" ,&chkPdu.initCxtSetupFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initCxtSetupFail.rx" ,&chkPdu.initCxtSetupFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtRelReq.tx" ,&chkPdu.ueCxtRelReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtRelReq.rx" ,&chkPdu.ueCxtRelReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtRelCmd.tx" ,&chkPdu.ueCxtRelCmd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtRelCmd.rx" ,&chkPdu.ueCxtRelCmd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtRelComp.tx" ,&chkPdu.ueCxtRelComp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtRelComp.rx" ,&chkPdu.ueCxtRelComp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtModReq.tx" ,&chkPdu.ueCxtModReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtModReq.rx" ,&chkPdu.ueCxtModReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtModResp.tx" ,&chkPdu.ueCxtModResp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtModResp.rx" ,&chkPdu.ueCxtModResp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtModFail.tx" ,&chkPdu.ueCxtModFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCxtModFail.rx" ,&chkPdu.ueCxtModFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initUEMsg.tx" ,&chkPdu.initUEMsg.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"initUEMsg.rx" ,&chkPdu.initUEMsg.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"dwnNASTpt.tx" ,&chkPdu.dwnNASTpt.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"dwnNASTpt.rx" ,&chkPdu.dwnNASTpt.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"upNASTpt.tx" ,&chkPdu.upNASTpt.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"upNASTpt.rx" ,&chkPdu.upNASTpt.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nonDelIndNAS.tx" ,&chkPdu.nonDelIndNAS.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nonDelIndNAS.rx" ,&chkPdu.nonDelIndNAS.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"errInd.tx" ,&chkPdu.errInd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"errInd.rx" ,&chkPdu.errInd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"noData.tx" ,&chkPdu.noData.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"noData.rx" ,&chkPdu.noData.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"reset.tx" ,&chkPdu.reset.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"reset.rx" ,&chkPdu.reset.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetAck.tx" ,&chkPdu.resetAck.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetAck.rx" ,&chkPdu.resetAck.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"setupReq.tx" ,&chkPdu.setupReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"setupReq.rx" ,&chkPdu.setupReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"setupResp.tx" ,&chkPdu.setupResp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"setupResp.rx" ,&chkPdu.setupResp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"setupFail.tx" ,&chkPdu.setupFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"setupFail.rx" ,&chkPdu.setupFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"paging.tx" ,&chkPdu.paging.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"paging.rx" ,&chkPdu.paging.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handReqd.tx" ,&chkPdu.handReqd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handReqd.rx" ,&chkPdu.handReqd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handCmd.tx" ,&chkPdu.handCmd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handCmd.rx" ,&chkPdu.handCmd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handPrepFail.tx" ,&chkPdu.handPrepFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handPrepFail.rx" ,&chkPdu.handPrepFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handReq.tx" ,&chkPdu.handReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handReq.rx" ,&chkPdu.handReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handReqAck.tx" ,&chkPdu.handReqAck.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handReqAck.rx" ,&chkPdu.handReqAck.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handFail.tx" ,&chkPdu.handFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handFail.rx" ,&chkPdu.handFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handNtfy.tx" ,&chkPdu.handNtfy.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handNtfy.rx" ,&chkPdu.handNtfy.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pathSwchReq.tx" ,&chkPdu.pathSwchReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pathSwchReq.rx" ,&chkPdu.pathSwchReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pathSwchReqAck.tx" ,&chkPdu.pathSwchReqAck.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pathSwchReqAck.rx" ,&chkPdu.pathSwchReqAck.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pathSwchReqFail.tx" ,&chkPdu.pathSwchReqFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pathSwchReqFail.rx" ,&chkPdu.pathSwchReqFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handCan.tx" ,&chkPdu.handCan.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handCan.rx" ,&chkPdu.handCan.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handCanAck.tx" ,&chkPdu.handCanAck.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"handCanAck.rx" ,&chkPdu.handCanAck.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBStaTrans.tx" ,&chkPdu.eNBStaTrans.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBStaTrans.rx" ,&chkPdu.eNBStaTrans.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeStaTrans.tx" ,&chkPdu.mmeStaTrans.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeStaTrans.rx" ,&chkPdu.mmeStaTrans.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"deactTrace.tx" ,&chkPdu.deactTrace.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"deactTrace.rx" ,&chkPdu.deactTrace.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"traceStart.tx", &chkPdu.traceStart.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"traceStart.rx", &chkPdu.traceStart.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"traceFailInd.tx", &chkPdu.traceFailInd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"traceFailInd.rx", &chkPdu.traceFailInd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"locReportCntrl.tx", &chkPdu.locReportCntrl.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"locReportCntrl.rx", &chkPdu.locReportCntrl.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"locReportFailInd.tx", &chkPdu.locReportFailInd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"locReportFailInd.rx", &chkPdu.locReportFailInd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"locReport.tx", &chkPdu.locReport.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"locReport.rx", &chkPdu.locReport.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbCfgUpd.tx", &chkPdu.enbCfgUpd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbCfgUpd.rx", &chkPdu.enbCfgUpd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbCfgUpdAck.tx", &chkPdu.enbCfgUpdAck.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbCfgUpdAck.rx", &chkPdu.enbCfgUpdAck.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbCfgUpdFail.tx", &chkPdu.enbCfgUpdFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbCfgUpdFail.rx", &chkPdu.enbCfgUpdFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeCfgUpd.tx", &chkPdu.mmeCfgUpd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeCfgUpd.rx", &chkPdu.mmeCfgUpd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeCfgUpdAck.tx", &chkPdu.mmeCfgUpdAck.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeCfgUpdAck.rx", &chkPdu.mmeCfgUpdAck.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeCfgUpdFail.tx", &chkPdu.mmeCfgUpdFail.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeCfgUpdFail.rx", &chkPdu.mmeCfgUpdFail.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"upS1CDMA2000Tunn.tx" ,&chkPdu.upS1CDMA2000Tunn.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"upS1CDMA2000Tunn.rx" ,&chkPdu.upS1CDMA2000Tunn.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"dnS1CDMA2000Tunn.tx" ,&chkPdu.dnS1CDMA2000Tunn.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"dnS1CDMA2000Tunn.rx" ,&chkPdu.dnS1CDMA2000Tunn.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCapInfoInd.tx" ,&chkPdu.ueCapInfoInd.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCapInfoInd.rx" ,&chkPdu.ueCapInfoInd.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"overloadStart.tx", &chkPdu.overloadStart.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"overloadStart.rx", &chkPdu.overloadStart.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"overloadStop.tx", &chkPdu.overloadStop.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"overloadStop.rx", &chkPdu.overloadStop.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"writeRepWarnReq.tx", &chkPdu.writeRepWarnReq.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"writeRepWarnReq.rx", &chkPdu.writeRepWarnReq.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"writeRepWarnRsp.tx", &chkPdu.writeRepWarnRsp.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"writeRepWarnRsp.rx", &chkPdu.writeRepWarnRsp.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbDirInfoTrans.tx", &chkPdu.enbDirInfoTrans.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"enbDirInfoTrans.rx", &chkPdu.enbDirInfoTrans.rx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeDirInfoTrans.tx", &chkPdu.mmeDirInfoTrans.tx);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mmeDirInfoTrans.rx", &chkPdu.mmeDirInfoTrans.rx);

         if((chkPdu.eRABSetupReq.tx        != rcvPdu->eRABSetupReq.tx     ) ||   
            (chkPdu.eRABSetupReq.rx        != rcvPdu->eRABSetupReq.rx     ) ||   
            (chkPdu.eRABSetupResp.tx       != rcvPdu->eRABSetupResp.tx    ) ||   
            (chkPdu.eRABSetupResp.rx       != rcvPdu->eRABSetupResp.rx    ) ||   
            (chkPdu.eRABModReq.tx          != rcvPdu->eRABModReq.tx       ) ||   
            (chkPdu.eRABModReq.rx          != rcvPdu->eRABModReq.rx       ) ||   
            (chkPdu.eRABModResp.tx         != rcvPdu->eRABModResp.tx      ) ||   
            (chkPdu.eRABModResp.rx         != rcvPdu->eRABModResp.rx      ) ||   
            (chkPdu.eRABRelCmd.tx          != rcvPdu->eRABRelCmd.tx       ) ||   
            (chkPdu.eRABRelCmd.rx          != rcvPdu->eRABRelCmd.rx       ) ||   
            (chkPdu.eRABRelComp.tx         != rcvPdu->eRABRelComp.tx      ) ||   
            (chkPdu.eRABRelComp.rx         != rcvPdu->eRABRelComp.rx      ) ||   
            (chkPdu.eRABRelReq.tx          != rcvPdu->eRABRelReq.tx       ) ||   
            (chkPdu.eRABRelReq.rx          != rcvPdu->eRABRelReq.rx       ) ||   
            (chkPdu.initCxtSetup.tx        != rcvPdu->initCxtSetup.tx     ) ||   
            (chkPdu.initCxtSetup.rx        != rcvPdu->initCxtSetup.rx     ) ||   
            (chkPdu.initCxtSetupResp.tx    != rcvPdu->initCxtSetupResp.tx ) ||   
            (chkPdu.initCxtSetupResp.rx    != rcvPdu->initCxtSetupResp.rx ) ||   
            (chkPdu.initCxtSetupFail.tx    != rcvPdu->initCxtSetupFail.tx ) ||   
            (chkPdu.initCxtSetupFail.rx    != rcvPdu->initCxtSetupFail.rx ) ||   
            (chkPdu.ueCxtRelReq.tx         != rcvPdu->ueCxtRelReq.tx      ) ||   
            (chkPdu.ueCxtRelReq.rx         != rcvPdu->ueCxtRelReq.rx      ) ||   
            (chkPdu.ueCxtRelCmd.tx         != rcvPdu->ueCxtRelCmd.tx      ) ||   
            (chkPdu.ueCxtRelCmd.rx         != rcvPdu->ueCxtRelCmd.rx      ) ||   
            (chkPdu.ueCxtRelComp.tx        != rcvPdu->ueCxtRelComp.tx     ) ||   
            (chkPdu.ueCxtRelComp.rx        != rcvPdu->ueCxtRelComp.rx     ) ||   
            (chkPdu.ueCxtModReq.tx         != rcvPdu->ueCxtModReq.tx      ) ||   
            (chkPdu.ueCxtModReq.rx         != rcvPdu->ueCxtModReq.rx      ) ||   
            (chkPdu.ueCxtModResp.tx        != rcvPdu->ueCxtModResp.tx     ) ||   
            (chkPdu.ueCxtModResp.rx        != rcvPdu->ueCxtModResp.rx     ) ||   
            (chkPdu.ueCxtModFail.tx        != rcvPdu->ueCxtModFail.tx     ) ||   
            (chkPdu.ueCxtModFail.rx        != rcvPdu->ueCxtModFail.rx     ) ||   
            (chkPdu.initUEMsg.tx           != rcvPdu->initUEMsg.tx        ) ||   
            (chkPdu.initUEMsg.rx           != rcvPdu->initUEMsg.rx        ) ||   
            (chkPdu.dwnNASTpt.tx           != rcvPdu->dwnNASTpt.tx        ) ||   
            (chkPdu.dwnNASTpt.rx           != rcvPdu->dwnNASTpt.rx        ) ||   
            (chkPdu.upNASTpt.tx            != rcvPdu->upNASTpt.tx         ) ||   
            (chkPdu.upNASTpt.rx            != rcvPdu->upNASTpt.rx         ) ||   
            (chkPdu.nonDelIndNAS.tx        != rcvPdu->nonDelIndNAS.tx     ) ||   
            (chkPdu.nonDelIndNAS.rx        != rcvPdu->nonDelIndNAS.rx     ) ||   
            (chkPdu.errInd.tx              != rcvPdu->errInd.tx           ) ||   
            (chkPdu.errInd.rx              != rcvPdu->errInd.rx           ) ||   
            (chkPdu.noData.tx              != rcvPdu->noData.tx           ) ||   
            (chkPdu.noData.rx              != rcvPdu->noData.rx           ) ||   
            (chkPdu.reset.tx               != rcvPdu->reset.tx            ) ||   
            (chkPdu.reset.rx               != rcvPdu->reset.rx            ) ||   
            (chkPdu.resetAck.tx            != rcvPdu->resetAck.tx         ) ||   
            (chkPdu.resetAck.rx            != rcvPdu->resetAck.rx         ) ||   
            (chkPdu.setupReq.tx            != rcvPdu->setupReq.tx         ) ||   
            (chkPdu.setupReq.rx            != rcvPdu->setupReq.rx         ) ||   
            (chkPdu.setupResp.tx           != rcvPdu->setupResp.tx        ) ||   
            (chkPdu.setupResp.rx           != rcvPdu->setupResp.rx        ) ||   
            (chkPdu.setupFail.tx           != rcvPdu->setupFail.tx        ) ||   
            (chkPdu.setupFail.rx           != rcvPdu->setupFail.rx        ) ||   
            (chkPdu.paging.tx              != rcvPdu->paging.tx           ) ||   
            (chkPdu.paging.rx              != rcvPdu->paging.rx           ) ||   
            (chkPdu.handReqd.tx            != rcvPdu->handReqd.tx         ) ||   
            (chkPdu.handReqd.rx            != rcvPdu->handReqd.rx         ) ||   
            (chkPdu.handCmd.tx             != rcvPdu->handCmd.tx          ) ||   
            (chkPdu.handCmd.rx             != rcvPdu->handCmd.rx          ) ||   
            (chkPdu.handPrepFail.tx        != rcvPdu->handPrepFail.tx     ) ||   
            (chkPdu.handPrepFail.rx        != rcvPdu->handPrepFail.rx     ) ||   
            (chkPdu.handReq.tx             != rcvPdu->handReq.tx          ) ||   
            (chkPdu.handReq.rx             != rcvPdu->handReq.rx          ) ||   
            (chkPdu.handReqAck.tx          != rcvPdu->handReqAck.tx       ) ||   
            (chkPdu.handReqAck.rx          != rcvPdu->handReqAck.rx       ) ||   
            (chkPdu.handFail.tx            != rcvPdu->handFail.tx         ) ||   
            (chkPdu.handFail.rx            != rcvPdu->handFail.rx         ) ||   
            (chkPdu.handNtfy.tx            != rcvPdu->handNtfy.tx         ) ||   
            (chkPdu.handNtfy.rx            != rcvPdu->handNtfy.rx         ) ||   
            (chkPdu.pathSwchReq.tx         != rcvPdu->pathSwchReq.tx      ) ||   
            (chkPdu.pathSwchReq.rx         != rcvPdu->pathSwchReq.rx      ) ||   
            (chkPdu.pathSwchReqAck.tx      != rcvPdu->pathSwchReqAck.tx   ) ||   
            (chkPdu.pathSwchReqAck.rx      != rcvPdu->pathSwchReqAck.rx   ) ||   
            (chkPdu.pathSwchReqFail.tx     != rcvPdu->pathSwchReqFail.tx  ) ||   
            (chkPdu.pathSwchReqFail.rx     != rcvPdu->pathSwchReqFail.rx  ) ||   
            (chkPdu.handCan.tx             != rcvPdu->handCan.tx          ) ||   
            (chkPdu.handCan.rx             != rcvPdu->handCan.rx          ) ||   
            (chkPdu.handCanAck.tx          != rcvPdu->handCanAck.tx       ) ||   
            (chkPdu.handCanAck.rx          != rcvPdu->handCanAck.rx       ) ||   
            (chkPdu.eNBStaTrans.tx         != rcvPdu->eNBStaTrans.tx      ) ||   
            (chkPdu.eNBStaTrans.rx         != rcvPdu->eNBStaTrans.rx      ) ||   
            (chkPdu.mmeStaTrans.tx         != rcvPdu->mmeStaTrans.tx      ) ||   
            (chkPdu.mmeStaTrans.rx         != rcvPdu->mmeStaTrans.rx      ) ||   
            (chkPdu.deactTrace.tx          != rcvPdu->deactTrace.tx       ) ||   
            (chkPdu.deactTrace.rx          != rcvPdu->deactTrace.rx       ) ||   
            (chkPdu.traceStart.tx          != rcvPdu->traceStart.tx       ) ||   
            (chkPdu.traceStart.rx          != rcvPdu->traceStart.rx       ) ||   
            (chkPdu.traceFailInd.tx        != rcvPdu->traceFailInd.tx     ) ||   
            (chkPdu.traceFailInd.rx        != rcvPdu->traceFailInd.rx     ) ||   
            (chkPdu.locReportCntrl.tx      != rcvPdu->locReportCntrl.tx   ) ||   
            (chkPdu.locReportCntrl.rx      != rcvPdu->locReportCntrl.rx   ) ||   
            (chkPdu.locReportFailInd.tx    != rcvPdu->locReportFailInd.tx ) ||   
            (chkPdu.locReportFailInd.rx    != rcvPdu->locReportFailInd.rx ) ||   
            (chkPdu.locReport.tx           != rcvPdu->locReport.tx        ) ||   
            (chkPdu.locReport.rx           != rcvPdu->locReport.rx        ) ||   
            (chkPdu.enbCfgUpd.tx           != rcvPdu->enbCfgUpd.tx        ) ||   
            (chkPdu.enbCfgUpd.rx           != rcvPdu->enbCfgUpd.rx        ) ||   
            (chkPdu.enbCfgUpdAck.tx        != rcvPdu->enbCfgUpdAck.tx     ) ||   
            (chkPdu.enbCfgUpdAck.rx        != rcvPdu->enbCfgUpdAck.rx     ) ||   
            (chkPdu.enbCfgUpdFail.tx       != rcvPdu->enbCfgUpdFail.tx    ) ||   
            (chkPdu.enbCfgUpdFail.rx       != rcvPdu->enbCfgUpdFail.rx    ) ||   
            (chkPdu.mmeCfgUpd.tx           != rcvPdu->mmeCfgUpd.tx        ) ||   
            (chkPdu.mmeCfgUpd.rx           != rcvPdu->mmeCfgUpd.rx        ) ||   
            (chkPdu.mmeCfgUpdAck.tx        != rcvPdu->mmeCfgUpdAck.tx     ) ||   
            (chkPdu.mmeCfgUpdAck.rx        != rcvPdu->mmeCfgUpdAck.rx     ) ||   
            (chkPdu.mmeCfgUpdFail.tx       != rcvPdu->mmeCfgUpdFail.tx    ) ||   
            (chkPdu.mmeCfgUpdFail.rx       != rcvPdu->mmeCfgUpdFail.rx    ) ||   
            (chkPdu.upS1CDMA2000Tunn.tx    != rcvPdu->upS1CDMA2000Tunn.tx ) ||   
            (chkPdu.upS1CDMA2000Tunn.rx    != rcvPdu->upS1CDMA2000Tunn.rx ) ||
            (chkPdu.dnS1CDMA2000Tunn.tx    != rcvPdu->dnS1CDMA2000Tunn.tx ) ||   
            (chkPdu.dnS1CDMA2000Tunn.rx    != rcvPdu->dnS1CDMA2000Tunn.rx ) ||   
            (chkPdu.ueCapInfoInd.tx        != rcvPdu->ueCapInfoInd.tx     ) ||   
            (chkPdu.ueCapInfoInd.rx        != rcvPdu->ueCapInfoInd.rx     ) ||   
            (chkPdu.overloadStart.tx       != rcvPdu->overloadStart.tx    ) ||   
            (chkPdu.overloadStart.rx       != rcvPdu->overloadStart.rx    ) ||   
            (chkPdu.overloadStop.tx        != rcvPdu->overloadStop.tx     ) ||   
            (chkPdu.overloadStop.rx        != rcvPdu->overloadStop.rx     ) ||   
            (chkPdu.writeRepWarnReq.tx     != rcvPdu->writeRepWarnReq.tx  ) ||   
            (chkPdu.writeRepWarnReq.rx     != rcvPdu->writeRepWarnReq.rx  ) ||   
            (chkPdu.writeRepWarnRsp.tx     != rcvPdu->writeRepWarnRsp.tx  ) ||   
            (chkPdu.writeRepWarnRsp.rx     != rcvPdu->writeRepWarnRsp.rx  ) ||   
            (chkPdu.enbDirInfoTrans.tx     != rcvPdu->enbDirInfoTrans.tx  ) ||   
            (chkPdu.enbDirInfoTrans.rx     != rcvPdu->enbDirInfoTrans.rx  ) ||   
            (chkPdu.mmeDirInfoTrans.tx     != rcvPdu->mmeDirInfoTrans.tx  ) ||
            (chkPdu.mmeDirInfoTrans.rx     != rcvPdu->mmeDirInfoTrans.rx  ))
         {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : Pdu Statistics mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
         }
      }
#ifdef LSZV1 
      if(checkErrSts == TRUE)
      {
         SzErrSts chkErrSts;
         SzErrSts *rcvErrSts =NULLP;

         CMXTA_ZERO(&chkErrSts, sizeof(SzErrSts));

         rcvErrSts =  &szMsg->u.szMngmt.u.sts.u.node.cfm.errSts;

         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"radioNwUnknownMmeUeS1apId" ,&chkErrSts.radioNwErrSts.unknownMmeUeS1apId);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"radioNwUnknownEnbUeS1apId" ,&chkErrSts.radioNwErrSts.unknownEnbUeS1apId);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"radioNwUnknownPairUeS1apId" ,&chkErrSts.radioNwErrSts.unknownPairUeS1apId);

         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"protTransferSyntaxErr" ,&chkErrSts.protErrSts.transferSyntaxErr);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"protAbsSyntaxErrRej" ,&chkErrSts.protErrSts.absSyntaxErrRej);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"protAbsSyntaxErrIgnAndNtfy" ,&chkErrSts.protErrSts.absSyntaxErrIgnAndNtfy);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"protMsgNotCompWithRcvrState" ,&chkErrSts.protErrSts.msgNotCompWithRcvrState);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"protSemanticErr" ,&chkErrSts.protErrSts.semanticErr);
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"protAbsSyntaxErrFalslyConsMsg" ,&chkErrSts.protErrSts.absSyntaxErrFalslyConsMsg);

         if((chkErrSts.radioNwErrSts.unknownMmeUeS1apId!= rcvErrSts->radioNwErrSts.unknownMmeUeS1apId) ||   
            (chkErrSts.radioNwErrSts.unknownEnbUeS1apId!= rcvErrSts->radioNwErrSts.unknownEnbUeS1apId) ||   
            (chkErrSts.radioNwErrSts.unknownPairUeS1apId!= rcvErrSts->radioNwErrSts.unknownPairUeS1apId) ||   
            (chkErrSts.protErrSts.transferSyntaxErr!= rcvErrSts->protErrSts.transferSyntaxErr) ||   
            (chkErrSts.protErrSts.absSyntaxErrRej!= rcvErrSts->protErrSts.absSyntaxErrRej) ||   
            (chkErrSts.protErrSts.absSyntaxErrIgnAndNtfy!= rcvErrSts->protErrSts.absSyntaxErrIgnAndNtfy) ||   
            (chkErrSts.protErrSts.msgNotCompWithRcvrState!= rcvErrSts->protErrSts.msgNotCompWithRcvrState) ||   
            (chkErrSts.protErrSts.semanticErr!= rcvErrSts->protErrSts.semanticErr) ||   
            (chkErrSts.protErrSts.absSyntaxErrFalslyConsMsg!= rcvErrSts->protErrSts.absSyntaxErrFalslyConsMsg))   
            
         {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : Error Statistics mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
         }

         CMXTA_DBG_INFO((_cmxtap, "\n\n------Error Statistics------\n"));

#ifdef ALIGN_64BIT
         CMXTA_DBG_INFO((_cmxtap, "\n ***Radio Network Errors***\n"));
         CMXTA_DBG_INFO((_cmxtap,"\n   Unknown mme UE S1AP ID :  %d", rcvErrSts->radioNwErrSts.unknownMmeUeS1apId));
         CMXTA_DBG_INFO((_cmxtap,"\n   Unknown enb UE S1AP ID:  %d ", rcvErrSts->radioNwErrSts.unknownEnbUeS1apId));
         CMXTA_DBG_INFO((_cmxtap,"\n   Unknown pair UE S1AP ID: %d ", rcvErrSts->radioNwErrSts.unknownPairUeS1apId));

         CMXTA_DBG_INFO((_cmxtap,"\n\n ***Protocol Errors*** \n"));
         CMXTA_DBG_INFO((_cmxtap,"\n   Transfer Syntax Error: %d ", rcvErrSts->protErrSts.transferSyntaxErr));
         CMXTA_DBG_INFO((_cmxtap,"\n   Abstract Syntax Error criticality reject: %d ", rcvErrSts->protErrSts.absSyntaxErrRej));
         CMXTA_DBG_INFO((_cmxtap,"\n   Abstract Syntax Error criticality ign & notify: %d ", rcvErrSts->protErrSts.absSyntaxErrIgnAndNtfy));
         CMXTA_DBG_INFO((_cmxtap,"\n   Message not compatible with receiver state: %d ", rcvErrSts->protErrSts.msgNotCompWithRcvrState));
         CMXTA_DBG_INFO((_cmxtap,"\n   Semantic Error: %d ", rcvErrSts->protErrSts.semanticErr));
         CMXTA_DBG_INFO((_cmxtap,"\n   Abstract Syntax Error falsely constructed msg: %d \n", rcvErrSts->protErrSts.absSyntaxErrFalslyConsMsg));
#else
         CMXTA_DBG_INFO((_cmxtap, "\n ***Radio Network Errors***\n"));
         CMXTA_DBG_INFO((_cmxtap,"\n   Unknown mme UE S1AP ID : %ld", rcvErrSts->radioNwErrSts.unknownMmeUeS1apId));
         CMXTA_DBG_INFO((_cmxtap,"\n   Unknown enb UE S1AP ID: %ld ", rcvErrSts->radioNwErrSts.unknownEnbUeS1apId));
         CMXTA_DBG_INFO((_cmxtap,"\n   Unknown pair UE S1AP ID: %ld ", rcvErrSts->radioNwErrSts.unknownPairUeS1apId));

         CMXTA_DBG_INFO((_cmxtap,"\n\n ***Protocol Errors*** \n"));
         CMXTA_DBG_INFO((_cmxtap,"\n   Transfer Syntax Error: %ld ", rcvErrSts->protErrSts.transferSyntaxErr));
         CMXTA_DBG_INFO((_cmxtap,"\n   Abstract Syntax Error criticality reject: %ld ", rcvErrSts->protErrSts.absSyntaxErrRej));
         CMXTA_DBG_INFO((_cmxtap,"\n   Abstract Syntax Error criticality ign & notify: %ld ", rcvErrSts->protErrSts.absSyntaxErrIgnAndNtfy));
         CMXTA_DBG_INFO((_cmxtap,"\n   Message not compatible with receiver state: %ld ", rcvErrSts->protErrSts.msgNotCompWithRcvrState));
         CMXTA_DBG_INFO((_cmxtap,"\n   Semantic Error: %ld ", rcvErrSts->protErrSts.semanticErr));
         CMXTA_DBG_INFO((_cmxtap,"\n   Abstract Syntax Error falsely constructed msg: %ld \n", rcvErrSts->protErrSts.absSyntaxErrFalslyConsMsg));
#endif   /* ALIGN_64BIT */        
      } 
#endif /* LSZV1 */
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkGenSts",&checkGenSts);
   if (checkGenSts == TRUE)
   {
      SzGenSts chkGen;
      SzGenSts *rcvGen;

      rcvGen   =  &szMsg->u.szMngmt.u.sts.u.gen;
      CMXTA_ZERO(&chkGen, sizeof(SzGenSts));

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbConn",&chkGen.nmbConn);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbFailConn",&chkGen.nmbFailConn);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"maxMemAlloc",&chkGen.maxMemAlloc);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbDecErr",&chkGen.nmbDecErr);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbEncErr",&chkGen.nmbEncErr);

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbAudReq",&chkGen.audSts.nmbAudReq);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbAudConn",&chkGen.audSts.nmbAudConn);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbAudPeer",&chkGen.audSts.nmbAudPeer);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbAudFlc",&chkGen.audSts.nmbAudFlc);
      
      if((chkGen.nmbConn      != rcvGen->nmbConn)||
         (chkGen.nmbFailConn  != rcvGen->nmbFailConn)||
         (chkGen.maxMemAlloc  != rcvGen->maxMemAlloc)||
         (chkGen.nmbDecErr    != rcvGen->nmbDecErr)||
         (chkGen.nmbEncErr    != rcvGen->nmbEncErr)||
         (chkGen.audSts.nmbAudReq    != rcvGen->audSts.nmbAudReq)||
         (chkGen.audSts.nmbAudConn   != rcvGen->audSts.nmbAudConn)||
         (chkGen.audSts.nmbAudPeer   != rcvGen->audSts.nmbAudPeer)||
         (chkGen.audSts.nmbAudFlc    != rcvGen->audSts.nmbAudFlc))
      {
         CMXTA_DBG_ERR((_cmxtap, "szAcHdlStsCfm() : Gen Statistics mismatch\n"));
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlStsCfm */
 
/*
*
*       Fun:   szAcHdlStaReq
*
*       Desc:  Call handler for Transport Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  ssta;
   Pst      pst;
   U8    staType;
 
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(szAcHdlStaReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStaReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStaReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&ssta, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }

   staType  = STSZGEN;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "staType", &staType);

   if(staType == STSZSZTSAP || staType == STSZSCTSAP)
   {
      ssta.u.ssta.s.sap.sapId =  0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sapId",  
                                                 &(ssta.u.ssta.s.sap.sapId ));
   }
   else if (staType == STSZPEER)
   {
      ssta.u.ssta.s.peer.nmbPeer = 1;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "nmbPeer", &(ssta.u.ssta.s.peer.nmbPeer));
      CMXTA_ALLOC(&ssta.u.ssta.s.peer.peerStaInfo, (sizeof(SzPeerStaInfo) * ssta.u.ssta.s.peer.nmbPeer)); 

      ssta.u.ssta.s.peer.peerStaInfo[0].peerId.pres = TRUE;
      ssta.u.ssta.s.peer.peerStaInfo[0].peerId.val  = 1;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(ssta.u.ssta.s.peer.peerStaInfo[0].peerId.val));
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, staType, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trensport Server Status Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszStaReq(&pst, &ssta);
 
   RETVALUE(ROK);
}/* szAcHdlStaReq */
 
/*
*
*       Fun:   szAcHdlStaCfm
*
*       Desc:  Call handler for Status Confirmation from Layer  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Txt      dispString[64];
   Pst      pst;
   S16      ret;
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStaCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStaCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

 
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLSZSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaCfm() : No match, not for this test case\n"));
      /* sz003.301: Updted for PSF-S1AP 3.1 release. Removed the flushing of
       * the message as it is required to be present in case of expect set */
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.szMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   if(status.status == LCM_PRIM_OK)
   {
      switch( szMsg->u.szMngmt.hdr.elmId.elmnt )
      {
         case STSZSZTSAP:
         {
 
            U8 sapState = LSZ_SAP_ISBOUND;
            S16   sapId =  0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "sapId",  &sapId);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapState",  &sapState);

            if (szMsg->u.szMngmt.u.ssta.s.sap.status != sapState)
            {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlsapStaCfm() : sapState mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
            if (szMsg->u.szMngmt.u.ssta.s.sap.sapId != sapId)
            {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlsapStaCfm() : sapState mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case STSZSCTSAP:
         {
 
            U8 sapState = LSZ_SAP_ISBOUND;
            S16   sapId =  0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapId",  &sapId);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapState",  &sapState);
            if (szMsg->u.szMngmt.u.ssta.s.sap.status != sapState)
            {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlsapStaCfm() : sapState mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
            if (szMsg->u.szMngmt.u.ssta.s.sap.sapId != sapId)
            {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlsapStaCfm() : sapState mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
 
         }
         break;
         case STSZSID:
         {
            SystemId tmpId;
            tmpId.mVer  =  1;
            tmpId.mRev  =  1;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "mVer",  &(tmpId.mVer));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "mRev",  &(tmpId.mRev));

            if((szMsg->u.szMngmt.u.ssta.s.sysId.mVer != tmpId.mVer)||
               (szMsg->u.szMngmt.u.ssta.s.sysId.mRev != tmpId.mRev))
            {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlSysIdStaCfm() : Sys Id values mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case STSZGEN:
         {
            Cntr tmpActConn = 0;
            U8 audit = 0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "numActvPeerConn",  &(tmpActConn));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "audit",  &audit);

            if((szMsg->u.szMngmt.u.ssta.s.gen.nmbActvPeerConn != tmpActConn))
            {
               CMXTA_DBG_ERR((_cmxtap, "szAcHdlGenStaCfm() : Gen Id values mismatch\n"));
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case STSZPEER:
         {
            SzPeerStaInfo chkInfo;
            SzPeerStaInfo *rcvInfo;

            U8 nmbPeer = 1;
            U8 i = 0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numPeer",  &(nmbPeer));

            CMXTA_ZERO(&chkInfo, sizeof(SzPeerStaInfo));
            chkInfo.peerId.pres = TRUE;
            chkInfo.peerId.val  = 1;

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32   , "peerId",    &(chkInfo.peerId.val));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8    , "peerState", &(chkInfo.peerState));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32   , "spAssocId", &(chkInfo.spAssocId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL  , "connected", &(chkInfo.connected));
         /* sz002.301: Removed unused statistics variable */
#ifndef LSZV2
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16   , "nmbRetries",&(chkInfo.nmbRetries));
#endif /* LSZV2 */

            for(i=0; i<nmbPeer; i++)
            {
               rcvInfo  = &(szMsg->u.szMngmt.u.ssta.s.peer.peerStaInfo[i]); 
               
               sprintf(dispString,"peerStaInfo_%d_peerId",i);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32 , dispString, &(chkInfo.peerId.val));

               sprintf(dispString,"peerStaInfo_%d_peerState",i);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8 , dispString, &(chkInfo.peerState));

               sprintf(dispString,"peerStaInfo_%d_spAssocId",i);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32 , dispString, &(chkInfo.spAssocId));

               sprintf(dispString,"peerStaInfo_%d_connected",i);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL , dispString, &(chkInfo.connected));

               /* sz002.301: Removed unused statistics variable */
#ifndef LSZV2
               sprintf(dispString,"peerStaInfo_%d_nmbRetries",i);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16 , dispString, &(chkInfo.nmbRetries));
#endif /* LSZV2 */

               /* sz002.301: Removed unused statistics variable */
               if(((rcvInfo->peerId.pres != chkInfo.peerId.pres)||
                   (rcvInfo->peerId.val != chkInfo.peerId.val))||
                  (rcvInfo->peerState != chkInfo.peerState)||
                  (rcvInfo->spAssocId != chkInfo.spAssocId)||
#ifndef LSZV2
                  (rcvInfo->nmbRetries != chkInfo.nmbRetries)||
#endif /* LSZV2 */
                  (rcvInfo->connected != chkInfo.connected))
               {
                  CMXTA_DBG_ERR((_cmxtap, "szAcHdlPeerSta() : Peer values mismatch\n"));
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }

               CMXTA_ZERO(&chkInfo, sizeof(SzPeerStaInfo));
               chkInfo.peerId.pres = TRUE;
               chkInfo.peerId.val  = 1;
               
            }
            break;
         }
      }
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(ROK);
}/* szAcHdlStaCfm */

/*    
*  
*       Fun:   szAcHdlStaInd 
*  
*       Desc:  Call handler for Status Indication 
*  
*       Ret:   S16
*
*       Notes: 
*  
*       File:  szac_lszhdl.c  
*/    
#ifdef ANSI
PUBLIC S16 szAcHdlStaInd
(     
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 szAcHdlStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif 
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret=ROK;
   Bool     validateElem = FALSE;
   S16      element = 0;
   U16      category = 0;
   U16      event = 0;
   U16      cause = 0;
   U16      type=0;
   U32      typeId = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStaInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif
      
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
      
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
      
   pst.event = EVTLSZSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {     
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }     

   szMsg = (SzAccMsgQElm *)msg->data;

   /*validate the element,alarm category,event and cause*/

   /*validation of element is optional*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"validateElem",&validateElem);
   if(validateElem)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"element",&element);
      if(szMsg->u.szMngmt.hdr.elmId.elmnt != element)
      {
         CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected element\
                 %d received %d\n",element,szMsg->u.szMngmt.hdr.elmId.elmnt));
         ret = CMXTA_ERR_INT;
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"category",&(category));
   if(szMsg->u.szMngmt.u.usta.alarm.category != category)
   {
       CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected category\
               %d received %d\n",category,szMsg->u.szMngmt.u.usta.alarm.category));
       ret = CMXTA_ERR_INT;
   }
     
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"event",&(event));
   if(szMsg->u.szMngmt.u.usta.alarm.event != event)
   {
       CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected event\
               %d received %d\n",event,szMsg->u.szMngmt.u.usta.alarm.event));
       ret = CMXTA_ERR_INT;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"cause",&(cause));
   if(szMsg->u.szMngmt.u.usta.alarm.cause != cause)
   {
       CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected cause\
               %d received %d\n",cause,szMsg->u.szMngmt.u.usta.alarm.cause));
       ret = CMXTA_ERR_INT;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"type",&(type));
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"typeId",&(typeId));
   switch(type)
   {
      case LSZ_USTA_DGNVAL_SAPID:
      {
         if(szMsg->u.szMngmt.u.usta.dgn.u.sapId != (S16)typeId)
         {
#ifdef ALIGN_64BIT
             CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected sapId\
                     %d received %d\n",typeId,szMsg->u.szMngmt.u.usta.dgn.u.sapId ));
#else
             CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected sapId\
                     %ld received %d\n",typeId,szMsg->u.szMngmt.u.usta.dgn.u.sapId ));
#endif
             ret = CMXTA_ERR_INT;
         }
      }
      break;
      case LSZ_USTA_DGNVAL_CONID:
      {
         if(szMsg->u.szMngmt.u.usta.dgn.u.connId != (U32)typeId)
         {
#ifdef ALIGN_64BIT
             CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected connid\
                     %d received %d\n",typeId,szMsg->u.szMngmt.u.usta.dgn.u.connId ));
#else
             CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected connid\
                     %ld received %ld\n",typeId,szMsg->u.szMngmt.u.usta.dgn.u.connId ));
#endif
             ret = CMXTA_ERR_INT;
         }
      }
      break;
      case LSZ_USTA_DGNVAL_PEER:
      {
         if(szMsg->u.szMngmt.u.usta.dgn.u.peerId.val != (U32)typeId)
         {
#ifdef ALIGN_64BIT
             CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected PeerId\
                     %d received %d\n",typeId,szMsg->u.szMngmt.u.usta.dgn.u.peerId.val ));
#else
             CMXTA_DBG_ERR((_cmxtap, "szAcHdlStaInd() failed,expected PeerId\
                     %ld received %ld\n",typeId,szMsg->u.szMngmt.u.usta.dgn.u.peerId.val ));
#endif
             ret = CMXTA_ERR_INT;
         }
      }
      break;
      default:
         break;
   }

   /*-- Pop the message --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
         
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      
   RETVALUE(ret);
}/* szAcHdlStaInd */
 
/*
*
*       Fun:   szAcHdlTrcInd
*
*       Desc:  Call handler for Trace Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   Pst      pst;
   S16      ret;
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlTrcInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlTrcInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
 
   pst.event = EVTLSZTRCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlTrcInd(): No Match, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlTrcInd */

/* 
*
*       Fun:   szAcHdlUSapCntrlReq
*
*       Desc:  Call handler for SSap Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*  
*/  
#ifdef ANSI
PUBLIC S16 szAcHdlUSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 szAcHdlUSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb; 
   
   TRC2(szAcHdlUSapCntrlReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlUSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlUSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildUSapCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZSZTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending SSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlUSapCntrlReq */
 
/*
*
*       Fun:   szAcHdlLSapCntrlReq
*
*       Desc:  Call handler for LSap Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlLSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlLSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlLSapCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlLSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlLSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildLSapCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZSCTSAP,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending S1AP TSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlLSapCntrlReq */
 
/*
*
*       Fun:   szAcHdlLSapTrcCntrlReq
*
*       Desc:  Call handler for LSap Trace Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlLSapTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlLSapTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlLSapTrcCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlLSapTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlLSapTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildLSapTrcCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZSCTSAP,
                    pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending S1AP LSAP Trc Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlLSapTrcCntrlReq */

/*
*
*       Fun:   szAcHdlPNodeTrcCntrlReq
*
*       Desc:  Call handler for PNode Trace Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlPNodeTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlPNodeTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(szAcHdlPNodeTrcCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlPNodeTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlPNodeTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildPNodeTrcCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZPEER,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending S1AP Peer Trace Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlPNodeTrcCntrlReq */

#ifdef DEBUGP
/*
*
*       Fun:   szAcHdlDebugCntrlReq
*
*       Desc:  Call handler for Debug Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlDebugCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlDebugCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlDebugCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlDebugCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
 
   szAcUtlBuildDebugCntrlReq(tcCb, spCb, &cntrl);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   /*-- Write a new function xxUtlHiBuildTSap to fill the data 
        structures and to get information from the XML, for smaller data, all
        the requests may map to a single build function as welll --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlDebugCntrlReq */
#endif

/*
*
*       Fun:   szAcHdlPeerCntrlReq
*
*       Desc:  Call handler for Debug Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlPeerCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlPeerCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
 
   TRC2(szAcHdlPeerCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlPeerCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlPeerCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }

 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   szAcUtlBuildPeerCntrlReq(tcCb, spCb, &cntrl);
   /*-- Write a new function xxUtlHiBuildTSap to fill the data 
        structures and to get information from the XML, for smaller data, all
        the requests may map to a single build function as welll --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /*-- Prepare header --*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZPEER, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending PeerControl Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlPeerCntrlReq */

/*
*
*       Fun:   szAcHdlUstaCntrlReq
*
*       Desc:  Call handler for Unsoliciated Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlUstaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;

 
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(szAcHdlUstaCntrlReq)
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlUstaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlUstaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildUstaCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZGEN, pst.selector);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "element", &(cntrl.hdr.elmId.elmnt));
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Usta Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlUstaCntrlReq */

/*
*
*       Fun:   szAcHdlTrcCntrlReq
*
*       Desc:  Call handler for Unsoliciated Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;
 
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlTrcCntrlReq)
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   szAcUtlBuildTrcCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trc Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlTrcCntrlReq */

/*
*
*       Fun:   szAcHdlCntrlCfm
*
*       Desc:  Call handler for Control confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
 
   pst.event = EVTLSZCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlCntrlCfm() :  No Match, not for this Test Case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.szMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(ROK);
 
}/* szAcHdlCntrlCfm */

/*
*
*       Fun:   szAcHdlShutDownCntrlReq
*
*       Desc:  Call handler for Shutdown Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlShutDownCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SzMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(szAcHdlShutDownCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlShutDownCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlShutDownCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(SzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl.u.cntrl.action        = ASHUTDOWN;
   cntrl.u.cntrl.subAction    = SAELMNT;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSZ, CMXTA_INST_ID, STSZGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending ShutDown Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLszCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* szAcHdlShutDownCntrlReq */

/*
*
*       Fun:   szAcHdlSctDelay
*
*       Desc:  Call handler for Sct interface delay
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSctDelay
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSctDelay(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst      entPst;
   Ent      provType;
 
   TRC2(szAcHdlSctDelay);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDelay(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDelay(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Internal command to handle delay --*/
   provType    =  ENTSB;
#ifdef SZAC_LKSCTP
   provType    = ENTHI;
#endif

#ifdef SZAC_INTG_TEST
   RETVALUE(cmXtaHdlIntDelay(tcCb, spCb));
#else
   cmXtaGetPst(&entPst, ENTSZ, CMXTA_INST_ID, provType, CMXTA_INST_ID, 0, 0, FALSE);

   /*-- Check if we are to skip delay command delays --*/
   if (entPst.selector == 0)
   {
      /*-- Just Pass to Internal Delay Handler --*/
      RETVALUE(cmXtaHdlIntDelay(tcCb, spCb));
   }

#endif /* #SZAC_INTG_TEST  */

   CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skipping SCT delay\n"), 3);
   RETVALUE(CMXTA_ERR_NONE);

}/* szAcHdlSctDelay */

/********************************************************************30**

         End of file:     szac_lszhdl.c@@/main/4 - Mon Jan 10 22:15:53 2011

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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4     sz002.301 pkaX  1. Removed the unused statistcs variable.
/main/4     sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4     sz006.301   ve    1. Removed un-necessary include files
/main/4     sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
