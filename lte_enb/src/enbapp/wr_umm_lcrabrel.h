
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_lcrabrel.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_LCRABREL_H__
#define __WR_UMM_LCRABREL_H__

#include "wr.h"
#include "wr_cmn.h"
#include "wr_umm.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/* The below two definitions are for field schdCfgState in structure      */
/*   WrUmmRabRelRabInfo                                                 */
#define WR_RAB_REL_SCHD_CFG_IDLE 0
#define WR_RAB_REL_SCHD_CFG_SENT 1
#define WR_RAB_REL_SCHD_CFM_FAIL 2
#define WR_RAB_REL_SCHD_CFM_SUCC 3

/** 
  * @brief This is a structure for Local Rab Release 
  * transaction each RAB information. 
  * @details The structure members 
  * - U8                        erabId       E-RAB ID 
  * - U8                        drbId        Data Radio Bearer Id
  * - U8                        lchId        Logical channel Id
  * - U8                        schdCfgState SCHD Cfg state
  */
typedef struct wrUmmLcRabRelInfo
{
   U8                        erabId;
   U8                        drbId;
   U8                        lchId;
   U8                        schdCfgState;
   U8                        qci;/*Added for KPI*/
} WrUmmLcRabRelInfo;

/* The following definitions are for the field status in the structure    */
/* below.                                                                 */
#define WR_UMM_RAB_REL_INITIATED      0
#define WR_UMM_RAB_REL_SCHD_CFG_DONE  1
#define WR_UMM_RAB_REL_STACK_CFG_DONE 2
#define WR_UMM_RAB_REL_SCHD_CFG_DRX   3
/** 
  * @brief This is a structure for Local RAB Release 
  * transaction. 
  * @details The structure members 
  * - U8                        transId       Transaction ID
  * - U32                       state         State within transaction
  * - U32                       numRabs       Num. of RABs to be deleted
  * - WrUmmRabRelRabInfo        *rabs         substructure for each RAB Info
  * - Bool                      isDrbCfgDone  Flag to determine CFG state of DRB 
  * - Void                      *msg          Copy of Incoming message
  * - U8                        cause         Cause value for Rab to be deleted
  * - U8                        causeTyp      Cause type  for Rab to be deleted
 */
typedef struct wrUmmLcRabRelTransCb
{
   U8                        transId;
   U32                       state;
   U32                       numRabs;
   void                      *msg;
   WrUmmLcRabRelInfo         rabs[WR_MAX_DRBS];
   U8                        cause[WR_MAX_DRBS];/*RRM_ARP*/
   U8                        causeTyp;
   Bool                      isDrbCfgDone;
   WrUmmIncMsg               *rrmUeRecfgRspMsg;
} WrUmmLcRabRelTransCb;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_LCRABREL_H__ */


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
