
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 
               

     File:     rm_schedulingrequestmgr.cpp

     Sid:      qf_schedulingrequestmgr.cpp@@/main/TeNB_Main_BR/2 - Mon Aug 11 16:56:51 2014

     Prg:     jbm , vikram korde

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=148;
/* header include files */
#include "rm_cmn.h"
#include "rmu.x"
#include "rm_schedulingrequestmgr.h"


CRmSchedulingReqMgr::CRmSchedulingReqMgr(LrmCellConfigData &stCellCfg)
{
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_5] = 5;
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_10] = 10;
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_20] = 20;
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_40] = 40;
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_80] = 80;
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_2] =  2;
   m_abSrPrdctySfNum[LRM_SR_PRDCTY_1] =  1;

   m_usSrStartOffset[LRM_SR_PRDCTY_5] = 0;
   m_usSrStartOffset[LRM_SR_PRDCTY_10] = 5;
   m_usSrStartOffset[LRM_SR_PRDCTY_20] = 15;
   m_usSrStartOffset[LRM_SR_PRDCTY_40] = 35;
   m_usSrStartOffset[LRM_SR_PRDCTY_80] = 75;
   m_usSrStartOffset[LRM_SR_PRDCTY_2] =  155;
   m_usSrStartOffset[LRM_SR_PRDCTY_1] =  157;

   m_usN1Pucch = 0;
   m_usSRPeriodicity = 0;
   m_usSRStartIdx = 0;
   m_enSrPrdcty = stCellCfg.enSrPrdcty;
   m_bNumSrPerTti = stCellCfg.usNumSrResPerTti;
   m_enDsrTransMax = stCellCfg.enDsrTransMax;
   m_enUlDlCfg = stCellCfg.enUlDlConfig;
   m_bMaxActiveUesServed = 
      (stCellCfg.bMaxActiveUesServed + stCellCfg.usMaxExtraUes);
   cmMemset((U8 *)m_stSrResAllocInfo, 0, sizeof(m_stSrResAllocInfo)); 
}


void CRmSchedulingReqMgr::rmRcmSrPopulateSrResTbl(U16  usSrResIdxStart)
{
   U8                   bSrPrdcty = m_abSrPrdctySfNum[m_enSrPrdcty];
   U16                  usNumUlSf;
   U16                  usOffsetIdx;
   U16                  usSfnSf;
   U16                  usUeIndex; 
   U16                  usSrResIdx; 
   U16                  usSrOffset[RM_RCM_MAX_OFFSET_ARRAY_SIZE];
   U16                  usAvalUlSfs[RM_RCM_MAX_OFFSET_ARRAY_SIZE];

   usNumUlSf = getAvailUlSubframeLst(bSrPrdcty, usAvalUlSfs);

   if(usNumUlSf > RM_RCM_MAX_OFFSET_ARRAY_SIZE)
   {
      RLOG3(L_WARNING,"Number of UL subframes [%d] for SR resource assignment"
            "for periodicity [%d] is more than Max supported [%d]."
            "Hence reassignig it to Max Value\n",usNumUlSf,bSrPrdcty,
            RM_RCM_MAX_OFFSET_ARRAY_SIZE);

      usNumUlSf = RM_RCM_MAX_OFFSET_ARRAY_SIZE;
   }
   
   /* Sequence the SR offsets to avoid SR-CQI collisions */
   for (usSfnSf = 0; usSfnSf < usNumUlSf; usSfnSf++)
   {

      /* UE Index is multiplied by two, to get the CQIPMI index difference of 
       * Two between two UE's. This is to accomodate the RI for the same UE in 
       * subsequent subframes and avoid the CQI-RI collision
       */
      if (usSfnSf < (RM_RCM_GET_HALF(usNumUlSf)))
      {
         usOffsetIdx = (usSfnSf * RM_RCM_SR_FACTOR) % usNumUlSf;
      }
      else
      {
         /* Offset = ( - ((UeId - (SrPrd/2)) * 2 + 1 )) % srPrd */
         usOffsetIdx = (usNumUlSf - 
                ((usSfnSf - (usNumUlSf/RM_RCM_SR_FACTOR)) * RM_RCM_SR_FACTOR
                      + RM_RCM_GET_HALF(RM_RCM_SR_FACTOR))) % usNumUlSf;
      }
      
      usSrOffset[usSfnSf] = usAvalUlSfs[usOffsetIdx];
   }

   RLOG0(L_DEBUG,"SR Resources Resever Per UE Index is as Below");
   /* Populate the SR Index table using the SR Offset Table */
   for (usUeIndex = 0, usSrResIdx = usSrResIdxStart; 
         (usUeIndex < m_bMaxActiveUesServed) && 
           (usSrResIdx < (m_bNumSrPerTti + usSrResIdxStart)); usSrResIdx++)
   {
      for (usSfnSf = 0; (usSfnSf < usNumUlSf) && 
            (usUeIndex < m_bMaxActiveUesServed); usSfnSf++)
      {
         m_stSrResAllocInfo[m_enSrPrdcty][usUeIndex].usSrResIdx = usSrResIdx;
         m_stSrResAllocInfo[m_enSrPrdcty][usUeIndex].usSrCfgIdx = 
                    usSrOffset[usSfnSf] + m_usSrStartOffset[m_enSrPrdcty];
         RLOG3(L_DEBUG,"UeIdx =%lu SR Res Idx =%lu SR Cfg Idx =%lu\n", usUeIndex,
                    m_stSrResAllocInfo[m_enSrPrdcty][usUeIndex].usSrResIdx,
                    m_stSrResAllocInfo[m_enSrPrdcty][usUeIndex].usSrCfgIdx);
         usUeIndex++;
      }
   }
   RLOG0(L_DEBUG,"End of SR resource Distribution");
}

S16 CRmSchedulingReqMgr::configureSR(CUEContext* pUE)
{
   U16 usUeIndex = pUE->getUeIdx();
	/* Configure the SR Index */
	U16 usSrIdx = getSRIdx(usUeIndex);

	/* Configure the SR Resource Index */
	U16 usSrResIdx = getSRResIdx(usUeIndex);

   CmRrmDsrTransMax enDsrTransMax = getDsrTransMax();
   
	/* Configure SR Index & SR Resource Index */
	pUE->setSrCfg(usSrIdx, usSrResIdx, enDsrTransMax);

	return ROK;
}

U16 CRmSchedulingReqMgr::getSRResIdx(U16 usUeIndex)
{
	return m_stSrResAllocInfo[m_enSrPrdcty][usUeIndex].usSrResIdx;
}

U16 CRmSchedulingReqMgr::getSRIdx(U16 usUeIndex)
{

	return m_stSrResAllocInfo[m_enSrPrdcty][usUeIndex].usSrCfgIdx;
}
 
CmRrmDsrTransMax CRmSchedulingReqMgr::getDsrTransMax()
{
	return m_enDsrTransMax;
}

/********************************************************************30**

End of file:     qf_schedulingrequestmgr.cpp@@/main/TeNB_Main_BR/2 - Mon Aug 11 16:56:51 2014

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
