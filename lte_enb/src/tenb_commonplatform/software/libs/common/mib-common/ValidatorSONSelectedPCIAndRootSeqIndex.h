///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSONSelectedPCIAndRootSeqIndex.h
//
// Description : This class validates values allowed for LTE_SON_SELECTED_PCI and
//               LTE_SON_SELECTED_PRACH_ROOT_SEQUENCE_INDEX parameters.
//               65535 is also considered valid value but not supposed to be
//               configured from HeMS or CLI. Its the initial value(first-time bootup)
//               of above mentioned parameters.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorSONSelectedPCIAndRootSeqIndex_h_
#define __ValidatorSONSelectedPCIAndRootSeqIndex_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorSONSelectedPCIAndRootSeqIndex : public ValidatorU32
{
public:

    ValidatorSONSelectedPCIAndRootSeqIndex() {};
    virtual ~ValidatorSONSelectedPCIAndRootSeqIndex() {};

    /**
     * \param value The value to validate.
     * \param min   The minimum allowed value.
     * \param max   The maximum allowed value.
     * \param failureDescriptor Gets filled in with information about any validation failure.
     */
    virtual bool ValidateU32(u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);

protected:

private:

};

#endif
