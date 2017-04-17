///////////////////////////////////////////////////////////////////////////////
//
// Tr069RpcInform.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069RpcInform_h_
#define __Tr069RpcInform_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Tr069ParameterValueStruct.h"

using namespace std;

namespace tr069
{

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



class RpcInform : public tr069::Tr069QueueableEvent
{
public:
    RpcInform( shared_ptr<EventStruct> eventStruct ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(RPC_INFORM), TRANSACTION_SESSION_FSM){ }
    virtual ~RpcInform(){};

    void AddEvent( shared_ptr<EventStruct> eventStruct );
    void AddParameterValue( shared_ptr<ParameterValueStruct> parameterValueStruct );

    string ToString();

private:
    vector< shared_ptr<Tr069EventStruct> > m_eventList;
    vector< shared_ptr<Tr069ParameterValueStruct> > m_parameterList;
};

}

#endif