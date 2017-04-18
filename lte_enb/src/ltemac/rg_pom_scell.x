/*********************************************************************

  Name:     LTE-MAC layer 
  
  Type:     C Include File 
  
  Desc:     Structures, variables, and typedefs required by Secondary cell
            received through PRG interface.
            

  File:     rg_pom_scell.x 

  Sid:      rg_pom_scell.x

  Prg:      

**********************************************************************/
/** 
  @file rg_pom_scell.x 
  @brief Structure declarations and definitions for Secondary cell received from  (PRG) interface.
  */

#ifndef __RGPOMSCELL_X__ 
#define __RGPOMSCELL_X__

#ifdef __cplusplus
extern "C" {
#endif
#ifdef LTE_ADV
EXTERN S16 RgPrgPMacSMacUeSCellLchModReq ARGS
((
 Pst                      *pst,
 RgPrgUeSCellLchModInfo   *lchCfgCb
));
EXTERN S16 RgPrgPMacSMacUeSCellLchAddReq ARGS
((
 Pst                      *pst,
 RgPrgUeSCellLchAddInfo   *lchCfgCb
));
EXTERN S16 RgPrgPMacSMacUeSCellLchDelReq ARGS
((
 Pst                       *pst,
 RgPrgUeSCellLchDelInfo    *delLcCb
));
EXTERN S16 rgPomSndUeSCellLchDelToSmac ARGS((Inst inst,CrgDel *lcDel,
                                              Bool *isCfmRqrd));
EXTERN S16 rgPomSndUeSCellLchAddToSmac ARGS((Inst inst,RgCellCb *cell,
                                              RgUeCb *ue,CrgLchCfg *lchCfg,
                                              Bool *isCfmRqrd));
EXTERN S16 rgPomSndUeSCellLchModToSmac ARGS((Inst inst,RgCellCb *cell,
                                              RgUeCb *ue,CrgLchRecfg *lchRecfg,
                                              Bool *isCfmRqrd));
EXTERN S16 rgPomVldtAddLch ARGS((Inst                    inst,
                                 RgPrgUeSCellLchAddInfo  *lcCfg,
                                 RgCellCb                **cell,
                                 RgUeCb                  **ue
                               ));
EXTERN S16 rgPomUeSCellLcAdd ARGS((Inst                     inst,
                                   RgCellCb                 *cell,
                                   RgUeCb                   *ue,
                                   RgPrgUeSCellLchAddInfo   *lcCfg
                                 ));
EXTERN S16 rgPomVltdModLch ARGS ((Inst                     inst,
                                  RgPrgUeSCellLchModInfo   *lchCfgCb,
                                  RgCellCb                 **cell,
                                  RgUeCb                   **ue,
                                  RgUlLcCb                 **ulLc
                                 ));
EXTERN S16 rgPomUeSCellLcMod ARGS((Inst                     inst,
                                    RgUeCb                  *ue,
                                    RgUlLcCb                *ulLc,
                                    RgPrgUeSCellLchModInfo  *lchCfgCb
                                  ));
EXTERN S16 rgPomUeSCellLcDel ARGS((Inst                   inst,
                                 RgPrgUeSCellLchDelInfo   *delLcCb,
                                 RgUeCb                   *ue,
                                 RgUlLcCb                 *ulLc,
                                 RgDlLcCb                 *dlLc
                               ));
EXTERN S16 rgPomVltdDelLch ARGS ((Inst                      inst,
                                  RgPrgUeSCellLchDelInfo    *delLcCb,                              
                                  RgCellCb                  **cell,
                                  RgUeCb                    **ue,
                                  RgUlLcCb                  **ulLc,
                                  RgDlLcCb                  **dlLc
                                ));
EXTERN Void rgLaaPrgRcvSmacTbInd ARGS((

 Pst    *pst,
 RgLaaPrgTbInd  *tbInd
));
EXTERN Void rgLaaPrgRcvPmacTbReq ARGS ((

 Pst    *pst,
 RgLaaPrgTbReq  *tbReq
));
#endif

#ifdef __cplusplus
}
#endif
#endif /* __RGPRG_X__*/

/**********************************************************************
  
         End of file:     rg_pom_scell.x
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************
Put notes here
**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat       init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       mpatel        1. LTE MAC CA release
*/
