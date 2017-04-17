
/********************************************************************20**
 
     Name:     TIP PHY Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for control plane primitives on TIP PHY Open Interface.

     File:     tip_ctf.c

     Sid:      tip_ctf.c@@

     Prg:      Radisys
     
*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="TIP";
static int RLOG_MODULE_ID=847;
static int RLOG_FILE_ID=1;

#include "tip_cmn.h"
#include "L3_L2L.h"
#include "tip_utils.h"
#include "tip.h"
#include "wr.h"
#include "wr_smm_init.h"

#define TIP_CALC_WAIT_TIME(_delay) (_delay/((1000/SS_TICKS_SEC)))
TipVmAssocInfo vmAssocInfo[WR_MAX_CELLS];
TipDrvrTskIpProcIdInfo drvrIpProcIdInfo[WR_MAX_CELLS];
EXTERN Void smWrConfigCell(U16  cellId);

TipVmAssocInfo ul2Info[1];
TipVmAssocInfo ll2Info[1];

EXTERN U32 LL2_IP_ADDR;
EXTERN U32 UL2_IP_ADDR;
EXTERN U8 tipIsL3Ready;

TipCellTransInfo tipL2CellInfo;

/** @brief This function is used to start a given timer. 
 *
 * @details
 *
 *     Function: tipStartTmr
 *
 *         Processing steps:
 *               This function based upon the timer event, derives the TimerCB 
 *               and adds it to the timer queue.
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @param[in] delay : Duration of the timer.
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 tipStartTmr
(
PTR                          cb,
S16                          tmrEvnt,
U32                          delay
)
{
   U32                       wait;
   CmTmrArg                  arg;
   CmTimer                   *tmr = NULLP;
   U16                       maxTmrs = 0;
   U16                       idx;
   wait = 0;
   wait = TIP_CALC_WAIT_TIME(delay);
   switch (tmrEvnt)
   {
      case TIP_MAC_INIT_IND_TMR:
      {
         tmr = &tipL2CellInfo.macInitTimer;
         maxTmrs = 1;
         break;
      }
      case TIP_RLC_INIT_IND_TMR:
      {
         tmr = &tipL2CellInfo.rlcInitTimer;
         maxTmrs = 1;
         break;
      }
      case TIP_PDCP_INIT_IND_TMR:
      {
         tmr = &tipL2CellInfo.pdcpInitTimer;
         maxTmrs = 1;
         break;
      }
      default:
      {
         printf("tipStartTmr: unknown event(%d) received\n", tmrEvnt);
         RETVALUE(RFAILED);
         break;
      }
        
   }
   for(idx = 0; idx < maxTmrs; idx++)
   {
      if (tmr[idx].tmrEvnt == TMR_NONE)
      {
         break;
      }
   }
   if (idx >= maxTmrs)
   {
      RETVALUE(RFAILED);
   }

   /* initialize argument for common timer function */
   if(wait != 0)
   {
      arg.tqCp   = &(tipL2CellInfo.tqCp);
      arg.tq     = tipL2CellInfo.tq;
      arg.cb     = cb;
      arg.timers = tmr;
      arg.evnt   = tmrEvnt;
      arg.wait   = wait;
      arg.tNum   = 0;
      arg.max    = maxTmrs;

      cmPlcCbTq(&arg);
   }
   RETVALUE(ROK);
}/* end of tip Start timer*/ 
/** @brief This function is used to stop a previously running timer. 
 *
 * @details
 *
 *     Function: tipStopTmr
 *
 *         Processing steps:
 *               This function based upon the timer event reterives relevant timerCb and 
 *               tries to determine whether timer is running or not.In case timer 
 *               was running, it is stopped .
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC Void tipStopTmr
(
PTR                          cb,
S16                          event
)
{
   CmTmrArg                  arg;
   U8                        idx = 0;
   Bool                      tmrRunning;
   CmTimer                   *timers = NULLP;
   U8                        max = 0;
   tmrRunning = FALSE;
   switch(event)
   {
      case TIP_MAC_INIT_IND_TMR:
      {
         timers = &tipL2CellInfo.macInitTimer;
         max    = 1;
         if (tipL2CellInfo.macInitTimer.tmrEvnt == event)
         {
            tmrRunning = TRUE;
         }
         break;
      }
     case TIP_RLC_INIT_IND_TMR:
      {
         timers = &tipL2CellInfo.rlcInitTimer;
          max = 1;
         if (tipL2CellInfo.rlcInitTimer.tmrEvnt == event)
         {
            tmrRunning = TRUE;
         }
         break;
      }
     case TIP_PDCP_INIT_IND_TMR:
      {
         timers = &tipL2CellInfo.pdcpInitTimer;
         max    = 1;
         if (tipL2CellInfo.pdcpInitTimer.tmrEvnt == event)
         {
            tmrRunning = TRUE;
         }
         break;
      }

      default:
      {
         printf("tipStopTmr : unknown event(%d) received\n", event);
         break;
      }
   }
   if(tmrRunning == FALSE)
   {
      RETVOID;
   }

   /* initialize argument for common timer function */
   arg.tqCp    = &tipL2CellInfo.tqCp;
   arg.tq      = tipL2CellInfo.tq; 
   arg.timers  = timers;
   arg.cb      = cb;
   arg.evnt    = event;
   arg.wait    = 0;
   arg.max     = max;
   arg.tNum    = idx;
   cmRmvCbTq(&arg);
   RETVOID;
}/*end of stop timer */

/** @brief This function Finds whether Timer is running or not
 *
 * @details
 *
 *     Function: tipIsTmrRunning
 *
 *         Processing steps:
 *               Check Whetether Timer is running or not based on Event type
 *
 * @param[in] tmr : pointre to the Timer. 
 * @param[in] event : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC Bool tipIsTmrRunning
(
CmTimer                      *tmr,
S16                          event
)
{

   if(tmr != NULLP)
   {   
      if(tmr->tmrEvnt == event)
      {
         RETVALUE(TRUE);
      }
      else if (tmr->tmrEvnt != TMR_NONE)
      {
         printf("Invalid Timer event [%d] received\n", event);
      }
   }
   RETVALUE(FALSE);
}

/** @brief This function handles timer expiry. 
 *
 * @details
 *
 *     Function: tipProcTmr
 *
 *         Processing steps:
 *          This function based upon the timer event invokes specific 
 *          routine to handle timer expiry. 
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PRIVATE Void tipProcTmr
(
Ptr                          cb,
S16                          event
)
{
   switch(event)
   {
      case TIP_MAC_INIT_IND_TMR:
      {
        tipStopTmr(NULLP, TIP_MAC_INIT_IND_TMR);
        tipBldSendInitInd(MAC_MOD_ID, MAC_INIT_IND); 
      }
      break;
      case TIP_RLC_INIT_IND_TMR:
      {
        tipStopTmr(NULLP, TIP_RLC_INIT_IND_TMR);
        tipBldSendInitInd(RLC_MOD_ID, RLC_INIT_IND); 
      } 
      break;
      case TIP_PDCP_INIT_IND_TMR:
      {
        tipStopTmr(NULLP, TIP_PDCP_INIT_IND_TMR);
        tipBldSendInitInd(PDCP_MOD_ID, PDCP_INIT_IND); 
      } 
      break;
     default:
      {
        printf("tipProcTmr: unknown timer event(%d)\n", event);
      }
   }
} /* end of tipProcTmr*/

/** @brief Invoked by system services to activate a task with
 *              a timer tick.
 *
 * @details
 *
 *     Function: tipActvTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */

PUBLIC S16 tipActvTmr
(
 Ent   ent,
 Inst  inst
)
{
   cmPrcTmr(&tipL2CellInfo.tqCp, tipL2CellInfo.tq, (PFV) tipProcTmr);
   RETVALUE(ROK);
} /* end of tipActvTmr */

/** @brief This function registers and initializes the timer
 *         queue structures in LTE eNodeB during general config.
 *
 * @details
 *
 *     Function: tipRegInitTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */
PUBLIC S16 tipRegInitTmr
(
Void
)
{
   U16                       idx;
   S16                       ret;
   Ticks                    timeRes  = TIP_TMR_RES;       /* Time resolution */
   

   ret = SRegTmrMt((Ent)ENTSM, (Inst)0, timeRes, tipActvTmr);
   if (ret != ROK)
   {
      printf("smRegInitTmr: SRegTmr Failed \n");
      RETVALUE(RFAILED);
   }

   /* initialize timing queues */
   tipL2CellInfo.tqCp.tmrLen      = TIP_NUM_TQENTRY;
   for (idx = 0; idx < TIP_NUM_TQENTRY; idx++)
   {
      tipL2CellInfo.tq[idx].first    = NULLP;
      tipL2CellInfo.tq[idx].tail     = NULLP;
   }

   RETVALUE(ROK);

} /* smRegInitTmr */

/***********************************************************
 *
 *     Func: tipStartInitTimer
 *
 *
 *     Desc:   Trigger InitInd 
 *     @details start timer to re-send INIT_IND if init_req not received
 *              
 *
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
PUBLIC S16 tipStartInitTimer
(
 U32 msgId
)
{
  static int firstInitInd = 0;
  if(firstInitInd == 0)
  {
    tipRegInitTmr();
    firstInitInd = 1;
    cmInitTimers(&(tipL2CellInfo.macInitTimer), 1);
    cmInitTimers(&(tipL2CellInfo.rlcInitTimer), 1);
    cmInitTimers(&(tipL2CellInfo.pdcpInitTimer), 1);
  }
   switch(msgId)
   {
      case MAC_INIT_IND:
      {
        tipStartTmr(NULLP, TIP_MAC_INIT_IND_TMR, TIP_INIT_IND_TMR_VAL);
      }
      break;
      case RLC_INIT_IND:
      {
        tipStartTmr(NULLP, TIP_RLC_INIT_IND_TMR, TIP_INIT_IND_TMR_VAL);
      } 
      break;
      case PDCP_INIT_IND:
      {
        tipStartTmr(NULLP, TIP_PDCP_INIT_IND_TMR, TIP_INIT_IND_TMR_VAL);
      } 
      break;
     default:
      {
        printf("tipStartInitTimer: unknown timer event(%ld)\n", msgId);
      }
   }
   RETVALUE(ROK);
}

/** @brief Called when INIT_RSP Is received from 
 *              a module.
 *
 * @details
 *
 *     Function: tipModuleInitDone
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */

PUBLIC S16 tipModuleInitDone
(
 U8 cellIdx
)
{
   if ((vmAssocInfo[cellIdx].pdcpAssocState == TIP_INIT_RSP_RECEIVED) &&
         (vmAssocInfo[cellIdx].rlcAssocState == TIP_INIT_RSP_RECEIVED) &&
         (vmAssocInfo[cellIdx].macAssocState == TIP_INIT_RSP_RECEIVED))
   {
      vmAssocInfo[cellIdx].vmOverallState = TIP_INIT_SYNC_SUCCESSFUL;
      if(tipIsL3Ready)
      {
         smWrConfigCell(cellIdx + 1);
      }
   }
   RETVALUE(ROK);
} /* end of tipModuleInitDone */
/***********************************************************
 *
 *     Func: tipInitInd
 *
 *
 *     Desc:   Trigger InitInd 
 *     @details This message to indicate L3 layers are up and ready to receive configuration
 *              
 *
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
PUBLIC S16 tipBldSendInitInd
(
 U32 srcModId,
 U32 msgId
)
{
   TipPacket *packet;
   InitInd   *initInd;
   CmIpAddr  ipAddr;
   S8        strArray[16];
   S8        *addrStr;
   U8        sendBuf[MAX_BUFF_LEN_L2_L3];
   addrStr = strArray;

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;
   if((srcModId == MAC_MOD_ID) || (srcModId == RLC_MOD_ID))
   {
      ipAddr = LL2_IP_ADDR;
   }
   else if ((srcModId == PDCP_MOD_ID) || (srcModId == DATARELAY_MOD_ID))
   {
      ipAddr = UL2_IP_ADDR;
   }
   else
   {
      printf("\n Invalid srcModId %ld. Unable to decide ipAddr\n", srcModId);
      RETVALUE(RFAILED);
   }
   packet->srcModId = srcModId;
   packet->dstModId = RRC_MOD_ID;
   packet->cellId = 1;  
   packet->msgId = msgId;   
   packet->transId = 0; 
   packet->pktLen = TIP_HDR_LEN + sizeof(InitInd);  
   initInd = (InitInd*)((U8*)sendBuf + TIP_HDR_LEN);
   ipAddr =  CM_INET_HTON_U32(ipAddr);
   cmInetNtoa(ipAddr, &addrStr); 
   strcpy((char*)initInd->l2IpAddr, addrStr);
   tipStartInitTimer(msgId); 
   RETVALUE(tipSendToL3(packet->pktLen,(U8*)&sendBuf));
}

/***********************************************************
 *
 *     Func: tipInitReq
 *
 *
 *     Desc:   Trigger InitResp 
 *     @details This message to indicate L3 layers are up and 
 *     ready to receive configuration
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
PUBLIC S16 tipBldSendInitReq
(
 U32 dstModId,
 U8  cellIdx
)
{

   TipPacket *packet;
   InitReq   *initReq;
   CmIpAddr  ipAddr;
   S8        strArray[16];
   S8        *addrStr;
   U8        sendBuf[MAX_BUFF_LEN_L2_L3];

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;
   addrStr = strArray;
   packet->srcModId = RRC_MOD_ID;
   packet->dstModId = dstModId;
   packet->cellId = vmAssocInfo[cellIdx].cellId;  
   packet->pktLen = TIP_HDR_LEN + sizeof(InitReq);  
   initReq = (InitReq*)((U8*)sendBuf + TIP_HDR_LEN);
   ipAddr = vmAssocInfo[cellIdx].l2lIpAddr.u.ipv4TptAddr.address;
   ipAddr =  CM_INET_HTON_U32(ipAddr);
   cmInetNtoa(ipAddr, &addrStr); 
   strcpy((char*)initReq->l2lIpAddr, addrStr);
   ipAddr = vmAssocInfo[cellIdx].l2uIpAddr.u.ipv4TptAddr.address;
   ipAddr =  CM_INET_HTON_U32(ipAddr);
   cmInetNtoa(ipAddr, &addrStr); 
   strcpy((char*)initReq->l2uIpAddr, addrStr);

   switch(dstModId)
   {
      case RLC_MOD_ID:
         {
            packet->msgId = RLC_INIT_REQ; 
            packet->transId = packet->cellId + RLC_MOD_ID; //TODO- Should check on a better TransID
            vmAssocInfo[cellIdx].rlcInitReqTransId = packet->transId;
            vmAssocInfo[cellIdx].rlcAssocState = TIP_INIT_REQ_SENT;
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_RRC, TIP_MOD_RLC,
                  TIP_MSG_RLC_INIT_REQ, packet->transId);
            RETVALUE(tipSendToCLL2(packet->pktLen,(U8*)&sendBuf));
         }
         break;
      case MAC_MOD_ID:
         {
            packet->msgId = MAC_INIT_REQ;   
            packet->transId = packet->cellId + MAC_MOD_ID; //TODO- Should check on a better TransID
            vmAssocInfo[cellIdx].macInitReqTransId = packet->transId;
            vmAssocInfo[cellIdx].macAssocState = TIP_INIT_REQ_SENT;
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_RRC, TIP_MOD_MAC,
                  TIP_MSG_MAC_INIT_REQ, packet->transId);
            RETVALUE(tipSendToCLL2(packet->pktLen,(U8*)&sendBuf));
         }
      case PDCP_MOD_ID:
         {
            packet->msgId = PDCP_INIT_REQ;   
            packet->transId = packet->cellId + PDCP_MOD_ID; //TODO- Should check on a better TransID
            vmAssocInfo[cellIdx].pdcpInitReqTransId = packet->transId;
            vmAssocInfo[cellIdx].pdcpAssocState = TIP_INIT_REQ_SENT;
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_RRC, TIP_MOD_PDCP,
                  TIP_MSG_PDCP_INIT_REQ, packet->transId);
            RETVALUE(tipSendToCUL2(packet->pktLen,(U8*)&sendBuf));
         }
         break;
      default:
         printf("Init Req recv with from wrong Dst(%ld)\n", dstModId);
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
 *
 *     Func: tipBldSendInitResp
 *
 *
 *     Desc:   Trigger InitResp 
 *     @details This message to indicate L3 layers are up and 
 *     ready to receive configuration
 *              
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
PUBLIC S16 tipBldSendInitResp
(
 U32 srcModId,
 U32 msgId,
 U32 transId
)
{
   TipPacket *packet;
   U8        sendBuf[MAX_BUFF_LEN_L2_L3];

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;
   packet->srcModId = srcModId;
   packet->dstModId = RRC_MOD_ID;
   packet->cellId = 1; /*Redundant-not to be considered*/ 
   packet->msgId = msgId;   
   packet->transId = transId; 
   packet->pktLen = TIP_HDR_LEN;
   printf(" Init Response transId %ld \n ", transId);
   RETVALUE(tipSendToL3(packet->pktLen,(U8*)&sendBuf));
}

/***********************************************************
 *
 *     Func: tipHdlInitReq
 *
 *
 *     Desc:   Handle Init request 
 *     @details stop init_ind timer 
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
PUBLIC S16 tipHdlInitReq
(
TipPacket *pkt
)
{
   switch(pkt->msgId)
   {
      case MAC_INIT_REQ:
         {
            printf("\n Received MAC Init Req \n");
            tipStopTmr(NULLP, TIP_MAC_INIT_IND_TMR);
            pkt->msgId = MAC_INIT_RSP;
            tipCpyVmInfofrmInitReq(VMTYPE_LL2, pkt);
         }
         break;
      case RLC_INIT_REQ:
         {
            printf("\n Received RLC Init Req \n");
            tipStopTmr(NULLP, TIP_RLC_INIT_IND_TMR);
            pkt->msgId = RLC_INIT_RSP;
         } 
         break;
      case PDCP_INIT_REQ:
         { 
            printf("\n Received PDCP Init Req \n");
            tipStopTmr(NULLP, TIP_PDCP_INIT_IND_TMR);
            pkt->msgId = PDCP_INIT_RSP;
            tipCpyVmInfofrmInitReq(VMTYPE_UL2, pkt);
         } 
         break;
      default:
         {
            printf("tipHdlInitReq: unknown timer event(%d)\n", (int)pkt->msgId);
         }
   }
   tipBldSendInitResp(pkt->dstModId, pkt->msgId, pkt->transId); 
   RETVALUE(ROK);
}

#ifdef TIP_L3
/***********************************************************
 *
 *     Func: tipL3ProcessInitMsg
 *
 *
 *     Desc:  This function at L3 will handle the INIT_IND 
 *     and INIT_RSP sent by L2Ls and L2Us. 
 *     @details Init sequence from L3 handling perspective
 *
 *     Ret: S16
 *
 *     Notes:
 *
 *     File: 
 *
 **********************************************************/
PUBLIC S16 tipL3ProcessInitMsg
(
Buffer* mBuf
)
{
   U8          rcvBuf[MAX_BUFF_LEN_L2_L3];
   TipPacket   *tipMsg = NULLP;
   MsgLen      msgLen;
   S16         ret;
   MsgLen      bufLen;
   InitInd     *initInd;
   CmIpAddr    ipAddr;
   U8          cellIdx = 0;
   U32         initRspTransId;   

   ret = SFndLenMsg(mBuf, &bufLen); 
   ret = SCpyMsgFix(mBuf, 0, bufLen, rcvBuf, &msgLen);
   tipMsg = (TipPacket*)&rcvBuf;
   initRspTransId = tipMsg->transId;

   switch(tipMsg->msgId)
   {
      /*INIT INDICATION message handling -START*/
      case MAC_INIT_IND:
         {
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_MAC, TIP_MOD_RRC,
                  TIP_MSG_MAC_INIT_IND, tipMsg->transId);
            initInd = (InitInd*)&tipMsg->message;
            cmInetAddr((S8 *)initInd->l2IpAddr, &(ipAddr));
            ipAddr =  CM_INET_HTON_U32(ipAddr);
            cellIdx = tipVldtIPAddressfromVmAssoc(VMTYPE_LL2, ipAddr);
            if (cellIdx == 0xFF)
            {
               RLOG_ARG1(L_ERROR, DBG_CELLID, cellIdx,
                     "IP Address entry not found: %s",
                     (S8*)initInd->l2IpAddr);
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
            if((vmAssocInfo[cellIdx].macAssocState != TIP_INIT_REQ_SENT) && 
                  (vmAssocInfo[cellIdx].macAssocState != TIP_INIT_RSP_RECEIVED))
            {
               tipBldSendInitReq(tipMsg->srcModId, cellIdx);
            }
            else
            {
               RLOG_ARG2(L_DEBUG, DBG_CELLID, cellIdx,
                     "Already ongoing MAC_INIT procedure. Dropping "
                     "MAC_INIT_IND [msgId: %d | state: %d]\n", tipMsg->msgId,
                     vmAssocInfo[cellIdx].macAssocState);
            }
         }
         break;
      case RLC_INIT_IND:
         {
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_RLC, TIP_MOD_RRC,
                  TIP_MSG_RLC_INIT_IND, tipMsg->transId);
            initInd = (InitInd*)&tipMsg->message;
            cmInetAddr((S8 *)initInd->l2IpAddr, &(ipAddr));
            ipAddr =  CM_INET_HTON_U32(ipAddr);
            cellIdx = tipVldtIPAddressfromVmAssoc(VMTYPE_LL2, ipAddr);
            if (cellIdx == 0xFF)
            {
               RLOG_ARG1(L_ERROR, DBG_CELLID, cellIdx,
                     "IP Address entry not found: %s",
                     (S8 *)initInd->l2IpAddr);
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
            if((vmAssocInfo[cellIdx].rlcAssocState != TIP_INIT_REQ_SENT) &&
                  (vmAssocInfo[cellIdx].rlcAssocState != TIP_INIT_RSP_RECEIVED))
            {
               tipBldSendInitReq(tipMsg->srcModId, cellIdx);
            }
            else
            {
               RLOG_ARG2(L_DEBUG, DBG_CELLID, cellIdx,
                     "Already ongoing RLC_INIT procedure. Dropping "
                     "RLC_INIT_IND [msgId: %d | state: %d]\n", tipMsg->msgId,
                     vmAssocInfo[cellIdx].rlcAssocState);
            }
         }
         break;
      case PDCP_INIT_IND:
         {
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_PDCP, TIP_MOD_RRC,
                  TIP_MSG_PDCP_INIT_IND, tipMsg->transId);
            initInd = (InitInd*)&tipMsg->message;
            cmInetAddr((S8 *)initInd->l2IpAddr, &(ipAddr));
            ipAddr =  CM_INET_HTON_U32(ipAddr);
            cellIdx = tipVldtIPAddressfromVmAssoc(VMTYPE_UL2, ipAddr);
            if (cellIdx == 0xFF)
            {
               RLOG_ARG1(L_ERROR, DBG_CELLID, cellIdx,
                     "IP Address entry not found: %s",
                     (S8 *)initInd->l2IpAddr);
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
            if((vmAssocInfo[cellIdx].pdcpAssocState != TIP_INIT_REQ_SENT) &&
                  (vmAssocInfo[cellIdx].pdcpAssocState != TIP_INIT_RSP_RECEIVED))
            {
               tipBldSendInitReq(tipMsg->srcModId, cellIdx);
            }
            else
            {
               RLOG_ARG2(L_DEBUG, DBG_CELLID, cellIdx,
                     "Already ongoing PDCP_INIT procedure. Dropping "
                     "PDCP_INIT_IND [msgId: %d | state: %d]\n", tipMsg->msgId,
                     vmAssocInfo[cellIdx].rlcAssocState);
            }
         }
         break;
      /*INIT INDICATION message handling -END*/
      /*INIT RESPONSE message handling -START*/
      case MAC_INIT_RSP:
         {
            TIP_EVENT_LOG(cellIdx, 0, TIP_MOD_MAC, TIP_MOD_RRC,
                  TIP_MSG_MAC_INIT_RSP, initRspTransId);
            cellIdx = tipFetchCellIdxFromTransId(MAC_MOD_ID, initRspTransId);
            if (cellIdx == 0xFF)
            {
               printf("[MAC_INIT_RSP]:Improper INIT_RSP TransID:%u , cellIdx: %d ", 
                (int)initRspTransId,cellIdx );
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
            if(vmAssocInfo[cellIdx].macAssocState == TIP_INIT_REQ_SENT)
            {
               vmAssocInfo[cellIdx].macAssocState = TIP_INIT_RSP_RECEIVED;
            }
            tipModuleInitDone(cellIdx);
         }
         break;
      case RLC_INIT_RSP:
         {
            cellIdx = tipFetchCellIdxFromTransId(RLC_MOD_ID, initRspTransId);
            if (cellIdx == 0xFF)
            {
               printf("[RLC_INIT_RSP]:Improper INIT_RSP TransID:%u, cellIdx: %d ", 
                (int)initRspTransId, cellIdx);
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
            if(vmAssocInfo[cellIdx].rlcAssocState == TIP_INIT_REQ_SENT)
            {
               vmAssocInfo[cellIdx].rlcAssocState = TIP_INIT_RSP_RECEIVED;
            }
            tipModuleInitDone(cellIdx);
            printf("INIT Response received from RLC for cellIdx: %d\n", cellIdx);
         }
         break;
      case PDCP_INIT_RSP:
         {
            cellIdx = tipFetchCellIdxFromTransId(PDCP_MOD_ID, initRspTransId);
            if (cellIdx == 0xFF)
            {
               printf("[PDCP_INIT_RSP]:Improper INIT_RSP TransID:%u, cellIdx: %d ", 
                 (int)initRspTransId, cellIdx);
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
            if(vmAssocInfo[cellIdx].pdcpAssocState == TIP_INIT_REQ_SENT)
            {
               vmAssocInfo[cellIdx].pdcpAssocState = TIP_INIT_RSP_RECEIVED;
            }
            tipModuleInitDone(cellIdx);
            printf("INIT Response received from PDCP for cellIdx: %d\n", cellIdx);
         }
         break;
      /*INIT RESPONSE message handling -END */
      default:
         {
            printf("L1 Message(%d) is not handled \n", tipMsg->msgId);
         }
         break;
   }
   SPutMsg(mBuf);
   RETVALUE(ROK);
}
#endif
