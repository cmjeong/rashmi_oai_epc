///////////////////////////////////////////////////////////////////////////////
//
// test_fsm_interface.h
//
// Autogenerated from test.fsm
//
// Fsm Interface Class
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __test_fsm_interface_h_
#define __test_fsm_interface_h_
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
#undef testInterfaceDefinition

namespace testing
{

/*** WARNING: Code AUTO-GENERATED from test.fsm. Do not edit! ***/
class TestFsmInterface
{
public:
    TestFsmInterface() {}
    virtual ~TestFsmInterface() {}
    
    // Actions
    virtual void Ignore(void*) = 0;
    virtual void SendGammaNack(void*) = 0;
    virtual void SendGammaAck(void*) = 0;
    virtual void SendGammaAck() = 0;
    
    // Entry/Exit
    virtual void ActiveEntry() = 0;
    virtual void InactiveEntry() = 0;
    virtual void InactiveExit() = 0;
    virtual void StartingEntry() = 0;
    
    // Guard Conditions
    virtual bool GammaMessageCorrupt(void*) = 0;
    virtual bool GammaMessageValidButInconsistant(void*) = 0;
    virtual bool Precondition2() = 0;
    
};
} // -namespace-

// Auto-updating Interface Definition
#define testInterfaceDefinition()  \
    virtual void Ignore(void*); \
    virtual void SendGammaNack(void*); \
    virtual void SendGammaAck(void*); \
    virtual void SendGammaAck(); \
    virtual void ActiveEntry(); \
    virtual void InactiveEntry(); \
    virtual void InactiveExit(); \
    virtual void StartingEntry(); \
    virtual bool GammaMessageCorrupt(void*); \
    virtual bool GammaMessageValidButInconsistant(void*); \
    virtual bool Precondition2()

#endif // __test_fsm_interface_h_

