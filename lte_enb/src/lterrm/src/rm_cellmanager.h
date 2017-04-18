
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               

     File:     rm_cellmanager.h

     Sid:      rm_cellmanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

     Prg:      hkrishna, vkorade 

*********************************************************************21*/


#ifndef RM_CELLCONTEXT_H_
#define RM_CELLCONTEXT_H_

#include "rm_cmn.h"
/*#include "cm_lte.x"
#include "cm_lte_rrm.x"
#include "lrm.x"
#include "rmu.x"*/
#include "rgm.x"
#include "rm_admissioncontroller.h"
#include "rm_resourceconfigmanager.h"
#include "rm_rcmpcqi.h"
#include "rm_radiobearercontroller.h"
#include "rm_uemanager.h"
#include "rm_acb.h"
#include "rm_prbcongestioncontroller.h"

typedef enum 
{
   RM_ENB_STATE_UP = 0,
   RM_ENB_STATE_DOWN
}RmEnbState;

class CCellManager;
class CAccessClassBarring;

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CCellManager
{
public:
   CCellManager(LrmCellConfigData *pstCellCfg);
   void reConfigureCell(LrmCellConfiguration &stCellCfg);
   void triggerUeRelInd(U16 usCrnti, RmuRrcCause enRelCause);
   void procUeAdmitReq(RmuUeAdmitReq & stUeAdmitReq);
   void procUeRecfgReq(RmuUeRecfgReq & stUeRecfgReq);
   void procUeRelReq(RmuUeRelReq *pstUeRelReq);
   void procUeHoReq(RmuUeHoReq & stUeHoReq);
   void procUeSpsDisInd(RmuUeSpsDisInd *pstUeSpsDisInd);
   /*RRM_SP3*/
   /**
    * @brief Funtion to handle UE inactivity indication
    *
    * @detail Function to update the UE control block with UE inactivity 
    *         information based on incoming inactivity event.
    *
    * @param[in]   stUeInactInd    UE inactivity report
    *
    * @return  void
    */
   void procUeInactInd(RmuUeInactInd & stUeInactInd);
   void deleteUe(CUEContext *pUE);
   void procChangeTransMode(RgmTransModeInd *stChangeTransMode);
   S16 triggerStopPrbUsageReport();
   S16 triggerStartPrbUsageReport();

   void handlePrbRprt(RgmPrbRprtInd *prbRprt);
#if 0
   bool isUeCanBeMadeActive(CUEContext * pUE, RmuStatusInfo& stStatusInfo);
#endif

   inline U16 getbroadBandUlBandwidth();
   inline U16 getbroadBandDlBandwidth();
   inline U16 getMaxUesServed();
   inline U8 getCellID() { return m_bCellId; } ;
   inline U8 getNumTxAnt()
   {
      return m_stCellCfgInfo.bNumTxAnt;
   }

   inline void  rmInitRadioRes();

public:
   CAccessClassBarring m_objAcb;
   static Bool m_bIsGbrDrxDis;
  
   static Bool  getGbrDrxDisFlag(){return CCellManager::m_bIsGbrDrxDis;};
   static void  setGbrDrxDisFlag(Bool bIsGbrDrxDis){CCellManager::m_bIsGbrDrxDis = bIsGbrDrxDis;};
   void setEnbState(U8 enEnbState);
#ifdef LTE_ADV
   void setScellApcqi(CUEContext* pUE,U8 sCellIdx);
#endif

   /**
    * @brief Function to get cell congestion state.
    * 
    * @details This function returns the congestion state of the system.
    * 
    * @return bool
    *         Returns m_bIsCellCongested;
    */
   bool getIsCellCongested(){return m_bIsCellCongested;};

private:
   /*!< Object of UE manager class */
   CUEManager m_objUEMgr;
   /*!< Object of Admission Controller class */
   CAdmissionController m_oAdmCtrlr;
   /*!< Object of Resource configuration manager class */
   CRmRsrcCfgMgr m_objResCfgMgr;
   /*!< Object of Radio bearer controller class */
   CRBearerController m_objRBearerCtrlr;
   /*!< Object of PRB congestion class */
   CPRBCongestionController m_objPrbCongCntrl;
   /*!< Cell Identity */
   U8 m_bCellId;
   /*!< Current Cell Configuration */
   LrmCellConfigData m_stCellCfgInfo;
   /*!< Indicates if PRB reporting is configured to Scheduler */
   bool m_bIsPrbReportConfigured;
   /*!< Operating state of system */
   RmEnbState m_enEnbState;
   U8 m_dftTxMode;

   /*!< Inidicates if cell is congested */
   bool m_bIsCellCongested;

private:
   U8 getTxnModeForUe(RmuEutraCapInfo &stEutraCapInfo);
   void updateCRNTI(RmuUeRecfgReq & stUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
   void modCsgMembrShp(CUEContext * pUE, RmuUeRecfgReq & stUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
   void handleERABReq(CUEContext * pUE, RmuUeRecfgReq & stUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
   void handleUEReconfigReq(CUEContext * pUE, RmuUeRecfgReq & stUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
   void handleUECapInfo(CUEContext * pUE, RmuUeRecfgReq & stUeRecfgReq);
   RmEnbState getEnbState();
};

inline U16 CCellManager::getbroadBandUlBandwidth()
{
   return (m_stCellCfgInfo.usMaxUlBroadbandBw);
}
inline U16 CCellManager::getbroadBandDlBandwidth()
{
   return (m_stCellCfgInfo.usMaxDlBroadbandBw);
}
inline U16 CCellManager::getMaxUesServed()
{
   return (m_stCellCfgInfo.bMaxActiveUesServed);
}
inline void CCellManager::rmInitRadioRes()
{
   m_objResCfgMgr.rmRcmPopulateRadioRes();
}


#endif /* RM_CELLCONTEXT_H_ */
/********************************************************************30**

           End of file:     rm_cellmanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

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
