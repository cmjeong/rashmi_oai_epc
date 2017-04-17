
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm.h

     Sid:      wr_umm_mobparms.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:33 2014

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_MOB_PARAMS_H__
#define __WR_UMM_MOB_PARAMS_H__

#include "wr.h"
#include "wr_cmn.h"
#ifdef __cplusplus
extern "C" {
#endif


#define DATA_TYPE_BOOL  0
#define DATA_TYPE_U8    1
#define DATA_TYPE_U16   2
#define DATA_TYPE_U32   3

   EXTERN S16 wrUmmFillMobParamsIntoCellCb(WrUmmCellCb *cellCb,
         WrMobParams  *cellMobParams, LwrCdma2k1xMobParams *mobParams);

#endif /* __WR_UMM_MOB_PARAMS_H__ */ 
/********************************************************************30**

           End of file:     wr_umm_mobparms.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:33 2014

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

