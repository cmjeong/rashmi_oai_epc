///////////////////////////////////////////////////////////////////////////////
//
// <File name>
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

/** DELETE THIS
 * Use this template for C++ source files.
 *  - Delete sections below that are empty (to make it easier to read).
 */

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <string.h>
#include <system/Trace.h>
#include <libcsoap/soap-server.h>
#include <nanohttp/nanohttp-client.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069Parser.h"
#include "Tr069XmlNodeString.hpp"


using namespace std;
using namespace boost;
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

Tr069ParseParameterNames::Tr069ParseParameterNames(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "ParameterNames\n");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "string"))
        {
           XmlNodeString xmlString(cur);
           if(! (xmlString.str().empty()) )
           {
              aString.push_back( xmlString.str() );
              TRACE_PRINTF("TR069-Parse:" "string=%s", aString.back().c_str());
           }
           else
           {
              aString.push_back( "Device." );
              TRACE_PRINTF("TR069-Parse:" "string=Empty, hence considering it as `Device.`");
           }
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseParameterAttributeStruct::Tr069ParseParameterAttributeStruct(xmlNodePtr cur)
{

    TRACE_PRINTF("TR069-Parse:" "ParameterAttributeStruct");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "Name"))
        {
            XmlNodeString xmlString(cur);

            name = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "Name=%s", name.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "NotificationChange"))
        {
            XmlNodeString xmlString(cur);

            notificationChange = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "NotificationChange=%s", notificationChange.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "Notification"))
        {
            XmlNodeString xmlString(cur);

            notification = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "Notification=%s", notification.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "AccessListChange"))
        {
            XmlNodeString xmlString(cur);

            accessListChange = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "AccessListChange=%s", accessListChange.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "AccessList"))
        {
            XmlNodeString xmlString(cur);

            accessList = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "AccessList=%s", accessList.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }
        cur = cur->next;
    }
}

Tr069ParseParameterAttributeList::Tr069ParseParameterAttributeList(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "ParameterList");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "SetParameterAttributesStruct"))
        {
            parameterAttributeStruct.push_back( shared_ptr<Tr069ParseParameterAttributeStruct>(new Tr069ParseParameterAttributeStruct(cur)) );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseGetParameterValues::Tr069ParseGetParameterValues(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "GetParameterValues");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "ParameterNames"))
        {
            parameterNames = shared_ptr<Tr069ParseParameterNames>(new Tr069ParseParameterNames(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseGetParameterAttributes::Tr069ParseGetParameterAttributes(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "GetParameterAttributes");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "ParameterNames"))
        {
            parameterNames = shared_ptr<Tr069ParseParameterNames>(new Tr069ParseParameterNames(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseGetParameterNames::Tr069ParseGetParameterNames(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "GetParameterNames");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "ParameterPath"))
        {
            parameterPath = XmlNodeString(cur).str();
        }
        else if(!strcmp((const char*)cur->name, "NextLevel"))
        {
            nextLevel = XmlNodeString(cur).str();
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseGetRpcMethods::Tr069ParseGetRpcMethods(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "GetRpcMethods");
}

Tr069ParseSetParameterAttributes::Tr069ParseSetParameterAttributes(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "SetParameterAttributes");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "ParameterList"))
        {
            parameterList = shared_ptr<Tr069ParseParameterAttributeList>(new Tr069ParseParameterAttributeList(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}


Tr069ParseInformResponse::Tr069ParseInformResponse(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "InformResponse");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "MaxEnvelopes"))
        {
            XmlNodeString xmlString(cur);

            maxEnvelopes = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "MaxEnvelopes=%s", maxEnvelopes.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseTransferCompleteResponse::Tr069ParseTransferCompleteResponse(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "TransferCompleteResponse");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "dummy"))
        {
            XmlNodeString xmlString(cur);

            dummy = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "dummy=%s", dummy.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseDownload::Tr069ParseDownload(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Download");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "CommandKey"))
        {
            XmlNodeString xmlString(cur);

            commandKey = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "CommandKey=%s", commandKey.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "FileType"))
        {
            XmlNodeString xmlString(cur);

            fileType = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "FileType=%s", fileType.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "URL"))
        {
            XmlNodeString xmlString(cur);

            url = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "URL=%s", url.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "Username"))
        {
            XmlNodeString xmlString(cur);

        	username = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "Username=%s", username.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "Password"))
        {
            XmlNodeString xmlString(cur);

        	password = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "Password=%s", password.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "FileSize"))
        {
            XmlNodeString xmlString(cur);

        	fileSize = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "FileSize=%s", fileSize.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "TargetFileName"))
        {
            XmlNodeString xmlString(cur);

        	targetFileName = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "TargetFileName=%s", targetFileName.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "DelaySeconds"))
        {
            XmlNodeString xmlString(cur);

        	delaySeconds = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "DelaySeconds=%s", delaySeconds.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "SuccessURL"))
        {
            XmlNodeString xmlString(cur);

        	successUrl = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "SuccessURL=%s", successUrl.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "FailureURL"))
        {
            XmlNodeString xmlString(cur);

        	failureUrl = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "FailureURL=%s", failureUrl.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseFaultDetail::Tr069ParseFaultDetail(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Fault");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "FaultCode"))
        {
            XmlNodeString xmlString(cur);

            faultcode = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "FaultCode=%s", faultcode.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "FaultString"))
        {
            XmlNodeString xmlString(cur);

            faultstring = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "FaultString=%s", faultstring.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseDetail::Tr069ParseDetail(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Detail");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "Fault"))
        {
            faultDetail = shared_ptr<Tr069ParseFaultDetail>(new Tr069ParseFaultDetail(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseFactoryReset::Tr069ParseFactoryReset(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "FactoryReset");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);

        cur = cur->next;
    }
}

Tr069ParseFault::Tr069ParseFault(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Fault");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "faultcode"))
        {
            XmlNodeString xmlString(cur);

            faultcode = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "faultcode=%s", faultcode.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "faultstring"))
        {
            XmlNodeString xmlString(cur);

            faultstring = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "faultstring=%s", faultstring.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "faultactor"))
        {
            XmlNodeString xmlString(cur);

            faultactor = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "faultactor=%s", faultactor.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "detail"))
        {
            detail = shared_ptr<Tr069ParseDetail>(new Tr069ParseDetail(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseReboot::Tr069ParseReboot(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Reboot");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "CommandKey"))
        {
            XmlNodeString xmlString(cur);

            commandKey = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "CommandKey=%s", commandKey.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseUpload::Tr069ParseUpload(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Upload");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "CommandKey"))
        {
            XmlNodeString xmlString(cur);

            commandKey = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "CommandKey=%s", commandKey.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "FileType"))
        {
            XmlNodeString xmlString(cur);

            fileType = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "FileType=%s", fileType.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "URL"))
        {
            XmlNodeString xmlString(cur);

            url = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "URL=%s", url.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "Username"))
        {
            XmlNodeString xmlString(cur);

            username = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "Username=%s", username.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "Password"))
        {
            XmlNodeString xmlString(cur);

            password = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "Password=%s", password.c_str() );
        }
        else if(!strcmp((const char*)cur->name, "DelaySeconds"))
        {
            XmlNodeString xmlString(cur);

            delaySeconds = xmlString.str();

            TRACE_PRINTF("TR069-Parse:" "DelaySeconds=%s", delaySeconds.c_str() );
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseBody::Tr069ParseBody(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" "Body");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "AddObject"))
        {
            addObject = shared_ptr<AddObject>(new AddObject(cur));
        }
        else if(!strcmp((const char*)cur->name, "DeleteObject"))
        {
            deleteObject = shared_ptr<DeleteObject>(new DeleteObject(cur));
        }
        else if(!strcmp((const char*)cur->name, "SetParameterValues"))
        {
            setParameterValues = shared_ptr<SetParameterValues>(new SetParameterValues(cur));
        }
        else if(!strcmp((const char*)cur->name, "SetParameterAttributes"))
        {
            setParameterAttributes = shared_ptr<Tr069ParseSetParameterAttributes>(new Tr069ParseSetParameterAttributes(cur));
        }
        else if(!strcmp((const char*)cur->name, "InformResponse"))
        {
            informResponse = shared_ptr<Tr069ParseInformResponse>(new Tr069ParseInformResponse(cur));
        }
        else if(!strcmp((const char*)cur->name, "GetParameterValues"))
        {
            getParameterValues = shared_ptr<Tr069ParseGetParameterValues>(new Tr069ParseGetParameterValues(cur));
        }
        else if(!strcmp((const char*)cur->name, "GetParameterNames"))
        {
            getParameterNames = shared_ptr<Tr069ParseGetParameterNames>(new Tr069ParseGetParameterNames(cur));
        }
        else if(!strcmp((const char*)cur->name, "GetParameterAttributes"))
        {
            getParameterAttributes = shared_ptr<Tr069ParseGetParameterAttributes>(new Tr069ParseGetParameterAttributes(cur));
        }
        else if (!strcmp((const char*)cur->name, "GetRPCMethods"))
        {
            getRpcMethods = shared_ptr<Tr069ParseGetRpcMethods>(new Tr069ParseGetRpcMethods(cur));
        }
        else if(!strcmp((const char*)cur->name, "Download"))
        {
            download = shared_ptr<Tr069ParseDownload>(new Tr069ParseDownload(cur));
        }
        else if(!strcmp((const char*)cur->name, "FactoryReset"))
        {
            factoryReset = shared_ptr<Tr069ParseFactoryReset>(new Tr069ParseFactoryReset(cur));
        }
        else if(!strcmp((const char*)cur->name, "Fault"))
        {
            fault = shared_ptr<Tr069ParseFault>(new Tr069ParseFault(cur));
        }
        else if(!strcmp((const char*)cur->name, "TransferCompleteResponse"))
        {
            transferCompleteResponse = shared_ptr<Tr069ParseTransferCompleteResponse>(new Tr069ParseTransferCompleteResponse(cur));
        }
        else if(!strcmp((const char*)cur->name, "Reboot"))
        {
            reboot = shared_ptr<Tr069ParseReboot>(new Tr069ParseReboot(cur));
        }
        else if(!strcmp((const char*)cur->name, "Upload"))
        {
            upload = shared_ptr<Tr069ParseUpload>(new Tr069ParseUpload(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}

Tr069ParseHeader::Tr069ParseHeader(xmlNodePtr cur)
{
   TRACE_PRINTF("TR069-Parse:" "Header");

   /* We don't care what the top level element name is */
   cur = cur->xmlChildrenNode;

   while (cur != NULL)
   {
      if(!strcmp((const char*)cur->name, "HoldRequests"))
      {
         XmlNodeString xmlString(cur);

         holdRequests = xmlString.str();

         TRACE_PRINTF("TR069-Parse:" "HoldRequests=%s", holdRequests.c_str() );
      }
      else if((strstr((const char*)cur->name,"ID")) != NULL)
      {
         XmlNodeString xmlString(cur);

         cwmp_Id = xmlString.str();

         TRACE_PRINTF("TR069-Parse:" "CWMP:ID=%s", cwmp_Id.c_str() );
      }
      else
      {
         TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
      }

      cur = cur->next;
   }
}

Tr069Parse::Tr069Parse(xmlNodePtr cur)
{
    TRACE_PRINTF("TR069-Parse:" ">>");
    TRACE_PRINTF("TR069-Parse:" "Envelope");

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        if(!strcmp((const char*)cur->name, "Body"))
        {
            body = shared_ptr<Tr069ParseBody>(new Tr069ParseBody(cur));
        }
        else if(!strcmp((const char*)cur->name, "Header"))
        {
            header = shared_ptr<Tr069ParseHeader>(new Tr069ParseHeader(cur));
        }
        else
        {
            TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
        }

        cur = cur->next;
    }
}



}
