

/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_rgrhdl.c

     Sid:      rgac_rgrhdl.c@@/main/3 - Sat Jul 30 02:21:01 2011

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
#include "rgac_rgr.h"
#include "rgac_acc.h"
#include "rg_env.h"
#include "rg_sch_inf.h"
#include "rg_sch.h"
#if 0
#include "rg_sch_err.h"
#endif
/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
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
#include "rgac_rgr.x"        /* MAC error defines */
#include "rgr.x"           /* layer management typedefs for MAC */
#include "rg_sch_inf.x"         /* typedefs for Scheduler */
#include "rg_sch.x"        /* typedefs for Scheduler */

#ifdef RGR_CQI_REPT
PRIVATE S16 rgAcHdlRgrVldtDlPwrCtInfo ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
RgrUeCqiInfo *cqiInfo
));
#endif
/* LTE_ADV_FLAG_REMOVED_START */
PRIVATE S16 rgAcHdlRgrVldtSfrPoolInfo ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
RgSchCellCb *cell
));
/* LTE_ADV_FLAG_REMOVED_END */
/**
 * @brief XTA Bind Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrBndReq
 *     
 *     Issues a bindrequest from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgrBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   Inst          instId = RGSCH_INST_START;
   
   TRC2(rgAcHdlRgrBndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST,RGAC_RGR_PROVENT,instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
   
   pst.event = RGAC_RGR_EVTBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   RGAC_RGR_BNDREQ(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRgrBndReq --*/


/**
 * @brief XTA Bind Confirm Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrBndCfm 
 *     
 *     Validates a Bind Confirm from MAC to RGR. 
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
PUBLIC S16 rgAcHdlRgrBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgrBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   Status        status = CM_BND_OK;
   Inst          instId = RGSCH_INST_START;
 
   TRC2(rgAcHdlRgrBndCfm);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, instId, RGAC_RGR_USERENT, RGAC_RGR_USERINST,RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
   
   pst.event = RGAC_RGR_EVTBNDCFM;
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rgrInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rgrInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != rgMsg->u.rgrInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, rgMsg->u.rgrInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRgrBndCfm --*/

/**
 * @brief XTA UnBind Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrUbndReq 
 *     
 *     Issues an Un-Bind request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/ 

#ifdef ANSI
PUBLIC S16 rgAcHdlRgrUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgrUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   Reason         reason = 0;
   
   TRC2(rgAcHdlRgrUbndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, RGSCH_INST_START, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST,RGAC_RGR_PROVENT,RGSCH_INST_START, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
   
   
   pst.event = RGAC_RGR_EVTUBNDREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   /* Send the request to the MAC --*/
   RGAC_RGR_UBNDREQ(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRgrUbndReq --*/

/**
 * @brief XTA  eNB Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrEnbCfgReq 
 *     
 *     Issues Cell Configuration request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrEnbCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgrEnbCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
   S16            ret = ROK;
   U8             instId = RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrEnbCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrEnbCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrEnbCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   
   pst.event = RGAC_RGR_EVTCFGREQ;

   //instId = 
   //spId = 
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   //transId = 

   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
#if 0
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);
#endif
   cfg->action = RGAC_RGR_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   if(ret != (rgAcUtlRgrBuildEnbCfgReq(tcCb, spCb, cfg)))
   {
      RETVALUE(ret);
   }

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending ENB Configuration request\n"));

   /* Send the request to the LM */
   RGAC_RGR_ENBCFGREQ(&pst, spId, rgr_transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrEnbCfgReq */
/**
 * @brief XTA  Cell Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrCellCfgReq 
 *     
 *     Issues Cell Configuration request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrCellCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrCellCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
   S16            ret = ROK;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrCellCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrCellCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrCellCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   
   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);
   
   cfg->action = RGAC_RGR_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = rgAcUtlRgrBuildCellCfgReq(tcCb, spCb, cfg);
   if (ret != ROK)
      RETVALUE(ret);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Cell Configuration request\n"));
 
   /* Send the request to the LM */
   RGAC_RGR_CELLCFGREQ(&pst, spId, rgr_transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrCellCfgReq */

/**
 * @brief XTA  UE Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrUeCfgReq 
 *     
 *     Issues Cell Configuration request from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrUeCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrUeCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   U8             num_transIds = 1;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;
   RgrUeCfg       ueCfg;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrUeCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUeCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUeCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }   
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));
   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildUeCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending UE Configuration request\n"));
 
   ueCfg = cfg->u.cfgInfo.u.ueCfg;
 
   /* Send the request to the LM */
   RGAC_RGR_UECFGREQ(&pst, spId, transId, cfg);
#if 0 
if(ueCfg.txMode.txModeEnum == RGR_UE_TM_3||ueCfg.txMode.txModeEnum == RGR_UE_TM_4)
{
   SuId              suId = 0;
   TfuDlCqiIndInfo   *dlCqiIndInfo;
   TfuDlCqiRpt       *newNode;
   U8                i=0;

   CMXTA_ZERO(&pst, sizeof(Pst));
   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID + 1, CMXTA_PROCID_MASTER, CMXTA_PROCID_MASTER, FALSE);
   rgAcUtlAllocEvnt ((Data**)&dlCqiIndInfo, sizeof(TfuDlCqiIndInfo));
   dlCqiIndInfo->cellId  = RG_ACC_CELL_ID;
  
   for(; i<20; i++)
   {
   /* allocate the new node */
   cmGetMem ((Ptr)&(dlCqiIndInfo->memCp), sizeof(TfuDlCqiRpt), (Ptr*)&newNode);
   newNode->rnti = ueCfg.crnti;
   newNode->isPucchInfo = TRUE;
   newNode->dlCqiInfo.pucchCqi.mode = TFU_PUCCH_CQI_MODE10;
   newNode->dlCqiInfo.pucchCqi.u.mode10Info.type = TFU_RPT_RI;
   newNode->dlCqiInfo.pucchCqi.u.mode10Info.u.ri = RG_ACC_DFLT_RI;
   newNode->lnk.node = (PTR)newNode;
   cmLListAdd2Tail (&(dlCqiIndInfo->dlCqiRptsLst), &(newNode->lnk));
   } 

   TfUiTfuDlCqiInd (&pst, suId, dlCqiIndInfo);  
}
#endif
   RETVALUE(ROK);
}/* rgAcHdlRgrUeCfgReq */

/**
 * @brief XTA  Logical Channel Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLchCfgReq 
 *     
 *     Issues Logical Channel Configuration request from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrLchCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrLchCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId = 0;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrLchCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLchCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLchCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildLchCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_LCCFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrLchCfgReq */
/**
 * @brief XTA  Logical Channel Group Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLcgCfgReq 
 *     
 *     Issues Logical Channel Group Configuration request from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrLcgCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrLcgCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId = 0;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrLcgCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLcgCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLcgCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_CONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildLcgCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_LCCFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrLcgCfgReq */


/**
 * @brief XTA  Cell Re Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrCellReCfgReq 
 *     
 *     Issues Cell Re Configuration request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrCellReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrCellReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
   S16            ret = ROK;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrCellReCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrCellReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrCellReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
 
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   
   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);
   
   cfg->action = RGAC_RGR_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = rgAcUtlRgrBuildCellReCfgReq(tcCb, spCb, cfg);
   if (ret != ROK)
      RETVALUE(ret);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Cell Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_CELLRECFGREQ(&pst, spId, rgr_transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrCellReCfgReq */

/**
 * @brief XTA  UE Re Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrUeReCfgReq 
 *     
 *     Issues Cell Re Configuration request from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrUeReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrUeReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   U8             num_transIds = 1;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrUeCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUeReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUeReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));
   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildUeReCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending UE Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_UERECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(ROK);
}/* rgAcHdlRgrUeReCfgReq */
/**
 * @brief XTA  Logical Channel Re Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLchReCfgReq 
 *     
 *     Issues Logical Channel Re Configuration request from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrLchReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrLchReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId = 0;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrLchReCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLchReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLchReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildLchReCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_LCRECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrLchReCfgReq */
/**
 * @brief XTA  Logical Channel Re Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLcgReCfgReq 
 *     
 *     Issues Logical Channel Re Configuration request from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrLcgReCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrLcgReCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId = 0;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrLcgReCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLcgReCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLcgReCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_RECONFIG;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildLcgReCfgReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_LCGRECFGREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrLcgReCfgReq */

/**
 * @brief XTA Delete Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrDelReq 
 *     
 *     Issues Delete request for Cell/UE/Logical Channel from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrDelReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrDelReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId=0;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrDelReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrDelReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrDelReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_DELETE;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildDelReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Logical Channel Re Configuration request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_DELREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrDelReq*/

/**
 * @brief XTA UE Reset Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrRstReq 
 *     
 *     Issues Reset request for UE from Dummy RRM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrRstReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrRstReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrCfgReqInfo  *cfg;
   Pst            pst;
   U8             num_transIds = 1;
   S16            spId=0;
   RgrCfgTransId  transId;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrDelReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrDelReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrDelReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(cfg, sizeof(RgrCfgReqInfo));
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&transId, sizeof(RgrCfgTransId));

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* Filling Default TransId */
   transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", transId.trans, &num_transIds);
   
   cfg->action = RGAC_RGR_RESET;
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   rgAcUtlRgrBuildRstReq(tcCb, spCb, cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending UE reset request\n"));
 
 
   /* Send the request to the LM */
   RGAC_RGR_RSTREQ(&pst, spId, transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrRstReq*/

/* Added for sending TTI tick to RRM */
#ifdef RGR_RRM_TICK
/**
 * @brief XTA  TTI indication Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrTtiInd
 *     
 *     Validates a TTI indication from MAC to RRRM.
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
PUBLIC S16 rgAcHdlRgrTtiInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgrTtiInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   Pst            pst;
   CmLteCellId    cellId=1;
   U8             instId=RGSCH_INST_START;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrTtiInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrTtiInd(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if (cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrTtiInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, instId, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
   pst.event = RGAC_RGR_EVTTTIIND;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlRgrTtiInd() : PST Mismatch for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrTtiInd*/
#endif /* RGR_RRM_TICK */


/**
 * @brief XTA  Config Confirm Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrCfgCfm
 *     
 *     Validates a Config Confirm from MAC to RGR.
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
PUBLIC S16 rgAcHdlRgrCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgrCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   U8             status = 0;
   U8             rgrStatus = 100;
   Pst            pst;
   U8             instId=RGSCH_INST_START;
   RgSchCb       *instCb;
   RgSchCellCb   *cell = NULLP;
   U8             valdtTrue = 0;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, instId, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   pst.event = RGAC_RGR_EVTCFGCFM;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlRgrCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "status",  &status);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrStatus",  &rgrStatus);
   if (rgrStatus != 100)
   {
      status = rgrStatus;
   }
   
   if (rgMsg->u.rgrInfo.status != status)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrCfgCfm() : result mismatch exp(%d) rcvd(%d)\n", status, rgMsg->u.rgrInfo.status));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /* LTE_ADV_FLAG_REMOVED_START */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &instId);
   instCb = &rgSchCb[instId -RGSCH_INST_START];
   cell = instCb->rgrSap[instId - RGSCH_INST_START].cell;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdtTrue",  &valdtTrue);
   if(valdtTrue == 1)
   {
       if(rgAcHdlRgrVldtSfrPoolInfo(tcCb,spCb,cell) != CMXTA_ERR_NONE)
       {
           CMXTA_DBG_CALLIND((_cmxtap, "Sfr Pool Info validation failed"), 2);
           cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
           RETVALUE(CMXTA_ERR_INT);
       }
   }
   /* LTE_ADV_FLAG_REMOVED_END */
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrCfgCfm*/

/* Added for SI Enhancement*/
#ifdef RGR_SI_SCH
/**
 * @brief XTA SI Config Confirm Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrSiCfgCfm
 *     
 *     Validates a SI Config Confirm from MAC to RGR.
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
PUBLIC S16 rgAcHdlRgrSiCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgrSiCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   U8             status = 0;
   U8             rgrStatus = 100;
   Pst            pst;
   U8             instId=RGSCH_INST_START;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if (cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrSiCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, instId, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   pst.event = RGAC_RGR_EVTSICFGCFM;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlRgrSiCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "status",  &status);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrStatus",  &rgrStatus);
   if (rgrStatus != 100)
   {
      status = rgrStatus;
   }
   
   if (rgMsg->u.rgrInfo.status != status)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrSiCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrSiCfgCfm*/


/**
 * @brief XTA  SI Config Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrSiCfgReq 
 *     
 *     Issues SI Configuration request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrSiCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrSiCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrSiCfgReqInfo  *cfg;
   Pst            pst;
   SpId           spId = 0;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
   S16            ret = ROK;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrSiCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   
   pst.event = RGAC_RGR_EVTSICFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = rgAcUtlRgrBuildSiCfgReq(tcCb, spCb, cfg);
   if (ret != ROK)
      RETVALUE(ret);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending SI Configuration request\n"));
 
   /* Send the request to the LM */
   RGAC_RGR_SICFGREQ(&pst, spId, rgr_transId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrSiCfgReq */


#ifdef ANSI
PUBLIC S16 rgAcHdlRgrWarningSiCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrWarningSiCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrWarningSiCfgReqInfo  *cfg;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
   Pst            pst;
   SpId           spId = 0;
   S16            ret = ROK;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;

   TRC2(rgAcHdlRgrWarningSiCfgReq);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrWarningSiCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   pst.event = RGAC_RGR_EVTWARNINGSICFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   ret = rgAcUtlRgrBuildWarningSiCfgReq(tcCb, spCb, cfg);
   if (ret != ROK)
      RETVALUE(ret);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Warning Sending SI Configuration request\n"));

   /* Send the request to the LM */
   RGAC_RGR_WARNINGSICFGREQ(&pst, spId, rgr_transId, cfg);

   RETVALUE(CMXTA_ERR_NONE);
}



/**
 * @brief XTA SI Config Confirm Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrWarningSiCfgCfm
 *     
 *     Validates a SI Config Confirm from MAC to RGR.
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
PUBLIC S16 rgAcHdlRgrWarningSiCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgrWarningSiCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   U8             status = 0;
   U8             rgrStatus = 100;
   Pst            pst;
   U8             instId=RGSCH_INST_START;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrSiCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if (cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrSiCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, instId, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   pst.event = RGAC_RGR_EVTSIWARNINGCFGCFM;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlRgrSiCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "status",  &status);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrStatus",  &rgrStatus);
   if (rgrStatus != 100)
   {
      status = rgrStatus;
   }
   
   if (rgMsg->u.rgrInfo.status != status)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrWarningSiCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrWarningSiCfgCfm*/


 /**
 * @brief XTA  Warning SI Stop Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrWarningSiStopReq 
 *     
 *     Issues SI Configuration request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrWarningSiStopReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrWarningSiStopReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   U8             instId=RGSCH_INST_START;
   U8             siId;

   CmXtaTxnCb     *txnCb = NULLP;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
 
   TRC2(rgAcHdlRgrWarningSiStopReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrWarningSiStopReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrWarningSiStopReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   
   pst.event = RGAC_RGR_EVTSIWARNINGSISTOPREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siId", &(siId));

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending SI Stop request\n"));
 
   /* Send the request to the LM */
   RGAC_RGR_WARNINGSISTOPREQ(&pst, spId, rgr_transId, siId);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrWarningSiStopReq */
 
#endif

#ifdef RGR_CQI_REPT

/**
 * @brief XTA Status Indication Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrStaInd  
 *     
 *     Validates Status Indication primitive recieved from MAC
 *     to Dummy-RGR against tester provided input and cached 
 *     information.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgrStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   CmLteCellId   cellId = RG_ACC_CELLID;
   CmLteRnti     ueId = 0;

   TRC2(rgAcHdlRgrStaInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrStaInd(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rgMsg = (RgAccMsgQElm *)msg->data;
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, RGSCH_INST_START, RGAC_RGR_USERENT, 
           RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   pst.event = RGAC_RGR_EVTSTAIND;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rgrInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rgrInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));

   if (cellId != rgMsg->u.rgrInfo.staInd.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rgrInfo.staInd.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));

   if (rgAccCb.acUeCb[ueId].crnti != rgMsg->u.rgrInfo.staInd.crnti)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, rgMsg->u.rgrInfo.staInd.crnti), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(rgAcHdlRgrVldtDlPwrCtInfo( tcCb, spCb,
            &(rgMsg->u.rgrInfo.staInd.ueCqiInfo))!= CMXTA_ERR_NONE)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "DL Power control validation failed"), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcHdlRgrStaInd */


/**
 * @brief XTA Validates DL Power control information. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrVldtDlPwrCtInfo  
 *     
 *     Validates DL Power control information recieved
 *     in StaInd frm MAC.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PRIVATE S16 rgAcHdlRgrVldtDlPwrCtInfo
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
RgrUeCqiInfo *cqiInfo
)
#else
PRIVATE S16 rgAcHdlRgrVldtDlPwrCtInfo(tcCb, spCb, cqiInfo)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
RgrUeCqiInfo *cqiInfo;
#endif
{

   CmLteRnti     ueId = 0;
#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
   RgAcDlPwrCntrlInfo  *rgAcDlpcInfo;
#endif
   S16             startIndx;
   U8            userCount;
   U8            numSubbnds;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));

   rgAcDlpcInfo = &(rgAccCb.acUeCb[ueId].dlpcInfo);
   userCount = rgAcDlpcInfo->cqiReptCount;
   
   /* This is a temp fix as subband CQI values are not being validated in any TC. */
   /* TODO: Remove this once validation of subband CQI is added */
   for(numSubbnds=0; numSubbnds<RGAC_DLPWR_CQIMAXN; numSubbnds++)
   {
      rgAcDlpcInfo->cqiRept[numSubbnds].numSubBand = 0;
      cmMemset((U8 *)&rgAcDlpcInfo->cqiRept[numSubbnds].sbCqiInfo, 0, (RGR_MAX_DL_CQI_SUBBAND * sizeof(RgrSubBandCqiInfo)));

   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numRept",  &(userCount));

   /* Check have we received wrong number of reports */
   if(userCount != cqiInfo->numCqiRept)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrVldtDlPwrCtInfo() Error : "
               "numCqiRpt missmatch for %d: exp (%d), but rceived(%d)\n",
               ueId, userCount, cqiInfo->numCqiRept));
      rgAcDlpcInfo->cqiReptCount  = 0;
      cmMemset((U8 *)&(rgAcDlpcInfo->cqiRept), 0,
            rgAcDlpcInfo->cqiSentCount*sizeof(RgrUeCqiRept));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   startIndx = rgAcDlpcInfo->cqiSentCount - userCount;
   if (startIndx  < 0)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrVldtDlPwrCtInfo() Error : "
               "Negative index\n"));
      rgAcDlpcInfo->cqiReptCount  = 0;
      cmMemset((U8 *)&(rgAcDlpcInfo->cqiRept), 0,
            rgAcDlpcInfo->cqiSentCount*sizeof(RgrUeCqiRept));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   /* Check have we received all report intact and in order */
   if(cmMemcmp((CONSTANT U8*)&(rgAcDlpcInfo->cqiRept[startIndx]),
            (CONSTANT U8*)&(cqiInfo->cqiRept),
            (PTR) (cqiInfo->numCqiRept*sizeof(RgrUeCqiRept))) != 0)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrVldtDlPwrCtInfo() Error :"
               "cqiRept missmatch for ueId %d\n", ueId));
      rgAcDlpcInfo->cqiReptCount  = 0;
      cmMemset((U8 *)&(rgAcDlpcInfo->cqiRept), 0,
            rgAcDlpcInfo->cqiSentCount*sizeof(RgrUeCqiRept));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   rgAcDlpcInfo->cqiSentCount = 0;

   RETVALUE(CMXTA_ERR_NONE);

}/*-- rgAcHdlRgrVldtDlPwrCtInfo --*/
#endif /* End of RGR_CQI_REPT */

/* VENKI */
/* LTE_ADV_FLAG_REMOVED_START */
/**
 * @brief XTA Validates SFR pool Info
 *
 * @details
 *
 *     Function : rgAcHdlRgrVldtSfrPoolInfo  
 *     
 *     Validates SFR Pool Info
 *     in StaInd frm MAC.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PRIVATE S16 rgAcHdlRgrVldtSfrPoolInfo
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
RgSchCellCb  *cell    
)
#else
PRIVATE S16 rgAcHdlRgrVldtSfrPoolInfo(tcCb, spCb, cell)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
RgSchCellCb  *cell;
#endif
{
    U8              i;
    RgSchDlSf       *sf;
	CmLListCp   *l;
    CmLList     *n;
    RgSchSFRPoolInfo *sfrCCPool;
    RgSchSFRPoolInfo *sfrCEPool;
    U8          valdtTrue = 0;
   
    /* CE Pool */
    U16         CEPoolStartRb = 0;
    U16         CEPoolEndRb = 0;
    U16         CEPoolBw = 0;
    U16         CEPoolBwAlloced = 0;
    U16         CEPoolType2Start = 0;
    U16         CEPoolType2End = 0;
    U16         CEPoolType0End = 0;
    
    /* CC Pool1 */
    U16         CCPool1StartRb = 0;
    U16         CCPool1EndRb = 0;
    U16         CCPool1Bw = 0;
    U16         CCPool1BwAlloced = 0;
    U16         CCPool1Type2Start = 0;
    U16         CCPool1Type2End = 0;
    U16         CCPool1Type0End = 0;
    
    /* CC Pool2 */
    U16         CCPool2StartRb = 0;
    U16         CCPool2EndRb = 0;
    U16         CCPool2Bw = 0;
    U16         CCPool2BwAlloced = 0;
    U16         CCPool2Type2Start = 0;
    U16         CCPool2Type2End = 0;
    U16         CCPool2Type0End = 0;
    
    /* Rcvd CC Pool1 */
    U16         rcvdCCPool1StartRb = 0;
    U16         rcvdCCPool1EndRb = 0;
    U16         rcvdCCPool1Bw = 0;
    U16         rcvdCCPool1BwAlloced = 0;
    U16         rcvdCCPool1Type2Start = 0;
    U16         rcvdCCPool1Type2End = 0;
    U16         rcvdCCPool1Type0End = 0;

    /* Rcvd CC Pool2 */
    U16         rcvdCCPool2StartRb = 0;
    U16         rcvdCCPool2EndRb = 0;
    U16         rcvdCCPool2Bw = 0;
    U16         rcvdCCPool2BwAlloced = 0;
    U16         rcvdCCPool2Type2Start = 0;
    U16         rcvdCCPool2Type2End = 0;
    U16         rcvdCCPool2Type0End = 0;
    
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdtTrue",  &valdtTrue);
    
    /* Getting CE Pool Info */
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolStartRb",      &CEPoolStartRb);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolEndRb",        &CEPoolEndRb);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolBw",           &CEPoolBw);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolBwAlloced",    &CEPoolBwAlloced);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolType2Start",   &CEPoolType2Start);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolType2End",     &CEPoolType2End);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CEPoolType0End",     &CEPoolType0End);

    /* Getting CC Pool1 Info */
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1StartRb",      &CCPool1StartRb);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1EndRb",        &CCPool1EndRb);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1Bw",           &CCPool1Bw);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1BwAlloced",    &CCPool1BwAlloced);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1Type2Start",   &CCPool1Type2Start);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1Type2End",     &CCPool1Type2End);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool1Type0End",     &CCPool1Type0End);
    
    /* Getting CC Pool2 Info */
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2StartRb",      &CCPool2StartRb);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2EndRb",        &CCPool2EndRb);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2Bw",           &CCPool2Bw);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2BwAlloced",    &CCPool2BwAlloced);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2Type2Start",   &CCPool2Type2Start);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2Type2End",     &CCPool2Type2End);
    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CCPool2Type0End",     &CCPool2Type0End);
    
    for(i = 0; i < RGSCH_NUM_DL_SUBFRAMES; i++)
    {
        sf = cell->subFrms[i];
		l = &sf->sfrTotalPoolInfo.cePool;
		n = cmLListFirst(l);
		sfrCEPool = (RgSchSFRPoolInfo*)n->node;
		
        if(i == 0)
        {
            printf("\n CE Pool Info:\n       \
                    sfrCEPool->poolstartRB = %d \n   \
                    sfrCEPool->poolendRB   = %d \n   \
                    sfrCEPool->bw          = %d \n   \
                    sfrCEPool->bwAlloced   = %d \n   \
                    sfrCEPool->type2Start  = %d \n   \
                    sfrCEPool->type2End    = %d \n   \
                    sfrCEPool->type0End    = %d \n",sfrCEPool->poolstartRB,sfrCEPool->poolendRB,sfrCEPool->bw,sfrCEPool->bwAlloced,sfrCEPool->type2Start,sfrCEPool->type2End,sfrCEPool->type0End);
        }

        l = &sf->sfrTotalPoolInfo.ccPool;
        n = cmLListFirst(l);
        sfrCCPool = (RgSchSFRPoolInfo*)n->node;

        if(i == 0)
        {
            printf("\n CC Pool 1 Info:\n       \
                    sfrCCPool->poolstartRB = %d \n   \
                    sfrCCPool->poolendRB   = %d \n   \
                    sfrCCPool->bw          = %d \n   \
                    sfrCCPool->bwAlloced   = %d \n   \
                    sfrCCPool->type2Start  = %d \n   \
                    sfrCCPool->type2End    = %d \n   \
                    sfrCCPool->type0End    = %d \n",sfrCCPool->poolstartRB,sfrCCPool->poolendRB,sfrCCPool->bw,sfrCCPool->bwAlloced,sfrCCPool->type2Start,sfrCCPool->type2End,sfrCCPool->type0End);
        }
        rcvdCCPool1StartRb    = sfrCCPool->poolstartRB;
        rcvdCCPool1EndRb      = sfrCCPool->poolendRB;
        rcvdCCPool1Bw         = sfrCCPool->bw;
        rcvdCCPool1BwAlloced  = sfrCCPool->bwAlloced;
        rcvdCCPool1Type2Start = sfrCCPool->type2Start;
        rcvdCCPool1Type2End   = sfrCCPool->type2End;
        rcvdCCPool1Type0End   = sfrCCPool->type0End;

        n = n->next;
        if(n != NULLP)
        {
            sfrCCPool = (RgSchSFRPoolInfo*)n->node;
			if(i == 0)
			{
				printf("\n CC Pool 2 Info:\n       \
						sfrCCPool->poolstartRB = %d \n   \
						sfrCCPool->poolendRB   = %d \n   \
						sfrCCPool->bw          = %d \n   \
						sfrCCPool->bwAlloced   = %d \n   \
						sfrCCPool->type2Start  = %d \n   \
						sfrCCPool->type2End    = %d \n   \
					sfrCCPool->type0End    = %d \n",sfrCCPool->poolstartRB,sfrCCPool->poolendRB,sfrCCPool->bw,sfrCCPool->bwAlloced,sfrCCPool->type2Start,sfrCCPool->type2End,sfrCCPool->type0End);
				
				rcvdCCPool2StartRb    = sfrCCPool->poolstartRB;
				rcvdCCPool2EndRb      = sfrCCPool->poolendRB;
				rcvdCCPool2Bw         = sfrCCPool->bw;
				rcvdCCPool2BwAlloced  = sfrCCPool->bwAlloced;
				rcvdCCPool2Type2Start = sfrCCPool->type2Start;
				rcvdCCPool2Type2End   = sfrCCPool->type2End;
				rcvdCCPool2Type0End   = sfrCCPool->type0End;

			}

        }
        else
        {
				rcvdCCPool2StartRb    = 0;
				rcvdCCPool2EndRb      = 0;
				rcvdCCPool2Bw         = 0;
				rcvdCCPool2BwAlloced  = 0;
				rcvdCCPool2Type2Start = 0;
				rcvdCCPool2Type2End   = 0;
				rcvdCCPool2Type0End   = 0;
        }
    }

    cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdtTrue",  &valdtTrue);
    if(valdtTrue == 1)
    {
        if( (CEPoolStartRb != sfrCEPool->poolstartRB)     ||
                (CEPoolEndRb   != sfrCEPool->poolendRB)       ||
                (CEPoolBw      != sfrCEPool->bw)              ||
                (CEPoolBwAlloced   != sfrCEPool->bwAlloced)   ||
                (CEPoolType2Start   != sfrCEPool->type2Start) ||
                (CEPoolType2End   != sfrCEPool->type2End)     ||
                (CEPoolType0End   != sfrCEPool->type0End)     ||

                (CCPool1StartRb != rcvdCCPool1StartRb)     || 
                (CCPool1EndRb != rcvdCCPool1EndRb)       ||
                (CCPool1Bw != rcvdCCPool1Bw)              ||
                (CCPool1BwAlloced != rcvdCCPool1BwAlloced)   ||
                (CCPool1Type2Start != rcvdCCPool1Type2Start) ||
                (CCPool1Type2End != rcvdCCPool1Type2End)     ||
                (CCPool1Type0End != rcvdCCPool1Type0End)     ||

                (CCPool2StartRb != rcvdCCPool2StartRb)     || 
                (CCPool2EndRb   != rcvdCCPool2EndRb)       ||
                (CCPool2Bw      != rcvdCCPool2Bw)              ||
                (CCPool2BwAlloced   != rcvdCCPool2BwAlloced)   ||
                (CCPool2Type2Start   != rcvdCCPool2Type2Start) ||
                (CCPool2Type2End   != rcvdCCPool2Type2End)     ||
                (CCPool2Type0End   != rcvdCCPool2Type0End))
                {
                    CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRgrVldtSfrPoolInfo : no match in sfr pool info"));
                    RETVALUE(CMXTA_ERR_NOMATCH);   
                }

    }
    RETVALUE(CMXTA_ERR_NONE);
}/*-- rgAcHdlRgrVldtSfrPoolInfo --*/
/* LTE_ADV_FLAG_REMOVED_END */

/**
 * @brief XTA UE Status Indication Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrUeStaInd  
 *     
 *     Validates UE Status Indication primitive recieved from MAC
 *     to Dummy-RGR against tester provided input and cached 
 *     information.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrUeStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgrUeStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;

   TRC2(rgAcHdlRgrUeStaInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUeStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrUeStaInd(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrUeStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rgMsg = (RgAccMsgQElm *)msg->data;
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, RGSCH_INST_START, RGAC_RGR_USERENT, 
           RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   pst.event = RGAC_RGR_EVTRGRUESTAIND;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcHdlRgrStaInd */


/* LTE_ADV_FLAG_REMOVED_START */
/**
 * @brief XTA  LoadInfo Request Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLoadInfReq 
 *     
 *     Issues Load Info request from RGR to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrLoadInfReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlRgrLoadInfReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgrLoadInfReqInfo  *loadInf;
   Pst            pst;
   SpId           spId = 0;
   RgrCfgTransId  rgr_transId;
   U8             num_transIds;
   S16            ret = ROK;
   U8             instId=RGSCH_INST_START;

   CmXtaTxnCb     *txnCb = NULLP;
 
   TRC2(rgAcHdlRgrLoadInfReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLoadInfReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLoadInfReq(): tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&loadInf, sizeof(RgrLoadInfReqInfo));
   if (loadInf == NULLP)
   {
      RETVALUE(RFAILED);
   }
   
   pst.event = RGAC_RGR_EVTLOADINFREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"transId", &(rgr_transId.trans), &num_transIds);
   
   /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   ret = rgAcUtlRgrBuildLoadInfReq(tcCb, spCb, loadInf);
   if (ret != ROK)
      RETVALUE(ret);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Load Info request\n"));
 
   /* Send the request to the LM */
   RGAC_RGR_LOADINFREQ(&pst, spId, rgr_transId, loadInf);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlRgrLoadInfReq */


/**
 * @brief XTA LoadInfo Indication Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLoadInfInd  
 *     
 *     Validates LoadInfo Indication primitive recieved from MAC
 *     to Dummy-RGR against tester provided input and cached 
 *     information.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef LTE_ADV
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrSCellActDeactReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgrSCellActDeactReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   RgrCfgReqInfo  *cfg;
   SpId           spId = 0;
   Pst           pst;
   RgrCfgTransId  rgr_transId;
   RgrSCellActDeactEvnt  *sCellActDeactEvnt;
   U8             numSCells = 1;
   U8             instId=RGSCH_INST_START;
   CmLteRnti     ueId = 0;
   CmXtaTxnCb     *txnCb = NULLP;
   U16           crnti;
   U8            sCellIdx[RGR_MAX_SCELL_PER_UE];
   U8            num;
   U8          sCellActionType = 1;



   TRC2(rgAcHdlRgrSCellActDeactReq);

   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgr_transId, sizeof(RgrCfgTransId));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgrCfgReqInfo));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   pst.event = RGAC_RGR_EVTCFGREQ;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGR_USERENT, RGAC_RGR_USERINST, RGAC_RGR_PROVENT, instId, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);
   /* Fetch UeId from command */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   rgr_transId.trans[0] = RGAC_RGR_DEFAULT_TRANSID;

   /*sprint4_ca*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sCellActionType",  &(sCellActionType));
   if (1 == sCellActionType)
   {
      cfg->action = RGAC_RGR_SCELL_READY;
   }
   else if (2 == sCellActionType)
   {
      cfg->action = RGAC_RGR_SCELL_ACT;
   }
   else
   {
      cfg->action = RGAC_RGR_SCELL_DEACT;
   }
   /*sprint4_ca*/

   /* Fill the activation params */
   sCellActDeactEvnt = &(cfg->u.sCellActDeactEvnt);

   crnti = rgAccCb.acUeCb[ueId].crnti;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",  &(crnti));
   sCellActDeactEvnt->crnti = crnti;
  
   numSCells = 1;
   sCellIdx[0] = 1; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSCells",  &(numSCells));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"sCellIdx", &(sCellIdx), &num);

   sCellActDeactEvnt->numOfSCells = numSCells;

   for(U8 idx = 0 ; idx < numSCells; idx++)
   {
      sCellActDeactEvnt->sCellActDeactInfo[idx].sCellIdx = sCellIdx[idx];/* need to rmv this hardcoding */
   }

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   /*-- Call MAC Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Cell Configuration request\n"));
 
   /* Send the request to the LM */
   RGAC_RGR_CELLCFGREQ(&pst, spId, rgr_transId, cfg);
   
   RETVALUE(CMXTA_ERR_NONE);
}
#endif
/**
 * @brief XTA LoadInfo Indication Handler for RGR interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgrLoadInfInd  
 *     
 *     Validates LoadInfo Indication primitive recieved from MAC
 *     to Dummy-RGR against tester provided input and cached 
 *     information.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgrLoadInfInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgrLoadInfInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   CmLteCellId   cellId = RG_ACC_CELLID;

   TRC2(rgAcHdlRgrLoadInfInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLoadInfInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgrLoadInfInd(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgrLoadInfInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rgMsg = (RgAccMsgQElm *)msg->data;
   cmXtaGetPst(&pst, RGAC_RGR_PROVENT, RGSCH_INST_START, RGAC_RGR_USERENT, 
           RGAC_RGR_USERINST, RGAC_RGR_SRCPROC, RGAC_RGR_DSTPROC, RGAC_RGR_MATCHPROC);

   pst.event = RGAC_RGR_EVTLOADINFIND;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rgrInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rgrInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));

   if (cellId != rgMsg->u.rgrInfo.loadInfInd.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rgrInfo.loadInfInd.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

/*
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));

   if (rgAccCb.acUeCb[ueId].crnti != rgMsg->u.rgrInfo.loadInfInd.crnti)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, rgMsg->u.rgrInfo.loadInfInd.crnti), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
    
   if(rgAcHdlRgrVldtDlPwrCtInfo( tcCb, spCb,
            &(rgMsg->u.rgrInfo.staInd.ueCqiInfo))!= CMXTA_ERR_NONE)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "DL Power control validation failed"), 2);
      RETVALUE(CMXTA_ERR_INT);
   }
*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcHdlRgrLoadInfInd */
/* LTE_ADV_FLAG_REMOVED_END */


/********************************************************************30**

         End of file:     rgac_rgrhdl.c@@/main/3 - Sat Jul 30 02:21:01 2011

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
             rg001.201 sm 1. Added TTI indication towards RGR user.
             rg004.201 rnt 1. Modified for SI Enhancement
/main/3      ---        dvasisht          1. Updated for LTE MAC Release 3.1
$SID$      ---          rt 1. LTE MAC 4.1 release
*********************************************************************91*/
