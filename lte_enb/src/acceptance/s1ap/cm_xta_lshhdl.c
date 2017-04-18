

/********************************************************************20**

     Name:    Common 

     Type:    C source file

     Desc:    C code for Configuration and Control Handler of System Agent.

     File:    cm_xta_lshhdl.c

     Sid:      cm_xta_lshhdl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:23 2015

     Prg:     up 

*********************************************************************21*/

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
/* cm_xta_lshhdl_c.main_2: Added the SHT include as it is required
 * for SHT Cntrl Cfm function */
#ifdef CM_XTA_PSF
#include "sht.x"
#endif   /* CM_XTA_PSF */

#include "cm_xta.x"

PRIVATE Void cmXtaUtlShBuildGenCfgReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,ShMngmt     *shMngmt));
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlLshCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlLshCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;   /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   ShMngmt      cfg;
   Pst          pst;
   Pst          lmPst;
   ProcId       srcProcId;
   ProcId       dstProcId;

   CMXTA_ZERO(&cfg, sizeof(ShMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlLshGenCfgReq)
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSH, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlShBuildGenCfgReq(tcCb, spCb, &cfg);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSH, CMXTA_INST_ID, STGEN, pst.selector);

   /* Store our configuration and send a configuration
      request to the System Agent */
   (Void) SmMiLshCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);


}/*  */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlLshCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlLshCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;   /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   ShMngmt      req;
   Pst          pst;
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   req.t.cntrl[0].action    = CMFTHA_AWARMSTART;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "action",  &(req.t.cntrl[0].action));
   req.t.cntrl[0].subAction = 0;
   req.t.cntrl[0].cntrlParams.sysMgr.nmbEnts            = 1;
   req.t.cntrl[0].cntrlParams.sysMgr.entPar[0].entId    =  1;
   req.t.cntrl[0].cntrlParams.sysMgr.entPar[0].instId   =  0;
   req.t.cntrl[0].cntrlParams.sysMgr.entPar[0].waitForAck = TRUE;
   req.t.cntrl[0].cntrlParams.sysMgr.entPar[0].nmbRsets = 1;
   req.t.cntrl[1].action    = ANOACT;
   req.t.cntrl[1].subAction = 0;
   SmMiLshCntrlReq(&pst, &req);

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   cmXtaHdlLshTrcCntrlReq
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
PUBLIC S16 cmXtaHdlLshTrcCntrlReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlLshTrcCntrlReq (tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   ShMngmt  req;
   Pst      pst;

   ProcId       srcProcId;
   ProcId       dstProcId;

   CmXtaTxnCb *txnCb;

   TRC2(cmXtaHdlLShTrcCntrlReq)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlLShTrcCntrlReq() tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&req, sizeof(ShMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSH, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   req.t.cntrl[0].action    = LSH_AENA;
   
   req.t.cntrl[0].subAction = LSH_SATRC;
   
   req.t.cntrl[0].cntrlParams.stackMgr.shTrc.trcMask  = SHTRCMI | SHTRCDE;
   
   req.t.cntrl[0].cntrlParams.stackMgr.shTrc.trcLevel = 0;
   
   req.t.cntrl[1].action    = ANOACT;
   
   req.t.cntrl[1].subAction = 0;
   
   SmMiLshCntrlReq(&pst, &req);

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlLShTrcCntrlReq*/


/*
*
*       Fun:   cmXtaHdlLshStsReq
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
PUBLIC S16 cmXtaHdlLshStsReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlLshStsReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   ShMngmt  req;
   Pst      pst;

   ProcId       srcProcId;
   ProcId       dstProcId;

   CmXtaTxnCb *txnCb;

   TRC2(cmXtaHdlLshStsReq)

   CMXTA_DBG_PARAM((_cmxtap, "soAcHdlShStsReq() tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&req, sizeof(ShMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSH, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   req.t.sts.shSts.entId = 254;
   
   SmMiLshStsReq(&pst, ZEROSTS, &req);

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlLshStsReq*/

/*
*
*       Fun:   cmXtaHdlLshStaReq
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
PUBLIC S16 cmXtaHdlLshStaReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlLshStaReq(tcCb, spCb)
CmXtaTCCb  *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   ShMngmt  req;
   Pst      pst;

   ProcId       srcProcId;
   ProcId       dstProcId;

   CmXtaTxnCb *txnCb;

   TRC2(cmXtaHdlLshStaReq)

   CMXTA_DBG_PARAM((_cmxtap, "soAcHdlShStaReq() tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&req, sizeof(ShMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSH, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   req.t.sts.shSts.entId = 254;

   SmMiLshCntrlReq(&pst, &req);

   RETVALUE(CMXTA_ERR_NONE);

}/* soAcHdlShStaCntrlReq*/


/*
*
*       Fun:   cmXtaUtlShBuildGenCfgReq
*
*       Desc:  Utility Function to Build General Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsgutl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlShBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
ShMngmt        *shMngmt   
)
#else
PRIVATE Void cmXtaUtlShBuildGenCfgReq(tcCb, spCb, shMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
ShMngmt       *shMngmt;   
#endif
{

   /* local variables */
   ShGenCfg    *shGen; 
   Pst            pst;
   ProcId       srcProcId;
   ProcId       dstProcId;

   TRC2(cmXtaUtlShBuildGenCfgReq)

   shGen   = &(shMngmt->t.cfg.shGen);

   cmMemset ((U8 *) shGen  , 0, sizeof (ShGenCfg));   

   shGen->trcMask = 0;

   shGen->dbgMask = 0;
   
   shGen->dbgMask = SHDBDSP | SHDBTRANS | SHDBFAIL;
   shGen->tmrRes       = 10;
   shGen->toLocal1.val = 300;
   shGen->toLocal1.enb = TRUE;
   shGen->toLocal2.val = 500;
   shGen->toLocal2.enb = TRUE;
   shGen->nLocal       = 3;
   shGen->toRemote.val = 5000;
   shGen->toRemote.enb = TRUE;
   shGen->nRemote      = 3;

#ifdef SS_MULTIPLE_PROCS
   shGen->localPst.srcProcId = CMXTA_PROCID_MASTER; 
   shGen->localPst.dstProcId = CMXTA_PROCID_MASTER;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc",
&(shGen->localPst.srcProcId));
#else
   shGen->localPst.srcProcId = SFndProcId();
   shGen->localPst.dstProcId = SFndProcId();
#endif /*-- SS_MULTIPLE_PROCS --*/
   shGen->localPst.srcEnt    = ENTSH;
   shGen->localPst.srcInst   = 0;
   shGen->localPst.prior     = 0;
   shGen->localPst.route     = 0;
   shGen->localPst.selector  = 0;
   shGen->localPst.region    = 0;
   shGen->localPst.pool      = 0;

   shGen->reverseHdr.response.selector   = 0;
   shGen->reverseHdr.response.prior      = 0;
   shGen->reverseHdr.response.route      = 0;
   shGen->reverseHdr.response.mem.region = 0;
   shGen->reverseHdr.response.mem.pool   = 0;


   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTSH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(shGen->smPst),
            (U8 *) &(pst),
            (PTR) sizeof(Pst));

   cmXtaGetPst(&pst, ENTSH, CMXTA_INST_ID, ENTSH, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

  /* Layer Manager post structure */
   cmMemcpy((U8 *) &(shGen->remotePst),
            (U8 *) &(pst),
            (PTR) sizeof(Pst));

   RETVOID;
}

/*
*
*       Fun:   cmXtaHdlLshCfgCfm
*
*       Desc:  Call handler for LSG config confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlLshCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 cmXtaHdlLshCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm      *msg;
   CmXtaFthaMsgQElm  *shMsg;
   CmStatus          status;
   Pst               pst;
   S16               ret;
   ProcId            srcProcId;
   ProcId            dstProcId;

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlLshCfgCfm(): tcId (%ld)\n", tcCb->tcId));

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   shMsg = (CmXtaFthaMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTSH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   pst.event = EVTLSHCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaHdllLshCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(shMsg->u.shMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdllLshCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlLshCfgCfm */


/*
*
*       Fun:   cmXtaHdlLshCntrlCfm
*
*       Desc:  Call handler for LSG control confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlLshCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 cmXtaHdlLshCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm      *msg;
   CmXtaFthaMsgQElm  *shMsg;
   CmStatus          status;
   Pst               pst;
   S16               ret;
   ProcId            srcProcId;
   ProcId            dstProcId;

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlLshCntrlCfm(): tcId (%ld)\n", tcCb->tcId));

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   shMsg = (CmXtaFthaMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTSH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   pst.event = EVTLSHCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlLshCntrlCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(shMsg->u.shMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlLshCntrlCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlLshCntrlCfm */

/* cm_xta_lshhdl_c.main_2: Added the ShtCntrlCfm function as it is 
 * required by every layer. This function is moved from the cm_xta_slave.c
 * file */
#if defined(CM_XTA_PSF) && defined(CMXTA_FTHA_INTEGRATED)
/*
 *
 *       Fun:    ShMiShtCntrlCfm
 *
 *       Desc:   Dummy Control Confirm.This has been used by the several Layer
 *       inside the SH flag(TUCL,SB)but ideally this should not be used unless 
 *       the Layer is trying to write  the Dummy SH and trying to implement SH 
 *       Interface in the tight coupling.
 *       coupling.This has been used outside the Application flag in all the
 *       Layers.We need to ivestigate in this as all the confirmation needs to
 *       be sent through the Loose Coupling.
 *
 *       Ret:    ROK     - succeeded
 *
 *       Notes:  None
 *
 *       File:   smsobdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ShMiShtCntrlCfm
(
Pst     *pst,
ShtCntrlCfmEvnt *cntrl
)
#else
PUBLIC S16 ShMiShtCntrlCfm (pst, cntrl)
Pst     *pst;
ShtCntrlCfmEvnt *cntrl;
#endif /* ANSI */
{

   TRC3(ShMiShtCntrlCfm)
   UNUSED(pst);

   RETVALUE(ROK);
} /* SmMiShtCntrlCfm */

#endif


/********************************************************************30**

         End of file:     cm_xta_lshhdl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:23 2015

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
/main/2      ----     sy   GCP 2.1 release
/main/3      ---      cm_xta_lshhdl_c_001.main_2 pka  1. Fix for integration testing
*********************************************************************91*/
