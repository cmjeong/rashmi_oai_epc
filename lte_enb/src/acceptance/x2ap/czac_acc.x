
/********************************************************************20**

     Name:     X2AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     czac_acc.x

     Sid:      czac_acc.x@@/main/2 - Tue Aug 30 18:35:44 2011

     Prg:      rp

*********************************************************************21*/

#ifndef __CZ_ACC_X__
#define __CZ_ACC_X__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

EXTERN Bool czAcFlag[CZAC_MAX_FLAGS];
EXTERN Txt  czAcFlagStr[CZAC_MAX_FLAGS][50];

/* cz001.101 : CR Fixes */

typedef struct czAcHitAssocCb
{
   UConnId    suConId;   /* service user connection Id   */
      UConnId    spConId;   /* service provider connection Id   */
             
      Bool       inUse;
                      
      CmTptAddr  localAddr;
} CzAcHitAssocCb; 

typedef struct czAcHitCb
{  
   U16          nxtConnId;
      CzAcHitAssocCb assoc[10];
} CzAcHitCb; 

typedef struct czAcSctAssocCb
{
   UConnId    suAssocId;   /* service user connection ID       */
   UConnId    spAssocId;   /* service provider connection Id   */

   Bool       inUse;
} CzAcSctAssocCb; 

typedef struct czAcSctCb
{
   CzAcSctAssocCb assoc[10];
} CzAcSctCb; 

typedef struct czAcSctConInfo
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
}CzAcSctConInfo;

typedef struct czAcTACb
{
   Txt               ipAddr[20];

   U16               glbNum;

   CzAcSctConInfo    sctConInfo[40]; /*-- Su Conn Id starts from max tpt servs.. --*/

#ifdef CMXTA_EXTENSION
   SpId              sctpId;
#endif /* CMXTA_EXTENSION */

}CzAcTACb;

/* Common interface element */
typedef struct czAcCmInfo
{
   SuId              suId;
   SpId              spId;
   Reason            reason;
   Buffer            mBuf;
}CzAcCmInfo;

/* SCT interface element */
typedef struct czAcSctInfo
{
  CzAcCmInfo      cmInfo;
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
}CzAcSctInfo;

typedef struct czAcCztStaInd 
{
   U8        type;          /* type */
   U8        status;
   U8        reason;
}CzAcCztStaInd;


typedef struct czAcCztAudCfm 
{
   U8        type;          /* type */
   U8        status;
   U16        cause;
   State     peerState;     /* State of the peer */
}CzAcCztAudCfm;


typedef struct czAcCztErrInd 
{
   U16        type;
   U16        value;
}CzAcCztErrInd;

typedef struct czAcCztUeInfo
{
   U16  oldX2APUEId;
   U16  newX2APUEId;
}CzAcCztUeInfo;

typedef struct czAcCztRsrcInfo
{
   U16  eNb1MeasId;
   U16  eNb2MeasId;
   U8  regReq;    /* STRAT/STOP */
}CzAcCztRsrcInfo;

typedef struct czAcCztCause
{
   U8   causeType;
   U8   causeVal;
}CzAcCztCause;
typedef struct czAcCztCrit
{
   U8        procCode;
   U8        trigMsg;
   U8        crit;
   U8        ieIdLst[4];
}CzAcCztCrit;
typedef CzAcCztStaInd CzAcCztRlsCfm;

typedef struct czAcCztPduInfo
{
   U32 enbId;
}CzAcCztPduInfo;
typedef struct czAcCztInfo
{
   CzAcCmInfo      cmInfo;
   Status          status;
   U32             enbId;
   U32             peerId;
   U8              timeToWait;
   CzAcCztCause    cause;
   CzAcCztCrit     crit;
   U8              msgType;
   TknU8           type;        /*Type is CZAC_AUDIT, CZAC_STAIND, CZAC_ERRIND */
   union
   {
      CzAcCztStaInd   staInd;           /* Status Indication */
      CzAcCztErrInd   errInd;           /* Error Indication */
      CzAcCztRsrcInfo rsrcInfo;
      CzAcCztUeInfo   ueInfo;
      CzAcCztRlsCfm   rlsCfm;           /* Status Indication */
      CzAcCztAudCfm   audCfm;           /* Audit Confirmation */
   }u;
}CzAcCztInfo;

/* Message queue element */
typedef struct czAccMsgQElm
{
   Pst           pst;                   /* pst structure         */
   Buffer        *mBuf;
   union
   {
      CzAcCztInfo  cztInfo;
      CzAcSctInfo  sctInfo;
      CzMngmt      czMngmt;
#ifdef SB
      SbMgmt       sbMgmt;
#endif /* SB */
#ifdef HI
      HiMngmt      hiMngmt;
#endif /* HI */
   }u;

   PMSGFREEFS16      msgFreeFun;       /* Function to free the msg */
}CzAccMsgQElm;

typedef struct czAcDirectives
{
   ProcId        xtaProcId;
   ProcId        eNb1ProcId;
   ProcId        eNb2ProcId;
   U32           eNb1IpAddr;
   U32           eNb2IpAddr;
   U16           basePort;
   CmInetIpAddr  baseIp;
   U16           tptType;
}CzAcDirectives;

/* Acceptance Test Global Structure */
typedef struct czAccCb
{
   CzAcTACb      taCb;
   CzAcHitCb     hitCb;
   CzAcSctCb     sctCb;

   U32           nxtCallId;
   U32           nxtDlgId;
   U32           nxtSuConnId;

   U16           nxtLoadIndx;

   U32           connArr[CZAC_CQ_SIZE];  /* Connection Identifier generated */
   CzAcDirectives directives;
}CzAccCb;


EXTERN Void czAcGetPst ARGS((CmXtaSpCb  *spCb, Pst  *pst, Ent srcEnt, Inst srcInst, Ent  dstEnt, Inst dstInst));
EXTERN ProcId czAcGetProc ARGS((CmXtaSpCb  *spCb, Ent ent, Inst inst));


EXTERN CzAccCb czAccCb;


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __CZ_ACC_X__ */

/**********************************************************************

         End of file:     czac_acc.x@@/main/2 - Tue Aug 30 18:35:44 2011

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
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
