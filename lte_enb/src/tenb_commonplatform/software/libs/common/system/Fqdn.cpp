///////////////////////////////////////////////////////////////////////////////
//
// Fqdn.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <cstdlib>
#include <string>
#include <sstream>

#include <system/Trace.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Fqdn.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

#define FQDN_REGEX ERE_START \
                   ERE_FQDN \
                   ERE_END

const char * Fqdn::Null = "0.0.0.0";

Regex Fqdn::fqdnRegex( FQDN_REGEX );

shared_ptr<Fqdn> Fqdn::FromString( const string & fqdnString )
{
    shared_ptr<Fqdn> fqdn;

    if( Validate(fqdnString) )
    {
        fqdn.reset(new Fqdn(fqdnString));
    }

    return fqdn;
}

bool Fqdn::Validate(const string & fqdnString )
{
    bool valid = fqdnRegex.Compare(fqdnString.c_str());
    if(!valid && (!ValidateIpv6String(fqdnString)))
    {   
        TRACE_PRINTF("Fqdn validation failure (%s).", fqdnString.c_str());
    }
    else
    {
       valid = true;
    }

    return valid;
}


Fqdn::Fqdn() :
    m_fqdn(Fqdn::Null)
{
}

Fqdn::Fqdn( const string & fqdn) :
    m_fqdn(fqdn)
{
    RSYS_ASSERT(Validate(m_fqdn));
}

const string & Fqdn::ToString(  ) const
{
    return m_fqdn;
}

void Fqdn::Set(  const string & fqdnString )
{
    RSYS_ASSERT(Validate(fqdnString));
    m_fqdn = fqdnString;
}

bool Fqdn::IsNull() const
{
    return (0 == m_fqdn.compare(Fqdn::Null));
}

bool Fqdn::ValidateIpv6String(const string& value)
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
   if(countcolon < 7 && countdoublecolon == 0)
   {
      validated = false;
   }
  return validated;
}


}
