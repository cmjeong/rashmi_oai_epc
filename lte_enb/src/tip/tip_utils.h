#ifndef __TIP_UTILS_H__
#define __TIP_UTILS_H__

#include "tip.h"
#include "../cm/ckw.h"
#include "../cm/ckw.x"
#include "L3_L2L.h"
#include "../cm/tfu.h"
#include "../ltemac/rg_env.h"
#include "../ltemac/rg_sch_inf.h"
#include "../ltemac/rg_sch.h"
#include "../cm/tfu.x"
#include "../ltemac/rg_sch_inf.x"
#include "../ltemac/rg_sch.x"
#define TIP_NUM_TQENTRY              5
#define TIP_TMR_RES                  1


#define TIP_DEFAULT_SI_SEGMENTS      1
#define TIP_FILL_HDR(_pst,_cellId, _msgId, _transId, _msgLen, _hdr)\
{\
   _hdr->srcModId = _pst->srcEnt;\
   _hdr->dstModId = _pst->dstEnt;\
   _hdr->cellId   = _cellId;\
   _hdr->msgId    = _msgId;\
   _hdr->transId  = _transId;\
   _hdr->pktLen   = _msgLen;\
}

#define TIP_CREATE_MAC_PST(_pst)\
{\
   _pst->srcEnt   = 0x0d9;\
   _pst->dstEnt   = 0x0d6;\
   _pst->dstInst  = 0;\
   _pst->intfVer  = 0;\
   _pst->region   = 0;\
   _pst->pool     = 1;\
   _pst->selector = 0;\
   _pst->event    = 4;\
}

#define TIP_CREATE_CTF_PST(_pst)\
{\
   _pst->srcEnt   = 0x0d9;\
   _pst->dstEnt   = 0x0d5;\
   _pst->dstInst  = 0;\
   _pst->intfVer  = 0;\
   _pst->region   = 0;\
   _pst->pool     = 1;\
   _pst->selector = 0;\
   _pst->event    = 4;\
}
#define TIP_INIT_IND_TMR_VAL  1000

#define TIP_COPY_L1_TRANSID(_srcTransId, _dstTransId)\
{\
    U8 cnt = 0;\
    for(;cnt < CTF_CFG_TRANSID_SIZE; cnt++)\
    {\
       _dstTransId.trans[cnt] = _srcTransId.trans[cnt];\
    }\
}

typedef enum tipTmr 
{
  TIP_MAC_INIT_IND_TMR = 1,
  TIP_RLC_INIT_IND_TMR,
  TIP_PDCP_INIT_IND_TMR
}enTipTimer;

typedef enum _tipKeyTyp
{
   TIP_LCL_KEY = 0, /* to create a key to store local trans info */
   TIP_INTF_KEY     /* to create a key to store info before sending over
                       the interface */
} TipKeyType;

typedef enum _cfgType
{
   TIP_RLC_CFG = 1,
   TIP_MAC_CFG
} TipL3CfgType;

typedef struct tipL3RgDat
{
   U8                      msgCnt;
   U8                      lcgCnt;
   U8                      lchIdCnt;
   U8                      lchId[10];
   MacUeConfigReq          mapperUeCfg;
   RgrCfgReqInfo           *schdUeRecfgReq[13];
}TipL3RgDat;

typedef struct tipLL2RgDat
{
   CmHashListEnt    transHlEnt;                  /**< List Entry of Transaction*/
   U64              key;
   U32              upperLyrTrans;
   Bool             lcg1;
   Bool             lcg2;
   Bool             lcg3;
   UeIdentity       ueId;
   U8               ll2RcvLchIdCnt;
   U8               ll2LchIdCnt;
   U8               ll2LchId[10];
   U8               ll2RbId[10];
   U8               ueRecfgsendBuf[MAX_BUFF_LEN_L2_L3];
   U8               expctdNumLcCfm;
   U8               recvdNumLcCfm;
   U8               isMacUeCfgSuccess;
   U8               isMacLchCfgSuccess;
   U8               isMacUeReCfgSuccess;
   U8               isMacUeDeleteSuccess;
   U8               isMacCellCfgSuccess;
   U8               isSchUeCfgSuccess;
   U8               isSchLcCfgSuccess;
   U8               exptdRgrCfgCfm; 
   U8               recvdRgrCfgCfm;
   U8               isPhyUeCfgDone;
   U8               isPhyUeReCfgDone;
   U8               isPhyUeDeleteDone;
}TipLL2RgDat;

typedef struct tipLL2RlcDat
{
   CmHashListEnt    transHlEnt;                  /**< List Entry of Transaction*/
   U64              key;
   CkwCfgInfo       *cfg;
} TipLL2RlcDat;

typedef struct tipL3CfgDat
{
   CmHashListEnt    transHlEnt;    /**< List Entry of Transaction*/
   U64              key;
   U32              upperLyrTrans;
   Bool             isMacPres;
   Bool             isRlcPres;
   CtfCfgTransId    l1TransId;
   TipL3RgDat       rgCfgDat;
   CkwCfgInfo       *cfgInfo;      /**< Stored RLC config Information */
}TipL3CfgDat;

typedef struct tipSiInfo
{
   U8                  isFirstCfgDone;
   U8                  macBrdcstPdu[MAX_BUFF_LEN_L2_L3];
   MacBroadcastMsgReq  *macBrdcstInfo;
   U16                 nextIdxToUse;
   RgrSiCfg            siCfgInfo;
   U16                 numSiCfgRecv;
} TipSiInfo;


/* Transient information pertaining to a particular cell.
 * The information should only be stored here to handle a scenario
 * where 1 or more RSYS APIs are merged into a single OpenInterface
 * API or vice versa.*/
typedef struct cellTransInfo
{
   U16         cellId;
   CmTimer    macInitTimer;
   CmTimer    rlcInitTimer;
   CmTimer    pdcpInitTimer;
   CmTqCp     tqCp;
   CmTqType   tq[TIP_NUM_TQENTRY];
   U8         isTmrInitDone;
   TipSiInfo  siInfo;
} TipCellTransInfo;

#define BCCH_BCH_ID 1 
#define BCCH_SIB1_ID 2
#define BCCH_SIB_OTHERS_ID 3
#define CCCH_DL_ID 4 
#define CCCH_UL_ID 5 
#define PCCH_ID 6 

#define UL_DIR 1
#define DL_DIR 2

#define CFG_STATUS_OK 0
#define CFG_STATUS_NOK 1

#define RGR_REGION 0
#define CTF_REGION 0
#define CKW_REGION 0

#define SEL_LC 0

#define TIP_MAC_INIT_DONE   0x01
#define TIP_RLC_INIT_DONE   0x02
#define TIP_PDCP_INIT_DONE  0x04

#define VMTYPE_UL2 1
#define VMTYPE_LL2 2

#define TIP_INIT_DONE  (TIP_MAC_INIT_DONE | TIP_RLC_INIT_DONE)

#ifdef TIP_LOWER_L2
#define TIP_MAX_RLF_EXPIRY 20
#endif

#define TIP_MAX_CELLS 12

EXTERN TipCellTransInfo tipCellInfoList[TIP_MAX_CELLS];
EXTERN U8 tipNumActvCells;

#define TIP_GET_NEW_CELLCB(_cellInfo)\
{\
   if(TIP_MAX_CELLS == tipNumActvCells) {\
      _cellInfo=NULLP;\
   }\
   else {\
      cmMemset((U8*)&(tipCellInfoList[tipNumActvCells]), 0,\
            sizeof(TipCellTransInfo));\
      _cellInfo = &tipCellInfoList[tipNumActvCells++];\
      cmMemset((U8*)&(_cellInfo->siInfo), 0, sizeof(TipSiInfo));\
   }\
}

#define TIP_GET_CELL_INFO(_cellId, _cellInfo)\
{\
   U8 idx;\
   for(idx = 0; idx < TIP_MAX_CELLS; idx++) {\
      if(tipCellInfoList[idx].cellId == _cellId) {\
         _cellInfo = &tipCellInfoList[idx];\
      }\
   }\
}

EXTERN void deriveTipTransId(U8* transId, TipPacket *hdr);
EXTERN void deriveTransId(U8* transid, U32 tiptransid, U8 action, U8 cfgtype, U8 size);
EXTERN S16 fillTIPHdr(Pst *pst, TipPacket *header, U16 msgId, U16 cellId, U16 size);
EXTERN S16 tipFillHdr(Pst *pst, U32 cellId, U32 msgId, U32 transId, U16 len, TipPacket *hdr);
EXTERN S16 fillPstStr(Pst *pst, TipPacket *header);
//EXTERN TipCellTransInfo tipCellInfo;
EXTERN S16 tipStartCell(U16 cellId);
EXTERN S16 smBuildWrCellCntrl();
EXTERN U8 tipFetchCellIdxFromCellId (U16 cellId);
EXTERN U32 tipFetchUl2IpAddrFromProcId (U32 procId);
EXTERN U8 tipFetchCellIdxFromTransId (U32 modId, U32 transId);
EXTERN U32 tipFetchUl2ProcIdFromCellId (U16 cellId);
EXTERN U8 tipVldtIPAddressfromVmAssoc(U32 vmType, CmIpAddr ipAddr);
EXTERN Void tipCpyVmInfofrmInitReq(U32 vmType, TipPacket *pkt);


EXTERN S16 tipGetUeIndex(CmLteCellId cellId, U16 crnti, U16 *ueIndex);
EXTERN void tipPrntBuf(U8* buf, U16 len);

/*  Hash List Funtions */
EXTERN S16 TipAddTransaction (TipL3CfgDat   *cfg);
EXTERN S16 TipFindTransaction(U64 key, TipL3CfgDat  **cfg);
EXTERN S16 TipDelTransaction(TipL3CfgDat *cfg);
EXTERN Void tipL3HashLstInit(Void);
EXTERN U64  tipPrepareKey(U16 cellId, U16 crnti, U8 tipInfKey);
EXTERN U64  tipDeriveKey(TipPacket *hdr);
/* LL2 Hash List Functions */
EXTERN Void tipLL2HashListInit(Void);
EXTERN S16 TipAddLL2Trans (TipLL2RgDat *cfg);
EXTERN S16 TipFindLL2Trans(U64 key,TipLL2RgDat **cfg);
EXTERN S16 TipDelLL2Trans(TipLL2RgDat   *cfg);
EXTERN U64 tipPrepareLL2Key(TipPacket *hdr);
EXTERN void deriveLL2TransId(U8* transid, U64 tiptransid, U8 action, U8 cfgtype, U8 size);

/* Hash List Utility Functions */
EXTERN S16 TipUtlPrepKeyAndStoreRlcTrans(Pst *pst, TipL3CfgType cfgTyp,
      U16 cellId, U16 ueId, U8 keyTyp, U32 transId,
      void *storeData, U64 *key);
EXTERN S16 TipUtlPrepKeyAndStoreMacTrans(Pst *pst, TipL3CfgType cfgTyp,
      U16 cellId, U16 ueId, U8 keyTyp, U32 transId,
      TipL3RgDat **macData, U64 *key);
EXTERN TipL3CfgDat *TipUtlDelL3TransFrmLst(Pst *pst, U16 cellId,
      U16 ueId, U8 keyTyp);
EXTERN S16 TipUtlFreeL3Trans(Pst *pst, U16 cellId, U16 ueId, U8 keyTyp);
EXTERN TipL3RgDat *TipUtlGetStoredL3MacData(U16 cellId, U16 ueId, U8 keyTyp);
EXTERN CkwCfgInfo *TipUtlGetStoredL3RlcData(U16 cellId, U16 ueId, U8 keyTyp);
EXTERN S16 TipUtlStoreTrans(U16 cellId, U16 ueId, U8 keyTyp, U32 transId,
      TipL3CfgDat *cfgData, U64 *key);

#ifdef TIP_LOWER_L2
EXTERN S16 tipSendUeRlsInd(U16 ueId, U16 cellId, U32 cause);
EXTERN Void tipTrackUeInactivity(RgSchUeCb *ue);
EXTERN S16 tipResetActTmr(RgSchUeCb *ue);
EXTERN S16 tipLL2SaveUeIndex(U16 cellId, U8 inst, U16 crnti, U16 ueIndex);
EXTERN S16 tipLL2GetUeIndex(U16 cellId, U8 inst, U16 crnti, U16 *ueIndex);
#endif

EXTERN PUBLIC U32 tipFetchUl2EgtpIpAddrFromCellId (U16 cellId);
#endif
