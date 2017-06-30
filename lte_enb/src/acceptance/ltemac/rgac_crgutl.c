

/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_crghdl.c

     Sid:      rgac_crgutl.c@@/main/3 - Sat Jul 30 02:20:53 2011

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
#include "rgac_crg.x"        /* MAC error defines */

/**
 * @brief XTA  Utility function to read cell configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlCrgBuildCellCfgReq
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
PUBLIC Void rgAcUtlCrgBuildCellCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildCellCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgCellCfg  *cfg;

   TRC2(rgAcUtlCrgBuildCellCfgReq)
 
   cfg   = &(cfgReq->u.cfgInfo.u.cellCfg);

   CMXTA_ZERO(cfg , sizeof (CrgCellCfg)); 

   cfgReq->u.cfgInfo.cfgType = RGAC_CRG_CELL_CFG;
   
   /* Default value for Cell id */
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   
   cfg->rachCfg.maxMsg3Tx = 2; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg3Tx",
         &(cfg->rachCfg.maxMsg3Tx));

   /* Filling Default Value for Downlink BandWidth */ 
   cfg->bwCfg.dlTotalBw = RGAC_CRG_DEFAULT_DLTOTBW;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlTotalBw", 
         &(cfg->bwCfg.dlTotalBw));

   /* Filling Default Value for Uplink BandWidth */
   cfg->bwCfg.ulTotalBw = RGAC_CRG_DEFAULT_ULTOTBW;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ulTotalBw", 
         &(cfg->bwCfg.ulTotalBw));
   RETVOID;
} /*rgAcUtlCrgBuildCellCfgReq */
/*
*  
*       Fun:  rgAcUtlCrgBuildUeCfgReq
*  
*       Desc:  Utility Function to Build Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlCrgBuildUeCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildUeCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgUeCfg    *cfg;
   U8          ueId = 0;
   Bool        isHoUe = FALSE; /* For dedicated crnti */

   TRC2(rgAcUtlCrgBuildUeCfgReq)
 
   cfg   = &(cfgReq->u.cfgInfo.u.ueCfg);

   CMXTA_ZERO(cfg , sizeof (CrgUeCfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_CRG_UE_CFG;
  
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", 
         &(ueId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isHoUe", 
         &(isHoUe));

   if(isHoUe == TRUE)
      cfg->crnti = rgAccCb.dedCrnti; /* Dedicated crnti used for HO UE */
   else
      cfg->crnti = rgAccCb.acUeCb[ueId].crnti;

   cfg->ueUlHqCfg.maxUlHqTx = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlHqTx", 
         &(cfg->ueUlHqCfg.maxUlHqTx));
/* Adding MIMO Support */
#ifdef LTEMAC_MIMO
   cfg->txMode.pres = PRSNT_NODEF;
   cfg->txMode.tm = CRG_UE_TM_1;
   cmXtaXmlGetVal(tcCb, spCb->childStep,CMXTA_ATTRIB_ENUM_U8, "tm", 
         &(cfg->txMode.tm));
#endif   


   RETVOID;
} /*rgAcUtlCrgBuildUeCfgReq */

EXTERN LchData lchData[9];
EXTERN Bool isPfsSim;
EXTERN U8 numLc;  

/*
*  
*       Fun:  rgAcUtlCrgBuildLchCfgReq
*  
*       Desc:  Utility Function to Build Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlCrgBuildLchCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildLchCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgLchCfg *cfg;
   U8        ueId = 0;
   static    U8  lcIdx = 0; 

   TRC2(rgAcUtlCrgBuildLchCfgReq)
 
   cfg   = &(cfgReq->u.cfgInfo.u.lchCfg);

   CMXTA_ZERO(cfg , sizeof (CrgLchCfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_CRG_LCH_CFG;
   
   /* Default value for Cell id */
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&ueId);
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;

   if(isPfsSim)
   {
       cfg->lcId = lchData[lcIdx].lcId;
       cfg->dir = lchData[lcIdx].dir;
       cfg->lcType = lchData[lcIdx].lcType;
#ifdef LTE_L2_MEAS
       cfg->qci = lchData[lcIdx].qci;
#endif 
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
      /* Default Direction for Logical Channels */
      cfg->dir = RGAC_CRG_DIR_TX_RX;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dir",
            &(cfg->dir));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcType",
            &(cfg->lcType));
     
#ifdef LTE_L2_MEAS
      /* Setting default value of qci 
       * as 5 as 0 is not valid.qci 0 earlier had priority 0
       * which is now the priority of qci 5*/
      cfg->qci = 5;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "qci",
            &(cfg->qci));
#endif
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlTrchType",
         &(cfg->dlInfo.dlTrchType));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ulTrchType",
         &(cfg->ulInfo.ulTrchType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",
         &(cfg->ulInfo.lcgId)); 

   RETVOID;
} /*rgAcUtlCrgBuildLchCfgReq */
/**
 * @brief XTA  Utility function to read cell re configuration values from XML and
 * fill the config structure. 
 *
 * @details
 *
 *     Function : rgAcUtlCrgBuildCellReCfgReq
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
PUBLIC Void rgAcUtlCrgBuildCellReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildCellReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgCellRecfg *cfg;

   TRC2(rgAcUtlCrgBuildCellReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.cellRecfg);

   CMXTA_ZERO(cfg , sizeof (CrgCellRecfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.recfgInfo.recfgType = RGAC_CRG_CELL_CFG;

   /* Default value for Cell id */
   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->cellId));


   cfg->rachRecfg.maxMsg3Tx = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxMsg3Tx",
         &(cfg->rachRecfg.maxMsg3Tx));

   RETVOID;
} /*rgAcUtlCrgBuildCellReCfgReq */
/*
*  
*       Fun:  rgAcUtlCrgBuildUeReCfgReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlCrgBuildUeReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildUeReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgUeRecfg    *cfg;
   U8            oldUeId = 0;
   U8            newUeId = 0;
#ifdef LTE_ADV
   U8            ueId = 0;
   Bool        isSCellCfgPres = FALSE; /* for sCellAdd */
   Inst        macInst  = 0;
   U8          idx = 0;
   U8          numSCells = 0;
   U16         sCellId = 0;
   SuId        rguUlSapId = 0;
   SuId        rguDlSapId = 0;
#endif /* LTE_ADV */

   TRC2(rgAcUtlCrgBuildUeReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.ueRecfg);

   CMXTA_ZERO(cfg , sizeof (CrgUeRecfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.recfgInfo.recfgType = RGAC_CRG_UE_CFG;
  
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
   cfg->newCrnti = rgAccCb.acUeCb[newUeId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newcrnti",
         &(cfg->newCrnti));
   
   cfg->ueUlHqRecfg.maxUlHqTx = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlHqTx", 
         &(cfg->ueUlHqRecfg.maxUlHqTx));
/* Adding MIMO Support */
#ifdef LTE_ADV
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isSCellCfgPres", &(isSCellCfgPres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSCells", &(numSCells));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sCellId", &(sCellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "macInst", &(macInst));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rguUlSapId", &(rguUlSapId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rguDlSapId", &(rguDlSapId));

   if(TRUE == isSCellCfgPres)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",
            &(ueId));
      cfg->newCrnti = rgAccCb.acUeCb[ueId].crnti;
      cfg->oldCrnti = rgAccCb.acUeCb[ueId].crnti;
      cfg->crgSCellCfg.isSCellCfgPres = TRUE;
      cfg->crgSCellCfg.numSCells = numSCells;
      for(idx = 0; idx < numSCells; idx++)
      {
         cfg->crgSCellCfg.ueSCellCfg[idx].sCellId = sCellId; 
         cfg->crgSCellCfg.ueSCellCfg[idx].macInst = macInst; 
         cfg->crgSCellCfg.ueSCellCfg[idx].rguUlSapId = rguUlSapId; 
         cfg->crgSCellCfg.ueSCellCfg[idx].rguDlSapId = rguDlSapId; 
      }
   }
#endif /* LTE_ADV */
#ifdef LTEMAC_MIMO
   cfg->txMode.pres = NOTPRSNT;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isTMRecfgPres", 
         &(cfg->txMode.pres));
   cfg->txMode.tm = CRG_UE_TM_1;
   cmXtaXmlGetVal(tcCb, spCb->childStep,CMXTA_ATTRIB_ENUM_U32, "tm", 
         &(cfg->txMode.tm));
#endif   
   RETVOID;
} /*rgAcUtlCrgBuildUeReCfgReq */
/*
*  
*       Fun:  rgAcUtlCrgBuildLchReCfgReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlCrgBuildLchReCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildLchReCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgLchRecfg *cfg;
   U8          ueId = 0;

   TRC2(rgAcUtlCrgBuildLchReCfgReq)
 
   cfg   = &(cfgReq->u.recfgInfo.u.lchRecfg);

   CMXTA_ZERO(cfg , sizeof (CrgLchRecfg));

  /*----------- Fill General Configuration Parameters ---------*/
   cfgReq->u.cfgInfo.cfgType = RGAC_CRG_LCH_CFG;
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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcgId",
         &(cfg->ulRecfg.lcgId));
   RETVOID;
} /*rgAcUtlCrgBuildLchReCfgReq */

/*
*  
*       Fun:  rgAcUtlCrgBuildDelReq
*  
*       Desc:  Utility Function to Build Re Configuration Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlCrgBuildDelReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildDelReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgDel *cfg;
   U8     ueId = 0;

   TRC2(rgAcUtlCrgBuildDelReq)
 
   cfg   = &(cfgReq->u.delInfo);

   CMXTA_ZERO(cfg , sizeof (CrgDel));
   cfg->delType = RGAC_CRG_CELL_CFG;

  /*----------- Fill General Configuration Parameters ---------*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "DelType",&(cfg->delType));

   if (cfg->delType == RGAC_CRG_CELL_CFG)
   {
      cfg->u.cellDel.cellId = RG_ACC_CELLID;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->u.cellDel.cellId));
   }
   else if (cfg->delType == RGAC_CRG_UE_CFG)
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
   else if (cfg->delType == RGAC_CRG_LCH_CFG)
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
      cfg->u.lchDel.dir = 2;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dir",&(cfg->u.lchDel.dir));
   }

} /* rgAcUtlCrgBuildDelReq */

/*
*  
*       Fun:  rgAcUtlCrgBuildRstReq
*  
*       Desc:  Utility Function to Build UE Reset Req
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rgac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC Void rgAcUtlCrgBuildRstReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CrgCfgReqInfo  *cfgReq
)
#else
PUBLIC Void rgAcUtlCrgBuildRstReq(tcCb, spCb, cfgReq)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CrgCfgReqInfo *cfgReq;
#endif
{
   /* local variables */
   CrgRst *cfg;
   U8     ueId = 0;

   TRC2(rgAcUtlCrgBuildRstReq)
 
   cfg   = &(cfgReq->u.rstInfo);

   CMXTA_ZERO(cfg , sizeof (CrgRst));

  /*----------- Fill General Configuration Parameters ---------*/

   cfg->cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",&(cfg->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",&(ueId));
   cfg->crnti = rgAccCb.acUeCb[ueId].crnti;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",&(cfg->crnti));
} /* rgAcUtlCrgBuildRstReq */

/********************************************************************30**

         End of file:     rgac_crgutl.c@@/main/3 - Sat Jul 30 02:20:53 2011

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
           rg007.201   ap  1. Added support for MIMO
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1.
           rg002.301 asehgal 1. ccpu00120621-added default value of qci.
$SID$        ---       rt    1. LTE MAC 4.1 release
*********************************************************************91*/
