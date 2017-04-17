///////////////////////////////////////////////////////////////////////////////
//
// Tr069HttpPostRequest
//
// Wraps the libcsoap interface into an easier to use OO class.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069HttpPostRequest_h_
#define __Tr069HttpPostRequest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Xmlable.h"

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



class HttpPostRequest : public tr069::Tr069QueueableEvent
{
public:

    HttpPostRequest( const char * post, bool waitForResponse = true ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(HTTP_POST_REQ), SOCKET_INTERFACE_FSM ),
        m_post(post),
        m_waitForResponse(waitForResponse) { }
    HttpPostRequest( Xmlable & xmlablePost, bool waitForResponse = true ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(HTTP_POST_REQ), SOCKET_INTERFACE_FSM ),
        m_post(xmlablePost.Xmlise()),
        m_waitForResponse(waitForResponse) { }
    virtual ~HttpPostRequest(){};

    const std::string & GetPost() const {return m_post;}
    Tr069QueueableEvent::Id GetId() const { return m_id;}
    bool WaitForResponse() const {return m_waitForResponse;}
private:
    static Tr069QueueableEvent::Id m_id;
    std::string m_post;
    bool m_waitForResponse;
};

}

#endif
