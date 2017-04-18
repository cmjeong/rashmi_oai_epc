
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               

     File:     rm_acb.h

     Sid:      rm_admissioncontroller.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

     Prg:      hkrishna, vkorade 

*********************************************************************21*/


#ifndef _RRM_ADMISSIONCONTROLLER_H_
#define _RRM_ADMISSIONCONTROLLER_H_


#include "rm_cmn.h"
#include "lrm.h"
#include "rm_uecontext.h"

#define RM_DEFAULT_WAIT_TIME_IN_SEC  3

class CUEManager;

class CAdmissionController
{
public:
	CAdmissionController(LrmCellConfigData & stCellCfg, CUEManager  &objUECtrlr);
	CUEContext* handleUEHOAdmission(RmuUeHoReq& StUEHoReq, RmuUeHoRsp *pstUeHoRsp);
	CUEContext* handleUEAdmission(RmuUeAdmitReq& stUEAdmReq, RmuUeAdmitRsp* pstUeAdmitRsp);
   bool admitMoSignalAsMoDataCall(RmuStatusInfo  & stStatusInfo);
   /* HCSG_DEV */
   bool checkAndUpdateUEAdmission(CUEContext* pUE);

private:
	bool admitEmergencyAndHighPriorityCall(RmuUeAdmitReq & stUEAdmReq, RmuStatusInfo & stStatusInfo);
	bool admitMoDataAndMtAccessCall(RmuStatusInfo & pstStatusInfo);
	bool admitMoSignalingCall(RmuStatusInfo  & stStatusInfo);
   /* HCSG_DEV */
	bool admitExtraUE(RmuStatusInfo & pstStatusInfo);

private:
	CUEManager & m_rObjUEMgr;
	U8 m_bWaitTime;
	U8 m_bCellId;
};

#endif /* _RRM_ADMISSIONCONTROLLER_H_ */
/********************************************************************30**

           End of file:     rm_admissioncontroller.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

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
