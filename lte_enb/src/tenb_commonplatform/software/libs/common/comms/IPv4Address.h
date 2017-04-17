///////////////////////////////////////////////////////////////////////////////
//
// IPv4Address.h
//
// General purpose class representing a v4 IP address.
//
// Copyright � 3 Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IPv4Address_h_
#define __IPv4Address_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <netinet/ip.h>
#include <vector>

#include <3waytypes.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IPv4Address
{
public:
    IPv4Address();
    IPv4Address(const char * ipAddress);
    IPv4Address(u8 digit0, u8 digit1, u8 digit2, u8 digit3);
    IPv4Address(u32 ipAddress);
    IPv4Address(const IPv4Address& rhs);
    virtual ~IPv4Address();

    /**
     * Clear (unset) the current value.
     */
    void Clear();

    // Set the IP address by individual bytes - e.g. Set(192, 168, 0, 1);
    void SetDigits(u8 digit0, u8 digit1, u8 digit2, u8 digit3);
    // Set by a 32 bit value NBO.  I.e. on Intel, first digit of IP address is LSByte.
    void Set(u32 ipAddress);
    // Set by string e.g. "127.0.0.1"
    void Set(const char *ipAddress);
    // Set by struct in_addr.
    void Set(struct in_addr ipAddress);

    // Get the IP address by individual bytes.
    // return - true if IP address has been set, false otherwise.
    bool GetDigits(u8 &digit0, u8 &digit1, u8 &digit2, u8 &digit3) const;
    // Get as a 32 bit value NBO.  I.e. on Intel, first digit of IP address is LSByte.
    // return - true if IP address has been set, false otherwise.
    bool Get(u32 &ipAddress) const;
    u32  Get() const;               // Use this form if confident IP address has already been set.
    // Get as string e.g. "127.0.0.1"
    // Client MUST ensure ipAddress points at at least 16 bytes of allocated memory.
    bool Get(char *ipAddress) const;

    // Check to see if it has ever been set to anything.
    bool IsSet() const { return m_isSet; };

    // Assignment.  Saves copying m_asString which isn't necessary.
    IPv4Address& operator=(const IPv4Address& rhs);

    // Check for identical IP addresses.
    bool operator==(const IPv4Address &ipAddress) const;
    bool operator!=(const IPv4Address &ipAddress) const;

    // Operators to support STL maps.
    bool operator<(const IPv4Address &ipAddress) const;
    bool operator>(const IPv4Address &ipAddress) const;

    // Increment.  So 192.168.0.1 -> 192.168.0.2 and 192.168.0.255 -> 192.168.1.0
    const IPv4Address& operator++();

    // Convenience function using local storage to convert to string.
    const char *ToString() const;

    // Static using ioctl to retrieve the address with an associated adaptor.  Request
	// format is "eth0", "eth1", etc.
    static bool GetEthernetAddress (const char *ethernetDevice, IPv4Address &ipAddress);

    /**
     * GetHostByName will BLOCK during the name resolution,
     * so use sparingly.
     * Consider only using just prior to a connect - i.e. when blocking
     * is unavoidable anyway.
     */
    static size_t GetHostByName(const char * fqdn, std::vector<IPv4Address> & addresses );

private:
    bool m_isSet;
    u32 m_ipAddress; // Stored NBO - first digit of IP address is first byte in memory.
    mutable char m_asString[16];
};

// Add.  So 192.168.0.255 + 2 = 192.168.1.1
IPv4Address operator+(IPv4Address ipAddress, s32 increment);

}

#endif
