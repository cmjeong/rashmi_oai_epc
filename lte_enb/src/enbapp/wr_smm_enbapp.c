
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_enbapp.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=37;

#ifdef RM_INTF
#include "rmu.h" /*RRM->FSM sck changes*/
#endif /*RM_INTF*/
#include "wr.h"
#include "wr_emm.h"
#include "wr_lwr.h"
#include "wr_cmn.h"
#include "wr_smm_smallcell.h"
#include "wr_smm_init.h"
#include "wr_utils.h"
#include "wr_umm.h"

#define WR_SMM_MAX_ACTIVE_UES_PER_CELL TENB_MAX_UE_SUPPORTED

PUBLIC S16 SmMiLwrAddNeighCfm(Pst *spst,LwrMngmt *cfg);
PRIVATE S16 PtMiLwrAddNeighCfm(Pst *spst,LwrMngmt *cfg);
PUBLIC S16 WrMiLwrAddNeighCfm(Pst *pst,LwrMngmt *cfg);
PUBLIC S16 SmMiLwrCntrlCfm(Pst *pst,LwrMngmt *cntrl);
PUBLIC S16 SmMiLwrAddNeighCfgReq(Pst *pst,LwrMngmt *cntrl);
PUBLIC S16 smBuildCdmaHrpdaBandClass( LwrMngmt *lwrMng );
PUBLIC S16 smBuildCdma1xRTTBandClass(LwrMngmt *lwrMng);
PRIVATE S16 smBuildWrstopPHYCntrl( ); /* IPSEC*/

#ifdef RM_INTF
PUBLIC S16 smBuildRmuProtMmeCfg(U16 mmeId, LrmEnbConfiguration *enbCfg, U32 action);
PUBLIC S16 smBuildRmuProtCellCfg(LrmCellConfiguration *cellCfg);
PUBLIC S16 smBuildRmuProtEnbCfg(LrmEnbConfiguration *enbCfg);

/*
*
*       Fun:   smBuildRmuProtCellCfg
*
*       Desc:  This function is used for filling cell configuration in RRM
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI 
PUBLIC S16 smBuildRmuProtCellCfg(LrmCellConfiguration *cellCfg)
#else
PUBLIC S16 smBuildRmuProtCellCfg(cellCfg)
LrmCellConfiguration *cellCfg;
#endif
{
   TRC2(smBuildRmuProtCellCfg);

   cellCfg->enCellAddModDel = LRM_PROTOCFG_ADD_CELL;
   cellCfg->stCellCfgInfo.bCellId         = 1;
   cellCfg->stCellCfgInfo.enCellDlBandWidth    = wrSmDfltCellDlBW[0];
   cellCfg->stCellCfgInfo.enMODataAcbTime      = wrSmDfltacBarringTime;
   cellCfg->stCellCfgInfo.enMOSigAcbTime       = wrSmDfltacBarringTime;
   cellCfg->stCellCfgInfo.usMaxUlBroadbandBw   = 10; /*TODO*/
   cellCfg->stCellCfgInfo.usMaxDlBroadbandBw   = 10; /*TODO*/
   cellCfg->stCellCfgInfo.bNRbCqi              = wrSmDfltPUCCHnRBCQI; /* N2Rb */
   cellCfg->stCellCfgInfo.bNCsAn               = wrSmDfltPUCCHnCSAN; /*N1Cs */
   cellCfg->stCellCfgInfo.bMaxActiveUesServed  = smCfgCb.maxUeSupp;
   cellCfg->stCellCfgInfo.bMaxSigUesServed     = smCfgCb.maxUeSupp + WR_MAX_SR_CQI_NOT_CONFIGURED_UES;  /*TODO*/
   cellCfg->stCellCfgInfo.flagDlfsScheduling   = wrSmDfltDLFSSchdTyp;
   cellCfg->stCellCfgInfo.flagPmiSupport       = wrSmDfltPmiEnabled;
   cellCfg->stCellCfgInfo.bWaitTime            = 3;  /*TODO: Pick from OAM*/
   cellCfg->stCellCfgInfo.flagAcbForEmergency  = wrSmDfltACBarrNormal;
   cellCfg->stCellCfgInfo.bAcBarringForSpClass = 0;  /*TODO*/
	cellCfg->stCellCfgInfo.bRcmAlgoType         = 1;  /* TODO */
	cellCfg->stCellCfgInfo.enSrPrdcty           = wrSmDfltSrPrdcty; /* TODO 2*/
	cellCfg->stCellCfgInfo.enCqiPrdcty          = wrSmDfltCqiPrdcty; /* TODO 5*/
	cellCfg->stCellCfgInfo.usNumSrResPerTti     = wrSmDfltNumSrResPerTti; 
	cellCfg->stCellCfgInfo.usNumCqiResPerTti    = wrSmDfltNumCqiResPerTti; 
	cellCfg->stCellCfgInfo.enUlDlConfig         = wrSmTddSubframeConfig; /*TODO 1*/
	cellCfg->stCellCfgInfo.enSplSfCfg           = wrSmTddSpecialSubframeConfig;
	cellCfg->stCellCfgInfo.usN1Pucch            = wrSmDfltN1PucchAn; /* TODO 7*/
	cellCfg->stCellCfgInfo.enDsrTransMax        = wrSmDfltDsrTransMax; /* TODO 7*/
	cellCfg->stCellCfgInfo.bNumTxAnt            = 2; /* TODO */
   /* Ca Dev Start */
	cellCfg->stCellCfgInfo.usMaxDlUePerTti      = wrSmDfltMaxDlUeNwTxPerTti;
#ifdef LTE_ADV/* Sprint 3*/
	cellCfg->stCellCfgInfo.bIsCaEnabled         = wrSmDfltCaEnabled;
#endif
   /* Ca Dev End */

    /* Fix for CR defeat ccpu00136285 */
    /* Align the Num of antenna enum to RRM cell configuration
     */
    if (SM_LWR_AP_CNT_1 == wrSmDfltNumOfTxAnt)
	 {
       cellCfg->stCellCfgInfo.bNumTxAnt = 1;
    }
    else if(SM_LWR_AP_CNT_2 == wrSmDfltNumOfTxAnt)
    {
       cellCfg->stCellCfgInfo.bNumTxAnt = 2;
    }
    else if(SM_LWR_AP_CNT_4 == wrSmDfltNumOfTxAnt)
    {
       cellCfg->stCellCfgInfo.bNumTxAnt = 4;
    }
    else
    {
       WR_DBGP(WR_ERROR,(WR_PRNT_BUF,
      " The Default value of wrSmDfltNumOfTxAnt %d is wrong\n",
      wrSmDfltNumOfTxAnt));
    }
    /*Cases WITHOUT RSYS_OAM*/
   /*DRX QCI*/
    cellCfg->stCellCfgInfo.stRmCellDrxCfg.isDRXQCIEnabled = wrSmDfltisDrxQCIEnabled; 
    /*Removed DRX Flag */
    cellCfg->stCellCfgInfo.stRmCellDrxCfg.bIsDrxEnabled        = wrSmDfltIsDrxEnabled; 
    cellCfg->stCellCfgInfo.stRmCellDrxCfg.usDrxInactvTmr       = wrSmDfltDrxInactvTmr; 
    cellCfg->stCellCfgInfo.stRmCellDrxCfg.bDrxRetxTmr          = wrSmDfltDrxReTxTmr; 
    cellCfg->stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleGbr    = wrSmDfltDrxLongCycleGbr; 
    cellCfg->stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleNonGbr = wrSmDfltDrxLongCycleNonGbr; 
    /*Cases WITHOUT RSYS_OAM*/

   /* SPS changes starts */
   /* wrSmDfltIsSpsEnabled is initialised as SPS disabled */
   cellCfg->stCellCfgInfo.stSpsCellCfg.bIsSpsEnabled = wrSmDfltIsSpsEnabled;
   if (wrSmDfltIsSpsEnabled == TRUE)
   {
      cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxDlSpsUePerTti = wrSmDfltMaxDlSpsUePerTti;
      cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxUlSpsUePerTti = wrSmDfltMaxUlSpsUePerTti;
      cellCfg->stCellCfgInfo.stSpsCellCfg.usSpsDlBwInRbs     = wrSmDfltSpsDlBandwidth;
   }
   /* SPS changes ends */

    RETVALUE(ROK);
}

/* IPSec Recovery */
/*
*
*       Fun:   smBuildRmuProtCellCfg
*
*       Desc:  This function is used for filling cell configuration in RRM
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI 
PUBLIC S16 smBuildRmuProtCellDel(LrmCellConfiguration *cellCfg)
#else
PUBLIC S16 smBuildRmuProtCellDel(cellCfg)
LrmCellConfiguration *cellCfg;
#endif
{
    TRC2(smBuildRmuProtCellDel);

    cellCfg->enCellAddModDel = LRM_PROTOCFG_DEL_CELL;
    cellCfg->stCellCfgInfo.bCellId         = 1;
    RETVALUE(ROK);
}

/* IPSec Recovery */

/*
*
*       Fun:   smBuildRmuProtEnbCfg
*
*       Desc:  This function is used for filling Enb configuration in RRM
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI 
PUBLIC S16 smBuildRmuProtEnbCfg(LrmEnbConfiguration *enbCfg)
#else
PUBLIC S16 smBuildRmuProtEnbCfg(enbCfg)
LrmEnbConfiguration *enbCfg;
#endif
{
   TRC2(smBuildRmuProtEnbCfg);

   enbCfg->bCfgType = RRM_ENB_CFG_SYS_CFG;
   enbCfg->u.bMaxNumCells = 1;

   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildRmuProtMmeCfg
*
*       Desc:  This function is used for filling Mme configuration in RRM
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI 
PUBLIC S16 smBuildRmuProtMmeCfg(U16 mmeId, LrmEnbConfiguration *enbCfg, U32 action)
#else
PUBLIC S16 smBuildRmuProtMmeCfg(mmeId, enbCfg, action)
U16                 mmeId;
LrmEnbConfiguration *enbCfg;
U32                   action;
#endif
{
   TRC2(smBuildRmuProtMmeCfg);

   enbCfg->bCfgType = RRM_ENB_CFG_MME_CFG;
   enbCfg->u.stMmeCfg.enMmeAddModOrDel = action;
   enbCfg->u.stMmeCfg.usMmeId        = mmeId;

   RETVALUE(ROK);
}

#endif /*RM_INTF*/
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
   if (SRegTTsk((Ent)ENTWR, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
                 wrActvInit, (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }
   /* Register RRC APP TAPA Task */
   if (SRegTTsk((Ent)ENTNX, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
                 NULLP, (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

    /* Register Data APP TAPA Task */
   if (SRegTTsk((Ent)ENTEU, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
                 NULLP , (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

    /* Register Data APP TAPA Task */
   if (SRegTTsk((Ent)ENTPX, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
                 NULLP , (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach EGTP AND CL USER TAPA Task */
   /* Mapping of VE to WR as EGTP and CL still send to VE */
   if (SRegTTsk((Ent)ENTVE, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
                 wrActvInit, (ActvTsk)wrActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach ENB TAPA Task */
   if (SAttachTTsk((Ent)ENTWR, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach RRC APP TAPA Task */
   if (SAttachTTsk((Ent)ENTNX, (Inst)0, sysTskId)!= ROK) 
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

   RETVALUE(ROK);
} /* end of smEuInit */

#endif /* EU_DAT_APP */

/*
*
*       Fun:   smBuildCdmaHrpdaBandClass
*
*       Desc:  This function for filling the Cell Band Class Configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildCdmaHrpdaBandClass
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildCdmaHrpdaBandClass(*lwrMng)
LwrMngmt *lwrMng
#endif
{
   LwrNeighBandClassCfg *bandClassCfg =NULLP;
   U32 idx = 0;  
   
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_BAND_CLASS;
   lwrMng->t.protoCfg.t.cdmaBandClassCfg.action = WR_ACT_ADD;

   lwrMng->t.protoCfg.t.cdmaBandClassCfg.cellId = 1;
   lwrMng->t.protoCfg.t.cdmaBandClassCfg.numBandClass = 1;
   
   for(idx=0;idx<1;idx++) 
   {
     bandClassCfg =lwrMng->t.protoCfg.t.cdmaBandClassCfg.t.bcAddCfg;
     bandClassCfg->cdmaType = wrSmDfltHrpda;
     bandClassCfg->t.bandClassHRPD.reCfgType = wrSmDfltBandClsReCfgType;
     bandClassCfg->t.bandClassHRPD.status = wrSmDfltBandClsStatus;
     bandClassCfg->t.bandClassHRPD.bandClass =wrSmDfltBandClass;
     bandClassCfg->t.bandClassHRPD.cellReselectPrior =wrSmDfltBandClsCellReSelPri;
     bandClassCfg->t.bandClassHRPD.threshXHigh = wrSmDfltBandClassThresHigh;
     bandClassCfg->t.bandClassHRPD.threshXLow = wrSmDfltBandClassThresLow;
     bandClassCfg++;
   }
   
   RETVALUE(ROK);
}



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

#ifdef ANSI
PRIVATE S16 smSndWrCdmaHrpdBandClass
(
void
)
#else
PRIVATE S16 smSndWrCdmaHrpdBandClass
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildCdmaHrpdaBandClass(&lwrMng);
   
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildWrEnbCfg
*
*       Desc:  This function for filling eNodeB Configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
PUBLIC S16 smBuildWrEnbCfg
(
LwrMngmt *lwrMng
)
{
   LwrENodeBCfg *enbCfg = NULLP;
   TknStrOSXL   *enbName;
   
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_ENB;
   lwrMng->t.protoCfg.t.eNbCfg.action = WR_ACT_ADD;
   
   enbCfg =&(lwrMng->t.protoCfg.t.eNbCfg.t.eNodeBCfg);

   /* add enb name */
   enbName = &(enbCfg->protoCfg.enbName);
   /* kworks fix */
   enbName->len = (U16)strlen((S8 *)wrSmDfltHenbName);
   WR_ALLOC(&(enbName->val), sizeof(enbName->val));
   if(enbName->val == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if(NULLP == enbName->val)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   cmMemcpy(enbName->val, wrSmDfltHenbName, enbName->len);

   enbCfg->maxNumOfUe = wrSmDfltMaxNoUE;
   enbCfg->enbCfgTransTmrVal = wrSmDfltEnbCfgTransTmrVal;
   enbCfg->pwsEtwsCmas = wrSmPwsEtwsCmas; /* Enable ETWS or CMAS or disable both*/
   if(wrSmDfltEnbType == WR_ENODEB_TYPE_HOME)
   {
      /* in home enb case eNodeB Id and cellId are same */
      enbCfg->protoCfg.enbId = wrSmDfltCellId;
   }
   else
   {
      /* in macro enb case eNodeB Id is MSB 28 bits of cellId */
      enbCfg->protoCfg.enbId = wrSmDfltCellId >> 8;
   }
   enbCfg->protoCfg.enbType =wrSmDfltEnbType;
   wrCpyCmTptAddr(&enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX], 
      &wrSmDfltEnbIpAddr[WR_IPV4_IDX]);
   wrCpyCmTptAddr(&enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX], 
      &wrSmDfltEnbIpAddr[WR_IPV6_IDX]);
   if(enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].type == CM_TPTADDR_IPV4) 
   {
      enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].u.ipv4TptAddr.port =  wrSmDfltEnbPort;
   }
   if(enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].type == CM_TPTADDR_IPV6) 
   {
      enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].u.ipv6TptAddr.port =  wrSmDfltEnbPort;
   }
  
   enbCfg->protoCfg.numPlmns =wrSmDfltEnbNoPlmn;
   
   enbCfg->protoCfg.plmns[0].numMncDigits  =wrSmDfltNumMncDigits;
   enbCfg->protoCfg.plmns[0].mcc[0] =wrSmDfltPlmn1Mcc0;
   enbCfg->protoCfg.plmns[0].mcc[1] =wrSmDfltPlmn1Mcc1;
   enbCfg->protoCfg.plmns[0].mcc[2] =wrSmDfltPlmn1Mcc2;

   enbCfg->protoCfg.plmns[0].mnc[0]=wrSmDfltPlmn1Mnc0;
   enbCfg->protoCfg.plmns[0].mnc[1]=wrSmDfltPlmn1Mnc1;
   enbCfg->protoCfg.plmns[0].mnc[2]=wrSmDfltPlmn1Mnc2;


#ifdef MME_LDBAL
   enbCfg->numOfMmePriGrps                 = wrSmDfltNumOfPriorityGrps;
   enbCfg->mmeLdBalCfg[0].mmeGroupId       = wrSmDfltMmeGrpID1;
   enbCfg->mmeLdBalCfg[0].mmeGrpPrior      = wrSmDfltMmeGrpIDPriority2;
   enbCfg->mmeLdBalCfg[1].mmeGroupId       = wrSmDfltMmeGrpID2;
   enbCfg->mmeLdBalCfg[1].mmeGrpPrior      = wrSmDfltMmeGrpIDPriority1;
   enbCfg->mmeLdBalCfg[2].mmeGroupId       = wrSmDfltMmeGrpID3;
   enbCfg->mmeLdBalCfg[2].mmeGrpPrior      = wrSmDfltMmeGrpIDPriority3;
   enbCfg->mmeLdBalCfg[3].mmeGroupId       = wrSmDfltMmeGrpID4; 
   enbCfg->mmeLdBalCfg[3].mmeGrpPrior      = wrSmDfltMmeGrpIDPriority4;
#endif
    enbCfg->macMainCfg.timeAlignmentTimerDedicated = wrSmDfltTaTmrDed; 
    enbCfg->macMainCfg.ulSchCfg.maxHARQ_Tx = wrSmDfltMaxUlHqTx; 
    enbCfg->macMainCfg.ulSchCfg.periodicBSR_Timer =
                                 wrSmDfltMacCfgPeriodicBSRTimer;
    enbCfg->macMainCfg.ulSchCfg.retxBSR_Timer = wrSmDfltMacCfgRetxBSRTimer;
    enbCfg->macMainCfg.ulSchCfg.ttiBundling = wrSmDfltMacCfgTtiBundling;
 
    enbCfg->cqiRptCfg.aperCqiEnbld = FALSE;
    enbCfg->cqiRptCfg.cqiAperiodicMode = wrSmDfltCqiRprtModeAperiodic;
    enbCfg->cqiRptCfg.nomPdschRsEpreOff = (U8)wrSmDfltCqiNomPDSCHRSEPREoff;
    enbCfg->cqiRptCfg.periodRptSetupPres = FALSE;
    enbCfg->cqiRptCfg.cqiPucchRsrcIdx = wrSmDfltCqiPUCCHResIdx;
    enbCfg->cqiRptCfg.cqipmiCfgIdx = WR_UMM_CQI_PMI_CONFIG_IDX;
    enbCfg->cqiRptCfg.subbndCqik = wrSmDfltUePrdDlCqiK;
    enbCfg->cqiRptCfg.fmtInd = WR_UE_CQI_FMT_WB;/*129311*/
    enbCfg->cqiRptCfg.riCfgIdx = 0;
    enbCfg->cqiRptCfg.simulAckNackAndCQI = wrSmDfltSimultAckNackAndCQI;
    enbCfg->cqiRptCfg.periodicmode = wrSmDfltPrdModeEnum;
    /*ccpu00129641*/
    enbCfg->cqiRptCfg.riPres = FALSE;
   RETVALUE(ROK);
} /* smBuildWrEnbCfg */

/*
*
*       Fun:   smBuildCdma1xRTTBandClass
*
*       Desc:  This function for filling the Cell Band Class Configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildCdma1xRTTBandClass
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildCdma1xRTTBandClass(*lwrMng)
LwrMngmt *lwrMng
#endif
{
   LwrNeighBandClassCfg *bandClassCfg =NULLP;
   U32 idx = 0; 
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_BAND_CLASS;
   lwrMng->t.protoCfg.t.cdmaBandClassCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.cdmaBandClassCfg.cellId = 1;
   lwrMng->t.protoCfg.t.cdmaBandClassCfg.numBandClass = 1;/* rcr */
  for(idx=0;idx<1;idx++)/*rcr*/
  {
   bandClassCfg =lwrMng->t.protoCfg.t.cdmaBandClassCfg.t.bcAddCfg;
   bandClassCfg->cdmaType = wrSmDflt1XRTT;
   bandClassCfg->t.bandClass1XRtt.reCfgType = wrSmDfltBandClsReCfgType;
   bandClassCfg->t.bandClass1XRtt.status = wrSmDfltBandClsStatus;
   bandClassCfg->t.bandClass1XRtt.bandClass =wrSmDfltBandClass;
   bandClassCfg->t.bandClass1XRtt.cellReselectPrior =wrSmDfltBandClsCellReSelPri;
   bandClassCfg->t.bandClass1XRtt.threshXHigh = wrSmDfltBandClassThresHigh;
   bandClassCfg->t.bandClass1XRtt.threshXLow = wrSmDfltBandClassThresLow;
   bandClassCfg++;
  } 
   RETVALUE(ROK);
}



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
*       File:  wr_sm_wr_cntrl.c 
*
*/

#ifdef ANSI
PRIVATE S16 smSndWrCdma1xRTTBandClass
(
void
)
#else
PRIVATE S16 smSndWrCdma1xRTTBandClass
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildCdma1xRTTBandClass(&lwrMng);
   
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}

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
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrEnbCfg(&lwrMng);
   
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
void
)
#else

PRIVATE S16 smSndWrCellCfg()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildCellCfg(&lwrMng);
   
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
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
void
)
#else
PUBLIC S16 smSndWrModCellCfg()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildModCellCfg(&lwrMng);

   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildModCellCfg
*
*       Desc:  fill in cellCfg for WR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*/
#ifdef ANSI
PUBLIC S16 smBuildModCellCfg
(
 LwrMngmt *lwrMng 
)
#else
PUBLIC S16 smBuildModCellCfg(lwrMng)
LwrMngmt lwrMng
#endif
{

   LwrCellMibCfgGrp *lwrMib = NULLP;
   LwrCellSib1CfgGrp *sib1 =NULLP;
   U8                cfgGrpIndex = 0;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng->t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellId = 1; /* this ownCellID in case of PLD based, jst logic cell */
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   
   /*Filling MIB params*/
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType 
                                                          = WR_CELL_CFG_GRP_MIB;
   lwrMib = &(lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.mibCfgGrp);
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;  
   lwrMib->dlBw = wrSmDfltCellDlBW[0];
   lwrMib->phichCfg.phichDur = wrSmDfltPhichDur;
   lwrMib->phichCfg.phichRes = wrSmDfltPhichRes;
   cfgGrpIndex++;

   /*Filling sib1 params*/
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType 
                                                        = WR_CELL_CFG_GRP_SIB1;
                                                          
   sib1 =&(lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib1CfgGrp);

   sib1->reCfgType = LWR_CELL_SIB1_CFG_CELL_ACCESS_INFO;

   sib1->cellAccessInfo.plmnInfo[0].rsrvdFrOperUse =wrSmDfltCellRsrvdForOperUse;

   /* Modify tac */
   /* kworks fix */
   sib1->cellAccessInfo.tac = (U16)(wrSmDfltTac + 1);

   sib1->cellAccessInfo.cellId = wrSmDfltCellId; /* wrSmDfltCellIdentity */
   sib1->cellAccessInfo.csgIndication = wrSmDfltCsgIndicator; 
   sib1->cellAccessInfo.csgIdentity.pres = (U8)wrSmDfltCsgIdPres;
   sib1->cellAccessInfo.csgIdentity.val = wrSmDfltCsgIdVal;
   sib1->cellAccessInfo.cellBarred = (U8)wrSmDfltCellBarred;
   sib1->cellAccessInfo.intraFreqReSelection = (Bool)wrSmDfltIntraFreqResel;

   sib1->cellSelectInfo.qRxLevMin = (S8)wrSmDlftqRxLevMin;
   /* Start - Fix for ccpu00123651 */
   wrFillTknU8(&(sib1->cellSelectInfo.qRxLevMinOffset), (U8)wrSmDfltqRxlevminoffset);
   /* End - Fix for ccpu00123651 */

   sib1->pMax = (S8)wrSmDfltPMax;
   
   sib1->siWindowSize = wrSmDfltSiWinSize;
   
/* ACC-TDD */   
#ifdef LTE_TDD
   sib1->tddCfg.specialSubframeCfg = wrSmTddSpecialSubframeConfig;
   sib1->tddCfg.subframeCfg = wrSmTddSubframeConfig;
#else
   // Not used for FDD - zero the configuration just to be safe
   sib1->tddCfg.specialSubframeCfg = 0;
   sib1->tddCfg.subframeCfg = 0;
#endif

   cfgGrpIndex++;

   lwrMng->t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;

   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildWrNehUtraFddCellCfg
*
*       Desc:  This function for filling neighbour cell configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrNehUtraFddCellCfg
(
LwrMngmt                     *lwrMng
)
#else /* if ANSI not defined*/
PUBLIC S16 smBuildWrNehUtraFddCellCfg(*lwrMng)
LwrMngmt                     *lwrMng;
#endif /* end of ANSI*/
{
   U8                        idx = 0;
   U8                        plmnIdx = 0;
   LwrUtraNeighCell          *utraNeghCell = NULLP;

   TRC2(smBuildWrNehUtraFddCellCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1;  /* this is ownCellID in case of PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = wrSmDfltNumofUtraFddNrCell;

   for (idx = 0; idx < wrSmDfltNumofUtraFddNrCell; idx++) 
   {
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type = 
         WR_NEIGH_CELL_UTRA_FDD;

      utraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].
            t.utranCell);

      utraNeghCell->nrIndex = wrSmDfltExtUtraCell[idx].relationIdx;
      utraNeghCell->rncId= smCfgCb.nghUtraFddInfo[idx]->rncId;

      utraNeghCell->cId = smCfgCb.nghUtraFddInfo[idx]->cId;

      utraNeghCell->numPlmn = wrSmDfltExtUtraCell[idx].numPlmns;
      for(plmnIdx = 0; plmnIdx < utraNeghCell->numPlmn; plmnIdx++)
      {
         /*Fix for ccpu00124056 */
         utraNeghCell->plmnId[plmnIdx].mcc[0] = wrSmDfltExtUtraCell[idx].
            plmnIds[plmnIdx].mcc[0];
         utraNeghCell->plmnId[plmnIdx].mcc[1] = wrSmDfltExtUtraCell[idx].
            plmnIds[plmnIdx].mcc[1];
         utraNeghCell->plmnId[plmnIdx].mcc[2] = wrSmDfltExtUtraCell[idx].
            plmnIds[plmnIdx].mcc[2];

         utraNeghCell->plmnId[plmnIdx].numMncDigits = wrSmDfltExtUtraCell[idx].
            plmnIds[plmnIdx].numMncDigits;

         utraNeghCell->plmnId[plmnIdx].mnc[0] = wrSmDfltExtUtraCell[idx].
            plmnIds[plmnIdx].mnc[0];
         utraNeghCell->plmnId[plmnIdx].mnc[1] = wrSmDfltExtUtraCell[idx].
            plmnIds[plmnIdx].mnc[1];

         if(3 == utraNeghCell->plmnId[plmnIdx].numMncDigits)
            utraNeghCell->plmnId[plmnIdx].mnc[2] = wrSmDfltExtUtraCell[idx].
               plmnIds[plmnIdx].mnc[2];
         /*End Fix for ccpu00124056 */
      }

      utraNeghCell->duplexMode = (U8)wrSmDfltExtUtraCell[idx].duplexType;
      utraNeghCell->t.utraFdd.psc = smCfgCb.nghUtraFddInfo[idx]->psc;
      utraNeghCell->t.utraFdd.arfcnDl = smCfgCb.nghUtraFddInfo[idx]->arfcnDl;
      utraNeghCell->t.utraFdd.arfcnUl = smCfgCb.nghUtraFddInfo[idx]->arfcnUl;
      utraNeghCell->t.utraFdd.isHOAllowed = TRUE;
      utraNeghCell->t.utraFdd.pcpich = 70;
      utraNeghCell->lac = smCfgCb.nghUtraFddInfo[idx]->lac;
      utraNeghCell->rac = smCfgCb.nghUtraFddInfo[idx]->rac;
      utraNeghCell->isRimSupported = smCfgCb.nghUtraFddInfo[idx]->isRimSupported;

      /*
         utraNeghCell->curRank      = wrSmDfltUtranNrCurRank;
         utraNeghCell->prevRank     = wrSmDfltUtranNrPrevRank;
         */
   }
   RETVALUE(ROK);
} /* end of smBuildWrNehUtraFddCellCfg */

/*
*
*       Fun:   smBuildWrNehUtraTddCellCfg
*
*       Desc:  This function for filling neighbour cell configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrNehUtraTddCellCfg
(
LwrMngmt                     *lwrMng
)
#else /* if ANSI not defined*/
PUBLIC S16 smBuildWrNehUtraTddCellCfg(*lwrMng)
LwrMngmt                     *lwrMng;
#endif /* end of ANSI*/
{
   U8                        idx = 0;
   U8                        plmnIdx = 0;
   LwrUtraNeighCell          *utraNeghCell = NULLP;

   TRC2(smBuildWrNehUtraTddCellCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1;  /* this is ownCellID in case of PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = wrSmDfltNumofUtraTddNrCell;

   for (idx = 0; idx < wrSmDfltNumofUtraTddNrCell; idx++) 
   {
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type = 
         WR_NEIGH_CELL_UTRA_TDD;

      utraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].
            t.utranCell);

      utraNeghCell->nrIndex = wrSmDfltExtUtraTddCell[idx].relationIdx;
      utraNeghCell->rncId= smCfgCb.nghUtraTddInfo[idx]->rncId;

      utraNeghCell->cId = smCfgCb.nghUtraTddInfo[idx]->cId;

      utraNeghCell->numPlmn = wrSmDfltExtUtraTddCell[idx].numPlmns;
      for(plmnIdx = 0; plmnIdx < utraNeghCell->numPlmn; plmnIdx++)
      {
         /*Fix for ccpu00124056 */
         utraNeghCell->plmnId[plmnIdx].mcc[0] = wrSmDfltExtUtraTddCell[idx].
            plmnIds[plmnIdx].mcc[0];
         utraNeghCell->plmnId[plmnIdx].mcc[1] = wrSmDfltExtUtraTddCell[idx].
            plmnIds[plmnIdx].mcc[1];
         utraNeghCell->plmnId[plmnIdx].mcc[2] = wrSmDfltExtUtraTddCell[idx].
            plmnIds[plmnIdx].mcc[2];

         utraNeghCell->plmnId[plmnIdx].numMncDigits = wrSmDfltExtUtraTddCell[idx].
            plmnIds[plmnIdx].numMncDigits;

         utraNeghCell->plmnId[plmnIdx].mnc[0] = wrSmDfltExtUtraTddCell[idx].
            plmnIds[plmnIdx].mnc[0];
         utraNeghCell->plmnId[plmnIdx].mnc[1] = wrSmDfltExtUtraTddCell[idx].
            plmnIds[plmnIdx].mnc[1];

         if(3 == utraNeghCell->plmnId[plmnIdx].numMncDigits)
            utraNeghCell->plmnId[plmnIdx].mnc[2] = wrSmDfltExtUtraTddCell[idx].
               plmnIds[plmnIdx].mnc[2];
         /*End Fix for ccpu00124056 */
      }

      utraNeghCell->duplexMode = (U8)wrSmDfltExtUtraTddCell[idx].duplexType;
      utraNeghCell->t.utraTdd.cellParamId = smCfgCb.nghUtraTddInfo[idx]->cellParamId;
      utraNeghCell->t.utraTdd.arfcn = smCfgCb.nghUtraTddInfo[idx]->arfcn;
      utraNeghCell->t.utraTdd.pccpch = smCfgCb.nghUtraTddInfo[idx]->ccpchTPwr;
      utraNeghCell->lac = smCfgCb.nghUtraTddInfo[idx]->lac;
      utraNeghCell->rac = smCfgCb.nghUtraTddInfo[idx]->rac;
      utraNeghCell->isRimSupported = smCfgCb.nghUtraTddInfo[idx]->isRimSupported;

      /*
         utraNeghCell->curRank      = wrSmDfltUtranNrCurRank;
         utraNeghCell->prevRank     = wrSmDfltUtranNrPrevRank;
         */
   }
   RETVALUE(ROK);
} /* end of smBuildWrNehUtraTddCellCfg */


/*
*
*       Fun:   smSndWrNhUtraCellCfg
*
*       Desc:  This function for sending Utra neighbour Cell Configuration to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PRIVATE S16 smSndWrNhUtraCellCfg
(
void
)
#else
PRIVATE S16 smSndWrNhUtraCellCfg()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNehUtraFddCellCfg(&lwrMng);
   smBuildWrNehUtraTddCellCfg(&lwrMng);
   
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
void
)
#else
PRIVATE S16 smSndWrNhCellCfg()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNehCellCfg(&lwrMng);
   
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
void
)
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNghCfg(&lwrMng);
   
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
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrMmeCfg(&lwrMng, mmeCfg);
   
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
}

/*
 *
 *       Fun:  smBuildWrNrCdmaHrpdFreqCfg- Build Neighbour frequency
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

PRIVATE S16 smBuildWrNrCdmaHrpdFreqCfg
(
 LwrMngmt *lwrMng
)
{
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1;  /* this is ownCellID in case of PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = 1;/* we are jst filling one frequency */
   nrFreqCfg =&(lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq);
   nrFreqCfg->type = WR_NEIGH_CELL_CDMA2K_HRPD;
   nrFreqCfg->t.cdmaHrpdFreq.reCfgType = wrSmDfltReCfgType;
   nrFreqCfg->t.cdmaHrpdFreq.status = wrSmDfltStatus;
   nrFreqCfg->t.cdmaHrpdFreq.bandClass = wrSmDfltBandClass;
   nrFreqCfg->t.cdmaHrpdFreq.arfcn = wrSmDfltArfcn;
   nrFreqCfg->t.cdmaHrpdFreq.searchRate = wrSmDfltSearchRate;
   nrFreqCfg->t.cdmaHrpdFreq.offsetFreq = wrSmDfltOffsetFreq;
   RETVALUE(ROK);
}

/*
 *
 *       Fun: smBuildWrNr1xCdmaFreqCfg- Build Neighbour frequency
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

PRIVATE S16 smBuildWrNr1xCdmaFreqCfg
(
 LwrMngmt *lwrMng
)
{
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;
      U32 idx = 0;
   
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = 1;//rcr

   for(idx=0;idx<1;idx++)
   {
     nrFreqCfg =&(lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq);
     nrFreqCfg->type = WR_NEIGH_CELL_CDMA2K_1XRTT;
  
     nrFreqCfg->t.cdma1xFreq.reCfgType = wrSmDfltReCfgType;
     nrFreqCfg->t.cdma1xFreq.status = wrSmDfltStatus;
     nrFreqCfg->t.cdma1xFreq.bandClass = wrSmDfltBandClass;
     nrFreqCfg->t.cdma1xFreq.arfcn = wrSmDfltArfcn;
     nrFreqCfg->t.cdma1xFreq.searchRate = wrSmDfltSearchRate;
     nrFreqCfg->t.cdma1xFreq.offsetFreq = wrSmDfltOffsetFreq;
  }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildWrNrUtraFddFreqCfg - Build Neighbour frequency
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
PRIVATE S16 smBuildWrNrUtraFddFreqCfg
(
 LwrMngmt *lwrMng
)
{
   U8  idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;

   TRC2(smBuildWrNrUtraFddFreqCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of
                                           PLD based conf, jst a logic entity */
   /* lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = wrSmDfltNumofUtraNrFreq;*/
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = (U8)smCfgCb.noOfUtraFddFreq;
   nrFreqCfg =lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq;
   for(idx = 0; idx < smCfgCb.noOfUtraFddFreq; idx++)
   {
      nrFreqCfg->type = WR_NEIGH_CELL_UTRA_FDD;
      nrFreqCfg->t.utranFreq.reCfgType = 0x000fff;
      nrFreqCfg->t.utranFreq.freqIndex = (U8)(wrSmDfltUtraFaPriorInfo[idx].
            faIndex);
      nrFreqCfg->t.utranFreq.t.utraFdd.arfcnUl = smCfgCb.nghUtraFddFreq[idx]->t.utraFdd.arfcnUl;
      nrFreqCfg->t.utranFreq.t.utraFdd.arfcnDl =  smCfgCb.nghUtraFddFreq[idx]->t.utraFdd.arfcnDl;
      
      nrFreqCfg->t.utranFreq.priority.pres = PRSNT_NODEF;
      nrFreqCfg->t.utranFreq.priority.val = (U8)wrSmDfltUtraFaPriorInfo[idx].
         priority;
      nrFreqCfg->t.utranFreq.threshXhigh = (U8)wrSmDfltUtraFaPriorInfo[idx].
         threshXhigh;
      nrFreqCfg->t.utranFreq.threshXlow = (U8)wrSmDfltUtraFaPriorInfo[idx].
         threshXLow;
      nrFreqCfg->t.utranFreq.qRxLevMin = (U8)wrSmDfltUtraFaPriorInfo[idx].
         qRxLevMin;
      nrFreqCfg->t.utranFreq.pMaxUtra = (U8)wrSmDfltUtraFaPriorInfo[idx].
         pMaxUtra;
      nrFreqCfg->t.utranFreq.t.utraFdd.pQualMin = (U8)wrSmDfltUtraFaPriorInfo[idx].
         qQualMin;
      nrFreqCfg->t.utranFreq.offsetFreq = (U8)wrSmDfltUtraFaPriorInfo[idx].
         offsetFreq;
      nrFreqCfg->t.utranFreq.duplexMode = (U8)wrSmDfltUtraFaPriorInfo[idx].
         duplexType;
      nrFreqCfg->t.utranFreq.t.utraFdd.thresR9.pres = PRSNT_NODEF;
      nrFreqCfg->t.utranFreq.t.utraFdd.thresR9.thresXHighQR9 =
         (U8)wrSmDfltUtraFaPriorInfo[idx].threshXhighQRel9;
      nrFreqCfg->t.utranFreq.t.utraFdd.thresR9.thresXLowQR9 =
         (U8)wrSmDfltUtraFaPriorInfo[idx].threshXlowQRel9;
      nrFreqCfg++;
   }
   RETVALUE(ROK);
} /* end of smBuildWrNrUtraFddFreqCfg */

/*
 *
 *       Fun:    smBuildWrNrUtraTddFreqCfg - Build Neighbour frequency
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
PRIVATE S16 smBuildWrNrUtraTddFreqCfg
(
 LwrMngmt *lwrMng
)
{
   U8  idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;

   TRC2(smBuildWrNrUtraTddFreqCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of
                                           PLD based conf, jst a logic entity */
   /* lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = wrSmDfltNumofUtraNrFreq;*/
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = (U8)smCfgCb.noOfUtraTddFreq;
   nrFreqCfg =lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq;
   for(idx = 0; idx < smCfgCb.noOfUtraTddFreq; idx++)
   {
      nrFreqCfg->type = WR_NEIGH_CELL_UTRA_TDD;
      nrFreqCfg->t.utranFreq.reCfgType = 0x000fff;
      nrFreqCfg->t.utranFreq.freqIndex = (U8)(wrSmDfltUtraTddFaPriorInfo[idx].
            faIndex);
      nrFreqCfg->t.utranFreq.t.utraTdd.arfcn = smCfgCb.nghUtraTddFreq[idx]->t.utraTdd.arfcn;
      nrFreqCfg->t.utranFreq.t.utraTdd.tddMode = smCfgCb.nghUtraTddFreq[idx]->t.utraTdd.tddMode;
      nrFreqCfg->t.utranFreq.t.utraTdd.bandIndicator = smCfgCb.nghUtraTddFreq[idx]->t.utraTdd.bandIndicator;
      
      nrFreqCfg->t.utranFreq.priority.pres = PRSNT_NODEF;
      nrFreqCfg->t.utranFreq.priority.val = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         priority;
      nrFreqCfg->t.utranFreq.threshXhigh = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         threshXhigh;
      nrFreqCfg->t.utranFreq.threshXlow = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         threshXLow;
      nrFreqCfg->t.utranFreq.qRxLevMin = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         qRxLevMin;
      nrFreqCfg->t.utranFreq.pMaxUtra = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         pMaxUtra;
      nrFreqCfg->t.utranFreq.offsetFreq = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         offsetFreq;
      nrFreqCfg->t.utranFreq.duplexMode = (U8)wrSmDfltUtraTddFaPriorInfo[idx].
         duplexType;
      nrFreqCfg++;
   }
   RETVALUE(ROK);
} /* end of smBuildWrNrUtraTddFreqCfg */

/*
 *
 *       Fun:    smBuildWrNrEutraFreqCfg - Build Neighbour frequency
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

PRIVATE S16 smBuildWrNrEutraFreqCfg
(
 LwrMngmt *lwrMng
)
{
   U32 idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic entity */
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = (U8)smCfgCb.noOfEutraFreq;


   nrFreqCfg = (lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq);
   nrFreqCfg->type = WR_NEIGH_CELL_EUTRA;

   for(idx=0; idx < smCfgCb.noOfEutraFreq; idx++)
   {
     nrFreqCfg->t.eutranFreq.reCfgType = wrSmDfltReCfgType;
     nrFreqCfg->t.eutranFreq.status = wrSmDfltStatus;
     nrFreqCfg->t.eutranFreq.earfcnUl = smCfgCb.nghEutraFreq[idx]->arfcnUl;
     nrFreqCfg->t.eutranFreq.earfcnDl = smCfgCb.nghEutraFreq[idx]->arfcnDl;
     nrFreqCfg->t.eutranFreq.priority = wrSmDfltPriority;
     nrFreqCfg->t.eutranFreq.qRxLevMin = wrSmDfltQRxLevMin;
     nrFreqCfg->t.eutranFreq.pMaxUsage = wrSmDfltPMaxUsage;
     nrFreqCfg->t.eutranFreq.pMax = wrSmDfltS3pMax;
     nrFreqCfg->t.eutranFreq.tReselection = wrSmDfltTReselection;
     nrFreqCfg->t.eutranFreq.sfUsage = wrSmDfltSfUsage;
     nrFreqCfg->t.eutranFreq.tReselectionSFMed = wrSmDfltTReselectionSFMed;
     nrFreqCfg->t.eutranFreq.tReselectionSFHigh = wrSmDfltTReselectionSFHigh;
     nrFreqCfg->t.eutranFreq.sIntraSearch.pres = PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.sIntraSearch.val = wrSmDfltSIntraSearch;
     nrFreqCfg->t.eutranFreq.sNonIntraSearch.pres = PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.sNonIntraSearch.val = wrSmDfltSNonIntraSearch;
     nrFreqCfg->t.eutranFreq.servThresholdLow = wrSmDfltServThresholdLow;
     nrFreqCfg->t.eutranFreq.threshXHigh = wrSmDfltThreshXHigh;
     nrFreqCfg->t.eutranFreq.threshXLow =  wrSmDfltThreshXLow;
     nrFreqCfg->t.eutranFreq.measBandwidth.pres =  PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.measBandwidth.val = wrSmDfltMeasBandwidth;
     nrFreqCfg->t.eutranFreq.presAntennaPort1 =  wrSmDfltPresAntennaPort1;
     nrFreqCfg->t.eutranFreq.neighCellCfg =  wrSmDfltNeighCellCfg;
     nrFreqCfg->t.eutranFreq.qOffsetFreq = LWR_Q_OFFSET_RANGE_0;
     nrFreqCfg->t.eutranFreq.offsetFreq =  LWR_Q_OFFSET_RANGE_0;
     nrFreqCfg->t.eutranFreq.sIntraSearchRel9.pres =  PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
     nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchQRel9 =  wrSmDfltsSearchQRel9;
     nrFreqCfg->t.eutranFreq.sInterSearchRel9.pres = PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
     nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
     nrFreqCfg->t.eutranFreq.qQualMinRel9.pres = PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.qQualMinRel9.val = wrSmDfltDualMinRel9;
     nrFreqCfg->t.eutranFreq.reselecThreshQRel9.pres = PRSNT_NODEF;
     nrFreqCfg->t.eutranFreq.reselecThreshQRel9.val =  wrSmDfltReselecThreshQRel9;
     nrFreqCfg->t.eutranFreq.threshXQRel9.threshXHighQR9 =  wrSmDfltThreshXHighQR9;
     nrFreqCfg->t.eutranFreq.threshXQRel9.threshXLowQR9 =  wrSmDfltThreshXLowQR9;

     nrFreqCfg++;
   }
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

PRIVATE S16 smSndWrNrCdmaHrpdFreqCfg()
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNrCdmaHrpdFreqCfg(&lwrMng);
   
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
}

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

PRIVATE S16 smSndWrNr1xCdmaFreqCfg()
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNr1xCdmaFreqCfg(&lwrMng);
   
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
}

/*
 *
 *       Fun:    smSndWrUtraNrFreqCfg - configure Neighbour Utra frequency
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
PRIVATE S16 smSndWrNrUtraFreqCfg
(
Void
)
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNrUtraFddFreqCfg(&lwrMng);
   smBuildWrNrUtraTddFreqCfg(&lwrMng);
   
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
}
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
Void
)
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildWrNrEutraFreqCfg(&lwrMng);
   
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
   U8 idx;

   TRC2(wrSmWrCfg)

#ifdef WR_DBG_CIRLOG
   if (smRegInitTmr() != ROK)
   {
      RLOG0(L_ERROR, " wrRegInitTmr Failed ");
      RETVOID;
   }

   cmInitTimers(&(smCb.cfgCb.logTimer), 1);
   smStartTmr((PTR)&(smCb),SM_TMR_LOG_TMR, SM_TMR_LOG_TMR_VAL);
#endif
   smBuildWrGenCfg();
   smBuildWrCtfLSapCfg(WR_YS_SUID, WR_YS_SPID);
   smBuildWrNhuLSapCfg(WR_NH_SUID, WR_NH_SPID);
#ifdef EU_DAT_APP
   smBuildWrPjuLSapCfg(WR_PJ_SUID, WR_PJ_SPID);
   smBuildWrEgtLSapCfg(WR_EG_SUID, WR_EG_SPID);
#endif
   smBuildWrSztLSapCfg(WR_SZ_SUID, WR_SZ_SPID);
#ifdef RM_INTF
   smBuildWrRmuLSapCfg(WR_RM_SUID, WR_RM_SPID); /*RRM->FSM sck changes*/
#endif /*RM_INTF*/

   smBuildWrCztLSapCfg(WR_CZ_SUID, WR_CZ_SPID);
   smBuildWrRgrLSapCfg(WR_RG_SUID, WR_RG_SPID);

   smSndWrEnbCfg();
   smSndWrCellCfg();
   for (idx = 0; idx < smCfgCb.noOfCfg; idx++)
   {
      smSndWrMmeCfg((smCfgCb.mmeCfg[idx]));
   }
   smSndWrNhCfg();
   smSndWrNrEutraFreqCfg();
   smSndWrNrUtraFreqCfg();
   smSndWrNhCellCfg();
   smSndWrNhUtraCellCfg();
   
   RETVOID;
} /* end of wrSmWrCfg */

PRIVATE S16 smUtlGetNumNghEnbCfg
(
Void
)
{
   S16 idx = 0;
   S16 indx2 = 0;
   U32 enbId = 0;
   U32 enbId1 = 0;
   S16 numEnb = 0;
   Bool newEnb = TRUE; /* it much be always true for the first enb */

   for(idx = 0; idx < smCfgCb.noOfNghCfg; idx++)
   {
      if(smCfgCb.wrNghCellCfg[idx]->enbType == WR_ENODEB_TYPE_MACRO)
         enbId = smCfgCb.wrNghCellCfg[idx]->enbId >> 8;
      else
         enbId = smCfgCb.wrNghCellCfg[idx]->enbId;

      for(indx2 = 0; indx2 < idx; indx2++)
      {
         if(smCfgCb.wrNghCellCfg[indx2]->enbType == WR_ENODEB_TYPE_MACRO)
            enbId1 = smCfgCb.wrNghCellCfg[indx2]->enbId >> 8;
         else
            enbId1 = smCfgCb.wrNghCellCfg[indx2]->enbId;

         if(enbId == enbId1)
         {
            newEnb = FALSE;
            break;
         }
      }
      if(newEnb == TRUE)
         numEnb++;
      else
         newEnb = TRUE;
   }
   RETVALUE(numEnb);
}

PRIVATE S16 smUtlGetNumIntraFreqNghCellCfg
(
)
{
   S32   lpCnt;
   S16   numCells = 0;
   for (lpCnt = 0; lpCnt < smCfgCb.noOfNghCfg; lpCnt++)
   {
      /* not including intra - frequency neighbors */
      if(smCfgCb.wrNghCellCfg[lpCnt]->dlEarfcn == wrSmDfltServingCellDLCarrierFreq)
      {
         numCells++;
      }
   }
   RETVALUE(numCells);
}

PRIVATE S16 smUtlGetNumInterFreqNghCellCfg
(
Void
)
{
   S32   lpCnt;
   S16   numCells = 0;
   for (lpCnt = 0; lpCnt < smCfgCb.noOfNghCfg; lpCnt++)
   {
      /* not including intra - frequency neighbors */
      if(smCfgCb.wrNghCellCfg[lpCnt]->dlEarfcn != wrSmDfltServingCellDLCarrierFreq)
      {
         numCells++;
      }
   }
   RETVALUE(numCells);
}

/*
*
*       Fun:   smBuildWrInterFreqNehCellCfg
*
*       Desc:  This function for filling neighbour cell configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrInterFreqNehCellCfg
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildWrInterFreqNehCellCfg(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrEUTRANeighCell *eutraNeghCell = NULLP;
   S32   lpCnt = 0;
   S32   cfgIndx = 0;
   S32   numCfg = 0;
   
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic entity */
   numCfg = smUtlGetNumInterFreqNghCellCfg();
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = (U16)numCfg;

   for (lpCnt = 0; lpCnt < smCfgCb.noOfNghCfg; lpCnt++)
   {
      /* not including intra - frequency neighbors */
      if(smCfgCb.wrNghCellCfg[lpCnt]->dlEarfcn == wrSmDfltServingCellDLCarrierFreq)
      {
         continue;
      }
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[cfgIndx].type = WR_NEIGH_CELL_EUTRA;
      eutraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[cfgIndx].t.eutraCell);

      eutraNeghCell->cellNum = wrSmDfltNeigCellNum[0];
      eutraNeghCell->nrIndex = 4;
      eutraNeghCell->enbId = smCfgCb.wrNghCellCfg[lpCnt]->enbId;
   
      eutraNeghCell->cio =wrSmDfltCIO;
       eutraNeghCell->enbPlmn.numMncDigits = wrSmDfltNeEnbNumMncDigits;
      eutraNeghCell->enbPlmn.mcc[0] =wrSmDfltNeEnbPlmn1Mcc0[1];
      eutraNeghCell->enbPlmn.mcc[1] =wrSmDfltNeEnbPlmn1Mcc1[1];
      eutraNeghCell->enbPlmn.mcc[2] =wrSmDfltNeEnbPlmn1Mcc2[1];

      eutraNeghCell->enbPlmn.mnc[0] =wrSmDfltNeEnbPlmn1Mnc0[1];
      eutraNeghCell->enbPlmn.mnc[1] =wrSmDfltNeEnbPlmn1Mnc1[1];
      eutraNeghCell->enbPlmn.mnc[2] =wrSmDfltNeEnbPlmn1Mnc2[1];

      eutraNeghCell->enbType = smCfgCb.wrNghCellCfg[lpCnt]->enbType;
      eutraNeghCell->numPlmn = wrSmDfltNeighCellNoPlmn;

      eutraNeghCell->pci = smCfgCb.wrNghCellCfg[lpCnt]->physCellId;
      eutraNeghCell->tac = smCfgCb.wrNghCellCfg[lpCnt]->tac;

      eutraNeghCell->qoffset = wrSmDfltQoff;

   eutraNeghCell->dlBw = wrSmDfltCellDlBW[0];
   /* kworks fix */
   eutraNeghCell->earfcnDl = (U16)smCfgCb.wrNghCellCfg[lpCnt]->dlEarfcn;
   eutraNeghCell->earfcnUl= (U16)smCfgCb.wrNghCellCfg[lpCnt]->ulEarfcn;
   cfgIndx++;
   }
  
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildWrNehCellCfg
*
*       Desc:  This function for filling neighbour cell configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrNehCellCfg
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildWrNehCellCfg(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrEUTRANeighCell *eutraNeghCell = NULLP;
   U32 idx; 
 /* Amit Changes Start
   U32 index1 = 0;
   Amit Changes End 
   S16 numCells = 0; */
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1; /* this is ownCellID in case of PLD, jst a logical entity */
   //numCells = smUtlGetNumIntraFreqNghCellCfg();
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = smCfgCb.noOfNghCfg;

   for(idx = 0; idx < smCfgCb.noOfNghCfg; idx++)
   {
      /* not including inter - frequency neighbors */
/*   Amit Changes Start 
      if(smCfgCb.wrNghCellCfg[idx]->dlEarfcn != wrSmDfltServingCellDLCarrierFreq)
   {
         continue;
      }
     Amit Changes End */
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type = WR_NEIGH_CELL_EUTRA;
      eutraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].t.eutraCell);
      eutraNeghCell->cellNum = wrSmDfltNeigCellNum[idx];
      eutraNeghCell->nrIndex = wrSmDfltNriIndex[idx];
      eutraNeghCell->enbId = smCfgCb.wrNghCellCfg[idx]->enbId;

      eutraNeghCell->cio =wrSmDfltCIO;
      eutraNeghCell->enbPlmn.numMncDigits = wrSmDfltNeEnbNumMncDigits;
      eutraNeghCell->enbPlmn.mcc[0] =wrSmDfltNeEnbPlmn1Mcc0[idx];
      eutraNeghCell->enbPlmn.mcc[1] =wrSmDfltNeEnbPlmn1Mcc1[idx];
      eutraNeghCell->enbPlmn.mcc[2] =wrSmDfltNeEnbPlmn1Mcc2[idx];

      eutraNeghCell->enbPlmn.mnc[0] =wrSmDfltNeEnbPlmn1Mnc0[idx];
      eutraNeghCell->enbPlmn.mnc[1] =wrSmDfltNeEnbPlmn1Mnc1[idx];
      eutraNeghCell->enbPlmn.mnc[2] =wrSmDfltNeEnbPlmn1Mnc2[idx];

      eutraNeghCell->enbType = smCfgCb.wrNghCellCfg[idx]->enbType;
   eutraNeghCell->numPlmn = wrSmDfltNeighCellNoPlmn;

      eutraNeghCell->pci = smCfgCb.wrNghCellCfg[idx]->physCellId;
      eutraNeghCell->tac = smCfgCb.wrNghCellCfg[idx]->tac;

   eutraNeghCell->qoffset = wrSmDfltQoff;

      eutraNeghCell->dlBw = wrSmDfltCellDlBW[0];
      /* kworks fix */
      eutraNeghCell->earfcnDl = (U16)smCfgCb.wrNghCellCfg[idx]->dlEarfcn;
      eutraNeghCell->earfcnUl= (U16)smCfgCb.wrNghCellCfg[idx]->ulEarfcn;
      /* CSG_DEV start */
      eutraNeghCell->isCsgIdResolved = WR_EMM_NBR_CSG_ID_DISCOVERED;
      eutraNeghCell->isCsgAccessModeResolved = WR_EMM_CELL_ACCESS_MODE_DETERMINED;
      eutraNeghCell->csgAccessMode = smCfgCb.wrNghCellCfg[idx]->csgAccessMode;
      eutraNeghCell->csgId = smCfgCb.wrNghCellCfg[idx]->csgId;
      eutraNeghCell->isHeMsCell = TRUE;
      /* CSG_DEV end */

      //eutraNeghCell++;
/* Amit Changes start 
      index1++;
   Amit Changes End */
   }   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildWrMmeCfg
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
PUBLIC S16 smBuildWrMmeCfg
(
LwrMngmt *lwrMng,
LwrSmMmeCfg *mmeSmCfg
)
#else
PUBLIC S16 smBuildWrMmeCfg(*lwrMng,*mmeCfg)
LwrMngmt *lwrMng;
LwrSmMmeCfg *mmeSmCfg;
#endif
{
   LwrAddModMmeCfg *mmeCfg =NULLP;
   
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_MME;
   lwrMng->t.protoCfg.t.mmeCfg.action = WR_ACT_ADD;

   mmeCfg =&(lwrMng->t.protoCfg.t.mmeCfg.t.addMme);

   mmeCfg->mmeIndex = (U8)mmeSmCfg->mmeId;

   /*Filling IP Address*/
   wrCpyCmTptAddr(&mmeCfg->ipAddr, &mmeSmCfg->mmeAddr);
   if(CM_TPTADDR_IPV4 == mmeCfg->ipAddr.type) 
   {
      mmeCfg->ipAddr.u.ipv4TptAddr.port = wrSmDfltMmePort;
   }
   else if(CM_TPTADDR_IPV6 == mmeCfg->ipAddr.type) 
   {
      mmeCfg->ipAddr.u.ipv6TptAddr.port = wrSmDfltMmePort;
   }

   /*Filling MME state*/
   mmeCfg->mmeState =wrSmDfltMmeState;
   mmeCfg->adminState =wrSmDfltMmeAdminState;
   
   RETVALUE(ROK);
}


/*
*
*       Fun:   smBuildWrNghCfg
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
PUBLIC S16 smBuildWrNghCfg
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildWrNghCfg(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrNeighAddModCfg *neighCfg = NULLP;
   U32 idx = 0;
   U32 enbId = 0;
   U32 enbId1 = 0;
   U32 indx2 = 0;
   U32 cfgIndx = 0;
   Bool oldEnb = FALSE;
   
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH;
   lwrMng->t.protoCfg.t.neighCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCfg.cellId = 1; /* this ownCellID in case of PLD based, jst a logic entity */
   /* kworks fix */
   lwrMng->t.protoCfg.t.neighCfg.numEnb = (U8)smUtlGetNumNghEnbCfg();
   
   neighCfg = (lwrMng->t.protoCfg.t.neighCfg.t.neighAdd);
   for(idx = 0; idx < smCfgCb.noOfNghCfg; idx++)
   {
      oldEnb = FALSE;
      if(smCfgCb.wrNghCellCfg[idx]->enbType == WR_ENODEB_TYPE_MACRO)
         enbId = smCfgCb.wrNghCellCfg[idx]->enbId >> 8;
      else
         enbId = smCfgCb.wrNghCellCfg[idx]->enbId;

      for(indx2 = 0; indx2 < idx; indx2++)
      {
         /* checking if the eNB is already add to configuration */
         /* if yes, ignoring the dulicate configuration and proceeding */
         /* this may occur when multiple cells or same eNB is configured */
         if(smCfgCb.wrNghCellCfg[indx2]->enbType == WR_ENODEB_TYPE_MACRO)
            enbId1 = smCfgCb.wrNghCellCfg[indx2]->enbId >> 8;
         else
            enbId1 = smCfgCb.wrNghCellCfg[indx2]->enbId;

         if(enbId == enbId1)
         {
            oldEnb = TRUE;
            break;
         }
      }
      if(oldEnb == TRUE)
         continue;

      neighCfg->enbType = smCfgCb.wrNghCellCfg[idx]->enbType;
      neighCfg->enbId = enbId;
      neighCfg->enbIndx = wrSmDfltNeighEnbIndex[idx];
      neighCfg->peerId = smCfgCb.wrNghCellCfg[idx]->peerId;

      neighCfg->plmn.numMncDigits=wrSmDfltNeEnbNumMncDigits;
      neighCfg->plmn.mcc[0]=wrSmDfltNeEnbPlmn1Mcc0[idx];
      neighCfg->plmn.mcc[1]=wrSmDfltNeEnbPlmn1Mcc1[idx];
      neighCfg->plmn.mcc[2]=wrSmDfltNeEnbPlmn1Mcc2[idx];

      neighCfg->plmn.mnc[0] =wrSmDfltNeEnbPlmn1Mnc0[idx];
      neighCfg->plmn.mnc[1] =wrSmDfltNeEnbPlmn1Mnc1[idx];
      neighCfg->plmn.mnc[2] =wrSmDfltNeEnbPlmn1Mnc2[idx];

      wrCpyCmTptAddr(&neighCfg->ipAddr, &smCfgCb.wrNghCellCfg[idx]->enbAddr);
      if(CM_TPTADDR_IPV4 == neighCfg->ipAddr.type)
      {
         neighCfg->ipAddr.u.ipv4TptAddr.port = WRSM_LCZ_ENB_SCTPORT;
      }
      else if(CM_TPTADDR_IPV6 == neighCfg->ipAddr.type)
      {
         neighCfg->ipAddr.u.ipv6TptAddr.port = WRSM_LCZ_ENB_SCTPORT;
      }

/* LTE_ADV_DSFR starts */
      neighCfg->dsfrCEFreqRange = smCfgCb.wrNghCellCfg[index]->dsfrCEFreqRange;
/* LTE_ADV_DSFR ends */
      neighCfg->state = wrSmDfltNeEnbState;
      neighCfg->isX2Reqd = smCfgCb.wrNghCellCfg[idx]->trgrX2;
      neighCfg++;
   }   
   RETVALUE(ROK);
}

/*
*
*       Fun:   smBuildDynWrNbrEnbCfg
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
PUBLIC S16 smBuildDynWrNbrEnbCfg
(
U32    dbIndex,
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildDynWrNbrEnbCfg(dbIndex,lwrMng)
U8    dbIndex;
LwrMngmt *lwrMng;
#endif
{
   lwrMng->t.nbrAddCfm.enbId = smCfgCb.wrNghCellCfg[dbIndex]->enbId;
   lwrMng->t.nbrAddCfm.peerId =  smCfgCb.wrNghCellCfg[dbIndex]->peerId;
   wrCpyCmTptAddr(&lwrMng->t.nbrAddCfm.ipAddr,&smCfgCb.wrNghCellCfg[dbIndex]->ipAddr);
   RETVALUE(ROK);
}/*smBuildDynWrNbrEnbCfg*/

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
   
   smBuildDynWrNbrEnbCfg(dbIndex,&lwrMng);
   
    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   //smCb.smState = WR_SM_STATE_DYN_X2AP_CFG_DONE;
   (Void) SmMiLwrAddNeighCfm(&pst, &lwrMng);
   
   RETVALUE(ROK);

}/*wrSmmSendDynNbrEnbCfg */

PRIVATE Void smBldCellAnrCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex
)
{
   LwrCellAnrCfgGrp          *anrCfg;
   anrCfg = &lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.anrCfgGrp;
   
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                     WR_CELL_CFG_GRP_ANR;
   anrCfg->csfbTransTmrVal = wrSmDfltCsfbTmrVal;

    /*Removed DRX Flag */
   anrCfg->ueAnrDrxCfg.longDrxCycle = wrSmDfltAnrDrxLongCycle;  
   anrCfg->ueAnrDrxCfg.drxOnDurTmr  = wrSmDfltAnrDrxOnDurationTmr;
   /* Fix for ccpu00132334 - To read DRX Inactivity timer for ANR*/
   anrCfg->ueAnrDrxCfg.inActivTmr  = wrSmDfltAnrDrxInActivTmr; 
   
   RETVOID;

} /* end of smBldCellAnrCfg */

PRIVATE void smBldCellSibSchCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex
)
{
   LwrCellSibSchedCfgGrp *sibSchCfg = NULLP;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                     WR_CELL_CFG_GRP_SIB_SCHED;
   
   sibSchCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sibSchedCfgGrp);
   /* Populate the SIB periodicites */
   sibSchCfg->sib2Period = WR_SIB2_PERIOD; 
   sibSchCfg->sib3Period = WR_SIB3_PERIOD;
   sibSchCfg->sib4Period = WR_SIB4_PERIOD; 
   sibSchCfg->sib5Period = WR_SIB5_PERIOD; 
   sibSchCfg->sib6Period = WR_SIB6_PERIOD; 
   sibSchCfg->sib9Period = WR_SIB9_PERIOD; 
   sibSchCfg->siWindow = wrSmDfltSiWinSize;
#if 1
   sibSchCfg->sib10ManualPrdPres = TRUE;
   sibSchCfg->sib10RepetPeriod = wrSmDfltSib10RptPrd;
   sibSchCfg->sib10NumBroadCast = wrSmDfltSib10NumBroadCast;
#endif
   sibSchCfg->sib11WarnSegSize = wrSmDfltWarnSegSize;
} /* end of smBldCellSibSchCfg */

PRIVATE void smBldCellRabConfigParam
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex
)
{
   U16                 idx;         
   LwrRabPolicyCfgGrp *rabPolicyCfg = NULLP;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                     WR_CELL_CFG_GRP_RAB_PARAMS;
   
   rabPolicyCfg= &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.rabPolicyCfgGrp);
   rabPolicyCfg->numDrbPolicies=WR_MAX_QCI;
   for(idx=0;idx<rabPolicyCfg->numDrbPolicies;idx++)
   {
       if(smCfgCb.isDscpEnable==TRUE)
     {
          rabPolicyCfg->drbPolicy[idx].qciInfo.qciSupported=TRUE;
          rabPolicyCfg->drbPolicy[idx].qci=(idx+1);
          rabPolicyCfg->drbPolicy[idx].dscpInfo.qci=(idx+1);
          rabPolicyCfg->drbPolicy[idx].dscpInfo.dscp=smCfgCb.qciDscpMap[idx];
   }
       else
       {
          rabPolicyCfg->drbPolicy[idx].qciInfo.qciSupported=TRUE;
          rabPolicyCfg->drbPolicy[idx].qci=(idx+1);
          rabPolicyCfg->drbPolicy[idx].dscpInfo.qci=(idx+1);
          rabPolicyCfg->drbPolicy[idx].dscpInfo.dscp=0;
       } 
   }
      rabPolicyCfg->drbPolicy[0].rlcInfo.rlcMode = WR_RLC_UM_MODE;
      rabPolicyCfg->drbPolicy[0].rlcInfo.ulSnFieldLength = NhuSN_FieldLengthsize5Enum;
      rabPolicyCfg->drbPolicy[0].rlcInfo.dlSnFieldLength = NhuSN_FieldLengthsize10Enum;
      rabPolicyCfg->drbPolicy[0].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[0].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring;
      rabPolicyCfg->drbPolicy[0].pdcpInfo.umSnSize = NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
      rabPolicyCfg->drbPolicy[0].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[0].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[0].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[1].lchPriority;
      rabPolicyCfg->drbPolicy[0].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[1].pbr;
      rabPolicyCfg->drbPolicy[0].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[1].bucketSizeDur;

      rabPolicyCfg->drbPolicy[1].rlcInfo.rlcMode = WR_RLC_UM_MODE;
      rabPolicyCfg->drbPolicy[1].rlcInfo.ulSnFieldLength = NhuSN_FieldLengthsize5Enum;
      rabPolicyCfg->drbPolicy[1].rlcInfo.dlSnFieldLength = NhuSN_FieldLengthsize10Enum;
      rabPolicyCfg->drbPolicy[1].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[1].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring;
      rabPolicyCfg->drbPolicy[1].pdcpInfo.umSnSize = NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
      rabPolicyCfg->drbPolicy[1].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[1].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[1].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[2].lchPriority;
      rabPolicyCfg->drbPolicy[1].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[2].pbr;
      rabPolicyCfg->drbPolicy[1].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[2].bucketSizeDur;

      rabPolicyCfg->drbPolicy[2].rlcInfo.rlcMode = WR_RLC_UM_MODE;
      rabPolicyCfg->drbPolicy[2].rlcInfo.ulSnFieldLength = NhuSN_FieldLengthsize5Enum;
      rabPolicyCfg->drbPolicy[2].rlcInfo.dlSnFieldLength = NhuSN_FieldLengthsize10Enum;
      rabPolicyCfg->drbPolicy[2].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[2].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring;
      rabPolicyCfg->drbPolicy[2].pdcpInfo.umSnSize = NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
      rabPolicyCfg->drbPolicy[2].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[2].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[2].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[3].lchPriority;
      rabPolicyCfg->drbPolicy[2].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[3].pbr;
      rabPolicyCfg->drbPolicy[2].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[3].bucketSizeDur;
   
      rabPolicyCfg->drbPolicy[3].rlcInfo.rlcMode = WR_RLC_UM_MODE;
      rabPolicyCfg->drbPolicy[3].rlcInfo.ulSnFieldLength = NhuSN_FieldLengthsize5Enum;
      rabPolicyCfg->drbPolicy[3].rlcInfo.dlSnFieldLength = NhuSN_FieldLengthsize10Enum;
      rabPolicyCfg->drbPolicy[3].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[3].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring;
      rabPolicyCfg->drbPolicy[3].pdcpInfo.umSnSize = NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
      rabPolicyCfg->drbPolicy[3].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[3].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[3].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[4].lchPriority;
      rabPolicyCfg->drbPolicy[3].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[4].pbr;
      rabPolicyCfg->drbPolicy[3].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[4].bucketSizeDur;


      rabPolicyCfg->drbPolicy[4].rlcInfo.rlcMode = WR_RLC_AM_MODE;
      rabPolicyCfg->drbPolicy[4].rlcInfo.ulTimerStatusProhibit = NhuT_StatusProhibitms10Enum; 
      rabPolicyCfg->drbPolicy[4].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[4].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
      rabPolicyCfg->drbPolicy[4].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[4].rlcInfo.ulTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[4].rlcInfo.ulMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum;
      rabPolicyCfg->drbPolicy[4].rlcInfo.dlTimerStatusProhibit = NhuT_StatusProhibitms35Enum;
      rabPolicyCfg->drbPolicy[4].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring; 
      rabPolicyCfg->drbPolicy[4].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
      rabPolicyCfg->drbPolicy[4].rlcInfo.dlPollPdu = NhuPollPDUp8Enum; 
      rabPolicyCfg->drbPolicy[4].rlcInfo.dlTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[4].rlcInfo.dlMaxRetransThresh = NhuPDCP_ConfigdiscardTimerinfinityEnum; 
      rabPolicyCfg->drbPolicy[4].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[4].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[4].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[5].lchPriority;
      rabPolicyCfg->drbPolicy[4].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[5].pbr;
      rabPolicyCfg->drbPolicy[4].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[5].bucketSizeDur;

      rabPolicyCfg->drbPolicy[5].rlcInfo.rlcMode = WR_RLC_AM_MODE;
      rabPolicyCfg->drbPolicy[5].rlcInfo.ulTimerStatusProhibit = NhuT_StatusProhibitms10Enum; 
      rabPolicyCfg->drbPolicy[5].rlcInfo.ulTimerReordering = NhuT_Reorderingms30Enum;
      rabPolicyCfg->drbPolicy[5].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
      rabPolicyCfg->drbPolicy[5].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[5].rlcInfo.ulTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[5].rlcInfo.ulMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum;
      rabPolicyCfg->drbPolicy[5].rlcInfo.dlTimerStatusProhibit = NhuT_StatusProhibitms40Enum;
      rabPolicyCfg->drbPolicy[5].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring; 
      rabPolicyCfg->drbPolicy[5].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
      rabPolicyCfg->drbPolicy[5].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[5].rlcInfo.dlTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[5].rlcInfo.dlMaxRetransThresh = NhuPDCP_ConfigdiscardTimerinfinityEnum; 
      rabPolicyCfg->drbPolicy[5].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[5].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[5].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[6].lchPriority;
      rabPolicyCfg->drbPolicy[5].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[6].pbr;
      rabPolicyCfg->drbPolicy[5].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[6].bucketSizeDur;

      rabPolicyCfg->drbPolicy[6].rlcInfo.rlcMode = WR_RLC_AM_MODE;
      rabPolicyCfg->drbPolicy[6].rlcInfo.ulTimerStatusProhibit = NhuT_StatusProhibitms35Enum; 
      rabPolicyCfg->drbPolicy[6].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[6].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
      rabPolicyCfg->drbPolicy[6].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[6].rlcInfo.ulTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[6].rlcInfo.ulMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum;
      rabPolicyCfg->drbPolicy[6].rlcInfo.dlTimerStatusProhibit = NhuT_StatusProhibitms5Enum;
      rabPolicyCfg->drbPolicy[6].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring; 
      rabPolicyCfg->drbPolicy[6].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
      rabPolicyCfg->drbPolicy[6].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[6].rlcInfo.dlTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[6].rlcInfo.dlMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum; 
      rabPolicyCfg->drbPolicy[6].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[6].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[6].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[7].lchPriority;
      rabPolicyCfg->drbPolicy[6].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[7].pbr;
      rabPolicyCfg->drbPolicy[6].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[7].bucketSizeDur;

      rabPolicyCfg->drbPolicy[7].rlcInfo.rlcMode = WR_RLC_AM_MODE;
      rabPolicyCfg->drbPolicy[7].rlcInfo.ulTimerStatusProhibit = NhuT_StatusProhibitms35Enum; 
      rabPolicyCfg->drbPolicy[7].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[7].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
      rabPolicyCfg->drbPolicy[7].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[7].rlcInfo.ulTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[7].rlcInfo.ulMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum;
      rabPolicyCfg->drbPolicy[7].rlcInfo.dlTimerStatusProhibit = NhuT_StatusProhibitms35Enum;
      rabPolicyCfg->drbPolicy[7].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring; 
      rabPolicyCfg->drbPolicy[7].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
      rabPolicyCfg->drbPolicy[7].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[7].rlcInfo.dlTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[7].rlcInfo.dlMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum; 
      rabPolicyCfg->drbPolicy[7].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[7].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[7].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[8].lchPriority;
      rabPolicyCfg->drbPolicy[7].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[8].pbr;
      rabPolicyCfg->drbPolicy[7].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[8].bucketSizeDur;

      rabPolicyCfg->drbPolicy[8].rlcInfo.rlcMode = WR_RLC_AM_MODE;
      rabPolicyCfg->drbPolicy[8].rlcInfo.ulTimerStatusProhibit = NhuT_StatusProhibitms35Enum; 
      rabPolicyCfg->drbPolicy[8].rlcInfo.ulTimerReordering = wrSmDfltUlDrbtReordring;
      rabPolicyCfg->drbPolicy[8].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
      rabPolicyCfg->drbPolicy[8].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[8].rlcInfo.ulTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[8].rlcInfo.ulMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum;
      rabPolicyCfg->drbPolicy[8].rlcInfo.dlTimerStatusProhibit = NhuT_StatusProhibitms35Enum;
      rabPolicyCfg->drbPolicy[8].rlcInfo.dlTimerReordering = wrSmDfltDlDrbtReordring; 
      rabPolicyCfg->drbPolicy[8].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
      rabPolicyCfg->drbPolicy[8].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
      rabPolicyCfg->drbPolicy[8].rlcInfo.dlTpRetransmit = NhuT_PollRetransmitms400Enum;
      rabPolicyCfg->drbPolicy[8].rlcInfo.dlMaxRetransThresh = NhuUL_AM_RLCmaxRetxThresholdt8Enum; 
      rabPolicyCfg->drbPolicy[8].pdcpInfo.discardTimer = NhuPDCP_ConfigdiscardTimerinfinityEnum;
      rabPolicyCfg->drbPolicy[8].pdcpInfo.statRprtReqrd = TRUE;
      rabPolicyCfg->drbPolicy[8].lchInfo.lchPriority        = wrSmDfltPrioInfoTbl.drb[9].lchPriority;
      rabPolicyCfg->drbPolicy[8].lchInfo.prioritisedBitRate = wrSmDfltPrioInfoTbl.drb[9].pbr;
      rabPolicyCfg->drbPolicy[8].lchInfo.bcketSizeDurn      = wrSmDfltPrioInfoTbl.drb[9].bucketSizeDur;

} /* end of smBldCellRabConfigaaram */
PRIVATE void smBldCellEaidCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex
)
{
   LwrCellEAIDCfgGrp         *eaidCfgGrp = NULLP;
   U8                        idx = 0; 
   U32                       tempEaid = 0x112233;
   
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                          WR_CELL_CFG_GRP_EAID;
   
  eaidCfgGrp = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.eaidCfgGrp);

  for (idx = 0; idx < LWR_SM_MAX_EAIDS; idx++)
  {
     eaidCfgGrp->eaid[idx].pres = TRUE;
     eaidCfgGrp->eaid[idx].val = tempEaid++;
  }
} /* end of smBldCellEaidCfG */

PRIVATE Void smBldMeasCellCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex
)
{
   LwrCellMeasCfgGrp         *measCfg = NULLP;
   LwrMeasEvntA5RptCfg       *a5Cfg;
   LwrMeasEvntRptCfg         *eventCfg;
   LwrMeasEutraPeridRptCfg   *eutraPerd;
   LwrMeasUtraPeriodRptCfg   *utraPerd;
   S8                         offset;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                        WR_CELL_CFG_GRP_MEAS;
   
   measCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.measCfgGrp);

   eventCfg = &measCfg->measA1EvtRptCfg[WR_MEAS_EVENTA1_HO_RSRP];
   /* configure Event A1 */
   eventCfg->isPres.pres = PRSNT_NODEF;
   eventCfg->reason = wrSmDfltReason;
   eventCfg->threshold_RSRP = wrSmDfltA1ThresRSRP;
   eventCfg->threshold_RSRQ = wrSmDfltThresRSRQ1;
   eventCfg->hysteresis = wrSmDfltHysteresis;
   eventCfg->timeToTrigger = wrSmDfltTimeToTrig;
   eventCfg->triggerQty = wrSmDfltTrigQty;
   eventCfg->reportQty = wrSmDfltRptQty;
   eventCfg->maxRptCells = wrSmDfltMaxRptCells;
   eventCfg->reportInterval = wrSmDfltRptInterval;
   eventCfg->reportAmount = wrSmDfltRptAmount;

   eventCfg = &measCfg->measA2EvtRptCfg[WR_MEAS_EVENTA2_HO_RSRP];
   /* configure Event A2 */
   eventCfg->isPres.pres = PRSNT_NODEF;
   eventCfg->reason = wrSmDfltReason;
   eventCfg->threshold_RSRP = wrSmDfltA2ThresRSRP;
   eventCfg->threshold_RSRQ = wrSmDfltThresRSRQ1;
   eventCfg->hysteresis = wrSmDfltHysteresis;
   eventCfg->timeToTrigger = wrSmDfltTimeToTrig;
   eventCfg->triggerQty = wrSmDfltTrigQty;
   eventCfg->reportQty = wrSmDfltRptQty;
   eventCfg->maxRptCells = wrSmDfltMaxRptCells;
   eventCfg->reportInterval = wrSmDfltRptInterval;
   eventCfg->reportAmount = wrSmDfltRptAmount;

   eventCfg = &measCfg->measA4EvtRptCfg[WR_MEAS_EVENTA4_ANR_SPECIFIC];
   /* configure Event A4 */
   eventCfg->isPres.pres = PRSNT_NODEF;
   eventCfg->reason = wrSmDfltReason;
   eventCfg->threshold_RSRP = wrSmDfltThresRSRP1;
   eventCfg->threshold_RSRQ = wrSmDfltThresRSRQ1;
   eventCfg->hysteresis = wrSmDfltHysteresis;
   eventCfg->timeToTrigger = wrSmDfltTimeToTrig;
   eventCfg->triggerQty = wrSmDfltTrigQty;
   eventCfg->reportQty = wrSmDfltRptQty;
   eventCfg->maxRptCells = wrSmDfltMaxRptCells;
   eventCfg->reportInterval = wrSmDfltRptInterval;
   eventCfg->reportAmount = wrSmDfltRptAmount;

   /* configure Event A3 */
   measCfg->measEvtA3Cfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measEvtA3Cfg[0].reason = wrSmDfltReason;
/* LTE_ADV starts */ /* #ifdef AIRSPAN_LTE_ADV */
   offset = wrSmDfltIntraA5ThresRSRP1 - wrSmDfltIntraA5ThresRSRP2;
   /* Offset Range is between -30 to 30*/
   if(offset > 31)
   {
      offset = 30;
   }
   else if (offset < -31)
   {
      offset = -30;
   }
   measCfg->measEvtA3Cfg[0].offset = offset;
/* LTE_ADV ends */
   measCfg->measEvtA3Cfg[0].reportOnLeave = wrSmDfltRptOnLeave;
   measCfg->measEvtA3Cfg[0].hysteresis = wrSmDfltHysteresis;
   measCfg->measEvtA3Cfg[0].timeToTrigger = wrSmDfltTimeToTrig;
   measCfg->measEvtA3Cfg[0].triggerQty = wrSmDfltTrigQty;
   measCfg->measEvtA3Cfg[0].reportQty = wrSmDfltRptQty;
   measCfg->measEvtA3Cfg[0].maxRptCells = wrSmDfltMaxRptCells;
   measCfg->measEvtA3Cfg[0].reportInterval = wrSmDfltRptInterval;
   measCfg->measEvtA3Cfg[0].reportAmount = wrSmDfltRptAmount;

/* LTE_ADV_ABS starts */
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].isPres.pres = PRSNT_NODEF;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reason = wrSmDfltReason;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].offset = 0; /* All neighbor stronger than serving */
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportOnLeave = FALSE; 
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].hysteresis = wrSmDfltHysteresis;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].timeToTrigger = wrSmDfltTimeToTrig;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].triggerQty = wrSmDfltTrigQty;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportQty = wrSmDfltRptQty;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].maxRptCells = wrSmDfltMaxRptCells;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportInterval = wrSmDfltRptInterval;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportAmount = 0; /* Report only once */
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].offset = smCfgCb.lteAdvancedConfig.a3Offset; /* ABS Offset */
/* LTE_ADV_ABS ends */

   a5Cfg = &measCfg->measEvtA5Cfg[WR_MEAS_EVENTA5_INTRA_FREQ_HO];
   /* configure Intra Event A5 */
   a5Cfg->isPres.pres = PRSNT_NODEF;
   a5Cfg->reason = wrSmDfltReason;
   a5Cfg->threshold1_RSRP = wrSmDfltIntraA5ThresRSRP1;
   a5Cfg->threshold1_RSRQ = wrSmDfltThresRSRQ1;
   a5Cfg->threshold2_RSRP = wrSmDfltIntraA5ThresRSRP2;
   a5Cfg->threshold2_RSRQ = wrSmDfltThresRSRQ2;
   a5Cfg->hysteresis = wrSmDfltHysteresis;
   a5Cfg->timeToTrigger = wrSmDfltTimeToTrig;
   a5Cfg->triggerQty = wrSmDfltTrigQty;
   a5Cfg->reportQty = wrSmDfltRptQty;
   a5Cfg->maxRptCells = wrSmDfltMaxRptCells;
   a5Cfg->reportInterval = wrSmDfltRptInterval;
   a5Cfg->reportAmount = wrSmDfltRptAmount;

   a5Cfg = &measCfg->measEvtA5Cfg[WR_MEAS_EVENTA5_INTER_FREQ_HO_RSRP];
   /* configure Inter Event A5 */
   a5Cfg->isPres.pres = PRSNT_NODEF;
   a5Cfg->reason = wrSmDfltReason;
   a5Cfg->threshold1_RSRP = wrSmDfltInterA5ThresRSRP1;
   a5Cfg->threshold1_RSRQ = wrSmDfltThresRSRQ1;
   a5Cfg->threshold2_RSRP = wrSmDfltInterA5ThresRSRP2;
   a5Cfg->threshold2_RSRQ = wrSmDfltThresRSRQ2;
   a5Cfg->hysteresis = wrSmDfltHysteresis;
   a5Cfg->timeToTrigger = wrSmDfltTimeToTrig;
   a5Cfg->triggerQty = wrSmDfltTrigQty;
   a5Cfg->reportQty = wrSmDfltRptQty;
   a5Cfg->maxRptCells = wrSmDfltMaxRptCells;
   a5Cfg->reportInterval = wrSmDfltRptInterval;
   a5Cfg->reportAmount = wrSmDfltRptAmount;

   eutraPerd = &measCfg->measEutraPerdRptCfg[WR_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS];
   /* configure Event Periodic */
   eutraPerd->isPres.pres = PRSNT_NODEF;
   eutraPerd->reason = wrSmDfltReason;
   eutraPerd->triggerQty = wrSmDfltTrigQty;
   eutraPerd->reportQty = wrSmDfltRptQty;
   eutraPerd->maxRptCells = wrSmDfltMaxRptCells;
   eutraPerd->reportInterval = wrSmDfltRptInterval;
   eutraPerd->reportAmount = wrSmDfltRptAmount;
   
   /*config for UTRA*/
   /* Below Report Amount parametrs hardcoded because current CSFB design 
    * support for only one measurement report per frequency. 
    * This will be resolved soon*/
   utraPerd = &measCfg->measUtraPerdRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_CSFB];

   utraPerd->reason = wrSmDfltUtraReason;
   utraPerd->maxReportCell= wrSmDfltUtraMaxRptCells;
   utraPerd->reportInterval= wrSmDfltUtraRptInterval;
   utraPerd->reportAmount= 0;

   utraPerd = &measCfg->measUtraPerdRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_ANR];

   utraPerd->reason = wrSmDfltUtraReason;
   utraPerd->maxReportCell= wrSmDfltUtraMaxRptCells;
   utraPerd->reportInterval= wrSmDfltUtraRptInterval;
   utraPerd->reportAmount= 0;

   /* configure 1xCdma Event B1 */
   measCfg->meas1xCDMAEventB1RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->meas1xCDMAEventB1RptCfg[0].reason = wrSmDfltReason;
   measCfg->meas1xCDMAEventB1RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->meas1xCDMAEventB1RptCfg[0].threshold = wrSmDfltCdmaThres1;
   measCfg->meas1xCDMAEventB1RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->meas1xCDMAEventB1RptCfg[0].timeToTrigger = wrSmDfltCdmaTimeToTrig;
   measCfg->meas1xCDMAEventB1RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->meas1xCDMAEventB1RptCfg[0].reportInterval = wrSmDfltCdmaRptInterval;
   measCfg->meas1xCDMAEventB1RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure 1xCdma Event B2 */
   measCfg->meas1xCDMAEventB2RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->meas1xCDMAEventB2RptCfg[0].reason = wrSmDfltReason;
   measCfg->meas1xCDMAEventB2RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->meas1xCDMAEventB2RptCfg[0].threshold1Rsrp = wrSmDfltCdmaThresRSRP1;
   measCfg->meas1xCDMAEventB2RptCfg[0].threshold1Rsrq = wrSmDfltCdmaThresRSRQ1;
   measCfg->meas1xCDMAEventB2RptCfg[0].threshold2 = wrSmDfltCdmaThres1;
   measCfg->meas1xCDMAEventB2RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->meas1xCDMAEventB2RptCfg[0].timeToTrigger = wrSmDfltCdmaTimeToTrig;
   measCfg->meas1xCDMAEventB2RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->meas1xCDMAEventB2RptCfg[0].trigQtyEutra = wrSmDfltTrigQty;
   measCfg->meas1xCDMAEventB2RptCfg[0].reportInterval = wrSmDfltCdmaRptInterval;
   measCfg->meas1xCDMAEventB2RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;


   /* configure Cdma Hrpd Event B1 */
   measCfg->measCDMAHrpdEventB1RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measCDMAHrpdEventB1RptCfg[0].reason = wrSmDfltReason;
   measCfg->measCDMAHrpdEventB1RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->measCDMAHrpdEventB1RptCfg[0].threshold = wrSmDfltCdmaThres1;
   measCfg->measCDMAHrpdEventB1RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->measCDMAHrpdEventB1RptCfg[0].timeToTrigger = wrSmDfltCdmaTimeToTrig;
   measCfg->measCDMAHrpdEventB1RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->measCDMAHrpdEventB1RptCfg[0].reportInterval = wrSmDfltCdmaRptInterval;
   measCfg->measCDMAHrpdEventB1RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure Cdma Hrpd Event B2 */
   measCfg->measCDMAHrpdEventB2RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measCDMAHrpdEventB2RptCfg[0].reason = wrSmDfltReason;
   measCfg->measCDMAHrpdEventB2RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->measCDMAHrpdEventB2RptCfg[0].threshold1Rsrp = wrSmDfltCdmaThresRSRP1;
   measCfg->measCDMAHrpdEventB2RptCfg[0].threshold1Rsrq = wrSmDfltCdmaThresRSRQ1;
   measCfg->measCDMAHrpdEventB2RptCfg[0].threshold2 = wrSmDfltCdmaThres1;
   measCfg->measCDMAHrpdEventB2RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->measCDMAHrpdEventB2RptCfg[0].timeToTrigger = wrSmDfltCdmaTimeToTrig;
   measCfg->measCDMAHrpdEventB2RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->measCDMAHrpdEventB2RptCfg[0].trigQtyEutra = wrSmDfltTrigQty;
   measCfg->measCDMAHrpdEventB2RptCfg[0].reportInterval = wrSmDfltCdmaRptInterval;
   measCfg->measCDMAHrpdEventB2RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure 1xCdma Periodic */
   measCfg->meas1xCDMAPeridRptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->meas1xCDMAPeridRptCfg[0].reason = wrSmDfltReason;
   measCfg->meas1xCDMAPeridRptCfg[0].cellType = wrSmDfltCellType;
   measCfg->meas1xCDMAPeridRptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->meas1xCDMAPeridRptCfg[0].reportInterval = wrSmDfltCdmaRptInterval;
   measCfg->meas1xCDMAPeridRptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure Cdma HRPD Periodic */
   measCfg->measCDMAHrpdPeridRptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measCDMAHrpdPeridRptCfg[0].reason = wrSmDfltReason;
   measCfg->measCDMAHrpdPeridRptCfg[0].cellType = wrSmDfltCellType;
   measCfg->measCDMAHrpdPeridRptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->measCDMAHrpdPeridRptCfg[0].reportInterval = wrSmDfltCdmaRptInterval;
   measCfg->measCDMAHrpdPeridRptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure Speed scaling Factors */
   measCfg->measSpdSclFact.sfUsagePres.pres =  PRSNT_NODEF;
   measCfg->measSpdSclFact.sMeasure = wrSmDfltSMeasure;
   measCfg->measSpdSclFact.timeToTriggerSfMedium = wrSmDfltTimeToTrigSfMedium;
   measCfg->measSpdSclFact.timeToTriggerSfHigh = wrSmDfltTimeToTrigSfHigh;

   /* configure Mobility state Params */
   measCfg->mobStatParams.speedStatPres.pres =  PRSNT_NODEF;
   measCfg->mobStatParams.tEvalulation = wrSmDfltTEvalulation;
   measCfg->mobStatParams.tHystNormal = wrSmDfltTHystNormal;
   measCfg->mobStatParams.nCellChangeMedium = wrSmDfltNCellChangeMedium;
   measCfg->mobStatParams.nCellChangeHigh = wrSmDfltNCellChangeHigh;

   /* configure Quantity params */
   measCfg->qtyCfg.rsrpFltrCoeff = wrSmDfltRsrpFltrCoeff;
   measCfg->qtyCfg.rsrqFltrCoeff = wrSmDfltRsrqFltrCoeff;
   measCfg->qtyCfg.measQtyCDMA2k = wrSmDfltMeasQtyCDMA2k;
   measCfg->qtyCfg.ecnoFltrCoeff = wrSmDfltEcnoFltrCoeff;
   measCfg->qtyCfg.measQtyUtraFdd = (U8)wrSmDfltMeasQtyUtraFdd;
   measCfg->qtyCfg.measQtyUtraTdd = (U8)wrSmDfltMeasQtyUtraTdd;

   /* configure Measurement Gap params */
   measCfg->measGap.gapForANRPres.pres =  PRSNT_NODEF;
   measCfg->measGap.gapPatternForInterFA = wrSmDfltGapPatForInterFA;
   measCfg->measGap.gapPatternForInterRAT = wrSmDfltGapPatForInterRAT;
   measCfg->measGap.gapPatternForANR = wrSmDfltGapPatForANR;

   /* configure PreRegistration HRPD */
   measCfg->preRegHrpd.preRegAllowed = wrSmDfltPreRegAllowed;
   measCfg->preRegHrpd.preRegZoneId = wrSmDfltPreRegZoneId;
   measCfg->preRegHrpd.NumOf2ndPreRegZoneIdList = wrSmDfltNumOf2ndPreRegZoneIdList;
   measCfg->preRegHrpd.secondaryPreRegZoneId1 = wrSmDfltSecondaryPreRegZoneId1;
   measCfg->preRegHrpd.secondaryPreRegZoneId2 = wrSmDfltSecondaryPreRegZoneId2;

   measCfg->anrRptCfg = wrSmDfltAnrRptCfgVal;
   measCfg->hoRptCfg = wrSmDfltHoRptCfgVal;
}

/* Populate the SIB periodicites */

/*
*
*       Fun:   smBuildCellCfg
*
*       Desc:  fill in cellCfg for WR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*/
#ifdef ANSI
PUBLIC S16 smBuildCellCfg
(
 LwrMngmt *lwrMng 
)
#else
PUBLIC S16 smBuildCellCfg(lwrMng)
LwrMngmt lwrMng
#endif
{
   
   LwrCellMibCfgGrp *lwrMib = NULLP;
   LwrCellSib1CfgGrp *sib1 =NULLP;
   LwrCellSib2CfgGrp *sib2 =NULLP;
   LwrCellSib3CfgGrp *sib3 =NULLP;
   LwrCellSib4CfgGrp *sib4 =NULLP;
   LwrProcTimerCfgGrp *tmrCfg = NULLP;
   U8                cfgGrpIndex = 0;
   LwrCellSib6CfgGrp *sib6 = NULLP;
   LwrCellSib9CfgGrp *sib9 = NULLP;      
   /* SPS changes starts */
   LwrCellSchdCfg        *schdCfg = NULLP;
   LwrCellUlSchdCfgGrp   *ulSchdCfgGrp = NULLP;
   LwrCellDlSchdCfgGrp   *dlSchdCfgGrp = NULLP;
   /* SPS changes ends */

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng->t.protoCfg.t.cellCfg.action = WR_ACT_ADD;
   
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.dlCarrierFreq = wrSmDfltServingCellDLCarrierFreq;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.duplexMode = wrSmDfltDuplexMode;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellId = 1; /* this is ownCellID in case of PLD based, this is jst a logical value */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellIndex = wrSmDfltCellIndex;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.physCellId = (U16)wrSmDfltPhysCellId;
#ifdef LTE_ADV
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.sCellDeActTmr.pres = PRSNT_NODEF;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.sCellDeActTmr.val = wrSmDfltSCellDeActTmrVal;
#endif /* LTE_ADV */
   /* CSG_DEV start */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.csgAccessMode = wrSmDfltAccessMode;
   if(wrSmDfltIsSmlCellPciCfgd == TRUE)
   {
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.smallCellCsgPciRange.pciRangeInfoPres = TRUE;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.smallCellCsgPciRange.startPci = wrSmDfltSmallCellStartPci;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.smallCellCsgPciRange.pciRange = wrSmDfltSmallCellPciRange;
   }
   /* CSG_DEV end */


   /*Filling MIB params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType 
                                                          = WR_CELL_CFG_GRP_MIB;
   lwrMib = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.mibCfgGrp);
   
   lwrMib->dlBw = wrSmDfltCellDlBW[0];
   lwrMib->phichCfg.phichDur = wrSmDfltPhichDur;
   lwrMib->phichCfg.phichRes = wrSmDfltPhichRes;
   cfgGrpIndex++;

   /*Filling sib1 params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType 
                                                        = WR_CELL_CFG_GRP_SIB1;
                                                          
   sib1 =&(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib1CfgGrp);

   sib1->freqBandInd = wrSmDfltFreqBandInd;
   sib1->cellAccessInfo.numOfPlmns = wrSmDfltNumPlmn;

   sib1->cellAccessInfo.plmnInfo[0].plmnId.numMncDigits = wrSmDfltNumMncDigits;
   
   sib1->cellAccessInfo.plmnInfo[0].plmnId.mcc[0] = wrSmDfltPlmn1Mcc0;
   sib1->cellAccessInfo.plmnInfo[0].plmnId.mcc[1] = wrSmDfltPlmn1Mcc1;
   sib1->cellAccessInfo.plmnInfo[0].plmnId.mcc[2] = wrSmDfltPlmn1Mcc2;

   sib1->cellAccessInfo.plmnInfo[0].plmnId.mnc[0] = wrSmDfltPlmn1Mnc0;
   sib1->cellAccessInfo.plmnInfo[0].plmnId.mnc[1] = wrSmDfltPlmn1Mnc1;
   sib1->cellAccessInfo.plmnInfo[0].plmnId.mnc[2] = wrSmDfltPlmn1Mnc2;

   sib1->cellAccessInfo.plmnInfo[0].rsrvdFrOperUse =wrSmDfltCellRsrvdForOperUse;
   sib1->cellAccessInfo.tac = wrSmDfltTac;

   sib1->cellAccessInfo.cellId = wrSmDfltCellId; /* read cellId from wr_cfg.txt wrSmDfltCellIdentity */
   /* CSG_DEV start */
   if (WR_ENB_OPEN_ACCESS == wrSmDfltAccessMode)
   {
      sib1->cellAccessInfo.csgIndication = FALSE;
      sib1->cellAccessInfo.csgIdentity.pres = NOTPRSNT;
   }
   else if(WR_ENB_CLOSED_ACCESS == wrSmDfltAccessMode)
   {
      sib1->cellAccessInfo.csgIndication = TRUE;
      wrFillTknU32(&sib1->cellAccessInfo.csgIdentity, wrSmDfltCsgIdVal);
   }
   else /* hybrid access */
   {
      sib1->cellAccessInfo.csgIndication = FALSE;
      wrFillTknU32(&sib1->cellAccessInfo.csgIdentity, wrSmDfltCsgIdVal);
   }
   /* CSG_DEV end */
   sib1->cellAccessInfo.cellBarred = (Bool)wrSmDfltCellBarred;
   sib1->cellAccessInfo.intraFreqReSelection = (Bool)wrSmDfltIntraFreqResel;

   sib1->cellSelectInfo.qRxLevMin = (S8)wrSmDlftqRxLevMin;
   /* Start - Fix for ccpu00123651 */
   wrFillTknU8(&(sib1->cellSelectInfo.qRxLevMinOffset), (U8)wrSmDfltqRxlevminoffset);
   /* End - Fix for ccpu00123651 */

   sib1->pMax = (S8)wrSmDfltPMax;
   
   sib1->siWindowSize = wrSmDfltSiWinSize;
   
   /* ACC-TDD */
#ifdef LTE_TDD
   sib1->tddCfg.specialSubframeCfg = wrSmTddSpecialSubframeConfig;
   sib1->tddCfg.subframeCfg = wrSmTddSubframeConfig;
#else
   // Not used for FDD - zero the configuration just to be safe
   sib1->tddCfg.specialSubframeCfg = 0;
   sib1->tddCfg.subframeCfg = 0;
#endif

   cfgGrpIndex++; 

   /*Filling Sib2 params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType 
                                                        = WR_CELL_CFG_GRP_SIB2;
                                                          
   sib2 =&(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib2CfgGrp);

   sib2->ueTimerConstants.t302 = 9;
   wrFillTknU8(&(sib2->acBarringInfo.pres), wrSmDfltACBarrInfoPres);
   sib2->acBarringInfo.acBarringForEmergency =  wrSmDfltACBarrNormal;

   wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOData.pres), 
                                                       wrSmDfltMOACBarrInfoPres);

   sib2->ulFreqInfo.ulBandwidth = wrSmDfltCellUlBW;
   sib2->ulFreqInfo.eARFCN = wrSmDfltUlEarFcn;
   sib2->ulFreqInfo.addSpectEmission = (U8)wrSmDfltAddSpectEmn;
   
   sib2->acBarringInfo.acBarringForMOData.acBarringAC11 = FALSE;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC12 = FALSE;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC13 = FALSE;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC14 = FALSE;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC15 = FALSE;

   sib2->acBarringInfo.acBarringForMOData.acBarringFactor 
                                                      =wrSmDfltacBarringFactor;
                                                      
   sib2->acBarringInfo.acBarringForMOData.acBarringTime = 
                                                        wrSmDfltacBarringTime;
                                                        
   wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOSignal.pres), 
                                                      wrSmDfltDOACBarrInfoPres);
                                                       
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC11 = FALSE;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC12 = FALSE;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC13 = FALSE;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC14 = FALSE;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC15 = FALSE;

   sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = 
                                                       wrSmDfltacBarringFactor;

   sib2->acBarringInfo.acBarringForMOSignal.acBarringTime = 
                                                         wrSmDfltacBarringTime;
   wrFillTknU8(&(sib2->acBarringVideo.pres),wrSmDfltVDACBarrInfoPres);
   
   sib2->acBarringVideo.acBarringAC11 = wrSmDfltacBarringAC11;

   
   sib2->acBarringVideo.acBarringAC12 = wrSmDfltacBarringAC12;
   sib2->acBarringVideo.acBarringAC13 = wrSmDfltacBarringAC13;
   sib2->acBarringVideo.acBarringAC14 = wrSmDfltacBarringAC14;
   sib2->acBarringVideo.acBarringAC15 = wrSmDfltacBarringAC15;
   sib2->acBarringVideo.acBarringFactor = wrSmDfltacBarringFactor;
   sib2->acBarringVideo.acBarringTime = wrSmDfltacBarringTime;

   wrFillTknU8(&(sib2->acBarringVideo.pres),wrSmDfltVOACBarrInfoPres);
   
   sib2->acBarringVoice.acBarringAC11 = wrSmDfltacBarringAC11;
   sib2->acBarringVoice.acBarringAC12 = wrSmDfltacBarringAC12;
   sib2->acBarringVoice.acBarringAC13 = wrSmDfltacBarringAC13;
   sib2->acBarringVoice.acBarringAC14 = wrSmDfltacBarringAC14;
   sib2->acBarringVoice.acBarringAC15 = wrSmDfltacBarringAC15;
   sib2->acBarringVoice.acBarringFactor = wrSmDfltacBarringFactor;
   sib2->acBarringVoice.acBarringTime = wrSmDfltacBarringTime;

   /*Filling BCCH*/
   sib2->radioResourceCommon.bcchCfgCommon.modPeriodCoeff 
                                                     = (U8)wrSmDfltModPeriodCoeff;
   /*Filling PCCH*/
   sib2->radioResourceCommon.pcchCfgCommon.defaultPagingCycle 
                                                      =wrSmDfltDefaultPagCycle;
   sib2->radioResourceCommon.pcchCfgCommon.nB =wrSmDfltPCCHCfgNB;
   
   /*Filling PDSCH*/

   sib2->radioResourceCommon.pdschCfgCommon.pB = (U8)wrSmDfltPDSCHCfgPB;
   sib2->radioResourceCommon.pdschCfgCommon.referenceSignalPwr = 
                                                        wrSmDfltRefSignalPower;

   /*Filling PRACH*/

   sib2->radioResourceCommon.prachCfgCommon.rootSequenceIndx = 
                                                      wrSmDfltRootSequenceIdx;

   sib2->radioResourceCommon.prachCfgCommon.prachCfgInfo.highSpeedFlag = 
                                                        (Bool)wrSmDfltHighSpeedFlag;

   sib2->radioResourceCommon.prachCfgCommon.prachCfgInfo.prachCfgIdx = 
                                                          (U8)wrSmDfltPrachCfgIdx;
   sib2->radioResourceCommon.prachCfgCommon.prachCfgInfo.prachFreqOffset = 
                                                        (U8)wrSmDfltPrachFreqOffset;
   sib2->radioResourceCommon.prachCfgCommon.prachCfgInfo.zeroCorrelationZoneCfg= 
                                                      (U8)wrSmDfltZeroCorrelZoneCfg;

   /*Filling PUCCH*/

   sib2->radioResourceCommon.pucchCfgCommon.deltaShift 
                                                      =wrSmDfltPUCCHDeltaShift;
   sib2->radioResourceCommon.pucchCfgCommon.n1PucchAn =wrSmDfltNlPUCCHAn;
   sib2->radioResourceCommon.pucchCfgCommon.nCSAN = (U8)wrSmDfltPUCCHnCSAN;
   sib2->radioResourceCommon.pucchCfgCommon.nRBCqi =(U8)wrSmDfltPUCCHnRBCQI;

   /*Filling PUSCH*/

   sib2->radioResourceCommon.puschCfgCommon.puschBasicCfg.enable64QAM 
                                                         = (Bool)wrSmDfltEnable64QAM;
   sib2->radioResourceCommon.puschCfgCommon.puschBasicCfg.hoppingMode =
                                                           wrSmDfltHoppingMode;
   sib2->radioResourceCommon.puschCfgCommon.puschBasicCfg.hoppingOffset= 
                                                      (U8)wrSmDfltPuschHoppingOff;
                                                      
   sib2->radioResourceCommon.puschCfgCommon.puschBasicCfg.nSb = (U8)wrSmDfltNSB;

   /*Filling RACH*/
   
   sib2->radioResourceCommon.rachCfgCommon.maxHARQMsg3 =(U8)wrSmDfltMaxHARQMsg3Tx;
   
   sib2->radioResourceCommon.rachCfgCommon.powerRamping.initRcvdTrgtPwr = 
                                               wrSmDfltPreambleInitRecvdTgtPwr;
                                                  
   sib2->radioResourceCommon.rachCfgCommon.powerRamping.powerRampingstep=
                                                      (U8)wrSmDfltPowerRampingStep;
   
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.groupASize =
                                                (U8)wrSmDflSizeOfRaPreamblesGroupA;
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.numOfRAPreambles=
                                                   (U8)wrSmDfltNumberOfRaPreambles;
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.msgSizeGroupA=
                                                   wrSmDfltMessageSizeGroupA;
                                                      
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.pwrOffstGrpB=
                                              wrSmDfltMessagePowerOffsetGroupB;
    
   sib2->radioResourceCommon.rachCfgCommon.raSupervisionCfg.macContResTimer=
                                                      (U8)wrSmDfltMacContentResTmr;
                                                      
   sib2->radioResourceCommon.rachCfgCommon.raSupervisionCfg.preambleTransMax=
                                                     (U8)wrSmDfltPreambleTransMax;
   sib2->radioResourceCommon.rachCfgCommon.raSupervisionCfg.rarWindowSize=
                                                       (U8)wrSmDfltRaRspWindowSize;

   /*Filling SRC */

   sib2->radioResourceCommon.srsCfgCommon.cSrs =(U8)wrSmDfltSrsBandwidthCfg;
   sib2->radioResourceCommon.srsCfgCommon.simulAckNackSrs=
                                                   (Bool)wrSmDfltAckNackSrsSimTrns;
   sib2->radioResourceCommon.srsCfgCommon.srsMaxUpts =(Bool)wrSmDfltSrsMaxUpPts;
   sib2->radioResourceCommon.srsCfgCommon.subframeCfg =(U8)wrSmDfltSrsSubfrmCfg;


   /*Filling UL Power Control*/
   sib2->radioResourceCommon.ulCyclicPrefix =wrSmDfltUlCyclicPrefixLength;
   sib2->radioResourceCommon.ulPwrCtrlCommon.alpha = wrSmDfltULPwrCtrlAlpha;
   
   sib2->radioResourceCommon.ulPwrCtrlCommon.deltaFLst.deltaPucchFormat1=
                                                   wrSmDfltDeltaFPUCCHFormat1;
                                                   
   sib2->radioResourceCommon.ulPwrCtrlCommon.deltaFLst.deltaPucchFormat1b=
                                                   wrSmDfltDeltaFPUCCHFormat1b;
                                                   
   sib2->radioResourceCommon.ulPwrCtrlCommon.deltaFLst.deltaPucchFormat2=
                                                    wrSmDfltDeltaFPUCCHFormat2;
   sib2->radioResourceCommon.ulPwrCtrlCommon.deltaFLst.deltaPucchFormat2a=
                                                   wrSmDfltDeltaFPUCCHFormat2a;
   sib2->radioResourceCommon.ulPwrCtrlCommon.deltaFLst.deltaPucchFormat2b=
                                                   wrSmDfltDeltaFPUCCHFormat2b;
   sib2->radioResourceCommon.ulPwrCtrlCommon.deltaMsg3 =
                                                   (S8)wrSmDfltUlDeltaPreambleMsg3;
   
   sib2->radioResourceCommon.ulPwrCtrlCommon.pNomialPucch=
                                                       (S8)wrSmDfltP0NominalPUCCH;
   sib2->radioResourceCommon.ulPwrCtrlCommon.pNomialPusch=
                                                       (S8)wrSmDfltP0NominalPUSCH;
   sib2->timeAlignmentCommon = wrSmDfltTaTmrCmn;
   cfgGrpIndex++; 

    /* Configure the SIB3 parameters*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                          WR_CELL_CFG_GRP_SIB3;
   
   sib3 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib3CfgGrp);

    /*Updating the SIB3 parameters*/
   sib3->qHyst                               = wrSmDfltqHyst;
   sib3->speedStateReselPres                 = WR_PRSNT;
   sib3->sfMedium                            = wrSmDfltSfMed;
   sib3->sfHigh                              = wrSmDfltSfHigh;
   /*Updating the mobility state parameters*/
   sib3->mobStateParams.tEvalulation         = wrSmDfltTEval;
   sib3->mobStateParams.tHystNormal          = wrSmDfltTHyst;
   sib3->mobStateParams.nCellChangeMedium    = (U16)wrSmDfltS3nCellChangeMedium;
   sib3->mobStateParams.nCellChangeHigh      = (U16)wrSmDfltS3nCellChangeHigh;

   cfgGrpIndex++; 

   /* Configure the SIB4 parameters*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                          WR_CELL_CFG_GRP_SIB4;
   sib4 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib4CfgGrp);

   /*Updating the CSG Split Info parameters */
   sib4->csgInfo.csgStartPhyCellId           = (U16)wrSmDfltCSGStartPci; 
   sib4->csgInfo.csgPciRangeUsage        = WR_PRSNT;
   sib4->csgInfo.csgPciRange           = (U8)wrSmDfltCSGPciRange;

   cfgGrpIndex++;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CELL_CFG_GRP_TIMER;
   /* Filling Emm (S1/X2) Timer values */
   /* TODO: Do the same for all other timers */
   tmrCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.procTimerCfgGrp);

   tmrCfg->s1SetupTmr                       = wrSmDfltS1SetupTmr;
   tmrCfg->s1UpdateTmr                      = wrSmDfltUpdateTmr;
   tmrCfg->s1RetryCount                     = wrSmDfltS1RtryCntTmr;
   tmrCfg->s1TimeToWait                     = wrSmDfltS1TimeToWait;
   tmrCfg->s1MmeConfigurationTransferTmr    = wrSmDfltS1MmeCfgTrfrTmr;
   tmrCfg->s1ResetTmr                       = wrSmDfltX2ResetRetryTmr; 
   tmrCfg->x2SetupTmr                       = wrSmDfltX2SetupTmr;
   tmrCfg->x2SetTimeToWait                  = wrSmDfltX2SetTimeToWait;
   tmrCfg->x2UpdateTmr                      = wrSmDfltX2UpdateTmr;
   tmrCfg->x2UpdTimeToWait                  = wrSmDfltX2UpdateTimeToWait;
   tmrCfg->x2ResetTmr                       = wrSmDfltS1ResetRetryTmr; 
   tmrCfg->X2ResetRetryCount                = wrSmDfltX2RstRtryCntTmr;
   tmrCfg->X2SetupRetryCount                = wrSmDfltX2SetupRtryCntTmr;
   tmrCfg->x2UpdRetryCount                  = wrSmDfltX2UpdateRetryCount;
   tmrCfg->internalNoWaitRetryTmr           = wrSmDfltIntNoWaitRetryTmr;

   /* Fill RRC Timer Values */
   tmrCfg->rrcConnectionSetupTmr           = wrSmDfltRrcConSetupTmr;
   tmrCfg->rrcConnectionReconfigTmr        = wrSmDfltRrcConReCfgTmr;
   tmrCfg->rrcConnectionReEstablishTmr     = wrSmDfltRrcConReEstTmr;
   tmrCfg->rrcSecurityModeCommandTmr       = wrSmDfltRrcSecModCmdTmr;
   tmrCfg->rrcUeCapabilityEnquiryTmr       = wrSmDfltRrcUeCapEnqTmr;
   tmrCfg->rrcConnectionReleaseTmr         = wrSmDfltRrcConRelTmr;
   tmrCfg->rrcHandoverPreperationTmr       = wrSmDfltRrcHandoverPrepTmr;
   tmrCfg->rrcUeInformationRequestTmr      = wrSmDfltRrcUeInfReqTmr;
   
   tmrCfg->s1InitialContextSetupTmr          = wrSmDflts1InitialContextSetupTmr;
   tmrCfg->s1ErabReleaseIndicationTmr        = wrSmDflts1ErabReleaseIndicationTmr;
   tmrCfg->s1UeContextReleaseTmr             = wrSmDflts1UeContextReleaseTmr;
   tmrCfg->s1PathSwitchTmr                   = wrSmDflts1PathSwitchTmr;
   tmrCfg->s1HandoverPreperationTmr          = wrSmDflts1HandoverPreperationTmr;
   tmrCfg->s1RelocOveallTmr                  = wrSmDflts1RelocOveallTmr;
   /* For wr_cfg.txt the IRAT HO Timers uses same value as cfgd for Intra LTE HO */
   tmrCfg->s1IRatHandoverPreperationTmr      = wrSmDflts1HandoverPreperationTmr;
   tmrCfg->s1IRatRelocOveallTmr              = wrSmDflts1RelocOveallTmr;
   tmrCfg->s1HandoverCancelTmr               = wrSmDflts1HandoverCancelTmr;
   tmrCfg->x2HandoverPreperationTmr          = wrSmDfltx2HandoverPreperationTmr;
   tmrCfg->x2RelocOverallTmr                 = wrSmDfltx2RelocOverallTmr;
   tmrCfg->x2StoreUeContextTmr               = wrSmDfltx2StoreUeContextTmr;
   tmrCfg->x2SnStatusTransferTmr             = wrSmDfltx2SnStatusTransferTmr;
   tmrCfg->internalSubCellChangeTmr          = wrSmDfltinternalSubCellChangeTmr;
   tmrCfg->internalSubCellPdcpControlTmr     = wrSmDfltinternalSubCellPdcpControlTmr;
   tmrCfg->ehrpdOptHoCompleteTmr             = wrSmDfltehrpdOptHoCompleteTmr;
   tmrCfg->intraEnbHoCompleteTmr             = wrSmDfltintraEnbHoCompleteTmr;
   tmrCfg->measurementReportToWaitTmr        = wrSmDfltmeasurementReportToWaitTmr;
   tmrCfg->internalResourceSetupTmr          = wrSmDfltinternalResourceSetupTmr;
   tmrCfg->internalResourceReleaseTmr        = wrSmDfltinternalResourceReleaseTmr;
   tmrCfg->internalSecurityControlTmr        = wrSmDfltinternalSecurityControlTmr;
   tmrCfg->internalRrcDataTransferTmr        = wrSmDfltinternalRrcDataTransferTmr;
   tmrCfg->internalForwardingPathSetupTmr    = wrSmDfltinternalForwardingPathSetupTmr;
   tmrCfg->internalReestablishControlTmr     = wrSmDfltinternalReestablishControlTmr;
   tmrCfg->internalBufferFlushTmr            = wrSmDfltinternalBufferFlushTmr;
   tmrCfg->internalDataTransferStartTmr      = wrSmDfltinternalDataTransferStartTmr;
   tmrCfg->internalDataForwardEndIndTmr      = wrSmDfltinternalDataForwardEndIndTmr;
   tmrCfg->internalReestablishTimeToWaitTmr  = wrSmDfltinternalReestablishTimeToWaitTmr;
   tmrCfg->internalUserInactivityTmr         = wrSmDfltinternalUserInactivityTmr;
   tmrCfg->internalSignalingInactivityTmr    = wrSmDfltinternalSignalingInactivityTmr;
   tmrCfg->internalUnassignedTmr             = wrSmDfltinternalUnassignedTmr;
   tmrCfg->internalNoWaitRetryTmr            = wrSmDfltinternalNoWaitRetryTmr;
   tmrCfg->internalRrcResetTmr               = wrSmDfltinternalRrcResetTmr;
   tmrCfg->internalEnbResetTmr               = wrSmDfltinternalEnbResetTmr;
   tmrCfg->internalSolicitMeasurementTmr     = wrSmDfltinternalSolicitMeasurementTmr;
   tmrCfg->internalRtdInfoReqTmr             = wrSmDfltinternalRtdInfoReqTmr;

   /*Config SIB6 Params*/
   cfgGrpIndex++; 

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                          WR_CELL_CFG_GRP_SIB6;
   
   sib6 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib6CfgGrp);

    /*Updating the SIB3 parameters*/
   sib6->reCfgType                           = wrSmDfltUtraReCfgType;
   sib6->sfUsagePres.pres                    = PRSNT_NODEF;
   sib6->tReselection                        = wrSmDfltReslct;
   sib6->tReselectionSfMedium                = wrSmDfltReslctSfMed;
   sib6->tReselectionSfHigh                  = wrSmDfltReslctSfHigh;

   cfgGrpIndex++; 
    /*Config SIB9 Params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
                                                             WR_CELL_CFG_GRP_SIB9;
   sib9 =
      &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib9CfgGrp);
   /* CSG_DEV */
   cmMemcpy(sib9->henbName, (U8 *)wrSmDfltHenbName, strlen((S8 *)wrSmDfltHenbName));
   sib9->henbName[strlen((S8 *)wrSmDfltHenbName)] = '\0';
  
   cfgGrpIndex++;

   /* Build the SIB Scheduling confuration parameters */
   smBldCellSibSchCfg(lwrMng, cfgGrpIndex);
   cfgGrpIndex++; 
  
   /* Build the RAB config params*/
   smBldCellRabConfigParam(lwrMng,cfgGrpIndex);
   cfgGrpIndex++;

   smBldCellEaidCfg(lwrMng, cfgGrpIndex);
   cfgGrpIndex++; 

   /* Build the Measurement  configuration parameters */
   smBldMeasCellCfg(lwrMng, cfgGrpIndex);
   cfgGrpIndex++; 

   /* Build the ANR confuration parameters */
   smBldCellAnrCfg(lwrMng, cfgGrpIndex); 
   cfgGrpIndex++; 

   /* Fill the RRM config */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
                                                           WR_CELL_CFG_GRP_RRM;
   /* currently Application shall support maximun 16 Active UE's + 20 MO
    * signalling UE, So if Active UE's above greater than 16 shall be intialed
    * to 16.*/
   if(smCfgCb.maxUeSupp >= (WR_SMM_MAX_ACTIVE_UES_PER_CELL+1))
   {
      smCfgCb.maxUeSupp = WR_SMM_MAX_ACTIVE_UES_PER_CELL;
   }
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.rrmCfgGrp.enbCacInfo.maxEnbCallCount = 
                                                             smCfgCb.maxUeSupp;
   cfgGrpIndex++; 

/* LTE_ADV starts */
   /*Fill the LTE Advanced Config*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CELL_CFG_GRP_LTEA;
   cmMemcpy((U8 *)&lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteAdvCfgGrp.lteAdvancedConfig, 
            (U8 *)&smCfgCb.lteAdvancedConfig, sizeof(LwrLteAdvancedConfig));
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteAdvCfgGrp.pres = TRUE;
   cfgGrpIndex++; 
/* LTE_ADV ends */

   /* SPS changes starts */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CELL_CFG_GRP_SCHD;
   schdCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.schdCfgGrp);
   schdCfg->prdEnum = wrSmDfltSrsCfgPrdEnum;
   schdCfg->retxCnt = wrSmDfltRetxCnt;
   WR_GET_PAGING_CYCLE(wrSmDfltDefaultPagCycle, dfltDrxCycle);
   WR_GET_MODIFI_COEFF(wrSmDfltModPeriodCoeff, dfltModPrdCoeff);
   schdCfg->modPrd = dfltModPrdCoeff * dfltDrxCycle;
   schdCfg->pwrCfg.pucchPwrFmt3Rnti = wrSmDfltPucchPwrFmt3RntiSt;
   schdCfg->pwrCfg.pucchPwrFmt3Siz = wrSmDfltPucchPwrFmt3RntiSz;
   schdCfg->pwrCfg.pucchPwrFmt3aRnti = wrSmDfltPucchPwrFmt3aRntiSt;
   schdCfg->pwrCfg.pucchPwrFmt3aSiz = wrSmDfltPucchPwrFmt3aRntiSz;
   schdCfg->pwrCfg.puschPwrFmt3Rnti = wrSmDfltPuschPwrFmt3RntiSt;
   schdCfg->pwrCfg.puschPwrFmt3Siz = wrSmDfltPuschPwrFmt3RntiSz;
   schdCfg->pwrCfg.puschPwrFmt3aRnti = wrSmDfltPuschPwrFmt3aRntiSt;
   schdCfg->pwrCfg.puschPwrFmt3aSiz = wrSmDfltPuschPwrFmt3aRntiSz;
   schdCfg->pwrCfg.pucchPwrFmt3aEnable = wrSmDfltPucchPwrFmt3AEnable; 
   schdCfg->pwrCfg.puschPwrFmt3aEnable = wrSmDfltPuschPwrFmt3AEnable;
   schdCfg->pwrCfg.isUlGrpPwrCntrlPucchEnable = wrSmDfltisUlGrpPwrCntrlPucchEnable;
   schdCfg->pwrCfg.isUlGrpPwrCntrlPuschEnable = wrSmDfltisUlGrpPwrCntrlPuschEnable;
    printf("%s:%d,wrSmDfltisUlGrpPwrCntrlPucchEnable=%ld\n",__FILE__,__LINE__,(U32)wrSmDfltisUlGrpPwrCntrlPucchEnable); 
   schdCfg->preamPres = wrSmDfltPreambleSetCfgPres;
   schdCfg->preamStart = wrSmDfltPreambleSetCfgStart;
   schdCfg->preamSize = wrSmDfltPreambleSetCfgSz;
   schdCfg->rachCfg.preambleFormat = wrSmDfltPreambleFrmt;
   schdCfg->rachCfg.raOccSize = wrSmDfltRaOccSz;
   schdCfg->rachCfg.raOccSfnEnum = wrSmDfltRaOccSfnEnum;
   schdCfg->rachCfg.prachResource = wrSmDfltPrachResource;
   schdCfg->genCfg.macInst = wrSmDfltMacInst;
   schdCfg->genCfg.maxUePerUlSf = wrSmDfltMaxUePerUlSf;
   schdCfg->genCfg.maxUePerDlSf = wrSmDfltMaxUePerDlSf;
   schdCfg->genCfg.maxUlBwPerUe = wrSmDfltMaxUlBwPerUe;
   schdCfg->genCfg.maxDlBwPerUe = wrSmDfltMaxDlBwPerUe;
   schdCfg->genCfg.maxDlRetxBw = wrSmDfltMaxDlRetxBw;
   schdCfg->genCfg.maxDlUeNewTxPerTti = wrSmDfltMaxDlUeNwTxPerTti;
   schdCfg->genCfg.maxUlUeNewTxPerTti = wrSmDfltMaxUlUeNwTxPerTti;
   schdCfg->genCfg.cellModSchm = wrSmDfltCellModSchm;
   schdCfg->spsCfg.bIsSpsEnabled = wrSmDfltIsSpsEnabled;
   if (wrSmDfltIsSpsEnabled == TRUE)
   {
      schdCfg->spsCfg.maxDlSpsUePerTti = wrSmDfltMaxDlSpsUePerTti;
      schdCfg->spsCfg.maxUlSpsUePerTti = wrSmDfltMaxUlSpsUePerTti;
      schdCfg->spsCfg.maxDlBwInRbs = wrSmDfltSpsDlBandwidth;
   }
   schdCfg->isDynCfiEnb = wrSmDfltIsDcfiEnabled;
   cfgGrpIndex++;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CELL_CFG_GRP_ULSCHD;
   ulSchdCfgGrp = &lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.ulSchdCfgGrp;
   ulSchdCfgGrp->ulSchedulingAlg = wrSmDfltUlSchdType;
   ulSchdCfgGrp->maxUePerUlSf = wrSmDfltMaxUePerUlSf;
   ulSchdCfgGrp->maxUlUeNewTxPerTti = wrSmDfltMaxUlUeNwTxPerTti;
   cfgGrpIndex++; 

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CELL_CFG_GRP_DLSCHD;
   dlSchdCfgGrp = &lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.dlSchdCfgGrp;
   dlSchdCfgGrp->dlSchedulingAlg = wrSmDfltDlSchdType;
   dlSchdCfgGrp->maxUePerDlSf = wrSmDfltMaxUePerDlSf;
   dlSchdCfgGrp->maxDlUeNewTxPerTti = wrSmDfltMaxDlUeNwTxPerTti;
   dlSchdCfgGrp->dlfsSchdType = wrSmDfltDLFSSchdTyp;
   cfgGrpIndex++;
   /* SPS changes ends */

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.numOfGrps = cfgGrpIndex;

   RETVALUE(ROK);
}

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
   LwrMngmt  wrMgt;
   LwrGenCfg    *cfg = NULLP;
   Pst       pst;
#ifdef WR_RELAY
   U8 loopCnt = 0;
#endif   
   TRC2(smBuildWrGenCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.genCfg);

   /*----------- Fill General Configuration Parameters ---------*/
#ifdef WR_RELAY
   /* CELL Configuration  */
   cfg->cellCfg.cellId       =  smCfgCb.cellId;
   cfg->cellCfg.modType      =  smCfgCb.modType;
   cfg->cellCfg.duplexMode   =  smCfgCb.duplexMode;
   cfg->cellCfg.maxUeSupp    =  smCfgCb.maxUeSupp;
   cfg->cellCfg.mcc[0].pres  =  smCfgCb.mcc[0].pres;
   cfg->cellCfg.mcc[0].val   =  smCfgCb.mcc[0].val;
   cfg->cellCfg.mcc[1].pres  =  smCfgCb.mcc[1].pres;
   cfg->cellCfg.mcc[1].val   =  smCfgCb.mcc[1].val;
   cfg->cellCfg.mcc[2].pres  =  smCfgCb.mcc[2].pres;
   cfg->cellCfg.mcc[2].val   =  smCfgCb.mcc[2].val;
   cfg->cellCfg.mnc[0].pres  =  smCfgCb.mnc[0].pres;
   /* wr003.102   : CR ID- ccpu00116764-IOT changes*/ 
   cfg->cellCfg.mnc[0].val   =  smCfgCb.mnc[0].val;
   cfg->cellCfg.mnc[1].pres  =  smCfgCb.mnc[1].pres;
   /* wr003.102   : CR ID- ccpu00116764-IOT changes*/ 
   cfg->cellCfg.mnc[1].val   =  smCfgCb.mnc[1].val;
   cfg->cellCfg.mnc[2].pres  =  smCfgCb.mnc[2].pres;
   cfg->cellCfg.mnc[2].val   =  smCfgCb.mnc[2].val;
   cfg->cellCfg.trackAreaCode=  smCfgCb.trackAreaCode;
   cfg->cellCfg.freqBandInd  =  smCfgCb.freqBandInd;
#ifdef LTE_HO_SUPPORT
   cfg->cellCfg.rrmRntiStart = smCfgCb.rrmRntiStart;
   cfg->cellCfg.maxRrmRntis = smCfgCb.maxRrmRntis;
   cfg->cellCfg.rrmPrmblStart = smCfgCb.rrmDedPrmStart;
   cfg->cellCfg.maxRrmPrmbls = smCfgCb.rrmNumDedPrm;
   cfg->cellCfg.macRntiStart = smCfgCb.macRntiStart;
   cfg->cellCfg.maxMacRntis = smCfgCb.maxMacRntis;
   cfg->cellCfg.numOfMacPrm = smCfgCb.numOfMacPrm;
   cfg->cellCfg.rsrpTrshldRange = smCfgCb.rsrpTrshldRange;
#endif
   /* Filling PLMN configuration */
   cfg->cellCfg.noOfBrdCstPlmn = smCfgCb.noOfBrdCstPlmn;
   for (loopCnt = 0; loopCnt < smCfgCb.noOfBrdCstPlmn; loopCnt++)
   {
   /* kworks fix */
      strcpy((S8 *)cfg->cellCfg.plmnId[loopCnt], (S8 *)smCfgCb.plmnId[loopCnt]);
   }
   /* Filling the ENB Type */
   cfg->eNBType = (U8)smCfgCb.eNBType;
   cfg->noOfNghInfo = smCfgCb.noOfNghInfo;
   /*cfg->nghInfo = smCfgCb.nghInfo;*/
   cfg->noOfguGrp = smCfgCb.noOfguGrp;
   /*cfg->guGrpId = smCfgCb.guGrpId;*/

   /* Filling S1 Handover Timers */
   cfg->s1PrepTimerVal = smCfgCb.s1PrepTimerVal;
   cfg->s1OvrAllTimerVal = smCfgCb.s1OvrAllTimerVal;

   /* Filling UE HO Attach Timer */
   cfg->ueHoAttachTimerVal = smCfgCb.ueHoAttachTimerVal;

   /* Filling UE Inactivity Timer */
   cfg->inactvTmrVal = smCfgCb.inactvTmrVal;
   cfg->expiryCnt    = smCfgCb.maxExpires;
   cfg->endMrkTmrVal = smCfgCb.endMrkTmrVal;

   /* Filling Physical Cell Id */
   cfg->cellCfg.physCellId = smCfgCb.pci;


#if 0 /* enb ip address is configured in protoCfg of WR(enbapp). Hence removing it */
   wrCpyCmTptAddr(&cfg->dataAppAddr, &smCfgCb.enbIpAddr);
   if(CM_TPTADDR_IPV4 == cfg->dataAppAddr.type) 
   {
      cfg->dataAppAddr.u.ipv4TptAddr.port       = WR_DFLT_EGTP_PORT;
   }
   else if(CM_TPTADDR_IPV6 == cfg->dataAppAddr.type) 
   {
      cfg->dataAppAddr.u.ipv6TptAddr.port       = WR_DFLT_EGTP_PORT;
   }
#endif
#endif /* end of WR_RELAY */
   
   /* Filling UE Inactivity Timer */
   cfg->inactvTmrVal = smCfgCb.inactvTmrVal;
   cfg->expiryCnt    = smCfgCb.maxExpires;
   cfg->endMrkTmrVal = smCfgCb.endMrkTmrVal;

#ifdef ENB_OVRLOAD
   cfg->eNBOvldParams.critThrldVal = WR_CRIT_THRLD_VAL;
   cfg->eNBOvldParams.majThrldVal  = WR_MAX_THRLD_VAL; 
   cfg->eNBOvldParams.minThrldVal  = WR_MIN_THRLD_VAL;
   cfg->eNBOvldParams.critRcvryVal = WR_CRIT_RCVRY_VAL;
   cfg->eNBOvldParams.majRcvryVal  = WR_MAX_RCVRY_VAL;
   cfg->eNBOvldParams.minRcvryVal  = WR_MIN_RCVRY_VAL;
   cfg->eNBOvldParams.eNBMemCritThresVal= WR_ENB_MEM_CRIT_THRES_VAL;
   cfg->eNBOvldParams.eNBMemMajThresVal = WR_ENB_MEM_MAX_THRES_VAL;
   cfg->eNBOvldParams.eNBMemMinThresVal = WR_ENB_MEM_MIN_THRES_VAL;
   cfg->eNBOvldParams.eNBOvldMonTimerVal= WR_ENB_OVLD_MON_TMR_VAL;
   cfg->eNBOvldParams.eNBOvldMonfreq   = WR_ENB_OVLD_MON_FREQ;
   cfg->eNBOvldParams.maxCntval        = WR_MAX_CNT_VAL;
   cfg->eNBOvldParams.eNbOvrLdFlag     = WR_ENB_OVLD_FLAG;
#endif

   cfg->lmPst.srcProcId = SM_SM_PROC;
   cfg->lmPst.dstProcId = SM_WR_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTWR;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)WRSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;

   cfg->lmPst.srcProcId = SM_SM_PROC;
   cfg->lmPst.dstProcId = SM_WR_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTWR;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)WRSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = smCb.init.region;
   cfg->lmPst.pool   =  WR_POOL;
   cfg->lmPst.selector = (Selector)/*WRSM_WRSMSEL*/1;

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
   wrMgt.hdr.transId             = 0;

   wrMgt.hdr.response.prior      = PRIOR0;
   wrMgt.hdr.response.route      = RTESPEC;
   wrMgt.hdr.response.mem.region = smCb.init.region;
   wrMgt.hdr.response.mem.pool   = WR_POOL;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Gen Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrCtfLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

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
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRCTFSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Ctf LSap Cfg sent");

   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrNhuLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

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
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRNHUSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Nhu LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
   RETVALUE(ROK);
}/* smBuildWrNhuLSapCfg */

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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrRmuLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

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
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRRMUSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "FSM to RRM LSAP Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrPjuLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_PJ_PROC;
   /* Shwetha - adding PDCP's entity Id instead of RLC's for data application's
      lower SAP */
   /* cfg->dstEnt       = ENTKW; */
   cfg->dstEnt       = ENTPJ;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRPJSEL;
   cfg->srcEnt       = ENTPX;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRPJUSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Nhu LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrRgrLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_RG_PROC;
   cfg->dstEnt       = ENTRG;
   cfg->dstInst      = (Inst)SCH_INST_ID;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WRRGSEL;
   cfg->srcEnt       = ENTNX;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRRGRSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Rgr LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrSztLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

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
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRSZTSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Szt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;

   TRC2(smBuildWrCztLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

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
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWRCZTSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Czt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);

   RETVALUE(ROK);
}/* smBuildWrCztLSapCfg */

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
   LwrMngmt    wrMgt;
   LwrLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildWrEgtLSapCfg)

   SM_SET_ZERO(&wrMgt, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(wrMgt.t.cfg.t.lSap);

   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_EG_PROC;
   cfg->dstEnt       = ENTEG;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = WRSM_WREGSEL;
   cfg->srcEnt       = ENTVE;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = smCb.init.region;
   cfg->mem.pool     = WR_POOL;

   cfg->maxBndRetry = WRSM_LWR_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = WRSM_LWR_VAL_10;

   /* Fill Header */
   wrMgt.hdr.msgType             = TCFG;
   wrMgt.hdr.msgLen              = 0;
   wrMgt.hdr.entId.ent           = ENTWR;
   wrMgt.hdr.entId.inst          = SM_INST_ZERO;
   wrMgt.hdr.elmId.elmnt         = STWREGTSAP;
   wrMgt.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Egt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLwrCfgReq(&pst, &wrMgt);
 
   RETVALUE(ROK);
}/* smBuildWrEgtLSapCfg */

#endif  /* EU_DAT_APP  */


/*
 *      FUN:   smBindWrToSztSap
 *
 *      Desc:  Bind WR with SCT LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToSztSap
(
Void
)
#else
PUBLIC S16 smBindWrToSztSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToSztSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_SZ_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRSZTSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for S1AP");
    /* Send the control request to the APP */
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToSztSap */

#ifdef LTE_HO_SUPPORT
/*
 *      FUN:   smBindWrToCztSap
 *
 *      Desc:  Bind WR with SCT LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToCztSap
(
Void
)
#else
PUBLIC S16 smBindWrToCztSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;

   TRC2(smBindWrToCztSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_CZ_SUID;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRCZTSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for X2AP");
    /* Send the control request to the APP */
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToCztSap */
#endif

#ifdef EU_DAT_APP

/*
 *      FUN:   smBindWrToEgtSap
 *
 *      Desc:  Bind WR with EGT LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToEgtSap
(
Void
)
#else
PUBLIC S16 smBindWrToEgtSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToEgtSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_EG_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWREGTSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for EGTP");
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToEgtSap */

#endif /* EU_DAT_APP */

/*
 *      FUN:   smBindWrToNhuSap
 *
 *      Desc:  Bind WR with NHU LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToNhuSap
(
Void
)
#else
PUBLIC S16 smBindWrToNhuSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToNhuSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_NH_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRNHUSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for RRC");
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToNhuSap */

/*
 *      FUN:   smBindWrToCtfSap
 *
 *      Desc:  Bind WR with CTF LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToCtfSap
(
Void
)
#else
PUBLIC S16 smBindWrToCtfSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToCtfSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_YS_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRCTFSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for Ctf");
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToCtfSap */

#ifdef RM_INTF 
/*RRM->FSM sck changes*/
/*
 *      FUN:   smBindWrToRmuSap
 *
 *      Desc:  Bind WR with RMU LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToRmuSap
(
Void
)
#else
PUBLIC S16 smBindWrToRmuSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToRmuSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_RM_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRRMUSAP;
   cntrl.hdr.response.selector   = RMU_SEL_LWLC;
   /* Fill Pst */
   pst.selector  = RMU_SEL_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "FSM Bnd Cntrl Req to wr for RRM");
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToRmuSap */
#endif /*RM_INTF*/

#ifdef EU_DAT_APP

/*
 *      FUN:   smBindWrToPjuSap
 *
 *      Desc:  Bind WR with PJU LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToPjuSap
(
Void
)
#else
PUBLIC S16 smBindWrToPjuSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToPjuSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_PJ_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRPJUSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for RLC/PDCP");
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToNhuSap */

#endif /* EU_DAT_APP */
/*
 *      FUN:   smBindWrToRgrSap
 *
 *      Desc:  Bind WR with RGR LSAP. 
 *
 *      Ret:   Void
 *
 *      Notes: None
 *
 *      File:  wr_sm_wr_cntrl.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindWrToRgrSap
(
Void
)
#else
PUBLIC S16 smBindWrToRgrSap(Void)
#endif /* ANSI */
{
   LwrMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
   
   TRC2(smBindWrToRgrSap)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.t.cntrl.action        = ABND_ENA;
   cntrl.t.cntrl.subAction    = 0;
   cntrl.t.cntrl.u.sapId       = WR_RG_SUID; 

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRRGRSAP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "RRM Bnd Cntrl Req to wr for SCH");
    /* Send the control request to the WR*/
   (Void)SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ret);
} /* smBindWrToRgrSap */


/*
*
*       Fun:   smBuildWrErabRelIndCntrl
*
*       Desc:  Invoked to build and send the eNodeB RAB Release
               Indication message from eNodeB.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrErabRelIndCntrl 
(
)
#else
PUBLIC S16 smBuildWrErabRelIndCntrl(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;
   
   TRC2(smBuildWrErabRelIndCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));


   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRSNDERABRELIND;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "Control Req to send ERAB Release Indication");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
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
   LwrMngmt cntrl;
   Pst      pst;
   
   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrGenCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.t.cntrl.action        =  AENA;
   cntrl.t.cntrl.u.sapId       =  0;
   cntrl.t.cntrl.subAction     =  SAUSTA;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRGEN;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Gen Cntrl Req to wr sent");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrGenCntrl */

/*
*
*       Fun:   smBuildWrCellCntrl
*
*       Desc:  Invoked to intimate the APP that Binding is DONE
*              and initiate cell control
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
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
   LwrMngmt cntrl;
   Pst      pst;
   
   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrCellCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRCELLCFG;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Cell Cntrl Req to wr");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
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
   LwrMngmt cntrl;
   Pst      pst;
  U8  noOfCfg=0; 
   
   TRC2(smBuildWrS1InitCntrl)

#if (defined(WR_PERF_MEAS) || defined(WR_WITHOUT_CNE))
   smBuildWrCellCntrl();
   RETVALUE(ROK);
#endif


   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRS1CONSETUP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   for ( noOfCfg=0; noOfCfg<smCfgCb.noOfCfg; noOfCfg++)
   {
     cntrl.t.cntrl.peerId[noOfCfg] = smCfgCb.mmeCfg[noOfCfg]->mmeId;
     cntrl.t.cntrl.idLst[noOfCfg] = smCfgCb.mmeCfg[noOfCfg]->mmeId;
   }
     cntrl.t.cntrl.numConn = noOfCfg;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for S1 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 wrSmDynInitS1Setup
(
)
#else
PUBLIC S16 wrSmDynInitS1Setup(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;
   
   TRC2(wrSmDynInitS1Setup)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRS1CONSETUP;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   cntrl.t.cntrl.numConn = 1;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for S1 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildWrX2InitCntrl
(
)
#else
PUBLIC S16 smBuildWrX2InitCntrl(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;
   U8       noOfCfg = 0;
   U32      noOfConn = 0;
   U32      idx = 0;
   U32      lstCnt = 0;
   Bool     newConn = TRUE;
   
   TRC2(smBuildWrX2InitCntrl)


   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRX2CONSETUP;
   cntrl.hdr.response.selector  = SM_SELECTOR_TC;

   noOfConn = (U8)smUtlGetNumNghEnbCfg();

   for (noOfCfg = 0; noOfCfg < smCfgCb.noOfNghCfg; noOfCfg++)
   {
      /* check if the peerId is already added to the list
       * this can happen if 2 cells from same NGH ENB are configured */
      for(idx = 0; idx < noOfCfg; idx++)
      {
         if(smCfgCb.wrNghCellCfg[noOfCfg]->peerId == cntrl.t.cntrl.idLst[idx])
         {
            newConn = FALSE;
            break;
         }
      }
      if(newConn == TRUE)
      {
         cntrl.t.cntrl.idLst[lstCnt] = smCfgCb.wrNghCellCfg[noOfCfg]->peerId;
         lstCnt++;
      }
      else
      {
         newConn = TRUE;
      }
   }
   cntrl.t.cntrl.numConn = noOfConn;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for X2 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 wrSmDynInitX2Setup
(
)
#else
PUBLIC S16 wrSmDynInitX2Setup(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;
   
   TRC2(wrSmDynInitX2Setup)


   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRX2CONSETUP;
   cntrl.hdr.response.selector  = SM_SELECTOR_TC;

   cntrl.t.cntrl.numConn = 1;
   
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Cntrl Req to wr for X2 Init");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

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
   LwrMngmt cntrl;
   Pst      pst;
   
   TRC2(smBuildWrDbgCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRGEN;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   cntrl.t.cntrl.action        =  AENA;
   cntrl.t.cntrl.subAction     =  SADBG;

   /* wr003.102: Fix for CRId- 115717 */

   cntrl.hdr.response.selector   = SM_SELECTOR_TC;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "RRM Debug Cntrl Req to wr");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrInitCntrl */

/* IPSec Recovery */


/*
*
*       Fun:   smBuildWrShutDownCntrl
*
*       Desc:  Invoked to shut down the APP.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_wr_cntrl.c
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
   LwrMngmt cntrl;
   Pst      pst;
   
   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildWrShutDownCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.t.cntrl.action        =  ASHUTDOWN;
  /* cntrl.t.cntrl.u.sapId       =  0; */ /* Needed ? */
   cntrl.t.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRGEN;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   RLOG0(L_DEBUG, "APP Shutdown Cntrl Req to wr sent");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildWrGenCntrl */


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
*       Notes:  None
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
#ifdef LCWRMILWR
      case EVTLWRCFGCFM:             /* Config confirm */
         ret = cmUnpkLwrCfgCfm(SmMiLwrCfgCfm, pst, mBuf);
         break;
      case EVTLWRCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLwrCntrlCfm(SmMiLwrCntrlCfm, pst, mBuf);
         break;
      case EVTLWRSTAIND:
         ret = cmUnpkLwrStaInd(SmMiLwrStaInd, pst,mBuf);
         break;
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
     
         smWrProcSm(pst->event);
         (Void)SPutMsg(mBuf);
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
PRIVATE U32 wrWrCfg = 0;


#define  MAXWRMI  2
#if(!defined(LCSMMILWR) || !defined(WR))
#define PTSMMILWR
#endif

#ifdef PTSMMILWR
PRIVATE S16 PtMiLwrCfgReq    (Pst *pst, LwrMngmt *cfg);
PRIVATE S16 PtMiLwrCntrlReq  (Pst *pst, LwrMngmt *cntrl);
PRIVATE S16 PtMiLwrLoadInd (Pst *spst, LwrLoadIndInfo *loadIndInfo);
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
 
PRIVATE LwrCfgReq SmMiLwrCfgReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCfgReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef WR
   WrMiLwrCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCfgReq,          /* 1 - tightly coupled, portable */
#endif
};


/* Control request primitiwr */
 
PRIVATE LwrCntrlReq SmMiLwrCntrlReqMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrCntrlReq,          /* 0 - loosely coupled  */
#else
   PtMiLwrCntrlReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef WR
   WrMiLwrCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCntrlReq,          /* 1 - tightly coupled, portable */
#endif
};

PRIVATE LwrCfgCfm SmMiLwrAddNeighCfmMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrAddNeighCfm,          /* 0 - loosely coupled  */
#else
   PtMiLwrAddNeighCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef WR
   WrMiLwrAddNeighCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrAddNeighCfm,          /* 1 - tightly coupled, portable */
#endif
}; 

PRIVATE LwrLoadInd SmMiLwrLoadIndMt[MAXWRMI] =
{
#ifdef LCSMMILWR
   cmPkLwrLoadInd,          /* 0 - loosely coupled  */
#else
   PtMiLwrLoadInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef WR
   WrMiLwrLoadInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrLoadInd,          /* 1 - tightly coupled, portable */
#endif
}; 

/*
*     layer management interface functions 
*/
 
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

#ifdef PTSMMILWR

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

#endif /* PTSMWRMILHI */

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
*       File:  wr_sm_wr_ptmi.c
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
   PRIVATE U8 proCfgCount = 0;
   
   TRC2(SmMiLwrCfgCfm);

   SM_SET_ZERO(&wrPst, sizeof(Pst));

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STWRGEN:
            wrWrCfg |= WR_WR_GEN_CFG;
            break;      
#ifdef WR_RELAY
         case STWRCTFSAP:
            wrWrCfg |= WR_WR_CTF_CFG;
            break;
         case STWRNHUSAP:
            wrWrCfg |= WR_WR_NHU_CFG;
            break;
         case STWRRGRSAP:
            wrWrCfg |= WR_WR_RGR_CFG;
            break;
         case STWRSZTSAP:
            wrWrCfg |= WR_WR_SZT_CFG;
            break;
#ifdef LTE_HO_SUPPORT
         case STWRCZTSAP:
            wrWrCfg |= WR_WR_CZT_CFG;
            break;
         case STWRNGH:
#if 0
#else
            wrWrCfg |= WR_WR_NHCFG_CFG;
#endif
            break;
         case STWRMME:
            wrWrCfg |= WR_WR_MME_CFG;
            break;
#endif            
#endif /* WR_RELAY */
#ifdef RM_INTF
         case STWRRMUSAP:
            wrWrCfg |= WR_WR_RMU_SAP_CFG; /*RRM->FSM sck changes*/
            break;
#endif /*RM_INTF*/
#ifdef EU_DAT_APP
         case STWRPJUSAP:
            wrWrCfg |= WR_WR_PJU_CFG;
            break;
         case STWREGTSAP:
            wrWrCfg |= WR_WR_EGT_CFG;
            break;
         case STWRPROTOCFG:
            proCfgCount ++;
            if( proCfgCount == LWR_MAX_PROTOCOL_CFG_COUNT)
            {
               wrWrCfg |= STWRPROTOCFG; 
            }
         break;
#endif /* EU_DAT_APP  */
         default:
            break;
      } /* end of switch statement */
      RLOG1(L_DEBUG, "APP Cfg Cfm received for the element %d",
         cfm->hdr.elmId.elmnt);
      if(smCb.smState == WR_SM_STATE_CELL_UP)
      {
         if(cfm->t.protoCfg.type == WR_CFG_TYPE_NEIGH_CELL)
         {
            RLOG0(L_DEBUG, "Dynamic Neighbor Cell add completed.");
         }
         RETVALUE(ROK);
      }

      if (wrWrCfg == WR_SM_WR_CONFIGURED)
      {
         smCb.smState = WR_SM_STATE_APP_CFG_DONE;
         WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWRRRCCFG, WR_POOL, SM_SELECTOR_TC);

         if(wrSmSelfPstMsg(&wrPst) != ROK)
         {
            RLOG0(L_FATAL, "APP CONFIGURATION NOT SUCCESSFULLY PERFORMED. "
               "Failure at Self Pst.");
         }
         else
         {
            RLOG0(L_DEBUG, "APP CONFIGURATION SUCCESSFULLY PERFORMED.");
         } /* end of else part */

      }  /* end of wrWrCfg == WR_SM_WR_CONFIGURED */
   } /* end of if statement cfm->cfm.status == LCM_PRIM_OK */
   else
   {
      RLOG0(L_ERROR, "Configuration Confirm received with Not OK.");
   }

   RETVALUE(ROK);
} /* end of SmMiLwrCfgCfm */

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
          WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWRRRCSHUT, WR_POOL, SM_SELECTOR_TC);

          if(wrSmSelfPstMsg(&wrPst) != ROK)
            {
               RLOG0(L_ERROR, "APP SHUTDOWN NOT SUCCESSFULLY PERFORMED. "
                   "Failure at Self Pst.");
            }
           else
            {
               RLOG0(L_DEBUG, "APP SHUTDOWN SUCCESSFULLY PERFORMED. ");
            } /* end of else part */
         }
      }  /* end of LCM_PRIM_OK_NDONE */


/*IPSec*/

#ifdef WR_RELAY
   if(cntrl->hdr.elmId.elmnt == STWRCTFSAP)
   {
      RLOG0(L_INFO, "BIND OF APP with CL(CTF) IS IN PROGRESS.");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRCTFSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRSZTSAP)
   {
      RLOG0(L_INFO, "Bind of RRM Tsap with S1AP is in progress.");
   }
#ifdef RM_INTF
   else if(cntrl->hdr.elmId.elmnt == STWRRMUSAP) /*RRM->FSM sck changes*/
   {
      RLOG0(L_INFO, "Bind of FSM Tsap with RRM is in progress.");
   }
#endif /*RM_INTF*/
#ifdef LTE_HO_SUPPORT
   else if(cntrl->hdr.elmId.elmnt == STWRCZTSAP)
   {
      RLOG0(L_INFO,"Bind of RRM Tsap with X2AP is in progress.");
   }
#endif
   else if(cntrl->hdr.elmId.elmnt == STWRNHUSAP)
   {
      RLOG0(L_INFO,"Bind of RRM with RRC (NHU) is in progress.");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRNHUSAP */
   else if(cntrl->hdr.elmId.elmnt == STWRRGRSAP)
   {
      RLOG0(L_INFO,"Bind of RRM TSap with MAC is in progress.");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRRGRSAP */
   else if (cntrl->hdr.elmId.elmnt == STWRGEN)
   {

      RLOG0(L_DEBUG,"Enabling Alarms of App is done.");
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
      RLOG0(L_DEBUG,"Received Control Confirm for S1 Setup.");
         /* smBuildWrCellCntrl();  */

   } /* end of else part */
#ifdef LTE_HO_SUPPORT
   else if( cntrl->hdr.elmId.elmnt == STWRX2CONSETUP)
   {
      RLOG0(L_DEBUG,"Received Control Confirm for X2 Setup.");

   } /* end of else part */
#endif
   else if( cntrl->hdr.elmId.elmnt == STWRCELLCFG)
   {
      RLOG0(L_DEBUG,"Received Control Confirm for CELL CFG .");
   } /* end of else part */
#endif  /* WR_RELAY */
#ifdef EU_DAT_APP
   else if(cntrl->hdr.elmId.elmnt == STWRPJUSAP)
   {
      RLOG0(L_INFO, "Bind of RRM with RLC (PJU) is in progress.");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWREGTSAP */
   else if(cntrl->hdr.elmId.elmnt == STWREGTSAP)
   {
      RLOG0(L_INFO, "Bind of RRM to EGTP is in progress");
   } /* end of if statement cntrl->hdr.elmId.elmnt == STWRPJUSAP */
#endif /* end of EU_DAT_APP */
   RETVALUE(ROK);
} /* end of SmMiLwrCntrlCfm() */


/*
 *
 *       Fun:    SmMiLwrAddNeighCfgReq - Neighbor Config Request
 *
 *       Desc:   Process the Neighbor Config Request
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
PUBLIC S16 SmMiLwrAddNeighCfgReq
(
Pst          *pst,
LwrMngmt     *cfgReq
)
#else
PUBLIC S16 SmMiLwrAddNeighCfgReq(pst, cfgReq)
Pst          *pst;
LwrMngmt     *cfgReq;
#endif /* ANSI */
{
   U8                         idx = 0;
   U8                         dbIdx = 0;
   LwrNghCellCfg             *nghCellCfg;

   TRC2(SmMiLwrAddNeighCfgReq)

   WR_ALLOC(&nghCellCfg, sizeof(LwrNghCellCfg));
   if(nghCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   nghCellCfg->enbId = cfgReq->t.nbrAddReq.enbId;
   wrCpyCmTptAddr(&nghCellCfg->enbAddr, &cfgReq->t.nbrAddReq.nbIpAddress);
   wrCpyCmTptAddr(&nghCellCfg->ipAddr, &cfgReq->t.nbrAddReq.nbIpAddress);
   WR_GET_PEERID_FROM_ENBID(nghCellCfg->enbId, nghCellCfg->peerId);
   if(WR_SMM_INVALID_PEERID == nghCellCfg->peerId)
   {
      RLOG0(L_ERROR, "Failed to get PeerId from wrX2apPeerIdLst List");
      WR_FREE(nghCellCfg, sizeof(LwrNghCellCfg));
      RETVALUE(RFAILED);
   }
   /* check if this neighbor info is already present in smCfgCb list */
   for(idx=0; idx<WR_SMM_MAX_NBR_ENB; idx++)
   {
      if(NULLP != smCfgCb.wrNghCellCfg[idx])
      {
         if(nghCellCfg->enbId == smCfgCb.wrNghCellCfg[idx]->enbId)
         {
            dbIdx = idx;
            /*ccpu00127802*/
            RLOG0(L_WARNING, "Neighbor already present in neighbor list");
            WR_FREE(nghCellCfg, sizeof(LwrNghCellCfg));
            break;
         }
      }
      else if(NULLP == smCfgCb.wrNghCellCfg[idx])
      {
         dbIdx = idx;
         smCfgCb.wrNghCellCfg[idx] = nghCellCfg;
         smCfgCb.noOfNghCfg++;
         break;
      }
   }

   if(cfgReq != NULLP)
   {
      WR_FREE(cfgReq, sizeof(LwrMngmt));
   }
   if(idx == WR_SMM_MAX_NBR_ENB)
   {
      WR_FREE(nghCellCfg, sizeof(LwrNghCellCfg));
      RETVALUE(RFAILED);
   }
   else
   {
      RLOG1(L_INFO, "smCb.smState before adding dynamic Nbr Enodeb is =%d",
         smCb.smState);
      smCb.smState = WR_SM_STATE_DYN_X2AP_CFG_DONE;
      smBuildDynCzPeerCfg(idx +1,dbIdx);
   }
   RETVALUE(ROK);
} /* end of SmMiLwrAddNeighCfgReq() */


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
 *       File:   wr_sm_wr_ptmi.c
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
   Pst  wrPst;
   LwrUstaDgn *dgn;

   /* wr002.102: Added trace macro */
   TRC2(SmMiLwrStaInd)

   SM_SET_ZERO(&wrPst, sizeof(Pst));

   dgn = &(usta->t.usta.dgn);
    if (usta->t.usta.alarm.event == LWR_EVENT_CELL_RECFG_SUCCESS)
    {    
       if(smCb.smState == WR_SM_STATE_REBOOT_REQUIRED)
       {
          RLOG0(L_DEBUG, "SENDING STOP REQUEST to CL ");
          smBuildWrstopPHYCntrl();
       }
       RETVALUE(ROK);
    }
         
    if (usta->t.usta.alarm.event == LWR_EVENT_PHY_STOP_SUCCESS)
    {
       RLOG0(L_ALWAYS, "SENDING SHUTDOWN REQUEST to ALL LAYERS");
       smCb.cellState = FALSE; /* We reached here means cell has been brought down successfully*/
       smCb.smState = WR_SM_STATE_DINIT;
        /*smCb.smState = WR_SM_STATE_RRM_SHUTDWN_DONE;*/
        WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR,EVTWRRRMSHUT, WR_POOL, SM_SELECTOR_LWLC);
        if(wrSmSelfPstMsg(&wrPst) != ROK)
        {
           RLOG1(L_ERROR, "Failure at Self Pst. %d", smCb.smState);
        }

    } 
   if ( usta->t.usta.alarm.event == LWR_EVENT_S1CON_SET_SUCCESS)
   {
      /*Added for avoiding second time cell configuration if mme come up
        after forcefully terminating*/
      if( smCb.cellState == FALSE)
      {
         smBuildWrCellCntrl();
      }
   } 
   if ((usta->t.usta.alarm.event == LWR_EVENT_CELL_CFG_SUCCESS)
         && smCb.smState == WR_SM_STATE_AWAIT_CELL_UP)
   {
      smCb.smState = WR_SM_STATE_CELL_UP;
      /*Added for avoiding second time cell configuration*/
      smCb.cellState = TRUE;
      /*ccpu00127802*/
      RLOG0(L_ALWAYS, "CELL CONFIGURATION SUCCESSFULLY PERFORMED.");
#ifdef CNE_UE_SIM_TEST
      /* eNodeB_Ue_Sim: Send the S1 Setup Now. */
      WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_TC);
      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
         RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
      }
#else
      /* eNodeB_Ue_Sim: Send the X2 Setup Now. */
      WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWRINITX2SETUP, WR_POOL, SM_SELECTOR_TC);
      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
         RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
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
                  RLOG1(L_INFO, "BIND OF RRM S1AP IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
                  if (smCb.smState == WR_SM_STATE_ENB_ALRMS_DONE)
                  {
                     smCb.smState = WR_SM_STATE_S1AP_STK_BND_DONE;
                     RLOG0(L_DEBUG, "BIND OF S1AP STACK SUCCESSFUL");
                     /* Perform the bind of APP and SCTP */
                     WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWREGTPSTKBND, WR_POOL, SM_SELECTOR_TC);
                     if(wrSmSelfPstMsg(&wrPst) != ROK)
                     {
                        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                     }
                  }
                  break;
               }
            case LWR_CAUSE_EGT_SAP_BOUND:
               {
                  RLOG1(L_INFO, "BIND OF RRM TO EGTP IS SUCCESSFUL SAPID= %d",
                     dgn->u.sapId);
                  if (smCb.smState == WR_SM_STATE_S1AP_STK_BND_DONE)
                  {
                     smCb.smState = WR_SM_STATE_EGTP_STK_BND_DONE;
                     RLOG0(L_DEBUG, "BIND OF EGTP STACK SUCCESSFUL");
#ifdef LTE_HO_SUPPORT
                     /* Perform the bind of APP and SCTP */
                     WR_FILL_PST(wrPst, SM_WR_PROC,ENTSM, ENTWR, EVTWRX2APSTKBND, WR_POOL, SM_SELECTOR_TC);
#else
                     /* Perform the bind of APP and SCTP */
                     WR_FILL_PST(wrPst, SM_WR_PROC,ENTSM, ENTWR, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_TC);
#endif
                     if(wrSmSelfPstMsg(&wrPst) != ROK)
                     {
                        RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                     }
                  }
                  break;
               }

#ifdef LTE_HO_SUPPORT
            case LWR_CAUSE_CZT_SAP_BOUND:
               {
                  RLOG1(L_INFO, "BIND OF RRM TO X2AP IS SUCCESSFUL SAPID= %d",
                     dgn->u.sapId);
                  if (smCb.smState == WR_SM_STATE_EGTP_STK_BND_DONE)
                  {
                     smCb.smState = WR_SM_STATE_X2AP_STK_BND_DONE;
                     RLOG0(L_DEBUG, "BIND OF X2AP STACK SUCCESSFUL ");
                     /* Perform the bind of APP and SCTP */
                     WR_FILL_PST(wrPst, SM_WR_PROC,ENTSM, ENTWR, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_TC);

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
                  RLOG1(L_INFO, "BIND OF APP CTF IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
                  /* Initiate Bind Request towards NHU Sap  */
                  smBindWrToNhuSap();
                  break;
               }
            case LWR_CAUSE_NHU_SAP_BOUND:
               {
                  RLOG1(L_INFO, "BIND OF APP NHU IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
                  /* Initiate Bind Request towards PJU Sap  */
                  smBindWrToPjuSap();
                  break;
               }
            case LWR_CAUSE_PJU_SAP_BOUND: 
               {
                  RLOG1(L_INFO, "BIND OF APP PJU IS SUCCESSFUL sapId = %d",
                        dgn->u.sapId);
                  /* Initiate Bind Request towards PJU Sap  */
#ifdef RM_INTF        /*RRM->FSM sck changes*/
               smBindWrToRmuSap();
#else
               smBindWrToRgrSap();
#endif /*RM_INTF*/
               break;
            }
#ifdef RM_INTF /*RRM->FSM sck changes*/
            case LWR_CAUSE_RMU_SAP_BOUND: 
               {
                  RLOG1(L_INFO, "BIND OF RMU SAP IS SUCCESSFUL sapId = %d",
                        dgn->u.sapId);
                  /* Initiate Bind Request towards Rmu Sap  */
                  smBindWrToRgrSap();
                  break;
               }
#endif /*RM_INTF*/
            case LWR_CAUSE_RGR_SAP_BOUND:
               {
                  RLOG1(L_INFO, "BIND OF APP RGR IS SUCCESSFUL sapId = %d",
                     dgn->u.sapId);
#ifdef LTE_ENB_PERF
                  smCb.smState = WR_SM_STATE_EGTP_STK_BND_DONE;
#endif

#ifdef LTE_HO_SUPPORT
                  if (smCb.smState == WR_SM_STATE_X2AP_STK_BND_DONE)
#else
                     if (smCb.smState == WR_SM_STATE_EGTP_STK_BND_DONE)
#endif
                     {
                        smCb.smState = WR_SM_STATE_RRC_STK_BND_DONE;

                        RLOG0(L_DEBUG, "BIND OF RRC STACK IS SUCCESSFUL");
                        /* Perform the bind of APP and SCTP */
#ifdef RM_INTF
                        WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWRRRMSTKBND, WR_POOL, SM_SELECTOR_TC);
#else
                        WR_FILL_PST(wrPst, SM_WR_PROC, ENTSM, ENTWR, EVTWRINITS1SETUP, WR_POOL, SM_SELECTOR_TC);
#endif
                        if(wrSmSelfPstMsg(&wrPst) != ROK)
                        {
                           RLOG1(L_FATAL, "Failure at Self Pst. %d", smCb.smState);
                        }
                     }
                  break;
               }
            default:
               {
                  RLOG1(L_ERROR, "Invalid alarm. %d", usta->t.usta.alarm.cause);
                  break;
               }
         }
      }
      else if (usta->t.usta.alarm.event == LCM_EVENT_BND_FAIL) 
      {
         RLOG2(L_ERROR, "BIND OF APP lsap id[%d] FAILED Cause %d", dgn->u.sapId,
            usta->t.usta.alarm.cause);
      }
   }
   else if (usta->t.usta.alarm.category == LCM_CATEGORY_LYR_SPECIFIC)
   {
      switch(usta->t.usta.alarm.event)
      {
         case LWR_EVENT_ENB_CFGUPD_SUCCESS:
            RLOG0(L_DEBUG, "ENB Config Update Successfully Complete");
            /* TODO : Send indication to OAM */
            break;
         case LWR_EVENT_ENB_CFGUPD_FAIL:
            RLOG1(L_ERROR, "ENB Config Update Failed with Cause %d",
               usta->t.usta.alarm.cause);
            /* TODO : Send indication to OAM */
            break;
      }
   }

   else if (usta->t.usta.alarm.category == LCM_CATEGORY_PROTOCOL)
   {
      /*Fix for ccpu00126143: Handling Alram raised when X2 setup Req fails*/
      if((usta->t.usta.alarm.cause == LWR_EVENT_CELL_UNAVAILABLE) &&
               (usta->t.usta.alarm.event == LWR_EVENT_ERRIND_FROM_PEER))
      {
         /* Raise a Alram towards OAM when support is available */
         RLOG0(L_ERROR, "X2-Setup Request Failed because of mismatch in enodeb ID");
      }

   }

   /*Free the memory which is allocated for status Indication */
 /*   WR_FREE(usta, sizeof(LwrMngmt)); */ 

   RETVALUE(ROK);
} /* end of SmMiLwrStaInd() */

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

   (*SmMiLwrLoadIndMt[spst->selector])(spst, loadIndInfo);

   RETVALUE(ROK);
} /* end of SmMiLwrLoadInd() */

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
)
#else
PUBLIC S16 smBuildWrPartRstCntrl(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;

   TRC2(smBuildWrPartRstCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRSNDPARTS1RST;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Control Request to send Partial RESET");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
)
#else
PUBLIC S16 smBuildWrFullRstCntrl(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;

   TRC2(smBuildWrFullRstCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRSNDFULLS1RST;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Control Request to send Full Reset");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
)
#else
PUBLIC S16 smBuildNghRstCntrl(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;

   TRC2(smBuildNghRstCntrl)

   SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRTRIGX2RST;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Control Request to send X2-Reset");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
 *       Notes: None
 *
 *       File: wr_sm_enbapp.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildAnrPrintCntrl
(
)
#else
PUBLIC S16 smBuildAnrPrintCntrl(Void)
#endif
{
   LwrMngmt cntrl;
   Pst      pst;

   TRC2(smBuildAnrPrintCntrl)

      SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STWRANRPRINTCELL;


   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   RLOG0(L_DEBUG, "Control Request to print neighbour cell Info in ANR");

   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

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
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrCellSib2CfgGrp *sib2 =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic cell id */
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib2 params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB2;
   sib2 =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib2CfgGrp);
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
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
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
   if ((configInfo->feature & RGR_ABS) == RGR_ABS) {
       lteAdvGroup->lteAdvancedConfig.absCfg.status = configInfo->flag;
   }

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
   LwrLteAdvancedConfig *lteAdvGroup =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic cell id */
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
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
            RLOG1(L_ERROR, "Wrong Load type :%d", choice);
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
*       File:     wr_sm_wr_ptmi.c
*
*/
#ifdef PTSMMILWR  
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
#endif

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

/*************************************** SIB Modification changes ********************/
#ifdef ANSI
PUBLIC S16 smBuildDynWrNehCellCfg
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildDynWrNehCellCfg(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrEUTRANeighCell *eutraNeghCell = NULLP;
   U32 idx; 
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1;
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = 2;

   for(idx = 0; idx < lwrMng->t.protoCfg.t.neighCellCfg.numCells; idx++)
   {
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type = WR_NEIGH_CELL_EUTRA;
      eutraNeghCell = &(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].t.eutraCell);
      eutraNeghCell->cellNum = 3;
      eutraNeghCell->nrIndex = 2;
      eutraNeghCell->enbId = 36103 + idx;

      eutraNeghCell->cio = wrSmDfltCIO;
      eutraNeghCell->enbPlmn.numMncDigits = 2;
      eutraNeghCell->enbPlmn.mcc[0] = 4;
      eutraNeghCell->enbPlmn.mcc[1] = 5;
      eutraNeghCell->enbPlmn.mcc[2] = 0;

      eutraNeghCell->enbPlmn.mnc[0] = 0;
      eutraNeghCell->enbPlmn.mnc[1] = 5;
      eutraNeghCell->enbPlmn.mnc[2] = -1;

      eutraNeghCell->enbType = wrSmDfltNeighEnbType;
      eutraNeghCell->numPlmn = wrSmDfltNeighCellNoPlmn;

      /* kworks fix */
      eutraNeghCell->pci = (U16)(142 + idx);
      eutraNeghCell->tac = 1;

      eutraNeghCell->qoffset = wrSmDfltQoff;

      eutraNeghCell->dlBw = wrSmDfltCellDlBW[0];
      eutraNeghCell->earfcnDl = 2500;
      eutraNeghCell->earfcnUl= 20500;

      eutraNeghCell++;
   }   
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 smSndDynWrNhCellCfg
(
void
)
#else
PUBLIC S16 smSndDynWrNhCellCfg()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildDynWrNehCellCfg(&lwrMng);
   
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
}

PRIVATE S16 smClearSmCfg
(
U16                          pci
)
{
   U16                       indx;
   U16                       indx1;

   for(indx = 0; indx < WR_X2AP_MAX_PEERS; indx++)
   {
      if(smCfgCb.wrNghCellCfg[indx] != NULLP)
     {
         if(smCfgCb.wrNghCellCfg[indx]->physCellId == pci)
         {
            WR_FREE(smCfgCb.wrNghCellCfg[indx], sizeof(LwrNghCellCfg));
            smCfgCb.wrNghCellCfg[indx] = NULLP;
            smCfgCb.noOfNghInfo--;
         break;
         }
     }
   }

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 smBuildDynWrNehCellDel
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildDynWrNehCellDel(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrEutranCellDelCfg *eutraNeghCell = NULLP;
   U32 idx = 0;
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_DEL;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1;
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = 2;

   for(idx = 0; idx < lwrMng->t.protoCfg.t.neighCellCfg.numCells; idx++)
   {
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighDelCfg[idx].type = WR_NEIGH_CELL_EUTRA;
      eutraNeghCell = &(lwrMng->t.protoCfg.t.neighCellCfg.t.neighDelCfg[idx].t.eutranCell);
      eutraNeghCell->nrIndex = 2;
      eutraNeghCell->phyCellId = (U16)(142 + idx);
      eutraNeghCell->earfcn = 2500;
   }

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 smSndDynWrNhCellDel
(
void
)
#else
PUBLIC S16 smSndDynWrNhCellDel()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildDynWrNehCellDel(&lwrMng);
   
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
}

#ifdef ANSI
PUBLIC S16 smBuildDynWrNehCellMod
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smBuildDynWrNehCellMod(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrEUTRANeighCell         *eutraNeghCell = NULLP;
   U32                       index = 0;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_MOD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1;
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = 2;

   for(index = 0; index < lwrMng->t.protoCfg.t.neighCellCfg.numCells; index++)
   {
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighModCfg[index].type = WR_NEIGH_CELL_EUTRA;
      eutraNeghCell = &(lwrMng->t.protoCfg.t.neighCellCfg.t.neighModCfg[index].t.eutraCell);

      eutraNeghCell->pci = 142 + index;
      eutraNeghCell->tac = 5;
      eutraNeghCell->qoffset = LWR_OFFSET_DB_MINUS_16;
      eutraNeghCell->cio = LWR_OFFSET_DB_PLUS_5;

      eutraNeghCell->earfcnDl = 2500;
   }

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 smSndDynWrNhCellMod
(
void
)
#else
PUBLIC S16 smSndDynWrNhCellMod()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smBuildDynWrNehCellMod(&lwrMng);
   
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
}

PRIVATE S16 smDynUtraFreqMod
(
LwrMngmt                     *lwrmng
)
{
   LwrNeighFreqAddModCfg *nrfreqcfg =NULLP;

   lwrmng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrmng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_MOD;
   lwrmng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is owncellid in case of pld based conf, jst a logic entity */

   lwrmng->t.protoCfg.t.neighFreqCfg.numFreq = 1;
   nrfreqcfg =lwrmng->t.protoCfg.t.neighFreqCfg.t.modNeighFreq;
   nrfreqcfg->type = WR_NEIGH_CELL_UTRA;
   nrfreqcfg->t.utranFreq.reCfgType = 0x000fff;
   nrfreqcfg->t.utranFreq.freqIndex = 1;
   nrfreqcfg->t.utranFreq.arfcnUl = 9764;
   nrfreqcfg->t.utranFreq.arfcnDl = 10726;
   nrfreqcfg->t.utranFreq.priority.pres = PRSNT_NODEF;
   nrfreqcfg->t.utranFreq.priority.val = 2;
   nrfreqcfg->t.utranFreq.threshXhigh = 31;
   nrfreqcfg->t.utranFreq.threshXlow = 31;
   nrfreqcfg->t.utranFreq.qRxLevMin = -50;
   nrfreqcfg->t.utranFreq.pMaxUtra = 1;
   nrfreqcfg->t.utranFreq.pQualMin = -16;
   nrfreqcfg->t.utranFreq.offsetFreq = 30; /* changed */
   nrfreqcfg->t.utranFreq.duplexMode = 0;
   nrfreqcfg->t.utranFreq.t.utraFdd.thresR9.pres = PRSNT_NODEF;
   nrfreqcfg->t.utranFreq.t.utraFdd.thresR9.thresXHighQR9 = 31;
   nrfreqcfg->t.utranFreq.t.utraFdd.thresR9.thresXLowQR9 = 31;

   RETVALUE(ROK);
}

PRIVATE S16 smDynUtraFreqAdd
(
LwrMngmt                     *lwrmng
)
{
   LwrNeighFreqAddModCfg *nrfreqcfg =NULLP;

   lwrmng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrmng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrmng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is owncellid in case of pld based conf, jst a logic entity */

   lwrmng->t.protoCfg.t.neighFreqCfg.numFreq = 1;
   nrfreqcfg =lwrmng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq;
   nrfreqcfg->type = WR_NEIGH_CELL_UTRA;

   nrfreqcfg->t.utranFreq.reCfgType = 0x000fff;
   nrfreqcfg->t.utranFreq.freqIndex = 1;
   nrfreqcfg->t.utranFreq.arfcnUl = 9764;
   nrfreqcfg->t.utranFreq.arfcnDl = 10726;
   nrfreqcfg->t.utranFreq.priority.pres = PRSNT_NODEF;
   nrfreqcfg->t.utranFreq.priority.val = 2;
   nrfreqcfg->t.utranFreq.threshXhigh = 31;
   nrfreqcfg->t.utranFreq.threshXlow = 31;
   nrfreqcfg->t.utranFreq.qRxLevMin = -50;
   nrfreqcfg->t.utranFreq.pMaxUtra = 1;
   nrfreqcfg->t.utranFreq.pQualMin = -16;
   nrfreqcfg->t.utranFreq.offsetFreq = 15;
   nrfreqcfg->t.utranFreq.duplexMode = 0;
   nrfreqcfg->t.utranFreq.t.utraFdd.thresR9.pres = PRSNT_NODEF;
   nrfreqcfg->t.utranFreq.t.utraFdd.thresR9.thresXHighQR9 = 31;
   nrfreqcfg->t.utranFreq.t.utraFdd.thresR9.thresXLowQR9 = 31;

   RETVALUE(ROK);
}

PRIVATE S16 smDynUtraFreqDel
(
LwrMngmt                     *lwrmng
)
{
   LwrNeighFreqDelCfg *nrfreqcfg =NULLP;

   lwrmng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrmng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_DEL;
   lwrmng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is owncellid in case of pld based conf, jst a logic entity */

   lwrmng->t.protoCfg.t.neighFreqCfg.numFreq = 1;
   nrfreqcfg =lwrmng->t.protoCfg.t.neighFreqCfg.t.delNeighFreq;
   nrfreqcfg->type = WR_NEIGH_CELL_UTRA;
   nrfreqcfg->t.utranFreq.freqIndex = 5;
   nrfreqcfg->t.utranFreq.arfcn = 10726;

   RETVALUE(ROK);
}

PUBLIC S16 smDynWrNrUtraFreqCfg
(
U8                           type
)
{
   LwrMngmt lwrMng;
   Pst pst;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   if(type == 1)
   {
      /* add new neighbor */
      smDynUtraFreqAdd(&lwrMng);
   }
   else if (type == 2)
   {
      /* modify existing neighbor */
      smDynUtraFreqMod(&lwrMng);
   }
   else
   {
      /* remove existing neighbor */
      smDynUtraFreqDel(&lwrMng);
   }
   
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
}
/*
*
*       Fun:   smSndWrCellModSib6
*
*       Desc:  This function for sending eNodeB SIB6 Modification to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellModSib6
(
)
#else
PUBLIC S16 smSndWrCellModSib6()
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrCellSib6CfgGrp *sib6 =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = wrSmDfltCellId;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib6 params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB6;

   sib6 =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib6CfgGrp);
   sib6->reCfgType = LWR_UTRAN_SIB6_TRESELECT;
   sib6->tReselection= 2;

   cfgGrpIndex++; 
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}                                             


/*
*
*       Fun:   smSndWrCellModSib9
*
*       Desc:  This function for sending eNodeB SIB9 Modification to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellModSib9
(
)
#else
PUBLIC S16 smSndWrCellModSib9()
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrCellSib9CfgGrp *sib9 =NULLP;
   U8                cfgGrpIndex  = 0;
   


   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = wrSmDfltCellId;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib9 params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB9;

   sib9 =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib9CfgGrp);

   /* kworks fix */
   cmMemcpy((U8 *)sib9->henbName, (U8 *)"SKT-Pangyo", cmStrlen((U8 *)"SKT-Pangyo"));

   cfgGrpIndex++; 
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}                                        

/*
*
*       Fun:   smBuildWrNehCellCfg
*
*       Desc:  This function for filling neighbour cell configuration
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smModBuildWrNehCellCfg
(
LwrMngmt *lwrMng
)
#else
PUBLIC S16 smModBuildWrNehCellCfg(*lwrMng)
LwrMngmt *lwrMng;
#endif
{
   LwrEUTRANeighCell *eutraNeghCell = NULLP;
   U32 idx; 
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_MOD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = 1; /* this is ownCellID in case of PLD, jst a logical entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = (U16)wrSmDfltNumCells;

   for(idx=0;idx<wrSmDfltNumCells;idx++)
   {
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighModCfg[idx].type = WR_NEIGH_CELL_EUTRA;
      eutraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighModCfg[idx].t.eutraCell);
      eutraNeghCell->cellNum = wrSmDfltNeigCellNum[idx];
      eutraNeghCell->nrIndex = wrSmDfltNriIndex[idx];
      eutraNeghCell->enbId = wrSmDfltNeighEnbID[idx];

      eutraNeghCell->cio =wrSmDfltCIO;
      eutraNeghCell->enbPlmn.numMncDigits = wrSmDfltNeEnbNumMncDigits;
      eutraNeghCell->enbPlmn.mcc[0] =wrSmDfltNeEnbPlmn1Mcc0[idx];
      eutraNeghCell->enbPlmn.mcc[1] =wrSmDfltNeEnbPlmn1Mcc1[idx];
      eutraNeghCell->enbPlmn.mcc[2] =wrSmDfltNeEnbPlmn1Mcc2[idx];

      eutraNeghCell->enbPlmn.mnc[0] =wrSmDfltNeEnbPlmn1Mnc0[idx];
      eutraNeghCell->enbPlmn.mnc[1] =wrSmDfltNeEnbPlmn1Mnc1[idx];
      eutraNeghCell->enbPlmn.mnc[2] =wrSmDfltNeEnbPlmn1Mnc2[idx];

   eutraNeghCell->enbType = wrSmDfltNeighEnbType;
   eutraNeghCell->numPlmn = wrSmDfltNeighCellNoPlmn;

   eutraNeghCell->pci = wrSmDfltNeighCellPci[idx];
   eutraNeghCell->tac = wrSmDfltNeighCellTAC[idx];

   eutraNeghCell->qoffset = LWR_OFFSET_DB_MINUS_8;

      eutraNeghCell->dlBw = wrSmDfltCellDlBW[0];

      eutraNeghCell->earfcnDl = wrSmDfltEartcnNrDLEarfcn[idx];
      eutraNeghCell->earfcnUl= wrSmDfltUlEarFcn;

      eutraNeghCell++;
   }   
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 smModWrNhCellCfg
(
void
)
#else
PRIVATE S16 smModWrNhCellCfg()
#endif
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   smModBuildWrNehCellCfg(&lwrMng);
   
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
}

/*
*
*       Fun:   smSndWrCellModSib4
*
*       Desc:  This function for sending eNodeB SIB4 Modification to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellModSib4
(
)
#else
PUBLIC S16 smSndWrCellModSib4()
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrCellSib4CfgGrp *sib4 =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = wrSmDfltCellId;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib4 params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB4;

   sib4 =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib4CfgGrp);

   sib4->reCfgType = LWR_CELL_SIB3_CFG_CSG_INFO;

   sib4->csgInfo.csgPciRange = 0;
   sib4->csgInfo.csgPciRangeUsage =0;
   //sib4->csgInfo.csgPciType = 0;
   sib4->csgInfo.csgStartPhyCellId = 0;

   cfgGrpIndex++; 
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}   

PRIVATE S16 smDynEutraFreqMod
(
LwrMngmt                     *lwrMng
)
{
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_MOD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic entity */

   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = 1;
   nrFreqCfg = (lwrMng->t.protoCfg.t.neighFreqCfg.t.modNeighFreq);
   nrFreqCfg->type = WR_NEIGH_CELL_EUTRA;
   nrFreqCfg->t.eutranFreq.reCfgType = wrSmDfltReCfgType;
   nrFreqCfg->t.eutranFreq.status = wrSmDfltStatus;
   nrFreqCfg->t.eutranFreq.earfcnUl = wrSmDfltUlEarFcn;
   nrFreqCfg->t.eutranFreq.earfcnDl = 5250;
   nrFreqCfg->t.eutranFreq.priority = wrSmDfltPriority;
   nrFreqCfg->t.eutranFreq.qRxLevMin = -60; /* changed */
   nrFreqCfg->t.eutranFreq.pMaxUsage = wrSmDfltPMaxUsage;
   nrFreqCfg->t.eutranFreq.pMax = wrSmDfltS3pMax;
   nrFreqCfg->t.eutranFreq.tReselection = wrSmDfltTReselection;
   nrFreqCfg->t.eutranFreq.sfUsage = wrSmDfltSfUsage;
   nrFreqCfg->t.eutranFreq.tReselectionSFMed = wrSmDfltTReselectionSFMed;
   nrFreqCfg->t.eutranFreq.tReselectionSFHigh = wrSmDfltTReselectionSFHigh;
   nrFreqCfg->t.eutranFreq.sIntraSearch.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sIntraSearch.val = wrSmDfltSIntraSearch;
   nrFreqCfg->t.eutranFreq.sNonIntraSearch.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sNonIntraSearch.val = 30;
   nrFreqCfg->t.eutranFreq.servThresholdLow = 30;
   nrFreqCfg->t.eutranFreq.threshXHigh = 30;
   nrFreqCfg->t.eutranFreq.threshXLow =  30;
   nrFreqCfg->t.eutranFreq.measBandwidth.pres =  PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.measBandwidth.val = 4;
   nrFreqCfg->t.eutranFreq.presAntennaPort1 =  wrSmDfltPresAntennaPort1;
   nrFreqCfg->t.eutranFreq.neighCellCfg =  wrSmDfltNeighCellCfg;
   nrFreqCfg->t.eutranFreq.qOffsetFreq = LWR_Q_OFFSET_RANGE_0;
   nrFreqCfg->t.eutranFreq.offsetFreq =  LWR_Q_OFFSET_RANGE_0;
   nrFreqCfg->t.eutranFreq.sIntraSearchRel9.pres =  PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchQRel9 =  wrSmDfltsSearchQRel9;
   nrFreqCfg->t.eutranFreq.sInterSearchRel9.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
   nrFreqCfg->t.eutranFreq.qQualMinRel9.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.qQualMinRel9.val = wrSmDfltDualMinRel9;
   nrFreqCfg->t.eutranFreq.reselecThreshQRel9.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.reselecThreshQRel9.val =  wrSmDfltReselecThreshQRel9;
   nrFreqCfg->t.eutranFreq.threshXQRel9.threshXHighQR9 =  wrSmDfltThreshXHighQR9;
   nrFreqCfg->t.eutranFreq.threshXQRel9.threshXLowQR9 =  wrSmDfltThreshXLowQR9;

   RETVALUE(ROK);
}

PRIVATE S16 smDynEutraFreqAdd
(
LwrMngmt                     *lwrMng
)
{
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic entity */

   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = 1;
   nrFreqCfg = (lwrMng->t.protoCfg.t.neighFreqCfg.t.modNeighFreq);
   nrFreqCfg->type = WR_NEIGH_CELL_EUTRA;
   nrFreqCfg->t.eutranFreq.reCfgType = wrSmDfltReCfgType;
   nrFreqCfg->t.eutranFreq.status = wrSmDfltStatus;
   nrFreqCfg->t.eutranFreq.earfcnUl = wrSmDfltUlEarFcn;
   nrFreqCfg->t.eutranFreq.earfcnDl = 5250;
   nrFreqCfg->t.eutranFreq.priority = wrSmDfltPriority;
   nrFreqCfg->t.eutranFreq.qRxLevMin = wrSmDfltQRxLevMin;
   nrFreqCfg->t.eutranFreq.pMaxUsage = wrSmDfltPMaxUsage;
   nrFreqCfg->t.eutranFreq.pMax = wrSmDfltS3pMax;
   nrFreqCfg->t.eutranFreq.tReselection = wrSmDfltTReselection;
   nrFreqCfg->t.eutranFreq.sfUsage = wrSmDfltSfUsage;
   nrFreqCfg->t.eutranFreq.tReselectionSFMed = wrSmDfltTReselectionSFMed;
   nrFreqCfg->t.eutranFreq.tReselectionSFHigh = wrSmDfltTReselectionSFHigh;
   nrFreqCfg->t.eutranFreq.sIntraSearch.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sIntraSearch.val = wrSmDfltSIntraSearch;
   nrFreqCfg->t.eutranFreq.sNonIntraSearch.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sNonIntraSearch.val = 30;
   nrFreqCfg->t.eutranFreq.servThresholdLow = 30;
   nrFreqCfg->t.eutranFreq.threshXHigh = 30;
   nrFreqCfg->t.eutranFreq.threshXLow =  30;
   nrFreqCfg->t.eutranFreq.measBandwidth.pres =  PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.measBandwidth.val = 4;
   nrFreqCfg->t.eutranFreq.presAntennaPort1 =  wrSmDfltPresAntennaPort1;
   nrFreqCfg->t.eutranFreq.neighCellCfg =  wrSmDfltNeighCellCfg;
   nrFreqCfg->t.eutranFreq.qOffsetFreq = LWR_Q_OFFSET_RANGE_0;
   nrFreqCfg->t.eutranFreq.offsetFreq =  LWR_Q_OFFSET_RANGE_0;
   nrFreqCfg->t.eutranFreq.sIntraSearchRel9.pres =  PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchQRel9 =  wrSmDfltsSearchQRel9;
   nrFreqCfg->t.eutranFreq.sInterSearchRel9.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
   nrFreqCfg->t.eutranFreq.qQualMinRel9.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.qQualMinRel9.val = wrSmDfltDualMinRel9;
   nrFreqCfg->t.eutranFreq.reselecThreshQRel9.pres = PRSNT_NODEF;
   nrFreqCfg->t.eutranFreq.reselecThreshQRel9.val =  wrSmDfltReselecThreshQRel9;
   nrFreqCfg->t.eutranFreq.threshXQRel9.threshXHighQR9 =  wrSmDfltThreshXHighQR9;
   nrFreqCfg->t.eutranFreq.threshXQRel9.threshXLowQR9 =  wrSmDfltThreshXLowQR9;

   RETVALUE(ROK);
}

PRIVATE S16 smDynEutraFreqDel
(
LwrMngmt                     *lwrMng
)
{
   LwrNeighFreqDelCfg *nrFreqCfg = NULLP;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_DEL;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = 1; /* this is ownCellID in case of PLD based, jst a logic entity */

   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = 1;
   nrFreqCfg = (lwrMng->t.protoCfg.t.neighFreqCfg.t.delNeighFreq);
   nrFreqCfg->type = WR_NEIGH_CELL_EUTRA;
   nrFreqCfg->t.eutranFreq.earfcn = 5250;

   RETVALUE(ROK);
}
 
PUBLIC S16 smDynWrNrEutraFreqCfg
(
U8                           type
)
{
   LwrMngmt lwrMng;
   Pst pst;
   
   
   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   if(type == 1)
   {
      /* add new configuration */
      smDynEutraFreqAdd(&lwrMng);
   }
   else if(type == 2)
   {
      /* modify existing configuration */
      smDynEutraFreqMod(&lwrMng);
   }
   else
   {
      /* delete existing configuration */
      smDynEutraFreqDel(&lwrMng);
   }
   
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
}

/*
*
*       Fun:   smSndWrCellModSib5
*
*       Desc:  This function for sending eNodeB SIB5 Modification to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellModSib5
(
)
#else
PUBLIC S16 smSndWrCellModSib5()
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = wrSmDfltCellId;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;


   cfgGrpIndex++; 
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}   

/*
*
*       Fun:   smSndWrCellModSib3
*
*       Desc:  This function for sending eNodeB SIB3 Modification to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellModSib3
(
)
#else
PUBLIC S16 smSndWrCellModSib3()
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrCellSib3CfgGrp *sib3 =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = wrSmDfltCellId;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib3 params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB3;

   sib3 =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib3CfgGrp);

   sib3->reCfgType = LWR_CELL_SIB3_CFG_QHYST | LWR_CELL_SIB3_CFG_SPD_ST_RESEL
      | LWR_CELL_SIB3_CFG_MOB_ST_PAR | LWR_CELL_SIB3_CFG_SF_MEDIUM | LWR_CELL_SIB3_CFG_SF_HIG
      | LWR_CELL_SIB3_CFG_SERV_FREQ_INFO | LWR_CELL_SIB3_CFG_INTRA_RREQ;
   sib3->qHyst = 2;
   sib3->speedStateReselPres = WR_PRSNT;
   sib3->mobStateParams.nCellChangeHigh = 2;
   sib3->mobStateParams.nCellChangeMedium =2;
   sib3->mobStateParams.speedStatPres.pres =WR_PRSNT;
   sib3->mobStateParams.tEvalulation = 1;
   sib3->mobStateParams.tHystNormal =1;
   sib3->sfMedium = 0;
   sib3->sfHigh =0;

   cfgGrpIndex++; 
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}   


/*
*
*       Fun:   smSndWrCellModSib2
*
*       Desc:  This function for sending eNodeB SIB2 Modification to LWR
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_wr_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smSndWrCellModSib2
(
)
#else
PUBLIC S16 smSndWrCellModSib2()
#endif
{
   LwrMngmt          lwrMng;
   Pst               pst;
   LwrCellSib2CfgGrp *sib2 =NULLP;
   U8                cfgGrpIndex  = 0;

   SM_SET_ZERO(&lwrMng, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   lwrMng.t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng.t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellId = wrSmDfltCellId;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellIndex = wrSmDfltCellIndex;
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;
   /*Filling Sib2 params*/
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType
                                                        = WR_CELL_CFG_GRP_SIB2;

   sib2 =&(lwrMng.t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].t.sib2CfgGrp);

   #if 0
   sib2->reCfgType = LWR_CELL_SIB2_CFG_RADIO_RSRC_CMN | LWR_CELL_SIB2_CFG_TIME_ALIGN | 
      LWR_CELL_SIB2_CFG_UE_FREQ_INFO | LWR_CELL_SIB2_CFG_TIME_ALIGN;
   
   sib2->radioResourceCommon.reCfgType = LWR_CELL_SIB2_RRSRCMN_RACH_CFG_CMN | LWR_CELL_SIB2_RRSRCMN_BCCH_CFG_CMN
      | LWR_CELL_SIB2_RRSRCMN_PRACH_CFG_CMN |LWR_CELL_SIB2_RRSRCMN_PDSCH_CFG_CMN | LWR_CELL_SIB2_RRSRCMN_PUSCH_CFG_CMN
      | LWR_CELL_SIB2_RRSRCMN_PUCCH_CFG_CMN | LWR_CELL_SIB2_RRSRCMN_SRS_CFG_CMN | LWR_CELL_SIB2_RRSRCMN_UL_PWR_CNRL_CFG_CMN
      | LWR_CELL_SIB2_RRSRCMN_UL_CYCPREFIX_CFG_CMN | LWR_CELL_SIB2_RRSRCMN_DL_CYCPREFIX_CFG_CMN;
   #endif

   sib2->reCfgType = LWR_CELL_SIB2_CFG_RADIO_RSRC_CMN | LWR_CELL_SIB2_CFG_UE_TMR_CONS | LWR_CELL_SIB2_CFG_TIME_ALIGN;
   
   sib2->radioResourceCommon.reCfgType = LWR_CELL_SIB2_RRSRCMN_RACH_CFG_CMN 
      | LWR_CELL_SIB2_RRSRCMN_PDSCH_CFG_CMN | LWR_CELL_SIB2_RRSRCMN_SRS_CFG_CMN;
    

   sib2->radioResourceCommon.rachCfgCommon.maxHARQMsg3 = 2;
   
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.numOfRAPreambles = NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn4Enum;
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.groupASize = NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn4Enum;
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.msgSizeGroupA = NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupAb56Enum;
   sib2->radioResourceCommon.rachCfgCommon.preambleCfg.pwrOffstGrpB  = 0x02;

   sib2->radioResourceCommon.rachCfgCommon.powerRamping.initRcvdTrgtPwr = 0x0a;
   sib2->radioResourceCommon.rachCfgCommon.powerRamping.powerRampingstep = 0x02;

   sib2->radioResourceCommon.rachCfgCommon.raSupervisionCfg.macContResTimer = NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf40Enum;
   sib2->radioResourceCommon.rachCfgCommon.raSupervisionCfg.rarWindowSize= 0x06;
   sib2->radioResourceCommon.rachCfgCommon.raSupervisionCfg.preambleTransMax= 0x02;

   sib2->radioResourceCommon.pdschCfgCommon.pB = 0x01;
   sib2->radioResourceCommon.pdschCfgCommon.referenceSignalPwr = 1;

   sib2->radioResourceCommon.srsCfgCommon.cSrs = 0x01;
   sib2->radioResourceCommon.srsCfgCommon.simulAckNackSrs = TRUE; 
   sib2->radioResourceCommon.srsCfgCommon.srsMaxUpts = 0x01;
   sib2->radioResourceCommon.srsCfgCommon.subframeCfg = 0x01;


   sib2->ueTimerConstants.t300 = 0x01;
   sib2->ueTimerConstants.t301 = 0x01;
   sib2->ueTimerConstants.t310 = 0x01;
   sib2->ueTimerConstants.n310 =0x01;
   sib2->ueTimerConstants.t311 =0x01;
   sib2->ueTimerConstants.n311 = 0x01;
   /* ccpu00125578 T304 value set to ms500 so that
    * RRC Connection Reestablishment will be delayed during HO */
   sib2->ueTimerConstants.ccoT304 = 0x04;
   sib2->ueTimerConstants.t304 = 0x04;

   sib2->timeAlignmentCommon = 0x06;


   #if 0
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
 #endif 
   cfgGrpIndex++; 
   lwrMng.t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;
   lwrMng.hdr.msgType             = TCFG;
   lwrMng.hdr.msgLen              = 0;
   lwrMng.hdr.entId.ent           = ENTWR;
   lwrMng.hdr.entId.inst          = SM_INST_ZERO;
   lwrMng.hdr.elmId.elmnt         = STWRPROTOCFG;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;

   (Void) SmMiLwrCfgReq(&pst, &lwrMng);
   
   RETVALUE(ROK);
}                                             

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
PRIVATE S16 smBuildWrstopPHYCntrl
(
)
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
}

/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
