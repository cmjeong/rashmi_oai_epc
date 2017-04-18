///////////////////////////////////////////////////////////////////////////////
//
// ValidatorSerialNumber.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
//#include <boost/regex.hpp>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorSerialNumber.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorSerialNumber::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    if(ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor))
    {
        // TODO: Could use boost regex once we add library.
//        const regex expression("[0-9a-zA-Z\\-]*");
//
//        if(regex_match(value, expression))
//        {
//            RETURN(true);
//        }
        static const char * VALID_SERIAL_NUM_CHARS = "0123456789";
        string::size_type p = value.find_first_not_of(VALID_SERIAL_NUM_CHARS);
        if(p == string::npos)
        {
            // Didn't find anything except valid chars so looking good.
            RETURN(true);
        }

        ostringstream description;
        description << "must contain only chars from \"" << VALID_SERIAL_NUM_CHARS << "\"";
        failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());

        RETURN(false);
    }

    RETURN(false);
}
