
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_mac.c

     Sid:      fc_smm_mac_t2k.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:52:21 2014

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=34;

#include "wr.h"
#include "wr_cmn.h"
#include "wr_emm.h"
#include "rgm.h"
#include "rgm.x"
#include "lrg.h"
#include "lrg.x"
#include "wr_lwr.h"
#include "wr_smm_init.h"
#include "wr_kpi.h"
#include "wr_kpiIds.h"
#include "wr_smm_smallcell.h"
#include "wr_msm_common.h"

#ifndef RG_POOL
  #define RG_POOL 0
#endif
#define WR_MAX_RGU_SAPS    2
#ifdef LTE_L2_MEAS
extern U32 glbMacMeasFlag;
PUBLIC S16 SmMiLrgSchL2MeasStartReq(Pst *pst,LrgSchMeasReqInfo *meas);
#endif
PRIVATE U32  numRguSaps = 0;
PUBLIC U8   macCfgInst = 0;

#ifdef WR_RSYS_OAM  
EXTERN S16 smStartTmr ARGS((PTR cb, S16 tmrEvnt,U32 delay));
EXTERN S16 smStopTmr ARGS((PTR cb, S16 tmrEvnt));
EXTERN Void smStaticCfgFailAlarm ARGS((Void));
#endif
extern MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];
  
/*
*
*       Fun:   Initialize MAC task.
*
*       Desc:  Invoked to create MAC TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  ve_se_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 smRgInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smRgInit(sysTskId)
SSTskId    sysTskId;
#endif
{
   U16      indx;

   /* ve002.102: Added trace macro */
   TRC2(smRgInit)
   /* Register LTE MAC TAPA Task */

   for(indx = 0; indx < wrSmDfltNumCells; indx++)
   {
      if (SRegTTsk((Ent)ENTRG, (Inst)indx, (Ttype)TTNORM, (Prior)PRIOR0,
               rgActvInit, (ActvTsk)rgActvTsk) != ROK) 
      {
         RETVALUE(RFAILED);
      } /* end of if statement */

      /* Attach LTE MAC TAPA Task */
      if (SAttachTTsk((Ent)ENTRG, (Inst)indx, sysTskId)!= ROK) 
      {
         RETVALUE(RFAILED);
      } /* end of if statement */
   }

   RLOG1(L_INFO, "LTE MAC Tapa Task successfullyregistered"
                 "and attached to %d", sysTskId);

   /* Register MAC SCHEDULER Task */
   if (SRegTTsk((Ent)ENTRG, (Inst)(wrSmDfltNumCells + SCH_INST_ID), 
               (Ttype)TTNORM, (Prior)PRIOR0,schActvInit, 
               (ActvTsk)schActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Attach RRC TAPA Task */
   if (SAttachTTsk((Ent)ENTRG, 
                   (Inst)(wrSmDfltNumCells + SCH_INST_ID),
                   sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RLOG1(L_INFO, "LTE SCH Tapa Task successfullyregistered"
                 "and attached to %d", sysTskId);
   RETVALUE(ROK);
} /* end of smRgInit */

  
#ifdef PHY_ERROR_LOGING   
PRIVATE Void smBuildRgSchUlAllocCfg(SmPhyCmd phyCmd);
#endif
PRIVATE U8 wrRgCfg = 0;

/*
 *
 *       Fun:    wrSmRgCfg - configure RG
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_rg_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmRgCfg
(
Void
)
#else
PUBLIC Void wrSmRgCfg(Void)
#endif /* ANSI */
{
   TRC2(wrSmRgCfg)
   wrRgCfg = 0;
   numRguSaps = 0;

#ifdef WR_RSYS_OAM  
   smStartTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR, SM_TMR_STATIC_CFG_TMR_VAL);
#endif

   smBuildRgGenCfg();
   smBuildRgUsapCfg(STRGUSAP, WR_SM_KWUL_INST);
   smBuildRgUsapCfg(STRGUSAP, WR_SM_KWDL_INST);
   smBuildRgUsapCfg(STCRGSAP, WR_SM_KWUL_INST);
   /* Build the TFU sap configuration of LTE MAC */
   smBuildRgTfuLsapCfg();

   RETVOID;
} /* end of wrSmRgCfg */

/*
*       Fun:   smBuildRgGenCfg
*
*       Desc:  Invoked to build MAC GEN CFG.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_mac.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgGenCfg
(
)
#else
PUBLIC S16 smBuildRgGenCfg(Void)
#endif
{  
   RgMngmt       rgMngmt;
   RgGenCfg      *genCfg=NULLP;
   Pst           pst;

   TRC2(smBuildRgGenCfg)

   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   genCfg   = &(rgMngmt.t.cfg.s.genCfg);

   /*----------- Fill General Configuration Parameters ---------*/
   
   genCfg->mem.region  = RG_MEM_REGION;
   genCfg->mem.pool    = RG_POOL;
   genCfg->tmrRes     = 10;
   genCfg->numRguSaps     = WR_MAX_RGU_SAPS;
   
#ifdef TIP_L2_L3_SPLIT
   genCfg->lmPst.dstProcId = SM_LL2_SM_PROC;
#else
   genCfg->lmPst.dstProcId = SM_SM_PROC;
#endif

   genCfg->lmPst.srcProcId = SM_RG_PROC;
   genCfg->lmPst.dstEnt    = ENTSM;
   genCfg->lmPst.dstInst   = 0;
   genCfg->lmPst.srcEnt    = ENTRG;
   genCfg->lmPst.srcInst   = macCfgInst;
   genCfg->lmPst.prior     = PRIOR0;
   genCfg->lmPst.route     = RTESPEC;
   genCfg->lmPst.region    = RG_MEM_REGION;
   genCfg->lmPst.pool      = RG_POOL;
   genCfg->lmPst.selector  = SM_SELECTOR_LC;
   

   /* Fill Header */
   rgMngmt.hdr.msgType             = TCFG;
   rgMngmt.hdr.msgLen              = 0;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STGEN;
   rgMngmt.hdr.seqNmb              = 0;
   rgMngmt.hdr.version             = 0;
   rgMngmt.hdr.transId             = 0;
  
   rgMngmt.hdr.response.prior      = PRIOR0;
   rgMngmt.hdr.response.route      = RTESPEC;
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;
   rgMngmt.hdr.response.selector   = SM_SELECTOR_LC;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstInst   = macCfgInst;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;

   RLOG0(L_DEBUG,"MAC Gen Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLrgCfgReq(&pst, &rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgGenCfg */

#ifdef PHY_ERROR_LOGING   

PUBLIC Void wrSmRgSchUlAllocCfg(SmPhyCmd phyCmd)
{

   TRC2(wrSmRgSchUlAllocCfg);
   smBuildRgSchUlAllocCfg(phyCmd);
   RETVOID;
}

/*
*       Fun:   smBuildRgSchUlAllocCfg
*
*       Desc:  Invoked to build MAC GEN CFG.
*
*       Ret:   ROK
*
*       Notes: None
*/

PRIVATE Void  smBuildRgSchUlAllocCfg(SmPhyCmd phyCmd)
{
   RgCntrl  *cntrl = NULLP;
   RgMngmt  rgMngmt;
   Pst      pst;

   TRC2(smBuildRgDbgCntrl)

   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(rgMngmt.t.cntrl);

   cntrl->action        =  AENA;
   cntrl->subAction     =  SAELMNT;

   if(phyCmd == PHY_CMD_START_TEST)
   {
      RLOG0(L_DEBUG,"<=========== PHY TESTING STARTED ============> ");
   }
   else if(phyCmd == PHY_CMD_STOP_TEST)
   {
      RLOG0(L_DEBUG,"<=========== PHY TESTING STOPPED ============> ");
   }
   else if(phyCmd == PHY_CMD_ENABLE_LOG)
   {
      RLOG1(L_DEBUG,"<=========== PHY LOGGING IS ENABLED for [%d] Seconds "
         "===========> ",  lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUlAllocInfoCbParams.logTime);

   }
   else if(phyCmd == PHY_CMD_DISABLE_LOG)
   {
      RLOG0(L_DEBUG,"<=========== PHY LOGGING IS DISABLED ============> ");
   }

   if(phyCmd != PHY_CMD_STOP_TEST)
      cntrl->s.rgSchUlAllocCntrl.testStart = TRUE;
   else
      cntrl->s.rgSchUlAllocCntrl.testStart = FALSE;

   if(phyCmd == PHY_CMD_ENABLE_LOG)
      smUlAllocInfoCb.enaLog = TRUE;
   else
      smUlAllocInfoCb.enaLog = FALSE;

   cntrl->s.rgSchUlAllocCntrl.enaLog = smUlAllocInfoCb.enaLog;
   cntrl->s.rgSchUlAllocCntrl.logTime = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUlAllocInfoCbParams.logTime;

   /* Fill Header */
   rgMngmt.hdr.msgType             = TCNTRL;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STGEN;
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.srcInst   = 0;
   pst.dstInst   = SCH_INST_ID;
   pst.region = smCb.init.region;

   /* Send the request to the MAC */
   SmMiLrgSchCntrlReq(&pst, &rgMngmt);

   RETVOID;
}
#endif /* PHY_ERROR_LOGING */

#ifdef MAC_SCH_STATS
/*
*       Fun:   smBuildRgStsReq
*
*       Desc:  Invoked to build MAC Statistics request.
*
*       Ret:   ROK
*
*       Notes: None
*/
#ifdef ANSI
PUBLIC S16 smBuildRgStsReq
(
)
#else
PUBLIC S16 smBuildRgStsReq (Void)
#endif
{
   RgMngmt       rgMngmt;
   RgSts   	     *sts;       /* MAC Statistics */
   Pst           pst;
   static int    iSecs= 0;

   TRC2(smBuildRgStsReq)
   {
      iSecs ++;
      /* Check the time */
      if(iSecs == lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUlAllocInfoCbParams.logTime)
      {
         iSecs = 0;
      }
      else
      {
         RETVALUE(ROK);
      }
      /* Check whether logging is enabled */
      if(!smUlAllocInfoCb.enaLog)
      {
         iSecs = 0;
         RETVALUE(ROK);
      }
   }

   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   sts = &(rgMngmt.t.sts);
   /* reset statistics to zero */
   sts->action = ZEROSTS; 

   /* Fill Header */
   rgMngmt.hdr.msgType             = TSTS;
   rgMngmt.hdr.msgLen              = 0;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STGEN;
   rgMngmt.hdr.seqNmb              = 0;
   rgMngmt.hdr.version             = 0;
   rgMngmt.hdr.transId             = 0;
  
   rgMngmt.hdr.response.prior      = PRIOR0;
   rgMngmt.hdr.response.route      = RTESPEC;
   rgMngmt.hdr.response.mem.region = smCb.init.region;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;
   rgMngmt.hdr.response.selector   = SM_SELECTOR_LC;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG,"MAC Statistics Req sent");

   /* Send the request to the MAC */
   SmMiLrgStsReq(&pst, &rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgStsReq */

#endif /* MAC_SCH_STATS */


/*
*
*       Fun:   smBuildCrgUsapCfg
*
*       Desc:  Invoked to build USAP CFG.(CRG)
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildCrgUsapCfg
(
)
#else
PUBLIC S16 smBuildCrgUsapCfg(Void)
#endif
{
   RgMngmt    rgMngmt;
   RgUpSapCfg  *uSap = NULLP;
   Pst         pst;

   TRC2(smBuildCrgUsapCfg)

   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   uSap   = &(rgMngmt.t.cfg.s.crgSap);
   
   uSap->mem.region = RG_MEM_REGION;
   uSap->mem.pool   = RG_POOL;
   uSap->suId       = 0;
   uSap->spId       = 0;
   uSap->procId     = SM_NH_PROC;
   uSap->ent        = ENTNH;
   uSap->inst       = SM_INST_ZERO;
   uSap->prior      = PRIOR0;
   uSap->route      = RTESPEC;
   uSap->selector   = SM_SELECTOR_LC;

   /* Fill Header */
   rgMngmt.hdr.msgType             = TCFG;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STCRGSAP;
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstInst   = macCfgInst;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region    = smCb.init.region;

   RLOG0(L_DEBUG,"MAC Crg USap Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLrgCfgReq(&pst, &rgMngmt);
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildRguUsapCfg
*
*       Desc:  Invoked to build USAP CFG.(RGU)
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRguUsapCfg
(
SpId sapId
)
#else
PUBLIC S16 smBuildRguUsapCfg(sapId)
SpId sapId
#endif
{
   RgMngmt     rgMngmt;
   RgUpSapCfg  *uSap = NULLP;
   Pst         pst;

   TRC2(smBuildRguUsapCfg)

   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   uSap   = &(rgMngmt.t.cfg.s.rguSap);
   
   uSap->mem.region = RG_MEM_REGION;
   uSap->mem.pool = RG_POOL;
   uSap->suId       = 0;
   uSap->spId       = sapId;
#ifndef UL_RLC_NET_CLUSTER
   uSap->procId     = SM_KW_PROC;
#else
   if(sapId == WR_SM_KWUL_INST)
   {
      uSap->procId     = SM_KW_UL_PROC;
   }else
   {/* MAC-DLRLC*/
      uSap->procId     = SM_KW_PROC;
   }
#endif
   uSap->ent        = ENTKW;
   uSap->inst       = sapId;
   uSap->prior      = PRIOR0;
   uSap->route      = RTESPEC;
   if (sapId == 0)
   {
#ifndef UL_RLC_NET_CLUSTER
      uSap->selector   = SM_SELECTOR_LWLC ;
#else
      uSap->selector   = SM_SELECTOR_LC ;
#endif 
   }
   else
   {
/*SANTOSH */
#ifdef SPLIT_RLC_DL_TASK
      uSap->selector   = 2 /*SM_SELECTOR_LWLC;*/;
#else 
      uSap->selector   = SM_SELECTOR_TC;
#endif 
   }


   /* Fill Header */
   rgMngmt.hdr.msgType             = TCFG;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STRGUSAP;
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstInst   = macCfgInst;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;

   RLOG0(L_DEBUG,"MAC Rgu USap Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLrgCfgReq(&pst, &rgMngmt);
   
   RETVALUE(ROK);
} /* end of smBuildRguUsapCfg */


/*
*
*       Fun:   smBuildRgUsapCfg
*
*       Desc:  Invoked to build USAP CFG.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgUsapCfg
(
U8  elemId,
SpId sapId
)
#else
PUBLIC S16 smBuildRgUsapCfg (elemId,sapId)
U8  elemId;
SpId sapId;
#endif
{
   TRC2(smBuildRgUsapCfg)

   switch (elemId)
   {
      case STRGUSAP:
         smBuildRguUsapCfg(sapId);
         break;

      case STCRGSAP:
         smBuildCrgUsapCfg();
         break;

      default:
         RLOG0(L_ERROR,"Invalid element Id");
         break;
   
   } /* end of switch statement */

   RETVALUE(ROK);
} /* end of smBuildRgUsapCfg */

/*
*
*       Fun:   smBuildRgSchInsCfg
*
*       Desc:  Invoked to build Scheduler Instance configuration.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgSchInsCfg
(
Void
)
#else
PUBLIC S16 smBuildRgSchInsCfg(Void)
#endif
{  
   RgMngmt       rgMngmt;
   RgSchInstCfg  *cfg = NULLP;
   Pst           pst;
   U8            sapIdx = 0;

   TRC2(smBuildRgSchInsCfg)

   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   cfg = &(rgMngmt.t.cfg.s.schInstCfg);
 
   /* Filling of Instance Id */
   cfg->instId = wrSmDfltNumCells + 1;
   /* Filling of Gen config */
   cfg->genCfg.mem.region = RG_MEM_REGION;
   cfg->genCfg.mem.pool = RG_POOL;
   cfg->genCfg.tmrRes = 10;
#ifdef LTE_ADV
   cfg->genCfg.forceCntrlSrbBoOnPCel = wrSmDfltForceCntrlSrbBoOnPCel;
   cfg->genCfg.isSCellActDeactAlgoEnable = wrSmDfltIsSCellActDeactAlgoEnable;
#endif/*LTE_ADV*/
   cfg->genCfg.startCellId     = 1;
#ifdef TIP_L2_L3_SPLIT
   cfg->genCfg.lmPst.dstProcId = SM_LL2_SM_PROC;
#else
   cfg->genCfg.lmPst.dstProcId = SM_SM_PROC;
#endif

   cfg->genCfg.lmPst.srcProcId = SM_RG_PROC;
   cfg->genCfg.lmPst.dstEnt    = ENTSM;
   cfg->genCfg.lmPst.dstInst   = 0;
   cfg->genCfg.lmPst.srcEnt    = ENTRG;
   cfg->genCfg.lmPst.srcInst   = wrSmDfltNumCells + 1;
   cfg->genCfg.lmPst.prior     = PRIOR0;
   cfg->genCfg.lmPst.route     = RTESPEC;
   cfg->genCfg.lmPst.region    = RG_MEM_REGION;
   cfg->genCfg.lmPst.pool      = RG_POOL;
   cfg->genCfg.lmPst.selector  = SM_SELECTOR_LC;
    
   if (wrSmDfltNumCells > 1)
   {
       RLOG1(L_ERROR,"Number of cells cannot exceed 1. Configured number of cells: %d",wrSmDfltNumCells);
       RETVALUE(RFAILED);
   }
    
   /* The number of RGR and TFU SAPs will be configured based on the nos. of cell. */
   cfg->numSaps = wrSmDfltNumCells;

   /* Filling the RGR sap information */
   for(sapIdx = 0; sapIdx < wrSmDfltNumCells; sapIdx++)
   {
      if ( sapIdx > LRG_MAX_SAPS_PER_INST)
      {
         RLOG1(L_ERROR,"Invalid sapIdx %d",sapIdx);
         RETVALUE(RFAILED);
      }

      cfg->rgrSap[sapIdx].selector  = SM_SELECTOR_LC;
      cfg->rgrSap[sapIdx].mem.region= RG_MEM_REGION;
      cfg->rgrSap[sapIdx].mem.pool  = RG_POOL;
      cfg->rgrSap[sapIdx].prior     = PRIOR0;
      cfg->rgrSap[sapIdx].procId    = SM_NX_PROC;
      cfg->rgrSap[sapIdx].ent       = ENTNX;
      cfg->rgrSap[sapIdx].inst      = SM_INST_ZERO;
      cfg->rgrSap[sapIdx].route     = RTESPEC;
      cfg->rgrSap[sapIdx].spId      = sapIdx;
      cfg->rgrSap[sapIdx].suId      = sapIdx;

      /* Filling the RGM sap information */
      cfg->rgmSap[sapIdx].selector  = RGM_SEL_LC;
      cfg->rgmSap[sapIdx].mem.region= smCb.init.region;
      cfg->rgmSap[sapIdx].mem.pool  = RG_POOL;
      cfg->rgmSap[sapIdx].prior     = PRIOR0;
      cfg->rgmSap[sapIdx].procId    = SM_RM_PROC;
      cfg->rgmSap[sapIdx].ent       = ENTRM;
      cfg->rgmSap[sapIdx].inst      = SM_INST_ZERO;
      cfg->rgmSap[sapIdx].route     = RTESPEC;
      cfg->rgmSap[sapIdx].spId      = 0;
      cfg->rgmSap[sapIdx].suId      = 0;


      /* Filling the TFU sap information of the scheduler */
      cfg->tfuSap[sapIdx].selector  = SM_SELECTOR_TC;
      cfg->tfuSap[sapIdx].mem.region= smCb.init.region;
      cfg->tfuSap[sapIdx].mem.pool  = RG_POOL;
      cfg->tfuSap[sapIdx].prior     = PRIOR0;
      cfg->tfuSap[sapIdx].procId    = SM_TF_PROC;
      cfg->tfuSap[sapIdx].ent       = ENTTF;
      cfg->tfuSap[sapIdx].inst      = SM_INST_ZERO;
      cfg->tfuSap[sapIdx].route     = RTESPEC;
      cfg->tfuSap[sapIdx].spId      = wrSmDfltNumCells + sapIdx;
      cfg->tfuSap[sapIdx].suId      = sapIdx;
      cfg->tfuSap[sapIdx].bndTmr.enb= TRUE;
      cfg->tfuSap[sapIdx].bndTmr.val= 10;
   }
 
   /* Fill Header */
   rgMngmt.hdr.msgType             = TCFG;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STSCHINST;
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.srcInst   = 0;
   pst.dstInst   = wrSmDfltNumCells + 1;
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG,"MAC Sch Cfg sent");

   SmMiLrgSchCfgReq(&pst, &rgMngmt); 

   RETVALUE(ROK);
} /* end of smBuildRgSchInsCfg */


/*
*
*       Fun:   smBuildRgTfuLsapCfg
*
*       Desc:  Invoked to build LSAP RGU CFG.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgTfuLsapCfg
(
Void
)
#else
PUBLIC S16 smBuildRgTfuLsapCfg(Void)
#endif
{
   RgMngmt       rgMngmt;
   RgLowSapCfg   *lSap=NULLP;
   Pst           pst;

   TRC2(smBuildRgTfuLsapCfg)

   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   lSap   = &(rgMngmt.t.cfg.s.tfuSap);
   
   lSap->mem.region  = RG_MEM_REGION;
   lSap->mem.pool    = RG_POOL;
   
   lSap->procId      = SM_TF_PROC;
   lSap->ent         = ENTTF;
   lSap->inst        = SM_INST_ZERO;
   lSap->spId        = macCfgInst;
   lSap->suId        = 0;
   lSap->bndTmr.enb  = TRUE;
   lSap->bndTmr.val  = 10;
   lSap->prior       = PRIOR0;
   lSap->route       = RTESPEC;
#ifndef CL_MAC_LWLC   
   lSap->selector    = SM_SELECTOR_TC;
#else
   lSap->selector    = SM_SELECTOR_LWLC;
#endif
   /* Fill Header */
   rgMngmt.hdr.msgType             = TCFG;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         =  STTFUSAP; 
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstInst   = macCfgInst;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;

   RLOG0(L_DEBUG,"MAC Tfu LSap Cfg sent");

   /* Send the request to the MAC*/
   SmMiLrgCfgReq(&pst, &rgMngmt);
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBindUnBindRgToTfuSap
*
*       Desc:  Invoked to bind and unbind MAC to TFU Sap
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_mac.c
*
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindRgToTfuSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindRgToTfuSap(U8 action)
#endif
{
   RgMngmt  rgMngmt;
   RgCntrl  *cntrl=NULLP;
   Pst      pst;
  
   TRC2(smBindUnBindRgToTfuSap)
 
   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   cntrl = &(rgMngmt.t.cntrl);

   cntrl->action             =  action;
   cntrl->subAction          =  SM_ZERO_VAL;
   cntrl->s.rgSapCntrl.suId  =  SM_ZERO_VAL;
   cntrl->s.rgSapCntrl.spId  =  macCfgInst;


   /* Fill Header */
   rgMngmt.hdr.msgType             = TCNTRL;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STTFUSAP; 
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstInst   = macCfgInst;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;
   
   if (action == ABND)
   {
      RLOG0(L_DEBUG,"Cntrl Req sent to MAC for TFU bind");
   }
   else
   {
      RLOG0(L_DEBUG,"Cntrl Req sent to MAC for TFU Unbind");
   }

   /* Send the request to the RRC */
   SmMiLrgCntrlReq(&pst, &rgMngmt);

   RETVALUE(ROK);
} /* end of smBindUnBindRgToTfuSap */

/*
*
*       Fun:   smBindUnBindRgSchToTfuSap
*
*       Desc:  Invoked to bind and Unbind Scheduler to TFU Sap
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_mac.
*
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindRgSchToTfuSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindRgSchToTfuSap(U8 action)
#endif
{
   RgMngmt  rgMngmt;
   RgCntrl  *cntrl=NULLP;
   Pst      pst;

   TRC2(smBindUnBindRgSchToTfuSap)
   
   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   cntrl = &(rgMngmt.t.cntrl);

   cntrl->action             =  action;
   cntrl->subAction          =  SM_ZERO_VAL;
   cntrl->s.rgSapCntrl.suId  =  macCfgInst;
   cntrl->s.rgSapCntrl.spId  =  (wrSmDfltNumCells + macCfgInst);


   /* Fill Header */
   rgMngmt.hdr.msgType             = TCNTRL;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STTFUSAP; 
   rgMngmt.hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt.hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.srcInst   = 0;
   pst.dstInst   = wrSmDfltNumCells + 1;
   pst.region = smCb.init.region;
   
   RLOG0(L_EVENT,"SCH Lrg Cntrl Req to Bind Tfu ");

   if (action == ABND)   
   {
      RLOG0(L_DEBUG,"SCH Lrg Cntrl Req to Bind Tfu ");
   }
   else
   {
      RLOG0(L_DEBUG,"SCH Lrg Cntrl Req to unBind Tfu ");
   }

   /* Send the request to the SCH */
   SmMiLrgSchCntrlReq(&pst, &rgMngmt);

   RETVALUE(ROK);
} /* end of smBindUnBindRgSchToTfuSap */

/*
*
*       Fun:   smBuildRgGenCntrl
*
*       Desc:  Invoked to Enable Alarms at RRC
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgGenCntrl
(
Void
)
#else
PUBLIC S16 smBuildRgGenCntrl(Void)
#endif
{
   RgCntrl  *cntrl = NULLP;
   RgMngmt  *rgMngmt = NULLP;
   Pst      pst;
  
   TRC2(smBuildRgGenCntrl)
 
   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&rgMngmt, sizeof(RgMngmt));
   if(NULLP == rgMngmt)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(rgMngmt, sizeof(RgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(rgMngmt->t.cntrl);

   cntrl->action        =  AENA;
   cntrl->subAction     =  SAUSTA;

   /* Fill Header */
   rgMngmt->hdr.msgType             = TCNTRL;
   rgMngmt->hdr.entId.ent           = ENTRG;
   rgMngmt->hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt->hdr.elmId.elmnt         = STGEN;
   rgMngmt->hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt->hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG,"MAC Gen Cntrl Req sent");

   /* Send the request to the RRC */
   SmMiLrgCntrlReq(&pst, rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgGenCntrl */
 
/**
 * @brief This function is used to send enable/disable control request to 
 * the MAC layers.
 *
 * @details
 *
 * Function: smBuildRgLogCntrl
 *
 * @param[in] actType
 * @param[in] mask
 *
 * @return Void
 */

#ifdef ANSI
PUBLIC S16 smBuildRgLogCntrl
(
 Bool actType,
 U32  mask
)
#else
PUBLIC S16 smBuildRgLogCntrl(actType, mask)
 Bool actType;
 U32  mask;
#endif
{
   RgCntrl  *cntrl = NULLP;
   RgMngmt  *rgMngmt = NULLP;
   Pst      pst;

   TRC2(smBuildRgLogCntrl)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&rgMngmt, sizeof(RgMngmt));
   if(NULLP == rgMngmt)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(rgMngmt, sizeof(RgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(rgMngmt->t.cntrl);

   if(actType == WR_ON)
   {
      cntrl->action        =  AENA;
   }
   else
   {
      cntrl->action        =  ADISIMM;
   }
#ifdef SS_DIAG
   cntrl->subAction     =  SALOG;
   cntrl->s.logMask = mask;
#endif
   /* Fill Header */
   rgMngmt->hdr.msgType             = TCNTRL;
   rgMngmt->hdr.entId.ent           = ENTRG;
   rgMngmt->hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt->hdr.elmId.elmnt         = STGEN;
   rgMngmt->hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt->hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   /* Send the request to the RRC */
   SmMiLrgCntrlReq(&pst, rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgLogCntrl */
 
/*
*
*       Fun:   smBuildRgDbgCntrl
*
*       Desc:  Invoked to Enable Debug at MAC
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgDbgCntrl
(
Void
)
#else
PUBLIC S16 smBuildRgDbgCntrl(Void)
#endif
{
   RgCntrl  *cntrl = NULLP;
   RgMngmt  *rgMngmt = NULLP;
   Pst      pst;

   TRC2(smBuildRgDbgCntrl)
   
   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&rgMngmt, sizeof(RgMngmt));
   if(NULLP == rgMngmt)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(rgMngmt, sizeof(RgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(rgMngmt->t.cntrl);

   cntrl->action        =  AENA;
   cntrl->subAction     =  SADBG;
/* wr004.102: Platform changes */
   cntrl->s.rgDbgCntrl.dbgMask = 0;

   /* Fill Header */
   rgMngmt->hdr.msgType             = TCNTRL;
   rgMngmt->hdr.entId.ent           = ENTRG;
   rgMngmt->hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt->hdr.elmId.elmnt         = STGEN;
   rgMngmt->hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt->hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG,"MAC Dbg Cntrl Req");

   /* Send the request to the RRC */
   SmMiLrgCntrlReq(&pst, rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgGenCntrl */

/*
*
*       Fun:   smBuildSchdDbgCntrl
*
*       Desc:  Invoked to Enable Debug at Schedular
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_mac.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSchdDbgCntrl
(
Void
)
#else
PUBLIC S16 smBuildSchdDbgCntrl(Void)
#endif
{
   RgCntrl  *cntrl = NULLP;
   RgMngmt  *rgMngmt = NULLP;
   Pst      pst;

   TRC2(smBuildSchdDbgCntrl)
   
   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&rgMngmt, sizeof(RgMngmt));
   if(NULLP == rgMngmt)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(rgMngmt, sizeof(RgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(rgMngmt->t.cntrl);

   cntrl->action        =  AENA;
   cntrl->subAction     =  SADBG;
   cntrl->s.rgDbgCntrl.dbgMask = 0;

   /* Fill Header */
   rgMngmt->hdr.msgType             = TCNTRL;
   rgMngmt->hdr.entId.ent           = ENTRG;
   rgMngmt->hdr.entId.inst          = SCH_INST_ID;
   rgMngmt->hdr.elmId.elmnt         = STGEN;
   rgMngmt->hdr.response.mem.region = RG_MEM_REGION;
   rgMngmt->hdr.response.mem.pool   = RG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
#ifdef DEBUGP
  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, "Schedular Dbg Cntrl Req\n"));
#endif

   /* Send the request to the RRC */
   SmMiLrgCntrlReq(&pst, rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildSchdDbgCntrl */

/* IPSec Recovery */

/*
*
*       Fun:   smBuildRgShutDownCntrl
*
*       Desc:  Invoked to shut down APP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgShutDownCntrl
(
Void
)
#else
PUBLIC S16 smBuildRgShutDownCntrl(Void)
#endif
{
   RgCntrl  *cntrl = NULLP;
   RgMngmt  rgMngmt; 
   Pst      pst;
  
   TRC2(smBuildRgShutDownCntrl)
 
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(rgMngmt.t.cntrl);

   cntrl->action        =  ASHUTDOWN;
   cntrl->subAction     =  NULLD;

   /* Fill Header */
   rgMngmt.hdr.msgType             = TCNTRL;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STGEN;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG,"MAC shut down Cntrl Req sent");

   /* Send the request to the RRC */
   SmMiLrgCntrlReq(&pst,&rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgGenCntrl */
 
/* IPSec Recovery */

/*
*
*       Fun:   Activate Task - initialize
*
*       Desc:  Invoked by system services to initialize a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  smrgexms.c
*
*/

#ifdef ANSI
PUBLIC S16 smRgActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smRgActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smRgActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
}


/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from KW
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   smrgexms.c
*
*/

#ifdef ANSI
PUBLIC S16 smRgActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smRgActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC3(smRgActvTsk)

      ret = ROK;

   switch(pst->event)
   {
#ifdef LCLRG
      case EVTLRGCFGCFM:             /* Config confirm */
         ret = cmUnpkLrgCfgCfm(SmMiLrgCfgCfm, pst, mBuf);
         break;
      case EVTLRGSCHCFGCFM:             /* Config confirm */
         ret = cmUnpkLrgSchCfgCfm(SmMiLrgSchCfgCfm, pst, mBuf);
         break;
      case EVTLRGCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLrgCntrlCfm(SmMiLrgCntrlCfm, pst, mBuf);
         break;
      case EVTLRGSCHCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLrgCntrlCfm(SmMiLrgSchCntrlCfm, pst, mBuf);
         break;
#ifdef MAC_SCH_STATS
      case EVTLRGSTSCFM:           /* Statistics confirm */
         ret = cmUnpkLrgStsCfm(SmMiLrgStsCfm, pst, mBuf);
         break;
#endif
#endif
         /*PRB: Review Tag*/
#ifdef LTE_L2_MEAS
      case EVTLRGSCHL2MEASCFM:
         ret = cmUnpkLrgSchL2MeasCfm(SmMiLrgSchL2MeasCfm, pst, mBuf);
         break;
      case EVTLRGSCHL2MEASSTOPCFM:
         ret = cmUnpkLrgSchL2MeasStopCfm(SmMiLrgSchL2MeasStopCfm, pst, mBuf);
         break;
#endif
    case EVTWRMACSCHDCFG:
    case EVTWRRRCSTKBND:
#ifndef LTE_ENB_PAL          
    case EVTWRCLCFG:
#endif
         smWrProcSm(pst->event);
         break;

         /*PRB: Review Tag*/
      default:
         SPutMsg(mBuf);
         ret = RFAILED;
         RLOG0(L_ERROR, "Received invalid event");
         break;
   }

   RETVALUE(ret);

} /* end of smRgActvTsk */


#if !(defined(LCSMMILRG)  && defined(RG))
#define PTSMMILRG
#endif

/* MAX Number of Service Providers of SM */
#define SM_MAX_LRG_PROV   3


#ifdef PTSMMILRG
EXTERN S16 PtLiLrgCfgReq (Pst * pst, RgMngmt * cfg);
EXTERN S16 PtLiLrgSchCfgReq (Pst * pst, RgMngmt * cfg);
EXTERN S16 PtLiLrgCntrlReq (Pst * pst, RgMngmt * cntrl);
EXTERN S16 PtLiLrgSchCntrlReq (Pst * pst, RgMngmt * cntrl);
#endif /*--#ifdef PTSMMILRG--*/


PRIVATE CONSTANT LrgCfgReq SmLiLrgCfgReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG
   cmPkLrgCfgReq,
#else
   PtLiLrgCfgReq,
#endif
#ifdef RG
   RgMiLrgCfgReq,
#else
   PtLiLrgCfgReq,
#endif
};

PRIVATE CONSTANT LrgSchCfgReq SmLiLrgSchCfgReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG
   cmPkLrgSchCfgReq,
#else
   PtLiLrgSchCfgReq,
#endif
#ifdef RG
   RgMiLrgSchCfgReq,
#else
   PtLiLrgSchCfgReq,
#endif
};

PRIVATE CONSTANT LrgCntrlReq SmLiLrgCntrlReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG
   cmPkLrgCntrlReq,
#else
   PtLiLrgCntrlReq,
#endif
#ifdef RG
   RgMiLrgCntrlReq,
#else
   PtLiLrgCntrlReq,
#endif
};

PRIVATE CONSTANT LrgSchCntrlReq SmLiLrgSchCntrlReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG
   cmPkLrgSchCntrlReq,
#else
   PtLiLrgSchCntrlReq,
#endif
#ifdef RG
   RgMiLrgSchCntrlReq,
#else
   PtLiLrgSchCntrlReq,
#endif
};

#ifdef MAC_SCH_STATS
PRIVATE CONSTANT LrgStsReq SmLiLrgStsReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG
   cmPkLrgStsReq,
#else
   PtLiLrgStsReq,
#endif
#ifdef RG
   RgMiLrgStsReq,
#else
#endif
};

/**************************************************************************
 *
 *      Fun:   Statistics request
 *
 *      Desc:  This function is used to send Statistics request to MAC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgStsReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 SmMiLrgStsReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{
   TRC3(SmMiLrgStsReq);

   (*SmLiLrgStsReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);
}
#endif /* MAC_SCH_STATS*/

#ifdef LTE_L2_MEAS
/*PRB: Review Tag*/
PRIVATE CONSTANT LrgSchL2MeasReq SmLiLrgSchL2MeasStartReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG 
   cmPkLrgSchL2MeasReq,
#else
   NULLP,
#endif
#ifdef RG
   RgMiLrgSchL2MeasReq,
#else
   NULLP,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchL2MeasReq
#else
   NULLP
#endif
};
PRIVATE CONSTANT LrgSchL2MeasStopReq SmLiLrgSchL2MeasStopReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG 
   cmPkLrgSchL2MeasStopReq,
#else
   NULLP,
#endif
#ifdef RG
   RgMiLrgSchL2MeasStopReq,
#else
   NULLP,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchL2MeasStopReq
#else
   NULLP
#endif
};
PRIVATE CONSTANT LrgSchL2MeasSendReq SmLiLrgSchL2MeasSendReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMMILRG 
   cmPkLrgSchL2MeasSendReq,
#else
   NULLP,
#endif
#ifdef RG
   RgMiLrgSchL2MeasSendReq,
#else
   NULLP,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchL2MeasSendReq
#else
   NULLP
#endif
};
/*PRB: Review Tag*/
#endif

/**************************************************************************
 *
 *      Fun:   Configuration request
 *
 *      Desc:  This function is used to configure RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 SmMiLrgCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{

   /* wr002.102: Corrected function name in trace macro */
   TRC3(SmMiLrgCfgReq);

   (*SmLiLrgCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}

/**************************************************************************
 *
 *      Fun:   Configuration request
 *
 *      Desc:  This function is used to configure RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 SmMiLrgSchCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{

   /* wr002.102: Corrected function name in trace macro */
   TRC3(SmMiLrgSchCfgReq);

   (*SmLiLrgSchCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}


/**************************************************************************
 *
 *      Fun:   Control request
 *
 *      Desc:  This function is used to send the control request RLC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 SmMiLrgCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{

   TRC3(SmMiLrgCntrlReq);

   (*SmLiLrgCntrlReqMt[pst->selector])(pst, cntrl);

   RETVALUE(ROK);

}

/**************************************************************************
 *
 *      Fun:   SCH  Control request
 *
 *      Desc:  This function is used to send the control request MAC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 SmMiLrgSchCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{

   TRC3(SmMiLrgSchCntrlReq);

   (*SmLiLrgSchCntrlReqMt[pst->selector])(pst, cntrl);

   RETVALUE(ROK);

}
/*PRB: Review Tag*/

#ifdef LTE_L2_MEAS
/**************************************************************************
 *
 *      Fun:   SCH  Measurement request
 *
 *      Desc:  This function is used to build and send L2 Meas req
 *             to MAC layer 
 *
 *      Ret:   S16 ret
 *
 *      Notes: None
 *
 *      File:  wr_smm_mac.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 smSndRgSchL2MeasStartReq
(
U16   measType
)
#else
PUBLIC S16 smSndRgSchL2MeasStartReq(measType)
U16    measType;
#endif
{
   Pst pst;
   U8 qciIdx;
   LrgSchMeasReqInfo measInfo;

   TRC3(smSndRgSchL2MeasStartReq);

   RLOG1(L_DEBUG,"meassType [%d]",measType);
   SM_SET_ZERO(&measInfo, sizeof(LrgSchMeasReqInfo));
   SM_SET_ZERO(&pst, sizeof(Pst)); 
   /*Fill Pst Structure*/
   /*Fill Pst Structure*/
   pst.selector  = SM_SELECTOR_LC; /*Currently hardCoded to 1 to accelerate debugging*/
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = wrCb.rgrSap[0]->pst.dstEnt;
   pst.dstProcId = wrCb.rgrSap[0]->pst.dstProcId;
   pst.srcProcId = wrCb.rgrSap[0]->pst.srcProcId;
   pst.dstInst = wrCb.rgrSap[0]->pst.dstInst;
   pst.srcInst = wrCb.rgrSap[0]->pst.srcInst;


   measInfo.hdr.msgType             = 0;
   measInfo.hdr.msgLen              = 0;
   measInfo.hdr.entId.ent           = ENTRG;
   measInfo.hdr.entId.inst          = SM_INST_ZERO;
   measInfo.hdr.elmId.elmnt         = STGEN;
   measInfo.hdr.seqNmb              = 0;
   measInfo.hdr.version             = 0;
   measInfo.hdr.response.selector = SM_SELECTOR_LC;
   measInfo.hdr.response.prior = PRIOR0;
   measInfo.hdr.response.route = RTESPEC;
   measInfo.hdr.response.mem.region = smCb.init.region;
   measInfo.hdr.response.mem.pool = RG_POOL;
   measInfo.hdr.transId = (kpiInfo.transId)++;

   /*Fill desired Measurement Info*/
   measInfo.cellId = 1;
   measInfo.measType = measType; 
   measInfo.timePrd = 0; 
   measInfo.avgPrbQciDl.numQci = LRG_MAX_QCI_PER_REQ - 1; 
   for(qciIdx =0; qciIdx < measInfo.avgPrbQciDl.numQci; qciIdx++)
   {
      measInfo.avgPrbQciDl.qci[qciIdx] = qciIdx+1;
   }
   measInfo.avgPrbQciUl.numQci = LRG_MAX_QCI_PER_REQ - 1; 
   for(qciIdx =0; qciIdx < measInfo.avgPrbQciUl.numQci;qciIdx++)
   {
      measInfo.avgPrbQciUl.qci[qciIdx] = qciIdx+1;
   }
   measInfo.nmbActvUeQciUl.sampPrd = 100;

   measInfo.nmbActvUeQciUl.numQci = LRG_MAX_QCI_PER_REQ - 1;
   for(qciIdx =0; qciIdx < measInfo.nmbActvUeQciUl.numQci; qciIdx++)
   {
      measInfo.nmbActvUeQciUl.qci[qciIdx] = qciIdx+1;
   }
   measInfo.nmbActvUeQciDl.sampPrd = 100; 

   measInfo.nmbActvUeQciDl.numQci = LRG_MAX_QCI_PER_REQ -1;
   for(qciIdx =0; qciIdx < measInfo.nmbActvUeQciDl.numQci; qciIdx++)
   {
      measInfo.nmbActvUeQciDl.qci[qciIdx] = qciIdx+1;
   }

   SmMiLrgSchL2MeasStartReq(&pst,&measInfo);
   RETVALUE(ROK);
}/*smSndRgSchL2MeasStartReq*/

/**************************************************************************
 *           
 *      Fun:   SCH  Measurement Stop request
 * 
 *      Desc:  This function is used to build and send L2 Meas Stop req
 *             to MAC layer 
 * 
 *      Ret:   S16 ret
 * 
 *      Notes: None
 *
 *      File:  wr_smm_mac.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 smSndRgSchL2MeasStopReq
(
U16   measType
)
#else
PUBLIC S16 smSndRgSchL2MeasStopReq(measType)
U16    measType;
#endif
{
   LrgSchMeasStopReqInfo measInfo;
   Pst           pst;

   TRC3(smSndRgSchL2MeasStopReq);

   RLOG1(L_DEBUG,"meassType [%d]",measType);
   SM_SET_ZERO(&measInfo, sizeof(LrgSchMeasStopReqInfo));
   SM_SET_ZERO(&pst, sizeof(Pst));
   /*Fill Pst Structure*/
   pst.selector = SM_SELECTOR_LC;
   pst.srcEnt = ENTSM;
   pst.dstEnt = wrCb.rgrSap[0]->pst.dstEnt;
   pst.dstProcId = wrCb.rgrSap[0]->pst.dstProcId;
   pst.srcProcId = wrCb.rgrSap[0]->pst.srcProcId;
   pst.dstInst = wrCb.rgrSap[0]->pst.dstInst;
   pst.srcInst = wrCb.rgrSap[0]->pst.srcInst;
   /*filling MeasInfo structure*/
   measInfo.hdr.msgType             = 0;
   measInfo.hdr.msgLen              = 0;
   measInfo.hdr.entId.ent           = ENTRG;
   measInfo.hdr.entId.inst          = SM_INST_ZERO;
   measInfo.hdr.elmId.elmnt         = STGEN;
   measInfo.hdr.seqNmb              = 0;
   measInfo.hdr.version             = 0;
   measInfo.hdr.response.selector = SM_SELECTOR_LC;
   measInfo.hdr.response.prior = PRIOR0;
   measInfo.hdr.response.route = RTESPEC;
   measInfo.hdr.response.mem.region = smCb.init.region;
   measInfo.hdr.response.mem.pool = RG_POOL;
   measInfo.measType = measType;
   measInfo.cellId = 1;
   measInfo.hdr.transId = (kpiInfo.transId)++;

   SmMiLrgSchL2MeasStopReq(&pst,&measInfo);

   RETVALUE(ROK);
}/*smSndRgSchL2MeasStopReq*/

/**************************************************************************
 *           
 *      Fun:   SCH  Measurement Stop request
 * 
 *      Desc:  This function is used to build and send L2 Meas Stop req
 *             to MAC layer 
 * 
 *      Ret:   S16 ret
 * 
 *      Notes: None
 *
 *      File:  wr_smm_mac.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 smSndRgSchL2MeasSendReq
(
U16   measType
)
#else
PUBLIC S16 smSndRgSchL2MeasSendReq(measType)
U16    measType;
#endif
{
   LrgSchMeasSndReqInfo measInfo;
   Pst               pst;

   TRC3(smSndRgSchL2MeasSendReq);

   SM_SET_ZERO(&measInfo, sizeof(LrgSchMeasSndReqInfo));
   SM_SET_ZERO(&pst, sizeof(Pst));
   /*Fill Pst Structure*/
   pst.selector = SM_SELECTOR_LC;
   pst.srcEnt = ENTSM;
   pst.dstEnt = wrCb.rgrSap[0]->pst.dstEnt;
   pst.dstProcId = wrCb.rgrSap[0]->pst.dstProcId;
   pst.srcProcId = wrCb.rgrSap[0]->pst.srcProcId;
   pst.dstInst = wrCb.rgrSap[0]->pst.dstInst;
   pst.srcInst = wrCb.rgrSap[0]->pst.srcInst;
   measInfo.hdr.msgType             = 0;
   measInfo.hdr.msgLen              = 0;
   measInfo.hdr.entId.ent           = ENTRG;
   measInfo.hdr.entId.inst          = SM_INST_ZERO;
   measInfo.hdr.elmId.elmnt         = STGEN;
   measInfo.hdr.seqNmb              = 0;
   measInfo.hdr.version             = 0;
   measInfo.hdr.response.selector = SM_SELECTOR_LC;
   measInfo.hdr.response.prior = PRIOR0;
   measInfo.hdr.response.route = RTESPEC;
   measInfo.hdr.response.mem.region = smCb.init.region;
   measInfo.hdr.response.mem.pool = RG_POOL;
   measInfo.measType = measType;
   measInfo.cellId = 1;
   measInfo.timePrd = 0;
   measInfo.hdr.transId = (kpiInfo.transId)++;
   RLOG2(L_INFO,"measType [%d] transId(%d)",measType, kpiInfo.transId);
   SmMiLrgSchL2MeasSendReq(&pst,&measInfo);

   RETVALUE(ROK);
}/*smSndRgSchL2MeasSendReq*/

/**************************************************************************
 *
 *      Fun:   SCH  Measurement request
 *
 *      Desc:  This function is used to send the Measurement request MAC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasStartReq
(
Pst * pst,
LrgSchMeasReqInfo *meas 
)
#else
PUBLIC S16 SmMiLrgSchL2MeasStartReq(pst, meas)
Pst * pst;
LrgSchMeasReqInfo *meas ;
#endif
{
   TRC3(SmMiLrgSchL2MeasStartReq);

   (*SmLiLrgSchL2MeasStartReqMt[pst->selector])(pst, meas);

   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   SCH  Measurement Stop request
 *
 *      Desc:  This function is used to send the Measurement stop request to 
 *              MAC layer
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasStopReq
(
Pst *pst,
LrgSchMeasStopReqInfo *meas
)
#else
PUBLIC S16 SmMiLrgSchL2MeasStopReq(pst, meas)
Pst *pst;
LrgSchMeasStopReqInfo *meas;
#endif
{
   TRC3(SmMiLrgSchL2MeasStopReq);

   (*SmLiLrgSchL2MeasStopReqMt[pst->selector])(pst, meas);

   RETVALUE(ROK);
}/*SmMiLrgSchL2MeasStopReq*/

/**************************************************************************
 *
 *      Fun:   SCH  Measurement Stop request
 *
 *      Desc:  This function is used to send the Measurement stop request to 
 *              MAC layer
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasSendReq
(
Pst *pst,
LrgSchMeasSndReqInfo *meas
)
#else
PUBLIC S16 SmMiLrgSchL2MeasSendReq(pst, meas)
Pst *pst;
LrgSchMeasSndReqInfo *meas;
#endif
{
   TRC3(SmMiLrgSchL2MeasSendReq);

   (*SmLiLrgSchL2MeasSendReqMt[pst->selector])(pst, meas);

   RETVALUE(ROK);
}/*SmMiLrgSchL2MeasSendReq*/

#endif
/*PRB: Review Tag*/

#ifdef PTSMMILRG
/**************************************************************************
 *
 *      Fun:   Portable Configuration request
 *
 *      Desc:  This function is used to send the configuration request RLC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiLrgCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 PtLiLrgCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{
   TRC3(PtLiLrgCfgReq);

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 PtLiLrgSchCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 PtLiLrgSchCfgReq(pst, cfg)
Pst * pst; 
RgMngmt * cfg;
#endif
{
   TRC3(PtLiLrgSchCfgReq);

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   Portable Control request
 *
 *      Desc:  This function is used to send the control request RLC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_rg_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiLrgCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 PtLiLrgCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{
   TRC3(PtLiLrgCntrlReq);

   UNUSED(pst);
   UNUSED(cntrl);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 PtLiLrgSchCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 PtLiLrgSchCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{
   TRC3(PtLiLrgSchCntrlReq);

   UNUSED(pst);
   UNUSED(cntrl);

   RETVALUE(ROK);
}

#ifdef LTE_L2_MEAS
/*PRB: Review Tag*/
/**
* @brief This API is used to send a 
L2 Measurement  Request from LM to MAC(Scheduler Instance).
*
* @details
*
*     Function : PtLiLrgSchL2MeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchL2MeasReqInfo *  meas
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgSchL2MeasReq
(
Pst * pst,
LrgSchMeasReqInfo *meas
)
#else
PUBLIC S16 PtLiLrgSchL2MeasReq(pst, meas)
Pst * pst;
LrgSchMeasReqInfo  * meas;
#endif
{
   TRC3(PtLiLrgSchL2MeasReq);

   UNUSED(pst);
   UNUSED(meas);

   RETVALUE(ROK);
}
/*PRB: Review Tag*/
#endif

#endif /* PTSMMILRG */

/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Managemer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLrgCfgCfm
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgCfgCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   Pst      rgPst;

   TRC2(SmMiLrgCfgCfm);

   SM_SET_ZERO(&rgPst, sizeof(Pst));

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STGEN:
            wrRgCfg |= WR_RG_GEN_CFG;
            break;      

         case STRGUSAP:
            wrRgCfg |= WR_RG_RGU_SAP_CFG;
            numRguSaps ++;
            break;
         case STCRGSAP:
            wrRgCfg |= WR_RG_CRG_SAP_CFG;
            break;
         case STTFUSAP:
            wrRgCfg |= WR_RG_TFU_SAP_CFG;
            break;
         default:
            break;
      } /* end of switch statement */

      RLOG1(L_DEBUG,"MAC Cfg Cfm received for the element[%d]",
         cfm->hdr.elmId.elmnt);

      if ((wrRgCfg == WR_SM_RG_CONFIGURED) 
          && (numRguSaps == WR_MAX_RGU_SAPS)
         )
      {
#ifdef WR_RSYS_OAM  
         smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif

#ifndef LTE_ENB_PAL          
         if (smCb.reCfg == TRUE)
         {
            smCb.smState = WR_SM_STATE_CL_CFG_DONE;
#ifndef  TIP_L2_L3_SPLIT
            WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTRG,0,0, EVTWRENBDEBUGS, WR_POOL, SM_SELECTOR_LC);
#else      
            WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTRG,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LC);
#endif
         }
         else
#endif
         {
            macCfgInst++;
            if(wrSmDfltNumCells == macCfgInst)
            {
               smCb.smState = WR_SM_STATE_MAC_CFG_DONE;
#ifdef  TIP_L2_L3_SPLIT
               WR_FILL_PST(rgPst, SM_LL2_SM_PROC, SM_RG_PROC, ENTSM, ENTRG,0,0, EVTWRMACSCHDCFG, WR_POOL, SM_SELECTOR_LC);
#else
               WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRMACSCHDCFG, WR_POOL, SM_SELECTOR_LC);
#endif
            }
            else
            {
#ifdef  TIP_L2_L3_SPLIT
               WR_FILL_PST(rgPst, SM_LL2_SM_PROC, SM_RG_PROC, ENTSM, ENTRG,0,0, EVTWRMACCFG, WR_POOL, SM_SELECTOR_LC);
#else
               WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRMACCFG, WR_POOL, SM_SELECTOR_LC);
#endif
            }
         }



         if(wrSmSelfPstMsg(&rgPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed at MAC Configuration. ");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success at MAC Configuration. ");
         } /* end of else part */

      }  /* end of wrRgCfg == WR_SM_RG_CONFIGURED */
   } /* end of if statement cfm->cfm.status == LCM_PRIM_OK */
   else
   {
      RLOG1(L_ERROR,"SmMiLrgCfgCfm Configuration not OK for element[%d]",
         cfm->hdr.elmId.elmnt);
#ifdef WR_RSYS_OAM  
      /*timer stop :: Raised an alarm */
      smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
      smCb.cfgCb.alarm.severity  = SM_ALARM_SEVERITY_MAJOR;
      smCb.cfgCb.alarm.causeType = SM_ALARM_CAUSE_TYPE_ERR_IND;
      smCb.cfgCb.alarm.causeVal  = SM_ALARM_CAUSE_VAL_INIT_FAIL;
      smStaticCfgFailAlarm();
#endif
   }

   RETVALUE(ROK);
} /* end of SmMiLkwCfgCfm */

/*
*
*       Fun:   Sch Config Confirm
*
*       Desc:  This function is used to handle config cfm from sch 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLrgSchCfgCfm
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgSchCfgCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   Pst      rgPst;
   SM_SET_ZERO(&rgPst, sizeof(Pst));

   TRC2(SmMiLrgSchCfgCfm);
   /* IPSec */
   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      //if (smCb.smState == WR_SM_STATE_PDCP_SHUTDWN_DONE)
      if (smCb.smState == WR_SM_STATE_RLC_UL_SHUTDWN_DONE)
      {
        smCb.smState = WR_SM_STATE_MAC_SHUTDWN_DONE;
         RLOG0(L_ALWAYS, "MAC SHUTDOWN SUCCESSFULLY PERFORMED.");
#ifdef LTE_ENB_PAL
         WR_FILL_PST(rgPst,SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWREGTPSHUT, WR_POOL, SM_SELECTOR_LC);
#else
         WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWREGTPSHUT, WR_POOL, SM_SELECTOR_LC);
#endif
         if(wrSmSelfPstMsg(&rgPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed at MAC SHUTDOWN Configuration.");
         }
         else
         {
            RLOG0(L_WARNING,"MAC SHUTDOWN SUCCESSFULLY PERFORMED"); 
         } /* end of else part */
      }
   }

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STSCHINST:
            wrRgCfg |= WR_RG_SCH_INS_CFG;
            break;
         default:
            RLOG1(L_ERROR, "Received Cfg Cfm with unknown element id[%d]",
               cfm->hdr.elmId.elmnt);
            break;
      } /* end of switch statement */
      RLOG1(L_DEBUG,"SCH Cfg Cfm received for the element[%d]",
            cfm->hdr.elmId.elmnt);
      if (wrRgCfg == WR_SM_SCH_CONFIGURED)
      {
         smCb.smState = WR_SM_STATE_MAC_SCHD_CFG_DONE;
#ifdef LTE_ENB_PAL          
#ifdef  TIP_L2_L3_SPLIT
         WR_FILL_PST(rgPst, SM_LL2_SM_PROC, SM_RG_PROC, ENTSM, ENTRG,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LC);
#else         
         WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRENBDEBUGS, WR_POOL, SM_SELECTOR_LC);
#endif
#else                   
         if (smCb.reCfg == TRUE)
         {
            WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRENBDEBUGS, WR_POOL, SM_SELECTOR_LC);
         }
         else
         {
#ifdef  TIP_L2_L3_SPLIT
            WR_FILL_PST(rgPst, SM_LL2_SM_PROC, SM_RG_PROC, ENTSM, ENTRG,0,0, EVTWRCLCFG, WR_POOL, SM_SELECTOR_LC);
#else         
            WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRCLCFG, WR_POOL, SM_SELECTOR_LC);
#endif
         }
#endif
         if(wrSmSelfPstMsg(&rgPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed at MAC Configuration.");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success at MAC Configuration.");
         } /* end of else part */

      }  /* end of wrRgCfg == WR_SM_RG_CONFIGURED */
   }
   RETVALUE(ROK);
}
/*
*
*       Fun:   Control Confirm
*
*       Desc:  This function is used by to present control confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLrgCntrlCfm
(
Pst            *pst,
RgMngmt        *cntrl
)
#else
PUBLIC S16 SmMiLrgCntrlCfm(pst, cntrl)
Pst            *pst;
RgMngmt        *cntrl;
#endif
{
   Pst  rgPst;

   TRC2(SmMiLrgCntrlCfm);

   SM_SET_ZERO(&rgPst, sizeof(Pst));
   /* IPSec */
   if (cntrl->cfm.status == LCM_PRIM_OK)
   {
      if (smCb.smState == WR_SM_STATE_MAC_SCH_SHUTDWN_DONE)
      {
        smCb.smState = WR_SM_STATE_MAC_SHUTDWN_DONE;
         RLOG0(L_ALWAYS, "MAC SHUTDOWN SUCCESSFULLY PERFORMED.");
#ifdef LTE_ENB_PAL
         WR_FILL_PST(rgPst, SM_SM_PROC,  SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWREGTPSHUT, WR_POOL, SM_SELECTOR_LC);
#else
         WR_FILL_PST(rgPst, SM_SM_PROC,  SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWREGTPSHUT, WR_POOL, SM_SELECTOR_LC);
#endif
         if(wrSmSelfPstMsg(&rgPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed at MAC Shutdown Configuration.");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success at MAC Shutdown Configuration.");
         }
         RETVALUE(ROK);
   }
 }

   if (cntrl->hdr.elmId.elmnt == STTFUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF MAC WITH CL SUCCESSFUL");

            smCb.smState = WR_SM_STATE_RRC_STK_UNBND_DONE;
            WR_FILL_PST(rgPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRX2APSTKUNBND,
               WR_POOL, SM_SELECTOR_TC);
            if(wrSmSelfPstMsg(&rgPst) != ROK)
            {
               RLOG1(L_ERROR,"Failure at Self Pst.[%d]", smCb.smState);
            }
         }
         RETVALUE(ROK);
      }
      if (cntrl->cfm.status == LCM_PRIM_OK)
      {
            RLOG0(L_DEBUG,"BIND OF MAC WITH CL SUCCESSFUL ");
         macCfgInst++;
         if(macCfgInst < wrSmDfltNumCells)
         {
            /*Bind the MAC lower SAP with CL */
            smBindUnBindRgToTfuSap(ABND);
         }
         else
         {
            /* Initiate control request for binding Sch with TFU sap*/
            macCfgInst = 0;
            smBindUnBindRgSchToTfuSap(ABND);
         }
      } /* end of if statement */
      else if (cntrl->cfm.status == LCM_PRIM_OK_NDONE)
      {
         RLOG0(L_INFO,"BIND OF MAC WITH CL IS IN PROGRESS ");
      }
      else 
      {
         RLOG0(L_FATAL,"BIND OF MAC WITH CL FAILED ");
      }
   } /* end of if statement */
   else
   {
      if (cntrl->cfm.status == LCM_PRIM_OK)
      {
         if((smCfgCb.rgDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_RG_DBG_MASK))
         {
            /* Update DbgMsk */
            smCfgCb.smDbgMsk = (smCfgCb.smDbgMsk | WR_SM_RG_DBG_MASK);
            /* Trigger Debug Cntrl */
            wrSmHdlEnbDebugs(EVTWRENBDEBUGS);
         }
      }
   }

   RETVALUE(ROK);
} /* end of SmMiLrgCntrlCfm */

/*
*
*       Fun:   SCH Control Confirm
*
*       Desc:  This function is used by to present control confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCntrlCfm
(
Pst            *pst,
RgMngmt        *cntrl
)
#else
PUBLIC S16 SmMiLrgSchCntrlCfm(pst, cntrl)
Pst            *pst;
RgMngmt        *cntrl;
#endif
{
   Pst  rgPst;

   TRC2(SmMiLrgSchCntrlCfm);

   SM_SET_ZERO(&rgPst, sizeof(Pst));
   /* IPSec */
   if (cntrl->cfm.status == LCM_PRIM_OK)
   {
      if (smCb.smState == WR_SM_STATE_RLC_UL_SHUTDWN_DONE)
      {
        smCb.smState = WR_SM_STATE_MAC_SCH_SHUTDWN_DONE;
         RLOG0(L_ALWAYS, "MAC Scheduler SHUTDOWN SUCCESSFULLY PERFORMED. ");
#ifdef LTE_ENB_PAL
         WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRMACSHUT, WR_POOL, SM_SELECTOR_LC);
#else
         WR_FILL_PST(rgPst, SM_SM_PROC, SM_RG_PROC, ENTSM, ENTWR,0,0, EVTWRMACSHUT, WR_POOL, SM_SELECTOR_LC);
#endif
         if(wrSmSelfPstMsg(&rgPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed at MAC Scheduler SHUTDOWN Configuration.");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success at MAC Scheduler SHUTDOWN Configuration.");
         }
         RETVALUE(ROK);
     }
   }      
   if (cntrl->hdr.elmId.elmnt == STTFUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF SCH WITH CL SUCCESSFUL");
            /* Unbind MAC with CL */
            smBindUnBindRgToTfuSap(AUBND);
         }
         RETVALUE(ROK);
      }
      if (cntrl->cfm.status == LCM_PRIM_OK)
      {
         RLOG0(L_DEBUG,"BIND OF SCH WITH CL SUCCESSFUL ");
         macCfgInst++;
         if(macCfgInst < wrSmDfltNumCells)
         {
            smBindUnBindRgSchToTfuSap(ABND);
         }
         else
         {
            macCfgInst = 0;
            smBindUnBindKwToRguSap(WR_SM_KW_INST,ABND);
         }
      } /* end of if statement */
      else if (cntrl->cfm.status == LCM_PRIM_OK_NDONE)
      {
         RLOG0(L_INFO,"BIND OF SCH WITH CL IS IN PROGRESS ");
      }
      else 
      {
         RLOG0(L_FATAL,"BIND OF SCH WITH CL FAILED ");
      }
   } /* end of if statement */

   RETVALUE(ROK);
} /* end of SmMiLrgSchCntrlCfm */



/*
*
*       Fun:   Status Ind
*
*       Desc:  This function is used by to present Status Ind
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLrgStaInd
(
Pst            *pst,
RgMngmt        *staInd
)
#else
PUBLIC S16 SmMiLrgStaInd(pst, staInd)
Pst            *pst;
RgMngmt        *staInd;
#endif
{
   TRC2(SmMiLrgStaInd)

   UNUSED(pst);
   UNUSED(staInd);

   RETVALUE(ROK);
} /* end of SmMiLrgStaInd */


/*
*
*       Fun:   Trc Ind
*
*       Desc:  This function is used by to present Trc Ind
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLrgTrcInd 
(
Pst            *pst,
RgMngmt        *trcInd,
Buffer         *mBuf
)
#else
PUBLIC S16 SmMiLrgTrcInd(pst, trcInd, mBuf)
Pst            *pst;
RgMngmt        *trcInd;
Buffer         *mBuf;
#endif
{
   TRC2(SmMiLrgTrcInd)

   UNUSED(pst);
   UNUSED(trcInd);
   UNUSED(mBuf);

   RETVALUE(ROK);
} /* end of SmMiLrgTrcInd */


/*
*
*       Fun:   Sta Cfm
*
*       Desc:  This function is used by to present Sta Cfm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLrgStaCfm
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgStaCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC2(SmMiLrgStaCfm)

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ROK);
} /* end of SmMiLrgStaCfm */

/*
*
*       Fun:   Sta Cfm
*
*       Desc:  This function is used by to present Sta Cfm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/

#ifdef LTE_L2_MEAS
/*PRB: Review Tag*/
/**
 * @brief L2 Measurement Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgSchL2MeasCfm
 *     
 *     Enqueues the Config Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasCfm
(
Pst               *pst,
LrgSchMeasCfmInfo *schL2MeasCfm
)
#else
PUBLIC S16 SmMiLrgSchL2MeasCfm(pst, schL2MeasCfm)
Pst               *pst;
LrgSchMeasCfmInfo *schL2MeasCfm;
#endif
{
   U16 indx;
   KpiId kpiId;
   U32 measPrd;

   TRC3(SmMiLrgSchL2MeasCfm);

   UNUSED(pst);
#ifdef WR_RSYS_KPI

   kpiInfo.numOfRcvdL2MeasCfm++;
   kpiInfo.measConfigRecv |= WR_MEAS_MAC_CFG;
   RLOG0(L_DEBUG,"Received confirmation");
   if(kpiInfo.kpiMeasPrd != 0)
   {
      if (schL2MeasCfm->measType &  LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
      {
         kpiId = KPI_ID_LTE_RRU_PRBDL_QCI1;
         for(indx = 0; indx < schL2MeasCfm->avgPrbQciDlCfm.numQci; indx++)
         {
            WR_INC_KPI((kpiId + schL2MeasCfm->avgPrbQciDlCfm.
                     prbPercQci[indx].qciValue - 1),KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->avgPrbQciDlCfm.prbPercQci[indx].prbPercQci);
            WR_INC_KPI(KPI_ID_LTE_RRU_PRBDL_QCI_SUM,KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->avgPrbQciDlCfm.prbPercQci[indx].prbPercQci);
         }
      }/*Updates PRB DL per QCI l2 cntrs*/
      if(schL2MeasCfm->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
      {
         kpiId = KPI_ID_LTE_RRU_PRBUL_QCI1;
         for(indx = 0; indx < schL2MeasCfm->avgPrbQciUlCfm.numQci; indx++)
         {
            WR_INC_KPI((kpiId + schL2MeasCfm->avgPrbQciUlCfm.prbPercQci[indx].
                     qciValue - 1),KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->avgPrbQciUlCfm.prbPercQci[indx].prbPercQci);
            WR_INC_KPI(KPI_ID_LTE_RRU_PRBUL_QCI_SUM,KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->avgPrbQciUlCfm.prbPercQci[indx].prbPercQci);
         }
      }/*Updates PRB UL per QCI l2 cntrs*/
      if(schL2MeasCfm->measType &  LRG_L2MEAS_AVG_PRB_DL)
      {
         WR_INC_KPI(KPI_ID_LTE_RRU_PRBTOTDL,KPI_VALUE_TYPE_INTEGER,
               schL2MeasCfm->avgPrbDl.prbPerc);
      }/*Updates Total Dl PRB usage l2 cntrs*/
      if(schL2MeasCfm->measType & LRG_L2MEAS_AVG_PRB_UL)
      {
         WR_INC_KPI(KPI_ID_LTE_RRU_PRBTOTUL,KPI_VALUE_TYPE_INTEGER,
               schL2MeasCfm->avgPrbUl.prbPerc);
      }/*Updates Total Ul Prb usage L2 cntrs*/
      if (schL2MeasCfm->measType &  LRG_L2MEAS_RA_PREAMBLE)
      {
         /*Calculates Mean number of Rach Preambles recevied in a cell in one second*/
         measPrd = kpiInfo.kpiMeasPrd/1000; /*in secs*/
         WR_INC_KPI(KPI_ID_LTE_RRU_RACHPREAMBLEDEDMEAN,KPI_VALUE_TYPE_INTEGER,
               (WR_PRMBL_DIV_ROUND(schL2MeasCfm->raPrmbsCfm.dedPreambles, measPrd)));
         WR_INC_KPI(KPI_ID_LTE_RRU_RACHPREAMBLEAMEAN,KPI_VALUE_TYPE_INTEGER,
               (WR_PRMBL_DIV_ROUND(schL2MeasCfm->raPrmbsCfm.randSelPreLowRange, measPrd)));
         WR_INC_KPI(KPI_ID_LTE_RRU_RACHPREAMBLEBMEAN,KPI_VALUE_TYPE_INTEGER,
               (WR_PRMBL_DIV_ROUND(schL2MeasCfm->raPrmbsCfm.randSelPreHighRange, measPrd)));
         RLOG3(L_INFO,"Dedicated Preamble Counter[%u] Preamble A Counter[%u]"
            " Preamble B Counter[%u]", schL2MeasCfm->raPrmbsCfm.dedPreambles,
                  schL2MeasCfm->raPrmbsCfm.randSelPreLowRange,
            schL2MeasCfm->raPrmbsCfm.randSelPreHighRange);

      }/*Updates Rach preambles related l2 cntrs */ 

      if (schL2MeasCfm->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
      {
         kpiId = KPI_ID_LTE_DRB_UE_ACT_DL_QCI1;
         for(indx = 0; indx < schL2MeasCfm->numUeQciDlCfm.numQci; indx++)
         {
            WR_INC_KPI((kpiId + schL2MeasCfm->numUeQciDlCfm.numActvUeQci[indx].qciValue - 1),KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->numUeQciDlCfm.numActvUeQci[indx].numActvUeQci);
            WR_INC_KPI( KPI_ID_LTE_DRB_UE_ACT_DL_SUM, KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->numUeQciDlCfm.numActvUeQci[indx].numActvUeQci);
         } 
      }
      if (schL2MeasCfm->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
      {
         kpiId = KPI_ID_LTE_DRB_UE_ACT_UL_QCI1;
         for(indx = 0; indx < schL2MeasCfm->numUeQciUlCfm.numQci; indx++)
         {
            WR_INC_KPI((kpiId + schL2MeasCfm->numUeQciUlCfm.numActvUeQci[indx].qciValue - 1),KPI_VALUE_TYPE_INTEGER,
                  schL2MeasCfm->numUeQciUlCfm.numActvUeQci[indx].numActvUeQci);
             WR_INC_KPI( KPI_ID_LTE_DRB_UE_ACT_UL_SUM, KPI_VALUE_TYPE_INTEGER,
                   schL2MeasCfm->numUeQciUlCfm.numActvUeQci[indx].numActvUeQci);
         }
      }

      if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_DL_COUNT)
      {
         WR_INC_KPI(KPI_ID_LTE_TB_TOT_NBR_DL,KPI_VALUE_TYPE_INTEGER,
               schL2MeasCfm->tbTransDlTotalCnt);
      }
      if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT)
      {
         WR_INC_KPI(KPI_ID_LTE_TB_ERR_NBR_DL,KPI_VALUE_TYPE_INTEGER,
               schL2MeasCfm->tbTransDlFaulty);
      }
      if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_UL_COUNT)
      {
         WR_INC_KPI(KPI_ID_LTE_TB_TOT_NBR_UL,KPI_VALUE_TYPE_INTEGER,
               schL2MeasCfm->tbTransUlTotalCnt);
      }
      if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT)
      {
         WR_INC_KPI(KPI_ID_LTE_TB_ERR_NBR_UL,KPI_VALUE_TYPE_INTEGER,
               schL2MeasCfm->tbTransUlFaulty);
      }

      /*Push Mac layer counter*/

      //if(kpiInfo.numOfTrggrL2MeasReq == kpiInfo.numOfRcvdL2MeasCfm)
      RLOG0(L_DEBUG,"Received Confirmation for MAC");
      if( kpiInfo.measConfigRecv == WR_MEAS_CFG_DONE )
      {
#ifdef WR_RSYS_OAM
         KpisInfoSentNotification();
#endif
         kpiInfo.measConfigRecv = 0;
         kpiInfo.numOfTrggrL2MeasReq = WR_KPI_SET_TO_ZERO;
         kpiInfo.numOfRcvdL2MeasCfm  = WR_KPI_SET_TO_ZERO;
      } 
#else
      glbMacMeasFlag = FALSE;

      if(schL2MeasCfm->cfm.status == ROK)
      {
         RLOG2(L_DEBUG,"Confirmatation Received for MeasType[%d] transId[%d]",
            schL2MeasCfm->measType,schL2MeasCfm->hdr.transId);
         if(schL2MeasCfm->measType &  LRG_L2MEAS_AVG_PRB_DL)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->avgPrbDl.prbPerc[%d]",
               schL2MeasCfm->avgPrbDl.prbPerc);
         }

         if(schL2MeasCfm->measType & LRG_L2MEAS_AVG_PRB_UL)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->avgPrbUl.prbPerc[%d]",
               schL2MeasCfm->avgPrbUl.prbPerc);
         }

         if (schL2MeasCfm->measType &  LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->avgPrbQciDlCfm.numQci[%d]",
               schL2MeasCfm->avgPrbQciDlCfm.numQci);
            for(i = 0; i < schL2MeasCfm->avgPrbQciDlCfm.numQci; i++)
            {
               RLOG2(L_DEBUG,"schL2MeasCfm->avgPrbQciDlCfm.qciValue[%d]=[%d]",
                  i,schL2MeasCfm->avgPrbQciDlCfm.prbPercQci[i].qciValue);
               RLOG2(L_DEBUG,"schL2MeasCfm->avgPrbQciDlCfm.prbPercQci[%d]=[%d] ",
                  i,schL2MeasCfm->avgPrbQciDlCfm.prbPercQci[i].prbPercQci);
            }
         }

         if (schL2MeasCfm->measType &  LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->avgPrbQciUlCfm.numQci[%d]",
               schL2MeasCfm->avgPrbQciUlCfm.numQci);
            for(i = 0; i < schL2MeasCfm->avgPrbQciUlCfm.numQci; i++)
               {
                  RLOG2(L_DEBUG,"schL2MeasCfm->avgPrbQciUlCfm.qciValue[%d]=[%d]",
                     i,schL2MeasCfm->avgPrbQciUlCfm.prbPercQci[i].qciValue);
                  RLOG2(L_DEBUG,"schL2MeasCfm->avgPrbQciUlCfm.prbPercQci[%d]=[%d]",
                     i,schL2MeasCfm->avgPrbQciUlCfm.prbPercQci[i].prbPercQci);

               }
         }

         if (schL2MeasCfm->measType &  LRG_L2MEAS_RA_PREAMBLE)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->dedPreambles[%d]",
               schL2MeasCfm->raPrmbsCfm.dedPreambles);
            RLOG1(L_DEBUG,"schL2MeasCfm->randSelPreLowRange[%d]",
               schL2MeasCfm->raPrmbsCfm.randSelPreLowRange);
            RLOG1(L_DEBUG,"schL2MeasCfm->randSelPreHighRange[%d]",
               schL2MeasCfm->raPrmbsCfm.randSelPreHighRange);
         }			

         if (schL2MeasCfm->measType &  LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->numUeQciDlCfm.numQci[%d]",
               schL2MeasCfm->numUeQciDlCfm.numQci);
#if 1 
            for(i = 0; i < schL2MeasCfm->numUeQciDlCfm.numQci; i++)
#else
               for(i = 0; i < 10; i++)
#endif
               {
                  RLOG2(L_DEBUG,"schL2MeasCfm->numUeQciDlCfm.qciValue[%d]=[%d]",
                     i,schL2MeasCfm->numUeQciDlCfm.numActvUeQci[i].qciValue);
               }
         }
         if (schL2MeasCfm->measType &  LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
         {
            RLOG1(L_DEBUG,"schL2MeasCfm->numUeQciUlCfm.numQci[%d]",
               schL2MeasCfm->numUeQciUlCfm.numQci);
#if 1
            for(i = 0; i < schL2MeasCfm->numUeQciUlCfm.numQci; i++)
#else
               for(i = 0; i < 10; i++)
#endif
               {

                  RLOG2(L_DEBUG,"schL2MeasCfm->numUeQciUlCfm.qciValue[%d]=[%d]",
                     i,schL2MeasCfm->numUeQciUlCfm.numActvUeQci[i].qciValue);
                  RLOG2(L_DEBUG,"schL2MeasCfm->numUeQciUlCfm.numActvUeQci[%d]=[%d]",
                     i,schL2MeasCfm->numUeQciUlCfm.numActvUeQci[i].numActvUeQci);
               }
         }
         if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_DL_COUNT)
         {
            RLOG1(L_DEBUG, " schL2MeasCfm->tbTransDlTotalCnt=[%u] ",schL2MeasCfm->tbTransDlTotalCnt); 
         }
         if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT)
         {
            RLOG1(L_DEBUG, " schL2MeasCfm->tbTransDlFaulty=[%u] ",schL2MeasCfm->tbTransDlFaulty);
         }
         if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_UL_COUNT)
         {
            RLOG1(L_DEBUG, " schL2MeasCfm->tbTransUlTotalCnt=[%u] ",schL2MeasCfm->tbTransUlTotalCnt); 
         }
         if (schL2MeasCfm->measType & LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT)
         {
            RLOG1(L_DEBUG, " schL2MeasCfm->tbTransUlFaulty=[%u] ",schL2MeasCfm->tbTransUlFaulty);
         }

      }
      else
      {
         RLOG2(L_DEBUG,"Negative Confirmatation Received for MeasType=[%d] with"
            "transId=[%d]",schL2MeasCfm->measType,schL2MeasCfm->hdr.transId);
      }
#endif
   }
   RETVALUE(ROK);
}/* End of SmMiLrgSchL2MeasCfm */

/*PRB: Review Tag*/
/**
 * @brief L2 Measurement Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgSchL2MeasCfm
 *     
 *     Enqueues the Config Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasStopCfm
(
Pst               *pst,
LrgSchMeasCfmInfo *schL2MeasCfm
)
#else
PUBLIC S16 SmMiLrgSchL2MeasStopCfm(pst, schL2MeasCfm)
Pst               *pst;
LrgSchMeasCfmInfo *schL2MeasCfm;
#endif
{
   S16 ret = ROK;
   TRC3(SmMiLrgSchL2MeasStopCfm);

  kpiInfo.numOfL2MeasStopCfm++;
  RLOG2(L_DEBUG,"numOfL2MeasStopCfm(%d) numOfL2MeasStopCfm(%d)",
     kpiInfo.numOfL2MeasStopReq,kpiInfo.numOfL2MeasStopCfm);
  if(kpiInfo.numOfL2MeasStopReq == kpiInfo.numOfL2MeasStopCfm)
  {
    /*KpiCollection is stopped*/
    wrKpiStopKpiCollecPrcCfm();
    kpiInfo.numOfL2MeasStopReq = WR_KPI_SET_TO_ZERO;
    kpiInfo.numOfL2MeasStopCfm = WR_KPI_SET_TO_ZERO;
  }
   RETVALUE(ret);
}
#endif



/*
*
*       Fun:   Sta Cfm
*
*       Desc:  This function is used by to present Sta Cfm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_rg_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLrgStsCfm
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgStsCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC2(SmMiLrgStsCfm)
#ifdef MAC_SCH_STATS
   RgGenSts          *sts;
   U8                cqi;
#endif /* MAC_SCH_STATS */

   UNUSED(pst);
#ifdef MAC_SCH_STATS
   sts = &(cfm->t.sts.s.genSts);
   RLOG0(L_INFO,"UL: Ack/Nack Statistics ");
   RLOG0(L_INFO,"cqi\tmcs\tnack\tack");
   RLOG0(L_INFO,"======================================================= ");
   for(cqi = 0; cqi <= 14; cqi ++)
   {
      if(sts->nackAckStats.ulCqiStat[cqi].mcs != 0)
         RLOG4(L_INFO,"%d\t%d\t%d\t%d", cqi+1, sts->nackAckStats.ulCqiStat[cqi].mcs, \
               sts->nackAckStats.ulCqiStat[cqi].numOfNacks, sts->nackAckStats.ulCqiStat[cqi].numOfAcks);
   }
   RLOG0(L_INFO,"UL: HARQ Retransmission Statistics ");
   RLOG0(L_INFO,"cqi\tmcs\tHq1\tHq2\tHq3\tHq4\tHqTotal");
   RLOG0(L_INFO,"======================================================= ");
   for(cqi = 0; cqi <= 14; cqi ++)
   {
      if(sts->nackAckStats.ulCqiStat[cqi].mcs != 0)
         RLOG1(L_INFO, "cqi+1 = %d", cqi+1);
         RLOG3(L_INFO,"%d\t%d\t%d", sts->hqRetxStats.ulCqiStat[cqi].mcs,
               sts->hqRetxStats.ulCqiStat[cqi].numOfHQ_1, 
               sts->hqRetxStats.ulCqiStat[cqi].numOfHQ_2);
         RLOG3(L_INFO,"%d\t%d\t%d", sts->hqRetxStats.ulCqiStat[cqi].numOfHQ_3,
               sts->hqRetxStats.ulCqiStat[cqi].numOfHQ_4,
               sts->hqRetxStats.ulCqiStat[cqi].totalTx);
   }
   RLOG0(L_INFO,"DL: Ack/Nack Statistics ");
   RLOG0(L_INFO,"cqi\tmcs\tnack\tack");
   RLOG0(L_INFO,"======================================================= ");
   for(cqi = 0; cqi <= 14; cqi ++)
   {
      if(sts->nackAckStats.dlCqiStat[cqi].mcs != 0)
         RLOG1(L_INFO, "cqi+1 = %d", cqi+1);
         RLOG3(L_INFO,"%d\t%d\t%d", sts->nackAckStats.dlCqiStat[cqi].mcs, \
               sts->nackAckStats.dlCqiStat[cqi].numOfNacks, sts->nackAckStats.dlCqiStat[cqi].numOfAcks);
   }
   RLOG0(L_INFO,"======================================================= ");
   RLOG0(L_INFO,"DL: HARQ Retransmission Statistics ");
   RLOG0(L_INFO,"cqi\tmcs\tHq1\tHq2\tHq3\tHq4\tHqTotal");
   RLOG0(L_INFO,"======================================================= ");
   for(cqi = 0; cqi <= 14; cqi ++)
   {
      if(sts->nackAckStats.dlCqiStat[cqi].mcs != 0)
         RLOG1(L_INFO, "cqi+1 = %d", cqi+1);
         RLOG3(L_INFO,"%d\t%d\t%d", sts->hqRetxStats.dlCqiStat[cqi].mcs,
               sts->hqRetxStats.dlCqiStat[cqi].numOfHQ_1,
               sts->hqRetxStats.dlCqiStat[cqi].numOfHQ_2);
         RLOG3(L_INFO,"%d\t%d\t%d", sts->hqRetxStats.dlCqiStat[cqi].numOfHQ_3,
               sts->hqRetxStats.dlCqiStat[cqi].numOfHQ_4,
               sts->hqRetxStats.dlCqiStat[cqi].totalTx);
   }
   RLOG0(L_INFO,"======================================================= ");
#endif /* MAC_SCH_STATS */
   UNUSED(cfm);

   RETVALUE(ROK);
} /* end of SmMiLrgStsCfm */


/*
*
*       Fun:   smBuildRgSCHShutCtrl
*
*       Desc:  Invoked to bind Scheduler to TFU Sap
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_rg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildRgSCHShutDownCtrl
(
Void
)
#else
PUBLIC S16 smBuildRgSCHShutDownCtrl(Void)
#endif
{
   RgMngmt  rgMngmt;
   RgCntrl  *cntrl=NULLP;
   Pst      pst;

   TRC2(smBuildRgSCHShutDownCtrl)
   
   SM_SET_ZERO(&pst, sizeof(Pst));
   SM_SET_ZERO(&rgMngmt, sizeof(RgMngmt));

   cntrl = &(rgMngmt.t.cntrl);

   cntrl->action             =  ASHUTDOWN;
   cntrl->subAction          =  SM_ZERO_VAL;
   cntrl->s.rgSapCntrl.suId  =  SM_ZERO_VAL;
   cntrl->s.rgSapCntrl.spId  =  1;


   /* Fill Header */
   rgMngmt.hdr.msgType             = TCNTRL;
   rgMngmt.hdr.entId.ent           = ENTRG;
   rgMngmt.hdr.entId.inst          = SM_INST_ZERO;
   rgMngmt.hdr.elmId.elmnt         = STGEN; 

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRG;
   pst.dstProcId = SM_RG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.srcInst   = 0;
   pst.dstInst   = SCH_INST_ID;
   
  RLOG0(L_DEBUG,"SCH Lrg Cntrl Req to SHUTDOWN SCHEDULER Tfu ");

   /* Send the request to the RG */
   SmMiLrgSchCntrlReq(&pst, &rgMngmt);

   RETVALUE(ROK);
} /* end of smBuildRgSCHShutDownCtrl */




/********************************************************************30**

           End of file:     fc_smm_mac_t2k.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:52:21 2014

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
SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
