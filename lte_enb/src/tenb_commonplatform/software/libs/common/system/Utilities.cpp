///////////////////////////////////////////////////////////////////////////////
//
// Utilities.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <fstream>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Utilities.h"

using namespace std;

std::string configFilePath = "";

///////////////////////////////////////////////////////////////////////////////
// Static Functions
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{
   u32 getRandomVal()
   {
      u32 byteCount = 4;
      u32 randValue;
      u8 data[byteCount];
      FILE *fp;

      fp = fopen("/dev/urandom", "r");
      if(NULL == fp)
      {
         randValue = rand();
         return randValue;
      }
      if(0 == fread(&data, 1, byteCount, fp))
      {
         TRACE_PRINTF(" random value generate fread call retrun 0 \n");
         randValue = rand();
         fclose(fp);
         return randValue;
      }
      fclose(fp);
      randValue = data[0];
      randValue = (randValue << 8) | data[1];
      randValue = (randValue << 8) | data[2];
      randValue = (randValue << 8) | data[3];
      return randValue;
   }

   string getConfigParamFromFile(const char *filename,
         const char *name,
         const char *defaultValue)
   {
      ifstream in(filename);
      string param, value;
      bool found = false;

      if (in.is_open())
      {
         while (!in.eof() && !found)
         {
            in >> param >> value;
            if (!param.compare(name))
               found = true;
         }
      }
      else
      {
          TRACE_PRINTF_LEV(TRACE_WARNING,"Failed to open %s. Using defaults.", filename);
      }

      return found? value: string(defaultValue);
   }

   string getConfigParam(const char *name, const char *defaultValue)
   {
      std::string path = configFilePath + "/configFile";
      return getConfigParamFromFile((char *)path.c_str(), name, defaultValue);
   }

   void setConfigFilePath(std::string path)
   {
      configFilePath = path;
   }
   string getConfigFilePath()
   {
      return configFilePath;
   }
}
