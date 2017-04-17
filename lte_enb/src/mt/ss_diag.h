

/********************************************************************20**
 
     Name:     System Services -- Logging functions
 
     Type:     C Header file
 
     Desc:     Header file for System Services Logging.
 
     File:     
 
     Sid:      ss_diag.h@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:44:09 2014
 
     Prg:      pakumar
  
*********************************************************************21*/ 
#ifndef __SS_DIAG_H__
#define __SS_DIAG_H__
#include "pthread.h"
 
#define SS_DIAG_INST0            0
#define SS_DIAG_INST1            1

#define SS_DIAG_LVL0             0x1
#define SS_DIAG_LVL1             0x2
#define SS_DIAG_LVL2             0x4
#define SS_DIAG_LVL3             0x8
#define SS_DIAG_LVL4             0x10
#define SS_DIAG_MSG              0x20  /*!< Macro used for Message Hex Dump  level     */
#define SS_DIAG_VAR              0x40   /*!< Macro used for Varible length level  */

#define SS_DIAG_BUF_SIZE_SYSTSK1     4095
#define SS_DIAG_BUF_SIZE_SYSTSK2     4095
#define SS_DIAG_BUF_SIZE_SYSTSK3     4095
#define SS_DIAG_BUF_SIZE_SYSTSK4     4095
#define SS_DIAG_BUF_SIZE_SYSTSK5     4095
#define SS_DIAG_BUF_SIZE_SYSTSK6     4095

#define SS_DIAG_SPL_TOKN         0xfffffff1
#define SS_DIAG_INV_ARG          0xffffffff
#define SS_DIAG_SORT_MARKER      0xfffffffe
#define SS_DIAG_MAX_CIRC_BUF     6
#define SS_DIAG_NUM_CIRBUF_UARM  4
#define SS_DIAG_MIN_BUF_DIFF     4
#define SS_DIAG_SLEEP            10
#define SS_DIAG_MAX_NUM_VAR_BUF  10
#define SS_DIAG_VAR_BUF_LEN      255
/* 
 * @details Macro definition for unpack a U16 into a static array  
 */
#define SS_UNPKU16(_tmpU16) \
{                           \
   _tmpU16 = 0;             \
   _tmpU16 = (U16)PutHiByte(_tmpU16, (U8)pkArray[bytCnt++]); \
   _tmpU16 = (U16)PutLoByte(_tmpU16, (U8)pkArray[bytCnt++]); \
}


/* 
 * @details Get Time stamp for Lower ARM and Upper ARM
 */
#define SS_DIAG_GET_TIME_STAMP(_timeRef)\
{\
   _timeRef=numTti;\
}

#define SS_DIAG_FILE_OPEN(_string, _mode)\
   fopen(_string, _mode);

#define SS_DIAG_FILE_WRITE(src, size, count, dst)\
   fwrite(src, size, count, dst);
 
 

#endif
