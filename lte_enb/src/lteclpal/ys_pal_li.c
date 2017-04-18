
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_pal_li.c
  
     Sid:      ys_pal_li.c@@/main/2 - Thu Dec  2 02:27:19 2010
  
     Prg:      hsingh 
  
**********************************************************************/

/** @file ys_pal_li.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files -- defines (.h) */
#ifndef SS_CAVIUM
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>
#endif

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management typedefs for CL */
#include "tfu.h"
#include "ys_pal_err.h"        /* YS error defines */
#include "ys_pal.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x" 

/* header/extern include files (.x) */
/* header include files (.h) */
/* ys005.102: Introduced the new flag YS_ENB_CFG for ENB.
 * This should be disabled at the UESIM side */
#ifdef YS_ENB_CFG

#ifndef SS_CAVIUM
PRIVATE Void *ysPalRcvrActvTsk ARGS ((Void *tskPtr));

PUBLIC struct sockaddr_in dstAddr;  /* local Internet address/port */

#ifdef ANSI
PUBLIC S16 ysPalInitRcvrTsk
(
Void
)
#else
PUBLIC S16 ysPalInitRcvrTsk()
#endif
{
   pthread_t tId;
   pthread_attr_t attr;

#ifdef LTE_LNX_AFFINITY
   cpu_set_t cpuSet;
#endif

   /* ys002.102: Added missed trace macro */
   TRC2(ysPalInitRcvrTsk)

   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, (size_t)NULLD);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

#ifndef TENB_SPLIT_ARCH_SUPPORT
   if ((pthread_create(&tId, &attr, ysPalRcvrActvTsk, (Ptr)NULL)) != 0)
#else
   if ((SCreatePThread(&tId, &attr, ysPalRcvrActvTsk, (Ptr)NULL)) != 0)
#endif
   {
      pthread_attr_destroy(&attr);
 
      YS_DBG_ERR((_ysp, "Failed to create receiver thread\n"));

      RETVALUE(RFAILED);
   }

#ifdef LTE_LNX_AFFINITY

   /* Following is applicable only for Linux machine (Calpella)
      from Intel. Core number used here can be changed
      accordingly, as expected on the machine of interest.*/

   /* Initialize the cpu mask */
   CPU_ZERO(&cpuSet);

   /* Set the cpu mask */
   CPU_SET(YS_RCVR_CPUCORE_VAL, &cpuSet);

   /* Set thread affinity for linux */
   if (pthread_setaffinity_np(tId, sizeof(cpuSet), &cpuSet) < 0)
   {
      printf("Set affinity failed for PAL reciever thread\n");
      exit(0);
   }
#endif

   RETVALUE(ROK);
}

#ifdef ANSI
PRIVATE Void *ysPalRcvrActvTsk
(
Void *tskPtr
)
#else
PRIVATE Void *ysPalRcvrActvTsk(tskPtr)
Void *tskPtr;
#endif
{
   struct sockaddr_in srcAddr;  /* local Internet address/port */
   struct sockaddr remSockAddr;
   U32    remAddrLen = 0;
   ssize_t recvLen;
   U8     buf[YS_MAX_RCVD_BUF_LEN];
   Buffer *rcvBuf;
   S16    ret;
   U8     prmtv;
   Pst    pst;
   /* ys004.102: g++ compilation */
   if((int)(ysCb.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() sockfd error lol!");
      exit(1);
   }

   cmMemset((U8*)&srcAddr, 0, sizeof(srcAddr));
   srcAddr.sin_family      = AF_INET;
#ifdef LTE_PAL_ENB   
   srcAddr.sin_port        = htons(YS_PORT_ENB);
   srcAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_ENB);
#else
   srcAddr.sin_port        = htons(YS_PORT_UE);
   srcAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_UE);
#endif

   if(bind(ysCb.sockfd, (struct sockaddr *)&srcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }
   cmMemset((U8*)&dstAddr, 0, sizeof(dstAddr));
   dstAddr.sin_family      = AF_INET;
#ifdef LTE_PAL_ENB   
   dstAddr.sin_port        = htons(YS_PORT_UE);
   dstAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_UE);
#else
   dstAddr.sin_port        = htons(YS_PORT_ENB);
   dstAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_ENB);
#endif

   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.dstEnt = ENTTF;
   pst.srcEnt = ENTTF;
   pst.srcInst = 0;
   pst.dstInst = 0;
   pst.route = RTESPEC;
   pst.prior = PRIOR0;
   pst.region = ysCb.ysInit.region;
   pst.pool = ysCb.ysInit.pool;

   /*loop forever*/
   while(1)
   {
      /* clear the structure */   
      cmMemset((U8*)&remSockAddr, 0, sizeof(remSockAddr));

      /*read the data from socket*/
      if((recvLen = recvfrom(ysCb.sockfd, buf, sizeof(buf), 0, 
                            (struct sockaddr *)&remSockAddr, 
                            (socklen_t *)&remAddrLen)) == -1)

      {
         YS_DBG_ERR((_ysp, "Server-recvfrom() error\n"));
         continue;
      }

      /* copy data to a message structure */
      ret = SGetMsg(ysCb.ysInit.region, ysCb.ysInit.pool, &rcvBuf);
      if (ret != ROK)
      {
         YS_DBG_ERR((_ysp, "SGetMsg failed\n"));
         continue;
      }

      ret = SAddPstMsgMult(buf, recvLen, rcvBuf);
      if (ret != ROK)
      {
         YS_DBG_ERR((_ysp, "SAddPstMsgMult failed\n"));
         continue;
      }

      ret = SRemPreMsg(&prmtv, rcvBuf);
      if (ret != ROK)
      {
         YS_DBG_ERR((_ysp, "SRemPreMsg failed\n"));
         continue;
      }

      pst.selector = YS_SELECTOR_LC;
      pst.event = prmtv;

#ifdef LTE_PAL_ENB   
      SPstTsk(&pst, rcvBuf);
#else
/* ys003.102: Changes for end to end performance */
      SPstTsk(&pst, rcvBuf);
#endif      
   }

   pthread_exit(NULLP);
}

#ifdef ANSI
PUBLIC S16 ysPalSend2Peer
(
Buffer *mBuf,
U8      cellId
)
#else
PUBLIC S16 ysPalSend2Peer(mBuf, cellId)
Buffer *mBuf;
U8      cellId
#endif
{
   S32     ret;                 /* temporary return value */
   ssize_t ret1;                 /* temporary return value */
   MsgLen  msgLen;              /* message length */ 
   MsgLen  bufLen;              /* send buffer length */
   U8      sendBuf[YS_MAX_RCVD_BUF_LEN];

   /* ys002.102: Added missed trace macro */
   TRC2(ysPalSend2Peer)

   ret = SFndLenMsg(mBuf, &bufLen);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }
   ret = SCpyMsgFix(mBuf, 0, bufLen, sendBuf, &msgLen);
   if ((ret != ROK) || (msgLen != bufLen)) 
   {
      YS_DBG_ERR((_ysp, "SCpyMsgFix failed\n"));
      RETVALUE(RFAILED);
   }

#ifdef YS_TEST_MULT_UE
   /* This changes are made to test atleast one UE per cell
      when multiple cells are configured. Listing port of 
      eNB remains same and only sending port changes. 
      The ys_cfg.txt at UE side needs to be changed */
   dstAddr.sin_port        = htons(YS_PORT_UE + cellId);
#endif /* YS_TEST_MULT_UE */

   ret1 = sendto(ysCb.sockfd, sendBuf, bufLen, 0, 
                (struct sockaddr *)&dstAddr, sizeof(dstAddr)); 
   if(ret1 == -1)
   {
      YS_DBG_ERR((_ysp, "sendto failed\n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

#endif /* SS_CAVIUM */

#else /* YS_ENB_CFG */

#ifndef SS_CAVIUM
PRIVATE Void *ysPalRcvrActvTsk ARGS ((Void *tskPtr));

PUBLIC struct sockaddr_in dstAddr;  /* local Internet address/port */

extern U8 actvIdx;

#ifdef ANSI
PUBLIC S16 ysPalInitRcvrTsk
(
Void
)
#else
PUBLIC S16 ysPalInitRcvrTsk()
#endif
{
   pthread_t tId;
   pthread_attr_t attr;

#ifdef LTE_LNX_AFFINITY
   cpu_set_t cpuSet;
#endif

   /* ys002.102: Added missed trace macro */
   TRC2(ysPalInitRcvrTsk)

   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, (size_t)NULLD);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   if ((pthread_create(&tId, &attr, ysPalRcvrActvTsk, (Ptr)NULL)) != 0)
   {
      pthread_attr_destroy(&attr);
 
      YS_DBG_ERR((_ysp, "Failed to create receiver thread\n"));

      RETVALUE(RFAILED);
   }

#ifdef LTE_LNX_AFFINITY

   /* Following is applicable only for Linux machine (Calpella)
      from Intel. Core number used here can be changed
      accordingly, as expected on the machine of interest.*/

   /* Initialize the cpu mask */
   CPU_ZERO(&cpuSet);

   /* Set the cpu mask */
   CPU_SET(YS_RCVR_CPUCORE_VAL, &cpuSet);

   /* Set thread affinity for linux */
   if (pthread_setaffinity_np(tId, sizeof(cpuSet), &cpuSet) < 0)
   {
      printf("Set affinity failed for PAL reciever thread\n");
      exit(0);
   }
#endif

   RETVALUE(ROK);
}


PUBLIC S16 ysChkAddrActv(struct sockaddr_in *remSockAddr,  Bool * isFrmActv)
{
   if( remSockAddr->sin_addr.s_addr == dstAddr.sin_addr.s_addr )
   {

      *isFrmActv = TRUE;
   }

   RETVALUE(ROK);
} /* end of ysChkAddrActv */



#ifdef ANSI
PRIVATE Void *ysPalRcvrActvTsk
(
Void *tskPtr
)
#else
PRIVATE Void *ysPalRcvrActvTsk(tskPtr)
Void *tskPtr;
#endif
{
   struct sockaddr_in srcAddr;  /* local Internet address/port */
   struct sockaddr remSockAddr;
   U32    remAddrLen = 0;
   ssize_t recvLen;
   U8     buf[YS_MAX_RCVD_BUF_LEN];
   Buffer *rcvBuf;
   S16    ret;
   U8     prmtv;
   Pst    pst;
   Bool    isFrmActv = FALSE;

   if((ysCb.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() sockfd error lol!");
      exit(1);
   }

   cmMemset((U8*)&srcAddr, 0, sizeof(srcAddr));
   srcAddr.sin_family      = AF_INET;
#ifdef LTE_PAL_ENB   
   srcAddr.sin_port        = htons(YS_PORT_ENB);
   srcAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_ENB);
#else
   srcAddr.sin_port        = htons(YS_PORT_UE);
   srcAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_UE);
#endif

   if(bind(ysCb.sockfd, (struct sockaddr *)&srcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }
   cmMemset((U8*)&dstAddr, 0, sizeof(dstAddr));
   dstAddr.sin_family      = AF_INET;
#ifdef LTE_PAL_ENB   
   dstAddr.sin_port        = htons(YS_PORT_UE);
   dstAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_UE);
#else
   /* Default Destination address is that of enodeb1 */
   dstAddr.sin_port        = htons(YS_PORT_ENB[actvIdx]);
   dstAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_ENB[actvIdx]);
#endif

   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.dstEnt = ENTTF;
   pst.srcEnt = ENTTF;
   pst.srcInst = 0;
   pst.dstInst = 0;
   pst.route = RTESPEC;
   pst.prior = PRIOR0;
   pst.region = ysCb.ysInit.region;
   pst.pool = ysCb.ysInit.pool;

   /*loop forever*/
   while(1)
   {
      /* clear the structure */   
      cmMemset((U8*)&remSockAddr, 0, sizeof(remSockAddr));

      /*read the data from socket*/
      if((recvLen = recvfrom(ysCb.sockfd, buf, sizeof(buf), 0, 
                            (struct sockaddr *)&remSockAddr, 
                            (socklen_t *)&remAddrLen)) == -1)

      {
         YS_DBG_ERR((_ysp, "Server-recvfrom() error\n"));
         continue;
      }

       /* Remote socket address contains the address from where
          the data is received */

       /* Check if the data is received from the active enodeb. If so then
         accept otherwise do not process further */
       isFrmActv = FALSE;
       ysChkAddrActv((struct sockaddr_in *)&remSockAddr, &isFrmActv);

      if(isFrmActv)
      {
         /* copy data to a message structure */
         ret = SGetMsg(ysCb.ysInit.region, ysCb.ysInit.pool, &rcvBuf);
         if (ret != ROK)
         {
            YS_DBG_ERR((_ysp, "SGetMsg failed\n"));
            continue;
         }

         ret = SAddPstMsgMult(buf, recvLen, rcvBuf);
         if (ret != ROK)
         {
            YS_DBG_ERR((_ysp, "SAddPstMsgMult failed\n"));
            continue;
         }

         ret = SRemPreMsg(&prmtv, rcvBuf);
         if (ret != ROK)
         {
            YS_DBG_ERR((_ysp, "SRemPreMsg failed\n"));
            continue;
         }

         pst.selector = YS_SELECTOR_LC;
         pst.event = prmtv;

#ifdef LTE_PAL_ENB   
         SPstTsk(&pst, rcvBuf);
#else
         ysActvTsk(&pst, rcvBuf);
#endif 
      }
   }

   pthread_exit(NULLP);
}

#ifdef ANSI
PUBLIC S16 ysPalSend2Peer
(
Buffer *mBuf
)
#else
PUBLIC S16 ysPalSend2Peer(mBuf)
Buffer *mBuf;
#endif
{
   S32     ret;                 /* temporary return value */
   ssize_t ret1;                 /* temporary return value */
   MsgLen  msgLen;              /* message length */ 
   MsgLen  bufLen;              /* send buffer length */
   U8      sendBuf[YS_MAX_RCVD_BUF_LEN];

   /* ys002.102: Added missed trace macro */
   TRC2(ysPalSend2Peer)

   ret = SFndLenMsg(mBuf, &bufLen);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }
   ret = SCpyMsgFix(mBuf, 0, bufLen, sendBuf, &msgLen);
   if ((ret != ROK) || (msgLen != bufLen)) 
   {
      YS_DBG_ERR((_ysp, "SCpyMsgFix failed\n"));
      RETVALUE(RFAILED);
   }

   ret1 = sendto(ysCb.sockfd, sendBuf, bufLen, 0, 
                (struct sockaddr *)&dstAddr, sizeof(dstAddr)); 
   if(ret1 == -1)
   {
      YS_DBG_ERR((_ysp, "sendto failed\n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

#endif /* SS_CAVIUM */

#endif /* YS_ENB_CFG */

/********************************************************************30**
  
         End of file:     ys_pal_li.c@@/main/2 - Thu Dec  2 02:27:19 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2    ys002.102  rk                   1. Added missed trace macro.
$SID$      ys003.102  sriky                1. Performance tuning
/main/2    ys004.102  ms                   1. g++ compilation warning.
/main/2    ys005.102 pbyadgi               1.Introduced the new flag YS_ENB_CFG
                                             for ENB. This should be disabled at 
                                             the UESIM side.
*********************************************************************91*/
