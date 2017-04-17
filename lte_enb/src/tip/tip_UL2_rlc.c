
/********************************************************************20**
 
     Name:     TIP RRC - RLC Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for control plane primitives on TIP RRC RLC Open Interface.

     File:     tip_UL2_rlc.c

     Sid:      tip_UL2_rlc.c@@

     Prg:      Radisys
     
*********************************************************************21*/
static const char* RLOG_MODULE_NAME="TIP";
static int RLOG_MODULE_ID=847;
static int RLOG_FILE_ID=6;

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "ckw.h"           /* CKW defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "ckw.x"           /* CKW */
#include "rgr.h" //TODO: this must be removed: added due to some dependencies in tip_utils.h(RgrSiCfg)
#include "rgr.x" //TODO: this must be removed: added due to some dependencies in tip_utils.h(RgrSiCfg)
#include "L2U_L2L_version1.h"
#include "tip.h"
#include "tip_rlc.h"
#include "tip_cmn.h"
#include "../ltepdcp/pj.h"
#ifdef TIP_UPPER_L2
#include "../lterlc/kw.h"
#include "../cm/cpj.h"                /* CPJ defines */
#include "../cm/pju.h"                /* PJU defines */
#include "../cm/lpj.h"                /* LPJ defines */
#include "../ltepdcp/pj_udx.h"
#include "../ltepdcp/pj_dl.h"
#include "../ltepdcp/pj_env.h"
#include "../cm/cpj.x"                /* CPJ defines */
#include "../cm/pju.x"                /* PJU defines */
#include "../cm/lpj.x"                /* LPJ defines */
#include "../ltepdcp/pj.x"
#include "../ltepdcp/pj_udx.x"
#include "../ltepdcp/pj_dl.x"
#endif

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

S16 tipFillHdr(Pst *pst, U32 cellId, U32 msgId, U32 transId, U16 len, TipPacket *hdr);
U32 noPktSentFromUl2Ll2 = 0;
U32 noStatuIndRcvFromLl2 = 0;
#ifdef TIP_UPPER_L2
/*
*
*    Fun:     tipUl2StoreUeId
*
*    Desc:    
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    tip_UL2_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 tipUl2StoreUeId
(
Pst        *pst, 
U16        cellId, 
UeIdentity *ueInfo
)
#else
PUBLIC S16 tipUl2StoreUeId(pst, cellId, ueInfo)
Pst        *pst;
U16        cellId;
UeIdentity *ueInfo;
#endif
{
   PjDlUeCb   *ueCb = NULLP;
   PjCb       *tPjCb;
   
   TRC3(tipUl2StoreUeId)
   
   tPjCb = PJ_GET_PJCB(1/*pst->dstInst*/);
   pjDbmFetchDlUeCb(tPjCb, ueInfo->cRnti, cellId, &ueCb);
   if(ueCb  == NULLP)
   {
      printf("DL UeId[%u] not found",ueInfo->cRnti);
      RETVALUE(RFAILED);
   }
   ueCb->ueIndex = ueInfo->ueIndex;
 
   RETVALUE(ROK);
}

/*
*
*    Fun:     tipUl2GetUeId
*
*    Desc:    
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    tip_UL2_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 tipUl2GetUeId
(
Pst        *pst, 
U16        cellId, 
UeIdentity *ueInfo
)
#else
PUBLIC S16 tipUl2GetUeId(pst, cellId, ueInfo)
Pst        *pst;
U16        cellId;
UeIdentity *ueInfo;
#endif
{
   PjDlUeCb   *ueCb = NULLP;
   PjCb       *tPjCb;
    
   TRC3(tipUl2GetUeId)
   
   tPjCb = PJ_GET_PJCB(1/*pst->dstInst*/);

   pjDbmFetchDlUeCb(tPjCb, ueInfo->cRnti, cellId, &ueCb);
   if(ueCb  == NULLP)
   {
      printf("DL UeId[%u] not found", ueInfo->cRnti);
      RETVALUE(RFAILED);
   }
   ueInfo->ueIndex = ueCb->ueIndex;
 
   RETVALUE(ROK);
}

#endif /* TIP_UPPER_L2 */

/**
 *
 * @brief 
 *
 *        Handler for sending the data(SDU) from upper layer. 
 *
 * @b Description:
 *
 *        This function is used to transfer a SDU received from the peer
 *        RLC entity to the service user(PDCP).
 *
 *  @param[in] pst         Post structure  
 *  @param[in] suId        Service User SAP ID 
 *  @param[in] datIndInfo  Data Request Information
 *  @param[in] mBuf         Data Buffer (SDU) 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 tipSendPdcpMsgInd
(
Pst               *pst,
SuId              suId,
KwuDatIndInfo     *datInd,
Buffer            *mBuf
)
#else
PUBLIC S16 tipSendPdcpMsgInd(pst, suId, datInd, mBuf)
Pst               *pst;
SuId              suId;
KwuDatIndInfo     *datInd;
Buffer            *mBuf;
#endif
{
   S16              ret;
   TipPacket        *packet = NULLP;
   PdcpMsgInd       *msgInd;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   U16              msgLen;
   U16              cellId;
   MsgLen           bufLen, cpyLen;

   TRC3(tipSendPdcpMsgInd);

   packet = (TipPacket*)sendBuf;
   msgInd = (PdcpMsgInd *)packet->message;

   SFndLenMsg(mBuf, &bufLen);
   msgInd->datBufLen         = bufLen; 

   ret = SCpyMsgFix(mBuf, 0, bufLen, msgInd->dataBuffer, &cpyLen);
   if((-1 == ret) || (bufLen != cpyLen))
   {
      printf("\n%s: failed to convert to mBuf\n", __func__);
      RETVALUE(RFAILED);
   }

   msgInd->ueInfo.ueIndex = 0;
   msgInd->ueInfo.cRnti   = datInd->rlcId.ueId;
   msgInd->rbInfo.rbId    = datInd->rlcId.rbId;
//   msgInd->rbInfo.lcId    = datInd->rlcId.rbType;
   if(datInd->rlcId.rbType == CM_LTE_SRB)
   {
     msgInd->rbInfo.lcId    = datInd->rlcId.rbId;
   }
   else
   {
     msgInd->rbInfo.lcId    = datInd->rlcId.rbId + 2;
   }

   
   msgInd->reEstblishmentFlag = 0;//TODO:: 0 (Normal Packet) 1 (Packet recieved due to RLC re-establishment)

   cellId = datInd->rlcId.cellId;
   msgLen = TIP_HDR_LEN + sizeof(PdcpMsgInd) - 4 + bufLen; 
 
   tipFillHdr(pst, cellId, PDCP_MSG_IND, 0, msgLen, packet);
   
   SPutMsg(mBuf);
   RETVALUE(tipSendToDUL2(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    tipUnpkPdcpMsgInd
*
*    Desc:   UnPack Message Ind from RLC TIP interface.
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 tipUnpkPdcpMsgInd
(
Pst               *pst,
U8*                recvBuf,
MsgLen             msgLen
)
#else
PUBLIC S16 tipUnpkPdcpMsgInd(pst, recvBuf, msgLen)
Pst               *pst;
U8*                recvBuf,
MsgLen             msgLen
#endif
{
   TipPacket      *hdr;
   SuId           suId = 0;
   PdcpMsgInd     *msgInd;
   KwuDatIndInfo  datInd;
   Buffer         *rcvBuf;

   TRC3(tipUnpkPdcpMsgInd)

   hdr = (TipPacket*)recvBuf;
   msgInd = (PdcpMsgInd*)hdr->message;

#ifdef TIP_UPPER_L2
   if( ROK != tipUl2StoreUeId(pst, hdr->cellId, &(msgInd->ueInfo)))
   {
      printf("\n\n Failed to add Ueindex in UeCb");
   }
#endif

   datInd.rlcId.cellId = hdr->cellId;
   datInd.rlcId.ueId   = msgInd->ueInfo.cRnti;
   datInd.rlcId.rbId   = msgInd->rbInfo.rbId;
   if (msgInd->rbInfo.lcId < 3)
   {
      datInd.rlcId.rbType = CM_LTE_SRB;
      if(datInd.rlcId.rbId  > PJ_MAX_SRB_PER_UE)
      {
         printf("Invalid SRB ID %d", datInd.rlcId.rbId);
         RETVALUE(RFAILED);
      }
      TIP_EVENT_LOG(datInd.rlcId.cellId, datInd.rlcId.ueId, TIP_MOD_RLC,
            TIP_MOD_PDCP, TIP_MSG_PDCP_MSG_IND, hdr->transId);
   }
   else
   {
      datInd.rlcId.rbType = CM_LTE_DRB;
      if(datInd.rlcId.rbId  > PJ_MAX_DRB_PER_UE)
      {
         printf("Invalid DRB ID %d", datInd.rlcId.rbId);
         RETVALUE(RFAILED);
      }
   }

   datInd.isOutOfSeq   = 0;
  
   if(ROK != SGetMsg(pst->region, pst->pool, &rcvBuf))
   {
      printf("SGetMsg failed\n");
      RETVALUE(RFAILED);
   }

   if(ROK != SAddPstMsgMult(msgInd->dataBuffer, msgInd->datBufLen, rcvBuf))
   {
      printf("SAddPstMsgMult failed\n");
      RETVALUE(RFAILED);
   }
    
   RETVALUE(PjLiKwuDatInd(pst, suId, &datInd, rcvBuf));
}

/**
* @brief To convert consolidated SDU status indications to TIP format.
*
* @details
*
*     Function: tipSendRlcStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendRlcStaInd
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
KwuStaIndInfo  *staInd                    /* Status Indication */
)
#else
PUBLIC S16 tipSendRlcStaInd(pst, suId, staInd)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
KwuStaIndInfo  *staInd;                   /* Status Indication */
#endif
{
   TipPacket        *packet;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   RlcSduStatusInd  *rlcStaInd;
   U8               idx;
   U16              msgLen;

   TRC3(tipSendRlcStaInd);

   packet = (TipPacket*)sendBuf;
   
   if(staInd->numSdu > RLC_MAX_NUM_OF_SDU_ID)
   {
      staInd->numSdu = RLC_MAX_NUM_OF_SDU_ID;
   }

   msgLen = TIP_HDR_LEN + 12 + (sizeof(SduStatus) * (staInd->numSdu));
   tipFillHdr(pst, staInd->rlcId.cellId, RLC_SDU_STATUS_IND, 0,
         msgLen, packet);
   rlcStaInd = (RlcSduStatusInd*)((U8*)sendBuf + TIP_HDR_LEN);

   rlcStaInd->ueInfo.ueIndex = 0;//TODO::
   rlcStaInd->ueInfo.cRnti   = staInd->rlcId.ueId;
   rlcStaInd->rbInfo.rbId    = staInd->rlcId.rbId;

   if (staInd->rlcId.rbType == CM_LTE_SRB)
   {
      rlcStaInd->rbInfo.lcId = staInd->rlcId.rbId;
   }
   else
   {
      rlcStaInd->rbInfo.lcId = staInd->rlcId.rbId + 2;
   }

   rlcStaInd->numberOfSDU = staInd->numSdu;

   for(idx = 0; idx < rlcStaInd->numberOfSDU; idx++)
   {
      rlcStaInd->sduStatus[idx].sduId = staInd->sduId[idx];
      rlcStaInd->sduStatus[idx].status = 1 /*TIP_FAILURE*/;
   }

   if (SPutStaticBuffer(pst->region, pst->pool, (Data *)staInd, 
               sizeof(KwuStaIndInfo), 0) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }
   RETVALUE(tipSendToDUL2(packet->pktLen, (U8 *)&sendBuf));
}

/**
* @brief To convert consolidated data TX confirmations to TIP format.
*
* @details
*
*     Function: tipSendRlcDatCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendRlcDatCfm
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
KwuDatCfmInfo  *datCfm                    /* Data Tx Confirm */
)
#else
PUBLIC S16 tipSendRlcDatCfm(pst, suId, datCfm)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
KwuDatCfmInfo  *datCfm;                   /* Data Tx Confirm */
#endif
{
   TipPacket        *packet;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   RlcSduStatusInd  *rlcStaInd;
   U8               idx;
   U16              msgLen;

   TRC3(tipSendRlcDatCfm);

   packet = (TipPacket*)sendBuf;

   if(datCfm->numSduIds > RLC_MAX_NUM_OF_SDU_ID)
   {
      datCfm->numSduIds = RLC_MAX_NUM_OF_SDU_ID;
   }

   msgLen = TIP_HDR_LEN + 12 + (sizeof(SduStatus) * (datCfm->numSduIds));
   tipFillHdr(pst, datCfm->rlcId.cellId, RLC_SDU_STATUS_IND, 0,
         msgLen, packet);
   rlcStaInd = (RlcSduStatusInd*)((U8*)sendBuf + TIP_HDR_LEN);

   rlcStaInd->ueInfo.ueIndex = 0;//TODO::
   rlcStaInd->ueInfo.cRnti   = datCfm->rlcId.ueId;
   rlcStaInd->rbInfo.rbId    = datCfm->rlcId.rbId;
//   rlcStaInd->rbInfo.lcId    = 0;//TODO::
   if (datCfm->rlcId.rbType == CM_LTE_SRB)
   {
      rlcStaInd->rbInfo.lcId = datCfm->rlcId.rbId;
   }
   else
   {
      rlcStaInd->rbInfo.lcId = datCfm->rlcId.rbId + 2;
   }

   rlcStaInd->numberOfSDU    = datCfm->numSduIds;

   for(idx = 0; idx < rlcStaInd->numberOfSDU; idx++)
   {
      rlcStaInd->sduStatus[idx].sduId = datCfm->sduIds[idx];
      rlcStaInd->sduStatus[idx].status = 0/*TIP_SUCCESS*/;
   }

   if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datCfm, 
               sizeof(KwuDatCfmInfo), 0) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }
   RETVALUE(tipSendToDUL2(packet->pktLen, (U8 *)&sendBuf));
}

/**
* @brief To unpack the consolidated SDU status indications from TIP format.
*
* @details
*
*     Function: tipUnpkRlcStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipUnpkRlcStaInd
(
Pst *pst,
U8*  recvBuf,
MsgLen msgLen
)
#else
PUBLIC S16 tipUnpkRlcStaInd(func1, func2, pst, recvBuf, msgLen)
KwuStaInd func1;
KwuDatCfm func2;
Pst *pst;
U8*  recvBuf;
MsgLen  msgLen;
#endif
{
   S16           idx;
   KwuStaIndInfo *staInd = NULLP;
   KwuDatCfmInfo *datCfm = NULLP;
   TipPacket     *hdr;
   SpId          spId = 0;
   RlcSduStatusInd *rlcStaInd;
   U32 failedSdus[RLC_MAX_NUM_OF_SDU_ID];
   U32 datCfmSdus[RLC_MAX_NUM_OF_SDU_ID];
   U16 numFailedSdus = 0;
   U16 numDatCfmSdus = 0;

   TRC3(tipUnpkRlcStaInd)

   hdr = (TipPacket*)recvBuf;

   rlcStaInd = (RlcSduStatusInd*)hdr->message;

   noStatuIndRcvFromLl2 +=rlcStaInd->numberOfSDU;
   if((rlcStaInd->rbInfo.lcId == 1)/*SRB1*/ || 
      (rlcStaInd->rbInfo.lcId == 2)/*SRB2*/)
   {
     printf("Dropping SDU Status Indication \n");
     RETVALUE(RFAILED);
   }
   for(idx = 0; idx < rlcStaInd->numberOfSDU; idx++)
   {
      if(1 /*TIP_FAILURE*/ == rlcStaInd->sduStatus[idx].status)
      {
         failedSdus[idx] = rlcStaInd->sduStatus[idx].sduId;
         numFailedSdus++;
      }
      else
      {
         datCfmSdus[idx] = rlcStaInd->sduStatus[idx].sduId;
         numDatCfmSdus++;
      }
   } 

   if(numFailedSdus)
   {
      if ((SGetStaticBuffer(pst->region, pst->pool, (Data **)&staInd,
                  sizeof(KwuStaIndInfo), 0)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
         RETVALUE(RFAILED);
      }

      
      staInd->rlcId.rbId = rlcStaInd->rbInfo.rbId;
      if(rlcStaInd->rbInfo.lcId < 3) 
      {
         staInd->rlcId.rbType = CM_LTE_SRB;
      }
      else
      {
         staInd->rlcId.rbType = CM_LTE_DRB;
      }
      staInd->rlcId.ueId = rlcStaInd->ueInfo.cRnti;
      staInd->rlcId.cellId = hdr->cellId;

      if(numFailedSdus > KWU_MAX_STA_IND_SDU)
      {
         numFailedSdus = KWU_MAX_STA_IND_SDU -1;
      }

      staInd->numSdu = numFailedSdus;

      cmMemcpy((U8*)&(staInd->sduId), (U8*)&(failedSdus), 
         (numFailedSdus * sizeof(U32)));

      RETVALUE(PjLiKwuStaInd(pst, spId, staInd));
   }

   if(numDatCfmSdus)
   {
      if ((SGetStaticBuffer(pst->region, pst->pool, (Data **)&datCfm,
                  sizeof(KwuDatCfmInfo), 0)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
         RETVALUE(RFAILED);
      }
      
      datCfm->rlcId.rbId = rlcStaInd->rbInfo.rbId;
      if(rlcStaInd->rbInfo.lcId < 3) 
      {
         datCfm->rlcId.rbType = CM_LTE_SRB;
         if(datCfm->rlcId.rbId  > PJ_MAX_SRB_PER_UE)
         {
            printf("Invalid SRB ID %d", datCfm->rlcId.rbId);
            RETVALUE(RFAILED);
         }
      }
      else
      {
         datCfm->rlcId.rbType = CM_LTE_DRB;
         if(datCfm->rlcId.rbId  > PJ_MAX_DRB_PER_UE)
         {
            printf("Invalid DRB ID %d", datCfm->rlcId.rbId);
            RETVALUE(RFAILED);
         }
      }
      datCfm->rlcId.ueId = rlcStaInd->ueInfo.cRnti;
      datCfm->rlcId.cellId = hdr->cellId;
      if(numDatCfmSdus > 1024)
      {
        printf("MAX RLC SDU STATUS reached %d", numDatCfmSdus);
      }
      if(numDatCfmSdus > KWU_MAX_DAT_CFM)
      {
         numDatCfmSdus = KWU_MAX_DAT_CFM - 1;
      }
      datCfm->numSduIds = numDatCfmSdus;
      cmMemcpy((U8*)&(datCfm->sduIds), (U8*)&(datCfmSdus),
         (numDatCfmSdus * sizeof(U32)));

      RETVALUE(PjLiKwuDatCfm(pst, spId, datCfm));
   }

   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler for sending the data(SDU) from upper layer. 
 *
 * @Description:
 *
 *       
 * 
 *
 *  @param[in] pst         Post structure  
 *  @param[in] suId        Service User SAP ID 
 *  @param[in] datReqInfo  Data Request Information
 *  @param[in] mBuf        Data Buffer (SDU) 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 tipSendRlcDataMsgReq
(
Pst               *pst,
SuId              suId,
KwuDatReqInfo     *datReq,
Buffer            *mBuf
)
#else
PUBLIC S16 tipSendRlcDataMsgReq(pst, suId, datReq, mBuf)
Pst               *pst;
SuId              suId;
KwuDatReqInfo     *datReq;
Buffer            *mBuf;
#endif
{
   S16              ret;
   TipPacket        *packet = NULLP;
   RlcDataMsgReq    *msgReq = NULLP;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   U16              msgLen = 0;
   U16              cellId = 0;
   MsgLen           bufLen, cpyLen;

   TRC3(tipSendRlcDataMsgReq)

   packet = (TipPacket*)sendBuf;
   msgReq = (RlcDataMsgReq *)&packet->message;

   SFndLenMsg(mBuf, &bufLen);
   msgLen = TIP_HDR_LEN + 16 /*sizeof(RlcDataMsgReq) -1 sizeof will give you 16bytes and if we do - 1 will fill date from 15bytes rather 13 byte*/ ; 

   ret = SCpyMsgFix(mBuf, 0, bufLen, (sendBuf + msgLen), &cpyLen);
   if((-1 == ret) || (bufLen != cpyLen))
   {
      printf("\n%s: failed to convert to mBuf\n", __func__);
      RETVALUE(RFAILED);
   }

   msgReq->ueInfo.cRnti = datReq->rlcId.ueId; 
   msgReq->rbInfo.rbId  = datReq->rlcId.rbId;
   msgReq->sduIdentity  = datReq->sduId;//TODO:: Same as TransId (mentioned in L2U_L2L.h)
   if (datReq->rlcId.rbType == CM_LTE_SRB)
   {
      msgReq->rbInfo.lcId  = datReq->rlcId.rbId;/* need to fill LCID not an rbType datReq->rlcId.rbType*/;
      TIP_EVENT_LOG(datReq->rlcId.cellId, datReq->rlcId.ueId, TIP_MOD_PDCP,
            TIP_MOD_RLC, TIP_MSG_RLC_DATAMSG_REQ, msgReq->sduIdentity);
   }
   else
   {
      msgReq->rbInfo.lcId = datReq->rlcId.rbId + 2;
   }

   msgReq->dataBufLen = bufLen;
   
#ifdef TIP_UPPER_L2
   if(ROK != tipUl2GetUeId(pst, datReq->rlcId.cellId, &(msgReq->ueInfo)))
   {
      printf("\n\n*** Failed to get Ue Index ****\n\n");
   }
#endif

   cellId = datReq->rlcId.cellId;
   msgLen += bufLen; 
 
   tipFillHdr(pst, cellId, RLC_DATAMSG_REQ, 0, msgLen, packet);
   noPktSentFromUl2Ll2++; 
   SPutMsg(mBuf);
   RETVALUE(tipSendToDLL2(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    tipUnpkRlcDataMsgReq
*
*    Desc:   UnPack Message Req from PDCP TIP interface.
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   tip_UL2_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 tipUnpkRlcDataMsgReq
(
Pst               *pst,
U8*                recvBuf,
MsgLen             msgLen
)
#else
PUBLIC S16 tipUnpkRlcDataMsgReq(pst, recvBuf, msgLen)
Pst               *pst;
U8*                recvBuf;
MsgLen             msgLen;
#endif
{
   S16 		      ret = 0;
   TipPacket      *hdr;
   SuId           suId = 0;
   RlcDataMsgReq  *msgReq;
   KwuDatReqInfo  datReq;
   Buffer         *rcvBuf;

   TRC3(tipUnpkRlcDataMsgReq)

   hdr = (TipPacket*)recvBuf;
   cmMemset((U8 *)&datReq, 0, sizeof(KwuDatReqInfo));

   msgReq = (RlcDataMsgReq*)hdr->message;
   datReq.rlcId.cellId = hdr->cellId;
   datReq.rlcId.ueId   = msgReq->ueInfo.cRnti;
   datReq.rlcId.rbId   = msgReq->rbInfo.rbId;
   datReq.sduId        = msgReq->sduIdentity; 
   if(msgReq->rbInfo.lcId < 3)
   {
      datReq.rlcId.rbType = CM_LTE_SRB;
      datReq.lcType = CM_LTE_LCH_DCCH;
   }
   else
   {
      datReq.rlcId.rbType = CM_LTE_DRB;
      datReq.lcType = CM_LTE_LCH_DTCH;
   }

   if(ROK != SGetMsg(pst->region, pst->pool, &rcvBuf))
   {
      printf("SGetMsg failed\n");
      RETVALUE(ret);
   }

   if(ROK != SAddPstMsgMult(msgReq->dataBuffer, msgReq->dataBufLen, rcvBuf))
   {
      printf("SAddPstMsgMult failed in tip_UL2_rlc.c\n");
      RETVALUE(ret);
   }
   RETVALUE(KwUiKwuDatReq(pst, suId, &datReq, rcvBuf));
}

/**
* @brief unpack all RLC-PDCP massages received from L2-RLC
*
* @details
*
*     Function: tipUnpkRlcPdcpMsg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkRlcPdcpMsg
(
Pst*    pst,
Buffer* mBuf
)
{
  U8               rcvBuf[MAX_BUFF_LEN_L2_L3];
  TipPacket        *hdr = NULLP;
  MsgLen           msgLen;
  MsgLen           bufLen;
  S16              ret,ret1;
   
  ret = SFndLenMsg(mBuf, &bufLen); 
  ret1 = SCpyMsgFix(mBuf, 0, bufLen, rcvBuf, &msgLen);
   
  hdr = (TipPacket*)&rcvBuf;
  switch(hdr->msgId)
  {
     case RLC_SDU_STATUS_IND:
     {
         tipUnpkRlcStaInd(pst, rcvBuf, msgLen);
     }
     break;
     case PDCP_MSG_IND:
     {
         tipUnpkPdcpMsgInd(pst, rcvBuf, msgLen);
     }
     break;
     case RLC_DATAMSG_REQ:
     {
         tipUnpkRlcDataMsgReq(pst, rcvBuf, msgLen);
     }
     break;
     case PDCP_INIT_REQ:
     {
         tipHdlInitReq(hdr);
     }
     break;
     case RLC_DATADISCARD_REQ:
     {
     }
     break;
     default:
     {
        printf("RLC-PDCP Tip Message(%d) unhandled\n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ROK);
}/*end of tipUnpkRlcPdcpMsg*/

#ifdef __cplusplus
}
#endif /* __cplusplus */
