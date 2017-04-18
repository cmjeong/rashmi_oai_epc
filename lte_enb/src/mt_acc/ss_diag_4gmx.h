

/********************************************************************20**
 
     Name:     System Services -- Logging functions
 
     Type:     C Header file
 
     Desc:     Header file for System Services Logging.
 
     File:     
 
     Sid:      
 
     Prg:      pakumar
  
*********************************************************************21*/ 
#ifndef __SS_DIAG_H__
#define __SS_DIAG_H__
 
/* @brief Global declarations */

PUBLIC S16 ssDiagInitBuf ARGS((Void));
 
/* 
 * @brief Logging buffer structure to store the runtime values. At present,
 * fixed length logs supports only 4 run time arguments and one standalone
 * argument
 */
typedef struct _ssDiagBuf
{
   U32       timRef;        /*!< Time tick reference                          */
   U32       tknId;         /*!< Token identifier of the log                  */
   U32       entInstId;     /*!< Layer Entity and instance Id                 */
   U32       level;         /*!< Level of log                                 */
   U32       type;          /*!< Type of log, Message or Event log            */
   U32       splArg;        /*!< Additional standalone argument for sorting   */
   U32       arg1;          /*!< User Argument 1                              */
   U32       arg2;          /*!< User Argument 2                              */
   U32       arg3;          /*!< User Argument 3                              */
   U32       arg4;          /*!< User Argument 4                              */
}SsDiagBuf;

/* 
 * @brief Structure for circular log buffer. This buffer is used for storing
 * run time values of the logging macro
 */
typedef struct _ssDiagCirBuf
{
   U32               front;                  /*!< Start pointer of the circular buffer */
   U32               rear;                   /*!< End pointer of the circular buffer   */
   SsDiagBuf         *logBuf;                /*!< Log buffer used to store values      */
   U32               nLen;                   /*!< length of circular buffer            */
   U8                noLogLost;              /*!< Number of lost log                   */
   U8                logLostState;           /*!< state of logs lost                   */
}SsDiagCirBuf;

typedef enum
{
   SS_DIAG_NORMAL,
   SS_DIAG_RPT_PEND,
   SS_DIAG_REPORTED
} ssDiagLostState;

typedef enum
{
   SS_DIAG_MSG_TYPE_FIXED = 1,       /*!< message type fixed log          */
   SS_DIAG_MSG_TYPE_HEXDUMP,       /*!< message type Message Hex Dump   */
   SS_DIAG_MSG_TYPE_VAR,           /*!< message type Varible length     */
   SS_DIAG_MSG_TYPE_MARKER,         /*!< message type Sort marker to indicate start sort in post processing  */
   SS_DIAG_MSG_TYPE_NOLOGLOST
}SsDiagMsgType; 
/* 
 * @details Macro definition  for ss_log  
 */
#define SS_DIAG_BUF1              0            /*!< buffer used for lower arm core1      */ 
#define SS_DIAG_BUF2              1            /*!< buffer used for lower arm core2      */

#define SS_DIAG_BUF1_LEN          128
#define SS_DIAG_BUF2_LEN          128

#define SS_DIAG_INST0             0
#define SS_DIAG_INST1             1

#define SS_DIAG_MAX_LOG_POST     10

#define SS_DIAG_LVL0              0x1
#define SS_DIAG_LVL1              0x2
#define SS_DIAG_LVL2              0x4
#define SS_DIAG_LVL3              0x8
#define SS_DIAG_LVL4              0x10

#define SS_DIAG_MIN_BUF_DIFF          4
#define SS_DIAG_SPL_TOKN          0x0FF00002
#define SS_DIAG_MAX_CIRC_BUF          2

#define EVTLYSRSYSLOG            10

#define SS_DIAG_INV_ARG           0xFFFFFFFF

EXTERN SsDiagCirBuf ssDiagCirBuf[SS_DIAG_MAX_CIRC_BUF];
EXTERN U32 numTti;
/*
 * TBD time stamp we are using count need to replace with proper time stamp
 * @details Get Time stamp for LARM and UARM
 */
#define SS_DIAG_GET_TIME_STAMP(_timeStamp){\
    _timeStamp=numTti;                \
}


/*
 * @brief Function forward declarations */
EXTERN S16 ssDiagInitCircBuf ARGS((SsDiagCirBuf *bufPtr, U16 maxBufLen));
EXTERN Void ssDiagFix ARGS(( U32 tknId, U32 splArgEnum, U32 entId, U32 instId, U32 logLvl, U32 logType, 
         U32 splArg, U32 arg1, U32 arg2, U32 arg3, U32 arg4, S8 *string));
EXTERN S16 ssDiagSndToPack   ARGS((Pst *pst));
EXTERN S16 ssPackLogs       ARGS((Pst *pst));
/* @brief Private functions forward declarations */
PRIVATE Void ssDiagInitBufEntMap ARGS((Void));
PRIVATE S16 ssDiagGetBufIdx ARGS((SsDiagCirBuf *bufPtr, SsDiagBuf **trgBufPtr));
EXTERN U8 ssDiagBufEntMap[SS_MAX_ENT][SS_MAX_INST];
#endif
