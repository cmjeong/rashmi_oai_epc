///////////////////////////////////////////////////////////////////////////////
//
// rt_fifos.h
//
// Defines and structures for the real time FIFOs used between NAS and AS.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __rt_fifos_h_
#define __rt_fifos_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <FapUserLimits.h>

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

#define PS_AMD_CHANNEL_1    9       // Indicates that this is logical channel 1 PS AM data

#define EOH             0xAAF00F55  // End of header marker.
#define EOM             0x550FF0AA  // End of message marker.

// FIFO devices and numbers.  Device strings

static const char RT_FIFO_DEV_PREFIX[] = "/dev/rtf";

// One FIFO on uplink and downlink for all CS calls
static const u32 UPLINK_CS_MEDIA_FIFO_NUMBER   = 0;
static const u32 DOWNLINK_CS_MEDIA_FIFO_NUMBER = 1;

// The rest of the FIFOs are for PS domain use
// Fifo's 2.... assigned to PS userplane
static const u32 PS_DOMAIN_USER_FIFO_MIN = 2;

// With 3 per PS connection
static const u32 PS_DOMAIN_FIFOS_PER_USER            = 3;
static const u32 PS_DOMAIN_FIFO_UL_PS_DATA_OFFSET    = 0; // Offset from base FIFO ID for a particular user.
static const u32 PS_DOMAIN_FIFO_DL_PS_DATA_OFFSET    = 1;
static const u32 PS_DOMAIN_FIFO_DL_PS_CONTROL_OFFSET = 2;

static const u32 PS_DOMAIN_NUM_USERS = MAX_PS_USERPLANE_CONNECTIONS;
static const u32 PS_DOMAIN_NUM_FIFOS = (PS_DOMAIN_NUM_USERS * PS_DOMAIN_FIFOS_PER_USER);

// Min and max FIFO numbers
static const u32 MIN_FIFO_NUMBER = UPLINK_CS_MEDIA_FIFO_NUMBER;
static const u32 MAX_FIFO_NUMBER = PS_DOMAIN_USER_FIFO_MIN + (PS_DOMAIN_NUM_USERS * PS_DOMAIN_FIFOS_PER_USER) - 1;

// And the total number of FIFOs
static const u32 TOTAL_NUMBER_OF_FIFOS = MAX_FIFO_NUMBER - MIN_FIFO_NUMBER + 1;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    int type;
    int nos_bytes;
    int nos_bits;
    int muiP;
    int head_marker;
    int rrc_sn;       // rrc sequence number to be passed to the RLC from the RRC
} fifo_message_header;

#endif
