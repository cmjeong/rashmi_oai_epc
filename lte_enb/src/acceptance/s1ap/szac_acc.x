
/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     szac_acc.x

     Sid:      szac_acc.x@@/main/4 - Mon Jan 10 22:15:35 2011

     Prg:      rs

*********************************************************************21*/

#ifndef __SZ_ACC_X__
#define __SZ_ACC_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN Bool szAcFlag[SZAC_MAX_FLAGS];
EXTERN Txt  szAcFlagStr[SZAC_MAX_FLAGS][50];


typedef struct szAcHitAssocCb
{
   UConnId    suConId;   /* service user connection Id   */
      UConnId    spConId;   /* service provider connection Id   */
             
      Bool       inUse;
                      
      CmTptAddr  localAddr;
} SzAcHitAssocCb; 

typedef struct szAcHitCb
{  
   U16          nxtConnId;
      SzAcHitAssocCb assoc[10];
} SzAcHitCb; 

typedef struct szAcSctAssocCb
{
   UConnId    suAssocId;   /* service user connection ID       */
   UConnId    spAssocId;   /* service provider connection Id   */

   Bool       inUse;
} SzAcSctAssocCb; 

typedef struct szAcSctCb
{
   SzAcSctAssocCb assoc[10];
} SzAcSctCb; 

typedef struct szAcSctConInfo
{
   SpId              spId;
   UConnId           suAssocId;
   UConnId           spAssocId;
   UConnId           suEndpId;
   UConnId           spEndpId;
   SctNetAddrLst     remAddrLst;
   SctNetAddrLst     localAddrLst;
   SctStrmId         outStrms;
   SctPort           port;
}SzAcSctConInfo;

typedef struct szAcTACb
{
   Txt               ipAddr[20];

   U16               glbNum;

   SzAcSctConInfo    sctConInfo[40]; /*-- Su Conn Id starts from max tpt servs.. --*/

#ifdef CMXTA_EXTENSION
   SpId              sctpId;
#endif

}SzAcTACb;

/* Common interface element */
typedef struct szAcCmInfo
{
   SuId              suId;
   SpId              spId;
   Reason            reason;
   Buffer            mBuf;
}SzAcCmInfo;

typedef struct szAcAuditCon
{
   U8 nmbConn;
   U8 connIdType;
   UConnId  connId[SZT_MAX_AUD_CONN];
   U8       connSt[SZT_MAX_AUD_CONN];
}SzAcAuditCon;

typedef struct szAcAuditPeer
{
   U32 peerId;
   State  peerState;
}SzAcAuditPeer;
   
typedef struct szAcAuditInfo
{
   U8                type;       /* Audit type */
   union
   {
      SzAcAuditCon   conn;        /* Number of connection info */
      SzAcAuditPeer  peer;
   }u;
   U16       status;    /* Request Status */
   U16       cause;     /* Request Cause */
}SzAcAuditInfo;

typedef struct szAcSztStaInd 
{
   U8        type;          /* type */
   U8        status;
   U8        reason;
}SzAcSztStaInd;

typedef struct szAcSztErrInd 
{
   U8        type;
   U8        value;
}SzAcSztErrInd;

typedef struct szAcSztPduInfo 
{
   U32  enbId;
   U32  mmeId;
}SzAcSztPduInfo;

/* SCT interface element */
typedef struct szAcSctInfo
{
  SzAcCmInfo      cmInfo;
  UConnId         suEndpId;
  UConnId         spEndpId;
  UConnId         suAssocId;
  UConnId         spAssocId;
  SctPort         port;
  SctCause        cause;
  Buffer         *mBuf;
  U8              endpIdType;
  SctResult       result;
  SctStrmId       outStrms;
#ifdef SCT3
  SctTos          tos;
#endif /* SCT3*/
  U8              assocIdType;
  SctNetAddrLst   dstNAddrLst;
  SctNetAddrLst   srcNAddrLst;
  SctAssocIndParams  assocParams;
  SctStrmId       strmId;
  Bool            unorderFlg;
  Bool            nobundleFlg;
  U16             lifeTime;
  U32             protId;
  TknU8           type;
  union
  {
     SzAcAuditInfo  audit;            /* Audit Information */
     SzAcSztStaInd  staInd;           /* Status Indication */
     SzAcSztErrInd  errInd;           /* Error Indication */
     SzAcSztPduInfo pduInfo;          /* enbId, mmeId */
  }u; 
}SzAcSctInfo; 

typedef struct szAcSztInfo
{
   SzAcCmInfo      cmInfo;
   Status          status;
   TknU32          peerId;
   UConnId         suConnId;
   UConnId         spConnId;
   TknU8           type;        /*Type is SZAC_AUDIT, SZAC_STAIND, SZAC_ERRIND */
   union
   {
      SzAcAuditInfo  audit;            /* Audit Information */
      SzAcSztStaInd  staInd;           /* Status Indication */
      SzAcSztErrInd  errInd;           /* Error Indication */
      SzAcSztPduInfo pduInfo;          /* enbId, mmeId */
   }u;
}SzAcSztInfo;

/* Message queue element */
typedef struct szAccMsgQElm
{
   Pst           pst;                   /* pst structure         */
   Buffer        *mBuf;
   union
   {
      SzAcSztInfo  sztInfo;
      SzAcSctInfo  sctInfo;
      SzMngmt      szMngmt;
#ifdef SB
      SbMgmt       sbMgmt;
#endif
#ifdef HI
      HiMngmt      hiMngmt;
#endif
   }u;

   PMSGFREEFS16      msgFreeFun;       /* Function to free the msg */
}SzAccMsgQElm;

typedef struct szAcDirectives
{
   ProcId  xtaProcId;
   ProcId  eNbProcId;
   ProcId  mmeProcId;
   U32     eNbIpAddr;
   U32     mmeIpAddr;
/* sz003.301: Updted for PSF-S1AP 3.1 release */
   ProcId  sbyProcId;
   ProcId  tptProcId;
}SzAcDirectives;

/* Acceptance Test Global Structure */
typedef struct szAccCb
{
   SzAcTACb      taCb;
   SzAcHitCb     hitCb;
   SzAcSctCb     sctCb;

   U32           nxtCallId;
   U32           nxtDlgId;
   U32           nxtSuConnId;

   U16           nxtLoadIndx;

   U32           connArr[SZAC_CQ_SIZE];  /* Connection Identifier generated */
   SzAcDirectives directives;
}SzAccCb;

#ifdef SZ_MME
EXTERN SztNetAddrLst dynamDstAddrLst;
#endif

EXTERN Void szAcGetPst ARGS((CmXtaSpCb  *spCb, Pst  *pst, Ent srcEnt, Inst srcInst, Ent  dstEnt, Inst dstInst));
EXTERN ProcId szAcGetProc ARGS((CmXtaSpCb  *spCb, Ent ent, Inst inst));

EXTERN S16 szAcEncode ARGS((Mem *mem, S1apPdu **s1apPdu, Buffer **mBuf));
EXTERN S16 szAcEncode_r9 ARGS((Mem *mem, S1apPdu **s1apPdu, Buffer **mBuf));
EXTERN S16 szAcEncode_r11 ARGS((Mem *mem, S1apPdu **s1apPdu, Buffer **mBuf));
EXTERN S16 szAcDecode ARGS((Mem *mem, S1apPdu **s1apPdu, Buffer **mBuf));
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
EXTERN S16 szAcEncodeIe ARGS((Mem *mem, SztEncDecEvnt *sztEncDecEvnt));
#endif /* SZTV1 */

EXTERN SzAccCb szAccCb;


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __SZ_ACC_X__ */

/**********************************************************************

         End of file:     szac_acc.x@@/main/4 - Mon Jan 10 22:15:35 2011

**********************************************************************/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz004.301   va    1. Updated for Transparent Container 
                                 Enc/Dec
*********************************************************************91*/
