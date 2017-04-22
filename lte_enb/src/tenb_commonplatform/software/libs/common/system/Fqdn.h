///////////////////////////////////////////////////////////////////////////////
//
// Fqdn.h
//
// Fqdn class containing with factory methods for
// constructing from a string with fegular expression
// validation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Fqdn_h_
#define __Fqdn_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <set>
#include <Radisys.h>
#include <system/Regex.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace std;

#define ERE_FQDN   "([[:alnum:]\\-]+)((\\.([[:alnum:]\\-]+))*)"

namespace threeway
{


class Fqdn
{
public:
    Fqdn();
    Fqdn( const string & fqdn);              // e.g.  www.bbc.co.uk

    static const u16 MaxLength = 0xfff;
    static shared_ptr<Fqdn> FromString( const string & url );
    static bool Validate(const string & fqdnString );

    virtual ~Fqdn() {}

    void Set(  const string & fqdn  );

    bool IsNull() const;
    static bool ValidateIpv6String(const string& value);

    const string & ToString() const;

    static const char * Null;

private:
    static Regex fqdnRegex;


    string m_fqdn;
};

}

#endif
