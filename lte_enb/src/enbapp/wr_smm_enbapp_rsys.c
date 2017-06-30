
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_enbapp_rsys.c

     Sid:      fc_smm_enbapp_rsys_t2k.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:52:12 2014

     Prg:      Sriky 

*********************************************************************21*/
#include "wr.h"
#include "wr_emm.h"
#include "wr_lwr.h"
#include "wr_cmn.h"
#include "wr_smm_smallcell.h"
#include "wr_smm_init.h"
#include "wr_utils.h"
#include "wr_emm_mme.h"
#include "lys.h"
#include "lys.x"
#ifdef TIP_L3_UL2_LL2_SPLIT
#include "wr_smm_init.h"
#include "wr_dam.h"
#endif
#ifdef LWLCSMMILWR
#define  MAXWRMI  3
#if (!defined(LCSMMILWR) || !defined(WR) ||!defined(LWLCSMMILWR))
#define PTSMMILWR
#endif
#else
#define  MAXWRMI  2
#if (!defined(LCSMMILWR) || !defined(WR))
#define PTSMMILWR
#endif
#endif
#ifdef RM_INTF
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_FILE_ID=116;


static int RLOG_MODULE_ID=2;

U16   tipCellId = 0;

static U8    cfgCfmRcvd = 0;
#include "rmu.h" /*RRM->FSM */
#endif /*RM_INTF*/
#include "tip_cmn.h"


EXTERN TipVmAssocInfo ul2Info[1];
EXTERN U32 tipFetchUl2ProcIdFromCellId (U16 cellId);
PUBLIC S16 SmMiLwrAddNeighCfm(Pst *spst,LwrMngmt *cfg);
PUBLIC S16 SmMiLwrCntrlCfm(Pst *pst,LwrMngmt *cntrl);
PUBLIC S16 SmMiLwrAddNeighCfgReq(Pst *pst,LwrMngmt *cntrl);
PUBLIC S16 smBuildCdmaHrpdaBandClass( LwrMngmt *lwrMng );
PUBLIC S16 wrSmmEnbBuildCdma1xRTTBandClass(LwrMngmt *lwrMng, U8  cellCfgIdx);
PUBLIC S16 wrSmmEnbBuildWrNr1xCdmaFreqCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
);
PUBLIC S16 wrSmmEnbBuildWrNr1xCdmaCellCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
);
#ifdef WR_RSYS_OAM
extern PUBLIC Void msmDynConfigComplete(MsmCfmType msmcfmsuccess,MsmCauseType msmcausena, MsmDynCfmInfo dynCfmInfo);
extern PUBLIC S16 smHdlNeighEnbCfgDel(Void);
PUBLIC Void updateMsmNeiCellParams(MsmEUTRANeighCell *dst, LwrEUTRANeighCell *src);
#endif
#ifdef PTSMMILWR
PRIVATE S16 PtMiLwrCfgReq    (Pst *pst, LwrMngmt *cfg);
PRIVATE S16 PtMiLwrCntrlReq  (Pst *pst, LwrMngmt *cntrl);
PRIVATE S16 PtMiLwrLoadInd (Pst *spst, LwrLoadIndInfo *loadIndInfo);
PRIVATE S16 PtMiLwrDynCfgReq(Pst *pst,LwrDynMngmt *dynCfg);
PRIVATE S16 PtMiLwrAddNeighCfm(Pst *spst,LwrMngmt *cfg);
#endif

PRIVATE S16 smSndWrNr1xCdmaFreqCfg(U8   cellCfgIdx);
PRIVATE S16 smSndWrNr1xCdmaCellCfg(U8   cellCfgIdx);
PRIVATE S16 smSndWrNhUtraFddCellCfg(U8    cellCfgIdx);
PRIVATE S16 smSndWrNhUtraTddCellCfg(U8    cellCfgIdx);
PRIVATE S16 smSndWrNrUtraFddFreqCfg(U8    cellCfgIdx);
PRIVATE S16 smSndWrNrUtraTddFreqCfg(U8    cellCfgIdx);
PRIVATE S16 smSndWrNrEutraFreqCfg(U8   cellCfgIdx);
#ifndef LTE_PAL_ENB
//PRIVATE S16 smBuildWrstopPHYCntrl(Void); /* IPSEC*/
#endif
#ifdef WR_RSYS_OAM
EXTERN Void FapAlarmInd(U32 alarmId, U8 severity, U8 causeType, U8 causeVal);
EXTERN Void MsmOperationalState(U32 opstate);
#endif

#if defined (WR_RSYS_OAM) || (WR_DBG_CIRLOG) 
EXTERN S16 smRegInitTmr ARGS((Void));
EXTERN S16 smStartTmr ARGS((PTR cb, S16 tmrEvnt,U32 delay));
EXTERN S16 smStopTmr ARGS((PTR cb, S16 tmrEvnt));
EXTERN Void smStaticCfgFailAlarm ARGS((Void));
EXTERN Void smDynCfgFailAlarm ARGS((U32 event));
EXTERN MsmFapParameters   fapParameters;
U32 smDynTmrEvent = 0;
#endif

#ifdef WR_TEST_CODE
EXTERN Void smWrProcCliMsg(Void);
#endif
PUBLIC S16 smBuildWrNluLSapCfg (SuId  suId, SpId  spId);

PRIVATE U32 wrWrCfg = 0;
PRIVATE U32 wrCellWrCfg = 0;
PRIVATE U8 wrNumPjuSaps = 1;
PRIVATE U8 wrNumCellCntrls = 0;
PRIVATE U8 cellCfgCfmIdx = 0;
/* extern declarations */
EXTERN S16 SReInitTmr(void);
 #ifdef TIP_L3
EXTERN Void smWrConfigCell(U16  cellId);
#endif
/*
*
*       Fun:   Initialize RRC App task.
*
*       Desc:  Invoked to create RRC App TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smWrInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smWrInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smWrInit)

   /* Register ENB TAPA Task */
   if (SRegTTsk((Ent)ENTWR, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR2,
                 wrActvInit, (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Removed registering of RRM task into WR entity, as new st=ystem task is
    * spawned for new RRM*/

   /* Register RRC APP TAPA Task */
   if (SRegTTsk((Ent)ENTNX, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR2,
                 NULLP, (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }


   /* Attach EGTP AND CL USER TAPA Task */
   /* Mapping of VE to WR as EGTP and CL still send to VE */
   if (SRegTTsk((Ent)ENTVE, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR2,
                 wrActvInit, (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach ENB TAPA Task */
   if (SAttachTTsk((Ent)ENTWR, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach RRM TAPA Task */
   if (SAttachTTsk((Ent)ENTWR, (Inst)RRM_INST_ID, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */


   /* Attach RRC APP TAPA Task */
   if (SAttachTTsk((Ent)ENTNX, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }



   /* Attach EGTP AND CL USER TAPA Task */
   /* Mapping of VE to WR as EGTP and CL still send to VE */
   if (SAttachTTsk((Ent)ENTVE, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }

   RLOG1(L_DEBUG,"RRC App Tapa Task successfully registered and attached to %d",
      sysTskId);

   RETVALUE(ROK);
} /* end of smWrInit */

#ifdef EU_DAT_APP

/*
*
*       Fun:   Initialize Data App task.
*
*       Desc:  Invoked to create Data App TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smEuInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smEuInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smEuInit)
    /* Register Data APP TAPA Task */
   if (SRegTTsk((Ent)ENTEU, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR1,
                 wrDamActvInit , (ActvTsk)wrDamActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

    /* Register Data APP TAPA Task */
   if (SRegTTsk((Ent)ENTPX, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR1,
                 NULLP , (ActvTsk)wrDamActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach RRC APP TAPA Task */
   if (SAttachTTsk((Ent)ENTEU, (Inst)0, sysTskId)!= ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Attach RRC APP TAPA Task */
   if (SAttachTTsk((Ent)ENTPX, (Inst)0, sysTskId)!= ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* end of smEuInit */

#endif /* EU_DAT_APP */

/*
*
*       Fun:   smSndWrCdmaHrpdBandClass
*
*       Desc:  This function for sending eNodeB Cell band class 
*               Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/

/*
*
*       Fun:   smSndWrCdma1xRTTBandClass
*
*       Desc:  This function for sending eNodeB Cell band class 
*               Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c 
*
*/
#ifdef ANSI
PRIVATE S16 smSndWrCdma1xRTTBandClass
(
 U8      cellCfgIdx
)
#else
PRIVATE S16 smSndWrCdma1xRTTBandClass(cellCfgIdx)
 U8      cellCfgIdx;
#endif
{
   LwrMngmt   *lwrMng = NULLP;
   Pst        pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   if (NULLP == lwrMng)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }/* End of if condition.*/

   SM_SET_ZERO(&pst, sizeof(Pst));
   
   wrSmmEnbBuildCdma1xRTTBandClass(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.transId             = LWR_TRANSID_CDMA1XRTT_BAND;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif
   
   RETVALUE(ROK);
} /* end of smSndWrCdma1xRTTBandClass */

/*
*
*       Fun:   smSndWrEnbCfg
*
*       Desc:  This function for sending eNode Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/

#ifdef ANSI
PRIVATE S16 smSndWrEnbCfg
(
void
)
#else
PRIVATE S16 smSndWrEnbCfg()
#endif
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrEnbCfg(lwrMng,WR_SM_DFLT_CELL_INDX);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.transId             = LWR_TRANSID_ENBCFG;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smSndWrCellCfg
*
*       Desc:  This function for sending eNodeB Cell Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PRIVATE S16 smSndWrCellCfg
(
U8              cellCfgIdx
)
#else
PRIVATE S16 smSndWrCellCfg(cellCfgIdx)
U8              cellCfgIdx;
#endif
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   if(RFAILED == wrSmmEnbBuildCellCfg(lwrMng, cellCfgIdx))
   {
      RETVALUE(RFAILED);
   }
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_CELLCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smSndWrModCellCfg
*
*       Desc:  This function used to modify cell cfg.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrModCellCfg
(
 U8       cellCfgIndx
)
#else
PUBLIC S16 smSndWrModCellCfg(cellCfgIndx)
   U8       cellCfgIndx;
#endif
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /*smBuildModCellCfg(lwrMng, cellCfgIndx);*/
   wrSmmEnbBuildModCellCfg(lwrMng, cellCfgIndx);

   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   /* filling the proper selector value */
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);

   RETVALUE(ROK);
}



/*
*
*       Fun:   smSndWrNhUtraFddCellCfg
*
*       Desc:  This function for sending Utra FDD neighbour Cell Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c 
*
*/
#ifdef ANSI
PRIVATE S16 smSndWrNhUtraFddCellCfg
(
U8    cellCfgIdx
)
#else
PRIVATE S16 smSndWrNhUtraFddCellCfg(cellCfgIdx)
U8    cellCfgIdx;
#endif
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = cellCfgIdx + 1;  /* this is ownCellID in case of PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = lteeNodeBparams[cellCfgIdx]. \
                                                lteNeighCellCfg.numUtraCells;
   wrSmmEnbBuildWrNehUtraFddCellCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NHUTRAN_CELLCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif
   
   RETVALUE(ROK);
}


/*
*
*       Fun:   smSndWrNhUtraTddCellCfg
*
*       Desc:  This function for sending Utra Tdd neighbour Cell Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PRIVATE S16 smSndWrNhUtraTddCellCfg
(
U8    cellCfgIdx
)
#else
PRIVATE S16 smSndWrNhUtraTddCellCfg(cellCfgIdx)
U8    cellCfgIdx;
#endif
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = cellCfgIdx + 1;  /* this is ownCellID in case of PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numUtraTddCells;

   wrSmmEnbBuildWrNehUtraTddCellCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NHUTRAN_CELLCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);
   
   RETVALUE(ROK);
}


/*
*
*       Fun:   smSndWrNhCellCfg
*
*       Desc:  This function for sending neighbour Cell Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/

#ifdef ANSI
PRIVATE S16 smSndWrNhCellCfg
(
 U8      cellCfgIdx
)
#else
PRIVATE S16 smSndWrNhCellCfg(cellCfgIdx)
U8    cellCfgIdx;
#endif
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrNehCellCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NHCELLCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smSndWrNhCfg
*
*       Desc:  This function for sending Neighbour eNodeB Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
PRIVATE S16 smSndWrNhCfg
(
 U8      cellCfgIdx
)
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrNghCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NHCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smSndWrMmeCfg
*
*       Desc:  This function for sending MME Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
PRIVATE S16 smSndWrMmeCfg
(
LwrSmMmeCfg *mmeCfg
)
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrMmeCfg(lwrMng, mmeCfg);
   
   lwrMng->hdr.msgType             = TCFG;

   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.transId             = LWR_TRANSID_MME;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);
   
   RETVALUE(ROK);
}


/*
 *
 *       Fun:    smSndWrNrCdmaHrpdFreqCfg - configure Neighbour 1xCdma frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */



/*
 *
 *       Fun:    smSndWrNr1xCdmaFreqCfg - configure Neighbour 1xCdma frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PRIVATE S16 smSndWrNr1xCdmaFreqCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   if (NULLP == lwrMng)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }/* End of if condition.*/

   SM_SET_ZERO(&pst, sizeof(Pst));
   
   wrSmmEnbBuildWrNr1xCdmaFreqCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_CDMA1XRTT_FREQ;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}
 
/*
 *
 *       Fun:    smSndWrNr1xCdmaCellCfg - configure Neighbour 1xCdma Cell
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */

PRIVATE S16 smSndWrNr1xCdmaCellCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   if (NULLP == lwrMng)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }/* End of if condition.*/

   SM_SET_ZERO(&pst, sizeof(Pst));
   
   wrSmmEnbBuildWrNr1xCdmaCellCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.transId            = LWR_TRANSID_CDMA1XRTT_CELL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smSndWrNrUtraFddFreqCfg - configure Neighbour Utra FDD frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp_rsys.c
 *
 */
PRIVATE S16 smSndWrNrUtraFddFreqCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = (cellCfgIdx + 1); /* this is ownCellID in case of
                                           PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = (U8)lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraFreq;

   wrSmmEnbBuildWrNrUtraFddFreqCfg(lwrMng, cellCfgIdx);

   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NRUTRAN;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smSndWrNrUtraTddFreqCfg - configure Neighbour Utra TDD frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp_rsys.c
 *
 */
PRIVATE S16 smSndWrNrUtraTddFreqCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = (cellCfgIdx + 1); /* this is ownCellID in case of
                                           PLD based conf, jst a logic entity */
   /* lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = wrSmDfltNumofUtraNrFreq;*/
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = (U8)lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraTddFreq;

   wrSmmEnbBuildWrNrUtraTddFreqCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NRUTRAN;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}



/*
 *
 *       Fun:    smSndWrNrGeranFreqCfg
 *
 *       Desc:   GERAN frequency configuration filling function
 *
 *       Ret:    S16
 *
 *       Notes:  None
 *
 *       File:   wr_smm_enbapp_rsys.c
 *
 */ 
PRIVATE S16 smSndWrNrGeranFreqCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrNrGeranFreqCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_GERAN_FREQ;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}/* End of smSndWrNrGeranFreqCfg */


/*
 *
 *       Fun:    smSndWrNrGeranCellCfg
 *
 *       Desc:   GERAN cell configuration filling function
 *
 *       Ret:    S16
 *
 *       Notes:  None
 *
 *       File:   wr_smm_enbapp_rsys.c
 *
 */
PRIVATE S16 smSndWrNrGeranCellCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrNrGeranCellCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_GERAN_CELL;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region    = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}/* End of smSndWrNrGeranCellCfg */


/*
 *
 *       Fun:    smSndWrEutraNrFreqCfg - configure Neighbour Eutra frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PRIVATE S16 smSndWrNrEutraFreqCfg
(
 U8      cellCfgIdx
 )
{
   LwrMngmt *lwrMng = NULLP;
   Pst pst;
   
   
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildWrNrEutraFreqCfg(lwrMng, cellCfgIdx);
   
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_NREUTRAN;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, lwrMng);
#else
   (Void) SmMiLwrCfgReq(&pst, lwrMng);
#endif

   RETVALUE(ROK);
}
/*
 *
 *       Fun:    wrSmWrCfg - configure WR 
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_sz_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmWrCfg
(
Void
)
#else
PUBLIC Void wrSmWrCfg(Void)
#endif /* ANSI */
{
   
   TRC2(wrSmWrCfg)
   wrWrCfg = 0;  

#ifdef WR_DBG_CIRLOG
   if (smRegInitTmr() != ROK)
   {
      RLOG0(L_ERROR, "smRegInitTmr Failed");
      RETVOID;
   }

   cmInitTimers(&(smCb.cfgCb.logTimer), 1);
   smStartTmr((PTR)&(smCb),SM_TMR_LOG_TMR, SM_TMR_LOG_TMR_VAL);
#endif
   /* To handle FAP ADMIN DOWN-UP scenario */
   wrNumPjuSaps = 1;

#ifdef WR_RSYS_OAM  
   smStartTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR, SM_TMR_STATIC_CFG_TMR_VAL);
#endif

   smBuildWrGenCfg();
   
   RETVOID;
} /* end of wrSmWrCfg */



/*
*
*       Fun:   wrSmmSendDynNbrEnbCfg
*
*       Desc:  fill in neighbour Cfg for WR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 wrSmmSendDynNbrEnbCfg
(
U32    dbIndex
)
#else
PUBLIC S16 wrSmmSendDynNbrEnbCfg(dbIndex)
U32    dbIndex;
#endif
{
   LwrMngmt lwrMng;
   Pst pst;


   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   wrSmmEnbBuildDynWrNbrEnbCfg(dbIndex,&lwrMng);

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

/*   smCb.smState = WR_SM_STATE_DYN_X2AP_CFG_DONE;*/
   (Void) SmMiLwrAddNeighCfm(&pst, &lwrMng);
  
   RETVALUE(ROK);

}/*wrSmmSendDynNbrEnbCfg */

/*
*
*       Fun:   smBuildDamGenCfg
*
*       Desc:  fill in genCfg for WR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildDamGenCfg
(
Void
)
#else
PUBLIC S16 smBuildDamGenCfg(Void)
#endif
{
   LwrMngmt  *wrMgt = NULLP;
   LwrGenCfg    *cfg = NULLP;
   Pst       pst;
   
   TRC2(smBuildDamGenCfg)
   
   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cfg   = &(wrMgt->t.cfg.t.genCfg);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildGenCfg(wrMgt,WR_SM_DFLT_CELL_INDX);
#ifdef TIP_L3_UL2_LL2_SPLIT
   cfg->lmPst.srcProcId = SM_UL2_SM_PROC;
#else
   cfg->lmPst.srcProcId = SM_SM_PROC;
#endif
   cfg->lmPst.dstProcId = SM_EU_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTSM;
   cfg->lmPst.dstEnt = (Ent)ENTEU;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)WRSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = WR_MEM_REGION;
   cfg->lmPst.pool   =  WR_POOL;
   cfg->lmPst.selector = SM_SELECTOR_LWLC;
   cfg->timeRes = 10;
  
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTEU;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRGEN;
   wrMgt->hdr.elmId.elmntInst1    = 0;
   wrMgt->hdr.elmId.elmntInst2    = 0;
   wrMgt->hdr.elmId.elmntInst3    = 0;
   wrMgt->hdr.seqNmb              = 0;
   wrMgt->hdr.version             = 0;
   wrMgt->hdr.transId             = LWR_TRANSID_GEN;

   wrMgt->hdr.response.prior      = PRIOR0;
   wrMgt->hdr.response.route      = RTESPEC;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEU;
   pst.dstProcId = SM_EU_PROC;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "RRM Gen Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiDamLwrCfgReq(&pst, wrMgt);
 
   RETVALUE(ROK);
}/* smBuildDamGenCfg */



/*
*
*       Fun:   smBuildWrGenCfg
*
*       Desc:  fill in genCfg for WR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrGenCfg
(
Void
)
#else
PUBLIC S16 smBuildWrGenCfg(Void)
#endif
{
   LwrMngmt  *wrMgt = NULLP;
   LwrGenCfg    *cfg = NULLP;
   Pst       pst;
   
   TRC2(smBuildWrGenCfg)
   
   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cfg   = &(wrMgt->t.cfg.t.genCfg);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   wrSmmEnbBuildGenCfg(wrMgt,WR_SM_DFLT_CELL_INDX);

   cfg->lmPst.srcProcId = SM_SM_PROC;
   cfg->lmPst.dstProcId = SM_WR_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTWR;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)WRSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = WR_MEM_REGION;
   cfg->lmPst.pool   =  WR_POOL;
   cfg->lmPst.selector = SM_SELECTOR_LWLC;
   cfg->timeRes = 10;
  
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRGEN;
   wrMgt->hdr.elmId.elmntInst1    = 0;
   wrMgt->hdr.elmId.elmntInst2    = 0;
   wrMgt->hdr.elmId.elmntInst3    = 0;
   wrMgt->hdr.seqNmb              = 0;
   wrMgt->hdr.version             = 0;
   wrMgt->hdr.transId             = LWR_TRANSID_GEN;

   wrMgt->hdr.response.prior      = PRIOR0;
   wrMgt->hdr.response.route      = RTESPEC;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "RRM Gen Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
 
   RETVALUE(ROK);
}/* smBuildWrGenCfg */

/*
*
*       Fun:   smBuildWrCtfLSapCfg
*
*       Desc:  Call handler for CTF LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrCtfLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrCtfLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrCtfLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_YS_PROC;
#ifdef LTE_ENB_PAL
   cfg->dstEnt       = ENTTF;
#else   
   cfg->dstEnt       = ENTYS;
#endif /* LTE_ENB_PAL */   
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRYSSEL;
   cfg->srcEnt       = ENTVE;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRCTFSAP;
   wrMgt->hdr.elmId.elmntInst1    = 0;
   wrMgt->hdr.elmId.elmntInst2    = 0;
   wrMgt->hdr.elmId.elmntInst3    = 0;
   wrMgt->hdr.seqNmb              = 0;
   wrMgt->hdr.version             = 0; 
   wrMgt->hdr.transId             = LWR_TRANSID_CTF;

   wrMgt->hdr.response.prior      = PRIOR0;
   wrMgt->hdr.response.route      = RTESPEC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "RRM Ctf LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);

   RETVALUE(ROK);
}/* smBuildWrCtfLSapCfg */

/*
*
*       Fun:   smBuildWrNhuLSapCfg
*
*       Desc:  Call handler for NHU LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrNhuLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrNhuLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst pst;
   
   TRC2(smBuildWrNhuLSapCfg)
   
   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_NH_PROC;
   cfg->dstEnt       = ENTNH;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRNHSEL;
   cfg->srcEnt       = ENTNX;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRNHUSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_NHU;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;
   
    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "RRM Nhu LSap Cfg sent ");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
   
   RETVALUE(ROK);
}/* smBuildWrNhuLSapCfg */

/*
*
*       Fun:   smBuildWrNluLSapCfg
*
*       Desc:  Call handler for NLU LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_enbapp.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrNluLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrNluLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;

   TRC2(smBuildWrNluLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   if(NULLP == wrMgt)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_NL_PROC;
   cfg->dstEnt       = ENTNL;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = NLU_SEL_LWLC;
   cfg->srcEnt       = ENTWR;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRNLUSAP;
   wrMgt->hdr.transId            = LWR_TRANSID_NLU;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

#ifdef DEBUGP
  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, "ENBAPP to SON LSAP Cfg sent\n"));
#endif
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);

   RETVALUE(ROK);
}/* smBuildWrNluLSapCfg */

#ifdef RM_INTF
/*
*
*       Fun:   smBuildWrRmuLSapCfg
*
*       Desc:  Call handler for RMU LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrRmuLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrRmuLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrRmuLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if (NULLP == wrMgt)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }/* End of if condition.*/

   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);
   if (NULLP == cfg)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }/* End of if condition.*/


   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_RM_PROC;
   /* cfg->dstEnt       = ENTKW; */
   cfg->dstEnt       = ENTRM;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = RMU_SEL_LWLC;
   cfg->srcEnt       = ENTWR;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRRMUSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_RMU;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

  RLOG0(L_DEBUG, "FSM to RRM LSAP Cfg sent ");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
 
   RETVALUE(ROK);
}/* smBuildWrRmuLSapCfg */
#endif /*RM_INTF*/

#ifdef EU_DAT_APP

/*
*
*       Fun:   smBuildWrPjuLSapCfg
*
*       Desc:  Call handler for PJU LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrPjuLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrPjuLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;

   TRC2(smBuildWrPjuLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_PJ_PROC;
   /* Shwetha - adding PDCP's entity Id instead of RLC's for data application's
      lower SAP */
   /* cfg->dstEnt       = ENTKW; */
   cfg->dstEnt       = ENTPJ;
   cfg->dstInst      = (suId == WR_SM_PJUL_INST) ? WR_SM_PJDL_INST : WR_SM_PJUL_INST;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRPJSEL;
   cfg->srcEnt       = ENTPX;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_DATAPP_MEM_REGION;
   cfg->mem.pool     = WR_POOL;
   
   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
#ifdef TIP_L3_UL2_LL2_SPLIT
   wrMgt->hdr.entId.ent           = ENTEU;
#else
   wrMgt->hdr.entId.ent           = ENTWR;
#endif
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRPJUSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_PJU;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
   pst.dstEnt    = ENTEU;
   pst.dstProcId = SM_EU_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
#endif
   pst.region = smCb.init.region;

  RLOG0(L_DEBUG,"RRM Nhu LSap Cfg sent");
   /* Send the request to the LM */
#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiDamLwrCfgReq(&pst, wrMgt);
#else
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
#endif

   RETVALUE(ROK);
}/* smBuildWrPjuLSapCfg */

#endif  /* EU_DAT_APP */

/*
*
*       Fun:   smBuildWrRgrLSapCfg
*
*       Desc:  Call handler for RGR LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrRgrLSapCfg
(

SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrRgrLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
   
   TRC2(smBuildWrRgrLSapCfg)
   
   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;
                                                          
   cfg->dstProcId    = SM_RG_PROC;
   cfg->dstEnt       = ENTRG;
   cfg->dstInst      = (Inst)(wrSmDfltNumCells + 1);
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRRGSEL;
   cfg->srcEnt       = ENTNX;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRRGRSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_RGR;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

  RLOG0(L_DEBUG, "RRM Rgr LSap Cfg sent");
   /* Send the request to the LM */
#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, wrMgt);
#else
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
#endif
                                                      
   RETVALUE(ROK);
}/* smBuildWrRgrLSapCfg */
                                                        
                                                       
/*
*
*       Fun:   smBuildWrSztLSapCfg
*
*       Desc:  Call handler for SZT LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrSztLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrSztLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;

   TRC2(smBuildWrSztLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_SZ_PROC;
   cfg->dstEnt       = ENTSZ;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRSZSEL;
   cfg->srcEnt       = ENTWR;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;
   
   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRSZTSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_SZT;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "RRM Szt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);

   RETVALUE(ROK);
}/* smBuildWrSztLSapCfg */

/*
*
*       Fun:   smBuildWrCztLSapCfg
*
*       Desc:  Call handler for CZT LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrCztLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrCztLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst       pst;

   TRC2(smBuildWrCztLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_CZ_PROC;
   cfg->dstEnt       = ENTCZ;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRCZSEL;
   cfg->srcEnt       = ENTWR;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRCZTSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_CZT;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   RLOG0(L_DEBUG, "RRM Czt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
   
   RETVALUE(ROK);
}/* smBuildWrCztLSapCfg */


/*
*
*       Fun:   smBuildWrDamLSapCfg
*
*       Desc:  Call handler for DAM LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c
*
*/

#ifdef ANSI
PUBLIC S16 smBuildWrDamLSapCfg
(
SuId        suId,             /*  App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrDamLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
   
   TRC2(smBuildWrDamLSapCfg)
   
   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }

   /* suId is passed as cellIdx, which starts from 0, to get cellId we need to
    * increment cellIdx by 1 */
   cfg->dstProcId    = tipFetchUl2ProcIdFromCellId(suId + 1);
   if( cfg->dstProcId == 0xFF )
   {
      RLOG0(L_FATAL, "Invalid ProcID");
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;
   cfg->dstEnt       = ENTEU;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRDAMSEL;
   cfg->srcEnt       = ENTWR;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
   wrMgt->hdr.entId.ent           = ENTWR;
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRDAMSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_DAMCFG;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

    RLOG0(L_DEBUG, "DAM LSap Cfg sent");
   /* Send the request to the LM */
#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiLwrCellCfgReq(&pst, wrMgt);
#else
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
#endif
                                                      
   RETVALUE(ROK);

}/* smBuildWrDamLSapCfg */


#ifdef EU_DAT_APP
/*
*
*       Fun:   smBuildWrEgtLSapCfg
*
*       Desc:  Call handler for EGT LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrEgtLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrEgtLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrEgtLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
  
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_EG_PROC;
   cfg->dstEnt       = ENTEG;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
#ifndef LC_EGTP_THREAD
   cfg->dstSel       = WRSM_WREGSEL;
#else
   cfg->dstSel       = 0;
#endif
   cfg->srcEnt       = ENTVE;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_DATAPP_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
#ifdef TIP_L3_UL2_LL2_SPLIT
   wrMgt->hdr.entId.ent           = ENTEU;
#else
   wrMgt->hdr.entId.ent           = ENTWR;
#endif
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWREGTSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_EGT;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.dstEnt    = ENTEU;
   pst.dstProcId = SM_EU_PROC;
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.region = smCb.init.region;

  RLOG0(L_DEBUG, "RRM Egt LSap Cfg sent");
   /* Send the request to the LM */
#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiDamLwrCfgReq(&pst, wrMgt);
#else
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
#endif
 
   RETVALUE(ROK);
}/* smBuildWrEgtLSapCfg */
#endif  /* EU_DAT_APP  */

#ifdef TIP_L3_UL2_LL2_SPLIT
/*
*
*       Fun:  smBuildWrAppDamLSapCfg 
*
*       Desc:  Call handler for DAM LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c
*
*/

#ifdef ANSI
PUBLIC S16 smBuildWrAppDamLSapCfg 
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildWrAppDamLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LwrMngmt    *wrMgt = NULLP;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrAppDamLSapCfg)

   WR_ALLOC(&wrMgt, sizeof(LwrMngmt));
   if(wrMgt == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
  
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      WR_FREE(wrMgt, sizeof(LwrMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_EU_PROC;
   cfg->dstEnt       = ENTEU;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
#ifndef LC_EGTP_THREAD
   cfg->dstSel       = WRSM_WREGSEL;
#else
   cfg->dstSel       = 0;
#endif
   cfg->srcEnt       = ENTSM;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = WR_DATAPP_MEM_REGION;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   if(wrMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   wrMgt->hdr.msgType             = TCFG;
   wrMgt->hdr.msgLen              = 0;
#ifdef TIP_L3_UL2_LL2_SPLIT
   wrMgt->hdr.entId.ent           = ENTEU;
#else
   wrMgt->hdr.entId.ent           = ENTWR;
#endif
   wrMgt->hdr.entId.inst          = SM_INST_ZERO;
   wrMgt->hdr.elmId.elmnt         = STWRDAMSAP;
   wrMgt->hdr.transId             = LWR_TRANSID_DAMCFG;
   wrMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   wrMgt->hdr.response.mem.region = WR_MEM_REGION;
   wrMgt->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst.dstEnt    = ENTEU;
   pst.dstProcId = SM_EU_PROC;
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.region = smCb.init.region;

  RLOG0(L_DEBUG, "UL2 DAM L3 LSap Cfg sent");
   /* Send the request to the LM */
#ifdef TIP_L3_UL2_LL2_SPLIT
   (Void) SmMiDamLwrCfgReq(&pst, wrMgt);
#else
   (Void) SmMiLwrCfgReq(&pst, wrMgt);
#endif
 
   RETVALUE(ROK);
}/* smBuildWrAppDamLSapCfg*/
#endif
/*
 *      FUN:   smBindUnBindWrToSztSap
*
 *      Desc:  Bind and Unbind WR with SCT LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToSztSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToSztSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindWrToSztSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
 
   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_SZ_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRSZTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for S1AP");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for S1AP");
   }
      
    /* Send the control request to the APP */
   (Void)SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ret);
} /* smBindUnBindWrToSztSap */

#ifdef LTE_HO_SUPPORT
/*
 *      FUN:   smBindUnBindWrToCztSap
*
 *      Desc:  Bind and WR with CZT LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToCztSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToCztSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindWrToCztSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_CZ_SUID;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRCZTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for X2AP");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for X2AP");
   }

    /* Send the control request to the APP */
   (Void)SmMiLwrCntrlReq(&pst, cntrl);
 
   RETVALUE(ret);
} /* smBindUnBindWrToCztSap */
#endif

/*
 *      FUN:   smBindUnBindDamToEgtSap
*
 *      Desc:  Bind and Unbind WR with EGT LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindDamToEgtSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindDamToEgtSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindDamToEgtSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_EG_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTEU;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWREGTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEU;
   pst.dstProcId = SM_EU_PROC;
#ifdef TIP_L2_L3_SPLIT
   pst.srcProcId = SM_UL2_SM_PROC;
#else
   pst.srcProcId = SM_SM_PROC;
#endif
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for EGTP");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for EGTP");
   }

    /* Send the control request to the WR*/
   (Void)SmMiDamLwrCntrlReq(&pst, cntrl);
 
   RETVALUE(ret);
} /* smBindUnBindDamToEgtSap */

#ifdef EU_DAT_APP

/*
 *      FUN:   smBindUnBindWrToEgtSap
*
 *      Desc:  Bind and Unbind WR with EGT LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToEgtSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToEgtSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindWrToEgtSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_EG_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWREGTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for EGTP");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for EGTP");
   }

    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, cntrl);
 
   RETVALUE(ret);
} /* smBindUnBindWrToEgtSap */

#endif /* EU_DAT_APP */

/*
 *      FUN:   smBindUnBindWrToNhuSap
*
 *      Desc:  Bind and UnBind WR with NHU LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToNhuSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToNhuSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;

   TRC2(smBindUnBindWrToNhuSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_NH_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRNHUSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for RRC");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for RRC");
   }

    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ret);
} /* smBindUnBindWrToNhuSap */


/*
 *      FUN:   smBindUnBindWrToCtfSap
*
 *      Desc:  Bind and Unbind WR with CTF LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToCtfSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToCtfSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst       pst;
   S16      ret = ROK;

   TRC2(smBindUnBindWrToCtfSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_YS_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRCTFSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for Ctf");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for Ctf");
   }
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, cntrl);
 
   RETVALUE(ret);
} /* smBindUnBindWrToCtfSap */

#ifdef RM_INTF 
/*RRM->FSM */
/*
 *      FUN:   smBindUnBindWrToRmuSap
 *
 *      Desc:  Bind and unbind WR with RMU LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_smm_enbapp_rsys.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToRmuSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToRmuSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindUnBindWrToRmuSap)


   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = action;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_RM_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt        = STWRRMUSAP;
   cntrl.hdr.response.selector   = RMU_SEL_LWLC;
   /* Fill Pst */
   pst.selector  = RMU_SEL_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for RRM");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for RRM");
   }

    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindUnBindWrToRmuSap */


#endif /*RM_INTF*/

/*
 *      FUN:   smBindUnBindWrToNluSap
 *
 *      Desc:  Bind and Unbind WR with NLU LSAP.
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_smm_enbapp_rsys.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToNluSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToNluSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst       pst;
   S16       ret = ROK;

   TRC2(smBindUnBindWrToNluSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction     = 0;
   cntrl->t.cntrl.u.sapId       = WR_NL_SUID;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRNLUSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */

   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region    = smCb.init.region;
   pst.pool      = smCb.init.pool;

#ifdef DEBUGP
  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, "NL Bnd Cntrl Req to wr for SON\n"));
#endif
   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for SON");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for SON");
   }

    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ret);
} /* smBindUnBindWrToNluSap */

#ifdef EU_DAT_APP

/*
 *      FUN:   smBindUnBindWrToPjuSap
*
 *      Desc:  Bind and Unbind WR with PJU LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToPjuSap
(
Inst inst, U8 action
)
#else
PUBLIC S16 smBindUnBindWrToPjuSap(inst,action)
Inst inst;
U8 action;
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst       pst;
   S16      ret = ROK;

   TRC2(smBindUnBindWrToPjuSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = WR_PJ_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
#ifndef TIP_L3_UL2_LL2_SPLIT
   cntrl->hdr.entId.ent           = ENTWR;
#else
   cntrl->hdr.entId.ent           = ENTEU;
#endif
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRPJUSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
#ifndef TIP_L3_UL2_LL2_SPLIT
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
#else
   pst.dstEnt    = ENTEU;
   pst.dstProcId = SM_EU_PROC;
   pst.srcProcId = SM_UL2_SM_PROC;
#endif
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
       RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for PDCP");
   }
   else
   {
       RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for PDCP");
   }

    /* Send the control request to the WR*/
#ifndef TIP_L3_UL2_LL2_SPLIT
   (Void)SmMiLwrCntrlReq(&pst, cntrl);
#else
   (Void)SmMiDamLwrCntrlReq(&pst, cntrl);
#endif
 
   RETVALUE(ret);
} /* smBindUnBindWrToPjuSap */
#endif

#ifdef TIP_L3_UL2_LL2_SPLIT
/*
 *      FUN:  smBindUnBindWrToAppDamSap 
*
 *      Desc:  Bind and unbind WR with DAM LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToAppDamSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToAppDamSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindWrToAppDamSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = tipCellId; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRDAMSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for DAM");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for DAM");
   }
 
    /* Send the control request to the WR*/
   (Void)SmMiLwrCellCntrlReq(&pst, cntrl);

   RETVALUE(ret);
} /* smBindUnBindWrToAppDamSap */
#endif

/*
 *      FUN:   smBindUnBindWrToRgrSap
*
 *      Desc:  Bind and unbind WR with RGR LSAP. 
*
 *      Ret:   Void
*
*       Notes: None
*              
*       File:  wr_smm_enbapp_rsys.c
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindWrToRgrSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindWrToRgrSap(U8 action)
#endif /* ANSI */
{
   LwrMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindWrToRgrSap)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = tipCellId; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRRGRSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   if (action == ABND_ENA)
   {
      RLOG0(L_DEBUG, "Bnd Cntrl Req to wr for SCH");
   }
   else
   {
      RLOG0(L_DEBUG, "UnBnd Cntrl Req to wr for SCH");
   }
 
    /* Send the control request to the WR*/
   (Void)SmMiLwrCellCntrlReq(&pst, cntrl);

   RETVALUE(ret);
} /* smBindUnBindWrToRgrSap */

/*
 *
*       Fun:   smBuildWrErabRelIndCntrl
 *
*       Desc:  Invoked to build and send the eNodeB RAB Release
               Indication message from eNodeB.
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrErabRelIndCntrl 
(
Void
)
#else
PUBLIC S16 smBuildWrErabRelIndCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildWrErabRelIndCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRSNDERABRELIND;
   /* filling proper selector value */
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "Control Req to send ERAB Release Indication");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrGenCntrl */



/*
 *
*       Fun:   smBuildWrGenCntrl
 *
*       Desc:  Invoked to Enable Alarms at APP
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrGenCntrl
(
)
#else
PUBLIC S16 smBuildWrGenCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrGenCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        =  AENA;
   cntrl->t.cntrl.u.sapId       =  0;
   cntrl->t.cntrl.subAction     =  SAUSTA;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRGEN;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Gen Cntrl Req to wr sent");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrGenCntrl */

/* CNM_DEV */
/*
 *
 *      Fun:   smBuildWrSyncCntrl
 *
 *      Desc:  Invoked to intiate Initial Sync
 *
 *      Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_smm_enbapp_rsys.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrSyncCntrl
(
)
#else
PUBLIC S16 smBuildWrSyncCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrSyncCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRINITALSYNC;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "Start Sync Req to WR");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrSyncCntrl */

/*
 *
*       Fun:   smBuildWrCellCntrl
 *
*       Desc:  Invoked to intimate the APP that Binding is DONE
*              and initiate cell control
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrCellCntrl
(
)
#else
PUBLIC S16 smBuildWrCellCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrCellCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRCELLCFG;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   /* Fill the Cell Id */
   cntrl->t.cntrl.u.cellId        = (wrNumCellCntrls + 1);
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Cell Cntrl Req to wr");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrCellCntrl */

/*
 *
*       Fun:   smBuildWrS1InitCntrl
 *
*       Desc:  Invoked to intimate the APP that Binding is DONE.
*              APP should initiate the S1AP association
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrS1InitCntrl
(
)
#else
PUBLIC S16 smBuildWrS1InitCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
  U8  noOfCfg=0; 
   
   TRC2(smBuildWrS1InitCntrl)

#if (defined(WR_PERF_MEAS) || defined(WR_WITHOUT_CNE))
   smBuildWrCellCntrl();
   RETVALUE(ROK);
#endif


   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRS1CONSETUP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   for ( noOfCfg=0; noOfCfg<smCfgCb.noOfCfg; noOfCfg++)
   {
     cntrl->t.cntrl.peerId[noOfCfg] = smCfgCb.mmeCfg[noOfCfg]->mmeId;
     cntrl->t.cntrl.idLst[noOfCfg] = smCfgCb.mmeCfg[noOfCfg]->mmeId;
   }
     cntrl->t.cntrl.numConn = noOfCfg;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for S1 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrInitCntrl */
/*
 *
*       Fun:   wrSmDynInitS1Setup
 *
*       Desc:  Invoked to intimate the APP that Binding is DONE.
*              APP should initiate the S1AP association
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmDynInitS1Setup
(
Void
)
#else
PUBLIC S16 wrSmDynInitS1Setup(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
#ifdef WR_RSYS_OAM
   U32      idx;
#endif
   TRC2(wrSmDynInitS1Setup)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRS1CONSETUP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   cntrl->t.cntrl.numConn = 1;
#ifdef WR_RSYS_OAM
   for(idx = 0; idx < smCfgCb.numMmeAdded; idx++)
   {
     cntrl->t.cntrl.numConn = smCfgCb.numMmeAdded;
     cntrl->t.cntrl.peerId[idx] = smCfgCb.addMmeList[idx];
     cntrl->t.cntrl.idLst[idx] = smCfgCb.addMmeList[idx]; 
   }
#endif/*end of WR_RSYS_OAM*/
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for S1 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrInitCntrl */



#ifdef LTE_HO_SUPPORT
/*
 *
*       Fun:   smBuildWrX2InitCntrl
 *
*       Desc:  Invoked to intimate the APP that Binding is DONE.
*              APP should initiate the X2AP association
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrX2InitCntrl
(
 U8   cellCfgIndx
)
#else
PUBLIC S16 smBuildWrX2InitCntrl(cellCfgIndx)
 U8   cellCfgIndx;
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildWrX2InitCntrl)

   
   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRX2CONSETUP;
   cntrl->hdr.response.selector  = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   wrSmmEnbFillX2InitCntrl(cntrl, cellCfgIndx);
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for X2 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrX2InitCntrl */
#endif /* End of smBuildWrX2InitCntrl */

#ifdef LTE_HO_SUPPORT
/*
 *
*       Fun:   wrSmDynInitX2Setup
 *
*       Desc:  Invoked to intimate the APP that Binding is DONE.
*              APP should initiate the X2AP association
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmDynInitX2Setup
(
Void
)
#else
PUBLIC S16 wrSmDynInitX2Setup(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   TRC2(wrSmDynInitX2Setup)

   
   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRX2CONSETUP;
   cntrl->hdr.response.selector  = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;

   cntrl->t.cntrl.numConn = 1;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for X2 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of wrSmDynInitX2Setup */
#endif

/**
 * @brief This function is used to send enable/disable control request to 
 * the Application layers.
*
 * @details
*
 * Function: smBuildWrLogCntrl
*
 * @param[in] actType
 * @param[in] mask
*
 * @return Void
*/
#ifdef ANSI
PUBLIC S16 smBuildWrLogCntrl
(
 Bool actType,
 U32  mask
)
#else
PUBLIC S16 smBuildWrLogCntrl(actType, mask)
 Bool actType;
 U32  mask;
#endif
{
   LwrMngmt cntrl;
   Pst      pst;
   
   TRC2(smBuildWrLogCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));


   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRGEN;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   if(actType == WR_ON)
   {
      cntrl.t.cntrl.action       =  AENA;
   }
   else
   {
      cntrl.t.cntrl.action       =  ADISIMM;
   }
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   cntrl.hdr.response.mem.region = WR_MEM_REGION;
   cntrl.hdr.response.mem.pool   = WR_POOL;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrLogCntrl */

/*
*
*       Fun:   smBuildWrDbgCntrl
*
*       Desc:  Invoked to enable debug prints
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrDbgCntrl
(
)
#else
PUBLIC S16 smBuildWrDbgCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildWrDbgCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRGEN;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   cntrl->t.cntrl.action        =  AENA;
   cntrl->t.cntrl.subAction     =  SADBG;

   /* wr003.102: Fix for CRId- 115717 */
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = WR_MEM_REGION;
   cntrl->hdr.response.mem.pool   = WR_POOL;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;
   
   RLOG0(L_DEBUG, "RRM Debug Cntrl Req to wr");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrInitCntrl */

/* IPSec Recovery */
/*
 *
 *      Fun:   smBuildWrShutDownCntrl
 *
 *      Desc:  Invoked to shut down the APP
 *
 *      Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrShutDownCntrl
(
)
#else
PUBLIC S16 smBuildWrShutDownCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrShutDownCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        =  ASHUTDOWN;
   /* cntrl->t.cntrl.u.sapId       =  0; */ /* Needed */
   cntrl->t.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRGEN;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "APP Shutdown Cntrl Req to wr sent");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of  smBuildWrShutDownCntrl */
/* IPSec Recovery */
/*
 *
 *      Fun:   smBuildWrUnbindSz
 *
 *      Desc:  Invoked to unbind SZ
 *
 *      Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_smm_enbapp_rsys.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrUnbindSz
(
Void
)
#else
PUBLIC S16 smBuildWrUnbindSz(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrUnbindSz)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        =  AUBND_DIS;
   /* cntrl->t.cntrl.u.sapId       =  0; */ /* Needed */
   cntrl->t.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRSZTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "APP Unbind SZ");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of  smBuildWrUnbindSz */

/* IPSec Recovery */
/*
 *
 *      Fun:   smBuildWrUnbindCz
 *
 *      Desc:  Invoked to unbind CZ
 *
 *      Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_smm_enbapp_rsys.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrUnbindCz
(
Void
)
#else
PUBLIC S16 smBuildWrUnbindCz(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrUnbindCz)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        =  AUBND_DIS;
   /* cntrl->t.cntrl.u.sapId       =  0; */ /* Needed */
   cntrl->t.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRCZTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "APP Unbind to CZ");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of  smBuildWrUnbindCz */

/* IPSec Recovery */
/*
 *
 *      Fun:   smBuildWrUnbindEg
 *
 *      Desc:  Invoked to Unbind the EG
 *
 *      Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  wr_smm_enbapp_rsys.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildWrUnbindEg
(
Void
)
#else
PUBLIC S16 smBuildWrUnbindEg(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrUnbindEg)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        =  AUBND_DIS;
   /* cntrl->t.cntrl.u.sapId       =  0; */ /* Needed */
   cntrl->t.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWREGTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "APP Unbind to EGTP");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of  smBuildWrUnbindEG */

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
*       File:  smwrexms.c
*
*/
#ifdef ANSI
PUBLIC S16 smWrActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smWrActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smWrActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reason);
   smCb.init.region = region;
   smCb.init.pool  = 0;
   RETVALUE(ROK);
}
/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from WR
*
*       Ret:    ROK  - ok
*
*       Notes: None
*
*       File:   wr_sm_wr_exms.c
*
*/
#ifdef ANSI
PUBLIC S16 smEuActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smEuActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC2(smEuActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#if (defined (LCWRMILWR) || defined(LWLCWRMILWR))
      case EVTLWRCFGREQ:             /* Config Request from SM */
         ret = cmUnpkLwrCfgReq(SmMiLwrAddNeighCfgReq, pst, mBuf);
         break;
      case EVTLWRNGHCFGREQ:             /* Config Request from SM */
         ret = cmUnpkLwrCfgReq(SmMiLwrAddNeighCfgReq, pst, mBuf);
         break;
      case EVTLWRCFGCFM:             /* Config confirm */
         ret = cmUnpkLwrCfgCfm(SmMiDamLwrCfgCfm, pst, mBuf);
         break;
      case EVTLWRCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLwrCntrlCfm(SmMiLwrCntrlCfm, pst, mBuf);
         break;
      case EVTLWRSTAIND:
         ret = cmUnpkLwrStaInd(SmMiLwrStaInd, pst,mBuf);
         break;
      case EVTLWRDYNCFGCFM:
         ret = cmUnpkLwrDynCfgCfm(SmMiLwrDynCfgCfm, pst, mBuf); 
         break;
      case EVTLWRADDNGHCELLCFGREQ:
         ret = cmUnpkLwrUpDateNhgCellCfgReq(SmMiLwrUpDateNhgCellCfgReq, pst, mBuf);
         break;
#ifdef WR_RSYS_OAM
      case EVTNGHCELLIND:
         ret=cmUnpkLwrNghCellInd(SmMiLwrHdlNghCellInd,pst,mBuf);
         break;
#endif
#endif
      case EVTWREGTPCFG:
      case EVTWRAPPCFG:
      case EVTWRPDCPCFG:
      case EVTWREGTPSTKBND:
      case EVTWRRRCSTKBND:
      case EVTWRRRMSTKBND:
      case EVTWRENBALRMS:
      case EVTWRENBDEBUGS:
      case EVTWRENBLOG:
      case EVTWRCELLCFG:
      case EVTWRRRMCFG:
      case EVTWRTUCLCFG:
         smWrProcSm(pst->event);
         SPutMsg(mBuf);
         break;

      case EVTWRTUCLSHUT:       
      case EVTWRSCTPSHUT:     
      case EVTWRS1APSHUT:     
      case EVTWREGTPSHUT:      
      case EVTWRAPPSHUT:       
      case EVTWRRRCSHUT:       
      case EVTWRPDCPSHUT:      
      case EVTWRRLCSHUT:       
      case EVTWRMACSHUT:       
      case EVTWRCLSHUT:        
      case EVTWRX2APSHUT:
      case EVTWRRRMSHUT:
      case EVTWRMACSCHSHUT:
      case EVTWRSONSHUT:
      case EVTWRRRMSTKUNBND:
      case EVTWRRRCSTKUNBND:
      case EVTWRX2APSTKUNBND:
      case EVTWREGTPSTKUNBND:
      case EVTWRS1APSTKUNBND:
           smWrShutdownSm(pst->event);
           (Void)SPutMsg(mBuf);        
          break;      
      default:
         SPutMsg(mBuf);
         ret = RFAILED;
         RLOG1(L_ERROR, "Invalid event [%d] received", pst->event);
         break;
   }

   RETVALUE(ret);
   
} /* end of smWrActvTsk */



/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from WR
*
*       Ret:    ROK  - ok
*
*       Notes: None
*
*       File:   wr_sm_wr_exms.c
*
*/
#ifdef ANSI
PUBLIC S16 smWrActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smWrActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC2(smWrActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#if (defined (LCWRMILWR) || defined(LWLCWRMILWR))
      case EVTLWRCFGREQ:             /* Config Request from SM */
         ret = cmUnpkLwrCfgReq(SmMiLwrAddNeighCfgReq, pst, mBuf);
         break;
      case EVTLWRNGHCFGREQ:             /* Config Request from SM */
         ret = cmUnpkLwrCfgReq(SmMiLwrAddNeighCfgReq, pst, mBuf);
         break;
      case EVTLWRCFGCFM:             /* Config confirm */
         ret = cmUnpkLwrCfgCfm(SmMiLwrCfgCfm, pst, mBuf);
         break;
      case EVTLWRCELLCFGCFM:             /* Config confirm */
         ret = cmUnpkCellLwrCfgCfm(SmMiCellLwrCfgCfm, pst, mBuf);
         break;
      case EVTLWRCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLwrCntrlCfm(SmMiLwrCntrlCfm, pst, mBuf);
         break;
      case EVTLWRCELLCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLwrCellCntrlCfm(SmMiLwrCellCntrlCfm, pst, mBuf);
         break;
      case EVTLWRSTAIND:
         ret = cmUnpkLwrStaInd(SmMiLwrStaInd, pst,mBuf);
         break;
      case EVTLWRDYNCFGCFM:
         ret = cmUnpkLwrDynCfgCfm(SmMiLwrDynCfgCfm, pst, mBuf); 
         break;
      case EVTLWRADDNGHCELLCFGREQ:
         ret = cmUnpkLwrUpDateNhgCellCfgReq(SmMiLwrUpDateNhgCellCfgReq, pst, mBuf);
         break;
#ifdef WR_RSYS_OAM
      case EVTNGHCELLIND:
         ret=cmUnpkLwrNghCellInd(SmMiLwrHdlNghCellInd,pst,mBuf);
         break;
#endif
#endif
      case EVTWRSCTPCFG:
      case EVTWRS1APCFG:
      case EVTWRX2APCFG:
      case EVTWREGTPCFG:
      case EVTWRAPPCFG:
      case EVTWRRRCCFG:
      case EVTWRPDCPCFG:
      case EVTWRRLCCFG:
      case EVTWRMACCFG:
      case EVTWRMACSCHDCFG:
      case EVTWRCLCFG:
      case EVTWRS1APSTKBND:
      case EVTWRX2APSTKBND:
      case EVTWREGTPSTKBND:
      case EVTWRRRCSTKBND:
      case EVTWRRRMSTKBND:
      case EVTWRENBALRMS:
      case EVTWRENBDEBUGS:
      case EVTWRENBLOG:
      case EVTWRINITS1SETUP:
      case EVTWRINITX2SETUP:
      case EVTWRCELLCFG:
      case EVTWRRRMCFG:
      case EVTWRTUCLCFG:
#ifdef E_TM
         if ( wrSmDfltBootMode )
         {
           smWrEtmProcSm(pst->event);
         }
         else
#endif /* E_TM */
         smWrProcSm(pst->event);
         (Void)SPutMsg(mBuf);
         break;
#ifdef WR_TEST_CODE
      case EVTWRCLIRECV:
         smWrProcCliMsg();
         SPutMsg(mBuf);
         break;
#endif /* WR_TEST_CODE */

      case EVTOAMCMDRECV:
         SPutMsg(mBuf);
         break;

      case EVTWRTUCLSHUT:       
      case EVTWRSCTPSHUT:     
      case EVTWRS1APSHUT:     
      case EVTWREGTPSHUT:      
      case EVTWRAPPSHUT:       
      case EVTWRRRCSHUT:       
      case EVTWRPDCPSHUT:      
      case EVTWRRLCSHUT:       
      case EVTWRMACSHUT:       
      case EVTWRCLSHUT:        
      case EVTWRX2APSHUT:
      case EVTWRRRMSHUT:
      case EVTWRMACSCHSHUT:
      case EVTWRSONSHUT:
      case EVTWRRRMSTKUNBND:
      case EVTWRRRCSTKUNBND:
      case EVTWRX2APSTKUNBND:
      case EVTWREGTPSTKUNBND:
      case EVTWRS1APSTKUNBND:
           smWrShutdownSm(pst->event);
           (Void)SPutMsg(mBuf);        
          break;      
#ifdef WR_RSYS_OAM
      case EVTSMSTATICCFG:
         ret = cmUnPackSendStaticCfg(wrSmmEnbStaticCfgReq, pst, mBuf);
          break;
      case EVTSMDYNCFG:
         ret = cmUnPackSendDynCfg(smDynCfgReq, pst, mBuf);
          break;
      case EVTSTKSTRSTPREQ:
         ret = smUnPackStartStopStackReq(smStartStopStack, pst, mBuf);
          break;
#endif
      default:
         SPutMsg(mBuf);
         ret = RFAILED;
         RLOG1(L_ERROR, "Invalid event [%d] received", pst->event);
         break;
   }

   RETVALUE(ret);
   
} /* end of smWrActvTsk */

/*

Layer management provides the necessary functions to control and
monitor the condition of each protocol layer.
   
The following functions are provided in this file:

     SmMiLwrCfgReq      Configure Request
     SmMiLwrCntrlReq    Control Request

It is assumed that the following functions are provided in the
stack management body files:

     SmMiLwrStaInd      Status Indication
     SmMiLwrStaCfm      Status Confirm
     SmMiLwrStsCfm      Statistics Confirm
     SmMiLwrTrcInd      Trace Indication

*/

#ifdef LWLCSMMILWR
#define  MAXWRMI  3
#else
#define  MAXWRMI  2
#endif

#ifndef  LCSMMILWR
#ifndef  PTSMMILWR
#define  PTSMMILWR
#endif
#else
#ifndef   WR
#ifndef  PTSMMILWR
#define  PTSMMILWR
#endif
#endif
#endif




/*
the following matrices define the mapping between the primitives
called by the layer management interface of TCP UDP Convergence Layer
and the corresponding primitives in TUCL
   
The parameter MAXWRMI defines the maximum number of layer manager
entities on top of TUCL . There is an array of functions per primitive
invoked by TCP UDP Conbvergence Layer. Every array is MAXWRMI long
(i.e. there are as many functions as the number of service users).
   
The dispatcysng is performed by the configurable variable: selector.
The selector is configured during general configuration.

The selectors are:

   0 - loosely coupled (#define LCSMMILWR) 2 - Lwr (#define WR)
   
*/

/* Configuration request primitive */

PRIVATE LwrCfgReq SmMiLwrCellCfgReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCellCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCfgReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiLwrCellCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCfgReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrCellCfgReq,          /* 2 - light weight loosely coupled   */
#else
   PtMiLwrCfgReq,          /* 2 - light weight loosely coupled , portable */
#endif
};

/* Configuration request primitive */

PRIVATE LwrCfgReq SmMiLwrCfgReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCfgReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiLwrCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCfgReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrCfgReq,          /* 2 - light weight loosely coupled   */
#else
   PtMiLwrCfgReq,          /* 2 - light weight loosely coupled , portable */
#endif
};

PRIVATE LwrCfgReq SmMiDamLwrCfgReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCfgReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiDamLwrCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCfgReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrCfgReq,          /* 2 - light weight loosely coupled   */
#else
   PtMiLwrCfgReq,          /* 2 - light weight loosely coupled , portable */
#endif
};

/* Control request primitive */

PRIVATE LwrCntrlReq SmMiDamLwrCntrlReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCntrlReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiDamLwrCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCntrlReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrCntrlReq,          /* 2 - light weight loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 2 - light weight loosely coupled, portable */
#endif
};
 
/* Control request primitive */

PRIVATE LwrCntrlReq SmMiLwrCntrlReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCntrlReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiLwrCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCntrlReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrCntrlReq,          /* 2 - light weight loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 2 - light weight loosely coupled, portable */
#endif
};

/* Control request primitive */

PRIVATE LwrCntrlReq SmMiLwrCellCntrlReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCellCntrlReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiLwrCellCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCntrlReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrCellCntrlReq,          /* 2 - light weight loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 2 - light weight loosely coupled, portable */
#endif
};
   

PRIVATE LwrCfgCfm SmMiLwrAddNeighCfmMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrAddNeighCfm,       /* 0 - loosely coupled  */
#else
   PtMiLwrAddNeighCfm,       /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiLwrAddNeighCfm,       /* 2 - tightly coupled, layer management  */
#else
   PtMiLwrAddNeighCfm,       /* 2 - tightly coupled, portable  */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrAddNeighCfm,       /* 1 - light weight loosely coupled  */
#else
   PtMiLwrAddNeighCfm,       /* 1 - light weight loosely coupled, portable */
#endif 
}; 
   

PRIVATE LwrLoadInd SmMiLwrLoadIndMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrLoadInd,            /* 0 - loosely coupled  */                       
#else                                                                          
   PtMiLwrLoadInd,            /* 0 - loosely coupled, portable */              
#endif
#ifdef WR                                                                      
   WrMiLwrLoadInd,            /* 2 - tightly coupled, layer management  */     
#else                                                                          
   PtMiLwrLoadInd,            /* 2 - tightly coupled, portable  */             
#endif
#ifdef LWLCSMMILWR                                                             
   cmPkLwrLoadInd,            /* 1 - light weight loosely coupled  */          
#else                                                                          
   PtMiLwrLoadInd,            /* 1 - light weight loosely coupled, portable */ 
#endif                                                                         
}; 

/* Dynamic Configuration request primitive */
PRIVATE LwrDynCfgReq SmMiLwrDynCfgReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrDynCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrDynCfgReq,          /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   WrMiLwrDynCfgReq,          /* 2 - tightly coupled, layer management */
#else
   PtMiLwrDynCfgReq,          /* 2 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrDynCfgReq,          /* 1 - light weight loosely coupled   */
#else
   PtMiLwrDynCfgReq,          /* 1 - light weight loosely coupled , portable */
#endif
}; 
 
/* Nieghbour Cell indication to OAM */
PRIVATE LwrNghCellIndToOam SmMiLwrNghCellInd[MAXWRMI] =
{
#ifdef LCSMMILWR
   NULLP,                            /* 0 - loosely coupled  */
#else
   NULLP,                           /* 0 - loosely coupled, portable */
#endif
#ifdef WR
   NULLP,                           /* 2 - tightly coupled, layer management */
#else
   NULLP,                           /* 2 - tightly coupled, portable */
#endif
#ifdef LWLCSMMILWR
   cmPkLwrNghCellInd,          /* 1 - light weight loosely coupled   */
#else
   NULLP,                           /* 1 - light weight loosely coupled , portable */
#endif
}; 

 
/*
*     layer management interface functions 
*/


#ifdef WR_TEST_CODE
/*
*
*       Fun:   smBuildWrPartRstCntrl
*
*       Desc:  Invoked to build and send the eNodeB RESET (PART)
*              message from eNodeB
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: wr_smm_enbapp.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrPartRstCntrl
(
Void
)
#else
PUBLIC S16 smBuildWrPartRstCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;
   
   TRC2(smBuildWrPartRstCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRSNDPARTS1RST;

   /* ccpu00127155 :filling proper selector value */
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Control Request to send Partial RESET");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrPartRstCntrl */


/*
*
*       Fun:   smBuildWrFullRstCntrl
*
*       Desc:  Invoked to build and send the eNodeB RESET (FULL)
*              message from eNodeB
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: wr_sm_enbapp.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrFullRstCntrl
(
Void
)
#else
PUBLIC S16 smBuildWrFullRstCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   TRC2(smBuildWrFullRstCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRSNDFULLS1RST;

   /* ccpu00127155 :filling proper selector value */
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "Control Request to send Full Reset");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrFullRstCntrl */

/*
*
*       Fun:   smBuildNghRstCntrl
*
*       Desc:  Invoked to build and send the X2-RESET 
*              message from eNodeB
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: wr_sm_enbapp.c 
*
*/

#ifdef ANSI
PUBLIC S16 smBuildNghRstCntrl
(
Void
)
#else
PUBLIC S16 smBuildNghRstCntrl(Void)
#endif
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

   TRC2(smBuildNghRstCntrl)

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRTRIGX2RST;

   /* filling proper selector value */
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Control Request to send X2-Reset");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrFullRstCntrl */

/*
*
 *       Fun:   smBuildAnrPrintCntrl
*
 *       Desc:  Invoked to print the neighbour cell
 *              information in ANR
*
 *       Ret:   ROK
*
*       Notes:  None
*
 *       File: wr_sm_enbapp.c
*
*/

#ifdef ANSI
PUBLIC S16 smBuildAnrPrintCntrl
(
Void
)
#else
PUBLIC S16 smBuildAnrPrintCntrl(Void)
#endif
{
   LwrMngmt *cntrl;
   Pst      pst;

   TRC2(smBuildAnrPrintCntrl)

   SM_SET_ZERO(&pst, sizeof(Pst));
   WR_ALLOC(&cntrl, sizeof(LwrMngmt));

   if(cntrl == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRANRPRINTCELL;
     
   /* :filling proper selector value */
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC; 

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG,"Control Request to print neighbour cell Info in ANR");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildAnrPrintCntrl */
   

   

#ifdef ENB_OVRLOAD

/*
*
*       Fun:   smSndWrCellReCfgSib2
*
*       Desc:  This function for sending eNodeB SIB2 ReConfiguration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellReCfgSib2
(
U8 ovldFlag
)
#else
PUBLIC S16 smSndWrCellReCfgSib2(ovldFlag)
U8 ovldFlag;
#endif
{
   LwrMngmt          *lwrMng = NULLP;
   Pst               pst;
   LwrCellSib2CfgGrp *sib2 =NULLP;
   U8                cfgGrpIndex  = 0;

 
   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng->t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic cell id */
   //lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellIndex = 0;
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib2 params*/
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB2;

   sib2 =&(lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib2CfgGrp);
   sib2->reCfgType = LWR_CELL_SIB2_CFG_BARRING_INFO;
   wrFillTknU8(&(sib2->acBarringInfo.pres), wrSmDfltACBarrInfoPres);

   if (ovldFlag == CRITICAL)
   {
      sib2->acBarringInfo.acBarringForEmergency                = wrSmDfltACBarrEmergency;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOSignal.pres), 
                                                      wrSmDfltDOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = WR_SIB2_ACBRFTR0;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringTime   = WR_SIB2_ACBRTIME128;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOData.pres), 
                                                       wrSmDfltMOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOData.acBarringFactor   = WR_SIB2_ACBRFTR0;
      sib2->acBarringInfo.acBarringForMOData.acBarringTime     = WR_SIB2_ACBRTIME128;
   }
   else if (ovldFlag == MAJOR)
   {
      sib2->acBarringInfo.acBarringForEmergency                = wrSmDfltACBarrNormal;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOSignal.pres), 
                                                      wrSmDfltDOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = WR_SIB2_ACBRFTR90;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringTime   = WR_SIB2_ACBRTIME32;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOData.pres), 
                                                       wrSmDfltMOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOData.acBarringFactor   = WR_SIB2_ACBRFTR70;
      sib2->acBarringInfo.acBarringForMOData.acBarringTime     = WR_SIB2_ACBRTIME32;
   }
   else if (ovldFlag == MINOR)
   {
      sib2->acBarringInfo.acBarringForEmergency                = wrSmDfltACBarrNormal;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOSignal.pres), 
                                                      wrSmDfltDOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = WR_SIB2_ACBRFTR95;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringTime   = WR_SIB2_ACBRTIME16;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOData.pres), 
                                                       wrSmDfltMOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOData.acBarringFactor   = WR_SIB2_ACBRFTR80;
      sib2->acBarringInfo.acBarringForMOData.acBarringTime     = WR_SIB2_ACBRTIME16;
   }
   else
   {
      sib2->acBarringInfo.acBarringForEmergency                = wrSmDfltACBarrNormal;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOSignal.pres), 
                                                      wrSmDfltDOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = WR_SIB2_ACBRFTR50;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringTime   = WR_SIB2_ACBRTIME4;
      wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOData.pres), 
                                                       wrSmDfltMOACBarrInfoPres);
      sib2->acBarringInfo.acBarringForMOData.acBarringFactor   = WR_SIB2_ACBRFTR50;
      sib2->acBarringInfo.acBarringForMOData.acBarringTime     = WR_SIB2_ACBRTIME4;
   }

   if (ovldFlag != NORMAL)
   {
      sib2->acBarringInfo.acBarringForMOData.acBarringAC11 = wrSmDfltacBarringAC11;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC12 = wrSmDfltacBarringAC12;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC13 = wrSmDfltacBarringAC13;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC14 = wrSmDfltacBarringAC14;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC15 = wrSmDfltacBarringAC15;
 
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC11 = 
         wrSmDfltacBarringAC11;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC12 
         =wrSmDfltacBarringAC12;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC13 = 
         wrSmDfltacBarringAC13;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC14 = 
         wrSmDfltacBarringAC14;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC15 = 
         wrSmDfltacBarringAC15; 
   }
   else
{
      sib2->acBarringInfo.acBarringForMOData.acBarringAC11 = ZERO;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC12 = ZERO;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC13 = ZERO;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC14 = ZERO;
      sib2->acBarringInfo.acBarringForMOData.acBarringAC15 = ZERO;

      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC11 = ZERO;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC12 = ZERO;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC13 = ZERO;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC14 = ZERO;
      sib2->acBarringInfo.acBarringForMOSignal.acBarringAC15 = ZERO;
   }
   cfgGrpIndex++; 
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;
 
   /* :filling proper selector value */
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
 
    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);
   
   RETVALUE(ROK);
}                                             
#endif /* ENB_OVRLOAD */
#endif /* WR_TEST_CODE */

 
/* LTE_ADV starts */
/*
*
*       Fun:   smBuildLteAdvConfig
*
*       Desc: construct LwrLteAdvancedConfigTransaction
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_enbapp.c
*/
#ifdef ANSI
PUBLIC S16 smBuildLteAdvConfigTrans
(
 LwrLteAdvancedConfigTrans *lteAdvGroup,
 WrEmmlteAdvFeatureActDeact *configInfo
)
#else
PUBLIC S16 smBuildLteAdvConfigTrans(lteAdvGroup, configInfo)
LwrLteAdvancedConfig *lteAdvGroup;
WrEmmlteAdvFeatureActDeact *configInfo;
#endif
{
   cmMemcpy((U8 *)&lteAdvGroup->lteAdvancedConfig, (U8 *)&smCfgCb.lteAdvancedConfig, sizeof(LwrLteAdvancedConfig)); 
/* LTE_ADV_ABS starts */
   if ((configInfo->feature & RGR_ABS) == RGR_ABS) {
       lteAdvGroup->lteAdvancedConfig.absCfg.status = configInfo->flag;
   }
/* LTE_ADV_ABS ends */

   if ((configInfo->feature & RGR_SFR) == RGR_SFR) {
       lteAdvGroup->lteAdvancedConfig.sfrCfg.status = configInfo->flag;

   }

   if ((configInfo->feature & RGR_DSFR) == RGR_DSFR) {
       lteAdvGroup->lteAdvancedConfig.dsfrCfg.status = configInfo->flag;

   }
   if ((configInfo->feature & RGR_RE) == RGR_RE) {
       lteAdvGroup->lteAdvancedConfig.reCfg.status = configInfo->flag;
   }

   lteAdvGroup->pres = configInfo->feature;
   RETVALUE(ROK);

}

/*
*
*       Fun:   smBuildWrLteAdvancedCellCfg
*
*       Desc:  Involed to modify CellCb with LteAdvanced Features
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: wr_smm_enbapp.c
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrLteAdvancedCellReCfg
(
WrEmmlteAdvFeatureActDeact *configInfo
)
#else
PUBLIC S16 smSndWrLteAdvancedCellReCfg(
WrEmmlteAdvFeatureActDeact *configInfo;
)
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrLteAdvancedConfigTrans *lteAdvGroup =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic cell id */
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = WR_DFLT_CELL_IDX;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;

   /*Filling lteAdvGroup params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CELL_CFG_GRP_LTEA;
   lteAdvGroup =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.lteAdvCfgGrp);
   smBuildLteAdvConfigTrans(lteAdvGroup, configInfo);
   cfgGrpIndex++;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;

   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng.hdr.response.selector   = SM_SELECTOR_TC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);

   RETVALUE(ROK);
} /* end of smSndWrLteAdvancedCellReCfg*/

/* LTE_ADV ends */
/*
*
*       Fun:  smSndLoadInd
*
*       Desc:  Invoked to build and send ENB recfg to modify cpu load
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: wr_sm_enbapp.c 
*
*/
PUBLIC S16 smSndLoadInd
(
U16                          choice,
U16                          value
)
{
   LwrLoadIndInfo loadIndInfo;
   Pst            pst;

   switch (choice)
   {
      case WRSM_ENB_CPU_LOAD:
         {
            loadIndInfo.cpuLoad = (U8) value;
         }
         break;

      default:
         {
            RLOG1(L_ERROR, " Wrong Load type :%d ", choice);
            RETVALUE(RFAILED);
         }
   }

   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrLoadInd(&pst, &loadIndInfo);

   RETVALUE(ROK);
}

/*
*
*       Fun:   wrSmmGetX2apFreePeerId
*
*       Desc:  To get free PeerId from list.
*
*       Ret:   ROK on success, RFAILED on error
*

*       Notes: None
*
*       File:  wr_smm_init_merged.c
*
*/
PUBLIC U16 wrSmmGetX2apFreePeerId()
{
   U8                        idCnt;
  
   for(idCnt = 0;idCnt < WR_SMM_MAX_NBR_ENB; idCnt++)
{
      if(smCfgCb.wrX2apPeerIdLst[idCnt].pres == FALSE)
      {
         smCfgCb.wrX2apPeerIdLst[idCnt].pres = TRUE;
         RETVALUE(smCfgCb.wrX2apPeerIdLst[idCnt].val);
      }
   }
   RETVALUE(WR_SMM_INVALID_PEERID);
}


/***************************************************************************
 *  layer management Confirmation handling
 **************************************************************************/

#ifdef TIP_UPPER_L2
PRIVATE Void wrSmmGetwrWrCfg
(
    LwrMngmt *cfm 
)
{

      switch (cfm->hdr.transId)
      {
         case LWR_TRANSID_GEN: 

            wrWrCfg |= WR_WR_GEN_CFG;
            wrNumPjuSaps=0;
            smBuildWrPjuLSapCfg(WR_PJ_SUID, WR_PJ_SPID);
            break;
         case LWR_TRANSID_PJU:
            wrWrCfg |= WR_WR_PJU_CFG;
            wrNumPjuSaps++;
            if (wrNumPjuSaps < 2)
            {
               smBuildWrPjuLSapCfg(wrNumPjuSaps, WR_PJ_SPID);
            }
            else
            {
               smBuildWrEgtLSapCfg(WR_EG_SUID, WR_EG_SPID);
            }
            break;
         default:
         RLOG1(L_ERROR, "APP Cfg Cfm received for unknown TransId, with "
            "element[%d]",cfm->hdr.elmId.elmnt);
            break;
    }
}
#else
#ifdef TIP_L3
PRIVATE Void wrSmmGetTipwrWrCfg
(
    LwrMngmt *cfm 
)
{
   static U8       mmeIdx = 1;

   switch (cfm->hdr.transId)
   {
      case LWR_TRANSID_GEN: 

         wrWrCfg |= WR_WR_GEN_CFG;
         smBuildWrCtfLSapCfg(WR_YS_SUID, WR_YS_SPID);
         break;      
      case LWR_TRANSID_CTF: 
         wrWrCfg |= WR_WR_CTF_CFG;
         smBuildWrNhuLSapCfg(WR_NH_SUID, WR_NH_SPID);
         break;
      case LWR_TRANSID_NHU:
         wrWrCfg |= WR_WR_NHU_CFG;
         smBuildWrNluLSapCfg(WR_NL_SUID, WR_NL_SPID);
         break;
      case LWR_TRANSID_NLU:
         wrWrCfg |= WR_WR_NLU_SAP_CFG;
         smBuildWrRmuLSapCfg(WR_RM_SUID, WR_RM_SPID);
         break;
      case LWR_TRANSID_RMU:
         wrWrCfg |= WR_WR_RMU_SAP_CFG;
         smBuildWrSztLSapCfg(WR_SZ_SUID, WR_SZ_SPID);
         break;
      case LWR_TRANSID_SZT:
         wrWrCfg |= WR_WR_SZT_CFG;
         smBuildWrCztLSapCfg(WR_CZ_SUID, WR_CZ_SPID);
         break;
      case LWR_TRANSID_CZT:
         wrWrCfg |= WR_WR_CZT_CFG;
         smSndWrEnbCfg();
         break;
      case LWR_TRANSID_ENBCFG:         
         wrWrCfg |= WR_WR_ENBCFG_CFG;
         smSndWrMmeCfg((smCfgCb.mmeCfg[0]));
         break;
      case LWR_TRANSID_MME:            
         if(mmeIdx < smCfgCb.noOfCfg)
         {
            smSndWrMmeCfg((smCfgCb.mmeCfg[mmeIdx]));
            mmeIdx++;
         }
         else
         {
            wrWrCfg |= WR_WR_MME_CFG;
         }
         break;
      default:
         RLOG1(L_ERROR, "APP Cfg Cfm received for unknown TransId, with "
               "element[%d]",cfm->hdr.elmId.elmnt);
         break;
   }
}

#else

PRIVATE Void wrSmmGetwrWrCfg
(
    LwrMngmt *cfm 
)
{
   static U8       mmeIdx = 1;
   static U8       utraCfgIdx = 0;
   static U8       nghCfgCfmIdx = 0;

      switch (cfm->hdr.transId)
      {
         case LWR_TRANSID_GEN: 

            wrWrCfg |= WR_WR_GEN_CFG;
            smBuildWrCtfLSapCfg(WR_YS_SUID, WR_YS_SPID);
            break;      
         case LWR_TRANSID_CTF: 
            wrWrCfg |= WR_WR_CTF_CFG;
            smBuildWrNhuLSapCfg(WR_NH_SUID, WR_NH_SPID);
            break;
         case LWR_TRANSID_NHU:
            wrWrCfg |= WR_WR_NHU_CFG;
            smBuildWrNluLSapCfg(WR_NL_SUID, WR_NL_SPID);
            break;
         case LWR_TRANSID_NLU:
            wrWrCfg |= WR_WR_NLU_SAP_CFG;
#ifndef TIP_L3_UL2_LL2_SPLIT
            smBuildWrPjuLSapCfg(WR_PJ_SUID, WR_PJ_SPID);
            break;
#else
            smBuildWrRmuLSapCfg(WR_RM_SUID, WR_RM_SPID);
            break;
#endif
#ifdef  RM_INTF
         case LWR_TRANSID_PJU:
            wrWrCfg |= WR_WR_PJU_CFG;
            if (1 == wrNumPjuSaps)
            {
            smBuildWrPjuLSapCfg(WR_PJ_SUID + 1, WR_PJ_SPID);
            wrNumPjuSaps++;
            }
            else
            {
            smBuildWrRmuLSapCfg(WR_RM_SUID, WR_RM_SPID);
            }
            break;
         case LWR_TRANSID_RMU:
            wrWrCfg |= WR_WR_RMU_SAP_CFG;
#ifndef TIP_L3_UL2_LL2_SPLIT
            smBuildWrEgtLSapCfg(WR_EG_SUID, WR_EG_SPID);
            break;
#else
            smBuildWrSztLSapCfg(WR_SZ_SUID, WR_SZ_SPID);
            break;
#endif
#else
         case LWR_TRANSID_PJU:
            wrWrCfg |= WR_WR_PJU_CFG;
            if (!wrNumPjuSaps)
            {
               smBuildWrPjuLSapCfg(WR_PJ_SUID + 1, WR_PJ_SPID);
            }
            else
            {
               smBuildWrEgtLSapCfg(WR_EG_SUID, WR_EG_SPID);
            }
            wrNumPjuSaps++;   // Murtuza:Check This->This is removed in the new code
            break;
#endif
#ifndef TIP_L3_UL2_LL2_SPLIT
         case LWR_TRANSID_EGT:
            wrWrCfg |= WR_WR_EGT_CFG;
            smBuildWrSztLSapCfg(WR_SZ_SUID, WR_SZ_SPID);
            break;
#endif
         case LWR_TRANSID_SZT:
            wrWrCfg |= WR_WR_SZT_CFG;
            smBuildWrCztLSapCfg(WR_CZ_SUID, WR_CZ_SPID);
            break;
         case LWR_TRANSID_CZT:
            wrWrCfg |= WR_WR_CZT_CFG;
            smBuildWrRgrLSapCfg(WR_RG_SUID, WR_RG_SPID);
            break;
         case LWR_TRANSID_RGR:            
         {
            cellCfgCfmIdx++;
            if(cellCfgCfmIdx == wrSmDfltNumCells)
            {
            wrWrCfg |= WR_WR_RGR_CFG;
               cellCfgCfmIdx = 0;
            smSndWrEnbCfg();
            }
            else
            {
               smBuildWrRgrLSapCfg(WR_RG_SUID + cellCfgCfmIdx, 
                     WR_RG_SPID + cellCfgCfmIdx);
            }
         }
            break;
         case LWR_TRANSID_ENBCFG:         
         {       
            wrWrCfg |= WR_WR_ENBCFG_CFG;
            cellCfgCfmIdx = 0;
            smSndWrCellCfg(cellCfgCfmIdx);
         }
            break;
         case LWR_TRANSID_CELLCFG:        
         {
            cellCfgCfmIdx++;
            if(cellCfgCfmIdx == wrSmDfltNumCells)
            {
            wrWrCfg |= WR_WR_CELLCFG_CFG;
            mmeIdx = 1;
               cellCfgCfmIdx = 0;
            smSndWrMmeCfg((smCfgCb.mmeCfg[0]));
            }
            else
            {
               smSndWrCellCfg(cellCfgCfmIdx);
            }
         }
            break;
         case LWR_TRANSID_MME:            
            if(mmeIdx < smCfgCb.noOfCfg)
            {
              smSndWrMmeCfg((smCfgCb.mmeCfg[mmeIdx]));
              mmeIdx++;
            }
         else
         {
            wrWrCfg |= WR_WR_MME_CFG;
            smSndWrNhCfg(nghCfgCfmIdx);
         }
         break;
      case LWR_TRANSID_NHCFG:          
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_NHCFG_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNrEutraFreqCfg(nghCfgCfmIdx);
            }
            else
            {
               /*NhCfg for multicell*/
               smSndWrNhCfg(nghCfgCfmIdx);
            }
         }
         break;
      case LWR_TRANSID_NREUTRAN:       
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_NREUTRAN_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNrUtraFddFreqCfg(nghCfgCfmIdx);
            }
            else
            {
               /*NrEutraFreqCfg for multicell*/
               smSndWrNrEutraFreqCfg(nghCfgCfmIdx);
            }
         }
         break;
      case LWR_TRANSID_NRUTRAN:        
         {
            if(nghCfgCfmIdx == wrSmDfltNumCells)
         {
            wrWrCfg |= WR_WR_NRUTRAN_CFG;
            utraCfgIdx = 0;
               nghCfgCfmIdx = 0;
               smSndWrNhCellCfg(nghCfgCfmIdx);
         }
         else
         {
               if(utraCfgIdx % 2)
               {
                  /*NrUtraFddFreqCfg for multicells*/
                  smSndWrNrUtraFddFreqCfg(nghCfgCfmIdx);
                  utraCfgIdx++;
               }
               else
               {
                  /*NrUtraTddFreqCfg for single and multicells*/
                  smSndWrNrUtraTddFreqCfg(nghCfgCfmIdx);
                  utraCfgIdx++;
                  nghCfgCfmIdx++;
               }
            }
         }
         break;
      case LWR_TRANSID_NHCELLCFG:      
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_NHCELL_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNhUtraFddCellCfg(nghCfgCfmIdx);
            }
            else
            {
               smSndWrNhCellCfg(nghCfgCfmIdx);
            }
         }
         break;

      case LWR_TRANSID_NHUTRAN_CELLCFG:
      case LWR_TRANSID_INTER_NHCELLCFG:
         {
            if(nghCfgCfmIdx == wrSmDfltNumCells)
         {
            wrWrCfg |= WR_WR_NHUTRAN_CELL_CFG;
            wrWrCfg |= WR_WR_INTER_NHCELL_CFG;
               utraCfgIdx = 0;
               nghCfgCfmIdx = 0;
               smSndWrCdma1xRTTBandClass(nghCfgCfmIdx);
            }
            else
            {
               if(utraCfgIdx % 2)
               {
                  /*NrUtraFddCellCfg for multicells*/
                  smSndWrNhUtraFddCellCfg(nghCfgCfmIdx);
                  utraCfgIdx++;
               }
               else
               {
                  /*NrUtraTddCellCfg for single and multicells*/
                  smSndWrNhUtraTddCellCfg(nghCfgCfmIdx);
                  utraCfgIdx++;
                  nghCfgCfmIdx++;
               }
            }
         }
         break;
      case LWR_TRANSID_CDMA1XRTT_BAND:       
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_CDMA1XRTT_BAND_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNr1xCdmaFreqCfg(nghCfgCfmIdx);
            }
            else
            {
               smSndWrCdma1xRTTBandClass(nghCfgCfmIdx);
            }
         }
         break;
      case LWR_TRANSID_CDMA1XRTT_FREQ:      
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_CDMA1XRTT_FREQ_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNr1xCdmaCellCfg(nghCfgCfmIdx);
            }
            else
            {
               smSndWrNr1xCdmaFreqCfg(nghCfgCfmIdx);
            }
         }
         break;
      case LWR_TRANSID_CDMA1XRTT_CELL:      
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_CDMA1XRTT_CELL_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNrGeranFreqCfg(nghCfgCfmIdx);
            }
            else
            {
               smSndWrNr1xCdmaCellCfg(nghCfgCfmIdx);
            }
         }
         break;

      case LWR_TRANSID_GERAN_FREQ: 
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_GERAN_FREQ_CFG;
               nghCfgCfmIdx = 0;
               smSndWrNrGeranCellCfg(nghCfgCfmIdx);
            }
            else
            {
               smSndWrNrGeranFreqCfg(nghCfgCfmIdx);
            }
         }
         break;
      case LWR_TRANSID_GERAN_CELL: 
         {
            nghCfgCfmIdx++;
            if(nghCfgCfmIdx == wrSmDfltNumCells)
            {
         wrWrCfg |= WR_WR_GERAN_CELL_CFG;
               nghCfgCfmIdx = 0;
            }
            else
            {
               smSndWrNrGeranCellCfg(nghCfgCfmIdx);
            }
         }
         break;
         default:
         RLOG1(L_ERROR, "APP Cfg Cfm received for unknown TransId, with "
            "element[%d]",cfm->hdr.elmId.elmnt);
            break;
    }
}
#endif
#endif
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
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiDamLwrCfgCfm
(
Pst     *pst,          /* post structure */
LwrMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiDamLwrCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
LwrMngmt *cfm;          /* configuration */
#endif
{
   Pst      wrPst;
   
   TRC2(SmMiDamLwrCfgCfm);

   SM_SET_ZERO(&wrPst, sizeof(Pst));
   if(cfm->cfm.status != LCM_PRIM_OK)
   {
     RLOG_ARG1(L_ERROR, DBG_TRNSID, cfm->hdr.transId,"APP Cfg Cfm received for"
        "the element = %d is NOT OK",cfm->hdr.elmId.elmnt);
     RETVALUE(ROK);
   }

   RLOG_ARG1(L_DEBUG, DBG_TRNSID, cfm->hdr.transId, "APP Cfg Cfm received"
                                "for the element=%d",cfm->hdr.elmId.elmnt);

   cfgCfmRcvd++;
   /* Change smState to APP_CFG_DONE upon receiving CfgCfm from EGT, PJU and APP */
   if( (smCb.smState == WR_SM_STATE_PDCP_DL_CFG_DONE) && cfgCfmRcvd == 3)
	{
		smCb.smState = WR_SM_STATE_APP_CFG_DONE;
		RLOG0(L_ALWAYS, "APP CONFIGURATION SUCCESSFULLY PERFORMED.");
#ifdef WR_RSYS_OAM  
		/*timer stop */
		smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif
#ifdef TIP_L2_L3_SPLIT
		WR_FILL_PST(wrPst, SM_UL2_SM_PROC, SM_EU_PROC, ENTSM, ENTEU,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#else
		WR_FILL_PST(wrPst, SM_SM_PROC, SM_EU_PROC, ENTSM, ENTEU,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#endif

		if(wrSmSelfPstMsg(&wrPst) != ROK)
		{
			RLOG0(L_FATAL, "Self Pst failed after APP Configuration.");
		}
		else
		{
			RLOG0(L_DEBUG, "Self Pst success after APP Configuration.");
		} /* end of else part */

	}
   RETVALUE(ROK);
} /* end of SmMiLwrCfgCfm */

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
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLwrCfgCfm
(
Pst     *pst,          /* post structure */
LwrMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLwrCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
LwrMngmt *cfm;          /* configuration */
#endif
{
   Pst      wrPst;
   
   TRC2(SmMiLwrCfgCfm);

   SM_SET_ZERO(&wrPst, sizeof(Pst));
   if(cfm->cfm.status != LCM_PRIM_OK)
   {
     RLOG_ARG1(L_ERROR, DBG_TRNSID, cfm->hdr.transId,"APP Cfg Cfm received for"
        "the element = %d is NOT OK",cfm->hdr.elmId.elmnt);
#ifdef WR_RSYS_OAM
      /*timer stop :: Raised an alarm */
      smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
      smCb.cfgCb.alarm.severity  = SM_ALARM_SEVERITY_MAJOR;
      smCb.cfgCb.alarm.causeType = SM_ALARM_CAUSE_TYPE_ERR_IND;
      smCb.cfgCb.alarm.causeVal  = SM_ALARM_CAUSE_VAL_INIT_FAIL;
      smStaticCfgFailAlarm();
#endif
     RETVALUE(ROK);
   }
 /* ccpu00127154 :Avoiding condition in case of dynamic update */
   if(wrWrCfg != WR_SM_WR_CONFIGURED)
   {
#ifdef TIP_L3
        wrSmmGetTipwrWrCfg(cfm);
#else
        wrSmmGetwrWrCfg(cfm);
#endif
   } /* end of if statement wrWrCfg != WR_SM_WR_CONFIGURED*/

   RLOG_ARG1(L_DEBUG, DBG_TRNSID, cfm->hdr.transId, "APP Cfg Cfm received"
                                "for the element=%d",cfm->hdr.elmId.elmnt);
#ifdef WR_RSYS_OAM
      if((smCb.smState == WR_SM_STATE_CELL_UP) || (smCb.smState == WR_SM_STATE_OAM_DYN_START))
      {
         if(cfm->t.protoCfg.type == WR_CFG_TYPE_NEIGH_CELL)
         {
            RLOG0(L_DEBUG, "Dynamic Neighbor Cell add completed.");
         }
         RETVALUE(ROK);
      }
#endif
      if(smCb.smState == WR_SM_STATE_CELL_UP)
      {
         if(cfm->t.protoCfg.type == WR_CFG_TYPE_NEIGH_CELL)
         {
            RLOG0(L_INFO, "Dynamic Neighbor Cell add completed.");
         }
         RETVALUE(ROK);
      }

      if (wrWrCfg == WR_SM_WR_CONFIGURED)
      {
         smCb.smState = WR_SM_STATE_APP_CFG_DONE;
         RLOG0(L_ALWAYS, "APP CONFIGURATION SUCCESSFULLY PERFORMED.");
#ifdef WR_RSYS_OAM  
         /*timer stop */
         smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif
         WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRRRCCFG, WR_POOL, SM_SELECTOR_LWLC);

         if(wrSmSelfPstMsg(&wrPst) != ROK)
         {
            RLOG0(L_FATAL, "Self Pst failed after APP Configuration.");
         }
         else
         {
            RLOG0(L_DEBUG, "Self Pst success after APP Configuration.");
         } /* end of else part */

      }

   RETVALUE(ROK);
} /* end of SmMiLwrCfgCfm */

/*
*
*       Fun:   smCfgCellAdd
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smCfgCellAdd
(
U16   cellIdx
)
#else
PUBLIC Void smCfgCellAdd( cellIdx)
U16   cellIdx;
#endif /* ANSI */
{
    LwrMngmt  wrMgt;
    Pst       pst;

    TRC2(smCfgCellAdd);

    SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
    tipCellId = cellIdx;
    /* Fill Header */
    wrMgt.hdr.msgType             = TCFG;
    wrMgt.hdr.msgLen              = 0;
    wrMgt.hdr.entId.ent           = ENTWR;
    wrMgt.hdr.entId.inst          = SM_INST_ZERO;
    wrMgt.hdr.elmId.elmnt         = STWRGEN;
    wrMgt.hdr.elmId.elmntInst1    = 0; 
    wrMgt.hdr.elmId.elmntInst2    = 0; 
    wrMgt.hdr.elmId.elmntInst3    = 0; 
    wrMgt.hdr.seqNmb              = 0;
    wrMgt.hdr.version             = 0;
    wrMgt.hdr.transId             = LWR_TRANSID_GEN;

    wrMgt.hdr.response.prior      = PRIOR0;
    wrMgt.hdr.response.route      = RTESPEC;
    wrMgt.hdr.response.selector   = SM_SELECTOR_LWLC;
    wrMgt.hdr.response.mem.region = WR_MEM_REGION;
    wrMgt.hdr.response.mem.pool   = WR_POOL;
    /* Fill Pst */
    pst.selector  = SM_SELECTOR_LWLC;
    pst.srcEnt    = ENTSM;
    pst.dstEnt    = ENTWR;
    pst.dstProcId = SM_WR_PROC;
    pst.srcProcId = SM_SM_PROC;
    pst.region = smCb.init.region;

    RLOG0(L_DEBUG, "RRM Gen Cfg sent");
    /* Send the request to the LM */
    (Void) SmMiCellLwrCfgCfm(&pst, &wrMgt);

}

PRIVATE Void wrSmmGetTipCellwrWrCfg
(
    LwrMngmt *cfm,
    U16      cellIdx
)
{
   static U8       utraCfgIdx = 0;

      switch (cfm->hdr.transId)
      {
         case LWR_TRANSID_GEN: 
            wrCellWrCfg |= WR_WR_GEN_CFG;
#ifndef TIP_L3 //CHINNA: revisit: currently CTF config doing in begining of state machine
            smBuildWrCtfLSapCfg(WR_YS_SUID, WR_YS_SPID);
            break;      
         case LWR_TRANSID_CTF: 
            wrCellWrCfg |= WR_WR_CTF_CFG;
#endif
            smBuildWrRgrLSapCfg(WR_RG_SUID + cellIdx, 
                  WR_RG_SPID + cellIdx);
            break;
         case LWR_TRANSID_RGR:            
            {
               wrCellWrCfg |= WR_WR_RGR_CFG;
               smSndWrCellCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_CELLCFG:        
            {
               wrCellWrCfg |= WR_WR_CELLCFG_CFG;
#ifdef TIP_L3_UL2_LL2_SPLIT
               smBuildWrDamLSapCfg(WR_DAM_SUID + cellIdx,
                                  WR_DAM_SPID + cellIdx);
            }
            break;
         case LWR_TRANSID_DAMCFG:
            {
               wrCellWrCfg |= WR_WR_DAMCFG_CFG;
#endif
               smSndWrNhCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_NHCFG:          
            {
               wrCellWrCfg |= WR_WR_NHCFG_CFG;
               smSndWrNrEutraFreqCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_NREUTRAN:       
            {

               wrCellWrCfg |= WR_WR_NREUTRAN_CFG;
               smSndWrNrUtraFddFreqCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_NRUTRAN:        
            {
               utraCfgIdx++;
               if(utraCfgIdx == 2) 
               {
                  wrCellWrCfg |= WR_WR_NRUTRAN_CFG;
                  utraCfgIdx = 0;
                  smSndWrNhCellCfg(cellIdx);
               }
               else
               {
                  smSndWrNrUtraTddFreqCfg(cellIdx);
               }
            }
            break;
         case LWR_TRANSID_NHCELLCFG:      
            {
               wrCellWrCfg |= WR_WR_NHCELL_CFG;
               smSndWrNhUtraFddCellCfg(cellIdx);
            }
            break;

         case LWR_TRANSID_NHUTRAN_CELLCFG:
         case LWR_TRANSID_INTER_NHCELLCFG:
            {
               wrCellWrCfg |= WR_WR_INTER_NHCELL_CFG;
               wrCellWrCfg |= WR_WR_NHUTRAN_CELL_CFG;
               smSndWrCdma1xRTTBandClass(cellIdx);
            }
            break;
         case LWR_TRANSID_CDMA1XRTT_BAND:       
            {
               wrCellWrCfg |= WR_WR_CDMA1XRTT_BAND_CFG;
               smSndWrNr1xCdmaFreqCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_CDMA1XRTT_FREQ:      
            {
               wrCellWrCfg |= WR_WR_CDMA1XRTT_FREQ_CFG;
               smSndWrNr1xCdmaCellCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_CDMA1XRTT_CELL:      
            {
               wrCellWrCfg |= WR_WR_CDMA1XRTT_CELL_CFG;
               smSndWrNrGeranFreqCfg(cellIdx);
            }
            break;

         case LWR_TRANSID_GERAN_FREQ: 
            {
               wrCellWrCfg |= WR_WR_GERAN_FREQ_CFG;
               smSndWrNrGeranCellCfg(cellIdx);
            }
            break;
         case LWR_TRANSID_GERAN_CELL: 
            {
               wrCellWrCfg |= WR_WR_GERAN_CELL_CFG;
            }
            break;
         default:
            RLOG1(L_ERROR, "APP Cfg Cfm received for unknown TransId, with "
                  "element[%d]",cfm->hdr.elmId.elmnt);
            break;
      }
}

/*
*
*       Fun:   Cell Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiCellLwrCfgCfm
(
Pst     *pst,          /* post structure */
LwrMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiCellLwrCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
LwrMngmt *cfm;          /* configuration */
#endif
{
   Pst      wrPst;
   TRC2(SmMiCellLwrCfgCfm);

   SM_SET_ZERO(&wrPst, sizeof(Pst));
   if(cfm->cfm.status != LCM_PRIM_OK)
   {
      RLOG_ARG1(L_ERROR, DBG_TRNSID, cfm->hdr.transId,"APP Cfg Cfm received for"
            "the element = %d is NOT OK",cfm->hdr.elmId.elmnt);
      RETVALUE(ROK);
   }
#ifdef TIP_L3_UL2_LL2_SPLIT
   /* ccpu00127154 :Avoiding condition in case of dynamic update */
   if(wrCellWrCfg != WR_SM_WR_CELL_CONFIGURED)
   {
      wrSmmGetTipCellwrWrCfg(cfm, tipCellId);
   } /* end of if statement wrCellWrCfg != WR_SM_WR_CONFIGURED*/

   RLOG_ARG1(L_DEBUG, DBG_TRNSID, cfm->hdr.transId, "APP Cfg Cfm received"
         "for the element=%d",cfm->hdr.elmId.elmnt);
   if (wrCellWrCfg == WR_SM_WR_CELL_CONFIGURED)
#else
   if(wrCellWrCfg != WR_SM_WR_CONFIGURED)
   {
      wrSmmGetTipCellwrWrCfg(cfm, tipCellId);
   } /* end of if statement wrCellWrCfg != WR_SM_WR_CONFIGURED*/

   RLOG_ARG1(L_DEBUG, DBG_TRNSID, cfm->hdr.transId, "APP Cfg Cfm received"
         "for the element=%d",cfm->hdr.elmId.elmnt);
   if (wrCellWrCfg == WR_SM_WR_CONFIGURED)
#endif
   {
      smCb.smState = WR_SM_STATE_APP_CELL_CFG_DONE;
      wrCellWrCfg = 0;
      RLOG0(L_ALWAYS, "APP CELL CONFIGURATION SUCCESSFULLY PERFORMED.");
      
      /* Initiate Bind Request towards RGR Sap  */
      smBindUnBindWrToRgrSap(ABND_ENA);
#if 0
#ifdef WR_RSYS_OAM  
      /*timer stop */
      smStopTmr((PTR)&(smCb),SM_TMR_STATIC_CFG_TMR);
#endif
      WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRRRCCFG, WR_POOL, SM_SELECTOR_LWLC);

      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
         RLOG0(L_FATAL, "Self Pst failed after APP Configuration.");
      }
      else
      {
         RLOG0(L_DEBUG, "Self Pst success after APP Configuration.");
      } /* end of else part */
#endif

   }

   RETVALUE(ROK);
} /* end of SmMiCellLwrCfgCfm */

/*
 *
 *       Fun:    SmMiLwrCellCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_wr_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrCellCntrlCfm
(
Pst         *pst,
LwrMngmt     *cntrl
)
#else
PUBLIC S16 SmMiLwrCellCntrlCfm(pst, cntrl)
Pst         *pst;
LwrMngmt     *cntrl;
#endif /* ANSI */
{
   Pst  wrPst;

   /* wr002.102: Added trace macro */

   TRC2(SmMiLwrCellCntrlCfm)

   SM_SET_ZERO(&wrPst, sizeof(Pst));
/*IPSec*/
   if (cntrl->cfm.status == LCM_PRIM_OK)
   {
      if (smCb.smState == WR_SM_STATE_RRM_SHUTDWN_DONE)
      {
          smCb.smState = WR_SM_STATE_APP_SHUTDWN_DONE;
         RLOG0(L_ALWAYS, "APP SHUTDOWN SUCCESSFULLY PERFORMED. ");
          WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRSONSHUT, WR_POOL, SM_SELECTOR_TC);
          if(wrSmSelfPstMsg(&wrPst) != ROK)
            {
            RLOG0(L_FATAL, "Self Pst failed after APP SHUTDOWN Configuration.");
            }
           else
            {
            RLOG0(L_DEBUG, "Self Pst success after APP SHUTDOWN Configuration.");
            } /* end of else part */
            RETVALUE(ROK);
         }
      }  /* end of LCM_PRIM_OK */


#ifdef WR_RELAY
   if(cntrl->hdr.elmId.elmnt == STWRCTFSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH CL SUCCESSFUL ");
            /* Unbind RRC to RLC DL */
            smBindUnBindNhToKwuSap(WR_SM_KWDL_INST,AUBND);
         }
         RETVALUE(ROK);
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRCTFSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRNHUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH RRC SUCCESSFUL ");
            /* Unbind APP to CL */
            smBindUnBindWrToCtfSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_DEBUG, "Bind of APP with RRC (NHU) is completed");
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRNHUSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRRGRSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH MAC SUCCESSFUL ");
            /* Unbind APP To RRM */
            smBindUnBindWrToRmuSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_DEBUG, "Bind of APP with MAC is completed");
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRRGRSAP */
#ifdef TIP_L3_UL2_LL2_SPLIT
   else if (cntrl->hdr.elmId.elmnt == STWRDAMSAP)
   {
     RLOG0(L_DEBUG, "Bind of APP with DAM is completed");
   }
#endif
   else if(cntrl->hdr.elmId.elmnt == STWRRMUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH RRM SUCCESSFUL ");
            /* Unbind APP To PDCP */
            smBindUnBindWrToPjuSap(WR_SM_PJUL_INST, AUBND);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_DEBUG, "Bind of APP with MAC is completed");
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRRGRSAP */
   else if (cntrl->hdr.elmId.elmnt == STWRGEN)
   {
      RLOG0(L_DEBUG, "Enabling Alarms of App is done.");
      if(cntrl->cfm.status == LCM_PRIM_OK)
      {
         if((smCfgCb.wrDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_WR_DBG_MASK))
         {
            /* Update DbgMsk */
            smCfgCb.smDbgMsk = (smCfgCb.smDbgMsk | WR_SM_WR_DBG_MASK);
            /* Trigger Debug Cntrl */
            wrSmHdlEnbDebugs(EVTWRENBDEBUGS);
         }
      }
      else
      {
         RLOG0(L_ERROR, "SmMiLwrCntrlCfm failed!");
      }

   } /* end of else */
   else if( cntrl->hdr.elmId.elmnt == STWRS1CONSETUP)
   {
      RLOG0(L_DEBUG, "Received Control Confirm for S1 Setup.");
#ifdef WR_RSYS_OAM
      /*Triggering x2setup  after admin state changed*/
      if(WR_SM_STATE_OAM_DYN_START == smCb.smState)
      {
         U8   cellCfgIndx;
         for(cellCfgIndx = 0; cellCfgIndx < wrSmDfltNumCells; cellCfgIndx++)
         {
            smBuildWrX2InitCntrl(cellCfgIndx);
         }
      }
#endif
         /* smBuildWrCellCntrl();  */

   } /* end of else part */
   else if( cntrl->hdr.elmId.elmnt == STWRCELLCFG)
   {
      RLOG0(L_DEBUG, "Received Control Confirm for CELL CFG .");
   } /* end of else part */
#endif  /* WR_RELAY */
#ifdef EU_DAT_APP
   else if(cntrl->hdr.elmId.elmnt == STWRPJUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH PDCP SUCCESSFUL ");
            /* Unbind APP To SON */
            smBindUnBindWrToNluSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWREGTSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRNLUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH SON SUCCESSFUL ");
            /* Unbind APP To RRC */
            smBindUnBindWrToNhuSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWREGTSAP */
   else if(cntrl->hdr.elmId.elmnt == STWREGTSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_X2AP_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP WITH EGTP SUCCESSFUL");
            /* Unbind EGTP with TUCL */
            smBindUnBindEgToHitSap(EG_HI_SPID,AUBND_DIS);
         }
         RETVALUE(ROK);
      }


      RLOG0(L_INFO, "Bind of RRM to EGTP is in progress");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRPJUSAP */
#endif /* end of EU_DAT_APP */
   RETVALUE(ROK);
} /* end of SmMiLwrCntrlCfm() */


/*
 *
 *       Fun:    SmMiLwrCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_wr_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrCntrlCfm
(
Pst         *pst,
LwrMngmt     *cntrl
)
#else
PUBLIC S16 SmMiLwrCntrlCfm(pst, cntrl)
Pst         *pst;
LwrMngmt     *cntrl;
#endif /* ANSI */
{
   Pst  wrPst;

   /* wr002.102: Added trace macro */

   TRC2(SmMiLwrCntrlCfm)

   SM_SET_ZERO(&wrPst, sizeof(Pst));
/*IPSec*/
   if (cntrl->cfm.status == LCM_PRIM_OK)
   {
      if (smCb.smState == WR_SM_STATE_RRM_SHUTDWN_DONE)
      {
          smCb.smState = WR_SM_STATE_APP_SHUTDWN_DONE;
         RLOG0(L_ALWAYS, "APP SHUTDOWN SUCCESSFULLY PERFORMED. ");
          WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRSONSHUT, WR_POOL, SM_SELECTOR_TC);
          if(wrSmSelfPstMsg(&wrPst) != ROK)
            {
            RLOG0(L_FATAL, "Self Pst failed after APP SHUTDOWN Configuration.");
            }
           else
            {
            RLOG0(L_DEBUG, "Self Pst success after APP SHUTDOWN Configuration.");
            } /* end of else part */
            RETVALUE(ROK);
         }
      }  /* end of LCM_PRIM_OK */


#ifdef WR_RELAY
   if(cntrl->hdr.elmId.elmnt == STWRCTFSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH CL SUCCESSFUL ");
            /* Unbind RRC to RLC DL */
            smBindUnBindNhToKwuSap(WR_SM_KWDL_INST,AUBND);
         }
         RETVALUE(ROK);
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRCTFSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRSZTSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_EGTP_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP WITH S1AP SUCCESSFUL");
            /* Unbind S1AP with SCTP */
            smBindUnBindSzToLSap(AUBND);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_INFO, "Bind of APP with S1AP is in progress.");
      }
   }
#ifdef LTE_HO_SUPPORT
   else if(cntrl->hdr.elmId.elmnt == STWRCZTSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRC_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP WITH X2AP SUCCESSFUL");
            /* Unbind X2AP with SCTP*/
            smBindUnBindCzToLSap(AUBND);
         }
         RETVALUE(ROK);
      }
      RLOG0(L_INFO, "Bind of RRM Tsap with X2AP is in progress.");
   }
#endif
   else if(cntrl->hdr.elmId.elmnt == STWRNHUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH RRC SUCCESSFUL ");
            /* Unbind APP to CL */
            smBindUnBindWrToCtfSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_DEBUG, "Bind of APP with RRC (NHU) is completed");
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRNHUSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRRGRSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH MAC SUCCESSFUL ");
            /* Unbind APP To RRM */
            smBindUnBindWrToRmuSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_DEBUG, "Bind of APP with MAC is completed");
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRRGRSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRRMUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH RRM SUCCESSFUL ");
            /* Unbind APP To PDCP */
            smBindUnBindWrToPjuSap(WR_SM_PJUL_INST, AUBND);
         }
         RETVALUE(ROK);
      }
      else
      {
         RLOG0(L_DEBUG, "Bind of APP with MAC is completed");
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRRGRSAP */
   else if (cntrl->hdr.elmId.elmnt == STWRGEN)
   {
      RLOG0(L_DEBUG, "Enabling Alarms of App is done.");
      if(cntrl->cfm.status == LCM_PRIM_OK)
      {
         if((smCfgCb.wrDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_WR_DBG_MASK))
         {
            /* Update DbgMsk */
            smCfgCb.smDbgMsk = (smCfgCb.smDbgMsk | WR_SM_WR_DBG_MASK);
            /* Trigger Debug Cntrl */
            wrSmHdlEnbDebugs(EVTWRENBDEBUGS);
         }
      }
      else
      {
         RLOG0(L_ERROR, "SmMiLwrCntrlCfm failed!");
      }

   } /* end of else */
   else if( cntrl->hdr.elmId.elmnt == STWRS1CONSETUP)
   {
      RLOG0(L_DEBUG, "Received Control Confirm for S1 Setup.");
#ifdef WR_RSYS_OAM
      /*Triggering x2setup  after admin state changed*/
      if(WR_SM_STATE_OAM_DYN_START == smCb.smState)
      {
         U8   cellCfgIndx;
         for(cellCfgIndx = 0; cellCfgIndx < wrSmDfltNumCells; cellCfgIndx++)
         {
            smBuildWrX2InitCntrl(cellCfgIndx);
         }
      }
#endif
         /* smBuildWrCellCntrl();  */

   } /* end of else part */
#ifdef LTE_HO_SUPPORT
   else if( cntrl->hdr.elmId.elmnt == STWRX2CONSETUP)
   {
      RLOG0(L_DEBUG, "Received Control Confirm for X2 Setup.");
   } /* end of else part */
#endif
   else if( cntrl->hdr.elmId.elmnt == STWRCELLCFG)
   {
      RLOG0(L_DEBUG, "Received Control Confirm for CELL CFG .");
   } /* end of else part */
#endif  /* WR_RELAY */
#ifdef EU_DAT_APP
   else if(cntrl->hdr.elmId.elmnt == STWRPJUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH PDCP SUCCESSFUL ");
            /* Unbind APP To SON */
            smBindUnBindWrToNluSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWREGTSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRNLUSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_RRM_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP  WITH SON SUCCESSFUL ");
            /* Unbind APP To RRC */
            smBindUnBindWrToNhuSap(AUBND_DIS);
         }
         RETVALUE(ROK);
      }
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWREGTSAP */
   else if(cntrl->hdr.elmId.elmnt == STWREGTSAP)
   {
      /* Due to unbind */
      if (smCb.smState == WR_SM_STATE_X2AP_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            RLOG0(L_DEBUG,"UNBIND OF APP WITH EGTP SUCCESSFUL");
            /* Unbind EGTP with TUCL */
            smBindUnBindEgToHitSap(EG_HI_SPID,AUBND_DIS);
         }
         RETVALUE(ROK);
      }


      RLOG0(L_INFO, "Bind of RRM to EGTP is in progress");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRPJUSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRDAMSAP)
   {
      RLOG0(L_INFO, "Bind of DAM is in progress ");
   }

#endif /* end of EU_DAT_APP */
   RETVALUE(ROK);
} /* end of SmMiLwrCntrlCfm() */

#ifdef WR_RSYS_OAM
/**
*
*       Fun:  updateMsmNeiCellParams 
*
*       Desc:  This function is used to update the neighbor cell of MSM global structure
*              if the confirmation of dynamic configuration request is success.
*
*       Ret:   None
*
*       Notes:  None
*
*       File:   wr_sm_enbapp_rsys.c
*
*/
PUBLIC Void updateMsmNeiCellParams(MsmEUTRANeighCell *dst, LwrEUTRANeighCell *src)
{
   U8 idx;
   dst->nrIndex = src->nrIndex;
   dst->cid = src->enbId;
   dst->pci = src->pci;
   dst->tac = src->tac;
   dst->numPlmn = src->numPlmn;
   for(idx=0;idx < src->numPlmn; idx++)
   {
       dst->plmnId[idx].numMncDigits = src->plmnId[idx].numMncDigits;
       dst->plmnId[idx].mcc[0] = src->plmnId[idx].mcc[0];
       dst->plmnId[idx].mcc[1] = src->plmnId[idx].mcc[1];
       dst->plmnId[idx].mcc[2] = src->plmnId[idx].mcc[2];
       dst->plmnId[idx].mnc[0] = src->plmnId[idx].mnc[0];
       dst->plmnId[idx].mnc[1] = src->plmnId[idx].mnc[1];
       dst->plmnId[idx].mnc[2] = src->plmnId[idx].mnc[2];
   }  
   dst->earfcnDl = src->earfcnDl;
   dst->earfcnUl = src->earfcnUl;
   dst->cio = src->cio;
   dst->qoffset = src->qoffset;
   dst->RSTxPower = src->refSigPower;
   dst->BlackListed = src->blackListed;
   dst->csgAccessMode = src->csgAccessMode;
   dst->csgId = src->csgId;
   RETVOID;
}
#endif
/**
 *
*       Fun:   Dynamic Configuration Confirm
 *
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
 *
*       Ret:   None
 *
 *       Notes:  None
 *
 *       File:   wr_sm_wr_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrDynCfgCfm
(
Pst         *pst,          /* post structure */
LwrDynMngmt    *dynCfgCfm
)
#else
PUBLIC S16 SmMiLwrDynCfgCfm(pst, dynCfgCfm)
Pst         *pst;          /* post structure */
LwrDynMngmt  *dynCfgCfm;
#endif
   {
#ifdef WR_RSYS_OAM
   smDynTmrEvent = dynCfgCfm->cfgType;

   Header      *dynCfmHdr = &dynCfgCfm->hdr;
   MsmDynCfmInfo dynCfmInfo={0};
   MsmEUTRANeighCell *msmEutraNghCell = NULLP;
   if(dynCfgCfm->cfm.status == LCM_PRIM_OK)
   { 
       smStopTmr((PTR)&(smCb),SM_TMR_DYN_CFG_TMR);
       if (LWR_DYN_EVNT_NEIGH_EUTRA_FREQ_CFG == dynCfgCfm->cfgType)
       {
          U8                   nodeFound = FALSE;
          U8                   idx;
          MsmLteNeighEutraFreq *msmLteNghEutraFreq = NULLP;
           for(idx = 0; idx < lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighFreqCfg.numEutraFreq; idx++)
          {
              msmLteNghEutraFreq = &(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighFreqCfg.t. \
                addNeighFreq[idx].eutranFreq);
              if((msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_ADD) ||
                 (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_MOD) ||
                 (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_DEL))
              {
                 nodeFound = TRUE;
                 break;
              }
          }
          if (TRUE == nodeFound)
          {
             if (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_ADD)
             {
                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS; 
                dynCfmInfo.action = MSM_DYN_ADD;
                dynCfmInfo.u.neighFreqIndx = msmLteNghEutraFreq->freqIndex;

                msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
             }
             else if (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_MOD)
             {
                msmLteNghEutraFreq->dynCfgInd = WR_CFG_INV;
                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_MOD;
                dynCfmInfo.u.neighFreqIndx = msmLteNghEutraFreq->freqIndex;

                msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
             }
             else if (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_DEL)
             {
                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_DEL;
                dynCfmInfo.u.neighFreqIndx = msmLteNghEutraFreq->freqIndex;
                msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
             }
          }
       }
       else if (LWR_DYN_EVNT_NEIGH_EUTRA_CELL_CFG == dynCfgCfm->cfgType)
       {
          U8                   nodeFound = FALSE;
          int                  idx1 = 0;
          for(idx1 = 0; idx1 < lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighCellCfg.numEutraCells; idx1++)
          {
             msmEutraNghCell = &lteeNodeBparams[WR_SM_DFLT_CELL_INDX]. \
                                                  lteNeighCellCfg.t.neighAddCfg[idx1].eutraCell;
              if((msmEutraNghCell->dynCfgInd == MSM_WR_CFG_ADD) ||
                 (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_MOD) ||
                 (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_DEL))
              {
                 nodeFound = TRUE;
                 break;
              }
          }
          if (TRUE == nodeFound)
          {
             if (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_ADD)
             {
                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS; 
                dynCfmInfo.action = MSM_DYN_ADD;
                dynCfmInfo.u.neighCellIndex = msmEutraNghCell->nrIndex;

                msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
             }
             else if (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_MOD)
             {
                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_MOD;
                dynCfmInfo.u.neighCellIndex = msmEutraNghCell->nrIndex;

                msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
             }
             else if (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_DEL)
             {
                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_DEL;
                dynCfmInfo.u.neighCellIndex = msmEutraNghCell->nrIndex;
                msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
             }
          }

       }
       else
       {
         /* Note: This has been added till OAM supports dynamic configuration of
          * MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS once SON updates the same to
          * OAM. As of now, we see that once SON updates, dynamic configuration
          * is not being triigered from OAM. This will be removed once OAM
          * provides the required functionality */
          if(TRUE != smCfgCb.sonTriggeredDynCfg)
          {
             msmDynConfigComplete(MSM_CFM_SUCCESS,MSM_CAUSE_NA,dynCfmInfo);
          }
          else
          {
             RLOG1(L_DEBUG, "Confirm Received for Dynamci Config from SON, value is %d",dynCfgCfm->cfgType); 
             smCfgCb.sonTriggeredDynCfg = FALSE;
          }
       }
       if(LWR_TRANSID_MME_DYN_DELCFG == dynCfmHdr->transId)
       {
         smCfgCb.noMmeDelCfm++;
         if(smCfgCb.noMmeDelCfm == smCfgCb.numMmeDel)
         {
           wrSmDynAddMme();
           smCfgCb.noMmeDelCfm = 0;
           smCfgCb.numMmeDel = 0;
         }
       }
       if(LWR_TRANSID_MME_DYN_ADDCFG == dynCfmHdr->transId)
       {
          smCfgCb.noMmeAddCfm++;
          if(smCfgCb.noMmeAddCfm == smCfgCb.numMmeAdded )
          {
             wrSmDynInitS1Setup();
             smCfgCb.noMmeAddCfm = 0;
             smCfgCb.numMmeAdded = 0;
          }
       }
       RLOG_ARG0(L_DEBUG, DBG_TRNSID,dynCfmHdr->transId,"Dynamic Configuration "
             "Confirm Success Received");
   }
   else
   {
       if (LWR_DYN_EVNT_NEIGH_EUTRA_FREQ_CFG == dynCfgCfm->cfgType)
       {
          U8                   nodeFound = FALSE;
          U8                   idx2;
          MsmLteNeighEutraFreq *msmLteNghEutraFreq = NULLP;
            for(idx2 = 0; idx2 < lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighFreqCfg.numEutraFreq; idx2++)
          {
              msmLteNghEutraFreq = &(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighFreqCfg.t. \
                addNeighFreq[idx2].eutranFreq);
              if((msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_ADD) ||
                 (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_MOD) ||
                 (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_DEL))
              {
                 nodeFound = TRUE;
                 break;
              }
          }
          if (TRUE == nodeFound)
          {
             if (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_ADD)
             {

                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS; 
                dynCfmInfo.action = MSM_DYN_ADD;
                dynCfmInfo.u.neighFreqIndx = msmLteNghEutraFreq->freqIndex;

                msmDynConfigComplete(MSM_CFM_FAILURE,MSM_CAUSE_CFG_FAIL,dynCfmInfo);
             }
             else if (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_MOD)
             {
                msmLteNghEutraFreq->dynCfgInd = WR_CFG_INV;

                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_MOD;
                dynCfmInfo.u.neighFreqIndx = msmLteNghEutraFreq->freqIndex;

                msmDynConfigComplete(MSM_CFM_FAILURE,MSM_CAUSE_CFG_FAIL,dynCfmInfo);
             }
             else if (msmLteNghEutraFreq->dynCfgInd == MSM_WR_CFG_DEL)
             {
                msmLteNghEutraFreq->dynCfgInd = MSM_WR_CFG_INV;

                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGH_FREQ_CFG_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_DEL;
                dynCfmInfo.u.neighFreqIndx = msmLteNghEutraFreq->freqIndex;

                msmDynConfigComplete(MSM_CFM_FAILURE,MSM_CAUSE_CFG_FAIL,dynCfmInfo);
             }
          }
       }
       if (LWR_DYN_EVNT_NEIGH_EUTRA_CELL_CFG == dynCfgCfm->cfgType)
       {
          U8                   nodeFound = FALSE;
          U8                   idx;
          for(idx = 0; idx < lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighCellCfg.numEutraCells; idx++)
          {
              msmEutraNghCell = &lteeNodeBparams[WR_SM_DFLT_CELL_INDX]. \
                                                  lteNeighCellCfg.t.neighAddCfg[idx].eutraCell;

              if((msmEutraNghCell->dynCfgInd == MSM_WR_CFG_ADD) ||
                 (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_MOD) ||
                 (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_DEL))
              {
                 nodeFound = TRUE;
                 break;
              }
          }
          if (TRUE == nodeFound)
          {
             if (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_ADD)
             {

                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS; 
                dynCfmInfo.action = MSM_DYN_ADD;
                dynCfmInfo.u.neighCellIndex = msmEutraNghCell->nrIndex;

                msmDynConfigComplete(MSM_CFM_FAILURE,MSM_CAUSE_CFG_FAIL,dynCfmInfo);
             }
             else if (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_MOD)
             {
                msmEutraNghCell->dynCfgInd = WR_CFG_INV;

                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_MOD;
                dynCfmInfo.u.neighCellIndex = msmEutraNghCell->nrIndex;

                msmDynConfigComplete(MSM_CFM_FAILURE,MSM_CAUSE_CFG_FAIL,dynCfmInfo);
             }
             else if (msmEutraNghCell->dynCfgInd == MSM_WR_CFG_DEL)
             {
                msmEutraNghCell->dynCfgInd = MSM_WR_CFG_INV;

                dynCfmInfo.cfgType = MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS; 
                dynCfmInfo.action = MSM_ACT_DEL;
                dynCfmInfo.u.neighCellIndex = msmEutraNghCell->nrIndex;

                msmDynConfigComplete(MSM_CFM_FAILURE,MSM_CAUSE_CFG_FAIL,dynCfmInfo);
             }
          }
       }
       if(dynCfgCfm->cfm.status == LCM_PRIM_NOK)
       {
         /* Note: This has been added till OAM supports dynamic configuration of
          * MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS once SON updates the same to
          * OAM. As of now, we see that once SON updates, dynamic configuration
          * is not being triigered from OAM. This will be removed once OAM
          * provides the required functionality */
          if(TRUE != smCfgCb.sonTriggeredDynCfg)
          {
          /* Inform the Failure to the Messenger (through MSM), 
       * So that Messenger will resend the configuration */
          /*timer stop :: Raised an alarm*/ 
          smStopTmr((PTR)&(smCb),SM_TMR_DYN_CFG_TMR);
          smCb.cfgCb.alarm.severity  = SM_ALARM_SEVERITY_MAJOR;
          smCb.cfgCb.alarm.causeType = SM_ALARM_CAUSE_TYPE_ERR_IND;
          smCb.cfgCb.alarm.causeVal  = SM_ALARM_CAUSE_VAL_INIT_FAIL;
          smDynCfgFailAlarm(dynCfgCfm->cfgType);
       }
          else
          {
             RLOG0(L_INFO, "Received Negative Cfm for SON trigger dynamic Config");
             smCfgCb.sonTriggeredDynCfg = FALSE;
          }
       }

       RLOG3(L_DEBUG, "Dynamic Configuration Confirm Received for Transaction Id"
                     "= %lu, Status = %d, Reason = %d", dynCfmHdr->transId,
                     dynCfgCfm->cfm.status, dynCfgCfm->cfm.reason);
   }
   WR_FREE(dynCfgCfm, sizeof(LwrDynMngmt));

#endif
   RETVALUE(ROK);
}/* end of SmMiLwrDynCfgCfm */ 

/*
 *
 *       Fun:    SmMiLwrStaInd - status indication
 *
 *       Desc:   Received the Status Indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:  wr_smm_enbapp_rsys.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrStaInd
(
Pst         *pst,
LwrMngmt      *usta
)
#else
PUBLIC S16 SmMiLwrStaInd(pst, usta)
Pst         *pst;
LwrMngmt      *usta;
#endif /* ANSI */
{
   Pst        wrPst;
   LwrUstaDgn *dgn;
#ifndef LTE_ENB_PAL
   //S8         ret = 0;
#endif /* LTE_ENB_PAL*/
#if 1
   U8   idx =0;
#endif /* 0 */
   U32        actualTmrVal;
   Bool       isTmrRunning = FALSE;

   /* wr002.102: Added trace macro */
   TRC2(SmMiLwrStaInd)

   SM_SET_ZERO(&wrPst, sizeof(Pst));

   dgn = &(usta->t.usta.dgn);
#if 0
    if (usta->t.usta.alarm.event == LWR_EVENT_CELL_RECFG_SUCCESS)
    {    
#ifndef LTE_PAL_ENB
       if(smCb.smState == WR_SM_STATE_REBOOT_REQUIRED)
       {
         RLOG0(L_DEBUG, "SENDING STOP REQUEST to CL");

         smBuildWrstopPHYCntrl();
      }
      RETVALUE(ROK);
   }

   if (usta->t.usta.alarm.event == LWR_EVENT_PHY_STOP_SUCCESS)
   {
      RLOG0(L_ALWAYS, "SENDING SHUTDOWN REQUEST to ALL LAYERS ");

      /* DIP changes for common code */
      RLOG0(L_DEBUG, " Re-Starting the Timer thread ");
      ret = SReInitTmr();
      if(ret != ROK)
      {
         RLOG0(L_ERROR, " Failed to Restart the Tmr ");

         RETVALUE(RFAILED);
      }
#endif

      smCb.cellState = FALSE; /* We reached here means cell has been brought down successfully*/
      smCb.smState = WR_SM_STATE_DINIT;
      /*smCb.smState = WR_SM_STATE_RRM_SHUTDWN_DONE;*/
      WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0,EVTWRRRMSTKUNBND, WR_POOL, SM_SELECTOR_LWLC);
      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
         RLOG1(L_ERROR, "Failure at Self Pst. %d", smCb.smState);
      }
   } 
#endif
   if ( usta->t.usta.alarm.event == LWR_EVENT_S1CON_SET_SUCCESS)
   {
      /*Added for avoiding second time cell configuration if mme come up
        after forcefully terminating*/
      if( smCb.cellState == FALSE)
      {
         smBuildWrCellCntrl();
      }
#ifdef BSP_SUPPORT_FOR_CNM 
 /*Comment the above if condition when the BSP support for new design CNM is availaible*/
      if(smCb.syncState == FALSE)
      {
         smBuildWrSyncCntrl();
      }
#endif
   } 
   /* CNM_DEV start */
   if (usta->t.usta.alarm.event == LWR_EVENT_SYNC_NBR_CELL_UNAVAILABLE)
   {
      RLOG0(L_ERROR, "Neighbor not found for Synchronization!!");
      if(smCb.syncState == TRUE)
      {
         /* intermediate sync loss */
         smCb.syncState = FALSE;
         if(RFAILED == wrEmmMmeBrngCellPwrUp())
         {
            RLOG1(L_ERROR, "Failed to power up cell cell ID [%d]",
                  wrEmmCb.cellCb[idx]->cellId);
            RETVALUE(RFAILED);
         }
         /* vrr : need to check */
         /* Setting syncState to True  
          * This is for case when no sync was there during 
          * Init and after that S1 goes down and comes back up again
          * in that case we have to send Power up for Cl
          */
         smCb.syncState = TRUE;
      }
      else
      {
         /* Initial sync failure */
         /* Added for avoiding second time cell configuration */
         if(smCb.cellState == FALSE)
         {
            smCb.smState   = WR_SM_STATE_AWAIT_CELL_UP;
            smBuildWrCellCntrl();
            /*vrr */
            /* Setting syncState to True  
             * This is for case when no sync was there during 
             * Init and after that S1 goes down and comes back up again
             * in that case we have to send Power up for Cl
             */
            smCb.syncState = TRUE;
         }
      }
   }

   if (usta->t.usta.alarm.event == LWR_EVENT_INIT_SYNC_SUCCESS)
   {
      smCb.syncState = TRUE;
 #ifdef TIP_L3
            smCb.smCellState = FALSE;
            if(smCb.numOfCells != 0)
            {
               smWrConfigCell(smCb.cellIdLst[0]);
               smCb.numOfCells--;
            }
            for(idx = 0;idx < smCb.numOfCells;idx++)
            {
               U16    tmpCellId = 0;

               tmpCellId = smCb.cellIdLst[idx + 1];
               smCb.cellIdLst[idx] = tmpCellId;
            }
 #endif

      /* Added for avoiding second time cell configuration */
      if(smCb.cellState == FALSE)
      {
         smCb.smState   = WR_SM_STATE_AWAIT_CELL_UP;
         smBuildWrCellCntrl();
      }
      else
      {
         if(RFAILED == wrEmmMmeBrngCellPwrUp())
         {
            RLOG1(L_FATAL, "Failed to power up cell cell ID [%d]",
                  wrEmmCb.cellCb[idx]->cellId);
            RETVALUE(RFAILED);
         }
 
      }
   }
   /* CNM_DEV end */

   if ((usta->t.usta.alarm.event == LWR_EVENT_CELL_CFG_SUCCESS)
         && smCb.smState == WR_SM_STATE_AWAIT_CELL_UP)
   {
#ifdef TIP_L3
        smSendCellUpIndToRrm(wrNumCellCntrls+1);
        printf("Layer configuration successfully performed for cell Id %d \n", wrNumCellCntrls+1);
        // smBuildWrCellCntrl();
#else

      wrNumCellCntrls++;
      if(wrNumCellCntrls < wrSmDfltNumCells)
      {
         smBuildWrCellCntrl();
      }
      else
      {
         wrNumCellCntrls = 0;
      smCb.smState = WR_SM_STATE_CELL_UP;
      /*Added for avoiding second time cell configuration*/
      smCb.cellState = TRUE;
      RLOG0(L_ALWAYS, "CELL CONFIGURATION SUCCESSFULLY PERFORMED.");
#if 1 
         /* All MMEs are down, no S1 Connection available with eNodeb */
         for(idx = 0; idx < WR_MAX_CELLS; idx++) 
         {
            if ((wrEmmCb.cellCb[idx] != NULLP)) 
            {
               if(wrEmmCellTxPwrReCfg(WR_TX_NORMAL, wrEmmCb.cellCb[idx]->cellId,wrEmmCb.cellCb[idx]->cellId) !=ROK)
               {
                  RLOG1(L_ERROR, "wrEmmCellTxPwrReCfg: returned failure for Cell "
                        "Id %d while setting power normal",wrEmmCb.cellCb[idx]->cellId);
                  RETVALUE(RFAILED);
               }
            }
         }                 
#endif /* 0 */
      RLOG0(L_ALWAYS, "CELL CONFIGURATION SUCCESSFULLY PERFORMED.");
#ifdef CNE_UE_SIM_TEST
      /* eNodeB_Ue_Sim: Send the S1 Setup Now. */
      WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_LWLC);
      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
      }
#else
      /* eNodeB_Ue_Sim: Send the X2 Setup Now. */
      WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRINITX2SETUP, WR_POOL, SM_SELECTOR_LWLC);
      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
         RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
      }

#endif
      }
#endif
   } /* end of if statement */
   /*else if (usta->t.usta.alarm.category == LCM_CATEGORY_INTERFACE)*/
   if (usta->t.usta.alarm.category == LCM_CATEGORY_INTERFACE)
   {
      if (usta->t.usta.alarm.event == LCM_EVENT_BND_OK)
      {
         switch (usta->t.usta.alarm.cause)
         {
            case LWR_CAUSE_SZT_SAP_BOUND:
               {
                  RLOG1(L_DEBUG,  "BIND OF RRM S1AP IS SUCCESSFUL sapId = %d", 
                                  dgn->u.sapId);
                  if (smCb.smState == WR_SM_STATE_ENB_ALRMS_DONE)
                  {
                     smCb.smState = WR_SM_STATE_S1AP_STK_BND_DONE;
                     RLOG0(L_DEBUG, "BIND OF S1AP STACK SUCCESSFUL");
                     /* Perform the bind of APP and SCTP */
#ifndef  TIP_L3_UL2_LL2_SPLIT
                     WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWREGTPSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#else
                     WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRX2APSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#endif
                     if(wrSmSelfPstMsg(&wrPst) != ROK)
                     {
                        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                     }
                  }
                  break;
               }
            case LWR_CAUSE_EGT_SAP_BOUND:
               {
                  RLOG1(L_DEBUG, "BIND OF RRM TO EGTP IS SUCCESSFUL SAPID= %d",
                     dgn->u.sapId);
#ifndef TIP_L3_UL2_LL2_SPLIT

                  if (smCb.smState == WR_SM_STATE_S1AP_STK_BND_DONE)
                  {
                     smCb.smState = WR_SM_STATE_EGTP_STK_BND_DONE;
                     RLOG0(L_DEBUG, "BIND OF EGTP STACK SUCCESSFUL");
#ifdef LTE_HO_SUPPORT
                     /* Perform the bind of APP and SCTP */
                     WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC,ENTSM, ENTWR,0,0, EVTWRX2APSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#else
                     /* Perform the bind of APP and SCTP */
                     WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC,ENTSM, ENTWR,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#endif
                     if(wrSmSelfPstMsg(&wrPst) != ROK)
                     {
                        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                     }
                  }
#else
                     smCb.smState = WR_SM_STATE_X2AP_STK_BND_DONE;
                     WR_FILL_PST(wrPst, SM_UL2_SM_PROC, SM_EU_PROC,ENTSM, ENTEU,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LWLC);
                     if(wrSmSelfPstMsg(&wrPst) != ROK)
                     {
                        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                     }
#endif
                  break;
               }

#ifdef LTE_HO_SUPPORT
            case LWR_CAUSE_CZT_SAP_BOUND:
               {
                  RLOG1(L_DEBUG, "BIND OF RRM TO X2AP IS SUCCESSFUL SAPID= %d",
                     dgn->u.sapId);
#ifndef TIP_L3_UL2_LL2_SPLIT
                  if (smCb.smState == WR_SM_STATE_EGTP_STK_BND_DONE)
#else
                  if (smCb.smState == WR_SM_STATE_S1AP_STK_BND_DONE)
#endif
                  {
                     smCb.smState = WR_SM_STATE_X2AP_STK_BND_DONE;
                     RLOG0(L_DEBUG, "BIND OF X2AP STACK SUCCESSFUL");
                     /* Perform the bind of APP and SCTP */
#ifndef  TIP_L3_UL2_LL2_SPLIT
                     WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC,ENTSM, ENTWR,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#else
                     WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC,ENTSM, ENTWR,0,0, EVTWRRRMSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#endif

                     if(wrSmSelfPstMsg(&wrPst) != ROK)
                     {
                        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                     }
                  }
                  break;  
               }  
#endif
            case LWR_CAUSE_CTF_SAP_BOUND:
               {
                  RLOG1(L_DEBUG, "BIND OF APP CTF IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
                  /* Initiate Bind Request towards NHU Sap  */
                  smBindUnBindWrToNhuSap(ABND_ENA);
                  break;
               }
            case LWR_CAUSE_NHU_SAP_BOUND:
               {
                  RLOG1(L_DEBUG, "BIND OF APP NHU IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
                  smBindUnBindWrToNluSap(ABND_ENA);
                 break;
            }
            case LWR_CAUSE_NLU_SAP_BOUND:
               {
                  RLOG1(L_DEBUG, "BIND OF NLU SAP IS SUCCESSFUL sapId = %d",
                        dgn->u.sapId);
#ifndef TIP_L3_UL2_LL2_SPLIT
                  /* Initiate Bind Request towards Pju Sap  */
                  smBindUnBindWrToPjuSap(WR_SM_PJUL_INST, ABND_ENA);
                  break;
#endif

#ifdef TIP_UPPER_L2
                 break;
#endif 
               }
            case LWR_CAUSE_PJU_SAP_BOUND:
               {
#ifdef TIP_UPPER_L2
                  RLOG1(L_DEBUG, "BIND OF APP PJU IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
                  
                  /* Simulate APP to DAM bind request */
                  /* suId and spId is same as cellIndex, cellIndex is same as
                   * cellId -1 */
                  EuUiDamBndReq(&wrDamCb.wrAppPst, WR_DAM_SUID, WR_DAM_SUID );
#else
#ifdef RM_INTF        /*RRM->FSM */
                  /* Initiate Bind Request towards RMU Sap  */
                  smBindUnBindWrToRmuSap(ABND_ENA);
#else
                  cellCfgCfmIdx = 0;
                  /* Initiate Bind Request towards RGR Sap  */
                  smBindUnBindWrToRgrSap(ABND_ENA);
#endif /*RM_INTF*/
#endif
                  break;
               }
#ifdef RM_INTF /*RRM->FSM */
            case LWR_CAUSE_RMU_SAP_BOUND: 
               {
                  cellCfgCfmIdx = 0;
                  RLOG1(L_DEBUG, "BIND OF APP RMU IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
#ifndef TIP_L3
                  /* Initiate Bind Request towards RGR Sap  */
                  smBindUnBindWrToRgrSap(ABND_ENA);
#else
                  smCb.smState = WR_SM_STATE_RRC_STK_BND_DONE;
                  WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_LWLC);
                  if(wrSmSelfPstMsg(&wrPst) != ROK)
                  {
                     RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                  }
#endif 
                  break;
               }
#endif /*RM_INTF*/
            case LWR_CAUSE_RGR_SAP_BOUND:
               {
                  RLOG1(L_DEBUG, "BIND OF APP RGR IS SUCCESSFUL sapId = %d",
                        dgn->u.sapId);
#ifdef TIP_L3
                  smBindUnBindWrToAppDamSap(ABND_ENA);
                  break;
               }
            case LWR_CAUSE_DAM_SAP_BOUND:
            {
                RLOG1(L_DEBUG, "BIND OF APP DAM IS SUCCESSFUL sapId = %d",
                             dgn->u.sapId);
                  smBindUnBindNhToCkwSap(ABND_ENA);
 #if 0
                  WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_LWLC);

                  if(wrSmSelfPstMsg(&wrPst) != ROK)
                  {
                     RLOG0(L_FATAL, "Self Pst failed during RGR SAP Configuration.");
                  }
                  else
                  {
                     RLOG0(L_DEBUG, "Self Pst success during RGR SAP Configuration.");
                  } /* end of else part */
#endif
#else
                  cellCfgCfmIdx++;
                  if(cellCfgCfmIdx < wrSmDfltNumCells)
                  {
                     smBindUnBindWrToRgrSap(ABND_ENA);
                  }
                  else
                  {
#ifndef TIP_L2_L3_SPLIT
#ifdef LTE_ENB_PERF
                     smCb.smState = WR_SM_STATE_EGTP_STK_BND_DONE;
#endif

#ifdef LTE_HO_SUPPORT
                     if (smCb.smState == WR_SM_STATE_X2AP_STK_BND_DONE)
#else
                        if (smCb.smState == WR_SM_STATE_EGTP_STK_BND_DONE)
#endif
#else
                           if (smCb.smState == WR_SM_STATE_RRM_STK_BND_DONE)
#endif
                           {
                              smCb.smState = WR_SM_STATE_RRC_STK_BND_DONE;
                              RLOG0(L_DEBUG, "BIND OF RRC STACK IS SUCCESSFUL ");
                              /* Perform the bind of APP and SCTP */
#ifndef TIP_L2_L3_SPLIT
#ifdef RM_INTF
                              WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRRRMSTKBND, WR_POOL, SM_SELECTOR_LWLC);
#else
                              WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_LWLC);
#endif
#else
                              WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_LWLC);
#endif
                              if(wrSmSelfPstMsg(&wrPst) != ROK)
                              {
                                 RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                              }
                           }
                  }
#endif
                  break;
               }
#ifdef TIP_UPPER_L2
            case LWR_CAUSE_DAM_SAP_BOUND:
               {
                    RLOG1(L_DEBUG, "BIND OF APP DAM IS SUCCESSFUL sapId = %d",
                             dgn->u.sapId);
                    break;
               }
#endif
            default:
               {
                  RLOG1(L_ERROR, "Invalid alarm. %d", usta->t.usta.alarm.cause);
                  break;
               }
         }
      }
      else if (usta->t.usta.alarm.event == LCM_EVENT_BND_FAIL) 
      {
         RLOG1(L_ERROR, "BIND OF APP lsap id[%d] FAILED ", dgn->u.sapId);
      }
   }
   else if (usta->t.usta.alarm.category == LCM_CATEGORY_LYR_SPECIFIC)
   {
      switch(usta->t.usta.alarm.event)

      {
         case LWR_EVENT_ENB_CFGUPD_SUCCESS:
            RLOG0(L_DEBUG, "ENB Config Update Successfully Complete");
 #ifdef TIP_L3
            wrNumCellCntrls++;
            smBuildWrCellCntrl();
            smCb.smState   = WR_SM_STATE_AWAIT_CELL_UP;
            smCb.smCellState = FALSE;
            if(smCb.numOfCells != 0)
            {
               smWrConfigCell(smCb.cellIdLst[0]);
               smCb.numOfCells--;
            }
            for(idx = 0;idx < smCb.numOfCells;idx++)
            {
               U16    tmpCellId = 0;

               tmpCellId = smCb.cellIdLst[idx + 1];
               smCb.cellIdLst[idx] = tmpCellId;
            }
 #endif
            /* TODO : Send indication to OAM */
            break;
         case LWR_EVENT_ENB_CFGUPD_FAIL:
            RLOG1(L_ERROR, "ENB Config Update Failed cause %d",usta->t.usta.alarm.cause);
            /* TODO : Send indication to OAM */
            break;
      }
   }

   else if (usta->t.usta.alarm.category == LCM_CATEGORY_PROTOCOL)
   {
      if (usta->t.usta.alarm.event == LWR_EVENT_CELL_UNAVAILABLE)
      {

         RLOG0(L_ALWAYS, "All S1 connectons are down, Hence Cell is brought down"
            " and Tx switched OFF. !!!");
#ifdef WR_RSYS_OAM
       /*indicate to OAM cell Tx is switch off */
       MsmOperationalState(FALSE);
#endif
      }
      else if (usta->t.usta.alarm.event == LWR_EVENT_CELL_AVAILABLE)
      {
         smCb.cellState = TRUE;
         smCb.reCfg = FALSE;
         RLOG0(L_ALWAYS, "CELL CONFIGURATION SUCCESSFULLY PERFORMED.");
         rlEnaBleBufferedIO();
         RLOG0(L_INFO, "Enabling Buffered IO");
         /* changes for CR ccpu00147678 */
#ifdef RM_INTF
#ifdef TIP_L3
         smSendCellUpIndToRrm(tipCellId);
#else
         smSendCellUpIndToRrm(1);
#endif
#endif
#ifdef WR_RSYS_OAM
       /*indicate to OAM cell Tx is switch on */
       wrSmConfigComplete();
       MsmOperationalState(TRUE);
       RLOG1(L_DEBUG, "Static Cfg for LOG LEVEL at L3 [%d] ", 
						fapParameters.lteLogLvlCfg.enbL3LogLvl);
       rlSetLogLevel(fapParameters.lteLogLvlCfg.enbL3LogLvl);
#else
      smCb.smState = WR_SM_STATE_CELL_UP;
      smCb.cellState = TRUE;
      RLOG1(L_DEBUG, "Static Cfg for LOG LEVEL at L3 [%d] [without OAM]", wrSmDfltRlLogLvl);
      rlSetLogLevel(wrSmDfltRlLogLvl);
#endif
/* Start the Restriction on number of logs logged per 10ms */
       rlStartLogCountLimit();
       /* Start the ANR cell deletion timer */
       if (lteeNodeBparams[0].lteFapControlParams.anrCellValidAge >= 10)
       {
         actualTmrVal = 10;
       }
       else
       {
          actualTmrVal = lteeNodeBparams[0].lteFapControlParams.anrCellValidAge;
       }

       isTmrRunning = wrIsTmrRunning(&wrEmmCb.cellCb[idx]->nrCb->cellValidAgeTmr,
                                               WR_TMR_ANR_CELL_MAX_AGE_TMR);
       if (isTmrRunning == FALSE)
       {
       wrStartTmr((PTR)wrEmmCb.cellCb[idx], 
          WR_TMR_ANR_CELL_MAX_AGE_TMR,actualTmrVal*60*1000);
       RLOG1(L_INFO, 
       "CELL UP : Started Cell valid age timer with value = %u",
       actualTmrVal);
       }
      }
      if(usta->t.usta.alarm.event == LWR_EVENT_SEND_ALARM)
      {
#ifdef WR_RSYS_OAM
         FapAlarmInd(dgn->u.alarm.alarmId, dgn->u.alarm.severity, dgn->u.alarm.causeType, dgn->u.alarm.causeVal);
#endif
      }
   }
   /*Fix for ccpu00126143: Handling Alram raised when X2 setup Req fails*/
   else if ((usta->t.usta.alarm.cause == LWR_EVENT_CELL_UNAVAILABLE) &&
         (usta->t.usta.alarm.event == LWR_EVENT_ERRIND_FROM_PEER))
   {
      /* Raise a Alram towards OAM when support is available */
      RLOG0(L_ERROR,"X2-Setup Request Failed because of mismatch in enodeb ID");
   }

   RETVALUE(ROK);
} /* end of SmMiLwrStaInd() */

/****************************************************************************
 * layer management interface functions
 ****************************************************************************/

/*
*
*       Fun:   Configuration request
*
*       Desc:  Twrs function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiDamLwrCfgReq
(
Pst *spst,                /* post structure */
LwrMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiDamLwrCfgReq(spst, cfg)
Pst *spst;                /* post structure */   
LwrMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiDamLwrCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiDamLwrCfgReqMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
}
/*
*
*       Fun:   Cell Configuration request
*
*       Desc:  Twrs function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLwrCellCfgReq
(
Pst *spst,                /* post structure */
LwrMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLwrCellCfgReq(spst, cfg)
Pst *spst;                /* post structure */   
LwrMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLwrCellCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrCellCfgReqMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLwrCfgReq */

/*
*
*       Fun:   Configuration request
*
*       Desc:  Twrs function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLwrCfgReq
(
Pst *spst,                /* post structure */
LwrMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLwrCfgReq(spst, cfg)
Pst *spst;                /* post structure */   
LwrMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLwrCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrCfgReqMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLwrCfgReq */

/*
*
*       Fun:   Dynamic Configuration request
*
*       Desc:  This function is used to configure enbapp dynamically
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLwrDynCfgReq
(
Pst    *spst,                /* post structure */
LwrDynMngmt *cfg 
)
#else
PUBLIC S16 SmMiLwrDynCfgReq(spst, cfg)
Pst    *spst;                /* post structure */   
LwrDynMngmt *cfg;
#endif
{
   TRC3(SmMiLwrCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrDynCfgReqMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLwrDynCfgReq */ 

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
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiDamLwrCntrlReq
(
Pst *spst,                 /* post structure */
LwrMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiDamLwrCntrlReq(spst, cntrl)
Pst *spst;                 /* post structure */   
LwrMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiDamLwrCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiDamLwrCntrlReqMt[spst->selector])(spst, cntrl); 
   RETVALUE(ROK);
} /* end of SmMiLwrCntrlReq */

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
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLwrCntrlReq
(
Pst *spst,                 /* post structure */
LwrMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLwrCntrlReq(spst, cntrl)
Pst *spst;                 /* post structure */   
LwrMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLwrCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrCntrlReqMt[spst->selector])(spst, cntrl); 
   RETVALUE(ROK);
} /* end of SmMiLwrCntrlReq */


/*
*
*       Fun:   Cell Control request
*
*       Desc:  This function is used to send control request to 
*              TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLwrCellCntrlReq
(
Pst *spst,                 /* post structure */
LwrMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLwrCellCntrlReq(spst, cntrl)
Pst *spst;                 /* post structure */   
LwrMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLwrCellCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrCellCntrlReqMt[spst->selector])(spst, cntrl); 
   RETVALUE(ROK);
} /* end of SmMiLwrCntrlReq */

/*
 *
 *       Fun:    SmMiLwrLoadInd - Load indication
 *
 *       Desc:   Send the load Indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_enbapp.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrLoadInd
(
Pst         *spst,
LwrLoadIndInfo  *loadIndInfo
)
#else
PUBLIC S16 SmMiLwrLoadInd(spst, loadIndInfo)
Pst         *spst;
LwrLoadIndInfo      *loadIndInfo;
#endif /* ANSI */
{
   
   /* wr002.102: Added trace macro */
   TRC2(SmMiLwrLoadInd)
   
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrLoadIndMt[spst->selector])(spst, loadIndInfo);
   
   RETVALUE(ROK);
} /* end of SmMiLwrLoadInd() */ 


/*
*
*       Fun:   Configuration request
*
*       Desc:  Twrs function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLwrAddNeighCfm
(
Pst *spst,                /* post structure */
LwrMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLwrAddNeighCfm(spst, cfg)
Pst *spst;                /* post structure */   
LwrMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLwrAddNeighCfm)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLwrAddNeighCfmMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLwrAddNeighCfm*/ 


 
/*****************************************************************************
 * Portable function definitions
 *****************************************************************************/

#ifdef PTSMMILWR  

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
*       File:     wr_sm_wr_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLwrAddNeighCfm
(
Pst *spst,                  /* post structure */
LwrMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLwrAddNeighCfm(spst, cfg)
Pst *spst;                  /* post structure */
LwrMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLwrAddNeighCfm) 

  UNUSED(spst);
  UNUSED(cfg);

   RETVALUE(ROK);
} /* end of PtMiLwrAddNeighCfm*/ 

/*
*
*       Fun:   Portable configure Request
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:  wr_smm_enbapp.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLwrLoadInd
(
Pst         *spst,
LwrLoadIndInfo      *loadIndInfo
)
#else
PRIVATE S16 PtMiLwrLoadInd(spst, loadIndInfo)
Pst *spst;                  /* post structure */
LwrLoadIndInfo      *loadIndInfo;
#endif
{
  TRC3(PtMiLwrLoadInd) 

  UNUSED(spst);
  UNUSED(loadIndInfo);
   
   RETVALUE(ROK);
} /* end of PtMiLwrLoadInd */


/*
*
*       Fun:   Portable configure Request- 
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLwrCfgReq
(
Pst *spst,                  /* post structure */
LwrMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLwrCfgReq(spst, cfg)
Pst *spst;                  /* post structure */
LwrMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLwrCfgReq) 

  UNUSED(spst);
  UNUSED(cfg);
   
   RETVALUE(ROK);
} /* end of PtMiLwrCfgReq */



/*
*
*       Fun:   Portable configure Request
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     wr_sm_wr_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLwrDynCfgReq
(
 Pst    *pst,                /* post structure */
 LwrDynMngmt *dynCfg
)
#else
PRIVATE S16 PtMiLwrDynCfgReq(pst, dynCfg)
 Pst    *pst;                /* post structure */
 LwrDynMngmt dynCfg;
#endif
{
  TRC3(PtMiLwrCfgReq) 

  UNUSED(pst);
  UNUSED(dynCfg);
  RETVALUE(ROK);
} /* end of PtMiLwrDynCfgReq */ 

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
*       File:     wr_sm_wr_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLwrCntrlReq
(
Pst *spst,                  /* post structure */
LwrMngmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLwrCntrlReq(spst, cntrl)
Pst *spst;                  /* post structure */
LwrMngmt *cntrl;             /* control */
#endif
   {
  TRC3(PtMiLwrCntrlReq)

  UNUSED(spst);
  UNUSED(cntrl);

 RETVALUE(ROK);
} /* end of PtMiLwrCntrlReq */

#endif /* PTSMMILWR */ 

#ifndef LTE_PAL_ENB
#if 0
/*
*
*       Fun: smBuildWrstopPHYCntrl
*
*       Desc: This function will send the stop request to CL 
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_smm_enbapp_rsys.c
*
*/
#ifdef ANSI
PRIVATE S16 smBuildWrstopPHYCntrl(Void)
#else
PRIVATE S16 smBuildWrstopPHYCntrl(Void)
#endif
{
   YsMngmt  *cntrl = NULLP;
   Pst      pst;

   TRC2()

   SGetSBuf(0, 0, (Data **)&cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(cntrl, sizeof(YsMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl->t.cntrl.action        =  ADISIMM;
   cntrl->t.cntrl.s.cellId =  WRSM_CELLID;
   cntrl->t.cntrl.subAction = SASTOPL1; 
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
   RLOG0(L_DEBUG, "Sending Gen Cntrl Req to ys");

   /* Send the request to the CL */
   SmMiLysCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
}/*smBuildWrstopPHYCntrl*/
#endif
#endif



/*
*
*       Fun:   smBldAndSendNghCellInd
*
*       Desc:  Involed to modify CellCb with LteAdvanced Features
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: wr_smm_enbapp.c
*
*/
#ifdef ANSI
PUBLIC S16 smBldAndSendNghCellInd
(
LwrNghCellInd *nghCellInd
)
#else
PUBLIC S16 smBldAndSendNghCellInd(
LwrNghCellInd *nghCellInd;

)
#endif
{
   Pst               pst = {0};
   
    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTWR;
   pst.dstEnt    = ENTSM;
   pst.dstProcId = SM_SM_PROC;
   pst.srcProcId = SM_WR_PROC;
   pst.region = smCb.init.region;
   pst.pool = smCb.init.pool;

   RETVALUE(SmMiLwrNghInd(&pst,nghCellInd));
}


/*
*
*       Fun:   Neighbour Cell indication
*
*       Desc:  This function is used to send neigbour cell(added/modified/deleted) details to OAM
*
*       Ret:   None
*
*       Notes: None
*              
*       File:     wr_smm_enbapp_rsys.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLwrNghInd
(
Pst    *spst,                
LwrNghCellInd *cfg 
)
#else
PUBLIC S16 SmMiLwrNghInd(spst, cfg)
Pst    *spst;                   
LwrNghCellInd *cfg;
#endif
{
   TRC3(SmMiLwrNghInd)
   if( SmMiLwrNghCellInd[spst->selector] != NULLP)
   {
      (*SmMiLwrNghCellInd[spst->selector])(spst, cfg); 
   }
   else
   {
      RLOG0(L_ERROR,"Failed to sent neighbour cell indication");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}


/*
*
*       Fun:   smSndWrPciUpdateReq
*
*       Desc:  Call handler for sending PCI update to eNB-Application
*
*       Ret:   ROK/RFAILED
*
*       Notes: None
*              
*       File:  wr_sm_enbapp_rsys.c
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrPciUpdateReq
(
NlUpdatePciCfgInd   *pciUpdate
)
#else
PUBLIC S16 smSndWrPciUpdateReq(pciUpdate)
{
NlUpdatePciCfgInd   *pciUpdate;
}
#endif
{
   LwrMngmt          *lwrMng = NULLP;
   Pst               pst;
   LwrCellCfg        *cellCfg = NULLP;
   TRC3 (smSndWrPciUpdateReq);

   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(lwrMng == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   cellCfg = &(lwrMng->t.protoCfg.t.cellCfg);
   cellCfg->action = WR_ACT_MOD;

   cellCfg->t.modCell.cellId = pciUpdate->cellId;
   cellCfg->t.modCell.cellIndex = WR_DFLT_CELL_IDX;
   cellCfg->t.modCell.reCfgType = LWR_CELL_CFG_PHY_PCI_UPDATE;
   cellCfg->t.modCell.physCellId = pciUpdate->pci;

   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_CELLCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);

   RETVALUE(ROK);
}

/*
*
*       Fun:   smSndWrSchdPrbPaUpdateReq
*
*       Desc:  Call handler for sending PRB and PA configuration
*              to eNB-Application
*
*       Ret:   ROK/RFAILED
*
*       Notes: None
*              
*       File:  wr_sm_enbapp_rsys.c
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrSchdPrbPaUpdateReq
(
LnlSonCfg   *sonCfg
)
#else
PUBLIC S16 smSndWrSchdPrbPaUpdateReq(sonCfg)
{
LnlSonCfg   *sonCfg;
}
#endif
{
   LwrMngmt          *lwrMng = NULLP;
   Pst               pst;
   LwrCellCfg        *cellCfg = NULLP;
   LwrAddCellCfg     *modCell = NULLP;
   LwrSonSchdCfg     *schdCfg = NULLP;
   U32               count;
   TRC3 (smSndWrSchdPrbPaUpdateReq);

   WR_ALLOC(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(lwrMng == NULLP)
   {
      RETVALUE(RFAILED);
   }
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   cellCfg = &(lwrMng->t.protoCfg.t.cellCfg);
   cellCfg->action = WR_ACT_MOD;
   modCell = &(cellCfg->t.modCell);
   modCell->cellId = sonCfg->ecgi.cellId;
   modCell->cellIndex = WR_DFLT_CELL_IDX;
   modCell->reCfgType = LWR_CELL_SON_UPDATE;
   modCell->sonCfg.cfgType = LNL_SON_SCHD_CFG;
   schdCfg = &(modCell->sonCfg.u.schdCfg);
   schdCfg->numUeCfg = sonCfg->u.schdCfg.numUeCfg;
   for(count = 0; count < schdCfg->numUeCfg; count ++)
   {
      schdCfg->ueCfg[count].crnti = sonCfg->u.schdCfg.ueCfg[count].crnti;
      schdCfg->ueCfg[count].isCellEdge = sonCfg->u.schdCfg.ueCfg[count].isCellEdge;
   }
   for(count  = 0; count < LNL_MAX_PRB_CNT; count ++)
   {
      schdCfg->paLevelPerPrb[count] = sonCfg->u.schdCfg.paLevelPerPrb[count];
   }
   schdCfg->pa = sonCfg->u.schdCfg.pa;
   schdCfg->paLow = sonCfg->u.schdCfg.paLow;
   schdCfg->paHigh = sonCfg->u.schdCfg.paHigh;
   schdCfg->pb = sonCfg->u.schdCfg.pb;

   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_CELLCFG;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;
   lwrMng->hdr.response.mem.region = WR_MEM_REGION;
   lwrMng->hdr.response.mem.pool   = WR_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCb.init.region;

   (Void) SmMiLwrCfgReq(&pst, lwrMng);

   RETVALUE(ROK);
}

/********************************************************************30**

           End of file:     fc_smm_enbapp_rsys_t2k.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:52:12 2014

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

