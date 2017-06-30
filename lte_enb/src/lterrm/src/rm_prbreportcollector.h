
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_prbreportcollecter.h

     Sid:      rm_prbreportcollector.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:58 2016

     Prg:      RRM Team

*********************************************************************21*/

/** @file rm_prbreportcollector.h 
 * @brief This file is the PRB reprot collector class holds the SCH reproted PRB
 *         usasge for all GBR bearers. which is useful during PRB based 
 *         RB admission and also to find the congestion is occured or not.
 */

#ifndef RM_PRBREPORTCOLLECTOR_H_
#define RM_PRBREPORTCOLLECTOR_H_

#include "rm_cmn.h"
#include <vector>

/*!< Number of Max GBR Bearers  */
#define RRM_MAX_GBR_QCIS RGM_MAX_QCI_REPORTS 

/**
 * @brief Class to hold the GBR bearers PRB usage reports which 
 *        are reported by MAC/SCH.
 */
class CPRBUsageInfo 
{
public:
   
   /*!< MAC/SCH reported DL PRB Usage infor for each QCI */
   U32   m_dlPrbReport[RRM_MAX_GBR_QCIS];

   /*< MAC/SCH reported UL PRB Usage infor for each QCI */
   U32   m_ulPrbReport[RRM_MAX_GBR_QCIS];

   /*!< sum of all GBR in DL for a sliding window */
   U32   m_gbrDlPrbRptsSum;

   /*!< sum of all GBR in UL for a sliding window */
   U32   m_gbrUlPrbRptsSum;
};

/**
 * @brief Class to hold the SCH sends the averaged reports to RRM 
 *        This object will keep the data in a perQCI basis for all GBR bearers
 *        and also at a cummulative level for all the GBRs on a sliding 
 *        window basis. This class is implemented as a singleton
 */
class CPRBReportCollector {
public:
   /**
    * @brief Function to get the current DL GBR PRB usage in percentage(%)
    * 
    * @details Function performs the average of the DL GBR PRB usage of
    *          for all slots stored in the PRB storage vector(sliding window 
    *          of PRB Usage info). 
    *
    * @param[in] timePeriod  Time period in milliseconds, for which the PRB
    *                        usage is requested. This is an optional parameter.
    * 
    * @return U32 
    *          Returns the Average percentage of DL GBR PRB usage. 
    */
   U32 getCurrentGbrDlPrbUsage(U32 timePeriod = 0) const;

   /**
    * @brief Function to get the current UL GBR PRB usage in percentage(%)
    * 
    * @details Function performs the average of the UL GBR PRB usage of
    *          for all slots stored in the PRB storage vector(sliding window 
    *          of PRB Usage info). 
    * 
    * @param[in] timePeriod  Time period in milliseconds, for which the PRB
    *                        usage is requested. This is an optional parameter.
    * 
    * @return U32 
    *          Returns the Average percentage of UL GBR PRB usage per ms. 
    */
   U32 getCurrentGbrUlPrbUsage(U32 timePeriod = 0) const;
   
   /**
    * @brief Function to get the instance of singleton PRB Report collector 
    * 
    * @details Function to get the instance of PRB report collector instance
    * 
    * @return CPRBReportCollector 
    *          Returns the instance to the singleton CPRBReportCollector object. 
    */
   static CPRBReportCollector &getInstance()
   {
      static CPRBReportCollector objRbReportCollector;
      return objRbReportCollector;
   }

   /**
    * @brief Function will update he configuration required for PRB report 
    *        collector class
    * 
    * @details Function update the recived configuration variable from Stack
    *          Manager into the class object and also intilizes the default 
    *          values of the class and resizes the PRB usage report collector 
    *          vector
    *         
    * @param[in] uiSchReportPeriodicity  PRB Usage report interval in ms
    * @param[in] uiWindowSize  number of reports to store in report collector
    * 
    * @return void 
    */
    void configurePRBReportCollector(U32 uiSchReportPeriodicity, U32 uiWindowSize);

   /**
    * @brief Function to update the GBR PRB usage vector in the cuttent slot 
    *        with the the received current PRB usage report from MAC/SCH.   
    * 
    * @details Function updates the received PRB usage report into the current slot
    *          in the PRB usage vector and also updates the SUM of the GBR PRB
    *          Usage for all slots in the sliding window(vector)
    *        
    * @param[in] pstPrbReport  pointer to the GBR PRB Usage report for all Qcis 
    *                          which is reported by MAC/SCH
    * 
    * @return void 
    */
   void updateQCIsPRBReport(const RgmPrbRprtInd *prbRprt);

   /**
    * @brief Function to clear all the GBR PRB usage samples and reset the 
    *        internal variables.
    * 
    * @details Function clears the stored PRB usage samples and resets
    *          the current slot, are all slots filled indicator and the resizes
    *          the sliding window (vector) to 0.
    *        
    * @return void 
    */
   void clearPrbUsageData();

#ifdef DBG_MAC_RRM_PRB_PRINT
   /**
    * @brief Function to display the PRB data
    * 
    * @details This function displays the contents of the entire PRB window.
    *        
    * @return void 
    */
   void displayWindow();
#endif

private:

   /*!< vector to store the received PRB Usage reports from SCH */
   std::vector<CPRBUsageInfo>   m_tvPrbUsge;

   /*!< The interval in ms after which SCH sends the PRB usage reports */
   U32                     m_schReportingInterval;

   /*!< The max number of PRB usage reports to store in vector */    
   U32                     m_windowSize;
   
   /*!< MAC reported PRB usage will be updated in the 
    *   current index pointed in the vector 
    */
   U32                     m_curntSlotIndx;

   /*!< Holds the last calculated GBR PRB usage in DL */
   U32                     m_currentGbrDlPrbUsage;

   /*!< Holds the last calculated GBR PRB usage in UL */
   U32                     m_currentGbrUlPrbUsage;

#ifdef DBG_MAC_RRM_PRB_PRINT
   /*!< This is to print the PRB usage vector fro every 20sec */
   U32                     m_DemoPrintCntFor20Sec;
#endif

   /*!< True:If all slots are filled in vector; else false */
   bool                    m_areAllSlotsFilled;

   /*!< Contains the bearer direction */
   enum rmBearerDirection
   {
      RM_DIR_DL=1,  /*!< Value of DL direction */
      RM_DIR_UL     /*!< Value of UL direction */
   };

   /**
    * @brief Function to get the slot to store the current PRB usage 
    *        in PRB report collector vector
    * 
    * @details Function retunrs the slot in the sliding window of PRB reports
    *          and also makse sure to wrap arounds the sliding window slot index 
    *      
    * @return CPRBUsageInfo* 
    *          Returns pointer to the PRB usage slot
    */
   CPRBUsageInfo* getCurrentSlot();

   /**
    * @brief Destructor of the class.
    * 
    * @return void
    */
   ~CPRBReportCollector()
   {
   }

   /**
    * @brief Function to get the PRB usage for n number of slots
    * 
    * @details This function returns the PRB usage in the last n slots for 
    *          the given direction (DL/UL).
    *      
    * @param[in] numSlots  Number of slots for which the PRB usage is requested
    * @param[in] dir       Indicates whether DL or UL PRB usage is requested
    *
    * @return U32
    *         Returns average PRB usage for the requested number of slots
    */
   U32 getPrbForLastSlots(U32 numSlots, rmBearerDirection dir) const;
};

#endif  /* RM_PRBREPORTCOLLECTOR_H_ */

/********************************************************************30**

       End of file:     rm_prbreportcollector.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:58 2016

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


