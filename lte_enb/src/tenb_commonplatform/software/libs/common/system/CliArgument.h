///////////////////////////////////////////////////////////////////////////////
//
// CliArgument.h
//
// Derive from string to provide various helper functions for CLI command
// handling functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliArgument_h_
#define __CliArgument_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <iostream>

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Template Functions
///////////////////////////////////////////////////////////////////////////////

template <class T>
bool FromString(T& t,
                const std::string& s,
                std::ios_base& (*f)(std::ios_base&))
{
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class CliArgument : public std::string
{
public:
    /**
     * Default constructor.
     */
    CliArgument() {};

    /**
     * Construct with a string.  Just sets the base class (std::string) to this value.
     */
    CliArgument(const std::string& str);
    virtual ~CliArgument() {};

    /**
     * Check if the string could be interpreted as a boolean.
     * I.e. is true, false, 1, 0, on, off (case insensitive).
     *
     * \return true if string could be interpreted as a boolean.
     */
    bool IsBool() const;

    /**
     * Get the value of the string as a boolean.
     *
     * \return true if string is a case insensitive match of "true", "1" or "on",
     *         false otherwise.
     */
    bool GetBool() const;

    /**
     * Alternatives to GetBool() that may be easier to read.
     */
    bool IsTrue() const { return GetBool(); }
    bool IsFalse() const { return !GetBool(); }

    /**
     * Check if the value of the string can be interpreted as
     * an unsigned 32-bit int.  Will check for hex and decimal values.
     *
     * \return true if string can be interpreted as s32.
     */
    bool IsU32() const;

    /**
     * Get the value of the string as a u32.
     *
     * \return u32 value or 0 if string cannot be interpreted as u32.
     */
    u32 GetU32() const;

    /**
     * Check if the value of the string can be interpreted as
     * a signed 32-bit int.  Will check for decimal values only.
     *
     * \return true if string can be interpreted as s32.
     */
    bool IsS32() const;

    /**
     * Get the value of the string as a s32.
     *
     * \return s32 value or 0 if string cannot be interpreted as s32.
     */
    s32 GetS32() const;

    /**
     * Do case insensitive compare.
     *
     * \return true if the strings match, ignoring case.
     */
    bool CaselessEquals(const char * compareStr) const;

protected:

private:

};

}

#endif
