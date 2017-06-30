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
#include "Tr069UdpServer.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFLEN 512
#define PORT 7547

using namespace std;
using namespace threeway;
using namespace tr069;

extern "C"
{
    extern void httpd_term(int sig);
    extern hrequest_t *call_parse_header(char *data);
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

   static bool firstBindResponse = false;

   Tr069UdpServer* Tr069UdpServer::s_instance = NULL;

Tr069UdpServer& Tr069UdpServer::GetInstance(const IPv4Address & localIpAddress)
{
    ENTER();

    if (s_instance == NULL)
    {
        TRACE_PRINTF("New Tr069UdpServer");
        s_instance = new Tr069UdpServer(localIpAddress);

        RSYS_ASSERT(s_instance);
    }

    RETURN (*s_instance);
}

Tr069UdpServer::Tr069UdpServer( const IPv4Address & localIpAddress ) :
    ThreadWithQueue("Tr069UdpServer"),
    m_localIpAddress(localIpAddress)
{
}

Tr069UdpServer::~Tr069UdpServer()
{
}

bool Tr069UdpServer::ResolveServerNameToFqdn(const char *resolveAddr)
{
   struct hostent * resolved = gethostbyname2(resolveAddr,AF_INET);
   if (resolved)
   {
        TRACE_PRINTF("...resolved to official hostname '%s'", resolved->h_name);
        if (AF_INET == resolved->h_addrtype)
        {
            char first[32];
            memset(first, 0, sizeof(first));
            inet_ntop(AF_INET, resolved->h_addr_list[0], first, sizeof(first));
            resolveAddr = first;
        }
        else
        {
            TRACE_PRINTF("UNABLE TO RESOLVE");
            return false;
        }
   }
   return true;
}

bool Tr069UdpServer::SetStunServerAddress(StunAddress4 &stunServerAddr)
{
     stunServerAddr.addr=0;
     Fqdn stunservName;
     Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_STUN_SERVER_ADDRESS,stunservName     );
     if(stunservName.IsNull())
     {
          string mserv;
          Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_MANAGEMENT_SERVER,mserv);
          Url serv(mserv);
          stunservName = serv.GetFqdn();
     }
     const char *resolveAddr =(stunservName.ToString()).c_str();
     if(isalpha(resolveAddr[0]))
     {
          if (!ResolveServerNameToFqdn(resolveAddr))
          {
               return false;
          }
     }
     stunServerAddr.addr = htonl(inet_addr(resolveAddr));
     Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_STUN_SERVER_PORT,stunServerAddr.port);

     return true;
}

void Tr069UdpServer::HandleStunMessage(char *buf,int recvlen)
{
    Tr069Application &app = Tr069Application::GetInstance(); 
    MibAttributeValues attrs;
    string fgwAddr;
    bool natDetected = false;

    StunAddress4 mapAddr;
    IPv4Address m_addr;
    TRACE_PRINTF("MSG RECEIVED IS STUN MSG");
    StunDecodeResponse(buf,recvlen,&mapAddr);
    m_addr.Set(ntohl(mapAddr.addr));
    TRACE_PRINTF("Mapped Address is %s",m_addr.ToString());
    app.GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_ENB_IP_ADDR_IPV4,fgwAddr);
                    
    if(m_addr.ToString() != fgwAddr)
    {
         natDetected = true;
    }
    if(natDetected)
    {  
         char port[6];
         char udpAddr[20];
         strcpy(udpAddr,fgwAddr.c_str());
         sprintf(port,":%u",mapAddr.port);
         strcat(udpAddr,port);
   
         if(!firstBindResponse)
         {
              u32 bindreqtimer;
              app.GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_STUN_MIN_KEEPALIVE_PERIOD,bindreqtimer);
              TRACE_PRINTF("Stun Timer Started");
              app.StartStunTimer(bindreqtimer*1000);
              attrs.AddAttribute(PARAM_ID_NAT_DETECTED,natDetected);
              firstBindResponse = true;
         }
         attrs.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV4,m_addr.ToString());
         attrs.AddAttribute(PARAM_ID_UDP_CONN_REQ_ADDR,udpAddr);
         app.GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);

         MibAttributeValues ipv4MioAttr;
         ipv4MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS,m_addr.ToString());
         ipv4MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS_ENABLED,(u32)true);
         MibDN ipInterfaceDn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
         MibDN::GenerateMibDN(ipInterfaceDn,MIB_OBJECT_CLASS_IP_INTERFACE_IPV4_ADDRESS,0);
         app.GetMibCache().SetMibAttributes(ipInterfaceDn,ipv4MioAttr,ENTITY_OAM);
    }
}


u32 Tr069UdpServer::ThreadProcedure()
{
   TRACE_PRINTF("In UDP Server Thread Procedure");
   struct sockaddr_in my_addr, cli_addr;
   int sockfd;
   socklen_t slen=sizeof(cli_addr);
   char buf[BUFLEN];
   bool stunEnable;
   if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
   {
      TRACE_PRINTF("UNABLE TO CREATE SOCKET");
   }
   else
   {
      TRACE_PRINTF("CREATE SOCKET SUCCESSFUL");
   }

   bzero(&my_addr, sizeof(my_addr));
   my_addr.sin_family = AF_INET;
   my_addr.sin_port = htons(PORT);
   my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
   {
      TRACE_PRINTF("UDP SOCKET BIND FAILED");
   }
   else
   {
      TRACE_PRINTF("UDP SERVER BIND SUCCESSFUL");
   }
   Tr069Application &app = Tr069Application::GetInstance();
   app.GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_STUN_ENABLE,stunEnable);
   if(stunEnable)
   {
        StunAddress4 stunServerAddr;
        if(SetStunServerAddress(stunServerAddr))
        {
            app.SendBindingRequest(sockfd,stunServerAddr);
            app.SendBindingRequest(sockfd,stunServerAddr);
            int recvlen=0;
            MibAttributeValues attrs;
            string fgwAddr;
            hpair_t *validatedQuery=NULL;
            hrequest_t *req=NULL;
            while(1)
            {
                if ((recvlen = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)) <= 0)
                {
                      TRACE_PRINTF("Packet Receive Error");
                }
                else if (recvlen >= 0)
                {
                      buf[recvlen] = 0;
                }
                if(buf[0]==0||buf[0]==1)
                {
                     HandleStunMessage(buf,recvlen);
                }
                else
                {
                   if(isalpha(buf[0]))
                   {
                     TRACE_PRINTF("Udp Message Received From HeMS");
                     bool valflag=false;
                     hpair_t *tmp=NULL,*tmp1=NULL;
                     req =call_parse_header(buf);
                    
                     if(req->method ==HTTP_REQUEST_GET)
                     {
                         if(validatedQuery == NULL)
                         {
                             validatedQuery = req->query;
                             valflag = true;
                         }
                         else
                         { 
                             tmp = req->query;
                             tmp1 = validatedQuery;
                             while(tmp != NULL)
                             {
                                   TRACE_PRINTF("KEY :%s,%s",tmp->key,tmp->value);
                                   if((!strcmp(tmp->key,tmp1->key))&&(strcmp(tmp->value,tmp1->value)))
                                   {
                                       if(!strcmp(tmp->key,"id"))
                                       {
                                           valflag=true;
                                           validatedQuery = req->query;
                                           break;
                                        }
                                   }
                                   tmp = tmp->next;
                                   tmp1 = tmp1->next;
                              }
                        }
                        
                        if(valflag)
                        {
                            TRACE_PRINTF("VALID UDP MSG");
                            shared_ptr<ConnectionRequest> connectionRequest(new ConnectionRequest());
                            shared_ptr<TransactionSessionCommand> transactionSessionCommand(new TransactionSessionCommand( connectionRequest ))    ;
                            app.Enqueue(transactionSessionCommand);
                        }
                    }
                     
                 }
              }
           }
         }
      }
      close(sockfd);
      return 0;
}


}

