




/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point functions
  
     File:     rg_com.c 
  
     Sid:      gk_com.c@@/main/3 - Sat Jul 30 02:21:25 2011
  
     Prg:      sd
  
**********************************************************************/

/** @file rg_com.c
@brief This module does processing related to handling of upper interface APIs 
invoked by RRC towards MAC.
*/

static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_FILE_ID=181;
static int RLOG_MODULE_ID=4096;
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_mblk.h"       /* common memory link list library */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "lrg.h"
#include "crg.h"
#include "rgu.h"
#include "tfu.h"
#include "rg_sch_inf.h"
#include "rg_prg.h"       /* PRG interface includes*/
#include "rg_env.h"
#include "rg.h"
#include "rg_err.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system service interface */
#include "cm5.x"           /* common timers */
#include "cm_lib.x"        /* common library */
#include "cm_hash.x"       /* common hash list */
#include "cm_mblk.x"       /* common memory link list library */
#include "cm_llist.x"      /* common linked list library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"        /* common LTE */
#include "lrg.x"
#include "crg.x"
#include "rgu.x"
#include "tfu.x"
#include "rg_sch_inf.x"
#include "rg_prg.x"       /* PRG interface typedefs*/
#include "rg.x"
#ifdef LTE_ADV
#include "rg_pom_scell.x"
#endif
/* local defines */
PRIVATE S16 rgCOMHndlCfgReq ARGS((Inst inst,CrgCfg  *cfg, RgErrInfo *errInfo,Bool *isCfmRqrd,CrgCfgTransId transId));
PRIVATE S16 rgCOMHndlRecfgReq ARGS((Inst inst,CrgRecfg *recfg, RgErrInfo *errInfo, \
         CrgCfgTransId transId,Bool *isCfmRqrd));
PRIVATE S16 rgCOMHndlDelReq ARGS((Inst inst,CrgDel *del, RgErrInfo *errInfo, Bool *isCfmRqrd, CrgCfgTransId transId));
PRIVATE S16 rgCOMHndlResetReq ARGS((Inst inst,CrgRst *reset,RgErrInfo *errInfo));
/* local typedefs */
 
/* local externs */
 
/* forward references */

/**
 * @brief Handler to handle config request from RRC to MAC.
 *
 * @details
 *
 *     Function: rgCOMCfgReq
 *     
 *     This API handles processing for config request from RRC to MAC. 
 *     
 *     Processing Steps:
 *      - If configuration, process configuration request. Call rgCOMHndlCfgReq.
 *      - else If re-configuration, process re-configuration request. 
 *        Call rgCOMHndlRecfgReq.
 *      - else If reset, process reset request. Call rgCOMHndlResetReq.
 *      - else If delete, process delete request. Call rgCOMHndlDelReq.
 *      - If successful, send confirmation to RRC. Call rgUIMCrgCfgCfm.
 *      - If failed, FAIL.
 *
 *  @param[in]  Inst        inst
 *  @param[in]  CrgCfgTransId transId
 *  @param[in]  CrgCfgReqInfo *crgCfgReq
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgCOMCfgReq
(
Inst          inst,
CrgCfgTransId transId,
CrgCfgReqInfo *crgCfgReq
)
#else
PUBLIC S16 rgCOMCfgReq(inst,transId, crgCfgReq)
Inst          inst;
CrgCfgTransId transId;
CrgCfgReqInfo *crgCfgReq;
#endif
{
   S16             ret;
   U8              cfmStatus = CRG_CFG_CFM_OK;
   RgErrInfo       errInfo;
   Bool            isCfmRqrd = TRUE;

   TRC2(rgCOMCfgReq);

   /* Process Config/Reconfig/Delete request from RRC */
   switch (crgCfgReq->action)
   {
      case CRG_CONFIG:
         {
            ret = rgCOMHndlCfgReq(inst,&crgCfgReq->u.cfgInfo, &errInfo,&isCfmRqrd, transId);
            break;
         }
      case CRG_RECONFIG:
         {
            ret = rgCOMHndlRecfgReq(inst,&crgCfgReq->u.recfgInfo, &errInfo, transId, &isCfmRqrd);
            break;
         }
         /* Start: LTEMAC_2.1_DEV_CFG */
      case CRG_RESET:
         {
            ret = rgCOMHndlResetReq(inst,&crgCfgReq->u.rstInfo, &errInfo);
            break;
         }
         /* End: LTEMAC_2.1_DEV_CFG */
      case CRG_DELETE:
         {
            ret = rgCOMHndlDelReq(inst,&crgCfgReq->u.delInfo, &errInfo, &isCfmRqrd, transId);
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "Invalid configuration action %d",
                     crgCfgReq->action);

            ret = RFAILED;
         }
   }

   if (ret != ROK)
   {
      cfmStatus = CRG_CFG_CFM_NOK;
   }

   /* When UeSCellCfg is present then confirmation will be sent later once
      confirm from all SMAC are recved at PMAC. PMAC will send a consolidated
      confirm to RRC.Handling the failure of PMAC for Ue Scell add*/
#ifdef LTE_ADV
if(TRUE == isCfmRqrd)
   {
#endif
      /* Send back confirmation status to RRC */
      rgUIMCrgCfgCfm(inst,transId, cfmStatus); 
#ifdef LTE_ADV
   }
#endif
   RGDBGINFO(inst,(rgPBuf(inst), "CRG Configuration request processed\n"));
   RETVALUE(ret);
}  /* rgCOMCfgReq */
/**
 * @brief Handler for processing Cell/Ue/Logical channel configuration request
 * recieved from RRC.
 *
 * @details
 *
 *     Function: rgCOMHndlCfgReq
 *     
 *     This API handles processing of configuration request from RRC to MAC. 
 *     
 *     Processing Steps:
 *        - Validate configuration request parameters at CFG module. 
 *          Call rgCFGVldtCrgCellCfg, rgCFGVldtCrgUeCfg, rgCFGVldtCrgLcCfg 
 *          for Cell, UE and Logical channel configuration respectively.
 *        - If validated successfully, Call rgCFGCrgCellCfg, rgCFGCrgUeCfg, 
 *          rgCFGCrgLcCfg for Cell, UE and Logical channel configuration 
 *          respectively, else FAIL.
 *
 *  @param[in]  Inst        inst
 *  @param[in]  CrgCfg    *cfg
 *  @param[out] RgErrInfo *errInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgCOMHndlCfgReq
(
Inst             inst,
CrgCfg           *cfg,
RgErrInfo        *errInfo,
Bool             *isCfmRqrd,
CrgCfgTransId    transId
)
#else
PRIVATE S16 rgCOMHndlCfgReq(inst,cfg, errInfo,isCfmRqrd,transId)
Inst            inst;
CrgCfg          *cfg;
RgErrInfo       *errInfo;
Bool            *isCfmRqrd;
CrgCfgTransId   transId;
#endif
{
   S16       ret;
   RgCellCb  *cell = NULLP;
   RgUeCb    *ue   = NULLP;

   TRC2(rgCOMHndlCfgReq);

   errInfo->errType = RGERR_COM_CFG_REQ;

   /* Validate and process the configuration request */ 
   switch (cfg->cfgType)
   {
      case CRG_CELL_CFG:
      {
         ret = rgCFGVldtCrgCellCfg(inst,&cfg->u.cellCfg,errInfo);
         if (ret != ROK)
         {
              RLOG_ARG0(L_ERROR,DBG_CELLID,cfg->u.cellCfg.cellId, "Cell configuration validation FAILED\n");
              RETVALUE(RFAILED);
         }
         ret = rgCFGCrgCellCfg(inst,&cfg->u.cellCfg, errInfo);
         break;
      }
      case CRG_UE_CFG:
      {
         {
            ret = rgCFGVldtCrgUeCfg(inst,&cfg->u.ueCfg, &cell, errInfo);
            if (ret != ROK)
            {
               RLOG_ARG0(L_ERROR,DBG_CRNTI,cfg->u.ueCfg.crnti, "Ue configuration validation FAILED\n");
               RETVALUE(RFAILED);
            }
            ret = rgCFGCrgUeCfg(inst,cell, &cfg->u.ueCfg, errInfo);
         }
         break;
      }
      case CRG_LCH_CFG:
      {

         ret = rgCFGVldtCrgLcCfg(inst,&cfg->u.lchCfg, &cell, &ue,errInfo);
         if (ret != ROK)
         {
            
            RLOG_ARG1(L_ERROR,DBG_CELLID,cfg->u.cellCfg.cellId,
                         "LC configuration validation FAILED: LC %d\n", cfg->u.lchCfg.lcId);
            RETVALUE(RFAILED);
         }
         ret = rgCFGCrgLcCfg(inst,cell, ue, &cfg->u.lchCfg, errInfo,isCfmRqrd,transId);
         break;
      }
      default:
      {
         RLOG1(L_ERROR, "Should never come here: cfgType %d",cfg->cfgType);
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ret);
}  /* rgCOMHndlCfgReq */


/**
 * @brief Handler for processing Cell/Ue/Logical channel re-configuration request
 * recieved from RRC.
 *
 * @details
 *
 *     Function: rgCOMHndlRecfgReq
 *     
 *     This API handles processing of reconfiguration request from RRC to MAC. 
 *     
 *     Processing Steps:
 *      - Validate reconfiguration request parameters at CFG module. Call 
 *        rgCFGVldtCrgCellRecfg, rgCFGVldtCrgUeRecfg, rgCFGVldtCrgLchRecfg for 
 *        Cell, UE and logical channel reconfiguration respectively.
 *      - If validated, Call rgCFGCrgCellRecfg, rgCFGCrgUeRecfg, 
 *        rgCFGCrgLchRecfg for Cell, UE and Logical channel re-configuration 
 *        respectively else FAIL.
 *
 *  @param[in]  Inst        inst
 *  @param[in]  CrgRecfg   *recfg
 *  @param[out] RgErrInfo  *errInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgCOMHndlRecfgReq
(
Inst             inst,
CrgRecfg         *recfg,
RgErrInfo        *errInfo,
CrgCfgTransId    transId,
Bool             *isCfmRqrd
)
#else
PRIVATE S16 rgCOMHndlRecfgReq(inst,recfg, errInfo, transId, isCfmRqrd)
Inst            inst;
CrgRecfg        *recfg;
RgErrInfo       *errInfo;
CrgCfgTransId   transId;
Bool            *isCfmRqrd;
#endif
{
   S16       ret;
   RgCellCb  *cell = rgCb[inst].cell;
   RgUeCb    *ue   = NULLP;
   RgUlLcCb  *ulLc = NULLP;

   TRC2(rgCOMHndlRecfgReq);

   errInfo->errType = RGERR_COM_RECFG_REQ;
   
   /* Validate and process the re-configuration request */ 
   switch (recfg->recfgType)
   {
      case CRG_CELL_CFG:
      {
         ret = rgCFGVldtCrgCellRecfg(inst,&recfg->u.cellRecfg, &cell, errInfo);
            if (ret != ROK) 
            {
               RLOG_ARG0(L_ERROR,DBG_CELLID,recfg->u.cellRecfg.cellId,
                         "Cell Recfg Validation FAILED");
               RETVALUE(RFAILED);
            }
         ret = rgCFGCrgCellRecfg(inst,cell, &recfg->u.cellRecfg, errInfo);
         break;
      }
      case CRG_UE_CFG:
      {
         /*ccpu00126865 - Added as a part of RRC Reestablishment issue with MAC
          * having a possibility of sending NOK */
         if (recfg->u.ueRecfg.oldCrnti != recfg->u.ueRecfg.newCrnti)
         {
            errInfo->errCause = RGERR_CFG_INVALID_CRG_UE_RECFG;
            ret = ROK;
         }    
         else
         {
#ifdef LTE_ADV
         /* Check for isSCellCfgPres */
         if(TRUE == recfg->u.ueRecfg.crgSCellCfg.isSCellCfgPres)
         {
            ret = rgFillAndAddSCellCfg(inst, cell, &recfg->u.ueRecfg, transId, isCfmRqrd);
            if (ret != ROK)
            {
               RGDBGERRNEW(inst,(rgPBuf(inst), "[%d]Ue SCell configuration FAILED for inst [%d]\n",
                        recfg->u.ueRecfg.oldCrnti, inst));
               RETVALUE(RFAILED);
            }

         }
         else
         {
#endif /* LTE_ADV */
            ret = rgCFGVldtCrgUeRecfg(inst,&recfg->u.ueRecfg, &cell, &ue, errInfo);
            if ( ret != ROK)
            {
               RLOG_ARG1(L_ERROR,DBG_CELLID,recfg->u.ueRecfg.cellId,
                      "Ue Re-configuration validation FAILED OLD CRNTI:%d",
                      recfg->u.ueRecfg.oldCrnti);
               RETVALUE(RFAILED);
            }
            ret = rgCFGCrgUeRecfg(inst,cell, ue, &recfg->u.ueRecfg, errInfo);
         }
#ifdef LTE_ADV
         }
#endif
         break;
      }
      case CRG_LCH_CFG:
      {
         ret = rgCFGVldtCrgLcRecfg(inst,&recfg->u.lchRecfg, &cell, &ue, 
               &ulLc, errInfo);
         if (ret != ROK)
         {
            RLOG_ARG2(L_ERROR,DBG_CELLID,recfg->u.lchRecfg.cellId,
                      "LC Re-configuration validation FAILED LCID:%d CRNTI:%d",
                      recfg->u.lchRecfg.lcId,recfg->u.lchRecfg.crnti);
            RETVALUE(RFAILED);
         }

#ifdef LTE_ADV
         /*ERAB- multicell fix*/
         cmMemcpy( (U8*)&(ue->cfgCfmInfo.transId), (U8*)&transId,
               sizeof(CrgCfgTransId));
#endif
         ret = rgCFGCrgLcRecfg(inst,cell, ue, ulLc,
               &recfg->u.lchRecfg, errInfo,isCfmRqrd);

         break;
      }
      default:
      {
         RLOG1(L_ERROR, "Should never come here: recfgType %d",
                  recfg->recfgType);
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ret);
}  /* rgCOMHndlRecfgReq */

/*Start: LTEMAC_2.1_DEV_CFG */
/**
 * @brief Handler for processing UE Reset request recieved from RRC.
 *
 * @details
 *
 *     Function: rgCOMHndlResetReq
 *     
 *     This API handles processing of Reset request from RRC to MAC. 
 *     
 *     Processing Steps:
 *      - Validate reset request parameters at CFG module. Call 
 *        rgCFGVldtCrgUeReset for UE reset.
 *      - If validated, Call rgCFGCrgUeReset for UE reset, else FAIL.
 *
 *  @param[in]  Inst        inst
 *  @param[in]  CrgRst     *reset
 *  @param[out] RgErrInfo  *errInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgCOMHndlResetReq
(
Inst       inst,
CrgRst     *reset,
RgErrInfo  *errInfo
)
#else
PRIVATE S16 rgCOMHndlResetReq(inst,reset, errInfo)
Inst       inst;
CrgRst     *reset;
RgErrInfo  *errInfo;
#endif
{
   TRC2(rgCOMHndlResetReq);

   /* Fix : ccpu00126865: ignore CRG reset. Let SCH trigger it. */
   
   errInfo->errCause = RGERR_NONE;
   RGDBGINFO(inst,(rgPBuf(inst), "CRG UE Reset processed \n"));
   RETVALUE(ROK);
}  /* rgCOMHndlResetReq */
/*End: LTEMAC_2.1_DEV_CFG */

/**
 * @brief Handler for processing Cell/UE/Logical channel delete request
 * recieved from RRC.
 *
 * @details
 *
 *     Function: rgCOMHndlDelReq
 *     
 *     This API handles processing of delete request from RRC to MAC. 
 *     
 *     Processing Steps:
 *        - Fetch corresponding control block and pass it to CFG module.
 *        - If control block does not exist, FAIL.
 *
 *  @param[in]  Inst        inst
 *  @param[in]  CrgDel    *del
 *  @param[out] RgErrInfo *errInfo
    @param[out] Bool      *isCfmRqrd
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgCOMHndlDelReq
(
Inst        inst,
CrgDel      *del,
RgErrInfo   *errInfo,
Bool        *isCfmRqrd,
CrgCfgTransId transId
)
#else
PRIVATE S16 rgCOMHndlDelReq(inst,del, errInfo,isCfmRqrd,transId)
Inst        inst;
CrgDel      *del;
RgErrInfo   *errInfo;
Bool        *isCfmRqrd;
CrgCfgTransId transId;
#endif
{

   S16            ret;
   VOLATILE U32   startTime=0;

   TRC2(rgCOMHndlDelReq);
   
   errInfo->errType = RGERR_COM_DEL_REQ;
   
   /* Process the delete request */ 
   switch (del->delType)
   {
      case CRG_CELL_CFG:
      {
         ret = rgCFGCrgCellDel(inst,del, errInfo);
         break;
      }
      case CRG_UE_CFG:
      {
         /*starting Task*/ 
         SStartTask(&startTime,PID_MAC_UE_DEL);


         ret = rgCFGCrgUeDel(inst,del, errInfo);
         RGDBGINFONEW(inst,(rgPBuf(inst),"[%d] Delete UE Done \n", del->u.ueDel.crnti));

         /*stoping Task*/ 
         SStopTask(startTime,PID_MAC_UE_DEL);

         break;
      }
      case CRG_LCH_CFG:
      {
         ret = rgCFGCrgLcDel(inst,del, errInfo,isCfmRqrd, transId);
         break;
      }
      default:
      {
         RLOG1(L_ERROR, "Should never come here: delType %d",
                  del->delType);
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ret);
}  /* rgCOMHndlDelReq */

#ifdef LTE_ADV
/**
 * @brief Handler for the SCell configuration request from RRC to MAC.
 *
 * @details
 *
 *     Function : RgPrgPMacSMacUeSCellCfgReq
 *
 *     Processing Steps:
 *      - Allocate and create UE control block.
 *      - Update UE control block with the values recieved in the
 *        configuration.
 *      - If successful, add the control block to hash list of UEs for the cell
 *        else Rollback and FAIL.
 *
 *  @param[in]  Pst          *pst
 *  @param[in]  RgPrgUeSCellCfgInfo *ueSCellCb
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 RgPrgPMacSMacUeSCellCfgReq
(
Pst         *pst,    
RgPrgUeSCellCfgInfo *ueSCellCb
)
#else
PUBLIC S16 RgPrgPMacSMacUeSCellCfgReq(pst, ueSCellCb)
Pst         *pst;    
RgPrgUeSCellCfgInfo *ueSCellCb;
#endif
{
   RgPrgCfgCfmInfo  cfgCfm;
   Inst             inst = pst->dstInst;
   RgCellCb         *cell = rgCb[inst].cell;
   S16              ret;
   Pst              cfmPst;    

   TRC2(RgPrgPMacSMacUeSCellCfgReq);
   
   RGDBGPRM(inst,(rgPBuf(inst),
            "APPLYING CRG UE SCELL CONFIG: cellId %d ueId %d\n",
            ueSCellCb->cellId, ueSCellCb->ueId));

   cfgCfm.ueId = ueSCellCb->ueId;
   cfgCfm.sCellId = ueSCellCb->cellId;
   cfgCfm.status = PRG_CFG_CFM_OK;
   cfgCfm.event = EVTPRGUESCELLCFGCFM;
   rgGetPstToInst(&cfmPst, inst, pst->srcInst);

  ret = rgUtlVltdAddSCellCfg(ueSCellCb, cell, inst);
  if(ret != ROK)
  {
     RGDBGERRNEW(inst,(rgPBuf(inst), "[%d]Crg Ue SCell failed:\
              cellId %d\n", ueSCellCb->ueId, ueSCellCb->cellId));
     /* Set status as Not OK*/
     cfgCfm.status = PRG_CFG_CFM_NOK;
  }
  else
  {
     ret = rgCfgAddUeSCellCfg(inst, ueSCellCb, cell);
     if(ret != ROK)
     {
        RGDBGERRNEW(inst,(rgPBuf(inst), "[%d]Crg Ue SCell failed:\
                 cellId %d\n", ueSCellCb->ueId, ueSCellCb->cellId));
        /* Set status as Not OK*/
        cfgCfm.status = PRG_CFG_CFM_NOK;
     }
  }
  
  RGDBGINFONEW(inst,(rgPBuf(inst), "[%d]Crg Ue SCell Config done:\
           cellId %d\n", ueSCellCb->ueId, ueSCellCb->cellId));

  /* Send positive confirmation to primary cell*/
  RgPrgSMacPMacCfg(&cfmPst, &cfgCfm);
  RETVALUE(ROK);
}  /* RgPrgPMacSMacUeSCellCfgReq */

/**
 * @brief Hander for config confim from sec MAC to Pri mac for Add Scell Cfg.
 *
 * @details
 *
 *     Function : RgPrgSMacPMacCfgCfm
 *
 *     Processing Steps:
 *      - Allocate and create UE control block.
 *      - If cfm event is lch recfg then send the confirmation to RRC for
 *        that event.
 *      - If cfm event is Scell addition then send the confirmation to RRC for
 *        the same.
 *         - Update UE control block with the values received in the
 *           configuration.
 *         - If successful, add the control block to hash list of UEs for the cell
 *           else Rollback and FAIL.
 *
 *  @param[in]  Inst        dstMacInst
 *  @param[in]  RgUrSCellCb  *ueSCellCb
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 RgPrgSMacPMacCfgCfm
(
Pst             *pst,    
RgPrgCfgCfmInfo *cfgCfm
)
#else
PUBLIC S16 RgPrgSMacPMacCfgCfm(pst, cfgCfm)
Pst             *pst;    
RgPrgCfgCfmInfo *cfgCfm;
#endif
{
   Inst      inst = pst->dstInst;
   RgCellCb *cell;
   RgUeCb   *ue;
   TRC2(RgPrgSMacPMacCfgCfm);


   RG_IS_INST_VALID(inst);

   RGDBGPRM(pst->dstInst,(rgPBuf(pst->dstInst),
            "Config Confirm Rcvd from Inst %d ueId %d cellId %d\n",
            pst->srcInst, cfgCfm->ueId, cfgCfm->cellId));

   cell = rgCb[inst].cell;

   if ((ue = rgDBMGetUeCb(cell, cfgCfm->ueId)) == NULLP)
   {
      RGDBGERRNEW(inst,(rgPBuf(inst), 
               "[%d]Ue does not exist\n", cfgCfm->ueId));
      RETVALUE(RFAILED);
   }
   switch(cfgCfm->event)
   {
      /* cfgCount increment for all cases */
      case EVTPRGUESCELLLCHMODCFM:
      case EVTPRGUESCELLLCHDELCFM:
      case EVTPRGUESCELLLCHADDCFM:
         {
            ue->cfgCfmInfo.cfgCfgCount++;
            ue->cfgCfmInfo.mask |= cfgCfm->status;
            if(ue->cfgCfmInfo.numSCells == ue->cfgCfmInfo.cfgCfgCount)
            {
               ue->cfgCfmInfo.cfgCfgCount = 0;
               /* Send back confirmation status to RRC */
               rgUIMCrgCfgCfm(inst, ue->cfgCfmInfo.transId, ue->cfgCfmInfo.mask);
               ue->cfgCfmInfo.mask = 0;
               RGDBGINFO(inst,(rgPBuf(inst), "CRG Configuration request processed\n"));
            }
         }
         break;
      case EVTPRGUESCELLCFGCFM:
         {
            /*Commit Added SCell info to UeCb as we confirmation received */
            if(PRG_CFG_CFM_OK == cfgCfm->status)
            {
               ue->sCelInfo[pst->srcInst].isSCellAdded = TRUE;
               ue->sCelInfo[pst->srcInst].macInst = pst->srcInst;
               ue->sCelInfo[pst->srcInst].sCellId = cfgCfm->sCellId;
            }

            ue->cfgCfmInfo.cfgCfgCount++;
            ue->cfgCfmInfo.mask |= cfgCfm->status;
            if(ue->cfgCfmInfo.numSCells == ue->cfgCfmInfo.cfgCfgCount)
            {
               ue->cfgCfmInfo.cfgCfgCount = 0;
               /* Send back confirmation status to RRC */
               rgUIMCrgCfgCfm(inst, ue->cfgCfmInfo.transId, ue->cfgCfmInfo.mask);
               ue->cfgCfmInfo.mask = 0;
               RGDBGINFO(inst,(rgPBuf(inst), "CRG Configuration request processed\n"));
            }
         }
         break;
      default:
         {
            RGDBGERRNEW(inst,(rgPBuf(inst), "Invalid configuration confirm event %d\n",
                     cfgCfm->event));

            RETVALUE(RFAILED);
         }

   }
   RETVALUE(ROK);
}  /* RgPrgSMacPMacCfgCfm */

/**
 * @brief Function for handling UE release for SCELL
 * triggered from Primary Cell
 *
 * @details
 *
 *     Function : RgPrgPMacSMacUeSCellDelReq
 *     
 *        - This Function should be invoked by PCell of UE
 *        - Remove the UE context from SCELL corresponding to rnti.
 *           
 *  @param[in] Pst                 *pst
 *  @param[in] RgPrgUeSCellDelInfo *ueSCellDelInfo
 *  @return  ROK is SUCCESS 
 **/
#ifdef ANSI
PUBLIC S16 RgPrgPMacSMacUeSCellDelReq
(
Pst                 *pst,
RgPrgUeSCellDelInfo *ueSCellDelInfo
)
#else
PUBLIC S16 RgPrgPMacSMacUeSCellDelReq(pst, ueSCellDelInfo)
Pst                 *pst;
RgPrgUeSCellDelInfo *ueSCellDelInfo;
#endif
{
   Inst        inst     = pst->dstInst - RG_INST_START;
   RgCellCb    *sCell   = rgCb[inst].cell;
   RgUeCb      *sCellUe = NULLP;

   TRC2(RgPrgPMacSMacUeSCellDelReq)

   /* Checking for cell Cb because in case of shutdownReq it is possible that
    * cell is already deleted for this cell*/
   if(sCell == NULLP)
   {
      RETVALUE(ROK);
   }
   /* Retrive the UeCb from sec cell*/
   if ((sCellUe = rgDBMGetUeCb(sCell, ueSCellDelInfo->ueId)) == NULLP)
   {
      RGDBGERRNEW(inst, (rgPBuf(inst), "[%d]UE:does not exist in sCell(%d)\n",
               ueSCellDelInfo->ueId, sCell->cellId));
      RETVALUE(RFAILED);
   }
   
   /*PMAC_Reest: ueId and newRnti is different that means its a UeId change
    *request from PMAC to SMAC during PCell reestablishment
    */
  if(ueSCellDelInfo->ueId != ueSCellDelInfo->newRnti)
  {
     /* Retrive the UeCb from sec cell*/
     if ((rgDBMGetUeCb(sCell, ueSCellDelInfo->newRnti)) != NULLP)
     {
        RGDBGERRNEW(inst, (rgPBuf(inst), "[%d]UE:UE context already exist in\
                 sCell(%d)",ueSCellDelInfo->newRnti, sCell->cellId));
        RETVALUE(RFAILED);
     }

     rgDBMDelUeCb(sCell, sCellUe);

     sCellUe->ueId = ueSCellDelInfo->newRnti;

     /* Reset harq procs*/
     rgDHMUeReset(sCell, &sCellUe->dl.hqEnt);

     rgDBMInsUeCb(sCell, sCellUe);
  }
  else
  {
     rgDBMDelUeCb(sCell, sCellUe);
     rgCFGFreeUeCb(sCell, sCellUe);
  }

   RETVALUE(ROK);
} /* RgPrgPMacSMacUeSCellDelReq */
#endif /*LTE_ADV */
/**********************************************************************
 
         End of file:     gk_com.c@@/main/3 - Sat Jul 30 02:21:25 2011
 
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
/main/1      ---    sd    1. Initial Release.
/main/2      ---    sd    1. LTE MAC 2.1 release
/main/3    rg008.201 rsharon 1. Removed commented code.
/main/3      ---        gvj  1. Updated for LTE MAC Rel 3.1         
$SID$        ---    rt    1. LTE MAC 4.1 release
*********************************************************************91*/
