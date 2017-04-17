/********************************************************************20**

     Name:

     Type:     C File.

     Desc:     Supervisor module is used to communicate with lower arm
               using shared memory

     File:     mt_4gmx.c

     Sid:      mt_4gmx.c@@/main/1 - Mon Aug 29 22:31:38 2011

     Prg:

************************************************************************/

#include "mt_4gmx.h"
#include "mt_4gmx.x"
#include "rb_common.h"

#ifdef SS_4GMX_UCORE


/*Initialize inter cpu configuration*/
SsRegIcpuCfg icpuCfg[SS_MAX_TTSKS] = ICPUINIT; /*Initializes inter cpu configuration*/


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
   if(BspInit(UARM)!=SUCCESS)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
            "SBspInit failed");
#endif
      RETVALUE(RFAILED);
   }

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
   /* Check whether it is the Data packets from Application to PDCP
    *  or Signalling packets from RRC
    */
   if((pst->srcEnt == ENTPX) && (pst->dstEnt == ENTPJ))
   {
      extern U32 totalIcpuPkts;
      totalIcpuPkts++;  
	  
      /*This function is used to check the status of the Tx queue 
       *and drop the data packets if the the free blocks are less than the threshold.
       */
      if(IcpuGetTxPFreeBlckNumAbs() <= 20)
      {
         extern U32 droppedIcpuPkts;
         droppedIcpuPkts++;
         SPutMsg(mBuf);
         RETVALUE(ROK);
      }
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

   /* moved this statement to above to prevent invalid MsgFreeBuffer */ 
   pHdr = (PMSGHEADER) l1Msg;

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
              /* SPstTsk frees mbuf in case of failure */
              /* SPutMsg(mBuf); */
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
RESULTCODE MacInit(PhyTxCb txCb, PhyRxCb rxCb, HANDLE toPhy, HANDLE fromPhy)
{
    return SUCCESS;
}


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

#endif


/********************************************************************30**

         End of file:     mt_4gmx.c@@/main/1 - Mon Aug 29 22:31:38 2011

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
