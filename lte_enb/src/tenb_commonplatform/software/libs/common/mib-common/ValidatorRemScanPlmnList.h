///////////////////////////////////////////////////////////////////////////////
//
// ValidatorRemScanPlmnList.h
//
// REM Scan Plmn list  value validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorRemScanPlmnList_h_
#define __ValidatorRemScanPlmnList_h_

#include <vector>
#include <system/Regex.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorStringArray.h"


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorRemScanPlmnList : public ValidatorStringArray
{
public:
    enum RemScanPlmnLst {empty,notEmpty} remScanPlmnList;
    ValidatorRemScanPlmnList() {};
    virtual ~ValidatorRemScanPlmnList() {};

    virtual bool ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

};

#endif

