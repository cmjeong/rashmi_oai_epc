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
#include <fstream>
#include <system/Trace.h>
#include <comms/TOSValues.h>
#include <nanohttp/nanohttp-server.h>
#include <nanohttp/nanohttp-request.h>
#include <fstream>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069TcpConnectInd.h"
#include "Tr069SocketServer.h"

using namespace std;
using namespace threeway;
using namespace tr069;

extern "C"
{
    extern void httpd_term(int sig);
}

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

int authorize_conn_req(hrequest_t * req, const char *user, const char *password)
{
    string connReqUsername;
    string connReqPassword;
    string suppliedUsername;
    string suppliedPassword;

    Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_TR069_CONNECTION_REQUEST_USERNAME, connReqUsername);
    Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_TR069_CONNECTION_REQUEST_PASSWORD, connReqPassword);

    if (!connReqUsername.compare(""))
    {
        return 1;
    }

    if (!user)
    {
        suppliedUsername = "";
    }
    else
    {
        suppliedUsername = user;
    }
    if(!password)
    {
       suppliedPassword = "";
    }
    else
    {
       suppliedPassword = password;
    }


    TRACE_PRINTF("HTTPD AUTH user(%s == %s) pass (%s == %s)", connReqUsername.c_str(), suppliedUsername.c_str(), connReqPassword.c_str(), suppliedPassword.c_str());
    if (!connReqUsername.compare(suppliedUsername) && !connReqPassword.compare(suppliedPassword))
    {
        return 1;
    }
    return 0;
}
#if 0
static void no_service(httpd_conn_t *conn, hrequest_t *req)
{
    TRACE_PRINTF("Attempt made to connect to invalid URL. Sending HTTP/1.1 503 Service Unavailable");

    conn->out = http_output_stream_new(conn->sock, NULL);

    std::ostringstream response;
    response <<
    "HTTP/1.1 503 Service Unavailable\r\n\r\n";

    http_output_stream_write_string(conn->out,
           response.str().c_str() );

    return;
}
#endif

static void fap_service(httpd_conn_t *conn, hrequest_t *req)
{
    Tr069Application &app = Tr069Application::GetInstance();

    TRACE_PRINTF("Connection to valid URL. Sending HTTP/1.1 200 OK");

    conn->out = http_output_stream_new(conn->sock, NULL);

    string dateAndTime;

    std::ostringstream response;
    response <<
    "HTTP/1.1 200 OK\r\n"
    "Date: "<< app.GetFormattedCurrentTime(dateAndTime) << "\r\n"
    "Server: FAP/CPE\r\n"
    "Content-Length: 0\r\n\r\n";

    http_output_stream_write_string(conn->out,
           response.str().c_str() );

    /*shared_ptr<TcpConnectInd> tcpConnectInd(new TcpConnectInd());
    app.Enqueue(tcpConnectInd);*/
    
    shared_ptr<ConnectionRequest> connectionRequest(new ConnectionRequest());
    shared_ptr<TransactionSessionCommand> transactionSessionCommand(new TransactionSessionCommand( connectionRequest ));
    app.Enqueue(transactionSessionCommand);

    return;
}

Tr069SocketServer* Tr069SocketServer::s_instance = NULL;

Tr069SocketServer& Tr069SocketServer::GetInstance(const IPv4Address & localIpAddress)
{
    ENTER();

    if (s_instance == NULL)
    {
        TRACE_PRINTF("New Tr069SocketServer");
        s_instance = new Tr069SocketServer(localIpAddress);

        RSYS_ASSERT(s_instance);
    }
    else
    {
        RSYS_ASSERT(s_instance->m_localIpAddress == localIpAddress);
    }

    RETURN (*s_instance);
}

Tr069SocketServer::Tr069SocketServer( const IPv4Address & localIpAddress ) :
    ThreadWithQueue("Tr069SocketServer"),
    m_localIpAddress(localIpAddress)
{
}

Tr069SocketServer::~Tr069SocketServer()
{
    httpd_term(2);

    WaitForThreadToExit();
}

u32 Tr069SocketServer::ThreadProcedure()
{
   //RSYS_ASSERT(QOS_CLASS_E == 20); // Explicit check that this hasn't changed as we assume it in string below.

   //check certificate path
   char strCert[100];
   std::string certPath;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_TLS_CERT_PATH,certPath);
   //copy certificate path
   snprintf(strCert,sizeof(strCert),"%s",certPath.c_str());

   ifstream filePres(certPath.c_str());

   if(filePres)
   {

      const char *argv[] = {"listener",
         NHTTPD_ARG_PORT, "7547",
         NHTTP_ARG_CERT, strCert,
         NHTTPD_ARG_ADDRESS, "INADDR_ANY",
         NHTTPD_ARG_MAXCONN, "1",
         "TOS", "20" // O&M QoS ToS - corresponds to QOS_CLASS_E - assert above ensures we validate this!
      };
      {
         const herror_t success = H_OK;
         herror_t result = httpd_init( sizeof(argv)/sizeof(argv[0]) , (char **)argv );

         RSYS_ASSERT_PRINTF( result == success, "Failed httpd_init (%p)", result);
      }

   }
   else
   {

      const char *argv[] = {"listener",
         NHTTPD_ARG_PORT, "7547",
         NHTTPD_ARG_ADDRESS, "INADDR_ANY",
         NHTTPD_ARG_MAXCONN, "1",
         "TOS", "20" // O&M QoS ToS - corresponds to QOS_CLASS_E - assert above ensures we validate this!
      };
      {
         const herror_t success = H_OK;
         herror_t result = httpd_init( sizeof(argv)/sizeof(argv[0]) , (char **)argv );

         RSYS_ASSERT_PRINTF( result == success, "Failed httpd_init (%p)", result);
      }
   }


   {
      const int success = 1;
      int result = httpd_register_default("", fap_service);

      RSYS_ASSERT_PRINTF( result == success, "Failed httpd_register_default (%"PRId32")", result);
   }

   {
      string urlAbsolutePath = Tr069Application::GetInstance().GetFapUrlAbsolutePath();
      const int success = 1;
      //int result = httpd_register_secure(urlAbsolutePath.c_str(), fap_service,authorize_conn_req);
      int result = httpd_register(urlAbsolutePath.c_str(), fap_service);

      RSYS_ASSERT_PRINTF( result == success, "Failed httpd_register (%"PRId32")", result);
   }

   {
      const herror_t success = H_OK;
      herror_t result = httpd_run();

      RSYS_ASSERT_PRINTF( result == success, "Failed httpd_run (%p)", result);
   }

   httpd_destroy();

   TRACE_PRINTF("Stopping thread SocketsListener");

   return 0;
}






}

