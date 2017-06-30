
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_acb.h

     Sid:      rm_acb.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:37 2013

     Prg:      hkrishna, vkorade 

*********************************************************************21*/


#ifndef RM_ACB_H_
#define RM_ACB_H_

#include "rm_cmn.h"

#define RM_RAC_ACB_CPULD_CRITICAL_MIN         90
#define RM_AVG_PRB_RPT_PERIODICITY_MILLI_SEC  600

class CAccessClassBarring
{
public:
	CAccessClassBarring(LrmCellConfigData &stCellCfgDat);
   
   /**
    * @brief Function to handle the reconfiguration for ACB params.
    * 
    * @details Function to handle the reconfiguration of ACB params for
    * Mo-signalling, Mo-data and Emergency.
    *      
    * @param[in] stCellCfgInfo modified data of ACB parameters for this cell.
    *
    * @return void
    */
	void handleCellReConfiguration(LrmCellConfiguration & stCellCfgInfo);

	void handleCpuLoadInd(U8 bCurrCpuLoad);
#ifdef RRM_UNUSED_FUNC
	void handlePrbUsageInd(U8 bUlPrbUsage, U8 bDlPrbUsage);
#endif
	bool admitUE(U8 bEstablishmentCause);
	void updateLeastMmeOverloadStatus(RmuMmeOvldStatus enOvldStatus);

private:
	void applyMmeOverloadForACB();
#ifdef RRM_UNUSED_FUNC
	U8 getPrbUsageIndex(U8 bCellPrbUsage);
#endif
	void applyACBParams(CmRrmAcb   &stAcBarringMoData, CmRrmAcb &stAcBarringMoSig);

private:
	CmRrmAcb  m_stCpuACBData;
	CmRrmAcb  m_stMmeMOSigAcbParams;
	CmRrmAcb  m_stMmeMODataAcbParams;
	CmRrmAcb  m_stMmeHighPriMOTermAcbMoDataParams;
	CmRrmAcb  m_stMmeHighPriMOTermAcbMoSigParams;
	CmRrmAcb  m_stPRBAcbParams;
	Bool  m_bAcBarringForEmergency;
	//U8 m_bAcBarringSpecialAcc;
	RmuMmeOvldStatus m_enMMEOverldStatus; /* least among all the MME overload status */
	U8 m_bPrevPrbUsageIndex;
	U8 m_bCpuLoad;
	U8 m_bCellId;
   Bool bIsAcbMoDataEnabledByOam; /*!< true: OAM enabled ACB for Mo-data */
   Bool bIsAcbMoDataEnabledByMme; /*!< true: Mme enabled ACB for Mo-data */
   Bool bIsAcbMoSigEnabledByOam; /*!< true: OAM enabled ACB for Mo-signaling */
   Bool bIsAcbMoSigEnabledByMme; /*!< true: Mme enabled ACB for Mo-signaling */
	
   RmuAcbParamInd m_stAcbCfgInfo;
   /**
    * @brief Function to display the ACB parameters.
    * 
    * @details Function to display the ACB parameters of the provided data
    *          structure.
    *      
    * @param[in] stAcbParams Data to be displayed
    *
    * @return void
    */
   void printAcbParams(CmRrmAcb & stAcbParams);

};

#endif /* RM_ACB_H_ */
/********************************************************************30**

           End of file:     rm_acb.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:37 2013

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
