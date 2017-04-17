///////////////////////////////////////////////////////////////////////////////
//
// SoftwareRelease.h
//
// Constants and conversion function for software release value.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SoftwareRelease_h_
#define _SoftwareRelease_h_

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

/* Some helpfully named constants.
 * Please extend if required.
 */
static const u32 SrOneDotZero   = 0x01000000;
static const u32 SrOneDotOne    = 0x01010000;
static const u32 SrTwoDotZero   = 0x02000000;
static const u32 SrTwoDotOne    = 0x02010000;

/**
 * Convert u32 release number AABBCCDD to string A.B.C.D
 */
std::string SoftwareReleaseToString(u32 softwareRelease, u8 significantDigits = 0);

#endif
