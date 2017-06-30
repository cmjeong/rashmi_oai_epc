
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_emm_cfg.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_EMM_CFG_H__
#define __WR_EMM_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

typedef struct wrEmmEnodCfgParama
{
   U8                        numEnb;
   WrNeighEnbCb              *neighEnbCb[MAX_NUM_NEIGH_CELLS];
} WrEmmEnodCfgParama;

EXTERN S16 WrEmmCfgReq (LwrMngmt *cfg,CmStatus *status);
EXTERN S16 WrEmmDynCfgReq(Void *cfg, CmStatus *cfmSts, U32 cfgType, Bool cfgPriority);
#if 0
 PUBLIC WrCdma2kNeighCellCb * wrEmmFindCdma1xRTTNeighCell
 (
 U8                          cellIndex,
 U16                         pnOffset
 );
 PUBLIC WrCdma2kNeighCellCb * wrEmmFindCdmaHRPDNeighCell
 (
 U8                          cellIndex,
 U16                         pnOffset
 );
#endif
PUBLIC WrUtraNeighCellCb  * wrEmmFindUtranNeighCell
(
U8              cellIndex,
U16               psc
);
PUBLIC S16 wrEmmBldEnbCfgTranFrmEnbId
(
WrEmmEnodCfgParama     *enbCfgparama,
U16                     cellId
);

PUBLIC S16 wrEmmProcRmCellRecfgInd
(
RmuCellRecfgInd         *rrmWrCellRecfgInd
);

PUBLIC  S16 wrEmmFindServedNeighCell
(
WrNeighEnbCb                *neignEnb,
U16                         pci,
U8                          cellId
);

PUBLIC S16 wrEmmSndLwrAddNeighCfm
(
  LwrMngmt                     *cfg
);

EXTERN Bool wrEmmPlmnPlmnsEqual
(
 WrPlmnId                   *plmnId1,
 WrPlmnId                   *plmnId2
);

PUBLIC WrNeighEnbCb* wrEmmAddNewNeighEnb
(
 WrEutranNeighCellCb           *neighCellCb,
 U16                          cellId
);

EXTERN Void wrEmmMmeBldEnbConfigTransfer(WrEmmEnodCfgParama *enbCfgparama,U16 cellId);

EXTERN S16 wrEmmCfgCellAddSib8
(
 WrCellCb                     *cellCb,
 LwrCellSib8CfgGrp            *sib8CfgGrp
);
EXTERN S16 wrEmmCfgCellAddCsfbCfg
(
 WrCellCb                 *cellCb,
 LwrCsfbCfgGrp            *csfbCfgGrp
);
EXTERN S16 wrEmmCfgValidateNeighFreqAddCdma1xRtt( WrCellCb *cellCb,
LwrNeighFreqAddModCfg *nbrFreqAdd);
EXTERN U16 wrEmmCfgNeighBandClassCfg(LwrNeighBandClass *neighBandClsCfg);

EXTERN S16 wrEmmCfgNeighFreqAddCdma1xFreq( WrCellCb *cellCb,
LwrNeighCdma1xFreq               *cdma1xFreq);

EXTERN S16 wrEmmCfgNeighCellAddCdma1xRtt
(
LwrNeighCellAddCfg           *neighCellAdd,
WrCellCb                     *cellCb
);

EXTERN S16 wrEmmPciModTmrExp
(
 PTR   cb
);


/* CSG_DEV start */
EXTERN S16 wrEmmCsgCopyCsgCfg (WrCellCb *cellCb, LwrAddCellCfg *cfgAdd);
EXTERN S16 wrEmmNbrCfgCopyCsgCfg (WrEutranNeighCellCb *eutNbrcellCb,
      LwrNeighCellAddCfg *nbrCellCfg);
/* CSG_DEV end */

EXTERN S16 wrEmmSendAddEutraNghInd(WrEutranNeighCellCb *eutraNgh,LwrActType actType,U8 cellId);
EXTERN S16 wrEmmSendUtraNghInd(WrUtraNeighCellCb *utraNgh,LwrActType actType, U8 cellId);
EXTERN S16 wrEmmSendAddGeranNghInd(WrGeranCellCb *eutraNgh,LwrActType actType,U8 cellId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_EMM_CFG_H__ */

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
