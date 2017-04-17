///////////////////////////////////////////////////////////////////////////////
//
// ValidatorPMFileTransferMethod.cpp
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
#include <string.h>
#include <system/Trace.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ValidatorPMFileTransferMethod.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorPMFileTransferMethod::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool validated = false;

   if( ValidatorString::ValidateString(value, minLength, maxLength, failureDescriptor) )
   {
      if(!strcmp(value.c_str(),"SFTP"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"FTP"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"SCP"))
      {
         validated = true;
      }
      else if(!strcmp(value.c_str(),"TFTP"))
      {
         ostringstream description;
         description << "\"" << value << "\" is not supported currently";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_OTHER, description.str());
      }
      else
      {
         ostringstream description;
         description << "PMFileTransferMethod is invalid";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      }
   }

   RETURN(validated);
}
