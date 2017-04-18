///////////////////////////////////////////////////////////////////////////////
//
// Tr069GetParameterNamesManager.h
//
// Class for managing ParameterAttributes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069GetParameterNamesManager_h_
#define __Tr069GetParameterNamesManager_h_

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
#include "Tr069ParameterInfoList.h"
#include "Tr069RpcGetParameterNames.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

namespace tr069
{

class GetParameterNamesManager
{

public:
    GetParameterNamesManager();
    /**
     * Construction / destruction.
     */
    virtual ~GetParameterNamesManager ();

    void HandleGetParameterNames( Tr069FsmInterface & m_transactionSessionFsm, const RpcGetParameterNames & rpcGetParameterNames );

private:
    void SendGetParameterNamesConfirm(Tr069FsmInterface& m_transactionSessionFsm, const ParameterInfoList& parameterInfoList, std::string cwmpId);
    void SendGetParameterNamesReject(Tr069FsmInterface & m_transactionSessionFsm, const ParameterNames & faultParameterNames, std::string cwmpId);
};



}
#endif
