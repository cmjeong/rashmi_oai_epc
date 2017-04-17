
/********************************************************************20**
 
     Name:     Trillium LTE CNE - PDN-GW 
  
     Type:     C include file
  
     Desc:     PGW EGT Utility functions
  
     File:     av_egt_utl.x 
  
*********************************************************************21*/
#ifndef __AV_EGT_UTL_X__
#define __AV_EGT_UTL_X__

PUBLIC S16 avPgwValMBReq ARGS((
AvPgwPdnCb        *pdnCb,
EgMsg             *egMsg,
U32               *cause
));

PUBLIC S16 avPgwEguTunnelModReq ARGS((
AvPgwUeTunnelCb         *pUTun,
EgMsg                   *pEgMsg
));

PUBLIC S16 avPgwBldMBRsp ARGS((
AvPgwPdnCb        *pdnCb, 
EgMsg             **egMsg
));

#endif /* __AV_EGT_UTL_X__ */
