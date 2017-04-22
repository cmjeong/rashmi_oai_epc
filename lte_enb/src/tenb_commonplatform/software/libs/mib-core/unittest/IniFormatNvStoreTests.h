///////////////////////////////////////////////////////////////////////////////
//
// IniFormatNvStoreTests.h
//
// Unit tests for IniFormatNvStore.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IniFormatNvStoreTests_h_
#define __IniFormatNvStoreTests_h_

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

const std::string corruptCurrentVersionFile = "../../../libs/mib-core/unittest/corruptcurrentversion.nv";
const std::string corruptVersionFile = "../../../libs/mib-core/unittest/corruptversion.nv";
const std::string corruptContainerFile = "../../../libs/mib-core/unittest/corruptcontainer.nv";
const std::string corruptAttributeFile = "../../../libs/mib-core/unittest/corruptattribute.nv";

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <algorithm>

// C headers
#include <cstdlib> // system
#include <unistd.h> // POSIX header for unlink()
#include <sys/stat.h> // stat
#include <ctime> // difftime

// Radisys headers
#include <Radisys.h>
#include <cppunit/TestCase.h>
#include <system/Trace.h>

// Header of class under test
#include <mib-core/IniFormatNvStore.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IniFormatNvStoreTests : public CppUnit::TestCase
{
public:
    ~IniFormatNvStoreTests() {
    }
    void runTest()
    {
        struct stat bufferBefore, bufferAfter;
        int         status;

        std::cout
             << std::endl
             << std::endl
             << "**********************" << std::endl
             << "IniFormatNvStore tests" << std::endl
             << "**********************" << std::endl
             << std::endl;

        std::string filename = "iniformatnvstoretests.nv";
        // Clearing up previous test
        TRACE_MSG("Deleting old storage file");
        unlink(filename.c_str());

        // Initialisations
        TRACE_MSG("Creating the IniFormatNvStore");
        IniFormatNvStore iniFormatNvStore;

        TRACE_MSG("Initialising the IniFormatNvStore");
        iniFormatNvStore.SetStoreFileName(filename);
        iniFormatNvStore.InitialiseNvStore();
        iniFormatNvStore.SetCurrentNvStoreSchemaVersion(5);

        TRACE_MSG("Creating a NvContainer Descriptor");
        NvContainerDescriptor nvContainer;
        nvContainer.m_nvContainerName = "containerName";
        nvContainer.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainer2;
        nvContainer2.m_nvContainerName = "containerName2";
        nvContainer2.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainer3;
        nvContainer3.m_nvContainerName = "containerName3";
        nvContainer3.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainer4;
        nvContainer4.m_nvContainerName = "containerName4";
        nvContainer4.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainer5;
        nvContainer5.m_nvContainerName = "containerName5";
        nvContainer5.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainerEmpty;
        nvContainerEmpty.m_nvContainerName = "containerNameEmpty";
        nvContainerEmpty.m_nvContainerInstance = 0;


        TRACE_MSG("Creating a list of NvAttributes");

        std::vector<NvAttribute> nvAttributeList;
        NvAttribute nvAttribute(NvAttributeDescriptor("attributeName", 0), "37", 1);
        nvAttributeList.push_back(nvAttribute);

        std::vector<NvAttribute> nvAttributeList2;
        NvAttribute nvAttribute2(NvAttributeDescriptor("attributeName2", 1), "attributeValue2", 1);
        nvAttributeList2.push_back(nvAttribute2);

        std::vector<NvAttribute> nvAttributeList3;
        NvAttribute nvAttribute3(NvAttributeDescriptor("attributeName3", 0), "attributeValue3", 1);
        nvAttributeList3.push_back(nvAttribute3);

        std::vector<NvAttribute> nvAttributeList4;
        NvAttribute nvAttribute4(NvAttributeDescriptor("attributeName4", 0), "attributeValue4", 1);
        nvAttributeList4.push_back(nvAttribute4);

        NvAttribute nvAttributeReceive(NvAttributeDescriptor("", 0), "", 0);

        // Test setting an attribute
        TRACE_MSG("Adding the attribute list to the IniFormatNvStore");
        iniFormatNvStore.SetNvAttributes(nvContainer, nvAttributeList);
        TRACE_MSG("Checking that the container now exists in the IniFormatNvStore");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvContainerPresent(nvContainer) == true);
        TRACE_MSG("Checking that the attribute now exists in the IniFormatNvStore");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvAttributePresent(nvContainer,nvAttribute.m_nvAttributeDescriptor.m_nvAttributeName) == true);

        // Test getting an attribute
        TRACE_MSG("Get an attribute value");
        NvAttributeValue nvAttributeValueReceive;
        iniFormatNvStore.GetNvAttribute(nvContainer, nvAttribute.m_nvAttributeDescriptor, nvAttributeValueReceive);
        CPPUNIT_ASSERT(nvAttributeValueReceive == nvAttribute.m_nvAttributeValue);


        // Test a simple transaction
        TRACE_MSG("Starting a transaction");
        iniFormatNvStore.StartNvTransaction();
        TRACE_MSG("Adding an attribute");
        iniFormatNvStore.SetNvAttributes(nvContainer2, nvAttributeList2);
        TRACE_MSG("Ensuring that attribute hasn't yet been added");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvAttributePresent(nvContainer2, nvAttribute2.m_nvAttributeDescriptor.m_nvAttributeName) == false);
        TRACE_MSG("Adding another to check that multiple writes during a transaction are okay");
        iniFormatNvStore.SetNvAttributes(nvContainer3, nvAttributeList3);
        TRACE_MSG("Stopping a transaction");
        iniFormatNvStore.EndNvTransaction();
        TRACE_MSG("Checking that the 2nd attribute now exists in the IniFormatNvStore");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvAttributePresent(nvContainer2,nvAttribute2.m_nvAttributeDescriptor.m_nvAttributeName) == true);
        TRACE_MSG("Checking that the 3rd attribute now exists in the IniFormatNvStore");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvAttributePresent(nvContainer3,nvAttribute3.m_nvAttributeDescriptor.m_nvAttributeName) == true);

        // Test CancelNvTransaction
        TRACE_MSG("Starting a transaction");
        iniFormatNvStore.StartNvTransaction();
        TRACE_MSG("Adding an attribute");
        iniFormatNvStore.SetNvAttributes(nvContainer4, nvAttributeList4);
        TRACE_MSG("Cancelling a transaction");
        iniFormatNvStore.CancelNvTransaction();
        TRACE_MSG("Ensuring that attribute hasn't yet been added");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvAttributePresent(nvContainer4, nvAttribute4.m_nvAttributeDescriptor.m_nvAttributeName) == false);

        TRACE_MSG("Adding an attribute");
        iniFormatNvStore.SetNvAttributes(nvContainer4, nvAttributeList4);
        TRACE_MSG("Checking that the 4th attribute now exists in the IniFormatNvStore");
        CPPUNIT_ASSERT(iniFormatNvStore.IsNvAttributePresent(nvContainer4,nvAttribute4.m_nvAttributeDescriptor.m_nvAttributeName) == true);


        /// Test GetNvContainerInstances
        TRACE_MSG("Getting null container instance set");
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvContainerInstances(nvContainerEmpty.m_nvContainerName).empty()); // container was never added
        TRACE_MSG("Getting singleton container instance set");
        ++nvContainer5.m_nvContainerInstance;
        iniFormatNvStore.SetNvAttributes(nvContainer5, nvAttributeList4);
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvContainerInstances(nvContainer5.m_nvContainerName).size() == 1); // two containers, same name, different instances
        TRACE_MSG("Getting multiple container instance set");
        ++nvContainer5.m_nvContainerInstance;
        iniFormatNvStore.SetNvAttributes(nvContainer5, nvAttributeList4);
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvContainerInstances(nvContainer5.m_nvContainerName).size() == 2); // three different instances

        // A bit nasty but we reuse the data structure set up from the tests above.
        /* [[!1]]
         * [[@5]]
            [containerName/0]
                attributeName/0 = 37
            [containerName2/0]
                attributeName2/1 = 1
            [containerName3/0]
                attributeName3/0 = 0
            [containerName4/0]
                attributeName4/0 = 0
            [containerName5/1]
                attributeName4/0 = 0
            [containerName5/2]
                attributeName4/0 = 0
         *
         */

        TRACE_MSG("Getting null attribute instance set");
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeInstances(nvContainerEmpty, nvAttribute.m_nvAttributeDescriptor.m_nvAttributeName).empty()); // null set
        TRACE_MSG("Getting singleton attribute instance set");
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeInstances(nvContainer, nvAttribute.m_nvAttributeDescriptor.m_nvAttributeName).size() == 1); // singleton
        TRACE_MSG("Getting multiple attribute instance set");
        std::vector<NvAttribute> nvAttributeList5;
        ++nvAttribute4.m_nvAttributeDescriptor.m_nvAttributeInstance;
        nvAttributeList5.push_back(nvAttribute4);
        iniFormatNvStore.SetNvAttributes(nvContainer5, nvAttributeList5);
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeInstances(nvContainer5, nvAttribute4.m_nvAttributeDescriptor.m_nvAttributeName).size() == 2); // multiple

        TRACE_MSG("Checking the repeated write of attributes doesn't cause an unnecessary rewrite");
        // Get timestamp on file
        status = stat(filename.c_str(), &bufferBefore);
        sleep(1); // this is required since stat measures only in seconds...so ensure the any erroneous writes happen at least 1 second later
        CPPUNIT_ASSERT(status == 0);
        iniFormatNvStore.SetNvAttributes(nvContainer5, nvAttributeList5);
        status = stat(filename.c_str(), &bufferAfter);
        CPPUNIT_ASSERT(status == 0);
        CPPUNIT_ASSERT(std::difftime(bufferBefore.st_mtime, bufferAfter.st_mtime) == 0);

        /*
         * structure update...
         *   [containerName5/2]
         *    attributeName4/0 = 0
         *    attributeName4/1 = 0
         */
        TRACE_MSG("Getting null attribute name set");
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeNames(nvContainerEmpty).empty()); // null set
        TRACE_MSG("Getting singleton attribute name set");
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeNames(nvContainer).size() == 1); // singleton
        TRACE_MSG("Getting multiple attribute name set");
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeNames(nvContainer5).size() == 1); // multiple
        CPPUNIT_ASSERT(iniFormatNvStore.GetNvAttributeInstances(nvContainer5, nvAttribute4.m_nvAttributeDescriptor.m_nvAttributeName).size() == 2);

        IniFormatNvStore iniFormatNvStore2;
        iniFormatNvStore2.SetStoreFileName(filename);
        iniFormatNvStore2.InitialiseNvStore();
        TRACE_MSG("Checking secondary store to ensure the data was saved and loaded back in correctly");
        TRACE_MSG("Getting null attribute name set");
        CPPUNIT_ASSERT(iniFormatNvStore2.GetNvAttributeNames(nvContainerEmpty).empty()); // null set
        TRACE_MSG("Getting singleton attribute name set");
        CPPUNIT_ASSERT(iniFormatNvStore2.GetNvAttributeNames(nvContainer).size() == 1); // singleton
        TRACE_MSG("Getting multiple attribute name set");
        CPPUNIT_ASSERT(iniFormatNvStore2.GetNvAttributeNames(nvContainer5).size() == 1); // multiple
        CPPUNIT_ASSERT(iniFormatNvStore2.GetNvAttributeInstances(nvContainer5, nvAttribute4.m_nvAttributeDescriptor.m_nvAttributeName).size() == 2);
        std::cout << iniFormatNvStore2 << std::endl;

        TRACE_MSG("Testing durability");

        TRACE_MSG("Corrupt current version");
        IniFormatNvStore corruptCurrentVersion;
        corruptCurrentVersion.SetStoreFileName(corruptCurrentVersionFile);
        corruptCurrentVersion.InitialiseNvStore();
        std::cout << corruptCurrentVersion << std::endl;

        TRACE_MSG("Corrupt version");
        IniFormatNvStore corruptVersion;
        corruptVersion.SetStoreFileName(corruptVersionFile);
        corruptVersion.InitialiseNvStore();
        std::cout << corruptVersion << std::endl;

        TRACE_MSG("Corrupt container");
        IniFormatNvStore corruptContainer;
        corruptContainer.SetStoreFileName(corruptContainerFile);
        corruptContainer.InitialiseNvStore();
        std::cout << corruptContainer << std::endl;

        TRACE_MSG("Corrupt attribute");
        IniFormatNvStore corruptAttribute;
        corruptAttribute.SetStoreFileName(corruptAttributeFile);
        corruptAttribute.InitialiseNvStore();
        std::cout << corruptAttribute << std::endl;

        // Clearing up after test
        TRACE_MSG("Deleting storage file");
        unlink(filename.c_str());

    }
};

#endif
