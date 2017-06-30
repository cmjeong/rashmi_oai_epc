///////////////////////////////////////////////////////////////////////////////
//
// ValidatorQOffsetFreqList.h
//
// S32 Array validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorQOffsetFreqList_h_
#define __ValidatorQOffsetFreqList_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorS32Array.h"
#include "ValidatorQOffsetFreq.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorQOffsetFreqList : public ValidatorS32Array,ValidatorQOffsetFreq
{
public:
    ValidatorQOffsetFreqList();
    virtual ~ValidatorQOffsetFreqList();

    /**
     * Validate a s32 array.
     *
     * \param value        The value(s) to validate.
     * \param min          The minimum allowed value.
     * \param max          The maximum allowed value.
     * \param maxInstances The maximum number of elements.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateS32Array(const std::vector<s32>& value, s32 min, s32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
private:    
    ValidatorQOffsetFreq m_validator;

};

#endif
