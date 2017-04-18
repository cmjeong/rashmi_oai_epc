

/**********************************************************************
 
    Name:   LTE UE Simulator layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE UE Simulator
 
    File:   ue_mac.c
 
    Sid:      ue_mac.c@@/main/1 - Sun Mar 28 22:59:23 2010
 
    Prg:    vp
 
**********************************************************************/
 
/* This file implements MAC layer for UE simulator                  */
/* Brief functionality description:                                 */
/*    1. SR Generation when data is present without allocation.     */
/*    2. BSR procedure implementation along with MUXing BSR.        */
/*    3. Handling UL allocation by requesting RLC for PDUS.         */
/*    4. Demultiplexing DL data into RLC PDUs and delivery to RLC   */

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "cm_pasn.h"        /* common LTE */
#ifndef SS_CAVIUM
#include "pcap.h"       /* common tokens */
#endif /* SS_CAVIUM */
/* ue007.101: unused file */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "nhu_asn.h"
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "tfu.h"
#include "ue.h"
#include "ue_err.h"

/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#include "resultcodes.h" /* Phy api file */
#include "apidefs.h"     /* Phy api file */
#endif

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#include "cm_pasn.x"        /* common LTE */
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Defines */
#include "cm_esm.x"        /* ESM Defines */
#include "cm_emm_esm.x"    /* EMM-ESM Defines */
#include "ue_app.x"        /* UE application includes */
#include "tfu.x"
#include "ue.x"            /* typedefs for MAC */

/* ue002.101: Multi ue support for Uu interface */
#ifdef ENB_PERF_MEAS
EXTERN U32  ueAppNumRecfgComplSent;
PUBLIC Bool ueAppSignalingComplte;
PUBLIC U32  ueAppCntrlReqCount;
#endif
/* ue006.101: Changes for end to end performance */
CmLteTimingInfo prvTmInfo;
/* ue008.101: Fix for compilation warning */
#ifndef LTE_E2E_PERF_MEAS      
EXTERN U16 noAppSdus, noRlcSdus, noRlcPdus;
#endif
PUBLIC U16 noMacPdus, noMacPdusSent;

/* SPEC defined constants and corresponding masks */
#if 0
/* This should be enough for most scenarios */
#define MAC_SI_RNTI            65535
/* ue003.101: Paging support changes */
#define MAC_P_RNTI             65534
#define UE_SIM_MAX_SUBHDRS     50
#define MAC_LCID_MASK          0x1f
#define MAC_TIMING_ADVANCE     0x1d
#define MAC_LCID_CONT_RES      0x1c
#define MAC_LCID_PADDING       0x1f
#define MAC_LCID_LONGBSR       0x1e
#define MAC_LCID_SHORTBSR      0x1d
#define MAC_LCID_TRUNCBSR      0x1c
#define MAC_SUBHDR_EXT_MASK    0x20
#define MAC_MIN_PDU_SIZE       2
#define MAC_PAD_SUBHDR         UE_MAC_PAD_LCID | UE_MAC_SUBHDR_EXT_MASK
#define MAC_CONT_RES_SIZE      6
#define UE_MAC_BSR_SIZE        4
/* ue003.101: MAX_RARNTI is moved to ue.h file */

#define MAC_GET_ITBS(_iMcs, _iTbs) {\
   if (_iMcs < 11) _iTbs = _iMcs;\
   else if (_iMcs < 21) _iTbs = _iMcs - 1;\
   else if (_iMcs < 29) _iTbs = _iMcs - 2;\
   else _iTbs = _iMcs;\
}

#define MAC_GET_BSR(_bo, _bsr) {\
   S16 _i; \
   for (_i = 0; _i < 64; _i++) {\
      if (_bo <= ueMacBsrTbl[_i]) {\
         _bsr = _i;\
          break;\
      }\
   }\
   if (_i == 64) _bsr = 63;\
}


#define UE_MAC_GET_MEM(_memPtr, _size, _allocPtr)               \
{                                                              \
   (*_allocPtr) = NULLP;                                       \
   (Void)cmGetMem(_memPtr, _size, (Ptr *)_allocPtr);           \
}

#endif

/* ue003.101: Compute latency */
#ifdef UE_COMPUTE_LATENCY
TimeDelayInfo   tmDelayInfo;
int latencyCompDone = 0;
#endif

#if 0

typedef struct ueSimMacSubHdr
{
   U8            lcId;
   MsgLen        len;
} UeMacSubHdr;

typedef struct ueMacPdu
{
   U8            numSubHdrs;
   UeMacSubHdr   subHdrs[UE_SIM_MAX_SUBHDRS];
} UeMacPdu;

typedef struct ueMacUlSf
{
   TfuDatIndInfo   *datInd;
   TfuSrIndInfo    *srInd;
   TfuHqIndInfo    *hqInd;
/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
   TfuDlCqiIndInfo *dlCqiInd;
#endif
} UeMacUlSf;
PRIVATE UeMacUlSf ueMacUlSf[10];
#endif

/* ue002.101: Changes to support padding */
PRIVATE Data      paddingBytes[1000] = {0};

PUBLIC UeMacTbSzTbl ueMacTbSzTbl = {
   {16,    32,    56,    88,    120,   152,   176,   208,   224,   256,   288,   328,   344,   376,   392,   424,   456,   488,   504,   536,   568,   600,   616,   648,   680,   712,   744,   776,   776,   808,   840,   872,   904,   936,   968,   1000,  1032,  1032,  1064,  1096,  1128,  1160,  1192,  1224,  1256,  1256,  1288,  1320,  1352,  1384,  1416,  1416,  1480,  1480,  1544,  1544,  1608,  1608,  1608,  1672,  1672,  1736,  1736,  1800,  1800,  1800,  1864,  1864,  1928,  1928,  1992,  1992,  2024,  2088,  2088,  2088,  2152,  2152,  2216,  2216,  2280,  2280,  2280,  2344,  2344,  2408,  2408,  2472,  2472,  2536,  2536,  2536,  2600,  2600,  2664,  2664,  2728,  2728,  2728,  2792,  2792,  2856,  2856,  2856,  2984,  2984,  2984,  2984,  2984,  3112},
   {24,    56,    88,    144,   176,   208,   224,   256,   328,   344,   376,   424,   456,   488,   520,   568,   600,   632,   680,   712,   744,   776,   808,   872,   904,   936,   968,   1000,  1032,  1064,  1128,  1160,  1192,  1224,  1256,  1288,  1352,  1384,  1416,  1416,  1480,  1544,  1544,  1608,  1608,  1672,  1736,  1736,  1800,  1800,  1864,  1864,  1928,  1992,  1992,  2024,  2088,  2088,  2152,  2152,  2216,  2280,  2280,  2344,  2344,  2408,  2472,  2472,  2536,  2536,  2600,  2600,  2664,  2728,  2728,  2792,  2792,  2856,  2856,  2856,  2984,  2984,  2984,  3112,  3112,  3112,  3240,  3240,  3240,  3240,  3368,  3368,  3368,  3496,  3496,  3496,  3496,  3624,  3624,  3624,  3752,  3752,  3752,  3752,  3880,  3880,  3880,  4008,  4008,  4008},
   {32,    72,    144,   176,   208,   256,   296,   328,   376,   424,   472,   520,   568,   616,   648,   696,   744,   776,   840,   872,   936,   968,   1000,  1064,  1096,  1160,  1192,  1256,  1288,  1320,  1384,  1416,  1480,  1544,  1544,  1608,  1672,  1672,  1736,  1800,  1800,  1864,  1928,  1992,  2024,  2088,  2088,  2152,  2216,  2216,  2280,  2344,  2344,  2408,  2472,  2536,  2536,  2600,  2664,  2664,  2728,  2792,  2856,  2856,  2856,  2984,  2984,  3112,  3112,  3112,  3240,  3240,  3240,  3368,  3368,  3368,  3496,  3496,  3496,  3624,  3624,  3624,  3752,  3752,  3880,  3880,  3880,  4008,  4008,  4008,  4136,  4136,  4136,  4264,  4264,  4264,  4392,  4392,  4392,  4584,  4584,  4584,  4584,  4584,  4776,  4776,  4776,  4776,  4968,  4968},
   {40,    104,   176,   208,   256,   328,   392,   440,   504,   568,   616,   680,   744,   808,   872,   904,   968,   1032,  1096,  1160,  1224,  1256,  1320,  1384,  1416,  1480,  1544,  1608,  1672,  1736,  1800,  1864,  1928,  1992,  2024,  2088,  2152,  2216,  2280,  2344,  2408,  2472,  2536,  2536,  2600,  2664,  2728,  2792,  2856,  2856,  2984,  2984,  3112,  3112,  3240,  3240,  3368,  3368,  3496,  3496,  3624,  3624,  3624,  3752,  3752,  3880,  3880,  4008,  4008,  4136,  4136,  4264,  4264,  4392,  4392,  4392,  4584,  4584,  4584,  4776,  4776,  4776,  4776,  4968,  4968,  4968,  5160,  5160,  5160,  5352,  5352,  5352,  5352,  5544,  5544,  5544,  5736,  5736,  5736,  5736,  5992,  5992,  5992,  5992,  6200,  6200,  6200,  6200,  6456,  6456},
   {56,    120,   208,   256,   328,   408,   488,   552,   632,   696,   776,   840,   904,   1000,  1064,  1128,  1192,  1288,  1352,  1416,  1480,  1544,  1608,  1736,  1800,  1864,  1928,  1992,  2088,  2152,  2216,  2280,  2344,  2408,  2472,  2600,  2664,  2728,  2792,  2856,  2984,  2984,  3112,  3112,  3240,  3240,  3368,  3496,  3496,  3624,  3624,  3752,  3752,  3880,  4008,  4008,  4136,  4136,  4264,  4264,  4392,  4392,  4584,  4584,  4584,  4776,  4776,  4968,  4968,  4968,  5160,  5160,  5160,  5352,  5352,  5544,  5544,  5544,  5736,  5736,  5736,  5992,  5992,  5992,  5992,  6200,  6200,  6200,  6456,  6456,  6456,  6456,  6712,  6712,  6712,  6968,  6968,  6968,  6968,  7224,  7224,  7224,  7480,  7480,  7480,  7480,  7736,  7736,  7736,  7992},
   {72,    144,   224,   328,   424,   504,   600,   680,   776,   872,   968,   1032,  1128,  1224,  1320,  1384,  1480,  1544,  1672,  1736,  1864,  1928,  2024,  2088,  2216,  2280,  2344,  2472,  2536,  2664,  2728,  2792,  2856,  2984,  3112,  3112,  3240,  3368,  3496,  3496,  3624,  3752,  3752,  3880,  4008,  4008,  4136,  4264,  4392,  4392,  4584,  4584,  4776,  4776,  4776,  4968,  4968,  5160,  5160,  5352,  5352,  5544,  5544,  5736,  5736,  5736,  5992,  5992,  5992,  6200,  6200,  6200,  6456,  6456,  6712,  6712,  6712,  6968,  6968,  6968,  7224,  7224,  7224,  7480,  7480,  7480,  7736,  7736,  7736,  7992,  7992,  7992,  8248,  8248,  8248,  8504,  8504,  8760,  8760,  8760,  8760,  9144,  9144,  9144,  9144,  9528,  9528,  9528,  9528,  9528},
   {88,    176,   256,   392,   504,   600,   712,   808,   936,   1032,  1128,  1224,  1352,  1480,  1544,  1672,  1736,  1864,  1992,  2088,  2216,  2280,  2408,  2472,  2600,  2728,  2792,  2984,  2984,  3112,  3240,  3368,  3496,  3496,  3624,  3752,  3880,  4008,  4136,  4136,  4264,  4392,  4584,  4584,  4776,  4776,  4968,  4968,  5160,  5160,  5352,  5352,  5544,  5736,  5736,  5992,  5992,  5992,  6200,  6200,  6456,  6456,  6456,  6712,  6712,  6968,  6968,  6968,  7224,  7224,  7480,  7480,  7736,  7736,  7736,  7992,  7992,  8248,  8248,  8248,  8504,  8504,  8760,  8760,  8760,  9144,  9144,  9144,  9144,  9528,  9528,  9528,  9528,  9912,  9912,  9912,  10296, 10296, 10296, 10296, 10680, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448},
   {104,   224,   328,   472,   584,   712,   840,   968,   1096,  1224,  1320,  1480,  1608,  1672,  1800,  1928,  2088,  2216,  2344,  2472,  2536,  2664,  2792,  2984,  3112,  3240,  3368,  3368,  3496,  3624,  3752,  3880,  4008,  4136,  4264,  4392,  4584,  4584,  4776,  4968,  4968,  5160,  5352,  5352,  5544,  5736,  5736,  5992,  5992,  6200,  6200,  6456,  6456,  6712,  6712,  6712,  6968,  6968,  7224,  7224,  7480,  7480,  7736,  7736,  7992,  7992,  8248,  8248,  8504,  8504,  8760,  8760,  8760,  9144,  9144,  9144,  9528,  9528,  9528,  9912,  9912,  9912,  10296, 10296, 10296, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448, 11448, 11832, 11832, 11832, 12216, 12216, 12216, 12576, 12576, 12576, 12960, 12960, 12960, 12960, 13536, 13536},
   {120,   256,   392,   536,   680,   808,   968,   1096,  1256,  1384,  1544,  1672,  1800,  1928,  2088,  2216,  2344,  2536,  2664,  2792,  2984,  3112,  3240,  3368,  3496,  3624,  3752,  3880,  4008,  4264,  4392,  4584,  4584,  4776,  4968,  4968,  5160,  5352,  5544,  5544,  5736,  5992,  5992,  6200,  6200,  6456,  6456,  6712,  6968,  6968,  7224,  7224,  7480,  7480,  7736,  7736,  7992,  7992,  8248,  8504,  8504,  8760,  8760,  9144,  9144,  9144,  9528,  9528,  9528,  9912,  9912,  9912,  10296, 10296, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448, 11832, 11832, 12216, 12216, 12216, 12576, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 13536, 13536, 14112, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15264},
   {136,   296,   456,   616,   776,   936,   1096,  1256,  1416,  1544,  1736,  1864,  2024,  2216,  2344,  2536,  2664,  2856,  2984,  3112,  3368,  3496,  3624,  3752,  4008,  4136,  4264,  4392,  4584,  4776,  4968,  5160,  5160,  5352,  5544,  5736,  5736,  5992,  6200,  6200,  6456,  6712,  6712,  6968,  6968,  7224,  7480,  7480,  7736,  7992,  7992,  8248,  8248,  8504,  8760,  8760,  9144,  9144,  9144,  9528,  9528,  9912,  9912,  10296, 10296, 10296, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11832, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 13536, 13536, 14112, 14112, 14112, 14112, 14688, 14688, 14688, 15264, 15264, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16416, 16992, 16992, 16992, 16992, 17568},
   {144,   328,   504,   680,   872,   1032,  1224,  1384,  1544,  1736,  1928,  2088,  2280,  2472,  2664,  2792,  2984,  3112,  3368,  3496,  3752,  3880,  4008,  4264,  4392,  4584,  4776,  4968,  5160,  5352,  5544,  5736,  5736,  5992,  6200,  6200,  6456,  6712,  6712,  6968,  7224,  7480,  7480,  7736,  7992,  7992,  8248,  8504,  8504,  8760,  9144,  9144,  9144,  9528,  9528,  9912,  9912,  10296, 10296, 10680, 10680, 11064, 11064, 11448, 11448, 11448, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 18336, 18336, 19080, 19080, 19080, 19080},
   {176,   376,   584,   776,   1000,  1192,  1384,  1608,  1800,  2024,  2216,  2408,  2600,  2792,  2984,  3240,  3496,  3624,  3880,  4008,  4264,  4392,  4584,  4776,  4968,  5352,  5544,  5736,  5992,  5992,  6200,  6456,  6712,  6968,  6968,  7224,  7480,  7736,  7736,  7992,  8248,  8504,  8760,  8760,  9144,  9144,  9528,  9528,  9912,  9912,  10296, 10680, 10680, 11064, 11064, 11448, 11448, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 13536, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 14688, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 18336, 19080, 19080, 19080, 19080, 19848, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 21384, 22152, 22152, 22152},
   {208,   440,   680,   904,   1128,  1352,  1608,  1800,  2024,  2280,  2472,  2728,  2984,  3240,  3368,  3624,  3880,  4136,  4392,  4584,  4776,  4968,  5352,  5544,  5736,  5992,  6200,  6456,  6712,  6712,  6968,  7224,  7480,  7736,  7992,  8248,  8504,  8760,  8760,  9144,  9528,  9528,  9912,  9912,  10296, 10680, 10680, 11064, 11064, 11448, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 22920, 23688, 23688, 23688, 23688, 24496, 24496, 24496, 24496, 25456},
   {224,   488,   744,   1000,  1256,  1544,  1800,  2024,  2280,  2536,  2856,  3112,  3368,  3624,  3880,  4136,  4392,  4584,  4968,  5160,  5352,  5736,  5992,  6200,  6456,  6712,  6968,  7224,  7480,  7736,  7992,  8248,  8504,  8760,  9144,  9144,  9528,  9912,  9912,  10296, 10680, 10680, 11064, 11448, 11448, 11832, 12216, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 22920, 23688, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 25456, 26416, 26416, 26416, 26416, 27376, 27376, 27376, 27376, 28336, 28336},
   {256,   552,   840,   1128,  1416,  1736,  1992,  2280,  2600,  2856,  3112,  3496,  3752,  4008,  4264,  4584,  4968,  5160,  5544,  5736,  5992,  6200,  6456,  6968,  7224,  7480,  7736,  7992,  8248,  8504,  8760,  9144,  9528,  9912,  9912,  10296, 10680, 11064, 11064, 11448, 11832, 12216, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 28336, 28336, 29296, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704},
   {280,   600,   904,   1224,  1544,  1800,  2152,  2472,  2728,  3112,  3368,  3624,  4008,  4264,  4584,  4968,  5160,  5544,  5736,  6200,  6456,  6712,  6968,  7224,  7736,  7992,  8248,  8504,  8760,  9144,  9528,  9912,  10296, 10296, 10680, 11064, 11448, 11832, 11832, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 23688, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008},
   {328,   632,   968,   1288,  1608,  1928,  2280,  2600,  2984,  3240,  3624,  3880,  4264,  4584,  4968,  5160,  5544,  5992,  6200,  6456,  6712,  7224,  7480,  7736,  7992,  8504,  8760,  9144,  9528,  9912,  9912,  10296, 10680, 11064, 11448, 11832, 12216, 12216, 12576, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 34008, 35160, 35160, 35160, 35160},
   {336,   696,   1064,  1416,  1800,  2152,  2536,  2856,  3240,  3624,  4008,  4392,  4776,  5160,  5352,  5736,  6200,  6456,  6712,  7224,  7480,  7992,  8248,  8760,  9144,  9528,  9912,  10296, 10296, 10680, 11064, 11448, 11832, 12216, 12576, 12960, 13536, 13536, 14112, 14688, 14688, 15264, 15264, 15840, 16416, 16416, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 35160, 36696, 36696, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 39232, 39232},
   {376,   776,   1160,  1544,  1992,  2344,  2792,  3112,  3624,  4008,  4392,  4776,  5160,  5544,  5992,  6200,  6712,  7224,  7480,  7992,  8248,  8760,  9144,  9528,  9912,  10296, 10680, 11064, 11448, 11832, 12216, 12576, 12960, 13536, 14112, 14112, 14688, 15264, 15264, 15840, 16416, 16416, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 40576, 42368, 42368, 42368, 42368, 43816, 43816},
   {408,   840,   1288,  1736,  2152,  2600,  2984,  3496,  3880,  4264,  4776,  5160,  5544,  5992,  6456,  6968,  7224,  7736,  8248,  8504,  9144,  9528,  9912,  10296, 10680, 11064, 11448, 12216, 12576, 12960, 13536, 13536, 14112, 14688, 15264, 15264, 15840, 16416, 16992, 16992, 17568, 18336, 18336, 19080, 19080, 19848, 20616, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888},
   {440,   904,   1384,  1864,  2344,  2792,  3240,  3752,  4136,  4584,  5160,  5544,  5992,  6456,  6968,  7480,  7992,  8248,  8760,  9144,  9912,  10296, 10680, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 14688, 15264, 15840, 16416, 16992, 16992, 17568, 18336, 18336, 19080, 19848, 19848, 20616, 20616, 21384, 22152, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 48936, 51024, 51024, 51024},
   {488,   1000,  1480,  1992,  2472,  2984,  3496,  4008,  4584,  4968,  5544,  5992,  6456,  6968,  7480,  7992,  8504,  9144,  9528,  9912,  10680, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 15840, 16416, 16992, 17568, 18336, 18336, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 52752, 55056, 55056, 55056},
   {520,   1064,  1608,  2152,  2664,  3240,  3752,  4264,  4776,  5352,  5992,  6456,  6968,  7480,  7992,  8504,  9144,  9528,  10296, 10680, 11448, 11832, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 16992, 17568, 18336, 19080, 19080, 19848, 20616, 21384, 21384, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256},
   {552,   1128,  1736,  2280,  2856,  3496,  4008,  4584,  5160,  5736,  6200,  6968,  7480,  7992,  8504,  9144,  9912,  10296, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 19848, 20616, 21384, 22152, 22152, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776},
   {584,   1192,  1800,  2408,  2984,  3624,  4264,  4968,  5544,  5992,  6712,  7224,  7992,  8504,  9144,  9912,  10296, 11064, 11448, 12216, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 19848, 20616, 21384, 22152, 22920, 22920, 23688, 24496, 25456, 25456, 26416, 26416, 27376, 28336, 28336, 29296, 29296, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 63776, 66592, 66592, 66592, 66592},
   {616,   1256,  1864,  2536,  3112,  3752,  4392,  5160,  5736,  6200,  6968,  7480,  8248,  8760,  9528,  10296, 10680, 11448, 12216, 12576, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 20616, 20616, 21384, 22152, 22920, 23688, 24496, 24496, 25456, 26416, 26416, 27376, 28336, 28336, 29296, 29296, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 63776, 66592, 66592, 66592, 66592, 68808, 68808, 68808, 71112},
   {712,   1480,  2216,  2984,  3752,  4392,  5160,  5992,  6712,  7480,  8248,  8760,  9528,  10296, 11064, 11832, 12576, 13536, 14112, 14688, 15264, 16416, 16992, 17568, 18336, 19080, 19848, 20616, 21384, 22152, 22920, 23688, 24496, 25456, 25456, 26416, 27376, 28336, 29296, 29296, 30576, 30576, 31704, 32856, 32856, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 63776, 63776, 63776, 66592, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 71112, 73712, 73712, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376}
};

PUBLIC UeMacIMcsTbl ueMacIMcsTbl =
{0,1,2,3,4,5,6,7,8,9,10,10,11,12,13,14,15,16,17,18,19,19,20,21,22,23,24,25,26};

PUBLIC UeMacBsrTbl ueMacBsrTbl =
{0,10,12,14,17,19,22,26,31,36,42,49,57,67,78,91,107,125,146,171,200,234,274,321,376,440,515,603,706,826,967,1132,1326,1552,1817,2127,2490,2915,3413,3995,4677,5476,6411,7505,8787,10287,12043,14099,16507,19325,22624,31009,36304,42502,49759,58255,68201,79846,93479,109439,128125,150000};

/* ue003.101: Timing advanche changes */
#ifdef TA_NEW
PRIVATE Void ueMacStartTmr ARGS((
CellCb           *cell,
UeCb             *ueCb,
S16              evnt,
U32              wait
));
PRIVATE Void ueMacStopTmr ARGS((
CellCb           *cell,
UeCb             *ueCb,
S16              evnt
));
PRIVATE Void ueMacProcessTA ARGS((
CellCb           *cell,
UeCb             *ueCb
));
#endif
/* 
 *
 *       Fun:    ueMacGetSubHdrs
 * 
 *       Desc:   This function reads the subheaders of the received PDU.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  1. Read a byte and determine the lcId and extension.
 *               2. Read the length if it is not UE Contention Resolution Subhdr
 *               3. Go to step 1 if extension is set
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacGetSubHdrs
(
Buffer      *mBuf,
UeMacPdu    *pdu
)
#else
PRIVATE S16 ueMacGetSubHdrs(mBuf,pdu)
Buffer      *mBuf;
UeMacPdu    *pdu;
#endif
{
   U8       extension;
   U8       len;
   U8       byte;

   TRC2(ueMacGetSubHdrs)

   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueMacGetSubHdrs: Processing to get MAC subheaders"));
   /* Read subheaders till you see no extension mark */
   do
   {
      UeMacSubHdr    *subHdr;

      subHdr = &pdu->subHdrs[pdu->numSubHdrs];
      SUnpkU8(&byte, mBuf);
      extension = byte & UE_MAC_SUBHDR_EXT_MASK;
      subHdr->lcId = byte & UE_MAC_LCID_MASK;

      /* Remove any padding subheaders at the beginning of the PDU */
      if ((subHdr->lcId == UE_MAC_PAD_LCID) && (pdu->numSubHdrs == 0))
      {
         continue;
      }

      /* Process the subheader */
      if ((subHdr->lcId != UE_MAC_CONT_RES_LCID) &&
         (subHdr->lcId != UE_MAC_TA_LCID))
      {
         if (extension)
         {
            /* This is a PDU so Get its length */
            SUnpkU8(&len, mBuf);
            if (len & 0x80)
            {
               subHdr->len = len & 0x7f;
               SUnpkU8(&len, mBuf);
               subHdr->len = (subHdr->len << 8) + len;
            }
            else
            {
               subHdr->len = len;
            }
         }
      }
      else
      {
         subHdr->len = 6;
      }
      pdu->numSubHdrs++;
   } while(extension);

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueMacDatInd
 * 
 *       Desc:   Thhis functions handles a DATA PDU from eNodeB.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Get the subheaders.
 *               2. For each subhdr that is not contention resolution,
 *                  create a RLC PDU
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacDatInd
(
CellCb    *cell,
UeCb      *ueCb,
Buffer    *mBuf
)
#else
PRIVATE S16 ueMacDatInd(cell,ueCb,mBuf)
CellCb    *cell;
UeCb      *ueCb;
Buffer    *mBuf;
#endif
{
   UeMacPdu           pdu;
   Buffer             *remBuf;
   S16                i;

   TRC2(ueMacDatInd)
   /* First parse the MAC sub headers                    */
   /* We can have UE contention resolution ID along with */
   /* data SDUs                                          */
   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueMacDatInd: Processing to data received in DatInd"));

  /* ue002.101: kworks_fix */
   if(NULLP == mBuf)
   {
      RETVALUE(ROK);
   }

   pdu.numSubHdrs = 0;
   if (ueMacGetSubHdrs(mBuf, &pdu) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* create each MAC SDU and deliver to RLC */
   /* ue002.101: kworks_fix */
   for (i = 0; (i < pdu.numSubHdrs - 1) && (i < UE_SIM_MAX_SUBHDRS); i++) 
   {
      UeMacSubHdr       *subHdr;

      subHdr = &pdu.subHdrs[i];
      if (subHdr->lcId == UE_MAC_CONT_RES_LCID)
      {
         SSegMsg(mBuf,UE_MAC_CON_RES_ID_SZ , &remBuf);
         SPutMsg(mBuf);
/* ue003.101: Timing advance changes */
         mBuf = remBuf;
#ifdef TA_NEW
    ueMacProcessTA(cell,ueCb);
#endif
      }
      else if (subHdr->lcId == UE_MAC_TA_LCID)
      {
/* ue003.101: Timing advance changes */
#ifdef TA_NEW
         SSegMsg(mBuf, 1, &remBuf);
         SRemPreMsg((Data *)&ueCb->mac.ta, mBuf);
         /* start TA Apply Timer */
         ueMacStartTmr(cell,ueCb, UE_MAC_EVNT_TA_APPLY_TMR, UE_MAC_TA_APPLY_TMR);
         mBuf = remBuf;
#else
         SSegMsg(mBuf, 1, &remBuf);
         SPutMsg(mBuf);
         mBuf = remBuf;
#endif
      }
      else
      {
         /* Give mBuf to RLC */
         SSegMsg(mBuf, subHdr->len, &remBuf);
         ueRlcDatInd(ueCb, pdu.subHdrs[i].lcId, mBuf);
/* ue003.101: Timing advance changes */
         mBuf = remBuf;
      }
   }
   /* Give the remaining one to RLC is the LCID is not padding */
   if (pdu.subHdrs[i].lcId != UE_MAC_PAD_LCID)
   {
      ueRlcDatInd(ueCb, pdu.subHdrs[i].lcId, mBuf);
   }
   else
   {
      /* ue002.101: kworks_fix */
      if (mBuf)
      {
         SPutMsg(mBuf);
      }
   }

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueMacAddBsr
 * 
 *       Desc:   Thhis functions builds either a SHORT or LONG BSR
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Currently build only long BSR. Later, if only one group has
 *               data, build a SHORT BSR.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacAddBsr
(
UeCb            *ueCb,
Buffer          *mBuf,
U8              *lcId,
MsgLen          *len
)
#else
PRIVATE Void ueMacAddBsr(ueCb,mBuf,lcId,len)
UeCb            *ueCb;
Buffer          *mBuf;
U8              *lcId;
MsgLen          *len;
#endif
{
   /* ue008.101 : TIC_ID : ccpu00117550: Fixed warning for gcc compilation on CentOS*/
   U8           bsr = 0;
   U32          lcg0, lcg1, lcg2, lcg3;
   U8           byte;

   TRC2(ueMacAddBsr)

   ueRlcGetBo(ueCb, &lcg0, &lcg1, &lcg2, &lcg3);

   /* Temporary change. We need to properly configure E Node B */
   lcg0 = lcg0 + lcg1;
   lcg1 = 0;

   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueMacAddBsr: BO reported by RLC %ld",lcg0));
   /* For now we are ignoring lcg2 and lcg 3 and also encode only long BSR */
   /* Prepare byte 3 that include portion of lcg2 and lcg3 */
   byte = 0;
   SAddPreMsg(byte, mBuf);

   /* Prepare byte 2 that has 4 LSB bits of lcg1 and 4 MSB bits of lcg2 */
   MAC_GET_BSR(lcg1, bsr);
   byte = (bsr & 0x0f) << 4;
   SAddPreMsg(byte, mBuf);

   /* Prepare byte 1 that has 6 bits of lcg0 and 2 MSB bits of lcg1 */
   MAC_GET_BSR(lcg0, bsr);
   byte = bsr << 2;
   MAC_GET_BSR(lcg1, bsr);
   byte = byte | ((bsr & 0x30) >> 4);
   SAddPreMsg(byte, mBuf);
   *len = 3;
   *lcId = UE_MAC_LONG_BSR_LCID;
}

/* 
 *
 *       Fun:    ueMacUlAlloc
 * 
 *       Desc:   This functions handles the allocation/grants received from eNodeB.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. If a BSR is to be included, add BSR
 *               2.  While there is data at RLC and tbSz is available, 
 *                  get data from RLC
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacUlAlloc
(
UeCb             *ueCb,
U32              tbSz,
Buffer           **pdu
)
#else
PRIVATE S16 ueMacUlAlloc(ueCb,tbSz,pdu)
UeCb             *ueCb;
U32              tbSz;
Buffer           **pdu;
#endif
{
   Buffer        *subHdrs;
   Buffer        *dataPdu;
   MsgLen        len = 0;
   U8            pad;
   U8            byte;
   U8            lcId;
   U8            lenSize;
   U8            hdrSize;
   MsgLen        pduLen = 0;
   Buffer        *rlcPdu;
   MsgLen        effTbSz = tbSz;
   /* ue006.101: Changes for end to end performance */
   U8            addSpclPad = 0;
   /* ue007.101: Fix for uu performance */
   Bool          reportBsr; 
   /* ue008.101: Added new local variable. */
   UeAppCb *ueAppCb = NULLP;

   TRC2(ueMacUlAlloc)
   /* Get the buffers for subheaders and CES, MAC SDUs */
   UE_ALLOC_BUF(subHdrs);
   /* ue002.101: kworks_fix */
   if(subHdrs == NULLP)
   {
      RETVALUE(RFAILED);
   }

   UE_ALLOC_BUF(dataPdu);
   /* ue002.101: kworks_fix */
   if(dataPdu == NULLP)
   {
      UE_FREE_BUF(subHdrs);
      RETVALUE(RFAILED);
   }
   /* ue006.101: Changes for end to end performance */
   noMacPdus++;
   /* ue007.101: Fix for uu performance */
   if ((reportBsr = ueCb->mac.reportBsr) == TRUE)
   {
      effTbSz -= UE_MAC_BSR_SIZE;
   }

   while(effTbSz > pduLen + UE_MAC_MIN_PDU_SIZE)
   {
      /* Get PDU from RLC */
      rlcPdu = NULLP;
      /* ue006.101: Changes for end to end performance */
      ueRlcGetPdu(ueCb, effTbSz - pduLen - 1, &rlcPdu, &lcId);
      len = 0;
      if (rlcPdu != NULLP)
      {
         SFndLenMsg(rlcPdu, &len);
         if (len == 0)
         {
            SPutMsg(rlcPdu);
         }
      }
      if (len == 0)
      {
         break;
      }
      
      /* ue006.101: Changes for end to end performance */
      SFndLenMsg(rlcPdu, &len);
      pduLen += len;
      byte = lcId;
      lenSize = len > 127 ? 2 : 1;
      hdrSize = lenSize + 1; /* 1 byte for indicating LCID */
      if ((pduLen + hdrSize) < effTbSz)
      {
         /* Set extension bit for filling rest of PDU */
         byte |= UE_MAC_SUBHDR_EXT_MASK;
         SAddPstMsg(byte, subHdrs);
         pduLen++;
         /* Pack length field into the subhdrs buffer */
         if (len <= 127)
         {
            SAddPstMsg((U8)len, subHdrs);
            pduLen++;
         }
         else
         {
            SAddPstMsg((U8)(((len & 0x7f00) >> 8) | 0x80), subHdrs);
            pduLen++;
            SAddPstMsg((U8)(len & 0x00ff), subHdrs);
            pduLen++;
         }
      }
      else
      {
         SAddPstMsg(byte, subHdrs);
        /* ue006.101: Changes for end to end performance */
         addSpclPad = 1;
         pduLen++;
      }
      SCatMsg(dataPdu, rlcPdu, M1M2);
      SPutMsg(rlcPdu);
   }

   /* If there is space to place BSR, include BSR. If ultimately we */
   /* are unable to include BSR, we will use SR for grant           */
   /* ue006.101: Changes for end to end performance */
   /* ue007.101: Fix for uu performance */
   /* ue008.101 : Fixed warning for g++ compilation on Linux */
   UE_GET_APPCB(ueCb->cellId,ueAppCb,ueCb->rnti);
   if ((((pduLen + UE_MAC_BSR_SIZE + 2) < (U16)tbSz) ||
          (reportBsr == TRUE)) && (ueAppCb->hoState == 0))
   {
      /* Unset the report */
      ueCb->mac.reportBsr = FALSE;

      /* Now actually build the BSR */
      ueMacAddBsr(ueCb, dataPdu, &byte, &len);
      pduLen += len;
      /* Add the subheader for BSR */
      /* If there exists any subheaders already, need to add extension */
      /* bit. Or else, if there are more than 2 bytes of data left, we */
      /* need to add extension bit for padding PDU                     */
      SFndLenMsg(subHdrs, &len);
      /* ue008.101 : Fixed warning for g++ compilation on Linux */
      if (((pduLen + 3) < (U16) tbSz) || (len != 0))
      {
         /* Set extension bit for filling rest of PDU */
         byte |= UE_MAC_SUBHDR_EXT_MASK;
      }
      if(len != 0) /* ue009.101 : ccpu00121211 Subheader to be included only if len !=0  */
      {
         SAddPreMsg(byte, subHdrs);
         pduLen++;
      }
   }

   /* ue006.101: Changes for end to end performance */
   if (addSpclPad)
   {
      pad = UE_MAC_PAD_SUBHDR;
      /* Add padding subheaders at the beginning of sub headers*/
      while (tbSz - pduLen)
      {
         SAddPreMsg(pad, subHdrs);
         pduLen++;
      }
   }
   /* ue002.101: kworks_fix */
   else
   {
      /* Add a padding subheader and fill up rest of the PDU */
      byte = UE_MAC_PAD_LCID;
      SAddPstMsg(byte, subHdrs);
      pduLen++;

      /*ue008.101 : Fixed warning for g++ compilation on Linux */
      if((U16)tbSz > pduLen) /* ue009.101 : ccpu00121211 NO PADDING REQUIRED WHEN FALSE */
      {
         SAddPstMsgMult((U8 *)paddingBytes, tbSz - pduLen, dataPdu);
      }
   }

   SCatMsg(subHdrs, dataPdu, M1M2);
   SPutMsg(dataPdu);
   *pdu = subHdrs;

   RETVALUE(ROK);
}

/* ue003.101: Timing advance changes */
#ifdef TA_NEW
/***********************************************************
 *
 *     Func : ueMacSndTaInd
 *
 *     Desc : Form and send timingAdv indication to EnodeB.
 *
 *     Ret  : 
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void ueMacSndTaInd
(
CellCb *cell,
UeCb *ueCb
)
#else
PRIVATE Void ueMacSndTaInd(cell,ueCb)
CellCb *cell;
UeCb *ueCb;
#endif
{
   Pst                 pst;
   Mem                 mem;
   TfuTimingAdvIndInfo *taIndInfo;
   TfuTimingAdvInfo    *taInfo;
   U8                   taVal;

   TRC2(ueMacSndTaInd)

   if (ueCb->mac.remTa == 0)
   {
      RETVOID;
   }
   else if (ueCb->mac.remTa > 0)
   {
      if ((31 - ueCb->mac.remTa) < 0)
      {
         taVal = 0;
      }
      else
      {
         taVal = 31 - ueCb->mac.remTa;
      }
   }
   else
   {
      if ((31 - ueCb->mac.remTa) > 63)
      {
         taVal = 63;
      }
      else
      {
         taVal = 31 - ueCb->mac.remTa;
      }
   }
   mem.region = 0; mem.pool = 0;
   /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
   if (cmAllocEvnt(sizeof(TfuTimingAdvIndInfo), TFU_BLKSZ,
                         &mem, (Ptr *)&taIndInfo) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
         "ueMacSndTaInd:  Allocation failed for taIndInfo\n"); 
      RETVOID;
   }
   taIndInfo->cellId     = ueCb->cellId;
   /* ue008.101: Changed cellArr index to 0 from ueCb->cellId - 1  */
   taIndInfo->timingInfo = cellCb->crntTime;
   taIndInfo->timingInfo.subframe = (taIndInfo->timingInfo.subframe+1)%10;
   UE_GET_MEM(taIndInfo, sizeof(TfuTimingAdvInfo), (Ptr*)&taInfo); 
   taInfo->rnti = ueCb->rnti;
   taInfo->timingAdv = taVal;
   taInfo->lnk.node = (PTR)taInfo;
   cmLListAdd2Tail (&(taIndInfo->timingAdvLst), &(taInfo->lnk));
   TfUiTfuTimingAdvInd(&pst, 0, taIndInfo);
   RETVOID;
}

/***********************************************************
 *
 *     Func : ueMacTaTmrExpiry
 *
 *     Desc : Timer expiry handler for TA related timers.
 *
 *     Ret  : 
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE S16 ueMacTaTmrExpiry
(
PTR cb,               /* Pointer to timer control block */
S16 tmrEvnt           /* Timer Event */
)
#else
PRIVATE S16 ueMacTaTmrExpiry(cb, tmrEvnt)
PTR cb;               /* Pointer to timer control block */
S16 tmrEvnt;          /* Timer Event */
#endif
{
   CellCb  *cell;
   UeCb *ueCb = (UeCb *)cb;
   PRIVATE U8 sign;
   TRC2(ueMacTaTmrExpiry)

   ueUtlFndCell(ueCb->cellId,&cell);
   if (cell == NULLP)
   {
      printf(" cell Id not found \n");
      RETVALUE(ROK);
   }
   
   switch(tmrEvnt)
   {
      case UE_MAC_EVNT_TA_MAX_TMR:
         ueCb->mac.ulSyncStatus = FALSE;
         break;
      case UE_MAC_EVNT_TA_CHNG_TMR:
         if (ueCb->mac.ulSyncStatus)
         {
            sign++;
            ueMacStartTmr(cell,ueCb, UE_MAC_EVNT_TA_CHNG_TMR, UE_MAC_TA_CHNG_TMR);
            if (ueCb->mac.remTa > 100)
            {
               if (sign % 2)
                  ueCb->mac.remTa = 100;
               else
                  ueCb->mac.remTa = -100;
            }
            else if (ueCb->mac.remTa == 0)
            {
               if (sign > 25)
               {
                  if (sign % 2)
                     ueCb->mac.remTa = 100;
                  else
                     ueCb->mac.remTa = -100;
               }
            }
            else
            {
               ueCb->mac.remTa += 10;
            }
            /* Send TA ind to enodeB every time remTa is updated. */
            ueMacSndTaInd(cellCb,ueCb);
         }
         break;
      case UE_MAC_EVNT_TA_APPLY_TMR:
         ueCb->mac.remTa += (ueCb->mac.ta - 31);
         ueMacStopTmr(cell,ueCb, UE_MAC_EVNT_TA_MAX_TMR);
         ueMacStartTmr(cell,ueCb, UE_MAC_EVNT_TA_MAX_TMR, UE_MAC_TA_MAX_TMR);
         /* Send TA ind to enodeB every time remTa is updated. */
         ueMacSndTaInd(cell,ueCb);
         break;
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func : ueMacTaTmrProc 
 *
 *     Desc : Timer entry point per cell. Timer
 *            processing is triggered at every subframe boundary.
 *
 *     Ret  : 
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void ueMacTaTmrProc
(
CellCb  *cell
)
#else
PRIVATE Void ueMacTaTmrProc()
CellCb  *cell;
#endif
{
   TRC2(ueMacTaTmrProc);

   cmPrcTmr(&cellCb->tmrTqCp, cellCb->tmrTq, (PFV)ueMacTaTmrExpiry);
 
   RETVOID;
}

/* 
 *
 *       Fun:    ueMacStartTmr
 * 
 *       Desc:   This functions starts TA related timers.
 * 
 *       Ret:    Void 
 *
 *       Notes:  
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacStartTmr
(
CellCb           *cellCb,
UeCb             *ueCb,
S16              evnt,
U32              wait
)
#else
PRIVATE Void ueMacStartTmr(cellCb,ueCb, evnt, wait)
CellCb           *cellCb;
UeCb             *ueCb;
S16              evnt;
U32              wait;
#endif
{
   /* ue008.101: Changed cellArr index to 0 from ueCb->cellId - 1  */
   CmTmrArg       arg;

   TRC2(ueMacStartTmr)

   cmMemset((U8 *)&arg, 0, sizeof(arg));
   arg.tqCp   = &cellCb->tmrTqCp;
   arg.tq     = cellCb->tmrTq;
   switch(evnt)
   {
      case UE_MAC_EVNT_TA_MAX_TMR:
         arg.timers = &ueCb->mac.taAlgntmr;
         break;
      case UE_MAC_EVNT_TA_CHNG_TMR:
         arg.timers = &ueCb->mac.taChngtmr;
         break;
      case UE_MAC_EVNT_TA_APPLY_TMR:
         arg.timers = &ueCb->mac.taAppltmr;
         break;
   }
   arg.cb     = (PTR)ueCb;
   arg.tNum   = 0;
   arg.max    = 1;
   arg.evnt   = evnt;
   arg.wait   = wait;

   cmPlcCbTq(&arg);
   RETVOID;
}

/* 
 *
 *       Fun:    ueMacStopTmr
 * 
 *       Desc:   This functions stops TA related timers.
 * 
 *       Ret:    Void 
 *
 *       Notes:  
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacStopTmr
(
CellCb           *cellCb,
UeCb             *ueCb,
S16              evnt
)
#else
PRIVATE Void ueMacStopTmr(cellCb,ueCb, evnt)
CellCb           *cellCb;
UeCb             *ueCb;
S16               evnt;
#endif
{
   /* ue008.101: Changed cellArr index to 0 from ueCb->cellId - 1  */
   CmTmrArg       arg;

   TRC2(ueMacStopTmr)

   cmMemset((U8 *)&arg, 0, sizeof(arg));
   arg.tqCp   = &cellCb->tmrTqCp;
   arg.tq     = cellCb->tmrTq;
   switch(evnt)
   {
      case UE_MAC_EVNT_TA_MAX_TMR:
         arg.timers = &ueCb->mac.taAlgntmr;
         break;
      case UE_MAC_EVNT_TA_CHNG_TMR:
         arg.timers = &ueCb->mac.taChngtmr;
         break;
      case UE_MAC_EVNT_TA_APPLY_TMR:
         arg.timers = &ueCb->mac.taAppltmr;
         break;
   }
   arg.cb     = (PTR)ueCb;
   arg.tNum   = 0;
   arg.max    = 1;
   arg.evnt   = evnt;

   cmRmvCbTq(&arg);
   RETVOID;
}

/* 
 *
 *       Fun:    ueMacProcessTA
 * 
 *       Desc:   This functions starts TA variable initialization.
 * 
 *       Ret:    Void 
 *
 *       Notes:  
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacProcessTA
(
CellCb           *cell,
UeCb             *ueCb
)
#else
PRIVATE Void ueMacProcessTA(ueCb)
CellCb           *cell,
UeCb             *ueCb;
#endif
{
   
   TRC2(ueMacProcessTA)

   ueCb->mac.ulSyncStatus = TRUE; 
   ueMacStartTmr(cell,ueCb, UE_MAC_EVNT_TA_MAX_TMR, UE_MAC_TA_MAX_TMR);
   ueCb->mac.remTa = 100; 
   ueMacStartTmr(ueCb, UE_MAC_EVNT_TA_CHNG_TMR, UE_MAC_TA_CHNG_TMR);
   RETVOID;
}
#endif

/* 
 *
 *       Fun:    ueMacCreateMsg3
 * 
 *       Desc:   This functions creates RRC Connection Request Message.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. If a BSR is to be included, add BSR
 *               2.  While there is data at RLC and tbSz is available, 
 *                  get data from RLC
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacCreateMsg3
(
UeCb             *ueCb,
U32              tbSz,
Buffer           **pdu
)
#else
PRIVATE S16 ueMacCreateMsg3(ueCb,tbSz,pdu)
UeCb             *ueCb;
U32              tbSz;
Buffer           **pdu;
#endif
{
   Buffer        *subHdrs;
   Buffer        *dataPdu;
   MsgLen        len = 0;
   MsgLen        pduLen = 0;
   U8            pad;
   U8            byte;

   TRC2(ueMacCreateMsg3)
   /* Get the buffers for subheaders and CES, MAC SDUs */
   UE_ALLOC_BUF(subHdrs);
   /* ue002.101: kworks_fix */
   if(subHdrs == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Get PDU from RLC */
   dataPdu = ueCb->mac.msg3;
   ueCb->mac.msg3 = NULLP;
   SFndLenMsg(dataPdu, &len);
   byte = 0; /* Set LCID to zero */
   pduLen = len;
   /*ue008.101 : MOD: Fixed warning for g++ compilation on Linux */
   if ((pduLen + 2) < (U16)tbSz)
   /*ue008.101 : MOD_END: Fixed warning for g++ compilation on Linux */
   {
      /* Set extension bit for filling rest of PDU */
      byte |= UE_MAC_SUBHDR_EXT_MASK;
      SAddPstMsg(byte, subHdrs);
      pduLen++;
      /* Pack length field into the subhdrs buffer */
      if (len <= 127)
      {
         SAddPstMsg((U8)len, subHdrs);
         pduLen++;
      }
      else
      {
         SAddPstMsg((U8)len, subHdrs);
         pduLen++;
      }
   }
   else
   {
      SAddPstMsg(byte, subHdrs);
      pduLen++;
   }

   if ((tbSz - len) <= 2)
   {
      /* Add padding subheaders at the beginning of sub headers*/
      pad = UE_MAC_PAD_SUBHDR;
      SAddPreMsg(pad, subHdrs);
      SAddPreMsg(pad, subHdrs);
   }
   else
   {
      /* Add a padding subheader and fill up rest of the PDU */
      byte = UE_MAC_PAD_LCID;
      SAddPstMsg(byte, subHdrs);
      pduLen++;
      SAddPstMsgMult((U8 *)paddingBytes, tbSz - pduLen, dataPdu);
   }

   SCatMsg(subHdrs, dataPdu, M1M2);
   SPutMsg(dataPdu);
   *pdu = subHdrs;

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueMacAddUlDat 
 * 
 *       Desc:   This function adds a UE UL transmission to a subframe.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Allocate memory for adding a UE transmission using cmGetMem.
 *               2. Add to the list of transmissions and set fields.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacAddUlDat
(
CellCb             *cell,
CmLteTimingInfo    tmInfo,
UeCb               *ueCb,
Buffer             *mBuf
)
#else
PRIVATE S16 ueMacAddUlDat(cell,tmInfo,ueCb,mBuf)
CellCb             *cell;
CmLteTimingInfo    tmInfo;
UeCb               *ueCb;
Buffer             *mBuf;
#endif
{
   UeMacUlSf       *sf;
   TfuDatInfo      *dat;

   TRC2(ueMacAddUlDat)

   sf = &(cell->ueMacUlSf[tmInfo.subframe]);
   if (cmGetMem(sf->datInd, sizeof(TfuDatInfo), (Ptr *)&dat) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE087, (ErrVal)0,
         "ueMacAddUlDat:  Allocation failed for DatInfo\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacAddUlDat: Sending Data to eNodeB"));

   sf->datInd->cellId = ueCb->cellId;
   dat->rnti = ueCb->rnti;
   dat->mBuf = mBuf;
   dat->lnk.node = (PTR) dat;
   cmLListAdd2Tail(&sf->datInd->datIndLst, &dat->lnk);
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueMacAddSr
 * 
 *       Desc:   This function adds a UE SR transmission to a subframe.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Allocate memory for adding a UE SR transmission using cmGetMem.
 *               2. Add to the list of transmissions and set fields.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacAddSr
(
CellCb            *cell,
CmLteTimingInfo    tmInfo,
UeCb               *ueCb
)
#else
PRIVATE S16 ueMacAddSr(cell,tmInfo,ueCb)
CellCb            *cell;
CmLteTimingInfo    tmInfo;
UeCb               *ueCb;
#endif
{
   UeMacUlSf       *sf;
   TfuSrInfo       *sr;

   TRC2(ueMacAddSr)

   sf = &(cell->ueMacUlSf[tmInfo.subframe]);
   if (cmGetMem(sf->srInd, sizeof(TfuSrInfo), (Ptr *)&sr) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE088, (ErrVal)0,
         "ueMacAddSr:  Allocation failed for TfuSrInfo\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacAddSr: Sending SR Indication "));

   sf->srInd->cellId = ueCb->cellId;
   sr->rnti = ueCb->rnti;
   cmLListAdd2Tail(&sf->srInd->srLst, &sr->lnk);
   sr->lnk.node = (PTR)sr;
   RETVALUE(ROK);
}


/* ue002.101: Changes to support MSPD CL */
/* 
 *
 *       Fun:    ueMacAddCqi
 * 
 *       Desc:   This function adds a UE CQI transmission to a subframe.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Allocate memory for adding a UE CQI transmission using cmGetMem.
 *               2. Add to the list of transmissions and set fields.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacAddCqi
(
CellCb            *cell,
CmLteTimingInfo    tmInfo,
UeCb               *ueCb
)
#else
PRIVATE S16 ueMacAddCqi(cell,tmInfo,ueCb)
CellCb             *cell;
CmLteTimingInfo    tmInfo;
UeCb               *ueCb;
#endif
{
   UeMacUlSf       *sf;
   TfuDlCqiRpt      *cqi;

   TRC2(ueMacAddCqi)

   sf = &(cell->ueMacUlSf[tmInfo.subframe]);
   if (cmGetMem(sf->dlCqiInd, sizeof(TfuDlCqiRpt), (Ptr *)&cqi) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE088, (ErrVal)0,
         "ueMacAddCqi:  Allocation failed for TfuDlCqiRpt\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacAddCqi: Sending CQI Indication "));

   sf->dlCqiInd->cellId = ueCb->cellId;
   cqi->rnti = ueCb->rnti;

   cqi->isPucchInfo = TRUE;
   cqi->dlCqiInfo.pucchCqi.mode = TFU_PUCCH_CQI_MODE10;
   cqi->dlCqiInfo.pucchCqi.u.mode10Info.type = TFU_RPT_CQI;
   cqi->dlCqiInfo.pucchCqi.u.mode10Info.u.cqi = 15;

   cmLListAdd2Tail(&sf->dlCqiInd->dlCqiRptsLst, &cqi->lnk);
   cqi->lnk.node = (PTR)cqi;
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueMacAddri
 * 
 *       Desc:   This function adds a UE CQI transmission to a subframe.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Allocate memory for adding a UE CQI transmission using cmGetMem.
 *               2. Add to the list of transmissions and set fields.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacAddRi
(
CellCb            *cell,
CmLteTimingInfo    tmInfo,
UeCb               *ueCb
)
#else
PRIVATE S16 ueMacAddRi(cell,tmInfo,ueCb)
CellCb             *cell;
CmLteTimingInfo    tmInfo;
UeCb               *ueCb;
#endif
{
   UeMacUlSf       *sf;
   TfuDlCqiRpt      *cqi;

   TRC2(ueMacAddCqi)

   sf = &(cell->ueMacUlSf[tmInfo.subframe]);
   if (cmGetMem(sf->dlCqiInd, sizeof(TfuDlCqiRpt), (Ptr *)&cqi) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE088, (ErrVal)0,
         "ueMacAddCqi:  Allocation failed for TfuDlCqiRpt\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacAddCqi: Sending RI Indication "));

   sf->dlCqiInd->cellId = ueCb->cellId;
   cqi->rnti = ueCb->rnti;

   cqi->isPucchInfo = TRUE;
   cqi->dlCqiInfo.pucchCqi.mode = TFU_PUCCH_CQI_MODE10;
   cqi->dlCqiInfo.pucchCqi.u.mode10Info.type = TFU_RPT_RI;
   cqi->dlCqiInfo.pucchCqi.u.mode10Info.u.ri = 2 ;

   cmLListAdd2Tail(&sf->dlCqiInd->dlCqiRptsLst, &cqi->lnk);
   cqi->lnk.node = (PTR)cqi;
   RETVALUE(ROK);
}


/* 
 *
 *       Fun:    ueMacAddHq
 * 
 *       Desc:   This function adds a DL HARQ transmission to a subframe.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Allocate memory for adding a DL HARQ transmission using cmGetMem.
 *               2. Add to the list of transmissions and set fields.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueMacAddHq
(
CellCb             *cell,
CmLteTimingInfo    tmInfo,
UeCb               *ueCb,
U8                  noOfTbs
)
#else
PRIVATE S16 ueMacAddHq(cell,tmInfo,ueCb,noOfTbs)
CellCb             *cell;
CmLteTimingInfo    tmInfo;
UeCb               *ueCb;
U8                  noOfTbs;
#endif
{
   UeMacUlSf       *sf;
   TfuHqInfo       *hq;

   TRC3(ueMacAddHq)

/* ue002.101: Changes to support TDD configuration */
#ifdef TFU_TDD
   if (cell->dlUlCfg == LTE_TDD_CFG_TYPE_2)
   {
      if((tmInfo.subframe == 4)|| 
         (tmInfo.subframe == 5)||
         (tmInfo.subframe == 6)||
         (tmInfo.subframe == 8))
      {
         sf = &(cell->ueMacUlSf[2]);
      }
      else
      {
         sf = &(cell->ueMacUlSf[7]);
      }
   }
   else if ( cell->dlUlCfg == LTE_TDD_CFG_TYPE_5)
   {
      sf = &(cell->ueMacUlSf[2]);
   }
#else
   if (tmInfo.subframe + 4 > UE_NUM_SUB_FRAMES)
   {
      tmInfo.sfn = (tmInfo.sfn + 1) % 1024;
   }
   tmInfo.subframe = (tmInfo.subframe + 4) % UE_NUM_SUB_FRAMES;
   sf = &(cell->ueMacUlSf[tmInfo.subframe]);
#endif

   if (cmGetMem(sf->hqInd, sizeof(TfuHqInfo), (Ptr *)&hq) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE089, (ErrVal)0,
         "ueMacAddHq :  Allocation failed for TfuHqInfo\n"); 
      RETVALUE(RFAILED);
   }
   sf->hqInd->cellId = ueCb->cellId;
   hq->rnti = ueCb->rnti;
   hq->noOfTbs = noOfTbs;

#ifdef TFU_TDD
   hq->M    = 1;
   hq->hqFbk[0][0] = 1; /* Assuming ACK (positive) as 1 and thinking this
                               is the matrix for that */
#else
   hq->isAck[0] = 1;
   if (noOfTbs > 1)
   {
      hq->isAck[1] = 1;
   }
#endif
   hq->lnk.node = (PTR)hq;
   
   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueMacAddHq: Sending HARQ feedback "));

   cmLListAdd2Tail(&sf->hqInd->hqIndLst, &hq->lnk);


   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueMacHndlRach 
 * 
 *       Desc:   This function is called to generate RACH requests in UL.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.  Ascertain that the subframe is a RACH occasion.
 *               2. If there is any UE pending RACH, generate for just one UE.
 *
 *       File:   ue_mac.c
 *
 */

#ifdef ANSI
PRIVATE Void ueMacHndlRach
(
CellCb              *cell,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE Void ueMacHndlRach(cell,tmInfo)
CellCb              *cell;
CmLteTimingInfo      tmInfo;
#endif
{
   Mem               mem;
   TfuRaReqIndInfo   *rachReq;
   TfuRaReqInfo      *rachInfo;
   Pst               pst;
   CmLList           *lnk;
   UeCb              *ueCb;

   TRC3(ueMacHndlRach)

   UE_DBGP_INFO((UE_PRNTBUF, 
       "ueMacHndlRach: Sending the RACH Indication to eNodeB"));
   /* frame number 1 is the RACH occasion for the given configuration */
   /* At this point we support only one UE. We will fetch UE from     */
   /* the RACH queue which is filled up at the time of init           */
   /* ue002.101: Changes to support TDD configuration */
#ifdef TFU_TDD
   if (tmInfo.subframe == 1)
   {
      if (cell->rachLst.first != NULLP)
      {
         lnk = cellArr->rachLst.first;
         cmLListDelFrm(&cell->rachLst, lnk);
         ueCb = (UeCb *)(lnk->node);
         mem.region = 0; mem.pool = 0;
         /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
         if (cmAllocEvnt(sizeof(TfuRaReqIndInfo), TFU_BLKSZ,
                         &mem, (Ptr *)&rachReq) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
               "ueMacHndlRach:  Allocation failed for RaReqInd\n"); 
            RETVOID;
         }
         
         rachReq->cellId = ueCb->cellId;
         rachReq->timingInfo = tmInfo;
         rachReq->timingInfo.subframe++;
         rachReq->nmbOfRaRnti = 1;
         UE_GET_MEM(rachReq,sizeof(TfuRachInfo), &rachReq->rachInfoArr); 
         rachReq->rachInfoArr[0].raRnti = 3;
         rachReq->rachInfoArr[0].numRaReqInfo = 1;
         UE_GET_MEM(rachReq,sizeof(TfuRaReqInfo), &rachReq->rachInfoArr[0].raReqInfoArr); 

         rachInfo = &rachReq->rachInfoArr[0].raReqInfoArr[0];
         rachInfo->rapId = ueCb->mac.preambleId = (cell->preambleId++)%UE_MAX_PREAMBLE; 
         rachInfo->ta    = 0;
         rachInfo->tpc   = 0;
         rachInfo->cqiPres = TRUE;
         rachInfo->cqiIdx = 15;
/* ue003.101: Compute latency */
#ifdef UE_COMPUTE_LATENCY
         tmDelayInfo.rachReq.status = 1;
         tmDelayInfo.rachReq.tmInfo = tmInfo;
         if (gettimeofday(&tmDelayInfo.rachReq.ts, NULL) == -1)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
               "ueMacHndlRach: gettimeofday() failed\n"); 
         }
#endif

         TfUiTfuRaReqInd(&pst, 0, rachReq);
         ueAppCellCb.numRachReqSent++;
      }
   }
#else
   if (tmInfo.subframe == 3)
   {
      if (cell->rachLst.first != NULLP)
      {
         lnk = cell->rachLst.first;
         cmLListDelFrm(&cell->rachLst, lnk);
         ueCb = (UeCb *)(lnk->node);
         mem.region = 0; mem.pool = 0;
         /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
         if (cmAllocEvnt(sizeof(TfuRaReqIndInfo), TFU_BLKSZ,
                         &mem, (Ptr *)&rachReq) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
               "ueMacHndlRach:  Allocation failed for RaReqInd\n"); 
            RETVOID;
         }
         
         rachReq->cellId = ueCb->cellId;
#ifndef YS_MSPD
         /*rachReq->timingInfo.subframe++;*/
         rachReq->timingInfo.subframe = (rachReq->timingInfo.subframe + 1) % 10;
#endif
         if (tmInfo.subframe + 4 > 10)
         {
            tmInfo.sfn = (tmInfo.sfn + 1) % 1024;
         }
         rachReq->timingInfo = tmInfo;
         rachReq->nmbOfRaRnti = 1;
         UE_GET_MEM(rachReq,sizeof(TfuRachInfo), &rachReq->rachInfoArr); 
#ifndef YS_MSPD
         rachReq->rachInfoArr[0].raRnti = 3;
#else
         rachReq->rachInfoArr[0].raRnti = 2;
#endif
         rachReq->rachInfoArr[0].numRaReqInfo = 1;
         UE_GET_MEM(rachReq,sizeof(TfuRaReqInfo), &rachReq->rachInfoArr[0].raReqInfoArr); 

         rachInfo = &rachReq->rachInfoArr[0].raReqInfoArr[0];
         rachInfo->rapId = ueCb->mac.preambleId = (cell->preambleId++)%6; 
         rachInfo->ta    = 0;
         rachInfo->tpc   = 0;
         rachInfo->cqiPres = TRUE;
         rachInfo->cqiIdx = 15;
/* ue003.101: Compute latency */
#ifdef UE_COMPUTE_LATENCY
         tmDelayInfo.rachReq.status = 1;
         tmDelayInfo.rachReq.tmInfo = tmInfo;
         if (gettimeofday(&tmDelayInfo.rachReq.ts, NULL) == -1)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
               "ueMacHndlRach: gettimeofday() failed\n"); 
         }
#endif

         TfUiTfuRaReqInd(&pst, 0, rachReq);
         ueSimAppCb.numRachReqSent++;
      }
   }
#endif
}

            
/* ue008.101: Added new function ueMacProcRarGrant() */
/* 
 *
 *       Fun:    ueMacProcRarGrant
 * 
 *       Desc:   This function is to process the grant allocated through RAR 
 *               PDU during the RACH procedure had taken place for other then 
 *               initial Attach.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacProcRarGrant
(
CellCb              *cell,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE Void ueMacProcRarGrant(cell,tmInfo)
CellCb               *cell;
CmLteTimingInfo      tmInfo;
#endif
{
   UeCb *ueCb = NULLP;
   RarGrantInfo *grantInfo = NULLP;
   Buffer *pdu = NULLP;
   UeAppCb *ueAppCb = NULLP; 

  
   TRC3(ueMacProcRarGrant);
   
   ueCb = &cell->ueArr[0];
   grantInfo = &ueCb->mac.grantInfo;
   
   if (TRUE == grantInfo->grantSts)
   {
      /* Unsetting the BSR flag to block the BSR report to the eNB2 */
      ueCb->mac.reportBsr = FALSE;
      printf("\n*********** Adding RRC Recfg Complete at TTI SFN:%d, Subframe:%d********\n",tmInfo.sfn, tmInfo.subframe);
      ueMacUlAlloc(ueCb, grantInfo->tbSz, &pdu);
      SPrntMsg(pdu,0,0);
      printf("\n***********Sending RRC Recfg Complete at SFN:%d, Subframe:%d********\n",grantInfo->tmInfo.sfn,grantInfo->tmInfo.subframe);
      ueMacAddUlDat(cell,grantInfo->tmInfo, ueCb, pdu);
      /* reset the RAR grant Info */
      grantInfo->tbSz = 0;
      grantInfo->grantSts = FALSE;     
      grantInfo->tmInfo.sfn = 0;
      grantInfo->tmInfo.subframe = 0;     
      /* Get UeAppCb using the macro using ueCb->ueId */
      UE_GET_APPCB(ueCb->cellId,ueAppCb,ueCb->rnti);
      ueAppCb->hoState = 0;
   }
}

#ifdef ANSI
PUBLIC Void ueMacHndlRachForHo
(
CmLteTimingInfo      tmInfo,
U16                  cellId,
U32                  prmIdx
)
#else
PUBLIC Void ueMacHndlRachForHo(tmInfo,cellId,prmIdx)
CmLteTimingInfo      tmInfo;
U16                  cellId;
U32                  prmIdx;
#endif
{
   Mem               mem;
   TfuRaReqIndInfo   *rachReq;
   TfuRaReqInfo      *rachInfo;
   Pst               pst;
   CmLList           *lnk;
   UeCb              *ueCb;

   TRC3(ueMacHndlRach)

   UE_DBGP_INFO((UE_PRNTBUF, 
       "ueMacHndlRach: Sending the RACH Indication to eNodeB"));


      if (cellArr[0].rachLst.first != NULLP)
      {
         lnk = cellArr[0].rachLst.first;
         cmLListDelFrm(&cellArr[0].rachLst, lnk);
         ueCb = (UeCb *)(lnk->node);
         mem.region = 0; mem.pool = 0;
         if (cmAllocEvnt(sizeof(TfuRaReqIndInfo), sizeof(TfuRaReqIndInfo),
                         &mem, (Ptr *)&rachReq) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
               "ueMacHndlRach:  Allocation failed for RaReqInd\n"); 
            RETVOID;
         }
         
         rachReq->cellId = cellId;
         if (tmInfo.subframe + 4 > 10)
         {
            tmInfo.sfn = (tmInfo.sfn + 1) % 1024;
         }
         rachReq->timingInfo = tmInfo;
         rachReq->nmbOfRaRnti = 1;
         UE_GET_MEM(rachReq,sizeof(TfuRachInfo), &rachReq->rachInfoArr); 
#ifndef YS_MSPD
         rachReq->rachInfoArr[0].raRnti = 3;
#else
         rachReq->rachInfoArr[0].raRnti = 2;
#endif
         rachReq->rachInfoArr[0].numRaReqInfo = 1;
         UE_GET_MEM(rachReq,sizeof(TfuRaReqInfo), &rachReq->rachInfoArr[0].raReqInfoArr); 

         rachInfo = &rachReq->rachInfoArr[0].raReqInfoArr[0];
         rachInfo->rapId = ueCb->mac.preambleId = prmIdx;
         rachInfo->ta    = 0;
         rachInfo->tpc   = 0;
         rachInfo->cqiPres = TRUE;
         rachInfo->cqiIdx = 15;
         TfUiTfuRaReqInd(&pst, 0, rachReq);
         ueSimAppCb.numRachReqSent++;
      }
}

#ifdef YS_MSPD
/* 
 *
 *       Fun:   ueMacPrcSr 
 * 
 *       Desc:  This function is called to include SR requests in UL.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.Include SR in MAC header if the flag is set to true. 
 *               2. Check for the BO and if positive set the flag to true.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacPrcSr
(
UeCb                 *ueCb,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE Void ueMacPrcSr(ueCb, tmInfo)
UeCb                 *ueCb;
CmLteTimingInfo      tmInfo;
#endif
{
   U32               lcg0, lcg1, lcg2, lcg3;

   TRC3(ueMacPrcSr)
   if((ueCb->srCfgInfo == NULLP) || 
      ((((tmInfo.sfn * UE_NUM_SUB_FRAMES) + tmInfo.subframe - 
         ueCb->srCfgInfo->srSfOffSet) % ueCb->srCfgInfo->srPeriod) != 0))
   {
      RETVOID;
   }

   ueRlcGetBo(ueCb, &lcg0, &lcg1, &lcg2, &lcg3);
   if (ueCb->mac.srReq == TRUE)
   {
      /* Trigger SR for this UE at UL subframe 2 */
      ueMacAddSr(tmInfo, ueCb);
      ueCb->mac.reportBsr = TRUE;
   }
   UE_DBGP_INFO((UE_PRNTBUF, 
            "ueMacPrcSr: Setting the SR falg based on BO %ld",lcg0 + lcg1));
   if ((lcg0 != 0) || (lcg1 != 0) || (lcg2 != 0) || (lcg3 != 0))
   {
      ueCb->mac.srReq = TRUE;
   }
   else
   {
      ueCb->mac.srReq = FALSE;
   }
}

#endif

/* 
 *
 *       Fun:   ueMacPrcCqi 
 * 
 *       Desc:  This function is called to include CQI requests in UL.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes: 
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacPrcCqi
(
CellCb               *cell,
UeCb                 *ueCb,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE Void ueMacPrcCqi(cell,ueCb, tmInfo)
CellCb               *cell;
UeCb                 *ueCb;
CmLteTimingInfo      tmInfo;
#endif
{
 
   TRC3(ueMacPrcCqi)
   if((ueCb->cqiCfgInfo == NULLP) || 
         ((((tmInfo.sfn * UE_NUM_SUB_FRAMES) + tmInfo.subframe - 
            ueCb->cqiCfgInfo->cqiSfOffSet) % ueCb->cqiCfgInfo->cqiPeriod) != 0))
   {
      RETVOID;
   }
   ueMacAddCqi(cell,tmInfo, ueCb);
#if 0
   if((ueCb->riCfgInfo == NULLP) || 
         ((((tmInfo.sfn * UE_NUM_SUB_FRAMES) + tmInfo.subframe - 
            ueCb->riCfgInfo->riSfOffSet) % ueCb->riCfgInfo->riPeriod) != 0))
   {
      RETVOID;
   }
#endif
   ueMacAddRi(cell,tmInfo,ueCb);
}

#ifdef YS_MSPD
/* 
 *
 *       Fun:   ueMacPrcSch 
 * 
 *       Desc:  This function is called to calculate UE schulings
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacPrcSch
(
CellCb              *cell,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE Void ueMacPrcSch(cell,tmInfo)
CellCb              *cell;
CmLteTimingInfo      tmInfo;
#endif
{
   U8                i;
   UeCb              *ueCb;
 
   TRC3(ueMacPrcSch)
    
   /* For now we support only one UE. In future, we could keep */
   /* track of UEs active at MAC and process accordingly   */
   for (i = 0; i < UE_NUM_PER_CELL; i++)
   {
      ueCb = &cell->ueArr[i];

      /* Process SRs */
      ueMacPrcSr(cell,ueCb, tmInfo);

      /* Process CQI */
      ueMacPrcCqi(cell,ueCb, tmInfo);
   }
}
#endif /* YS_MSPD */

#ifndef YS_MSPD
/* 
 *
 *       Fun:   ueMacPrcSrs 
 * 
 *       Desc:  This function is called to include SR requests in UL.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.Include SR in MAC header if the flag is set to true. 
 *               2. Check for the BO and if positive set the flag to true.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacPrcSrs
(
CellCb              *cell,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE Void ueMacPrcSrs(cell,tmInfo)
CellCb              *cell;
CmLteTimingInfo      tmInfo;
#endif
{
   U8                i;
   UeCb              *ueCb;
   U32               lcg0, lcg1, lcg2, lcg3;
 
   TRC3(ueMacPrcSrs)
   
/* ue002.101: Changes to support TDD configuration */
#ifdef TFU_TDD   
   if (tmInfo.subframe != 0)
   {
      RETVOID;
   }

   tmInfo.subframe = 2;
#endif

   /* For now we support only one UE. In future, we could keep */
   /* track of UEs active at MAC and process SRs accordingly   */
   /* For now frequency of SR is every 10 subframes */
   for (i = 0; i < UE_NUM_PER_CELL; i++)
   {
      ueCb = &cell->ueArr[i];
      ueRlcGetBo(ueCb, &lcg0, &lcg1, &lcg2, &lcg3);
      if (ueCb->mac.srReq == TRUE)
      {
         /* Trigger SR for this UE at UL subframe 2 */
         ueMacAddSr(cell,tmInfo, ueCb);
         ueCb->mac.reportBsr = TRUE;
      }
      UE_DBGP_INFO((UE_PRNTBUF, 
         "ueMacPrcSrs: Setting the SR falg based on BO %ld",lcg0 + lcg1));
      if ((lcg0 != 0) || (lcg1 != 0) || (lcg2 != 0) || (lcg3 != 0))
      {
         ueCb->mac.srReq = TRUE;
      }
      else
      {
         ueCb->mac.srReq = FALSE;
      }

      /* Process CQI */
      ueMacPrcCqi(cell,ueCb, tmInfo);
   }
}
#endif

/* 
 *
 *       Fun:   ueMacTtiInd
 * 
 *       Desc:  This function receives TTI indication at UE.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Process any pending RACH access towards E NodeB. 
 *               2. Generate any SR towards E NodeB.
 *
 *       File:   ue_mac.c
 *
 */

#ifdef ANSI
PRIVATE S16 ueMacTtiInd 
(
CellCb              *cell,
CmLteTimingInfo      tmInfo
)
#else
PRIVATE S16 ueMacTtiInd(cell,tmInfo)
CellCb               *cell;
CmLteTimingInfo      tmInfo;
#endif
{
   Pst               pst;
   UeMacUlSf         *sf;
   Mem               mem;
   /* ue006.101: Changes for end to end performance */
   /* ue007.101: unused variable */
   U32               sfmnm;

/* ue002.101: Changes to support MSPD CL */
   U16               cellId;
#ifdef YS_MSPD
   cellId = 1;
#endif
   TRC3(ueMacTtiInd)


   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacTtiInd: Processing the TTI Indication cellId (%d) :(subframe)%d (sfn)%d",
      cell->cellId,tmInfo.subframe, tmInfo.sfn));
   /* SRIKY: Added for debugging onsite */
#ifdef DEBUGP
   if (prvTmInfo.subframe == 9) 
   {
       if ((tmInfo.sfn != ((prvTmInfo.sfn + 1) % 1024)) ||
           (tmInfo.subframe != 0))
       {
          UE_DBGP_INFO((UE_PRNTBUF, "Rcvd {%d,%d}, Prev {%d,%d}\n", tmInfo.sfn, tmInfo.subframe,
                  prvTmInfo.sfn, prvTmInfo.subframe));
       }
   }
   else
   {
       if (((prvTmInfo.subframe + 1) != tmInfo.subframe) ||
           (prvTmInfo.sfn != tmInfo.sfn))
       {
          UE_DBGP_INFO((UE_PRNTBUF, "Rcvd {%d,%d}, Prev {%d,%d}\n", tmInfo.sfn, tmInfo.subframe,
                  prvTmInfo.sfn, prvTmInfo.subframe));
       }
   }
   prvTmInfo = tmInfo;
   if ((tmInfo.subframe == 0) && (tmInfo.sfn % 128 == 0))
   {  /* ue007.101: type specifier warning fixed */
      UE_DBGP_INFO((UE_PRNTBUF, "No of MAC PDUs prep = %d MAC PDUs sent= %d RLC PDUs = %d\n", 
              noMacPdus, noMacPdusSent, noRlcPdus));
#ifndef LTE_E2E_PERF_MEAS      
      UE_DBGP_INFO((UE_PRNTBUF,"No of APP SDUs = %d RLC SDUs = %d, RLC PDUs = %d\n", 
              noAppSdus, noRlcSdus, noRlcPdus));
      noAppSdus = noRlcSdus = noRlcPdus = 0;
#endif      
   }
#endif /* DEBUGP */
/* ue003.101: Compute latency */
#ifdef UE_COMPUTE_LATENCY
   if((latencyCompDone == 0) && (tmDelayInfo.attachComp.status == 2))
   {
      struct timespec interval;

      latencyCompDone = 1;

      printf("Msg sent(sfn, subframe): rachPreamble at (%d, %d),\
            Msg3 at(%d, %d)\n rrcConRecfComp at (%d, %d), attachComp at (%d, %d)\n", 
              tmDelayInfo.rachReq.tmInfo.sfn,tmDelayInfo.rachReq.tmInfo.subframe
              ,tmDelayInfo.rrcConReq.tmInfo.sfn, 
               tmDelayInfo.rrcConReq.tmInfo.subframe, 
               tmDelayInfo.rrcConRecfgComp.tmInfo.sfn, 
               tmDelayInfo.rrcConRecfgComp.tmInfo.subframe, 
               tmDelayInfo.attachComp.tmInfo.sfn, 
               tmDelayInfo.attachComp.tmInfo.subframe);

      printf("Msg sent(sec, usec): rachPreamble at (%ld sec, %ld usec),\
            Msg3 at(%ld sec, %ld usec)\nrrcConRecfComp at (%ld sec, %ld usec),\
            attachComp at (%ld sec, %ld usec)\n", 
             tmDelayInfo.rachReq.ts.tv_sec, tmDelayInfo.rachReq.ts.tv_nsec, 
             tmDelayInfo.rrcConReq.ts.tv_sec, tmDelayInfo.rrcConReq.ts.tv_nsec, 
             tmDelayInfo.rrcConRecfgComp.ts.tv_sec, 
             tmDelayInfo.rrcConRecfgComp.ts.tv_nsec, 
             tmDelayInfo.attachComp.ts.tv_sec, 
             tmDelayInfo.attachComp.ts.tv_nsec);

      interval.tv_nsec = (((tmDelayInfo.rrcConReq.ts.tv_sec -
               tmDelayInfo.rachReq.ts.tv_sec) * 1000000) + 
               (tmDelayInfo.rrcConReq.ts.tv_nsec - 
                 tmDelayInfo.rachReq.ts.tv_nsec));
      printf("Time elapsed(in usec): rachPreamble to msg3:%ld usec\n", 
              interval.tv_nsec);

      interval.tv_nsec = (((tmDelayInfo.rrcConRecfgComp.ts.tv_sec - 
                         tmDelayInfo.rrcConReq.ts.tv_sec) * 1000000) + 
                         (tmDelayInfo.rrcConRecfgComp.ts.tv_nsec - 
                          tmDelayInfo.rrcConReq.ts.tv_nsec));
      printf("Time elapsed(in usec): msg3 to RRC Connection\
            Reconfiguration:%ld usec\n", interval.tv_nsec);

      interval.tv_nsec = (((tmDelayInfo.attachComp.ts.tv_sec - 
                         tmDelayInfo.rrcConRecfgComp.ts.tv_sec) * 1000000) +
                        (tmDelayInfo.attachComp.ts.tv_nsec - 
                         tmDelayInfo.rrcConRecfgComp.ts.tv_nsec)); 
      printf("Time elapsed(in usec): RRC Connection Reconfiguration to attach\
            complete:%ld usec\n", interval.tv_nsec);
   }
#endif

   /* Place SR and RACH processing here */
#ifdef ENB_PERF_MEAS    
   if (ueAppNumRecfgComplSent == ueAppCellCb.numRachReqSent)
   {
      ueMacHndlRach(cell,tmInfo);
   }
#elif defined(LTE_E2E_PERF_MEAS)
   if(ueAppCellCb.numAttachCompSent == ueAppCellCb.numRachReqSent)
   {
      ueMacHndlRach(cell,tmInfo);
   }
#else
   ueMacHndlRach(cell,tmInfo);
#endif
   /* ue008.101: This is to process the grant allocated through RAR PDU during the RACH procedure
      had taken place for other then initial Attach */
   ueMacProcRarGrant(cell,tmInfo);

/* ue002.101: Changes to support MSPD CL */
#ifndef YS_MSPD
   /* Process SRs */
   ueMacPrcSrs(cell,tmInfo);
#else
   ueMacPrcSch(cell,tmInfo);
#endif /*YS_MSPD */      

   /* Deliver the subframe to PAL */
   mem.region = 0; mem.pool = 0;
   sf = &(cell->ueMacUlSf[tmInfo.subframe]);
   if (sf->datInd)
   {
      if(sf->datInd->datIndLst.count != 0)
      {
       /* ue006.101: Changes for end to end performance */
       noMacPdusSent++;
/* ue003.101: Compute latency */
#ifdef UE_COMPUTE_LATENCY
         if (tmDelayInfo.rrcConReq.status == 1)
         {
            tmDelayInfo.rrcConReq.status = 2;
            tmDelayInfo.rrcConReq.tmInfo = tmInfo;
            if (gettimeofday(&tmDelayInfo.rrcConReq.ts, NULL) == -1)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
                  "ueMacTtiInd: gettimeofday() failed\n"); 
            }
         }

         if (tmDelayInfo.rrcConRecfgComp.status == 1)
         {
            tmDelayInfo.rrcConRecfgComp.status = 2;
            tmDelayInfo.rrcConRecfgComp.tmInfo = tmInfo;
            if (gettimeofday(&tmDelayInfo.rrcConRecfgComp.ts, NULL) == -1)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
                  "ueMacTtiInd: gettimeofday() failed\n"); 
            }
         }

         if (tmDelayInfo.attachComp.status == 1)
         {
            tmDelayInfo.attachComp.status = 2;
            tmDelayInfo.attachComp.tmInfo = tmInfo;
            if (gettimeofday(&tmDelayInfo.attachComp.ts, NULL) == -1)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE090, (ErrVal)0,
                  "ueMacTtiInd: gettimeofday() failed\n"); 
            }
         }
#endif

         /* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
         cellId = sf->datInd->cellId;
         TfUiTfuDatInd(&pst, 0, sf->datInd);
         sf->datInd = NULLP;
#else        
         TfUiTfuDatInd(&pst, 0, sf->datInd);
#endif         
         /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
         if (cmAllocEvnt(sizeof(TfuDatIndInfo), TFU_BLKSZ, &mem, 
                  (Ptr *)&sf->datInd) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE091, (ErrVal)0,
               "ueMacTtiInd:  Allocation failed for TfuDatInd\n"); 
            RETVALUE(RFAILED);
         }
         cmLListInit(&sf->datInd->datIndLst);
      }
      sf->datInd->timingInfo = tmInfo;
#ifndef YS_MSPD
      sf->datInd->timingInfo.sfn = ((tmInfo.sfn + 1) % 1024);
#endif
   }

   if (sf->srInd)
   {
      if (sf->srInd->srLst.count != 0)
      {
         /* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
         cellId = sf->srInd->cellId;
         TfUiTfuSrInd(&pst, 0, sf->srInd);
         sf->srInd = NULLP;
#else
         TfUiTfuSrInd(&pst, 0, sf->srInd);
#endif         
         /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
         if (cmAllocEvnt(sizeof(TfuSrIndInfo), TFU_BLKSZ, &mem, 
                  (Ptr *)&sf->srInd) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE092, (ErrVal)0,
               "ueMacTtiInd:  Allocation failed for TfuSrInd\n"); 
            RETVALUE(RFAILED);
         }
         cmLListInit(&sf->srInd->srLst);
      }
      sf->srInd->timingInfo = tmInfo;
#ifndef YS_MSPD
      sf->srInd->timingInfo.sfn = ((tmInfo.sfn + 1) % 1024);
#endif
   }
/* ue006.101: Fix added to process and send the HqInd to cl 
 *  and hence to eNb at 1 subframe ahead
 */
  sfmnm = (tmInfo.subframe+1); /*(tmInfo.subframe == 0)?9:(tmInfo.subframe -1);*/
  sf = &(cell->ueMacUlSf[(sfmnm%10)]);
   if (sf->hqInd)
   {
      if (sf->hqInd->hqIndLst.count != 0)
      {
         /* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
         cellId = sf->hqInd->cellId;
         TfUiTfuHqInd(&pst, 0, sf->hqInd);
         sf->hqInd = NULLP;
#else
         TfUiTfuHqInd(&pst, 0, sf->hqInd);
#endif         
         /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
         if (cmAllocEvnt(sizeof(TfuHqIndInfo), TFU_BLKSZ, &mem, 
                  (Ptr *)&sf->hqInd) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE093, (ErrVal)0,
               "ueMacTtiInd:  Allocation failed for TfuHqInd\n"); 
            RETVALUE(RFAILED);
         }
         cmLListInit(&sf->hqInd->hqIndLst);
      }
      sf->hqInd->timingInfo = tmInfo;
      sf->hqInd->timingInfo.subframe = sfmnm %10;
#ifndef YS_MSPD
  if(sfmnm >= 10)
  {
      sf->hqInd->timingInfo.sfn = ((tmInfo.sfn + 2) % 1024);
  }
  else
  {
      sf->hqInd->timingInfo.sfn = ((tmInfo.sfn + 1) % 1024);
  }
#endif
   }

   /* ue002.101: Changes to support MSPD CL */
   if (sf->dlCqiInd)
   {
      if(sf->dlCqiInd->dlCqiRptsLst.count != 0)
      {
         cellId = sf->dlCqiInd->cellId;
         TfUiTfuDlCqiInd(&pst, 0, sf->dlCqiInd);
         sf->dlCqiInd = NULLP;
         /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
         if (cmAllocEvnt(sizeof(TfuDlCqiIndInfo), TFU_BLKSZ, &mem, 
                  (Ptr *)&sf->dlCqiInd) != ROK)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE091, (ErrVal)0,
               "ueMacTtiInd:  Allocation failed for TfuDatInd\n"); 
            RETVALUE(RFAILED);
         }
         cmLListInit(&sf->dlCqiInd->dlCqiRptsLst);
      }
      sf->dlCqiInd->timingInfo = tmInfo;
      sf->dlCqiInd->timingInfo.sfn = ((tmInfo.sfn + 1) % 1024);
   }

#ifdef LTE_START_UL_DL_DATA
   if(tmInfo.subframe == 0)
   {
      ueAppTti(tmInfo);
   }
#endif /* LTE_START_UL_DL_DATA */
      
   /* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
   TfUiTfuEndInd(&pst, 0, tmInfo, cellId);
#endif

#ifdef TA_NEW
   cell->crntTime = tmInfo;
   ueMacTaTmrProc(cell);
#endif
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:   RgLiTfuCntrlReq
 * 
 *       Desc:  This function is for reading PDCCHs with DCI format 0. 
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.  Go through the UL PDCCHs and provide data for the same.  
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PUBLIC S16 RgLiTfuCntrlReq 
(
Pst *                pst,
SpId                 spId,
TfuCntrlReqInfo *    cntrlReq
)
#else
PUBLIC S16 RgLiTfuCntrlReq(pst,spId,cntrlReq)
Pst *                pst;
SpId                 spId;
TfuCntrlReqInfo *    cntrlReq;
#endif
{
   CellCb            *cell;
   CmLListCp         *ulDciLst;
   CmLList           *lnk;
   MsgLen            tbSz;
   U8                iTbs;
   CmLteTimingInfo   tmInfo;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD: Fixed warning for gcc compilation on CentOS*/
   Buffer            *pdu = NULLP;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD_END: Fixed warning for gcc compilation on CentOS*/

   TRC2(RgLiTfuCntrlReq)
   /* Set the time to 4 subframes later */
   tmInfo = cntrlReq->ulTiming;
   /* ue006.101: Changes for end to end performance */
   if (tmInfo.subframe + 4 >= 10)
   {
      tmInfo.sfn = (tmInfo.sfn + 1) % 1024;
   }
   UE_DBGP_INFO((UE_PRNTBUF, 
      "RgLiTfuCntrlReq: Processing the Received TfuCntrlReq "));
#ifdef ENB_PERF_UL_DATA
   tmInfo.subframe = (tmInfo.subframe + 4) % 10;
#else
   tmInfo.subframe = (tmInfo.subframe + 4) % 10;
#endif
   /* Get all the UL DCIs and generate data towards PAL */
   ulDciLst = &cntrlReq->ulPdcchLst;  
   lnk = ulDciLst->first;

   ueUtlFndCell(cntrlReq->cellId,&cell);
   if ((cell == NULLP) || (cntrlReq->cellId == 0))
   {
#if 0
      UELOGERROR(ERRCLS_ADD_RES, EUE094, (ErrVal)cntrlReq->cellId,
            "RgLiTfuCntrlReq: Cell Not found \n"); 
#endif
      cmFreeMem(cntrlReq);
      RETVALUE(RFAILED);
   }

   while (lnk != NULLP)
   {
      TfuPdcchInfo   *ulAlloc;
      UeCb           *ueCb;

      ulAlloc = (TfuPdcchInfo *)(lnk->node);
      lnk     = lnk->next;


      /* This is allocation for a UE. Prepare data for the received alloc */
      if (ueUtlFndUe(cell,ulAlloc->rnti, &ueCb) != ROK)
      {
         /* Print Error here and go to the next ulAlloc */
         UELOGERROR(ERRCLS_ADD_RES, EUE094, (ErrVal)ulAlloc->rnti,
            "RgLiTfuCntrlReq:  UE control block not found\n"); 
         continue;
      }

      /* We have the ue and process the UL allocation here */
      ueCb->mac.srReq = FALSE;

      MAC_GET_ITBS(ulAlloc->dci.u.format0Info.mcs,iTbs);

      if (iTbs > 26)
      {
#ifdef ENB_PERF_UL_DATA
         iTbs = 26; 
#else
         UELOGERROR(ERRCLS_ADD_RES, EUE095, (ErrVal)iTbs,
            "RgLiTfuCntrlReq: Invalid MCS received\n"); 
         continue; 
#endif
      }
      tbSz = ueMacTbSzTbl[iTbs][ulAlloc->dci.u.format0Info.numRb - 1] >> 3;
      ueMacUlAlloc(ueCb, tbSz, &pdu);
      ueMacAddUlDat(cell, tmInfo, ueCb, pdu);
   }
   ueMacTtiInd(cell,cntrlReq->ulTiming);

   /* ue002.101: Multi ue support for Uu interface */
#ifdef ENB_PERF_MEAS    
   if ((ueAppNumRecfgComplSent == UE_NUM_PER_CELL) &&
       ueAppCellCb.state == UE_STATE_DATA_READY)
   {
      ueAppSignalingComplte = TRUE;
   }

   if ((ueAppNumRecfgComplSent == UE_NUM_PER_CELL) &&
       ueAppCellCb.state == UE_STATE_SIGNALLING_COMPLETED)
   {
      ueAppCntrlReqCount++;
      if (ueAppCntrlReqCount == 500)
      {
         ueAppCellCb.state = UE_STATE_DATA_READY;
      }
   }
#endif

   cmFreeMem(cntrlReq);

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:   ueMacHndlRaGrnt 
 * 
 *       Desc:  This function handles RA grant received from E NodeB. 
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Retrieve the UL Grant embedded in the RA grant.
 *               2. From the UL grant, retrieve start RB and num RB of the grant.
 *               3.  From the UL grant, also retrieve MCS and TBS. 
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PRIVATE Void ueMacHndlRaGrnt
(
CellCb           *cell,
CmLteTimingInfo  timingInfo,
Buffer           *mBuf
)
#else
PRIVATE Void ueMacHndlRaGrnt(timingInfo,mBuf)
CellCb           *cell,
CmLteTimingInfo  timingInfo;
Buffer           *mBuf;
#endif
{
   U8                byte;
   U8                rbStart;
   U8                numRbs;
   U32               allocation;
   U32               grant;
   U8                iMcs;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD: Fixed warning for gcc compilation on CentOS*/
   U8                iTbs = 0;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD_END: Fixed warning for gcc compilation on CentOS*/
   U32               tbSz;
   CmLteTimingInfo   tmInfo;
   U8                rapId;
   S16               i;
   UeCb              *ueCb;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD: Fixed warning for gcc compilation on CentOS*/
   Buffer            *pdu = NULLP;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD_END: Fixed warning for gcc compilation on CentOS*/
   U16               crnti;
   /* ue008.101: Added new local variables.*/
   UeAppCb *ueAppCb = NULLP;
   U8      transId = 0;
   NhuDatReqSdus *reCon_pdu = NULLP;

   TRC3(ueMacHndlRaGrnt)
  
   /* ue002.101: kworks_fix */
   ueCb = NULLP;
   /* First byte contains RAP ID. Current assumption is that there       */
   /* is just one RAPID in the data. We will validate and fail otherwise */
   SUnpkU8(&byte, mBuf);
   if ((byte & 0x80) != 0)
   {
      /* Extension is marked. Invalid for now */
      UELOGERROR(ERRCLS_ADD_RES, EUE096, (ErrVal)iTbs,
         "ueMacHndlRaGrnt: there is more than one RAPID in the RAR\n"); 
      SPutMsg(mBuf);
      RETVOID;
   }
   rapId = byte & 0x3f;

   /* throw away the first byte which is part of timing advance */
   SUnpkU8(&byte, mBuf);
   /* Next one has part allocation. Read that */
   SUnpkU8(&byte, mBuf);
   allocation = byte & 0xf;
   /* read two more bytes and add them to allocation */
   SUnpkU8(&byte, mBuf);
   allocation = (allocation << 8) + byte;
   SUnpkU8(&byte, mBuf);
   allocation = (allocation << 8) + byte;

   /* Now allocation contains 20 LSB bits of grant sent by E NodeB */
   /* Of which, some bits form the grant and 4 other for MCS       */
   /* Grant is in RIV format. Decode the start and number of RBs   */
   grant = (0x0007fe00 & allocation) >> 9;
   /* assume number of blocks to be less than 25 */
   rbStart = grant % UE_MAX_BW;
   numRbs  = (grant / UE_MAX_BW) + 1;
   if ((rbStart + numRbs - 1) > UE_MAX_BW)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE097, (ErrVal)grant,
         "ueMacHndlRaGrnt: Grant for RACH access should be quite less\n"); 
      rbStart = UE_MAX_BW  - (grant % UE_MAX_BW) - 1;
      numRbs  = UE_MAX_BW - (grant / UE_MAX_BW) + 1;
   }
   iMcs = (0x000001e0 & allocation) >> 5;
   MAC_GET_ITBS(iMcs, iTbs);
   if (iTbs > 26)
   {
      RETVOID;
   }
   tbSz = ueMacTbSzTbl[iTbs][numRbs - 1] >> 3;

   /* Get the UE control block from the rapId in the buffer */
   for(i = 0; i < UE_NUM_PER_CELL; i++)
   {
      if (cell->ueArr[i].mac.preambleId == rapId)
      {
         ueCb = &cell->ueArr[i];
#ifdef MULTI_UE_ATTACH
         /*-- ue008.101: loop breaks out when the first id match happens --*/
         break;
#endif
      }
   }
   if (ueCb == NULLP)
   {
      /* We could not find the UECb from the preamble Id */
      UELOGERROR(ERRCLS_ADD_RES, EUE098, (ErrVal)rapId,
         "ueMacHndlRaGrnt: UE with preamble id %u does not exist\n"); 
      SPutMsg(mBuf);
      RETVOID;
   }
   ueCb->mac.preambleId = 0xff;
   SUnpkU8(&byte, mBuf);
   crnti = byte;
   SUnpkU8(&byte, mBuf);
   crnti = (crnti << 8) | byte;
   ueCb->rnti = crnti;
   
   printf("RAGRANT received for cellId %d ueId %d\n", cell->cellId,crnti);

   tmInfo = timingInfo;

   /* ue002.101: Changes to support TDD configuration */
#ifdef TFU_TDD   
   tmInfo.subframe = (tmInfo.subframe + 6) % 10;
   if (tmInfo.subframe < 2)
   {
      tmInfo.subframe = 2;
   }
   else
   {
      tmInfo.subframe = 7;
   }
#else
   if (tmInfo.subframe + 4 > 10)
   {
      tmInfo.sfn = (tmInfo.sfn + 1) % 1024;
   }
   tmInfo.subframe = (tmInfo.subframe + 4) % 10;
#endif

   /* ue008.101: Get UeAppCb using the macro using ueCb->ueId */
   
   UE_GET_APPCB(ueCb->cellId,ueAppCb,ueCb->rnti);  

   if (ueAppCb->hoState == 0)
   { 
      /* The msg3 will only go via CCCH (SRB0) to eNB durinng Initial 
         Attach as it doesn't have any other logical(DCCH & DTCH) channel 
         established. Since CCCH comes under TM mode data with respect to RLC
         msg3 is directly getting orginated from MAC here*/
      
      ueMacCreateMsg3(ueCb, tbSz, &pdu);
      ueMacAddUlDat(cell,tmInfo, ueCb, pdu);
   }
   else
   {
      /* The msg3 can go via any logical channel when the RACH procedure 
         was triggered for other then initial attach, 
         Here msg3 is a DCCH RRC message (RRC Connection Reconfiguration Complete) 
         during Handover and it comes under AM mode with respect to the RLC, so it is
         getting orginated from RRC and passes through RLC(normal flow). */
   

      /* Send RRC Reconfig complete */
      ueAppUtlBldRRCConReCfgComplete(&reCon_pdu, transId);

      ueAppLimSndRRCMsg(reCon_pdu, ueAppCb);
      /* Update the Calculated TB size and the tming info 
         innto the UEs MAC Context*/
      ueCb->mac.grantInfo.tbSz = tbSz;
      ueCb->mac.grantInfo.grantSts = TRUE;
      ueCb->mac.grantInfo.tmInfo.sfn = tmInfo.sfn;
      ueCb->mac.grantInfo.tmInfo.subframe = tmInfo.subframe;
   }

/* ue003.101: Compute latency */
#ifdef UE_COMPUTE_LATENCY
   tmDelayInfo.rrcConReq.status = 1;
#endif
   
   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueMacHndlRaGrnt: Sent a RRC Con req to the ENB"));
   SPutMsg(mBuf);
}

/* 
 *
 *       Fun:   RgLiTfuDatReq
 * 
 *       Desc:  This function is processing DL MAC PDUs received from E NodeB.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.  Go through the received DL MAC PDUs and provide SDUs to RLC
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PUBLIC S16 RgLiTfuDatReq 
(
Pst *                pst,
SpId                 spId,
TfuDatReqInfo *      datReq
)
#else
PUBLIC S16 RgLiTfuDatReq(pst,spId,datReq)
Pst *                pst;
SpId                 spId;
TfuDatReqInfo *      datReq;
#endif
{
   CellCb            *cell;
   CmLListCp         *lst;
   CmLList           *lnk;
   TfuDatReqPduInfo  *data;
   UeCb              *ue;
   S16               i;
   U32               count;

   TRC2(RgLiTfuDatReq)

   lst = &datReq->pdus;
   lnk = lst->first;

   UE_DBGP_INFO((UE_PRNTBUF, 
      "RgLiTfuDatReq: Processing the TfuDatReq "));

   ueUtlFndCell(datReq->cellId,&cell);
   if (cell == NULLP)
   {
      printf("cellId wrong for Cell \n");
      if (datReq->bchDat.pres)
      {
         SPutMsg(datReq->bchDat.val);
      }
      RETVALUE(ROK);
   }

   /* ue002.101: Processing MIB changes */
   if (datReq->bchDat.pres)
   {
      if (((datReq->timingInfo.sfn % 4) == 0) && 
          (datReq->timingInfo.subframe == 0))
      {
         UE_DBGP_INFO((UE_PRNTBUF, 
         "RgLiTfuDatReq: Processing the MIB\n"));
      }
      else
      {
         UE_DBGP_INFO((UE_PRNTBUF, 
         "RgLiTfuDatReq: Received MIB in invalid subframe\n"));
         printf("RgLiTfuDatReq: Received MIB in invalid subframe\n");
      }
      SPutMsg(datReq->bchDat.val);
   }

   count = 0;
   while(lnk != NULLP)
   {

      data = (TfuDatReqPduInfo *)(lnk->node);

      lnk = lnk->next;

      if (data->rnti == UE_MAC_SI_RNTI)
      {
#ifdef SI_NEW
         /* The subsequent print and ueRrcSIBInd is disabled to avoid prints for
          *  SIB handling verification */
         if (0)
         {
            printf("\nReceived SI_RNTI sfn(%d) subframe(%d) ", datReq->timingInfo.sfn, datReq->timingInfo.subframe);
            ueRrcSIBInd(data->mBuf[0]);
         }
         else /* This block to be removed if SIB prints are desired */
         {
            SPutMsg(data->mBuf[0]);
         }
#else
         SPutMsg(data->mBuf[0]);
#endif
         continue;
      }
      if (data->rnti == UE_MAC_P_RNTI)
      {
         printf("Received P_RNTI sfn(%d) subframe(%d) ", datReq->timingInfo.sfn, datReq->timingInfo.subframe);
         SPrntMsg(data->mBuf[0], 0 , 0);
         ueRrcPagingInd(cell,data->mBuf[0]);
         continue;
      }
      if (data->rnti <= UE_MAC_MAX_RARNTI)
      {
         /* Process RA RSP. Here we need to send data on UL subframe */
         /* It should have just one RA RSP based on our system       */
         /* UL grant occupies 2.5 bytes starting at 1.5 bytes        */
         ueMacHndlRaGrnt(cell,datReq->timingInfo, data->mBuf[0]);
         /* ue007.101: ccpu00117613 error fix */
         continue;
      }

      if (ueUtlFndUe(cell,data->rnti, &ue) != ROK)
      {
         UE_DBGP_INFO((UE_PRNTBUF, 
               "RgLiTfuDatReq: Could not find UE with rnti %d ",data->rnti));
         continue;
      }

#if 0
      if (data->nmbOfTBs > 1)
      {
        printf("received 2 TBs \n");
      }
#endif
      for (i = 0; i < data->nmbOfTBs; i++)
      {
         MsgLen  len;
#if 0
         /* Trigger HARQ for this UE */
         ueMacAddHq(cell,datReq->timingInfo, ue);
#endif
         SFndLenMsg(data->mBuf[i], &len);
#if 0
         printf("sizeof tb = %d\n", len);
#endif
         ueMacDatInd(cell,ue, data->mBuf[i]);
      }
  
      if (data->nmbOfTBs > 0)
      {
         ueMacAddHq(cell,datReq->timingInfo, ue, data->nmbOfTBs);
      }
   }
   cmFreeMem(datReq);
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:  ueMacRachReq 
 * 
 *       Desc: This function receives RACH requests from higher layers.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.Recieve the request and enqueue it.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PUBLIC Void ueMacRachReq
(
CellCb          *cell,
UeCb            *ueCb,
Buffer          *msg3
)
#else
PUBLIC Void ueMacRachReq(cell,ueCb,msg3)
CellCb          *cell;
UeCb            *ueCb;
Buffer          *msg3; 
#endif
{
   TRC2(ueMacRachReq)
   /* Enqueue the UE on to the rach list */
   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacRachReq: Enqueuing the UE's RACH "));
   cmLListAdd2Tail(&cell->rachLst, &ueCb->mac.rachLnk);
   ueCb->mac.rachLnk.node = (PTR)ueCb;
   ueCb->mac.msg3         = msg3;
}

/* 
 *
 *       Fun:   RgLiTfuRecpReq
 * 
 *       Desc:  This function processes the received reception request.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1.Calls the ueMacTtiInd function.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PUBLIC S16 RgLiTfuRecpReq
(
Pst*                 pst,
SpId                 spId,
TfuRecpReqInfo*      recpReq
)
#else
PUBLIC S16 RgLiTfuRecpReq(pst,spId,recpReq)
Pst*                 pst;
SpId                 spId;
TfuRecpReqInfo*      recpReq;
#endif
{
   TRC2(RgLiTfuRecpReq)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "RgLiTfuRecpReq: Processing the Reception Request "));

/* ue002.101: Changes to support TDD configuration */
#ifdef TFU_TDD
   ueMacTtiInd(recpReq->timingInfo);
#endif

   cmFreeMem(recpReq);
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:   ueMacInit
 * 
 *       Desc:  This function initializes the structures.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. Allocates the memory for DatInd, HqInd and SrInd.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueMacInit
(
CellCb *cell
)
#else
PUBLIC S16 ueMacInit(CellCb *cell)
CellCb *cell;
#endif
{
   S16               i;
   Mem               mem;
   U8                ueIdx;
   Buffer           *msg3;

   TRC2(ueMacInit)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueMacInit: Initializing the MAC structures"));

   mem.region = 0; mem.pool = 0;
   for (i = 0; i < 10; i++)
   {
      UeMacUlSf      *sf;
      sf = &cell->ueMacUlSf[i];
      /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
      if (cmAllocEvnt(sizeof(TfuDatIndInfo), TFU_BLKSZ, &mem, 
                      (Ptr *)&sf->datInd) != ROK)
      {
         RETVALUE(RFAILED);
      }

      /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
      if (cmAllocEvnt(sizeof(TfuSrIndInfo), TFU_BLKSZ, &mem, 
                      (Ptr *)&sf->srInd) != ROK)
      {
         RETVALUE(RFAILED);
      }
      /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
      if (cmAllocEvnt(sizeof(TfuHqIndInfo), TFU_BLKSZ, &mem, 
                      (Ptr *)&sf->hqInd) != ROK)
      {
         RETVALUE(RFAILED);
      }
      /* ue007.101: Modified maxBlkSize to TFU_BLKSZ */
      if (cmAllocEvnt(sizeof(TfuDlCqiIndInfo), TFU_BLKSZ, &mem, 
                      (Ptr *)&sf->dlCqiInd) != ROK)
      {
         RETVALUE(RFAILED);
      }

   }

   for(ueIdx=0; ueIdx < UE_NUM_PER_CELL; ueIdx++)
   {
        /* ue003.101: changes to pass UeInfo for bld */
       ueRrcBuildRRCConReq(&msg3 ,&(cell->ueArr[ueIdx]), FALSE);
       ueMacRachReq(cell, &cell->ueArr[ueIdx], msg3);
   } 
 

   RETVALUE(ROK);
}

/* ue007.101: UESim shutdown support */
/* 
 *
 *       Fun:   ueMacDeInit
 * 
 *       Desc:  This function deinitializes the structures.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  1. DeAllocates the memory for DatInd, HqInd and SrInd.
 *
 *       File:   ue_mac.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueMacDeInit
(
CellCb *cell
 )
#else
PUBLIC S16 ueMacDeInit(cell)
CellCb *cell;
#endif
{
   S16               i;
   S16               ueIdx;
   /* ue008.101 : TIC_ID : ccpu00117550 DEL: Deleted unused variable for warning removal on CentOS*/

   TRC2(ueMacDeInit)

   UE_DBGP_INFO((UE_PRNTBUF, 
            "ueMacDeInit: DeInitializing the MAC structures"));
   for (i = 0; i < 10; i++)
   {
      UeMacUlSf      *sf;
      sf = &(cell->ueMacUlSf[i]);
      if(sf->datInd)
         cmFreeMem(sf->datInd);
      if(sf->srInd)
         cmFreeMem(sf->srInd);
      if(sf->hqInd)
         cmFreeMem(sf->hqInd);
      if(sf->dlCqiInd)
         cmFreeMem(sf->dlCqiInd);
   }
     /* Uninitilize UE */
    for(ueIdx=0; ueIdx < UE_NUM_PER_CELL; ueIdx++)
    {
       CmLList           *lnk;
       UeCb    *ueCb;
       while(cell->rachLst.first != NULLP)
       {
          lnk = cell->rachLst.first;
          cmLListDelFrm(&cell->rachLst, lnk);
          ueCb = (UeCb *)(lnk->node);
          if(ueCb && ueCb->mac.msg3)
          {
             (Void)SPutMsg(ueCb->mac.msg3);
             ueCb->mac.msg3 = NULLP;
          }
       }
   }
      

   RETVALUE(ROK);
}

/**********************************************************************
 
         End of file:     ue_mac.c@@/main/1 - Sun Mar 28 22:59:23 2010
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp                1. Initial Release.
/main/1+   ue002.101  sv                1. Multi ue support changes.
                                        2. Changes to support MSPD CL.
                                        3. Changes to support TDD. 
/main/1+   ue003.101  rp                1. Timing advance support changes.
                                        2. Latency computation.
/main/1+   ue006.101  sriky             1. Performance tuning
                                        2. To process and send the HqInd to cl 
                                           and hence to eNb at 1 subframe ahead
/main/1+   ue007.101  rk                1. Modified maxBlkSize to TFU_BLKS
                                        2. UESim shutdown support.
                      ms                3. fix for ccpu00117613                                           
                                        4. unused variable.                                           
                      rk                5. Fix for uu performance.
                                        6. unused file.
/main/1+   ue008.101  ragrawal          1. TIC_ID :ccpu00117550 Fixed warning for gcc compilation on CentOS
                                        2. Fixed error/warning for g++ compilation on Linux
                                        3. The loop breaks out when the first id match happens
                                        4. Added new function ueMacProcRarGrant().
                                        5. Added new local variables in ueMacHndlRaGrnt()
                                           and ueMacUlAlloc().
                                        6. Added code to get UeAppCb using the macro using 
                                           ueCb->ueId.
                                        7. Changed cellArr index to 0 from (ueCb->cellId - 1).
/main/1+   ue009.101  ragrawal          1. TIC_ID : ccpu00121211 UeSIM crashes when TbSize < 2 bytes.
*********************************************************************91*/

