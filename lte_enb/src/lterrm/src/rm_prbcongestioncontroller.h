
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_prbcongestioncontroller.h

     Sid:      rm_prbcongestioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/11 - Mon Feb 15 12:52:07 2016

     Prg:      RRM Team

*********************************************************************21*/

/** @file rm_prbcongestioncontroller.h
 * @brief This file contains the PRB congestion collector class which 
 *        is used to decide if the system is congested or not based on 
 *        the current GBR PRB usage reported by scheduler.
 */

#ifndef RM_PRBCONGESTIONCONTROLLER_H_
#define RM_PRBCONGESTIONCONTROLLER_H_

#include "rm_cmn.h"

/*!< Percentage of PRB usage to be used to calculate the lower threshold for 
 * congestion */
#define RM_CONGES_MIN_PRB_THRESH    5

/*!< Percentage of PRB usage to be used to calculate the upper threshold for 
 * congestion */
#define RM_CONGES_MAX_PRB_THRESH    10

/*!< Percentage of time samples to be considered while checking for 
 *   un-congestion */
#define RM_CONGES_PRB_DEFAULT_SAMPLE_TIME  40

/*!< Time to wait between two preemptions */
#define RM_CONG_PREEMPT_WAIT_INT 3

/*!< Maximum available PRBs a the system */
#define RM_PRB_LIMIT_FULL 100

/*!< PRB limit when RM_PRB_LIMIT_FULL is configured */
#define RM_PRB_LIMIT_FOR_FULL_CFG 98

class CRBearerController;

/**
 * @brief Class to determine if system is congested.
 */
class CPRBCongestionController
{
public:
   /**
    * @brief Constructor
    * 
    * @details This function updates the min and max PRB threshold values from
    *          file. If RRM configuration file is not present, the default 
    *          values are used.
    * 
    */
   CPRBCongestionController(CRBearerController *pstRbBrCntrlr, U8 bMaxPrbGbrUsage, 
                            LrmCellBandwidth cellBw);

   /**
    * @brief Function to decide if system is congested
    * 
    * @details This function checks for congestion and preempts a ERAB,
    *          if indicated, to recover from congestion.
    *          If the system is already congested, this function invokes
    *          verifies the change in PRB usage to determine if 
    *          the system has recovered from congestion.
    * 
    * @return bool
    *          Returns true if congestion, else false.
    */
   bool checkForCongestion();

private:
   /*!< Indicates if system is congested or not */
   bool  m_bIsCongested;

   /*!< Max GBR PRB limit to decide that system is congested (GBR PRB Limit +
    * 10% of GBR PRB Limit) */
   U32   m_uiMaxPrbThreshold;

   /*!< Min GBR PRB limit to decide that system is uncongested (GBR PRB Limit -
    * 5% of GBR PRB Limit) */
   U32   m_uiMinPrbThreshold;

   /*!< Maximum limit of GBR PRB usage in percentage */
   U8    m_usGBRPRBLimit;

   /*!< Reference of radio bearer controller object in cellManager */
   CRBearerController *m_objRBearerCtrlr;

   /*!< DL PRB usage when congestion occured */
   U32 m_uiPrevDlPrb;

   /*!< UL PRB usage when congestion occured */
   U32 m_uiPrevUlPrb;

   /*!< Samples for last 'x' millisecons to be used to detect un-congestion */
   U16 m_uiTimeSamples;

   /*!< Number of reports to consider before preempting another bearer 
    * during congestion */
   U16 m_uiPreemptWaitInterval;

   /**
    * @brief Function to decide congestion
    * 
    * @details This function verifies the current GBR PRB usage reported by
    *          Scheduler with max PRB thresholds to decide if
    *          the system is congested.
    * 
    * @return bool
    *          Returns true if congestion, else false.
    */
   bool verifyCongestion();

   /**
    * @brief Function to decide un-congestion
    * 
    * @details This function verifies the change in GBR PRB usage reported by
    *          Scheduler with the min PRB thresholds to decide if
    *          the system has recovered from congestion.
    * 
    * @return void
    */
   void verifyUncongestion();

   /**
    * @brief Function to detect change in PRB usage after preempting a ERAB
    *        to recover from congestion.
    * 
    * @details This function verifies the current GBR PRB usage reported by
    *          Scheduler in the last n number of samples, to decide if the
    *          earlier preemption of an ERAB has caused reduction in PRB
    *          usage or not.
    *          If there is no change in the GBR PRB usage or if the change in
    *          PRB usage is not enough to recover from congestion, another
    *          ERAB is preempted.
    * 
    * @return bool
    *          Returns true if congestion, else false.
    */
   bool verifyChangeInPrbUsage();

   /**
    * @brief Function to read from internal RRM configuration
    * 
    * @details This function reads from the internal RRM configuration file and 
    *          updates the internal variables. If the file is not present,
    *          the default values are used.
    * 
    * @return void
    */
   void readAndUpdateFromRrmCfgFile();

   /**
    * @brief Function to return the number of PRBs for given bandwidth
    * 
    * @details This function takes bandwidth enum as input and returns the value
    *          of total number of PRBs for particular bandwidth.
    * 
    * @param[in] cellBw   Bandwidth enum
    *
    * @return U32 
    *            Return the total number of PRBs
    */
    U32 convertBwToPrb(LrmCellBandwidth cellBw);

};

#endif  /* RM_PRBCONGESTIONCONTROLLER_H_ */

/********************************************************************30**

       End of file:     rm_prbcongestioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/11 - Mon Feb 15 12:52:07 2016

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


