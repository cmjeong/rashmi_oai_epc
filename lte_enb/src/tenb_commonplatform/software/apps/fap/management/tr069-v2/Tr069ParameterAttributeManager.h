///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterAttributeManager.h
//
// Class for managing ParameterAttributes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParameterAttributeManager_h_
#define __Tr069ParameterAttributeManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/Trace.h>
#include <mib-common/MibAttributeValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069RpcSetParameterAttribute.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

namespace tr069
{

class ParameterAttributeManager : public SerialisableFactory
{

public:
    ParameterAttributeManager(const char * filename);
    /**
     * Construction / destruction.
     */
    virtual ~ParameterAttributeManager ();

    void HandleSetParamAttributes( Tr069FsmInterface & m_transactionSessionFsm, const RpcSetParameterAttribute & rpcSetParameterAttribute );

private:
    SerialisableFileStore m_setParameterAttributesHistory;

    shared_ptr<Serialisable> GetSerialisable(u32 serialisationId,
                                             const u8* serialisedData,
                                             u32 serialisedDataLen);

    void SendSetParametersConfirm(Tr069FsmInterface & m_transactionSessionFsm, std::string cwmpId);
    void SendSetParametersAttributeReject(Tr069FsmInterface & m_transactionSessionFsm, std::string cwmpId);
};



}
#endif
