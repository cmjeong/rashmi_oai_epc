

/********************************************************************20**
  
        Name:    CKW user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Handle Primitive code
                  for CKW Interface
 
        File:    kwac_ckwhdl.c

        Sid:      kwac_ckwhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:22 2014
  
        Prg:     chakrapani
  
*********************************************************************21*/

/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */


/*
*
*       Fun:   kwAcHdlCkwBndReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlCkwBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   Inst          kwInst;
   TRC2(kwAcHdlCkwBndReq);
   
   suId = 0;
   spId = 0;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwBndReq(), tcId (%d)\n", tcCb->tcId));
#endif 

   CMXTA_ZERO(&pst, sizeof(Pst));
/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   
   /*cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = CKW_EVT_BND_REQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   NhLiCkwBndReq(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlCkwBndReq --*/

/*
*
*       Fun:   kwAcHdlCkwBndCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlCkwBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *elm;
   KwAcMsgQElm  *kwElm;
   Pst           pst;
   S16           ret;
   SpId          suId;
   Status        status;
   /*Pradeep - start*/
   Inst          kwInst;
   /*Pradeep - end*/
   TRC2(kwAcHdlCkwBndCfm);
 
   ret = ROK;
   suId = 0;
   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)elm->data;
/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));

   /* Expected post structure */
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
/*Pradeep - end*/
   
   pst.event = CKW_EVT_BND_CFM;
   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != kwElm->u.ckwInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.ckwInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != kwElm->u.ckwInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, kwElm->u.ckwInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlCkwBndCfm --*/

 
/*
*
*       Fun:   kwAcHdlCkwUbndReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCkwUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;
   /*Pradeep - start*/
   Inst           kwInst = 0;
   /*Pradeep - end*/
   
   TRC2(kwAcHdlCkwUbndReq);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));

/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));

   /*cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = CKW_EVT_UBND_REQ;
 
   spId = kwAcCb.ckwCb.spId;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   reason = 0; /*-- Reason is unused --*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "reason",  &(reason));
 
   /* Send the request to the GCP --*/
   NhLiCkwUbndReq(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- kwAcHdlCkwUbndReq --*/

/*
*
*       Fun:   kwAcHdlCkwCfgReq
*
*       Desc:  Call handler for Control Request 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCkwCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CkwCfgInfo        *cfgReq;
#if 0
   /*Pradeep -start*/
   Inst              kwInst = 0;
   /*Pradeep -end*/
#endif
   TRC2(kwAcHdlCkwCfgReq);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
   cfgReq = NULLP;
#if 0
/*Pradeep -start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));

   /*-- Get the Pst information here from GCP to GCP User --*/
   /*cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep -end*/
#endif
/* Venki - fixing here */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID+1, 0, 0, FALSE);

   pst.event = CKW_EVT_CFG_REQ;
   
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(cfgReq, sizeof(CkwCfgInfo));
   if (cfgReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwCfgReq(): KW_ALLOC_ACC cfgReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlCkwBuildCfgReq(tcCb, spCb, cfgReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwCfgReq(): kwAcUtlCkwBuildCfgReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCkwCfgReq(&pst, kwAcCb.ckwCb.spId, cfgReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCkwCfgReq */

 
/*
*
*       Fun:   kwAcHdlCkwCfgCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCkwCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
#if 0
   /*Pradeep -start*/
   Inst              kwInst = 0;
   /*Pradeep -end*/
#endif 
   TRC2(kwAcHdlCkwCfgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;
#if 0
   /*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   /*Pradeep - end*/
#endif
/* Venki - fixing here */
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = CKW_EVT_CFG_CFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.ckwCb.suId != kwElm->u.ckwInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.ckwInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (kwAcUtlValdtCfgCfm(tcCb, spCb, kwElm->u.ckwInfo.cfgCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwCfgCfm(): kwAcUtlValdtCfgCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCkwCfgCfm */

  
/*
*
*       Fun:   kwAcHdlCkwUeIdChgReq
*
*       Desc:  Call handler for UeId Change Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwUeIdChgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCkwUeIdChgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CkwUeInfo         *ueInfo, *newUeInfo;
   U32               transId;
 
   TRC2(kwAcHdlCkwUeIdChgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwUeIdChgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwUeIdChgReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
   ueInfo = NULLP;
   newUeInfo = NULLP;
   transId = 0;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = CKW_EVT_CFG_REQ;
   
   /* Allocate memory for CkwUeInfo */
   KW_ALLOC_ACC(ueInfo, sizeof(CkwUeInfo));
   if (ueInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwUeIdChgReq(): KW_ALLOC_ACC ueInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   KW_ALLOC_ACC(newUeInfo, sizeof(CkwUeInfo));
   if (newUeInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwUeIdChgReq(): KW_ALLOC_ACC newUeInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));

   ret = kwAcUtlCkwBuildUeIdChgReq(tcCb, spCb, ueInfo, newUeInfo);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwUeIdChgReq(): kwAcHdlCkwUeIdChgReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCkwUeIdChgReq(&pst, kwAcCb.ckwCb.spId, transId, ueInfo, newUeInfo);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCkwUeIdChgReq */

  
/*
*
*       Fun:   kwAcHdlCkwUeIdChgCfm
*
*       Desc:  Call handler for UeId Change Confirm
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwUeIdChgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCkwUeIdChgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   U16            status;
 
   TRC2(kwAcHdlCkwUeIdChgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
   status   = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCkwCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = CKW_EVT_UEIDCHG_CFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.ckwCb.suId != kwElm->u.ckwInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.ckwInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status",  &(status));
   /* Validate the Configuration confirmation */
   if (status != kwElm->u.ckwInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, kwElm->u.ckwInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCkwUeIdChgCfm */

  
/*
*
*       Fun:   kwAcHdlCkwMapDlUl
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlCkwMapDlUl
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCkwMapDlUl(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   U16            ueId;
   U16            cellId;
   U8             numRb;
   U8             tmpNumRb;
   U8             dir[KWAC_MAX_DRB];
   U8             mode[KWAC_MAX_DRB];
   U8             snType[KWAC_MAX_DRB];
   U8             rbId[KWAC_MAX_DRB];
   U8             rbType[KWAC_MAX_DRB];
   U8             othRbId[KWAC_MAX_DRB];
   U8             othRbType[KWAC_MAX_DRB];
   U8             othUeId[KWAC_MAX_UE];
   U8             othCellId[KWAC_MAX_CELL];
   U8             numLc;
   U8             dlLcId[KWAC_MAX_LC];
   U8             dlLcType[KWAC_MAX_LC];
   U8             ulLcId[KWAC_MAX_LC];
   U8             ulLcType[KWAC_MAX_LC];
   U8             idx;
   KwAcMapDlUlCb  *map;
   KwAcMapDlUl    *mapDlUl;

   TRC2(kwAcHdlCkwMapDlUl);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwMapDlUl(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCkwMapDlUl(), tcId (%d)\n", tcCb->tcId));
#endif
   ueId = 0;
   cellId = 0;
   numLc = 0;
   numRb = 0;
   tmpNumRb = 0;
   map = NULLP;
   mapDlUl = NULLP;

   CMXTA_ZERO(&rbId, sizeof(rbId));
   CMXTA_ZERO(&rbType, sizeof(rbType));
   CMXTA_ZERO(&othRbId, sizeof(othRbId));
   CMXTA_ZERO(&othRbType, sizeof(othRbType));
   CMXTA_ZERO(&othUeId, sizeof(othUeId));
   CMXTA_ZERO(&othCellId, sizeof(othCellId));
   CMXTA_ZERO(&dlLcId, sizeof(dlLcId));
   CMXTA_ZERO(&dlLcType, sizeof(dlLcType));
   CMXTA_ZERO(&ulLcId, sizeof(ulLcId));
   CMXTA_ZERO(&ulLcType, sizeof(ulLcType));
   CMXTA_ZERO(&dir, sizeof(dir));
   CMXTA_ZERO(&mode, sizeof(mode));
   CMXTA_ZERO(&snType, sizeof(snType));

   /* Mapping will be done per Ue/Cell basis.
    * Each UE/CELL has to map seperately.
    * Tag for the mapping of UE Logica Channels looks like below:
    * <tapa.ckw.mapdlul ueId="1" cellId="1"
    *    numRb="5"
    *    dir="1:2:1:2:1"
    *    snType="0:0:0:0:0"
    *    mode="1:1:1:1:1"
    *    rbId="1:2:3:4:5"
    *    rbType="0:1:1:1:1"
    *    othRbId="2:1:4:3:5" othUeId="1:1:1:1:1" othCellId="1:1:1:1:1"
    *    othRbType="0:1:1:1:1"
    *    dlLcId="1:1:2:2:3" dlLcType="1:1:2:2:3"
    *    ulLcId="1:1:2:2:3" ulLcType="1:1:2:2:3" />
    */
   /* kw005.201 removed redundant code */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &cellId);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRb",  &(numRb));

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dir", dir, &tmpNumRb);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "mode", mode, &tmpNumRb);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "snType", snType, &tmpNumRb);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "rbId", rbId, &tmpNumRb);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "othRbId", othRbId, &tmpNumRb);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "rbType", rbType, &tmpNumRb);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "othRbType", othRbType, &tmpNumRb);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "othUeId", othUeId, &tmpNumRb);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "othCellId", othCellId, &tmpNumRb);

   /* Logical Channel */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dlLcId", dlLcId, &tmpNumRb);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dlLcType", dlLcType, &tmpNumRb);

   /* Other Logical Channel */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "ulLcId", ulLcId, &tmpNumRb);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "ulLcType", ulLcType, &tmpNumRb);
 
   map = &kwAcCb.mapDlUlCb;

   for (idx = 0; idx < map->count; idx++)
   {
      if ((ueId == map->mapDlUl[idx].ueId) &&
            (cellId == map->mapDlUl[idx].cellId))
      {
         mapDlUl = &map->mapDlUl[idx];
      }
   }

   if (mapDlUl == NULLP)
   {
      map->mapDlUl[map->count].ueId = ueId;
      map->mapDlUl[map->count].cellId = cellId;

      mapDlUl = &map->mapDlUl[map->count];
      map->count++;
   }

   mapDlUl->numRb += numRb;

   for (idx = 0; idx < numRb; idx++)
   {
      U8 id = rbId[idx];
      /* First fill RB CBs Information */
      /* rbId is the index to particular UE/CELL CB */
      if (rbType[idx] == CM_LTE_SRB)
      {
         mapDlUl->srbCb[id].dir = dir[idx];
         mapDlUl->srbCb[id].mode = mode[idx];
         mapDlUl->srbCb[id].snType = snType[idx];
         mapDlUl->srbCb[id].rbId = rbId[idx];
         mapDlUl->srbCb[id].rbType = rbType[idx];
         mapDlUl->srbCb[id].othRlcId.rbId = othRbId[idx];
         mapDlUl->srbCb[id].othRlcId.rbType = othRbType[idx];
         mapDlUl->srbCb[id].othRlcId.ueId = othUeId[idx];
         mapDlUl->srbCb[id].othRlcId.cellId = othCellId[idx];
         mapDlUl->srbCb[id].dlLc.lcId = dlLcId[idx];
         mapDlUl->srbCb[id].dlLc.lcType = dlLcType[idx];
         mapDlUl->srbCb[id].ulLc.lcId = ulLcId[idx];
         mapDlUl->srbCb[id].ulLc.lcType = ulLcType[idx];
      }
      else
      {
         mapDlUl->drbCb[id].dir = dir[idx];
         mapDlUl->drbCb[id].mode = mode[idx];
         mapDlUl->drbCb[id].snType = snType[idx];
         mapDlUl->drbCb[id].rbId = rbId[idx];
         mapDlUl->drbCb[id].rbType = rbType[idx];
         mapDlUl->drbCb[id].othRlcId.rbId = othRbId[idx];
         mapDlUl->drbCb[id].othRlcId.rbType = othRbType[idx];
         mapDlUl->drbCb[id].othRlcId.ueId = othUeId[idx];
         mapDlUl->drbCb[id].othRlcId.cellId = othCellId[idx];
         mapDlUl->drbCb[id].dlLc.lcId = dlLcId[idx];
         mapDlUl->drbCb[id].dlLc.lcType = dlLcType[idx];
         mapDlUl->drbCb[id].ulLc.lcId = ulLcId[idx];
         mapDlUl->drbCb[id].ulLc.lcType = ulLcType[idx];
      }

      id = dlLcId[idx];
      /* Later Fill LC CBs Information */
      mapDlUl->lcCb[id - 1].dir = dir[idx];
      mapDlUl->lcCb[id - 1].mode = mode[idx];
      mapDlUl->lcCb[id - 1].snType = snType[idx];
      mapDlUl->lcCb[id - 1].rbId = rbId[idx];
      mapDlUl->lcCb[id - 1].rbType = rbType[idx];
      mapDlUl->lcCb[id - 1].othRlcId.rbId = othRbId[idx];
      mapDlUl->lcCb[id - 1].othRlcId.rbType = othRbType[idx];
      mapDlUl->lcCb[id - 1].othRlcId.ueId = othUeId[idx];
      mapDlUl->lcCb[id - 1].othRlcId.cellId = othCellId[idx];
      mapDlUl->lcCb[id - 1].dlLc.lcId = dlLcId[idx];
      mapDlUl->lcCb[id - 1].dlLc.lcType = dlLcType[idx];
      mapDlUl->lcCb[id - 1].ulLc.lcId = ulLcId[idx];
      mapDlUl->lcCb[id - 1].ulLc.lcType = ulLcType[idx];
   }

   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCkwMapDlUl */

/********************************************************************30**
         End of file:     kwac_ckwhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:22 2014
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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3      kw005.201 ap     1. Removed redundant code.
*********************************************************************91*/

