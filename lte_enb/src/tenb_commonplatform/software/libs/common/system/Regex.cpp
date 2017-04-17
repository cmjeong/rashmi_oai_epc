///////////////////////////////////////////////////////////////////////////////
//
// Regex.cpp
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

#include "Regex.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Regex::Regex( const string & regularExpression, int flags) :
    m_regularExpression(regularExpression)
{
    bool compilationOk = (REG_NOERROR == regcomp( &m_regex, m_regularExpression.c_str(), flags ));

    RSYS_ASSERT_PRINTF( compilationOk, "Regex compilation failure (%s)", m_regularExpression.c_str() );
}

Regex::~Regex()
{
    regfree(&m_regex);
}

bool Regex::Compare( const char * cStr, u16 * length )
{
    /**
     * Use array of 1 for the regex result.
     * This makes interpretation a doddle.
     */
    regmatch_t match[1];

    bool matched = (REG_NOERROR == regexec( &m_regex, cStr, 1, match, 0) );

    if(matched)
    {
        TRACE_PRINTF_LEV( TRACE_VERBOSE,
                "Regular expression OK (%i), \"%.*s\" == \"%s\"",
                (match[0].rm_eo - match[0].rm_so),
                (match[0].rm_eo - match[0].rm_so),
                cStr,
                m_regularExpression.c_str());
    }
    else
    {
        TRACE_PRINTF("Regular expression compare failure \"%s\" != \"%s\"", cStr, m_regularExpression.c_str());
    }

    if( length )
    {
        if( matched )
        {
            *length = match[0].rm_eo - match[0].rm_so;
        }
        else
        {
            *length = 0;
        }
    }

    return matched;
}

const char * Regex::ToString()
{
    return m_regularExpression.c_str();
}


}
