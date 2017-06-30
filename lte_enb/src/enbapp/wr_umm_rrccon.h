
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_rrccon.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_RRCCON_H__
#define __WR_UMM_RRCCON_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#define WR_UMM_RRC_CON_TRANS_UE        0x00
#define WR_UMM_RRC_CON_TRANS_SRB       0x01
#define WR_UMM_RRC_CON_TRANS_SRB_LCG   0x02

#define WR_UMM_RRC_CON_CFG_IDLE        0
#define WR_UMM_RRC_CON_CFG_SENT        1
#define WR_UMM_RRC_CON_CFG_SUCC        2
#define WR_UMM_RRC_CON_CFG_FAIL        3
#define WR_UMM_RRC_CON_CFG_ERRO        4

#define WR_UMM_RRC_CON_INITED          0
#define WR_UMM_RRC_CON_PHY_CFGD        1
#define WR_UMM_RRC_CON_SCH_CFGD        2
#define WR_UMM_RRC_CON_STK_CFGD        3

#define WR_UMM_RRC_REJ_DUE_TO_CONGESTION 1
#define WR_UMM_RRC_REJ_DUE_TO_UNSPECIFIC 2

/** 
  * @brief This is a structure for RRC Setup
  * transaction. 
  * @details The structure members 
  * - U8                        state;       State within the transaction 
  * - WrGummei                  gummei;      GUMMEI received from UE                  
  * - TknU32                    gummeiType;  GUMMEI Type
  * - U8                        selPlmnIdx;  Index of the selected PLMN 
  * - U16                       tac;         Tracking area code 
  * - WrPlmnId                  *plmnId;     PLMN ID  
  * - WrMmeId                   mmeId;       Selected MMEID 
  * - TknStrOSXL                *nasPdu;     NAS PDU received from UE 
  * - U8                        schUeCfg;    Flag to indicate SCHD CFG 
  * - U8                        schSrbCfg;   Flag to indicate SRBs SCHD CFG 
  * - U8                        phyCfg;      Flag to indicate PHY CFG 
  * - U8                        rrcCfg;      Flag to indicate RRC CFG 
  * - U8                        ueCfg;       Flag to indicate UE CFG 
  */
/**
 * Defination of RRC Connection Transaction CB*/
typedef struct wrRrcConTransCb {
    U8                        state;      
    WrGummei                  gummei;                     
    TknU32                    gummeiType;
    U8                        selPlmnIdx; 
    U16                       tac;        
    WrPlmnId                  *plmnId;    
    WrMmeId                   mmeId;      
    TknStrOSXL                *nasPdu;    
    U8                        schUeCfg;   
    U8                        schSrbCfg;  
    U8                        phyCfg;     
    U8                        rrcCfg;     
    U8                        ueCfg;      
    RmuStatusInfo             ueAdmitStatus;
} WrRrcConTransCb;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_RRCCON_H__ */

/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
