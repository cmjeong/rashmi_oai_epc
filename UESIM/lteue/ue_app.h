

/**********************************************************************
 
    Name:   
 
    Type:   C include file
 
    Desc:  
 
    File:   ue_app.h
 
    Sid:      ue_app.h@@/main/1 - Sun Mar 28 22:59:20 2010
 
    Prg:
 
**********************************************************************/


#ifndef __UE_APPH__
#define __UE_APPH__


#define UE_APP_TQSIZE   10

#define UE_APP_CR_TMR     1
#define UE_APP_DETACH_TMR  2
#define UE_APP_CR_TMR_VAL 50
/* ue003.101: Added timers for dedicated bearer establishment */
#define UE_APP_BR_RES_TMR     3
#define UE_APP_BR_RES_TMR_VAL     30
/*ue006.101: Fix for CID:1465-02-01, DefectId:ccpu00116336.
  Removing the compiler warning.*/

/*-- ue008.101: Switch for invoking multi-Attach/Detach --*/

#define MULTI_ATTACH_DETACH 0

#if MULTI_ATTACH_DETACH 
#define UE_APP_DATA_DETACH_TMR_VAL 30
#else
#define UE_APP_DATA_DETACH_TMR_VAL 5
#endif

/* ue007.101: Support for Multiple attach timer */
#define UE_APP_MULT_ATTACH_TMR     4

/*-- ue008.101: Switch for invoking multi-Attach/Detach --*/
#if MULTI_ATTACH_DETACH
#define UE_APP_MULT_ATTACH_VAL     50
#else
#define UE_APP_MULT_ATTACH_VAL     100000
#endif
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
/*Bearer Release timer*/
#define UE_ESM_MAX_TIMERS    2
#define UE_ESM_DEACTV_BER_TMR_VAL 1000000
#define UE_INIT_DED_BEARER_RELEASE_TMR 5 
#define UE_ESM_CAUSE_VALUE 36

/* ue002.101: Multi ue support for end to end performance on Linux */ 
#ifdef LTE_E2E_PERF_MEAS
#define UE_APP_DATA_TMR  5
#define UE_APP_DATA_TMR_VAL 1000
#define UE_MAX_PDU_SIZE_E2E_PERF 1488
#define UE_APP_MAX_TMRS 5
#else
#define UE_APP_MAX_TMRS 4 
#endif

#define UE_APP_CELL_ID    1

/*MI type and odd/even*/
#define UE_EVEN 0x00
#define UE_ODD  0x01

/*Define the Detach Type */
#define UE_DETACH_EPS    0x01
#define UE_DETACH_IMSI  0x02
#define UE_DETACH_EPS_IMSI  0x03

#define UE_APP_L2_HEADER_SIZE 14

/*Swich Off*/
#define UE_DETACH_NORMAL    0x0
#define UE_DETACH_SWITCHOFF 0x1

/*Default Bearer ID Index*/
#define UE_APP_EPS_DFLT_BEARER_INDX 5
/* ue003.101: Added dedicated bearers support */
#define UE_APP_EPS_DED_BEARER_1        6

/* ue003.101: Added QOS support */
#define UE_DED_BR_QOS_LEN_CONT 9
#define UE_DED_BR_QOS_QCI            0
#define UE_DED_BR_QOS_MBR_UL 159 /* 10011111 for 2048000 bps */
#define UE_DED_BR_QOS_MBR_DL 159 /* 10011111 for 2048000 bps */
#define UE_DED_BR_QOS_GBR_UL 159 /* 10011111 for 2048000 bps */
#define UE_DED_BR_QOS_GBR_DL 159 /* 10011111 for 2048000 bps */
#define UE_DED_BR_QOS_EXT_MBR_UL 0 /* data rate is 2Mbps, i.e. < 8600kbps */
#define UE_DED_BR_QOS_EXT_MBR_DL 0 /* data rate is 2Mbps */
#define UE_DED_BR_QOS_EXT_GBR_UL 0 /* data rate is 2Mbps */
#define UE_DED_BR_QOS_EXT_GBR_DL 0 /* data rate is 2Mbps */

#define UE_UTL_SDU_SIZE 2048

#define UEAPP_MAX_BND_RETRY 3

#define UEAPP_BND_RETRY_CNT 0

#define UEAPP_RRC_SUID 0
#define UEAPP_PDCP_SUID 1

#define UEAPP_SPID 0

#define UE_APP_MAX_MCC_LEN 3
#define UE_APP_MAX_MNC_LEN 3

#define UE_APP_MCC_DIG0 0
#define UE_APP_MCC_DIG1 0
#define UE_APP_MCC_DIG2 1

#define UE_APP_MNC_DIG0 1
#define UE_APP_MNC_DIG1 0
#define UE_APP_MNC_DIG2 0

#define UE_APP_ID_DIG1  1
#define UE_APP_ID_DIG2  2
#define UE_APP_ID_DIG3  3
#define UE_APP_ID_DIG4  4
#define UE_APP_ID_DIG5  5
#define UE_APP_ID_DIG6  6
#define UE_APP_ID_DIG7  1
#define UE_APP_ID_DIG8  4 
#define UE_APP_ID_DIG9  1

#define UE_APP_MME_GROUP_ID 1
#define UE_APP_MME_CODE     1

/* ue002.101: Support of reading configuration parameters now 
   from a filesystem supportive platform config file;
   Example: Linux */
#ifdef NOFILESYS
#define UE_APP_SELF_ETH_INF_ADDR  0xAC1A0A08
#define UE_APP_DATA_SRVR_ADDR 0xAC1A0AB1
#if 1
#define UE_APP_DATA_SRVR_PORT 0x2710   /* This is for VLC */
#else
#define UE_APP_DATA_SRVR_PORT 0x50   /* This is for HTTP web service */
#endif
#endif /* NOFILESYS */

#define UESIM_MAX_CFG_FILE_LINE_LEN  256
#define UESIM_MAX_CFG_PARAM_LEN      256



/* Allocation memory for UE event */
#define UE_ALLOC_UEEVNT(_evntPtr, _evntType)             \
do                                                       \
{                                                        \
  (*_evntPtr) = NULLP;                                   \
  ueAppUtlCreateEvent(_evntPtr, _evntType);                 \
}while(0)

/* Freeing memory for UE event */
#define UE_FREE_UEEVNT(_evnt)                            \
do                                                       \
{                                                        \
  ueAppUtlFreeEvent((_evnt));                               \
  (*_evnt) = NULLP;                                      \
}while(0)

/*  ue002.101: Multi ue support: added macro to find ueAppCellCb */
#define UE_GET_APPCELLCB(_cellId,_ueAppCellCb)\
{\
  U16 _cellIdx=0;                                       \
  for (_cellIdx = 0; _cellIdx < UE_NUM_CELL; _cellIdx++)        \
  {                                                 \
     if (_cellId == ueSimAppCb.cellCb[_cellIdx].cellId)   \
     {                                              \
        _ueAppCellCb = &(ueSimAppCb.cellCb[_cellIdx]);    \
        break;                                      \
     }                                              \
  }                                                 \
  if (_cellIdx == UE_NUM_CELL)                         \
  {                                                \
     printf("not able to find cellId = %d\n", _cellId);\
     _ueAppCellCb = NULLP;                         \
  }                                                \
}

/*  ue002.101: Multi ue support: added macro to find ueAppCellCb */
#define UE_GET_APPCB(_cellId,_ueAppCb,_ueId)\
{\
  U16 _idx=0; \
  UeAppCellCb *_cell;                  \
  UE_GET_APPCELLCB(_cellId, _cell);      \
  if (_cell != NULLP)                  \
  {                                    \
     _idx=(UE_NUM_PER_CELL > 1)? (_ueId - _cell->startRnti): 0; \
     _ueAppCb = &_cell->ueAppCbLst[_idx];\
  }                                                       \
  else                                               \
  {                                               \
     printf("not able to find ue = %d\n", _ueId); \
  } \
} 

/* Layer Name appearing in the Debug prints */
#define UEAPP_LYR_NAME     "LTE-UE-SIMULATOR"
/* Allocation/Dellocation Macros for static buffers in UE SIM */
#define UEAPP_ALLOC(_buf, _size)                                        \
{                                                                       \
   if (SGetSBuf(UE_REGION, UE_POOL,                 \
                (Data **) _buf, (Size) _size) == ROK)                   \
   {                                                                    \
      UEAPP_DBG_MEM(ueSimAppCb.init, UEAPP_LYR_NAME, _buf, UEAPP_TYPE_BUF, \
      UEAPP_MEMMODE_ALLOC, _size);                                         \
      cmMemset((U8 *)(*_buf), 0, _size);                                \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      (*_buf) = NULLP;                                                  \
   }                                                                    \
}

#define UEAPP_FREE(_buf, _size)                                         \
{                                                                       \
   /*  ue002.101: Multi ue support changes */                              \
   UEAPP_DBG_MEM(ueSimAppCb.init, UEAPP_LYR_NAME, _buf, UEAPP_TYPE_BUF,   \
         UEAPP_MEMMODE_FREE, _size);                                       \
   (Void) SPutSBuf(ueSimAppCb.init.region, ueSimAppCb.init.pool,         \
                   (Data *) _buf, (Size) _size);                           \
   (_buf) = NULLP;                                                         \
}

/*--------------- Debug prints used under ERRCLS -------------------*/
#ifndef NO_ERRCLS

#define UEAPP_ERRCLS_CHK(errCls)    \
   if((errCls & ERRCLASS))

/* ue008.101: Fix for g++ compiation warnings */
#define UEAPP_LOGERROR(errCls, errCode, errVal, errDesc) \
do \
{ \
   UEAPP_ERRCLS_CHK(errCls) \
   { \
    SLogError(ueSimAppCb.init.ent, ueSimAppCb.init.inst, ueSimAppCb.init.procId,     \
          __FILE__, __LINE__, errCls, errCode, (ErrVal)errVal, \
          errDesc); \
   } \
}while(0)

#else  /* ERRCLS */

#define UEAPP_LOGERROR(errCls, errCode, errVal, errDesc)
#endif  /* ERRCLS */

/**********************************************************************/
#define UEAPP_PRNTBUF   ueSimAppCb.init.prntBuf

#define UEAPP_DBGMASK_MEM     (DBGMASK_LYR << 0)
#define UEAPP_DBGMASK_TRC     (DBGMASK_LYR << 1)
#define UEAPP_DBGMASK_ERROR   (DBGMASK_LYR << 2)
#define UEAPP_DBGMASK_INFO    (DBGMASK_LYR << 3)

/*-- Different memory types --*/
#define UEAPP_MEMTYPE_EVNT  1
#define UEAPP_MEMTYPE_MSG   2
#define UEAPP_TYPE_BUF  3

/*-- Different memory modes --*/
#define UEAPP_MEMMODE_ALLOC 1
#define UEAPP_MEMMODE_FREE  2
#define UEAPP_MEMMODE_SEND  3
#define UEAPP_MEMMODE_RCV   4

#ifdef DEBUGP 
/* macro to print buffer 
*/
#define UESIMPRNT(_init, _prntBuf)     \
{                                      \
   sprintf _prntBuf;                   \
   SPrint(_init.prntBuf);              \
}

/* macro to get and print timestamp value */
#ifdef UEAPP_PRNT_TIMESTAMP
#define UEAPP_PRNTTIMESTAMP(_init)                                      \
{                                                                       \
   S8 _buf[60];                                                         \
   (Void) SGetTimeStamp(_buf);                                          \
   UESIMPRNT(_init, (_init.prntBuf, "[%s]:", _buf));                    \
}
#else
#define UEAPP_PRNTTIMESTAMP(_init)
#endif

/* macro to print layer Name */
#define UEAPP_PRNT_LAYER(_init, _lyr)                                   \
{                                                                       \
   UESIMPRNT(_init, (_init.prntBuf, " [%s 0x%x:%x]", _lyr,              \
         _init.ent, _init.inst));                                       \
}

/* macro to print filename, line number and function name */
#define UEAPP_PRNT_FILE_LINE_FUNC(_init)                                     \
{                                                                       \
   UESIMPRNT(_init, (_init.prntBuf, " [%s:%d:%s]",__FILE__,__LINE__, __tapa_fun)); \
}
/* macro to print filename, line number  */
#define UEAPP_PRNT_FILE_LINE(_init)                                     \
{                                                                       \
   UESIMPRNT(_init, (_init.prntBuf, " [%s:%d]",__FILE__,__LINE__)); \
}

/* Debug macros for different debug levels */

/* ue004.101: Passing _init in UEAPP_PRNTTIMESTAMP for 64bit */
/*-------------------------Memory Debug Prints------------------------*/
#ifdef ALIGN_64BIT
#define UEAPP_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)     \
{                                                                       \
   if (_init.dbgMask & (UEAPP_DBGMASK_MEM))                               \
   {                                                                    \
      UEAPP_PRNTTIMESTAMP(_init)                                        \
      UEAPP_PRNT_LAYER(_init, _lyr)                                     \
      UEAPP_PRNT_FILE_LINE(_init)                                       \
      UESIMPRNT(_init, (_init.prntBuf, " [ MEM  : %d %d %p %d]\n",      \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));            \
   }                                                                    \
}
#else
#define UEAPP_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)     \
{                                                                       \
   if (_init.dbgMask & (UEAPP_DBGMASK_MEM))                               \
   {                                                                    \
      UEAPP_PRNTTIMESTAMP(_init)                                        \
      UEAPP_PRNT_LAYER(_init, _lyr)                                     \
      UEAPP_PRNT_FILE_LINE(_init)                                       \
      UESIMPRNT(_init, (_init.prntBuf, " [ MEM  : %d %d %p %ld]\n",     \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));            \
   }                                                                    \
}
#endif /*ALIGN_64BIT */

/*------------------------- Trace Prints------------------------*/

/* Trace for Utilities / General Code */
/* Note: For now the common places, ueAppCellCb is used presently.
 * Take care in the process of segregation of code.*/
#define UEAPP_TRC2(_arg)                                                \
Txt __tapa_fun[PRNTSZE];                                                \
sprintf(__tapa_fun,#_arg);                                              \
{                                                                       \
   if (ueSimAppCb.init.dbgMask & (UEAPP_DBGMASK_TRC))                        \
   {                                                                    \
      UEAPP_PRNTTIMESTAMP(ueSimAppCb.init)                                 \
      UEAPP_PRNT_LAYER(ueSimAppCb.init, UEAPP_LYR_NAME)                    \
      UEAPP_PRNT_FILE_LINE_FUNC(ueSimAppCb.init)                           \
      UESIMPRNT(ueAppCellCb.init, (ueSimAppCb.init.prntBuf," Entering\n"));    \
      TRC2(_arg);                                                       \
   }                                                                    \
}

#define UEAPP_TRC3(_arg)                                                \
Txt __tapa_fun[PRNTSZE];                                                \
sprintf(__tapa_fun,#_arg);                                              \
{                                                                       \
   if (ueAppCellCb.init.dbgMask & (UEAPP_DBGMASK_TRC))                        \
   {                                                                    \
      UEAPP_PRNTTIMESTAMP(ueSimAppCb.init)                                 \
      UEAPP_PRNT_LAYER(ueSimAppCb.init, UEAPP_LYR_NAME)                    \
      UEAPP_PRNT_FILE_LINE_FUNC(ueSimAppCb.init)                           \
      UESIMPRNT(ueAppCellCb.init, (ueSimAppCb.init.prntBuf," Entering\n"));    \
      TRC3(_arg);                                                       \
   }                                                                    \
}

#define UEAPP_RETVOID                                                   \
do                                                                      \
{                                                                       \
   if (ueSimAppCb.init.dbgMask & (UEAPP_DBGMASK_TRC))                        \
   {                                                                    \
      UEAPP_PRNTTIMESTAMP(ueSimAppCb.init)                                 \
      UEAPP_PRNT_LAYER(ueSimAppCb.init,  UEAPP_LYR_NAME)                      \
      UEAPP_PRNT_FILE_LINE(ueSimAppCb.init)                                \
      UESIMPRNT(ueSimAppCb.init, (ueSimAppCb.init.prntBuf, " Exiting\n"));    \
   }                                                                    \
   RETVOID;                                                             \
}while(0)

#define UEAPP_RETVALUE(_arg)                                            \
{                                                                       \
   if (ueSimAppCb.init.dbgMask & (UEAPP_DBGMASK_TRC))                        \
   {                                                                    \
      UEAPP_PRNTTIMESTAMP(ueSimAppCb.init)                                 \
      UEAPP_PRNT_LAYER(ueSimAppCb.init,  UEAPP_LYR_NAME)                      \
      UEAPP_PRNT_FILE_LINE(ueSimAppCb.init)                                \
      UESIMPRNT(ueSimAppCb.init, (ueSimAppCb.init.prntBuf, " Exiting\n"));    \
   }                                                                    \
   RETVALUE(_arg);                                                      \
}

#else /* DEBUGP */
/* macro to print buffer */
#define UESIMPRNT(_prntbuf)

/* macro to get and print timestamp value */
#define UEAPP_PRNTTIMESTAMP(_init)

/* macro to print layer Name */
#define UEAPP_PRNT_LAYER(_init, _lyr)

/* macro to print filename, line number and function name */
#define UEAPP_PRNT_FILE_LINE(_init)



/*-------------------------Memory Debug Prints------------------------*/
#ifdef ALIGN_64BIT
#define UEAPP_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)
#else
#define UEAPP_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)
#endif
/*------------------------- Trace Prints------------------------*/
#define UE_TRC2(_arg)
#define UE_TRC3(_arg)

#define UEAPP_RETVOID         RETVOID
#define UEAPP_RETVALUE(_arg)  RETVALUE(_arg)

#endif /* DEBUGP */


/* ESM definitions */
#define UE_ESM_TRANS_ID_INDX  1
#define UE_ESM_MAX_TRANS_ID  254
#define UE_ESM_MAX_BID  30

#define UEAPP_ALLOC_RRC_EVNT(_evntPtr, _size, _mem, _maxBlkSize)   \
{                                                              \
   (*_evntPtr) = NULLP;                                        \
   (Void)cmAllocEvnt((Size) _size, _maxBlkSize, _mem,          \
                     (Ptr *)_evntPtr);                         \
}

#define UEAPP_FREE_RRC_EVNT(_evntPtr)  \
{                                      \
   cmFreeMem((Ptr *)_evntPtr);         \
   (_evntPtr) = NULLP;                 \
}

#define UEAPP_RRC_BLKSZ    2000

#define UEAPP_FILL_U8_U32_TKN(_ie, _pres, _val) \
{ \
   _ie.pres = _pres;\
   _ie.val = _val;\
}

#define UE_APP_FREE_PKT  0
#define UE_APP_DONT_FREE_WQE  1


/* Macros for data handler */
#ifdef BOARD_OCTEON56XX
#define UE_APP_BASE_PORT    0
#else
#define UE_APP_BASE_PORT    16
#endif
#define UE_APP_MAC_PORT_ID  1
#define UE_PCAP_PORT_GROUP  10


/* ue003.101: Added dedicated bearer support */
#define   UE_APP_DED_BEARER_START_PORT 1235

#define UE_APP_PROXY_PORT 1234

#define UE_APP_MAX_IP_ADDR_LEN 4
#define UE_APP_MAX_IP_ADDR_STR_LEN 16
#define UE_APP_MAC_ADDR_LEN 6
#define UE_APP_MAX_ETH_PKT_LEN 1600
#define UE_APP_MAX_ARP_PKT_LEN 60
#define UE_APP_MAX_PCAP_DEV_LEN 256
/*-- ue008.101: Update support for 17 connections --*/
#define UE_APP_MAX_CONNS 17
#define UE_APP_ARP_PKT_SIZE  42

#define UE_APP_PCAP_BUF_SIZE 65536
#define UE_APP_MAX_IP_PKT 5000
#define UE_APP_PCAP_TIMEOUT 10 /* milli seconds */
#define UE_APP_ETH_TYPE_IP 0x0008
#define UE_APP_ETH_TYPE_ARP 0x0608

#define UE_APP_IP_PROTO_ICMP 0x01
#define UE_APP_IP_PROTO_TCP  0x06
#define UE_APP_IP_PROTO_UDP  0x11

#define UE_APP_ARP_REQ 0x0100
#define UE_APP_ARP_RSP 0x0200

#define UE_APP_SRC_IP_ADDR_IDX  12
#define UE_APP_DST_IP_ADDR_IDX  16

#endif

/**********************************************************************
         End of file:     ue_app.h@@/main/1 - Sun Mar 28 22:59:20 2010
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
                              3. Changes to support MSPD CL.
/main/1+   ue003.101  rp      1. Added support for paging.
                              2. Added support for dedicated bearers.
                              3. Added support for QOS.
/main/1+   ue004.101  rk      1. Passing _init in UEAPP_PRNTTIMESTAMP for 64bit
/main/1+   ue006.101  sgm     1. Fix for CID:1465-02-01, DefectId:ccpu00116336. 
                                 Removing the compiler warning.
/main/1+   ue007.101  rk      1. Added support for multiple attach and detach.
/main/1+   ue008.101 ragrawal 1. CRID:ccpu00117391 ERAB RELEASE support. 
                              2. Added new macro for multi-Attach/Detach.
                              3. Fix for g++ compilation warnings.
                              4. Updated UE_APP_MAX_CONNS to support for 17 connections. 
*********************************************************************91*/

