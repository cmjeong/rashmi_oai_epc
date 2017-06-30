///////////////////////////////////////////////////////////////////////////////
//
// SerialisationIds.h
//
// Contains all our serialisation IDs so it is easier to manage their
// uniqueness.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __SerialisationIds_h_
#define __SerialisationIds_h_

#include <inttypes.h>
  
    typedef uint8_t     u8;
    typedef uint16_t    u16;
    typedef uint32_t    u32;
    typedef uint64_t    u64;
    typedef int8_t      s8;
    typedef int16_t     s16;
    typedef int32_t     s32;
	
	#define SERIALISATION_ID_WATCHDOG_BASE                 0x4700
    #define SERIALISATION_ID_WATCHDOG_ADD_PID_REQ          0x4701
    #define SERIALISATION_ID_WATCHDOG_REMOVE_PID_REQ       0x4702
    #define SERIALISATION_ID_WATCHDOG_KICK_REQ             0x4703
    #define SERIALISATION_ID_WATCHDOG_KICK_STOP_REQ        0x4704

#endif
