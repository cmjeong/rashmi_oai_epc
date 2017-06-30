///////////////////////////////////////////////////////////////////////////////
//
// MacAddress.cpp
//
// See header file for documentation.
//
// Copyright � 3 Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <string.h>

#include <system/Trace.h>
#include <system/Exception.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MacAddress.h"


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const u32 MAC_ADDRESS_LENGTH = 17; // 00:01:02:ab:cd:ef

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MacAddress::MacAddress() :
    m_isSet(false)
{
    ENTER();

    m_macAddress[0] = '\0';

    EXIT();
}

MacAddress::MacAddress(const char * macAddress) :
    m_isSet(true)
{
    ENTER();

    Set(macAddress);

    EXIT();
}

MacAddress::~MacAddress()
{
    ENTER();
    EXIT();
}

void MacAddress::Clear()
{
    ENTER();

    m_macAddress[0] = '\0';
    m_isSet = false;

    EXIT();
}

void MacAddress::Set(const char *macAddress)
{
    ENTER();

    // Check length is correct.
    size_t strLen = strlen(macAddress);
    if((u32)strLen != MAC_ADDRESS_LENGTH)
    {
        EXIT();
        throw Exception(__FILE__, __LINE__, "MacAddress: MAC address is wrong length (%" PRIu32 ")", (u32)strLen);
    }

    // Check separators are correct.
    if((macAddress[2] != ':') ||
       (macAddress[5] != ':') ||
       (macAddress[8] != ':') ||
       (macAddress[11] != ':') ||
       (macAddress[14] != ':'))
    {
        EXIT();
        throw Exception(__FILE__, __LINE__, "MacAddress: MAC address bad format (%s)", macAddress);
    }

    // Check contains only valid characters.
    for(u32 i = 0; i < MAC_ADDRESS_LENGTH; i++)
    {
        char ch = toupper(macAddress[i]);
        if(ch != ':' &&
           (ch < '0' || ch > '9') &&
           (ch < 'A' || ch > 'F'))
        {
            EXIT();
            throw Exception(__FILE__, __LINE__, "MacAddress: MAC address contains invalid characters (%c)", ch);
        }
    }

    // MAC address looks good.
    memcpy(m_macAddress, macAddress, MAC_ADDRESS_LENGTH);
    m_macAddress[MAC_ADDRESS_LENGTH] = '\0';
    m_isSet = true;

    EXIT();
}

void MacAddress::Set(u8 d0, u8 d1, u8 d2, u8 d3, u8 d4, u8 d5)
{
    ENTER();

    snprintf(m_macAddress, sizeof(m_macAddress), "%02X:%02X:%02X:%02X:%02X:%02X", d0, d1, d2, d3, d4, d5);

    EXIT();
}

const char * MacAddress::Get() const
{
    ENTER();

    RETURN(m_macAddress);
}

}
