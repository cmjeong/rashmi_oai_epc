/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_son.h

     Sid:      wr_ifm_son.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 16:06:19 2014

     Prg:      subhamay 

*********************************************************************21*/


#ifndef __WR_IFM_SON_H__
#define __WR_IFM_SON_H__

#include "wr_umm.h"
#include "wr_emm.h"

EXTERN S16 wrIfmSonAddAnrNeighborReq(U32   cellId, WrEutranNeighCellCb *neighborCellCb);   
EXTERN S16 wrIfmSonSendNeighborReq( NluNeighborReport   *nghRpt);
EXTERN S16 wrIfmSonPciModIndCfm(WrCellCb *cellCb);
EXTERN S16 WrIfmSonPerCellSrchRsp (CtfPeriodicRemCellSearchRsp *cellSrchInfo);
#ifdef RGR_CQI_REPT
EXTERN S16 wrIfmSonUeCqiReportInd(RgrStaIndInfo   *statInd, WrUeCb  *ueCb);
#endif
EXTERN S16 wrIfmSonUeMeasReportInd(WrUeCb  *ueCb, NhuMeasResults   *measRpt);
EXTERN S16 wrIfmSonDelUeInd(U16 crnti, U16  cellId, WrPlmnId *plmnId);
EXTERN S16 wrIfmSonAddUeInd(WrUeCb *ueCb);
EXTERN S16 wrIfmSonModUeInd(WrUeCb *ueCb);
EXTERN S16 wrIfmSonDelAnrNeighborReq(U32   cellId, WrEutranNeighCellCb *neighborCellCb);

#endif /* __WR_IFM_SON_H__ */


/********************************************************************30**

           End of file:     wr_ifm_son.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 16:06:19 2014

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
        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
