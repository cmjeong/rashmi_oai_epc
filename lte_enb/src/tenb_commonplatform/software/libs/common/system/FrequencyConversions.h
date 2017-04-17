///////////////////////////////////////////////////////////////////////////////
//
// FrequencyConversions.h
//
// Contains all frequency to band conversion functions that should
// be used within the FAP.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FrequencyConversions_h_
#define __FrequencyConversions_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <mobnet/UmtsBandId.h>
#include <mobnet/GsmBandId.h>
#include <messaging/messages/cphy/CPhyTypes.h>

// TODO: Delete unused sections below.

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ADDITIONAL_UARFCN_LIST_ENTRIES  14

typedef struct
{
    uarfcn_t minUarfcn;
    uarfcn_t maxUarfcn;
    UmtsBandId numberOfAdditionalUarfcnChannels;
    uarfcn_t additionalUarfcnChannelList[MAX_ADDITIONAL_UARFCN_LIST_ENTRIES];
}
uarfcn_band_limits_t;

typedef struct
{
    arfcn_t minArfcn1;
    arfcn_t maxArfcn1;
    bool    arfcn2rangePresent;
    arfcn_t minArfcn2;
    arfcn_t maxArfcn2;
}
arfcn_band_limits_t;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

// UMTS FDD Frequency Functions.

uband_t GetUmtsFddBand(const uarfcn_t uarfcn, const bool bandVIavailable);
const uarfcn_band_limits_t * UmtsFddBandToUarfcnRange(const uband_t bandId);


// Gsm Frequency Functions

// note - when the changes have been performed in CPhyTypes.h to typedef band_t GsmBandId then the
//        the following line should be changed as shown so that this function can be made
//        use of in any C code requiring it.
//band_t GetGsmBand(const arfcn_t arfcn, const bool pcsInOperation);
GsmBandId GetGsmBand(const arfcn_t arfcn, const bool pcsInOperation);

// arfcn_band_limits_t * GsmBandToArfcnRange(band_t bandId);
const arfcn_band_limits_t * GsmBandToArfcnRange(const GsmBandId bandId);


#ifdef __cplusplus
}
#endif

#endif
