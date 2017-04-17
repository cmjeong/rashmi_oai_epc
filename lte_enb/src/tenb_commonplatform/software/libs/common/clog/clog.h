/*****************************************************************************
 *
 * $Id: clog.h 29110 2010-08-11 13:43:39Z mmcternan $
 *
 * Copyright (C) Radisys Ltd
 *
 *****************************************************************************/

#ifndef CLOG_H
#define CLOG_H

/*****************************************************************************
 * Header Files
 *****************************************************************************/

#include <stdint.h>

/*****************************************************************************
 * Preprocessor Macros & Constants
 *****************************************************************************/

/** Macro to check if the CLogging filter has changed.
 * This returns \a true if the CLogging filter has changed since the last
 * time the macro was called.  Use of the function is call-site specific
 * such that different bits of code may call the macro to check if the filter
 * changed and each will be returned \a true once.
 */
#define ClogFilterChanged()                                \
({                                                         \
    static uint32_t _gen = 0;                              \
    uint32_t _genNow = ClogFilterGeneration();             \
    bool     _r = _gen != _genNow;                         \
                                                           \
    _gen = _genNow;                                        \
    _r;                                                    \
})

/*****************************************************************************
 * Typedefs
 *****************************************************************************/

/** Type for a filter callback function.
 */
typedef void (*clog_filter_func_t)(void);


/** Commands from the logging client to control the target.
 */
typedef enum clog_cmd_type_tag
{
    CLOG_CMD_FILTER_ALL_OFF,
    CLOG_CMD_FILTER_ENABLE_BULK,
    CLOG_CMD_KEEPALIVE,

    NUM_CLOG_CMD
}
clog_cmd_type_t;


/** Different log message types.
 *
 * \note Only add messages to the end of this enumeration to ensure
 *        back/forward compatability.  Similarly don't ever remove elements.
 */
typedef enum clog_msg_type_tag
{
    CLOG_MSG_DROP_RECORD,
    CLOG_MSG_SEARCHER_RESULTS,
    CLOG_MSG_REG_READ,
    CLOG_MSG_REG_WRITE,
    CLOG_MSG_RAKE_STAT_PHASE,
    CLOG_MSG_RAKE_STAT_DPCCH,
    CLOG_MSG_RAKE_STAT_DPDCH,
    CLOG_MSG_AGC,
    CLOG_EVENT_SFN,
    CLOG_MSG_BLER,
    CLOG_MSG_SIR,
    CLOG_MSG_RAKE_TPC_UL,
    CLOG_MSG_RAKE_TPC_DL,
    CLOG_MSG_CPHY_STRUCT,
    CLOG_MSG_UE_MODE,
    CLOG_EVENT_MPS_START,
    CLOG_EVENT_MPS_STOP,
    CLOG_MSG_AIR_RATE,
    CLOG_MSG_DLPC,
    CLOG_MSG_VITERBI_CORRECTIONS,
    CLOG_MSG_CM_INFO,
    CLOG_MSG_BER_STAT,
    CLOG_EVENT_RLF,

    CLOG_MSG_MESSENGER,       /**< Serialised C++ Messenger data. */
    CLOG_MSG_TIMEOFDAY,       /**< Current result from gettimeofday() */

    NUM_CLOG_MSG
}
clog_msg_type_t;


/** Type for a log message.
 * Message data is declared as a union which isn't yet defined.  This enables
 * different users of the library to define the union to a convenient type
 * while not requiring this library to include all headers for every message
 * type.
 */
typedef union clog_msg_data clog_msg_data_t;

/*****************************************************************************
 * Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 * Global Function Declarations
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CLOG_PARSING

void     ClogInit(void);
bool     ClogAlloc(const clog_msg_type_t type, uint16_t len, clog_msg_data_t **buf);
bool     ClogZalloc(const clog_msg_type_t type, uint16_t len, clog_msg_data_t **buf);
void     ClogFree(clog_msg_data_t *buf);
void     ClogEvent(const clog_msg_type_t type, uint32_t data);
bool     ClogMsgEnabled(const clog_msg_type_t type);
void     ClogFilterCallback(clog_filter_func_t func);
void     ClogRunServer(void);
uint32_t ClogFilterGeneration(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* CLOG_H */

