///////////////////////////////////////////////////////////////////////////////
//
// Tr069GetParameterAttributesManager.h
//
// Class for managing ParameterAttributes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069GetParameterAttributesManager_h_
#define __Tr069GetParameterAttributesManager_h_

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
#include "Tr069RpcGetParameterAttributes.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

namespace tr069
{

class GetParameterAttributesManager
{

public:
    GetParameterAttributesManager();
    /**
     * Construction / destruction.
     */
    virtual ~GetParameterAttributesManager ();

    void HandleGetParameterAttributes( Tr069FsmInterface & m_transactionSessionFsm, const RpcGetParameterAttributes & rpcGetParameterAttributes );

private:
    void SendGetParameterAttributesConfirm(Tr069FsmInterface & m_transactionSessionFsm, const AttributeList & attributeList,std::string cwmpId);
    void SendGetParameterAttributesReject(Tr069FsmInterface & m_transactionSessionFsm, const ParameterNames & faultParameterNames, std::string cwmpId);
};



}
#endif


