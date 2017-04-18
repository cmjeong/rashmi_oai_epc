
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_meas_fun.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_MEAS_FUN_H__
#define __WR_UMM_MEAS_FUN_H__

#include "wr_umm_trans.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */
typedef enum wrMeasInitCause
{
   WR_MEAS_CONFIG_EVT_ANR = 1,
   WR_MEAS_CONFIG_NO_EVT_ANR,
}MeasInitCause;

/* Function  Declaration */
 EXTERN   S16 wrUmmMeasProcNrUpdt
   (
    U16                      cellId,
    Bool                     isNewFreq,
    WrNrUpdtInfo             *nrUpdtInfo
   );

 EXTERN   S16 wrUmmMeasUeCbInit
   (
    WrUeCb                       *ueCb
   );
 EXTERN  S16 wrUmmMeasUeCbDeInit
   (
    WrUeCb                    *ueCb
   );
EXTERN S16 wrUmmMeasAllocNrGeranObj
(
 WrUmmCellCb                 *cellCb,
 U8                          numFreq,
 WrUmmMeasGeranMeasInfo      *cellFreqCfg
);
 EXTERN   S16 wrUmmMeasAllocNrFreqCfg
   (
    WrUmmCellCb                 *cellCb,
    U8                          numFreq,
    LwrNeighFreqAddModCfg       *cellFreqCfg
   );
EXTERN S16 wrUmmMeasAllocRecfgMsg
(
 NhuDatReqSdus             **rrcReCfgMsg,
 WrUmmMeasTransInfo        *measTransCb,
 WrUeCb                    *ueCb,
 U32                        transId
);
 EXTERN S16 wrUmmHoHdlMeasRprt
   (
    WrUeCb                       *ueCb,
    WrMeasRptCfgType             event,
    NhuMeasResults               *measRprt,
    U32                          earfcn
   );
 EXTERN S16 wrUmmMeasAllocCellCfg
   (
    WrUmmCellCb                 *cellCb,
    LwrCellMeasCfgGrp           *measCfgParams
   );
 EXTERN   S16 wrUmmMeasCellReCfg
   (
    U16                         cellId,
    LwrNeighFreqCfg             *cellFreqCfg
   );
 EXTERN   S16 wrUmmMeasIntraCellReCfg
   (
    U16                         cellId
   );
 EXTERN  S16 wrUmmMeasDeAllocCellCfgReq
   (
    U16                      cellId
   );
 EXTERN   S16 wrUmmMeasInitialUeCfg 
   (
    CmMemListCp              *memCp,
    WrUeCb                   *ueCb,
    WrUmmMeasTransInfo       *measTransCb,
    NhuMeasConfig            *nhuMeasCfg,
    WrUmmTransCb             *transCb,
    MeasInitCause            cause
   );
 EXTERN   S16 wrUmmMeasCellReCfgParams
   (
    LwrCellMeasCfgGrp            *cellCfgParams, 
    LwrCellMeasCfgGrp            *measReCfg
   );
 EXTERN   S16 wrUmmMeasNrFreqReCfgMod
   (
    WrUmmCellCb                 *cellCb,
    U8                          numFreq,
    LwrNeighFreqAddModCfg       *modMeasCfg
   );
 EXTERN   S16 wrUmmMeasNrFreqReCfgDel
   (
    WrUmmCellCb                 *cellCb,
    U8                          numFreq,
    LwrNeighFreqDelCfg          *delMeasCfg
   );
 EXTERN   S16 wrUmmMeasCsfbUtraFddCfg
   (
    WrUeCb                      *ueCb,
    WrUmmTransCb                *transCb
   );
  EXTERN   S16 wrUmmMeasCsfbUtraTddCfg
   (
    WrUeCb                      *ueCb,
    WrUmmTransCb                *transCb
   );
 EXTERN   S16 wrUmmMeasCsfbCdmaCfg
   (
    WrUeCb                      *ueCb,
    WrUmmTransCb                *transCb
   );
 EXTERN   S16 wrUmmMeasGetArfcnAndRptType
  (
    U16                     ueIdx,
    WrCellId                cellId,
    NhuMeasResults          *measRpt,
    WrUmmMeasRptInfo        *measRptInfo
  );

EXTERN  Void  wrUmmMeasGetNhuMeasCfgFrmReCfg
(
  NhuDatReqSdus                *rrcReCfgMsg,
  NhuMeasConfig                **nhuMeasCfg
);

EXTERN  Void wrUmmMeasGetNhuMeasCfgFrmReCfg
(
  NhuDatReqSdus                *rrcReCfgMsg,
  NhuMeasConfig                **nhuMeasCfg
);
EXTERN S16 wrUmmMeasFillMeasIdObj
(
 U8                           measID,
 NhuMeasIdToAddMod            *measIdAddMod,
 CmLListCp                    *measIdLst
);
EXTERN S16 wrUmmMeasFindMeasObjAndTyp
(
 WrUmmMeasObjInfo             *measObjInfo,
 U8                           measObjId,
 WrMeasUeCb                   *measUeCb
);
EXTERN S16 wrUmmMeasFindRptCfgTyp
(
 U8                           rptCfgId,
 WrMeasRptCfgType             *rptCfgTyp,
 CmLListCp                    *rptCfgLst
);
EXTERN PUBLIC S16 wrUmmMeasCfgDelNewPciObj
(
 WrUmmMeasObjInfo           *measObjInfo,
 WrMeasUeCb                 *measUeCb
);
EXTERN S16 wrUmmMeasCfgReCfgReqCompHand
(
 WrUmmMeasTyp                 measTyp,
 WrUmmTransCb                 *transCb
);
EXTERN S16 wrUmmMeasSetFreeMeasIds 
(
 WrUmmMeasTyp                 measTyp,
 WrUmmTransCb                 *transCb
);
EXTERN S16 wrUmmMeasFindRptCfgID
(
 U8                           *rptCfgId,
 WrUmmMeasRptCfgInfo          *rptCfgInfo,
 CmLListCp                    *rptCfgLst
);
EXTERN U8 wrUmmMeasCreatRptCfgObjInUeCb
(
 WrUmmMeasRptCfgInfo       *rptCfgInfo,
 WrUeCb                    *ueCb,
 LwrCellMeasCfgGrp         *measCellCfg
);
EXTERN U8 wrUmmMeasCreatMeasIdNode
(
 WrUmmMeasTyp                measIdTyp,
 U8                          measObjId,
 U8                          rptCfgId,
 WrMeasUeCb                  *measUeCb
);
EXTERN S16 wrUmmMeasGetFreeMeasObjId
(
 WrMeasUeCb           *measUeCb,
 U8                   *measObjId
);
EXTERN S16 wrUmmMeasSetFreeRptCfgId
(
 WrMeasUeCb                   *measUeCb,
 U8                           rptCfgId
);
EXTERN S16 wrUmmMeasCreateRptCfg
(
 U8                           rptCfgId,
 WrUmmMeasRptCfgInfo          *intRptCfg,
 WrMeasRptCfgNode             *rptCfg,
 LwrCellMeasCfgGrp            *measCellCfg,
 WrUeCb                       *ueCb
);
EXTERN S16 wrUmmMeasUpdtEutraMeasObjAndIdFromArfcn
(
 U32                          arfcn,
 WrMeasUeCb                   *measUeCb,
 U8                           *measObjId,
 WrUmmMeasEutraMeasObjNode    **cellCbMeasObj
);

EXTERN U8 wrUmmMeasAddInterMeasObjToUeCb
(
 WrMeasUeCb                  *measUeCb,
 WrUmmMeasEutraMeasObjNode   *cellCbMeasObj,
 U16                         newPci
 );
EXTERN S16 wrMeasFillNhuMsg
(
 CmMemListCp                  *memCp,
 NhuMeasConfig                *nhuMeasCfg,
 WrUeCb                       *ueCb,
 WrUmmMeasTransInfo           *measTransCb,
 LwrCellMeasCfgGrp            *measCellCfg,
 U32                          transId
);
EXTERN S16 wrUmmMeasGetFreeRptCfgId
(
 WrMeasUeCb                   *measUeCb,
 U8                           *rptCfgId
);
EXTERN S16 wrUmmMeasUpdtCellEutraMeasObjFrmArfcn
(
 U32                         arfcn,
 CmLListCp                   *interMeasObjLst,
 WrUmmMeasEutraMeasObjNode   **enbMeasObj
);

EXTERN S16 wrUmmMeasFillNhuRmvIdLst
(
CmMemListCp                  *memCp,
NhuMeasConfig                *nhuMeasCfg,
WrUmmMeasRmvInfo             *measTransCb
);
EXTERN S16 wrUmmMeasFillNhuAddIdLst
(
CmMemListCp                  *memCp,
NhuMeasConfig                *nhuMeasCfg,
WrUeCb                       *ueCb,
WrUmmMeasAddInfo             *measTransCb
);
EXTERN S16 wrUmmMeasFillRptCfgObj
(
U8                                  rptCfgId,
NhuReportConfigToAddModreportConfig *nhuRptCfgObj,
CmLListCp                           *rptCfgLst
);
EXTERN S16 wrUmmMeasFillMeasGapCfg
(
WrUmmMeasGapStatus           measGapStatus,
WrMeasUeCb                   *measUeCb,
NhuMeasGapConfig             *nhuMeasGap
);
EXTERN Void wrUmmMeasAddMeasGap
(
U32                          reqModule,
WrUmmCellCb                  *cellCb,
WrUeCb                       *ueCb,
WrUmmMeasGapStatus           *measGapStatus,
U32                          reqModuleTransId
);

EXTERN Void wrUmmMeasRelMeasGap 
(
U32                          reqModule,
WrUmmCellCb                  *cellCb,
WrUeCb                       *ueCb,
WrUmmMeasGapStatus           *measGapStatus,
U32                          reqModuleTransId
);

EXTERN S16 wrUmmMeasUpdtCellUtraMeasObjFrmArfcn
(
U32                          arfcn, 
CmLListCp                    *utraMeasObjLst,
WrUmmMeasUtraMeasObjNode     **utraMeasObj
);
EXTERN U8 wrUmmMeasAddUtraMeasObjToUeCb
   (
    WrMeasUeCb                  *measUeCb,
    WrUmmMeasUtraMeasObjNode    *cellCbMeasObj,
    U16                         newPsc
   );
EXTERN PUBLIC S16  wrUmmMeasGetMeasIdObj
    (
     U32                           measID,
     WrMeasIdNode                 **measIdObj,
     CmLListCp                    *measIdLst
    ); /* KW fix for LTE_ADV */
EXTERN PUBLIC S16 wrUmmFindNewPciFrmAnrMeasRpt
   (
    WrUmmMeasObjInfo             *measObjInfo,
    NhuMeasResults               *measRprt,
    WrUmmTransCb                 *transCb,
    U8                           isEvntAnr
   );

EXTERN PUBLIC U8 wrUmmMeasRptAndMeasIdCfg
   (
    WrUmmMeasTyp                measIdTyp,
    U8                          measObjId,
    WrUmmMeasRptCfgInfo        *rptCfgInfo,
    WrUeCb                       *ueCb,
    LwrCellMeasCfgGrp          *measCellCfg,
    WrUmmMeasAddInfo            *measTransCb
   );
EXTERN PUBLIC WrUmmIntAnrMeasMsg* wrUmmAnrMeasIntraNewPciCfg
   (
    WrUeCb                       *ueCb
   );
EXTERN PUBLIC WrUmmIntAnrMeasMsg* wrUmmAnrMeasInterNewPciCfg
(
 CmLListCp                     *interNewPciLst
);

EXTERN  PUBLIC U16 wrUmmMeasGetRptAmtFrmEnum
   (
    U8                        rptAmt
   ); 
EXTERN  PUBLIC S16 wrUmmAnrPrcRrcTmrExpiry
(
  WrUmmTransCb            *transCb
);
EXTERN  S16 wrUmmStartPeriodicAnrTrans
(
   WrUeCb                      *ueCb
);
EXTERN S16 wrUmmStopPeriodicAnr
(
   WrUeCb  *ueCb
);
EXTERN S16 wrUmmStartEventAnrTrans
(
   Bool reCfgReq, 
   WrUeCb   *ueCb
);
EXTERN S16 wrUmmStopEventAnrTrans
(
   WrUeCb   *ueCb
);
EXTERN  PUBLIC Void  wrUmmMeasGetNhuMacMainCfgFrmReCfg
   (
    NhuDatReqSdus           *rrcReCfgMsg,
    NhuMAC_MainConfig       **macCfg
   );
EXTERN Void wrUmmMeasResetTransCb
   (
    WrUmmMeasTransInfo *measTransCfg
   );

EXTERN PUBLIC S16 wrUmmMeasDelPerdCfgInUeCb
   (
    WrMeasUeCb                  *measUeCb
   );
EXTERN PUBLIC Void wrUmmMeasDeAllocMemForNewPciObj
   (
    CmLListCp                   *newPciLst
   );

/* ccpu00132002 Added function prototype */
 EXTERN S16 wrUmmMeasRmvMeaIdInUeCb
      (
       U8                           measId,
       CmLListCp                    *measIdLst
      );

 EXTERN S16 wrUmmMeasSetFreeMeasId
      (
       WrMeasUeCb                   *measUeCb,
       U8                           measId
      );

EXTERN S16 wrUmmConfigurePeriodicANR(WrUeCb *ueCb);

EXTERN S16 wrUmmMeasPrepareSendRrcRecfg
(
   U16                        cellId, 
   WrUeCb                    *ueCb,
   WrUmmMeasTransInfo        *measTransCb,
   U32                        transId
);

EXTERN Void wrUmmDelIntraFreqNonCfgNewPciObj
(
  CmLListCp                  *newPciLLst
);

EXTERN Void wrUmmDelInterFreqNonCfgNewPciObj
(
 CmLListCp                    *newPciFreqNode
);
EXTERN S16 wrUmmCsfbGeranHdlMeasRpt
(  
 WrUmmTransCb                *transCb,
 NhuMeasResults              *measRpt
); 
/*rel10*/
EXTERN S16 wrUmmGetUtraRscp
(
  NhuMeasResultUTRAmeasResult *utraMeasResult
);
EXTERN U8 wrUmmGetUtraEcno
(
  NhuMeasResultUTRAmeasResult *utraMeasResult
);
EXTERN U32 wrUmmGetUtraPscId
(
  NhuMeasResultUTRAphysCellId *phyCell
);
EXTERN U8 wrUmmMeasAddGeranMeasObjToUeCb
(
 WrUmmMeasAddInfo            *measTransInfo,
 WrUeCb                      *ueCb,
 WrUmmMeasGeranMeasObjNode    *cellCbMeasObj,
 U16                         newPsc
);
EXTERN S16 wrUmmMeasUpdtGeranMeasObjAndIdFromArfcn
(
WrMeasUeCb                   *measUeCb,
U8                           *measObjId,
WrMeasUeCbGeranMeasObjNode    **cellCbMeasObj
);

EXTERN Bool wrUmmChkIRATBndLstNeedFrGaps
(
 WrUeCb   *ueCb,
 U8       *tgtBnd,
 U8       nghCnt
);

EXTERN S16 wrUmmIRatGeranRedirHdlMeasRpt
(
 WrUeCb                       *ueCb,
 U8                           event,
 NhuMeasResults               *measRprt
);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_MEAS_FUN_H__ */

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
