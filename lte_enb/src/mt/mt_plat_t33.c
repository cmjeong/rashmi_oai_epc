/********************************************************************20**

Name:

Type:     C File.

Desc:     Supervisor module is used to communicate with lower arm
using shared memory

File:     mt_plat_t33.c

Sid:      mt_plat_t33.c@@/main/TeNB_Main_BR/1 - Tue Jul  8 12:01:34 2014

Prg:

 ************************************************************************/

#ifdef SS_4GMX_UCORE
#include "mt_4gmx.h"
#include "mt_4gmx.x"
#include "rb_common.h"
#endif /* SS_4GMX_UCORE */


#include "envopt.h"        /* environment options */
#ifdef L2_L3_SPLIT
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
#include <sys/time.h>
/* mt008.21: addition */
#include <errno.h>



/* header include files (.h) */


#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_dep.h"        /* implementation-specific */

#include "cm5.h"           /* common timers */
#include "mt_ss.h"         /* MTSS specific */
#include "mt_err.h"        /* MTSS error defines */

#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "ss_err.h"        /* error */
#include "cm_mem.h"        /* common memory manager */
#ifdef SS_THREAD_PROFILE
#include "ss_err.h"
#endif
#include "sys/syscall.h"
#include "LtePhyL2Api.h"
#include "resultcodes.h"
#include "gen.x"
#include "ssi.x"

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"        /* implementation-specific */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"        /* general */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#ifdef SS_DRVR_SUPPORT
#include "ss_drvr.x"
#endif
#include "cm_llist.x"
#include "cm_mem_wl.x"

#include "ss_gen.x"
#include "kwu.h"
#include "mt_plat_t33.h"
#include "mt_plat_t33.x"
#include "ss_rbuf.h"
#include "ss_rbuf.x"
#define MAX_ICPU_BUF_SIZE 10*1024
#define MT_KW_UL_INST   0
extern S32 clusterMode;
#endif
#ifdef T2K_MEM_LEAK_DBG
EXTERN void InsertToT2kMemLeakInfo(U32 address, U32 size, U32 lineNo, char* fileName);
EXTERN void RemoveFromT2kMemLeakInfo(U32 address, char *file, U32 line);
#endif
extern SsOs osCp;
extern U8 *cmMemset
(
 U8           *str,
 U8           val,
 PTR          len
 );
#ifdef SPLIT_RLC_DL_TASK
EXTERN PUBLIC U8 SUpdMbufMemInfo (Pst    *pst,Buffer *mBuf);
#endif 
#ifdef LC_EGTP_THREAD
PUBLIC S16 mtAddEgtpBufToRing(SsRngBufId ringId,U8 *tmpBuf,U8 *buf, U32 bufLen);
#endif

#ifdef L2_L3_SPLIT
/*
 *
 *     Fun  : DrvrInit
 *
 *     Desc : Initializes uppercore driver task to facilitate communication with
 *            lower arm.
 *
 *     Ret:   ROK      - ok
 *            RFAILED  - failed, general (optional)
 *
 *     Notes: None
 *
 *     File : mt_plat_t33.c
 *
 */
#ifdef ANSI
PUBLIC S16 drvrTskInit
(
Void
)
#else
PUBLIC S16 drvrTskInit()
#endif
{
   S16 ret;

   TRC0(drvrTskInit);

   /* Channel initialized to handle messages targetted towards
    * 4GMX channels, and Vice versa.
    */
   ret = SRegDrvrTsk(0, 0, 1, iccPstTsk, iccIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   AppContext.MsgPerMs = DEFAULT_MESSAGE_COUNT_PER_MS;
   AppContext.MaxMsgSize = DEFAULT_MAX_MESSAGE_SIZE;

   RETVALUE(ROK);
}

/*
 *
 *       Fun:  iccIsTsk
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
 *       File:  mt_plat_t33.c
 *
 */
#ifdef ANSI
PUBLIC void iccIsTsk
(
Inst inst
)
#else
PUBLIC S16 iccIsTsk(inst)
Inst inst;
#endif
{

   TRC0(iccIsTsk);
   printf("%s:%d\n",__func__,__LINE__);
}


/*
 *
 *       Fun:   Post a message to a remote task using supervisor module
 *
 *       Desc:  This function is used to post a message to a TAPA
 *              task.Basically its a message post from Upper ARM to
 *              Lower ARM using shared memory.
 *
 *       Ret:   ROK      - ok
 *              RFAILED  - failed, general (optional)
 *
 *       Notes:
 *
 *       File:  mt_plat_t33.c
 *
 */
#ifdef ANSI
PUBLIC S16 iccPstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
 )
#else
PUBLIC S16 iccPstTsk(pst, mBuf)
Pst *pst;                       /* post information */
Buffer *mBuf;                   /* message to post */
#endif
{
   U8  *pMsg;
   U32     ret;
   MsgLen         bufLen    = 0;
   MsgLen         msgLen    = 0;
   Inst           inst;
   MsgLen         numBytes;
   Buffer         *tmp;
   U16            numBlk = 0;
   U32            flag = 0;
   void *usedHandle = AppContext.hUAII;
   TRC0(iccPstTsk);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (!pst || !mBuf)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Invalid Inputs.NULL pst/mBuf");
      if (mBuf)
      {
         SPutMsg(mBuf);
      }
      RETVALUE(RFAILED);
   }

#endif
   /* Remove the channel id */
   CMCHKUNPKLOG(cmUnpkInst, &inst, mBuf, 0, pst);

   if (inst != 0)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Wrong Instance");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

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

   if(bufLen > MAX_ICPU_BUF_SIZE)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Message size is > 10*1024");
#endif
      printf("Message size is > 10*1024\n");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }


#ifndef UL_RLC_NET_CLUSTER
   if (((clusterMode == RADIO_CLUSTER_MODE) && (pst->srcEnt == ENTKW)
            && (pst->srcInst == MT_KW_UL_INST)) ||
         ((clusterMode == NET_CLUSTER_MODE) && ((pst->srcEnt == ENTPJ) || (pst->srcEnt == ENTEG) || (pst->srcEnt == ENTEU) || (pst->srcEnt == ENTPX))))
   {
      usedHandle = AppContext.hUAII_second;
   }
#else
   if(clusterMode == NET_CLUSTER_MODE) 
   {
      if(((pst->srcEnt == ENTPJ) || (pst->srcEnt == ENTEG) || (pst->srcEnt == ENTEU) || (pst->srcEnt == ENTPX)))
      {
         usedHandle = AppContext.hUAII_second;
      }else if(pst->srcEnt == ENTKW)
      {
         usedHandle = AppContext.hUAII_third;
      } 
   }
#endif
   if((pst->srcEnt == ENTPJ) && (pst->event == 0x5b))  /* KWU_EVT_UPLANE_DAT_REQ */
   {
      /* It is a U-Plane data from PDCP to RLC.                */
      /* Loop through DBlk and use scatter-gather technique.   */
      /* SG_FIRST: Identifier for 1st data block.              */
      /* SG_NEXT: Identifier for next data block till last -1. */
      /* SG_LAST: Identifier for last data block.              */
      /* ICC_TF_KAAT: TL_Put does not free the packet.         */
      tmp = mBuf->b_cont;
      numBlk++;
      
      numBytes = tmp->b_wptr - tmp->b_rptr;
      while(tmp->b_cont)
      {
         numBlk++;
         if(numBlk == 2)
         {
            flag = SG_FIRST | ICC_TF_KAAT;
         }
         else
         {
            flag = SG_NEXT | ICC_TF_KAAT;
         }
         ret = TL_Put(usedHandle, tmp->b_rptr, numBytes, AppContext.TxID, flag);
         /* Traverse to next DBlk */
         tmp = tmp->b_cont;
         numBytes = tmp->b_wptr - tmp->b_rptr;
      }
      if(numBlk == 1)
      {
         flag = ICC_TF_KAAT;
      }
      else
      {
         flag = SG_LAST | ICC_TF_KAAT;
      }
      ret = TL_Put(usedHandle, tmp->b_rptr, numBytes, AppContext.TxID, flag);

      SPutMsg(mBuf);
   }
   else
   {
      /*Locks*/
      pMsg = TL_Alloc(usedHandle, bufLen);
      
#ifdef T2K_MEM_LEAK_DBG
      InsertToT2kMemLeakInfo((U32)(pMsg - ((U32)pMsg % 512)),bufLen, __LINE__, __FILE__);
#endif

      if (pMsg)
      {
         ret = SCpyMsgFix(mBuf, 0, bufLen, (Data*)pMsg, &msgLen);

         if((ret != ROK) || (bufLen != msgLen))
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
                  "SAddPstMsgMult failed");
#endif
            printf("SAddPstMsgMult failed\n");
            SPutMsg(mBuf);
            TL_Free(usedHandle, pMsg);
            RETVALUE(RFAILED);
         }
         /*Done with buffer, free it*/
         SPutMsg(mBuf);
#ifdef T2K_MEM_LEAK_DBG
         RemoveFromT2kMemLeakInfo((U32)(pMsg - ((U32)pMsg % 512)), __FILE__, __LINE__);
#endif
         ret = TL_Put(usedHandle, pMsg, bufLen, AppContext.TxID, 0);

         if(ret != SUCCESS)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO, "TL_Put failed");
#endif
            printf("TL Put failed\n");
            TL_Free(usedHandle, pMsg);
            RETVALUE(RFAILED);
         }
      }
   }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:   iccPktReceiver
 *
 *       Desc:  This primitive is a listener for messages from shared memory of clusters..
 *
 *       Ret:   ROK      - ok
 *              RFAILED  - failed, general (optional)
 *
 *
 *       Notes: None
 *
 *       File:  mt_plat_t33.c
 *
 */
#ifdef ANSI
PUBLIC Void *iccPktReceiver
(
Void *parm
)
#else
PUBLIC Void *iccPktReceiver
(
Void *parm;
)
#endif
{
   S16           ret;
   Buffer        *mBuf;
   Pst            nPst;
   U32   MsgSize;
   U8  *pMsg;
   TRC0(iccPktReceiver);
   UNUSED(parm);
   while ((ret = sem_wait(&osCp.dep.ssStarted) != ROK) && (errno == EINTR))
      continue;

   printf("\n iccPktReceiver syscall(SYS_gettid)=%ld\n", syscall(SYS_gettid));

   while (!AppContext.ExitStatus)
   {
      /* handle RX stuff */
      if ((pMsg = TL_WGet(AppContext.hUAII, &MsgSize)) != NULL)
      {
#ifdef T2K_MEM_LEAK_DBG
         InsertToT2kMemLeakInfo((U32)(pMsg - ((U32)pMsg % 512)), MsgSize, __LINE__, __FILE__);
#endif
         if(MsgSize > MAX_ICPU_BUF_SIZE)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
                  "Message length is greater than MAX_BUF_SIZE");
#endif
            TL_Free(AppContext.hUAII, pMsg);
            printf("MsgSize > 100*MAX_ICPU_BUF_SIZE = %lu \n", MsgSize);
            return NULL;
         }
         if (clusterMode == NET_CLUSTER_MODE)
         {
          #ifdef T2K_MEM_LEAK_DBG 
            if (ROK != SAttachPtrToBufNew(DFLT_REGION, 2, pMsg, MsgSize,
                     &mBuf,__FILE__,__LINE__))
          #else
            if (ROK != SAttachPtrToBuf(DFLT_REGION, 2, pMsg, MsgSize, &mBuf))
          #endif
            {
               printf("Failed to attach the pointer to mBuf\n");
               TL_Free(AppContext.hUAII, pMsg);
               return NULL;
            }

            CMCHKUNPK(cmUnpkPst, &nPst, mBuf);
#if (defined(L2_L3_SPLIT) && defined(ICC_RECV_TSK_RBUF))
            /* Implimented ring buffer to send Data pkts from ICC pkt receiver thread to PDCP UL entity */
            if((nPst.dstEnt == ENTPJ) && (nPst.event == KWU_EVT_DAT_IND))  /* KWU_EVT_DAT_IND */
            {

               Void *elem = NULLP;
               RxmBufReq *rxMbufReq = NULLP;
               elem = SRngGetWIndx(SS_RNG_BUF_RX_TO_ULPDCP);
               rxMbufReq = (RxmBufReq *) elem;
               if (NULLP != elem)
               {
                  rxMbufReq->mBuf = mBuf;
                  rxMbufReq->pst = nPst; 
                  SRngIncrWIndx(SS_RNG_BUF_RX_TO_ULPDCP);
                  SsRngInfoTbl[SS_RNG_BUF_RX_TO_ULPDCP].pktRate++;
               } 
               else /* Drop the pkt if the ring is full or if the ring element is already in use */
               {
                  SsRngInfoTbl[SS_RNG_BUF_RX_TO_ULPDCP].pktDrop++;
                  SPutMsg(mBuf);
                  ret = RFAILED;
               }
            }
            else /* For control messages SPstTsk will be done */
#endif
            {
 
               ret = SPstTsk(&nPst,mBuf);

               if(ROK != ret)
               {
                  printf("SPstTsk failed...(%d/%d/%d/%d/%d)  \n",
                        nPst.srcProcId,nPst.dstProcId,nPst.srcInst,nPst.dstInst,
                        nPst.event);
               }
            }

            pMsg = NULL;
            MsgSize = 0;
         }
         else
         {
         #ifdef T2K_MEM_LEAK_DBG
            if (ROK != SAttachPtrToBufNew(DFLT_REGION, 2, pMsg, MsgSize,
                     &mBuf,__FILE__,__LINE__))
         #else
             if (ROK != SAttachPtrToBuf(DFLT_REGION, 2, pMsg, MsgSize, &mBuf))
         #endif
            {
               printf("Failed to attach the pointer to mBuf\n");
               TL_Free(AppContext.hUAII, pMsg);
               return NULL;
            }

            CMCHKUNPK(cmUnpkPst, &nPst, mBuf);
            /* Implimented ring buffer to send Data pkts from ICC pkt receiver thread to RLC DL entity */
#if (defined(L2_L3_SPLIT) && defined(ICC_RECV_TSK_RBUF))
            if((nPst.srcEnt == ENTPJ) && (nPst.event == KWU_EVT_UPLANE_DAT_REQ))  /* KWU_EVT_UPLANE_DAT_REQ */
            {

               Void *elem = NULLP;
               RxmBufReq *rxMbufReq = NULLP;
               elem = SRngGetWIndx(SS_RNG_BUF_RX_TO_DLRLC);
               rxMbufReq = (RxmBufReq *) elem;
               if (NULLP != elem)
               {
#ifdef SPLIT_RLC_DL_TASK
                  SUpdMbufMemInfo (&nPst,mBuf);
#endif 
                  rxMbufReq->mBuf = mBuf;
                  rxMbufReq->pst = nPst; 
                  SRngIncrWIndx(SS_RNG_BUF_RX_TO_DLRLC);
                  SsRngInfoTbl[SS_RNG_BUF_RX_TO_DLRLC].pktRate++;
               } 
               else /* Drop the pkt if the ring is full or if the ring element is already in use */
               {
                  SsRngInfoTbl[SS_RNG_BUF_RX_TO_DLRLC].pktDrop++;
                  SPutMsg(mBuf);
                  ret = RFAILED;
               }

            }
            else /* For control messages SPstTsk will be done */
#endif
            {
               ret = SPstTsk(&nPst,mBuf);
               if(ROK != ret)
               {
                  printf("SPstTsk failed  \n");
                  printf("SPstTsk failed...(%d/%d/%d/%d/%d)  \n",
                        nPst.srcProcId,nPst.dstProcId,nPst.srcInst,nPst.dstInst,
                        nPst.event);
               }
            }
            pMsg = NULL;
            MsgSize = 0;
         }
      }

   }

   return NULL;
}

#ifdef ANSI
PUBLIC U32 iccTtiTick
(
)
#else
PUBLIC U32 iccTtiTick()
#endif
{
   Pst pst;
   Buffer *mBuf = NULLP;
   TRC0(iccTtiTick);

   cmMemset((U8*)&pst,0x00,sizeof(Pst));

   pst.dstEnt = ENTEG;
   pst.srcEnt = ENTYS;

   while (!AppContext.ExitStatus)
   {

      /*Get Message for General Use*/
      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
      pst.event = 22;
      SPstTsk(&pst,mBuf);

      /*Get Message for General Use*/
      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
      pst.event = 23;
      SPstTsk(&pst,mBuf);
      usleep(1000);
   }

   RETVALUE(SUCCESS);
}

void App_SigExitCallback(int signum)
{
   AppContext.ExitStatus = TRUE;
}


#if (defined (MAC_FREE_RING_BUF) || defined (RLC_FREE_RING_BUF))
S16 mtAddBufToRing(SsRngBufId ringId,void *bufPtr,U8 freeType)
{
   S16 ret1 = ROK;
   
   Void *elem = NULLP;

   RgKwFreeInfo *bufFreeInfo = NULLP;
   elem = SRngGetWIndx(ringId);

   if (NULLP != elem)
   {
      bufFreeInfo = (RgKwFreeInfo *) elem;

      bufFreeInfo->bufToFree = bufPtr;
      bufFreeInfo->freeType  = freeType;

      SRngIncrWIndx(ringId);

      SsRngInfoTbl[ringId].pktRate++;
   }   
   else
   {
      printf("Free Ring FULL id %d!!! \n",ringId);
      SsRngInfoTbl[ringId].pktDrop++;
      ret1 = RFAILED;
   }
   RETVALUE(ret1);
}
#endif

#ifdef LC_EGTP_THREAD
PUBLIC S16 mtAddEgtpBufToRing(SsRngBufId ringId,U8 *tmpBuf,U8 *buf, U32 bufLen)
{
   S16 ret1 = ROK;
   
   Void *elem = NULLP;

   EgWrFreeInfo *bufFreeInfo = NULLP;
   elem = SRngGetWIndx(ringId);

   if (NULLP != elem)
   {
      bufFreeInfo = (EgWrFreeInfo *) elem;

      bufFreeInfo->tmpBuf = tmpBuf;
      bufFreeInfo->buf    = buf;
      bufFreeInfo->bufLen = bufLen;

      SRngIncrWIndx(ringId);

      SsRngInfoTbl[ringId].pktRate++;
   }   
   else
   {
      printf("Egtp Ring FULL id %d!!! \n",ringId);
      SsRngInfoTbl[ringId].pktDrop++;
      ret1 = RFAILED;
   }
   RETVALUE(ret1);
}
#endif

#endif


/********************************************************************30**

  End of file:     mt_plat_t33.c@@/main/TeNB_Main_BR/1 - Tue Jul  8 12:01:34 2014

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

  ver        pat        init                  description
  ---------  ---------  ----------  -------------------------------------
  /main/1      --------     ------    1. Initial release
 *********************************************************************91*/

