

/********************************************************************20**
  
        Name:    CPJ user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Handle Primitive code
                  for CPJ Interface
 
        File:    pjac_cpjhdl.c

        Sid:      pjac_cpjhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:44 2015
  
        Prg:     adarsh
  
*********************************************************************21*/

/**
 * @file
 * @brief CPJ Handler File
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
#ifdef KW
#include "ckw.h"           /* CKW defines */
#include "lkw.h"           /* LKW defines */
#include "rgu.h"           /* RGU defines */
#endif
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */
#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_cpj.h"      /* CPJ Acceptance defines */

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
#ifdef KW
#include "ckw.x"           /* CKW */
#include "lkw.x"           /* LKW */
#include "rgu.x"           /* RGU */
#endif
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"
#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_cpj.x"      /* CPJ Acceptance defines */

/* Venki */
#ifndef KW_PDCP
/**
 * @brief Constructs PjUiCpjBndReq
 *
 * @details
 * This XML tag is handles construction of Bind Request and invokes
 * PjUiCpjBndReq
 * @code
 * XML Tag              - <tapa.cpj.bndreq>
 * Mapping Primitive    - PjUiCpjBndReq
 * Mapping Handler Fn   - pjAcHdlCpjBndReq
 * Mapping Util Fn      - None
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 pjAcHdlCpjBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   Inst          pjInst;

   TRC2(pjAcHdlCpjBndReq);
   
   suId = 0;
   spId = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjBndReq(), tcId (%d)\n", tcCb->tcId)); 
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   
   pst.event = EVTCPJBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   NhLiCpjBndReq(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- pjAcHdlCpjBndReq --*/


/**
 * @brief Validates PjUiCpjBndCfm
 *
 * @details
 * This XML tag is handles Validation of PjUiCpjBndCfm
 * @code
 * XML Tag              - <tapa.cpj.bndcfm>
 * Mapping Primitive    - PjUiCpjBndCfm
 * Mapping Handler Fn   - pjAcHdlCpjBndCfm
 * Mapping Util Fn      - None
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 pjAcHdlCpjBndCfm(tcCb, spCb)
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
   Inst          pjInst;

   TRC2(pjAcHdlCpjBndCfm);
 
   ret = ROK;
   suId = 0;
   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
 CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)elm->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));
   /* Expected post structure */
   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJBNDCFM;
   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != kwElm->u.cpjInfo.u.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, kwElm->u.cpjInfo.u.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- pjAcHdlCpjBndCfm --*/


/**
 * @brief Constructs PjUiCpjUbndReq
 *
 * @details
 * This XML tag is handles construction of Unbind Request and invokes
 * PjUiCpjUbndReq
 * @code
 * XML Tag              - <tapa.cpj.ubndreq>
 * Mapping Primitive    - PjUiCpjUbndReq
 * Mapping Handler Fn   - pjAcHdlCpjUbndReq
 * Mapping Util Fn      - None
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;

   TRC2(pjAcHdlCpjUbndReq);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJUBNDREQ;
 
   spId = kwAcCb.nhCpjCb.spId;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   reason = 0; /*-- Reason is unused --*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "reason",  &(reason));
 
   /* Send the request to the GCP --*/
   NhLiCpjUbndReq(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- pjAcHdlCpjUbndReq --*/


/**
 * @brief Constructs PjUiCpjCfgReq
 *
 * @details
 * This XML tag is handles construction of Configuration Request and invokes
 * PjUiCpjCfgReq
 * @code
 * XML Tag              - <tapa.cpj.cfgreq>
 * Mapping Primitive    - PjUiCpjCfgReq
 * Mapping Handler Fn   - pjAcHdlCpjCfgReq
 * Mapping Util Fn      - pjAcUtlCpjCfgReq
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjCfgReqInfo     *cfgReq;
 
   TRC2(pjAcHdlCpjCfgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
    CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCfgReq(), tcId (%d)\n", tcCb->tcId)); 
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   cfgReq = NULLP;

   /* Venki */
   /*-- Get the Pst information here from GCP to GCP User --*/
   /* cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJCFGREQ;
   
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(cfgReq, sizeof(CpjCfgReqInfo));
   if (cfgReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCfgReq(): KW_ALLOC cfgReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildCfgReq(tcCb, spCb, cfgReq);
   if (ret != CMXTA_ERR_NONE)
   {
      PJ_FREE_ACC(cfgReq, sizeof(CpjCfgReqInfo));
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCfgReq(): pjAcUtlCpjBuildCfgReq Failed\n"));
      RETVALUE(ret);
   }

   kwAcCb.tcCb = tcCb;
   kwAcCb.spCb = spCb;

   NhLiCpjCfgReq(&pst, kwAcCb.nhCpjCb.spId, cfgReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjCfgReq */


/**
 * @brief validates PjUiCpjCfgCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjCfgCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.cfgcfm>
 * Mapping Primitive    - PjUiCpjCfgCfm
 * Mapping Handler Fn   - pjAcHdlCpjCfgCfm
 * Mapping Util Fn      - pjAcUtlCpjCfgCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   Inst           pjInst = 0;

   TRC2(pjAcHdlCpjCfgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;
   /* Venki - fixing here */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJCFGCFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (pjAcUtlCpjValdtCfgCfm(tcCb, spCb, kwElm->u.cpjInfo.u.cfgCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCfgCfm(): pjAcUtlCpjValdtCfgCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjCfgCfm */


/**
 * @brief Constructs PjUiCpjReEstReq
 *
 * @details
 * This XML tag is handles construction of Re-establishment Request and invokes
 * PjUiCpjReEstReq
 * @code
 * XML Tag              - <tapa.cpj.reestreq>
 * Mapping Primitive    - PjUiCpjReEstReq
 * Mapping Handler Fn   - pjAcHdlCpjReEstReq
 * Mapping Util Fn      - pjAcUtlCpjReEstReq
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjReEstReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjReEstReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjReEstReqInfo   *reEstReq;
 
   TRC2(pjAcHdlCpjReEstReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjReEstReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjReEstReq(), tcId (%d)\n", tcCb->tcId)); 
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   reEstReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
/*Pradeep - changed the PJ instance to 1*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJREESTREQ;
   
   /* Allocate memory for reEstReq */
   KW_ALLOC_ACC(reEstReq, sizeof(CpjReEstReqInfo));
   if (reEstReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjReEstReq(): KW_ALLOC reEstReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildReEstReq(tcCb, spCb, reEstReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjReEstReq(): pjAcUtlCpjBuildReEstReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjReEstReq(&pst, kwAcCb.nhCpjCb.spId, reEstReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjReEstReq */


/**
 * @brief Validates PjUiCpjReEstCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjReEstCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.reestcfm>
 * Mapping Primitive    - PjUiCpjReEstCfm
 * Mapping Handler Fn   - pjAcHdlCpjReEstCfm
 * Mapping Util Fn      - pjAcUtlCpjReEstCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjReEstCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjReEstCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(pjAcHdlCpjReEstCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjReEstCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjReEstCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjReEstCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

/*Pradeep - changed the PJ instance to 1*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJREESTCFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (pjAcUtlValdtReEstCfm(tcCb, spCb, kwElm->u.cpjInfo.u.reEstCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjReEstCfm(): pjAcUtlValdtReEstCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjReEstCfm */


/**
 * @brief Constructs PjUiCpjSecCfgReq
 *
 * @details
 * This XML tag is handles construction of Security Configuraiton Request and
 * invokes PjUiCpjSecCfgReq
 * @code
 * XML Tag              - <tapa.cpj.seccfgreq>
 * Mapping Primitive    - PjUiCpjSecCfgReq
 * Mapping Handler Fn   - pjAcHdlCpjSecCfgReq
 * Mapping Util Fn      - pjAcUtlCpjSecCfgReq
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjSecCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjSecCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjSecCfgReqInfo  *secCfg;
 
   TRC2(pjAcHdlCpjSecCfgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSecCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSecCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
   secCfg = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   /*cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJSECCFGREQ;
   
   /* Allocate memory for secCfg */
   KW_ALLOC_ACC(secCfg, sizeof(CpjSecCfgReqInfo));
   if (secCfg == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSecCfgReq(): KW_ALLOC secCfg Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildSecCfgReq(tcCb, spCb, secCfg);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSecCfgReq(): pjAcUtlCpjBuildCfgReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjSecCfgReq(&pst, kwAcCb.nhCpjCb.spId, secCfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjSecCfgReq */


/**
 * @brief Validates PjUiCpjSecCfgCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjSecCfgCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.seccfgcfm>
 * Mapping Primitive    - PjUiCpjSecCfgCfm
 * Mapping Handler Fn   - pjAcHdlCpjSecCfgCfm
 * Mapping Util Fn      - pjAcUtlCpjSecCfgCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjSecCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjSecCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   /* venki */
   Inst            pjInst;
 
   TRC2(pjAcHdlCpjSecCfgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSecCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSecCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSecCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;
   /* Venki */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(pjInst));

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJSECCFGCFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (pjAcUtlValdtSecCfgCfm(tcCb, spCb, kwElm->u.cpjInfo.u.secCfgCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSecCfgCfm(): kwAcUtlValdtSecCfgCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjSecCfgCfm */

  
/**
 * @brief Constructs PjUiCpjUeIdChgReq
 *
 * @details
 * This XML tag is handles construction of UeId Change Request and invokes
 * PjUiCpjUeIdChgReq
 *
 * @code
 * XML Tag              - <tapa.cpj.ueidchgreq>
 * Mapping Primitive    - PjUiCpjUeIdChgReq
 * Mapping Handler Fn   - pjAcHdlCpjUeIdChgReq
 * Mapping Util Fn      - pjAcUtlCpjUeIdChgReq
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjUeIdChgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjUeIdChgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjUeInfo         *ueInfo, *newUeInfo;
   U32               transId;
 
   TRC2(pjAcHdlCpjUeIdChgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjUeIdChgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjUeIdChgReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
   ueInfo = NULLP;
   newUeInfo = NULLP;
   transId = 0;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJUEIDCHGREQ;
   
   /* Allocate memory for CpjUeInfo */
   KW_ALLOC_ACC(ueInfo, sizeof(CpjUeInfo));
   if (ueInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjUeIdChgReq(): KW_ALLOC ueInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   KW_ALLOC_ACC(newUeInfo, sizeof(CpjUeInfo));
   if (newUeInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjUeIdChgReq(): KW_ALLOC newUeInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));

   ret = pjAcUtlCpjBuildUeIdChgReq(tcCb, spCb, ueInfo, newUeInfo);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjUeIdChgReq(): kwAcHdlCpjUeIdChgReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjUeIdChgReq(&pst, kwAcCb.nhCpjCb.spId, transId, ueInfo, newUeInfo);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjUeIdChgReq */

  
/**
 * @brief Validates PjUiCpjUeIdChgCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjUeIdChgCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.ueidchgcfm>
 * Mapping Primitive    - PjUiCpjUeIdChgCfm
 * Mapping Handler Fn   - pjAcHdlCpjUeIdChgCfm
 * Mapping Util Fn      - pjAcUtlCpjUeIdChgCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjUeIdChgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjUeIdChgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   U16            status;
 
   TRC2(pjAcHdlCpjUeIdChgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
   status   = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjUeIdChgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjUeIdChgCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjUeIdChgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJUEIDCHGCFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status",  &(status));
   /* Validate the Configuration confirmation */
   if (status != kwElm->u.cpjInfo.u.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, kwElm->u.cpjInfo.u.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjUeIdChgCfm */


/**
 * @brief Constructs PjUiCpjCountReq
 *
 * @details
 * This XML tag is handles construction of Count Report Request and
 * invokes PjUiCpjCountReq
 * @code
 * XML Tag              - <tapa.cpj.countreq>
 * Mapping Primitive    - PjUiCpjCountReq
 * Mapping Handler Fn   - pjAcHdlCpjCountReq
 * Mapping Util Fn      - pjAcUtlCpjCountReq
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjCountReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjCountReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjCountReqInfo   *countReq;
   /* venki */
   Inst pjInst;
 
   TRC2(pjAcHdlCpjCountReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCountReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCountReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   countReq = NULLP;
   /* venki */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));
   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   
   pst.event = EVTCPJCOUNTREQ;
   
   /* Allocate memory for countReq */
   KW_ALLOC_ACC(countReq, sizeof(CpjCountReqInfo));
   if (countReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCountReq(): KW_ALLOC countReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildCountReq(tcCb, spCb, countReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCountReq(): kwAcUtlCpjBuildCountReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjCountReq(&pst, kwAcCb.nhCpjCb.spId, countReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjCountReq */


/**
 * @brief Validates PjUiCpjCountCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjCountCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.countcfm>
 * Mapping Primitive    - PjUiCpjCountCfm
 * Mapping Handler Fn   - pjAcHdlCpjCountCfm
 * Mapping Util Fn      - pjAcUtlCpjCountCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjCountCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjCountCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   /* venki */
   Inst pjInst;

   TRC2(pjAcHdlCpjCountCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCountCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjCountCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCountCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;
   /* Venki */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJCOUNTCFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (pjAcUtlValdtCountCfm(tcCb, spCb, kwElm->u.cpjInfo.u.countCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjCountCfm(): kwAcUtlValdtCountCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjCountCfm */


/**
 * @brief Constructs PjUiCpjSduStaReq
 *
 * @details
 * This XML tag is handles construction of SDU Status Report Request and
 * invokes PjUiCpjSduStaReq
 * @code
 * XML Tag              - <tapa.cpj.sdustareq>
 * Mapping Primitive    - PjUiCpjSduStaReq
 * Mapping Handler Fn   - pjAcHdlCpjSduStaReq
 * Mapping Util Fn      - pjAcUtlCpjSduStaReq
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjSduStaReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjSduStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjSduStaReqInfo  *sduStaReq;
 
   TRC2(pjAcHdlCpjSduStaReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSduStaReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSduStaReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   sduStaReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJSDUSTAREQ;
   
   /* Allocate memory for sduStaReq */
   KW_ALLOC_ACC(sduStaReq, sizeof(CpjSduStaReqInfo));
   if (sduStaReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSduStaReq(): KW_ALLOC sduStaReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildSduStaReq(tcCb, spCb, sduStaReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSduStaReq(): kwAcUtlCpjBuildSduStaReq Failed\n"));
      RETVALUE(ret);
   }


   NhLiCpjSduStaReq(&pst, kwAcCb.nhCpjCb.spId, sduStaReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjSduStaReq */


/**
 * @brief Validates PjUiCpjSduStaCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjSduStaCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.sdustacfm>
 * Mapping Primitive    - PjUiCpjSduStaCfm
 * Mapping Handler Fn   - pjAcHdlCpjSduStaCfm
 * Mapping Util Fn      - pjAcUtlCpjSduStaCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjSduStaCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjSduStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(pjAcHdlCpjSduStaCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSduStaCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjSduStaCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSduStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJSDUSTACFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (pjAcUtlValdtSduStaCfm(tcCb, spCb, kwElm->u.cpjInfo.u.sduStaCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjSduStaCfm(): kwAcUtlValdtSduStaCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjSduStaCfm */
/**
 * @brief Constructs PjUiCpjDatResumeReq
 *
 * @details
 * This XML tag is handles construction of Data Resume Request and
 * invokes PjDlUdxDatResumeReq
 * @code
 * XML Tag              - <tapa.cpj.datresumereq>
 * Mapping Primitive    - PjDlUdxDatResumeReq
 * Mapping Handler Fn   - pjAcHdlCpjDatResumeReq
 * Mapping Util Fn      - pjAcUtlCpjDatResumeReq
 * Attributes            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjDatResumeReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjDatResumeReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjDatResumeReqInfo  *datResumeReq;
 
   TRC2(pjAcHdlCpjDatResumeReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjDatResumeReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjDatResumeReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   datResumeReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJDATRESUMEREQ;
   
   /* Allocate memory for datResumeReq */
   KW_ALLOC_ACC(datResumeReq, sizeof(CpjDatResumeReqInfo));
   if (datResumeReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjDatResumeReq(): KW_ALLOC datResumeReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildDatResumeReq(tcCb, spCb, datResumeReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjDatResumeReq(): kwAcUtlCpjBuildDatResumeReq Failed\n"));
      RETVALUE(ret);
   }
   
   NhLiCpjDatResumeReq(&pst, kwAcCb.nhCpjCb.spId, datResumeReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjDatResumeReq */

/**
 * @brief Validates PjDlUdxDatResumeCfm
 *
 * @details
 * This XML tag is handles the validation of PjDlUdxDatResumeCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.datresumecfm>
 * Mapping Primitive    - PjDlUdxDatResumeCfm
 * Mapping Handler Fn   - pjAcHdlCpjDatResumeCfm
 * Mapping Util Fn      - pjAcUtlCpjDatResumeCfm
 * Attributs            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjDatResumeCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjDatResumeCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(pjAcHdlCpjSduStaCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjDatResumeCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjDatResumeCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjDatResumeCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = EVTCPJDATRESUMECFM;

   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (kwAcCb.nhCpjCb.suId != kwElm->u.cpjInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.cpjInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate the Configuration confirmation */
   if (pjAcUtlValdtDatResumeCfm(tcCb, spCb, kwElm->u.cpjInfo.u.datResCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjDatResumeCfm(): kwAcUtlValdtDatResumeCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* pjAcHdlCpjDatResumeCfm */


/**
 * @brief Constructs PjUiCpjDatForwardReq
 *
 * @details
 * This XML tag is handles construction of Data Forward Request and
 * invokes PjDlUdxDatForwardReq
 * @code
 * XML Tag              - <tapa.cpj.datforwardreq>
 * Mapping Primitive    - PjDlUdxDatForwardReq
 * Mapping Handler Fn   - pjAcHdlCpjDatForwardReq
 * Mapping Util Fn      - pjAcUtlCpjDatForwardReq
 * Attributes            - 
 * 
 * @endcode
 *
 * @param[in]  tcCb  -  Test Case Control Block
 * @param[in]  spCb  -  Stack Control Block
 *
 * @return CMXTA_ERR_NONE
 */
#ifdef ANSI
PUBLIC S16 pjAcHdlCpjDatForwardReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlCpjDatForwardReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjDataFwdReqInfo  *datForwardReq;
 
   TRC2(pjAcHdlCpjDatResumeReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjDatForwardReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlCpjDatForwardReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   datForwardReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   
   pst.event = EVTCPJSTARTDATAFWDREQ;
   
   /* Allocate memory for datResumeReq */
   KW_ALLOC_ACC(datForwardReq, sizeof(CpjDataFwdReqInfo));
   if (datForwardReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjDatForwardReq(): KW_ALLOC datForwardReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlCpjBuildDatForwardReq(tcCb, spCb, datForwardReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlCpjDatForwardReq(): kwAcUtlCpjBuildDatForwardReq Failed\n"));
      RETVALUE(ret);
   }
   
   NhLiCpjDatForwardReq(&pst, kwAcCb.nhCpjCb.spId, datForwardReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlCpjDatForwardReq */




#endif /* KW_PDCP */

/********************************************************************30**
         End of file:     pjac_cpjhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:44 2015
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
/main/1      ---       vb            1. LTE PDCP Initial Release 2.1
*********************************************************************91*/
