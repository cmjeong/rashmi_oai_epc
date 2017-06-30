

/********************************************************************20**

     Name:    RLC - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    kwac_acc.x

     Sid:      kwac_acc.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:21 2014

     Prg:     cp 
*********************************************************************21*/

#ifndef __KWAC_ACC_X__
#define __KWAC_ACC_X__
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

typedef struct kwAcCkwInfo
{
   KwAcCmInfo              cmInfo;
   Status                  status;
   CkwCfgCfmInfo           *cfgCfm;
} KwAcCkwInfo;

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
   KwAcCmInfo              cmInfo;
   union {
      Status               status;
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

/**
 * @struct rgAcRguInfo
 * Holds interface primitives received from MAC to Dummy-RLC.
 */
typedef struct kwAcRguInfo
{
   SuId                    suId;
   SpId                    spId;
   Reason                  reason;
   union 
   {
      RguCDatReqInfo       *cDatReq;
      RguDDatReqInfo       *dDatReq;
      RguCStaRspInfo       *cStaRsp;
      RguDStaRspInfo       *dStaRsp;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
      RguL2MUlThrpMeasReqInfo  *l2mUlThrpMeasReq;
#endif
#endif
   }u;
} KwAcRguInfo;

#ifdef KW_PDCP
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

#endif /* KW_PDCP */

/* Message queue element */
typedef struct kwAcMsgQElm
{
   Pst                     pst;              /* pst structure         */
   Buffer                  *mBuf;
   union 
   {
       KwMngmt             kwMngmt;
       KwAcCkwInfo         ckwInfo;
       KwAcKwuInfo         kwuInfo;
       KwAcRguInfo         rguInfo;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
       KwL2MeasCfmEvt      kwMeasCfmEvt;
#endif
#ifdef KW_PDCP
       PjMngmt             pjMngmt;
       KwAcCpjInfo         cpjInfo;
       KwAcPjuInfo         pjuInfo;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
       PjL2MeasCfmEvt      pjMeasCfmEvt;
#endif
#endif
   }u;

   PMSGFREEFS16            msgFreeFun;       /* Function to free the msg */
} KwAcMsgQElm;

/** @struct KwAcCkwCfgReq
 * Configuration Information
 */
typedef struct kwAcCkwCfgReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   Pst                     pst;                    /*!< Post structure */
   CkwCfgInfo              cfgInfo;                /*!< Configuration info */
} KwAcCkwCfgReq;

/** @struct KwAcKwuDatReq
 * Maints the KWU Sap Data Request Information
 */
typedef struct kwAcKwuDatReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   U8                      entity;                 /*!< Entity - NH/PJ */
   U32                     sduSize;                /*!< SDU Size */
   KwuDatReqInfo           datReq;                 /*!< Data Request
                                                     Information*/
   Buffer                  *mBuf;                   /*!< SDU */
} KwAcKwuDatReq;

/** @struct KwAcKwuDatCfm
 * Maints the KWU Sap Data Request Information
 */
typedef struct kwAcKwuDatCfm
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   U32                     sduId;                  /*!< SDU id */
} KwAcKwuDatCfm;

/** @struct KwAcCkwCircQ
 * Circular Q for tracking Configurations
 */
typedef struct kwAcCkwCircQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcCkwCfgReq           node[KWAC_MAX_CIRCQ_SIZE];/*!< Configuration node */
} KwAcCkwCircQ;

/** @struct KwAcCkwCb
 * CKW SAP Information */
typedef struct kwAcCkwCb
{
   SuId                    suId;                   /*!< Service User Id */
   SpId                    spId;                   /*!< Service Provider Id */
   U32                     nxtTransId;             /*!< Next Transaction id to
                                                      use */
   KwAcCkwCircQ            cfgReq;                 /*!< Configuration Request
                                                      Circular Q */
} KwAcCkwCb;

/** @struct KwAcKwuDatReqQ
 * Circular Q for KwuDatReq
 */
typedef struct kwAcKwuDatReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcKwuDatReq           node[KWAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} KwAcKwuDatReqQ;

/** @struct KwAcKwuDatCfmQ
 * Circular Q for KwuDatReq
 */
typedef struct kwAcKwuDatCfmQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcKwuDatCfm           node[KWAC_MAX_CIRCQ_SIZE];    /*!< Data Confirm node */
} KwAcKwuDatCfmQ;

/** @struct KwAcKwuCb
 * KWU SAP Information
 */
typedef struct kwAcKwuCb
{
   SuId                    suId;          /*!< Service User Id */
   SpId                    spId;          /*!< Service Provider Id */
   S16                     nxtSduId;      /*!< counter for tracking the sdu's */
   U32                     nxtTransId;    /*!< Next Transaction id to use */
   KwAcKwuDatReqQ          datReq;        /*!< Data Request Queue */
   KwAcKwuDatCfmQ          datCfm;        /*!< Data Confirm Queue */
} KwAcKwuCb;

/** @struct KwAcRguDStaRsp
 * Contains BO
 */
typedef struct kwAcRguDStaRsp
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   S32                     bo;                     /*!< BO */
} KwAcRguDStaRsp;

/** @struct KwAcRguDStaRspQ
 * Circular Q for RguDStaRsp
 */
typedef struct kwAcRguDStaRspQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Front Index */
   KwAcRguDStaRsp          node[KWAC_MAX_CIRCQ_SIZE];   /*!< Dedicated Channel Status
                                                     Response node */
} KwAcRguDStaRspQ;

/** @struct KwAcRguCStaInd
 * Contains CStaInd
 */
typedef struct kwAcRguCStaInd
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   RguCStaIndInfo          cStaInd;                /*!< Common Channel
                                                     Status Indication */
} KwAcRguCStaInd;

/** @struct KwAcRguCStaIndQ
 * Circular Q for RguCStaInd
 */
typedef struct kwAcRguCStaIndQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Front Index */
   KwAcRguCStaInd          node[KWAC_MAX_CIRCQ_SIZE];    /*!< DStaInd Queue */
} KwAcRguCStaIndQ;

/** @struct KwAcRguDStaInd
 * Contains DStaInd
 */
typedef struct kwAcRguDStaInd
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   RguDStaIndInfo          dStaInd;                /*!< Dedicated Channel
                                                     Status Indication */
} KwAcRguDStaInd;

/** @struct KwAcRguDStaIndQ
 * Circular Q for RguDStaInd
 */
typedef struct kwAcRguDStaIndQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Front Index */
   KwAcRguDStaInd          node[KWAC_MAX_CIRCQ_SIZE];    /*!< DStaInd Queue */
} KwAcRguDStaIndQ;

/** @struct KwAcRguCDatReq
 * Contains CDatReq
 */
typedef struct kwAcRguCDatReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   RguCDatReqInfo          *cDatReq;                /*!< Dedicated Channel
                                                     Status Indication */
} KwAcRguCDatReq;

/** @struct KwAcRguCDatReqQ
 * Circular Q for RguCDatReq
 */
typedef struct kwAcRguCDatReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcRguCDatReq          node[KWAC_MAX_CIRCQ_SIZE];   /*!< Common Channel Data
                                                     Request node */
} KwAcRguCDatReqQ;

/** @struct KwAcRguDDatReq
 * Contains DDatReq
 */
typedef struct kwAcRguDDatReq
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   Bool                    isRem[10][10];          /*!< Is pdus are removed */
   Bool                    isLchRem[10];           /*!< Is pdus are removed */
   RguDDatReqInfo          *dDatReq;               /*!< Dedicated Channel
                                                     Status Indication */
} KwAcRguDDatReq;

/** @struct KwAcRguDDatReqQ
 * Circular Q for RguDDatReq
 */
typedef struct kwAcRguDDatReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Front Index */
   KwAcRguDDatReq          node[KWAC_MAX_CIRCQ_SIZE];   /*!< Dedicated Channel Data
                                                     Request node */
} KwAcRguDDatReqQ;

/** @struct KwAcRguCDatInd
 * Contains CDatInd
 */
typedef struct kwAcRguCDatInd
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   RguCDatIndInfo          *dDatInd;                /*!< Dedicated Channel
                                                     Status Indication */
} KwAcRguCDatInd;

/** @struct KwAcRguCDatIndQ
 * Circular Q for RguCDatInd
 */
typedef struct kwAcRguCDatIndQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcRguCDatInd          node[KWAC_MAX_CIRCQ_SIZE];   /*!< Common Channel Data
                                                     Indication node */
} KwAcRguCDatIndQ;

/** @struct KwAcRguDDatInd
 * Contains DDatInd
 */
typedef struct kwAcRguDDatInd
{
   Bool                    isInQ;                  /*!< Is this message still in
                                                     Queue */
   RguDDatIndInfo          *dDatInd;                /*!< Dedicated Channel
                                                     Status Indication */
} KwAcRguDDatInd;

/** @struct KwAcRguDDatIndQ
 * Circular Q for RguDDatInd
 */
typedef struct kwAcRguDDatIndQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Front Index */
   KwAcRguDDatInd          node[KWAC_MAX_CIRCQ_SIZE];   /*!< Dedicated Channel Data
                                                     Indication node */
} KwAcRguDDatIndQ;

/** @struct KwAcLcInfo
 * Contains the Logical Channel Information
 */
typedef struct kwAcLcInfo
{
   U8                     lcId;        /*!< Logical Channel Id */
   U8                     lcType;      /*!< Logical Channel Type */
} KwAcLcInfo;

/** @struct KwAcRguCb
 * Maintains the RGU SAP Information
 */
typedef struct kwAcRguCb
{
   SuId                    suId;                   /* Service User Id */
   SpId                    spId;                   /* Service Provider Id */
   U32                     nxtTransId;

   /* cStaRsp, dStaRsp, and cStaInd Info are not required */
   KwAcRguDStaIndQ        dStaInd;     /*!< Dedicated Channel Status Indication
                                         Info */
   KwAcRguCDatReqQ        cDatReq;     /*!< Common Channel Data Request Info */
   KwAcRguDDatReqQ        dDatReq;     /*!< Dedicated Channel Data Request Info
                                         */
   KwAcRguCDatIndQ        cDatInd;     /*!< Common Channel Data Indication */
   KwAcRguDDatIndQ        dDatInd;     /*!< Dedicatd Channel Data Indicaiton */
} KwAcRguCb;

#ifdef KW_PDCP
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
   KwAcCpjCfgReq           node[KWAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
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
   KwAcCpjReEstReq         node[KWAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
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
   KwAcCpjSecCfgReq        node[KWAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
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
   Buffer                  *mBuf;                  /*!< SDU */
} KwAcPjuDatReq;

/** @struct KwAcPjuDatReqQ
 * Circular Q for PjuDatReq
 */
typedef struct kwAcPjuDatReqQ
{
   U16                     front;                  /*!< Front Index */
   U16                     rear;                   /*!< Rear Index */
   KwAcPjuDatReq           node[KWAC_MAX_CIRCQ_SIZE];    /*!< Data Request node */
} KwAcPjuDatReqQ;

/** @struct KwAcPjuCb
 * Maintains the PJU SAP Information
 */
typedef struct kwAcPjuCb
{
   SuId                    suId;          /*!< Service User Id */
   SpId                    spId;          /*!< Service Provider Id */
   S16                     nxtSduId;      /*!< counter for tracking the sdu's */
   U32                     nxtTransId;    /*!< Next Transaction id to use */
   KwAcPjuDatReqQ          datReq;        /*!< Data Request Circular Q */
} KwAcPjuCb;
#endif /* KW_PDCP */

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
   KwAcRbCb               srbCb[KWAC_MAX_SRB];     /*!< Rbs configured */
   KwAcRbCb               drbCb[KWAC_MAX_DRB];     /*!< Rbs configured */
   KwAcLcCb               lcCb[KWAC_MAX_LC];       /*!< Downlink Channel
                                                     Information */
} KwAcMapDlUl;

/** @struct KwAcMapDlUlCb
 * Maintains the DL to Ul mapping for UE/Cell
 */
typedef struct kwAcMapDlUlCb
{
   U8                     count;                   /*!< Number of Mappings */
   KwAcMapDlUl            mapDlUl[KWAC_MAX_SIZE];  /*!< DL to UL Mapping entries */
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
   KwAcCkwCb              ckwCb;                   /*!< RRC CKW Interface CB */
   KwAcKwuCb              nhKwuCb;                 /*!< RRC KWU Interface CB */
   KwAcDirective          directive;               /*!< Directives for offboard */
#ifdef KW_PDCP
   KwAcCpjCb              nhCpjCb;                 /*!< RRC CPJ Interface CB */
   KwAcPjuCb              nhPjuCb;                 /*!< RRC PJU Interface CB */
   KwAcPjuCb              pxPjuCb;                 /*!< Relay PJU Interface CB */
#else
   KwAcKwuCb              pjKwuCb;                 /*!< PDCP KWU Interface CB */
#endif /* KW_PDCP */
   KwAcRguCb              rguCb;                   /*!< MAC RGU Interface CB */
   KwAcMapDlUlCb          mapDlUlCb;               /*!< DL to UL Mapping */
} KwAcCb;


EXTERN U32  Nr;
EXTERN U32  Nk;

EXTERN KwAcCb kwAcCb;

EXTERN S16 kwAcCkwInit ARGS((Void));
EXTERN S16 kwAcKwuInit ARGS((Void));
EXTERN S16 kwAcLkwInit ARGS((Void));
EXTERN S16 kwAcRguInit ARGS((Void));
EXTERN S16 kwAcKwuDeInit ARGS((Void));
EXTERN S16 kwAcCkwDeInit ARGS((Void));
EXTERN S16 kwAcLkwDeInit ARGS((Void));
EXTERN S16 kwAcRguDeInit ARGS((Void));

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
EXTERN S16 kwAcUtlRguExtractUmHdr ARGS((Buffer* mBuf,KwUmHdr *hdr,U16 snType));
EXTERN S16 kwAcUtlRguExtractAmHdr ARGS((Buffer* mBuf,KwAmHdr *hdr));
EXTERN S16 kwAcUtlRguExtractAmdPduSegHdr ARGS((Buffer* buf,KwAmHdr *hdr));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 kwAcUtlBuildRguHqStaInd ARGS((CmXtaTCCb   *tcCb, CmXtaSpCb    *spCb,
RguHarqStatusInd  *hqStaInd));
EXTERN S16 SmMiLkwSendL2MeasMsg ARGS((
Pst         *pst,
KwL2MeasCfmEvt *measEvt
));
EXTERN Void kwAcUtlLkwBuildL2MeasReq  ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
KwL2MeasReqEvt *l2MeasReqEvt
));
EXTERN S16 kwAcUtlLkwVldtL2MeasCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
KwL2MeasCfmEvt *l2MeasCfmEvt
));
#ifdef LTE_RLC_R9
EXTERN S16 kwAcUtlValdtL2MUlThrpMeasReq ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
));
#endif
#endif
EXTERN S16 rgInitExt ARGS((Void));
EXTERN CmXtaTCCb*  kwAcLkwTstCbFind ARGS((Void));
EXTERN S16 SmMiLkwSendMsg ARGS((
Pst         *pst,
KwMngmt     *cfm,
Buffer      *mBuf
));
EXTERN S16 kwAcUtlKwVerifyStsCfm ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwSts         *sts
));
EXTERN S16 kwAcUtlKwVerifyStaCfm ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwSSta        *sta
));
EXTERN S16 kwAcUtlKwVerifyStaInd ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwUSta        *usta
));
EXTERN S16 kwAcUtlKwVerifyTrcInd ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwTrc         *trc
));

#ifdef KW_PDCP
EXTERN S16 kwAcCpjInit ARGS((Void));
EXTERN S16 kwAcPjuInit ARGS((Void));
EXTERN S16 kwAcLpjInit ARGS((Void));
EXTERN S16 kwAcObdInit ARGS((Void));
EXTERN S16 kwAcObdDeInit ARGS(( Void));
EXTERN S16 kwAcCpjDeInit ARGS((Void));
EXTERN S16 kwAcPjuDeInit ARGS((Void));
EXTERN S16 kwAcLpjDeInit ARGS((Void));
EXTERN CmXtaTCCb*  kwAcCpjTstCbFind ARGS((Void));
EXTERN CmXtaTCCb*  kwAcPjuTstCbFind ARGS((Void));
EXTERN S16 kwAcCpjSendMsg ARGS((
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr
));
EXTERN S16 kwAcPjuSendMsg ARGS((
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr,
Void           *ptr2,
Buffer         *mBuf
));

EXTERN S16 kwAcUtlRguPdcpExtractUmHdr ARGS((Buffer* mBuf,Buffer **pdcpBuf,U16 snType));
EXTERN S16 kwAcUtlRguPdcpExtractAmHdr ARGS((Buffer* mBuf,Buffer **pdcpBuf));
#endif /* KW_PDCP */








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


#endif /* KW_PDCP */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __KWAC_ACC_X__ */


/********************************************************************30**

         End of file:     kwac_acc.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:21 2014

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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3      kw005.201 ap     1. Added support for L2 Measurement.
*********************************************************************91*/

