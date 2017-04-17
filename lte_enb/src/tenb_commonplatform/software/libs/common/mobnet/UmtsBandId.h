///////////////////////////////////////////////////////////////////////////////
//
// UmtsBandId.h
//
// IDs of all possible Umts Bands.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__UmtsBandId_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __UmtsBandId_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**
 * Frequency bands.  See http://en.wikipedia.org/wiki/UMTS_frequency_bands
 *
 * Band             DL to UL        3GPP TS 25.101              3GPP TS 25.101
 *                  Frequency       Downlink                    Uplink
 *                  Separation      UARFCN Range                UARFCN Range
 *                  (MHz)
 *
 * I (IMT-2000)     190             10562 - 10838               9612 - 9888
 * D/L 2100MHz
 *
 * II (U.S. PCS)    80              9662 - 9938                 9262 - 9538
 * D/L 1900MHz                      412, 437, 462, 487, 512,    12, 37, 62, 87, 112, 137,
 *                                  537, 562, 587, 612, 637,    162, 187, 212, 237, 262, 287
 *                                  662, 687
 *
 * III (DCS/PCS)    95              1162 - 1513                 937 - 1288
 * D/L 1800MHz
 *
 * IV               400             1537 - 1738                 1312 - 1513
 * 1700                             1887, 1912, 1937, 1962,     1662, 1687, 1712, 1737, 1762,
 *                                  1987, 2012, 2037, 2062,     1787, 1812, 1837, 1862
 *                                  2087
 *
 * V                45              4132 to 4233                4357 to 4458
 * 850                              782, 787, 807,              1007, 1012, 1032,
 *                                  812, 837, 862               1037, 1062, 1087
 */

// IMPORTANT NOTE!
//
// This table and it's entries must *EXACTLY* match the entries of the table "uarfcn_band_limits_list"
// in file /libs/common/system/FrequencyConversion.c
// It it fails to do this then *all* band information function will fail to function correctly
// and will return corrupt information.
//
// So if you modify the table below you *MUST* make the same changes to "uarfcn_band_limits_list" as well!
//
ENUM_START(UmtsBandId)
{
    ENUM_ELEMENT_VALUE_STRING( UBAND_INVALID,   0,  "{invalid}")
    ENUM_ELEMENT_DUPLICATE(    UBAND_FIRST,     1)
    ENUM_ELEMENT_VALUE_STRING( UBAND_I_2100,    1,  "I")
    ENUM_ELEMENT_VALUE_STRING( UBAND_II_1900,   2,  "II")
    ENUM_ELEMENT_VALUE_STRING( UBAND_III_1800,  3,  "III")
    ENUM_ELEMENT_VALUE_STRING( UBAND_IV_1700,   4,  "IV")
    ENUM_ELEMENT_VALUE_STRING( UBAND_V_850,     5,  "V")
    ENUM_ELEMENT_VALUE_STRING( UBAND_VI,        6,  "VI")
    ENUM_ELEMENT_VALUE_STRING( UBAND_VII,       7,  "VII")
    ENUM_ELEMENT_VALUE_STRING( UBAND_VIII,      8,  "VIII")
    ENUM_ELEMENT_VALUE_STRING( UBAND_IX,        9,  "IX")
    ENUM_ELEMENT_VALUE_STRING( UBAND_X,        10,  "X")
    ENUM_ELEMENT_VALUE_STRING( UBAND_XI,       11,  "XI")
    ENUM_ELEMENT_VALUE_STRING( UBAND_XII,      12,  "XII")
    ENUM_ELEMENT_VALUE_STRING( UBAND_XIII,     13,  "XIII")
    ENUM_ELEMENT_VALUE_STRING( UBAND_XIV,      14,  "XIV")
    ENUM_ELEMENT_DUPLICATE(    UBAND_LAST,     14)
    ENUM_ELEMENT_VAL(          UBAND_NUMBER_OF,15)
}
ENUM_END(UmtsBandId)

const char * UmtsBandIdToDetailedString(UmtsBandId umtsBandID);

#endif
