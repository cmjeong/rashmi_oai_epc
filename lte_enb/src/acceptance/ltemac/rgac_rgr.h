

/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    rgac_rgr.h

     Sid:      rgac_rgr.h@@/main/3 - Sat Jul 30 02:21:01 2011

     Prg:     nsadar 
*********************************************************************21*/

#ifndef __RGAC_RGR_H__
#define __RGAC_RGR_H__
#ifdef __cplusplus
extern "C" {
#endif
   
/* Directions for Logical Channels */
#define RGAC_RGR_DIR_TX_RX RGAC_RGR_DIR_TX | RGAC_RGR_DIR_RX
#define RGAC_RGR_DIR_TX    (1<<0)
#define RGAC_RGR_DIR_RX    (1<<1)

#define RGAC_RGR_MAX_LCINFO 50
   /* NG ENUMS SHASHAHNK */

#define RGAC_RGR_NG_ONESIXTH 0
#define RGAC_RGR_NG_HALF 1
#define RGAC_RGR_NG_ONE 2
#define RGAC_RGR_NG_TWO 3

/* Default Values for CRG */
#define RGAC_RGR_DEFAULT_TRANSID 1
#define RGAC_RGR_DEFAULT_CELLID 3 
#define RGAC_RGR_FALSE FALSE
#define RGAC_RGR_DEFAULT_NUMTXNPORTS 1
#define RGAC_RGR_DEFAULT_DLTOTBW 100
#define RGAC_RGR_DEFAULT_ULTOTBW 100
#define RGAC_RGR_DEFAULT_DLCQI 6

/* Re Configuration types for CELL */
#define RGAC_RGR_CELL_PUCCH_RECFG (1<<0)
#define RGAC_RGR_CELL_SRS_RECFG (1<<1)
#define RGAC_RGR_CELL_RACH_RECFG (1<<2)

   /* Ue Reconfig related MACROs */
#define RGAC_RGR_UE_TXMODE_RECFG     (1<<0)
#define RGAC_RGR_UE_DLHARQ_RECFG     (1<<1)
#define RGAC_RGR_UE_APRD_DLCQI_RECFG (1<<2)
#define RGAC_RGR_UE_PRD_DLCQI_RECFG  (1<<3)
#define RGAC_RGR_UE_ULHARQ_RECFG     (1<<4)
#define RGAC_RGR_UE_QOS_RECFG        (1<<5)
#define RGAC_RGR_UE_TATMR_RECFG      (1<<6)
#define RGAC_RGR_UE_ULPWR_RECFG      (1<<7)
#define RGAC_RGR_UE_MEASGAP_RECFG    (1<<8)

/* Logical channel types related MACROs */
#define RGAC_RGR_LCH_BCCH 1 
#define RGAC_RGR_LCH_PCCH 2
#define RGAC_RGR_LCH_CCCH 3
#define RGAC_RGR_LCH_DCCH 4
#define RGAC_RGR_LCH_DTCH 5

/* Cell Reconfig related MACROs */
#define RGAC_RGR_CELL_PUCCH_RECFG (1<<0)
#define RGAC_RGR_CELL_SRS_RECFG (1<<1)
#define RGAC_RGR_CELL_RACH_RECFG (1<<2)

#define RGAC_RGR_MAX_STS_TX_OFFSET 8

#define RGAC_RGR_CFG_TRANSID_SIZE 12

/* Config/Reconfig MACROs */
#define RGAC_RGR_CONFIG   RGR_CONFIG 
#define RGAC_RGR_RECONFIG RGR_RECONFIG
#define RGAC_RGR_DELETE   RGR_DELETE
#define RGAC_RGR_RESET    RGR_RESET
#define RGAC_RGR_SCELL_ACT RGR_SCELL_ACT
#define RGAC_RGR_SCELL_DEACT RGR_SCELL_DEACT
#define RGAC_RGR_SCELL_READY RGR_SCELL_READY

#define RGAC_RGR_DEFAULT_MAXBWPERUE 50


/* Cell MACROs */
#define RGAC_RGR_CELL_CFG RGR_CELL_CFG 
#define RGAC_RGR_UE_CFG   RGR_UE_CFG
#define RGAC_RGR_LCH_CFG  RGR_LCH_CFG
#define RGAC_RGR_LCG_CFG  RGR_LCG_CFG
#define RGAC_RGR_ENB_CFG  RGR_ENB_CFG 

/* Cell Reconfig related MACROs */
#define RGAC_RGR_CELL_DL_CMNRATE_RECFG (1<<0)
#define RGAC_RGR_CELL_CFI_RECFG        (1<<1)
#define RGAC_RGR_CELL_TRGCQI_RECFG     (1<<2)
#define RGAC_RGR_CELL_PUSCH_SB_RECFG   (1<<3)
#define RGAC_RGR_CELL_UL_CMNRATE_RECFG (1<<4)
#define RGAC_RGR_CELL_DL_HARQ_RECFG    (1<<5)

   /* Different Scheduler Type Values */
#define RGAC_RGR_SCH_TYPE_SC1   0 
#define RGAC_RGR_SCH_TYPE_PFS   1
#define RGAC_RGR_SCH_TYPE_RR    2
#define RGAC_RGR_SCH_TYPE_MAXCI 3
   /* Power Realted Macros */
#define RGAC_RGR_PWR_ALPHAALL 10
   
   /* PFS Specific macros */
#define RGR_PFS_PRIO_LVLS  17

#define RGAC_RGR_USERENT    ENTNX 
#define RGAC_RGR_PROVENT    ENTRG
#define RGAC_RGR_USERINST   CMXTA_INST_ID
#define RGAC_RGR_PROVINST   CMXTA_INST_ID
#define RGAC_RGR_SRCPROC    CMXTA_PROC_ID 
#define RGAC_RGR_DSTPROC    CMXTA_PROC_ID
#define RGAC_RGR_MATCHPROC  FALSE


#define RGAC_RGR_EVTBNDCFM   EVTRGRBNDCFM
#define RGAC_RGR_EVTBNDREQ   EVTRGRBNDREQ
#define RGAC_RGR_EVTUBNDREQ  EVTRGRBNDREQ
#define RGAC_RGR_EVTCFGREQ   EVTRGRCFGREQ
#define RGAC_RGR_EVTCFGCFM   EVTRGRCFGCFM
#define RGAC_RGR_EVTTTIIND   EVTRGRTTIIND

#ifdef RGR_CQI_REPT
#define RGAC_RGR_EVTSTAIND   EVTRGRSTAIND
#endif
/* LTE_ADV_FLAG_REMOVED_START */
#define RGAC_RGR_EVTLOADINFIND   EVTRGRLOADINFIND
#define RGAC_RGR_EVTLOADINFREQ   EVTRGRLOADINFREQ
/* LTE_ADV_FLAG_REMOVED_END */
#define RGAC_RGR_EVTRGRUESTAIND EVTRGRUESTAIND
/* Added for SI Enhancement*/
#ifdef RGR_SI_SCH
#define RGAC_RGR_EVTSICFGREQ   EVTRGRSICFGREQ
#define RGAC_RGR_EVTSICFGCFM   EVTRGRSICFGCFM
#define RGAC_RGR_EVTWARNINGSICFGREQ   EVTRGRWARNINGSICFGREQ
#define RGAC_RGR_EVTSIWARNINGCFGCFM   EVTRGRWARNINGSICFGCFM
#define RGAC_RGR_EVTSIWARNINGSISTOPREQ   EVTRGRWARNINGSISTOPREQ
#endif

#define RGAC_RGR_DFLTRGN  cmXtaCb.init.region 
#define RGAC_RGR_DFLTPOOL cmXtaCb.init.pool

#define RGAC_RGR_BNDREQ(_pst, _suId, _spId)     NxLiRgrBndReq(_pst, _suId, _spId);
#define RGAC_RGR_UBNDREQ(_pst, _suId, _reason)  NxLiRgrUbndReq(_pst, _suId, _reason);

#define RGAC_RGR_CELLCFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_UECFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_LCCFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_LCGFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_ENBCFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);

#define RGAC_RGR_CELLRECFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_UERECFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_LCRECFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_LCGRECFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);

#define RGAC_RGR_DELREQ(_pst, _spId, _transId, _cfg) NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_RSTREQ(_pst, _spId, _transId, _cfg) NxLiRgrCfgReq(_pst, _spId, _transId, _cfg);
#ifdef RGR_SI_SCH
#define RGAC_RGR_SICFGREQ(_pst, _spId, _transId, _cfg)  NxLiRgrSiCfgReq(_pst, _spId, _transId, _cfg);
#define RGAC_RGR_WARNINGSICFGREQ(_pst, _spId,  _transId,_cfg)  NxLiRgrWarningSiCfgReq(_pst, _spId,  _transId,  _cfg);
#define RGAC_RGR_WARNINGSISTOPREQ(_pst, _spId, _transId,  _siId)  NxLiRgrWarningSiStopReq(_pst, _spId,  _transId, _siId);
#endif
/* LTE_ADV_FLAG_REMOVED_START */
#define RGAC_RGR_LOADINFREQ(_pst, _spId, _transId, _cfg) NxLiRgrLoadInfReq(_pst, _spId, _transId, _cfg);
/* LTE_ADV_FLAG_REMOVED_END */
#define RGAC_NUM_SUBFRAMES 10
#define RGAC_MAX_SFN 1024

/* Added for sending TTI tick to RRM */
#define RGR_ADD_TO_CRNTTIME(crntTime, toFill, incr)          \
      toFill.sfn = (crntTime.sfn + (incr)) % RGAC_MAX_SFN;      

#ifdef __cplusplus
}
#endif
#endif /* __RGAC_RGR_H__ */

/**********************************************************************
  
         End of file:     rgac_rgr.h@@/main/3 - Sat Jul 30 02:21:01 2011
  
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
                                        RGR user.
             rg004.201   1.Modified for SI Enhancement
/main/3      ---     dvasisht          1. Updated for LTE MAC Release 3.1          
$SID$        ---     rt     1. LTE MAC 4.1 release
*********************************************************************91*/
