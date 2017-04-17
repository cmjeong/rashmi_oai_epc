///////////////////////////////////////////////////////////////////////////////
//
// Filename.cpp
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
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Filename.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Filename::Filename( std::string filename) :
    std::string( filename )
{
}

Filename::Filename( std::string dir, std::string notdir) :
    std::string( dir )
{
    bool dirEndsInSlash = EndsWithSlash(*this);

    if( !dirEndsInSlash )
    {
        append("/");
    }

    append(notdir);
}

Filename::Filename( std::string dir, std::string notDirLessSuffix, std::string suffix) :
    std::string( dir )
{
    bool dirEndsInSlash = EndsWithSlash(*this);

    if( !dirEndsInSlash )
    {
        append("/");
    }

    append(notDirLessSuffix);

    AppendSuffix( suffix );
}

Filename Filename::GetNotDir() const
{
    return substr( find_last_of("/\\") + 1 );
}

void Filename::SetNotDir( std::string newNotDir )
{
    *this = GetDir();
    append( newNotDir );
}

Filename Filename::GetDir() const
{
    return substr( 0, find_last_of("/\\") + 1);
}

void Filename::SetDir( std::string newDir )
{
    *this = GetNotDir();

    bool newDirEndsInSlash = EndsWithSlash(newDir);

    if( !newDirEndsInSlash )
    {
        insert( 0, "/");
    }

    insert( 0, newDir );
}

Filename Filename::GetBasename() const
{
    size_t positionOfLastSlash = find_last_of("/\\");
    size_t positionOfLastDot   = find_last_of(".");

    bool noSlashFound = (positionOfLastSlash == npos);
    bool lastDotMarksSuffixSeparation = (positionOfLastSlash > positionOfLastDot);

    if(noSlashFound || lastDotMarksSuffixSeparation)
    {
        return substr( 0, positionOfLastDot );
    }
    else
    {
        return *this;
    }
}

void Filename::SetBasename( std::string newBasename )
{
    *this = GetSuffix();
    insert( 0, newBasename );
}

std::string Filename::GetSuffix() const
{
    size_t positionOfLastSlash = find_last_of("/\\");
    size_t positionOfLastDot   = find_last_of(".");

    bool noSlashFound = (positionOfLastSlash == npos);
    bool lastDotMarksSuffixSeparation = (positionOfLastSlash > positionOfLastDot);

    if(noSlashFound || lastDotMarksSuffixSeparation)
    {
        return substr( positionOfLastDot );
    }
    else
    {
        return string("");
    }
}

void Filename::SetSuffix( std::string newSuffix )
{
    *this = GetBasename();

    AppendSuffix( newSuffix );
}


bool Filename::EndsWithSlash( const string & s)
{
    return ( s.find_last_of("/\\") == (s.length() - 1));
}

void Filename::AppendSuffix( const string & s)
{
    if( !s.empty() )
    {
        bool newSuffixStartsWithDot = (s.length() > 0 && s.at(0) == '.');

        if( !newSuffixStartsWithDot )
        {
            append(".");
        }

        append(s);
    }
}


}
