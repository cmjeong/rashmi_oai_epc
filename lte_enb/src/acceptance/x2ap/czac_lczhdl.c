
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_lczhdl.c

     Sid:      czac_lczhdl.c@@/main/2 - Tue Aug 30 18:35:47 2011

     Prg:     sy
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
#include "cm_tpt.h"        /* common transport defines */
#include "cm_pasn.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for CZCP */
#include "cz.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 


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
#include "cm_pasn.x"        /* common transport defines */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* CZT Interface Structures */
#include "lcz.x"           /* layer management typedefs for CZCP */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"

PUBLIC eNodeBProfile czENodeB[CZ_MAX_ENODEB];
PUBLIC CzProtCfg     czProtProf[10];
PUBLIC CzPeerCfg    czPeerProf[10];

/* cz001.101 : CR Fixes. */
/*
*
*       Fun:   czAcHdlGenCfgReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cfg;
   Pst      pst;

   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(czAcHdlGenCfgReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cfg, sizeof(CzMngmt)); 
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cfg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlGenCfgReq(): cfg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildGenCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZGEN, pst.selector);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "element", &(cfg->hdr.elmId.elmnt));
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));
 
 
   /* Send the request to the LM */
   (Void) SmMiLczCfgReq(&pst,cfg);
 
   RETVALUE(ROK);
}/* czAcHdlGenCfgReq */
 
/*
*
*       Fun:   czAcHdlUSapCfgReq
*
*       Desc:  Call handler for SSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlUSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlUSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlUSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlUSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlUSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cfg, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cfg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlUSapCfgReq(): cfg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildUSapCfgReq(tcCb, spCb, cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZCZTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending CZT SSAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCfgReq(&pst, cfg);
 
   RETVALUE(ROK);
}/* czAcHdlUSapCfgReq */
 
 
 
/*
*
*       Fun:   czAcHdlLSapCfgReq
*
*       Desc:  Call handler for TSAP Cfg Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlLSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlLSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlLSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlLSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlLSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cfg, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cfg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlLSapCfgReq(): cfg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildLSapCfgReq(tcCb, spCb, cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZSCTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TSAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCfgReq(&pst, cfg);
 
   RETVALUE(ROK);
}/* czAcHdlLSapCfgReq */
 

/*
*
*       Fun:   czAcHdlProtCfgReq
*
*       Desc:  Call handler for Protocol Configuration Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlProtCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlProtCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   Bool tightCoupled = FALSE;
 
   TRC2(czAcHdlProtCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlProtCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlProtCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cfg, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
  
   /* klockwork fix */ 
   if (cfg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlProtCfgReq(): cfg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
 
   czAcUtlBuildProtCfgReq(tcCb, spCb, cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZPROT,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP Protocol Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCfgReq(&pst, cfg);
 
   RETVALUE(ROK);
}/* czAcHdlProtCfgReq */


/*
*
*       Fun:   czAcHdlPeerCfgReq
*
*       Desc:  Call handler for Transort Server Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlPeerCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlPeerCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cfg;
   Pst      pst;
 
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlPeerCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlPeerCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlPeerCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cfg, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   /* klockwork fix */ 
   if (cfg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlPeerCfgReq(): cfg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
 
   czAcUtlBuildPeerCfgReq(tcCb, spCb, cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZPEER,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP PEER Configuration request\n"));
 
 
   /* Send the request to the LM */
   (Void) SmMiLczCfgReq(&pst, cfg);
 
   RETVALUE(ROK);
}/* czAcHdlPeerCfgReq */

/*
*
*       Fun:   czAcHdlCfgCfm
*
*       Desc:  Call handler for configuration conformation 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   TRC2(czAcHdlCfgCfm);
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCfgCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCfgCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;

   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
 
   pst.event = EVTLCZCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCfgCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.czMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCfgCfm */

/*  
*
*       Fun:   czAcHdlStsReq
*
*       Desc:  Call handler for  Statistics Request 
*   
*       Ret:   ROK
*  
*       Notes: None
*              
*       File:  czac_lczhdl.c
*  
*/ 
#ifdef ANSI
PUBLIC S16 czAcHdlStsReq
(  
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   U8 stsType;
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(czAcHdlStsReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStsReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStsReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&sts, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   /* klockwork fix */ 
   if (sts == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsReq(): sts is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   action = NOZEROSTS;
   stsType  =  STCZGEN;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &action);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "actionErr",  &action);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"stsType",&stsType);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);


   if(stsType == STCZPEER)
   {
      sts->t.sts.u.nodeSts.peerId= 0;
    
      /*-- Use Python wrapper APIs to extract the parameters which can be changed
           using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  
                                       &(sts->t.sts.u.nodeSts.peerId));
   } 
    
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, stsType, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczStsReq(&pst, action, sts);
 
   RETVALUE(ROK);
}/* czAcHdlStsReq */

/*
*
*       Fun:   czAcHdlStsCfm
*
*       Desc:  Call handler for Statistics Confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Bool     checkGenSts = FALSE;
   Bool     checkPeerSts = FALSE;
   Bool     checkGenPduSts =FALSE;
   TRC2(czAcHdlStsCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStsCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStsCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   czMsg = (CzAccMsgQElm *)msg->data;

 
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLCZSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.czMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkPeerSts",&checkGenSts);
   if (checkPeerSts == TRUE)
   {
      CzPeerNodeSts  chkSts;
      CzPeerNodeSts  *rcvSts;
      Bool  checkPduSts =  FALSE;

      rcvSts   =  &czMsg->u.czMngmt.t.sts.u.nodeSts;
      CMXTA_ZERO(&chkSts, sizeof(CzPeerNodeSts));

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbUnexpEvt"     ,&chkSts.cfm.nmbUnexpEvt);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbDecErr" ,&chkSts.cfm.nmbDecErr);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbEncErr" ,&chkSts.cfm.nmbEncErr);

      if((rcvSts->cfm.nmbUnexpEvt       != chkSts.cfm.nmbUnexpEvt)      ||
         (rcvSts->cfm.nmbEncErr   != chkSts.cfm.nmbEncErr)  ||
         (rcvSts->cfm.nmbDecErr  != chkSts.cfm.nmbDecErr))
      {
         CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsCfm() : PEER_Statistics mismatch\n"));
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkPduSts",&checkPduSts);
      if(checkPduSts == TRUE)
      {
         CzPduSts chkPdu;
         CzPduSts *rcvPdu;

         rcvPdu   =  &czMsg->u.czMngmt.t.sts.u.nodeSts.cfm.pdu;

        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrRqst.tx" ,&chkPdu.hovrRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrRqst.rx" ,&chkPdu.hovrRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrReqAck.tx" ,&chkPdu.hovrReqAck.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrReqAck.rx" ,&chkPdu.hovrReqAck.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrPrepFail.tx" ,&chkPdu.hovrPrepFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrPrepFail.rx" ,&chkPdu.hovrPrepFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"sNStatusTfr.tx" ,&chkPdu.sNStatusTfr.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"sNStatusTfr.rx" ,&chkPdu.sNStatusTfr.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrCancel.tx" ,&chkPdu.hovrCancel.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrCancel.rx" ,&chkPdu.hovrCancel.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCntxtRls.tx" ,&chkPdu.ueCntxtRls.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCntxtRls.rx" ,&chkPdu.ueCntxtRls.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"loadInform.tx" ,&chkPdu.loadInform.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"loadInform.rx" ,&chkPdu.loadInform.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"errInd.tx" ,&chkPdu.errInd.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"errInd.rx" ,&chkPdu.errInd.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupRqst.tx" ,&chkPdu.x2SetupRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupRqst.rx" ,&chkPdu.x2SetupRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupFail.tx" ,&chkPdu.x2SetupFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupFail.rx" ,&chkPdu.x2SetupFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetRqst.tx" ,&chkPdu.resetRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetRqst.rx" ,&chkPdu.resetRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetResp.tx" ,&chkPdu.resetResp.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetResp.rx" ,&chkPdu.resetResp.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdRqst.tx" ,&chkPdu.eNBCfgUpdRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdRqst.rx" ,&chkPdu.eNBCfgUpdRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdAck.tx" ,&chkPdu.eNBCfgUpdAck.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdAck.rx" ,&chkPdu.eNBCfgUpdAck.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdFail.tx" ,&chkPdu.eNBCfgUpdFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdFail.rx" ,&chkPdu.eNBCfgUpdFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusRqst.tx" ,&chkPdu.resStatusRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusRqst.rx" ,&chkPdu.resStatusRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusResp.tx" ,&chkPdu.resStatusResp.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusResp.rx" ,&chkPdu.resStatusResp.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusFail.tx" ,&chkPdu.resStatusFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusFail.rx" ,&chkPdu.resStatusFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusUpd.tx" ,&chkPdu.resStatusUpd.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusUpd.rx" ,&chkPdu.resStatusUpd.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeReq.tx" ,&chkPdu.mobChangeReq.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeReq.rx" ,&chkPdu.mobChangeReq.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeAck.tx" ,&chkPdu.mobChangeAck.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeAck.rx" ,&chkPdu.mobChangeAck.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeFail.tx" ,&chkPdu.mobChangeFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeFail.rx" ,&chkPdu.mobChangeFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"rlfIndication.tx" ,&chkPdu.rlfIndication.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"rlfIndication.rx" ,&chkPdu.rlfIndication.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hoReport.tx" ,&chkPdu.hoReport.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hoReport.rx" ,&chkPdu.hoReport.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationReq.tx" ,&chkPdu.cellActvReq.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationReq.rx" ,&chkPdu.cellActvReq.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationRes.tx" ,&chkPdu.cellActvRes.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationRes.rx" ,&chkPdu.cellActvRes.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationFail.tx" ,&chkPdu.cellActvFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationFail.rx" ,&chkPdu.cellActvFail.rx);

         if((chkPdu.hovrRqst.tx            != rcvPdu->hovrRqst.tx           ) ||   
               (chkPdu.hovrRqst.rx           != rcvPdu->hovrRqst.rx            ) ||   
               (chkPdu.hovrReqAck.tx           != rcvPdu->hovrReqAck.tx            ) ||   
               (chkPdu.hovrReqAck.rx           != rcvPdu->hovrReqAck.rx            ) ||   
               (chkPdu.hovrPrepFail.tx        != rcvPdu->hovrPrepFail.tx             ) ||   
               (chkPdu.hovrPrepFail.rx        != rcvPdu->hovrPrepFail.rx             ) ||   
               (chkPdu.sNStatusTfr.tx         != rcvPdu->sNStatusTfr.tx              ) ||   
               (chkPdu.sNStatusTfr.rx         != rcvPdu->sNStatusTfr.rx              ) ||   
               (chkPdu.hovrCancel.tx            != rcvPdu->hovrCancel.tx           ) ||   
               (chkPdu.hovrCancel.rx            != rcvPdu->hovrCancel.rx           ) ||   
               (chkPdu.ueCntxtRls.tx              != rcvPdu->ueCntxtRls.tx             ) ||   
               (chkPdu.ueCntxtRls.rx              != rcvPdu->ueCntxtRls.rx             ) ||   
               (chkPdu.loadInform.tx           != rcvPdu->loadInform.tx          ) ||   
               (chkPdu.loadInform.rx           != rcvPdu->loadInform.rx          ) ||   
               (chkPdu.errInd.tx         != rcvPdu->errInd.tx        ) ||   
               (chkPdu.errInd.rx         != rcvPdu->errInd.rx        ) ||   
               (chkPdu.x2SetupRqst.tx        != rcvPdu->x2SetupRqst.tx       ) ||   
               (chkPdu.x2SetupRqst.rx        != rcvPdu->x2SetupRqst.rx       ) ||   
               (chkPdu.x2SetupFail.tx         != rcvPdu->x2SetupFail.tx        ) ||   
               (chkPdu.x2SetupFail.rx         != rcvPdu->x2SetupFail.rx        ) ||   
               (chkPdu.resetRqst.tx        != rcvPdu->resetRqst.tx       ) ||   
               (chkPdu.resetRqst.rx        != rcvPdu->resetRqst.rx       ) ||   
               (chkPdu.resetResp.tx        != rcvPdu->resetResp.tx       ) ||   
               (chkPdu.resetResp.rx        != rcvPdu->resetResp.rx       ) ||   
               (chkPdu.eNBCfgUpdRqst.tx         != rcvPdu->eNBCfgUpdRqst.tx        ) ||   
               (chkPdu.eNBCfgUpdRqst.rx         != rcvPdu->eNBCfgUpdRqst.rx        ) ||   
               (chkPdu.eNBCfgUpdAck.tx        != rcvPdu->eNBCfgUpdAck.tx       ) ||   
               (chkPdu.eNBCfgUpdAck.rx        != rcvPdu->eNBCfgUpdAck.rx       ) ||   
               (chkPdu.eNBCfgUpdFail.tx    != rcvPdu->eNBCfgUpdFail.tx   ) ||   
               (chkPdu.eNBCfgUpdFail.rx    != rcvPdu->eNBCfgUpdFail.rx   ) ||   
               (chkPdu.resStatusRqst.tx    != rcvPdu->resStatusRqst.tx   ) ||   
               (chkPdu.resStatusRqst.rx    != rcvPdu->resStatusRqst.rx   ) ||   
               (chkPdu.resStatusResp.tx        != rcvPdu->resStatusResp.tx     ) ||   
               (chkPdu.resStatusResp.rx        != rcvPdu->resStatusResp.rx     ) ||   
               (chkPdu.resStatusFail.tx          != rcvPdu->resStatusFail.tx       ) ||   
               (chkPdu.resStatusFail.rx          != rcvPdu->resStatusFail.rx       ) ||   
               (chkPdu.resStatusUpd.tx         != rcvPdu->resStatusUpd.tx      ) ||   
               (chkPdu.resStatusUpd.rx         != rcvPdu->resStatusUpd.rx      ) ||
               (chkPdu.mobChangeReq.tx        != rcvPdu->mobChangeReq.tx       ) ||
               (chkPdu.mobChangeReq.rx        != rcvPdu->mobChangeReq.rx       ) ||
               (chkPdu.mobChangeAck.tx         != rcvPdu->mobChangeAck.tx        ) ||
               (chkPdu.mobChangeAck.rx         != rcvPdu->mobChangeAck.rx        ) ||
               (chkPdu.mobChangeFail.tx        != rcvPdu->mobChangeFail.tx       ) ||
               (chkPdu.mobChangeFail.rx        != rcvPdu->mobChangeFail.rx       ) ||
               (chkPdu.rlfIndication.tx    != rcvPdu->rlfIndication.tx   ) ||
               (chkPdu.rlfIndication.rx    != rcvPdu->rlfIndication.rx   ) ||
               (chkPdu.hoReport.tx    != rcvPdu->hoReport.tx   ) ||
               (chkPdu.hoReport.rx    != rcvPdu->hoReport.rx   ) ||
               (chkPdu.cellActvReq.tx        != rcvPdu->cellActvReq.tx     ) ||
               (chkPdu.cellActvReq.rx        != rcvPdu->cellActvReq.rx     ) ||
               (chkPdu.cellActvRes.tx          != rcvPdu->cellActvRes.tx       ) ||
               (chkPdu.cellActvRes.rx          != rcvPdu->cellActvRes.rx       ) ||
               (chkPdu.cellActvFail.tx         != rcvPdu->cellActvFail.tx      ) ||
               (chkPdu.cellActvFail.rx         != rcvPdu->cellActvFail.rx      )
               )
               {
                  CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsCfm() : Pdu Statistics mismatch\n"));
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkGenSts",&checkGenSts);
   if (checkGenSts == TRUE)
   {
      CzGenSts chkGen;
      CzGenSts *rcvGen;

      rcvGen   =  &czMsg->u.czMngmt.t.sts.u.genSts;
      CMXTA_ZERO(&chkGen, sizeof(CzGenSts));

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"maxNumPeerConn",&chkGen.maxNumPeerConn);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbPeerConnFail",&chkGen.nmbPeerConnected);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbPeerConnFail",&chkGen.nmbPeerConnFail);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbDecErr" ,&chkGen.nmbDecErr);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nmbEncErr" ,&chkGen.nmbEncErr);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"maxMemAlloc",&chkGen.maxMemAlloc);

      
      if((chkGen.maxNumPeerConn      != rcvGen->maxNumPeerConn)||
         (chkGen.nmbPeerConnected  != rcvGen->nmbPeerConnected)||
         (chkGen.nmbPeerConnFail  != rcvGen->nmbPeerConnFail)||
         (chkGen.nmbDecErr    != rcvGen->nmbDecErr)||
         (chkGen.nmbEncErr    != rcvGen->nmbEncErr)||
         (chkGen.maxMemAlloc  != rcvGen->maxMemAlloc))
      {
         CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsCfm() : Gen Statistics mismatch\n"));
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"checkGenPduSts",&checkGenPduSts);
      if(checkGenPduSts == TRUE)
      {

        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrRqst.tx" ,&chkGen.pdu.hovrRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrRqst.rx" ,&chkGen.pdu.hovrRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrReqAck.tx" ,&chkGen.pdu.hovrReqAck.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrReqAck.rx" ,&chkGen.pdu.hovrReqAck.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrPrepFail.tx" ,&chkGen.pdu.hovrPrepFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrPrepFail.rx" ,&chkGen.pdu.hovrPrepFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"sNStatusTfr.tx" ,&chkGen.pdu.sNStatusTfr.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"sNStatusTfr.rx" ,&chkGen.pdu.sNStatusTfr.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrCancel.tx" ,&chkGen.pdu.hovrCancel.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hovrCancel.rx" ,&chkGen.pdu.hovrCancel.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCntxtRls.tx" ,&chkGen.pdu.ueCntxtRls.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCntxtRls.rx" ,&chkGen.pdu.ueCntxtRls.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"loadInform.tx" ,&chkGen.pdu.loadInform.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"loadInform.rx" ,&chkGen.pdu.loadInform.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"errInd.tx" ,&chkGen.pdu.errInd.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"errInd.rx" ,&chkGen.pdu.errInd.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupRqst.tx" ,&chkGen.pdu.x2SetupRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupRqst.rx" ,&chkGen.pdu.x2SetupRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupFail.tx" ,&chkGen.pdu.x2SetupFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"x2SetupFail.rx" ,&chkGen.pdu.x2SetupFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetRqst.tx" ,&chkGen.pdu.resetRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetRqst.rx" ,&chkGen.pdu.resetRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetResp.tx" ,&chkGen.pdu.resetResp.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resetResp.rx" ,&chkGen.pdu.resetResp.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdRqst.tx" ,&chkGen.pdu.eNBCfgUpdRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdRqst.rx" ,&chkGen.pdu.eNBCfgUpdRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdAck.tx" ,&chkGen.pdu.eNBCfgUpdAck.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdAck.rx" ,&chkGen.pdu.eNBCfgUpdAck.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdFail.tx" ,&chkGen.pdu.eNBCfgUpdFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"eNBCfgUpdFail.rx" ,&chkGen.pdu.eNBCfgUpdFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusRqst.tx" ,&chkGen.pdu.resStatusRqst.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusRqst.rx" ,&chkGen.pdu.resStatusRqst.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusResp.tx" ,&chkGen.pdu.resStatusResp.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusResp.rx" ,&chkGen.pdu.resStatusResp.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusFail.tx" ,&chkGen.pdu.resStatusFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusFail.rx" ,&chkGen.pdu.resStatusFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusUpd.tx" ,&chkGen.pdu.resStatusUpd.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"resStatusUpd.rx" ,&chkGen.pdu.resStatusUpd.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeReq.tx" ,&chkGen.pdu.mobChangeReq.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeReq.rx" ,&chkGen.pdu.mobChangeReq.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeAck.tx" ,&chkGen.pdu.mobChangeAck.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeAck.rx" ,&chkGen.pdu.mobChangeAck.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeFail.tx" ,&chkGen.pdu.mobChangeFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"mobChangeFail.rx" ,&chkGen.pdu.mobChangeFail.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"rlfIndication.tx" ,&chkGen.pdu.rlfIndication.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"rlfIndication.rx" ,&chkGen.pdu.rlfIndication.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hoReport.tx" ,&chkGen.pdu.hoReport.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hoReport.rx" ,&chkGen.pdu.hoReport.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationReq.tx" ,&chkGen.pdu.cellActvReq.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationReq.rx" ,&chkGen.pdu.cellActvReq.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationRes.tx" ,&chkGen.pdu.cellActvRes.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationRes.rx" ,&chkGen.pdu.cellActvRes.rx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationFail.tx" ,&chkGen.pdu.cellActvFail.tx);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"cellActivationFail.rx" ,&chkGen.pdu.cellActvFail.rx);

         if(
               (chkGen.pdu.hovrRqst.tx            != rcvGen->pdu.hovrRqst.tx           ) ||   
               (chkGen.pdu.hovrRqst.rx            != rcvGen->pdu.hovrRqst.rx           ) ||   
               (chkGen.pdu.hovrReqAck.tx           != rcvGen->pdu.hovrReqAck.tx            ) ||   
               (chkGen.pdu.hovrReqAck.rx           != rcvGen->pdu.hovrReqAck.rx            ) ||   
               (chkGen.pdu.hovrPrepFail.tx              != rcvGen->pdu.hovrPrepFail.tx             ) ||   
               (chkGen.pdu.hovrPrepFail.rx              != rcvGen->pdu.hovrPrepFail.rx             ) ||   
               (chkGen.pdu.sNStatusTfr.tx               != rcvGen->pdu.sNStatusTfr.tx              ) ||   
               (chkGen.pdu.sNStatusTfr.rx               != rcvGen->pdu.sNStatusTfr.rx              ) ||   
               (chkGen.pdu.hovrCancel.tx            != rcvGen->pdu.hovrCancel.tx           ) ||   
               (chkGen.pdu.hovrCancel.rx            != rcvGen->pdu.hovrCancel.rx           ) ||   
               (chkGen.pdu.ueCntxtRls.tx              != rcvGen->pdu.ueCntxtRls.tx             ) ||   
               (chkGen.pdu.ueCntxtRls.rx              != rcvGen->pdu.ueCntxtRls.rx             ) ||   
               (chkGen.pdu.loadInform.tx           != rcvGen->pdu.loadInform.tx          ) ||   
               (chkGen.pdu.loadInform.rx           != rcvGen->pdu.loadInform.rx          ) ||   
               (chkGen.pdu.errInd.tx         != rcvGen->pdu.errInd.tx        ) ||   
               (chkGen.pdu.errInd.rx         != rcvGen->pdu.errInd.rx        ) ||   
               (chkGen.pdu.x2SetupRqst.tx        != rcvGen->pdu.x2SetupRqst.tx       ) ||   
               (chkGen.pdu.x2SetupRqst.rx        != rcvGen->pdu.x2SetupRqst.rx       ) ||   
               (chkGen.pdu.x2SetupFail.tx         != rcvGen->pdu.x2SetupFail.tx        ) ||   
               (chkGen.pdu.x2SetupFail.rx         != rcvGen->pdu.x2SetupFail.rx        ) ||   
               (chkGen.pdu.resetRqst.tx        != rcvGen->pdu.resetRqst.tx       ) ||   
               (chkGen.pdu.resetRqst.rx        != rcvGen->pdu.resetRqst.rx       ) ||   
               (chkGen.pdu.resetResp.tx        != rcvGen->pdu.resetResp.tx       ) ||   
               (chkGen.pdu.resetResp.rx        != rcvGen->pdu.resetResp.rx       ) ||   
               (chkGen.pdu.eNBCfgUpdRqst.tx         != rcvGen->pdu.eNBCfgUpdRqst.tx        ) ||   
               (chkGen.pdu.eNBCfgUpdRqst.rx         != rcvGen->pdu.eNBCfgUpdRqst.rx        ) ||   
               (chkGen.pdu.eNBCfgUpdAck.tx        != rcvGen->pdu.eNBCfgUpdAck.tx       ) ||   
               (chkGen.pdu.eNBCfgUpdAck.rx        != rcvGen->pdu.eNBCfgUpdAck.rx       ) ||   
               (chkGen.pdu.eNBCfgUpdFail.tx    != rcvGen->pdu.eNBCfgUpdFail.tx   ) ||   
               (chkGen.pdu.eNBCfgUpdFail.rx    != rcvGen->pdu.eNBCfgUpdFail.rx   ) ||   
               (chkGen.pdu.resStatusRqst.tx    != rcvGen->pdu.resStatusRqst.tx   ) ||   
               (chkGen.pdu.resStatusRqst.rx    != rcvGen->pdu.resStatusRqst.rx   ) ||   
               (chkGen.pdu.resStatusResp.tx        != rcvGen->pdu.resStatusResp.tx     ) ||   
               (chkGen.pdu.resStatusResp.rx        != rcvGen->pdu.resStatusResp.rx     ) ||   
               (chkGen.pdu.resStatusFail.tx          != rcvGen->pdu.resStatusFail.tx       ) ||   
               (chkGen.pdu.resStatusFail.rx          != rcvGen->pdu.resStatusFail.rx       ) ||   
               (chkGen.pdu.resStatusUpd.tx         != rcvGen->pdu.resStatusUpd.tx      ) ||   
               (chkGen.pdu.resStatusUpd.rx         != rcvGen->pdu.resStatusUpd.rx      ) ||
               (chkGen.pdu.mobChangeReq.tx        != rcvGen->pdu.mobChangeReq.tx       ) ||
               (chkGen.pdu.mobChangeReq.rx        != rcvGen->pdu.mobChangeReq.rx       ) ||
               (chkGen.pdu.mobChangeAck.tx         != rcvGen->pdu.mobChangeAck.tx        ) ||
               (chkGen.pdu.mobChangeAck.rx         != rcvGen->pdu.mobChangeAck.rx        ) ||
               (chkGen.pdu.mobChangeFail.tx        != rcvGen->pdu.mobChangeFail.tx       ) ||
               (chkGen.pdu.mobChangeFail.rx        != rcvGen->pdu.mobChangeFail.rx       ) ||
               (chkGen.pdu.rlfIndication.tx    != rcvGen->pdu.rlfIndication.tx   ) ||
               (chkGen.pdu.rlfIndication.rx    != rcvGen->pdu.rlfIndication.rx   ) ||
               (chkGen.pdu.hoReport.tx    != rcvGen->pdu.hoReport.tx   ) ||
               (chkGen.pdu.hoReport.rx    != rcvGen->pdu.hoReport.rx   ) ||
               (chkGen.pdu.cellActvReq.tx        != rcvGen->pdu.cellActvReq.tx     ) ||
               (chkGen.pdu.cellActvReq.rx        != rcvGen->pdu.cellActvReq.rx     ) ||
               (chkGen.pdu.cellActvRes.tx          != rcvGen->pdu.cellActvRes.tx       ) ||
               (chkGen.pdu.cellActvRes.rx          != rcvGen->pdu.cellActvRes.rx       ) ||
               (chkGen.pdu.cellActvFail.tx         != rcvGen->pdu.cellActvFail.tx      ) ||
               (chkGen.pdu.cellActvFail.rx         != rcvGen->pdu.cellActvFail.rx      )

               )
               {
                  CMXTA_DBG_ERR((_cmxtap, "czAcHdlStsCfm() : Pdu Statistics mismatch\n"));
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }
          }
      }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlStsCfm */
 
/*
*
*       Fun:   czAcHdlStaReq
*
*       Desc:  Call handler for Transport Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *ssta;
   Pst      pst;
   U8    staType;
 
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlStaReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStaReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStaReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&ssta, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   /* klockwork fix */ 
   if (ssta == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaReq(): ssta is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   staType  = STCZGEN;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "staReqType", &staType);

   if(staType == STCZSCTSAP)
   {
      ssta->t.ssta.s.tSapSta.tSapId =  0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tSapId",  
            &(ssta->t.ssta.s.tSapSta.tSapId ));
   }
   else if(staType == STCZCZTSAP )
   {
      ssta->t.ssta.s.sSapSta.sSapId =  0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sSapId",  
            &(ssta->t.ssta.s.sSapSta.sSapId ));
   }
   else if(staType == STCZSID )
   {
      CMXTA_ALLOC(&ssta->t.ssta.s.sysId.ptNmb, LCZ_MAX_PT_NUM_SIZE);
   }
   else if (staType == STCZPEER)
   {
      ssta->t.ssta.s.peerSta.nmbPeer = 1;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "nmbPeer", &(ssta->t.ssta.s.peerSta.nmbPeer));
      CMXTA_ALLOC(&ssta->t.ssta.s.peerSta.peerStaInfo, (sizeof(CzPeerStaInfo) * ssta->t.ssta.s.peerSta.nmbPeer)); 

      ssta->t.ssta.s.peerSta.peerStaInfo[0].peerId  = 1;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(ssta->t.ssta.s.peerSta.peerStaInfo[0].peerId));
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, staType, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trensport Server Status Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczStaReq(&pst, ssta);
 
   RETVALUE(ROK);
}/* czAcHdlStaReq */
 
/*
*
*       Fun:   czAcHdlStaCfm
*
*       Desc:  Call handler for Status Confirmation from Layer  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   CmStatus       status;
   Txt      dispString[64];
   Pst      pst;
   S16      ret;
   TRC2(czAcHdlStaCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStaCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStaCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

 
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = EVTLCZSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaCfm() : No match, not for this test case\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.czMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   if(status.status == LCM_PRIM_OK)
   {
      switch( czMsg->u.czMngmt.hdr.elmId.elmnt )
      {
         case STCZCZTSAP:
         {
 
            U8 sapState = LCZ_SAP_ISBOUND;
            S16   sapId =  0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "sapId",  &sapId);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapState",  &sapState);

            if (czMsg->u.czMngmt.t.ssta.s.sSapSta.status != sapState)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlsapStaCfm() : sapState \
                        mismatch: exp (%d) rcvd(%d)\n", sapState,
                        czMsg->u.czMngmt.t.ssta.s.sSapSta.status), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
            if (czMsg->u.czMngmt.t.ssta.s.sSapSta.sSapId != sapId)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlsapStaCfm() : sapState \
                        mismatch: exp (%d) rcvd(%d)\n", sapId,
                        czMsg->u.czMngmt.t.ssta.s.sSapSta.sSapId), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case STCZSCTSAP:
         {
 
            U8 sapState = LCZ_SAP_ISBOUND;
            S16   sapId =  0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapId",  &sapId);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapState",  &sapState);
            if (czMsg->u.czMngmt.t.ssta.s.sSapSta.status != sapState)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlsapStaCfm() : sapState \
                        mismatch :exp(%d) rcvd(%d)\n", sapState,
                        czMsg->u.czMngmt.t.ssta.s.sSapSta.status), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
            if (czMsg->u.czMngmt.t.ssta.s.sSapSta.sSapId != sapId)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlsapStaCfm() : sapState \
                        mismatch exp(%d) rcvd(%d)\n", sapId,
                        czMsg->u.czMngmt.t.ssta.s.sSapSta.sSapId), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
 
         }
         break;
         case STCZSID:
         {
            SystemId tmpId;
            tmpId.mVer  =  1;
            tmpId.mRev  =  1;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "mVer",  &(tmpId.mVer));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "mRev",  &(tmpId.mRev));

            if((czMsg->u.czMngmt.t.ssta.s.sysId.mVer != tmpId.mVer)||
               (czMsg->u.czMngmt.t.ssta.s.sysId.mRev != tmpId.mRev))
            {
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlSysIdStaCfm() : Sys Id \
                        values mismatch exp (%d) rcvd (%d)\n", tmpId.mVer,
                        czMsg->u.czMngmt.t.ssta.s.sysId.mVer), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case STCZGEN:
         {
            Cntr tmpActConn =CZAC_LCZ_MAX_PEER;
             

            U16                  tRELOCprep=CMXTA_CZ_500_MSECONDS;        /**< Handover prepration Timer */
            U16                  tX2RELOCOverall=CMXTA_CZ_4_SECONDS;   /**< Handover prepration over all timer*/
            U16                  timeToWait=CMXTA_CZ_4_SECONDS;        /**< Value for the time to wait i*/
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "numActvPeerConn",  &(tmpActConn));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "tRELOCprep",  &(tRELOCprep));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "tX2RELOCOverall",  &(tX2RELOCOverall));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "timeToWait",  &(timeToWait));

            if((czMsg->u.czMngmt.t.ssta.s.genSta.nmbActvPeerConn !=tmpActConn )||
               (czMsg->u.czMngmt.t.ssta.s.genSta.tRELOCprep != tRELOCprep)||
               (czMsg->u.czMngmt.t.ssta.s.genSta.tX2RELOCOverall != tX2RELOCOverall)||
               (czMsg->u.czMngmt.t.ssta.s.genSta.timeToWait != timeToWait))
            {
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlGenStaCfm() : Gen Id values \
                        mismatch : exp(%d) rcvd (%d) \n", timeToWait,
                        czMsg->u.czMngmt.t.ssta.s.genSta.timeToWait), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case STCZPEER:
         {
            CzPeerStaInfo chkInfo;
            CzPeerStaInfo *rcvInfo;

            U8 nmbPeer = 1;
            U8 i = 0;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numPeer",  &(nmbPeer));

            CMXTA_ZERO(&chkInfo, sizeof(CzPeerStaInfo));
            chkInfo.peerId  = 1;

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32   , "peerId",    &(chkInfo.peerId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8    , "peerState", &(chkInfo.peerState));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8    , "assocState", &(chkInfo.assocState));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8    , "tsapState", &(chkInfo.tsapState));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16   , "sapId",&(chkInfo.sapId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32   , "spAssocId", &(chkInfo.spAssocId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32   , "suAssocId", &(chkInfo.suAssocId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL  , "peerENbId", &(chkInfo.peerENbId));
               
            for(i=0; i<nmbPeer; i++)
            {

                  rcvInfo  = &(czMsg->u.czMngmt.t.ssta.s.peerSta.peerStaInfo[i]); 

               if(nmbPeer > 1)
               {  
                  sprintf(dispString,"peerStaInfo_%d_peerId",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32 , dispString, &(chkInfo.peerId));

                  sprintf(dispString,"peerStaInfo_%d_peerState",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8 , dispString, &(chkInfo.peerState));

                  sprintf(dispString,"peerStaInfo_%d_assocState",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8 , dispString, &(chkInfo.assocState));
                  sprintf(dispString,"peerStaInfo_%d_tsapState",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8 , dispString, &(chkInfo.tsapState));
                  sprintf(dispString,"peerStaInfo_%d_sapId",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8 , dispString, &(chkInfo.sapId));
                  sprintf(dispString,"peerStaInfo_%d_spAssocId",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32 , dispString, &(chkInfo.spAssocId));

                  sprintf(dispString,"peerStaInfo_%d_suAssocId",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL , dispString, &(chkInfo.suAssocId));

                  sprintf(dispString,"peerStaInfo_%d_peerENbId",i);
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL , dispString, &(chkInfo.peerENbId));
               }

               if(((rcvInfo->peerId != chkInfo.peerId))||
                  (rcvInfo->peerState != chkInfo.peerState)||
                  (rcvInfo->assocState != chkInfo.assocState)||
                  (rcvInfo->tsapState != chkInfo.tsapState)||
                  (rcvInfo->sapId != chkInfo.sapId)||
                  (rcvInfo->suAssocId != chkInfo.suAssocId)||
                  (rcvInfo->spAssocId != chkInfo.spAssocId)||
                  (rcvInfo->peerENbId != chkInfo.peerENbId))
               {
                  CMXTA_DBG_ERR((_cmxtap, "czAcHdlPeerSta() : Peer values mismatch\n"));
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }

               CMXTA_ZERO(&chkInfo, sizeof(CzPeerStaInfo));
               chkInfo.peerId  = 1;
               
            }
            /* cz001.301 : purify fix : freeing the memorey */
            CMXTA_FREE(czMsg->u.czMngmt.t.ssta.s.peerSta.peerStaInfo, (sizeof(CzPeerStaInfo) * nmbPeer));
            break;
         }
         default:
            break;
      }
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(ROK);
}/* czAcHdlStaCfm */

/*    
*  
*       Fun:   czAcHdlStaInd 
*  
*       Desc:  Call handler for Status Indication 
*  
*       Ret:   S16
*
*       Notes: 
*  
*       File:  czac_lczhdl.c  
*/    
#ifdef ANSI
PUBLIC S16 czAcHdlStaInd
(     
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 czAcHdlStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif 
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret=ROK;
   Bool     validateElem = FALSE;
   S16      element = 0;
   U16      category = 0;
   U16      event = 0;
   U16      cause = 0;
   U16      typeVal=0;
   U32      typeId = 0;
   TRC2(czAcHdlStaInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStaInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif
      
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
      
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
      
   pst.event = EVTLCZSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {     
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }     

   czMsg = (CzAccMsgQElm *)msg->data;

   /*validate the element,alarm category,event and cause*/

   /*validation of element is optional*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"validateElem",&validateElem);
   if(validateElem)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"element",&element);
      if(czMsg->u.czMngmt.hdr.elmId.elmnt != element)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected element\
               %d received %d\n",element,czMsg->u.czMngmt.hdr.elmId.elmnt), 2);
         ret = CMXTA_ERR_INT;
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"category",&(category));
   if(czMsg->u.czMngmt.t.usta.alarm.category != category)
   {
       CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected category\
               %d received %d\n",category,czMsg->u.czMngmt.t.usta.alarm.category), 2);
       ret = CMXTA_ERR_INT;
   }
     
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"event",&(event));
   if(czMsg->u.czMngmt.t.usta.alarm.event != event)
   {
       CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected event\
               %d received %d\n",event,czMsg->u.czMngmt.t.usta.alarm.event), 2);
       ret = CMXTA_ERR_INT;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"cause",&(cause));
   if(czMsg->u.czMngmt.t.usta.alarm.cause != cause)
   {
       CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected cause\
               %d received %d\n",cause,czMsg->u.czMngmt.t.usta.alarm.cause),2);
       ret = CMXTA_ERR_INT;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"type",&(typeVal));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"typeId",&(typeId));
   switch(typeVal)
   {
      case LCZ_USTA_DGNVAL_SAPID:
      {
         if(czMsg->u.czMngmt.t.usta.dgn.u.sapId != (S16)typeId)
         {
#ifdef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected sapId\
                     %d received \
                     %d\n",typeId,czMsg->u.czMngmt.t.usta.dgn.u.sapId ), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected sapId\
                     %ld received \
                     %d\n",typeId,czMsg->u.czMngmt.t.usta.dgn.u.sapId ), 2);
#endif
             ret = CMXTA_ERR_INT;
         }
      }
      break;
      case LCZ_USTA_DGNVAL_UE:
      {
         if(czMsg->u.czMngmt.t.usta.dgn.u.ueInfo.ueId != (U32)typeId)
         {
#ifdef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected ueId\
                     %d received \
                     %d\n",typeId,czMsg->u.czMngmt.t.usta.dgn.u.ueInfo.ueId ),
                     2);
#else
             CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected ueId\
                     %ld received %d\n",typeId,czMsg->u.czMngmt.t.usta.dgn.u.ueInfo.ueId ),  2);
#endif
             ret = CMXTA_ERR_INT;
         }
      }
      break;
      case LCZ_USTA_DGNVAL_PEER:
      {
         if(czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.peerId != (U32)typeId)
         {
#ifdef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected PeerId\
                     %d received %d\n",typeId,czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.peerId ), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,expected PeerId\
                     %ld received %ld\n",typeId,czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.peerId ), 2);
#endif
             ret = CMXTA_ERR_INT;
         }
#ifdef SCT_ENDP_MULTI_IPADDR
         if(czMsg->u.czMngmt.t.usta.alarm.event == LCZ_EVENT_LI_NET_DOWN)
         {
            S8             ipAddress[20];
            CmInetIpAddr   ipAddr = 0;
            U16 addrType;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM,"ipAddrType",
                  &addrType);
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , "ipAddress",
                  ipAddress);
            if(ROK == cmInetAddr(ipAddress,&ipAddr))
            {
               if((czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.dstNAddr.type ==
                        CM_IPV4ADDR_TYPE) )
               {
                  if(czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.dstNAddr.u.ipv4NetAddr
                        !=  ipAddr || (
                           czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.dstNAddr.type
                           != addrType))
                  {
                     /* error */
                     CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed addr type\
                              mismatch\n"),2);
                     ret = CMXTA_ERR_INT;
                  }
               }
#ifdef SB_IPV6_SUPPORTED
               else if((czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.dstNAddr.type
                        == CM_IPV6ADDR_TYPE) )
               {
                  if(czMsg->u.czMngmt.t.usta.dgn.u.peerInfo.dstNAddr.u.ipv6NetAddr
                        !=  ipAddr || (czMsg->u.czMngmt.t.usta.dgn.
                           u.peerInfo.dstNAddr.type != addrType))
                  {
                     /* error */
                     CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed, addr\
                              mismatch\n"),2);
                     ret = CMXTA_ERR_INT;
                  }
               }
#endif
               else
               {
                  /* error */
                  CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,unknown addrType\
                           \n"),2);
                  ret = CMXTA_ERR_INT;
               }
            }
            else
            {
               /* error */
               CMXTA_DBG_CALLIND((_cmxtap, "czAcHdlStaInd() failed,unknown addrType\
                        \n"),2);
               ret = CMXTA_ERR_INT;
            }
         }
#endif
      }
      break;
      default:
         break;
   }

   /*-- Pop the message --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
         
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlStaInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      
   RETVALUE(ret);
}/* czAcHdlStaInd */
 
/*
*
*       Fun:   czAcHdlTrcInd
*
*       Desc:  Call handler for Trace Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   Pst      pst;
   S16      ret;
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlTrcInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlTrcInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlTrcInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
 
   pst.event = EVTLCZTRCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlTrcInd(): No Match, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlTrcInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlTrcInd */

/* 
*
*       Fun:   czAcHdlUSapCntrlReq
*
*       Desc:  Call handler for SSap Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*  
*/  
#ifdef ANSI
PUBLIC S16 czAcHdlUSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 czAcHdlUSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb; 
   
   TRC2(czAcHdlUSapCntrlReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlUSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlUSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlUSapCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildUSapCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZCZTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending SSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlUSapCntrlReq */
 
/*
*
*       Fun:   czAcHdlLSapCntrlReq
*
*       Desc:  Call handler for LSap Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlLSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlLSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlLSapCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlLSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlLSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlLSapCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildLSapCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZSCTSAP,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP TSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlLSapCntrlReq */
 

/*
*
*       Fun:   czAcHdlEndPtCntrlReq
*
*       Desc:  Call handler for End point Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlEndPtCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlEndPtCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlEndPtCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlEndPtCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlEndPtCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlEndPtCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildEndPtCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STTPTSRV,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP TSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlEndPtCntrlReq */
 
/*
*
*       Fun:   czAcHdlAssocCntrlReq
*
*       Desc:  Call handler for Assoc Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlAssocCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlAssocCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlAssocCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlAssocCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlAssocCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlAssocCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildAssocCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID,STASSOC ,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP TSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlAssocCntrlReq */
 
/*
*
*       Fun:   czAcHdlLSapTrcCntrlReq
*
*       Desc:  Call handler for LSap Trace Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlLSapTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlLSapTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlLSapTrcCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlLSapTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlLSapTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlLSapTrcCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildLSapTrcCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZSCTSAP,
                    pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP LSAP Trc Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlLSapTrcCntrlReq */

/*
*
*       Fun:   czAcHdlPNodeTrcCntrlReq
*
*       Desc:  Call handler for PNode Trace Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlPNodeTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlPNodeTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(czAcHdlPNodeTrcCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlPNodeTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlPNodeTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlPNodeTrcCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildPNodeTrcCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZPEER,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending X2AP Peer Trace Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlPNodeTrcCntrlReq */

#ifdef DEBUGP
/*
*
*       Fun:   czAcHdlDebugCntrlReq
*
*       Desc:  Call handler for Debug Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlDebugCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlDebugCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlDebugCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlDebugCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlDebugCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
 
   czAcUtlBuildDebugCntrlReq(tcCb, spCb, cntrl);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   /*-- Write a new function xxUtlHiBuildTSap to fill the data 
        structures and to get information from the XML, for smaller data, all
        the requests may map to a single build function as welll --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlDebugCntrlReq */
#endif

/*
*
*       Fun:   czAcHdlPeerCntrlReq
*
*       Desc:  Call handler for Debug Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlPeerCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlPeerCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
 
   TRC2(czAcHdlPeerCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlPeerCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlPeerCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlPeerCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }

 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   czAcUtlBuildPeerCntrlReq(tcCb, spCb, cntrl);
   /*-- Write a new function xxUtlHiBuildTSap to fill the data 
        structures and to get information from the XML, for smaller data, all
        the requests may map to a single build function as welll --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /*-- Prepare header --*/
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZPEER, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending PeerControl Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlPeerCntrlReq */

/*
*
*       Fun:   czAcHdlUstaCntrlReq
*
*       Desc:  Call handler for Unsoliciated Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlUstaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;

 
   CmXtaTxnCb* txnCb;
   Bool tightCoupled = FALSE;
 
   TRC2(czAcHdlUstaCntrlReq)
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlUstaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlUstaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlUstaCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildUstaCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZGEN, pst.selector);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "element", &(cntrl->hdr.elmId.elmnt));
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Usta Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlUstaCntrlReq */

/*
*
*       Fun:   czAcHdlTrcCntrlReq
*
*       Desc:  Call handler for Unsoliciated Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
 
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlTrcCntrlReq)
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlTrcCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   czAcUtlBuildTrcCntrlReq(tcCb, spCb, cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trc Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlTrcCntrlReq */

/*
*
*       Fun:   czAcHdlCntrlCfm
*
*       Desc:  Call handler for Control confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   TRC2(czAcHdlCntrlCfm);
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCntrlCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czMsg = (CzAccMsgQElm *)msg->data;

   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);
 
   pst.event = EVTLCZCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCntrlCfm() :  No Match, not for this Test Case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCntrlCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.czMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(ROK);
 
}/* czAcHdlCntrlCfm */

/*
*
*       Fun:   czAcHdlShutDownCntrlReq
*
*       Desc:  Call handler for Shutdown Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlShutDownCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CzMngmt  *cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
 
   TRC2(czAcHdlShutDownCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlShutDownCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlShutDownCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ALLOC(&cntrl, sizeof(CzMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* klockwork fix */ 
   if (cntrl == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlShutDownCntrlReq(): cntrl is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
         
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cntrl->t.cntrl.action        = ASHUTDOWN;
   cntrl->t.cntrl.subAction    = SAELMNT;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl->hdr), txnCb->txnId, ENTCZ, CMXTA_INST_ID, STCZGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending ShutDown Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLczCntrlReq(&pst, cntrl);
 
   RETVALUE(ROK);
}/* czAcHdlShutDownCntrlReq */

/*
*
*       Fun:   czAcHdlSctDelay
*
*       Desc:  Call handler for Sct interface delay
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlSctDelay
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSctDelay(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst      entPst;
   Ent      provType;
 
   TRC2(czAcHdlSctDelay);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDelay(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDelay(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Internal command to handle delay --*/
   provType    =  ENTSB;
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
   provType    = ENTHI;
#endif

#ifdef CZAC_INTG_TEST
   RETVALUE(cmXtaHdlIntDelay(tcCb, spCb));
#else
   cmXtaGetPst(&entPst, ENTCZ, CMXTA_INST_ID, provType, CMXTA_INST_ID, 0, 0, FALSE);

   /*-- Check if we are to skip delay command delays --*/
   if (entPst.selector == 0)
   {
      /*-- Just Pass to Internal Delay Handler --*/
      RETVALUE(cmXtaHdlIntDelay(tcCb, spCb));
   }

#endif /* #CZAC_INTG_TEST  */

   CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skipping SCT delay\n"), 3);
   RETVALUE(CMXTA_ERR_NONE);

}/* czAcHdlSctDelay */

/********************************************************************30**

         End of file:     czac_lczhdl.c@@/main/2 - Tue Aug 30 18:35:47 2011

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
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
