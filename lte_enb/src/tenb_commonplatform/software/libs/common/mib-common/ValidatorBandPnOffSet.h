///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//  ValidatorBandPnOffSet.h
//
//  Band PnOffset Validator
//
//  Copyright Radisys limited
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


#ifndef __ValidatorBandPnOffSet_h
#define __ValidatorBandPnOffSet_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorU32Array.h"
#include "ValidatorU32.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class ValidatorBandPnOffSet : public ValidatorU32Array, ValidatorU32
{
public:
   ValidatorBandPnOffSet();
   virtual ~ValidatorBandPnOffSet();

   /**
    * Validate a u32 array.
    * \param value        The value(s) to validate.
    * \param min          The minimum allowed value.
    * \param max          The maximum allowed value.
    * \param maxInstances The maximum number of elements.
    * \param failureDescriptor Gets filled in with information about any validation failure.
    */
   virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif
