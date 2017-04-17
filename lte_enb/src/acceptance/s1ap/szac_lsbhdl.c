
/********************************************************************20**

     Name:    S1AP

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    sz_lsbhdl.c

     Sid:      szac_lsbhdl.c@@/main/3 - Mon Jan 10 22:15:48 2011

     Prg:     pk

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

#include "lsb.h"           /* layer management defines for SCTP */
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
#include "sct.h"           /* SB (SCTP) layer */
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */

#include "cm_pasn.h"
#include "cm_xta.h" 

#include "sz.h"            /* defines and macros for S1AP */
#include "szt.h"            /* defines and macros for S1AP */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for S1AP acceptance tests */
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
#include "lsb.x"           /* layer management defines for SCTP */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for S1AP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "sb.x"
#include "lsb.x"
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x" 
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */
#include "szac_lsb.x" 

/*
*
*       Fun:   szAcHdlSbGenCfgReq
*
*       Desc:  Call handler for General Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSbGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbGenCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the GenConfig request.
   *     Default value of "serviceType" is UDP, other value can be RAW
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;
   CmXtaTxnCb *txnCb;
   S16      ret;

   TRC2(szAcHdlSbGenCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbGenCfgReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbGenCfgReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   if ((ret = szAcUtlLsbBldGenCfg(tcCb, spCb, &cfg)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCfgReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);

}/* szAcHdlSbGenCfgReq*/


/*
*
*       Fun:   szAcHdlSbTSapCfgReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSbTSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbTSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the TSap Configuration request.
   *     Default value of "tSapId" is 2
   *     SOAC_ENHANCE: SCT NET address list
   *
   --*/
   SbMgmt      cfg;
   Pst         pst;
   CmXtaTxnCb   *txnCb;
   SuId       suId;
   SpId       spId;
   S16         ret;

   TRC2(szAcHdlSbTSapCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapCfgReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapCfgReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   suId = 2;
   spId = 2;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "tSapId", &(suId));
   spId = suId; /*-- The SuId and SpId are taken as same --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if ((ret = szAcUtlLsbBldTSapCfg(tcCb, spCb, suId, spId, &cfg)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCfgReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbTSapCfgReq*/


/*
*
*       Fun:   szAcHdlSbSctSapCfgReq
*
*       Desc:  Call handler for SSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSbSctSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbSctSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the TSap Configuration request.
   *     Default value of "sSapId" is 2
   *     Default value of "entity" is ENTSO
   *     Default value of "spId" is 2
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   S16      ret;
   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbSctSapCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapCfgReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapCfgReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   if ((ret = szAcUtlLsbBldSctSapCfg(tcCb, spCb, 2, &cfg)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Made route as RTE_PROTO as
    * it needs to be translated in MR */
#ifdef SZ_FTHA
   cfg.t.cfg.s.sctSapCfg.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(cfg.t.cfg.s.sctSapCfg.route));
#endif /* SZ_FTHA */
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "sSapId",  &(cfg.t.cfg.s.sctSapCfg.spId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBSCTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCfgReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);

}/* szAcHdlSbSctSapCfgReq*/
/*
*
*       Fun:   szAcHdlSbCfgCfm
*
*       Desc:  Call handler for configuration confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSbCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Handles Config confirmation
   *     1. Validates if destination of the msg is valid.
   *     2. Remove the msg from the Queue
   *     3. Validates status & reason
   *
   --*/
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm  *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(szAcHdlSbCfgCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbCfgCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbCfgCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbCfgCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.sbMgmt.cfm));
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbCfgCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbCfgCfm*/

/*
*
*       Fun:   szAcHdlSbUstaCntrlReq
*
*       Desc:  Call handler for unsolicited status control request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSbUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbUstaCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the unsolicited status request
   *     Default value of "action" is ADISIMM, If debug mask is on then AENA
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbUstaCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbUstaCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbUstaCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ADISIMM;
   cfg.t.cntrl.subAction = SAUSTA;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask >= SZAC_SB_DBG)
   {
      cfg.t.cntrl.action = AENA;
   }
#endif /*-- DEBUGP --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cfg.t.cntrl.action));


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCntrlReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);

}/* szAcHdlSbUstaCntrlReq*/

/*
*
*       Fun:   szAcHdlSbTrcCntrlReq
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
PUBLIC S16 szAcHdlSbTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbTrcCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the trace control request
   *     Default value of "action" is ADISIMM, If debug mask is on then AENA
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbTrcCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTrcCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTrcCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ADISIMM;
   cfg.t.cntrl.subAction = SATRC;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask > SZAC_SB_DBG)
   {
      cfg.t.cntrl.action = AENA;
   }
#endif /*-- DEBUGP --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(cfg.t.cntrl.action));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCntrlReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbTrcCntrlReq*/

/*
*
*       Fun:   szAcHdlSbTSapCntrlReq
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
PUBLIC S16 szAcHdlSbTSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbTSapCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the TSAP control request
   *     Default value of "tSapId" is 2
   *     Default value of "action" is ABND_ENA
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbTSapCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   cfg.t.cntrl.sapId = 2;
   cfg.t.cntrl.action = ABND_ENA;


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "tSapId",  &(cfg.t.cntrl.sapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cfg.t.cntrl.action));


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCntrlReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbTSapCntrlReq*/
/*
*
*       Fun:   szAcHdlSbSctSapCntrlReq
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
PUBLIC S16 szAcHdlSbSctSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbSctSapCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the SSAP control request
   *     Default value of "sSapId" is 2
   *     Default value of "action" is AENA
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbSctSapCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = AENA;
   cfg.t.cntrl.sapId = 2;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "sSapId",  &(cfg.t.cntrl.sapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cfg.t.cntrl.action));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBSCTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCntrlReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbSctSapCntrlReq*/

/*
*
*       Fun:   szAcHdlSbDebugCntrlReq
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
PUBLIC S16 szAcHdlSbDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbDebugCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the debug control request
   *     Default value of "action" is ADISIMM, If debug mask is on then AENA
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbDebugCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbDebugCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbDebugCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ADISIMM;
   cfg.t.cntrl.subAction = SADBG;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask >= SZAC_SB_DBG)
   {
      cfg.t.cntrl.action = AENA;
   }
#endif /*-- DEBUGP --*/

#ifdef DEBUGP
   cfg.t.cntrl.dbgMask = (U32)(DBGMASK_SI|DBGMASK_MI|DBGMASK_UI);
   cfg.t.cntrl.dbgMask = 0xfffffdff;
#endif /*-- DEBUGP --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cfg.t.cntrl.action));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCntrlReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbDebugCntrlReq*/

/*
*
*       Fun:   szAcHdlSbShutDownCntrlReq
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
PUBLIC S16 szAcHdlSbShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbShutDownCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the shutdown control request
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbShutDownCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbShutDownCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbShutDownCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ASHUTDOWN;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbCntrlReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbShutDownCntrlReq*/

/*
*
*       Fun:   szAcHdlSbCntrlCfm
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
PUBLIC S16 szAcHdlSbCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbCntrlCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Handles Control confirmation
   *     1. Validates if destination of the msg is valid.
   *     2. Remove the msg from the Queue
   *     3. Validates status & reason
   *
   --*/
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm  *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(szAcHdlSbCntrlCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbCntrlCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbCntrlCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbCntrlCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbCntrlCfm*/

/*
*
*       Fun:   szAcHdlSbGenStsReq
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
PUBLIC S16 szAcHdlSbGenStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbGenStsReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the general statistics request
   *     Default value of "action" is ZEROSTS
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;
   Action  action;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbGenStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbGenStsReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbGenStsReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   action = ZEROSTS;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(action));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStsReq(&pst, action, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbGenStsReq*/

/*
*
*       Fun:   szAcHdlSbSctSapStsReq
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
PUBLIC S16 szAcHdlSbSctSapStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbSctSapStsReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the SCT SAP statistics request
   *     Default value of "action" is ZEROSTS
   *     Default value of "sSapId" is 2
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;
   Action  action;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbSctSapStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapStsReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapStsReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cfg.t.sts.sapId = 2;
   action = ZEROSTS;


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "sSapId",  &(cfg.t.sts.sapId));


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBSCTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStsReq(&pst, action, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbSctSapStsReq*/
/*
*
*       Fun:   szAcHdlSbTSapStsReq
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
PUBLIC S16 szAcHdlSbTSapStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbTSapStsReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the TSAP statistics request
   *     Default value of "action" is ZEROSTS
   *     Default value of "tSapId" is 2
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;
   Action  action;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbTSapStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapStsReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapStsReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cfg.t.sts.sapId = 2;
   action = ZEROSTS;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "tSapId",  &(cfg.t.sts.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStsReq(&pst, action, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbTSapStsReq*/
/*
*
*       Fun:   szAcHdlSbStsCfm
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
PUBLIC S16 szAcHdlSbStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbStsCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Handles statistics confirmation
   *     1. Validates if destination of the msg is valid.
   *     2. Remove the msg from the Queue
   *     3. Validates status & reason
   *
   --*/
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm  *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(szAcHdlSbStsCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbStsCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbStsCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbStsCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbStsCfm*/
/*
*
*       Fun:   szAcHdlSbSysStaReq
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
PUBLIC S16 szAcHdlSbSysStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbSysStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the System Status request
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbSysStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSysStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSysStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBSID, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbSysStaReq*/
/*
*
*       Fun:   szAcHdlSbSctSapStaReq
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
PUBLIC S16 szAcHdlSbSctSapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbSctSapStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the SSAP Status request
   *     Default value of "sSapId" is 2
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbSctSapStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbSctSapStaReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cfg.t.ssta.sapId = 2;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "sSapId",  &(cfg.t.ssta.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBSCTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbSctSapStaReq*/
/*
*
*       Fun:   szAcHdlSbTSapStaReq
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
PUBLIC S16 szAcHdlSbTSapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbTSapStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the debug Status request
   *     Default value of "tSapId" is 2
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbTSapStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTSapStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cfg.t.ssta.sapId = 2;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "tSapId",  &(cfg.t.ssta.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBTSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbTSapStaReq*/
/*
*
*       Fun:   szAcHdlSbGenStaReq
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
PUBLIC S16 szAcHdlSbGenStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbGenStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the gen Status request
   *     Default value of "action" is ADISIMM, If debug mask is on then AENA
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbGenStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbGenStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbGenStaReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbGenStaReq*/
/*
*
*       Fun:   szAcHdlSbAssocStaReq
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
PUBLIC S16 szAcHdlSbAssocStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbAssocStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the Assoc Status request
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbAssocStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbAssocStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbAssocStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cfg.t.ssta.s.assocSta.assocId = 0; /*-- SOAC_ENHANCE --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocId",  &(cfg.t.ssta.s.assocSta.assocId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBASSOC, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbAssocStaReq*/
/*
*
*       Fun:   szAcHdlSbDtaStaReq
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
PUBLIC S16 szAcHdlSbDtaStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbDtaStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Builds the Destination Address Status request
   *
   --*/
   SbMgmt  cfg;
   Pst      pst;

   CmXtaTxnCb *txnCb;

   TRC2(szAcHdlSbDtaStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbDtaStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbDtaStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBDTA, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbDtaStaReq*/
/*
*
*       Fun:   szAcHdlSbStaCfm
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
PUBLIC S16 szAcHdlSbStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Handles Status confirmation
   *     1. Validates if destination of the msg is valid.
   *     2. Remove the msg from the Queue
   *     3. Validates status & reason
   *
   --*/
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm  *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(szAcHdlSbStaCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbStaCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbStaCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbStaCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbStaCfm*/
/*
*
*       Fun:   szAcHdlSbStaInd
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
PUBLIC S16 szAcHdlSbStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Handles Status Indication
   *     1. Validates if destination of the msg is valid.
   *     2. Remove the msg from the Queue
   *     3. Validates status & reason
   *
   --*/
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm  *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(szAcHdlSbStaInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbStaInd() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbStaInd() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbStaInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbStaInd*/
/*
*
*       Fun:   szAcHdlSbTrcInd
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
PUBLIC S16 szAcHdlSbTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 szAcHdlSbTrcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /*--
   *     Usage:
   *     Handles Trace Indication
   *     1. Validates if destination of the msg is valid.
   *     2. Remove the msg from the Queue
   *     3. Validates status & reason
   *
   --*/
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm  *szMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(szAcHdlSbTrcInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTrcInd() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSbTrcInd() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTTRCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbTrcInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(szMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSbTrcInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* szAcHdlSbTrcInd*/


/********************************************************************30**

         End of file:     szac_lsbhdl.c@@/main/3 - Mon Jan 10 22:15:48 2011

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
