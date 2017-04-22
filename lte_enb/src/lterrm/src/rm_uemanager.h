
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_uemanager.h

     Sid:      rm_uemanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:41 2013

     Prg:      hkrishna, vkorade 

*********************************************************************21*/


#ifndef _RRM_UECONTROLLER_H_
#define _RRM_UECONTROLLER_H_

#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "rm_cmn.h"
#include "rm_uecontext.h"

typedef U16 CRNTI;

#define INITIAL_UE_POOL_SIZE	128
#define RM_MAX_UES_PER_CELL   128
/* HCSG_DEV */
#define RM_MAX_ONHOLD_UES_PER_CELL (RM_MAX_UES_PER_CELL / 4)

class CUEManager
{
public:
	CUEManager(LrmCellConfigData & stCellCfg);
	bool isMaxActiveUELimitReached();
	bool isMaxSignalingUELimitReached();
   /* HCSG_DEV */
   void cellRecfg(LrmCellConfigData &stCellCfg);
	bool allowExtraUe();
	bool allowSigUeToActUeLst();
   bool isUEInExtraUEList(CUEContext *);
   CUEContext* findCsgUEToRelease();
   CUEContext* findNonCsgUEToRelease();
	void moveUEFrmExtLstToNonCsgLst(CUEContext*);
	void moveUEFrmExtLstToCsgLst(CUEContext*);
	void moveUEFrmCsgLstToNonCsgLst(CUEContext*);
	void moveUEFrmNonCsgLstToCsgLst(CUEContext*);
   bool isMaxNonCsgUEsAdmitted();
   bool isMaxCsgUEsAdmitted();
   bool isExtraCsgUEsAdmitted();
#if 0
   bool isExtraNonCsgUEsAdmitted();
#endif
   inline U32  getNumActCsgUEs(){ return m_tlCsgActiveUEList.size();};
   inline U32  getNumActNonCsgUEs(){ return m_tlNonCsgActiveUEList.size();};

	bool releaseUE(CUEContext*);
   void updateNewCRNTI(U16 usCRNTI, U16 usNewCRNTI);
	CUEContext* findLeastPriorityUEToRelease(U8	bConnEstablishmentCause);
	CUEContext* admitUE(U16 usCRNTI, U8 bConnEstablishmentCause);
	CUEContext*	findUE(U16 usCRNTI);
	CUEContext* moveUEfromSigLstToActiveLst(CUEContext*);
#ifdef RRM_UNUSED_FUNC
	bool moveUEfromActiveLstToSigLst(CUEContext*);
#endif
	bool isRadioResThrsldReached();
	void updateUECapability(RmuUeCapInfoIe &stUECapability);
   void printStats();
   /**
    * @brief Function to return the establishment cause priority.
    * 
    * @details Function to return the priority of UE establishment cause.
    * 
    * @param[in] estCause UE establihsment cause
    *
    * @return U8
    *        Establishment cause priority 
    */
   static U8 getUeEstCausePrio(U8 estCause) {
      return m_usUeEstCausePriority[estCause];
   };

private:
   std::vector<CUEContext> 	          m_tvUEList;
   std::list<CUEContext*>		          m_tlCsgActiveUEList;
   std::list<CUEContext*>		          m_tlNonCsgActiveUEList;
   std::list<CUEContext*>  	 	       m_tlFreeUEPool;
   std::list<CUEContext*> 	 	 	       m_tlSigUEList;
   std::list<CUEContext*> 	 	 	       m_tlExtUEList;
   std::map<CRNTI, CUEContext*>	       m_tmUE;
   std::map<CRNTI, CUEContext*>::iterator m_itUE;
	U16 							          m_usMaxActiveUEs;
	U16 							          m_usMaxSigUEs;
   U16                               m_bUeIdx[RM_MAX_UES_PER_CELL];
   U16                               m_usTotActUe;
	U16 							          m_usMaxExtraUEs;
   U16                               m_usMaxCsgUes;
   U16                               m_usMaxNonCsgUes;
   /*!< Priority list for UE establishment cause */
   static U8                         m_usUeEstCausePriority[RMU_MAX_EST_CAUSE];
};

#endif /* _RRM_UECONTROLLER_H_ */
/********************************************************************30**

           End of file:     rm_uemanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:41 2013

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
