///////////////////////////////////////////////////////////////////////////////
//
// ValidatorIpAddress.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorIpAddress.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorIpAddress::ValidateString(const std::string& value, u32 minLength, u32 maxLength, ValidationFailureDescriptor& failureDescriptor)
{
    ENTER();
    if(ValidateIpv4(value,failureDescriptor)||ValidateIpv6(value,failureDescriptor))
    {
        return true;
    }
    return false;
}

bool ValidatorIpAddress::ValidateIpv4(const std::string& value,ValidationFailureDescriptor& failureDescriptor)
{
   if(ValidatorString::ValidateString(value, 7, 15, failureDescriptor))
   {
      // TODO: Could use boost regex once we add library.

      static const char * VALID_IP_ADDRESS_CHARS = "0123456789.";
      string::size_type p = value.find_first_not_of(VALID_IP_ADDRESS_CHARS);
      if(p != string::npos)
      {
         ostringstream description;
         description << "NotValidValue for IP address, must contain only chars from \"" << VALID_IP_ADDRESS_CHARS << "\"";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         RETURN(false);
      }

      // Tokenise based on '.' and check we have 4 tokens, each 0-255.
      string token;
      string::size_type pos = 0;
      string::size_type dotPos = 0;
      u32 numTokens = 0;

      while(dotPos != string::npos)
      {
         dotPos = value.find_first_of('.', pos);
         token = value.substr(pos, dotPos - pos);
         u32 tokenVal = (u32)atoi(token.c_str());

         if((token.length() < 1) || (token.length() > 3) || (tokenVal > 255))
         {
            ostringstream description;
            description << "NotValidValue for IP address, each digit must be 0-255";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
            RETURN(false);
         }

         pos = dotPos + 1;
         numTokens++;
      }

      if(numTokens != 4)
      {
         ostringstream description;
         description << "NotValidValue for IP address, must have 4 values delimited with '.' e.g. 1.2.3.4";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         RETURN(false);
      }

      // This is just belt and braces, should be covered by token test above.
      if((value.find_first_of('.') == 0) || (value.find_last_of('.') == (value.length() - 1)))
      {
         ostringstream description;
         description << "NotValidValue for IP address, cannot start or end with '.'";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         RETURN(false);
      }

      RETURN(true);
   }

   RETURN(false);
}

bool ValidatorIpAddress::ValidateIpv6(const std::string& value,ValidationFailureDescriptor& failureDescriptor)
{
   int countchars = 0,countcolon = 0,countdoublecolon = 0;
   bool validated = true,doublecolonnow=false;

   for(size_t pos = 0;pos < value.length();pos++)
   {
      if((value.at(pos) >= 'A' && value.at(pos) <= 'F')||
            (value.at(pos) >= 'a' && value.at(pos) <= 'f')||
            (value.at(pos) >= '0' && value.at(pos) <= '9'))
      {
         countchars++;
         doublecolonnow = false;
      }
      else if(value.at(pos) == ':')
      {
         if(doublecolonnow)
         {
            validated = false;
            break;
         }
         else
         {
            doublecolonnow = false;
         }

         if((pos < value.length()-1)&&(value.at(pos + 1) == ':'))
         {
            doublecolonnow = true;
            countdoublecolon++;
            pos++;
         }
         else
         {
            countcolon ++;
         }
         countchars = 0;
      }
      else
      {
         validated = false;
         break;
      }

      if(countchars > 4 || countcolon > 7 ||countdoublecolon > 1)
      {
         validated = false;
         break;
      }
   }
   if((!validated)||((countcolon < 7) && (countdoublecolon == 0)))
   {
      ostringstream description;
      description << "NotValidValue for IP address.";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
      validated = false;
   }
   return validated;
}
