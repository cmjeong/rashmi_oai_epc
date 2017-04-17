///////////////////////////////////////////////////////////////////////////////
//
// Tr)69ContactConfigServerProcFsm.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <system/Trace.h>
#include <libcsoap/soap-server.h>
#include <nanohttp/nanohttp-client.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069HttpPostResponse.h"

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

SoapCtx * HttpPostResponse::initSoapCtx(SoapEnv * soapEnv)
{
    SoapCtx * soapCtx = NULL;

    if(soapEnv)
    {
        soapCtx = soap_ctx_new(soapEnv);

        if(soapCtx)
        {
            xmlBufferPtr buffer = xmlBufferCreate();

            xmlDocPtr doc = soapCtx->env->root->doc;
            xmlNodePtr cur = soapCtx->env->root;

            xmlNodeDump(buffer, doc, cur, 1, 0 );

            m_post += (const char *) xmlBufferContent(buffer);

            xmlBufferFree(buffer);

            parsed = shared_ptr<Tr069Parse>(new Tr069Parse(cur));
        }
    }

    return soapCtx;
 }


HttpPostResponse::HttpPostResponse(hresponse_t  * response) :
    Tr069QueueableEvent(TR069_EVENT(HTTP_POST_RES), TRANSACTION_SESSION_FSM),
    m_SoapCtx(NULL),responseErrCode(200)
{
   /* Create Response Context */
   if( response &&
         response->in &&
         response->in->type != HTTP_TRANSFER_CONNECTION_CLOSE &&
         response->in->content_length != 0 )
   {
      SoapEnv * soapEnv = NULL;

      soap_env_new_from_stream(response->in, &soapEnv);

      m_SoapCtx = initSoapCtx(soapEnv);
   }
   else
   {
      SoapEnv * soapEnv = NULL;

      soap_env_new_from_buffer("<empty/>", &soapEnv);

      m_SoapCtx = initSoapCtx(soapEnv);

      if(response)
      {
         std::string digestValues;
         responseErrCode = response->errcode ; 
         int fh = response->errcode;
         TRACE_PRINTF("TR069:httpPostWithResponse REsponse ERR Code = %d desc=%s", responseErrCode,response->desc);
         TRACE_PRINTF("TR069:httpPostWithResponse SECOND REsponse ERR Code = %d desc=%s", responseErrCode,response->desc);
         if(fh ==401)
            TRACE_PRINTF("TR069:httpPostWithResponse REsponse ERR Code = %d desc=%s", responseErrCode,response->desc);
         if(responseErrCode == fh )
         {
            if(response->header != NULL)
            {
               do
               {
                  if(responseErrCode == 401)

                     if(strcmp(response->header->key,"WWW-Authenticate") == 0)
                     { 
                        digestValues = response->header->value;

                        TRACE_PRINTF("TR069:httpPostWithResponse digestValues %s ", digestValues.c_str());
                        updateMap(digestValues);
                        break;
                     }
                  response->header = response->header->next;
               }while(response->header->next);
            }
         }
         if(response->in)
         {
            TRACE_PRINTF("TR069:httpPostWithResponse end. (HTTP_TRANSFER_CONNECTION_CLOSE).");
         }
         else
         {
            TRACE_PRINTF("TR069:httpPostWithResponse failure (No response->in).");
         }
      }
      else
      {
         TRACE_PRINTF("TR069:httpPostWithResponse failure (No response).");
      }
   }
}

void HttpPostResponse::updateMap(string digestValues)
{
   TRACE_PRINTF("%s",__func__);

   char * token;
   string key,value,tokenStr;

   std::size_t pos = digestValues.find("realm"); // Remove the word Digest from the start of string
   string auth = digestValues.substr(0, pos-1);

   digestValues = digestValues.substr(pos);
   char * valuesChar = new char[digestValues.size() + 1];
   std::copy(digestValues.begin(), digestValues.end(), valuesChar);
   valuesChar[digestValues.size()] = '\0';
   token = strtok(valuesChar,", ");//Token is comma and space
   while(token != NULL)
   {
      TRACE_PRINTF("TR069:updateMap, token = %s",token);
      tokenStr = token;
      key = tokenStr.substr(0,tokenStr.find("="));
      value = tokenStr.substr(tokenStr.find("=")+2); //Value has to be without quotes
      if(value.size()>0)
      {
         value.resize(value.size()-1);
      }
      digestMap[key] = value;
      TRACE_PRINTF("TR069:updateMap  key = %s value = %s",key.c_str(), value.c_str());
      token = strtok(NULL,",");
   }				
   Tr069Application::GetInstance().SetDigestAttribute(digestMap, auth);
}
