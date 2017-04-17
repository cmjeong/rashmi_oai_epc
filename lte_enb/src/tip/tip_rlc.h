
/**********************************************************************
     Name:     LTE-RLC layer 
  
     Type:     C include file 
  
     Desc:     Defines required by the LTE MAC-RRM control (RGR) interface.

     File:     tip_rlc.h 

     Sid:      rgr.h@@/main/9 - Wed Jul 27 13:44:32 2011

     Prg:      Radisys

**********************************************************************/

#ifndef __TIP_RLC_H__
#define __TIP_RLC_H__

#include "tip_cmn.h"
#include "kwu.h"
#include "kwu.x"

EXTERN  S16 tipSendRlcCfgReq(Pst *pst,SpId spId,CkwCfgInfo *cfg);
EXTERN  S16 TipUnpkRlcCfgReq(Pst *pst, U8 *recvBuf);
EXTERN  S16 tipSendRlcCfgRsp(Pst *pst, SuId suId, CkwCfgCfmInfo *cfmInfo);
EXTERN  S16 TipUnpkRlcCfgCfm(Pst *pst, U8 *recvBuf);
EXTERN  S16 TipUnpkCcchMsgReq(Pst *pst,U8 *recvBuf);
EXTERN  S16 tipSendCcchMsgReq(Pst *pst,SpId spId,KwuDatReqInfo *datInd,Buffer *mBuf);
EXTERN  S16 tipSendPcchMsgReq(Pst *pst,SpId spId,KwuDatReqInfo *datInd,Buffer *mBuf);
EXTERN  S16 TipUnpkRlcCcchMsgInd(Pst *pst,U8 *recvBuf);
EXTERN  S16 tipSendCcchMsgInd(Pst *pst,SuId suId,KwuDatIndInfo *datInd,Buffer *mBuf);
EXTERN  S16 tipSendRlcUeIdChgReq(Pst *pst, SpId spId, U32 transId, CkwUeInfo *oldUeInfo, CkwUeInfo *newUeInfo);
EXTERN  S16 TipUnPkRlcUeIdChgReq(Pst *pst, U8 *recvBuf);
EXTERN  S16 tipSendRrcUeIdChgCfm(Pst *pst, SuId suId, U32 transId, CkwUeInfo *ueInfo, CmStatus status);
EXTERN  S16 TipUnpkRrcUeIdChgCfm(Pst *pst, U8 *recvBuf);

EXTERN  S16 tipUnpkAppRlcMsg(Pst *pst, Buffer *mBuf);
EXTERN  S16 tipUnpkRlcPdcpMsg(Pst *pst, Buffer *mBuf);
EXTERN  S16 tipSendPdcpMsgInd(Pst *pst, SuId suId, KwuDatIndInfo *datInd, Buffer *mBuf);
EXTERN  S16 tipSendRlcDatCfm(Pst *pst, SuId  suId, KwuDatCfmInfo  *datCfm);
EXTERN  S16 tipSendRlcStaInd(Pst *pst, SuId suId, KwuStaIndInfo  *staInd);
EXTERN  S16 tipSendRlcCmnCfgRsp(Pst *pst, SuId  suId, CkwCfgCfmInfo  *cfmInfo);
EXTERN  S16 tipUnpkRlcAppMsg(Pst *pst, Buffer* mBuf);
#endif /*end of __TIP_RLC_H__ */

