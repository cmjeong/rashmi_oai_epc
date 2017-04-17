///////////////////////////////////////////////////////////////////////////////
//
// Tr069RpcSetParameterValue
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069RpcSetParameterValue_h_
#define __Tr069RpcSetParameterValue_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"

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

typedef std::map< std::string /*param*/, std::string /*value*/ > ParameterValueMap;


class RpcSetParameterValue : public tr069::Tr069QueueableEvent
{
public:
    RpcSetParameterValue( const std::string & parameterKey ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(RPC_SET_PARAMETER_VALUE), SPV_FSM),
        m_parameterKey(parameterKey)
    {
        // Todo
        // This is a short-cut that gives us the behaviour we expect,
        // but actually the parameter is data-model READ_ONLY, so it will
        // fail when we start checking whether writable.
        //m_parameterValueMap[std::string("Device.ManagementServer.ParameterKey")] = parameterKey;
    }

    virtual ~RpcSetParameterValue()
    {
        m_parameterValueMap.clear();
    };

    void Add( const std::string & parameter, const std::string & value)
    {
        m_parameterValueMap[parameter] = value;
    }

    const ParameterValueMap & GetMap(void) const
    {
        return m_parameterValueMap;
    }
	
    void SetCwmpId( std::string cwmpId)
    {
	m_cwmpId = cwmpId;
    }

    std::string GetCwmpId(void)const
    {
	return m_cwmpId;
    }

    std::string GetParameterKey(void) const
    {
        return m_parameterKey;
    }

private:
    ParameterValueMap m_parameterValueMap;
    std::string m_cwmpId;
    std::string m_parameterKey;
};

}

#endif
