
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_cl.c

     Sid:      fc_smm_cl_t2k.c@@/main/TeNB_Main_BR/10 - Mon Aug 11 16:52:03 2014

     Prg:      Sriky 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_FILE_ID=134;


static int RLOG_MODULE_ID=2;
#include "wr.h"
#include "wr_emm.h"
#include "wr_msm_common.h"


#include "lys.h"           /* layer management defines for CL */
#include "lys.x"           /* CL types */

#include "wr_smm_init.h"
#include "wr_smm_smallcell.h"
#ifdef TENB_STATS
#include "cm_tenb_stats.x"
#include "wr_cmn.h"
#endif

#ifdef E_TM
PUBLIC U8 etmCellState = ETM_CELL_STATE_IDLE;
#endif /* E_TM */
PRIVATE U8 wrYsCfg = 0;
PRIVATE U8 wrNumTfuSaps = 0;

EXTERN U16 wrSmMaxBufLen[SS_DIAG_MAX_CIRC_BUF];
EXTERN MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];

#ifdef WR_RSYS_OAM  
EXTERN S16 smStartTmr ARGS((PTR cb, S16 tmrEvnt,U32 delay));
EXTERN S16 smStopTmr ARGS((PTR cb, S16 tmrEvnt));
EXTERN Void smStaticCfgFailAlarm ARGS((Void));
#endif



#ifndef LTE_ENB_PAL
/*
*
*       Fun:   Initialize CL task.
*
*       Desc:  Invoked to create LTE CL TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  ve_se_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 smYsInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smYsInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smYsInit); 

   /* Register CL TAPA Task */
   if (SRegTTsk((Ent)ENTYS, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
            ysActvInit, (ActvTsk)ysActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

#ifndef CNE_UE_SIM_TEST
   if (SRegTTsk((Ent)ENTTF, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
            NULLP, (ActvTsk)ysActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Attach PHY STUB TAPA Task */
   if (SAttachTTsk((Ent)ENTTF, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif

   /* Attach CL TAPA Task */
   if (SAttachTTsk((Ent)ENTYS, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RLOG1(L_INFO, "CL Tapa Task successfully registered and attached to %d",
      sysTskId);

   RETVALUE(ROK);
} /* end of smYsInit */
#endif


/*
 *
 *       Fun:    wrSmYsCfg - configure YS
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_ys_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmYsCfg
(
Void
)
#else
PUBLIC Void wrSmYsCfg()
#endif /* ANSI */
{


  FILE *fp;
  S8 buf[] = "pkill -SIGINT enodeb\nreboot\n";
   U8 cfgIndx = 0;
   TRC2(wrSmYsCfg)
   wrYsCfg = 0;
   wrNumTfuSaps = 0; /*WR_DIP */

#ifdef WR_RSYS_OAM  
   smStartTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR, SM_TMR_STATIC_CFG_TMR_VAL);
#endif
   smBuildYsGenCfg();
#ifdef E_TM
   /* Do only General configuration in case of E_TM */
   if ( wrSmDfltBootMode )
   {
      RETVOID;
   }
#endif
   for(cfgIndx = 0; cfgIndx < wrSmDfltNumCells; cfgIndx++)
   {
      smBuildYsTfuSapCfg(RG_YS_SUID, cfgIndx);        
      smBuildYsSchTfuSapCfg(cfgIndx, (cfgIndx + wrSmDfltNumCells));
   }
   smBuildYsCtfSapCfg(WR_YS_SUID, WR_YS_SPID);

 
   if((fp = fopen("L1_L2_log_info.sh", "w")) == NULL)
   {
     RLOG0(L_FATAL, "Error while creating L1_L2_log_info.sh file");
     RETVOID;
   }
   fprintf(fp, "%s",buf);
   fclose(fp);


   RETVOID;
} /* end of wrSmYsCfg */



/*
*
*       Fun:   smBuildYsGenCfg
*
*       Desc:  fill in genCfg for YS
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_ys_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsGenCfg
(
Void
)
#else
PUBLIC S16 smBuildYsGenCfg()
#endif
{
   YsMngmt     *ysMgt = NULLP;
   YsGenCfg    *cfg = NULLP;
   Pst         pst;

   TRC2(smBuildYsGenCfg)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(ysMgt->t.cfg.s.genCfg);

   /*----------- Fill General Configuration Parameters ---------*/
   cfg->maxTfuSaps  = (U16)WRSM_LYS_MAX_TFU_SAPS;
   cfg->nmbUe       = lteeNodeBparams[0].lteSmCellCfg.maxUeSupp;
   cfg->enblSIAndPagngLog = lteeNodeBparams[0].lteGostLog.rrcLogEnable; 

#ifdef MSPD
   cfg->logBuf0Size  = wrSmMaxBufLen[1];
   cfg->logBuf1Size  = wrSmMaxBufLen[2];
#endif

   /*----------- Fill lmPst ---------*/
   cfg->lmPst.srcProcId = SM_YS_PROC;
#ifdef TIP_L2_L3_SPLIT
   cfg->lmPst.dstProcId = SM_LL2_SM_PROC;
#else
   cfg->lmPst.dstProcId = SM_SM_PROC;
#endif

   cfg->lmPst.srcEnt = (Ent)ENTTF;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)WRSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = YS_MEM_REGION;
   cfg->lmPst.pool =  smCb.init.pool;
   cfg->lmPst.selector = (Selector)WRSM_YSSMSEL;

   /* Fill Header */
   ysMgt->hdr.msgType             = TCFG;
   ysMgt->hdr.msgLen              = 0;
   ysMgt->hdr.entId.ent           = ENTTF;
   ysMgt->hdr.entId.inst          = SM_INST_ZERO;
   ysMgt->hdr.elmId.elmnt         = STGEN;
   ysMgt->hdr.elmId.elmntInst1    = 0;
   ysMgt->hdr.elmId.elmntInst2    = 0;
   ysMgt->hdr.elmId.elmntInst3    = 0;
   ysMgt->hdr.seqNmb              = 0;
   ysMgt->hdr.version             = 0;
   ysMgt->hdr.transId             = 0;

   ysMgt->hdr.response.prior      = PRIOR0;
   ysMgt->hdr.response.route      = RTESPEC;
   ysMgt->hdr.response.mem.region = YS_MEM_REGION;
   ysMgt->hdr.response.mem.pool   = YS_POOL;
   ysMgt->hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
 
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "Sending Gen Cfg Req to ys");
 
   /* Send the request to the LM */
   (Void) SmMiLysCfgReq(&pst, ysMgt);
 
   RETVALUE(ROK);
}/* smBuildYsGenCfg */

/*
*
*       Fun:   smBuildYsTfuSapCfg
*
*       Desc:  Call handler for TFU SAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsTfuSapCfg
(
SuId        suId,             /* CL Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildYsTfuSapCfg(suId, spId)
SuId        suId;             /* CL Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   YsMngmt      *ysMgt = NULLP;
   YsTfuSapCfg  *cfg = NULLP;
   Pst          pst;
 
   TRC2(smBuildYsTfuSapCfg)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(ysMgt->t.cfg.s.tfuSap);

   cfg->selector     = WRSM_RGYSSEL;
   cfg->mem.region   = YS_MEM_REGION;
   cfg->mem.pool     = YS_POOL;
   cfg->prior        = PRIOR0;
   cfg->route        = RTESPEC;
   cfg->procId       = SM_RG_PROC;
   cfg->ent          = ENTRG;
   cfg->inst         = (Inst)0;
   cfg->route        = RTESPEC;

   cfg->type         = (spId == RG_YS_SPID) ? LYS_TFU_USR_SAP :  
                                               LYS_TFU_SCH_SAP;
   cfg->suId         = suId;
   cfg->spId         = spId;
   cfg->type         = LYS_TFU_USR_SAP;
   /* In case of multiCell configuration, the spId will be the loop index
    * based on the number of cells. Therefor the cell Index sent to CL
    * will be different for each cell. */
   cfg->cellId       = WRSM_CELLID + spId;
   
   /* Fill Header */
   ysMgt->hdr.msgType             = TCFG;
   ysMgt->hdr.msgLen              = 0;
   ysMgt->hdr.entId.ent           = ENTTF;
   ysMgt->hdr.entId.inst          = SM_INST_ZERO;
   ysMgt->hdr.elmId.elmnt         = STTFUSAP;
   ysMgt->hdr.response.mem.region = YS_MEM_REGION;
   ysMgt->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "Sending Tfu Sap Req to ys");
 
   /* Send the request to the LM */
   (Void) SmMiLysCfgReq(&pst, ysMgt);
 
   RETVALUE(ROK);
}/* smBuildYsTfuSapCfg */


/*
*
*       Fun:   smBuildYsSchTfuSapCfg
*
*       Desc:  Call handler for SCH TFU SAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsSchTfuSapCfg
(
SuId        suId,             /* CL Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildYsSchTfuSapCfg(suId, spId)
SuId        suId;             /* CL Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   YsMngmt      *ysMgt = NULLP;
   YsTfuSapCfg  *cfg = NULLP;
   Pst          pst;
 
   TRC2(smBuildYsSchTfuSapCfg)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(ysMgt->t.cfg.s.tfuSap);

   cfg->selector     = WRSM_RGYSSEL;
#ifdef CL_MAC_LWLC
   cfg->selector     = 1; 
#endif
   cfg->mem.region   = YS_MEM_REGION;
   cfg->mem.pool     = YS_POOL;
   cfg->prior        = PRIOR0;
   cfg->route        = RTESPEC;
   cfg->procId       = SM_RG_PROC;
   cfg->ent          = ENTRG;
   cfg->inst         = (Inst)1;
   cfg->route        = RTESPEC;

   cfg->suId         = suId;
   cfg->spId         = spId;
   cfg->type         = LYS_TFU_SCH_SAP;
   /* In case of multiCell configuration, the suId will be the loop index
    * based on the number of cells. Therefor the cell Index sent to CL
    * will be different for each cell. */
   cfg->cellId       = WRSM_CELLID + suId;
   
   /* Fill Header */
   ysMgt->hdr.msgType             = TCFG;
   ysMgt->hdr.msgLen              = 0;
   ysMgt->hdr.entId.ent           = ENTTF;
   ysMgt->hdr.entId.inst          = SM_INST_ZERO;
   ysMgt->hdr.elmId.elmnt         = STTFUSAP;
   ysMgt->hdr.response.mem.region = YS_MEM_REGION;
   ysMgt->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "Sending Tfu Sap Req to ys");
 
   /* Send the request to the LM */
   (Void) SmMiLysCfgReq(&pst, ysMgt);
 
   RETVALUE(ROK);
}/* smBuildYsTfuSapCfg */



/*
*
*       Fun:   smBuildYsCtfSapCfg
*
*       Desc:  Call handler for CTF SAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsCtfSapCfg
(
SuId        suId,             /* CL Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildYsCtfSapCfg(suId, spId)
SuId        suId;             /* CL Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   YsMngmt      *ysMgt = NULLP;
   YsCtfSapCfg  *cfg = NULLP;
   Pst          pst;
 
   TRC2(smBuildYsCtfSapCfg)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(ysMgt->t.cfg.s.ctfSap);

   cfg->selector     = WRSM_WRYSSEL;
   cfg->mem.region   = YS_MEM_REGION;
   cfg->mem.pool     = YS_POOL;
   cfg->prior        = PRIOR0;
   cfg->route        = RTESPEC;
   cfg->procId       = SM_WR_PROC;

   cfg->inst         = (Inst)0;
   cfg->route        = RTESPEC;

   cfg->suId         = suId;
   cfg->spId         = spId;
   
   /* Fill Header */
   ysMgt->hdr.msgType             = TCFG;
   ysMgt->hdr.msgLen              = 0;
   ysMgt->hdr.entId.ent           = ENTTF;
   ysMgt->hdr.entId.inst          = SM_INST_ZERO;
   ysMgt->hdr.elmId.elmnt         = STCTFSAP;
   ysMgt->hdr.response.mem.region = YS_MEM_REGION;
   ysMgt->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_LL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "Sending Ctf Sap Req to ys");
 
   /* Send the request to the LM */
   (Void) SmMiLysCfgReq(&pst, ysMgt);
 
   RETVALUE(ROK);
}/* smBuildYsCtfSapCfg */

#ifdef TENB_STATS
/*
*
*       Fun:   smBuildYsTenbStatsCntrl
*
*       Desc:  Invoked to alter TeNB STATS related params at CL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsTenbStatsCntrl
(
   U32   statsPer
)
#else
PUBLIC S16 smBuildYsTenbStatsCntrl(statsPer)
   U32   statsPer;
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildYsTenbStatsCntrl)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl->t.cntrl.action        =  ARST;

   cntrl->t.cntrl.subAction     =  SAACNT;
   cntrl->t.cntrl.s.statsPer    =  statsPer;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTTF;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STGEN;
   cntrl->hdr.response.mem.region = YS_MEM_REGION;
   cntrl->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_EVENT, "Tenb STATS Cntrl Req to ys");
 
   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildYsGenCntrl */
#endif

/*
*
*       Fun:   smBuildYsGenCntrl
*
*       Desc:  Invoked to Enable Alarms at CL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsGenCntrl
(
)
#else
PUBLIC S16 smBuildYsGenCntrl(Void)
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildYsGenCntrl)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl->t.cntrl.action        =  AENA;
   cntrl->t.cntrl.s.ysSapCntrl.suId =  0;
   cntrl->t.cntrl.subAction     =  SAUSTA;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTTF;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STGEN;
   cntrl->hdr.response.mem.region = YS_MEM_REGION;
   cntrl->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "Sending Gen Cntrl Req to ys");
 
   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildYsGenCntrl */
/* wr004.102: Platform vendor changes */
 
/**
 * @brief This function is used to send enable/disable control request to 
 * the Convergence layers.
 *
 * @details
 *
 * Function: smBuildYsLogCntrl
 *
 * @param[in] actType
 * @param[in] mask
 *
 * @return Void
 */

#ifdef ANSI
PUBLIC S16 smBuildYsLogCntrl
(
 Bool actType,
 U32  mask
)
#else
PUBLIC S16 smBuildYsLogCntrl(actType, mask)
 Bool actType;
 U32  mask;
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildYsLogCntrl)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(actType == WR_ON)
   {
   cntrl->t.cntrl.action        =  AENA;
   }
   else
   {
   cntrl->t.cntrl.action        =  ADISIMM;
   }
#ifdef SS_DIAG
   cntrl->t.cntrl.subAction     =  SALOG;

   cntrl->t.cntrl.s.logMask = mask;
#endif
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTTF;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STGEN;
   cntrl->hdr.response.mem.region = YS_MEM_REGION;
   cntrl->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
 
   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildYsLogCntrl */ 

/*
*
*       Fun:   smBuildYsDbgCntrl
*
*       Desc:  Invoked to Enable Debugs at CL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsDbgCntrl
(
)
#else
PUBLIC S16 smBuildYsDbgCntrl(Void)
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildYsDbgCntrl)

   SGetSBuf(smCb.init.region, smCb.init.pool, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl->t.cntrl.action        =  AENA;
   cntrl->t.cntrl.subAction     =  SADBG;

/* wr004.102: Platform vendor changes */
   cntrl->t.cntrl.s.ysDbgCntrl.dbgMask = 0x1;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTTF;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STGEN;
   cntrl->hdr.response.mem.region = YS_MEM_REGION;
   cntrl->hdr.response.mem.pool   = YS_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "Sending Debug Cntrl Req to ys");
 
   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildYsDbgCntrl */

/** @brief  Invoked by system services to initialize a Stack Manager task.
 * @param ent 
 * @param inst 
 * @param region 
 * @param reason 
 * @return ROK/RFAILED
 */

/* IPSec Recovery */
/*
*
*       Fun:   smBuildYsShutDownCntrl
*
*       Desc:  Invoked to shut down CL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsShutDownCntrl
(
)
#else
PUBLIC S16 smBuildYsShutDownCntrl(Void)
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildYsShutDownCntrl)

   SGetSBuf(0, 0, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl->t.cntrl.action        =  ASHUTDOWN;
   cntrl->t.cntrl.subAction     =  NULLD;


   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTTF;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STGEN;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "PHY ShutDown Cntrl Req to ys");
 
   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildYsDbgCntrl */


/* IPSec Recovery */

#ifdef ANSI
PUBLIC S16 smYsActvInit
(
 Ent ent,                      /* entity */
 Inst inst,                    /* instance */
 Region region,                /* region */
 Reason reason                 /* reason */
 )
#else
PUBLIC S16 smYsActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smYsActvInit)

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
*       Desc:   Processes received event from YS
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   wr_sm_ys_exms.c
*
*/

#ifdef ANSI
PUBLIC S16 smYsActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smYsActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   /* wr002.102: Added trace macro */
   TRC2(smYsActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#ifdef LCYSMILYS
      case EVTLYSCFGCFM:             /* Config confirm */
         ret = cmUnpkLysCfgCfm(SmMiLysCfgCfm, pst, mBuf);
         break;
      case EVTLYSCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLysCntrlCfm(SmMiLysCntrlCfm, pst, mBuf);
         break;
      case EVTLYSRSYSLOG:           /* LOG */
         /* unpacking of log buffer posted from lower layer */
#ifdef SS_DIAG
         ret = ssDiagUnPackLogs(mBuf);
#endif
         break;
#ifdef E_TM
     case EVTLYSUSTAIND:
         ret = cmUnpkLysStaInd(SmMiLysStaInd, pst, mBuf); 
         break; 
#endif /* E_TM */
#endif
#ifdef TENB_STATS
      case  EVTTENBL2UESTATS:
       //  printf("\n TENB_STATS in smm_rlc...\n");
         TSInfUnpkL2UeStats(TSInfHdlL2UeStatsInd, pst, mBuf);
         break;
      case  EVTTENBL2CELLSTATS:
        // printf("\n TENB_STATS in smm_rlc(cellStats)...\n");
         TSInfUnpkL2CellStats(TSInfHdlL2CellStatsInd, pst, mBuf);
         break;
#endif
      case EVTWRRRCSTKBND:
         smWrProcSm(pst->event);
         (Void)SPutMsg(mBuf);
         break;
      default:
         WR_FREEMBUF(mBuf);
         ret = RFAILED;
         RLOG1(L_ERROR, "Invalid event [%d] received", pst->event);
         break;
   }

   RETVALUE(ret);

} /* end of smYsActvTsk */

/*
  
Layer management provides the necessary functions to control and
monitor the condition of each protocol layer.

The following functions are provided in this file:

     SmMiLysCfgReq      Configure Request
     SmMiLysStaReq      Status Request
     SmMiLysStsReq      Statistics Request
     SmMiLysCntrlReq    Control Request
   
It is assumed that the following functions are provided in the
stack management body files:

     SmMiLysStaInd      Status Indication
     SmMiLysStaCfm      Status Confirm
     SmMiLysStsCfm      Statistics Confirm
     SmMiLysTrcInd      Trace Indication
   
*/   
#define  MAXYSMI  2


#ifndef  LCSMYSMILYS
#define  PTSMYSMILYS
#else
#ifndef   YS
#define  PTSMYSMILYS
#endif
#endif

#ifdef PTSMYSMILYS
PRIVATE S16 PtMiLysCfgReq    (Pst *pst, YsMngmt *cfg);
PRIVATE S16 PtMiLysCntrlReq  (Pst *pst, YsMngmt *cntrl);
PRIVATE S16 PtMiLysREMScanCfgReq    (Pst *pst, U16 remScanInterval,
                                        U16 remScanCount);
PRIVATE S16 PtPkLysTPMRefSigPwrChangeReq  (Pst *pst, S16 refSigPwr);


PRIVATE S16 PtMiLysStaReq    (Pst *pst, YsMngmt *sta);
#endif


/*
the following matrices define the mapping between the primitives
called by the layer management interface of TCP UDP Convergence Layer
and the corresponding primitives in TUCL
 
The parameter MAXYSMI defines the maximum number of layer manager
entities on top of TUCL . There is an array of functions per primitive
invoked by TCP UDP Conbvergence Layer. Every array is MAXYSMI long
(i.e. there are as many functions as the number of service users).

The dispatcysng is performed by the configurable variable: selector.
The selector is configured during general configuration.

The selectors are:

   0 - loosely coupled (#define LCSMYSMILYS) 2 - Lys (#define YS)

*/


/* Configuration request primitive */
 
PRIVATE LysCfgReq SmMiLysCfgReqMt[MAXYSMI] =
{
#ifdef LCSMYSMILYS
   cmPkLysCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLysCfgReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef YS
   YsMiLysCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLysCfgReq,          /* 1 - tightly coupled, portable */
#endif
};


/* Control request primitive */
 
PRIVATE LysCntrlReq SmMiLysCntrlReqMt[MAXYSMI] =
{
#ifdef LCSMYSMILYS
   cmPkLysCntrlReq,          /* 0 - loosely coupled  */
#else
   PtMiLysCntrlReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef YS
   YsMiLysCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLysCntrlReq,          /* 1 - tightly coupled, portable */
#endif
};




/* Status request primitive */
 
PRIVATE LysStaReq SmMiLysStaReqMt[MAXYSMI] =
{
#ifdef LCSMYSMILYS
   cmPkLysStaReq,          /* 0 - loosely coupled  */
#else
   PtMiLysStaReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef YS
   YsMiLysStaReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLysStaReq,          /* 1 - tightly coupled, portable */
#endif
};

/* REM Tx Power Change Req */
PRIVATE LysTPMRefSigPwrChangeReq SmLysTPMTxPwrChangeReqMt[MAXYSMI] =
{
#ifdef LCSMYSMILYS
   cmPkLysTPMRefSigPwrChangeReq,          /* 0 - loosely coupled  */
#else
   PtPkLysTPMRefSigPwrChangeReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef YS
   YsTPMRefSigPwrChangeReq,               /* 1 - tightly coupled, layer management */
#else
   PtPkLysTPMRefSigPwrChangeReq,          /* 1 - tightly coupled, portable */
#endif
};


/*
*     layer management interface functions 
*/
 
/*
*
*       Fun:   Configuration request
*
*       Desc:  Tyss function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLysCfgReq
(
Pst *spst,                /* post structure */
YsMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLysCfgReq(spst, cfg)
Pst *spst;                /* post structure */   
YsMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLysCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLysCfgReqMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLysCfgReq */



/*
*
*       Fun:   Control request
*
*       Desc:  This function is used to send control request to 
*              TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLysCntrlReq
(
Pst *spst,                 /* post structure */
YsMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLysCntrlReq(spst, cntrl)
Pst *spst;                 /* post structure */   
YsMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLysCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLysCntrlReqMt[spst->selector])(spst, cntrl); 
   RETVALUE(ROK);
} /* end of SmMiLysCntrlReq */

/*
*
*       Fun:   Status request
*
*       Desc:  Tyss function is used to send a status request to 
*              TUCL
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLysStaReq
(
Pst *spst,                /* post structure */
YsMngmt *sta              /* status */
)
#else
PUBLIC S16 SmMiLysStaReq(spst, sta)
Pst *spst;                /* post structure */   
YsMngmt *sta;             /* status */
#endif
{
   TRC3(SmMiLysStaReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLysStaReqMt[spst->selector])(spst, sta); 
   RETVALUE(ROK);
} /* end of SmMiLysStaReq */

#ifdef PTSMYSMILYS

/*
 *             Portable Functions
 */

/*
*
*       Fun:   Portable configure Request- TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
  
#ifdef ANSI
PRIVATE S16 PtMiLysCfgReq
(
Pst *spst,                  /* post structure */
YsMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLysCfgReq(spst, cfg)
Pst *spst;                  /* post structure */
YsMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLysCfgReq) 

  UNUSED(spst);
  UNUSED(cfg);

  RETVALUE(ROK);
} /* end of PtMiLysCfgReq */


/*
*
*       Fun:   Portable control Request TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLysCntrlReq
(
Pst *spst,                  /* post structure */
YsMngmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLysCntrlReq(spst, cntrl)
Pst *spst;                  /* post structure */
YsMngmt *cntrl;             /* control */
#endif
{
  TRC3(PtMiLysCntrlReq)

  UNUSED(spst);
  UNUSED(cntrl);

 RETVALUE(ROK);
} /* end of PtMiLysCntrlReq */

/*
*
*       Fun:   Portable status Request TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
  
#ifdef ANSI
PRIVATE S16 PtMiLysStaReq
(
Pst *spst,                  /* post structure */
YsMngmt *sta                /* status */
)
#else
PRIVATE S16 PtMiLysStaReq(spst, sta)
Pst *spst;                  /* post structure */
YsMngmt *sta;               /* status */
#endif
{
  TRC3(PtMiLysStaReq);

  UNUSED(spst);
  UNUSED(sta);

 RETVALUE(ROK);
} /* end of PtMiLysStaReq */
/*
*
*       Fun:   Portable REM Scan configure Request- TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
  
#ifdef ANSI
PRIVATE S16 PtMiLysREMScanCfgReq
(
Pst *spst,                  /* post structure */
U16 remScanInterval,        /* REM Scan Interval */
U16 remScanCount            /* REM Scan Count */
)
#else
PRIVATE S16 PtMiLysREMScanCfgReq(spst, remScanInterval,remScanCount)
Pst *spst;                  /* post structure */
U16 remScanInterval;        /* REM Scan Interval */
U16 remScanCount;            /* REM Scan Count */
#endif
{
  TRC3(PtMiLysREMScanCfgReq) 

  UNUSED(spst);
  UNUSED(remScanInterval);
  UNUSED(remScanCount);

  RETVALUE(ROK);
} /* end of PtMiLysREMScanCfgReq */

#endif /* PTSMYSMILHI */

/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_ys_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLysCfgCfm
(
Pst     *pst,          /* post structure */
YsMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLysCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
YsMngmt *cfm;          /* configuration */
#endif
{
   Pst      ysPst;

   TRC2(SmMiLysCfgCfm);

   SM_SET_ZERO(&ysPst, sizeof(Pst));

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STGEN:
            wrYsCfg |= WR_YS_GEN_CFG;
#ifdef E_TM
            /* Set SAP Config confirm as TRUE if the boot mode
               is ETM */
            if ( wrSmDfltBootMode )
            {
               wrYsCfg |= WR_YS_CTF_SAP_CFG;
               wrYsCfg |= WR_YS_TFU_SAP_CFG;
            }
#endif /* E_TM */
            break;      
         case STTFUSAP:
            wrNumTfuSaps++;
            if (WR_NUM_OF_TFU_SAPS == wrNumTfuSaps)
            {
               wrNumTfuSaps = 0;
               wrYsCfg |= WR_YS_TFU_SAP_CFG;
            }
            break;
         case STCTFSAP:
            wrYsCfg |= WR_YS_CTF_SAP_CFG;
            break;
#ifdef E_TM 
         case STETMCELL:
            wrYsCfg = WR_YS_CELL_CFG;
            break;
         case STETM:
            wrYsCfg = WR_YS_ETM_CFG;
            RLOG0(L_DEBUG, "ETM Init Cfg Cfm Received"); 
            break;
#endif
         default:
            break;
      } /* end of switch statement */
      RLOG1(L_DEBUG, "CL Cfg Cfm received for the element %d",
         cfm->hdr.elmId.elmnt);

      if (wrYsCfg == WR_SM_YS_CONFIGURED)
      {
         smCb.smState = WR_SM_STATE_CL_CFG_DONE;
         RLOG0(L_ALWAYS, "CL CONFIGURATION SUCCESSFULLY PERFORMED.");
#ifdef WR_RSYS_OAM  
         smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif
#ifdef E_TM
         if ( wrSmDfltBootMode )
         {
            WR_FILL_PST(ysPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRCELLCFG, WR_POOL, SM_SELECTOR_LC);
         }
         else
#endif /* E_TM */
         {
#ifndef LTE_ENB_PAL          
#ifndef TIP_L2_L3_SPLIT          
            WR_FILL_PST(ysPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRENBDEBUGS, WR_POOL, SM_SELECTOR_LC);
#else         
            WR_FILL_PST(ysPst, SM_LL2_SM_PROC, SM_WR_PROC, ENTSM, ENTYS,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LC);
#endif
#endif
         }
         if(wrSmSelfPstMsg(&ysPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed after CL Configuration");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success after CL Configuration");
         } /* end of else part */

      }  /* end of wrYsCfg == WR_SM_YS_CONFIGURED */
#ifdef E_TM
      else if ( wrYsCfg == WR_YS_CELL_CFG )
      {
         RLOG0(L_DEBUG, "Cell Cfg CFM received from CL ");

      }
      else if ( wrYsCfg == WR_YS_ETM_CFG )
      {
         RLOG0(L_INFO, "ETM Cfg Cfm received from CL");
         RLOG0(L_ALWAYS, "Sending PHY_START Req.... ");
         /* Invoked control request to start PHY */
         smBuildYsEtmCntrl(AENA);
      }
#endif /* E_TM */
   } /* end of if statement cfm->cfm.status == LCM_PRIM_OK */
   else
   {
      RLOG0(L_ERROR, "CL CONFIGURATION CFM NOK");
#ifdef WR_RSYS_OAM  
      /*timer stop :: Raised an alarm */
      smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
      smCb.cfgCb.alarm.severity  = SM_ALARM_SEVERITY_MAJOR;
      smCb.cfgCb.alarm.causeType = SM_ALARM_CAUSE_TYPE_ERR_IND;
      smCb.cfgCb.alarm.causeVal  = SM_ALARM_CAUSE_VAL_INIT_FAIL;
      smStaticCfgFailAlarm();
#endif
   }
   WR_FREE(cfm, sizeof(YsMngmt));

   RETVALUE(ROK);
} /* end of SmMiLysCfgCfm */

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
*       File:  wr_sm_ys_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLysCntrlCfm
(
Pst     *pst,          /* post structure */
YsMngmt *cntrl         /* control */
)
#else
PUBLIC S16 SmMiLysCntrlCfm(pst, cntrl)
Pst     *pst;          /* post structure */
YsMngmt *cntrl;        /* control */
#endif
{
   Pst  ysPst;
   TRC2(SmMiLysCntrlCfm);
   /* IPSec */
   if (cntrl->cfm.status == LCM_PRIM_OK)
   {
      if (smCb.smState == WR_SM_STATE_S1AP_SHUTDWN_DONE)
      {
         smCb.smState = WR_SM_STATE_CL_SHUTDWN_DONE;
         RLOG0(L_ALWAYS, "CL SHUTDOWN SUCCESSFULLY PERFORMED.");
         WR_FILL_PST(ysPst, SM_SM_PROC, SM_SZ_PROC, ENTSM, ENTWR,0,0, EVTWRSCTPSHUT, WR_POOL, SM_SELECTOR_LC);

         if(wrSmSelfPstMsg(&ysPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed after CL Shutdown Configuration");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success after CL Shutdown Configuration");
         } /* end of else part */
         SPutSBuf(pst->region, pst->pool, (Data *) cntrl, sizeof(YsMngmt));
         RETVALUE(ROK);
      }
   }

   SPutSBuf(pst->region, pst->pool, (Data *) cntrl, sizeof(YsMngmt));
   RETVALUE(ROK);
} /* end of SmMiLysCntrlCfm */


/*
*
*       Fun:   Portable TPM Ref Sig Pwr Change Req 
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_smm_cl.c
*
*/
#ifdef ANSI
PRIVATE S16 PtPkLysTPMRefSigPwrChangeReq
(
Pst *spst,                  /* post structure */
S16 refSigPwr               /* Ref Sig Pwr */
)
#else
PRIVATE S16 PtPkLysTPMRefSigPwrChangeReq(spst, refSigPwr)
Pst *spst;                  /* post structure */
S16 refSigPwr;        /* Ref Sig Pwr */
#endif
{
  TRC3(PtPkLysTPMRefSigPwrChangeReq) 

  UNUSED(spst);
  UNUSED(refSigPwr);

  RETVALUE(ROK);
} /* end of PtPkLysTPMRefSigPwrChangeReq */


/*
*
*       Fun:   TPM Ref Signal Power Changes Req 
*
*       Desc:  Ref Signal Power Change Req
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_smm_cl.c
*
*/
#ifdef ANSI
PUBLIC S16 SmLysTPMTxPwrChangeReq
(
S16   refSigPwr
)
#else
PUBLIC S16 SmLysTPMTxPwrChangeReq(refSigPwr)
#endif
{
   S16 ret = ROK; 
   Pst sPst;
   
   TRC3(SmLysTPMTxPwrChangeReq)

   SM_SET_ZERO(&sPst, sizeof(Pst));
   /* Fill Pst */
   sPst.selector  = SM_SELECTOR_LC;
   sPst.srcEnt    = ENTSM;
   sPst.dstEnt    = ENTTF;
   sPst.dstProcId = SM_YS_PROC;
   sPst.srcProcId = SM_SM_PROC;

   sPst.region    = smCb.init.region;
   sPst.prior     = PRIOR1;
   /* jump to specific primitive depending on configured selector */
   ret = (*SmLysTPMTxPwrChangeReqMt[sPst.selector])(&sPst, refSigPwr); 
   RETVALUE(ret);
} /* end of SmLysTPMTxPwrChangeReq */


#ifdef E_TM
/*
*
*       Fun:   smBuildYsEtmCntrl
*
*       Desc:  Invoked to Enable Alarms at CL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_ys_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildYsEtmCntrl
(
Action action
)
#else
PUBLIC S16 smBuildYsEtmCntrl(Action action)
Action action;
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildYsEtmCntrl)

   SGetSBuf(0, 0, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl->t.cntrl.action        =  action;
   cntrl->t.cntrl.s.cellId =  WRSM_CELLID;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTTF;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STETM;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "Sending Gen Cntrl Req to ys");
 
   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildYsEtmCntrl */

/*
*
*       Fun:   Unsolicited Status Indication
*
*       Desc:  This function is used to handle any unsolited status indication 
*              from CL 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_ys_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLysStaInd
(
Pst     *pst,          /* post structure */
YsMngmt *usta         /* control */
)
#else
PUBLIC S16 SmMiLysStaInd(pst, cntrl)
Pst     *pst;          /* post structure */
YsMngmt *usta;        /* control */
#endif
{
   TRC2(SmMiLysStaInd);

   U16 event;
   U16 cause; 

   event = usta->t.usta.cmAlarm.event; 
   cause = usta->t.usta.cmAlarm.cause; 
   if ( cause != LCM_CAUSE_UNKNOWN )
   { 
     RLOG2(L_ERROR, "SM: Event[%d] Failed with Cause[%d]", event, cause);
     RETVALUE(ROK);
   }
   switch(event) 
   {
      case LYS_EVENT_ETM_CELLCFG:
         RLOG0(L_INFO, "Status Indication: Cell Cfg ( PHY_INIT ) is Done!");
         RLOG0(L_DEBUG, "Enter the cmd `etmtest on/off <tst id(1 to 6)>` "
            "To start/stop tst");
         etmCellState = ETM_CELL_STATE_CFG;
         break;
      case LYS_EVENT_ETM_PHY_START:
            RLOG0(L_INFO, "Status Indication: Cell is UP( PHY_START) !");
         etmCellState = ETM_CELL_STATE_UP;
         break;
      case LYS_EVENT_ETM_PHY_STOP:
         etmCellState = ETM_CELL_STATE_CFG;
         RLOG0(L_INFO, "Status Indication: Cell is DOWN(PHY_STOP)!");
         RLOG0(L_DEBUG, "Enter the cmd `etmtest on/off <tst id(1 to 6)>` "
            "To start/stop tst");
         break;
      default:
         RLOG0(L_ERROR, "Status Indication: default case !");
         break;
   }
         
  RETVALUE(ROK);
} /* SmMiLysStaInd */

/*
 *
 *       Fun:    wrSmYsCellCfg - configure PHY through YS
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_cl.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmYsCellCfg
(
Void
)
#else
PUBLIC Void wrSmYsCellCfg()
#endif /* ANSI */
{
   TRC2(wrSmYsCellCfg)

   smBuildYsCellCfg();
   RETVOID;
} /* end of wrSmYsCellCfg */

/*
*
*       Fun:   smBuildYsCellCfg
*
*       Desc:  fill in Cellcfg for YS
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_ys_cntrl.c 
*
*/
PUBLIC S16 smBuildYsCellCfg
(
Void
)
{
   YsMngmt     *ysMgt = NULLP;
   Pst         pst;
   LysCellCfgInfo  *cellCfgReq = NULLP;

   TRC2(smBuildCellCfg)

   SGetSBuf(0, 0, (Data **)&ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cellCfgReq  = &(ysMgt->t.cfg.s.cellCfg);

   cellCfgReq->cellId = wrSmDfltCellId; 
   cellCfgReq->cellIdGrpId = ((lteeNodeBparams[WR_DFLT_CELL_IDX].lteAddCellCfg.physCellId) / 3);

   /*cellCfgReq->physCellIdPres = PRSNT_NODEF ;*/
   cellCfgReq->physCellId = ((lteeNodeBparams[WR_DFLT_CELL_IDX].lteAddCellCfg.physCellId) % 3);
   /* Bandwidth Config */
   cellCfgReq->bwCfg.pres = PRSNT_NODEF ; 
   /* configuring the BW from cell configuration */
   /* ETM 20 MHz fixes */
   cellCfgReq->bwCfg.dlBw = lteeNodeBparams[WR_DFLT_CELL_IDX].lteCellMibCfgGrp.dlBw;
   cellCfgReq->bwCfg.ulBw = lteeNodeBparams[WR_DFLT_CELL_IDX].lteULFrequencyInfo.ulBandwidth;
   cellCfgReq->bwCfg.eUtraBand = lteeNodeBparams[WR_DFLT_CELL_IDX].lteCellSib1CfgGrp.freqBandInd;

   /* Basic transmission scheme */
   cellCfgReq->txCfg.pres = PRSNT_NODEF ;
   cellCfgReq->txCfg.duplexMode = lteeNodeBparams[WR_DFLT_CELL_IDX].lteSmCellCfg.duplexMode;
      
   cellCfgReq->txCfg.scSpacing = wrSmDfltScSpacing;
   cellCfgReq->txCfg.cycPfx = wrSmDfltCycPfx;
   /* Antenna config */
   if ( wrSmDfltNumOfTxAnt == 1)
   {
      cellCfgReq->antennaCfg.antPortsCnt = CTF_AP_CNT_1; 
   }
   else if ( wrSmDfltNumOfTxAnt == 2)
   {
      cellCfgReq->antennaCfg.antPortsCnt = CTF_AP_CNT_2; 
   }
   else
   {
      cellCfgReq->antennaCfg.antPortsCnt = CTF_AP_CNT_4; 
   }

   /* PRACH config */
   cellCfgReq->prachCfg.pres = PRSNT_NODEF;
   cellCfgReq->prachCfg.rootSequenceIndex = wrSmDfltRootSequenceIdx;
   cellCfgReq->prachCfg.prachCfgIndex = lteeNodeBparams[WR_DFLT_CELL_IDX].ltePrachCfgCommon.prachCfgInfo.prachCfgIdx;
   cellCfgReq->prachCfg.zeroCorrelationZoneCfg = wrSmDfltZeroCorrelZoneCfg; 
   cellCfgReq->prachCfg.highSpeedFlag = wrSmDfltHighSpeedFlag;
   cellCfgReq->prachCfg.prachFreqOffset = wrSmDfltPrachFreqOffset;

   cellCfgReq->pdschCfg.pres = PRSNT_NODEF;
   cellCfgReq->pdschCfg.refSigPwr = wrSmDfltRefSignalPower;
   cellCfgReq->pdschCfg.p_b =  wrSmDfltPDSCHCfgPB;
   /* SRS UL config, setup case */
   cellCfgReq->srsUlCfg.pres =  NOTPRSNT;
   cellCfgReq->srsUlCfg.srsCfgType = SOUNDINGRS_UL_CONFIGCMN_SETUP;

   cellCfgReq->srsUlCfg.srsSetup.srsBw         = wrSmDfltSrsBandwidthCfg; 
   cellCfgReq->srsUlCfg.srsSetup.sfCfg         = wrSmDfltSrsSubfrmCfg;
   cellCfgReq->srsUlCfg.srsSetup.srsANSimultTx = wrSmDfltAckNackSrsSimTrns;
   cellCfgReq->srsUlCfg.srsSetup.srsMaxUpPts   = NOTPRSNT; 
      /* PHY configuration parameters */
   cellCfgReq->opMode  = lteeNodeBparams[WR_DFLT_CELL_IDX].lteMsCellCfgReq.opMode;
   cellCfgReq->counter = 0;
   cellCfgReq->period  = 1; /* MSPD suggested value for ETM test */

#if (defined (E_TM) )
   /* Period value must set to zero in case of ETM testing for T2200
    * The wrSmDfltBootMode is set based on configuration in wr_cfg file */
   if(wrSmDfltBootMode)
   {
      cellCfgReq->period = 0;
   }
#endif 

   cellCfgReq->priSigPwr = wrSmDfltPriSigPwr;
   cellCfgReq->secSigPwr  = wrSmDfltSecSigPwr;

   RLOG2(L_DEBUG, "OP MODE:%d PERIOD:%ld",
         cellCfgReq->opMode, cellCfgReq->period);

   /* Fill Header */
   ysMgt->hdr.msgType             = TCFG;
   ysMgt->hdr.msgLen              = 0;
   ysMgt->hdr.entId.ent           = ENTTF;
   ysMgt->hdr.entId.inst          = SM_INST_ZERO;
   ysMgt->hdr.elmId.elmnt         = STETMCELL;
   ysMgt->hdr.elmId.elmntInst1    = 0;
   ysMgt->hdr.elmId.elmntInst2    = 0;
   ysMgt->hdr.elmId.elmntInst3    = 0;
   ysMgt->hdr.seqNmb              = 0;
   ysMgt->hdr.version             = 0;
   ysMgt->hdr.transId             = 0;

   ysMgt->hdr.response.prior      = PRIOR0;
   ysMgt->hdr.response.route      = RTESPEC;
   ysMgt->hdr.response.mem.region = smCb.init.region;
   ysMgt->hdr.response.mem.pool   = smCb.init.pool;
   ysMgt->hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Sending Cell Cfg Req to ys");
 
   /* Send the request to the LM */
   (Void) SmMiLysCfgReq(&pst, ysMgt);
 
   RETVALUE(ROK);
}/* smBuildYsGenCfg */
/*
*
*       Fun:   wrSmYsEtmCfg
*
*       Desc:  fill and send ETM cfg to CL
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_ys_cntrl.c 
*
*/
PUBLIC S16 wrSmYsEtmCfg
(
Void
)
{
   YsMngmt     *ysMgt = NULLP;
   Pst          pst;
   YsEtmCfg    *etmCfg = NULLP;

   TRC2(wrSmYsEtmCfg)

   SGetSBuf(0, 0, (Data **)&ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(ysMgt, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   etmCfg  = &(ysMgt->t.cfg.s.etmCfg);

   etmCfg->cellId = wrSmDfltCellId;

   /* Presently reading test model from Cfg file 
     and hardcoding rest of the params */
   etmCfg->etmInit.tModel = (YsEtmIntMod)wrSmDfltEtmId;
   /* configuring ETM bandwidth from global variable */
   /* Fix for ETM 20 MHz */
   etmCfg->etmInit.bw = lteeNodeBparams[WR_DFLT_CELL_IDX].lteCellMibCfgGrp.dlBw; 
   etmCfg->etmInit.e_rs = wrSmDfltRefSignalPower; 
   etmCfg->etmInit.ant0 = 1; /* Enabling antenna 0 */
   etmCfg->etmInit.ant1 = 0; /* disabling antenna 1 */
   etmCfg->etmInit.num_layers = 1; 
   etmCfg->etmInit.num_cw = 1;
   etmCfg->etmInit.tdd = 0; /* Disabling TDD */

   /* Fill Header */
   ysMgt->hdr.msgType             = TCFG;
   ysMgt->hdr.msgLen              = 0;
   ysMgt->hdr.entId.ent           = ENTTF;
   ysMgt->hdr.entId.inst          = SM_INST_ZERO;
   ysMgt->hdr.elmId.elmnt         = STETM;
   ysMgt->hdr.elmId.elmntInst1    = 0;
   ysMgt->hdr.elmId.elmntInst2    = 0;
   ysMgt->hdr.elmId.elmntInst3    = 0;
   ysMgt->hdr.seqNmb              = 0;
   ysMgt->hdr.version             = 0;
   ysMgt->hdr.transId             = 0;

   ysMgt->hdr.response.prior      = PRIOR0;
   ysMgt->hdr.response.route      = RTESPEC;
   ysMgt->hdr.response.mem.region = smCb.init.region;
   ysMgt->hdr.response.mem.pool   = smCb.init.pool;
   ysMgt->hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTTF;
   pst.dstProcId = SM_YS_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Sending Cell Cfg Req to ys");
 
   /* Send the request to the LM */
   (Void) SmMiLysCfgReq(&pst, ysMgt);
 
   RETVALUE(ROK);
}/* wrSmYsEtmCfg */
#endif /* E_TM */


/* REM Scan Configuration request primitive */
PRIVATE LysREMScanCfgReq SmMiLysREMScanCfgReqMt[MAXYSMI] =
{
#ifdef LCSMYSMILYS
   cmPkLysREMScanCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLysREMScanCfgReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef YS
   YsMiLysREMScanCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLysREMScanCfgReq,          /* 1 - tightly coupled, portable */
#endif
};

/*
*
*       Fun:   REM Scan Configuration request
*
*       Desc:  Tyss function is used to configure  Periodic REM Scan at BRDCM-CL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_ys_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLysREMScanCfgReq
(
U16 remScanInterval,        /* REM Scan Interval */
U16 remScanCount            /* REM Scan Count */
)
#else
PUBLIC S16 SmMiLysREMScanCfgReq(remScanInterval, remScanCount)
U16 remScanInterval;        /* REM Scan Interval */
U16 remScanCount;            /* REM Scan Count */
#endif
{
   S16 ret = ROK; 
   Pst sPst;
   
   TRC3(SmMiLysREMScanCfgReq)

   SM_SET_ZERO(&sPst, sizeof(Pst));
   /* Fill Pst */
   sPst.selector  = SM_SELECTOR_LC;
   sPst.srcEnt    = ENTSM;
   sPst.dstEnt    = ENTTF;
   sPst.dstProcId = SM_YS_PROC;
   sPst.srcProcId = SM_SM_PROC;

   sPst.region    = smCb.init.region;
   sPst.prior     = PRIOR1;
   /* jump to specific primitive depending on configured selector */
   ret = (*SmMiLysREMScanCfgReqMt[sPst.selector])(&sPst, remScanInterval, remScanCount); 
   RETVALUE(ret);
} /* end of SmMiLysREMScanCfgReq */


/********************************************************************30**

           End of file:     fc_smm_cl_t2k.c@@/main/TeNB_Main_BR/10 - Mon Aug 11 16:52:03 2014

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
