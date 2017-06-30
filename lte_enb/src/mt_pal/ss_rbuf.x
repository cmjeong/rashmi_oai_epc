/********************************************************************20**
  
     Name:    Packet Buffers Free Manager 
  
     Type:     C include file
  
     Desc:     This file implements the funcitons required to isolate
               freeing of packer buffers from Main stack processing. This will be 
               usefull in a hyper threaded environment where the freeing can be
               done from low priority thread
  
     File:     ss_rbuf.x
  
     Sid:      ss_rbuf.x@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:44:15 2014
   
     Prg:      
  
*********************************************************************21*/
#ifndef __SS_RBUF_X__
#define __SS_RBUF_X__

#ifdef __cplusplus
extern "C" {
#endif
extern Void SsRngBufEnable ARGS((Void));
extern Void SsRngBufDisable ARGS((Void));
extern S16 SCreateSRngBuf ARGS((U8 id, Region region, Pool pool, U32 elmSize, U32 rngSize));
extern S16 SDestroySRngBuf ARGS((U8 id, Region region, Pool pool));
extern S16 SAttachSRngBuf ARGS((U8 id, U32 ent, U32 txRx));
extern S16 SEnqSRngBuf ARGS((U8 id, Void* elem));
extern S16 SDeqSRngBuf ARGS((U8 id, Void* elem));
extern S16 SPrintSRngStats ARGS((Void));
extern S16 pjBatchProc ARGS((Void));
extern Void* SRngGetWIndx ARGS((U8 rngId));
extern Void* SRngGetRIndx ARGS((U8 rngId));
extern Void SRngIncrRIndx ARGS((U8 rngId));
extern Void SRngIncrWIndx ARGS((U8 rngId));
extern S16  isRngEmpty ARGS((U8 rngId));
extern S16 SConnectSRngBuf ARGS((U8 id,  U32 rxEnt));
extern U32 ssRngBufStatus;

#define SS_RNG_BUF_STATUS() ssRngBufStatus
/* Ring Buffer Structure */
typedef struct
{
   U32 size;    /* Number of elements in a ring */
   U32 read;    /* Read Index incremented by Deque operation */
   U32 write;   /* Write index incremented by Enque operation */
   U32 type;    /* sizeof user specified ring element structure */
   Void* elem;  /* pointer to the allocated ring Elements */
}SsRngBuf;

/* Ring Cfg Table */
typedef struct
{
   U32 rngSize;
   U32 elemSize;
} SsRngCfg;

/* Global Ring Buffer Info structure */
typedef struct
{
   SsRngBuf* r_addr;     // Address of allocated ring
   U32 txEnt;          // Tx Entity id
   U32 rxEnt;          // Rx Entity id
   U32 n_write;        // Number of Enque operations
   U32 n_read;         // Number of Deque operations
   U32 nReadFail;      // Number of Deque failures due to ring empty
   U32 nWriteFail;     // Number of Enque failures due to ring full
   U32 rngState;       /* Ring Buffer State */
   U32 pktDrop;        // Number of pkts dropped due to  buffer full
   U32 nPktProc;       // Debug counter for pkts processed per tti
   U32 pktRate;        // Debug counter for icpu pkt rate
} SsRngBufTbl;

/* Global Structure for updating Ring buffer for Flow Control */
typedef struct
{
   U16 dlRngBuffCnt;   /* Dl Ring Buffer Count */
   U16 ulRngBuffCnt;   /* Ul Ring Buffer Count */
}SsRngBufCnt;

/* Ring Buffer Id Enum */
typedef enum
{
  SS_RNG_BUF_DEBUG_COUNTER,
  SS_RNG_BUF_ICPU_TO_DLPDCP,
  SS_RNG_BUF_DLPDCP_TO_DLRLC,
  SS_RNG_BUF_L2_RT_TO_FREE_MGR,
  SS_RNG_BUF_L2_NRT_TO_FREE_MGR,
  SS_RNG_BUF_PRC_L1D_TO_CL,
  SS_RNG_BUF_PRC_FREE_TO_CL,
  SS_RNG_BUF_ICPU_TO_DAM,
  SS_RNG_BUF_L2_NRT_DLRLC_TO_FREE_MGR,
  SS_RNG_BUF_ICPU_BATCH_START,
#ifdef SS_RBUF
  SS_RNG_BUF_ICPU_BATCH_END = SS_RNG_BUF_ICPU_BATCH_START + BC_BATCH_MGR_MAX_BKT,
#endif
#ifdef CIPH_BATCH_PROC
  SS_RNG_BUF_DLPDCP_TO_CIPH,
  SS_RNG_BUF_CIPH_TO_DLPDCP,
  SS_RNG_BUF_ULPDCP_TO_CIPH,
  SS_RNG_BUF_CIPH_TO_ULPDCP,
#endif
  SS_RNG_BUF_ULMAC_TO_ULRLC,
  SS_RNG_BUF_RX_TO_DLRLC,
  SS_RNG_BUF_RX_TO_ULPDCP,
  SS_RNG_BUF_DL_SMSG_REUSE,
  SS_RNG_BUF_DLRLC_TO_DLMAC,
  SS_RNG_BUF_MAC_HARQ,
  SS_RNG_BUF_MAX
} SsRngBufId;

/* Ring Buffer User Entity Enum */
typedef enum
{
   SS_RBUF_ENT_ICPU,
   SS_RBUF_ENT_DLPDCP,
   SS_RBUF_ENT_DLRLC,
   SS_RBUF_ENT_L2_RT,
   SS_RBUF_ENT_L2_NRT,
   SS_RBUF_ENT_FREE_MGR,
   SS_RBUF_ENT_CL,
   SS_RBUF_ENT_PRC_L1D,
   SS_RBUF_ENT_PRC_FREE,
   SS_RBUF_ENT_DAM
#ifdef CIPH_BATCH_PROC
   ,
   SS_RBUF_ENT_DLCIPH,
   SS_RBUF_ENT_ULCIPH
#endif
   ,SS_RBUF_ENT_ULPDCP,
   SS_RBUF_ENT_ULMAC,
   SS_RBUF_ENT_ICCRX_DL,
   SS_RBUF_ENT_ULRLC

}SsRngUserEnt;
/* Ring Buffer State Enum   */

typedef enum
{
   SS_RNG_DESTROYED,
   SS_RNG_CREATED,
   SS_RNG_TX_ATTACHED,
   SS_RNG_RX_ATTACHED,
   SS_RNG_READY,
   SS_RNG_EMPTY,
   SS_RNG_FULL
}SsRngBufState;

/* User defined Ring Element structures */
typedef struct
{
  Buffer* mBuf;
} SsRngBufElem;

EXTERN  SsRngBufTbl SsRngInfoTbl[SS_RNG_BUF_MAX];
EXTERN S16 SGetNumElemInRng ARGS(( U8 id));

#ifdef __cplusplus
}
#endif

#endif
