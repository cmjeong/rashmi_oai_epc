/*****************************************************************************
 *
 * $Id: clog_client.c 29110 2010-08-11 13:43:39Z mmcternan $
 *
 * Copyright (C) Radisys Ltd
 *
 *****************************************************************************/

/** \file
 * Circular logging infrastructure.
 * This is the logging client functions i.e. the functions that allow for the
 * creation log messages.
 */
#define FILE_NAME CLOG_CLIENT

#ifndef HARDWARE_hbs2_3_5

/*****************************************************************************
 * Header Files
 *****************************************************************************/

#include <pthread.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <poll.h>
#include "clog_internal.h"
#include "system/Expect.h"

/*****************************************************************************
 * Preprocessor Macros & Constants
 *****************************************************************************/

/** Number of callback functions that can be registered for filter changes.
 */
#define MAX_FILTER_CALLBACKS 8

/*****************************************************************************
 * Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Local Variable Definitions
 *****************************************************************************/

/** The logging data buffer.
 * This is the pointer to the shared memory segment containing the logging
 * structures.
 */
static clog_t            *clog = NULL;

/** Message filter callbacks.
 */
static clog_filter_func_t clogFilterCallback[MAX_FILTER_CALLBACKS];

/** Count of message filter callbacks that have been registered.
 */
static uint8_t            clogFilterCallbackCount = 0;

/*****************************************************************************
 * Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 * Local Function Definitions
 *****************************************************************************/

/** Thread function to run the filter change callbacks when required.
 * This function monitors the logging filter generation count and uses a
 * futex to wait until it changes.  When ever the filter generation changes
 * the registered callback functions are executed.
 */
static void *filterCallbackWorker(void *param __attribute__((__unused__)))
{
    TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Started filter change callback thread");

    while(1)
    {
        uint32_t n, c = clog->filterGeneration;

        /* Wait for the filter generation to change */
        while(c == clog->filterGeneration)
        {
            syscall(SYS_futex, &clog->filterGeneration, FUTEX_WAIT, c, NULL, NULL, 0);
        }

        TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Filter changed: Running %u callback(s)",
                         clogFilterCallbackCount);

        /* Run the registered callbacks */
        for(n = 0; n < clogFilterCallbackCount && n < MAX_FILTER_CALLBACKS; n++)
        {
            if(clogFilterCallback[n] != NULL)
            {
                clogFilterCallback[n]();
            }
        }
    }

    return NULL;
}


/** Get free buffer space from the head to the end without wrapping.
 * This returns the contigious free bytes from the current header.
 *
 * \note The headLock needs to be held when calling this function to ensure
 *        that the count returned is still available after the return i.e.
 *        the head is not advanced  after the function returns.
 *        The tailLock is not needed if the amount of free space is allowed
 *        to increase after the function call.
 */
static uint16_t cFreeNoWrap(const uint32_t idx)
{
    ClogAssert(idx < CLOG_SIZE, "Invalid index: %u", idx);

    if(clog->bufferTail > idx)
        return clog->bufferTail - idx;
    else
        return CLOG_SIZE - idx;
}


/** Get free buffer space from the buffer start to the tail.
 * This returns the contigious free bytes at the start of the buffer as though
 * the buffer had just wrapped.  If the first bytes are occupied, 0 is returned.
 */
static uint16_t cFreeWrap(const uint32_t idx)
{
    ClogAssert(idx < CLOG_SIZE, "Invalid index: %u", idx);

    if(clog->bufferTail > idx)
        return 0;
    else
        return clog->bufferTail;
}

/*****************************************************************************
 * Global Function Definitions
 *****************************************************************************/

/** Initialise a client connection to the clogging interface.
 * This finds and attaches the shared memory segment used for logging.
 * The segment is created by the server process clogd, which must already
 * be running somewhere on the system when this call is made.
 */
void ClogInit(void)
{
    int shmid;

    /* Check initialisation only happens once */
    if(clog != NULL)
    {
        TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Already initialised");
        return;
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Initialising lock-free cs");
    }

    /* Get the idenitifer for the shared memory */
    shmid = shmget(CLOG_SHM_KEY, sizeof(clog_t) + CLOG_SIZE, S_IRWXU);
    if(shmid == -1)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Failed to find shared memory: %m");
        return;
    }

    /* Now attach the shared memory */
    clog = shmat(shmid, NULL, 0);
    if(clog == (void *)-1)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Failed to attach shared memory: %m");
        return;
    }

    TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Attached logging shared memory segment at %p", clog);
}


/** Internal initialisation function.
 * This allows initialisation of the CLogging client API in the case that a
 * pointer to the shared memory segment is already available.  This is
 * principally present to allow the server process to use the client API without
 * re-mapping the shared memory.
 *
 * \param[in] shm  Pointer to the shared clog_t structure.
 */
void ClogInitInternal(clog_t *shm)
{
    /* Check initialisation only happens once */
    if(clog != NULL)
    {
        ClogFail("CLog: Already initialised");
        return;
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Initialising lock-free cs");
    }

    clog = shm;

    TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Using existing shared memory segment at %p", clog);
}


/** Allocate storage for a clog message.
 * This allocates a message buffer.  The buffer should be quickly filled with
 * the data to log, and then returned using ClogFree().
 */
bool ClogAlloc(const clog_msg_type_t type, uint16_t len, clog_msg_data_t **buf)
{
    /* Clear return buffer by default */
    *buf = NULL;

    /* Check filter to see if message type is enabled and Clogger is intialised */
    if(clog == NULL || !clog->filter[type])
    {
        return false;
    }

    /* Round up the length to a 32-bit boundary + a message header */
    len = M_Round32(len) + sizeof(clog_hdr_t);

    /* Reject things that can't be logged */
    ClogAssert(len < CLOG_SIZE,
               "CLog message too long: %" PRIu16 ", limit %" PRIu16,
               len, CLOG_SIZE);
    do
    {
        uint32_t idx = clog->bufferHead;
        uint32_t nextIdx = idx + len;

        /* Check if the message drops right with space for another header.
         *  Note we need to have space for 1 extra header at the end of the
         *  message.  This is to ensure the head doesn't meet the tail and also
         *  to allow insertion of a wrap marker before the next allocation if
         *  needed.
         */
        if(likely(len + sizeof(clog_hdr_t) <= cFreeNoWrap(idx)))
        {
            /* Try to reserve a buffer */
            if(__sync_bool_compare_and_swap(&clog->bufferHead, idx, nextIdx))
            {
                clog_hdr_t *hdr = M_clog_hdr_t(idx);

                /* We now have a buffer */
                hdr->len  = len | CLOG_LEN_PENDING;
                hdr->type = type;
                *buf = hdr->data;

                return true;
            }
        }
        /* Check if the buffer can wrap to take the message */
        else if(likely(len + sizeof(clog_hdr_t) <= cFreeWrap(idx)))
        {
            /* Try inserting a wrap marker */
            if(__sync_bool_compare_and_swap(&clog->bufferHead, idx, 0))
            {
                /* Update the wrap location, then set the wrap marker.
                 *  Potentially another thread could be freeing blocks and
                 *  advancing bufferMid, so we have to ensure the wrap index
                 *  is set before this header is updated from free to a wrap
                 *  marker.
                 */
                clog->bufferWrap = idx;
                __sync_synchronize();
                M_clog_hdr_t(idx)->len = CLOG_LEN_WRAP;
            }
        }
        else
        {
            /* No space */
            __sync_fetch_and_add(&clog->dropped, len);
            return false;
        }
    }
    while(1);
}


/** The same as ClogAlloc(), except the returned buffer is zero'd.
 * This operates in the same way as ClogAlloc(), but for convenience in the
 * success case it will return a buffer whose contents have been zero'd.  This
 * is useful for logging sparse data structures which need zero initialising.
 *
 * \see ClogAlloc()
 */
bool ClogZalloc(const clog_msg_type_t type, uint16_t len, clog_msg_data_t **buf)
{
    /* This implementation will always allocate a zero'd buffer */
    return ClogAlloc(type, len, buf);
}


/** Free an allocated CLog message buffer.
 * This indicates that the buffer has been populated and that the data should
 * be sent to the logging host.  Any underlying storage maybe recycled once
 * this function has been called, so it is important that the passed \a buf
 * is not used again.
 *
 * \param[in] buf  The logging buffer pointer to free, originally returned by
 *                  ClogAlloc().
 */
void ClogFree(clog_msg_data_t *buf)
{
    clog_hdr_t *hdr = (clog_hdr_t *)((uint8_t *)buf - sizeof(clog_hdr_t));
    bool        recheck, wakeup = false;

    /* Check buffer is valid */
    ClogAssert(((uint32_t)hdr & 3) == 0 && (uint8_t *)hdr >= clog->buffer,
               "CLog: Bad clog buffer: %p", buf);
    ClogAssert((hdr->len & 3) == 0,
               "CLog: Bad clog buffer length: %u %p", hdr->len, buf);
    ClogAssert((hdr->len & CLOG_LEN_PENDING) != 0, "CLog: Buffer not pending: %p", buf);

    /* Mark the buffer as free */
    hdr->len &= ~CLOG_LEN_PENDING;

    /* Now try to advance the mid pointer as much as possible.
     *  Due to out-of-order freeing, we may now be able to advance over
     *  lots of buffers, or maybe a wrap marker.
     */
    do
    {
        const uint32_t oldVal = clog->bufferMid;
        const uint16_t l      = M_clog_hdr_t(oldVal)->len;

        recheck = false;

        /* Stop if the mid has reached the head */
        if(oldVal != clog->bufferHead && l != CLOG_LEN_FREE)
        {
            bool updated = false;

            if(unlikely(l == CLOG_LEN_WRAP))
            {
                updated = __sync_bool_compare_and_swap(&clog->bufferMid, oldVal, 0);
                recheck = true;
            }
            else if((l & CLOG_LEN_PENDING) == 0)
            {
                updated = __sync_bool_compare_and_swap(&clog->bufferMid,
                                                       oldVal,
                                                       oldVal + l);
                recheck = true;
            }

            /* If we updated the mid-pointer we must check if the log thread
             *  was waiting at that point and should now be woken up.
             */
            if(updated && clog->bufferTail == oldVal)
            {
                wakeup = true;
            }
        }

    }
    while(recheck);

    /* If a useful message was freed, wakeup the transfer thread */
    if(likely(wakeup))
    {
        syscall(SYS_futex, &clog->bufferMid, FUTEX_WAKE, 1, NULL, NULL, 0);
    }
}


/** Check if some message is enabled for logging.
 * \param[in] type   The message type to check.
 * \returns true if the message is enabled for logging, false otherwise.
 */
bool ClogMsgEnabled(const clog_msg_type_t type)
{
    /* Range check and ensure Clogging is setup before examining the filter */
    return likely(type < NUM_CLOG_MSG) &&
           likely(clog != NULL) &&
           clog->filter[type];
}


/** Log an event.
 * Events are short messages with only a uint32_t payload.
 *
 * \param[in] id    The event ID.
 * \param[in] data  Data to go with the event.
 */
void ClogEvent(const clog_msg_type_t type, uint32_t data)
{
    clog_msg_data_t *msg;

    /* We could duplicate the allocate and free code here, but not bother
     *  with ever setting a pending state.  This would save a couple of ops
     *  but mainly the assert checking on the Free.
     */

    if(ClogAlloc(type, sizeof(clog_msg_event_t), &msg))
    {
        msg->event.data = data;

        ClogFree(msg);
    }
}


/** Get the generation of the current logging filter.
 * The filter generation is simply a counter which is increased each time
 * the CLogger application sends a new filter.  Numerically it has no meaning,
 * but can be used to detect if the filter has been changed between calls.
 */
uint32_t ClogFilterGeneration(void)
{
    if(clog)
        return clog->filterGeneration;
    else
        return 0;
}


/** Set a callback to be called when the message filter is changed.
 * This registers a callback function to be called when the message filter
 * is updated.  The function is called from the the logging thread so care
 * must be taken that any operations are both brief and thread safe.
 *
 * \param[in] func  The function to call when the message filter is changed.
 */
void ClogFilterCallback(clog_filter_func_t func)
{
    uint8_t oldCount;

    ClogAssert(func != NULL, "CLog: Cannot register NULL callback");

    oldCount = __sync_fetch_and_add(&clogFilterCallbackCount, 1);
    if(oldCount < MAX_FILTER_CALLBACKS)
    {
        clogFilterCallback[oldCount] = func;
    }
    else
    {
        clogFilterCallbackCount = NUM_CLOG_MSG;
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Too many filter callbacks");
    }

    /* Check if this is the first callback to be added */
    if(oldCount == 0 && clog != NULL)
    {
        pthread_t tid;

        pthread_create(&tid, NULL, filterCallbackWorker, NULL);
    }
}

/*****************************************************************************
 * Unit Test Support
 *****************************************************************************/

#ifdef UNITTEST_CLOG

/*Compile with something like:
 * gcc -Wall -Wextra  -g -o clog -DUNITTEST_CLOG -D_REENTRANT infra/clog.c infra/devcheck.c infra/log.c -DREM -I infra/ -I l1/ -I ../../../libs/ -I ../../../libs/common/ -I../../../libs/messaging/messages/cphy -I ../../../libs/common/include/ -Inode-b -lpthread -rdynamic -lm
 */


/** Generator thread.
 * This creates messages where the Id is the thread index and the body is
 * a single uint32_t giving a sequence number.  This allows the checking
 * program to ensure that the output from each thread is not corrupted.
 *
 * \note We don't use an Id of 0 as that would clash with any drop records.
 */
void *genThread(void *p)
{
    uint32_t idx = (uint32_t)p + 1;
    uint32_t x, n = 0;

    for(x = 0; x < 10000; x++)
    {
        clog_msg_data_t *buf;

        if(ClogZalloc(idx, sizeof(uint32_t) + idx, &buf))
        {
            uint32_t *p =  (uint32_t *)buf;

            *p = n++;

            ClogFree(buf);
        }

usleep(10000);
    }

    return NULL;
}

static void filterFunc(void)
{
    fprintf(stderr, "Filter change callback called\n");
}

#define N_THREADS 20

int main(int argc, char *argv[])
{
    pthread_t tid[N_THREADS];
    uint32_t  t;

    Trace_EnableStdoutLogging();

    if(argc == 1)
    {
        ClogInit();

    sleep(1);

    ClogFilterCallback(filterFunc);

        for(t = 0; t < N_THREADS; t++)
          pthread_create(&tid[t], NULL, genThread, (void *)t);

        for(t = 0; t < N_THREADS; t++)
          pthread_join(tid[t], NULL);
    }
    else
    {
        ClogRunServer();
    }


    return 0;
}
#endif

#endif /* HARDWARE_hbs2_3_5 */

/* END OF FILE */
