
/********************************************************************20**

     Name:    SIP 

     Type:    C source file

     Desc:    C code for Handler functions for LSG interface

     File:    cm_xta_lsghdl.c

     Sid:      cm_xta_lsghdl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:22 2015

     Prg:     sm 

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


static  ProcId    crntActvProc = CMXTA_PROCID_SLAVE1;
/* Donot change the values of these hash Defines and these defines 
 *  are used in this file only.
 */

PRIVATE Void cmXtaUtlSgBuildGenCfgReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,SgMngmt     *sgMngmt));
PRIVATE Void cmXtaUtlSgBuildEntCfgReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,SgMngmt     *sgMngmt));
PRIVATE Void cmXtaUtlSgBuildEnableNodeReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,SgMngmt     *sgMngmt));
PRIVATE Void cmXtaUtlSgBuildDisableNodeReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,SgMngmt     *sgMngmt));
PRIVATE Void cmXtaUtlSgBuildSwapNodeReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,SgMngmt     *sgMngmt));
PRIVATE Void cmXtaUtlSgBuildCntrlSwitchNodeReq ARGS(( ProcId srcProcId, ProcId  dstProcId,SgMngmt     *sgMngmt));
PRIVATE Void cmXtaUtlSgBuildAbortReq ARGS(( CmXtaTCCb    *tcCb, CmXtaSpCb  *spCb,SgMngmt     *sgMngmt));
/*
*
*       Fun:   cmXtaHdlSgGenCfgReq
*
*       Desc:  Call handler for General config request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cfg;
   Pst      pst;
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgGenCfgReq)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgGenCfgReq(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cfg, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildGenCfgReq(tcCb, spCb, &cfg);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager General Configuration request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgGenCfgReq */

/*
*
*       Fun:   cmXtaHdlSgEntCfgReq
*
*       Desc:  Call handler for Entity config request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgEntCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgEntCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cfg;
   Pst      pst;
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgEntCfgReq)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgEntCfgReq(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cfg, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);



   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildEntCfgReq(tcCb, spCb, &cfg);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STSGENT, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager Entity Configuration request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCfgReq(&pst, &cfg);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgEntCfgReq */

/*
*
*       Fun:   cmXtaHdlSgAbort
*
*       Desc:  Call handler for abort control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgAbort
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgAbort(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cntrl;
   Pst      pst;
/* so003.202 : Updated for SIP FTHA */
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgAbort)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgAbort(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildAbortReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager abort control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgAbort */

/* cm_xta_lsghdl_c_001.main_1: Added function to send the debug control for SG */
/*
*
*       Fun:   cmXtaHdlSgDebugCntrlReq
*
*       Desc:  Call handler for debug control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgDebugCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgDebugCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cntrl;
   Pst      pst;
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgDebugCntrlReq)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgDebugCntrlReq(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   cmMemset ((U8 *) &cntrl  , 0, sizeof (SgMngmt));
   cntrl.apiType                  = LSG_HI_API;
   cntrl.t.hi.cntrl.action        = LSG_AENA;
   cntrl.t.hi.cntrl.subAction     = SADBG;
   cntrl.t.hi.cntrl.u.dbg.dbgMask = 0x1FFF;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager debug control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* "cmXtaHdlSgDebugCntrlReq */
 

/*
*
*       Fun:   cmXtaHdlSgSwapNode
*
*       Desc:  Call handler for swap node control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgSwapNode
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgSwapNode(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cntrl;
   Pst      pst;
/* so003.202 : Updated for SIP FTHA */
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgSwapNode)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgSwapNode(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildSwapNodeReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager swap node control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgSwapNode */

/*
*
*       Fun:   cmXtaControlSwitch
*
*       Desc:  Call handler for Control SW node control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaControlSwitch
(
)
#else
PUBLIC S16 cmXtaControlSwitch()
#endif
{
   SgMngmt  cntrl;
   Pst      pst;
/* so003.202 : Updated for SIP FTHA */
   ProcId       srcProcId;
   ProcId       dstProcId;
   Buffer        *mBuf;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaControlSwitch)


   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = crntActvProc;
   if (crntActvProc == CMXTA_PROCID_SLAVE1)
      dstProcId = CMXTA_PROCID_SLAVE2;
   else
      dstProcId = CMXTA_PROCID_SLAVE1;

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, CMXTA_PROCID_MASTER, CMXTA_PROCID_MASTER, TRUE);
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildCntrlSwitchNodeReq(srcProcId, dstProcId, &cntrl);

   /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl); 
   crntActvProc = dstProcId;

   printf("\n Current Active ProcId = %d \n", crntActvProc);
   RETVALUE(CMXTA_ERR_NONE);
}  /* cmXtaControlSwitch */

/*
*
*       Fun:   cmXtaUtlSgBuildCntrlSwitchNodeReq
*
*       Desc:  Call handler for Build Control SW
*              node control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlSgBuildCntrlSwitchNodeReq
(
ProcId         srcProcId,    /* tcCb data structure  */
ProcId         dstProcId,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildCntrlSwitchNodeReq(srcProcId, dstProcId, sgMngmt)
ProcId        srcProcId;    /* tcCb data structure  */
ProcId        dstProcId;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiSwapNode *swapReq; 
   Ent          entList[LSG_MAX_ENTS];
   U8           nmb;
   S16          i;

   TRC2(cmXtaUtlSgBuildCntrlSwitchNodeReq)

   swapReq   = &(sgMngmt->t.hi.cntrl.u.swapNode);
   cmMemset ((U8 *) swapReq  , 0, sizeof (SgHiSwapNode));   

  /*----------- Fill Entity Configuration Parameters ---------*/
  
   /*-- ACtion is enable --*/
   sgMngmt->apiType           = LSG_HI_API;
   sgMngmt->t.hi.cntrl.action = LSG_ASWAP;
   sgMngmt->t.hi.cntrl.subAction = NOTUSED;

   swapReq->srcProcId = srcProcId;

   swapReq->dstProcId = dstProcId;

   swapReq->nmbEnts = 1;

   i = 0;

#ifdef SO
   swapReq->entList[i].ent = ENTSO;
#endif /* SO */
#ifdef SZ
   swapReq->entList[i].ent = ENTSZ;
#endif /* SZ */
#ifdef AQ
   swapReq->entList[i].ent = ENTAQ;
#endif /* AQ */

   RETVOID;
} /* cmXtaUtlSgBuildCntrlSwitchNodeReq */

/*
*
*       Fun:   cmXtaHdlSgDisableNode
*
*       Desc:  Call handler for disable node control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgDisableNode
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgDisableNode(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cntrl;
   Pst      pst;
/* so003.202 : Updated for SIP FTHA */
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgDisableNode)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgDisableNode(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);


   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildDisableNodeReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager disable node control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgDisableNode */




/*
*
*       Fun:   cmXtaHdlSgEnableNode
*
*       Desc:  Call handler for Enable node control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlSgEnableNode
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlSgEnableNode(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   SgMngmt  cntrl;
   Pst      pst;
/* so003.202 : Updated for SIP FTHA */
   ProcId       srcProcId;
   ProcId       dstProcId;
   
   CmXtaTxnCb* txnCb; 

   TRC2(cmXtaHdlSgEnableNode)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgEnableNode(): tcId (%ld)\n", tcCb->tcId));

   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &dstProcId);
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   cmXtaUtlSgBuildEnableNodeReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending System Manager Enable node control request\n"));

   /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgEnableNode */

/*
*
*       Fun:   cmXtaHdlSgCntrlCfm
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
PUBLIC S16 cmXtaHdlSgCntrlCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 cmXtaHdlSgCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
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
   cmXtaGetPst(&pst, ENTSG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

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
*       Fun:   cmXtaHdlSgCfgCfm
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
PUBLIC S16 cmXtaHdlSgCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 cmXtaHdlSgCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm      *msg;
   CmXtaFthaMsgQElm  *sgMsg;
   CmStatus          status;
   Pst               pst;
   S16               ret;
   ProcId            srcProcId;
   ProcId            dstProcId;

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlSgCfgCfm(): tcId (%ld)\n", tcCb->tcId));

   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);

   sgMsg = (CmXtaFthaMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTSG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   pst.event = EVTLSGCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlSgCfgCfm() : No Match, not for this test case\n"));
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
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlSgCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlSgCfgCfm */

/*
*
*       Fun:   cmXtaUtlSgBuildGenCfgReq
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
PRIVATE Void cmXtaUtlSgBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildGenCfgReq(tcCb, spCb, sgMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiGenCfg    *genCfg; 
   Pst            pst;
   ProcId       srcProcId;
   ProcId       dstProcId;

   TRC2(cmXtaUtlSgBuildGenCfgReq)

   genCfg   = &(sgMngmt->t.hi.cfg.gen);
   cmMemset ((U8 *) genCfg  , 0, sizeof (SgHiGenCfg));   

  /*----------- Fill General Configuration Parameters ---------*/
   sgMngmt->apiType                    = LSG_HI_API;
   genCfg->maxSysNodes                 = CMXTA_SG_MAX_SYS_NODES;
   genCfg->maxSysEnts                  = CMXTA_SG_MAX_SYS_ENTS;
   /* cm_xta_lsghdl_c_001.main_1: Added the value for maxEntRsets */
   genCfg->maxEntRsets                 = 1;
   genCfg->tmrRes                      = CMXTA_SG_TMR_RES;
   genCfg->rtxTimerCfg.enb               = TRUE;
   genCfg->rtxTimerCfg.val               = CMXTA_SG_RTX_TM;
   genCfg->rtxLongTimerCfg.enb           = TRUE;
   genCfg->rtxLongTimerCfg.val           = CMXTA_SG_LONG_RTX_TM;
   genCfg->rtxCount                    = CMXTA_SG_RTX_COUNT;
   genCfg->peerExists                  = TRUE;
   genCfg->peerMemory.region           = DFLT_REGION;
   genCfg->peerMemory.pool             = DFLT_POOL;
   genCfg->txHeartBeatTimerCfg.enb     = FALSE;
   genCfg->txHeartBeatTimerCfg.enb     = FALSE;
   genCfg->rxHeartBeatTimerCfg.val     = CMXTA_SG_TX_HEARTBEAT;
   genCfg->rxHeartBeatTimerCfg.val     = CMXTA_SG_RX_HEARTBEAT;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "proc", &srcProcId);
   cmXtaGetPst(&pst, ENTSG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(genCfg->smPst),
            (U8 *) &(pst),
            (PTR) sizeof(Pst));

   cmXtaGetPst(&pst, ENTSG, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(genCfg->remotePst),
            (U8 *) &(pst),
            (PTR) sizeof(Pst));

   RETVOID;
} /* cmXtaUtlSgBuildGenCfgReq() */

/*
*
*       Fun:   cmXtaUtlSgBuildEntCfgReq
*
*       Desc:  Utility Function to Build Entity Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsgutl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlSgBuildEntCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildEntCfgReq(tcCb, spCb, sgMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiEntCfg    *entCfg; 
   U8             nmb;
   Ent            userList[LSG_MAX_ASSOC];        /* lst of service users */
   Inst           userInst[LSG_MAX_ASSOC];        /* lst of user insts.   */
   Ent            provList[LSG_MAX_ASSOC];        /* lst of service provs */
   Inst           provInst[LSG_MAX_ASSOC];        /* lst of prov. insts.  */
   S16            i;
   

   TRC2(cmXtaUtlSgBuildEntCfgReq)


   sgMngmt->apiType                    = LSG_HI_API;
   entCfg   = &(sgMngmt->t.hi.cfg.ent);
   cmMemset ((U8 *) entCfg  , 0, sizeof (SgHiEntCfg));   

  /*----------- Fill Entity Configuration Parameters ---------*/
  
   entCfg->entId                 = ENTSO;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "entId",  &(entCfg->entId));

   entCfg->instId                 = CMXTA_INST_ID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "instId",  &(entCfg->instId));

   /*-- Default is conventional all FT/HA layers would need to 
      explicitly provide this value through XML --*/
   entCfg->entType                 = LSG_HI_ENT_CONVENTIONAL;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "entType",  &(entCfg->entType));
   
   /*-- For FTHA this value will be 1 for DFTHA this may change
      user will need to modify XML for that --*/
   entCfg->nmbCritical = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "nmbCritical",  &(entCfg->nmbCritical));

   entCfg->nmbUsers = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "nmbUsers",  &(entCfg->nmbUsers));

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "userList",
         userList,
         &nmb);

   for (i = 0; i < nmb; i++)
      entCfg->userList[i] = userList[i];

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "userInst",
         userInst,
         &nmb);

   for (i = 0; i < nmb; i++)
      entCfg->userInst[i] = userInst[i];

   entCfg->nmbProv = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "nmbProv",  &(entCfg->nmbProv));

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "provList",
         provList,
         &nmb);
   for (i = 0; i < nmb; i++)
      entCfg->provList[i] = provList[i];

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "provInst",
         provInst,
         &nmb);

   for (i = 0; i < nmb; i++)
      entCfg->provInst[i] = provInst[i];

   RETVOID;
} /* cmXtaUtlSgBuildEntCfgReq() */

/*
*
*       Fun:   cmXtaUtlSgBuildEnableNodeReq
*
*       Desc:  Utility Function to Build enable node cntrl req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsgutl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlSgBuildEnableNodeReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildEnableNodeReq(tcCb, spCb, sgMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiEnableNode *enableReq; 
   Ent          entList[LSG_MAX_ENTS];
   Inst         instList[LSG_MAX_ENTS];
   U8           procUsage[LSG_MAX_ENTS];                      /* node usage flag      */
   Bool         lastProc[LSG_MAX_ENTS];                      /* node usage flag      */
   U8           nmb;
   S16          i;
   

   TRC2(cmXtaUtlSgBuildEnableNodeReq)

   sgMngmt->apiType                    = LSG_HI_API;
   enableReq   = &(sgMngmt->t.hi.cntrl.u.enableNode);
   cmMemset ((U8 *) enableReq  , 0, sizeof (SgHiEnableNode));   

  /*----------- Fill Entity Configuration Parameters ---------*/
  
   /*-- ACtion is enable --*/
   sgMngmt->t.hi.cntrl.action = LSG_AENABLE;
   sgMngmt->t.hi.cntrl.subAction = NOTUSED;

   enableReq->procId = CMXTA_PROCID_SLAVE1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "enableProcId",  &(enableReq->procId));

   enableReq->nmbEnts = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "nmbEnts",  &(enableReq->nmbEnts));

   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "entList",
         entList,
         &nmb);

   for (i = 0; i < nmb; i++)
      enableReq->entList[i].entId = entList[i];

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "instList",
         instList,
         &nmb);

   for (i = 0; i < nmb; i++)
      enableReq->entList[i].instId = instList[i];

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "procUsage",
         procUsage,
         &nmb);

   for (i = 0; i < nmb; i++)
      enableReq->entList[i].procUsage = procUsage[i];

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_BOOL, CMXTA_SEP_COLON,
         "lastProc",
         lastProc,
         &nmb);

  for (i = 0; i < nmb; i++)
      enableReq->entList[i].lastProc = lastProc[i];

   RETVOID;
} /* cmXtaUtlSgBuildEnableNodeReq() */


/*
*
*       Fun:   cmXtaUtlSgBuildDisableNodeReq
*
*       Desc:  Utility Function to Build disable node cntrl req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsgutl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlSgBuildDisableNodeReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildDisableNodeReq(tcCb, spCb, sgMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiDisableNode *disableReq; 
   Ent          entList[LSG_MAX_ENTS];
   Inst         instList[LSG_MAX_ENTS];
   U8           nmb;
   S16          i;

   TRC2(cmXtaUtlSgBuildEnableNodeReq)

   sgMngmt->apiType                    = LSG_HI_API;
   disableReq   = &(sgMngmt->t.hi.cntrl.u.disableNode);
   cmMemset ((U8 *) disableReq  , 0, sizeof (SgHiDisableNode));   

  /*----------- Fill Entity Configuration Parameters ---------*/
  
   /*-- ACtion is enable --*/
   sgMngmt->t.hi.cntrl.action = LSG_ADISABLE;
   sgMngmt->t.hi.cntrl.subAction = NOTUSED;

   disableReq->forcedDisable = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "forcedDisable",  &(disableReq->forcedDisable));

   disableReq->procId = CMXTA_PROCID_SLAVE1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId",  &(disableReq->procId));

   disableReq->nmbEnts = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "nmbEnts",  &(disableReq->nmbEnts));

   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "entList",
         entList,
         &nmb);

   for (i = 0; i < nmb; i++)
      disableReq->entList[i].ent = entList[i];

   nmb = 0;
   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "instList",
         instList,
         &nmb);

   for (i = 0; i < nmb; i++)
      disableReq->entList[i].inst = instList[i];

   RETVOID;
} /* cmXtaUtlSgBuildDisableNodeReq() */


/*
*
*       Fun:   cmXtaUtlSgBuildSwapNodeReq
*
*       Desc:  Utility Function to Build swap node cntrl req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsgutl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlSgBuildSwapNodeReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildSwapNodeReq(tcCb, spCb, sgMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiSwapNode *swapReq; 
   Ent          entList[LSG_MAX_ENTS];
   U8           nmb;
   S16          i;

   TRC2(cmXtaUtlSgBuildSwapNodeReq)

   swapReq   = &(sgMngmt->t.hi.cntrl.u.swapNode);
   cmMemset ((U8 *) swapReq  , 0, sizeof (SgHiSwapNode));   

  /*----------- Fill Entity Configuration Parameters ---------*/
  
   /*-- ACtion is enable --*/
   sgMngmt->apiType           = LSG_HI_API;
   sgMngmt->t.hi.cntrl.action = LSG_ASWAP;
   sgMngmt->t.hi.cntrl.subAction = NOTUSED;

   swapReq->srcProcId = CMXTA_PROCID_SLAVE1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProcId",  &(swapReq->srcProcId));

   swapReq->dstProcId = CMXTA_PROCID_SLAVE1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProcId",  &(swapReq->dstProcId));

   swapReq->nmbEnts = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "nmbEnts",  &(swapReq->nmbEnts));

   cmXtaXmlGetValList(NULLP, spCb->childStep,
         CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
         "entList",
         entList,
         &nmb);

   for (i = 0; i < nmb; i++)
      swapReq->entList[i].ent = entList[i];

   RETVOID;
} /* cmXtaUtlSgBuildSwapNodeReq */

/*
*
*       Fun:   cmXtaUtlSgBuildAbortReq
*
*       Desc:  Utility Function to Build abort cntrl req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsgutl.c
*
*/
#ifdef ANSI
PRIVATE Void cmXtaUtlSgBuildAbortReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SgMngmt        *sgMngmt   
)
#else
PRIVATE Void cmXtaUtlSgBuildAbortReq(tcCb, spCb, sgMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SgMngmt       *sgMngmt;   
#endif
{
   /* local variables */
   SgHiAbort *abortReq; 

   TRC2(cmXtaUtlSgBuildAbortReq)

   abortReq   = &(sgMngmt->t.hi.cntrl.u.abort);
   cmMemset ((U8 *) abortReq  , 0, sizeof (SgHiAbort));   

  /*----------- Fill Entity Configuration Parameters ---------*/
  
   /*-- ACtion is enable --*/
   sgMngmt->t.hi.cntrl.action = LSG_AMK_ABORT;
   sgMngmt->t.hi.cntrl.subAction = NOTUSED;

   /*-- TODO: Shashank figure this part out --*/
   abortReq->transId = 0xfffff;

   RETVOID;
} /* cmXtaUtlSgBuildSwapNodeReq */



/********************************************************************30**

         End of file:     cm_xta_lsghdl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:22 2015

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
/main/1      ----      aj      1. main release
/main/2      ---      cm_xta_lsghdl_c_001.main_1 pka 1. Integration test fixes.
*********************************************************************91*/



