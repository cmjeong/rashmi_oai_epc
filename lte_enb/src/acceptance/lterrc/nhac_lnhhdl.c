
/********************************************************************20**

     Name:    RRC 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_lnhhdl.c

     Sid:      nhac_lnhhdl.c@@/main/3 - Fri Jul  1 01:13:04 2011

     Prg:     dm 

*********************************************************************21*/

/* header include files (.h) */
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_cpj.x"
#include "nhac_acc_ctf.x"


EXTERN NhAccCpjVal  gCpjCfgStore[25];
EXTERN NhAccCrgVal  gCrgValStore[25];
EXTERN NhAccCkwVal  gCkwValStore[25];
#ifdef RRC_PHY_CFG_SUPP
EXTERN NhAccCtfVal  gCtfValStore[25];
#endif
EXTERN U8 gValIdx;

EXTERN NhAcCkwCfgInfo gCkwCfgInf[5];
EXTERN NhAcCpjCfgInfo gCpjCfgInfo[5];
EXTERN NhAcCrgCfgInfo gCrgCfgInfo[5];
#ifdef RRC_PHY_CFG_SUPP
EXTERN NhAcCtfCfgInfo gCtfCfgInfo[5];
#endif

PRIVATE S16 nhAcValidateStsCfm ARGS((CmXtaTCCb  *tcCb, 
                                     CmXtaSpCb  *spCb,
                                     NhMngmt    *stsCfm));
#ifdef NH_TRACE_ENABLED
PRIVATE S16 nhAcValidateTrcInd ARGS((NhMngmt     *nhMngmt));
#endif

/* XTA Config Req Starts */

/*
*
*       Fun:   nhAcHdlNhGenCfgReq
*
*       Desc:  Call handler for General Config Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cfg;
   Pst      pst;
   Pst      lmPst;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16      ret = 0;
   CmXtaTxnCb* txnCb = NULLP; 
   NhAcTACb   tmpTaCb;

   TRC2(nhAcHdlNhGenCfgReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   /* Initialization of nhAccCb */
   tmpTaCb = nhAccCb.taCb;
   cmMemset((U8 *)&nhAccCb, 0, (PTR)(sizeof(NhAccCb)));
   nhAccCb.taCb = tmpTaCb;

   /*Initialise lower layer confirm arrays*/
   cmMemset((U8*)&gCkwCfgInf, 0, 5 * sizeof(NhAcCkwCfgInfo));
   cmMemset((U8*)&gCpjCfgInfo, 0, 5 * sizeof(NhAcCpjCfgInfo));
   cmMemset((U8*)&gCrgCfgInfo, 0, 5 * sizeof(NhAcCrgCfgInfo));
#ifdef RRC_PHY_CFG_SUPP
   cmMemset((U8*)&gCtfCfgInfo, 0, 5 * sizeof(NhAcCtfCfgInfo));
#endif

   CMXTA_ZERO(&cfg, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&lmPst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = nhAcUtlNhBuildGenCfgReq(tcCb, spCb, &cfg);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhGenCfgReq() Unable to Build General Configuration Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get the LmPst */
   /* Moved outside MULTIPLE PROC flag */
    cmXtaGetPst(&lmPst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,dstProcId,srcProcId,FALSE);

   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(cfg.u.cfg.u.gen.lmPst),
            (U8 *) &(lmPst),
            (PTR) sizeof(Pst));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"selector",  &cfg.u.cfg.u.gen.lmPst.selector);
 
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   pst.selector = cfg.u.cfg.u.gen.lmPst.selector;
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC General Configuration request\n"));

   /* Send the request to the RRC */
   SmMiLnhCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhGenCfgReq */

/*
*
*       Fun:   nhAcHdlNhUsapCfgReq
*
*       Desc:  Call handler for Upper SAP Config Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhUsapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhUsapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cfg;
   Pst      pst;

   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16      ret = 0;

   TRC2(nhAcHdlNhUsapCfgReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUsapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUsapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ret = nhAcUtlNhBuildUsapCfgReq(tcCb, spCb, &cfg); 
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildUsapCfgReq() Unable to Build USAP Configuration Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHUSAP, pst.selector);

                       
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC USAP Configuration request\n"));

   SmMiLnhCfgReq(&pst, &cfg);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhUsapCfgReq */


/*
*
*       Fun:   nhAcHdlNhLsapCfgReq
*
*       Desc:  Call handler for Lower SAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhLsapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhLsapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cfg;
   Pst      pst,entPst;
   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16      ret = 0;
   U16      elem = 0;


   TRC2(nhAcHdlNhLsapCfgReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhLsapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhLsapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cfg, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&entPst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = nhAcUtlNhBuildLsapCfgReq(tcCb,spCb,&cfg);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhGenCfgReq() Unable to Build LSAP Configuration Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"elem",  &elem);

    (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, elem, pst.selector);
      
   switch(elem)
   {
     case 3:
     /* Moved outside MULTIPLE PROC flag */
     cmXtaGetPst(&entPst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
     break;
     
     case 4:
     /* Moved outside MULTIPLE PROC flag */
     cmXtaGetPst(&entPst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
     break;
     
     case 5:
     /* Moved outside MULTIPLE PROC flag */
     cmXtaGetPst(&entPst,ENTNH , CMXTA_INST_ID, ENTRG, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
     break;
     
     case 6:
     /* Moved outside MULTIPLE PROC flag */
     cmXtaGetPst(&entPst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
     break;
     
     case 7:
     /* Moved outside MULTIPLE PROC flag */
     cmXtaGetPst(&entPst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
     break;

     case 12:
     /* Moved outside MULTIPLE PROC flag */
     cmXtaGetPst(&entPst, ENTNH, CMXTA_INST_ID, ENTTF, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
     break;
    }
   cfg.u.cfg.u.lSap.selector =  entPst.selector;
   /* This is for the error scenario. In successful case selector value
    * shouldnot be given from XML */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "selector",
         &(cfg.u.cfg.u.lSap.selector));
   cfg.u.cfg.u.lSap.procId =  entPst.dstProcId;
   cfg.u.cfg.u.lSap.ent =  entPst.dstEnt;
   cfg.u.cfg.u.lSap.inst =  entPst.dstInst;
   cfg.u.cfg.u.lSap.route =  entPst.route;
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC LSAP Configuration request\n"));

    SmMiLnhCfgReq(&pst, &cfg);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhLsapCfgReq */


/*
*
*       Fun:   nhAcHdlNhProtCfgReq
*
*       Desc:  Call handler for Lower SAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhProtCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhProtCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cfg;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;


   TRC2(nhAcHdlNhProtCfgReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhProtCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhProtCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&cfg, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;


#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ret = nhAcUtlNhBuildProtCfgReq(tcCb,spCb,&cfg);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhGenCfgReq() Unable to Build Protocol Configuration Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHPROT, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Protocol Configuration request\n"));

   SmMiLnhCfgReq(&pst, &cfg);


   RETVALUE(CMXTA_ERR_NONE);
} /*nhAcHdlNhProtCfgReq*/


/*
*
*       Fun:   nhAcHdlNhCfgCfm
*
*       Desc:  Call handler for Config Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nh_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmStatus       status;
   Pst      pst;
   S16      ret = 0;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16      option=1; 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));
   cmMemset((U8*)&status, 0 , sizeof(CmStatus));

   cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &srcProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = EVTLNHCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "nhAcHdlNhCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"option",  &option);
   /*-- Validate return value and reason --*/
   ret= nhAcValidateStatus(&status, &(rrcMsg->u.nhMngmt.cfm));
   if(option ==2 && ret !=ROK)
    ret = ROK;
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhCfgCfm */

/* XTA Config Req ends */

/* XTA  Control Req Starts */


/*
*   
*       Fun:   nhAcHdlNhUstaCntrlReq
*   
*       Desc:  Call handler for Unsolicited Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhUstaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   S16      ret = 0;
   NhMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;

   TRC2(nhAcHdlNhUstaCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUstaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUstaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ret = nhAcUtlNhBuildUstaCntrlReq(tcCb,spCb,&cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Usta Control Request\n"));

   /* Send the request */
    SmMiLnhCntrlReq(&pst, &cntrl);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhUstaCntrlReq */





/*
*
*       Fun:   nhAcHdlNhLsapCntrlReq
*
*       Desc:  Call handler for Lower SAP Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nh_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhLsapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhLsapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;
   U16     elem=3;

   TRC2(nhAcHdlNhLsapCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhLsapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhLsapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ret = nhAcUtlNhBuildLsapCntrlReq(tcCb,spCb,&cntrl);
    if(ret != CMXTA_ERR_NONE)
    {
       CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildLsapCntrlReq() Unable to build LSap Control Request \n"));
       RETVALUE(CMXTA_ERR_INT);
    }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"elem",  &elem);
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, elem, pst.selector);


   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Lower SAP Control Request\n"));

   /* Send the request */
    SmMiLnhCntrlReq(&pst, &cntrl);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhLsapCntrlReq */


/*
*
*       Fun:   nhAcHdlNhUsapCntrlReq
*
*       Desc:  Call handler for Upper SAP Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nh_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhUsapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhUsapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;

   TRC2(nhAcHdlNhUsapCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUsapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUsapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ret = nhAcUtlNhBuildUsapCntrlReq(tcCb,spCb,&cntrl);
    if(ret != CMXTA_ERR_NONE)
    {
       CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildUsapCntrlReq() Unable to build LSap Control Request \n"));
       RETVALUE(CMXTA_ERR_INT);
    }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID,STNHUSAP , pst.selector);
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Upper SAP Control Request\n"));

   /* Send the request */
   SmMiLnhCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhUsapCntrlReq */

#ifdef NH_TRACE_ENABLED
/*
*
*       Fun:   nhAcHdlNhTrcCntrlReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cntrl;
   Pst      pst;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;

   CmXtaTxnCb* txnCb = NULLP; 

   TRC2(nhAcHdlNhLsapTrcCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret =  nhAcUtlNhBuildTrcCntrlReq(tcCb, spCb,&cntrl);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildTrcCntrlReq() Unable to build the trace control Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
   
   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Upper SAP Control Request\n"));

   /* Send the request */
   SmMiLnhCntrlReq(&pst, &cntrl);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhTrcCntrlReq */
#endif

/*
*
*       Fun:   nhAcHdlNhPnodeTrcCntrlReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nh_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhPnodeTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhPnodeTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cntrl;
   Pst      pst;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;

   CmXtaTxnCb* txnCb = NULLP; 

   TRC2(nhAcHdlNhPnodeTrcCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhPnodeTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhPnodeTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = nhAcUtlNhBuildPnodeCntrlReq(tcCb,spCb,&cntrl);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildPnodeCntrlReq() Unable to build the trace control Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Peer Node Trace Control Request\n"));

   /* Send the request */
   SmMiLnhCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhPnodeTrcCntrlReq */

/*
*
*       Fun:   nhAcHdlNhDebugCntrlReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhDebugCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
#ifdef DEBUGP
   NhMngmt  cntrl;
   Pst      pst;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;

   CmXtaTxnCb* txnCb = NULLP; 

   TRC2(nhAcHdlNhDebugCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhDebugCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhDebugCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret =  nhAcUtlNhBuildDebugCntrlReq(tcCb, spCb,&cntrl);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildDebugCntrlReq() Unable to build the trace control Request \n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Debug Control Request\n"));

   /* Send the request */
   SmMiLnhCntrlReq(&pst, &cntrl);
#else
/* Dont send control request to layer insted directly push control confirm to
 * queue */
   /* Layer manager test group 7 
    * and Test case ids 18,29,30,34 are valid only if DEBUGP is 
    * enable else push dummy msg in CMXTA Queue to proceed further */
   Pst pst; 
   NhMngmt cntrlCfm;
   Pst      srcPst;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;

   CMXTA_ZERO(&srcPst, sizeof(Pst));
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&srcPst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
   cntrlCfm.cfm.status= LCM_PRIM_OK;
   cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   pst.srcEnt = ENTNH;
   pst.srcInst   = CMXTA_INST_ID; 
   pst.srcProcId = CMXTA_PROCID_MASTER;
   pst.dstEnt    = ENTSM;
   pst.dstInst   = srcPst.srcInst;
   pst.dstProcId = srcPst.srcProcId;
                                  
   SmMiLnhCntrlCfm(&pst,&cntrlCfm);

#endif   
   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhDebugCntrlReq */
/* #endif */ /* DEBUGP */


/*
*
*       Fun:   nhAcHdlNhShutDownCntrlReq
*
*       Desc:  Call handler for Shut Down control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhShutDownCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhShutDownCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb =  NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;

   TRC2(nhAcHdlNhShutDownCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhShutDownCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhShutDownCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = nhAcUtlNhBuildShutdownCntrlReq(&cntrl);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildShutdownCntrlReq() Unable to build the Shutdown Request\n"));
      RETVALUE(CMXTA_ERR_INT);
   }/* end of if statement */

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC ShutDown Request\n"));

   /* Send the request */
   SmMiLnhCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhShutDownCntrlReq */


/*
*
*       Fun:   nhAcHdlNhStartCntrlReq
*
*       Desc:  Call handler for Start control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhStartCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhStartCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  cntrl;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;

   TRC2(nhAcHdlNhStartCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStartCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStartCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&cntrl, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = nhAcUtlNhBuildStartCntrlReq(&cntrl);
   if(ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildStartCntrlReq() Unable to Start Control Request\n"));
      RETVALUE(CMXTA_ERR_INT);
   }/* end of if statement */

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Start Request\n"));
   /* Send the request */
   SmMiLnhCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhStartCntrlReq */


/*
*
*       Fun:   nhAcHdlNhCntrlCfm
*
*       Desc:  Call handler for Command Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmStatus       status;
   Pst      pst;
   S16      ret = 0;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16      option = 1;
   U8       idx=0;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&status, 0 , sizeof(CmStatus));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;

   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &srcProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = EVTLNHCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhCntrlCfm() :  No Match, not for this Test Case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= nhAcValidateStatus(&status, &(rrcMsg->u.nhMngmt.cfm));
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"option",  &option); 
    if(option == 2)
      ret =  ROK;
#ifndef DEBUGP
    /* This test case is not valid if debug is not enabled 
       so skip steps with OK */
    /* layer manager test group 7 and test id 34  */
   if((tcCb->tstGrpId == 6 ) && (tcCb->tstId == 33 ))
   {
      ret = ROK;
   }
#endif
    
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   for(idx = 0;idx < 25;idx++)
   {
      gCkwValStore[idx].used = FALSE;
      gCrgValStore[idx].used = FALSE;
      gCpjCfgStore[idx].used = FALSE;
#ifdef RRC_PHY_CFG_SUPP
      gCtfValStore[idx].used = FALSE;
#endif
   }
   gValIdx = 0;

   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhCntrlCfm */

/* XTA  Control Req ends */

/* XTA Statistics start */
/*
*
*       Fun:   nhAcHdlNhGenStsReq
*
*       Desc:  Call handler for General Statistics
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhGenStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhGenStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  sts;
   Pst      pst;
   U16   action = 1;         /* zeroing action */

   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;


   TRC2(nhAcHdlNhGenStsReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhGenStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhGenStsReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&action, sizeof(Action));
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
      using XML --*/
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "action",  &action);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC General Statistics request\n"));

   /* Send the request to the RRC */
    SmMiLnhStsReq(&pst, action, &sts);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhGenStsReq */

/*
*
*       Fun:   nhAcHdlNhPnodeStsReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhPnodeStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhPnodeStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  sts;
   Pst      pst;
   U16  action = 1;         /* zeroing action */
   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16       elem=0;
   U32       ueId=0;
   U32       cellId=0;

   TRC2(nhAcHdlNhPnodeStsReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhPnodeStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhPnodeStsReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&action, sizeof(Action));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "action",  &action);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "elem",  &elem);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "ueId",  &ueId);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &cellId);


   sts.u.sts.u.ueSts.crnti = ueId;
   sts.u.sts.u.ueSts.cellId = cellId;
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, STNHPROT, CMXTA_INST_ID, elem, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Reep Statistics request\n"));

   /* Send the request to the TUCL */
    SmMiLnhStsReq(&pst, action, &sts);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhPnodeStsReq */

/*
*
*       Fun:   nhAcHdlNhCellStsReq
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhCellStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhCellStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  sts;
   Pst      pst;
   U16  action = 1;         /* zeroing action */
   CmXtaTxnCb* txnCb = NULLP; 
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16       elem=0;
   U32       cellId=0;

   TRC2(nhAcHdlNhCellStsReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhCellStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhCellStsReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sts, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&action, sizeof(Action));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "action",  &action);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "elem",  &elem);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &cellId);


   sts.u.sts.u.cellSts.cellId = cellId;
   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, STNHPROT, CMXTA_INST_ID, elem, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Reep Statistics request\n"));

   /* Send the request to the TUCL */
   SmMiLnhStsReq(&pst, action, &sts);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhCellStsReq */

/*
*
*       Fun:   nhAcHdlNhStsCfm
*
*       Desc:  Call handler for Statistics Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmStatus       status={0};
   Pst      pst;
   S16      ret = 0;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16 option = 1;
#ifndef NH_NO_STS
   U32      cntr;
#endif
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif


   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&status, sizeof(CmStatus));
   cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   rrcMsg = (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &srcProcId);
#endif
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"option",  &option);
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);


   pst.event = EVTLNHSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStsCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= nhAcValidateStatus(&status, &(rrcMsg->u.nhMngmt.cfm));
   if (option == 2 && ret != ROK)
     ret = ROK;


   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStsCfm() : result mismatch\n"));
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(rrcMsg->u.nhMngmt.cfm.status == LCM_PRIM_OK)
   {
      ret = nhAcValidateStsCfm(tcCb, spCb, &(rrcMsg->u.nhMngmt));
      if(ret != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStsCfm() : result mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }   
   }

#ifndef NH_NO_STS
   if (STNHCELL == rrcMsg->u.nhMngmt.hdr.elmId.elmnt)
   {
      cntr = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"hoStsCntr",  &cntr);

      if(cntr != rrcMsg->u.nhMngmt.u.sts.u.cellSts.hoFromEUTRAFail)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStsCfm() : hoStsCntr mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif 

   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhStsCfm */

/* XTA Statistics ends */

/* XTA Status Begins */
/*
*
*       Fun:   nhAcHdlNhSysStaReq
*
*       Desc:  Call handler for System Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhSysStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhSysStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  ssta;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;

   TRC2(nhAcHdlNhSysStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhSysStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhSysStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    /* Design:- No Data need to be filled here*/


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHSID, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC System Status request\n"));

   /* Send the request to the TUCL */
    SmMiLnhStaReq(&pst, &ssta);


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhSysStaReq */

/*
*
*       Fun:   nhAcHdlNhUsapStaReq
*
*       Desc:  Call handler for Upper SAP Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhUsapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhUsapStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  ssta;
   Pst      pst;

   CmXtaTxnCb* txnCb =  NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;

   TRC2(nhAcHdlNhUsapStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUsapStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhUsapStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "sapId",  &(ssta.u.ssta.u.sap.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHUSAP, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Upper SAP Status Request\n"));

   /* Send the request */
     SmMiLnhStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhUsapStaReq */

/*
*
*       Fun:   nhAcHdlNhGenStaReq
*
*       Desc:  Call handler for General solicited Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhGenStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhGenStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  ssta;
   Pst      pst;
   CmXtaTxnCb* txnCb = NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;

   TRC2(nhAcHdlNhGenStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhGenStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhGenStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    /* Design: No Data is need to be filled */


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, STNHGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC General Status request\n"));

   /* Send the request */
    SmMiLnhStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhGenStaReq */

/*
*
*       Fun:   nhAcHdlNhLsapStaReq
*
*       Desc:  Call handler for Lower Sap Status Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhLsapStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhLsapStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhMngmt  ssta;
   Pst      pst;

   CmXtaTxnCb* txnCb = NULLP;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   U16      elem = STNHKWUSAP;
   TRC2(nhAcHdlNhLsapStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhLsapStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhLsapStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&ssta, sizeof(NhMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
    ssta.u.ssta.u.sap.sapId = 1;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "sapId",  &(ssta.u.ssta.u.sap.sapId));

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "elem",  &elem);
   /* Prepare header */
   (Void) cmXtaInitHdr(&(ssta.hdr), txnCb->txnId, ENTNH, CMXTA_INST_ID, elem, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending RRC Lower SAP Status Request\n"));

   /* Send the request */
   SmMiLnhStaReq(&pst, &ssta);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhLsapStaReq */


/*
*
*       Fun:   nhAcHdlNhStaCfm
*
*       Desc:  Call handler for Status Confirmation from Layer  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhAccMsgQElm   *rrcMsg = NULLP;
   CmXtaMsgQElm   *msg=NULLP;
   CmStatus       status;
   Pst      pst;
   S16      ret = 0;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      valCfmRet = 0;
   U16      option = 1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&status, sizeof(CmStatus));
   cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   rrcMsg   = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"option",  &option);

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTNH , CMXTA_INST_ID, ENTSM , CMXTA_INST_ID,srcProcId,dstProcId,FALSE);


   pst.event = EVTLNHSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStaCfm() : No match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
   /*
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"status",  &status.status);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"reason",  &status.reason);
*/
   /*-- Validate return value and reason --*/
   ret= nhAcValidateStatus(&status, &(rrcMsg->u.nhMngmt.cfm));
   
   if (option ==2 )
     ret = ROK;

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStaCfm() : result mismatch\n"));
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   valCfmRet = nhAcValidateStaCfm(tcCb,spCb,&(rrcMsg->u.nhMngmt));

   if(valCfmRet != CMXTA_ERR_NONE && rrcMsg->u.nhMngmt.cfm.status == 0)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhStaCfm() : Validation of Status Confirm failed \n"));
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhStaCfm */

/*
*
*       Fun:   nhAcHdlNhStaInd
*
*       Desc:  Call handler for Unsolicited Status Inidication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhAccMsgQElm   *rrcMsg = NULLP;
   CmXtaMsgQElm   *msg=NULLP;
   Pst      pst;
   S16      ret = 0;
   U16   category = 0;           /* ALARM category*/
   U16   event = 0;              /* ALARM event */
   U16   cause = 0;              /* ALARM cause */
   U8    alarmType = 0;          /* Type of parameter */
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      retVal = 0;
   U16      guardTmr = 0;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhStaInd(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(pst));
   guardTmr = CMXTA_TMR_GUARD_VAL;
   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   rrcMsg   = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif


   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = EVTLNHSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "nhAcHdlNhStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   category = LCM_CATEGORY_INTERFACE;

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "category",  &(category));
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      /* Matching the category from xml and that from the message */
      if (category != rrcMsg->u.nhMngmt.u.usta.alarm.category)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Category MisMatch: exp (%d) recvd (%d) \n", category , rrcMsg->u.nhMngmt.u.usta.alarm.category), 2);

         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      } /* End of if statement  */
   } /* end of if statement  */
   else
   {
      /* category is always expected from the xml file   */
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhStaInd()  Category field is expected from the xml file to validate\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   event = 15;

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "event",  &(event));

   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      /* Matching the category from xml and that from the message */
      if (event != rrcMsg->u.nhMngmt.u.usta.alarm.event)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : event MisMatch: exp (%d) recvd (%d) \n", event, rrcMsg->u.nhMngmt.u.usta.alarm.event), 2);

         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
       } /* end of if statement  */
   } /* end of if statement */
   else
   {
      /* event is always expected from the xml file   */
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhStaInd()  Event field is expected from the xml file to validate\n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   cause = NHAC_CAUSE_TCP_IPSEC_SRV_OPEN_SUCC;

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cause",  &(cause));
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      /* Matching the category from xml and that from the message */
      if (cause != rrcMsg->u.nhMngmt.u.usta.alarm.cause)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause MisMatch: exp (%d) recvd (%d) \n",
                     cause, rrcMsg->u.nhMngmt.u.usta.alarm.cause), 2);

         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }  /* end of if statement  */
    } /* end of if statement  */
    else
    {
      /* cause is always expected from the xml file   */
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhStaInd()  Cause field is expected from the xml file to validate\n"));
      RETVALUE(CMXTA_ERR_INT);
    } /* end of else statement  */

   alarmType = NHAC_USTA_DGNVAL_SAPID;

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "alarmType",  &(alarmType));

   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      /* Matching the alarm type from xml and that from the message */
      if (alarmType != rrcMsg->u.nhMngmt.u.usta.dgn.type)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : alarmType MisMatch: exp (%d) recvd (%d) \n",
                     alarmType, rrcMsg->u.nhMngmt.u.usta.dgn.type), 2);

         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
    } /*end of if statement  */
    else
    {
      /* alarmType is always expected from the xml file   */
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhStaInd()  Alarm type field is expected from the xml file to validate\n"));
      RETVALUE(CMXTA_ERR_INT);
    } /* end of else statement  */
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcHdlNhStaInd */

/* XTA Status ends */

/* XTA Trace start */

/*
*
*       Fun:   nhAcHdlNhTrcInd
*
*       Desc:  Call handler for Trace Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhTrcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 nhAcHdlNhTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   NhAccMsgQElm   *rrcMsg = NULLP;
   CmXtaMsgQElm *msg = NULLP;
   Pst      pst;
   U16      dstProcId = 0;
   U16      srcProcId = 0;
   S16      ret = 0;


   TRC2(nhAcHdlNhTrcInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));
   cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",  &dstProcId);
#endif

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = EVTLNHTRCIND;
   
   rrcMsg = (NhAccMsgQElm *)msg->data;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "nhAcHdlNhTrcInd(): No Match, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
#ifdef NH_TRACE_ENABLED
  nhAcValidateTrcInd(&(rrcMsg->u.nhMngmt));
#endif
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);


}/* nhAcHdlNhTrcInd */

/*
*
*       Fun:   nhAcValidateStsCfm
*
*       Desc:  Utility Function to validate Statistics Confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PRIVATE S16 nhAcValidateStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *stsCfm
)
#else
PRIVATE S16 nhAcValidateStsCfm(tcCb, spCb, stsCfm)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *stsCfm;
#endif
{


   TRC2(nhAcValidateStsCfm)

   switch(stsCfm->hdr.elmId.elmnt)
   {
      case STNHGEN:
      {
#ifndef ALIGN_64BIT
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Established RRC Connections %ld\n",  stsCfm->u.sts.u.genSts.numEstbCon);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Failed RRC Connections  %ld\n",  stsCfm->u.sts.u.genSts.numFailCon);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Unexpected Messages Received  %ld\n",  stsCfm->u.sts.u.genSts.numUnExptMsg);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Erroneous Messages Received  %ld\n",  stsCfm->u.sts.u.genSts.numDecErr);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages with encoding errors  %ld\n",  stsCfm->u.sts.u.genSts.numEncErr);
         SPrint(  pbuf  );
#else
         sprintf( pbuf ,   "  Number of Established RRC Connections %d\n",  stsCfm->u.sts.u.genSts.numEstbCon);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Failed RRC Connections  %d\n",  stsCfm->u.sts.u.genSts.numFailCon);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Unexpected Messages Received  %d\n",  stsCfm->u.sts.u.genSts.numUnExptMsg);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Erroneous Messages Received  %d\n",  stsCfm->u.sts.u.genSts.numDecErr);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages with encoding errors  %d\n",  stsCfm->u.sts.u.genSts.numEncErr);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of RLC Unrecoverable Errors  %d\n",  stsCfm->u.sts.u.genSts.numRlcErr);
         SPrint(  pbuf  );
#endif
         break;
      }

      case STNHPROT:
      {

#ifndef ALIGN_64BIT
         /* connection setup message */
         sprintf( pbuf ,   "  Connection Setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );

/* connection setup complete message */
         sprintf( pbuf ,   "  Connection Setup Complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );

/* connection release message */
         sprintf( pbuf ,   "  Connection Release counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );


/* downlink direct transfer message */
         sprintf( pbuf ,   "  Initial Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );


/* uplink direct transfer message */
         sprintf( pbuf ,   "  Uplink Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );


/* Connection Reconfiguration message */
         sprintf( pbuf ,   "  RB setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );


/* Connection Recinfiguration Complete message */
         sprintf( pbuf ,   "  RB setup complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );
#ifdef LTERRC_REL9
         /* UE info request message */
         sprintf( pbuf ,   "  UE info request message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoReq);
         SPrint(  pbuf  );
         /* UE info RSP message */
         sprintf( pbuf ,   "  UE info RSP message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoRsp);
         SPrint(  pbuf  );
         /* Proximity Indication message */
         sprintf( pbuf ,   "  Proximity indication message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.prxmtyInd);
         SPrint(  pbuf  );
#endif/*LTERRC_REL9*/
#else

/* connection setup message */
         sprintf( pbuf ,   "  Connection Setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );

/* connection setup complete message */
         sprintf( pbuf ,   "  Connection Setup Complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );

/* connection release message */
         sprintf( pbuf ,   "  Connection Release counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );


/* downlink direct transfer message */
         sprintf( pbuf ,   "  Initial Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );


/* uplink direct transfer message */
         sprintf( pbuf ,   "  Uplink Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );


/* Connection Recinfiguration message */
         sprintf( pbuf ,   "  RB setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );


/* Connection Recinfiguration Complete message */
         sprintf( pbuf ,   "  RB setup complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );

#ifdef LTERRC_REL9
         /* UE info request message */
         sprintf( pbuf ,   "  UE info request message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoReq);
         SPrint(  pbuf  );
         /* UE info RSP message */
         sprintf( pbuf ,   "  UE info RSP message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoRsp);
         SPrint(  pbuf  );
         /* Proximity Indication message */
         sprintf( pbuf ,   "  Proximity indication message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.prxmtyInd);
         SPrint(  pbuf  );
#endif /*LTERRC_REL9*/
#endif
         break;
      }

      case STNHUE:
      {


#ifndef ALIGN_64BIT
/* connection setup complete message */
         sprintf( pbuf ,   "  Connection Setup Complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );

/* connection release message */
         sprintf( pbuf ,   "  Connection Release counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );


/* downlink direct transfer message */
         sprintf( pbuf ,   "  Initial Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );


/* uplink direct transfer message */
         sprintf( pbuf ,   "  Uplink Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );


/* Connection Reconfiguration message */
         sprintf( pbuf ,   "  RB setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );


/* Connection Recinfiguration Complete message */
         sprintf( pbuf ,   "  RB setup complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );
#ifdef LTERRC_REL9
         /* UE info request message */
         sprintf( pbuf ,   "  UE info request message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoReq);
         SPrint(  pbuf  );
         /* UE info RSP message */
         sprintf( pbuf ,   "  UE info RSP message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoRsp);
         SPrint(  pbuf  );
         /* Proximity Indication message */
         sprintf( pbuf ,   "  Proximity indication message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.prxmtyInd);
         SPrint(  pbuf  );
#endif/*LTERRC_REL9*/
#else

/* connection setup complete message */
         sprintf( pbuf ,   "  Connection Setup Complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connSetupComplete);
         SPrint(  pbuf  );

/* connection release message */
         sprintf( pbuf ,   "  Connection Release counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connRel);
         SPrint(  pbuf  );


/* downlink direct transfer message */
         sprintf( pbuf ,   "  Initial Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.dlInfoTransfer);
         SPrint(  pbuf  );


/* uplink direct transfer message */
         sprintf( pbuf ,   "  Uplink Direct Transfer counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ulInfoTransfer);
         SPrint(  pbuf  );


/* Connection Recinfiguration message */
         sprintf( pbuf ,   "  RB setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfig);
         SPrint(  pbuf  );


/* Connection Recinfiguration Complete message */
         sprintf( pbuf ,   "  RB setup complete counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.connReconfigCom);
         SPrint(  pbuf  );

#ifdef LTERRC_REL9
         /* UE info request message */
         sprintf( pbuf ,   "  UE info request message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoReq);
         SPrint(  pbuf  );
         /* UE info RSP message */
         sprintf( pbuf ,   "  UE info RSP message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.ueInfoRsp);
         SPrint(  pbuf  );
         /* Proximity Indication message */
         sprintf( pbuf ,   "  Proximity indication message counter\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.ueSts.cfm.pdu.prxmtyInd);
         SPrint(  pbuf  );
#endif /*LTERRC_REL9*/
#endif
         break;
      }
      
      case STNHCELL:
      {
#ifndef ALIGN_64BIT
         /* connection setup message */
         sprintf( pbuf ,   "  Connection Setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );
         
         /* connection Reject message */
         sprintf( pbuf ,   "  Connection Reject counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connReject);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connReject);
         SPrint(  pbuf  );
         
         /* connection Connection req message */
         sprintf( pbuf ,   "  Connection Request counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connReq);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connReq);
         SPrint(  pbuf  );
         
         /* connection Reestablishment req message */
         sprintf( pbuf ,   "  Connection Reestablishment req counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connReestabReq);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connReestabReq);
         SPrint(  pbuf  );
         
         /* connection reestablishment message */
         sprintf( pbuf ,   "  Connection Reestablishment counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connReestab);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connReestab);
         SPrint(  pbuf  );
         
         /* connection reestablishment Reject  message */
         sprintf( pbuf ,   "  Connection Reestablishment Reject counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %ld\n",  stsCfm->u.sts.u.cellSts.connReestabRej);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %ld\n",  stsCfm->u.sts.u.cellSts.connReestabRej);
         SPrint(  pbuf  );
         
         /* Number of UEs */
         sprintf( pbuf ,   "  Number of UEs Served \n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of UEs %ld\n",  stsCfm->u.sts.u.cellSts.numUEs);
         SPrint(  pbuf  );
         
         /* Successful HO to EUTRAN */
         sprintf( pbuf ,   "  Successful HO to EUTRAN counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Successful HO to EUTRAN %ld\n",\
               stsCfm->u.sts.u.cellSts.hoToEUTRASucc);
         SPrint(  pbuf  );

         /* Unsuccessful HO From EUTRAN */
         sprintf( pbuf ,   "  Unsuccessful HO from EUTRAN counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Unsuccessful HO from EUTRAN %ld\n",\
               stsCfm->u.sts.u.cellSts.hoFromEUTRAFail);
         SPrint(  pbuf  );

#else/*ALIGN_64BIT*/

         /* connection setup message */
         sprintf( pbuf ,   "  Connection Setup counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connSetup);
         SPrint(  pbuf  );

         /* connection Reject message */
         sprintf( pbuf ,   "  Connection Reject counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connReject);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connReject);
         SPrint(  pbuf  );
         
         /* connection Connection req message */
         sprintf( pbuf ,   "  Connection Request counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connReq);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connReq);
         SPrint(  pbuf  );
         
         /* connection Reestablishment req message */
         sprintf( pbuf ,   "  Connection Reestablishment req counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connReestabReq);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connReestabReq);
         SPrint(  pbuf  );
         
         /* connection reestablishment message */
         sprintf( pbuf ,   "  Connection Reestablishment counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connReestab);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connReestab);
         SPrint(  pbuf  );
         
         /* connection reestablishment Reject  message */
         sprintf( pbuf ,   "  Connection Reestablishment Reject counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages transmitted %d\n",  stsCfm->u.sts.u.cellSts.connReestabRej);
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of messages received %d\n",  stsCfm->u.sts.u.cellSts.connReestabRej);
         SPrint(  pbuf  );
         
         /* Number of UEs */
         sprintf( pbuf ,   "  Number of UEs Served \n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of UEs %d\n",  stsCfm->u.sts.u.cellSts.numUEs);
         SPrint(  pbuf  );
         
         /* Successful HO to EUTRAN */
         sprintf( pbuf ,   "  Successful HO to EUTRAN counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Successful HO to EUTRAN %d\n",\
               stsCfm->u.sts.u.cellSts.hoToEUTRASucc);
         SPrint(  pbuf  );

         /* Unsuccessful HO From EUTRAN */
         sprintf( pbuf ,   "  Unsuccessful HO from EUTRAN counters\n");
         SPrint(  pbuf  );
         sprintf( pbuf ,   "  Number of Unsuccessful HO from EUTRAN %d\n",\
               stsCfm->u.sts.u.cellSts.hoFromEUTRAFail);
         SPrint(  pbuf  );
#endif/*ALIGN_64BIT*/
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcValidateProbeCfm() : Invalid Element Id \n"));
         break;
      }
  }
   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcValidateStsCfm    */


/*
*
*       Fun:   nhAcValidateStaCfm
*
*       Desc:  Utility Function to validate Status Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcValidateStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt     *staCfm
)
#else
PUBLIC S16 nhAcValidateStaCfm(tcCb,spCb,staCfm)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt     *staCfm;
#endif
{
   S16   verRet = 0;
   S16   ptNmbRet = 0;
   S16   sapStaRet = 0;

   U32   numberOfCon = 0;
   S16   xmlVer = 0;
   Txt   xmlPtNmb[50] = {0};
   S16   xmlSapStatus = 0;


   TRC2(nhAcValidateStaCfm)
   switch(staCfm->hdr.elmId.elmnt)
   {

      case STNHGEN:
      {
         verRet = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"numCon",  &numberOfCon);
         if(verRet != CMXTA_ERR_NO_VALUE)
         {
            if(numberOfCon != staCfm->u.ssta.u.genSta.numCon)
            {
#ifndef ALIGN_64BIT
               CMXTA_DBG_ERR((_cmxtap,"nhAcValidateStaCfm() mismatch mVer : Expected : %ld  Received : %ld \n",numberOfCon,staCfm->u.ssta.u.genSta.numCon));
                CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [numCon '%ld']\tExpected: [numCon '%ld']\n",
                staCfm->u.ssta.u.genSta.numCon,numberOfCon), 2);
#else
               CMXTA_DBG_ERR((_cmxtap,"nhAcValidateStaCfm() mismatch mVer : Expected : %d  Received : %d \n",numberOfCon,staCfm->u.ssta.u.genSta.numCon));
                CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [numCon '%d']\tExpected: [numCon '%d']\n",
                staCfm->u.ssta.u.genSta.numCon,numberOfCon), 2);
#endif

               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
      }


      case STNHSID:
      {
         verRet = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"mVer",  &xmlVer);
         if(verRet != CMXTA_ERR_NO_VALUE)
         {
            if(xmlVer != staCfm->u.ssta.u.sysId.mVer)
            {
               CMXTA_DBG_ERR((_cmxtap,"nhAcValidateStaCfm() mismatch mVer : Expected : %d  Received : %d \n",xmlVer,staCfm->u.ssta.u.sysId.mVer));
                CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [mVer '%d']\tExpected: [mVer '%d']\n",
                staCfm->u.ssta.u.sysId.mVer,xmlVer), 2);
               RETVALUE(CMXTA_ERR_INT);
            }
         }

         ptNmbRet = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_TXT ,"ptNmb",  xmlPtNmb);
         if(ptNmbRet != CMXTA_ERR_NO_VALUE)
         {
            if(cmStrcmp((U8 *)xmlPtNmb,(U8 *)staCfm->u.ssta.u.sysId.ptNmb)!= 0)
            {
               CMXTA_DBG_ERR((_cmxtap,"nhAcValidateStaCfm() mismatch PtNmb : Expected : %s  Received : %s \n",xmlPtNmb,staCfm->u.ssta.u.sysId.ptNmb));
                /*CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [PtNmb '%ld']\tExpected: [PtNmb '%ld']\n",
                staCfm->u.ssta.u.sysId.ptNmb,xmlPtNmb), 2);*/

               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
      }

      case STNHUSAP:
      case STNHKWUSAP:
      case STNHCKWSAP:
      case STNHCRGSAP:
      case STNHCPJSAP:
      case STNHPJUSAP:
#ifdef RRC_PHY_CFG_SUPP
      case STNHCTFSAP:
#endif
      {
         sapStaRet = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"sapStatus",  &xmlSapStatus);
         if (sapStaRet != CMXTA_ERR_NO_VALUE)
         {
            if(xmlSapStatus != staCfm->u.ssta.u.sap.sapState)
            {
               CMXTA_DBG_ERR((_cmxtap,"nhAcValidateStaCfm() mismatch sapStatus: Expected : %d  Received : %d \n",xmlSapStatus,staCfm->u.ssta.u.sap.sapState));
               CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [sapStatus '%d']\tExpected: [sapStatus '%d']\n",
                staCfm->u.ssta.u.sap.sapState,xmlSapStatus), 2);

               RETVALUE(CMXTA_ERR_INT);
            }
         }

         break;
      }
   }/* switch */

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcValidateStaCfm    */

/*
*
*       Fun:   nhAcValidateTrcInd
*
*       Desc:  Utility Function to validate Trace Indication
*
*       Ret:   ROK
General Config Requestone
*              
*       File:  nhac_lnhhdl.c
*
*/
#ifdef NH_TRACE_ENABLED
#ifdef ANSI
PRIVATE S16 nhAcValidateTrcInd
(
NhMngmt     *nhMngmt
)
#else
PRIVATE S16 nhAcValidateTrcInd(nhMngmt)
NhMngmt     *nhMngmt;
#endif
{
   U32 i=0;

   TRC2(nhAcValidateTrcInd)
   /* print TRACE */
   CMXTA_DBG_CALLIND((_cmxtap, "Trace Buffer length = %d",nhMngmt->u.trc.len),2);
   CMXTA_DBG_CALLIND((_cmxtap, "\n Trace Buffer is :::"),2);
   for (i=0; i< nhMngmt->u.trc.len; i++)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "%x",nhMngmt->u.trc.evntParm[i]),2);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcValidateTrcInd    */
#endif /* NH_TRACE_ENABLED */


/********************************************************************30**

         End of file:     nhac_lnhhdl.c@@/main/3 - Fri Jul  1 01:13:04 2011

*********************************************************************31*/
/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
