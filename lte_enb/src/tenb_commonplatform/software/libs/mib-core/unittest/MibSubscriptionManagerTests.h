///////////////////////////////////////////////////////////////////////////////
//
// MibSubscriptionManagerTests.h
//
// Unit tests for MibSubscriptionManager.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSubscriptionManagerTests_h_
#define __MibSubscriptionManagerTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

#include <mib-core/MibSubscriptionManager.h>

#include <MibManagedObjects.h>
#include <MibAttributes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const u32 SUBSCRIBER_ID_1 = 1;
static const u32 SUBSCRIPTION_ID_1 = 2;

static const u32 SUBSCRIBER_ID_2 = 7;
static const u32 SUBSCRIPTION_ID_2 = 8;

static const u32 SUBSCRIBER_ID_3 = 1;
static const u32 SUBSCRIPTION_ID_3 = 3;

static const u32 SUBSCRIBER_ID_4 = 1;
static const u32 SUBSCRIPTION_ID_4 = 4;

static const u32 SUBSCRIBER_ID_5 = 5;
static const u32 SUBSCRIPTION_ID_5 = 5;


///////////////////////////////////////////////////////////////////////////////
// Support Classes
///////////////////////////////////////////////////////////////////////////////

class TestSubClient : public MibSubscriptionNotifyInterface, public MibInterface
{
public:
    TestSubClient() :
        m_notifyCount(0),
        m_deleteNotifyCount(0),
        m_getCount(0)
    {
    }

    virtual void SendSubscriptionNotification(
            u32 subscriberId,
            u32 subscriptionId,
            const MibAttributeValuesByDn & changedMibAttributeValuesByDn)
    {
        CPPUNIT_ASSERT_MESSAGE("SendObjectSubscriptionNotification with no objects!", (changedMibAttributeValuesByDn.size() > 0));

        cout << "SendObjectSubscriptionNotification(#"<< m_notifyCount << ")\n"
             << "\tsubscriberId=" << subscriberId << "\n"
             << "\tsubscriptionId=" << subscriptionId << "\n"
             << endl;

        for(MibAttributeValuesByDn::const_iterator i = changedMibAttributeValuesByDn.begin();
            i != changedMibAttributeValuesByDn.end();
            i++ )
        {
            MibDN dn = i->first;
            MibAttributeValues changedAttributeValues = i->second;

            TRACE_PRINTF("SendSubscriptionNotification: count=%"PRIu32", subscriberId=%"PRIu32", subscriptionId=%"PRIu32", dn=%s, mibAttributeValues=%s",
                         m_notifyCount, subscriberId, subscriptionId,
                         dn.ToString().c_str(), changedAttributeValues.ToString().c_str());

            CPPUNIT_ASSERT(dn.size() == 1 || dn.size() == 2);
            CPPUNIT_ASSERT(dn.at(0).GetMibObjectClass() == MIB_OBJECT_CLASS_FAP);
            CPPUNIT_ASSERT(dn.at(0).GetMibObjectInstance() == 0);
            if(dn.size() > 1)
            {
                if(dn.at(1).GetMibObjectClass() == MIB_OBJECT_CLASS_FACTORY)
                {
                    CPPUNIT_ASSERT(dn.at(1).GetMibObjectInstance() == 0);
                }
                else if(dn.at(1).GetMibObjectClass() == MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS)
                {
                    CPPUNIT_ASSERT(dn.at(1).GetMibObjectInstance() < 2);
                }
            }

            switch(m_notifyCount)
            {
            case 0:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_1);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_1);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("MCC=124 ") == 0);
                break;

            case 1:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_1);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_1);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("MCC=124 MNC=33 ") == 0);
                break;

            case 2:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_3);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_3);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("MCC=124 ") == 0);
                break;

            case 3:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_3);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_3);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("SERIAL_NUMBER=\"SerialNumber1234\" MCC=124 ") == 0);
                break;

            case 4:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_2);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_2);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("SERIAL_NUMBER=\"SerialNumber1234\" ") == 0);
                break;

            case 5:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_4);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_4);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("SERIAL_NUMBER=\"SerialNumber9999\" ") == 0);
                break;

            case 6:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_1);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_1);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("MCC=125 MNC=33 ") == 0);
                break;

            case 7:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_3);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_3);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("SERIAL_NUMBER=\"SerialNumber1235\" MCC=125 ") == 0);
                break;

            case 8:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_2);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_2);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("SERIAL_NUMBER=\"SerialNumber1235\" ") == 0);
                break;

            case 9:
                CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_5);
                CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_1);
                CPPUNIT_ASSERT(changedAttributeValues.ToString().compare("MCC=127 MNC=23 ") == 0);
                break;

            }
        }

        m_notifyCount++;
    }

    virtual void SendSubscriptionDeleteNotification(u32 subscriberId, u32 subscriptionId,
                                                    const MibAttributeIdsByDn& deletedAttributeIdsByDn)
    {
        CPPUNIT_ASSERT(deletedAttributeIdsByDn.size() == 1);

        const MibDN & dn = deletedAttributeIdsByDn.begin()->first;
        const MibAttributeIds & deletedAttributeIds = deletedAttributeIdsByDn.begin()->second;

        TRACE_PRINTF("SendSubscriptionDeleteNotification: count=%"PRIu32", subscriberId=%"PRIu32", subscriptionId=%"PRIu32", dn=%s, deletedAttributeIds=%s",
                     m_notifyCount, subscriberId, subscriptionId,
                     dn.ToString().c_str(), deletedAttributeIds.ToString().c_str());

        CPPUNIT_ASSERT(dn.size() == 1 || dn.size() == 2);
        CPPUNIT_ASSERT(dn.at(0).GetMibObjectClass() == MIB_OBJECT_CLASS_FAP);
        CPPUNIT_ASSERT(dn.at(0).GetMibObjectInstance() == 0);
        if(dn.size() > 1)
        {
            CPPUNIT_ASSERT(dn.at(1).GetMibObjectClass() == MIB_OBJECT_CLASS_FACTORY || dn.at(1).GetMibObjectClass() == MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS);
            CPPUNIT_ASSERT(dn.at(1).GetMibObjectInstance() == 0);
        }

        switch(m_deleteNotifyCount)
        {
        case 0:
            CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_1);
            CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_1);
            CPPUNIT_ASSERT(deletedAttributeIds.ToString().compare("MCC ") == 0);
            break;
        case 1:
            CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_3);
            CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_3);
            CPPUNIT_ASSERT(deletedAttributeIds.ToString().compare("MCC ") == 0);
            break;
        case 2:
            CPPUNIT_ASSERT(subscriberId == SUBSCRIBER_ID_5);
            CPPUNIT_ASSERT(subscriptionId == SUBSCRIPTION_ID_1);
            CPPUNIT_ASSERT(deletedAttributeIds.ToString().empty());
            break;
        }

        m_deleteNotifyCount++;
    }

    virtual void SendSubscriptionDeleteNotification(
            u32 subscriberId,
            u32 subscriptionId,
            const vector<MibDN> & objects)
    {
        cout << "SendObjectSubscriptionDeleteNotification()\n"
             << "\tsubscriberId" << subscriberId << "\n"
             << "\tsubscriptionId" << subscriptionId << "\n"
             << endl;
    }

    virtual void CreateObject(const MibDN& parent, const MibRDN & childRdn)
    {
        // Used here only for dynamic object creation
        // i.e. MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS
        CPPUNIT_ASSERT(parent.size() == 1);
        CPPUNIT_ASSERT(parent.at(0).GetMibObjectClass() == MIB_OBJECT_CLASS_FAP);
        CPPUNIT_ASSERT(parent.at(0).GetMibObjectInstance() == 0);

        CPPUNIT_ASSERT(childRdn.GetMibObjectClass() == MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS);

        MibAttributeValues::MibAttributeValuesById empty;

        m_interRatNeighbourAttributes[childRdn.GetMibObjectInstance()] = empty;
    };


    virtual void CreateObject(const MibDN& parent, const MibRDN & childRdn, const MibAttributeValues& attributeValues) { };
    virtual MibObjectDeleteResult DeleteObject(const MibDN& dnToDelete)
    {
        CPPUNIT_ASSERT(dnToDelete.size() == 2);
        CPPUNIT_ASSERT(dnToDelete.at(0).GetMibObjectClass() == MIB_OBJECT_CLASS_FAP);
        CPPUNIT_ASSERT(dnToDelete.at(0).GetMibObjectInstance() == 0);
        CPPUNIT_ASSERT(dnToDelete.at(1).GetMibObjectClass() == MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS);

        m_interRatNeighbourAttributes.erase( dnToDelete.at(1).GetMibObjectInstance() );

        return MIB_OBJ_DEL_SUCCESS;
    }
    virtual boost::weak_ptr<MibObject> FindMibObject(const MibDN& dn) const { boost::weak_ptr<MibObject> mibObject; return mibObject; };
    virtual MibAttrValidationFailures ValidateAttributes(const MibDN& moDn, const MibAttributeValues& attributeValues, bool checkAccessClass) const { MibAttrValidationFailures failures; return failures; };

    virtual void SetAttributes(const MibDN& moDn, const MibAttributeValues& attributeValues, bool forced = false )
    {
        MibAttributeValues::MibAttributeValuesById attrs = attributeValues.GetAttributeValues();
        MibAttributeValues::MibAttributeValuesById::const_iterator attrsIter = attrs.begin();
        while(attrsIter != attrs.end())
        {
            TRACE_PRINTF("SetAttributes: %s", attrsIter->second->ToString().c_str());

            if(moDn.size() == 1)
            {
                m_fapAttributes[attrsIter->first] = attrsIter->second;
            }
            else if(moDn.size() == 2)
            {
                switch( moDn.at(1).GetMibObjectClass() )
                {
                    case MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS:
                    {
                        u32 instance = moDn.at(1).GetMibObjectInstance();
                        bool objectInExistence = m_interRatNeighbourAttributes.find(instance) != m_interRatNeighbourAttributes.end();

                        CPPUNIT_ASSERT(objectInExistence);

                        m_interRatNeighbourAttributes[instance][attrsIter->first] = attrsIter->second;
                    }
                    break;

                    case MIB_OBJECT_CLASS_FACTORY:
                        m_factoryAttributes[attrsIter->first] = attrsIter->second;
                        break;

                    default:
                        CPPUNIT_ASSERT_MESSAGE(false, "Unexpected Object class");
                }

            }
            else
            {
                CPPUNIT_ASSERT_MESSAGE(false, "Unexpected DN");
            }
            ++attrsIter;
        }
    };

    virtual void GetAttributes(const MibDN& moDn,
                               const MibAttributeIds& attributeIds,
                               MibAttributeValues& mibAttributeValues) const
    {
        cout << "GetAttributes(" << moDn.ToString() << ")\n"
             << endl;

        MibAttributeIds::const_iterator idsIter = attributeIds.begin();
        while(idsIter != attributeIds.end())
        {
            if(moDn.size() == 1)
            {
                map< MibAttributeId, shared_ptr<MibAttributeValue> >::const_iterator attrsIter = m_fapAttributes.find(*idsIter);
                if(attrsIter != m_fapAttributes.end())
                {
                    mibAttributeValues.AddAttribute(*idsIter, attrsIter->second);
                }
            }
            else if(moDn.size() == 2)
            {
                switch( moDn.at(1).GetMibObjectClass() )
                {
                    case MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS:
                    {

                        u32 instance = moDn.at(1).GetMibObjectInstance();
                        bool objectInExistence = (m_interRatNeighbourAttributes.find(instance) != m_interRatNeighbourAttributes.end());

                        CPPUNIT_ASSERT_MESSAGE("Object not created yet?", objectInExistence);

                        const MibAttributeValues::MibAttributeValuesById & mavbi = m_interRatNeighbourAttributes.at(instance);

                        map< MibAttributeId, shared_ptr<MibAttributeValue> >::const_iterator attrsIter = mavbi.find(*idsIter);
                        if(attrsIter != mavbi.end())
                        {
                            mibAttributeValues.AddAttribute(*idsIter, attrsIter->second);
                        }
                    }
                    break;

                    case MIB_OBJECT_CLASS_FACTORY:
                    {
                        map< MibAttributeId, shared_ptr<MibAttributeValue> >::const_iterator attrsIter = m_factoryAttributes.find(*idsIter);
                        if(attrsIter != m_factoryAttributes.end())
                        {
                            mibAttributeValues.AddAttribute(*idsIter, attrsIter->second);
                        }
                    }
                    break;

                    default:
                        CPPUNIT_ASSERT_MESSAGE( "Unexpected Object class", false);
                }

            }
            else
            {
                CPPUNIT_ASSERT_MESSAGE(false, "Unexpected DN");
            }

            ++idsIter;
        }

        TRACE_PRINTF("GetAttributes: call#=%"PRIu32", dn=%s, attr(%"PRIu32")=%s",
                     m_getCount, moDn.ToString().c_str(), mibAttributeValues.GetAttributeCount(), mibAttributeValues.ToString().c_str() );

        m_getCount++;
    }

    virtual void DeleteAttributes(const MibDN& moDn,
                                  const MibAttributeIds& attributeIds)
    {
        TRACE_PRINTF("DeleteAttributes: %s: %s", moDn.ToString().c_str(), attributeIds.ToString().c_str());

        for(MibAttributeIds::const_iterator attrIdsIter = attributeIds.begin();
            attrIdsIter != attributeIds.end();
            ++attrIdsIter)
        {

            if(moDn.size() == 1)
            {
                m_fapAttributes.erase(*attrIdsIter);
            }
            else
            {
                m_factoryAttributes.erase(*attrIdsIter);
            }
        }
    }

    MibAttributeValues::MibAttributeValuesById m_fapAttributes;
    MibAttributeValues::MibAttributeValuesById m_factoryAttributes;
    map< u32 /* instance */, MibAttributeValues::MibAttributeValuesById> m_interRatNeighbourAttributes;

    u32 m_notifyCount;
    u32 m_deleteNotifyCount;
    mutable u32 m_getCount;

};

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class MibSubscriptionManagerTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "****************************" << endl
             << "MibSubscriptionManager tests" << endl
             << "****************************" << endl << endl;

        // TODO: Provide some progress info for the test using TRACE macros...
        TRACE_MSG("Constructing instance of MibSubscriptionManager...");
        TestSubClient testSubClient;
        MibSubscriptionManager mibSubscriptionManager(testSubClient, testSubClient);

        MibAttributeIds      mibAttributeIds;
        MibAttributeIdsByDn  mibAttributeIdsByDn;
        MibObjectClasses     mibObjectClasses;
        MibObjectClassesByDn mibObjectClassesByDn;

        MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
        MibDN dn;
        dn.push_back(fapRdn);

        MibDN factoryDn;
        MibRDN factoryRdn(MIB_OBJECT_CLASS_FACTORY, 0);
        factoryDn.push_back(fapRdn);
        factoryDn.push_back(factoryRdn);

        TRACE_MSG("Setting MCC on FAP.0");
        MibAttributeValues attrs1;
        attrs1.AddAttribute(PARAM_ID_MCC, (u32)124);
        testSubClient.SetAttributes(dn, attrs1);
        MibAttributeIds changedAttributeIds1;
        changedAttributeIds1.insert(PARAM_ID_MCC);
        mibSubscriptionManager.HandleChangedAttributes(dn, changedAttributeIds1);

        TRACE_PRINTF("Adding subscription %"PRIu32"/%"PRIu32" for MCC and MNC.  Should trigger a subscription notify.", SUBSCRIBER_ID_1, SUBSCRIPTION_ID_1);
        mibAttributeIds.clear();
        mibAttributeIdsByDn.clear();
        mibObjectClassesByDn.clear();
        mibAttributeIds.insert(PARAM_ID_MCC);
        mibAttributeIds.insert(PARAM_ID_MNC);
        mibAttributeIdsByDn[dn] = mibAttributeIds;
        mibSubscriptionManager.AddSubscription(SUBSCRIBER_ID_1, "sub1", SUBSCRIPTION_ID_1, mibAttributeIdsByDn, mibObjectClassesByDn);

        TRACE_MSG("Setting MNC on FAP.0 ... should trigger a subscription notify");
        MibAttributeValues attrs2;
        attrs2.AddAttribute(PARAM_ID_MNC, (u32)33);
        testSubClient.SetAttributes(dn, attrs2);
        MibAttributeIds changedAttributeIds2;
        changedAttributeIds2.insert(PARAM_ID_MNC);
        mibSubscriptionManager.HandleChangedAttributes(dn, changedAttributeIds2);

        TRACE_PRINTF("Adding subscription %"PRIu32"/%"PRIu32" for SERIAL_NUMBER.  Won't trigger a subscription as SERIAL_NUMBER not in MIB yet.", SUBSCRIBER_ID_2, SUBSCRIPTION_ID_2);
        mibAttributeIds.clear();
        mibAttributeIdsByDn.clear();
        mibObjectClassesByDn.clear();
        mibAttributeIds.insert(PARAM_ID_SERIAL_NUMBER);
        mibAttributeIdsByDn[dn] = mibAttributeIds;
        mibSubscriptionManager.AddSubscription(SUBSCRIBER_ID_2, "sub2", SUBSCRIPTION_ID_2, mibAttributeIdsByDn, mibObjectClassesByDn);

        TRACE_PRINTF("Adding subscription %"PRIu32"/%"PRIu32" for SERIAL_NUMBER and MCC.  Will trigger a subscription as MCC is in MIB.", SUBSCRIBER_ID_3, SUBSCRIPTION_ID_3);
        mibAttributeIds.clear();
        mibAttributeIdsByDn.clear();
        mibObjectClassesByDn.clear();
        mibAttributeIds.insert(PARAM_ID_SERIAL_NUMBER);
        mibAttributeIds.insert(PARAM_ID_MCC);
        mibAttributeIdsByDn[dn] = mibAttributeIds;
        mibSubscriptionManager.AddSubscription(SUBSCRIBER_ID_3, "sub3", SUBSCRIPTION_ID_3, mibAttributeIdsByDn, mibObjectClassesByDn);

        TRACE_PRINTF("Adding subscription %"PRIu32"/%"PRIu32" for SERIAL_NUMBER on FACTORY.0.  Won't trigger a subscription as SERIAL_NUMBER is not set on *FAP.0.FACTORY.0*.", SUBSCRIBER_ID_4, SUBSCRIPTION_ID_4);
        mibAttributeIds.clear();
        mibAttributeIdsByDn.clear();
        mibObjectClassesByDn.clear();
        mibAttributeIds.insert(PARAM_ID_SERIAL_NUMBER);
        mibAttributeIdsByDn[factoryDn] = mibAttributeIds;
        mibSubscriptionManager.AddSubscription(SUBSCRIBER_ID_4, "sub4", SUBSCRIPTION_ID_4, mibAttributeIdsByDn, mibObjectClassesByDn);

        TRACE_MSG("Setting SERIAL_NUMBER on FAP.0... should trigger 2 subscriptions");
        MibAttributeValues attrs3;
        attrs3.AddAttribute(PARAM_ID_SERIAL_NUMBER, "SerialNumber1234");
        testSubClient.SetAttributes(dn, attrs3);
        MibAttributeIds changedAttributeIds3;
        changedAttributeIds3.insert(PARAM_ID_SERIAL_NUMBER);
        mibSubscriptionManager.HandleChangedAttributes(dn, changedAttributeIds3);

        TRACE_MSG("Setting SERIAL_NUMBER on FAP.0.FACTORY.0... should trigger 1 subscription");
        MibAttributeValues attrs5;
        attrs5.AddAttribute(PARAM_ID_SERIAL_NUMBER, "SerialNumber9999");
        testSubClient.SetAttributes(factoryDn, attrs5);
        MibAttributeIds changedAttributeIds5;
        changedAttributeIds5.insert(PARAM_ID_SERIAL_NUMBER);
        mibSubscriptionManager.HandleChangedAttributes(factoryDn, changedAttributeIds3);

        TRACE_MSG("Setting MCC and SERIAL_NUMBER on FAP.0.  Should trigger 3 subscriptions.");
        MibAttributeValues attrs4;
        attrs4.AddAttribute(PARAM_ID_MCC, (u32)125);
        attrs4.AddAttribute(PARAM_ID_SERIAL_NUMBER, "SerialNumber1235");
        testSubClient.SetAttributes(dn, attrs4);
        MibAttributeIds changedAttributeIds4;
        changedAttributeIds4.insert(PARAM_ID_MCC);
        changedAttributeIds4.insert(PARAM_ID_SERIAL_NUMBER);
        mibSubscriptionManager.HandleChangedAttributes(dn, changedAttributeIds4);

        TRACE_MSG("Deleting MCC on FAP.0.  Should trigger 2 delete subscriptions.");
        MibAttributeIds attrsToDelete;
        attrsToDelete.insert(PARAM_ID_MCC);
        testSubClient.DeleteAttributes(dn, attrsToDelete);
        MibAttributeIds deletedAttributeIds;
        deletedAttributeIds.insert(PARAM_ID_MCC);
        mibSubscriptionManager.HandleDeletedAttributes(dn, deletedAttributeIds);

        //Check the new object subscription functionality
        //
        // FAP.0
        //   INTER_RAT_NEIGHBOURS.0
        //     MNC
        //     MCC...
        //   INTER_RAT_NEIGHBOURS.1
        //     MNC
        //     MCC...
        TRACE_PRINTF("Adding subscription %"PRIu32"/%"PRIu32" for FAP.0.INTER_RAT_NEIGHBOURS.  Should trigger a subscription notify.", SUBSCRIBER_ID_5, SUBSCRIPTION_ID_1);

        MibDN fapDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
        mibAttributeIdsByDn.clear();
        mibObjectClasses.clear();
        mibObjectClassesByDn.clear();
        mibObjectClasses.insert(MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS);
        mibObjectClassesByDn[fapDn] = mibObjectClasses;
        mibSubscriptionManager.AddSubscription(SUBSCRIBER_ID_5, "INTER-RAT-NEIGHBOURS", SUBSCRIPTION_ID_1, mibAttributeIdsByDn, mibObjectClassesByDn);

        // Create "FAP.0.INTER_RAT_NEIGHBOURS.0"
        MibRDN irn0Rdn(MIB_OBJECT_CLASS_INTER_RAT_NEIGHBOURS, 0);
        testSubClient.CreateObject(fapDn,irn0Rdn);

        MibDN irn0Dn;
        irn0Dn.push_back(fapRdn);
        irn0Dn.push_back(irn0Rdn);

        MibAttributeValues attrs6;
        attrs6.AddAttribute(PARAM_ID_MCC, (u32)127);
        attrs6.AddAttribute(PARAM_ID_MNC, (u32)23);
        testSubClient.SetAttributes(irn0Dn, attrs6);

        MibAttributeIds changedAttributeIds6;
        changedAttributeIds6.insert(PARAM_ID_MCC);
        changedAttributeIds6.insert(PARAM_ID_MNC);
        mibSubscriptionManager.HandleChangedAttributes(irn0Dn, changedAttributeIds6);

        // Delete "FAP.0.INTER_RAT_NEIGHBOURS.0"
        testSubClient.DeleteObject(irn0Dn);

        MibAttributeIds noMibAttributeIds;
        mibSubscriptionManager.HandleDeletedAttributes(irn0Dn, noMibAttributeIds);


        /**
         * A final sanity check
         */
        CPPUNIT_ASSERT(testSubClient.m_getCount == 12);
        CPPUNIT_ASSERT(testSubClient.m_notifyCount == 10);
        CPPUNIT_ASSERT(testSubClient.m_deleteNotifyCount == 3);

        fflush(stdout);
    }

protected:

private:

};

#endif
