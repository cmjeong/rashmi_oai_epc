///////////////////////////////////////////////////////////////////////////////
//
// ValidatorInterA5RsrpThrsld2.h
//
// A validator for InterA5RsrpThrsld2
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorInterA5RsrpThrsld2_h_
#define __ValidatorInterA5RsrpThrsld2_h_

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

class ValidatorInterA5RsrpThrsld2: public ValidatorU32
{
public:

    ValidatorInterA5RsrpThrsld2() {};
    virtual ~ValidatorInterA5RsrpThrsld2() {};

    virtual bool ValidateU32(MibDN Dn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor);
protected:

private:
   u32 InterAnrA5RsrpThrsld2;
  
};

#endif
