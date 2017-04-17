
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               

     File:     rm_cellcontroller.h

     Sid:      rm_cellcontroller.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

     Prg:      hkrishna, vkorade , jbm

*********************************************************************21*/


#ifndef _RRM_CELLCONTROLLER_H_
#define _RRM_CELLCONTROLLER_H_

#include <list>
#include <vector>
#include <map>

#include "rm_cmn.h"
#include "rm_cellContext.h"
#include "rm_mme.h"

typedef struct rmPrbAcbTbl
{
   U8                   bPrbStartThres;
   U8                   bPrbEnbThres;
   RmuAcBarringFactor   enAcbFactor;   /* Defines access class barring factor */
   RmuAcBarringTime     enAcbTime;     /* Defines Access class baring time value in seconds */
}RmPrbAcbTbl;
#define RRM_RAC_ACB_MAX_ENTRIES  16

typedef void (CRmCellController::*fsmFtnPtr)( U8*);
typedef LrmCause (CRmCellController::*smFtnPtr)(U8*);
typedef void (CRmCellController::*macFtnPtr)( U8*);

#define RM_MAX_MME_SUPPORTED  16

class CRmCellController
{
public:
   CRmCellController();
   ~CRmCellController(){};
   void processFsmMsg(U8  bEvent, U8* pbReqMsg);
   U16  processSmMsg(U8  bEvent, U8* pbReqMsg);
   void processMacMsg(U8  bEvent, U8* pbReqMsg);

   void getAcbParamsPrbUsage(U8 bAcbTblIndx, RmuAcBarringInfo *pstAcbParams);
	
   void handlePrbUsageInd(U8* pBuff);
   void handleFsmStatusInd(U8* pBuff);

#if 0
	void sendUeAdmitRsp(RmuUeAdmitReq *pstUeAdmitReq, RmuUeAdmitRsp *pstUeAdmitRsp);
	void sendUeRecfgRsp(RmuUeRecfgReq *pstUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
	void sendUeRelRsp(RmuUeRelReq *pstUeRelReq, RmuUeRelRsp *pstUeRelRsp);
	void sendUeRelInd(RmuUeRelInd *pstUeRelInd);
	void sendUeHoRsp(RmuUeHoReq *pstUeHoReq, RmuUeHoRsp *pstUeHoRsp);
	void sendCellRecfgInd(RmuCellRecfgInd *pstCellRecfgInd);
   void sendCellCfgPrbReport(RgmPrbRprtCfg   *pstPrbRprt);
#endif

   CRmCellContext* getCellCtxt(U8 bCellId);
   U8  getPrbUsageIndex(U8 bCellPrbUsage);
	void printCellCtxts();

private:
	void handleFsmUnknownEvent(U8* pBuff);
	void handleUeAdmitReq(U8* pBuff);
	void handleUeRecfgReq(U8* pBuff);
	void handleUeRelReq(U8* pBuff);
	void handleHoReq(U8* pBuff);
	void handleMmeOverloadStart(U8* pBuff);
	void handleMmeOverloadStop(U8* pBuff);

	void procMmeStatus(RmuMmeStatusInd & stMmeStatusInd);
	void procEnodebStatus(RmuEnbStatusInd & stEnbStatusInd);
	RmuMmeOvldStatus getLeastPrioMmeOveldStatus();
	RmMmeInfo* findMme(U16 usMmeId);

	LrmCause handleSmUnknownEvent(U8* pBuff);
	LrmCause handleSmEnbStaInd(U8* pBuff);
	LrmCause handleRmProtoCfgReq(U8* pBuff);
	LrmCause handleCellCfgReq(LrmCellConfiguration* stCellCfgData);
	LrmCause handleEnbCfgReq(LrmEnbConfiguration* pstRmEnbCfgData);
	LrmCause procMmeCfg(LrmMmeCfg & stMmeCfg);

	void handleMacUnknownEvent(U8* pBuff);
	void handlePrbRprtInd(U8* pBuff);

private:
	void updateMMEOverloadStatus(RmuMmeOvldStatus enMmeOvldStatus);

private:
	CMMEManger & m_rObjMMEMgr;

   std::map<U8, CRmCellContext*> m_tmCellList;
   std::map<U8, CRmCellContext*>::iterator m_itCell;
	U8 m_bMaxNumCellSupp;

	fsmFtnPtr m_ftnPtrPrcFsmMsg[EVTRMUMAX];
	smFtnPtr m_ftnPtrPrcSmMsg[EVTLRMMAX];
	macFtnPtr m_ftnPtrPrcMacMsg[EVTRGMMAX];
};

inline void CRmCellController::processFsmMsg(U8  bEvent, U8* pbReqMsg)
{
	(this->*m_ftnPtrPrcFsmMsg[bEvent])(pbReqMsg);
}

inline U16 CRmCellController::processSmMsg(U8  bEvent, U8* pbReqMsg)
{
	return ((this->*m_ftnPtrPrcSmMsg[bEvent])(pbReqMsg));
}

inline void CRmCellController::processMacMsg(U8  bEvent, U8* pbReqMsg)
{
	(this->*m_ftnPtrPrcMacMsg[bEvent])(pbReqMsg);
}


#endif /* _RRM_CELLCONTROLLER_H_ */
/********************************************************************30**

           End of file:     rm_cellcontroller.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

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
