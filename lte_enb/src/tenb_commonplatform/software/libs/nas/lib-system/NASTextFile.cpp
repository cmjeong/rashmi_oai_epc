///////////////////////////////////////////////////////////////////////////////
//
// NASTextFile.cpp
//
// Generic text configuration file reader.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include <system/StringUtils.h>

#include <NASTrace.h>
#include <lib-system/NASException.h>
#include <lib-system/NASFileName.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTextFile.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// The maximum length of a line (in characters) in the config file.
// Need an extra couple because we have 512 visible characters, plus the
// carriage return / line feed pair.  Plus an additional terminating
// NULL character.
static const u32 TEXT_BUFFER_SIZE = 515;

///////////////////////////////////////////////////////////////////////////////
// Class: NASTextFile
// Desc : Read the system configuration file, and provide accessors so the
//        various application settings can be retrieved.
///////////////////////////////////////////////////////////////////////////////
NASTextFile::NASTextFile (const char *fileDir, const char *fileName)
{
    memset (m_fileName, '\0', MAX_PATH);
    if (fileName != NULL)
        memcpy (m_fileName, fileName, MAX_PATH);

    memset (m_fileDir, '\0', MAX_PATH);
    if (fileDir != NULL)
        memcpy (m_fileDir, fileDir, MAX_PATH);
}

NASTextFile::~NASTextFile ()
{
}

void NASTextFile::SetDirectoryName (const char *fileDir)
{
    strncpysafe (m_fileDir, fileDir, MAX_PATH);
}

void NASTextFile::ReadNASTextFile ()
{
    //TRACE_PRINTF("NASTextFile::ReadNASTextFile(): %s%s", m_fileDir, m_fileName);

    // This must be safe to call multiple times, so clear out any
    // existing information before rebuilding the parameter map.
    m_parameterMap.clear ();

    // And on to file reading....
    // Little note here: if this is _very_ early in program startup,
    // this will be reading the system configuration file so we
    // have no working directory.  In this case, default to the current
    // working directory and hope for the best.

    if(strlen(m_fileName) <= 0)
    {
        throw NASException (
         __FILE__,
         __LINE__,
         "Failed To Open File - m_fileName is empty");
    }

    NASFileName textFile (
        "%s%s",
        m_fileDir,
        m_fileName);

    const char *fileName = textFile.GetFileName ();

    if(strlen(fileName) <= 0)
    {
        throw NASException (
         __FILE__,
         __LINE__,
         "Failed To Open File - file name is empty");
    }

    FILE *fHandle = fopen (fileName, "rt");
    if (fHandle == NULL)
    {
        TRACE_PRINTF ("Failed To Open System Configuration File -\n [%s]\n", fileName);
        throw NASException (
         __FILE__,
         __LINE__,
         "Failed To Open File %s", fileName);
    }//end if

    char textBuffer[TEXT_BUFFER_SIZE + 1];
    char lhs[TEXT_BUFFER_SIZE + 1], rhs[TEXT_BUFFER_SIZE + 1];
    u32 lineNumber = 1;
    while (!feof (fHandle))
    {
        memset (lhs, '\0', sizeof (lhs));
        memset (rhs, '\0', sizeof (rhs));
        memset (textBuffer, '\0', sizeof (textBuffer));

        if (fgets (textBuffer, TEXT_BUFFER_SIZE, fHandle) == NULL)
        {
            // Intentionally printf as opposed to NAS_TRACE as we are
            // probably doing this _very_ early in program loading.  The
            // Tracer egnine might not be ready for us.
            if (!feof (fHandle))
                TRACE_PRINTF ("Error Reading Line # %" PRIu32 " of %s\n", lineNumber, fileName);
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
            }//end if
        }//end if

        lineNumber++;
    }//end while

    fclose (fHandle);
}

void NASTextFile::SplitString (const char *src, const char *splitStr, char *lhs, char *rhs)
{
    memset (lhs, '\0', sizeof (lhs));
    memset (rhs, '\0', sizeof (rhs));

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
}

void NASTextFile::InterpretParameter (char *paramName, char *paramValue)
{
    TidyString (paramName);
    TidyString (paramValue);

    if (strlen (paramName) > 0)
    {
        //TRACE_PRINTF("  %s = %s", paramName, paramValue);

        // Just store the recorded value for now: we leave it to the actual
        // applications to request the values.  Again, a small efficiency
        // saving as different apps will want different parameters and I'm
        // not coding multiple config files...
        m_parameterMap.insert (std::make_pair (paramName, paramValue));
    }//end if
}

void NASTextFile::TidyString (char *src)
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
        }//end switch
    }//end while

    if((realStringStart <= realStringEnd) && ((realStringEnd - realStringStart + 1) <= sizeof(tempCopy)))
    {
        strncpysafe (tempCopy, src + realStringStart, sizeof(tempCopy));
        tempCopy[realStringEnd - realStringStart + 1] = '\0';
        strcpy (src, tempCopy);
    }
    else
    {
        *src = '\0';
    }

    EXIT();
}

const char *NASTextFile::GetStringParameter (const char *paramName, const char *paramDefault) const
{
    NAS_ENTER ();
    NAS_TRACE ("Looking For Parameter", paramName);

    if(m_parameterMap.size() > 0)
    {
        ParameterMap::const_iterator foundParam = m_parameterMap.find (paramName);
        if (foundParam != m_parameterMap.end ())
        {
            NAS_TRACE ("Found It: Returning", foundParam->second.c_str ());
            NAS_RETURN (foundParam->second.c_str ());
        }//end if
    }
    else
    {
        NAS_TRACE ("Empty parameter map for", m_fileName);
    }

    NAS_TRACE("Not Found Returning Default", paramDefault);
    NAS_RETURN (paramDefault);
}

u32 NASTextFile::GetU32Parameter (const char *paramName, u32 paramDefault) const
{
    NAS_ENTER ();
    const char *foundParam = GetStringParameter (paramName, NULL);
    NAS_RETURN (foundParam == NULL ? paramDefault : atoi (foundParam));
}

void NASTextFile::ShowParameters () const
{
    if (m_parameterMap.size () > 0)
    {
        ParameterMap::const_iterator paramIter = m_parameterMap.begin ();
        while (paramIter != m_parameterMap.end ())
        {
            TRACE_PRINTF (
                "Param: %s Value: %s\n",
                paramIter->first.c_str (),
                paramIter->second.c_str ());
            paramIter++;
        }//end while
    }
    else
    {
        NAS_MSG ("No Paramater Information Present");
    }//end if
}

u8 HexCharToU8 (char inChar)
{
    if ((inChar >= 48) && (inChar <= 57))
        return inChar - 48;
    else if ((inChar >= 65) && (inChar <= 70))
        return inChar - 55;
    else if ((inChar >= 97) && (inChar <= 102))
        return inChar - 87;
    else
        return 0;
    //end if
}

char U8ToHexChar (u8 inByte)
{
    return inByte < 10 ? (char) inByte + 48 : (char) inByte + 55;
}

