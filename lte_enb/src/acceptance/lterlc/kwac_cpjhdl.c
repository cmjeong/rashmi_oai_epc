

/********************************************************************20**
  
        Name:    CPJ user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Handle Primitive code
                  for CPJ Interface
 
        File:    kwac_cpjhdl.c

        Sid:      kwac_cpjhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:24 2014
  
        Prg:     chakrapani
  
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
#include "ckw.h"           /* CKW defines */
#include "lkw.h"           /* LKW defines */
#include "cpj.h"           /* CPJ defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_cpj.h"      /* CPJ Acceptance defines */

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
#include "ckw.x"           /* CKW */
#include "lkw.x"           /* LKW */
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_cpj.x"      /* CPJ Acceptance defines */


#ifdef KW_PDCP
/**
 * @brief Constructs PjUiCpjBndReq
 *
 * @details
 * This XML tag is handles construction of Bind Request and invokes
 * PjUiCpjBndReq
 * @code
 * XML Tag              - <tapa.cpj.bndreq>
 * Mapping Primitive    - PjUiCpjBndReq
 * Mapping Handler Fn   - kwAcHdlCpjBndReq
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
PUBLIC S16 kwAcHdlCpjBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlCpjBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   
   TRC2(kwAcHdlCpjBndReq);
   
   suId = 0;
   spId = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjBndReq(), tcId (%d)\n", tcCb->tcId)); 
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   NhLiCpjBndReq(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- kwAcHdlCpjBndReq --*/


/**
 * @brief Validates PjUiCpjBndCfm
 *
 * @details
 * This XML tag is handles Validation of PjUiCpjBndCfm
 * @code
 * XML Tag              - <tapa.cpj.bndcfm>
 * Mapping Primitive    - PjUiCpjBndCfm
 * Mapping Handler Fn   - kwAcHdlCpjBndCfm
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
PUBLIC S16 kwAcHdlCpjBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 kwAcHdlCpjBndCfm(tcCb, spCb)
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
 
   TRC2(kwAcHdlCpjBndCfm);
 
   ret = ROK;
   suId = 0;
   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
 CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)elm->data;

   /* Expected post structure */
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   
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
 
}/*-- kwAcHdlCpjBndCfm --*/


/**
 * @brief Constructs PjUiCpjUbndReq
 *
 * @details
 * This XML tag is handles construction of Unbind Request and invokes
 * PjUiCpjUbndReq
 * @code
 * XML Tag              - <tapa.cpj.ubndreq>
 * Mapping Primitive    - PjUiCpjUbndReq
 * Mapping Handler Fn   - kwAcHdlCpjUbndReq
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
PUBLIC S16 kwAcHdlCpjUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;

   TRC2(kwAcHdlCpjUbndReq);
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjUbndReq(), tcId (%d)\n", tcCb->tcId));
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
} /*-- kwAcHdlCpjUbndReq --*/


/**
 * @brief Constructs PjUiCpjCfgReq
 *
 * @details
 * This XML tag is handles construction of Configuration Request and invokes
 * PjUiCpjCfgReq
 * @code
 * XML Tag              - <tapa.cpj.cfgreq>
 * Mapping Primitive    - PjUiCpjCfgReq
 * Mapping Handler Fn   - kwAcHdlCpjCfgReq
 * Mapping Util Fn      - kwAcUtlCpjCfgReq
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
PUBLIC S16 kwAcHdlCpjCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjCfgReqInfo     *cfgReq;
 
   TRC2(kwAcHdlCpjCfgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
    CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCfgReq(), tcId (%d)\n", tcCb->tcId)); 
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   cfgReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJCFGREQ;
   
   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(cfgReq, sizeof(CpjCfgReqInfo));
   if (cfgReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCfgReq(): KW_ALLOC cfgReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlCpjBuildCfgReq(tcCb, spCb, cfgReq);
   if (ret != CMXTA_ERR_NONE)
   {
      PJ_FREE(cfgReq, sizeof(CpjCfgReqInfo));
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCfgReq(): kwAcUtlCpjBuildCfgReq Failed\n"));
      RETVALUE(ret);
   }

   kwAcCb.tcCb = tcCb;
   kwAcCb.spCb = spCb;

   NhLiCpjCfgReq(&pst, kwAcCb.nhCpjCb.spId, cfgReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCpjCfgReq */


/**
 * @brief validates PjUiCpjCfgCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjCfgCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.cfgcfm>
 * Mapping Primitive    - PjUiCpjCfgCfm
 * Mapping Handler Fn   - kwAcHdlCpjCfgCfm
 * Mapping Util Fn      - kwAcUtlCpjCfgCfm
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
PUBLIC S16 kwAcHdlCpjCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(kwAcHdlCpjCfgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
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
   if (kwAcUtlCpjValdtCfgCfm(tcCb, spCb, kwElm->u.cpjInfo.u.cfgCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCfgCfm(): kwAcUtlCpjValdtCfgCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCpjCfgCfm */


/**
 * @brief Constructs PjUiCpjReEstReq
 *
 * @details
 * This XML tag is handles construction of Re-establishment Request and invokes
 * PjUiCpjReEstReq
 * @code
 * XML Tag              - <tapa.cpj.reestreq>
 * Mapping Primitive    - PjUiCpjReEstReq
 * Mapping Handler Fn   - kwAcHdlCpjReEstReq
 * Mapping Util Fn      - kwAcUtlCpjReEstReq
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
PUBLIC S16 kwAcHdlCpjReEstReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjReEstReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjReEstReqInfo   *reEstReq;
 
   TRC2(kwAcHdlCpjReEstReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjReEstReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjReEstReq(), tcId (%d)\n", tcCb->tcId)); 
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   reEstReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJREESTREQ;
   
   /* Allocate memory for reEstReq */
   KW_ALLOC_ACC(reEstReq, sizeof(CpjReEstReqInfo));
   if (reEstReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjReEstReq(): KW_ALLOC reEstReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlCpjBuildReEstReq(tcCb, spCb, reEstReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjReEstReq(): kwAcUtlCpjBuildReEstReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjReEstReq(&pst, kwAcCb.nhCpjCb.spId, reEstReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCpjReEstReq */


/**
 * @brief Validates PjUiCpjReEstCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjReEstCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.reestcfm>
 * Mapping Primitive    - PjUiCpjReEstCfm
 * Mapping Handler Fn   - kwAcHdlCpjReEstCfm
 * Mapping Util Fn      - kwAcUtlCpjReEstCfm
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
PUBLIC S16 kwAcHdlCpjReEstCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjReEstCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(kwAcHdlCpjReEstCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjReEstCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjReEstCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjReEstCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
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
   if (kwAcUtlValdtReEstCfm(tcCb, spCb, kwElm->u.cpjInfo.u.reEstCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjReEstCfm(): kwAcUtlValdtReEstCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCpjReEstCfm */


/**
 * @brief Constructs PjUiCpjSecCfgReq
 *
 * @details
 * This XML tag is handles construction of Security Configuraiton Request and
 * invokes PjUiCpjSecCfgReq
 * @code
 * XML Tag              - <tapa.cpj.seccfgreq>
 * Mapping Primitive    - PjUiCpjSecCfgReq
 * Mapping Handler Fn   - kwAcHdlCpjSecCfgReq
 * Mapping Util Fn      - kwAcUtlCpjSecCfgReq
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
PUBLIC S16 kwAcHdlCpjSecCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjSecCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjSecCfgReqInfo  *secCfg;
 
   TRC2(kwAcHdlCpjSecCfgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSecCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSecCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
   secCfg = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJSECCFGREQ;
   
   /* Allocate memory for secCfg */
   KW_ALLOC_ACC(secCfg, sizeof(CpjSecCfgReqInfo));
   if (secCfg == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSecCfgReq(): KW_ALLOC secCfg Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlCpjBuildSecCfgReq(tcCb, spCb, secCfg);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSecCfgReq(): kwAcUtlCpjBuildCfgReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjSecCfgReq(&pst, kwAcCb.nhCpjCb.spId, secCfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCpjSecCfgReq */


/**
 * @brief Validates PjUiCpjSecCfgCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjSecCfgCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.seccfgcfm>
 * Mapping Primitive    - PjUiCpjSecCfgCfm
 * Mapping Handler Fn   - kwAcHdlCpjSecCfgCfm
 * Mapping Util Fn      - kwAcUtlCpjSecCfgCfm
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
PUBLIC S16 kwAcHdlCpjSecCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjSecCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(kwAcHdlCpjSecCfgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSecCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSecCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSecCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
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
   if (kwAcUtlValdtSecCfgCfm(tcCb, spCb, kwElm->u.cpjInfo.u.secCfgCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSecCfgCfm(): kwAcUtlValdtSecCfgCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCpjSecCfgCfm */

  
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
 * Mapping Handler Fn   - kwAcHdlCpjUeIdChgReq
 * Mapping Util Fn      - kwAcUtlCpjUeIdChgReq
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
PUBLIC S16 kwAcHdlCpjUeIdChgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjUeIdChgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjUeInfo         *ueInfo, *newUeInfo;
   U32               transId;
 
   TRC2(kwAcHdlCpjUeIdChgReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjUeIdChgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjUeIdChgReq(), tcId (%d)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
   ueInfo = NULLP;
   newUeInfo = NULLP;
   transId = 0;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJUEIDCHGREQ;
   
   /* Allocate memory for CpjUeInfo */
   KW_ALLOC_ACC(ueInfo, sizeof(CpjUeInfo));
   if (ueInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjUeIdChgReq(): KW_ALLOC ueInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   KW_ALLOC_ACC(newUeInfo, sizeof(CpjUeInfo));
   if (newUeInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjUeIdChgReq(): KW_ALLOC newUeInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));

   ret = kwAcUtlCpjBuildUeIdChgReq(tcCb, spCb, ueInfo, newUeInfo);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjUeIdChgReq(): kwAcHdlCpjUeIdChgReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjUeIdChgReq(&pst, kwAcCb.nhCpjCb.spId, transId, ueInfo, newUeInfo);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCpjUeIdChgReq */

  
/**
 * @brief Validates PjUiCpjUeIdChgCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjUeIdChgCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.ueidchgcfm>
 * Mapping Primitive    - PjUiCpjUeIdChgCfm
 * Mapping Handler Fn   - kwAcHdlCpjUeIdChgCfm
 * Mapping Util Fn      - kwAcUtlCpjUeIdChgCfm
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
PUBLIC S16 kwAcHdlCpjUeIdChgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjUeIdChgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
   U16            status;
 
   TRC2(kwAcHdlCpjUeIdChgCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
   status   = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjUeIdChgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjUeIdChgCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjUeIdChgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
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
 
}/* kwAcHdlCpjUeIdChgCfm */


/**
 * @brief Constructs PjUiCpjCountReq
 *
 * @details
 * This XML tag is handles construction of Count Report Request and
 * invokes PjUiCpjCountReq
 * @code
 * XML Tag              - <tapa.cpj.countreq>
 * Mapping Primitive    - PjUiCpjCountReq
 * Mapping Handler Fn   - kwAcHdlCpjCountReq
 * Mapping Util Fn      - kwAcUtlCpjCountReq
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
PUBLIC S16 kwAcHdlCpjCountReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjCountReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjCountReqInfo   *countReq;
 
   TRC2(kwAcHdlCpjCountReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCountReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCountReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   countReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJCOUNTREQ;
   
   /* Allocate memory for countReq */
   KW_ALLOC_ACC(countReq, sizeof(CpjCountReqInfo));
   if (countReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCountReq(): KW_ALLOC countReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlCpjBuildCountReq(tcCb, spCb, countReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCountReq(): kwAcUtlCpjBuildCountReq Failed\n"));
      RETVALUE(ret);
   }

   NhLiCpjCountReq(&pst, kwAcCb.nhCpjCb.spId, countReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCpjCountReq */


/**
 * @brief Validates PjUiCpjCountCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjCountCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.countcfm>
 * Mapping Primitive    - PjUiCpjCountCfm
 * Mapping Handler Fn   - kwAcHdlCpjCountCfm
 * Mapping Util Fn      - kwAcUtlCpjCountCfm
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
PUBLIC S16 kwAcHdlCpjCountCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjCountCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(kwAcHdlCpjCountCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCountCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjCountCfm(), tcId (%d)\n", tcCb->tcId));
#endif 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCountCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
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
   if (kwAcUtlValdtCountCfm(tcCb, spCb, kwElm->u.cpjInfo.u.countCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjCountCfm(): kwAcUtlValdtCountCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCpjCountCfm */


/**
 * @brief Constructs PjUiCpjSduStaReq
 *
 * @details
 * This XML tag is handles construction of SDU Status Report Request and
 * invokes PjUiCpjSduStaReq
 * @code
 * XML Tag              - <tapa.cpj.sdustareq>
 * Mapping Primitive    - PjUiCpjSduStaReq
 * Mapping Handler Fn   - kwAcHdlCpjSduStaReq
 * Mapping Util Fn      - kwAcUtlCpjSduStaReq
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
PUBLIC S16 kwAcHdlCpjSduStaReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjSduStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16               ret;
   Pst               pst;
   CpjSduStaReqInfo  *sduStaReq;
 
   TRC2(kwAcHdlCpjSduStaReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSduStaReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSduStaReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   sduStaReq = NULLP;

   /*-- Get the Pst information here from GCP to GCP User --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   pst.event = EVTCPJSDUSTAREQ;
   
   /* Allocate memory for sduStaReq */
   KW_ALLOC_ACC(sduStaReq, sizeof(CpjSduStaReqInfo));
   if (sduStaReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSduStaReq(): KW_ALLOC sduStaReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlCpjBuildSduStaReq(tcCb, spCb, sduStaReq);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSduStaReq(): kwAcUtlCpjBuildSduStaReq Failed\n"));
      RETVALUE(ret);
   }


   NhLiCpjSduStaReq(&pst, kwAcCb.nhCpjCb.spId, sduStaReq);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlCpjSduStaReq */


/**
 * @brief Validates PjUiCpjSduStaCfm
 *
 * @details
 * This XML tag is handles the validation of PjUiCpjSduStaCfm
 *
 * @code
 * XML Tag              - <tapa.cpj.sdustacfm>
 * Mapping Primitive    - PjUiCpjSduStaCfm
 * Mapping Handler Fn   - kwAcHdlCpjSduStaCfm
 * Mapping Util Fn      - kwAcUtlCpjSduStaCfm
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
PUBLIC S16 kwAcHdlCpjSduStaCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlCpjSduStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SuId           suId;
 
   TRC2(kwAcHdlCpjSduStaCfm);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId     = 0;
#ifndef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSduStaCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlCpjSduStaCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSduStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
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
   if (kwAcUtlValdtSduStaCfm(tcCb, spCb, kwElm->u.cpjInfo.u.sduStaCfm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlCpjSduStaCfm(): kwAcUtlValdtSduStaCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/* kwAcHdlCpjSduStaCfm */

#endif /* KW_PDCP */

/********************************************************************30**
         End of file:     kwac_cpjhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:24 2014
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
/main/1      ---     gk            1. Initial Release.
*********************************************************************91*/

