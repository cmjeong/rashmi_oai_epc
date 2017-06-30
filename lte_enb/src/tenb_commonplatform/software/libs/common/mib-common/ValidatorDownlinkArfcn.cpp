///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDownlinkArfcn.cpp
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

#include "ValidatorDownlinkArfcn.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorDownlinkArfcn::ValidatorDownlinkArfcn()
{
    ENTER();

    EXIT();
}

ValidatorDownlinkArfcn::~ValidatorDownlinkArfcn()
{
    ENTER();

    EXIT();
}

bool ValidatorDownlinkArfcn::ValidateU32(u32 value, u32 /*min*/, u32 /*max*/, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool isValid = false;

    // Check for GSM 1900
	if((value >= 512) && (value <= 810) && m_bandsSupported.Find(GSM_BAND_ID_PCS1900))
	{
		isValid = true;
	}
	// Check for GSM 1800
	if((value >= 512) && (value <= 885) && m_bandsSupported.Find(GSM_BAND_ID_DCS1800))
	{
		isValid = true;
	}
	// Check for P-GSM 900
	if((value >= 1) && (value <= 124) && m_bandsSupported.Find(GSM_BAND_ID_P_GSM900))
	{
		isValid = true;
	}
	// Check for E-GSM 900
	if((((value >= 975) && (value <= 1023)) || (value == 0)) && m_bandsSupported.Find(GSM_BAND_ID_E_GSM900))
	{
		isValid = true;
	}
	// Check for GSM 850
	if((value >= 128) && (value <= 251) && m_bandsSupported.Find(GSM_BAND_ID_GSM850))
	{
		isValid = true;
	}
	// This value is used to indicate an unset value, so we need to allow it for now.
	if((s32)value == -1)
	{
		isValid = true;
	}
	// TODO: Add support for other bands here if we need them

    TRACE_PRINTF("ValidatorDownlinkArfcn: Validating Arfcn %u Bands supported %s",
    	value, ToString().c_str());

    if(!isValid)
    {
        ostringstream stream;
        stream << "NotValidValue (" << value << ") for supported bands (" << ToString();

        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, stream.str());
        TRACE_PRINTF("%s", stream.str().c_str());
    }
    RETURN(isValid);
}

void ValidatorDownlinkArfcn::SetBandsSupported(GsmBands bandsSupported)
{
    m_bandsSupported = bandsSupported;
	TRACE_PRINTF("Setting bands supported: %s", ToString().c_str());
}


std::string ValidatorDownlinkArfcn::ToString() const
{
    ostringstream stream;

   stream << "ValidatorDownlinkArfcn: Bands supported " << m_bandsSupported.ToString();

   return(stream.str());
}
