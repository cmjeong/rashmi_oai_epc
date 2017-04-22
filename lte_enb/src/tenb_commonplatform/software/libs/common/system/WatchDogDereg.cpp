///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/Exception.h>
#include <system/Trace.h>
#include <system/SerialisationIds.h>
#include <system/SerialisedData.h>
#include <system/WatchDogDereg.h>

using namespace threeway;
///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////
void FillWatchDogHdr(u8 *msgBuff, u32 msgType, u32 *len, u32 srcEnt, u32 dstEnt)
{
   u32 tmpMsg = 0;
   pid_t tmpId = 0;

   srcEnt = htonl(srcEnt);
   memcpy(&msgBuff[*len], (u8*)&srcEnt, sizeof(srcEnt));
   *len += sizeof(srcEnt);

   dstEnt = htonl(dstEnt);
   memcpy(&msgBuff[*len], (u8*)&dstEnt, sizeof(dstEnt));
   *len += sizeof(dstEnt);

   tmpMsg = htonl(msgType);
   memcpy(&msgBuff[*len], (u8*)&tmpMsg, sizeof(tmpMsg));
   *len += sizeof(tmpMsg);

   tmpId = htonl(getpid());
   memcpy(&msgBuff[*len], (u8*)&tmpId, sizeof(tmpId));
   *len += sizeof(tmpId);
}

void DeregisterWithWatchDog(u32 srcEnt ,u32 dstEnt)
{
   struct sockaddr_in watchDogDestAddr;
   s32    watchSockFd = 0;

   // Opening Socket
   watchSockFd = socket(PF_INET, SOCK_DGRAM, 0);
   if(watchSockFd == (-1))
   {
      TRACE_PRINTF("Failed to open socket for watchdog %d\n", watchSockFd);
      return;
   }
   // Filling Destination Address
   memset(&watchDogDestAddr, 0, sizeof(watchDogDestAddr));
   watchDogDestAddr.sin_family = AF_INET;
   watchDogDestAddr.sin_port = htons(6019);
   inet_pton(AF_INET, "127.0.0.1", &watchDogDestAddr.sin_addr);

   //Creating send packet
   u8 msgPkt[MESSENGER_MAX_SERIALISED_PACKET_LEN];
   u32 pktLen = 0;

   FillWatchDogHdr(msgPkt, SERIALISATION_ID_WATCHDOG_KICK_STOP_REQ , &pktLen, srcEnt, dstEnt);
   //Sending message to watchdog
   u32 sendSize = sendto(watchSockFd, msgPkt, pktLen, 0,(const struct sockaddr *)&watchDogDestAddr,sizeof(struct sockaddr_in));
   if(sendSize != pktLen)
   {
      TRACE_PRINTF("WATCHDOG_KICK_STOP FAILED");
   }
   pktLen = 0;
   FillWatchDogHdr(msgPkt, SERIALISATION_ID_WATCHDOG_REMOVE_PID_REQ , &pktLen, srcEnt, dstEnt);
   sendSize = sendto(watchSockFd, msgPkt, pktLen, 0,(const struct sockaddr *)&watchDogDestAddr,sizeof(struct sockaddr_in));
   if(sendSize != pktLen)
   {
      TRACE_PRINTF("WATCHDOG_REMOVE_PID FAILED");
   }
   close(watchSockFd);
}

