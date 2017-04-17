
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_rabmod.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_RABMOD_H__
#define __WR_UMM_RABMOD_H__

#include "wr.h"
#include "wr_cmn.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/* The below two definitions are for field schdCfgState in structure      */
/*   WrUmmRabModifyRabInfo                                                 */
#define WR_RAB_MODIFY_SCHD_CFG_IDLE 0
#define WR_RAB_MODIFY_SCHD_CFG_SENT 1
#define WR_RAB_MODIFY_SCHD_CFM_FAIL 2
#define WR_RAB_MODIFY_SCHD_CFM_SUCC 3
#define WR_RAB_MODIFY_SCHD_CFM_FAIL_RVRT 4


#define WR_UMM_RAB_MODIFY_UE_CFG_SENT   0x01
#define WR_UMM_RAB_MODIFY_LCG_CFG_SENT  0x02
#define WR_UMM_RAB_MODIFY_LCH_CFG_SENT  0x04
#define WR_UMM_RAB_MODIFY_UE_CFG_RECVD  0x08
#define WR_UMM_RAB_MODIFY_LCG_CFG_RECVD 0x10
#define WR_UMM_RAB_MODIFY_LCH_CFG_RECVD 0x20
#define WR_UMM_RAB_MODIFY_CFG_RECVD (WR_UMM_RAB_MODIFY_UE_CFG_RECVD | WR_UMM_RAB_MODIFY_LCG_CFG_RECVD | WR_UMM_RAB_MODIFY_LCH_CFG_RECVD)

/** @brief This structure contains the ARP info of the Radio Access Bearer
 *
 - U16           priority  - This idicates the prioriy of the bearer
 - Bool          preemptCap   - This indicates the preemption capability of the bearer
 - Bool          preemptVulnerability  - This indicates the preemption vulnerability
*/
typedef struct wrUmmRabArpInfo
{
   U32                        priorityLvl;
   U32                        preemptCapability;
   U32                        preemptVulnerability;
} WrUmmRabArpInfo;

/** 
  * @brief This is a structure for Rab Modify 
  * transaction each RAB information. 
  * @details The structure members 
  * - U8                        qci          QCI Value
  * - U8                        erabId       E-RAB ID 
  * - U8                        rabAllowed   Rab Allowed flag
  * - Bool                      rabfailed    Flag to say rab failed to modify             
  * - U8                        drbId        Data Radio Bearer Id
  * - U8                        lchId        Logical channel Id
  * - U8                        schdCfgState SCHD Cfg state
  * - U32                       ulGbr        UL Gauranteed Bit Rate 
  * - U32                       dlGbr        DL Gauranteed Bit Rate  
  * - U32                       ulMbr        UL Maximum Bit Rate 
  * - U32                       dlMbr        DL Maximum Bit Rate 
  * - TknStrOSXL                *nasPdu      NAS PDU for each RAB
  */
typedef struct wrUmmRabModifyRabInfo
{
   U8                        qci;
   U8                        erabId;
   U8                        drbId;
   Bool                      rabAllowed;     /* Removed rabFailed as per the comments*/
   U8                        rlcMode;
   U8                        lchId;
   U8                        schdCfgState;
   U8                        schdRvrtCfgCfmCnt;
   U32                       ulGbr;
   U32                       dlGbr;
   U32                       ulMbr;
   U32                       dlMbr;
   TknStrOSXL                *nasPdu;
   WrUmmRabArpInfo           arpInfo;
   WrUmmMsgCause             cause;           /* Added cause value for E-Rab Modify procedures */
   /* SPS changes starts */
   Bool                      isDlSpsEnabled;
   Bool                      isUlSpsEnabled;
   /* SPS changes ends */
   Bool                      isQciChanged;
} WrUmmRabModifyRabInfo;

/* The following definitions are for the field status in the structure    */
/* below.                                                                 */
#define WR_UMM_RAB_MODIFY_INITIATED      0
#define WR_UMM_RAB_MODIFY_SCHD_CFG_DONE  1
#define WR_UMM_RAB_MODIFY_STACK_CFG_DONE 2
#define WR_UMM_RAB_MODIFY_SCHD_DRX_CFG_DONE  3
#define WR_UMM_RAB_MODIFY_SCHD_CFG_RVRT_DONE 4
/** 
  * @brief This is a structure for RAB modify 
  * transaction. 
  * @details The structure members 
  * - U8                        transId          Transaction ID
  * - U32                       dlAmbr           Downlink AMBR value
  * - U32                       ulAmbr           Uplink AMBR  value
  * - U32                       state            State within transaction
  * - U32                       numRabs          Num. of RABs to be modify 
  * - WrUmmRabRelRabInfo        *rabs            substructure for each RAB Info
  * - Bool                      isDrbCfgDone     Flag to determine CFG state of DRB 
  * - Void                      *msg             Copy of Incoming message
  * - U8                        isUeAggrMaxBitRateRcvd
  *                             Flag to indication if AMBR is recvd in message
  * - U32                       cfgStateMsk      Bitmask to maintain Schedular msg state
 */
typedef struct wrUmmRabModifyTransCb
{
   U8                        transId;
   U32                       dlAmbr;
   U32                       ulAmbr;
   U32                       state;
   U32                       numRabs;
   WrUmmRabModifyRabInfo     *rabs;
   Void                      *msg;
   Bool                      isDrbCfgDone;
   Bool                      schdUndoCfgState;
   Bool                      rrmConfigRvrt;
   U8                        numRabsFound;
   WrUmmIncMsg               *rrmUeRecfgRspMsg;
   /* SPS changes starts */
   Bool                      isDlSpsEnabled;
   Bool                      isUlSpsEnabled;
   /* SPS changes ends */
   U8                        isUeAggrMaxBitRateRcvd;
   U32                       cfgStateMsk;
   U8                        lcgCfgStatus[WR_UMM_MAX_LCG_GRP_ID];
   U8                        expectedLcgCfgStatus;
   Bool                      allRabsFailed;
} WrUmmRabModifyTransCb;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_RABMOD_H__ */

/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
