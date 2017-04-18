
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:46:48 2014

     Prg:     up 

*********************************************************************21*/
#ifndef __CMXTA_H__
#define __CMXTA_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------------------------------------------------------
      CMXTA FTHA related defines 
----------------------------------------------------------------------*/
#ifdef CMXTA_FTHA_INTEGRATED
#define CMXTA_SG_MAX_SYS_NODES      10
#define CMXTA_SG_MAX_SYS_ENTS       10
#define CMXTA_SG_MAX_SYS_INSTANCES  10
#define CMXTA_SG_TMR_RES            1
#define CMXTA_SG_RTX_TM             40  
#define CMXTA_SG_LONG_RTX_TM        40  
#define CMXTA_SG_RTX_COUNT          2  
#define CMXTA_SG_TX_HEARTBEAT       20
#define CMXTA_SG_RX_HEARTBEAT       20

#define CMXTA_MR_MAX_PEERSYNC_MSG   5
#define CMXTA_MR_MAX_QSIZE          10
#define CMXTA_MR_TIMER_RES          1
#define CMXTA_MR_PEER_TIMER         20

#define CMXTA_FM_TIMER_1            1
#define CMXTA_FM_TIMER_2            2

#define CMXTA_FM_TIMER_1_EXP        1
#define CMXTA_FM_TIMER_2_EXP        50
#define CMXTA_FM_MAX_TIMERS         2
#define CMXTA_FM_MAX_RETRY         5
#define CMXTA_FM_TQ_SIZE            2

#endif

/* cm_xta_h_001.main_12: Provided the flixibility to define the value in case 
 * it need to be changed */
#ifndef CMXTA_NODES
#define CMXTA_NODES                 5
#endif

#define CMXTA_MAX_ENTITY        50
#define CMXTA_MAX_CALL          10
/* cm_xta_h_001.main_6: Updates for SIP Release 2.3 */
#define CMXTA_MAX_DLG_PER_CALL          10
#define CMXTA_MAX_TRANS_PER_DLG          10
#define CMXTA_MAX_EXP_SET_MSG            50

/*----------------------------------------------------------------------
             TA: Single Or Multiple Binary Instances
-----------------------------------------------------------------------*/
#define CMXTA_TA_INST_NONE              1
#define CMXTA_TA_INST_MASTER            2
#define CMXTA_TA_INST_SLAVE             3

/*----------------------------------------------------------------------
             TA: Proc Id
-----------------------------------------------------------------------*/
#define CMXTA_PROCID_SLAVE      100

#define CMXTA_PROCID_SLAVE1     CMXTA_PROCID_SLAVE
#define CMXTA_PROCID_SLAVE2     200
#define CMXTA_PROCID_SLAVE3     300
#define CMXTA_PROCID_SLAVE4     400
#define CMXTA_PROCID_SLAVE5     500
#define CMXTA_PROCID_SLAVE6     600
#define CMXTA_PROCID_SLAVE7     700
#define CMXTA_PROCID_SLAVE8     800

#define CMXTA_PROCID_SLAVEMAX   CMXTA_PROCID_SLAVE8

#define CMXTA_PROCID_MASTER     900

/* cm_xta_h_001.main_2 */
/*-- These #defines are for Message router support --*/
#define CMXTA_PROCID_SINGLE  CMXTA_PROCID_MASTER  
#define CMXTA_PROCID_ONE     CMXTA_PROCID_SLAVE1
#define CMXTA_PROCID_TWO     CMXTA_PROCID_SLAVE2
#define CMXTA_PROCID_THREE   CMXTA_PROCID_SLAVE3
#define CMXTA_PROCID_FOUR    CMXTA_PROCID_SLAVE4
#define CMXTA_PROCID_FIVE    CMXTA_PROCID_SLAVE5
#define ZO_ZOT_MODE_MANUAL  1

/*----------------------------------------------------------------------
             TA: Procs Macros
-----------------------------------------------------------------------*/
#define cmXtaProcStart(_arg) {TRUE, _arg,
#define cmXtaProcEnd   },


/*----------------------------------------------------------------------
             TA: Profile Macros
-----------------------------------------------------------------------*/
#define cmXtaTopEmpty {TRUE, "Not Available"}

#define cmXtaTopStart(_arg) {TRUE, _arg,
#define cmXtaTopEnd   },

#define cmXtaTopSTasks(_arg) _arg,

#define cmXtaTopProcStart(_arg) _arg, {
#define cmXtaTopProcEnd   },

#define cmXtaTopEntitiesStart {
#define cmXtaTopEntitiesEnd },

#define cmXtaTopEntity(_sTsk, _proc, _ent, _inst, _type, _prior, _initTsk, _actvTsk) \
      {TRUE, _sTsk, _proc, _ent, _inst, _type, _prior, _initTsk, _actvTsk},

#define cmXtaTopCouplingStart {
#define cmXtaTopCouplingEnd },

#define cmXtaTopCoupling(_dstProc, _dstEnt, _dstInst, _srcProc, _srcEnt, _srcInst, _toSel, _fromSel) \
      {TRUE, _dstProc, _dstEnt, _dstInst, _srcProc, _srcEnt, _srcInst, _toSel, _fromSel},


/*----------------------------------------------------------------------
             TA: Forward declarations
-----------------------------------------------------------------------*/
/* cm_xta_h_001.main_9: Two new flags added for DNS enhancement under 
 * GPR 26 release  */
/* cm_xta_h_001.main_10: Added two flags for Iuh 2.1 release */
/* cm_xta_h_001.main_11: Added five flags for LTE RRC 3.1 release */
/* cm_xta_h_001.main_13: Added sixteen flags for Diameter 1.3 release */
#define CMXTA_MAX_FLAGS         65

/*----------------------------------------------------------------------
             TA mode
-----------------------------------------------------------------------*/
#define CMXTA_TA_MODE_DFLT             1
#define CMXTA_TA_MODE_DFLT_NOSHUTDOWN  2
#define CMXTA_TA_MODE_LOOP             4
#define CMXTA_TA_MODE_MULT_TOP         8
#define CMXTA_TA_MODE_GRPNOSHUTDOWN    16

#define CMXTA_TA_MODE_EXTERNAL         32
#define CMXTA_TA_MODE_LOAD             64

/*----------------------------------------------------------------------
             TC modes
-----------------------------------------------------------------------*/
#define CMXTA_MODE_SINGLE   0
#define CMXTA_MODE_MULTIPLE 1
#define CMXTA_MODE_EXTERNAL 2
#define CMXTA_MODE_LOAD     3

/*----------------------------------------------------------------------
             Memory Print Types
-----------------------------------------------------------------------*/
#define CMXTA_MEM_LOG_INIT          0
#define CMXTA_MEM_LOG_DEINIT        1

#define CMXTA_MEM_TA_INIT           2
#define CMXTA_MEM_TA_DEINIT         3

#define CMXTA_MEM_TC_INIT           4
#define CMXTA_MEM_TC_DEINIT         5
#define CMXTA_MEM_TC_RUN            6
#define CMXTA_MEM_TC_CLEAN          7

/*----------------------------------------------------------------------
             Flag options
-----------------------------------------------------------------------*/
#define CMXTA_INV_IFDEF          0
#define CMXTA_INV_IFNDEF         1
#define CMXTA_LAYER_FLAGS        2

/*----------------------------------------------------------------------
             Context for step execution
-----------------------------------------------------------------------*/
#define CMXTA_CTXT_TC  1
#define CMXTA_CTXT_TG  2
#define CMXTA_CTXT_TA  3
#define CMXTA_CTXT_EXT 4

/*----------------------------------------------------------------------
             Timer events
-----------------------------------------------------------------------*/
#define CMXTA_TMR_GUARD_EXP                 1
#define CMXTA_TMR_TIMEOUT                   2
#define CMXTA_TMR_DELAY                     3
#define CMXTA_TMR_DELAY_TST                 4
#define CMXTA_TMR_DELAY_SHUTDOWN            5
#define CMXTA_TMR_PERD_RPT_TMR              8
#define CMXTA_TMR_T321                      9
/*-- These two timers are for Fault detection module --*/
#define CMXTA_TMR_FD_TIMER_1                6
#define CMXTA_TMR_FD_TIMER_2                7

/*----------------------------------------------------------------------
             Timer Values
-----------------------------------------------------------------------*/
#ifndef CMXTA_TMR_GUARD_VAL
#define CMXTA_TMR_GUARD_VAL                   100
#endif
#define CMXTA_TMR_TIMEOUT_VAL                 15
#define CMXTA_TMR_DELAY_VAL                   50
#define CMXTA_TMR_DELAY_TST_VAL               300
#define CMXTA_TMR_DELAY_SHUTDOWN_VAL          300
#define CMXTA_TMR_PERD_RPT_TMR_VAL            300

/*----------------------------------------------------------------------
             TA Results
-----------------------------------------------------------------------*/
/* Individual test and group result status */
#define CMXTA_TEST_NONE                        0           /* test result - pass   */
#define CMXTA_TEST_PASSED                      1           /* test result - pass   */
#define CMXTA_TEST_FAILED                      2           /* test result - failed */
#define CMXTA_TEST_IGNORED                     3           /* test result - ignored */
#define CMXTA_TEST_LEAK                        4           /* test result - leak    */


#define CMXTA_TEST_LEAK_CFG                    1           /* test result - pass   */
#define CMXTA_TEST_LEAK_RUN                    2           /* test result - failed */

/*----------------------------------------------------------------------
             XML Element Types
-----------------------------------------------------------------------*/
#define CMXTA_DOM_ELEMENT_NODE                1
#define CMXTA_DOM_ATTRIBUTE_NODE              2
#define CMXTA_DOM_TEXT_NODE                   3
#define CMXTA_DOM_CDATA_SECTION_NODE          4
#define CMXTA_DOM_ENTITY_REFERENCE_NODE       5
#define CMXTA_DOM_ENTITY_NODE                 6
#define CMXTA_DOM_PROCESSING_INSTRUCTION_NODE 7
#define CMXTA_DOM_COMMENT_NODE                8
#define CMXTA_DOM_DOCUMENT_NODE               9
#define CMXTA_DOM_DOCUMENT_TYPE_NODE          10
#define CMXTA_DOM_DOCUMENT_FRAGMENT_NODE      11
#define CMXTA_DOM_NOTATION_NODE               12

/*----------------------------------------------------------------------
             Element Attributes Type
-----------------------------------------------------------------------*/
#define CMXTA_ATTRIB_U16         1
#define CMXTA_ATTRIB_TXT         2
#define CMXTA_ATTRIB_ENUM        3
#define CMXTA_ATTRIB_S16         4
#define CMXTA_ATTRIB_ENUM_U8     5
#define CMXTA_ATTRIB_ENUM_U32    6
#define CMXTA_ATTRIB_U8          7
#define CMXTA_ATTRIB_U32         8
#define CMXTA_ATTRIB_ENUM_U16    9
#define CMXTA_ATTRIB_FLAG       10
#define CMXTA_ATTRIB_BOOL       11
#define CMXTA_ATTRIB_S8         12

/*----------------------------------------------------------------------
             XML Command Type
-----------------------------------------------------------------------*/
#define CMXTA_TYPE_INT   1
#define CMXTA_TYPE_COMPOUND   2
#define CMXTA_TYPE_DIR        3
#define CMXTA_TYPE_LEAF   4
#define CMXTA_TYPE_TC   5
#define CMXTA_TYPE_TG   6

/*----------------------------------------------------------------------
             TC Step Type
-----------------------------------------------------------------------*/
#define CMXTA_SUBTYPE_SEND       1
#define CMXTA_SUBTYPE_EXPECT     2
#define CMXTA_SUBTYPE_EXPSEQ     3
#define CMXTA_SUBTYPE_EXPOPT     4
#define CMXTA_SUBTYPE_EXPSET     5
#define CMXTA_SUBTYPE_TIMEOUT    6
#define CMXTA_SUBTYPE_DELAY      7
#define CMXTA_SUBTYPE_RE         8
#define CMXTA_SUBTYPE_OTHER      9
/* cm_xta_h_001.main_5 loop changes start */
/*--New Macros are introduced for repeat start and repeat end */
#define CMXTA_SUBTYPE_REPEAT_START    10 
#define CMXTA_SUBTYPE_REPEAT_END    11 
/* loop changes ends */

/*----------------------------------------------------------------------
             Error Codes
-----------------------------------------------------------------------*/
#define CMXTA_ERR_BASE                0

#define CMXTA_ERR_NONE                CMXTA_ERR_BASE + 0
#define CMXTA_ERR_INT                 CMXTA_ERR_BASE + 1
#define CMXTA_ERR_NO_VALUE            CMXTA_ERR_BASE + 2

#define CMXTA_ERR_RSRC                CMXTA_ERR_BASE + 4
#define CMXTA_ERR_DUP                 CMXTA_ERR_BASE + 12

#define CMXTA_ERR_PENDING             CMXTA_ERR_BASE + 16
#define CMXTA_ERR_FINISHED            CMXTA_ERR_BASE + 17
#define CMXTA_ERR_CONTINUE            ROK
#define CMXTA_ERR_COMPLETE            CMXTA_ERR_BASE + 20
#define CMXTA_ERR_NOMATCH             CMXTA_ERR_BASE + 21
#define CMXTA_ERR_FATAL               CMXTA_ERR_BASE + 22
#define CMXTA_ERR_SKIP                RSKIP

/* demo fix start */
/* #define CMXTA_ERR_MAX                 CMXTA_ERR_BASE + 19 */

/*----------------------------------------------------------------------
             Attribute List Separator
-----------------------------------------------------------------------*/
#define CMXTA_SEP_COLON          1
#define CMXTA_SEP_DOT            2
/* cm_xta_h_001.main_13: Added delimiter hash */
#define CMXTA_SEP_HASH           3

/*----------------------------------------------------------------------
             STM States
-----------------------------------------------------------------------*/
#define CMXTA_START_INIT              0
#define CMXTA_START_CFG         1
#define CMXTA_END_CFG           2
#define CMXTA_START_RUN         3
#define CMXTA_END_RUN           4
#define CMXTA_START_CLN         5
#define CMXTA_END_CLN           6
#define CMXTA_SHUTDOWN          7
#define CMXTA_END_SHUTDOWN      8
#define CMXTA_START_EXT         9
#define CMXTA_END_EXT           10

#define CMXTA_MAX               11
/*----------------------------------------------------------------------
         TG/TC States
-----------------------------------------------------------------------*/
/* Test group states */
#define CMXTA_NONE                       0           /* test idle state      */
#define CMXTA_IDLE                       1           /* test idle state      */
#define CMXTA_INIT                       2           /* test init state      */
#define CMXTA_CFG                        3           /* test cfg state       */
#define CMXTA_RUN                        4           /* test run state       */
#define CMXTA_CLN                        5           /* test clean up state  */
#define CMXTA_CMP                        6           /* test complete state  */

/*----------------------------------------------------------------------
             General Defines
-----------------------------------------------------------------------*/
#define CMXTA_MAX_TMR                 10
#define CMXTA_MAX_QUEUES              2 /*-- MAX number of message queues --*/
#define CMXTA_TQ_SIZE                 20

/*----------------------------------------------------------------------
             General Defines
-----------------------------------------------------------------------*/
/* Layer name */
#define CMXTA_LAYERNAME     "CmXta"

#define CMXTA_DFLT_TOP  0

#define  CMXTA_STACK_DEPTH      25 

#define CMXTA_MAX_INTERFACE            180
#define EVTSTTTSTINIT  0
#define EVTSTTTSTSKIP  1
/*-- Defines for fault manager in XTA --*/
#ifdef CMXTA_FTHA_INTEGRATED
#define EVTSTHEARTBEATREQ             4
#define EVTSTHEARTBEATRSP             5
#define EVTSTHEARTBEATRSP             5
#define EVTSTFMSERVERINIT             6
#define EVTSTFMCLIENTINIT             7
#endif

#define CMXTA_MAX_GRP                 100
#define CMXTA_MAX_TST                 250

#define CMXTA_MAX_TASK 5

/* Max number of psf updates from Active to Standby */
#ifdef CM_XTA_PSF
#define CMXTA_MAX_PSF_UPDATES 10;
#endif

#define CMXTA_INST_ID                   0
#define CMXTA_PROC_ID                   0
#define CMXTA_MSGQ_SIZE                   150

#define CMXTA_TXN_INVALID 0

#ifdef CMXTA_INSURE
/* allow to run on VERY slow machine / Insure */
#define CMXTA_TMR_RES          10     /* system ticks per 100ms */
#else /* CMXTA_INSURE */
/* normal execution */
#define CMXTA_TMR_RES          1     /* system ticks per 100ms */
#endif /* CMXTA_INSURE */

/*----------------------------------------------------------------------
             General Macros
-----------------------------------------------------------------------*/
#define CMXTA_OFFSET_OF(type, member)     ((PTR)(&(((type *) 0)->member)))

#define CMXTA_ZERO(_buf, _size)                                         \
   cmMemset((U8 *)(_buf), 0, _size);

#define CMXTA_CPY(_dst, _src, _len) \
   cmMemcpy((U8*) (_dst), (U8*) (_src), _len);

/* Allocation/Dellocation Macros */

/* SGetSBuf & SPutSBuf Macros */
#define CMXTA_ALLOC(_buf, _size)\
{\
   if (SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **) _buf,    \
                _size) == ROK)                                \
   {                                                                 \
      cmMemset((U8 *)(*_buf), 0, _size);                             \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (*_buf) = NULLP;                                               \
   }                                                                 \
}
#define CMXTA_FREE(_buf, _size)\
{\
   (Void) SPutSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data *) _buf, \
   (Size) _size);\
   (_buf) = NULLP;\
}

/* SGetMsg & SPutMsg Macros */
#define CMXTA_ALLOCMBUF(_buf)\
{\
   if (SGetMsg(cmXtaCb.init.region, cmXtaCb.init.pool, (Buffer **) _buf) != ROK) \
   {                                                                       \
      (*_buf) = NULLP;                                                     \
   }                                                                       \
}
#define CMXTA_FREEMBUF(_mBuf) \
if (_mBuf != (Buffer*) NULLP)      \
{                                   \
   (Void)SPutMsg(_mBuf);            \
   _mBuf = NULLP;                   \
}

/* cm_xta_h_001.main_7: macros for event related
 * memory allocations and free
*/
/* Macro to allocate event structure */
#define CMXTA_ALLOC_EVNT(_evntPtr, _size, _mem, _maxBlkSize)   \
{                                                              \
   (*_evntPtr) = NULLP;                                        \
   (Void)cmAllocEvnt((Size) _size, _maxBlkSize, _mem,          \
                     (Ptr *)_evntPtr);                         \
}

/* Macro to get additional memory */
#define CMXTA_GET_MEM(_memPtr, _size, _allocPtr)               \
{                                                              \
   (*_allocPtr) = NULLP;                                       \
   (Void)cmGetMem(_memPtr, _size, (Ptr *)_allocPtr);           \
}

/* Macro to free the Event Structure */
#define CMXTA_FREEEVNT(_evntPtr)       \
{                                      \
   cmFreeMem((_evntPtr));              \
   (_evntPtr) = NULLP;                 \
}

/*----------------------------------------------------------------------
             Debug Macros
-----------------------------------------------------------------------*/

/* Debug printing mask defines */
#define CMXTA_DBGMASK_RES             0     /* encode/decode */
#define CMXTA_DBGMASK_FATAL           1     /* encode/decode */
#define CMXTA_DBGMASK_CALL            2     /* encode/decode */
#define CMXTA_DBGMASK_ERR             3     /* error conds   */
#define CMXTA_DBGMASK_PARAM           9     /* param         */
#define CMXTA_DBGMASK_INFO            8     /* informational */
#define CMXTA_DBGMASK_PY              9     /* encode/decode */


#define CMXTA_DBGP(_tskInit, _dbgMask, _layerName, _msgClass, _arg1, _arg2) \
        { \
           /*-- Use Debug Level rather than debug mask --*/ \
           if (_dbgMask >= (_msgClass)) \
           { \
              /* SOAC_ENHANCE:  Add Timestamp code */\
              sprintf(cmXtaCb.apb, "[%s 0x%x:%x] %8s:%4d ", \
                    _layerName, (_tskInit)->ent, (_tskInit)->inst, \
                    __FILE__, __LINE__); \
              SPrint(cmXtaCb.apb); \
              sprintf(cmXtaCb.apb, "%s", _arg1); \
              SPrint(cmXtaCb.apb); \
              sprintf _arg2; \
              SPrint(cmXtaCb.apb); \
           } \
        }

#define _cmxtap                       cmXtaCb.apb
#define CMXTA_DBG_INT(_msgClass, _arg1, _arg2)    CMXTA_DBGP(&cmXtaCb.init, cmXtaCb.dbgMask, CMXTA_LAYERNAME, _msgClass, _arg1, _arg2)
#define CMXTA_DBG_PRNT(_msgClass, _arg)     {\
   /*-- Use Debug Level rather than debug mask --*/ \
   if (cmXtaCb.dbgMask >= (_msgClass)) \
   { \
      /* SOAC_ENHANCE:  Add Timestamp code */\
      sprintf _arg; \
      SPrint(cmXtaCb.apb); \
   } \
}
/* Macro used for indentation --*/
#define CMXTA_DBG_PRNTIND(_msgClass, _arg2, _arg3)  {\
   S16 _val_;\
   if (cmXtaCb.dbgMask >= (_msgClass)) \
   { \
      for (_val_ = 0; _val_ < _arg3; _val_++) {\
         sprintf(cmXtaCb.apb, "   "); \
         SPrint(cmXtaCb.apb); \
      }\
      CMXTA_DBG_PRNT(_msgClass, _arg2);\
   }\
}


/* display error */
#define CMXTA_DBG_ERR(_arg)               CMXTA_DBG_INT(CMXTA_DBGMASK_ERR,   "Failed: ", _arg)
/* display params */
#define CMXTA_DBG_PARAM(_arg)             CMXTA_DBG_INT(CMXTA_DBGMASK_PARAM, "Param : ", _arg)
/* display call flow */
#define CMXTA_DBG_INFO(_arg)              CMXTA_DBG_INT(CMXTA_DBGMASK_INFO,  "Info  : ", _arg)
/* display fatal error */
#define CMXTA_DBG_FATAL(_arg)             CMXTA_DBG_INT(CMXTA_DBGMASK_FATAL, "** FATAL ** : ", _arg)
/* display memory */
#define CMXTA_DBG_PY(_arg)                CMXTA_DBG_INT(CMXTA_DBGMASK_PY,    "Python: ", _arg)
/* display result dump */
#define CMXTA_DBG_CALL(_arg)              CMXTA_DBG_PRNT(CMXTA_DBGMASK_CALL, _arg)
#define CMXTA_DBG_RES(_arg)               CMXTA_DBG_PRNT(CMXTA_DBGMASK_RES, _arg)
#define CMXTA_DBG_RESIND(_arg1, _arg2)    CMXTA_DBG_PRNTIND(CMXTA_DBGMASK_RES, _arg1, _arg2)
#define CMXTA_DBG_CALLIND(_arg1, _arg2)   CMXTA_DBG_PRNTIND(CMXTA_DBGMASK_CALL, _arg1, _arg2)

#define CMXTA_LOGERROR(errCls, errCode, errVal, errDesc)                   \
        SLogError(cmXtaCb.init.ent, cmXtaCb.init.inst, cmXtaCb.init.procId,     \
                  __FILE__, __LINE__, errCls, errCode, (ErrVal)errVal, \
                  errDesc);

#define CMXTALOGDBGERR(errCode, errVal, errDesc)                          \
        CMXTA_LOGERROR(ERRCLS_DEBUG, errCode, errVal, errDesc)

#if (ERRCLASS & ERRCLS_DEBUG)
#define CMXTA_LOGERR_DBG(errCode, errVal, errDesc)                        \
        CMXTA_LOGERROR(ERRCLS_DEBUG, errCode, errVal, errDesc)
#else
#define CMXTA_LOGERR_DBG(errCode, errVal, errDesc)
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
#define CMXTA_LOGERR_INTPAR(errCode, errVal, errDesc)                       \
        CMXTA_LOGERROR(ERRCLS_INT_PAR, errCode, errVal, errDesc)
#else
#define CMXTA_LOGERR_INTPAR(errCode, errVal, errDesc)
#endif

#if (ERRCLASS & ERRCLS_ADD_RES)
#define CMXTA_LOGERR_ADDRES(errCode, errVal, errDesc)                       \
        CMXTA_LOGERROR(ERRCLS_ADD_RES, errCode, errVal, errDesc)
#else
#define CMXTA_LOGERR_ADDRES(errCode, errVal, errDesc)
#endif

/* Runtime error checking macros - */
#ifdef ERRCLS_DEBUG
#define CMXTA_ASSERT_NONNULL(cond)                                             \
   {                                                                        \
      if(!(cond))                                                           \
      {                                                                     \
         CMXTA_DBG_ERR((sop, #cond "Null pointer assertion failure\n"));       \
         RETVALUE(RFAILED);                                                 \
      }                                                                     \
   }
#else   /* ERRCLS_DEBUG */
#define CMXTA_ASSERT_NONNULL(cond)
#endif  /* ERRCLS_DEBUG */
 
/*-- Macro to reverse the Pst --*/
#define cmXtaReversePst(_pst) \
{ \
   Pst lPst; \
   cmMemcpy((U8*) &lPst, (U8*) &(_pst), sizeof(Pst)); \
   (_pst).dstProcId = lPst.srcProcId;\
   (_pst).dstInst   = lPst.srcInst;\
   (_pst).dstEnt    = lPst.srcEnt;\
   (_pst).srcProcId = lPst.dstProcId;\
   (_pst).srcInst   = lPst.dstInst;\
   (_pst).srcEnt    = lPst.dstEnt;\
}



#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CMXTA_H__ */
/********************************************************************30**

         End of file:     cm_xta.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:46:48 2014

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
------------ -------- ---- ----------------------------------------------
/main/2      ----     up   1. Main release
/main/3      ---      cm_xta_h_001.main_2  sk  1. Added defines are for Message router support 
/main/4      ---      mr  1. Increased the MsgQSize.
/main/5      ---      aj  1. CMXTA FTHA related defines  
                         2. Defines for fault Manager got added
/main/6      ---      cm_xta_h_001.main_5 mn  1. Adding cm_xta loop changes
/main/7      ---      cm_xta_h_001.main_6 ve  1. Updates for SIP Release 2.3
/main/8      ---      cm_xta_h_001.main_7 vk  1. Updated for Release of LTE RRC 1.1.
/main/9      ---      cm_xta_h_001.main_8 mp  1. Two new flags added for DNS 
/main/10     ---      cm_xta_h_001.main_9 mp  1. Two new flags added for DNS 
                                                 enhancement under sip GPR 26 release.
/main/11     ---      cm_xta_h_001.main_10 gjahagirdar 1. Added two flags for Iuh 2.1 release
/main/12     ---      cm_xta_h_001.main_11 mpatel      1. Added five flags for LTE RRC 3.1 release
/main/13     ---      cm_xta_h_001.main_12      pka     1. Made CMXTA_NODES as configurable 
                                                if it is required to changed.
/main/14     ---      cm_xta_h_001.main_13 vvashishth   1. Changed the macro CMXTA_MAX_FLAGS. 
*********************************************************************91*/
