///////////////////////////////////////////////////////////////////////////////
//
// MibManagerTests.h
//
// Unit tests for MibManager.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibManagerTests_h_
#define __MibManagerTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <cstring>

#include <cppunit/TestCase.h>

#include <Radisys.h>

#include <mib-common/MibAttributeValues.h>
#include <mib-core/MibManager.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibManagerTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "****************" << endl
             << "MibManager tests" << endl
             << "****************" << endl << endl;

        bool asserted = false;

        TRACE_MSG("Construct a couple of RDNs");
        MibRDN fapRDN(MIB_OBJECT_CLASS_FAP, 0);
        MibDN rootDN;

        TRACE_MSG("Creating MibManager instance");
        MibManager manager(NULL);

        MibDN fapDN;
        fapDN.push_back(fapRDN);

        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            TRACE_MSG("Check MibManager::FindMibObject for root object before it has been added");
            boost::weak_ptr<MibObject> fapObjectWeak = manager.FindMibObject(fapDN);
        } catch(const Exception& e) {
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that ensure this object may be attached to this parent.", asserted == true);


        TRACE_MSG("Creating the root object in MibManger");
        manager.CreateObject(rootDN, fapRDN);

        TRACE_MSG("Check MibManager::FindMibObject for root object");
        boost::weak_ptr<MibObject> fapObjectWeak = manager.FindMibObject(fapDN);

        {
            boost::shared_ptr<MibObject> fapObject;
            TRACE_MSG("Getting shared_ptr to found object");
            CPPUNIT_ASSERT(fapObject = fapObjectWeak.lock());

            TRACE_MSG("Comparing the MibRDN values");
            CPPUNIT_ASSERT(fapObject->GetRDN() == fapRDN);

            TRACE("Comparing MibObject stringified value", fapObject->ToString());
            CPPUNIT_ASSERT(fapObject->ToString().compare("FAP.0:\n No Attributes\n No Children") == 0);
        }


        TRACE_MSG("Now trying a FindMibObject search for a non-root object")

        TRACE_MSG("Creating the non-root object in MibManger");
        MibRDN radioRDN(MIB_OBJECT_CLASS_RADIO, 0);
        manager.CreateObject(fapDN, radioRDN);

        MibDN radioDN;
        radioDN.push_back(fapRDN);
        radioDN.push_back(radioRDN);

        TRACE_MSG("Check MibManager::FindMibObject for non-root object");
        boost::weak_ptr<MibObject> radioObjectWeak = manager.FindMibObject(radioDN);

        {
            boost::shared_ptr<MibObject> radioObject;
            TRACE_MSG("Getting shared_ptr to found object");
            CPPUNIT_ASSERT(radioObject = radioObjectWeak.lock());

            TRACE_MSG("Comparing the MibRDN values");
            CPPUNIT_ASSERT(radioObject->GetDN() == radioDN);

            TRACE("Comparing MibObject stringified value", radioObject->ToString());
            CPPUNIT_ASSERT(radioObject->ToString().compare("FAP.0.RADIO.0:\n Attributes: DL_UARFCN=10800 \n No Children") == 0);
        }

        TRACE_MSG("Check MibManager::CreateObject with parent that doesn't specify this object");
        MibDN dn3(radioDN);
        MibRDN rdn3(MIB_OBJECT_CLASS_RADIO, 0);
        dn3.push_back(rdn3);

        asserted = false;
        Trace_SetAssertAbortDisabled(true);
        try {
            // Trying to create MibObject at incorrect place
            manager.CreateObject(radioDN, fapRDN);
        } catch(const Exception& e) {
            //CPPUNIT_ASSERT_MESSAGE("Check for correct assert condition.", std::strcmp(e.what(), "parentObjectClass != validParentClass") == 0);
            asserted = true;
        }
        Trace_SetAssertAbortDisabled(false);
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that this object may NOT be attached to this parent.", asserted == true);


    }

protected:

private:

};

#endif
