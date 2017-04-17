
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_rabrel.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_RABREL_H__
#define __WR_UMM_RABREL_H__

#include "wr.h"
#include "wr_cmn.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/* The below two definitions are for field schdCfgState in structure      */
/*   WrUmmRabRelRabInfo                                                 */
#define WR_RAB_REL_SCHD_CFG_IDLE 0
#define WR_RAB_REL_SCHD_CFG_SENT 1
#define WR_RAB_REL_SCHD_CFM_FAIL 2
#define WR_RAB_REL_SCHD_CFM_SUCC 3

#define WR_UMM_RAB_REL_UE_CFG_SENT   0x01
#define WR_UMM_RAB_REL_LCG_CFG_SENT  0x02
#define WR_UMM_RAB_REL_LCH_CFG_SENT  0x04
#define WR_UMM_RAB_REL_UE_CFG_RECVD  0x08
#define WR_UMM_RAB_REL_LCG_CFG_RECVD 0x10
#define WR_UMM_RAB_REL_LCH_CFG_RECVD 0x20
#define WR_UMM_RAB_REL_CFG_RECVD (WR_UMM_RAB_REL_UE_CFG_RECVD | WR_UMM_RAB_REL_LCG_CFG_RECVD | WR_UMM_RAB_REL_LCH_CFG_RECVD)

#define WR_RAB_REL_UE_TRANS_ID       0x0f

/** 
  * @brief This is a structure for Rab Release 
  * transaction each RAB information. 
  * @details The structure members 
  * - U8                        erabId       E-RAB ID 
  * - Bool                      rabfailed    Flag to say RAB can be deleted              
  * - U8                        drbId        Data Radio Bearer Id
  * - U8                        lchId        Logical channel Id
  * - U8                        schdCfgState SCHD Cfg state
  * - U8                        cause        Cause for Rab to delete 
  */

typedef struct wrUmmRabRelRabInfo
{
   U8                        erabId;
   Bool                      rabfailed;
   U8                        drbId;
   U8                        lchId;
   U8                        schdCfgState;
   U8                        cause;
   WrUmmMsgCause             relCause;     /* Added cause value for E-Rab Setup procedures */
   U8                        qci; /*Added for KPI*/
   /* SPS changes starts */
   Bool                      isDlSpsEnabled;
   Bool                      isUlSpsEnabled;
   /* SPS changes ends */
} WrUmmRabRelRabInfo;

/* The following definitions are for the field status in the structure    */
/* below.                                                                 */
#define WR_UMM_RAB_REL_INITIATED      0
#define WR_UMM_RAB_REL_SCHD_CFG_DONE  1
#define WR_UMM_RAB_REL_STACK_CFG_DONE 2
#define WR_UMM_RAB_REL_SCH_CFG_DRX    4
/** 
  * @brief This is a structure for RAB Release 
  * transaction. 
  * @details The structure members 
  * - U8                        transId       Transaction ID
  * - U32                       dlAmbr        Downlink AMBR value
  * - U32                       ulAmbr        Uplink AMBR  value
  * - U32                       state         State within transaction
  * - U32                       numRabs       Num. of RABs to be deleted
  * - WrUmmRabRelRabInfo        *rabs         substructure for each RAB Info
  * - Bool                      isDrbCfgDone  Flag to determine CFG state of DRB 
  * - Void                      *msg          Copy of Incoming message
  * - TknStrOSXL                *nasPdu       Copy of NAS PDU
  * - U8                        isUeAggrMaxBitRateRcvd
  *                             Flag to indication if AMBR is recvd in message
  * - U32                       cfgStateMsk   Bitmask to maintain Schedular msg state
 */

typedef struct wrUmmRabRelTransCb
{
   U8                        transId;
   U32                       dlAmbr;
   U32                       ulAmbr;
   U32                       state;
   U32                       numRabs;
   WrUmmRabRelRabInfo        *rabs;
   Bool                      isDrbCfgDone;
   Void                      *msg;
   TknStrOSXL                *nasPdu;
   U8                        numRabsFound;
   Bool                      schdUeCfgCfmRcvd;
   WrUmmIncMsg               *rrmUeRecfgRspMsg;
   /*DRX QCI*/
   WrUmmMeasTransInfo        measTransCb;
   U8                        isUeAggrMaxBitRateRcvd;
   U32                       cfgStateMsk;
   U8                        lcgCfgStatus[WR_UMM_MAX_LCG_GRP_ID];
} WrUmmRabRelTransCb;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_RABREL_H__ */


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
