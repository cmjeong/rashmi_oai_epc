

/********************************************************************20**

     Name:    PDCP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    pjac_acc.x

     Sid:      pjac_acc.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:41 2015

     Prg:     Adarsh 
*********************************************************************21*/

#ifndef __PJAC_ACC_X__
#define __PJAC_ACC_X__
#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/


/* Common interface element */
typedef struct kwAcCmInfo
{
   SuId                    suId;
   SpId                    spId;
   Reason                  reason;
   Buffer                  mBuf;
} KwAcCmInfo;


typedef struct kwAcDatCfm
{
   KwuDatCfmInfo           cfmInfo;
} KwAcDatCfm;

typedef struct kwAcStaInd
{
   CmLteRlcId              rlcId;
} KwAcStaInd;

typedef struct kwAcKwuInfo
{
   SuId                    suId;
   SpId                    spId;
   Reason                  reason;
   KwAcCmInfo              cmInfo;
   union {
      Status               status;
      KwuDatReqInfo        *datReq;
      KwuDatIndInfo        *datInd;
      KwuDatCfmInfo        *datCfm;
      KwuStaIndInfo        *staInd;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
      KwuDiscSduInfo       *discSduCfm;
      KwuDatAckInfo        *datAckInd;
#endif
   }u;
} KwAcKwuInfo;

typedef struct kwAcCpjInfo
{
   KwAcCmInfo              cmInfo;
   union {
      Status                  status;
      CpjCfgCfmInfo           *cfgCfm;
      CpjSecCfgCfmInfo        *secCfgCfm;
      CpjReEstCfmInfo         *reEstCfm;
      CpjCountCfmInfo         *countCfm;
      CpjSduStaCfmInfo        *sduStaCfm;
      CpjDatResumeCfmInfo     *datResCfm;
   }u;
} KwAcCpjInfo;

typedef struct kwAcPjuInfo
{
   KwAcCmInfo              cmInfo;
   CmLtePdcpId             *pdcpId;
   union {
      Status               status;
      PjuDatCfmInfo        *datCfm;
      PjuStaIndInfo        *staInd;
      PjuDatFwdIndInfo     *datFwdInd;
   }u;
} KwAcPjuInfo;

/* Message queue element */
typedef struct kwAcMsgQElm
{
   Pst                     pst;              /* pst structure         */
   Buffer                  *mBuf;
   union 
   {
       KwAcKwuInfo         kwuInfo;
      /* kw005.201 added support for L2 Measurement */
       PjMngmt             pjMngmt;
       KwAcCpjInfo         cpjInfo;
       KwAcPjuInfo         pjuInfo;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
       PjL2MeasCfmEvt      pjMeasCfmEvt;
#endif
   }u;

   PMSGFREEFS16            msgFreeFun;       /* Function to free the msg */
} KwAcMsgQElm;

/** @struct PjAcKwuDatReq
 * Maints the KWU Sap Data Request Information
 */
typedef struct pjAcKwuDatReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   U8                      entity;                 /*!< Entity - NH/PJ */
   U32                     sduSize;                /*!< SDU Size */
   KwuDatReqInfo           *datReq;                 /*!< Data Request
                                                     Information*/
   U32                     transId;
   Buffer                  *mBuf;                   /*!< SDU */
} PjAcKwuDatReq;

/** @struct PjAcKwuDatCfm
 * Maints the KWU Sap Data Request Information
 */
typedef struct kwAcKwuDatCfm
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   U32                     sduId;                  /*!< SDU id */
} PjAcKwuDatCfm;


/** @struct PjAcKwuDatReqQ
 * Circular Q for KwuDatReq
 */
typedef struct pjAcKwuDatReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   PjAcKwuDatReq           node[PJAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} PjAcKwuDatReqQ;

/** @struct PjAcKwuDatCfmQ
 * Circular Q for KwuDatReq
 */
typedef struct pjAcKwuDatCfmQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   PjAcKwuDatCfm           node[PJAC_MAX_CIRCQ_SIZE];    /*!< Data Confirm node */
} PjAcKwuDatCfmQ;

/** @struct KwAcKwuCb
 * KWU SAP Information
 */
typedef struct kwAcKwuCb
{
   SuId                    suId;          /*!< Service User Id */
   SpId                    spId;          /*!< Service Provider Id */
   S16                     nxtSduId;      /*!< counter for tracking the sdu's */
   U32                     nxtTransId;    /*!< Next Transaction id to use */
   PjAcKwuDatReqQ          datReq;        /*!< Data Request Queue */
   PjAcKwuDatCfmQ          datCfm;        /*!< Data Confirm Queue */
} KwAcKwuCb;


typedef struct kwAcLcInfo
{
   U8                     lcId;        /*!< Logical Channel Id */
   U8                     lcType;      /*!< Logical Channel Type */
} KwAcLcInfo;

/** @struct KwAcCpjcfgReq
 * Configuration Information
 */
typedef struct kwAcCpjCfgReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   Pst                     pst;                    /*!< Post structure */
   CpjCfgReqInfo           cfgInfo;                /*!< Configuration info */
} KwAcCpjCfgReq;

/** @struct KwAcCpjCfgReqQ
 * Circular Q for CpjCfgReq
 */
typedef struct kwAcCpjCfgReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcCpjCfgReq           node[PJAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} KwAcCpjCfgReqQ;

/** @struct KwAcCpjReEstReq
 * Re-establishment Information
 */
typedef struct kwAcCpjReEstReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   Pst                     pst;                    /*!< Post structure */
   CpjReEstReqInfo         cfgInfo;                /*!< Re-establishment info */
} KwAcCpjReEstReq;

/** @struct KwAcCpjReEstReqQ
 * Circular Q for CpjReEstReq
 */
typedef struct kwAcCpjReEstReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcCpjReEstReq         node[PJAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} KwAcCpjReEstReqQ;

/** @struct KwAcCpjSecCfgReq
 * Security Configuration Information
 */
typedef struct kwAcCpjSecCfgReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   Pst                     pst;                    /*!< Post structure */
   CpjSecCfgReqInfo        cfgInfo;                /*!< Security configuration info */
} KwAcCpjSecCfgReq;

/** @struct KwAcCpjSecCfgReqQ
 * Circular Q for CpjSecCfgReq
 */
typedef struct kwAcCpjSecCfgReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcCpjSecCfgReq        node[PJAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} KwAcCpjSecCfgReqQ;

/** @struct KwAcCpjCb
 * Maintains the CPJ SAP Information
 */
typedef struct kwAcCpjCb
{
   SuId                    suId;                   /*!< Service User Id */
   SpId                    spId;                   /*!< Service Provider Id */
   U32                     nxtTransId;             /*!< Next Transaction id to
                                                      use */
   Bool                    cipInitFail;            /*!< Ciphering Security 
                                                      Init Req Fail */
   Bool                    intInitFail;            /*!< Integrity Security 
                                                      Init Req Fail */
   Bool                    resetFlag;              /*!< Reset flag */
   Bool                    saveMsg;                /*!< Reset flag */
   KwAcCpjCfgReqQ          cfgReq;                 /*!< Configuration Request
                                                     Circular Q */
   KwAcCpjReEstReqQ        reEstReq;               /*!< Re-establishment Request
                                                     Circular Q */
   KwAcCpjSecCfgReqQ       secCfgReq;              /*!< Security Configuration
                                                      Request Circular Q */
} KwAcCpjCb;

/** @struct KwAcPjuDatReq
 * Maints the PJU Sap Data Request Information
 */
typedef struct kwAcPjuDatReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   U8                      entity;                 /*!< Entity - NH/PJ */
   U16                     sduSize;                /*!< SDU Size */
   U32                     sduId;                  /*!< SDU ID */
   CmLtePdcpId             pdcpId;                 /*!< PDCP ID */
   U32                     transId;
   Buffer                  *mBuf;                  /*!< SDU */
} KwAcPjuDatReq;

/** @struct KwAcPjuDatReqQ
 * Circular Q for PjuDatReq
 */
typedef struct kwAcPjuDatReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcPjuDatReq           node[PJAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} KwAcPjuDatReqQ;

/** @struct KwAcPjuCb
 * Maintains the PJU SAP Information
 */
typedef struct kwAcPjuCb
{
   SuId                    suId;          /*!< Service User Id */
   SpId                    spId;          /*!< Service Provider Id */
   S16                     nxtSduId[PJAC_MAX_CELL+1][32][2][32];      /*!< counter for tracking the sdu's */
   U32                     nxtTransId;    /*!< Next Transaction id to use */
   KwAcPjuDatReqQ          datReq;        /*!< Data Request Circular Q */
} KwAcPjuCb;

/** @struct KwAcDirective
 * Maintains the information for OBD.
 */
typedef struct kwAcDirective
{
   U32            id;                     /*!< Index at which it should be saved */
   Bool           feedback;               /*!< Is feedback necessary */
   Bool           seqStart;               /*!< Start sequence numbering */
   Bool           seqOn;                  /*!< Sequence numbering is on */
   Bool           cmpInitFail;            /*!< Compression Init should fail */
   Bool           intInitFail;            /*!< Integrity Init should fail */
   Bool           cmpFail;                /*!< Compression  should fail */
   Bool           intProtFail;            /*!< Integrity Protection  should fail */
   Bool           cipFail;                /*!< Ciphering  should fail */
   Bool           decmpFail;              /*!< Decompression  should fail */
   Bool           intVerFail;             /*!< Integrity Verification  should fail */
   Bool           decipFail;              /*!< Deciphering should fail */
   Bool           saveCmpMsg;             /*!< Should save message at compression */
   Bool           saveIntMsg;             /*!< Should save message at Integrity */
   Bool           saveCpMsg;              /*!< Should save message at Ciphering */
   Bool           saveDecmpMsg;           /*!< Should save message at Decompression */
   Bool           saveIntVerMsg;          /*!< Should save message at Int Ver */
   Bool           saveDecpMsg;            /*!< Should save deciphering message */

   U16            numPosTc;               /*!< Number of positive TCs */
   U16            numNegTc;               /*!< Number of Negative TCs */
} KwAcDirective;

/** @struct KwAcLcCb
 * Maintains the Logical Channel information in MAC (both uplink and downlink)
 */
typedef struct kwAcLcCb
{
   U8                     dir;         /*!< Direction */
   U8                     mode;        /*!< Mode */
   U8                     snType;      /*!< Mode */
   KwAcLcInfo             dlLc;        /*!< Logical Channel Info */
   KwAcLcInfo             ulLc;        /*!< Logical Channel Info in opposite
                                         direction */
   U8                     rbId;        /*!< RB Id */
   U8                     rbType;      /*!< RB Type */
   CmLteRlcId             othRlcId;    /*!< RLC Id */
} KwAcLcCb;

/** @struct KwAcRbCb
 * Maintains the Rbs configured and corresponding Data Request and Data Confirm
 */
typedef struct kwAcRbCb
{
   U8                     dir;         /*!< Direction */
   U8                     mode;        /*!< Mode */
   U8                     snType;      /*!< Mode */
   U8                     rbId;        /*!< RB Id */
   U8                     rbType;      /*!< RB Type */
   CmLteRlcId             othRlcId;    /*!< RLC Id */
   KwAcLcInfo             dlLc;        /*!< Logical Channel configured int the
                                          direction */
   KwAcLcInfo             ulLc;        /*!< Logical Channel configured in
                                          opposite direction */
} KwAcRbCb;

/** @struct KwAcMapDlUl
 * Maintains the mapping between Downlink and Uplink Logical Channels
 * per UE/CELL
 */
typedef struct kwAcMapDlUl
{
   CmLteRnti              ueId;                    /*!< UE Identifier */
   CmLteCellId            cellId;                  /*!< Cell Identifier */
   U8                     numRb;                   /*!< Number of Rbs */
   KwAcRbCb               srbCb[PJAC_MAX_SRB];     /*!< Rbs configured */
   KwAcRbCb               drbCb[PJAC_MAX_DRB];     /*!< Rbs configured */
   KwAcLcCb               lcCb[PJAC_MAX_LC];       /*!< Downlink Channel
                                                     Information */
} KwAcMapDlUl;

/** @struct KwAcMapDlUlCb
 * Maintains the DL to Ul mapping for UE/Cell
 */
typedef struct kwAcMapDlUlCb
{
   U8                     count;                   /*!< Number of Mappings */
   KwAcMapDlUl            mapDlUl[PJAC_MAX_SIZE];  /*!< DL to UL Mapping entries */
} KwAcMapDlUlCb;

/** @struct KwAcCb
 * Test Engine global Control block for storing
 * All Requests to verify at the time of response */
typedef struct _kwAcCb
{
   Bool                   isRxTst;                 /*!< Is this Testcase is only
                                                     recieption side */
   CmXtaTCCb              *tcCb;                   /*!< Testcase Cb */
   CmXtaSpCb              *spCb;                   /*!< Stack pointer cb */
   KwAcDirective          directive;               /*!< Directives for offboard */
   KwAcCpjCb              nhCpjCb;                 /*!< RRC CPJ Interface CB */
   KwAcPjuCb              nhPjuCb;                 /*!< RRC PJU Interface CB */
   KwAcPjuCb              pxPjuCb;                 /*!< Relay PJU Interface CB */
   KwAcKwuCb              pjKwuCb;                 /*!< PDCP KWU Interface CB */
   KwAcMapDlUlCb          mapDlUlCb;               /*!< DL to UL Mapping */
} KwAcCb;


EXTERN U32  Nr;
EXTERN U32  Nk;

EXTERN KwAcCb kwAcCb;
EXTERN KwuUbndReq pjLiKwuUbndReqMt[4];
EXTERN KwuBndReq pjLiKwuBndReqMt[4];
EXTERN KwuDatReq pjLiKwuDatReqMt[4];
EXTERN KwuDiscSduReq pjLiKwuDiscSduReqMt[4];

EXTERN S16 kwAcCkwInit ARGS((Void));
EXTERN S16 kwAcKwuInit ARGS((Void));
EXTERN S16 kwAcLkwInit ARGS((Void));
EXTERN S16 kwAcKwuDeInit ARGS((Void));
EXTERN S16 kwAcCkwDeInit ARGS((Void));
EXTERN S16 kwAcLkwDeInit ARGS((Void));

EXTERN CmXtaTCCb*  kwAcCkwTstCbFind ARGS((Void));
EXTERN S16 kwAcCkwSendMsg ARGS((
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr
));
EXTERN CmXtaTCCb*  kwAcKwuTstCbFind ARGS((Void));
EXTERN S16 kwAcKwuSendMsg ARGS((
Pst            *pst,
SpId           suId,
U8             status,
Void           *ptr,
Buffer         *mBuf
));
EXTERN S16 NhLiKwuDiscSduReq ARGS((
Pst               *pst,
SpId              spId,
KwuDiscSduInfo    *discSdu
));
EXTERN S16 nhInitExt ARGS((Void));
EXTERN S16 pjInitExt ARGS((Void));
EXTERN CmXtaTCCb*  kwAcRguTstCbFind ARGS((Void));
EXTERN S16 kwAcRguSendMsg ARGS((
Pst            *pst,
SuId           suId,
SpId           spId,
Reason         reason,
Void           *ptr
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
EXTERN S16 kwAcUtlValdtL2MUlThrpMeasReq ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwuuL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
));
#endif
#endif
EXTERN S16 rgInitExt ARGS((Void));
EXTERN CmXtaTCCb*  kwAcLkwTstCbFind ARGS((Void));
EXTERN S16 SmMiLpjSendMsg ARGS((
Pst         *pst,
PjMngmt     *cfm,
Buffer      *mBuf
));

EXTERN S16 pjAcCpjInit ARGS((Void));
EXTERN S16 pjAcPjuInit ARGS((Void));
EXTERN S16 pjAcLpjInit ARGS((Void));
EXTERN S16 pjAcObdInit ARGS((Void));
EXTERN S16 pjAcObdDeInit ARGS(( Void));
EXTERN S16 pjAcCpjDeInit ARGS((Void));
EXTERN S16 pjAcPjuDeInit ARGS((Void));
EXTERN S16 pjAcLpjDeInit ARGS((Void));
EXTERN CmXtaTCCb*  pjAcCpjTstCbFind ARGS((Void));
EXTERN CmXtaTCCb*  pjAcPjuTstCbFind ARGS((Void));
EXTERN S16 pjAcCpjSendMsg ARGS((
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr
));
EXTERN S16 pjAcPjuSendMsg ARGS((
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr,
Void           *ptr2,
Buffer         *mBuf
));

EXTERN S16 pjAcUtlKwuPdcpExtractUmHdr ARGS((Buffer* mBuf,Buffer **pdcpBuf,U16 snType));
EXTERN S16 pjAcUtlKwuPdcpExtractAmHdr ARGS((Buffer* mBuf,Buffer **pdcpBuf));



/****************************************************************************
 *                      EXTERN Declarations
 ***************************************************************************/
EXTERN S16 nhActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 nhActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));
#ifndef KW_PDCP
EXTERN S16 pjActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 pjActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));
#endif 

EXTERN S16 rgActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 rgActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

#ifdef KW_PDCP
EXTERN S16 pxActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 pxActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 nxInitExt ARGS((Void));

EXTERN S16 osActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 osActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 osInitExt ARGS((Void));

EXTERN S16 ocActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 ocActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 ocInitExt ARGS((Void));
/* Venki - #ifndef KW_PDCP */
#else

EXTERN S16 kwDlActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 kwUlActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 pxActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 pxActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 kwDlActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 kwUlActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 nxInitExt ARGS((Void));

EXTERN S16 osActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 osActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 osInitExt ARGS((Void));

EXTERN S16 ocActvInit ARGS ((
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
));

EXTERN S16 ocActvTsk ARGS ((
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
));

EXTERN S16 ocInitExt ARGS((Void));
#endif /* KW_PDCP */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __PJAC_ACC_X__ */


/********************************************************************30**

         End of file:     pjac_acc.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:41 2015

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
/main/1      ---      vb        1. LTE PDCP Initial release 2.1
*********************************************************************91*/
