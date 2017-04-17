///////////////////////////////////////////////////////////////////////////////
//
// ValidatorTReselectionSFList.h
//
// U32 Array validator.
//
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorTReselectionSFList_h_
#define __ValidatorTReselectionSFList_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorU32Array.h"
#include "ValidatorTReselectionSF.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class ValidatorTReselectionSFList : public ValidatorU32Array,ValidatorTReselectionSF
{
public:
    ValidatorTReselectionSFList();
    virtual ~ValidatorTReselectionSFList();

    /**
     * Validate a u32 array.
     * \param value        The value(s) to validate.
     * \param min          The minimum allowed value.
     * \param max          The maximum allowed value.
     * \param maxInstances The maximum number of elements.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);

private:

ValidatorTReselectionSF m_validator;

};

#endif

