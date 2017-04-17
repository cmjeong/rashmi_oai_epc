
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_leghdl.c

     Sid:      egac_leghdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:35 2015

     Prg:     an
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

#include "eg_edm.h"        /* EDM Module structures            */
#include "leg.h"           /* layer management defines for EGCP */
#include "eg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

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
#include "cm_dns.x"         /* common DNS libraru defines */

#include "egt.x"           /* EGT Interface Structures */
#include "leg.x"           /* layer management typedefs for EGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for EGCP */
#include "eg_tpt.x"            /* EGTP TPT module defines */

#include "egac_acc.x"        /* typedefs for EGCP acceptance tests */
#include "egac_leg.x"
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"
#endif
/*ccpu00136421:purecov fix */
EXTERN PUBLIC SpId egAcDmSmGetTSapIdFromProt(U8 protType);

/*
*
*       Fun:   egAcHdlGenCfgReq
*
*       Desc:  Call handler for General Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cfg;
   Pst      pst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

   CmXtaTxnCb* txnCb;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlGenCfgReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   cmMemset((U8*)&(egAccCb.egAcMsgInfo), 0,
                 (sizeof(EgAcEgtMsgInfo) * EGAC_MAX_PROCS * EGAC_LEG_MAX_TRANSID));
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildGenCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));
 
 
   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* egAcHdlGenCfgReq */
 
/*
*
*       Fun:   egAcHdlUSapCfgReq
*
*       Desc:  Call handler for SSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlUSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlUSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlUSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlUSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlUSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildUSapCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGUSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending eGTP USAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* egAcHdlUSapCfgReq */
 
 
 
/*
*
*       Fun:   egAcHdlLSapCfgReq
*
*       Desc:  Call handler for TSAP Cfg Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlLSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlLSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlLSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlLSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlLSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildLSapCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGTSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TSAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* egAcHdlLSapCfgReq */
 
/*
*
*       Fun:   egAcHdlTServerCfgReq
*
*       Desc:  Call handler for Transport server Cfg Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlTServerCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlTServerCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlTServerCfgReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTServerCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTServerCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildTServerCfgReq(tcCb, spCb, &cfg);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGSRVR, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending TPT Server Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &cfg);

   /*-- eg006.201: Avoid mem leak by freeing memory allocated for hostname --*/
   egFree((Data*)cfg.u.cfg.s.tptSrv.hostName.val, cfg.u.cfg.s.tptSrv.hostName.len);

   RETVALUE(ROK);
} 

/*
*
*       Fun:   egAcHdlCfgCfm
*
*       Desc:  Call handler for configuration conformation 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlCfgCfm)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlCfgCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

 
   pst.event = EVTLEGCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   /* eg012.201: check condition added for return */
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egMsg->u.egMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

/* eg001.102 Multithreaded performance changes gaurded under SS_MT_CB flag. */
#ifdef EGTP_U 
   if(egMsg->u.egMngmt.cfm.status != ROK && egMsg->u.egMngmt.hdr.elmId.elmnt == STEGIPADDR)
	{
		 SPutSBuf(msg->pst.region, msg->pst.pool, (Data* )egMsg->u.egMngmt.u.cfg.s.ipAddr.ipInfo,
		              (Size)(sizeof(EgIpInfo) * egMsg->u.egMngmt.u.cfg.s.ipAddr.nmbIpAddr));
	}
#endif /* EGTPU */
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlCfgCfm */

/*  
*
*       Fun:   egAcHdlStsReq
*
*       Desc:  Call handler for  Statistics Request 
*   
*       Ret:   ROK
*  
*       Notes: None
*              
*       File:  egac_leghdl.c
*  
*/ 
#ifdef ANSI
PUBLIC S16 egAcHdlStsReq
(  
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   U8 stsType;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   Txt          ipAddr[50];
#ifdef EGTP_U
   U16          port;
   S16          ret = 0;
#endif 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlStsReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStsReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStsReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&sts, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   action  = EGAC_DFLT_STS_ACTION;
   stsType = EGAC_DFLT_STS_TYPE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, (Txt  *)"action",  &action);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt  *)"stsType",&stsType);

   CMXTA_ZERO(ipAddr, 50 );

   switch(stsType)
   {
      case STEGGEN:
             break;

      case STEGUSAP:
             sts.u.sts.s.usap.sapId = EGAC_DFLT_SPID_UCFG;
             cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,(Txt  *)"sapId",
                                                      &(sts.u.sts.s.usap.sapId));
             break;
      case STEGTSAP:
             sts.u.sts.s.tsap.sapId = EGAC_DFLT_SPID_LCFG;
             cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,(Txt  *)"sapId",
                                                      &(sts.u.sts.s.tsap.sapId));
             break;

#ifdef EGTP_U
     case STEGIPADDR:
             /***************************
              * Get the IP Address type *
              * ************************/
             sts.u.sts.s.ipSts.spId = 0;  
             sts.u.sts.s.ipSts.IpAddr.type = EGAC_DFLT_ADDR_TYPE;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"addrType",
                                               &(sts.u.sts.s.ipSts.IpAddr.type));

             /***************************
              * Get the port number     *
              * ************************/
             sts.u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.port = EGAC_DFLT_PORT;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"port", &(port));

             /*******************************
              * Get the IP address for IPV4 *
              * ****************************/
             if(sts.u.sts.s.ipSts.IpAddr.type == CM_TPTADDR_IPV4)
             {    
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,
                                      (Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(sts.u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.address));
                 }
                 else
                 {
                      cmInetAddr ( (S8 *)ipAddr, &(sts.u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.address));
                 }     
                 sts.u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.port    = port;
                 sts.u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.address =
                                       CM_INET_NTOH_U32(sts.u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.address);
              }
#ifdef IPV6_SUPPORTED               
             /*******************************
              * Get the IP address for IPV6 *
              * ****************************/
              else
              {
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                              &(sts.u.sts.s.ipSts.IpAddr.u.ipv6TptAddr.ipv6NetAddr));
                 }
                 else
                 {
                      cmInetPton6 (&sts.u.sts.s.ipSts.IpAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
                 }     

                 sts.u.sts.s.ipSts.IpAddr.u.ipv6TptAddr.port = port;
              }
#endif   
             /*******************
              * Get SAP Id      *
              * ****************/
             sts.u.sts.s.ipSts.spId = EGAC_LEG_DFLT_SPID;
             cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,(Txt  *)"spId",
                                                      &(sts.u.sts.s.ipSts.spId));

             break;                                   
     case STEGSRVR:
             /*******************
              * Get SAP Id      *
              * ****************/
             sts.u.sts.s.tptSrvrSts.spId = EGAC_LEG_DFLT_SPID;
             cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,(Txt  *)"spId",
                                                      &(sts.u.sts.s.tptSrvrSts.spId));
             
             /***************************
              * Get the IP Address type *
              * ************************/
             sts.u.sts.s.tptSrvrSts.lclAddr.type = EGAC_DFLT_ADDR_TYPE;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"addrType",
                                               &(sts.u.sts.s.tptSrvrSts.lclAddr.type));

             /***************************
              * Get the port number     *
              * ************************/
             sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.port = EGAC_DFLT_PORT;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"port", &(port));

             /*******************************
              * Get the IP address for IPV4 *
              * ****************************/
             if(sts.u.sts.s.tptSrvrSts.lclAddr.type == CM_TPTADDR_IPV4)
             {    
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,
                                      (Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.address));
                 }
                 else
                 {
                      cmInetAddr ( (S8 *)ipAddr, &(sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.address));
                 }     
                 sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.port    = port;
                 sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.address =
                                       CM_INET_NTOH_U32(sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.address);
              }
#ifdef IPV6_SUPPORTED               
             /*******************************
              * Get the IP address for IPV6 *
              * ****************************/
              else
              {
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                              &(sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv6TptAddr.ipv6NetAddr));
                 }
                 else
                 {
                      cmInetPton6 (&sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
                 }     

                 sts.u.sts.s.tptSrvrSts.lclAddr.u.ipv6TptAddr.port = port;
              }
#endif   
             break;                                   

     case STEGTNL:
             /********************************
              * Get Tunnel Id                *
              * *****************************/
             sts.u.sts.s.tnlSts.teId = EGUAC_DFLT_TEID;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"teid",
                                               &(sts.u.sts.s.tnlSts.teId));
             /*******************
              * Get SAP Id      *
              * ****************/
             sts.u.sts.s.tnlSts.spId = EGUAC_DFLT_SPID_TNLCFG;
             cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,(Txt  *)"spId",
                                                      &(sts.u.sts.s.tnlSts.spId));
             /**************************
              * For Source IP Address  *
              * ***********************/
             /***************************
              * Get the IP Address type *
              * ************************/
             sts.u.sts.s.tnlSts.srcIpAddr.type = EGAC_DFLT_ADDR_TYPE;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"addrType",
                                               &(sts.u.sts.s.tnlSts.srcIpAddr.type));

             /***************************
              * Get the port number     *
              * ************************/
             sts.u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.port = EGAC_DFLT_PORT;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"port", &(port));

             /**************************************
              * Get the Source IP address for IPV4 *
              * ***********************************/
             if(sts.u.sts.s.tnlSts.srcIpAddr.type == CM_TPTADDR_IPV4)
             {    
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,
                                      (Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(sts.u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.address));
                 }
                 else
                 {
                      cmInetAddr ( (S8 *)ipAddr, &(sts.u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.address));
                 }     
                 sts.u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.port    = port;
                 sts.u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.address =
                                       CM_INET_NTOH_U32(sts.u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.address);
              }
#ifdef IPV6_SUPPORTED               
             /**************************************
              * Get the Source IP address for IPV6 *
              * ***********************************/
              else
              {
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                              &(sts.u.sts.s.tnlSts.srcIpAddr.u.ipv6TptAddr.ipv6NetAddr));
                 }
                 else
                 {
                      cmInetPton6 (&sts.u.sts.s.tnlSts.srcIpAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
                 }     

                 sts.u.sts.s.tnlSts.srcIpAddr.u.ipv6TptAddr.port = port;
              }
#endif   
             CMXTA_ZERO(ipAddr, 50 );
             /*******************************
              * For Destination IP Address  *
              * ****************************/
             /***************************
              * Get the IP Address type *
              * ************************/
             sts.u.sts.s.tnlSts.destIpAddr.type = EGAC_DFLT_ADDR_TYPE;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"addrType",
                                               &(sts.u.sts.s.tnlSts.destIpAddr.type));

             /***************************
              * Get the port number     *
              * ************************/
             sts.u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.port = EGAC_DFLT_PORT;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"port", &(port));

             /**************************************
              * Get the Source IP address for IPV4 *
              * ***********************************/
             if(sts.u.sts.s.tnlSts.destIpAddr.type == CM_TPTADDR_IPV4)
             {    
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,
                                      (Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(sts.u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.address));
                 }
                 else
                 {
                      cmInetAddr ( (S8 *)ipAddr, &(sts.u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.address));
                 }     
                 sts.u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.port    = port;
                 sts.u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.address =
                                       CM_INET_NTOH_U32(sts.u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.address);
              }
#ifdef IPV6_SUPPORTED               
             /*******************************************
              * Get the Destination IP address for IPV6 *
              * ****************************************/
              else
              {
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                              &(sts.u.sts.s.tnlSts.destIpAddr.u.ipv6TptAddr.ipv6NetAddr));
                 }
                 else
                 {
                      cmInetPton6 (&sts.u.sts.s.tnlSts.destIpAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
                 }     

                 sts.u.sts.s.tnlSts.destIpAddr.u.ipv6TptAddr.port = port;
              }
#endif   
             break;                                   

#ifdef EGTP_U_MULTI_THREADED
     case STEGTHRD:
             break;                                   
#endif
#endif /* EGTP_U */
     default:
             CMXTA_DBG_ERR((_cmxtap,"egAcHdlStsReq() Invalid Statistics Type \n"));
             break;
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, stsType, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegStsReq(&pst, action, &sts);
 
   RETVALUE(ROK);
}/* egAcHdlStsReq */

/*
*
*       Fun:   egAcHdlStsCfm
*
*       Desc:  Call handler for Statistics Confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Bool     checkGenSts = FALSE;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   U8 egtpMsgType; 
   U8 txCount;
   U8 rxCount; 
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlStsCfm)
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStsCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStsCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlStsCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   egtpMsgType = 0; 
   txCount = 0;
   rxCount = 0; 
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"egtpMsgType", &egtpMsgType);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"txCount", &txCount); 
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"rxCount", &rxCount); 
   pst.event = EVTLEGSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStsCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
  /*eg012.201: check condition added for return */
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egMsg->u.egMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   if(egtpMsgType)
   {
     if(egMsg->u.egMngmt.u.sts.s.tsap.msgType[egtpMsgType].Tx != txCount)
     {
        CMXTA_DBG_ERR((_cmxtap, "egAcHdlStsCfm() : count mismatch\n"));
        cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
        RETVALUE(CMXTA_ERR_INT);
     } 

     if(egMsg->u.egMngmt.u.sts.s.tsap.msgType[egtpMsgType].Rx != rxCount)
     {
        CMXTA_DBG_ERR((_cmxtap, "egAcHdlStsCfm() : count mismatch\n"));
        cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
        RETVALUE(CMXTA_ERR_INT);
     } 
   }
#ifdef EGTP_U_MULTI_THREADED
   if(egMsg->u.egMngmt.hdr.elmId.elmnt == STEGTHRD)
      displayThreadStsInfo(egMsg->u.egMngmt.u.sts.s.thrdSts);
#endif
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"checkPeerSts",&checkGenSts);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"checkGenSts",&checkGenSts);

  /* ccpu00136421:memory leak fix */
  if(egMsg->u.egMngmt.u.sts.s.ipSts.portsLst!=NULLP)
  {
     egFree((Data*)(egMsg->u.egMngmt.u.sts.s.ipSts.portsLst), sizeof(U32));
  }
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlStsCfm */

#ifdef EGTP_U_MULTI_THREADED
/*
 * *
 * *       Fun:   displayThreadStsInfo
 * *
 * *       Desc:  Call handler for Statistics Confirm
 * *
 * *       Ret:   ROK
 * *
 * *       Notes: None
 * *
 * *       File:  egac_leghdl.c
 * *
 * */
#ifdef ANSI
PUBLIC Void displayThreadStsInfo
(
 EgThrdSts thrdSts
 )
#else
PUBLIC Void displayThreadStsInfo(thrdSts)
 EgThrdSts thrdSts;
#endif
{
   U8 i;

   /*-- eg003.201: changes from eg006.102 --*/
	EG_TRC2(displayThreadStsInfo)
   for(i=0; i< thrdSts.nmbThrd; i++)
   {
       printf("Stastics fo thread %d\n", i);
       printf("\n=====================\n");
   /*-- eg003.201 : 64 Bit alignment change from eg006.102 --*/
#ifdef ALIGN_64BIT
       printf("Thread ID = %d\n",thrdSts.threadInfo[i].thrId);
       printf("Total Messag Txed = %d\n",thrdSts.threadInfo[i].totalMsgsTx);
       printf("Total meaasge Rxed = %d\n",thrdSts.threadInfo[i].totalMsgsRx);
       printf("No of Reordering Tunnels = %d\n",thrdSts.threadInfo[i].nmbOfReorderTnl);
#else
       printf("Thread ID = %ld\n",thrdSts.threadInfo[i].thrId);
       printf("Total Messag Txed = %ld\n",thrdSts.threadInfo[i].totalMsgsTx);
       printf("Total meaasge Rxed = %ld\n",thrdSts.threadInfo[i].totalMsgsRx);
       printf("No of Reordering Tunnels = %ld\n",thrdSts.threadInfo[i].nmbOfReorderTnl);
#endif /* ALIGN_64BIT */
       printf("\n=====================\n");
   }
   egFree((Data*)thrdSts.threadInfo,(sizeof(EgThrStsInfo)) * egCb.genCfg.nmbWorkerThread);
	RETVOID;
}
#endif
/*
*
*       Fun:   egAcHdlStaReq
*
*       Desc:  Call handler for Transport Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  ssta;
   Pst      pst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   U8           staType;
   Txt          ipAddr[50];
#ifdef EGTP_U
   U16          port = 0;
   S16          ret = 0;
#endif 
   CmXtaTxnCb* txnCb;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlStaReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStaReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStaReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&ssta, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   staType  = EGAC_DFLT_STA_TYPE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"staType", &staType);

   CMXTA_ZERO(ipAddr, 50 );

   switch(staType)
   {
     case STEGGEN:
     case STEGSID:
             break;
     case STEGUSAP:
             ssta.u.ssta.s.uSapSta.uSapId = EGAC_DFLT_SPID_UCFG;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"sapId",
                                               &(ssta.u.ssta.s.uSapSta.uSapId));
             break;
     case STEGTSAP:
             ssta.u.ssta.s.tSapSta.tSapId = EGAC_DFLT_SPID_LCFG;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"sapId",
                                               &(ssta.u.ssta.s.tSapSta.tSapId));
             break;

#ifdef EGTP_U
     case STEGSRVR:
             /*******************
              * Get the SAP ID  *
              * ****************/
             ssta.u.ssta.s.tSrvrSta.tSapId = EGUAC_DFLT_SPID_TCFG;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"sapId",
                                               &(ssta.u.ssta.s.tSrvrSta.tSapId));

             /*************************
              * Get the TPT ServerID  *
              * **********************/
             ssta.u.ssta.s.tSrvrSta.tptSrvId = EGAC_DFLT_TPT_SRV_ID;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"tptSrvId",
                                               &(ssta.u.ssta.s.tSrvrSta.tptSrvId));
             break;                                   

     case STEGTNL:
             /*********************
              * Get the TEID      *
              * ******************/
             ssta.u.ssta.s.tnlSta.teId = EGUAC_DFLT_TEID;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"teid",
                                               &(ssta.u.ssta.s.tnlSta.teId));
             /*******************
              * Get the SAP ID  *
              * ****************/
             ssta.u.ssta.s.tnlSta.spId = EGUAC_DFLT_SPID_TNLCFG;
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",
                                               &(ssta.u.ssta.s.tnlSta.spId));
             /**************************
              * For Source IP Address  *
              * ***********************/
             /***************************
              * Get the IP Address type *
              * ************************/
             ssta.u.ssta.s.tnlSta.srcIpAddr.type = EGAC_DFLT_ADDR_TYPE;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"addrType",
                                               &(ssta.u.ssta.s.tnlSta.srcIpAddr.type));

             /***************************
              * Get the port number     *
              * ************************/
             ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv4TptAddr.port = 0;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"port", &(port));

             /**************************************
              * Get the Source IP address for IPV4 *
              * ***********************************/
             if(ssta.u.ssta.s.tnlSta.srcIpAddr.type == CM_TPTADDR_IPV4)
             {    
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,
                                      (Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv4TptAddr.address));
                 }
                 else
                 {
                      cmInetAddr ( (S8 *)ipAddr, &(ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv4TptAddr.address));
                 }     
                 ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv4TptAddr.port    = port;
                 ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv4TptAddr.address =
                                       CM_INET_NTOH_U32(ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv4TptAddr.address);
              }
#ifdef IPV6_SUPPORTED               
             /**************************************
              * Get the Source IP address for IPV6 *
              * ***********************************/
              else
              {
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                              &(ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv6TptAddr.ipv6NetAddr));
                 }
                 else
                 {
                      cmInetPton6 (&ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
                 }     

                 ssta.u.ssta.s.tnlSta.srcIpAddr.u.ipv6TptAddr.port = port;
              }
#endif   
             CMXTA_ZERO(ipAddr, 50 );
             /**************************
              * For dest IP Address    *
              * ***********************/
             /***************************
              * Get the IP Address type *
              * ************************/
             ssta.u.ssta.s.tnlSta.destIpAddr.type = EGAC_DFLT_ADDR_TYPE;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"addrType",
                                               &(ssta.u.ssta.s.tnlSta.destIpAddr.type));

             /***************************
              * Get the port number     *
              * ************************/
             ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv4TptAddr.port = 0;  
             cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"port", &(port));

             /**************************************
              * Get the Source IP address for IPV4 *
              * ***********************************/
             if(ssta.u.ssta.s.tnlSta.destIpAddr.type == CM_TPTADDR_IPV4)
             {    
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,
                                      (Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv4TptAddr.address));
                 }
                 else
                 {
                      cmInetAddr ( (S8 *)ipAddr, &(ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv4TptAddr.address));
                 }     
                 ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv4TptAddr.port    = port;
                 ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv4TptAddr.address =
                                       CM_INET_NTOH_U32(ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv4TptAddr.address);
              }
#ifdef IPV6_SUPPORTED               
             /**************************************
              * Get the Source IP address for IPV6 *
              * ***********************************/
              else
              {
                 ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"ipAddr",&(ipAddr));
                 if(ret == CMXTA_ERR_NO_VALUE)
                 {
                      cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                              &(ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv6TptAddr.ipv6NetAddr));
                 }
                 else
                 {
                      cmInetPton6 (&ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
                 }     

                 ssta.u.ssta.s.tnlSta.destIpAddr.u.ipv6TptAddr.port = port;
              }
#endif   
             break;                                   

#endif
             
     default:
             CMXTA_DBG_ERR((_cmxtap,"egAcHdlStaReq() Invalid Status Type \n"));
             break;
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, staType, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trensport Server Status Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegStaReq(&pst, &ssta);
 
   RETVALUE(ROK);
}/* egAcHdlStaReq */
 
/*
*
*       Fun:   egAcHdlStaCfm
*
*       Desc:  Call handler for Status Confirmation from Layer  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlStaCfm) 

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStaCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStaCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   pst.event = EVTLEGSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaCfm() : No match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   /*eg012.201: check condition added for return */
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egMsg->u.egMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlStaCfm */

/*    
*  
*       Fun:   egAcHdlStaInd 
*  
*       Desc:  Call handler for Status Indication 
*  
*       Ret:   S16
*
*       Notes: 
*  
*       File:  egac_leghdl.c  
*/    
#ifdef ANSI
PUBLIC S16 egAcHdlStaInd
(     
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 egAcHdlStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif 
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   Pst      pst;
   S16      ret=ROK;
   Bool     validateElem = FALSE;
   S16      element = 0;
   U16      category = 0;
   U16      event = 0;
   U16      cause = 0;
   U16      type=0;
   U32      typeId = 0;

#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlStaInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStaInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif
      
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
      
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
      
   pst.event = EVTLEGSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {     
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }     

   egMsg = (EgAccMsgQElm *)msg->data;

   /*validate the element,alarm category,event and cause*/

   /*validation of element is optional*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"validateElem",&validateElem);
   if(validateElem)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,(Txt  *)"element",&element);
      if(egMsg->u.egMngmt.hdr.elmId.elmnt != element)
      {
         CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaInd() failed,expected element\
                 %d received %d\n",element,egMsg->u.egMngmt.hdr.elmId.elmnt));
         ret = CMXTA_ERR_INT;
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,(Txt  *)"category",&(category));
    
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,(Txt  *)"event",&(event));
   

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,(Txt  *)"cause",&(cause));
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,(Txt  *)"type",&(type));
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"typeId",&(typeId));

   if(egMsg->u.egMngmt.u.usta.alarm.category != category)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaInd() : category mismatch\n"));
      ret = CMXTA_ERR_INT;
   }
   else if(egMsg->u.egMngmt.u.usta.alarm.event != event)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaInd() : event mismatch\n"));
      ret = CMXTA_ERR_INT;
   }
/*
   else if(egMsg->u.egMngmt.u.usta.alarm.cause != cause)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaInd() : cause mismatch\n"));
      ret = CMXTA_ERR_INT;
   }*/
   else if(egMsg->u.egMngmt.u.usta.dgn.dgnVal[0].type != type)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaInd() : dgn type mismatch\n"));
      ret = CMXTA_ERR_INT;
   }
   else if(egMsg->u.egMngmt.u.usta.alarm.cause != cause)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlStaInd() : cause mismatch\n"));
      /*-- eg003.201 : changes from eg009.102: updated return value--*/
      ret = CMXTA_ERR_INT;
   } 

     /*-- Pop the message --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   /*eg012.201: check condition added for return */
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
         
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      
   RETVALUE(ret);
}/* egAcHdlStaInd */
 
/*
*
*       Fun:   egAcHdlTrcInd
*
*       Desc:  Call handler for Trace Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   Pst      pst;
   S16      ret;
   U16      eventType=0;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlTrcInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTrcInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTrcInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlTrcInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   pst.event = EVTLEGTRCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlTrcInd(): No Match, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
  
   egMsg = (EgAccMsgQElm *)msg->data;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"eventType",&eventType);
   if ( egMsg->u.egMngmt.u.trc.evnt != eventType)
   {
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlTrcInd(): event MISMatch, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   /*-- Remove the msg from the Queue --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   /*eg012.201: check condition added for return */
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlTrcInd */

/* 
*
*       Fun:   egAcHdlGenCntrlReq
*
*       Desc:  Call handler for Gen Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*  
*/  
#ifdef ANSI
PUBLIC S16 egAcHdlGenCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 egAcHdlGenCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

 
   CmXtaTxnCb* txnCb; 
   
   EG_TRC2(egAcHdlGenCntrlReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlGenCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlGenCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildGenCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN, pst.selector);

   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"elmnt",  &(cntrl.hdr.elmId.elmnt));
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlGenCntrlReq */
 
/* 
*
*       Fun:   egAcHdlUSapCntrlReq
*
*       Desc:  Call handler for SSap Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*  
*/  
#ifdef ANSI
PUBLIC S16 egAcHdlUSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure */
CmXtaSpCb  *spCb
)  
#else
PUBLIC S16 egAcHdlUSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

 
   CmXtaTxnCb* txnCb; 
   
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlUSapCntrlReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlUSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlUSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildUSapCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGUSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending SSAP Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlUSapCntrlReq */
 
/*
*
*       Fun:   egAcHdlLSapCntrlReq
*
*       Desc:  Call handler for LSap Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlLSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlLSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   /*ccpu00136421:purecov fix */
   Bool           invalTsapCbState = FALSE;
   Bool           invalTsapCbState1 = FALSE; 
   Bool           invalTsapCbState2 = FALSE; 
   SuId           suId;      /* service user SAP identifier */
  /********************************************************/
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlLSapCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlLSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlLSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   /*ccpu00136421:purecov fix */
   /*-- Get value for spid --*/
   suId = egAcDmSmGetTSapIdFromProt ( LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState",   &invalTsapCbState);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState1",  &invalTsapCbState1);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState2",  &invalTsapCbState2);
   egAcUtlBuildLSapCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGTSAP,
                    pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending eGTP TSAP Control Request\n"));
   /* ccpu00136421:purecov fix */
   if(invalTsapCbState)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  LEG_TSAP_UBNDDIS;
#else
      egCb.tSapCb->state =  LEG_TSAP_UBNDDIS;
#endif
   }
   else if(invalTsapCbState1)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  LEG_TSAP_WAIT_BNDDIS;
#else
      egCb.tSapCb->state =  LEG_TSAP_WAIT_BNDDIS;
#endif
   }
   else if(invalTsapCbState2)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  20;
#else
      egCb.tSapCb->state =  20;
#endif
   }   
   /* ccpu00136421:purecov fix */
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlLSapCntrlReq */
 
/*
*
*       Fun:   egAcHdlTServerCntrlReq
*
*       Desc:  Call handler for TServer Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlTServerCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlTServerCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
/* TODO */
   EgMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlTServerCntrlReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTServerCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTServerCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildTServerCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGSRVR,
                    pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending eGTP TServer Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
}

/*
*
*       Fun:   egAcHdlLSapTrcCntrlReq
*
*       Desc:  Call handler for LSap Trace Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlLSapTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlLSapTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlLSapTrcCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlLSapTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlLSapTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildLSapTrcCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN,
                    pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending eGTP LSAP Trc Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlLSapTrcCntrlReq */

#ifdef DEBUGP
/*
*
*       Fun:   egAcHdlDebugCntrlReq
*
*       Desc:  Call handler for Debug Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlDebugCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;

#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   CmXtaTxnCb* txnCb;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlDebugCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlDebugCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlDebugCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   egAcUtlBuildDebugCntrlReq(tcCb, spCb, &cntrl);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   /*-- Write a new function xxUtlHiBuildTSap to fill the data 
        structures and to get information from the XML, for smaller data, all
        the requests may map to a single build function as welll --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlDebugCntrlReq */
#endif


/*
*
*       Fun:   egAcHdlUstaCntrlReq
*
*       Desc:  Call handler for Unsoliciated Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlUstaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

 
   CmXtaTxnCb* txnCb;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlUstaCntrlReq)
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlUstaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlUstaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildUstaCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Usta Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlUstaCntrlReq */

/*
*
*       Fun:   egAcHdlTrcCntrlReq
*
*       Desc:  Call handler for Unsoliciated Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

 
   CmXtaTxnCb* txnCb;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlTrcCntrlReq)
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egAcUtlBuildTrcCntrlReq(tcCb, spCb, &cntrl);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trc Control Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlTrcCntrlReq */

/*
*
*       Fun:   egAcHdlCntrlCfm
*
*       Desc:  Call handler for Control confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlCntrlCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   pst.event = EVTLEGCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCntrlCfm() :  No Match, not for this Test Case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   /*eg012.201: check condition added for return */
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCfgCfm() : result mismatch\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egMsg->u.egMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(ROK);
 
}/* egAcHdlCntrlCfm */

/*
*
*       Fun:   egAcHdlShutDownCntrlReq
*
*       Desc:  Call handler for Shutdown Control Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlShutDownCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
#ifdef HW
   U16           MemRelflag = TRUE;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHdlShutDownCntrlReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlShutDownCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlShutDownCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

#ifdef HW
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"MemRelflag",  &(MemRelflag));
#endif

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
#ifdef HW
   egAcUtlBuildShutdownCntrlReq((EgMngmt *)&cntrl,MemRelflag);
#else
   egAcUtlBuildShutdownCntrlReq((EgMngmt *)&cntrl);
#endif
	cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl.u.cntrl.flag));
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGGEN, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending ShutDown Request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);
 
   RETVALUE(ROK);
}/* egAcHdlShutDownCntrlReq */

#ifdef EGTP_U
/*
*
*       Fun:   egUAcHdlUSapCfgReq
*
*       Desc:  Call handler for USAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egUAcHdlUSapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egUAcHdlUSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egUAcHdlUSapCfgReq);
 
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egUAcHdlUSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egUAcHdlUSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&cfg, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egUAcUtlBuildUSapCfgReq(tcCb, spCb, &cfg);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID, STEGUSAP, pst.selector);
 
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending eGTP USAP Configuration request\n"));
 
   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &cfg);
 
   RETVALUE(ROK);
}/* egUAcHdlUSapCfgReq */
 
/*
*
*       Fun:   egUAcHdlIPAddrCfgReq
*
*       Desc:  Call handler for IP Address Cfg Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 egUAcHdlIPAddrCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egUAcHdlIPAddrCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   S16      retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egUAcHdlIPAddrCfgReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlIPAddrCfgReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlIPAddrCfgReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   retValue = egUAcUtlBuildIPAddrCfgReq(tcCb, spCb, &cfg);
   if(retValue != CMXTA_ERR_NONE)
   {   
       CMXTA_DBG_ERR((_cmxtap,"egUAcHdlIPAddrCfgReq(): failed \n"));
       RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID,
                         STEGIPADDR, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending IP Address Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* end of egUAcHdlIPAddrCfgReq */ 

/*
*
*       Fun:   egUAcHdlIPAddrCntrlReq
*
*       Desc:  Call handler for IP Address Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egUAcHdlIPAddrCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egUAcHdlIPAddrCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egUAcHdlIPAddrCntrlReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egUAcHdlIPAddrCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egUAcHdlIPAddrCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   egUAcUtlBuildIPAddrCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTEG, CMXTA_INST_ID,
                       STEGIPADDR, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending eGTP IP Address Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLegCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /*End of egUAcHdlIPAddrCntrlReq */
#endif /* EGTP_U */


/*-- eg003.201 : TRC changes from eg009.102: Proc to resolve genCfg issue --*/
/*--
*
*       Fun:   egAcHdlCfgCntrlReq
*
*       Desc:  Resets value of genCfg back to TRUE
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_leghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlCfgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  --*/
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlCfgCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  --*/
CmXtaSpCb  *spCb;
#endif
{
   EgMngmt  cntrl;
   Pst      pst;
   Bool     genCfgReset = TRUE;
   Bool     disAlarm    = FALSE;

#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif


   CmXtaTxnCb* txnCb;

   EG_TRC2(egAcHdlCfgCntrlReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlCfgCntrlReq(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlCfgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(EgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgReset",  &genCfgReset);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"disAlarm",  &disAlarm);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Gen Config Control Request\n"));

   if(genCfgReset)
   {
      egCb.init.cfgDone = TRUE;
   }

   if(!disAlarm)
   {
      egCb.init.usta = FALSE;
   }
   RETVALUE(ROK);
}/* egAcHdlCfgCntrlReq --*/

/********************************************************************30**

         End of file:     egac_leghdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:35 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
						        rss					  2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg003.201    psingh            1. Fixed TRACE5 macro related issue from eg006.102
                                            2. Fixed warnings
                                            3. eg009.102, Proc to resolve genCfg issue
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
/main/3      eg006.201    psingh            1. Fixed Mem leak by freeing memory allocated for IP host address
/maim/3      eg012.201    shpandey          1. added klockwork warning fixes

*********************************************************************91*/
