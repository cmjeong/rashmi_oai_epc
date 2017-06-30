
/********************************************************************20**
  
     Name:     psf-sip
  
     Type:     C source file
  
     Desc:     This file contains the handler functions for LMR 
               interface commands. 
  
     File:     cm_xta_lmrhdl.c
  
     Sid:      cm_xta_lmrhdl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:20 2015
  
     Prg:      sk
  
*********************************************************************21*/

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
#include "lmr.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
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
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "cm_xta.x"



/* forward declarations for utility funcions */
PRIVATE Void cmXtaUtlMrBuildGenCfgReq ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, MrMngmt *mrMngmt));  

/*
*
*       Fun:   cmXtaHdlMrGenCfgReq 
*
*       Desc:  This function handles the config request
*                sent by the SM to PSF-SIP. 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lmrhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 cmXtaHdlMrGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlMrGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   MrMngmt cfg;        /* MR management structure */
   Pst pst;            /* Pst structure */
   Pst      lmPst;
  
   ProcId       srcProcId;
   ProcId       dstProcId;
   CmXtaTxnCb* txnCb;
 
   TRC2(cmXtaHdlMrGenCfgReq)

   CMXTA_ZERO(&cfg, sizeof(MrMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTMR, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);


   /* Fill the data structure here, even the parameters which
   needs to be changed from XML */ 
   cmXtaUtlMrBuildGenCfgReq(tcCb, spCb, &cfg);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTMR, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager General Configuration request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLmrCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
    
}/* cmXtaHdlMrGenCfgReq*/


/*
*
*       Fun:   cmXtaHdlMrCfgCfm
*
*       Desc:  This function handles the config confirm
*                sent by the SIP-PSF to SM
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lmrhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlMrCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 cmXtaHdlMrCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm      *msg;
   CmXtaFthaMsgQElm  *mrMsg;
   CmStatus          status;
   Pst               pst;
   S16               ret;
   ProcId            srcProcId;
   ProcId            dstProcId;

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlMrCfgCfm(): tcId (%ld)\n", tcCb->tcId));

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   mrMsg = (CmXtaFthaMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTMR, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
   pst.event = EVTLMRCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlMrCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(mrMsg->u.mrMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlMrCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

} /* cmXtaHdlMrCfgCfm */


/*
*
*       Fun:   cmXtaHdlMrShutDownCntrlReq 
*
*       Desc:  This function handles sending a Shutdown Control request
*                sent by the SM to PSF-SIP
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lmrhdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlMrShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlMrShutDownCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{

}/* cmXtaHdlMrShutDownCntrlReq */


/*
*
*       Fun:   cmXtaHdlMrCntrlCfm
*
*       Desc:  Call handler for Control Confirmation from Layer  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lmrhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlMrCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlMrCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{

   CmXtaMsgQElm      *msg;
   CmXtaFthaMsgQElm  *sgMsg;
   CmStatus          status;
   Pst               pst;
   S16               ret;
   ProcId            srcProcId;
   ProcId            dstProcId;

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgCntrlCfm(): tcId (%ld)\n", tcCb->tcId));

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   sgMsg = (CmXtaFthaMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTMR, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   pst.event = EVTLSGCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlSgCntrlCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(sgMsg->u.sgMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlSgCntrlCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlSgCntrlCfm */

/*
*
*       Fun:   cmXtaUtlMrBuildGenCfgReq
*
*       Desc:  Utility Function to Build Gen Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lmrhdl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlMrBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
MrMngmt        *mrMngmt
)
#else
PRIVATE Void cmXtaUtlMrBuildGenCfgReq(tcCb, spCb, mrMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
MrMngmt       *mrMngmt;
#endif
{

   ProcId       srcProcId;
   ProcId       dstProcId;
   MrCfg        *genCfg;
   Pst          pst;

   TRC2(cmXtaUtlMrBuildGenCfgReq)

      genCfg   = &(mrMngmt->s.cfg);

   cmMemset ((U8 *) genCfg  , 0, sizeof (MrCfg));

   /*-- Filll in the values of the structures --*/

   genCfg->maxEntities      = CMXTA_SG_MAX_SYS_ENTS;
   genCfg->maxInstances     = CMXTA_SG_MAX_SYS_INSTANCES;
   genCfg->maxPeerSyncMsg   = CMXTA_MR_MAX_PEERSYNC_MSG;
   genCfg->maxQSize         = CMXTA_MR_MAX_QSIZE;
   genCfg->timeRes          = CMXTA_MR_TIMER_RES;
   genCfg->peerTmr.enb      = TRUE; 
   genCfg->peerTmr.val      = CMXTA_MR_PEER_TIMER; 
   genCfg->region           = DFLT_REGION; 
   genCfg->pool             = DFLT_POOL; 

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTMR, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(genCfg->smPst),
         (U8 *) &(pst),
         (PTR) sizeof(Pst));

   RETVOID;
}/* cmXtaUtlMrBuildGenCfgReq */
/********************************************************************30**

         end of file:     cm_xta_lmrhdl.c@@/main/1 - wed jun 27 16:21:27 2007

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
*********************************************************************91*/
