///////////////////////////////////////////////////////////////////////////////
//
// ValidatorDownlinkUArfcnRem.h
//
// A validator for UARFCN.  Can be given a band in order to improved the
// validation accuracy.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorDownlinkUArfcnRem_h_
#define __ValidatorDownlinkUArfcnRem_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <mobnet/MobnetTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
typedef ValidatorDownlinkUArfcn ValidatorDownlinkUArfcnRem;
#if(0)
class ValidatorDownlinkUArfcnRem : public ValidatorU32
{
public:
    ValidatorDownlinkUArfcnRem();
    virtual ~ValidatorDownlinkUArfcnRem();

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
    void SetUBandsSupported(UmtsBands uBandsSupported);

private:
    UmtsBands m_uBandsSupported;

};

#endif
#endif
