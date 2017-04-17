///////////////////////////////////////////////////////////////////////////////
//
// Airvana.h
//
//
// Definition of basic types.
//
// Copyright Airvana Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Airvana_h_
#define __Airvana_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#include <inttypes.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

static const char DEV_MAN_OUI [] = "0005B9";
static const char ENT_NUMBER [] = "6587";

// BITS_PER_LONG is set in linux/include/asm/types.h where u8 etc are also defined.
// Check this to ensure we don't have duplicate definitions.
#if !defined(BITS_PER_LONG) || defined(__XENO__)
    typedef uint8_t     u8;
    typedef uint16_t    u16;
    typedef uint32_t    u32;
    typedef uint64_t    u64;
    typedef int8_t      s8;
    typedef int16_t     s16;
    typedef int32_t     s32;
#endif

#ifdef HARDWARE_hbs2_4
#  if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4)
//#    error HBS2-4 builds need at least gcc 4.4.x
#  endif
#endif

#endif
