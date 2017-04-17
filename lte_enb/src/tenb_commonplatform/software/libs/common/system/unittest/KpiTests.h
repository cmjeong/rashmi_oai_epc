///////////////////////////////////////////////////////////////////////////////
//
// KpiTests.h
//
// Unit tests for KPI classes.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiTests_h_
#define __KpiTests_h_

#define THREE_G_KPI
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/KpiGroup.h>
#include <system/KpiCollector.h>
#include <system/KpiLogFileMgr.h>
#include <system/KpiAggregator.h>
#include <system/NumberConversions.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiGroupTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "**************" << endl
             << "KpiGroup tests" << endl
             << "**************" << endl << endl;

        TRACE_MSG("Constructing KpiGroup.");

        KpiGroup kpiGroup(KPI_GROUP_ID_ATTEMPTED_RAB_EST);

        TRACE_MSG("Incrementing some KPIs.");
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL);

        TRACE_MSG("Checking KPI values.");
        CPPUNIT_ASSERT_MESSAGE("Check CsVoice KPI", kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 2);
        CPPUNIT_ASSERT_MESSAGE("Check PsConversational KPI", kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL) == 1);

        TRACE("Let's take a look at ToString()", kpiGroup.ToString().c_str());
        TRACE(" pos", (s32)(kpiGroup.ToString().find("(created)")));
        CPPUNIT_ASSERT_MESSAGE("Check ToString() starts correctly", kpiGroup.ToString().find("AttemptedRabEst          : [CsVoice=2] [PsConversational=1] ") == 0);
        CPPUNIT_ASSERT_MESSAGE("Check ToString() has (created) in it (at end we expect)", kpiGroup.ToString().find("(created)") == 79);

        kpiGroup.TouchTimestamp();
        TRACE("Let's take a look at ToString() after touching it", kpiGroup.ToString().c_str());
        TRACE(" pos", (s32)(kpiGroup.ToString().find("(created)")));
        CPPUNIT_ASSERT_MESSAGE("Check ToString() doesn't have (created) in it", kpiGroup.ToString().find("(created)") == string::npos);
        CPPUNIT_ASSERT_MESSAGE("Check ToString() has (touched) in it (at end we expect)", kpiGroup.ToString().find("(touched)") != string::npos);

        TRACE_MSG("Serialise it and check length and data.");
        u8 data[200];
        u8 expectedData[] = { 0, 0, 0, 0, // Group ID
                              0, 0, 0, 0, // Timestamp - filled in below.
                              1,          // Has been touched.
                              0, 0, 0, 2, // Num KPIs
                              0, 0, 0, 0, // KPI ID 0
                              0, 0, 0, 2, // Value of 2
                              0, 0, 0, 3, // KPI ID 3
                              0, 0, 0, 1  // Value of 1
                            };
        TimeWrap timestamp;
        kpiGroup.GetTimestamp(timestamp);
        U32ToBigEndianByteArray(timestamp.GetUnixTime(), &expectedData[4]);

        TRACE_HEX_MSG("Expected data", expectedData, sizeof(expectedData));

        s32 len = kpiGroup.Serialise(data, sizeof(data));
        TRACE("Serialised data len", len);
        CPPUNIT_ASSERT_MESSAGE("Check Serialise() data len", len == (s32)sizeof(expectedData));

        if(len > 0)
        {
            TRACE_HEX_MSG("Actual data  ", data, (u32)len);
        }

        CPPUNIT_ASSERT_MESSAGE("Check Serialise() data", memcmp(data, expectedData, sizeof(expectedData)) == 0);

        KpiGroup newKpiGroup;
        newKpiGroup.DeSerialise(data, len);

        CPPUNIT_ASSERT_MESSAGE("Check DeSerialised object equals original", kpiGroup == newKpiGroup);

        TRACE_MSG("Check += operator.");
        KpiGroup kpiGroupToAddOn(KPI_GROUP_ID_ATTEMPTED_RAB_EST);
        // Add in KPI values for one we already have and one we don't.
        kpiGroupToAddOn.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL);
        kpiGroupToAddOn.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE);
        kpiGroupToAddOn.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE);

        newKpiGroup += kpiGroupToAddOn;
        TRACE("After addition", newKpiGroup.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE("Check CS_VOICE", newKpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 2);
        CPPUNIT_ASSERT_MESSAGE("Check PS_CONVERSATIONAL", newKpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL) == 2);
        CPPUNIT_ASSERT_MESSAGE("Check PS_INTERACTIVE", newKpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE) == 2);

        // Test the INC_BY_N type of KPI.
        KpiGroup kpiGroup2(KPI_GROUP_ID_IU_USER_DATA_VOLUME_CS);
        kpiGroup2.IncKpiByIntVal(KPI_ID_IU_USER_DATA_VOLUME_CS_DOWNLINK_KB, 1234);
        kpiGroup2.IncKpiByIntVal(KPI_ID_IU_USER_DATA_VOLUME_CS_DOWNLINK_KB, 1);
        TRACE("INC_BY_N group", newKpiGroup.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE("Check CS_DOWNLINK_KB", kpiGroup2.GetIntTypKpi(KPI_ID_IU_USER_DATA_VOLUME_CS_DOWNLINK_KB) == 1235);

        fflush(stdout);
    }

private:
};

class KpiLogFileMgrTest : public CppUnit::TestCase, public KpiGroupVisitor
{
public:
    virtual void VisitKpiGroup(const KpiGroup& kpiGroup)
    {
        TimeWrap timestamp;

        TRACE_PRINTF("VisitKpiGroup, prior number of visits=%" PRIu32 ": %s", m_numVisits, kpiGroup.ToString().c_str());

        switch(m_numVisits)
        {
        case 0:
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO) == 1);
            CPPUNIT_ASSERT(kpiGroup.GetTimestamp(timestamp) == false);
            CPPUNIT_ASSERT(kpiGroup == m_kpiGroupsCrossCheck[m_numVisits]);
            break;
        case 1:
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO) == 3);
            CPPUNIT_ASSERT(kpiGroup.GetTimestamp(timestamp) == false);
            CPPUNIT_ASSERT(kpiGroup == m_kpiGroupsCrossCheck[m_numVisits]);
            break;
        case 2:
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO) == 3);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetTimestamp(timestamp) == false);
            CPPUNIT_ASSERT(kpiGroup == m_kpiGroupsCrossCheck[m_numVisits]);
            break;
        case 3:
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO) == 3);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetIntTypKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE) == 2);
            CPPUNIT_ASSERT(kpiGroup.GetTimestamp(timestamp) == false);
            CPPUNIT_ASSERT(kpiGroup == m_kpiGroupsCrossCheck[m_numVisits]);
            break;
        case 6:
        case 7:
            CPPUNIT_ASSERT(kpiGroup.GetTimestamp(timestamp) == true);
            // *** Intentional drop through
        case 5:
        case 4:
            // We get to here having added a total of 7 groups then closing and reopening the log file and doing a visit.
            // 7 means we've had 2 full files (3 each) and 1 with only 1 in it.  So when we visit we get 4 KPI group objects.
            // So we read the most recent 4 groups i.e. indexes 3,4,5,6
            // So the check here is against m_kpiGroupsCrossCheck[m_numVisits-1]
            CPPUNIT_ASSERT(kpiGroup == m_kpiGroupsCrossCheck[m_numVisits - 1]);
            break;

        default:
            CPPUNIT_FAIL("Got more visits than we expected!");
            break;

        }

        m_numVisits++;
    }

    void runTest()
    {
        cout << endl << endl
             << "****************" << endl
             << "KpiLogFile tests" << endl
             << "****************" << endl << endl;

        m_numVisits = 0;

        remove("./kpilog-0");
        remove("./kpilog-1");
        TimeWrap startTestTime;

        TRACE_MSG("Construct KpiLogFileMgr");

        KpiLogFileMgr kpiLogFileMgr("./kpilog", 3);

        kpiLogFileMgr.StartLogging();

        KpiGroup kpiGroup(KPI_GROUP_ID_ATTEMPTED_RAB_EST);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE);
        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);

        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO);
        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);

        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND);
        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);

        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE);
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE);
        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);

        kpiLogFileMgr.StopLogging();

        // Check first 4 KPI groups.
        TRACE_MSG("Visit log and check first 4 KPI groups.");
        kpiLogFileMgr.AcceptVisitor(*this);
        CPPUNIT_ASSERT_MESSAGE("Check number of KpiGroups read", m_numVisits == 4);


        kpiLogFileMgr.StartLogging();

        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);
        sleep(1);
        TimeWrap middleTestTime;
        kpiGroup.TouchTimestamp();
        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_STREAMING);
        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);

        kpiGroup.IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_STREAMING);
        kpiLogFileMgr.WriteObject(kpiGroup);
        m_kpiGroupsCrossCheck.push_back(kpiGroup);

        kpiLogFileMgr.StopLogging();

        kpiLogFileMgr.AcceptVisitor(*this);

        // Now test the aggregator.
        KpiAggregator kpiAggregator(kpiLogFileMgr);

        // Do all the KPI groups first.
        TimeWrap timeNow;
        kpiAggregator.AggregateKpis(startTestTime, timeNow);

        TRACE("Aggregator all", kpiAggregator.ToString().c_str());
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 8);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO) == 12);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_CS_STREAMING) == 2);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE) == 8);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND) == 8);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_STREAMING) == 1);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL) == 0);

        kpiAggregator.AggregateKpis(middleTestTime, timeNow);

        TRACE("Aggregator last couple", kpiAggregator.ToString().c_str());
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE) == 4);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO) == 6);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_CS_STREAMING) == 2);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE) == 4);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND) == 4);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_STREAMING) == 1);
        CPPUNIT_ASSERT(kpiAggregator.GetKpiTotalCount(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL) == 0);

        TRACE("Aggregator after all that", kpiAggregator.ToString().c_str());

        fflush(stdout);
    }

private:
    u32 m_numVisits;
    vector<KpiGroup> m_kpiGroupsCrossCheck;
};


#endif
