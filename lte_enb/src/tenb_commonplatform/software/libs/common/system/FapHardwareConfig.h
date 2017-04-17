///////////////////////////////////////////////////////////////////////////////
//
// FapHardwareConfig.h
//
// Hardware types, revisions and mod states.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FapHardwareConfig_h_
#define __FapHardwareConfig_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

/* Hardware types and revisions.
 *
 *  See http://ukdev1/wiki/index.php/Hardware_Types_And_Revisions
 *   for details of board numbering.
 */

// Hardware types.
static const u32 HARDWARE_TYPE_TYPE5 = 5;
static const u32 HARDWARE_TYPE_TYPE6 = 6;
static const u32 HARDWARE_TYPE_TYPE7 = 7;
static const u32 HARDWARE_TYPE_TYPE8 = 8;

// Use in conjunction with HARDWARE_TYPE_TYPE5
static const u32 HARDWARE_REVISION_TYPE5REV0_2100_RF = 0;
static const u32 HARDWARE_REVISION_TYPE5REV1_2100_RF = 1;
static const u32 HARDWARE_REVISION_TYPE5REV2_1900_RF = 2;
static const u32 HARDWARE_REVISION_TYPE5REV3_1900_RF = 3;
static const u32 HARDWARE_REVISION_TYPE5REV4_BAND_VIII = 4;
static const u32 HARDWARE_REVISION_TYPE5REV5_BAND_V = 5;
static const u32 HARDWARE_REVISION_TYPE5REV6_BAND_IV_AWS = 6;
static const u32 HARDWARE_REVISION_TYPE5REV7_1900_RF = 7;

// Use in conjunction with HARDWARE_TYPE_TYPE6
static const u32 HARDWARE_REVISION_TYPE6REV0_2100_RF = 0;
static const u32 HARDWARE_REVISION_TYPE6REV1_1900_850_RF = 1;
static const u32 HARDWARE_REVISION_TYPE6REV2_2100_RF_DEMO = 2;
static const u32 HARDWARE_REVISION_TYPE6REV3_1900_850_RF_DEMO = 3;

// Use in conjunction with HARDWARE_TYPE_TYPE7
static const u32 HARDWARE_REVISION_TYPE7REV0_2100_RF = 0;
static const u32 HARDWARE_REVISION_TYPE7REV1_1900_850_RF = 1;

// Use in conjunction with HARDWARE_TYPE_TYPE8
static const u32 HARDWARE_REVISION_TYPE8REV0 = 0;
static const u32 HARDWARE_REVISION_TYPE8REV4 = 4;

#endif
