
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_scell.h

     Sid:      wr_umm_scell.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:28 2014

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_SCELL_H__
#define __WR_UMM_SCELL_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#include "wr_umm_msg.h"
#define WR_UMM_SCH_TRANS_SCELL_ADD 0x01
#define WR_UMM_SCH_TRANS_SCELL_ACT 0x02
/*sprint4_scelldeletedeact_changes*/   
#define WR_UMM_SCH_TRANS_SCELL_RELEASE 0x04
#define WR_UMM_SCH_TRANS_SCELL_DEACT 0x08
#define WR_UMM_SCH_TRANS_SCELL_READY 0x10
/*sprint4_scelldeletedeact_changes*/   

#ifdef LTE_ADV

#define WR_UMM_APER_CSI_TGR_MASK 0x01
EXTERN Bool wrUtlGetSCellDeActTmrVal(
  U32    sCellDeActTmr,
  U32   *actTmr
);

EXTERN S16 wrUtlFillAddModSCell
(
 NhuSCellToAddMod_r10  *member,
 WrSCellInfo           *sCellInfo,
 WrUeCb                *ueCb, 
 NhuDatReqSdus         *recfgMsg
);

typedef struct wrUmmSCellPrcInfo
{
   WrUmmScellAction         action;
   WrSCellInfo           *sCellInfo; /* This is pointer of each SCellInfo.*/
}WrSCellTransInfo;

/*! states for rollback in case of failures*/
typedef enum wrUmmRollBackState
{
   WR_UMM_SCELL_ROLLBACK_INVALID,/*For SCell Release case*/
   WR_UMM_SCELL_ROLLBACK_RRM_INFO,/*To revert RRM SCell Add Cfg*/
   WR_UMM_SCELL_ROLLBACK_RRM_CTF_INFO,/*To revert RRM and CTF SCell Add Cfg*/
   WR_UMM_SCELL_ROLLBACK_RRM_CTF_SCH_INFO/*To revert RRM,CTF and SCH SCell Add Cfg*/
}WrUmmRollBackState;

/*! secondary cell structure*/
typedef struct wrUmmSCellTransCb
{
   U8                    numSCells;/*number of Secondary cells*/
   WrUmmRollBackState    rollBackState;/*state that describes the failure handling*/
   WrUmmScellAction      triggerTyp;/*action for the SCell*/
   WrSCellTransInfo      sCellTransInfo[WR_MAX_SCELL_PER_UE]; /* This is array of pointer of SCells.*/
}WrUmmSCellTransCb;
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*End of _WR_UMM_SCELL_H__*/


