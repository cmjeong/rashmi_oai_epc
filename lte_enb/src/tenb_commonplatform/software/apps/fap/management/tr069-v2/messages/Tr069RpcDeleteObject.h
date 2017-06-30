///////////////////////////////////////////////////////////////////////////////
//
// Tr069RpcDeleteObject
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069RpcDeleteObject_h_
#define __Tr069RpcDeleteObject_h_

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
 class RpcDeleteObject : public tr069::Tr069QueueableEvent
{
public:
    RpcDeleteObject( const std::string & objectName, const std::string & parameterKey ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(RPC_DELETE_OBJECT), DELETE_OBJECT_FSM),
        m_objectName_with_instance(objectName),
        m_parameterKey(parameterKey)
    {
    }

    virtual ~RpcDeleteObject()
    {
    };

    std::string GetObjectName(void)
    {
        m_objectName=m_objectName_with_instance;
        m_objectName.erase(m_objectName.begin() + m_objectName.size() - 1); 
        m_objectName = m_objectName.substr(0,m_objectName.find_last_of(".")+1);
        return m_objectName;
    }


    u32 GetInstance(void)
    {
 	std::string objNameWithInst = m_objectName_with_instance;	
     	objNameWithInst.erase(objNameWithInst.begin() + objNameWithInst.size() - 1); 
	std::string instStr = objNameWithInst.substr(objNameWithInst.find_last_of(".")+1);
	instance = std::atoi(instStr.c_str());
    return instance;
   
    }

    std::string GetParameterKey(void) const
    {
        return m_parameterKey;
    }

    void SetCwmpId( std::string cwmpId)
    {
	m_cwmpId = cwmpId;
    }

    std::string GetCwmpId(void)const
    {
	return m_cwmpId;
    }


private:
    std::string m_objectName_with_instance;
    std::string m_parameterKey;
    std::string m_objectName;
    u32 instance; 
    std::string m_cwmpId;
};

}

#endif 
