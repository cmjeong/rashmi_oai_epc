///////////////////////////////////////////////////////////////////////////////
//
// MacAddress.h
//
// Stores an ethernet MAC address.
//
// Copyright © 3 Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MacAddress_h_
#define __MacAddress_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>

namespace threeway
{
    
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MacAddress
{
public:
    // Construct a blank MacAddress.
    MacAddress();
    // Construct by null terminated string e.g. "00:01:02:AB:CD:EF\0"
    MacAddress(const char * macAddress);
    // Destructor.
    virtual ~MacAddress();

    /**
     * Clear (unset) current value.
     */
    void Clear();

    /**
     * Set by null terminated string e.g. "00:01:02:AB:CD:EF\0".
     */
    void Set(const char *macAddress);

    /**
     * Set by digits.
     */
    void Set(u8 d0, u8 d1, u8 d2, u8 d3, u8 d4, u8 d5);

    // Get as string e.g. "00:01:02:AB:CD:EF\0"
    const char * Get() const;
    
    // Check to see if it has ever been set to anything.
    bool IsSet() const { return m_isSet; };
    
private:
    bool m_isSet;
    char m_macAddress[18]; // "00:01:02:AB:CD:EF" + null
};

}

#endif
