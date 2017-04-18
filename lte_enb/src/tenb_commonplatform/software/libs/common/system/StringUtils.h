///////////////////////////////////////////////////////////////////////////////
//
// StringUtils.h
//
// Helper functions for converting STL containers to strings and streams
// and other handy functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __StringUtils_h_
#define __StringUtils_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#endif

#include <Radisys.h>

#ifdef __cplusplus
#include <system/Trace.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes / Functions
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
namespace threeway
{

class StringUtils
{
public:
    static u32 SplitString(const string& input,
                           const string& delimiter,
                           vector<string>& results);
	static int tokenise(const string& input, vector<string>& sv);
    /***
     * This escapes a string (" -> \", \ -> \\ and <newline> -> \n) and encapsulates it in quotes.
     * e.g. string1 -> "string1"
     *      string\2 -> "string\\2"
     *      string"3 -> "string\"3"
     *      string   ---\ "string\n4"
     *      4        ---/
     *      string\"5 -> "string\\\"5"
     * @param m_value raw string
     * @return escaped string
     */
    static std::string EscapeString (const std::string & m_value);

    /***
     * This function takes a string that is encapulated and escaped and returns an unencapsulated and unescaped string
     *   i.e. "string\"1" -> string"1
     *
     * @param m_value escaped string
     * @return unescaped string
     */
    static std::string UnEscapeString (const std::string & m_value);


    template < typename T >
    static bool ConvertStringToInteger( const string & valueAsString, T & value)
    {
        bool conversionOk = false;

        if(!valueAsString.empty())
        {
            bool hexadecimal = (valueAsString.substr(0,2) == "0x");

            stringstream conversionStream;

            if(hexadecimal) { conversionStream << hex; }

            conversionStream << valueAsString;
            conversionStream >> value;

            stringstream testStream;
            testStream << value;

            conversionOk = (    (conversionStream.str() == testStream.str())
                            || hexadecimal /* hexadecimal won't match! */);

            if(!conversionOk)
            {
                TRACE_PRINTF("StringUtils::ConvertStringToInteger error: valueAsString=\"%s\", conversionStream=\"%s\", testStream=\"%s\"", valueAsString.c_str(), conversionStream.str().c_str(), testStream.str().c_str());
            }
        }
        else
        {
            value = 0;
        }

        return conversionOk;
    }

    static bool ConvertStringToInteger( const string & valueAsString, vector<u32> & value);
    static bool ConvertStringToInteger( const string & valueAsString, vector<s32> & value);

    static void ConvertStringToBool( const string & valueAsString, bool & value)
    {
        value = false;
    
        if((0 == valueAsString.compare("true"))||(0 == valueAsString.compare("1")))
        {
           value = true; 
        }
    }
    static char* GetMibObjectInstanceNum(string mibDN);
    static void Trim(std::string &);
};

}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Safe version of strncpy.
 * Asserts if src is too long.
 */
char * strncpysafe(char *dest, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif
