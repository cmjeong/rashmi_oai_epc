///////////////////////////////////////////////////////////////////////////////
//
// Tr069DownloadComplete
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069DownloadResponse_h_
#define __Tr069DownloadResponse_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/messages/common/FtpCompleteInd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Parser.h"
#include "Tr069QueueableEvent.h"
#include "Tr069DownloadRequest.h"

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


class DownloadResponse : public tr069::Tr069QueueableEvent
{
public:
    DownloadResponse( bool fileValid, const std::string& eventCode, threeway::TimeWrap startTime, threeway::TimeWrap stopTime, std::string commandKey = "", std::string faultCode = "", std::string faultString = "" ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(DOWNLOAD_RESPONSE), TRANSACTION_SESSION_FSM ),
        m_succeeded(fileValid),
        m_eventCode(eventCode),
        m_startTime(startTime),
        m_stopTime(stopTime),
        m_commandKey(commandKey),
        m_faultCode(faultCode),
        m_faultString(faultString)
        { }
    virtual ~DownloadResponse(){}

    bool GetDownloadSucceeded(void) const { return m_succeeded; }
    std::string GetEventCode(void) const { return m_eventCode; }
    std::string GetCommandKey() const { return m_commandKey; }
    threeway::TimeWrap GetStartTime() const { return m_startTime; }
    threeway::TimeWrap GetStopTime() const { return m_stopTime; }
    std::string GetFaultString() const { return m_faultString; }
    Tr069ParseFaultDetail::FaultCode GetFaultCode() const
    {
        Tr069ParseFaultDetail::FaultCode faultCode = Tr069ParseFaultDetail::NoFault;

        if(!m_succeeded)
        {
            faultCode = Tr069ParseFaultDetail::DownloadFailure;

            if(std::string::npos != m_faultString.find("530"))
            {
                faultCode = Tr069ParseFaultDetail::FileTransferServerAuthenticationFailure;
            }
        }

        return faultCode;
    }

private:
    shared_ptr<DownloadRequest> m_downloadRequest;
    shared_ptr<FtpCompleteInd> m_ftpCompleteInd;
    bool m_succeeded;
    std::string m_eventCode;
    std::string m_commandKey;
    std::string m_faultCode;
    std::string m_faultString;
    threeway::TimeWrap m_startTime;
    threeway::TimeWrap m_stopTime;
};

}

#endif
