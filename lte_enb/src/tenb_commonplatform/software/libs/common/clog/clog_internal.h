/*****************************************************************************
 *
 * $Id: clog_internal.h 28631 2010-07-24 13:19:22Z mmcternan $
 *
 * Copyright (C) Radisys Ltd
 *
 *****************************************************************************/

/** \file
 * Structures and macros common to the client and server modules.
 * This gives types and structures not meant for end user code but are instead
 * common to the client and server modules.
 */

#ifndef CLOG_INTERNAL_H
#define CLOG_INTERNAL_H

/*****************************************************************************
 * Header Files
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "system/Trace.h"
#include "clog.h"

/*****************************************************************************
 * Preprocessor Macros & Constants
 *****************************************************************************/

#if defined(DEBUG)
#define ClogAssert(c, ...)  assert(c)
#define ClogFail(...)       assert(false)
#elif !defined(NDEBUG)
#define ClogAssert          RSYS_ASSERT_PRINTF
#define ClogFail            RSYS_ASSERT_FAIL
#else
#define ClogAssert(c, ...)
#define ClogFail(...)
#endif

/** Size of the logging circular buffer in bytes.
 * This gives the size of the shared logging buffer.  We know the kernel uses
 * 4k pages of memory when mapping to processes, so this size should be a
 * multiple of 4k minus the management structure overheads to avoid wastage.
 */
#define CLOG_SIZE             ((4096*4) - M_Round32(sizeof(clog_t)))

/** Listening port on this host.
 */
#define CLOG_PORT             7878

/** Shared memory key value for identifying the shared memory.
 */
#define CLOG_SHM_KEY        0x7778

/** Length bit value to indicate a message is pending being ClogFree()'d.
 */
#define CLOG_LEN_PENDING    0x8000

/** Magic message length to indicate the end of the circular buffer is reached.
 * The clogging code inserts a message of this type once the circular buffer
 * is filled and the next messages start at the bottom of the buffer.
 */
#define CLOG_LEN_WRAP       0xffff

/** Length value to indicate that a clog_hdr_t hasn't yet been populated.
 */
#define CLOG_LEN_FREE            0

/** Casting macro.
 * This converts a passed buffer index to a \a clog_hdr_t pointer.
 * This needs to be used with care since if \a v is not of the correct
 * alignment the produced code will fail.
 */
#define M_clog_hdr_t(idx)                                     \
({                                                            \
    uint32_t _idx = idx;                                      \
    ClogAssert((_idx & 3) == 0,                               \
               "Maligned clog_hdr_t: %u", _idx);              \
    ClogAssert(_idx <= CLOG_SIZE - sizeof(clog_hdr_t),        \
               "Out-of-bounds clog_hdr_t: %u %u",             \
               _idx, CLOG_SIZE - sizeof(clog_hdr_t));         \
    (clog_hdr_t *)&clog->buffer[_idx];                        \
})


/** Round a value to a 32-bit boundary.
 */
#define M_Round32(v)        (((v) + 3) & ~3)

/*****************************************************************************
 * Typedefs
 *****************************************************************************/

/** Message structure for a logging drop record.
 */
typedef uint32_t clog_msg_drop_record_t;


/** Message structure for logging an event.
 */
typedef struct
{
    uint32_t data;
}
clog_msg_event_t;


/** Local message type.
 * This defines the message structures which can be sent directly from the
 * CLogger infrastructure.
 */
union clog_msg_data
{
    clog_msg_drop_record_t dropRecord;
    clog_msg_event_t       event;
};


/** Circular buffer message header structure.
 */
typedef struct
{
    uint16_t            type;
    uint16_t            len;
    union clog_msg_data data[];
}
clog_hdr_t;


/** A whole clogger context.
 * This is the structure that is mapped into each processes address space.
 *
 * \note Pointers cannot be contained in this structure since it may map to
 *       a different virtual address in each process.  Therefore indices into
 *       the buffer are used instead.
 */
typedef struct
{
    /** Message filter.
     * This contains a boolean per message type to indicate which messages are
     * enabled.
     */
    bool               filter[NUM_CLOG_MSG];

    /** Count giving the number of times the filter has been updated.
     * This is used with a futex to determine when the messaging filter
     * has changed.
     */
    uint32_t           filterGeneration;

    /** Head and tail and middle indexes into the circular log buffer.
     * Data is allocated from the buffer head using ClogAlloc(), while the
     * mid pointer is advanced by ClogFree().  The data sending thread advances
     * the tail towards the mid pointer as data is freed.
     */
    uint32_t           bufferHead, bufferMid, bufferTail;

    /** Record of wrap marker location.
     * When the ClogAlloc() inserts a wrap marker, it also updates this count
     * with the marker position.  The server process, upon finding the
     * bufferMid < bufferTail can then use this count to determine how many
     * valid log bytes exist between bufferTail and the end of the buffer.
     */
    uint32_t           bufferWrap;

    /** Counter of unlogged bytes due to circular buffer being full.
     */
    uint32_t           dropped;

    /** Circular log buffer storage.
     */
    uint8_t            buffer[];
}
clog_t;

/*****************************************************************************
 * Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 * Global Function Declarations
 *****************************************************************************/

void ClogInitInternal(clog_t *shm);

#endif /* CLOG_INTERNAL_H */

