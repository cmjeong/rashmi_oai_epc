///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDownlinkUArfcn.cpp
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
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorDownlinkUArfcn.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorDownlinkUArfcn::ValidatorDownlinkUArfcn()
{
    ENTER();

    EXIT();
}

ValidatorDownlinkUArfcn::~ValidatorDownlinkUArfcn()
{
    ENTER();

    EXIT();
}

bool ValidatorDownlinkUArfcn::ValidateU32(u32 value, u32 /*min*/, u32 /*max*/, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    // TODO - this looks wrong... UARFCN could map to multiple bands so we should check it falls into at least one of them
    // In otherwords, we can't just map UARFCN to a single band then validate that is in the supported bands
    // We should get a list of possible bands then check at least one is in the list of supported bands.
    UmtsBandId uBand = m_uBandsSupported.UarfcnToUband((u16)value);
    TRACE_PRINTF("ValidatorDownlinkUArfcn: Validating value %"PRIu32" UBand=%u (bands supported=%s)",
    		value, uBand,
    		m_uBandsSupported.ToString().c_str() );

    bool isValid = m_uBandsSupported.Find(uBand);

    if(!isValid)
    {
        ostringstream stream;
        stream << "NotValidValue " << uBand << " "
                << "(" << UmtsBandIdToString(uBand) << ") "
                << "for supported bands "
                << "(" <<  m_uBandsSupported.ToString() << ")";

        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, stream.str());
        TRACE_PRINTF("%s", stream.str().c_str());
    }
    RETURN(isValid);
}

void ValidatorDownlinkUArfcn::SetUBandsSupported(UmtsBands uBandsSupported)
{
    m_uBandsSupported = uBandsSupported;

    TRACE_PRINTF("ValidatorDownlinkUArfcn: Bands supported set to %s",
            m_uBandsSupported.ToString().c_str() );
}

