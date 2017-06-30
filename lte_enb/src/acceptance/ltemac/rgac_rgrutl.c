

/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_rgrutl.c

     Sid:      rgac_rgrutl.c@@/main/3 - Sat Jul 30 02:21:03 2011

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
#include "rgac_crg.h"
#include "rgac_rgr.h"
#include "rgac_acc.h"

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

PRIVATE S16 rgAcUtlRgrfillNdmrsWrapper ARGS ((U8 bw,U8 ngEnum,U8 sbStart,U8 numSb,
      U8 sbSize,U8 ndmrsArr[]));
PRIVATE S16 rgAcUtlRgrfillNdmrs ARGS ((U8 sbStart,U8 numSb,U8 sbSize,U8 numGrp,
         U8 *ndmrsP));
PRIVATE U8 rgAcUtlRgrphichUsed ARGS ((U16 phich,U16 numPhich,U16 phichArr[]));
PRIVATE U16 rgAcUtlRgrgetPhich ARGS ((U8 rbStart,U8 ndmrs,U8 numGrp));
PRIVATE U8 rgAcUtlRgrgetPhichGrp ARGS ((U8 rbStart,U8 ndmrs,U8 numGrp));
PRIVATE U8 rgAcUtlRgrgetPhichSeq ARGS ((U8 rbStart,U8 ndmrs,U8 numGrp));

PRIVATE Void rgAcUtlRgrBuildPfsDefDlCqiPrioTbl ARGS ((RgrCfgReqInfo  *cfgReq));
PRIVATE Void rgAcUtlRgrBuildPfsDefUlLcgPrioTbl ARGS ((RgrCfgReqInfo  *cfgReq));

/* Adding preamble format to lenght mapping table */
#ifdef LTE_TDD
RgAccSchRaPrmFmtToRaPrmLenTbl rgAccSchRaPrmFmtToRaPrmLenTbl = {1, 2, 2, 3, 1};
#else
RgAccSchRaPrmFmtToRaPrmLenTbl rgAccSchRaPrmFmtToRaPrmLenTbl = {1, 2, 2, 3};
#endif

PRIVATE Void rgAcUtlRgrBuildSCellAddCfg ARGS((
         CmXtaTCCb      *tcCb,    /* tcCb data structure  */
         CmXtaSpCb      *spCb,
         RgrCfgReqInfo  *cfgReq
         ));

/**
 * @brief XTA  Utility function to read cell configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildDlfsSchInfo
 *     
 *     Utility function to read Scheduler Specific Information for 
 *     Uplink from XML and fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildDlfsSchInfo
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildDlfsSchInfo(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   RgrCellCfg *cfg;

   cfg   = &(cfgReq->u.cfgInfo.u.cellCfg);

   /* Which DLFS Scheduler Type to use */
   cfg->dlfsSchdType= 0; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlfsSchdType", 
         &(cfg->dlfsSchdType));
   
   cfg->dlfsCfg.isDlFreqSel = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isDlFreqSel", 
         &(cfg->dlfsCfg.isDlFreqSel));

  
} /* rgAcUtlRgrBuildDlfsSchInfo*/

/**
 * @brief XTA  Utility function to read cell configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildUlSchInfo
 *     
 *     Utility function to read Scheduler Specific Information for 
 *     Uplink from XML and fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildUlSchInfo
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildUlSchInfo(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   //U8        numCqiPrios;
   //U8        numFracPrios;
   //U8        numLcgPrios;
   RgrSchedEnbCfg *cfg;

   cfg   = &(cfgReq->u.cfgInfo.u.schedEnbCfg);
   /* Downlink Scheduler Type Default RR*/
   cfg->ulSchdType = RGAC_RGR_SCH_TYPE_RR;

   /* raAccCb.ulSchdType updated from command line argument -x -d 1 -s 1*/
   cfg->ulSchdType = rgAccCb.ulSchedType;
   
   /* If value is given through xml then over rides value from command line */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ulSchdType", 
         &(cfg->ulSchdType));
  
   if (cfg->ulSchdType == RGAC_RGR_SCH_TYPE_PFS)
   {
      cfg->ulSchInfo.ulPfs.fairCoeffi = 10;
      cfg->ulSchInfo.ulPfs.tptCoeffi = 10;
      cfg->ulSchInfo.ulPfs.qciWgt[0] = 8;
      cfg->ulSchInfo.ulPfs.qciWgt[1] = 6;
      cfg->ulSchInfo.ulPfs.qciWgt[2] = 7;
      cfg->ulSchInfo.ulPfs.qciWgt[3] = 5;
      cfg->ulSchInfo.ulPfs.qciWgt[4] = 9;
      cfg->ulSchInfo.ulPfs.qciWgt[5] = 4;
      cfg->ulSchInfo.ulPfs.qciWgt[6] = 3;
      cfg->ulSchInfo.ulPfs.qciWgt[7] = 2;
      cfg->ulSchInfo.ulPfs.qciWgt[8] = 1;
 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ulThroughputFactor",
         &(cfg->ulSchInfo.ulPfs.tptCoeffi));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ulFairnessFactor",
         &(cfg->ulSchInfo.ulPfs.fairCoeffi));
#if 0
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,CMXTA_SEP_COLON,
            "lcgPrios", cfg->ulSchInfo.cellUlPfs.lcgPrios, &numLcgPrios);
      if (!numLcgPrios)
      {
         rgAcUtlRgrBuildPfsDefUlLcgPrioTbl(cfgReq);
      }
#endif
   }
   else if (cfg->ulSchdType == RGAC_RGR_SCH_TYPE_MAXCI)
   {
      /* Read MAX CI Information  */
   }
} /* rgAcUtlRgrBuildUlSchInfo*/


/**
 * @brief XTA  Utility function to read cell configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildDlSchInfo
 *     
 *     Utility function to read cell configuration values from XML and
 *     fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildDlSchInfo
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildDlSchInfo(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   RgrSchedEnbCfg *cfg;

   cfg   = &(cfgReq->u.cfgInfo.u.schedEnbCfg);
   /* Downlink Scheduler Type RR*/
   cfg->dlSchdType = RGAC_RGR_SCH_TYPE_RR;
   
   /* raAccCb.dlSchedType updated from command line argument -x -d 1 -s 1*/
   cfg->dlSchdType = rgAccCb.dlSchedType; //RGAC_RGR_SCH_TYPE_PFS;// NAVEEN  Added this only for Testing first TC 
   //rgAccCb.dlSchedType;
   
   /* If value is given through xml then it over rides value from command line*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlSchdType", 
         &(cfg->dlSchdType));

   if (cfg->dlSchdType == RGAC_RGR_SCH_TYPE_PFS)
   {
      cfg->dlSchInfo.dlPfs.fairCoeffi = 10;
      cfg->dlSchInfo.dlPfs.tptCoeffi = 10;
      cfg->dlSchInfo.dlPfs.qciWgt[0] = 8;
      cfg->dlSchInfo.dlPfs.qciWgt[1] = 6;
      cfg->dlSchInfo.dlPfs.qciWgt[2] = 7;
      cfg->dlSchInfo.dlPfs.qciWgt[3] = 5;
      cfg->dlSchInfo.dlPfs.qciWgt[4] = 9;
      cfg->dlSchInfo.dlPfs.qciWgt[5] = 4;
      cfg->dlSchInfo.dlPfs.qciWgt[6] = 3;
      cfg->dlSchInfo.dlPfs.qciWgt[7] = 2;
      cfg->dlSchInfo.dlPfs.qciWgt[8] = 1;
      
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dlThroughputFactor",
         &(cfg->dlSchInfo.dlPfs.tptCoeffi));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dlFairnessFactor",
         &(cfg->dlSchInfo.dlPfs.fairCoeffi));
   }
   else if (cfg->dlSchdType == RGAC_RGR_SCH_TYPE_MAXCI)
   {
      /* Read MAX CI Information  */
   }
} /* rgAcUtlRgrBuildDlSchInfo*/


/**
 * @brief XTA  Utility function to read ENB configuration values from
 * XML/DEFAULT and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildEnbCfgReq
 *     
 *     Utility function to read Enb configuration values from XML/Default and
 *     fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlRgrBuildEnbCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC S16 rgAcUtlRgrBuildEnbCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   RgrSchedEnbCfg    *cfg;
   Inst          macInst  = 0;
   TRC2(rgAcUtlRgrBuildEnbCfgReq)

      cfg   = &(cfgReq->u.cfgInfo.u.schedEnbCfg);

   CMXTA_ZERO(cfg , sizeof (RgrSchedEnbCfg));

   /*----------- Fill General Configuration Parameters ---------*/
   /* Configuration Type is CELL Configration */
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_ENB_CFG;

#if 0
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
#endif
   /* Default Values for numTxAntPorts is 1 */
   cfg->numTxAntPorts = RGAC_RGR_DEFAULT_NUMTXNPORTS;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numTxAntPorts", 
         &(cfg->numTxAntPorts));

   rgAccCb.numTxAntPorts = cfg->numTxAntPorts;

   cfg->accsMode = RGR_CELL_ACCS_OPEN;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "csgAccMode",
         &(cfg->accsMode));

   /* Reading downlink scheduler Specific Information */
   rgAcUtlRgrBuildDlSchInfo(tcCb, spCb, cfgReq);

   /* Reading Uplink scheduler Specific Information */
   rgAcUtlRgrBuildUlSchInfo(tcCb, spCb, cfgReq);
   /* MultiInstance change */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "macInst",  &(macInst));

   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcUtlRgrBuildCellCfgReq */
/**
 * @brief XTA  Utility function to read cell configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildCellCfgReq
 *     
 *     Utility function to read cell configuration values from XML and
 *     fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlRgrBuildCellCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC S16 rgAcUtlRgrBuildCellCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrCellCfg    *cfg;
   //S16           ret;
   U8            valid=FALSE;
   U32           ngEnum=0;
   U32           srsBwEnum=0;
   U8            num;
   U8            lcInfo[RGAC_RGR_MAX_LCINFO];
   U8            lcCnt, lcInfoCnt;
#ifdef LTE_TDD
   U8            freqIdxLst[6];
   U8            sfnLst[6];
   U8            halfFrmLst[6];
   U8            ulStartSfIdxLst[6];
   U8            numFreqIdx;
#endif /* LTE_TDD */
#ifdef TFU_UPGRADE  
   U8            saven1Pucch = 0;
#endif
   Inst          macInst  = 0;
   U8            isLaaCell = FALSE;
   /* LTE_ADV_FLAG_REMOVED_START */
   U8 idx;
   U8 absPattern[10];
   U8 absNum;
   U8 idx1;
   S16 pMax = 23;
   /* LTE_ADV_FLAG_REMOVED_END */
   TRC2(rgAcUtlRgrBuildCellCfgReq)

      cfg   = &(cfgReq->u.cfgInfo.u.cellCfg);

   CMXTA_ZERO(cfg , sizeof (RgrCellCfg));

   /*----------- Fill General Configuration Parameters ---------*/
   /* Configuration Type is CELL Configration */
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_CELL_CFG;

   /* Assiging Default Cell Id "3" */
   cfg->cellId = RG_ACC_CELLID;
   /*Reading CELL Id from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));

   cfg->siCfg.siWinSize = 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siWinSize", 
         &(cfg->siCfg.siWinSize));

   cfg->siCfg.retxCnt = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siRetxCnt", 
         &(cfg->siCfg.retxCnt));

#ifdef RGR_SI_SCH
   /*ccpu00115364 MOD changed modPrd default value to lowest configurable val*/

/* solaris changes for  g++ compilation */ 
 cfg->siCfg.modPrd = (RgrModPeriodicity)64;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "modPrd", 
         &(cfg->siCfg.modPrd));
   cfg->siCfg.numSi = 4;
   cfg->siCfg.siPeriodicity[0] = (RgrSiPeriodicity)8;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "si1Prd", 
         &(cfg->siCfg.siPeriodicity[0]));
   cfg->siCfg.siPeriodicity[1] = (RgrSiPeriodicity)8;
   cfg->siCfg.siPeriodicity[2] = (RgrSiPeriodicity)16;
   cfg->siCfg.siPeriodicity[3] = (RgrSiPeriodicity)32;
#endif

   /* Assigning Default value for Downlink Max HARQ Transmissions "4"*/
   cfg->dlHqCfg.maxDlHqTx = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxDlHqTx", 
         &(cfg->dlHqCfg.maxDlHqTx));
   cfg->dlHqCfg.maxMsg4HqTx = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg4HqTx",
         &(cfg->dlHqCfg.maxMsg4HqTx));

#ifndef LTE_TDD
   /* Range of RNTI's Managed by MAC starts from 10 */
   cfg->macRnti.startRnti = 11;
#else
   cfg->macRnti.startRnti = 61;
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "startRnti",
         &(cfg->macRnti.startRnti));
   cfg->macRnti.size = 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rntiSize",
         &(cfg->macRnti.size));

   /* Assigning Default value for CFI "2" */
   cfg->cfiCfg.cfi = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cfi",
         &(cfg->cfiCfg.cfi));

   /* Assigning Default value for Target Uplink CQI "6" */
   cfg->trgUlCqi.trgCqi = 9;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trgCqi",
         &(cfg->trgUlCqi.trgCqi));

   /* Reading Coding rate for Downlink Channels */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "bcchPchCodeRate",
         &(cfg->dlCmnCodeRate.bcchPchRaCodeRate));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pdcchCodeRate",
         &(cfg->dlCmnCodeRate.pdcchCodeRate));
   cfg->dlCmnCodeRate.ccchCqi = RGAC_RGR_DEFAULT_DLCQI;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlCcchCqi",
         &(cfg->dlCmnCodeRate.ccchCqi));
   /* Filling Default Value for Downlink BandWidth */
   cfg->bwCfg.dlTotalBw = RGAC_RGR_DEFAULT_DLTOTBW;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlTotalBw", 
         &(cfg->bwCfg.dlTotalBw));

   /* Compute rbgSize, number of RBGs and lastRbgSize */
   if (cfg->bwCfg.dlTotalBw > 63)
   {
      rgAccCb.rbgSize = 4;
   }
   else if (cfg->bwCfg.dlTotalBw > 26)
   {
      rgAccCb.rbgSize = 3;
   }
   else if (cfg->bwCfg.dlTotalBw > 10)
   {
      rgAccCb.rbgSize = 2;
   }
   else
   {
      rgAccCb.rbgSize = 1;
   }

   rgAccCb.numRbgs =  (cfg->bwCfg.dlTotalBw + rgAccCb.rbgSize - 1)/ 
      (rgAccCb.rbgSize); 
   rgAccCb.lastRbgSize = cfg->bwCfg.dlTotalBw - 
      ((cfg->bwCfg.dlTotalBw/rgAccCb.rbgSize) * rgAccCb.rbgSize);

   if (rgAccCb.lastRbgSize == 0)
   {
      rgAccCb.lastRbgSize=rgAccCb.rbgSize;
   }
   /* Filling Default Value for Uplink BandWidth */
   cfg->bwCfg.ulTotalBw = RGAC_RGR_DEFAULT_ULTOTBW;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ulTotalBw", 
         &(cfg->bwCfg.ulTotalBw));
   rgAccCb.dlTotalBw = cfg->bwCfg.dlTotalBw;
   rgAccCb.ulTotalBw = cfg->bwCfg.ulTotalBw; 

   /* Reading Uplink Sub Band Information */
   cfg->puschSubBand.subbandStart = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subbandStart",
         &(cfg->puschSubBand.subbandStart));

  /* Reading Sub Band Enum to Specify its size */
   ngEnum = RGAC_RGR_NG_ONESIXTH;
   cmXtaXmlGetVal(tcCb, spCb->childStep,CMXTA_ATTRIB_ENUM , "ngEnum",
         &ngEnum);
   rgAccCb.ngEnum = ngEnum;

   switch (rgAccCb.ngEnum)
   {
      case RGAC_RGR_NG_ONESIXTH:
         cfg->puschSubBand.size = 6;
         break;
      case RGAC_RGR_NG_HALF:
         cfg->puschSubBand.size = 2;
         break;
      case RGAC_RGR_NG_ONE:
      case RGAC_RGR_NG_TWO:
         cfg->puschSubBand.size = 1;
         break;
      default:
         /* ERROR */
         break;
   } /* End of switch */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "size",
         &(cfg->puschSubBand.size));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valid",
         &(valid));
   if (valid == FALSE)
   {
      cfg->puschSubBand.numSubbands = \
                                      (rgAccCb.ulTotalBw - cfg->puschSubBand.subbandStart)/cfg->puschSubBand.size;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSubbands",
         &(cfg->puschSubBand.numSubbands));

   /* Rading coding rate for uplink uplink channels */
   cfg->ulCmnCodeRate.ccchCqi = 8;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ccchCqi",
         &(cfg->ulCmnCodeRate.ccchCqi));

   cfg->maxUePerUlSf = 10; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUePerUlSf",
         &(cfg->maxUePerUlSf));
#ifdef RGR_V1
   cfg->maxMsg3PerUlSf = 4; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg3PerUlSf",
         &(cfg->maxMsg3PerUlSf));
#endif
   cfg->maxUlUeNewTxPerTti= 10; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlUeNewTxPerTti",
         &(cfg->maxUlUeNewTxPerTti));

   /* Assiging Default value for Uplink max Band Width Per UE */
   cfg->maxUlBwPerUe =  0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlBwPerUe",
         &(cfg->maxUlBwPerUe));

   /* Assging Default values for maximum Downlink Bandwidth Per UE */
   cfg->maxDlBwPerUe =  cfg->bwCfg.dlTotalBw/2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxDlBwPerUe", 
         &(cfg->maxDlBwPerUe));

   /* Assiging maximum Downlink retransmission bandwidth */
   cfg->maxDlRetxBw = cfg->bwCfg.dlTotalBw;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxDlRetxBw", 
         &(cfg->maxDlRetxBw));

   /* Assiging maximum UE per Downlink Subframe */
   cfg->maxUePerDlSf =  2; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUePerDlSf", 
         &(cfg->maxUePerDlSf));

   /* Assiging maximum UE to be considered for a Downlink scheduling per TTI */
   cfg->maxUlUeNewTxPerTti=  2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlUeNewTxPerTti", 
         &(cfg->maxUlUeNewTxPerTti));

   /* Assiging maximum UE to be considered for a Uplink scheduling per TTI */
   cfg->maxDlUeNewTxPerTti=  2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxDlUeNewTxPerTti", 
         &(cfg->maxDlUeNewTxPerTti));

   /* Assiging maximum CCCH MSG to be considered in Downlink*/
   //cfg->maxCcchPerDlSf =  1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxCcchPerDlSf", 
         &(cfg->maxCcchPerDlSf));

#if 0
   /* Reading downlink scheduler Specific Information */
   rgAcUtlRgrBuildDlSchInfo(tcCb, spCb, cfgReq);

   /* Reading Uplink scheduler Specific Information */
   rgAcUtlRgrBuildUlSchInfo(tcCb, spCb, cfgReq);
#endif
   /* Reading DLFS Specific Information */
   rgAcUtlRgrBuildDlfsSchInfo(tcCb, spCb, cfgReq);

   /* Default Value for isCpUlExtend is FALSE*/
   cfg->isCpUlExtend = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isCpUlExtend",
         &(cfg->isCpUlExtend));

   /* Default Value for isCpDlExtend is FALSE*/
   cfg->isCpDlExtend = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isCpDlExtend",
         &(cfg->isCpDlExtend));

   /* Reading PHICH Information */
   ngEnum = (RgrPhichNg)RGAC_RGR_NG_HALF;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ngEnum",
         &(ngEnum));
   rgAccCb.ngEnum = ngEnum;
   cfg->phichCfg.ngEnum = (RgrPhichNg) ngEnum;

   cfg->phichCfg.isDurExtend = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDurExtend", 
         &(cfg->phichCfg.isDurExtend));

   /* Reading Pucch configuration Information */
   cfg->pucchCfg.resourceSize = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "resourceSize", 
         &(cfg->pucchCfg.resourceSize));
   cfg->pucchCfg.n1PucchAn = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "n1PucchAn", 
         &(cfg->pucchCfg.n1PucchAn));
#ifdef TFU_UPGRADE  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saven1Pucch", 
         &saven1Pucch);
   if(saven1Pucch)
   {
      rgAccCb.n1PucchAn = cfg->pucchCfg.n1PucchAn;
   }
#endif
   
     cfg->pucchCfg.maxPucchRb = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxPucchRb", 
         &(cfg->pucchCfg.maxPucchRb));

   cfg->pucchCfg.deltaShift = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "deltaShift", 
         &(cfg->pucchCfg.deltaShift));
   cfg->pucchCfg.cyclicShift = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cyclicShift", 
         &(cfg->pucchCfg.cyclicShift));
   rgAccCb.cp = 0; /* Cyclic prefix Normal */
   rgAccCb.deltaPucchShift = cfg->pucchCfg.deltaShift;
   rgAccCb.nCsAn           = cfg->pucchCfg.cyclicShift;
   rgAccCb.n2RB            = cfg->pucchCfg.resourceSize;   
   /* Reading SRS Configuration Information */
   cfg->srsCfg.isSrsCfgSetup = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsCfgPrdEnum", 
         &(cfg->srsCfg.srsCfgPrdEnum));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsBwEnum", 
         &(srsBwEnum));
   cfg->srsCfg.srsBwEnum = (RgrSrsBwCfg)srsBwEnum;
#ifdef LTE_TDD
   cfg->srsCfg.srsSubFrameCfg=1;
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "srsSubFrameCfg", 
         &(cfg->srsCfg.srsSubFrameCfg));

   /* Reading Rach Configuration Information */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "preambleFormat",
         &(cfg->rachCfg.preambleFormat));
   cfg->rachCfg.raWinSize = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "raWinSize",
         &(cfg->rachCfg.raWinSize));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "raOccSize",
         &(cfg->rachCfg.raOccasion.size));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "sfnEnum",
         &(cfg->rachCfg.raOccasion.sfnEnum));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON,
         "raOccSubFrameNum", cfg->rachCfg.raOccasion.subFrameNum, &num);
   cfg->rachCfg.maxMsg3Tx = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg3Tx",
         &(cfg->rachCfg.maxMsg3Tx));
   cfg->rachCfg.numRaPreamble = 60; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRaPreamble",
         &(cfg->rachCfg.numRaPreamble));
   cfg->rachCfg.sizeRaPreambleGrpA = 20;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sizeRaPreambleGrpA",
         &(cfg->rachCfg.sizeRaPreambleGrpA));
   cfg->rachCfg.msgSizeGrpA = 12;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "msgSizeGrpA",
         &(cfg->rachCfg.msgSizeGrpA));
   if (cfg->bwCfg.ulTotalBw <= 26)
   {
      cfg->rachCfg.prachResource = 0;
   }
   else
   {
      cfg->rachCfg.prachResource = 20;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachResource",
         &(cfg->rachCfg.prachResource));
   /*  Copy above RachInfo to RgAcCb and Include rgac_acc.x for rgAcCb accessing
    *  here*/
   /* Changes for CR timer implementation*/
#ifdef RGR_V1 
   cfg->rachCfg.contResTmr = 40;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "contResTmr",
         &(cfg->rachCfg.contResTmr));
#endif

   cmMemcpy((U8 *)&rgAccCb.acRachCfg, (U8 *)&(cfg->rachCfg), sizeof(RgAcRachCfgCb));

   if(cfg->rachCfg.preambleFormat < RG_ACC_MAX_PREAMBLE_FORMATS)
   {
      /* Storing the preamble length in acc's rach cfg cb */
      rgAccCb.acRachCfg.preambleDur =
               rgAccSchRaPrmFmtToRaPrmLenTbl[cfg->rachCfg.preambleFormat];
   }

   /* Reading Power realted Information */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "p0NominalPusch",
         &(cfg->pwrCfg.p0NominalPusch));
   cfg->pwrCfg.alpha = RGR_PWR_ALPHAALL;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "alpha",
         &(cfg->pwrCfg.alpha));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "p0NominalPucch",
         &(cfg->pwrCfg.p0NominalPucch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "deltaPreambleMsg3",
         &(cfg->pwrCfg.deltaPreambleMsg3));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchFmt3StartRnti",
         &(cfg->pwrCfg.pucchPwrFmt3.startTpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchFmt3RntiSize",
         &(cfg->pwrCfg.pucchPwrFmt3.size));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchFmt3aStartRnti",
         &(cfg->pwrCfg.pucchPwrFmt3a.startTpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchFmt3aRntiSize",
         &(cfg->pwrCfg.pucchPwrFmt3a.size));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "puschFmt3StartRnti",
         &(cfg->pwrCfg.puschPwrFmt3.startTpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "puschFmt3RntiSize",
         &(cfg->pwrCfg.puschPwrFmt3.size));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "puschFmt3aStartRnti",
         &(cfg->pwrCfg.puschPwrFmt3a.startTpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "puschFmt3aRntiSize",
         &(cfg->pwrCfg.puschPwrFmt3a.size));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "pMax",
         &(pMax));
   cfg->pMax = (S8) pMax;
   
   /* Reading PUSCh realted Information */
   cfg->puschCfg.numSubBands = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSubBands",
         &(cfg->puschCfg.numSubBands));
   cfg->puschCfg.isIntraHop = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isIntraHop",
         &(cfg->puschCfg.isIntraHop));
   cfg->puschCfg.hopOffst = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "hopOffst",
         &(cfg->puschCfg.hopOffst));

   cfg->cellModSchm = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cellModSchm", 
         &(cfg->cellModSchm));

   /* PDCCH Order Preamble Id's managed by MAC */
   cfg->macPreambleSet.pres = NOTPRSNT; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "preambleSetPres",
         &(cfg->macPreambleSet.pres));
   cfg->macPreambleSet.start = 60; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "preambleStart",
         &(cfg->macPreambleSet.start));
   cfg->macPreambleSet.size = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "preambleSize",
         &(cfg->macPreambleSet.size));
#if 0
   ret = rgAcUtlRgrfillNdmrsWrapper(cfg->bwCfg.ulTotalBw, rgAccCb.ngEnum, 
         cfg->puschSubBand.subbandStart, cfg->puschSubBand.numSubbands, 
         cfg->puschSubBand.size, cfg->puschSubBand.dmrs);
   if (ret != ROK)
      RETVALUE(CMXTA_ERR_INT);

#endif
   /* Added for sending TTI tick to RRM */
#ifdef RGR_RRM_TICK
   /* Sending one TTI to RRM per SFN */
   cfg->rrmTtiIndPrd = 1;
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rrmTtiIndPrd", &(cfg->rrmTtiIndPrd));
   rgAccCb.rrmTtiIndPrd = cfg->rrmTtiIndPrd;
#endif

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numCmnLc", &(cfg->numCmnLcs));
   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
         "cmnLcInfo", lcInfo, &num);
   for (lcCnt = 0, lcInfoCnt=0; (lcInfoCnt<num)&&(lcCnt < cfg->numCmnLcs); lcCnt++)
   {
      cfg->cmnLcCfg[lcCnt].lcId = (CmLteLcId)lcInfo[lcInfoCnt++];
      if (lcInfoCnt >= num) break;
      cfg->cmnLcCfg[lcCnt].lcType = (CmLteLcType)lcInfo[lcInfoCnt++];
      if (lcInfoCnt >= num) break;
      cfg->cmnLcCfg[lcCnt].dir = (U8)lcInfo[lcInfoCnt++];
      if (lcInfoCnt >= num) break;
      cfg->cmnLcCfg[lcCnt].dlTrchType = (CmLteTrchType)lcInfo[lcInfoCnt++];
      if (lcInfoCnt >= num) break;
      cfg->cmnLcCfg[lcCnt].ulTrchType = (CmLteTrchType)lcInfo[lcInfoCnt++];
      if (lcInfoCnt >= num) break;
   }
#ifdef LTE_TDD
   /* Reading TDD realted information */
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ulDlCfgIdx", &(cfg->ulDlCfgIdx));
   rgAccCb.ulDlCfgIdx = cfg->ulDlCfgIdx;
   cfg->spclSfCfgIdx = 0;
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "spclSfCfgIdx", &(cfg->spclSfCfgIdx));
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRsc", &(cfg->prachRscInfo.numRsc));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"freqIdxLst", freqIdxLst, &numFreqIdx);

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"sfnLst", sfnLst, &numFreqIdx);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"halfFrmLst", halfFrmLst, &numFreqIdx);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"ulStartSfIdxLst", ulStartSfIdxLst, &numFreqIdx);

   for (idx = 0; idx < numFreqIdx; idx++)
   {
      cfg->prachRscInfo.prachInfo[idx].freqIdx = freqIdxLst[idx];
      cfg->prachRscInfo.prachInfo[idx].sfn = (RgrRaSfn)sfnLst[idx];
      cfg->prachRscInfo.prachInfo[idx].halfFrm = halfFrmLst[idx];
      cfg->prachRscInfo.prachInfo[idx].ulStartSfIdx = ulStartSfIdxLst[idx];
   }
#endif /* LTE_TDD */
#ifdef LTEMAC_SPS

   cfg->spsCfg.maxSpsDlBw = 0;
   cfg->spsCfg.maxSpsUePerDlSf = 1;
   cfg->spsCfg.maxSpsUePerUlSf = 1;
   cmXtaXmlGetVal(tcCb,spCb->childStep,CMXTA_ATTRIB_U8,"DLSPSMaxBw",
      &(cfg->spsCfg.maxSpsDlBw));
   cmXtaXmlGetVal(tcCb,spCb->childStep,CMXTA_ATTRIB_U8,"maxSpsUePerDlSf",
      &(cfg->spsCfg.maxSpsUePerDlSf));
   cmXtaXmlGetVal(tcCb,spCb->childStep,CMXTA_ATTRIB_U8,"maxSpsUePerUlSf",
      &(cfg->spsCfg.maxSpsUePerUlSf));
#endif 
   cfg->t300TmrVal = 400;
   cmXtaXmlGetVal(tcCb,spCb->childStep,CMXTA_ATTRIB_U16,"t300TmrVal",                                                              &(cfg->t300TmrVal));
   /* LTE_ADV_FLAG_REMOVED_START */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrFeatureAbs",
         &(cfg->rgrLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isAbsEnabled",
         &(cfg->rgrLteAdvCfg.absCfg.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "absPatternType",
         &(cfg->rgrLteAdvCfg.absCfg.absPatternType));
/* Anshika - Load periodicity */
   cfg->rgrLteAdvCfg.absCfg.absLoadPeriodicity = 200;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "absLoadPeriodicity",
           &(cfg->rgrLteAdvCfg.absCfg.absLoadPeriodicity));

   idx1 = 0;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern1", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern2", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern3", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern4", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrFeatureAbs", /* VENKI::duplicate read - already there under AIRSPAN_LTE_ADV */
         &(cfg->rgrLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isSfrEnabled",
         &(cfg->rgrLteAdvCfg.sfrCfg.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellEdgeStartRb",
         &(cfg->rgrLteAdvCfg.sfrCfg.cellEdgeRbRange.startRb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellEdgeEndRb",
         &(cfg->rgrLteAdvCfg.sfrCfg.cellEdgeRbRange.endRb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellCenterPower",
         &(cfg->rgrLteAdvCfg.sfrCfg.pwrThreshold.pLow));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellEdgePower",
         &(cfg->rgrLteAdvCfg.sfrCfg.pwrThreshold.pHigh));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrFeatureAbs", /* VENKI::duplicate read - already there under AIRSPAN_LTE_ADV */
         &(cfg->rgrLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isDsfrEnabled",
         &(cfg->rgrLteAdvCfg.dsfrCfg.status));
   /* LTE_ADV_FLAG_REMOVED_END */

   cfg->isDynCfiEnb = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDynCfiEnb",
         &(cfg->isDynCfiEnb));
   cfg->csgParamCfg.minDlResNonCsg = 10;
   cfg->csgParamCfg.minUlResNonCsg = 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "minDlResNonCsg",
         &(cfg->csgParamCfg.minDlResNonCsg));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "minUlResNonCsg",
         &(cfg->csgParamCfg.minUlResNonCsg));

   /* MultiInstance change */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "macInst",  &(macInst));
   cfg->macInst = macInst;

   cfg->lteUCfg.isLaaCell = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isLaaCell",  &(cfg->lteUCfg.isLaaCell));


   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcUtlRgrBuildCellCfgReq */

/**
 * @brief XTA  Utility function to build up a default set
 *             of PFS CQI priority tables for cell config
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildPfsDefDlCqiPrioTbl
 *     
 *     Utility function to build up a default set of CQI priority
 *     tables for PFS in the cell config.
 *     
 *  @param[in]  *cfgReq 
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgAcUtlRgrBuildPfsDefDlCqiPrioTbl
(
RgrCfgReqInfo  *cfgReq
)
#else
PRIVATE Void rgAcUtlRgrBuildPfsDefDlCqiPrioTbl(cfgReq)
RgrCfgReqInfo *cfgReq;
#endif
{
   RgrEnbPfs  *pfs;
   //int            i;

   TRC2(rgAcUtlRgrBuildPfsDefDlCqiPrioTbl);
 
   pfs   = &cfgReq->u.cfgInfo.u.schedEnbCfg.dlSchInfo.dlPfs;
   /* Read from XML */

   RETVOID;
} /*rgAcUtlRgrBuildPfsDefDlCqiPrioTbl */


#if 0
/**
 * @brief XTA  Utility function to build up a default set
 *             of PFS LCG priority tables for cell config
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildPfsDefUlLcgPrioTbl
 *     
 *     Utility function to build up a default set of priority
 *     tables for PFS in the cell config.
 *     
 *  @param[in]  *cfgReq 
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgAcUtlRgrBuildPfsDefUlLcgPrioTbl
(
RgrCfgReqInfo  *cfgReq
)
#else
PRIVATE Void rgAcUtlRgrBuildPfsDefUlLcgPrioTbl(cfgReq)
RgrCfgReqInfo *cfgReq;
#endif
{
   RgrCellUlPfs  *pfs;
   int            i;

   TRC2(rgAcUtlRgrBuildPfsDefUlLcgPrioTbl);
 
   pfs   = &cfgReq->u.cfgInfo.u.cellCfg.ulSchInfo.cellUlPfs;
   for (i = 0; i < 3; ++i)
   {
      pfs->lcgPrios[i] = 3 + 3 * (2 - i);
   }

   RETVOID;
} /*rgAcUtlRgrBuildPfsDefUlLcgPrioTbl */
#endif
/*
*  
*       Fun:  rgAcUtlRgrBuildUeCfgReq
*  
*       Desc:  Utility Function to Build Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildUeCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildUeCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrUeCfg    *cfg;
   U8          ueId = 0;
   S16         ret;
#ifdef RGR_CQI_REPT
   U8          pushNCqi = 0;
#endif

#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
   RgAcDlPwrCntrlInfo *dlpcInfo;
#endif
#ifdef TFU_UPGRADE 
   S16        pA = -1;
#endif

#ifdef LTEMAC_SPS
   U8 num;
#endif
   TRC2(rgAcUtlRgrBuildUeCfgReq)
 
   cfg   = &(cfgReq->u.cfgInfo.u.ueCfg);

   CMXTA_ZERO(cfg , sizeof (RgrUeCfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_UE_CFG;
  
   /* Filling Defaul Cell Id "3" */
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   /* Reading UeId from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", 
         &(ueId));
   /* XXX: crnti initialized during acc Init? */
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;
   
#ifdef LTE_ADV
   cfg->accessStratumRls = RGR_REL_8;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "accessStratumRls",  &(cfg->accessStratumRls));
   rgAccCb.acUeCb[ueId].accessStratumRls = cfg->accessStratumRls;
   rgAccCb.acUeCb[ueId].cellId = cfg->cellId;
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti", 
         &(cfg->crnti));
/* Changes for MIMO feature addition */
#ifdef LTEMAC_MIMO
   /* Reading state of transmission Mode transition from XML */
   cfg->txMode.tmTrnstnState = RGR_TXMODE_RECFG_CMPLT;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "tmTrnstnState", 
         &(cfg->txMode.tmTrnstnState));
#endif
   /* Reading UE Transmission  mode from XML */
   cfg->txMode.txModeEnum = RGR_UE_TM_1; 
   cfg->txMode.pres = TRUE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32,"txModeEnum", 
         &(cfg->txMode.txModeEnum));

   /* Reading UE Downlink CQI Information from XML */
   cfg->ueDlCqiCfg.aprdCqiCfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "aprdModeEnumPres", 
         &(cfg->ueDlCqiCfg.aprdCqiCfg.pres));

   cfg->ueDlCqiCfg.aprdCqiCfg.aprdModeEnum = RGR_APRD_CQI_MOD12;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "aprdModeEnum", 
         &(cfg->ueDlCqiCfg.aprdCqiCfg.aprdModeEnum));
/* Added changes of TFU_UPGRADE */
#ifndef TFU_UPGRADE   
   
   cfg->ueDlCqiCfg.prdCqiCfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "prdModeEnumPres", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.pres));
   
   cfg->ueDlCqiCfg.prdCqiCfg.prdModeEnum = RGR_PRD_CQI_MOD10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdModeEnum", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.prdModeEnum));
   
   cfg->ueDlCqiCfg.prdCqiCfg.prdicityEnum = RGR_CQI_PRD_MS2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdicityEnum", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.prdicityEnum));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subframeOffst", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.subframeOffst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "cqiOffst", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.cqiOffst));

   cfg->ueDlCqiCfg.prdCqiCfg.k = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "k", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.k));
   cfg->ueDlCqiCfg.prdCqiCfg.cqiPmiCfgIdx = 9;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPmiCfgIdx", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.cqiPmiCfgIdx));

   cfg->ueDlCqiCfg.prdCqiCfg.pres = TRUE;
#else /*else of TFU_UPGRADE */
cfg->ueDlCqiCfg.prdCqiCfg.type= FALSE;
 cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "prdCqiCfg.type", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.type));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.cqiPResIdx = 500; 
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPResIdx", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.cqiPResIdx));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.cqiPCfgIdx = 315; 
 cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPCfgIdx", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.cqiPCfgIdx));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.cqiRepType = 1; 
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cqiRepType", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.cqiRepType));       
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.k = 1; 
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "K", 
          &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.k));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.riEna = FALSE; 
 cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "riEna", 
         &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.riEna));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.riCfgIdx = 500; 
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "riCfgIdx", 
       &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.riCfgIdx));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.sANCQI = TRUE; 
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sANCQI", 
       &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.sANCQI));
cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.prdModeEnum = RGR_PRD_CQI_MOD10; 
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdModeEnum", 
       &(cfg->ueDlCqiCfg.prdCqiCfg.cqiSetup.prdModeEnum));
cfg->srsCfg.type = FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "srsCfgPres", 
        &(cfg->srsCfg.type));
cfg->srsCfg.srsSetup.srsCfgIdx = 157;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "srsCfgIdx", 
        &(cfg->srsCfg.srsSetup.srsCfgIdx));
cfg->srsCfg.srsSetup.srsBw = RGR_ULSRS_BW_0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsBw", 
         &(cfg->srsCfg.srsSetup.srsBw));
cfg->srsCfg.srsSetup.srsHopBw= RGR_ULSRS_HOP_BW_0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsHopBw", 
         &(cfg->srsCfg.srsSetup.srsHopBw));
cfg->srsCfg.srsSetup.cycShift= RGR_ULSRS_CYSHIFT_0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "cycShift", 
         &(cfg->srsCfg.srsSetup.cycShift));
cfg->srsCfg.srsSetup.duration = TRUE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "duration", 
         &(cfg->srsCfg.srsSetup.duration));
cfg->srsCfg.srsSetup.sANSrs= TRUE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sANSrs", 
         &(cfg->srsCfg.srsSetup.sANSrs));
cfg->srsCfg.srsSetup.txComb= 0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "txComb", 
         &(cfg->srsCfg.srsSetup.txComb));
cfg->srsCfg.srsSetup.fDomPosi = 1;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "fDomPosi", 
         &(cfg->srsCfg.srsSetup.fDomPosi));
cfg->srCfg.type= FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "srCfgPres", 
        &(cfg->srCfg.type));
cfg->srCfg.srSetup.srResIdx = 45;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "srResIdx", 
        &(cfg->srCfg.srSetup.srResIdx));
cfg->srCfg.srSetup.srCfgIdx = 75;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "srCfgIdx", 
        &(cfg->srCfg.srSetup.srCfgIdx));
#endif /*TFU_UPGRADE */
   /* Reading UE Uplink HARQ Information from XML */
   cfg->ueUlHqCfg.maxUlHqTx = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlHqTx", 
         &(cfg->ueUlHqCfg.maxUlHqTx));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "deltaHqOffst", 
         &(cfg->ueUlHqCfg.deltaHqOffst));

   /* Reading Uplink Power related Information from xml */
   cfg->ueUlPwrCfg.uePuschPwr.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "puschTpcRntiPres", 
         &(cfg->ueUlPwrCfg.uePuschPwr.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "puschtpcRnti", 
         &(cfg->ueUlPwrCfg.uePuschPwr.tpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "uePuschPwrIdx", 
         &(cfg->ueUlPwrCfg.uePuschPwr.idx));
   
   cfg->ueUlPwrCfg.uePucchPwr.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "pucchTpcRntiPres", 
         &(cfg->ueUlPwrCfg.uePucchPwr.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchtpcRnti", 
         &(cfg->ueUlPwrCfg.uePucchPwr.tpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "uePucchPwrIdx", 
         &(cfg->ueUlPwrCfg.uePucchPwr.idx));

   cfg->ueUlPwrCfg.isAccumulated = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isAccumulated", 
         &(cfg->ueUlPwrCfg.isAccumulated));
   
   cfg->ueUlPwrCfg.isDeltaMCSEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDeltaMCSEnabled", 
         &(cfg->ueUlPwrCfg.isDeltaMCSEnabled));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "p0UePusch", 
         &(cfg->ueUlPwrCfg.p0UePusch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "p0UePucch", 
         &(cfg->ueUlPwrCfg.p0UePucch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pSRSOffset", 
         &(cfg->ueUlPwrCfg.pSRSOffset));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trgCqi",
         &(cfg->ueUlPwrCfg.trgCqi));

   /* QOS information from xml */
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlAmbr", 
         &(cfg->ueQosCfg.dlAmbr));
   if (ret != CMXTA_ERR_NO_VALUE)
      cfg->ueQosCfg.ambrPres = TRUE;

   cfg->ueQosCfg.ueBr = 0xfffffffd; /*Default UeBr */
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueBr", 
         &(cfg->ueQosCfg.ueBr));
   
   cfg->ueCatEnum = CM_LTE_UE_CAT_1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ueCatEnum", 
         &(cfg->ueCatEnum));

   rgAccCb.acUeCb[ueId].ueCatEnum = cfg->ueCatEnum;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "taTmr", 
         &(cfg->ueTaTmrCfg.taTmr));

   /* default parameters for periodic BSR timer*/
   cfg->ueBsrTmrCfg.isPrdBsrTmrPres = TRUE;
   cfg->ueBsrTmrCfg.prdBsrTmr       = 10;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "prdBsrTmr", 
         &(cfg->ueBsrTmrCfg.prdBsrTmr));

   if (cfg->ueTaTmrCfg.taTmr)
   {
      cfg->ueTaTmrCfg.pres = TRUE;
   }
#ifdef LTEMAC_DRX
   /* New feature validations FROM DRX.*/ 
   cfg->ueDrxCfg.isDrxEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDrxEnabled", 
         &(cfg->ueDrxCfg.isDrxEnabled));
#ifdef LTEMAC_R9
   cfg->ueDrxCfg.cqiMask.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cqiMask", 
         &(cfg->ueDrxCfg.cqiMask.pres));
   if ( cfg->ueDrxCfg.cqiMask.pres == TRUE )
   {
      cfg->ueDrxCfg.cqiMask.val = RGR_DRX_SETUP;
   }
   
#endif/*LTEMAC_R9*/
   cfg->ueDrxCfg.drxOnDurTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxOnDurTmr", 
         &(cfg->ueDrxCfg.drxOnDurTmr));
   cfg->ueDrxCfg.drxInactvTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "drxInactvTmr", 
         &(cfg->ueDrxCfg.drxInactvTmr));
   cfg->ueDrxCfg.drxRetxTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxRetxTmr", 
         &(cfg->ueDrxCfg.drxRetxTmr));

   cfg->ueDrxCfg.drxLongCycleOffst.longDrxCycle = 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "longDrxCycle", 
         &(cfg->ueDrxCfg.drxLongCycleOffst.longDrxCycle));

   cfg->ueDrxCfg.drxLongCycleOffst.drxStartOffst= 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "drxStartOffst", 
         &(cfg->ueDrxCfg.drxLongCycleOffst.drxStartOffst));
   
   cfg->ueDrxCfg.drxShortDrx.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isShortDrxPrsnt", 
         &(cfg->ueDrxCfg.drxShortDrx.pres));
   cfg->ueDrxCfg.drxShortDrx.shortDrxCycle = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "shortDrxCycle", 
         &(cfg->ueDrxCfg.drxShortDrx.shortDrxCycle));
   cfg->ueDrxCfg.drxShortDrx.drxShortCycleTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxShortCycleTmr", 
         &(cfg->ueDrxCfg.drxShortDrx.drxShortCycleTmr));

#endif /*LTEMAC_DRX*/

   cfg->isTtiBundlEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isTtiBundlEnabled", 
         &(cfg->isTtiBundlEnabled));

   /* Reading Ack/Nack Information from xml  */
   cfg->ueAckNackCfg.isAckNackEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isAckNackEnabled", 
         &(cfg->ueAckNackCfg.isAckNackEnabled));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchAckNackRep", 
         &(cfg->ueAckNackCfg.pucchAckNackRep));
   cfg->ueAckNackCfg.ackNackRepFactor = RGR_ACKNACK_REPFACT_N2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ackNackRepFactor", 
         &(cfg->ueAckNackCfg.ackNackRepFactor));

   /* Reading Measurement Gap Information from xml */
   cfg->ueMesGapCfg.isMesGapEnabled= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isMesGapEnabled", 
         &(cfg->ueMesGapCfg.isMesGapEnabled));
   cfg->ueMesGapCfg.gapPrd = 40;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "gapPrd", 
         &(cfg->ueMesGapCfg.gapPrd));
   cfg->ueMesGapCfg.gapOffst = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "gapOffst", 
         &(cfg->ueMesGapCfg.gapOffst));
   /* Store gapPrd and Offset */
   rgAccCb.acUeCb[ueId].gapPrd = cfg->ueMesGapCfg.gapPrd; 
   rgAccCb.acUeCb[ueId].gapOffst = cfg->ueMesGapCfg.gapOffst; 

   /* Reading UE Capabilty information from xnl */
   cfg->ueCapCfg.pwrClass= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pwrClass", 
         &(cfg->ueCapCfg.pwrClass));
   cfg->ueCapCfg.intraSfFeqHop = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "intraSfFeqHop", 
         &(cfg->ueCapCfg.intraSfFeqHop));
   cfg->ueCapCfg.resAloocType1= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "resAloocType1", 
         &(cfg->ueCapCfg.resAloocType1));
   cfg->ueCapCfg.simCqiAckNack= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "simCqiAckNack", 
         &(cfg->ueCapCfg.simCqiAckNack));
#ifdef LTEMAC_MIMO
   /* Reading UE TxAntSel from XML */
   cfg->ueCapCfg.txAntSel = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "txAntSel", 
         &(cfg->ueCapCfg.txAntSel));
   
#endif
   cfg->ueCodeBookRstCfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "codeBookResPrsnt", 
         &(cfg->ueCodeBookRstCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pmiBitMap0", 
         &(cfg->ueCodeBookRstCfg.pmiBitMap[0]));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pmiBitMap1", 
         &(cfg->ueCodeBookRstCfg.pmiBitMap[1]));

   cfg->dedPreambleId.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "dedPrmblPrsnt", 
         &(cfg->dedPreambleId.pres));
   if(cfg->dedPreambleId.pres ==TRUE)
   {
      cfg->crnti = rgAccCb.dedCrnti;
      rgAccCb.dedCrnti++;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti", 
         &(cfg->crnti));
      /* Create ACC CB with this ded CRNTI */
      rgAccCb.acUeCb[rgAccCb.nmbOfUes].crnti = cfg->crnti;
      cmLListInit(&(rgAccCb.acUeCb[rgAccCb.nmbOfUes].staIndLst));
      rgAccCb.nmbOfUes++;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dedPrmblId", 
         &(cfg->dedPreambleId.val));

#ifdef LTE_TDD
   /* Reading TDD related information */
   cfg->ackNackModeEnum = RGR_TDD_ACKNACK_MODE_BUNDL;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ackNackModeEnum", 
         &(cfg->ackNackModeEnum));
#endif /* LTE_TDD */
#ifdef LTEMAC_MIMO
   cfg->ulTxAntSel.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ulTxAntSelPres", 
         &(cfg->ulTxAntSel.pres));
   cfg->ulTxAntSel.selType = RGR_UE_TX_ANT_OPENLOOP;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "selType", 
         &(cfg->ulTxAntSel.selType));
#endif
#ifdef TFU_UPGRADE
   cfg->puschDedCfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "betaOffsetPres", 
         &(cfg->puschDedCfg.pres));
   cfg->puschDedCfg.bACKIdx= 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bACKIdx", 
         &(cfg->puschDedCfg.bACKIdx));
   cfg->puschDedCfg.bRIIdx= 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bRIIdx", 
         &(cfg->puschDedCfg.bRIIdx));
   cfg->puschDedCfg.bCQIIdx= 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bCQIIdx", 
         &(cfg->puschDedCfg.bCQIIdx));
   
   rgAccCb.acUeCb[ueId].puschDedCfg = cfg->puschDedCfg;
#endif /* TFU_UPGRADE */

#ifdef LTEMAC_SPS
/**
* @brief SPS parameters  
*/
cfg->ueSpsCfg.spsRnti = RG_ACC_SPSRNTI;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "SPSRnti", 
         &(cfg->ueSpsCfg.spsRnti));
   rgAccCb.acUeCb[ueId].SPScrnti=cfg->ueSpsCfg.spsRnti;
/**
*  DL config
*/
cfg->ueSpsCfg.dlSpsCfg.isDlSpsEnabled = FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "DLSPSEnFlag", 
      &(cfg->ueSpsCfg.dlSpsCfg.isDlSpsEnabled));

if(cfg->ueSpsCfg.dlSpsCfg.isDlSpsEnabled)
{
   cfg->ueSpsCfg.dlSpsCfg.numPucchVal = RG_ACC_NUM_PUCCH_VALUES;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "NumPucchVal", 
         &(cfg->ueSpsCfg.dlSpsCfg.numPucchVal));

   cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[0] = 2;
   cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[1] = 3;
   cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[2] = 5;
   cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[3] = 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "n1PucchVal0", 
         &(cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[0]));  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "n1PucchVal1", 
         &(cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[1]));  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "n1PucchVal2", 
         &(cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[2]));  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "n1PucchVal3", 
         &(cfg->ueSpsCfg.dlSpsCfg.n1PucchVal[3])); 
   rgAccCb.acUeCb[ueId].numPucchVal = cfg->ueSpsCfg.dlSpsCfg.numPucchVal;
 
   cfg->ueSpsCfg.dlSpsCfg.numSpsHqProc = RG_ACC_NUM_SPS_HARQ_PROC;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "NumSPSProc", 
         &(cfg->ueSpsCfg.dlSpsCfg.numSpsHqProc));

   cfg->ueSpsCfg.dlSpsCfg.dlSpsPrdctyEnum = RGR_SPS_PRD_20SF;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "DLSPSSchIntrv", 
         &(cfg->ueSpsCfg.dlSpsCfg.dlSpsPrdctyEnum));

   /* REVANTH_FIX */
   cfg->ueSpsCfg.dlSpsCfg.explicitRelCnt = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "DLSpsExpltRelCnt", 
         &(cfg->ueSpsCfg.dlSpsCfg.explicitRelCnt));

   rgAccCb.acUeCb[ueId].dlSpsPrd     = cfg->ueSpsCfg.dlSpsCfg.dlSpsPrdctyEnum;
   rgAccCb.acUeCb[ueId].NumSPSProc = cfg->ueSpsCfg.dlSpsCfg.numSpsHqProc;

}
/**
*UL config
*/
cfg->ueSpsCfg.ulSpsCfg.isUlSpsEnabled = FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ULSPSEnFlag", 
   &(cfg->ueSpsCfg.ulSpsCfg.isUlSpsEnabled));

if(cfg->ueSpsCfg.ulSpsCfg.isUlSpsEnabled)
{
   
   cfg->ueSpsCfg.ulSpsCfg.implicitRelCnt = RGR_SPS_E2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ULSPSimpRls", 
      &(cfg->ueSpsCfg.ulSpsCfg.implicitRelCnt));
#ifdef LTE_TDD
   cfg->ueSpsCfg.ulSpsCfg.twoIntervalCfg = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ULSPSTwoIntConf", 
      &(cfg->ueSpsCfg.ulSpsCfg.twoIntervalCfg));
#endif
   cfg->ueSpsCfg.ulSpsCfg.pwrCfgPres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ULSPSPwrCfgPres", 
      &(cfg->ueSpsCfg.ulSpsCfg.pwrCfgPres));

   cfg->ueSpsCfg.ulSpsCfg.pwrCfg.p0NominalPuschVal= RG_ACC_P0_NOMINAL_PUSCH_VAL;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "ULSPSP0NomPUSCHVal", 
      &(cfg->ueSpsCfg.ulSpsCfg.pwrCfg.p0NominalPuschVal));

   cfg->ueSpsCfg.ulSpsCfg.pwrCfg.p0UePuschVal = RG_ACC_P0_UE_PUSCH_VAL;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "ULSPSP0UePUSCHVal", 
   &(cfg->ueSpsCfg.ulSpsCfg.pwrCfg.p0UePuschVal));

   cfg->ueSpsCfg.ulSpsCfg.ulSpsPrdctyEnum = RGR_SPS_PRD_20SF;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ULSPSSchIntrv", 
   &(cfg->ueSpsCfg.ulSpsCfg.ulSpsPrdctyEnum));

#if 0  /* REVANTH_FIX */
   cfg->ueSpsCfg.ulSpsCfg.packetSize = RG_ACC_SPS_PACKET_SIZE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ULSPSPcktSize", 
   &(cfg->ueSpsCfg.ulSpsCfg.packetSize));
   
   
   rgAccCb.acUeCb[ueId].ulPacketSize = cfg->ueSpsCfg.ulSpsCfg.packetSize;
#endif

   /* Anshika SPS */
   cfg->ueSpsCfg.ulSpsCfg.isLcSRMaskEnab = TRUE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "LcSRMask", 
   &(cfg->ueSpsCfg.ulSpsCfg.isLcSRMaskEnab));


   cfg->ueSpsCfg.ulSpsCfg.lcCnt = RG_ACC_SPS_NUM_LOG_CHNLS;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ULSPSLcCnt", 
   &(cfg->ueSpsCfg.ulSpsCfg.lcCnt));


   cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[0].isSpsEnabled=TRUE;
   cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[0].lcId=4;
      cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
                    "ULSPSLcId",  &(cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[0].lcId), &num);
   {
       U8 idx, ulSpsLcId[RGR_MAX_SPS_LC]; 

      cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
                    "ULSPSLcId", ulSpsLcId, &(cfg->ueSpsCfg.ulSpsCfg.lcCnt));

      for( idx=0; idx<cfg->ueSpsCfg.ulSpsCfg.lcCnt; idx++ )
      {
          cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[idx].isSpsEnabled = TRUE;
          cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[idx].lcId = ulSpsLcId[idx];
      }
 
      if(cfg->ueSpsCfg.ulSpsCfg.lcCnt == 0)
      {
         cfg->ueSpsCfg.ulSpsCfg.lcCnt = RG_ACC_SPS_NUM_LOG_CHNLS;
         cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[0].isSpsEnabled=TRUE;
         cfg->ueSpsCfg.ulSpsCfg.spsLcInfo[0].lcId=4;
      } 
   } 
}
#endif /* LTEMAC_SPS */
#ifdef LTEMAC_HDFDD
   cfg->isHdFddEnbld = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "hdfdd", &(cfg->isHdFddEnbld));
   rgAccCb.acUeCb[ueId].isHdFddEnbld = cfg->isHdFddEnbld;
#endif /* ifdef LTEMAC_HDFDD */
#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
   dlpcInfo =  &(rgAccCb.acUeCb[ueId].dlpcInfo);
#ifdef RGR_CQI_REPT
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pushNCqiVal", &pushNCqi);
   if(pushNCqi)
   {
      cfg->ueCqiReptCfg.numColltdCqiRept= pushNCqi;

      /* Keep copy of what has been sent */
      dlpcInfo->cqiReptCount = pushNCqi;
   }
   else
   {
      cfg->ueCqiReptCfg.numColltdCqiRept = 0;
      /* Keep copy of what has been sent */
      dlpcInfo->cqiReptCount = 0;
      dlpcInfo->cqiSentCount = 0;

   }
#endif /* End ofRGR_CQI_REPT */
#endif /* End ofRGR_CQI_REPT */
#ifdef TFU_UPGRADE 
   pA = -1;
   cfg->uePdschDedCfg.uepACfg.pAPrsnt= FALSE;
   /* cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "pAVal", &(cfg->uePdschDedCfg.uepACfg.pA)); */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "pAVal", &(pA));
   if (!(pA < 0))
   {
      cfg->uePdschDedCfg.uepACfg.pAPrsnt= TRUE;
      switch(pA)
      {
         case RGAC_UE_DLPWRCNTRL_PA_DB_6:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_6;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB_4dot77:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_4DOT77;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB_3:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_3;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB_1dot77:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_1DOT77;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB0:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB0;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB1:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB1;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB2:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB2;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB3;
            break;
         default:
            CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildUeCfgReq: Invalid parameters"
               " passed for pA\n"));
      }
      dlpcInfo->pA = cfg->uePdschDedCfg.uepACfg.pA;
   }
#endif
/* LTE_ADV_FLAG_REMOVED_START */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isUeCellEdge",
         &(cfg->ueLteAdvCfg.isUeCellEdge));
/* LTE_ADV_FLAG_REMOVED_END */
/* Anshika - fix for ABS UE BO Order */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pres",
         &(cfg->ueLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isAbsUe",
         &(cfg->ueLteAdvCfg.isAbsUe));

   RETVOID;
} /*rgAcUtlRgrBuildUeCfgReq */

EXTERN LchData lchData[9];
EXTERN Bool isPfsSim;
EXTERN U8   numLc;


/*
*  
*       Fun:  rgAcUtlRgrBuildLchCfgReq
*  
*       Desc:  Utility Function to Build Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildLchCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildLchCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrLchCfg *cfg;
   U8        ueId = 0;
   static    U8  lcIdx = 0; 
   RgAcUeCb        *ueCb=NULLP;

   TRC2(rgAcUtlRgrBuildLchCfgReq)
 
   cfg   = &(cfgReq->u.cfgInfo.u.lchCfg);

   CMXTA_ZERO(cfg , sizeof (RgrLchCfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_LCH_CFG;
   
   /* Default value for Cell id */
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&ueId);
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;

   if(isPfsSim)
   {
       cfg->lcId = lchData[lcIdx].lcId;
       cfg->lcType = lchData[lcIdx].lcType;
       cfg->dlInfo.dlQos.qci = lchData[lcIdx].qci;
       cfg->dlInfo.dlQos.gbr = lchData[lcIdx].gbr;
       cfg->dlInfo.dlQos.mbr = lchData[lcIdx].mbr;

       ueCb = &rgAccCb.acUeCb[ueId];
       ueCb->lcs[cfg->lcId].gbr = cfg->dlInfo.dlQos.gbr;
       ueCb->lcs[cfg->lcId].mbr = cfg->dlInfo.dlQos.mbr;

       lcIdx++;

       if(numLc == lcIdx)
       {
          lcIdx = 0;
       }   
   }
   else
   { 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",
            &(cfg->lcId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcType",
            &(cfg->lcType));

      /* Default value of qci set as 5.
       * qci of 5 has priority 0 which was the earlier dflt val*/
      cfg->dlInfo.dlQos.qci = 5; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlQci",
            &(cfg->dlInfo.dlQos.qci));
      cfg->dlInfo.dlQos.gbr = 2560;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlGbr",
            &(cfg->dlInfo.dlQos.gbr));
      cfg->dlInfo.dlQos.mbr = 8192;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlMbr",
            &(cfg->dlInfo.dlQos.mbr));
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlTrchType",
         &(cfg->dlInfo.dlTrchType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ulQci",
         &(cfg->ulLchQciInfo.qci));
   cfg->ulLchQciInfo.lcId = cfg->lcId;
   cfg->ulLchQciInfo.lcgId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",
         &(cfg->ulLchQciInfo.lcgId));
#ifdef LTE_L2_MEAS
   cfg->lcgId = cfg->ulLchQciInfo.lcgId;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",
            &(cfg->lcgId));
#endif
#ifdef LTEMAC_SPS
   
   cfg->dlInfo.dlSpsCfg.isSpsEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "DLSPSLchEnabFlag",
         &(cfg->dlInfo.dlSpsCfg.isSpsEnabled));
   if(cfg->dlInfo.dlSpsCfg.isSpsEnabled)
   {
     // cfg->dlInfo.dlSpsCfg.packetSize= RG_ACC_SPS_PACKET_SIZE;
      //cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "DLSPSLchPktSize",
      //      &(cfg->dlInfo.dlSpsCfg.packetSize));

      //cfg->dlInfo.dlSpsCfg.packetPrdcty = RG_ACC_SPS_PACKET_PRD;
     // cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "DLSPSLchPktPrd",
        //    &(cfg->dlInfo.dlSpsCfg.packetPrdcty));
      
     // cfg->dlInfo.dlSpsCfg.explicitRelCnt = RG_ACC_SPS_EXPLCT_REL_CNT;
    //  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
     //    "DLSPSLchExpltRelCnt",&(cfg->dlInfo.dlSpsCfg.explicitRelCnt));
   }
#endif /*(defined(LTEMAC_SPS))*/

   RETVOID;
} /*rgAcUtlRgrBuildLchCfgReq */
/*
*  
*       Fun:  rgAcUtlRgrBuildLcgCfgReq
*  
*       Desc:  Utility Function to Build Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildLcgCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildLcgCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrLcgCfg *cfg;
   U8        ueId = 0;
   U8        isGbrPresent = FALSE; 
#ifdef LTE_L2_MEAS
   U8        qciList[RGR_MAX_LC_PER_LCG];
   U8        lcIdList[RGR_MAX_LC_PER_LCG];
   U8        idx;
#endif

   TRC2(rgAcUtlRgrBuildLcgCfgReq)
 
   cfg   = &(cfgReq->u.cfgInfo.u.lcgCfg);

   CMXTA_ZERO(cfg , sizeof (RgrLchCfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_LCG_CFG;
   
   /* Default value for Cell id */
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&ueId);
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",
         &(cfg->ulInfo.lcgId));
#ifdef LTE_L2_MEAS
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch",
         &(cfg->ulInfo.numLch));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON, "lcId",
         &lcIdList, &(cfg->ulInfo.numLch));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON, "qci",
         &qciList, &(cfg->ulInfo.numLch));
   for(idx = 0; idx < cfg->ulInfo.numLch; idx++)
   {
      cfg->ulInfo.lchUlCfg[idx].lcId = lcIdList[idx];
      cfg->ulInfo.lchUlCfg[idx].qci  = qciList[idx];
      if(cfg->ulInfo.lchUlCfg[idx].qci < 5 && cfg->ulInfo.lchUlCfg[idx].qci > 0)
      {
        isGbrPresent = TRUE; 
      }
   }
#endif
   if(isGbrPresent)
   {
      cfg->ulInfo.gbr = 2560; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "gbr",
         &(cfg->ulInfo.gbr));
      cfg->ulInfo.mbr = 3560;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "mbr",
         &(cfg->ulInfo.mbr));
   }
   else
   {
      cfg->ulInfo.gbr = 0; 
      cfg->ulInfo.mbr = 0;
   }

   RETVOID;
} /*rgAcUtlRgrBuildLcgCfgReq */


/**
 * @brief XTA  Utility function to read cell re configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildCellReCfgReq
 *     
 *     Utility function to read cell re configuration values from XML and
 *     fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlRgrBuildCellReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC S16 rgAcUtlRgrBuildCellReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrCellRecfg  *cfg;
   S16           ret = ROK;
   U8            numSubFrameNum;
   U32           srsBwEnum=0;
   /* LTE_ADV_FLAG_REMOVED_START */
   U8 idx;
   U8 absPattern[10];
   U8 absNum;
   U8 idx1;
   /* LTE_ADV_FLAG_REMOVED_END */

   TRC2(rgAcUtlRgrBuildCellReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.cellRecfg);

   CMXTA_ZERO(cfg , sizeof (RgrCellCfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.recfgInfo.recfgType = RGAC_RGR_CELL_CFG;

   /* Assging Default Cell Id "3" */
   cfg->cellId = RG_ACC_CELLID; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "recfgType", 
         &(cfg->recfgTypes));

   /* Reading Timing infor for re configuration from xml */
   cfg->recfgActvTime.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "actvTimePres",&(cfg->recfgActvTime.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "actvTimesfn", 
         &(cfg->recfgActvTime.actvTime.sfn));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "actvTimesf", 
         &(cfg->recfgActvTime.actvTime.subframe));
  
   /* reading Downlink HARQ infor for Re configuration from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxDlHqTx",
         &(cfg->dlHqRecfg.maxDlHqTx));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg4HqTx",
         &(cfg->dlHqRecfg.maxMsg4HqTx));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cfi",
         &(cfg->cfiRecfg.cfi));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trgCqi",
         &(cfg->trgUlCqi.trgCqi));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "bcchPchCodeRate",
         &(cfg->dlCmnCodeRate.bcchPchRaCodeRate));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pdcchCodeRate",
         &(cfg->dlCmnCodeRate.pdcchCodeRate));
   cfg->dlCmnCodeRate.ccchCqi = 3;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlCcchCqi",
         &(cfg->dlCmnCodeRate.ccchCqi));
   
   cfg->puschSubBand.subbandStart = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subbandStart",
         &(cfg->puschSubBand.subbandStart));
   cfg->puschSubBand.numSubbands = 8;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSubbands",
         &(cfg->puschSubBand.numSubbands));
   cfg->puschSubBand.size = 6;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "size",
         &(cfg->puschSubBand.size));
   /* Calling utility to fill ndmrs */
   ret = rgAcUtlRgrfillNdmrsWrapper( 50, rgAccCb.ngEnum, cfg->puschSubBand.subbandStart,
         cfg->puschSubBand.numSubbands, cfg->puschSubBand.size, cfg->puschSubBand.dmrs);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   cfg->ulCmnCodeRate.ccchCqi = 8;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ccchCqi",
         &(cfg->ulCmnCodeRate.ccchCqi));

   cfg->pucchRecfg.resourceSize = 20;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "resourceSize",&(cfg->pucchRecfg.resourceSize));
   cfg->pucchRecfg.n1PucchAn = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "n1PucchAn",&(cfg->pucchRecfg.n1PucchAn));
   cfg->pucchRecfg.deltaShift = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "deltaShift",&(cfg->pucchRecfg.deltaShift));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cyclicShift",&(cfg->pucchRecfg.cyclicShift));

   cfg->srsRecfg.isSrsCfgSetup = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsCfgPrdEnum",&(cfg->srsRecfg.srsCfgPrdEnum));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsBwEnum", 
         &(srsBwEnum));
   cfg->srsRecfg.srsBwEnum = (RgrSrsBwCfg)srsBwEnum;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "srsSubFrameCfg",
         &(cfg->srsRecfg.srsSubFrameCfg));
#ifdef LTE_TDD
   cfg->srsRecfg.srsSubFrameCfg = 1;
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "preambleFormat",
         &(cfg->rachRecfg.preambleFormat));
   cfg->rachRecfg.raWinSize = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "raWinSize",
         &(cfg->rachRecfg.raWinSize));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "size",
         &(cfg->rachRecfg.raOccasion.size));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "sfnEnum",
         &(cfg->rachRecfg.raOccasion.sfnEnum));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON,"raOccSubFrameNum", cfg->rachRecfg.raOccasion.subFrameNum, &numSubFrameNum);
   cfg->rachRecfg.maxMsg3Tx = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg3Tx",
         &(cfg->rachRecfg.maxMsg3Tx));
   cfg->rachRecfg.numRaPreamble = 60;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRaPreamble",
         &(cfg->rachRecfg.numRaPreamble));
   cfg->rachRecfg.sizeRaPreambleGrpA = 12;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sizeRaPreambleGrpA",
         &(cfg->rachRecfg.sizeRaPreambleGrpA));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "msgSizeGrpA",
         &(cfg->rachRecfg.msgSizeGrpA));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachResource",
         &(cfg->rachRecfg.prachResource));
   
   /*  Copy above RachInfo to RgAcCb and Include rgac_acc.x for rgAcCb accessing
    *  here*/
   cmMemcpy((U8 *)&rgAccCb.acRachCfg, (U8 *)&(cfg->rachRecfg), sizeof(RgAcRachCfgCb));

   /* Reading DLFS Information for Reconfiguration */
   cfg->dlfsRecfg.isDlFreqSel = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isDlFreqSel", 
         &(cfg->dlfsRecfg.isDlFreqSel));

#ifdef RGR_SI_SCH
   cfg->siReCfg.siWinSize = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siWinSize", 
         &(cfg->siReCfg.siWinSize));

   cfg->siReCfg.retxCnt = 3;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siRetxCnt", 
         &(cfg->siReCfg.retxCnt));

   /*ccpu00115364 MOD changed modPrd default value to lowest configurable val*/
   /* solaris fixes for g++ compilation */
   /* added the type cast RgrModPeriodicity below */

   cfg->siReCfg.modPrd = (RgrModPeriodicity)64;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "modPrd", 
         &(cfg->siReCfg.modPrd));
   cfg->siReCfg.numSi = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSi", 
         &(cfg->siReCfg.numSi));
   cfg->siReCfg.siPeriodicity[0] = (RgrSiPeriodicity)8;
   cfg->siReCfg.siPeriodicity[1] = (RgrSiPeriodicity)8;
   cfg->siReCfg.siPeriodicity[2] = (RgrSiPeriodicity)16;
   cfg->siReCfg.siPeriodicity[3] = (RgrSiPeriodicity)8;
#endif
   /* LTE_ADV_FLAG_REMOVED_START */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrFeatureAbs",
         &(cfg->rgrLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isAbsEnabled",
         &(cfg->rgrLteAdvCfg.absCfg.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "absPatternType",
           &(cfg->rgrLteAdvCfg.absCfg.absPatternType));
   
   idx1 = 0;
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern1", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern2", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern3", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         CMXTA_SEP_COLON,"absPattern4", absPattern, &absNum);
   for(idx = 0;idx<absNum;idx++)
   {
       cfg->rgrLteAdvCfg.absCfg.absPattern[idx1] = absPattern[idx];
       idx1++;
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrFeatureAbs", /* VENKI::duplicate read - already there under AIRSPAN_LTE_ADV */
         &(cfg->rgrLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isSfrEnabled",
         &(cfg->rgrLteAdvCfg.sfrCfg.status));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellEdgeStartRb",
         &(cfg->rgrLteAdvCfg.sfrCfg.cellEdgeRbRange.startRb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellEdgeEndRb",
         &(cfg->rgrLteAdvCfg.sfrCfg.cellEdgeRbRange.endRb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellCenterPower",
         &(cfg->rgrLteAdvCfg.sfrCfg.pwrThreshold.pLow));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellEdgePower",
         &(cfg->rgrLteAdvCfg.sfrCfg.pwrThreshold.pHigh));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rgrFeatureAbs", /* VENKI::duplicate read - already there under AIRSPAN_LTE_ADV */
         &(cfg->rgrLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isDsfrEnabled",
         &(cfg->rgrLteAdvCfg.dsfrCfg.status));

   cfg->isDynCfiEnb = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDynCfiEnb",
         &(cfg->isDynCfiEnb));

   /* LTE_ADV_FLAG_REMOVED_END */
   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcUtlRgrBuildCellReCfgReq*/
#ifdef LTE_ADV
/*
*  
*       Fun:  rgAcUtlRgrBuildSCellAddCfg
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PRIVATE Void rgAcUtlRgrBuildSCellAddCfg 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PRIVATE Void rgAcUtlRgrBuildSCellAddCfg(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   RgrUePrdDlCqiCfg  *cqiCfg;
   RgrUeRecfg    *cfg;
   RgrUeSecCellInfo *secCellInfo;
   RgrUeSecCellCfg *ueSCellDedCfg;
   U8             numSCells = 1,num=1;
   U8             sCellIdx[RGR_MAX_SCELL_PER_UE];
   U16            sCellId[RGR_MAX_SCELL_PER_UE];
   U8             ueId      = 0;
   U8             testName[2];
   U32            deActTmrVal = 90;
   Txt            parseStr[200];
   S16            ret1 = CMXTA_ERR_NONE;
   RgrUeUlPwrDedSCellCfg *ueSCellUlDedPwrCfg;

   TRC2(rgAcUtlRgrBuildSCellAddCfg)

   cfg   = &(cfgReq->u.recfgInfo.u.ueRecfg);

   cfg->ueRecfgTypes |= RGR_UE_SCELL_ADD_RECFG;
   secCellInfo = &cfg->ueSCellCfgInfo;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",
         &(ueId));

   cfg->newCrnti = rgAccCb.acUeCb[ueId].crnti;
   cfg->oldCrnti = cfg->newCrnti;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSCells", 
         &(numSCells));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "deActTmrVal", 
         &(deActTmrVal));
   
   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, "name", 
         testName, &num);
   printf("\n tstName is %d\n",testName[0]);

   secCellInfo->numSCells = numSCells;
   
   RGAC_XML_GET_VALLIST(parseStr, "sCellIdx",":",   sCellIdx,  U8, num);

   if(num < numSCells)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildSCellAddCfg():num scell idx < num scells\n"));
   }

   RGAC_XML_GET_VALLIST(parseStr, "sCellId",":",   sCellId,  U16, num);

   if(num < numSCells)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildSCellAddCfg():num scell id < num scells\n"));
   }

   for(U8 idx = 0; idx < numSCells; idx++)
   { /* Fill the params for each scell to 
        be added for this UE*/
      ueSCellDedCfg = &secCellInfo->ueSCellDedCfg[idx];
      ueSCellDedCfg->sCellIdx = sCellIdx[idx];
      ueSCellDedCfg->sCellId  = sCellId[idx];
      /* TODO::need to fill cqi cfgs during 
       * respective sprints*/
      /* setting to rlease in spring 2*/
      if (deActTmrVal == 0xffffffff)
      {
         /* Don't Configure deactivation timer */
         ueSCellDedCfg->sCellDeActTmr.pres = NOTPRSNT;
         ueSCellDedCfg->sCellDeActTmr.val = 0;
      }
      else
      {
         ueSCellDedCfg->sCellDeActTmr.pres = PRSNT_NODEF;
         ueSCellDedCfg->sCellDeActTmr.val = deActTmrVal;
      }

      ueSCellDedCfg->ueSCellDlCqiCfg.aprdCqiCfg.pres = FALSE;
      
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "aprdModeEnumPres", 
            &(ueSCellDedCfg->ueSCellDlCqiCfg.aprdCqiCfg.pres ));
      if(ueSCellDedCfg->ueSCellDlCqiCfg.aprdCqiCfg.pres) 
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "aprdModeEnum", 
               &(ueSCellDedCfg->ueSCellDlCqiCfg.aprdCqiCfg.aprdModeEnum));

      }
      ueSCellDedCfg->ueSCellDlCqiCfg.prdCqiCfg.type  = 0;

      ueSCellDedCfg->uePdschDedCfg.uepACfg.pAPrsnt = FALSE;

      ueSCellDedCfg->txMode.pres = TRUE;
      ueSCellDedCfg->txMode.txModeEnum = 3;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "txModeEnum", 
         &(ueSCellDedCfg->txMode.txModeEnum));
   
      

      cqiCfg = &ueSCellDedCfg->ueSCellDlCqiCfg.prdCqiCfg;
      cqiCfg->type = FALSE;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "prdCqiCfg.type", 
            &(cqiCfg->type));
      cqiCfg->cqiSetup.cqiPResIdx = 500; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPResIdx", 
            &(cqiCfg->cqiSetup.cqiPResIdx));
      cqiCfg->cqiSetup.cqiPCfgIdx = 315; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPCfgIdx", 
            &(cqiCfg->cqiSetup.cqiPCfgIdx));
      cqiCfg->cqiSetup.cqiRepType = 1; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cqiRepType", 
            &(cqiCfg->cqiSetup.cqiRepType));       
      cqiCfg->cqiSetup.k = 1; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "k", 
            &(cqiCfg->cqiSetup.k));
      cqiCfg->cqiSetup.riEna = FALSE; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "riEna", 
            &(cqiCfg->cqiSetup.riEna));
      cqiCfg->cqiSetup.riCfgIdx = 500; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "riCfgIdx", 
            &(cqiCfg->cqiSetup.riCfgIdx));
      cqiCfg->cqiSetup.sANCQI = TRUE; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sANCQI", 
            &(cqiCfg->cqiSetup.sANCQI));
      cqiCfg->cqiSetup.prdModeEnum = RGR_PRD_CQI_MOD10; 
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdModeEnum", 
            &(cqiCfg->cqiSetup.prdModeEnum));

      /* Adding Fixed UL config values : Default */
      ueSCellDedCfg->isUlCaEnabled = FALSE;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isUlCaEnabled", 
            &(ueSCellDedCfg->isUlCaEnabled));

      ueSCellUlDedPwrCfg = &ueSCellDedCfg->ueSCellUlDedPwrCfg;
      ueSCellUlDedPwrCfg->isAccumulated = TRUE;
      ueSCellUlDedPwrCfg->isDeltaMCSEnabled = FALSE;
      ueSCellUlDedPwrCfg->p0UePusch = -13;
      ueSCellUlDedPwrCfg->pSRSOffset = 0;
   }

   RETVOID;
}

/*
*  
*       Fun:  rgAcUtlRgrBuildSCellRelCfg
*  
*       Desc:  Utility Function to Build Scell Release Cfg
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PRIVATE Void rgAcUtlRgrBuildSCellRelCfg 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PRIVATE Void rgAcUtlRgrBuildSCellRelCfg(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   U8             numSCells = 1,num=1;
   U8             sCellIdx[RGR_MAX_SCELL_PER_UE];
   U16            sCellId[RGR_MAX_SCELL_PER_UE];
   U8             ueId      = 0;
   U16            cellId;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cellId));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",
         &(ueId));

   struct rgrUeScellRel *ueScellRelCfg = NULLP;
   cfgReq->action = RGR_DELETE;
   cfgReq->u.delInfo.delType = RGR_SCELL_UE_CFG;
   ueScellRelCfg = &cfgReq->u.delInfo.u.ueScellRel;
   ueScellRelCfg->cellId = cellId;
   ueScellRelCfg->crnti = rgAccCb.acUeCb[ueId].crnti;
   ueScellRelCfg->ueDelTypes        = RGR_UE_SCELL_DEL_RECFG; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSCells", &(numSCells));
   ueScellRelCfg->ueSCellRelCfgInfo.numSCells = numSCells;

   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, "sCellIdx", 
         sCellIdx, &num);

   if(num < numSCells)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildSCellAddCfg():num scell idx < num scells\n"));
   }

   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON, "sCellId", 
         sCellId, &num);

   if(num < numSCells)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildSCellAddCfg():num scell id < num scells\n"));
   }

   for(U8 idx = 0; idx < numSCells; idx++)
   {
      ueScellRelCfg->ueSCellRelCfgInfo.ueSCellRelDedCfg[idx].sCellIdx = sCellIdx[idx];
      ueScellRelCfg->ueSCellRelCfgInfo.ueSCellRelDedCfg[idx].sCellId = sCellId[idx];
   }
   RETVOID;
}
   /* local variables */
 
#endif
/*
*  
*       Fun:  rgAcUtlRgrBuildUeReCfgReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildUeReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildUeReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrUeRecfg    *cfg;
   U8            oldUeId = 0;
   U8            newUeId = 0;
   Bool          ueCatRecfgPres = FALSE;
#ifdef RGR_CQI_REPT
   S16          pushNCqi = -1;
#endif
#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
   RgAcDlPwrCntrlInfo *dlpcInfo;
#endif
   U8        ueId = 0;
#ifdef TFU_UPGRADE
   S16      pA = -1;
#endif
   S16           ret;
#ifdef LTEMAC_SPS
   U8 num = 0;
#endif
#ifdef LTE_ADV
   Bool addSCellCfgPres = FALSE;
   Bool relSCellCfgPres = FALSE;
#endif


   TRC2(rgAcUtlRgrBuildUeReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.ueRecfg);
   cfg->ueRecfgTypes = 0;

   CMXTA_ZERO(cfg , sizeof (RgrUeRecfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.recfgInfo.recfgType = RGAC_RGR_UE_CFG;
 
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "oldUeId",
         &(oldUeId));
   cfg->oldCrnti = rgAccCb.acUeCb[oldUeId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "oldcrnti",
         &(cfg->oldCrnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "newUeId",
         &(newUeId));
 
#ifdef LTE_ADV
   cfg->accessStratumRls = RGR_REL_8;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "accessStratumRls",  &(cfg->accessStratumRls));
   rgAccCb.acUeCb[oldUeId].accessStratumRls = cfg->accessStratumRls;
   rgAccCb.acUeCb[newUeId].accessStratumRls = cfg->accessStratumRls;
   rgAccCb.acUeCb[oldUeId].cellId = cfg->cellId;
   rgAccCb.acUeCb[newUeId].cellId = cfg->cellId;
   
   cfg->aprdDlCqiRecfg.triggerSet1 = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "triggerSet1", 
         &(cfg->aprdDlCqiRecfg.triggerSet1));
   cfg->aprdDlCqiRecfg.triggerSet2 = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "triggerSet2", 
         &(cfg->aprdDlCqiRecfg.triggerSet2));
   cfg->sCellAckN1ResCfg.pucchFormatType = 255;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "pucchFormatType", 
         &(cfg->sCellAckN1ResCfg.pucchFormatType));

   if (RG_SCH_UCI_FORMAT1B_CS == cfg->sCellAckN1ResCfg.pucchFormatType)
   {
      cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON, 
            "n1PUCCHValTB1", cfg->sCellAckN1ResCfg.sCellAckN1ResTb1, &num);
      cfg->sCellAckN1ResCfg.sCellAckN1ResTb1Count = num;


      cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON, 
            "n1PUCCHValTB2", cfg->sCellAckN1ResCfg.sCellAckN1ResTb2, &num);
      cfg->sCellAckN1ResCfg.sCellAckN1ResTb2Count = num;

      for (U8 idx=0;idx < 4 ;idx++)
      {
         rgAccCb.acUeCb[newUeId].sCellAckN1ResCfg.sCellAckN1ResTb1[idx] = 
               cfg->sCellAckN1ResCfg.sCellAckN1ResTb1[idx];
         rgAccCb.acUeCb[newUeId].sCellAckN1ResCfg.sCellAckN1ResTb2[idx] = 
               cfg->sCellAckN1ResCfg.sCellAckN1ResTb2[idx];
      }
      cfg->ueRecfgTypes |= RGR_UE_SCELL_PUCCH_RECFG;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isSCellAdd", 
         &(addSCellCfgPres));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isSCellRel", 
         &(relSCellCfgPres));

   if(addSCellCfgPres  == TRUE)
   {
      rgAcUtlRgrBuildSCellAddCfg(tcCb,spCb,cfgReq);
      RETVOID;
   }
   if(relSCellCfgPres  == TRUE)
   {
      rgAcUtlRgrBuildSCellRelCfg(tcCb,spCb,cfgReq);
      RETVOID;
   }
   
#endif 
   
#ifdef LTEMAC_SPS
   if((newUeId != oldUeId)&& (rgAccCb.acUeCb[oldUeId].SPScrnti))
   {
      rgAccCb.acUeCb[newUeId].SPScrnti = rgAccCb.acUeCb[oldUeId].SPScrnti;
   }  
#endif     

   cfg->newCrnti = rgAccCb.acUeCb[newUeId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newcrnti",
         &(cfg->newCrnti));
   cfg->ueRecfgTypes = RGAC_RGR_UE_TXMODE_RECFG;
#ifdef RGR_V2
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "UeReCfgType",&(cfg->ueRecfgTypes));
#else
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "UeReCfgType",&(cfg->ueRecfgTypes));
#endif
#ifdef LTEMAC_MIMO
   /* Reading state of transmission Mode transition from XML */
   cfg->txMode.tmTrnstnState = RGR_TXMODE_RECFG_CMPLT;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "tmTrnstnState", 
         &(cfg->txMode.tmTrnstnState));
#endif
/* Changes for UE Category Reconfiguration feature addition */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ueCatRecfgPres", 
         &ueCatRecfgPres);
   if (ueCatRecfgPres)
   {
      cfg->ueCatEnum = CM_LTE_UE_CAT_1;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ueCatEnum", 
            &(cfg->ueCatEnum));
   }
   
   cfg->txMode.txModeEnum = RGR_UE_TM_1; 
   cfg->txMode.pres = TRUE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "txModeEnum", 
         &(cfg->txMode.txModeEnum));
   cfg->aprdDlCqiRecfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "aprdModeEnumPres", 
         &(cfg->aprdDlCqiRecfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "aprdModeEnum", 
         &(cfg->aprdDlCqiRecfg.aprdModeEnum));
#ifndef TFU_UPGRADE 
   cfg->prdDlCqiRecfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "prdModeEnumPres", 
         &(cfg->prdDlCqiRecfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdModeEnum", 
         &(cfg->prdDlCqiRecfg.prdModeEnum));
   cfg->prdDlCqiRecfg.prdicityEnum = RGR_CQI_PRD_MS2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdicityEnum", 
         &(cfg->prdDlCqiRecfg.prdicityEnum));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subframeOffst", 
         &(cfg->prdDlCqiRecfg.subframeOffst));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "cqiOffst", 
         &(cfg->prdDlCqiRecfg.cqiOffst));
   
   cfg->prdDlCqiRecfg.k = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "k", 
         &(cfg->prdDlCqiRecfg.k));
   cfg->prdDlCqiRecfg.cqiPmiCfgIdx = 9;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPmiCfgIdx", 
         &(cfg->prdDlCqiRecfg.cqiPmiCfgIdx));
#else /*TFU_UPGRADE */
  cfg->cqiCfg.type = FALSE;
 cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "prdCqiCfg.type", 
         &(cfg->cqiCfg.type));
cfg->cqiCfg.cqiSetup.cqiPResIdx = 500; 
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPResIdx", 
         &(cfg->cqiCfg.cqiSetup.cqiPResIdx));
cfg->cqiCfg.cqiSetup.cqiPCfgIdx = 315; 
 cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cqiPCfgIdx", 
         &(cfg->cqiCfg.cqiSetup.cqiPCfgIdx));
cfg->cqiCfg.cqiSetup.cqiRepType = 1; 
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cqiRepType", 
         &(cfg->cqiCfg.cqiSetup.cqiRepType));       
cfg->cqiCfg.cqiSetup.k = 1; 
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "k", 
          &(cfg->cqiCfg.cqiSetup.k));
cfg->cqiCfg.cqiSetup.riEna = FALSE; 
 cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "riEna", 
         &(cfg->cqiCfg.cqiSetup.riEna));
cfg->cqiCfg.cqiSetup.riCfgIdx = 500; 
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "riCfgIdx", 
       &(cfg->cqiCfg.cqiSetup.riCfgIdx));
cfg->cqiCfg.cqiSetup.sANCQI = TRUE; 
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sANCQI", 
       &(cfg->cqiCfg.cqiSetup.sANCQI));
cfg->cqiCfg.cqiSetup.prdModeEnum = RGR_PRD_CQI_MOD10; 
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "prdModeEnum", 
       &(cfg->cqiCfg.cqiSetup.prdModeEnum));
cfg->srsCfg.type = FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "srsCfgPres", 
        &(cfg->srsCfg.type));
cfg->srsCfg.srsSetup.srsCfgIdx = 26;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "srsCfgIdx", 
        &(cfg->srsCfg.srsSetup.srsCfgIdx));
cfg->srsCfg.srsSetup.srsBw = RGR_ULSRS_BW_0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsBw", 
         &(cfg->srsCfg.srsSetup.srsBw));
cfg->srsCfg.srsSetup.srsHopBw= RGR_ULSRS_HOP_BW_0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "srsHopBw", 
         &(cfg->srsCfg.srsSetup.srsHopBw));
cfg->srsCfg.srsSetup.cycShift= RGR_ULSRS_CYSHIFT_0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "cycShift", 
         &(cfg->srsCfg.srsSetup.cycShift));
cfg->srsCfg.srsSetup.duration = TRUE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "duration", 
         &(cfg->srsCfg.srsSetup.duration));
cfg->srsCfg.srsSetup.sANSrs= TRUE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sANSrs", 
         &(cfg->srsCfg.srsSetup.sANSrs));
cfg->srsCfg.srsSetup.txComb= 0;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "txComb", 
         &(cfg->srsCfg.srsSetup.txComb));
cfg->srsCfg.srsSetup.fDomPosi = 1;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "fDomPosi", 
         &(cfg->srsCfg.srsSetup.fDomPosi));
cfg->srCfg.type= FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "srCfgPres", 
        &(cfg->srCfg.type));
cfg->srCfg.srSetup.srResIdx = 45;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "srResIdx", 
        &(cfg->srCfg.srSetup.srResIdx));
cfg->srCfg.srSetup.srCfgIdx = 45;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "srCfgIdx", 
        &(cfg->srCfg.srSetup.srCfgIdx));
#endif
   cfg->ueUlHqRecfg.maxUlHqTx = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlHqTx", 
         &(cfg->ueUlHqRecfg.maxUlHqTx));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "deltaHqOffst", 
         &(cfg->ueUlHqRecfg.deltaHqOffst));

   /* By default  cfg->ueQosRecfg.ambrPres was added as
    * TRUE now changed depending on value read from XML*/
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlAmbr", 
         &(cfg->ueQosRecfg.dlAmbr));
   if (ret != CMXTA_ERR_NO_VALUE)
      cfg->ueQosRecfg.ambrPres = TRUE;

   cfg->ueQosRecfg.ueBr = 0xfffffffd;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueBr", 
         &(cfg->ueQosRecfg.ueBr));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "taTmr", 
         &(cfg->ueTaTmrRecfg.taTmr));
   if (cfg->ueTaTmrRecfg.taTmr)
   {
      cfg->ueRecfgTypes = cfg->ueRecfgTypes | RGR_UE_TATMR_RECFG;
      cfg->ueTaTmrRecfg.pres = TRUE;
   }
   
   /* Note: some names changed */
   cfg->ueUlPwrRecfg.uePuschPwr.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "puschTpcRntiPres", 
         &(cfg->ueUlPwrRecfg.uePuschPwr.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "puschtpcRnti", 
         &(cfg->ueUlPwrRecfg.uePuschPwr.tpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "uePuschPwrIdx", 
         &(cfg->ueUlPwrRecfg.uePuschPwr.idx));

   cfg->ueUlPwrRecfg.uePucchPwr.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "pucchTpcRntiPres", 
         &(cfg->ueUlPwrRecfg.uePucchPwr.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchtpcRnti",
         &(cfg->ueUlPwrRecfg.uePucchPwr.tpcRnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "uePucchPwrIdx", 
         &(cfg->ueUlPwrRecfg.uePucchPwr.idx));

   cfg->ueUlPwrRecfg.isAccumulated = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isAccumulated", 
         &(cfg->ueUlPwrRecfg.isAccumulated));

   cfg->ueUlPwrRecfg.isDeltaMCSEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDeltaMCSEnabled", 
         &(cfg->ueUlPwrRecfg.isDeltaMCSEnabled));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "p0UePusch", 
         &(cfg->ueUlPwrRecfg.p0UePusch));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "p0UePucch", 
         &(cfg->ueUlPwrRecfg.p0UePucch));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pSRSOffset", 
         &(cfg->ueUlPwrRecfg.pSRSOffset));
   
#ifdef LTEMAC_DRX
   /* New feature validations FROM DRX.*/ 
   cfg->ueDrxRecfg.isDrxEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isDrxEnabled", 
         &(cfg->ueDrxRecfg.isDrxEnabled));
#ifdef LTEMAC_R9
   cfg->ueDrxRecfg.cqiMask.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cqiMask", 
         &(cfg->ueDrxRecfg.cqiMask.pres));

   if ( cfg->ueDrxRecfg.cqiMask.pres == TRUE )
   {
      cfg->ueDrxRecfg.cqiMask.val = RGR_DRX_SETUP;
   }
#endif/*LTEMAC_R9*/
   cfg->ueDrxRecfg.drxOnDurTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxOnDurTmr", 
         &(cfg->ueDrxRecfg.drxOnDurTmr));
   cfg->ueDrxRecfg.drxInactvTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "drxInactvTmr", 
         &(cfg->ueDrxRecfg.drxInactvTmr));
   cfg->ueDrxRecfg.drxRetxTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxRetxTmr", 
         &(cfg->ueDrxRecfg.drxRetxTmr));

   cfg->ueDrxRecfg.drxLongCycleOffst.longDrxCycle = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "longDrxCycle", 
         &(cfg->ueDrxRecfg.drxLongCycleOffst.longDrxCycle));
   cfg->ueDrxRecfg.drxLongCycleOffst.drxStartOffst= 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "drxStartOffst", 
         &(cfg->ueDrxRecfg.drxLongCycleOffst.drxStartOffst));

   cfg->ueDrxRecfg.drxShortDrx.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isShortDrxPrsnt", 
         &(cfg->ueDrxRecfg.drxShortDrx.pres));
   cfg->ueDrxRecfg.drxShortDrx.shortDrxCycle = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "shortDrxCycle", 
         &(cfg->ueDrxRecfg.drxShortDrx.shortDrxCycle));
   cfg->ueDrxRecfg.drxShortDrx.drxShortCycleTmr = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxShortCycleTmr", 
         &(cfg->ueDrxRecfg.drxShortDrx.drxShortCycleTmr));
#endif

   cfg->isTtiBundlEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isTtiBundlEnabled", 
         &(cfg->isTtiBundlEnabled));

   cfg->ueAckNackRecfg.isAckNackEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isAckNackEnabled", 
         &(cfg->ueAckNackRecfg.isAckNackEnabled));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pucchAckNackRep", 
         &(cfg->ueAckNackRecfg.pucchAckNackRep));
   cfg->ueAckNackRecfg.ackNackRepFactor = RGR_ACKNACK_REPFACT_N2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ackNackRepFactor", 
         &(cfg->ueAckNackRecfg.ackNackRepFactor));
   
   cfg->ueCapRecfg.pwrClass= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pwrClass", 
         &(cfg->ueCapRecfg.pwrClass));
   cfg->ueCapRecfg.intraSfFeqHop = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "intraSfFeqHop", 
         &(cfg->ueCapRecfg.intraSfFeqHop));
   cfg->ueCapRecfg.resAloocType1= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "resAloocType1", 
         &(cfg->ueCapRecfg.resAloocType1));
   cfg->ueCapRecfg.simCqiAckNack= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "simCqiAckNack", 
         &(cfg->ueCapRecfg.simCqiAckNack));
#ifdef LTEMAC_MIMO
   /* Reading UE TxAntSel from XML */
   cfg->ueCapRecfg.txAntSel = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "txAntSel", 
         &(cfg->ueCapRecfg.txAntSel));
#endif
   cfg->ueMeasGapRecfg.isMesGapEnabled= FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isMesGapEnabled", 
         &(cfg->ueMeasGapRecfg.isMesGapEnabled));
   cfg->ueMeasGapRecfg.gapPrd = 40;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "gapPrd", 
         &(cfg->ueMeasGapRecfg.gapPrd));
   cfg->ueMeasGapRecfg.gapOffst = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "gapOffst", 
         &(cfg->ueMeasGapRecfg.gapOffst));
   rgAccCb.acUeCb[oldUeId].gapPrd = cfg->ueMeasGapRecfg.gapPrd; 
   rgAccCb.acUeCb[oldUeId].gapOffst = cfg->ueMeasGapRecfg.gapOffst; 


   cfg->ueCodeBookRstRecfg.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "codeBookResPrsnt", 
         &(cfg->ueCodeBookRstRecfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pmiBitMap0", 
         &(cfg->ueCodeBookRstRecfg.pmiBitMap[0]));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pmiBitMap1", 
         &(cfg->ueCodeBookRstRecfg.pmiBitMap[1]));
#ifdef LTEMAC_MIMO
   cfg->ulTxAntSel.pres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ulTxAntSelPres", 
         &(cfg->ulTxAntSel.pres));
   cfg->ulTxAntSel.selType = RGR_UE_TX_ANT_OPENLOOP;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "selType", 
         &(cfg->ulTxAntSel.selType));
#endif
#ifdef LTEMAC_SPS
/**
* @brief SPS parameters   <kk>
*/

/**
*  DL config
*/
cfg->ueSpsRecfg.dlSpsCfg.isDlSpsEnabled = FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "DLSPSEnFlag", 
      &(cfg->ueSpsRecfg.dlSpsCfg.isDlSpsEnabled));

if(cfg->ueSpsRecfg.dlSpsCfg.isDlSpsEnabled)
{
   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON, "n1PUCCHVal", 
         cfg->ueSpsRecfg.dlSpsCfg.n1PucchVal, &num);

   cfg->ueSpsRecfg.dlSpsCfg.numSpsHqProc = RG_ACC_NUM_SPS_HARQ_PROC;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "NumSPSProc", 
         &(cfg->ueSpsRecfg.dlSpsCfg.numSpsHqProc));

   cfg->ueSpsRecfg.dlSpsCfg.numPucchVal = RG_ACC_NUM_PUCCH_VALUES;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "NumPucchVal", 
         &(cfg->ueSpsRecfg.dlSpsCfg.numPucchVal));


   cfg->ueSpsRecfg.dlSpsCfg.dlSpsPrdctyEnum = RGR_SPS_PRD_20SF;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "DLSPSSchIntrv", 
         &(cfg->ueSpsRecfg.dlSpsCfg.dlSpsPrdctyEnum));

   /* REVANTH_FIX */
   cfg->ueSpsRecfg.dlSpsCfg.explicitRelCnt = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "DLSpsExpltRelCnt", 
         &(cfg->ueSpsRecfg.dlSpsCfg.explicitRelCnt));

   cfg->ueSpsRecfg.spsRnti = RG_ACC_SPSRNTI;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "SPSRnti", 
         &(cfg->ueSpsRecfg.spsRnti));
   rgAccCb.acUeCb[oldUeId].SPScrnti=cfg->ueSpsRecfg.spsRnti;
}

/**
*UL config
*/
cfg->ueSpsRecfg.ulSpsCfg.isUlSpsEnabled = FALSE;
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ULSPSEnFlag", 
   &(cfg->ueSpsRecfg.ulSpsCfg.isUlSpsEnabled));

if (cfg->ueSpsRecfg.ulSpsCfg.isUlSpsEnabled)
{
   cfg->ueSpsRecfg.ulSpsCfg.implicitRelCnt = RGR_SPS_E2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ULSPSimpRls", 
      &(cfg->ueSpsRecfg.ulSpsCfg.implicitRelCnt));
#ifdef LTE_TDD
   cfg->ueSpsRecfg.ulSpsCfg.twoIntervalCfg = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ULSPSTwoIntConf", 
      &(cfg->ueSpsRecfg.ulSpsCfg.twoIntervalCfg));
#endif
   cfg->ueSpsRecfg.ulSpsCfg.pwrCfgPres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ULSPSPwrCfgPres", 
      &(cfg->ueSpsRecfg.ulSpsCfg.pwrCfgPres));

   cfg->ueSpsRecfg.ulSpsCfg.pwrCfg.p0NominalPuschVal= RG_ACC_P0_NOMINAL_PUSCH_VAL;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "ULSPSP0NomPUSCHVal", 
      &(cfg->ueSpsRecfg.ulSpsCfg.pwrCfg.p0NominalPuschVal));

   cfg->ueSpsRecfg.ulSpsCfg.pwrCfg.p0UePuschVal = RG_ACC_P0_UE_PUSCH_VAL;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S8, "ULSPSP0UePUSCHVal", 
   &(cfg->ueSpsRecfg.ulSpsCfg.pwrCfg.p0UePuschVal));

   cfg->ueSpsRecfg.ulSpsCfg.ulSpsPrdctyEnum = RGR_SPS_PRD_20SF;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ULSPSSchIntrv", 
   &(cfg->ueSpsRecfg.ulSpsCfg.ulSpsPrdctyEnum));

#if 0 /* REVANTH_FIX */
   cfg->ueSpsRecfg.ulSpsCfg.packetSize = RG_ACC_SPS_PACKET_SIZE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ULSPSPcktSize", 
         &(cfg->ueSpsRecfg.ulSpsCfg.packetSize));
#endif

/* Anshika SPS */
   cfg->ueSpsRecfg.ulSpsCfg.isLcSRMaskEnab = TRUE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "LcSRMask", 
   &(cfg->ueSpsRecfg.ulSpsCfg.isLcSRMaskEnab));


   cfg->ueSpsRecfg.ulSpsCfg.lcCnt = RG_ACC_SPS_NUM_LOG_CHNLS;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ULSPSLcCnt", 
   &(cfg->ueSpsRecfg.ulSpsCfg.lcCnt));

   cfg->ueSpsRecfg.ulSpsCfg.spsLcInfo[0].lcId = 4;
   cfg->ueSpsRecfg.ulSpsCfg.spsLcInfo[0].isSpsEnabled = TRUE;
   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
                       "ULSPSLcId", &(cfg->ueSpsRecfg.ulSpsCfg.spsLcInfo[0].lcId), &num);
   if(cfg->ueSpsRecfg.ulSpsCfg.lcCnt < num )
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildUeReCfgReq(): Invalid parameters"
               " passed.. \n  Please Recheck the parameters \n"));
   }
   
   cfg->ueSpsRecfg.spsRnti = RG_ACC_SPSRNTI;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "SPSRnti", 
         &(cfg->ueSpsRecfg.spsRnti));
   rgAccCb.acUeCb[oldUeId].SPScrnti=cfg->ueSpsRecfg.spsRnti;
}
#endif /* LTEMAC_SPS */
#ifdef LTEMAC_HDFDD
   cfg->isHdFddEnbld = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "hdfdd", &(cfg->isHdFddEnbld));
   rgAccCb.acUeCb[newUeId].isHdFddEnbld = cfg->isHdFddEnbld;
#endif /* ifdef LTEMAC_HDFDD */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&ueId);
#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
   dlpcInfo =  &(rgAccCb.acUeCb[ueId].dlpcInfo);
#ifdef RGR_CQI_REPT
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "pushNCqiVal", &pushNCqi);
   if (!(pushNCqi < 0))
   {
#ifdef RGR_V2
      cfg->ueRecfgTypes = cfg->ueRecfgTypes | RGR_UE_CQIREPT_RECFG;
#endif
      cfg->ueCqiReptCfg.numColltdCqiRept= (U8)pushNCqi;

      /* Keep copy of what has been sent */
      dlpcInfo->cqiReptCount = (U8)pushNCqi;
      if(!pushNCqi)
      {
         dlpcInfo->cqiSentCount = (U8)pushNCqi;
      }
   }
   else
   {
      cfg->ueCqiReptCfg.numColltdCqiRept= 0;
   }
#endif
#endif /* End ofRGR_CQI_REPT */
#ifdef TFU_UPGRADE
   cfg->uePdschDedCfg.uepACfg.pAPrsnt= FALSE;
 /*   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "pACfg", &pACfg);
   if (pACfg)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "pA", &(cfg->uePdschDedCfg.uepACfg.pA));
      cfg->uePdschDedCfg.uepACfg.pAPrsnt = TRUE;
      dlpcInfo->pA = cfg->uePdschDedCfg.uepACfg.pA;
   } */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "pAVal", &(pA));
#ifdef RGR_V2
   if(!(pA < 0))
   {
      cfg->ueRecfgTypes = cfg->ueRecfgTypes | RGR_UE_PA_RECFG;
      cfg->uePdschDedCfg.uepACfg.pAPrsnt= TRUE;
      switch(pA)
      {
         case RGAC_UE_DLPWRCNTRL_PA_DB_6:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_6;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB_4dot77:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_4DOT77;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB_3:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_3;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB_1dot77:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB_1DOT77;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB0:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB0;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB1:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB1;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB2:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB2;
            break;
         case RGAC_UE_DLPWRCNTRL_PA_DB:
            cfg->uePdschDedCfg.uepACfg.pA = RGRUE_DLPWRCNTRL_PA_DB3;
            break;
         default:
            CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildUeCfgReq: Invalid parameters"
                     " passed for pA\n"));
      }
      dlpcInfo->pA = cfg->uePdschDedCfg.uepACfg.pA;
   }
#endif
#endif
/* LTE_ADV_FLAG_REMOVED_START */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isUeCellEdge",
         &(cfg->ueLteAdvCfg.isUeCellEdge));
   cfg->ueLteAdvCfg.pres = RGR_SFR;
   /* LTE_ADV_FLAG_REMOVED_END */
   /* Fix for ABS UE BO Order */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pres",
         &(cfg->ueLteAdvCfg.pres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isAbsUe",
         &(cfg->ueLteAdvCfg.isAbsUe));
   /* By default UE is not a member of CSG */
   cfg->csgMmbrSta = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "csgMmbrSta",
         &(cfg->csgMmbrSta));

   RETVOID;
} /*rgAcUtlRgrBuildUeReCfgReq */
/*
*  
*       Fun:  rgAcUtlRgrBuildLchReCfgReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildLchReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildLchReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrLchRecfg *cfg;
   U8          ueId = 0;

   TRC2(rgAcUtlRgrBuildLchReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.lchRecfg);

   CMXTA_ZERO(cfg , sizeof (RgrLchRecfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_LCH_CFG;
   /* Assiging Default Value to cell Id "3" */
   cfg->cellId = RG_ACC_CELLID; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", 
         &(ueId));
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",
         &(cfg->crnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",
         &(cfg->lcId));
   
#ifdef LTEMAC_SPS  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgTypes",
         &(cfg->recfgTypes));

#endif
   cfg->dlRecfg.dlQos.qci = 5; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlQci",
         &(cfg->dlRecfg.dlQos.qci));
   cfg->dlRecfg.dlQos.gbr = 2560;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlGbr",
         &(cfg->dlRecfg.dlQos.gbr));
   cfg->dlRecfg.dlQos.mbr = 8192;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlMbr",
         &(cfg->dlRecfg.dlQos.mbr));
#ifdef LTEMAC_SPS
   
   cfg->dlRecfg.dlSpsRecfg.isSpsEnabled = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "DLSPSLchEnabFlag",
         &(cfg->dlRecfg.dlSpsRecfg.isSpsEnabled));
   #if 0
   if(cfg->dlRecfg.dlSpsRecfg.isSpsEnabled)
   {
      cfg->dlRecfg.dlSpsRecfg.packetSize= RG_ACC_SPS_PACKET_SIZE;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "DLSPSLchPktSize",
            &(cfg->dlRecfg.dlSpsRecfg.packetSize));

      cfg->dlRecfg.dlSpsRecfg.packetPrdcty = RG_ACC_SPS_PACKET_PRD;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "DLSPSLchPktPrd",
            &(cfg->dlRecfg.dlSpsRecfg.packetPrdcty));
      
      cfg->dlRecfg.dlSpsRecfg.explicitRelCnt = RG_ACC_SPS_EXPLCT_REL_CNT;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
         "DLSPSLchExpltRelCnt",&(cfg->dlRecfg.dlSpsRecfg.explicitRelCnt));
   }
   #endif
#endif /*(defined(LTEMAC_SPS))*/
   
   RETVOID;
} /*rgAcUtlRgrBuildLchReCfgReq */

/*
*  
*       Fun:  rgAcUtlRgrBuildLcgReCfgReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildLcgReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildLcgReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrLcgRecfg *cfg;
   U8          ueId = 0;
#if 0
//#ifdef LTE_L2_MEAS
   U8        qciList[RGR_MAX_LC_PER_LCG];
   U8        lcIdList[RGR_MAX_LC_PER_LCG];
   U8        idx;
#endif


   TRC2(rgAcUtlRgrBuildLcgReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.lcgRecfg);

   CMXTA_ZERO(cfg , sizeof (RgrLchRecfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_RGR_LCG_CFG;
   /* Assiging Default Value to cell Id "3" */
   cfg->cellId = RG_ACC_CELLID; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", 
         &(ueId));
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",
         &(cfg->crnti));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",
         &(cfg->ulRecfg.lcgId));

#if 0
//#ifdef LTE_L2_MEAS
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch",
         &(cfg->ulRecfg.numLch));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON, "lcId",
         &lcIdList, &(cfg->ulRecfg.numLch));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,CMXTA_SEP_COLON, "qci",
         &qciList, &(cfg->ulRecfg.numLch));
   for(idx = 0; idx < cfg->ulRecfg.numLch; idx++)
   {
      cfg->ulRecfg.lchUlCfg[idx].lcId = lcIdList[idx];
      cfg->ulRecfg.lchUlCfg[idx].qci  = qciList[idx];
   }
#endif

   RETVOID;
} /*rgAcUtlRgrBuildLchReCfgReq */


/*
*  
*       Fun:  rgAcUtlRgrBuildDelReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildDelReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildDelReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrDel *cfg;
   U8     ueId = 0;

   TRC2(rgAcUtlRgrBuildDelReq)
 
   cfg   = &(cfgReq->u.delInfo);

   CMXTA_ZERO(cfg , sizeof (RgrDel));
   cfg->delType = RGAC_RGR_CELL_CFG;

  /*----------- Fill General Configuration Parameters ---------*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "DelType",&(cfg->delType));

   if (cfg->delType == RGAC_RGR_CELL_CFG)
   {
      cfg->u.cellDel.cellId = RG_ACC_CELLID;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->u.cellDel.cellId));
   }
   else if (cfg->delType == RGAC_RGR_UE_CFG)
   {
      cfg->u.ueDel.cellId = RG_ACC_CELLID;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->u.ueDel.cellId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&(ueId));
      if (ueId > RG_ACC_MAX_UE)
         cfg->u.ueDel.crnti = 0;
      else
         cfg->u.ueDel.crnti = rgAccCb.acUeCb[ueId].crnti;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",&(cfg->u.ueDel.crnti));
   }
   else if (cfg->delType == RGAC_RGR_LCH_CFG)
   {
      cfg->u.lchDel.cellId = RG_ACC_CELLID;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->u.lchDel.cellId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&(ueId));
      if (ueId > RG_ACC_MAX_UE)
         cfg->u.lchDel.crnti = 0;
      else
         cfg->u.lchDel.crnti = rgAccCb.acUeCb[ueId].crnti;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",&(cfg->u.lchDel.crnti));
      cfg->u.lchDel.lcId = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",&(cfg->u.lchDel.lcId));
   }
   else if (cfg->delType == RGAC_RGR_LCG_CFG)
   {
      cfg->u.lcgDel.cellId = RG_ACC_CELLID;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->u.lcgDel.cellId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&(ueId));
      if (ueId > RG_ACC_MAX_UE)
         cfg->u.lcgDel.crnti = 0;
      else
         cfg->u.lcgDel.crnti = rgAccCb.acUeCb[ueId].crnti;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",&(cfg->u.lcgDel.crnti));
      cfg->u.lcgDel.lcgId = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",&(cfg->u.lcgDel.lcgId));
   }

} /* rgAcUtlRgrBuildDelReq */

/*
*  
*       Fun:  rgAcUtlRgrBuildRstReq
*  
*       Desc:  Utility Function to Build UE Reset Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_rgrutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlRgrBuildRstReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlRgrBuildRstReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   RgrRst *cfg;
   U8     ueId = 0;

   TRC2(rgAcUtlRgrBuildRstReq)
 
   cfg   = &(cfgReq->u.rstInfo);

   CMXTA_ZERO(cfg , sizeof (RgrRst));

  /*----------- Fill General Configuration Parameters ---------*/

   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&(ueId));
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",&(cfg->crnti));
} /* rgAcUtlRgrBuildRstReq */

/**
 * @brief XTA  Utility function to. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrfillNdmrsWrapper
 *     
 **/
#ifdef ANSI
PRIVATE S16 rgAcUtlRgrfillNdmrsWrapper
(
U8 bw,
U8 ngEnum,
U8 sbStart,
U8 numSb,
U8 sbSize,
U8 *ndmrsArrP
)
#else
PRIVATE S16 rgAcUtlRgrfillNdmrsWrapper(bw,ngEnum, sbStart, numSb, sbSize, ndmrsArrP)
U8 bw;
U8 ngEnum;
U8 sbStart;
U8 numSb;
U8 sbSize;
U8 *ndmrsArrP;
#endif
{
   S16  ret;
   U8   numGrp;
   U8   ng6;

   switch (ngEnum)
   {
      case RGAC_RGR_NG_ONESIXTH:
         ng6 = 1;
         break;
      case RGAC_RGR_NG_HALF:
         ng6 = 3;
         break;
      case RGAC_RGR_NG_ONE:
         ng6 = 6;
         break;
      case RGAC_RGR_NG_TWO:
         ng6 = 12;
         break;
      default:
         RETVALUE(RFAILED);
   }

   numGrp = ((bw / 8) * ng6) / 6;
   ret = rgAcUtlRgrfillNdmrs(sbStart, numSb, sbSize, numGrp, ndmrsArrP);
   RETVALUE(ret);
} /* rgAcUtlRgrfillNdmrsWrapper */

/**
 * @brief XTA  Utility function to  
 *
 * @details
 *
 *     Function : rgAcUtlRgrfillNdmrs
 *     
 *     
 **/
#ifdef ANSI
PRIVATE S16 rgAcUtlRgrfillNdmrs
(
U8 sbStart,
U8 numSb,
U8 sbSize,
U8 numGrp,
U8 *ndmrsP
)
#else
PRIVATE S16 rgAcUtlRgrfillNdmrs(sbStart, numSb, sbSize, numGrp, ndmrsP)
U8 sbStart;
U8 numSb;
U8 sbSize;
U8 numGrp;
U8 *ndmrsP;
#endif
{
   U16 phichArr[110 * 2] = {0};
   U8  i;
   U8 numNdmrs = 0;

   if (numGrp * 8 < numSb)
   {
      /* PHICH groups not adequate */
      RETVALUE(RFAILED);
   }

   for (i = 0; i < numSb; ++i)
   {
      U8 ndmrs;
      U8 rb = sbStart + i * sbSize;
      for (ndmrs = 0; ndmrs < 8; ++ndmrs)
      {
         U16 phich = rgAcUtlRgrgetPhich(rb, ndmrs, numGrp);
         if (!rgAcUtlRgrphichUsed(phich, numNdmrs, phichArr))
         {
            ndmrsP[numNdmrs] = ndmrs;
            phichArr[numNdmrs] = phich;
            ++numNdmrs;
            /* go over to next subband */
            break;
         }
      }
      if (ndmrs == 8)
      {
         /* Could not assign a valid ndmrs */
         RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
} /* rgAcUtlRgrfillNdmrs */

/**
 * @brief XTA  Utility function to 
 *
 * @details
 *
 *     Function : rgAcUtlRgrphichUsed
 *     
 *     
 **/
#ifdef ANSI
PRIVATE U8 rgAcUtlRgrphichUsed
(
 U16 phich,
 U16 numPhich,
 U16 *phichArr
 )
#else
PRIVATE U8 rgAcUtlRgrphichUsed(phich, numPhich, phichArr)
 U16 phich;
 U16 numPhich;
 U16 *phichArr;
#endif
{
   U16  i;
   for (i = 0; i < numPhich; ++i)
   {
      if (phichArr[i] == phich)
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* rgAcUtlRgrphichUsed */
/**
 * @brief XTA  Utility function to 
 *
 * @details
 *
 *     Function : rgAcUtlRgrgetPhich
 *     
 *     
 **/
#ifdef ANSI
PRIVATE U16 rgAcUtlRgrgetPhich
(
 U8 rbStart,
 U8 ndmrs,
 U8 numGrp
 )
#else
PRIVATE U16 rgAcUtlRgrgetPhich(rbStart, ndmrs, numGrp)
 U8 rbStart;
 U8 ndmrs;
 U8 numGrp;
#endif
{

   U8 grp = rgAcUtlRgrgetPhichGrp(rbStart, ndmrs, numGrp);
   U8 seq = rgAcUtlRgrgetPhichSeq(rbStart, ndmrs, numGrp);

   RETVALUE(grp * 8 + seq);
} /* rgAcUtlRgrgetPhich */
/**
 * @brief XTA  Utility function to 
 *
 * @details
 *
 *     Function : rgAcUtlRgrgetPhichGrp
 *     
 *     
 **/
#ifdef ANSI
PRIVATE U8 rgAcUtlRgrgetPhichGrp
(
 U8 rbStart,
 U8 ndmrs,
 U8 numGrp
 )
#else
PRIVATE U8 rgAcUtlRgrgetPhichGrp(rbStart, ndmrs, numGrp)
 U8 rbStart;
 U8 ndmrs;
 U8 numGrp;
#endif
{
   RETVALUE((rbStart + ndmrs) % numGrp);
} /*rgAcUtlRgrgetPhichGrp */
/**
 * @brief XTA  Utility function to 
 *
 * @details
 *
 *     Function : rgAcUtlRgrgetPhichSeq
 *     
 *     
 **/
#ifdef ANSI
PRIVATE U8 rgAcUtlRgrgetPhichSeq
(
 U8 rbStart,
 U8 ndmrs,
 U8 numGrp
 )
#else
PRIVATE U8 rgAcUtlRgrgetPhichSeq(rbStart, ndmrs, numGrp)
 U8 rbStart;
 U8 ndmrs;
 U8 numGrp;
#endif
{
   RETVALUE(((rbStart / numGrp) + ndmrs) % 8);
} /* rgAcUtlRgrgetPhichSeq */

/* Added for SI Enhancement*/
#ifdef RGR_SI_SCH
/**
 * @brief XTA  Utility function to read SI configuration values 
 *  from XML and fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildSiCfgReq
 *     
 *     Utility function to read SI configuration values from XML and
 *     fill the config structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *cfgReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlRgrBuildSiCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrSiCfgReqInfo  *cfgReq
)
#else
PUBLIC S16 rgAcUtlRgrBuildSiCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrSiCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   U32           buffSz;
   U8            str[50];
   U8            bcchIdx=0;

   TRC2(rgAcUtlRgrBuildSiCfgReq)

   CMXTA_ZERO(cfgReq , sizeof (RgrSiCfgReqInfo));

   /* Assiging Default Cell Id "3" */
   cfgReq->cellId = RG_ACC_CELLID;
   /*Reading CELL Id from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfgReq->cellId));

   cfgReq->cfgType = RGR_SI_CFG_TYPE_MIB;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "cfgType", 
         &(cfgReq->cfgType));

   if(RGR_SI_CFG_TYPE_SI == cfgReq->cfgType)
   {
      cfgReq->siId = 1;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siId", 
         &(cfgReq->siId));
   }
   
   /*Set the PDU based upon the cfgType */
   switch(cfgReq->cfgType)
   {
      case RGR_SI_CFG_TYPE_MIB:
         buffSz = 3;
         cmMemset(str,0,sizeof(str));
         break;
      case RGR_SI_CFG_TYPE_SIB1:
         buffSz = 13;
         break;
      case RGR_SI_CFG_TYPE_SI:
         switch(cfgReq->siId)
         {
            case 1:
              buffSz = 32;
              break;
            case 2:
              buffSz = 37;
              break;
            case 3:
              buffSz = 41;
              break;
            case 4:
              buffSz = 47;
              break;
            case 5:
              break;
            default:
              RETVALUE(CMXTA_ERR_NOMATCH);
         }
         break;

      case 3:
         buffSz = 1;
         break;

      default:
         RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "buffSz", 
         &(buffSz));

   if(ROK != SGetMsg(RGAC_RGR_DFLTRGN, RGAC_RGR_DFLTPOOL, 
        &cfgReq->pdu))
      RETVALUE(CMXTA_ERR_RSRC);

   SAddPstMsgMult((U8 *)str, (MsgLen)(buffSz), cfgReq->pdu);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bcchIdx", &(bcchIdx));

   if (rgAccCb.bcchBuf[bcchIdx] != NULLP)
   {
      SPutMsg(rgAccCb.bcchBuf[bcchIdx]);
      rgAccCb.bcchBuf[bcchIdx] = NULLP;
   }

   if ((SCpyMsgMsg (cfgReq->pdu, CMXTA_TSTREG, 
               CMXTA_TSTPOOL, &(rgAccCb.bcchBuf[bcchIdx]))) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildSiCfgReq(): resource error\n"));
      RETVALUE(RFAILED);
   }

   /* LTE-MAC may add padding bytes to the pdu if the size does 
    * not match a pre-defined tbSz. Before,we cache the pdu, we 
    * will add paddinb bytes ourselves.
    */
   if (cfgReq->cfgType != RGR_SI_CFG_TYPE_MIB)
   {
      S32    tbSz   = 0;
      U8     nPrb   = 0;
      U8     mcs    = 0;

      tbSz = rgSCHUtlGetAllwdCchTbSz(buffSz*8,&nPrb,&mcs);

      if ( tbSz !=(S32)(buffSz*8) )
      {
         /* need to add padding bytes */
         MsgLen  nmPadBytes = 0;
         Data*   padding    = NULLP;

         nmPadBytes = (tbSz - (buffSz*8))/8;

         if ( SGetSBuf(RGAC_RGR_DFLTRGN,RGAC_RGR_DFLTPOOL,
                           &padding,nmPadBytes) != ROK)
         {
            RETVALUE(CMXTA_ERR_RSRC);
         }

         cmMemset((U8*)padding,(U8)0,nmPadBytes);

         if ( SAddPstMsgMult((Data*)padding,nmPadBytes,
                             rgAccCb.bcchBuf[bcchIdx]) != ROK )
         {
            RETVALUE(CMXTA_ERR_RSRC);
         }
         SPutSBuf(RGAC_RGR_DFLTRGN, RGAC_RGR_DFLTPOOL, 
                  (Data* )padding,(Size)nmPadBytes);
      }/* if (tbSz != ...*/
   }/* if (cfgReq->cfgType....*/

   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcUtlRgrBuildSiCfgReq */

#ifdef ANSI
PUBLIC S16 rgAcUtlRgrBuildWarningSiCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrWarningSiCfgReqInfo  *cfgReq
)
#else
PUBLIC S16 rgAcUtlRgrBuildWarningSiCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrWarningSiCfgReqInfo *cfgReq;
#endif
{
   typedef struct tmp 
   {
    Buffer       *pdu;
    CmLList      *node;
   }Tmp;
   /* local variables */
   U8           str[50];
   U32          buffSz;
   U8           bcchIdx=0, i, numSeg;
   Tmp          tmp[10];

   TRC2(rgAcUtlRgrBuildWarningSiCfgReq)

      CMXTA_ZERO(cfgReq , sizeof (RgrWarningSiCfgReqInfo));

   /* Assiging Default Cell Id "3" */
   cfgReq->cellId = RG_ACC_CELLID;
   /*Reading CELL Id from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfgReq->cellId));

   cfgReq->siId = 4;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "siId", 
         &(cfgReq->siId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "buffSz", 
         &(buffSz));

   cmLListInit(&cfgReq->siPduLst);

  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bcchIdx", &(bcchIdx));
  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSeg", &(numSeg));

   for(i = 0; i < numSeg; i++)
   {
      if(bcchIdx < RG_ACC_MAX_BCCH)
      {
         if(ROK != SGetMsg(RGAC_RGR_DFLTRGN, RGAC_RGR_DFLTPOOL, 
               &tmp[i].pdu))
            RETVALUE(CMXTA_ERR_RSRC);

          SGetSBuf(RGAC_RGR_DFLTRGN,RGAC_RGR_DFLTPOOL,
             (Data **)&tmp[i].node , sizeof(CmLList));
          SAddPstMsgMult((U8 *)str, (MsgLen)(buffSz),  tmp[i].pdu);    
          tmp[i].node->node = (PTR) tmp[i].pdu;
          cmLListAdd2Tail(&cfgReq->siPduLst, tmp[i].node);
          if (rgAccCb.bcchBuf[bcchIdx] != NULLP)
          {
             SPutMsg(rgAccCb.bcchBuf[bcchIdx]);
             rgAccCb.bcchBuf[bcchIdx] = NULLP;
          }
          if ((SCpyMsgMsg (tmp[i].pdu, CMXTA_TSTREG, 
                  CMXTA_TSTPOOL, &(rgAccCb.bcchBuf[bcchIdx]))) != ROK)
             RETVALUE(CMXTA_ERR_RSRC);
      }
      else
      {
         CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRgrBuildWarningSiCfgReq(): BCCH Index exceeding the array size of BCCH Buffer\n")); 
         break;
      }
      bcchIdx++;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcUtlRgrBuildWarningSiCfgReq */
#endif /*RGR_SI_SCH*/

/* LTE_ADV_FLAG_REMOVED_START */
/**
 * @brief XTA  Utility function to read RNTP values 
 *  from XML and fill the loadInf structure. 
 *
 * @details
 *
 *     Function : rgAcUtlRgrBuildLoadInfReq
 *     
 *     Utility function to read RNTP values from XML and
 *     fill the loadInf structure.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[out]  *loadInfReq 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlRgrBuildLoadInfReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
RgrLoadInfReqInfo  *loadInfReq
)
#else
PUBLIC S16 rgAcUtlRgrBuildLoadInfReq(tcCb, spCb, loadInfReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
RgrLoadInfReqInfo *loadInfReq;
#endif
{

   TRC2(rgAcUtlRgrBuildLoadInfReq)

   CMXTA_ZERO(loadInfReq , sizeof (RgrLoadInfReqInfo));

   /* Assiging Default Cell Id "3" */
   loadInfReq->cellId = RG_ACC_CELLID;

   /*Reading CELL Id from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghcellId", 
         &(loadInfReq->cellId));

   /* Reading nghCellPHighStartRb */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghPHighStartRb", 
         &(loadInfReq->rgrCcPHighStartRb));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghPHighEndRb", 
         &(loadInfReq->rgrCcPHighEndRb));

   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcUtlRgrBuildLoadInfReq */
/* LTE_ADV_FLAG_REMOVED_END */
/********************************************************************30**

         End of file:     rgac_rgrutl.c@@/main/3 - Sat Jul 30 02:21:03 2011

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
/main/1      ---       ns  1. Initial Release.
/main/2      ---       ns  1. LTE MAC 2.1 release
             rg001.201 sm            1. Added TTI indication towards 
                                        RGR user.
             rg002.201 sm  1. Adding preamble format to lenght mapping table.
                           2. Storing the preamble length in acc's rach cfg cb.
             rg004.201 ns  1. ccpu00105882: By default  cfg->ueQosRecfg.ambrPres
                              was added as TRUE now changed depending on value
                              read from XML.
             rg004.201 rnt 1. Modified for SI Enhancement
             rg005.201 rnt 1. Changed attribute type for solaris execution
             rg007.201   ap  1. Added support for MIMO
             rg008.201  rsharon  1. Added support for SPS.
             rg009.201  rsharon  1.[ccpu00112372]:Changes for CR timer
                                   implementation.
                         adi   1 ccpu00114920: Change to add paddying bytes
                               to pdu received from application to ensure
                               validity checks later on in acceptance do not
                               fail
            rg009.201 dv 1.Added changes for TFU_UPGRADE.
/main/3      ---        dvasisht          1. Updated for LTE MAC Release 3.1
            rg002.301 asehgal 1. ccpu00120621: default value of qci set as 1
/main/4     rg003.301 ap      1. ccpu00121085: added element maxMsg3PerUlsf.
$SID$       ---       rt      1. LTE MAC 4.1 release
*********************************************************************91*/
