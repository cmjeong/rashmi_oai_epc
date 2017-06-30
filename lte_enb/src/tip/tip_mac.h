
/**********************************************************************
     Name:     LTE-MAC layer 
  
     Type:     C include file 
  
     Desc:     Defines required by the LTE MAC-RRM control (RGR) interface.

     File:     tip_mac.h 

     Sid:      rgr.h@@/main/9 - Wed Jul 27 13:44:32 2011

     Prg:      Radisys

**********************************************************************/

#ifndef __TIP_MAC_H__
#define __TIP_MAC_H__
#include "L3_L2L.h"


EXTERN S16 tipSendMacCfgReq(Pst* pst,SpId spId,RgrCfgTransId transId,RgrCfgReqInfo * cfgReqInfo);
EXTERN S16 tipUnpkRgrCfgReq(RgrCfgReq func,Pst *pst,Buffer *mBuf);
EXTERN S16 tipProcRgrCfgCfm(RgrCfgCfm func,Pst *pst,Buffer *mBuf);
EXTERN S16 tipSendMacCfgRsp(Pst* pst,SuId suId,RgrCfgTransId transId,U8 status, U8 action, U8 cfgType);
EXTERN S16 tipSendMacCellStartReq(Pst* pst,U16  cellId);
EXTERN S16 tipStartCell(U16 cellId);
EXTERN S16 tipSendSiCfgReq (Pst* pst,SpId spId,RgrCfgTransId transId,
      RgrSiCfgReqInfo * cfgReqInfo);

EXTERN S16 tipProcSiCfgReq(RgrSiCfgReq func,Pst *pst,Buffer *mBuf);
EXTERN S16 tipSendMacSiCfgRsp(Pst* pst,SuId suId, RgrCfgTransId transId,U8 status);
EXTERN S16 tipSendMacAppTtiInd(Pst* pst, SuId suId, RgrTtiIndInfo *ttiInd);
EXTERN S16 tipSendCrgCfgCfm(CrgCfgTransId transId, U8 status);

#endif /*end of __TIP_MAC_H__ */
