///////////////////////////////////////////////////////////////////////////////
//
// Tr069RpcSetParameterAttribute
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069RpcSetParameterAttribute_h_
#define __Tr069RpcSetParameterAttribute_h_

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

class SetParameterAttributeNotification
{
public:
    SetParameterAttributeNotification( std::string name, u32 notification) :
        m_name(name),
        m_notification(notification)
    {}

    std::string GetName() const { return m_name; }
    u32 GetNotification() const { return m_notification; }

    string ToString() const
    {
        stringstream ss;

        ss << m_name << "=" << m_notification;

        return ss.str();
    }
private:
    std::string m_name;
    u32 m_notification;
};

class SetParameterAttributeNotifications : public vector<SetParameterAttributeNotification>
{
public:
    string ToString() const
    {
        stringstream ss;

        for( SetParameterAttributeNotifications::const_iterator i = begin();
             i != end();
             ++i)
        {
            ss << i->ToString() << "; ";
        }

        return ss.str();
    }
    
    u32 GetSizeOfSetParameterAttributeNotifications() const
    {
       return size();
    }
    
    SetParameterAttributeNotification* GetParamterAttribute(u32 pos)
    {
       return &(at(pos));
    }
};


class RpcSetParameterAttribute : public tr069::Tr069QueueableEvent
{
public:
    RpcSetParameterAttribute( ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(RPC_SET_PARAMETER_ATTRIBUTE), ANONYMOUS)
    {
    }

    virtual ~RpcSetParameterAttribute()
    {
        m_parameterAttributes.clear();
    };

    void Add( const std::string & name, u32 notificationLevel)
    {
        SetParameterAttributeNotification span(name,notificationLevel);

        m_parameterAttributes.push_back(span);
    }

    const SetParameterAttributeNotifications & GetNoticications(void) const
    {
        return m_parameterAttributes;
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
    SetParameterAttributeNotifications m_parameterAttributes;
    std::string m_cwmpId;
};

}

#endif
