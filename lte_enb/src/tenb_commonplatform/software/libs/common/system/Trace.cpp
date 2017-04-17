///////////////////////////////////////////////////////////////////////////////
//
// Trace.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifndef BUILD_bfin_uclinux_2008
#include <execinfo.h>
#endif
#include <pthread.h>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>

#include <system/TimeWrap.h>
#include <system/StringUtils.h>
#include <system/Exception.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Trace.h"
#include "Exception.h"
#include "ConfigurationFile.h"
#include "Utilities.h"

using namespace std;
using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Global Data
///////////////////////////////////////////////////////////////////////////////

u32 g_Trace_enabledLevels = TRACE_INFO | TRACE_WARNING | TRACE_CRITICAL | TRACE_FATAL | TRACE_EXCEPTIONS;
u32 g_Trace_enabledCategories = 0;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

/**
 * Call stack indentation for use when call stack tracing is turned on.
 */
static u32 s_callStackIndent = 0;

static pthread_mutex_t s_logfileWriteMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t s_logUDPSendMutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * User defined categories and their associated strings.
 */
static std::map<u32, std::string> s_categoryStrings;

/**
 * Allow disabling of abort() after assert for unit tests ONLY!!!
 * Exception will be thrown instead.
 */
static bool s_Trace_assertAbortDisabled = false;


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<Trace> Trace::s_instance;

#ifdef BUILD_i686_linux
const char * Trace::m_assertionFailureLogFilename = "./assertion_failures.log";
#else
const char * Trace::m_assertionFailureLogFilename = "/mnt/log/assertion_failures.log";
#endif

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

const char * Trace::TraceLevelToStr(u32 level)
{
    switch(level)
    {
    case TRACE_VERBOSE:     return "";                  break;
    case TRACE_INFO:        return "";                  break;
    case TRACE_WARNING:     return "!!WARNING!! ";      break;
    case TRACE_CRITICAL:    return "!!!CRITICAL!!! ";   break;
    case TRACE_FATAL:       return "!!!!FATAL!!!! ";    break;
    case TRACE_CALL_STACK:  return "";                  break;
    case TRACE_EXCEPTIONS:  return "!!EXCEPTION!! ";    break;
    }
    return "";
}

const char * Trace::TraceCatToStr(u32 category)
{
    map<u32, string>::const_iterator iter = s_categoryStrings.find(category);
    if(iter != s_categoryStrings.end())
    {
        // Returning a pointer to the embedded c_str is efficient and safe to do so long as we don't delete categories.
        // Even then we'd be very unlucky to hit a problem and would only hit it during development/debug :-)
        return iter->second.c_str();
    }
    return "[cat?]";
}

Trace& Trace::GetInstance()
{
    if (s_instance == NULL)
    {
        s_instance.reset(new Trace());
    }

    return (*s_instance);
}

Trace::Trace() :
    m_logToStdout(false),
    m_loggingToFile (false),
    m_loggingToUdp (false),
    m_appendloggingToExistingFile (false),
    m_outputFile (NULL),
    m_traceFileLimit (262144),      // Default, can be changed in EnableFileLogging call...
    m_loggingSocket (INVALID_SOCKET),
    m_destinationAddress (0),
    m_destinationPort (0),
    m_swWarningInterface(NULL),
    m_logSoftwareWarningLevel(0xffffffff)
{
    m_traceDir[0] = '\0';
    m_outputFileNamePrefix[0] = '\0';
    m_outputFileName[0] = '\0';

    strcpy(m_traceDir, ".\\");
    m_numClosedFiles = 0;
    m_fileToDelete = 0;
}

Trace::~Trace()
{
    DisableFileLogging ();
}

void Trace::SetApplicationInfo(const std::string& appInfo)
{
    m_appInfo = appInfo;
}

void Trace::SetFileLoggingParams(const char *traceDir, const char *outputFileNamePrefix)
{
    if (traceDir)
    {
        size_t  traceDirLen  = strlen(traceDir);
        size_t  separatorLen = ((traceDir[traceDirLen - 1] != '/') ? 1 : 0);

        if ((traceDirLen + separatorLen) < sizeof(m_traceDir))
        {
            strncpysafe(m_traceDir, traceDir, sizeof(m_traceDir));

            if (separatorLen)
            {
                m_traceDir[traceDirLen]     = '/';
                m_traceDir[traceDirLen + 1] = '\0';
            }
        }
    }

    if (outputFileNamePrefix)
    {
        strncpysafe(m_outputFileNamePrefix, outputFileNamePrefix, sizeof(m_outputFileNamePrefix));
    }
}


int Trace::GetLogFilesToUpload(string fileNameArray[])
{
   pthread_mutex_lock(&s_logfileWriteMutex);
   int fileIndx =0;
   for(fileIndx =0; fileIndx < m_numClosedFiles;fileIndx++)
   {
      fileNameArray[fileIndx] = m_closedFiles[fileIndx];
   }
   m_numClosedFiles = 0;
   m_fileToDelete = 0;
   fileNameArray[fileIndx] = FileName;
   StartNewTraceFile();
   pthread_mutex_unlock(&s_logfileWriteMutex);
   return (fileIndx+1);
}

void Trace::SetTraceLevelsMask(u32 levelsMask)
{
    g_Trace_enabledLevels = levelsMask;

    // Call trace function directly to show current levels so as to
    // ensure it comes out i.e. no trace level filtering!
    Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", ToString().c_str());
}

void Trace::SetTraceLevelOn(u32 levelsMask)
{
    g_Trace_enabledLevels |= levelsMask;

    // Call trace function directly to show current levels so as to
    // ensure it comes out i.e. no trace level filtering!
    Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", ToString().c_str());
}

void Trace::SetTraceLevelOff(u32 levelsMask)
{
    g_Trace_enabledLevels &= ~levelsMask;

    // Call trace function directly to show current levels so as to
    // ensure it comes out i.e. no trace level filtering!
    Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", ToString().c_str());
}

void Trace::RegisterTraceCategory(u32 categoryMask, const char * categoryString)
{
    s_categoryStrings[categoryMask] = categoryString;
}

void Trace::SetTraceCategoriesMask(u32 categoriesMask)
{
    g_Trace_enabledCategories = categoriesMask;

    // Call trace function directly to show current levels so as to
    // ensure it comes out i.e. no trace level filtering!
    Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", ToString().c_str());
}

void Trace::SetTraceCategoriesOn(u32 categoriesMask)
{
    g_Trace_enabledCategories |= categoriesMask;

    // Call trace function directly to show current levels so as to
    // ensure it comes out i.e. no trace level filtering!
    Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", ToString().c_str());
}

void Trace::SetTraceCategoriesOff(u32 categoriesMask)
{
    g_Trace_enabledCategories &= ~categoriesMask;

    // Call trace function directly to show current levels so as to
    // ensure it comes out i.e. no trace level filtering!
    Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", ToString().c_str());
}

u32 Trace::GetTraceCategoryFromString(const char * categoryString) const
{
    map<u32, string>::const_iterator iter = s_categoryStrings.begin();

    while(iter != s_categoryStrings.end())
    {
        if(strcasecmp(iter->second.c_str(), categoryString) == 0)
        {
            return iter->first;
        }
        ++iter;
    }

    return 0;
}

void Trace::EnableFileLogging (u32 traceFileLimit)
{
    // If we are already logging, just change the file size limit
    if (traceFileLimit > 0)
    {
        m_traceFileLimit = traceFileLimit;
    }

    if (!m_loggingToFile)
    {
        TurnFileLoggingOn();
    }
}

void Trace::DisableFileLogging(const char * reason)
{
    if (m_loggingToFile)
    {
        TurnFileLoggingOff(reason);
    }
}

bool Trace::LoggingToFile() const
{
    return m_loggingToFile;
}

const char * Trace::GetTraceFilename() const
{
    if (LoggingToFile())
    {
        return m_outputFileName;
    }

    return "<not logging to file>";
}

void Trace::EnableUDPLogging (u16 destinationPort, u32 destinationAddress)
{
    if(m_loggingToUdp)
    {
        TurnUdpLoggingOff();
    }

    TurnUdpLoggingOn (destinationPort, destinationAddress);
}

void Trace::DisableUDPLogging ()
{
    if(m_loggingToUdp)
    {
        TurnUdpLoggingOff ();
    }
}

bool Trace::LoggingToUdp () const
{
    return m_loggingToUdp;
}

u32 Trace::GetUdpLoggingDestAddr() const
{
    return m_destinationAddress;
}

u16 Trace::GetUdpLoggingDestPort() const
{
    return m_destinationPort;
}

string Trace::ToString() const
{
    ostringstream str;

    str << "Enabled Levels: "
        << (g_Trace_enabledLevels & TRACE_VERBOSE ? "VERBOSE" : "")
        << (g_Trace_enabledLevels & TRACE_INFO ? " INFO" : "")
        << (g_Trace_enabledLevels & TRACE_WARNING ? " WARNING" : "")
        << (g_Trace_enabledLevels & TRACE_CRITICAL ? " CRITICAL" : "")
        << (g_Trace_enabledLevels & TRACE_CRITICAL ? " FATAL" : "")
        << (g_Trace_enabledLevels & TRACE_CALL_STACK ? " CALL_STACK" : "")
        << (g_Trace_enabledLevels & TRACE_EXCEPTIONS ? " EXCEPTIONS" : "")
        << "\n";

    str << "Available Levels: VERBOSE INFO WARNING CRITICAL FATAL CALL_STACK EXCEPTIONS\n";

    str << "Enabled Categories: ";
    if(g_Trace_enabledCategories == 0)
    {
        str << "[none]";
    }
    else
    {
        for(u32 cat = 1; cat != 0; cat = cat << 1)
        {
            if(g_Trace_enabledCategories & cat)
            {
                map<u32, string>::const_iterator iter = s_categoryStrings.find(cat);
                if(iter != s_categoryStrings.end())
                {
                    str << iter->second << " ";
                }
                else
                {
                    str << cat << " ";
                }
            }
        }
    }
    str << "\n";

    string registeredTraceCategoriesString = GetRegisteredTraceCategoriesString();
    if(registeredTraceCategoriesString.empty())
    {
        str << "Available Categories: [none]";
    }
    else
    {
        str << "Available Categories: " << registeredTraceCategoriesString;
    }
    return str.str();
}

string Trace::GetRegisteredTraceCategoriesString() const
{
    ostringstream str;

    for(u32 cat = 1; cat != 0; cat = cat << 1)
    {
        map<u32, string>::const_iterator iter = s_categoryStrings.find(cat);
        if(iter != s_categoryStrings.end())
        {
            str << iter->second << " ";
        }
    }

    return str.str();
}

void Trace::LogToStderr(const char * traceMsg)
{
    fprintf(stderr, "%s", traceMsg);
}

void Trace::LogToFile(const char * traceMsg)
{
    if (m_loggingToFile)
    {
        pthread_mutex_lock(&s_logfileWriteMutex);
        if (m_outputFile)
        {
            fprintf(m_outputFile, "%s", traceMsg);
            fflush(m_outputFile);

            if ((u32)ftell(m_outputFile) > m_traceFileLimit)
            {
               if(m_numClosedFiles == MAXNUMCLOSEDFILES)
               {
                   string val;
                   val = getConfigParam("OAM_LOGGING_DIR", "");
                   ostringstream command;
                   command <<"cd "<<val <<" && rm -f "<< m_closedFiles[m_fileToDelete] ;
                   if(system(command.str().c_str()) != 0)
                   {
                      TRACE_PRINTF_LEV(TRACE_WARNING, "Failed To Delete Trace File %s",m_closedFiles[m_fileToDelete].c_str() );
                   }
                   m_closedFiles[m_fileToDelete] = std::string(FileName);
                   m_fileToDelete = (m_fileToDelete + 1) % MAXNUMCLOSEDFILES;
                }
               else
               {
                  m_closedFiles[m_numClosedFiles] = std::string(FileName);
                  m_numClosedFiles = m_numClosedFiles + 1;
               }
               StartNewTraceFile();
            }
        }
        pthread_mutex_unlock(&s_logfileWriteMutex);

        // Deliberately outside the mutex, to reduce blocking time.
        }
}


void Trace::LogToUdp (const char *traceMsg)
{
    if(m_loggingToUdp)
    {
        pthread_mutex_lock(&s_logUDPSendMutex);
        if(m_loggingSocket != INVALID_SOCKET)
        {
            struct sockaddr_in targetAddress;

            targetAddress.sin_family = PF_INET;
            targetAddress.sin_port = htons (m_destinationPort);
            targetAddress.sin_addr.s_addr = m_destinationAddress;

            s32 sendResult = ::sendto(
                m_loggingSocket,
                traceMsg,
                strlen (traceMsg),
                0,
                (struct sockaddr *) &targetAddress,
                sizeof (targetAddress));

            // Silent failure and abort.
            if (sendResult == SOCKET_ERROR)
            {
                DisableUDPLogging ();
            }//end if
        }//end if
        pthread_mutex_unlock(&s_logUDPSendMutex);
    }//end if
}

void Trace::LogWarnings ( u32 level, const char *traceMsg)
{

    if(level >= m_logSoftwareWarningLevel)
    {
        if(m_swWarningInterface)
        {
            m_swWarningInterface->SoftwareWarning(traceMsg);
        }
        else
        {
            fprintf( stderr, "!!%s",traceMsg);
        }
    }
}

void Trace::GetTimeStr(char * outputBuff, u32 outputBuffLen)
{
    struct timeval timeVal;
    struct timezone timeZone;

    gettimeofday (&timeVal, &timeZone);
    struct tm *tmVal = gmtime (&(timeVal.tv_sec));  // gmtime works in UTC.

    snprintf(outputBuff,
             outputBuffLen,
             "%02" PRIu32 ":%02" PRIu32 ":%02" PRIu32 ".%.06" PRIu32,
             tmVal->tm_hour,
             tmVal->tm_min,
             tmVal->tm_sec,
             (u32)(timeVal.tv_usec));
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, u32 numberValue)
{
    if (numberValue == 0xffffffff)
    {
        Trace_TracePrintf(category, level, "%s: UNDEFINED", message);
    }
    else
    {
        Trace_TracePrintf(category, level, "%s: %"PRIu32, message, numberValue);
    }
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, s32 numberValue)
{
    Trace_TracePrintf(category, level, "%s: %"PRId32, message, numberValue);
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, const char *strValue)
{
    Trace_TracePrintf(category, level, "%s: %s", message, strValue);
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, const string& str)
{
    Trace_TracePrintf(category, level, "%s: %s", message, str.c_str());
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, bool boolValue)
{
    Trace_TracePrintf(category, level, "%s: %s", message, (boolValue?"true":"false"));
}

void Trace::TraceFunc (u32 category, u32 level, const Exception &e)
{
    Trace_TracePrintf(category, level, "%s", e.what());
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, const u8 digitArray [], u16 digitCount)
{
    char numberBuff[32];

    // Preconditions.
    // Make sure we have room for the number of digits in our number string.  Includes allowing a null byte terminator.
    RSYS_ASSERT(digitCount < (sizeof(numberBuff) - 1));

    if (digitCount > 0)
    {
        memset (numberBuff, '\0', sizeof (numberBuff));

        for (u16 i = 0; i < digitCount; i++)
        {
            numberBuff[i] = (char) (digitArray[i] <= 9 ? digitArray[i] + 48 : digitArray[i] + 55);
        }

        Trace_TracePrintf(category, level, "%s: %s", message, numberBuff);
    }
    else
    {
        Trace_TracePrintf(category, level, "%s: Number Is EMPTY", message);
    }//end if
}

void Trace::TraceFunc (u32 category, u32 level, const char *message, const TimeWrap &timeValue)
{

    char dateBuff[128];
    timeValue.GetDateStr (dateBuff, sizeof(dateBuff));

    Trace_TracePrintf(category, level, "%s: %s", message, dateBuff);
}

void Trace::TraceFuncHex (u32 level, const char *message, u32 numberValue)
{
    if (numberValue == 0xffffffff)
    {
        Trace_TracePrintf(TRACE_CAT_NONE, level, "%s: UNDEFINED", message);
    }
    else
    {
        Trace_TracePrintf(TRACE_CAT_NONE, level, "%s: 0x%02" PRIX32, message, numberValue);
    }
}

void Trace::TraceFuncHex (u32 level, const char *message, const u8 *data, u32 dataLen)
{
    // This will inevitably get truncated by the addition of timestamp and other
    // trace prefix info if over a certain size, but it's safe and will say
    // " ... [truncated]" on the end.
    char hexStr[TRACE_STR_MAX_LENGTH];

    // Preconditions.
    // Check for enough space in our work buffer.
    RSYS_ASSERT_PRINTF(dataLen * 2 <= (sizeof(hexStr) - 1), "dataLen=%" PRIu32, dataLen);

    if(data == NULL)
    {
        Trace_TracePrintf(TRACE_CAT_NONE, level, "%s: NULL MSG", message);
    }
    else
    {
        u32 hexStrLen = 0;
        for(u32 i = 0; i < dataLen; i++)
        {
            hexStrLen += snprintf(&hexStr[hexStrLen], sizeof(hexStr) - hexStrLen,
                                  "%02X", (u8)data[i]);
        }

        Trace_TracePrintf(TRACE_CAT_NONE, level, "%s: %s", message, hexStr);
    }
}

void Trace::TraceMessageSequenceTag (const char *src, const char *dest, const char *pd, const char *mt, u32 pid, const char *p1, const char *p2, const char *desc)
{
    char timeStr[20];
    char traceMsg[TRACE_STR_MAX_LENGTH];

    // LAYER:PD:MT:DIRECTION:PROCID:PARAM1:PARAM2:DESC
    GetTimeStr(timeStr, sizeof(timeStr));
    snprintf (traceMsg, sizeof(traceMsg), "PP|%s|%s|%s|%s|%s|%" PRIu32 "|%s|%s|%s\n", timeStr,
        src, dest, pd, mt, pid, p1, p2, desc != NULL ? desc : "");

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void Trace::TraceMessageSequenceTag (const char * src, const char * dest, const char * pd,
                                      const char * mt, const char * pid, const char *p1,
                                      const char * p2, const char * desc)
{
    char timeStr[20];
    char traceMsg[TRACE_STR_MAX_LENGTH];

    GetTimeStr(timeStr, sizeof(timeStr));
    snprintf (traceMsg, sizeof(traceMsg), "PP|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", timeStr,
        src, dest, pd, mt, pid, p1, p2, desc != NULL ? desc : "");

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void Trace::TraceMessageSequenceTag (const char * src, const char * dest, const char * pd,
                                      const char * mt, const char * desc)
{
    char timeStr[20];
    char traceMsg[TRACE_STR_MAX_LENGTH];

    GetTimeStr(timeStr, sizeof(timeStr));
    snprintf (traceMsg, sizeof(traceMsg), "PP|%s|%s|%s|%s|%s||||%s\n", timeStr,
        src, dest, pd, mt, desc != NULL ? desc : "");

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void Trace::TurnFileLoggingOn ()
{
    if( m_appendloggingToExistingFile == false ||
        SelectExistingTraceFile() == false )
    {
        StartNewTraceFile();
    }

    m_loggingToFile = true;
}

void Trace::AppendTraceToExistingFile ()
{
    m_appendloggingToExistingFile = true;
}

void Trace::RemoveOldTraceFiles()
{
    if(m_outputFileNamePrefix[0] != '\0')
    {
        DIR *dir = opendir(m_traceDir);

        if(dir)
        {
            const u16 prefixLen = strlen(m_outputFileNamePrefix);
            char      newestName[MAX_PATH_LENGTH], curName[MAX_PATH_LENGTH];
            time_t    newestTime = 0;
            struct dirent *d;

            /* Iterate each file */
            while((d = readdir(dir)) != NULL)
            {
                /* Check if a log file for this application, and not the current file */
                if(strncmp(d->d_name, m_outputFileNamePrefix, prefixLen) == 0 &&
                   (!m_loggingToFile || !EndsWith(m_outputFileName, d->d_name)))
                {
                    /* Build full name */
                    snprintf(curName, sizeof(curName), "%s%s", m_traceDir, d->d_name);

                    int currentFile = open(curName, O_RDONLY);

                    if(currentFile >= 0)
                    {
                        struct stat sb;

                        if(fstat(currentFile, &sb) != 0)
                        {
                            /* fstat() failed, so delete */
                            close(currentFile);
                            remove(curName);
                        }
                        else if(sb.st_mtime < newestTime)
                        {
                            /* Older than current best */
                            close(currentFile);
                            remove(curName);
                        }
                        else
                        {
                            if(newestTime != 0)
                            {
                                remove(newestName);
                            }

                            /* Store the newest file time and name */
                            newestTime = sb.st_mtime;
                            strncpysafe(newestName, curName, sizeof(newestName));

                            close(currentFile);
                        }
                    }
                    else
                    {
                        remove(curName);
                    }
                }
            }

            closedir(dir);

            /* Roll newest file to .previous, having delete all others */
            if(newestTime != 0)
            {
                char prevFile[MAX_PATH_LENGTH];

                snprintf(prevFile, MAX_PATH_LENGTH, "%s/.previous.%s.txt", m_traceDir, m_outputFileNamePrefix);

                remove(prevFile);
                rename(newestName, prevFile);
            }
        }
    }
}

bool Trace::SelectExistingTraceFile()
{
   bool existingFileSelected = false;

   if(m_outputFileNamePrefix[0] != '\0')
   {
      DIR *dir = NULL;
      if ( m_traceDir[0] == '\0')
      {

         dir = opendir(".\\");
      }
      else
      {
         dir = opendir(m_traceDir);
      }

      if(dir)
      {
         const u16 prefixLen = strlen(m_outputFileNamePrefix);
         char      newestName[MAX_PATH_LENGTH], curName[MAX_PATH_LENGTH];
         time_t    newestTime = 0;
         struct dirent *d;

         /* Iterate each file */
         while((d = readdir(dir)) != NULL)
         {
            /* Check if a log file for this application, and not the current file */
            if(strncmp(d->d_name, m_outputFileNamePrefix, prefixLen) == 0 &&
                  (!m_loggingToFile || !EndsWith(m_outputFileName, d->d_name)))
            {
               /* Build full name */
               snprintf(curName, sizeof(curName),
                     "%s%s",
                     m_traceDir[0] == '\0' ? ".\\" : m_traceDir,
                     d->d_name);

               int currentFile = open(curName, O_RDONLY);

               if(currentFile >= 0)
               {
                  struct stat sb;

                  if(fstat(currentFile, &sb) != 0)
                  {
                     /* fstat() failed, so delete */
                     close(currentFile);
                     remove(curName);
                  }
                  else if(sb.st_mtime < newestTime)
                  {
                     /* Older than current best */
                     close(currentFile);
                     remove(curName);
                  }
                  else
                  {
                     if(newestTime != 0)
                     {
                        remove(newestName);
                     }

                     /* Store the newest file time and name */
                     newestTime = sb.st_mtime;
                     strncpysafe(newestName, curName, sizeof(newestName));

                     close(currentFile);
                  }
               }
               else
               {
                  remove(curName);
               }
            }
         }

         closedir(dir);

         /* Select newest file to append to */
         if(newestTime != 0)
         {
            strncpysafe(m_outputFileName, newestName, sizeof(m_outputFileName));
            m_outputFile = fopen (m_outputFileName, "at");

            if (m_outputFile)
            {
               TimeWrap now;

               fprintf (m_outputFile, "Log File (appending) at %s\n",
                     now.ToString().c_str());
               existingFileSelected = true;

            }
            else
            {
               TRACE_PRINTF_LEV(TRACE_CRITICAL, "Failed To Create DEBUG Trace File %s", m_outputFileName);
            }

         }
      }
   }

   return existingFileSelected;
}

void Trace::StartNewTraceFile()
{
    struct stat sd;

    if (m_outputFile)
    {
        fclose(m_outputFile);
        m_outputFile = NULL;
    }

    if (    (0 == stat(m_traceDir, &sd))
         && (S_ISDIR(sd.st_mode))
       )
    {
        TimeWrap now;

        // Put Date + Time into the output file name generated: this will tell
        // us when the application was started.
        string datetime = now.GetSafeFileName(); 
        snprintf(
            m_outputFileName, sizeof(m_outputFileName),
            "%s%s.%s.txt",
            m_traceDir,
            m_outputFileNamePrefix,
            datetime.c_str()
        );
        snprintf(FileName,sizeof(m_outputFileName),"%s.%s.txt",m_outputFileNamePrefix,datetime.c_str());

        m_outputFile = fopen(m_outputFileName, "wt");

        if (m_outputFile)
        {
            int flags, fd = fileno(m_outputFile);

            // Set the close on exec flag if possible.
            //  If the application calls exec(), this automatically closes this
            //  file to prevent file descriptor resource leaks.
            flags = fcntl(fd, F_GETFD);
            if(flags != -1)
            {
                fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
            }

            fprintf(m_outputFile, "Log File Started At %s\n", now.ToString().c_str());
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_WARNING, "Failed To Create DEBUG Trace File %s", m_outputFileName);
        }
    }
}

void Trace::TurnFileLoggingOff (const char *porQue)
{
    m_loggingToFile = false;

    pthread_mutex_lock(&s_logfileWriteMutex);
    if (m_outputFile)
    {
        if (porQue)
        {
            fprintf (m_outputFile, "Reason For Stop: %s\n", porQue);
        }

        TimeWrap now;

        fprintf (m_outputFile, "Log File Stopped At %s\n", now.ToString().c_str());

        fclose (m_outputFile);
        m_outputFile = NULL;
    }
    pthread_mutex_unlock(&s_logfileWriteMutex);
}

void Trace::TurnUdpLoggingOn (u16 destinationPort, u32 destinationAddress)
{
    ENTER ();

    TRACE ("Tracer Logging To Destination Address", destinationAddress);
    TRACE ("Destination Port", (u32) destinationPort);

    // If we are already logging, stop then start again.  This will let us change
    // the destination address for the log messages.
    if (m_loggingSocket != INVALID_SOCKET)
        DisableUDPLogging ();

    m_loggingSocket = socket (PF_INET, SOCK_DGRAM, 0);
    if (m_loggingSocket == INVALID_SOCKET)
        throw Exception (__FILE__, __LINE__, "Failed socket() For UDP Logging");

    m_destinationAddress = destinationAddress;
    m_destinationPort = destinationPort;

    // We _never_ expect to receive anything on this socket, so no further setup required.

    m_loggingToUdp = true;

    EXIT ();
}

void Trace::TurnUdpLoggingOff ()
{
    ENTER ();

    m_loggingToUdp = false;

    close (m_loggingSocket);
    m_loggingSocket = INVALID_SOCKET;

    EXIT ();
}

u32 Trace::GetCallStackIndent() const
{
    return s_callStackIndent;
}

std::string Trace_GetMemoryUsageStr()
{
    std::ostringstream outStream;
    char buf[30];
    snprintf(buf, 30, "/proc/%u/statm", (unsigned) getpid ());
    FILE* pf = fopen(buf, "r");
    if (pf)
    {
        unsigned size; //      total program size
        unsigned resident;//   resident set size
        unsigned share;//      shared pages
        unsigned text;//       text (code)
        unsigned lib;//        library
        unsigned data;//       data/stack
        unsigned dt;//         dirty pages (unused in Linux 2.6)

        int numAssigned = fscanf(pf, "%u %u %u %u %u %u %u",
            &size, &resident, &share, &text, &lib, &data, &dt);
        fclose(pf);

        if (numAssigned != 7)
        {
            outStream << "Error: only " << numAssigned << " values read successfully from " <<
                    "/proc/" << (unsigned) getpid () << "/statm" << std::endl;
        }
        else
        {
            //std::setprecision (4);
            outStream << "{ Process Memory Summary" << std::endl;
            outStream << "  MB Mem Used        : " << size / (1024.0) << std::endl;
            outStream << "  Total Program Size : " << size << std::endl;
            outStream << "  Resident Set Size  : " << resident << std::endl;
            outStream << "  Shared Pages       : " << share << std::endl;
            outStream << "  Text (Code)        : " << text << std::endl;
            outStream << "  Library            : " << lib << std::endl;
            outStream << "  Data / Stack       : " << data << std::endl;
            outStream << "  Dirty Pages        : " << dt << std::endl;
            outStream << "}" << std::endl;
        }
    }
    return outStream.str();
}

}

/** Check if some string \a s is postfixed with \a end.
 * \param[in] s   The string to search.
 * \param[in] end The sought extension.
 * \retval true if \a s ends with \a end.
 */
bool Trace::EndsWith(const char *s, const char *end)
{
    const u32 sLen = strlen(s);
    const u32 endLen = strlen(end);

    if(sLen >= endLen)
        return strcmp(&s[sLen - endLen], end) == 0;
    else
        return false;
}

void Trace_FuncHex (const char *strMsg, const u8 *data, u32 datalength)
{
    Trace::GetInstance().TraceFuncHex(TRACE_INFO, strMsg, data, datalength);
}

void Trace_TracePrintf(u32 category, u32 level, const char *format, ...)
{
    char timeStr[20];
    char traceMsg[TRACE_STR_MAX_LENGTH];
    int traceMsgLen = 0;
    int traceMsgLenMax = sizeof(traceMsg) - 25; // Give ourselves a bit of room to put [truncated] on the end if need be.

    Trace::GetInstance().GetTimeStr(timeStr, sizeof(timeStr));
    if(category != TRACE_CAT_NONE)
    {
        // We have a category so include it in the trace.
        traceMsgLen = snprintf(traceMsg, traceMsgLenMax, "%s%*c%s[%s] ",
                               timeStr, s_callStackIndent, ' ',
                               Trace::GetInstance().TraceLevelToStr(level),
                               Trace::GetInstance().TraceCatToStr(category)
                               );
    }
    else
    {
        traceMsgLen = snprintf(traceMsg, traceMsgLenMax, "%s%*c%s",
                               timeStr, s_callStackIndent, ' ',
                               Trace::GetInstance().TraceLevelToStr(level));
    }

    va_list args;
    va_start(args, format);
    traceMsgLen += vsnprintf(&traceMsg[traceMsgLen], traceMsgLenMax - traceMsgLen, format, args);
    va_end(args);

    if(traceMsgLen < traceMsgLenMax)
    {
        // Put a newline on it.
        traceMsgLen += snprintf(&traceMsg[traceMsgLen], traceMsgLenMax - traceMsgLen, "\n");
    }
    else
    {
        // Oops, we blew the buffer.  Stick a note on the end... the -1 takes us back so
        // we overwrite the trailing \0.
        traceMsgLen += snprintf(&traceMsg[traceMsgLenMax - 1], sizeof(traceMsg) - traceMsgLenMax, " ... [truncated]\n");
    }

    Trace::GetInstance().LogToFile(traceMsg);
    Trace::GetInstance().LogToUdp(traceMsg);
    Trace::GetInstance().LogWarnings(level, traceMsg);
    if(Trace::GetInstance().IsStdoutLogging())
    {
        // It's only unit tests that disable aborting on assert.
        // Unit tests also need trace output to console.
        fprintf(stdout, "%s", traceMsg);
    }
}

void Trace_TraceConsole(u32 category, u32 level, bool isNewLineRequired, const char *format, ...)
{
    char timeStr[20];
    char traceMsg[TRACE_STR_MAX_LENGTH];
    int traceMsgLen = 0;
    int traceMsgLenMax = sizeof(traceMsg) - 25; // Give ourselves a bit of room to put [truncated] on the end if need be.

    Trace::GetInstance().GetTimeStr(timeStr, sizeof(timeStr));

    va_list args;
    va_start(args, format);
    traceMsgLen += vsnprintf(&traceMsg[traceMsgLen], traceMsgLenMax - traceMsgLen, format, args);
    va_end(args);

    if(isNewLineRequired)
    {
       if(traceMsgLen < traceMsgLenMax)
       {
           // Put a newline on it.
           traceMsgLen += snprintf(&traceMsg[traceMsgLen], traceMsgLenMax - traceMsgLen, "\n");
       }
       else
       {
           // Oops, we blew the buffer.  Stick a note on the end... the -1 takes us back so
           // we overwrite the trailing \0.
           traceMsgLen += snprintf(&traceMsg[traceMsgLenMax - 1], sizeof(traceMsg) - traceMsgLenMax, " ... [truncated]\n");
       }
    }

        // It's only unit tests that disable aborting on assert.
        // Unit tests also need trace output to console.
        fprintf(stdout, "%s", traceMsg);    
}        

/** Printf equivalent for logging at the fatal level.
 */
int Trace_TracePrintfFatal(const char *format, ...)
{
    char timeStr[20];
    char traceMsg[TRACE_STR_MAX_LENGTH];
    int traceMsgLen = 0;
    int traceMsgLenMax = sizeof(traceMsg) - 25; // Give ourselves a bit of room to put [truncated] on the end if need be.

    Trace::GetInstance().GetTimeStr(timeStr, sizeof(timeStr));

    traceMsgLen = snprintf(traceMsg, traceMsgLenMax, "%s%*c%s",
                           timeStr, s_callStackIndent, ' ',
                           Trace::GetInstance().TraceLevelToStr(TRACE_FATAL));

    va_list args;
    va_start(args, format);
    traceMsgLen += vsnprintf(&traceMsg[traceMsgLen], traceMsgLenMax - traceMsgLen, format, args);
    va_end(args);

    if(traceMsgLen < traceMsgLenMax)
    {
        // Put a newline on it.
        traceMsgLen += snprintf(&traceMsg[traceMsgLen], traceMsgLenMax - traceMsgLen, "\n");
    }
    else
    {
        // Oops, we blew the buffer.  Stick a note on the end... the -1 takes us back so
        // we overwrite the trailing \0.
        traceMsgLen += snprintf(&traceMsg[traceMsgLenMax - 1], sizeof(traceMsg) - traceMsgLenMax, " ... [truncated]\n");
    }

    Trace::GetInstance().LogToFile(traceMsg);
    Trace::GetInstance().LogToUdp(traceMsg);

    return traceMsgLen;
}

void Trace_TraceMessageSequenceTag(const char *src, const char *dest, const char *pd, const char *mt,
                                   u32 pid, const char *p1, const char *p2, const char *desc)
{
    Trace::GetInstance().TraceMessageSequenceTag (src, dest, pd, mt, pid, p1, p2, desc);
}

void Trace_TraceMessageSequenceShortTag(const char *src, const char *dest, const char *pd,
                                                 const char *mt, const char *desc)
{
    Trace::GetInstance().TraceMessageSequenceTag (src, dest, pd, mt, desc);
}

// coverity[+kill]
void Trace_TraceAssert(const char * baseFile, const char * file, u32 line, const char * function,
                       const void *retAddrPtr, const int errNum,
                       const char *condition, const char *format, ...)
{
   const unsigned int returnAddress = (unsigned int)retAddrPtr;
   char timeStr[20], tname[20];
   char traceMsg[TRACE_STR_MAX_LENGTH];
   const pid_t pid = getpid();
   unsigned int codeStart, codeEnd;
   FILE *statFile;
   bool statFileParsedOk = false;

   // Check whether abort should be called - for unit test support ONLY!
   // Release/production code always calls abort().
   if(s_Trace_assertAbortDisabled)
   {
      // Throw an exception instead.  This means ASSERTs still
      // protect following code and will still be picked up
      // by static code analysis.
      fprintf(stdout, "Assert (abort disabled): %s#%"PRIu32" [%s]", file, line, condition);
      throw Exception(file, line, "%s", condition);
   }

   Trace::GetInstance().GetTimeStr(timeStr, sizeof(timeStr));

   // Store shortened version of assert message for retrieval and reporting on next reboot.
   // Do this first in case something goes wrong dumping the assert to trace/stderr.
   FILE * assertLogFile = fopen(Trace::GetInstance().GetAssertionFailureLogFilename(), "a");
   if(assertLogFile)
   {
      char logMsg[80 + 1];

      int logMsgLen = snprintf (logMsg, sizeof(logMsg),
            "%s %s:%" PRIu32 " (%s) %s(): ",
            timeStr, file, line, condition, function);

      // N.B: on use of (v)snprintf from the man page:

      // The functions snprintf() and vsnprintf() do not write  more  than  size
      // bytes  (including  the trailing '\0').  If the output was truncated due
      // to this limit then the return value is the number  of  characters  (not
      // including the trailing '\0') which would have been written to the final
      // string if enough space had been available.  Thus,  a  return  value  of
      // size  or  more  means  that  the output was truncated.

      // So, don't try to write to a negative length string if truncated above!
      if (logMsgLen < (int)(sizeof(logMsg)))
      {
         va_list args;
         va_start(args, format);
         logMsgLen += vsnprintf(&logMsg[logMsgLen], sizeof(logMsg) - logMsgLen, format, args);
         va_end(args);
      }

      char * p= &logMsg[0];

      while(*p)
      {
         if(*p == '\n') *p = '~';
         p++;
      }

      fprintf(assertLogFile, "%s", logMsg);
      fprintf(assertLogFile, "\n");
      fflush(assertLogFile);
      fsync(fileno(assertLogFile));
      fclose(assertLogFile);
      assertLogFile = NULL;
   }

   /*
    * Generate a trace string from all the info we have available.
    */

   // Get the (per-thread) process name or leave blank if not supported
   //  Note: PR_GET_NAME may return upto 16 bytes.  tname[] must therefore
   //        be at least this long + space for a terminating nul.
   memset(tname, 0, sizeof(tname));
#ifndef BUILD_bfin_uclinux_2008
   prctl(PR_GET_NAME, &tname, 0, 0, 0);
#endif

   // First the basics...
   int traceMsgLen = snprintf (traceMsg, sizeof(traceMsg),
         "================================\n"
         "!!!!!!!!!!!! ASSERT !!!!!!!!!!!!\n"
         "Time     : %s\n"
         "App      : %s\n"
         "Thread   : %s\n"
         "Location : %s:%" PRIu32 ":%s()\n"
         "Condition: %s\nMessage  : ",
         timeStr, Trace::GetInstance().GetApplicationInfo().c_str(), tname, file, line, function, condition);

   // And any message passed in.
   va_list args;
   va_start(args, format);
   traceMsgLen += vsnprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen, format, args);
   va_end(args);

   // Errno and PID.
   traceMsgLen += snprintf (&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen,
         "\nErrno    : %" PRId32 " (%s)\n"
         "PID      : %" PRId32 "\n",
         errNum, strerror(errNum), (int)pid);

   // Return address analysis.
   /* Open the stats file for this process */
   statFile = fopen("/proc/self/stat", "r");
   if(statFile != NULL)
   {
      /* Try to parse the filename and code area */
      char filename[32];
      if(fscanf(statFile, "%*d %31s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u "
               "%*u %*u %*u %*d %*d %*d %*d %*d %*u %*u %*d %*u %" SCNu32 " %" SCNu32,
               filename, &codeStart, &codeEnd) == 3)
      {
         // Ensure filename string properly terminated.
         filename[sizeof(filename)-1] = '\0';

         /* The filename is wrapped in parenthesis, remove these */
         if(strlen(filename) > 0)
         {
            memmove(filename, &filename[1], strlen(filename) - 1);
            filename[strlen(filename) - 1] = '\0';
         }

         /* Check if the return address falls within the bounds of the app */
         if(returnAddress >= codeStart && returnAddress <= codeEnd)
         {
            /* Print command and offset */

            traceMsgLen += snprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen,
                  "Return   : 0x%" PRIx32 " (%s + 0x%" PRIx32 ")\n",
                  returnAddress, filename, returnAddress - codeStart);
         }
         else
         {
            traceMsgLen += snprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen,
                  "Return   : 0x%" PRIx32 " (%s + \?\?\?\?: 0x%" PRIx32 "-0x%" PRIx32 ")\n",
                  returnAddress, filename, codeStart, codeEnd);
         }
         statFileParsedOk = true;
      }

      fclose(statFile);
      statFile = NULL;
   }

   /* If decoding failed for some reason, just print the whole address */
   if(!statFileParsedOk)
   {
      traceMsgLen += snprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen,
            "Return   : 0x%" PRIx32 " (\?\?\?\?)\n", returnAddress);
   }

#ifndef BUILD_bfin_uclinux_2008
   void   *list[32];    /* Max call depth */
   size_t  size, i;
   char  **strings;

   /* First get and decode the trace */
   size = backtrace(list, sizeof(list) / sizeof(list[0]));
   strings = backtrace_symbols(list, size);
   if(strings)
   {
      /* Now print it to the buffer*/
      traceMsgLen += snprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen, "Backtrace:\n");
      for(i = 0; i < size && traceMsgLen < (signed)sizeof(traceMsg); i++)
      {
         traceMsgLen += snprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen, " %2u: %s\n", i, strings[i]);
      }

      free(strings);
   }
#endif

   // Bung a clear footer on the message.
   traceMsgLen += snprintf(&traceMsg[traceMsgLen], sizeof(traceMsg) - traceMsgLen,
         "!!!!!!!!!!!! ASSERT !!!!!!!!!!!!\n"
         "================================\n");

   Trace::GetInstance().LogToStderr(traceMsg);
   Trace::GetInstance().LogToFile(traceMsg);
   Trace::GetInstance().LogToUdp(traceMsg);

   // And make it come out on the main console
   // TODO - we are logging to stderr above?  Should this be stdout or removed?
   fprintf(stderr, "%s", traceMsg);
   fflush(stderr);

   abort();
}

void Trace_SetAssertAbortDisabled(bool abortDisabled)
{
    s_Trace_assertAbortDisabled = abortDisabled;
}

void Trace_ShowMemoryUsage(u32 category, u32 level)
{
    Trace_TracePrintf(category, level, "%s", Trace_GetMemoryUsageStr().c_str());
}

void Trace_EnableStdoutLogging()
{
    Trace::GetInstance().EnableStdoutLogging();
}

void Trace_SetFileLoggingParams(const char *traceDir, const char *outputFileName)
{
    Trace::GetInstance().SetFileLoggingParams(traceDir, outputFileName);
}

void Trace_EnableFileLogging(u32 traceFileLimit)
{
    Trace::GetInstance().EnableFileLogging(traceFileLimit);
}

// END OF FILE
