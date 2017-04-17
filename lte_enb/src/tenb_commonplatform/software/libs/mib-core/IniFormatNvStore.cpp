///////////////////////////////////////////////////////////////////////////////
//
// IniFormatNvStore.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
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

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <system/NumberConversions.h>
#include <system/ConfigurationFile.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IniFormatNvStore.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

IniFormatNvStore::IniFormatNvStore() :
    m_currentVersion(MIB_NV_SCHEMA_OLDSTYLE),
    m_transactionState(IDLE),
    m_initialised(false),
    m_updateInheritedStoreRequired(false),
    m_prohibitSchemaVersionChange(false),
    m_forceReadOnly(false),
    m_doSave(false)
{
   ENTER();

   EXIT();
}

IniFormatNvStore::~IniFormatNvStore()
{
   ENTER();

   // We do NOT write to the file here in case it throws an error. The best we can do
   //  is assert that a transaction is not in progress.
   RSYS_ASSERT(m_transactionState == IDLE);

   EXIT();
}

// Need to move these functions into a more generic file
// START:
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

bool IniFormatNvStore::InitialiseNvStore()
{
   ENTER();

   TRACE_PRINTF("Initialising %s", m_nvStoreFileName.c_str());

   RSYS_ASSERT(not(m_nvStoreFileName.empty()));// ensure file name set
   m_nvAttributesTodo.clear();

   string currentLine;
   const string instanceDelimiter = "/";
   const string avpDelimiter = "=";

   bool configurationFileExists = false;
   bool currentVersionSet = false, versionSet = false, containerSet = false;
   bool fileCurrupted = false;

   // Current version
   NvStoreSchemaVersion version = numeric_limits<NvStoreSchemaVersion>::max();
   // Current container
   string containerName;
   u32 containerInstance = numeric_limits<u32>::max();

   NvContainerDescriptor nvContainerDescriptor;


   ifstream input(m_nvStoreFileName.c_str());

   configurationFileExists = input.good();

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
            trimOuter(currentLine,'[',']');
            if (currentLine[0] == '!')
            {
               m_currentVersion = stringToU32(currentLine.substr(1));
               TRACE_PRINTF("NV configuration:Current Version : %d", m_currentVersion);
               currentVersionSet = true;
            }
            else if (currentLine[0] == '@')
            {
               version = stringToU32(currentLine.substr(1)); // first character is @
               versionSet = true;
               containerSet = false; // we're expecting a container next
            }
         }
         else // should be a container
         {
            if (not(versionSet))
            {
               TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
               // skip this container
               containerSet = false;
               fileCurrupted = true;
               continue;
            }

            string containerInstanceString;
            vector<string> splitStrings;

            if (not(threeway::StringUtils::SplitString(currentLine, instanceDelimiter, splitStrings) == 2))
            {
               TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
               // skip this container
               containerSet = false;
               fileCurrupted = true;
               continue;
            }
            containerInstance = stringToU32(splitStrings[1]);
            chomp(splitStrings[0]);

            // Container to add to
            nvContainerDescriptor.m_nvContainerName = splitStrings[0];
            nvContainerDescriptor.m_nvContainerInstance = containerInstance;

            containerSet = true;
         }
      }
      else if(currentLine[0] == '#') // comment
      {
         // ignore
      }
      else // avp
      {
         if (not(containerSet && versionSet))
         {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "NV configuration is corrupt: %s", currentLine.c_str());
            // skip this attribute
            fileCurrupted = true;
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
            fileCurrupted = true;
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
            fileCurrupted = true;
            continue;
         }

         chomp(splitStrings2[0]); // remove surround whitespace
         instance = stringToU32(splitStrings2[1]);
         // NvAttribute
         NvAttribute nvAttribute(NvAttributeDescriptor(splitStrings2[0], instance), splitStrings[1].c_str(), version);

         NvAttributeMap::iterator i = m_nvCompleteAttributeStore[version][nvContainerDescriptor].find(nvAttribute.m_nvAttributeDescriptor);
        if(i != m_nvCompleteAttributeStore[version][nvContainerDescriptor].end())
        {
            i->second = nvAttribute;
        }
        else
        {
          m_nvCompleteAttributeStore[version][nvContainerDescriptor].insert(make_pair<NvAttributeDescriptor,NvAttribute>(nvAttribute.m_nvAttributeDescriptor, nvAttribute));
        }
      }
   }

   if (not(configurationFileExists) || not(currentVersionSet) || fileCurrupted) // ensure we saw a [[!number]] somewhere in the file
   {
      TRACE_MSG_LEV(TRACE_CRITICAL, "NV configuration is corrupt; no current version information");
      return false;
   }

   UpdateInheritedNvStore();

   // Finally, signal that we've practically completed initialisation
   m_initialised = true;

   return true;
}

void IniFormatNvStore::UpdateInheritedNvStore()
{
   ENTER();

   TRACE_MSG_LEV(TRACE_VERBOSE, "Updating inherited in-RAM NV store.");

   m_nvInheritedAttributeStore.clear();

   // Loop from oldest schema version (1) to current overwriting attributes as we go so that
   // we end up with the latest and greatest in one map.

   for(NvStoreSchemaVersion schema = 1; schema <= m_currentVersion; schema++)
   {
      // See if this version exists.
      map<NvStoreSchemaVersion, NvStoreMap>::const_iterator schemaVersionIter = m_nvCompleteAttributeStore.find(schema);
      if(schemaVersionIter != m_nvCompleteAttributeStore.end())
      {
         TRACE_PRINTF_LEV(TRACE_VERBOSE, "Schema %"PRIu32" exists in complete store.  NvStoreMap size=%"PRIu32, schema, (u32)schemaVersionIter->second.size());

         // Schema version exists in complete store.
         // Iterate over the containers and attributes and copy them in.
         for (NvStoreMap::const_iterator versionedContainerIter = schemaVersionIter->second.begin();
               versionedContainerIter != schemaVersionIter->second.end();
               ++versionedContainerIter)
         {
            TRACE_PRINTF_LEV(TRACE_VERBOSE, "Container %s exists in complete store.", versionedContainerIter->first.m_nvContainerName.c_str());
            NvStoreMap::iterator checkIfContainerExistsIter = m_nvInheritedAttributeStore.find(versionedContainerIter->first);
            if(checkIfContainerExistsIter != m_nvInheritedAttributeStore.end())
            {
               TRACE_PRINTF_LEV(TRACE_VERBOSE, "Container %s already exists in inherited store.", versionedContainerIter->first.m_nvContainerName.c_str());
               // Already exists, iterate over attributes and copy them in one by one.
               for(NvAttributeMap::const_iterator attrIter = versionedContainerIter->second.begin();
                     attrIter != versionedContainerIter->second.end();
                     ++attrIter)
               {
                  TRACE_PRINTF_LEV(TRACE_VERBOSE, "Adding attr %s/%"PRIu32" = %s.  Map size now %"PRIu32,
                        attrIter->first.m_nvAttributeName.c_str(),
                        attrIter->first.m_nvAttributeInstance,
                        attrIter->second.m_nvAttributeValue.GetAsString().c_str(),
                        (u32)m_nvInheritedAttributeStore.at(versionedContainerIter->first).size());
                  if(checkIfContainerExistsIter->second.find(attrIter->first) != checkIfContainerExistsIter->second.end())
                  {
                     // Have to erase as insert() won't overwrite.
                     checkIfContainerExistsIter->second.erase(attrIter->first);
                  }
                  checkIfContainerExistsIter->second.insert(make_pair<NvAttributeDescriptor, NvAttribute>(attrIter->first, attrIter->second));
               }
            }
            else
            {
               TRACE_PRINTF_LEV(TRACE_VERBOSE, "Container %s doesn't exist in inherited store.", versionedContainerIter->first.m_nvContainerName.c_str());
               // Doesn't exist, copy whole container.
               m_nvInheritedAttributeStore[versionedContainerIter->first] = versionedContainerIter->second;
            }
         }
      }
   }

   m_updateInheritedStoreRequired = false;

   EXIT();
}


bool IniFormatNvStore::IsNvContainerPresent(const NvContainerDescriptor& nvContainerDescriptor) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_updateInheritedStoreRequired));

   RETURN(not(m_nvInheritedAttributeStore.find(nvContainerDescriptor) == m_nvInheritedAttributeStore.end()));
}

vector<u32> IniFormatNvStore::GetNvContainerInstances(const NvContainerName& nvContainerName) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_updateInheritedStoreRequired));

   vector<u32> vec;

   for(NvStoreMap::const_iterator iter = m_nvInheritedAttributeStore.begin();
         iter != m_nvInheritedAttributeStore.end();
         ++iter)
   {
      if (iter->first.m_nvContainerName == nvContainerName)
      {
         vec.push_back(iter->first.m_nvContainerInstance);
      }
   }

   RETURN(vec);
}

bool IniFormatNvStore::IsNvAttributePresent(const NvContainerDescriptor& nvContainerDescriptor,
      const NvAttributeName& nvAttributeName) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_updateInheritedStoreRequired));


   for(NvStoreMap::const_iterator iter = m_nvInheritedAttributeStore.begin();
         iter != m_nvInheritedAttributeStore.end();
         ++iter)
   {
      for (NvAttributeMap::const_iterator attrIter = iter->second.begin(); attrIter != iter->second.end(); ++attrIter )
      {
         if (attrIter->first.m_nvAttributeName == nvAttributeName)
         {
            RETURN (true);
         }
      }
   }

   RETURN(false);
}

vector<u32> IniFormatNvStore::GetNvAttributeInstances(const NvContainerDescriptor& nvContainerDescriptor,
      const NvAttributeName& nvAttributeName) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_updateInheritedStoreRequired));


   vector<u32> vec;

   for(NvStoreMap::const_iterator containerIter = m_nvInheritedAttributeStore.begin();
         containerIter != m_nvInheritedAttributeStore.end();
         ++containerIter)
   {
      if (containerIter->first == nvContainerDescriptor)
      {
         for (NvAttributeMap::const_iterator attrIter = containerIter->second.begin(); attrIter != containerIter->second.end(); ++attrIter )
         {
            if (attrIter->first.m_nvAttributeName == nvAttributeName)
            {
               vec.push_back(attrIter->first.m_nvAttributeInstance);
            }
         }
      }
   }

   RETURN(vec);
}

vector<NvAttributeName> IniFormatNvStore::GetNvAttributeNames(const NvContainerDescriptor& nvContainerDescriptor) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_updateInheritedStoreRequired));

   // By using a set we ensure that we don't duplicate attribute names when there are 2 instances
   set<NvAttributeName> attributeNames;

   NvStoreMap::const_iterator attributeMapIter = m_nvInheritedAttributeStore.find(nvContainerDescriptor);

   if (not(attributeMapIter == m_nvInheritedAttributeStore.end())) // check that descriptor is in the map
   {
      for (NvAttributeMap::const_iterator attrIter = attributeMapIter->second.begin(); attrIter != attributeMapIter->second.end(); ++attrIter )
      {
         attributeNames.insert(attrIter->first.m_nvAttributeName);
      }
   }

   vector<NvAttributeName> result(attributeNames.begin(), attributeNames.end());

   RETURN(result);
}

NvAttributeResult IniFormatNvStore::GetNvAttribute(const NvContainerDescriptor& nvContainerDescriptor,
      const NvAttributeDescriptor& nvAttributeDescriptor,
      NvAttributeValue& nvAttributeValue) const
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_updateInheritedStoreRequired));


   NvAttributeResult result;
   NvStoreMap::const_iterator attributeMapIter = m_nvInheritedAttributeStore.find(nvContainerDescriptor);

   if (not(attributeMapIter == m_nvInheritedAttributeStore.end())) // check that descriptor is in the map
   {
      result = NV_ATTRIBUTE_RESULT_NO_SUCH_ATTRIBUTE;
      NvAttributeMap::const_iterator attrIter = attributeMapIter->second.find(nvAttributeDescriptor);
      if (not(attrIter == attributeMapIter->second.end()))
      {
         nvAttributeValue = attrIter->second.m_nvAttributeValue;
         result = NV_ATTRIBUTE_RESULT_OK;
      }
   }
   else
   {
      result = NV_ATTRIBUTE_RESULT_NO_SUCH_CONTAINER;
   }

   RETURN(result);
}

void IniFormatNvStore::SetNvAttributes(const NvContainerDescriptor& nvContainerDescriptor, const vector<NvAttribute>& nvAttributes)
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT((m_transactionState == IDLE) || (m_transactionState == DECIDEACTION) || (m_transactionState == ADD));

   // Auto learn the type of transaction
   if (m_transactionState == DECIDEACTION)
   {
      m_transactionState = ADD;
   }

   if(m_forceReadOnly)
   {
      TRACE_PRINTF_LEV(TRACE_WARNING, "Attempting to write to NV store %s but it is read-only", m_nvStoreFileName.c_str());
      for(vector<NvAttribute>::const_iterator iter = nvAttributes. begin(); iter != nvAttributes.end(); ++iter)
      {
         TRACE_PRINTF("  Attempting to write NV attribute %s/%" PRIu32 " = %s",
               (*iter).m_nvAttributeDescriptor.m_nvAttributeName.c_str(),
               (*iter).m_nvAttributeDescriptor.m_nvAttributeInstance,
               (*iter).m_nvAttributeValue.GetAsString().c_str());
      }
      RETURN_VOID();
   }

   for(vector<NvAttribute>::const_iterator iter = nvAttributes. begin(); iter != nvAttributes.end(); ++iter)
   {
      if(m_nvAttributesTodo[nvContainerDescriptor].find(iter->m_nvAttributeDescriptor) != m_nvAttributesTodo[nvContainerDescriptor].end())
      {
         TRACE_PRINTF_LEV(TRACE_WARNING,
               "Setting NV attribute %s/%"PRIu32" for which we already have a pending value",
               iter->m_nvAttributeDescriptor.m_nvAttributeName.c_str(),
               iter->m_nvAttributeDescriptor.m_nvAttributeInstance
               );
         m_nvAttributesTodo[nvContainerDescriptor].erase(iter->m_nvAttributeDescriptor);
      }
      m_nvAttributesTodo[nvContainerDescriptor].insert(make_pair<NvAttributeDescriptor, NvAttribute>(iter->m_nvAttributeDescriptor, *iter));
   }

   if (m_transactionState == IDLE)
   {
      m_transactionState = ADD;
      // Write values out to file
      ForceNvFlush();
      m_transactionState = IDLE;
   }
   else
   {
      // We only allow version numbers to be changed at the start of a transaction
      m_prohibitSchemaVersionChange = true;
   }

   EXIT();
}

void IniFormatNvStore::DeleteNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
      const vector<NvAttributeDescriptor>& nvAttributeDescriptors)
{
   ENTER();

   RSYS_ASSERT((m_transactionState == IDLE) || (m_transactionState == DECIDEACTION) || (m_transactionState == DELETE));

   // Auto learn the type of transaction
   if (m_transactionState == DECIDEACTION)
   {
      m_transactionState = DELETE;
   }

   m_nvAttributesMarked[nvContainerDescriptor].insert(m_nvAttributesMarked[nvContainerDescriptor].end(), nvAttributeDescriptors.begin(), nvAttributeDescriptors.end());

   if (m_transactionState == IDLE)
   {
      m_transactionState = DELETE;
      // Write values out to file
      ForceNvFlush();
      m_transactionState = IDLE;
   }
   else
   {
      // We only allow version numbers to be changed at the start of a transaction
      m_prohibitSchemaVersionChange = true;
   }

   EXIT();
}

void IniFormatNvStore::StartNvTransaction()
{
   ENTER();

   RSYS_ASSERT_PRINTF(m_initialised,"Class not initialised");
   RSYS_ASSERT_PRINTF(m_transactionState == IDLE, "Nested transactions");
   RSYS_ASSERT_PRINTF(m_nvAttributesTodo.empty(), "Attributes remain in list");
   RSYS_ASSERT_PRINTF(m_nvAttributesMarked.empty(), "Attributes remain in list");

   // Flush existing transactions out to the file.
   ForceNvFlush(); // Should not be necessary

   m_transactionState = DECIDEACTION;

   EXIT();
}

void IniFormatNvStore::SetNvDeleteTransactionExceptions(const NvContainerDescriptor& nvContainerDescriptor)
{
   ENTER();

   // Auto learn the type of transaction
   if (m_transactionState == DECIDEACTION)
   {
      m_transactionState = RESET;
   }

   RSYS_ASSERT(m_transactionState == RESET);

   m_nvContainersMarked.push_back(nvContainerDescriptor);

   EXIT();
}

void IniFormatNvStore::SetNvDeleteTransactionExceptions(const NvContainerDescriptor& nvContainerDescriptor,
      const vector<NvAttributeDescriptor>& nvAttributeDescriptors)
{
   ENTER();

   RSYS_ASSERT((m_transactionState == DECIDEACTION) || (m_transactionState == RESET));

   // Auto learn the type of transaction
   if (m_transactionState == DECIDEACTION)
   {
      m_transactionState = RESET;
   }

   m_nvAttributesMarked[nvContainerDescriptor].insert(m_nvAttributesMarked[nvContainerDescriptor].end(), nvAttributeDescriptors.begin(), nvAttributeDescriptors.end());

   EXIT();
}

void IniFormatNvStore::EndNvTransaction()
{
   ENTER();

   RSYS_ASSERT_PRINTF(m_initialised, "Class not initialised");
   RSYS_ASSERT_PRINTF(not(m_transactionState == IDLE), "No transaction started");

   // Flush existing transactions out to the file.
   ForceNvFlush();

   m_transactionState = IDLE;
   m_prohibitSchemaVersionChange = false;

   EXIT();
}

void IniFormatNvStore::CancelNvTransaction()
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT_PRINTF(not(m_transactionState == IDLE), "No transaction started");

   // Discard existing transactions by re parsing the ini file.
   m_nvAttributesTodo.clear();
   m_nvAttributesMarked.clear();
   m_transactionState = IDLE;
   m_prohibitSchemaVersionChange = false;

   EXIT();
}

void IniFormatNvStore::MakeNvReadOnly()
{
   ENTER();

   m_forceReadOnly = true;

   EXIT();
}

void IniFormatNvStore::ForceNvFlush()
{
   ENTER();

   RSYS_ASSERT(m_initialised);

   if(m_forceReadOnly)
   {
      TRACE_PRINTF_LEV(TRACE_WARNING, "Attempting to flush NV store %s but it is read-only", m_nvStoreFileName.c_str());
      RETURN_VOID();
   }

   // ForceNvFlush has 2 meanings dependent on whether we're in the mist of a delete type transaction or not
   // Merge the to do list with the current model
   // To Do containers
   if ((m_transactionState == DELETE) || (m_transactionState == RESET)) // delete transaction
   {
      // For each version up to the current one.
      for(NvStoreSchemaVersion schema = 1; schema <= m_currentVersion; schema++)
      {
         // See if this version exists.
         map<NvStoreSchemaVersion, NvStoreMap>::iterator schemaVersionIter = m_nvCompleteAttributeStore.find(schema);
         if(schemaVersionIter != m_nvCompleteAttributeStore.end())
         {
            // for each container
            for (NvStoreMap::iterator containerIter = schemaVersionIter->second.begin();
                  containerIter != schemaVersionIter->second.end();
                  ++containerIter)
            {
               // for each attribute
               NvAttributeMap::iterator attrIter = containerIter->second.begin();
               while (attrIter != containerIter->second.end())
               {
                  bool foundAttribute = false;

                  // Is attribute in the save list?
                  for (vector<NvContainerDescriptor>::const_iterator containerIter1 = m_nvContainersMarked.begin();
                        containerIter1 != m_nvContainersMarked.end();
                        ++containerIter1 )
                  {
                     if (*containerIter1 == containerIter->first)
                     {
                        foundAttribute = true;
                        break;
                     }
                  }

                  if( !foundAttribute )
                  {
                     // iterate through todoContainers
                     map<NvContainerDescriptor, vector<NvAttributeDescriptor> >::const_iterator todoContainerIter2 = m_nvAttributesMarked.find(containerIter->first);
                     if (not(todoContainerIter2 == m_nvAttributesMarked.end()))
                     {
                        for (vector<NvAttributeDescriptor>::const_iterator todoAttrIter = todoContainerIter2->second.begin();
                              todoAttrIter != todoContainerIter2->second.end();
                              ++todoAttrIter)
                        {
                           if (attrIter->first == *todoAttrIter)
                           {
                              foundAttribute = true;
                              break;
                           }
                        }
                     } // for each to-do container
                  }

                  if (((m_transactionState == RESET) && not(foundAttribute)) || ((m_transactionState == DELETE) && foundAttribute))
                  {
                     NvAttributeMap::iterator deleteAttrIter = attrIter;
                     ++attrIter;
                     // delete attribute
                     containerIter->second.erase(deleteAttrIter);
                     m_updateInheritedStoreRequired = true;
                  }
                  else // next attribute
                  {
                     ++attrIter;
                  }
               } // for each attribute
            } // for each container
         }
      } // for each version
   } // inside a reset or delete transaction
   else if (m_transactionState == ADD)
   {
      // Loop through the to-do list, first by container, then by attribute descriptor.
      for (NvStoreMap::iterator todoContainerIter = m_nvAttributesTodo.begin();
            todoContainerIter != m_nvAttributesTodo.end();
            ++todoContainerIter)
      {
         // To Do attributes in those containers
         for (NvAttributeMap::iterator todoAttrIter = todoContainerIter->second.begin();
               todoAttrIter != todoContainerIter->second.end();
               ++todoAttrIter)
         {
            // Looping through each to-do attribute...

            // Each attribute has a schema version which we use to put it in the correct place in the complete NV store.
            NvStoreSchemaVersion attrSchemaVersion = todoAttrIter->second.m_schemaVersion;

            // Check we're not trying to add something we don't understand.
            RSYS_ASSERT_PRINTF(attrSchemaVersion <= m_currentVersion,
                  "Trying to add attribute at schema version %"PRIu32" but current schema version is %"PRIu32,
                  attrSchemaVersion, m_currentVersion);

            // Find/create the container in our existing attribute store.
            NvAttributeMap& completeStoreContainer = m_nvCompleteAttributeStore[attrSchemaVersion][todoContainerIter->first];

            // Check if attribute is already there.
            NvAttributeMap::iterator completeStoreAttrIter = completeStoreContainer.find(todoAttrIter->first /* attr descriptor */);
            if (completeStoreAttrIter != completeStoreContainer.end())
            {
               // It's already there... check the value...
               RSYS_ASSERT_PRINTF(completeStoreAttrIter->second.m_schemaVersion == attrSchemaVersion,
                     "Schema version mismatch on attr already in NV store, expect=%"PRIu32", got=%"PRIu32", todoAttr=%s",
                     attrSchemaVersion, completeStoreAttrIter->second.m_schemaVersion, todoAttrIter->second.m_nvAttributeDescriptor.m_nvAttributeName.c_str());
               if (not(completeStoreAttrIter->second.m_nvAttributeValue == todoAttrIter->second.m_nvAttributeValue))
               {
                  // Value has changed so we need to save.
                  // Store the value.
                  completeStoreContainer.erase(todoAttrIter->first);
                  completeStoreContainer.insert(make_pair<NvAttributeDescriptor, NvAttribute>(todoAttrIter->first, todoAttrIter->second));
                  DeleteFromIntermediateSchemas(attrSchemaVersion, todoContainerIter->first, todoAttrIter->first);
                  m_updateInheritedStoreRequired = true;
               }
            }
            else
            {
               // It's not there.
               // Store the value.
               completeStoreContainer.insert(make_pair<NvAttributeDescriptor, NvAttribute>(todoAttrIter->first, todoAttrIter->second));
               DeleteFromIntermediateSchemas(attrSchemaVersion, todoContainerIter->first, todoAttrIter->first);
               m_updateInheritedStoreRequired = true;
            }

            TRACE_PRINTF("Added %s = %s",
                  m_nvCompleteAttributeStore.at(attrSchemaVersion).at(todoContainerIter->first).at(todoAttrIter->first).m_nvAttributeDescriptor.m_nvAttributeName.c_str(),
                  m_nvCompleteAttributeStore.at(attrSchemaVersion).at(todoContainerIter->first).at(todoAttrIter->first).m_nvAttributeValue.GetAsString().c_str());
         } // for each to-do attribute
      } // for each to-do container
   } // in a add transaction


   if(m_updateInheritedStoreRequired)
   {
      UpdateInheritedNvStore();
      m_doSave = true;
   }

   if (m_doSave)
   {
      TRACE_PRINTF("Flushing NV store %s", m_nvStoreFileName.c_str());

      // Write out values to the file.
      writeToNvFile();
      m_doSave = false; // clear this flag
   }

   // Clear the to do lists
   m_nvAttributesTodo.clear();
   m_nvAttributesMarked.clear();

   EXIT();
}

void IniFormatNvStore::DeleteFromIntermediateSchemas(NvStoreSchemaVersion attrSchema, const NvContainerDescriptor& container, const NvAttributeDescriptor& attrDesc)
{
   // Now loop through schemas after this one and delete any instances of this attribute.
   // This takes account of the old NV scheme where all values were written into the current
   // schema block regardles of the attribute schema version.
   for(NvStoreSchemaVersion subsequentSchema = attrSchema + 1;
         subsequentSchema <= m_currentVersion;
         ++subsequentSchema)
   {
      if(m_nvCompleteAttributeStore.find(subsequentSchema) != m_nvCompleteAttributeStore.end())
      {
         // Schema exists.
         if(m_nvCompleteAttributeStore[subsequentSchema].find(container) != m_nvCompleteAttributeStore[subsequentSchema].end())
         {
            // Container exists.
            if(m_nvCompleteAttributeStore[subsequentSchema][container].find(attrDesc) != m_nvCompleteAttributeStore[subsequentSchema][container].end())
            {
               // Attribute exists, delete it.
               m_nvCompleteAttributeStore[subsequentSchema][container].erase(attrDesc);
            }

         }
      }
   }
}

void IniFormatNvStore::SetCurrentNvStoreSchemaVersion(NvStoreSchemaVersion newSchemaVersion)
{
   ENTER();

   RSYS_ASSERT(m_initialised);
   RSYS_ASSERT(not(m_prohibitSchemaVersionChange));

   if(m_forceReadOnly)
   {
      TRACE_PRINTF_LEV(TRACE_WARNING, "Attempting to set current schema version on NV store %s but it is read-only", m_nvStoreFileName.c_str());
      RETURN_VOID();
   }

   if (m_currentVersion != newSchemaVersion)
   {
      m_currentVersion  = newSchemaVersion;
      m_updateInheritedStoreRequired = true;

      // We'll definitely want to save to NV at some point.
      m_doSave = true;

      // Flush immediately if not in a transaction.
      if (m_transactionState == IDLE)
      {
         m_transactionState = ADD;
         // Write values out to file
         ForceNvFlush();
         m_transactionState = IDLE;
      }

      // Make sure we've done this.  A change in schema version is done during
      // an upgrade and we want to make sure the client can read the value
      // associated with the new schema (if this unit had previously been
      // upgraded to the same scheme for instance).
      if(m_updateInheritedStoreRequired)
      {
         UpdateInheritedNvStore();
      }

   }

   EXIT();
}

ostream & operator<<(ostream & os, const NvAttributeMap::value_type &nvAttributeMapItem)
{
   os << nvAttributeMapItem.first << " = " << nvAttributeMapItem.second.m_nvAttributeValue.GetAsString();

   return(os);
}

ostream & operator<<(ostream & os, const IniFormatNvStore &iniFormatNvStore)
{
   ENTER();

   // Record the current version in the file
   os << "[[!" << iniFormatNvStore.GetCurrentNvStoreSchemaVersion() << "]]" << endl;
   // Loop through each version
   for (map<u32, NvStoreMap>::const_iterator versionIter = iniFormatNvStore.m_nvCompleteAttributeStore.begin();
         versionIter != iniFormatNvStore.m_nvCompleteAttributeStore.end();
         ++versionIter)
   {
      if(!versionIter->second.empty())
      {
         os << "[[@" << versionIter->first << "]]" << endl;

         // Loop through each container in that version
         for (NvStoreMap::const_iterator containerIter = versionIter->second.begin();
               containerIter != versionIter->second.end();
               ++containerIter)
         {
            os << containerIter->first << endl;

            // Loop through each attribute in that container in that version
            for (NvAttributeMap::const_iterator attrIter = containerIter->second.begin();
                  attrIter != containerIter->second.end();
                  ++attrIter)
            {
               os << *attrIter << endl;
            }
         } // container
      }
   } // version

   RETURN(os);
}

void IniFormatNvStore::DeleteNvContainer( NvContainerDescriptor& nvContainerDescriptor)
{
   for(NvStoreSchemaVersion schema = 1; schema <= m_currentVersion; schema++)
   {
      map<NvStoreSchemaVersion, NvStoreMap>::iterator schemaVersionIter = m_nvCompleteAttributeStore.find(schema);
      if(schemaVersionIter != m_nvCompleteAttributeStore.end())
      {
         NvStoreMap::iterator containerIter = schemaVersionIter->second.find(nvContainerDescriptor);
         if(containerIter !=  schemaVersionIter->second.end())
         {
            m_nvCompleteAttributeStore[schema].erase(containerIter);
            break;
         }
      }
   }
   UpdateInheritedNvStore();
   writeToNvFile();
}

void IniFormatNvStore::writeToNvFile()
{

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
