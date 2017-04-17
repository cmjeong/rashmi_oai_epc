///////////////////////////////////////////////////////////////////////////////
//
// Tr069CwmpTr196
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

#ifndef __Tr069Cwmp_h_
#define __Tr069Cwmp_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069FsmInterface.h"
#include "Tr069CwmpConnection_fsm.h"
#include "Tr069GetParameterValuesManager.h"
#include "Tr069GetParameterNamesManager.h"
#include "Tr069GetParameterAttributesManager.h"
#include "CwmpInform.h"
#include "Tr069TransactionSession.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
#define CONN_MAX_RETRY 10
#define INPROGRESS "InProgress"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

class Tr069Cwmp : public Tr069FsmInterface, CwmpConnectionFsmInterface, CwmpInterface
{

public:
    Tr069Cwmp( Tr069FsmInterface & secGwFsm, bool reconnectSecGw, bool bootEventSent );
    Tr069Cwmp( Tr069FsmInterface & secGwFsm, bool reconnectSecGw, bool bootEventSent, bool cwmpInUse );
    virtual ~Tr069Cwmp();

    /**
     *  Tr069FsmInterface
     */
    void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    bool HandleTimerExpiry( threeway::TimerHandle expiredTimer);

    /**
     *  CwmpInterface
     */
    void HandleServerCommand( shared_ptr<HttpPostResponse> cwmpCommand);
    void HandleServerResponse( shared_ptr<HttpPostResponse> cwmpResponse);
    void HandleServerFault( shared_ptr<HttpPostResponse> cwmpFault, TransactionSessionComplete::Result & tscResult);
    bool GetBootEvent() { return m_bootEventSent; };
    void HandlePeriodicInformSubscriptionInd();

    void SendSecGwModifyReq(shared_ptr<TransactionSessionComplete>);
    void RequestReboot(boost::shared_ptr<tr069::TransactionSessionComplete>);
    bool QueryFailedTransactionSessionRecoveryMechanismIsToSelectAnotherServer(boost::shared_ptr<tr069::TransactionSessionComplete>);
    bool QueryFailedTransactionSessionShouldBeIgnored(boost::shared_ptr<tr069::TransactionSessionComplete>);
    bool QueryTransactionSessionSucceded(boost::shared_ptr<tr069::TransactionSessionComplete>);
    void SendAutoTransferCompReq(shared_ptr<AutoTransfer> autoTransfer);

private:

    // Cwmp Responses
    bool QueryInformResponse(shared_ptr<HttpPostResponse> httpResponse);
    bool Query401Response( shared_ptr<HttpPostResponse> cwmpResponse);
    bool QueryTransferCompleteResponse(shared_ptr<HttpPostResponse> httpResponse);

    void HandleInformResponse(shared_ptr<HttpPostResponse> httpResponse);
    void HandleTransferCompleteResponse(shared_ptr<HttpPostResponse> httpResponse);
    void HandleUnknownServerResponse(shared_ptr<HttpPostResponse> httpResponse);

    // Cwmp Commands
    bool QueryAddObject(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryDeleteObject(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryDownloadRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryFactoryReset(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryGetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryGetParameterNamesRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryGetParameterAttributesRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryReboot(shared_ptr<HttpPostResponse> httpResponse);
    bool QuerySetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QuerySetParametersAttributesRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryUploadRequest(shared_ptr<HttpPostResponse> httpResponse);
    bool QueryGetRpcMethods(shared_ptr<HttpPostResponse> httpResponse);

    void HandleAddObject(shared_ptr<HttpPostResponse> httpResponse);
    void HandleDeleteObject(shared_ptr<HttpPostResponse> httpResponse);
    void HandleDownloadRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleFactoryReset(shared_ptr<HttpPostResponse> httpResponse);
    void HandleGetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleGetParameterNamesRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleGetParameterAttributesRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleReboot(shared_ptr<HttpPostResponse> httpResponse);
    void HandleSetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleSetParametersAttributesRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleUploadRequest(shared_ptr<HttpPostResponse> httpResponse);
    void HandleGetRpcMethods(shared_ptr<HttpPostResponse> httpResponse);
    void HandleUnknownServerCommand(shared_ptr<HttpPostResponse> httpResponse);

    // Periodic Inform Timer Expiry
    void HandlePeriodicInformTimerExpiry(void *);

    // Connection failure methods
    void HandleConnectionFailureTimerExpiry(void *);
    void HandleConnectionFailure();
    void HandleConnectionSuccess();
    u32 GetConnectionFailureTimerInSeconds(u32 numberOfConsecutiveFailures);

    void RemoveFgwServerFromMib(const threeway::IPv4Address & outerIpAddress, const threeway::IPv4Address & innerIpAddress);
    void InitialiseServerSelectionAlgorithm(void);


    Tr069FsmInterface & m_secGwFsm;
    // TransactionSession FSM
    shared_ptr<Tr069TransactionSession> m_fsmTransactionSession;
    shared_ptr<Tr069FsmInterface> m_fsmSetParameterValueManager;
    shared_ptr<Tr069FsmInterface> m_fsmAddObjectManager;
    shared_ptr<Tr069FsmInterface> m_fsmDeleteObjectManager;
    shared_ptr<GetParameterValuesManager> m_getParameterValuesManager;
    shared_ptr<GetParameterNamesManager> m_getParameterNamesManager;
    shared_ptr<GetParameterAttributesManager> m_getParameterAttributesManager;

    bool m_remScanPerformed;
    bool m_isFgw;
    bool m_bootEventSent;
    bool m_reconnectSecGw;

    threeway::TimerHandle m_stateGuardTimer;
    threeway::TimerHandle m_periodicInformTimer;
    threeway::TimerHandle m_connectionReattemptTimer;
    shared_ptr<Tr069QueueableEvent> m_transactionSessionInProgressEvent;

    void Enqueue( shared_ptr<Event0Bootstrap> );
    void Enqueue( shared_ptr<ValueChange> );
    void Enqueue( shared_ptr<DownloadResponse> );
    void Enqueue( shared_ptr<UploadResponse> );
    void Enqueue( shared_ptr<ConnectionRequest> connectionRequest);
    void Enqueue( shared_ptr<Periodic> periodic);

    void PostTransferComplete(
            const string & commandKey,
            Tr069ParseFaultDetail::FaultCode faultcode,
            const string & faultString,
            const threeway::TimeWrap & startTime,
            const threeway::TimeWrap & completeTime,
            const string cwmpId);

    // Fsm
    // Auto-updating FSM interface macro
    Tr069CwmpConnectionInterfaceDefinition();
    CwmpConnectionFsm m_fsm;
    bool m_cwmpUsesTunnel;
    TransactionSessionComplete::Result m_transactionSessionResult;
    u32 m_successiveConnectionFailures;
};

}
#endif
