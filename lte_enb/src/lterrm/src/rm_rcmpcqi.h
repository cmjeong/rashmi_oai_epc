
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains class for configuring the CQI report.
               
     File:     rm_rcmpcqi.h

     Sid:      rm_rcmpcqi.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:40 2013

     Prg:     jbm 

*********************************************************************21*/
#ifndef RM_RCMPCQI_H_
#define RM_RCMPCQI_H_


#include "rm_cmn.h"
#include "rm_uecontext.h"

/** @brief Number of Subcarrier per resource block
 */
#define RM_NUM_SC_PER_RB            12

/** @brief Maximum number of values that N_1_CS can take (0 - 7)
 */
#define RM_MAX_NUM_N1CS             8


#define RM_BYTE_MASK_ONE            1

/** @brief  Max number of subbands per bandwith parts
 */
#define RM_MAX_NUM_SUBBANDS         4

#define RM_MSB_OF_BYTE              0x80

/* Macros for Basic Algo */

#ifdef LTE_MULTIUE 
#define RM_DFLT_CQI_RI_IDX_CM2         161//Suggested by anoop for multi UE Testing
#define RM_DFLT_CQI_RI_IDX_CM1         165//Suggested by anoop for multi UE Testing
#define WR_UMM_SR_CQI_PRD_TDD       40

#define WR_NUM_SUBFRMS_IN_FRAME     10

#define WR_NUM_TDD_UL_DL_CFG_TYPES  7

#else

#define RM_DFLT_CQI_RI_IDX          161
#endif//LTE_MULTIUE

#define RM_DFLT_CQI_FACTOR_K 	      1

#define RM_PCELL_IDX                0
#ifdef LTE_ADV
#define RM_MAX_SCELL                7
#endif  

typedef struct rmCqiResInfo
{
   U16      usCqiResIdx;
   U16      usRiCfgIdx;
   U16      usCqiCfgIdx;
   U16      usRiOffset;
}RmCqiResInfo;

typedef struct rmServingCellCqiResInfo
{
#ifdef LTE_ADV
   RmCqiResInfo cellCqiResInfo[1 + RM_MAX_SCELL];    
                                       /* Secondary Cells CQI Resource Info. \
                                       Currently we are supporting for 2 Cells \
                                       i.e only one SCell,so we will fill valid \
                                       values in only one index(0).\
                                       Index 0 will be primary cell.  */
#else
   RmCqiResInfo cellCqiResInfo[1];    
#endif
}RmServingCellCqiResInfo;

typedef enum rmRcmMri
{
   RM_RCM_MRI_1,
   RM_RCM_MRI_2,
   RM_RCM_MRI_4,
   RM_RCM_MRI_8,
   RM_RCM_MRI_16,
   RM_RCM_MRI_32,
   RM_RCM_MRI_MAX
}RmRcmMri;


class CRmRcmCqiMgr : public CRmRcmResMgr
{
public:
   CRmRcmCqiMgr(LrmCellConfigData &stCellCfg);
   ~CRmRcmCqiMgr();
	S32 rmRcmCfgCqi(CUEContext	*pobjUe);
	S32 rmRcmRecfgCqi(CUEContext  *pobjUe);
	S32 rmRcmRelCqi(CUEContext	*pobjUe);
	S32 rmRcmCfgRi(CUEContext	*pobjUe);
   void rmRcmCqiPopulateCqiResTbl();
#ifdef LTE_ADV
   S32 rmRcmScellCfgCqi(CUEContext *pobjUe);
   S32 rmRcmCfgScellApcqi(CUEContext *pobjUe,U8 sCellIdx);
#endif
private:
	RmuPcqiFormatInd  rmPcqiGetCqiFormatIndicator(CUEContext *pobjUe);
	S32 rmPcqiGetCqiPmiIdxResIdx(CUEContext *pobjUe);
	U8  rmPcqiGetCqiFactorK();
	U16 rmPcqiGetRiIdx(CUEContext *pobjUe);
	S32 rmPcqiRsrvCqiRiRes();
	S32 rmPcqiRelCqiRiRes(CUEContext *pobjUe);
   U16 rmPcqiGetRiOffset(U16 usUeIndex);
#ifdef LTE_ADV	
   U16 rmScellPcqiGetRiIdx(U8 sCellIdx,CUEContext *pobjUe);
   U16 rmScellPcqiGetRiOffset(U8 idx,U16 usUeIndex);
	S32 rmScellPcqiRelCqiRiRes(U8 idx,CUEContext *pobjUe);
#endif
private:
	U16 					   	m_usn2Pucch;
	U16							m_isDlfsEnabled;
   U16                     m_transModeUse;
   bool                    m_bSimANCqiEnb;

   U8                      m_bNumCqiPerTti;
   U8                      m_abCqiPrdctySfNum[LRM_CQI_PRDCTY_MAX];
   U16                     m_ausCqiStartOffset[LRM_CQI_PRDCTY_MAX];
   U16                     m_ausRiStartOffset[RM_RCM_MRI_MAX];
   RmServingCellCqiResInfo m_stCqiResAllocInfo[LRM_UL_DL_CONFIG_MAX][RM_RCM_MAX_UES_SUPPORTED];

   LrmCqiPrdcty            m_enCqiPrdcty;
   RmRcmMri                m_enMri;
   U16                     m_enRiPrdcty;
   U8                      m_bMaxActiveUesServed;
#ifdef LTE_ADV
   Bool                    m_bIsCaEnabled;
#endif
};

#endif /* RM_RCMPCQI_H_ */
/********************************************************************30**

           End of file:     rm_rcmpcqi.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:40 2013

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

