/*****************************************************************************
 *
 * $Id: clog_stub.c 29110 2010-08-11 13:43:39Z mmcternan $
 *
 * Copyright (C) Radisys Ltd
 *
 *****************************************************************************/

/** \file
 * Null CLogging implementation.
 * This provides a null implementation of the CLogger API for use on platforms
 * which don't support the necessary features to use CLogger.
 */
#define FILE_NAME CLOG_STUB

#ifdef HARDWARE_hbs2_3_5

/*****************************************************************************
 * Header Files
 *****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "clog.h"

/*****************************************************************************
 * Preprocessor Macros & Constants
 *****************************************************************************/

/*****************************************************************************
 * Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Local Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 * Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 * Local Function Definitions
 *****************************************************************************/

/*****************************************************************************
 * Global Function Definitions
 *****************************************************************************/

void ClogInit(void)
{
}


bool ClogAlloc(const clog_msg_type_t type __attribute__((__unused__)),
               uint16_t              len  __attribute__((__unused__)),
               clog_msg_data_t     **buf)
{
    *buf = NULL;
    return false;
}


bool ClogZalloc(const clog_msg_type_t type __attribute__((__unused__)),
                uint16_t              len  __attribute__((__unused__)),
                clog_msg_data_t     **buf)
{
    *buf = NULL;
    return false;
}


void ClogFree(clog_msg_data_t *buf __attribute__((__unused__)))
{

}


void ClogEvent(const clog_msg_type_t type __attribute__((__unused__)),
               uint32_t              data __attribute__((__unused__)))
{
}


bool ClogMsgEnabled(const clog_msg_type_t type __attribute__((__unused__)))
{
    return false;
}


void ClogFilterCallback(clog_filter_func_t func __attribute__((__unused__)))
{
}


uint32_t ClogFilterGeneration(void)
{
    return 0;
}


void ClogRunServer(void)
{
}

#endif /* HARDWARE_hbs2_3_5 */

/* END OF FILE */
