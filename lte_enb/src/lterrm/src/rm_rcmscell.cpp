
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 
               

     File:     rm_rcmscell.cpp

     Sid:      qf_rcmscell.cpp@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:42:56 2014

     Prg:      mnawas

*********************************************************************21*/

/* header include files */

#include "rm_cmn.h"
#ifdef LTE_ADV
#include "rm_rcmscell.h"
CRmRcmSCellMgr::CRmRcmSCellMgr(LrmCellConfigData &stCellCfg)
{
   cmMemset((U8 *)m_stSCellAckN1Res, 0, sizeof(m_stSCellAckN1Res));
   m_usMaxActiveUeCount = stCellCfg.bMaxActiveUesServed;
   m_usMaxDlUePerTti    = stCellCfg.usMaxDlUePerTti;
   m_usN1Pucch          = stCellCfg.usN1Pucch;
   m_enUlDlCfg          = stCellCfg.enUlDlConfig;
}

CRmRcmSCellMgr::~CRmRcmSCellMgr()
{
   //Do Nothing 
   return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// Reserving N1 pucch resources of SCELL harq feedback
//
///////////////////////////////////////////////////////////////////////////////////////////////////

U16 CRmRcmSCellMgr::rmRcmSCellPopulateN1PucchResTbl(U16 startN1Idx)
{
   U16 usMaxN1ResPerTti = 0;
   U16 usMaxN1ResPerTbPerUe = RM_RCM_MAX_SCELL_ACK_N1_PUCCH;
   U16 usMaxPucchUePerTti = 0;

   U32 cw1N1ResStartIdx = startN1Idx;

#ifdef LTE_TDD
   if(m_enUlDlCfg == LRM_UL_DL_CONFIG_1)
   {
      /* 2 DL mapped to one 1UL */
      usMaxPucchUePerTti   = m_usMaxDlUePerTti * 2; 

      if( (m_usMaxDlUePerTti * 2 ) < RM_RCM_MAX_SCELL_ACK_N1_PUCCH)
      {
         usMaxN1ResPerTbPerUe = m_usMaxDlUePerTti * 2;
      }
   }else if(m_enUlDlCfg == LRM_UL_DL_CONFIG_2)
   {
      /* 4 DL mapped to one 1UL */
      usMaxPucchUePerTti = m_usMaxDlUePerTti * 4; 
   }
#else
   /* For FDD 1 DL is mapped to 1 UL subframe */
   usMaxPucchUePerTti = m_usMaxDlUePerTti;
   
   if( m_usMaxDlUePerTti < RM_RCM_MAX_SCELL_ACK_N1_PUCCH)
   {
      usMaxN1ResPerTbPerUe = m_usMaxDlUePerTti;
   }
#endif

   usMaxN1ResPerTti = usMaxPucchUePerTti * 2 ; /* For 2 CWs*/
   /* TODO:: Validate the availablity of max resouces
    * if MaxRes > n1Pucch) return failure
    * */

   if((usMaxN1ResPerTti +  startN1Idx) > m_usN1Pucch)
   {
      printf("\n NO resources available for Scell Ack/Nack n1 resources\
            Reqd %d from %d. N1Pucch cfgd is %d\n",usMaxN1ResPerTti,\
            startN1Idx, m_usN1Pucch);
      RETVALUE(0);
   }
   for(U16 bUeIdx = 0; bUeIdx < m_usMaxActiveUeCount; bUeIdx++)                                  
   { 
      for(U8 bIdx = 0; bIdx < usMaxN1ResPerTbPerUe ; bIdx++)
      {
         /* Asigning start to max res per tti req to TB1 */
         /* Assigning from maxresperttti to Tb2*/
         m_stSCellAckN1Res[bUeIdx].sCellAckN1ResTb1[bIdx] = (U16)(startN1Idx + (cw1N1ResStartIdx % usMaxPucchUePerTti)); 
         m_stSCellAckN1Res[bUeIdx].sCellAckN1ResTb2[bIdx] = m_stSCellAckN1Res[bUeIdx].sCellAckN1ResTb1[bIdx] + usMaxPucchUePerTti; 
         cw1N1ResStartIdx++;
      }
      
      m_stSCellAckN1Res[bUeIdx].sCellAckN1ResTb1Count= usMaxN1ResPerTbPerUe;
      m_stSCellAckN1Res[bUeIdx].sCellAckN1ResTb2Count= usMaxN1ResPerTbPerUe;

      if(usMaxPucchUePerTti > RM_RCM_MAX_SCELL_ACK_N1_PUCCH)
      {/* Changing the pattern */
         cw1N1ResStartIdx = m_stSCellAckN1Res[bUeIdx].sCellAckN1ResTb1[1];
      }   
   }

   RETVALUE(usMaxN1ResPerTti + startN1Idx);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//For configuring the N1 resources for
//HARQ ACK/NACK feedback for SCells in case of F1b with channel selection
///////////////////////////////////////////////////////////////////////////////////////////////////
void CRmRcmSCellMgr::rmRcmConfigureSCellAckN1Res
	(
		RmuUeRadioResCfg & stUeRadioResCfg,
		CUEContext* pUE
	)
{
	U16    	   usUeIndex;

   usUeIndex = pUE->getUeIdx();

   stUeRadioResCfg.stPhyCfgDed.pucchCfgDed = m_stSCellAckN1Res[usUeIndex];

   /* TODO:: Need to fill the below bitmaps */
   stUeRadioResCfg.stPhyCfgDed.bPhyCfgDedResBitMap |= RM_RCM_PHY_DED_RES_CFG_SCELL_ACK_N1_RES;
   stUeRadioResCfg.bRadioResDedBitMap |= RM_RCM_PHY_DED_RES_CFG;
}

#endif /* LTE_ADV */
  
/********************************************************************30**

           End of file:     qf_rcmscell.cpp@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:42:56 2014

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
