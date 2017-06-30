///////////////////////////////////////////////////////////////////////////////
//
// MibObjectTests.h
//
// Unit tests for MibObject class.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibObjectTests_h_
#define __MibObjectTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <system/Exception.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-core/MibObject.h>
#include <mib-core/IniFormatNvStore.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace boost;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class TestNvStore : public NonVolatileStoreInterface
{
    virtual bool InitialiseNvStore(bool forceReadOnly) {};
    virtual bool IsNvContainerPresent(const NvContainerDescriptor& nvContainerDescriptor) const { return true; };
    virtual std::vector<u32> GetNvContainerInstances(const NvContainerName& nvContainerName) const { std::vector<u32> vec; vec[0] = 1; return vec; };
    virtual bool IsNvAttributePresent(const NvContainerDescriptor& nvContainerDescriptor,
                              const NvAttributeName& nvAttributeName) const { return true; };
    virtual std::vector<u32> GetNvAttributeInstances(const NvContainerDescriptor& nvContainerDescriptor,
                                             const NvAttributeName& nvAttributeName) const { std::vector<u32> vec; vec[0] = 1; return vec; };
    virtual std::vector<NvAttributeName> GetNvAttributeNames(const NvContainerDescriptor& nvContainerDescriptor) const { std::vector<std::string> vec; vec[0] = "blah"; return vec; };
    virtual NvAttributeResult GetNvAttribute(const NvContainerDescriptor& nvContainerDescriptor,
                                     const NvAttributeDescriptor& nvAttributeDescriptor,
                                     NvAttributeValue& nvAttributeValue) const
    {
        if(nvAttributeDescriptor.m_nvAttributeName == "serialNumber")
        {
            nvAttributeValue.assign("serialnumber123");
        }
        return NV_ATTRIBUTE_RESULT_OK;
    };
    virtual void SetNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
                                 const std::vector<NvAttribute>& nvAttributes) {};
    virtual void DeleteNvAttributes(const NvContainerDescriptor& nvContainerDescriptor) {};
    virtual void DeleteNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
                                    const std::vector<NvAttributeDescriptor>& nvAttributeDescriptors) {};
    virtual void StartNvTransaction() {};
    virtual void EndNvTransaction() {};
    virtual void CancelNvTransaction() {};
    virtual void ForceNvFlush() {};

};

class MibObjectTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "MibObject tests" << endl
             << "***************" << endl << endl;

        std::string filename = "mibobjecttest.nv";
        std::string command = filename;

        // Create file with content...this is a bit nasty. Is there another way?
        {
            std::ofstream output(filename.c_str());
            output << "[[!1]]"                            << std::endl
                   << "[[@1]]"                            << std::endl
                   << "[TEST_MO/0]"                       << std::endl
                   << "SERIAL_NUMBER/0 = serialnumber123" << std::endl
                   << "[FAP.0.RADIO/0]"                   << std::endl
                   << "SOME_STRING/0 = somestring"        << std::endl
                   << "[FAP.0.RADIO/2]"                   << std::endl
                   << "DL_UARFCN/0 = 10700"               << std::endl;
            output.close();
        }

        //TestNvStore testNvStore;
        IniFormatNvStore testNvStore;
        testNvStore.SetStoreFileName(filename);
        testNvStore.InitialiseNvStore();

        TRACE_MSG("Create a test MO.");
        MibRDN mibRdn1(MIB_OBJECT_CLASS_TEST_MO, 0);
        shared_ptr<MibObject> testObject(new MibObject(mibRdn1, testNvStore));
        MibAttributeValues mibAttributeValues;
        mibAttributeValues.AddAttribute(PARAM_ID_SERIAL_NUMBER, "serialnumber123");
        testObject->InitialiseMO(mibAttributeValues);

        TRACE_MSG("Check MO overrid'able accessClass setting");
        CPPUNIT_ASSERT_MESSAGE("Check that the access class on the TEST_MO object is read write.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO, PARAM_ID_OVERRIDE_ACCESS_CLASS_READ_WRITE)->accessClass == MIB_ACCESS_READ_WRITE );
        CPPUNIT_ASSERT_MESSAGE("Check that the access class on the TEST_MO_OVERRIDE object is read only.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO_OVERRIDE, PARAM_ID_OVERRIDE_ACCESS_CLASS_READ_WRITE)->accessClass == MIB_ACCESS_READ_ONLY );
        CPPUNIT_ASSERT_MESSAGE("Check that the access class on the TEST_MO object is read only.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO, PARAM_ID_OVERRIDE_ACCESS_CLASS_READ_ONLY)->accessClass == MIB_ACCESS_READ_ONLY );
        CPPUNIT_ASSERT_MESSAGE("Check that the access class on the TEST_MO_OVERRIDE object is write once.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO_OVERRIDE, PARAM_ID_OVERRIDE_ACCESS_CLASS_READ_ONLY)->accessClass == MIB_ACCESS_WRITE_ONCE );
        CPPUNIT_ASSERT_MESSAGE("Check that the access class on the TEST_MO object is write once.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO, PARAM_ID_OVERRIDE_ACCESS_CLASS_WRITE_ONCE)->accessClass == MIB_ACCESS_WRITE_ONCE );
        CPPUNIT_ASSERT_MESSAGE("Check that the access class on the TEST_MO_OVERRIDE object is read write.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO_OVERRIDE, PARAM_ID_OVERRIDE_ACCESS_CLASS_WRITE_ONCE)->accessClass == MIB_ACCESS_READ_WRITE );

        TRACE_MSG("Check MO overrid'able storageClass setting");
        CPPUNIT_ASSERT_MESSAGE("Check that the storage class on the TEST_MO object is volatile.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO, PARAM_ID_OVERRIDE_STORAGE_CLASS_VOLATILE)->storageClass == MIB_STORAGE_VOLATILE );
        CPPUNIT_ASSERT_MESSAGE("Check that the storage class on the TEST_MO_OVERRIDE object is non-volatile.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO_OVERRIDE, PARAM_ID_OVERRIDE_STORAGE_CLASS_VOLATILE)->storageClass == MIB_STORAGE_NON_VOLATILE );
        CPPUNIT_ASSERT_MESSAGE("Check that the storage class on the TEST_MO object is non-volatile.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO, PARAM_ID_OVERRIDE_STORAGE_CLASS_NON_VOLATILE)->storageClass == MIB_STORAGE_NON_VOLATILE );
        CPPUNIT_ASSERT_MESSAGE("Check that the storage class on the TEST_MO_OVERRIDE object is volatile.",
            getMibObjectAttributeDescriptor(MIB_OBJECT_CLASS_TEST_MO_OVERRIDE, PARAM_ID_OVERRIDE_STORAGE_CLASS_NON_VOLATILE)->storageClass == MIB_STORAGE_VOLATILE );


        TRACE_MSG("Successfully add an attribute to it.");
        mibAttributeValues.AddAttribute(PARAM_ID_MCC, (u32)1234);
        testObject->SetMibAttributes(mibAttributeValues);
        TRACE_MSG("Erroneously add an invalid attribute to it.");
        mibAttributeValues.AddAttribute(PARAM_ID_MCC, (u32)1235);
        bool asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            testObject->SetMibAttributes(mibAttributeValues);
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be attached to this object.", asserted == true);
        TRACE_MSG("Erroneously add an implicitly disallowed attribute to it.");
        mibAttributeValues.AddAttribute(PARAM_ID_MNC, (u32)1234);
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            testObject->SetMibAttributes(mibAttributeValues);
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be attached to this object.", asserted == true);


        TRACE_MSG("Check GetMibAttributeValues() success case.");
        MibAttributeIds mibAttributeValueIdsToBeReturned;
        mibAttributeValueIdsToBeReturned.insert(PARAM_ID_SERIAL_NUMBER);
        mibAttributeValueIdsToBeReturned.insert(PARAM_ID_MCC);
        MibAttributeValues mibAttributeValuesReturned;
        testObject->GetMibAttributes(mibAttributeValueIdsToBeReturned, mibAttributeValuesReturned);
        CPPUNIT_ASSERT(mibAttributeValuesReturned.GetAttributeCount() == 2);
        std::string returnedSerialNumber;
        mibAttributeValuesReturned.GetAttributeValue(PARAM_ID_SERIAL_NUMBER, returnedSerialNumber);
        CPPUNIT_ASSERT(returnedSerialNumber == "serialnumber123");
        u32 returnedMcc;
        mibAttributeValuesReturned.GetAttributeValue(PARAM_ID_MCC, returnedMcc);
        CPPUNIT_ASSERT(returnedMcc == 1234);

        // Now do some edge case tests.
        TRACE_MSG("Check GetMibAttributeValues() edge cases.");
        mibAttributeValueIdsToBeReturned.insert(PARAM_ID_MNC);
        MibAttributeValues mibAttributeValuesReturned2;
        testObject->GetMibAttributes(mibAttributeValueIdsToBeReturned, mibAttributeValuesReturned2);
        CPPUNIT_ASSERT_MESSAGE("Check that we ignore the erroneous additional attribute that is requested.", mibAttributeValuesReturned2.GetAttributeCount() == 2);

        TRACE_MSG("Check ToString().");
        TRACE_PRINTF("%s", testObject->ToString().c_str());
        CPPUNIT_ASSERT(testObject->ToString().compare("TEST_MO.0:\n Attributes: SERIAL_NUMBER=\"serialnumber123\" MCC=1234 \n No Children") == 0);

        TRACE_MSG("Add a child object");
        MibRDN mibRdn2(MIB_OBJECT_CLASS_RADIO, 0);
        shared_ptr<MibObject> radioObject(new MibObject(mibRdn2, testNvStore));

        testObject->AddChildObject(radioObject);
        TRACE("testObject (with child)", testObject->ToString());
        CPPUNIT_ASSERT(testObject->ToString().compare("TEST_MO.0:\n Attributes: SERIAL_NUMBER=\"serialnumber123\" MCC=1234 \n Children: RADIO.0 ") == 0);

        MibDN checkDn;
        checkDn.push_back(mibRdn1);
        TRACE_PRINTF("Check DNs (%s) and RDN (%s) on Radio object",
                     radioObject->GetDN().ToString().c_str(),
                     radioObject->GetRDN().ToString().c_str());
        checkDn.push_back(mibRdn2);
        CPPUNIT_ASSERT(radioObject->GetDN() == checkDn);
        CPPUNIT_ASSERT(radioObject->GetRDN() == mibRdn2);

        TRACE_MSG("Add a valid child object...");
        MibRDN ncRdn0(MIB_OBJECT_CLASS_INTER_FREQ_NEIGHBOURS, 0);
        shared_ptr<MibObject> ncObject0(new MibObject(ncRdn0, testNvStore));
        testObject->AddChildObject(ncObject0);

        TRACE_MSG("...and then an invalid child object");
        MibRDN ncRdn2(MIB_OBJECT_CLASS_INTER_FREQ_NEIGHBOURS, 2);
        shared_ptr<MibObject> ncObject2(new MibObject(ncRdn2, testNvStore));

        Trace_SetAssertAbortDisabled(true);
        asserted = false;
        try {
            testObject->AddChildObject(ncObject2);
        } catch(const Exception& e) {
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this object is invalid.", asserted == true);

        // Try setting attribute using wrong type.
        Trace_SetAssertAbortDisabled(true);
        asserted = false;
        try {
            MibAttributeValues mibAttributeValuesDodgyType;
            mibAttributeValuesDodgyType.AddAttribute(PARAM_ID_MCC, (s32)0);
            testObject->SetMibAttributes(mibAttributeValuesDodgyType);
        } catch(const Exception& e) {
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute has the wrong type.", asserted == true);

        //
        // Check generation of NV container names
        //

        TRACE_MSG("Check generation of NV container names.");

        // FAP.0 > FAP, 0
        MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
        NvContainerDescriptor nvContainerDesc = MibObject::GetNvContainerDescriptor(fapDn);
        TRACE_PRINTF("FAP.0 (%s) > %s, %"PRIu32, fapDn.ToString().c_str(), nvContainerDesc.m_nvContainerName.c_str(), nvContainerDesc.m_nvContainerInstance);
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0 DN gives NV container name \"FAP\".", nvContainerDesc.m_nvContainerName == "FAP");
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0 DN gives NV container instance 0.", nvContainerDesc.m_nvContainerInstance == 0);

        // FAP.0.FACTORY.0 > FACTORY, 0
        MibDN factoryDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
        MibRDN factoryRdn(MIB_OBJECT_CLASS_FACTORY, 0);
        factoryDn.push_back(factoryRdn);
        nvContainerDesc = MibObject::GetNvContainerDescriptor(factoryDn);
        TRACE_PRINTF("FAP.0.FACTORY.0 (%s) > %s, %"PRIu32, factoryDn.ToString().c_str(), nvContainerDesc.m_nvContainerName.c_str(), nvContainerDesc.m_nvContainerInstance);
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0.FACTORY.0 DN gives NV container name \"FACTORY\".", nvContainerDesc.m_nvContainerName == "FACTORY");
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0.FACTORY.0 DN gives NV container instance 0.", nvContainerDesc.m_nvContainerInstance == 0);

        // FAP.0.TEST_MO.2 > FAP.0.TEST_MO, 2
        MibDN testMoDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
        MibRDN testMoRdn(MIB_OBJECT_CLASS_TEST_MO, 2);
        testMoDn.push_back(testMoRdn);
        nvContainerDesc = MibObject::GetNvContainerDescriptor(testMoDn);
        TRACE_PRINTF("FAP.0.TEST_MO.2 (%s) > %s, %"PRIu32, testMoDn.ToString().c_str(), nvContainerDesc.m_nvContainerName.c_str(), nvContainerDesc.m_nvContainerInstance);
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0.TEST_MO.2 DN gives NV container name \"FAP.0.TEST_MO\".", nvContainerDesc.m_nvContainerName == "FAP.0.TEST_MO");
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0.TEST_MO.2 DN gives NV container instance 2.", nvContainerDesc.m_nvContainerInstance == 2);

        //
        // Check auto-creation of child object based on NV contents.
        //
        Trace::GetInstance().SetTraceLevelOn(TRACE_VERBOSE);
        TRACE_MSG("Create a FAP MIB object that should auto create RADIO child objects.");
        std::cout << testNvStore << std::endl;
        MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
        shared_ptr<MibObject> fapObject(new MibObject(fapRdn, testNvStore));
        MibAttributeValues mibAttributeValuesEmpty;
        fapObject->InitialiseMO(mibAttributeValuesEmpty);

        // Now get FAP.0.RADIO.0 and FAP.0.RADIO.2 and confirm they exist and that DL_UARFCN
        // is 10800 (default) on .0 and 10700 (from NV) on .2
        {
        MibRDN radio0Rdn(MIB_OBJECT_CLASS_RADIO, 0);
        shared_ptr<MibObject> radio0 = fapObject->FindChildObject(radio0Rdn);
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0.RADIO.0 exists", radio0 != NULL);
        MibAttributeValues radio0Attribs;
        radio0->GetMibAttributes(radio0Attribs);
        CPPUNIT_ASSERT_MESSAGE("Check has DL_UARFCN", radio0Attribs.IsAttributePresent(PARAM_ID_DL_UARFCN));
        u32 radio0DlArfcn;
        radio0Attribs.GetAttributeValue(PARAM_ID_DL_UARFCN, radio0DlArfcn);
        CPPUNIT_ASSERT_MESSAGE("Check DL_UARFCN is 10800", radio0DlArfcn == 10800);
        }

        {
        MibRDN radio2Rdn(MIB_OBJECT_CLASS_RADIO, 2);
        shared_ptr<MibObject> radio2 = fapObject->FindChildObject(radio2Rdn);
        CPPUNIT_ASSERT_MESSAGE("Check FAP.0.RADIO.2 exists", radio2 != NULL);
        MibAttributeValues radio2Attribs;
        radio2->GetMibAttributes(radio2Attribs);
        CPPUNIT_ASSERT_MESSAGE("Check has DL_UARFCN", radio2Attribs.IsAttributePresent(PARAM_ID_DL_UARFCN));
        u32 radio0DlArfcn;
        radio2Attribs.GetAttributeValue(PARAM_ID_DL_UARFCN, radio0DlArfcn);
        CPPUNIT_ASSERT_MESSAGE("Check DL_UARFCN is 10800", radio0DlArfcn == 10700);
        }

        // Clearing up previous test
        TRACE_MSG("Deleting old storage file");
        system(command.insert(0,"rm -f ").c_str());


        fflush(stdout);
    }

protected:

private:

};


#endif
