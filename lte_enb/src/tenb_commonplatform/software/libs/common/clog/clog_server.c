/*****************************************************************************
 *
 * $Id: clog_server.c 29110 2010-08-11 13:43:39Z mmcternan $
 *
 * Copyright (C) Radisys Ltd
 *
 *****************************************************************************/

/** \file
 * Circular logging infrastructure.
 * This implements a circular buffer and simple protocol over TCP.
 * The circular buffer supports multiple writers of log messages which are then
 * collected by the logging thread and sent via TCP.  Log message filtering
 * can be controlled through the TCP connection, allowing selected messages
 * to be enabled or disabled.
 *
 * Each process or thread that wishes to add messages to the buffer must
 * first map the shared memory structure into it's address space.  It can
 * then write data directly into the buffer and update the variables as needed.
 *
 * Concurrency is managed by careful use of 3 pointers; buffer head, mid and
 * tail.  The head pointer is manipulated only by CLogAlloc(), and access to
 * this pointer is made by atomic updates.  The head pointer represents the
 * first free byte of the circular buffer, and is where new messages are
 * allocated.  CLogFree() manipulates only the mid pointer.  It advances
 * the mid pointer towards the head pointer as buffers are determined to be
 * ready for logging.  Access to the mid pointer is also performed by atomic
 * operations.
 *
 * Finally the logging thread manipulates the tail pointer only.  Since there
 * is only 1 logging thread, little protection is needed, although a futex
 * is used to control when the thread should run.  The logging thread advances
 * the tail pointer towards the mid pointer.
 *
 * The buffer is completely empty when all three pointers are equal.  The
 * pointers are always arranged such that the tail <= mid <= head in logging
 * order, but due to buffer wrapping this may not hold true for the address
 * values.
 *
 * The GCC builtins for atomic operations are used extensively in this
 * lock-free implementation.  The lockless nature ensures low overhead when
 * making and freeing allocations and removes any need for a context switch.
 * Blocking due to contention is also completely avoided.  Instead, concurrent
 * operations may cause atomic updates to sometimes fail.  In such a case the
 * operation is simply recalculated and retried.  This gives a spin-lock like
 * behaviour although it is unlikely that locking is attempted more than twice
 * since unless a context switch occurs after the first lock attempt, the second
 * will try will succeed.
 *
 * Finally, since the scheduling quantum is very large compared with the number
 * of instructions required to make an allocation or free, failed lock events
 * will also be rare.
 */
#define FILE_NAME CLOG_SERVER

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
#include "system/Trace.h"

/*****************************************************************************
 * Preprocessor Macros & Constants
 *****************************************************************************/

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

/*****************************************************************************
 * Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 * Local Function Definitions
 *****************************************************************************/

/** Dump the buffer to the console for debugging.
 */
static void __attribute__((__used__)) dumpBuffer(void)
{
    FILE       *outfile = stderr;
    clog_hdr_t *h;
    uint32_t    idx;

    fprintf(outfile, "buffer=%p\n", clog->buffer);
    fprintf(outfile, "tail=%u mid=%u head=%u\n",
            clog->bufferTail, clog->bufferMid, clog->bufferHead);

    fprintf(outfile, "Walk from the buffer tail:\n");
    idx = clog->bufferTail;
    do
    {
        h = M_clog_hdr_t(idx);

        fprintf(outfile, "  %p: len=0x%04x%s%s%s%s type=0x%04x %s%s%s%s\n",
               h,
               h->len,
               h->len & CLOG_LEN_PENDING ? "[P]" : "",
               h->len == CLOG_LEN_WRAP ? "[W]" : "",
               h->len == CLOG_LEN_FREE ? "[F]" : "",
               (h->len & 3) != 0 ? "!" : "",
               h->type,
               idx == clog->bufferTail ? "tail " : "",
               idx == clog->bufferMid ? "mid " : "",
               idx == clog->bufferHead ? "head " : "",
               idx ==0 ? "buffer " : "");

        if(h->len == CLOG_LEN_WRAP)
            idx = 0;
        else
            idx  += h->len & ~CLOG_LEN_PENDING;
    }
    while(idx != clog->bufferHead);

    h = M_clog_hdr_t(idx);

    fprintf(outfile, "  %p: len=0x%04x%s%s%s%s type=0x%04x %s%s%s%s\n",
            h,
            h->len,
            h->len & CLOG_LEN_PENDING ? "[P]" : "",
            h->len == CLOG_LEN_WRAP ? "[W]" : "",
            h->len == CLOG_LEN_FREE ? "[F]" : "",
            (h->len & 3) != 0 ? "!" : "",
            h->type,
            idx == clog->bufferTail ? "tail " : "",
            idx == clog->bufferMid ? "mid " : "",
            idx == clog->bufferHead ? "head " : "",
            idx == 0 ? "buffer " : "");
}


/** Signal processes that the filter has changed.
 * This notifies any waiting processes that the filter has changed.  Any
 * registered callbacks may then be executed by the clients.
 */
static void runFilterCallbacks(void)
{
    /* Increase the filter generation */
    __sync_fetch_and_add(&clog->filterGeneration, 1);

    /* Wake anything waiting */
    syscall(SYS_futex, &clog->filterGeneration, FUTEX_WAKE, INT_MAX, NULL, NULL, 0);
}


/** Handle a command from the remote logging host.
 * \param[in] fd     The client socket from which to recieve.
 * \returns   false  If the socket was found to be disconnected.
 */
static bool handleCmd(int fd)
{
    clog_cmd_type_t cmd;
    bool            connected;

    /* Get the mesage and check it's still connected */
    connected = (recv(fd, &cmd, sizeof(clog_cmd_type_t), 0) == sizeof(clog_cmd_type_t));

    if(!connected) return false;

    switch(cmd)
    {
        case CLOG_CMD_KEEPALIVE:
            /* Do nothing; TCP acks will confirm everything needed */
            break;

        case CLOG_CMD_FILTER_ALL_OFF:

            TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Got all off filter command");
            memset(clog->filter, 0, sizeof(clog->filter));

            runFilterCallbacks();
            break;

        case CLOG_CMD_FILTER_ENABLE_BULK:
        {
            uint16_t n, msg;

            /* Get count of messages to enable */
            recv(fd, &n, sizeof(n), 0);
            TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Got bulk enable filter command: n=%" PRIu16, n);

            while(n > 0)
            {
                recv(fd, &msg, sizeof(msg), 0);
                if(msg < NUM_CLOG_MSG)
                {
                    clog->filter[msg] = true;
                }
                else
                {
                    TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Out of range msg id: %" PRIu16, msg);
                }

                n--;
            }

            runFilterCallbacks();
            break;
        }
        default:
            TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Unrecognised cmd: %" PRIu8, cmd);
            break;
    }

    return true;
}


/** Completely send a buffer to the logging host.
 * This sends the passed buffer to the remote logging host, looping to ensure
 * short writes are correctly handled if needed.
 *
 * \param[in] fd  File descriptor for for the remote host.
 * \param[in] ptr Pointer to the buffer to be sent.
 * \param[in] len Length of the buffer in bytes.
 * \returns false if the write failed and the connection has been lost.
 */
static bool sendComplete(const int fd, const void *ptr, uint16_t len)
{
    bool        connected = true;
    const char *buf = ptr;
    ssize_t     v;

    do
    {
#ifndef DEBUG_FILE_OUT
        v = send(fd, buf, len, MSG_NOSIGNAL);
#else
        v = write(fd, buf, len);
#endif
        if(unlikely(v == -1))
        {
            connected = false;
        }
        else
        {
            buf += v;
            len -= v;
        }
    }
    while(unlikely(len > 0) && likely(connected));

    return connected;
}


/** Send data from the circular buffer to the passed file descriptor.
 *
 * \param[in] fd     The file descriptor into which data should be sent.
 */
static bool sendData(const int fd)
{
    uint32_t    tail = clog->bufferTail;
    uint32_t    mid   = clog->bufferMid;
    clog_hdr_t *hdr   = M_clog_hdr_t(tail);
    bool        connected = true;

    /* Simple non-wrapping case */
    if(tail < mid)
    {
        uint32_t len = mid - tail;

        /* Send the data */
        connected = sendComplete(fd, hdr, len);

        /* Wipe the buffer data */
        memset(hdr, 0, len);

        /* Update the tail */
        __sync_bool_compare_and_swap(&clog->bufferTail, clog->bufferTail, mid);
    }
    else if(tail > mid) /* Wrap case */
    {
        uint32_t len = clog->bufferWrap - tail;

        /* Send the data */
        connected = sendComplete(fd, hdr, len);

        /* Wipe the buffer data + wrap marker */
        memset(hdr, 0, len + sizeof(clog_hdr_t));

        /* Update the tail with a wrap */
        __sync_bool_compare_and_swap(&clog->bufferTail, clog->bufferTail, 0);
    }

    return connected;
}


/** Send a drop record to the logging host and reset the drop counter.
 *
 * \param[in] fd  The file descriptor for writing to the logging host.
 */
static bool sendDropped(int fd)
{
    const uint16_t len = sizeof(clog_hdr_t) + sizeof(clog_msg_drop_record_t);
    clog_hdr_t    *hdr;

    /* Allocate message on the stack */
    hdr = alloca(len);
    hdr->len  = len;
    hdr->type = CLOG_MSG_DROP_RECORD;

    /* Now get and reset the drop count */
    do
    {
        hdr->data[0].dropRecord = clog->dropped;
    }
    while(!__sync_bool_compare_and_swap(&clog->dropped, hdr->data[0].dropRecord, 0));

    /* Send the message */
    return sendComplete(fd, hdr, len);
}


/** Create the Clogger server socket.
 *
 * \returns The socket file descriptior, or -1 if an error occured.
 */
static int createServerSocket(void)
{
    int                server;
#ifndef DEBUG_FILE_OUT
    struct sockaddr_in addr;
    int                v = 1;

    /* Create socket */
    server = socket(AF_INET, SOCK_STREAM, 0);
    ClogAssert(server != -1, "CLog: failed to create socket");

    /* Allow local address reuse */
    if(setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(v)))
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: setsockopt() failed");
    }

    /* Try to bind and start listening for connections */
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CLOG_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server, (struct sockaddr*)&addr, sizeof(addr)) == -1 || listen(server, 5) == -1)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: bind() failed: %m");
        close(server);
        server = -1;
    }
#else
    /* Stdout */
    server = 0;
#endif

    return server;
}


/*****************************************************************************
 * Global Function Definitions
 *****************************************************************************/

/** Starts the CLog server process.
 * This creates or attaches to a logging shared memory segment and then sets
 * it up for logging.  A server socket is then created before the function
 * forks a child which enters the server handling loop.
 * Upon return a CLog server will be running, and the CLog client API will
 * also have been initialised for use.
 */
void ClogRunServer(void)
{
    int   shmid, server;

    /* Try to find existing shared memory segment */
    shmid = shmget(CLOG_SHM_KEY, sizeof(clog_t) + CLOG_SIZE, IPC_CREAT | S_IRWXU);
    if(shmid == -1)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Failed to create shared memory: %m");
        return;
    }

    /* Now attach the shared memory */
    clog = shmat(shmid, NULL, 0);
    if(clog == (void *)-1)
    {
        clog = NULL;
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Failed to attach shared memory: %m");
        return;
    }

    TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Attached logging shared memory segment at %p", clog);

    /* Initialise the buffer */
    memset(clog, 0, sizeof(clog_t) + CLOG_SIZE);
    clog->bufferHead = clog->bufferMid = clog->bufferTail = 0;
    clog->dropped = 0;

    /* Initialise the client side */
    ClogInitInternal(clog);

    /* Create the server socket */
    server = createServerSocket();
    if(server == -1)
    {
        clog = NULL;
        TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: Failed to bind or listen to server socket; clogging disabled");
        return;
    }

#ifndef DEBUG_FILE_OUT
    /* Now drop into the background; the shm & socket are ready */
    if(fork() != 0)
    {
        close(server);
        return;
    }
#endif

    while(1)
    {
        socklen_t          saddrLen = sizeof(struct sockaddr);
        struct sockaddr_in saddr;
        bool               connected;
        int                client;
        struct pollfd      pollfd;

        /* Clear the log filter when disconnected */
        memset(clog->filter, 0, sizeof(clog->filter));
        runFilterCallbacks();

#ifndef DEBUG_FILE_OUT
        TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Waiting for client connection to port %" PRIu16, CLOG_PORT);

        /* Accept a client connection */
        client = accept(server, (struct sockaddr *)&saddr, &saddrLen);
        if(client != -1)
        {
            TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Client accepted from %s", inet_ntoa(saddr.sin_addr));

            /* Setup poll structure */
            pollfd.fd = client;
            pollfd.events = POLLIN;
            pollfd.revents = 0;

            connected = true;
        }
        else
        {
            connected = false;
        }
#else
        if(strcmp(DEBUG_FILE_OUT, "-") == 0)
           client = STDOUT_FILENO;
        else
           client = open(DEBUG_FILE_OUT, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        ClogAssert(client != -1, "Failed to open output file: %m");
        connected = true;
#endif

        /* Clear the logging buffer and pointers.
         *  This can be done because the logging filter will be clear so
         *  these data are not being accessed by client code.
         */
        memset(clog->buffer, 0, CLOG_SIZE);
        clog->bufferHead = clog->bufferMid = clog->bufferTail = 0;
        clog->dropped = 0;

#ifdef DEBUG_FILE_OUT
        /* For file logging, set filter to pass everything */
        memset(clog->filter, 1, sizeof(clog->filter));
#endif
        /* Data transfer loop */
        do
        {
            static const struct timespec timeout = { .tv_nsec = 0, .tv_sec = 2 };
            int                          err;

#ifndef DEBUG_FILE_OUT
            /* Check if there is data to recieve */
            while(unlikely(poll(&pollfd, 1, 0) == 1) && connected)
            {
                connected = handleCmd(client);
            }
#endif
            /* Check if we need to wait for more data */
            if(clog->bufferTail == clog->bufferMid)
            {
                /* Wait, but not indefinitely since we need to poll for data.
                 *  Note: We get 0 back if woken up, -1 & ETIMEDOUT if the timeout
                 *         occured and EWOULDBLOCK/EAGAIN in the case that midVal
                 *         already differs from clogBufferMid.
                 */
                err = syscall(SYS_futex, &clog->bufferMid, FUTEX_WAIT, clog->bufferTail, &timeout, NULL, 0);err = syscall(SYS_futex, &clog->bufferMid, FUTEX_WAIT, clog->bufferTail, &timeout, NULL, 0);
                if(err != 0 && errno != EWOULDBLOCK && errno != ETIMEDOUT)
                {
                    TRACE_PRINTF_LEV(TRACE_WARNING, "CLog: futex() failed (err=%d errno=%m)", err);
                    connected = false;
                }
            }

            /* Check if there is data to send and send it */
            if(likely(connected))
            {
                connected = sendData(client);
                if(likely(connected) && unlikely(clog->dropped != 0))
                {
                    connected = sendDropped(client);
                }
            }
        }
        while(likely(connected));
    }

    TRACE_PRINTF_LEV(TRACE_INFO, "CLog: Worker returning");
}

#endif /* HARDWARE_hbs2_3_5 */

/* END OF FILE */
