///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteNeighCellConfig.cpp
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
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>
#include <string.h>

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorLteNeighCellConfig.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorLteNeighCellConfig::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;

    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
		    if(!strcmp(value.c_str(),"00"))
		    {
			    validated = true;
            RETURN(true);
		    }
		    else if(!strcmp(value.c_str(),"01"))
		    {
			    validated = true;
            RETURN(true);
		    }
		    else if(!strcmp(value.c_str(),"10"))
		    {
			    validated = true;
            RETURN(true);
		    }
                    else if(!strcmp(value.c_str(),"11"))
                    {
                            validated = true;
            RETURN(true);
                    }
		    else
                    {
	    		    ostringstream description;
	                    description << failureDescriptor.GetDescription()<<
                                       "Supported value of NeighCellConfig (00,10,01,110)";
	                    failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
	                    RETURN(false);
	            }
    }

    RETURN(validated);

}
