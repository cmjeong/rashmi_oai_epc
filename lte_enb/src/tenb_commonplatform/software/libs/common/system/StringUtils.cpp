///////////////////////////////////////////////////////////////////////////////
//
// StringUtils.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "StringUtils.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

std::string StringUtils::EscapeString (const std::string & value)
{
    std::string escapedString("\"");
    for (std::string::const_iterator valueIter = value.begin();
            not(valueIter == value.end());
            ++valueIter)
    {
        switch (*valueIter)
        {
        case '\\': // backslash
            escapedString.append("\\\\");
            break;
        case '"': // quote
            escapedString.append("\\\"");
            break;
        case '\n': // newline
            escapedString.append("\\n");
            break;
        default:
            escapedString.push_back(*valueIter);
            break;
        }
    }
    escapedString.push_back('\"');

    return(escapedString);
}

std::string StringUtils::UnEscapeString (const std::string & value)
{
    RSYS_ASSERT_PRINTF(value.size() >= 2, "Value too short: %s", value.c_str());

    std::string unEscapedString;

    for (std::string::const_iterator valueIter = value.begin() + 1;
            not((valueIter+1) == value.end());
            ++valueIter)
    {
        if (not(*valueIter == '\\'))
        {
            unEscapedString.push_back(*valueIter);
        }
        else
        {
            // advance escapedString pointer
            valueIter++;
            if ((valueIter + 1) == value.end()) // this indicates a bad string
            {
                break;
            }
            switch (*valueIter)
            {
            case 'n':
                unEscapedString.push_back('\n');
                break;
            default:
                unEscapedString.push_back(*valueIter);
                break;
            }
        } //
    } // for

    return(unEscapedString);
}


u32 StringUtils::SplitString(const string& input,
                             const string& delimiter,
                             vector<string>& results)
{
    ENTER();

    u32 currentPos = 0;
    u32 delimPos = 0;
    u32 inputLen = input.size();
    u32 delimLen = delimiter.size();

    results.clear();
    while(currentPos < inputLen)
    {
        delimPos = input.find(delimiter, currentPos);
        if(delimPos == string::npos)
        {
            // No more delimiters but we have some string left so
            // grab the remainder as the last token.
            results.push_back(input.substr(currentPos));
            // And skip to the end.
            currentPos = inputLen;
        }
        else if(delimPos > currentPos)
        {
            // There is a delimiter somewhere out there.
            // Grab the substring and add to the list of tokens.
            results.push_back(input.substr(currentPos, delimPos-currentPos));
            // And skip over the delimiter.
            currentPos = delimPos + delimLen;
        }
        else
        {
            // Current pos points at a delimiter, skip over it.
            currentPos += delimLen;
        }
    }

    RETURN(results.size());
}

/**
 * Converts a string sequence of comma separated values into a vector of values.
 * The CSV sequence can contain range values
 *  e.g. "1,5..9,11" == "1,5,6,7,8,9,11"
 */
bool StringUtils::ConvertStringToInteger( const string & commaSeparartedValuesAsString, vector<u32> & valuesAsVector)
{
    bool conversionOk = true;
    stringstream arrayStream;
    std::string  valueAsString;

    arrayStream << commaSeparartedValuesAsString;

    for( std::getline(arrayStream, valueAsString, ',');
         !arrayStream.fail();
         std::getline(arrayStream, valueAsString, ','))
    {
        if(valueAsString.empty() || valueAsString.at(0) == '-')
        {
            conversionOk = false;
            continue;
        }

        size_t dotdotPos = valueAsString.find("..");

        if( dotdotPos == string::npos )
        {
            u32 valueU32 = 0;
            if( StringUtils::ConvertStringToInteger( valueAsString, valueU32 ) )
            {
                valuesAsVector.push_back(valueU32);
            }
            else
            {
                conversionOk = false;
            }
        }
        else
        {
            // rangeStart..rangeEnd
            const u32 lenDotDot = 2;
            u32 rangeStart;
            u32 rangeEnd;
            if(    StringUtils::ConvertStringToInteger( valueAsString.substr(0, dotdotPos), rangeStart)
                && StringUtils::ConvertStringToInteger( valueAsString.substr(dotdotPos + lenDotDot), rangeEnd ) )
            {
                while(rangeEnd >= rangeStart)
                {
                    valuesAsVector.push_back(rangeStart);
                    rangeStart++;
                }
            }
            else
            {
                conversionOk = false;
            }
        }
    }

    return conversionOk;
}

bool StringUtils::ConvertStringToInteger( const string & commaSeparartedValuesAsString, vector<s32> & valuesAsVector)
{
    bool conversionOk = true;
    stringstream arrayStream;
    std::string  valueAsString;

    arrayStream << commaSeparartedValuesAsString;

    for( std::getline(arrayStream, valueAsString, ',');
         !arrayStream.fail();
         std::getline(arrayStream, valueAsString, ','))
    {
        if(valueAsString.empty())
        {
            conversionOk = false;
            continue;
        }

        size_t dotdotPos = valueAsString.find("..");

        if( dotdotPos == string::npos )
        {
            s32 valueS32 = 0;
            if( StringUtils::ConvertStringToInteger( valueAsString, valueS32 ) )
            {
                valuesAsVector.push_back(valueS32);
            }
            else
            {
                conversionOk = false;
            }
        }
        else
        {
            // rangeStart..rangeEnd
            const u32 lenDotDot = 2;
            s32 rangeStart;
            s32 rangeEnd;
            if(    StringUtils::ConvertStringToInteger( valueAsString.substr(0, dotdotPos), rangeStart)
                && StringUtils::ConvertStringToInteger( valueAsString.substr(dotdotPos + lenDotDot), rangeEnd ) )
            {
                while(rangeEnd >= rangeStart)
                {
                    valuesAsVector.push_back(rangeStart);
                    rangeStart++;
                }
            }
            else
            {
                conversionOk = false;
            }
        }
    }

    return conversionOk;
}

int StringUtils::tokenise(const string& input, vector<string>& sv)
{
   unsigned int spacePos;
   unsigned int quotePos;
   unsigned int quoteLastPos;
   string str = input;

   while (str.size())
   {
      string token;

      // Eat leading spaces
      while((spacePos = str.find(" ")) == 0)
      {
         str = str.substr(1);
      }
      quotePos = str.find("\"");
      quoteLastPos = str.find_last_of("\"");
      if ((quotePos != string::npos) && ((spacePos == string::npos) || (spacePos > quotePos)))
      {
         if (quotePos != 0)
         {
            sv.push_back(str);
            str.erase();
            continue;
         }
         token = str.substr(0, quotePos);
         token = str.substr(0,quoteLastPos+1);
         sv.push_back(token);
         if(str.size() > quoteLastPos + 1)
         {
            str = str.substr(quoteLastPos+2);
         }
         else
         {
            str = str.substr(quoteLastPos+1);
         }
      }
      spacePos = str.find(" ");
      if (spacePos != string::npos)
      {
         sv.push_back(str.substr(0, spacePos));
         str = str.substr(spacePos + 1);
      }
      else
      {
         if(str.size())
         {
            sv.push_back(str);
         }
         str.erase();
      }
   }
   RETURN (sv.size());
}

char * StringUtils::GetMibObjectInstanceNum(string dn)
{
   char* dnchar = const_cast<char*>(dn.c_str());
   char * token = strtok(dnchar,".");
   char * lasttoken = NULL;
   while(token != NULL)
   {
      lasttoken = token;
      token = strtok(NULL,".");
   }
   return lasttoken;
}

void StringUtils::Trim(std::string &str)
{
   for(size_t i=0;i<str.length();i++)
   {

      if(str.at(i)==' ')
      {
         str.erase(i,1);
      }
   }
}
}

char * strncpysafe(char *dest, const char *src, size_t n)
{
    ENTER();

    RSYS_ASSERT(dest != NULL);
    RSYS_ASSERT(src != NULL);
    size_t srcLen = strlen(src);
    RSYS_ASSERT_PRINTF(srcLen < n, "src \"%s\" is too long for dest, n=%"PRIu32, src, (u32)n);
    
    if (((src + srcLen) < dest) || ((dest + n) < src))
    {
       // src and dest don't overlap
       size_t i;

       for (i = 0 ; i < srcLen ; i++)
       {
          dest[i] = src[i];
       }
       dest[i] = '\0'; // The assert above ensures we are safe to bung a null terminator on.
    }
    else
    {
       //memory overlap noted
       bcopy(src,dest,srcLen);
       dest[srcLen]='\0';
    } 

    

    RETURN(dest);
}
