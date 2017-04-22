
/********************************************************************20**

     Name:    X2AP

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    cz_lsbhdl.c

     Sid:      czac_lsbhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:27 2015

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
*       Fun:   czAcHdlSbGenCfgReq
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
PUBLIC S16 czAcHdlSbGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbGenCfgReq(tcCb, spCb)
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

   TRC2(czAcHdlSbGenCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbGenCfgReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbGenCfgReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   if ((ret = czAcUtlLsbBldGenCfg(tcCb, spCb, &cfg)) != CMXTA_ERR_NONE)
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

}/* czAcHdlSbGenCfgReq*/


/*
*
*       Fun:   czAcHdlSbTSapCfgReq
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
PUBLIC S16 czAcHdlSbTSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbTSapCfgReq(tcCb, spCb)
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

   TRC2(czAcHdlSbTSapCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapCfgReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapCfgReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   suId = 2;
   spId = 2;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "tSapId", &(suId));
   spId = suId; /*-- The SuId and SpId are taken as same --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if ((ret = czAcUtlLsbBldTSapCfg(tcCb, spCb, suId, spId, &cfg)) != CMXTA_ERR_NONE)
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
}/* czAcHdlSbTSapCfgReq*/


/*
*
*       Fun:   czAcHdlSbSctSapCfgReq
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
PUBLIC S16 czAcHdlSbSctSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbSctSapCfgReq(tcCb, spCb)
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

   TRC2(czAcHdlSbSctSapCfgReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapCfgReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapCfgReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   if ((ret = czAcUtlLsbBldSctSapCfg(tcCb, spCb, 2, &cfg)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

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

}/* czAcHdlSbSctSapCfgReq*/
/*
*
*       Fun:   czAcHdlSbCfgCfm
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
PUBLIC S16 czAcHdlSbCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbCfgCfm(tcCb, spCb)
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
   CzAccMsgQElm  *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(czAcHdlSbCfgCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbCfgCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbCfgCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCfgCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCfgCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCfgCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.sbMgmt.cfm));
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCfgCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbCfgCfm*/

/*
*
*       Fun:   czAcHdlSbUstaCntrlReq
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
PUBLIC S16 czAcHdlSbUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbUstaCntrlReq(tcCb, spCb)
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

   TRC2(czAcHdlSbUstaCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbUstaCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbUstaCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ADISIMM;
   cfg.t.cntrl.subAction = SAUSTA;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask >= CZAC_SB_DBG)
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

}/* czAcHdlSbUstaCntrlReq*/

/*
*
*       Fun:   czAcHdlSbTrcCntrlReq
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
PUBLIC S16 czAcHdlSbTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbTrcCntrlReq(tcCb, spCb)
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

   TRC2(czAcHdlSbTrcCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTrcCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTrcCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ADISIMM;
   cfg.t.cntrl.subAction = SATRC;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask > CZAC_SB_DBG)
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
}/* czAcHdlSbTrcCntrlReq*/

/*
*
*       Fun:   czAcHdlSbTSapCntrlReq
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
PUBLIC S16 czAcHdlSbTSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbTSapCntrlReq(tcCb, spCb)
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

   TRC2(czAcHdlSbTSapCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbTSapCntrlReq*/
/*
*
*       Fun:   czAcHdlSbSctSapCntrlReq
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
PUBLIC S16 czAcHdlSbSctSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbSctSapCntrlReq(tcCb, spCb)
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

   TRC2(czAcHdlSbSctSapCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbSctSapCntrlReq*/

/*
*
*       Fun:   czAcHdlSbDebugCntrlReq
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
PUBLIC S16 czAcHdlSbDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbDebugCntrlReq(tcCb, spCb)
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

   TRC2(czAcHdlSbDebugCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbDebugCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbDebugCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   cfg.t.cntrl.action = ADISIMM;
   cfg.t.cntrl.subAction = SADBG;

#ifdef DEBUGP
   /* Check if TA wants to enable all traces etc*/
   if (cmXtaCb.dbgMask >= CZAC_SB_DBG)
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
}/* czAcHdlSbDebugCntrlReq*/

/*
*
*       Fun:   czAcHdlSbShutDownCntrlReq
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
PUBLIC S16 czAcHdlSbShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbShutDownCntrlReq(tcCb, spCb)
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

   TRC2(czAcHdlSbShutDownCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbShutDownCntrlReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbShutDownCntrlReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbShutDownCntrlReq*/

/*
*
*       Fun:   czAcHdlSbCntrlCfm
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
PUBLIC S16 czAcHdlSbCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbCntrlCfm(tcCb, spCb)
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
   CzAccMsgQElm  *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(czAcHdlSbCntrlCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbCntrlCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbCntrlCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCntrlCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCntrlCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCntrlCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbCntrlCfm*/

/*
*
*       Fun:   czAcHdlSbGenStsReq
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
PUBLIC S16 czAcHdlSbGenStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbGenStsReq(tcCb, spCb)
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

   TRC2(czAcHdlSbGenStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbGenStsReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbGenStsReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbGenStsReq*/

/*
*
*       Fun:   czAcHdlSbSctSapStsReq
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
PUBLIC S16 czAcHdlSbSctSapStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbSctSapStsReq(tcCb, spCb)
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

   TRC2(czAcHdlSbSctSapStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapStsReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapStsReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbSctSapStsReq*/
/*
*
*       Fun:   czAcHdlSbTSapStsReq
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
PUBLIC S16 czAcHdlSbTSapStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbTSapStsReq(tcCb, spCb)
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

   TRC2(czAcHdlSbTSapStsReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapStsReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapStsReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbTSapStsReq*/
/*
*
*       Fun:   czAcHdlSbStsCfm
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
PUBLIC S16 czAcHdlSbStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbStsCfm(tcCb, spCb)
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
   CzAccMsgQElm  *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(czAcHdlSbStsCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbStsCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbStsCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStsCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStsCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStsCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbStsCfm*/
/*
*
*       Fun:   czAcHdlSbSysStaReq
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
PUBLIC S16 czAcHdlSbSysStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbSysStaReq(tcCb, spCb)
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

   TRC2(czAcHdlSbSysStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSysStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSysStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBSID, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbSysStaReq*/
/*
*
*       Fun:   czAcHdlSbSctSapStaReq
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
PUBLIC S16 czAcHdlSbSctSapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbSctSapStaReq(tcCb, spCb)
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

   TRC2(czAcHdlSbSctSapStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbSctSapStaReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbSctSapStaReq*/
/*
*
*       Fun:   czAcHdlSbTSapStaReq
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
PUBLIC S16 czAcHdlSbTSapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbTSapStaReq(tcCb, spCb)
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

   TRC2(czAcHdlSbTSapStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTSapStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbTSapStaReq*/
/*
*
*       Fun:   czAcHdlSbGenStaReq
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
PUBLIC S16 czAcHdlSbGenStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbGenStaReq(tcCb, spCb)
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

   TRC2(czAcHdlSbGenStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbGenStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbGenStaReq() tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSB, CMXTA_INST_ID, STSBGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   /* Send the request to the SCTP */
   (Void) SmMiLsbStaReq(&pst, &cfg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbGenStaReq*/
/*
*
*       Fun:   czAcHdlSbAssocStaReq
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
PUBLIC S16 czAcHdlSbAssocStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbAssocStaReq(tcCb, spCb)
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

   TRC2(czAcHdlSbAssocStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbAssocStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbAssocStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbAssocStaReq*/
/*
*
*       Fun:   czAcHdlSbDtaStaReq
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
PUBLIC S16 czAcHdlSbDtaStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbDtaStaReq(tcCb, spCb)
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

   TRC2(czAcHdlSbDtaStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbDtaStaReq() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbDtaStaReq() tcId (%ld)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(SbMgmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSM, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID);

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
}/* czAcHdlSbDtaStaReq*/
/*
*
*       Fun:   czAcHdlSbStaCfm
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
PUBLIC S16 czAcHdlSbStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbStaCfm(tcCb, spCb)
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
   CzAccMsgQElm  *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(czAcHdlSbStaCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbStaCfm() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbStaCfm() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbStaCfm*/
/*
*
*       Fun:   czAcHdlSbStaInd
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
PUBLIC S16 czAcHdlSbStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbStaInd(tcCb, spCb)
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
   CzAccMsgQElm  *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(czAcHdlSbStaInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbStaInd() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbStaInd() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbStaInd*/
/*
*
*       Fun:   czAcHdlSbTrcInd
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
PUBLIC S16 czAcHdlSbTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 czAcHdlSbTrcInd(tcCb, spCb)
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
   CzAccMsgQElm  *czMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(czAcHdlSbTrcInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTrcInd() tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSbTrcInd() tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbTrcInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   pst.event = LSB_EVTTRCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbTrcInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaPopMsg(&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbTrcInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(czMsg->u.sbMgmt.cfm));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSbTrcInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/* czAcHdlSbTrcInd*/
#endif/*ifdef SB */

/********************************************************************30**

         End of file:     czac_lsbhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:27 2015

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
/main/1      ---        sy       1. LTE-X2AP Initial Release.
/main/2      ---        pt       1. LTE-X2AP 3.1 release.
*********************************************************************91*/
