#include <stdlib.h>
#include <string.h>
#include <resolv.h>

#include "Tr069Stun.h"
//#include "Tr069Udp.h"

static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR = -1;

using namespace std;
void StunEncodeRequest(int sockfd,StunAddress4& dest)
{
    char msg[2048];
   
    StunMessage req;
    int len = BuildBindingRequest(req,msg);
    sendMessage( sockfd, msg, len, dest.addr, dest.port );
}

int StunDecodeResponse(char recvmsg[],int recvLen, StunAddress4* mapAddr)
{
    StunMessage resp;
    memset(&resp, 0, sizeof(StunMessage));
    
    bool ok = stunParseMessage( recvmsg, recvLen, resp);
    if (!ok)
    { 
       return -1;
    }
    
    StunAddress4 mappedAddr = resp.mappedAddress.ipv4;

    *mapAddr = mappedAddr;
    
   return ok;
}

int BuildBindingRequest(StunMessage &req,char msg[])
{
    memset(&req, 0, sizeof(StunMessage));
    req.msgHdr.msgType = 0x0001;

    for ( int i=0; i<16; i=i+4 )
    {
         int r = rand() % 10000;
         req.msgHdr.id.octet[i+0]= r>>0;
         req.msgHdr.id.octet[i+1]= r>>8;
         req.msgHdr.id.octet[i+2]= r>>16;
         req.msgHdr.id.octet[i+3]= r>>24;
    }

    char* ptr = msg;
    UInt16 ndata = htons(req.msgHdr.msgType);
    memcpy(msg, reinterpret_cast<void*>(&ndata), sizeof(UInt16));
    ptr = msg + sizeof(UInt16);
    
    char* lengthp = ptr;

    ndata = htons(0);
    memcpy(ptr, reinterpret_cast<void*>(&ndata), sizeof(UInt16));
    ptr =  ptr + sizeof(UInt16);
   
    const char* data = reinterpret_cast<const char*>(req.msgHdr.id.octet);
    unsigned int length = sizeof(req.msgHdr.id) ;
    memcpy(ptr, data, length);
    ptr = ptr + length;
       
    UInt16 data1 = UInt16(ptr - msg - sizeof(StunMsgHdr));
    ndata = htons(data1);
    memcpy(lengthp, reinterpret_cast<void*>(&ndata), sizeof(UInt16));
    int len = int(ptr - msg);
    return len;
}

bool
stunParseMessage( char* buf, unsigned int bufLen, StunMessage& msg)
{
   memset(&msg, 0, sizeof(msg));
	
   if (sizeof(StunMsgHdr) > bufLen)
   {
      return false;
   }
	
   memcpy(&msg.msgHdr, buf, sizeof(StunMsgHdr));
   msg.msgHdr.msgType = ntohs(msg.msgHdr.msgType);
   msg.msgHdr.msgLength = ntohs(msg.msgHdr.msgLength);
	
   if (msg.msgHdr.msgLength + sizeof(StunMsgHdr) != bufLen)
   {
      return false;
   }
	
   char* body = buf + sizeof(StunMsgHdr);
   unsigned int size = msg.msgHdr.msgLength;
	
	
   while ( size > 0 )
   {
		
      StunAtrHdr* attr = reinterpret_cast<StunAtrHdr*>(body);
		
      unsigned int attrLen = ntohs(attr->length);
      int atrType = ntohs(attr->type);
		
      if ( attrLen+4 > size ) 
      {
         return false;
      }
		
      body += 4; // skip the length and type in attribute header
      size -= 4;
		
      switch ( atrType )
      {
         case MappedAddress:
            msg.hasMappedAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.mappedAddress )== false )
            {  
               return false;
            }
            break;  

      }
		
      body += attrLen;
      size -= attrLen;
   }
    
   return true;
}


 bool 
stunParseAtrAddress( char* body, unsigned int hdrLen,  StunAtrAddress4& result )
{
   if ( hdrLen != 8 )
   {
      clog << "hdrLen wrong for Address" <<endl;
      return false;
   }
   result.pad = *body++;
   result.family = *body++;


      UInt16 nport;
      memcpy(&nport, body, 2); body+=2;
      result.ipv4.port = ntohs(nport);
		
      UInt32 naddr;
      memcpy(&naddr, body, 4); body+=4;
      result.ipv4.addr = ntohl(naddr);
      return true;
}

void initNetwork()
{
#ifdef WIN32 
   WORD wVersionRequested = MAKEWORD( 2, 2 );
   WSADATA wsaData;
   int err;
	
   err = WSAStartup( wVersionRequested, &wsaData );
   if ( err != 0 ) 
   {
      // could not find a usable WinSock DLL
      cerr << "Could not load winsock" << endl;
      assert(0);  
      exit(1);
   }
    
    
   if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 ) 
   {
      WSACleanup( );
      cerr << "Bad winsock verion" << endl;
      assert(0);  
      exit(1);
   }    
#endif
}
bool sendMessage( int fd, char* buf, int l,unsigned int dstIp, unsigned short dstPort)
{
   struct sockaddr_in to;
   int toLen = sizeof(to);
   memset(&to,0,toLen);

   to.sin_family = AF_INET;
   to.sin_port = htons(dstPort);
   to.sin_addr.s_addr = htonl(dstIp);

   int s = sendto(fd, buf, l, 0,(sockaddr*)&to, toLen);
   if ( s == SOCKET_ERROR )
   {
      return false;
   }
   return true;
}


