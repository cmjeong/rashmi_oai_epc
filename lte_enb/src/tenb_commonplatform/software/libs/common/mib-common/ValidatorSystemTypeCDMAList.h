#ifndef __ValidatorSystemTypeCDMAList_h
#define __ValidatorSystemTypeCDMAList_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorU32Array.h"
#include "ValidatorU32.h"

#define TWO 2

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class ValidatorSystemTypeCDMAList : public ValidatorU32Array
{
public:
   ValidatorSystemTypeCDMAList();
   virtual ~ValidatorSystemTypeCDMAList();

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
	ValidatorU32 m_validator;

};

#endif
