
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_schd.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


#ifndef __WR_IFM_SCHD_H__
#define __WR_IFM_SCHD_H__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 WrIfmSchdUbndReq (Pst* pst, SpId spId, Reason reason);
EXTERN S16 WrIfmSchdBndReq (Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmSchdTtiInd (Pst *pst, SuId suId, RgrTtiIndInfo *ttiInd);
EXTERN S16 WrIfmSchdSiCfgReq (U32         transId,
                              RgrSiCfgReqInfo * cfgReqInfo);
EXTERN S16 WrIfmSchdBndCfm (Pst *pst, SuId suId, U8 status);
EXTERN S16 WrIfmSchdCfgCell (RgrCfgReqInfo *cfgReq, U32 transId);
EXTERN S16 WrIfmSchdCfgUe (RgrCfgReqInfo *uecfg, U32 transId, WrCellId cellId);
#ifdef RGR_CQI_REPT
EXTERN S16 NxLiRgrStaInd (Pst *pst, SuId   suId, RgrStaIndInfo   *staInd);
#endif
/* LTE_ADV_DSFR starts */
EXTERN S16 WrIfmSchdLoadInfReq (U32    transId, RgrLoadInfReqInfo *loadInfReq);

EXTERN S16 NxLiRgrLoadInfInd (Pst *pst, SuId  suId, RgrLoadInfIndInfo  *loadInfInd);
/* LTE_ADV_DSFR ends */

EXTERN S16 NxLiRgrUeStaInd (Pst *pst, SuId  suId, RgrUeStaIndInfo  *ueStaInd);

/* PH04_CMAS */

EXTERN S16 WrIfmSchdWrngSiCfgReq
(
U32                          transId,
RgrWarningSiCfgReqInfo       *cfgReqInfo
);


EXTERN S16 WrIfmSchdWrngSiStopReq
(
    U32            transId,
    U8             siIndex
);


EXTERN S16 wrUmmSchdUeStaInd(RgrUeStaIndInfo   *ueStaInd);
EXTERN S16 NxLiRgrTtiInd(Pst   *pst,SuId  suId,RgrTtiIndInfo    *ttiInd);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_IFM_SCHD_H__ */



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
