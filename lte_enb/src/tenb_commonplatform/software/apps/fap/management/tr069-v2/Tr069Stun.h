#ifndef __Tr069Stun_h_
#define __Tr069Stun_h_

#include <iostream>
// if you change this version, change in makefile too 
#define STUN_VERSION "0.97"

#define STUN_MAX_STRING 256
#define STUN_MAX_MESSAGE_SIZE 2048

#define STUN_PORT 3478

// define some basic types
typedef unsigned char  UInt8;
typedef unsigned short UInt16;
typedef unsigned int   UInt32;
typedef unsigned long long UInt64;
typedef struct { unsigned char octet[16]; }  UInt128;
const UInt16 MappedAddress    = 0x0001;

typedef struct 
{
      UInt16 msgType;
      UInt16 msgLength;
      UInt128 id;
} StunMsgHdr;

typedef struct
{
      UInt16 type;
      UInt16 length;
} StunAtrHdr;

typedef struct
{
      UInt16 port;
      UInt32 addr;
} StunAddress4;

typedef struct
{
      UInt8 pad;
      UInt8 family;
      StunAddress4 ipv4;
} StunAtrAddress4;

void StunEncodeRequest(int fd,StunAddress4& dest);
typedef struct
{
      StunMsgHdr msgHdr;
      bool hasMappedAddress;
      StunAtrAddress4  mappedAddress;
} StunMessage; 

bool stunParseMessage( char* buf, unsigned int bufLen, StunMessage& msg);
void initNetwork();
bool stunParseAtrAddress( char* body, unsigned int hdrLen,  StunAtrAddress4& result );
int BuildBindingRequest(StunMessage &req,char *msg);
int StunDecodeResponse(char recvmsg[],int recvlen, StunAddress4* mapAddr);
bool sendMessage( int fd, char* buf, int l,unsigned int dstIp, unsigned short dstPort);

#endif
