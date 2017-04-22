
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_outinterface.h

     Sid:      rm_outinterface.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:39 2013

     Prg:      hkrishna, vkorade 

*********************************************************************21*/


#ifndef RM_OUTINTERFACE_H_
#define RM_OUTINTERFACE_H_

#include "rm_cmn.h"

void rrmSendAcbParamsToFsm(RmuAcbParamInd & stAcb, U8    bCellId);
void rrmSendUeRecfgInd(RmuUeRecfgInd *pstUeRecfgInd);
void rrmSendUeAdmitRsp(RmuUeAdmitReq & stUeAdmitReq, RmuUeAdmitRsp *pstUeAdmitRsp);
void rrmSendUeRecfgRsp(RmuUeRecfgReq & stUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
void rrmSendUeRelRsp(RmuUeRelReq *pstUeRelReq, RmuUeRelRsp *pstUeRelRsp);
void rrmSendUeHoRsp(RmuUeHoReq & stUeHoReq, RmuUeHoRsp *pstUeHoRsp);

void rrmSendCellCfgPrbReport(RgmPrbRprtCfg   *pstPrbRprt);

void rrmSendCellRecfgInd(RmuCellRecfgInd *pstCellRecfgInd);
void rrmSendUeRelInd(RmuUeRelInd *pstUeRelInd);
void rrmSendUeRelInd(U8 bCellId, U16 usCrnti, RmuRrcCause enRelCause);
void rrmSendUeERabRelInd(RmuUeERabRelInd *pstUeERabRelInd);

#endif /* RM_OUTINTERFACE_H_ */
/********************************************************************30**

           End of file:     rm_outinterface.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:39 2013

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
