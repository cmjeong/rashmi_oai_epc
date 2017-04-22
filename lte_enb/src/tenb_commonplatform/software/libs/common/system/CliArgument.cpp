///////////////////////////////////////////////////////////////////////////////
//
// CliArgument.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliArgument.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

CliArgument::CliArgument(const std::string& str)
{
    ENTER();

    assign(str);

    EXIT();
}


bool CliArgument::IsBool() const
{
    ENTER();

    if(CaselessEquals("on") ||
       CaselessEquals("off") ||
       CaselessEquals("1") ||
       CaselessEquals("0") ||
       CaselessEquals("true") ||
       CaselessEquals("false"))
    {
        RETURN(true);
    }

    RETURN(false);
}

bool CliArgument::GetBool() const
{
    ENTER();

    if(CaselessEquals("on") ||
       CaselessEquals("1") ||
       CaselessEquals("true"))
    {
        RETURN(true);
    }

    RETURN(false);
}

bool CliArgument::IsU32() const
{
    ENTER();

    u32 u32Value = 0;

    if(find("-") != npos)
    {
        // Added for old toolchains that don't fail if string has
        // a '-' in it when converting to unsigned value.
        RETURN(false);
    }

    if(find("0x") == 0)
    {
        if(FromString<u32>(u32Value, *this, std::hex))
        {
            RETURN(true);
        }
        RETURN(false);
    }

    if(FromString<u32>(u32Value, *this, std::dec))
    {
        RETURN(true);
    }
    RETURN(false);
}

u32 CliArgument::GetU32() const
{
    ENTER();

    u32 u32Value = 0;

    if(find("-") != npos)
    {
        // Added for old toolchains that don't fail if string has
        // a '-' in it when converting to unsigned value.
        RETURN(0);
    }

    if(find("0x") == 0)
    {
        if(FromString<u32>(u32Value, *this, std::hex))
        {
            RETURN(u32Value);
        }
        RETURN(0);
    }

    if(FromString<u32>(u32Value, *this, std::dec))
    {
        RETURN(u32Value);
    }

    RETURN(0);
}

bool CliArgument::IsS32() const
{
    ENTER();

    s32 s32Value = 0;

    if(FromString<s32>(s32Value, *this, std::dec))
    {
        RETURN(true);
    }

    RETURN(false);
}

s32 CliArgument::GetS32() const
{
    ENTER();

    s32 s32Value = 0;

    if(FromString<s32>(s32Value, *this, std::dec))
    {
        RETURN(s32Value);
    }

    RETURN(0);
}

bool CliArgument::CaselessEquals(const char * compareStr) const
{
    ENTER();

    RETURN(strcasecmp(compareStr, c_str()) == 0);
}
