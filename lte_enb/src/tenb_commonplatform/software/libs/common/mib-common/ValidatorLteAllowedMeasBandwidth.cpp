///////////////////////////////////////////////////////////////////////////////
//
// ValidatorLteAllowedMeasBandwidth.cpp
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
#include "ValidatorLteAllowedMeasBandwidth.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorLteAllowedMeasBandwidth::ValidateString(const std::string &value, u32 minLength, u32 maxLength,ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();

    bool validated = false;

    if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
    {
		    if(!strcmp(value.c_str(),"mbw6"))
		    {
			    validated = true;
            RETURN(true);
		    }
		    else if(!strcmp(value.c_str(),"mbw15"))
		    {
			    validated = true;
            RETURN(true);
		    }
		    else if(!strcmp(value.c_str(),"mbw25"))
		    {
			    validated = true;
            RETURN(true);
		    }
             else if(!strcmp(value.c_str(),"mbw50"))
                    {
                            validated = true;
            RETURN(true);
                    }
             else if(!strcmp(value.c_str(),"mbw75"))
                    {
                            validated = true;
            RETURN(true);
                    }
             else if(!strcmp(value.c_str(),"mbw100"))
                    {
                            validated = true;
            RETURN(true);
                    }
		    else
                    {
	    		    ostringstream description;
	                    description << failureDescriptor.GetDescription()<<
                             "supported value of AllowedMeasBandwidth (mbw6,mbw15,mbw25,mbw50,mbw75,mbw100)";
	                    failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
	                    RETURN(false);
	            }
    }

    RETURN(validated);

}
