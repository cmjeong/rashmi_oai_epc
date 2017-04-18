/********************************************************************20**

     Name:

     Type:     C File.

     Desc:     Supervisor module is used to communicate with lower arm
               using shared memory

     File:     mt_4gmx.c

     Sid:      mt_4gmx.c@@/main/TeNB_Main_BR/8 - Thu Apr 24 17:09:29 2014

     Prg:

************************************************************************/

#ifdef SS_4GMX_UCORE
#include "mt_4gmx.h"
#include "mt_4gmx.x"
#include "rb_common.h"


/*Initialize inter cpu configuration*/
SsRegIcpuCfg icpuCfg[SS_MAX_TTSKS] = ICPUINIT; /*Initializes inter cpu configuration*/

PUBLIC pthread_mutex_t ttiMutex = PTHREAD_MUTEX_INITIALIZER;
EXTERN Void ysMsSndPhyShutDown();
void ssTtiLock()
{
   pthread_mutex_lock(&ttiMutex);
}

void ssTtiUnlock()
{
   pthread_mutex_unlock(&ttiMutex);
}


/*
 *
 *     Fun  : uarmGetDstInstId
 *
 *     Desc : Provides the instance id  of larm corresponding to ent and inst ID
 *
 *     Ret:  core id - SUCCESS
 *           -1 - FAILURE
 *
 *     Notes: None
 *
 *     File : ss_supervisor.c
 *
 */
#ifdef ANSI
PUBLIC S16 uarmGetDstInstId
(
U32 ent,
U32 inst
)
#else
PUBLIC S16 uarmGetDstInstId(ent,inst)
U32 ent;
U32 inst;
#endif
{
   U32 i = 0;

   TRC0(uarmGetDstInstId);

   for(i=0;i<SS_MAX_TTSKS;i++)
   {
      if((icpuCfg[i].Ent == RB_END) && (icpuCfg[i].Inst == RB_END) && (icpuCfg[i].CoreId == RB_END))
      {
         break;
      }

      if((icpuCfg[i].Ent == ent) && (icpuCfg[i].Inst == inst))
      {
         return IID_CORE + icpuCfg[i].CoreId;
      }
   }
   return -1;
}

void ssPrintTrace(char *s, U32 startTime)
{
    /*printf("Time consumed %s is %d\n", s, (MacGetTick() - startTime)/150);*/
}
void printPointer(PTR ptr)
{
   /*printf("Cfg elem %x %x\n", ptr, IcpuGetPhys((PTR)ptr));*/
}

PTR ssGetVirPtr(PTR ptr)
{
    RETVALUE(IcpuGetVirt(ptr));
}



/* Debug code only*/
extern U32 gMsgType[20][20];
/*extern U32 ysGT;*/
void storeMessageTypes(MAC2PHY_QUEUE_EL*  ptr)
{
     int cnt=0;
     MAC2PHY_QUEUE_EL *tmpPtr = ptr;
     while(tmpPtr)
     {
        gMsgType[ysGT%10][cnt++] = tmpPtr->MessageType;
        tmpPtr = ssGetVirPtr(tmpPtr->Next);
     }
     gMsgType[ysGT%10][cnt++] = cnt;
}

void ssMsgFreeBuffer(PTR ptr)
{
    (MsgFreeBuffer((PMSGHEADER)ptr));
}



PTR ssGetPhyPtr(PTR ptr)
{
    RETVALUE(IcpuGetPhys(ptr));
}

extern volatile unsigned long *Timer0;
PUBLIC volatile unsigned long ssTimer0GetCntr(void)
{
     RETVALUE(*(Timer0+1));
}

void printHex1(char *s, void *pApi)
{
    int i,j;
    unsigned char *pDat;
    pDat = (unsigned char *) pApi;
    printf("%s\n", s);
    for (i = 0; i < 64; i += 16)
    {
        for (j = 0; j < 16; j++)
        {
            printf("%02X ", pDat[j]);
	}
	for (j = 0; j < 16; j++)
	{
	    if (isprint(pDat[j]))
	        printf("%c", pDat[j]);
	    else
	        printf(".");
	}
	printf("\n");
	pDat += 16;
    } 
}

void printfHex(char *s, void *pApi)
{
    /*int i,j;
    unsigned char *pDat;
    pDat = (unsigned char *) pApi;
    printf("%s\n", s);
    for (i = 0; i < 64; i += 16)
    {
        for (j = 0; j < 16; j++)
        {
            printf("%02X ", pDat[j]);
	}
	for (j = 0; j < 16; j++)
	{
	    if (isprint(pDat[j]))
	        printf("%c", pDat[j]);
	    else
	        printf(".");
	}
	printf("\n");
	pDat += 16;
    } */
}



#define RoundUp32(x)            (((x)+3)&(~3))
#define ROUND(x, dx)  (((x) + ((dx) - 1) ) & ~((dx) - 1))
/*
*
*       Fun:   ssMsgAppendU32
*
*       Desc:  This primitive is used to Append U32
*
*       Ret:
*
*       Notes: None
*
*       File:  ys_ms_li.c`
*
*/
#ifdef ANSI
PUBLIC S16 ssMsgAppendU32
(
PMSGHEADER msg, 
U16 paramID, 
U32 paramData
)
#else
PUBLIC S16 ssMsgAppendU32
(
PMSGHEADER msg, 
U16 paramID, 
U32 paramData
)
#endif
{
    PPARAMHEADER ptr = (PPARAMHEADER) &msg->param[RoundUp32(msg->length) / sizeof(U32)];

    ptr->paramID = paramID;
    ptr->length = sizeof(U32);
    ptr->data[0] = paramData;

    msg->length = RoundUp32(msg->length) + sizeof(PARAMHEADER);

    return SUCCESS;
}



#ifdef ANSI
PUBLIC PPARAMHEADER ssGetNextParam
(
PMSGHEADER   msg, 
PPARAMHEADER pParam
)
#else
PUBLIC S16 ssGetNextParam
(
PMSGHEADER   msg, 
PPARAMHEADER pParam
)
#endif
{
   PPARAMHEADER *tmp;
   /*printHex1("toplevel Msgheader\n", msg);*/
   
   if (pParam == NULLP)
   {
#if 0
      tmp = (PPARAMHEADER)((U8*)msg + sizeof(MSGHEADER) );
#else
      tmp = (PPARAMHEADER) &(msg->param[0]);
#endif
   }
   else
   {
      tmp = (PPARAMHEADER)ssGetVirPtr((PTR)((((U8*)pParam) + sizeof (PARAMHEADER) +
                        ROUND(pParam->length, 4))));
   }
   if (tmp!=NULLP)
   RETVALUE (tmp);
} /* ssGetNextParam */


#ifdef ANSI
PUBLIC S16 ssGetPParamById
(
PMSGHEADER   msg, 
U16          paramID, 
PPARAMHEADER *pParam
)
#else
PUBLIC S16 ssGetPParamById
(
PMSGHEADER   msg, 
U16          paramID, 
PPARAMHEADER *pParam
)
#endif
{
    *(pParam) = NULLP;

    while ((*(pParam) = ssGetNextParam(msg, *(pParam))) != NULLP)
    {
       if ((*(pParam))->paramID == paramID)
       {
          RETVALUE (ROK);
       }
    }

    *pParam = NULLP;
    RETVALUE (RFAILED);
}




S16 sStartMLog
(
)
{
#if 1
#if 0
   MLogOpen(0x0, 0);
#else
   MLogOpen(0x15100000, 0xb4c0);
#endif
   MLogDevInfo(4007);
   MLogFREQ(RESOURCE_LINUX0, 600*1000*1000); 
   MLogSetResetCounter(1000);
   MLogSetMask(1<<RESOURCE_LINUX0);

   /*
   MLogOpen(0, 0);
   MLogDevInfo(4007);
   MLogFREQ(RESOURCE_LINUX0, 600*1000*1000); 
   MLogSetResetCounter(200);
   mlog_ctx.EnabledMask = 1<<RESOURCE_LINUX0;
   mlog_ctx.Started = MLOG_TRUE; */
#endif
}

S16 sStopMLog
(
)
{
    char            *fileName;
    char            *id_str;
    unsigned int    count;
    U32             *virtAddr;
    FILE            *file;
    U32             id=0;

#if 0
    virtAddr = mlog_ctx.Mlogbuffer[id]->pDataHead;
    count    = mlog_ctx.Mlogbuffer[id]->Size;

    file = fopen("mlog_uarm_stack.bin", "wb");
    if (file == NULL)
    {
        DiagPrint(DIAG_LEVELALL, "ERROR", "Unable to create file [%s]\n", fileName);
        return FAILURE;
    }

    printf("prepare operation is ok for getmlog\n");

    if (virtAddr == NULL)
    {
        DiagPrint(DIAG_LEVELALL, "ERROR", "Unable to map address [%p:%u]\n", (PTR) virtAddr, count);
        fclose(file);
        return FAILURE;
    }
    fwrite(virtAddr, count, 1, file);
    fclose(file);
#endif

    return SUCCESS;
}


/*
*
*       Fun:   ssPstLarmMsg
*
*       Desc:  This primitive is used by CL to send message to PHY
*
*       Ret:
*
*       Notes: None
*
*       File:  ys_ms_li.c`
*
*/
#ifdef ANSI
PUBLIC S16 ssPstLarmMsg
(
U32          size,
PMSGHEADER   pMsg
)
#else
PUBLIC S16 ssPstLarmMsg(size, pHdr)
U32          size;
PMSGHEADER   pMsg;
#endif
{
   PMSGHEADER pHdr = (PMSGHEADER) MsgAllocBuffer(MSG_FAST);

   size +=sizeof(PMAC2PHY_QUEUE_EL);

   pHdr->control = CTRL_BYPASS | CTRL_VERSION;
   pHdr->length = size;
   pHdr->type = MSGT_DATA;
   pHdr->srcID = MSGS_MAC;
#if 0
   pHdr->dstID = MSGS_LARM | PhyInstanceID;
#else
   pHdr->dstID = IID_CORE | CORE_1_ID;
   pHdr->dstID = 38 | MSGS_LARM;
#endif
   pHdr->msgID = PHY_LTE_MSG_LIST;

   
#if 0
   memcpy(&pHdr->param[0], pMsg, size);
#else
   pHdr->length = 0;
   /*printf("Larm pElm %x %x\n", pMsg, IcpuGetPhys(pMsg)); */
   ssMsgAppendU32(pHdr, PHY_QUE_HDR_PARAM_ID, (U32)(IcpuGetPhys((PTR)pMsg)));
   /* printf("pHdr Parm %x %x\n", pHdr, IcpuGetPhys(pHdr)); */
#if 0
   memcpy(&(PPARAMHEADER)(pHdr->param[0]).data, pMsg, size);
#endif
#endif

   /* Free the contents redundant buffer */
#if 0
   MsgFreeBuffer(pMsg);
#endif
   /*printfHex("BeforeDispatch", pHdr); */

   return MsgDispatch(MSGS_MAC, sizeof(MSGHEADER) + size, pHdr);
}




/*
 *
 *     Fun  : uarmDrvrInit
 *
 *     Desc : Initializes uppercore driver task to facilitate communication with
 *            lower arm.
 *
 *     Ret:   ROK      - ok
 *            RFAILED  - failed, general (optional)
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
#ifdef ANSI
PUBLIC S16 uarmDrvrInit
(
 Void
)
#else
PUBLIC S16 uarmDrvrInit()
#endif
{
   S16 ret;

   TRC0(uarmDrvrInit);

   /* Channel initialized to handle messages targetted towards
    * 4GMX channels, and Vice versa.
    */
   ret = SRegDrvrTsk(SVSR_CHANNEL, IARM_PROCESSOR_ID_LOW, IARM_PROCESSOR_ID_HIGH, uarmPstTsk, uarmIsTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SRegDrvrTsk failed");
#endif
      RETVALUE(RFAILED);
   }

   /*SSetIntPend(SVSR_CHANNEL, TRUE);*/

   RETVALUE(ROK);
}


/*
 *
 *     Fun  : uarmInit
 *
 *     Desc : Initializes uppercore dependencies to facilitate communication with
 *     lower arm.
 *
 *     Ret:   ROK      - ok
 *            RFAILED  - failed, general (optional)
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
#ifdef ANSI
PUBLIC S16 uarmInit
(
 Void
)
#else
PUBLIC S16 uarmInit()
#endif
{
   S16 ret;

   TRC0(uarmInit);

   /* IcpuMode = IMODE_DIRECT;*/

   /*MindSpeed specific initializations*/
#if 0
   if(BspInit(UARM)!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SBspInit failed");
#endif
      RETVALUE(RFAILED);
   }
#endif

   if(OsalInit(UARM)!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SOsalInit failed");
#endif
      RETVALUE(RFAILED);
   }

   /* The argument (argc=) 1 bypasses the commandline parsing during
    * the Linux Bsp initialization
    */
   if(InitSettings(1, NULL)!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "InitSettings failed");
#endif
      RETVALUE(RFAILED);
   }

   if(AuxInit()!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "AuxInit failed");
#endif
      RETVALUE(RFAILED);
   }

   if(SvsrInit()!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SvsrInit failed");
#endif
      RETVALUE(RFAILED);
   }

   if(MsgDispatcherInit()!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "MsgDispatcherInit failed");
#endif
      RETVALUE(RFAILED);
   }

   if(IcpuInit(UARM)!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "IcpuInit failed");
#endif
      RETVALUE(RFAILED);
   }

#ifdef TENB_RTLIN_CHANGES
   DiagInit();
#endif /*TENB_RTLIN_CHANGES*/

    if(TimerInit(UARM)!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "IcpuInit failed");
#endif
      RETVALUE(RFAILED);
   }

   printf("MSPD Uarm Initializing completed\n");
   /*ProtoInit(PROTO_TCP);*/

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
PUBLIC S16 uarmIsTsk
(
Inst inst
)
#else
PUBLIC S16 uarmIsTsk(inst)
Inst inst;
#endif
{

   TRC0(uarmIsTsk);

   printf("%s:%d\n",__func__,__LINE__);

   RETVALUE(ROK);
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
 *       File:  mt_4gmx.c
 *
 */
#ifdef ANSI
PUBLIC S16 uarmPstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
)
#else
PUBLIC S16 uarmPstTsk(pst, mBuf)
Pst *pst;                       /* post information */
Buffer *mBuf;                   /* message to post */
#endif
{
   U32            uInstId;
   Data           *pMsg;
   RESULTCODE     ret;
   PMSGHEADER     pHdr;
   MsgLen         bufLen    = 0;
   MsgLen         msgLen    = 0;
   Inst           inst;
   S16            dstInstId = 0;

   TRC0(uarmPstTsk);

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
   if (inst != SVSR_CHANNEL)
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
            "Message size is > MAX_ICPU_BUF_SIZE");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pHdr = MsgAllocBuffer(MSG_FAST);

   if(NULLP == pHdr)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "MsgAllocBuffer failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pMsg = (Data*) MsgGetDataOffset((PTR)pHdr);

   MsgInitMessage(pHdr);

   ret = SCpyMsgFix(mBuf, 0, bufLen, (Data*)pMsg, &msgLen);
   if((ret != ROK) || (bufLen != msgLen))
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SAddPstMsgMult failed");
#endif
      MsgFreeBuffer(pHdr);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /*Done with buffer, free it*/
   SPutMsg(mBuf);

   pHdr->control = CTRL_BYPASS | CTRL_VERSION;
   pHdr->length = bufLen;
   pHdr->type = MSGT_DATA;
   pHdr->srcID = MSGS_MAC;
   pHdr->msgID = PHY_LTE_MSG;
   dstInstId = uarmGetDstInstId(pst->dstEnt,pst->dstInst);
   if(dstInstId < 0)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "TAPA task not running on larm");
#endif
      MsgFreeBuffer(pHdr);
      RETVALUE(RFAILED);
   }
   pHdr->dstID = (dstInstId | MSGS_LARM);

   /* Send msg from mac to L-arm */
   ret = MsgDispatch(dstInstId, (U32)pHdr->length + sizeof(MSGHEADER), (Ptr)pHdr);
   if(ret != SUCCESS)
   {
      static unsigned int c;
      if (c++ % 64 == 0)
         printf("[1/64] dropped data for LARM, %u times\n", c);
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "MsgDispatch failed");
#endif

      MsgFreeBuffer(pHdr);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

PUBLIC PPARAMHEADER ssMsgGetDataOffset
(
PTR ptr
)
{
    return (MsgGetDataOffset(ptr));
}


/*
 *
 *       Fun:   MacDispatch
 *
 *       Desc:  This primitive is a callback from Syscore of Mindspeed from
 *              Lower arm to upper arm
 *
 *       Ret:   ROK      - ok
 *              RFAILED  - failed, general (optional)
 *
 *
 *       Notes: None
 *
 *       File:  mt_4gmx.c
 *
 */
#ifdef ANSI
PUBLIC RESULTCODE MacDispatch
(
U32   size,
PTR   l1Msg
)
#else
PUBLIC RESULTCODE MacDispatch(size, l1Msg)
U32   size;
PTR   l1Msg;
#endif
{
   S16           ret;
   Buffer        *mBuf;
   Data          *pData;
   PMSGHEADER    pHdr;
   Pst            nPst;

   TRC0(MacDispatch);

   ret = SGetMsg(CL_REGION, 1, &mBuf);
   if(ROK != ret)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, (ErrVal) ret,
            "Could not create msg for passing to main thread");
#endif
      MsgFreeBuffer(pHdr);
      RETVALUE(FAILURE);
   }

   pHdr = (PMSGHEADER) l1Msg;

   /* Check for the destination of the message */
   if(((pHdr->dstID & MSGS_ROUTE) != MSGS_UARM)
         || (pHdr->dstID != MSGS_MAC))
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Msg is not destined to CL");
#endif
      MsgFreeBuffer(pHdr);
      SPutMsg(mBuf);
      RETVALUE(FAILURE);
   }

   pData = (Data *) &pHdr->param[0];

   if(pHdr->length > MAX_ICPU_BUF_SIZE)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "Message length is greater than MAX_BUF_SIZE");
#endif
      MsgFreeBuffer(pHdr);
      SPutMsg(mBuf);
      RETVALUE(FAILURE);
   }

   switch(pHdr->type)
   {
      case MSGT_DATA:      /* Data message */
         {
            ret = SAddPstMsgMult((Data*)pData, pHdr->length, mBuf);
            if(ret != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
                     "SAddPstMsgMult failed");
#endif
               SPutMsg(mBuf);
               break;
            }
            CMCHKUNPK(cmUnpkPst, &nPst, mBuf);
            ret = SPstTsk(&nPst,mBuf);
            if(ROK != ret)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS527, (ErrVal) ret,
                     "Could not post to TAPA task");
#endif
               SPutMsg(mBuf);
            }
            break;
         }
      case MSGT_RESPONSE:
         break;
      default:
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
                  "Received unknown header message from lower arm");
#endif
            break;
         }
   }

   MsgFreeBuffer(pHdr);
   RETVALUE(SUCCESS);
} /* end of MacDispatch */


/*
 *
 *     Fun  : MacSetInitConfig
 *
 *     Desc : MAC layer initialization callback from SysCore
 *
 *     Ret:  SUCCESS
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
RESULTCODE MacSetInitConfig(HANDLE h)
{
   return SUCCESS;
}


/*
 *
 *     Fun  : MacInit
 *
 *     Desc : MAC layer initialization callback from SysCore
 *
 *
 *     Ret:  SUCCESS
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
#if 0
RESULTCODE MacInit(PhyTxCb txCb, PhyRxCb rxCb, HANDLE toPhy, HANDLE fromPhy)
{
    return SUCCESS;
}
#endif


/*
 *
 *     Fun  : MacDone
 *
 *     Desc : MAC layer callback from SysCore
 *
 *
 *     Ret:  SUCCESS
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
RESULTCODE MacDone(void)
{
    return SUCCESS;
}


/*
 *
 *     Fun  : MacRxEthPacket
 *
 *     Desc : MAC layer callback from SysCore
 *
 *     Ret:  SUCCESS
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
RESULTCODE MacRxEthPacket(PTR pPacket, U32 Len)
{
    return SUCCESS;
}


/*
 *
 *     Fun  : sctp_send
 *
 *     Desc :
 *
 *     Ret: SUCCESS
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
int sctp_send(int s, const void *msg, size_t len,
          const struct sctp_sndrcvinfo *sinfo, int flags)
{
   return 1;
}


/*
 *
 *     Fun  : sctp_recvmsg
 *
 *     Desc :
 *
 *     Ret: SUCCESS
 *
 *     Notes: None
 *
 *     File : mt_4gmx.c
 *
 */
int sctp_recvmsg(int s, void *msg, size_t len, struct sockaddr *from,
                 socklen_t *fromlen, struct sctp_sndrcvinfo *sinfo,
                 int *msg_flags)
{
   return 1;
}

#endif /* SS_4GMX_UCORE */

#include "envopt.h"        /* environment options */
#ifdef TENB_RTLIN_CHANGES

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
#include <execinfo.h>



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
#include "ss_err.h"        /* error */
#include "cm_mem.h"        /* common memory manager */
#ifdef SS_THREAD_PROFILE 
#include "ss_err.h"
#endif

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timers */

#include "mt_ss.x"         /* MTSS specific */
#ifdef SS_LOCKLESS_MEMORY
#include "mt_ss_wl.x"         /* MTSS specific */
#endif /* SS_LOCKLESS_MEMORY */

#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "cm_lib.x"
#include "cm_llist.x"
#include "cm_hash.x"
#include "cm_mem_wl.x"
#include "mt_4gmx.x"


PRIVATE Void ssMemlogWriteToFile(char  *filename );

PUBLIC Void ssMlogInit()
{
#ifndef MSPD_PHY_NEW
   tlMlogInit(0,
         SS_MLOG_BUF_SIZE,
         4007,
         RESOURCE_L2,
         600,
         500,
         0xffffffff, 
         "l2mlog");
#elif CA_PHY
   tlMlogInit(0,
         SS_MLOG_BUF_SIZE,
         4007,
         RESOURCE_L2,
         0xffffffff,
         "l2mlog");
#else
   tlMlogInit(0,
         SS_MLOG_BUF_SIZE,
         4007,
         RESOURCE_L2,
         600,
         500,
         0xffffffff,
         "l2mlog");
#endif
}

PUBLIC Void ssMlogIncrCounter()
{
#ifdef CA_PHY
#ifndef LTE_TDD
   tlMlogIncrementTti(0);
#else
   tlMlogIncrementCounter();
#endif
#else   
   tlMlogIncrementCounter();
#endif
}

PUBLIC Void ssMlogPrint()
{
#ifdef MSPD_MLOG_NEW
#ifdef CA_PHY
   tlMlogPrint(); 
#elif MSPD_PHY_NEW
   tlMLogPrint(1); 
#else
   tlMLogPrint(); 
#endif
#endif
}

extern void DumpLayersDebugInformation(void);

PUBLIC Void mtStopHndlr()
{
   extern U32 ysGT;
   U32  avail;
   U8   regIdx = 0;
   static U16 invoked;
   if (invoked)
      return;
#if 1
   for(regIdx = 0; regIdx < SS_MAX_REGS; regIdx++)
      SRegInfoShow(regIdx, &avail);

#endif
   DumpLayersDebugInformation();
#ifdef T2K_MEM_LEAK_DBG
   DumpT2kMemLeakInfoToFile();
#endif
#ifdef SSI_STATIC_MEM_LEAK_DETECTION
   DumpStaticMemLeakFiles();
#endif
   printf("@%lu Stopping, writing out mspd mlog and ccpu.log\n", ysGT);
#if 0
   mtSigSegvHndlr();
   mtSigUsr2Hndlr();
#endif
   ssMlogPrint();
   ssMemlogWrite();
   
   /*ysMsSndPhyShutDown();*/
   invoked = 1;
}

PUBLIC Void ysPrntBkTrace(Void)
{

   void *trace[50];
   int tsize, cnt;
   char **buffer;
   tsize = backtrace(trace, 50);
   buffer = backtrace_symbols(trace, tsize);
   if (buffer == NULL)
   {
      perror("backtrace_symbols");
      return;
   }
   for (cnt= 0; cnt< tsize; cnt++)
      printf("%s\n", buffer[cnt]);
   free(buffer);
}
 

/************************************************************************
 * MEMORY LOG FUNCTIONALITY, MOSTLY BORROWED FROM MT4GMX (rb_log.[cxh]) *
 ************************************************************************/


PUBLIC Void ssMemlogInit()
{
   SsMemlogCb   *mLogCb;
   S16           ret;

   mLogCb         = &ssMemlogCb;

   cmMemset((U8*)mLogCb->buf, ' ', sizeof(mLogCb->buf));
   ret = SInitLock(&mLogCb->lock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      printf("memlog init failed\n");
      return;
   }

   printf("\nRsys memlog initialized\n");
   return;
}


#ifdef ANSI
PUBLIC Void ssMemlog
(
char  *src,
U32   size
)
#else
PUBLIC Void ssMemlog(src, size)
char  *src;
U32   size;
#endif
{
   SsMemlogCb   *mLogCb;
   S8  *endmarker = "<END>\n";
   U32  endlen = 6;
   U32  actualsize = size;
   U32  wPtr;

   mLogCb = &ssMemlogCb;
   size += endlen;

   if (size > SS_MEMLOG_MAXSTRLEN-7)
   {
      printf("Printing too many bytes %lu\n", size);
      return;
   }
   SLock(&mLogCb->lock);
   wPtr = mLogCb->wPtr;
   if (wPtr + size > SS_MEMLOG_SIZE)
   {
      cmMemset((U8*)(mLogCb->buf + wPtr), ' ',
            SS_MEMLOG_SIZE - wPtr);
	   wPtr = 0;
   }

   SMemCpy((Void *)(&mLogCb->buf[wPtr]), (Void *)src, (size_t)actualsize);
   SMemCpy((Void *)(&mLogCb->buf[wPtr+=actualsize]), (Void *)endmarker,
   	   (size_t)endlen);

   mLogCb->wPtr = wPtr;

   SUnlock(&mLogCb->lock);
   return;
}

#ifdef ANSI
PRIVATE Void ssMemlogWriteToFile
(
char  *filename
)
#else
PRIVATE Void ssMemlogWriteToFile(filename)
char  *filename;
#endif
{
   const SsMemlogCb   *mLogCb = &ssMemlogCb;
   const char *firstline = "\nMEMLOG\n";
   FILE  *fp;
   if ((fp = fopen(filename, "w")) == NULLP)
   {
      printf("error: could not open '%s' for writing\n", filename);
      return;
   }
   fwrite(firstline, strlen(firstline), 1, fp);
   fwrite(mLogCb->buf, SS_MEMLOG_SIZE, 1, fp);
   fclose(fp);
   return;
}

#ifdef ANSI
PUBLIC Void ssMemlogWrite
(
)
#else
PUBLIC Void ssMemlogWrite()
#endif
{
   ssMemlogWriteToFile(SS_MEMLOG_OUTFILE);
}

#endif


/********************************************************************30**

         End of file:     mt_4gmx.c@@/main/TeNB_Main_BR/8 - Thu Apr 24 17:09:29 2014

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

