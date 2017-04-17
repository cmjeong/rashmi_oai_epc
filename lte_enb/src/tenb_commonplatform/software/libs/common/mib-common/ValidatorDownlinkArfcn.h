///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDownlinkArfcn.h
//
// A validator for ARFCN.  Must be given the bands supported as Arfcns aren't
// unique to a particular band.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorDownlinkArfcn_h_
#define __ValidatorDownlinkArfcn_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/GsmBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorDownlinkArfcn : public ValidatorU32
{
public:
    ValidatorDownlinkArfcn();
    virtual ~ValidatorDownlinkArfcn();

    /**
     * Validate a UARFCN (as u32).
     *
     * \param value The value to validate.
     * \param min   The minimum allowed value.  Provides further limitation
     *              over and above the normal range of UARFCN.
     * \param max   The maximum allowed value.  Provides further limitation
     *              over and above the normal range of UARFCN.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);

    /**
     * Set band.  Means the validator can be much more accurate.
     */
    void SetBandsSupported(GsmBands bandsSupported);

    virtual std::string ToString() const;

private:
    GsmBands m_bandsSupported;

};

#endif
