

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE MAC
 
    File:   kw_udx.x
 
    Sid:      kw_udx.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:52 2014
 
    Prg:   mraj
 
**********************************************************************/
/** @file kw_udx.x
@brief This file contains basic data structures for the Uplink Downlink 
interface.
*/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/
 
#ifndef __UDX__
#define __UDX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define KW_UDX_MAX_NACK_CNT   100
#define KW_UDX_MAX_CNTRL_INFO   100


#ifdef UDX_CKW_AVAILABLE
typedef CkwUeInfo  UdxUeInfo;
typedef CkwCfgInfo UdxCfgInfo;
typedef CkwCfgCfmInfo UdxCfgCfmInfo;
#else
/** @brief
   Logical Channel Information */
typedef struct udxLChInfo
{
   U8   lChId;       /*!< Logical Channel ID.
                        The allowed values are [1..10] */
   U8    type;        /*!< Logical Channel Type - 
                           BCCH/PCCH/CCCH/DTCH/DCCH */
}UdxLChInfo;

/** @brief
   Un-acknowledge Mode Information */
typedef struct udxUmInfo
{
   struct   _umUdxDl
   {
      U8     snLen;   /*!< Sequence Number length in bits. */
                      /*!  Allowed values are 5 and 10*/
   }dl;                   /*!< Downlink */
   struct   _umUdxUl
   {
      U8      snLen;               /*!< Sequence Number length in bits.*/
                                   /*!< Allowed values are 5 and 10*/
      U8      reOrdTmr;            /*!< T_reordering Timer in msec */
   }ul;                            /*!< Uplink */
}UdxUmInfo;

/** @brief
   Acknowledge Mode Information */
typedef struct udxAmInfo
{
   struct   _amUdxDl
   {
      U16  pollRetxTmr;    /*!< T_poll_retransmit Timer in msec */
      S16  pollPdu;        /*!< Used to trigger a poll for every pollPdu.*/
                           /*!< This field indicates the number of PDUs */
                           /* !<For Infinite, RLC expects value 0xFFFF */
      S32  pollByte;       /*!< Poll_Byte in bytes. */
                           /*!<For Infinite RLC expects value 0xFFFFFFFF */
      U8   maxRetx;        /*!< Max_Retx_Threshold */
   }dl;                    /*!< Down link */
   struct   _amUdxUl
   {
      U16  staProhTmr;      /*!< T_status_prohibit Timer in msec*/
      U8   reOrdTmr;        /*!< T_reordering Timer in msec*/
   }ul;                     /*!< Up link */
}UdxAmInfo;

/** @brief
   Transparent Mode Information */
typedef union udxTmInfo
{
   struct   _tmUdxDl
   {
      U32      buffSize;     /*!< Buffer Size in bytes */
   }dl;                      /*!< Down link */
}UdxTmInfo;

/** @brief
   Entity Configuration Information */
typedef struct udxEntCfgInfo
{
   U8  cfgType;     /*!< Type of Configuration - 
                         ADD/MODIFY/DELETE/RE-ESTABLISH/
                        DELTEUE */
   U8  rbId;                /* RB ID. The allowed Values are [0..255] */
   U8  rbType;              /* Type of the RB - can be SRB or DRB */
#ifdef LTE_L2_MEAS
   U8   qci;                /*!< qCI value Associated with that RB */
#endif /* LTE_L2_MEAS */
   UdxLChInfo   lCh[CM_LTE_MAX_LOGCH_PER_RB];  /*!< Logical channel
                                                        information
                                                In case of AM mode: 
                                                idx = 0 implies DL and
                                                idx = 1 implies UL
                                                In case of TM/UM idx 0 is only
                                                applicable */
   CmLteRlcMode    entMode;   /*!< Entity mode: AM, UM or TM */
   U8              dir;       /*!< Direction: It can be either
                                       UL / DL for TM mode 
                                       UL / DL or BOTH for UM mode 
                                       and for AM its always for both UL 
                                       and DL. */
   union
   {
      UdxUmInfo   umInfo;        /*!< Un-acknowledged Mode Information */
      UdxAmInfo   amInfo;        /*!< Acknowledged Mode Information */
      UdxTmInfo   tmInfo;        /*!< Transparent Mode Information */
   }m;
}UdxEntCfgInfo;

/** @brief
   Configuration Information from RRC to RLC */
typedef struct udxCfgInfo
{
   U32           transId;         /*!< Transaction Id */
   CmLteRnti     ueId;            /*!< UE ID */
   CmLteCellId   cellId;          /*!< Cell ID */
   U8            numEnt;          /*!< Number of entities to configure */
   UdxEntCfgInfo     entCfg[UDX_MAX_ENT_CFG];  /*!< Array of Entities to be
                                              configure */
}UdxCfgInfo;

/** @brief
   Entity Configuration Confirmation Information */
typedef struct udxEntCfgCfmInfo
{
   U8       rbId;                /*!< rb ID */
   U8       rbType;              /*!< RB type - can be SRB or DRB */
   CmStatus status;              /*!< Status of the confirmation */
}UdxEntCfgCfmInfo;

/** @brief
   Configuration Confirmation Informatin RLC to RRC */
typedef struct udxCfgCfmInfo
{
   U32               transId;        /*!< Transaction Id */
   CmLteRnti         ueId;           /*!< UE ID */
   CmLteCellId       cellId;         /*!< Cell ID */
   U8                numEnt;         /*!< Number of entities configured */
   UdxEntCfgCfmInfo  entCfgCfm[UDX_MAX_ENT_CFG]; /*!< Array of Entity cfg
                                                         confiramations */
}UdxCfgCfmInfo;

/** @brief
     UE Id Information */
typedef struct udxUeInfo
{
   CmLteRnti      ueId;               /*!< UE ID */
   CmLteCellId    cellId;             /*!< Cell ID */
}UdxUeInfo;
#endif

typedef struct kwNackInfo
{
   U8           isSegment;
   U16         sn;      /*!< Nack Sn */
   U16          soStart; /*!< Segment offset start */
   U16          soEnd;   /*!< Segment offset End */
}KwNackInfo;

typedef struct kwUdxStaPdu
{
   U16         ackSn;
   /* TODO : KW_UDX_MAX_NACK_CNT should set to MAx SR delay 
      It is tradeoff to consider array based instead of dynamic
      as there are chances where we might loose Status information
      on spill over*/
   U8           nackCnt; /* Cnt of valid Nacks */
   KwNackInfo   nackInfo[KW_UDX_MAX_NACK_CNT];
}KwUdxStaPdu;

typedef struct kwUdxBufLst
{
   CmLListCp   rlsTxLst;         /*!< Stores to be released Tx PDUs */
   CmLListCp   rlsRetxLst;       /*!< Stores to be released Retx PDUs */
   CmLListCp   rlsSduLst;        /*!< Stores to be released SDUs*/
}KwUdxBufLst;

typedef struct kwDlStaPdu
{
    CmLList      lstEnt;                        /*!< List entry for SDU */
    U16          pduSz;                    /*!< Length of status PDU size */
    Buffer       *mBuf;                     /*!< Stores complete statusPdu to be dispatched */
}KwUdxDlStaPdu;


#if 0
typedef struct  kwUdxCntrlInfo
{
   S32          cntrlBo;
   U16          cntrlCnt; 
   KwCntrlInfo  cntrlInfo[KW_UDX_MAX_CNTRL_INFO]; 
}KwUdxCntrlInfo;
#endif
/**
  * @brief
  * UDX APIs
  */
typedef S16 (*UdxBndCfm) ARGS((Pst* pst, SuId suId,U8  status ));
typedef S16 (*UdxBndReq) ARGS((Pst* pst, SuId suId,SpId  spId ));
typedef S16 (*UdxUbndReq) ARGS((Pst* pst, SuId suId,Reason reason));
typedef S16 (*UdxCfgReq) ARGS((Pst *pst, SpId spId, UdxCfgInfo *cfgInfo));
typedef S16 (*UdxCfgCfm) ARGS(( Pst* pst,SuId suId,UdxCfgCfmInfo *cfmInfo));
typedef S16 (*UdxStaUpdReq) ARGS((Pst* pst,SpId spId,CmLteRlcId *rlcId,
                                KwUdxStaPdu         *pStaPdu ));
typedef S16 (*UdxUeIdChgReq) ARGS((Pst *pst, SpId spId, U32 transId, 
                                   UdxUeInfo *ueInfo, UdxUeInfo *newUeInfo));
typedef S16 (*UdxUeIdChgCfm) ARGS((Pst *pst, SuId suId, U32 transId, 
                                   UdxUeInfo *ueInfo, CmStatus status));


typedef S16 (*UdxStaUpdCfm) ARGS((Pst* pst,SuId  suId,CmLteRlcId  *rlcId,
                             KwUdxBufLst  *pBufLst));

typedef S16 (*UdxStaPduReq) ARGS(( Pst* pst,SpId  spId, CmLteRlcId *rlcId,
                             KwUdxDlStaPdu  *pStaPdu ));
#ifdef LCUDX
EXTERN S16 cmPkUdxBndCfm ARGS((Pst* pst, SuId suId,U8  status ));
EXTERN S16 cmPkUdxBndReq ARGS((Pst* pst, SuId suId,SpId  spId ));
EXTERN S16 cmPkUdxUbndReq ARGS((Pst* pst, SuId suId,Reason reason));
EXTERN S16 cmPkUdxCfgReq ARGS((Pst *pst, SpId spId, UdxCfgInfo *cfgInfo));
EXTERN S16 cmPkUdxCfgCfm ARGS(( Pst* pst,SuId suId,UdxCfgCfmInfo *cfmInfo));
EXTERN S16 cmPkUdxStaUpdReq ARGS((Pst* pst,SpId spId,CmLteRlcId *rlcId,
                               KwUdxStaPdu         *pStaPdu ));
EXTERN S16 cmPkUdxUeIdChgReq ARGS((Pst *pst, SpId spId, U32 transId, 
                                  UdxUeInfo *ueInfo, UdxUeInfo *newUeInfo));
EXTERN S16 cmPkUdxUeIdChgCfm ARGS((Pst *pst, SuId suId, U32 transId, 
                                   UdxUeInfo *ueInfo, CmStatus status));


EXTERN S16 cmPkUdxStaUpdCfm ARGS((Pst* pst,SuId  suId,CmLteRlcId  *rlcId,
                             KwUdxBufLst  *pBufLst));

EXTERN S16 cmPkUdxStaPduReq ARGS(( Pst* pst,SpId  spId, CmLteRlcId *rlcId,
                             KwUdxDlStaPdu  *pStaPdu ));

EXTERN S16 cmUnpkUdxBndCfm ARGS((UdxBndCfm func,Pst* pst, Buffer *mBuf ));
EXTERN S16 cmUnpkUdxBndReq ARGS((UdxBndReq func,Pst* pst, Buffer *mBuf ));
EXTERN S16 cmUnpkUdxUbndReq ARGS((UdxUbndReq func,Pst* pst, Buffer *mBuf));
EXTERN S16 cmUnpkUdxCfgReq ARGS((UdxCfgReq func,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkUdxCfgCfm ARGS((UdxCfgCfm func , Pst* pst,Buffer *mBuf));
EXTERN S16 cmUnpkUdxStaUpdReq ARGS((UdxStaUpdReq func,Pst* pst,Buffer *mBuf));
EXTERN S16 cmUnpkUdxUeIdChgReq ARGS((UdxUeIdChgReq func,Pst *pst, Buffer *mBuf)); 
EXTERN S16 cmUnpkUdxUeIdChgCfm ARGS((UdxUeIdChgCfm func,Pst *pst, Buffer *mBuf)); 

EXTERN S16 cmUnpkUdxStaUpdCfm ARGS((UdxStaUpdCfm func,Pst* pst,Buffer *mBuf));

EXTERN S16 cmUnpkUdxStaPduReq ARGS((UdxStaPduReq func, Pst* pst, Buffer *mBuf));

#endif


#ifdef KW
EXTERN S16 KwUlUdxBndReq ARGS((
   Pst*                pst,
   SuId        suId,
   SpId        spId ));

EXTERN S16 KwDlUdxBndReq ARGS((
   Pst*                pst,
   SuId        suId,
   SpId        spId ));

EXTERN S16 KwDlUdxBndCfm ARGS((
   Pst*                pst,
   SuId        suId,
   U8          status));

EXTERN S16 KwUlUdxBndCfm ARGS((
   Pst*                pst,
   SuId        suId,
   U8          status));

EXTERN S16 KwDlUdxCfgCfm ARGS((
   Pst*                pst,
   SuId                suId,
   UdxCfgCfmInfo      *cfmInfo));


EXTERN S16 KwUlUdxCfgCfm ARGS((
   Pst*                pst,
   SuId                suId,
   UdxCfgCfmInfo      *cfmInfo));

EXTERN S16 KwDlUdxUeIdChgCfm ARGS((Pst *pst, SuId suId, U32 transId, 
                                   UdxUeInfo *ueInfo, CmStatus status));
EXTERN S16 KwUlUdxUeIdChgCfm ARGS((Pst *pst, SuId suId, U32 transId, 
                                   UdxUeInfo *ueInfo, CmStatus status));
EXTERN S16 KwUlUdxUbndReq ARGS((Pst* pst, SuId suId,Reason reason));
EXTERN S16 KwDlUdxUbndReq ARGS((Pst* pst, SuId suId,Reason reason));

EXTERN S16 KwUlUdxUeIdChgReq ARGS((Pst *pst, SpId spId, U32 transId, 
                                   UdxUeInfo *ueInfo, UdxUeInfo *newUeInfo));
EXTERN S16 KwUlUdxCfgReq ARGS((Pst *pst, SpId spId, UdxCfgInfo *cfgInfo));
EXTERN S16 KwDlUdxCfgReq ARGS((Pst *pst, SpId spId, UdxCfgInfo *cfgInfo));


EXTERN S16 KwUlUdxStaUpdReq ARGS((
   Pst*                pst,
   SpId                spId,
   CmLteRlcId          *rlcId,
   KwUdxStaPdu         *pStaPdu ));
EXTERN S16 KwDlUdxStaUpdReq ARGS((
   Pst*                pst,
   SpId                spId,
   CmLteRlcId          *rlcId,
   KwUdxStaPdu         *pStaPdu ));

EXTERN S16 KwDlUdxStaUpdCfm ARGS((
   Pst*                pst,
   SuId                suId,
   CmLteRlcId          *rlcId,
   KwUdxBufLst         *pBufLst));
EXTERN S16 KwUlUdxStaUpdCfm ARGS((
   Pst*                pst,
   SuId                suId,
   CmLteRlcId          *rlcId,
   KwUdxBufLst         *pBufLst));

EXTERN S16 KwUlUdxStaPduReq ARGS((
   Pst                 *pst,
   SpId                spId,
   CmLteRlcId          *rlcId,
   KwUdxDlStaPdu         *pStaPdu ));
EXTERN S16 KwDlUdxStaPduReq ARGS((
   Pst                 *pst,
   SpId                spId,
   CmLteRlcId          *rlcId,
   KwUdxDlStaPdu         *pStaPdu ));
EXTERN S16 KwDlUdxUeIdChgReq ARGS((Pst *pst, SpId spId, U32 transId, 
                                   UdxUeInfo *ueInfo, UdxUeInfo *newUeInfo));
EXTERN S16 KwDlUdxCfgReq ARGS((Pst *pst, SpId spId, UdxCfgInfo *cfgInfo));


EXTERN S16 KwUlUdxStaUpdCfm ARGS((
   Pst*                pst,
   SuId                suId,
   CmLteRlcId          *rlcId,
   KwUdxBufLst         *pBufLst));

EXTERN S16 KwDlUdxStaPduReq ARGS((
   Pst                 *pst,
   SpId                spId,
   CmLteRlcId          *rlcId,
   KwUdxDlStaPdu         *pStaPdu ));
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __SCH__ */


/**********************************************************************
         End of file:     kw_udx.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:52 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       mraj   1. LTE RLC Initial Release
*********************************************************************91*/

