///////////////////////////////////////////////////////////////////////////////
//
// ValidatorUmtsBands.h
//
// UMTS Band value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorUmtsBands_h_
#define __ValidatorUmtsBands_h_

#include <boost/shared_ptr.hpp>
#include <system/Regex.h>
#include <system/UmtsBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorStringArray.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorUmtsBands : public ValidatorStringArray
{
public:
    ValidatorUmtsBands();
    virtual ~ValidatorUmtsBands() {};

    virtual bool ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

    void SetBandsSupported(const UmtsBands & bandsSupported);

private:
    boost::shared_ptr<threeway::Regex> m_umtsBandsRegex;
};

#endif
