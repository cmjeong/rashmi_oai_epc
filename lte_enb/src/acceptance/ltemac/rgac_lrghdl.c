


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_lrghdl.c 
  
     Sid:      rgac_lrghdl.c@@/main/3 - Sat Jul 30 02:20:56 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_lrghdl.c
@brief This file contains the definitions for XTA LRG interface handler 
functions.
*/

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
#include "rgm.h"           /* RGM Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_lrg.h"        /* MAC error defines */
#include <stdlib.h>

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
#include "rgm.x"           /* RGM Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"        /* MAC error defines */
#include "rgac_lrg.x"        /* MAC error defines */


/**
 * @brief XTA General Configuration request handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgGenCfgReq
 *     
 *     Issues a Gen Cfg request from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgGenCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgGenCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   U8            nmbUpperSaps = 3;
   U8            nmbLowerSaps = 1;
   U8            region = 0;
   U8            pool = 0;
   RgMngmt       rgMngmt;
   RgGenCfg      *cfg;
   U8             tmrRes = 10;
   CmXtaTxnCb*   txnCb;
   Inst          instId = 0;

   TRC2(rgAcHdlLrgGenCfgReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgGenCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgGenCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbUpperSaps",  &(nmbUpperSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbLowerSaps",  &(nmbLowerSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "region",  &(region));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pool",  &(pool));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "tmrRes",  &(tmrRes));
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));


   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, instId,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   cfg = &(rgMngmt.t.cfg.s.genCfg);
#if 0
   cmXtaGetPst(&(cfg->lmPst), RGAC_LRG_PROVENT, RGAC_LRG_USERINST, RGAC_LRG_USERENT, 
         RGAC_LRG_PROVINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
#else
   cmXtaGetPst(&(cfg->lmPst), RGAC_LRG_PROVENT, instId, RGAC_LRG_USERENT, 
         RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
#endif

   cfg->mem.region = region;
   cfg->mem.pool = pool;
   cfg->tmrRes = tmrRes;

   cfg->numRguSaps = 6;

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   instId, RGAC_LRG_ELEMGENCFG, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_CFGREQ(&pst, &rgMngmt);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgGenCfgReq --*/



/**
 * @brief XTA TFU Sap Cfg Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgTfuSapCfgReq 
 *     
 *     Issues a TFU sap cfg from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgTfuSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgTfuSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst,entPst;
   RgMngmt       rgMngmt;
   RgLowSapCfg   *cfg;
   SpId          spId = 0;
   SuId          suId = 0;
   TmrCfg        bndTmr;
   CmXtaTxnCb*   txnCb;
   Inst          instId = 0;
 
   TRC2(rgAcHdlLrgTfuSapCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgTfuSapCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgTfuSapCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&entPst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   bndTmr.enb = TRUE;
   bndTmr.val = 5;
   
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "bndTimerValue",  &(bndTmr.val));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
 
   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, instId,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   cmXtaGetPst(&entPst, RGAC_LRG_PHYENT, RGAC_LRG_PHYINST, RGAC_LRG_PROVENT,
         instId,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   cfg = &(rgMngmt.t.cfg.s.tfuSap);
   cfg->suId         = suId;
   cfg->spId         = spId;
   cfg->mem.region = entPst.region;
   cfg->mem.pool   = entPst.pool;
   cfg->procId    = entPst.srcProcId;
   cfg->ent       = entPst.srcEnt;
   cfg->inst      = entPst.srcInst;
   cfg->prior     = entPst.prior;
   cfg->route     = entPst.route;
   cfg->selector       = entPst.selector;
   cfg->bndTmr.enb= bndTmr.enb;
   cfg->bndTmr.val= bndTmr.val;

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   instId, RGAC_LRG_ELEMTFUSAPCFG, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_CFGREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgTfuSapCfgReq --*/
 

/**
 * @brief XTA LRG Sap Cfg Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgRguSapCfgReq 
 *     
 *     Issues a LRG sap cfg from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgRguSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgRguSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst,entPst;
   RgMngmt       rgMngmt;
   RgUpSapCfg    *cfg;
   SpId          spId = 0;
   SuId          suId = 0;
   CmXtaTxnCb*   txnCb;
   Inst          instId = 0;
 
   TRC2(rgAcHdlLrgRguSapCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgRguSapCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgRguSapCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&entPst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
 
   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, instId,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   cmXtaGetPst(&entPst, RGAC_LRG_RLCENT, RGAC_LRG_RLCINST, RGAC_LRG_PROVENT,
   instId,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   cfg = &(rgMngmt.t.cfg.s.rguSap);
   cfg->suId         = suId;
   cfg->spId         = spId;
   cfg->mem.region = entPst.region;
   cfg->mem.pool   = entPst.pool;
   cfg->procId    = entPst.srcProcId;
   cfg->ent       = entPst.srcEnt;
   cfg->inst      = entPst.srcInst;
   cfg->prior     = entPst.prior;
   cfg->route     = entPst.route;
   cfg->selector       = entPst.selector;

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   instId, RGAC_LRG_ELEMRGUSAPCFG, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_CFGREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgRguSapCfgReq --*/
 

/**
 * @brief XTA CRG Sap Cfg Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgCrgSapCfgReq 
 *     
 *     Issues a CRG sap cfg from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgCrgSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgCrgSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst,entPst;
   RgMngmt       rgMngmt;
   RgUpSapCfg      *cfg;
   SpId          spId = 0;
   SuId          suId = 0;
   CmXtaTxnCb*   txnCb;
   Inst          inst = 0;
 
   TRC2(rgAcHdlLrgCrgSapCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCrgSapCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCrgSapCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&entPst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(inst));
 
   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, inst,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   cmXtaGetPst(&entPst, RGAC_LRG_RRCENT, RGAC_LRG_RRCINST, RGAC_LRG_PROVENT,
   inst,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   cfg = &(rgMngmt.t.cfg.s.crgSap);
   cfg->suId         = suId;
   cfg->spId         = spId;
   cfg->mem.region = entPst.region;
   cfg->mem.pool   = entPst.pool;
   cfg->procId    = entPst.srcProcId;
   cfg->ent       = entPst.srcEnt;
   cfg->inst      = entPst.srcInst;
   cfg->prior     = entPst.prior;
   cfg->route     = entPst.route;
   cfg->selector       = entPst.selector;

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   inst, RGAC_LRG_ELEMCRGSAPCFG, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_CFGREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgCrgSapCfgReq --*/
 

/**
 * @brief XTA RGR Sap Cfg Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgRgrSapCfgReq 
 *     
 *     Issues a RGR sap cfg from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgRgrSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgRgrSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgCrgSapCfgReq --*/

/**
 * @brief XTA Scheduler Instance Configuration Request for LRG Interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchInsCfgReq 
 *     
 *     Issues a Scheduler Instance config from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchInsCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchInsCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   Pst           rgrPst[LRG_MAX_SAPS_PER_INST],tfuPst[LRG_MAX_SAPS_PER_INST] ;
   Pst           rgmPst[LRG_MAX_SAPS_PER_INST];
   RgMngmt       rgMngmt;
   RgSchInstCfg  *cfg;
   Inst          instId = RGSCH_INST_START;
   U8            numSaps = 1;
   U8            rgr_suId[LRG_MAX_SAPS_PER_INST];
   U8            rgr_spId[LRG_MAX_SAPS_PER_INST];
   U8            num_rgrsuIds = 0;
   U8            num_rgrspIds = 0;
   U8            rgm_suId[LRG_MAX_SAPS_PER_INST];
   U8            rgm_spId[LRG_MAX_SAPS_PER_INST];
   U8            num_rgmsuIds = 0;
   U8            num_rgmspIds = 0;

   U8            tfu_suId[LRG_MAX_SAPS_PER_INST];
   U8            tfu_spId[LRG_MAX_SAPS_PER_INST];
   U8            num_tfusuIds = 0;
   U8            num_tfuspIds = 0;
   U8            numBndTmrval = 0;
   U8            idx;
   CmXtaTxnCb*   txnCb;
   TmrCfg        bndTmr[LRG_MAX_SAPS_PER_INST];
   U16           tmrVal[LRG_MAX_SAPS_PER_INST];
   U8            region = 0;
   U8            pool = 0;
   U8            tmrRes = 10;
 
   TRC2(rgAcHdlLrgSchInsCfgReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchInsCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchInsCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

  
   /* Read Instance Id of the Scheduler from XML Default Value is 1 */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   
   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT,
         instId,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   /* Read number of pairs of saps (RGR and TFU) needs to be configured 
    * Default value for this is 1 indicating by default 1 pair of (RGR and TFU)
    * is created for one cell*/ 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSaps",  &(numSaps));

   /* Read memory related details */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "region",  &(region));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pool",  &(pool));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "tmrRes",  &(tmrRes));
   
   rgMngmt.hdr.elmId.elmnt = STSCHINST;
   cfg = &(rgMngmt.t.cfg.s.schInstCfg);
   
   cmXtaGetPst(&(cfg->genCfg.lmPst), RGAC_LRG_PROVENT, instId,
         RGAC_LRG_USERENT,RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC,
         RGAC_LRG_MATCHPROC);

   cfg->genCfg.mem.region = region;
   cfg->genCfg.mem.pool = pool;
   cfg->genCfg.tmrRes = tmrRes;
   cfg->instId = instId;
   cfg->numSaps = numSaps;
#ifdef LTE_ADV
   cfg->genCfg.forceCntrlSrbBoOnPCel = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "forceCntrlSrbBoOnPCel",&(cfg->genCfg.forceCntrlSrbBoOnPCel));
   cfg->genCfg.isSCellActDeactAlgoEnable = TRUE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isSCellActDeactAlgoEnable",&(cfg->genCfg.isSCellActDeactAlgoEnable));
#endif

   /* Read spId and suId for RGR SAP */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON,
         "rgr_suId", rgr_suId, &num_rgrsuIds);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
         "rgr_spId", rgr_spId, &num_rgrspIds);
    /* Read spId and suId for RGM SAP */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON,
         "rgm_suId", rgm_suId, &num_rgmsuIds);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
         "rgm_spId", rgm_spId, &num_rgmspIds);
   
   /* Read spId and suId for TFU SAP */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
         "tfu_suId", tfu_suId, &num_tfusuIds);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
         "tfu_spId", tfu_spId, &num_tfuspIds);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
         "bndTimerValue", tmrVal, &numBndTmrval);
 
   for (idx = 0; idx < numSaps; idx++)
   {
      bndTmr[idx].enb = TRUE;
      bndTmr[idx].val = tmrVal[idx];
   }
   for (idx = 0; idx < numSaps; idx++)
   {
      CMXTA_ZERO(&rgrPst[idx], sizeof(Pst));
      CMXTA_ZERO(&rgmPst[idx], sizeof(Pst));
      CMXTA_ZERO(&tfuPst[idx], sizeof(Pst));
      /* PST details for RGR */
      cmXtaGetPst(&rgrPst[idx], RGAC_LRG_RGRENT, RGAC_LRG_RGRINST, RGAC_LRG_PROVENT,
           instId , RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
      cfg->rgrSap[idx].selector  = rgrPst[idx].selector;
      cfg->rgrSap[idx].mem.region= rgrPst[idx].region;
      cfg->rgrSap[idx].mem.pool  = rgrPst[idx].pool;
      cfg->rgrSap[idx].prior     = rgrPst[idx].prior;
      cfg->rgrSap[idx].procId    = rgrPst[idx].srcProcId;
      cfg->rgrSap[idx].ent       = rgrPst[idx].srcEnt;
      cfg->rgrSap[idx].inst      = rgrPst[idx].srcInst;
      cfg->rgrSap[idx].route     = rgrPst[idx].route;
      cfg->rgrSap[idx].spId      = rgr_spId[idx];
      cfg->rgrSap[idx].suId      = rgr_suId[idx];
       /* PST details for RGM */
      cmXtaGetPst(&rgmPst[idx], RGAC_LRG_RGMENT, RGAC_LRG_RGMINST, RGAC_LRG_PROVENT,
            instId, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
      cfg->rgmSap[idx].selector  = rgmPst[idx].selector;
      cfg->rgmSap[idx].mem.region= rgmPst[idx].region;
      cfg->rgmSap[idx].mem.pool  = rgmPst[idx].pool;
      cfg->rgmSap[idx].prior     = rgmPst[idx].prior;
      cfg->rgmSap[idx].procId    = rgmPst[idx].srcProcId;
      cfg->rgmSap[idx].ent       = rgmPst[idx].srcEnt;
      cfg->rgmSap[idx].inst      = rgmPst[idx].srcInst;
      cfg->rgmSap[idx].route     = rgmPst[idx].route;
      cfg->rgmSap[idx].spId      = rgm_spId[idx];
      cfg->rgmSap[idx].suId      = rgm_suId[idx];
      /* PST details for TFU */
      cmXtaGetPst(&tfuPst[idx], RGAC_LRG_PHYENT, RGAC_LRG_PROVINST, RGAC_LRG_PROVENT,
            instId,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
      cfg->tfuSap[idx].selector  = tfuPst[idx].selector;
      cfg->tfuSap[idx].mem.region= tfuPst[idx].region;
      cfg->tfuSap[idx].mem.pool  = tfuPst[idx].pool;
      cfg->tfuSap[idx].prior     = tfuPst[idx].prior;
      cfg->tfuSap[idx].procId    = tfuPst[idx].srcProcId;
      cfg->tfuSap[idx].ent       = tfuPst[idx].srcEnt;
      cfg->tfuSap[idx].inst      = tfuPst[idx].srcInst;
      cfg->tfuSap[idx].route     = tfuPst[idx].route;
      cfg->tfuSap[idx].spId      = tfu_spId[idx];
      cfg->tfuSap[idx].suId      = tfu_suId[idx];
      
      cfg->tfuSap[idx].bndTmr.enb= bndTmr[idx].enb;
      cfg->tfuSap[idx].bndTmr.val= bndTmr[idx].val;
   }

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   instId, RGAC_LRG_ELEMSCHINSCFG, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_SCHCFGREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchInsCfgReq --*/



/**
 * @brief XTA Config Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgCfgCfm 
 *     
 *     Validates cfg cfm from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgCfgCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst          instId = 0;
 
   TRC2(rgAcHdlLrgCfgCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, instId, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.rgMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgCfgCfm --*/


/**
 * @brief XTA Scheduler Config Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchCfgCfm 
 *     
 *     Validates sch cfg cfm from MAC (Sch Ins) to Dummy Layer Manager. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchCfgCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst     instId = RGSCH_INST_START;
 
   TRC2(rgAcHdlLrgSchCfgCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchCfgCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgSchCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, instId , RGAC_LRG_USERENT,
         RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTSCHCFGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgSchCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.rgMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchCfgCfm --*/


/**
 * @brief Skip Validation Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSkipValidation  
 *     
 *     If tester does not want a particular indication from MAC 
 *     to be validated, he can just issue the leaf command SKIP,
 *     This is the corresponding handler function for SKIP, which
 *     will pop off the last received indication, without any 
 *     further processing. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSkipValidation
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlLrgSkipValidation(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;

   TRC2(rgAcHdlLrgSkipValidation);
 
   UNUSED(spCb);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSkipValidation(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSkipValidation(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if(cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSkipValidation(): Peek failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*-- Remove the msg from the Queue --*/
   if(cmXtaPopMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSkipValidation(): Pop failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcHdlLrgSkipValidation*/





/**
 * @brief XTA Control Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgCntrlReq 
 *     
 *     Issues a Cntrl Req from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   RgMngmt       rgMngmt;
   RgCntrl       *cntrl;
   U8            action, subAction, elmntType;
   CmXtaTxnCb*   txnCb;
   Inst          instId = 0;
 
   TRC2(rgAcHdlLrgCntrlReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCntrlReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCntrlReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, instId,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   action = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "action",  &(action));
   subAction = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "subAction",  &(subAction));
   elmntType = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "elmntType",  &(elmntType));

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   cntrl = &(rgMngmt.t.cntrl);

   if (rgAcUtlLrgCntrlReq(tcCb, spCb, cntrl, action, subAction) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgCntrlReq() : failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   instId, elmntType, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_CNTRLREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgCntrlReq --*/


/**
 * @brief XTA Control Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgCntrlCfm 
 *     
 *     Validates cntrl cfm from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgCntrlCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgCntrlCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst     instId = 0;
 
   TRC2(rgAcHdlLrgCntrlCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

 
   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, instId, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);

   pst.event = RGAC_LRG_EVTCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgCntrlCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.rgMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgCntrlCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgCntrlCfm --*/


/**
 * @brief XTA Sch Control Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchCntrlReq 
 *     
 *     Issues a Cntrl Req from Dummy Layer Manager to MAC (Scheduler Instance). 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchCntrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   RgMngmt       rgMngmt;
   RgCntrl       *cntrl;
   U8            action, subAction, elmntType;
   CmXtaTxnCb*   txnCb;
   Inst          instId = RGSCH_INST_START;
 
   TRC2(rgAcHdlLrgSchCntrlReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchCntrlReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchCntrlReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, 
         instId,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   action = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "action",  &(action));
   subAction = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "subAction",  &(subAction));
   elmntType = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "elmntType",  &(elmntType));

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   cntrl = &(rgMngmt.t.cntrl);

   if (rgAcUtlLrgCntrlReq(tcCb, spCb, cntrl, action, subAction) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgCntrlReq() : failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   instId, elmntType, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_SCHCNTRLREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchCntrlReq --*/


/**
 * @brief XTA Control Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchCntrlCfm 
 *     
 *     Validates cntrl cfm from MAC(Scheduler Instance) to LM.
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchCntrlCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchCntrlCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst     instId = RGSCH_INST_START;
 
   TRC2(rgAcHdlLrgSchCntrlCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif

  cmMemset((U8 *)&status, 0, sizeof(CmStatus));
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgSchCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, instId, RGAC_LRG_USERENT, 
         RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTSCHCNTRLCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgSchCntrlCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.rgMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchCntrlCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchCntrlCfm --*/


/**
 * @brief XTA Statistics Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgStsReq 
 *     
 *     Issues a Sts Req from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgStsReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   RgMngmt       rgMngmt;
   RgSts         *sts;
   U8            sapInst=0, elmntType;
   CmXtaTxnCb*   txnCb;
   U8            action = 0;
 
   TRC2(rgAcHdlLrgStsReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStsReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStsReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "elmntType",  &(elmntType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapInst",
   &(sapInst));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(action));

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   sts = &(rgMngmt.t.sts);
   sts->sapInst = sapInst;
   sts->action = action;
   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   RGAC_LRG_PROVINST, elmntType, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_STSREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgStsReq --*/


/**
 * @brief XTA Statistics Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgStsCfm 
 *     
 *     Validates sts cfm from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgStsCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgStsCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Bool     validateSts = FALSE;
   U8  elmntType= STGEN;
   U32 numPduRcvd=0;
   U32 numPduTxmit=0;
   U32 numPduDrop=0;
   U32 numHarqFail=0;
   U32 numUeCfg=0;
   U16 numCellCfg=0;
   
 
   TRC2(rgAcHdlLrgStsCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgStsCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTSTSCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgStsCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "elmntType",  &(elmntType));
   if (rgMsg->u.rgMngmt.hdr.elmId.elmnt != elmntType)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : elmntType mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.rgMngmt.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "validateSts",
   &(validateSts));
   if (validateSts == FALSE) goto phinish;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numHarqFail",
   &(numHarqFail));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numUeCfg",
   &(numUeCfg));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numCellCfg",
   &(numCellCfg));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numPduRcvd",
   &(numPduRcvd));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numPduTxmit",
   &(numPduTxmit));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numPduDrop",
   &(numPduDrop));
   switch(elmntType)
   {
      case STRGUSAP:
         if ((numPduRcvd != rgMsg->u.rgMngmt.t.sts.s.rguSts.numPduRcvd) ||
             (numPduTxmit != rgMsg->u.rgMngmt.t.sts.s.rguSts.numPduTxmit) ||
             (numPduDrop != rgMsg->u.rgMngmt.t.sts.s.rguSts.numPduDrop))
         {
            CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : sap sts mismatch\n"));
            /*-- Free memory, use callback function --*/
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
         break;
      case STTFUSAP:
         if ((numPduRcvd != rgMsg->u.rgMngmt.t.sts.s.tfuSts.numPduRcvd) ||
             (numPduTxmit != rgMsg->u.rgMngmt.t.sts.s.tfuSts.numPduTxmit) ||
             (numPduDrop != rgMsg->u.rgMngmt.t.sts.s.tfuSts.numPduDrop))
         {
            CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : sap sts mismatch\n"));
            /*-- Free memory, use callback function --*/
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
         break;
      case STCRGSAP:
         if ((numPduRcvd != rgMsg->u.rgMngmt.t.sts.s.crgSts.numPduRcvd) ||
             (numPduTxmit != rgMsg->u.rgMngmt.t.sts.s.crgSts.numPduTxmit) ||
             (numPduDrop != rgMsg->u.rgMngmt.t.sts.s.crgSts.numPduDrop))
         {
            CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : sap sts mismatch\n"));
            /*-- Free memory, use callback function --*/
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
         break;
      case STRGRSAP:
         if ((numPduRcvd != rgMsg->u.rgMngmt.t.sts.s.rgrSts.numPduRcvd) ||
             (numPduTxmit != rgMsg->u.rgMngmt.t.sts.s.rgrSts.numPduTxmit) ||
             (numPduDrop != rgMsg->u.rgMngmt.t.sts.s.rgrSts.numPduDrop))
         {
            CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : result mismatch\n"));
            /*-- Free memory, use callback function --*/
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
         break;
       case STGEN:
          if ((numHarqFail != rgMsg->u.rgMngmt.t.sts.s.genSts.numHarqFail) ||
             (numUeCfg != rgMsg->u.rgMngmt.t.sts.s.genSts.numUeCfg) ||
             (numCellCfg != rgMsg->u.rgMngmt.t.sts.s.genSts.numCellCfg))
         {
            CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStsCfm() : gen sts mismatch\n"));
            /*-- Free memory, use callback function --*/
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
         break;
   }
phinish:   
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgStsCfm --*/



/**
 * @brief XTA Status Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgStaReq 
 *     
 *     Issues a Sta Req from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   RgMngmt       rgMngmt;
   RgSsta        *sta;
   U8            sapInst=0, elmntType;
   CmXtaTxnCb*   txnCb;
 
   TRC2(rgAcHdlLrgStaReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStaReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStaReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&rgMngmt, sizeof(RgMngmt));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST,
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "elmntType",  &(elmntType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapInst",
   &(sapInst));

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
 
   sta = &(rgMngmt.t.ssta);
   sta->sapInst = sapInst;
   if (elmntType == STGEN)
   {
      SGetSBuf(pst.region, pst.pool, (Data **)&sta->s.sysId.ptNmb, LRG_MAX_PT_NUM_SIZE);
      cmMemset((U8 *)sta->s.sysId.ptNmb, 0, LRG_MAX_PT_NUM_SIZE);
   }
   /* Prepare header */
   (Void) cmXtaInitHdr(&(rgMngmt.hdr), txnCb->txnId, RGAC_LRG_PROVENT,
   RGAC_LRG_PROVINST, elmntType, pst.selector);

   /* Send the request to the MAC --*/
   RGAC_LRG_STAREQ(&pst, &rgMngmt);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgStaReq --*/


/**
 * @brief XTA Status Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgStaCfm 
 *     
 *     Validates sta cfm from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgStaCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   U8       sapState=0, incSapState = 0;
   U8       sapInst=0;
 
   TRC2(rgAcHdlLrgStaCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgStaCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   if (rgMsg->u.rgMngmt.t.ssta.s.sysId.ptNmb != NULLP)
   {
      SPutSBuf(pst.region, pst.pool, (Data *)rgMsg->u.rgMngmt.t.ssta.s.sysId.ptNmb, LRG_MAX_PT_NUM_SIZE);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.rgMngmt.cfm));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStaCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapInst",
   &(sapInst));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "sapState",
   &(sapState));
   switch (sapInst)
   {
      case RGAC_LRG_RGUSAPINST:
         incSapState = rgMsg->u.rgMngmt.t.ssta.s.rguSapSta.sapState;
         break;
      case RGAC_LRG_TFUSAPINST:
         incSapState = rgMsg->u.rgMngmt.t.ssta.s.tfuSapSta.sapState;
         break;
      case RGAC_LRG_CRGSAPINST:
         incSapState = rgMsg->u.rgMngmt.t.ssta.s.crgSapSta.sapState;
         break;
      case RGAC_LRG_RGRSAPINST:
         incSapState = rgMsg->u.rgMngmt.t.ssta.s.rgrSapSta.sapState;
         break;
      case RGAC_LRG_RGMSAPINST:
         incSapState = rgMsg->u.rgMngmt.t.ssta.s.rgmSapSta.sapState;
         break;
   }
   if (incSapState != sapState)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStaCfm() : sapState mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgStaCfm --*/



/**
 * @brief XTA Status Indication Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgStaInd 
 *     
 *     Validates sta Ind from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb   *tcCb 
 *  @param[in] CmXtaSpCb   *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgStaInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16 ret = ROK;
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   Pst      pst;
   U8       category=0, cause=0;
   U16      event = 0;
   Bool validateElem = FALSE;
   S16 element;
 
   TRC2(rgAcHdlLrgStaInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgStaInd(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgStaInd() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*validation of element is optional*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"validateElem",&validateElem);
   if(validateElem)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"element",&element);
      if(rgMsg->u.rgMngmt.hdr.elmId.elmnt != element)
      {
         CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStaInd() failed,expected element\
                 %d received %d\n",element,rgMsg->u.rgMngmt.hdr.elmId.elmnt));
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   } 

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"category",&(category));
   if(rgMsg->u.rgMngmt.t.usta.cmAlarm.category != category)
   {
       CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStaInd() failed,expected category\
               %d received %d\n",category,rgMsg->u.rgMngmt.t.usta.cmAlarm.category));
       cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
       RETVALUE(CMXTA_ERR_INT);
   }
     
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"event",&(event));
   if(rgMsg->u.rgMngmt.t.usta.cmAlarm.event != event)
   {
       CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStaInd() failed,expected  event\
               %d received %d\n",event,rgMsg->u.rgMngmt.t.usta.cmAlarm.event));
       cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
       RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"cause",&(cause));
   if(rgMsg->u.rgMngmt.t.usta.cmAlarm.cause != cause)
   {
       CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgStaInd() failed,expected cause\
               %d received %d\n",cause,rgMsg->u.rgMngmt.t.usta.cmAlarm.cause));
       cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
       RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgStaInd --*/

/**
 * @brief XTA Status Indication Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchStaInd 
 *     
 *     Validates sta Ind from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb   *tcCb 
 *  @param[in] CmXtaSpCb   *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchStaInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16 ret = ROK;
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   Pst      pst;
   U8       category=0;
   U16      cause = 0;
   U16      event=0;
   Bool validateElem = FALSE;
   S16 element;
   Inst          instId = 1;
 
   TRC2(rgAcHdlLrgSchStaInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchStaInd(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgSchStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   /*cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);*/
   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGSCH_INST_START, RGAC_LRG_USERENT,
         RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
/*   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT,
         (RGAC_LRG_PROVINST+1),RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);*/
 
   pst.event = RGAC_LRG_EVTSCHSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgSchStaInd() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /* Read Instance Id of the Scheduler from XML Default Value is 1 */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   /*validation of element is optional*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"validateElem",&validateElem);
   if(validateElem)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"element",&element);
      if(rgMsg->u.rgMngmt.hdr.elmId.elmnt != element)
      {
         CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchStaInd() failed,expected element\
                 %d received %d\n",element,rgMsg->u.rgMngmt.hdr.elmId.elmnt));
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   } 

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"category",&(category));
   if(rgMsg->u.rgMngmt.t.usta.cmAlarm.category != category)
   {
       CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchStaInd() failed,expected category\
               %d received %d\n",category,rgMsg->u.rgMngmt.t.usta.cmAlarm.category));
       cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
       RETVALUE(CMXTA_ERR_INT);
   }
     
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"event",&(event));
   if(rgMsg->u.rgMngmt.t.usta.cmAlarm.event != event)
   {
       CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchStaInd() failed,expected event\
               %d received %d\n",event,rgMsg->u.rgMngmt.t.usta.cmAlarm.event));
       cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
       RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"cause",&(cause));
   if(rgMsg->u.rgMngmt.t.usta.cmAlarm.cause != cause)
   {
       CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchStaInd() failed,expected cause\
               %d received %d\n",cause,rgMsg->u.rgMngmt.t.usta.cmAlarm.cause));
       cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
       RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchStaInd --*/



/**
 * @brief XTA Trace Indication Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgTrcInd 
 *     
 *     Validates trc Ind from Dummy Layer Manager to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgTrcInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgTrcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   S16 ret=ROK;
   CmXtaMsgQElm   *msg;
   Pst      pst;
 
   TRC2(rgAcHdlLrgTrcInd);

   UNUSED(spCb);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGAC_LRG_PROVINST, RGAC_LRG_USERENT, RGAC_LRG_USERINST, 
   RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTTRCIND; 

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgTrcInd(): No Match, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   ret = cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgTrcInd(): cmXtaPopMsg Failed."));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgStaInd --*/

#ifdef LTE_L2_MEAS

/**
 * @brief XTA Sch L2 Measurement Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchL2MeasReq
 *     
 *     Issues a L2 Measurement Req from Dummy Layer Manager to
 *     MAC (Scheduler Instance). 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchL2MeasReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchL2MeasReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst                 pst;
   LrgSchMeasReqInfo   measInfo;
   U32                 transId
 
   TRC2(rgAcHdlLrgSchL2MeasReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2MeasReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2MeasReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&measInfo, sizeof(LrgSchMeasReqInfo));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, 
         RGSCH_INST_START,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "measType",  &(measInfo.measType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "timePrd",  &(measInfo.timePrd));
   measInfo.cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(measInfo.cellId));

   if (rgAcUtlLrgSchL2MeasReq(tcCb, spCb, &measInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgSchL2MeasReq() : failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Prepare header */
   measInfo.hdr.elmId.elmnt = STSCHINST;
   transId = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",
                 &(transId));
   (Void) cmXtaInitHdr(&(measInfo.hdr), transId, RGAC_LRG_PROVENT,
   RGAC_LRG_PROVINST, 0, pst.selector);
   /* Send the l2 Meas request to the MAC --*/
   RGAC_LRG_SCHL2MEASREQ(&pst, &measInfo);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchL2MeasReq --*/


/**
 * @brief XTA Scheduler Measurement Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchL2MeasCfm
 *     
 *     Validates sch cfg cfm from MAC (Sch Ins) to Dummy Layer Manager. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchL2MeasCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchL2MeasCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
 
   TRC2(rgAcHdlLrgSchL2MeasCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2MeasCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2MeasCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgSchL2MeasCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGSCH_INST_START, RGAC_LRG_USERENT,
         RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTL2MEASCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgSchL2MeasCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.l2MeasInfo.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = rgAcUtlLrgSchValL2MeasCfm(tcCb, spCb, &(rgMsg->u.l2MeasInfo));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgSchValL2MeasCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchCfgCfm --*/

/* Anshika Start */


/**
 * @brief XTA Scheduler Measurement Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchL2StopMeasCfm
 *     
 *     Validates sch cfg cfm from MAC (Sch Ins) to Dummy Layer Manager. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 *      -# CMXTA_ERR_NOMATCH
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchL2StopMeasCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchL2StopMeasCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm   *msg;
   RgAccMsgQElm   *rgMsg;
   CmStatus       status;
   Pst      pst;
   S16      ret;
 
   TRC2(rgAcHdlLrgSchL2StopMeasCfm);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2StopMeasCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2StopMeasCfm(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlLrgSchL2StopMeasCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_LRG_PROVENT, RGSCH_INST_START, RGAC_LRG_USERENT,
         RGAC_LRG_USERINST, RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 
   pst.event = RGAC_LRG_EVTL2MEASSTOPCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "rgAcHdlLrgSchL2StopMeasCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",
   &(status.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",
   &(status.reason));
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(rgMsg->u.l2MeasInfo.cfm));
 
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlLrgSchCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

#if 0 /* Anshika: TBD */
   ret = rgAcUtlLrgSchValL2MeasCfm(tcCb, spCb, &(rgMsg->u.l2MeasInfo));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgSchValL2MeasCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
#endif
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchCfgCfm --*/


/**
 * @brief XTA Sch L2 Measurement Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchSendL2MeasReq
 *     
 *     Issues a L2 Measurement Req from Dummy Layer Manager to
 *     MAC (Scheduler Instance). 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchSendL2MeasReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchSendL2MeasReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst                 pst;
   LrgSchMeasSndReqInfo   measInfo;
   U32                 transId
 
   TRC2(rgAcHdlLrgSchSendL2MeasReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchSendL2MeasReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchSendL2MeasReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&measInfo, sizeof(LrgSchMeasSndReqInfo));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, 
         RGSCH_INST_START,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "measType",  &(measInfo.measType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "timePrd",  &(measInfo.timePrd));
   measInfo.cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(measInfo.cellId));

#if 0
   if (rgAcUtlLrgSchL2MeasReq(tcCb, spCb, &measInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgSchL2MeasReq() : failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
#endif

   /* Prepare header */
   measInfo.hdr.elmId.elmnt = STSCHINST;
   transId = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",
                 &(transId));
   (Void) cmXtaInitHdr(&(measInfo.hdr), transId, RGAC_LRG_PROVENT,
   RGAC_LRG_PROVINST, 0, pst.selector);
   /* Send the l2 Meas request to the MAC --*/
   RGAC_LRG_SCHL2SENDMEASREQ(&pst, &measInfo);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchL2MeasReq --*/


/**
 * @brief XTA Sch L2 Measurement Req Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgSchStopL2MeasReq
 *     
 *     Issues a L2 Measurement Req from Dummy Layer Manager to
 *     MAC (Scheduler Instance). 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_RSRC 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgSchStopL2MeasReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgSchStopL2MeasReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst                 pst;
   LrgSchMeasStopReqInfo   measInfo;
   U32                 transId
 
   TRC2(rgAcHdlLrgSchStopL2MeasReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2MeasReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgSchL2MeasReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&measInfo, sizeof(LrgSchMeasStopReqInfo));

   cmXtaGetPst(&pst, RGAC_LRG_USERENT, RGAC_LRG_USERINST, RGAC_LRG_PROVENT, 
         RGSCH_INST_START,RGAC_LRG_SRCPROC, RGAC_LRG_DSTPROC, RGAC_LRG_MATCHPROC);
 /* Anshika made it U16 */  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "measType",  &(measInfo.measType));
   measInfo.cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(measInfo.cellId));

#if 0   
   if (rgAcUtlLrgSchL2MeasReq(tcCb, spCb, &measInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlLrgSchL2MeasReq() : failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
#endif
   /* Prepare header */
   measInfo.hdr.elmId.elmnt = STSCHINST;
   transId = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",
                 &(transId));
   (Void) cmXtaInitHdr(&(measInfo.hdr), transId, RGAC_LRG_PROVENT,
   RGAC_LRG_PROVINST, 0, pst.selector);
   /* Send the l2 Meas request to the MAC --*/
   RGAC_LRG_SCHL2STOPMEASREQ(&pst, &measInfo);
    
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgSchL2MeasReq --*/


/* Anshika End */
#endif

/**
 * @brief XTA Directive Handler for LRG interface. 
 *
 * @details
 *
 *     Function : rgAcHdlLrgDirective 
 *     
 *     XTA Directive Handler for LRG interface. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlLrgDirective 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlLrgDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
 
   TRC2(rgAcHdlLrgDirective);

   UNUSED(spCb);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgDirective(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlLrgDirective(): tcId (%d)\n", tcCb->tcId));
#endif
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlLrgDirective --*/



/**********************************************************************
 
         End of file:     rgac_lrghdl.c@@/main/3 - Sat Jul 30 02:20:56 2011
 
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
/main/1      ---     sm                1. Initial Release.
/main/2      ---     sm                1. LTE MAC 2.1 release
           rg003.201 ns                1. Ccpu00108135. Changed cause var
                                          from U8 to U16.
           rg004.201 ns                1. Memory Fix.
/main/3      ---      dvasisht          1. Updated for LTE MAC Release 3.1          
$SID$      ---          rt              1. LTE MAC 4.1 release
*********************************************************************91*/
