

/********************************************************************20**
  
        Name:    LTE RLC file 
    
        Type:    C include file
  
        Desc:    This file contains all the data structures and 
                 prototypes for LTE RLC.
 
        File:    kw.x

        Sid:      kw.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:55 2014
  
        Prg:     N/A 
  
*********************************************************************21*/
/** @file kw.x
@brief RLC Product Structures, prototypes
*/

#ifndef __KWX__
#define __KWX__


/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000371      LTE-RLC
 *
*/
 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @brief Local typedefs */
typedef U16    KwSn;                        /*!< Sequence Number length */
typedef RguDDatIndInfo KwDatIndInfo;
typedef RguDStaIndInfo KwDStaIndInfo;
typedef RguPduInfo KwPduInfo;                 /* kw002.201 : Aligning the structure with RGU */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
typedef struct kwSduSnMap KwSduSnMap;
typedef RguLchMapInfo KwLchMapInfo;
#ifdef LTE_RLC_R9
typedef RgL2MeasUlThrpTimInfo KwL2MeasUlThrpTimInfo;
#endif /* LTE_RLC_R9 */
#endif /*  LTE_L2_MEAS_RLC */


/** @defgroup ummode UM Module Info 
*/

/** @struct KwUmhdr 
UM Header Info */
typedef struct kwUmHdr
{
   U8          fi;                          /*!< Framing Info */
   KwSn        sn;                          /*!< Sequence number */
   U16         numLi;                       /*!< Number of LIs */
   U16         li[KW_MAX_LI];               /*!< Array of LIs */
}KwUmHdr;

/** @struct KwAmhdr 
AM Header Info */
typedef struct kwAmHdr
{
   U8          dc;                          /*!< Data/Control PDU */
   U8          rf;                          /*!< Resegmentation flag */
   U8          p;                           /*!< Poll bit */
   U8          fi;                          /*!< Framing Info */
   U8          e;                           /*!< Extension bit */
   U8          lsf;                         /*!< Last segment flag */
   KwSn        sn;                          /*!< Sequence number */
   U16         so;                          /*!< Segment offset */
   U16         numLi;                       /*!< Number of LIs */
   U16         li[KW_MAX_LI];               /*!< Array of LIs */
}KwAmHdr;

/**
 * @struct KwLchInfo
 * Logical Channel Information
 */
typedef struct kwLchInfo
{
   CmLteLcId       lChId;              /*!< Logical channel Id */
   CmLteLcType     lChType;            /*!< Logical channel type */
}KwLchInfo;

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC

/** @struct KwL2Cntr
 * RLC L2 Counter  */
typedef struct kwL2Cntr
{
   struct
   {
      U32  numActvUe;        /*!< number of active Ue */
      U32  sampOc;           /*!< Total number of sampling occasion */
   }actUe;
   struct
   {
      U32  dLoss;            /*!< Total number of lost packets */  
      U32  posPkts;          /*!< Total number of positively acknowlegded 
                                  packets */
   }uuLoss;
   struct                    /*!< For DL IP throughput */
   {
      U32 volSummation;      /*!< Sum of data in bytes */
      U32 timeSummation;     /*!< Sum of time difference in milli sec*/
   }dlIpThruput;
   struct                    /*!< For UL IP throughput */
   {
      U32 volSummation;      /*!< Sum of data in bytes */
      U32 timeSummation;     /*!< Sum of time difference in milli sec*/
   }ulIpThruput;
}KwL2Cntr;

struct kwSduSnMap
{
   CmLList     lstEnt;
   Bool        failMarked;
   Bool        fullySent;
   U32         sduId;
   U16         numSn;
   U16         snList[KW_MAX_PDU_MAP];
   U16         harqAck;
   U16         reqSent;
   U16         rspRcvd;
};

typedef struct kwSnSduMap
{
   U16         sn;
   CmLteLcId   lChId;              /*!< Logical channel Id */
   U16         numSdu;
#ifdef LTE_RLC_R9
   Bool        isBurstSplitted;    /*!< true: burst for this LCH is splitted */
#endif /* LTE_RLC_R9 */
   KwSduSnMap  *sduList[KW_MAX_LI];
}KwSnSduMap;

typedef struct kwTbSnMap
{
   CmHashListEnt  hlTbEnt;
   U32            tbId;
   U16            prevNumSn;
   U16            numSn;
   KwSnSduMap     snSduMap[RGU_MAX_PDU * RGU_MAX_LC];
}KwTbSnMap;

/** @struct KwL2MeasCb
 * RLC L2 Measurement CB */
typedef struct kwL2MeasCb
{
   U8            measType;                /*!< Bit-wise set measurement types */ 
   U16           numSamples;              /*!< Number of samples to take on numActUe */
   U16           numQci;                  /*!< number of valid qcI */             
   U8            qci[LKW_MAX_QCI];        /*!< list of valid qcI */     
   KwL2Cntr      measData[LKW_MAX_QCI];   /*!< Measurement CB */
#ifdef LTE_RLC_R9
   CmLteRnti     ueId;                    /*!< UE ID (Used only for IP Throughput
                                             in UL/DL */
   CmLteCellId   cellId;                  /*!< UE ID (Used only for IP Throughput
                                             in UL/DL */
   U8            numLcId;                 /*!< Holds the number of LCh for which Ul Ip 
                                             measurement is ON */
   U8            lcId[KW_MAX_LCH_PER_UE]; /*!< Holds the list of LCh for which Ul ip
                                             measurement is ON */
#endif /* LTE_RLC_R9 */
}KwL2MeasCb;

/** @struct KwL2MeasEvtCb
 * RLC L2 Measurement Evt CB */
typedef struct kwL2MeasEvtCb
{
   U32           transId;                /*!< TransId of Measurement Req */
   U32           cbIdx;                  /*!< TransId of Measurement Req */
   CmTimer       l2Tmr;                  /*!< L2 Timer per request */
   TmrCfg        l2TmrCfg;               /*!< Time period of measurement */
   KwL2MeasCb    measCb;                 /*!< Measurement CB */ 
}KwL2MeasEvtCb;

/** @struct KwL2MeasRbCb
 * RLC L2 Measurement Rb CB */
typedef struct kwL2MeasRbCb
{
   U8            measOn;                      /*!< Measurements that are running */ 
   KwL2Cntr      *l2Sts[KW_MAX_L2MEAS_EVT];  /*!< L2 Mesurement statistics */     
}KwL2MeasRbCb;

/** @struct KwL2Cb
 * RLC L2  CB */
typedef struct kwL2Cb
{
   CmHashListCp  qciHlCp;                     /*!< Hashlist of qci */
   CmHashListCp  tbHlCp;                      /*!< Hashlist of TBId to KwTbSnMap */
   U32           tbId;                        /*!< TbId of the tbList */
   KwTbSnMap     *curTbSnMap;                 /*!< Current tbSnMap: in U/AmmProcessSdus */
   U16           kwNumMeas;                   /*!< Number of measurements going on */
   KwL2MeasEvtCb *kwL2EvtCb[LKW_MAX_L2MEAS];  /*!< Pointers to Measurement Cb */
   U8           measOn[LKW_MAX_QCI];          /*!< Measurement on */
   U32           numActUe[LKW_MAX_QCI];       /*!< Measurement on */
}KwL2Cb;

#ifdef LTE_RLC_R9
typedef enum _dlIpThrputState
{
   KW_DL_IPTHRU_RESET = 0,
   KW_DL_IPTHRU_BURST_STARTED,
   KW_DL_IPTHRU_BURST_CONTINUE,
   KW_DL_IPTHRU_BURST_COMPLETED
}DlIpThrputState;

/* Structure to hold parameters for DL/UL ip throughput for a RB */
typedef struct _kwL2MeasIpThruput
{
   EpcTime         timeT2;                  /*!< Time stamp T2(in milli sec)*/
   EpcTime         tempTimeT1;              /*!< Temporary Time stamp T1(in milli sec)*/
   U32             dataVol;                 /*!< Holds volume of new data in bytes
                                              for DL IP throughput */
   DlIpThrputState dlIpThrputSt;            /*!< Holds the state of RbCb */
   KwTbSnMap       *prevTbSnMap;            /*!< Holds the KwTBSnMap for the 1st allocation
                                                 which splits the data burst*/
   U32             ulDataVol;               /*!< Holds volume of new data in bytes
                                              for UL IP throughput */
   U16             count;                   /*!< Holds the number of times DL Data 
                                               Burst is split across a TTI.*/
}KwL2MeasIpThruput;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

typedef struct kwUeKey
{
   CmLteRnti     ueId;                      /*!< UE Id */
   CmLteCellId   cellId;                    /*!< Cell Id */
}KwUeKey;

/** @struct KwCkwSapCb
CKW Sap Conrol Block */
typedef struct kwCkwSapCb
{
   Pst           pst;                       /*!< Service user post structure */
   SpId          spId;                      /*!< Service provider Id */
   SuId          suId;                      /*!< Service user Id */
   U8            state;                     /*!< Sap Status */
   KwCkwCntSts   sts;                       /*!< Statistics */
}KwCkwSapCb;

/** @struct KwKwuSapCb
KWU Sap Conrol Block */
typedef struct kwKwuSapCb
{
   Pst           pst;                       /*!< Service user post structure */
   SpId          spId;                      /*!< Service provider Id */
   SuId          suId;                      /*!< Service user Id */
   U8            state;                     /*!< Sap Status */
   KwKwuSapSts   sts;                       /*!< Statistics */
}KwKwuSapCb;

/** @struct KwRguSapCb
RGU Sap Control Block */
typedef struct kwRguSapCb
{
   Pst           pst;                       /*!< Service user post structure */
   SpId          spId;                      /*!< Service provider Id */
   SuId          suId;                      /*!< Service user Id */
   U8            state;                     /*!< Sap Status */
   CmTimer       bndTmr;                    /*!< Bind Timer */
   U16           bndTmrInt;                 /*!< Timer Interval */
   U8            retryCnt;                  /*!< Bind Retry Count */
}KwRguSapCb;

typedef struct kwUdxUlSapCb
{
   Pst           pst;                       /*!< Service user post structure */
   SpId          spId;                      /*!< Service provider Id */
   SuId          suId;                      /*!< Service user Id */
   U8            state;                     /*!< Sap Status */
   CmTimer       bndTmr;                    /*!< Bind Timer */
   U16           bndTmrInt;                 /*!< Timer Interval */
   U8            retryCnt;                  /*!< Bind Retry Count */
}KwUdxUlSapCb;

typedef struct kwUdxDlSapCb
{
   Pst           pst;                       /*!< Service user post structure */
   SpId          spId;                      /*!< Service provider Id */
   SuId          suId;                      /*!< Service user Id */
   U8            state;                     /*!< Sap Status */
}KwUdxDlSapCb;

typedef struct kwCfgInfo
{
   CmHashListEnt  transHlEnt;
   U32            transId;
   U8             cfgType;
   CkwCfgInfo     *cfgInfo;
   CkwUeInfo      *ueInfo;
   CkwUeInfo      *newUeInfo;
} KwCfgInfo;

typedef struct _kwDlCb
{
   U8            numKwuSaps;                /*!< Number of RLC Data Saps */
   U8            numUdxSaps;                /*!< Number of RLC Data Saps */
   KwKwuSapCb    *kwuDlSap;                   /*!< KWU Sap Control Block */
   KwUdxDlSapCb  *udxDlSap;
   KwRguSapCb    rguDlSap;                    /*!< RGU Sap Control Block */
   CmHashListCp  cellLstCp;                 /*!< Hashlist of CellCb */
   CmHashListCp  ueLstCp;                   /*!< Hashlist of UeCb */
}KwDlCb;

typedef struct _kwUlCb
{
   KwCkwSapCb    ckwSap;                    /*!< CKW Sap Conrol Block */ 
   U8            numKwuSaps;                /*!< Number of RLC Data Saps */
   U8            numUdxSaps;                /*!< Number of RLC Data Saps */
   KwUdxUlSapCb  *udxUlSap;
   KwKwuSapCb    *kwuUlSap;                   /*!< KWU Sap Control Block */
   KwRguSapCb    rguUlSap;                    /*!< RGU Sap Control Block */
   CmHashListCp  cellLstCp;                 /*!< Hashlist of CellCb */
   CmHashListCp  ueLstCp;                   /*!< Hashlist of UeCb */
   CmHashListCp  transIdLstCp;              /*!< Hashlist of cfg trans */
}KwUlCb;


/** @struct KwCb
RLC global control block */
typedef struct _kwCb
{
   TskInit       init;                      /*!< Task Initialization Info */
   KwGenCfg      genCfg;                    /*!< General Configuration Structure */
   KwGenSts      genSts;                    /*!< General Statistics */
   S16           trcLen;                    /*!< Trace Length */
   U8            trcMask;                   /*!< Trace Mask */
   CmTqType      kwTq[KW_TMR_LEN];          /*!< Timer queue */
   CmTqCp        kwTqCp;                    /*!< Timer queue control point */
   union 
   {
      KwUlCb        *ulCb;                   /*!< Ul Control Block */
      KwDlCb        *dlCb;                   /*!< Dl Control Block */
   } u;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwL2Cb        kwL2Cb;                    /*!< Control Block for L2 Measurements in RLC */
#endif /* LTE_L2_MEAS_RLC */
}KwCb;

/* Extern variable declaration */
EXTERN KwCb *kwCb[KW_MAX_RLC_INSTANCES];                           /*!< RLC global control block */

/****************************************************************************
 *                      EXTERN Declarations
 ***************************************************************************/
EXTERN S16 kwGetSId ARGS((SystemId *s));
EXTERN S16 kwTmrExpiry      ARGS(( PTR cb, S16 tmrEvnt ));
EXTERN S16 kwLmmSendTrc ARGS (( KwCb *gCb,Event event, Buffer *mBuf));
/* Activation functions */
EXTERN S16 kwActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));
EXTERN S16 kwStartTmr       ARGS(( KwCb *gCb,PTR cb, S16 tmrEvnt ));
EXTERN S16 kwStopTmr        ARGS(( KwCb *gCb,PTR cb, U8 tmrType ));
EXTERN Bool kwChkTmr        ARGS(( KwCb *gCb,PTR cb, S16 tmrEvnt ));
#ifdef LTE_L2_MEAS_RLC
EXTERN Void kwLmmSendAlarm ARGS (( KwCb *gCb,U16 category, U16 event, 
                                   U16 cause, SuId suId, U32 ueId, U8 qci));
EXTERN S16 KwMiLkwL2MeasReq ARGS (( Pst *pst, KwL2MeasReqEvt *measReqEvt ));
#else /* LTE_L2_MEAS_RLC */
EXTERN Void kwLmmSendAlarm ARGS (( KwCb *gCb,U16 category, U16 event, 
                                   U16 cause, SuId suId, U32 ueId));
#endif /* LTE_L2_MEAS_RLC */



/* TMM Module */
#if 0
EXTERN PUBLIC S16 kwTmmQSdu ARGS ((KwRbCb *rbCb,KwuDatReqInfo *datReqInfo,
                                   Buffer *mBuf));
EXTERN PUBLIC S16 kwTmmSndToLi ARGS ((KwRbCb *rbCb));
#ifdef CCPU_OPT
EXTERN PUBLIC S16 kwTmmRcvFrmLi ARGS ((KwRbCb *rbCb,CmLteRnti tCrnti,
                                       Buffer *pdu));
#else /* CCPU_OPT */
EXTERN PUBLIC S16 kwTmmRcvFrmLi ARGS ((KwRbCb *rbCb,Buffer *pdu));
#endif /* CCPU_OPT */
EXTERN PUBLIC S16 kwTmmReEstablish ARGS ((KwRbCb *rbCb));

/* UMM Module */
EXTERN PUBLIC S16 kwUmmQSdu ARGS ((KwRbCb *rbCb,U32 sduId,Buffer *mBuf));
EXTERN PUBLIC S16 kwUmmProcessSdus ARGS ((KwRbCb *rbCb, KwDatReq *datReq));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
EXTERN S16 kwUmmProcessPdus ARGS((KwRbCb  *rbCb, KwPduInfo *pduInfo,
      KwL2MeasUlThrpTimInfo *ulTimeInfo));
#else /* LTE_RLC_R9 */
EXTERN PUBLIC S16 kwUmmProcessPdus ARGS (( KwRbCb *rbCb,KwPduInfo *pduInfo));
#endif /* LTE_RLC_R9 */
#else /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUmmProcessPdus ARGS (( KwRbCb *rbCb,KwPduInfo *pduInfo));
#endif /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUmmReEstablish ARGS ((CmLteRlcId rlcId, KwRbCb *rbCb));
EXTERN PUBLIC S16 kwUmmDiscSdu ARGS ((KwRbCb *rbCb,U32 sduId));

/* Utility Module */
EXTERN PUBLIC S16 kwUtlRmvSdu ARGS ((CmLListCp *sduQ,KwSdu *sdu,
                                     CmLList *firstNode));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
EXTERN PUBLIC S16 kwUtlEmptySduQ ARGS ((KwRbCb *rbCb, CmLListCp *sduQ));
#else /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUtlEmptySduQ ARGS ((CmLListCp *sduQ));
#endif /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUtlSndDStaRsp ARGS ((KwRbCb *rbCb,S32 bo,S32 estHdrSz,
                                         Bool staPduPrsnt));
EXTERN PUBLIC S16 kwUtlSndCStaRsp ARGS ((KwRbCb *rbCb,S32 bo));
EXTERN PUBLIC S16 kwUtlSndToLi ARGS ((KwDStaIndInfo *staIndInfo));
EXTERN PUBLIC S16 kwUtlRcvFrmLi ARGS ((KwDatIndInfo *datIndInfo));
EXTERN PUBLIC S16 kwUtlShutDown ARGS ((void));
EXTERN PUBLIC S16 kwUtlCalcLiForSdu ARGS ((U16 numLi,MsgLen msgLen,S16 *pduSz));
EXTERN Void kwUtlFreeRbCb ARGS (( KwRbCb *rbCb));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
EXTERN S16 kwUtlHdlL2TmrExp   ARGS (( KwL2MeasEvtCb *measEvtCb));
EXTERN S16 kwUtlSndL2MeasCfm  ARGS (( KwL2MeasEvtCb *measEvtCb));
EXTERN S16 kwUtlSndL2MeasNCfm ARGS (( KwL2MeasReqEvt *measReqEvt, 
                                      KwL2MeasCfmEvt *measCfmEvt)) ;
EXTERN S16 kwUtlSndDiscSduCfm ARGS (( KwRbCb *kwRbCb, U32    sduId));
EXTERN S16 kwUtlUpdSduSnMap   ARGS (( KwRbCb *kwRbCb, KwSdu  *sdu, 
                                      KwDatReq *kwDatReq, Bool   lastSegSent));
EXTERN S16 kwUtlProcHarqInd  ARGS (( RguHarqStatusInd *staInd, KwUeCb *ueCb, 
                                     U8 tbIdx));
#ifdef LTE_RLC_R9
EXTERN S16 kwUtlValidateL2Meas ARGS((KwL2MeasReqEvt *measReqEvt, 
                                     KwL2MeasCfmEvt *measCfmEvt, 
                                     CmLteLcId *lChId, U8 *numLCh));
#else /* LTE_RLC_R9 */
EXTERN S16 kwUtlValidateL2Meas ARGS((KwL2MeasReqEvt *measReqEvt,
                                     KwL2MeasCfmEvt *measCfmEvt));
#endif /* LTE_RLC_R9 */
EXTERN Void kwUtlPlcMeasDatInL2Sts ARGS((KwL2Cntr *measData, 
                                         KwL2MeasRbCb *rbL2Cb ,U8  measType));
#ifdef LTE_RLC_R9
EXTERN Void kwUtlResetKwRbL2Meas ARGS(( KwRbCb  *rbCb ));
#endif /* LTE_RLC_R9 */
#endif /*  LTE_L2_MEAS_RLC */

/* TMR Module */
EXTERN S16 kwStartTmr       ARGS(( PTR cb, S16 tmrEvnt ));
EXTERN S16 kwStopTmr        ARGS(( PTR cb, U8 tmrType ));
EXTERN Bool kwChkTmr        ARGS(( PTR cb, S16 tmrEvnt ));

/* AMM Module */
EXTERN S16 kwAmmProcessSdus     ARGS(( KwRbCb *rbCb, KwDatReq *kwDatReq ));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
EXTERN S16 kwAmmProcessPdus ARGS((KwRbCb  *rbCb, KwPduInfo  *pduInfo,
KwL2MeasUlThrpTimInfo *ulTimeInfo));
#else /* LTE_RLC_R9 */
EXTERN S16 kwAmmProcessPdus     ARGS(( KwRbCb *rbCb, KwPduInfo *pduInfo));
#endif /* LTE_RLC_R9 */
#else /* LTE_L2_MEAS_RLC */
EXTERN S16 kwAmmProcessPdus     ARGS(( KwRbCb *rbCb, KwPduInfo *pduInfo));
#endif /* LTE_L2_MEAS_RLC */
EXTERN S16 kwAmmDiscSdu         ARGS(( KwRbCb *rbCb, U32 sduId));
EXTERN S16 kwAmmReEstablish     ARGS(( CmLteRlcId rlcId, KwRbCb *rbCb));
EXTERN Void kwAmmReOrdTmrExp    ARGS(( KwRbCb *rbCb));
EXTERN Void kwAmmStaProTmrExp   ARGS(( KwRbCb *rbCb));
EXTERN Void kwAmmPollRetxTmrExp ARGS(( KwRbCb *rbCb));

/* CFG Module */
EXTERN S16 kwCfgAddRb ARGS (( CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgReCfgRb ARGS (( CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelRb ARGS (( CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelUe ARGS (( CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgReEstRb ARGS (( CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelCell ARGS (( CmLteCellId cellId, CkwEntCfgInfo *entCfg, 
                                CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgUeIdChng ARGS (( CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo, 
                                 CmStatus  *status));

/* LMM Module */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
EXTERN Void kwLmmSendAlarm ARGS (( U16 category, U16 event, U16 cause, 
                                   SuId suId, U32 ueId, U8 qci));
EXTERN S16 KwMiLkwL2MeasReq ARGS (( Pst *pst, KwL2MeasReqEvt *measReqEvt ));
#else /* LTE_L2_MEAS_RLC */
EXTERN Void kwLmmSendAlarm ARGS (( U16 category, U16 event, U16 cause, 
                                   SuId suId, U32 ueId));
#endif /* LTE_L2_MEAS_RLC */

/* DBM Module */
EXTERN S16 kwDbmInit ARGS ((Void));

EXTERN S16 kwDbmDeInit ARGS ((Void));

EXTERN S16 kwDbmCreateUeCb ARGS ((
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUeCb            **ueCb       /* UE Control Block */
));

EXTERN S16 kwDbmFetchUeCb ARGS ((
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUeCb            **ueCb       /* UE Control Block */
));

EXTERN S16 kwDbmDelUeCb ARGS ((
KwUeCb            *ueCb,       /* UE Identifier */
Bool              abortFlag    /* Abort Flag */
));

EXTERN S16 kwDbmDelAllUe ARGS ((Void));

EXTERN S16 kwDbmCreateCellCb ARGS ((
CmLteCellId       cellId,     /* Cell Identifier */
KwCellCb          **cellCb     /* UE Control Block */
));

EXTERN S16 kwDbmFetchCellCb ARGS ((
CmLteCellId       cellId,     /* Cell Identifier */
KwCellCb          **cellCb     /* Cell Control Block */
));

EXTERN S16 kwDbmDelCellCb ARGS ((
KwCellCb          *cellCb     /* Cell Control Block */
));

EXTERN S16 kwDbmDelAllCell ARGS ((Void));

EXTERN S16 kwDbmFetchRbCbForUi ARGS ((
CmLteRlcId        rlcId,      /* RLC Identifier */
KwRbCb            **rbCb       /* RB Cb */
));

EXTERN S16 kwDbmFetchRbCbForLi ARGS ((
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
CmLteLcId         lcId,       /* Logical channel instance */
U8                dir,        /* Direciotn DL/UL */
KwRbCb            **rbCb      /* RB Cb */
));

EXTERN S16 kwDbmDelAllRb ARGS ((
RbCb            **rbCbLst,  /* RB Cb list */
U8                numRbCb     /* Number of rbCbs */
));

EXTERN S16 kwDbmShutdown ARGS ((Void));

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
EXTERN S16 kwDbmDelMeasEvtCb ARGS((Void));
#endif /* LTE_L2_MEAS_RLC */

/* Activation functions */
EXTERN S16 kwActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 kwActvTsk ARGS ((
Pst *pst,              /* pst structure */
Buffer *mBuf            /* message buffer */
));
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __KWX__ */

  
/********************************************************************30**
  
         End of file:     kw.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:55 2014
  
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
/main/1      ---       nm  1. Initial release.
/main/2      ---       nm  1. LTERLC Release 2.1
/main/3      kw002.201 vp  1. Patch for optimization,fixes for multi-region
                              and retransmission.
/main/4      kw003.201 vp  1. Fixes for re-segmentation, segement offset
                               value and optimization 
/main/5      kw005.201 ap  1. Updated KwRbCb for statistics calculation.
                           2. Removed compilation warning.
                           3. Added cellId and ueId KwL2MeasCb
                           4. Added declaration for kwUtlValidateL2Meas.
*********************************************************************91*/

