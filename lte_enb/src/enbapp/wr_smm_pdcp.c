
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_pdcp.c

     Sid:      fc_smm_pdcp_intel.c@@/main/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:37 2016

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_FILE_ID=40;
static int RLOG_MODULE_ID=2;

#include "wr.h"
#include "wr_cmn.h"
#include "lkw.h"
#include "lkw.x"
#include "lpj.h"
#include "lpj.x"

#include "wr_lwr.h"
#include "wr_smm_init.h"
#include "wr_kpiIds.h"
#include "wr_kpi.h"
#include "tip_cmn.h"
/* wr004.102:g++ */
#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */

PRIVATE U8  wrPjCfg = 0;

#if !(defined(LCSMMILPJ) && defined(PJ))
#define PTSMMILPJ
#endif

/* MAX Number of Service Providers of SM */
#define MAXPJMI 2

#ifdef PTSMMILPJ
EXTERN S16 PtMiLpjCfgReq   (Pst * pst, PjMngmt * cfg);
EXTERN S16 PtMiLpjCntrlReq (Pst * pst, PjMngmt * cfg);
#ifdef LTE_L2_MEAS  
EXTERN S16 PtMiLpjL2MeasReq (Pst * pst,PjL2MeasReqEvt *l2MeasEvt);
#endif /*LTE_L2_MEAS */
#endif /*--#ifdef PTSMMILTF--*/

#ifdef WR_RSYS_OAM  
EXTERN S16 smStartTmr ARGS((PTR cb, S16 tmrEvnt,U32 delay));
EXTERN S16 smStopTmr ARGS((PTR cb, S16 tmrEvnt));
EXTERN Void smStaticCfgFailAlarm ARGS((Void));
#endif

#ifdef TIP_LOWER_L2
EXTERN S16 tipLL2MiLpjCntrlReq ARGS((Pst *ppst, PjMngmt *cntrl));
#endif

PRIVATE CONSTANT LpjCfgReq SmMiLpjCfgReqMt[MAXPJMI] =
{
#ifdef LCSMMILPJ
   cmPkLpjCfgReq,
#else
   PtMiLpjCfgReq,
#endif
#ifdef PJ
   PjMiLpjCfgReq,
#else
   PtMiLpjCfgReq,
#endif
};

PRIVATE CONSTANT LpjCntrlReq SmMiLpjCntrlReqMt[MAXPJMI] =
{
#ifdef LCSMMILPJ
   cmPkLpjCntrlReq,
#else
   PtMiLpjCntrlReq,
#endif
#ifdef PJ
   PjMiLpjCntrlReq,
#else
   PtMiLpjCntrlReq,
#endif
};

#include "wr_kpiIds.h"
#include "wr_kpi.h"

extern S16 SmMiLpjL2MeasStopReq ( Pst *pst, U16 measType);
extern S16 SmMiLpjL2MeasSendReq ( Pst *pst, U16 measType);

PRIVATE U8  wrPjuSapCfgCnt = 0;
#ifdef LTE_L2_MEAS  
EXTERN S16 PtMiLpjL2MeasReq (Pst * pst,PjL2MeasReqEvt *l2MeasEvt);
#endif /*LTE_L2_MEAS */
 
#ifdef PTSMMILPJ
/**************************************************************************
 *
 *      Fun:   Portable Control request
 *
 *      Desc:  This function is used to send the Control request RLC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_pj_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 PtMiLpjL2MeasStopReq
(
Pst *pst,
U16  measType 
)
#else
PUBLIC S16 PtMiLpjL2MeasStopReq(pst, measType)
Pst *pst;
U16  measType; 
#endif
{

   TRC3(PtMiLpjL2MeasStopReq);
 
   UNUSED(pst);
   UNUSED(measType);

   RETVALUE(ROK);

}/*PtMiLpjL2MeasStopReq*/
 
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
 *      File:  wr_sm_pj_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 PtMiLpjL2MeasSendReq
(
Pst *pst,
U16  measType
)
#else
PUBLIC S16 PtMiLpjL2MeasSendReq(pst, measType)
Pst *pst;
U16  measType;
#endif
{


   TRC3(PtMiLpjL2MeasSendReq);

   UNUSED(pst);
   UNUSED(measType);

   RETVALUE(ROK);

}/*PtMiLpjL2MeasSendReq*/
#endif /* PTSMMILTF */
 
#ifdef LTE_L2_MEAS 
PRIVATE CONSTANT LpjL2MeasReq SmMiLpjL2MeasStartReqMt[MAXPJMI] =
{
#ifdef LCSMMILPJ
   cmPkLpjL2MeasReq,
#else
   PtMiLpjL2MeasReq,
#endif
#ifdef PJ
   PjMiLpjL2MeasReq,
#else
   PtMiLpjL2MeasReq,
#endif
};
PRIVATE CONSTANT LpjL2MeasStopReq SmMiLpjL2MeasStopReqMt[MAXPJMI] =
{
#ifdef LCSMMILPJ
   cmPkLpjL2MeasStopReq,
#else
   PtMiLpjL2MeasStopReq,
#endif
#ifdef PJ
   PjMiLpjL2MeasStopReq,
#else
   PtMiLpjL2MeasStopReq,
#endif
};
PRIVATE CONSTANT LpjL2MeasSendReq SmMiLpjL2MeasSendReqMt[MAXPJMI] =
{
#ifdef LCSMMILPJ
   cmPkLpjL2MeasSendReq,
#else
   PtMiLpjL2MeasSendReq,
#endif
#ifdef PJ
   PjMiLpjL2MeasSendReq,
#else
   PtMiLpjL2MeasSendReq,
#endif
};
#endif/* LTE_L2_MEAS*/
 
/*
*
*       Fun:   Initialize PDCP task.
*
*       Desc:  Invoked to create RLC/PDCP TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_enb_init.c
*
*/
#ifdef ANSI
PUBLIC S16 smPjUlInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smPjUlInit(sysTskId)
SSTskId    sysTskId;
#endif
{
   TRC2(smPjUlInit)

   /* Register RLC TAPA Task */
   if (SRegTTsk((Ent)ENTPJ, (Inst) WR_SM_PJUL_INST, (Ttype)TTNORM, (Prior)PRIOR1,
            pjUlActvInit, (ActvTsk)pjUlActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Attach RLC TAPA Task */
   if (SAttachTTsk((Ent)ENTPJ, (Inst)WR_SM_PJUL_INST, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RLOG1(L_INFO, "PDCP UL Tapa Task successfully registered"
                 "and attached to %d",sysTskId);
   RETVALUE(ROK);
} /* end of smPjUlInit */

/*
*
*       Fun:   Initialize PDCP task.
*
*       Desc:  Invoked to create RLC/PDCP TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_enb_init.c
*
*/
#ifdef ANSI
PUBLIC S16 smPjDlInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smPjDlInit(sysTskId)
SSTskId    sysTskId;
#endif
{
   TRC2(smPjUlInit)

   /* Register RLC TAPA Task */
   if (SRegTTsk((Ent)ENTPJ, (Inst)WR_SM_PJDL_INST, (Ttype)TTNORM, (Prior)PRIOR1,
            pjDlActvInit, (ActvTsk)pjDlActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Attach RLC TAPA Task */
   if (SAttachTTsk((Ent)ENTPJ, (Inst)WR_SM_PJDL_INST, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RLOG1(L_INFO, "PDCP DL Tapa Task successfully"
                 "registered and attached to %d", sysTskId);
   RETVALUE(ROK);
} /* end of smPjUlInit */

/*
 *
 *       Fun:    wrSmPjUlCfg - configure PJ
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_pj_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmPjUlCfg
(
Void
)
#else
PUBLIC Void wrSmPjUlCfg(Void)
#endif /* ANSI */
{
   TRC2(wrSmPjCfg)

   wrPjCfg = 0;
   wrPjuSapCfgCnt = 0;

#ifdef WR_RSYS_OAM  
   smStartTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR, SM_TMR_STATIC_CFG_TMR_VAL);
#endif
   smBuildPjGenCfg((Inst)WR_SM_PJUL_INST);
   smBuildPjCpjSapCfg((Inst)WR_SM_PJUL_INST);
   smBuildPjPjuSapCfg(WR_PJ_SPID,(Inst)WR_SM_PJUL_INST);
   smBuildPjPjuSapCfg(NH_PJ_SPID,(Inst)WR_SM_PJUL_INST);
   smBuildPjKwuSapCfg((Inst)WR_SM_PJUL_INST);
   smBuildPjUdxSapCfg((Inst)WR_SM_PJUL_INST);

   RETVOID;
} /* end of wrSmPjCfg */
/*
 *
 *       Fun:    wrSmPjCfg - configure PJ
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_pj_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmPjDlCfg
(
Void
)
#else
PUBLIC Void wrSmPjDlCfg(Void)
#endif /* ANSI */
{
   TRC2(wrSmPjDlCfg)

   wrPjCfg = 0;
   wrPjuSapCfgCnt = 0;

#ifdef WR_RSYS_OAM  
   smStartTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR, SM_TMR_STATIC_CFG_TMR_VAL);
#endif
   smBuildPjGenCfg((Inst) WR_SM_PJDL_INST);
   smBuildPjPjuSapCfg(WR_PJ_SPID,(Inst)WR_SM_PJDL_INST);
   smBuildPjPjuSapCfg(NH_PJ_SPID,(Inst)WR_SM_PJDL_INST);
   smBuildPjKwuSapCfg((Inst)WR_SM_PJDL_INST);
   smBuildPjUdxSapCfg((Inst)WR_SM_PJDL_INST);

   RETVOID;
} /* end of wrSmPjCfg */

/*
*
*       Fun:   smBuildPjGenCfg
*
*       Desc:  Invoked to build PDCP GEN CFG.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_pj_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildPjGenCfg
(
Inst  inst
)
#else
PUBLIC S16 smBuildPjGenCfg(inst)
Inst   inst;
#endif
{
   PjMngmt       pjMngmt;
   PjGenCfg      *genCfg=NULLP;
   Pst           pst;

   TRC2(smBuildPjGenCfg);

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   genCfg   = &(pjMngmt.t.cfg.s.gen);
   genCfg->timeRes  = 10;
   genCfg->mode = (inst == WR_SM_PJUL_INST) ? LPJ_MODE_PDCP_UL : 
                                             LPJ_MODE_PDCP_DL;
   genCfg->maxUe      = 0xffff;
   genCfg->maxKwuSaps  = 1;
   genCfg->maxPjuSaps = 2;
   genCfg->nmbUlBins  = 10;
   genCfg->nmbDlBins  = 10;
#ifdef TIP_L3_UL2_LL2_SPLIT
   genCfg->lmPst.dstProcId = SM_UL2_SM_PROC;
#else
   genCfg->lmPst.dstProcId = SM_SM_PROC;
#endif
   genCfg->lmPst.srcProcId = SM_PJ_PROC;
   genCfg->lmPst.dstEnt    = ENTSM;
   genCfg->lmPst.dstInst   = 0;
   genCfg->lmPst.srcEnt    = ENTPJ;
   genCfg->lmPst.srcInst   = inst;
   genCfg->lmPst.prior     = PRIOR0;
   genCfg->lmPst.route     = RTESPEC;
   genCfg->lmPst.region    = (inst == WR_SM_PJUL_INST) ?
                             PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;
   genCfg->lmPst.pool      = PJ_POOL;
   genCfg->lmPst.selector  = SM_SELECTOR_LC;

#ifdef PJ_ASYNC_HOOK
#ifdef TIP_L3_UL2_LL2_SPLIT
   genCfg->obdPst.cmpPst.dstProcId = SM_UL2_SM_PROC;
#else
   genCfg->obdPst.cmpPst.dstProcId = SM_SM_PROC;
#endif
   genCfg->obdPst.cmpPst.srcProcId = SM_PJ_PROC;
   genCfg->obdPst.cmpPst.dstEnt    = ENTSM;
   genCfg->obdPst.cmpPst.dstInst   = 0;
   genCfg->obdPst.cmpPst.srcEnt    = ENTPJ;
   genCfg->obdPst.cmpPst.srcInst   = inst;
   genCfg->obdPst.cmpPst.prior     = PRIOR0;
   genCfg->obdPst.cmpPst.route     = RTESPEC;
   genCfg->obdPst.cmpPst.region    = smCb.init.region;
   genCfg->obdPst.cmpPst.pool      = PJ_POOL;
   genCfg->obdPst.cmpPst.selector  = SM_SELECTOR_LC;

#ifdef TIP_L3_UL2_LL2_SPLIT
   genCfg->obdPst.secPst.dstProcId = SM_UL2_SM_PROC;
#else
   genCfg->obdPst.secPst.dstProcId = SM_SM_PROC;
#endif
   genCfg->obdPst.secPst.srcProcId = SM_PJ_PROC;
   genCfg->obdPst.secPst.dstEnt    = ENTSM;
   genCfg->obdPst.secPst.dstInst   = 0;
   genCfg->obdPst.secPst.srcEnt    = ENTPJ;
   genCfg->obdPst.secPst.srcInst   = inst; 
   genCfg->obdPst.secPst.prior     = PRIOR0;
   genCfg->obdPst.secPst.route     = RTESPEC;
   genCfg->obdPst.secPst.region    = smCb.init.region;
   genCfg->obdPst.secPst.pool      = PJ_POOL;
   genCfg->obdPst.secPst.selector  = SM_SELECTOR_LC;

   genCfg->obdTmrInt        = 50;
   genCfg->obdWtTmrInt      = 50;
#endif  /* PJ_ASYNC_HOOK */
   genCfg->nmbUlBins        = 100;
   genCfg->nmbDlBins        = 100;

   /* Fill Header */
   pjMngmt.hdr.msgType             = TCFG;
   pjMngmt.hdr.msgLen              = 0;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STGEN;
   pjMngmt.hdr.seqNmb              = 0;
   pjMngmt.hdr.version             = 0;
   pjMngmt.hdr.transId             = 0;

   pjMngmt.hdr.response.prior      = PRIOR0;
   pjMngmt.hdr.response.route      = RTESPEC;
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   pjMngmt.hdr.response.selector   = SM_SELECTOR_LC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.dstInst   = inst;
   pst.region = smCb.init.region;

   RLOG0(L_EVENT, "PDCP Gen Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLpjCfgReq(&pst, &pjMngmt);

   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildPjKwuSapCfg
*
*       Desc:  Invoked to build PDCP UDX SAP Config (CPJ).
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_pj_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildPjKwuSapCfg
(
Inst inst
)
#else
PUBLIC S16 smBuildPjKwuSapCfg(inst)
Inst inst;
#endif
{
   
   PjMngmt       pjMngmt;
   PjSapCfg     *lsap=NULLP;
   Pst           pst;

   TRC2(smBuildPjKwuSapCfg)

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lsap   = &(pjMngmt.t.cfg.s.sap);

   lsap->sapId        = 0;

#ifndef UL_RLC_NET_CLUSTER
   lsap->procId      = SM_KW_PROC;
   lsap->selector    = SM_SELECTOR_LC;
#else
   if(inst == WR_SM_PJUL_INST)
   {
      lsap->procId    = SM_KW_UL_PROC;
      //lsap->selector  = SM_SELECTOR_LWLC;
      /* Making RLC-UL to PDCP-UL as tightly coupled */
#ifdef UL_DL_SPLIT
      lsap->selector  = SM_SELECTOR_TC;
#else
      lsap->selector  = SM_SELECTOR_LC;
#endif
   }
   else
   {
      lsap->procId    = SM_KW_PROC;
      lsap->selector  = SM_SELECTOR_LC;
   }
#endif
   lsap->priority    = PRIOR0;
   lsap->route       = RTESPEC;

   lsap->ent         = ENTKW;
   lsap->inst        = inst;
   lsap->mem.region  = (inst == WR_SM_PJUL_INST) ?
                       PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;
   lsap->mem.pool    = PJ_POOL;
   lsap->bndTmrIntvl = TRUE;


   /* Fill Header */
   pjMngmt.hdr.msgType             = TCFG;
   pjMngmt.hdr.msgLen              = 0;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STKWUSAP;
   pjMngmt.hdr.seqNmb              = 0;
   pjMngmt.hdr.version             = 0;
   pjMngmt.hdr.transId             = 0;
  
   pjMngmt.hdr.response.prior      = PRIOR0;
   pjMngmt.hdr.response.route      = RTESPEC;
   pjMngmt.hdr.response.mem.region = smCb.init.region;
   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   pjMngmt.hdr.response.selector   = SM_SELECTOR_LC;
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.dstInst   = inst;
   pst.region = smCb.init.region;

   RLOG0(L_EVENT,"PDCP Gen Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLpjCfgReq(&pst, &pjMngmt);

   RETVALUE(ROK);
} /* end of smBuildPjKwuSapCfg*/
/*
*
*       Fun:   smBuildPjUdxSapCfg
*
*       Desc:  Invoked to build PDCP UDX SAP Config (CPJ).
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_pj_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildPjUdxSapCfg
(
Inst inst
)
#else
PUBLIC S16 smBuildPjUdxSapCfg(inst)
Inst inst;
#endif
{
   
   PjMngmt       pjMngmt;
   PjSapCfg     *usap=NULLP;
   Pst           pst;

   TRC2(smBuildPjUdxSapCfg)

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   usap   = &(pjMngmt.t.cfg.s.sap);

   usap->sapId        = 0;
   usap->procId      = SM_PJ_PROC;
   usap->priority    = PRIOR0;
   usap->route       = RTESPEC;
   /* Enabling LWLC for PDCP UL-DL interface(i.e UDX) */
#ifdef UL_DL_SPLIT
   usap->selector    = 1 /* UDX_SEL_LWLC */;
#else
   usap->selector    = 2 /* UDX_SEL_LWLC */;
#endif
   usap->ent         = ENTPJ;
   usap->inst        = (inst == WR_SM_PJUL_INST) ? WR_SM_PJDL_INST:WR_SM_PJUL_INST;
   usap->mem.region  = (inst == WR_SM_PJUL_INST) ?
                       PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;
   usap->mem.pool    = PJ_POOL;
   usap->bndTmrIntvl = TRUE;


   /* Fill Header */
   pjMngmt.hdr.msgType             = TCFG;
   pjMngmt.hdr.msgLen              = 0;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STUDXSAP;
   pjMngmt.hdr.seqNmb              = 0;
   pjMngmt.hdr.version             = 0;
   pjMngmt.hdr.transId             = 0;
  
   pjMngmt.hdr.response.prior      = PRIOR0;
   pjMngmt.hdr.response.route      = RTESPEC;
   pjMngmt.hdr.response.mem.region = smCb.init.region;
   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   pjMngmt.hdr.response.selector   = SM_SELECTOR_LC;
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.dstInst   = inst;
   pst.region = smCb.init.region;
   RLOG0(L_EVENT, "PDCP cpj Sap Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLpjCfgReq(&pst, &pjMngmt);

   RETVALUE(ROK);
} /* end of smBuildPjUdxSapCfg*/

/*
*
*       Fun:   smBuildPjCpjSapCfg
*
*       Desc:  Invoked to build PDCP CPJ SAP Config (CPJ).
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_pj_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildPjCpjSapCfg
(
Inst inst
)
#else
PUBLIC S16 smBuildPjCpjSapCfg(inst)
Inst inst;
#endif
{
   
   PjMngmt       pjMngmt;
   PjSapCfg     *usap=NULLP;
   Pst           pst;

   TRC2(smBuildPjCpjSapCfg)

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   usap   = &(pjMngmt.t.cfg.s.sap);

   usap->sapId        = 0;
   usap->procId      = SM_KW_PROC;
   usap->priority    = PRIOR0;
   usap->route       = RTESPEC;
   usap->selector    = SM_SELECTOR_LC;
   usap->ent         = ENTPJ;
   usap->inst        = inst;
   usap->mem.region  = (inst == WR_SM_PJUL_INST) ?
                       PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;
   usap->mem.pool    = PJ_POOL;
   usap->bndTmrIntvl = TRUE;


   /* Fill Header */
   pjMngmt.hdr.msgType             = TCFG;
   pjMngmt.hdr.msgLen              = 0;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STCPJSAP;
   pjMngmt.hdr.seqNmb              = 0;
   pjMngmt.hdr.version             = 0;
   pjMngmt.hdr.transId             = 0;
  
   pjMngmt.hdr.response.prior      = PRIOR0;
   pjMngmt.hdr.response.route      = RTESPEC;
   pjMngmt.hdr.response.mem.region = smCb.init.region;
   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   pjMngmt.hdr.response.selector   = SM_SELECTOR_LC;
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.dstInst   = inst;
   pst.region = smCb.init.region;

   RLOG0(L_EVENT,"PDCP cpj Sap Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLpjCfgReq(&pst, &pjMngmt);

   RETVALUE(ROK);
} /* end of smBuildPjCpjSapCfg */

/*
*
*       Fun:   smBuildPjPjuSapCfg
*
*       Desc:  Invoked to build PDCP PJU SAP Config (PJU).
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_pj_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildPjPjuSapCfg
(
SpId spId,
Inst inst
)
#else
PUBLIC S16 smBuildPjPjuSapCfg (spId,inst)
SpId spId;
Inst inst;
#endif
{
   
   PjMngmt       pjMngmt;
   PjSapCfg     *usap=NULLP;
   Pst           pst;

   TRC2(smBuildPjPjuSapCfg)

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   usap   = &(pjMngmt.t.cfg.s.sap);

   usap->sapId        = spId;
   usap->procId      = SM_KW_PROC;
#ifdef TIP_UPPER_L2
   usap->procId      = WR_L3_OFFSET;
#endif
   usap->priority    = PRIOR0;
   usap->route       = RTESPEC;
   usap->selector    = SM_SELECTOR_LC;
   if(spId == WR_PJ_SPID)
   {
      usap->selector    = WRSM_PJWRSEL;
      usap->ent         = ENTWR;
   }
   else if(spId == NH_PJ_SPID)
   {
      usap->ent         = ENTNH;
   }
   else
   {
      RLOG0(L_ERROR,"smBuildPjPjuSapCfg: Invalid spId");
   }
   usap->inst        = inst;
   usap->mem.region  = (inst == WR_SM_PJUL_INST) ?
                       PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;
   usap->mem.pool    = PJ_POOL;
   usap->bndTmrIntvl = TRUE;

   /* Fill Header */
   pjMngmt.hdr.msgType             = TCFG;
   pjMngmt.hdr.msgLen              = 0;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STPJUSAP;
   pjMngmt.hdr.seqNmb              = 0;
   pjMngmt.hdr.version             = 0;
   pjMngmt.hdr.transId             = 0;
  
   pjMngmt.hdr.response.prior      = PRIOR0;
   pjMngmt.hdr.response.route      = RTESPEC;
   pjMngmt.hdr.response.mem.region = smCb.init.region;
   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   pjMngmt.hdr.response.selector   = SM_SELECTOR_LC;
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif

   pst.dstInst   = inst;
   pst.region = smCb.init.region;

   RLOG0(L_EVENT,"PDCP pju Sap Cfg Req sent");

   /* Send the request to the RRC */
   SmMiLpjCfgReq(&pst, &pjMngmt);

   RETVALUE(ROK);
} /* end of smBuildPjPjuSapCfg */

/* IPSec Recovery */
/**
 * @brief This function is used to shut down PDCP
 *
 * @details
 *
 * Function: smBuildPjShutDownCntrl
 *
 * @param[in] actType
 * @param[in] mask
 *
 * @return Void
 */

#ifdef ANSI
PUBLIC S16 smBuildPjShutDownCntrl
(
U8 inst
)
#else
PUBLIC S16 smBuildPjShutDownCntrl(inst)
U8 inst;
#endif
{
   PjCntrl  *cntrl = NULLP;
   PjMngmt  pjMngmt;
   Pst      pst;

   TRC2(smBuildPjLogCntrl)

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(pjMngmt.t.cntrl);

      cntrl->action            =  ASHUTDOWN;

   cntrl->subAction            =  NULLD;
   /* Fill Header */
   pjMngmt.hdr.msgType             = TCNTRL;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = SM_INST_ZERO;
   pjMngmt.hdr.elmId.elmnt         = STGEN; 
   SGetDateTime(&(cntrl->dt));
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.dstInst   = inst;
   RLOG0(L_DEBUG, "SENDING SHUTDOWN REQUEST to PDCP");
   /* Send the request to the RRC */
   SmMiLpjCntrlReq(&pst, &pjMngmt);

   RETVALUE(ROK);

}
/*
*
*       Fun:   smBindUnBindPjKwuSap
*
*       Desc:  Invoked to bind and unbind RLC to UDX Sap
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindPjKwuSap
(
Inst inst,
U8   action
)
#else
PUBLIC S16 smBindUnBindPjKwuSap(inst,action)
Inst inst;
#endif
{
   PjCntrl  *cntrl = NULLP;
   PjMngmt  pjMngmt;
   Pst      pst;
  
   TRC2(smBindUnBindPjKwuSap)
 
   SM_SET_ZERO(&pjMngmt, sizeof(KwMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(pjMngmt.t.cntrl);

   cntrl->action            =  action;
   cntrl->subAction         =  SM_ZERO_VAL;
   cntrl->s.sapCntrl.suId   =  SM_ZERO_VAL;
   cntrl->s.sapCntrl.spId   =  1;

   /* Fill Header */
   pjMngmt.hdr.msgType             = TCNTRL;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STKWUSAP; 
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
   pst.dstInst   = inst;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.region = smCb.init.region;
   
   if (action == ABND)
   {
      RLOG1(L_EVENT, "PDCP Ctrl Req to PDCP instance %d for Binding KWU sap",
          inst);
   }
   else
   {
      RLOG1(L_EVENT, "PDCP Ctrl Req to PDCP instance %d for UnBinding KWU sap",
          inst);
   }

   /* Send the request to the RRC */
   SmMiLpjCntrlReq(&pst, &pjMngmt);

   RETVALUE(ROK);
} /* smBindUnBindPjKwuSap */
 /*
*
*       Fun:   smBindPjUdxSap
*
*       Desc:  Invoked to bind RLC to UDX Sap
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_kw_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBindPjUdxSap
(
Inst inst
)
#else
PUBLIC S16 smBindPjUdxSap(inst)
Inst inst;
#endif
{
   PjCntrl  *cntrl = NULLP;
   PjMngmt  pjMngmt;
   Pst      pst;
  
   TRC2(smBindPjUdxSap)
 
   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(pjMngmt.t.cntrl);

   cntrl->action            =  ABND;
   cntrl->subAction         =  SM_ZERO_VAL;
   cntrl->s.sapCntrl.suId   =  SM_ZERO_VAL;
   cntrl->s.sapCntrl.spId   =  SM_ZERO_VAL;

   /* Fill Header */
   pjMngmt.hdr.msgType             = TCNTRL;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = inst;
   pjMngmt.hdr.elmId.elmnt         = STUDXSAP; 
   pjMngmt.hdr.response.mem.region = (inst == WR_SM_PJUL_INST) ? 
                                      PJ_UL_MEM_REGION:PJ_DL_MEM_REGION;

   pjMngmt.hdr.response.mem.pool   = PJ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
   pst.dstInst   = inst;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "PDCP Cntrl Req to PDCP UL for Binding UDX sap");
   /* Send the request to the RRC */
   SmMiLpjCntrlReq(&pst, &pjMngmt);

   RETVALUE(ROK);
} /* smBindKwToRguSap */
 

/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from PJ
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   wr_sm_pj_exms.c
*
*/

#ifdef ANSI
PUBLIC S16 smPjActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smPjActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   /* wr002.102: Added trace macro */
   TRC2(smPjActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#ifdef LCSMMILPJ
      case LPJ_EVT_CFG_CFM:             /* Config confirm */
         ret = cmUnpkLpjCfgCfm(SmMiLpjCfgCfm, pst, mBuf);
         break;
      case LPJ_EVT_CNTRL_CFM:           /* Control confirm */
         ret = cmUnpkLpjCntrlCfm(SmMiLpjCntrlCfm, pst, mBuf);
         break;
#endif
      case EVTWRPDCPCFG:           /* Control confirm */
      case EVTWRDAMCFG:           /* Control confirm */
      case EVTWREGTPSTKBND:           /* Control confirm */
         smWrProcSm(pst->event);
         break;
      default:
         WR_FREEMBUF(mBuf);
         ret = RFAILED;
         RLOG0(L_ERROR, "Received invalid event");
         break;
   }

   RETVALUE(ret);

} /* end of smPjActvTsk */

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
 *      File:  wr_sm_pj_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLpjCfgReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 SmMiLpjCfgReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{
   TRC3(SmMiLpjCfgReq);

   (*SmMiLpjCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   Control Request
 *
 *      Desc:  This function is used to configure RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smpjptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 SmMiLpjCntrlReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 SmMiLpjCntrlReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{

   TRC3(SmMiLpjCntrlReq);
#ifdef TIP_LOWER_L2
    tipLL2MiLpjCntrlReq(pst, cfg);
#else
   (*SmMiLpjCntrlReqMt[pst->selector])(pst, cfg);
#endif
   RETVALUE(ROK);

}


#ifdef PTSMMILPJ
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
 *      File:  wr_sm_pj_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtMiLpjCfgReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 PtMiLpjCfgReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{

   TRC3(PtMiLpjCfgReq);

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}

#ifdef LTE_L2_MEAS
/**************************************************************************
 *
 *      Fun:   Portable Control request
 *
 *      Desc:  This function is used to send the Control request RLC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_pj_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 PtMiLpjL2MeasReq 
(
Pst * pst,
PjL2MeasReqEvt *l2MeasEvt
)
#else
PUBLIC S16 PtMiLpjL2MeasReq(pst, l2MeasEvt)
Pst * pst;
PjL2MeasReqEvt *l2MeasEvt
#endif
{

   TRC3(PtMiLpjL2MeasReq);

   UNUSED(pst);
   UNUSED(l2MeasEvt);

   RETVALUE(ROK);

}/*PtMiLpjL2MeasReq*/
#endif /*LTE_L2_MEAS*/ 

/**************************************************************************
 *
 *      Fun:   Portable Control request
 *
 *      Desc:  This function is used to send the Control request RLC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  wr_sm_pj_ptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtMiLpjCntrlReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 PtMiLpjCntrlReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{

   TRC3(PtMiLpjCntrlReq);

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}

#endif /* PTSMMILTF */
 
/**
 * @brief This function is used to send enable/disable control request to 
 * the PDCP layers.
 *
 * @details
 *
 * Function: smBuildPjLogCntrl
 *
 * @param[in] actType
 * @param[in] mask
 *
 * @return Void
 */

#ifdef ANSI
PUBLIC S16 smBuildPjLogCntrl
(
 Bool actType,
 U32  mask
)
#else
PUBLIC S16 smBuildPjLogCntrl(actType, mask)
 Bool actType;
 U32  mask;
#endif
{
   PjCntrl  *cntrl = NULLP;
   PjMngmt  pjMngmt;
   Pst      pst;

   TRC2(smBuildPjLogCntrl)

   SM_SET_ZERO(&pjMngmt, sizeof(PjMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl = &(pjMngmt.t.cntrl);

   if(actType == WR_ON)
   {
      cntrl->action            =  AENA;
   }
   else
   {
      cntrl->action            =  ADISIMM;
   }

   /* Fill Header */
   pjMngmt.hdr.msgType             = TCNTRL;
   pjMngmt.hdr.entId.ent           = ENTPJ;
   pjMngmt.hdr.entId.inst          = SM_INST_ZERO;
   pjMngmt.hdr.elmId.elmnt         = STGEN; 

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_KW_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = SM_MEM_REGION;

   /* Send the request to the RRC */
   SmMiLpjCntrlReq(&pst, &pjMngmt);

   RETVALUE(ROK);

} /* smBuildPjLogCntrl */

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
*       File:  wr_sm_pj_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 smProcPjUlCfgCfm
(
PjMngmt        *cfm
)
#else
PRIVATE S16 smProcPjUlCfgCfm(pst, cfm)
PjMngmt        *cfm;
#endif
{
   Pst      pjPst;

   TRC2(smProcUlPjCfgCfm);

   SM_SET_ZERO(&pjPst, sizeof(Pst));

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STGEN:
            wrPjCfg |= WR_PJ_GEN_CFG;
            break;      
         case STCPJSAP:
            wrPjCfg |= WR_PJ_CPJ_SAP_CFG;
            break;
         case STPJUSAP:
            wrPjCfg |= WR_PJ_PJU_SAP_CFG;
            wrPjuSapCfgCnt++;
            break;
         case STKWUSAP:
            wrPjCfg |= WR_PJ_KWU_SAP_CFG;
            break;
         case STUDXSAP:
            wrPjCfg |= WR_PJ_UDX_SAP_CFG;
            break;
         default:
            RLOG1(L_ERROR, "PDCP Cfg Cfm received with invalid element %d",
               cfm->hdr.elmId.elmnt);
            break;
      } /* end of switch statement */

      RLOG1(L_DEBUG, "PDCP Cfg Cfm received for element %d",
         cfm->hdr.elmId.elmnt);

      if ((wrPjCfg == WR_SM_PJ_UL_CONFIGURED) && (wrPjuSapCfgCnt == 2))
      {
         smCb.smState = WR_SM_STATE_PDCP_UL_CFG_DONE;
#ifdef WR_RSYS_OAM  
         smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif
         wrPjCfg = 0;
         wrPjuSapCfgCnt = 0;
#ifdef TIP_L3_UL2_LL2_SPLIT
         WR_FILL_PST(pjPst, SM_UL2_SM_PROC, SM_PJ_PROC, ENTSM, ENTPJ,0,0, EVTWRPDCPCFG, WR_POOL, SM_SELECTOR_LC);
#else
         WR_FILL_PST(pjPst, SM_SM_PROC, SM_PJ_PROC, ENTSM, ENTWR,0,0, EVTWRPDCPCFG, WR_POOL, SM_SELECTOR_LC);
#endif

         if(wrSmSelfPstMsg(&pjPst) != ROK)
         {
            RLOG0(L_ERROR, "PDCP CONFIGURATION SUCCESSFULLY PERFORMED. "
               "Failure at Self Pst.");
         }
         else
         {
            RLOG0(L_DEBUG, "PDCP CONFIGURATION SUCCESSFULLY PERFORMED.");
         } /* end of else part */

      }  /* end of wrPjCfg == WR_SM_PJ_CONFIGURED */
   } /* end of if statement cfm->cfm.status == LCM_PRIM_OK */
   else
   {
      RLOG0(L_ERROR, "Configuration Cfm for PDCP UL with NOK Received.");
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
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Managemer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_pj_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 smProcPjDlCfgCfm
(
PjMngmt        *cfm
)
#else
PRIVATE S16 smProcPjDlCfgCfm(pst, cfm)
PjMngmt        *cfm;
#endif
{
   Pst      pjPst;

   TRC2(SmMiLpjCfgCfm);

   SM_SET_ZERO(&pjPst, sizeof(Pst));

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STGEN:
            wrPjCfg |= WR_PJ_GEN_CFG;
            break;      
         case STPJUSAP:
            wrPjCfg |= WR_PJ_PJU_SAP_CFG;
            wrPjuSapCfgCnt++;
            break;
         case STKWUSAP:
            wrPjCfg |= WR_PJ_KWU_SAP_CFG;
            break;
         case STUDXSAP:
            wrPjCfg |= WR_PJ_UDX_SAP_CFG;
            break;
         default:
            RLOG1(L_ERROR,"SmMiLpjCfgCfm PDCP Cfg Cfm received with invalid "
               "element[%d]",cfm->hdr.elmId.elmnt);
            break;
      } /* end of switch statement */

      RLOG1(L_DEBUG,"PDCP Cfg Cfm received for the element[%d]",
         cfm->hdr.elmId.elmnt);

      if ((wrPjCfg == WR_SM_PJ_DL_CONFIGURED) && (wrPjuSapCfgCnt == 2))
      {
         smCb.smState = WR_SM_STATE_PDCP_DL_CFG_DONE;
#ifdef WR_RSYS_OAM  
         smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif
#ifdef TIP_L3_UL2_LL2_SPLIT
         WR_FILL_PST(pjPst, SM_UL2_SM_PROC, SM_PJ_PROC, ENTSM, ENTPJ,0,0, EVTWRDAMCFG, WR_POOL, SM_SELECTOR_LC);
#else
         WR_FILL_PST(pjPst, SM_SM_PROC, SM_PJ_PROC, ENTSM, ENTWR,0,0, EVTWRRLCCFG, WR_POOL, SM_SELECTOR_LC);
#endif

         if(wrSmSelfPstMsg(&pjPst) != ROK)
         {
            RLOG0(L_WARNING,"PDCP CONFIGURATION SUCCESSFULLY PERFORMED. "
               "Failure at Self Pst.");
         }
         else
         {
            RLOG0(L_DEBUG,"PDCP CONFIGURATION SUCCESSFULLY PERFORMED.");
         } /* end of else part */

      }  /* end of wrPjCfg == WR_SM_PJ_CONFIGURED */
   } /* end of if statement cfm->cfm.status == LCM_PRIM_OK */
   else
   {
      RLOG0(L_DEBUG,"SmMiLkwCfgCfm: Configuration Cfm with NOK Received.");
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
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Managemer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_pj_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLpjCfgCfm
(
Pst            *pst,
PjMngmt        *cfm
)
#else
PUBLIC S16 SmMiLpjCfgCfm(pst, cfm)
Pst            *pst;
PjMngmt        *cfm;
#endif
{
   TRC2(SmMiLpjCfgCfm);

   if (pst->srcInst == WR_SM_PJUL_INST)
   {
      smProcPjUlCfgCfm(cfm);
   }
   else
   {
      smProcPjDlCfgCfm(cfm);
   }

   RETVALUE(ROK);
} /* end of SmMiLkwCfgCfm */


/*
*
*       Fun:   Control Confirm
*
*       Desc:  This function is used by to present Control confirm
*              information to Layer Managemer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_pj_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLpjCntrlCfm
(
Pst            *pst,
PjMngmt        *cfm
)
#else
PUBLIC S16 SmMiLpjCntrlCfm(pst, cfm)
Pst            *pst;
PjMngmt        *cfm;
#endif
{
   Pst      pjPst;
   TRC2(SmMiLpjCntrlCfm)
   /*IPSec */
   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      /*if (smCb.smState == WR_SM_STATE_RLC_SHUTDWN_DONE)*/
      if (smCb.smState == WR_SM_STATE_RRC_SHUTDWN_DONE)
      {
         if(pst->srcInst == WR_SM_PJDL_INST)
         {
            smCb.smState = WR_SM_STATE_PDCP_DL_SHUTDWN_DONE;
            WR_FILL_PST(pjPst, SM_SM_PROC, SM_PJ_PROC, ENTSM, ENTWR,0,0, EVTWRPDCPSHUT, WR_POOL, SM_SELECTOR_LC);

            if(wrSmSelfPstMsg(&pjPst) != ROK)
            {
               RLOG0(L_EVENT, "PDCP DL SHUTDOWN SUCCESSFULLY PERFORMED. Failure at Self Pst.");
            }
            else
            {
               RLOG0(L_EVENT, "PDCP DL SHUTDOWN SUCCESSFULLY PERFORMED. ");
            } /* end of else part */
         } 
         else 
         {
               RLOG1(L_ERROR, " Invalid DL Instance ID %d ", pst->srcInst);
         }
         RETVALUE(ROK);
      }
      else if (smCb.smState == WR_SM_STATE_PDCP_DL_SHUTDWN_DONE)
      {
         if(pst->srcInst == WR_SM_PJUL_INST)
         {
            smCb.smState = WR_SM_STATE_PDCP_UL_SHUTDWN_DONE;
            WR_FILL_PST(pjPst, SM_SM_PROC, SM_PJ_PROC, ENTSM, ENTWR,0,0, EVTWRRLCSHUT, WR_POOL, SM_SELECTOR_LC);

            if(wrSmSelfPstMsg(&pjPst) != ROK)
            {
               RLOG0(L_EVENT, "PDCP UL SHUTDOWN SUCCESSFULLY PERFORMED. Failure at Self Pst.");
            }
            else
            {
               RLOG0(L_EVENT, "PDCP UL SHUTDOWN SUCCESSFULLY PERFORMED. ");
            } /* end of else part */
            RETVALUE(ROK);
         } 
         else 
         {
               RLOG1(L_ERROR, " Invalid UL Instance ID %d ", pst->srcInst);
         }
         RETVALUE(ROK);
      }
   } 

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case  STGEN:
         {
            if((smCfgCb.kwDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_KW_DBG_MASK))
            {
               /* Update DbgMsk */
               smCfgCb.smDbgMsk = (smCfgCb.smDbgMsk | WR_SM_KW_DBG_MASK);
               /* Trigger Debug Cntrl */
               wrSmHdlEnbDebugs(EVTWRENBDEBUGS);
            }
            break;
         }
         case  STKWUSAP:
         {
            /* Due to unbind */
            if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
            {
               if (cfm->cfm.status == LCM_PRIM_OK)
               {
                  if (pst->srcInst == WR_SM_PJDL_INST)
                  {
                     RLOG0(L_DEBUG,"UNBIND OF PDCP DL WITH RLC DL SUCCESSFUL");
                     /* Unbind PDCP UL to RLC UL */
                     smBindUnBindPjKwuSap(WR_SM_PJUL_INST,AUBND);
                  }
                  else if (pst->srcInst == WR_SM_PJUL_INST)
                  {
                     RLOG0(L_DEBUG,"UNBIND OF PDCP UL WITH RLC UL SUCCESSFUL");
                     /* Unbind RLC DL to MAC DL */
                     smBindUnBindKwToRguSap(WR_SM_KWDL_INST,AUBND);
                  }
               }
               RETVALUE(ROK);
            }
            if (pst->srcInst == WR_SM_PJDL_INST)
            {
               RLOG0(L_DEBUG, "BIND OF PDCP DL TO RLC DL (KWU) SAP SUCCESSFUL");
               /* Initiate control request for binding PJ to RLC */
               smBindPjUdxSap((Inst)WR_SM_KWUL_INST); 
            }
            else
            {
               RLOG0(L_DEBUG, "BIND OF PDCP UL TO RLC UL (KWU) SAP SUCCESSFUL");
               /* Initiate control request for binding RRC to RLC */
               smBindUnBindPjKwuSap((Inst)WR_SM_PJDL_INST,ABND); 

            }
            break;
         }
         case  STUDXSAP:
         {
            if (pst->srcInst == WR_SM_KWUL_INST)
            {
               RLOG0(L_DEBUG, "BIND OF PDCP UL TO PDCP DL(UDX) SAP SUCCESSFUL");
               /* Initiate control request for binding RRC to RLC */
#ifdef TIP_L3_UL2_LL2_SPLIT
         smCb.smState = WR_SM_STATE_RRC_STK_BND_DONE;
         WR_FILL_PST(pjPst, SM_UL2_SM_PROC, SM_PJ_PROC, ENTSM, ENTPJ,0,0, EVTWREGTPSTKBND, WR_POOL, SM_SELECTOR_LC);
         if(wrSmSelfPstMsg(&pjPst) != ROK)
         {
            RLOG0(L_ERROR, "DL/UL PDCP CONFIGURATION SUCCESSFULLY PERFORMED. "
               "Failure at Self Pst.");
         }
         else
         {
            RLOG0(L_DEBUG, "DL/UL PDCP CONFIGURATION SUCCESSFULLY PERFORMED.");
         } /* end of else part */
#else
               smBindUnBindNhToCkwSap(ABND_ENA); 
#endif
            }
            break;
         }
         default:
           break;
      }
   }

   RETVALUE(ROK);
} /* end of SmMiLpjCntrlCfm */


#ifdef LTE_L2_MEAS
/*
*
*       Fun:  smSndPjL2MeasStartReq 
*
*       Desc:  This function is used to  build and send L2 Meas Req 
*                to PDCP layer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/

#ifdef ANSI 
PUBLIC S16 smSndPjL2MeasStartReq
(
U16              measType
)
#else
PUBLIC S16 smSndPjL2MeasStartReq(measType)
U16    measType;
#endif
{
   U8 qciIdx = 0;
   Pst pst;
   PjL2MeasReqEvt l2MeasEvt; 
   PjL2MeasReqInfo  *measReq;

   TRC3(smSndPjL2MeasStartReq);

   RLOG1(L_DEBUG,"smSndPjL2MeasStartReq: measType[%d]",measType);
   SM_SET_ZERO(&l2MeasEvt, sizeof(PjL2MeasReqEvt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /*fillig pst structure*/
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.dstInst   = SM_INST_ZERO;

   /*filling L2 counters meas info*/
   l2MeasEvt.transId = (kpiInfo.transId)++;

   l2MeasEvt.measPeriod = 0; /*collection Period value*/
   measReq= &(l2MeasEvt.measReq);
   measReq->measType = measType;
   measReq->numQci = LPJ_MAX_QCI - 1;

   for(qciIdx = 0; qciIdx < measReq->numQci; qciIdx++)
   {
      measReq->qci[qciIdx] = qciIdx+1;
   } 
   SmMiLpjL2MeasReq(&pst,&l2MeasEvt);  
   RETVALUE(ROK);
}/*smSndPjL2MeasStartReq*/
/*
* 
*       Fun:   smBuildPjL2MeasStopReq 
* 
*       Desc:  This function is used to  build and send L2 Meas 
*                stop  Req to PDCP layer.
*             
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/

#ifdef ANSI 
PUBLIC S16 smSndPjL2MeasStopReq
(
U16              measType
)
#else
PUBLIC S16 smSndPjL2MeasStopReq(measType)
U16    measType;
#endif 
{
   Pst pst;

   TRC3(smSndPjL2MeasStopReq);

   RLOG1(L_DEBUG,"smSndPjL2MeasStopReq: measType[%d]",measType);
   SM_SET_ZERO(&pst, sizeof(Pst));

   /*fillig pst structure*/
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.dstInst   = SM_INST_ZERO;

   SmMiLpjL2MeasStopReq(&pst,measType);

   RETVALUE(ROK);
}/*smSndPjL2MeasStopReq*/

/*
* 
*       Fun:   smBuildPjL2MeasSendReq 
* 
*       Desc:  This function is used to  build and send L2 Meas 
*                stop  Req to PDCP layer.
*             
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/

#ifdef ANSI 
PUBLIC S16 smSndPjL2MeasSendReq
(
U16              measType
)
#else
PUBLIC S16 smSndPjL2MeasSendReq(measType)
U16    measType;
#endif
{
   Pst pst;

   TRC3(smSndPjL2MeasSendReq);

   RLOG1(L_DEBUG,"smSndPjL2MeasSendReq: measType[%d]",measType);
   SM_SET_ZERO(&pst, sizeof(Pst));

   /*fillig pst structure*/
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTPJ;
   pst.dstProcId = SM_PJ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.dstInst   = SM_INST_ZERO;

   SmMiLpjL2MeasSendReq(&pst,measType);
   RETVALUE(ROK);
}/*smSndPjL2MeasSendReq*/

/*
*
*       Fun:    SmMiLpjL2MeasReq 
*
*       Desc:  This function is used to send L2 Meas req 
*              to Pdcp Layer 
*
*       Ret:   S16 ret
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasReq
(
Pst * pst,
PjL2MeasReqEvt *l2MeasEvt
)
#else
PUBLIC S16 SmMiLpjL2MeasReq(pst, l2MeasEvt)
Pst * pst;
PjL2MeasReqEvt *l2MeasEvt;
#endif
{
   TRC3(SmMiLpjL2MeasReq);

   (*SmMiLpjL2MeasStartReqMt[pst->selector])(pst, l2MeasEvt);

   RETVALUE(ROK);
}/*SmMiLpjL2MeasReq*/

/*
*
*       Fun:    SmMiLpjL2MeasStopReq 
*
*       Desc:  This function is used to send L2 Meas Stop req 
*              to Pdcp Layer 
*
*       Ret:   S16 ret
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasStopReq
(
Pst *pst,
U16 measType
)
#else
PUBLIC S16 SmMiLpjL2MeasStopReq(pst, measType)
Pst *pst;
U16 measType
#endif
{
   TRC3(SmMiLpjL2MeasStopReq);

   (*SmMiLpjL2MeasStopReqMt[pst->selector])(pst,measType);

   RETVALUE(ROK);
}/*SmMiLpjL2MeasReq*/

/*
*
*
*       Fun:    SmMiLpjL2MeasSendReq 
*
*       Desc:  This function is used to send L2 Meas Stop req 
*              to Pdcp Layer 
*
*       Ret:   S16 ret
*
*       Notes: None
*
*       File:  wr_smm_pdcp.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasSendReq
(
Pst *pst,
U16 measType
)
#else
PUBLIC S16 SmMiLpjL2MeasSendReq(pst, measType)
Pst *pst;
U16 measType;
#endif
{
   TRC3(SmMiLpjL2MeasSendReq);

   (*SmMiLpjL2MeasSendReqMt[pst->selector])(pst,measType);

   RETVALUE(ROK);
}/*SmMiLpjL2MeasSendReq*/

/*
*
*       Fun:   SmMiLpjL2MeasCfm
*
*       Desc:  This function is recevied L2 Cntr meas cfm
*              from Pdcp layer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_pj_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasCfm
(
Pst     *pst,           /* post structure */
PjL2MeasCfmEvt *measEvt /* measuremnet */
)
#else
PUBLIC S16 SmMiLpjL2MeasCfm(pst, measEvt)
Pst     *pst;           /* post structure */
PjL2MeasCfmEvt *measEvt; /* measuremnet */
#endif
{
   S16 ret = ROK;
   U32  kpiId = INVALID_KPI;
   U32  kpiId1 = INVALID_KPI;
   U16 numOfQcis;
   U16  measType;
   U8  qciVal;
   U8  indx;

   TRC2(SmMiLpjL2MeasCfm);

   measType = measEvt->measType;
   numOfQcis = measEvt->numQciCfm;
   (kpiInfo.numOfRcvdL2MeasCfm)++;
   kpiInfo.measConfigRecv |= WR_MEAS_PDCP_CFG;
   RLOG3(L_DEBUG,"count[%d] meastype[%d] NbQci[%d]",
      kpiInfo.numOfRcvdL2MeasCfm, measType, numOfQcis);

   for(indx = 0 ; indx < numOfQcis;indx++)
   {
      qciVal = measEvt->measCfm[indx].qci;
      if( (qciVal < 1) || (qciVal > 9) ) 
      {
         RLOG1(L_ERROR,"Error Condition qciVal[%d]",qciVal);
         continue;
      }
      /*Updtes PDCP DL DELAY L2 cntrs in OAM*/
      if((measType & LPJ_L2MEAS_DL_DELAY) == LPJ_L2MEAS_DL_DELAY)
      {
         kpiId = KPI_ID_LTE_DRB_PDCPSDUDELAYDL_QCI1;
         WR_INC_KPI((kpiId + qciVal - 1),KPI_VALUE_TYPE_INTEGER,
               measEvt->measCfm[indx].dlDelay);
         WR_INC_KPI(KPI_ID_LTE_RB_PDCPSDUDELAYDL_QCI_SUM,KPI_VALUE_TYPE_INTEGER,
               measEvt->measCfm[indx].dlDelay);
      }/*LPJ_L2MEAS_DL_DELAY*/
      /*Updates PDCP LD DISCARD L2 cntrs in OAM */
      if((measType & LPJ_L2MEAS_DL_DISC) == LPJ_L2MEAS_DL_DISC)
      {
         kpiId = KPI_ID_LTE_DRB_PDCPSDUDROPRATEDL_QCI1;
         WR_INC_KPI((kpiId + qciVal - 1),KPI_VALUE_TYPE_INTEGER,
               measEvt->measCfm[indx].dlDisc);
         WR_INC_KPI(KPI_ID_LTE_DRB_PDCPSDUDROPRATEDL_QCI_SUM,
               KPI_VALUE_TYPE_INTEGER,measEvt->measCfm[indx].dlDisc);
      }/*LPJ_L2MEAS_DL_DISC*/
      /*Updates PDCP UL LOSS L2 cntrs in OAM*/
      if((measType & LPJ_L2MEAS_UL_LOSS) == LPJ_L2MEAS_UL_LOSS)
      {
         kpiId =  KPI_ID_LTE_DRB_PDCPSDULOSSRATEUL_QCI1;
         WR_INC_KPI((kpiId + qciVal - 1),KPI_VALUE_TYPE_INTEGER,
               measEvt->measCfm[indx].ulLoss);
         WR_INC_KPI(KPI_ID_LTE_DRB_PDCPSDULOSSRATEUL_QCI_SUM,
               KPI_VALUE_TYPE_INTEGER,measEvt->measCfm[indx].ulLoss);
      }/*LPJ_L2MEAS_UL_LOSS*/

   }/*end of for loop*/
   if((measType & LPJ_L2CPU_PERCORE_STATS) == LPJ_L2CPU_PERCORE_STATS)
   {  
      for(indx = 0; indx < measEvt->numCores;indx++)
      {
         kpiId = KPI_ID_LTE_L2CPUSTATS_CORE0_AVG;
         WR_INC_KPI((kpiId + indx ),KPI_VALUE_TYPE_INTEGER,
               measEvt->cmLteCpuInfo[indx].avgCpuUtil);
         kpiId1 = KPI_ID_LTE_L2CPUSTATS_CORE0_MAX;
         WR_INC_KPI((kpiId1 + indx ),KPI_VALUE_TYPE_INTEGER,
               measEvt->cmLteCpuInfo[indx].maxCpuUtil);
      }
   }/*LPJ_L2CPU_PERCORE_STATS*/
   /*Increments number of confirm recevied from PDCP layer*/

   RLOG0(L_DEBUG,"Received Confirmation");
   //if(kpiInfo.numOfTrggrL2MeasReq == kpiInfo.numOfRcvdL2MeasCfm)
   if( kpiInfo.measConfigRecv == WR_MEAS_CFG_DONE )
   {
#ifdef WR_RSYS_OAM
      KpisInfoSentNotification();
#endif
      kpiInfo.measConfigRecv = 0;
      kpiInfo.numOfTrggrL2MeasReq = WR_KPI_SET_TO_ZERO;
      kpiInfo.numOfRcvdL2MeasCfm  = WR_KPI_SET_TO_ZERO;
   }
   RETVALUE(ret);
} /* SmMiLpjStsCfm */

/*
*
*       Fun:   SmMiLpjL2MeasStopCfm
*
*       Desc:  This function is recevied L2 Cntr meas cfm
*              from Pdcp layer.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_pj_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasStopCfm
(
Pst     *pst,           /* post structure */
U16     measType,
U8      status
)
#else
PUBLIC S16 SmMiLpjL2MeasStopCfm(pst, measEvt)
Pst     *pst;           /* post structure */
U16      measType; /* measuremnet */
U8      status;
#endif
{
   TRC2(SmMiLpjL2MeasStopCfm);

   kpiInfo.numOfL2MeasStopCfm++;
   if(kpiInfo.numOfL2MeasStopReq == kpiInfo.numOfL2MeasStopCfm)
   {
      /*KpiCollection is stopped*/
      wrKpiStopKpiCollecPrcCfm();
      kpiInfo.numOfL2MeasStopReq = WR_KPI_SET_TO_ZERO;
      kpiInfo.numOfL2MeasStopCfm = WR_KPI_SET_TO_ZERO;
   } 
   RETVALUE(ROK);
}
#endif/*LTE_L2_MEAS*/ 

#ifdef __cplusplus
}
#endif /* cplusplus */



/********************************************************************30**

           End of file:     fc_smm_pdcp_intel.c@@/main/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:37 2016

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
