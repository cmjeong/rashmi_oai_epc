
/** @file rm_qcibasedadmissioncontroller.h 
 * @brief This file contains the class of QCI based radio bearer admission(RBA)
 *        controller.
 */

#ifndef RM_QCIBASEDADMISSIONCONTROLLER_H_
#define RM_QCIBASEDADMISSIONCONTROLLER_H_

#include "rm_cmn.h"
#include "rm_uecontext.h"

#define RM_MAX_NUM_GBR  4             /*!< Maximum number of GBR bearers */
#define RM_MIN(x, y)    ((x) <= (y) ? (x) : (y)) /*!< To find minumum of 2 
                                                      numbers */

/**
 * @brief  Class to check if a RB can be admitted into the system without 
 *         possibly disrupting the timing requirements of the existing GBRs
 */
class CQCIBasedAdmissionController {
public:
   /**
    * @brief Constructor 
    *
    * @details Constructor, to setup the internal variables with values from 
    *          cell configuration
    *
    * @param[in]     stCellCfg   Cell Configuration
    *
    * @return  void
    */
   CQCIBasedAdmissionController(LrmCellConfigData &stCellCfg);

   /**
    * @brief To check if the ERABs can be admitted
    *
    * @detail Function to determine if the incoming list of bearers can be 
    *         allowed based on the maximum number of bearers allowed for the
    *         particular QCI (which is determined based on configured QCI
    *         timings) and the current number of bearers already admitted in 
    *         the system.
    *
    * @param[in]     stERAB         Incoming list of bearers for admission
    * @param[in/out] erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canRBsBeAdmitted(RmuErabConfigIe & stERAB,
                         RrmRbcRspInfo & erabRbcRspInfo);
   /**
    * @brief To check if the ERABs can be modified
    *
    * @detail Function to determine if the incoming list of bearers modification 
    *         can be allowed based on the maximum number of bearers allowed for 
    *         the particular QCI (which is determined based on configured QCI
    *         timings) and the current number of bearers already admitted in 
    *         the system if there is a change the QCI(with-in Bearer's QCI rage).
    *         Reject the modification of bearer from non-GBR to GBR or vice
    *         versa.
    *
    * @param[in]     pUE            UE control block
    * @param[in]     stERAB         Incoming list of bearers for modification
    * @param[in/out] erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canModifyRBsBeAdmitted(CUEContext *pUE,
                               RmuErabConfigIe & stERAB, 
                               RrmRbcRspInfo & erabRbcRspInfo);
   /**
    * @brief Release bearer for a particular QCI 
    *
    * @details Funtion to handle RAB release indication for a particular QCI.
    *          The function updates the internal states and counters regarding 
    *          the radio bearers.
    *
    * @param[in]     uiQci   QCI value
    *
    * @return  void
    */
   void rbReleaseInd(U32 uiQci);

   /**
    * @brief Add  bearer for a particular QCI 
    *
    * @details Funtion to handle RAB addition indication for a particular QCI.
    *          The function updates the internal states and counters regarding 
    *          the radio bearers.
    *
    * @param[in]     uiQci   QCI value
    *
    * @return  void
    */
   void rbAdditionInd(U32 qci);

   /**
    * @brief To fetch maximum number of bearers allowed per QCI 
    *
    * @details Function to fetch the maximum number of bearers 
    *          allowed per QCI.
    *
    * @param[in]     uiQci   QCI value
    *
    * @return  U32
    *          Returns the maximum number of bearers
    */
    U32   getMaxNumOfQCIBearersAllowed(U32 qciVal)
    {
       return(m_MaxNumOfQciBearersAllowed[qciVal-1]);
    };

private:
   /*!< Number of UE for new transmission per TTI in DL */
   U8    m_bNumDlNewUesPerTti;
   /*!< Number of UE for new transmission per TTI in UL */
   U8    m_bNumUlNewUesPerTti;
   /*!< Number of UE for retransmission per TTI in DL */
   U8    m_bNumDlReTxUesPerTti;
   /*!< Number of UE for retransmission per TTI in UL */
   U8    m_bNumUlReTxUesPerTti;
   /*!< Duplex mode - FDD / TDD */
   U8    m_bDuplexMode;
   /*!< Stores the configured QCI timings in milliseconds for QCI 1,2,3 and 4 */
   U8    m_bRbcQciTmngReq[RM_MAX_NUM_GBR];
   /*!< Indicates if timing requirement is to be enabled for QCI 4 */
   bool  m_bRbcQci4TmngReqEnable;
   /*!< Config mode - used when duplex mode is configured as TDD */
   LrmUlDlConfig      m_enConfigMode;
   /*!< Maximum number of QCI (1,2,3,4) bearers that can be allowed based on 
    *   configured QCI timings */
   U16   m_MaxNumOfQciBearersAllowed[RM_MAX_NUM_GBR];
   /*!< Current number of QCI (1,2,3,4) bearers that are admitted in the 
    *   system */
   U16   m_numOfQciBearersAdmitted[RM_MAX_NUM_GBR];
   /**
    * @brief canQCI1RBBeAdmitted
    *
    * @details Funtion to determine of the incoming QCI 1 bearer can be admitted
    *          or not based on the current number of QCI 1 bearers in the 
    *          system and the maximum number of QCI 1 beaers that can be
    *          allowed.
    *
    * @param[in]     stRabQos   Incoming QCI 1 RAB QoS information
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canQCI1RBBeAdmitted(RmuUErabQosInfoIe &stRabQos);

   /**
    * @brief canQCI2RBBeAdmitted
    *
    * @details Funtion to determine of the incoming QCI 2 bearer can be admitted
    *          or not based on the current number of QCI 2 bearers in the 
    *          system and the maximum number of QCI 2 beaers that can be
    *          allowed.
    *
    * @param[in]     stRabQos   Incoming QCI 2 RAB QoS information
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canQCI2RBBeAdmitted(RmuUErabQosInfoIe &stRabQos);

   /**
    * @brief canQCI3RBBeAdmitted
    *
    * @details Funtion to determine of the incoming QCI 3 bearer can be admitted
    *          or not based on the current number of QCI 3 bearers in the 
    *          system and the maximum number of QCI 3 beaers that can be
    *          allowed.
    *
    * @param[in]     stRabQos   Incoming QCI 3 RAB QoS information
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canQCI3RBBeAdmitted(RmuUErabQosInfoIe &stRabQos);

   /**
    * @brief canQCI4RBBeAdmitted
    *
    * @details Funtion to determine of the incoming QCI 4 bearer can be admitted
    *          or not based on the current number of QCI 4 bearers in the 
    *          system and the maximum number of QCI 4 beaers that can be
    *          allowed.
    *
    * @param[in]     stRabQos   Incoming QCI 4 RAB QoS information
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canQCI4RBBeAdmitted(RmuUErabQosInfoIe &stRabQos);
};

#endif  /* RM_QCIBASEDADMISSIONCONTROLLER_H_ */

/********************************************************************30**

       End of file:     rm_qcibasedadmissioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:59 2016

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


