///////////////////////////////////////////////////////////////////////////////
//
// Tr069SocketsInterface
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

#ifndef __Tr069ServerConnection_h_
#define __Tr069ServerConnection_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Tr069Events.h"
#include "Tr069FileTransfer.h"
#include "Tr069FsmInterface.h"
#include "messages/Tr069AutoTransfer.h"

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

class Tr069ServerConnection : public Tr069FsmInterface
{
private:
    // Is singleton so private constructor.
    Tr069ServerConnection();

public:
    ~Tr069ServerConnection();
    static Tr069ServerConnection& GetInstance();

    /**
     *  EventHandler Interface
     */
    virtual void StartFsm(void);
    virtual void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    virtual bool HandleTimerExpiry(threeway::TimerHandle expiredTimer);
    virtual bool GetBootEvent() { return false; }

    void UpdatedSecGwUrl(MibAttributeId mibAttributeId);
    bool QueryMinimumNecessaryConfiguration();
    void HandlePeriodicInformSubscriptionInd();
    void HandleSecGwSubsciptionInd();
    void HandleConnectionRequestParameterUpdate();
    void HandleAdminStateChange();
    void InitialisePeriodicInform();
    void HandleAutoTransferCompReq(string uploadFileName,
    string startTime, string completeTime, bool isUploadSuccess);
    void InitializeCwmp();
private:
    static Tr069ServerConnection* s_instance;

    shared_ptr<Tr069FsmInterface> m_fsmSecGw;

    // HMS connection FSM if IPSec tunnel is not used for CWMP traffic
    shared_ptr<Tr069FsmInterface> m_fsmHms;

};

}
#endif
