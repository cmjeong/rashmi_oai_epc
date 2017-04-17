///////////////////////////////////////////////////////////////////////////////
//
// MibMessageTests.h
//
// MIB messaging API unit tests.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibMessageTests_h_
#define __MibMessageTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

#include <mib-common/messages/MibCreateObjectReq.h>
#include <mib-common/messages/MibCreateObjectCnf.h>
#include <mib-common/messages/MibDeleteObjectReq.h>
#include <mib-common/messages/MibDeleteObjectCnf.h>
#include <mib-common/messages/MibSetAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesDeleteInd.h>
#include <mib-common/messages/MibValidateAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <mib-common/MibObjectDeleteResult.h>

#include <MibObjectClass.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class MibMessageTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*****************" << endl
             << "Mib Message Tests" << endl
             << "*****************" << endl << endl;

        //
        // MibCreateObjectReq
        //
        TRACE_MSG("Testing MibCreateObjectReq without attributes");
        MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
        MibDN parentDn;
        parentDn.push_back(fapRdn);
        MibRDN childRdn(MIB_OBJECT_CLASS_FACTORY, 0);
        MibAttributeValues emptyChildAttributes;
        MibCreateObjectReq mibCreateObjectReq1(parentDn, childRdn, emptyChildAttributes);

        MibCreateObjectReq mibCreateObjectReqRxd1;
        TestSerialisation(mibCreateObjectReq1, mibCreateObjectReqRxd1);

        TRACE_MSG("Testing MibCreateObjectReq");
        MibAttributeValues childAttributes;
        childAttributes.AddAttribute(PARAM_ID_SERIAL_NUMBER, "Serial number baby");
        MibCreateObjectReq mibCreateObjectReq2(parentDn, childRdn, childAttributes);

        MibCreateObjectReq mibCreateObjectReqRxd2;
        TestSerialisation(mibCreateObjectReq2, mibCreateObjectReqRxd2);

        //
        // MibCreateObjectCnf
        //
        TRACE_MSG("Testing MibCreateObjectCnf");
        parentDn.push_back(childRdn);
        MibCreateObjectCnf mibCreateObjectCnf(parentDn);

        MibCreateObjectCnf mibCreateObjectCnfRxd;
        TestSerialisation(mibCreateObjectCnf, mibCreateObjectCnfRxd);

        //
        // MibDeleteObjectReq
        //
        TRACE_MSG("Testing MibDeleteObjectReq");
        MibRDN factoryRdn(MIB_OBJECT_CLASS_FACTORY, 0);
        MibDN factoryDn;
        factoryDn.push_back(fapRdn);
        factoryDn.push_back(factoryRdn);
        MibDeleteObjectReq mibDeleteObjectReq(factoryDn);
        CPPUNIT_ASSERT_MESSAGE("Check DN OK", mibDeleteObjectReq.GetDn() == factoryDn);

        MibDeleteObjectReq mibDeleteObjectReqRxd;
        TestSerialisation(mibDeleteObjectReq, mibDeleteObjectReqRxd);

        //
        // MibDeleteObjectCnf
        //
        TRACE_MSG("Testing MibDeleteObjectCnf");
        MibDeleteObjectCnf mibDeleteObjectCnf(factoryDn, MIB_OBJ_DEL_SUCCESS);

        MibDeleteObjectCnf mibDeleteObjectCnfRxd;
        TestSerialisation(mibDeleteObjectCnf, mibDeleteObjectCnfRxd);

        //
        // MibSetAttributesReq
        //
        TRACE_MSG("Testing MibSetAttributesReq");
        // Construct DN.
        MibRDN rdn(MIB_OBJECT_CLASS_TEST_MO, 3);
        MibDN dn;
        dn.push_back(rdn);
        // Construct MibAttributeValues and add attribute(s).
        MibAttributeValues attrValues;
        attrValues.AddAttribute(PARAM_ID_SOME_STRING, "Well hello there");
        attrValues.AddAttribute(PARAM_ID_DL_UARFCN, (u32)12345);
        attrValues.AddAttribute(PARAM_ID_TX_POWER_DBM, (s32)-12345);
        boost::shared_ptr<MibAttributeValue> aStringArrayValue(MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_STRINGARRAY, "string 1, string 2"));
        attrValues.AddAttribute(PARAM_ID_TEST_STRING_ARRAY, aStringArrayValue);
        MibSetAttributesReq mibSetAttributesReq(dn, attrValues);

        MibSetAttributesReq mibSetAttributesReqRxd;
        TestSerialisation(mibSetAttributesReq, mibSetAttributesReqRxd);

        //
        // MibSubscribeAttributesReq tests
        //
        TRACE_MSG("Testing MibSubscribeAttributesReq");
        MibAttributeIds attributeIds;
        attributeIds.insert(PARAM_ID_SOME_STRING);
        MibSubscribeAttributesReq subscribeAttributesReq(0x123, dn, attributeIds);

        MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
        MibObjectClasses objClasses;
        objClasses.insert(MIB_OBJECT_CLASS_COMMISSIONING);
        subscribeAttributesReq.AddObjectClasses(fapDn, objClasses);

        MibSubscribeAttributesReq subscribeAttributesReqRxd;
        TestSerialisation(subscribeAttributesReq, subscribeAttributesReqRxd);

        //
        // MibSubscribeAttributesDeleteInd tests
        //
        TRACE_MSG("Testing MibSubscribeAttributesDeleteInd");
        MibAttributeIds attributeIdsToDelete;
        attributeIdsToDelete.insert(PARAM_ID_SOME_STRING);
        MibAttributeIdsByDn mibAttributeIdsByDn;
        mibAttributeIdsByDn[dn] = attributeIdsToDelete;
        MibSubscribeAttributesDeleteInd subscribeAttributesDeleteInd(0x123, mibAttributeIdsByDn);

        MibSubscribeAttributesDeleteInd subscribeAttributesDeleteIndRxd;
        TestSerialisation(subscribeAttributesDeleteInd, subscribeAttributesDeleteIndRxd);

        //
        // MibValidateAttributesCnf
        //
        TRACE_MSG("Testing MibValidateAttributesReq");
        MibAttrValidationFailures failures;
        ValidationFailureDescriptor failureDesc;
        failureDesc.Set(ValidationFailureDescriptor::CAUSE_NOT_ALLOWED_ON_OBJECT, "yo!  whas up?");
        MibAttrValidationFailure failure(PARAM_ID_SOME_STRING, failureDesc);
        failures.push_back(failure);
        MibValidateAttributesCnf validateCnf(dn, failures);

        MibValidateAttributesCnf validateCnfRxd;
        TestSerialisation(validateCnf, validateCnfRxd);

        //
        // MibSubscribeAttributesInd
        //
        TRACE_MSG("Testing MibSubscribeAttributesInd");
        MibAttributeValuesByDn mibObjects;
        mibObjects[dn] =  attrValues;
        MibSubscribeAttributesInd mibSubscribeObjectsInd(10, mibObjects);

        MibSubscribeAttributesInd mibSubscribeObjectsIndRxd;
        TestSerialisation(mibSubscribeObjectsInd, mibSubscribeObjectsIndRxd);

        fflush(stdout);
    }

protected:

private:

    void TestSerialisation(const Serialisable& txMessage, Serialisable& rxMessage)
    {
        u8 serialisedData[2000];
        s32 serialisedLen;

        serialisedLen = txMessage.Serialise(serialisedData, sizeof(serialisedData));
        CPPUNIT_ASSERT_MESSAGE("Check serialised OK", serialisedLen > 0);

        // De-serialise it.
        bool success = rxMessage.DeSerialise(serialisedData, serialisedLen);
        CPPUNIT_ASSERT_MESSAGE("Checking de-serialised OK", success);

        // Compare.
        TRACE("txMessage", txMessage.ToString());
        TRACE("rxMessage", rxMessage.ToString());
        CPPUNIT_ASSERT_MESSAGE("Compare pre and post serialisation", txMessage.ToString() == rxMessage.ToString());
    }

};

#endif
