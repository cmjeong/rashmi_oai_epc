///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeTests.h
//
// Unit tests for MibAttribute and derived classes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributeTests_h_
#define __MibAttributeTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <limits>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <system/Exception.h>

#include <MibAttributes.h>
#include <mib-common/MibAttributeValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttribute.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class BasicMibAttributeTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "******************" << endl
             << "MibAttribute tests" << endl
             << "******************" << endl << endl;

        TRACE_MSG("Check a String attribute.");
        shared_ptr<MibAttributeValue> serialNumFalseValue(new MibAttributeValueString("12345678901234567890"));
        shared_ptr<MibAttributeValue> serialNumValue(new MibAttributeValueString("1234"));
        TRACE_MSG("Checking String ValidateValue");
        MibAttrValidationFailure failureDescriptor;
        CPPUNIT_ASSERT_MESSAGE("Check attribute validation", not(MibAttribute::ValidateValue(PARAM_ID_SERIAL_NUMBER, serialNumFalseValue, failureDescriptor)));
        CPPUNIT_ASSERT_MESSAGE("Check attribute validation", MibAttribute::ValidateValue(PARAM_ID_SERIAL_NUMBER, serialNumValue, failureDescriptor));

        MibAttribute mibAttrString(PARAM_ID_SERIAL_NUMBER, serialNumValue);
        CPPUNIT_ASSERT(mibAttrString.GetMibAttributeId() == PARAM_ID_SERIAL_NUMBER);
        CPPUNIT_ASSERT(mibAttrString.GetValue()->GetValueString() == "1234");

        TRACE_MSG("Check a String attribute asserts when we attempt to get a StringArray from it.");
        bool asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrString.GetValue()->GetValueStringArray();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a StringArray.", asserted == true);

        TRACE_MSG("Check a String attribute asserts when we attempt to get a S32 from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrString.GetValue()->GetValueS32();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a S32.", asserted == true);

        TRACE_MSG("Check a String attribute asserts when we attempt to get a U32 from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrString.GetValue()->GetValueU32();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a U32.", asserted == true);

        TRACE_MSG("Checking String PopulateWithValue().");
        MibAttributeValues mibAttributeStringValues;
        mibAttrString.PopulateWithValue(mibAttributeStringValues);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert String attribute into list", mibAttributeStringValues.GetAttributeCount() == 1);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct ID into list", mibAttributeStringValues.IsAttributePresent(mibAttrString.GetMibAttributeId()));
        std::string populatedStringValue;
        mibAttributeStringValues.GetAttributeValue(mibAttrString.GetMibAttributeId(), populatedStringValue);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct value into list", mibAttrString.GetValue()->GetValueString() == populatedStringValue);

        TRACE_MSG("Check a StringArray attribute.");
        std::vector<std::string> stringArrayValuesReturned;
        std::vector<std::string> stringArrayFalseValues;
        std::string stringFalseValueString1("12345678");
        std::string stringFalseValueString2("12345678901234567890");
        std::string stringFalseValueString3("1");
        stringArrayFalseValues.push_back(stringFalseValueString1);
        stringArrayFalseValues.push_back(stringFalseValueString2);
        stringArrayFalseValues.push_back(stringFalseValueString3);
        shared_ptr<MibAttributeValue> stringArrayFalseValue(new MibAttributeValueStringArray(stringArrayFalseValues));
        std::vector<std::string> stringArrayValues;
        std::string stringValueString1("123456");
        std::string stringValueString2("234567");
        stringArrayValues.push_back(stringValueString1);
        stringArrayValues.push_back(stringValueString2);
        shared_ptr<MibAttributeValue> testStringArrayValue(new MibAttributeValueStringArray(stringArrayValues));

        TRACE_MSG("Checking StringArray ValidateValue");
        CPPUNIT_ASSERT_MESSAGE("Check attribute validation", not(MibAttribute::ValidateValue(PARAM_ID_TEST_STRING_ARRAY, stringArrayFalseValue, failureDescriptor)));
        CPPUNIT_ASSERT_MESSAGE("Check attribute validation", MibAttribute::ValidateValue(PARAM_ID_TEST_STRING_ARRAY, testStringArrayValue, failureDescriptor));

        MibAttribute mibAttrStringArray(PARAM_ID_TEST_STRING_ARRAY, testStringArrayValue);
        CPPUNIT_ASSERT(mibAttrStringArray.GetMibAttributeId() == PARAM_ID_TEST_STRING_ARRAY);
        stringArrayValuesReturned = mibAttrStringArray.GetValue()->GetValueStringArray();
        CPPUNIT_ASSERT(stringArrayValuesReturned.size() == 2);
        CPPUNIT_ASSERT(stringArrayValuesReturned[0] == stringValueString1);
        CPPUNIT_ASSERT(stringArrayValuesReturned[1] == stringValueString2);

        TRACE_MSG("Check a StringArray attribute asserts when we attempt to get a String from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrStringArray.GetValue()->GetValueString();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a String.", asserted == true);

        TRACE_MSG("Check a StringArray attribute asserts when we attempt to get a S32 from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrStringArray.GetValue()->GetValueS32();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a S32.", asserted == true);

        TRACE_MSG("Check a StringArray attribute asserts when we attempt to get a U32 from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrStringArray.GetValue()->GetValueU32();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a U32.", asserted == true);

        TRACE_MSG("Checking StringArray PopulateWithValue().");
        MibAttributeValues mibAttributeStringArrayValues;
        mibAttrStringArray.PopulateWithValue(mibAttributeStringArrayValues);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert StringArray attribute into list", mibAttributeStringArrayValues.GetAttributeCount() == 1);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct ID into list", mibAttributeStringArrayValues.IsAttributePresent(mibAttrStringArray.GetMibAttributeId()));
        std::vector<std::string> populatedStringArrayValue;
        mibAttributeStringArrayValues.GetAttributeValue(mibAttrStringArray.GetMibAttributeId(), populatedStringArrayValue);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct value into list", mibAttrStringArray.GetValue()->GetValueStringArray() == populatedStringArrayValue);

        std::vector<std::string> populatedStringArrayValueReturned = mibAttrStringArray.GetValue()->GetValueStringArray();
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct value into list", populatedStringArrayValueReturned.size() == 2);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct value into list", populatedStringArrayValueReturned[0] == stringValueString1);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct value into list", populatedStringArrayValueReturned[1] == stringValueString2);


        TRACE_MSG("Check a U32 attribute.");
        shared_ptr<MibAttributeValue> mccValue(new MibAttributeValueU32(123));
        MibAttribute mibAttrU32(PARAM_ID_MCC, mccValue);
        CPPUNIT_ASSERT(mibAttrU32.GetMibAttributeId() == PARAM_ID_MCC);
        CPPUNIT_ASSERT(mibAttrU32.GetValue()->GetValueU32() == 123);

        TRACE_MSG("Check a U32 attribute asserts when we attempt to get a String from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrU32.GetValue()->GetValueString();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a string.", asserted == true);

        TRACE_MSG("Check a U32 attribute asserts when we attempt to get a StringArray from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrU32.GetValue()->GetValueStringArray();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a StringArray.", asserted == true);

        TRACE_MSG("Check a U32 attribute asserts when we attempt to get a S32 from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrU32.GetValue()->GetValueS32();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a S32.", asserted == true);

        TRACE_MSG("Checking U32 PopulateWithValue().");
        MibAttributeValues mibAttributeU32Values;
        mibAttrU32.PopulateWithValue(mibAttributeU32Values);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert U32 attribute into list", mibAttributeU32Values.GetAttributeCount() == 1);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct ID into list", mibAttributeU32Values.IsAttributePresent(mibAttrU32.GetMibAttributeId()));
        u32 populatedU32Value;
        mibAttributeU32Values.GetAttributeValue(mibAttrU32.GetMibAttributeId(), populatedU32Value);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct value into list", mibAttrU32.GetValue()->GetValueU32() == populatedU32Value);

        TRACE_MSG("Check a S32 attribute.");
        shared_ptr<MibAttributeValue> powerValue(new MibAttributeValueS32(5));
        MibAttribute mibAttrS32(PARAM_ID_TX_POWER_DBM, powerValue);
        CPPUNIT_ASSERT(mibAttrS32.GetMibAttributeId() == PARAM_ID_TX_POWER_DBM);
        CPPUNIT_ASSERT(mibAttrS32.GetValue()->GetValueS32() == 5);

        TRACE_MSG("Check a S32 attribute asserts when we attempt to get a U32 from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrS32.GetValue()->GetValueU32();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a S32.", asserted == true);

        TRACE_MSG("Check a S32 attribute asserts when we attempt to get a String from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrS32.GetValue()->GetValueString();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a string.", asserted == true);

        TRACE_MSG("Check a S32 attribute asserts when we attempt to get a StringArray from it.");
        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            mibAttrS32.GetValue()->GetValueStringArray();
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert message.", std::strcmp(e.what(), "MNC:NotAllowedOnObject: Attribute MNC not allowed on MO TEST_MO.0") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this attribute may NOT be retrieved as a StringArray.", asserted == true);

        TRACE_MSG("Checking S32 PopulateWithValue().");
        MibAttributeValues mibAttributeS32Values;
        mibAttrS32.PopulateWithValue(mibAttributeS32Values);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert S32 attribute into list", mibAttributeS32Values.GetAttributeCount() == 1);
        CPPUNIT_ASSERT_MESSAGE("Failed to insert correct ID into list", mibAttributeS32Values.IsAttributePresent(mibAttrS32.GetMibAttributeId()));
        s32 populatedS32Value;
        mibAttributeS32Values.GetAttributeValue(mibAttrS32.GetMibAttributeId(), populatedS32Value);
        CPPUNIT_ASSERT_MESSAGE("Failed to into correct value into list", mibAttrS32.GetValue()->GetValueS32() == populatedS32Value);

        shared_ptr<MibAttributeValue> serialNumValue2(new MibAttributeValueString(""));
        MibAttribute mibAttrString2(PARAM_ID_SERIAL_NUMBER, serialNumValue2);
        shared_ptr<MibAttributeValue> txPower(new MibAttributeValueS32(0));
        MibAttribute mibAttrS32_2(PARAM_ID_TX_POWER_DBM2, txPower);

        TRACE_MSG("Checking String IsValueEqual().");
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different types", not(mibAttrString.IsValueEqual(mibAttrU32_2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different types", not(mibAttrString.IsValueEqual(mibAttrS32_2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different values", not(mibAttrString.IsValueEqual(mibAttrString2)));
        MibAttribute mibAttrString3(PARAM_ID_SERIAL_NUMBER, serialNumValue2);
        CPPUNIT_ASSERT_MESSAGE("Failed to compare identical values", mibAttrString2.IsValueEqual(mibAttrString3));

        TRACE_MSG("Checking U32 IsValueEqual().");
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different types", not(mibAttrU32_2.IsValueEqual(mibAttrString2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different types", not(mibAttrU32_2.IsValueEqual(mibAttrS32_2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different values", not(mibAttrU32.IsValueEqual(mibAttrU32_2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare identical values", mibAttrU32_2.IsValueEqual(mibAttrU32_3));

        TRACE_MSG("Checking S32 IsValueEqual().");
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different types", not(mibAttrS32_2.IsValueEqual(mibAttrString2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different types", not(mibAttrS32_2.IsValueEqual(mibAttrU32_2)));
        CPPUNIT_ASSERT_MESSAGE("Failed to compare different values", not(mibAttrS32.IsValueEqual(mibAttrS32_2)));
        MibAttribute mibAttrS32_3(PARAM_ID_TX_POWER_DBM2, txPower);
        CPPUNIT_ASSERT_MESSAGE("Failed to compare identical values", mibAttrS32_2.IsValueEqual(mibAttrS32_3));


        TRACE_MSG("Check a DownlinkUArfcn attribute.");
        shared_ptr<MibAttributeValue> dlUArfcn(new MibAttributeValueU32(412));
        MibAttribute mibAttr4(PARAM_ID_DL_UARFCN, dlUArfcn);
        CPPUNIT_ASSERT(mibAttr4.GetMibAttributeId() == PARAM_ID_DL_UARFCN);
        CPPUNIT_ASSERT(mibAttr4.GetValue()->GetValueU32() == 412);

        TRACE_MSG("Checking an enumeration.");
        shared_ptr<MibAttributeValue> opStateValue(new MibAttributeValueU32(MIB_ATTR_OP_STATE_ENABLED));
        MibAttribute mibAttr5(PARAM_ID_OP_STATE, opStateValue);

        fflush(stdout);
    }

protected:

private:

};

#endif
