///////////////////////////////////////////////////////////////////////////////
#ifndef __Tr069DeleteObjectManager_h_
#define __Tr069DeleteObjectManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <mib-common/MibDN.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069FsmInterface.h"
#include "Tr069DeleteObject_fsm.h"
#include "Tr069MultiInstanceMibObject.h"
#include "SoapFault.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

namespace tr069
{

class DeleteObjectManager : public Tr069FsmInterface, DeleteObjectFsmInterface
{
public:
    // Is singleton so private constructor.
    DeleteObjectManager(MibAccessInterface& mib, SendMessageInterface &messanger, Tr069TransactionSession & transactionSessionFsm );

    
 // Construction / destruction.
     
    virtual ~DeleteObjectManager ();

    // Implement Tr069FsmInterface
    virtual void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    virtual bool HandleTimerExpiry( threeway::TimerHandle expiredTimer){ return false;}
    virtual bool GetBootEvent() {return false; }
    void AddObject( const string & pathname );
    void DeleteObject( const string & name );

    void AddParameterToParameterList( const string & name, ParameterList & parameterList );
    void SendFault(SoapFault &soapFault, string CwmpId);
    private:
    string m_parameterKey;
    MibAccessInterface& m_mib;
    SendMessageInterface & m_messenger;
    Tr069TransactionSession & m_transactionSessionFsm;
    map< string, shared_ptr<Tr069MultiInstanceObject> > m_multiInstanceObjects;

    Tr069DeleteObjectInterfaceDefinition();
    DeleteObjectFsm m_fsm;
	shared_ptr<RpcDeleteObject> m_rpcDeleteObject;
};



}
#endif 

