///////////////////////////////////////////////////////////////////////////////
//
// GsmBandId.h
//
// IDs of all possible GSM Bands.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__GsmBandId_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __GsmBandId_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

// IMPORTANT NOTE!
//
// This table and it's entries must *EXACTLY* match the entries of the table "arfcn_band_limits_list"
// in file /libs/common/system/FrequencyConversion.c
// It it fails to do this then *all* band information function will fail to function correctly
// and will return corrupt information.
//
// So if you modify the table below you *MUST* make the same changes to "arfcn_band_limits_list" as well!
//
ENUM_START(GsmBandId)
{
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_INVALID,   0, "{invalid}")
    ENUM_ELEMENT_DUPLICATE(   GSM_BAND_ID_FIRST,     1)
    // NOTE : E-GSM must be first entry on list for the GetGsmBand() logic to work correctly.
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_E_GSM900,  1, "E-GSM900")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_P_GSM900,  2, "P-GSM900")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_R_GSM900,  3, "R-GSM900")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_GSM450,    4, "GSM450")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_GSM480,    5, "GSM480")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_GSM710,    6, "GSM710")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_GSM750,    7, "GSM750")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_GSM850,    8, "GSM850")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_DCS1800,   9, "DCS1800")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_PCS1900,  10, "PCS1900")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_T_GSM380, 11, "T-GSM380")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_T_GSM410, 12, "T-GSM410")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_T_GSM810, 13, "T-GSM810")
    ENUM_ELEMENT_VALUE_STRING(GSM_BAND_ID_T_GSM900, 14, "T-GSM900")

    ENUM_ELEMENT_DUPLICATE(   GSM_BAND_ID_LAST,     14)
    ENUM_ELEMENT_VAL(         GSM_BAND_ID_NUMBER_OF,15)


}
ENUM_END(GsmBandId)

#endif
