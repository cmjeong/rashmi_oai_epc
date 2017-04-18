
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_rcmdrx.h

     Sid:      rm_rcmdrx.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:37 2013

     Prg:     jbm 

*********************************************************************21*/

#ifndef RM_RCMDRX_H_
#define RM_RCMDRX_H_


#include "rm_cmn.h"
#include "rm_uecontext.h"

#define RM_DRX_LONG_CYCLE_MIN            10
#define RM_DRX_LONG_CYCLE_MAX            2560

/*Below Macro defines the On Duration percentage in long cycle value */
#define RM_DRX_ON_DUR_PERCENT     10

/** @brief The below Macros are used to return configuration status */
#define RM_RCM_DRX_PRES           1
#define RM_RCM_DRX_ROK            2
#define RM_RCM_DRX_RFAILED        3

class CRmRcmDrxMgr : public CRmRcmResMgr
{
public:
   CRmRcmDrxMgr(LrmCellConfigData &stCellCfg);
   ~CRmRcmDrxMgr();
	S32 rmRcmCfgDrx(CUEContext	*pobjUe, U32  bResCfgMask);
	S32 rmRcmRelDrx(CUEContext	*pobjUe);
   U16 rmRcmGetDrxOffset(U16 usDrxLongCycle, U16 usCqiPmiCfgIdx, U8 bResAllocated, U16 usOnDurationTmr);
   bool isDrxEnabled() {return m_stRmCellDrxCfg.bIsDrxEnabled;};
   U16 rmRcmDrxGetOnDuration(U16 usDrxLongCycle, CmRrmDrxCfg& m_stRmDrxCfg, CUEContext *pobjUe, U16& usOnDurationTmr);
   S16 rmRcmDrxGetShortCycle(U16 usDrxLongCycle, U16 usOnDurationTmr, CmRrmDrxCfg& m_stRmDrxCfg);
   U8 rmRcmGetDrxLongCycleIdx(U16 usDrxLongCycle);
   void rmRcmDrxPopulateOnduration();
private:
   CmRrmCellDrxCfg                m_stRmCellDrxCfg;
   U16                            rmDrxONDurationTmr[16];
   U16                            rmDrxLongCycle[16];
   U16                            rmDrxShortCycle[16];
   U16                            m_usTddOnDuration;
   LrmUlDlConfig                  m_enUlDlConfig;
};

#endif /* RM_RCMDRX_H_ */
/********************************************************************30**

           End of file:     rm_rcmdrx.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:37 2013

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
