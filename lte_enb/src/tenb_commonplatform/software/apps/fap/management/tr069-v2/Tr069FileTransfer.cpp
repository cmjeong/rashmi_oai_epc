///////////////////////////////////////////////////////////////////////////////
//
// <File name>
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/Trace.h>
#include <system/SoftwareRelease.h>
#include <messaging/messages/common/FtpAbort.h>
#include <messaging/messages/common/FtpReq.h>
#include <messaging/messages/common/RemScanReq.h>
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/common/ApplyUpdateReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


#include "Tr069Application.h"
#include "Tr069FileTransfer.h"
#include "Tr069Md5.hpp"
#include "Tr069ServerConnection.h"
#include "Tr069TransportReq.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

Tr069FileTransfer* Tr069FileTransfer::s_instance = NULL;


Tr069FileTransfer& Tr069FileTransfer::GetInstance()
{
    ENTER
    ();

    if (s_instance == NULL)
    {
        s_instance = new Tr069FileTransfer;

        RSYS_ASSERT(s_instance);
    }

    RETURN (*s_instance);
}

Tr069FileTransfer::Tr069FileTransfer() :
    m_fsm(*this, true),
    m_remoteFqdn(),
    m_ftpConfirmId(0),
    m_FtpRetried(false),
    m_stateGuardTimer(0),
    m_initialRemScanRequested(false)
{
}

Tr069FileTransfer::~Tr069FileTransfer()
{
    Tr069FileTransfer::s_instance = NULL;
}

void Tr069FileTransfer::HandleEvent( shared_ptr<Queueable> event)
{
   RSYS_ASSERT(event);

   switch(event->GetDomain())
   {
      case Queueable::MESSAGE_SERIALISED_DATA:
         {
            shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);
            if (message)
            {
               switch (message->GetSerialisationId())
               {
                  case SERIALISATION_ID_FTP_CNF:
                     {
                        shared_ptr<FtpCnf> ftpCnf = Serialisable::DeSerialise<FtpCnf>(message);
                        RSYS_ASSERT(ftpCnf);
                        m_fsm.InjectFtpCnf( ftpCnf );
                     }
                     break;

                  case SERIALISATION_ID_FTP_COMPLETE_IND:
                     {
                        shared_ptr<FtpCompleteInd> ftpCompleteInd = Serialisable::DeSerialise<FtpCompleteInd>(message);
                        RSYS_ASSERT(ftpCompleteInd);
                        m_fsm.InjectFtpCompleteInd( ftpCompleteInd );
                     }
                     break;

                  case SERIALISATION_ID_SW_UPDATE_CNF:
                     {
                        shared_ptr<ApplyUpdateCnf> applyUpdateCnf = Serialisable::DeSerialise<ApplyUpdateCnf>(message);
                        RSYS_ASSERT(applyUpdateCnf);
                        m_fsm.InjectApplyUpdateCnf( applyUpdateCnf );
                     }
                     break;

                  case SERIALISATION_ID_SW_INSTALL_CNF:
                     {
                        shared_ptr<InstallUpdateCnf> installUpdateCnf = Serialisable::DeSerialise<InstallUpdateCnf>(message);
                        RSYS_ASSERT(installUpdateCnf);
                        m_fsm.InjectInstallUpdateCnf( installUpdateCnf );
                     }
                     break;

                  case SERIALISATION_ID_SW_ACTIVATE_CNF:
                     {
                        shared_ptr<ActivateUpdateCnf> activateUpdateCnf = Serialisable::DeSerialise<ActivateUpdateCnf>(message);
                        RSYS_ASSERT(activateUpdateCnf);
                        m_fsm.InjectActivateUpdateCnf( activateUpdateCnf );
                     }
                     break;

                  default: break;
               }
            }
         }
         break;

      case Queueable::OTHER:
         {
            shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

            if (tr069Event)
            {
               switch( tr069Event->GetDst() )
               {
                  case Tr069QueueableEvent::FILE_TRANSFER_FSM:
                     {
                        switch(tr069Event->GetId())
                        {
                           case Tr069QueueableEvent::FTP_SESSION_COMMAND:
                              {
                                 shared_ptr<FtpSessionCommand> ftpSessionCommand = dynamic_pointer_cast<FtpSessionCommand>(event);
                                 RSYS_ASSERT(ftpSessionCommand);
                                 m_fsm.InjectFtpSessionCommand( ftpSessionCommand );
                              }
                              break;

                           case Tr069QueueableEvent::TRANSPORT_CNF:
                              {
                                 shared_ptr<TransportCnf> transportCnf = dynamic_pointer_cast<TransportCnf>(tr069Event);
                                 m_fsm.InjectTransportCnf( transportCnf );
                              }
                              break;

                           case Tr069QueueableEvent::ACTIVATE_SOFTWARE:
                              {
                                 m_fsm.InjectActivateSoftware( NULL );
                              }
                              break;

                           default:
                              RSYS_ASSERT_PRINTF(false,"Unhandled FILE_TRANSFER_FSM event.");
                              break;
                        }
                        break;
                     }

                  default:
                     RSYS_ASSERT_PRINTF(false, "Unsupported Event not handled %s", tr069Event->ToString() );
                     break;
               }
            }
         }
         break;

      default:
         RSYS_ASSERT_PRINTF(false, "Unsupported Event domain not handled" );
         break;
   }
}

bool Tr069FileTransfer::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{
   bool timerHandled = false;

   if(expiredTimer)
   {
      if( expiredTimer == m_stateGuardTimer )
      {
         m_fsm.InjectTimerExpiry( NULL );
         timerHandled = true;
      }
   }

   return timerHandled;
}

void Tr069FileTransfer::StoreFtpCommand( shared_ptr<FtpSessionCommand> ftpSessionCommand)
{
    RSYS_ASSERT(ftpSessionCommand);
    RSYS_ASSERT(!m_uploadRequest);
    RSYS_ASSERT(!m_downloadRequest);

    m_downloadRequest = dynamic_pointer_cast<DownloadRequest>(ftpSessionCommand->GetEvent());
    m_uploadRequest = dynamic_pointer_cast<UploadRequest>(ftpSessionCommand->GetEvent());

    RSYS_ASSERT((m_downloadRequest) || (m_uploadRequest));
    RSYS_ASSERT(!((m_downloadRequest) && (m_uploadRequest)));
}

void Tr069FileTransfer::StoreFtpCnfId( shared_ptr<FtpCnf> ftpCnf)
{
    RSYS_ASSERT(ftpCnf);

    m_ftpConfirmId = ftpCnf->GetFtpConfirmIdentity();
}

void Tr069FileTransfer::StoreFtpCompleteInd(shared_ptr<FtpCompleteInd> ftpCompleteInd)
{
    m_ftpCompleteInd = ftpCompleteInd;
}

void Tr069FileTransfer::SendFtpAbort( void* )
{
    FtpAbort ftpAbort(  (u32)this, m_ftpConfirmId );

    Tr069Application::GetInstance().SendMessage(ftpAbort, ENTITY_OAM);
}

void Tr069FileTransfer::SendUploadSuccess()
{
    RSYS_ASSERT(m_uploadRequest);

    shared_ptr<FtpFile> ftpFile = m_uploadRequest->GetFtpFile();

    shared_ptr<UploadResponse> uploadResponse(new UploadResponse(m_uploadRequest, m_ftpCompleteInd));
    RSYS_ASSERT(uploadResponse);

    shared_ptr<TransactionSessionCommand> tsc(new TransactionSessionCommand( uploadResponse ));
    RSYS_ASSERT(tsc);

    Tr069ServerConnection::GetInstance().HandleEvent(tsc);
}

void Tr069FileTransfer::SendUploadFailed()
{
    RSYS_ASSERT(m_uploadRequest);

    shared_ptr<FtpFile> ftpFile = m_uploadRequest->GetFtpFile();

    shared_ptr<UploadResponse> uploadResponse(new UploadResponse(m_uploadRequest, m_ftpCompleteInd));
    RSYS_ASSERT(uploadResponse);

    shared_ptr<TransactionSessionCommand> tsc(new TransactionSessionCommand( uploadResponse ));
    RSYS_ASSERT(tsc);

    Tr069ServerConnection::GetInstance().HandleEvent(tsc);
}

void Tr069FileTransfer::AwaitTransportCnfEntry()
{
    shared_ptr<TransportReq> transportReq(new TransportReq(Tr069QueueableEvent::FILE_TRANSFER_FSM) );
    Tr069ServerConnection::GetInstance().HandleEvent(transportReq);
}

bool Tr069FileTransfer::QueryTransportOk( shared_ptr<TransportCnf> transportCnf)
{
    return transportCnf->GetTransportOk();
}

void Tr069FileTransfer::InstallUpdateEntry()
{
    InstallUpdateReq installUpdateReq(
            m_downloadRequest->GetLocalDirectory(),
            m_downloadRequest->GetFilename()
            );

    Tr069Application::GetInstance().SendMessage(installUpdateReq, ENTITY_SW_UPDATE);
}

void Tr069FileTransfer::RebootIntoNewSwLoad(shared_ptr<ActivateUpdateCnf>)
{
    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD, (u32)1);
    Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);

    Tr069Application::GetInstance().RebootFapViaOam();
}

void Tr069FileTransfer::ActivatingSwPackageEntry()
{
    ActivateUpdateReq activateUpdateReq;
    Tr069Application::GetInstance().SendMessage(activateUpdateReq, ENTITY_SW_UPDATE);
}

void Tr069FileTransfer::InProcedureEntry()
{
   u32 pmProfileIdx = 0;
   for(pmProfileIdx = 0; pmProfileIdx < MAX_PERF_MGMT_ENTRY; pmProfileIdx++)
   {
      MibAccessInterface& m_mib = Tr069Application::GetInstance().GetMibCache();
      MibDN dnobj = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_PERF_MGMT, pmProfileIdx);
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());
      if(m_mib.IsMibObjectPresent(dnobj))
      {
         u32 uploadEnable = 0;

         Tr069Application::GetInstance().GetMibCache().GetMibAttribute(dnobj, PARAM_ID_PM_UPLOAD_ENABLE, uploadEnable);
         if(uploadEnable)
         {
            Url ftpServer;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(dnobj, PARAM_ID_PM_URL, ftpServer);
            m_remoteFqdn.Set( ftpServer.GetFqdn().ToString() );
         }
      }
   }

   m_FtpRetried = false;
   m_ftpConfirmId = 0;
}

void Tr069FileTransfer::InProcedureExit()
{

    if(m_uploadRequest && (m_uploadRequest->GetFtpFile()->GetType() == FtpFile::SwDiagnostics))
    {
        string localFileUrl = m_uploadRequest->GetLocalDirectory() + m_uploadRequest->GetFilename();

        // Delete SW diagnostics file.
        string deleteSwDiagnosticsFile = "rm -f " + localFileUrl;

        TRACE_PRINTF("%s", deleteSwDiagnosticsFile.c_str());
        if(system( deleteSwDiagnosticsFile.c_str() ) != oam_ret_zero )
	{
	    TRACE_MSG("Tr069FileTransfer::InProcedureExit, Failed to delete SW diagnostics File");
	}
    }

    m_downloadRequest.reset();
    m_uploadRequest.reset();
}

void Tr069FileTransfer::WaitFtpThreadResponseEntry()
{
    RSYS_ASSERT(m_stateGuardTimer == 0);

    u32 ftpTimeout = 0;

    if(QueryUpload())
    {
        RSYS_ASSERT(m_uploadRequest);

        ftpTimeout = m_uploadRequest->GetFtpTimeout();
    }
    else
    {
        RSYS_ASSERT(m_downloadRequest);

        ftpTimeout = m_downloadRequest->GetFtpTimeout();
    }

    if(ftpTimeout)
    {
        m_stateGuardTimer = Tr069Application::GetInstance().CreateTimer("FtpReqGuardTimer", ftpTimeout );
    }
}


void Tr069FileTransfer::WaitFtpThreadResponseExit()
{
    Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );

    m_stateGuardTimer = 0;
}


void Tr069FileTransfer::WaitFtpCnfEntry()
{
    IPv4Address localIpAddress;
    Tr069Application::GetInstance().GetMibCache().GetMibAttribute( PARAM_ID_ENB_IP_ADDR_IPV4, localIpAddress);

    if(QueryUpload())
    {
        RSYS_ASSERT(m_uploadRequest);

        FtpReq ftpReq(  (u32)this,
                        FtpReq::PUT,
                        m_uploadRequest->GetUsername(),
                        m_uploadRequest->GetPassword(),
                        m_uploadRequest->GetFilename(),
                        m_remoteFqdn,
                        m_uploadRequest->GetRemoteDirectory(),
                        localIpAddress,
                        m_uploadRequest->GetLocalDirectory() );

        Tr069Application::GetInstance().SendMessage(ftpReq, ENTITY_SW_UPDATE);
    }
    else
    {
        RSYS_ASSERT(m_downloadRequest);

        FtpReq ftpReq(  (u32)this,
                        FtpReq::GET,
                        m_downloadRequest->GetUsername(),
                        m_downloadRequest->GetPassword(),
                        m_downloadRequest->GetFilename(),
                        m_remoteFqdn,
                        m_downloadRequest->GetRemoteDirectory(),
                        localIpAddress,
                        m_downloadRequest->GetLocalDirectory() );

        Tr069Application::GetInstance().SendMessage(ftpReq, ENTITY_SW_UPDATE);
    }
}

void Tr069FileTransfer::FileTransferSucceededEntry()
{
    RSYS_ASSERT(m_ftpCompleteInd != NULL);

}

void Tr069FileTransfer::SendDownloadSucceededResponseEntry()
{
    RSYS_ASSERT(m_downloadRequest);
    RSYS_ASSERT(m_ftpCompleteInd->GetSucceeded());

    shared_ptr<FtpFile> ftpFile = m_downloadRequest->GetFtpFile();

    bool downloadResult   = true;
    std::string eventCode = ftpFile->GetResponseEventCodeSuccessString();
    TimeWrap startTime    = m_ftpCompleteInd->GetStartTime();
    TimeWrap stopTime     = m_ftpCompleteInd->GetStopTime();
    string commandKey     = m_downloadRequest->GetCommandKey();

    shared_ptr<DownloadResponse> downloadResponse(new DownloadResponse( downloadResult, eventCode , startTime, stopTime, commandKey ));
    RSYS_ASSERT(downloadResponse);

    shared_ptr<TransactionSessionCommand> tsc(new TransactionSessionCommand( downloadResponse));
    RSYS_ASSERT(tsc);

    Tr069ServerConnection::GetInstance().HandleEvent(tsc);

    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD_COMMAND_KEY, m_downloadRequest->GetCommandKey());
    attrs.AddAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD_START_TIME, m_ftpCompleteInd->GetStartTime().GetUnixTime());
    attrs.AddAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD_COMPLETE_TIME, m_ftpCompleteInd->GetStopTime().GetUnixTime());
    Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
}

void Tr069FileTransfer::SendDownloadFailedResponseEntry()
{
    RSYS_ASSERT(m_downloadRequest);

    shared_ptr<FtpFile> ftpFile = m_downloadRequest->GetFtpFile();

    bool downloadResult   = false;
    std::string eventCode = ftpFile->GetResponseEventCodeFailureString();
    TimeWrap startTime    = m_ftpCompleteInd->GetStartTime();
    TimeWrap stopTime     = m_ftpCompleteInd->GetStopTime();
    string commandKey     = m_downloadRequest->GetCommandKey();

    shared_ptr<DownloadResponse> downloadResponse(new DownloadResponse( downloadResult, eventCode , startTime, stopTime, commandKey ));
    RSYS_ASSERT(downloadResponse);

    shared_ptr<TransactionSessionCommand> tsc(new TransactionSessionCommand( downloadResponse));
    RSYS_ASSERT(tsc);

    Tr069ServerConnection::GetInstance().HandleEvent(tsc);
}

void Tr069FileTransfer::SendDownloadInvalidResponseEntry()
{
    bool downloadResult   = false;
    std::string eventCode = "X 000FBB SW activation failed";
    TimeWrap startTime;
    TimeWrap stopTime;
    string commandKey;

    if(m_downloadRequest && m_ftpCompleteInd)
    {
        startTime  = m_ftpCompleteInd->GetStartTime();
        stopTime   = m_ftpCompleteInd->GetStopTime();
        commandKey = m_downloadRequest->GetCommandKey();
    }
    else
    {
        Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD_COMMAND_KEY, commandKey);
        u32 time;
        Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD_START_TIME, time);
        startTime = time;
        Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_RPC_SW_LOAD_DOWNLOAD_COMPLETE_TIME, time);
        stopTime = time;
    }

    shared_ptr<DownloadResponse> downloadResponse(new DownloadResponse( downloadResult, eventCode , startTime, stopTime, commandKey ));
    RSYS_ASSERT(downloadResponse);

    shared_ptr<TransactionSessionCommand> tsc(new TransactionSessionCommand( downloadResponse));
    RSYS_ASSERT(tsc);

    Tr069ServerConnection::GetInstance().HandleEvent(tsc);
}

bool Tr069FileTransfer::QueryUpload(  )
{
    return (m_uploadRequest != NULL);
}

bool Tr069FileTransfer::QueryInstallUpdateSucceeded(shared_ptr<InstallUpdateCnf> installUpdateCnf)
{
    RSYS_ASSERT(installUpdateCnf);

    return installUpdateCnf->GetSucceeded();
}

bool Tr069FileTransfer::QueryActivateUpdateSucceeded(shared_ptr<ActivateUpdateCnf> activateUpdateCnf)
{
    RSYS_ASSERT(activateUpdateCnf);

    return activateUpdateCnf->GetSucceeded();
}

bool Tr069FileTransfer::QueryFtpSuccessful( shared_ptr<FtpCompleteInd> ftpCompleteInd)
{
    RSYS_ASSERT(ftpCompleteInd);

    return ftpCompleteInd->GetSucceeded();
}

bool Tr069FileTransfer::QueryFtpSuccessful( )
{
    RSYS_ASSERT(m_ftpCompleteInd);

    return m_ftpCompleteInd->GetSucceeded();
}

bool Tr069FileTransfer::QueryFtpAlreadyRetried( shared_ptr<FtpCompleteInd> ftpCompleteInd )
{
    bool alreadyRetried = m_FtpRetried;

    m_FtpRetried = true;

    return alreadyRetried;
}

bool Tr069FileTransfer::QuerySwLoad( )
{
    RSYS_ASSERT(m_downloadRequest);

    return (m_downloadRequest->GetFtpFile()->GetType() == FtpFile::SwLoad);
}

bool Tr069FileTransfer::QuerySwTransfer( )
{
    RSYS_ASSERT(m_downloadRequest);

    return (m_downloadRequest->GetFtpFile()->GetType() == FtpFile::SwTransfer);
}


}
