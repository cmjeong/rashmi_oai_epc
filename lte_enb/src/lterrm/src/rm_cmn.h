
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               

     File:     rm_cmn.h

     Sid:      rm_cmn.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:39 2013

     Prg:      hkrishna, jbm 

*********************************************************************21*/


#ifndef __RM_CMN_H__
#define __RM_CMN_H__


   /* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list  defines  */
#include "cm_hash.h"       /* Common hashlist  defines */
#include "cm_lte.h"        /* Common LTE defines */
#include "cm_inet.h"
#include "cm_tpt.h"
#include "szt_asn.h"       /* S1AP RRM control Interface */
#include "rmu.h"
#include "lrm.h"

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lte.x"       /*  Common UMTS includes */
#include "cm_lib.x"
#include "cm_inet.x"
#include "cm_tpt.x"
#include "cm_lte.x"
#include "cm_lte_rrm.x"

#include "ss_diag.h"

#include "rmu.h"
#include "rmu.x"
#include "lrm.h"
#include "lrm.x"
#include "rgm.h"
#include "rgm.x"

#include "rm.h"

extern RmCb g_stRmCb;

#define RM_NUM_SF_PER_SFN             10 

#define RM_RCM_MAX_UES_SUPPORTED TENB_MAX_UE_SUPPORTED
#define RM_NUM_CQI_RES_PER_RB         12
#define RM_RCM_MAX_OFFSET_ARRAY_SIZE  160

#define RM_RBC_GBR_MIN_QCI   1  /*!< Minumum GBR QCI number */
#define RM_RBC_GBR_MAX_QCI   4  /*!< Maximum GBR QCI number */
#define RM_RBC_MAX_QCI       9  /*!< Maximum QCI number */

/*!< MIN ARP value for an ERAB  */
#define MIN_ARP_VAL     1

/*!< MAX ARP value for an ERAB  */
#define MAX_ARP_VAL     15

/*!< Contails all the possible GBR QCI numbers */
enum rmGbrQciNum
{
   RM_QCI_ONE=1,  /*!< Value of QCI 1 */
   RM_QCI_TWO,    /*!< Value of QCI 2 */
   RM_QCI_THREE,  /*!< Value of QCI 3 */
   RM_QCI_FOUR    /*!< Value of QCI 4 */
};

/*!< Returns the divide and round off the value */
#define RM_ROUND(_x, _y) (((_x) + (_y)/2) / (_y))

/*!< Macro for 5ms Periodicity */
#define RM_RCM_SR_PERIODICTY_5MS  5

/**
 * @brief  Structure to hold the required GBR PRBs in % for accepted bearer
 *         by Radio Admission controller.
 * 
 * @details
 * - uiReqPrbForDl : Number of DL PRBs required in % for to satisfy the DL GBR.
 * - uiReqPrbForUl : Number of UL PRBs required in % for to satisfy the UL GBR.
 * - bERabId : ERAB Identity. 
 */
typedef struct rrmErabAdmitted
{
   U32  uiReqPrbForDl;  /*!< Required PRB for DL */
   U32  uiReqPrbForUl;  /*!< Required PRB for UL */
   U8   bERabId;       /*!< ERAB Identifier */
} RrmErabAdmitted;

/**
 * @brief  Structure to hold the required GBR PRBs in % for rejected bearer
 *         by Radio Admission controller.
 * 
 * @details
 * - uiReqPrbForDl : Number of DL PRBs required in % for to satisfy the DL GBR.
 * - uiReqPrbForUl : Number of UL PRBs required in % for to satisfy the UL GBR.
 * - uiDiffPrbForDl: Difference of DL PRBs during modification of DL GBR
 * - uiDiffPrbForUl: Difference of UL PRBs during modification of UL GBR
 * - uiQci   : QoS Class Identifier
 * - bArpVal : ARP value of rejected ERAB. 
 * - bCause  : cause for ERAB rejection. 
 * - bERabId : ERAB Identity. 
 * - bIsPreemptable : Pre-emption Vulnerability
 * - bErabPreemptCap : Pre-emption Capability
 * - bIsModifyReq  : Modification Request flag
 */
typedef struct rrmErabRejected
{
   U32   uiReqPrbForDl;  /*!< Required PRB for DL */
   U32   uiReqPrbForUl;  /*!< Required PRB for UL */
   U32   uiDiffPrbForDl;  /*!< Difference PRB for DL */
   U32   uiDiffPrbForUl;  /*!< Difference PRB for UL */
   U32   uiQci;         /*!< QCI Value */
   U8    bArpVal;        /*!< ARP value of ERAB*/
   U8    bCause;         /*!< Cause Value*/
   U8    bERabId;        /*!< ERAB Identifier*/
   bool  bIsPreemptable; /*!< Pre-emption Vulnerability */
   bool  bErabPreemptCap; /*!< Pre-emption Capability */
   bool  bIsModifyReq;    /*!< Modification Request flag*/
} RrmErabRejected;

/**
 * @brief  Structure to hold the Response information(like accepted/rejected
 *         bearers information) by Radio Admission controller.
 * 
 * @details
 * - eRabAcceptedLst : Accepted bearers information.
 * - eRabRejectedLst : Rejected bearers information.
 * - nErabsAccepted : Number of bearers accepted. 
 * - nErabsRejected : Number of berarers rejected. 
 * - isGBRBearerExists : Is at least one GBR bearer exists. 
 */
typedef struct rrmRbcRspInfo
{
  RrmErabAdmitted   eRabAcceptedLst[RMU_MAX_NUM_ERABS];/*!<accepted bearer information */ 
  RrmErabRejected   eRabRejectedLst[RMU_MAX_NUM_ERABS];/*!<Rejected bearer information*/
  U8                nErabsAccepted;/*!<Number of bearers accepted */
  U8                nErabsRejected;/*!<Number of bearers rejected */       
  bool              isGBRBearerExists;/*!<does at least one GBR bearer exists */
  U16               usCRNTI; /*!< CRNTI of the UE */
} RrmRbcRspInfo;

/*!< Contains the UL subframe info */
typedef struct rmTddUlSfInfo
{
   U8 bNumUlSfs;                    /*!< Number of Feedbacks for DL Subframes */
   U8 bUlSfNum[RM_NUM_SF_PER_SFN];  /*!< List of Subframe Number */
} RmTddUlSfInfo;

/*!< Contails the duplex modes */
typedef enum rmDuplexMode
{
    RM_MODE_FDD=1,   /*!< FDD mode */
    RM_MODE_TDD      /*!< TDD mode */
} RmDuplexMode;

class CRmRcmResMgr
{
   public:
    U16  getAvailUlSubframeLst(U16 usSrPrdcty, U16  *usAvalUlSfs);
    static U8   getNumUlSf(LrmUlDlConfig enUlDlConfig);

   public:
      static RmTddUlSfInfo m_astRmTddUlSfInfo[LRM_UL_DL_CONFIG_MAX];

   public:
      LrmUlDlConfig m_enUlDlCfg;
      U16 m_usMaxActiveUeCount;
      U16 m_usMaxDlUePerTti;
      U16 m_usN1Pucch;
};

    
inline U8 CRmRcmResMgr::getNumUlSf(LrmUlDlConfig enUlDlConfig)
{
   return m_astRmTddUlSfInfo[enUlDlConfig].bNumUlSfs;
}

inline U8* rrmAlloc(U16 usMsgLen)
{
	U8 *pbMsg;
	RM_ALLOC(&pbMsg, usMsgLen);
	return pbMsg;
}

inline void rrmFree(U8* pbMsg, U16 usMsgLen)
{
	RM_FREE(pbMsg, usMsgLen);
}

#endif /* __RM_CMN__H__ */
/********************************************************************30**

           End of file:     rm_cmn.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:39 2013

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
