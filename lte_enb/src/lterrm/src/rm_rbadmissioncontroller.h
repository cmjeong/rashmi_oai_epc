
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_rbadmissioncontroller.h

     Sid:      rm_rbadmissioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:00 2016

     Prg:      Amit Ghosh

*********************************************************************21*/

#ifndef RM_RBADMISSIONCONTROLLER_H_
#define RM_RBADMISSIONCONTROLLER_H_

#include "rm_cmn.h"
#include "rm_prbbasedadmissioncontroller.h"
#include "rm_qcibasedadmissioncontroller.h"

class CCellManager;

class CRBAdmissionController {
public:
   /**
    * @brief CRBAdmissionController
    *
    * @detail Constructor, initializes PRB based admission controller and QCI
    *         based admission controller objects.
    *
    * @param[in]     stCellCfg   Cell Configuration
    *
    * @return  void
    */
   CRBAdmissionController(LrmCellConfigData &stCellCfg, 
                          CCellManager *pstObjCellMngr);

   /**
    * @brief Funtion to admit UEs when establishing a new ERAB
    *
    * @detail Function to invoke QCI based admission controller and PRB based 
    *         admission controller to determine if the incoming bearers can be
    *         admitted or not. The output is indicated in the form of accepted
    *         and reject bearer lists.
    *
    * @param[in]     pUE             UE control block
    * @param[in]     stERAB          Incoming bearer requests
    * @param[out]    erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  void
    */
   void canRBsBeAdmitted(CUEContext *pUE,
                         RmuErabConfigIe & stERAB,
                         RrmRbcRspInfo & erabRbcRspInfo);

   /**
    * @brief Funtion to admit UEs when modifying an existing ERAB
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
    * @param[in/out] erabRbcRspInfo ERAB Radio bearer control response
    *
    * @return  void
    */
   void canModifyRBsBeAdmitted(CUEContext *pUE,
                               RmuErabConfigIe & stERAB, 
                               RrmRbcRspInfo & erabRbcRspInfo);

   /**
    * @brief rbReleaseInd
    *
    * @detail Function to is used to update the release of a bearer of a
    *         particular QCI type.
    *
    * @param[in]     uiQci   QCI Type
    *
    * @return  void
    */
   void rbReleaseInd(U32 qci);

   /**
    * @brief rbAdditionInd
    *
    * @detail Function to is used to update incoming bearer count of a
    *         particular QCI type.
    *
    * @param[in]     uiQci   QCI Type
    *
    * @return  void
    */
    void rbAdditionInd(U32 qci);

   /**
    * @brief triggerPrbReportConfig
    *
    * @detail Function to fetch the trigger PRB report configuration towards
    *         scheduler. This funtion can be used to send both START and 
    *         STOP request.
    *
    * @param[in]     cellId   Cell Identity
    * @param[in]     action   Report configuration type.
    *                         [RGM_PRB_REPORT_START - to start reporting PRB
    *                         usage and RGM_PRB_REPORT_STOP  - to stop 
    *                         reporting PRB usage]
    *
    * @return  S16
    *          Returns ROK in case of success and RFAILED in case of failure.
    */
   S16 triggerPrbReportConfig(U8 cellId, U32 action);
private:
   /*!< Instance of PRB based admission controller class */
   CPRBBasedAdmissionController m_objPrbAdmissionController;
   /*!< Instance of QCI based admission controller class */
   CQCIBasedAdmissionController m_objQciAdmissionController;
   /*!< Reference to cell context */
   CCellManager *m_pstCellMngr;


   /**
    * @brief Funtion to add all accepted ERABs to rejected ERAB list
    *
    * @detail This function moves all the accepted ERABs from accepted list
    *         to rejected ERAB list.
    *
    * @param[in]  stERAB          Incoming bearer requests
    * @param[out] erabRbcRspInfo  ERAB Radio bearer control response
    *
    * @return  void
    */
   void addAllAccptErabsToRejList(
                               RmuErabConfigIe & stERAB, 
                               RrmRbcRspInfo & erabRbcRspInfo);

};

#endif  /* RM_RBADMISSIONCONTROLLER_H_ */

/********************************************************************30**

       End of file:     rm_rbadmissioncontroller.h@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:00 2016

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


