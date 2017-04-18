///////////////////////////////////////////////////////////////////////////////
//
// Tr069Reboot.h
//
// <Description of class/module>
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

/** DELETE THIS
 * Use this template for C/C++ header files.
 *  - Fill in the header above.
 *  - Delete sections below that are empty (to make it easier to read).
 *  - Don't forget to replace __Template_h_ with __<Your Filename Stem>_h__
 */

#ifndef __Tr069Reboot_h_
#define __Tr069Reboot_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Tr069Events.h"
#include "Tr069FileTransfer.h"
#include "Tr069Reboot_fsm.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

class Tr069Reboot : public RebootFsmInterface
{
private:
    // Is singleton so private constructor.
    Tr069Reboot();

public:
    virtual ~Tr069Reboot();
    static Tr069Reboot& GetInstance();

    /**
     *  EventHandler Interface
     */
    void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    bool HandleTimerExpiry(threeway::TimerHandle expiredTimer);

    void OperationalStateDisabled(void);

    bool QueryFapAboutToReboot()
    {
        return m_fapRebooting;
    }

private:
    static Tr069Reboot* s_instance;

    bool m_fapRebooting;
    threeway::TimerHandle m_stateGuardTimer;

    /**
     * Fsm Interface
     */
    // Actions
    virtual void ImmediateReboot(void*);

    // Entry/Exit
    virtual void RebootingEntry();
    virtual void DelaySecGwDisconnectEntry();
    virtual void DelaySecGwDisconnectExit();
    virtual void SecGwDisconnectEntry();
    virtual void SecGwDisconnectExit();

    // Guard Conditions
    virtual bool QueryOperational();



    /**
     * Fsm
     */
    RebootFsm   m_fsm;

};

}
#endif
