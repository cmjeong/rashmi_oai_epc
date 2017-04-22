
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_dam.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_IFM_DAM_H__
#define __WR_IFM_DAM_H__

#include "wr.h"
#include "wr_dam.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#define EVTDAMCREATEEGTPTUNEL       1
#define EVTDAMCREATEEGTPTUNELCFM    2
#define EVDAMMODIFYEGTPTUNEL        3
#define EVTDAMDELEGTPTUNEL          4
#define EUTXXX 1

/** @def WR_DAM_CFG_OK 
 * This Macro defines the Configuration Status Success.
 */
#define WR_DAM_CFG_OK               0

/** @def WR_DAM_CFG_FAIL
 * This Macro defines the Configuration Status Fail.
 */
#define WR_DAM_CFG_FAIL             1

/* structure definitions to be used beween DAM and other modules */
   
/**
 *@brief This defines the EGTP TEID. 
 */
typedef U32                  WrEgtpTeid;

/**
 *@brief This structure contains the DAM Configuration. 
 *
 *@details These are the structure members
 * - U32      inactvTmrVal   Inactive Timer Value
 * - U32      endMrkTmrVal   End Marker Timer Value
 */
typedef struct wrDamCfg
{
   U32                       inactvTmrVal;
   U16                       expiryCnt; 
   U32                       endMrkTmrVal;
} WrDamCfg;

/**
 *@brief This structure contains the DAM Cell Info. 
 *
 *@details These are the structure members
 * - U16     cellId        Cell ID.
 * - U16     startRnti     Start RNTI.
 * - U16     maxRntis      Max RNTIs.
 */
typedef struct wrDamCellInfo
{
   U16                       cellId;
   U16                       startRnti;
   U16                       maxRntis;
} WrDamCellInfo;

/**
 *@brief This structure describes the types of the tunnel
 *
 *@details These are the values of enumerations
 * - WR_TNL_NORMAL         Normal Tunnel
 * - WR_TNL_DL_DATFWD      Downlink Data forwarding tunnel
 * - WR_TNL_UL_DATFWD      Uplink Data forwarding tunnel
 */


typedef enum wrTnlType{
      WR_TNL_NORMAL,
      WR_TNL_DL_DATFWD,
      WR_TNL_UL_DATFWD
} WrDamTnlType;

/**
 *@brief This structure contains the DAM Tunnel ID. 
 *
 *@details These are the structure members
 * - U16     cellId        Cell ID.
 * - U16     crnti         CRNTI.
 * - U8      drbId         DRB ID.
 * - WrDamTnlType tnlType  Type of the tunnel
 */
typedef struct wrDamTnlId
{
   U16                       cellId;
   U16                       crnti;
   U8                        drbId;
   WrDamTnlType              tnlType;
   U8                        tnlPriority;
} WrDamTnlId;

/**
 *@brief This structure contains the DAM Tunnel Information. 
 *
 *@details These are the structure members
 * - U32            transId      Transaction ID.
 * - WrDamTnlId     tnlId        Tunnel ID.
 * - U8             dscp         DSCP Value.
 * - WrDamTnlType   tnlType      Type of the tunnel
 * - CmTptAddr      dstAddr      Destination Addresses
 * - CmTptAddr      srcAddr      Source Address.
 * - WrEgtpTeid     remTeid      Remote TEID.
 * - Bool           isFullCfg    indicate the need for full configuration during HO
 */
typedef struct wrDamTunInfo
{
   U32                       transId;
   WrDamTnlId                tnlId;
   U8                        dscp;
   WrDamTnlType              tnlType;
   CmTptAddr                 dstAddr;
   CmTptAddr                 srcAddr;
   WrEgtpTeid                remTeid;
   Bool                      hoSrcEnodeb;
   WrHoType                  hoType;
   Bool                      isFullCfg;     /* RRC-REL10-Upgrade */
} WrDamTnlInfo;

/**
 *@brief This structure contains the DAM Tunnel Information for modifying a tunnel. 
 *
 *@details These are the structure members
 * - U32            transId      Transaction ID.
 * - WrDamTnlId     tnlId        Tunnel ID.
 * - CmTptAddr      newDstAddr      New Destination Addresses
 */
typedef struct wrDamTunModInfo
{
   U32                       transId;
   WrDamTnlId                tnlId;
   U32                       remTeid;
   CmTptAddr                 newDstAddr;
   U8                        dscp;     /*dscp value for the tunnel */
} WrDamTnlModInfo;

/**
 *@brief This structure contains the DAM Configuration. 
 *
 *@details These are the structure members
 * - U32      inactvTmrVal   Inactive Timer Value
 */
typedef struct wrDamTnlStInfo
{
   U32                 transId;
   U16                 state;
   U16                 cause;
   WrEgtpTeid          lclTeid;
} WrDamTnlStInfo;

/* Adding for handling the bind request */
EXTERN S16 WrIfmDatBndReq(Pst *pst, SuId suId, SpId spId);

//EXTERN DamTnlCreatReq WrDamTnlCreatReq;

/* DAM initialization function which is called as part of system init     */
EXTERN S16 wrIfmDamWrCfg(WrDamCfg *cfg);
EXTERN S16 wrDamCfg(WrDamCfg *cfg);

/* DAM tunnel creation which is responsible for creating a eGTP tunnel    */
/* for a data bearer. The association between tunnel and DRB is maintained*/
/* as part of DAM.                                                        */
EXTERN S16 wrIfmDamWrTnlCreatReq(U32 transId, WrDamTnlInfo *tnlInfo);
EXTERN S16 wrIfmDamTnlCreatReq(U32 transId, WrDamTnlInfo *tnlInfo);
EXTERN Void  wrDamTnlCreatReq(U32 transId, WrDamTnlInfo *tnlInfo);
EXTERN S16 wrIfmDamTnlCreatCfm(U32 transId, U8 status, U32 lclTeid);
EXTERN S16 wrUmmTnlCreatCfm(U32 transId, U8 status, U32 lclTeid);
EXTERN Void  wrIfmDamWrCntrlReq(LwrMngmt    *cfg);
EXTERN Void wrIfmDamWrCfgReq(LwrMngmt *cfg);

EXTERN Void  wrIfmDamSendAlarmInd(U16     category,U16     event,U16     cause);
EXTERN S16 wrIfmDamCfgReq(LwrMngmt *cfg);
EXTERN S16 wrIfmDamCfgCfm(LwrMngmt  *cfg,CmStatus *cfmStatus);
EXTERN S16 wrIfmDamCntrlReq(LwrMngmt    *cfg);
EXTERN S16 wrIfmDamCntrlCfm(LwrMngmt    *cntrl,CmStatus   *cfmStatus);
EXTERN S16 wrIfmDamTnlModCfm(U32 transId,U8  status,U32  lclTeId);
EXTERN S16 wrIfmDamReestabCfm(U32  transId,U8  status);
EXTERN S16  wrIfmDamPdcpDatCfm(CmLtePdcpId pdcpId);

EXTERN Void wrDamTnlDelReq(U32  transId, WrDamTnlId  *tnlId);
EXTERN S16 wrDamStartUeTmr(U16 cellId,U16 crnti); 

/* ccpu00126336 */
/* Tunnel modification primitive to modify the tunnels                    */
EXTERN Void wrIfmDamWrTnlModReq(U32 transId, WrDamTnlModInfo *tnlModInfo);
EXTERN S16 wrIfmDamTnlModReq(U32 transId, WrDamTnlModInfo *tnlModInfo);
EXTERN S16 wrDamTnlModReq(U32 transId, WrDamTnlModInfo *tnlModInfo);
EXTERN S16 wrUmmTnlModCfm(U32 transId, U8 status, U32 lclTeId);

/* HO_REEST */
EXTERN S16 wrIfmDamWrHdlHoFailure(U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamHdlHoFailure(U16 cellId, U16 crnti);
EXTERN S16 wrDamHdlHoFailure(U16 cellId, U16 crnti);

/* Tunnel deletion primitive to delete the tunnels upon bearer release    */
/* No confirmation is provided for deletion request                      */
EXTERN Void wrIfmDamWrTnlDelReq(U32 transId, WrDamTnlId *tnlId);
EXTERN S16 wrIfmDamTnlDelReq(U32 transId, WrDamTnlId *tnlId);

/* Tunnel state change primitive                                          */
EXTERN Void wrIfmDamWrChngTnlState(WrDamTnlStInfo *tnlStInfo);
EXTERN S16 wrIfmDamChngTnlState(WrDamTnlStInfo *tnlStInfo, U16 cellId);
EXTERN S16 wrDamTnlStChngReq(WrDamTnlStInfo *tnlStInfo);

/* Primitive to start end marker timer                                    */
EXTERN S16 wrDamStartEndMrkrTmr(U16 cellId, U16 ueId);

EXTERN S16 wrUmmPrcEgtpErrInd(U32 lclTeid, U32 numDrbs, U16 crnti);

/* Cell addition request primitive for system bring up*/
EXTERN Void wrIfmDamWrCellAddReq(WrDamCellInfo *cellInfo);
EXTERN S16 wrIfmDamCellAddReq(WrDamCellInfo *cellInfo);
EXTERN S16 wrDamCellAddReq(WrDamCellInfo *cellInfo);

/* UE deletion request primitive when a call tear down is performed       */
EXTERN Void wrIfmDamWrUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN Void  wrDamUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamUeDelCfm(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrUmmPrcDamUeDelCfm(U32 transId, U16 cellId, U16 crnti);

/* UE ID change primitives to be used during reestablishment              */
EXTERN S16 wrIfmDamWrUeIdChgReq(U32 transId, U16 cellId, U16 oCrnti, U16 nCrnti);
EXTERN S16 wrDamUeIdChgReq(U32 transId, U16 cellId, U16 oCrnti, U16 nCrnti);
EXTERN S16 wrIfmDamWrUeIdChgCfm(U32 transId, U8 status);
EXTERN S16 wrUmmPrcDamUeIdChgCfm(U32 transId, U8 status);

EXTERN Void wrIfmDamWrReestabReq(U32 transId, U16 cellId, U16 ocrnti, U16 ncrnti);
EXTERN S16 wrIfmDamReestabReq(U32 transId, U16 cellId, U16 ocrnti, U16 ncrnti);
/* RLC_DL_MAX_RETX fix */
EXTERN S16 wrIfmDamWrReCfgReq(U32 transId,U16 cellId,U16 crnti);
EXTERN S16 wrIfmDamReCfgReq(U32 transId,U16 cellId,U16 crnti);
EXTERN S16 wrIfmDamStopUeTmr(U16 cellId,U16 ueId);
EXTERN S16 wrDamStopUeTmr (U16 cellId,U16 ueId);
EXTERN S16 wrIfmDamStartInactivityTimer(U16 cellId,U16 crnti);
EXTERN S16 wrIfmDamSetDataRcvdFlag(U16 cellId, U16 ueId);/*ccpu00138576*/
EXTERN S16 WrIfmDamBndReq(Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmDamBndCfm (Pst *pst, SuId suId, U8 status);
EXTERN S16 EuLiDamBndCfm (Pst *pst, SuId suId, U8 status);
EXTERN S16 EuLiDamTnlCreatCfm(Pst* pst,U32 transId,U8 status,U32 lclTeid);
EXTERN S16 EuLiDamUeDelCfm(Pst* pst,U32 transId, U16  cellId, U16 crnti);
EXTERN S16 EuLiDamReestabCfm(Pst* pst,U32 transId, U8 status);
EXTERN S16 EuLiDamCfgCfm(Pst* pst,LwrMngmt *cfg, CmStatus *cfmStatus);
EXTERN S16 EuLiDamCntrlCfm(Pst* pst,LwrMngmt *cntrl, CmStatus *cfmStatus);
EXTERN S16 EuLiDamStaInd(Pst* pst,U16 category, U16 event, U16 cause);
EXTERN S16 EuLiDamTnlModCfm(Pst* pst,U32 transId, U8 status, U32 lclTeId);
EXTERN S16 EuLiDamPdcpDatCfm(Pst* pst, CmLtePdcpId pdcpId);
EXTERN S16 EuLiDamSendCtxtRel(Pst* pst,U16 crnti, U16 cellId, U8 event);
EXTERN S16 EuLiDamEgtpErrInd(Pst* pst,U32 lclTeid, U32 numDrbs, U16 crnti);


EXTERN S16 EuUiDamBndReq (Pst *pst, SuId suId, SpId spId);
EXTERN S16 EuUiDamTnlCreatReq(Pst *pst,U32 transId, WrDamTnlInfo *tnlInfo);
EXTERN S16 EuUiDamTnlDelReq(Pst *pst,U32 transId, WrDamTnlId *tnlId);
EXTERN S16 EuUiDamUeDelReq(Pst *pst,U32 transId, U16 cellId, U16 crnti);
EXTERN S16 EuUiDamCellAddReq(Pst *pst,WrDamCellInfo *cellInfo);
EXTERN S16 EuUiDamReCfgReq(Pst *pst,U32 transId, U16 cellId, U16 crnti);
EXTERN S16 EuUiDamReestabReq(Pst *pst,U32 transId, U16 cellId, U16 oldcrnti, U16 newcrnti);
EXTERN S16 EuUiDamTnlStChngReq(Pst *pst,WrDamTnlStInfo *tnlStInfo);
EXTERN S16 EuUiDamStartInactivityTmr(Pst *pst,U16 cellId, U16 crnti);
EXTERN S16 EuUiDamStopUeTmr(Pst *pst,U16 cellId, U16 ueId);
EXTERN S16 EuUiDamCfgReq(Pst *pst,LwrMngmt *cfg);
EXTERN S16 EuUiDamCntrlReq(Pst *pst,LwrMngmt *cntrl);
EXTERN S16 EuUiDamTnlModReq(Pst *pst,U32 transId, WrDamTnlModInfo *tnlModInfo);
EXTERN S16 EuUiDamHdlHoFailure(Pst *pst,U16 cellId, U16 crnti);
EXTERN S16 EuUiDamSetDataRcvdFlag(Pst *pst,U16 cellId, U16 ueId);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_IFM_DAM_H__ */

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

