
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_resourceconfigmanager.h

     Sid:      rm_resourceconfigmanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:37 2013

     Prg:     jbm 

*********************************************************************21*/

#ifndef RM_RSRCCFGMGR_H_
#define RM_RSRCCFGMGR_H_

#include "rm_cmn.h"
#include "rm_rcmpcqi.h"
#include "rm_rcmdrx.h"
#include "rm_schedulingrequestmgr.h"
#include "rm_rcmsps.h"
#ifdef LTE_ADV
#include "rm_rcmscell.h"
#endif


/** @brief The below macros are the mask for the RCM resource config type
 */
#define RM_RCM_RES_CFG_SR           0x01
#define RM_RCM_RES_CFG_CQI          0x02
#define RM_RCM_RES_CFG_DRX          0x04
#define RM_RCM_RES_CFG_SRS          0x08
#define RM_RCM_RES_CFG_RI           0x10
#define RM_RCM_RES_CFG_DRX_REL      0x20
#define RM_RCM_RES_CFG_SR_REL       0x40
#define RM_RCM_RES_CFG_CQI_REL      0x80
#define RM_RCM_RES_CFG_SRS_REL      0x100
#define RM_RCM_RES_CFG_SPS          0x200
#define RM_RCM_RES_REL_SPS          0x400
#define RM_RCM_RES_CFG_TX_MODE      0x800

/** @brief This represents the number of resource configuration type supported
 * in RRM
 */
#define RM_RCM_MAX_RES_CFG_TYPE     4


/* macros for the Ranges of balues for RCM Weightage and Level Mappign tables */


#if 0
class CRmRcmAlgo
{
public:
	virtual U32 rmRcmGetResToCfg(U8 bRecfgType,CUEContext *pUE, Bool bIsDrxEnabled) = 0;
   virtual ~CRmRcmAlgo() = 0;
};

class CRmRcmAlgoBasic : public CRmRcmAlgo

#endif

class CRmRcmAlgoBasic 
{
public:
	U32 rmRcmGetResToCfg (U8 bRecfgType, CUEContext	*pUE , Bool bIsDrxEnabled, Bool bIsSpsEnabled, Bool usNumSpsUe);
   virtual ~CRmRcmAlgoBasic() {};
};


class CRmRsrcCfgMgr
{
public:
   CRmRsrcCfgMgr(LrmCellConfigData &stCellCfg);

   S32 rmRcmCfgUeRes(CUEContext* pUE, RmuUeRadioResCfg	&stUeRadioResCfg);
   S32 rmRcmRecfgUeRes(CUEContext* pUE, RmuUeRecfgReq & stUeReCfgReq,RmuUeRecfgRsp *pstUeRecfgRsp);
   S32 rmRcmRecfgUeRes(CUEContext* pUE, RmuUeHoReq & stUeHoReq, RmuUeHoRsp *pstUeHoRsp);
   S32 rmRcmProcTxnModeInd(CUEContext* pUE,RmuUeRadioResCfg  &stUeRadioResCfg );

   S32 rmRcmRelUeRes(CUEContext	*pUE);
#ifdef RRM_UNUSED_FUNC
   S32 rmRcmModCellRes();
#endif
   void rmRcmPopulateRadioRes();
   void rmRcmSpsDisInd(CUEContext* pUE);
#ifdef LTE_ADV
   void setScellApcqi(CUEContext* pUE,U8 sCellIdx);
#endif
private:
	S32 configureUeResources(CUEContext* pUE, Bool bSCellActN1Req,  RmuUeRadioResCfg & stUeRadioResCfg);
	void configurePCQI(U8 bResCfgMask, RmuUeRadioResCfg & stUeRadioResCfg, CUEContext* pUE);
	void configureTxnMode(U32 bResCfgMask, RmuUeRadioResCfg & stUeRadioResCfg, CUEContext* pUE);
	void configureDRX(U8 bResCfgMask, RmuUeRadioResCfg & stUeRadioResCfg, CUEContext* pUE);
	void configureSR(U8 bResCfgMask, RmuUeRadioResCfg & stUeRadioResCfg, CUEContext* pUE);
	void configureSPS(U32 bResCfgMask, RmuUeRadioResCfg & stUeRadioResCfg, CUEContext* pUE);

private:
	CRmRcmAlgoBasic		m_objRcmAlgoInfo;
	CRmRcmCqiMgr 			m_objRcmCqiMgr;
   CRmRcmDrxMgr         m_objRcmDrxMgr;
	CRmSchedulingReqMgr	m_objSRMgr;
   CRmRcmSpsMgr         m_objRcmSpsMgr; 
#ifdef LTE_ADV
   CRmRcmSCellMgr       m_objRcmSCellMgr;
#endif
	LrmCellBandwidth		m_enDlBw;
	U8						   m_bN2Rb;
	U8						   m_bN1Cs;
   U8                   m_bRcmAlgoType;
#ifdef LTE_ADV/* Sprint 3*/
   Bool                 m_bIsCaEnabled;
#endif
};

#endif /* RM_RSRCCFGMGR_H_ */
/********************************************************************30**

           End of file:     rm_resourceconfigmanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:37 2013

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
