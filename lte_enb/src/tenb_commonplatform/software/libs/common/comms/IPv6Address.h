///////////////////////////////////////////////////////////////////////////////
//
// IPv6Address.h
//
// General purpose class representing a v4 IP address.
//
// Copyright Radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IPv6Address_h_
#define __IPv6Address_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <netinet/ip.h>
#include <vector>
#include <string>
#include <3waytypes.h>

#define MAXSIZE 39
namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IPv6Address 
{
public:
 
    IPv6Address();
    IPv6Address(const char * ipAddress);
    /*Convert the IPAddress digits in hexadecimal before calling the constructor*/
    IPv6Address(u16 hexdigit0, u16 hexdigit1, u16 hexdigit2, u16 hexdigit3, u16 hexdigit4, u16 hexdigit5, u16 hexdigit6, u16 hexdigit7);
    /*Convert the IPAddress array in hexadecimal before calling the constructor*/
    IPv6Address(u16 ipAddress[]);
    IPv6Address(const IPv6Address& rhs);
    virtual ~IPv6Address();

    /**
     * Clear (unset) the current value.
     */
    void Clear();

    // Set the IP address by individual bytes - e.g. Set(0x921, 0x1681,0x0000, 0x1000,0xabcd,0xffff,0x2222,0x1111);
    // Convert the digits to hexadecimal before calling
    void SetDigits(u16 hexdigit0, u16 hexdigit1, u16 hexdigit2, u16 hexdigit3, u16 hexdigit4, u16 hexdigit5, u16 hexdigit6, u16 hexdigit7);
    // Set the ip address 
    void Set(u16 ipAddress[]);
    // Set by string e.g. "abcd:aaaa:0000:0000:7777:2222:2222:5543"
    void Set(const char *ipAddress);
    // Set by struct in6_addr.
    void Set(struct in6_addr ipAddress);

    // Get the IP address by individual bytes.
    // return - true if IP address has been set, false otherwise.
    bool GetDigits(u16 &digit0, u16 &digit1, u16 &digit2, u16 &digit3, u16 &digit4, u16 &digit5, u16 &digit6, u16 &digit7) const;
    bool GetDigitsU8(u8 digitu8[]) const;
    // Get Ip address.
    // return - true if IP address has been set, false otherwise.
    bool Get(u16 ipAddress[]) const;
    bool Get(u8 ipAddress[]) const;
    struct in6_addr  Get() const;               // Use this form if confident IP address has already been set.
    // Get as string e.g. "abcd:aaaa:0000:0000:7777:2222:2222:5543"
    bool Get(char *ipAddress) const;

    // Check to see if it has ever been set to anything.
    bool IsSet() const { return m_isSet; };
    
    /*//Converts digit in hexadecimal digit to return it in format as entered by user*/
    std::string DecimalToHexadecimal(u16 digit) const;
    // Assignment.  Saves copying m_asString which isn't necessary.
    IPv6Address& operator=(const IPv6Address& rhs);

    // Check for identical IP addresses.
    bool operator==(const IPv6Address &ipAddress) const;
    bool operator!=(const IPv6Address &ipAddress) const;

    // Operators to support STL maps.
    bool operator<(const IPv6Address &ipAddress) const;
    bool operator>(const IPv6Address &ipAddress) const;

    // Convenience function using local storage to convert to string.
    const char *ToString() const;

    // Static using ioctl to retrieve the address with an associated adaptor.  Request
	// format is "eth0", "eth1", etc.
    static bool GetEthernetAddress (const char *ethernetDevice, IPv6Address &ipAddress);

    /**
     * GetHostByName will BLOCK during the name resolution,
     * so use sparingly.
     * Consider only using just prior to a connect - i.e. when blocking
     * is unavoidable anyway.
     */
    static size_t GetHostByName(const char * fqdn, std::vector<IPv6Address> & addresses );

private:
    bool m_isSet;
    struct in6_addr m_ipAddress;// Stored NBO - first digit of IP address is first byte in memory.
    mutable char m_asString[MAXSIZE];
    
};


}

#endif
