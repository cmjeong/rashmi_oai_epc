


///////////////////////////////////////////////////////////////////////////////////////////////////
// @ author Vikram
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* RLOG_MODULE_NAME="ENBAPP";
static int RLOG_FILE_ID=114;


static int RLOG_MODULE_ID=64;


#include<stdio.h>
#ifndef NMM_PHYINTERFACE_CPP_
#define NMM_PHYINTERFACE_CPP_

#if 0
#include <sys/select.h>
#include <mqueue.h>
#include "wr.h"
#include "apidefs.h"
#include "osal.h"
#include "resultcodes.h"
#endif

#ifdef L2_L3_SPLIT
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
#endif

#include "LtePhyL2Api.h"
#include "wr_nmm.h"
#include "ctrlmsg.h"
#ifdef WR_RSYS_OAM
#include "wr_msm_common.h"
extern MsmLteeNodeBparams lteeNodeBparams;
void fillAntennaPortInfo(U32 *antennaPort);
RESULTCODE InitAdi(U32 configBand, U32 configTxAnt, U32 configRxAnt, U32 configLoopback, U32 configDejitter_init);
#endif
void* phyNmmListner(void* pArg);
void dump_hex(int len, U8 *p);
RESULTCODE NmmDispatch(U32 size, PTR msg);
PTR IcpuAllocBlock(void);

PUBLIC S32 ssCheckAndAddMemoryRegionMap ARGS((pthread_t  threadId,
                                               Region region));

void wrHandleSnfMsgs(Buffer *ptrClMsg);
#define MSGHDR_PARAMHDR_LEN (sizeof(MSGHEADER) + sizeof(PARAMHEADER))
#define MSGHDR_LEN (sizeof(MSGHEADER))
#define MAX_NMM_MSG_LEN   1024

mqd_t g_RemMsgQIdSend;
mqd_t g_RemMsgQIdRecv;

///////////////////////////////////////////////////////////////////////////////////////////////////
//    @Function : initClNmmRecvTask
//     @param[in]: bMsgType - uint8_t
//    This funtions is used to create a thread which listens for NMM message from L1.
///////////////////////////////////////////////////////////////////////////////////////////////////

void initNmmTask(void)
{
   pthread_t taskId;
   pthread_attr_t attr;
   struct mq_attr qattr;
   int policy;
   S32   ret = FALSE;

   struct sched_param schedParams;
        qattr.mq_flags=0;
        qattr.mq_maxmsg=100;
        qattr.mq_msgsize=512;
        qattr.mq_curmsgs=0;

   g_RemMsgQIdSend = mq_open("/REMQ", O_WRONLY | O_CREAT,(S_IRWXU|S_IRWXG|S_IRWXO),&qattr);
   g_RemMsgQIdRecv = mq_open("/ENBQ", O_RDONLY | O_CREAT,(S_IRWXU|S_IRWXG|S_IRWXO),&qattr);

   if (g_RemMsgQIdSend == -1 || g_RemMsgQIdRecv == -1) 
   {
      /*127802*/
     RLOG0(L_ERROR, "Failed to open REMQ ..exiting");
               perror("NMMTask:");
      exit(0);
   }

   pthread_attr_init(&attr);
#if 1
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   /* When the thread is created, we check for the memory mapping table if
    * threadId can be placed in thread memory map table. If it is not able to place
    * threadId is stored in tmporary array. Once thread is created successful,
    * thread_cancel is sent for each thread which are created before. All the 
    * threads are made to wait on sema which is cancel point for thread.
    */
   while(ret == FALSE)
   {
      if ((pthread_create(&taskId, &attr, phyNmmListner, NULLP)) != 0)
      {
         RLOG0(L_ERROR, "initNmmTask() pthread_create failed");
         pthread_attr_destroy(&attr);
         RETVOID;
      }

      ret = ssCheckAndAddMemoryRegionMap(taskId, (SS_MAX_REGS-1));
   }
   RLOG1(L_INFO, "taskId =%ld\n", (U32)taskId);
#else
   pthread_create(&taskId, &attr, phyNmmListner, NULL);
   ret = ssCheckAndAddMemoryRegionMap(taskId, SS_MAX_REGS - 1);
   if(FALSE == ret)
   {
      RLOG1(L_ERROR, "Not able to register NMM %ld task with memory map, exiting", taskId);
   }
#endif
   schedParams.sched_priority = SCHED_RR;
   pthread_getschedparam(taskId, &policy, &schedParams);
   pthread_setschedparam(taskId, SCHED_RR, &schedParams);

}

void dump_hex(int len, U8 *p)
{
   int i = 0;
   for(i=0; i<len; i++)
   {
    /* 127802 */
     RLOG1(L_DEBUG, "%x ", p[i]); 
      if( i % 10 == 0 )
     /* 127802 */
    RLOG0(L_DEBUG, "\n");
   }
}


RESULTCODE NmmDispatch(U32 size, PTR msg)
{

   dump_hex(size, (U8*)msg);

   if(((PGENMSGDESC )msg)->msgType == PHY_INIT_IND)
   {
      RLOG0(L_ERROR, "NmmDispatch:Received PhyInitInd @NMM : Dropping");
      return MAC_SUCCESS;
   }
        

   if (mq_send(g_RemMsgQIdSend, (const char*)msg, size, ((PGENMSGDESC )msg)->msgType) < 0 )
   {
      RLOG0(L_ERROR, "NmmDispatch: Failed to send message to REM"); 
      RLOG3(L_DEBUG, "NmmDispatch: Sending Msg to REM Type=%d MSize=%lu, TSize=%lu",((MSGHEADER*)msg)->type, ((MSGHEADER*)msg)->length, size); 
   }

   return MAC_SUCCESS;
}

void* phyNmmListner(void* pArg)
{
   U8 szNmmMsg[MAX_NMM_MSG_LEN];
#ifdef L2_L3_SPLIT
   U32 ret = FALSE;
#endif
   int nmmMsgLen,dest;
   Buffer *mBuf = NULLP;
   Pst     pst;
#ifdef L2_L3_SPLIT      
   while ((ret = sem_wait(&osCp.dep.ssStarted) != ROK) && (errno == EINTR))
      continue;
#endif
   /*127802*/
   RLOG0(L_DEBUG, "NMM Task Started ....");
   printf("\n NMM syscall(SYS_gettid)=%ld\n", syscall(SYS_gettid));
 
   while( (nmmMsgLen = mq_receive(g_RemMsgQIdRecv, (char*)szNmmMsg, MAX_NMM_MSG_LEN, (unsigned*)&dest)) >= 0 )
   {
      if( nmmMsgLen == 0 )
         continue;


      dump_hex(nmmMsgLen, (U8*)szNmmMsg);


      /*when we receive the message, same is converted into Mbuf and Posted to the NMM TAPA Task.
        Later based the Message type, Appropriate action is taken.
       */

      /*SS_MAX_REGS-1 is the Timer Region as as of now TIMER is not running,
        hence using the same to post message to CL */

      SGetMsg(SS_MAX_REGS-1, 0, (Buffer **) &mBuf);

      SAddPstMsgMult(szNmmMsg,nmmMsgLen,mBuf);

      cmMemset((U8*)&pst,0x00,sizeof(Pst));

      pst.dstEnt = ENTYS;
      pst.srcEnt = ENTYS;
#ifdef L2_L3_SPLIT      
      pst.dstProcId = 1;
      pst.srcEnt = ENTWR;
#endif
      pst.event = szNmmMsg[2];
      SPstTsk(&pst,mBuf);
   }

     /*127802*/
   RLOG0(L_INFO, "NMM Task Exiting"); 
   perror("NMMTask:");

   return NULL;
}

void wrHandleSnfMsgs(Buffer *ptrClMsg)
{
   RETVOID;
}
#ifdef L2_L3_SPLIT      


/** @brief This function is responsible for handling the incoming NMM msgs from PHY
 *
 * @details
 *
 *     Function: wrHandleNmmMsg
 *
 *         Processing steps:
 *         - Invoke the handlers based on the MsgType
 *
 * @param[in] mBuf : Incoming msg
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC U16 wrHandleNmmMsg
(
   Buffer *mBuf
)
{
   Data       *buf = NULLP;
   MsgLen cLen;
   S16 ret = ROK;
   MsgLen        nmmMsgLen;
   U8         msgType;
   SFndLenMsg(mBuf,(MsgLen *)&nmmMsgLen);
   if( ROK != SGetSBuf(SS_MAX_REGS-1, 0, &buf, (Size)nmmMsgLen))
   {
      RETVALUE(RFAILED);
   }

   if(ROK != SCpyMsgFix(mBuf, (MsgLen)0, (MsgLen)nmmMsgLen,
               (Data*) (buf), (MsgLen*)&cLen))
   {
      SPutSBuf(SS_MAX_REGS-1, 0, (Data *)buf, (Size)nmmMsgLen);
      RETVALUE(RFAILED);
   }

   msgType = ((PGENMSGDESC )buf)->msgType;
   if(msgType >= NMM_START && msgType <= NMM_CMD)
   {
      ret = NmmDispatch(cLen, (PTR)buf);
   }
   else
   {
      printf("Invalid message received for NMM \n");
   }
   SPutMsg(mBuf);
   RETVALUE(ROK);
}

#endif
#endif
