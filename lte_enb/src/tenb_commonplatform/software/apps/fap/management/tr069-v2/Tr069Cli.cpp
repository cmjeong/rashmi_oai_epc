///////////////////////////////////////////////////////////////////////////////
//
// OamCli.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdio.h>

#include <comms/IPv4Address.h>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/common/OamActionReq.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include <platform/RadisysFapAlarmId.h>
#include "Tr069Cli.h"
#include "Tr069Application.h"
#include "Tr069DownloadRequest.h"
#include "Tr069AlarmManager.h"
#include "Tr196Alarm.h"
#include "MibHelper.h"
#include "Tr069MultiInstanceMibObjectManager.h"
#include "Tr069RpcGetParameterValues.h"
#include "Tr069DataModelManager.h"
#ifdef PRODUCT_generic
extern "C" void __gcov_flush(void);
#endif
using namespace std;
using namespace threeway;
using namespace boost;
using namespace tr069;



CppCliPair Tr069CliCommands::s_cppCliPairs[] =
{      
#ifdef PRODUCT_generic
	{
		{
			"coverage", 0, 0, // min/max arguments
			"ate",
			"coverage",
			"Get coverage."
		},
		&Tr069CliCommands::CliCmdGetCoverage,
	},
#endif
	{
            {
                "addobject", 1, 1,  // min/max arguments
                "dev",
                "addobject dn",
                "Add MultiInstance Object."
            },
            &Tr069CliCommands::CliCmdAddObject,
        },
        {
           {
               "deleteobject", 2, 2,  // min/max arguments
               "dev",
               "deleteobject dn",
               "Delete MultiInstance Object."
          },
          &Tr069CliCommands::CliCmdDeleteObject,
        },
        {
            {
                "ftpget", 3, 3,  // min/max arguments
                "dev",
                "ftpget username password filename",
                "Copy a remote file into /mnt/tmp."
            },
            &Tr069CliCommands::CliCmdDownloadRequest,
        },
	     {
            {
                "ftpput", 3, 3,  // min/max arguments
                "dev",
                "ftpput username password filename",
                "Copy a remote file into /mnt/tmp."
            },
            &Tr069CliCommands::CliCmdUploadRequest,
        },
        {
            {
                "clocks", 0, 1,  // min/max arguments
                "dev",
                "clocks",
                "Test the clocks."
            },
            &Tr069CliCommands::CliCmdClocks,
        },
        {
            {
                "alarms", 0, 1,
                "dev",
                "alarms <file>",
                "Dump all alarms to <file> or STDERR."
            },
            &Tr069CliCommands::CliCmdAlarms,
        },
	     {
            {
                "upload.fm.file", 3, 3,  // min/max arguments
                "dev",
                "upload.fm.file username password filename",
                "Upload FM data file"
            },
            &Tr069CliCommands::CliCmdUploadFmFile,
        },
        {
            {
                "gen.pm.file", 1, 1,  // min/max arguments
                "dev",
                "gen.pm.file <filename>",
                "Generate a PM data file"
            },
            &Tr069CliCommands::CliCmdGenPmFile,
        },
	{
            {
                "gen.upload.pm.file", 1, 1,  // min/max arguments
                "dev",
                "gen.upload.pm.file <filename>",
                "Generate a PM data file and upload"
            },
            &Tr069CliCommands::CliCmdGenAndUploadPmFile,
        },
	{
            {
                "mib.upload.xml.file", 1, 1,  // min/max arguments
                "dev",
                "mib.upload.xml.file <filename>",
                "Generate a MIB XML data file and upload"
            },
            &Tr069CliCommands::CliCmdGenMibXmlAndUpload,
        },
        {
            {
                "action.factory.reset", 0, 0,  // min/max arguments
                "dev",
                "action.factory.reset",
                "Reset the MIB back to factory settings"
            },
            &Tr069CliCommands::CliCmdActionFactoryReset,
        },
        {
            {
                "set.parameter.attribute.notification.active", 1, 1,  // min/max arguments
                "dev",
                "set.parameter.attribute.notification.active <TR data model parameter name or wildcard>",
                "Set the notification level to active (trigger upon change) on the specified parameters"
            },
            &Tr069CliCommands::CliCmdSetParameterAttributeNotificationActive,
        },
        {
            {
                "set.parameter.attribute.notification.passive", 1, 1,  // min/max arguments
                "dev",
                "set.parameter.attribute.notification.active <TR data model parameter name or wildcard>",
                "Set the notification level to passive (queued upon change) on the specified parameters"
            },
            &Tr069CliCommands::CliCmdSetParameterAttributeNotificationPassive,
        },
        {
            {
                "set.parameter.attribute.notification.off", 1, 1,  // min/max arguments
                "dev",
                "set.parameter.attribute.notification.active <TR data model parameter name or wildcard>",
                "Set the notification level to off on the specified parameters"
            },
            &Tr069CliCommands::CliCmdSetParameterAttributeNotificationOff,
        },
        {
            {
                "get", 1, 1,  // min/max arguments
                "dev",
                "get.ParameterDatamodeString value string",
                "To set parametrs"
            },
            &Tr069CliCommands::CliCmdGetParameterValue,
        },
        {
           {
              "set", 2, 2,
              "dev",
              "set.ParameterData",
              "To Set Parameters"
           },
            &Tr069CliCommands::CliCmdSetParameterValue
        }
} ;

Tr069CliCommands::Tr069CliCommands( ApplicationWithMessaging & appWithMess ) :
        m_appWithMess(appWithMess)
{
}

void Tr069CliCommands::Register()
{
    shared_ptr<CliHandler> cli(new CliHandler(ENTITY_TR069, "tr69"));

    m_appWithMess.RegisterCliHandler(ENTITY_TR069, cli);

    for (u32 i = 0; i < sizeof(s_cppCliPairs) / sizeof(s_cppCliPairs[0]); i++)
    {
        cli->RegisterCliCmd(s_cppCliPairs[i].descriptor, s_cppCliPairs[i].cppFuncPtr);
    }
}
  
shared_ptr<CliResponse> Tr069CliCommands::CliCmdUploadRequest(const CliArguments& args)
{
    ostringstream responseStream ;

    if(args.size() == 3)
    {
        std::string commandKey = "command_key";
        std::string fileUrl = args[2];
        std::string username = args[0];
        std::string password = args[1];
	
        std::string targetFilename = "";
        std::string successUrl = "";
        std::string failureUrl = "";

        shared_ptr<UploadRequest> uploadRequest(new UploadRequest(
                    commandKey,
                    shared_ptr<FtpFile>(new FtpFile()),
                    0,
                    fileUrl,
                    username,
                    password ) );

        shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( uploadRequest ));
        Tr069Application::GetInstance().Enqueue(fsc);
        responseStream << "Upload requested...";
    }
    else
    {
        responseStream << "Not correct number arguments.";
    }
    shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;
    return response;
}

shared_ptr<CliResponse> Tr069CliCommands::CliCmdAddObject(const CliArguments& args)
{
   ostringstream responseStream;

   shared_ptr<Tr069MultiInstanceObject> mio = MultiInstanceMibObjectManager::GetInstance().GetMio(args[0]);

   if(mio)
   {
      MibObjectClass MOC = mio->GetChildClass();
      if(MIOAutoManage::GetInstance().isReadOnly(MOC))
      {
         responseStream << "Object NOT created : ReadOnly";
      }
      else
      {
         MibAttributeValues attr;
         shared_ptr<MibCreateObjectReq> mibCreateObjectReq = mio->New( attr );
         if(mibCreateObjectReq)
         {
            Tr069Application::GetInstance().SendMessage( *mibCreateObjectReq, ENTITY_MIB, ENTITY_TR069 );
            responseStream << "Object created instance ID:"<<mibCreateObjectReq->GetChildRdn().GetMibObjectInstance() <<"\n";
         }
         else
         {
            responseStream << "Object NOT created : Exceeded maximum limit";
         }
      }
   }
   else
   {
      responseStream << "Object NOT created, dn doesn't exist";
   }

   shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;

   return response;
}

shared_ptr<CliResponse> Tr069CliCommands::CliCmdDeleteObject(const CliArguments& args)
{
   ostringstream responseStream;

   shared_ptr<Tr069MultiInstanceObject> mio = MultiInstanceMibObjectManager::GetInstance().GetMio(args[0]);

   if(mio)
   {
      string inst = args[1];
      u32 instance = atoi(args[1].c_str());

      if (strstr(args[0].c_str(),"CellConfig.LTE.RAN.NeighborList.LTECell."))
      {
         if(instance < 200)  //for fixing kworks
         {
            mio->Delete( instance);
         }
      }
      else
      {
         if (mio->check_if_instance_exist((u32)atoi(args[1].c_str())))
         {
            if(instance < 200)   //for fixing kworks
            {
               mio->Delete( instance );
               responseStream << "Object Deleted Instance ID:"<<(atoi(args[1].c_str()));
            }
         }
         else
         {
            responseStream << "Object Cannot be Deleted, Given instance doesn't exist";
         }    
      }

   }
   else
   {
      responseStream << "Object Cannot be Deleted, dn doesn't exist";
   }

   shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;      

   return response;
}

shared_ptr<CliResponse> Tr069CliCommands::CliCmdDownloadRequest(const CliArguments& args)
{
    ostringstream responseStream ;

    if(args.size() == 3)
    {
        std::string commandKey = "command_key";
        std::string fileUrl = args[2];
        std::string username = args[0];
        std::string password = args[1];
	
        u32 fileSize = 0;
        std::string targetFilename = "";
        std::string successUrl = "";
        std::string failureUrl = "";

        shared_ptr<DownloadRequest> downloadRequest(new DownloadRequest(
                    commandKey,
                    shared_ptr<FtpFile>(new FtpFile()),
                    0,
                    fileUrl,
                    username,
                    password,
                    fileSize,
                    targetFilename,
                    successUrl,
                    failureUrl ) );

        shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( downloadRequest ));
        Tr069Application::GetInstance().Enqueue(fsc);
        responseStream << "Download requested...";
    }
    else
    {
        responseStream << "Not correct number arguments.";
    }
    shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;
    return response;
}


shared_ptr<CliResponse> Tr069CliCommands::CliCmdClocks(const CliArguments& args)
{
   ostringstream responseStream ;

   if(args.size() == 1)
   {
      string newTimezone = args[0];

      responseStream <<
         "setenv TZ " << newTimezone << endl;

      setenv("TZ", newTimezone.c_str(), true);

      if(system("env") != oam_ret_zero)
      {
	TRACE_MSG("Tr069CliCommands::CliCmdClocks, System command env failed");
      }
   }

   TimeWrap now;
   time_t timer = time(NULL);
   struct tm * localTime = localtime ( &timer );

   if(NULL != localTime)
   {
      responseStream
         << "TimeWrap: " << now.ToString() << endl
         << "localtime: " << asctime(localTime) << endl;
   }

   shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;
   return response;
}

class CliTr069AlarmVisitor : public AlarmEventListVisitor
{
	public:
		CliTr069AlarmVisitor( string filename ) : m_file(NULL)
	{
		m_file = fopen( filename.c_str(), "w" );
	}
		CliTr069AlarmVisitor( ) : m_file(NULL) {}
		virtual ~CliTr069AlarmVisitor()
		{
			if(m_file)
			{
				fclose(m_file);
			}
		}

		void VisitAlarmEvent(const AlarmEvent& alarmEvent)
		{
			const char * severity[] = { "Cleared ", "Warning ", "Minor   ", "Major   ", "Critical" };
			const char * lifetime[] = { "TRANSIENT", "NON_TRANSIENT" };

			char buffer[200];

			if(m_file)
			{
				fprintf(m_file,\
						"<?xml version=\"1.0\" encoding=\"utf-8\"?>\
						\n<managedElement localDn=\"ManagedElement=HENB\" swVersion=\"2.1.0\" />\
						\n<AlarmSequenceNumber=\"%d\"/>\
						\n<AlarmObservationTime=\"%s\"/>\
						\n<AlarmLifetime=\"%s\"/>\
						\n<AlarmSeverity=\"%s\"/>\
						\n<AlarmId=\"%s\"/>\
						\n<AlarmAdditionalInfo=\"%s\"/>",
						alarmEvent.GetSequenceNumber(), alarmEvent.GetObservationTime().ToString().c_str(), lifetime[alarmEvent.GetLifetime()], severity[alarmEvent.GetSeverity()], (alarmEvent.GetAlarmId()->ToString().c_str()), alarmEvent.GetAdditionalInfo().c_str());
			}	
			else
			{
				snprintf( buffer, sizeof(buffer),
						"%"PRIu32" %s %c%s %s %s\n",
						alarmEvent.GetSequenceNumber(),
						alarmEvent.GetObservationTime().ToString().c_str(),
						AlarmEvent::ALARM_EVENT_TRANSIENT == alarmEvent.GetLifetime()? '~':' ',
						severity[alarmEvent.GetSeverity()],
						alarmEvent.GetAlarmId()->ToString().c_str(),
						alarmEvent.GetAdditionalInfo().c_str()
					);
				CliExecuteCmdInd cliInd( buffer );
				Tr069Application::GetInstance().SendMessage(cliInd, ENTITY_CLI, ENTITY_TR069);
			}
		}

	private:
		FILE * m_file;
};

shared_ptr <CliResponse> Tr069CliCommands::CliCmdAlarms(const CliArguments& args)
{
	ostringstream responseString;
	shared_ptr<CliTr069AlarmVisitor> visitor;

	if(args.size())
	{
		visitor.reset(new CliTr069AlarmVisitor(args[0]));
	}
	else
	{
		visitor.reset(new CliTr069AlarmVisitor);
	}

	Tr069Application::GetInstance().getAlarmManager()->AcceptAlarmEventLogVisitor( *visitor );

	shared_ptr<CliResponse> response (new CliResponse (responseString.str(), CLI_ERROR_NONE)) ;
	return response ;

}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdUploadFmFile(const CliArguments& args)
{
	ENTER();
	ostringstream responseStream ;
	ostringstream command;

	if(args.size() == 3)
	{
		std::string commandKey = "command_key";
		std::string fileUrl = args[2];
		std::string username = args[0];
		std::string password = args[1];
		std::string targetFilename = "";
		std::string successUrl = "";
		std::string failureUrl = "";

		command << "cp -rf " << fileUrl.c_str() << " /tmp/  && rm -rf  " << fileUrl.c_str();
		TRACE_PRINTF( "Command is %s", command.str().c_str() );
    		if(system(command.str().c_str()) != oam_ret_zero)
		{
		  TRACE_PRINTF("Command %s Failed", command.str().c_str() );
		}

		shared_ptr<UploadRequest> uploadRequest(new UploadRequest(
					commandKey,
					shared_ptr<FtpFile>(new FtpFile()),
					0,
					fileUrl,
					username,
					password ) );

		shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( uploadRequest ));
		Tr069Application::GetInstance().Enqueue(fsc);
		responseStream << "Upload requested...";
	}
	else
	{
		responseStream << "Not correct number arguments.";
	}

	shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;

    return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdGenPmFile(const CliArguments& args)
{

    ostringstream responseStream ;
    
    if(args.size() == 1)
    {
       if(Tr069Application::GetInstance().GeneratePmDataFile(args[0]))
       {
          responseStream << "PM file generated.." ;
       }
       else
       {
          responseStream << "PM file NOT generated..check logs" ;
       }	 
    }
    else
    {
       responseStream << "Invalid number of arguments, expected one";
    }
    
    shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;
    
    return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdGenAndUploadPmFile(const CliArguments& args)
{

    ostringstream responseStream ;
    
    if(args.size() == 1)
    {
       bool IfFileGenerated = Tr069Application::GetInstance().GeneratePmDataFile(args[0]);
       
       if(IfFileGenerated)
       {
          responseStream << "PM file generated and " ;
       
          if (std::system("pidof ftp-func >/dev/null 2>&1") == 0)
          {
             Tr069Application::GetInstance().UploadPmDataFile(args[0]);
             responseStream << "Upload requested...";
          }
          else
          {
             responseStream << "Att!! UploadPmDataFile is not performed as Application ftp-func is not running";
          }
       }
       else
       {
          responseStream << "PM file NOT generated..check logs" ;
       }	  
    }
    else
    {
       responseStream << "Invalid number of arguments, expected one";
    }   

    shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;
    
    return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdGenMibXmlAndUpload(const CliArguments& args)
{
    ostringstream responseStream;
    string paramString;
    string patternString;
    fstream filestr;
    
    if(args.size() == 1)
    {
       filestr.open (args[0].c_str(), fstream::in | fstream::out | fstream::app);
       filestr<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
       filestr<< "\n<?xml-stylesheet href=\"mine.xsl\" type=\"text/xsl\"?>";
       filestr<< "\n<MIB>";

       patternString = string("");

       //now need to actually do a search to see if we have this mib param.
       MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds(patternString, &MibHelper::LooseMatcher);

       if(not(ids.empty()))
       {
          for(MibAttributeIds::const_iterator id = ids.begin(); id != ids.end(); id++)
          {
             std::string attributeNameString = getMibAttributeName(*id);
  	     filestr<< "\n<ELEMENT>\n<ATTRIBUTE>";
	     filestr<<attributeNameString.c_str();
	     filestr<<"</ATTRIBUTE>";
             
	     if(MibHelper::GetMibAttributeDirectAsString(*id, paramString))
             {
		filestr<<"\n<VALUE>";
		filestr<<paramString.c_str();
		filestr<<"</VALUE>";
             }
             else
             {
		filestr<<"\n<VALUE>NOT SET</VALUE>";
             }
	    
	     filestr<<"\n</ELEMENT>";
         }
      }
    
      filestr<<"\n</MIB>";
      filestr.close();
    
      if (std::system("pidof ftp-func >/dev/null 2>&1") == 0)
      {
         Tr069Application::GetInstance().UploadPmDataFile(args[0]);
         responseStream << "MIB XML file upload is requested";
      }
      else
      {
        responseStream << "Att!! MIB XML is not performed as Application ftp-func is not running";
      }
    }
    else
    {
      responseStream << "Invalid number of arguments, expected one";
    }
    
    shared_ptr<CliResponse> response (new CliResponse(responseStream.str())) ;
    
    return response;
}

#ifdef PRODUCT_generic 
shared_ptr<CliResponse> Tr069CliCommands::CliCmdGetCoverage(const CliArguments& args)
{

    s32 result = CLI_ERROR_NONE;
    ostringstream responseStream ;
    
    responseStream << "Generating coverage for Tr069-v2";
    __gcov_flush();
    shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;
    
    return response;
}
#endif 

#if 0
shared_ptr <CliResponse> Tr069CliCommands::CliCmdActionReconnectOtherFgw(const CliArguments& args)
{
    shared_ptr<CliResponse> response;
    NsnParameterManager::GetInstance().SetParameter( NsnParameter::ActionReconnect, "2" );

    if( Tr069Reboot::GetInstance().QueryFapAboutToReboot() )
    {
        response.reset( new CliResponse( string("Attempting to Reconnect To Other Fgw, rebooting...")));
    }
    else
    {
        response.reset( new CliResponse( string("Attempting to Reconnect To Other Fgw ignored.")));
    }

    return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdActionReconnectPrimaryFgw(const CliArguments& args)
{
    shared_ptr<CliResponse> response;
    NsnParameterManager::GetInstance().SetParameter( NsnParameter::ActionReconnect, "1" );

    if( Tr069Reboot::GetInstance().QueryFapAboutToReboot() )
    {
        response.reset( new CliResponse( string("Attempting to Reconnect To Primary Fgw, rebooting...")));
    }
    else
    {
        response.reset( new CliResponse( string("Attempting to Reconnect To Primary Fgw ignored.")));
    }

    return response;
}
#endif

shared_ptr <CliResponse> Tr069CliCommands::CliCmdActionFactoryReset(const CliArguments& args)
{
   Tr069Application &app = Tr069Application::GetInstance();

   OamActionReq oamActionReq(OAM_ACTION_FACTORY_RESET);
   app.SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);

   shared_ptr<CliResponse> response(new CliResponse( string("Attempting Factory Reset, (forces reboot!)")));

   return response;
}

class StubHttpPostFsm : public Tr069FsmInterface
{
public:
    StubHttpPostFsm() :
        m_response("<no response>")
    {};
    virtual ~StubHttpPostFsm(){}

    virtual void HandleEvent(shared_ptr<threeway::Queueable> event)
    {
            shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

            if (tr069Event)
            {
                if(tr069Event->GetId() == Tr069QueueableEvent::HTTP_POST_REQ)
                {
                      shared_ptr<HttpPostRequest> httpPostRequest = dynamic_pointer_cast<HttpPostRequest>(tr069Event);

                      m_response = httpPostRequest->ToString();
                }
            }

    }
    virtual bool HandleTimerExpiry( threeway::TimerHandle expiredTimer){return true;}
    virtual bool GetBootEvent() { return false; }

    string GetResponse()
    {
        return m_response;
    }

private:
    string m_response;
};

shared_ptr <CliResponse> Tr069CliCommands::CliCmdSetParameterAttributeNotificationActive(const CliArguments& args)
{

    StubHttpPostFsm stubFsm;

    RpcSetParameterAttribute spa;
    spa.Add( args[0], 2);

    Tr069Application::GetInstance().GetParameterAttributeManager()->HandleSetParamAttributes( stubFsm, spa);

    shared_ptr<CliResponse> response(new CliResponse( stubFsm.GetResponse() ));

    return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdSetParameterAttributeNotificationPassive(const CliArguments& args)
{

    StubHttpPostFsm stubFsm;

    RpcSetParameterAttribute spa;
    spa.Add( args[0], 1);

    Tr069Application::GetInstance().GetParameterAttributeManager()->HandleSetParamAttributes( stubFsm, spa);

    shared_ptr<CliResponse> response(new CliResponse( stubFsm.GetResponse() ));

    return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdSetParameterAttributeNotificationOff(const CliArguments& args)
{

    StubHttpPostFsm stubFsm;

    RpcSetParameterAttribute spa;
    spa.Add( args[0], 0);

    Tr069Application::GetInstance().GetParameterAttributeManager()->HandleSetParamAttributes( stubFsm, spa);

    shared_ptr<CliResponse> response(new CliResponse( stubFsm.GetResponse() ));

    return response;
}

shared_ptr<CliResponse> Tr069CliCommands::CliCmdSetParameterValue(const CliArguments& args)
{
   string result ;
   bool Ok = DataModelManager::GetInstance().HandleCliSetParameterValue(args[0],args[1],result);
   shared_ptr<CliResponse> response;
   if(!Ok)
   {
      response.reset(new CliResponse(result));
   }
   else
   {
      response.reset(new CliResponse("" ));
   }
   return response;
}

shared_ptr <CliResponse> Tr069CliCommands::CliCmdGetParameterValue(const CliArguments& args)
{
   MibAttributeId attr;
   char dn[100];
   string name;
   std::string resultString(""),strVal;

   name = args[0];
   if(name.at(name.length()-1) == '.')
   {
      std::vector<MibAttributeId> attrIds;
      std::vector<std::string> mibDNs;
      std::vector<std::string> names;
      DataModelManager::GetInstance().getAllAttrInfo(name.c_str(),names,attrIds,mibDNs);

      if(names.size())
      {
         for(u32 i=0;i<names.size();i++)
         { 
            if(Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent( MibDN::GenerateMibDN(mibDNs[i]), attrIds[i]))
            {
               Tr069Application::GetInstance().GetMibCache().GetMibAttributeAsString(
                     MibDN::GenerateMibDN(mibDNs[i].c_str()), attrIds[i], strVal);
               resultString=resultString+"\n"+names[i]+"  "+strVal;
            }
         }
      }
      else
      {
         resultString = "Error : string for get not found.";
      }
   }
   else
   {
      TRACE_PRINTF("paramneme %s",args[0].c_str()); 

      if((DataModelManager::GetInstance().getAttrInfo(args[0].c_str(),attr,dn)) == FALSE)
      {
         resultString = "Error : string for get not found.";
         shared_ptr<CliResponse> response(new CliResponse( resultString));
         return response;
      }

      if(Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent( MibDN::GenerateMibDN(dn), attr))
      {
         Tr069Application::GetInstance().GetMibCache().GetMibAttributeAsString(MibDN::GenerateMibDN(dn), attr, strVal);
         resultString=strVal;
      }
      else
      {
         resultString = "Error : string for get not found.";
      }
   }
   shared_ptr<CliResponse> response(new CliResponse( resultString));
   return response;
}
