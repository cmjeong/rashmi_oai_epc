

/********************************************************************20**
  
        Name:    Convergence Layer specific
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for CL
 
        File:    ys.x

        Sid:      ys.x@@/main/2 - Thu Dec  2 02:27:13 2010
  
        Prg:     pkumar
  
*********************************************************************21*/

#ifndef __YS_X__
#define __YS_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/
#include "lys.x"
#ifdef YS_PICO
#include "ys_pc_ta_alg.h"   
#endif
/* Forward declarations */
typedef struct ysCb           YsCb;
typedef struct ysCellCb       YsCellCb;
typedef struct ysUeCb         YsUeCb;  
/*ys003.102 SINR to CQI Mapping*/
#ifdef YS_PICO_ESINR 
#define YS_NUM_RSSI_SAMPLES 5
#endif

/** 
  * Control Block structure for Upper SAPs at CTF and TFU interfaces
  */
typedef struct ysCtfSapCb
{
   Pst         sapPst;          /* Post info associated with SAP */
   SpId        spId;            /* SpId associated with SAP */
   SuId        suId;            /* SuId associated with SAP */
   State       sapState;        /* SAP state. */
   YsCtfSapSts ctfSts;          /* CTF SAP statistics */
}YsCtfSapCb;

typedef struct ysTfuSapCb
{
   YsTfuSapCfg  tfuSapCfg;    /* SAP cfg received from LM */
   Pst          sapPst;       /* Post info associated with SAP */
   SpId         spId;         /* SpId associated with SAP */
   SuId         suId;         /* SuId associated with SAP */
   YsCellCb     *cellCb;      /* Cell Control Block */
   State        sapState;     /* SAP state. */
   YsTfuSapSts  tfuSts;       /* TFU SAP statistics */
   YsL1PhySts   phySts;       /* message related statistics */
}YsTfuSapCb;

typedef struct ysTxMsgInfo
{
   TfuCntrlReqInfo *cntrlReq;
   TfuCntrlReqInfo *hiDciReq;
   TfuDatReqInfo   *datReq;
   TfuRecpReqInfo  *recpReq;
} YsTxMsgInfo;

typedef struct ysTxMsgArr
{
   U8             num;
   YsTxMsgInfo    txMsgInfo[YS_NUM_MSG_INFO];
} YsTxMsgArr;

#ifdef YS_PICO
typedef struct ysPduTypeInfo
{
   Bool             pres;
   YsUeCb           *ueCb;
   Bool             srPres;
   Bool             cqiPres;
#ifdef LTEMAC_MIMO
   Bool             riPres;
#endif
   TfuUeRecpReqInfo *schReqInfo;
   TfuUeRecpReqInfo *harqReqInfo;
} YsPduTypeInfo;

typedef struct ysSrCfgInfo
{
   U8    srCfgIndex;             /*!< SR Config Index, (0..154) */
   U8    srPeriod;               /*!< SR periodicity */
   U8    srSfOffSet;             /*!< SR subframe ofset */
}YsSrCfgInfo;


typedef struct ysSrsCfgInfo
{
   U16    srsCfgIndex;            /*!< SRS Config Index, (0..636) */
   U16    srsPeriod;              /*!< SRS periodicity */
   U16    srsSfOffSet;            /*!< SRS subframe ofset */
}YsSrsCfgInfo;

typedef struct ysCqiPmiCfgIdxInfo
{
   U32    cqiPmiCfgIndex;         /*!< Cqi-PMI Config Index, (0..315) */
   U32    cqiPeriod;              /*!< Cqi periodicity */
   U32    cqiSfOffSet;            /*!< Cqi subframe ofset */
}YsCqiPmiCfgIdxInfo;

#ifdef LTEMAC_MIMO
typedef struct ysRiCfgIdxInfo
{
   U32    riCfgIndex;         /*!< Ri Config Index, (0..1023) */
   U8    mRi;                /*!< Ri periodicity in multiples of cfgd CQI perioicity */
   S32   riSfOffSet;         /*!< Ri subframe ofset */
}YsRiCfgIdxInfo;
#endif

typedef struct ysCqiPmiRiMap
{
   Bool    cqiPres;
   Bool    pmiPres;
   Bool    riPres;
}YsCqiPmiRiMap;

#ifdef LTE_TDD
typedef struct ysPrachTddCfgInfo
{
   U8    prachCfgIndex;          /*!< Prach Config Index, (0..63) */
   S8    preamFrmt;              /*!< Preamble Format, (0..4) */
   S8    dRA;                    /*!< Density per 10ms */
   S8    rRA;                    /*!< version */
}YsPrachTddCfgInfo;

typedef struct ysPrachTddMapInfo
{
   U8    fRA;          /*!< Freq. resource index */
   U8    t0RA;         /*!< RACH occurence in radio frames */
   U8    sfNo;         /*!< Subframe Number */
}YsPrachTddMapInfo;

typedef struct ysPrachTddMapLst
{
   U8                numCfg;                 /* Number of UL/DL cfg */
   YsPrachTddMapInfo prachTddMapLst[YS_NUM_CFG_PER_PRACH_CFG];
}YsPrachTddMapLst;

typedef struct ysPrachCb
{
   YsPrachTddCfgInfo *rachCfgInfo;           /* RACH configurations in TDD */
   YsPrachTddMapLst  *rachMapInfo;
   U8                ysPrachPresArr[YS_NUM_PRACH_PRES_ARR]; /* Even:0-9, Odd:10-19 */
}YsPrachCb;

#else /* LTE_TDD */

typedef struct ysPrachFddCfgInfo
{
   U8        prachCfgIndex;          /*!< Prach Config Index, (0..63) */
   S8        preamFrmt;              /*!< Preamble Format, (0..4) */
   U8        sfn;                    /*!< System Frame Number Type */
   U8        numSf;                  /*!< Number of Subframe Cfg */
   U8        sf[YS_NUM_SUB_FRAMES];  /*!< Subframe Number */
}YsPrachFddCfgInfo;

typedef struct ysPrachCb
{
   YsPrachFddCfgInfo *rachCfgInfo;   /* RACH configurations in FDD */
   U32               ysPrachPres;    /* Even:0-9, Odd:10-19 */
}YsPrachCb;
#endif /* LTE_TDD */

typedef struct ysSrCb
{
   CmLListCp       srPeriod5Lst[YS_SR_PERIOD_5];
   CmLListCp       srPeriod10Lst[YS_SR_PERIOD_10];
   CmLListCp       srPeriod20Lst[YS_SR_PERIOD_20];
   CmLListCp       srPeriod40Lst[YS_SR_PERIOD_40];
   CmLListCp       srPeriod80Lst[YS_SR_PERIOD_80];
}YsSrCb;

#ifdef LTEMAC_MIMO
typedef enum ysPerCqiMode
{
   YS_PERCQI_MODE10,
   YS_PERCQI_MODE11
}YsPerCqiMode;

typedef enum ysExpctdRpt
{
   YS_PER_CQI,
   YS_PER_RI
}YsExpctdRpt;

typedef struct ysPerCqiMode10
{
   U8 cqi;  /* size of cqi field in bits */
}YsPerCqiMode10;

typedef struct ysPerCqiMode11
{
   U8    cqi;         /* size of cqi field in bits */
   TknU8 wideDiffCqi; /* size of Diff cqi field in bits */
   U8    pmi;         /* size of PMI field in bits */
}YsPerCqiMode11; 

typedef struct ysUeCqiRiCb
{
   U32          riPeriodicity; /*RI periodicity Mri*Cqi  periodicity */
   S32          riCqiOffset;   /*Computed offset= -(cqiOffset+riOffset) */
   U8           lastRi;        /*Latest RI */
   YsExpctdRpt  expctdRpt;     /*Next expected report RI or CQI */
   U8           riSz;          /*Size of RI in bits */
   YsPerCqiMode perCqiMode;    /*Reriodic CQI mode */
   union {
      YsPerCqiMode10 mode10Info;
      YsPerCqiMode11 mode11Info;
   }cqiSz;
}YsUeCqiRiCb;
#endif

typedef struct ysCqiCb
{
#ifdef LTE_TDD
   CmLListCp       cqiPeriod1Lst[YS_CQI_PERIOD_1];
#else
   CmLListCp       cqiPeriod2Lst[YS_CQI_PERIOD_2];
   CmLListCp       cqiPeriod32Lst[YS_CQI_PERIOD_32];
   CmLListCp       cqiPeriod64Lst[YS_CQI_PERIOD_64];
   CmLListCp       cqiPeriod128Lst[YS_CQI_PERIOD_128];
#endif
   CmLListCp       cqiPeriod5Lst[YS_CQI_PERIOD_5];
   CmLListCp       cqiPeriod10Lst[YS_CQI_PERIOD_10];
   CmLListCp       cqiPeriod20Lst[YS_CQI_PERIOD_20];
   CmLListCp       cqiPeriod40Lst[YS_CQI_PERIOD_40];
   CmLListCp       cqiPeriod80Lst[YS_CQI_PERIOD_80];
   CmLListCp       cqiPeriod160Lst[YS_CQI_PERIOD_160];
}YsCqiCb;
#endif /* YS_PICO */

/** 
  * UE control block for UE specific information
  */
struct ysUeCb
{
   CmLteRnti            ueId;             /* UE ID */
   CtfDedCfgInfo        ueCfg;            /* UE configuration */
   YsCellCb             *cellCb;          /* Cell Control Block */
   CmLList              lnkUeLst;         /* Link List Node for UE List */
#ifdef YS_PICO                                                   
   CmLList              lnkSrLst;         /* Link List Node for SR List */
   CmLList              lnkCqiLst;        /* Link List Node for CQI List */
   taAlgState_t         taAlgState;
   YsSrCfgInfo          *srCfgInfo;
   YsCqiPmiCfgIdxInfo   *cqiCfgInfo;
#ifdef LTEMAC_MIMO
   YsUeCqiRiCb          cqiRiCb;          /* RI-CQI related computed information */
   YsRiCfgIdxInfo       *riCfgInfo;       /* RI Cfg INfo */
#endif
   U8                   pduType;
   Bool                 taAlgRestartReqd;
#endif
/*ys003.102 SINR to CQI Mapping*/
#ifdef YS_PICO_ESINR 
U8                   sinr[YS_NUM_RSSI_SAMPLES];
U8                   crntSinrIdx;
U8                   numSinrSamples;
U8                   ulCqi;
U16                  totalSinr;
#endif
};

/** 
  * control block for storing common information of Ues
  */
typedef struct ysUeListCb
{
   CmLListCp       ueLst;                       /* Link list of UE control 
                                                   blocks: YsUeCb */
}YsUeListCb;

/** 
  * List of UEId's 
  */
typedef struct ysUeLst
{
   U16         numUe;
   YsUeCb      *ueLst[YS_NUM_UES];
}YsUeLst;   


  /* ys005.102 : Adding the new structure YsPicoSpecific */
typedef struct YsPicoSpecific
{  
   U16               syncSigPowOs;              /*!< Synchronization signal power offset */
   Bool              syncSigPowOsPres;
   U16               cfiPowOs;                  /*!< Cfi Power Offset */
   Bool              cfiPowOsPres;
   U16               dciPowOs;                  /*!< Dci Power Offser */
   Bool              dciPowOsPres;
   U16               extWinMargin;              /*!< Extraction Window Marin */
   Bool              extWinMarginPres;
   U16               pucchNoiseGamma;           /*!< PUCCH Noise Estimation Gamma*/
   Bool              pucchNoiseGammaPres;
   U16               prachPkRatio4;             /*!< PRACH Format4 Peak Ratio */
   Bool              prachPkRatio4Pres;
   U16               prachPkRatio0;             /*!< PRACH Format0 Peak Ratio */
   Bool              prachPkRatio0Pres;
   U16               srsDopEstFactor;           /*!< Doppler Estimation Compensation Power */
   Bool              srsDopEstFactorPres;
   U16               puschProbDtxAck;           /*!< Portability Dtx Ack PUSCH */
   Bool              puschProbDtxAckPres;
   U16               pucchProbDtxAck;           /*!< Portability Dtx Ack PUCCH Format1 */
   Bool              pucchProbDtxAckPres;

   U16               txAntennaPorts ;           /*!< The number of cell specific transmit antenna ports */
   Bool              txAntennaPortsPres;
   U16               rxAntennaPorts ;           /*!< The number of cell specific receive antenna ports */
   Bool              rxAntennaPortsPres ;

   U16               phySyncMode;               /*!< The method used by the PHY to signal the 1ms subframe */
   Bool              phySyncModePres;
   U16               dataRepMode;               /*!< The data report mode for the uplink data */
   Bool              dataRepModePres ;
   U16               rachSrRepMode;             /*!< The reporting mode for RACH.indication and SR.indcation */
   Bool              rachSrRepModePres;
   /* Following fields are for CTF Cell Reconfiguarton*/
   U8                ctfReCfgType;              /*!< Type of CTF Reconfiguration. 0 - MAJOR RECONFIG 1 - MINOR RECONFIG */
   Bool              bwCfgPres;
   Bool              txCfgPres;
   Bool              phyCellIdPres;
   U8                phyCellId;
   CtfBwCfgInfo      bwCfg;                     /*!<i Bandwidth onfiguration */
   CtfTxSchemeCfg    txCfg;                     /* !< Basic transmossion Scheme Configuration[36.300, 5.1.1] */
   CtfAntennaCfgInfo antennaCfg;                /* !< Antenna Configuration */

}YsPicoSpecific;


struct ysCellCb
{
   CmLteCellId     cellId;                      /*!< Cell ID */
   CtfCellCfgInfo  cellCfg;                     /* Cell configuration */
   U8              dlBw;
   U8              ulBw;
   CmLteTimingInfo timingInfo;                  /* Timing information */
   YsTfuSapCb      *tfuSap;                     /* TFU SAP Control Block */
   YsTfuSapCb      *schTfuSap;                  /* scheduler's TFU SAP Control Block */
   YsUeListCb      ueLstCb;                   
   YsTxMsgInfo     txMsgInfo[YS_NUM_SUB_FRAMES];/* Used for storing MAC 
                                                CntrlReq/DatReq pointer */
#if 0
   YsPrachCb       prachCb;                     /* PRACH Control Block */
   YsSrCb          srCb;                        /* Sceduling Request Control 
                                                   Block */
   YsCqiCb         cqiCb;
#endif
   Pst             peerPst;

   State           phyState;                    /* L1 PHY state */
#ifndef NCCE_FIX
   U8              nCceInfo[YS_NUM_SUB_FRAMES];
#endif

      /* ys005.102 : Adding the vendor specific parameter support */
#ifdef CTF_VER3
   YsPicoSpecific  vendorParams ; /*!< Vendor Specific Parameter */
#endif

};   
   
/*********************************************/
/** 
  * Global Control block for Convergence Layer
  */
struct ysCb
{
   TskInit         ysInit;                         /* Task Init info */
   S16             trcLen;                         /* trace length */
   YsCtfSapCb      ctfSap;                         /* CTF SAP Control Block */
#ifdef YS_LTE_PAL   
   YsTfuSapCb      tfuSap;                         /* TFU SAP Control Block */
   YsTfuSapCb      schTfuSap;                      /* scheduler's TFU SAP Control Block */
   YsCellCb        cellCb;                         /* Cell configuration */   
#else /* YS_LTE_PAL */
   YsTfuSapCb      **tfuSapLst;                    /* TFU SAP Control Block */
   YsCellCb        *cellCfgLst[YS_NUM_LOG_CELLS];  /* Cell configuration list */
#endif /* YS_LTE_PAL */
   Txt             apb[10000];                     /* print buf */
   YsGenCfg        genCfg;                         /* general config */
#ifdef YS_PICO
   CmLteCellId     cellId;                         /*!< Cell ID */
#endif /* YS_PICO */   
   CmTqCp          tmrTqCp;  
   CmTqType        tmrTq[YS_TQ_SIZE];
   CmTimer         tmr;
#ifdef YS_LTE_PAL   
#ifndef SS_CAVIUM   
   U32             sockfd;
#endif /* SS_CAVIUM */
#ifdef LTE_PAL_ENB
   Bool            ttiReady;   
#endif
#endif /* YS_LTE_PAL */
};

/* Declaration for YsCb */
EXTERN YsCb ysCb;

#ifdef YS_PICO
#ifdef LTE_TDD
EXTERN YsPrachTddCfgInfo ysPrachTddCfgDb[YS_NUM_PRACH_TDD_CFG];
EXTERN YsPrachTddMapLst ysPrachTddMapLstDb[YS_NUM_PRACH_TDD_CFG][YS_NUM_TDD_SF_CFG];
#else /* LTE_TDD */
EXTERN YsPrachFddCfgInfo ysPrachFddCfgDb[YS_NUM_PRACH_FDD_CFG];
#endif /* LTE_TDD */
EXTERN Bool               ysPrachPresDb[YS_NUM_PRACH_PRES_ARR];
EXTERN YsSrCfgInfo        ysSrCfgDb[YS_NUM_SR_CFG];
EXTERN YsSrsCfgInfo       ysSrsCfgDb[YS_NUM_SRS_CFG];
EXTERN YsCqiPmiCfgIdxInfo ysCqiPmiCfgDb[YS_NUM_CQI_CFG];
#ifdef LTEMAC_MIMO
EXTERN YsRiCfgIdxInfo ysRiCfgDb[YS_NUM_RI_CFG];
#endif
EXTERN YsCqiPmiRiMap      ysCqiPmiRiMapDb[YS_NUM_TRANS_MODE];
#endif /* YS_PICO */

EXTERN S16 ysActvInit ARGS((Ent entity, Inst inst, Region 
       region, Reason reason));
EXTERN S16 ysActvTsk ARGS((Pst *pst, Buffer *mBuf));

EXTERN Void ysGetSId ARGS((SystemId *s));

EXTERN S16 ysLMMStaInd ARGS((
U16 category,
U16 event,
U16 cause,
YsUstaDgn *dgn
));

EXTERN Data * ysUtlMalloc ARGS((
Size               size
));

EXTERN Void ysUtlDeAlloc ARGS((
Data               *buf,
Size               size
));

EXTERN S16 ysUtlAllocEventMem ARGS((
Ptr       *memPtr,
Size      memSize
));

EXTERN S16 ysUtlFreeEventMem ARGS((
Ptr       memPtr
));

EXTERN YsCellCb *ysUtlGetCellCfg ARGS((
CmLteCellId    cellId 
));

EXTERN YsUeCb *ysUtlGetUe ARGS((
YsCellCb        *cellCb,
CmLteRnti       ueId
));

PUBLIC S16 ysUtlDelCellCfg ARGS((
CmLteCellId    cellId
));

PUBLIC S16 ysUiChkAndGetCtfSap ARGS((
SpId       spId,
YsCtfSapCb **ctfSapCb
));

EXTERN S16 ysUtlDeAllocUeCb ARGS((
YsCellCb        *cellCb,
YsUeCb          *ueCb
));

#ifdef YS_LTE_PAL   
EXTERN S16 ysPalInitTti ARGS ((
Void
));

EXTERN S16 ysPalDeinitTti ARGS ((
Void
));

EXTERN S16 ysPalPrcCntrlReq ARGS((
YsCellCb        *cellCb,
TfuCntrlReqInfo *cntrlReq
));

EXTERN S16 ysPalPrcDatReq ARGS((
YsCellCb        *cellCb,
TfuDatReqInfo   *datReq
));

EXTERN S16 ysPalPrcRecpReq ARGS((
YsCellCb        *cellCb,
TfuRecpReqInfo  *recpReq
));

#ifndef LTE_PAL_ENB
EXTERN S16 YsUiTfuRaReqInd ARGS((
Pst             *pst,
SpId            spId,
TfuRaReqIndInfo *raReqInd
));

EXTERN S16 YsUiTfuHqInd ARGS((
Pst             *pst,
SpId            spId,
TfuHqIndInfo    *hqInd
));

EXTERN S16 YsUiTfuSrInd ARGS((
Pst             *pst,
SpId            spId,
TfuSrIndInfo    *srInd
));

EXTERN S16 YsUiTfuDatInd ARGS((
Pst             *pst,
SpId            spId,
TfuDatIndInfo   *datInd
));

EXTERN S16 YsUiTfuTimingAdvInd ARGS((
Pst                 *pst,
SpId                spId,
TfuTimingAdvIndInfo *taIndInfo
));
#endif

EXTERN S16 ysPalUtlSetTfuMsg ARGS((
YsCellCb *cellCb,
Void      *tfuMsg,
Event     event,
CmLteTimingInfo *timingInfo
));

#ifdef LTE_PAL_ENB
EXTERN Void ysPalHdlTtiInd ARGS((
CmLteTimingInfo *timingInfo
));

#ifdef SS_CAVIUM
EXTERN Void ttiHdlr (Void);
#endif /* SS_CAVIUM */
#endif /* LTE_PAL_ENB */

EXTERN Void ysPalHdlDlMsg ARGS((
CmLteTimingInfo *timingInfo
));

#ifndef SS_CAVIUM
EXTERN S16  ysPalInitRcvrTsk ARGS ((Void));
EXTERN S16  ysPalInitTtiTmrTsk ARGS ((Void));
EXTERN S16  ysPalSend2Peer ARGS(( Buffer *mBuf, int type));
#endif /* SS_CAVIUM */

#endif /* YS_LTE_PAL */

EXTERN S16 YsRecvMsg ARGS((Void *buf));

EXTERN Void ysUtlFreeDatReq ARGS ((TfuDatReqInfo   *datReq));

/* ys004.102:  startDebug removed */

EXTERN Void ysPrcTmrExpiry ARGS((Ptr cb, S16 tmrEvnt));

#ifndef NOFILESYS
EXTERN S16  ysInitCfg ARGS((Void));
#endif

EXTERN S16 YsUiTfuBndCfm ARGS((Pst* pst, SuId suId, U8 status));
EXTERN S16 YsUiTfuSchBndCfm ARGS((Pst* pst, SuId suId, U8 status));
EXTERN S16 YsUiTfuRaReqInd ARGS((Pst * pst, SuId suId, TfuRaReqIndInfo * raReqInd));
EXTERN S16 YsUiTfuUlCqiInd ARGS((Pst * pst, SuId suId, TfuUlCqiIndInfo * ulCqiInd));
EXTERN S16 YsUiTfuHqInd ARGS((Pst * pst, SuId suId, TfuHqIndInfo *hqInd));
EXTERN S16 YsUiTfuSrInd ARGS((Pst * pst, SuId suId, TfuSrIndInfo * srInd));
EXTERN S16 YsUiTfuDlCqiInd ARGS((Pst * pst, SuId suId, TfuDlCqiIndInfo * dlCqiInd));
EXTERN S16 YsUiTfuDatInd ARGS((Pst * pst, SuId suId, TfuDatIndInfo * datInd));
EXTERN S16 YsUiTfuCrcInd ARGS((Pst * pst, SuId suId, TfuCrcIndInfo * crcInd));
EXTERN S16 YsUiTfuTimingAdvInd ARGS((Pst * pst, SuId suId, TfuTimingAdvIndInfo * timingAdvInd));
EXTERN S16 YsUiTfuTtiInd ARGS((Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd));
EXTERN S16 YsUiTfuSchTtiInd ARGS((Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd));
EXTERN S16 YsUiCtfBndCfm ARGS((Pst* pst, SuId suId, U8 status));
EXTERN S16 YsUiCtfCfgCfm ARGS((Pst* pst, SuId suId, CtfCfgTransId transId, U8 status));

EXTERN S16 ysUtlAllocEventMem1 ARGS((Ptr  *memPtr,Size memSize));
EXTERN Void postToApp ARGS((Buffer *mBuf, U8 radioType, U8 direction, U8 rntiType,
                            U16 rnti,U16 ueid, U16   subframe,
                            U8  isPredefinedData, U8 retx, U8 crcStatus));

#ifdef YS_WIRESHARK_LOG
EXTERN Void ysTrillWiresharkMsg ARGS ((Buffer *mBuf, U8 radioType, U8 direction, U8 rntiType,
                                       U16  rnti, U16 ueid, U16 subframe,  U8 isPredefinedData,
                                       U8 retx,  U8 crcStatus));
EXTERN int ysInitLogWireless ARGS ((Void));
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __YS_X__ */

/********************************************************************30**
  
         End of file:     ys.x@@/main/2 - Thu Dec  2 02:27:13 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---           sgm             1. eNodeB 1.2 release
/main/2      ys003.102     pkd             1.ESINR to CQI Mapping 
/main/2      ys004.102     pmacharla       1.Removed unsed variable startDebug
/main/2      ys005.102     pbyadgi         1. Adding the new structure YsPicoSpecific.
                                           2. Adding the vendor specific parameter support.
*********************************************************************91*/
