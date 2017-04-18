
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 
               

     File:     rm_outinterface.cpp

     Sid:      qf_outinterface.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:34 2013

     Prg:     vkorde, jbm 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=152;

/* header include files */
#include "rm_application.h"
#include "rm_outinterface.h"

// static CRmApplication  *g_pObjRrmApp = CRmApplication::getRmAppInstance();

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendAcbParamsToFsm(RmuAcbParamInd & stAcb, U8    bCellId)
{
	RmuCellRecfgInd   *pstCellRecfgInd = (RmuCellRecfgInd*)rrmAlloc(sizeof(RmuCommonMsg));//YSM
   
  if(NULLP == pstCellRecfgInd)
  {
     RLOG0(L_FATAL, "RRM->FSM: Not able to allocate memory for CELL RECFG IND");
     return;
  }

	pstCellRecfgInd->stAcbParamInd = stAcb;
	pstCellRecfgInd->enCellRecfgType = RMU_CELL_RECFG_ACB_IND;
	pstCellRecfgInd->bCellId = bCellId;

	/* Send the Cell Reconfiguration Indication message to the FSM */
	rrmSendCellRecfgInd(pstCellRecfgInd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendUeAdmitRsp(RmuUeAdmitReq & stUeAdmitReq, RmuUeAdmitRsp *pstUeAdmitRsp)
{
	pstUeAdmitRsp->bCellId = stUeAdmitReq.bCellId;
	pstUeAdmitRsp->uiTransId = stUeAdmitReq.uiTransId;
	pstUeAdmitRsp->usCrnti = stUeAdmitReq.usCrnti;

   RLOG4(L_EVENT, "RRM->FSM: Sending the UE Admit Response"
             "CELLID:[%d] CRNTI:[%d] STATUS:[%d] CAUSE:[%d]",
              pstUeAdmitRsp->bCellId,
              pstUeAdmitRsp->usCrnti,
              pstUeAdmitRsp->stStatusInfo.enStatus,
              pstUeAdmitRsp->stStatusInfo.enCause );
	RmUiRmuUeAdmitRsp(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstUeAdmitRsp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendUeRecfgRsp(RmuUeRecfgReq & stUeRecfgReq, RmuUeRecfgRsp *pstUeRecfgRsp)
{

	pstUeRecfgRsp->bCellId = stUeRecfgReq.bCellId;
	pstUeRecfgRsp->uiTransId = stUeRecfgReq.uiTransId;
	pstUeRecfgRsp->usCrnti = stUeRecfgReq.usCrnti;

   RLOG4(L_EVENT, "RRM->FSM: Sending the UE RCFG Response"
             "CELLID:[%d] CRNTI:[%d] STATUS:[%d] CAUSE:[%d]",
              pstUeRecfgRsp->bCellId,
              pstUeRecfgRsp->usCrnti,
              pstUeRecfgRsp->stStatusInfo.enStatus,
              pstUeRecfgRsp->stStatusInfo.enCause );
	RmUiRmuUeRecfgRsp(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstUeRecfgRsp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendUeRelRsp(RmuUeRelReq *pstUeRelReq, RmuUeRelRsp *pstUeRelRsp)
{
	pstUeRelRsp->bCellId = pstUeRelReq->bCellId;
	pstUeRelRsp->uiTransId = pstUeRelReq->uiTransId;
	pstUeRelRsp->usCrnti = pstUeRelReq->usCrnti;

   RLOG4(L_EVENT, "RRM->FSM: Sending the UE Release Response"
             "CELLID:[%d] CRNTI:[%d] STATUS:[%d] CAUSE:[%d]",
              pstUeRelRsp->bCellId,
              pstUeRelRsp->usCrnti,
              pstUeRelRsp->stStatusInfo.enStatus,
              pstUeRelRsp->stStatusInfo.enCause );
	RmUiRmuUeRelRsp(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstUeRelRsp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendUeHoRsp(RmuUeHoReq & stUeHoReq, RmuUeHoRsp *pstUeHoRsp)
{
	pstUeHoRsp->bCellId = stUeHoReq.bCellId;
	pstUeHoRsp->uiTransId = stUeHoReq.uiTransId;
	pstUeHoRsp->usCrnti = stUeHoReq.usCrnti;

   RLOG4(L_EVENT, "RRM->FSM: Sending the UE HO Response"
             "CELLID:[%d] CRNTI:[%d] STATUS:[%d] CAUSE:[%d]",
         pstUeHoRsp->bCellId,
         pstUeHoRsp->usCrnti,
         pstUeHoRsp->stStatusInfo.enStatus,
         pstUeHoRsp->stStatusInfo.enCause );
	RmUiRmuUeHoRsp(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstUeHoRsp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendCellCfgPrbReport(RgmPrbRprtCfg   *pstPrbRprt)
{
   RLOG2(L_EVENT, "RRM->SCH: Send cell configuration for PRB report "
         "[CELL ID:PRB report start/stop]-[%d:%d]",
         pstPrbRprt->bCellId,
         pstPrbRprt->bConfigType);
	RmLiRgmCfgPrbRprt(&g_stRmCb.rgmSap.pst, g_stRmCb.rgmSap.suId, pstPrbRprt);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendCellRecfgInd(RmuCellRecfgInd *pstCellRecfgInd)
{
   RLOG2(L_EVENT, "RRM->FSM: [CELL ID:RECFG TYPE]-[%d:%d] CELL RECFG Indication sent",
         pstCellRecfgInd->bCellId,
         pstCellRecfgInd->enCellRecfgType);
	RmUiRmuCellRecfgInd(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstCellRecfgInd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendUeRelInd(RmuUeRelInd *pstUeRelInd)
{
   RLOG2(L_EVENT, "RRM->FSM: CELL:UE [%d:%d] UE Release Indication sent",
         pstUeRelInd->bCellId,
         pstUeRelInd->usCrnti);
	RmUiRmuUeRelInd(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstUeRelInd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rrmSendUeRelInd(U8 bCellId, U16 usCrnti, RmuRrcCause enRelCause)
{
   RmuUeRelInd* pstUeRelInd = (RmuUeRelInd*)rrmAlloc(sizeof(RmuCommonMsg));//YSM
  
  if(NULLP == pstUeRelInd)
  {
     RLOG0(L_FATAL, "RRM->FSM: Not able to allocate memory for UE REL IND ");
     return;
  }

   pstUeRelInd->enRelCause  = enRelCause;
   pstUeRelInd->usCrnti	    = usCrnti;
   pstUeRelInd->bCellId 	 = bCellId;

   RLOG2(L_EVENT, "RRM->FSM: CELL:UE [%d:%d] UE Release Indication sent",
         pstUeRelInd->bCellId,
         pstUeRelInd->usCrnti);
   /* Send the UE Release Indication message to the FSM */
   rrmSendUeRelInd(pstUeRelInd);
}

void rrmSendUeRecfgInd(RmuUeRecfgInd *pstUeRecfgInd)
{
   RmUiRmuUeRecfgInd(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId, pstUeRecfgInd);
}

void rrmSendUeERabRelInd( RmuUeERabRelInd *pstUeERabRelInd)
{
   RLOG3(L_EVENT,
         "RRM->FSM: CELL:UE:numberOfRABs [%d:%d:%d] ERAB Release Indication sent",
         pstUeERabRelInd->bCellId,
         pstUeERabRelInd->usCrnti,
         pstUeERabRelInd->stErabRelInfo.bNoErabsToRel);
   
   RLOG0(L_DEBUG, "RRM->FSM: List of RABS for Release are:");
   for (U32 indx = 0; indx < pstUeERabRelInd->stErabRelInfo.bNoErabsToRel; indx++)
   {
      RLOG2(L_DEBUG, "RAB ID [%d], CAUSE:[%d]", 
            pstUeERabRelInd->stErabRelInfo.stErabRelLst[indx].bErabId,
            pstUeERabRelInd->stErabRelInfo.stErabRelLst[indx].enErabRelCause);
   }

   RmUiRmuUeERabRelInd(&g_stRmCb.rmuSap.pst, g_stRmCb.rmuSap.suId,
   pstUeERabRelInd);
}
/********************************************************************30**

           End of file:     qf_outinterface.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:34 2013

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
