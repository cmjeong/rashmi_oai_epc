

/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_crghdl.c

     Sid:      rgac_crghdl.c@@/main/3 - Sat Jul 30 02:20:52 2011

     Prg:     nsadar 
*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_crg.h"
#include "rgac_acc.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_crg.x"        /* MAC error defines */


/**
 * @brief XTA Bind Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgBndReq
 *     
 *     Issues a bindrequest from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlCrgBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;    /* service user SAP identifier */
   SpId          spId = 0;    /* service provuder SAP identifier */
   Inst          instId = 0;
   
   TRC2(rgAcHdlCrgBndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
 
   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST,RGAC_CRG_PROVENT,instId, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);
   
   pst.event = RGAC_CRG_EVTBNDREQ;
   /* Send the request to the LTEMAC --*/
   RGAC_CRG_BNDREQ(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlCrgBndReq --*/


/**
 * @brief XTA Bind Confirm Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgBndCfm 
 *     
 *     Validates a Bind Confirm from MAC to Dummy RRC. 
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
PUBLIC S16 rgAcHdlCrgBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlCrgBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;  /* service user SAP identifier */
   U8            status = CM_BND_OK;
   Inst      instId = 0;
 
   TRC2(rgAcHdlCrgBndCfm);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst)); 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlCrgBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   
   cmXtaGetPst(&pst, RGAC_CRG_PROVENT, instId, RGAC_CRG_USERENT, RGAC_CRG_USERINST,RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);
   
   pst.event = RGAC_CRG_EVTBNDCFM;
   
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.crgInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.crgInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));
 
   if (status != rgMsg->u.crgInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, rgMsg->u.crgInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlCrgBndCfm --*/

/**
 * @brief XTA UnBind Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgUbndReq 
 *     
 *     Issues an Un-Bind request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/ 

#ifdef ANSI
PUBLIC S16 rgAcHdlCrgUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlCrgUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   Reason         reason = 0;
   Inst           instId = 0;
   
   TRC2(rgAcHdlCrgUbndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, instId, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);
   
   pst.event = RGAC_CRG_EVTUBNDREQ;
   /* Send the request to the MAC --*/
   RGAC_CRG_UBNDREQ(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlCrgUbndReq --*/
/**
 * @brief XTA  Cell Config Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgCellCfgReq 
 *     
 *     Issues Cell Configuration request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgCellCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgCellCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaTxnCb     *txnCb = NULLP;
   Pst            pst;
   SpId           spId = 0;  /* service provuder SAP identifier */
   U8             num_transIds = 0;
   CrgCfgTransId  transId;
   CrgCfgReqInfo  *cfg;
   Inst           instId = 0;
 
   TRC2(rgAcHdlCrgCellCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgCellCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgCellCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlCrgCellCfgReq(): SGetSBuf failed\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));
   
   pst.event = RGAC_CRG_EVTCFGREQ;


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, instId, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);
   
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML -- */
   rgAcUtlCrgBuildCellCfgReq(tcCb, spCb, cfg); 

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Cell Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_CELLCFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgCellCfgReq */
/**
 * @brief XTA  UE Config Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgUeCfgReq 
 *     
 *     Issues Cell Configuration request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgUeCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgUeCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   U8             num_transIds = 1;
   CrgCfgTransId  transId;
   Inst           instId = 0;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgUeCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgUeCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgUeCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }   
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));
   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, instId, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildUeCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending UE Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_UECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(ROK);
}/* rgAcHdlCrgUeCfgReq */

/**
 * @brief XTA  Logical Channel Config Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgLchCfgReq 
 *     
 *     Issues Logical Channel Configuration request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgLchCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgLchCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId = 0;
   CrgCfgTransId  transId;
   Inst           instId = 0;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgLchCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgLchCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgLchCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));

   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, instId, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildLchCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_LCCFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgLchCfgReq */
/**
 * @brief XTA  Cell Re Config Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgCellReCfgReq 
 *     
 *     Issues Cell Re Configuration request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgCellReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgCellReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   U8             num_transIds = 1;
   CrgCfgTransId  transId;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgCellReCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgCellReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgCellReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));
   
   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, RGAC_CRG_PROVINST, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildCellReCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Cell Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_CELLRECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgCellReCfgReq */
/**
 * @brief XTA  UE Re Config Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgUeReCfgReq 
 *     
 *     Issues Cell Re Configuration request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgUeReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgUeReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   U8             num_transIds = 1;
   CrgCfgTransId  transId;
   Inst           instId = RGAC_CRG_PROVINST;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgUeCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgUeReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgUeReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));
   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, instId, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildUeReCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending UE Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_UERECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(ROK);
}/* rgAcHdlCrgUeReCfgReq */
/**
 * @brief XTA  Logical Channel Re Config Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgLchReCfgReq 
 *     
 *     Issues Logical Channel Re Configuration request from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgLchReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgLchReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId = 0;
   CrgCfgTransId  transId;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgLchReCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgLchReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgLchReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));

   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, RGAC_CRG_PROVINST, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildLchReCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_LCRECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgLchReCfgReq */

/**
 * @brief XTA Delete Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgDelReq 
 *     
 *     Issues Delete request for Cell/UE/Logical Channel from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgDelReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgDelReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId=0;
   CrgCfgTransId  transId;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgDelReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgDelReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgDelReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));

   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, RGAC_CRG_PROVINST, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_DELETE;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildDelReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_DELREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgDelReq*/

/**
 * @brief XTA UE Reset Request Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgRstReq 
 *     
 *     Issues Reset request for UE from Dummy RRC to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCrgRstReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgRstReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CrgCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId=0;
   CrgCfgTransId  transId;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlCrgDelReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgDelReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgDelReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(CrgCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(CrgCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(CrgCfgTransId));

   pst.event = RGAC_CRG_EVTCFGREQ;

   cmXtaGetPst(&pst, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_PROVENT, RGAC_CRG_PROVINST, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_CRG_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_CRG_RESET;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlCrgBuildRstReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending UE reset request\n"));
 
 
   /* Send the request to the LM */
   RGAC_CRG_RSTREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgRstReq*/

/**
 * @brief XTA  Config Confirm Handler for CRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCrgCfgCfm
 *     
 *     Validates a Config Confirm from MAC to Dummy RRC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_FATAL
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_NONE
 **/

#ifdef ANSI
PUBLIC S16 rgAcHdlCrgCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCrgCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   U8             status=0;
   Pst            pst;
   Inst           instId = 0;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCrgCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if (cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlCrgCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_CRG_PROVENT, instId, RGAC_CRG_USERENT, RGAC_CRG_USERINST, RGAC_CRG_SRCPROC, RGAC_CRG_DSTPROC, RGAC_CRG_MATCHPROC);

   pst.event = RGAC_CRG_EVTCFGCFM;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlCrgCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));
 
   /*-- Validate return value and reason --*/
   if (rgMsg->u.crgInfo.status != status)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlCrgCfgCfm() : result mismatch\
               Exp(%d) Rcvd(%d)\n",status, rgMsg->u.crgInfo.status));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCrgCfgCfm*/


/********************************************************************30**

         End of file:     rgac_crghdl.c@@/main/3 - Sat Jul 30 02:20:52 2011

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
/main/1      ---     ns  1. Initial Release.
/main/2      ---     ns  1. LTE MAC 2.1 release
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---     rt    1. LTE MAC 4.1 release
*********************************************************************91*/
