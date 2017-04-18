///////////////////////////////////////////////////////////////////////////////
//
// AddObjectManager.h
//
// Class for managing TR069 Add Object RPC
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069AddObjectManager_h_
#define __Tr069AddObjectManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <mib-common/MibDN.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069FsmInterface.h"
#include "Tr069AddObject_fsm.h"
#include "Tr069MultiInstanceMibObject.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

namespace tr069
{

class AddObjectManager : public Tr069FsmInterface, AddObjectFsmInterface
{
public:
    // Is singleton so private constructor.
    AddObjectManager(MibAccessInterface& mib, SendMessageInterface &messanger, Tr069TransactionSession & transactionSessionFsm );

    /**
     * Construction / destruction.
     */
    virtual ~AddObjectManager ();

    // Implement Tr069FsmInterface
    virtual void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    virtual bool HandleTimerExpiry( threeway::TimerHandle expiredTimer){ return false;}
    virtual bool GetBootEvent() {return false; }

    void AddObject( const string & pathname );
    void DeleteObject( const string & name );

    void AddParameterToParameterList( const string & name, ParameterList & parameterList );


private:
    string m_parameterKey;
    MibAccessInterface& m_mib;
    SendMessageInterface & m_messenger;
    Tr069TransactionSession & m_transactionSessionFsm;
    map< string, shared_ptr<Tr069MultiInstanceObject> > m_multiInstanceObjects;

    Tr069AddObjectInterfaceDefinition();
    AddObjectFsm m_fsm;
    shared_ptr<RpcAddObject> m_rpcAddObject;
};



}
#endif
