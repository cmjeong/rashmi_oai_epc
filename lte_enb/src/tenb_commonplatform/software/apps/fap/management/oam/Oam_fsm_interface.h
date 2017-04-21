
///////////////////////////////////////////////////////////////////////////////
//
// Oam_fsm_interface.h
//
// Autogenerated from oam.fsm
//
// Fsm Interface Class
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Oam_fsm_interface_h_
#define __Oam_fsm_interface_h_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamFsmTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

// Definition at end of file
#undef OamInterfaceDefinition

namespace Oam
{

/*** WARNING: Code AUTO-GENERATED from oam.fsm. Do not edit! ***/
class OamFsmInterface
{
public:
    OamFsmInterface() {}
    virtual ~OamFsmInterface() {}
    
    // Actions
    
    // Entry/Exit
    virtual void InitialisingExit() = 0;
    virtual void StartExit() = 0;
    virtual void RemScanInProgressEntry() = 0;
    virtual void RemScanInProgressExit() = 0;
    virtual void WaitingForFullScanCompleteEntry() = 0;
    
    // Guard Conditions
    virtual bool Tr069Enabled(void*) = 0;
    
};
} // -namespace-

// Auto-updating Interface Definition
#define OamInterfaceDefinition()  \
    virtual void InitialisingExit(); \
    virtual void StartExit(); \
    virtual void RemScanInProgressEntry(); \
    virtual void RemScanInProgressExit(); \
    virtual void WaitingForFullScanCompleteEntry(); \
    virtual bool Tr069Enabled(void*)

#endif // __Oam_fsm_interface_h_
