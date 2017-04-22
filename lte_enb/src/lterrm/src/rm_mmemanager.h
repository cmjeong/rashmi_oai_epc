
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               

     File:     rm_mmemanager.h

     Sid:      rm_mmemanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:39 2013

     Prg:      hkrishna, vkorade 

*********************************************************************21*/


#ifndef RM_MME_H_
#define RM_MME_H_


typedef enum 
{
   RM_MME_STATE_UP,
   RM_MME_STATE_DOWN,
   RM_MME_STATE_INIT
} RmMmeState;

#include "rm_cmn.h"
#include <map>

typedef struct rmMMeInfo
{
	U16 usMmeId;
	RmMmeState enMmeState;
	RmuMmeOvldStatus enMmeOvldStatus;
} RmMmeInfo;

typedef U16 MMEID;

class CMMEManger
{
public:
	static CMMEManger & getInstance();
	LrmCause addMME(LrmMmeCfg & stMmeCfg);
#ifdef RRM_UNUSED_FUNC
	LrmCause modifyMME(LrmMmeCfg & stMmeCfg);
#endif
	LrmCause deleteMME(LrmMmeCfg & stMmeCfg);
	RmuMmeOvldStatus handleMMEOvldStart(RmuMmeOvldStartInd & stMmeOvldStrtInd);
	RmuMmeOvldStatus handleMmeOverloadStop(RmuMmeOvldStopInd & stMmeOvldStopInd);
	RmuMmeOvldStatus upMME(U16 usMmeId);
	RmuMmeOvldStatus downMME(U16 usMmeId);

public:
	CMMEManger();

private:
	RmuMmeOvldStatus updateMMEOverloadStatus();
#ifdef RRM_UNUSED_FUNC
	void printMmes();
#endif


private:
	std::map<MMEID, RmMmeInfo> m_tmMme;
	static CMMEManger m_objMME;
	RmuMmeOvldStatus m_enMMEOverloadStatus;
	U8 m_bActiveMmesCnt;
	U8 m_bOverloadedMmesCnt;
	RmuMmeOvldStatus m_enHighPriOvldStatus;
};


#endif /* RM_MME_H_ */
/********************************************************************30**

           End of file:     rm_mmemanager.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:39 2013

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
