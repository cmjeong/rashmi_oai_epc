
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains the class of PRB based admission controller.
               
     File:     rm_prbbasedadmissioncontroller.h

     Sid:      rm_prbbasedadmissioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:57 2016

     Prg:      RRM Team

*********************************************************************21*/

#ifndef RM_PRBBASEDADMISSIONCONTROLLER_H_
#define RM_PRBBASEDADMISSIONCONTROLLER_H_

#include "rm_cmn.h"
#include "rm_uecontext.h"
#include "rmu.x"

/**
 * @brief  Class to determine if allowing the incoming RBs will lead 
 *         the sytem to cross the GBR PRB usage thresholds
 */
class CPRBBasedAdmissionController {
public:
   /**
    * @brief Contructor
    *
    * @details Function to setup the internal variables with values from cell
    *          configuration and to configure PRB report collector.
    *
    * @param[in]     stCellCfg   Cell Configuration
    *
    * @return  void
    */
   CPRBBasedAdmissionController(LrmCellConfigData & stCellCfg);

   /**
    * @brief Destructor
    *
    * @details Function to clear internal data and in PRB report collector.
    *
    * @return  void
    */
   ~CPRBBasedAdmissionController();

   /**
    * @brief Funtion to admit UEs when establishing a new ERAB
    *
    * @detail Function to determine if the incoming list of bearers can be served 
    *         within the configured limit of max GBR PRB usage without stressing 
    *         the system.
    *
    * @param[in]     stERAB          Incoming bearer requests
    * @param[out]    erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canRBsBeAdmitted(RmuErabConfigIe & stERAB,
                         RrmRbcRspInfo & erabRbcRspInfo);
   /**
    * @brief Funtion to admit UEs when modifying an existing ERAB
    *
    * @detail Function to determine if the incoming list of bearers for modification
    *         can be served within the configured limit of max GBR PRB usage without 
    *         stressing the system.
    *
    * @param[in]     pUE             UE control block
    * @param[in]     stERAB          Incoming bearer requests
    * @param[out]    erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  bool
    *          Returns true in case of success; else false
    */
   bool canModifyRBsBeAdmitted(CUEContext *pUE,
                               RmuErabConfigIe & stERAB,
                               RrmRbcRspInfo & erabRbcRspInfo);


   /**
    * @brief Function to send PRB report configuration to Scheduler
    *
    * @detail Function to fill the PRB report request and send to scheduler.
    *
    * @param[in]     cellId   Cell Identity
    * @param[in]     action   Report configuration type.
    *                         [RGM_PRB_REPORT_START - to start reporting PRB
    *                         usage and RGM_PRB_REPORT_STOP  - to stop 
    *                         reporting PRB usage]
    *
    * @return  S16
    *          Returns ROK in case of success; else RFAILED
    */
   S16 triggerPrbReportConfig(U8 cellId, U32 action);

   /**
    * @brief Function to update the PRB usage requirement of rejected bearers.
    *
    * @detail Function to determine the PRB usage of each ERAB that were 
    *         rejected by QCI admission control.
    *
    * @param[in]     stERAB          Incoming bearer requests
    * @param[in/out] erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  void
    */
   void updatePrbUsageForRejErabs(RmuErabConfigIe & stERAB,
                                  RrmRbcRspInfo & erabRbcRspInfo);

   /**
    * @brief Function to reorder the accept list
    *
    * @detail Function to reorder the accept list to avoid gaps caused by moving
    *         accepted bearers into reject list.
    *
    * @param[in/out]     erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  void
    */
   void reorderAcceptList(RrmRbcRspInfo & erabRbcRspInfo);

private:
   /*!< Cell Identity */
   U8     m_bCellId;
   /*!< PRB report interval configured at SCH */
   U32    m_uiPrbReportInterval;
   /*!< Number of Transmission antennas */
   U8     m_bNumTxAnt; 
   /*!< Duplex mode - FDD / TDD */
   U8     m_bDuplexMode; /* Duplex mode FDD-1 and TDD-2 */
   /*!< Config mode - used when duplex mode is configured as TDD */
   LrmUlDlConfig  m_enConfigMode;
   /*!< Maximum limit of GBR PRB usage in percentage */
   /* AC takes care of all BWs while reporting % of GBR PRB Usage to the RRM */
   U8    m_usMaxGBRPRBUsageLimit;
   /*!< Default iTBS */
   U8    m_bDefaultiTbs;
   /*!< System Bandwidth */
   LrmCellBandwidth  m_enDlBw; 

   /**
    * @brief sendPrbReportCfg
    *
    * @details Function to send the PRB report configuration to Scheduler
    *
    * @param[in]     cellId   Cell Identity
    * @param[in]     action   Report configuration type
    *
    * @return  S16
    *          Returns ROK in case of success; else RFAILED
    */
   S16 sendPrbReportCfg(U8 cellId, U32 action);

   /**
    * @brief getNumPrbsRequiredForBitRate
    *
    * @details Function to calculate number of PRBs required for the given 
    *          bit rate.
    *
    * @param[in]     uiBitRate       Bit rate for which PRB required is to be 
    *                                calculated
    * @param[in]     bIsDlGbrBitRate Indication is calculation is for DL bit
    *                                rate
    * @param[in]     biTbs Report    iTBS value to be used for calculation
    *
    * @return  U32
    *          Returns required number of PRBs for the given bit rate
    */
   U32 getNumPrbsRequiredForBitRate(U32 uiBitRate,
                                    bool bIsDlGbrBitRate,
                                    U32 biTbs);

   /**
    * @brief getReqPrbInPercent
    *
    * @detail Funtion to calculate the percentage of PRBs required for the given 
    *         bit rate.
    *
    * @param[in]     uiBitRate       Bit rate for which PRB required is to be 
    *                                calculated
    * @param[in]     bIsDlGbrBitRate Indication is calculation is for DL bit
    *                                rate
    * @param[in]     biTbs Report    iTBS value to be used for calculation
    *
    * @return  U32
    *          Returns percentage of PRBs required
    */
   U32 getReqPrbInPercent(U32 uiRcvdGbrBitsPerSec,
                          bool bIsDlGbrBitRate,
                          U32 biTbs);

#if 0
   /**
    * @brief getRbAddModIe
    *
    * @detail Function to fetch the ERAB add info from list of incoming ERABs 
    *         for the particular ERAB ID.
    *
    * @param[in]     stErab   List of incoming ERABs
    * @param[in]     bErabId  ERAB Identity
    *
    * @return  RmuUErabAddModIe *
    *          Returns address to ERAB add IE from list of incoming ERABs 
    *          for the corresponding ERAB ID
    */
   RmuUErabAddModIe *getRbAddModIe(RmuErabConfigIe & stERAB, U8 bErabId);
#endif
};

#endif  /* RM_PRBBASEDADMISSIONCONTROLLER_H_ */

/********************************************************************30**

       End of file:     rm_prbbasedadmissioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:57 2016

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


