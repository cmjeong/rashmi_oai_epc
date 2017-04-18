
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_radiobearercontroller.h

     Sid:      rm_radiobearercontroller.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:40 2013

     Prg:      hkrishna 

*********************************************************************21*/

#ifndef RM_RADIOBEARRERCONTROLLER_H_
#define RM_RADIOBEARRERCONTROLLER_H_

#include <list>
#include <vector>
#include "rm_cmn.h"
#include "rm_uecontext.h"
#include "rm_rbadmissioncontroller.h"
#include "rm_preEmptableERABFinder.h"

/*!< MAX ARP of the ERAB */
#define RM_RBC_MAX_ARP 16

/*!< ERAB List QCI priority */
#define RM_RBC_LEAST_QCI_PRIORITY 255

/*!< backhaul bandwidth support is enabled or not : for future use */
#define RM_ERAB_BHBW_SUPPORT  0

/**
 * @brief Class to process the ERABs received in ERAB setup/modify/release
 *        and HO request after contacting the Radio Admission controller and 
 *        PreEmption Finder class.
 */
class CRBearerController
{
public:
   /**
    * @brief Constructor of the class.
    * 
    * @details Constructor of the class will update the cell configuration.
    *      
    * @param[in] stCellCfg stores the cell configuaration data.
    * @return void 
    */
   CRBearerController(LrmCellConfigData & stCellCfg,
                      CCellManager *pstObjCellMngr);

   /**
    * @brief Function to process the ICS req, ERAB setup
    *        ERAB modify, RAB release requests in RBC.
    * 
    * @details Function to process the ERAB setup, modify, release request with
    *          contacting the RAC and Pre-empt the other bearers if required.
    *      
    * @param[in] pObjUE           Pointer to the object of the UE.
    * @param[in] stERAB           ERAB setup/modify/relese request information.
    * @param[out] pstRabsRspInfo  Response contains all ERBAs with eiter accept or
    *                             reject with cause.
    *
    * @return bool 
    *         Returns true in case of successfull processing of the ERABs in
    *         ERAB setup/modify/release request;
    *         else returns false.
    *
    */
   bool processErabRequest(CUEContext *pObjUE,
                           RmuErabConfigIe & stERAB,
                           RmuUeRecfgRsp *pstRabsRspInfo);
   /**
    * @brief Function to process the ERABS in Handover request at RBC.
    * 
    * @details Function to process the ERABs in Handover request at RBC 
    *      
    * @param[in] pobjUE           Pointer to the object of the UE.
    * @param[in] stERAB           ERAB's inforamtion received in HO request. 
    * @param[out] pstHoRspInfo    Response contains all ERABs with eiter accept or
    *                             reject with cause.
    *
    * @return bool 
    *         Returns true in case of successfull processing the ERABs in
    *         Handover request; else returns false.
    */
   bool processErabAdmissionInHORequest(CUEContext *pobjUE,
                                        RmuErabConfigIe & stERAB,
                                        RmuUeHoRsp *pstHoRspInfo);
   /**
    * @brief Function to trigger the start/stop PRB usage report 
    *        configuration request to MAC/SCH.
    * 
    * @details Function to trigger the start/stop PRB usage report 
    *          configuration request to MAC/SCH.
    *      
    * @param[in] cellId cell Id.
    * @param[in] action start/stop GBR PRB usage report.
    *
    * @return S16 
    *         Returns ROK in case of successful configuration req sent to
    *         MAC/SCH; else RFAILED.
    */
   S16 triggerPrbReportConfig(U8 cellId, U32 action);

   /**
    * @brief Function to release all ERABs of the UE in RBC.
    * 
    * @details Function to release all ERABs of the UE in RBC and
    *          update the RAC and pre-emption class.
    *      
    * @param[in] pUE pointer to the object of the UE.
    *
    * @return void 
    */
   void releaseAllERABs(CUEContext* pUE);

   /**
    * @brief Function of friend of CUEContext class, used to update the
    *        CSG membership modification of an UE need to update into the GBR 
    *        ERABs multimap table.
    * 
    * @details Function to update the key of the ERABs of this UE to access from
    *          GBR ERABs table when there is a modification of CSG memebership
    *          status.
    *      
    * @param[in] pUE           Pointer to the object of the UE for accessing the
    *                          all ERABs of the UE.
    * @param[in] ObjRbc        Object of the RBC class to access the Pre-emption
    *                          finder class object.
    * @param[in] bIsCSGMember  The modified CSG membership.
    * @return void 
    */
   friend void updateCsgMemberShip(CUEContext* pUE, 
                                   CRBearerController &ObjRbc,
                                   bool bIsCSGMember);

   /**
    * @brief Function to preempt ERAB(s) due to congestion.
    * 
    * @details This function gets one preemtable ERAB from preemtable ERAB
    *          finder class and preempts the ERAB.
    * 
    * @return void 
    */
   void preemptErabDueToCongestion();

   /**
    * @brief Function to get the cell identity.
    * 
    * @details This function returns the configured cell identity.
    * 
    * @return U8 - cell Identity
    */
   U8 getCellId() {return m_bCellId;}
private:
   /**
    * @brief Function to prepare and send the ERAB release indication.
    * 
    * @details Function to trigger the ERAB release indication per UE.
    *      
    * @param[in] objPreEmptedERABsList  List of ERABs for multiple UEs need to
    *                                   trigger ERAB release indication per UE
    * @return void 
    */
   void triggerERabRelIndPerUe(CERABInfoLst &objPreEmptedERABsList);

   /**
    * @brief Function to process the ERAB setup/ICS request. 
    *
    * @detail Function to process the incoming RAB setup information and
    *         respond back with a list of accepted and rejected list of RABs.
    *         This funtion internally uses the RB Admission Controller for
    *         deciding whether the incoming RB can be admitted or not based on
    *         system capacity.
    *
    * @param[in]     pUE             UE control block
    * @param[in]     stERAB          Incoming list of RAB information
    * @param[out]    pstRabsRspInfo  RAB response information
    *
    * @return bool
    *         Returns true incase of successful ERAB setup request process; else retruns
    *         false.
    */
   bool processErabSetupRequest(CUEContext *pObjUE,
                                RmuErabConfigIe & stERAB,
                                RmuUeRecfgRsp *pstRabsRspInfo);
   /**
    * @brief Function to process the ERAB Modify request. 
    *
    * @detail Function to process the incoming RAB Modify information and
    *         respond back with a list of accepted and rejected list of RABs.
    *         This funtion internally uses the RB Admission Controller for
    *         deciding whether the incoming RB can be admitted or not based on
    *         system capacity and also updates the pre-emption GRB RABs table.
    *
    * @param[in]     pUE             UE control block
    * @param[in]     stERAB          Incoming list of RAB information
    * @param[out]    pstRabsRspInfo  RAB response information
    *
    * @return bool
    *         Returns true incase of successful ERAB setup request process; else retruns
    *         false.
    */
   bool processErabModifyRequest(CUEContext *pObjUE,
                                 RmuErabConfigIe & stERAB,
                                 RmuUeRecfgRsp *pstRabsRspInfo);
   /**
    * @brief Function to process the ERAB Release request. 
    *
    * @detail Function to process the incoming RAB Release request and
    *         respond back with a list of accepted and rejected list of RABs.
    *         This funtion internally uses the RB Admission Controller to update
    *         the release RB information.
    *
    * @param[in]     pUE             UE control block
    * @param[in]     stERAB          Incoming list of RAB information
    * @param[out]    pstRabsRspInfo  RAB response information
    *
    * @return bool
    *         Returns true incase of successful ERAB setup request process; else retruns
    *         false.
    */

   bool processErabReleaseRequest(CUEContext *pObjUE,
                                  RmuErabConfigIe & stERAB,
                                  RmuUeRecfgRsp *pStRabRspInfo);

#if RM_ERAB_BHBW_SUPPORT
   bool validateAndUpdateBackHaulBandWidth(CERABInfo *pObjExistedERab, 
                                           RmuUErabAddModIe &stERabAddMod);
#endif

   /**
    * @brief Function to arr ERAB to UE. 
    *
    * @detail Function to add a ERAB info to the list of ERABs in UE control block.
    *
    * @param[in] pUE             UE control block
    * @param[in] stERabAddMod    ERAB information
    *
    * @return CERABInfo* pointer to the E-RAB object 
    */
   CERABInfo*  addErabToUe(CUEContext *pUE, RmuUErabAddModIe &stERabAddMod);

 /**
    *@brief function used to process incoming Erabs for setup.
    *
    *@details  Fundtion is performing the fallowing tasks.
    *          1. Checking with QCI and PRB basaed radio bearer admission to
    *             admit the incoming requests.
    *          2. Pre-empting the ERABS if required.
    *          3. Adding the admitted ERABs to UEs RB list.
    *          4. Populating the UE RECFG RESPONSE with accepted and rejected
    *             list.
    *
    *@param[in/out] pUE pointer to object of UE 
    *@param[in]     stERAB Erab structure
    *@param[out] pstErabAmitLst admitted erab list
    *@param[out] stErabRejectLst rejected erab list
    *@param[out] bNoErabsAdmitted number of erabs admitted
    *@param[out] bNoErabsRejected number of erabs rejected
    *
    *@return bool
    */
   void processIncomingERabsforSetup(CUEContext *pUE,
                                     RmuErabConfigIe & stERAB,
                                     RmuErabAdmitted *pstErabAdmitLst,
                                     RmuErabRejected *stErabRejectLst,
                                     U8  *bNoErabsAdmitted,
                                     U8  *bNoErabsRejected);

#if RM_ERAB_BHBW_SUPPORT /* consider in Next Release */
   inline bool validateUlBwUsage(S32 usUlGbr);
   inline bool validateDlBwUsage(S32 usDlGbr);
   void updateUlBwUsage(S32 usUlGbr);
   void updateDlBwUsage(S32 usUlGbr);
#endif /* end of RM_ERAB_BHBW_SUPPORT */
   U16                    m_usBroadBandUlBwUsage;
   U16                    m_usBroadBandDlBwUsage;
   U16                    m_usMaxUlBroadbandBw;
   U16                    m_usMaxDlBroadbandBw;

   /*!< ARP of Emergency bearer*/
   U32                    m_bArpForEmergencyBearer;

   /*!< Instance of RB admission controller class */
   CRBAdmissionController m_objRbAdmissionController;

   /*!< Instance of pre-emptable Rabs finder class */
   CPreEmptableERABFinder m_objPreEmptableRabsFinder;

   /*!< vector of ERABs object to create a Free pool of Erabs */
   std::vector<CERABInfo>   m_tvRabList;

   /*!< Pool of free ERabs used for creating bearers for all UEs */
   std::list<CERABInfo*>   m_tlFreeRabPool;

   /*!< cell ID  */
   U8   m_bCellId;
};

#endif /* RM_RADIOBEARERCONTROLLER_H_ */
/********************************************************************30**

           End of file:     rm_radiobearercontroller.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:40 2013

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
