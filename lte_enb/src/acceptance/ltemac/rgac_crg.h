

/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    rgac_crg.h

     Sid:      rgac_crg.h@@/main/3 - Sat Jul 30 02:20:51 2011

     Prg:     ns 
*********************************************************************21*/

#ifndef __RGAC_CRG_H__
#define __RGAC_CRG_H__
#ifdef __cplusplus
extern "C" {
#endif

   /* Directions for Logical Channels */
#define RGAC_CRG_DIR_TX_RX RGAC_CRG_DIR_TX | RGAC_CRG_DIR_RX
#define RGAC_CRG_DIR_TX    (1<<0)
#define RGAC_CRG_DIR_RX    (1<<1)

   /* NG ENUMS */
#define RGAC_CRG_NG_ONESIXTH CRG_NG_ONESIXTH
#define RGAC_CRG_NG_HALF CRG_NG_HALF
#define RGAC_CRG_NG_ONE CRG_NG_ONE
#define RGAC_CRG_NG_TWO CRG_NG_TWO

/* Default Values for CRG */
#define RGAC_CRG_DEFAULT_TRANSID 1
#define RGAC_CRG_DEFAULT_CELLID 3 
#define RGAC_CRG_FALSE FALSE
#define RGAC_CRG_DEFAULT_NUMTXNPORTS 1
#define RGAC_CRG_DEFAULT_DLTOTBW 100
#define RGAC_CRG_DEFAULT_ULTOTBW 100

/* Config/Reconfig/Delete MACROs */
#define RGAC_CRG_CONFIG   CRG_CONFIG
#define RGAC_CRG_RECONFIG CRG_RECONFIG
#define RGAC_CRG_DELETE   CRG_DELETE
#define RGAC_CRG_RESET    CRG_RESET

/* Re Configuration types for CELL */
#define RGAC_CRG_CELL_PUCCH_RECFG (1<<0)
#define RGAC_CRG_CELL_SRS_RECFG (1<<1)
#define RGAC_CRG_CELL_RACH_RECFG (1<<2)

   /* Ue Reconfig related MACROs */
#define RGAC_CRG_UE_ULHARQ_RECFG     (1<<0)

/* Cell/Ue/Logical channel MACROs */
#define RGAC_CRG_CELL_CFG CRG_CELL_CFG 
#define RGAC_CRG_UE_CFG   CRG_UE_CFG
#define RGAC_CRG_LCH_CFG  CRG_LCH_CFG

/* Logical channel types related MACROs */
#define RGAC_CRG_LCH_BCCH 1 
#define RGAC_CRG_LCH_PCCH 2
#define RGAC_CRG_LCH_CCCH 3
#define RGAC_CRG_LCH_DCCH 4
#define RGAC_CRG_LCH_DTCH 5

/* Cell Reconfig related MACROs */
#define RGAC_CRG_CELL_PUCCH_RECFG (1<<0)
#define RGAC_CRG_CELL_SRS_RECFG (1<<1)
#define RGAC_CRG_CELL_RACH_RECFG (1<<2)

#define RGAC_CRG_MAX_STS_TX_OFFSET 8

#define RGAC_CRG_CFG_TRANSID_SIZE 12
#define RGAC_CRG_USERENT    ENTNH
#define RGAC_CRG_PROVENT    ENTRG
#define RGAC_CRG_USERINST   CMXTA_INST_ID
#define RGAC_CRG_PROVINST   CMXTA_INST_ID
#define RGAC_CRG_SRCPROC    CMXTA_PROC_ID 
#define RGAC_CRG_DSTPROC    CMXTA_PROC_ID
#define RGAC_CRG_MATCHPROC  FALSE


#define RGAC_CRG_EVTBNDCFM   EVTCRGBNDCFM
#define RGAC_CRG_EVTBNDREQ   EVTCRGBNDREQ
#define RGAC_CRG_EVTUBNDREQ  EVTCRGUBNDREQ
#define RGAC_CRG_EVTCFGREQ   EVTCRGCFGREQ
#define RGAC_CRG_EVTCFGCFM   EVTCRGCFGCFM

#define RGAC_CRG_DFLTRGN  rgCb.init.region 
#define RGAC_CRG_DFLTPOOL rgCb.init.pool

#define RGAC_CRG_BNDREQ(_pst, _suId, _spId)     NhLiCrgBndReq(_pst, _suId, _spId);
#define RGAC_CRG_UBNDREQ(_pst, _suId, _reason)  NhLiCrgUbndReq(_pst, _suId, _reason);

#define RGAC_CRG_CELLCFGREQ(_pst, _spId, _transId, _cfg)  NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_CRG_UECFGREQ(_pst, _spId, _transId, _cfg)  NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_CRG_LCCFGREQ(_pst, _spId, _transId, _cfg)  NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);

#define RGAC_CRG_CELLRECFGREQ(_pst, _spId, _transId, _cfg)  NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_CRG_UERECFGREQ(_pst, _spId, _transId, _cfg)  NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_CRG_LCRECFGREQ(_pst, _spId, _transId, _cfg)  NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);

#define RGAC_CRG_DELREQ(_pst, _spId, _transId, _cfg) NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_CRG_RSTREQ(_pst, _spId, _transId, _cfg) NhLiCrgCfgReq(_pst, _spId, _transId, _cfg);
 
#ifdef __cplusplus
}
#endif
#endif /* __RGAC_CRG_H__ */


/**********************************************************************
  
         End of file:     rgac_crg.h@@/main/3 - Sat Jul 30 02:20:51 2011
  
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
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---    rt     1. LTE MAC 4.1 release
*********************************************************************91*/
