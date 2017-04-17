///////////////////////////////////////////////////////////////////////////////
//
// Tr069SetParameterValueManager.h
//
// Class for managing SetParameterValue RPC.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069SetParameterValueManager_h_
#define __Tr069SetParameterValueManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/StringUtils.h>
#include <system/Trace.h>
#include <mib-common/MibAttributeValuesByDn.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069FsmInterface.h"
#include "Tr069SetParameterValueTypes.h"
#include "Tr069SetParameterValue_fsm.h"
#define MAX_NO_OF_FAULTS 5

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

namespace tr069
{

class Tr069SetParameterValueManager : public Tr069FsmInterface, SpvFsmInterface
{

public:
    Tr069SetParameterValueManager(MibAccessInterface& mib, SendMessageInterface &messanger, Tr069TransactionSession & transactionSessionFsm);
    /**
     * Construction / destruction.
     */
    ~Tr069SetParameterValueManager ();

    // Implement Tr069FsmInterface
    virtual void HandleEvent(shared_ptr<threeway::Queueable> tr069Event);
    virtual bool HandleTimerExpiry( threeway::TimerHandle expiredTimer);
    virtual bool GetBootEvent() { return false; }

    std::string GetParameterKey(void) const
    {
        return m_parameterKey;
    }
void HandleSetParamValue(Tr069FsmInterface & transactionSessionFsm, const RpcSetParameterValue & rpcSetParameterValue);

private:
    string m_parameterKey;
    MibAccessInterface& m_mib;
    SendMessageInterface & m_messenger;
    Tr069TransactionSession & m_transactionSessionFsm;
    shared_ptr<RpcSetParameterValue> m_rpcSetParameterValue;
    shared_ptr<MibAttributeValuesByDn> m_mibAttributeValuesByDn;
    string m_faults[MAX_NO_OF_FAULTS],name[MAX_NO_OF_FAULTS];
    int no_of_fault;

    u32 getFaultCode(string faultString);
     /**
     * Retrieve the instance number of the object from DN string
     */
    char * GetMibObjectInstanceNum(string dn) const;

    // Fsm & interface
    Tr069SetParameterValueInterfaceDefinition();
    SpvFsm m_fsm;

    typedef struct FaultCodeMap{
       char  const  *faultString;
       u32 faultCode;
    }FaultCodeMap;
};



}
#endif
