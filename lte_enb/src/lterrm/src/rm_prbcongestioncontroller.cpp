
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 

     File:     rm_prbcongestioncontroller.cpp

     Sid:      qf_prbcongestioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/11 - Mon Feb 15 12:52:06 2016

     Prg:     sprasad, anandyal, hkrishna

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=154;

/** @file rm_prbcongestioncontroller.cpp
 * @brief This file contains the implementation of PRB congestion collector 
 *        class functions.
 */
#include "rm_radiobearercontroller.h"
#include "rm_prbcongestioncontroller.h"
#include "rm_outinterface.h"
#include "rm_prbreportcollector.h"

U32 CPRBCongestionController::convertBwToPrb(LrmCellBandwidth cellBw)
{
   U32 prb = 100;

   switch(cellBw)
   {
      case LRM_BANDWIDTH_6:
         prb = 6;
         break;
      case LRM_BANDWIDTH_15:
         prb = 15;
         break;
      case LRM_BANDWIDTH_25:
         prb = 25;
         break;
      case LRM_BANDWIDTH_50:
         prb = 50;
         break;
      case LRM_BANDWIDTH_75:
         prb = 75;
         break;
      case LRM_BANDWIDTH_100:
         prb = 100;
         break;
      default:
         RLOG1(L_ERROR,"Invalid BW config [%d]",cellBw);
         break;
   }
   return prb;
}

CPRBCongestionController::CPRBCongestionController(
                                 CRBearerController *pstRbBrCntrlr, 
                                 U8 bMaxPrbGbrUsage, LrmCellBandwidth cellBw)
{
   U32   prbPerBW;
   m_usGBRPRBLimit = bMaxPrbGbrUsage;

   prbPerBW = convertBwToPrb(cellBw);

   /*Maximum threshold for congestion is considered as sum of GBR PRB limit and 
    * 10% of Total PRBs for given bandwidth. This is limited to 100*/
   m_uiMaxPrbThreshold = m_usGBRPRBLimit + 
      ((prbPerBW * RM_CONGES_MAX_PRB_THRESH)/100);

   if(m_uiMaxPrbThreshold > RM_PRB_LIMIT_FULL)
   {
      m_uiMaxPrbThreshold = RM_PRB_LIMIT_FULL;
   }

   /*Minimum threshold for congestion is considered as difference between GBR 
    * PRB limit and 5% of Total PRBs for given bandwidth.*/ 
   m_uiMinPrbThreshold = m_usGBRPRBLimit - 
      (prbPerBW * RM_CONGES_MIN_PRB_THRESH)/100;
   /*If m_usGBRPRBLimit = 0, m_uiMinPrbThreshold will wrap around. Hence the
    * below check.*/
   if(m_uiMinPrbThreshold > RM_PRB_LIMIT_FULL)
   {
      m_uiMinPrbThreshold = 0;
   }

   m_uiTimeSamples = RM_CONGES_PRB_DEFAULT_SAMPLE_TIME;
   m_uiPreemptWaitInterval = RM_CONG_PREEMPT_WAIT_INT;
   m_uiPrevDlPrb = 0;
   m_uiPrevUlPrb = 0;
   m_objRBearerCtrlr = pstRbBrCntrlr;
   m_bIsCongested = false;
   RLOG_ARG4(L_DEBUG, DBG_CELLID, m_objRBearerCtrlr->getCellId(),
         "PRB Congestion Configuration:: Threshold max/min: [%d, %d] "
         "timeSample During Congestion: %d waitTime: %d",
         m_uiMaxPrbThreshold, m_uiMinPrbThreshold, 
         m_uiTimeSamples, m_uiPreemptWaitInterval);
}


bool CPRBCongestionController::verifyCongestion()
{
   U32  uiCurDlPrbUsage;
   U32  uiCurUlPrbUsage;
   bool bPreemptBearer = false;

   /* get current usage for DL*/
   uiCurDlPrbUsage=CPRBReportCollector::getInstance().getCurrentGbrDlPrbUsage();

   /* get current usage for UL*/
   uiCurUlPrbUsage=CPRBReportCollector::getInstance().getCurrentGbrUlPrbUsage();

   if(uiCurUlPrbUsage >= m_uiMaxPrbThreshold ||
         uiCurDlPrbUsage >= m_uiMaxPrbThreshold)
   {
      m_bIsCongested = true;
      m_uiPrevDlPrb= CPRBReportCollector::getInstance().getCurrentGbrDlPrbUsage(
            m_uiTimeSamples);
      m_uiPrevUlPrb= CPRBReportCollector::getInstance().getCurrentGbrUlPrbUsage(
            m_uiTimeSamples);

      bPreemptBearer = true;

      RLOG_ARG4(L_INFO, DBG_CELLID, m_objRBearerCtrlr->getCellId(),
            "Cell is Congested. Curr DL/UL PRB Usage: [%ld, %ld] [%ld, %ld]",
            uiCurDlPrbUsage, uiCurUlPrbUsage, m_uiPrevDlPrb, m_uiPrevUlPrb);
   }
   return bPreemptBearer;
}

void CPRBCongestionController::verifyUncongestion()
{
   U32  uiCurDlPrbUsage;
   U32  uiCurUlPrbUsage;

   uiCurDlPrbUsage=CPRBReportCollector::getInstance().getCurrentGbrDlPrbUsage();
   uiCurUlPrbUsage=CPRBReportCollector::getInstance().getCurrentGbrUlPrbUsage();

   if(uiCurUlPrbUsage <= m_uiMinPrbThreshold &&
         uiCurDlPrbUsage <= m_uiMinPrbThreshold)
   {
      m_bIsCongested = false;
      m_uiPrevDlPrb = 0;
      m_uiPrevUlPrb = 0;

      RLOG_ARG4(L_INFO, DBG_CELLID, m_objRBearerCtrlr->getCellId(),
            "Cell is Un-Congested. Curr DL/UL PRB Usage: [%ld, %ld] [%ld, %ld]",
            uiCurDlPrbUsage, uiCurUlPrbUsage, m_uiMaxPrbThreshold,
            m_uiMinPrbThreshold);
   }
}

bool CPRBCongestionController::verifyChangeInPrbUsage()
{
   bool bPreemptBearer = false;
   U32  uiCurDlPrbUsage;
   U32  uiCurUlPrbUsage;
   static U16 uiWaitTime = 0;

   /* get current usage for DL*/
   uiCurDlPrbUsage=CPRBReportCollector::getInstance().getCurrentGbrDlPrbUsage(
         m_uiTimeSamples);

   /* get current usage for UL*/
   uiCurUlPrbUsage=CPRBReportCollector::getInstance().getCurrentGbrUlPrbUsage(
         m_uiTimeSamples);

#ifdef DBG_MAC_RRM_PRB_PRINT
   // enable only for debugging
   CPRBReportCollector::getInstance().displayWindow();
#endif

   if(uiCurDlPrbUsage < m_uiPrevDlPrb ||
         uiCurUlPrbUsage < m_uiPrevUlPrb)
   {
      // if the PRB usage is decrementing, do not preempt immediately,
      // wait for further PRB reports before deciding to preempt
      // next ERAB.

      // reset wait time
      uiWaitTime = 0;

      verifyUncongestion();
   }
   else
   {
      if(!(++uiWaitTime % m_uiPreemptWaitInterval))
      {
         // if no change in PRB usage, preempt another bearer
         bPreemptBearer = true;
         // reset preemption wait time
         uiWaitTime = 0;
      }
   }

   if(m_bIsCongested)
   {
      RLOG_ARG4(L_INFO, DBG_CELLID, m_objRBearerCtrlr->getCellId(),
            "Cell is Congested. Curr DL/UL PRB Usage: [%ld, %ld] [%ld, %ld]",
            uiCurDlPrbUsage, uiCurUlPrbUsage, m_uiPrevDlPrb, m_uiPrevUlPrb);
   }

   /* update the change in local variables */
   m_uiPrevDlPrb = uiCurDlPrbUsage;
   m_uiPrevUlPrb = uiCurUlPrbUsage;

   return bPreemptBearer;
}

bool CPRBCongestionController::checkForCongestion()
{
   bool bPreemptBearer;

   if(m_bIsCongested)
   {
      bPreemptBearer = verifyChangeInPrbUsage();
   }
   else
   {
      bPreemptBearer = verifyCongestion();
   }

   if(bPreemptBearer)
   {
      m_objRBearerCtrlr->preemptErabDueToCongestion();
   }

   return m_bIsCongested;
}

/********************************************************************30**

           End of file:     qf_prbcongestioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/11 - Mon Feb 15 12:52:06 2016

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


