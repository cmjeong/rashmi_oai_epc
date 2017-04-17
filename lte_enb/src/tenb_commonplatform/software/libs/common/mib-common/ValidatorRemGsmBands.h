///////////////////////////////////////////////////////////////////////////////
//
// ValidatorRemGsmBands.h
//
// GSM Band value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorRemGsmBands_h_
#define __ValidatorRemGsmBands_h_

#include <vector>
#include <system/GsmBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32Array.h"


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorRemGsmBands : public ValidatorU32Array
{
public:
    ValidatorRemGsmBands();
    virtual ~ValidatorRemGsmBands();

    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

    /**
     * Set band.  Means the validator can be much more accurate.
     */
    void SetBandsSupported( const GsmBands & bandsSupported);

private:
    GsmBandIds m_bandsSupported;

};

#endif
