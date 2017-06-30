

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     kwac_rguhdl.c 
  
     Sid:      kwac_rguhdl.c@@/main/TeNB_Main_BR/tenb_br_tdd_e1.2_4.0.0_cr/1 - Thu Nov 20 22:41:28 2014
  
     Prg:      sm
  
**********************************************************************/

/** @file kwac_rguhdl.c
@brief This file contains the definitions for XTA RGU interface handler 
functions.
*/


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
#include "kwac_rgu.h"      /* CKW Acceptance defines */

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
#include "kwac_rgu.x"      /* CKW Acceptance defines */
#include "kwac_kwu.x"
#ifdef KW_PDCP
#include "kwac_pju.x"
#include "kwac_lib.x"
#endif /* KW_PDCP */

U64  glblTtiCnt = 0;

/************************************************************************
                             RGU Interface Handler Functions
************************************************************************/
/**
 * @brief XTA Bind Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguBndReq
 *     
 *     Issues a bindrequest from Dummy RLC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   SpId           spId;
/*Pradeep - start*/
   Inst           kwInst;
/*Pradeep - end*/

   TRC2(kwAcHdlRguBndReq);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
   spId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguBndReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
/*Pradeep - end*/
   pst.event = KWAC_RGU_EVT_BND_REQ;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != kwElm->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   if (spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Store suId and spId */
   kwAcCb.rguCb.suId = kwElm->u.rguInfo.suId;
   kwAcCb.rguCb.spId = kwElm->u.rguInfo.spId;
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguBndReq --*/


/**
 * @brief XTA Bind Confirm Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguBndCfm 
 *     
 *     Validates a Bind Confirm from MAC to Dummy RLC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;
   U8            status;
/*Pradeep - start*/
   Inst          kwInst;
/*Pradeep - end*/
   
   TRC2(kwAcHdlRguBndCfm);
   
   suId = 0;
   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif   
   CMXTA_ZERO(&pst, sizeof(Pst));

/*Pradeep - start*/   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   /*cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/
   
   pst.event = KWAC_RGU_EVT_BND_CFM;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   if (suId != kwAcCb.rguCb.suId)
      suId = kwAcCb.rguCb.suId;

   /* Send the request to the MAC --*/
   RgUiRguBndCfm(&pst, kwAcCb.rguCb.suId, status);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlRguBndCfm --*/
 

/**
 * @brief XTA UnBind Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguUbndReq 
 *     
 *     Issues an Un-Bind request from Dummy RLC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/ 
#ifdef ANSI
PUBLIC S16 kwAcHdlRguUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlRguUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SpId           spId;
   Reason         reason;
 
   TRC2(kwAcHdlRguUbndReq);

   qElm     = NULLP;
   kwElm    = NULLP;
   spId     = 0;
   reason   = 0;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWAC_RGU_EVT_UBND_REQ;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "reason",  &(reason));
 
   if (reason != kwElm->u.rguInfo.reason)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Reason MisMatch: exp (%d) rcvd (%d) \n",
                  reason, kwElm->u.rguInfo.reason), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlRguUbndReq --*/


/**
 * @brief XTA Common Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguCDatReq 
 *     
 *     Issues a Cdat request from Dummy RLC to MAC. This handler 
 *     Considers data that tester has provided and also the data
 *     that the test engine has cached from the previous status
 *     response and indication. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguCDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  kwAcHdlRguCDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SpId           spId;
   S16            ret;
 
   TRC2(kwAcHdlRguCDatReq);

   qElm     = NULLP;
   kwElm    = NULLP;
   spId     = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCDatReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguCDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWAC_RGU_EVT_CDAT_REQ;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (kwAcCb.rguCb.spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate CDatReq recived for BO and validate PDU in case of BCCH/PCCH
    * and send in uplink in case of CCCH */
   ret = kwAcUtlValdtCDatReq(tcCb, spCb, kwElm->u.rguInfo.u.cDatReq);
   if (ret != CMXTA_ERR_NONE)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(ret);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlRguCDatReq --*/


/**
 * @brief XTA Dedicated Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguDDatReq  
 *     
 *     Issues a Ddat request from Dummy RLC to MAC. This handler 
 *     Considers data that tester has provided and also the data
 *     that the test engine has cached from the previous status
 *     response and indication. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguDDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  kwAcHdlRguDDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SpId           spId;
   S16            ret = CMXTA_ERR_NONE;
 
   TRC2(kwAcHdlRguDDatReq);

   qElm     = NULLP;
   kwElm    = NULLP;
   spId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDDatReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguDDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWAC_RGU_EVT_DDAT_REQ;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (kwAcCb.rguCb.spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate Data Request */
   ret = kwAcUtlValdtDDatReq(tcCb, spCb, kwElm->u.rguInfo.u.dDatReq);
   if (ret != CMXTA_ERR_NONE)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(ret);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlRguDDatReq --*/


/**
 * @brief XTA Common Channel Status Response Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguCStaRsp  
 *     
 *     Issues a Cstatus response from Dummy-RLC to MAC.
 *     It also caches the required information, that would 
 *     be used to formulate/validate subsequent staInd/DatReq/
 *     DatInd primitives.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguCStaRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  kwAcHdlRguCStaRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
 
   TRC2(kwAcHdlRguCStaRsp);

   qElm     = NULLP;
   kwElm    = NULLP;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCStaRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCStaRsp(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguCStaRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWAC_RGU_EVT_CSTA_RSP;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   if (kwAcCb.rguCb.spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.rguCb.spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (kwAcUtlValdtCStaRsp(tcCb, spCb, kwElm->u.rguInfo.u.cStaRsp) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "Failed kwAcUtlValdtCStaRsp: Validation Failed \n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlRguCStaRsp --*/


/**
 * @brief XTA Dedicated Channel Status Response Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguDStaRsp  
 *     
 *     Issues a Dstatus response from Dummy-RLC to MAC.
 *     It also caches the required information, that would 
 *     be used to formulate/validate subsequent staInd/DatReq/
 *     DatInd primitives.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguDStaRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  kwAcHdlRguDStaRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
 
   TRC2(kwAcHdlRguDStaRsp);

   qElm     = NULLP;
   kwElm    = NULLP;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDStaRsp(), tcId (%ld)\n", tcCb->tcId));
#else
    CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDStaRsp(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguDStaRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWAC_RGU_EVT_DSTA_RSP;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   if (kwAcCb.rguCb.spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.rguCb.spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate DStaRsp for BO */
   if (kwAcUtlValdtDStaRsp(tcCb, spCb, kwElm->u.rguInfo.u.dStaRsp) !=
         CMXTA_ERR_NONE)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlRguDStaRsp --*/


/**
 * @brief XTA Common Channel Data Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguCDatInd  
 *     
 *     Validates Data Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguCDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguCDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;
   Pst               pst;
   SuId              suId;
   RguCDatIndInfo    *datInd;

   TRC2(kwAcHdlRguCDatInd);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
    CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCDatInd(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
/*Pradeep - start hard coded the instance id to 1*/
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID+1, 0, 0, FALSE);
/*Pradeep - end*/   
   pst.event = KWAC_RGU_EVT_CDAT_IND;
 
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(datInd, sizeof(RguCDatIndInfo));
   if (datInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguCDatInd(): KW_ALLOC datInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlBuildCDatInd(tcCb, spCb, datInd);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   /* Send the Indication to the RLC --*/
   RgUiRguCDatInd(&pst, kwAcCb.rguCb.suId, datInd);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguCDatInd --*/


/**
 * @brief XTA Dedicated Channel Data Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguDDatInd  
 *     
 *     Validates Data Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguDDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguDDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;
   Pst               pst;
   SuId              suId;
   RguDDatIndInfo    *datInd;

   TRC2(kwAcHdlRguDDatInd);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDDatInd(), tcId (%d)\n", tcCb->tcId)); 
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));
 
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = KWAC_RGU_EVT_DDAT_IND;
 
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(datInd, sizeof(RguDDatIndInfo));
   if (datInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguDDatInd(): KW_ALLOC datInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlBuildDDatInd(tcCb, spCb, datInd);
   if (ret != CMXTA_ERR_NONE)
   {
      KW_FREE_ACC(datInd, sizeof(RguDDatIndInfo));
      RETVALUE(ret);
   }
#ifdef KW_PDCP
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "resetFlag", &(kwAcCb.nhCpjCb.resetFlag));
#endif

   /* Send the Indication to the RLC --*/
   RgUiRguDDatInd(&pst, suId, datInd);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguDDatInd --*/


#ifndef KW_PDCP
/**
 * @brief XTA RX (Receiving) side SDU creation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguRxSduCreate
 *     
 *     Builds the Recieving side of RLC with SDUs expected at KWU interface and
 *     corresponding PDUs to send from RGU interface of RLC.
 *
 *     It is XTA Internal Function for SDU Creation.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguRxSduCreate
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguRxSduCreate(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;

   TRC2(kwAcHdlRguRxSduCreate);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguRxSduCreate(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguRxSduCreate(), tcId (%d)\n", tcCb->tcId));
#endif 
   ret = kwAcUtlBuildRxSduCreate(tcCb, spCb);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguRxSduCreate --*/


/**
 * @brief XTA RX (Receiving) side PDU creation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguRxPduCreate
 *     
 *     Builds the Recieving side of RLC with corresponding PDUs to send from 
 *     RGU interface of RLC.
 *
 *     It is XTA Internal Function for PDU Creation.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguRxPduCreate
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguRxPduCreate(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;

   TRC2(kwAcHdlRguRxPduCreate);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguRxPduCreate(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguRxPduCreate(), tcId (%d)\n", tcCb->tcId));
#endif 
   ret = kwAcUtlBuildRxPduCreate(tcCb, spCb);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguRxPduCreate --*/

#else

/**
 * @brief XTA RX (Receiving) side RLC PDU along with PDCP PDU creation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguRxPdcpPduCreate
 *     
 *     Builds the Recieving side of RLC with corresponding PDUs along with the
 *     proper PDCP PDU as data to send from RGU interface of RLC.
 *
 *     It is XTA Internal Function for PDU Creation.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguRxPdcpPduCreate
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguRxPdcpPduCreate(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;

   TRC2(kwAcHdlRguRxPdcpPduCreate);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguRxPdcpPduCreate(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguRxPdcpPduCreate(), tcId (%d)\n", tcCb->tcId));
#endif 
   ret = kwAcUtlBuildRxPdcpPduCreate(tcCb, spCb);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguRxPdcpPduCreate --*/
#endif /* KW_PDCP */


/**
 * @brief XTA Common Channel Status Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguCStaInd  
 *     
 *     Validates CStatus Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information. It also caches the required information to
 *     used in sub-sequent DatReq/DatInd primitives. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguCStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguCStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;
   Pst               pst;
   RguCStaIndInfo    *staInd;

   TRC2(kwAcHdlRguCStaInd);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguCStaInd(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = KWAC_RGU_EVT_CSTA_IND;
 
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(staInd, sizeof(RguCStaIndInfo));
   if (staInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguCStaInd(): KW_ALLOC staInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlBuildRguCStaInd(tcCb, spCb, staInd);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
   /* Send the Indication to the RLC --*/
   RgUiRguCStaInd(&pst, kwAcCb.rguCb.suId, staInd);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguCStaInd --*/


/**
 * @brief XTA Dedicated Channel Status Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguDStaInd  
 *     
 *     Validates DStatus Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information. It also caches the required information to
 *     used in sub-sequent DatReq/DatInd primitives. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguDStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguDStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;
   Pst               pst;
   SuId              suId;
   RguDStaIndInfo    *staInd;

   TRC2(kwAcHdlRguDStaInd);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguDStaInd(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = KWAC_RGU_EVT_DSTA_IND;
 
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(staInd, sizeof(RguDStaIndInfo));
   if (staInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguDStaInd(): KW_ALLOC staInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   staInd->nmbOfUeGrantPerTti++;

   ret = kwAcUtlBuildRguDStaInd(tcCb, spCb, staInd);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
   /* Send the Indication to the RLC --*/
   RgUiRguDStaInd(&pst, kwAcCb.rguCb.suId, staInd);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguDStaInd --*/

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS

/**
 * @brief XTA Harq Status Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguHqStaInd  
 *     
 *     Sends HqStatus Indication primitive RLC against
 *     tester provided input.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguHqStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguHqStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16               ret;
   Pst               pst;
   SuId              suId;
   RguHarqStatusInd  *hqStaInd;

   TRC2(kwAcHdlRguHqStaInd);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguHqStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguHqStaInd(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = KWAC_RGU_EVT_HQSTA_IND;
 
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(hqStaInd, sizeof(RguHarqStatusInd));
   if (hqStaInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguHqStaInd(): KW_ALLOC staInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlBuildRguHqStaInd(tcCb, spCb, hqStaInd);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
   /* Send the Indication to the RLC --*/
   RgUiRguHqStaInd(&pst, kwAcCb.rguCb.suId, hqStaInd);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguHqStaInd --*/
#ifdef LTE_RLC_R9

/**
 * @brief XTA L2 Measurement UL Ip Throughput request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguL2MUlThrpMeasReq
 *     
 *     Validates LMeasMUlThrpMeasReq primitive recieved from RLC
 *     to Dummy-MAC against tester provided input and cached 
 *     information.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguL2MUlThrpMeasReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlRguL2MUlThrpMeasReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SpId           spId;
   S16            ret = CMXTA_ERR_NONE;
 
   TRC2(kwAcHdlRguL2MUlThrpMeasReq);

   qElm     = NULLP;
   kwElm    = NULLP;
   spId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguL2MUlThrpMeasReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguL2MUlThrpMeasReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguL2MUlThrpMeasReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWAC_RGU_EVT_L2MULTHR_REQ;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (kwAcCb.rguCb.spId != kwElm->u.rguInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.rguInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the request */
   ret = kwAcUtlValdtL2MUlThrpMeasReq(tcCb, spCb, kwElm->u.rguInfo.u.l2mUlThrpMeasReq);
   if (ret != CMXTA_ERR_NONE)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(ret);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
}/*-- kwAcHdlRguL2MUlThrpMeasReq --*/
#endif
#endif

/**
 * @brief Skip Validation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlRguSkipValidation  
 *     
 *     If tester does not want a particular indication from MAC 
 *     to be validated, he can just issue the leaf command SKIP,
 *     This is the corresponding handler function for SKIP, which
 *     will pop off the last received indication, without any 
 *     further processing. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlRguSkipValidation
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlRguSkipValidation(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;

   TRC2(kwAcHdlRguSkipValidation);

   /* kw005.201 removed warning */
   UNUSED(spCb);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguSkipValidation(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlRguSkipValidation(): tcId (%d)\n", tcCb->tcId));
#endif 
   if(cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlRguSkipValidation(): Peek failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*-- Remove the qElm from the Queue --*/
   if(cmXtaPopMsg(&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlRguSkipValidation(): Pop failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*kwAcHdlRguSkipValidation*/


/**
 * @brief Skip Validation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlShutdown  
 *     
 *     If tester does not want a particular indication from MAC 
 *     to be validated, he can just issue the leaf command SKIP,
 *     This is the corresponding handler function for SKIP, which
 *     will pop off the last received indication, without any 
 *     further processing. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlShutdown
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlShutdown(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   U16            idx = 0;
   KwAcRguCDatReq *tmCDatReq = NULLP;
   KwAcRguDDatReq *datReq = NULLP;
   KwAcKwuDatReq  *kwuDatReq = NULLP;
#ifdef KW_PDCP
   KwAcPjuDatReq  *pjuDatReq = NULLP;
#endif

   TRC2(kwAcHdlShutdown);
   /* kw005.201 removed warning */
   UNUSED(spCb);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlShutdown(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlShutdown(): tcId (%d)\n", tcCb->tcId));
#endif 
   /*************************************************************************
    *                      RGU FREE
    ************************************************************************/
   /* Get the PDU tmCDatReq information */
   idx = kwAcUtlRguCDatReqCircQGetFront(&kwAcCb.rguCb.cDatReq);
   while (idx)
   {
      tmCDatReq = &kwAcCb.rguCb.cDatReq.node[idx];
      if (tmCDatReq->isInQ && tmCDatReq->cDatReq)
      {
         KW_FREE_BUF(tmCDatReq->cDatReq->pdu);
         KW_FREE_ACC(tmCDatReq->cDatReq, sizeof(RguCDatReqInfo));
      }
      CMXTA_ZERO(&kwAcCb.rguCb.cDatReq.node[idx], sizeof(KwAcRguCDatReq));
      idx = kwAcUtlRguCDatReqCircQGetNext(&kwAcCb.rguCb.cDatReq, idx);
      kwAcUtlRguCDatReqCircQDequeue(&kwAcCb.rguCb.cDatReq);
   }

   /* Set 0 for DStaInd */
   idx = kwAcUtlRguDStaIndCircQGetFront(&kwAcCb.rguCb.dStaInd);
   while (idx)
   {
      CMXTA_ZERO(&kwAcCb.rguCb.dStaInd.node[idx], sizeof(KwAcRguDStaInd));
      idx = kwAcUtlRguDStaIndCircQGetNext(&kwAcCb.rguCb.dStaInd, idx);
      kwAcUtlRguDStaIndCircQDequeue(&kwAcCb.rguCb.dStaInd);
   }

   /* Free DDatReq Information */
   idx = kwAcUtlRguDDatReqCircQGetFront(&kwAcCb.rguCb.dDatReq);
   while (idx)
   {
      datReq = &kwAcCb.rguCb.dDatReq.node[idx];
      if (datReq->isInQ)
      {
         U16   idx2, idx3, idx4, idx5;
         for(idx5 = 0; idx5 < datReq->dDatReq->nmbOfUeGrantPerTti; idx5++)
         {
            for ( idx4 = 0; idx4 < datReq->dDatReq->datReq[idx5].nmbOfTbs; idx4++)
            {
               RguDatReqTb *datReqTb = &(datReq->dDatReq->datReq[idx5].datReqTb[idx4]);
               for (idx3 = 0; idx3 < datReqTb->nmbLch; idx3++)
               {
                  for (idx2 = 0; idx2 < datReqTb->lchData[idx3].pdu.numPdu; idx2++)
                  {
                     KW_FREE_BUF(datReqTb->lchData[idx3].pdu.mBuf[idx2]);
                  }
               }
            }
         }
         KW_FREE_ACC(datReq->dDatReq, sizeof(RguDDatReqInfo));

         /* Memset to 0 and Dequeue */
         CMXTA_ZERO(datReq, sizeof(KwAcRguDDatReq));
      }

      idx = kwAcUtlRguDDatReqCircQGetNext(&kwAcCb.rguCb.dDatReq, idx);
      kwAcUtlRguDDatReqCircQDequeue(&kwAcCb.rguCb.dDatReq);
   }

   /*************************************************************************
    *                      KWU FREE
    ************************************************************************/
   /* KWU DatReq FREE PRIMITIVES */
   /* RRC - ENTNH Free */
   idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.nhKwuCb.datReq);
   while (idx)
   {
      kwuDatReq = &kwAcCb.nhKwuCb.datReq.node[idx];
      if (kwuDatReq->isInQ)
      {
         KW_FREE_BUF(kwuDatReq->mBuf);
         CMXTA_ZERO(kwuDatReq, sizeof(KwAcKwuDatReq));
      }
      idx = kwAcUtlKwuDatReqCircQGetNext(&kwAcCb.nhKwuCb.datReq, idx);
      kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.nhKwuCb.datReq);
   }

#ifdef KW_PDCP
   /* RRC - ENTNH Free */
   idx = kwAcUtlPjuDatReqCircQGetFront(&kwAcCb.nhPjuCb.datReq);
   while (idx)
   {
      pjuDatReq = &kwAcCb.nhPjuCb.datReq.node[idx];
      if (pjuDatReq->isInQ)
      {
         KW_FREE_BUF(pjuDatReq->mBuf);
         CMXTA_ZERO(pjuDatReq, sizeof(KwAcPjuDatReq));
      }
      idx = kwAcUtlPjuDatReqCircQGetNext(&kwAcCb.nhPjuCb.datReq, idx);
      kwAcUtlPjuDatReqCircQDequeue(&kwAcCb.nhPjuCb.datReq);
   }

   /* PDCP USER - ENTPX Free */
   idx = kwAcUtlPjuDatReqCircQGetFront(&kwAcCb.pxPjuCb.datReq);
   while (idx)
   {
      pjuDatReq = &kwAcCb.pxPjuCb.datReq.node[idx];
      if (pjuDatReq->isInQ)
      {
         Buffer *tmp;
         tmp = pjuDatReq->mBuf->b_cont ;
         while(tmp)
         {
            if(tmp->b_datap->db_ref > 1)
            {
               tmp->b_datap->db_ref = 1;
            }   
            tmp = tmp->b_cont;
         }  
       //  printf("mBuf getting freed in pjuDatReq shutdown %u\n\n", pjuDatReq->mBuf);
         KW_FREE_BUF(pjuDatReq->mBuf);
         CMXTA_ZERO(pjuDatReq, sizeof(KwAcPjuDatReq));
      }
      idx = kwAcUtlPjuDatReqCircQGetNext(&kwAcCb.pxPjuCb.datReq, idx);
      kwAcUtlPjuDatReqCircQDequeue(&kwAcCb.pxPjuCb.datReq);
   }

#else
   /* PDCP - ENTPJ Free */
   idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.pjKwuCb.datReq);
   while (idx)
   {
      kwuDatReq = &kwAcCb.pjKwuCb.datReq.node[idx];
      if (kwuDatReq->isInQ)
      {
         Buffer *tmp;
         tmp = kwuDatReq->mBuf->b_cont ;
         while(tmp)
         {
            if(tmp->b_datap->db_ref > 1)
            {
               tmp->b_datap->db_ref = 1;
            }   
            tmp = tmp->b_cont;
         }  
      //   printf("mBuf getting freed in kwucbDatReq shutdown %u\n\n", kwuDatReq->mBuf);
         KW_FREE_BUF(kwuDatReq->mBuf);
         CMXTA_ZERO(kwuDatReq, sizeof(KwAcKwuDatReq));
      }
      idx = kwAcUtlKwuDatReqCircQGetNext(&kwAcCb.pjKwuCb.datReq, idx);
      kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.pjKwuCb.datReq);
   }
#endif /* KW_PDCP */ 
#ifdef KW_PDCP
   /* For the freeing of KwAcLibCb */
   {
      CmLList       *lstEnt = NULLP;
      CmLListCp     *datQ   = NULLP;
      KwAcLibOutEnt *ent    = NULLP;
      KwAcLibSecEnt *secEnt = NULLP;

      datQ = &(libCb.compCb.compOutList);
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            ent = (KwAcLibOutEnt *)cmLListNode(lstEnt);
            if ( ent->mBuf != NULLP )
            {
               PJ_FREE_BUF(ent->mBuf);
            }
            PJ_FREE(ent, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);
 
      datQ = &(libCb.cipCb.cipOutList);
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            ent = (KwAcLibOutEnt *)cmLListNode(lstEnt);
            if ( ent->mBuf != NULLP )
            {
               PJ_FREE_BUF(ent->mBuf);
            }
            PJ_FREE(ent, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);
  
      datQ = &(libCb.intCb.intOutList);
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            ent = (KwAcLibOutEnt *)cmLListNode(lstEnt);
            if ( ent->mBuf != NULLP )
            {
               PJ_FREE_BUF(ent->mBuf);
            }
            PJ_FREE(ent, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);

      datQ = &(libCb.intCb.intList); 
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            secEnt = (KwAcLibSecEnt *)cmLListNode(lstEnt);
            PJ_FREE(secEnt, sizeof(KwAcLibSecEnt));
         }
      }
      cmLListInit(datQ);
    
      datQ = &(libCb.cipCb.cipList);   
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            secEnt = (KwAcLibSecEnt *)cmLListNode(lstEnt);
            PJ_FREE(secEnt, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);
   }
#endif

   /*************************************************************************
    *                      CKW FREE
    ************************************************************************/
   /* Configuration Request is nothing to free, because it regular memory
    * used to store */

   /* Configuration Confirmation is freed once we got the confirmation */

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlShutdown */


/**
 * @brief Skip Validation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : kwAcHdlChkVar  
 *     
 *     This handler will verify the state of variable for the given rlcId
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 **/
#ifdef ANSI
PUBLIC S16 kwAcHdlChkVar
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlChkVar(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
/*Pradeep - TODO, need to update this for accessing of rbCb from UL data structure.
            commenting the code for compilation*/
#if 0
   CmLteRlcId     rlcId;
   KwRbCb         *rbCb;
   U8             dir = KW_DIR_UL;
   U16            vrMs = 0;

   TRC2(kwAcHdlChkVar);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlChkVar(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlChkVar(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&rlcId, sizeof(CmLteRlcId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(rlcId.cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId",  &(rlcId.rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType",  &(rlcId.rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dir",  &(dir));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "vrMs",  &(vrMs));

   if (kwDbmFetchRbCbForUi(rlcId, &rbCb) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlChkVar(): rbCb not Found\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   if (dir == KW_DIR_UL)
   {
      if (rbCb->m.am.amUl.vrMs != vrMs)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : vrMs MisMatch: exp (%d) rcvd (%d) \n",
                     vrMs, rbCb->m.am.amUl.vrMs), 2);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
   }
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlChkVar */

/**********************************************************************
 
         End of file:     kwac_rguhdl.c@@/main/TeNB_Main_BR/tenb_br_tdd_e1.2_4.0.0_cr/1 - Thu Nov 20 22:41:28 2014
 
**********************************************************************/
 

/**********************************************************************
 
        Notes:
 
**********************************************************************/
 

/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm     1. Initial Release.
/main/2      ---     gk     1. LTE RLC Release 2.1.
/main/3   kw005.201  ap     1. Removed compilation warning.
                            2. Added support for L2 Measurement.
*********************************************************************91*/
