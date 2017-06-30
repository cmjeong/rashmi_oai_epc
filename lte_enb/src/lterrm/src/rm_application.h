
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               

     File:     rm_application.h

     Sid:      rm_application.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

     Prg:      hkrishna , jbm, vkorade

*********************************************************************21*/


#ifndef _RRM_CELLCONTROLLER_H_
#define _RRM_CELLCONTROLLER_H_

#include <list>
#include <vector>
#include <map>

#include "rm_cmn.h"
#include "lrm.x"
#include "rmu.x"
#include "rm_cellmanager.h"
#include "rm_mmemanager.h"


#define RM_RCM_NUM_N2PUCCH_PER_UE  2 

#define RM_NUM_SF_PER_SFN   10

typedef struct rmPrbAcbTbl
{
   U8                   bPrbStartThres;
   U8                   bPrbEnbThres;
   CmRrmAcBarringFactor enAcbFactor;   /* Defines access class barring factor */
   CmRrmAcBarringTime   enAcbTime;     /* Defines Access class baring time value in seconds */
}RmPrbAcbTbl;
#define RRM_RAC_ACB_MAX_ENTRIES  16

class CRrmApplication;
typedef void (CRrmApplication::*fsmFtnPtr)( U8*);
typedef LrmCause (CRrmApplication::*smFtnPtr)(U8*);
typedef void (CRrmApplication::*macFtnPtr)( U8*);
extern CRrmApplication & g_rObjRRMApp;

#define RM_MAX_MME_SUPPORTED  16

class CRrmApplication
{
public:
   CRrmApplication();
   ~CRrmApplication(){};
   void processFsmMsg(U8  bEvent, U8* pbReqMsg);
   U16  processSmMsg(U8  bEvent, U8* pbReqMsg);
   void processMacMsg(U8  bEvent, U8* pbReqMsg);
   void procDelUe(U32 bCellId, CUEContext *pCandidateUE);
   void getAcbParamsPrbUsage(U8 bAcbTblIndx, CmRrmAcbInfo *pstAcbParams);
#ifdef RRM_UNUSED_FUNC
   void handlePrbUsageInd(U8* pBuff);
#endif
   void handleFsmStatusInd(U8* pBuff);
   static CRrmApplication & getInstance();
   CCellManager* getCellCtxt(U8 bCellId);

#if 0
   void sendUeAdmitRsp(RmuUeAdmitReq *pstUeAdmitReq, RmuUeAdmitRsp *pstUeAdmitRsp);
   void sendUeRecfgRsp(RmuUeRecfgReq *pstUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp);
   void sendUeRelRsp(RmuUeRelReq *pstUeRelReq, RmuUeRelRsp *pstUeRelRsp);
   void sendUeRelInd(RmuUeRelInd *pstUeRelInd);
   void sendUeHoRsp(RmuUeHoReq *pstUeHoReq, RmuUeHoRsp *pstUeHoRsp);
   void sendCellRecfgInd(RmuCellRecfgInd *pstCellRecfgInd);
   void sendCellCfgPrbReport(RgmPrbRprtCfg   *pstPrbRprt);
#endif

private:
#ifdef RRM_UNUSED_FUNC
   U8  getPrbUsageIndex(U8 bCellPrbUsage);
#endif
   void printCellCtxts();

private:
   void handleFsmUnknownEvent(U8* pBuff);
   void handleUeAdmitReq(U8* pBuff);
   void handleUeRecfgReq(U8* pBuff);
   void handleUeRelReq(U8* pBuff);
   void handleHoReq(U8* pBuff);
   void handleMmeOverloadStart(U8* pBuff);
   void handleMmeOverloadStop(U8* pBuff);
   void handleUeSpsDisInd(U8* pBuff);
   /*RRM_SP3*/
   /**
    * @brief Funtion to handle UE inactivity indication
    *
    * @detail Function to trigger UE inactivity handler in cell manager.
    *
    * @param[in]   pBuff    UE inactivity report
    *
    * @return  void
    */
   void handleUeInactInd(U8* pBuff);

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
   void handleTransModeChangeInd(U8* pBuff);
private:
   void updateMMEOverloadStatus(RmuMmeOvldStatus enMmeOvldStatus);

private:
   static CRrmApplication m_oRrmApplication;

   CMMEManger & m_rObjMMEMgr;


   std::map<U8, CCellManager*> m_tmCellList;
   std::map<U8, CCellManager*>::iterator m_itCell;
   CCellManager* m_pCellMgr;
   U8 m_bMaxNumCellSupp;

   fsmFtnPtr m_ftnPtrPrcFsmMsg[EVTRMUMAX];
   smFtnPtr m_ftnPtrPrcSmMsg[EVTLRMMAX];
   macFtnPtr m_ftnPtrPrcMacMsg[EVTRGMMAX];
};


inline void CRrmApplication::processFsmMsg(U8  bEvent, U8* pbReqMsg)
{
   (this->*m_ftnPtrPrcFsmMsg[bEvent])(pbReqMsg);

   if(bEvent == EVTRMUUEINACTIND)
   {
      RM_FREE_SHAREBLE_BUF(pbReqMsg, sizeof(RmuCommonMsg))
   }
   else
   {
     rrmFree(pbReqMsg, sizeof(RmuCommonMsg));
   }
}
inline void CRrmApplication::procDelUe(U32 bCellId, CUEContext *pCandidateUE)
{

	m_pCellMgr = getCellCtxt(bCellId);

	if( m_pCellMgr )
	{
		m_pCellMgr->deleteUe(pCandidateUE);
	}
}
inline U16 CRrmApplication::processSmMsg(U8  bEvent, U8* pbReqMsg)
{
   return ((this->*m_ftnPtrPrcSmMsg[bEvent])(pbReqMsg));
}

inline void CRrmApplication::processMacMsg(U8  bEvent, U8* pbReqMsg)
{
   (this->*m_ftnPtrPrcMacMsg[bEvent])(pbReqMsg);
}


#endif /* _RRM_CELLCONTROLLER_H_ */
/********************************************************************30**

           End of file:     rm_application.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:38 2013

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
