

/********************************************************************20**
  
        Name:    LTE RLC file 
    
        Type:    C include file
  
        Desc:    This file contains all the data structures and 
                 prototypes for LTE RLC.
 
        File:    kw.x

        Sid:      kw_dl.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:46 2014
  
        Prg:     N/A 
  
*********************************************************************21*/
/** @file kw.x
@brief RLC Product Structures, prototypes
*/

#ifndef __KW_DLX__
#define __KW_DLX__


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

typedef  struct kwDlUeCb KwDlUeCb;
/** @struct KwPduMap
PDU Map Info for AM */
typedef struct kwPduMap
{
  KwSn         sn;                          /*!< Mapped PDU's SN */
  Bool         rcvd;                        /*!< Flag to indicate if an ACK is
                                                 received for the PDU */
}KwPduMap;

/** @struct KwSdu
SDU received from RRC/PDCP */
typedef struct kwSdu                        
{
   CmLList   lstEnt;                        /*!< List entry for SDU */
   Buffer    *mBuf;                         /*!< SDU buffer */ 
   MsgLen    sduSz;                         /*!< Buffer Size */
   MsgLen    actSz;                         /*!< Actual buffer Size */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwSduSnMap  *snMap;                       /*!< Sdu and the list of SN it maps to */
#endif /* LTE_L2_MEAS_RLC */

   union
   {
      struct   _t 
      {
         U16           sfn;                 /*!< Sub frame number for BCCH/PCCH */
         U8            subframe;            /*!< Subframe number */
         CmLteRnti     rnti;                /*!< RNTI for CCCH */
      }tm;                                  /*!< SDU for TM mode */

      struct   _u
      {
         U32           sduId;               /*!< SDU Identifier */
         Bool          isSegmented;         /*!< Flag to indicate if the SDU is segmented */
      }um;                                  /*!< SDU for UM mode */

      struct   _a
      {
         U32           sduId;               /*!< SDU Identifier */
         MsgLen        rcvdSz;              /*!< Received SDU Size from the peer */
         U8            numPdu;              /*!< Number of PDUs in pduMap */
         KwPduMap      pduMap[KW_MAX_PDU_MAP];   /*!< Array of PDUs mapped with SDU */
         Bool          isSegmented;         /*!< Flag to indicate if the SDU is segmented */
      }am;                                  /*!< SDU for AM mode */
   }mode;                                   /*!< RLC mode specific SDUs */

}KwSdu;

/** @addtogroup tmmode */
/*@{*/

/** @struct KwTm
Transparent mode control block */
typedef struct kwTm
{
   CmLListCp   sduQ;                        /*!< SDU queue for TM */
}KwTm;
/*@}*/

/** @struct KwBoReport
Buffer Occupancy Report */
typedef struct kwBoRep
{
   S32         bo;                          /*!< Buffer occupancy */
   U16         estHdrSz;                    /*!< Estimated header size for the bo */
   Bool        staPduPrsnt;                 /*!< Flag to indicate if the bo is control PDU */
} KwBoRep;

/** @struct KwDatReq
Data Request to be sent to MAC */
typedef struct kwDatReq
{
   MsgLen      pduSz;                       /*!< PDU(s) size indicated by MAC */ 
   KwPduInfo   pduInfo;                     /*!< PDU Information for lChs within UE */
   KwBoRep     boRep;                       /*!< BO report */ 
   U32         dataId;                      /*!< Data Id sent with PDUs to MAC */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwLchMapInfo lchMapInfo;                 /*!< Logical channel mapping info */
#endif /* LTE_L2_MEAS_RLC */
}KwDatReq;

/** @defgroup ummode UM Module Info 
*/

/** @addtogroup ummode */
/*@{*/
/** @struct KwUmDl
Unacknowledged mode downlink control block */
typedef struct kwUmDl
{
   CmLListCp   sduQ;                        /*!< SDU queue for UM */
   U8          snLen;                       /*!< Sequence number length */
   S32         bo;                          /*!< Buffer occupancy */
   /* kw005.201 removed the warning */
   S32         estHdrSz;                    /*!< Estimated header size for the available BO */
   KwSn        vtUs;                        /*!< VT(US) */
   U16         numLi;                       /*!< Number of LIs */
   U16         li[KW_MAX_LI];               /*!< Length Indicator array */
}KwUmDl;

/** @struct KwSduMap
SDU Map Info for AM */
typedef struct kwSduMap
{
   U32           sduId;                     /*!< SDU Identifier */
   MsgLen        actSz;                     /*!< SDU Size */
   MsgLen        sduSz;                     /*!< SDU Size */
   Bool          isSegmented;               /*!< Flag to indicate if the SDU is segmented */
}KwSduMap;

/** @struct KwRetx
Retransmission Buffer */
typedef struct kwRetx
{
   CmLList     lstEnt;                      /*!< List entry for Retransmission PDU */
   Buffer      *seg;                        /*!< Buffer of PDU or Segment */
   MsgLen      segSz;                       /*!< Segment Size */
   MsgLen      hdrSz;                       /*!< Header size for the segment */
   KwAmHdr     amHdr;                       /*!< AM header Info */
   U16         soEnd;                       /*!< Segment Offset End */
   KwSn        retxCnt;                     /*!< Retransmission count */
   Bool        yetToConst;                  /*!< Yet to construct seg flag */
   Bool        wtForAck;                    /*!< Flag to indicate if the node is 
                                                 waiting for an Ack */
   U8          numSdu;                      /*!< Number of PDUs in sduMap */
   KwSduMap    sduMap[KW_MAX_LI];           /*!< Array of SDUs mapped with PDU */
}KwRetx;

/** @struct KwTx
Transmission Buffer */
typedef struct kwTx
{
   Buffer      *pdu;                        /*!< Buffer of PDU */
   MsgLen      pduSz;                       /*!< PDU Size */
   MsgLen      hdrSz;                       /*!< Header size for the PDU */
   KwAmHdr     amHdr;                       /*!< AM header Info */
   U8          numSdu;                      /*!< Number of PDUs in sduMap */
   KwSduMap    sduMap[KW_MAX_LI];           /*!< Array of SDUs for this PDU */
   CmLList     rlsLnk;                      /*!< Lnk to store on release lst */
}KwTx;

/** @addtogroup ammode */
/*@{*/

/** @struct KwAmDl
Acknowledged mode downlink control block */
typedef struct kwAmDl
{
   CmLListCp   sduQ;                        /*!< SDU queue */
   KwSdu       *nxtTx;                      /*!< Next SDU to be transmitted */
   CmTimer     pollRetxTmr;                 /*!< T_poll_retransmit Timer */
   U16         pollRetxTmrInt;              /*!< Timer Interval */
   S16         pollPdu;                     /*!< Poll_PDU */
   S32         pollByte;                    /*!< Poll_Byte */
   U8          maxRetx;                     /*!< Max_Retx_Threshold */
   S32         cntrlBo;                     /*!< BO of control pdu */ 
   S32         retxBo;                      /*!< BO of Retransmission PDUs */ 
   U32         estHdrSz;                    /*!< Estimated header size for the available BO */
   S32         bo;                          /*!< BO of new PDUs */
   KwTx        **txBuf;                     /*!< Transmission buffer */
   CmLListCp   retxLst;                     /*!< Retransmission PDU list */
   KwRetx      *nxtRetx;                    /*!< Next node to be retransmitted */
   KwSn        txSn;                        /*!< Starting sn for txBuf */
   KwSn        vtS;                         /*!< VT(S) - Send state variable */
   KwSn        vtMs;                        /*!< VT(MS) - Maximum send state variable */
   KwSn        vtA;                         /*!< VT(A) - Acknowledgement state variable */ 
   S16         pduWoPoll;                   /*!< PDU without poll bit counter */
   S32         byteWoPoll;                  /*!< Byte without poll bit counter */
   KwSn        pollSn;                      /*!< Poll SN */
   /* kw003.201 */
   S16         numSduPdu;                   /*!< Number of SDUs/PDU to be sent*/
   S16         numSeg;                      /*!< Number of segments to be sent*/
#ifdef KW_BG_DL_PROC
   CmLListCp   toBeRlsLst;                  /*!< Stores to be released PDUs */
#endif
   Buffer      *mBuf;                       /*!< Stores the Control Pdu */
}KwAmDl;

/*@}*/



/** @struct KwRbCb 
RLC RB control block */
typedef struct _kwDlRbCb
{
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   CmHashListEnt   qciHlEnt;                /*!< QcI Hash list entry for RbCb */
   KwDlUeCb          *ueCb;                   /*!< Pointer to UeCb  */
   KwL2MeasRbCb    rbL2Cb;                  /*!< RB measurement L2 Cb */
   CmLListCp       sduSnMapQ;               /*!< SDU SN map queue for UM */
   U8              qci;                     /*!< qci of the RB */
#ifdef LTE_RLC_R9
   KwL2MeasIpThruput l2MeasIpThruput;       /*!< Holds related parameter for
                                                 DL/Ul ip throughput>*/
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */
   CmLteRlcId      rlcId;                   /*!< RLC Identifier */
   KwLchInfo       lch; /*!< Logical Channel Info 
                                                      For AM mode: 
                                                      idx = 0 is for DL and
                                                      idx = 1 is for UL */
   CmLteRlcMode    mode;               /*!< Entity Mode */
   U8              dir;                /*!< Direction for UL/DL */
   Inst            inst;               /*!< Tapa Instance where rb created */
   SpId            kwuSapId;           /*!< KWU sap Id, to get the KwuSapCb */
   SpId            udxSapId;           /*!< KWU sap Id, to get the KwuSapCb */
   U32             transId;                 /*!< Transaction Id for RLC */
   union          
   {
/** @defgroup tmmode TM Module Info 
*/
      KwTm         tm;                   /*!< TM mode specific elements */
      KwUmDl       umDl;                       /*!< UM downlink elements */
      KwAmDl       amDl;                    /*!< AM downlink elements */
   }m;                                      /*!< RLC mode specific Info */
#ifdef KW_BG_DL_PROC
   CmLList        rlsLnk;                   /*!< Link to add to release list */
#endif
}KwDlRbCb;


/** @struct KwLch
Logical channel mapping with RbCb */
typedef struct kwDlLch
{
   KwDlRbCb *dlRbCb;                          /*!< Pointer to Downlink RbCb */
}KwDlLch;                                  

/** @struct KwDlCellCb
Cell control block */
typedef struct kwDlCellCb
{
   CmHashListEnt cellHlEnt;                 /*!< Hash list entry for CellCb */
   CmLteCellId   cellId;                    /*!< Cell Id */
   KwDlRbCb          *rbCb[KW_MAX_RB_PER_CELL]; /*!< RbCbs within a Cell */
   KwDlLch         lCh[KW_MAX_LCH_PER_CELL];  /*!< Array of Logical channels */
}KwDlCellCb;


/** @struct KwDlUeCb
UE control block */
struct kwDlUeCb
{
   CmHashListEnt ueHlEnt;                   /*!< Hash list entry for UeCb */
   KwUeKey       key;                       /*!< Hash list key for UeCb */
   KwDlRbCb          *srbCb[KW_MAX_SRB_PER_UE]; /*!< SRB RbCbs within a UE */ 
   KwDlRbCb          *drbCb[KW_MAX_DRB_PER_UE]; /*!< DRB RbCbs within a UE */ 
   KwDlLch             lCh[KW_MAX_LCH_PER_UE];    /*!< Array of Logical channels */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   U16           numActRb[LKW_MAX_QCI]; /* number of RBs Active */
#endif /* LTE_L2_MEAS_RLC */
};

/****************************************************************************
 *                      EXTERN Declarations
 ***************************************************************************/
EXTERN S16 kwCfgAddDlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgReCfgDlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelDlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelDlUe ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgReEstDlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                Bool sndReEst,CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelDlCell ARGS ((KwCb *gCb, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg,CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDlUeIdChng ARGS ((KwCb *gCb, CkwUeInfo *ueInfo, 
                                  CkwUeInfo *newUeInfo, CmStatus  *status));

EXTERN S16 kwDbmDlInit ARGS ((KwCb *gCb));

EXTERN S16 kwDbmDlDeInit ARGS ((KwCb *gCb));

EXTERN S16 kwDbmCreateDlUeCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwDlUeCb            **ueCb       /* UE Control Block */
));

EXTERN S16 kwDbmFetchDlUeCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwDlUeCb            **ueCb       /* UE Control Block */
));

EXTERN S16 kwDbmDelDlUeCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
KwDlUeCb            *ueCb,       /* UE Identifier */
Bool              abortFlag    /* Abort Flag */
));

EXTERN S16 kwDbmDelAllDlUe ARGS ((KwCb *gCb));

EXTERN S16 kwDbmCreateDlCellCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteCellId       cellId,     /* Cell Identifier */
KwDlCellCb          **cellCb     /* UE Control Block */
));

EXTERN S16 kwDbmFetchDlCellCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteCellId       cellId,     /* Cell Identifier */
KwDlCellCb          **cellCb     /* Cell Control Block */
));

EXTERN S16 kwDbmDelDlCellCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
KwDlCellCb          *cellCb     /* Cell Control Block */
));

EXTERN S16 kwDbmDelAllDlCell ARGS ((KwCb *gCb));

EXTERN S16 kwDbmFetchDlRbCbForUi ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRlcId        rlcId,      /* RLC Identifier */
KwDlRbCb            **rbCb       /* RB Cb */
));

EXTERN S16 kwDbmFetchDlRbCbForLi ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
CmLteLcId         lcId,       /* Logical channel instance */
U8                dir,        /* Direciotn DL/UL */
KwDlRbCb            **rbCb      /* RB Cb */
));

EXTERN S16 kwDbmDelAllDlRb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
KwDlRbCb         **rbCbLst,   /* RB Cb list */
U8                numRbCb     /* Number of rbCbs */
));

EXTERN S16 kwDbmDlShutdown ARGS ((KwCb *gCb));

EXTERN PUBLIC S16 kwTmmQSdu ARGS ((KwCb *gCb,KwDlRbCb *rbCb,
                                   KwuDatReqInfo *datReqInfo,
                                   Buffer *mBuf));
EXTERN PUBLIC S16 kwTmmSndToLi ARGS ((KwCb *gCb,KwDlRbCb *rbCb));
EXTERN S16 kwDlTmmReEstablish ARGS ((KwCb *gCb,KwDlRbCb *rbCb));

EXTERN S16 kwUmmQSdu ARGS ((KwCb *gCb,KwDlRbCb *rbCb,U32 sduId,Buffer *mBuf));
EXTERN S16 kwUmmDiscSdu ARGS ((KwCb *gCb,KwDlRbCb *rbCb,U32 sduId));
EXTERN S16 kwDlUmmReEstablish ARGS ((KwCb *gCb, CmLteRlcId rlcId, 
                                     Bool sndReEst,KwDlRbCb *rbCb));
EXTERN S16 kwDlAmmReEstablish     ARGS((KwCb *gCb, CmLteRlcId rlcId, 
                                       Bool sndReEst,KwDlRbCb *rbCb));
EXTERN PUBLIC S16 kwUtlSndToLi ARGS ((KwCb *gCb,KwDStaIndInfo *staIndInfo));
EXTERN PUBLIC S16 kwUmmProcessSdus ARGS ((KwCb *gCb,
                                         KwDlRbCb *rbCb, KwDatReq *datReq));
EXTERN S16 kwAmmQSdu            ARGS((KwCb *gCb, KwDlRbCb *rbCb, 
                                      Buffer *mBuf, U32 sduId ));
EXTERN S16 kwAmmProcessSdus     ARGS((KwCb *gCb, 
                                      KwDlRbCb *rbCb, KwDatReq *kwDatReq ));
EXTERN S16 kwAmmDiscSdu         ARGS((KwCb *gCb, KwDlRbCb *rbCb, U32 sduId));
EXTERN Void kwAmmPollRetxTmrExp ARGS((KwCb *gCB, KwDlRbCb *rbCb));

EXTERN S16 kwUtlSndDStaRsp ARGS ((KwCb *gCb,KwDlRbCb *rbCb,
                                         S32 bo,S32 estHdrSz,
                                         Bool staPduPrsnt));
#ifdef LTE_L2_MEAS_RLC
EXTERN PUBLIC S16 kwUtlEmptySduQ ARGS ((KwCb *gCb,
                                        KwDlRbCb *rbCb, CmLListCp *sduQ));
#else /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUtlEmptySduQ ARGS ((KwCb *gCb,CmLListCp *sduQ));
#endif /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUtlCalcLiForSdu ARGS ((KwCb *gCb,U16 numLi,
                                           MsgLen msgLen,S16 *pduSz));
EXTERN Void kwUtlFreeDlRbCb ARGS ((KwCb *gCb, KwDlRbCb *rbCb));

/* Activation functions */
EXTERN S16 kwDlActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 kwDlActvTsk ARGS ((
Pst *pst,              /* pst structure */
Buffer *mBuf            /* message buffer */
));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __KW_DLX__ */

  
/********************************************************************30**
  
         End of file:     kw_dl.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:46 2014
  
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

