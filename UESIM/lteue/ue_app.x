

/**********************************************************************
 
    Name:  LTE UESIM - Sample Application Module 
 
    Type:  C include file
 
    Desc:  C source code for UE Sample Application
 
    File:  ue_app.x 
 
    Sid:      ue_app.x@@/main/1 - Sun Mar 28 22:59:21 2010
 
    Prg:   vp
 
**********************************************************************/
#ifndef __UE_APPX__
#define __UE_APPX__

/* UeEmmState EPS Mobility Management States */
typedef enum ueEmmState
{
   UE_EMM_UE_NULL = 0,       /* UE NULL */
   UE_EMM_UE_DEREGISTERED ,  /* UE Deregistered */
   UE_EMM_UE_REG_INIT,       /* UE Registration Initiated/In progress */
   UE_EMM_UE_REGISTERED,     /* UE Registered */
   UE_EMM_UE_DEREG_INIT      /* UE Deregister Initiated */
}UeEmmState;

/* ue003.101: Added paging support */
/* UeEcmState EPS Connection Management States */
typedef enum ueEcmState
{
   UE_ECM_IDLE = 0,          /* UE ECM IDLE */
   UE_ECM_CONNECTED          /* UE ECM_CONNECTED */
}UeEcmState;


/* EMM common procedures State */
typedef enum ueEmmCommProcState
{
   UE_EMM_COMM_PROC_IDLE = 0,  /* Common procedure initiated */
   UE_EMM_COMM_PROC_INIT       /* Common procedure complete */
}UeEmmCommProcSubState;


/* EMM Common procedure in progress */
typedef enum ueEmmCommPrcInPrg
{
   UE_EMM_COM_PRC_NONE = 0x0,
   UE_EMM_COM_PRC_GUTI_RALC_CMD = 0x1,
   UE_EMM_COM_PRC_GUTI_RALC_CMP = 0x2,
   UE_EMM_COM_PRC_AUTH_REQ = 0x4,
   UE_EMM_COM_PRC_AUTH_RSP = 0x8,
   UE_EMM_COM_PRC_AUTH_REJ = 0x10,
   UE_EMM_COM_PRC_AUTH_FAIL = 0x20,
   UE_EMM_COM_PRC_ID_REQ = 0x40,
   UE_EMM_COM_PRC_ID_RSP = 0x80,
   UE_EMM_COM_PRC_SEC_MOD_CMD = 0x100,
   UE_EMM_COM_PRC_SEC_MOD_CMP = 0x200,
   UE_EMM_COM_PRC_SEC_MOD_REJ = 0x400
}UeEmmCommPrcInPrg;

/* EMM common procedure events */
typedef enum ueEmmCmnPrcEvt
{
   UE_EMM_EVNT_CMN_PRC_GUTI_RLC = 0,
   UE_EMM_EVNT_CMN_PRC_AUTH_NRML,
   UE_EMM_EVNT_CMN_PRC_AUTH_ABNRML,
   UE_EMM_EVNT_CMN_PRC_ID,
   UE_EMM_EVNT_CMN_PRC_SEC_MOD_NRML,
   UE_EMM_EVNT_CMN_PRC_SEC_MOD_ABNRML,
   UE_EMM_EVNT_CMN_PRC_INVALID
}UeEmmCmnPrcEvt;


/* ESM Bearer Context States at UE */
typedef enum ueEsmBearerCtxtState
{
   UE_ESM_ST_BEARER_CTXT_INACTIVE = 0,   /* Bearer Inactive */
   UE_ESM_ST_BEARER_CTXT_ACTIVE          /* Bearer Active */
}UeEsmBearerCtxtState;

/* ESM Procedure Transaction States at UE */
typedef enum ueEsmProcTxnState
{
   UE_ESM_ST_PROC_TXN_INACTIVE = 0,   /* Procedure Transaction Inactive */
   UE_ESM_ST_PROC_TXN_PENDING         /* Procedure Transaction Pending */
}UeEsmProcTxnState;

/* UE ESM structure */
typedef struct ueEsmCb
{
   UeEsmBearerCtxtState bState;  /* EPS Bearer context state */
   UeEsmProcTxnState    pState;  /* Procedure transaction state */
   U8                   bId;     /* EPS bearer identity */
   U8                   tId;     /* Procedure transaction identity */

} UeEsmCb;

/*  This structure represents EMM Context Control block for an UE */
typedef struct ueEmmCb
{

   UeEmmState             state;       /* State of this UE involved in EMM
                                          procedure. */

   UeEmmCommProcSubState  emmCommProcSubState;
                                /* Sub-State of this UE within an EMM 
                                   common procedure. */

   UeEmmCommPrcInPrg      emmCommProcInProgress;
                                 /* The bit array to indicate the common proc 
                                    that is going on. Each bit represents one
                                    message of the EMM common procedures */

   Bool                   esmPiggyBacked;  /* Flag to indicate if Default EPS
                                       bearer needs to be established with ESM
                                       piggybacked on EMM message */

}UeEmmCb;


/* RRC SAP control block */

typedef struct ueAppNhuSapCb        /* UE Application's Lower SAP Control Block */
{
   Pst           pst;            /* Service user post structure */
   State         state;          /* State of this SAP */
   SuId          suId;           /* Service User SAP id */
   SpId          spId;           /* Service Provider Id */
   U8            maxBndRetry;    /* maximum Bind Retry counter */
   U8            bndRetryCnt;    /* Bind retry count */
   TmrCfg        tBndTmr;        /* Bind Timer */
   CmTimer       timer;          /* Interface timer control block */
}UeAppNhuSapCb;

/* PDCP SAP control block */

typedef struct ueAppPjuSapCb        /* UE Application's Lower SAP Control Block */
{
   Pst           pst;            /* Service user post structure */
   State         state;          /* State of this SAP */
   SuId          suId;           /* Service User SAP id */
   SpId          spId;           /* Service Provider Id */
   U8            maxBndRetry;    /* maximum Bind Retry counter */
   U8            bndRetryCnt;    /* Bind retry count */
   TmrCfg        tBndTmr;        /* Bind Timer */
   CmTimer       timer;          /* Interface timer control block */
}UeAppPjuSapCb;

typedef struct ueAppNwId
{
   U8   mcc[UE_APP_MAX_MCC_LEN];  /* MCC */
   U8   mnc[UE_APP_MAX_MNC_LEN];  /* MNC */
}UeAppNwId;

#ifdef SS_CAVIUM
typedef U32 UeInetIpAddr;
typedef U64 UeInetIpAddr6;
typedef struct ueInetNetAddr
{
   U8   type;      /* type of network address */
   union
   {
      UeInetIpAddr   ipv4NetAddr; /* IP network address */
#ifdef IPV6_SUPPORTED
      UeInetIpAddr6  ipv6NetAddr; /* IPv6 network address */
#endif /* IPV6_SUPPORTED */
   }u;
} UeInetNetAddr;
#endif /* SS_CAVIUM */

typedef struct ueAppGUMMEI
{
   UeAppNwId  nwId;           /* Serving Network with PLMN ID */ 
   U8         mmeCode;        /* MME Code */
   U16        mmeGrpId;       /* MME Group ID */ 
}UeAppGUMMEI;

typedef struct ueAppInfo
{
   UeAppGUMMEI   gummei;     /* GUMMEI of serving MME for this UE */
   U8            ueImsi[CM_EMM_MAX_MOBILE_ID_DIGS];    /* IMSI of UE */
   GUTI          ueGuti;      /* Guti allocated to this UE from MME  */
   CmEmmTaiLst   *taList;     /* Tracking Area List for this UE from MME */
   CmEmmUeNwCap  ueNwCap;     /* Network capability of UE */
   CmEmmUeSecCap ueSecCap;    /* UE security capability */
#ifdef SS_CAVIUM
   UeInetNetAddr selfAddr;    /* IP address allocated for this UE. */
#else
   CmInetNetAddr selfAddr;    /* IP address allocated for this UE. */
#endif /* SS_CAVIUM */

}UeAppInfo;

/* UE data routing info */
typedef struct ueAppDataRoutCb
{
   U32 ipAddr;
   U8  ipAddrStr[UE_APP_MAX_IP_ADDR_LEN];
   U8  macAddr[UE_APP_MAC_ADDR_LEN];
}UeAppDataRouteCb;

#ifndef SS_CAVIUM
/* Structure to contain the information related to the data application at ue */
typedef struct ueAppDataCb
{
   pcap_t *dataHdlr; /* pcap handler callback */
   U16     proxyPort; /* Self port acting as proxy for all UE clients */
   U8      ethPkt[UE_APP_MAX_ETH_PKT_LEN]; /* The ethernet packet that is 
                                              sent out from pcap */
   U8      arpPkt[UE_APP_MAX_ARP_PKT_LEN]; /* The ARP packet that is 
                                              sent out from pcap */
   S8      ethInf[UE_APP_MAX_PCAP_DEV_LEN]; /* The ethernet interface to send
                                               the pkt */
   U32     ueAppDstAddr;
   U8      ueAppDstAddrStr[UE_APP_MAX_IP_ADDR_LEN];
   U16     ueAppDstPort; /* The Data server port */
/* ue003.101: Removed unwanted members */
   U8      ueAppIpAddrStr[UE_APP_MAX_IP_ADDR_LEN];  /* Self IP Address of the
                                                       UESIM Application. */
   U32     ueAppIpAddr;    /* Self IP address of the UESIM Application. */
   U8      lclMACAddr[UE_APP_MAC_ADDR_LEN];  /* Local MAC Address of the UESIM */
   U8      mapCnt; /* Number of UE Clients */
   UeAppDataRouteCb ip2Mac[UE_NUM_CELL][UE_NUM_PER_CELL]; /* Data routing table for UE Clients */
}UeAppDataCb;
#else
/* Structure to contain the information related to the data application at ue */
typedef struct ueAppDataCb
{
   U16     proxyPort; /* Self port acting as proxy for all UE clients */
   U8      *ethPkt; /* The ethernet packet that is 
                                              sent out from pcap */
   U8      *arpPkt; /* The ARP packet that is 
                                              sent out from pcap */
   U32     ueAppDstAddr;
   U8      ueAppDstAddrStr[UE_APP_MAX_IP_ADDR_LEN];
   U16     ueAppDstPort; /* The Data server port */
   U8      ueIpAddrStr[UE_APP_MAX_IP_ADDR_LEN];  /* IP Address of the UE assigned
                                                    by CNE. */
   U32     ueIpAddr;    /* IP address of this UE assigned by CNE */
   U8      ueAppIpAddrStr[UE_APP_MAX_IP_ADDR_LEN];  /* Self IP Address of the
                                                       UESIM Application. */
   U32     ueAppIpAddr;    /* Self IP address of the UESIM Application. */
   U8      lclMACAddr[UE_APP_MAC_ADDR_LEN];  /* Local MAC Address of the UESIM */
   U8      mapCnt; /* Number of UE Clients */
   UeAppDataRouteCb ip2Mac[UE_APP_MAX_CONNS]; /* Data routing table for UE Clients */
}UeAppDataCb;
#endif

typedef struct ueArpPkt /* assumes IPv4 */
{
   U16 hw_type;
   U16 proto;
   U8  hw_addr_len;
   U8  proto_addr_len;
   U16 opcode;
   U8  src_mac[6];
   U8  src_ip[4];
   U8  dest_mac[6];
   U8  dest_ip[4];
} UeArpPkt;

/* ue003.101: Added support for paging */
typedef struct ueEcmCb
{
   UeEcmState    state;      /* ECM state */

}UeEcmCb;
/* ue007.101:ccpu00117835 enodeb TxId used */
typedef struct _ueAppCb_TxId
{
   U32 rrc_con_setupTxId;
   U32 rrc_Sec_ModeTxId;
   U32 rrc_Cap_InfoTxId;
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 * depends on the RRC timer. */
   U32 rrc_con_reestbTxId;
#endif
}ueAppCb_TxId;
#ifdef TOTAL_ENB
/* ue009.101: Added support to send measurement support */
typedef struct ueMeasCfg
{
   Bool            cfgPres;
   U32             noMeasIds;
   U32             *measIdLst;
} UeMeasCfg;
#endif

/* This is a global structure representing UE Control block in UE's scope */
/*  ue002.101: Multi ue support changes */
typedef struct _ueAppCb
{
   UeAppInfo   ueCtxt;       /* Addtional UE Information for this UE */
   UeEmmCb     emmCb;        /* EMM Context for this UE */
/* ue003.101: Added paging support */
   UeEcmCb     ecmCb;        /* ECM Context for this UE */
   UeEsmCb     *esmTList[CM_ESM_MAX_BEARER_ID];/* TRANS List of ESM Cbs */
   UeEsmCb     *esmBList[CM_ESM_MAX_BEARER_ID];/* BID List of ESM Cbs */
   U32         transIdCntr;   /* Transaction counter for sending the 
                                 ESM Procedural transactions. */
   U16         cellId; /* cellId */
   U16         ueId;   /* ueId */
/* ue003.101: Added for paging support */
   U8          nasEsmState;  /* NAS State */
   /* ue008.101: Added new variable hoState */
   U8          hoState;      /* HO State */
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 * depends on the RRC timer. */
   /* RE-EST added new variable for Re-Est */
   U8          isReest;
#endif
   Bool        drpSecMode;
/* ue008.101: Flag to indicate UE is detached --*/
#ifdef MULTI_UE_ATTACH
   Bool         isDetached;/* Flag to indicate Attach state */
#endif
   ueAppCb_TxId rcvdTxId; /* ue007.101:ccpu00117835 enodeb TxId used */
#ifdef TOTAL_ENB
/* ue009.101: Added support to send measurement support */
   UeMeasCfg    measCfg;
#endif
}UeAppCb;

/*  ue002.101: Multi ue support changes */
/* ueAppCellCb structure */
typedef struct _ueAppCellCb
{
   U16            cellIdx;
   CmLteCellId    cellId;
   U16            numUeCfgd;
   U16            startRnti;
   UeAppCb        ueAppCbLst[UE_NUM_PER_CELL];
}UeAppCellCb;

/* uesim global control block structure */

typedef struct _ueSimAppCb
{
   TskInit        init;         /* Task initialization structure */
   CmTqCp         ueTqCp;             /* Timing queue control point */
   CmTqType       ueTq[UE_APP_TQSIZE]; /* Timing queue */
   TmrCfg         tmr;                /* Timer config */
   CmTimer        timers[UE_APP_MAX_TMRS];/* Interface timer control blocks
                                        one for each running timer */
   UeAppNhuSapCb  *rrcSapCb;     /* Upper RRC SAP for this UE with eNodeB. */
   UeAppPjuSapCb  *pdcpSapCb;    /* Upper PDCP SAP for this UE with eNodeB. */
   UeAppDataCb    dataCb;       /* UE Data Application routing information */
   UeAppCellCb    cellCb[UE_NUM_CELL];
/* ue008.101: Flag to indicate Attach/Detach has been started --*/
#if MULTI_UE_ATTACH
   U16           multAtchStrt;/* Flag to indicate state of Multi Attach tmr */
   U16           multDtchStrt;/* Flag to indicate state of Multi Attach tmr */
#endif
#ifdef LTE_E2E_PERF_MEAS
   U16            numAttachCompSent;
#endif
   U16            numRachReqSent;
#ifdef ENB_PERF_MEAS
   U8             state; /* Ready To generate UL Load */
   U32            wait;
#endif
}UeSimAppCb;


EXTERN UeSimAppCb ueSimAppCb;

typedef enum ueAppEsmKeyType
{  UE_ESM_TRANS_KEY,
   UE_ESM_BID_KEY
}UeAppEsmKeyType;

/* ue002.101: Support of reading configuration parameters now 
   from a filesystem supportive platform config file;
   Example: Linux */
#ifndef NOFILESYS
EXTERN U32 UE_APP_SELF_ETH_INF_ADDR;
EXTERN U32 UE_APP_SELF_PDN_ADDR;
EXTERN U32 UE_APP_DATA_SRVR_ADDR;
EXTERN U32 UE_APP_DATA_SRVR_PORT;
#endif
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 * depends on the RRC timer. */
EXTERN U32 UE_RRC_TIMER;
#endif
/* ue003.101: added for latency related changes */
#ifdef UE_COMPUTE_LATENCY
typedef struct timeStampInfo
{
   U8               status;
   CmLteTimingInfo  tmInfo;
   struct timespec  ts;
}TimeStampInfo;

typedef struct timeDelayInfo
{
   TimeStampInfo   rachReq;
   TimeStampInfo   rrcConReq;
   TimeStampInfo   rrcConRecfgComp;
   TimeStampInfo   attachComp;
}TimeDelayInfo;
#endif

/* UE-EMM utility functions prototype*/

EXTERN S16 ueAppUtlBldAttachReq ARGS((UeAppCb *ueCb, CmNasEvnt **ueEvt,
                                      U8       miType));

EXTERN S16 ueAppUtlBldAttachComplete ARGS((UeAppCb *ueCb, CmNasEvnt **ueEvt));

EXTERN S16 ueAppUtlBldIdentityResp ARGS((UeAppCb *ueCb, CmNasEvnt **ueEvt));

EXTERN S16 ueAppUtlBldAuthResp ARGS((UeAppCb *ueCb, 
                                     CmNasEvnt **ueEvt,
                                     CmEmmAuthPrmRES *authParmRes));

EXTERN S16 ueAppUtlBldSecModComplete ARGS((UeAppCb *ueCb, CmNasEvnt **ueEvt));

EXTERN S16 ueAppUtlBldDetachReq ARGS((UeAppCb  *ueCb,
                                      CmNasEvnt **ueEvt, 
                                      U8        detachType, 
                                      U8        miType));

/* ue007.101: Building Detach Accept */
EXTERN S16 ueAppUtlBldDetachAcc ARGS((UeAppCb  *ueCb,
                                      CmNasEvnt **ueEvt));


/* UE-ESM utility functions prototype*/
EXTERN S16 ueAppUtlBldPdnConReq ARGS((UeAppCb *ueCb, CmNasEvnt **ueEvt));
EXTERN S16 ueAppUtlBldActDefltBerContextAccept ARGS((UeAppCb *ueCb, 
                                                     CmNasEvnt **ueEvt));

EXTERN S16 ueAppUtlBldActDefltBerContextRej ARGS((UeAppCb  *ueCb, 
                                                  CmNasEvnt **ueEvt,
                                                  U8        cause,
                                                  U8        bId, 
                                                  U8        tId 
                                                  ));
/* ue003.101: Added for dedicated bearer support */
EXTERN S16 ueAppUtlBldActDedBerContextAccept ARGS((UeEsmCb *esmCb,
                                                   UeAppCb *ueCb, 
                                                     CmNasEvnt **ueEvt));

EXTERN S16 ueAppSndServiceRequest ARGS((
 UeAppCb *ueAppCb
 ));

EXTERN S16 ueAppRcvRRCPaging ARGS((
 U16                  cellId,
 NhuPCCH_Msg          *pcchMsg
 ));

EXTERN S16 ueAppUtlBldServiceReq ARGS ((
  UeAppCb *ueCb,
  CmNasEvnt **ueEvt
));

/* ue008.101: Fix for compilation warnings*/
EXTERN S16 ueAppSndBrResAllocReq ARGS ((UeAppCb    *ueAppCb));

/* RRC Build Utilities protoypes */

EXTERN S16  ueAppUtlBldRRCConReq ARGS((NhuDatReqSdus    **pdu));

EXTERN S16  ueAppUtlBldRRCConSetupComplete ARGS((NhuDedicatedInfoNAS *nasPdu,
                                                 NhuDatReqSdus       **pdu,
                                                 UeAppCb             *ueAppCb));
/* ue007.101: ccpu00117835 enodeb TxID passed */
EXTERN S16  ueAppUtlBldRRCSecModeComplete ARGS((NhuDatReqSdus    **pdu, U32 Sec_ModeTxId));
/* ue005.101: Added support for UeCapability */
#ifdef UE_RAD_CAP
EXTERN S16 ueAppUtlBldRRCUeCapInfo ARGS((NhuDatReqSdus    **pdu,U32 Cap_InfoTxId));
EXTERN S16 ueAppUtlFillRRCUECapIE ARGS((Ptr  evnt, NhuUE_EUTRA_Cap *ueEutraCap));
EXTERN S16 ueAppLimHdlRRCUeCapEnq ARGS((UeAppCb *ueAppCb));
#endif
EXTERN S16  ueAppUtlBldRRCConReCfgComplete ARGS((NhuDatReqSdus  **pdu, U32 transId));

EXTERN S16 ueAppUtlBldRRCUpLinkTrfr ARGS((NhuDedicatedInfoNAS *nasPdu,
                                          NhuDatReqSdus       **pdu));

EXTERN S16 ueAppUtlFillTknStrOSXL ARGS((TknStrOSXL *ptr,
                                        U16         len,
                                        Data       *val,
                                        Ptr         memPtr));

EXTERN S16 ueAppUtlFillTknStrBSXL ARGS((TknStrBSXL *ptr,
                                        U16         len,
                                        U8          val,
                                        Ptr         memPtr));

EXTERN S16 ueAppUtlFillTknStr4 ARGS((TknStr4 *ptr,
                                     U8      len,
                                     U8      val));


/* Function prototypes for ESM handlers */
EXTERN S16 ueEsmHdlIncUeEvnt ARGS((CmNasEvnt *evnt));
EXTERN S16 ueEsmHdlOutUeEvnt ARGS((CmNasEvnt *evnt));

EXTERN S16 ueAppUtlAddEsmCb ARGS((UeEsmCb **esmCb,UeAppCb *ueAppCb));
EXTERN S16 ueAppUtlFndEsmCb ARGS((UeEsmCb **esmCb, U8 key, 
                                  UeAppEsmKeyType  type, UeAppCb *ueAppCb));
EXTERN S16 ueAppUtlDelEsmCb ARGS((UeEsmCb *esmCb, UeAppCb *ueAppCb));
EXTERN S16 ueAppUtlMovEsmCbTransToBid  ARGS((UeEsmCb *esmCb,UeAppCb *ueAppCb));


/* All Application Controller, Lower Interface and Public function prototypes */
EXTERN S16 ueAppActvInit ARGS((Ent    entity,
                               Inst   inst,
                               Region region,
                               Reason reason));

EXTERN S16 ueAppActvTsk ARGS((Pst           *pst,
                              Buffer        *mBuf));

EXTERN S16 ueAppRouteInit ARGS((Void));

EXTERN S16 ueAppCfgrPdnAssignedAddr ARGS((U32 pdnAsgndAddr,U16 cellIdx, U16 ueId));

EXTERN S16 ueAppSndArpCompInd ARGS((UeAppCb *ueAppCb));

EXTERN U16 ueAppCalcIPChecksum ARGS((U8  *ipPkt, 
                                     U32 ipHdrLen));

EXTERN S16 ueAppRcvEmmMsg ARGS((CmNasEvnt *ueEvnt,  U8 emmMsgType, 
                                UeAppCb *ueAppCb));

EXTERN S16 ueAppRcvRRCConSetup ARGS((NhuDatIndSdus *datIndSdus));

EXTERN S16 ueAppLimSndToLower ARGS((CmNasEvnt  *ueEvnt,
                                    U8          msgType,
                                    UeAppCb    *ueAppCb));

EXTERN S16 ueAppLimSndRRCMsg ARGS((NhuDatReqSdus *datReqSdu, UeAppCb *ueAppCb));

#ifndef SS_CAVIUM
EXTERN S16 ueAppLimSndPdcpMsg ARGS((CONSTANT U8* data, U32 len,
                                    UeAppCb *ueAppCb));
#else
EXTERN S16 ueAppLimSndPdcpMsg ARGS((Void *work, UeAppCb *ueAppCb));
#endif



EXTERN S16 ueAppEmmHdlIncUeEvnt ARGS((CmNasEvnt  *evnt, UeAppCb *ueAppCb));

EXTERN S16 ueAppEmmHdlOutUeEvnt ARGS((CmNasEvnt  *ueEvnt, UeAppCb *ueAppCb));

EXTERN S16 ueAppEsmHdlIncUeEvnt ARGS((CmNasEvnt  *evnt,UeAppCb *ueAppCb));

EXTERN S16 ueAppEsmHdlOutUeEvnt ARGS((CmNasEvnt  *ueEvnt,UeAppCb *ueAppCb));

EXTERN S16 ueAppLimHdlUeEvnt ARGS((CmNasEvnt  *ueEvnt, UeAppCb *ueAppCb));

EXTERN S16 ueAppUtlCreateEvent ARGS((CmNasEvnt **newEvnt, U8 evntType));

EXTERN S16 ueAppUtlFreeEvent ARGS((CmNasEvnt  **evnt ));

EXTERN S16 ueAppTmrEvnt ARGS((Ptr  cb, S16  tmrEvnt));
/* ue006.101: Fix for CID:1465-02-01, DefectId:ccpu00116336. 
   Removing the compiler warning.*/ 
EXTERN S16 ueAppStartTmr ARGS((U16 cellId,U8  tmrType, U32  wait));

EXTERN S16 ueAppSndAttachRequest ARGS((UeAppCb *ueAppCb));

EXTERN S16 ueAppEdmDecode ARGS ((NhuDedicatedInfoNAS  *nasPdu,CmNasEvnt **ueEvnt));

EXTERN S16 ueAppLimHdlRRCSecModeCmd ARGS((UeAppCb *ueAppCb));

/* ue003.101: Added for dedicated bearer support */
EXTERN S16  ueAppUtlBldBrResAllocReq ARGS((UeEsmCb *esmCb,
                                       UeAppCb *ueAppCb, 
                                       CmNasEvnt **actDedBrAcc)); 
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
EXTERN S16  ueAppUtlBldBrResModReq ARGS((UeEsmCb *esmCb,
                                       UeAppCb *ueAppCb, 
                                       CmNasEvnt **actDedBrAcc)); 

EXTERN  S16 ueAppIncActvDedBearerReq ARGS((
UeEsmCb *esmCb,
UeAppCb *ueAppCb,
CmNasEvnt *esmEvnt
));

#ifdef SS_CAVIUM
EXTERN S16  ueUtlIpv4InetToArr ARGS((U8 *addrArr, UeInetIpAddr *address));
#else
EXTERN S16  ueUtlIpv4InetToArr ARGS((U8 *addrArr, CmInetIpAddr *address));
#endif

#ifdef ENB_PERF_MEAS
EXTERN S16 ueAppTti ARGS((CmLteTimingInfo    tti));
#endif

EXTERN S16 ueAppLimHdlRRCConReCfg ARGS(( UeAppCb *ueAppCb, U32 transId));

/* ue008.101: Modified function prototype */
EXTERN S16 ueAppSndServiceReqMsg ARGS((UeAppCb     *ueAppCb));
#endif
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 * depends on the RRC timer. */
/* RRC-REEST START */
EXTERN S16  ueAppUtlBldRRCReEstlmntReqMsg ARGS((NhuDatReqSdus **pdu, UeAppCb *ueAppCb));

EXTERN S16  ueAppUtlBldRRCReEstlmntCmpltMsg ARGS(( NhuDatReqSdus **pdu, U32 transId));

EXTERN S16  ueAppRcvRRCConReestab ARGS((NhuDatIndSdus *datIndSdus));

EXTERN S16 ueAppRcvRRCConReestabRej ARGS(( NhuDatIndSdus *datIndSdus));
/* RRC-REEST END*/
#endif
/**********************************************************************
         End of file:     ue_app.x@@/main/1 - Sun Mar 28 22:59:21 2010
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp      1. Initial Release
/main/1+   ue002.101  sv      1. Multi ue support changes.
                              2. Changes to support reading uesim
                                 configuration from file.
                              3. Changes to support MSPD CL
/main/1+   ue003.101  rp      1. Added support for dedicated bearers.
                              2. Added support for paging.
/main/1+   ue005.101  cshekar 1. Added support for ue capability.
/main/1+   ue006.101  sgm     1. Fix for CID:1465-02-01, DefectId:
                                 ccpu00116336. Removing the compiler
                                 warning.
/main/1+   ue007.101  rk      1. Added support for network initiated Detach.
                      ms      1. enodeb TxId used.   
/main/1+   ue008.101 ragrawal 1. CRID:ccpu00117391 ERAB RELEASE support.
                              2. Updated UeAppCellCb & UeAppCb for Multi-UE Attach/detach
                              3. Fix for compilation warning.
                              4. Modified function prototype for ueAppSndServiceReqMsg().
/main/1+   ue009.101 akaranth 1. Added feature to drop the RRC messages 
                                 depends on the RRC timer.
                              2. Added support send Measurement support.
*********************************************************************91*/
