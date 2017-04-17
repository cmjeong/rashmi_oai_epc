///////////////////////////////////////////////////////////////////////////////
//
// <File name>
//
// <Description of class/module>
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

/** DELETE THIS
 * Use this template for C/C++ header files.
 *  - Fill in the header above.
 *  - Delete sections below that are empty (to make it easier to read).
 *  - Don't forget to replace __Template_h_ with __<Your Filename Stem>_h__
 */

#ifndef __Tr069QueueableEvent_h_
#define __Tr069QueueableEvent_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

#define TR069_EVENT( eVENT ) eVENT, #eVENT

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


class Tr069QueueableEvent : public threeway::Queueable
{
public:
    typedef enum Id_tag
    {
        ACTIVATE_SOFTWARE,
        ALARM_OBSERVATION,
        CONNECTION_REQ,
        DATA_MODEL_VERIFY_CNF,
        EVENT_0_BOOTSTRAP,
        FACTORY_RESET_COMMAND,
        FGW_QUERY,
        FTP_GET_REQUEST,
        FTP_PUT_REQUEST,
        FTP_SESSION_COMMAND,
        DOWNLOAD_REQUEST,
        DOWNLOAD_RESPONSE,
        HTTP_POST_REQ,
        HTTP_POST_RES,
        HMS_MODIFY_REQ,
        LOCKED_IND,
        PROCEDURE_COMPLETE_IND,
        REBOOT_REQ,
        RPC_ADD_OBJECT,
        RPC_DELETE_OBJECT,
        RPC_GET_PARAMETER_VALUES,
        RPC_GET_PARAMETER_NAMES,
        RPC_SET_PARAMETER_VALUE,
        RPC_SET_PARAMETER_ATTRIBUTE,
        RPC_INFORM,
        SCAN_RESULTS,
        SECGW_MODIFY_REQ,
        SERVER_DESELECT,
        SHUTDOWN,
        START_UP_MODE,
        START_TRANSACTION_SESSION,
        TCP_CONNECT_CNF,
        TCP_CONNECT_IND,
        TCP_CONNECT_REJ,
        TCP_CONNECT_REQ,
        TCP_CONNECTION_FAILURE_IND,
        TCP_DISCONNECT_CNF,
        TCP_DISCONNECT_REQ,
        TRANSPORT_REQ,
        TRANSPORT_CNF,
        TIMER_EXPIRY_EVENT,
        TRANSACTION_SESSION_COMMAND,
        TRANSACTION_SESSION_COMPLETE,
        UPLOAD_REQUEST,
        UPLOAD_RESPONSE,
        VALUE_CHANGE,
        PERIODIC,
        PERIODIC_INFORM_UPDATE,
        AUTO_TRANSFER_COMPLETE,
        RECONNECT,

    } Id;

    typedef enum Handler_tag
    {
        CWMP_CONNECTION_FSM,
        ANONYMOUS,
        REBOOT_FSM,
        FILE_TRANSFER_FSM,
        SECGW_CONNECTION_FSM,
        SOCKET_INTERFACE_FSM,
        SPV_FSM,
        ADD_OBJECT_FSM,
        DELETE_OBJECT_FSM,
        TR069_APPLICATION,
        TRANSACTION_SESSION_FSM,

    } Handler;

    Tr069QueueableEvent(
            Tr069QueueableEvent::Id id,
            std::string name,
            Tr069QueueableEvent::Handler dst,
            Tr069QueueableEvent::Handler src = ANONYMOUS ) :
        m_src(src),
        m_dst(dst),
        m_id(id),
        m_name(name),
        Queueable(Queueable::OTHER) {}
    virtual ~Tr069QueueableEvent() {}

    void SetDstObject(Tr069QueueableEvent::Handler dst) { m_dst = dst; }
    Tr069QueueableEvent::Handler GetSrc() const { return m_src; }
    Tr069QueueableEvent::Handler GetDst() const { return m_dst; }

    const char * ToString() const { return m_name.c_str(); };

    Tr069QueueableEvent::Id GetId(void) const { return m_id; }

private:
    Tr069QueueableEvent::Handler m_src;
    Tr069QueueableEvent::Handler m_dst;
    std::string m_name;
    Tr069QueueableEvent::Id m_id;
};

}

#endif
