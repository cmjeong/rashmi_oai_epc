///////////////////////////////////////////////////////////////////////////////
//
// ConfigurationFile.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/stat.h>
#include <sstream>
#include <string.h>

#include <system/Trace.h>
#include <system/Exception.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ConfigurationFile.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ConfigurationFile::ConfigurationFile(
    const string& fileName,
    const string& altDirectory
) :
    m_fileName(fileName),
    m_altDirectory(altDirectory)
{
}

ConfigurationFile::~ConfigurationFile()
{
}

bool ConfigurationFile::FileExists() const
{
    string fullPath = GetFullPath();

    return !fullPath.empty();
}

void ConfigurationFile::ReadConfigurationFile ()
{
    string fullPath = GetFullPath();

    if (!fullPath.empty())
    {
        // This must be safe to call multiple times, so clear out any
        // existing information before rebuilding the parameter map.
        m_parameterMap.clear ();

        FILE *fHandle = fopen (fullPath.c_str(), "rt");
        if (fHandle == NULL)
        {
            TRACE_LEV(TRACE_WARNING, "Failed to open file", fullPath);
            RETURN_VOID();
        }
        else
        {
            TRACE("Config file opened", fullPath);
        }

        char textBuffer[TEXT_BUFFER_SIZE + 1];
        char lhs[TEXT_BUFFER_SIZE + 1], rhs[TEXT_BUFFER_SIZE + 1];

        for (u32 lineNumber = 1; !feof(fHandle); lineNumber++)
        {
            memset(lhs, '\0', sizeof (lhs));
            memset(rhs, '\0', sizeof (rhs));
            memset(textBuffer, '\0', sizeof (textBuffer));

            if (fgets (textBuffer, TEXT_BUFFER_SIZE, fHandle) == NULL)
            {
                // Intentionally printf as opposed to TRACE as we are
                // probably doing this _very_ early in program loading.  The
                // Tracer egnine might not be ready for us.
                if (!feof(fHandle))
                {
                    TRACE_PRINTF("Error Reading Line # %u of %s\n", lineNumber, m_fileName.c_str());
                }
            }
            else
            {
                // First off, so we have a comment character.
                char *commentChar = strstr (textBuffer, "#");
                if (commentChar == NULL)
                {
                    // No: split string into two parts, variable name and value,
                    // then get parameter filled out.
                    SplitString (textBuffer, "=", lhs, rhs);
                    InterpretParameter (lhs, rhs);
                }
                else
                {
                    char leftOfComment[TEXT_BUFFER_SIZE + 1];
                    memset (leftOfComment, '\0', sizeof (leftOfComment));

                    SplitString (textBuffer, "#", leftOfComment, rhs);
                    SplitString (leftOfComment, "=", lhs, rhs);
                    InterpretParameter (lhs, rhs);
                }
            }
        }

        fclose (fHandle);
    }
}

void ConfigurationFile::SplitString (const char *src, const char *splitStr, char *lhs, char *rhs)
{
    ENTER();

    const char *theSplit = strstr (src, splitStr);
    if (theSplit != NULL)
    {
        // Need cast because stoopid compiler can't figure out size_t is a u32...
        u32 strLength = (u32) strlen (src);
        bool leftHandSide = true;
        for (u32 i=0,lhsCounter=0,rhsCounter=0;i<strLength;i++)
        {
            if (&(src[i]) == theSplit)
            {
                leftHandSide = false;
                continue;
            }//end if

            if (leftHandSide)
                lhs[lhsCounter++] = src[i];
            else
                rhs[rhsCounter++] = src[i];
            //end if
        }//end for
    }//end if

    EXIT();
}

void ConfigurationFile::ReverseSplitString (const char *src, char splitChar, char *lhs, char *rhs)
{
    ENTER();

    const char *theSplit = strrchr (src, splitChar);
    if (theSplit != NULL)
    {
        // Need cast because stoopid compiler can't figure out size_t is a u32...
        u32 strLength = (u32) strlen (src);
        bool leftHandSide = true;
        for (u32 i=0,lhsCounter=0,rhsCounter=0;i<strLength;i++)
        {
            if (&src[i] == theSplit)
            {
                leftHandSide = false;
                continue;
            }//end if

            if (leftHandSide)
                lhs[lhsCounter++] = src[i];
            else
                rhs[rhsCounter++] = src[i];
            //end if
        }//end for
    }//end if

    EXIT();
}

void ConfigurationFile::TidyString (char *src)
{
    ENTER();

    // Really a combined TrimLeading plus TrimTrailing.
    char tempCopy[TEXT_BUFFER_SIZE];
    char *srcPtr = src;
    memset (tempCopy, '\0', sizeof (tempCopy));

    u32 strLength = (u32) strlen (srcPtr);
    u32 realStringStart = 0;

    if(strLength == 0)
    {
        RETURN_VOID();
    }

    bool foundStart = false;
    while (!foundStart)
    {
        switch (srcPtr[realStringStart])
        {
        case ' ':
        case '\r':
        case '\n':
        case '\t':
            {
                // Intentionally do nothing: we are removing these
                // extraneous characters from the input string.
                realStringStart++;
            }
            break;

        default:
            {
                foundStart = true;
            }
        }//end switch
    }//end while

    bool foundEnd = false;
    u32 realStringEnd = strLength - 1;
    while (!foundEnd && realStringEnd > realStringStart)
    {
        switch (srcPtr[realStringEnd])
        {
        case ' ':
        case '\r':
        case '\n':
        case '\t':
            {
                // Intentionally do nothing: we are removing these
                // extraneous characters from the input string.
                realStringEnd--;
            }
            break;

        default:
            {
                foundEnd = true;
            }
        }
    }
    if((realStringStart <= realStringEnd) && ((realStringEnd - realStringStart + 1) <= (sizeof(tempCopy) - 1)))
    {
        strncpysafe (tempCopy, src + realStringStart, sizeof(tempCopy));
        tempCopy[realStringEnd - realStringStart + 1] = '\0';
        strncpy (src, tempCopy, TEXT_BUFFER_SIZE);
    }
    else
    {
        *src = '\0';
    }

    EXIT();
}


std::vector<std::string> ConfigurationFile::GetParameters() const
{
    std::vector<std::string> resultVector;

    // copy keys
    for (ParameterMap::const_iterator it=m_parameterMap.begin() ; it != m_parameterMap.end(); ++it )
    {
      resultVector.push_back(it->first);
    }

    RETURN(resultVector);
}


const char *ConfigurationFile::GetStringParameter (const char *paramName, const char *paramDefault) const
{
    ENTER ();

    ParameterMap::const_iterator foundParam = m_parameterMap.find (paramName);

    if (foundParam != m_parameterMap.end ())
    {
        RETURN (foundParam->second.c_str ());
    }

    RETURN (paramDefault);
}

u32 ConfigurationFile::GetU32Parameter (const char *paramName, u32 paramDefault) const
{
    ENTER ();

    const char *foundParam = GetStringParameter (paramName);

    if(strcmp(foundParam, ""))
    {
        RETURN (atoi (foundParam));
    }
    RETURN (paramDefault);
}

s32 ConfigurationFile::GetS32Parameter (const char *paramName, s32 paramDefault) const
{
    ENTER ();

    const char *foundParam = GetStringParameter (paramName);

    if(strcmp(foundParam, ""))
    {
            RETURN (atoi (foundParam));
    }
    RETURN(paramDefault);
}

string ConfigurationFile::ToString () const
{
    ENTER();

    ostringstream stream;

    if (m_parameterMap.size () > 0)
    {
        ParameterMap::const_iterator paramIter = m_parameterMap.begin ();
        while (paramIter != m_parameterMap.end ())
        {
            stream << "Param: " << paramIter->first << " Value: " << paramIter->second << endl;
            paramIter++;
        }
    }
    else
    {
        stream << "No Paramater Information Present" << endl;
    }

    RETURN(stream.str());
}

string ConfigurationFile::GetFullPath() const
{
    string path;

    if (m_fileName.length() > 0)
    {
        struct stat sb;

        if (m_altDirectory.length() > 0)
        {
            string altPath = m_altDirectory + m_fileName;

            if ((stat(altPath.c_str(), &sb) == 0) && S_ISREG(sb.st_mode))
            {
                path = altPath;
            }
        }
	else if ((stat(m_fileName.c_str(), &sb) == 0) && S_ISREG(sb.st_mode))
        {
            path = m_fileName;
        }
    }

    return path;
}

void ConfigurationFile::InterpretParameter (char *paramName, char *paramValue)
{
    ENTER();

    TidyString (paramName);
    TidyString (paramValue);

    if (strlen (paramName) > 0)
    {
        //TRACE_PRINTF ("Name Is %s Value Is %s\n", paramName, paramValue);

        // Just store the recorded value for now: we leave it to the actual
        // applications to request the values.  Again, a small efficiency
        // saving as different apps will want different parameters and I'm
        // not coding multiple config files...
        m_parameterMap.insert (std::make_pair (paramName, paramValue));
    }

    EXIT();
}

u8 ConfigurationFile::HexCharToU8 (char inChar)
{
    if ((inChar >= 48) && (inChar <= 57))
    {
        return inChar - 48;
    }
    else if ((inChar >= 65) && (inChar <= 70))
    {
        return inChar - 55;
    }
    else if ((inChar >= 97) && (inChar <= 102))
    {
        return inChar - 87;
    }
    else
    {
        return 0;
    }
}

char ConfigurationFile::U8ToHexChar (u8 inByte)
{
    return inByte < 10 ? (char) inByte + 48 : (char) inByte + 55;
}
