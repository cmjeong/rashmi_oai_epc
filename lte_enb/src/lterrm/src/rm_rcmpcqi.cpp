
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 
               

     File:     rm_rcmpcqi.cpp

     Sid:      qf_rcmpcqi.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:35 2013

     Prg:     jbm 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=146;
/* header include files */
#ifndef RM_RCMPCQI_CPP_
#define RM_RCMPCQI_CPP_

#include "rm_cmn.h"
#include "rm_rcmpcqi.h"

CRmRcmCqiMgr::CRmRcmCqiMgr(LrmCellConfigData &stCellCfg)
{
#ifdef LTE_TDD
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_1] = 1;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_5] = 5;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_10] = 10;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_20] = 20;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_40] = 40;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_80] = 80;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_160] = 160;
   
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_1] = 0;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_5] = 1;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_10] = 6;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_20] = 16;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_40] = 36;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_80] = 76;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_160] = 156;
#else
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_2] = 2;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_5] = 5;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_10] = 10;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_20] = 20;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_40] = 40;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_80] = 80;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_160] = 160;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_32] = 32;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_64] = 64;
   m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_128] = 128;
   
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_2] = 0;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_5] = 2;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_10] = 7;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_20] = 17;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_40] = 37;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_80] = 77;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_160] = 157;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_32] = 318;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_64] = 350;
   m_ausCqiStartOffset[LRM_CQI_PRDCTY_128] = 414;
#endif
   m_ausRiStartOffset[RM_RCM_MRI_1] = 0;
   m_ausRiStartOffset[RM_RCM_MRI_2] = 161;
   m_ausRiStartOffset[RM_RCM_MRI_4] = 322;
   m_ausRiStartOffset[RM_RCM_MRI_8] = 483;
   m_ausRiStartOffset[RM_RCM_MRI_16] = 644;
   m_ausRiStartOffset[RM_RCM_MRI_32] = 805;

   m_enUlDlCfg = stCellCfg.enUlDlConfig;
   m_enCqiPrdcty = stCellCfg.enCqiPrdcty;
   m_enMri = RM_RCM_MRI_2;
   m_bNumCqiPerTti = stCellCfg.usNumCqiResPerTti;
   m_bMaxActiveUesServed = 
      (stCellCfg.bMaxActiveUesServed + stCellCfg.usMaxExtraUes);

   m_usn2Pucch = stCellCfg.bNRbCqi * RM_NUM_SC_PER_RB + 
                  ((RM_CEIL((stCellCfg.bNCsAn), (RM_MAX_NUM_N1CS))) *
                   (RM_NUM_SC_PER_RB - stCellCfg.bNCsAn - 2));

   m_isDlfsEnabled = stCellCfg.flagDlfsScheduling;
   m_transModeUse = stCellCfg.flagTransMode;

   m_bSimANCqiEnb = stCellCfg.bSimulCqiAckNack;

   m_enRiPrdcty = RM_RCM_MRI_2;
   cmMemset((U8 *)m_stCqiResAllocInfo,0,sizeof(m_stCqiResAllocInfo));
#ifdef LTE_ADV
   m_bIsCaEnabled = stCellCfg.bIsCaEnabled;
#endif   
}

void CRmRcmCqiMgr::rmRcmCqiPopulateCqiResTbl()
{
   const U8             bCqiPrdcty = m_abCqiPrdctySfNum[m_enCqiPrdcty];
   U16                  usNumUlSf;
   U16                  usSfnSf;
   U16                  usUeIndex; 
   U16                  usCqiResIdx; 
   U16                  usCqiOffset[RM_RCM_MAX_OFFSET_ARRAY_SIZE];
   U16                  ausRiOffset[RM_RCM_MAX_OFFSET_ARRAY_SIZE];
   U16                  usAvalUlSfs[RM_RCM_MAX_OFFSET_ARRAY_SIZE];
   U16                  usCqiOffsetIdx;
   U16                  usRiOffsetIdx;
   U16                  usRiOffset;
   U8                   maxUlSfPerRes;
   usNumUlSf = getAvailUlSubframeLst(bCqiPrdcty, usAvalUlSfs);

   if(usNumUlSf > RM_RCM_MAX_OFFSET_ARRAY_SIZE)
   {
      RLOG3(L_WARNING,"Number of UL subframes [%d] for CQI resource assignment"
             "for periodicity [%d] is more than Max supported [%d]." 
             "Hence reassignig it to Max Value",usNumUlSf,bCqiPrdcty,
             RM_RCM_MAX_OFFSET_ARRAY_SIZE);

      usNumUlSf = RM_RCM_MAX_OFFSET_ARRAY_SIZE;
   }

   /* Sequence the SR offsets to avoid SR-CQI collisions */
   for (usSfnSf = 0; usSfnSf < usNumUlSf; usSfnSf++)
   {
      /* UE Index is multiplied by two, to get the CQIPMI index difference of 
       * Two between two UE's. The RI will scheduled a subframe ahead of CQI.
       * This is to accomodate the RI for the same UE in 
       * subsequent subframes and avoid the CQI-RI collision
       * Hence the RI offset is CQI - 1
       */
      usCqiOffsetIdx = (usSfnSf * RM_RCM_CQI_PMI_IDX_FACTOR_PER_CELL + RM_RCM_CQI_PMI_IDX_FACTOR_PER_CELL) % usNumUlSf;
      usRiOffsetIdx = (usCqiOffsetIdx - 1 + usNumUlSf) % usNumUlSf;

      usCqiOffset[usSfnSf] = usAvalUlSfs[usCqiOffsetIdx];
      ausRiOffset[usSfnSf]  = usAvalUlSfs[usRiOffsetIdx];
   }


   /* Populate the CQI Index table using the SR Offset Table */
   for (usUeIndex = 0, usCqiResIdx = 0; 
         (usUeIndex < m_bMaxActiveUesServed) && 
         (usCqiResIdx < m_bNumCqiPerTti); usCqiResIdx++)
   {
      /* For each UE two resources (one CQI and One RI, in different subfames)
       * will be allocated hence in the below check the usNumUlSf is 
       * divided by two.
       */
      maxUlSfPerRes = usNumUlSf/RM_RCM_CQI_PMI_IDX_FACTOR_PER_CELL ;
      for (usSfnSf = 0; (usSfnSf < maxUlSfPerRes ) && 
               (usUeIndex < m_bMaxActiveUesServed); usSfnSf++)
      {
         m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usCqiCfgIdx = 
            usCqiOffset[usSfnSf] + m_ausCqiStartOffset[m_enCqiPrdcty];

         /* Since RI will be havng the least offset we are xsaving to 
          * derive the DRX offset */
         m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usRiOffset = 
            ausRiOffset[usSfnSf];

         usRiOffset  = 
            (-1 * (((S16)(ausRiOffset[usSfnSf] - usCqiOffset[usSfnSf] 
                          - bCqiPrdcty)) % bCqiPrdcty));

         m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usRiCfgIdx = 
            usRiOffset + m_ausRiStartOffset[m_enRiPrdcty];

         m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usCqiResIdx = 
                                                   usCqiResIdx;

         /* Now for every UE, we are reserving 4 sucessive indices 
            2 indices for primary cell (one for CQI another for RI)
            2 indices for secondary cell (one for CQI another for RI)
            
            Limitation:
            1. Periodicity for primary and secondary is same.
            2. Currently spported for only one Scell

            Note: If CA is not enable, it will allocate 2 indices for 
                  every UE as earlier.
         */
#ifdef LTE_ADV
         if (m_bIsCaEnabled)
         {
            for (U8 sCellIdx = 0; sCellIdx < RM_MAX_SCELL_SUPPORTED ;sCellIdx++)
            {
               usSfnSf++;
               m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].
                  cellCqiResInfo[sCellIdx +1].usCqiCfgIdx = 
                  usCqiOffset[usSfnSf] + m_ausCqiStartOffset[m_enCqiPrdcty];

               m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].
                  cellCqiResInfo[sCellIdx +1].usRiOffset = 
                  ausRiOffset[usSfnSf];

               usRiOffset  = 
                  (-1 * (((S16)(ausRiOffset[usSfnSf] - usCqiOffset[usSfnSf] 
                                - bCqiPrdcty)) % bCqiPrdcty));

               m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].
                  cellCqiResInfo[sCellIdx +1].usRiCfgIdx = 
                  usRiOffset + m_ausRiStartOffset[m_enRiPrdcty];

               m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].
                  cellCqiResInfo[sCellIdx +1].usCqiResIdx = usCqiResIdx;
            }
         }
#endif
         usUeIndex++;
      }
   }

}

CRmRcmCqiMgr::~CRmRcmCqiMgr()
{
}

#ifdef LTE_ADV
S32 CRmRcmCqiMgr::rmRcmCfgScellApcqi(CUEContext *pobjUe,U8 sCellIdx)
{
	RmuPcqiFormatInd  enUeCqiFormat;

   U32 uiTxnMode = (U32)pobjUe->getUeTxnMode();
	/* configure the CQI Format Indicator */
	enUeCqiFormat = rmPcqiGetCqiFormatIndicator(pobjUe);
   if(enUeCqiFormat != RMU_PCQI_FMT_WIDEBAND)
	{
      /* if UE is SB CQI reporting capable and cell DLFSS enabled then 
       * Aperiodic SB CQI reporting is configured. */
      if(uiTxnMode == RM_UE_TXN_MODE4)
      {
         pobjUe->setUeScellAperiodicCqi(RMU_APRD_CQI_MODE31,sCellIdx);
      }
      else
      {
         pobjUe->setUeScellAperiodicCqi(RMU_APRD_CQI_MODE30,sCellIdx);
      }   
	}
   else
   {
      /* Enabling A-CQi in case of CA inorder to handle the below
       * mentioned scenario::
       * UE drops reporting CQI in case of F1BCS+CQI if there
       * was data on secondary cell. This leads to missing of CQI
       * */
      if((pobjUe->getUePcqiSubbandSupp()) && (pobjUe->getUeCaCap()))
      {
         if(uiTxnMode == RM_UE_TXN_MODE4)
         {
            printf("\n RRM_ACQI_DBG::Setting Mode 31 for scell.....\n");
            pobjUe->setUeScellAperiodicCqi(RMU_APRD_CQI_MODE31,sCellIdx);
         }
         else
         {
            printf("\n RRM_ACQI_DBG::Setting Mode 30 for scell.....\n");
            pobjUe->setUeScellAperiodicCqi(RMU_APRD_CQI_MODE30,sCellIdx);
         }   
      }
   }

   
	return ROK;
}
#endif

S32 CRmRcmCqiMgr::rmRcmCfgCqi(CUEContext *pobjUe)
{
	RmuPcqiFormatInd  enUeCqiFormat;
	U32               uiFactorK;
	U32               uiTxnMode;
	U32               uiRiIndex;
	/* configure the CQI Format Indicator */
	enUeCqiFormat = rmPcqiGetCqiFormatIndicator(pobjUe);

	pobjUe->setUePCqiFormat(enUeCqiFormat);

	/* Configure the CQI PMI Index and Resourfce Index */
	rmPcqiGetCqiPmiIdxResIdx(pobjUe);
   
   /* Configure the RI Index */
   uiTxnMode = (U32)pobjUe->getUeTxnMode();
	/* Configure the Factor K */
	if(enUeCqiFormat != RMU_PCQI_FMT_WIDEBAND)
	{
      if(uiTxnMode == RM_UE_TXN_MODE4)
      {
         pobjUe->setUePeriodicCqi(RMU_CQI_MODE21);
         pobjUe->setUeAperiodicCqi(RMU_APRD_CQI_MODE31);
      }
      else
      {
      pobjUe->setUePeriodicCqi(RMU_CQI_MODE20);
      /* if UE is SB CQI reporting capable and cell DLFSS
       * enabled then Aperiodic SB CQI reporting is configured. */
      /* Note: Only Mode 3-0 supported */
		pobjUe->setUeAperiodicCqi(RMU_APRD_CQI_MODE30);
      }
		uiFactorK = rmPcqiGetCqiFactorK();

		pobjUe->setUeCqiFactorK(uiFactorK);
      pobjUe->setSubbandCQIPeriodicityFactor(RMU_PERIODICITY_FACTOR_N2);
	}
   else
   {
#ifdef LTE_ADV
      /* Enabling A-CQi in case of CA inorder to handle the below
       * mentioned scenario::
       * UE drops reporting CQI in case of F1BCS+CQI if there
       * was data on secondary cell. This leads to missing of CQI
       * */
      if((pobjUe->getUePcqiSubbandSupp()) && (pobjUe->getUeCaCap()))
      {
         if(uiTxnMode == RM_UE_TXN_MODE4)
         {
            pobjUe->setUeAperiodicCqi(RMU_APRD_CQI_MODE31);
         }
         else
         {
            pobjUe->setUeAperiodicCqi(RMU_APRD_CQI_MODE30);
         }
      }
#endif
      if(uiTxnMode == RM_UE_TXN_MODE4)
      {
         pobjUe->setUePeriodicCqi(RMU_CQI_MODE11);
      }
      else
      {
         pobjUe->setUePeriodicCqi(RMU_CQI_MODE10);
      }
   }


	if((uiTxnMode == RM_UE_TXN_MODE3) ||
			(uiTxnMode == RM_UE_TXN_MODE4))
	{
		uiRiIndex = rmPcqiGetRiIdx(pobjUe);

		pobjUe->setUeCqiRiIndex(uiRiIndex, TRUE);
	}
	else
	{
		pobjUe->setUeCqiRiIndex(0, FALSE);
	}   

	rmPcqiRsrvCqiRiRes();

	pobjUe->setSimCqiAckSupp(m_bSimANCqiEnb);

   pobjUe->setUeCqiRprtInfo();

   pobjUe->setUeRiOffset(rmPcqiGetRiOffset(pobjUe->getUeIdx()));

	return ROK;
}
#ifdef LTE_ADV
S32 CRmRcmCqiMgr::rmRcmScellCfgCqi(CUEContext *pobjUe)
{
	U16    	   usUeIndex;
	U16 			usCqiPmiIdx;
	U16  			usCqiResIdx;
   U32         uiTxnMode;
   U8          sCellIdx;
	U32         uiRiIndex;

   usUeIndex = pobjUe->getUeIdx();
   for (sCellIdx = 0;sCellIdx < RM_MAX_SCELL_SUPPORTED;sCellIdx++)
   {
      /* Copy all the config from Pcell to Scell*/
      pobjUe->setUeScellCqi(sCellIdx);
      
      /*Set CQI PMI Cfg Index*/
      usCqiPmiIdx	= m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].
         cellCqiResInfo[sCellIdx +1].usCqiCfgIdx;

      usCqiResIdx = m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].
         cellCqiResInfo[sCellIdx +1].usCqiResIdx;

      pobjUe->setUeScellCqiPmiIdxResIdx(sCellIdx,usCqiPmiIdx, usCqiResIdx);

      /* Configure the RI Index */
      uiTxnMode = (U32)pobjUe->getUeTxnMode();

      if((uiTxnMode == RM_UE_TXN_MODE3) ||
            (uiTxnMode == RM_UE_TXN_MODE4))
      {
         uiRiIndex = rmScellPcqiGetRiIdx(sCellIdx, pobjUe);

         pobjUe->setUeScellCqiRiIndex(sCellIdx,uiRiIndex, TRUE);
      }
      else
      {
         pobjUe->setUeScellCqiRiIndex(sCellIdx,0, FALSE);
      }
      /*Increment UE Scell num*/
      pobjUe->incUeScellNum();
      /*Currently we are supporting for only one SCell*/
      break;
   }
	return ROK;
}

U16 CRmRcmCqiMgr::rmScellPcqiGetRiOffset(U8 idx,U16 usUeIndex)
{
   return m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[idx +1].usRiOffset;
}

#endif

U16 CRmRcmCqiMgr::rmPcqiGetRiOffset(U16 usUeIndex)
{
   return m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usRiOffset;
}

S32 CRmRcmCqiMgr::rmRcmRecfgCqi(CUEContext *pobjUe)
{
	rmRcmRelCqi(pobjUe);

	rmRcmCfgCqi(pobjUe);
#ifdef LTE_ADV
   /* Configure CQI/PMI/RI resource for Scells*/
   rmRcmScellCfgCqi(pobjUe);
#endif

	return ROK;
}

S32 CRmRcmCqiMgr::rmRcmRelCqi(CUEContext *pobjUe)
{
	rmPcqiRelCqiRiRes(pobjUe);
#ifdef LTE_ADV
   /* Reset CQI resource for all the configured Scells*/
   for (U8 idx =0;idx < RM_MAX_SCELL_SUPPORTED;idx++)
   {
      rmScellPcqiRelCqiRiRes(idx,pobjUe);
   }
#endif
	return ROK;
}

S32 CRmRcmCqiMgr::rmPcqiGetCqiPmiIdxResIdx
(
   CUEContext  *pobjUe
)
{
	U16    	   usUeIndex;
	U16 			usCqiPmiIdx;
	U16  			usCqiResIdx;

   usUeIndex = pobjUe->getUeIdx();
   usCqiPmiIdx	= m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usCqiCfgIdx;

	usCqiResIdx = m_stCqiResAllocInfo[m_enCqiPrdcty][usUeIndex].cellCqiResInfo[RM_PCELL_IDX].usCqiResIdx;

	pobjUe->setUeCqiPmiIdxResIdx(usCqiPmiIdx, usCqiResIdx);

	return ROK;
}

U8 CRmRcmCqiMgr::rmPcqiGetCqiFactorK()
{
	return RM_DFLT_CQI_FACTOR_K;
}

U16 CRmRcmCqiMgr::rmPcqiGetRiIdx(CUEContext	*pobjUe)
{
	return m_stCqiResAllocInfo[m_enCqiPrdcty][pobjUe->getUeIdx()].
                           cellCqiResInfo[RM_PCELL_IDX].usRiCfgIdx;
}

#ifdef LTE_ADV
U16 CRmRcmCqiMgr::rmScellPcqiGetRiIdx(U8 idx, CUEContext	*pobjUe)
{
   if (idx <  RM_MAX_SCELL)
   {
      return m_stCqiResAllocInfo[m_enCqiPrdcty][pobjUe->getUeIdx()].
         cellCqiResInfo[1+idx].usRiCfgIdx;
   }
   else
   {
      /* Should not come here*/
      return 0;
   }
}
S32 CRmRcmCqiMgr::rmScellPcqiRelCqiRiRes(U8 idx,CUEContext	*pobjUe)
{
	pobjUe->resetUeScellPCqiRprtInfo(idx);
	return ROK;
}
#endif

S32 CRmRcmCqiMgr::rmPcqiRsrvCqiRiRes()
{
	return ROK;
}
S32 CRmRcmCqiMgr::rmPcqiRelCqiRiRes(CUEContext	*pobjUe)
{
	pobjUe->resetUePCqiRprtInfo();
	return ROK;
}

RmuPcqiFormatInd CRmRcmCqiMgr::rmPcqiGetCqiFormatIndicator(CUEContext *pobjUe)
{
   Bool                       isUeSuppSbCqi;

	isUeSuppSbCqi = pobjUe->getUePcqiSubbandSupp();

	if(!(isUeSuppSbCqi & m_isDlfsEnabled))
	{
		return RMU_PCQI_FMT_WIDEBAND;
	}
	else
	{
		return RMU_PCQI_FMT_SUBBAND;
	}
}

#endif /* RM_RCMPCQI_CPP_ */
/********************************************************************30**

           End of file:     qf_rcmpcqi.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:35 2013

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
*********************************************************************91*/
