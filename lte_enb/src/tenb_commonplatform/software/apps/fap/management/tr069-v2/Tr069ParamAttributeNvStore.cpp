///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParamAttributeNvStore.cpp
//
// Class for handling all the alarm events.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iterator>  // ostream_iterator,iterator
#include <set>       // for uniquifying a vector
#include <limits>
#include <algorithm> // for_each, count_if
#include <sstream>
#include <cstdio>    // fileno, rename
#include <unistd.h>  // open, close, fflush, sync
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <system/NumberConversions.h>
#include <system/ConfigurationFile.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069ParamAttributeNvStore.h"



///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Tr069ParamAttributeNvStore::Tr069ParamAttributeNvStore() :
   m_initialised(false)
{
   ENTER();

   EXIT();
}

Tr069ParamAttributeNvStore::~Tr069ParamAttributeNvStore()
{
   ENTER();
}

void chomp(string& to_trim)
{
   ENTER();

   size_t lstrip = to_trim.find_first_not_of(" \t\n");
   size_t rstrip = to_trim.find_last_not_of(" \t\n");

   if (lstrip == string::npos || rstrip == string::npos)
   {
      to_trim = "";
   }
   else
   {
      to_trim = to_trim.substr(lstrip, rstrip + 1);
   }

   EXIT();
}

void trimOuter(string& to_trim, char left, char right)
{
   ENTER();

   size_t lstrip = to_trim.find(left);
   size_t rstrip = to_trim.rfind(right);

   if (lstrip == string::npos && rstrip == string::npos) {
      to_trim = "";
   }
   else if (lstrip == string::npos)
   {
      to_trim = to_trim.substr(0, rstrip-1);
   }
   else if (rstrip == string::npos)
   {
      to_trim = to_trim.substr(lstrip+1);
   }
   else
   {
      to_trim = to_trim.substr(lstrip+1, rstrip-1);
   }

   EXIT();
}

u32 stringToU32(const string& inputString)
{
   ENTER();

   u32 result = 0;

   stringstream tempSS;
   tempSS << inputString;
   tempSS >> result;

   RETURN(result);
}
void Tr069ParamAttributeNvStore::InitialiseParamAttributeNvStore()
{
   TRACE_PRINTF("Initialising %s", m_nvStoreFileName.c_str());
   RSYS_ASSERT(not(m_nvStoreFileName.empty()));// ensure file name set

   string currentLine;
   const string instanceDelimiter = "/";
   const string avpDelimiter = "=";

   bool containerSet = false;

   // Current container
   string containerName;
   u32 containerInstance = numeric_limits<u32>::max();

   NvContainerDescriptor nvContainerDescriptor;
   ExtDMAttrNotificationType notificationType;
   ifstream input(m_nvStoreFileName.c_str());

   // Read in values from file
   while (getline(input, currentLine))
   {
      // Trim whitespace from line
      chomp(currentLine);
      // Skip empty lines
      if (currentLine.empty())
      {
         continue;
      }

      if(currentLine[0] == '[') // version or container
      {
         trimOuter(currentLine,'[',']');
         if(currentLine[0] == '[') // version
         {
            // We dont use version 
         }
         else // should be a container
         {
            string containerInstanceString;
            vector<string> splitStrings;

            if (not(threeway::StringUtils::SplitString(currentLine, instanceDelimiter, splitStrings) == 2))
            {
               TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
               // skip this container
               containerSet = false;
               continue;
            }
            containerInstance = stringToU32(splitStrings[1]);
            chomp(splitStrings[0]);

            // Container to add to
            nvContainerDescriptor.m_nvContainerName = splitStrings[0];
            nvContainerDescriptor.m_nvContainerInstance = containerInstance;

            containerSet = true;
            TRACE_PRINTF("Container SET");
         }
      }
      else if(currentLine[0] == '#') // comment
      {
         // ignore
      }
      else 
      {
         if (not(containerSet))
         {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
            // skip this attribute
            continue;
         }

         u32 instance = 0;
         string nameInstance, name, value, instanceString;

         vector<string> splitStrings;
         threeway::StringUtils::SplitString(currentLine, avpDelimiter, splitStrings);
         if (not((splitStrings.size() == 1) || (splitStrings.size() == 2)))
         {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
            // skip this value
            continue;
         }
         if (splitStrings.size() == 1)
         {
            splitStrings.push_back("");
         }
         chomp(splitStrings[1]); // remove surround whitespace

         vector<string> splitStrings2;
         if (not(threeway::StringUtils::SplitString(splitStrings[0], instanceDelimiter, splitStrings2) == 2))
         {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
            // skip this value
            continue;
         }

         chomp(splitStrings2[0]); // remove surround whitespace
         instance = stringToU32(splitStrings2[1]);
         // NvAttribute
         NvAttribute nvAttribute(NvAttributeDescriptor(splitStrings2[0], instance), splitStrings[1].c_str(), MIB_NV_SCHEMA_OLDSTYLE); // We dont care about version
         notificationType=(ExtDMAttrNotificationType)stringToU32(splitStrings[1]);

         m_nvParamAttStoreMap[nvContainerDescriptor].insert(make_pair<NvAttributeDescriptor,ExtDMAttrNotificationType>(nvAttribute.m_nvAttributeDescriptor, notificationType));
      }
   }

   // Finally, signal that we've practically completed initialisation
   m_initialised = true;
}

bool Tr069ParamAttributeNvStore::IsNvAttributePresent(const NvContainerDescriptor& nvContainerDescriptor,
      const NvAttributeName& nvAttributeName) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);

   for(NvStoreMap::const_iterator iter = m_nvParamAttStoreMap.begin();
         iter != m_nvParamAttStoreMap.end();
         ++iter)
   {
      for (NvParamAttributeMap::const_iterator attrIter = iter->second.begin(); attrIter != iter->second.end(); ++attrIter )
      {
         if (attrIter->first.m_nvAttributeName == nvAttributeName)
         {
            RETURN (true);
         }
      }
   }

   RETURN(false);
}

NvAttributeResult Tr069ParamAttributeNvStore::GetParamAttributeNvVal(const NvContainerDescriptor& nvContainerDescriptor,
      const NvAttributeDescriptor& nvAttributeDescriptor,
      ExtDMAttrNotificationType& nvNotificationType) const
{
   ENTER();
   RSYS_ASSERT(m_initialised);

   NvAttributeResult result;
   NvStoreMap::const_iterator attributeMapIter = m_nvParamAttStoreMap.find(nvContainerDescriptor);
   if (not(attributeMapIter == m_nvParamAttStoreMap.end())) // check that descriptor is in the map
   {
      result = NV_ATTRIBUTE_RESULT_NO_SUCH_ATTRIBUTE;
      NvParamAttributeMap::const_iterator attrIter = attributeMapIter->second.find(nvAttributeDescriptor);

      if (not(attrIter == attributeMapIter->second.end()))
      {
         nvNotificationType = attrIter->second; // get notification value here
         result = NV_ATTRIBUTE_RESULT_OK;
      }
   }
   else
   {
      result = NV_ATTRIBUTE_RESULT_NO_SUCH_CONTAINER;
   }

   RETURN(result);
}

NvAttributeResult Tr069ParamAttributeNvStore::GetParamAttributeNvVal(MibDN dn,string name, ExtDMAttrNotificationType& notify)
{
   RSYS_ASSERT(m_initialised);
   NvAttributeResult result;

   // Remove PARAM_ID_ substring if present
   string param_id = "PARAM_ID_";
   if (name.compare(0,param_id.size(), param_id) == 0)
   {
      name = name.substr(param_id.size());
   }

   NvContainerDescriptor nvContainerDescriptor = GetNvContainerDescriptor(dn);
   char * index = threeway::StringUtils::GetMibObjectInstanceNum(dn.ToString().c_str());
   if(index == NULL)
   {
      TRACE_PRINTF("Index is NULL, hence stopping further validation");
      return NV_ATTRIBUTE_RESULT_NO_SUCH_ATTRIBUTE;
   }
   u32 instance = atoi(index);
   NvAttributeDescriptor nvAttrDesc;
   nvAttrDesc.m_nvAttributeInstance = instance;
   nvAttrDesc.m_nvAttributeName = name;
   result = GetParamAttributeNvVal( nvContainerDescriptor,nvAttrDesc, notify);
   return result;
}

void Tr069ParamAttributeNvStore::SetParamAttributeNvVal(MibDN dn, string name, ExtDMAttrNotificationType notify)
{
   RSYS_ASSERT(m_initialised);

   // Remove PARAM_ID_ substring if present
   string param_id = "PARAM_ID_";
   if (name.compare(0,param_id.size(), param_id) == 0)
   {
      name = name.substr(param_id.size());
   }

   NvContainerDescriptor nvContainerDescriptor = GetNvContainerDescriptor(dn);
   char * index = threeway::StringUtils::GetMibObjectInstanceNum(dn.ToString().c_str());
   if(index == NULL)
   {
      TRACE_PRINTF("Index is NULL, hence stopping further validation");
      return ;
   }
   u32 instance = atoi(index);
   NvAttributeDescriptor nvAttrDesc;
   nvAttrDesc.m_nvAttributeInstance = instance;
   nvAttrDesc.m_nvAttributeName = name;
   SetParamAttributeNvVal( nvContainerDescriptor,nvAttrDesc, notify);
   return ;

}

void Tr069ParamAttributeNvStore::SetParamAttributeNvVal(const NvContainerDescriptor& nvContainerDescriptor,
      const NvAttributeDescriptor& nvAttributeDescriptor,
      ExtDMAttrNotificationType& nvNotificationType)
{
   TRACE_PRINTF("%s ",__FUNCTION__);
   RSYS_ASSERT(m_initialised);

   NvParamAttributeMap::iterator iter = m_nvParamAttStoreMap[nvContainerDescriptor].find(nvAttributeDescriptor);
   if(iter != m_nvParamAttStoreMap[nvContainerDescriptor].end())
   {
      TRACE_PRINTF(
            "Setting NV attribute %s/%"PRIu32" for which we already have a value",
            nvAttributeDescriptor.m_nvAttributeName.c_str(),
            nvAttributeDescriptor.m_nvAttributeInstance
            );
      iter->second = nvNotificationType;

   }
   else
   {
      m_nvParamAttStoreMap[nvContainerDescriptor].insert
         (make_pair<NvAttributeDescriptor,ExtDMAttrNotificationType>(nvAttributeDescriptor,nvNotificationType));
   }
   // Write values out to file
   writeToNvFile();
}

void Tr069ParamAttributeNvStore::writeToNvFile()
{
   RSYS_ASSERT(m_initialised);

   // Write out values to the file.
   string m_nvStoreFileNameTemp = m_nvStoreFileName + ".tmp";
   ofstream output(m_nvStoreFileNameTemp.c_str());
   output << *this;
   output.flush(); // this flushes C++ iostream buffer out to filesystem

   // Flush file out of file system cache 
   FILE* fileHandle  = fopen(m_nvStoreFileNameTemp.c_str(),"a+");
   if(NULL != fileHandle)
   {
      fflush(fileHandle);
      fsync(fileno(fileHandle));
      fclose(fileHandle);
   }

   // Copy file
   rename(m_nvStoreFileNameTemp.c_str(), m_nvStoreFileName.c_str());

}

void Tr069ParamAttributeNvStore::DeleteNvAttributes( NvContainerDescriptor& nvContainerDescriptor,
      const vector<NvAttributeDescriptor>& nvAttributeDescriptors)
{
   RSYS_ASSERT(m_initialised);
   bool updateNvFile = false;

   for(vector<NvAttributeDescriptor>::const_iterator attDescIter = nvAttributeDescriptors.begin();
         attDescIter != nvAttributeDescriptors.end(); ++attDescIter)
   {
      NvParamAttributeMap::iterator iter = m_nvParamAttStoreMap[nvContainerDescriptor].find(*attDescIter);
      if(iter != m_nvParamAttStoreMap[nvContainerDescriptor].end())
      {
         NvParamAttributeMap::iterator deleteAttrIter = iter;
         ++iter;
         // delete attribute
         m_nvParamAttStoreMap[nvContainerDescriptor].erase(deleteAttrIter);
         updateNvFile = true;

      }

   }
   if(updateNvFile)
   {
      // Write values out to file
      writeToNvFile();
   }     

}

void Tr069ParamAttributeNvStore::DeleteNvAttributes(MibDN dn)
{
   bool updateNvFile = false;
   NvContainerDescriptor nvContainerDescriptor = GetNvContainerDescriptor(dn);
   NvStoreMap::iterator attributeMapIter = m_nvParamAttStoreMap.find(nvContainerDescriptor);
   if (not(attributeMapIter == m_nvParamAttStoreMap.end())) // check that descriptor is in the map
   {
      NvStoreMap::iterator deleteIter = attributeMapIter;
      ++attributeMapIter;
      // delete attribute
      m_nvParamAttStoreMap.erase(deleteIter);
      updateNvFile = true;
   }
   if(updateNvFile)
   {
      // Write values out to file
      writeToNvFile();
   }

}

NvContainerDescriptor Tr069ParamAttributeNvStore::GetNvContainerDescriptor(const MibDN& dn)
{
   u32 instance = dn.back().GetMibObjectInstance();
   string name = dn.ToString();
   char * container = NULL;
   if(name == "FAP.0")
   {
      container = (char *)dn.ToString().c_str();
   }
   else
   {
      char * dnName = (char *)alloca(name.length()+1);
      RSYS_ASSERT(dnName !=NULL);
      memcpy(dnName,name.c_str(),name.length());
      dnName[name.length()+1] ='\0';
      container = strtok(dnName,".");
      container = strtok(NULL,".");
      container = strtok(NULL,"."); 
   }
   RSYS_ASSERT(container !=NULL);
   NvContainerName containerName(container);
   NvContainerDescriptor desc(containerName, instance);
   return desc;
}

ostream & operator<<(ostream & os, const NvParamAttributeMap::value_type &nvAttributeMapItem)
{
   os << nvAttributeMapItem.first << " = " << (int)nvAttributeMapItem.second;

   return(os);
}

ostream & operator<<(ostream & os, const Tr069ParamAttributeNvStore &nvStore)
{
   for(NvStoreMap::const_iterator containerIter = nvStore.m_nvParamAttStoreMap.begin();
         containerIter != nvStore.m_nvParamAttStoreMap.end();
         ++containerIter)
   {
      os << containerIter->first << endl;
      for (NvParamAttributeMap::const_iterator attrIter = containerIter->second.begin(); attrIter != containerIter->second.end(); ++attrIter )
      {
         os << *attrIter << endl;
      }
   }
   return(os);
} 


