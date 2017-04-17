///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNghFreqEarfcnList.h
//
// A validator for EarfcnList.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorNghFreqEarfcnList_h_
#define __ValidatorNghFreqEarfcnList_h_

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

class ValidatorNghFreqEarfcnList : public ValidatorU32Array, ValidatorU32
{
	public:

		ValidatorNghFreqEarfcnList() {};
		virtual ~ValidatorNghFreqEarfcnList() {};

                virtual bool ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
		void SetLteBands(std::vector<u32> bandSupported);        
      void SetServingEarfcn(u32 earfcn);

	private:
		std::vector<u32> BandSupported;
      u32 ServingEarfcn;
};

#endif
