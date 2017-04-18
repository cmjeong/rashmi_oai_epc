
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_dlcdma.h

     Sid:      wr_umm_dlcdma.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:00 2016

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_DLCDMA_H__
#define __WR_UMM_DLCDMA_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */


/* The following macros are used for the state field in the transaction  */

#define WR_UMM_DL_CDMA_INITED        0
#define WR_UMM_DL_CDMA_ERROR         1


typedef struct wrUmmDlCdmaTransCb
{
   U8                       transId;
   U8                        state;
   WrUmmIncMsg               *msg;
   TknStrOSXL                *cdmaPdu;
   U32                       ratTyp;
   U32                       numOfDlTxCnt;
   U8                        datCfmState;
} WrUmmDlCdmaTransCb;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* Enf of __WR_UMM_DLCDMA_H__ */

/********************************************************************30**

           End of file:     wr_umm_dlcdma.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:00 2016

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
/main/1        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/

