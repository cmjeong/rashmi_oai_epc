

/**********************************************************************
 
    Name:   LTE UE Simulator  layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE UE Simulator
 
    File:   ue.x 
 
    Sid:      ue.x@@/main/1 - Sun Mar 28 22:59:20 2010
 
    Prg:    vp
 
**********************************************************************/
 
 
#ifndef __UEX__
#define __UEX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


EXTERN  U8 rlcAmFxdHdr; /* first 6 bits in AM header */
/*U8  rlcAmFxdHdr = 0x20;  first 6 bits in AM header */

/* struct RLC RB */
typedef struct rbCb
{
   CmLListCp  sduLst;
   U8  rbId;        /* Radio Bearer Id*/
   U8  lcId;        /* Logical Channel Id */
   U16 pdcpSn;      /* PDCP Seq Num */
   U16 rcvdPdcpSn;  /* PDCP Seq Num of the last received PDU*/

   /* ue002.101: Additional defines for RLC UM mode support */
   U16 rcvd_um_seq; /* Seq number received by UE for UM mode */
   U16 cur_um_seq;  /* Current UM mode Seq Num for UL transmission */
   U16 rcvd_am_seq; /* Seq number received by UE for AM mode*/
   U16 cur_am_seq;  /* Current AM mode Seq Num for UL transmission */
   S32 bo;
   Buffer *partialSdu;/* Any buffer that needs to be sent */
   Bool    ackToBeSent; /* Set to TRUE if poll bit is received */
   Buffer *mBuf; 
} RbCb;

typedef struct ueRlcSdu
{
   CmLList   lstEnt;
   MsgLen    len;
   Buffer    *mBuf;
   Bool      isSegmented;
} UeRlcSdu;

/* ue002.101: Additional defines for RLC UM mode support path */
typedef struct ueRlcUmHdr
{
   U8          fi;                          /*!< Framing Info */
   U16         sn;                          /*!< Sequence number */
   U16         numLi;                       /*!< Number of LIs */
   U16         li[UE_RLC_MAX_LI];           /*!< Array of LIs */
}UeRlcUmHdr;   
typedef struct ueRlcAmHdr
{
   U8          dc;                  /*!< Data/Control PDU */
   U8          rf;                  /*!< Resegmentation flag */
   U8          p;                   /*!< Poll bit */
   U8          fi;                  /*!< Framing Info */
   U8          e;                   /*!< Extension bit */
   U16         sn;                  /*!< Sequence number */
   U8          lsf;                 /*!< Last segment flag */
   U16         so;                  /*!< Segment offset */
   U16         numLi;               /*!< Number of LIs */
   U16         li[UE_RLC_MAX_LI];   /*!< Array of LIs */
} UeRlcAmHdr;

/* struct RLC Context */
typedef struct ueRlcCxt
{
   RbCb rbArr[UE_NUM_RLC_RB_PER_UE];  /* 4 RBs of the UE: one to map with ccch and
                                     one for each of SRB1, SRB2, DRB */
   U8   snLen; /* SN Length 5 bits or 10 bits (Configure 1 or 2 respectively) */
} UeRlcCxt;

/* struct MAC LC */
typedef struct lcCb
{
   U8               lcId;
} LcCb;

/* ue008.101: Added new structure rarGrantInfo */
typedef struct rarGrantInfo
{
  Bool grantSts; /* TRUE => valid grant; FALSE => invalid grant */
  U32 tbSz; /* holds the TB size calculated from the grant 
               recieved through RAR PDU */
  CmLteTimingInfo tmInfo; /* Time at which the TB has to be sent out on this grant */             
}RarGrantInfo;


typedef struct ueSimMacSubHdr
{
   U8            lcId;
   MsgLen        len;
} UeMacSubHdr;

typedef struct ueMacPdu
{
   U8            numSubHdrs;
   UeMacSubHdr   subHdrs[UE_SIM_MAX_SUBHDRS];
} UeMacPdu;

typedef struct ueMacUlSf
{
   TfuDatIndInfo   *datInd;
   TfuSrIndInfo    *srInd;
   TfuHqIndInfo    *hqInd;
/* ue002.101: Changes to support MSPD CL */
   TfuDlCqiIndInfo *dlCqiInd;
} UeMacUlSf;

/* struct MAC Context */
typedef struct ueMacCxt
{
   CmLList    rachLnk;
   Bool       reportBsr; /* Set to TRUE if BSR needs to be sent */
   Bool       srReq;
   U8         preambleId;
   Buffer     *msg3;
   /* ue008.101: Added new element grantInfo */
   RarGrantInfo grantInfo;
/* ue003.101: Added TA feature */
#ifdef TA_NEW
   S32        remTa;          /* remaining timing adjustment required */
   Bool       ulSyncStatus;   /* UL synchronization status */
   CmTimer    taAlgntmr;      /* Timing Alignment timer */
   CmTimer    taChngtmr;      /* TA Change timer */
   CmTimer    taAppltmr;      /* TA Apply timer */
   U8         ta;             /* TA as indicated by eNodeB */
                              /* remTa and ta values are in multiples of 16Ts */
#endif
} UeMacCxt;


typedef struct harqOffset
{
   U8    sfnOffset;        /*!< SFN offset with respect to expected
                                UL data reception time */
   U8    subframe;         /*!< Subframe number */

} HarqOffset;

/* ue002.101: Additional defines for MSPD CL */
typedef struct ueMsSrCfgInfo
{
   U8    srCfgIndex;             /*!< SR Config Index, (0..154) */
   U8    srPeriod;               /*!< SR periodicity */
   U8    srSfOffSet;             /*!< SR subframe ofset */
}UeMsSrCfgInfo;

typedef struct ueMsSrsCfgInfo
{
   U16    srsCfgIndex;            /*!< SRS Config Index, (0..636) */
   U16    srsPeriod;              /*!< SRS periodicity */
   U16    srsSfOffSet;            /*!< SRS subframe ofset */
}UeMsSrsCfgInfo;

typedef struct ueMsCqiPmiCfgIdxInfo
{
   U16    cqiPmiCfgIndex;         /*!< Cqi-PMI Config Index, (0..315) */
   U8    cqiPeriod;              /*!< Cqi periodicity */
   U8    cqiSfOffSet;            /*!< Cqi subframe ofset */
}UeMsCqiPmiCfgIdxInfo;

typedef struct ueRiCfgIdxInfo
{
  U16  riCfgIndex;
  U8   mRi;
  S16  riOffset;
} UeRiCfgIdxInfo;

#ifdef YS_MSPD

/* Data Strcutures */
typedef struct uePhyRxSdu
{
   CmLList     lnk;
   PRXSDUIND   rxSduInd;
   MsgLen      sduLen;
} UePhyRxSdu;

/*Data Strcutures*/
typedef struct ueDlEncL1Msgs
{
   TfuDatReqInfo   *tfuDatReqInfo;   /* Tfu Dat Indication Information*/
   TfuCntrlReqInfo   *tfuCntrlReqInfo;   /* Tfu Crc Indication Information*/
   TfuRaReqIndInfo *rachIndInfo;     /* Tfu Rach Indication Information */
   TfuUlCqiIndInfo *ulCqiIndInfo;    /* Tfu UL CQI Information */
   TfuDlCqiIndInfo *dlCqiIndInfo;    /* Tfu DL CQI Information */
   TfuHqIndInfo    *harqIndInfo;     /* Tfu Harq Indication Information */
   TfuSrIndInfo    *srIndInfo;       /* Tfu SR Indication Information */
   PTR              rxVector;        /* RxVector for current subframe */
} UeDlEncL1Msgs;

typedef struct ueUlEncL1Msgs
{
   TfuDatIndInfo   *tfuDatIndInfo;   /* Tfu Dat Indication Information*/
   TfuDlCqiIndInfo *dlCqiIndInfo;    /* Tfu DL CQI Information */
   TfuHqIndInfo    *harqIndInfo;     /* Tfu Harq Indication Information */
   TfuSrIndInfo    *srIndInfo;       /* Tfu SR Indication Information */
   TfuRaReqIndInfo *rachIndInfo;     /* Tfu Rach Indication Information */

   PGENMSGDESC     txVector;
   CmLListCp       txSduLst;     /* List of TXSDUREQ */
   Bool            txVectorSent; /* To check whether start req has sent or not */
} UeUlEncL1Msgs;
#endif /* YS_MSPD */

/* struct ue */
typedef struct ueCb
{
   CmLList  ueLstEnt;
   U16      rnti;      /* C-RNTI */
   U16      cellId;    /* Cell to which this Ue belongs to */
   S8       wait;
   U16      ueId;
#ifdef ENB_PERF_MEAS
   U8       ueAppState; /* Ready To generate UL Load */
#endif
   /* ue008.101: Added new element isDel */
   U8       isDel;
   U8       state;     /* State of UE */
   UeRlcCxt rlc;       /* RLC context of the UE */
   UeMacCxt mac;       /* MAC context of the UE */
   U8       drbEst;
/* ue003.101: Dedicated bearer support */
   U8       dedDrbEst;
   U16      szOfLastPkt;
/* ue002.101: Additional defines for MSPD CL */
   UeMsSrCfgInfo          *srCfgInfo;
   UeMsSrsCfgInfo         *srsCfgInfo;
   UeMsCqiPmiCfgIdxInfo   *cqiCfgInfo;
   UeRiCfgIdxInfo         *riCfgInfo;
#ifdef YS_MSPD 
   NhuPhysicalConfigDedicated  rrcCfg;
#endif /* YS_MSPD*/
}UeCb;


typedef struct cell
{
   U8            bw;
   U8            dlUlCfg;
   U8            preambleId;
   CmLListCp     rachLst;
   CmLteCellId     cellId;                      /*!< Cell ID */
   U16           startRnti;
   UeCb          ueArr[UE_NUM_PER_CELL];
   UeMacUlSf     ueMacUlSf[10];
/* ue002.101: Additional defines for MSPD CL */
#ifdef YS_MSPD
   CmLteTimingInfo timingInfo;                  /* Timing information */
   UeDlEncL1Msgs   dlEncL1Msgs[MAX_SUBFRAMES];  /* L1 DL encoded message 
                                                      buffer */
   UeUlEncL1Msgs   ulEncL1Msgs[MAX_SUBFRAMES];  /* L1 UL encoded message 
                                                      buffer */
   Pst            pst;                          /* Post info associated with SAP */
   SuId           suId;                         /* SuId associated with SAP */
#endif /* YS_MSPD*/
/* ue003.101: Added for TA feature */
#ifdef TA_NEW
   CmLteTimingInfo     crntTime;            /*!< Crnt Time updated as per TTI Ind */ 
   CmTqCp              tmrTqCp;             /*!< Refresh Timer Task Queue
                                             * Control Point */
   CmTqType            tmrTq[UE_MAX_TMR_Q]; /*!< Timer Task Queue */
#endif
}CellCb;


EXTERN CellCb cellArr[UE_NUM_CELL];
EXTERN UeCb   ueArr[UE_NUM_CELL][UE_NUM_PER_CELL];

/* ue002.101: Additional defines for MSPD CL */
/* ue008.101: Fixed compilation Warnings */
EXTERN U16  YS_PORT_ENB[];
EXTERN U16  YS_PORT_UE;
#ifdef YS_MSPD
EXTERN U8   YS_IP_ADDR_ENB[];
#endif
EXTERN U8   YS_IP_ADDR_UE[];


typedef struct ueMacCeSubHdr
{
   CmLList  subHdrLstEnt;
   U8       lcId;
} UeMacCeSubHdr;

typedef struct ueMacSdu
{
   CmLList  sduLstEnt;
   U8       lcId;
   MsgLen   len;
   Buffer   *mBuf;
} UeMacSdu;

typedef struct ueMacDecPdu
{
   CmMemListCp memCp;
   CmLListCp   ceLst;
   CmLListCp   sduLst;
   struct 
   {
      U8    contResId[6];
      U8    ta;
   }ces;
} UeMacDecPdu;

typedef struct ueMacEncPdu
{
   CmMemListCp memCp;
   MsgLen      schdTbSz;
   CmLListCp   sduLst;
   U16         bitMask;
   struct
   {
      U16   cRnti;
      U8    phr;
      union 
      {
         U8    truncBsr;
         U8    shortBsr;
         struct
         {
            U8    bs1;
            U8    bs2;
            U8    bs3;
            U8    bs4;
         }longBsr;
      }bsr;
   } ces;
} UeMacEncPdu;

typedef struct ueMacRarSdu
{
   CmLList  rarSduLstEnt;
   U8       rapId;
   struct
   {
      U8    iMcs;
      U8    rbStart;
      U8    numRbs;
   }ulGrnt;
   U16      tmpCRnti;
} UeMacRarSdu;

typedef struct ueMacDecRarPdu
{
   CmMemListCp memCp;
   CmLListCp   rarSduLst;
} UeMacDecRarPdu;

typedef struct ueMacMUXSubHdr
{
   U8 shLen;  
   U8 shData[UE_MAC_MAX_PDU_SUB_HDR_LEN];
} UeMacMUXSubHdr;
/* ue010.101: Enhanced measurement feature. */
typedef struct ueEnbTAC
{
U16   ys_enb1_tac;
U16   ys_enb2_tac;
U16   ys_enb3_tac;
U16   ys_enb4_tac;
U16   ys_enb5_tac;
}UeEnbTAC;

typedef struct ueEnbECI
{
U16   ys_enb1_eci;
U16   ys_enb2_eci;
U16   ys_enb3_eci;
U16   ys_enb4_eci;
U16   ys_enb5_eci;
}UeEnbECI;

typedef struct ueEnbMcc
{
U32   ys_enb1_mcc;
U32   ys_enb2_mcc;
U32   ys_enb3_mcc;
U32   ys_enb4_mcc;
U32   ys_enb5_mcc;
}UeEnbMcc;

typedef struct ueEnbMnc
{
U32   ys_enb1_mnc;
U32   ys_enb2_mnc;
U32   ys_enb3_mnc;
U32   ys_enb4_mnc;
U32   ys_enb5_mnc;
}UeEnbMnc;

typedef struct ueEnbcgi
{
U16   ys_enb1_cgi;
U16   ys_enb2_cgi;
U16   ys_enb3_cgi;
U16   ys_enb4_cgi;
U16   ys_enb5_cgi;
}UeEnbcgi;

typedef struct ueEnbRsrp
{
U16   ys_enb1_rsrp;
U16   ys_enb2_rsrp;
U16   ys_enb3_rsrp;
U16   ys_enb4_rsrp;
U16   ys_enb5_rsrp;
}UeEnbRsrp;

typedef struct ueEnbRsrq
{
U16   ys_enb1_rsrq;
U16   ys_enb2_rsrq;
U16   ys_enb3_rsrq;
U16   ys_enb4_rsrq;
U16   ys_enb5_rsrq;
}UeEnbRsrq;

typedef struct ueNetWorkParam
{
UeEnbTAC       ueenbtac;    
UeEnbECI       ueenbeci;
UeEnbMcc       ueenbmcc;
UeEnbMnc       ueenbmnc;
UeEnbcgi       ueenbcgi;
UeEnbRsrp      ueenbrsrp;
UeEnbRsrq      ueenbrsrq;
}UeNetWorkParam;

/* ue008.101: Removed variable padArr to fix compilation warning */ 

typedef U32 UeMacTbSzTbl[UE_MAC_NUM_ITBS][UE_MAC_MAX_NUM_RB];
EXTERN UeMacTbSzTbl ueMacTbSzTbl;

typedef U32 UeMacBsrTbl[UE_MAC_MAX_BSR_INDEX];
EXTERN UeMacBsrTbl ueMacBsrTbl;

typedef U8  UeMacIMcsTbl[UE_MAC_NUM_IMCS];
EXTERN UeMacIMcsTbl ueMacIMcsTbl;

/* All the services provided by different layers */
/* MAC layer related services */
EXTERN S16 ueMacInit ARGS((CellCb *));
/* ue007.101: Deinitializing mac */
EXTERN S16 ueMacDeInit ARGS((CellCb *));
EXTERN S16 RgLiTfuCntrlReq ARGS((Pst *  pst, SpId spId, 
                                 TfuCntrlReqInfo * cntrlReq));
EXTERN S16 RgLiTfuDatReq ARGS((Pst * pst, SpId spId, TfuDatReqInfo * datReq));
EXTERN S16 RgLiTfuTtiInd ARGS((Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd));
EXTERN Void ueMacRachReq ARGS((CellCb *cell, UeCb *ueCb, Buffer *msg3));

/* RLC related services */
EXTERN S16 ueRlcDatInd ARGS((UeCb *ueCb, U8 lcId, Buffer *pdu));
EXTERN S16 ueRlcGetBo ARGS((UeCb *ueCb, U32 *lcg0, U32 *lcg1, U32 *lcg2,
                            U32 *lcg3));
EXTERN S16 ueRlcDatReq ARGS((UeCb *ueCb, U8 lcId, Buffer *mBuf));

EXTERN S16 ueRlcGetPdu ARGS((UeCb *ueCb, MsgLen size, Buffer **pdu, U8 *lcId));

/* PAL related services */
/* ue003.101: Added for paging support */
EXTERN S16 uePalDatInd ARGS((CmLteTimingInfo tmInfo, UeCb *ueCb, Buffer *pdu));
EXTERN S16 uePalAddSr ARGS((CmLteTimingInfo tmInfo, UeCb *ueCb));
EXTERN S16 ueUtlFndUe ARGS((CellCb *cell,U16 rnti, UeCb **ueCb));

/* RRC related services */
EXTERN S16 ueRrcBuildRRCConReq ARGS((Buffer **mBuf, UeCb    *ueCb, Bool   sTmsiPres));
EXTERN S16 ueRrcBuildRRCConSetupComplete ARGS((Buffer **mBuf));
EXTERN S16 ueRrcBuildRRCSecModeComplete ARGS((Buffer **mBuf));
EXTERN S16 ueRrcBuildRRCConReCfgComplete  ARGS((Buffer **mBuf));
EXTERN S16 ueRrcDatInd ARGS((UeCb *ueCb, U8 lcId, Buffer *pdu));
EXTERN S16 ueRRCBuildUpLinkTrfr ARGS((Buffer **mBuf)); 
/* ue008.101: Fixed compilation Warnings */
#ifdef TOTAL_ENB
/* ue009.101: Changes to send the Measurement report */
EXTERN S16 ueRrcBuildMeasRpt ARGS((UeAppCb *ueAppCb, NhuDatReqSdus **pdu, NhuMeasConfig *measCfg));
/* ue010.101: Enhanced measurement feature.
   Added new Functions to fill measurement report */
EXTERN U16 uefillrrcMeasurementIE(NhuMeasurementReport_r8_IEs *r8Ie1, 
               NhuReportConfigEUTRA  *reportConfigEUTRA, U32 measId, U8 purpose, U32 PhyCellid, NhuDatReqSdus  *tmpPdu);
EXTERN NhuMeasObjectToAddModmeasObject* ueExtractmeasObj(U32 measObjectId, NhuMeasObjectToAddModLst  *measObjectToAddModLst);
EXTERN NhuReportConfigToAddModreportConfig* ueExtractReportCfgObj(U32 reportConfigID, NhuReportConfigToAddModLst *reportConfigToAddModLst);
#else /* ifdef TOTAL_ENB */
EXTERN S16 ueRrcBuildMeasRpt ARGS((NhuDatReqSdus **pdu));
#endif
#ifdef TRACKING_AREA_UPDATE
EXTERN S16 ueAppSndTAURequest(UeAppCb *ueAppCb);
#endif
/* ue003.101: Added for paging support */
EXTERN S16 ueRrcPagingInd ARGS ((CellCb *cell,Buffer *mBuf));

EXTERN S16 ueDapDatInd ARGS((UeCb *ueCb, U8 lcId, Buffer *pdu));

EXTERN S16 processSrb0 ARGS((UeCb *ueCb, Buffer *pdu));

EXTERN S16 processSrb12  ARGS((UeCb *ueCb, Buffer *pdu));
/* ue008.101: Fixed compilation Warnings */
EXTERN S16 UeUiPjuDatReq ARGS ((Pst *pst, SpId spId, Buffer *mBuf, U16 cellId,U16 ueId,U8 lcId));

EXTERN S16 initUe ARGS ((UeCb *ue,U8 cellId,U8 ueId));
EXTERN S16 ueUtlInit  ARGS((Void));

EXTERN S16 UePerfAppLiNhuDatInd ARGS((Pst *pst,SuId suId,
                                      NhuDatIndSdus *datIndSdus));

EXTERN S16 UePerfAppLiPjuDatInd ARGS ((Pst *pst,SuId suId,
                                       Buffer *mBuf,U16 ueIdx));

EXTERN S16 ueRlcUmReAssemblePdu ARGS((UeCb  *ueCb, UeRlcUmHdr *umHdr,
                                      U8    lcId, Buffer *pdu)); 

/* ue002.101: Additional defines for MSPD CL */
#ifdef YS_MSPD
EXTERN UeMsSrCfgInfo        ueSrCfgDb[UE_NUM_SR_CFG];
EXTERN UeMsSrsCfgInfo       ueSrsCfgDb[UE_NUM_SRS_CFG];
EXTERN UeMsCqiPmiCfgIdxInfo ueCqiPmiCfgDb[UE_NUM_CQI_CFG];
/* Functions Required for LTE CL */
EXTERN S16 ysMsUePalDatInd ARGS((CmLteTimingInfo tmInfo, UeCb *ueCb, Buffer *pdu));
EXTERN S16 ysMsUePalAddSr ARGS((CmLteTimingInfo tmInfo, UeCb *ueCb));
EXTERN S16 ysMsUeClUtlMapRxSduInd ARGS ((PRXSDUIND      rxSduInd,
                                        CellCb         *cellCb));

EXTERN RESULTCODE MacDispatch ARGS ((
U32   size,
Ptr   l1Msg
));

EXTERN S16 ysMsUeClUlmRxStartInd ARGS ((
PDLSUBFRDESC    rxStartInd,
CellCb        *cellCb
));

EXTERN Void ysMsUeClUlmRxEndInd ARGS ((
PMSGIND        rxEndInd,
CellCb        *cellCb
));

EXTERN S16 ysMsUeClUtlMapRxStartInd ARGS ((
PDLSUBFRDESC      rxStartInd,
TfuCntrlReqInfo   *cntrlReq 
));
EXTERN S16   ysMsUeClUtlMapTxVector ARGS ((
CellCb            *cellCb,
CmLteTimingInfo   timingInfo,
GENMSGDESC        *msgHeader));

EXTERN S16 ysMsUeClUtlMapDatInd ARGS ((
TfuDatIndInfo  *tfuDatIndInfo,
TfuDatInfo     *pduInfo,
UePhyRxSdu     *phyRxSduInd,
U8             channelType
));

EXTERN S16 ysMsUeClUtlMapRachInd ARGS ((
TfuRaReqIndInfo   *rachInd,
TfuRachInfo       rachInfo,
UePhyRxSdu        *phyRxSduInd,
U8                channelType
));

EXTERN S16 ysMsUeClUtlMapSrInd ARGS ((
TfuSrIndInfo   *tfuSrIndInfo,
TfuSrInfo      *srInfo,
UePhyRxSdu     *phyRxSduInd,
U8             channelType
));

EXTERN S16 ysMsUeClUtlMapDlCqiInd ARGS
((
TfuDlCqiIndInfo   *tfuDlCqiInd,
TfuDlCqiRpt       *cqiRpt,
UePhyRxSdu        *phyRxSduInd
));

EXTERN S16 ysMsUeClUtlMapDlHarqCqiInd ARGS
((
TfuDlCqiIndInfo   *tfuDlCqiInd,
TfuDlCqiRpt       *cqiRpt,
UePhyRxSdu        *phyRxSduInd
));

EXTERN S16 ysMsUeClUtlMapHqInd ARGS
((
TfuHqIndInfo   *tfuHqInd,
TfuHqInfo      *hqInfo,
UePhyRxSdu     *phyRxSduInd,
U8             channelType
));

EXTERN Void ueUtlFreeDatReq ARGS
((
TfuDatReqInfo   *datReq
));

EXTERN S16 ysMsUeClUtlAllocEventMem ARGS
((
Ptr       *memPtr,
Size      memSize
));


EXTERN Void ysMsUeClUtlFreeDatInfo ARGS
((
TfuDatIndInfo   *datInfo
));

EXTERN Void ysMsUeClUtlFreeSduLst ARGS
((
CmLListCp *sduLst
));


EXTERN S16 TfUiTfuEndInd ARGS((Pst *pst, SuId suId, CmLteTimingInfo tmInfo, U16 callId));

/* Function prototypes for pal and stub */
EXTERN S16 ysMsUePalInitRcvrTsk ARGS((Void));

EXTERN S16 ysMsUePalSend2Peer ARGS((
U8        *sendBuf,
U32        bufLen,
Bool       loopBack
));

EXTERN PTR MsgGetDataOffset ARGS((PTR msg));

EXTERN Void MsgInitMessage ARGS((PMSGHEADER pHdr));
#endif /* YS_MSPD*/

#ifdef LTE_START_UL_DL_DATA
EXTERN U32  recvPkt;
EXTERN S16 ueAppTti ARGS((CmLteTimingInfo    tti));
#endif /* LTE_START_UL_DL_DATA */

/* ue003.101: Added for SI feature */
EXTERN Void ueAppSibInd ARGS((NhuBCCH_DL_SCH_Msg *bcchSchMsg));
EXTERN S16 ueRrcSIBInd ARGS((Buffer *mBuf));
/* ue007.101:warning fix */
#ifndef SS_CAVIUM
PUBLIC Void ueAppHndlIPPkt(CONSTANT U8  *pkt,U32 bytesRcvd);
#else
PUBLIC S16 ueAppHndlIPPkt(cvmx_wqe_t  *work );
#endif

/* ue008.101: Added new function prototype. */
EXTERN Void ueMacHndlRachForHo ARGS((CmLteTimingInfo      tmInfo,
                               U16                  cellId,
                               U32                  raRnti));

EXTERN S16 ueAppUtlBldDeActBerContextAccept ARGS((UeEsmCb *esmCb,
                                                  UeAppCb *ueCb,
                                                  CmNasEvnt **esmEvnt));

EXTERN S16 ueAppSndModBrReq ARGS((void));

EXTERN S16 ueAppIncModBearerRej ARGS((UeEsmCb *esmCb,
                                 UeAppCb *ueAppCb,
                                 CmNasEvnt *esmEvnt));


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __UEX__ */


/**********************************************************************
         End of file:     ue.x@@/main/1 - Sun Mar 28 22:59:20 2010
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp   1. Initial Release.
/main/1+    ue002.101  sv   1. Support for RLC UM mode, MSPD CL.
/main/1+    ue003.101 rp   1. Added support for paging.
                           2. Added support for dedicated bearers.
                           3. Added TA and SI features.
/main/1+    ue007.101 rk   1. Added support for multiple attach and detach.
                      ms  1. warning fix.                           
/main/1+    ue008.101 ragrawal 1. Fix for compilation warnings.
                               2. Added new function prototype.
                               3. Updated ueMacCxt and ueCb structure.
                               4. Added new structure rarGrantInfo.
/main/1+    ue009.101 akaranth 1. Changes to send the measurement report. 
/main/1+    ue010.101 akaranth 1. Enhanced measurement report. 
                               2. Added new function fill measurement report.
*********************************************************************91*/
