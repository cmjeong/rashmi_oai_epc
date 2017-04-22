

/********************************************************************20**
  
        Name:    LTE RLC file 
    
        Type:    C include file
  
        Desc:    This file contains all the data structures and 
                 prototypes for LTE RLC.
 
        File:    kw.x

        Sid:      kw_ul.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:53 2014
  
        Prg:     N/A 
  
*********************************************************************21*/
/** @file kw_ul.x
@brief RLC Product Structures, prototypes
*/

#ifndef __KW_ULX__
#define __KW_ULX__


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

typedef struct kwUlUeCb KwUlUeCb;
/* kw005.201 added support for L2 Measurement */

/** @defgroup ummode UM Module Info 
*/

/** @struct KwUmRecBuf 
UM Reception Info */
typedef struct kwUmRecBuf
{
   Buffer      *pdu;                        /*!< PDU Buffer */
   KwUmHdr     *umHdr;                      /*!< UM Header Info */
   MsgLen      pduSz;                       /*!< PDU Size */
}KwUmRecBuf;

/** @struct KwUmUl
Unacknowledged mode uplink control block */
typedef struct kwUmUl
{
   U8          snLen;                       /*!< Sequence number length */
   U8          reOrdTmrInt;                 /*!< Timer Interval */
   KwUmRecBuf  **recBuf;                    /*!< Reception buffer */
   KwSn        umWinSz;                     /*!< UM window size */ 
   KwSn        sn;                          /*!< Sequence number */
   KwSn        vrUr;                        /*!< VR(UR) - Receive state variable */
   KwSn        vrUh;                        /*!< VR(UH) - Highest received state variable */
   KwSn        vrUx;                        /*!< VR(UX) - Reordering state variable */
   CmTimer     reOrdTmr;                    /*!< Reordering Timer */
   Buffer      *partialSdu;                 /*!< Partial SDU - Remains till the complete SDU is received */
}KwUmUl;
/*@}*/

/** @struct KwSeg
Segment List */
typedef struct kwSeg
{
   CmLList     lstEnt;                      /*!< List entry for PDU segment */
   Buffer      *seg;                        /*!< PDU segment */
   MsgLen      segSz;                       /*!< Buffer Size */
   U16         soEnd;                       /*!< Segment Offset End */
   KwAmHdr     amHdr;                       /*!< AM header */
}KwSeg;

/*@}*/


/** @struct KwAmRecBuf
AM Reception buffer */
typedef struct kwAmRecBuf
{
   Buffer      *pdu;                        /*!< PDU buffer */
   MsgLen      pduSz;                       /*!< Buffer Size */
   KwAmHdr     amHdr;                       /*!< AM header Info */
   CmLListCp   segLst;                      /*!< PDU Segments list */
   KwSeg       *expByteSeg;                 /*!< Next expected byte segment */
   U16         expSo;                       /*!< Next expected seg offset */
   Bool        allRcvd;                     /*!< All bytes received flag for
                                                 this PDU */
#ifdef KW_BG_UL_PROC
   CmLList     pduLnk;                      /*!< Link to store PDU to be 
                                                 released */
#endif
}KwAmRecBuf;

/** @addtogroup ammode */
/*@{*/

/** @struct KwAmUl
Acknowledged mode uplink control block */
typedef struct kwAmUl
{
   KwAmRecBuf  **recBuf;                    /*!< Reception buffer */
   KwSn        sn;                          /*!< Sequence number */
   KwSn        vrR;                         /*!< VR(R) - Receive state variable */
   KwSn        vrH;                         /*!< VR(H) - Highest received state variable */
   KwSn        vrX;                         /*!< VR(X) - reorderig state variable */
   KwSn        vrMr;                        /*!< VR(MR) - Maximum acceptable receive 
                                                 state variable */ 
   KwSn        vrMs;                        /*!< VR(MS) - Maximum STATUS transmit 
                                                 state variable */
   Bool        staTrg;                      /*!< Flag to indicate if status trigger occured */
   Buffer      *partialSdu;                 /*!< Partial SDU - Remains till the 
                                                 complete SDU is received */
   S32         cntrlBo;                     /*!< BO of control pdu */ 
   KwSn        expSn;                       /*!< Expected SN for reassembly */
   U16         expSo;                       /*!< Expected SO for reassembly */
#ifdef KW_BG_UL_PROC
   CmLListCp   pduLst;                      /*!< List to store PDUs to be 
                                                 released */
#endif
   CmTimer     staProhTmr;                  /*!< T_status_prohibit Timer */
   U16         staProhTmrInt;               /*!< Timer Interval */
   CmTimer     reOrdTmr;                    /*!< T_reordering Timer */
   U8          reOrdTmrInt;                 /*!< Timer Interval */
}KwAmUl;

/*@}*/

/** @struct KwRbCb 
RLC RB control block */
typedef struct _kwUlRbCb
{
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   CmHashListEnt   qciHlEnt;                /*!< QcI Hash list entry for RbCb */
   KwUlUeCb          *ueCb;                   /*!< Pointer to UeCb  */
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
   Inst            inst;               /*!< Tapa where Rb created Instance id */
   SpId            kwuSapId;           /*!< KWU sap Id, to get the KwuSapCb */
   SpId            udxSapId;           /*!< KWU sap Id, to get the KwuSapCb */
   U32             transId;                 /*!< Transaction Id for RLC */
   union          
   {
      KwUmUl       umUl;                       /*!< UM  mode Ul elements */
      KwAmUl       amUl;                    /*!< AM mode uplink elements */
   }m;                                      /*!< RLC mode specific Info */
#ifdef KW_BG_DL_PROC
   CmLList        rlsLnk;                   /*!< Link to add to release list */
#endif
}KwUlRbCb;


/** @struct KwLch
Logical channel mapping with RbCb */
typedef struct kwUlLch
{
   KwUlRbCb *ulRbCb;                          /*!< Pointer to Uplink RbCb */
}KwUlLch;                                  

/** @struct KwCellCb
Cell control block */
typedef struct kwUlCellCb
{
   CmHashListEnt cellHlEnt;                 /*!< Hash list entry for CellCb */
   CmLteCellId   cellId;                    /*!< Cell Id */
   KwUlRbCb     *rbCb[KW_MAX_RB_PER_CELL]; /*!< RbCbs within a Cell */
   KwUlLch         lCh[KW_MAX_LCH_PER_CELL];  /*!< Array of Logical channels */

}KwUlCellCb;


/** @struct KwUeCb
UE control block */
struct kwUlUeCb
{
   CmHashListEnt ueHlEnt;                   /*!< Hash list entry for UeCb */
   KwUeKey       key;                       /*!< Hash list key for UeCb */
   KwUlRbCb      *srbCb[KW_MAX_SRB_PER_UE]; /*!< SRB RbCbs within a UE */ 
   KwUlRbCb      *drbCb[KW_MAX_DRB_PER_UE]; /*!< DRB RbCbs within a UE */ 
   KwUlLch       lCh[KW_MAX_LCH_PER_UE];    /*!< Array of Logical channels */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   U16           numActRb[LKW_MAX_QCI]; /* number of RBs Active */
#endif /* LTE_L2_MEAS_RLC */
};


/****************************************************************************
 *                      EXTERN Declarations
 ***************************************************************************/
EXTERN S16 kwCfgAddUlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgReCfgUlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelUlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelUlUe ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgReEstUlRb ARGS ((KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, 
               Bool sndReEst, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgDelUlCell ARGS ((KwCb *gCb, CmLteCellId cellId, 
                              CkwEntCfgInfo *entCfg,CkwEntCfgCfmInfo *entCfm));
EXTERN S16 kwCfgUlUeIdChng ARGS ((KwCb *gCb, CkwUeInfo *ueInfo, 
                                  CkwUeInfo *newUeInfo, CmStatus  *status));

EXTERN S16 kwDbmUlInit ARGS ((KwCb *gCb));

EXTERN S16 kwDbmUlDeInit ARGS ((KwCb *gCb));

EXTERN S16 kwDbmCreateUlUeCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUlUeCb            **ueCb       /* UE Control Block */
));

EXTERN S16 kwDbmFetchUlUeCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUlUeCb            **ueCb       /* UE Control Block */
));

EXTERN S16 kwDbmDelUlUeCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
KwUlUeCb            *ueCb,       /* UE Identifier */
Bool              abortFlag    /* Abort Flag */
));

EXTERN S16 kwDbmDelAllUlUe ARGS ((KwCb *gCb));

EXTERN S16 kwDbmCreateUlCellCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteCellId       cellId,     /* Cell Identifier */
KwUlCellCb          **cellCb     /* UE Control Block */
));

EXTERN S16 kwDbmFetchUlCellCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteCellId       cellId,     /* Cell Identifier */
KwUlCellCb          **cellCb     /* Cell Control Block */
));

EXTERN S16 kwDbmDelUlCellCb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
KwUlCellCb          *cellCb     /* Cell Control Block */
));

EXTERN S16 kwDbmDelAllUlCell ARGS ((KwCb *gCb));

EXTERN S16 kwDbmFetchUlRbCbForUi ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRlcId        rlcId,      /* RLC Identifier */
KwUlRbCb            **rbCb       /* RB Cb */
));

EXTERN S16 kwDbmFetchUlRbCbForLi ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
CmLteLcId         lcId,       /* Logical channel instance */
U8                dir,        /* Direciotn DL/UL */
KwUlRbCb            **rbCb      /* RB Cb */
));

EXTERN S16 kwDbmDelAllUlRb ARGS ((
KwCb             *gCb,        /* isnt cntrl blk */
KwUlRbCb         **rbCbLst,   /* RB Cb list */
U8                numRbCb     /* Number of rbCbs */
));
EXTERN S16 kwDbmAddUlTransIdLst ARGS((KwCb *gCb,KwCfgInfo  *cfg));
EXTERN S16 kwDbmFindUlTransIdLst ARGS((KwCb *gCb,U32 transId,
                                      KwCfgInfo   **cfg));
EXTERN S16 kwDbmDelUlTransIdLst ARGS((KwCb *gCb,KwCfgInfo  **cfg));
EXTERN S16 kwDbmDelAllUlTransIdLst ARGS((KwCb  *gCb));

EXTERN S16 kwDbmUlShutdown ARGS ((KwCb *gCb));
#ifdef CCPU_OPT
EXTERN PUBLIC S16 kwTmmRcvFrmLi ARGS ((KwCb *gCb, KwUlRbCb *rbCb,
                                       CmLteRnti tCrnti, Buffer *pdu));
#else /* CCPU_OPT */
EXTERN PUBLIC S16 kwTmmRcvFrmLi ARGS ((KwCb *gCb,KwUlRbCb *rbCb,Buffer *pdu));
#endif /* CCPU_OPT */

EXTERN S16 kwTmmUlReEstablish ARGS ((KwCb *gCb,KwUlRbCb *rbCb));

#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
EXTERN S16 kwUmmProcessPdus ARGS((KwCb *gCb,KwUlRbCb  *rbCb, KwPduInfo *pduInfo,
      KwL2MeasUlThrpTimInfo *ulTimeInfo));
#else /* LTE_RLC_R9 */
EXTERN PUBLIC S16 kwUmmProcessPdus ARGS ((KwCb *gCb, KwUlRbCb *rbCb,
                                               KwPduInfo *pduInfo));
#endif /* LTE_RLC_R9 */
#else /* LTE_L2_MEAS_RLC */
EXTERN PUBLIC S16 kwUmmProcessPdus ARGS ((KwCb *gCb, KwUlRbCb *rbCb,
                                                 KwPduInfo *pduInfo));
#endif /* LTE_L2_MEAS_RLC */
EXTERN S16 kwUmmUlReEstablish ARGS ((KwCb *gCb, CmLteRlcId rlcId, 
                                     Bool sndReEst,KwUlRbCb *rbCb));
EXTERN S16 kwAmmUlReEstablish     ARGS((KwCb *gCb, CmLteRlcId rlcId, 
                                     Bool sndReEst,KwUlRbCb *rbCb));
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
EXTERN S16 kwAmmProcessPdus ARGS((KwCb *gCb,KwUlRbCb  *rbCb, 
                                  KwPduInfo  *pduInfo,
                                  KwL2MeasUlThrpTimInfo *ulTimeInfo));
#else /* LTE_RLC_R9 */
EXTERN S16 kwAmmProcessPdus     ARGS((KwCb *gCb, KwUlRbCb *rbCb,
                                               KwPduInfo *pduInfo));
#endif /* LTE_RLC_R9 */
#else /* LTE_L2_MEAS_RLC */
EXTERN S16 kwAmmProcessPdus     ARGS((KwCb *gCb,KwUlRbCb *rbCb, 
                                           KwPduInfo *pduInfo));
#endif /* LTE_L2_MEAS_RLC */
EXTERN  S16 kwUmmReOrdTmrExp ARGS((KwCb *gCb,KwUlRbCb  *rbCb));
EXTERN Void kwAmmReOrdTmrExp    ARGS((KwCb *gCb, KwUlRbCb *rbCb));
EXTERN Void kwAmmStaProTmrExp   ARGS((KwCb *gCb, KwUlRbCb *rbCb));

EXTERN PUBLIC S16 kwUtlRcvFrmLi ARGS ((KwCb *gCb,KwDatIndInfo *datIndInfo));
EXTERN PUBLIC S16 kwUtlSndDatInd ARGS ((KwCb *gCb,KwUlRbCb *rbCb, Buffer *sdu));
EXTERN Void kwUtlFreeUlRbCb ARGS ((KwCb *gCb, KwUlRbCb *rbCb));
/* Activation functions */
EXTERN S16 kwUlActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 kwUlActvTsk ARGS ((
Pst *pst,              /* pst structure */
Buffer *mBuf            /* message buffer */
));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __KWX__ */

  
/********************************************************************30**
  
         End of file:     kw_ul.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:53 2014
  
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

