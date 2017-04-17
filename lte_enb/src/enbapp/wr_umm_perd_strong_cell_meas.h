
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_perd_strong_cell_meas.h

     Prg:      Vmahanka 

*********************************************************************21*/

#ifndef __WR_UMM_PERD_STRONG_CELL_MEAS_H__
#define __WR_UMM_PERD_STRONG_CELL_MEAS_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

typedef struct wrUmmPerdStrongCellMeasTranInfo
{
    WrUmmMeasTransInfo       measTransCfg;
    Bool                     isReCfgSent;
    Bool                     closeTrns;
} WrUmmPerdStrongCellMeasTransInfo;


typedef struct wrUmmStrongCell
{
    U32 pci;
    U32 rsrp;
    U32 rsrq;
} WrUmmStrongCell;
 
typedef struct wrUmmPerdStrongCellLst
{
    U8		numComp;
    WrUmmStrongCell strongCell[WR_EMM_MAX_PCI_PER_REPORT];
} WrUmmPerdStrongCellLst;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_ANRMEAS_H__ */

/********************************************************************30**

           End of file:     wr_umm_perd_strong_cell_meas.h@@/main/tenb_main_ccb/1 - Thu Jan 21 17:51:26 2016

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
       ---      Vmahanka         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
