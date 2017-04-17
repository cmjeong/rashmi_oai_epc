///////////////////////////////////////////////////////////////////////////////
//
// Application.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <system/ConfigurationFile.h>
#include <system/Utilities.h>
#include <string.h>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Application.h"

#define MAX_DIR_LEN 50

using namespace std;

void * operator new (size_t size)
{
   void * p = malloc(size);

   RSYS_ASSERT_PRINTF( p || (size == 0),"Out of memory. new(%zu)", size);

   return p;
}

void operator delete (void *p)
{
   free(p);
}

namespace threeway
{

   ///////////////////////////////////////////////////////////////////////////////
   // Static Data
   ///////////////////////////////////////////////////////////////////////////////

   // Redefine threeway::appVer as weak
   // This is weak such that programs linking against the system library don't
   // have to define it.  In such a case, no version information will be available
   // from Application::GetApplicationInfo().
   // Note: not all users of this library use the Application class.
   extern const ApplicationVersion __attribute__((__weak__)) appVer;

   ///////////////////////////////////////////////////////////////////////////////
   // Classes
   ///////////////////////////////////////////////////////////////////////////////

   const char * Application::GetName() const
   {
      return m_appName.c_str();
   }

   std::string Application::GetApplicationInfo() const
   {
      ostringstream stream;

      stream << GetName();

      // Add product and hardware defines
      stream << ", " << PRODUCT_STR;
#if defined(HARDWARE_hbs2_4)
      stream << ", hbs2_4";
#elif defined(HARDWARE_hbs2_3_5)
      stream << ", hbs2_v3_5";
#endif

      // Check if the application version is defined; it's a weak symbol so
      //  might not have been linked and will have a NULL address.
      if(&appVer != NULL)
      {
         stream << ", ver " << appVer.version << "," << appVer.buildCount
            << " built at " << appVer.buildTime << " " << appVer.buildDate;
      }
      else
      {
         // DeclareAppVersionStamp missing from application
         stream << " ver unknown, built at unknown unknown";
      }

      return stream.str();
   }

   void Application::ParseCmdLineArgs(int argc, char ** argv)
   {
      m_exePath = argv[0];

      if(argc >= 2)
      {
         setConfigFilePath(argv[1]);
      }
      else
      {
         setConfigFilePath("/mnt/tmp/");
      }

      // command line args may specify (1) key-value pairs or (2) flags (standalone keys)
      // a key is formed from a head and tail where...
      // ...the head is one or more hyphens
      // ...and tail is optional

      for (int idx = 1; idx < argc; idx++)
      {
         if (0 == (strncmp(argv[idx], "-", 1)))
         {
            if (    (idx == (argc - 1))
                  || (0 == strncmp(argv[idx + 1], "-", 1))
               )
            {
               /* no value or key follows => flag */
               m_cmdLineArgs[argv[idx]] = "";
            }
            else
            {
               /* non-key follows => pair */
               m_cmdLineArgs[argv[idx]] = argv[idx + 1];
               idx++; /* non-key consumed */
            }
         }
      }
   }

   const char * Application::GetCmdLineArgument(const char * argument) const
   {
      CmdLineArgs::const_iterator iter = m_cmdLineArgs.find(argument);

      if (iter != m_cmdLineArgs.end())
      {
         return iter->second.c_str();
      }

      return NULL;
   }

   u32 Application::GetNumCmdLineArgs() const
   {
      return m_cmdLineArgs.size();
   }

   int Application::Run(int argc, char * argv[])
   {
      ENTER();

      int result = 1; // Default to error condition

      try
      {
         ParseCmdLineArgs(argc, argv);

         if (GetCmdLineArgument("--help"))
         {
            TRACE_PRINTF("%s", ToString().c_str());
            result = 0;
         }
         else
         {
            m_systemConfig.ReadConfigurationFile();

            StartTrace();

            result = Main(argc, argv);
         }
      }
      catch  (Exception& e)
      {
         TRACE_PRINTF("Exception caught: %s : %s \n",GetName(),e.what());
      }  
      catch (...)
      {
         TRACE_PRINTF("Top level exception caught. \n");
      }

      RETURN(result);
   }

   const char * Application::GetNvLogDirectory() const
   {
      return "./";
   }

   const char * Application::GetNvTmpDirectory() const
   {
      return "./";
   }

   string Application::ToString() const
   {
      ostringstream stream;

      stream << endl << GetName() << endl << endl;

      stream << "Usage:" << endl
         << "  --tracelev none | [verbose],[call-stack]" << endl
         << "  --trace-dir <directory>" << endl
         << endl;

      return stream.str();
   }
 
   void Application::StartTrace() const
   {
      Trace::GetInstance().SetApplicationInfo(GetApplicationInfo());

      const char * traceLevelArg = GetCmdLineArgument("--tracelev");

      if (traceLevelArg)
      {
         string traceLevelStr(traceLevelArg);

         if (traceLevelStr.compare("none") == 0)
         {
            Trace::GetInstance().SetTraceLevelsMask(0);
         }
         else
         {
            u32 traceLevelMask = TRACE_FATAL | TRACE_CRITICAL | TRACE_WARNING | TRACE_INFO;

            if (traceLevelStr.find("verbose") != string::npos)
            {
               traceLevelMask |= TRACE_VERBOSE;
            }

            if (traceLevelStr.find("call-stack") != string::npos)
            {
               traceLevelMask |= TRACE_CALL_STACK;
            }

            Trace::GetInstance().SetTraceLevelsMask(traceLevelMask);
         }
      }

      const char * remoteLoggingAddress = m_systemConfig.GetStringParameter("UDP_Logging", "OFF");

      if (strcasecmp(remoteLoggingAddress, "OFF") != 0)
      {
         char fileEntry[64];
         snprintf (fileEntry, 64, "%s_LoggingPort", m_appName.c_str ());

         u32 destPort = m_systemConfig.GetU32Parameter (fileEntry);
         if (destPort != UINT_MAX)
         {
            TRACE_PRINTF("UDP Tracing Sent To %s:%u", remoteLoggingAddress, destPort);
            Trace::GetInstance().EnableUDPLogging (destPort, inet_addr (remoteLoggingAddress));
         }
      }

      char * traceDir = (char * )GetCmdLineArgument("--trace-dir");

      if (!traceDir)
      {
#if defined(PRODUCT_test)       
         traceDir = "/dbx/trace";
#else        
         string val;

         val = getConfigParam("OAM_LOGGING_DIR", "");

         traceDir = (char *)val.c_str();
#endif        
      }

      if(traceDir != NULL)
      {
         if (strlen(traceDir))
         {
            Trace::GetInstance().SetFileLoggingParams(traceDir, GetName());

            if (strcasecmp(m_systemConfig.GetStringParameter ("GenerateTraceFiles", "Yes"), "Yes") == 0)
            {
               Trace::GetInstance().EnableFileLogging(m_systemConfig.GetU32Parameter("TraceFileLimit", 256 * 1024));
            }
         }

         TRACE_PRINTF("App: %s", GetApplicationInfo().c_str());
      }
   }
}
