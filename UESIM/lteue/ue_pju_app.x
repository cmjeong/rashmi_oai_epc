

/**********************************************************************
 
    Name:   UE Application interface with PJU[PDCP]
 
    Type:   C include file
 
    Desc:   Defines required by UE Application interface with PDCP
 
    File:   ue_pju_app.x 
 
    Sid:      ue_pju_app.x@@/main/1 - Sun Mar 28 22:59:26 2010
 
    Prg:    vp 
 
**********************************************************************/
 

 
#ifndef __UE_PJU_APPX__
#define __UE_PJU_APPX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*ue002.101: Multi ue support changes */
/* Dummy PDCP's upper interface with UE Application */
   /* ue008.101: Added new parameter in lcId UeUiPjuDatReq() */
EXTERN S16 UeUiPjuDatReq ARGS((Pst    *pst,
                               SpId    spId,
                               Buffer *mBuf,
                               U16     cellId,
                               U16     ueId,
                               U8      lcId));

EXTERN S16 UeAppLiPjuDatInd ARGS((Pst    *pst,
                                  SuId    suId,
                                  Buffer *mBuf,
                                  U16     cellId,
                                  U16     ueIdx));

#ifndef SS_CAVIUM
EXTERN S16 ueAppFrwdIpPkt ARGS ((U8* flatBuf, U32 len,U16 cellIdx,U16 ueIdx));
#else
EXTERN S16 ueAppFrwdIpPkt ARGS ((Buffer *,U16 cellIdx,U16 ueIdx));
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __UE_PJU_APPX__*/



/**********************************************************************
         End of file:     ue_pju_app.x@@/main/1 - Sun Mar 28 22:59:26 2010
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     vp            1. Initial Release.
/main/1+  ue002.101  sv           1. Multi ue support changes.
/main/1+  ue008.101 ragrawal      1.  Added new parameter in lcId UeUiPjuDatReq().
*********************************************************************91*/



