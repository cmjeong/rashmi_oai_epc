///////////////////////////////////////////////////////////////////////////////
//
// LedTypes_v3_5.h
//
// TODO: Describe purpose and usage of class(es).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LedTypes_v3_5_h_
#define __LedTypes_v3_5_h_


typedef enum
{
	// 3.5 HW handles 3 LEDs for historical reasons.
	// And the funny numbering is part of it
    LED_RESERVED = 1,
    LED_ALARM	 = 0,
    LED_ACCESS	 = 2
} LedId_v3_5;


#endif
