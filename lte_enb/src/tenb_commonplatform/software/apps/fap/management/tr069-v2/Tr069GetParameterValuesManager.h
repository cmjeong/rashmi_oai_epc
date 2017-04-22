///////////////////////////////////////////////////////////////////////////////
//
// Tr069GetParameterValuesManager.h
//
// Class for managing ParameterAttributes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069GetParameterValuesManager_h_
#define __Tr069GetParameterValuesManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <system/Trace.h>
#include <mib-common/MibAttributeValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069RpcGetParameterValues.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

namespace tr069
{

class GetParameterValuesManager
{

public:
    GetParameterValuesManager();
    /**
     * Construction / destruction.
     */
    virtual ~GetParameterValuesManager ();

    void HandleGetParameterValues( Tr069FsmInterface & m_transactionSessionFsm, const RpcGetParameterValues & rpcGetParameterValues );

private:
    void SendGetParameterValuesConfirm(Tr069FsmInterface & m_transactionSessionFsm, const ParameterList & parameterList,std::string cwmpId);
    void SendGetParameterValuesReject(Tr069FsmInterface & m_transactionSessionFsm, const ParameterNames & faultParameterNames, std::string cwmpId);
};



}
#endif
