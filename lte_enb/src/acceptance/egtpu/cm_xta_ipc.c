
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_ipc.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:18 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */
#include "cm_inet.h"        /* common inet */

#include "cm_xta.h"
/* cm_xta_ipc_c_001.main_5 Removed cm_xta_app.h for Psf-Diameter 1.1 */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */
#include "cm_inet.x"        /* common inet */

#include "cm_xta.x"
/* cm_xta_ipc_c_001.main_5 Removed cm_xta_app.x for Psf-Diameter 1.1 */
CmInetFd sockFd;                   /* socketdescriptor for UDP Socket relay*/
CmInetFdSet          readFdSet;

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcInit(Void)
#endif
{

   TRC2(cmXtaAppIpcInit)
   /*-- Part of support for multiple slaves. In order to talk to 
        multiple slaves we need to have relay configured for each of the 
        nodes. The following code if the relay flag is enabled will use the 
        common relay product else it will used the minmial relay that we have as 
        part of CM_XTA. --*/




    /*-- Support for Relay in the FTHA Integration*/
#ifdef CM_XTA_RELAY
   RETVALUE(cmXtaRelayInit());
#else
   RETVALUE(cmXtaAppIpcUdpInit());
#endif

}/* cmXtaAppIpcInit()*/

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcDeInit(Void)
#endif
{
   TRC2(cmXtaAppIpcDeInit)

/* cm_xta_ipc_c_001.main_3: relay shutdown request is sent */
#ifdef CM_XTA_RELAY
  /* cm_xta_ipc_c_001.main_4: Removed the unused parameter passed to function.
   * The number of channels is not required to send control request */
  cmXtaRlyShutDownReq(cmXtaProc[cmXtaCb.curNode].lowProcId, cmXtaProc[cmXtaCb.curNode].lowProcId);
#else
   cmXtaAppIpcUdpDeInit();
#endif

   RETVALUE(ROK);
}/* cmXtaAppIpcDeInit()*/

/*-- Support for Relay in the FTHA Integration*/

#ifdef CM_XTA_RELAY
/*
*
*       Fun: cmXtaRelayInit
*
*       Desc: This function configures the common relay 
*              product in accordance to the current topology.
*              
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes: Steps 
*           1. Perform general configuration
*           2. For each node configure one channel, based on 
*              information present in xxac_proc.c file. 
*
*       File: cm_xta_ipc.c 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaRelayInit
(
Void
)
#else
PUBLIC S16 cmXtaRelayInit()
#endif
{
   S16      ret;
   U8       i;  
   U8       indx;  


   /*-- Perform General config for relay 
     this requires the number of channels 
     to be configured i.e. one minus the 
     total number of nodes in the system --*/
   cmXtaRlyGenCfgReq(cmXtaProc[cmXtaCb.curNode].lowProcId, cmXtaProc[cmXtaCb.curNode].lowProcId, (CMXTA_NODES));

    /*Initialize the CmXtaProcs Array here for taking Port and IpAddress from the
    * command Line options*/
    for (i = 0; i < CMXTA_NODES; i++)
    {
       cmXtaProc[i].port = cmXtaCb.portBase+cmXtaProc[i].port; 
       /* Add the Logic of the IpAddrss through the command Line*/
    } /*-- End of For for Nodes --*/

   RETVALUE(ROK);

} /* cmXtaRelayInit */
/* cm_xta_ipc_c_001.main_3: Relay GenCfgCfm is handeled. */
/*
*
*       Fun: rycmXtaGenCfgCfm
*
*       Desc: This function configures the common relay 
*              Channel Configuration.
*              
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes: Steps 
*           1. For each node configure one channel, based on 
*              information present in xxac_proc.c file. 
*
*       File: cm_xta_ipc.c 
*
*/
#ifdef ANSI
PUBLIC S16 rycmXtaGenCfgCfm
(
Pst *pst,                       /* post */
RyMngmt *cfg      
)
#else
PUBLIC S16 rycmXtaGenCfgCfm(pst, cfg)
Pst *pst;                       /* post */
RyMngmt *cfg;
#endif
{
   U8       i;  
   U8       indx;
#ifdef CMXTA_FTHA_INTEGRATED
   Pst      lcl_pst;
   Buffer *mBuf;
#endif

   switch(cfg->hdr.elmId.elmnt)
   {
      case STGEN:

         /*-- Logic: We loop through all the nodes
           For all node except this one we need to configure 
           one channel --*/
         /*-- If we are the master then we need to configure 
           an extra listen channel --*/
         cmXtaRlyChannelCfgReq(0, 
               0,  /*-- Destination low procId --*/
               0,   /*-- Destination higher procId --*/
               0,                       /*-- Destination port --*/
               cmXtaProc[cmXtaCb.curNode].ipAddr,     /*-- Destination IP address --*/
               cmXtaProc[cmXtaCb.curNode].port,     /*-- Local Port --*/
               cmXtaProc[cmXtaCb.curNode].lowProcId
               );

         indx = 1;
         for (i = 0; i < CMXTA_NODES; i++)
         {
            if (i == cmXtaCb.curNode)
               continue;
            /*-- Perform channel configuration for 
              every other node i.e. from this node to every other 
              node in the system. --*/
            cmXtaRlyChannelCfgReq(indx, 
                  cmXtaProc[i].lowProcId,  /*-- Destination low procId --*/
                  cmXtaProc[i].hiProcId,   /*-- Destination higher procId --*/
                  cmXtaProc[i].port,       /*-- Destination port --*/
                  cmXtaProc[i].ipAddr,     /*-- Destination IP address --*/
                  0, /*-- Local Port --*/
                  cmXtaProc[cmXtaCb.curNode].lowProcId
                  );
            indx++;
         } /*-- End of For for Nodes --*/
   }
  if ((cmXtaCb.masterMode == CMXTA_TA_INST_MASTER)  ||
          (cmXtaCb.masterMode == CMXTA_TA_INST_NONE))
  {
/*-- Need to send a message to self --*/
   /* Moved the cmXtaGetPst out of the Multiple Proc flag*/
      cmXtaGetPst(&lcl_pst, ENTFM, CMXTA_INST_ID, ENTFM, CMXTA_INST_ID, 
            cmXtaProc[0].lowProcId, cmXtaProc[cmXtaCb.curNode].lowProcId, TRUE);

      CMXTA_ALLOCMBUF(&mBuf);

      lcl_pst.event = EVTSTFMSERVERINIT;
   /*-- Post the message to client --*/
      SPstTsk(&lcl_pst, mBuf);
  }
   RETVALUE(ROK);
}

#endif /*-- End of CM_XTA_RELAY --*/
 
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcUdpInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcUdpInit()
#endif
{
   S16 ret;
   CmInetAddr     localRelay;    /* local relay addr/port */
   U16             localPort;

   TRC2(cmXtaAppIpcUdpInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppIpcUdpInit(): Initializing UDP IPC\n"));

   /*-- Initialize cminet library --*/
   cmInetInit();

#ifdef IPV6_SUPPORTED
   localRelay.type = CM_INET_IPV4ADDR_TYPE;
#endif

   if (cmXtaCb.masterMode == CMXTA_TA_INST_MASTER)
      localPort    = cmXtaCb.ipcPort;
   else
      localPort    = cmXtaCb.ipcPort + 1;

   /*
    * Need this conversion as cmInetAddr returns in host format
    * and cmInetConnect requires in Network format
    */
   cmXtaCb.localIpcIpAddr = CM_INET_HTON_U32(cmXtaCb.localIpcIpAddr);

   /*
    * Need this conversion as cmInetAddr returns in host format
    * and cmInetConnect requires in Network format
    */
   cmXtaCb.remoteIpcIpAddr = CM_INET_HTON_U32(cmXtaCb.remoteIpcIpAddr);

   /* create and bind the socket */
#ifdef IPV6_SUPPORTED  
   ret = cmInetSocket(CM_INET_DGRAM, &sockFd, 0, CM_INET_IPV4_DOMAIN);
#else
   ret = cmInetSocket(CM_INET_DGRAM, &sockFd, 0);
#endif

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaAppIpcUdpInit() : listening server create socket failure\n"));
      RETVALUE(RFAILED);
   }

   /* bind socket to local ephemeral port */
#ifdef IPV6_SUPPORTED
   localRelay.u.ipv4Addr.address = cmXtaCb.localIpcIpAddr;
   localRelay.u.ipv4Addr.port    = localPort;
#else
   localRelay.address = cmXtaCb.localIpcIpAddr;
   localRelay.port    = localPort;
#endif
   ret = cmInetBind(&sockFd, &localRelay);  

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaAppIpcUdpInit() : listening server bind failure\n"));
      RETVALUE(RFAILED);
   }

   /* set the server fd in the read fd set --*/
   CM_INET_FD_SET(&sockFd, &readFdSet);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppIpcUdpInit() : Server Opened successfully at port (%u)\n",
                localPort));

   if (cmXtaCb.masterMode == CMXTA_TA_INST_MASTER)
      ret = SRegDrvrTsk((Inst)1, CMXTA_PROCID_SLAVE1 - 1, CMXTA_PROCID_SLAVEMAX,
                         cmXtaAppIpcUdpPstTsk, (ISTsk) cmXtaAppIpcUdpGetTsk);
   else
      ret = SRegDrvrTsk((Inst)1, CMXTA_PROCID_MASTER, CMXTA_PROCID_MASTER,
                         cmXtaAppIpcUdpPstTsk, (ISTsk) cmXtaAppIpcUdpGetTsk);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   SSetIntPend((U16)1, TRUE);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppIpcUdpInit(): UDP IPC Init Done\n"));

   RETVALUE(ROK);
} /* end of cmXtaAppIpcUdpInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcUdpPstTsk
(
Pst *pst,                       /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmXtaAppIpcUdpPstTsk(pst, mBuf)
Pst *pst;                       /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   S16 retVal;
   MsgLen msgLen; /* stores the length of the message posted */
   CmInetMemInfo  info;         /* memory pool/region info*/
   CmInetAddr remoteRelay;      /* remote relay addr/port */
   U16 remotePort;

   TRC2(cmXtaAppIpcUdpPstTsk)

   if (cmXtaCb.masterMode == CMXTA_TA_INST_MASTER)
      remotePort    = cmXtaCb.ipcPort + 1;
   else
      remotePort    = cmXtaCb.ipcPort;

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppIpcUdpPstTsk() : Sent: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
                  pst->srcProcId, pst->srcEnt, pst->srcInst, 
                  pst->dstProcId, pst->dstEnt, pst->dstInst, 
                  pst->event));

   /* pack the post struct */ 
   CMCHKPK(cmPkPst, pst, mBuf);

#ifdef IPV6_SUPPORTED
   remoteRelay.type = CM_INET_IPV4ADDR_TYPE;
#endif

   /* sent cached message */
   info.region = cmXtaCb.init.region;
   info.pool   = cmXtaCb.init.pool;

#ifdef IPV6_SUPPORTED
   remoteRelay.u.ipv4Addr.address = cmXtaCb.remoteIpcIpAddr;
   remoteRelay.u.ipv4Addr.port    = remotePort;
#else
#ifdef TRY
   remoteRelay.address = cmXtaCb.remoteIpcIpAddr;
   remoteRelay.port    = remotePort;
#else
   remoteRelay.address = cmXtaCb.remoteIpcIpAddr;
   remoteRelay.port    = remotePort;
#endif
#endif
#ifdef IPV6_OPTS_SUPPORTED
   retVal = cmInetSendMsg(&sockFd,&remoteRelay, &info, mBuf, &msgLen, 
                             NULLP, CM_INET_NO_FLAG);
#else
   retVal = cmInetSendMsg(&sockFd,&remoteRelay, &info, mBuf, &msgLen, 
                             CM_INET_NO_FLAG);
#endif

   retVal = SPutMsg(mBuf);

   if (retVal != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaAppIpcUdpPstTsk() : msg send failed\n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of cmXtaAppIpcUdpPstTsk*/

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppIpcUdpIsTsk
(
UProc *uProc
)
#else
PUBLIC Void cmXtaAppIpcUdpIsTsk(uProc)
UProc *uProc;
#endif
{
   TRC2(cmXtaAppIpcUdpIsTsk)

   (Void)cmXtaAppIpcUdpGetTsk(uProc);

   RETVOID;
} /* end of cmXtaAppIpcUdpIsTsk*/

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcUdpGetTsk
(
UProc *uProc
)
#else
PUBLIC S16 cmXtaAppIpcUdpGetTsk(uProc)
UProc *uProc;
#endif
{
   S16 retVal;
   CmInetAddr remAddr;
   CmInetMemInfo info;          /* buffer allocation info */
   Buffer *mBuf;
   MsgLen msgLen;               /* length to read */
   Pst remPst;
   Pst *remPstPtr;
   Inst inst;
   S16  setFds;

   TRC2(cmXtaAppIpcUdpGetTsk)

   info.pool = DFLT_POOL;
   info.region = DFLT_REGION;

   setFds = 0;
   /* call select() correctly, depending on mode --*/
   retVal = cmInetSelect(&readFdSet, NULLP, NULLP, &setFds);

   /* if any fds are set, process them --*/
   if (setFds == 0)
   {
      RETVALUE(RFAILED);
   }

   msgLen=CM_INET_READ_ANY;
#ifdef IPV6_OPTS_SUPPORTED
   retVal = cmInetRecvMsg(&sockFd, &remAddr, &info, &mBuf,
                   &msgLen, NULLP, CM_INET_NO_FLAG);
#else
   retVal = cmInetRecvMsg(&sockFd, &remAddr, &info, &mBuf,
                   &msgLen, CM_INET_NO_FLAG);
#endif

   if (retVal != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaAppIpcUdpGetTsk() : msg rcv failed\n"));
      RETVALUE(RFAILED);
   }

   CMXTA_ZERO(&remPst, sizeof(Pst));
   remPstPtr = &remPst;
   CMCHKUNPK(cmUnpkPst, remPstPtr, mBuf);

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaAppIpcUdpGetTsk() : Received: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
                     remPstPtr->srcProcId, remPstPtr->srcEnt, remPstPtr->srcInst, 
                     remPstPtr->dstProcId, remPstPtr->dstEnt, remPstPtr->dstInst, 
                     remPstPtr->event));
   CMCHKUNPK(cmUnpkInst, &inst, mBuf);

   RETVALUE(SPstTsk(&remPst,mBuf));
} /* end of cmXtaAppIpcUdpGetTsk*/

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppIpcUdpDeInit
(
Void
)
#else
PUBLIC Void cmXtaAppIpcUdpDeInit()
#endif
{
   TRC2(cmXtaAppIpcUdpDeInit);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppIpcUdpDeInit(): Shutting down the UDP IPC\n"));

   /*-- clear interrupt pending flag --*/
   SSetIntPend((U16)1, FALSE);

   /* close the socket */
   (Void) cmInetClose(&sockFd);

   CM_INET_SET_INV_SOCK_FD(&sockFd);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppIpcUdpDeInit(): UDP IPC Shutdown Done\n"));

   RETVOID;
} /* cmXtaAppIpcUdpDeInit */

/********************************************************************30**

         End of file:     cm_xta_ipc.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:18 2015

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
/main/1      ----     up  1. Main release
/main/2      ---      sk   1. Updated for PSF-SIP 1.1 Release
/main/3      ---      aj   1. Updated for Relay in FTHA Integration   
/main/4      ---  cm_xta_ipc_c_001.main_3   ve  1. Relay GenCfgCfm is handeled.
                                               2. relay shutdown request is sent.
/main/5      ---      cm_xta_ipc_c_001.main_4  pka   1. Removed the unused parameter from
                                             shutdown request.
/main/6      ---      cm_xta_ipc_c_001.main_5   nh 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
