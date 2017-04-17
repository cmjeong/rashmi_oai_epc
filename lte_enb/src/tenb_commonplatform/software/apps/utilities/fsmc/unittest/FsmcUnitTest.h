///////////////////////////////////////////////////////////////////////////////
//
// FsmcUnitTest.h
//
// Unit tests for fsmc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FsmcUnitTest_h_
#define __FsmcUnitTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

//#include <stdio.h>
//#include <iostream>
//#include <cppunit/TestCase.h>

//#include <3waytypes.h>
//#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "FsmcUnitTest_fsm.h"



using namespace threeway;
using namespace std;
using namespace fsmc;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

namespace fsmc
{

class FsmcUnitTest : public FsmcUnitTestFsmInterface
{
private:
    // Singleton
    FsmcUnitTest() :
        m_fsm(*this,true)
    {

    }
public:
    virtual ~FsmcUnitTest() {}
    static FsmcUnitTest & GetInstance()
    {
        ENTER
        ();

        if (s_instance == NULL)
        {
            s_instance = new FsmcUnitTest();

            RSYS_ASSERT(s_instance);
        }

        RETURN (*s_instance);
    }


    FsmcUnitTestFsm & Fsm() { return m_fsm; }

    void ResetTest()
    {
        //Trace::GetInstance()->SetTraceLevelsMask(0xffffffff);
        m_testRecording = "";
    }
    const string & GetTestResult() { return m_testRecording; }

private:
    static FsmcUnitTest * s_instance;

    void Record( const char * func )
    {
        m_testRecording += func;
        m_testRecording += ";";
    }

    string m_testRecording;

    // Actions
    virtual void ContractFailure(void*) { abort(); }
    virtual void logEvent01(void*) {Record( __func__ );}
    virtual FsmcUnitTestFsmActionlogEvent01failure::Outcome logEvent01failure(void*) {Record( __func__ ); return FsmcUnitTestFsmActionlogEvent01failure::FSM_ACTION_f01;}
    virtual void logEvent02(void*) {Record( __func__ );}
    virtual FsmcUnitTestFsmActionlogEvent02failure::Outcome logEvent02failure(void*) {Record( __func__ ); return FsmcUnitTestFsmActionlogEvent02failure::FSM_ACTION_f02;}
    virtual void logEvent03(void*) {Record( __func__ );}
    virtual FsmcUnitTestFsmActionlogEvent03failure::Outcome logEvent03failure(void*) {Record( __func__ ); return FsmcUnitTestFsmActionlogEvent03failure::FSM_ACTION_f03;}
    virtual void logEvent04(void*) {Record( __func__ );}

    // (Super)State Entry & Exit
    virtual void TransitionTestsEntry() {Record( __func__ );}
    virtual void TransitionTestsExit() {Record( __func__ );}
    virtual void Tt01_s01Entry() {Record( __func__ );}
    virtual void Tt01_s01Exit() {Record( __func__ );}
    virtual void Tt01_s02Entry() {Record( __func__ );}
    virtual void Tt01_s02Exit() {Record( __func__ );}
    virtual void Tt01_ss03Entry() {Record( __func__ );}
    virtual void Tt01_ss03Exit() {Record( __func__ );}
    virtual void Tt01_s03Entry() {Record( __func__ );}
    virtual void Tt01_s03Exit() {Record( __func__ );}
    virtual void GuardConditionTestsEntry() {Record( __func__ );}
    virtual void GuardConditionTestsExit() {Record( __func__ );}
    virtual void Gct_s01Entry() {Record( __func__ );}
    virtual void Gct_s01Exit() {Record( __func__ );}
    virtual void Gct_ss01_s02Entry() {Record( __func__ );}
    virtual void Gct_ss01_s02Exit() {Record( __func__ );}
    virtual void Gct_s02Entry() {Record( __func__ );}
    virtual void Gct_s02Exit() {Record( __func__ );}
    virtual void ActionTestsEntry() {Record( __func__ );}
    virtual void ActionTestsExit() {Record( __func__ );}
    virtual void Act_s01Entry() {Record( __func__ );}
    virtual void Act_s01Exit() {Record( __func__ );}
    virtual void Act_s02Entry() {Record( __func__ );}
    virtual void Act_s02Exit() {Record( __func__ );}
    virtual void Act_s03Entry() {Record( __func__ );}
    virtual void Act_s03Exit() {Record( __func__ );}
    virtual void DeepHistoryTestsEntry() {Record( __func__ );}
    virtual void DeepHistoryTestsExit() {Record( __func__ );}
    virtual void Dht_extEntry() {Record( __func__ );}
    virtual void Dht_extExit() {Record( __func__ );}
    virtual void Dht_s01Entry() {Record( __func__ );}
    virtual void Dht_s01Exit() {Record( __func__ );}
    virtual void Dht_ss01Entry() {Record( __func__ );}
    virtual void Dht_ss01Exit() {Record( __func__ );}
    virtual void Dht_ss01_ss01Entry() {Record( __func__ );}
    virtual void Dht_ss01_ss01Exit() {Record( __func__ );}
    virtual void Dht_s02Entry() {Record( __func__ );}
    virtual void Dht_s02Exit() {Record( __func__ );}
    virtual void Dht_s03Entry() {Record( __func__ );}
    virtual void Dht_s03Exit() {Record( __func__ );}

    virtual void ShallowHistoryTestsEntry() {Record( __func__ );}
    virtual void ShallowHistoryTestsExit() {Record( __func__ );}
    virtual void Sht_extEntry() {Record( __func__ );}
    virtual void Sht_extExit() {Record( __func__ );}
    virtual void Sht_ss01Entry() {Record( __func__ );}
    virtual void Sht_ss01Exit() {Record( __func__ );}
    virtual void Sht_s01Entry() {Record( __func__ );}
    virtual void Sht_s01Exit() {Record( __func__ );}
    virtual void Sht_s02Entry() {Record( __func__ );}
    virtual void Sht_s02Exit() {Record( __func__ );}

    virtual void DeferEventTestsEntry() {Record( __func__ );}
    virtual void DeferEventTestsExit() {Record( __func__ );}
    virtual void DeferEvent_e01Entry() {Record( __func__ );}
    virtual void DeferEvent_e01Exit() {Record( __func__ );}
    virtual void DeferEvent_e02Entry() {Record( __func__ );}
    virtual void DeferEvent_e02Exit() {Record( __func__ );}
    virtual void DeferEvent_e03Entry() {Record( __func__ );}
    virtual void DeferEvent_e03Exit() {Record( __func__ );}
    virtual void DeferEvent_noneEntry() {Record( __func__ );}
    virtual void DeferEvent_noneExit() {Record( __func__ );}

    // Guard conditions
    virtual bool QueryTrue(void*) {Record( __func__ ); return true; }
    virtual bool QueryFalse(void*) {Record( __func__ ); return false; }


    // AutoGen Fsm
    FsmcUnitTestFsm m_fsm;
};


class FsmcTests : public CppUnit::TestCase
{
public:
    virtual void runTest() = 0;

    void AssertOnExpectedResult( const char * expectedResult )
    {
        string message("expectedResult=\"");
        message += expectedResult;
        message += "\", FsmcUnitTest::GetInstance().GetTestResult()=\"";
        message += FsmcUnitTest::GetInstance().GetTestResult();
        message += "\"";

        CPPUNIT_ASSERT_MESSAGE( message.c_str(), FsmcUnitTest::GetInstance().GetTestResult() == expectedResult);

        TRACE_MSG("passed.");
    }
};

class StateTransitions : public FsmcTests
{
public:
    void runTest()
    {
        cout << endl
             << "*********************" << endl
             << "Test StateTransitions" << endl
             << "*********************" << endl;

        TRACE_MSG("0-->[[Tt01_s01]TransitionTest01]");
        AssertOnExpectedResult("TransitionTestsEntry;Tt01_s01Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s01] e01/-");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s01] e02/- [Tt01s01]");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("Tt01_s01Exit;Tt01_s01Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s01] e03/- [Tt01s02]");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("Tt01_s01Exit;Tt01_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s02] e01/logEvent01");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("logEvent01;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s02] e02/logEvent02 [Tt01s02]");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("Tt01_s02Exit;logEvent02;Tt01_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s02] e03/logEvent03 [[Tt01s03]Tt01_ss03]");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("Tt01_s02Exit;logEvent03;Tt01_ss03Entry;Tt01_s03Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_ss03] e01/logEvent01");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("logEvent01;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_ss03] e02/logEvent02 [Tt01s03]");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("Tt01_s03Exit;logEvent02;Tt01_s03Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_s03] e03/logEvent03 [Tt01_s03]");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("Tt01_s03Exit;logEvent03;Tt01_s03Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Tt01_ss03[Tt01_s03]] e04/logEvent04 [Gct_s01]");
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("Tt01_s03Exit;Tt01_ss03Exit;logEvent04;Tt01_s01Entry;");

        FsmcUnitTest::GetInstance().Fsm().InjectNextTest(NULL);

        fflush(stdout);
    }
};

class GuardConditions : public FsmcTests
{
public:
    void runTest()
    {
        cout << endl
             << "********************" << endl
             << "Test GuardConditions" << endl
             << "********************" << endl;

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s01] (=True)e01/logEvent01");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("QueryTrue;logEvent01;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s01] (=!False)e02/logEvent02");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("QueryFalse;logEvent02;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s01] (=True)e03/logEvent03");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("QueryFalse;QueryTrue;logEvent03;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s01] (=True)e04/logEvent04 [[Gct_s02]Gct_ss01_s02]");
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("QueryFalse;QueryFalse;Gct_s01Exit;logEvent04;Gct_ss01_s02Entry;Gct_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s02] e01/logEvent01");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("QueryFalse;logEvent01;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s02] e02/logEvent02");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("QueryFalse;QueryFalse;logEvent02;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s02] e03");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("QueryFalse;QueryFalse;QueryFalse;QueryFalse;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Gct_s02] e04");
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("QueryFalse;QueryFalse;Gct_s02Exit;logEvent04;Gct_s02Entry;");

        FsmcUnitTest::GetInstance().Fsm().InjectNextTest(NULL);

        fflush(stdout);
    }
};

class Actions : public FsmcTests
{
public:
    void runTest()
    {
        cout << endl
             << "************" << endl
             << "Test Actions" << endl
             << "************" << endl;

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Act_s01] e01/logEvent01failure [Act_s02]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("Act_s01Exit;logEvent01failure;Act_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Act_s02 e02/logEvent02failure] [Act_s03Entry]");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("logEvent02failure;Act_s02Exit;Act_s03Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[Act_s03] e03/logEvent03failure [Act_s03]");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("Act_s03Exit;logEvent03;logEvent03failure;Act_s03Entry;");

        FsmcUnitTest::GetInstance().Fsm().InjectNextTest(NULL);

        fflush(stdout);
    }
};

class DeepHistory : public FsmcTests
{
public:
    void runTest()
    {
        cout << endl
             << "*****************" << endl
             << "Test Deep-History" << endl
             << "*****************" << endl;

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Change state within deep-history-state Dht_ss01");
        TRACE_MSG("[Dht_s01] e01/logEvent01 [Dht_s02]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("Dht_s01Exit;logEvent01;Dht_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Exit deep history state Dht_ss01");
        TRACE_MSG("[DeepHistoryTests[Dht_ss01[Dht_ss01_ss01[Dht_s02]]]] e01/logEvent01 [Dht_extEntry]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("Dht_s02Exit;Dht_ss01_ss01Exit;Dht_ss01Exit;DeepHistoryTestsExit;logEvent01;Dht_extEntry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Test deep history of Dht_ss01");
        TRACE_MSG("[Dht_extEntry] (=True)e04/logEvent04 [DeepHistoryTests]");
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("Dht_extExit;DeepHistoryTestsEntry;Dht_ss01Entry;Dht_ss01_ss01Entry;Dht_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Exit deep history state Dht_ss01");
        TRACE_MSG("[Dht_ss01[Dht_ss01_ss01[Dht_s02]]] e02/logEvent02 [Dht_s03]]]");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("Dht_s02Exit;Dht_ss01_ss01Exit;Dht_ss01Exit;logEvent02;Dht_s03Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Test deep history of Dht_ss01 ignored if target sub-state supplied");
        TRACE_MSG("[Dht_s03] e01/logEvent01 [Dht_ss01[Dht_ss01_ss01[Dht_s01]]]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("Dht_s03Exit;logEvent01;Dht_ss01Entry;Dht_ss01_ss01Entry;Dht_s01Entry;");

        FsmcUnitTest::GetInstance().Fsm().InjectNextTest(NULL);

        fflush(stdout);
    }
};

class ShallowHistory : public FsmcTests
{
public:
    void runTest()
    {
        cout << endl
             << "********************" << endl
             << "Test Shallow-History" << endl
             << "********************" << endl;

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("First entry to shallow-history-state Sht_ss01");
        TRACE_MSG("[Sht_ext] e01/logEvent01 [Sht_ss01[Sht_s01]]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("Sht_extExit;logEvent01;Sht_ss01Entry;Sht_s01Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Transition to shallow-history-state internal Sht_s02");
        TRACE_MSG("[Sht_s01] e02/logEvent02 [Sht_s02]");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        AssertOnExpectedResult("Sht_s01Exit;logEvent02;Sht_s02Entry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Transition out or shallow-history-state Sht_ss01");
        TRACE_MSG("[Sht_ss01[Sht_s02]] e03/logEvent03 [Sht_ext]");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        AssertOnExpectedResult("Sht_s02Exit;Sht_ss01Exit;logEvent03;Sht_extEntry;");

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("Re-entry to shallow-history-state Sht_ss01");
        TRACE_MSG("[Sht_ext] e01/logEvent01 [Sht_ss01[Sht_s02]]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        AssertOnExpectedResult("Sht_extExit;logEvent01;Sht_ss01Entry;Sht_s02Entry;");


        FsmcUnitTest::GetInstance().Fsm().InjectNextTest(NULL);

        fflush(stdout);
    }
};

class DeferredEvents : public FsmcTests
{
public:
    void runTest()
    {
        cout << endl
             << "********************" << endl
             << "Test Deferred-Events" << endl
             << "********************" << endl;

        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("First entry to deferred-event-state DeferEventTests");

        TRACE_MSG("Defer one event...");
        TRACE_MSG("[DeferEvent_e01] defer e01");
        TRACE_MSG("[DeferEvent_e01] e04/logEvent04 [DeferEvent_none]");
        TRACE_MSG("[DeferEvent_e01] e04/logEvent04 [DeferEvent_none]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("DeferEvent_e01Exit;logEvent04;DeferEvent_noneEntry;DeferEvent_noneExit;logEvent01;DeferEvent_e01Entry;DeferEvent_e01Exit;logEvent04;DeferEvent_noneEntry;");

        TRACE_MSG("Defer two events...");
        TRACE_MSG("[DeferEvent_none] e02");
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[DeferEvent_e02] defer e01");
        TRACE_MSG("[DeferEvent_e02] defer e02");
        TRACE_MSG("[DeferEvent_e02] e04/logEvent04 [DeferEvent_none]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("DeferEvent_e02Exit;logEvent04;DeferEvent_noneEntry;DeferEvent_noneExit;logEvent01;DeferEvent_e01Entry;DeferEvent_e01Exit;logEvent02;DeferEvent_e02Entry;");

        TRACE_MSG("Defer three events...");
        TRACE_MSG("[DeferEvent_none] e03");
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        FsmcUnitTest::GetInstance().ResetTest();
        TRACE_MSG("[DeferEvent_e02] defer e01");
        TRACE_MSG("[DeferEvent_e02] defer e02");
        TRACE_MSG("[DeferEvent_e02] defer e03");
        TRACE_MSG("[DeferEvent_e02] e04/logEvent04 [DeferEvent_none]");
        FsmcUnitTest::GetInstance().Fsm().Injecte01(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte02(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte03(NULL);
        FsmcUnitTest::GetInstance().Fsm().Injecte04(NULL);
        AssertOnExpectedResult("DeferEvent_e03Exit;logEvent04;DeferEvent_noneEntry;DeferEvent_noneExit;logEvent01;DeferEvent_e01Entry;DeferEvent_e01Exit;logEvent02;DeferEvent_e02Entry;DeferEvent_e02Exit;logEvent03;DeferEvent_e03Entry;");

        FsmcUnitTest::GetInstance().Fsm().InjectNextTest(NULL);

        fflush(stdout);
    }
};

}


#endif
