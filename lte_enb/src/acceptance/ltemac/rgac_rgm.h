
/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    rgac_rgm.h

     Sid:      rgac_rgm.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:22 2013

     Prg:     nsadar 
*********************************************************************21*/

#ifndef __RGAC_RGM_H__
#define __RGAC_RGM_H__
#ifdef __cplusplus
extern "C" {
#endif
   
/* Directions for Logical Channels */
#define RGAC_RGM_DIR_TX_RX RGAC_RGR_DIR_TX | RGAC_RGR_DIR_RX
#define RGAC_RGM_DIR_TX    (1<<0)
#define RGAC_RGM_DIR_RX    (1<<1)

/* Default Values for CRG */
#define RGAC_RGM_DEFAULT_TRANSID 1
#define RGAC_RGM_DEFAULT_CELLID 3 
#define RGAC_RGM_FALSE FALSE
#define RGAC_RGM_DEFAULT_NUMTXNPORTS 1
#define RGAC_RGM_DEFAULT_DLTOTBW 100
#define RGAC_RGM_DEFAULT_ULTOTBW 100
#define RGAC_RGM_DEFAULT_DLCQI 6

/* Config/Reconfig MACROs */
#define RGAC_RGM_CONFIG   RGM_CONFIG 


#define RGAC_RGM_USERENT    ENTRM 
#define RGAC_RGM_PROVENT    ENTRG
#define RGAC_RGM_USERINST   CMXTA_INST_ID
#define RGAC_RGM_PROVINST   CMXTA_INST_ID
#define RGAC_RGM_SRCPROC    CMXTA_PROC_ID 
#define RGAC_RGM_DSTPROC    CMXTA_PROC_ID
#define RGAC_RGM_MATCHPROC  FALSE


#define RGAC_RGM_EVTBNDCFM   EVTRGMBNDCFM
#define RGAC_RGM_EVTBNDREQ   EVTRGMBNDREQ
#define RGAC_RGM_EVTUBNDREQ   EVTRGMUBNDREQ
#define RGAC_RGM_EVTCFGPRBREPRT  EVTRGMCFGPRBRPRT
#define RGAC_RGM_EVTCFGPRBREPRTIND  EVTRGMPRBRPRTIND
#define RGAC_RGM_EVTCFGTRANSMODEIND EVTRGMTRANSMODEIND


#define RGAC_RGM_DFLTRGN  cmXtaCb.init.region 
#define RGAC_RGM_DFLTPOOL cmXtaCb.init.pool

#define RGAC_RGM_BNDREQ(_pst, _suId, _spId)     RmLiRgmBndReq(_pst, _suId, _spId);
#define RGAC_RGM_UBNDREQ(_pst, _suId, _reason)  RmLiRgmUbndReq(_pst, _suId, _reason);
#define RGAC_RGM_PRB_RPRT_CONFIG(_pst, _suId, _config) RmLiRgmCfgPrbRprt(_pst, _suId, _config);


#ifdef __cplusplus
}
#endif
#endif /* __RGAC_RGM_H__ */

/**********************************************************************
  
         End of file:     rgac_rgm.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:22 2013
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************

**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ns  1. Initial Release.
/main/2      ---     ns  1. LTE MAC 2.1 release
             rg001.201 sm            1. Added TTI indication towards 
                                        RGM user.
             rg004.201   1.Modified for SI Enhancement
/main/3      ---     dvasisht          1. Updated for LTE MAC Release 3.1          
*********************************************************************91*/
