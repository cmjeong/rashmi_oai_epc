
/********************************************************************20**

     Name:     EnodeB LTE-Advanced Application

     Type:     C include file

     Desc:     This file contains 
               
     File:     wr_umm_lteadv.h

     Sid:      wr_umm_lteadv.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:32 2014

     Prg:      skulal

*********************************************************************21*/

 
#ifndef __WR_UMM_LTE_ADV_H__
#define __WR_UMM_LTE_ADV_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

/* LTE_ADV starts */
#include "wr_emm.h"
#include "wr_cmn.h"
#include "wr_umm_msg.h"

typedef struct _wrLteAdvTransCb
{
   WrUmmLteAdvProc           procType;
   union
   {
      WrUmmMeasTransInfo     measInfo;
   } u;
} WrLteAdvTransCb;


EXTERN S16  wrUmmHdlLteAdvRecfg (U32 cellId, RgrFeature  feature,
                                      RgrFeatureStatus status);

EXTERN S16 wrUmmHdlLteAdvRecfgForUe (WrUmmCellCb *cellCb, WrUeCb *ueCb, RgrFeatureStatus status, 
                                 WrUmmLteAdvProc procType, WrUmmLteAdvPeerType peerType);


/* LTE_ADV_ABS starts */
EXTERN S16 wrUmmAbsPrcHdlMeasRpt (WrUeCb *ueCb, 
                                  NhuMeasResults *measRprt, U32 earfcn);
/* LTE_ADV_ABS ends */

EXTERN S16 wrUmmIntraMeasCfgForLteAdvAddEvntA3 (WrUeCb *ueCb,
                                        WrUmmMeasAddInfo  *addMeasInfo,
                                        WrUmmCellCb  *cellCb, WrMeasRptCfgType rptCfgTyp);

EXTERN S16 wrUmmIntraMeasCfgForLteAdvDelEvntA3 (WrMeasUeCb  *measUeCb,
                                        WrUmmMeasRmvInfo  *rmvMeasInfo,
                                        WrUmmCellCb *cellCb, WrMeasRptCfgType rptCfgTyp);
/* LTE_ADV ends */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_LTE_ADV_H__ */

