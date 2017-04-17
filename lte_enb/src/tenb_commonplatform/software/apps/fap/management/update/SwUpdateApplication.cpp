 
///////////////////////////////////////////////////////////////////////////////
//
// SwUpdateApplication.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <system/Trace.h>
#include <system/Exception.h>
#include <system/SerialisationIds.h>
#include <messaging/transport/CliHandler.h>
#include <messaging/messages/common/FtpReq.h>
#include <messaging/messages/common/FtpCnf.h>
#include <messaging/messages/common/FtpAbort.h>
#include <messaging/messages/common/FtpCompleteInd.h>
#include <messaging/messages/common/FtpGetReq.h>
#include <messaging/messages/common/FtpGetCnf.h>
#include <messaging/messages/common/FtpPutReq.h>
#include <messaging/messages/common/FtpPutCnf.h>
#include <messaging/messages/common/ApplyUpdateReq.h>
#include <messaging/messages/common/ApplyUpdateCnf.h>
#include <messaging/messages/common/RevertUpdateReq.h>
#include <messaging/messages/common/RevertUpdateCnf.h>
#include <messaging/messages/common/InstallUpdateReq.h>
#include <messaging/messages/common/InstallUpdateCnf.h>
#include <messaging/messages/common/ActivateUpdateReq.h>
#include <messaging/messages/common/ActivateUpdateCnf.h>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/cli/CliExecuteCmdProgressInd.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <messaging/messages/common/RequestStartRsp.h>
#include <messaging/messages/common/AutonomousTransferComp.h>
#include <messaging/messages/common/UploadLogReq.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SwUpdateApplication.h"
#include "SwUpdateCli.h"

#define UPLOADSUCCESS 0
using namespace threeway;
using namespace boost;
bool SwUpdateApplication::swIsDeregWatchDog = false;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

SwUpdateApplication* SwUpdateApplication::instance = NULL;

DeclareAppVersionStamp
#if 0
static const ParamId FactoryMibSubscriptions[] =
{
	PARAM_ID_HARDWARE_TYPE,
	PARAM_ID_HARDWARE_REVISION,
	PARAM_ID_HARDWARE_MOD_STATE,
    PARAM_ID_INVALID
};
#endif

static const ParamId FapMibSubscriptions[] =
{
	PARAM_ID_SW_PACKAGE_ACTIVE,
	PARAM_ID_SW_PACKAGE_SELECTED,
	PARAM_ID_SW_UPDATE_PACKAGE_NAME_A,
	PARAM_ID_SW_UPDATE_PACKAGE_NAME_B,
	PARAM_ID_QOS_ENABLE,
   PARAM_ID_FILE_TRANSFER_METHOD,
   PARAM_ID_MANAGEMENT_SERVER,
   PARAM_ID_LOG_UPLOAD_INTERVAL,
   PARAM_ID_TRACE_FT_SERVER_NAME,
   PARAM_ID_INVALID
};

static const ParamId FapLteMibSubscriptions[] =
{
   PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE,
   PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE,
   PARAM_ID_INVALID
};


static const ParamId PerfMgmtMibSubscriptions[] =
{
   PARAM_ID_PM_URL,
   PARAM_ID_PM_UPLOAD_ENABLE,
   PARAM_ID_INVALID
};

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SwUpdateApplication::SwUpdateApplication () :
   SingleThreadedAppWithAttrCache("ftp-func"),
   isreadyForSwUpgrade(false),
   m_updateEngine(*this)
{
   ENTER ();

   RegisterMessageHandler(this, "ftp-func");

   EXIT ();
}

SwUpdateApplication::~SwUpdateApplication ()
{
   ENTER ();

   instance = NULL;

   EXIT();
}

SwUpdateApplication &SwUpdateApplication::GetInstance()
{
   ENTER ();

   if(instance == NULL)
   {
      instance = new SwUpdateApplication();
   }

   RETURN (*instance);
}

void SwUpdateApplication::InitialiseApp()
{
   ENTER ();

   shared_ptr<CliHandler> cliFtp(new CliHandler(ENTITY_FTP, "ftp"));
   RegisterCliHandler(ENTITY_FTP, cliFtp); // Base class keeps a shared ptr to it.
   FtpCli::RegisterFtpCliCmds(cliFtp) ;
   isSwUpgradeStarted = false;
   string logDir;
   logDir = getConfigParam("OAM_LOGGING_DIR","");
   SetLogDirPath(logDir);
}

void SwUpdateApplication::StartApp()
{
   ConfigureUpdateEngine();
   WatchdogRegisterPid();
   m_watchdogKickTimer = CreateTimer ("SMWatchdogKick", 5000, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_REPEAT);
   WatchdogKick(getpid(),5,15);
}

void SwUpdateApplication::HandleTimerExpiry(shared_ptr<threeway::TimerExpiry> expiredTimer)
{
   if (expiredTimer->GetTimerHandle() == m_watchdogKickTimer)
   {
      if(swIsDeregWatchDog == false)
      {
         WatchdogKick (getpid(),5,15);
      }
   }
   else if(expiredTimer->GetTimerHandle() == m_logTimerHandle) 
   { 
      string logFileName[3]; 
      int numClosedFiles = Trace::GetInstance().GetLogFilesToUpload(logFileName); 
      for(int n_uploadfile = 0;n_uploadfile < numClosedFiles;n_uploadfile++) 
      {   
         UploadLogReq upLogReq(logFileName[n_uploadfile]); 
         SendMessage(upLogReq,ENTITY_FTP,ENTITY_FTP); 
      } 
      HandleLogUpload(); 
   } 
}

std::vector<MessagingEntity> SwUpdateApplication::GetSupportedEntities()
{
   vector<MessagingEntity> entities;

   entities.push_back(ENTITY_SW_UPDATE);
   entities.push_back(ENTITY_FTP);

   return entities;
}

void SwUpdateApplication::GetSubscriptions(std::vector<SubscriptionDescriptor>& subscriptions)
{
   MibAttributeIds fapAttrIds;
   const ParamId * paramId = FapMibSubscriptions ;
   while(PARAM_ID_INVALID != *paramId)
   {
      fapAttrIds.insert(*paramId);
      paramId++;
   }
   MibAttributeIds fapAdminDown;
   fapAdminDown.insert(PARAM_ID_LTE_RFTX_OP_STATE);
   fapAdminDown.insert(PARAM_ID_LTE_FAP_ADMIN_STATE);

#if 0
   MibAttributeIds factoryAttrIds;
   paramId = FactoryMibSubscriptions ;
   while(PARAM_ID_INVALID != *paramId)
   {
      factoryAttrIds.insert(*paramId);
      paramId++;
   }
#endif

   MibAttributeIds fapLteAttrIds;
   paramId = FapLteMibSubscriptions ;
   while(PARAM_ID_INVALID != *paramId)
   {
      fapLteAttrIds.insert(*paramId);
      paramId++;
   }

   MibAttributeIds perfMgmtAttrIds;
   paramId = PerfMgmtMibSubscriptions ;
   while(PARAM_ID_INVALID != *paramId)
   {
      perfMgmtAttrIds.insert(*paramId);
      paramId++;
   }

   // Add subscriptions to list.
   AddSubscription(subscriptions,
         LOG_UPLOAD_INTERVAL_CHANGE,
         ENTITY_SW_UPDATE,
         MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),
         fapAttrIds);

   AddSubscription(subscriptions,
         ADMIN_DOWN_ACK,
         ENTITY_SW_UPDATE,
         MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),
         fapAdminDown);
#if 0
   AddSubscription(subscriptions,
         UPDATE_APP_FACTORY_MIB_SUBSCRIPTION_ID,
         ENTITY_SW_UPDATE,
         MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),
          factoryAttrIds );
#endif

   AddSubscription(subscriptions,
         UPDATE_APP_FAP_MIB_SUBSCRIPTION_ID,
         ENTITY_SW_UPDATE,
         MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),
         fapLteAttrIds);


   for(u32 perfMgmtId = 0; perfMgmtId < MAX_PERF_MGMT_ENTRY;  perfMgmtId++)
   {
      MibDN perfMgmtMO = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_PERF_MGMT, perfMgmtId);
      AddSubscription(subscriptions, UPDATE_APP_FAP_MIB_SUBSCRIPTION_ID_PERF_MGMNT, ENTITY_SW_UPDATE, perfMgmtMO, perfMgmtAttrIds);
   }
}

bool SwUpdateApplication::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
   // First, pass to parent
   bool handled = SingleThreadedAppWithAttrCache::MessageHandler(message);

   if (MessageSerialisedData::CONNECTIONLESS == message->GetStatus())
   {
      // Handle the message.
      switch(message->GetSerialisationId())
      {
         case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
            {
               shared_ptr<MibSubscribeAttributesInd> subscribeAttributesInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);
               RSYS_ASSERT(subscribeAttributesInd != NULL);

               switch(subscribeAttributesInd->GetSubscriptionId())
               {
                  case LOG_UPLOAD_INTERVAL_CHANGE:
                     HandleLogUpload();
                     break;
                  case ADMIN_DOWN_ACK:
                     HandleAdminDownAck();
                     break;
               }
            }
            break;
         case SERIALISATION_ID_FTP_REQ:
            HandleFtpReq(message);
            break;

         case SERIALISATION_ID_FTP_ABORT:
            HandleFtpAbortReq(message);
            break;

         case SERIALISATION_ID_FTP_GET_REQ:
            HandleFtpGetReq(message);
            break;

         case SERIALISATION_ID_FTP_PUT_REQ:
            HandleFtpPutReq(message);
            break;

         case SERIALISATION_ID_FTP_COMPLETE_IND:
            HandleFtpCompleteInd(message);
            break ;

         case SERIALISATION_ID_FTP_CNF:
            HandleFtpCnf(message);
            break ;
         case SERIALISATION_ID_UPLOAD_LOG_REQ:
            {
               string LogServer;
               GetMibCache().GetMibAttribute(PARAM_ID_TRACE_FT_SERVER_NAME, LogServer);
               if(LogServer.size())
               {
                  //Extarcting file name
                  shared_ptr<UploadLogReq> uploadLogReq = Serialisable::DeSerialise<UploadLogReq>(message);
                  string uploadFileName = uploadLogReq->GetFileName();
                  TimeWrap now;
                  string startTime = (string)now.ToString(); 
                  bool uploadStatus = false;
                  ostringstream Uploadcommand,Deletecommand;;
                  string filePath = threeway::getConfigFilePath();
                  Uploadcommand <<"cd " << filePath.c_str() <<" && sh ftpputLog.sh "<<uploadFileName.c_str();
                  Deletecommand <<"rm -f "<<GetLogDirPath().c_str()<<"/"<<uploadFileName.c_str();

                  TRACE_PRINTF("\nCALLING UPLOAD file Script");
                  //calling Upload file script
                  if( (UPLOADSUCCESS != system(Uploadcommand.str().c_str())))
                  {
                     uploadStatus = false;
                  }
                  else
                  {
                     uploadStatus = true;
                  }
                  bool isDelLogFile = uploadLogReq->GetOpAfterFileUpload();
                  if (isDelLogFile)
                  {
                     if(UPLOADSUCCESS != system(Deletecommand.str().c_str()))
                     {
                        TRACE_PRINTF("Failed to delete log files");
                     }
                  }
                  string completeTime = (string)now.ToString(); 

                  //Send Upload complete message to Tr069
                  AutonomousTransferComp autonomousTransferComp(uploadFileName,
                        startTime, completeTime, uploadStatus);
                  SendMessage(autonomousTransferComp,ENTITY_TR069,ENTITY_FTP);
               }
            }
            break;

         default:
            break;
      }
   }
   else
   {
      TRACE_MSG_LEV(TRACE_WARNING, "Connection oriented message received but this app doesn't use them!");
   }

   return handled;
}

void SwUpdateApplication::HandleFtpReq(shared_ptr<threeway::MessageSerialisedData> message)
{
   // Recover the message.
   shared_ptr<FtpReq> ftpReq = Serialisable::DeSerialise<FtpReq>(message);

   shared_ptr<FtpRequest> ftpRequest ( new FtpRequest(ftpReq->GetRemoteFqdn().ToString(),
            ftpReq->GetUsername(),
            ftpReq->GetPassword(),
            ftpReq->GetRemoteDirectory(),
            ftpReq->GetFilename(),
            (""),
            ftpReq->GetLocalDirectory(),
            ftpReq->GetFilename(),
            message->GetFromEntity(),
            ((FtpReq::GET == ftpReq->GetCommand())? FtpRequest::FTP_DIRECTION_GET : FtpRequest::FTP_DIRECTION_PUT),
            ftpReq->GetFtpRequestIdentity() ) );
   m_updateEngine.Enqueue(ftpRequest);
}

void SwUpdateApplication::HandleFtpCompleteInd(shared_ptr<threeway::MessageSerialisedData> message)
{
   // If one of these comes back we can assume it's as a result of an
   // update request injected by CLI so we can format it into a CLI response
   // message and send it back...
   // Recover the message.
   shared_ptr<FtpCompleteInd> completeInd = Serialisable::DeSerialise<FtpCompleteInd>(message);
   ostringstream responseStream ;

   if (completeInd->GetSucceeded())
   {
      responseStream << "FTP completed OK:"
         << " Client ID = " << completeInd->GetFtpRequestIdentity()
         << " Server ID = " << completeInd->GetFtpConfirmIdentity() ;
   }
   else
   {
      responseStream << "FTP failed: " << completeInd->GetFailureString()
         << " Client ID = " << completeInd->GetFtpRequestIdentity()
         << " Server ID = " << completeInd->GetFtpConfirmIdentity() ;
   }

   CliExecuteCmdProgressInd progressInd(responseStream.str().c_str());
   SendMessage(progressInd, ENTITY_CLI);
}

void SwUpdateApplication::HandleFtpCnf(shared_ptr<threeway::MessageSerialisedData> message)
{
   // If one of these comes back we can assume it's as a result of an
   // update request injected by CLI so we can format it into a CLI response
   // message and send it back...
   // Recover the message.
   shared_ptr<FtpCnf> cnf = Serialisable::DeSerialise<FtpCnf>(message);
   ostringstream responseStream ;

   responseStream << "FTP started:"
      << " Client ID = " << cnf->GetFtpRequestIdentity()
      << " Server ID = " << cnf->GetFtpConfirmIdentity() ;

   CliExecuteCmdProgressInd progressInd(responseStream.str().c_str());
   SendMessage(progressInd, ENTITY_CLI);
}

void SwUpdateApplication::HandleAdminDownAck() 
{
   u32 op_state;
   SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),PARAM_ID_LTE_RFTX_OP_STATE, op_state);
   if((!op_state)&&(isreadyForSwUpgrade))
   {
      isreadyForSwUpgrade=false;
      char absoluteDirPath[10000];
      if( NULL != realpath(".",absoluteDirPath))
      {
         std::ostringstream upgradeCommand;
         string filePath = threeway::getConfigFilePath();
         upgradeCommand << "cd " << filePath.c_str() << "&&";
         upgradeCommand << "./upgrade.sh -d " << absoluteDirPath <<" -f " << newSwFileName;
         TRACE_PRINTF("SwUpdateApplication::%s ugrade command :%s\n",__FUNCTION__,upgradeCommand.str().c_str()); 

         bool result = system(upgradeCommand.str().c_str());
         if (result)
         {
            TRACE_PRINTF("SwUpdateApplication:%s Software upgrade failed ",__func__); 
         }
      }
      else
      {
         TRACE_PRINTF("SwUpdateApplication:%s oamConfigPath not set ",__func__); 
      }
   }
}

void SwUpdateApplication::HandleLogUpload() 
{ 
   TRACE_PRINTF("%s\n",__FUNCTION__); 
   u32 timer_value=0; 
   GetMibCache().GetMibAttribute((MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP)), PARAM_ID_LOG_UPLOAD_INTERVAL,timer_value); 

   if(IsTimerRunning(m_logTimerHandle)) 
   { 
      DeleteTimer(m_logTimerHandle); 
   } 
   if(timer_value > 0) 
   { 
      SwUpdateApplication::GetInstance().StartLogTimer(timer_value*60000); 
   } 
   else 
   { 
      TRACE_PRINTF("\nLOG UPLOAD FUNCTIONALITY IS DISABLED"); 
   } 
} 

void SwUpdateApplication::StartLogTimer(u32 timer_value) 
{ 
   m_logTimerHandle = CreateTimer((const std::string&)"LOG expiration timeout", timer_value ,TimerEngineInterface::TIMER_START_NOW,TimerEngineInterface::TIMER_SINGLE_SHOT); 
}

void SwUpdateApplication::HandleFtpAbortReq(shared_ptr<threeway::MessageSerialisedData> message)
{
   // Recover the message.
   shared_ptr<FtpAbort> ftpAbortReq = Serialisable::DeSerialise<FtpAbort>(message);
   m_updateEngine.Abort(ftpAbortReq->GetFtpRequestIdentity(), ftpAbortReq->GetFtpConfirmIdentity());
}

void SwUpdateApplication::HandleFtpGetReq(shared_ptr<threeway::MessageSerialisedData> message)
{
   // Recover the message.
   shared_ptr<FtpGetReq> ftpGetReq = Serialisable::DeSerialise<FtpGetReq>(message);
   shared_ptr<FtpRequest> ftpRequest ( new FtpRequest(ftpGetReq->GetRemoteIpAddress().ToString(),
            ftpGetReq->GetUsername(),
            ftpGetReq->GetPassword(),
            ftpGetReq->GetRemoteDirectory(),
            ftpGetReq->GetFilename(),
            (""),
            ftpGetReq->GetLocalDirectory(),
            ftpGetReq->GetFilename(),
            message->GetFromEntity(),
            FtpRequest::FTP_DIRECTION_GET));

   m_updateEngine.Enqueue(ftpRequest);
}

void SwUpdateApplication::HandleFtpPutReq(shared_ptr<threeway::MessageSerialisedData> message)
{
   // Recover the message.
   shared_ptr<FtpPutReq> ftpPutReq = Serialisable::DeSerialise<FtpPutReq>(message);
   shared_ptr<FtpRequest> ftpRequest ( new FtpRequest(ftpPutReq->GetRemoteIpAddress().ToString(),
            ftpPutReq->GetUsername(),
            ftpPutReq->GetPassword(),
            ftpPutReq->GetRemoteDirectory(),
            ftpPutReq->GetFilename(),
            (""),
            ftpPutReq->GetLocalDirectory(),
            ftpPutReq->GetFilename(),
            message->GetFromEntity(),
            FtpRequest::FTP_DIRECTION_PUT));

   m_updateEngine.Enqueue(ftpRequest);
}

void SwUpdateApplication::ConfigureUpdateEngine()
{
   m_updateEngine.StartThread(SMALL_DEFAULT_THREAD_STACK_SIZE);
}

void SwUpdateApplication::FtpCallback(FtpRequestPtr request)
{
   if (request)
   {
      FtpStatusInfo ftpStatus (request->GetClientRequestId(),
            request->GetLocalRequestId());
      switch (request->GetFtpStatus())
      {
         case FtpRequest::FTP_ABORTED :
            {
               ftpStatus.SetStatus("ABORTED") ;
               shared_ptr<FtpCompleteInd> msgPtr(new FtpCompleteInd(
                        request->GetClientRequestId(),
                        request->GetLocalRequestId(),
                        request->GetSuccess(),
                        request->GetStartTime(),
                        request->GetStopTime(),
                        request->GetFailureString()));

               SendMessage(*msgPtr, request->GetRequestingEntity(), ENTITY_SW_UPDATE);
            }
            break ;

         case FtpRequest::FTP_COMPLETED :
            {
               if (request->GetSuccess())
               {
                  TRACE_PRINTF("FTP Transfer Succeeded");
                  ftpStatus.SetStatus("COMPLETED") ;
               }
               else
               {
                  TRACE_PRINTF("FTP Transfer Failed: %s", request->GetFailureString().c_str());
                  ftpStatus.SetStatus("FAILED") ;
               }

               /*
                * Length of failure string needs to be checked and string truncated if neccesary!
                */
               string failureString = request->GetFailureString() ;
               if (failureString.length() > FtpCompleteInd::MaxFtpComleteIndStringLength)
               {
                  failureString.erase(FtpCompleteInd::MaxFtpComleteIndStringLength -1) ;
               }

               shared_ptr<FtpCompleteInd> msgPtr(new FtpCompleteInd(
                        request->GetClientRequestId(),
                        request->GetLocalRequestId(),
                        request->GetSuccess(),
                        request->GetStartTime(),
                        request->GetStopTime(),
                        failureString));

               SendMessage(*msgPtr, request->GetRequestingEntity(), ENTITY_SW_UPDATE);
            }
            break ;

         case FtpRequest::FTP_STARTED :
            TRACE_PRINTF ("FTP Transfer starting") ;
            ftpStatus.SetStatus("TRANSFER") ;
            break ;

         case FtpRequest::FTP_QUEUED :
            {
               TRACE_PRINTF ("New FTP Transfer Request Queued") ;
               FtpCnf ftpCnf( request->GetClientRequestId(), request->GetLocalRequestId() );
               SendMessage(ftpCnf, request->GetRequestingEntity(), ENTITY_SW_UPDATE);
               ftpStatus.SetStatus("QUEUED") ;
            }
            break ;

         default :
            break ;
      }
      ftpStatus.SetExtendedStatus (request->GetFailureString()) ;
      m_ftpStatus[request->GetLocalRequestId()] = ftpStatus ;
   }
}

string SwUpdateApplication::GetFtpStatusString (bool extended)
{
   ostringstream outputString ;

   map <u32, FtpStatusInfo>::iterator statusIter;
   for (statusIter = m_ftpStatus.begin(); statusIter != m_ftpStatus.end(); statusIter++)
   {
      outputString << statusIter->second.GetClientRequestId() << " "
         << statusIter->second.GetServerRequestId() << " "
         << statusIter->second.GetStatus() ;
      if ((statusIter->second.GetExtendedStatus().length()) && extended)
      {
         outputString << " " << statusIter->second.GetExtendedStatus() ;
      }
      outputString << endl ;
   }
   //    shared_ptr<string> outputPtr (new string (outputString.str()));
   //    return outputPtr ;
   return outputString.str() ;
}

string SwUpdateApplication::GetUpdateStatusString (bool extended)
{
   ostringstream outputString ;

   outputString << m_updateStatus.GetStatus();
   if (extended)
   {
      outputString << " " << m_updateStatus.GetExtendedStatus();
   }
   return outputString.str() ;
}


bool SwUpdateApplication::IsQosEnabled()
{
   u32 qosEnable = 0;
   GetMibCache().GetMibAttribute(PARAM_ID_QOS_ENABLE, qosEnable);
   return (qosEnable == 1);
}


int main (int argc, char **argv)
{
   try
   {
      return(SwUpdateApplication::GetInstance().Run(argc, argv));
   }
   catch(Exception &e)
   {
      return EXIT_FAILURE;
   }
}

// END OF FILE
