///////////////////////////////////////////////////////////////////////////////
//
// Url.cpp
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

#include "Url.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


#define ERE_SCHEME     "([[:alnum:]]+:)?"
#define ERE_SCHEME_SS  "(" ERE_SCHEME "//)?"
#define ERE_PORTNUM    "(:[[:digit:]]+)?"
#define ERE_PATH       "(/[[:graph:]]*)?"
#define ERE_IPv6       "((([0-9a-fA-F]([0-9a-fA-F]?)([0-9a-fA-F]?)([0-9a-fA-F]?):)*)|:)(((:([0-9a-fA-F]([0-9a-fA-F]?)([0-9a-fA-F]?)([0-9a-fA-F]?)))*)|([0-9a-fA-F]([0-9a-fA-F]?)([0-9a-fA-F]?)([0-9a-fA-F]?))|:)"

#define URL_REGEX \
    ERE_SCHEME_SS \
    ERE_FQDN \
    ERE_PORTNUM \
    ERE_PATH

#define URL_REGEXIPv6 \
      ERE_SCHEME_SS \
      ERE_IPv6 \
      ERE_PORTNUM \
      ERE_PATH

const char * Url::Null = "0.0.0.0";

Regex Url::urlRegex(ERE_START URL_REGEX ERE_END);
Regex Url::schemeRegex(ERE_START ERE_SCHEME);
Regex Url::fqdnRegex(ERE_FQDN);
Regex Url::portRegex(ERE_PORTNUM);
Regex Url::pathRegex(ERE_PATH ERE_END);
Regex Url::urlRegexIpv6(ERE_START URL_REGEXIPv6 ERE_END);
Regex Url::ipv6Regex(ERE_IPv6);


shared_ptr<Url> Url::FromString( const string & urlString )
{
    shared_ptr<Url> url;

    if( Validate(urlString) )
    {
        url.reset(new Url(urlString));
    }

    return url;
}

bool Url::Validate(const string & urlString )
{
    bool validIpv4 = urlRegex.Compare(urlString.c_str());
    bool valid = true;
    if(!validIpv4)
    {
        bool validIpv6 = urlRegexIpv6.Compare(urlString.c_str());
        if(!validIpv6)
        {
           TRACE_PRINTF("Url validation failure (%s:%s).", urlRegex.ToString(), urlString.c_str());
           valid = false;
        }
    }

    return valid;
}


Url::Url()
{
    Reset();
}

void Url::Reset()
{
    Set(Url::Null);
}

Url::Url( const string & url)
{
    Set(url);
}

string Url::Get() const
{
    ostringstream outputUrl;

    if( m_url.scheme.size() )
    {
        outputUrl << m_url.scheme << "//";
    }

    outputUrl << m_url.fqdn.ToString();

    if( m_url.port )
    {
        outputUrl << ":" << m_url.port;
    }

    if( m_url.path.size() )
    {
        outputUrl << "/" << m_url.path;
    }

    return outputUrl.str();;
}

void Url::Set(  const string & url  )
{
    RSYS_ASSERT(Validate(url));

    const char * c = url.c_str();

    /**
     * The URL regular expression has been split apart into component parts
     * 1)   scheme://       (optional)
     * 2)   hostname
     * 3)   :port-num       (optional)
     * 4)   /path           (optional)
     */

    u16 length = 0;
    UrlTokens newUrl;

    if( schemeRegex.Compare(c, &length) )
    {
       if(length)
       {
          newUrl.scheme.assign( c, length );

          const u16 lengthOfSlashSlash = 2;
          length += lengthOfSlashSlash;
       }

       c += length;
       bool isIpv6=false;
       if( ipv6Regex.Compare(c,&length))
       {
          s32 portNbrLength = (string( c, length).length())-(string( c, length).find_last_of(":"));
          if((portNbrLength < length)&&(Fqdn::ValidateIpv6String(string( c, length-portNbrLength))))
          {
             newUrl.fqdn.Set(string( c, length-portNbrLength));
             c +=(length-portNbrLength);
             isIpv6=true;
          }
          else
          {
             TRACE_PRINTF("IPV6 chking failed Testing Fqdn received %s",string( c, length).c_str());
          }
       }
       
       if((!isIpv6)&&( fqdnRegex.Compare(c, &length) ))
       {
          if(length)
          {
             newUrl.fqdn.Set(string( c, length));
             c +=length;
          }
          else
          {
             TRACE_PRINTF("IPV4 URL Faild to compare regx");
          }
       }
       if( portRegex.Compare(c, &length) )
       {
          if(length)
          {
             const u16 lengthOfColon = 1;
             newUrl.port = strtoul( c + lengthOfColon, NULL, 10 );
             TRACE_PRINTF("IPV6 URL Testing portnbr received %d",newUrl.port );
          }

          c += length;

          if( pathRegex.Compare(c, &length) )
          {
             if(length)
             {
                newUrl.path.assign( c, length );

                TRACE_PRINTF("IPV6 URL Testing path received %s",newUrl.path.c_str());
             }
          }
       }
    }

    m_url = newUrl;
}

void Url::SetScheme( const string & scheme )
{
    u16 length = 0;

    const char * c = scheme.c_str();

    if( schemeRegex.Compare(c, &length) )
    {
        m_url.scheme.assign( c, length );
    }
    else
    {
        TRACE_PRINTF("Url::SetScheme failed (try appending \":\"?).")
    }
}

const string & Url::GetScheme( ) const
{
    return m_url.scheme;
}

void Url::SetFqdn( const Fqdn & fqdn  )
{
    m_url.fqdn = fqdn;
}

const Fqdn & Url::GetFqdn() const
{
    return m_url.fqdn;
}

void Url::SetPort( u16 port )
{
    m_url.port = port;
}

u16 Url::GetPort( void ) const
{
    return m_url.port;
}


bool Url::IsNull() const
{
    return m_url.fqdn.IsNull();
}

}
