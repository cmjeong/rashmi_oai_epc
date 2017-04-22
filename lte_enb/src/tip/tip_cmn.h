
/**********************************************************************
     Name:     LTE-PHY layer 
  
     Type:     C include file 
  
     Desc:     Defines required by the LTE PHY-RRC control (CTF) interface.

     File:     ctf.h 

     Sid:      ctf.h@@/main/3 - Thu Feb 16 19:38:59 2012

     Prg:      vkulkarni

**********************************************************************/
#ifndef __TIP_CMN_H__
#define __TIP_CMN_H__

#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list  defines  */
#include "cm_hash.h"       /* Common hashlist  defines */
#include "cm_lte.h"        /* Common LTE defines */
#include "cm_inet.h"
#include "cm_tpt.h"
#include "szt_asn.h"       /* S1AP RRM control Interface */
#include "nhu_3gasn.h" /* 3G RRC ASN control Interface */

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lte.x"       /*  Common UMTS includes */
#include "cm_lib.x"
#include "cm_inet.x"
#include "cm_tpt.x"

/* header include files related to lower layer interfaces */
#include "nhu.h"           /* NHU interface defines */
#include "pju.h"           /* PDCP data interface defines */
#ifdef RM_INTF
#include "rmu.h"           /* RRM interface defines */
#endif /*RM_INTF*/
#include "nlu.h"           /* SON interface defines */
#include "cpj.h"           /* PDCP conrol interface defines */
#include "rgr.h"           /* MAC RRM control Interface */
#include "ctf.h"           /* PHY RRM control Interface */
#include "szt.h"           /* S1AP RRM control Interface */
#include "sct.h"           /* S1AP RRM control Interface */

#include "czt.h"           /* X2AP Upper Interface */
#include "sct.h"           /* S1AP RRM control Interface */
#include "lrg.h"           /* MAC RRM control Interface */
#include "egt.h"           /* DATA app, GTP interface   */
#ifdef SZTV3
#include "szt_3gasn.h"
#endif

#include "nhu.x"           /* NHU Interface includes */
#include "pju.x"           /* PJU Interface includes */
#include "cm_lte.x"
#include "cm_lte_rrm.x"
#include "rmu.x"           /* RRM Interface includes */
#include "nlu.x"           /* SON Interface include */
#include "cpj.x"           /* CPJ Interface includes */
#include "rgr.x"           /* MAC RRM control Interface */
#include "ctf.x"           /* PHY RRM control Interface */
#include "szt_asn.x"       /* S1AP RRM control Interface */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#ifdef SZTV3
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* S1AP RRM control Interface */
#include "nhu_asn.x"       /* RRC ASN Interface */

#include "nhu_3gasn.x"       /* 3G RRC ASN Interface */

#include "czt.x"           /* X2AP Upper Interface */
#include "sct.x"           /* X2AP RRM control Interface */
#include "lrg.x"           /* MAC RRM control Interface */
#include "egt.x"           /* DATA app, GTP interface   */
#include "tip.h"
#include "rl_interface.h"

#define EVTTIPINITMSG      100
#define EVTL1TIPPMSG       101
#define EVTMACTIPPMSG    102
#define EVTRLCTIPPMSG     103
#define EVTPDCPTIPPMSG   104
#define EVTRRCTIPPMSG     105
#define EVTAPPTIPPMSG     106

#define MAX_BUFF_LEN_L2_L3           8196
#define TIP_HDR_LEN                  16

typedef enum tipModName 
{
   TIP_MOD_RRC,
   TIP_MOD_DATARELAY,
   TIP_MOD_RLC,
   TIP_MOD_PDCP,
   TIP_MOD_MAC,
   TIP_MOD_PHY,
   TIP_MOD_END
} TipModId;

typedef enum tipIntfMsgId
{
   TIP_MSG_MAC_INIT_IND, 
   TIP_MSG_MAC_INIT_REQ, 
   TIP_MSG_MAC_INIT_RSP, 
   TIP_MSG_RLC_INIT_IND, 
   TIP_MSG_RLC_INIT_REQ, 
   TIP_MSG_RLC_INIT_RSP, 
   TIP_MSG_PDCP_INIT_IND,
   TIP_MSG_PDCP_INIT_REQ,
   TIP_MSG_PDCP_INIT_RSP, 
   TIP_MSG_HEARTBEAT_REQ, 
   TIP_MSG_HEARTBEAT_RSP,
   TIP_MSG_MAC_CELLCONFIG_REQ,
   TIP_MSG_MAC_CELLCONFIG_RSP,
   TIP_MSG_MAC_CELLRECONFIG_REQ,
   TIP_MSG_MAC_CELLRECONFIG_RSP,
   TIP_MSG_MAC_CELLDELETE_REQ,
   TIP_MSG_MAC_CELLDELETE_RSP,
   TIP_MSG_MAC_BROADCASTMSG_REQ,
   TIP_MSG_MAC_BROADCASTMSG_RSP,
   TIP_MSG_MAC_UECONFIG_REQ,
   TIP_MSG_MAC_UECONFIG_RSP,
   TIP_MSG_MAC_UERECONFIG_REQ,
   TIP_MSG_MAC_UERECONFIG_RSP,
   TIP_MSG_MAC_UEDELETE_REQ,
   TIP_MSG_MAC_UEDELETE_RSP,
   TIP_MSG_MAC_CELLSTART_IND,
   TIP_MSG_RLC_CMNCHNL_CONFIG_REQ,
   TIP_MSG_RLC_CMNCHNL_CONFIG_RSP,
   TIP_MSG_RLC_CMNCHNL_DELETE_REQ,
   TIP_MSG_RLC_CMNCHNL_DELETE_RSP,
   TIP_MSG_RLC_UECONFIG_REQ,
   TIP_MSG_RLC_UECONFIG_RSP,
   TIP_MSG_RLC_UERECONFIG_REQ,
   TIP_MSG_RLC_UERECONFIG_RSP,
   TIP_MSG_RLC_UEDELETE_REQ,
   TIP_MSG_RLC_UEDELETE_RSP,
   TIP_MSG_RRC_CCCHMSG_IND,
   TIP_MSG_RLC_CCCHMSG_REQ,
   TIP_MSG_RLC_PCCHMSG_REQ,
   TIP_MSG_PHY_CELLCONFIG_REQ,
   TIP_MSG_PHY_CELLCONFIG_RSP,
   TIP_MSG_PHY_CELLDELETE_REQ,
   TIP_MSG_PHY_CELLDELETE_RSP,
   TIP_MSG_L3_TTI_IND,
   TIP_MSG_L2_UERELEASE_IND,
   TIP_MSG_RLC_SDU_STATUS_IND,
   TIP_MSG_PDCP_MSG_IND,
   TIP_MSG_RLC_DATAMSG_REQ,
   TIP_MSG_RLC_DATADISCARD_REQ,
   TIP_MSG_END
} TipIntfMsgId;

EXTERN char *tipModName[TIP_MOD_END];
EXTERN char *tipIntfMsgName[TIP_MSG_END];

#define TIP_LOG_ENABLE

#ifdef TIP_LOG_ENABLE
#define TIP_EVENT_LOG(cellId, ueId, srcMod, dstMod, msgId, transId) \
{\
   char result[100];\
   sprintf(result, "[%d] [%d] [%s -> %s] %s (transId: %x)", cellId, ueId,\
         tipModName[srcMod],tipModName[dstMod], tipIntfMsgName[msgId],\
         transId);\
   printf("\n%s\n", result);\
   RLOG_STR(L_EVENT, "%s\n", result);\
}
#else
#define TIP_EVENT_LOG(cellId, ueId, srcMod, dstMod, msgId, transId)\
{\
   char result[100];\
   sprintf(result, "[%d] [%d] [%s -> %s] %s (transId: %x)\n", cellId, ueId,\
         tipModName[srcMod],tipModName[dstMod], tipIntfMsgName[msgId],\
         transId);\
   RLOG_STR(L_EVENT, "%s\n", result);\
}
#endif

EXTERN S16 tipUnpkAppMacMsg(Pst*   pst,Buffer* mBuf);
EXTERN S16 tipUnpkMacAppMsg(Pst*   pst,Buffer* mBuf);
EXTERN S16 tipUnpkL1AppMsg(Pst*   pst,Buffer* mBuf);
EXTERN S16 tipL3ProcessInitMsg(Buffer* mBuf);

EXTERN S16 tipUnpkAppL1Msg(Pst*   pst,Buffer* mBuf);
EXTERN S16 tipUnpkAppRlcMsg(Pst*   pst,Buffer* mBuf);
EXTERN S16 tipUnpkRlcAppMsg(Pst*   pst,Buffer* mBuf);
EXTERN S16 tipUnpkRlcPdcpMsg(Pst*   pst,Buffer* mBuf);

EXTERN S16 tipBldSendInitInd( U32 srcModId, U32 msgId);
EXTERN S16 tipSendToL3(U32 msgLen, U8* buf);
EXTERN S16 tipSendToCLL2(U32 msgLen, U8* buf);
EXTERN S16 tipSendToDLL2(U32 msgLen, U8* buf);
EXTERN S16 tipSendToCUL2(U32 msgLen, U8* buf);
EXTERN S16 tipSendToDUL2(U32 msgLen, U8* buf);
EXTERN S16 InitUL2DrvrTsk (Void);
EXTERN S16 InitUL2TipSockTsk (Void);
EXTERN S16 InitL3DrvrTsk (Void);
EXTERN S16 InitL3TipSockTsk (Void);
EXTERN S16 InitLL2TipSockTsk (Void);
EXTERN S16 tipBldSendInitReq( U32 dstModId, U8 cellIdx);
EXTERN S16 tipModuleInitDone(U8 cellIdx);
EXTERN S16 tipHdlInitReq( TipPacket *pkt);
EXTERN S16 tipCheckIsL2Ready();
EXTERN S16 tipSendCtfUeCfgReq(TipPacket *hdr,Pst *nPst);
EXTERN S16 tipSendCtfUeDelReq(TipPacket *hdr,Pst *nPst);

//#define L3_PORT  50000 
#define UL2_PORT 40000
#define LL2_PORT 30000
#define DUL2_PORT_TIP 35000
#define DLL2_PORT_TIP 37000


#define WR_UL2_OFFSET 2000
#define WR_LL2_OFFSET 3000
#define WR_L3_OFFSET  1000

/**
  * @enum VM Association State
  * Enumeration of VM Association states.
  */
typedef enum tipVmAssocState
{
   TIP_NO_ASSOCIATION,
   TIP_INIT_IND_RECEIVED,
   TIP_INIT_REQ_SENT,
   TIP_INIT_RSP_RECEIVED
} TipVmAssocState;

/**
  * @enum VM Association State
  * Enumeration of VM Association states.
  */
typedef enum tipVMOverallState
{
   TIP_INIT_PENDING,
   TIP_INIT_SYNC_SUCCESSFUL
} TipVMOverallState;

typedef struct tipVmAssocInfo
{
  U16     cellId;
  CmTptAddr           l2uIpAddr;
  CmTptAddr           l2uEgtpIpAddr;
  CmTptAddr           l2lIpAddr;
  TipVmAssocState    pdcpAssocState;  
  TipVmAssocState    rlcAssocState;   
  TipVmAssocState    macAssocState; 
  U32                       pdcpInitReqTransId;
  U32                       rlcInitReqTransId;
  U32                       macInitReqTransId;
  TipVMOverallState  vmOverallState;
} TipVmAssocInfo; 

typedef struct tipDrvrTskIpProcIdInfo
{
  U16                 cellId;
  U32                 ul2ProcId;
  U32                 ll2ProcId;
  CmTptAddr           l2uIpAddr;
  CmTptAddr           l2lIpAddr;
} TipDrvrTskIpProcIdInfo; 

#endif /* __TIP_CMN_H__ */


