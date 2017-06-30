
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C interface file

     Desc:     Interface file which defines the structures

     File:     egac_acc.x

     Sid:      egac_acc.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:22 2015

     Prg:      an

*********************************************************************21*/

#ifndef __EG_ACC_X__
#define __EG_ACC_X__

#ifdef __cplusplus
extern "C" {
#endif

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for EG */
#include "leg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */
#include "cm_xta.h" 

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
/* eg004.201 Header files included for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "leg.x"           /* layer management typedefs for EGCP */
#include "egt.x"           /* typedefs for EGCP */
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for EGCP */
#include "eg_tpt.x"            /* EGTP TPT module defines */

#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#ifdef NOT_USED
#include "egac_acc.x"      /* typedefs for EGCP acceptance tests */
#include "egac_egt.x"
#endif
/* eg004.201 Header files included for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"
#endif


EXTERN Bool egAcFlag[EGAC_MAX_FLAGS];
EXTERN Txt  egAcFlagStr[EGAC_MAX_FLAGS][50];


/* Common interface element */
typedef struct egAcCmInfo
{
   SuId              suId;
   SpId              spId;
   Reason            reason;

   Buffer            mBuf;

}EgAcCmInfo;

typedef struct egAcHitInfo
{
   EgAcCmInfo       cmInfo;

   UConnId           suConId;
   UConnId           spConId;
/*   CmTptAddr         servTAddr;--*/
   U8                srvcType;
   CmTptAddr         remAddr;
   CmTptAddr         localAddr;
   CmIpHdrParm       hdrParm;
   U8                choice;
   Buffer            *mBuf;
   Action            action;
}EgAcHitInfo;

typedef struct egAcHitAssocCb
{
   UConnId    suConId;   /* service user connection Id   */
   UConnId    spConId;   /* service provider connection Id   */
             
   Bool       inUse;     /* flag to indicate in Use or not */
                      
   CmTptAddr  localAddr; /* Local Address */
} EgAcHitAssocCb; 

typedef struct egAcHitCb
{  
   U16          nxtConnId;   /* next Connection Id  */
   EgAcHitAssocCb assoc[10]; /* Association Control blocks  */
} EgAcHitCb; 

typedef struct egAcTACb
{
   Txt               ipAddr[20];   /*Ipaddress   */
   U16               glbNum;

   SpId              tuclId;
   SpId              dtuclId;

}EgAcTACb;

#ifdef EGTP_C
typedef struct egtEgErrIndEvt
{
EgErrEvnt  errInd;       /* Error event strucutre */
}EgtEgErrIndEvt;

typedef struct edmErrIndEvt
{
EgErrEvnt  errInd;       /* Error event strucutre */
}EdmEgErrIndEvt;

typedef struct egtEgSigCfmEvt
{
CmTptAddr   *localAddr; /* Local node address */
CmTptAddr   *remAddr;   /* Remote node address */
TknU32      lclTeid;    /* Local Tunnel Identifier */
TknU32      transId;   /* Transaction IDentifier */
EgMsg  *egMsg;       /* GTP message */
}EgtEgSigCfmEvt;

typedef struct egtEgSigRspEvt
{
EgMsg  *egMsg;       /* GTP message */
}EgtEgSigRspEvt;


typedef struct egtEgLclDelCfmEvt
{

U32          transId;    /* Transaction ID */
U32          teid;      /* self TEID */
CmStatus     status;

}EgtEgLclDelCfmEvt;

typedef struct egtEgStaCfmEvt
{
U8           eventType;    /* Status event type */
EgPathInfo   *pathInfo;
CmStatus     status;
}EgtEgStaCfmEvt;

typedef struct egtEgStaIndEvt
{
U8           eventType;    /* Status event type */
EgPathStatus   *pathStatus;
}EgtEgStaIndEvt;

typedef struct egtEgSigIndEvt
{
EgMsg  *egMsg;       /* GTP message */
CmTptAddr   *localAddr; /* Local node address */
CmTptAddr   *remAddr;   /* Remote node address */
TknU32      lclTeid;    /* Local Tunnel Identifier */
}EgtEgSigIndEvt;

typedef struct egtEgSigReqEvt
{
EgMsg  *egMsg;       /* GTP message */
}EgtEgSigReqEvt;
#endif /* EGTP_C */

typedef struct egAcEdmInfo
{
   U8       choice;    /* choice to select the kind of event */
   U8   intfType;
   Buffer *mBuf;
}EgAcEdmInfo;

typedef struct egAcEgtInfo
{
   EgAcCmInfo      cmInfo;
   Status          status;
   TknU32          peerId;
   UConnId         suConnId;
   UConnId         spConnId;
   U8              choice;   /* choice to select the kind of event */
   U32             teid;
   S16             seqNo;   
   union
   {
#ifdef EGTP_C 
      EgtEgSigReqEvt egSigReqEvt;        /* GTP Sig Req */
      EgtEgSigIndEvt egSigIndEvt;        /* GTP Sig Ind */
      EgtEgStaIndEvt egStaIndEvt;        /* GTP Sta Ind */
      EgtEgStaCfmEvt egStaCfmEvt;        /* GTP Sta Cfm */
      EgtEgLclDelCfmEvt egLclDelCfmEvt;  /* GTP Lcl del Cfm */
      EgtEgErrIndEvt egErrIndEvt;        /* GTP Err Ind */
      EdmEgErrIndEvt errEvt;             /* GTP STUB Err Ind */
      EgtEgSigRspEvt egSigRspEvt;        /* GTP Sig Rsp */
      EgtEgSigCfmEvt egSigCfmEvt;        /* GTP Sig Cfm */
#endif /* EGTP_C */
      EgMngmt      egMngmt;             /* Management LEG interface structure */
   }u;
}EgAcEgtInfo;

#ifdef EGTP_U

/* eGTP-U event message */
typedef struct eguAcInfo
{  
   SpId     suId;
   EgtUEvnt eguAcEvntMsg;
}EguAcInfo;

#endif

/* Message queue element */
typedef struct egAccMsgQElm
{
   Pst           pst;                   /* pst structure         */
   Buffer        *mBuf;                 /* message Buffer        */
   union
   {
      EgAcEgtInfo  egtInfo;             /* Information at the EGT interface */
      EgAcEdmInfo  edmInfo;             /* Information at the EDM STUB interface */
      EgAcHitInfo  hitInfo;             /* Information at the HIT interface */
      EgMngmt      egMngmt;             /* Management LEG interface structure */
#ifdef HI
      HiMngmt      hiMngmt;             /* Management structure for LHI inteface */
#endif
#ifdef EGTP_U
      EguAcInfo  eguAcMsg;            /* eGTP-U event message */
#endif
   }u;

   PMSGFREEFS16      msgFreeFun;       /* Function to free the msg */
}EgAccMsgQElm;

typedef struct egAcDirectives
{
   ProcId  xtaProcId;                 /* xta ProcId  */
   ProcId  hiProcId;                  /* TUCL ProcId */
   U8             tptType;
}EgAcDirectives;

typedef struct egAcEgtMsgInfo 
{
   U32  teid;
   U32  rmTeid;
   U16  seqNo;
}EgAcEgtMsgInfo;


/* Acceptance Test Global Structure */
typedef struct egAccCb
{
   EgAcTACb      taCb;
   EgAcHitCb     hitCb;
   U8            intfType;

   EgIeDictCfg   selfIeCfg;/* Self GM Entry siganture */
   EgIeDictCfg   peerIeCfg;/* Self GM Entry siganture */

   Bool   selfIeCfgDone;   /* Self GM Entry siganture */
   Bool   peerIeCfgDone;   /* Self GM Entry siganture */

   U8            intfTypeMap[MAX_APP_INTERFACES]; /* Interface to index mapping */

   EgGmDictCfg   selfGmMsgCfg[MAX_APP_INTERFACES];/* Self GM Entry siganture */
   EgGmDictCfg   peerGmMsgCfg[MAX_APP_INTERFACES];/* Self GM Entry siganture */

   Bool   selfGmMsgCfgDone[MAX_APP_INTERFACES];   /* Self GM Entry siganture */
   Bool   peerGmMsgCfgDone[MAX_APP_INTERFACES];   /* Self GM Entry siganture */

   EgAcDirectives   directives;      /* directives  */     
   EgAcHitInfo saveDat; /* saves the Udatreq buffer. Used by UdatInd */
   EgAcEgtMsgInfo egAcMsgInfo[EGAC_MAX_PROCS][EGAC_LEG_MAX_TRANSID];
#ifdef EGAC_LOOP_TEST
   EgAcEgtMsgInfo egAcCrtInfo; /* Used for th eloop testing only */
#endif /* loop testing */
}EgAccCb;

/* Acceptance Build Msg */
typedef struct egBuildMsg
{
Pst         pst;          /* Post structure */
SpId        spId;          /* service provider id */
CmTptAddr   localAddr;    /* Local node address */
CmTptAddr   remAddr;      /* Remote node address */
TknU32      lclTeid;       /* Local Tunnel Identifier */
TknU32      transId;       /* Transaction Identifier */
TknU8       crtFlag;       /* Create tunnel or not */
TmrCfg      T3;            /* Request timer expiry */
#ifdef EGTP_C
EgPathInfo   pathInfo;
#endif /* EGTP_C */
U8           eventType;    /* Used for Status Req: Path/Tunnel */
U32         seqNo;
}EgBuildMsg;

typedef struct _egAcSeqNo 
{
   Bool present;
   U16 value;
}EgAcSeqNo;

typedef struct _egAcTCCb
{

   EgAcSeqNo  seqNo[NMB_MAX_SEQ_NOS];
   U8         intfType;
   EgAcDirectives directives;
   /* DTUCL */
}EgAcTCCb;

EXTERN EgAccCb egAccCb;


/**************************************************************************
*                          FUNCTION   PROTOTYPES
**************************************************************************/


/*-- eg003.201 : changes from eg006.102--*/

#ifdef SS_MULTIPLE_PROCS
PUBLIC S16 egAcHiActvInit ARGS((
ProcId procId,         /* procId */
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void **xxCb           /* Protocol Control Block */
));
#else
PUBLIC S16 egAcHiActvInit ARGS((
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
));
#endif

#ifdef EGTP_C
PUBLIC S16 egAcGetFteidFrmMsg ARGS
((
EgMsg   *egMsg
));

PUBLIC S16 egAcEncEgMsg ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg   *egMsg,  /* the egtp message to be encoded */
Buffer      **mBuf    /* to hold the encoded buffer */
));

PUBLIC S16 egAcDecEgMsg ARGS
((
EgMsg   *egMsg,     /* to hold the decodeed egtp message */
Buffer      *mBuf       /* the encodeed buffer */
));

/* This is common function used by EDM stuff and XTA */
PUBLIC S16 egAcEdmBuildEgMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8                msgType,
EgMsg **egMsg
));

#endif /* EGTP_C */

#ifdef EGTP_U
PUBLIC S16 egUAcEncEgMsg ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgUMsg         *eguMsg,  /* the egtp message to be encoded */
Buffer        **mBuf     /* to hold the encoded buffer */
));

PUBLIC S16 egUAcDecEgMsg ARGS
((
EgUMsg        *eguMsg,    /* to hold the decodeed egtp message */
Buffer        *mBuf       /* the encodeed buffer */
));

PUBLIC S16 egUAcUtlDEdmBuildMsg ARGS
((
  CmXtaTCCb         *tcCb,
  CmXtaSpCb         *spCb,
  EgUMsg      **eguMsg
 ));

 PUBLIC Void  egUAcEgtBuildEgHeader ARGS
 ((
 CmXtaTCCb         *tcCb,
 CmXtaSpCb         *spCb,
 EgUMsgHdr         *eguHdr,
 U8                msgType
 ));

#endif /* EGTP_U */

PUBLIC S16 egAcHiActvTsk ARGS((
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
));

PUBLIC S16 populateIeConfigInTA  ARGS
((
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
U8     diffPeerCfg
));

PUBLIC S16 populateGmConfigInTA ARGS
((
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
U8     intfType,
U8     diffPeerCfg
));

#ifdef EGTP_C
/*******************************************************************************/
   
PUBLIC S16 egAcEdmBuildEgS3Message ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgS4Message ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgS5Message ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgS10Message ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgS11Message ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgS16Message ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgSMMessage ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));

PUBLIC S16 egAcEdmBuildEgSNMessage ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8         intfType,
Mem         *memInfo
));


PUBLIC Void  egEgtBuildCrtSesReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void   egEgtBuildCrtSesRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildCrtBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildCrtBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildBreResCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildBreResFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildModBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildModBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDelSesReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDelBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDwLnkDatNotFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDelSesRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDelBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDwDatLnkNotMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDwDatLnkNotAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildModBreCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildModBreFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildUpdBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildUpdBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDeActvBreCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildDeActvBreFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3FwdRelReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3FwdRelRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3FwdRelCmpNtfMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3FwdRelCmpAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3DetNtfMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3DetAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3IdentReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3IdentRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3CtxReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3CtxRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3CtxAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS3RelCancelReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3RelCancelRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3CsPageIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3RanInfoRlyMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS3AlrtMmeNotFnMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS3AlrtMmeAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS3UeActNotFnMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS3UeActAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS3SuspndNotFnMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS3SuspndAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS4DelBreCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS4BreResCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS4CrtSesReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS4CrtSesRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS4ModBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS4ModBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4DelSesReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4DelSesRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4ChgNtfReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4ChgNtfRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4ModBreCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4ModBreFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4DelBreFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void egEgtBuildS4BreResFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4DwlnkDatNotflrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4TraceSessActvMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4TraceSessDeActvMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4StopPagingIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4CrtBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4CrtBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4UpdBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4UpdBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4DelBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4DelBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4CrtIndDatFwdTunReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4CrtIindDatFwdTunRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4DelIndDatFwdTunReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4DelIndDatFwdTunRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4RelAccBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4RelAccBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void egEgtBuildS4DwLnkDatNotMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS4DwLnkDatnNotAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10CtxReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS10FwdrelReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS10FwdrelRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10CtxRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS10CtxAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS10IdentReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10IdentRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10FwdrelCmpntfMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10FwdrelcmPackMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10FwdaccsCtxntfMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10FwdaccsCtxackMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10RelcancelReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10RelcancelRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS10CfgtfrtnlMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11UpdUplnReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11UpdUplnRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11SuspendNotMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11SuspendAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11ResumeNotMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11ResumeAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11CrtFwdTunReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11CrtFwdTunRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS11TraceSessActvMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11TraceSessDeactvMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11DelPdnConSetReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11DelPdnConSetRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11DelIndDatFwdTunReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11DelIndDatFwdTunRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11RelAccBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS11RelAccBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16FwdRelReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS16FwdRelRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS16IdReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS16IdRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS16CtxReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16CctxRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16CtxAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16FwdRelCmpntfMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16FwdAccsCtxntfMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16FwdRelCmpAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16FwdAccsCtxAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16RelCancelReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16RelCancelRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16RanInforLyMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16SuspndNotfnMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS16SuspndAckMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));



PUBLIC Void  egEgtBuildSMSesStartReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSMSesStartRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSMSesUpdReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSMSesUpdRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSMSesStopReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSMSesStopRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildSNSesStartReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSNSesStartRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSNSesUpdReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSNSesUpdRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildSNSesStopReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildSNSesStopRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5ChgNtfReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5ChgNtfRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5TrcSesActMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5TrcSesDeactMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5StopPagingIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5DelPdnConsetReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5DelPdnConsetRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5UpdPdnConsetReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));


PUBLIC Void  egEgtBuildS5UpdPdnConsetRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

EXTERN Void  egAcEgtBuildEgIeHeader ARGS
((
EgIe         *egIe,
U8           ieType,
U8           ieInst,
U8           dataType
));

EXTERN Void  egAcEgtBuildEgHeader ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsgHdr         *egHdr,
U8                msgType
));


/*************************************
 * eg009.201 - Added for S2A and S2B *
 *************************************/
PUBLIC S16 egAcEdmBuildEgS2aS2bMessage ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8              msgType,
EgMsg           **egMsg,
U8             intfType,
Mem            *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BCrtSesReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem            *memInfo
));

PUBLIC Void   egEgtBuildS2AS2BCrtSesRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BCrtBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BCrtBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BDelSesReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BDelPdnConReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BDelBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BDelSesRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BDelBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BModBreCmdMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BModBreFlrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));
PUBLIC Void  egEgtBuildS2AS2BUpdBreReqMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BDelPdnConRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BUpdBreRspMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BTrcSessActMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));

PUBLIC Void  egEgtBuildS2AS2BTrcSessDeactMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg           **egMsg, U8   intfType,
Mem              *memInfo
));
#endif /* EGTP_C */

/****************************************************************************
 *                          EG-SM PRimitive                                 *
 ****************************************************************************/

EXTERN S16 egAcSmMiLegCfgCfm ARGS(( Pst     *pst, EgMngmt  *cfm));
EXTERN S16 egAcSmMiLegCntrlCfm ARGS(( Pst     *pst, EgMngmt  *cfm));
EXTERN S16 egAcSmMiLegStaInd ARGS(( Pst     *pst, EgMngmt  *usta));
EXTERN S16 egAcSmMiLegTrcInd ARGS(( Pst     *pst, EgMngmt  *trc, Buffer   *mBuf));
EXTERN S16 egAcSmMiLegStsCfm ARGS(( Pst     *pst, EgMngmt  *sts));
EXTERN S16 egAcSmMiLegStaCfm ARGS(( Pst     *pst, EgMngmt  *sta));


/*****************************************************************************/
PUBLIC LegIeEntry* egGetIeFrmIeDict ARGS (( U8 ieType ));
PUBLIC LegMsgEntry* egGetMsgFrmGmDict ARGS (( U8 msgType, U8  intfType));

EXTERN S16 egAcCmpTptAddr ARGS((CmTptAddr *one, CmTptAddr *two, Bool *addressMatch));

#ifdef EGTP_U
EXTERN S16 eguAcEdmBuildEchoReqMsg ARGS (( CmXtaTCCb *tcCb, CmXtaSpCb *spCb, 
                                         U32 msgType, EgUMsg **eguMsg, 
                                         Mem *memInfo));

EXTERN S16 eguAcEdmBuildEchoRspMsg ARGS(( CmXtaTCCb *tcCb, CmXtaSpCb *spCb,
                                        U32 msgType, EgUMsg **eguMsg,
                                        Mem *memInfo));

EXTERN S16 eguAcEdmBuildErrIndMsg  ARGS (( CmXtaTCCb *tcCb, CmXtaSpCb *spCb,
                                         U32 msgType, EgUMsg **eguEvtMsg,
                                         Mem *memInfo));

EXTERN S16 eguAcEdmBuildSuppExtHdrNotMsg ARGS (( CmXtaTCCb *tcCb, 
                                              CmXtaSpCb *spCb, U32 msgType,
                                             EgUMsg **eguEvtMsg, Mem *memInfo)); 

EXTERN S16 eguAcEdmBuildEndMarkerMsg ARGS (( CmXtaTCCb *tcCb, CmXtaSpCb *spCb,
                                             U32 msgType, EgUMsg **eguEvtMsg,
                                             Mem *memInfo));
#endif /* EGTP_U */
/* eg001.102 rss        1. Multithreaded performance changes. */
EXTERN S16 eguValidatePst ARGS((Pst  *recvPst, Pst  *expPst));
#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __EG_ACC_X__ */

/**********************************************************************

         End of file:     egac_acc.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:22 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/2      eg001.102 rss        1. Multithreaded performance changes.
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix
                                     warnings
/main/3     eg004.201 magnihotri  1. Header files included for 
                                     eGTP-C PSF
            eg009.201 asaurabh    1. Added for S2B and S2A 
*********************************************************************91*/
