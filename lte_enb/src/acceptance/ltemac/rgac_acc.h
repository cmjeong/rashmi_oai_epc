


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      rgac_acc.h@@/main/3 - Sat Jul 30 02:20:50 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/


#ifndef __RGAC_ACCH__
#define __RGAC_ACCH__
#ifdef __cplusplus
extern "C" {
#endif
   /* This file contains #defines needed for the test architecture. */

#define RG_ACC_MAX_DAT_REQS   10 /* This is the maximum DATA requests are are maintained. */
#define RG_ACC_MAX_UE         200 /* Maximum number of UEs supported for testing */
#define RG_ACC_MAX_BCCH       30 /* Maximum number if BCCH PDUs supported for testing */
#define RG_ACC_MAX_SUBFRAMES  100 /* Maximum number of Subframes stored for testing */
#ifdef LTE_TDD
#define RG_ACC_MAX_RARNTI     60  /* Maximum number of RA-RNTIs possible */
#else
#define RG_ACC_MAX_RARNTI     10  /* Maximum number of RA-RNTIs possible */
#endif
#define RG_ACC_TFU_TQ_SIZE    1 
#define RG_ACC_TFU_MAX_TIMERS 2 
#define RG_ACC_CELL_ID        3 /* Default cell ID */ 
#define RG_ACC_DFLT_CQI       1 /* Default CQI */ 
/* Changes for MIMO feature addition */
#ifdef LTEMAC_MIMO
#define RG_ACC_DFLT_RI        1 /* Default RI */ 
#define RG_ACC_DFLT_PMI       1 /* Default PMI */ 
#endif
#define RG_ACC_DFLT_RBSTART   1 /* Default RB START for CQI reporting */ 
#define RG_ACC_DFLT_NUMRB     1 /* Default number of RBs for CQI reporting */ 
   /* following #defines are for the dummy encoder/decoder */
#define RG_ACC_EXT_PWR_HDR_CE 25 
#define RG_ACC_PWR_HDR_CE     26 
#define RG_ACC_CRNTI_CE       27
#define RG_ACC_TBSR_CE        28
#define RG_ACC_SBSR_CE        29
#define RG_ACC_LBSR_CE        30
#define RG_ACC_PADDING_CE     31
#define RG_ACC_CONT_RES_CE    28
#define RG_ACC_TIMING_ADV_CE  29
#define RG_ACC_DRX_CMD_CE     30
#ifdef LTE_ADV
#define RG_ACC_SCELL_ACT_CE  RG_SCELL_LCID_IDX 
#endif
   /* This should be same as the one in prooduct code rg_env.h */
#define DL_DELTA 2

#define RG_ACC_TFU_MAX_SUBHDRS    20
#define RG_ACC_LAST_SUBHDR    1
#define RG_ACC_LONG_SUBHDR    2
#define RG_ACC_SHORT_SUBHDR   3
#define RG_ACC_CCCH_SDU       0   

#define RG_ACC_DAT_PDU        1
#define RG_ACC_RAR_PDU        2

#define RGAC_RGU_MAXARR       10
#define RG_ACC_TF_TTI         1
#define CMXTA_TSTREG          DFLT_REGION
#define CMXTA_TSTPOOL         DFLT_POOL

#define RG_ACC_RA_RNTI        1
#define RG_ACC_CELLID         3 
/* Added support for SPS*/
#if (defined(LTEMAC_SPS))
#define RG_ACC_SPSRNTI        60 /*3C*/ /*SPS RNTI*/
#define RG_ACC_NUM_SPS_HARQ_PROC 4   /*!number of sps harq process */

#define RG_ACC_NUM_PUCCH_VALUES 2   /*!number of PUCCH values */

#define RG_ACC_N1_PUCCH_VALUES_1 0   /*!number of n1PUCCH values [0] */
#define RG_ACC_N1_PUCCH_VALUES_2 1598   /*!number of n1PUCCH values [1] */
#define RG_ACC_N1_PUCCH_VALUES_3 2030   /*!number of n1PUCCH values [2]*/
#define RG_ACC_N1_PUCCH_VALUES_4 400   /*!number of n1PUCCH values [3]*/

#define RG_ACC_P0_NOMINAL_PUSCH_VAL  -100 /**/
#define RG_ACC_P0_UE_PUSCH_VAL       -2 /**/
#define RG_ACC_SPS_PACKET_SIZE       100
#define RG_ACC_SPS_PACKET_PRD        20 /*Assming the 20ms  i.e. 20 TTI*/
#define RG_ACC_SPS_NUM_LOG_CHNLS     1  
#define RG_ACC_SPS_EXPLCT_REL_CNT    2  /*!< Number of SPS ocassions with BO = 0 after 
                                  which SPS shall be released */

#define RG_ACC_SPS_DL_BW 10

#endif 
#define RG_ACC_MAXARR         20
#define RG_ACC_MAX_SAVES      20

#define RG_ACC_MAX_PDU_SIZE   4096

#define RG_ACC_PLUS      1
#define RG_ACC_MINUS     2
#define RG_ACC_INVLD_CRNTI 0xFFFF
#ifdef RG_PFS_STATS
#define RG_ACC_DED_RNTI_START 171
#else
#define RG_ACC_DED_RNTI_START 121
#endif
#ifdef LTE_TDD
#define RGACCSCH_MIN_MAC_RNTI      61   /*!< Minimum value of RNTI to be managed by 
                                    MAC */
#define RG_ACC_MAX_PREAMBLE_FORMATS 5
#else
#define RGACCSCH_MIN_MAC_RNTI      11   /*!< Minimum value of RNTI to be managed by 
                                    MAC */
#define RG_ACC_MAX_PREAMBLE_FORMATS 4
#endif

#ifdef TFU_UPGRADE
/*Bit masks for PUCCH and PUSCH types */
/*Bitmasks for PUSCH */
#define RG_ACC_TFU_ZERO_MSK   0
#define RG_ACC_TFU_PUSCH_DATA (1<<0)
#define RG_ACC_TFU_PUSCH_HARQ (1<<1)
#define RG_ACC_TFU_PUSCH_CQI (1<<2)
#define RG_ACC_TFU_PUSCH_SRS (1<<3)



/*Bitmasks for PUCCH */
#define RG_ACC_TFU_PUCCH_HARQ (1<<8)
#define RG_ACC_TFU_PUCCH_CQI (1<<9)
#define RG_ACC_TFU_PUCCH_SRS (1<<10)
#define RG_ACC_TFU_PUCCH_SR (1<<11)

#define RG_ACC_UPD_BM_N_CHK_NODE_DEL(_BITMSK, _RECREQND, _RECREQ, _RECREQINFO) \
           _RECREQND->recpTypeBitMsk ^= _BITMSK; \
           if(RG_ACC_TFU_ZERO_MSK == _RECREQND->recpTypeBitMsk) \
           {\
              cmLListDelFrm(&_RECREQ->ueRecpReqLst, &_RECREQND->node->lnk);\
              cmLListDelFrm(&_RECREQINFO->ueRecpReqNdLst, &_RECREQND->lnk);\
              rgAcUtlFreeMem ((Data *)_RECREQND, sizeof(RgAcTfuUeRecpReqNode));\
           }
#endif

#ifdef LTEMAC_HDFDD
/* Introduced timing delta for DL control */
#define RGAC_HDFDD_SF_HIST   (TFU_DLCNTRL_DLDELTA + 1)   /* Three subframes */
/* Subframe States */
#define RGAC_HDFDD_NOSCHD       0x00 /* Not scheduled */
#define RGAC_HDFDD_DLDATA       0x01 /* Not DL data+cntrl scheduled */
#define RGAC_HDFDD_DLCNTRL      0x02 /* Not scheduled only downlink Control is scheduled*/
#define RGAC_HDFDD_UL           0x04 /* Not scheduled uplink data scheduled */

#endif

#ifdef RGR_CQI_REPT
#define RGAC_DLPWR_CQIMAXN RGR_CQIRPTS_MAXN
#endif

#define RGAC_UE_DLPWRCNTRL_PA_DB_6 0
#define RGAC_UE_DLPWRCNTRL_PA_DB_4dot77 1
#define RGAC_UE_DLPWRCNTRL_PA_DB_3 2
#define RGAC_UE_DLPWRCNTRL_PA_DB_1dot77 3
#define RGAC_UE_DLPWRCNTRL_PA_DB0 4
#define RGAC_UE_DLPWRCNTRL_PA_DB1 5
#define RGAC_UE_DLPWRCNTRL_PA_DB2 6
#define RGAC_UE_DLPWRCNTRL_PA_DB 7

#define RGAC_RB_FREE 0
#define RGAC_RB_BUSY 1

#define RGAC_XML_GET_VALLIST(_parseStr, _strName, _strTok, _dstArray,  _size, _num)       \
{                                                                                   \
      Txt   *_token   =  NULLP;                                                        \
      U8    _i        =  0;                                                            \
      CMXTA_ZERO(_parseStr, sizeof(_parseStr));                                        \
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, _strName, _parseStr);    \
      _token =  strtok(_parseStr, _strTok);                                            \
      for(_i=0;_token != NULLP;(_token =  strtok(NULLP, _strTok)), _i++)               \
         _dstArray[_i]  =  (_size )atoi(_token);                                       \
      _num = _i; \
}

#ifdef __cplusplus
}
#endif
#endif /* __RGAC_ACCH__ */



/**********************************************************************
 
         End of file:     rgac_acc.h@@/main/3 - Sat Jul 30 02:20:50 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ps              1. Initial Release.
/main/2      ---     ps              1. LTE MAC 2.1 release
           rg007.201   ap  1. Added support for MIMO
           rg008.201 rsharon 1. Added support for SPS.
           rg009.201 dv 1.Added TFU_UPGRADE in 2.1 mnt.
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
           rg002.301  asehgal 1.ccpu00118351: seperate UL & DL deltas.
$SID$      ---        rt      1. LTE MAC 4.1 release
*********************************************************************91*/
