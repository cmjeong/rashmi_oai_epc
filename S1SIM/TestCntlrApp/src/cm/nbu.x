/********************************************************************20**

     Name:     

     Type:     C Hearder file

     Desc:     Defines required by the NBU layer service user

     File:     nbu.x

     Sid:      
     Prg:      

*********************************************************************21*/
typedef struct _nbuSTmsi
{
   Bool                      pres;
   U8                        mmec;
   U32                       mTMSI;
} NbuSTmsi;

typedef struct _nbuUeAttachReq
{
    U8 ueId;
    U32 rrcCause;
    NbuSTmsi stmsi;
    TknStrOSXL nasPdu;
}NbuInitialUeMsg;

typedef struct _nbuUlNasMsg
{
   U8 ueId;
   TknStrOSXL  nasPdu;
}NbuUlNasMsg;
typedef struct _nbuUlRrcMsg
{
   U8 ueId;
   TknStrOSXL  rrcPdu;
}NbuUlRrcMsg;

typedef struct _nbuDlNasMsg
{
   U8 ueId;
   TknStrOSXL nasPdu;
}NbuDlNasMsg;

typedef struct _nbuErabCb
{
   U8 erabId;
   TknStrOSXL nasPdu;
}NbuErabCb;

typedef struct _nbuErabLst
{
   U8 numOfErab;
   NbuErabCb *rabCbs; 
}NbuErabLst;

typedef struct _nbuErabRelIndLst
{
   U8 ueId;
   U8 numOfErabIds;
   U8 *erabIdLst; 
}NbuErabRelIndList;

typedef struct _nbuErabsInfo 
{
   U8 ueId;
   Bool nasPduPres;
   Bool ueRadCapRcvd;
   NbuErabLst *erabInfo;
}NbuErabsInfo;

typedef struct _nbuS1RelInd
{
   U8 ueId;
}NbuS1RelInd;

typedef struct _nbuUeInActvInd
{
   U8 ueId;
}NbuUeInActvInd;

typedef struct _nbuUeIpInfoReq
{
   U8 ueId;
   U8 bearerId;
}NbuUeIpInfoReq;

typedef struct _uePagingMsg
{
   U8      ueIdenType;
   union
   {   
      NbuSTmsi  sTMSI;      /*!< S-TMSI of the UE*/ 
      U8       imsi[22];   /*!< IMSI of the UE. IMSI size is
                             min-6 Integer digits and
                             max-21 Integer Digits.As we are using
                             the first index for the storing
                             the length of IMSI */
   } ueIden;     /*!< It contians either IMSI or S-TMSI */
   U8      domIndType;

}UePagingMsg;

typedef enum  _bearerType
{
 DEFAULT_BER =1,
 DEDICATED_BER
}BearerType;

typedef struct _nbuUeIpInfoRsp
{
   U8 ueId;
   U8 bearerId;
   S8 IpAddr[20];
   BearerType berType;
}NbuUeIpInfoRsp;

typedef S16 (*NbuInitialUeMsgHdl)(Pst*, NbuInitialUeMsg*);
typedef S16 (*NbuUlNasMsgHdl)(Pst*, NbuUlNasMsg*);
typedef S16 (*NbuDlNasMsgHdl)(Pst*, NbuDlNasMsg*);
typedef S16 (*NbuPagingMsgHdl)(Pst*, UePagingMsg*);
typedef S16 (*NbuUlRrcMsgHdl)(Pst*, NbuUlRrcMsg*);
typedef S16 (*NbuUeInactivHdl)(Pst *, NbuUeInActvInd*);
typedef S16 (*NbuS1RelIndMsgHdl)(Pst *, NbuS1RelInd*);
typedef S16 (*NbuErabsInfoMsgHdl) (Pst *, NbuErabsInfo*);
typedef S16 (*NbuUeIpInfoReqHdl) (Pst *, NbuUeIpInfoReq*);
typedef S16 (*NbuUeIpInfoRspHdl) (Pst *, NbuUeIpInfoRsp*);
typedef S16 (*NbuErabRelIndHdl)(Pst *, NbuErabRelIndList*);/*NbErabRelInd*);*/
EXTERN S16 cmPkNbuInitialUeMsg(Pst *pst,NbuInitialUeMsg *req);
EXTERN S16 cmPkNbuErabRelInd(Pst *pst, NbuErabRelIndList *);
EXTERN S16 cmPkNbuUlNasMsg(Pst *pst,NbuUlNasMsg *msg);
EXTERN S16 cmPkNbuDlNasMsg(Pst *pst,NbuDlNasMsg *msg);
EXTERN S16 cmPkNbuUeInActvInd(Pst*, NbuUeInActvInd*);
EXTERN S16 cmPkNbuS1RelInd(Pst*, NbuS1RelInd*);
EXTERN S16 cmPkNbuUeIpInfoReq ARGS((Pst *pst,NbuUeIpInfoReq *req));
EXTERN S16 cmPkNbuErabsInfo (Pst *pst,NbuErabsInfo *msg);
EXTERN S16 cmPkNbuUeIpInfoRsp (Pst *pst,NbuUeIpInfoRsp *msg);
EXTERN S16 cmPkNbuUlRrcMsg ARGS((Pst *pst, NbuUlRrcMsg *msg));

EXTERN S16 cmUnPkNbuInitialUeMsg(NbuInitialUeMsgHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuErabRelInd(NbuErabRelIndHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuUlNasMsg(NbuUlNasMsgHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuDlNasMsg(NbuDlNasMsgHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuDlNasMsg(NbuDlNasMsgHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuUeInActvInd(NbuUeInactivHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuS1RelInd(NbuS1RelIndMsgHdl, Pst*, Buffer*);
EXTERN S16 NbUiNbuHdlInitialUeMsg(Pst*, NbuInitialUeMsg*);
EXTERN S16 NbUiNbuHdlErabRelInd(Pst*, NbuErabRelIndList*); /*NbErabRelInd*);*/
EXTERN S16 NbUiNbuHdlUlNasMsg(Pst*, NbuUlNasMsg*);
EXTERN S16 cmUnPkNbuErabsInfo(NbuErabsInfoMsgHdl func, Pst *pst, Buffer *mBuf);
EXTERN S16 cmPkNbuPagingMsg(Pst *pst, UePagingMsg *msg);
EXTERN S16 cmUnPkNbuPagingMsg(NbuPagingMsgHdl, Pst*, Buffer*);
EXTERN S16 cmUnPkNbuUlRrcMsg ARGS((NbuUlRrcMsgHdl, Pst*, Buffer*));
EXTERN S16 NbUiNbuHdlUeRadioCapMsg(Pst *pst, NbuUlRrcMsg *msg);
EXTERN S16 cmUnPkNbuUeIpInfoReq (NbuUeIpInfoReqHdl func,Pst *pst,Buffer *mBuf);
EXTERN S16 cmUnPkNbuUeIpInfoRsp (NbuUeIpInfoRspHdl func,Pst *pst,Buffer *mBuf);
/********************************************************************30**

         End of file:     

*********************************************************************31*/
