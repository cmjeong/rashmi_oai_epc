

/**********************************************************************
 
    Name:   LTE UE Simulator
 
    Type:   C include file
 
    Desc:   Defines required by LTE UE Simulator
 
    File:   ue.h
 
    Sid:      ue.h@@/main/1 - Sun Mar 28 22:59:20 2010
 
    Prg:    vp
 
**********************************************************************/
 
 
#ifndef __UEH__
#define __UEH__


#define UE_CR_TMR                   1
#define UE_MAX_TMR                  2
/* ue003.101: Added for TA feature */
#ifdef TA_NEW
#define UE_MAC_TA_MAX_TMR           10240 /* Time Alignment Timer */
#define UE_MAC_TA_CHNG_TMR          1000  /* Custom timer to bring change in Residual timer value */
#define UE_MAC_TA_APPLY_TMR         6     /* TA command received at n and applied at n+UE_MAC_TA_APPLY_TMR */ 
#define UE_MAX_TMR_Q                3
#define UE_MAC_EVNT_TA_MAX_TMR           1 /* Time Alignment Timer */
#define UE_MAC_EVNT_TA_CHNG_TMR          2 /* Custom timer to bring change in Residual timer value */
#define UE_MAC_EVNT_TA_APPLY_TMR         3 /* TA command received at n and applied at n+UE_MAC_TA_APPLY_TMR */ 
#endif

#define UE_MAC_MAX_NUM_DED_LC       10 /*max dedicated logical channels in UE*/
#define UE_MAC_CON_RES_ID_SZ        6
#define UE_MAC_RAR_SDU_SZ           6
#define UE_MAC_BSR_SIZE             4

/* DUX related macros */
#define UE_MAC_LCID_MASK            0x1F
#define UE_MAC_LCID_LEN             0x5
#define UE_MAC_CCCH_LCID            0x00
#define UE_MAC_DEDLC_MIN_LCID       0x01
#define UE_MAC_DEDLC_MAX_LCID       0x0A
#define UE_MAC_RES_MIN_LCID         0x0B
#define UE_MAC_RES_MAX_LCID         0x19
#define UE_MAC_PHR_LCID             0x1A
#define UE_MAC_CRNTI_LCID           0X1B
#define UE_MAC_TRUNC_BSR_LCID       0X1C
#define UE_MAC_SHORT_BSR_LCID       0X1D
#define UE_MAC_LONG_BSR_LCID        0X1E
#define UE_MAC_PAD_LCID             0x1F
#define UE_MAC_MAX_EXTN_PAD_SUBHDRS 0x02
#define UE_MAC_SUBHDR_EXT_MASK    0x20
#define UE_MAC_MIN_PDU_SIZE       2
#define UE_MAC_PAD_SUBHDR            (UE_MAC_PAD_LCID | UE_MAC_SUBHDR_EXT_MASK)
#define UE_SIM_MAX_SUBHDRS     50

#define UE_MAC_SI_RNTI            65535
#define UE_MAC_P_RNTI             65534

#define UE_MAC_CRNTI_CE_TX         (1<<0)
#define UE_MAC_PHR_CE_TX           (1<<1)
#define UE_MAC_TRUNC_BSR_CE_TX     (1<<2)
#define UE_MAC_SHORT_BSR_CE_TX     (1<<3)
#define UE_MAC_LONG_BSR_CE_TX      (1<<4)

/* ue008.101: Changed the value from 103 to 60*/
#define UE_MAC_MAX_RARNTI         60


#define UE_MAC_MAX_PDU_SUB_HDR_LEN 3
#define UE_MAC_CONT_RES_LCID       0x1C
#define UE_MAC_TA_LCID             0x1D

#define UE_MAC_SDU_SUB_HDR_LEN_EXC_LEN_FIELD     0x1
#define UE_MAC_LAST_SDU_SUB_HDR_LEN              0x1
#define UE_MAC_CE_SUB_HDR_LEN                    0x1

#define UE_MAC_SHORT_BSR_ELM_LEN   0x1
#define UE_MAC_SHORT_BSR_LEN       UE_MAC_CE_SUB_HDR_LEN+UE_MAC_SHORT_BSR_ELM_LEN

#define UE_MAC_TRUNC_BSR_ELM_LEN   0x1
#define UE_MAC_TRUNC_BSR_LEN       UE_MAC_CE_SUB_HDR_LEN+UE_MAC_TRUNC_BSR_ELM_LEN

#define UE_MAC_LONG_BSR_ELM_LEN    0x3
#define UE_MAC_LONG_BSR_LEN        UE_MAC_CE_SUB_HDR_LEN+UE_MAC_LONG_BSR_ELM_LEN

#define UE_MAC_CRNTI_ELM_LEN       0x2
#define UE_MAC_CRNTI_LEN           UE_MAC_CE_SUB_HDR_LEN+UE_MAC_CRNTI_ELM_LEN

#define UE_MAC_PHR_ELM_LEN         0x1
#define UE_MAC_PHR_LEN             UE_MAC_CE_SUB_HDR_LEN+UE_MAC_PHR_ELM_LEN

#define UE_MAC_MAX_PAD_ARR_SZ      100
#define UE_MAC_PAD_BYTE            0x00
#define UE_MAC_NUM_IMCS            29
#define UE_MAC_NUM_ITBS            27
#define UE_MAC_MAX_BSR_INDEX       64 
#define UE_MAC_MAX_NUM_RB          110

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
/* Define for the block size for memory allocation */
#define UE_MAC_BLKSZ               2048
#define UE_RRC_BLKSZ               5108

#define UE_REGION                  0
#define UE_POOL                    0

#define UE_MAC_HDR_SZ_INC_BSR   UE_MAC_SHORT_BSR_LEN+UE_MAC_LAST_SDU_SUB_HDR_LEN
#define UE_MAC_HDR_SZ           UE_MAC_LAST_SDU_SUB_HDR_LEN
#define UE_MAC_HDR_SZ_INC_LEN(_len)   UE_MAC_LAST_SDU_SUB_HDR_LEN+_len

/* ue002.101: Additional defines for performance path */
#define UE_NUM_PER_CELL            1
#define UE_MAX_PREAMBLE            6 
#define UE_NUM_CELL                4
#define UE_CELL_ID                 1

#define  UE_MAX_BW                 100   /* Band width in Mhz */

/* Total UL Load in 10 ms:  */
#define  UE_MAX_SDU_SIZE           1450
#define  UE_MAX_NO_SDUS            3 

#define UEMAXBUFLEN                10000
/* ue008.101: Changed the value from 104 to (UE_MAC_MAX_RARNTI + 1) */
#define UE_CELL_RNTI_SPACE_DIFF    000
#define UE_START_RNTI              (UE_MAC_MAX_RARNTI + 1) 

/* ue002.101: Removed unnecessary defines */
#define MAX_SUBFRAMES              10
#define MAX_SFN                    1024

#define UE_RLC_MAX_AM_SEQ          1024 
#define UE_RLC_MAX_UM_SEQ          1024 
/* ue003.101: increased from 4 */
#define UE_NUM_RLC_RB_PER_UE       5

#define UE_PDCP_MAX_DRB_AM_SEQ     4096  
#define UE_PDCP_MAX_DRB_UM_SEQ     4096 
#define UE_PDCP_MAX_SRB_AM_SEQ     32    
#define UE_RLC_MIN_HDR_LEN         2 
#define UE_RLC_ACK_PDU_SZ          2  

/* Following are the UE states- not used  */
#define NO_UL_TRANSFER             0
#define SR_TO_BE_SENT              1
#define BSR_TO_BE_SENT             2
#define DATA_TO_BE_SENT            3

#define NUM_MAC_LC_PER_UE          1 

/* UEs capable of uplink data transfer  */
#define UL_DATA_MIN_RNTI           10
#define UL_DATA_MAX_RNTI           13

/* Following shall be used as message types for internal processing  */
#define RAR_PDU                    50
#define RRC_CONN_SETUP             51
#define RRC_SEC_MODE               52
#define RRC_CONN_RECFG             53

/* ue008.101: Added new macro UE_HO_IN_PROGRESS */
#define UE_HO_IN_PROGRESS         1

/* eNB shall send EVTDRBCFG to indicate the completion of DRB configuration at eNB */
#define EVTLTFDRBCFG               99

#define UE_NUM_UL_PKT              5000

#define UE_RLC_BYTE_LEN            8

#define UE_RLC_DC_LEN              1
#define UE_RLC_RF_LEN              1
#define UE_RLC_P_LEN               1
#define UE_RLC_FI_LEN              2
#define UE_RLC_E_LEN               1
#define UE_RLC_SN_LEN              10
#define UE_RLC_LSF_LEN             1
#define UE_RLC_SO_LEN              15
#define UE_RLC_LI_LEN              11

#define UE_RLC_MAX_LI              50

#define UE_RLC_FI_FIRST_SEG        0x02
#define UE_RLC_FI_LAST_SEG         0x01

#define UE_RLC_STATUS_PDU          0x00
#define UE_RLC_DATA_PDU            0x01

#define UE_RLC_SEGMENT_PDU         0x01
#define UE_RLC_AM_HDR_LEN          0x02
#define UE_RLC_UM_HDR_LEN          0x02

#define UE_PDCP_MACI_LEN           0x04

#define UE_LC_SRB0                 0x00
#define UE_LC_SRB1                 0x01
#define UE_LC_SRB2                 0x02
#define UE_LC_DRB1                 0x03
/* ue003.101: Added dedicated bearer support */
#define UE_LC_DRB2                 0x04

#define UE_MAX_RB                  0x05

/* ue003.101: Added paging feature */
#define UE_STATE_NOT_READY              0x00
#define UE_STATE_SIGNALLING_COMPLETED   0x01
#define UE_STATE_DATA_READY             0x02

/* ue002.101: Additional defines for UL performance path */
#define UE_SDU_SIZE                1500

#define UE_STATE_NOT_READY              0x00
#define UE_STATE_SIGNALLING_COMPLETED   0x01
#define UE_STATE_DATA_READY             0x02

#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 *  depends on the RRC timer. */
/*RRC TIMER START*/
#define UE_RRC_RECONFIG_TMR     1
#define UE_RRC_REEST_TMR        2
#define UE_RRC_SECUCMD_TMR      3
#define UE_RRC_CAPENQ_TMR       4
#define UE_RRC_CONREL_TMR       5
#define UE_RRC_CONSETUP_TMR     6
/*RRC TIMER STOP*/
#endif
/** @def nhumsgcat NHU Message Category */
#define NHU_MSG_DLDCCH             0x01 /* DL-DCCH message */
#define NHU_MSG_ULDCCH             0x02 /* UL-DCCH message */
#define NHU_MSG_DLCCCH             0x03 /* DL-CCCH message */
#define NHU_MSG_ULCCCH             0x04 /* UL-CCCH message */
#define NHU_MSG_DLPCCH             0x05 /* DL-PCCH message */
#define NHU_MSG_DLBCCHBCH          0x06 /* BCCH on BCH message */
#define NHU_MSG_DLBCCHDLSCH        0x07 /* BCCH on DL-SCH message */

#define UE_NH_MEM_PDU_SIZE         5108

/* ue002.101: Additional defines for performance */
#define UE_NUM_SUB_FRAMES          10
#define UE_NUM_SFN                 1024

/* ue002.101: Additional defines for TDD support */
#define LTE_TDD_CFG_TYPE_0         0
#define LTE_TDD_CFG_TYPE_1         1
#define LTE_TDD_CFG_TYPE_2         2
#define LTE_TDD_CFG_TYPE_3         3
#define LTE_TDD_CFG_TYPE_4         4
#define LTE_TDD_CFG_TYPE_5         5
#define LTE_TDD_CFG_TYPE_6         6

#define UE_LYR_NAME     "LTE-UE-SIMULATOR"

#define UEDBGP()\

#define UE_RRC_FREE_EVNT(_evntPtr)       \
{                                      \
      cmFreeMem((_evntPtr));              \
      (_evntPtr) = NULLP;                 \
}

#define RGADDTOCRNTTIME(crntTime, toFill, incr)          \
   if ((crntTime.subframe + incr) > (MAX_SUBFRAMES - 1))   \
      toFill.sfn = (crntTime.sfn + 1) % MAX_SFN;      \
   else                                                  \
      toFill.sfn = crntTime.sfn;                              \
   toFill.subframe = (crntTime.subframe + incr) % MAX_SUBFRAMES;

#define UE_INCR_TIMING_INFO(_timingInfo, _delta)                             \
{                                                                            \
   if ((_timingInfo.subframe + _delta) > (9))            \
      _timingInfo.sfn = ((_timingInfo.sfn + 1) % TF_NUM_SFN);                \
   _timingInfo.subframe = ((_timingInfo.subframe + _delta) %                 \
                              TF_NUM_SUB_FRAMES);                            \
}

#define UE_ALLOC(_buf, _size)\
{\
   if (SGetSBuf(UE_REGION, UE_POOL, (Data **)&_buf,      \
                (Size) _size) == ROK)                                \
   {                                                                 \
      cmMemset((U8 *)(_buf), 0, _size);                             \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (_buf) = NULLP;                                               \
   }                                                                \
}

#define UE_ALLOC_BUF(_buf)\
{\
   if (SGetMsg(UE_REGION, 3, (Buffer **)&_buf) != ROK) \
   {                                                       \
      (_buf) = NULLP;                                      \
   }                                                       \
}


#define UE_ALLOCEVNT(_evntPtr, _size, _mem)           \
do                                                    \
{                                                     \
   (*_evntPtr) = NULLP;                               \
   (Void)cmAllocEvnt((Size) _size, UE_NH_MEM_PDU_SIZE,\
                     _mem, (Ptr *)_evntPtr);                \
}                                                     \
while(0)

#define UE_GET_MEM(_memPtr, _size, _allocPtr)               \
{                                                              \
   (*_allocPtr) = NULLP;                                       \
   (Void)cmGetMem(_memPtr, _size, (Ptr *)_allocPtr);           \
}

#define UE_FREE_BUF(_buf)\
{\
    if (_buf != NULLP)                                      \
   {                                                       \
      SPutMsg(_buf);                                       \
   }                                                       \
   _buf = NULLP;                                           \
}

#define UE_FREE(_buf, _size)\
{\
    if (_buf != NULLP)                                               \
   {                                                                 \
      (Void) SPutSBuf(UE_REGION, UE_POOL,                            \
            (Data *) _buf, (Size) _size);                            \
      _buf = NULLP;                                                  \
   }                                                                 \
}

/* ue002.101: Additional defines for RLC UM mode support */
#define UE_ADD_PRE_MSG(_pduPtr,_liValue, _liSize)\
{\
   Data liByte;\
   U16  sze;\
   sze = 0;\
   while (_liSize > sze )\
   {\
   liByte = (U8) (_liValue >> (8*sze));\
   SAddPreMsg((Data )liByte, _pduPtr);\
   sze++;\
   }\
}

#define UE_ADD_RLC_HDR(pdu, rbCb, fi, liCnt)                       \
{                                                                  \
   U8    data[2] = {0,0};                                          \
   U8    e  = 0;                                                   \
   S8    count1  = 0;                                               \
   U16   li = UE_SDU_SIZE;                                         \
   U16   li1 = UE_SDU_SIZE;                                        \
   U16   ackData = rbCb->cur_am_seq;                               \
   if ( liCnt % 2 == 1 )                                           \
   {                                                               \
      U16 liData;                                                  \
      liData = li << 4;                                            \
      UE_ADD_PRE_MSG(pdu,liData,2);                                \
      liCnt--;                                                     \
      e = 1;                                                       \
   }                                                               \
   for ( count1 = liCnt - 1;count1 >= 0;count1 = count1 -2 )       \
   {                                                               \
      U32 liData = li | ( e << 11);                                \
                                                                   \
      li1 |= (1<<11);                                              \
      liData |= (li1 << 12);                                       \
                                                                   \
      UE_ADD_PRE_MSG(pdu,liData,3);                                \
      e = 1;                                                       \
   }                                                               \
   data[1] = (U8)(ackData>>8);                                     \
   data[0] = (U8)(ackData & 0xFF);                                 \
   data[1] |= ( fi << 3);                                          \
   data[1] |= ( e << 2);                                          \
   data[1] |= 0x80;                                                \
   SAddPreMsgMult(&data[0], 2, pdu);                               \
}

/* ue002.101: Additional defines for RLC UM mode support */
#ifdef UE_SUPPORT_RLC_UM_MODE
#define UE_ADD_RLC_UM_HDR(pdu, rbCb, fi)                           \
{                                                                  \
   U16   ackData = rbCb->cur_um_seq;                               \
   U8    data[2] = {0,0};                                          \
   data[1] = (U8)(ackData>>8);                                     \
   data[0] = (U8)(ackData & 0xFF);                                 \
   data[1] |= ( fi << 3);                                          \
   data[1] |= 0x00;                                                \
   SAddPreMsgMult(&data[0], 2, pdu);                               \
}
#endif



/**********************************************************************/
/* ue003.101: For DEBUGP support */
#define UE_PRNTBUF   ueAppCellCb.init.prntBuf

#define UE_DBGMASK_MEM     (DBGMASK_LYR << 0)
#define UE_DBGMASK_TRC     (DBGMASK_LYR << 1)
#define UE_DBGMASK_ERROR   (DBGMASK_LYR << 2)
#define UE_DBGMASK_INFO    (DBGMASK_LYR << 3)

/*-- Different memory types --*/
#define UE_MEMTYPE_EVNT  1
#define UE_MEMTYPE_MSG   2
#define UE_TYPE_BUF  3

/*-- Different memory modes --*/
#define UE_MEMMODE_ALLOC 1
#define UE_MEMMODE_FREE  2
#define UE_MEMMODE_SEND  3
#define UE_MEMMODE_RCV   4

/* ue002.101: Additional defines for MSPD CL support */
#define UE_NUM_SR_CFG              155
#define UE_NUM_SRS_CFG             637
#define UE_NUM_CQI_CFG             414
#define UE_NUM_RI_CFG              965
#ifdef YS_MSPD
#define UE_MEM_SDU_SIZE            2048
/* Read Init Params from CFG file */
#define YS_MAX_CFG_FILE_LINE_LEN  256
#define YS_MAX_CFG_PARAM_LEN      256
#define YS_IP_ADDR_STR_LEN        64
#endif

#if 0
/* macro to print buffer 
*/
#define UESIMPRNT(_init, _prntBuf)     \
{                                      \
   sprintf _prntBuf;                   \
   SPrint(_init.prntBuf);              \
}

/* macro to get and print timestamp value */
#ifdef UEP_PRNT_TIMESTAMP
#define UE_PRNTTIMESTAMP(_init)                                      \
{                                                                       \
   S8 _buf[60];                                                         \
   (Void) SGetTimeStamp(_buf);                                          \
   UESIMPRNT(_init, (_init.prntBuf, "[%s]:", _buf));                    \
}
#else
#define UE_PRNTTIMESTAMP(_init)
#endif

/* macro to print layer Name */
#define UE_PRNT_LAYER(_init, _lyr)                                   \
{                                                                       \
   UESIMPRNT(_init, (_init.prntBuf, " [%s 0x%x:%x]", _lyr,              \
         _init.ent, _init.inst));                                       \
}

/* macro to print filename, line number and function name */
#define UE_PRNT_FILE_LINE_FUNC(_init)                                     \
{                                                                       \
   UESIMPRNT(_init, (_init.prntBuf, " [%s:%d:%s]",__FILE__,__LINE__, __tapa_fun)); \
}
/* macro to print filename, line number  */
#define UE_PRNT_FILE_LINE(_init)                                     \
{                                                                       \
   UESIMPRNT(_init, (_init.prntBuf, " [%s:%d]",__FILE__,__LINE__)); \
}
/* macro to collect print all the information */
#define UE_DBG(_init, _lyr, _mask, _arg, _lvl)                 \
do                                                                \
{                                                                 \
   if(_init.dbgMask & (_mask))                                    \
   {                                                              \
      UE_PRNTTIMESTAMP(_init)                                  \
      UE_PRNT_LAYER(_init, _lyr)                               \
      UE_PRNT_FILE_LINE(_init)                                 \
      UESIMPRNT(_init, (_init.prntBuf, " [" #_lvl "]" ));         \
      UESIMPRNT(_init, (_init.prntBuf, " : "));                   \
      UESIMPRNT(_init, _arg);                                     \
      UESIMPRNT(_init, (_init.prntBuf, "\n"));                    \
   }                                                              \
} while (0)

/* Debug macros for different debug levels */
#define UE_DBG_INFO(_init, _layerName, _mask, _arg)\
   UE_DBG(_init, _layerName, _mask, _arg, "INFO")

#define UE_DBG_ERROR(_init, _layerName, _mask, _arg)\
   UE_DBG(_init, _layerName, _mask, _arg, "ERROR")

/* Debug prints for MME */
#define UE_DBGP_INFO(_arg) \
   UE_DBG_INFO(ueAppCellCb.init, UE_LYR_NAME, UE_DBGMASK_INFO, _arg)

#define UE_DBGP_ERROR(_arg) \
   UE_DBG_ERROR(ueAppCellCb.init, UE_LYR_NAME, UE_DBGMASK_ERROR, _arg)

/*-------------------------Memory Debug Prints------------------------*/
#ifdef ALIGN_64BIT
#define UE_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)     \
{                                                                       \
   if (_init.dbgMask & (UE_DBGMASK_MEM))                               \
   {                                                                    \
      UE_PRNTTIMESTAMP                                               \
      UE_PRNT_LAYER(_init, _lyr)                                     \
      UE_PRNT_FILE_LINE(_init)                                       \
      UESIMPRNT(_init, (_init.prntBuf, " [ MEM  : %d %d %p %d]\n",      \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));            \
   }                                                                    \
}
#else
#define UE_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)     \
{                                                                       \
   if (_init.dbgMask & (UE_DBGMASK_MEM))                               \
   {                                                                    \
      UE_PRNTTIMESTAMP(_init)                                        \
      UE_PRNT_LAYER(_init, _lyr)                                     \
      UE_PRNT_FILE_LINE(_init)                                       \
      UESIMPRNT(_init, (_init.prntBuf, " [ MEM  : %d %d %p %ld]\n",     \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));            \
   }                                                                    \
}
#endif /*ALIGN_64BIT */

/*------------------------- Trace Prints------------------------*/

/* Trace for Utilities / General Code */
/* Note: For now the common places, ueAppCellCb is used presently.
 * Take care in the process of segregation of code.*/
#define UE_TRC2(_arg)                                                \
Txt __tapa_fun[PRNTSZE];                                                \
sprintf(__tapa_fun,#_arg);                                              \
{                                                                       \
   if (ueAppCellCb.init.dbgMask & (UE_DBGMASK_TRC))                        \
   {                                                                    \
      UE_PRNTTIMESTAMP(ueAppCellCb.init)                                 \
      UE_PRNT_LAYER(ueAppCellCb.init, UE_LYR_NAME)                    \
      UE_PRNT_FILE_LINE_FUNC(ueAppCellCb.init)                           \
      UESIMPRNT(ueAppCellCb.init, (ueAppCellCb.init.prntBuf," Entering\n"));    \
      TRC2(_arg);                                                       \
   }                                                                    \
}

#define UE_TRC3(_arg)                                                \
Txt __tapa_fun[PRNTSZE];                                                \
sprintf(__tapa_fun,#_arg);                                              \
{                                                                       \
   if (ueAppCellCb.init.dbgMask & (UE_DBGMASK_TRC))                        \
   {                                                                    \
      UE_PRNTTIMESTAMP(ueAppCellCb.init)                                 \
      UE_PRNT_LAYER(ueAppCellCb.init, UE_LYR_NAME)                    \
      UE_PRNT_FILE_LINE_FUNC(ueAppCellCb.init)                           \
      UESIMPRNT(ueAppCellCb.init, (ueAppCellCb.init.prntBuf," Entering\n"));    \
      TRC3(_arg);                                                       \
   }                                                                    \
}

#define UE_RETVOID                                                   \
do                                                                      \
{                                                                       \
   if (ueAppCellCb.init.dbgMask & (UE_DBGMASK_TRC))                        \
   {                                                                    \
      UE_PRNTTIMESTAMP(ueAppCellCb.init)                                 \
      UE_PRNT_LAYER(ueAppCellCb.init,  UE_LYR_NAME)                      \
      UE_PRNT_FILE_LINE(ueAppCellCb.init)                                \
      UESIMPRNT(ueAppCellCb.init, (ueAppCellCb.init.prntBuf, " Exiting\n"));    \
   }                                                                    \
   RETVOID;                                                             \
}while(0)

#define UE_RETVALUE(_arg)                                            \
{                                                                       \
   if (ueAppCellCb.init.dbgMask & (UE_DBGMASK_TRC))                        \
   {                                                                    \
      UE_PRNTTIMESTAMP(ueAppCellCb.init)                                 \
      UE_PRNT_LAYER(ueAppCellCb.init,  UE_LYR_NAME)                      \
      UE_PRNT_FILE_LINE(ueAppCellCb.init)                                \
      UESIMPRNT(ueAppCellCb.init, (ueAppCellCb.init.prntBuf, " Exiting\n"));    \
   }                                                                    \
   RETVALUE(_arg);                                                      \
}

#else /* DEBUGP */

/* macro to get and print timestamp value */
#define UE_PRNTTIMESTAMP(_init)

/* macro to print layer Name */
#define UE_PRNT_LAYER(_init, _lyr)

/* macro to print filename, line number and function name */
#define UE_PRNT_FILE_LINE(_init)

/* macro to collect print all the information */
#define UE_DBG(_init, _lyr, _mask, _arg, _lvl)

/* Debug macros for different debug levels */
#define UE_DBG_INFO(_init, _layerName, _mask, _arg)
#define UE_DBG_ERROR(_init, _layerName, _lyr, _arg)

/* Debug prints for MME */
#define UE_DBGP_INFO(_arg)
#define UE_DBGP_ERROR(_arg)

/*-------------------------Memory Debug Prints------------------------*/
#ifdef ALIGN_64BIT
#define UE_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)
#else
#define UE_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)
#endif
/*------------------------- Trace Prints------------------------*/
#define UE_TRC2(_arg)
#define UE_TRC3(_arg)

#define UE_RETVOID         RETVOID
#define UE_RETVALUE(_arg)  RETVALUE(_arg)

#endif /* DEBUGP */


#if (ERRCLASS & ERRCLS_INT_PAR)

#define UELOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(ueSimAppCb.init.ent, ueSimAppCb.init.inst, ueSimAppCb.init.procId, \
                   __FILE__, __LINE__, errCls, errCode, errVal, errDesc)
#else
#define UELOGERROR(errCls, errCode, errVal, errDesc)  
#endif
#endif
/**********************************************************************
         End of file:     ue.h@@/main/1 - Sun Mar 28 22:59:20 2010
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rr        1. Initial Release
/main/1+    ue002.101 sv        1. Multi ue support changes.
                                2. Changes to support MSPD CL. 
                                3. Changes to support RLC UM mode functionality. 
/main/1+    ue003.101 rp        1. Added dedicated bearer support.
                                2. Added TA, SI features.
/main/1+    ue008.101 ragrawal  1. Changed the value of macro UE_MAC_MAX_RARNTI
                                   and UE_START_RNTI.
                                2. Added new macro UE_HO_IN_PROGRESS.
/main/1+    ue009.101 akaranth  1. Added  feature to drop diffrent RRC messages to depends
                                   on the RRC timer.
*********************************************************************91*/

