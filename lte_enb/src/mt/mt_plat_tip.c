

/********************************************************************20**
  
     Name:     Multi-threaded System Services - Solaris
  
     Type:     C source file
  
     Desc:     C source code for the MTSS-Solaris implementation of
               System Services.
  
     File:     mt_ss.c
  
     Sid:      pt_ss.c@@/main/1 - Mon Nov 17 15:54:31 2008
   
     Prg:      kp
  
*********************************************************************21*/



/* mt003.301 moved env files to use the __USE_UNIX98 flag in sys includes */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
 
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
 /* mt003.301: included sys/time.h 
  * for both solaris and linux
  * */
#include <sys/time.h>
 /* mt008.21: addition */
#include <errno.h>                 



/* header include files (.h) */

 
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "cm5.h"           /* common timers */

#include "mt_ss.h"         /* MTSS specific */
#include "mt_err.h"        /* MTSS error defines */

#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
/* mt003.301 Additions - Task deregistration */
#include "ss_err.h"        /* error */
#include "cm_mem.h"        /* common memory manager */
/* mt001.301 : Additions */
#ifdef SS_THREAD_PROFILE 
#include "ss_err.h"
#endif


/* multi-core support enhancement */
/*mt013.301 :Added SS_AFFINITY_SUPPORT  */
#if defined(SS_MULTICORE_SUPPORT) ||defined(SS_AFFINITY_SUPPORT)
#ifdef SS_LINUX
#include <sched.h>
#else
#ifdef SUNOS
#include <sys/types.h>
#include <sys/processor.h>
#include <sys/procset.h>
#endif /* SUNOS */
#endif /* SS_LINUX */
#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT */
/* mt001.301 : Additions */
#ifdef SS_WATCHDOG 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif /* SS_WATCHDOG */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timers */

#include "mt_ss.x"         /* MTSS specific */

#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */

#include "cm_mem.x"        /* common memory manager */
/* mt001.301 : Additions */
#ifdef SS_LOGGER_SUPPORT 
#include "cm_lib.x"
#endif /*  SS_LOGGER_SUPPORT */

#include "cm_lib.x"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>
#include "tip.h"
#include "tip_cmn.h" 
//#include "tip_utils.h" 
struct sockaddr_in L3DstSockAddr;
S32 l3SockFd;

struct sockaddr_in Ll2DstSockAddr;
S32 Ll2SockFd;

struct sockaddr_in Ul2DstSockAddr;
S32 Ul2SockFd;

S32 Ul2TipSockFd;
S32 Dul2TipSockFd;
S32 Ll2TipSockFd;
S32 Dll2TipSockFd;
S32 l3TipSockFd;

U8 strtPst = 0;

#define SVSR_CHANNEL_1 0
#define SVSR_CHANNEL_2 1


#define PID_LOW_L3   10
#define PID_HIGH_L3  65000
#define PID_LOW_UPPER_L2 20
#define PID_HIGH_UPPER_L2 65000
#define PID_LOW_LOWER_L2 30
#define PID_HIGH_LOWER_L2 65000

#define WR_TIP_MAX_CELLS 12
PRIVATE  Bool DrvrTskInitialized = FALSE;

EXTERN U8 tipFetchCellIdxFromCellId (U16 cellId);
EXTERN U32 tipFetchUl2IpAddrFromProcId (U32 procId);
Void tipInitEgRecv();
EXTERN U32 LL2_IP_ADDR;
EXTERN U32 UL2_IP_ADDR;
EXTERN U32 L3_IP_ADDR;
EXTERN U32 LL2_PORT_TIP;
EXTERN U32 UL2_PORT_TIP;
EXTERN U32 L3_PORT_TIP;
extern TipVmAssocInfo vmAssocInfo[WR_TIP_MAX_CELLS];
extern TipVmAssocInfo ll2Info[1];
extern TipVmAssocInfo ul2Info[1];
EXTERN S16 fillPstStr(Pst *pst, TipPacket *header);


//#define L3_PORT  50000 
#define UL2_PORT 40000
#define LL2_PORT 30000
#if 0
#define UL2_PORT_TIP  34000
#define DUL2_PORT_TIP 35000
#define LL2_PORT_TIP  36000
#define DLL2_PORT_TIP 37000
#define L3_PORT_TIP   38000
#endif
U32 L3_PORT_TIP;
U32 L3_PORT;

/***********************************************************
 *
 *     Func: tipSendToL3
 *
 *
 *     Desc:   Messages L3-VM receives from UL2-VM and LL2-VM 
 *     @details TIP Interface messages like INIT_IND/RSP, RSP/CFM
 *                  TTI, IND messages will use this API L3<-LL2 and UL2
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendToL3
(
U32  len,                       /* post information */
U8 *sendBuf                    /* message to post */
)
#else
PUBLIC S16 tipSendToL3(len, mBuf)
U32 len;                       /* post information */
U8 *mBuf;                   /* message to post */
#endif
{ 
   S16     ret;
   struct  sockaddr_in tipSrcAddr;      /* local Internet address/port */
   S32     sockFd = 0; 

   if(len == 0 || len > MAX_BUFF_LEN_L2_L3)
   {
      printf("***Recieved length error\n");
      RETVALUE(RFAILED);
   }

   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(L3_PORT_TIP);
   tipSrcAddr.sin_addr.s_addr = htonl(L3_IP_ADDR);
#ifdef TIP_LOWER_L2
   sockFd = Ll2TipSockFd;
#else
#ifdef TIP_UPPER_L2
   sockFd = Ul2TipSockFd;
#endif
#endif
   
   ret = sendto(sockFd, sendBuf, len, 0,
                (struct sockaddr *)&tipSrcAddr, sizeof(tipSrcAddr)); 
   if(ret == -1)
   {
      printf("L3 sendto failed\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func: tipSendToCUL2
 *
 *
 *     Desc:   Messages UL2-VM receives from L3-VM only 
 *     @details TIP Interface messages like INIT_REQ from L3->UL2
 *                  
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendToCUL2
(
U32  len,                       /* post information */
U8 * sendBuf                    /* message to post */
)
#else
PUBLIC S16 tipSendToCUL2(len, sendBuf)
U32 len;                       /* post information */
U8 *sendBuf;                   /* message to post */
#endif
{ 
   S16     ret;
   struct  sockaddr_in tipSrcAddr;      /* local Internet address/port */
   S32     sockFd = 0; 
   U8       cellIdx;
   
   if(len == 0 || len > MAX_BUFF_LEN_L2_L3)
   {
      printf("***Recieved length error\n");
      RETVALUE(RFAILED);
   }
   TipPacket *pkt = (TipPacket*)sendBuf;
   cellIdx  = tipFetchCellIdxFromCellId(pkt->cellId);

   if (cellIdx > WR_TIP_MAX_CELLS )
   {
      printf("\ntipSendToCUL2 : Invalid cellIdx %d derived for  cellId %d \n", cellIdx, pkt->cellId);
      RETVALUE(RFAILED);
   }
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(vmAssocInfo[cellIdx].l2uIpAddr.u.ipv4TptAddr.port);
   tipSrcAddr.sin_addr.s_addr = htonl(vmAssocInfo[cellIdx].l2uIpAddr.u.ipv4TptAddr.address);

#ifdef TIP_L3
   sockFd = l3TipSockFd;
#endif
   
   ret = sendto(sockFd, sendBuf, len, 0, 
                (struct sockaddr *)&tipSrcAddr, sizeof(tipSrcAddr)); 
   if(ret == -1)
   {
      printf("UL2 sendto failed\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func: tipSendToDUL2
 *
 *
 *     Desc:   Messages UL2-VM received from LL2-VM only
 *     @details TIP Interface messages like UL Data Msg from LL2->UL2
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendToDUL2
(
U32  len,                       /* post information */
U8 * sendBuf                    /* message to post */
)
#else
PUBLIC S16 tipSendToDUL2(len, sendBuf)
U32 len;                       /* post information */
U8 *sendBuf;                   /* message to post */
#endif
{ 
   S16     ret;
   struct  sockaddr_in tipSrcAddr;      /* local Internet address/port */
   S32     sockFd = 0; 
   
   if(len == 0 || len > MAX_BUFF_LEN_L2_L3)
   {
      printf("***Recieved length error\n");
      RETVALUE(RFAILED);
   }
      
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(UL2_PORT_TIP+1);
   tipSrcAddr.sin_addr.s_addr = htonl(ll2Info[0].l2uIpAddr.u.ipv4TptAddr.address);
#ifdef TIP_LOWER_L2
   sockFd = Dll2TipSockFd;
#endif
   
   ret = sendto(sockFd, sendBuf, len, 0, 
                (struct sockaddr *)&tipSrcAddr, sizeof(tipSrcAddr)); 
   if(ret == -1)
   {
      printf("UL2 sendto failed\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func: tipSendToCLL2
 *
 *
 *     Desc:   Messages LL2-VM received from L3-VM only
 *     @details TIP Interface messages INIT_REQ, CFG_REQ for MAC/RLC/
 *                  PHY, SI_CFG, CCCH_MSG etc from L3->LL2
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendToCLL2
(
U32  len,                       /* post information */
U8*  sendBuf                    /* message to post */
)
#else
PUBLIC S16 tipSendToCLL2(len, sendBuf)
U32 len;                       /* post information */
U8 *mBuf;                   /* message to post */
#endif
{ 
   S16     ret;
   struct  sockaddr_in tipSrcAddr;      /* local Internet address/port */
   S32     sockFd = 0; 
   U8      buf[MAX_BUFF_LEN_L2_L3];
   U8      cellIdx;
   TipPacket *pkt;
   		 
   if(len == 0 || len > MAX_BUFF_LEN_L2_L3)
   {
      printf("***Recieved length error\n");
      RETVALUE(RFAILED);
   }
   pkt = (TipPacket*)sendBuf;
   cellIdx  = tipFetchCellIdxFromCellId(pkt->cellId);

   if (cellIdx > WR_TIP_MAX_CELLS )
   {
      printf("\n tipSendToCLL2 : Invalid cellIdx %d derived for  cellId %d \n", cellIdx, pkt->cellId);
      RETVALUE(RFAILED);
   }
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(vmAssocInfo[cellIdx].l2lIpAddr.u.ipv4TptAddr.port);
   tipSrcAddr.sin_addr.s_addr = htonl(vmAssocInfo[cellIdx].l2lIpAddr.u.ipv4TptAddr.address);
   sockFd = l3TipSockFd;

      cmMemcpy(buf,sendBuf,len);
#if 0
printf("Send to LL2 port %d",LL2_PORT_TIP); 
TipPacket *hdr1;
hdr1 = (TipPacket *)&buf;
printf("*******While Sending*******\n");
printf("src:%d\n",hdr1->srcModId);
printf("dst:%d\n",hdr1->dstModId);
printf("cell:%d\n",hdr1->cellId);
printf("msg:%d\n",hdr1->msgId);
printf("trans:%d\n",hdr1->transId);
printf("pktLen:%d\n",hdr1->pktLen);
printf("length:%ld\n",len);
#endif
   ret = sendto(sockFd, buf, len, 0, 
                (struct sockaddr *)&tipSrcAddr, sizeof(tipSrcAddr)); 
   if(ret == -1)
   {
      printf("LL2 sendto failed\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func: tipSendToDLL2
 *
 *
 *     Desc:   Messages UL2-VM receives from LL2-VM only
 *     @details TIP Interface messages like DL Data Msg from UL2->LL2
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendToDLL2
(
U32  len,                       /* post information */
U8*  sendBuf                    /* message to post */
)
#else
PUBLIC S16 tipSendToDLL2(len, sendBuf)
U32 len;                       /* post information */
U8 *mBuf;                   /* message to post */
#endif
{ 
   S16     ret;
   struct  sockaddr_in tipSrcAddr;      /* local Internet address/port */
   S32     sockFd = 0; 
   U8      buf[MAX_BUFF_LEN_L2_L3];
       
   if(len == 0 || len > MAX_BUFF_LEN_L2_L3)
   {
      printf("***Recieved length error\n");
      RETVALUE(RFAILED);
   }
      
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(LL2_PORT_TIP+1);
   tipSrcAddr.sin_addr.s_addr = htonl(ul2Info[0].l2lIpAddr.u.ipv4TptAddr.address);
#ifdef TIP_UPPER_L2
   sockFd = Dul2TipSockFd;
#else
   printf("*** tipSendToDLL2 should be used send Data only\n");
   RETVALUE(RFAILED);
#endif

   cmMemcpy(buf,sendBuf,len);
   ret = sendto(sockFd, buf, len, 0, 
                (struct sockaddr *)&tipSrcAddr, sizeof(tipSrcAddr)); 
   if(ret == -1)
   {
      printf("LL2 sendto failed\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 tipL3Ul2PstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
)
#else
PUBLIC S16 tipL3Ul2PstTsk(pst, mBuf)
Pst *pst;                       /* post information */
Buffer *mBuf;                   /* message to post */
#endif
{
   MsgLen         bufLen    = 0;
   MsgLen         msgLen    = 0;
   Inst           inst;
   struct sockaddr_in *dstSockAddr = NULL;  
   U8             sendBuf[MAX_BUFF_LEN_L2_L3];
   S32            sockFd = 0;
   S8 ret, ret1;   

   TRC0(tipL3Ul2PstTsk);

   if (DrvrTskInitialized == FALSE)
   {
       while (DrvrTskInitialized == FALSE)
       {
         sleep(1);
       }
   }

#if 0
   printf("driver task called	%s:	%d\n",__FUNCTION__,__LINE__);
#endif
   if (!pst || !mBuf)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Invalid Inputs.NULL pst/mBuf");
#endif
      if (mBuf)
      {
         SPutMsg(mBuf);
      }
      RETVALUE(RFAILED);
   }

   /* Remove the channel id */
   CMCHKUNPKLOG(cmUnpkInst, &inst, mBuf, 0, pst);

/* UL2 will always post to L3 and vice versa, as LL2 have TIP interface
 * communication between L3 and Ul2 */
#ifdef TIP_UPPER_L2
    sockFd = Ul2SockFd;
    dstSockAddr = &L3DstSockAddr;
#endif
#ifdef TIP_L3
     sockFd = l3SockFd;

     cmMemset((U8*)&Ul2DstSockAddr, 0, sizeof(Ul2DstSockAddr));
     Ul2DstSockAddr.sin_family      = AF_INET;
     Ul2DstSockAddr.sin_port        = htons(UL2_PORT);
     UL2_IP_ADDR = tipFetchUl2IpAddrFromProcId(pst->dstProcId);
     Ul2DstSockAddr.sin_addr.s_addr = htonl(UL2_IP_ADDR);

     dstSockAddr = &Ul2DstSockAddr;
     //pst->dstProcId=10;
#endif

/* Pack pst structure. Check the return value */
   if(cmPkPst(pst, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "cmPkPst failed!");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   ret = SFndLenMsg(mBuf, &bufLen);
   
   ret1 = SCpyMsgFix(mBuf, 0, bufLen, sendBuf, &msgLen);
   if ((ret1 != ROK) || (msgLen != bufLen)) 
   {
      //YS_DBG_ERR((_ysp, "SCpyMsgFix failed\n"));
      printf("SCpyMsgFix failed [msgLen: %d bufLen: %d]\n", msgLen, bufLen);
      RETVALUE(RFAILED);
   }

   ret1 = sendto(sockFd, sendBuf, bufLen, 0, 
                (struct sockaddr *)dstSockAddr, sizeof(*dstSockAddr)); 
   if(ret1 == -1)
   {
      //YS_DBG_ERR((_ysp, "sendto failed\n"));
      printf( "tipL3Ul2PstTsk: sendto failed\n");
      RETVALUE(RFAILED);
   }
#if 0
   printf("SEND POST INFO(len: %d): dst: %d src: %d dstEnt: %d srcEnt: %d event: %d region: %d\n\n", 
         ret1, pst->dstProcId, pst->srcProcId, pst->dstEnt, pst->srcEnt,
         pst->event, pst->region);
   //SPrntMsg(mBuf, 0, 0);
#endif
#if 0
   printf("after driver sendto	%s:	%d\n\n",__FUNCTION__,__LINE__);
#endif

   SPutMsg(mBuf);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 tipPstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
)
#else
PUBLIC S16 tipPstTsk(pst, mBuf)
Pst *pst;                       /* post information */
Buffer *mBuf;                   /* message to post */
#endif
{
   MsgLen         bufLen    = 0;
   MsgLen         msgLen    = 0;
   Inst           inst;
   struct sockaddr_in *dstSockAddr = NULL;  
   U8             sendBuf[MAX_BUFF_LEN_L2_L3];
   S32            sockFd = 0;
   S8 ret, ret1;   

   TRC0(tipPstTsk);

   if (DrvrTskInitialized == FALSE)
   {
       while (DrvrTskInitialized == FALSE)
       {
         sleep(1);
       }
   }

#if 0
   printf("driver task called	%s:	%d\n",__FUNCTION__,__LINE__);
#endif
   if (!pst || !mBuf)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Invalid Inputs.NULL pst/mBuf");
#endif
      if (mBuf)
      {
         SPutMsg(mBuf);
      }
      RETVALUE(RFAILED);
   }

   /* Remove the channel id */
   CMCHKUNPKLOG(cmUnpkInst, &inst, mBuf, 0, pst);

#if 0 /* Removing logic to post to LL2 from UL2 and L3 */
   if((pst->srcEnt == ENTPJ) && (pst->dstEnt == ENTNH))/*manjappa*/ 
   {
      inst = 1;
      pst->dstProcId=10;
   }
   switch (inst)
   {
      case SVSR_CHANNEL_1: 
      {
#ifdef TIP_LOWER_L2
          sockFd = Ll2SockFd;
          dstSockAddr = &L3DstSockAddr;
#else
#ifdef TIP_UPPER_L2
          sockFd = Ul2SockFd;
          dstSockAddr = &Ll2DstSockAddr;
#else
          sockFd = l3SockFd;
          dstSockAddr = &Ll2DstSockAddr;
#endif
#endif
        break;
      }
     case SVSR_CHANNEL_2:
      {
#ifdef TIP_LOWER_L2
          sockFd = Ll2SockFd;
          dstSockAddr = &Ul2DstSockAddr;
#else
#ifdef TIP_UPPER_L2
          sockFd = Ul2SockFd;
          dstSockAddr = &L3DstSockAddr;
#else
          sockFd = l3SockFd;
          dstSockAddr = &Ul2DstSockAddr;
#endif
#endif
         break;
      } 
      default:
       SPutMsg(mBuf);
       RETVALUE(ROK);
   }
#else
/* UL2 will always post to L3 and vice versa, as LL2 have TIP interface
 * communication between L3 and Ul2 */
#ifdef TIP_UPPER_L2
    sockFd = Ul2SockFd;
    dstSockAddr = &L3DstSockAddr;
    //pst->dstProcId=10;
#endif
#ifdef TIP_L3
     sockFd = l3SockFd;
     dstSockAddr = &Ul2DstSockAddr;
     //pst->dstProcId=10;
#endif

#endif
/* Pack pst structure. Check the return value */
   if(cmPkPst(pst, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "cmPkPst failed!");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   ret = SFndLenMsg(mBuf, &bufLen);
   
   ret1 = SCpyMsgFix(mBuf, 0, bufLen, sendBuf, &msgLen);
   if ((ret1 != ROK) || (msgLen != bufLen)) 
   {
      //YS_DBG_ERR((_ysp, "SCpyMsgFix failed\n"));
      printf("SCpyMsgFix failed [msgLen: %d bufLen: %d]\n", msgLen, bufLen);
      RETVALUE(RFAILED);
   }

   ret1 = sendto(sockFd, sendBuf, bufLen, 0, 
                (struct sockaddr *)dstSockAddr, sizeof(*dstSockAddr)); 
   if(ret1 == -1)
   {
      //YS_DBG_ERR((_ysp, "sendto failed\n"));
      printf( "tipPstTsk  sendto failed\n");
      RETVALUE(RFAILED);
   }
#if 0
   printf("SEND POST INFO(len: %d): dst: %d src: %d dstEnt: %d srcEnt: %d event: %d region: %d\n\n", 
         ret1, pst->dstProcId, pst->srcProcId, pst->dstEnt, pst->srcEnt,
         pst->event, pst->region);
   //SPrntMsg(mBuf, 0, 0);
#endif
#if 0
   printf("after driver sendto	%s:	%d\n\n",__FUNCTION__,__LINE__);
#endif

   SPutMsg(mBuf);

   RETVALUE(ROK);

}
/*
 *
 *       Fun:  uarmIsTsk
 *
 *       Desc:Dummy function
 *
 *
 *
 *       Ret:   ROK      - ok
 *              RFAILED  - failed, general (optional)
 *
 *       Notes:
 *
 *       File:  mt_4gmx.c
 *
 */
#ifdef ANSI
PUBLIC Void tipIsTsk
(
Inst inst
)
#else
PUBLIC Void tipIsTsk(inst)
Inst inst;
#endif
{

   TRC0(tipIsTsk);

#if 0
   printf("%s:%d\n",__func__,__LINE__);
#endif

   RETVOID;
}

void *TipCSocketRecv (void *in)
{
   struct     sockaddr_in remSockAddr;     /* local Internet address/port */
   S32        tipSockfd;
   socklen_t  remAddrLen = sizeof(remSockAddr);
   ssize_t    recvLen;
   U8         buf[MAX_BUFF_LEN_L2_L3];
   Buffer    *rcvBuf;
   S16        ret;
   Pst       nPst;

#ifdef TIP_LOWER_L2
  tipSockfd = Ll2TipSockFd;
#else
#ifdef TIP_UPPER_L2
   tipSockfd = Ul2TipSockFd;
#else
   tipSockfd = l3TipSockFd;
#endif
#endif

#if 0
   if((S32)(tipSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() tipSockfd error lol!");
      exit(1);
   }
   
   printf("Tip Socket Creation entered\n");
#ifdef TIP_LOWER_L2
  Ll2TipSockFd = tipSockfd;
  ipAddr = htonl(LL2_IP_ADDR);
  port = LL2_PORT_TIP;
#else
#ifdef TIP_UPPER_L2
   Ul2TipSockFd = tipSockfd;
   ipAddr = htonl(UL2_IP_ADDR);
   port   = UL2_PORT_TIP;
#else
   l3TipSockFd = tipSockfd;
   ipAddr = htonl(L3_IP_ADDR);
   port   = L3_PORT_TIP;
#endif
#endif

   cmMemset((U8*)&tipSrcAddr, 0, sizeof(tipSrcAddr));
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(port);
   tipSrcAddr.sin_addr.s_addr = ipAddr;

   if(bind(tipSockfd, (struct sockaddr *)&tipSrcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }
   printf("*****TIP socket created\n");
#endif
   while(1)
   {
      /* clear the structure */   
      cmMemset((U8*)&remSockAddr, 0, sizeof(remSockAddr));

      /*read the data from socket*/
      if((recvLen = recvfrom(tipSockfd, buf, sizeof(buf), 0, 
                            (struct sockaddr *)&remSockAddr, 
                            &remAddrLen)) == -1)

      {
       //  YS_DBG_ERR((_ysp, "Server-recvfrom() error\n"));
         printf("TIP SOCKET Server-recvfrom() error\n");
         continue;
      }

     // printf("*****Recieved TIP socket Message\n");
#if 1
      /* copy data to a message structure */
      ret = SGetMsg(DFLT_REGION, DFLT_POOL, &rcvBuf);
      if (ret != ROK)
      {
         printf("SGetMsg failed\n");
         continue;
      }

      ret = SAddPstMsgMult(buf, recvLen, rcvBuf);
      if (ret != ROK)
      {
         printf("SAddPstMsgMult failed\n");
         continue;
      }

      //CMCHKUNPK(cmUnpkPst, &nPst, rcvBuf);
#else
      SGetSBuf(DFLT_REGION,DFLT_POOL,(Data **)&rcvBuf,recvLen);
      cmMemcpy(recvBuf,&buf,len);
#endif
 TipPacket *hdr1;
hdr1 = (TipPacket *)&buf;
#if 0
printf("*******While Reciveing*******\n");
printf("src:%d\n",hdr1->srcModId);
printf("dst:%d\n",hdr1->dstModId);
printf("cell:%d\n",hdr1->cellId);
printf("msg:%d\n",hdr1->msgId);
printf("trans:%d\n",hdr1->transId);
printf("pktLen:%d\n",hdr1->pktLen);
printf("length:%d\n",recvLen);
#endif
 //     SGetSBuf(DFLT_REGION,DFLT_POOL,(Data **)&nPst,sizeof(Pst));
      if(fillPstStr(&nPst,(TipPacket *)&buf) != ROK)
      {
         printf("Filling Post structure failed\n");
      }
       
      //printf("*****TIP socket: Post Task filled\n");
      ret = SPstTsk(&nPst,rcvBuf);
      if(ROK != ret)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS527, (ErrVal) ret,
               "Could not post to TAPA task");
#endif
         printf("Post Task Failed\n");
         SPutMsg(rcvBuf);
      }
   }
   pthread_exit(NULLP);
}

void *TipDSocketRecv(void *in)
{
   struct     sockaddr_in tipSrcAddr;      /* Global Internet address/port */
   struct     sockaddr_in remSockAddr;     /* local Internet address/port */
   S32        tipSockfd;
   U32        ipAddr = 0;
   U16        port = 0;
   socklen_t  remAddrLen = sizeof(remSockAddr);
   ssize_t    recvLen;
   U8         buf[MAX_BUFF_LEN_L2_L3];
   Buffer    *rcvBuf;
   S16        ret;
   Pst       nPst;

   if((S32)(tipSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() tipSockfd error lol!");
      exit(1);
   }
   
   printf("Tip Socket Creation entered\n");
#ifdef TIP_LOWER_L2
  Dll2TipSockFd = tipSockfd;
  ipAddr = htonl(LL2_IP_ADDR);
  port =  LL2_PORT_TIP+1;
#else
#ifdef TIP_UPPER_L2
   Dul2TipSockFd = tipSockfd;
   ipAddr = htonl(UL2_IP_ADDR);
   port   =  UL2_PORT_TIP+1;
#endif
#endif

   cmMemset((U8*)&tipSrcAddr, 0, sizeof(tipSrcAddr));
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(port);
   tipSrcAddr.sin_addr.s_addr = ipAddr;

   if(bind(tipSockfd, (struct sockaddr *)&tipSrcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }
   printf("*****TIP socket created\n");
   while(1)
   {
      /* clear the structure */   
      cmMemset((U8*)&remSockAddr, 0, sizeof(remSockAddr));

      /*read the data from socket*/
      if((recvLen = recvfrom(tipSockfd, buf, sizeof(buf), 0, 
                            (struct sockaddr *)&remSockAddr, 
                            &remAddrLen)) == -1)

      {
       //  YS_DBG_ERR((_ysp, "Server-recvfrom() error\n"));
         printf("TIP SOCKET Server-recvfrom() error\n");
         continue;
      }

     // printf("*****Recieved TIP socket Message\n");
#if 1
      /* copy data to a message structure */
      ret = SGetMsg(DFLT_REGION, DFLT_POOL, &rcvBuf);
      if (ret != ROK)
      {
         printf("SGetMsg failed\n");
         continue;
      }

      ret = SAddPstMsgMult(buf, recvLen, rcvBuf);
      if (ret != ROK)
      {
         printf("SAddPstMsgMult failed\n");
         continue;
      }

      //CMCHKUNPK(cmUnpkPst, &nPst, rcvBuf);
#else
      SGetSBuf(DFLT_REGION,DFLT_POOL,(Data **)&rcvBuf,recvLen);
      cmMemcpy(recvBuf,&buf,len);
#endif
 TipPacket *hdr1;
hdr1 = (TipPacket *)&buf;
#if 0
printf("*******While Reciveing*******\n");
printf("src:%d\n",hdr1->srcModId);
printf("dst:%d\n",hdr1->dstModId);
printf("cell:%d\n",hdr1->cellId);
printf("msg:%d\n",hdr1->msgId);
printf("trans:%d\n",hdr1->transId);
printf("pktLen:%d\n",hdr1->pktLen);
printf("length:%d\n",recvLen);
#endif
 //     SGetSBuf(DFLT_REGION,DFLT_POOL,(Data **)&nPst,sizeof(Pst));
      if(fillPstStr(&nPst,(TipPacket *)&buf) != ROK)
      {
         printf("Filling Post structure failed\n");
      }
       
      //printf("*****TIP socket: Post Task filled\n");
      ret = SPstTsk(&nPst,rcvBuf);
      if(ROK != ret)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS527, (ErrVal) ret,
               "Could not post to TAPA task");
#endif
         printf("Post Task Failed\n");
         SPutMsg(rcvBuf);
      }
   }
   pthread_exit(NULLP);
}


void *DrvrRcvrTsk(void *in)
{
   struct sockaddr_in srcAddr;  /* local Internet address/port */
   struct sockaddr_in remSockAddr;  /* local Internet address/port */
   S32 sockfd;
   U32 ipAddr;
   U16 port;
   socklen_t    remAddrLen = sizeof(remSockAddr);
   ssize_t recvLen;
   U8     buf[MAX_BUFF_LEN_L2_L3];
   Buffer *rcvBuf;
   S16    ret;
   Pst    nPst;

   /* ys004.102: g++ compilation */
   if((int)(sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() sockfd error lol!");
      exit(1);
   }
   
  printf("\n Entered DrvrRcvrTsk \n");
#ifdef TIP_LOWER_L2
   Ll2SockFd = sockfd;
   ipAddr = htonl(LL2_IP_ADDR);
   port   = LL2_PORT;
#else
#ifdef TIP_UPPER_L2
   Ul2SockFd = sockfd;
   ipAddr = htonl(UL2_IP_ADDR);
   port   = UL2_PORT;
#else
   l3SockFd = sockfd;
   ipAddr = htonl(L3_IP_ADDR);
   port   = L3_PORT;
#endif
#endif

   cmMemset((U8*)&srcAddr, 0, sizeof(srcAddr));
   srcAddr.sin_family      = AF_INET;
   srcAddr.sin_port        = htons(port);
   srcAddr.sin_addr.s_addr = ipAddr;

   if(bind(sockfd, (struct sockaddr *)&srcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }

   printf("*****DRVR socket Created\n");
   DrvrTskInitialized=TRUE;
   while(1)
   {
      /* clear the structure */   
      cmMemset((U8*)&remSockAddr, 0, sizeof(remSockAddr));

#if 0
   printf("before driver recvfrom	%s:	%d\n",__FUNCTION__,__LINE__);
#endif
      /*read the data from socket*/
      if((recvLen = recvfrom(sockfd, buf, sizeof(buf), 0, 
                            (struct sockaddr *)&remSockAddr, 
                            &remAddrLen)) == -1)

      {
       //  YS_DBG_ERR((_ysp, "Server-recvfrom() error\n"));
        printf("Server-recvfrom() error\n");
         continue;
      }
#if 0
   printf("after driver recvfrom	%s:	%d\n",__FUNCTION__,__LINE__);
   printf("*****DRVR socket recieved\n");
#endif
/* copy data to a message structure */
      ret = SGetMsg(DFLT_REGION, DFLT_POOL, &rcvBuf);
      if (ret != ROK)
      {
//         YS_DBG_ERR((_ysp, "SGetMsg failed\n"));
        printf("SGetMsg failed\n");
         continue;
      }

      ret = SAddPstMsgMult(buf, recvLen, rcvBuf);
      if (ret != ROK)
      {
//         YS_DBG_ERR((_ysp, "SAddPstMsgMult failed\n"));
        printf("SAddPstMsgMult failed\n");
         continue;
      }

      CMCHKUNPK(cmUnpkPst, &nPst, rcvBuf);

#if 0
      //SPrntMsg(rcvBuf, 0, 0);
      printf("\nRECV POST INFO(len: %d): dst: %d src: %d dstEnt: %d srcEnt: %d event: %d region: %d\n\n", 
            recvLen, nPst.dstProcId, nPst.srcProcId, nPst.dstEnt, nPst.srcEnt,
            nPst.event, nPst.region);
       printf("*****DRVR socket Post Task\n");
#endif
       nPst.dstProcId =SFndProcId();

       ret = SPstTsk(&nPst,rcvBuf);
       if(ROK != ret)
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS527, (ErrVal) ret,
                "Could not post to TAPA task");
#endif
           SPutMsg(rcvBuf);
       }

   }

   pthread_exit(NULLP);
}

#ifdef TIP_LOWER_L2
#ifdef ANSI
PUBLIC S16 InitLL2TipSockTsk
(
 Void
)
#else
PUBLIC S16 InitLL2TipSockTsk
#endif
{

   TRC0(InitLL2TipSockTsk)

   pthread_t  tId_tip;
   pthread_attr_t  attr_tip;
   
   pthread_attr_init(&attr_tip);
   pthread_attr_setstacksize(&attr_tip, (size_t)NULLD);
   pthread_attr_setscope(&attr_tip, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr_tip, PTHREAD_CREATE_DETACHED);
   
   if ((SCreatePThread(&tId_tip, &attr_tip, TipCSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }

   if ((SCreatePThread(&tId_tip, &attr_tip, TipDSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }

   pthread_attr_destroy(&attr_tip);
   RETVALUE(ROK);
}
#endif


#ifdef TIP_UPPER_L2
#ifdef ANSI
PUBLIC S16 InitUL2DrvrTsk   
(
 Void
)
#else
PUBLIC S16 InitUL2DrvrTsk   
#endif
{
   S16 ret;
   U16 pidLow;
   U16 pidHigh;
   U16 pidLow1;
   U16 pidHigh1;

   TRC0(InitUL2DrvrTsk);

    pidLow = PID_LOW_LOWER_L2;
    pidHigh = PID_HIGH_LOWER_L2;
    pidLow1 = PID_LOW_L3;
    pidHigh1 = PID_HIGH_L3;
  /* Curerntly LL2 Driver task not used */ 
   ret = SRegDrvrTsk(SVSR_CHANNEL_1, pidLow, pidHigh, tipL3Ul2PstTsk, tipIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   ret = SRegDrvrTsk(SVSR_CHANNEL_2, pidLow1, pidHigh1, tipL3Ul2PstTsk, tipIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }
   cmMemset((U8*)&L3DstSockAddr, 0, sizeof(L3DstSockAddr));
   L3DstSockAddr.sin_family      = AF_INET;
   L3DstSockAddr.sin_port        = htons(L3_PORT);
   L3DstSockAddr.sin_addr.s_addr = htonl(L3_IP_ADDR);

   pthread_t tId;
   pthread_attr_t attr;

   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, (size_t)NULLD);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   if ((SCreatePThread(&tId, &attr, DrvrRcvrTsk, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr);
 
     printf("Failed to create receiver thread\n");

      RETVALUE(RFAILED);
   }

#ifdef TIP_UPPER_L2
   printf("\n TIP DEBUG:: Creating thread to post EGTP ticks from initDrvrTsk \n");
   tipInitEgRecv();
#endif
   pthread_attr_destroy(&attr);
   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 InitUL2TipSockTsk
(
 Void
)
#else
PUBLIC S16 InitUL2TipSockTsk
#endif
{

   TRC0(InitUL2TipSockTsk);

   pthread_t  tId_tip;
   pthread_attr_t  attr_tip;
   
   pthread_attr_init(&attr_tip);
   pthread_attr_setstacksize(&attr_tip, (size_t)NULLD);
   pthread_attr_setscope(&attr_tip, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr_tip, PTHREAD_CREATE_DETACHED);
   
/* TODO:: Below flag to be enabled when LL2 TIP message is handled completely */
   if ((SCreatePThread(&tId_tip, &attr_tip, TipCSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }
   if ((SCreatePThread(&tId_tip, &attr_tip, TipDSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }

   pthread_attr_destroy(&attr_tip);
   RETVALUE(ROK);
}
#endif

#ifdef TIP_L3
#ifdef ANSI
PUBLIC S16 InitL3DrvrTsk   
(
 Void
)
#else
PUBLIC S16 InitL3DrvrTsk   
#endif
{
   S16 ret;
   U16 pidLow;
   U16 pidHigh;
   U16 pidLow1;
   U16 pidHigh1;

   TRC0(InitL3DrvrTsk);
    pidLow = PID_LOW_LOWER_L2;
    pidHigh = PID_HIGH_LOWER_L2;
    pidLow1 = PID_LOW_UPPER_L2;
    pidHigh1 = PID_HIGH_UPPER_L2;
  /* Curerntly LL2 Driver task not used */ 
   ret = SRegDrvrTsk(SVSR_CHANNEL_1, pidLow, pidHigh, tipL3Ul2PstTsk, tipIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   ret = SRegDrvrTsk(SVSR_CHANNEL_2, pidLow1, pidHigh1, tipL3Ul2PstTsk, tipIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8*)&L3DstSockAddr, 0, sizeof(L3DstSockAddr));
   L3DstSockAddr.sin_family      = AF_INET;
   L3DstSockAddr.sin_port        = htons(L3_PORT);
   L3DstSockAddr.sin_addr.s_addr = htonl(L3_IP_ADDR);

   pthread_t tId;
   pthread_attr_t attr;

   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, (size_t)NULLD);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   if ((SCreatePThread(&tId, &attr, DrvrRcvrTsk, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr);

      printf("Failed to create receiver thread\n");

      RETVALUE(RFAILED);
   }
   pthread_attr_destroy(&attr);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 InitL3TipSockTsk
(
 Void
)
#else
PUBLIC S16 InitL3TipSockTsk
#endif
{

   TRC0(InitL3TipSockTsk);

   pthread_t  tId_tip;
   pthread_attr_t  attr_tip;
   
   pthread_attr_init(&attr_tip);
   pthread_attr_setstacksize(&attr_tip, (size_t)NULLD);
   pthread_attr_setscope(&attr_tip, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr_tip, PTHREAD_CREATE_DETACHED);

   if ((SCreatePThread(&tId_tip, &attr_tip, TipCSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }

   pthread_attr_destroy(&attr_tip);
   RETVALUE(ROK);
}
#endif
#ifdef ANSI
PUBLIC S16 InitDrvrTsk
(
 Void
)
#else
PUBLIC S16 InitDrvrTsk
#endif
{
   S16 ret;
   U16 pidLow;
   U16 pidHigh;
   U16 pidLow1;
   U16 pidHigh1;

   TRC0(InitDrvrTsk);

   /* Channel initialized to handle messages targetted towards
    * 4GMX channels, and Vice versa.
    */
#ifdef TIP_LOWER_L2
    pidLow = PID_LOW_L3;
    pidHigh = PID_HIGH_L3;
    pidLow1 = PID_LOW_UPPER_L2;
    pidHigh1 = PID_HIGH_UPPER_L2;
#else
#ifdef TIP_UPPER_L2
    pidLow = PID_LOW_LOWER_L2;
    pidHigh = PID_HIGH_LOWER_L2;
    pidLow1 = PID_LOW_L3;
    pidHigh1 = PID_HIGH_L3;
#else
    pidLow = PID_LOW_LOWER_L2;
    pidHigh = PID_HIGH_LOWER_L2;
    pidLow1 = PID_LOW_UPPER_L2;
    pidHigh1 = PID_HIGH_UPPER_L2;
#endif
#endif
   ret = SRegDrvrTsk(SVSR_CHANNEL_1, pidLow, pidHigh, tipPstTsk, tipIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   ret = SRegDrvrTsk(SVSR_CHANNEL_2, pidLow1, pidHigh1, tipPstTsk, tipIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8*)&Ll2DstSockAddr, 0, sizeof(Ll2DstSockAddr));
   Ll2DstSockAddr.sin_family      = AF_INET;
   Ll2DstSockAddr.sin_port        = htons(LL2_PORT);
   Ll2DstSockAddr.sin_addr.s_addr = htonl(LL2_IP_ADDR);

   cmMemset((U8*)&L3DstSockAddr, 0, sizeof(L3DstSockAddr));
   L3DstSockAddr.sin_family      = AF_INET;
   L3DstSockAddr.sin_port        = htons(L3_PORT);
   L3DstSockAddr.sin_addr.s_addr = htonl(L3_IP_ADDR);

   cmMemset((U8*)&Ul2DstSockAddr, 0, sizeof(Ul2DstSockAddr));
   Ul2DstSockAddr.sin_family      = AF_INET;
   Ul2DstSockAddr.sin_port        = htons(UL2_PORT);
   Ul2DstSockAddr.sin_addr.s_addr = htonl(UL2_IP_ADDR);

   pthread_attr_t attr;

//if (defined(TIP_UPPER_L2) || defined(TIP_L3))
   pthread_t  tId_tip;
   pthread_attr_t  attr_tip;
   
   pthread_attr_init(&attr_tip);
   pthread_attr_setstacksize(&attr_tip, (size_t)NULLD);
   pthread_attr_setscope(&attr_tip, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr_tip, PTHREAD_CREATE_DETACHED);
//#endif
   
   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, (size_t)NULLD);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
#ifndef TIP_LOWER_L2
   pthread_t tId;
   if ((SCreatePThread(&tId, &attr, DrvrRcvrTsk, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr);
      pthread_attr_destroy(&attr_tip);
 
     printf("Failed to create receiver thread\n");

      RETVALUE(RFAILED);
   }
#endif

/* TODO:: Below flag to be enabled when LL2 TIP message is handled completely */
   if ((SCreatePThread(&tId_tip, &attr_tip, TipCSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr);
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }
#ifndef TIP_L3
   if ((SCreatePThread(&tId_tip, &attr_tip, TipDSocketRecv, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr);
      pthread_attr_destroy(&attr_tip);
      printf("Failed to create TIP receiver thread\n");
      RETVALUE(RFAILED);
   }
#endif
#ifdef TIP_UPPER_L2
   printf("\n TIP DEBUG:: Creating thread to post EGTP ticks from initDrvrTsk \n");
   tipInitEgRecv();
#endif
   pthread_attr_destroy(&attr);
   pthread_attr_destroy(&attr_tip);
   RETVALUE(ROK);
}
#ifdef TIP_UPPER_L2
void *tipSendTtiIndEgToRecvData (void *in)
{
  static Pst pst = {.dstProcId=20/*Ul2 ProcId ProcId*/,.srcProcId=20/*UL2 ProcId*/,.dstEnt = ENTEG, .srcEnt = ENTSM};
  Buffer *mBuf = NULLP;
  pst.dstProcId = SFndProcId();
  pst.srcProcId = SFndProcId();
  printf("\n\n********* NIRANJAN DEBUG:: Waiting for start post trigger (DAM cell add) **********\n\n");
  while(!strtPst)
  {
     usleep(10000);
  }
  printf("\n\n********* NIRANJAN DEBUG:: TIP EGTP TICK PST STARTED **********\n\n");
  while(1)
  {
     usleep(1000);
     mBuf = NULLP;
     SGetMsg(0, 0, (Buffer **) &mBuf);
     pst.event = 22;
     pst.dstProcId = SFndProcId();
     pst.srcProcId = SFndProcId();
     SPstTsk(&pst,mBuf);

     mBuf = NULLP;
     SGetMsg(0, 0, (Buffer **) &mBuf);
     pst.event = 23;
     SPstTsk(&pst,mBuf);
  }
   pthread_exit(NULLP);
}

Void tipInitEgRecv()
{
   pthread_t  tId_tip;
   pthread_attr_t  attr_tip;
   
   pthread_attr_init(&attr_tip);
   pthread_attr_setstacksize(&attr_tip, (size_t)NULLD);
   pthread_attr_setscope(&attr_tip, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr_tip, PTHREAD_CREATE_DETACHED);
   if ((SCreatePThread(&tId_tip, &attr_tip, tipSendTtiIndEgToRecvData, (Ptr)NULL)) != 0)
   {
      printf("Failed to create TIP receiver thread\n");
   }
   pthread_attr_destroy(&attr_tip);
   RETVOID;
}
#endif



/********************************************************************30**
  
         End of file:     pt_ss.c@@/main/1 - Mon Nov 17 15:54:31 2008
  
*********************************************************************31*/
  

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      es   1. Initial Release

                                   NULLP */   
/**********************************************************************91*/
