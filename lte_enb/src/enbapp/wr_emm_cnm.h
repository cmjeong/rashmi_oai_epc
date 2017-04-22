
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_emm.h

     Sid:      wr_emm_cnm.h@@/main/Br_Tenb_Brdcm_Bcm61750_Intg_GA2_0_TDD_GAFDD_final/1 - Thu Jun 26 19:23:41 2014

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_EMM_CNM_H__
#define __WR_EMM_CNM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define WR_CNM_MAX_VENDOR_LIST  6 /* same MAX_VENDOR_LIST listed in interface API header file */
#define WR_CNM_MAX_EARFCN_TABLE_SIZE 8 /* from freq band 33 to 40
                                        * For FDD, this needs to be modified
                                        * */
#define WR_CNM_RADIO_ELMNT_SIZE 20 /* From the CNM API doc */

/* Events for Initiating Cell Sync Request */
typedef enum _cnmStates
{
   WR_EMM_CNM_INIT_SYNC_IN_PROGRESS = 1,
   WR_EMM_CNM_SYNC_AFTER_SYNC_LOSS,
   WR_EMM_CNM_INIT_SYNC_AFTER_S1_UP,
   WR_EMM_CNM_IN_SYNC
} wrEmmCnmState;

typedef struct wrCnmEarfcnTable
{
  U16   fDlLow;
  U16   nOffsetDl;
  U16   earfcnStart;
  U16   earfcnEnd;
  U8    freqBand;
}WrCnmEarfcnTable;



EXTERN S16  wrEmmCnmStartInitalSync
(
Void
);

EXTERN S16  wrEmmCnmPrcS1LnkUp
(
Void
);

EXTERN void  wrEmmCnmPrntEutraNbrInfo
(
U16                          cellId
);

EXTERN S16  wrEmmCnmPrcInitSyncRsp
(
U16                          cellId,
CtfCnmInitSyncRsp            *cnmInitSyncRsp
);

EXTERN S16  wrEmmCnmPrcSyncInd
(
U16                          cellId,
CtfCnmCellSyncInd            *cnmSyncInd
);

EXTERN S16  wrEmmCnmPrcSyncRsp
(
U16                          cellId,
CtfCnmCellSyncRsp            *cnmSyncRsp
);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_EMM_CNM_H__ */

/********************************************************************30**

           End of file:     wr_emm_cnm.h@@/main/Br_Tenb_Brdcm_Bcm61750_Intg_GA2_0_TDD_GAFDD_final/1 - Thu Jun 26 19:23:41 2014

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

*********************************************************************91*/

