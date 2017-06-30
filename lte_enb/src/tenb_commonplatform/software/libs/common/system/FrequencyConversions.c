///////////////////////////////////////////////////////////////////////////////
//
// FrequencyConversions.c
//
// Contains all frequency to band conversion functions that should
// be used within the FAP.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FrequencyConversions.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// IMPORTANT NOTE!
//
// This table and it's entries must *EXACTLY* match the entries of the table "UmtsBandId"
// in file /libs/common/mobnet/UmtsBandId.h
// It it fails to do this then *all* band information returned in the following methods will be
// corrupt!
//
static const uarfcn_band_limits_t uarfcn_band_limits_list[UBAND_NUMBER_OF] = {
        // minUarfcn, maxUarfcn, numberAdditional, additional Uarfcn(1)...(n)
        {     0,          0,            0,        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_INVALID
        { 10562,      10838,            0,        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_I_2100,
        {  9662,       9938,           12,        { 412, 437, 462, 487, 512, 537, 562, 587, 612, 637, 662, 687,0,0 }}, // UBAND_II_1900,
        {  1162,       1513,            0,        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_III_1800,
        {  1537,       1738,            9,        { 1887, 1912, 1937, 1962, 1987, 2012, 2037, 2062, 2087, 0,0,0,0,0 }}, // UBAND_IV_1700,
        {  4357,       4458,            4,        { 1037, 1062, 1032, 1087, 0,0,0,0,0,0,0,0,0,0 }}, // UBAND_V_850,
        {  4387,       4413,            2,        { 1037, 1062, 0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_VI,
        {  2237,       2563,           14,        { 2587, 2612, 2637, 2662, 2687, 2712, 2737, 2762, 2787, 2812, 2837, 2862, 2887, 2912 }}, // UBAND_VII,
        {  2937,       3088,            0,        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_VIII,
        {  9237,       9387,            0,        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_IX,
        {  3112,       3388,           12,        { 3412, 3437, 3462, 3487, 3512, 3537, 3562, 3587, 3612, 3637, 3662, 3687,0,0 }}, // UBAND_X,
        {  3712,       3787,            0,        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_XI,
        {  3837,       3903,            6,        { 3927, 3932, 3957, 3962, 3987, 3992,0,0,0,0,0,0,0,0 }}, // UBAND_XII,
        {  4017,       4043,            2,        { 4067, 4092, 0,0,0,0,0,0,0,0,0,0,0,0 }}, // UBAND_XIII
        {  4117,       4143,            2,        { 4167, 4192, 0,0,0,0,0,0,0,0,0,0,0,0 }} // UBAND_XIV
};

// Band        ARFCN Range
// -----------------------
// P-GSM 900 - 1..124
// E-GSM 900 - 0..124
//             975..1023
// R-GSM 900   0..124
//             955..1023
// GSM 850     128..251
// GSM 450     259..293
// GSM 480     306..340
// GSM 750     438..511
// DCS 1800    512..885
// PCS 1900    512..810
//
// Not currently used (and ARFCNs are dynamic - based off of BCCH info).
//   T-GSM380
//   T-GSM410
//   T-GSM810
//   T-GSM900

// Also not currently supported in this logic.
//   GSM710

// IMPORTANT NOTE!
//
// This table and it's entries must *EXACTLY* match the entries of the table "GsmBandId"
// in file /libs/common/mobnet/GsmBandId.h
// It it fails to do this then *all* band information returned in the following methods will be
// corrupt!
//
static const arfcn_band_limits_t arfcn_band_limits_list[GSM_BAND_ID_NUMBER_OF] = {
        // minArfcn1, maxArfcn1, arfcn2inUse?, minArfcn2, maxArfcn2
        {      0,         0,        false,         0,         0 }, // GSM_BAND_ID_INVALID
        {      0,       124,        false,       975,      1023 }, // E-GSM900 - Must be first entry in this table!
        {      1,       124,        false,         0,         0 }, // P-GSM900
        {      0,       124,        false,       955,      1023 }, // R-GSM900
        {    259,       293,        false,         0,         0 }, // GSM450
        {    306,       340,        false,         0,         0 }, // GSM480
        {      0,         0,        false,         0,         0 }, // GSM710
        {    428,       511,        false,         0,         0 }, // GSM750
        {    128,       251,        false,         0,         0 }, // GSM850
        {    512,       885,        false,         0,         0 }, // DCS1800
        {    512,       810,        false,         0,         0 }, // PCS1900
        {      0,         0,        false,         0,         0 }, // T-GSM380
        {      0,         0,        false,         0,         0 }, // T-GSM410
        {      0,         0,        false,         0,         0 }, // T-GSM810
        {      0,         0,        false,         0,         0 }  // T-GSM900
};

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions - UMTS FDD Frequencies.
///////////////////////////////////////////////////////////////////////////////

// band IV flag required due to UARFCN numbers 1037 & 1042 being shared by
// bands V & VI - trust 3GPP to always add a little complication into the system
// that stuffs up the simplicity of the code.
uband_t GetUmtsFddBand(const uarfcn_t uarfcn, const bool bandVIavailable)
{
    uband_t foundBand = UBAND_INVALID;
    uband_t currentBand;
    const uarfcn_band_limits_t * currentBandLimits = NULL;
    u8 additionaUarfcnChannelIndex = 0;

    // Loop until list is exhausted or the band has been found.
    for(currentBand = UBAND_FIRST; (currentBand <= UBAND_LAST) && (foundBand == UBAND_INVALID); currentBand++)
    {
        // Skip bands V or VI depending on setting of bandIVavailable flag.
        if((currentBand == UBAND_V_850 &&  bandVIavailable) ||
           (currentBand == UBAND_VI    && !bandVIavailable))
        {
            continue;
        }
        // Get ptr to the current band limits information
        currentBandLimits = UmtsFddBandToUarfcnRange(currentBand);
        if(currentBandLimits) // ptr was returned.
        {
            // Check basic min and max.
            if(uarfcn >= currentBandLimits->minUarfcn &&
               uarfcn <= currentBandLimits->maxUarfcn)
            {
                // UARFCN is within this range, therefore this is the
                // band to select
                foundBand = currentBand;
            }
            else
            {
                // Check the additional uarfcn list.
                additionaUarfcnChannelIndex = 0;
                // Loop until list is exhausted or the band has been found.
            while((additionaUarfcnChannelIndex < currentBandLimits->numberOfAdditionalUarfcnChannels) && (foundBand == UBAND_INVALID) && (currentBandLimits->numberOfAdditionalUarfcnChannels <= 14))
                {
                    if(uarfcn == currentBandLimits->additionalUarfcnChannelList[additionaUarfcnChannelIndex])
                    {
                        // frequencies matched - so band has been found.
                        foundBand = currentBand;
                    }
                    additionaUarfcnChannelIndex++;
                }
            }
        }
    }

    return (foundBand);
}

const uarfcn_band_limits_t * UmtsFddBandToUarfcnRange(const uband_t bandId)
{
    const uarfcn_band_limits_t * listEntryPtr = &uarfcn_band_limits_list[UBAND_INVALID];
    if(bandId <= UBAND_NUMBER_OF)
    {
        // BandId is in valid range - get the associated arfcn band limit entry in list.
        listEntryPtr = &uarfcn_band_limits_list[bandId];
    }
    return listEntryPtr;
}


///////////////////////////////////////////////////////////////////////////////
// Functions - GSM Frequencies
///////////////////////////////////////////////////////////////////////////////
//
// NOTE - when the changes have been performed in CPhyTypes.h to typedef band_t GsmBandId then the
//        the following line should be changed as shown so that this function can be made
//        use of in any C code requiring it.
//band_t GetGsmBand(const arfcn_t arfcn, const bool pcsInOperation)
GsmBandId GetGsmBand(const arfcn_t arfcn, const bool pcsInOperation)
{
    GsmBandId foundBand = GSM_BAND_ID_INVALID;
    GsmBandId currentBand;
    const arfcn_band_limits_t * currentBandLimits = NULL;

    // Loop until list is exhausted or the band has been found.
    for(currentBand = GSM_BAND_ID_FIRST; (currentBand <= GSM_BAND_ID_LAST) && (foundBand == GSM_BAND_ID_INVALID); currentBand++)
    {
        // Skip bands 1800DCS or 1900PCS depending on setting of pcsInOperation flag.
        if((currentBand == GSM_BAND_ID_DCS1800 &&  pcsInOperation) ||
           (currentBand == GSM_BAND_ID_PCS1900 && !pcsInOperation))
        {
            continue;
        }
        // Get ptr to the current band limits information
        currentBandLimits = GsmBandToArfcnRange(currentBand);
        if(currentBandLimits) // ptr was returned.
        {
            // Check basic min and max.
            if(arfcn >= currentBandLimits->minArfcn1 &&
               arfcn <= currentBandLimits->maxArfcn1)
            {
                // ARFCN is within this range, therefore this is the
                // band to select
                foundBand = currentBand;
            }
            else
            {
                // Check the additional range (if present)
                if(currentBandLimits->arfcn2rangePresent)
                {
                    // Check 2nd range min and max.
                    if(arfcn >= currentBandLimits->minArfcn2 &&
                       arfcn <= currentBandLimits->maxArfcn2)
                    {
                        // ARFCN is within this range, therefore this is the
                        // band to select
                        foundBand = currentBand;
                    }
                }
            }
        }
    }

    return (foundBand);
}



// arfcn_band_limits_t GsmBandToArfcnRange(band_t bandId)
const arfcn_band_limits_t * GsmBandToArfcnRange(GsmBandId bandId)
{
    const arfcn_band_limits_t * listEntryPtr = &arfcn_band_limits_list[GSM_BAND_ID_INVALID];
    if(bandId <= GSM_BAND_ID_NUMBER_OF)
    {
        // BandId is in valid range - get the associated arfcn band limit entry in list.
        listEntryPtr = &arfcn_band_limits_list[bandId];
    }
    return listEntryPtr;
}
