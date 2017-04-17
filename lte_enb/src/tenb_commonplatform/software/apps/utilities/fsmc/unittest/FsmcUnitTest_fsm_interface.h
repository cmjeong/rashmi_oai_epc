///////////////////////////////////////////////////////////////////////////////
//
// FsmcUnitTest_fsm_interface.h
//
// Autogenerated from FsmcUnitTest.fsm
//
// Fsm Interface Class
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FsmcUnitTest_fsm_interface_h_
#define __FsmcUnitTest_fsm_interface_h_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

// Definition at end of file
#undef FsmcUnitTestInterfaceDefinition

namespace fsmc
{

/*** WARNING: Code AUTO-GENERATED from FsmcUnitTest.fsm. Do not edit! ***/
class FsmcUnitTestFsmActionlogEvent01failure
{
public:
    FsmcUnitTestFsmActionlogEvent01failure() {}
    virtual ~FsmcUnitTestFsmActionlogEvent01failure() {}

    typedef enum Outcome_tag
    {
        FSM_ACTION_SUCCESS,
        FSM_ACTION_f01,
    } Outcome;

    virtual Outcome logEvent01failure(void*) = 0;
};

/*** WARNING: Code AUTO-GENERATED from FsmcUnitTest.fsm. Do not edit! ***/
class FsmcUnitTestFsmActionlogEvent02failure
{
public:
    FsmcUnitTestFsmActionlogEvent02failure() {}
    virtual ~FsmcUnitTestFsmActionlogEvent02failure() {}

    typedef enum Outcome_tag
    {
        FSM_ACTION_SUCCESS,
        FSM_ACTION_f01,
        FSM_ACTION_f02,
    } Outcome;

    virtual Outcome logEvent02failure(void*) = 0;
};

/*** WARNING: Code AUTO-GENERATED from FsmcUnitTest.fsm. Do not edit! ***/
class FsmcUnitTestFsmActionlogEvent03failure
{
public:
    FsmcUnitTestFsmActionlogEvent03failure() {}
    virtual ~FsmcUnitTestFsmActionlogEvent03failure() {}

    typedef enum Outcome_tag
    {
        FSM_ACTION_SUCCESS,
        FSM_ACTION_f01,
        FSM_ACTION_f02,
        FSM_ACTION_f03,
    } Outcome;

    virtual Outcome logEvent03failure(void*) = 0;
};

/*** WARNING: Code AUTO-GENERATED from FsmcUnitTest.fsm. Do not edit! ***/
class FsmcUnitTestFsmInterface :
    public FsmcUnitTestFsmActionlogEvent01failure,
    public FsmcUnitTestFsmActionlogEvent02failure,
    public FsmcUnitTestFsmActionlogEvent03failure
{
public:
    FsmcUnitTestFsmInterface() {}
    virtual ~FsmcUnitTestFsmInterface() {}
    
    // Actions
    virtual void ContractFailure(void*) = 0;
    virtual void logEvent01(void*) = 0;
    virtual void logEvent02(void*) = 0;
    virtual void logEvent03(void*) = 0;
    virtual void logEvent04(void*) = 0;
    
    // Entry/Exit
    virtual void TransitionTestsEntry() = 0;
    virtual void TransitionTestsExit() = 0;
    virtual void Tt01_s01Entry() = 0;
    virtual void Tt01_s01Exit() = 0;
    virtual void Tt01_s02Entry() = 0;
    virtual void Tt01_s02Exit() = 0;
    virtual void Tt01_ss03Entry() = 0;
    virtual void Tt01_ss03Exit() = 0;
    virtual void Tt01_s03Entry() = 0;
    virtual void Tt01_s03Exit() = 0;
    virtual void GuardConditionTestsEntry() = 0;
    virtual void GuardConditionTestsExit() = 0;
    virtual void Gct_s01Entry() = 0;
    virtual void Gct_s01Exit() = 0;
    virtual void Gct_ss01_s02Entry() = 0;
    virtual void Gct_ss01_s02Exit() = 0;
    virtual void Gct_s02Entry() = 0;
    virtual void Gct_s02Exit() = 0;
    virtual void ActionTestsEntry() = 0;
    virtual void ActionTestsExit() = 0;
    virtual void Act_s01Entry() = 0;
    virtual void Act_s01Exit() = 0;
    virtual void Act_s02Entry() = 0;
    virtual void Act_s02Exit() = 0;
    virtual void Act_s03Entry() = 0;
    virtual void Act_s03Exit() = 0;
    virtual void DeepHistoryTestsEntry() = 0;
    virtual void DeepHistoryTestsExit() = 0;
    virtual void Dht_extEntry() = 0;
    virtual void Dht_extExit() = 0;
    virtual void Dht_ss01Entry() = 0;
    virtual void Dht_ss01Exit() = 0;
    virtual void Dht_ss01_ss01Entry() = 0;
    virtual void Dht_ss01_ss01Exit() = 0;
    virtual void Dht_s01Entry() = 0;
    virtual void Dht_s01Exit() = 0;
    virtual void Dht_s02Entry() = 0;
    virtual void Dht_s02Exit() = 0;
    virtual void Dht_s03Entry() = 0;
    virtual void Dht_s03Exit() = 0;
    virtual void ShallowHistoryTestsEntry() = 0;
    virtual void ShallowHistoryTestsExit() = 0;
    virtual void Sht_extEntry() = 0;
    virtual void Sht_extExit() = 0;
    virtual void Sht_ss01Entry() = 0;
    virtual void Sht_ss01Exit() = 0;
    virtual void Sht_s01Entry() = 0;
    virtual void Sht_s01Exit() = 0;
    virtual void Sht_s02Entry() = 0;
    virtual void Sht_s02Exit() = 0;
    virtual void DeferEventTestsEntry() = 0;
    virtual void DeferEventTestsExit() = 0;
    virtual void DeferEvent_e01Entry() = 0;
    virtual void DeferEvent_e01Exit() = 0;
    virtual void DeferEvent_e02Entry() = 0;
    virtual void DeferEvent_e02Exit() = 0;
    virtual void DeferEvent_e03Entry() = 0;
    virtual void DeferEvent_e03Exit() = 0;
    virtual void DeferEvent_noneEntry() = 0;
    virtual void DeferEvent_noneExit() = 0;
    
    // Guard Conditions
    virtual bool QueryTrue(void*) = 0;
    virtual bool QueryFalse(void*) = 0;
    
};
} // -namespace-

// Auto-updating Interface Definition
#define FsmcUnitTestInterfaceDefinition()  \
    virtual FsmcUnitTestFsmActionlogEvent01failure::Outcome logEvent01failure(void*); \
    virtual FsmcUnitTestFsmActionlogEvent02failure::Outcome logEvent02failure(void*); \
    virtual FsmcUnitTestFsmActionlogEvent03failure::Outcome logEvent03failure(void*); \
    virtual void ContractFailure(void*); \
    virtual void logEvent01(void*); \
    virtual void logEvent02(void*); \
    virtual void logEvent03(void*); \
    virtual void logEvent04(void*); \
    virtual void TransitionTestsEntry(); \
    virtual void TransitionTestsExit(); \
    virtual void Tt01_s01Entry(); \
    virtual void Tt01_s01Exit(); \
    virtual void Tt01_s02Entry(); \
    virtual void Tt01_s02Exit(); \
    virtual void Tt01_ss03Entry(); \
    virtual void Tt01_ss03Exit(); \
    virtual void Tt01_s03Entry(); \
    virtual void Tt01_s03Exit(); \
    virtual void GuardConditionTestsEntry(); \
    virtual void GuardConditionTestsExit(); \
    virtual void Gct_s01Entry(); \
    virtual void Gct_s01Exit(); \
    virtual void Gct_ss01_s02Entry(); \
    virtual void Gct_ss01_s02Exit(); \
    virtual void Gct_s02Entry(); \
    virtual void Gct_s02Exit(); \
    virtual void ActionTestsEntry(); \
    virtual void ActionTestsExit(); \
    virtual void Act_s01Entry(); \
    virtual void Act_s01Exit(); \
    virtual void Act_s02Entry(); \
    virtual void Act_s02Exit(); \
    virtual void Act_s03Entry(); \
    virtual void Act_s03Exit(); \
    virtual void DeepHistoryTestsEntry(); \
    virtual void DeepHistoryTestsExit(); \
    virtual void Dht_extEntry(); \
    virtual void Dht_extExit(); \
    virtual void Dht_ss01Entry(); \
    virtual void Dht_ss01Exit(); \
    virtual void Dht_ss01_ss01Entry(); \
    virtual void Dht_ss01_ss01Exit(); \
    virtual void Dht_s01Entry(); \
    virtual void Dht_s01Exit(); \
    virtual void Dht_s02Entry(); \
    virtual void Dht_s02Exit(); \
    virtual void Dht_s03Entry(); \
    virtual void Dht_s03Exit(); \
    virtual void ShallowHistoryTestsEntry(); \
    virtual void ShallowHistoryTestsExit(); \
    virtual void Sht_extEntry(); \
    virtual void Sht_extExit(); \
    virtual void Sht_ss01Entry(); \
    virtual void Sht_ss01Exit(); \
    virtual void Sht_s01Entry(); \
    virtual void Sht_s01Exit(); \
    virtual void Sht_s02Entry(); \
    virtual void Sht_s02Exit(); \
    virtual void DeferEventTestsEntry(); \
    virtual void DeferEventTestsExit(); \
    virtual void DeferEvent_e01Entry(); \
    virtual void DeferEvent_e01Exit(); \
    virtual void DeferEvent_e02Entry(); \
    virtual void DeferEvent_e02Exit(); \
    virtual void DeferEvent_e03Entry(); \
    virtual void DeferEvent_e03Exit(); \
    virtual void DeferEvent_noneEntry(); \
    virtual void DeferEvent_noneExit(); \
    virtual bool QueryTrue(void*); \
    virtual bool QueryFalse(void*)

#endif // __FsmcUnitTest_fsm_interface_h_

