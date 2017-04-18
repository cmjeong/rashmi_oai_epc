
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_scell_utils.c

     Sid:      $SID$ 

     Prg:      Amit 

*********************************************************************21*/

#include "wr.h"
#include "wr_umm_trans.h"
#include "wr_utils.h"
#include "wr_smm_smallcell.h"
#include "wr_umm_meas_fun.h" 
#include "wr_kpi.h"


#ifdef LTE_ADV
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=176;

static int RLOG_MODULE_ID=32;

EXTERN Bool wrUtlGetSCellDeActTmrVal 
(
 U32          sCellDeActTmr,
 U32         *actTmr         
);

EXTERN S16  wrUtlFillAddModSCell
(
 NhuSCellToAddMod_r10  *member,
 WrSCellInfo           *sCellInfo,
 WrUeCb                *ueCb, 
 NhuDatReqSdus         *recfgMsg
);
EXTERN S16  wrUtlFillAddModSCellRadResCfgDedUL
(
NhuPhysicalConfigDedicatedSCell_r10ul_Cfg_r10 *uL_Cfg_r10,
WrSCellInfo 			 *sCellInfo,
WrUeCb                *ueCb 
);
EXTERN S16  wrUtlFillAddModSCellRadResCfgDedNonUL
(
NhuPhysicalConfigDedicatedSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
WrSCellInfo 			 *sCellInfo,
WrUeCb					 *ueCb,
NhuDatReqSdus		*recfgMsg
);
EXTERN S16  wrUtlFillAddModSCellRadResCfgCmnUL
(
NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10 *uL_Cfg_r10,
WrCellCb           *cellCb
);
EXTERN S16  wrUtlFillAddModSCellRadResCfgCmnNonUL
(
NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
WrCellCb           *cellCb
);
EXTERN S16  wrUtlFillAddModSCellRadResCfgCmn
(
NhuRadioResourceConfigCmnSCell_r10 *cfgCmnSCell,
WrCellCb           *cellCb
);
EXTERN S16  wrUtlFillAddModSCellRadResCfgDed
(
NhuRadioResourceConfigDedicatedSCell_r10 *cfgDedSCell,
WrSCellInfo 			 *sCellInfo,
WrUeCb                *ueCb,
NhuDatReqSdus		*recfgMsg
);

PUBLIC S16 wrUmmFillN1PucchRes
   (
    WrUeCb                          *ueCb, 
    NhuDatReqSdus                   *recfgMsg,
    NhuRadioResourceConfigDedicated *rrcCfgDed
 );

/**
 *  @brief This function will fill the SapIds for below interfaces which MAC
 *  will use 
 *      . RLC-MAC  
 *
 *      Function: wrFillRlcMacSaps
 *
 *          Processing steps:
 *             - Fill the SapIds for all interfaces which will be used for multi
 *             Sap/instance support
 *
 *  @param[in]  cellId        :  Cell Id of corresponding CellCb
 *  @param[out]  *ueSCellCfg    :  sapId list to be filled by App
 *  @return Bool 
 */
PUBLIC Void wrFillRlcMacSaps
(
   NhuUeSCellInfo   *ueSCellInfo,
   U8                cellId 
)
{
   /* Fill all correct SuIds in this structure */
   /* Cell Id will always be assigned starting from 1.
    * So Cell Id should not be 0. */

   ueSCellInfo->rguUlSapId = wrCb.sapIds[cellId - 1].rguUlSapId;
   ueSCellInfo->rguDlSapId = wrCb.sapIds[cellId - 1].rguDlSapId;

   RETVOID;
}

/**
 *  @brief This function is used for getting list of SCell for a particular cell
 *
 *      Function: wrEmmGetSCellIdLst
 *
 *@param[in]     cellId    : cell id
 *@param[out]    numSCells : No of Cells 
 *@param[out]     sCellIdLst: sCellId List to be Updated
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrEmmGetSCellIdLst
(
 WrCellId                  cellId,
 U8                        *numSCells,
 WrCellId                  *sCellIdLst
)
{
   U8                      idx = 0;
   *numSCells = 0;
   for (idx = 0; idx < WR_MAX_CELLS; idx++)
   {
      if ((wrEmmCb.cellCb[idx] != NULLP) && (wrEmmCb.cellCb[idx]->cellId != cellId))
      {
         sCellIdLst[*numSCells] = wrEmmCb.cellCb[idx]->cellId; 
         (*numSCells)++;
         if (*numSCells == WR_MAX_SCELL_PER_UE)
         {
            break;
         }
      }
   }
   RETVALUE(ROK);
}
      
/**
 *  @brief This function is used for filling SCell Config Dedicated Non UL for a particular cell
 *
 *      Function: wrUtlFillAddModSCellRadResCfgDedUL
 *
 *@param[out]       NhuPhysicalConfigDedicatedSCell_r10ul_Cfg_r10 *nonUL_Cfg_r10,
 
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCellRadResCfgDedUL
(
NhuPhysicalConfigDedicatedSCell_r10ul_Cfg_r10 *uL_Cfg_r10,
WrSCellInfo 			 *sCellInfo,
WrUeCb                *ueCb 
)
{
   NhuUlnkPowerCntrlDedicatedSCell_r10      *uplnkPwrCntrl = NULLP;
   WrCellCb                *cellCb = NULLP;
   NhuCQI_ReportConfigSCell_r10 *cqi_ReportConfigSCell_r10;
   NhuCQI_ReportPeriodic_r10setup *setup;

   WR_EMM_GET_CELLCB(cellCb, sCellInfo->sCellId);
   
   wrFillTknU8(&uL_Cfg_r10->pres, PRSNT_NODEF);

   /*CQI Cofiguration*/
	if (sCellInfo->bResCfgBitMap &  WR_UE_RADIO_RES_CFG_CQI)
   {
      wrFillTknU8(&uL_Cfg_r10->cqi_ReportConfigSCell_r10.pres, PRSNT_NODEF);

      cqi_ReportConfigSCell_r10 = &uL_Cfg_r10->cqi_ReportConfigSCell_r10;
      if(ueCb->cqiRptCfg.aperCqiEnbld)
      {
      /*When you uncommnet here, also uncomment APCQI pres check in
        wrAcFillUlCfgRadioRscCfgDedScell in wrac_nhuhdl.c*/

         wrFillTknU32(&cqi_ReportConfigSCell_r10->cqi_ReportModeAperiodic_r10, 
               sCellInfo->cqiRptCfg.cqiAperiodicMode);

         printf("\n APP_ACQI_SCELL:: Mode is %lu\n",sCellInfo->cqiRptCfg.cqiAperiodicMode);
      }
      else
      {
	      cqi_ReportConfigSCell_r10->cqi_ReportModeAperiodic_r10.pres = NOTPRSNT;
      }      
      wrFillTknS32(&cqi_ReportConfigSCell_r10->nomPDSCH_RS_EPRE_Offset_r10, 
            (S32)sCellInfo->cqiRptCfg.nomPdschRsEpreOff);
      cqi_ReportConfigSCell_r10->pmi_RI_Report_r10.pres = NOTPRSNT;

      /*Periodic CQI -R10 Configuration*/
      WR_FILL_TKN_UINT(cqi_ReportConfigSCell_r10->cqi_ReportPeriodicSCell_r10.choice, 
            CQI_REPORTPERIODIC_SETUP);

      setup = &(cqi_ReportConfigSCell_r10->cqi_ReportPeriodicSCell_r10.val.setup);
      wrFillTknU8(&setup->pres, PRSNT_NODEF);

      WR_FILL_TKN_UINT(setup->cqi_PUCCH_ResourceIdx_r10, sCellInfo->cqiRptCfg.cqiPucchRsrcIdx);
      setup->cqi_PUCCH_ResourceIdxP1_r10.pres = NOTPRSNT;

		
      WR_FILL_TKN_UINT(setup->cqi_pmi_ConfigIdx, (U32)sCellInfo->cqiRptCfg.cqipmiCfgIdx);

      if(sCellInfo->cqiRptCfg.fmtInd ==  WR_UE_CQI_FMT_SB)
      {
         WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.choice, 
               CQI_FORMATINDICATORPERIODIC_SUBBANDCQI);
         WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.pres, PRSNT_NODEF);
         WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.k,\
               sCellInfo->cqiRptCfg.subbndCqik);
         WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.periodicityFactor_r10, 
               sCellInfo->cqiRptCfg.sBCqiPeriodicityFactor);
      }
      else
      {
         WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.choice, 
               CQI_FORMATINDICATORPERIODIC_WIDEBANDCQI);
         WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.pres, 
               PRSNT_NODEF);					
         /*to-do assumed that this is required only for TMMode9, hence made not present currently*/
         /* WR_FILL_TKN_UINT(setup->cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.csi_ReportMode_r10, 
               NOTPRSNT); */
      }

      /* HO_REEST: Filling RI Index */
      if(sCellInfo->cqiRptCfg.riPres == TRUE)
      {
         WR_FILL_TKN_UINT(setup->ri_ConfigIdx, sCellInfo->cqiRptCfg.riCfgIdx);
      }
		
      WR_FILL_TKN_UINT(setup->simultaneousAckNackAndCQI, FALSE); /* UE wil ignor this parm for scell add*/
     setup->cqi_Mask_r9.pres = NOTPRSNT;
	}
	else
   {
        uL_Cfg_r10->cqi_ReportConfigSCell_r10.pres.pres = NOTPRSNT;
	}
	
	uL_Cfg_r10->soundingRS_UL_ConfigDedicated_r10.choice.pres = NOTPRSNT;
	uL_Cfg_r10->soundingRS_UL_ConfigDedicated_v1020.pres.pres = NOTPRSNT;
	uL_Cfg_r10->soundingRS_UL_ConfigDedicatedAperiodic_r10.choice.pres = NOTPRSNT;

   /* UL PC DED params */
   if (TRUE == wrEmmCb.isUlCaEnabled)
   {
      /* Uplink Power Control Configuration */
      uplnkPwrCntrl = &(uL_Cfg_r10->uplinkPowerCntrlDedicatedSCell_r10);

      WR_FILL_TKN_UINT(uplnkPwrCntrl->pres, PRSNT_NODEF);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->p0_UE_PUSCH_r10,
            cellCb->ulPwrCtrl.p0UePUSCH);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->deltaMCS_Enabled_r10,
            cellCb->ulPwrCtrl.deltaMCSenabled);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->accumulationEnabled_r10,
            cellCb->ulPwrCtrl.accumulationEnabled);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->pSRS_Offset_r10,
            cellCb->ulPwrCtrl.pSRSoffset);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->pSRS_OffsetAp_r10,
            cellCb->ulPwrCtrl.pSRSoffset);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->filterCoefficient_r10,
            cellCb->ulPwrCtrl.filterCoefficient);
      WR_FILL_TKN_UINT(uplnkPwrCntrl->pathlossReferenceLinking_r10, 1);
   }

	RETVALUE(ROK);
}


/**
 *  @brief This function is used for filling SCell Config Dedicated Non UL for a particular cell
 *
 *      Function: wrUtlFillAddModSCellRadResCfgDedNonUL
 *
 *@param[out]       NhuPhysicalConfigDedicatedSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
 
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCellRadResCfgDedNonUL
(
NhuPhysicalConfigDedicatedSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
WrSCellInfo 			 *sCellInfo,
WrUeCb					 *ueCb,
NhuDatReqSdus		*recfgMsg
)
{	
   NhuPDSCH_ConfigDedicated        *pdschCfg = NULLP;
	wrFillTknU8(&nonUL_Cfg_r10->pres, PRSNT_NODEF);
	NhuAntennaInfoDedicated_r10 *antennaInfo = &(nonUL_Cfg_r10->antennaInfo_r10);
	wrFillTknU8(&antennaInfo->pres, PRSNT_NODEF);
	wrFillTknU32(&antennaInfo->transmissionMode_r10, ueCb->antennaInfo.txmode);   
	wrFillTknU8(&antennaInfo->ue_TransmitAntennaSelection.choice,
					UE_TRANSMITANTENNASELECTION_RELEASE);
	antennaInfo->codebookSubsetRestrn_r10.pres = NOTPRSNT;
	
	if (ueCb->antennaInfo.txmode == NhuAntennaInfoDedicatedtransmissionModetm3Enum)
	{
		WR_FILL_BIT_STR(antennaInfo->codebookSubsetRestrn_r10, 2, 3, recfgMsg); 
	}
	if (ueCb->antennaInfo.txmode == NhuAntennaInfoDedicatedtransmissionModetm4Enum)
   {
		WR_FILL_BIT_STR(antennaInfo->codebookSubsetRestrn_r10, 6, 63, recfgMsg); 
   }
	/* PDSCH Configuration */
    pdschCfg = &(nonUL_Cfg_r10->pdsch_ConfigDedicated_r10);
    WR_FILL_TKN_UINT(pdschCfg->pres,PRSNT_NODEF);
    WR_FILL_TKN_UINT(pdschCfg->p_a, ueCb->pdschDedCfg.p_a); 

	/*to-do*/
	RETVALUE(ROK);
}

/**
 *  @brief This function is used for filling SCell Config Common Non UL for a particular cell
 *
 *      Function: wrUtlFillAddModSCellRadResCfgCmnUL
 *
 *@param[out]       NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
 
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCellRadResCfgCmnUL
(
NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10 *uL_Cfg_r10,
WrCellCb           *cellCb
)
{
   NhuPUSCH_ConfigCmn *puschCfg;
   NhuSoundingRS_UL_ConfigCmn *srsCfg;
   WrSib2Params *sib2       = &cellCb->sib2;
   WrSib1Params *sib1 = &cellCb->sib1;

   if (FALSE == wrEmmCb.isUlCaEnabled)
   {
      uL_Cfg_r10->pres.pres = NOTPRSNT;
   }
   else
   {
      wrFillTknU8(&uL_Cfg_r10->pres, PRSNT_NODEF);

      wrFillTknU8 (&uL_Cfg_r10->ul_FreqInfo_r10.pres, PRSNT_NODEF);

      WR_FILL_TKN_UINT( uL_Cfg_r10->ul_FreqInfo_r10.ul_CarrierFreq_r10, sib2->ulCarrierFreq);
      WR_FILL_TKN_UINT( uL_Cfg_r10->ul_FreqInfo_r10.ul_Bandwidth_r10, sib2->ulBw);
      WR_FILL_TKN_UINT( uL_Cfg_r10->ul_FreqInfo_r10.additionalSpectrumEmissionSCell_r10, 
            sib2->addlSpectrEmission);

      WR_FILL_TKN_UINT(uL_Cfg_r10->p_Max_r10, sib1->pMax);

      wrFillTknU8 (&uL_Cfg_r10->uplinkPowerCntrlCmnSCell_r10.pres, PRSNT_NODEF);
      WR_FILL_TKN_UINT(uL_Cfg_r10->uplinkPowerCntrlCmnSCell_r10.p0_NominalPUSCH_r10,
            sib2->ulPwrCtrlCfg.p0NominalPusch);
      WR_FILL_TKN_UINT(uL_Cfg_r10->uplinkPowerCntrlCmnSCell_r10.alpha_r10, sib2->ulPwrCtrlCfg.alpha);

      /* SoundingsRS UL Cfg */
      srsCfg = &(uL_Cfg_r10->soundingRS_UL_ConfigCmn_r10);
      if (sib2->srsCfg.release == 1)
      {
         WR_FILL_TKN_UINT(srsCfg->choice, SOUNDINGRS_UL_CONFIGCMN_RELEASE);
      }
      else
      {
         WR_FILL_TKN_UINT(srsCfg->choice, SOUNDINGRS_UL_CONFIGCMN_SETUP);
         WR_FILL_TKN_UINT(srsCfg->val.setup.pres, PRSNT_NODEF);
         WR_FILL_TKN_UINT(srsCfg->val.setup.srs_BandwidthConfig,
               sib2->srsCfg.srsBandwidthCfg);
         WR_FILL_TKN_UINT(srsCfg->val.setup.srs_SubfrmConfig,
               sib2->srsCfg.srsSubfrmCfg);
         WR_FILL_TKN_UINT(srsCfg->val.setup.ackNackSRS_SimultaneousTransmission,
               sib2->srsCfg.ackNackSrsSimulTx);
         srsCfg->val.setup.srs_MaxUpPts.pres = NOTPRSNT;
      }

      /* Fill UL cyclic prefix                                               */
      WR_FILL_TKN_UINT(uL_Cfg_r10->ul_CyclicPrefixLength_r10,
            sib2->ulCyclicPrefix);

      uL_Cfg_r10->prach_ConfigSCell_r10.pres.pres = NOTPRSNT;

#if 0
      uL_Cfg_r10->pusch_ConfigCmn_r10.pres.pres = NOTPRSNT;
      uL_Cfg_r10->pusch_ConfigCmn_r10.pusch_ConfigBasic.pres.pres = NOTPRSNT;
      uL_Cfg_r10->pusch_ConfigCmn_r10.ul_ReferenceSignalsPUSCH.pres.pres = NOTPRSNT;
#endif

      /* PUSCH Cfg*/
      puschCfg = &(uL_Cfg_r10->pusch_ConfigCmn_r10);
      WR_FILL_TKN_UINT(puschCfg->pres, PRSNT_NODEF);
      WR_FILL_TKN_UINT(puschCfg->pusch_ConfigBasic.pres, PRSNT_NODEF);
      WR_FILL_TKN_UINT(puschCfg->pusch_ConfigBasic.n_SB, sib2->puschCfg.nSB);
      WR_FILL_TKN_UINT(puschCfg->pusch_ConfigBasic.hoppingMode,
            sib2->puschCfg.hoppingMode);
      WR_FILL_TKN_UINT(puschCfg->pusch_ConfigBasic.pusch_HoppingOffset,
            sib2->puschCfg.hoppingOffset);
      WR_FILL_TKN_UINT(puschCfg->pusch_ConfigBasic.enable64QAM,
            sib2->puschCfg.qam64Enabled);
      WR_FILL_TKN_UINT(puschCfg->ul_ReferenceSignalsPUSCH.pres, PRSNT_NODEF);
      WR_FILL_TKN_UINT(puschCfg->ul_ReferenceSignalsPUSCH.groupHoppingEnabled,
            sib2->puschCfg.grpHoppingEnabled);
      WR_FILL_TKN_UINT(puschCfg->ul_ReferenceSignalsPUSCH.groupAssignmentPUSCH,
            sib2->puschCfg.grpAssignPusch);
      WR_FILL_TKN_UINT(puschCfg->ul_ReferenceSignalsPUSCH.sequenceHoppingEnabled,
            sib2->puschCfg.seqHoppingEnabled);
      WR_FILL_TKN_UINT(puschCfg->ul_ReferenceSignalsPUSCH.cyclicShift,
            sib2->puschCfg.cyclicShift);

   }
   RETVALUE(ROK);
}


/**
 *  @brief This function is used for filling SCell Config Common Non UL for a particular cell
 *
 *      Function: wrUtlFillAddModSCellRadResCfgCmnNonUL
 *
 *@param[out]       NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
 
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCellRadResCfgCmnNonUL
(
NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10 *nonUL_Cfg_r10,
WrCellCb           *cellCb
)
{	
   NhuAntennaInfoCmn         *antInfoCmn;	
   NhuPHICH_Config           *phichCfg;
   NhuPDSCH_ConfigCmn        *pdschCfg   = NULLP;
   WrSib2Params              *sib2       = &cellCb->sib2;	
   NhuTDD_Config             *tddCfg;
   U8                        numAntPorts = 0;
	
	wrFillTknU8(&nonUL_Cfg_r10->pres, PRSNT_NODEF);
	wrFillTknU32(&nonUL_Cfg_r10->dl_Bandwidth_r10, cellCb->mib.dlBw);

	/* Fill NhuAntennaInfoCmn IE */
   antInfoCmn = &nonUL_Cfg_r10->antennaInfoCmn_r10;
   wrFillTknU8(&(antInfoCmn->pres), PRSNT_NODEF);
   WR_GET_NUM_ANT_PORT(cellCb,numAntPorts);
   wrFillTknU32(&(antInfoCmn->antennaPortsCount), numAntPorts);

	/*to-do add MBSFN in future*/

	/* Fill NhuPHICH_Config IE */
   phichCfg = &nonUL_Cfg_r10->phich_Config_r10;
   wrFillTknU8((&phichCfg->pres), PRSNT_NODEF);
   wrFillTknU32((&phichCfg->phich_Duration),
                   cellCb->mib.phichDur);
   wrFillTknU32((&phichCfg->phich_Resource),
                   cellCb->mib.phichGrps);

   /* PDSCH Cfg */
   pdschCfg = &(nonUL_Cfg_r10->pdsch_ConfigCmn_r10);
   WR_FILL_TKN_UINT(pdschCfg->pres, PRSNT_NODEF);
   WR_FILL_TKN_UINT(pdschCfg->referenceSignalPower, sib2->pdschCfg.refSigPower);
   WR_FILL_TKN_UINT(pdschCfg->p_b, sib2->pdschCfg.pB);

   /* Fill NhuTDD_Config IE*/
   tddCfg = &nonUL_Cfg_r10->tdd_Config_r10;
#ifndef LTE_TDD
   tddCfg->pres.pres = NOTPRSNT;
#else
   WR_FILL_TKN_UINT(tddCfg->pres, PRSNT_NODEF);
   WR_FILL_TKN_UINT(tddCfg->subframeAssignment, cellCb->sib1.tddCfg.subframeCfg);
   WR_FILL_TKN_UINT(tddCfg->specialSubfrmPatterns, cellCb->sib1.tddCfg.specialSubframeCfg);
#endif	


	RETVALUE(ROK);
}

/**
 *  @brief This function is used for filling SCell Config Common for a particular cell
 *
 *      Function: wrUtlFillAddModSCellRadResCfgCmn
 *
 *@param[out]      NhuRadioResourceConfigCmnSCell_r10 *radioResourceConfigCmnSCell 
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCellRadResCfgCmn
(
NhuRadioResourceConfigCmnSCell_r10 *cfgCmnSCell,
WrCellCb           *cellCb
)
{
	wrFillTknU8(&cfgCmnSCell->pres, PRSNT_NODEF);
	if (ROK != wrUtlFillAddModSCellRadResCfgCmnNonUL(&cfgCmnSCell->nonUL_Cfg_r10, cellCb))
	{
		RLOG0(L_ERROR, "wrUtlFillAddModSCellRadResCfgCmnNonUL failed");
	   RETVALUE(RFAILED);
	}	

	/*to-do */
	if (ROK != wrUtlFillAddModSCellRadResCfgCmnUL(&cfgCmnSCell->ul_Cfg_r10, cellCb))
	{
		RLOG0(L_ERROR, "wrUtlFillAddModSCellRadResCfgCmnUL failed");
	   RETVALUE(RFAILED);
	}	
	RETVALUE(ROK);
}

/**
 *  @brief This function is used for filling SCell Config Dedicated for a particular cell
 *
 *      Function: wrUtlFillAddModSCellRadResCfgDed
 *
 *@param[out]      NhuRadioResourceConfigCmnSCell_r10 *radioResourceConfigCmnSCell 
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCellRadResCfgDed
(
NhuRadioResourceConfigDedicatedSCell_r10 *cfgDedSCell,
WrSCellInfo 			 *sCellInfo,
WrUeCb                *ueCb,
NhuDatReqSdus		*recfgMsg
)
{
	NhuPhysicalConfigDedicatedSCell_r10 *physicalConfigDedicatedSCell_r10 = 
		&cfgDedSCell->physicalConfigDedicatedSCell_r10;
	wrFillTknU8(&cfgDedSCell->pres, PRSNT_NODEF);	
	
	wrFillTknU8(&physicalConfigDedicatedSCell_r10->pres, PRSNT_NODEF);

	if (ROK != wrUtlFillAddModSCellRadResCfgDedNonUL(&physicalConfigDedicatedSCell_r10->nonUL_Cfg_r10, 
		sCellInfo, ueCb, recfgMsg))
	{
		RLOG0(L_ERROR, "wrUtlFillAddModSCellRadResCfgDedNonUL failed");
	   RETVALUE(RFAILED);
	}	

	/*to-do */
	if (ROK != wrUtlFillAddModSCellRadResCfgDedUL(&physicalConfigDedicatedSCell_r10->ul_Cfg_r10, sCellInfo, ueCb))
	{
		RLOG0(L_ERROR, "wrUtlFillAddModSCellRadResCfgDedUL failed");
	   RETVALUE(RFAILED);
	}	
    RETVALUE(ROK);
}


/**
 *  @brief This function is used for filling SCell for a particular cell
 *
 *      Function: wrUtlFillAddModSCell
 *
 *@param[in]    WrSCellInfo       *sCellInfo
  *@param[out]    NhuSCellToAddMod_r10 *member
 *
 *
 *  @return ROK/RFAILED
 */
PUBLIC S16  wrUtlFillAddModSCell
(
 NhuSCellToAddMod_r10  *member,
 WrSCellInfo           *sCellInfo,
 WrUeCb                *ueCb, 
 NhuDatReqSdus         *recfgMsg
)
{
   WrCellCb                *cellCb = NULLP; 
   WR_EMM_GET_CELLCB(cellCb, sCellInfo->sCellId);
   if(cellCb == NULLP)
   {
      RLOG1(L_DEBUG, "Error in getting WR CELL CB for cellId = %lu",(U32)sCellInfo->sCellId);
      RETVALUE(RFAILED);
   }
   RLOG1(L_ALWAYS, "SCell: sCellInfo->sCellIdx = %d", sCellInfo->sCellIdx);
   RLOG1(L_ALWAYS, "SCell: cellCb->physCellId = %d", cellCb->physCellId);
   RLOG1(L_ALWAYS, "SCell: cellCb->dlCarrierFreq = %d", cellCb->dlCarrierFreq);

   /*kw_fix*/
   wrFillTknU8(&member->pres, PRSNT_NODEF);			
   wrFillTknU32(&member->sCellIdx_r10, sCellInfo->sCellIdx);
	
	/*Fill cellIdentification_r10*/
	wrFillTknU8(&member->cellIdentification_r10.pres, PRSNT_NODEF);
	wrFillTknU32(&member->cellIdentification_r10.physCellId_r10, 
		cellCb->physCellId);	
	wrFillTknU32(&member->cellIdentification_r10.dl_CarrierFreq_r10, 
		cellCb->dlCarrierFreq);

   wrEmmCb.isUlCaEnabled = FALSE;

	/*Fill SCellConfigCommon*/
	if (ROK != wrUtlFillAddModSCellRadResCfgCmn(&member->radioResourceConfigCmnSCell_r10, cellCb))
	{
		RLOG0(L_ERROR, "wrUtlFillAddModSCellRadResCfgCmn failed");
	   RETVALUE(RFAILED);
	}

	/*Fil SCell Dedicated */	
	/*to-do */
	if (ROK != wrUtlFillAddModSCellRadResCfgDed(&member->radioResourceConfigDedicatedSCell_r10, sCellInfo, ueCb, recfgMsg))
	{
		RLOG0(L_ERROR, "wrUtlFillAddModSCellRadResCfgDed failed");
		RETVALUE(RFAILED);
	}	
	RETVALUE(ROK);
}
      
/**
 *  @brief This function gets the absolute 
 *   timer values from the enum
 *
 *      Function: wrUtlGetSCellDeActTmrVal 
 *
 *
 *  @param[in]  sCellDeActTmr     
 *  @param[in]  taTmr   
 *  @return Bool 
 */
PUBLIC Bool wrUtlGetSCellDeActTmrVal 
(
U32    sCellDeActTmr,
U32   *actTmr         
 )
{
   switch(sCellDeActTmr)
   {
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf2Enum:
         {
            *actTmr = 20;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf4Enum:
         {
            *actTmr = 40;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf8Enum:
         {
            *actTmr = 80;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf16Enum:
         {
            *actTmr = 160;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf32Enum:
         {
            *actTmr = 320;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf64Enum:
         {
            *actTmr = 640;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf128Enum:
         {
            *actTmr = 1280;   
            break;
         }
      case NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10spareEnum:
         {
            RETVALUE(FALSE);
            break;
         }
      default:
         {
            RETVALUE(FALSE);
         }
   }
   RETVALUE(TRUE);
}

/** @brief This function is used to Fill N1 PUCCh Resources
 *
 * @details
 *
 *     Function:wrUmmFillN1PucchRsr
 *
 *         Processing steps:
 *          - Fill from Ue Cb to RRC Reconfig

 *
 * @param[in] ueCb: UE CB, ReconfigMsg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrUmmFillN1PucchRes
(
 WrUeCb                          *ueCb, 
 NhuDatReqSdus                   *recfgMsg,
 NhuRadioResourceConfigDedicated *rrcCfgDed
 )
{

   RmuUePucchCfg                               *ueSCellAckN1ResCfg;
   U8                                           idx = 0;
   U8                                           n1ResLstCount = 0; 
   WrCqiRptCfg                                 *cqiRptCfg = &(ueCb->cqiRptCfg);
	NhuCQI_ReportConfig_r10         *cqiReportConfigR10 = NULLP;
   NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setupn1PUCCH_AN_CS_Lst_r10 *sCellPucchCfg;
   /* Fill the N1 resources for scell ack/nack */
   /* Need to fill the IE's */  
   sCellPucchCfg = &(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.val.channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.\
         n1PUCCH_AN_CS_Lst_r10);

   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pres,\
         PRSNT_NODEF);

   //Naveen: Filling CQI Reporting for SCell 
   cqiReportConfigR10 = &(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10);

   WR_FILL_TKN_UINT(cqiReportConfigR10->pres, PRSNT_NODEF);

   WR_FILL_TKN_UINT(cqiReportConfigR10->nomPDSCH_RS_EPRE_Offset, \
         cqiRptCfg->nomPdschRsEpreOff);

   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.choice, \
         CQI_REPORTPERIODIC_SETUP);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.pres, PRSNT_NODEF);
   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.cqi_PUCCH_ResourceIdx_r10, \
         cqiRptCfg->cqiPucchRsrcIdx);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.cqi_pmi_ConfigIdx, \
         cqiRptCfg->cqipmiCfgIdx);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup. \
         cqi_FormatIndicatorPeriodic_r10.choice, 
         CQI_FORMATINDICATORPERIODIC_WIDEBANDCQI);

   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup. \
         cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.pres, 
         PRSNT_NODEF);					

   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.simultaneousAckNackAndCQI, \
         cqiRptCfg->simulAckNackAndCQI);


   WR_FILL_TKN_UINT(cqiReportConfigR10->cqi_ReportPeriodic_r10.val.setup.ri_ConfigIdx, \
         cqiRptCfg->riCfgIdx);

  /* End of NhuCQI_ReportConfig_r10 filling */
   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pres,\
         PRSNT_NODEF);

   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.choice, PUCCH_FORMAT_R10_CHANNELSELECTION_R10);

   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.val.channelSelection_r10.pres, PRSNT_NODEF);


   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.val.channelSelection_r10.n1PUCCH_AN_CS_r10.choice,N1PUCCH_AN_CS_R10_SETUP);

   WR_FILL_TKN_UINT(rrcCfgDed->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.val.channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.pres,PRSNT_NODEF);

   ueSCellAckN1ResCfg =  &(ueCb->pucchCfgDed);

   if(ueSCellAckN1ResCfg->sCellAckN1ResTb1Count)
   {
      n1ResLstCount++;
   }
   if(ueSCellAckN1ResCfg->sCellAckN1ResTb2Count)
   {
      n1ResLstCount++;
   }

   if(!n1ResLstCount)
   {
      RLOG0(L_ERROR, " No list configured..\n");
      RETVALUE(RFAILED);
   }
   wrFillTknU16(&sCellPucchCfg->noComp, n1ResLstCount); 

   WR_GET_MEM(&(recfgMsg->memCp),(sizeof(NhuN1PUCCH_AN_CS_r10) * sCellPucchCfg->noComp.val),\
         &(sCellPucchCfg->member)); /* for 2 list */

   if(NULLP == sCellPucchCfg->member)
   {
      RLOG0(L_ERROR, " Failed to allocate memory for Pucch cfg in recfg msg \n");
      RETVALUE(RFAILED);
   }

   wrFillTknU16(&sCellPucchCfg->member[0].noComp,\
         ueSCellAckN1ResCfg->sCellAckN1ResTb1Count);

   WR_GET_MEM(&(recfgMsg->memCp), (sizeof(NhuN1PUCCH_AN_CS_r10Member) * sCellPucchCfg->member[0].noComp.val),\
         &(sCellPucchCfg->member[0].member)); /* for 2 list */

   if(NULLP == sCellPucchCfg->member[0].member)
   {
      RLOG0(L_ERROR, " Failed to allocate memory for Pucch cfg in recfg msg \n");
      RETVALUE(RFAILED);
   }

   for(idx = 0; idx < ueSCellAckN1ResCfg->sCellAckN1ResTb1Count; idx++)
   {
      wrFillTknU32(&sCellPucchCfg->member[0].member[idx],\
            ueSCellAckN1ResCfg->sCellAckN1ResTb1[idx]);
   }


   if(ueSCellAckN1ResCfg->sCellAckN1ResTb2Count)
   {
      wrFillTknU16(&sCellPucchCfg->member[1].noComp,\
            ueSCellAckN1ResCfg->sCellAckN1ResTb2Count);

      WR_GET_MEM(&(recfgMsg->memCp), (sizeof(NhuN1PUCCH_AN_CS_r10Member) * sCellPucchCfg->member[1].noComp.val),\
            &(sCellPucchCfg->member[1].member));

      if(NULLP == sCellPucchCfg->member[1].member)
      {
         RLOG0(L_ERROR, " Failed to allocate memory for Pucch cfg in recfg msg \n");
         RETVALUE(RFAILED);
      }

      for(idx = 0; idx < ueSCellAckN1ResCfg->sCellAckN1ResTb2Count; idx++)
      {
         wrFillTknU32(&sCellPucchCfg->member[1].member[idx],\
               ueSCellAckN1ResCfg->sCellAckN1ResTb2[idx]);
      }
   }

   RETVALUE(ROK);
}/* wrUmmFillN1PucchRes */
#endif /* LTE_ADV */
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
$SID$        ---      Sriky         1. initial release TotaleNodeB 
*********************************************************************91*/
