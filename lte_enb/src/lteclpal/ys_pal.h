
/********************************************************************20**
  
        Name:    Convergence Layer specific
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for CL
 
        File:    ys.h

        Sid:      ys.h@@/main/2 - Thu Dec  2 02:27:12 2010
  
        Prg:     pkumar
  
*********************************************************************21*/

#ifndef __YS_H__
#define __YS_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

#define  YsUiCtfBndReq TfUiCtfBndReq
#define  YsUiCtfBndCfm TfUiCtfBndCfm
#define  YsUiCtfUbndReq TfUiCtfUbndReq
#define  YsUiCtfCfgReq TfUiCtfCfgReq
#define  YsUiCtfCfgCfm TfUiCtfCfgCfm

#define  YsUiTfuBndReq TfUiTfuBndReq
#define  YsUiTfuBndCfm TfUiTfuBndCfm
#define  YsUiTfuUbndReq TfUiTfuUbndReq
#define  YsUiTfuSchBndReq TfUiTfuSchBndReq
#define  YsUiTfuSchBndCfm TfUiTfuSchBndCfm
#define  YsUiTfuSchUbndReq TfUiTfuSchUbndReq
#define  YsUiTfuRaReqInd TfUiTfuRaReqInd
#define  YsUiTfuRecpReq TfUiTfuRecpReq
#define  YsUiTfuCntrlReq TfUiTfuCntrlReq
#define  YsUiTfuDatReq TfUiTfuDatReq
#define  YsUiTfuDatInd TfUiTfuDatInd
#define  YsUiTfuHqInd TfUiTfuHqInd
#define  YsUiTfuSrInd TfUiTfuSrInd
#define  YsUiTfuUlCqiInd TfUiTfuUlCqiInd
#define  YsUiTfuCrcInd TfUiTfuCrcInd
#define  YsUiTfuTimingAdvInd TfUiTfuTimingAdvInd
#define  YsUiTfuTtiInd TfUiTfuTtiInd
#define  YsUiTfuSchTtiInd TfUiTfuSchTtiInd
#define  YsUiTfuDlCqiInd TfUiTfuDlCqiInd

#define YS_TIME_RES                1
#define YS_TTI_TMR_EVNT            10

#ifdef YS_LTE_PAL
/* TTI timer value for PAL here shall be in nano seconds directly
   Avoid multiply operation while generating the TTI 
   Always assign mapping in terms of milli seconds
1000000 -> 1ms TTI 
10000000-> 10ms TTI .. so on */
/* ys005.102 : MOD : Setting YS_TTI_TMR_VAL_CFG  */
#ifdef YS_ENB_CFG
extern U32 YS_TTI_TMR_VAL_CFG; /* ys004.102: ccpu00117531 TTI VALUE CONFIGURED */   
#define YS_TTI_TMR_VAL             YS_TTI_TMR_VAL_CFG /* ys004.102: ccpu00117531 */
#else
#define YS_TTI_TMR_VAL             10000000
#endif
/* ys005.102 : MOD_END : Setting YS_TTI_TMR_VAL_CFG  */
/* Adding TTI count - to generate as expected TTIs at one go
  This is required if TTI is set to larger value, say 5ms,
  the amount of TTI ticks generated shall be 5 all at one go
  to simulate 1ms tti generation environment 
  Always assign mapping this value with TTI TMR Value above
  YS_TTI_TMR_VAL   1000000 => YS_TTI_COUNT_VAL 1
  YS_TTI_TMR_VAL   2000000 => YS_TTI_COUNT_VAL 2
  YS_TTI_TMR_VAL   5000000 => YS_TTI_COUNT_VAL 5 ... so on */
#define YS_TTI_COUNT_VAL           1

/* Following cpucore value is applicable only for Linux machine
   (Calpella) from Intel. Core number used here can be changed
   accordingly, as expected on the machine of interest */
#define YS_TTI_CPUCORE_VAL         2
#define YS_RCVR_CPUCORE_VAL        2

#elif YS_PICO
#define YS_TTI_TMR_VAL             1
#endif

#define YS_NUM_PHY_CELLS           3
#define YS_NUM_LOG_CELLS           504

#define YS_NUM_SFN                 1024
#define YS_NUM_SUB_FRAMES          10

/* Changing from 4096 to 1500 to align with max bucket-max packet size */
#define YS_MEM_SDU_SIZE            1500 

#define YS_CPY_DL_PDCCH            1 
#define YS_CPY_UL_PDCCH_HI         2 
#define YS_CPY_DL_UL_BOTH          3 

#define YS_NUM_PRACH_TDD_CFG       64
#define YS_NUM_PRACH_FDD_CFG       64
#define YS_NUM_PRACH_TDD_MAP       64
#define YS_NUM_PRACH_PRES_ARR      20
#define YS_ODD_SF_OFFSET           10
#define YS_NUM_TDD_SF_CFG          7
#define YS_NUM_CFG_PER_PRACH_CFG   7

#define YS_NUM_PRACH_FDD_CFG       64

#define YS_NUM_SR_CFG              155
#ifndef YS_MIN_SR_FREQ
#define YS_MIN_SR_FREQ             40
#endif
#ifndef YS_MAX_SR_FREQ
#define YS_MAX_SR_FREQ             40
#endif

#define YS_NUM_SRS_CFG              637
#ifndef YS_MIN_SRS_FREQ
#define YS_MIN_SRS_FREQ             40
#endif
#ifndef YS_MAX_SRS_FREQ
#define YS_MAX_SRS_FREQ             40
#endif

#define YS_SR_PERIOD_5             5
#define YS_SR_PERIOD_10            10
#define YS_SR_PERIOD_20            20
#define YS_SR_PERIOD_40            40
#define YS_SR_PERIOD_80            80

#ifdef LTE_TDD
#define YS_NUM_CQI_CFG             316
#else
#define YS_NUM_CQI_CFG             542
#endif

#ifdef LTEMAC_MIMO
#define YS_NUM_RI_CFG             1023
#ifndef YS_MIN_M_RI
#define YS_MIN_M_RI               2 
#endif
#ifndef YS_MAX_M_RI
#define YS_MAX_M_RI               2
#endif
#endif


#ifndef YS_MIN_CQI_FREQ
#define YS_MIN_CQI_FREQ            40
#endif
#ifndef YS_MAX_CQI_FREQ
#define YS_MAX_CQI_FREQ            40
#endif

#define YS_CQI_PMI_PAYLOAD_SIZE    4
#define YS_NUM_TRANS_MODE          8

#define YS_CQI_PERIOD_1             1
#define YS_CQI_PERIOD_2             1
#define YS_CQI_PERIOD_5             5
#define YS_CQI_PERIOD_10            10
#define YS_CQI_PERIOD_20            20
#define YS_CQI_PERIOD_32            32
#define YS_CQI_PERIOD_40            40
#define YS_CQI_PERIOD_64            64
#define YS_CQI_PERIOD_80            80
#define YS_CQI_PERIOD_128           128
#define YS_CQI_PERIOD_160           160

#define YS_HARQ_SIZE               1

#define YS_PREAM_FRMT_NA           -1
#define YS_PREAM_FRMT_0            0
#define YS_PREAM_FRMT_1            1
#define YS_PREAM_FRMT_2            2
#define YS_PREAM_FRMT_3            3
#define YS_PREAM_FRMT_4            4

#define YS_DRA_NA                  -1
#define YS_DRA_0_POINT_5           0
#define YS_DRA_1                   1
#define YS_DRA_2                   2
#define YS_DRA_3                   3
#define YS_DRA_4                   4
#define YS_DRA_5                   5
#define YS_DRA_6                   6

#define YS_rRA_NA                  -1
#define YS_rRA_0                   0
#define YS_rRA_1                   1
#define YS_rRA_2                   2

#define YS_ALL_SFN                 0
#define YS_EVEN_SFN                1
#define YS_ODD_SFN                 2

#define YS_FREQ_RES_IDX_0          0
#define YS_FREQ_RES_IDX_1          1
#define YS_FREQ_RES_IDX_2          2

#define YS_PRACH_NOT_PRSNT         0x0
#define YS_PRACH_FREQ_IDX_0        0x1
#define YS_PRACH_FREQ_IDX_1        0x2
#define YS_PRACH_FREQ_IDX_2        0x4

#define YS_SF_0                    0
#define YS_SF_1                    1
#define YS_SF_2                    2
#define YS_SF_3                    3
#define YS_SF_4                    4
#define YS_SF_5                    5
#define YS_SF_6                    6
#define YS_SF_7                    7
#define YS_SF_8                    8
#define YS_SF_9                    9

#define YS_NUM_UES                 2
#define YS_DIR_UP                  1
#define YS_DIR_DOWN                2

#define YS_PDU_TYPE_ULSCH          0x01
#define YS_PDU_TYPE_CQI            0x02
#define YS_PDU_TYPE_HARQ           0x04
#define YS_PDU_TYPE_SR             0x08

#define YS_PMI_CFM_0               0
#define YS_PMI_CFM_1               1

#define YS_NDI_REP_DATA            0
#define YS_NDI_NEW_DATA            1

#define YS_PAG_RNTI                0xFFFE
#define YS_SI_RNTI                 0xFFFF
#define YS_MIN_RA_RNTI             1
#define YS_MAX_RA_RNTI             60

#define YS_TX_MODE_SISO            0
#define YS_TX_MODE_MIMO            1

#define YS_UL_PDU_ULSCH            0
#define YS_UL_PDU_ULSCH_CQI        1
#define YS_UL_PDU_ULSCH_HARQ       2
#define YS_UL_PDU_ULSCH_CQI_HARQ   3
#define YS_UL_PDU_UCI_CQI          4
#define YS_UL_PDU_UCI_SR           5
#define YS_UL_PDU_UCI_HARQ         6
#define YS_UL_PDU_UCI_SR_HARQ      7
#define YS_UL_PDU_UCI_CQI_HARQ     8
#define YS_UL_PDU_UCI_CQI_SR       9
#define YS_UL_PDU_UCI_HARQ_CQI_SR  10
#ifdef LTEMAC_MIMO
#define YS_UL_PDU_ULSCH_RI_HARQ   11
#define YS_UL_PDU_ULSCH_RI        12
#endif

#define YS_PUCCH_IDX_TYPE_1        0
#define YS_PUCCH_IDX_TYPE_2        1

#define YS_AN_MODE_BUND            0
#define YS_AN_MODE_MUX             1

#define YS_TQ_SIZE                 2

/* Read Init Params from CFG file */
#define YS_MAX_CFG_FILE_LINE_LEN  256
#define YS_MAX_CFG_PARAM_LEN      256
#define YS_IP_ADDR_STR_LEN        64
/* ys005.102 : Defined new macro */
#define YS_MAX_ENB_SUPP            5


/* LTE PAL specific hash defines */
#ifdef YS_LTE_PAL   

#define YS_SELECTOR_LC             0
#define YS_SELECTOR_TC             1

#define YS_NUM_MSG_INFO            10

#ifndef YS_DST_PROCID
#ifdef LTE_PAL_ENB
#define YS_DST_PROCID              2
#else
#define YS_DST_PROCID              0
#endif
#endif

#ifndef SS_CAVIUM

/* Read Init Params from CFG file */

/* exceptionally adding extern declaration in ".h" file
 * for supporting file based configuation of some params
 * with less changes to code
 */
/* ys005.102 :  Multiple eNodeB support changes */
#ifdef YS_ENB_CFG
extern U16  YS_PORT_ENB;
extern U16  YS_PORT_UE;
extern U8  YS_IP_ADDR_ENB[];
extern U8  YS_IP_ADDR_UE[];
#else
extern U16  YS_PORT_ENB[YS_MAX_ENB_SUPP];
extern U16  YS_PORT_UE;
extern U8  YS_IP_ADDR_ENB[YS_MAX_ENB_SUPP][YS_IP_ADDR_STR_LEN];
extern U8  YS_IP_ADDR_UE[YS_IP_ADDR_STR_LEN];
#endif

#define YS_MAX_RCVD_BUF_LEN        100000

#ifdef YS_WIRESHARK_LOG
/* radioType */
#define FDD_RADIO 1
#define TDD_RADIO 2

/* Direction */
#define DIRECTION_UPLINK   0
#define DIRECTION_DOWNLINK 1

/* rntiType */
#define NO_RNTI  0
#define P_RNTI   1
#define RA_RNTI  2
#define C_RNTI   3
#define SI_RNTI  4
#define SPS_RNTI 5

#define MAC_LTE_START_STRING        "mac-lte"
#define MAC_LTE_RNTI_TAG            0x02
#define MAC_LTE_UEID_TAG            0x03
#define MAC_LTE_SUBFRAME_TAG        0x04
#define MAC_LTE_PREDFINED_DATA_TAG  0x05
#define MAC_LTE_RETX_TAG            0x06
#define MAC_LTE_CRC_STATUS_TAG      0x07
#define MAC_LTE_PAYLOAD_TAG         0x01

/* ys005.102: Wireshark changes */
extern U8  WIRESHARK_SRVR_IP_ADDR[]; 
#endif /* YS_WIRESHARK_LOG */
#endif /* SS_CAVIUM */

#endif /* YS_LTE_PAL */

#ifdef WIRESHARK_LOG
#endif


/* ys005.102: Added two new macros */
#define YS_CTF_MINOR_RECFG  0
#define YS_CTF_MAJOR_RECFG  1


#define YS_FREE_SDU(_sdu) \
{\
   if (_sdu != NULLP) \
   {\
      cmFreeMem ((Ptr)(_sdu));\
      _sdu = NULLP;\
   }\
}

#define YS_GET_BUF(_buf, _ret) \
{ \
   _ret = SGetMsg(ysCb.ysInit.region, ysCb.ysInit.pool, &(_buf));  \
}

#define YS_FREE_BUF(_buf) \
{ \
   if (_buf != NULLP) \
   {\
      SPutMsg (_buf); \
      _buf = NULLP; \
   }\
}

#define YS_INCR_TIMING_INFO(_timingInfo, _delta)                             \
{                                                                            \
   if ((_timingInfo.subframe + _delta) > (YS_NUM_SUB_FRAMES - 1))            \
      _timingInfo.sfn = ((_timingInfo.sfn + 1) % YS_NUM_SFN);                \
   _timingInfo.subframe = ((_timingInfo.subframe + _delta) %                 \
                              YS_NUM_SUB_FRAMES);                            \
}

#define YS_DECR_TIMING_INFO(_timingInfo, _delta)                              \
{                                                                            \
   if (_timingInfo.subframe  >= _delta)                                       \
   {                                                                         \
      _timingInfo.subframe = ((_timingInfo.subframe - _delta) %               \
                                      YS_NUM_SUB_FRAMES);                    \
   }                                                                         \
   else                                                                      \
   {                                                                         \
       _timingInfo.sfn = (_timingInfo.sfn < 1) ?                             \
                               (YS_NUM_SFN - (1 - _timingInfo.sfn)) :        \
                               (_timingInfo.sfn - 1);                        \
      _timingInfo.subframe = (YS_NUM_SUB_FRAMES -                            \
                           (_delta - (_timingInfo.subframe)) %               \
                            YS_NUM_SUB_FRAMES);                              \
   }                                                                         \
}

#define YS_CONVERT_STR4_TO_INT(_int, _str)         \
{                                                  \
   U16 _tmp16;              /* temporary value */  \
   _tmp16 = 0;                                     \
   _tmp16 = (U16) PutHiByte(_tmp16, (U8) _str[3]); \
   _tmp16 = (U16) PutLoByte(_tmp16, (U8) _str[2]); \
   _int =   (U32) PutHiWord(_int, (U16) _tmp16);   \
   _tmp16 = (U16) PutHiByte(_tmp16, (U8) _str[1]); \
   _tmp16 = (U16) PutLoByte(_tmp16, (U8) _str[0]); \
   _int =   (U32) PutLoWord(_int, (U16) _tmp16);   \
}

#define YS_CALCULATE_HARQ_N_P(_nRB, _p, _Np)       \
{                                                  \
   S32   _temp;                                    \
   _Np = (_temp = ((_nRB * (12 * (_p) - 4)) / 36)) < 0 ? 0 : (U8)_temp;  \
}

#define YS_CALCULATE_n_1_PUCCH_i(_M, _i, _Np, _Np1, _nCCEi, _n1PUCCH, _n1PUUCHi) \
{                                                                            \
   _n1PUUCHi = (((_M - _i - 1) * _Np) + (_i * _Np1) + _nCCEi + _n1PUCCH);    \
}

#define YS_GET_DL_BW(_cfg)         \
((_cfg.dlBw == CTF_BW_RB_6) ?  6 :    \
 (_cfg.dlBw == CTF_BW_RB_15) ? 15 :   \
 (_cfg.dlBw == CTF_BW_RB_25) ? 25 :   \
 (_cfg.dlBw == CTF_BW_RB_50) ? 50 :   \
 (_cfg.dlBw == CTF_BW_RB_75) ? 75 : 100 )

#define YS_GET_UL_BW(_cfg)         \
((_cfg.ulBw == CTF_BW_RB_6) ?  6 :    \
 (_cfg.ulBw == CTF_BW_RB_15) ? 15 :   \
 (_cfg.ulBw == CTF_BW_RB_25) ? 25 :   \
 (_cfg.ulBw == CTF_BW_RB_50) ? 50 :   \
 (_cfg.ulBw == CTF_BW_RB_75) ? 75 : 100 )

#include <sys/time.h>
/* ys004.102 : ccpu00117468 Removed Dummy Macro DEBUG_MSG() */
#define PRINT_TIME()\
{\
   struct timeval currTime;\
   cv_gettimeofday(&currTime);\
}


#ifdef SS_DIAG 
#define YS_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                                             \
   if(ysCb.ysInit.dbgMask & SS_DIAG_LVL0)                             \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTYS, ysCb.ysInit.inst, SS_DIAG_LVL0, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for CL error logs
 *  
*/
#define YS_DIAG_LVL1(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)            \
{                                                                 \
   if(ysCb.ysInit.dbgMask & SS_DIAG_LVL1)                             \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTYS, ysCb.ysInit.inst, SS_DIAG_LVL1, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for CL critical logs
 *  
*/
#define YS_DIAG_LVL2(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
   if(ysCb.ysInit.dbgMask & SS_DIAG_LVL2)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTYS, ysCb.ysInit.inst, SS_DIAG_LVL2, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for CL logs 
 *  
*/
#define YS_DIAG_LVL3(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(ysCb.ysInit.dbgMask & SS_DIAG_LVL3)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTYS, ysCb.ysInit.inst, SS_DIAG_LVL3, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for CL logs
 *  
*/
#define YS_DIAG_LVL4(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(ysCb.ysInit.dbgMask & SS_DIAG_LVL4)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTYS, ysCb.ysInit.inst, SS_DIAG_LVL4, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}
#else
#define YS_DIAG_LVL0(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        
#define YS_DIAG_LVL1(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        
#define YS_DIAG_LVL2(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        
#define YS_DIAG_LVL3(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        
#define YS_DIAG_LVL4(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        
#endif

#define YS_PAL_MAX_CELLS 2

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __YS_H__ */

/********************************************************************30**
  
         End of file:     ys.h@@/main/2 - Thu Dec  2 02:27:12 2010
  
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**

     ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2     ys004.102 ms                   1. TTI value configured.
                      sbalakrishna          2. Removed definition and call to dummy macro
                                              DEBUG_MSG.
/main/2     ys005.102  pbyadgi              1. wireshark changes.
                                            2. Added new Macro.
*********************************************************************91*/
