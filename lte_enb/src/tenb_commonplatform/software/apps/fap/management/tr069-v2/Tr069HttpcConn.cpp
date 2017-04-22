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
#include <string.h>
#include <system/Trace.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <comms/TOSValues.h>
#include <errno.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069QueueableEvent.h"
#include "Tr069SocketsInterface.h"
#include "md5.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
#define MAX_RETRY_COUNT 10

//TLS changes
#ifdef ENABLE_CSOAP_DEBUG
#include <nanohttp/nanohttp-logging.h>
#endif

#if !defined(TR069_SSL_CERT_CLIENT)
#define TR069_SSL_CERT_CLIENT "/root/server/cert.pem"
#endif

#if !defined(TR069_SSL_CERT_CA)
#define TR069_SSL_CERT_CA "/root/server/client_ca.crt"
#endif

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

bool HttpcConn::hsocket_open_ipsec(hsocket_t * dsock, const char *hostname, int port)
{
   struct sockaddr_in address;
   struct sockaddr_in localInnerIpAddr;
   struct hostent *host = NULL;
   char *ip = NULL;


   memset( &address, 0, sizeof(address) );
   memset( &localInnerIpAddr, 0, sizeof(localInnerIpAddr));

   if ((dsock->sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
   {
      TRACE_PRINTF("TR069:hsocket_open_ipsec[socket] failure.");
      return false;
   }

   // getsockopt call is need only to prevent setsockopt to fail
   {
      int getVal = 0;
      socklen_t len = sizeof(getVal);
      getsockopt(dsock->sock, SOL_SOCKET, IP_TOS, &getVal, &len );
   }

   int val = (int)QOS_CLASS_E; //O&M
   int err = setsockopt(dsock->sock, SOL_IP, IP_TOS, &val, ((socklen_t)sizeof(val)) );
   if (err<0)
   {
      TRACE_PRINTF("(TR069) Error setting setsockopt for TOS (%d)", err);
      return false;
   }

   /*ccpu00131180: Fix for TR069 client at eNB not sending the Inform immediately for 
     Active Parameter Notifications */
   struct linger so_linger;
   so_linger.l_onoff = true;
   so_linger.l_linger = 0;
   err = setsockopt(dsock->sock, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger);
   if (err<0)
   {
      TRACE_PRINTF("(TR069) Error setting setsockopt LINGER for TOS (%d)", err);
      return false;
   }

   /* Get host data */
   if (!(host = gethostbyname(hostname)))
   {
      TRACE_PRINTF("TR069:hsocket_open_ipsec[gethostbyname] failure.");
      return false;
   }


   ip = inet_ntoa(*(struct in_addr *) *host->h_addr_list);
   address.sin_addr.s_addr = inet_addr(ip);

   /* set server address */
   address.sin_family = host->h_addrtype;
   address.sin_port = htons((unsigned short) port);

   localInnerIpAddr.sin_family = AF_INET;
   localInnerIpAddr.sin_port = 0;//htons(7547);
   localInnerIpAddr.sin_addr.s_addr = m_localIpaddress.Get();

   u32 retryCount = 1;
   bool bindsuccess = false;
   while( MAX_RETRY_COUNT > retryCount && !bindsuccess )
   {
      if (bind(dsock->sock, (struct sockaddr *) &localInnerIpAddr, sizeof(struct sockaddr)) == -1)
      {
         retryCount++;
         TRACE_PRINTF("TR069:hsocket_open_ipsec[bind to %s] failure(%i, ErrNo:%d(%s)) Retrying(%d)", m_localIpaddress.ToString(),err, errno, strerror( errno ), retryCount);
         sleep(5); 
      }
      else
      { 
         TRACE_PRINTF("connection to %s:%u", ip,port);
         TRACE_PRINTF("successful bind to %s:%d", inet_ntoa(localInnerIpAddr.sin_addr), ntohs(localInnerIpAddr.sin_port));
         bindsuccess = true;
      } 
   }

   if(!bindsuccess)
   { 
      return false;
   }

   if (connect(dsock->sock, (struct sockaddr *) &address, sizeof(address)) != 0)
   {
      TRACE_PRINTF("TR069:hsocket_open_ipsec[connect] failure (%i, %s).", err, strerror( errno ) );

      return false;
   }
   else
   { 
      TRACE_PRINTF("Connected to %s:%d", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
   }

   return true;;
}

const int HttpcConn::PostReplyTimeoutInSeconds = 30;

bool HttpcConn::Connect(const string & url )
{
   char strCert[200];
   char strCa[200];
   char strKey[200];
   std::string certPath;
   std::string caPath;
   std::string keyPath;
   bool connectedOk = false;
   herror_t error = NULL;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_TLS_CERT_PATH,certPath);
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_TLS_CERT_CA,caPath);
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_TLS_KEY_PATH,keyPath);
   snprintf(strCert,sizeof(strCert),"%s",certPath.c_str());
   ifstream clientCertFilePres(strCert);

   snprintf(strCa,sizeof(strCa),"%s",caPath.c_str());
   ifstream clientCAPres(strCa);

   snprintf(strKey,sizeof(strKey),"%s",keyPath.c_str());
   ifstream clientKeyPres(strKey);
   ostringstream command;

   if(clientCertFilePres && clientCAPres && clientKeyPres)
   {
      const char *argv[] = {
         NHTTP_ARG_HTTPS, "1",
         NHTTP_ARG_CERT, strCert,
         NHTTP_ARG_CA, strCa,
         NHTTP_ARG_KEY,strKey
      };
      error = httpc_init(sizeof(argv) / sizeof(argv[0]), (char**)argv);
   }
   else
   {
      TRACE_PRINTF("\nCERTIFIACTES NOT FOUND");
      error = H_OK;
   }

#ifdef ENABLE_CSOAP_DEBUG
   hlog_set_level(HLOG_VERBOSE);
#endif

   if (error != H_OK)
   {
      TRACE_PRINTF("TR069:httpc_init failure (%s)", herror_message(error));
      herror_release(error);
      return false;
   }

   m_url = url;

   error = hurl_parse(&m_hurl, m_url.c_str());
   if (error != H_OK)
   {
      TRACE_PRINTF("Invalid URL:%s",m_url.c_str());
      herror_release(error);
      httpc_destroy();
      return false;
   }
   string vendor("RADISYS");
   if (Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(
            MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING),
            PARAM_ID_GATEWAY_VENDOR))
   {
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(
            MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING),
            PARAM_ID_GATEWAY_VENDOR,vendor);
   }

   TRACE_PRINTF("TR069:hsocket_open (%s:%d)",m_hurl.host, m_hurl.port);

   m_conn = httpc_new();

   if(m_conn)
   {
      error = hsocket_open(&m_conn->sock,
            m_hurl.host,
            m_hurl.port,
            m_hurl.protocol);

      if(error != H_OK)
      {
         error = hsocket6_open(&m_conn->sock6,
               m_hurl.host,
               m_hurl.port,
               m_hurl.protocol);
      }

      if (error == H_OK)
      {
         TRACE_PRINTF("TR069:hsocket_open success %s:%d",
               m_hurl.host,
               m_hurl.port);
         connectedOk = true;
         // The default timeout is 10s - which may be too quick for our poor
         // old over-worked FGW to cope with.
         httpd_set_timeout(PostReplyTimeoutInSeconds);
      }
      else
      {
         TRACE_PRINTF("TR069:hsocket_open failure %s:%d (%s)",
               m_hurl.host,
               m_hurl.port,
               herror_message(error));
         herror_release(error);
      }
   }
   else
   {
      TRACE_PRINTF("TR069:httpc_new failure %s:%d",
            m_hurl.host,
            m_hurl.port);
   }

   if (!connectedOk)
   {
      httpc_destroy();
   }
   return connectedOk;
}

void HttpcConn::Disconnect()
{
   m_url = "";
   if (m_conn)
   {
      httpc_close_free(m_conn);
      httpc_destroy();
      m_conn = NULL;
   }
}

void HttpcConn::SendTcpConnectionFailureInd()
{
   Tr069Application &app = Tr069Application::GetInstance();

   Disconnect();

   shared_ptr<TcpConnectionFailureInd> connectionFailureInd(new TcpConnectionFailureInd() );
   app.Enqueue(connectionFailureInd);
}

void HttpcConn::SendTcpConnectCnf()
{
   Tr069Application &app = Tr069Application::GetInstance();

   shared_ptr<TcpConnectCnf> connectCnf(new TcpConnectCnf() );
   app.Enqueue(connectCnf);
}



void HttpcConn::httpc_header_add_date(void)
{
   char buffer[32];
   time_t ts;
   struct tm stm;

   ts = time(NULL);
   localtime_r(&ts, &stm);
   strftime(buffer, 32, "%a, %d %b %Y %H:%M:%S GMT", &stm);

   httpc_add_header(m_conn, HEADER_DATE, buffer);

   return;
}

void HttpcConn::httpc_header_free( void )
{
   while (m_conn->header != NULL)
   {
      hpair_t *tmp = m_conn->header;
      m_conn->header = m_conn->header->next;
      hpairnode_free(tmp);
   }
}
 
void CvtHex
(
      unsigned char *Bin,
      char *Hex
      )
{
   unsigned short i;
   unsigned char j;

   for (i = 0; i < 16; i++) {
      j = (Bin[i] >> 4) & 0xf;
      if (j <= 9)
         Hex[i*2] = (j + '0');
      else
         Hex[i*2] = (j + 'a' - 10);
      j = Bin[i] & 0xf;
      if (j <= 9)
         Hex[i*2+1] = (j + '0');
      else
         Hex[i*2+1] = (j + 'a' - 10);
   };
   Hex[32] = '\0';
};

void HttpcConn::httpc_header_new(
      hreq_method_t method,
      size_t txContentLength,
      std::string & txMessage )
{
   TRACE_PRINTF("%s:%d",__func__, __LINE__);

   static u32 cnt = 0;
   int idx = 0;
   string header;
   Url url;

   if(m_conn->header)
   {
      httpc_header_free();
   }

   string vendor("RADISYS");
   if( Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING),PARAM_ID_GATEWAY_VENDOR) )
   {
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), PARAM_ID_GATEWAY_VENDOR, vendor );
   }

   if(txContentLength > 0)
   {
      httpc_add_header(m_conn, HEADER_CONTENT_TYPE, "text/xml");
   }

   string cpeusername("cpe");
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_MANAGEMENT_USERNAME, cpeusername);

   string cpepassword("cpe");
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_MANAGEMENT_PASSWORD, cpepassword);

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_MANAGEMENT_SERVER, url);
   const string url1 = url.Get();
   if(H_OK != hurl_parse( &m_hurl, url1.c_str()))
   {
      TRACE_PRINTF("Invalid URL:%s",url1.c_str());
   }

   if( 0 == vendor.compare("RADISYS") )
   {
      httpc_add_header(m_conn, "Cookie", "Cookie");//key = Cookie, is valid but Value = Cookie, is just a dummy value
      string authMethod = Tr069Application::GetInstance().GetAuthMethod();
      if(0 == strcmp(authMethod.c_str(), "Digest"))
      {
         string digestRealm = Tr069Application::GetInstance().GetDigestAttribute("realm");

         string qop = Tr069Application::GetInstance().GetDigestAttribute(" qop");
         string nonce = Tr069Application::GetInstance().GetDigestAttribute(" nonce");
         if((m_hurl.context[0] == '/') && (m_hurl.context[1] == '/'))
         {
            while(m_hurl.context[idx] != '\0')
            {
               m_hurl.context[idx] = m_hurl.context[idx + 1];
               idx++;
            }
         }
         string uri = m_hurl.context;
         string opaque = Tr069Application::GetInstance().GetDigestAttribute(" opaque");
         const char* nc = "00000001"; //Digest Value TODO
         const char* cnonce = "0a4f113b";//Digest Value TODO
         char SessionKey[33];
         MD5_CTX Md5Ctx;
         unsigned char HA1[33];

         MD5Init(&Md5Ctx);
         MD5Update(&Md5Ctx, cpeusername.c_str(), strlen(cpeusername.c_str()));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, digestRealm.c_str(), strlen(digestRealm.c_str()));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, cpepassword.c_str(), strlen(cpepassword.c_str()));
         MD5Final(HA1, &Md5Ctx);
         CvtHex(HA1, SessionKey);

         unsigned char HA2[33];
         unsigned char RespHash[33];
         char HA2Hex[33];
         char response[33];
         const char * method = "POST";
         MD5Init(&Md5Ctx);
         MD5Update(&Md5Ctx, method, strlen(method));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, uri.c_str(), strlen(uri.c_str()));
         MD5Final(HA2, &Md5Ctx);
         CvtHex(HA2, HA2Hex);

         MD5Init(&Md5Ctx);
         MD5Update(&Md5Ctx, SessionKey, 32);
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, nonce.c_str(), strlen(nonce.c_str()));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, nc, strlen(nc));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, cnonce, strlen(cnonce));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, qop.c_str(), strlen(qop.c_str()));
         MD5Update(&Md5Ctx, ":", 1);
         MD5Update(&Md5Ctx, HA2Hex, 32);
         MD5Final(RespHash, &Md5Ctx);
         CvtHex(RespHash, response);

         TRACE_PRINTF("HttpcConn::Post value of realm= %s response=%s",digestRealm.c_str(),response);
         httpc_set_digest_authorization(m_conn, cpeusername.c_str(), digestRealm.c_str(), qop.c_str(), nonce.c_str(), uri.c_str(), nc, cnonce, response, opaque.c_str());
      }
      else
      {
         if(cnt)
         {
            httpc_set_basic_authorization(m_conn, cpeusername.c_str(), cpepassword.c_str());
            TRACE_PRINTF("Management password is %s",cpepassword.c_str());
            httpc_add_header(m_conn, "Password", cpepassword.c_str());

            TRACE_PRINTF("Management username is %s",cpeusername.c_str());
            httpc_add_header(m_conn, "Username", cpeusername.c_str());
         }
         else
         {
            cnt++;
         }
      }
   }

   /* Stringize content length */
   char tmp[15];
   sprintf(tmp, "%d", (int)txContentLength);
   httpc_add_header(m_conn, HEADER_CONTENT_LENGTH, tmp);

   /* Build request header */
   httpc_header_add_date();

   /* Set hostname */
   httpc_add_header(m_conn, HEADER_HOST, m_hurl.host);

   switch(method)
   {
      case HTTP_REQUEST_GET:
         header += "GET ";
         header += (m_hurl.context[0] != '\0') ? m_hurl.context : "/";
         header += " HTTP/1.1\r\n";
         break;

      case HTTP_REQUEST_POST:
         {
            header += "POST ";
            string vendor("RADISYS");
            if( Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING),PARAM_ID_GATEWAY_VENDOR) )
            {
               Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), PARAM_ID_GATEWAY_VENDOR, vendor );
            }
            if((m_hurl.context[0] == '/') && (m_hurl.context[1] == '/'))
            {
               while(m_hurl.context[idx] != '\0')
               {
                  m_hurl.context[idx] = m_hurl.context[idx + 1];
                  idx++;
               }
            }

            header += (m_hurl.context[0] != '\0') ? m_hurl.context : "/";
            header += " HTTP/1.1\r\n";
         }
         break;

      default:
         assert(FALSE);
   }

   hpair_t *walker;

   for (walker = m_conn->header; walker; walker = walker->next)
   {
      if (walker->key && walker->value)
      {
         header += walker->key;
         header += ":";
         header += walker->value;
         header += "\r\n";
      }
   }

   header += "\r\n";

   txMessage += header;
}


class XmlTrace
{
   public:
      XmlTrace( const string & xmlString ):
         m_traceString(xmlString)
   {
      size_t indent = 0;
      size_t pos = 0;

      while( string::npos != (pos = m_traceString.find( '>', pos )) )
      {
         if( '/' == m_traceString.at( m_traceString.find_last_of ('<', pos) + 1 ) )
         {
            indent--;
         }
         else
            if(m_traceString.at(pos-1) != '/')
            {
               indent++;
            }


         pos++;
         m_traceString.insert ( pos, indent, ' ' );
         m_traceString.insert ( pos, "\n" );
         m_traceString.insert ( pos, "\r" );
      }

      pos = 0;
      char buffer[2049];
      while(pos < m_traceString.size())
      {
         snprintf(buffer, sizeof(buffer), "%s",  m_traceString.substr(pos).c_str());
         pos += strlen(buffer);
         TRACE_PRINTF("%s", buffer);
      }
   }
      ~XmlTrace() {}

      const string & str() const { return m_traceString; }

   private:
      string m_traceString;
};

bool HttpcConn::WriteToSocket(string& envelope)
{
   string input(envelope);
   string partstring;
   size_t len = input.size();
   size_t lengthOfPart = 1000;

   while (len > lengthOfPart)
   {
      partstring = input.substr(0, lengthOfPart);
      input = input.substr(lengthOfPart);
      len = input.size();
      if(H_OK != http_output_stream_write_string( m_conn->out, partstring.c_str() ) )
      {
         return false;
      }
   }
   if(H_OK != http_output_stream_write_string( m_conn->out, input.c_str() ) )
   {
      return false;
   }
   return true;
}

bool HttpcConn::Post( const string & txSoapEnvelope, hresponse_t ** response  )
{
   bool postedOk = false;

   if(m_conn && m_conn->sock.sock != HSOCKET_FREE)
   {
      std::string txHttpPost;
      std::string matchStr[3] = {"GetParameterNamesResponse", 
                                 "GetParameterValuesResponse", 
                                 "GetParameterAttributesResponse"};
      bool disableXmlTrace = false;
      std::size_t matchFound;

      httpc_header_new(HTTP_REQUEST_POST, txSoapEnvelope.size(), txHttpPost );
      assert(m_conn->header);

      m_conn->out = http_output_stream_new( &m_conn->sock, m_conn->header);

      assert(m_conn->out);

      TRACE_PRINTF("(Prettified) http_stream_write:");

      for (int idx=0; idx<3; idx++)
      {
         matchFound = txSoapEnvelope.find(matchStr[idx]);
         if (matchFound != std::string::npos)
         {
            disableXmlTrace = true;
            break;
         }
      }

      TRACE_PRINTF("disableXmlTrace is %d",disableXmlTrace);

      if (!disableXmlTrace)
      {
        XmlTrace xmlTrace(txSoapEnvelope);
      }

      txHttpPost += txSoapEnvelope;

      unsigned postAttempts = 0;

      while( !postedOk && postAttempts++ < 2)
      {
         TRACE_PRINTF("HttpcConn::Post attempt #%u ", postAttempts);

         if(!WriteToSocket( txHttpPost))
         {
            TRACE_PRINTF("http_stream_write failure.");
         }
         else
         {
            TRACE_PRINTF("httpc_post_end");

            if(response)
            {
               RSYS_ASSERT(*response == NULL);

               if(H_OK != httpc_post_end(m_conn, response))
               {
                  TRACE_PRINTF("TR069:httpc_post_end failure.");
               }
               else
               {
                  postedOk = true;
               }
            }
            else
            {
               // Any response is ignored
               if(H_OK != http_output_stream_flush(m_conn->out))
               {
                  TRACE_PRINTF("TR069:http_output_stream_flush failure.");
               }
               else
               {
                  postedOk = true;
               }

            }
         }
      }

      http_output_stream_free(m_conn->out);
      m_conn->out = NULL;
   }
   else
   {
      TRACE_PRINTF("TR069:httpPostWithResponse failure (%s Socket). Tx'd:%s", (m_conn?"Freed":"No"), txSoapEnvelope.c_str());
   }
   return postedOk;
}

}
