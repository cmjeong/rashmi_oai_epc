///////////////////////////////////////////////////////////////////////////////
//
// Url.h
//
// Manage a string representing an URL.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Url_h_
#define __Url_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <set>
#include <Radisys.h>

#include <system/Fqdn.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace std;


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


class Url
{
    // http://en.wikipedia.org/wiki/Uniform_Resource_Locator
public:
    Url();
    Url( const string & url);              //  http://www.bbc.co.uk:80/index.html

    static shared_ptr<Url> FromString( const string & url );
    static bool Validate(const string & url );
    virtual ~Url() {}

    void Set( const string & url  );
    string Get() const;

    void SetScheme( const string & protocol );
    const string & GetScheme() const ;

    void SetFqdn( const Fqdn & fqdn  );
    const Fqdn & GetFqdn() const;

    void SetPort( u16 port );
    u16 GetPort( void ) const;

    void SetPath( const string & path  );
    string & GetPath( string & path ) const;

    void Reset();

    bool IsNull() const;

    string ToString() const {return Get();}

    static const char * Null;
private:
    class UrlTokens
    {
    public:
        UrlTokens() : port(0) {}

        string scheme;
        Fqdn   fqdn;
        u16    port;
        string path;
    };


    static Regex urlRegex;
    static Regex schemeRegex;
    static Regex fqdnRegex;
    static Regex portRegex;
    static Regex pathRegex;
    static Regex urlRegexIpv6;
    static Regex ipv6Regex;
    UrlTokens m_url;
};

}

#endif
