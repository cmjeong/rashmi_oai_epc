///////////////////////////////////////////////////////////////////////////////
//
// Tr069TransactionSession.h
//
// <Description of class/module>
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069TransactionSession_h_
#define __Tr069TransactionSession_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/TimerInterface.h>
#include <system/Url.h>
#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Tr069TransactionSession_fsm.h"
#include "Tr069SocketsInterface.h"
#include "Tr069CwmpInterface.h"

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

class Tr069TransactionSession : public Tr069FsmInterface, TransactionSessionFsmInterface
{
public:
    Tr069TransactionSession( MibAccessInterface&, CwmpInterface &);
    ~Tr069TransactionSession();

    /**
     *  EventHandler Interface
     */
    void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    bool HandleTimerExpiry(threeway::TimerHandle expiredTimer);
    bool GetBootEvent() {return false;}

    void Disconnect() { m_fsm.InjectServerDisconnect(NULL); }

    void EnqueueSoapEnvelope( shared_ptr<string> soapEnvelope );
    void IncrUnAuthErrCount(){m_unauthErrCount++;}
    int  GetUnAuthErrCount(){return m_unauthErrCount;}

private:

    MibAccessInterface & m_paramCache;

    CwmpInterface &m_cwmpInterface;

    void ProcessHttpPostResponseHeader(shared_ptr<HttpPostResponse>);

    bool m_holdRequests;
    TransactionSessionComplete::Result m_transactionSessionResult;
    u32 m_serverConnectCount;
    bool m_fapSentEmptyHttpPostBecauseProceduresFinished;
    bool m_fgwSentEmptyHttpPostBecauseProceduresFinished;
    deque< shared_ptr<string> > httpPostQueue;
    int m_unauthErrCount;

    tr069::SocketsInterface * m_socketsInterface;

    threeway::TimerHandle m_workerThreadGuardTimer;

    /* AutoGen Fsm
     * Keep last - so constructed last.
     */
    Tr069TransactionSessionInterfaceDefinition();
    TransactionSessionFsm m_fsm;
};

}
#endif
