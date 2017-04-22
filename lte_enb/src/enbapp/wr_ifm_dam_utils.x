

/********************************************************************20**

     Name:     DAM Layer

     Type:     C source file

     Desc:     C Source code for DMA  upper interface structures

     File:     wr_ifm_dam_utils.x

     Sid:      wr_ifm_dam_utils.x@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:53:14 2014

     Prg:      sn

*********************************************************************21*/

#ifndef __WRIFMUTL__X
#define __WRIFMUTL__X

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm_tkns.h"          /* common tokens */
#include "cm_mblk.h"          /* Memory Link List */
#include "wr_ifm_dam_utils.h" /* Event structure file */
#include "wr_ifm_dam.h"       /* Event structure file */

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* Memory Link List typedefs */
#include "cm_lib.x"        /* common ss7 */


/** @file wr_ifm_dam_utils.x
    @brief DAT Interface File (wr_ifm_dam_utils.x) 
*/
/*typedef S16 (*PrnThptReq) ARGS((
      void)); 
*/

typedef S16 (*DamBndReq)     ARGS((
        Pst *, 
        SuId, 
        SpId
        ));

typedef S16 (*DamBndCfm)     ARGS((
        Pst *, 
        SuId, 
        U8
        ));

typedef S16 (*DamUbndReq)    ARGS((
        Pst *, 
        SpId,  
        Reason
        ));


typedef S16 (*DamSetDataRcvdFlag)     ARGS((
        Pst *,
        U16, 
        U16
        ));

typedef S16 (*DamPrnThptReq)     ARGS((
        Pst *
        ));

typedef S16 (*DamTnlCreatReq)     ARGS((
        Pst *,
        U32,
        WrDamTnlInfo *
        ));

typedef S16 (*DamTnlCreatCfm)     ARGS((
        Pst *,
        U32,
        U8,
        U32
        ));

typedef S16 (*DamTnlDelReq)     ARGS((
        Pst *,
        U32,
        WrDamTnlId *
        ));

typedef S16 (*DamUeDelReq)     ARGS((
        Pst *,
        U32,
        U16,
        U16
        ));

typedef S16 (*DamReestabReq)     ARGS((
        Pst *,
        U32,
        U16,
        U16,
        U16
        ));


typedef S16 (*DamReCfgReq)     ARGS((
        Pst *,
        U32,
        U16,
        U16
        ));

typedef S16 (*DamCellAddReq)     ARGS((
        Pst *,
        WrDamCellInfo *
        ));

typedef S16 (*DamTnlStChngReq)     ARGS((
        Pst *,
        WrDamTnlStInfo *
        ));

typedef S16 (*DamReestabCfm)     ARGS((
        Pst *,
        U32,
        U8
        ));

typedef S16 (*DamStartInactivityTmr)     ARGS((
        Pst *,
        U16,
        U16
        ));

typedef S16 (*DamStopUeTmr)     ARGS((
        Pst *,
        U16,
        U16
        ));

typedef S16 (*DamSendCtxtRel)     ARGS((
        Pst *,
        U16,
        U16,
        U8
        ));

typedef S16 (*DamHoFailure)     ARGS((
        Pst *,
        U16,
        U16
        ));

typedef S16 (*DamCfgReq)     ARGS((
        Pst *,
        LwrMngmt *
        ));

typedef S16 (*DamCntrlReq)     ARGS((
        Pst *,
        LwrMngmt *
        ));

typedef S16 (*DamTnlModReq)     ARGS((
        Pst *,
        U32, 
        WrDamTnlModInfo *
        ));

typedef S16 (*DamCfgCfm)     ARGS((
        Pst *,
        LwrMngmt *, 
        CmStatus *
        ));

typedef S16 (*DamCntrlCfm)     ARGS((
        Pst *,
        LwrMngmt *, 
        CmStatus *
        ));


typedef S16 (*DamSendAlarmInd)     ARGS((
        Pst *,
        U16, 
        U16,
        U16
        ));


typedef S16 (*DamTnlModCfm)     ARGS((
        Pst *,
        U32, 
        U8,
        U32
        ));
 
typedef S16 (*DamPdcpDatCfm)     ARGS((
        Pst *,
        CmLtePdcpId 
        )); 

typedef S16 (*DamEgtpErrInd)     ARGS((
        Pst *,
        U32,
        U32,
        U16
        ));  

typedef S16 (*DamUeDelCfm)     ARGS((
        Pst *,
        U32,
        U16,
        U16
        ));         
/* Pack Function Prototype */
EXTERN S16 cmPkUeDelReq ARGS ((Pst *pst,U32 transId,U16 cellId,U16 crnit));

EXTERN S16 cmPkUeDelCfm ARGS ((Pst *pst,U32 transId,U16 cellId,U16 crnit));

EXTERN S16 cmPkCellAddReq ARGS ((Pst *pst, WrDamCellInfo *cellInfo));

EXTERN S16 cmPkTnlCreatReq ARGS((Pst *pst,U32 transId,WrDamTnlInfo *tnlInfo));

EXTERN S16 cmPkTnlCreatCfm ARGS((Pst * pst,U32 transId,U8 status,U32 lclTeid));

EXTERN S16 cmPkTnlDelReq   ARGS((Pst *pst,U32 transId,WrDamTnlId *tnlId ));

EXTERN S16 cmPkTnlStChngReq ARGS((Pst *pst,WrDamTnlStInfo *tnlStInfo));

EXTERN S16 cmPkReestabReq ARGS((Pst *pst,U32 transId,U16 cellId,U16 oldcrnti,U16  newcrnti));

EXTERN S16 cmPkReestabCfm ARGS((Pst * pst,U32 transId,U8 status));

EXTERN S16 cmPkReCfgReq ARGS((Pst *pst,U32 transId,U16 cellId,U16 crnti));

EXTERN S16 cmPkPrnThptReq ARGS((Pst* pst));
EXTERN S16 cmPkEgtpErrInd ARGS((Pst* pst, U32 lclTeid,U32 numDrbs,U16 crnti));
EXTERN S16 cmPkDamPdcpDatCfm ARGS((Pst* pst, CmLtePdcpId pdcpId));
EXTERN S16 cmPkTnlModCfm ARGS((Pst* pst, U32 transId, U8 status, U32 lclTeid ));

EXTERN S16 cmPkStartInactivityTimer ARGS((Pst *pst,U16 cellId,U16 crnti));
EXTERN S16 cmPkStopUeTmr ARGS((Pst *pst,U16 cellId,U16 ueId));
EXTERN S16 cmPkDamSendCtxtRel ARGS((Pst *pst,U16 crnti,U16 CellId,U8 event));
EXTERN S16 cmPkSetDataRcvdFlag ARGS((Pst *pst,U16 cellId,U16 ueId));/*ccpu00138576*/
EXTERN S16 cmPkDamBndReq ARGS((Pst *pst,SuId suId,SpId spId));
EXTERN S16 cmPkDamBndCfm ARGS((Pst *pst,SuId suId,U8 status));

EXTERN S16 DaUiDatBndReq ARGS (( Pst *pst, SuId suId, SpId spId));

/* Element Pack Functions */
EXTERN S16 cmPkCmTnlInfo ARGS (( WrDamTnlInfo  *tnlInfo,Buffer  *mBuf)); 


EXTERN S16 cmPkDamTnlId ARGS ((WrDamTnlId  *tnlId,Buffer  *mBuf ));
EXTERN S16 cmPkDamCellInfo ARGS ((WrDamCellInfo  *cellInfo,Buffer  *mBuf ));

EXTERN S16 cmPkHdlHoFailure ARGS((Pst *pst,U16 cellId,U16 crnti ));

EXTERN S16 cmPkDamCntrlReq ARGS((Pst *pst,LwrMngmt *cntrl));
EXTERN S16 cmPkDamCfgReq ARGS((Pst *pst,LwrMngmt *cfg));
EXTERN S16 cmPkTnlModReq ARGS((Pst *pst,U32 transId,WrDamTnlModInfo *tnlModInfo));

/* Unpack function prototype */

EXTERN S16 cmUnpkPrnThptReq
ARGS((
DamPrnThptReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnPkTnlCreatReq 
ARGS((
DamTnlCreatReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnPkTnlCreatCfm 
ARGS((
DamTnlCreatCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnPkTnlDelReq
ARGS((
DamTnlDelReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkUeDelReq
ARGS((
DamUeDelReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkReestabReq
ARGS((
DamReestabReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkReCfgReq 
ARGS((
DamReCfgReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkCellAddReq 
ARGS((
DamCellAddReq func,
Pst *pst,
Buffer *mBuf
));


EXTERN S16 cmUnPkTnlStChngReq 
ARGS((
DamTnlStChngReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkReestabCfm
ARGS((
DamReestabCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkStartInactivityTmr 
ARGS((
DamStartInactivityTmr func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkStopUeTmr 
ARGS((
DamStopUeTmr func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkDamSendCtxtRel 
ARGS((
DamSendCtxtRel func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnPkHdlHoFailure
ARGS((
DamHoFailure func,
Pst *pst,
Buffer *mBuf
));

/*ccpu00138576 - start*/
EXTERN S16 cmUnPkSetDataRcvdFlag 
ARGS((
DamSetDataRcvdFlag func,
Pst *pst,
Buffer *mBuf
));
/*ccpu00138576 - end*/


EXTERN S16 cmUnpkDamBndReq 
ARGS((
DamBndReq func,
Pst *pst,
Buffer *mBuf
));


EXTERN S16 cmUnpkDamBndCfm 
ARGS((
DamBndCfm func,
Pst *pst,
Buffer *mBuf
));


EXTERN S16 cmUnpkDamCfgReq
ARGS((
DamCfgReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkDamCntrlReq
ARGS((
DamCntrlReq func,
Pst *pst,
Buffer *mBuf
));


EXTERN S16 cmUnpkTnlModReq
ARGS((
DamTnlModReq func,
Pst *pst,
Buffer *mBuf));

#ifdef TIP_L3_UL2_LL2_SPLIT
EXTERN S16 cmUnpkDamCfgCfm 
ARGS((
DamCfgCfm func,
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnpkDamCntrlCfm 
ARGS((
DamCntrlCfm func,
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnpkDamSendAlarmInd 
ARGS((
DamSendAlarmInd func,
Pst *pst,
Buffer *mBuf));
#else
EXTERN S16 cmUnpkDamCfgCfm 
ARGS((
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnpkDamCntrlCfm 
ARGS((
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnpkDamSendAlarmInd 
ARGS((
Pst *pst,
Buffer *mBuf));

#endif
EXTERN S16 cmUnpkTnlModCfm 
ARGS((
DamTnlModCfm func,
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnpkDamPdcpDatCfm 
ARGS((
DamPdcpDatCfm func,
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnpkEgtpErrInd 
ARGS((
DamEgtpErrInd func,
Pst *pst,
Buffer *mBuf));

EXTERN S16 cmUnPkUeDelCfm 
ARGS((
DamUeDelCfm func,
Pst *pst,
Buffer *mBuf));

#endif

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
