/*
 * $Id: clogparser.c 28555 2010-07-22 14:29:58Z mmcternan $
 *
 * Read a clog stream and check syntax & contents.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define NUM_THREADS 200

static uint16_t threadCounter[NUM_THREADS];

static uint16_t readU16(FILE *f)
{
    uint16_t v;

    fread(&v, sizeof(uint16_t), 1, f);

    return v;
}


static uint8_t readU8(FILE *f)
{
    uint8_t v;

    fread(&v, sizeof(uint8_t), 1, f);

    return v;
}

int main(int argc, char *argv[])
{
    uint16_t msg, len, t;
    FILE *f;

    memset(threadCounter, 0, sizeof(threadCounter));

    if(argc != 2)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "-") == 0)
    {
        f = stdin;
    }
    else
    {
        f = fopen(argv[1], "rb");
    }

    if(!f)
    {
        TRACE_PRINTF("Failed to open file: %m\n");
        return EXIT_FAILURE;
    }

    do
    {
        msg = readU16(f);
        len = readU16(f);

        if(feof(f))
        {
            break;
        }

        TRACE_PRINTF("Msg: %x %d ", msg, len);
        if(len < 4)
        {
            TRACE_PRINTF("Invalid length: %" PRIu16, len);
        }
        else
        {
            union {
                uint32_t w;
                uint8_t  b[4];
            } data;

            uint16_t n = 0, c;

            len -= 4;
            c = len;
            TRACE_PRINTF("{ ");

            while(c > 0)
            {
                uint8_t b = readU8(f);

                if(n < sizeof(data.b))
                {
                    data.b[n++] = b;
                }

                TRACE_PRINTF("0x%02x ", b);
                c--;
            }

            TRACE_PRINTF("} ");

            /* Compute the length of the message */
            uint16_t idealLen = (msg + sizeof(uint32_t) + 3) & ~3;

            if(n == 4 && msg < NUM_THREADS && threadCounter[msg] == data.w && len == idealLen)
            {
                threadCounter[msg]++;
                TRACE_PRINTF("OK\n");
            }
            else if(msg == 0)
            {
                TRACE_PRINTF("DROP %d\n", data.w);
            }
            else
            {
                TRACE_PRINTF("BAD (%08x vs %0x8) (%u %u)\n", threadCounter[msg], data.w, msg, idealLen);
            }
        }
    }
    while(!feof(f));

    TRACE_PRINTF("Final counter values:\n");
    for(t = 1; t < NUM_THREADS && threadCounter[t] != 0; t++)
    {
        TRACE_PRINTF("%02d: %08x\n", t, threadCounter[t]);
    }

    return 0;
}
