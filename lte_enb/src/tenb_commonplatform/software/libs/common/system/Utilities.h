///////////////////////////////////////////////////////////////////////////////
//
// Utilities.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Utilities_h_
#define __Utilities_h_

#include <string>

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{
   std::string getConfigParamFromFile(const char *filename,
         const char *name,
         const char *defaultValue);
   std::string getConfigParam(const char *name, const char *defaultValue);

   void setConfigFilePath(std::string configFilePath);
   std::string getConfigFilePath();

   u32 getRandomVal();
}
#endif // __Utilities_h_
