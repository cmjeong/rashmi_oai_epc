 
///////////////////////////////////////////////////////////////////////////////
//
// UpdateEngine.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <dirent.h>
#include <system/Trace.h>
#include <comms/TOSValues.h>
#include <platform/FapAlarmId.h>
#include <system/SerialisationIds.h>
#include <system/WatchDogDereg.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SwUpdateApplication.h"
#include "SwUpdateEngine.h"

///////////////////////////////////////////////////////////////////////////////
// UpdateEngine Class Functions
///////////////////////////////////////////////////////////////////////////////

SwUpdateEngine::SwUpdateEngine (SwUpdateInterface &owner) : Thread("Update Engine"),
                                                   m_swUpdateInterface (owner)
{
    TRACE_PRINTF("SwUpdateEngine::SwUpdateEngine");
    Thread::InitialiseMutex(m_queueMutex);
    Thread::ConditionInit(m_queueCondition);
}


SwUpdateEngine::~SwUpdateEngine()
{
    Thread::LockMutex(m_queueMutex);

    // Delete everything left on the queue.
    // Queue contains smart pointers so this won't leave any dangling objects.
    while(!m_queue.empty())
    {
        m_queue.pop_front();
    }

    Thread::UnlockMutex(m_queueMutex);
    Thread::ConditionDestroy(m_queueCondition);
}

void SwUpdateEngine::Enqueue(SwUpdateOperationRequestPtr objectToQueue)
{
   RSYS_ASSERT (objectToQueue) ;

   Thread::LockMutex(m_queueMutex);
   m_queue.push_back(objectToQueue);

   if (objectToQueue->GetSwUpdateEventType() == SwUpdateOperationRequest::FTP_REQUEST)
   {
      // Inform client through callback that an FTP request has been enqueued
      FtpRequestPtr ftpRequest = dynamic_pointer_cast<FtpRequest>(objectToQueue);
      RSYS_ASSERT(ftpRequest != NULL);
      ftpRequest->SetFtpStatus(FtpRequest::FTP_QUEUED) ;
      ftpRequest->SetSuccess(false) ;
      ftpRequest->SetFailureString("Request Queued") ;
      m_swUpdateInterface.FtpCallback(ftpRequest);
   }

   TRACE_PRINTF ("SwUpdateEngine::Enqueue: Queue length = %d", (int)m_queue.size()) ;
   // Signal to dequeue function that there is a message waiting.
   Thread::ConditionSignal(m_queueCondition);
   Thread::UnlockMutex(m_queueMutex);
}

SwUpdateOperationRequestPtr SwUpdateEngine::Dequeue(u32 timeoutMilliSecs)
{
   // No ENTER/EXIT as this is often called in a tight loop.
   SwUpdateOperationRequestPtr dequeuedObject;

   Thread::LockMutex(m_queueMutex);

   struct timespec absTimeout;
   Thread::ConditionGetAbsTimeout(timeoutMilliSecs, &absTimeout);

   // If there's nothing on the queue, wait for a while...
   while(m_queue.empty())
   {
      // The timed wait function may return before the timeout even if
      // there is nothing on the queue.  Hence we keep checking whether
      // the queue is empty.  The timeout is absolute so we don't need
      // to recalculate it each time.
      if(Thread::ConditionTimedWait(m_queueCondition, m_queueMutex, &absTimeout))
      {
         // Timed out - return empty message
         Thread::UnlockMutex(m_queueMutex);
         return dequeuedObject;
      }
   }

   if (!m_queue.empty())
   {
      dequeuedObject = m_queue.front();
      m_queue.pop_front();
      TRACE_PRINTF ("SwUpdateEngine::Dequeue: Queue length = %d", (int)m_queue.size()) ;
   }

   Thread::UnlockMutex(m_queueMutex);

   return dequeuedObject;
}

bool SwUpdateEngine::Abort (u32 clientRequestId, u32 localRequestId)
{
   bool returnValue = false ;
   bool foundMatchingRequest = false ;
   SwUpdateOperationRequestPtr request ;

   TRACE_PRINTF ("SwUpdateEngine::Abort: Client ID = %u, Local ID = %d", clientRequestId, localRequestId) ;

   // Lock queue while we're processing aborts!
   Thread::LockMutex(m_queueMutex);

   // Check request currently being processed first.
   if (m_currentRequest)
   {
      if ((m_currentRequest->GetClientRequestId() == clientRequestId) &&
            (m_currentRequest->GetLocalRequestId() == localRequestId))
      {
         foundMatchingRequest = true ;
         TRACE_PRINTF ("SwUpdateEngine::Abort: Aborting Current Request!");

         if (m_currentRequest->GetSwUpdateEventType() == SwUpdateOperationRequest::FTP_REQUEST)
         {
            FtpRequestPtr ftpRequest = dynamic_pointer_cast<FtpRequest>(m_currentRequest);
            RSYS_ASSERT(ftpRequest != NULL);

            // Attempt to kill FTP operation
            if (ftpRequest->GetDirection() == FtpRequest::FTP_DIRECTION_GET)
            {
               if(system ("killall -q ftpget") != oam_ret_zero)
                  TRACE_MSG("SwUpdateEngine::Abort, Failed to kill ftp get operation");
            }
            else
            {
               if(system ("killall -q ftpput") != oam_ret_zero)

                  TRACE_MSG("SwUpdateEngine::Abort,Failed to kill ftp put operation ");

            }
            returnValue = true ;
            ftpRequest->SetFtpStatus(FtpRequest::FTP_ABORTED) ;
            ftpRequest->SetSuccess(false) ;
            ftpRequest->SetFailureString("Aborted by client") ;
            m_swUpdateInterface.FtpCallback(ftpRequest);
         }
         else
         {
            // Abort operation only supported for FTP at present
            returnValue = false ;
         }
      }
   }

   if (!foundMatchingRequest && !m_queue.empty())
   {
      TRACE_PRINTF ("SwUpdateEngine::Abort: Checking Queue for matching request!");
      // Check queue for a pending request with matching request IDS
      deque<SwUpdateOperationRequestPtr>::iterator requestIterator;

      int count = 0 ;
      for (requestIterator = m_queue.begin(); requestIterator != m_queue.end(); requestIterator++)
      {
         SwUpdateOperationRequestPtr request (*requestIterator) ;

         if (request)
         {
            TRACE_PRINTF ("SwUpdateEngine::Abort: Queue Item %d - Client ID = %u, Local ID = %d", count++,
                  request->GetClientRequestId(),
                  request->GetLocalRequestId());
         }
         else
         {
            TRACE_PRINTF ("SwUpdateEngine::Abort: Queue Item %d - Null Pointer!", count++ );

         }

         if ((request->GetClientRequestId() == clientRequestId) &&
               (request->GetLocalRequestId() == localRequestId))
         {
            foundMatchingRequest = true ;
            TRACE_PRINTF ("SwUpdateEngine::Abort: Found matching item in queue") ;
            if (request->GetSwUpdateEventType() == SwUpdateOperationRequest::FTP_REQUEST)
            {
               TRACE_PRINTF ("SwUpdateEngine::Abort: Item is FTP request - deleting");
               // Remove from queue and inform client through callback
               m_queue.erase(requestIterator);
               FtpRequestPtr ftpRequest = dynamic_pointer_cast<FtpRequest>(request);
               RSYS_ASSERT(ftpRequest != NULL);
               returnValue = true ;
               ftpRequest->SetFtpStatus(FtpRequest::FTP_ABORTED) ;
               ftpRequest->SetSuccess(false) ;
               ftpRequest->SetFailureString("Aborted by client") ;
               m_swUpdateInterface.FtpCallback(ftpRequest);
            }
            else
            {
               // Abort operation only supported for FTP at present
               returnValue = false ;
            }
            break ;
         }
      }
   }


   Thread::UnlockMutex(m_queueMutex);
   if (foundMatchingRequest)
   {
      TRACE_PRINTF ("SwUpdateEngine::Abort: Done - Found a matching request!") ;
   }
   else
   {
      TRACE_PRINTF ("SwUpdateEngine::Abort: Done - Didn't find a matching request!") ;
   }
   return returnValue ;
}

u32 SwUpdateEngine::ThreadProcedure()
{
   while (!ThreadStopped())
   {
      SwUpdateOperationRequestPtr request = Dequeue(1000);
      if (request)
      {
         m_currentRequest = request ;
         if (SwUpdateOperationRequest::FTP_REQUEST == request->GetSwUpdateEventType())
         {
            FtpRequestPtr ftpRequest = dynamic_pointer_cast<FtpRequest>(request);
            RSYS_ASSERT(ftpRequest != NULL);
            HandleFtpRequest(ftpRequest);
         }

         m_currentRequest.reset();
      }
   }
   return 0 ;
}

void SwUpdateEngine::HandleFtpRequest(FtpRequestPtr requestPtr)
{
   RSYS_ASSERT (requestPtr) ;

   u32 admin_state;
   std::ostringstream ftpCommand;
   bool ftpCommandOk = false;

   switch (requestPtr->GetDirection())
   {
      case FtpRequest::FTP_DIRECTION_GET:
         ftpCommandOk = BuildFtpGetCommand(requestPtr, ftpCommand);
         break;

      case FtpRequest::FTP_DIRECTION_PUT:
         ftpCommandOk = BuildFtpPutCommand(requestPtr, ftpCommand);
         break;

      default:
         break;
   }

   if (ftpCommandOk)
   {
      // Update request status.
      requestPtr->UpdateStartTime();
      requestPtr->SetFtpStatus(FtpRequest::FTP_STARTED) ;

      // Invoke callback to signal start of operation to "owner".
      TRACE_PRINTF(("SwUpdateEngine::HandleFtpRequest: Invoking FTP start callback"));

      // Kick off the transfer.
      m_swUpdateInterface.FtpCallback(requestPtr);
      u32 result = system(ftpCommand.str().c_str());
      requestPtr->UpdateStopTime();

      // Check result.
      requestPtr->SetFtpStatus(FtpRequest::FTP_COMPLETED) ;
      if (result)
      {
         requestPtr->SetSuccess(false);
         char oneLineFromFile[ErrorStringLength] = "";

         string filePath = threeway::getConfigFilePath();
         string fileName = filePath + "/FtpStdErr.txt";
         ifstream ftpStderrStream(fileName.c_str()) ;
         if (ftpStderrStream)
         {
            ftpStderrStream.getline(oneLineFromFile, sizeof(oneLineFromFile));
            TRACE_PRINTF("SwUpdateEngine::HandleFtpRequest: FTP stderr = %s", oneLineFromFile);
            ftpStderrStream.close();
            requestPtr->SetFailureString(oneLineFromFile);
         }
      }
      else
      {
         SwUpdateApplication::GetInstance().isreadyForSwUpgrade=true;
         u32 swUpgrd = 0;

         SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE, swUpgrd);

         if(swUpgrd)
         {
            MibAttributeValues attrs;

            attrs.AddAttribute(PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE, false);
            attrs.AddAttribute(PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE, true);

            
            //Send Admin State Down Req
            SwUpdateApplication::GetInstance().isSwUpgradeStarted = true;

            SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),PARAM_ID_LTE_FAP_ADMIN_STATE, admin_state);
            if(admin_state)
            {
              TRACE_PRINTF("SwUpdateEngine::HandleFtpRequest LTE_FAP_ADMIN_STATE Down Req\n");
              attrs.AddAttribute(PARAM_ID_LTE_FAP_ADMIN_STATE, false);
            }
              SwUpdateApplication::GetInstance().GetMibCache().SetMibAttributesByDn( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrs, ENTITY_OAM);
           
       }

          //Deregister all processes from Watchdog as Upgrade is being performed
          TRACE_PRINTF("SwUpdateEngine::HandleFtpRequest Deregistering with watchdog\n");
         SwUpdateApplication::GetInstance().SetIsDeregWatchDog(true);
         DeregisterWithWatchDog(ENTITY_FTP, ENTITY_WATCHDOG);

         requestPtr->SetSuccess(true) ;
         struct stat sd;
         string filePath = threeway::getConfigFilePath();
         string errFileName = filePath + "/ftp_error.log";
         string FtpStdErr(errFileName.c_str());

         if((0 == stat( FtpStdErr.c_str(), &sd )) && (0 == sd.st_size))
         {
            string FileToDel = "rm -rf " + filePath;
            FileToDel += requestPtr->GetLocalFilename().c_str();
            if(system(FileToDel.c_str()) != oam_ret_zero)
            {
               TRACE_MSG("SwUpdateEngine::HandleFtpRequest,Failed to remove local file"); 
            }
            TRACE_PRINTF("Ftp Success: File %s Deleted", requestPtr->GetLocalFilename().c_str());			     
         }
         else
         {
            TRACE_PRINTF("Ftp is Not success, please check file FtpStdErr");
         }
      }
   }
   else
   {
      requestPtr->SetSuccess(false);
      requestPtr->SetFailureString("Error in request structure");
   }

   // Need to "sync" after any operation which makes changes to file
   // system or errors build up and (eventually) Horrible Things happen...
   if(system("sync") != oam_ret_zero)
   {
      TRACE_MSG("SwUpdateEngine::HandleFtpRequest, Sync operation failed");
   }

   // Invoke callback to signal completion to "owner".
   if (requestPtr->GetSuccess())
   {
      TRACE_PRINTF(("SwUpdateEngine::HandleFtpRequest: Invoking FTP callback: State = FTP_COMPLETED"));
   }
   else
   {
      TRACE_PRINTF(("SwUpdateEngine::HandleFtpRequest: Invoking FTP callback: State = FTP_FAILED"));
   }
   m_swUpdateInterface.FtpCallback(requestPtr);
   u32 opState;
   SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE),PARAM_ID_LTE_RFTX_OP_STATE ,opState);
   if((!opState)&&(SwUpdateApplication::GetInstance().isreadyForSwUpgrade))
   {
      SwUpdateApplication::GetInstance().HandleAdminDownAck();
   }

}

bool SwUpdateEngine::BuildFtpGetCommand(FtpRequestPtr requestPtr, std::ostringstream& ftpGetCommand)
{
   RSYS_ASSERT (requestPtr) ;

   // Construct FTP command line.
   if (requestPtr->GetLocalDir() != "")
   {
      ftpGetCommand << "cd " << requestPtr->GetLocalDir() << " && ";
   }
   if (requestPtr->GetServer() != ""         &&
         requestPtr->GetLocalFilename() != ""  &&
         requestPtr->GetRemoteFilename() != "" )
   {
      bool extendedCommandLineOptionsSupported = (requestPtr->GetLocalIpAddress() != "");

      // remove any existing file of the same name
      ftpGetCommand << "rm -f " <<  requestPtr->GetLocalFilename() << " && ";

      ftpGetCommand << "./ftpget.sh ";

      if(extendedCommandLineOptionsSupported)
      {
         if (SwUpdateApplication::GetInstance().IsQosEnabled())
         {
            ftpGetCommand << "-t " << QOS_CLASS_E << " ";
         }
         else
         {
            ftpGetCommand << "-t " << QOS_NONE << " ";
         }
      }

      if (requestPtr->GetUsername() != "")
      {
         ftpGetCommand << "-u \"" << requestPtr->GetUsername() << "\" ";
         if (requestPtr->GetPassword() != "")
         {
            ftpGetCommand << "-p \"" << requestPtr->GetPassword() << "\" ";
         }
      }

      if (extendedCommandLineOptionsSupported && requestPtr->GetLocalIpAddress() != "")
      {
         ftpGetCommand << "-s " << requestPtr->GetLocalIpAddress() << " ";
      }

      ftpGetCommand << " " << requestPtr->GetServer() <<
         " " << requestPtr->GetLocalFilename() <<
         " ";

      string remoteDir = requestPtr->GetRemoteDir() ;
      if (remoteDir.length() != 0)
      {
         ftpGetCommand << remoteDir;
      }

      ftpGetCommand << requestPtr->GetRemoteFilename();

      string filePath = threeway::getConfigFilePath();
      string errFileName = filePath + "/FtpStdErr.txt";
      string result = filePath + "/FtpResult.txt";
      ftpGetCommand << " 1> " << result.c_str() <<"2> " << errFileName.c_str();

      // Diagnostic/debug stuff
      TRACE_PRINTF("BuildFtpGetCommand: FTP Command = %s", ftpGetCommand.str().c_str());
      string rFileName = requestPtr->GetRemoteFilename();
      SwUpdateApplication::GetInstance().newSwFileName = 
         rFileName.substr(rFileName.find_last_of("/")+1,rFileName.size());
   }
   else
   {
      TRACE_MSG("BuildFtpGetCommand: BuildFtpGetCommand: One or more mandatory params not provided, abandoning ftp request.");
      TRACE_PRINTF("BuildFtpGetCommand: Server=%s, Filename=%s, RemoteFile=%s",
            requestPtr->GetServer().c_str(),
            requestPtr->GetLocalFilename().c_str(),
            requestPtr->GetRemoteFilename().c_str());
      return false ;
   }

   return true;
}

bool SwUpdateEngine::BuildFtpPutCommand(FtpRequestPtr requestPtr, std::ostringstream& ftpPutCommand)
{
   std::string fileTransferMethod, url, ftpServer, remoteDirectory, remoteFilename, user, pswd;

   RSYS_ASSERT (requestPtr) ;

   SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_FILE_TRANSFER_METHOD, fileTransferMethod);

   u32 pmProfileIdx = 0;
   for(pmProfileIdx = 0; pmProfileIdx < MAX_PERF_MGMT_ENTRY; pmProfileIdx++)
   {
      MibDN dnobj = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_PERF_MGMT, pmProfileIdx);
      MibAccessInterface& m_mib = SwUpdateApplication::GetInstance().GetMibCache();
      TRACE_PRINTF("Mibdn generated: %s", dnobj.ToString().c_str());
      if(m_mib.IsMibObjectPresent(dnobj))
      {
         u32 uploadEnable = 0;

         SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(dnobj, PARAM_ID_PM_UPLOAD_ENABLE, uploadEnable);
         if(uploadEnable)
         {
            SwUpdateApplication::GetInstance().GetMibCache().GetMibAttribute(dnobj, PARAM_ID_PM_URL, url);
         }
      }
   }

   TRACE_PRINTF("File Transfer method is %s, URL is %s\n",fileTransferMethod.c_str(),url.c_str());

   //Extract FTP server IP address from the URL

   size_t position_of_ip_add_begin = url.find("://")+3;
   size_t position_of_ip_add_end = url.find("/",position_of_ip_add_begin);

   if(position_of_ip_add_begin != std::string::npos)
   {
      if(position_of_ip_add_end != std::string::npos)
      {
         ftpServer = url.substr( position_of_ip_add_begin, (position_of_ip_add_end - position_of_ip_add_begin) );
         //Eliminate the port if provided
         size_t position_of_port = ftpServer.find(":");
         if(position_of_port != std::string::npos)
         {
            ftpServer.erase(position_of_port);
         }
      }
      else
      {
         ftpServer = url.substr( position_of_ip_add_begin);
      }
   }
   else
   {
      ftpServer = url;
   }

   //Extract Destination Directory from the URL

   if(position_of_ip_add_end != std::string::npos)
   {
      remoteDirectory = url.substr( position_of_ip_add_end);
   }
   else
   {
      remoteDirectory = "./";
   }   

   // Construct FTP command line.
   if (requestPtr->GetLocalDir() != "")
   {
      ftpPutCommand << "cd " << requestPtr->GetLocalDir() << " && ";
   }
   if (requestPtr->GetServer() != ""         &&
         requestPtr->GetLocalFilename() != ""  &&
         requestPtr->GetRemoteDir() != ""      )
   {
      bool extendedCommandLineOptionsSupported = (requestPtr->GetLocalIpAddress() != "");

      ftpPutCommand << "./ftpput.sh ";

      if(extendedCommandLineOptionsSupported)
      {
         if (SwUpdateApplication::GetInstance().IsQosEnabled())
         {
            ftpPutCommand << "-t " << QOS_CLASS_E << " ";
         }
         else
         {
            ftpPutCommand << "-t " << QOS_NONE << " ";
         }
      }

      if (requestPtr->GetUsername() != "")
      {
         ftpPutCommand << "-u \"" << requestPtr->GetUsername() << "\" ";
         if (requestPtr->GetPassword() != "")
         {
            ftpPutCommand << "-p \"" << requestPtr->GetPassword() << "\" ";
         }
      }

      /* Adding the file transfer method option */
      ftpPutCommand << "-f \"" << fileTransferMethod << "\" ";

      ftpPutCommand << " " << ftpServer <<
         " " << remoteDirectory <<
         " " << requestPtr->GetLocalFilename();
      string filePath = threeway::getConfigFilePath();
      string errFileName = filePath + "/FtpStdErr.txt";
      string result = filePath + "/FtpResult.txt";
      ftpPutCommand << " 1> " << result.c_str() <<"2> " << errFileName.c_str();

      // Diagnostic/debug stuff
      TRACE_PRINTF("SwUpdateEngine::BuildFtpPutCommand: FTP Command = %s", ftpPutCommand.str().c_str());
   }
   else
   {
      TRACE_MSG("SwUpdateEngine::BuildFtpPutCommand: One or more mandatory params not provided, abandoning ftp request.");
      return false ;
   }

   return true ;
}

