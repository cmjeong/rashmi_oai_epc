///////////////////////////////////////////////////////////////////////////////
//
    // ValidatorRemGsmBands.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>
#include <mobnet/GsmBandId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorRemGsmBands.h"

using namespace std;

ValidatorRemGsmBands::ValidatorRemGsmBands()
{
    // All bands accepted until corrected by OAM at startup.

    for(GsmBandId i = GSM_BAND_ID_FIRST;
            i <= GSM_BAND_ID_LAST;
            i = GsmBandId(u32(i) + 1))
    {
        m_bandsSupported.insert(i);
    }
}

ValidatorRemGsmBands::~ValidatorRemGsmBands()
{
}

bool ValidatorRemGsmBands::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    // Restrict limits to sensible values
    maxInstances = min(maxInstances, u32(GSM_BAND_ID_NUMBER_OF) );
    minValue     = max(minValue,     u32(GSM_BAND_ID_FIRST) );
    maxValue     = min(maxValue,     u32(GSM_BAND_ID_LAST) );

    if(!ValidatorU32Array::ValidateU32Array(value, minValue, maxValue, maxInstances, failureDescriptor) )
    {
        return false;
    }

    ostringstream strRequested;
    ostringstream strUnsupported;

    for( std::vector<u32>::const_iterator i = value.begin();
            i != value.end();
            i++)
    {
        GsmBandId bandRequested = GsmBandId(*i);

        strRequested << GsmBandIdToString(bandRequested) << " ";

        bool supported = (m_bandsSupported.find(bandRequested) != m_bandsSupported.end());

        if(!supported)
        {
            strUnsupported << GsmBandIdToString(bandRequested) << " ";
        }
    }

    bool validGsmBands = strUnsupported.str().empty();

    if( !validGsmBands )
    {
        ostringstream description;
        description << "Requested (" << strRequested.str() << "), but (" << strUnsupported.str() << ") are unsupported.";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_INVALID, description.str());
    }

    return validGsmBands;
}


void ValidatorRemGsmBands::SetBandsSupported( const GsmBands & bandsSupported)
{
    m_bandsSupported.clear();
    m_bandsSupported = bandsSupported.Get();
}

