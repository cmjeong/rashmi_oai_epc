
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 

     File:     rm_rbadmissioncontroller.cpp

     Sid:      qf_rbadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:04 2016

     Prg:      Amit Ghosh

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=159;

#include "rm_rbadmissioncontroller.h"
#include "rm_utils.h"
#include "rm_cellmanager.h"

CRBAdmissionController::CRBAdmissionController(
                        LrmCellConfigData &stCellCfg,
                        CCellManager *pstObjCellMngr):
                        m_objPrbAdmissionController(stCellCfg),
                        m_objQciAdmissionController(stCellCfg)
{
   m_pstCellMngr = pstObjCellMngr;
}

void CRBAdmissionController::canModifyRBsBeAdmitted(CUEContext *pUE,
                                                RmuErabConfigIe & stERAB, 
                                                RrmRbcRspInfo & erabRbcRspInfo)
{
   /* check QCI requirements of the incoming bearer */
   if(false == m_objQciAdmissionController.canModifyRBsBeAdmitted(pUE,
                                                                stERAB,
                                                                erabRbcRspInfo))
   {
      m_objPrbAdmissionController.updatePrbUsageForRejErabs(stERAB,
                                                            erabRbcRspInfo);
      return;
   }

   /* if the system is congested, no need to check if PRB criteria is 
    * satisfied */
   if(true == m_pstCellMngr->getIsCellCongested())
   {
      RLOG_ARG0(L_INFO, DBG_CRNTI, pUE->getCRNTI(),
            "Cell is Congested. Rejecting all bearers");
      addAllAccptErabsToRejList(stERAB, erabRbcRspInfo);
      m_objPrbAdmissionController.updatePrbUsageForRejErabs(stERAB,
                                                            erabRbcRspInfo);
      return;
   }

   m_objPrbAdmissionController.updatePrbUsageForRejErabs(stERAB,
                                                         erabRbcRspInfo);

   /* check current PRB usage in the system */
   m_objPrbAdmissionController.canModifyRBsBeAdmitted(pUE,
                                                      stERAB,
                                                      erabRbcRspInfo);
}

void CRBAdmissionController::canRBsBeAdmitted(CUEContext *pUE, 
                                              RmuErabConfigIe & stERAB, 
                                              RrmRbcRspInfo & erabRbcRspInfo)
{
   /* check QCI requirements of the incoming bearer */
   if(false == m_objQciAdmissionController.canRBsBeAdmitted(stERAB,
                                                            erabRbcRspInfo))
   {
      m_objPrbAdmissionController.updatePrbUsageForRejErabs(stERAB,
                                                            erabRbcRspInfo);
      return;
   }

   /* if the system is congested, no need to check if PRB criteria is 
    * satisfied */
   if(true == m_pstCellMngr->getIsCellCongested())
   {
      RLOG_ARG0(L_INFO, DBG_CRNTI, pUE->getCRNTI(),
            "Cell is Congested. Rejecting all bearers");
      addAllAccptErabsToRejList(stERAB, erabRbcRspInfo);
      m_objPrbAdmissionController.updatePrbUsageForRejErabs(stERAB,
                                                            erabRbcRspInfo);
      return;
   }

   m_objPrbAdmissionController.updatePrbUsageForRejErabs(stERAB,
                                                         erabRbcRspInfo);

   /* check current PRB usage in the system */
   m_objPrbAdmissionController.canRBsBeAdmitted(stERAB,
                                                erabRbcRspInfo);
}

void CRBAdmissionController::rbReleaseInd(U32 uiQci)
{
   m_objQciAdmissionController.rbReleaseInd(uiQci);
}

S16 CRBAdmissionController::triggerPrbReportConfig(U8 cellId, U32 action)
{
   RETVALUE(m_objPrbAdmissionController.triggerPrbReportConfig(cellId, action));
}

void CRBAdmissionController::rbAdditionInd(U32 uiQci)
{
   m_objQciAdmissionController.rbAdditionInd(uiQci);
}

void CRBAdmissionController::addAllAccptErabsToRejList(
                                              RmuErabConfigIe & stERAB, 
                                              RrmRbcRspInfo & erabRbcRspInfo)
{
   U32   bNumErabsAdmitted = erabRbcRspInfo.nErabsAccepted;
   U32   bNumErabsRejected = erabRbcRspInfo.nErabsRejected;
   RrmErabAdmitted   *pAcceptLst = erabRbcRspInfo.eRabAcceptedLst;
   RrmErabRejected   *pRejectLst = erabRbcRspInfo.eRabRejectedLst;

   for(U32 uiRbIdx = 0; uiRbIdx < erabRbcRspInfo.nErabsAccepted; uiRbIdx++)
   {
      U8  bErabId = pAcceptLst[uiRbIdx].bERabId;
      RmuUErabAddModIe *stRbAddMod = getRbAddModIe(stERAB, bErabId);
      if(stRbAddMod == NULL)
      {
         RLOG_ARG1(L_ERROR, DBG_CRNTI, erabRbcRspInfo.usCRNTI,
               "ErabId %d not found", bErabId);
         continue;
      }
      U8  bQci = stRbAddMod->stErabQosInfo.bErabQCI;

      if(isGbrBearer(bQci))
      {
         pAcceptLst[uiRbIdx].bERabId = 0;
         bNumErabsAdmitted--;
         /* add to reject list */
         pRejectLst[bNumErabsRejected].bERabId = bErabId;
         pRejectLst[bNumErabsRejected].bCause =
            RMU_CAUSE_RADIO_RESOURCE_NOT_AVAIL;
         pRejectLst[bNumErabsRejected].uiQci = 
            stRbAddMod->stErabQosInfo.bErabQCI;
         /* Update ARP value */
         pRejectLst[bNumErabsRejected].bArpVal = 
            stRbAddMod->stErabQosInfo.stErabArpInfo.bErabPrioLvl;
         pRejectLst[bNumErabsRejected].bIsPreemptable = 
            stRbAddMod->stErabQosInfo.stErabArpInfo.bErabPreemptVul;
         pRejectLst[bNumErabsRejected].bErabPreemptCap = 
            stRbAddMod->stErabQosInfo.stErabArpInfo.bErabPreemptCap;
         bNumErabsRejected++;
      }
   }

   if(erabRbcRspInfo.nErabsAccepted != bNumErabsAdmitted)
   {
      /* update number of admitted and rejected bearers to rbc response */
      erabRbcRspInfo.nErabsAccepted = bNumErabsAdmitted;
      erabRbcRspInfo.nErabsRejected = bNumErabsRejected;
      m_objPrbAdmissionController.reorderAcceptList(erabRbcRspInfo);
   }

   RLOG_ARG2(L_DEBUG, DBG_CRNTI, erabRbcRspInfo.usCRNTI,
         "Number of Admitted/Rejected ERAB:: [%d, %d]",
         bNumErabsAdmitted, bNumErabsRejected);

   return;
}

/********************************************************************30**

           End of file:     qf_rbadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:04 2016

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


