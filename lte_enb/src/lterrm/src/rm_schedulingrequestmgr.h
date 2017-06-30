
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_resourceconfigmanager.h

     Sid:      rm_schedulingrequestmgr.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:21 2016

     Prg:     jbm 

*********************************************************************21*/

#ifndef __RM_SCHDUELING_REQUEST_MGR_H__
#define __RM_SCHDUELING_REQUEST_MGR_H__

#include "rm_cmn.h"
#include "rm_uecontext.h"


/** @brief 
 */
#define  RM_RCM_SR_PRDICITY_40MS          40
#define  RM_RCM_SR_PRDICITY_20MS          20
#define  RM_RCM_SR_START_IDX_40MS         35
#define  RM_RCM_SR_START_IDX_20MS         15
#define  RM_RCM_SR_FACTOR                 2
#define  MAX_NUM_UE_20             			20


typedef struct rmSrResAllocInfo
{
   U16      usSrResIdx;
   U16      usSrCfgIdx;
}RmSrResAllocInfo;

class CRmSchedulingReqMgr : public CRmRcmResMgr
{
public:
	CRmSchedulingReqMgr(LrmCellConfigData &stCellCfg);
	S16 configureSR(CUEContext* pUE);
   void rmRcmSrPopulateSrResTbl(U16 usSpsN1PucchResEnd);
#if 0
	S16 reConfigureSR(CUEContext* pUE);
	S16 releaseSR(CUEContext* pUE);
	S16 reserveSRRes(CUEContext* pUE);
#endif

private:
	U16 getSRResIdx(U16 bUEIdx);
	U16 getSRIdx(U16 bUEIdx);
   CmRrmDsrTransMax getDsrTransMax();

private:
	U16                  m_usN1Pucch;
	U16                  m_usSRPeriodicity;
	U16                  m_usSRStartIdx;
   U16                  m_bNumSrPerTti;
   U8                   m_abSrPrdctySfNum[LRM_SR_PRDCTY_MAX];
   U16                  m_usSrStartOffset[LRM_SR_PRDCTY_MAX];
   LrmSrPrdcty          m_enSrPrdcty;
   CmRrmDsrTransMax     m_enDsrTransMax;
   U16                  m_bMaxActiveUesServed;
   
   RmSrResAllocInfo     m_stSrResAllocInfo[LRM_UL_DL_CONFIG_MAX][RM_RCM_MAX_UES_SUPPORTED];
   

};

#endif /* __RM_SCHDUELING_REQUEST_MGR_H__ */
/********************************************************************30**

           End of file:     rm_schedulingrequestmgr.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:21 2016

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
