///////////////////////////////////////////////////////////////////////////////
//
// UpgradeNvStoreTests.h
//
// Unit tests for NonVolatileStoreUpgradeDowngradeInterface.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UpgradeNvStoreTests_h_
#define __UpgradeNvStoreTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <algorithm>

// C headers
#include <cstdlib> // system
#include <unistd.h> // POSIX header for unlink()

// Radisys headers
#include <Radisys.h>
#include <cppunit/TestCase.h>
#include <system/Trace.h>

// Header of class under test
#include <mib-core/IniFormatNvStore.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class UpgradeNvStoreTests : public CppUnit::TestCase
{
public:
    ~UpgradeNvStoreTests() {
    }
    void runTest()
    {
        std::cout
             << std::endl
             << std::endl
             << "***********************************************" << std::endl
             << "NonVolatileStoreUpgradeDowngradeInterface tests" << std::endl
             << "***********************************************" << std::endl
             << std::endl;

        std::string filename = "upgradeiniformatnvstoretests.nv";
        // Clearing up previous test
        TRACE_MSG("Deleting old storage file");
        unlink(filename.c_str());

        /* Unit testing Plan:
         * Container is constant
         * Attribute name varies
         * Attribute instance is constant
         *
         * attribute  |       version
         *            |     1   2   3
         * ---------------------------------
         *    1       |    37  38
         *    2       |    42       43
         *    3       |             47
         *
         * In addition another container will be added in version 2.
         */

        static const NvStoreSchemaVersion SCHEMA_V1 = 1;
        static const NvStoreSchemaVersion SCHEMA_V2 = 2;
        static const NvStoreSchemaVersion SCHEMA_V3 = 3;

        NvContainerDescriptor nvContainer;
        nvContainer.m_nvContainerName = "containerName";
        nvContainer.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainerOfV2Attribs;
        nvContainerOfV2Attribs.m_nvContainerName = "nvContainerOfV2Attribs";
        nvContainerOfV2Attribs.m_nvContainerInstance = 0;

        NvContainerDescriptor nvContainerOfV2AndV3Attribs;
        nvContainerOfV2AndV3Attribs.m_nvContainerName = "nvContainerOfV2AndV3Attribs";
        nvContainerOfV2AndV3Attribs.m_nvContainerInstance = 0;

        std::vector<NvAttribute> nvAttributeListV1;
        NvAttribute nvAttribute1v1(NvAttributeDescriptor("attributeName1", 1), "37", 1);
        NvAttribute nvAttribute2v1(NvAttributeDescriptor("attributeName2", 1), "42", 1);
        nvAttributeListV1.push_back(nvAttribute2v1);
        nvAttributeListV1.push_back(nvAttribute1v1);

        std::vector<NvAttribute> nvAttributeListV2;
        NvAttribute nvAttribute1v2(NvAttributeDescriptor("attributeName1", 1), "38", 2);
        nvAttributeListV2.push_back(nvAttribute1v2);

        std::vector<NvAttribute> nvAttributeListV2AndV3;
        nvAttributeListV2AndV3.push_back(nvAttribute1v2);
        NvAttribute nvAttribute2v3(NvAttributeDescriptor("attributeName2", 1), "43", 3);
        nvAttributeListV2AndV3.push_back(nvAttribute2v3);
        NvAttribute nvAttribute3v3(NvAttributeDescriptor("attributeName3", 1), "47", 3);
        nvAttributeListV2AndV3.push_back(nvAttribute3v3);

        // Initialisations
        boost::shared_ptr<IniFormatNvStore> iniFormatNvStore1(new IniFormatNvStore);

        TRACE_MSG("Setting the version");
        iniFormatNvStore1->SetStoreFileName(filename);
        iniFormatNvStore1->InitialiseNvStore();
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V1);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeListV1);

        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);
        TRACE_MSG("Checking that setting the version worked");
        CPPUNIT_ASSERT(iniFormatNvStore1->GetCurrentNvStoreSchemaVersion() == SCHEMA_V2);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeListV1);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeListV2);

        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V3);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeListV2AndV3);
        iniFormatNvStore1->SetNvAttributes(nvContainerOfV2AndV3Attribs, nvAttributeListV2AndV3);

        // Now reload the file back, looking at 3 different versions of the same file
        iniFormatNvStore1.reset(new IniFormatNvStore);
        iniFormatNvStore1->SetStoreFileName(filename);
        iniFormatNvStore1->InitialiseNvStore();

        NvAttributeValue savedValue;

        // Check that the first version contains only 1 attribute
        TRACE_MSG("Switching to schema 1");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V1);

        TRACE_MSG("Checking attribute names");
        std::vector<NvAttributeName> names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 2);
        CPPUNIT_ASSERT(names.at(0) == nvAttribute1v1.m_nvAttributeDescriptor.m_nvAttributeName);
        CPPUNIT_ASSERT(names.at(1) == nvAttribute2v1.m_nvAttributeDescriptor.m_nvAttributeName);

        TRACE_MSG("Checking attribute instance numbers");
        std::vector<u32> instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(0));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute1v1.m_nvAttributeDescriptor.m_nvAttributeInstance);
        instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(1));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute2v1.m_nvAttributeDescriptor.m_nvAttributeInstance);

        TRACE_MSG("Checking attribute values");
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute1v1.m_nvAttributeDescriptor, savedValue);
        CPPUNIT_ASSERT(nvAttribute1v1.m_nvAttributeValue == savedValue);
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute2v1.m_nvAttributeDescriptor, savedValue);
        CPPUNIT_ASSERT(nvAttribute2v1.m_nvAttributeValue == savedValue);

        TRACE_MSG("Checking it does NOT contain the container that only contains v2 and v3 attribs");
        CPPUNIT_ASSERT(not(iniFormatNvStore1->IsNvContainerPresent(nvContainerOfV2AndV3Attribs)));


        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Checking attribute names");
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 2);
        CPPUNIT_ASSERT(names.at(0) == nvAttribute1v2.m_nvAttributeDescriptor.m_nvAttributeName);
        CPPUNIT_ASSERT(names.at(1) == nvAttribute2v1.m_nvAttributeDescriptor.m_nvAttributeName);

        TRACE_MSG("Checking attribute instance numbers");
        instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(0));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute1v2.m_nvAttributeDescriptor.m_nvAttributeInstance);
        instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(1));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute2v1.m_nvAttributeDescriptor.m_nvAttributeInstance);

        TRACE_MSG("Checking attribute values");
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute1v2.m_nvAttributeDescriptor, savedValue);
        TRACE_PRINTF("nvAttribute1 = %s", savedValue.GetAsString().c_str());
        CPPUNIT_ASSERT(nvAttribute1v2.m_nvAttributeValue == savedValue);
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute2v1.m_nvAttributeDescriptor, savedValue);
        CPPUNIT_ASSERT(nvAttribute2v1.m_nvAttributeValue == savedValue);

        TRACE_MSG("Checking it DOES contain the container that only contains v2 and v3 attribs");
        CPPUNIT_ASSERT(iniFormatNvStore1->IsNvContainerPresent(nvContainerOfV2AndV3Attribs));


        TRACE_MSG("Switching to schema 3");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V3);

        TRACE_MSG("Checking attribute names");
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 3);
        CPPUNIT_ASSERT(names.at(0) == nvAttribute1v2.m_nvAttributeDescriptor.m_nvAttributeName);
        CPPUNIT_ASSERT(names.at(1) == nvAttribute2v3.m_nvAttributeDescriptor.m_nvAttributeName);
        CPPUNIT_ASSERT(names.at(2) == nvAttribute3v3.m_nvAttributeDescriptor.m_nvAttributeName);

        TRACE_MSG("Checking attribute instance numbers");
        instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(0));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute1v2.m_nvAttributeDescriptor.m_nvAttributeInstance);
        instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(1));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute2v3.m_nvAttributeDescriptor.m_nvAttributeInstance);
        instances = iniFormatNvStore1->GetNvAttributeInstances(nvContainer, names.at(2));
        CPPUNIT_ASSERT(instances.size() == 1);
        CPPUNIT_ASSERT(instances.at(0) == nvAttribute3v3.m_nvAttributeDescriptor.m_nvAttributeInstance);

        TRACE_MSG("Checking attribute values");
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute1v2.m_nvAttributeDescriptor, savedValue);
        CPPUNIT_ASSERT(nvAttribute1v2.m_nvAttributeValue == savedValue);
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute2v3.m_nvAttributeDescriptor, savedValue);
        CPPUNIT_ASSERT(nvAttribute2v3.m_nvAttributeValue == savedValue);
        iniFormatNvStore1->GetNvAttribute(nvContainer, nvAttribute3v3.m_nvAttributeDescriptor, savedValue);
        CPPUNIT_ASSERT(nvAttribute3v3.m_nvAttributeValue == savedValue);

        TRACE_MSG("Checking it DOES contain the container that only contains v2 and v3 attribs");
        CPPUNIT_ASSERT(iniFormatNvStore1->IsNvContainerPresent(nvContainerOfV2AndV3Attribs));

        TRACE_MSG("After all this adding and changing schema version we have:");
        std::cout << *iniFormatNvStore1 << std::endl;

        TRACE_MSG("Deleting all attributes save one");
        iniFormatNvStore1->StartNvTransaction();
        std::vector<NvAttributeDescriptor> attributesToSave;
        attributesToSave.push_back(nvAttribute1v1.m_nvAttributeDescriptor);
        iniFormatNvStore1->SetNvDeleteTransactionExceptions(nvContainer, attributesToSave);
        iniFormatNvStore1->EndNvTransaction();

        TRACE_MSG("After deleting all but attributeName1/0 on container containerName/0:");
        std::cout << *iniFormatNvStore1 << std::endl;

        TRACE_MSG("Checking that nvContainer now contains only 1 attribute");
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 1);
        CPPUNIT_ASSERT(names.at(0) == nvAttribute1v1.m_nvAttributeDescriptor.m_nvAttributeName);

        TRACE_MSG("Deleting no attributes");
        iniFormatNvStore1->StartNvTransaction();
        std::vector<NvAttributeDescriptor> attributesToDelete;
        iniFormatNvStore1->DeleteNvAttributes(nvContainer, attributesToDelete);
        iniFormatNvStore1->EndNvTransaction();

        TRACE_MSG("Checking that nvContainer still contains only 1 attribute")
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 1);
        CPPUNIT_ASSERT(names.at(0) == nvAttribute1v1.m_nvAttributeDescriptor.m_nvAttributeName);

        TRACE_MSG("Deleting the last remaining attribute");
        attributesToDelete.push_back(nvAttribute1v1.m_nvAttributeDescriptor);
        iniFormatNvStore1->DeleteNvAttributes(nvContainer, attributesToDelete);

        TRACE_MSG("Checking that nvContainer contains no attributes");
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 0);

        TRACE_MSG("Adding back a couple of schema V1 attributes");
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeListV1);
        TRACE_MSG("Checking that nvContainer contains 2 attributes");
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 2);

        TRACE_MSG("Deleting attribute 1 inside a transaction");
        iniFormatNvStore1->StartNvTransaction();
        iniFormatNvStore1->DeleteNvAttributes(nvContainer, attributesToDelete);
        iniFormatNvStore1->EndNvTransaction();

        TRACE_MSG("Checking that nvContainer contains 1 attribute");
        names = iniFormatNvStore1->GetNvAttributeNames(nvContainer);
        CPPUNIT_ASSERT(names.size() == 1);
        CPPUNIT_ASSERT(names.at(0) == nvAttribute2v1.m_nvAttributeDescriptor.m_nvAttributeName);

        std::cout << *iniFormatNvStore1 << std::endl;

        // Test deleting an attribute when schema set to V2 then check still there in V3
        TRACE_MSG("Adding schema 3 attribute into schema 3");
        std::vector<NvAttribute> nvAttributeList;
        NvAttribute nvAttribute1v3B(NvAttributeDescriptor("attributeName1", 1), "70", 3);
        nvAttributeList.push_back(nvAttribute1v3B);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Adding schema 2 attribute into schema 2");
        nvAttributeList.clear();
        NvAttribute nvAttribute1v2B(NvAttributeDescriptor("attributeName1", 1), "69", 2);
        nvAttributeList.push_back(nvAttribute1v2B);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        TRACE_MSG("Checking attribute values");
        iniFormatNvStore1->GetNvAttribute(nvContainer, NvAttributeDescriptor("attributeName1", 1), savedValue);
        CPPUNIT_ASSERT(savedValue == "69");

        TRACE_MSG("Deleting attributeName1 while at schema 2");
        attributesToDelete.clear();
        attributesToDelete.push_back(NvAttributeDescriptor("attributeName1", 1));
        iniFormatNvStore1->DeleteNvAttributes(nvContainer, attributesToDelete);

        TRACE_MSG("Switching to schema 3");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V3);

        TRACE_MSG("Checking attribute values");
        NvAttributeResult result = iniFormatNvStore1->GetNvAttribute(nvContainer, NvAttributeDescriptor("attributeName1", 1), savedValue);
        CPPUNIT_ASSERT(result == NV_ATTRIBUTE_RESULT_OK);
        CPPUNIT_ASSERT(savedValue == "70");

        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Checking attribute values");
        CPPUNIT_ASSERT(iniFormatNvStore1->GetNvAttribute(nvContainer, NvAttributeDescriptor("attributeName1", 1), savedValue) == NV_ATTRIBUTE_RESULT_NO_SUCH_ATTRIBUTE);

        std::cout << *iniFormatNvStore1 << std::endl;

        // Check setting a value on an attribute when at schema V2 then change to
        // schema V3 and set value on same attribute but V3 version of it then go back
        // to V2 schema and check value unchanged.
        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Setting attributeName1 V2 attribute in schema 2");
        nvAttributeList.clear();
        NvAttribute nvAttribute1v2C(NvAttributeDescriptor("attributeName1", 1), "99", 2);
        nvAttributeList.push_back(nvAttribute1v2C);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        TRACE_MSG("Switching to schema 3");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V3);

        TRACE_MSG("Setting attributeName1 V3 attribute in schema 3");
        nvAttributeList.clear();
        NvAttribute nvAttribute1v3C(NvAttributeDescriptor("attributeName1", 1), "199", 3);
        nvAttributeList.push_back(nvAttribute1v3C);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Checking attribute values");
        CPPUNIT_ASSERT(iniFormatNvStore1->GetNvAttribute(nvContainer, NvAttributeDescriptor("attributeName1", 1), savedValue) == NV_ATTRIBUTE_RESULT_OK);
        CPPUNIT_ASSERT(savedValue == "99");

        std::cout << *iniFormatNvStore1 << std::endl;

        // Test setting a V1 attribute when we have a value written in V2 and V3 blocks and are at schema 2.
        // Check we delete it in the V2 block but leave V3 alone.
        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Setting checkOldStyleCleanUp V2 attribute in schema 2");
        nvAttributeList.clear();
        NvAttribute nvAttrCheckOldStyleDeletev2(NvAttributeDescriptor("checkOldStyleCleanUp", 0), "abc", 2);
        nvAttributeList.push_back(nvAttrCheckOldStyleDeletev2);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        TRACE_MSG("Switching to schema 3");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V3);

        TRACE_MSG("Setting checkOldStyleCleanUp V3 attribute in schema 3");
        nvAttributeList.clear();
        NvAttribute nvAttrCheckOldStyleDeletev3(NvAttributeDescriptor("checkOldStyleCleanUp", 0), "abcdef", 3);
        nvAttributeList.push_back(nvAttrCheckOldStyleDeletev3);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        TRACE_MSG("Switching to schema 2");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V2);

        TRACE_MSG("Setting checkOldStyleCleanUp V1 attribute in schema 2");
        nvAttributeList.clear();
        NvAttribute nvAttrCheckOldStyleDeletev1(NvAttributeDescriptor("checkOldStyleCleanUp", 0), "zxcv", 1);
        nvAttributeList.push_back(nvAttrCheckOldStyleDeletev1);
        iniFormatNvStore1->SetNvAttributes(nvContainer, nvAttributeList);

        std::cout << *iniFormatNvStore1 << std::endl;

        TRACE_MSG("Check we still have a value but have deleted it from V2 schema block and left value in V3 block untouched");
        CPPUNIT_ASSERT(iniFormatNvStore1->GetNvAttribute(nvContainer, NvAttributeDescriptor("checkOldStyleCleanUp", 0), savedValue) == NV_ATTRIBUTE_RESULT_OK);
        CPPUNIT_ASSERT(savedValue == "zxcv");

        TRACE_MSG("Switching to schema 3");
        iniFormatNvStore1->SetCurrentNvStoreSchemaVersion(SCHEMA_V3);

        TRACE_MSG("Check value at schema 3");
        CPPUNIT_ASSERT(iniFormatNvStore1->GetNvAttribute(nvContainer, NvAttributeDescriptor("checkOldStyleCleanUp", 0), savedValue) == NV_ATTRIBUTE_RESULT_OK);
        CPPUNIT_ASSERT(savedValue == "abcdef");


        // Clearing up after test
        TRACE_MSG("Deleting storage file");
        unlink(filename.c_str());

    }
};

#endif // __UpgradeNvStoreTests_h_
