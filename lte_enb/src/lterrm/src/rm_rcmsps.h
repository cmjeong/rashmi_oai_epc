
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_rcmdrx.h

     Sid:      rm_rcmsps.h@@/main/TeNB_Main_BR/tenb_brcm_fdd_3.0.1_to_tdd_GA_4.0_merge/1 - Fri Sep 12 10:54:57 2014

     Prg:     jbm 

*********************************************************************21*/

#ifndef RM_RCMSPS_H_
#define RM_RCMSPS_H_

#include "rm_cmn.h"
#include "rm_uecontext.h"

#define RM_RCM_EXPLCT_REL_AFTR_DL         4
#define RM_RCM_NUM_SPS_PROC_DL            2
#define RM_RCM_SPS_PRDCT                  20

typedef struct rmRcmN1PucchRes
{
   U8             bN1PucchCnt;
   U16            usN1Pucch[RM_RCM_SPS_MAX_N1_PUCCH];
}RmRcmN1PucchRes;   

#ifdef LTE_TDD
typedef enum 
{
  RM_TDD_CONFIG0_MIN_DLUL_SF = 4,
  RM_TDD_CONFIG1_MIN_DLUL_SF = 4,
  RM_TDD_CONFIG2_MIN_DLUL_SF = 2,
  RM_TDD_CONFIG3_MIN_DLUL_SF = 3,
  RM_TDD_CONFIG4_MIN_DLUL_SF = 2,
  RM_TDD_CONFIG5_MIN_DLUL_SF = 1,
  RM_TDD_CONFIG6_MIN_DLUL_SF = 5
}RmMinDlUlSfTdd;
#endif

class CRmRcmSpsMgr : public CRmRcmResMgr
{
public:
   CRmRcmSpsMgr(LrmCellConfigData &stCellCfg);
   ~CRmRcmSpsMgr();
	void rmRcmCfgSps(CUEContext	*pobjUe);
	S32 rmRcmRelSps(CUEContext	*pobjUe);
   bool isSpsEnabled() {return m_stRmCellSpsCfg.bIsSpsEnabled;};
   bool isSpsUeRem();
   void calcMaxNumSpsUe();
   U16 rmRcmSpsPopulateN1PucchResTbl();
   void getUeN1PucchResForDl(RmuSpsConfigDl *stRmSpsDlCfg, CUEContext  *pobjUe);
private:
   LrmSpsCellConfigData        m_stRmCellSpsCfg;
   RmuSpsIntervalDl            m_eSpsIntervalDl;
   U16                         m_usExplctRelAftrDl;
   U8                          m_usNumOfConfSpsProcDl;
   RmuSpsIntervalUl            m_eSpsIntervalUl;
   RmuSpsImplctRelAftr         m_eImplctRelAftrUl;
#ifdef LTE_TDD   
   Bool                        m_bTwoIntervalCfg;
#endif   
   U16                         m_usMaxSpsUePerTti;     
   U16                         m_usMaxNumSpsUe;
   RmRcmN1PucchRes             m_stN1PucchRes[RM_RCM_MAX_UES_SUPPORTED];
   U8                          m_bMaxActiveUesServed;
};
#endif /* RM_RCMDRX_H_ */
