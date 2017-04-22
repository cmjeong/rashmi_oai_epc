
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_rcmscell.h

     Sid:      rm_rcmscell.h@@/main/TeNB_Main_BR/tenb_brcm_fdd_3.0.1_to_tdd_GA_4.0_merge/1 - Fri Sep 12 10:54:57 2014

     Prg:      mnawas

*********************************************************************21*/

#ifndef RM_RCMSCELL_H_
#define RM_RCMSCELL_H_

#include "rm_cmn.h"
#include "rm_uecontext.h"

#define RM_RCM_EXPLCT_REL_AFTR_DL         4
#define RM_RCM_NUM_SPS_PROC_DL            2
#define RM_RCM_SPS_PRDCT                  20

class CRmRcmSCellMgr:public CRmRcmResMgr
{
public:
   CRmRcmSCellMgr(LrmCellConfigData &stCellCfg);
   ~CRmRcmSCellMgr();
   U16 rmRcmSCellPopulateN1PucchResTbl(U16 n1StrtIdx);
   void rmRcmConfigureSCellAckN1Res(RmuUeRadioResCfg & stUeRadioResCfg, CUEContext *pUE);
private:
   RmuUePucchCfg               m_stSCellAckN1Res[RM_RCM_MAX_UES_SUPPORTED];
};
#endif /* RM_RCMSCELL_H_ */
